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

#ifndef __UTC_CALENDAR_FILTER_H__
#define __UTC_CALENDAR_FILTER_H__

void utc_calendar_filter_startup(void);
void utc_calendar_filter_cleanup(void);
int utc_calendar_filter_create_p(void);
int utc_calendar_filter_create_n(void);
int utc_calendar_filter_destroy_p(void);
int utc_calendar_filter_destroy_n(void);
int utc_calendar_filter_add_str_p(void);
int utc_calendar_filter_add_str_n(void);
int utc_calendar_filter_add_int_p(void);
int utc_calendar_filter_add_int_n(void);
int utc_calendar_filter_add_double_p(void);
int utc_calendar_filter_add_double_n(void);
int utc_calendar_filter_add_lli_p(void);
int utc_calendar_filter_add_lli_n(void);
int utc_calendar_filter_add_caltime_p(void);
int utc_calendar_filter_add_caltime_n(void);
int utc_calendar_filter_add_filter_p(void);
int utc_calendar_filter_add_filter_n(void);
int utc_calendar_filter_add_operator_p(void);
int utc_calendar_filter_add_operator_n(void);

#endif /* __UTC_CALENDAR_FILTER_H__ */
