#include "appointment.h"


Appointment::Appointment(Appointments *appointmenst, Jobs *jobs, DBManager *db, int m_msid, QString m_title,int m_jobID, QDateTime StartDate,int Duration,
                         QDateTime endDate, bool m_isClosed, bool m_blockRest,
                         bool m_planRest,int m_typeIndex,bool m_calcTime,QString m_description, int m_planMode,
                         int BucketID, int BucketItemID, QDateTime workingOnStartDate, bool isAttached, bool isDeleted, QObject *parent)
    : QObject{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    this->jobs = jobs;
    this->db = db;
    this->appointments = appointmenst;
    this->m_msid = m_msid;
    this->m_title = m_title;
    this->m_jobID = m_jobID;
    this->m_job = this->jobs->job(m_jobID);
    this->m_startDate = StartDate;
    this->m_duration = Duration;
    this->m_endDate = endDate;
    if(endDate < QDateTime::currentDateTime()){
        this->m_isPast = true;
    }else{
        this->m_isPast = false;
    }
    this->m_isClosed = m_isClosed;
    this->m_blockRest = m_blockRest;
    this->m_planRest = m_planRest;
    this->m_type = appointments->get_type(m_typeIndex);
    this->m_calcTime = m_calcTime;
    this->m_description = m_description;
    this->m_planMode = m_planMode;
    this->m_isAttached = isAttached;
    this->m_deleted = isDeleted;
    this->m_rePlanningNeeded = false;
    this->m_inEditMode = false;
    this->m_savingInProgress = false;
    this->m_repeatMode = 0;
    this->m_repeatCount = 0;
    this->m_saveispartofmulti = false;
    this->m_bucketID = BucketID;
    this->m_BucketItemID = BucketItemID;
    this->m_workingOnStartDate = workingOnStartDate;

    this->planner = new AppointmentPlanner(this, appointmenst->agenda);
    connect(this->appointments->agenda, SIGNAL(AgendaLoaded()), this, SLOT(AfterAgendaLoaded()));



    if(m_isAttached == false){
        this->BeforeBlock = new Appointment(this->appointments, this->jobs, this->db, -2, "Planner Block for "+ m_title, m_jobID, QDateTime::currentDateTime(), 0, QDateTime::currentDateTime(), false, false, false, this->appointments->types()->GetBlockIndex(), false, "Block for "+ m_title,PlanModes::Fixed, -1, -1, QDateTime::fromSecsSinceEpoch(0), true,true);
        appointments->AddAppointment(BeforeBlock);
        this->AfterBlock = new Appointment(this->appointments, this->jobs, this->db, -3, "Planner Block for "+ m_title, m_jobID, QDateTime::currentDateTime(), 0, QDateTime::currentDateTime(), false, false, false, this->appointments->types()->GetBlockIndex(), false, "Block for "+ m_title,PlanModes::Fixed, -1, -1, QDateTime::fromSecsSinceEpoch(0), true, true);
        appointments->AddAppointment(AfterBlock);
        this->RestBlock = new Appointment(this->appointments, this->jobs, this->db, -4, "Rest after "+ m_title, m_jobID, QDateTime::currentDateTime(), 0, QDateTime::currentDateTime(), false, false, false, this->appointments->types()->GetBlockIndex(), false, "Block for "+ m_title,PlanModes::Fixed, -1, -1, QDateTime::fromSecsSinceEpoch(0), true, true);
        appointments->AddAppointment(RestBlock);
        this->planner->DoMagic();
        this->UpdateAttached();
    }
}



int Appointment::msid() const
{
   // //QMutexLocker locker (&_listMutex);
    return m_msid;
}

void Appointment::setmsid(int newMsid)
{
   //QMutexLocker locker (&m);
    if (m_msid == newMsid)
        return;
    m_msid = newMsid;
  //  m_log->AppointmentIDChanged();
    emit msidChanged();
}

QString Appointment::title() const
{
   // //QMutexLocker locker (&_listMutex);
    return m_title;
}

void Appointment::setTitle(const QString &newTitle)
{
    //QMutexLocker locker (&m);
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    if(this->RestBlock != NULL){
    this->RestBlock->setTitle("Rest After "+ newTitle);
    }
    if(this->BeforeBlock != NULL){
    this->BeforeBlock->setTitle("Planner Blok voor "+ newTitle);
    }
    if(this->AfterBlock != NULL){
    this->AfterBlock->setTitle("Planner Blok voor "+ newTitle);
    }
  //  this->save(0,0);
    emit titleChanged();
}

