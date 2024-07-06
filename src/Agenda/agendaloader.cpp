#include "agendaloader.h"

AgendaLoader::AgendaLoader(Agenda *agenda,Appointments*appointments, QObject *parent)
    : QObject{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    this->agenda = agenda;
    this->appointments = appointments;
    this->planner = new AgendaPlanner(agenda,appointments, agenda->buckets);
    this->running = false;
}

void AgendaLoader::Run(){
    //continues thread
    this->AddAction(LoaderType::agenda_Load);

    QThread *thread = QThread::create([this]{
        while(appointments->appointmentsLoaded() == false){
            QThread::msleep(10);
        }

        while(1) {
            int lItem = -1;
            AgendaLoaderItem *item = NULL;
            vectorMutex.lock();
            if(this->loaderItems.size() > 0){
                item = this->loaderItems[0];
                lItem = this->loaderItems[0]->type;
            }
            vectorMutex.unlock();
            if(lItem == LoaderType::agenda_Load){
                 emit this->isLoaderRunning(true);
                this->LoadAgenda();
                this->FixeDoubleItems();
                this->agenda->wta->process(this->agenda);
                this->PublishResults(false);
                emit this->isLoaderRunning(false);
            }else if(lItem == LoaderType::agenda_Plan){
                   emit this->isLoaderRunning(true);
                this->PlanAgenda();
                this->FixeDoubleItems();
                this->PublishResults(false);
                 emit this->isLoaderRunning(false);
            }else if(lItem == LoaderType::agenda_Save){
                int bp = 0;
                bp++;
            }else if(lItem == LoaderType::agenda_PlanAndSave){
                emit this->isLoaderRunning(true);
                this->PlanAgenda();
                this->FixeDoubleItems();
                this->SaveAgenda();
                this->PublishResults(true);
                emit this->isLoaderRunning(false);
            }else if(lItem == LoaderType::appointment_Delete){
                 emit this->isLoaderRunning(true);
                this->PlanAgenda();
                this->RemoveAppointment(item->app);
                this->FixeDoubleItems();
                this->SaveAgenda();
                this->PublishResults(true);
                 emit this->isLoaderRunning(false);
            }else if(lItem == LoaderType::appointment_DeleteTimeFrame){
                emit this->isLoaderRunning(true);
                this->RemoveAppointmentTimeFrame(item->app, item->starttime, item->endtime);
                this->PublishResults(false);
                this->PlanAgenda();
                this->FixeDoubleItems();
                this->SaveAgenda();
                this->PublishResults(true);
                 emit this->isLoaderRunning(false);
            }else if(lItem == LoaderType::appointment_SaveTimeFrame){
                emit this->isLoaderRunning(true);
                this->SaveAppointmentTimeFrame(item->app, item->starttime, item->endtime, item->isClosed);

                this->PlanAgenda();

                this->FixeDoubleItems();

                this->SaveAgenda();

                this->PublishResults(true);
                emit this->isLoaderRunning(false);
            }else if(lItem == LoaderType::agenda_Export){
                  emit this->isLoaderRunning(true);
                this->PlanAgenda();
                this->FixeDoubleItems();
                this->SaveAgenda();
                this->PublishResults(true);
                 emit this->isLoaderRunning(false);
                this->agenda->graph->SaveAgenda(this->agenda);
            }else if(lItem == LoaderType::appointment_Close){
                 emit this->isLoaderRunning(true);
                this->PlanAgenda();
                this->FixeDoubleItems();
                this->CloseAppointment(item->app);
                this->SaveAgenda();
                this->PublishResults(true);
                 emit this->isLoaderRunning(false);
            }
            if(lItem != -1){
            vectorMutex.lock();
                this->loaderItems[0]->deleteLater();
                this->loaderItems.removeAt(0);
            vectorMutex.unlock();
            }

            if(this->loaderItems.size() > 0){

            }else{
            QThread::msleep(500);
            }


        } //while(1)
    });

    thread->start();
}

