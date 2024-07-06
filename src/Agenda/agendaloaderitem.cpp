#include "agendaloaderitem.h"

AgendaLoaderItem::AgendaLoaderItem(LoaderType type, Appointment *appointment, QDateTime starttime, QDateTime endtime, bool isClosed, QObject *parent)
    : QObject{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    this->type = type;
    this->app = appointment;
    this->starttime = starttime;
    this->endtime = endtime;
    this->isClosed = isClosed;
}
