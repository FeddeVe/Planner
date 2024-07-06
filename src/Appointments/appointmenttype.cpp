#include "appointmenttype.h"

AppointmentType::AppointmentType(int index, QString label, QString color,QString boxcolor, bool calcTime, QObject *parent)
    : QObject{parent}
{
    this->m_index = index;
    this->m_label = label;
    this->m_clr = color;
    this->m_boxclr = boxcolor;
    this->m_calcTime = calcTime;
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);


}

int AppointmentType::index() const
{
    return m_index;
}

void AppointmentType::setIndex(int newIndex)
{
    if (m_index == newIndex)
        return;
    m_index = newIndex;
    emit indexChanged();
}

QString AppointmentType::label() const
{
    return m_label;
}

void AppointmentType::setLabel(const QString &newLabel)
{
    if (m_label == newLabel)
        return;
    m_label = newLabel;
    emit labelChanged();
}

QString AppointmentType::clr() const
{
    return m_clr;
}

void AppointmentType::setClr(const QString &newClr)
{
    if (m_clr == newClr)
        return;
    m_clr = newClr;
    emit clrChanged();
}

bool AppointmentType::calcTime() const
{
    return m_calcTime;
}

void AppointmentType::setCalcTime(bool newCalcTime)
{
    if (m_calcTime == newCalcTime)
        return;
    m_calcTime = newCalcTime;
    emit calcTimeChanged();
}

QString AppointmentType::boxclr() const
{
    return m_boxclr;
}

void AppointmentType::setboxclr(const QString &newBoxclr)
{
    if (m_boxclr == newBoxclr)
        return;
    m_boxclr = newBoxclr;
    emit boxclrChanged();
}
