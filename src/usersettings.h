#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QObject>
#include <QTime>
#include <QDateTime>

class UserSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool PlanMonday READ PlanMonday WRITE setPlanMonday NOTIFY PlanMondayChanged);
    Q_PROPERTY(bool planTuesday READ planTuesday WRITE setPlanTuesday NOTIFY planTuesdayChanged);
    Q_PROPERTY(bool planWednesDay READ planWednesDay WRITE setPlanWednesDay NOTIFY planWednesDayChanged);
    Q_PROPERTY(bool planThursday READ planThursday WRITE setPlanThursday NOTIFY planThursdayChanged);
    Q_PROPERTY(bool planFriday READ planFriday WRITE setPlanFriday NOTIFY planFridayChanged);
    Q_PROPERTY(bool planSaturday READ planSaturday WRITE setPlanSaturday NOTIFY planSaturdayChanged);
    Q_PROPERTY(bool planSunday READ planSunday WRITE setPlanSunday NOTIFY planSundayChanged);
    Q_PROPERTY(QString mondayStart READ mondayStart WRITE setMondayStart NOTIFY mondayStartChanged);
    Q_PROPERTY(QString mondayEnd READ mondayEnd WRITE setMondayEnd NOTIFY mondayEndChanged);
    Q_PROPERTY(QString tuesdayStart READ tuesdayStart WRITE setTuesdayStart NOTIFY tuesdayStartChanged);
    Q_PROPERTY(QString  tuesdayEnd READ tuesdayEnd WRITE setTuesdayEnd NOTIFY tuesdayEndChanged);
    Q_PROPERTY(QString wednesdayStart READ wednesdayStart WRITE setWednesdayStart NOTIFY wednesdayStartChanged);
    Q_PROPERTY(QString wednesdayEnd READ wednesdayEnd WRITE setWednesdayEnd NOTIFY wednesdayEndChanged);
    Q_PROPERTY(QString thursdayStart READ thursdayStart WRITE setThursdayStart NOTIFY thursdayStartChanged);
    Q_PROPERTY(QString thursdayEnd READ thursdayEnd WRITE setThursdayEnd NOTIFY thursdayEndChanged);
    Q_PROPERTY(QString fridayStart READ fridayStart WRITE setFridayStart NOTIFY fridayStartChanged);
    Q_PROPERTY(QString fridayEnd READ fridayEnd WRITE setFridayEnd NOTIFY fridayEndChanged);
    Q_PROPERTY(QString saterdayStart READ saterdayStart WRITE setSaterdayStart NOTIFY saterdayStartChanged);
    Q_PROPERTY(QString saturedayEnd READ saturedayEnd WRITE setSaturedayEnd NOTIFY saturedayEndChanged);
    Q_PROPERTY(QString sundayStart READ sundayStart WRITE setSundayStart NOTIFY sundayStartChanged);
    Q_PROPERTY(QString sundayEnd READ sundayEnd WRITE setSundayEnd NOTIFY sundayEndChanged);

public:
    explicit UserSettings(QObject *parent = nullptr);

    bool PlanMonday() const;
    void setPlanMonday(bool newPlanMonday);

    bool planTuesday() const;
    void setPlanTuesday(bool newPlanTuesday);

    bool planWednesDay() const;
    void setPlanWednesDay(bool newPlanWednesDay);

    bool planThursday() const;
    void setPlanThursday(bool newPlanThursday);

    bool planFriday() const;
    void setPlanFriday(bool newPlanFriday);

    bool planSaturday() const;
    void setPlanSaturday(bool newPlanSaturday);

    bool planSunday() const;
    void setPlanSunday(bool newPlanSunday);

    QString mondayStart() const;
    QTime MondayStart() const;
    void setMondayStart(const QString &newMondayStart);

    QString mondayEnd() const;
    QTime MondayEnd() const;
    void setMondayEnd(const QString &newMondayEnd);

    QString tuesdayStart() const;
    QTime TuesdayStart() const;
    void setTuesdayStart(const QString &newTuesdayStart);

    QString tuesdayEnd() const;
    QTime TuesdayEnd() const;
    void setTuesdayEnd(const QString &newTuesdayEnd);

    QString wednesdayStart() const;
    QTime WednesdayStart() const;
    void setWednesdayStart(const QString &newWednesdayStart);

    QString wednesdayEnd() const;
    QTime WednesdayEnd() const;
    void setWednesdayEnd(const QString &newWednesdayEnd);

    QString thursdayStart() const;
    QTime ThursdayStart() const;
    void setThursdayStart(const QString &newThursdayStart);

    QString thursdayEnd() const;
    QTime ThursdayEnd() const;
    void setThursdayEnd(const QString &newThursdayEnd);

    QString fridayStart() const;
    QTime FridayStart() const;
    void setFridayStart(const QString &newFridayStart);

    QString fridayEnd() const;
    QTime FridayEnd() const;
    void setFridayEnd(const QString &newFridayEnd);

    QString saterdayStart() const;
    QTime SaturdayStart() const;
    void setSaterdayStart(const QString &newSaterdayStart);

    QString saturedayEnd() const;
    QTime SaturdayEnd() const;
    void setSaturedayEnd(const QString &newSaturedayEnd);

    QString sundayStart() const;
    QTime SundayStart() const;
    void setSundayStart(const QString &newSundayStart);

    QString sundayEnd() const;
    QTime SundayEnd() const;
    void setSundayEnd(const QString &newSundayEnd);

    bool isWorkingDay(QDateTime date);
    QTime getStartTime(QDateTime date);
    QTime getEndTime(QDateTime date);


signals:

    void PlanMondayChanged();
    void planTuesdayChanged();

    void planWednesDayChanged();

    void planThursdayChanged();

    void planFridayChanged();

    void planSaturdayChanged();

    void planSundayChanged();

    void mondayStartChanged();

    void mondayEndChanged();

    void tuesdayStartChanged();

    void tuesdayEndChanged();

    void wednesdayStartChanged();

    void wednesdayEndChanged();

    void thursdayStartChanged();

    void thursdayEndChanged();

    void fridayStartChanged();

    void fridayEndChanged();

    void saterdayStartChanged();

    void saturedayEndChanged();

    void sundayStartChanged();

    void sundayEndChanged();

private:
    bool m_PlanMonday;
    bool m_planTuesday;
    bool m_planWednesDay;
    bool m_planThursday;
    bool m_planFriday;
    bool m_planSaturday;
    bool m_planSunday;
    QTime m_mondayStart;
    QTime m_mondayEnd;
    QTime m_tuesdayStart;
    QTime m_tuesdayEnd;
    QTime m_wednesdayStart;
    QTime m_wednesdayEnd;
    QTime m_thursdayStart;
    QTime m_thursdayEnd;
    QTime m_fridayStart;
    QTime m_fridayEnd;
    QTime m_saterdayStart;
    QTime m_saturedayEnd;
    QTime m_sundayStart;
    QTime m_sundayEnd;
};

#endif // USERSETTINGS_H
