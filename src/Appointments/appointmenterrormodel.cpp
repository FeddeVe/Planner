#include "appointmenterrormodel.h"

AppointmentErrorModel::AppointmentErrorModel(QObject *parent)
    : QAbstractListModel{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

}

int AppointmentErrorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int AppointmentErrorModel::count() const{
    return m_data.count();
}

QVariant AppointmentErrorModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const AppointmentErrorItem  *item = m_data.at(row);
    switch(role) {
    case TitleRole:
        return item->title();
    case JobRole:
        return item->job();
    case IDRole:
        return item->id();
    case MSGRole:
        return item->errMSG();
    }
    return QVariant();
}

QHash<int, QByteArray> AppointmentErrorModel::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[TitleRole] = "Title";
    roles[JobRole] = "Job";
    roles[IDRole] = "ID";
    roles[MSGRole] = "MSG";
    return roles;
}

void AppointmentErrorModel::LoadData(Appointments *appointements){
    // m.lock();
    beginResetModel();
    for(int i = 0; i < m_data.size(); i++){
        m_data[i]->deleteLater();
    }
    m_data.clear();
    m_data.shrink_to_fit();
    for(int i = 0; i < appointements->list.size(); i++){
        appointements->list[i]->appPlanner()->DoMagic();
        if(appointements->list[i]->appPlanner()->m_DurationResult > 0){
            QString job = appointements->list[i]->jobNo() + " // "+ appointements->list[i]->jobTitle();
            QString planMode = "PlanMode : Fixed";
            if(appointements->list[i]->planMode() == PlanModes::AsBlock){
                planMode = "PlanMode : As Block";
            }else if(appointements->list[i]->planMode() == PlanModes::AsTask){
                 planMode = "PlanMode : As Task";
            }
            QString msg = "Could not plan "+ durationToString(appointements->list[i]->appPlanner()->m_DurationLeft) + " out of "+ durationToString(appointements->list[i]->Duration()) + "\n "+ planMode;
            if(appointements->list[i]->msid() > -1){
            AppointmentErrorItem *item = new AppointmentErrorItem(appointements->list[i]->title(), job, appointements->list[i]->msid(), msg);
            this->m_data.push_back(item);
            }
        }
    }
    endResetModel();
    emit this->countChanged();
}


