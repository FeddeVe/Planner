#ifndef AGENDABLOCKS_H
#define AGENDABLOCKS_H

#include <QObject>
#include <QMutex>

#include "agendablock.h"
#include "../Appointments/appointmentlogitem.h"
#include "../Defines.h"


class AgendaBlocks : public QObject
{
    Q_OBJECT
public:
    explicit AgendaBlocks(Agenda *agenda, QObject *parent = nullptr);

    bool PublishItem(Appointment *appointment, AppointmentLogItem *logItem);

     QVector<AgendaBlock*>blocks;
private:
    QMutex m;
    Agenda *m_agenda;

    void insertBlocks(qint64 startIndex);
    void addBlock(qint64 endIndex);
    AgendaBlock *CreateBlock(qint64 Index, QDateTime startTime);
signals:

};

#endif // AGENDABLOCKS_H
