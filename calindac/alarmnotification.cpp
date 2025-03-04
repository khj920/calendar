/*
 * SPDX-FileCopyrightText: 2019 Dimitris Kardarakos <dimkard@posteo.net>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "alarmnotification.h"
#include "notificationhandler.h"
#include <KLocalizedString>
#include <QDebug>

AlarmNotification::AlarmNotification(NotificationHandler *handler, const QString &uid) : m_uid {uid}, m_remind_at {QDateTime()}, m_notification_handler {handler}
{
    m_notification = new KNotification("alarm");
    m_notification->setActions({i18n("Suspend"), i18n("Dismiss")});

    connect(m_notification, &KNotification::action1Activated, this, &AlarmNotification::suspend);
    connect(m_notification, &KNotification::action2Activated, this, &AlarmNotification::dismiss);
    connect(this, &AlarmNotification::suspend, m_notification_handler, [ = ]() {
        m_notification_handler->suspend(this);
    });
    connect(this, &AlarmNotification::dismiss, m_notification_handler, [ = ]() {
        m_notification_handler->dismiss(this);
    });
}

AlarmNotification::~AlarmNotification()
{
    delete m_notification;
}

void AlarmNotification::send() const
{
    m_notification->sendEvent();
}

QString AlarmNotification::uid() const
{
    return m_uid;
}

QString AlarmNotification::text() const
{
    return m_notification->text();
}

void AlarmNotification::setText(const QString &alarmText)
{
    m_notification->setText(alarmText);
}

QDateTime AlarmNotification::remindAt() const
{
    return m_remind_at;
}

void AlarmNotification::setRemindAt(const QDateTime &remindAtDt)
{
    m_remind_at = remindAtDt;
}
