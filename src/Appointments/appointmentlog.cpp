#include "appointmentlog.h"

AppointmentLog::AppointmentLog(Appointment *appointment, DBManager *db, QObject *parent)
    : QAbstractListModel{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    m_appointment = appointment;
    m_db = db;
    this->LoadData();

}

void AppointmentLog::LoadData(){
    if(m_appointment->msid() > 0){
     QJsonObject data;
     data.insert("appointmentID", m_appointment->msid());
     DBRequest *request = new DBRequest(RequestTypes::LoadAppointmentLog, data, this);
     connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(AfterLoad(QJsonObject)));
     this->m_db->AddRequest(request);
    }
}

void AppointmentLog::AfterLoad(QJsonObject data){
    QString msg = data.value("msg").toString();
    if(msg != "OK"){
        return;
    }


    QJsonArray a = data.value("data").toArray();
    for (int i = 0; i < a.size(); i++){
        QJsonObject x = a[i].toObject();

        int msid = (x.value("id").toString()).toInt();
        int duration = (x.value("duration").toString().toInt());
        qint64 endblock = x.value("endBlock").toString().toLongLong();
        QDateTime endDate = QDateTime::fromSecsSinceEpoch(x.value("endDate").toString().toULongLong());
        qint64 startBlock = x.value("startBlock").toString().toLongLong();
        QDateTime startDate = QDateTime::fromSecsSinceEpoch(x.value("startDate").toString().toULongLong());
        int status = x.value("status").toString().toInt();
        bool found = false;
        for(int i = 0; i < this->m_data.size(); i++){
            if(this->m_data[i]->msid() == msid){
                found = true;
                int bp = 0;
                bp++;
                break;
            }
        }


        if(found == false){
            AppointmentLogItem *item = new AppointmentLogItem(msid, startDate, duration, endDate, startBlock, endblock, status, m_db);
            m_data.push_back(item);
            item->setIsPublished(m_appointment->appointments->agenda->NewAgendaBlocks->PublishItem(m_appointment, item));
        }
    }
}

void AppointmentLog::ClearPlan(AgendaBlock *startBlock){
    for(int i = 0; i < this->m_data.size(); i++){
        if(this->m_data[i]->status() != logStatus::WorkedOn){
            QDateTime startTime = startBlock->m_startTime;
            if(this->m_data[i]->EndDate() > startTime){
                if(m_appointment->planMode() != PlanModes::Fixed){
                    // planmode Fixed wordt geupdate bij wijzigen van de appointment
                    // Andere planmodes kunnen opnieuw gepland worden
                    if(this->m_data[i]->StartDate() > startTime){
                        //Item wordt opnieuw gepland
                        this->m_data[i]->setStatus(logStatus::ReUsable); // remove from current agenda
                        //depublish

                    }else{
                        //Inkorten en de rest wordt opnieuw gepland
                        this->m_data[i]->setEndDate(startTime);
                        this->m_data[i]->setDuration(m_data[i]->StartDate().secsTo(m_data[i]->EndDate()));
                        this->m_data[i]->save(m_appointment->msid());
                    }
                }
            }
        }
        //set saved to false, dit komt bij Agenda Publish weer goed.
        this->m_data[i]->setIsSaved(false);
    }

    int DurationLeft = m_appointment->Duration();
    for(int i = 0; i < this->m_data.size(); i++){
        if((m_data[i]->status() == logStatus::Planned) || (m_data[i]->status() == logStatus::WorkedOn)){
            DurationLeft = DurationLeft - m_data[i]->Duration();
        }
    }
    m_appointment->setDurationLeft(DurationLeft);
}

void AppointmentLog::AgendaPublish(AgendaBlock *startBlock, AgendaBlock *endBlock){
    // check if deze al bestaat
    bool found = false;
    for(int i = 0; i < m_data.size(); i++){
        if((m_data[i]->startBlock() == startBlock->blockID) && (m_data[i]->endBlock() == endBlock->blockID) && (m_data[i]->isSaved() == false)){
            //bestaat al, hoeft niets meer aan gedaan te worden.
            m_data[i]->setIsSaved(true);
            found = true;
            break;
        }
    }

    if(found == false){
        beginResetModel();
        AppointmentLogItem *item = new AppointmentLogItem(-1,startBlock->m_startTime, startBlock->m_startTime.secsTo(endBlock->m_endTime), endBlock->m_endTime, startBlock->blockID, endBlock->blockID, 0, m_db);
        item->save(m_appointment->msid());
        item->setIsSaved(true);
        this->m_data.push_back(item);
        this->SortList();
        endResetModel();
    }
}

void AppointmentLog::AgendaPublishFinished(){
    beginResetModel();
    for(int i = 0; i < this->m_data.size(); i++){
        if(this->m_data[i]->isSaved() == false){
            //niet meer nodig, deleten maar!!!
            QJsonObject data;
            data.insert("logID", m_data[i]->msid());
            DBRequest *request = new DBRequest(RequestTypes::DeleteAppointmentLog, data, this);
            connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(AfterLoad(QJsonObject)));
            this->m_db->AddRequest(request);

            m_data[i]->deleteLater();
            m_data.erase(m_data.begin() + i);
            i = i -1;

            int bp = 0;
            bp++;

        }
    }
    endResetModel();
}



int AppointmentLog::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int AppointmentLog::count() const{
    return m_data.count();
}

QVariant AppointmentLog::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const AppointmentLogItem  *item = m_data.at(row);
    switch(role) {
    case IDRole:
        return item->msid();
    }
    return QVariant();
}

QHash<int, QByteArray> AppointmentLog::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[IDRole] = "ID";
    return roles;
}

void AppointmentLog::loadModel(const QString searchValue){
    // m.lock();
    /*
    m.lock();
    QString sval = searchValue.toUpper();

    beginResetModel();
    this->m_data.clear();
    this->m_data.shrink_to_fit();
    int index = 0;
    Job *j = jobs->getJob(index);
    while(j!=NULL){
        try{
            if((j->no().toUpper().contains(sval)) || (j->title().toUpper().contains(sval)) || (j->client().toUpper().contains(sval))){
                this->m_data.push_back(j);
            }
        }catch(...){
            int bp = 0;
            bp++;
        }
        index++;
        j = jobs->getJob(index);
        // emit this->dataChanged(index(0),index(0);
    }
    //this->m_data.push_back(jobs->editJob);
    this->SortList();
    endResetModel();
    m.unlock();
*/
}

AppointmentLogItem *AppointmentLog::get(int row) const{
    //QMutexLocker lock( &m);
    if((row < 0) || (row >= m_data.count())){
        return NULL;
    }
    return m_data[row];
}

void AppointmentLog::SortList(){
    std::sort(m_data.begin(), m_data.end(), [](const AppointmentLogItem *a, const AppointmentLogItem *b) { return a->StartDate() < b->StartDate(); });
}

void AppointmentLog::AppointmentIDChanged(){
    for(int i = 0; i < m_data.size(); i++){
        m_data[i]->save(m_appointment->msid());
    }
}
