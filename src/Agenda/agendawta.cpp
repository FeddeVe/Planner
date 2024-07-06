#include "agendawta.h"

AgendaWTA::AgendaWTA(QObject *parent)
    : QObject{parent}
{

}

void AgendaWTA::process(Agenda *agenda){

    m_agenda = agenda;
    //rust
    bool found8rest = false;
    QVector<QDate> rest8list;
    bool found11rest = false;
    bool found32rest = false;
    QVector<QDate> rest32list;
    bool found72rest = false;
    qint64 workDuration = 0;
    qint64 restDuration = 0;
    int lastWorkingDayLength = 0;

    int hours8 = 8*60*60;
    int hours11 = 11*60*60;
    int hours12 = 12*60*60;
    int hours14 = 14*60*60;
    int hours32 = 32*60*60;
    int hours72 = 72*60*60;

    for(int i = 0; i < m_agenda->agendaBlocks.size(); i++){
        AgendaBlock *b = m_agenda->agendaBlocks[i];
        if(b->items.count() > 0){
            if(restDuration < hours8){
                // do nothing kleiner dan 8 uur is geen rust tijd
            }else{
                if((restDuration >= hours8) && (restDuration < hours11)){
                    // rusttijd is 8 uur
                    if(workDuration > hours12){
                        // na een shift van meer dan 12 uur minimaal 24 uur rust
                        // los dit op door een agenda appointment te maken
                        // maak een melding in de error model
                        int bp = 0;
                        bp++;
                    }
                    int bp = 0;
                    bp++;
                }else if((restDuration >= hours11) && (restDuration < hours32)){
                    //rusttijd is 11 uur
                    int bp = 0;
                    bp++;
                }else if((restDuration >= hours32) && (restDuration < hours72)){
                    //rusttijd is 32 uur
                    int bp = 0;
                    bp++;
                }else if((restDuration > hours72)){
                    //rusttijd is 72 uur of groter
                    int bp = 0;
                    bp++;
                }
            }

            restDuration = 0;

            workDuration = workDuration + AGENDABLOCKDURATION;
        }else{
            if(workDuration > hours14){
                int bp = 0;
                bp++;
            }
            lastWorkingDayLength = workDuration;

            workDuration = 0;

            restDuration = restDuration + AGENDABLOCKDURATION;
        }
    }

    int bp = 0;
    bp++;
}



