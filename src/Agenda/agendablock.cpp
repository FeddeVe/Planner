#include "agendablock.h"

AgendaBlock::AgendaBlock(qint64 blockID, QDateTime startTime, QDateTime endTime, bool isPlannablke,bool isWorkingDay, bool isFromTMPY, QObject *parent)
    : QObject{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    this->blockID = blockID;
    this->m_startTime = startTime;
    this->m_endTime = endTime;
    this->isPlannable = isPlannablke;
    this->isWorkingDay = isWorkingDay;
    this->overurenvorigemaand = 0;
    this->isFromTMPY = isFromTMPY;

}

AgendaBlock::~AgendaBlock(){
    for(int i = 0; i < this->items.size(); i++){
      //  this->items[i]->deleteLater();
    }
}

bool AgendaBlock::isFree() const{
    if(this->items.count() == 0){
        return true;
    }
    return false;
}

int AgendaBlock::getCount() const{
    return this->items.count();
}

void AgendaBlock::AddBlockItem(AgendaBlockItem *item){
    this->items.push_back(item);
}

int AgendaBlock::getdayXpos() const{
    QTime time = this->m_startTime.time();
    int xPos = time.msecsSinceStartOfDay();
    xPos = xPos / 1000;  // seconds
    xPos = xPos / 60; // minutes;
    xPos = xPos / 15; // kwartiertjes;
    return xPos;
}

