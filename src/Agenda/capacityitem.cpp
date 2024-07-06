#include "capacityitem.h"

CapacityItem::CapacityItem(QString m_month,
                           QString m_capPercentage,
                           QString m_capColor,
                           QString m_workabledHours,
                           QString m_hoursFromLastMoth,
                           QString m_plannedHours,
                           QString m_workedHours,
                           QString m_resultHours,
                           bool m_isCurMonth,float m_percentage, QObject *parent)
    : QObject{parent}
{
    this->m_month = m_month;
    this->m_capPercentage = m_capPercentage;
    this->m_capColor = m_capColor;
    this->m_workabledHours = m_workabledHours;
    this->m_hoursFromLastMoth = m_hoursFromLastMoth;
    this->m_plannedHours = m_plannedHours;
    this->m_workedHours = m_workedHours;
    this->m_resultHours = m_resultHours;
    this->m_isCurMonth = m_isCurMonth;
    this->m_percentage = m_percentage;
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

QString CapacityItem::month() const
{
    return m_month;
}

void CapacityItem::setMonth(const QString &newMonth)
{
    if (m_month == newMonth)
        return;
    m_month = newMonth;
    emit monthChanged();
}

QString CapacityItem::capPercentage() const
{
    return m_capPercentage;
}

void CapacityItem::setCapPercentage(const QString &newCapPercentage)
{
    if (m_capPercentage == newCapPercentage)
        return;
    m_capPercentage = newCapPercentage;
    emit capPercentageChanged();
}

QString CapacityItem::capColor() const
{
    return m_capColor;
}

void CapacityItem::setCapColor(const QString &newCapColor)
{
    if (m_capColor == newCapColor)
        return;
    m_capColor = newCapColor;
    emit capColorChanged();
}

QString CapacityItem::workabledHours() const
{
    return m_workabledHours;
}

QString CapacityItem::hoursFromLastMoth() const
{
    return m_hoursFromLastMoth;
}

QString CapacityItem::plannedHours() const
{
    return m_plannedHours;
}

QString CapacityItem::workedHours() const
{
    return m_workedHours;
}

QString CapacityItem::resultHours() const
{
    return m_resultHours;
}


bool CapacityItem::isCurMonth() const
{
    return m_isCurMonth;
}

float CapacityItem::percentage() const{
    return m_percentage;
}
