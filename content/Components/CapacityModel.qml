import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property bool isTMPYagenda : false
    property bool displayResults : false
    property var dataModel : agendaManager.capModel()

    id:root
    width: 1400
    height: displayResults ? 300 :210




    Rectangle{
        x: 0
        y: 0
        height: root.height
        width: root.width
        border.color: Style.amber
        border.width: 1
        radius: 20
        color: agendaManager.tmpyActive ? Style.amber : Style.background

    Text{
        id:monthHeader
        x: 34
        y: 21
        text: "Capacity"
        color: agendaManager.capModel().tmpyActive ? Style.clrDark : Style.clrText
        font: Style.fLargeBold
         width: 125
    }


        ListView{
            id: capView
            x: monthHeader.x + monthHeader.width + 20
            y: 0
            width: root.width - x
            height: root.height - y * 2
            clip: true
            boundsMovement: Flickable.StopAtBounds
            flickableDirection: Flickable.AutoFlickDirection
            interactive: true
            boundsBehavior: Flickable.DragOverBounds
            orientation: ListView.Horizontal
            model: agendaManager.capModel()
            //model: capacitymodel
            delegate: ItemDelegate {
                width: 80
                height: capView.height
                padding: 0
                contentItem:
                    CapacityBlock{
                        id:capChartItem
                        x:0
                        y:0
                        width:80
                        height: capView.height
                        label: Month
                        isCurrent: CurMonth
                        workHours: WorkableHours
                        plannedHours: PlannedHours
                        workedHours: WorkedHours
                        lastMonthExtraHours: HoursFromLastMonth
                        resulthours: Result
                        capacityPercentage: CapPercentage
                        boxColor: BoxColor

                    }

                /*
                MouseArea{
                    anchors.fill: dayChartItem
                    hoverEnabled: true
                    onEntered: dayChartItem.hover = true
                    onExited: dayChartItem.hover = false
                    onClicked: dayView.currentIndex = index
                }
                */
            }

            ScrollIndicator.vertical: ScrollIndicator {visible: true}
            ScrollBar.vertical: ScrollBar {visible: true}
        }

        Text {
            id: monthHeader2
            x: 34
            y: 93
             width: 125
            height: 15
             color: agendaManager.capModel().tmpyActive ? Style.clrDark : Style.clrText
            text: "Month:"
            horizontalAlignment: Text.AlignRight
            font: Style.fStandard
        }

        Text {
            id: monthHeader3
            x: 34
            y: 108
             width: 125
            height: 15
             color: agendaManager.capModel().tmpyActive ? Style.clrDark : Style.clrText
            text: "Werkbare Uren:"
            horizontalAlignment: Text.AlignRight
            font: Style.fStandard
        }

        Text {
            id: monthHeader4
            x: 34
            y: 123
             width: 125
            height: 15
             color: agendaManager.capModel().tmpyActive ? Style.clrDark : Style.clrText
            text: "Uren van vorige maand:"
            horizontalAlignment: Text.AlignRight
            font: Style.fStandard
        }

        Text {
            id: monthHeader5
            x: 34
            y: 137
             width: 125
            height: 15
            color: agendaManager.capModel().tmpyActive ? Style.clrDark : Style.clrText
            text: "Geplande Uren:"
            horizontalAlignment: Text.AlignRight
            font: Style.fStandard
        }

        Text {
            id: monthHeader6
            x: 34
            y: 151
            width: 125
            height: 15
            color: agendaManager.capModel().tmpyActive ? Style.clrDark : Style.clrText
            text: "Gemaakte uren:"
            horizontalAlignment: Text.AlignRight
            font: Style.fStandard
        }

        Text {
            id: monthHeader7
            x: 34
            y: 178
             width: 125
            height: 15
             color: agendaManager.capModel().tmpyActive ? Style.clrDark : Style.clrText
            text: "Resultaat:"
            horizontalAlignment: Text.AlignRight
            font: Style.fStandard
        }



    /*
    Repeater{
        id:monthBloks
        model: capacitymodel
        x: 120
        y: 5
        Rectangle{
            x: monthBloks.x + (index * width)
            y: monthBloks.y
            width: capmonthBlock.width + 5
            CapacityBlock{
                id: capmonthBlock
                x:0
                y:0
                labelBelow: true
                label: descrription
                capacityPercentage: capacity
                isCurrent: current
                labelColor: isTMPYagenda ? Style.clrDark : Style.clrText
                displayResults: root.displayResults
            }
        }
    }

    */
    }

    Rectangle{
       // visible: dataModel.isLoading
        visible: false;
        id:loaderRect
        x:0
        y:0
        height: root.height
        width: root.width
        color: Style.background
        Text{
            x: loaderRect.width / 2 - width/2
            y: 20
            font:Style.fHugeBold
            text: "Capacity chart is loading"
            width: loaderRect.width
            horizontalAlignment: Text.AlignHCenter
            color:Style.clrText
        }
        BusyIndicator{
            x: loaderRect.width / 2 - width/2
            y: 100
            height:64
            width: 64
        }

    }

    ListModel{
        id:capacitymodel

        ListElement{descrription: "JAN"; capacity: 0.1; current: false}
        ListElement{descrription: "FEB"; capacity: 0.2; current: false}
        ListElement{descrription: "MRT"; capacity: 0.3; current: false}
        ListElement{descrription: "APR"; capacity: 0.4; current: false}
        ListElement{descrription: "MEI"; capacity: 0.5; current: false}
        ListElement{descrription: "JUN"; capacity: 0.6; current: false}
        ListElement{descrription: "JUL"; capacity: 0.7; current: true}
        ListElement{descrription: "AUG"; capacity: 0.8; current: false}
        ListElement{descrription: "SEP"; capacity: 0.9; current: false}
        ListElement{descrription: "OKT"; capacity: 0.8; current: false}
        ListElement{descrription: "NOV"; capacity: 0.7; current: false}
        ListElement{descrription: "DEC"; capacity: 0.6; current: false}
        ListElement{descrription: "DEC"; capacity: 0.5; current: false}
        ListElement{descrription: "DEC"; capacity: 0.4; current: false}

    }
}
