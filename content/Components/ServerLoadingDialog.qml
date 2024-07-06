import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    id:root
    width: Constants.width
    height: Constants.height

    Rectangle{

        x:0
        y:0
        width: root.width
        height:root.height
        z:10
        color: "#00000088"


    }
    Rectangle{
        id:box
        x: root.width / 2 - width/2
        y: root.height / 2 - height/2
        width: 400;
        height:300
        border.color: Style.amber
        border.width: 1
        radius:10
        Rectangle{
            x: 0
            y: 0
            width: 400;
            height:btn.y + btn.height + 20
            border.color: Style.amber
            border.width: 1
            radius:10

            Text{
                id:title;
                x: 80;
                y: 10;
                height: 40
                width: parent.width - x*2;
                text: "Loading"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: Style.clrDark
                font:Style.fHugeBold
            }

            Canvas {
                    width: box.width; height: box.height
                    //x:dayPartHeight * index + dayPartHeight
                    //property color fillColor : disabled ? "#ababab" : "#ffffff"
                    //onFillColorChanged: requestPaint()
                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.lineWidth = 1
                        ctx.fillStyle = Style.background
                        ctx.strokeStyle = Style.amber
                        ctx.beginPath()
                        ctx.moveTo(40, title.y+title.height+5)
                        ctx.lineTo(box.width - 40, title.y+title.height+5)
                        ctx.closePath()
                        //ctx.fill()
                        ctx.stroke()
                    }
                }

            Text{
                id:txtjobs
                x:200
                y: title.y + title.height + 20
                font: Style.fMedium
                text: "Jobs"
            }

            BusyIndicator {
                visible: !jobsManager.jobsLoaded
                id: jobsbusyIndicator
                x: 100
                y: txtjobs.y - height / 4
                height: txtjobs.height * 2
            }

            Image{
                visible: jobsManager.jobsLoaded
                x: jobsbusyIndicator.x
                y: jobsbusyIndicator.y
                height: jobsbusyIndicator.height
                width: jobsbusyIndicator.width
                source: "../images/check.png"
                fillMode: Image.PreserveAspectFit
            }

            Text{
                id:txtAppointments
                x:200
                y: jobsbusyIndicator.y + jobsbusyIndicator.height + 20
                font: Style.fMedium
                text: "Appointmets"
            }

            BusyIndicator {
                visible: !appManager.appointmentsLoaded
                id: appointmentsbusyIndicator
                x: 100
                y: txtAppointments.y - height / 4
                height: txtAppointments.height * 2
            }

            Image{
                visible: appManager.appointmentsLoaded
                x: 100
                y: appointmentsbusyIndicator.y
                height: appointmentsbusyIndicator.height
                width: height
                source: "../images/check.png"
            }

            Text{
                id:txtBuckets
                x:200
                y: appointmentsbusyIndicator.y + appointmentsbusyIndicator.height + 20
                font: Style.fMedium
                text: "Buckets"
            }

            BusyIndicator {
                visible: !bucketManager.bucketsLoaded
                id: bucketsbusyIndicator
                x: 100
                y: txtBuckets.y - height / 4
                height: txtBuckets.height * 2
            }

            Image{
                visible: bucketManager.bucketsLoaded
                x: 100
                y: txtBuckets.y - height / 4
                height: txtBuckets.height * 2
                width: height
                source: "../images/check.png"
            }

            Canvas {
                    width: box.width; height: box.height
                    //x:dayPartHeight * index + dayPartHeight
                    //property color fillColor : disabled ? "#ababab" : "#ffffff"
                    //onFillColorChanged: requestPaint()
                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.lineWidth = 1
                        ctx.fillStyle = Style.background
                        ctx.strokeStyle = Style.amber
                        ctx.beginPath()
                        ctx.moveTo(40, jobsbusyIndicator.y+jobsbusyIndicator.height+5)
                        ctx.lineTo(box.width - 40, jobsbusyIndicator.y+jobsbusyIndicator.height+5)
                        ctx.closePath()
                        //ctx.fill()
                        ctx.stroke()
                    }
                }


        }


    }

   // MouseArea{
   //     anchors.fill: parent
   // }


}
