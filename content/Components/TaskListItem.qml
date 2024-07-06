import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property string title: "Title"
    property int itemHeight : 120
    property int itemCount : items.count
    property bool isActive : false
    property bool logVisible : false
    property bool isPrio : false

    id: root
    width: 250
    height: logVisible ? logItems.y+ items.count * itemHeight + 20 : logItems.y + 20

    Rectangle{
        x:0
        y:0
        width: root.width
        height: root.height
        color: "#00000000"
        clip: true
    }

    Rectangle{
        x:0
        y:0
        width: root.width
        height: root.height
        color: root.isActive ? Style.clrTitle : Style.clrLight
        border.color: Style.gray
        border.width: 1
        radius: 20

        Text{
            x:10
            y:2
            width: root.width - 2*x
            font: Style.fHugeBold
            text: root.isPrio ? " !! "+ title +" !! " : title
            horizontalAlignment: Text.AlignHCenter
            color:root.isPrio ? Style.red : Style.gray
        }

        Text{
            x:8
            y:38
            width: 100
            font: Style.fStandard
            text: "StartDate:"
            horizontalAlignment: Text.AlignRight
            rotation: 0
        }

        Text{
            x:114
            y:38
            font: Style.fStandardBold
            text: "88/88/8888 21:40"
            width: 150
        }

       Text {
           x: 8
           y: 52
           width: 100
           text: "Due Date:"
           horizontalAlignment: Text.AlignRight
           font: Style.fStandard
       }

       Text {
           x: 114
           y: 52
           width: 150
           text: "88/88/8888 21:40"
           font: Style.fStandardBold
       }

       Text {
           x: 8
           y: 67
           width: 100
           text: "Total Duration:"
           horizontalAlignment: Text.AlignRight
           font: Style.fStandard
       }

       Text {
           x: 114
           y: 67
           width: 150
           text: "88/88/8888 21:40"
           font: Style.fStandardBold
       }

       Text {
           x: 8
           y: 82
           width: 100
           text: "Gebruikt:"
           horizontalAlignment: Text.AlignRight
           font: Style.fStandard
       }

       Text {
           x: 114
           y: 82
           width: 150
           text: "88/88/8888 21:40"
           font: Style.fStandardBold
       }

       DurationProgressBar{
           x:10
           y:103
           width: root.width - x*2
           height: 15
       }

       Button{
           x: 10
           y: 113
           width: root.width - x*2
           height: 40
           text: root.isActive? "Stop" : "Start"
           onClicked: root.isActive = !root.isActive
       }

       Button{
           x: 10
           y: 154
           width: root.width - x*2
           height: 40
           text: "Complete and close"
           onClicked: root.isActive = !root.isActive
       }

       Button{
           x: 10
           y: 195
           width: root.width - x*2
           height: 40
           text: "Show Log"
           onClicked: root.logVisible = !root.logVisible
       }

       Repeater{
           visible:logVisible
           id: logItems
           x:10
           y: 240
           model: items
           Rectangle{
               visible:logVisible
               id: checkItem
               property bool hover : false
               x:logItems.x
               y:logItems.y + index * itemHeight
               height: itemHeight - 2
               width: root.width - 20
               color: Style.white
               border.color: hover ? Style.cyan : Style.grey
               border.width: 1
               radius: 5
               Text{
                   x:5
                   y:5
                   width: 60
                   text: "StartDate:"
                   horizontalAlignment: Text.AlignRight
                   font: Style.fStandard
               }
               Text{
                   x:65
                   y:5
                   width: 130
                   text: startDateTime
                   horizontalAlignment: Text.AlignRight
                   font: Style.fStandard
               }
               Text{
                   x:5
                   y:25
                   width: 60
                   text: "StartDate:"
                   horizontalAlignment: Text.AlignRight
                   font: Style.fStandard
               }
               Text{
                   x:65
                   y:25
                   width: 130
                   text: stopDateTime
                   horizontalAlignment: Text.AlignRight
                   font: Style.fStandard
               }
               Text{
                   x:5
                   y:45
                   width: 60
                   text: "Duration:"
                   horizontalAlignment: Text.AlignRight
                   font: Style.fStandard
               }
               Text{
                   x:65
                   y:45
                   width: 130
                   text: duration
                   horizontalAlignment: Text.AlignRight
                   font: Style.fStandard
               }
               Button{
                   x:5
                   y:65
                   width: parent.width - x*2
                   text: "Edit"
                   height: 45
               }

               MouseArea{
                   anchors.fill: checkItem
                   hoverEnabled: true
                   onEntered: hover = true
                   onExited: hover = false
                   onClicked: isChecked = !isChecked
               }
           }
       }

       ListModel{
           id:items
           ListElement{logID: 23;startDateTime:"88/88/8888 88:88"; stopDateTime: "88/88/8888 88;88"; duration: "100"}
           ListElement{logID: 23;startDateTime:"88/88/8888 88:88"; stopDateTime: "88/88/8888 88;88"; duration: "100"}
           ListElement{logID: 23;startDateTime:"88/88/8888 88:88"; stopDateTime: "88/88/8888 88;88"; duration: "100"}

       }







    }

}
