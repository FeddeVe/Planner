#include "bucket.h"

int CalcTimeLeft(const Bucket *bucket){
    int duration = 0;
    for(int i = 0; i < bucket->m_data.size(); i++){
        if(bucket->m_data[i]->isClosed() == false){
            duration = duration + bucket->m_data[i]->DurationLeft();
        }
    }
    return duration;
}

Bucket::Bucket(int msid,QString title, float crit1, float crit2, float crit3, float crit4, bool showCompleted, Job *job, DBManager *db, Appointments *appointments, Jobs *jobs, QObject *parent)
    : QAbstractListModel{parent}
{
    this->m_msid = msid;
    this->m_title = title;
    this->m_crit1 = crit1;
    this->m_crit2 = crit2;
    this->m_crit3 = crit3;
    this->m_crit4 = crit4;
    this->calcCritFactor();
    this->m_showCompleted = showCompleted;
    this->m_job = job;
    this->m_db = db;
    this->lastEdit = 0;
    this->m_isLoaded = false;
    this->m_appointments = appointments;
    this->m_jobs = jobs;
    this->m_appointments->getBucketAppointments(m_msid, &this->appointments);
    int bp = 0;
    bp++;
    this->LoadData();

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

void Bucket::LoadData(){
    QJsonObject data;
    data.insert("bucketID", m_msid);
    data.insert("lastEdit", this->lastEdit);
    DBRequest *request = new DBRequest(RequestTypes::LoadBucketItems, data);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(AfterLoad(QJsonObject)));
    this->m_db->AddRequest(request);
}

void Bucket::AfterLoad(QJsonObject data){

    QMutexLocker lock(&m);
    beginResetModel();
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
        bool found = false;
        QDateTime dueDate = QDateTime::fromSecsSinceEpoch(x.value("DueDate").toString().toULongLong());
        int duration = x.value("Duration").toString().toInt();
        QString msPlannerID = x.value("MSPlannerID").toString();
        int index = x.value("SortOrder").toString().toInt();
        int templateID = x.value("TemplateID").toString().toInt();
        QString title = x.value("Title").toString();
        bool isClosed = x.value("isClosed").toString().toInt();
        int planAss = x.value("planAss").toString().toInt();
        QDateTime startWorkingOn = QDateTime::fromSecsSinceEpoch(x.value("startWorkingOn").toString().toULongLong());

        for(int i = 0; i < this->m_data.size(); i++){
            if(this->m_data[i]->msid() == msid){
                found = true;
                this->m_data[i]->SetDueDate(dueDate);
                this->m_data[i]->SetDuration(duration);
                this->m_data[i]->setMsPlannerID(msPlannerID);
                this->m_data[i]->setIndex(index);
                this->m_data[i]->setTemplateID(templateID);
                this->m_data[i]->setTitle(title);
                this->m_data[i]->setIsClosed(isClosed);

                break;
            }
        }


        if(found == false){
            BucketItem *m = new BucketItem(msid, templateID, index, title, dueDate, duration, isClosed, msPlannerID,planAss,startWorkingOn, this, this->m_db);

            connect(m, SIGNAL(durationLeftChanged()), this, SLOT(childDurationLeftChanged()));
            this->m_data.push_back(m);
        }
    }

    int bp = 0;
    bp++;
    //this->plan();
    this->setIsLoaded(true);
}

void Bucket::childDurationLeftChanged(){
    emit this->timeLeftChanged();
}

void Bucket::calcCritFactor(){
    float tmp = m_crit1 + (m_crit2 / 10) + m_crit3;
    float divider = 1.0;
    if(m_crit4 == 1){
        divider = 0.75;
    }else if(m_crit4 == 2){
        divider = 0.5;
    }else if(m_crit4 == 3){
        divider = 0.25;
    }
    tmp = tmp * divider;
    if(tmp < 0){
        tmp = 1.0;
    }
    this->m_critFactor = tmp;
    emit this->critFactorChanged();

}

int Bucket::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int Bucket::count() const{
    return m_data.count();
}

QVariant Bucket::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    /*
    const Job  *job = m_data.at(row);
    switch(role) {
    case IDRole:
        return job->msid();
    case JobNoRole:
        return job->no();
    case TitleRole:
        return job->title();
    case ClientRole:
        return job->client();
    case DateRole:
        return job->jobDate();
    case StartDateRole:
        return job->jobStartDate();
    case PickDateRole:
        return job->jobPickDate();
    case StatusColorRole:
        return job->statusColor();
    }
*/
    return QVariant();
}

