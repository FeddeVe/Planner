#ifndef APPOINTMENTERRORMODEL_H
#define APPOINTMENTERRORMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "appointments.h"
#include "appointmenterroritem.h"

QT_FORWARD_DECLARE_CLASS(Appointments);

class AppointmentErrorModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged);

public:

    enum RoleNames {
        TitleRole = Qt::UserRole,
        JobRole = Qt::UserRole+2,
        IDRole = Qt::UserRole+3,
        MSGRole = Qt::UserRole+4
    };

    explicit AppointmentErrorModel(QObject *parent = nullptr);

    void LoadData(Appointments *appointements);

    int count() const;

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    QVector<AppointmentErrorItem*>m_data;

    int m_count;
    QHash<int, QByteArray> m_roleNames;

signals:
    void countChanged();

public:


signals:

};

#endif // APPOINTMENTERRORMODEL_H
