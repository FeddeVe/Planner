#include "agendadayitemmodel.h"

AgendaDayItemModel::AgendaDayItemModel(QObject *parent)
    : QAbstractListModel{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

}



void AgendaDayItemModel::LoadData(Agenda *agenda){

    if(agenda->planMode() == 1){

    beginResetModel();
    //get the first full day
    for(int i = 0; i < m_data.size(); i++){
        delete m_data[i];
    }
    m_data.clear();
    m_data.shrink_to_fit();

    int startindex = 0;

    AgendaDayItem *item = NULL;
    QDate dag = QDateTime::fromSecsSinceEpoch(0).date();
    qint64 tmpy_switch_block = agenda->agendaBlocks[agenda->agendaBlocks.count()-1]->blockID;

    if(agenda->TMPYAgendaBlocks.size() > 0){
        tmpy_switch_block = agenda->TMPYAgendaBlocks[0]->blockID;
    }
    bool tmpyActive = false;
    int index = 0;
    AgendaBlock *block = NULL;
    while(1){
        if(tmpyActive){
            if(index >= agenda->TMPYAgendaBlocks.size()){
                break;
            }else{
                block = agenda->TMPYAgendaBlocks[index];
            }
        }else{
            if(index >= agenda->agendaBlocks.size()){
                break;
            }else{
                block = agenda->agendaBlocks[index];
            }
            if(block->blockID == tmpy_switch_block){
                tmpyActive = true;
                index = 0;
                if(index >= agenda->TMPYAgendaBlocks.size()){
                    break;
                }else{
                    block = agenda->TMPYAgendaBlocks[index];
                }
            }

        }
        if(dag != block->m_startTime.date()){
            dag = block->m_startTime.date();
            //nieuwe dag
            if(item != NULL){
                m_data.push_back(item);
            }
            item = new AgendaDayItem(dag, block->isWorkingDay, tmpyActive);
        }
        item->AddBlock(block);
        index++;
    }
    if(item != NULL){
        m_data.push_back(item);
    }



    for(int i = 0; i < m_data.size(); i++){
        this->m_data[i]->combineData();
    }
    endResetModel();
    emit this->countChanged();
    }else if(agenda->planMode() == 2){
    beginResetModel();
    //get the first full day
    for(int i = 0; i < m_data.size(); i++){
        delete m_data[i];
    }
    m_data.clear();
    m_data.shrink_to_fit();

    int startindex = 0;

    AgendaDayItem *item = NULL;
    QDate dag = QDateTime::fromSecsSinceEpoch(0).date();

    int index = 0;
    AgendaBlock *block = NULL;
    while(1){
            if(index >= agenda->NewAgendaBlocks->blocks.size()){
                break;
            }
            block = agenda->NewAgendaBlocks->blocks[index];

        if(dag != block->m_startTime.date()){
            dag = block->m_startTime.date();
            //nieuwe dag
            if(item != NULL){
                m_data.push_back(item);
            }
            item = new AgendaDayItem(dag, block->isWorkingDay, false);
        }

        item->AddBlock(block);
        index++;
    }

    if(item != NULL){
        m_data.push_back(item);
    }



    for(int i = 0; i < m_data.size(); i++){
        this->m_data[i]->combineData();
    }

    endResetModel();
    emit this->countChanged();
    }






    //int index = agenda->agendaIndex();

    //this->setAgendaIndex(agenda->agendaIndex());
    this->indexAt(this->curIndex);

}

int AgendaDayItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}



QVariant AgendaDayItemModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const AgendaDayItem  *item = m_data.at(row);
    switch(role) {
    case DayNameRol:
        return item->dayName();
    case DayDatumRole:
        return item->datum();
    case DayIsWorkingDayRole:
        return item->isWorkingDay();
    case DayIsSelected:
        return item->isSelected();
    case IndexRole:
        return row;
    case ISTMPYRole:
        return item->isFromTMPY();
    }
    return QVariant();
}

QHash<int, QByteArray> AgendaDayItemModel::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[DayNameRol] = "Name";
    roles[DayDatumRole] = "Datum";
    roles[DayIsWorkingDayRole] = "WorkingDay";
    roles[DayIsSelected] = "isSelected";
    roles[IndexRole] = "IndexRow";
    roles[ISTMPYRole] = "IsFromTMPY";
    return roles;
}

AgendaDayItem *AgendaDayItemModel::get(int row) const{
    if((row < 0) || (row >= m_data.count())){
        //return jobs->editJob;
        int bp = 0;
        bp++;
        return NULL;
    }
    return m_data[row];
}



int AgendaDayItemModel::indexAt(QDateTime DateTime){
   // beginResetModel();
    this->curIndex = DateTime;

    QDate b = DateTime.date();

    for(int i = 0; i < m_data.count(); i++){
        if(m_data[i]->isSelected()){
            m_data[i]->setisSelected(false);
            emit dataChanged(index(i), index(i));
        }
    }

    for(int i = 0; i < m_data.count(); i++){
        if(m_data[i]->date() == b){
            m_data[i]->setisSelected(true);
            emit dataChanged(index(i), index(i));
            this->setAgendaIndex(i);
            return i;
        }
    }
    //endResetModel();
    this->setAgendaIndex(0);
    return 0;
}




bool AgendaDayItemModel::tmpyActive() const
{
    return m_tmpyActive;
}

void AgendaDayItemModel::setTmpyActive(bool newTmpyActive)
{
    if (m_tmpyActive == newTmpyActive)
        return;
    m_tmpyActive = newTmpyActive;
    emit tmpyActiveChanged();
}

int AgendaDayItemModel::count() const
{
    return m_data.count();
}

void AgendaDayItemModel::setCount(int newCount)
{

}

int AgendaDayItemModel::agendaIndex() const
{
    return m_agendaIndex;
}

void AgendaDayItemModel::setAgendaIndex(int newAgendaIndex)
{
    m_agendaIndex = newAgendaIndex;
    emit agendaIndexChanged();
}

void AgendaDayItemModel::setIndexAt(QString datetime){
    QDateTime a = QDateTime::fromString(datetime, "dd/MM/yyyy HH:mm");
    if(a.isValid()){
        this->setAgendaIndex(this->indexAt(a));
    }
    a = QDateTime::fromString(datetime, "dd-MM-yyyy HH:mm");
    if(a.isValid()){
        this->setAgendaIndex(this->indexAt(a));
    }

}