int Appointment::jobID() const
{
   // //QMutexLocker locker (&_listMutex);

    return m_jobID;
}

void Appointment::setJobID(int newJobID)
{
    //QMutexLocker locker (&m);
    if(this->m_jobID == newJobID){
        return;
    }
    this->m_jobID = newJobID;
    this->m_job = jobs->job(newJobID);
    if(this->m_jobID == -1){
        this->m_job = this->jobs->CreateJob();
    }
    emit jobIDChanged();
    emit jobNoChanged();
    emit jobTitleChanged();
    emit jobClientChanged();
}

QString Appointment::startDate() const
{
   // //QMutexLocker locker (&_listMutex);
    return m_startDate.toString("dd-MM-yyyy HH:mm");
}

QDateTime Appointment::StartDate() const{
   // //QMutexLocker locker (&_listMutex);
    return m_startDate;
}

void Appointment::setStartDate(const QString &newStartDate)
{
    //QMutexLocker locker (&m);
    QDateTime a = QDateTime::fromString(newStartDate, "dd-MM-yyyy HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_startDate == a)
        return;
    m_startDate = a;

    if(m_planMode == PlanModes::Fixed){
        m_endDate = a.addSecs(m_duration);
        emit this->endDateChanged();
    }

    this->checkDateErrors();
    this->UpdateAttached();
    //int index = this->appointments->agenda->agendaIndexAt(newStartDate);
    if(this->m_planMode == 0){
    this->appointments->agenda->dayModel()->setIndexAt(newStartDate);
    }
     emit startDateChanged();
    if(this->m_duration >0){
        //this->plan();
    }

}

void Appointment::SetStartDate(const QDateTime a){
    if (m_startDate == a)
        return;
    m_startDate = a;

    if(m_planMode == PlanModes::Fixed){
        m_endDate = a.addSecs(m_duration);
        emit this->endDateChanged();
    }

    this->checkDateErrors();
    this->UpdateAttached();
    emit startDateChanged();
    //this->plan();
}

QString Appointment::duration() const
{
  //  //QMutexLocker locker (&_listMutex);

    QString ret = durationToString(m_duration);
    return ret;
}

int Appointment::Duration()const{
   // //QMutexLocker locker (&_listMutex);
    return m_duration;
}

void Appointment::setDuration(const QString &newDuration)
{

    //QMutexLocker locker (&m);
    int duration = durationFromString(newDuration);
    if (m_duration == duration)
        return;
    if(m_planMode == PlanModes::Fixed){
         m_endDate = m_startDate.addSecs(duration);
        emit this->endDateChanged();
    }
    m_duration = duration;
    this->planner->DoMagic();
    this->checkDateErrors();
     this->UpdateAttached();
     emit durationChanged();
     if(this->m_duration >0){
        //this->plan();
     }

}

QString Appointment::endDate() const
{
    ////QMutexLocker locker (&_listMutex);
    return m_endDate.toString("dd-MM-yyyy HH:mm");
}

QDateTime Appointment::EndDate() const{
   // //QMutexLocker locker (&_listMutex);
    return m_endDate;
}

void Appointment::setEndDate(const QString &newEndDate)
{
    //QMutexLocker locker (&m);
    QDateTime a = QDateTime::fromString(newEndDate, "dd-MM-yyyy HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_endDate == a)
        return;

    m_endDate = a;
    this->checkDateErrors();
    this->UpdateAttached();
    if(this->m_planMode > 0){
        this->appointments->agenda->dayModel()->setIndexAt(newEndDate);
    }
     emit endDateChanged();
    //this->plan();

}

void Appointment::SetEndDate(const QDateTime a)
{
    //QMutexLocker locker (&m);

    if (m_endDate == a)
        return;

    m_endDate = a;
    this->checkDateErrors();
    this->UpdateAttached();
    emit endDateChanged();
   // //this->plan();

}

bool Appointment::isPlanned() const
{
   // //QMutexLocker locker (&_listMutex);
    return false;
   // return m_isPlanned;
}

void Appointment::setIsPlanned(bool newIsPlanned)
{
    //QMutexLocker locker (&m);
    /*
    if (m_isPlanned == newIsPlanned)
        return;
    m_isPlanned = newIsPlanned;
    emit isPlannedChanged();
    */
}

bool Appointment::isPast() const
{
  //  //QMutexLocker locker (&_listMutex);
    return m_isPast;
}

void Appointment::setIsPast(bool newIsPast)
{
   //QMutexLocker locker (&m);
    if (m_isPast == newIsPast)
        return;
    m_isPast = newIsPast;
    emit isPastChanged();
}

bool Appointment::isClosed() const
{
   // //QMutexLocker locker (&_listMutex);
    return m_isClosed;
}

void Appointment::setIsClosed(bool newIsClosed)
{
   //QMutexLocker locker (&m);
    if (m_isClosed == newIsClosed)
        return;
    m_isClosed = newIsClosed;
    emit isClosedChanged();
}

bool Appointment::blockRest() const
{
   // //QMutexLocker locker (&_listMutex);
    return m_blockRest;
}

void Appointment::setBlockRest(bool newBlockRest)
{
    //QMutexLocker locker (&m);
    if (m_blockRest == newBlockRest)
        return;
    m_blockRest = newBlockRest;
     this->setRePlanningNeeded(true);
    emit blockRestChanged();
}

bool Appointment::planRest() const
{
   // //QMutexLocker locker (&_listMutex);
    return m_planRest;
}

void Appointment::setPlanRest(bool newPlanRest)
{
   //QMutexLocker locker (&m);
    if (m_planRest == newPlanRest)
        return;
    m_planRest = newPlanRest;
     this->setRePlanningNeeded(true);
    this->UpdateAttached();
    emit planRestChanged();
}

int Appointment::typeIndex() const
{
   // //QMutexLocker locker (&_listMutex);
    //return m_typeIndex;
    if(this->m_type != NULL){
        return this->appointments->appointmenttypes->GetIndex(this->m_type);
    }
    return 0;
}

void Appointment::setTypeIndex(int newTypeIndex)
{
   //QMutexLocker locker (&m);
    /*
    if (m_typeIndex == newTypeIndex)
        return;
    m_typeIndex = newTypeIndex;
    emit typeIndexChanged();
*/
    if(this->m_type != NULL){
        if(this->m_type->index() == newTypeIndex){
            return;
        }
    }
    this->m_type = this->appointments->types()->get(newTypeIndex);
  //  this->m_type = this->appointments->get_type(newTypeIndex);
    emit this->typeIndexChanged();
    emit this->boxclrChanged();
    emit this->clrChanged();
    emit this->typeNameChanged();
    if(this->m_type != NULL){

       this->setCalcTime(m_type->calcTime());
    }
  //this->plan();
}

QString Appointment::clr() const
{
   // //QMutexLocker locker (&_listMutex);
    if(this->m_type == NULL){
        return "#FFFFFF";
    }
    return m_type->clr();
}

void Appointment::setClr(const QString &newClr)
{
    //QMutexLocker locker (&m);

}

bool Appointment::calcTime() const
{
  //  //QMutexLocker locker (&_listMutex);
    return m_calcTime;
}

void Appointment::setCalcTime(bool newCalcTime)
{
 //QMutexLocker locker (&m);
    if (m_calcTime == newCalcTime)
        return;
    m_calcTime = newCalcTime;
    appointments->agenda->planAgenda();
     this->setRePlanningNeeded(true);
    emit calcTimeChanged();
     //this->plan();
}


QString Appointment::description() const
{
   // //QMutexLocker locker (&_listMutex);
    return m_description;
}

void Appointment::setDescription(const QString &newDescription)
{
  //QMutexLocker locker (&m);
    if (m_description == newDescription)
        return;
    if(this->BeforeBlock != NULL){
        this->BeforeBlock->setDescription(newDescription);
    }
    if(this->AfterBlock != NULL){
        this->AfterBlock->setDescription(newDescription);

    }
    if(this->RestBlock != NULL){
        this->RestBlock->setDescription(newDescription);
    }
    m_description = newDescription;
    emit descriptionChanged();
}



int Appointment::planMode() const
{
   // //QMutexLocker locker (&_listMutex);
    return m_planMode;
}

void Appointment::setPlanMode(int newPlanMode)
{
   //QMutexLocker locker (&m);
    if (m_planMode == newPlanMode)
        return;
    m_planMode = newPlanMode;
    if(newPlanMode > 0){
        this->SetStartDate(QDateTime::currentDateTime());
    }
     this->setRePlanningNeeded(true);
    emit planModeChanged();
    //this->plan();
}

Job *Appointment::job(){
  //  //QMutexLocker locker (&_listMutex);
    return this->m_job;
}

QString Appointment::jobNo() const
{
  //  //QMutexLocker locker (&_listMutex);
    if(m_job == NULL){
        return "";
    }
    return m_job->no();
}

void Appointment::setJobNo(const QString &newJobNo)
{

    if(m_job == NULL){
        return;
    }
    if(m_job->msid() != -1){
        return;
    }
   //QMutexLocker locker (&m);
    if (m_job->no() == newJobNo)
        return;
    m_job->setno(newJobNo);
    emit jobNoChanged();
}

QString Appointment::jobTitle() const
{
  //  //QMutexLocker locker (&_listMutex);
    if(m_job == NULL){
        return "";
    }
    return m_job->title();
}

void Appointment::setJobTitle(const QString &newJobTitle)
{
   //QMutexLocker locker (&m);
    if(m_job == NULL){
        return;
    }
    if (m_job->title() == newJobTitle)
        return;
    m_job->settitle(newJobTitle);
    emit jobTitleChanged();
}

QString Appointment::jobClient() const
{
  //  //QMutexLocker locker (&_listMutex);
    if(m_job == NULL){
        return "";
    }
    return m_job->client();
}

void Appointment::setJobClient(const QString &newJobClient)
{
   //QMutexLocker locker (&m);
    if(this->m_job == NULL){
        return;
    }
    if (m_job->client() == newJobClient)
        return;
    m_job->setclient(newJobClient);
    emit jobClientChanged();
}

bool Appointment::inEditMode() const
{
  //  //QMutexLocker locker (&_listMutex);
    return m_inEditMode;
}

void Appointment::setInEditMode(bool newInEditMode)
{
   //QMutexLocker locker (&m);
    if (m_inEditMode == newInEditMode)
        return;
    m_inEditMode = newInEditMode;
    if(m_inEditMode){
        this->originValues.m_title = m_title;
        this->originValues.jobID = m_jobID;
        this->originValues.m_startDate = m_startDate;
        this->originValues.m_duration = m_duration;
        this->originValues.m_endDate = m_endDate;
        this->originValues.m_isPast = m_isPast;
        this->originValues.m_isClosed = m_isClosed;
        this->originValues.m_blockRest = m_blockRest;
        this->originValues.m_planRest = m_planRest;
        this->originValues.m_type = m_type;
        this->originValues.m_calcTime = m_calcTime;
        this->originValues.m_planMode = m_planMode;
        this->originValues.m_deleted = m_deleted;
    }

    emit inEditModeChanged();
}

bool Appointment::deleted() const
{
  //  //QMutexLocker locker (&_listMutex);
    return m_deleted;
}

void Appointment::setDeleted(bool newDeleted)
{
    //QMutexLocker locker (&m);
    if (m_deleted == newDeleted)
        return;
    m_deleted = newDeleted;
   //this->plan();
    emit deletedChanged();
}





QString Appointment::boxclr() const
{
   // //QMutexLocker locker (&_listMutex);
    if(this->m_type == NULL){
        return "#AAFFFFFF";
    }
    return this->m_type->boxclr();
}

void Appointment::setBoxclr(const QString &newBoxclr)
{
     //QMutexLocker locker (&m);

}

QString Appointment::type() const
{
   // //QMutexLocker locker (&_listMutex);
    return m_type->label();
}



QString Appointment::dateErrors() const
{

    return m_dateErrors;
}

void Appointment::setDateErrors(const QString &newDateErrors)
{
////QMutexLocker locker (&m);
    if (m_dateErrors == newDateErrors)
        return;
    m_dateErrors = newDateErrors;
    emit dateErrorsChanged();
}

void Appointment::checkDateErrors(){
    QString err = "\n";
    if(m_startDate < QDateTime::currentDateTime()){
        err += "Start datum is in het verleden, planning kijkt alleen vooruit, check planning met werkelijkheid! \n";
    }
    if(m_endDate < m_startDate){
        err += "Eind datum is kleiner dan startdatum. \n";
    }

    this->setDateErrors(err);
}

bool Appointment::isAttached() const
{
    return m_isAttached;
}

void Appointment::SetDuration(const int &duration){
    if(this->m_duration == duration){
        return;
    }
    this->m_duration = duration;
    emit this->durationChanged();
}

void Appointment::setIsAttached(bool newIsAttached)
{
//QMutexLocker locker (&m);
    if (m_isAttached == newIsAttached)
        return;
    m_isAttached = newIsAttached;
    emit isAttachedChanged();
}

void Appointment::UpdateAttached(){

    if(RestBlock != NULL){
    if(m_planRest){
        RestBlock->setDeleted(false);
        RestBlock->setStartDate(this->endDate());
        RestBlock->setDuration("10:00");
    }else{
        RestBlock->setDeleted(true);
    }
    }
    if(BeforeBlock != NULL){
        BeforeBlock->setDeleted(true);
        if(m_blockRest){
            QTime StartTime = this->m_startDate.time();
            //check if workingday
            if(this->appointments->agenda->settings->isWorkingDay(m_startDate)){
                QTime WorkingDayStartTime = this->appointments->agenda->settings->getStartTime(m_startDate);
                QTime WorkingDayEndTime = this->appointments->agenda->settings->getEndTime(m_startDate);
                if(StartTime > WorkingDayStartTime){
                    QDateTime beforeStart = m_startDate;
                    beforeStart.setTime(WorkingDayStartTime);
                    QDateTime beforeEnd = m_startDate;
                    if(StartTime > WorkingDayEndTime){
                        beforeEnd.setTime(WorkingDayEndTime);
                    }
                    BeforeBlock->setDeleted(false);
                    BeforeBlock->SetStartDate(beforeStart);
                    BeforeBlock->SetDuration(beforeStart.secsTo(beforeEnd));
                    BeforeBlock->SetEndDate(beforeEnd);
                }
        }
    }
  }

    if(AfterBlock != NULL){
        AfterBlock->setDeleted(true);
    if(m_blockRest){
        QDateTime jobEndTime = m_endDate;
        if((m_planRest) && (RestBlock != NULL)){
            jobEndTime = RestBlock->EndDate();
        }
        if(this->appointments->agenda->settings->isWorkingDay(jobEndTime)){
            QTime WorkingDayStartTime = this->appointments->agenda->settings->getStartTime(jobEndTime);
            QTime WorkingDayEndTime = this->appointments->agenda->settings->getEndTime(jobEndTime);
            if(jobEndTime.time() < WorkingDayEndTime){
                QDateTime afterStart = jobEndTime;
                QDateTime afterEnd = jobEndTime;
                afterEnd.setTime(WorkingDayEndTime);
                if(jobEndTime.time() <= WorkingDayStartTime){
                    afterStart.setTime(WorkingDayStartTime);
                }
                AfterBlock->setDeleted(false);
                AfterBlock->SetStartDate(afterStart);
                AfterBlock->SetDuration(afterStart.secsTo(afterEnd));
                AfterBlock->SetEndDate(afterEnd);
            }
        }
    }
  }

}

bool Appointment::rePlanningNeeded() const
{
    return m_rePlanningNeeded;
}

void Appointment::setRePlanningNeeded(bool newRePlanningNeeded)
{

    if (m_rePlanningNeeded == newRePlanningNeeded)
    return;
    m_rePlanningNeeded = newRePlanningNeeded;
    emit rePlanningNeededChanged();
}

void Appointment::plan(){
    if(m_isAttached){
        return;
    }
  //  qApp->processEvents();
    this->UpdateAttached();
    if(this->appointments != NULL){
    appointments->SortList();
  //  this->setRePlanningNeeded(false);
    }else{
    int bp = 0;
    bp++;
    }
}

QString Appointment::typeName() const
{
    if(this->m_type != NULL){
        return this->m_type->label();
    }
    return "";
}

void Appointment::AfterAgendaLoaded(){
    this->planner->DoMagic();
}

AppointmentPlanner *Appointment::appPlanner(){
    return this->planner;
}

int Appointment::durationLeft() const
{
    if(m_isClosed){
        return 0;
    }
   // if(m_durationLeft < 0){
   //     return 0;
   // }

    return this->planner->m_DurationLeft;
    //return m_durationLeft;
}

void Appointment::setDurationLeft(int newDurationLeft)
{
    if (m_durationLeft == newDurationLeft)
    return;
    m_durationLeft = newDurationLeft;
    emit durationLeftChanged();
}

void Appointment::cancelEdit(){
    if(this->jobID() == -1){
        //delete unsaved job
        jobs->removeJob(this->m_job);
    }
    if(this->m_msid == -1){
        //delete this job
        appointments->removeAppointment(this);

    }else{


    this->setTitle(this->originValues.m_title);
    this->setJobID(this->originValues.jobID);
    this->SetStartDate(this->originValues.m_startDate);
    this->setDuration(durationToString(this->originValues.m_duration));
    this->SetEndDate(this->originValues.m_endDate);
    this->setIsPast(this->originValues.m_isPast);
    this->setIsClosed(this->originValues.m_isClosed);
    this->setBlockRest(this->originValues.m_blockRest);
    this->setPlanRest(this->originValues.m_planRest);
    if(this->originValues.m_type != NULL){
        this->setTypeIndex(this->originValues.m_type->index());
    }
    this->setCalcTime(this->originValues.m_calcTime);
    this->setPlanMode(this->originValues.m_planMode);
    }

    this->appointments->agenda->clearTmpyAgenda();
    //Setting values back to original
    int bp = 0;
    bp++;
}

void Appointment::del(){
    if(this->jobID() == -1){
    //delete unsaved job
    jobs->removeJob(this->m_job);
    }

    //delete this job
    appointments->removeAppointment(this);
    //this->appointments->agenda->clearTmpyAgenda();
    this->appointments->agenda->appointmentDeleted(this);
    //this->appointments->agenda->saveAgenda();
    //Setting values back to original
    int bp = 0;
    bp++;
}

void Appointment::save(int repeatMode, int repeatCount, bool ispartofmulti){
    this->setSavingInProgress(true);
    this->m_saveispartofmulti = ispartofmulti;
    this->m_repeatMode = repeatMode;
    this->m_repeatCount = repeatCount;

    if((this->jobID() == -1) && (this->m_job != NULL)){
        QJsonObject obj;
        obj.insert("msid", this->m_job->msid());
        obj.insert("lastEdit", QDateTime::currentSecsSinceEpoch());
        obj.insert("jobNo", this->m_job->no());
        obj.insert("jobTitle", this->m_job->title());
        obj.insert("jobClient", this->m_job->client());
        obj.insert("jobDate", 0);
        obj.insert("jobStartDate", 0);
        obj.insert("jobPickDate", 0);
        DBRequest *request = new DBRequest(RequestTypes::UpdateJob, obj);
        connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(afterSaveJob(QJsonObject)));
        this->db->AddRequest(request);
    }else{
        QJsonObject obj;
        obj.insert("msg", "OK");
        this->afterSaveJob(obj);
    }

    /*
    QJsonObject obj;
    obj.insert("appointmentID", msid());
    obj.insert("appointmentTitle", title());
    obj.insert("appointmentJobID", this->jobID());
    obj.insert("appointmentStartDate", this->m_startDate.toSecsSinceEpoch());
    obj.insert("appointmentDuration", this->m_duration);
    obj.insert("appointmentEndDate", this->m_endDate.toSecsSinceEpoch());
    obj.insert("appointmentBlockRest", (int)this->m_blockRest);
    obj.insert("appointmentPlanRest", (int)this->m_planRest);
    obj.insert("appointmentType", this->typeIndex());
    obj.insert("appointmentCalcTime", (int)this->m_calcTime);
    obj.insert("appointmentDescription", this->m_description);
    obj.insert("appointmentLastEdit", QDateTime::currentDateTime().toSecsSinceEpoch());
    DBRequest *request = new DBRequest(RequestTypes::SaveAppoinment, obj);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(afterSave(QJsonObject)));
    this->db->AddRequest(request);
*/
}

void Appointment::afterSaveJob(QJsonObject msg){
    int bp = 0;
    bp++;
    if(msg.value("msg").toString() == "OK"){
        if(this->m_job != NULL){
            int msid = msg.value("id").toInt();
            if((this->m_job->msid() == -1) && (msid > 0)){
                this->m_job->setmsid(msid);
                this->m_jobID = msid;
            }
        }

        QJsonObject obj;
        obj.insert("appointmentID", msid());
        obj.insert("appointmentTitle", title());
        obj.insert("appointmentJobID", this->jobID());
        obj.insert("appointmentStartDate", this->m_startDate.toSecsSinceEpoch());
        obj.insert("appointmentDuration", this->m_duration);
        obj.insert("appointmentEndDate", this->m_endDate.toSecsSinceEpoch());
        obj.insert("appointmentBlockRest", (int)this->m_blockRest);
        obj.insert("appointmentPlanRest", (int)this->m_planRest);
        if(this->m_type != NULL){
            obj.insert("appointmentType", m_type->index());
        }else{
         obj.insert("appointmentType", 0);
        }
        obj.insert("appointmentCalcTime", (int)this->m_calcTime);
        obj.insert("appointmentPlanMode", this->m_planMode);
        obj.insert("appointmentDescription", this->m_description);
        obj.insert("appointmentIsClosed", (int)this->m_isClosed);
        obj.insert("appointmentBucketID", this->m_bucketID);
        obj.insert("appointmentBucketItemID", this->m_BucketItemID);
        obj.insert("appointmentWorkingOnStart", this->m_workingOnStartDate.toSecsSinceEpoch());
        obj.insert("appointmentLastEdit", QDateTime::currentDateTime().toSecsSinceEpoch());
        DBRequest *request = new DBRequest(RequestTypes::SaveAppoinment, obj);
        if(this->m_msid == -1){
            connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(afterSaveAppointment(QJsonObject)));
        }
        this->db->AddRequest(request);
        if(this->m_msid != -1){
            QJsonObject obj;
            obj.insert("msg", "OK");
            this->afterSaveAppointment(obj);
        }
    }else{
        int bp = 0;
        bp++;
    }
}

