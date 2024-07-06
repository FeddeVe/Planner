import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property var onClick
    property bool dark : false

    id: root
    width: 32
    height: 32

    Image{
        x:0
        y:0
        width: root.width
        height: root.height
        source: root.dark ? "../images/edit.png" : "../images/edit_light.png"
        fillMode: Image.PreserveAspectFit

    }

    MouseArea{
        anchors.fill: parent
        onClicked: onClick()
    }
}
