#include "Defines.h"

QString durationToString(int duration){
    bool minus = false;
    if(duration < 0){
        minus = true;
        duration = duration * -1;
    }
    int hours = 0;
    int minutes = 0;
    while(duration >= 60){
        minutes++;
        duration = duration - 60;
        if(minutes >= 60){
            minutes = 0;
            hours++;
        }
    }

    QString str_hours = QString::number(hours);
    if(hours < 10){
        str_hours = "0"+ QString::number(hours);
    }
    QString str_minutex = QString::number(minutes);
    if(minutes < 10){
        str_minutex = "0"+ QString::number(minutes);
    }

    QString retString = str_hours +":" + str_minutex;
    if(minus){
        retString = "-" + str_hours +":"+ str_minutex;
    }
    return retString;
}



int durationFromString(QString duration){
    QStringList tmp = duration.split(":");
    if(tmp.size() != 2){
        int bp = 0;
        return 0;
    }
    int hours = tmp[0].toInt();
    int minutes = tmp[1].toInt();


    int ret = hours * 60;
    ret = ret + minutes;
    ret = ret * 60;
    return ret;
}

QDateTime NullDate(){
    return QDateTime::fromSecsSinceEpoch(0);
}
