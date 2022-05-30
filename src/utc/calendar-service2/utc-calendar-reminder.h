/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __UTC_CALENDAR_REMINDER_H__
#define __UTC_CALENDAR_REMINDER_H__

void utc_calendar_reminder_startup(void);
void utc_calendar_reminder_cleanup(void);
int utc_calendar_reminder_add_cb_utime_once_p(void);
int utc_calendar_reminder_add_cb_utime_daily_p(void);
int utc_calendar_reminder_add_cb_utime_weekly_p(void);
int utc_calendar_reminder_add_cb_utime_monthly_p(void);
int utc_calendar_reminder_add_cb_utime_yearly_p(void);
int utc_calendar_reminder_add_cb_utime_specific_p(void);
int utc_calendar_reminder_add_cb_localtime_once_p(void);
int utc_calendar_reminder_add_cb_localtime_daily_p(void);
int utc_calendar_reminder_add_cb_localtime_weekly_p(void);
int utc_calendar_reminder_add_cb_localtime_monthly_p(void);
int utc_calendar_reminder_add_cb_localtime_yearly_p(void);
int utc_calendar_reminder_add_cb_localtime_specific_p(void);
int utc_calendar_reminder_add_cb_n(void);
int utc_calendar_reminder_remove_cb_p(void);
int utc_calendar_reminder_remove_cb_n(void);

#endif /* __UTC_CALENDAR_REMINDER_H__ */
