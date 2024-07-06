#ifndef AGENDABLOCK_H
#define AGENDABLOCK_H

#include <QObject>
#include <QDateTime>

#include "agendablockitem.h"

QT_FORWARD_DECLARE_CLASS(AgendaBlockItem);

class AgendaBlock : public QObject
{
    Q_OBJECT
public:
    explicit AgendaBlock(qint64 blockID, QDateTime startTime, QDateTime endTime, bool isPlannable, bool isWorkingDay,bool isFromTMPY, QObject *parent = nullptr);
    ~AgendaBlock();

    qint64 blockID;
    QDateTime m_startTime;
    QDateTime m_endTime;
    bool isPlannable;
    bool isWorkingDay;
    bool isFree() const;
    int getCount() const;
    int getdayXpos() const;
    void AddBlockItem(AgendaBlockItem *item);
    int itemHeight;
     QVector<AgendaBlockItem*>items;
    int overurenvorigemaand;
     bool isFromTMPY;
private:



signals:

};

#endif // AGENDABLOCK_H
