#include "agendaerrormodel.h"

AgendaErrorModel::AgendaErrorModel(QObject *parent)
    : QAbstractListModel{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

}

int AgendaErrorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int AgendaErrorModel::count() const{
    return m_data.count();
}

QVariant AgendaErrorModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const AgendaErrorItem  *item = m_data.at(row);
    switch(role) {
    case DatumRole:
        return item->datum();
    case MessageRole:
        return item->message();
    }
    return QVariant();
}

QHash<int, QByteArray> AgendaErrorModel::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[DatumRole] = "Datum";
    roles[MessageRole] = "Message";
    return roles;
}

void AgendaErrorModel::LoadData(Agenda *agenda){
    // m.lock();
    beginResetModel();
    for(int i = 0; i < m_data.size(); i++){
        m_data[i]->deleteLater();
    }
    m_data.clear();
    m_data.shrink_to_fit();

    int TMPYFirstBlockID = agenda->agendaBlocks[agenda->agendaBlocks.size() -1]->blockID + 100; // 100 om er zeker van te zijn dat hij niet getriggerd word
    if(agenda->tmpyActive()){
        TMPYFirstBlockID = agenda->TMPYAgendaBlocks[0]->blockID;
    }
    bool useTMPY = false;

    AgendaBlock *block = NULL;
    qint64 index = 0;
    while (1) {
        if(useTMPY){
            if(index >= agenda->TMPYAgendaBlocks.size()){
                break;
            }
            block = agenda->TMPYAgendaBlocks[index];
        }else{
            if(index >= agenda->agendaBlocks.size()){
                break;
            }
            block = agenda->agendaBlocks[index];
            if(block->blockID == TMPYFirstBlockID){
                block = agenda->TMPYAgendaBlocks[0];
                index = 0;
                useTMPY = true;
            }
        }

        if(block->items.size() > 1){
            //double agenda items in block
            if(alreadyExist(block->m_startTime) == false){
                AgendaErrorItem *item = new AgendaErrorItem(block->m_startTime, "Double planned items", useTMPY);
                this->m_data.push_back(item);
            }
        }

        index++;

    }
    endResetModel();
    emit this->countChanged();
}

bool AgendaErrorModel::alreadyExist(QDateTime datum){
    for(int i = 0; i < m_data.size(); i++){
        if(m_data[i]->Datum().date() == datum.date()){
            return true;
        }
    }
    return false;
}



