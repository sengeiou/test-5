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
#ifndef __TCT_ALARM-NATIVE_H__
#define __TCT_ALARM-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_alarm_startup(void);
extern void ITs_alarm_cleanup(void);

extern int ITc_alarm_schedule_once_after_delay_p(void);
extern int ITc_alarm_schedule_once_at_date_p(void);
extern int ITc_alarm_schedule_with_recurrence_week_flag_p(void);
extern int ITc_alarm_foreach_registered_alarm_p(void);
extern int ITc_alarm_get_app_control_p(void);
extern int ITc_alarm_get_scheduled_period_p(void);
extern int ITc_alarm_get_scheduled_date_p(void);
extern int ITc_alarm_get_scheduled_recurrence_week_flag_p(void);
extern int ITc_alarm_cancel_p(void);
extern int ITc_alarm_cancel_all_p(void);
extern int ITc_alarm_get_current_time_p(void);
extern int ITc_alarm_set_get_global_p(void);
extern int ITc_alarm_schedule_noti_once_at_date_p(void);
extern int ITc_alarm_schedule_noti_after_delay_p(void);
extern int ITc_alarm_schedule_noti_once_after_delay_p(void);
extern int ITc_alarm_schedule_noti_with_recurrence_week_flag_p(void);
extern int ITc_alarm_get_notification_p(void);
extern int ITc_alarm_update_delay_p(void);
extern int ITc_alarm_update_date_p(void);
extern int ITc_alarm_update_period_p(void);
extern int ITc_alarm_update_week_flag_p(void);

testcase tc_array[] = {
	{"ITc_alarm_schedule_once_after_delay_p",ITc_alarm_schedule_once_after_delay_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_schedule_once_at_date_p",ITc_alarm_schedule_once_at_date_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_schedule_with_recurrence_week_flag_p",ITc_alarm_schedule_with_recurrence_week_flag_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_foreach_registered_alarm_p",ITc_alarm_foreach_registered_alarm_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_get_app_control_p",ITc_alarm_get_app_control_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_get_scheduled_period_p",ITc_alarm_get_scheduled_period_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_get_scheduled_date_p",ITc_alarm_get_scheduled_date_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_get_scheduled_recurrence_week_flag_p",ITc_alarm_get_scheduled_recurrence_week_flag_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_cancel_p",ITc_alarm_cancel_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_cancel_all_p",ITc_alarm_cancel_all_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_get_current_time_p",ITc_alarm_get_current_time_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_set_get_global_p",ITc_alarm_set_get_global_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_schedule_noti_once_at_date_p",ITc_alarm_schedule_noti_once_at_date_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_schedule_noti_after_delay_p",ITc_alarm_schedule_noti_after_delay_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_schedule_noti_once_after_delay_p",ITc_alarm_schedule_noti_once_after_delay_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_schedule_noti_with_recurrence_week_flag_p",ITc_alarm_schedule_noti_with_recurrence_week_flag_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_get_notification_p",ITc_alarm_get_notification_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_update_delay_p", ITc_alarm_update_delay_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_update_date_p", ITc_alarm_update_date_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_update_period_p", ITc_alarm_update_period_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{"ITc_alarm_update_week_flag_p",ITc_alarm_update_week_flag_p,ITs_alarm_startup,ITs_alarm_cleanup},
	{NULL, NULL}
};

#endif // __TCT_ALARM-NATIVE_H__
