#ifndef AGENDADAYITEMMODEL_H
#define AGENDADAYITEMMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "agendadayitem.h"
#include "agenda.h"

QT_FORWARD_DECLARE_CLASS(Agenda);
QT_FORWARD_DECLARE_CLASS(AgendaDayItem);

class AgendaDayItemModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool tmpyActive READ tmpyActive WRITE setTmpyActive NOTIFY tmpyActiveChanged);
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged);
    Q_PROPERTY(int agendaIndex READ agendaIndex WRITE setAgendaIndex NOTIFY agendaIndexChanged);
public:
    explicit AgendaDayItemModel(QObject *parent = nullptr);

    enum RoleNames {
        DayNameRol = Qt::UserRole,
        DayDatumRole = Qt::UserRole+2,
        DayIsWorkingDayRole = Qt::UserRole+3,
        DayIsSelected = Qt::UserRole + 4,
        IndexRole = Qt::UserRole + 5,
        ISTMPYRole = Qt::UserRole + 6
    };

    Q_INVOKABLE AgendaDayItem *get(int row) const;
    Q_INVOKABLE void setIndexAt(QString datetime);

    int indexAt(QDateTime dateTime);

    AgendaDayItem *getByIndex(int index);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    void LoadData(Agenda *agenda);

    bool tmpyActive() const;
    void setTmpyActive(bool newTmpyActive);

    int count() const;
    void setCount(int newCount);

    int agendaIndex() const;
    void setAgendaIndex(int newAgendaIndex);

       QVector<AgendaDayItem*>m_data;
        QDateTime curIndex;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;


private:


    QHash<int, QByteArray> m_roleNames;


    bool m_tmpyActive;



    int m_agendaIndex;


signals:

    void tmpyActiveChanged();
    void countChanged();
    void agendaIndexChanged();
};

#endif // AGENDADAYITEMMODEL_H
