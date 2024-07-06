#ifndef APPOINTMENTPLANNER_H
#define APPOINTMENTPLANNER_H

#include <QObject>
#include <QAbstractListModel>

#include "../Agenda/agenda.h"
#include "../Appointments/appointment.h"
#include "appointmentplanneritem.h"

QT_FORWARD_DECLARE_CLASS(AgendaBlock);
QT_FORWARD_DECLARE_CLASS(AppointmentPlannerItem);

class AppointmentPlanner : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString totalDuration READ totalDuration NOTIFY totalDurationChanged);
    Q_PROPERTY(QString workedDuration READ workedDuration NOTIFY workedDurationChanged);
    Q_PROPERTY(QString plannedDuration READ plannedDuration  NOTIFY plannedDurationChanged);
    Q_PROPERTY(QString durationLeft READ durationLeft NOTIFY durationLeftChanged);
    Q_PROPERTY(bool completePlanned READ completePlanned NOTIFY completePlannedChanged);
    Q_PROPERTY(bool agendaErrors READ agendaErrors  NOTIFY agendaErrorsChanged);
    Q_PROPERTY(QString agendaErrorsText READ agendaErrorsText  NOTIFY agendaErrorsTextChanged);

public:
    explicit AppointmentPlanner(Appointment *appointment, Agenda *agenda, QObject *parent = nullptr);

    QString totalDuration() const;

    QString workedDuration() const;

    QString plannedDuration() const;

    QString durationLeft() const;
    int m_DurationLeft;
    int m_DurationResult;

    Q_INVOKABLE QString saveWorkedOn(QString dateTime, QString Duration);

    void DoMagic();

    enum RoleNames {
        DatumRole = Qt::UserRole,
        DurationRole = Qt::UserRole+2,
        StatusRole = Qt::UserRole+3,
        RemarksRole = Qt::UserRole + 4,
        CompletedRole = Qt::UserRole + 5,
        FromTMPYRole = Qt::UserRole + 6,
        IsPastRole = Qt::UserRole + 7
    };



    Q_INVOKABLE AppointmentPlannerItem *get(int row) const;

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    bool completePlanned() const;

    bool agendaErrors() const;

    QString agendaErrorsText() const;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;


private:
    Appointment *appointment;
    Agenda *agenda;
    QVector<AgendaBlock*> agendaBlocks;
    QVector<AppointmentPlannerItem*>m_data;
    QHash<int, QByteArray> m_roleNames;


    QString m_totalDuration;

    QString m_workedDuration;

    QString m_plannedDuration;

    QString m_durationLeft;

    bool m_completePlanned;

    bool m_agendaErrors;

    QString m_agendaErrorsText;

    void combinePlanning();

signals:

    void totalDurationChanged();
    void workedDurationChanged();
    void plannedDurationChanged();
    void durationLeftChanged();
    void completePlannedChanged();
    void agendaErrorsChanged();
    void agendaErrorsTextChanged();

public slots:
    void afterBlockSave(QJsonObject msg);
};

#endif // APPOINTMENTPLANNER_H
