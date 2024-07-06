#ifndef AGENDAWTAERROR_H
#define AGENDAWTAERROR_H

#include <QObject>
#include <QDateTime>

class AgendaWTAError : public QObject
{
    Q_OBJECT
public:

    enum ErrorTypes{
        WorkExceedsMax,
    };

    explicit AgendaWTAError(QObject *parent = nullptr);



signals:

};

#endif // AGENDAWTAERROR_H