void AgendaLoader::LoadAgenda(){
    m.lock();
    //Clear blocks
    for(int i = 0; i < agenda->agendaBlocks.size(); i++){
        delete agenda->agendaBlocks[i];
    }
    agenda->agendaBlocks.clear();
    agenda->agendaBlocks.shrink_to_fit();

    this->wait_for_loading = true;
    DBRequest *request = new DBRequest(RequestTypes::LoadAgendaItems, QJsonObject());
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(afterLoadItems(QJsonObject)));
    this->agenda->db->AddRequest(request);

    while(wait_for_loading == true){
        QThread::msleep(10);
    }

    m.unlock();
}

void AgendaLoader::AddAction(LoaderType type, Appointment *appointent, QDateTime startTime, QDateTime endtime, bool isClosed){
    vectorMutex.lock();
    //check if action is already in list dan removen want hier is de nieuwe cue

    for(int i = 0; i < loaderItems.size(); i++){
        if(loaderItems[i]->type == type){
            loaderItems[i]->deleteLater();
            loaderItems.removeAt(i);
            i=i-1;
        }
    }
    AgendaLoaderItem *item = new AgendaLoaderItem(type, appointent, startTime, endtime, isClosed);
    loaderItems.push_back(item);
    vectorMutex.unlock();
}

void AgendaLoader::PlanAgenda(){
    m.lock();

    this->planner->process();

    m.unlock();
}

void AgendaLoader::PublishResults(bool saveData){
    for(int i = 0; i < this->appointments->list.size(); i++){
        this->appointments->list[i]->planner->DoMagic();
    }
    this->agenda->dayModel()->LoadData(this->agenda);
    this->agenda->capModel()->Process(saveData);
    this->agenda->CheckErrors();
    this->appointments->CheckErrors();
    /*
    if(saveData){
        this->agenda->graph->SaveAgenda(agenda);
    }
*/
}

void AgendaLoader::process(){
    //waiting for finishing task & appointments
    if(this->running){
       // qApp->processEvents();
        QThread::msleep(10);
    }
    this->running = true;


    while(appointments->appointmentsLoaded() == false){
        qApp->processEvents();
        QThread::msleep(10);
    }




    //Clear blocks
    for(int i = 0; i < agenda->agendaBlocks.size(); i++){
        delete agenda->agendaBlocks[i];
    }
    agenda->agendaBlocks.clear();
    agenda->agendaBlocks.shrink_to_fit();

    DBRequest *request = new DBRequest(RequestTypes::LoadAgendaItems, QJsonObject());
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(afterLoadItems(QJsonObject)));
    this->agenda->db->AddRequest(request);

    //for nu
   // afterLoadItems(QJsonObject());
}

