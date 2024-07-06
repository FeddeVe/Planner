import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {


    id: root
    width: Constants.width
    height: Constants.height

    Rectangle{
        id: mainRect
        x:0
        y:0
        width: root.width
        height: root.height
        color: Style.background

        Appointment_Large{
            id:appointment
           x: 10
           y: 10
           editMode: true
           onStartDateFocusChanged: {
               agenda.positionIndex = agendaManager.dayModel().indexAt(appointment.startDateTime)
           }
        }

        Agenda{
            id: agenda
            x: 10 + appointment.x + appointment.width
            y: 10
            displayButtons: false
            height: appointment.height
            width: root.width - x - 10
        }

        CapacityModel{
            x:agenda.x
            y:appointment.y + appointment.height + appointment.y
            width: root.width - x - 10
            height: root.height - y
            displayResults: true

        }
    }
}