void Appointment::afterSaveAppointment(QJsonObject msg){
    if(msg.value("msg").toString() == "OK"){
        int msid = msg.value("id").toInt();
        if((this->m_msid == -1) && (msid > 0)){
            this->setmsid(msid);
            if(this->m_planMode == PlanModes::Fixed){
                this->appointments->agenda->saveAppointmentBlock(this, this->m_startDate, this->m_endDate, false);
            }
        }


        if(this->m_repeatMode != 0){
            QVector<Appointment*> createdApps;
            int index = 1;
            while(this->m_repeatCount > 0){
                QDateTime newStartTime = this->m_startDate;
                QDateTime newEndTime = this->m_endDate;
                if(m_repeatMode == 1){
                    newStartTime = newStartTime.addDays(1 * index);
                    newEndTime = newEndTime.addDays(1 * index);
                }else if(m_repeatMode == 2){
                    newStartTime = newStartTime.addDays(7 *index);
                    newEndTime = newEndTime.addDays(7 * index);
                }else if(m_repeatMode == 3){
                    newStartTime = newStartTime.addMonths(1 *index);
                    newEndTime = newEndTime.addMonths(1 *index);
                }
                Appointment *app = new Appointment(this->appointments, this->jobs, this->db, -1, this->m_title, this->m_jobID, newStartTime, m_duration, newEndTime, m_isClosed, m_blockRest, m_planRest, m_type->index(), m_calcTime, m_description, m_planMode, -1, -1, NullDate());
                createdApps.push_back(app);
                this->appointments->AddAppointment(app);
                m_repeatCount = m_repeatCount-1;
                index++;
            }


            for(int i = 0; i < createdApps.size(); i++){
                createdApps[i]->save(0,0, true);
            }
        }




        this->m_repeatCount = 0;
        this->m_repeatMode= 0;


        if(m_saveispartofmulti == false){
            //this->appointments->SortList();
            this->appointments->agenda->saveAgenda();
        }
        m_saveispartofmulti = false;
    }else{
        int bp = 0;
        bp++;
    }
}

