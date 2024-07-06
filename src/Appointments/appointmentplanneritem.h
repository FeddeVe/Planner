#ifndef APPOINTMENTPLANNERITEM_H
#define APPOINTMENTPLANNERITEM_H

#include <QObject>

#include "../Agenda/agenda.h"
#include "../Defines.h"

class AppointmentPlannerItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString datum READ datum WRITE setDatum NOTIFY datumChanged);
    Q_PROPERTY(QString duration READ duration WRITE setDuration NOTIFY durationChanged);
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged);
    Q_PROPERTY(QString remarks READ remarks WRITE setRemarks NOTIFY remarksChanged);
    Q_PROPERTY(bool completed READ completed  NOTIFY completedChanged);
    Q_PROPERTY(bool fromTMPY READ fromTMPY NOTIFY fromTMPYChanged);
    Q_PROPERTY(bool isPast READ isPast WRITE setIsPast NOTIFY isPastChanged);

public:
    explicit AppointmentPlannerItem(QDateTime starttime, bool completed, bool fromtmpy,  QObject *parent = nullptr);

    QString datum() const;
    QDateTime Datum() const;
    void setDatum(const QString &newDatum);

    QString duration() const;
    int Duration() const;
    void setDuration(const QString &newDuration);
    void addDuration(int duration);

    QString status() const;
    void setStatus(const QString &newStatus);

    QString remarks() const;
    void setRemarks(const QString &newRemarks);

    bool completed() const;
    void setCompleted(bool newCompleted);

    bool fromTMPY() const;
   // void setFromTMPY(bool newFromTMPY);

    bool isPast() const;
    void setIsPast(bool newIsPast);


signals:

    void datumChanged();
    void durationChanged();

    void statusChanged();

    void remarksChanged();

    void completedChanged();

    void fromTMPYChanged();

    void isPastChanged();

private:
    QDateTime m_datum;
    int m_duration;
    QString m_status;
    QString m_remarks;
    bool m_completed;
    bool m_fromTMPY;
    bool m_isPast;
};

#endif // APPOINTMENTPLANNERITEM_H
