#ifndef APPOINTMENTLOG_H
#define APPOINTMENTLOG_H

#include <QObject>
#include <QAbstractListModel>
#include <QMutex>
#include <QQmlEngine>

#include "appointmentlogitem.h"
#include "appointment.h"

QT_FORWARD_DECLARE_CLASS(AgendaBlock);

class AppointmentLog : public QAbstractListModel
{
    Q_OBJECT
public:

    enum RoleNames {
        IDRole = Qt::UserRole
    };

    explicit AppointmentLog(Appointment *appointment, DBManager *db,  QObject *parent = nullptr);

    void LoadData();

    void Publish(AppointmentLogItem *item);

    void ClearPlan(AgendaBlock *startBlock);
    void AgendaPublish(AgendaBlock *startBlock, AgendaBlock *endBlock);
    void AgendaPublishFinished();
    void AppointmentIDChanged();


    Q_INVOKABLE void loadModel(const QString SearchValue);
    Q_INVOKABLE AppointmentLogItem *get(int row) const;

    int count() const;


    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    QMutex m;
    QVector<AppointmentLogItem*>m_data;
    QHash<int, QByteArray> m_roleNames;
    Appointment *m_appointment;
    DBManager *m_db;

    void SortList();

signals:

public slots:
    void AfterLoad(QJsonObject data);
};

#endif // APPOINTMENTLOG_H
