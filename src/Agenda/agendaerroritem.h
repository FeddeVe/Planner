#ifndef AGENDAERRORITEM_H
#define AGENDAERRORITEM_H

#include <QObject>
#include <QDateTime>
#include <QQmlEngine>

class AgendaErrorItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString datum READ datum NOTIFY datumChanged);
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged);
    Q_PROPERTY(bool isTMPY READ isTMPY NOTIFY isTMPYChanged);

public:
    explicit AgendaErrorItem(QDateTime datum, QString errorText, bool isTMPY, QObject *parent = nullptr);

    QString datum() const;
    QDateTime Datum() const;

    QString message() const;
    void setMessage(const QString &newMessage);

    bool isTMPY() const;

signals:

    void datumChanged();
    void messageChanged();

    void isTMPYChanged();

private:
    QDateTime m_datum;
    QString m_message;
    bool m_isTMPY;
};

#endif // AGENDAERRORITEM_H
