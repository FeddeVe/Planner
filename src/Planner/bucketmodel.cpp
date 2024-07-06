#include "bucketmodel.h"

BucketModel::BucketModel(Buckets *buckets, QObject *parent)
    : QAbstractListModel{parent}
{
    this->m_buckets = buckets;
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

int BucketModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}



QVariant BucketModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const Bucket  *bucket = m_data.at(row);
    /*
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

QHash<int, QByteArray> BucketModel::roleNames() const
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

void BucketModel::loadModel(){
    // m.lock();
    m.lock();
    beginResetModel();
    this->m_data.clear();
    this->m_data.shrink_to_fit();
    for(int i = 0; i < this->m_buckets->list.size(); i++){
        if(this->m_buckets->list[i]->job() == this->m_job){
            m_data.push_back(m_buckets->list[i]);
        }
    }
    this->SortList();
    endResetModel();
    m.unlock();
}

Bucket *BucketModel::get(int row) const{
    //QMutexLocker lock( &m);
    if((row < 0) || (row >= m_data.count())){
        return NULL;
    }
    return m_data[row];
}


void BucketModel::SortList(){
    /*
    for(int i = 0; i < m_data.size(); i++){
        int diff = QDateTime::currentDateTime().secsTo(m_data[i]->JobDate());
        if(diff < 0){
            diff = diff * -1;

        }
        m_data[i]->setSecDiff(diff);
    }

    std::sort(m_data.begin(), m_data.end(), [](const Job *a, const Job *b) { return a->secDiff() < b->secDiff(); });
*/
}

void BucketModel::SetJob(Job *j){
    this->m_job = j;
    this->loadModel();
}

void BucketModel::createBucket(){
    int bp = 0;
    bp++;

    Bucket *b = new Bucket(-1, "", -1,-1,-1,2,false, this->m_job, this->m_buckets->db, this->m_buckets->m_appointments, m_buckets->jobs);
    b->save();
    this->m_buckets->AddBucket(b);
    this->loadModel();
}