void AgendaLoader::afterLoadItems(QJsonObject data){

    QString msg = data.value("msg").toString();
    if(msg != "OK"){

        return;
    }

    for(int i = 0; i < dataItems.size(); i++){
        dataItems[i]->deleteLater();
    }
    dataItems.clear();
    dataItems.shrink_to_fit();

    QJsonArray a = data.value("data").toArray();

        //blokken creeeren
        QDateTime lastItemDate = QDateTime::currentDateTime();
        QDateTime firstItemDate = QDateTime::currentDateTime();
        for(int i = 0; i < agenda->appointments->list.size(); i++){
            if(agenda->appointments->list[i]->StartDate() < firstItemDate){
                firstItemDate = agenda->appointments->list[i]->StartDate();
            }
            if(agenda->appointments->list[i]->EndDate() > lastItemDate){
                lastItemDate = agenda->appointments->list[i]->EndDate();
            }
        }
        QDateTime firstBlockDate = QDateTime::fromSecsSinceEpoch(0);
        qint64 firstBlockIndex = 0;

          if(a.size() > 0){
            QJsonObject x = a[0].toObject();
            //JSON OBJECTEN CHECKEN !!!
            QString blockID = x.value("blockID").toString();
             firstBlockDate = QDateTime::fromSecsSinceEpoch(x.value("blockStartTime").toString().toLongLong());
             firstBlockIndex = x.value("blockID").toString().toLongLong();
          }

        // zodat we kunnen plannen vanaf complete maanden
        lastItemDate = lastItemDate.addMonths(1);
          if(firstItemDate < agenda->agendaStart){
             firstItemDate= agenda->agendaStart;
        }
        firstItemDate = firstItemDate.addMonths(-1);

        this->CreateBlocks(firstItemDate, firstBlockIndex, firstBlockDate, lastItemDate);



    for (int i = 0; i < a.size(); i++){
        QJsonObject x = a[i].toObject();
             qint64 msid = x.value("id").toString().toLongLong();
        qint64 blockID = x.value("blockID").toString().toULongLong();
             quint64 blockStartTime = x.value("blockStartTime").toString().toLongLong();
        qint64 endBlockID = x.value("endBlockID").toString().toULongLong();
        bool isclosed = x.value("isClosed").toString().toInt();
             int type = x.value("type").toString().toInt();
        int typeID = x.value("typeID").toString().toInt();
             Appointment *a = this->appointments->get(typeID);
          AgendaTypes aType = static_cast<AgendaTypes>(type);

             AgendaDataItem *dataItem = new AgendaDataItem(msid, blockID, blockStartTime, endBlockID, isclosed, type, typeID);
        this->dataItems.push_back(dataItem);

        if(a != NULL){
                AgendaBlockItem *item = new AgendaBlockItem(-1, aType, a, isclosed);
                this->addToBlock(blockID, endBlockID, item);
        }
        //
    }


    /*

    qint64 blockId = 0;
    QDateTime epoch = QDateTime::fromSecsSinceEpoch(0);
    QElapsedTimer timer;
    timer.start();

    while(epoch < agenda->agendaStop){
        blockId++;
        epoch = epoch.addSecs(15*60);
        if(epoch >= agenda->agendaStart){
            int Weekday = epoch.date().dayOfWeek();
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
                this->agenda->agendaBlocks.push_back(new AgendaBlock(blockId,epoch, epoch.addSecs(15*60), isPlanbaar, isWorkingDay, false));
        }
    }

   // time to load data from apointments and tasks
    this->agenda->dayModel()->LoadData(this->agenda);


    qDebug() << "The slow operation took" << timer.elapsed() << "milliseconds";
    qDebug() << "The slow operation took" << timer.nsecsElapsed() << "nanoseconds";
*/

   // emit this->finished();
    this->wait_for_loading = false;
}

void AgendaLoader::CreateBlocks(QDateTime StartDate, qint64 startblockindex,QDateTime startblockDate, QDateTime lastPlannedObject){
    while(startblockDate > StartDate){
        startblockDate = startblockDate.addSecs(-AGENDABLOCKDURATION);
        startblockindex = startblockindex - 1;
        if(startblockindex <= 0){
                break;
        }
    }

    if(startblockindex == 0){
        startblockDate = QDateTime::fromSecsSinceEpoch(0);
    }

    while(startblockDate <= lastPlannedObject){
        if(startblockDate >= StartDate){
                int Weekday = startblockDate.date().dayOfWeek();
                bool isPlanbaar = false;
                bool isWorkingDay = false;
                switch(Weekday){
                case Qt::Monday:
                    if(agenda->settings->PlanMonday()){
                        isWorkingDay = true;
                        if((startblockDate.time() >= agenda->settings->MondayStart()) && (startblockDate.time() < agenda->settings->MondayEnd())){
                            isPlanbaar = true;
                        }
                    }
                    break;
                case Qt::Tuesday:

                    if(agenda->settings->planTuesday()){
                        isWorkingDay = true;
                        if((startblockDate.time() >= agenda->settings->TuesdayStart()) && (startblockDate.time() < agenda->settings->TuesdayEnd())){
                            isPlanbaar = true;
                        }
                    }
                    break;
                case Qt::Wednesday:
                    if(agenda->settings->planWednesDay()){
                        isWorkingDay = true;
                        if((startblockDate.time() >= agenda->settings->WednesdayStart()) && (startblockDate.time() < agenda->settings->WednesdayEnd())){
                            isPlanbaar = true;
                        }
                    }
                    break;
                case Qt::Thursday:
                    if(agenda->settings->planThursday()){
                        isWorkingDay = true;
                        if((startblockDate.time() >= agenda->settings->ThursdayStart()) && (startblockDate.time() < agenda->settings->ThursdayEnd())){
                            isPlanbaar = true;
                        }
                    }
                    break;
                case Qt::Friday:
                    if(agenda->settings->planFriday()){
                        isWorkingDay = true;
                        if((startblockDate.time() >= agenda->settings->FridayStart()) && (startblockDate.time() < agenda->settings->FridayEnd())){
                            isPlanbaar = true;
                        }
                    }
                    break;
                case Qt::Saturday:
                    if(agenda->settings->planSaturday()){
                        isWorkingDay = true;
                        if((startblockDate.time() >= agenda->settings->SaturdayStart()) && (startblockDate.time() < agenda->settings->SaturdayEnd())){
                            isPlanbaar = true;
                        }
                    }
                    break;
                case Qt::Sunday:
                    if(agenda->settings->planSunday()){
                        isWorkingDay = true;
                        if((startblockDate.time() >= agenda->settings->SundayStart()) && (startblockDate.time() < agenda->settings->SundayEnd())){
                            isPlanbaar = true;
                        }
                    }
                    break;
                }
                this->agenda->agendaBlocks.push_back(new AgendaBlock(startblockindex ,startblockDate, startblockDate.addSecs(15*60), isPlanbaar, isWorkingDay, false));
        }
        startblockindex++;
        startblockDate = startblockDate.addSecs(AGENDABLOCKDURATION);
    }

}

