#include "dbmanager.h"

DBManager::DBManager(QObject *parent)
    : QObject{parent}
{
    this->DBInfo = new db_info();
    this->Server = "http://192.168.2.251/Planner/";  
    this->m_serverError = false;
    this->m_serverErrorText = "";
    this->m_loginRequired = false;
    this->m_loginRunning = false;
    this->network = new QNetworkAccessManager(this);
    this->last_msg_recieved = 0;
    this->LoadSession();
   // this->GetState();
   // this->Run();
}

void DBManager::LoadSession(){

    QString fileloc = QDir::currentPath() +"/Session.dat";
    QFile file(fileloc);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open bin file for reading";
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QDataStream stream(data);
    stream.setVersion(QDataStream::Qt_6_5);
    stream >> this->DBInfo->username;
    stream >> this->DBInfo->token;
    stream >> this->DBInfo->tokenIndex;
    stream >> this->DBInfo->serverID;
    stream >> this->DBInfo->userID;
    int bp = 0;
    bp++;
}

void DBManager::SaveSession(){
    QByteArray bytearray;
    QDataStream stream(&bytearray, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_6_5);
    stream << this->DBInfo->username;
    stream << this->DBInfo->token;
    stream << this->DBInfo->tokenIndex;
    stream << this->DBInfo->serverID;
    stream << this->DBInfo->userID;

    QString fileloc = QDir::currentPath() +"/Session.dat";
    QFile file(fileloc);

    if(file.open(QIODevice::ReadWrite)) {
      //  QTextStream stream(&file);
        file.write(bytearray);
        file.close();
    }
}

void DBManager::GetState(){
    DBRequest *request = new DBRequest(RequestTypes::Welcome, QJsonObject(), this);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(handleGetState(QJsonObject)));
    this->AddRequest(request);
}

void DBManager::handleGetState(QJsonObject data){
    DBRequest *request = new DBRequest(RequestTypes::CheckLogin, QJsonObject(), this);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(handleLogin(QJsonObject)));
    this->AddRequest(request);
}

void DBManager::handleLogin(QJsonObject data){
    QString ok = data.value("msg").toString();
    if(ok == "OK"){
        emit this->LoginOk();
         this->setloginRequired(false);
    }

    int bp  =0;
    bp++;
}

void DBManager::Run(){
    this->quit = false;

    QThread *thread = QThread::create([this]{

                while (!this->quit) {
            if(QDateTime::currentSecsSinceEpoch() - this->last_msg_recieved > 60){
                this->last_msg_recieved = QDateTime::currentSecsSinceEpoch();
                this->GetState();
            }

            DBRequest *dbrequest = NULL;
            this->request_mutex.lock();
            if(this->request_list.size() > 0){
                    dbrequest = this->request_list[0];
            }
                    this->request_mutex.unlock();
            if(dbrequest != NULL){
            QNetworkRequest request;
                    request.setUrl(QUrl(this->Server));
            request.setHeader(QNetworkRequest::ContentTypeHeader,
                              "application/json");


            dbrequest->postData.insert("ID", dbrequest->RequestType);
            dbrequest->postData.insert("UserID", this->DBInfo->userID);

            QString checkString = QString::number(this->DBInfo->userID);
            checkString.append(this->DBInfo->serverID);
            checkString.append(this->DBInfo->token);
           // checkString.append(QString::number(this->DBInfo->tokenIndex));
            QCryptographicHash hash(QCryptographicHash::Sha256);
            hash.addData(checkString.toStdString());
            QByteArray result = hash.result();
            dbrequest->postData.insert("token", QString(result.toHex().toBase64()));

            QJsonDocument doc(dbrequest->postData);
            QByteArray postData = doc.toJson();

           // qDebug() << "postData: " << postData;

            QNetworkReply* reply = this->network->post(request, postData);

            bool waiting = reply->isFinished();
            int count = 0;
            bool TimeOut = false;
            while (!waiting) {
                    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
                    count++;
                    waiting = reply->isFinished();
                    QThread::msleep(1);
                    if (count > 5000) {/// wait 10 seconds
                        TimeOut = true;
                        waiting = true;
                    }
            }
            int bp = 0;
            bp++;
            if(reply->error()){
                    qDebug() << reply->errorString();
                    qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                    this->setServerError(true);
                    this->setserverErrorText(reply->errorString());
                    bp++;
            }else{
                    if(TimeOut){
                        qDebug() << "SERVER NOT RESPONDING";
                        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                        this->setServerError(true);
                        this->setserverErrorText("Server not responding");
                         bp++;
                    }else{
                         this->last_msg_recieved = QDateTime::currentSecsSinceEpoch();

             //   qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
             //   qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
             //   qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
             //   qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
              //  qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

                    if(this->handleMessage(reply->readAll(), dbrequest)){
                    this->setserverErrorText("");
                    this->setServerError(false);
                    this->request_mutex.lock();
                    this->request_list[0]->deleteLater();
                    this->request_list.erase(this->request_list.begin());
                    this->request_mutex.unlock();
                    emit this->waitingListChanged();
                }
                bp++;
              }
            }


 }
                // Process the data to the dispatcher.
                // SimConnect_CallDispatch could also be used.
                // https://docs.flightsimulator.com/html/Programming_Tools/SimConnect/API_Reference/General/SimConnect_GetNextDispatch.htm

 if(this->request_list.size() > 0){
               // QThread::msleep(1);
 }else{
            QThread::msleep(500);
 }

            }

    });

    thread->start();
}

