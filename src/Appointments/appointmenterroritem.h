#ifndef APPOINTMENTERRORITEM_H
#define APPOINTMENTERRORITEM_H

#include <QObject>

class AppointmentErrorItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged);
    Q_PROPERTY(QString job READ job NOTIFY jobChanged);
    Q_PROPERTY(int id READ id NOTIFY idChanged);
    Q_PROPERTY(QString errMSG READ errMSG NOTIFY errMSGChanged);


public:
    explicit AppointmentErrorItem(QString appTitle, QString job, int appID, QString msg, QObject *parent = nullptr);

    QString title() const;

    QString job() const;

    int id() const;

    QString errMSG() const;

signals:

    void titleChanged();
    void jobChanged();

    void idChanged();

    void errMSGChanged();

private:
    QString m_title;
    QString m_job;
    int m_id;
    QString m_errMSG;
};

#endif // APPOINTMENTERRORITEM_H
