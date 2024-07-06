#ifndef AGENDADATAITEM_H
#define AGENDADATAITEM_H

#include <QObject>
#include <QQmlEngine>

class AgendaDataItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint64 msid READ msid WRITE setMsid NOTIFY msidChanged);
    Q_PROPERTY(qint64 blockID READ blockID WRITE setBlockID NOTIFY blockIDChanged);
    Q_PROPERTY(quint64 blockStartTime READ blockStartTime WRITE setBlockStartTime NOTIFY blockStartTimeChanged);
    Q_PROPERTY(qint64 endBlockId READ endBlockId WRITE setEndBlockId NOTIFY endBlockIdChanged);
    Q_PROPERTY(int isClosed READ isClosed WRITE setIsClosed NOTIFY isClosedChanged);
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged);
    Q_PROPERTY(int typeID READ typeID WRITE setTypeID NOTIFY typeIDChanged);
    Q_PROPERTY(bool isSaved READ isSaved NOTIFY isSavedChanged);


public:
    explicit AgendaDataItem(qint64 msid, qint64 blockID, quint64 blockStartTime, qint64 blockEndID, int isClosed, int type, int typeID, QObject *parent = nullptr);

    qint64 msid() const;
    void setMsid(qint64 newMsid);

    quint64 blockStartTime() const;
    void setBlockStartTime(quint64 newBlockStartTime);

    qint64 endBlockId() const;
    void setEndBlockId(qint64 newEndBlockId);

    qint64 blockID() const;
    void setBlockID(qint64 newBlockID);

    int isClosed() const;
    void setIsClosed(int newIsClosed);

    int type() const;
    void setType(int newType);

    int typeID() const;
    void setTypeID(int newTypeID);

    bool isSaved() const;
    bool checkSave(qint64 blockID, qint64 endBlockId, int isClosed, int type, int typeID);
    void setIsSaved(bool newIsSaved);


signals:

    void msidChanged();
    void blockStartTimeChanged();

    void endBlockIdChanged();

    void blockIDChanged();



    void isClosedChanged();

    void typeChanged();

    void typeIDChanged();

    void isSavedChanged();

private:
    qint64 m_msid;
    quint64 m_blockStartTime;
    qint64 m_endBlockId;
    qint64 m_blockID;

    int m_isClosed;
    int m_type;
    int m_typeID;
    bool m_isSaved;
};

#endif // AGENDADATAITEM_H
