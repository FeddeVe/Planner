#include "agendaplanner.h"

AgendaPlanner::AgendaPlanner(Agenda *agenda,Appointments *appointments, Buckets *buckets, QObject *parent)
    : QObject{parent}
{
    this->agenda = agenda;
    this->appointments = appointments;
    this->buckets = buckets;
    this->m_exit = true;
    this->m_running = false;
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

void AgendaPlanner::process(){

     for(int i = 0; i < this->buckets->list.size(); i++){
         this->buckets->list[i]->plan();
     }


     for(int i = 0; i < appointments->list.size(); i++){
         appointments->list[i]->UpdateAttached();
     }

     std::sort(appointments->list.begin(), this->appointments->list.end(), [](const Appointment *a, const Appointment *b) { return a->EndDate() < b->EndDate(); });




    QDateTime endtime = appointments->list[appointments->list.count()-1]->EndDate();
    // if task heeft grotere enddate hier aanpassen

    endtime = endtime.addMonths(1);
    QDateTime starttime = QDateTime::currentDateTime();
    AgendaBlock *startblok = NULL;
    qint64 startIndex = 0;
    for(int i = 0; i < agenda->agendaBlocks.size(); i++){
        if(agenda->agendaBlocks[i]->m_endTime < starttime){
            startblok = agenda->agendaBlocks[i];
            startIndex = i + 1;
        }else{
            break;
        }
    }
    if(startblok == NULL){
        int bp = 0;
        bp++;
    }

    qint64 startID = startblok->blockID;
    starttime = startblok->m_startTime;

    for(int i = 0; i < agenda->TMPYAgendaBlocks.count(); i++){
        agenda->TMPYAgendaBlocks[i]->deleteLater();
    }
    agenda->TMPYAgendaBlocks.clear();
    agenda->TMPYAgendaBlocks.shrink_to_fit();



    while(starttime <= endtime){
        startID++;
        starttime = starttime.addSecs(15*60);
        QDateTime epoch = starttime;
        int Weekday = starttime.date().dayOfWeek();
        bool isPlanbaar = false;
        bool isWorkingDay = false;
        switch(Weekday){
        case Qt::Monday:
            if(agenda->settings->PlanMonday()){
                isWorkingDay = true;
                if((epoch.time() >= agenda->settings->MondayStart()) && (epoch.time() < agenda->settings->MondayEnd())){
                    isPlanbaar = true;
                }
            }
            break;
        case Qt::Tuesday:
            if(agenda->settings->planTuesday()){
                isWorkingDay = true;
                if((epoch.time() >= agenda->settings->TuesdayStart()) && (epoch.time() < agenda->settings->TuesdayEnd())){
                    isPlanbaar = true;
                }
            }
            break;
        case Qt::Wednesday:
            if(agenda->settings->planWednesDay()){
                isWorkingDay = true;
                if((epoch.time() >= agenda->settings->WednesdayStart()) && (epoch.time() < agenda->settings->WednesdayEnd())){
                    isPlanbaar = true;
                }
            }
            break;
        case Qt::Thursday:
            if(agenda->settings->planThursday()){
                isWorkingDay = true;
                if((epoch.time() >= agenda->settings->ThursdayStart()) && (epoch.time() < agenda->settings->ThursdayEnd())){
                    isPlanbaar = true;
                }
            }
            break;
        case Qt::Friday:
            if(agenda->settings->planFriday()){
                isWorkingDay = true;
                if((epoch.time() >= agenda->settings->FridayStart()) && (epoch.time() < agenda->settings->FridayEnd())){
                    isPlanbaar = true;
                }
            }
            break;
        case Qt::Saturday:
            if(agenda->settings->planSaturday()){
                isWorkingDay = true;
                if((epoch.time() >= agenda->settings->SaturdayStart()) && (epoch.time() < agenda->settings->SaturdayEnd())){
                    isPlanbaar = true;
                }
            }
            break;
        case Qt::Sunday:
            if(agenda->settings->planSunday()){
                isWorkingDay = true;
                if((epoch.time() >= agenda->settings->SundayStart()) && (epoch.time() < agenda->settings->SundayEnd())){
                    isPlanbaar = true;
                }
            }
            break;
        }
        this->agenda->TMPYAgendaBlocks.push_back(new AgendaBlock(startID,epoch, epoch.addSecs(15*60), isPlanbaar, isWorkingDay, true));
    }

    for(qint64 i = startIndex; i < this->agenda->agendaBlocks.size(); i++){
       // if(this->agenda->agendaBlocks[i]->blockID >= startID){
            for(int y = 0; y < agenda->agendaBlocks[i]->items.size(); y++){
                if(agenda->agendaBlocks[i]->items[y]->isClosed){
                    AgendaBlockItem *oldItem = agenda->agendaBlocks[i]->items[y];
                    AgendaBlockItem *item = new AgendaBlockItem(oldItem->msid, oldItem->Type, oldItem->appointment, oldItem->isClosed);
                    agenda->TMPYAgendaBlocks[i-startIndex]->AddBlockItem(item);
                }
            }
        //}
    }


    this->PlanApp1();
    this->PlanApp2();
    this->PlanApp3();
}

void AgendaPlanner::PlanApp1(){
    QElapsedTimer timer;
    timer.start();
 //   std::sort(appointments->list.begin(), this->appointments->list.end(), [](const Appointment *a, const Appointment *b) { return a->StartDate() < b->StartDate(); });
    // Appointments Fixed start & end date
    if(agenda->TMPYAgendaBlocks.size() == 0){
        return;
    }
    qint64 curIndex = 0;
    for(int i = 0; i < appointments->list.size(); i++){
        Appointment *app = appointments->list[i];
        if((app->deleted() == false) && (app->planMode() == PlanModes::Fixed)){
            while(1){
                if(curIndex >= agenda->TMPYAgendaBlocks.size()){
                    int bp = 0;
                    bp++;

                    //zou niet mogen kunnen, tmpy agenda is groter dan laatste appointment
                }
            AgendaBlock *curBlock = agenda->TMPYAgendaBlocks[curIndex];
            if(app->EndDate() < curBlock->m_startTime){
                //something strange or is in the past;
                int bp = 0;
                bp++;
                break; // break while 1 loop
            }else{
                if((app->EndDate() > curBlock->m_startTime) && (app->EndDate() <= curBlock->m_endTime)){
                    //startblock found
                    qint64 tmpindex = curIndex;
                    int duration = app->durationLeft();
                    while(duration > 0){
                        AgendaBlockItem *item = new AgendaBlockItem(-1, appointmentType, app, false);
                        agenda->TMPYAgendaBlocks[tmpindex]->items.push_back(item);
                        duration = duration - AGENDABLOCKDURATION;
                        tmpindex = tmpindex -1;
                        if(tmpindex <= 0){
                            break;
                        }
                    }
                    break; // break while 1 loop
                }
            }

            curIndex++;
            if(curIndex >= agenda->TMPYAgendaBlocks.size()){
                int bp = 0;
                bp++;

                //zou niet mogen kunnen, tmpy agenda is groter dan laatste appointment
            }
             }

        }
    }

    qint64 method1time = timer.elapsed();

    //OLD METHOD
    /*

    for(int i = 0; i < appointments->list.size(); i++){
        if((appointments->list[i]->deleted() == false) && (appointments->list[i]->planMode() == PlanModes::Fixed)){
           // QDateTime endDate = appointments->list[i]->EndDate();
            int Duration = appointments->list[i]->durationLeft();
            if(Duration > 0){
            QDateTime startDate = appointments->list[i]->StartDate();
            QDateTime endDate = startDate.addSecs(Duration);
            AgendaBlock *endBlock = this->getBlock(endDate);
            //check als startdate >= enddate
            if(endBlock == NULL){
                int bp = 0;
                bp++;
            }else{
                AgendaBlockItem *bli = new AgendaBlockItem(-1, AgendaTypes::appointmentType, appointments->list[i], false);
                endBlock->AddBlockItem(bli);
                int Blockindex = this->getBlockIndex(endBlock);
                if(Blockindex == -1){
                    int bp = 0;
                    bp++;
                }
            while(Blockindex > 0){
                Blockindex = Blockindex -1;
                AgendaBlock *bl =agenda->TMPYAgendaBlocks[Blockindex];
                if(bl->m_endTime > startDate){
                    bli = new AgendaBlockItem(-1, AgendaTypes::appointmentType, appointments->list[i], false);
                    agenda->TMPYAgendaBlocks[Blockindex]->AddBlockItem(bli);
                }else{
                    break;
                }
            }
            }
        }
       }
    }
*/
}

void AgendaPlanner::PlanApp2(){
    QElapsedTimer timer;
    timer.start();

    if(agenda->TMPYAgendaBlocks.size() == 0){
        return;
    }
    qint64 curIndex = 0;
    for(int i = 0; i < appointments->list.size(); i++){
        Appointment *app = appointments->list[i];
        if((app->deleted() == false) && (app->planMode() == PlanModes::AsBlock)){
            while(1){
                AgendaBlock *curBlock = agenda->TMPYAgendaBlocks[curIndex];
                if(app->EndDate() < curBlock->m_startTime){
                    //something strange or is in the past;
                    int bp = 0;
                    bp++;
                    break; // break while 1 loop
                }else{
                    if((app->EndDate() > curBlock->m_startTime) && (app->EndDate() <= curBlock->m_endTime)){
                        //startblock found
                        qint64 tmpindex = curIndex;
                        int duration = app->durationLeft();
                        int noBlocks = 0;
                        if(duration > 0){
                            noBlocks = (float(duration) / (AGENDABLOCKDURATION)) + 0.5;
                        }
                        QVector<AgendaBlock*> reserverdBlocks;
                        while(tmpindex > 0){
                            AgendaBlock *pscurBlock = this->agenda->TMPYAgendaBlocks[tmpindex];
                            if((pscurBlock->isPlannable) && (pscurBlock->items.size() == 0)){
                                reserverdBlocks.push_back(pscurBlock);
                                if(reserverdBlocks.size() == noBlocks){
                                    for(int y = 0; y < reserverdBlocks.size(); y++){
                                        AgendaBlockItem *item = new AgendaBlockItem(-1, appointmentType, app, false);
                                        reserverdBlocks[y]->AddBlockItem(item);
                                    }
                                    reserverdBlocks.clear();
                                    break;
                                }
                            }else{
                                reserverdBlocks.clear();
                            }
                            tmpindex = tmpindex-1;
                        }

                        //als niet alles gepland kan worden plan dan dit maar
                        for(int y = 0; y < reserverdBlocks.size(); y++){
                            AgendaBlockItem *item = new AgendaBlockItem(-1, appointmentType, app, false);
                            reserverdBlocks[y]->AddBlockItem(item);
                        }
                    break; // break while 1 loop
                }
            }
            curIndex++;
            if(curIndex >= agenda->TMPYAgendaBlocks.size()){
                int bp = 0;
                bp++;
                //zou niet mogen kunnen, tmpy agenda is groter dan laatste appointment
            }
             }

        }
    }

    qint64 method1time = timer.elapsed();
    timer.restart();

    //OLD METHOD

    /*
    for(int i = 0; i < agenda->appointments->list.size(); i++){
       Appointment *app = agenda->appointments->list[i];
       if(app->planMode() == PlanModes::AsBlock){
            int duration = app->durationLeft();
            int noBlocks = 0;
            if(duration > 0){
            noBlocks = (float(duration) / (AGENDABLOCKDURATION)) + 0,5;
            }
            QDateTime endDate = app->EndDate();
            AgendaBlock *endBlock = this->getBlock(endDate);
            if(endBlock == NULL){
            break;
            }
            qint64 endBlockIndex = getBlockIndex(endBlock);

            qint64 index = endBlockIndex;
            QVector<AgendaBlock*> reserverdBlocks;
            while(index > 0){
                index = index - 1;
                AgendaBlock *curBlock = this->agenda->TMPYAgendaBlocks[index];
                if((curBlock->isPlannable) && (curBlock->items.size() == 0)){
                reserverdBlocks.push_back(curBlock);
                if(reserverdBlocks.size() == noBlocks){
                for(int y = 0; y < reserverdBlocks.size(); y++){
                    AgendaBlockItem *item = new AgendaBlockItem(-1, appointmentType, app, false);
                    reserverdBlocks[y]->AddBlockItem(item);

                }
                reserverdBlocks.clear();
                break;
                }
                }else{
                reserverdBlocks.clear();
                }
            }
            for(int y = 0; y < reserverdBlocks.size(); y++){
                AgendaBlockItem *item = new AgendaBlockItem(-1, appointmentType, app, false);
                reserverdBlocks[y]->AddBlockItem(item);

            }



       }
    }
*/

    qint64 method2time = timer.elapsed();
    int bp = 0;
    bp++;
}

void AgendaPlanner::PlanApp3(){

    if(agenda->TMPYAgendaBlocks.size() == 0){
        return;
    }
    qint64 curIndex = 0;
    for(int i = 0; i < appointments->list.size(); i++){
        Appointment *app = appointments->list[i];
        if((app->deleted() == false) && (app->planMode() == PlanModes::AsTask)){
            while(1){
            AgendaBlock *curBlock = agenda->TMPYAgendaBlocks[curIndex];
            if(app->EndDate() < curBlock->m_startTime){
                //something strange or is in the past;
                int bp = 0;
                bp++;
                break; // break while 1 loop
            }else{
                if((app->EndDate() > curBlock->m_startTime) && (app->EndDate() <= curBlock->m_endTime)){
                    //startblock found
                    qint64 tmpindex = curIndex;
                    int duration = app->durationLeft();
                    int noBlocks = 0;
                    if(duration > 0){
                            noBlocks = (float(duration) / (AGENDABLOCKDURATION)) + 0.5;
                    }
                    while((noBlocks > 0) && (tmpindex >= 0)){
                            AgendaBlock *pscurBlock = this->agenda->TMPYAgendaBlocks[tmpindex];
                            if((pscurBlock->isPlannable) && (pscurBlock->items.size() == 0)){
                                AgendaBlockItem *item = new AgendaBlockItem(-1, appointmentType, app, false);
                                pscurBlock->AddBlockItem(item);
                                noBlocks = noBlocks - 1;
                            }
                            tmpindex = tmpindex-1;
                    }
                    break; // break while 1 loop
                }
            }
            curIndex++;
            if(curIndex >= agenda->TMPYAgendaBlocks.size()){
                int bp = 0;
                bp++;
                //zou niet mogen kunnen, tmpy agenda is groter dan laatste appointment
            }
             }

        }
    }

    //old Method
    /*

    for(int i = 0; i < agenda->appointments->list.size(); i++){
       Appointment *app = agenda->appointments->list[i];
       if(app->planMode() == PlanModes::AsTask){
            int duration = app->durationLeft();
            int noBlocks = 0;
            if(duration > 0){
                noBlocks = (float(duration) / (AGENDABLOCKDURATION)) + 0,5;
            }
            QDateTime endDate = app->EndDate();
            AgendaBlock *endBlock = this->getBlock(endDate);
            if(endBlock == NULL){
                break;
            }
            qint64 endBlockIndex = getBlockIndex(endBlock);
            qint64 index = endBlockIndex;

            while(index > 0){
                index = index - 1;
                AgendaBlock *curBlock = this->agenda->TMPYAgendaBlocks[index];
                if((curBlock->isPlannable) && (curBlock->items.size() == 0)){
                    AgendaBlockItem *item = new AgendaBlockItem(-1, appointmentType, app, false);
                curBlock->AddBlockItem(item);
                    noBlocks = noBlocks-1;
                if(noBlocks == 0){
                        break;
                    }
                }
            }

       }
    }
*/
}

void AgendaPlanner::PublishResults(){
    //this->agenda->dayModel()->LoadData(this->agenda);
}


AgendaBlock *AgendaPlanner::getBlock(QDateTime date){
    AgendaBlock *ret = NULL;
    for(int i = 0; i < agenda->TMPYAgendaBlocks.size(); i++){
        if(agenda->TMPYAgendaBlocks[i]->m_endTime <= date){
            ret = agenda->TMPYAgendaBlocks[i];
        }else{
            break;
        }
    }
    return ret;
}

qint64 AgendaPlanner::getBlockIndex(AgendaBlock *block){
    for(int i = 0; i < agenda->TMPYAgendaBlocks.size(); i++){
        if(agenda->TMPYAgendaBlocks[i]->blockID == block->blockID){
            return i;
        }
    }
    return -1;
}


bool AgendaPlanner::exit() const
{
    return m_exit;
}

void AgendaPlanner::setExit(bool newExit)
{
    if (m_exit == newExit)
        return;
    m_exit = newExit;
    emit exitChanged();
}

bool AgendaPlanner::running() const
{
    return m_running;
}

void AgendaPlanner::setRunning(bool newRunning)
{
    if (m_running == newRunning)
        return;
    m_running = newRunning;
    emit runningChanged();
}
