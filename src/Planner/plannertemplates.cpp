#include "plannertemplates.h"

PlannerTemplates::PlannerTemplates(Appointments *appointments, QObject *parent)
    : QAbstractListModel{parent}
{
    this->appointments = appointments;
    this->LoadModel();

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

int PlannerTemplates::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int PlannerTemplates::count() const{
    return m_data.count();
}

QVariant PlannerTemplates::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const PlannerTemplate  *temp = m_data.at(row);
    switch(role) {
    case MSIDRole:
        return temp->msid();
    case NameRole:
        return temp->name();

    }



    return QVariant();
}

QHash<int, QByteArray> PlannerTemplates::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[MSIDRole] = "ID";
    roles[NameRole] = "Name";
    roles[PlanAsRole] = "PlanAs";

    return roles;
}

void PlannerTemplates::LoadModel(){
    // m.lock();
    m.lock();
    beginResetModel();
    PlannerTemplate *temp = new PlannerTemplate(-1, "New Template", this->appointments);
    this->m_data.push_back(temp);
    temp = new PlannerTemplate(-1, "Prep Licht", this->appointments);
     this->m_data.push_back(temp);
    //load rest behind

    endResetModel();
    m.unlock();
}

PlannerTemplate *PlannerTemplates::get(int row) const{
    //QMutexLocker lock( &m);
    if((row < 0) || (row >= m_data.count())){
        return NULL;
    }
    return m_data[row];
}