QHash<int, QByteArray> Bucket::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    /*
    roles[IDRole] = "ID";
    roles[JobNoRole] = "JobNo";
    roles[TitleRole] = "Title";
    roles[ClientRole] = "Client";
    roles[DateRole] = "Date";
    roles[StartDateRole] = "StartDate";
    roles[PickDateRole] = "PickDate";
    roles[StatusColorRole] = "StatusColor";
*/
    return roles;
}

void Bucket::loadModel(const QString searchValue){
    // m.lock();
    m.lock();
    QString sval = searchValue.toUpper();

    beginResetModel();
    this->m_data.clear();
    this->m_data.shrink_to_fit();

    //this->m_data.push_back(jobs->editJob);
    this->SortList();
    endResetModel();
    m.unlock();
}

BucketItem *Bucket::get(int row) const{
    //QMutexLocker lock( &m);
    if((row < 0) || (row >= m_data.count())){
        return NULL;
    }
    return m_data[row];
}


void Bucket::SortList(){
   // std::sort(m_data.begin(), m_data.end(), [](const BucketItem *a, const BucketItem *b) { return a->secDiff() < b->secDiff(); });
}

QString Bucket::title() const
{
    return m_title;
}

void Bucket::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    for(int i = 0; i < this->appointments.size(); i++){
        this->appointments[i]->setTitle(m_title);
    }
    emit titleChanged();
    this->save();
}

QString Bucket::jobNo() const
{
    return m_job->no();
}

QString Bucket::jobTitle() const
{
    return m_job->title();
}



QString Bucket::jobClient() const
{
    return m_job->client();
}



QString Bucket::crit1() const
{
    if(m_crit1 < 0){
        return "0";
    }
    return QString::number(round(m_crit1));
}

void Bucket::setCrit1(const QString &newCrit1)
{
    int newVal = newCrit1.toInt();

    int bp = 0;
    bp++;


    if (m_crit1 == newVal)
        return;
    m_crit1 = newVal;
    emit crit1Changed();
    this->calcCritFactor();
    this->save();

}

QString Bucket::crit2() const
{
    if(m_crit2 < 0){
        return "0";
    }
    return QString::number(round(m_crit2));
}

void Bucket::setCrit2(const QString &newCrit2)
{
    int newVal = newCrit2.toInt();

    int bp = 0;
    bp++;


    if (m_crit2 == newVal)
        return;
    m_crit2 = newVal;
    emit crit2Changed();
    this->calcCritFactor();
    this->save();
}

QString Bucket::crit3() const
{
    if(m_crit4 < 0){
        return "0";
    }
    return QString::number(round(m_crit4));
}

void Bucket::setCrit3(const QString &newCrit3)
{
    int newVal = newCrit3.toInt();

    int bp = 0;
    bp++;


    if (m_crit3 == newVal)
        return;
    m_crit3 = newVal;
    emit crit3Changed();
    this->calcCritFactor();
    this->save();

}

QString Bucket::crit4() const
{
    if(m_crit4 < 0){
        return "0";
    }
    return QString::number(round(m_crit4));
}

void Bucket::setCrit4(const QString &newCrit4)
{
    int newVal = newCrit4.toInt();

    int bp = 0;
    bp++;


    if (m_crit4 == newVal)
        return;
    m_crit4 = newVal;
    emit crit4Changed();
    this->calcCritFactor();
    this->save();

}

QString Bucket::critFactor() const
{
    return QString::number(round(m_critFactor * 10) / 10);;
}

QString Bucket::timeLeft() const
{
    //CALCULATE TIME LEFT
    return durationToString(CalcTimeLeft(this));
}

QString Bucket::statusColor() const
{
    return m_statusColor;
}

void Bucket::setStatusColor(const QString &newStatusColor)
{
    if (m_statusColor == newStatusColor)
        return;
    m_statusColor = newStatusColor;
    emit statusColorChanged();
}

QString Bucket::statusText() const
{
    return m_statusText;
}

void Bucket::setStatusText(const QString &newStatusText)
{
    if (m_statusText == newStatusText)
        return;
    m_statusText = newStatusText;
    emit statusTextChanged();
}

bool Bucket::showCompleted() const
{
    return m_showCompleted;
}

void Bucket::setShowCompleted(bool newShowCompleted)
{
    if (m_showCompleted == newShowCompleted)
        return;
    m_showCompleted = newShowCompleted;
    emit showCompletedChanged();
}

int Bucket::msid() const
{
    return m_msid;
}

void Bucket::setMsid(int newMsid)
{
    if (m_msid == newMsid)
        return;
    m_msid = newMsid;
    emit msidChanged();
}

