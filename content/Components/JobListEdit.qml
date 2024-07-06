import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import Planner 1.0

Item {
    id:root
    width: Constants.width
    height: Constants.height

    Rectangle{
        id:jobRect
        x:0
        y:0
        height: root.height
        width: root.width / 3
        color:Style.clrDark

        Text{
            id:jobInfoTitle
            x:10
            y:10
            font:Style.fHugeBold
            text:"Job Info"
            horizontalAlignment: Text.AlignHCenter
            width: jobRect.width
            color:Style.clrText

        }


        Canvas {
                width: jobRect.width; height: jobRect.height
                //x:dayPartHeight * index + dayPartHeight
                //property color fillColor : disabled ? "#ababab" : "#ffffff"
                //onFillColorChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.lineWidth = 2
                    ctx.fillStyle = Style.background
                    ctx.strokeStyle = Style.amber
                    ctx.beginPath()
                    ctx.moveTo(120, jobInfoTitle.y+jobInfoTitle.height + 10)
                    ctx.lineTo(jobInfoTitle.width - 120, jobInfoTitle.y+jobInfoTitle.height + 10)
                    ctx.closePath()
                    //ctx.fill()
                    ctx.stroke()
                }
            }

        Canvas {
                width: jobRect.width; height: jobRect.height
                //x:dayPartHeight * index + dayPartHeight
                //property color fillColor : disabled ? "#ababab" : "#ffffff"
                //onFillColorChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.lineWidth = 2
                    ctx.fillStyle = Style.background
                    ctx.strokeStyle = Style.amber
                    ctx.beginPath()
                    ctx.moveTo(jobRect.width - 2, 120)
                    ctx.lineTo(jobRect.width - 2, jobRect.height-120)
                    ctx.closePath()
                    //ctx.fill()
                    ctx.stroke()
                }
            }


    }

    Rectangle{
        id:infoRect
        x:jobRect.width
        y:0
        height: root.height
        width: root.width / 3
        color:Style.clrDark

        Text{
            id:listInfoTitle
            x:10
            y:10
            font:Style.fHugeBold
            text:"List Info"
            horizontalAlignment: Text.AlignHCenter
            width: jobRect.width
            color:Style.clrText

        }

        Canvas {
                width: jobRect.width; height: jobRect.height
                //x:dayPartHeight * index + dayPartHeight
                //property color fillColor : disabled ? "#ababab" : "#ffffff"
                //onFillColorChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.lineWidth = 2
                    ctx.fillStyle = Style.background
                    ctx.strokeStyle = Style.amber
                    ctx.beginPath()
                    ctx.moveTo(120, listInfoTitle.y+listInfoTitle.height + 10)
                    ctx.lineTo(jobRect.width - 120, listInfoTitle.y+listInfoTitle.height + 10)
                    ctx.closePath()
                    //ctx.fill()
                    ctx.stroke()
                }
            }

        Canvas {
                width: jobRect.width; height: jobRect.height
                //x:dayPartHeight * index + dayPartHeight
                //property color fillColor : disabled ? "#ababab" : "#ffffff"
                //onFillColorChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.lineWidth = 2
                    ctx.fillStyle = Style.background
                    ctx.strokeStyle = Style.amber
                    ctx.beginPath()
                    ctx.moveTo(jobRect.width - 2, 120)
                    ctx.lineTo(jobRect.width - 2, jobRect.height-120)
                    ctx.closePath()
                    //ctx.fill()
                    ctx.stroke()
                }
            }


    }

    Rectangle{
        id:listRect
        x:infoRect.x + infoRect.width
        y:0
        height: root.height
        width: root.width / 3
        color:Style.clrDark

        Text{
            id:listTitle
            x:10
            y:10
            font:Style.fHugeBold
            text:"List"
            horizontalAlignment: Text.AlignHCenter
            width: jobRect.width
            color:Style.clrText
        }

        Canvas {
                width: listRect.width; height: listRect.height
                //x:dayPartHeight * index + dayPartHeight
                //property color fillColor : disabled ? "#ababab" : "#ffffff"
                //onFillColorChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.lineWidth = 2
                    ctx.fillStyle = Style.background
                    ctx.strokeStyle = Style.amber
                    ctx.beginPath()
                    ctx.moveTo(120, listTitle.y+listTitle.height + 10)
                    ctx.lineTo(listRect.width - 120, listTitle.y+listTitle.height + 10)
                    ctx.closePath()
                    //ctx.fill()
                    ctx.stroke()
                }
            }

        TaskList{
            x:2
            y:listTitle.y+listTitle.height + 15
            height: listRect.height - y*2
            width: listRect.width - x*2
        }

    }

}
