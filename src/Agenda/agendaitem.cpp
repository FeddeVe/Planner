#include "agendaitem.h"

AgendaItem::AgendaItem(AgendaTypes type, Appointment *appointment,QObject *parent)
    : QObject{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    this->AgendaType = type;
    this->appointment = appointment;
}

AgendaItem::~AgendaItem(){
    for(int i = 0; i < this->agendaBlock.size(); i++){
        delete this->agendaBlock[i];
    }
}

void AgendaItem::SetAgendaBlock(QDateTime startTime, QDateTime endTime, bool isTMPY){

}

void AgendaItem::ClearPlanning(bool isTMPY){

}

QDateTime AgendaItem::getEndDateTime() const{
    if(AgendaType == AppointmentItem){
        return this->appointment->StartDate();
    } // CODE FOR TASKS
}

int AgendaItem::getDuration() const{
    if(AgendaType == AppointmentItem){
        return this->appointment->Duration();
    } // CODE FOR TASKS
}

QDateTime AgendaItem::getStartTime() const{
    if(AgendaType == AppointmentItem){
        return this->appointment->EndDate();
    } // CODE FOR TASKS
}

int AgendaItem::getPlanMode() const{
    if(AgendaType == AppointmentItem){
        return this->appointment->planMode();
    } // CODE FOR TASKS
}

bool AgendaItem::isPlanned(bool TMPY) const{
    /*
    if(AgendaType == AppointmentItem){
        int agenda_duration = 0;
        if(TMPY){
            for(int i = 0; i < agendaBlock.size(); i++){
                agenda_duration = agenda_duration + (agendaBlock[i]->startTime().secsTo(agendaBlock[i]->endTime()));
            }
        }else{
            for(int i = 0; i < this->appointment->agendaBlock.size(); i++){
                agenda_duration = agenda_duration + (this->appointment->agendaBlock[i]->startTime().secsTo(this->appointment->agendaBlock[i]->endTime()));
            }
        }
        if(agenda_duration >= appointment->PlannedDuration()){
            return true;
        }
        return false;
    }//CODE FOR TASKS
*/
}

bool AgendaItem::isDeleted() const{
    if(AgendaType == AppointmentItem){
        return this->appointment->deleted();
    } //CODE FOR TASK
}
int AgendaItem::getMSID() const {
    if(AgendaType == AppointmentItem){
        return this->appointment->msid();
    } //CODE FOR TASK
}

Appointment *AgendaItem::getAppointmet(){
    return this->appointment;
}
