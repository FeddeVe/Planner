import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property int spacing : 5
    property int clickIndex : -1
    id:root
    width: 75
    height: Constants.height
    Rectangle{
        id:menuRect
        x:0
        y:0
        height: root.height
        width: root.width
        color: Style.gray
        ScrollView{
            x:0
            y:0
            width: root.width
            height: root.height - networkStartRect.height-20
            MyMenuButton{
                id:btnDashBoard
                x: spacing
                y: spacing
                label: "Dash Board"
                onClick: function(){ root.clickIndex = 1}
            }
            MyMenuButton{
                id:btnStatus
                x: spacing
                y: btnDashBoard.y + btnDashBoard.height + spacing *2
                label: "Agenda Status"
                onClick: function(){ root.clickIndex = 2}
            }
            MyMenuButton{
                id:btnAddAppointment
                x: spacing
                y: btnStatus.y + btnStatus.height + spacing * 2
                label: "Add Appoint ment"
                 onClick: function(){ root.clickIndex = 3}
            }
            MyMenuButton{
                id: btnAddTask
                x: spacing
                y: btnAddAppointment.y + btnAddAppointment.height + spacing * 2
                label: "Add Task"
            }

            MyMenuButton{
                id: btnJobs
                x: spacing
                y: btnAddTask.y + btnAddTask.height + spacing * 2
                label: "Jobs"
            }

            MyMenuButton{
                id: btnAppointmets
                x: spacing
                y: btnJobs.y + btnJobs.height + spacing * 2
                label: "Appoint ments"
            }

            MyMenuButton{
                id: btnTasks
                x: spacing
                y: btnAppointmets.y + btnAppointmets.height + spacing * 2
                label: "Tasks"
            }


        }

        MyMenuButton{
            //visible: !solidManager.authenticated
            id:srStartButton
            x:spacing
            y:msStartButton.y - spacing-height
            height: 100
            width: root.width-x*2
            label: "Solid Auth enticate"
            warning: !solidManager.authenticated
            enabled: !solidManager.authenticated
            onClick: function(){ solidManager.authenticate() }
        }



        MyMenuButton{
            visible: !microsoftManager.authenticated
            id:msStartButton
            x:spacing
            y:root.height - height - networkStartRect.height - spacing - spacing - spacing - msStartRect.height
            height: 100
            width: root.width-x*2
            label: "Autenticate"
            warning: true
            onClick: function(){ microsoftManager.authenticate() }
        }

        MyMenuButton{
            visible: (microsoftManager.itemsLeft == 0) && (microsoftManager.authenticated)
            id:msStartButton1
            x:spacing
            y:root.height - height - networkStartRect.height - spacing - spacing - spacing - msStartRect.height
            height: 100
            width: root.width-x*2
            label: "Save Agenda"
            enabled: microsoftManager.itemsLeft == 0
            onClick: function(){
                agendaManager.exportAgenda();
            }
        }

        Rectangle{
            id:msStartRect
            x:spacing
            y:root.height - height - networkStartRect.height - spacing - spacing
            height: 100
            width: root.width-x*2
            color: menuRect.color
            border.color: Style.clrLight
            border.width: 1
            radius: 10
            Text{
                text: "Agenda Sync"
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                color: Style.clrText
                font:Style.fStandard
                width: msStartRect.width
            }
            MyBusyIndicator{
                visible: microsoftManager.itemsLeft > 0
                x: msStartRect.width/2 - width/2
                y: 30
                width: 45
                height: 45
            }
            Image{
                 visible: microsoftManager.itemsLeft == 0
                x: msStartRect.width/2 - width/2
                y: 30
                width: 45
                height: 45
                source: "../images/check.png"
            }

            Text{
                y:msStartRect.height - height
                text: microsoftManager.itemsLeft > 0 ? "Syncing \n "+ microsoftManager.itemsLeft +" Left" : "Micfrosoft is sync"
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                color: Style.clrText
                font:Style.fStandard
                width: msStartRect.width
            }

        }

        Rectangle{
            id:networkStartRect
            x:spacing
            y:root.height - height - spacing
            height: 100
            width: root.width-x*2
            color: menuRect.color
            border.color: Style.clrLight
            border.width: 1
            radius: 10
            Text{
                text: "Network Status"
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                color: Style.clrText
                font:Style.fStandard
                width: networkStartRect.width
            }
            MyBusyIndicator{
                visible: dbManager.waitingList > 0
                x: networkStartRect.width/2 - width/2
                y: 30
                width: 45
                height: 45
            }
            Image{
                 visible: dbManager.waitingList == 0
                x: networkStartRect.width/2 - width/2
                y: 30
                width: 45
                height: 45
                source: "../images/check.png"
            }

            Text{
                y:networkStartRect.height - height
                text: dbManager.waitingList > 0 ? "Syncing \n "+ dbManager.waitingList +" Left" : "Network is sync"
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                color: Style.clrText
                font:Style.fStandard
                width: networkStartRect.width
            }

        }
    }
}
