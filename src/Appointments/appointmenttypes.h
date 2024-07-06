#ifndef APPOINTMENTTYPES_H
#define APPOINTMENTTYPES_H

#include <QObject>
#include <QAbstractListModel>
#include <QQmlEngine>

#include "appointmenttype.h"

class AppointmentTypes : public QAbstractListModel
{
    Q_OBJECT
public:

    enum RoleNames {
        IDRole = Qt::UserRole,
        LabelRole = Qt::UserRole+2,
        ColorRole = Qt::UserRole+3,
        CalcRole = Qt::UserRole + 4
    };

    explicit AppointmentTypes(QObject *parent = nullptr);

    void LoadModel();
    Q_INVOKABLE AppointmentType *get(int row);
    AppointmentType *getByID(int ID);
    int GetBlockIndex();
    int GetIndex(AppointmentType *type);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;


private:
    void LoadData();
    QVector<AppointmentType*>m_data;
    QHash<int, QByteArray> m_roleNames;




signals:

};

#endif // APPOINTMENTTYPES_H
