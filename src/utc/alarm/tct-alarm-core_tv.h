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

extern void utc_alarm_startup(void);
extern void utc_alarm_cleanup(void);

extern int utc_alarm_schedule_after_delay_p(void);
extern int utc_alarm_schedule_after_delay_n1(void);
extern int utc_alarm_schedule_after_delay_n2(void);
extern int utc_alarm_schedule_after_delay_n3(void);
extern int utc_alarm_schedule_after_delay_n4(void);
extern int utc_alarm_schedule_at_date_p(void);
extern int utc_alarm_schedule_at_date_n(void);
extern int utc_alarm_schedule_once_after_delay_p(void);
extern int utc_alarm_schedule_once_after_delay_n1(void);
extern int utc_alarm_schedule_once_after_delay_n2(void);
extern int utc_alarm_schedule_once_after_delay_n3(void);
extern int utc_alarm_cancel_p(void);
extern int utc_alarm_cancel_n(void);
extern int utc_alarm_cancel_all_p(void);
extern int utc_alarm_foreach_registered_alarm_p(void);
extern int utc_alarm_foreach_registered_alarm_n(void);
extern int utc_alarm_get_scheduled_date_p(void);
extern int utc_alarm_get_scheduled_date_n(void);
extern int utc_alarm_get_scheduled_period_p(void);
extern int utc_alarm_get_scheduled_period_n1(void);
extern int utc_alarm_get_scheduled_period_n2(void);
extern int utc_alarm_schedule_once_at_date_p(void);
extern int utc_alarm_schedule_once_at_date_n1(void);
extern int utc_alarm_schedule_once_at_date_n2(void);
extern int utc_alarm_schedule_once_at_date_n3(void);
extern int utc_alarm_schedule_with_recurrence_week_flag_p(void);
extern int utc_alarm_schedule_with_recurrence_week_flag_n1(void);
extern int utc_alarm_schedule_with_recurrence_week_flag_n2(void);
extern int utc_alarm_schedule_with_recurrence_week_flag_n3(void);
extern int utc_alarm_get_scheduled_recurrence_week_flag_p(void);
extern int utc_alarm_get_scheduled_recurrence_week_flag_n(void);
extern int utc_alarm_get_current_time_p(void);
extern int utc_alarm_get_current_time_n(void);
extern int utc_alarm_get_app_control_p(void);
extern int utc_alarm_get_app_control_n1(void);
extern int utc_alarm_get_app_control_n2(void);
extern int utc_alarm_set_global_p(void);
extern int utc_alarm_set_global_n1(void);
extern int utc_alarm_set_global_n2(void);
extern int utc_alarm_get_global_p(void);
extern int utc_alarm_get_global_n(void);
extern int utc_alarm_schedule_noti_once_at_date_p(void);
extern int utc_alarm_schedule_noti_once_at_date_n1(void);
extern int utc_alarm_schedule_noti_once_at_date_n2(void);
extern int utc_alarm_schedule_noti_after_delay_p(void);
extern int utc_alarm_schedule_noti_after_delay_n1(void);
extern int utc_alarm_schedule_noti_after_delay_n2(void);
extern int utc_alarm_schedule_noti_once_after_delay_p(void);
extern int utc_alarm_schedule_noti_once_after_delay_n1(void);
extern int utc_alarm_schedule_noti_once_after_delay_n2(void);
extern int utc_alarm_schedule_noti_with_recurrence_week_flag_p(void);
extern int utc_alarm_schedule_noti_with_recurrence_week_flag_n1(void);
extern int utc_alarm_schedule_noti_with_recurrence_week_flag_n2(void);
extern int utc_alarm_get_notification_p(void);
extern int utc_alarm_get_notification_n(void);
extern int utc_alarm_update_delay_p(void);
extern int utc_alarm_update_delay_n1(void);
extern int utc_alarm_update_delay_n2(void);
extern int utc_alarm_update_delay_n3(void);
extern int utc_alarm_update_date_p(void);
extern int utc_alarm_update_date_n1(void);
extern int utc_alarm_update_date_n2(void);
extern int utc_alarm_update_date_n3(void);
extern int utc_alarm_update_period_p1(void);
extern int utc_alarm_update_period_p2(void);
extern int utc_alarm_update_period_p3(void);
extern int utc_alarm_update_period_n1(void);
extern int utc_alarm_update_period_n2(void);
extern int utc_alarm_update_week_flag_p1(void);
extern int utc_alarm_update_week_flag_p2(void);
extern int utc_alarm_update_week_flag_n1(void);
extern int utc_alarm_update_week_flag_n2(void);
extern int utc_alarm_update_week_flag_n3(void);

