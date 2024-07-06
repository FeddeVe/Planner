import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Popup {
    property string title: "Title"
    property string msg: "MESSAGE"
    property int returnCode: -1

    onReturnCodeChanged: {
        console.log("ReturnCode = "+ root.returnCode);
    }

    id:root
    width: 400
    height: okButton.y + okButton.height + 20
    x:0
    y:0
    z:100
    background: Rectangle{
        height: root.height
        width: root.width
        color: Style.white
        border.color: Style.clrLight
        border.width: 1
    }



            Text{
                id:title
                x:0
                y:10
                width:root.width
                horizontalAlignment: Text.AlignHCenter
                font:Style.fHugeBold
                text:root.title
                color: Style.gray

            }

            SpacerLine{
                id:space1
                x:0
                y:title.y+title.height +5
                width: root.width
            }

            Text{
                id:msg
                x:20
                y:space1.y +space1.height + 5
                font:Style.fStandard
                width: root.width - x*2
                text: root.msg
            }

            SpacerLine{
                id:space2
                x:0
                y:msg.y+msg.height +5
                width: root.width
            }

            Button{
                id:okButton
                x:20
                y:space2.y + space2.height + 5
                width: root.width / 2 - x*2
                text: "OK"
                onClicked:{
                    root.returnCode = 0
                    root.close()
                }
            }

            Button{
                id:cancelButton
                x:(root.width / 2) + 20
                y:space2.y + space2.height + 5
                width: root.width / 2 - 40
                text: "CANCEL"
                onClicked: {
                    root.returnCode = 1
                    root.close()
                }
            }
        }



