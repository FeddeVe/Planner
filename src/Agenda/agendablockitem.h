#ifndef AGENDABLOCKITEM_H
#define AGENDABLOCKITEM_H

#include <QObject>
#include "../Appointments/appointment.h"
#include "../Defines.h"



QT_FORWARD_DECLARE_CLASS(Appointment);

class AgendaBlockItem : public QObject
{
    Q_OBJECT

public:


    explicit AgendaBlockItem(qint64 msid, AgendaTypes type, Appointment *appointment, bool isClosed, QObject *parent = nullptr);

    qint64 msid;
    AgendaTypes Type;
    Appointment *appointment;
    bool isClosed;
    bool isSaved;
    bool isDisplayd;




signals:

};

#endif // AGENDABLOCKITEM_H
