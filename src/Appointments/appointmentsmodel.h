#ifndef APPOINTMENTSMODEL_H
#define APPOINTMENTSMODEL_H

#include <QObject>

class AppointmentsModel : public QObject
{
    Q_OBJECT
public:
    explicit AppointmentsModel(QObject *parent = nullptr);

signals:

};

#endif // APPOINTMENTSMODEL_H
