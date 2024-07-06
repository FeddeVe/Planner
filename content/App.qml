// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import Planner

Window {
    id:window
    visible: true
    title: "Planner"
    visibility: Window.Maximized

        onWidthChanged: mainScreen.width = width
        onHeightChanged: mainScreen.height = height


    Screen01 {
        id: mainScreen
        width: window.width
        height:window.height
    }



}

