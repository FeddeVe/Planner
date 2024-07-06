#ifndef CAPACITYMODEL_H
#define CAPACITYMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QThread>
#include <QColor>

#include "capacityitem.h"
#include "agenda.h"
#include "../Defines.h"

class CapacityModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool tmpyActive READ tmpyActive WRITE setTmpyActive NOTIFY tmpyActiveChanged);
    Q_PROPERTY(bool isLoading READ isLoading WRITE setIsLoading NOTIFY isLoadingChanged);

public:
    explicit CapacityModel(Agenda *agenda, QObject *parent = nullptr);

    enum RoleNames {
        MonthNameRole = Qt::UserRole,
        CapPercentageRol = Qt::UserRole+2,
        WorkableHoursRole = Qt::UserRole+3,
        HoursFromLastMonthRole = Qt::UserRole + 4,
        PlannedHoursRole = Qt::UserRole + 5,
        WorkedHoursRole = Qt::UserRole + 6,
        ResultHoursRole = Qt::UserRole + 7,
        BoxColorRole = Qt::UserRole + 8,
        CurMonthRole = Qt::UserRole + 9,
        PercentRole = Qt::UserRole + 10
    };

    Q_INVOKABLE CapacityItem *get(int row);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    bool tmpyActive() const;
    void setTmpyActive(bool newTmpyActive);

    bool isLoading() const;
    void setIsLoading(bool newIsLoading);



    bool exit;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
     void Process(bool save);
    void DBDebug(QJsonObject msg);

private:
    Agenda *m_agenda;
    QVector<CapacityItem*>m_data;
    QHash<int, QByteArray> m_roleNames;


    bool m_isLoading;
    QString monthToString(int month);



    bool m_tmpyActive;

signals:

    void tmpyActiveChanged();

    void isLoadingChanged();

};

#endif // CAPACITYMODEL_H
