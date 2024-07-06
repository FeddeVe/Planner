#include "plannertemplatesubitem.h"

PlannerTemplateSubItem::PlannerTemplateSubItem(int msid, int index, QString title, int defDeadline, int calculatedDuration,QObject *parent)
    : QObject{parent}
{
    this->m_msid = msid;
    this->m_index = index;
    this->m_title = title;
    this->m_defaultDeadline = defDeadline;
    this->m_calculatedDuration = calculatedDuration;

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

}

int PlannerTemplateSubItem::index() const
{
    return m_index;
}

void PlannerTemplateSubItem::setIndex(int newIndex)
{
    if (m_index == newIndex)
        return;
    m_index = newIndex;
    emit indexChanged();
}

int PlannerTemplateSubItem::msid() const
{
    return m_msid;
}

void PlannerTemplateSubItem::setMsid(int newMsid)
{
    if (m_msid == newMsid)
        return;
    m_msid = newMsid;
    emit msidChanged();
}

QString PlannerTemplateSubItem::title() const
{
    return m_title;
}

void PlannerTemplateSubItem::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

int PlannerTemplateSubItem::defaultDeadline() const
{
    return m_defaultDeadline;
}

void PlannerTemplateSubItem::setDefaultDeadline(int newDefaultDeadline)
{
    if (m_defaultDeadline == newDefaultDeadline)
        return;
    m_defaultDeadline = newDefaultDeadline;
    emit defaultDeadlineChanged();
}

QString PlannerTemplateSubItem::calculatedDuration() const
{
    return durationToString(m_calculatedDuration);
}

int PlannerTemplateSubItem::CalculatedDuration() const{
    return m_calculatedDuration;
}

void PlannerTemplateSubItem::setCalculatedDuration(const QString &newCalculatedDuration)
{
    int duration = durationFromString(newCalculatedDuration);
    if (m_calculatedDuration == duration)
        return;
    m_calculatedDuration = duration;
    emit calculatedDurationChanged();
}

void PlannerTemplateSubItem::SetCalculatedDuration(const int &newCalculatedDuration){
    if (m_calculatedDuration == newCalculatedDuration)
        return;
    m_calculatedDuration = newCalculatedDuration;
    emit calculatedDurationChanged();
}
