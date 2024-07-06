#include "jobListModel.h"

JobListModel::JobListModel(Jobs *jobs, QObject *parent)
    : QAbstractListModel{parent}
{
    this->jobs = jobs;
    // fill all data
    int index = 0;
    Job *j = jobs->getJob(index);
    while(j != NULL){
        this->m_data.push_back(j);
        index++;
        j=jobs->getJob(index);
    }
    this->SortList();
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

int JobListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int JobListModel::count() const{
    return m_data.count();
}

QVariant JobListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
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
    return QVariant();
}

QHash<int, QByteArray> JobListModel::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[IDRole] = "ID";
    roles[JobNoRole] = "JobNo";
    roles[TitleRole] = "Title";
    roles[ClientRole] = "Client";
    roles[DateRole] = "Date";
    roles[StartDateRole] = "StartDate";
    roles[PickDateRole] = "PickDate";
    roles[StatusColorRole] = "StatusColor";
    return roles;
}

void JobListModel::loadModel(const QString searchValue){
   // m.lock();
    m.lock();
    QString sval = searchValue.toUpper();

    beginResetModel();
    this->m_data.clear();
    this->m_data.shrink_to_fit();
    int index = 0;
    Job *j = jobs->getJob(index);
    while(j!=NULL){
        try{
        if((j->no().toUpper().contains(sval)) || (j->title().toUpper().contains(sval)) || (j->client().toUpper().contains(sval))){
            this->m_data.push_back(j);
        }
        }catch(...){
        int bp = 0;
        bp++;
        }
        index++;
        j = jobs->getJob(index);
        // emit this->dataChanged(index(0),index(0);
    }
    //this->m_data.push_back(jobs->editJob);
    this->SortList();
    endResetModel();
    m.unlock();
}

Job *JobListModel::get(int row) const{
    //QMutexLocker lock( &m);
if((row < 0) || (row >= m_data.count())){
        return NULL;
}
return m_data[row];
}


void JobListModel::SortList(){
for(int i = 0; i < m_data.size(); i++){
        int diff = QDateTime::currentDateTime().secsTo(m_data[i]->JobDate());
        if(diff < 0){
        diff = diff * -1;

        }
         m_data[i]->setSecDiff(diff);
}

std::sort(m_data.begin(), m_data.end(), [](const Job *a, const Job *b) { return a->secDiff() < b->secDiff(); });
}