void AgendaLoader::addToBlock(qint64 blockID, qint64 endBlockID, AgendaBlockItem *item){


    for(int i = 0; i < this->agenda->agendaBlocks.size(); i++){
        if((this->agenda->agendaBlocks[i]->blockID >= blockID) && (this->agenda->agendaBlocks[i]->blockID <= endBlockID)){
                if(item->appointment == NULL){
                    int bp = 0;
                    bp++;
                }
                this->agenda->agendaBlocks[i]->AddBlockItem(item);
        }
        if(this->agenda->agendaBlocks[i]->blockID > endBlockID){
                break;
        }
    }

}

void AgendaLoader::SaveAgenda(){
    //wait for planner running
    m.lock();
    if(agenda->TMPYAgendaBlocks.size() > 0){
        qint64 tmpyStartIndex = agenda->TMPYAgendaBlocks[0]->blockID;
        for(int i = 0; i < this->agenda->agendaBlocks.size(); i++){
                if(this->agenda->agendaBlocks[i]->blockID >= tmpyStartIndex){
                    this->agenda->agendaBlocks[i]->deleteLater();
                    this->agenda->agendaBlocks.removeAt(i);
                    i = i - 1;
                }
        }
        //copying blocks from tmpy to agenda
        while(agenda->TMPYAgendaBlocks.size() > 0){
                this->agenda->agendaBlocks.push_back(agenda->TMPYAgendaBlocks[0]);
                agenda->TMPYAgendaBlocks.removeAt(0);
        }
    }

    for(int i = 0; i < agenda->agendaBlocks.size(); i++){
        for(int y = 0; y < agenda->agendaBlocks[i]->items.size(); y++){
                agenda->agendaBlocks[i]->items[y]->isSaved = false;
        }
    }

    /*
    QJsonObject obj;
    obj.insert("startBlockID", this->agenda->agendaBlocks[0]->blockID);
    DBRequest *request = new DBRequest(RequestTypes::DeleteAgendaItemsFromBlockID, obj);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(debug(QJsonObject)));
    this->agenda->db->AddRequest(request);
*/

    for(int i = 0; i < dataItems.size(); i++){
        dataItems[i]->setIsSaved(false);
    }

    for(int i = 0; i < agenda->agendaBlocks.size(); i++){
        for(int y = 0; y < agenda->agendaBlocks[i]->items.size(); y++){
                AgendaBlockItem *item = agenda->agendaBlocks[i]->items[y];
                if(item->isSaved == false){
                    int itemID = -1;
                    if((item->Type == appointmentType) && (item->appointment != NULL)){
                        qint64 startBlockID = agenda->agendaBlocks[i]->blockID;
                        qint64 endBlockId = this->getEndBlockID(i, appointmentType, item->appointment, item->isClosed);

                        //item->appointment->log()->AgendaPublish(agenda->agendaBlocks[i], this->getEndBlock(i, appointmentType, item->appointment, item->isClosed));

                        itemID = item->appointment->msid();
                        if(itemID >= 0){
                            bool found = false;
                            for(int z = 0; z < dataItems.size(); z++){
                                if(dataItems[z]->isSaved() == false){
                                found = dataItems[z]->checkSave(agenda->agendaBlocks[i]->blockID, endBlockId, (int)item->isClosed, item->Type, itemID);
                                if(found == true){
                                    break;
                                }
                                }
                            }

                            if(found == false){
                                qint64 startBlockID = agenda->agendaBlocks[i]->blockID;
                                qint64 endBlockId = this->getEndBlockID(i, appointmentType, item->appointment, item->isClosed);
                                QJsonObject obj;
                                obj.insert("blockMSID", -1);
                                obj.insert("blockID", agenda->agendaBlocks[i]->blockID);
                                obj.insert("endBlockID", endBlockId);
                                obj.insert("blockType", item->Type);
                                obj.insert("blockTypeID", itemID);
                                obj.insert("blockIsClosed", (int)item->isClosed);
                                obj.insert("lastEdit", QDateTime::currentDateTime().toSecsSinceEpoch());
                                obj.insert("blockStartTime", agenda->agendaBlocks[i]->m_startTime.toSecsSinceEpoch());
                                DBRequest *request = new DBRequest(RequestTypes::InsertAgendaItem, obj);

                                AgendaDataItem *dataItem = new AgendaDataItem(-1, agenda->agendaBlocks[i]->blockID,agenda->agendaBlocks[i]->m_startTime.toSecsSinceEpoch(), endBlockId, (int)item->isClosed, item->Type, itemID);

                                this->dataItems.push_back(dataItem);
                                //no connect hier
                                this->agenda->db->AddRequest(request);
                            }
                        }
                    }
                }
        }
    }

    for(int i = 0; i < dataItems.size(); i++){
        if(dataItems[i]->isSaved() == false){
                if(dataItems[i]->msid() > 0){
                    QJsonObject obj;
                    obj.insert("blockItemMSID", dataItems[i]->msid());
                    DBRequest *request = new DBRequest(RequestTypes::DeleteAgendaItem, obj);
                    connect(request, SIGNAL(finished(QJsonObject())), this, SLOT(dbgDelete(QJsonObject)));
                    this->agenda->db->AddRequest(request);
                }
                dataItems[i]->deleteLater();
                dataItems.erase(dataItems.begin() + i);
                i=i-1;
        }
    }

    m.unlock();
}

