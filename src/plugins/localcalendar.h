/*
 * Copyright (C) 2018 Dimitris Kardarakos
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LOCALCALENDAR_H
#define LOCALCALENDAR_H

#include <QSharedPointer>
#include <KCalCore/MemoryCalendar>
#include <KCalCore/FileStorage>
#include <KCalCore/Event>

using namespace KCalCore;

class LocalCalendar : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QSharedPointer<MemoryCalendar> memorycalendar READ memorycalendar WRITE setMemorycalendar NOTIFY memorycalendarChanged)
    Q_PROPERTY(QSharedPointer<FileStorage> calendarstorage READ calendarstorage WRITE setCalendarstorage NOTIFY calendarstorageChanged)
    Q_PROPERTY(QDateTime nulldate READ nulldate CONSTANT)

public:
    explicit LocalCalendar(QObject* parent = nullptr);
    ~LocalCalendar() override;

    MemoryCalendar::Ptr memorycalendar() const;
    FileStorage::Ptr calendarstorage() const;
    QString name() const;
    QDateTime nulldate() const;

    void setMemorycalendar(MemoryCalendar::Ptr memoryCalendar);
    void setCalendarstorage(FileStorage::Ptr calendarStorage);
    void setName(QString calendarName);

public Q_SLOTS:
    void addEditTask(QString uid, QDate startDate, QString summary, QString description, int startHour, int startMinute, bool allDayFlg, QString location, bool completed);
    void deleteTask(QString uid);
    int todosCount(const QDate &date) const;
    void deleteCalendar();
    int eventsCount(const QDate& date) const;
    bool save();
Q_SIGNALS:
    void memorycalendarChanged();
    void calendarstorageChanged();
    void nameChanged();

private:
    MemoryCalendar::Ptr m_calendar;
    FileStorage::Ptr m_cal_storage;
    QString m_name;
    QString m_fullpath;
};

#endif // LOCALCALENDAR_H

