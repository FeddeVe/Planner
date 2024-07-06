#include "agendadayitem.h"

QMutex m;

AgendaDayItem::AgendaDayItem(QDate datum, bool isWorkingDay,bool isFromTMPY, QObject *parent)
    : QAbstractListModel{parent}
{
    this->m_date = datum;
    this->m_isWorkingDay = isWorkingDay;
    this->m_isSelected = false;
    this->m_isFromTMPY = isFromTMPY;
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

QString AgendaDayItem::dayName() const
{
    return m_date.toString("dddd");
}

QString AgendaDayItem::datum() const
{
    return m_date.toString("dd.MM.yyyy");
}

QDate AgendaDayItem::date(){
    return m_date;
}


bool AgendaDayItem::isWorkingDay() const
{
    return m_isWorkingDay;
}

bool AgendaDayItem::isSelected() const
{
    return m_isSelected;
}

void AgendaDayItem::setisSelected(bool newIsSelected)
{
    if (m_isSelected == newIsSelected)
        return;
    m_isSelected = newIsSelected;
    emit isSelectedChanged();
}

int AgendaDayItem::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}



QVariant AgendaDayItem::data(const QModelIndex &index, int role) const
{
    QMutexLocker locker(&m);
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const AgendaDisplayItem *item = m_data.at(row);
    if(item == NULL){
        return QVariant();
    }
    switch(role) {
    case xPosRole:
        return item->xPos();
    case xWidthRole:
        return item->xWidth();
    case xHeightRole:
        return item->xHeight();
    case xTitleRole:
        return item->title();
    case xJobNoRole:
        return item->jobNo();
    case xBoxColor:
        return item->boxColor();
    case xDateRole:
        return item->planDate();
    case xendDateRole:
        return item->endPlanDate();
        //return "EVEN NIETS HIER";
    }
    return QVariant();
}

QHash<int, QByteArray> AgendaDayItem::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[xPosRole] = "xPos";
    roles[xHeightRole] = "xHeight";
    roles[xWidthRole] = "xWidth";
    roles[xTitleRole] = "xTitle";
    roles[xJobNoRole] = "xJobNo";
    roles[xJobTitleRole] = "xJobTitle";
    roles[xBoxColor] = "xBoxColor";
    roles[xDateRole] = "xDate";
    roles[xendDateRole] = "xEndDate";

    return roles;
}

AgendaDisplayItem *AgendaDayItem::get(int row) const{
     QMutexLocker locker(&m);
    if((row < 0) || (row >= m_data.size())){
        //return jobs->editJob;
        int bp = 0;
        bp++;
        return NULL;
    }
    return m_data[row];
}

void AgendaDayItem::AddBlock(AgendaBlock *block){
    QMutexLocker locker(&m);
    this->blocks.push_back(block);

}

void AgendaDayItem::combineData(){
    QMutexLocker locker(&m);
    beginResetModel();
    for(int i = 0; i < this->m_data.size(); i++){
        this->m_data[i]->deleteLater();
    }
    this->m_data.clear();
    this->m_data.shrink_to_fit();

    for(int i = 0; i < this->blocks.size(); i++){
        for(int y = 0; y < this->blocks[i]->items.size(); y++){
            this->blocks[i]->items[y]->isDisplayd = false;
        }
    }

    for(int i = 0; i < this->blocks.size(); i++){

        for(int y = 0; y < this->blocks[i]->items.size(); y++){
            AgendaBlockItem *item = this->blocks[i]->items[y];
            if(item->isDisplayd == false){
                AgendaDisplayItem *displayItem = new AgendaDisplayItem(item->Type, item->appointment, this->blocks[i]->m_startTime, this->blocks[i]->m_endTime);

                displayItem->setXPos(this->blocks[i]->getdayXpos());
                displayItem->setXWidth(this->blocks[i]->getCount());
                displayItem->setXHeight(1);
                this->m_data.push_back(displayItem);
                // searching for the end
                for(int z = i + 1; z < this->blocks.size(); z++){
                    if(this->contains(this->blocks[z], item)){
                        if(this->blocks[z]->getCount() > displayItem->xWidth()){
                            displayItem->setXWidth(this->blocks[z]->getCount());
                        }
                        displayItem->setXHeight(displayItem->xHeight() + 1);
                        displayItem->setendPlanDate(this->blocks[z]->m_endTime);
                }else{
                    break;
                }
            }
            }else{
            int bp = 0;
            bp++;
            }
        }
    }

    endResetModel();
}

bool AgendaDayItem::contains(AgendaBlock *a, AgendaBlockItem *contains){
    for(int i = 0; i < a->items.size(); i++){
        if(a->items[i]->Type == contains->Type){
            if(a->items[i]->Type == AgendaTypes::appointmentType){
            if((a->items[i]->appointment != NULL) && (contains->appointment != NULL)){
                if((a->items[i]->appointment->msid() == contains->appointment->msid()) && (a->items[i]->isClosed == contains->isClosed)){
                    a->items[i]->isDisplayd = true;
                    return true;
                }
            }
            }// CODE FOR TASKS
        }
    }
    return false;
}

bool AgendaDayItem::exist(AgendaDisplayItem *a){
    for(int i = 0; i < m_data.size();i++){
        if(a->type == m_data[i]->type){
            if(a->type == AgendaTypes::appointmentType){
            if((a->m_appointment != NULL) && (m_data[i]->m_appointment != NULL)){
                if(a->m_appointment->msid() == m_data[i]->m_appointment->msid()){
                    return true;
                }
            }
            }
        }
    }
    return false;
}




bool AgendaDayItem::isFromTMPY() const
{
    return m_isFromTMPY;
}

void AgendaDayItem::setIsFromTMPY(bool newIsFromTMPY)
{
    if (m_isFromTMPY == newIsFromTMPY)
        return;
    m_isFromTMPY = newIsFromTMPY;
    emit isFromTMPYChanged();
}
