import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property bool hover: false
    property string label : "LABEL"
    property var onClick
    property bool warning: false
    property color warningColor : Style.amber
    id: root
    width: 65
    height: 65
    Rectangle{
        x:0
        y:0
        height: root.height
        width: root.width
        color: root.hover ? (root.warning ? warningColor : Style.clrLight) : Style.gray
        radius: 10
        border.color: root.hover ? Style.gray : (root.warning ? warningColor: Style.clrLight)
        border.width: 1

        Text{
            x: 5
            y: 5
            width: root.width - x*2
            height: root.height - y*2
            text: label
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            font:Style.fMedium
            color: root.hover ? Style.gray : root.warning ? warningColor : Style.clrLight

        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: root.hover = true
            onExited: root.hover = false
            onPressed: onClick()
        }
    }
}