void Appointment::afterSave(QJsonObject msg){
    int bp = 0;
    bp++;
    if(msg.value("msg").toString() == "OK"){
        int msid = msg.value("id").toInt();
        if((this->m_msid == -1) && (msid > 0)){
        this->setmsid(msid);
        }
    }
}

bool Appointment::savingInProgress() const
{
    return m_savingInProgress;
}

void Appointment::setSavingInProgress(bool newSavingInProgress)
{
    if (m_savingInProgress == newSavingInProgress)
        return;
    m_savingInProgress = newSavingInProgress;
    emit savingInProgressChanged();
}

void Appointment::deleteTimeFrame(int plannerIndex){
    AppointmentPlannerItem *item = planner->get(plannerIndex);
    if(item != NULL){
        QDateTime starttime = item->Datum();
        int Duration = item->Duration();
        QDateTime endTime = starttime.addSecs(Duration);
        this->appointments->agenda->removeAppointmentBlock(this, starttime, endTime);
    }

    int bp = 0;
    bp++;
}

void Appointment::closeApp(){

    //this->m_duration = this->durationLeft();
    //emit this->durationChanged();
    this->m_isClosed = true;
    this->save(0,0);
    /*
    QJsonObject obj;
    obj.insert("appointmentID", msid());
    obj.insert("appointmentTitle", title());
    obj.insert("appointmentJobID", this->jobID());
    obj.insert("appointmentStartDate", this->m_startDate.toSecsSinceEpoch());
    obj.insert("appointmentDuration", this->m_duration);
    obj.insert("appointmentEndDate", this->m_endDate.toSecsSinceEpoch());
    obj.insert("appointmentBlockRest", (int)this->m_blockRest);
    obj.insert("appointmentPlanRest", (int)this->m_planRest);
    if(this->m_type != NULL){
        obj.insert("appointmentType", m_type->index());
    }else{
        obj.insert("appointmentType", 0);
    }
    obj.insert("appointmentCalcTime", (int)this->m_calcTime);
    obj.insert("appointmentPlanMode", this->m_planMode);
    obj.insert("appointmentDescription", this->m_description);
    obj.insert("appointmentIsClosed", this->m_isClosed);
    obj.insert("appointmentBucketID", this->m_bucketID);
    obj.insert("appointmentBucketItemID", this->m_BucketItemID);
    obj.insert("appointmentWorkingOnStart", this->m_workingOnStartDate.toSecsSinceEpoch());
    obj.insert("appointmentLastEdit", QDateTime::currentDateTime().toSecsSinceEpoch());
    DBRequest *request = new DBRequest(RequestTypes::SaveAppoinment, obj);
    if(this->m_msid == -1){
        connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(afterSaveAppointment(QJsonObject)));
    }
    this->db->AddRequest(request);
    */
    this->appointments->agenda->closeAppointment(this);
}

