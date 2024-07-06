import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property var subItem

    id: root
    width: 600
    height: itemRect.height

    Rectangle{
               id: itemRect
               x:0
               y:0
               height: itemDuration.y + itemDuration.height + 10
               width: root.width
               color: Style.gray
               clip:true
               gradient: Gradient {
                       orientation: Gradient.Horizontal
                       GradientStop { position: 0.0; color: Style.clrTransparant}
                       GradientStop { position: 0.25; color: Style.gray}
               }
               Image {
                   visible: !isFirst
                   id: btnItemUp
                   x:10
                   source: "../images/up-arrow-light.png"
                   fillMode: Image.PreserveAspectFit
                   width:32
                   height: 64
                   MouseArea{
                       anchors.fill: parent
                       onClicked: console.log("Clicked");
                   }
               }

               Image {
                   visible: !isLast
                   id: btnItemDown
                   x:btnItemUp.x + btnItemUp.width + 20
                   source: "../images/down-arrow-light.png"
                   fillMode: Image.PreserveAspectFit
                   width:32
                   height: 64
                   MouseArea{
                       anchors.fill: parent
                       onClicked: console.log("Clicked");
                   }
               }

               DeleteButton{
                   id: deleteItemBtn
                   x: btnItemDown.x + btnItemDown.width + 20
                   height: 64
               }

               MyTextField{
                   id:itemTitel
                   x: deleteItemBtn.x + deleteItemBtn.width + 20
                   y:5
                   label: "Item:"
                   value: subItem.title
                   editMode: true
                   width: itemRect.width - x - 10
                   onValueChanged: subItem.title = value
               }

               MyComboBox{
                   id: defDaedLine
                   x:itemTitel.x
                   y:itemTitel.y + itemTitel.height
                   width: itemTitel.width
                   model: deadLines
                   currentIndex: subItem.defaultDeadline
                   editMode: true
                   label: "Default Deadline:"
                   textRole: "d_title"
                   onCurrentIndexChanged: subItem.defaultDeadline = currentIndex
               }






               MyTextField{
                   id:itemDuration
                   x: deleteItemBtn.x + deleteItemBtn.width + 20
                   y:defDaedLine.y + defDaedLine.height
                   label: "Duration from history:"
                   value: subItem.calculatedDuration
                   editMode: false
                   width: itemRect.width - x - 10
               }

               Canvas {
                   id: splitLine
                       width: root.width; height: root.height
                       property color lineColor : Style.grey
                       onLineColorChanged: requestPaint()

                       onPaint: {
                           var ctx = getContext("2d")
                           ctx.lineWidth = 2
                           ctx.strokeStyle = lineColor
                           ctx.beginPath()
                           ctx.moveTo(10, itemRect.height - 1)
                           ctx.lineTo(lstItems.width, itemRect.height+2)
                           ctx.closePath()
                           //ctx.fill()
                           ctx.stroke()
                       }
                   }
    }

    ListModel{
        id:deadLines
        ListElement{d_title: "Not Set"; d_template: "Tekening Opstarten"; d_dueDate: "Not Set"; d_durationLeft: "01:00"; d_completed: true; d_isNodig: true; d_type:1}
        ListElement{d_title: "JobDate"; d_template: "Tekening Opstarten"; d_dueDate: "Not Set"; d_durationLeft: "01:00"; d_completed: true; d_isNodig: true; d_type:1}
        ListElement{d_title: "JobStartDate"; d_template: "Venue 2D"; d_dueDate: "Not Set"; d_durationLeft: "04:00"; d_completed: false; d_isNodig: true;d_type:1}
        ListElement{d_title: "JobPickDate"; d_template: "Set Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}

    }
}
