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

#ifndef __UTC_CALENDAR_LIST_H__
#define __UTC_CALENDAR_LIST_H__

void utc_calendar_list_startup(void);
void utc_calendar_list_cleanup(void);
int utc_calendar_list_create_p(void);
int utc_calendar_list_create_n(void);
int utc_calendar_list_destroy_p(void);
int utc_calendar_list_destroy_n(void);
int utc_calendar_list_get_count_p(void);
int utc_calendar_list_get_count_n(void);
int utc_calendar_list_add_p(void);
int utc_calendar_list_add_n(void);
int utc_calendar_list_remove_p(void);
int utc_calendar_list_remove_n(void);
int utc_calendar_list_get_current_record_p_p(void);
int utc_calendar_list_get_current_record_p_n(void);
int utc_calendar_list_prev_p(void);
int utc_calendar_list_prev_n(void);
int utc_calendar_list_next_p(void);
int utc_calendar_list_next_n(void);
int utc_calendar_list_first_p(void);
int utc_calendar_list_first_n(void);
int utc_calendar_list_last_p(void);
int utc_calendar_list_last_n(void);

#endif /* __UTC_CALENDAR_LIST_H__ */
