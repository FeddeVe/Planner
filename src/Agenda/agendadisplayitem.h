#ifndef AGENDADISPLAYITEM_H
#define AGENDADISPLAYITEM_H

#include <QObject>
#include <QDateTime>

#include "../Appointments/appointment.h"
#include "agendablockitem.h"
#include "../Defines.h"

QT_FORWARD_DECLARE_CLASS(Appointment);
QT_FORWARD_DECLARE_CLASS(AgendaBlockItem);

class AgendaDisplayItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title NOTIFY titleChanged);
    Q_PROPERTY(QString jobNo READ jobNo NOTIFY jobNoChanged);
    Q_PROPERTY(QString jobTitle READ jobTitle NOTIFY jobTitleChanged);
    Q_PROPERTY(int xPos READ xPos WRITE setXPos NOTIFY xPosChanged);
    Q_PROPERTY(int xHeight READ xHeight WRITE setXHeight NOTIFY xHeightChanged);
    Q_PROPERTY(int xWidth READ xWidth WRITE setXWidth NOTIFY xWidthChanged);
    Q_PROPERTY(QString boxColor READ boxColor NOTIFY boxColorChanged);
    Q_PROPERTY(QString planDate READ planDate NOTIFY planDateChanged);
    Q_PROPERTY(QString endPlanDate READ endPlanDate NOTIFY endPlanDateChanged);

public:

    explicit AgendaDisplayItem(AgendaTypes type, Appointment *appointment, QDateTime planDate,QDateTime endPlanDate, QObject *parent = nullptr);

    Q_INVOKABLE Appointment *appointment();
    AgendaTypes type;
    QString title() const;

    QString jobNo() const;

    QString jobTitle() const;

    int xPos() const;
    void setXPos(int newXPos);

    int xHeight() const;
    void setXHeight(int newXHeight);

    int xWidth() const;
    void setXWidth(int newXWidth);

    QString boxColor() const;



    QString planDate() const;

    QString endPlanDate() const;

    void setendPlanDate(const QDateTime &newEndPlanDate);

      Appointment *m_appointment;
    QDateTime m_planDate;
    QDateTime m_endplanDate;

signals:

    void titleChanged();
    void jobNoChanged();

    void jobTitleChanged();

    void xPosChanged();

    void xHeightChanged();

    void xWidthChanged();

    void boxColorChanged();

    void planDateChanged();

    void endPlanDateChanged();

    void someThingChanged();

private:
    QString m_title;
    QString m_jobNo;
    QString m_jobTitle;
    int m_xPos;
    int m_xHeight;
    int m_xWidth;
    //QString m_boxColor;



public slots:


};

#endif // AGENDADISPLAYITEM_H
