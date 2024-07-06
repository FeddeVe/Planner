import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property color backgroundClr : Style.background
    property color textClr : Style.clrText
    property color borderClr : Style.clrLight
    property color highlightClr : Style.clrTitle
    property string value : " 88:88"
    property bool isFocus : false


    id: root
    width: 90
    height: 35
    Rectangle{
        x:0
        y:0
        height: root.height
        width: root.width
        radius: 10
        color: backgroundClr
        border.color: borderClr
        border.width: 1

        Image {
            visible: !isFocus
            id: clockIcon
            x: 5
            y: 0
            width: 20
            height: root.height
            source: "../images/clock.png"
            fillMode: Image.PreserveAspectFit

        }

        Text{
            visible: !isFocus
            x: 35
            y: 0
            font: Style.fMedium
            height: root.height
            text: value
            verticalAlignment: Text.AlignVCenter
            color: textClr
        }

        TextField{
            id:inputField
            visible: isFocus
            x:0
            y:0
            height: root.height
            width: root.width
            text: value
            color: textClr
            inputMask: "99:99"
            Keys.onEnterPressed: root.isFocus = false
            Keys.onTabPressed: root.isFocus = false

        }





    }
}
