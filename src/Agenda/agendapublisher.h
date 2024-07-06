#ifndef AGENDAPUBLISHER_H
#define AGENDAPUBLISHER_H

#include <QObject>

#include "agenda.h"


class AgendaPublisher : public QObject
{
    Q_OBJECT
public:
    explicit AgendaPublisher( QObject *parent = nullptr);

    void planAgenda();

    void process();

private:
    bool stopandrestart;
    Agenda *m_agenda;

signals:

};

#endif // AGENDAPUBLISHER_H