int Bucket::status() const
{
    return m_status;
}

void Bucket::setStatus(int newStatus)
{
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    emit statusChanged();
}

Job *Bucket::job(){
    return m_job;
}

void Bucket::save(){
    QJsonObject data;
    data.insert("bucketID", m_msid);
    data.insert("bucketTitle", m_title);
    data.insert("bucketCrit1", m_crit1);
    data.insert("bucketCrit2", m_crit2);
    data.insert("bucketCrit3", m_crit3);
    data.insert("bucketCrit4", m_crit4);
    data.insert("bucketJobID", m_job->msid());
    data.insert("lastEdit", QDateTime::currentSecsSinceEpoch());
    DBRequest *request = new DBRequest(RequestTypes::SaveBucket, data);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(AfterSave(QJsonObject)));
    this->m_db->AddRequest(request);

}

void Bucket::AfterSave(QJsonObject data){
    int msid = data.value("id").toInt();
    if(msid != 0){
        this->setMsid(msid);
    }
    int bp = 0;
    bp++;
}

void Bucket::addItem(QString title, QString duration, QString dueDate, int planAss){
     beginResetModel();
    int dur = durationFromString(duration);
    QDateTime a = QDateTime::fromString(dueDate, "dd:MM:yyyy HH:mm");
    if(!a.isValid()){
        a = QDateTime::fromSecsSinceEpoch(0);
    }



    int planTypeID = m_appointments->appointmenttypes->get(planAss)->index();


    BucketItem *item = new BucketItem(-1, -1, -1, title, a, dur, false, "",planTypeID,QDateTime::fromMSecsSinceEpoch(0), this, this->m_db);

    this->m_data.push_back(item);
    for(int i = 0; i < m_data.size(); i++){
        this->m_data[i]->setIndex(i);
    }
    item->save();
    emit this->timeLeftChanged();
    endResetModel();
}

bool Bucket::isLoaded() const
{
    return m_isLoaded;
}

void Bucket::setIsLoaded(bool newIsLoaded)
{
    if (m_isLoaded == newIsLoaded)
        return;
    m_isLoaded = newIsLoaded;
    emit isLoadedChanged();
}

void Bucket::plan(){
    this->m_appointments->getBucketAppointments(m_msid, &this->appointments);
    int index = 0;
    QDateTime planDate = NullDate();
    int duration = 0;
    int planass = 0;
    QString description = "";

    if(this->m_data.size() > 0){
        planDate = m_data[0]->DueDate();
        planass = m_data[0]->planAss();
    }

    for(int i = 0; i < m_data.size(); i++){
        if((m_data[i]->DueDate() == planDate) && (m_data[i]->planAss() == planass)){
            duration = duration + m_data[i]->DurationLeft();
            description = description + m_data[i]->title() + " \n";
        }else{
            if(index >= this->appointments.size()){
                //nieuwe
                Appointment * app = new Appointment(m_appointments, m_jobs, m_db, -1, m_title, m_job->msid(), QDateTime::currentDateTime(), duration, planDate, false, false, false, planass, true, description, PlanModes::AsTask, m_msid, -1, NullDate());
                app->save(0,0);
                this->m_appointments->AddAppointment(app);
                this->appointments.push_back(app);
                index++;
            }else{
                this->appointments[index]->SetEndDate(planDate);
                this->appointments[index]->SetDuration(duration);
                this->appointments[index]->setDescription(description);
                this->appointments[index]->save(0,0);
                index++;
            }
            planDate = m_data[i]->DueDate();
            planass = m_data[i]->planAss();
            duration = m_data[i]->DurationLeft();
            description = m_data[i]->title() + " /n";
        }
    }

    if(duration > 0){
    if(index >= this->appointments.size()){
        //nieuwe
        Appointment * app = new Appointment(m_appointments, m_jobs, m_db, -1, m_title, m_job->msid(), QDateTime::currentDateTime(), duration, planDate, false, false, false, planass, true, description, PlanModes::AsTask, m_msid, -1, NullDate());
        app->save(0,0);
        this->m_appointments->AddAppointment(app);
        this->appointments.push_back(app);
        index++;
    }else{
        this->appointments[index]->setTitle(m_title);
        this->appointments[index]->SetEndDate(planDate);
        this->appointments[index]->SetDuration(duration);
        this->appointments[index]->setDescription(description);
        index++;
    }
    }

    if(index < this->appointments.size()){
        for(int i = index; i < this->appointments.size(); i++){
            this->appointments[i]->del();
        }
    }

  //  m_appointments->agenda->saveAgenda();
    int bp = 0;
    bp++;
}
