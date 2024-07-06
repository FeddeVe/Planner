import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property var onClick

    id: root
    width: 32
    height: 32

    Image{
        x:0
        y:0
        width: root.width
        height: root.height
        source: "../images/add-light.png"
        fillMode: Image.PreserveAspectFit

    }

    MouseArea{
        anchors.fill: parent
        onClicked: onClick()
    }
}
