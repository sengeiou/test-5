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

#ifndef __UTC_CALENDAR_HELPER_EVENT_BOOK_H__
#define __UTC_CALENDAR_HELPER_EVENT_BOOK_H__

#include <calendar.h>

int utc_calendar_helper_event_book_set_new_str(calendar_record_h record);
int utc_calendar_helper_event_book_set_new_int(calendar_record_h record);
int utc_calendar_helper_event_book_set_new_double(calendar_record_h record);
int utc_calendar_helper_event_book_set_new_caltime(calendar_record_h record);
int utc_calendar_helper_event_book_set_new(calendar_record_h record);
int utc_calendar_helper_event_book_set_mod_str(calendar_record_h record);
int utc_calendar_helper_event_book_set_mod_int(calendar_record_h record);
int utc_calendar_helper_event_book_set_mod_double(calendar_record_h record);
int utc_calendar_helper_event_book_set_mod_caltime(calendar_record_h record);
int utc_calendar_helper_event_book_set_mod(calendar_record_h record);
int utc_calendar_helper_event_book_check_new_str(calendar_record_h record);
int utc_calendar_helper_event_book_check_new_str_p(calendar_record_h record);
int utc_calendar_helper_event_book_check_new_int(calendar_record_h record);
int utc_calendar_helper_event_book_check_new_double(calendar_record_h record);
int utc_calendar_helper_event_book_check_new_caltime(calendar_record_h record);
int utc_calendar_helper_event_book_check_new(calendar_record_h record);
int utc_calendar_helper_event_book_check_mod_str(calendar_record_h record);
int utc_calendar_helper_event_book_check_mod_int(calendar_record_h record);
int utc_calendar_helper_event_book_check_mod_double(calendar_record_h record);
int utc_calendar_helper_event_book_check_mod_caltime(calendar_record_h record);
int utc_calendar_helper_event_book_check_mod(calendar_record_h record);

#endif /* __UTC_CALENDAR_HELPER_EVENT_BOOK_H__ */
