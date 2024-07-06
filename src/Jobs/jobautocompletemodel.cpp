#include "jobautocompletemodel.h"

JobAutoCompleteModel::JobAutoCompleteModel(Jobs *jobs, QObject *parent)
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
      QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

int JobAutoCompleteModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int JobAutoCompleteModel::count() const{
    return m_data.count();
}

QVariant JobAutoCompleteModel::data(const QModelIndex &index, int role) const
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
    }
    return QVariant();
}

QHash<int, QByteArray> JobAutoCompleteModel::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[IDRole] = "ID";
    roles[JobNoRole] = "JobNo";
    roles[TitleRole] = "Title";
    roles[ClientRole] = "Client";
    return roles;
}

void JobAutoCompleteModel::LoadModel(const QString searchValue){
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
    endResetModel();
    m.unlock();
}

Job *JobAutoCompleteModel::get(int row) const{
    //QMutexLocker lock( &m);
if((row < 0) || (row >= m_data.count())){
        return jobs->editJob;
}
return m_data[row];
}