bool DBManager::handleMessage(QByteArray data, DBRequest *request){
    qDebug() << request->postData;
    qDebug() << data;
    QJsonDocument itemDoc = QJsonDocument::fromJson(data);
    QJsonObject rootObject = itemDoc.object();
    int statusCode = rootObject.value("statusCode").toInt();
    if(statusCode == 0){
        this->DBInfo->serverID = rootObject["serverId"].toString();
        this->DBInfo->tokenIndex = rootObject["index"].toInt();
        this->SaveSession();
        quint64 JLE = rootObject["JLE"].toString().toULongLong();
        emit this->JLERecieved(JLE);
        QJsonObject data = rootObject.value("data").toObject();
        emit request->finished(data);
        return true;
    }else if(statusCode == 1){
        //login required
        this->setloginRequired(true);
        int bp = 0;
        bp++;
        this->DBInfo->serverID = rootObject["serverId"].toString();
        QJsonObject data = rootObject.value("data").toObject();
        emit request->finished(data);
        return true;
    }else if(statusCode == 3){
        //Welcome Response
        this->DBInfo->serverID = rootObject["serverId"].toString();
        quint64 JLE = rootObject["JLE"].toString().toULongLong();
        emit this->JLERecieved(JLE);
       // this->DBInfo->tokenIndex = rootObject["index"].toInt();
       // this->SaveSession();
        QJsonObject data = rootObject.value("data").toObject();
        emit request->finished(data);
        return true;
    }else{
        //handle status code
        this->DBInfo->serverID = rootObject["serverId"].toString();
        this->DBInfo->tokenIndex = rootObject["index"].toInt();
        this->SaveSession();
        QJsonObject data = rootObject.value("data").toObject();
        emit request->finished(data);
        return true;
        int bp = 0;
        bp++;
    }

    return false;
}

void DBManager::AddRequest(DBRequest *request){
    this->request_mutex.lock();
    this->request_list.push_back(request);
    this->request_mutex.unlock();
    emit this->waitingListChanged();
}

void DBManager::InsertRequest(DBRequest *request){
    this->request_mutex.lock();
    if(this->request_list.size() > 1){
    this->request_list.insert(1,request);
    }else{
    this->request_list.push_back(request);
    }
    this->request_mutex.unlock();
    emit this->waitingListChanged();
}

bool DBManager::serverError() const{
    return m_serverError;
}
void DBManager::setServerError(bool serverError){
    if(m_serverError == serverError){
        return;
    }
    m_serverError = serverError;
    emit(this->serverErrorChanged());
}

QString DBManager::serverErrorText() const{
    return m_serverErrorText;
}
void DBManager::setserverErrorText(QString serverError){
    if(m_serverErrorText == serverError){
        return;
    }
    m_serverErrorText = serverError;
    emit(this->serverErrorTextChanged());
}

bool DBManager::loginRequired() const{
    return m_loginRequired;
}
void DBManager::setloginRequired(bool loginRequired){
    if(m_loginRequired == loginRequired){
        return;
    }
    m_loginRequired = loginRequired;
    emit(this->loginRequiredChanged());
}

QString DBManager::userName(){
    return this->DBInfo->username;
}

void DBManager::setuserName(QString username){
    if(this->DBInfo->username == username){
        return;
    }
    this->DBInfo->username = username;
    this->SaveSession();
    emit(this->userNameChanged());
}

QString DBManager::password(){
    return "";
}

void DBManager::setpassword(QString password){
    this->DBInfo->password = password;
}

bool DBManager::loginRunning(){
    return this->m_loginRunning;
}

void DBManager::setloginRunning(bool running){
    if(m_loginRunning == running){
        return;
    }
    m_loginRunning = running;
    emit this->loginRunningChanged();
}

void DBManager::login(){
    this->setloginRunning(true);
    this->DBInfo->token = "";
    this->DBInfo->userID = 0;
    this->DBInfo->tokenIndex = 0;

    QJsonObject data;
    data.insert("UserName", this->DBInfo->username);
    QString pass = this->DBInfo->password;
    //pass+=this->DBInfo->password;
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(pass.toStdString());
    QByteArray result = hash.result();

    QString check =this->DBInfo->serverID;
    check += QString(result.toHex().toBase64());



    data.insert("cred", QString(result.toHex().toBase64()));

    DBRequest *request = new DBRequest(RequestTypes::Login, data, this);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(handleAfterLogin(QJsonObject)));
    this->AddRequest(request);
    int bp = 0;
    bp++;



}

void DBManager::handleAfterLogin(QJsonObject data){
    this->setloginRunning(false);
    QString ok = data.value("msg").toString();
    if(ok == "OK"){
        this->DBInfo->userID = data.value("userid").toInt();
        this->DBInfo->token = data.value("UserToken").toString();
        this->DBInfo->tokenIndex = data.value("index").toInt();
        this->SaveSession();
    }else{
        //not ok
    }

    DBRequest *request = new DBRequest(RequestTypes::CheckLogin, QJsonObject(), this);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(handleLogin(QJsonObject)));
    this->AddRequest(request);
    int bp = 0;
    bp++;
}






int DBManager::waitingList() const
{
    return this->request_list.size();
}

