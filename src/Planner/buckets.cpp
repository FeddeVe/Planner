#include "buckets.h"

Buckets::Buckets(DBManager *db, Jobs *jobs, Appointments *appointments, QObject *parent)
    : QObject{parent}
{
    this->db = db;
    this->jobs = jobs;
    this->lastEdit = 0;
    this->m_appointments = appointments;
    this->setBucketsLoaded(false);
    this->m_bucketModel = new BucketModel(this);
    connect(appointments, SIGNAL(appointmentsLoadedChanged()), this, SLOT(loadBuckets()));
}



void Buckets::SetAgenda(Agenda *agenda){
    this->agenda = agenda;
}

void Buckets::loadBuckets(){
    /*
    QJsonObject data;
    data.insert("lastEdit", this->lastEdit);
    DBRequest *request = new DBRequest(RequestTypes::LoadBuckets, data, this);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(AfterLoadBuckets(QJsonObject)));
    this->db->AddRequest(request);
*/
    this->setBucketsLoaded(true);
}

void Buckets::AfterLoadBuckets(QJsonObject data){
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
        QString title = x.value("Title").toString();
        int crit1 = x.value("Crit1").toString().toInt();
        int crit2 = x.value("Crit2").toString().toInt();
        int crit3 = x.value("Crit3").toString().toInt();
        int crit4 = x.value("Crit4").toString().toInt();
        int jobId = x.value("JobID").toString().toInt();

        bool found = false;
        for(int i = 0; i < this->list.size(); i++){
            if(this->list[i]->msid() == msid){
                found = true;
                int bp = 0;
                bp++;
                break;
            }
        }

        Job *job = this->jobs->job(jobId);
        if(job == NULL){
            int bp = 0;
            bp++;

        }


        if(found == false){
            Bucket *bucket = new Bucket(msid, title, crit1, crit2, crit3, crit4, false, job, db, m_appointments, jobs);
            connect(bucket, SIGNAL(isLoadedChanged()), this, SLOT(childLoaded()));
            this->list.push_back(bucket);
        }
    }
}

void Buckets::childLoaded(){
    bool loaded = true;
    for(int i = 0; i < list.size(); i++){
        if(this->list[i]->isLoaded() == false){
            loaded = false;
            break;
        }
    }
    this->setBucketsLoaded(loaded);
}





Bucket *Buckets::bucket(int id){
    for(int i = 0; i < this->list.size(); i++){
        if(this->list[i]->msid() == id){
            return this->list[i];
        }
    }
    return NULL;

}

BucketModel *Buckets::bucketModel(){
    return this->m_bucketModel;
}

void Buckets::AddBucket(Bucket *bucket){
    QMutexLocker locker(&m);
    this->list.push_back(bucket);
}

void Buckets::removeBucket(Bucket *bucket){

    QJsonObject obj;
    obj.insert("bucketID", bucket->msid());
    DBRequest *request = new DBRequest(RequestTypes::DeleteBucket, obj);
    this->db->AddRequest(request);

    for(int i = 0; i < list.size(); i++){
        if(list[i] == bucket){
            list.erase(list.begin() + i);
        }
    }

    bucket->deleteLater();

}


bool Buckets::bucketsLoaded() const
{
    return m_bucketsLoaded;
}

void Buckets::setBucketsLoaded(bool newBucketsLoaded)
{
    if (m_bucketsLoaded == newBucketsLoaded)
        return;
    m_bucketsLoaded = newBucketsLoaded;
    emit bucketsLoadedChanged();
}

void Buckets::setCurrentJob(int msid){
    this->m_bucketModel->SetJob(this->jobs->job(msid));
    this->m_bucketModel->loadModel();
}
