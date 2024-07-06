#ifndef AGENDADAYITEM_H
#define AGENDADAYITEM_H

#include <QObject>
#include <QDateTime>
#include <QAbstractListModel>
#include <QMutex>
#include <QMutexLocker>

#include "../Agenda/agendablock.h"
#include "agendadayitemsecondmodel.h"
#include "agendadisplayitem.h"

QT_FORWARD_DECLARE_CLASS(AgendaBlock);
QT_FORWARD_DECLARE_CLASS(AgendaDisplayItem);

class AgendaDayItem : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString dayName READ dayName NOTIFY dayNameChanged);
    Q_PROPERTY(QString datum READ datum NOTIFY datumChanged);
    Q_PROPERTY(bool isWorkingDay READ isWorkingDay NOTIFY isWorkingDayChanged);
    Q_PROPERTY(bool isSelected READ isSelected WRITE setisSelected NOTIFY isSelectedChanged);
    Q_PROPERTY(bool isFromTMPY READ isFromTMPY WRITE setIsFromTMPY NOTIFY isFromTMPYChanged);


public:
    explicit AgendaDayItem(QDate datum, bool isWorkingDay,bool isFromTMPY, QObject *parent = nullptr);

    enum RoleNames {
        xPosRole = Qt::UserRole,
        xWidthRole = Qt::UserRole+2,
        xHeightRole = Qt::UserRole+3,
        xTitleRole = Qt::UserRole+4,
        xJobNoRole = Qt::UserRole+5,
        xJobTitleRole = Qt::UserRole+6,
        xBoxColor = Qt::UserRole+7,
        xDateRole = Qt::UserRole+8,
        xendDateRole = Qt::UserRole+9
    };

    Q_INVOKABLE AgendaDisplayItem *get(int row) const;
    void AddBlock(AgendaBlock *block);
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;


    QString dayName() const;


    QString datum() const;
    QDate date();

    bool isWorkingDay() const;


    bool isSelected() const;
    void setisSelected(bool newIsSelected);

    void combineData();
    bool contains(AgendaBlock *a, AgendaBlockItem *contains);
    bool exist(AgendaDisplayItem *a);



    bool isFromTMPY() const;
    void setIsFromTMPY(bool newIsFromTMPY);

     QVector<AgendaDisplayItem*> m_data;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;

signals:

    void dayNameChanged();
    void datumChanged();

    void isWorkingDayChanged();

    void isSelectedChanged();

    void isFromTMPYChanged();

private:

    QDate m_date;
    bool m_isWorkingDay;
    bool m_isSelected;

    QVector<AgendaBlock*> blocks;
    QHash<int, QByteArray> m_roleNames;


    bool m_isFromTMPY;
};

#endif // AGENDADAYITEM_H
