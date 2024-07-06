#ifndef AGENDAITEM_H
#define AGENDAITEM_H

#include <QObject>
#include "agendablock.h"
#include "../Appointments/appointment.h"

QT_FORWARD_DECLARE_CLASS(Appointment);

class AgendaItem : public QObject
{
    Q_OBJECT
public:
    enum AgendaTypes{
        TaskItem,
        AppointmentItem
    } AgendaType;

    explicit AgendaItem(AgendaTypes type, Appointment *appointment, QObject *parent = nullptr);
    ~AgendaItem();
    void SetAgendaBlock(QDateTime startTime, QDateTime endTime, bool isTMPY);
    void ClearPlanning(bool isTMPY);


    QDateTime getEndDateTime() const;
    int getDuration() const;
    QDateTime getStartTime() const;
    int getPlanMode() const;
    bool isPlanned(bool isTMPY) const;
    bool isDeleted() const;
    int getMSID() const;

    Appointment *getAppointmet();



private:
    QVector<AgendaBlock*>agendaBlock;
    Appointment *appointment;


signals:

};

#endif // AGENDAITEM_H
