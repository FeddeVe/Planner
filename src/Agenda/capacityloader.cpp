#include "capacityloader.h"

CapacityLoader::CapacityLoader(CapacityModel *model, QObject *parent)
    : QObject{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    this->m_model = model;
}

void CapacityLoader::exit(){
    this->m_model->exit = true;
}

void CapacityLoader::process(){
    this->m_model->exit = true;
    while(m_model->isLoading()){
       //
        QThread::msleep(1);
        //qApp->processEvents();
    }
    this->m_model->Process(false);
    emit this->finished();
}



