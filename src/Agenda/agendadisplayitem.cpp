#include "agendadisplayitem.h"

AgendaDisplayItem::AgendaDisplayItem(AgendaTypes type, Appointment *appointment, QDateTime planDate,QDateTime endPlanDate, QObject *parent)
    : QObject{parent}
{
    this->m_appointment = appointment;
   // bool ok = connect(this->m_appointment, SIGNAL(someThingChanged()), this, SLOT(someThingChangedSlot()));
    this->m_planDate = planDate;
    this->m_endplanDate = endPlanDate;
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}


QString AgendaDisplayItem::title() const
{

    if(this->type == AgendaTypes::appointmentType){
        return this->m_appointment->title();
    }
    return "TASK MOET NOG";
}

QString AgendaDisplayItem::jobNo() const
{
    if(this->type == AgendaTypes::appointmentType){
        return this->m_appointment->jobNo();
    }
    return "TASK MOET NOG";
}

QString AgendaDisplayItem::jobTitle() const
{
    if(this->type == AgendaTypes::appointmentType){
        return this->m_appointment->jobTitle();
    }
    return "TASK MOET NOG";
}

int AgendaDisplayItem::xPos() const
{
    return m_xPos;
}

void AgendaDisplayItem::setXPos(int newXPos)
{
    if (m_xPos == newXPos)
        return;
    m_xPos = newXPos;
    emit xPosChanged();
}

int AgendaDisplayItem::xHeight() const
{
    return m_xHeight;
}

void AgendaDisplayItem::setXHeight(int newXHeight)
{
    if (m_xHeight == newXHeight)
        return;
    m_xHeight = newXHeight;
    emit xHeightChanged();
}

int AgendaDisplayItem::xWidth() const
{
    return m_xWidth;
}

void AgendaDisplayItem::setXWidth(int newXWidth)
{
    if (m_xWidth == newXWidth)
        return;
    m_xWidth = newXWidth;
    emit xWidthChanged();
}

QString AgendaDisplayItem::boxColor() const
{
    if(this->type == AgendaTypes::appointmentType){
        return this->m_appointment->clr();
    }
    return "TASK MOET NOG";
}

QString AgendaDisplayItem::planDate() const
{
    return m_planDate.toString("dd.MM.yyyy HH:mm");
}


QString AgendaDisplayItem::endPlanDate() const
{
    if(m_endplanDate.isValid()){
    return m_endplanDate.toString("dd.MM.yyyy HH:mm");
    }else{
    return "NO VALID DATE";
    }
}

void AgendaDisplayItem::setendPlanDate(const QDateTime &newEndPlanDate)
{
    if (m_endplanDate == newEndPlanDate)
        return;
    m_endplanDate = newEndPlanDate;
    emit endPlanDateChanged();
}

Appointment *AgendaDisplayItem::appointment(){
    return this->m_appointment;
}
