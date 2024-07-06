#ifndef PLANNERTEMPLATE_H
#define PLANNERTEMPLATE_H

#include <QObject>
#include <QMutex>
#include <QAbstractListModel>

#include "../Defines.h"
#include "plannertemplateitem.h"

QT_FORWARD_DECLARE_CLASS(Appointments);
QT_FORWARD_DECLARE_CLASS(PlannerTemplateSubItem);
QT_FORWARD_DECLARE_CLASS(PlannerTemplateItem);

class PlannerTemplate : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged);
    Q_PROPERTY(int msid READ msid WRITE setMsid NOTIFY msidChanged);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);

public:
    enum RoleNames {
        MSIDRole = Qt::UserRole,
        IndexRole = Qt::UserRole+2,
        LabelRole = Qt::UserRole+3,
        PlanAsRole = Qt::UserRole + 4
    };

    explicit PlannerTemplate(int msid, QString name, Appointments *appointments, QObject *parent = nullptr);

    void LoadModel(const QString SearchValue);

    Q_INVOKABLE PlannerTemplateItem *get(int row) const;
    Q_INVOKABLE void addCatagory();
    Q_INVOKABLE void moveUp(PlannerTemplateItem *item);
    Q_INVOKABLE void moveDown(PlannerTemplateItem *item);

    int count() const;


    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    QString name() const;
    void setName(const QString &newName);


    int msid() const;
    void setMsid(int newMsid);

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    QMutex m;
    QVector<PlannerTemplateItem*>m_data;
    QHash<int, QByteArray> m_roleNames;
    Appointments *appointments;
    QString m_name;


    int m_msid;

    PlannerTemplateItem *insertItem();


signals:
    void countChanged();
    void nameChanged();
    void msidChanged();
};


#endif // PLANNERTEMPLATE_H
