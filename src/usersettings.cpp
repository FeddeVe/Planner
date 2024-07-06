#include "usersettings.h"

UserSettings::UserSettings(QObject *parent)
    : QObject{parent}
{
    m_PlanMonday = true;
    m_mondayStart = QTime::fromString("09:30", "HH:mm");
    m_mondayEnd = QTime::fromString("17:30", "HH:mm");
    m_planTuesday = true;
    m_tuesdayStart = QTime::fromString("09:30", "HH:mm");
    m_tuesdayEnd = QTime::fromString("17:30", "HH:mm");
    m_planWednesDay = true;
    m_wednesdayStart = QTime::fromString("09:30", "HH:mm");
    m_wednesdayEnd = QTime::fromString("17:30", "HH:mm");
    m_planThursday = true;
    m_thursdayStart = QTime::fromString("09:30", "HH:mm");
    m_thursdayEnd = QTime::fromString("17:30", "HH:mm");
    m_planFriday = true;
    m_fridayStart = QTime::fromString("09:30", "HH:mm");
    m_fridayEnd = QTime::fromString("17:30", "HH:mm");
    m_planSaturday = false;
    m_planSunday = false;

}

bool UserSettings::PlanMonday() const
{
    return m_PlanMonday;
}

void UserSettings::setPlanMonday(bool newPlanMonday)
{
    if (m_PlanMonday == newPlanMonday)
        return;
    m_PlanMonday = newPlanMonday;
    emit PlanMondayChanged();
}

bool UserSettings::planTuesday() const
{
    return m_planTuesday;
}

void UserSettings::setPlanTuesday(bool newPlanTuesday)
{
    if (m_planTuesday == newPlanTuesday)
        return;
    m_planTuesday = newPlanTuesday;
    emit planTuesdayChanged();
}

bool UserSettings::planWednesDay() const
{
    return m_planWednesDay;
}

void UserSettings::setPlanWednesDay(bool newPlanWednesDay)
{
    if (m_planWednesDay == newPlanWednesDay)
        return;
    m_planWednesDay = newPlanWednesDay;
    emit planWednesDayChanged();
}

bool UserSettings::planThursday() const
{
    return m_planThursday;
}

void UserSettings::setPlanThursday(bool newPlanThursday)
{
    if (m_planThursday == newPlanThursday)
        return;
    m_planThursday = newPlanThursday;
    emit planThursdayChanged();
}

bool UserSettings::planFriday() const
{
    return m_planFriday;
}

void UserSettings::setPlanFriday(bool newPlanFriday)
{
    if (m_planFriday == newPlanFriday)
        return;
    m_planFriday = newPlanFriday;
    emit planFridayChanged();
}

bool UserSettings::planSaturday() const
{
    return m_planSaturday;
}

void UserSettings::setPlanSaturday(bool newPlanSaturday)
{
    if (m_planSaturday == newPlanSaturday)
        return;
    m_planSaturday = newPlanSaturday;
    emit planSaturdayChanged();
}

bool UserSettings::planSunday() const
{
    return m_planSunday;
}

void UserSettings::setPlanSunday(bool newPlanSunday)
{
    if (m_planSunday == newPlanSunday)
        return;
    m_planSunday = newPlanSunday;
    emit planSundayChanged();
}

QString UserSettings::mondayStart() const
{
    return m_mondayStart.toString("HH:mm");
}

QTime UserSettings::MondayStart()const{
    return m_mondayStart;
}

void UserSettings::setMondayStart(const QString &newMondayStart)
{
    QTime a = QTime::fromString(newMondayStart, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_mondayStart == a)
        return;
    m_mondayStart = a;
    emit mondayStartChanged();
}

QString UserSettings::mondayEnd() const
{
    return m_mondayEnd.toString("HH:mm");
}

QTime UserSettings::MondayEnd() const{
    return m_mondayEnd;
}

void UserSettings::setMondayEnd(const QString &newMondayEnd)
{
    QTime a = QTime::fromString(newMondayEnd, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_mondayEnd == a)
        return;
    m_mondayEnd = a;
    emit mondayEndChanged();
}

QString UserSettings::tuesdayStart() const
{
    return m_tuesdayStart.toString("HH:mm");
}

QTime UserSettings::TuesdayStart() const{
    return m_tuesdayStart;
}

void UserSettings::setTuesdayStart(const QString &newTuesdayStart)
{
    QTime a = QTime::fromString(newTuesdayStart, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_tuesdayStart == a)
        return;
    m_tuesdayStart = a;
    emit tuesdayStartChanged();
}

QString UserSettings::tuesdayEnd() const
{
    return m_tuesdayEnd.toString("HH:mm");
}

QTime UserSettings::TuesdayEnd() const{
    return m_tuesdayEnd;
}

void UserSettings::setTuesdayEnd(const QString &newTuesdayEnd)
{
    QTime a = QTime::fromString(newTuesdayEnd, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_tuesdayEnd == a)
        return;
    m_tuesdayEnd = a;
    emit tuesdayEndChanged();
}

QString UserSettings::wednesdayStart() const
{
    return m_wednesdayStart.toString("HH:mm");
}

QTime UserSettings::WednesdayStart() const{
    return m_wednesdayStart;
}

void UserSettings::setWednesdayStart(const QString &newWednesdayStart)
{
    QTime a = QTime::fromString(newWednesdayStart, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_wednesdayStart == a)
        return;
    m_wednesdayStart = a;
    emit wednesdayStartChanged();
}

