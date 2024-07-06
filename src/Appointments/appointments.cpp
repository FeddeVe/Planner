#include "appointments.h"

Appointments::Appointments(DBManager *db, Jobs *jobs, QObject *parent)
    : QObject{parent}
{
    this->db = db;
    this->jobs = jobs;
    this->lastEdit = 0;
    this->m_err = new AppointmentErrorModel();
    this->setAppointmentsLoaded(false);

   // this->agenda = agenda;


    this->appointmenttypes = new AppointmentTypes(this);

    connect(jobs, SIGNAL(jobsLoadedChanged()), this, SLOT(LoadAppointments()));
   // QDateTime nu = QDateTime::currentDateTime();
   // this->editAppointment = new Appointment(this, this->jobs,this->db, -1, "", -1, nu,0,false,nu, nu, false,false,0, "#FFFFFF", true, "", 0, false);
}



void Appointments::SetAgenda(Agenda *agenda){
    this->agenda = agenda;
}

void Appointments::LoadAppointments(){
    QJsonObject data;
    data.insert("lastEdit", this->lastEdit);
    DBRequest *request = new DBRequest(RequestTypes::LoadAppointments, data, this);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(AfterLoadAppointments(QJsonObject)));
    this->db->AddRequest(request);
}

void Appointments::AfterLoadAppointments(QJsonObject data){
    QString msg = data.value("msg").toString();
    if(msg != "OK"){
        return;
    }

    QJsonArray a = data.value("data").toArray();
    for (int i = 0; i < a.size(); i++){
        QJsonObject x = a[i].toObject();
        qint64 lastEdit = x.value("lastEdit").toString().toULongLong();
        if(lastEdit > this->lastEdit){
            this->lastEdit = lastEdit;
        }
        int msid = (x.value("id").toString()).toInt();
        QString title = x.value("title").toString();
        int jobID = x.value("jobID").toString().toInt();
        QDateTime startDate = QDateTime::fromSecsSinceEpoch(x.value("startDate").toString().toULongLong());
        int duration = x.value("duration").toString().toInt();
        QDateTime endDate = QDateTime::fromSecsSinceEpoch(x.value("endDate").toString().toULongLong());
        bool blockRest = x.value("blockRest").toString().toInt();
        bool planRest = x.value("planRest").toString().toInt();
        int typeIndex = x.value("type").toString().toInt();
        bool calcTime = x.value("calcTime").toString().toInt();
        QString description = x.value("description").toString();
        bool isClosed = x.value("isClosed").toString().toInt();
        int bucketID = x.value("BucketID").toString().toInt();
        int bucketItemID = x.value("BucketItemID").toString().toInt();
        QDateTime workingOnStart = QDateTime::fromSecsSinceEpoch(x.value("workingOnStart").toString().toULongLong());

        int planMode = x.value("planMode").toString().toInt();

        bool found = false;
        for(int i = 0; i < this->list.size(); i++){
            if(this->list[i]->msid() == msid){
                found = true;
                int bp = 0;
                bp++;
                break;
            }
        }


        if(found == false){
            Appointment *m = new Appointment(this, this->jobs, this->db, msid, title, jobID, startDate, duration, endDate,isClosed, blockRest, planRest, typeIndex, calcTime, description, planMode, bucketID, bucketItemID, workingOnStart);
          // Job *j = new Job(this->db,msid,no,title,client, jobDate, jobStartDate, jobPickDate, this);
            this->list.push_back(m);
        }
    }



    this->setAppointmentsLoaded(true);
}

AppointmentType *Appointments::get_type(int index){
    return this->appointmenttypes->getByID(index);
}

AppointmentTypes *Appointments::types(){
    return this->appointmenttypes;
}

Appointment *Appointments::CreateEditAppointment(){
    QDateTime nu = QDateTime::currentDateTime();
    Appointment *a = new Appointment(this, this->jobs,this->db, -1, "", -2, nu, 0, nu,false, false,false,0, true, "", PlanModes::Fixed, -1, -1, NullDate());
    this->list.push_back(a);
    return a;
}

void Appointments::SortList(){

    //updating model

    //updating agenda
    this->agenda->planAgenda();
    //int bp= 0;
    //bp++;
}

Appointment *Appointments::appointment(int id){
    for(int i = 0; i < this->list.size(); i++){
        if(this->list[i]->msid() == id){
            if(this->list[i]->msid() == -1){
                this->list[i]->setDeleted(false);
            }
            return this->list[i];
        }
    }
    return this->CreateEditAppointment();

}

Appointment *Appointments::get(int id){
    for(int i = 0; i < this->list.size(); i++){
        if(this->list[i]->msid() == id){
            return this->list[i];
        }
    }
    return NULL;

}

void Appointments::AddAppointment(Appointment *app){
     QMutexLocker locker(&m);
     this->list.push_back(app);
}

bool Appointments::appointmentsLoaded() const
{
     return m_appointmentsLoaded;
}

void Appointments::setAppointmentsLoaded(bool newAppointmentsLoaded)
{
     if (m_appointmentsLoaded == newAppointmentsLoaded)
        return;
     m_appointmentsLoaded = newAppointmentsLoaded;
     emit appointmentsLoadedChanged();
}

AppointmentErrorModel *Appointments::errModel(){
     return m_err;
}

void Appointments::CheckErrors(){
     m_err->LoadData(this);
}

void Appointments::removeAppointment(Appointment *appointment){

        QJsonObject obj;
        obj.insert("appointmentID", appointment->msid());
        DBRequest *request = new DBRequest(RequestTypes::DeleteAppointment, obj);
        this->db->AddRequest(request);

        for(int i = 0; i < list.size(); i++){
            if(list[i] == appointment){
                list.erase(list.begin() + i);
            }
        }

        appointment->deleteLater();
      //  this->agenda->loadAgenda();



}

Appointment *Appointments::getBucketItemAppointment(int bucketItemID){
        for(int i = 0; i < this->list.size(); i++){
            if(this->list[i]->BucketItemID() == bucketItemID){
                return this->list[i];
            }
        }
        return NULL;
}

void Appointments::getBucketAppointments(int BucketID, QVector<Appointment*> *list){
        list->clear();
        for(int i = 0; i < this->list.size(); i++){
            if((this->list[i]->bucketID() == BucketID) && (this->list[i]->BucketItemID() < 0)){
                list->push_back(this->list[i]);
            }
        }
}