void AgendaLoader::dbgDelete(QJsonObject data){
    int bp = 0;
    bp++;
}

qint64 AgendaLoader::getEndBlockID(int startIndex, AgendaTypes type, Appointment *appointment, bool isClosed){
    qint64 oldBlockId = startIndex;
    for(int i = startIndex; i < agenda->agendaBlocks.size(); i++){
        bool found = false;
        for(int y = 0; y < agenda->agendaBlocks[i]->items.size(); y++){
                AgendaBlockItem *item = agenda->agendaBlocks[i]->items[y];
                if(item->Type == type){
                    if(type == appointmentType){
                        if((item->appointment == appointment) && (item->isClosed == isClosed)){
                            found = true;
                            item->isSaved = true;
                        }
                    }
                }
        }
        if(found == false){
                return oldBlockId;
        }
        oldBlockId = agenda->agendaBlocks[i]->blockID;
    }
    return 0;
}

AgendaBlock *AgendaLoader::getEndBlock(int startIndex, AgendaTypes type, Appointment *appointment, bool isClosed){
    //qint64 oldBlockId = startIndex;
    AgendaBlock *oldAgendaBlock = NULL;
    for(int i = startIndex; i < agenda->agendaBlocks.size(); i++){
        bool found = false;
        for(int y = 0; y < agenda->agendaBlocks[i]->items.size(); y++){
                AgendaBlockItem *item = agenda->agendaBlocks[i]->items[y];
                if(item->Type == type){
                    if(type == appointmentType){
                        if((item->appointment == appointment) && (item->isClosed == isClosed)){
                            found = true;
                            item->isSaved = true;
                        }
                    }
                }
        }

        if(found == false){
            return oldAgendaBlock;
        }

        oldAgendaBlock = agenda->agendaBlocks[i];
    }
    return NULL;
}

