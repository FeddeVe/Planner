import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property color backColor: Style.clrLight
    property bool editMode : false
    property string label : ""
    id: root
    width: 600
    height: 200
    Rectangle{
        x:0
        y:0
        width: root.width
        height: root.height
        color: Style.clrNormal
        border.color:backColor
        border.width: 1
        gradient:
             Gradient {
                     orientation: Gradient.Vertical
                    GradientStop { position: 0.0; color:Style.white}
                     GradientStop { position: 1.0; color: backColor}
                }

        MyCheckBox{
            visible: !editMode
            id:ch
            x:5
            y:5
            width: 300
            font: Style.fMediumBold
            text: label
        }

        TextField{
            visible: editMode
            x:ch.x
            y:ch.y
            width: ch.width
            height: ch.height
            clip:true
            text: label
            font: Style.fMedium
            color: Style.background
            onTextChanged: label = text
            placeholderText: "Label"
            placeholderTextColor: Style.grey
        }

        DurationInput{
            visible: !editMode
            id:durationInput
            x:root.width - 70 - width
            y:ch.y + 4
            textClr: Style.clrDark
            backgroundClr: "#00000000"
            borderClr: Style.clrDark
        }

        TextField{
            visible: editMode
            id:inputField
            x:durationInput.x
            y:durationInput.y
            height: durationInput.height
            width: durationInput.width
            text: durationInput.value
            color: durationInput.textClr
            inputMask: "99:99"
        }

        EditButton{
            id: edit
            x:root.width - width - 20
            y: 9
            height:32
            width: 32
            onClick: function(){root.editMode = true}
        }




        Text{
            x: 8
            y: 64
            height: 15
            font: Style.fStandard
            text:"Start Date:"
            color: Style.background
        }
        Text{
            id:startDate
            visible: !editMode
            x: 8
            y: 85
            height:35
            width: root.width/2-10
            font: Style.fMedium
            text:"88/88/8888 88:88"
            color: Style.background
        }
        TextField{
            visible: editMode
            x:startDate.x
            y:startDate.y
            height: startDate.height
            width: startDate.width
            text: startDate.text
            color: startDate.textClr
            font: startDate.font
            inputMask: "99/99/9999 99:99"
        }



        Text{
            x: root.width - 8 - width
            y: 64
            width: 75
            height: 15
            font: Style.fStandard
            text:"Due Date:"
            horizontalAlignment: Text.AlignRight
            color: Style.background
        }

        Text{
            id:dueDate
            visible: !editMode
            x: root.width - 8 - width
            y: 85
            height: 35
            width: parent.width / 2-10
            font: Style.fMedium
            text:"88/88/8888 88:88"
            color: Style.background
            horizontalAlignment: Text.AlignRight
        }

        TextField{
            visible: editMode
            x:dueDate.x
            y:dueDate.y
            height: dueDate.height
            width: dueDate.width
            text: dueDate.text
            color: dueDate.textClr
            font: dueDate.font
            inputMask: "99/99/9999 99:99"
            horizontalAlignment: Text.AlignRight
        }

        Text {
            x: 8
            y: 120
            height: 15
            color: Style.background
            text: "Total Duration:"
            font: Style.fStandard
        }

        Text {
            x: root.width - width - 8
            y: 127
            height: 15
            color: Style.background
            text: "88:88"
            font: Style.fMedium
        }

        Text {
            x: root.width - width - 8
            y: 120
            height: 15
            color: Style.background
            text: "Remaining:"
            font: Style.fStandard
        }

        Text {
            x: 8
            y: 177
            height: 15
            color: Style.background
            text: "Automatic"
            font: Style.fMedium
        }

        Text {
            x: 8
            y: 162
            height: 15
            color: Style.background
            text: "Plan State:"
            font: Style.fStandard
        }

        Text {
            x: root.width - width - 8
            y: 163
            height: 15
            color: Style.background
            text: "88/88/8888 88:88"
            font: Style.fMedium
        }

        Text {
            x: root.width - width - 8
            y: 148
            height: 15
            color: Style.background
            text: "Plan Date:"
            font: Style.fStandard
        }

        Text {
            x: 8
            y: 141
            height: 15
            color: Style.background
            text: "88:88"
            font: Style.fMedium
        }


        Keys.onEnterPressed: {console.log("ENTER")
        root.editMode = false
        }
        Keys.onReturnPressed: {console.log("RETURN")
        root.editMode = false
        }
        Keys.onEscapePressed: {console.log("RETURN")
        root.editMode = false
        }

    }
}
