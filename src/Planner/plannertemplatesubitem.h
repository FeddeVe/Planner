#ifndef PLANNERTEMPLATESUBITEM_H
#define PLANNERTEMPLATESUBITEM_H

#include <QObject>
#include <QQmlEngine>

#include "../Defines.h"

class PlannerTemplateSubItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int msid READ msid WRITE setMsid NOTIFY msidChanged);
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged);
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged);
    Q_PROPERTY(int defaultDeadline READ defaultDeadline WRITE setDefaultDeadline NOTIFY defaultDeadlineChanged);
    Q_PROPERTY(QString calculatedDuration READ calculatedDuration WRITE setCalculatedDuration NOTIFY calculatedDurationChanged);

public:
    explicit PlannerTemplateSubItem(int msid, int index, QString title, int defDeadline, int calculatedDuration, QObject *parent = nullptr);

    int index() const;
    void setIndex(int newIndex);

    int msid() const;
    void setMsid(int newMsid);

    QString title() const;
    void setTitle(const QString &newTitle);

    int defaultDeadline() const;
    void setDefaultDeadline(int newDefaultDeadline);

    QString calculatedDuration() const;
    int CalculatedDuration() const;
    void setCalculatedDuration(const QString &newCalculatedDuration);
    void SetCalculatedDuration(const int &newCalculatedDuration);

signals:

    void indexChanged();
    void msidChanged();

    void titleChanged();

    void defaultDeadlineChanged();

    void calculatedDurationChanged();

private:

    int m_index;
    int m_msid;
    QString m_title;
    int m_defaultDeadline;
    int m_calculatedDuration;
};


#endif // PLANNERTEMPLATESUBITEM_H
