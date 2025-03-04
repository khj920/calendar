/*
 * SPDX-FileCopyrightText: 2020 Dimitris Kardarakos <dimkard@posteo.net>
 *                         2021 Wang Rui <wangrui@jingos.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.7
import org.kde.kirigami 2.15 as Kirigami
import org.kde.calindori 0.1 as Calindori

Kirigami.ApplicationWindow {
    id: mainWindow

    width: mainWindow.screen.width
    height: mainWindow.screen.height

    fastBlurMode: true
    fastBlurColor: "#CFFFFFFF"

    pageStack {
        initialPage: [calendarMonthPage]
        defaultColumnWidth: Kirigami.Units.gridUnit * 60
    }

    Calindori.LocalCalendar {
        id: localCalendar

        name: _calindoriConfig.activeCalendar
    }

    Component {
        id: calendarMonthPage

        CalendarMonthPage {
            calendar: localCalendar

            onPageEnd: switchToMonthPage(lastDate, lastActionIndex)
        }
    }
}
