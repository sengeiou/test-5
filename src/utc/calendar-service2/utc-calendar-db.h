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

#ifndef __UTC_CALENDAR_DB_H__
#define __UTC_CALENDAR_DB_H__

#include "utc-calendar-db-alarm.h"
#include "utc-calendar-db-attendee.h"
#include "utc-calendar-db-book.h"
#include "utc-calendar-db-event.h"
#include "utc-calendar-db-event-book.h"
#include "utc-calendar-db-extended.h"
#include "utc-calendar-db-instance-localtime-book-extended.h"
#include "utc-calendar-db-instance-localtime-book.h"
#include "utc-calendar-db-instance-utime-book-extended.h"
#include "utc-calendar-db-instance-utime-book.h"
#include "utc-calendar-db-timezone.h"
#include "utc-calendar-db-todo.h"
#include "utc-calendar-db-todo-book.h"

void utc_calendar_db_startup(void);
void utc_calendar_db_cleanup(void);
int utc_calendar_db_insert_record_p(void);
int utc_calendar_db_insert_record_n(void);
int utc_calendar_db_get_record_p(void);
int utc_calendar_db_get_record_n(void);
int utc_calendar_db_update_record_p(void);
int utc_calendar_db_update_record_n(void);
int utc_calendar_db_delete_record_p(void);
int utc_calendar_db_delete_record_n(void);
int utc_calendar_db_get_all_records_p(void);
int utc_calendar_db_get_all_records_n(void);
int utc_calendar_db_get_records_with_query_p(void);
int utc_calendar_db_get_records_with_query_n(void);
int utc_calendar_db_get_count_p(void);
int utc_calendar_db_get_count_n(void);
int utc_calendar_db_get_count_with_query_p(void);
int utc_calendar_db_get_count_with_query_n(void);
int utc_calendar_db_insert_records_p(void);
int utc_calendar_db_insert_records_n(void);
int utc_calendar_db_update_records_p(void);
int utc_calendar_db_update_records_n(void);
int utc_calendar_db_delete_records_p(void);
int utc_calendar_db_delete_records_n(void);
int utc_calendar_db_get_current_version_p(void);
int utc_calendar_db_get_current_version_n(void);
int utc_calendar_db_add_changed_cb_p(void);
int utc_calendar_db_add_changed_cb_n(void);
int utc_calendar_db_remove_changed_cb_p(void);
int utc_calendar_db_remove_changed_cb_n(void);
int utc_calendar_db_get_changes_by_version_p(void);
int utc_calendar_db_get_changes_by_version_n(void);
int utc_calendar_db_insert_vcalendars_p(void);
int utc_calendar_db_insert_vcalendars_n(void);
int utc_calendar_db_replace_vcalendars_p(void);
int utc_calendar_db_replace_vcalendars_n(void);
int utc_calendar_db_replace_record_p(void);
int utc_calendar_db_replace_record_n(void);
int utc_calendar_db_replace_records_p(void);
int utc_calendar_db_replace_records_n(void);
int utc_calendar_db_get_last_change_version_p(void);
int utc_calendar_db_get_last_change_version_n(void);
int utc_calendar_db_get_changes_exception_by_version_p(void);
int utc_calendar_db_get_changes_exception_by_version_n(void);
int utc_calendar_db_clean_after_sync_p(void);
int utc_calendar_db_clean_after_sync_n(void);
int utc_calendar_db_link_record_p(void);
int utc_calendar_db_link_record_n(void);
int utc_calendar_db_unlink_record_p(void);
int utc_calendar_db_unlink_record_n(void);

#endif /* __UTC_CALENDAR_DB_H__ */

