import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property var onAgendaErrorViewClick
    property var onAppErrorViewClick

    id:root
    width: 400
    height: Constants.height

    ScrollView{
        id:container
        x:0
        y:0
        width: root.width
        height: root.height
        contentHeight: rect1.y + rect1.height

        Rectangle{
            id:rect1
            x:0
            y:0
            height: appErrorList.y+appErrorList.height
            width: container.width
            color: Style.background
        }


    Text{
        id:aerrtxt
        x:20
        y:20
        width: root.width - x*2
        font: Style.fHugeBold
        text: "Agenda Errors"
        color:Style.clrText;
    }

    SpacerLine{
        id: spacer1
        x:0
        y: aerrtxt.y + aerrtxt.height
        width: root.width
        clr: Style.grey
    }

    Text{
        visible: agendaManager.errModel().count == 0
        id:noAgendaErrorText
        x:20
        y:spacer1.y + spacer1.height
        width: root.width - x*2
        font: Style.fHugeBold
        text: "No Errors Found"
        color:Style.clrText;
    }

    ListView{
        //visible: agendaManager.errModel().count > 0
        id: agendaErrorList
        x: input.x
        y: spacer1.y + spacer1.height
        width: root.width - x * 2
        height: contentHeight + 150
        model: agendaManager.errModel()
        delegate:
            Rectangle{
            id:itemRect
            property bool hover:  false
                x:0
                y:2
                width: agendaErrorList.width
                height: viewButton.y+viewButton.height + 3
                color:hover ? Style.clrNormal : Style.clrTransparant
                Text{
                    id:no
                    x: 20
                    y:0
                    font: Style.fMediumBold
                    color: Style.clrText
                    text: Datum
                }
                Text{
                    id:name
                    x: 20
                    y:no.y+no.height
                    font: Style.fStandard
                    color: Style.clrText
                    text: Message
                }
                MyMenuButton{
                    id: viewButton
                    x: itemRect.width - width - 20
                    y: 5
                    height: 32
                    label: "View"
                    warningColor: Style.amber
                    warning: true
                    onClick: function(){
                        root.onAgendaErrorViewClick(Datum);
                    }
                }

                Canvas {
                    id: itemLine
                        width: itemRect.width; height: itemRect.height
                        //x:dayPartHeight * index + dayPartHeight
                        //property color fillColor : disabled ? "#ababab" : "#ffffff"
                        //onFillColorChanged: requestPaint()
                        onPaint: {
                            var ctx = getContext("2d")
                            ctx.lineWidth = 1
                            ctx.fillStyle = Style.background
                            ctx.strokeStyle = Style.grey
                            ctx.beginPath()
                            ctx.moveTo(20, viewButton.y + viewButton.height + 2)
                            ctx.lineTo(itemRect.width-20, viewButton.y + viewButton.height + 4)
                            ctx.closePath()
                            //ctx.fill()
                            ctx.stroke()
                        }
                    }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: hover  = true
                    onExited: hover = false
                    onClicked: root.onAgendaErrorViewClick(Datum);



                }




        }

        SpacerLine{
            id: spacer2
            x:0
           // y: agendaManager.errModel().count > 0 ? agendaErrorList.y + agendaErrorList.height : noAgendaErrorText.y + noAgendaErrorText.height
           y: agendaErrorList.y + agendaErrorList.height
            width: root.width
            clr: Style.grey
        }

        Text{

            id:apperrtxt
            x:20
            y:spacer2.y + spacer2.height
            width: root.width - x*2
            font: Style.fHugeBold
            text: "Appointment Errors"
            color:Style.clrText;
        }

        SpacerLine{
            id: spacer3
            x:0
            y: apperrtxt.y + apperrtxt.height
            width: root.width
            clr: Style.grey
        }

        Text{
            visible: appManager.errModel().count == 0
            id:noAppErrorText
            x:20
            y:spacer3.y + spacer3.height
            width: root.width - x*2
            font: Style.fHugeBold
            text: "No Errors Found"
            color:Style.clrText;
        }

        ListView{
            visible: truel
           //visible: appManager.errModel().count > 0
            id: appErrorList
            x: input.x
            y: spacer3.y + spacer3.height
            width: root.width - x * 2
            height: contentHeight + 150
            model: appManager.errModel();
            delegate:
                Rectangle{
                id:appItemRect
                property bool hover:  false
                    x:0
                    y:2
                    width: appErrorList.width
                    height:  apmsg.y+apmsg.height + 3
                    color:hover ? Style.clrNormal : Style.clrTransparant
                    Text{
                        id:apTitle
                        x: 20
                        y:0
                        font: Style.fMediumBold
                        color: Style.clrText
                        text: Title
                    }
                    Text{
                        id:appJobNo
                        x: 20
                        y:apTitle.y+apTitle.height
                        font: Style.fStandard
                        color: Style.clrText
                        text: Job
                    }
                    Text{
                        id:apmsg
                        x: 20
                        y:appJobNo.y + appJobNo.height
                        font: Style.fMediumBold
                        color: Style.amber
                        width: appItemRect.width - 40
                        text: MSG
                        wrapMode: Text.WordWrap
                    }

/*
                    MyMenuButton{
                        id: appViewButtono
                        x: appItemRect.width - width - 20
                        y: 5
                        height: appItemRect.height - y*2
                        label: "View"
                        warningColor: Style.amber
                        warning: true
                        onClick: function(){
                            root.onAgendaErrorViewClick(Datum);
                        }
                    }
                    */

                    Canvas {
                        id: itemLine2
                            width: appItemRect.width; height: appItemRect.height
                            //x:dayPartHeight * index + dayPartHeight
                            //property color fillColor : disabled ? "#ababab" : "#ffffff"
                            //onFillColorChanged: requestPaint()
                            onPaint: {
                                var ctx = getContext("2d")
                                ctx.lineWidth = 1
                                ctx.fillStyle = Style.background
                                ctx.strokeStyle = Style.grey
                                ctx.beginPath()
                                ctx.moveTo(20, apmsg.y + apmsg.height + 2)
                                ctx.lineTo(appItemRect.width-20, apmsg.y + apmsg.height + 4)
                                ctx.closePath()
                                //ctx.fill()
                                ctx.stroke()
                            }
                        }

                    MouseArea{
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: hover  = true
                        onExited: hover = false
                        onClicked: root.onAppErrorViewClick(ID);



                    }




            }





}



    }


    ListModel{
        id:jobs
        ListElement{jobID: 1222; jobNo: "24-0001"; jobName: "Naam";jobClient: "Client"; isSubItem: true}
        ListElement{jobNo: "24-0002"; isSubItem: true}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"; isSubItem: true}
        ListElement{jobNo: "24-0002"; isSubItem: true}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
    }







     }
}
