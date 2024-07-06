#ifndef AGENDAWTA_H
#define AGENDAWTA_H

#include <QObject>
#include <QVector>
#include <QDateTime>

#include "../Appointments/appointments.h"
#include "agenda.h"


class AgendaWTA : public QObject
{
    Q_OBJECT
public:
    explicit AgendaWTA(QObject *parent = nullptr);

    void process(Agenda *agenda);

private:
    Agenda *m_agenda;



    int check_duration(qint64 startIndex); // returns no of blocks
    void check_rest(qint64 startIndex, int duration);

    void handle_rust8(qint64 workduration);

signals:

};

#endif // AGENDAWTA_H
