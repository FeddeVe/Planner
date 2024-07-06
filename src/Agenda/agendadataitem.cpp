#include "agendadataitem.h"

AgendaDataItem::AgendaDataItem(qint64 msid, qint64 blockID, quint64 blockStartTime, qint64 blockEndID, int isClosed, int type, int typeID, QObject *parent)
    : QObject{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    this->m_msid = msid;
    this->m_blockID = blockID;
    this->m_blockStartTime = blockStartTime;
    this->m_endBlockId = blockEndID;
    this->m_isClosed = isClosed;
    this->m_type = type;
    this->m_typeID = typeID;
    this->m_isSaved = true;
}

qint64 AgendaDataItem::msid() const
{
    return m_msid;
}

void AgendaDataItem::setMsid(qint64 newMsid)
{
    if (m_msid == newMsid)
        return;
    m_msid = newMsid;
    emit msidChanged();
}

quint64 AgendaDataItem::blockStartTime() const
{
    return m_blockStartTime;
}

void AgendaDataItem::setBlockStartTime(quint64 newBlockStartTime)
{
    if (m_blockStartTime == newBlockStartTime)
        return;
    m_blockStartTime = newBlockStartTime;
    emit blockStartTimeChanged();
}

qint64 AgendaDataItem::endBlockId() const
{
    return m_endBlockId;
}

void AgendaDataItem::setEndBlockId(qint64 newEndBlockId)
{
    if (m_endBlockId == newEndBlockId)
        return;
    m_endBlockId = newEndBlockId;
    emit endBlockIdChanged();
}

qint64 AgendaDataItem::blockID() const
{
    return m_blockID;
}

void AgendaDataItem::setBlockID(qint64 newBlockID)
{
    if (m_blockID == newBlockID)
        return;
    m_blockID = newBlockID;
    emit blockIDChanged();
}



int AgendaDataItem::isClosed() const
{
    return m_isClosed;
}

void AgendaDataItem::setIsClosed(int newIsClosed)
{
    if (m_isClosed == newIsClosed)
        return;
    m_isClosed = newIsClosed;
    emit isClosedChanged();
}

int AgendaDataItem::type() const
{
    return m_type;
}

void AgendaDataItem::setType(int newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

int AgendaDataItem::typeID() const
{
    return m_typeID;
}

void AgendaDataItem::setTypeID(int newTypeID)
{
    if (m_typeID == newTypeID)
        return;
    m_typeID = newTypeID;
    emit typeIDChanged();
}

bool AgendaDataItem::isSaved() const
{
    return m_isSaved;
}

void AgendaDataItem::setIsSaved(bool newIsSaved)
{
    if (m_isSaved == newIsSaved)
        return;
    m_isSaved = newIsSaved;
    emit isSavedChanged();
}

bool AgendaDataItem::checkSave(qint64 blockID, qint64 endBlockId, int isClosed, int type, int typeID){
    if(m_blockID != blockID){
        this->setIsSaved(false);
        return false;
    }
    if(m_endBlockId != endBlockId){
        this->setIsSaved(false);
        return false;
    }
    if(m_isClosed != isClosed){
        this->setIsSaved(false);
        return false;
    }
    if(m_type != type){
        this->setIsSaved(false);
        return false;
    }
    if(m_typeID != typeID){
        this->setIsSaved(false);
        return false;
    }

    this->setIsSaved(true);
    return true;
}
