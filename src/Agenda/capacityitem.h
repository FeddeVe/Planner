#ifndef CAPACITYITEM_H
#define CAPACITYITEM_H

#include <QObject>
#include <QDateTime>
#include <QQmlEngine>

class CapacityItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString month READ month WRITE setMonth NOTIFY monthChanged);
    Q_PROPERTY(QString capPercentage READ capPercentage WRITE setCapPercentage NOTIFY capPercentageChanged);
    Q_PROPERTY(QString capColor READ capColor WRITE setCapColor NOTIFY capColorChanged);
    Q_PROPERTY(QString month READ month WRITE setMonth NOTIFY monthChanged);
    Q_PROPERTY(QString workabledHours READ workabledHours NOTIFY workabledHoursChanged);
    Q_PROPERTY(QString hoursFromLastMoth READ hoursFromLastMoth NOTIFY hoursFromLastMothChanged);
    Q_PROPERTY(QString plannedHours READ plannedHours NOTIFY plannedHoursChanged);
    Q_PROPERTY(QString workedHours READ workedHours NOTIFY workedHoursChanged);
    Q_PROPERTY(QString resultHours READ resultHours  NOTIFY resultHoursChanged);
    Q_PROPERTY(bool isCurMonth READ isCurMonth NOTIFY isCurMonthChanged);
    Q_PROPERTY(float percentage READ percentage NOTIFY percentageChanged)


public:
    explicit CapacityItem(QString m_month,
                          QString m_capPercentage,
                          QString m_capColor,
                          QString m_workabledHours,
                          QString m_hoursFromLastMoth,
                          QString m_plannedHours,
                          QString m_workedHours,
                          QString m_resultHours,
                           bool m_isCurMonth,float m_percentage,
                          QObject *parent = nullptr);

    QString month() const;
    void setMonth(const QString &newMonth);

    QString capPercentage() const;
    void setCapPercentage(const QString &newCapPercentage);

    QString capColor() const;
    void setCapColor(const QString &newCapColor);

    QString workabledHours() const;

    QString hoursFromLastMoth() const;

    QString plannedHours() const;

    QString workedHours() const;

    QString resultHours() const;


    bool isCurMonth() const;

    float percentage() const;

signals:

    void monthChanged();
    void capPercentageChanged();

    void capColorChanged();

    void workabledHoursChanged();

    void hoursFromLastMothChanged();

    void plannedHoursChanged();

    void workedHoursChanged();

    void resultHoursChanged();

    void isCurMonthChanged();

    void percentageChanged();

private:
   // QDateTime m_startDate;
    QString m_month;
    QString m_capPercentage;
    QString m_capColor;
    QString m_workabledHours;
    QString m_hoursFromLastMoth;
    QString m_plannedHours;
    QString m_workedHours;
    QString m_resultHours;
    bool m_isCurMonth;
    float m_percentage;
};

#endif // CAPACITYITEM_H
