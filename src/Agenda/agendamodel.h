#ifndef AGENDAMODEL_H
#define AGENDAMODEL_H

#include <QObject>

class AgendaModel : public QObject
{
    Q_OBJECT
public:
    explicit AgendaModel(QObject *parent = nullptr);

signals:

};

#endif // AGENDAMODEL_H