void AgendaLoader::RemoveAppointment(Appointment *app){
    m.lock();
    for(int i = 0; i < agenda->agendaBlocks.size(); i++){
        for(int y = 0; y < agenda->agendaBlocks[i]->items.size(); y++){
                if(agenda->agendaBlocks[i]->items[y]->Type == appointmentType){
                    if(agenda->agendaBlocks[i]->items[y]->appointment == app){
                        agenda->agendaBlocks[i]->items[y]->deleteLater();
                        agenda->agendaBlocks[i]->items.removeAt(y);
                        break;
                    }
                }
        }
    }
    m.unlock();
}

void AgendaLoader::RemoveAppointmentTimeFrame(Appointment *app, QDateTime start, QDateTime end){
    // this can only appear in active agenda
    m.lock();
    for(int i = 0; i < agenda->agendaBlocks.size(); i++){
        for(int y = 0; y < agenda->agendaBlocks[i]->items.size(); y++){
                if(agenda->agendaBlocks[i]->items[y]->Type == appointmentType){
                    if(agenda->agendaBlocks[i]->items[y]->appointment == app){
                        if((agenda->agendaBlocks[i]->m_startTime >= start) && (agenda->agendaBlocks[i]->m_endTime <= end)){
                            agenda->agendaBlocks[i]->items[y]->deleteLater();
                            agenda->agendaBlocks[i]->items.removeAt(y);
                            break;
                        }
                    }
                }
        }
    }
    m.unlock();
}

void AgendaLoader::SaveAppointmentTimeFrame(Appointment *app, QDateTime start, QDateTime end, bool isClosed){
    m.lock();
    for(int i = 0; i < agenda->agendaBlocks.size(); i++){
        AgendaBlock *block = agenda->agendaBlocks[i];
        if((block->m_startTime >= start) && (block->m_endTime <= end)){
                AgendaBlockItem *item = new AgendaBlockItem(-1, appointmentType, app, isClosed);
                block->items.push_back(item);
                if((block->items.size() > 1) && (isClosed == true)){
                    // clear unclosed blocks;
                    for(int y = 0; y < block->items.size(); y++){
                        if(block->items[y]->isClosed == false){
                            block->items.erase(block->items.begin() + y);
                            y = y - 1;
                        }
                    }
                }
        }
        if(block->m_startTime > end){
                break;
        }
    }
    m.unlock();


}

void AgendaLoader::FixeDoubleItems(){
    for(int i = 0; i < this->agenda->agendaBlocks.size(); i++){
        AgendaBlock *block = this->agenda->agendaBlocks[i];
        for(int y = 0; y < block->items.size(); y++){
                Appointment *app = block->items[y]->appointment;

                bool closed = block->items[y]->isClosed;
                for(int z = y+1; z < block->items.size(); z++){
                    if(block->items[z]->appointment == app){
                        if(block->items[z]->isClosed){
                            closed = true;
                        }
                       // delete block->items[z];
                        block->items.erase(block->items.begin()+z);
                        z = z - 1;

                    }
                }

                block->items[y]->isClosed = closed;

        }
    }
}

void AgendaLoader::CloseAppointment(Appointment *app){
    m.lock();

    for(int i = 0; i < agenda->agendaBlocks.size(); i++){
        if(agenda->agendaBlocks[i]->m_startTime > app->EndDate()){
                break;
        }
        for(int y = 0; y < agenda->agendaBlocks[i]->items.size(); y++){
                AgendaBlockItem *item = agenda->agendaBlocks[i]->items[y];
                if(item->Type == appointmentType){
                    if(item->appointment == app){
                        if(item->isClosed == false){
                            agenda->agendaBlocks[i]->items[y]->deleteLater();
                            agenda->agendaBlocks[i]->items.erase(agenda->agendaBlocks[i]->items.begin() + y);
                        }
                        //item->isClosed = true;
                    }
                }
        }
    }


    m.unlock();
}
