#ifndef PLANNERTEMPLATEITEM_H
#define PLANNERTEMPLATEITEM_H

#include <QObject>
#include <QQmlEngine>
#include <QAbstractListModel>
#include <QMutex>

#include "../Defines.h"
#include "plannertemplatesubitem.h"
#include "plannertemplate.h"
#include "../Appointments/appointments.h"

QT_FORWARD_DECLARE_CLASS(PlannerTemplate);

class PlannerTemplateItem : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged);
    Q_PROPERTY(int msid READ msid WRITE setMsid NOTIFY msidChanged);
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged);
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged);
    Q_PROPERTY(int planAss READ planAss WRITE setPlanAss NOTIFY planAssChanged);
    Q_PROPERTY(QString clr READ clr WRITE setClr NOTIFY clrChanged);

public:

    enum RoleNames {
        MSIDRole = Qt::UserRole,
        IndexRole = Qt::UserRole+2,
        TitleRole = Qt::UserRole+3,
        DefDeadlineRole = Qt::UserRole + 4,
        CalcDurationRole = Qt::UserRole + 5
    };

    explicit PlannerTemplateItem(int msid, int index, QString label, int appointmentTypeID, PlannerTemplate *Template, Appointments *appointments, QObject *parent = nullptr);

    void LoadModel(const QString SearchValue);

    Q_INVOKABLE PlannerTemplateSubItem *get(int row) const;
    Q_INVOKABLE void addItem();
    Q_INVOKABLE void moveUp();
    Q_INVOKABLE void moveDown();

    void MoveUp(PlannerTemplateSubItem *item);
    void MoveDown(PlannerTemplateSubItem *item);

    int count() const;


    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    int index() const;
    void setIndex(int newIndex);

    int msid() const;
    void setMsid(int newMsid);

    QString label() const;
    void setLabel(const QString &newLabel);

    int planAss() const;
    void setPlanAss(int newPlanAss);

    QString clr() const;
    void setClr(const QString &newClr);

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    QMutex m;
    QVector<PlannerTemplateSubItem*>m_data;
    QHash<int, QByteArray> m_roleNames;

signals:
    void countChanged();

    void indexChanged();

    void msidChanged();

    void labelChanged();

    void planAssChanged();

    void clrChanged();

private:

    Appointments *appointments;
    PlannerTemplate *m_template;
    int m_index;
    int m_msid;

    int m_count;
    QString m_label;
    AppointmentType *m_planAss;
    QString m_clr;
};

#endif // PLANNERTEMPLATEITEM_H
