#ifndef PLANNERTEMPLATES_H
#define PLANNERTEMPLATES_H

#include <QObject>
#include <QAbstractListModel>

#include "../Defines.h"
#include "plannertemplate.h"

class PlannerTemplates : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum RoleNames {
        MSIDRole = Qt::UserRole+1,
        NameRole = Qt::UserRole+2,
        PlanAsRole = Qt::UserRole + 3
    };

     explicit PlannerTemplates(Appointments *appointments, QObject *parent = nullptr);

    void LoadModel();

    Q_INVOKABLE PlannerTemplate *get(int row) const;

    int count() const;


    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    QMutex m;
    QVector<PlannerTemplate*>m_data;
    QHash<int, QByteArray> m_roleNames;
    Appointments *appointments;

signals:
    void countChanged();
};


#endif // PLANNERTEMPLATES_H
