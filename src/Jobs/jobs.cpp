#include "jobs.h"



Jobs::Jobs(DBManager *db, QObject *parent)
    : QObject{parent}
{
    this->db = db;
    this->m_jobsLoaded = false;
    this->last_sync = 0;
    this->m_listModel = new JobListModel(this);
   // Job *j = new Job(this->db, 99, "24-9999", "TestJob 1", "Test Client 1", QDateTime::currentDateTime(), QDateTime::currentDateTime(), QDateTime::currentDateTime());
   // this->jobs.push_back(j);
   // j = new Job(this->db, 101, "24-9998", "TestJob 2", "Test Client 2", QDateTime::currentDateTime(), QDateTime::currentDateTime(), QDateTime::currentDateTime());
   // this->jobs.push_back(j);

   // this->editJob = new Job(this->db, -1, "", "", "", QDateTime::fromSecsSinceEpoch(0), QDateTime::fromSecsSinceEpoch(0), QDateTime::fromSecsSinceEpoch(0), true);
    this->m_autocompletemodel = new JobAutoCompleteModel(this);
    connect(db, SIGNAL(LoginOk()), this, SLOT(LoadJobs()));
    connect(db, SIGNAL(JLERecieved(quint64)), this, SLOT(NewJLE(quint64)));
}

void Jobs::NewJLE(quint64 JLE){
    if(this->jobsLoaded()){
    if(this->last_sync < JLE){
        this->LoadJobs();
    }
    }
}

void Jobs::LoadJobs(){
    QJsonObject data;
    data.insert("lastEdit", QString::number(this->last_sync));
    DBRequest *request = new DBRequest(RequestTypes::LoadJobs, data, this);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(AfterLoadJObs(QJsonObject)));
    this->db->AddRequest(request);
}

void Jobs::AfterLoadJObs(QJsonObject data){
    QMutexLocker lock(&m);
    QString msg = data.value("msg").toString();
    if(msg != "OK"){
        return;
    }

    QJsonArray a = data.value("jobs").toArray();
    for (int i = 0; i < a.size(); i++){
        QJsonObject x = a[i].toObject();
        qint64 lastEdit = x.value("lastEdit").toString().toULongLong();
        if(lastEdit > this->last_sync){
            this->last_sync = lastEdit;
        }
        int msid = (x.value("id").toString()).toInt();
        bool found = false;
        QString no =(x.value("jobNo").toString());
        QString title = (x.value("title").toString());
        QString client = (x.value("client").toString());

        QDateTime jobDate = (QDateTime::fromSecsSinceEpoch(x.value("jobDate").toString().toULongLong()));
        QDateTime jobStartDate = (QDateTime::fromSecsSinceEpoch(x.value("jobStartDate").toString().toULongLong()));
        QDateTime jobPickDate = (QDateTime::fromSecsSinceEpoch(x.value("jobPickDate").toString().toULongLong()));
        for(int i = 0; i < this->jobs.size(); i++){
            if(this->jobs[i]->msid() == msid){
                found = true;
                this->jobs[i]->setno(no);
                this->jobs[i]->settitle(title);
                this->jobs[i]->setclient(client);
                this->jobs[i]->setjobStartDate(jobStartDate);
                this->jobs[i]->setjobDate(jobDate);
                this->jobs[i]->setjobPickDate(jobPickDate);
                break;
            }
        }


        if(found == false){
            Job *j = new Job(this->db,msid,no,title,client, jobDate, jobStartDate, jobPickDate);
            this->jobs.push_back(j);
        }
    }

    if(this->m_jobsLoaded == false){
        this->m_autocompletemodel->LoadModel("");
        this->m_listModel->loadModel("");
    }

    this->setjobsLoaded(true);
    int bp = 0;
    bp++;
}

bool Jobs::jobsLoaded() const{
    return m_jobsLoaded;
}

void Jobs::setjobsLoaded(bool loaded){
    if(m_jobsLoaded == loaded){
        return;
    }
    m_jobsLoaded = loaded;
    emit this->jobsLoadedChanged();
}

Job *Jobs::job(int msid){
    QMutexLocker lock(&m);
    for(int i = 0; i < this->jobs.size(); i++){
        if(this->jobs[i]->msid() == msid){
            return this->jobs[i];
        }
    }


   // Job *j = new Job(this->db,0, "APPPA", "", "", QDateTime::currentDateTime(), QDateTime::currentDateTime(), QDateTime::currentDateTime(), this);
   // this->jobs.push_back(j);
   // return j;
    return NULL;
}

JobAutoCompleteModel *Jobs::autocompletemodel(){
    return m_autocompletemodel;
}

void Jobs::loadAutoComplete(QString Value){
    this->m_autocompletemodel->LoadModel(Value);
}

Job *Jobs::getJob(int rowID) const{
   // QMutexLocker lock(&m);
    if((rowID < 0) || (rowID >= this->jobs.size())){
        return NULL;
    }
    return this->jobs[rowID];
}

Job *Jobs::CreateJob(){
    Job *j = new Job(this->db, -1, "", "", "", QDateTime::fromSecsSinceEpoch(0), QDateTime::fromSecsSinceEpoch(0), QDateTime::fromSecsSinceEpoch(0), true);
    // this->jobs.push_back(j); pushback on save
    return j;
}

void Jobs::ClearEditJob(){
    this->editJob->setmsid(-1);
    this->editJob->setno("");
    this->editJob->settitle("");
    this->editJob->setclient("");
    this->editJob->setjobDate(QDateTime::fromSecsSinceEpoch(0));
    this->editJob->setjobStartDate(QDateTime::fromSecsSinceEpoch(0));
    this->editJob->setjobPickDate(QDateTime::fromSecsSinceEpoch(0));
}

void Jobs::removeJob(Job *j){
    if(j != NULL){
    QJsonObject obj;
    obj.insert("jobMSID", j->msid());
    DBRequest *request = new DBRequest(RequestTypes::DeleteJob, obj);
    db->AddRequest(request);
    for(int i = 0; i < jobs.size(); i++){
        if(jobs[i] == j){
            jobs.erase(jobs.begin() + i);
            break;
        }
    }
    j->deleteLater();
    }
}

JobListModel *Jobs::listModel(){
    return m_listModel;
}

QString Jobs::createJob(int msid, QString jobNo, QString jobTitle, QString jobClient, QString jobDate, QString jobStartDate, QString jobPickDate){
    QDateTime JobDate = QDateTime::fromString(jobDate, "dd-MM-yyyy HH:mm");
    if(!JobDate.isValid()){
        return "JobDate is not valid";
    }
    QDateTime JobStartDate = QDateTime::fromString(jobStartDate, "dd-MM-yyyy HH:mm");
    if(!JobStartDate.isValid()){
        return "JobStartDate is not valid";
    }

    QDateTime JobPickDate = QDateTime::fromString(jobPickDate, "dd-MM-yyyy HH:mm");
    if(!JobPickDate.isValid()){
        return "JobPickDate is not valid";
    }

    Job *j = this->job(msid);
    if(j == NULL){
        j = new Job(this->db, -1, "", "", "", QDateTime::fromSecsSinceEpoch(0), QDateTime::fromSecsSinceEpoch(0), QDateTime::fromSecsSinceEpoch(0));
        this->jobs.push_back(j);
    }
    j->save(jobNo, jobTitle, jobClient, jobDate, jobStartDate, jobPickDate);



    return "OK";
}
