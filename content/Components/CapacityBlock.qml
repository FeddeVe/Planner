import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property bool labelBelow : true
    property string capacityPercentage : "-"
    property string label : "DEC"
    property bool isCurrent : true
    property color labelColor : Style.gray
    property bool displayResults: true
    property string workHours : "00"
    property string plannedHours: "01"
    property string workedHours: "02"
    property string lastMonthExtraHours: "03"
    property string resulthours : "04"
    property string boxColor: Style.green
    property real perc : 0.0

    id:root
    width: 80
    height: displayResults ? uren_beschikbaar.y + uren_beschikbaar.height + 5 : label.y + label.height + 5

    Rectangle{
        x:1
        y: labelBelow ? 1 : 20
        width: root.width - x*2
        height: root.height
        border.color: Style.grey
        border.width: isCurrent ? 4 : 0
        radius:10
        color: "#00000000"
    }

    Text{
        id:lbl
        x:0
        y:labelBelow ? box.y + box.height : 0
        width: root.width
        text: label
        horizontalAlignment: Text.AlignHCenter
        font:Style.fMediumBold
        color: agendaManager.dayModel().tmpyActive ? Style.clrDark : Style.clrText
    }

    Text{
        visible: displayResults
        id:werkbare_uren
        y:labelBelow ? lbl.y + lbl.height : 0
        width: root.width
        text: workHours
        horizontalAlignment: Text.AlignHCenter
        font:Style.fStandard
        color: agendaManager.dayModel().tmpyActive ? Style.clrDark : Style.clrText
           }
    Text{
        visible: displayResults
        id:overuren_uren
        y:labelBelow ? werkbare_uren.y + werkbare_uren.height : 0
        width: root.width
        text: lastMonthExtraHours
        horizontalAlignment: Text.AlignHCenter
       font:Style.fStandard
       color: agendaManager.dayModel().tmpyActive ? Style.clrDark : Style.clrText
       }
    Text{
        visible: displayResults
        id:geplande_uren
        y:labelBelow ? overuren_uren.y + overuren_uren.height : 0
        width: root.width
        text: plannedHours
        horizontalAlignment: Text.AlignHCenter
       font:Style.fStandard
       color: agendaManager.dayModel().tmpyActive ? Style.clrDark : Style.clrText
     }
    Text{
        visible: displayResults
        id:gemaakte_uren
        y:labelBelow ? geplande_uren.y + geplande_uren.height : 0
        width: root.width
        text: workedHours
        horizontalAlignment: Text.AlignHCenter
       font:Style.fStandard
       color: agendaManager.dayModel().tmpyActive ? Style.clrDark : Style.clrText
      }

    SpacerLine{
        id:spacer1
        x:0
        y: gemaakte_uren.y + gemaakte_uren.height
        width: root.width
    }

    Text{
        visible: displayResults
        id:uren_beschikbaar
        y:labelBelow ? spacer1.y + spacer1.height : 0
        width: root.width
        text: resulthours
        horizontalAlignment: Text.AlignHCenter
        font:Style.fMediumBold
        color: agendaManager.dayModel().tmpyActive ? Style.clrDark : Style.clrText
    }






    Rectangle{
        id: box
        x:1
        y: labelBelow ? 1 : 20
        width: root.width - x*2
        height: 80
        border.color: Style.grey
        border.width: isCurrent ? 4 : 0
        gradient:
            Gradient {
                    orientation: Gradient.Vertical
                    GradientStop { position: 0.0; color:root.labelBelow? boxColor : Style.background}
                    GradientStop { position: 1.0 - perc; color: root.labelBelow? Style.background : boxColor}

               }

        Text{
            x:0
            y:0
            width: parent.width
            height: parent.height
            text: capacityPercentage
            //text: green
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font:Style.fLarge
            color: Style.clrText
        }
    }
}
