pragma Singleton
import QtQuick 6.2
import QtQuick.Studio.Application

QtObject {
    readonly property int width: 1920
    readonly property int height: 1080

    readonly property color green : "#00FF00"
    readonly property color grey : "#A0A0A0"
    readonly property color gray : "#363636"
    readonly property color cyan : "#00FFFF"
    readonly property color white : "#FFFFFF"
    readonly property color amber : "#e68000"
    readonly property color magenta : "#ff94ff"
    readonly property color red : "#ff0000"

    readonly property color clrLight : "#bdd7d6"
    readonly property color clrNormal : "#7f9d9d"
    readonly property color clrDark : "#516365"
    readonly property color clrText : "#eff2dd"
    readonly property color clrTitle : "#ee6b61"
    readonly property color clrTransparant: "#00000000"

    readonly property color halfAmber : "#AAe68000"
    readonly property color halfLight : "#AAbdd7d6"
    readonly property color halfGrey : "#AAA0A0A0"


    //readonly property color background : "#040404"
readonly property color background : "#516365"
    readonly property font fStandard : Qt.font({family: "B612", pixelSize : 12, styleName: "Regular"})
    readonly property font fStandardBold : Qt.font({family: "B612", pixelSize : 12, styleName: "Bold"})

    readonly property font fMedium : Qt.font({family: "B612", pixelSize : 14, styleName: "Regular"})
    readonly property font fMediumBold : Qt.font({family: "B612", pixelSize : 14, styleName: "Bold"})
    readonly property font fLarge : Qt.font({family: "B612", pixelSize : 18, styleName: "Regular"})
    readonly property font fLargeBold : Qt.font({family: "B612", pixelSize : 18, styleName: "Bold"})
    readonly property font fHugeBold : Qt.font({family: "B612", pixelSize : 24, styleName: "Bold"})



    /*
        font.pointSize: 24
        font.styleName: "Bold"
        font.family: "B612"
        */
}