testcase tc_array[] = {
	{"utc_alarm_schedule_after_delay_p",utc_alarm_schedule_after_delay_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_after_delay_n1",utc_alarm_schedule_after_delay_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_after_delay_n2",utc_alarm_schedule_after_delay_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_after_delay_n3",utc_alarm_schedule_after_delay_n3,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_after_delay_n4",utc_alarm_schedule_after_delay_n4,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_at_date_p",utc_alarm_schedule_at_date_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_at_date_n",utc_alarm_schedule_at_date_n,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_once_after_delay_p",utc_alarm_schedule_once_after_delay_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_once_after_delay_n1",utc_alarm_schedule_once_after_delay_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_once_after_delay_n2",utc_alarm_schedule_once_after_delay_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_once_after_delay_n3",utc_alarm_schedule_once_after_delay_n3,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_cancel_p",utc_alarm_cancel_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_cancel_n",utc_alarm_cancel_n,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_cancel_all_p",utc_alarm_cancel_all_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_foreach_registered_alarm_p",utc_alarm_foreach_registered_alarm_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_foreach_registered_alarm_n",utc_alarm_foreach_registered_alarm_n,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_scheduled_date_p",utc_alarm_get_scheduled_date_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_scheduled_date_n",utc_alarm_get_scheduled_date_n,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_scheduled_period_p",utc_alarm_get_scheduled_period_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_scheduled_period_n1",utc_alarm_get_scheduled_period_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_scheduled_period_n2",utc_alarm_get_scheduled_period_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_once_at_date_p",utc_alarm_schedule_once_at_date_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_once_at_date_n1",utc_alarm_schedule_once_at_date_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_once_at_date_n2",utc_alarm_schedule_once_at_date_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_once_at_date_n3",utc_alarm_schedule_once_at_date_n3,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_with_recurrence_week_flag_p",utc_alarm_schedule_with_recurrence_week_flag_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_with_recurrence_week_flag_n1",utc_alarm_schedule_with_recurrence_week_flag_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_with_recurrence_week_flag_n2",utc_alarm_schedule_with_recurrence_week_flag_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_with_recurrence_week_flag_n3",utc_alarm_schedule_with_recurrence_week_flag_n3,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_scheduled_recurrence_week_flag_p",utc_alarm_get_scheduled_recurrence_week_flag_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_scheduled_recurrence_week_flag_n",utc_alarm_get_scheduled_recurrence_week_flag_n,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_current_time_p",utc_alarm_get_current_time_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_current_time_n",utc_alarm_get_current_time_n,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_app_control_p",utc_alarm_get_app_control_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_app_control_n1",utc_alarm_get_app_control_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_app_control_n2",utc_alarm_get_app_control_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_set_global_p",utc_alarm_set_global_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_set_global_n1",utc_alarm_set_global_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_set_global_n2",utc_alarm_set_global_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_global_p",utc_alarm_get_global_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_global_n",utc_alarm_get_global_n,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_noti_once_at_date_p",utc_alarm_schedule_noti_once_at_date_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_noti_once_at_date_n1",utc_alarm_schedule_noti_once_at_date_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_noti_once_at_date_n2",utc_alarm_schedule_noti_once_at_date_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_noti_after_delay_p",utc_alarm_schedule_noti_after_delay_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_noti_after_delay_n1",utc_alarm_schedule_noti_after_delay_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_noti_after_delay_n2",utc_alarm_schedule_noti_after_delay_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_noti_once_after_delay_p",utc_alarm_schedule_noti_once_after_delay_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_noti_once_after_delay_n1",utc_alarm_schedule_noti_once_after_delay_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_noti_once_after_delay_n2",utc_alarm_schedule_noti_once_after_delay_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_noti_with_recurrence_week_flag_p",utc_alarm_schedule_noti_with_recurrence_week_flag_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_noti_with_recurrence_week_flag_n1",utc_alarm_schedule_noti_with_recurrence_week_flag_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_schedule_noti_with_recurrence_week_flag_n2",utc_alarm_schedule_noti_with_recurrence_week_flag_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_notification_p",utc_alarm_get_notification_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_get_notification_n",utc_alarm_get_notification_n,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_delay_p",utc_alarm_update_delay_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_delay_n1",utc_alarm_update_delay_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_delay_n2",utc_alarm_update_delay_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_delay_n3",utc_alarm_update_delay_n3,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_date_p",utc_alarm_update_date_p,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_date_n1",utc_alarm_update_date_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_date_n2",utc_alarm_update_date_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_date_n3",utc_alarm_update_date_n3,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_period_p1",utc_alarm_update_period_p1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_period_p2",utc_alarm_update_period_p2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_period_p3",utc_alarm_update_period_p3,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_period_n1",utc_alarm_update_period_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_period_n2",utc_alarm_update_period_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_week_flag_p1",utc_alarm_update_week_flag_p1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_week_flag_p2",utc_alarm_update_week_flag_p2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_week_flag_n1",utc_alarm_update_week_flag_n1,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_week_flag_n2",utc_alarm_update_week_flag_n2,utc_alarm_startup,utc_alarm_cleanup},
	{"utc_alarm_update_week_flag_n3",utc_alarm_update_week_flag_n3,utc_alarm_startup,utc_alarm_cleanup},
	{NULL, NULL}
};

#endif // __TCT_ALARM-NATIVE_H__
