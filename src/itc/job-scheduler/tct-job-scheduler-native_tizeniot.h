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
#ifndef __TCT_JOB_SCHEDULER_NATIVE_H__
#define __TCT_JOB_SCHEDULER_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_job_info_cleanup(void);
extern void ITs_job_info_startup(void);
extern void ITs_job_info_event_cleanup(void);
extern void ITs_job_info_event_startup(void);
extern void ITs_job_scheduler_cleanup(void);
extern void ITs_job_scheduler_startup(void);
extern void ITs_job_scheduler_schedule_cleanup(void);
extern void ITs_job_scheduler_schedule_startup(void);
extern void ITs_job_scheduler_service_cleanup(void);
extern void ITs_job_scheduler_service_startup(void);

extern int ITc_job_info_create_destroy(void);
extern int ITc_job_info_set_periodic(void);
extern int ITc_job_info_set_persistent(void);
extern int ITc_job_info_set_once(void);
extern int ITc_job_info_set_requirement_timeout(void);
extern int ITc_job_info_set_requires_battery_not_low(void);
extern int ITc_job_info_set_requires_charging(void);
extern int ITc_job_info_set_requires_wifi_connection(void);
extern int ITc_job_info_add_trigger_event_battery(void);
extern int ITc_job_info_add_trigger_event(void);
extern int ITc_job_info_add_trigger_event_location(void);
extern int ITc_job_info_add_trigger_event_usb(void);
extern int ITc_job_info_add_trigger_event_network(void);
extern int ITc_job_info_remove_trigger_event(void);
extern int ITc_job_info_get_job_id(void);
extern int ITc_job_info_clone(void);
extern int ITc_job_scheduler_init_finish(void);
extern int ITc_job_scheduler_schedule(void);
extern int ITc_job_scheduler_cancel(void);
extern int ITc_job_scheduler_cancel_all(void);
extern int ITc_job_scheduler_notify_job_finished(void);
extern int ITc_job_scheduler_foreach_job(void);
extern int ITc_job_scheduler_service_add(void);
extern int ITc_job_scheduler_service_remove(void);

testcase tc_array[] = {
    {"ITc_job_info_create_destroy", ITc_job_info_create_destroy, ITs_job_info_startup, ITs_job_info_cleanup},
	{"ITc_job_info_set_periodic", ITc_job_info_set_periodic, ITs_job_info_startup, ITs_job_info_cleanup},
	{"ITc_job_info_set_persistent", ITc_job_info_set_persistent, ITs_job_info_startup, ITs_job_info_cleanup},
	{"ITc_job_info_set_once", ITc_job_info_set_once, ITs_job_info_startup, ITs_job_info_cleanup},
	{"ITc_job_info_set_requirement_timeout", ITc_job_info_set_requirement_timeout, ITs_job_info_startup, ITs_job_info_cleanup},
	{"ITc_job_info_set_requires_wifi_connection", ITc_job_info_set_requires_wifi_connection, ITs_job_info_event_startup, ITs_job_info_event_cleanup},
	{"ITc_job_info_set_requires_battery_not_low", ITc_job_info_set_requires_battery_not_low, ITs_job_info_event_startup, ITs_job_info_event_cleanup},
	{"ITc_job_info_set_requires_charging", ITc_job_info_set_requires_charging, ITs_job_info_event_startup, ITs_job_info_event_cleanup},
	{"ITc_job_info_add_trigger_event_battery", ITc_job_info_add_trigger_event_battery, ITs_job_info_event_startup, ITs_job_info_event_cleanup},
	{"ITc_job_info_add_trigger_event", ITc_job_info_add_trigger_event, ITs_job_info_event_startup, ITs_job_info_event_cleanup},
	{"ITc_job_info_add_trigger_event_location", ITc_job_info_add_trigger_event_location, ITs_job_info_event_startup, ITs_job_info_event_cleanup},
	{"ITc_job_info_add_trigger_event_usb", ITc_job_info_add_trigger_event_usb, ITs_job_info_event_startup, ITs_job_info_event_cleanup},
	{"ITc_job_info_add_trigger_event_network", ITc_job_info_add_trigger_event_network, ITs_job_info_event_startup, ITs_job_info_event_cleanup},
	{"ITc_job_info_remove_trigger_event", ITc_job_info_remove_trigger_event, ITs_job_info_event_startup, ITs_job_info_event_cleanup},
	{"ITc_job_info_get_job_id", ITc_job_info_get_job_id, ITs_job_scheduler_startup, ITs_job_scheduler_cleanup},
	{"ITc_job_info_clone", ITc_job_info_clone, ITs_job_info_startup, ITs_job_info_cleanup},
	{"ITc_job_scheduler_init_finish", ITc_job_scheduler_init_finish, ITs_job_scheduler_schedule_startup, ITs_job_scheduler_schedule_cleanup},
	{"ITc_job_scheduler_schedule", ITc_job_scheduler_schedule, ITs_job_scheduler_schedule_startup, ITs_job_scheduler_schedule_cleanup},
	{"ITc_job_scheduler_cancel", ITc_job_scheduler_cancel, ITs_job_scheduler_startup, ITs_job_scheduler_cleanup},
	{"ITc_job_scheduler_cancel_all", ITc_job_scheduler_cancel_all, ITs_job_scheduler_startup, ITs_job_scheduler_cleanup},
	{"ITc_job_scheduler_foreach_job", ITc_job_scheduler_foreach_job, ITs_job_scheduler_startup, ITs_job_scheduler_cleanup},
	{"ITc_job_scheduler_notify_job_finished", ITc_job_scheduler_notify_job_finished, ITs_job_scheduler_startup, ITs_job_scheduler_cleanup},
	{"ITc_job_scheduler_service_add", ITc_job_scheduler_service_add, ITs_job_scheduler_service_startup, ITs_job_scheduler_service_cleanup},
	{"ITc_job_scheduler_service_remove", ITc_job_scheduler_service_remove, ITs_job_scheduler_service_startup, ITs_job_scheduler_service_cleanup},
	{NULL, NULL}
};

#endif // __TCT_JOB_SCHEDULER_NATIVE_H__
