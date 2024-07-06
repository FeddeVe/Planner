import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property bool editMode : false
    id: root
    width: 600
    height: 55
    Rectangle{
        x:0
        y:0
        width: root.width
        height: root.height
        border.color: Style.clrDark
        border.width:0
        MyCheckBox{
            id:chk
            visible: !editMode
            x:1
            y:1
            width: 350
            height: root.height-2*x -5
            clip:true
            text: "Hele Lange Subitem Text SubItem"
            clr: Style.background
            txtclr:  Style.background
            font: Style.fMedium
        }
        TextField{
            visible: editMode
            x:chk.x
            y:chk.y
            width: chk.width
            height: chk.height
            clip:true
            text: "Hele Lange Subitem Text SubItem"
            font: Style.fMedium
            color: Style.background
        }

        DurationInput{
            visible: !editMode
            id:durationInput
            x:root.width - 70 - width
            y:root.height / 2 - height / 2-3
            textClr: Style.clrDark
            backgroundClr: parent.color
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



        Canvas {
                width: root.width; height: root.height
                //x:dayPartHeight * index + dayPartHeight
                //property color fillColor : disabled ? "#ababab" : "#ffffff"
                //onFillColorChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.lineWidth = 1
                    ctx.fillStyle = Style.background
                    ctx.strokeStyle = Style.amber
                    ctx.beginPath()
                    ctx.moveTo(20, root.height - 5)
                    ctx.lineTo(root.width - 20, root.height-5)
                    ctx.closePath()
                    //ctx.fill()
                    ctx.stroke()
                }
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
