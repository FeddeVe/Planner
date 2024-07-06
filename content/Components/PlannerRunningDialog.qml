import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    id:root
    width: Constants.width
    height: Constants.height

    Rectangle{

        x:0
        y:0
        width: root.width
        height:root.height
        z:10
        color: "#00000088"
    }
    Rectangle{
        x: root.width / 2 - width/2
        y: root.height / 2 - height/2
        width: 400;
        height:300
        border.color: Style.amber
        border.width: 1
        radius:10
        Rectangle{
            x: 0
            y: 0
            width: 400;
            height:100
            border.color: Style.amber
            border.width: 1
            radius:10
            MyBusyIndicator{
                x: 10
                y: 10
                width:64;
                height:parent.height - 2*y
            }
            Text{
                x: 80;
                y: 10;
                height: parent.height - y*2;
                width: parent.width - x*2;
                text: "Planner Running"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: Style.amber
                font:Style.fHugeBold
            }
        }
        Text{
            x:10
            y:125
            width: parent.width - x*2
            font: Style.fMedium;
            text: dbManager.serverErrorText
            wrapMode: Text.WordWrap
        }
    }

    MouseArea{
        anchors.fill: parent
    }


}
