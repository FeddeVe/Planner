#include "agenda.h"

Agenda::Agenda(UserSettings *settings,Appointments *appointments, Buckets *buckets, DBManager *db, MSGraph *graph, QObject *parent)
    : QObject{parent}
{
    this->m_planMode = 1; // v2
    this->db = db;
    this->appointments = appointments;
    this->settings = settings;
    this->m_dayModel = new AgendaDayItemModel();
    this->m_tmpyActive = false;
    this->buckets = buckets;
    this->planner = new AgendaPlanner(this, appointments, buckets);
    this->graph = graph;
    this->wta = new AgendaWTA();

    this->m_error = new AgendaErrorModel();

    this->plannerThread = new QThread();
    this->planner->moveToThread(plannerThread);
    connect(plannerThread, SIGNAL(started()), planner, SLOT(process()));
    connect(planner, SIGNAL(finished()), plannerThread, SLOT(quit()));
    connect(planner, SIGNAL(finished()), this, SLOT(plannerFinished()));
    //connect(planner, SIGNAL(finished()), planner, SLOT(deleteLater()));
    //connect(plannerThread, SIGNAL(finished()), plannerThread, SLOT(deleteLater()));

    this->m_capmodel = new CapacityModel(this);
    this->m_capLoader = new CapacityLoader(m_capmodel);
    this->capacityThread = new QThread();
    this->m_capLoader->moveToThread(this->capacityThread);
    connect(capacityThread, SIGNAL(started()), m_capLoader, SLOT(process()));
    connect(m_capLoader, SIGNAL(finished()), capacityThread, SLOT(quit()));
    //connect(planner, SIGNAL(finished()), this, SLOT(plannerFinished()));

    //this->LoadBlocks(QDateTime::currentDateTime().addMonths(-7), QDateTime::currentDateTime().addMonths(7));
    this->agendaStart = QDateTime::currentDateTime().addMonths(-13);
    this->agendaStop = QDateTime::currentDateTime().addMonths(13);
    this->loader = new AgendaLoader(this, appointments);
    this->loaderThread = new QThread();
    connect(loaderThread, SIGNAL(started()), loader, SLOT(process()));
    connect(loader, SIGNAL(finished()), loaderThread, SLOT(quit()));
    connect(loader, SIGNAL(finished()), this, SLOT(loaderFinished()));
    connect(loader, SIGNAL(isLoaderRunning(bool)), this, SLOT(loaderStatus(bool)));
  //  connect(loader, SIGNAL(finished()), loader, SLOT(deleteLater()));
  //  connect(loaderThread, SIGNAL(finished()), loaderThread, SLOT(deleteLater()));
    this->m_agendaLoading = true;

    this->m_plannerRunning = false;
   // this->loadAgenda();

    if(this->m_planMode == 1){
        this->loader->Run();
    }else{

   // this->NewAgendaBlocks = new AgendaBlocks(this);
   //     this->setAgendaLoading(false);
   }

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

void Agenda::loaderStatus(bool busy){
    this->setAgendaLoading(busy);
    emit this->tmpyActiveChanged();

}

void Agenda::loadAgenda(){
    this->loader->AddAction(LoaderType::agenda_Load);

}

void Agenda::plannerFinished(){


}

void Agenda::loaderFinished(){

}

void Agenda::planAgenda(){
    this->loader->AddAction(LoaderType::agenda_Plan);
}

void Agenda::exportAgenda(){
    this->loader->AddAction(LoaderType::agenda_Export);
}

AgendaDayItemModel *Agenda::dayModel() const{
    return m_dayModel;
}


bool Agenda::tmpyActive() const
{
    if(TMPYAgendaBlocks.size() > 0){
        return true;
    }
    return false;

}

void Agenda::setTmpyActive(bool newTmpyActive)
{
    if (m_tmpyActive == newTmpyActive)
        return;
    m_tmpyActive = newTmpyActive;
    emit tmpyActiveChanged();
}

bool Agenda::plannerRunning() const
{
    return this->planner->running();
}

void Agenda::setPlannerRunning(bool newPlannerRunning)
{
    if (m_plannerRunning == newPlannerRunning)
        return;
    m_plannerRunning = newPlannerRunning;
    emit plannerRunningChanged();
}

void Agenda::LoadBlocks(QDateTime start, QDateTime end){

}

bool Agenda::agendaLoading() const
{
    return m_agendaLoading;
}

void Agenda::setAgendaLoading(bool newAgendaLoading)
{
    if (m_agendaLoading == newAgendaLoading)
        return;
    m_agendaLoading = newAgendaLoading;
    emit agendaLoadingChanged();
}


int Agenda::agendaIndex(){
    /*
    //if(this->tmpyActive()){
        for(int i = 0; i < appointments->list.size(); i++){
            if(appointments->list[i]->inEditMode()){
            int index = this->m_dayModel->indexAt(appointments->list[i]->EndDate());
                return index;
            }
        }
         // code for tasks
*/
    int a = this->m_dayModel->indexAt(m_dayModel->curIndex);
    return a;




}


CapacityModel *Agenda::capModel(){
        return this->m_capmodel;
}

void Agenda::saveAgenda(){
        this->loader->AddAction(LoaderType::agenda_PlanAndSave);

}

/*
qint64 Agenda::getEndBlockID(int startIndex, AgendaTypes type, Appointment *appointment, bool isClosed){
        qint64 oldBlockId = startIndex;
        for(int i = startIndex; i < agendaBlocks.size(); i++){
        bool found = false;
        for(int y = 0; y < agendaBlocks[i]->items.size(); y++){
            AgendaBlockItem *item = agendaBlocks[i]->items[y];
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
        oldBlockId = agendaBlocks[i]->blockID;
        }

        return 0;
}
*/

void Agenda::CheckErrors(){
        m_error->LoadData(this);
}

void Agenda::clearTmpyAgenda(){
        m.lock();
        for(int i = 0; i < this->TMPYAgendaBlocks.size(); i++){
            delete this->TMPYAgendaBlocks[i];
        }
        this->TMPYAgendaBlocks.clear();
        this->TMPYAgendaBlocks.shrink_to_fit();
        this->capModel()->Process(false);
        this->m_dayModel->LoadData(this);
        this->m_error->LoadData(this);
        this->appointments->CheckErrors();
        emit this->tmpyActiveChanged();
        m.unlock();
}

void Agenda::appointmentDeleted(Appointment *app){
       this->loader->AddAction(LoaderType::appointment_Delete, app);
}

void Agenda::removeAppointmentBlock(Appointment *app, QDateTime startTime, QDateTime endTime){
        this->loader->AddAction(LoaderType::appointment_DeleteTimeFrame, app, startTime, endTime);
}

void Agenda::saveAppointmentBlock(Appointment *app, QDateTime start, QDateTime end, bool isClosed){
        this->loader->AddAction(LoaderType::appointment_SaveTimeFrame, app, start, end, isClosed);
}

void Agenda::closeAppointment(Appointment *app){
        this->loader->AddAction(LoaderType::appointment_Close, app);
}

int Agenda::agendaIndexAt(QString date){
        QDateTime a = QDateTime::fromString(date, "dd/MM/yyyy");
        if(!a.isValid()){
            return m_dayModel->indexAt(QDateTime::currentDateTime());
        }
        return m_dayModel->indexAt(a);
}

void Agenda::debug(QJsonObject msg){
        int bp = 0;
        bp++;
}

AgendaErrorModel *Agenda::errModel(){
        return this->m_error;
}


int Agenda::planMode() const
{
        return m_planMode;
}

void Agenda::setPlanMode(bool newPlanMode)
{
        if (m_planMode == newPlanMode)
            return;
        m_planMode = newPlanMode;
        emit planModeChanged();
}

AgendaWTA *Agenda::wtaModel(){
        return this->wta;
}
