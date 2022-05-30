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

#ifndef __UTC_CALENDAR_QUERY_H__
#define __UTC_CALENDAR_QUERY_H__

void utc_calendar_query_startup(void);
void utc_calendar_query_cleanup(void);
int utc_calendar_query_create_p(void);
int utc_calendar_query_create_n(void);
int utc_calendar_query_destroy_p(void);
int utc_calendar_query_destroy_n(void);
int utc_calendar_query_set_projection_p(void);
int utc_calendar_query_set_projection_n(void);
int utc_calendar_query_set_distinct_p(void);
int utc_calendar_query_set_distinct_n(void);
int utc_calendar_query_set_filter_p(void);
int utc_calendar_query_set_filter_n(void);
int utc_calendar_query_set_sort_p(void);
int utc_calendar_query_set_sort_n(void);

#endif /* __UTC_CALENDAR_QUERY_H__ */
