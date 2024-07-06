#include "appointmentplanner.h"

AppointmentPlanner::AppointmentPlanner(Appointment *appointment, Agenda *agenda, QObject *parent)
    : QAbstractListModel{parent}
{
    this->appointment = appointment;
    this->agenda = agenda;
    this->m_durationLeft = 0;

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

}

QString AppointmentPlanner::totalDuration() const
{
    return m_totalDuration;
}

QString AppointmentPlanner::workedDuration() const
{
    return m_workedDuration;
}

QString AppointmentPlanner::plannedDuration() const
{
    return m_plannedDuration;
}

QString AppointmentPlanner::durationLeft() const
{

    return m_durationLeft;
}

void AppointmentPlanner::DoMagic(){

     beginResetModel();
    if(agenda->agendaBlocks.size() <= 0){

        for(int i = 0; i < m_data.size(); i++){
            m_data[i]->deleteLater();

        }
        m_data.clear();
        m_data.shrink_to_fit();
        endResetModel();
        return;
    }

    this->agendaBlocks.clear();
    // loading blocks from agenda
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
        for(int i = 0; i < block->items.size(); i++){
            if((block->items[i]->Type == appointmentType) && (block->items[i]->appointment == this->appointment)){
                this->agendaBlocks.push_back(block);
            }
        }
        index++;
    }

    //Creating Headers
    int totalDuration = appointment->Duration();
    int workedDuration = 0;
    int plannedDuation = 0;
    bool double_planned = false;
    for(int i = 0; i < this->agendaBlocks.size(); i++){
        if(this->agendaBlocks[i]->items.size() > 1){
            double_planned = true;
        }
        for(int y = 0; y < this->agendaBlocks[i]->items.size(); y++){
            AgendaBlockItem *item = this->agendaBlocks[i]->items[y];
            if((item->Type == appointmentType) && (item->appointment == this->appointment)){
                //ismijn
                if(item->isClosed){
                    workedDuration = workedDuration + 15*60;
                }else{
                    plannedDuation = plannedDuation + 15*60;
                }
            }
        }
    }
    int resultDuration = totalDuration - workedDuration - plannedDuation;
    this->m_DurationLeft = totalDuration - workedDuration;
    this->m_totalDuration = durationToString(totalDuration);
    this->m_workedDuration = durationToString(workedDuration);
    this->m_plannedDuration = durationToString(plannedDuation);
    if(appointment->isClosed()){
        m_DurationLeft = 0;
        resultDuration = 0;
    }
    this->m_durationLeft = durationToString(resultDuration);
    if(resultDuration <= 0){
        this->m_completePlanned = true;
    }else{
        this->m_completePlanned = false;
    }
    this->m_agendaErrors = double_planned;
    this->m_agendaErrorsText = "Double planned items in agenda";
    this->m_DurationResult = resultDuration;
    this->combinePlanning();

    emit this->totalDurationChanged();
    emit this->workedDurationChanged();
    emit this->plannedDurationChanged();
    emit this->durationLeftChanged();
    emit this->completePlannedChanged();
    emit this->agendaErrorsChanged();
    emit this->agendaErrorsTextChanged();
    endResetModel();

}

void AppointmentPlanner::combinePlanning(){

    for(int i = 0; i < m_data.size(); i++){
        delete m_data[i];
    }
    m_data.clear();
    m_data.shrink_to_fit();
    AppointmentPlannerItem * item = NULL;
    qint64 checkBlockID = 0;

    for(int i = 0; i < this->agendaBlocks.size(); i++){
        checkBlockID++;
        if(agendaBlocks[i]->blockID != checkBlockID){
            if(item != NULL){
                m_data.push_back(item);
            }
            bool iscompleted = false;

            for(int y = 0; y < agendaBlocks[i]->items.size(); y++){
                if(agendaBlocks[i]->items[y]->Type == appointmentType){
                    if(agendaBlocks[i]->items[y]->appointment == this->appointment){
                        iscompleted = agendaBlocks[i]->items[y]->isClosed;
                        break;
                    }
                }
            }

            item = new AppointmentPlannerItem(agendaBlocks[i]->m_startTime, iscompleted, agendaBlocks[i]->isFromTMPY);
            checkBlockID = agendaBlocks[i]->blockID;
        }
        item->addDuration(15*60);
    }
    if(item != NULL){
        m_data.push_back(item);
    }

}

int AppointmentPlanner::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->m_data.count();
}



QVariant AppointmentPlanner::data(const QModelIndex &index, int role) const
{


    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const AppointmentPlannerItem  *item = m_data.at(row);
    switch(role) {
    case DatumRole:
        return item->datum();
    case DurationRole:
        return item->duration();
    case StatusRole:
        return item->status();
    case RemarksRole:
        return item->remarks();
    case CompletedRole:
        return item->completed();
    case FromTMPYRole:
        return item->fromTMPY();
    case IsPastRole:
        return item->isPast();
    }
    return QVariant();

}

QHash<int, QByteArray> AppointmentPlanner::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[DatumRole] = "Datum";
    roles[DurationRole] = "Duration";
    roles[StatusRole] = "Status";
    roles[RemarksRole] = "Remarks";
    roles[CompletedRole] = "Completed";
    roles[FromTMPYRole] = "IsFromTMPY";
    roles[IsPastRole] = "IsPast";
    return roles;
}

AppointmentPlannerItem *AppointmentPlanner::get(int row) const{
  //  return NULL;
    /*
    if((row < 0) || (row >= m_data.count())){
        //return jobs->editJob;
        int bp = 0;
        bp++;
        return NULL;
    }
    return m_data[row];
*/
    if((row < 0) || (row >= m_data.count())){
        return NULL;
    }
    return m_data[row];
}


bool AppointmentPlanner::completePlanned() const
{
    return m_completePlanned;
}

bool AppointmentPlanner::agendaErrors() const
{
    return m_agendaErrors;
}

QString AppointmentPlanner::agendaErrorsText() const
{
    return m_agendaErrorsText;
}

QString AppointmentPlanner::saveWorkedOn(QString dateTime, QString Duration){
    QDateTime a = QDateTime::fromString(dateTime, "dd/MM/yyyy HH:mm");
    if(!a.isValid()){
        return "Invalid Date Set";
    }
    QDateTime b = QDateTime::fromString(Duration, "dd/MM/yyyy HH:mm");
    if(!b.isValid()){
        return "Invalid Date Set";
    }
   // int duration = durationFromString(Duration);
    int duration = a.secsTo(b);
    if(duration == 0){
        return "Invalid Duration Set";
    }
  //  if(a > QDateTime::currentDateTime()){
  //      return "Starttime cannot be in the future";
  //  }

   // if(appointment->msid() < 0){
   //     return "Appointment has to be saved first";
   // }

    QDateTime startTime = a;
    QDateTime endTime = b; // a.addSecs(duration);

   // if(endTime > QDateTime::currentDateTime()){
   //     return "StartTime + Duration cannot be in the Future";
   // }

    this->agenda->saveAppointmentBlock(this->appointment, startTime, endTime, true);
   // this->DoMagic();

    return "";
}

void AppointmentPlanner::afterBlockSave(QJsonObject msg){
    int bp = 0;
    bp++;
}


