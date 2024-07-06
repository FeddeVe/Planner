#ifndef APPOINTMENTTYPE_H
#define APPOINTMENTTYPE_H

#include <QObject>
#include <QQmlEngine>

class AppointmentType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged);
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged);
    Q_PROPERTY(QString clr READ clr WRITE setClr NOTIFY clrChanged);
    Q_PROPERTY(QString boxclr READ boxclr WRITE setboxclr NOTIFY boxclrChanged)
    Q_PROPERTY(bool calcTime READ calcTime WRITE setCalcTime NOTIFY calcTimeChanged);
public:
    explicit AppointmentType(int index, QString label, QString color, QString boxcolor, bool calcTime, QObject *parent = nullptr);



    int index() const;
    void setIndex(int newIndex);

    QString label() const;
    void setLabel(const QString &newLabel);

    QString clr() const;
    void setClr(const QString &newClr);

    bool calcTime() const;
    void setCalcTime(bool newCalcTime);

    QString boxclr() const;
    void setboxclr(const QString &newBoxclr);

signals:

    void indexChanged();
    void labelChanged();

    void clrChanged();

    void calcTimeChanged();

    void boxclrChanged();

private:
    int m_index;
    QString m_label;
    QString m_clr;
    bool m_calcTime;
    QString m_boxclr;
};

#endif // APPOINTMENTTYPE_H
