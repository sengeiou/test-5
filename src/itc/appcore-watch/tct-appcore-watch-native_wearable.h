//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef __TCT_APPCORE-WATCH-NATIVE_H__
#define __TCT_APPCORE-WATCH-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_appcore_watch_startup(void);
extern void ITs_appcore_watch_cleanup(void);

extern int ITc_appcore_watch_watch_app_add_remove_event_handler_p(void);
extern int ITc_appcore_watch_watch_time_get_current_time_delete_p(void);
extern int ITc_appcore_watch_watch_time_get_year_p(void);
extern int ITc_appcore_watch_watch_time_get_month_p(void);
extern int ITc_appcore_watch_watch_time_get_day_p(void);
extern int ITc_appcore_watch_watch_time_get_day_of_week_p(void);
extern int ITc_appcore_watch_watch_time_get_hour_p(void);
extern int ITc_appcore_watch_watch_time_get_hour24_p(void);
extern int ITc_appcore_watch_watch_time_get_minute_p(void);
extern int ITc_appcore_watch_watch_time_get_second_p(void);
extern int ITc_appcore_watch_watch_time_get_millisecond_p(void);
extern int ITc_appcore_watch_watch_time_get_utc_time_p(void);
extern int ITc_appcore_watch_watch_time_get_utc_timestamp_p(void);
extern int ITc_appcore_watch_watch_time_get_time_zone_p(void);
extern int ITc_appcore_watch_watch_app_set_get_ambient_tick_type_p(void);
extern int ITc_appcore_watch_watch_app_set_get_time_tick_frequency_p(void);
extern int ITc_appcore_watch_watch_time_get_dst_status_p(void);

testcase tc_array[] = {
	{"ITc_appcore_watch_watch_app_add_remove_event_handler_p",ITc_appcore_watch_watch_app_add_remove_event_handler_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_current_time_delete_p",ITc_appcore_watch_watch_time_get_current_time_delete_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_year_p",ITc_appcore_watch_watch_time_get_year_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_month_p",ITc_appcore_watch_watch_time_get_month_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_day_p",ITc_appcore_watch_watch_time_get_day_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_day_of_week_p",ITc_appcore_watch_watch_time_get_day_of_week_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_hour_p",ITc_appcore_watch_watch_time_get_hour_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_hour24_p",ITc_appcore_watch_watch_time_get_hour24_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_minute_p",ITc_appcore_watch_watch_time_get_minute_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_second_p",ITc_appcore_watch_watch_time_get_second_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_millisecond_p",ITc_appcore_watch_watch_time_get_millisecond_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_utc_time_p",ITc_appcore_watch_watch_time_get_utc_time_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_utc_timestamp_p",ITc_appcore_watch_watch_time_get_utc_timestamp_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_time_zone_p",ITc_appcore_watch_watch_time_get_time_zone_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_app_set_get_ambient_tick_type_p",ITc_appcore_watch_watch_app_set_get_ambient_tick_type_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_app_set_get_time_tick_frequency_p",ITc_appcore_watch_watch_app_set_get_time_tick_frequency_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{"ITc_appcore_watch_watch_time_get_dst_status_p",ITc_appcore_watch_watch_time_get_dst_status_p,ITs_appcore_watch_startup,ITs_appcore_watch_cleanup},
	{NULL, NULL}
};

#endif // __TCT_APPCORE-WATCH-NATIVE_H__
