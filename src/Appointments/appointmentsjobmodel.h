#ifndef APPOINTMENTSJOBMODEL_H
#define APPOINTMENTSJOBMODEL_H

#include <QObject>

class AppointmentsJobModel : public QObject
{
    Q_OBJECT
public:
    explicit AppointmentsJobModel(QObject *parent = nullptr);

signals:

};

#endif // APPOINTMENTSJOBMODEL_H
