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

#ifndef __UTC_CALENDAR_RECORD_H__
#define __UTC_CALENDAR_RECORD_H__

void utc_calendar_record_startup(void);
void utc_calendar_record_cleanup(void);
int utc_calendar_record_create_p(void);
int utc_calendar_record_create_n(void);
int utc_calendar_record_destroy_p(void);
int utc_calendar_record_destroy_n(void);
int utc_calendar_record_clone_p(void);
int utc_calendar_record_clone_n(void);
int utc_calendar_record_get_uri_p_p(void);
int utc_calendar_record_get_uri_p_n(void);
int utc_calendar_record_get_str_p(void);
int utc_calendar_record_get_str_n(void);
int utc_calendar_record_get_str_p_p(void);
int utc_calendar_record_get_str_p_n(void);
int utc_calendar_record_get_int_p(void);
int utc_calendar_record_get_int_n(void);
int utc_calendar_record_get_double_p(void);
int utc_calendar_record_get_double_n(void);
int utc_calendar_record_get_lli_p(void);
int utc_calendar_record_get_lli_n(void);
int utc_calendar_record_get_caltime_p(void);
int utc_calendar_record_get_caltime_n(void);
int utc_calendar_record_set_str_p(void);
int utc_calendar_record_set_str_n(void);
int utc_calendar_record_set_int_p(void);
int utc_calendar_record_set_int_n(void);
int utc_calendar_record_set_double_p(void);
int utc_calendar_record_set_double_n(void);
int utc_calendar_record_set_lli_p(void);
int utc_calendar_record_set_lli_n(void);
int utc_calendar_record_set_caltime_p(void);
int utc_calendar_record_set_caltime_n(void);
int utc_calendar_record_add_child_record_p(void);
int utc_calendar_record_add_child_record_n(void);
int utc_calendar_record_remove_child_record_p(void);
int utc_calendar_record_remove_child_record_n(void);
int utc_calendar_record_get_child_record_count_p(void);
int utc_calendar_record_get_child_record_count_n(void);
int utc_calendar_record_get_child_record_at_p_p(void);
int utc_calendar_record_get_child_record_at_p_n(void);
int utc_calendar_record_clone_child_record_list_p(void);
int utc_calendar_record_clone_child_record_list_n(void);

#endif /* __UTC_CALENDAR_RECORD_H__ */

