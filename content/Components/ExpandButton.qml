import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property var onClick
    property bool expandLeftRight : false
    property bool expanded : false
    property bool darkMode : false

    id: root
    width: 32
    height: 32

    Image{
        x:0
        y:0
        width: root.width
        height: root.height
        source: root.expanded ? (root.darkMode ? "../images/up-arrow.png" :  "../images/up-arrow-light.png" ) : (root.darkMode ? "../images/down-arrow.png" : "../images/down-arrow-light.png")
        fillMode: Image.PreserveAspectFit
    }

    MouseArea{
        anchors.fill: parent
        onClicked: expanded = !expanded
    }
}