QString UserSettings::wednesdayEnd() const
{
    return m_wednesdayEnd.toString("HH:mm");
}

QTime UserSettings::WednesdayEnd() const{
    return m_wednesdayEnd;
}

void UserSettings::setWednesdayEnd(const QString &newWednesdayEnd)
{
    QTime a = QTime::fromString(newWednesdayEnd, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_wednesdayEnd == a)
        return;
    m_wednesdayEnd = a;
    emit wednesdayEndChanged();
}

QString UserSettings::thursdayStart() const
{
    return m_thursdayStart.toString("HH:mm");
}

QTime UserSettings::ThursdayStart() const{
    return m_thursdayStart;
}

void UserSettings::setThursdayStart(const QString &newThursdayStart)
{
    QTime a = QTime::fromString(newThursdayStart, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_thursdayStart == a)
        return;
    m_thursdayStart = a;
    emit thursdayStartChanged();
}

QString UserSettings::thursdayEnd() const
{
    return m_thursdayEnd.toString("HH:mm");
}

QTime UserSettings::ThursdayEnd() const{
    return m_thursdayEnd;
}

void UserSettings::setThursdayEnd(const QString &newThursdayEnd)
{
    QTime a = QTime::fromString(newThursdayEnd, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_thursdayEnd == a)
        return;
    m_thursdayEnd = a;
    emit thursdayEndChanged();
}

QString UserSettings::fridayStart() const
{
    return m_fridayStart.toString("HH:mm");
}

QTime UserSettings::FridayStart() const{
    return m_fridayStart;
}

void UserSettings::setFridayStart(const QString &newFridayStart)
{
    QTime a = QTime::fromString(newFridayStart, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_fridayStart == a)
        return;
    m_fridayStart = a;
    emit fridayStartChanged();
}

QString UserSettings::fridayEnd() const
{
    return m_fridayEnd.toString("HH:mm");
}

QTime UserSettings::FridayEnd() const{
    return m_fridayEnd;
}

void UserSettings::setFridayEnd(const QString &newFridayEnd)
{
    QTime a = QTime::fromString(newFridayEnd, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_fridayEnd == a)
        return;
    m_fridayEnd = a;
    emit fridayEndChanged();
}

QString UserSettings::saterdayStart() const
{
    return m_saterdayStart.toString("HH:mm");
}

QTime UserSettings::SaturdayStart() const{
    return m_saterdayStart;
}

void UserSettings::setSaterdayStart(const QString &newSaterdayStart)
{
    QTime a = QTime::fromString(newSaterdayStart, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_saterdayStart == a)
        return;
    m_saterdayStart = a;
    emit saterdayStartChanged();
}

QString UserSettings::saturedayEnd() const
{
    return m_saturedayEnd.toString("HH:mm");
}

QTime UserSettings::SaturdayEnd() const{
    return m_saturedayEnd;
}

void UserSettings::setSaturedayEnd(const QString &newSaturedayEnd)
{
    QTime a = QTime::fromString(newSaturedayEnd, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_saturedayEnd == a)
        return;
    m_saturedayEnd = a;
    emit saturedayEndChanged();
}

QString UserSettings::sundayStart() const
{
    return m_sundayStart.toString("HH:mm");
}

QTime UserSettings::SundayStart() const{
    return m_sundayStart;
}

void UserSettings::setSundayStart(const QString &newSundayStart)
{
    QTime a = QTime::fromString(newSundayStart, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_sundayStart == a)
        return;
    m_sundayStart = a;
    emit sundayStartChanged();
}

QString UserSettings::sundayEnd() const
{
    return m_sundayEnd.toString("HH:mm");
}

QTime UserSettings::SundayEnd() const{
    return m_sundayEnd;
}

void UserSettings::setSundayEnd(const QString &newSundayEnd)
{
    QTime a = QTime::fromString(newSundayEnd, "HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_sundayEnd == a)
        return;
    m_sundayEnd = a;
    emit sundayEndChanged();
}

bool UserSettings::isWorkingDay(QDateTime date){
    int bp = date.date().day();
    switch(date.date().dayOfWeek()){
    case Qt::Monday:
        return PlanMonday();
    case Qt::Tuesday:
        return planTuesday();
    case Qt::Wednesday:
        return planWednesDay();
    case Qt::Thursday:
         return planThursday();
    case Qt::Friday:
        return planFriday();
    case Qt::Saturday:
        return planSaturday();
    case Qt::Sunday:
        return planSunday();
    }
    return false;
}

QTime UserSettings::getStartTime(QDateTime date){
    switch(date.date().dayOfWeek()){
    case Qt::Monday:
        return MondayStart();
    case Qt::Tuesday:
        return TuesdayStart();
    case Qt::Wednesday:
        return WednesdayStart();
    case Qt::Thursday:
        return ThursdayStart();
    case Qt::Friday:
        return FridayStart();
    case Qt::Saturday:
        return SaturdayStart();
    case Qt::Sunday:
        return SundayStart();
    }
    return QTime();
}

QTime UserSettings::getEndTime(QDateTime date){
    switch(date.date().dayOfWeek()){
    case Qt::Monday:
        return MondayEnd();
    case Qt::Tuesday:
        return TuesdayEnd();
    case Qt::Wednesday:
        return WednesdayEnd();
    case Qt::Thursday:
        return ThursdayEnd();
    case Qt::Friday:
        return FridayEnd();
    case Qt::Saturday:
        return SaturdayEnd();
    case Qt::Sunday:
        return SundayEnd();
    }
    return QTime();
}
