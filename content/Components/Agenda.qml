import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property int minWidth : 300
    property int maxWidth : 400
    property bool isMinWidth : true
    property int todayIndex : 8
    property bool displayButtons: true
    property bool agendaLoading: true
    property int positionIndex : agendaManager.dayModel().agendaIndex
    property bool isTMPY : true
    property var onItemClick


    onPositionIndexChanged: {
        gotoIndex(positionIndex);
    }


    Connections {
        target: dayView.model
        //onDataChanged: dayView.positionViewAtIndex(agendaManager.agendaIndex(), listView.Center);
       onModelReset:dayView.positionViewAtIndex(agendaManager.agendaIndex(), ListView.Center);

    }

    function gotoIndex(idx) {
            anim.running = false;

            var pos = dayView.contentX;
            var destPos;

            dayView.positionViewAtIndex(idx, ListView.Center);
            destPos = dayView.contentX;

            anim.from = pos;
            anim.to = destPos;
            anim.running = true;
        }


    NumberAnimation { id: anim; target: dayView; property: "contentX"; duration: 1000 }


    id: root
    width: Constants.width
    height: Constants.height

    Rectangle{
        visible: false;
       // visible: agendaManager.dayModel().tmpyActive
        id:mainRect
        x:0
        y:0
        height: root.height
        width: root.width
        color:Style.amber
        radius: 20
    }

    Rectangle{
        visible: agendaManager.dayModel().count == 0 ? true : false
        id:emptyRect
        x:0
        y:0
        z:50
        width: root.width
        height: root.height
        color: Style.background

        Text{

            x:emptyRect.width / 2 - width/2
            y: 20
            color: Style.clrText
            font:Style.fHugeBold
            text: "Agenda is empty"
        }
    }

    Rectangle{
        visible: agendaManager.agendaLoading || agendaManager.plannerRunning
        id:loaderRect
        x:0
        y:0
        z:50
        width: root.width
        height: root.height
        color: Style.halfGrey

        Text{

            x:loaderRect.width / 2 - width/2
            y: 20
            color: Style.clrText
            font:Style.fHugeBold
            text: agendaManager.agendaLoading ? "Loading Agenda" : "Loading Planner"
        }
        BusyIndicator{
            x: loaderRect.width / 2 - width/2
            y:100
            height:50
            width:50
        }

    }



    Button{
        visible: displayButtons
       id:todayButton
       x: 10
       y: 0
       text: "Scroll to today"
       onClicked: {
           gotoIndex(agendaManager.agendaIndexAt(""));
       }
    }

    Button{
       visible: displayButtons
       id:expandButton
       x: todayButton.x + todayButton.width + 20
       y: 0
       text: isMinWidth ? "Expand ->" : "<- Collapse"
       onClicked: {
           root.isMinWidth  = !root.isMinWidth
           root.width = root.isMinWidth ? minWidth : maxWidth
           dayView.positionViewAtIndex(root.isMinWidth ? todayIndex : todayIndex + 1,ListView.Center)
       }
    }



    ListView{
        id: dayView
        x: 10
        y: displayButtons ? todayButton.height : 0
        width: root.width - x - 20
        height: root.height - y
        clip: true
        boundsMovement: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickDirection
        interactive: true
        boundsBehavior: Flickable.DragOverBounds
        orientation: ListView.Horizontal
        model: agendaManager.dayModel()
        currentIndex: positionIndex
        add: Transition { NumberAnimation { property: 'width'; from: 0; to: 150; duration: 600 } }

        //  Component.onStatusChanged: dayView.positionViewAtIndex(agendaManager.agendaIndex(), listView.Center);
         headerPositioning: ListView.OverlayHeader
        header: AgendaErrors{
            visible: (agendaManager.errModel().count > 0) || (appManager.errModel().count > 0)
            width:(agendaManager.errModel().count > 0) || (appManager.errModel().count > 0) ? 300 : 10
            height: dayView.height
            x:0
            y:0
            z:25
            onAgendaErrorViewClick: function(datum){
                gotoIndex(agendaManager.agendaIndexAt(datum));
            }
            onAppErrorViewClick: function(id){
                root.onItemClick(0, id)
            }
        }

        delegate: ItemDelegate {
            width: 250
            height: dayView.height
            padding: 0
            contentItem:

                DayChart{
                    id:dayChartItem
                    isToday: false
                    height: 400
                    width: 250
                    datum: Datum
                    dag : Name
                    isHighLight: isSelected
                    isWorkingDay: WorkingDay
                    rowIndex: index
                    isTMPY: IsFromTMPY
                    onItemClick:function(id,type){

                        root.onItemClick(id, type)
                    }
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



    ListModel{
        id:jobs
        ListElement{jobID: 1222; jobNo: "24-0001"; isActive: false}
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
