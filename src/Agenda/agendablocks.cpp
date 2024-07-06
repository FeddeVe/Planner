#include "agendablocks.h"

AgendaBlocks::AgendaBlocks(Agenda *agenda, QObject *parent)
    : QObject{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    m_agenda = agenda;
}

bool AgendaBlocks::PublishItem(Appointment *appointment, AppointmentLogItem *logItem){
    QMutexLocker locker(&m);
    QDateTime startTime = logItem->StartDate();
    QDateTime endTime = logItem->EndDate();

    if(logItem->startBlock() <= 0){
        return false;
    }

    if(this->blocks.size() == 0){
        // create blocks
        this->blocks.push_back(this->CreateBlock(logItem->startBlock(), logItem->StartDate()));
    }


    //need to create back ??
    while(this->blocks[0]->blockID > logItem->startBlock()){
        qint64 blockID = this->blocks[0]->blockID -1;
        QDateTime startTime = this->blocks[0]->m_startTime.addSecs(-AGENDABLOCKDURATION);
        this->blocks.insert(0, this->CreateBlock(blockID, startTime));
    }

     //need to create forward ??
    while(this->blocks[this->blocks.size() -1]->blockID < logItem->endBlock()){
        qint64 blockID = this->blocks[this->blocks.size()-1]->blockID + 1;
        QDateTime startTime = this->blocks[this->blocks.size() -1]->m_startTime.addSecs(AGENDABLOCKDURATION);
        this->blocks.push_back(this->CreateBlock(blockID, startTime));
    }

    for(int i = 0; i < this->blocks.size();i++){
        if(this->blocks[i]->blockID == logItem->startBlock()){
            for(int y = i; y < this->blocks.size(); y++){
                if(this->blocks[y]->blockID > logItem->endBlock()){
                    break;
                }
                AgendaBlockItem *item = new AgendaBlockItem(-1, AgendaTypes::appointmentType, appointment, appointment->isClosed());
                this->blocks[y]->AddBlockItem(item);
            }
        }
    }

    this->m_agenda->dayModel()->LoadData(this->m_agenda);
   // this->m_agenda->capModel()->Process(true);
   // this->m_agenda->CheckErrors();
   // appointment->CheckErrors();

    return true;

}

AgendaBlock *AgendaBlocks::CreateBlock(qint64 Index, QDateTime startTime){

    int Weekday = startTime.date().dayOfWeek();
    bool isPlanbaar = false;
    bool isWorkingDay = false;
    switch(Weekday){
    case Qt::Monday:
        if(m_agenda->settings->PlanMonday()){
            isWorkingDay = true;
            if((startTime.time() >= m_agenda->settings->MondayStart()) && (startTime.time() < m_agenda->settings->MondayEnd())){
                isPlanbaar = true;
            }
        }
        break;
    case Qt::Tuesday:

        if(m_agenda->settings->planTuesday()){
            isWorkingDay = true;
            if((startTime.time() >= m_agenda->settings->TuesdayStart()) && (startTime.time() < m_agenda->settings->TuesdayEnd())){
                isPlanbaar = true;
            }
        }
        break;
    case Qt::Wednesday:
        if(m_agenda->settings->planWednesDay()){
            isWorkingDay = true;
            if((startTime.time() >= m_agenda->settings->WednesdayStart()) && (startTime.time() < m_agenda->settings->WednesdayEnd())){
                isPlanbaar = true;
            }
        }
        break;
    case Qt::Thursday:
        if(m_agenda->settings->planThursday()){
            isWorkingDay = true;
            if((startTime.time() >= m_agenda->settings->ThursdayStart()) && (startTime.time() < m_agenda->settings->ThursdayEnd())){
                isPlanbaar = true;
            }
        }
        break;
    case Qt::Friday:
        if(m_agenda->settings->planFriday()){
            isWorkingDay = true;
            if((startTime.time() >= m_agenda->settings->FridayStart()) && (startTime.time() < m_agenda->settings->FridayEnd())){
                isPlanbaar = true;
            }
        }
        break;
    case Qt::Saturday:
        if(m_agenda->settings->planSaturday()){
            isWorkingDay = true;
            if((startTime.time() >= m_agenda->settings->SaturdayStart()) && (startTime.time() < m_agenda->settings->SaturdayEnd())){
                isPlanbaar = true;
            }
        }
        break;
    case Qt::Sunday:
        if(m_agenda->settings->planSunday()){
            isWorkingDay = true;
            if((startTime.time() >= m_agenda->settings->SundayStart()) && (startTime.time() < m_agenda->settings->SundayEnd())){
                isPlanbaar = true;
            }
        }
        break;
    }

    AgendaBlock *block = new AgendaBlock(Index, startTime, startTime.addSecs(AGENDABLOCKDURATION), isPlanbaar, isWorkingDay, false);
    return block;
}

