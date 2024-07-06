import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property bool editMode : false
    property color backGroundcolor: Style.clrTransparant
    property color textColor: Style.clrText
    property int currentIndex : 1
    property var model
    property string label : "LABEL:"
    property string textRole: "text"
    property font labelFont: Style.fStandard
    property font textFont: Style.fMedium
    property int textAlign: Text.AlignLeft
    property int textOffset: 20
    property var editModeSelected : function(){}
    property var editModeDeselected : function(){}
    property bool enabled : true
    property bool showLabel : true

    id: root
    width: Constants.width
    height: 60

    Rectangle{
        id:mainRect
        x: 0;
        y: 0
        height: root.height
        width: root.width
        color: backGroundcolor

    Text{
         visible: root.showLabel
        id:lbl
        x:0
        y:1
        font: labelFont
        color: textColor
        text: label
    }



    ComboBox{
        visible: editMode
        id:defDaedLine
        x:0
        y:root.showLabel ? lbl.y + lbl.height : 0
        width: root.width
        model: root.model
        textRole: root.textRole
        height: root.showLabel ? root.height - lbl.height - lbl.y : root.height
        currentIndex: root.currentIndex
        activeFocusOnTab: true
       // displayText: select
        background: Rectangle{
            color:Style.clrTransparant
            border.width: parent && parent.activeFocus ? 2 : 1
            border.color: parent && parent.activeFocus ? Style.amber : Style.white
        }

        Material.accent: "green"
        Material.foreground: Style.clrText

        onActivated: {
            console.log("Selected index = " + currentIndex);
             root.currentIndex = currentIndex
            console.log("Selected index = " + currentIndex);
        }
        Keys.onEnterPressed: {
            root.newValue = txtInput.text
            root.editModeDeselected();
        }
        Keys.onReturnPressed: {
            root.newValue = txtInput.text
            root.editModeDeselected();
        }
        Keys.onEscapePressed: root.editModeDeselected();
    }

    Rectangle{
        visible: !editMode
        property bool hover : false
        id:hoverRect
        x:lbl.x + textOffset / 2
        y:root.showLabel ? lbl.y+lbl.height : 0
        width: root.width - x *2
        height: root.height - y - 2
        color: Style.clrTransparant
        border.color: hover ? Style.clrText : Style.clrTransparant
        border.width: 1
        radius: 10


    Text{
        id: txtText
        x: textOffset / 2
        height: hoverRect.height
        wrapMode: Text.WordWrap
        horizontalAlignment: root.textAlign
        verticalAlignment: Text.AlignVCenter
        color: textColor
        text: defDaedLine.currentText
        font: textFont


    }

    MouseArea{
        anchors.fill: parent;
        hoverEnabled: true
        onEntered: root.enabled ? hoverRect.hover = true : hoverRect.hover = false;
        onExited: hoverRect.hover = false;
        onClicked: editModeSelected()

    }
   }

    }

}