void Appointment::emitAll(){

    if(this->m_planMode > 0){
        this->appointments->agenda->dayModel()->indexAt(m_endDate);
    }else{
        this->appointments->agenda->dayModel()->indexAt(m_startDate);
    }

    emit msidChanged();

    emit titleChanged();

    emit jobIDChanged();

    emit startDateChanged();

    emit durationChanged();

    emit endDateChanged();

    emit isPastChanged();

    emit isClosedChanged();

    emit blockRestChanged();

    emit planRestChanged();

    emit typeIndexChanged();

    emit clrChanged();

    emit calcTimeChanged();
    emit descriptionChanged();

    emit planModeChanged();

    emit jobChanged();

    emit jobNoChanged();

    emit jobTitleChanged();

    emit jobClientChanged();

    emit inEditModeChanged();

    emit deletedChanged();



    emit isPlannedChanged();

    emit boxclrChanged();

    emit typeChanged();

    emit dateErrorsChanged();

    emit isAttachedChanged();

    emit rePlanningNeededChanged();

    emit typeNameChanged();

    emit durationLeftChanged();

    emit savingInProgressChanged();

    qApp->processEvents();

}

int Appointment::bucketID() const
{
    return m_bucketID;
}

void Appointment::setBucketID(int newBucketID)
{
    if (m_bucketID == newBucketID)
        return;
    m_bucketID = newBucketID;
    emit isBucketChanged();
    emit isBucketItemChanged();
    emit bucketIDChanged();
}

int Appointment::BucketItemID() const
{
    return m_BucketItemID;
}

void Appointment::setBucketItemID(int newBucketItemID)
{
    if (m_BucketItemID == newBucketItemID)
        return;
    m_BucketItemID = newBucketItemID;
    emit isBucketChanged();
    emit isBucketItemChanged();
    emit BucketItemIDChanged();
}

bool Appointment::workingOn() const
{
    if(m_workingOnStartDate.toSecsSinceEpoch() == 0){
        return false;
    }
    return true;
}

bool Appointment::isBucket() const
{
    if(m_bucketID < 0){
        return false;
    }
    if(m_BucketItemID >= 0){
        return false;
    }
    return true;
}

bool Appointment::isBucketItem() const
{
    if(m_BucketItemID < 0){
        return false;
    }
    return true;
}
