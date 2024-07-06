import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property bool editMode : false
    property color backGroundcolor: Style.clrTransparant
    property color textColor: Style.clrText
    property string placeHolder: ""
    property string value : ""
    property string label : "LABEL:"
    property font labelFont: Style.fStandard
    property font textFont: Style.fMedium
    property int textAlign: Text.AlignLeft
    property int textOffset: 20
    property var editModeSelected : function(){}
    property var editModeDeselected : function(){}
    property bool enabled : true
    property bool showLabel : true

    onFocusChanged: txtInput.focus = focus

    id: root
    width: 200
    height: 50



    Text{
        id:lbl
        x:0
        y:0
        font: labelFont
        color: textColor
        text: label
    }

    TextArea{
        visible: editMode
        id:txtInput
        y:lbl.y+lbl.height
        width: root.width
        height: root.height - y
        textMargin: 20
        background:
            Rectangle{
                width: parent.width
                height: parent.height
                color: backGroundcolor
                border.color: textColor
                border.width: 1
                radius: 10
             }
        placeholderText: placeHolder
        color: textColor
        text: root.value
        font: textFont
        Material.accent: Style.amber
        focus: root.focus
        onFocusChanged: {
            if(focus){ txtInput.selectAll();
            }

        }
        onTextChanged: root.quickNewValue = text
        onEditingFinished: root.newValue = txtInput.text
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
        text: value
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
