/*
 * Copyright (c) 2017 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __TCT_JOB_SCHEDULER_NATIVE_H__
#define __TCT_JOB_SCHEDULER_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_job_info_create_p_cleanup(void);
extern int utc_job_info_create_p(void);
extern int utc_job_info_create_n(void);
extern void utc_job_info_destroy_p_startup(void);
extern void utc_job_info_destroy_p_cleanup(void);
extern int utc_job_info_destroy_p(void);
extern int utc_job_info_destroy_n(void);
extern void utc_job_info_set_periodic_p_startup(void);
extern void utc_job_info_set_periodic_p_cleanup(void);
extern int utc_job_info_set_periodic_p(void);
extern int utc_job_info_set_periodic_n(void);
extern void utc_job_info_set_persistent_p_startup(void);
extern void utc_job_info_set_persistent_p_cleanup(void);
extern int utc_job_info_set_persistent_p(void);
extern int utc_job_info_set_persistent_n(void);
extern void utc_job_info_set_once_p_startup(void);
extern void utc_job_info_set_once_p_cleanup(void);
extern int utc_job_info_set_once_p(void);
extern int utc_job_info_set_once_n(void);
extern void utc_job_info_set_requirement_timeout_p_startup(void);
extern void utc_job_info_set_requirement_timeout_p_cleanup(void);
extern int utc_job_info_set_requirement_timeout_p(void);
extern int utc_job_info_set_requirement_timeout_n(void);
extern void utc_job_info_set_requires_battery_not_low_p_startup(void);
extern void utc_job_info_set_requires_battery_not_low_p_cleanup(void);
extern int utc_job_info_set_requires_battery_not_low_p(void);
extern int utc_job_info_set_requires_battery_not_low_n1(void);
extern void utc_job_info_set_requires_battery_not_low_n2_startup(void);
extern void utc_job_info_set_requires_battery_not_low_n2_cleanup(void);
extern int utc_job_info_set_requires_battery_not_low_n2(void);
extern void utc_job_info_set_requires_charging_p_startup(void);
extern void utc_job_info_set_requires_charging_p_cleanup(void);
extern int utc_job_info_set_requires_charging_p(void);
extern int utc_job_info_set_requires_charging_n1(void);
extern void utc_job_info_set_requires_charging_n2_startup(void);
extern void utc_job_info_set_requires_charging_n2_cleanup(void);
extern int utc_job_info_set_requires_charging_n2(void);
extern void utc_job_info_set_requires_wifi_connection_p_startup(void);
extern void utc_job_info_set_requires_wifi_connection_p_cleanup(void);
extern int utc_job_info_set_requires_wifi_connection_p(void);
extern int utc_job_info_set_requires_wifi_connection_n1(void);
extern void utc_job_info_set_requires_wifi_connection_n2_startup(void);
extern void utc_job_info_set_requires_wifi_connection_n2_cleanup(void);
extern int utc_job_info_set_requires_wifi_connection_n2(void);
extern void utc_job_info_add_trigger_event_p_startup(void);
extern void utc_job_info_add_trigger_event_p_cleanup(void);
extern int utc_job_info_add_trigger_event_p1(void);
extern int utc_job_info_add_trigger_event_p2(void);
extern int utc_job_info_add_trigger_event_p3(void);
extern int utc_job_info_add_trigger_event_p4(void);
extern int utc_job_info_add_trigger_event_p5(void);
extern int utc_job_info_add_trigger_event_p6(void);
extern int utc_job_info_add_trigger_event_p7(void);
extern int utc_job_info_add_trigger_event_p8(void);
extern int utc_job_info_add_trigger_event_p9(void);
extern int utc_job_info_add_trigger_event_p10(void);
extern int utc_job_info_add_trigger_event_p11(void);
extern int utc_job_info_add_trigger_event_p12(void);
extern int utc_job_info_add_trigger_event_p13(void);
extern int utc_job_info_add_trigger_event_p14(void);
extern int utc_job_info_add_trigger_event_p15(void);
extern int utc_job_info_add_trigger_event_p16(void);
extern int utc_job_info_add_trigger_event_p17(void);
extern int utc_job_info_add_trigger_event_p18(void);
extern int utc_job_info_add_trigger_event_p19(void);
extern int utc_job_info_add_trigger_event_p20(void);
extern int utc_job_info_add_trigger_event_p21(void);
extern int utc_job_info_add_trigger_event_n1(void);
extern void utc_job_info_add_trigger_event_n2_startup(void);
extern void utc_job_info_add_trigger_event_n2_cleanup(void);
extern int utc_job_info_add_trigger_event_n2(void);
extern void utc_job_info_add_trigger_event_n3_startup(void);
extern void utc_job_info_add_trigger_event_n3_cleanup(void);
extern int utc_job_info_add_trigger_event_n3(void);
extern void utc_job_info_add_trigger_event_n4_startup(void);
extern void utc_job_info_add_trigger_event_n4_cleanup(void);
extern int utc_job_info_add_trigger_event_n4(void);
extern void utc_job_info_remove_trigger_event_p_startup(void);
extern void utc_job_info_remove_trigger_event_p_cleanup(void);
extern int utc_job_info_remove_trigger_event_p(void);
extern int utc_job_info_remove_trigger_event_n1(void);
extern void utc_job_info_remove_trigger_event_n2_startup(void);
extern void utc_job_info_remove_trigger_event_n2_cleanup(void);
extern int utc_job_info_remove_trigger_event_n2(void);
extern void utc_job_info_remove_trigger_event_n3_startup(void);
extern void utc_job_info_remove_trigger_event_n3_cleanup(void);
extern int utc_job_info_remove_trigger_event_n3(void);
extern void utc_job_info_get_job_id_p_startup(void);
extern void utc_job_info_get_job_id_p_cleanup(void);
extern int utc_job_info_get_job_id_p(void);
extern int utc_job_info_get_job_id_n1(void);
extern void utc_job_info_get_job_id_n2_startup(void);
extern void utc_job_info_get_job_id_n2_cleanup(void);
extern int utc_job_info_get_job_id_n2(void);
extern void utc_job_info_get_job_id_n3_startup(void);
extern void utc_job_info_get_job_id_n3_cleanup(void);
extern int utc_job_info_get_job_id_n3(void);
extern void utc_job_info_clone_p_startup(void);
extern void utc_job_info_clone_p_cleanup(void);
extern int utc_job_info_clone_p(void);
extern int utc_job_info_clone_n1(void);
extern void utc_job_info_clone_n2_startup(void);
extern void utc_job_info_clone_n2_cleanup(void);
extern int utc_job_info_clone_n2(void);
extern int utc_job_info_clone_n3(void);
extern void utc_job_scheduler_init_p_cleanup(void);
extern int utc_job_scheduler_init_p(void);
extern void utc_job_scheduler_finish_p_startup(void);
extern int utc_job_scheduler_finish_p(void);
extern int utc_job_scheduler_finish_n(void);
extern void utc_job_scheduler_schedule_p_startup(void);
extern void utc_job_scheduler_schedule_p_cleanup(void);
extern int utc_job_scheduler_schedule_p(void);
extern int utc_job_scheduler_schedule_n1(void);
extern void utc_job_scheduler_schedule_n2_startup(void);
extern void utc_job_scheduler_schedule_n2_cleanup(void);
extern int utc_job_scheduler_schedule_n2(void);
extern void utc_job_scheduler_schedule_n3_startup(void);
extern void utc_job_scheduler_schedule_n3_cleanup(void);
extern int utc_job_scheduler_schedule_n3(void);
extern void utc_job_scheduler_schedule_n4_startup(void);
extern void utc_job_scheduler_schedule_n4_cleanup(void);
extern int utc_job_scheduler_schedule_n4(void);
extern void utc_job_scheduler_cancel_p_startup(void);
extern void utc_job_scheduler_cancel_p_cleanup(void);
extern int utc_job_scheduler_cancel_p(void);
extern int utc_job_scheduler_cancel_n1(void);
extern int utc_job_scheduler_cancel_n2(void);
extern void utc_job_scheduler_cancel_n3_startup(void);
extern void utc_job_scheduler_cancel_n3_cleanup(void);
extern int utc_job_scheduler_cancel_n3(void);
extern void utc_job_scheduler_cancel_all_p_startup(void);
extern void utc_job_scheduler_cancel_all_p_cleanup(void);
extern int utc_job_scheduler_cancel_all_p(void);
extern int utc_job_scheduler_cancel_all_n(void);
extern void utc_job_scheduler_notify_job_finished_p_startup(void);
extern void utc_job_scheduler_notify_job_finished_p_cleanup(void);
extern int utc_job_scheduler_notify_job_finished_p(void);
extern int utc_job_scheduler_notify_job_finished_n1(void);
extern int utc_job_scheduler_notify_job_finished_n2(void);
extern void utc_job_scheduler_notify_job_finished_n3_startup(void);
extern void utc_job_scheduler_notify_job_finished_n3_cleanup(void);
extern int utc_job_scheduler_notify_job_finished_n3(void);
extern void utc_job_scheduler_foreach_job_p_startup(void);
extern void utc_job_scheduler_foreach_job_p_cleanup(void);
extern int utc_job_scheduler_foreach_job_p(void);
extern int utc_job_scheduler_foreach_job_n1(void);
extern int utc_job_scheduler_foreach_job_n2(void);
extern void utc_job_scheduler_foreach_job_n3_startup(void);
extern void utc_job_scheduler_foreach_job_n3_cleanup(void);
extern int utc_job_scheduler_foreach_job_n3(void);
extern void utc_job_scheduler_service_add_p_startup(void);
extern void utc_job_scheduler_service_add_p_cleanup(void);
extern int utc_job_scheduler_service_add_p(void);
extern int utc_job_scheduler_service_add_n1(void);
extern int utc_job_scheduler_service_add_n2(void);
extern int utc_job_scheduler_service_add_n3(void);
extern int utc_job_scheduler_service_add_n4(void);
extern int utc_job_scheduler_service_add_n5(void);
extern int utc_job_scheduler_service_add_n6(void);
extern int utc_job_scheduler_service_add_n7(void);
extern void utc_job_scheduler_service_remove_p_startup(void);
extern void utc_job_scheduler_service_remove_p_cleanup(void);
extern int utc_job_scheduler_service_remove_p(void);
extern int utc_job_scheduler_service_remove_n1(void);
extern void utc_job_scheduler_service_remove_n2_startup(void);
extern void utc_job_scheduler_service_remove_n2_cleanup(void);
extern int utc_job_scheduler_service_remove_n2(void);

testcase tc_array[] = {
	{"utc_job_info_create_p", utc_job_info_create_p, NULL, utc_job_info_create_p_cleanup},
	{"utc_job_info_create_n", utc_job_info_create_n, NULL, NULL},
	{"utc_job_info_destroy_p", utc_job_info_destroy_p, utc_job_info_destroy_p_startup, utc_job_info_destroy_p_cleanup},
	{"utc_job_info_destroy_n", utc_job_info_destroy_n, NULL, NULL},
	{"utc_job_info_set_periodic_p", utc_job_info_set_periodic_p, utc_job_info_set_periodic_p_startup, utc_job_info_set_periodic_p_cleanup},
	{"utc_job_info_set_periodic_n", utc_job_info_set_periodic_n, NULL, NULL},
	{"utc_job_info_set_persistent_p", utc_job_info_set_persistent_p, utc_job_info_set_persistent_p_startup, utc_job_info_set_persistent_p_cleanup},
	{"utc_job_info_set_persistent_n", utc_job_info_set_persistent_n, NULL, NULL},
	{"utc_job_info_set_once_p", utc_job_info_set_once_p, utc_job_info_set_once_p_startup, utc_job_info_set_once_p_cleanup},
	{"utc_job_info_set_once_n", utc_job_info_set_once_n, NULL, NULL},
	{"utc_job_info_set_requirement_timeout_p", utc_job_info_set_requirement_timeout_p, utc_job_info_set_requirement_timeout_p_startup, utc_job_info_set_requirement_timeout_p_cleanup},
	{"utc_job_info_set_requirement_timeout_n", utc_job_info_set_requirement_timeout_n, NULL, NULL},
	{"utc_job_info_set_requires_battery_not_low_p", utc_job_info_set_requires_battery_not_low_p, utc_job_info_set_requires_battery_not_low_p_startup, utc_job_info_set_requires_battery_not_low_p_cleanup},
	{"utc_job_info_set_requires_battery_not_low_n1", utc_job_info_set_requires_battery_not_low_n1, NULL, NULL},
	{"utc_job_info_set_requires_battery_not_low_n2", utc_job_info_set_requires_battery_not_low_n2, utc_job_info_set_requires_battery_not_low_n2_startup, utc_job_info_set_requires_battery_not_low_n2_cleanup},
	{"utc_job_info_set_requires_charging_p", utc_job_info_set_requires_charging_p, utc_job_info_set_requires_charging_p_startup, utc_job_info_set_requires_charging_p_cleanup},
	{"utc_job_info_set_requires_charging_n1", utc_job_info_set_requires_charging_n1, NULL, NULL},
	{"utc_job_info_set_requires_charging_n2", utc_job_info_set_requires_charging_n2, utc_job_info_set_requires_charging_n2_startup, utc_job_info_set_requires_charging_n2_cleanup},
	{"utc_job_info_set_requires_wifi_connection_p", utc_job_info_set_requires_wifi_connection_p, utc_job_info_set_requires_wifi_connection_p_startup, utc_job_info_set_requires_wifi_connection_p_cleanup},
	{"utc_job_info_set_requires_wifi_connection_n1", utc_job_info_set_requires_wifi_connection_n1, NULL, NULL},
	{"utc_job_info_set_requires_wifi_connection_n2", utc_job_info_set_requires_wifi_connection_n2, utc_job_info_set_requires_wifi_connection_n2_startup, utc_job_info_set_requires_wifi_connection_n2_cleanup},
	{"utc_job_info_add_trigger_event_p1", utc_job_info_add_trigger_event_p1, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p2", utc_job_info_add_trigger_event_p2, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p3", utc_job_info_add_trigger_event_p3, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p4", utc_job_info_add_trigger_event_p4, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p5", utc_job_info_add_trigger_event_p5, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p6", utc_job_info_add_trigger_event_p6, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p7", utc_job_info_add_trigger_event_p7, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p8", utc_job_info_add_trigger_event_p8, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p9", utc_job_info_add_trigger_event_p9, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p10", utc_job_info_add_trigger_event_p10, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p11", utc_job_info_add_trigger_event_p11, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p12", utc_job_info_add_trigger_event_p12, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p13", utc_job_info_add_trigger_event_p13, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p14", utc_job_info_add_trigger_event_p14, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p15", utc_job_info_add_trigger_event_p15, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p16", utc_job_info_add_trigger_event_p16, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p17", utc_job_info_add_trigger_event_p17, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p18", utc_job_info_add_trigger_event_p18, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p19", utc_job_info_add_trigger_event_p19, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p20", utc_job_info_add_trigger_event_p20, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_p21", utc_job_info_add_trigger_event_p21, utc_job_info_add_trigger_event_p_startup, utc_job_info_add_trigger_event_p_cleanup},
	{"utc_job_info_add_trigger_event_n1", utc_job_info_add_trigger_event_n1, NULL, NULL},
	{"utc_job_info_add_trigger_event_n2", utc_job_info_add_trigger_event_n2, utc_job_info_add_trigger_event_n2_startup, utc_job_info_add_trigger_event_n2_cleanup},
	{"utc_job_info_add_trigger_event_n3", utc_job_info_add_trigger_event_n3, utc_job_info_add_trigger_event_n3_startup, utc_job_info_add_trigger_event_n3_cleanup},
	{"utc_job_info_add_trigger_event_n4", utc_job_info_add_trigger_event_n4, utc_job_info_add_trigger_event_n4_startup, utc_job_info_add_trigger_event_n4_cleanup},
	{"utc_job_info_remove_trigger_event_p", utc_job_info_remove_trigger_event_p, utc_job_info_remove_trigger_event_p_startup, utc_job_info_remove_trigger_event_p_cleanup},
	{"utc_job_info_remove_trigger_event_n1", utc_job_info_remove_trigger_event_n1, NULL, NULL},
	{"utc_job_info_remove_trigger_event_n2", utc_job_info_remove_trigger_event_n2, utc_job_info_remove_trigger_event_n2_startup, utc_job_info_remove_trigger_event_n2_cleanup},
	{"utc_job_info_remove_trigger_event_n3", utc_job_info_remove_trigger_event_n3, utc_job_info_remove_trigger_event_n3_startup, utc_job_info_remove_trigger_event_n3_cleanup},
	{"utc_job_info_get_job_id_p", utc_job_info_get_job_id_p, utc_job_info_get_job_id_p_startup, utc_job_info_get_job_id_p_cleanup},
	{"utc_job_info_get_job_id_n1", utc_job_info_get_job_id_n1, NULL, NULL},
	{"utc_job_info_get_job_id_n2", utc_job_info_get_job_id_n2, utc_job_info_get_job_id_n2_startup, utc_job_info_get_job_id_n2_cleanup},
	{"utc_job_info_get_job_id_n3", utc_job_info_get_job_id_n3, utc_job_info_get_job_id_n3_startup, utc_job_info_get_job_id_n3_cleanup},
	{"utc_job_info_clone_p", utc_job_info_clone_p, utc_job_info_clone_p_startup, utc_job_info_clone_p_cleanup},
	{"utc_job_info_clone_n1", utc_job_info_clone_n1, NULL, NULL},
	{"utc_job_info_clone_n2", utc_job_info_clone_n2, utc_job_info_clone_n2_startup, utc_job_info_clone_n2_cleanup},
	{"utc_job_info_clone_n3", utc_job_info_clone_n3, NULL, NULL},
	{"utc_job_scheduler_init_p", utc_job_scheduler_init_p, NULL, utc_job_scheduler_init_p_cleanup},
	{"utc_job_scheduler_finish_p", utc_job_scheduler_finish_p, utc_job_scheduler_finish_p_startup, NULL},
	{"utc_job_scheduler_finish_n", utc_job_scheduler_finish_n, NULL, NULL},
	{"utc_job_scheduler_schedule_p", utc_job_scheduler_schedule_p, utc_job_scheduler_schedule_p_startup, utc_job_scheduler_schedule_p_cleanup},
	{"utc_job_scheduler_schedule_n1", utc_job_scheduler_schedule_n1, NULL, NULL},
	{"utc_job_scheduler_schedule_n2", utc_job_scheduler_schedule_n2, utc_job_scheduler_schedule_n2_startup, utc_job_scheduler_schedule_n2_cleanup},
	{"utc_job_scheduler_schedule_n3", utc_job_scheduler_schedule_n3, utc_job_scheduler_schedule_n3_startup, utc_job_scheduler_schedule_n3_cleanup},
	{"utc_job_scheduler_schedule_n4", utc_job_scheduler_schedule_n4, utc_job_scheduler_schedule_n4_startup, utc_job_scheduler_schedule_n4_cleanup},
	{"utc_job_scheduler_cancel_p", utc_job_scheduler_cancel_p, utc_job_scheduler_cancel_p_startup, utc_job_scheduler_cancel_p_cleanup},
	{"utc_job_scheduler_cancel_n1", utc_job_scheduler_cancel_n1, NULL, NULL},
	{"utc_job_scheduler_cancel_n2", utc_job_scheduler_cancel_n2, NULL, NULL},
	{"utc_job_scheduler_cancel_n3", utc_job_scheduler_cancel_n3, utc_job_scheduler_cancel_n3_startup, utc_job_scheduler_cancel_n3_cleanup},
	{"utc_job_scheduler_cancel_all_p", utc_job_scheduler_cancel_all_p, utc_job_scheduler_cancel_all_p_startup, utc_job_scheduler_cancel_all_p_cleanup},
	{"utc_job_scheduler_cancel_all_n", utc_job_scheduler_cancel_all_n, NULL, NULL},
	{"utc_job_scheduler_notify_job_finished_p", utc_job_scheduler_notify_job_finished_p, utc_job_scheduler_notify_job_finished_p_startup, utc_job_scheduler_notify_job_finished_p_cleanup},
	{"utc_job_scheduler_notify_job_finished_n1", utc_job_scheduler_notify_job_finished_n1, NULL, NULL},
	{"utc_job_scheduler_notify_job_finished_n2", utc_job_scheduler_notify_job_finished_n2, NULL, NULL},
	{"utc_job_scheduler_notify_job_finished_n3", utc_job_scheduler_notify_job_finished_n3, utc_job_scheduler_notify_job_finished_n3_startup, utc_job_scheduler_notify_job_finished_n3_cleanup},
	{"utc_job_scheduler_foreach_job_p", utc_job_scheduler_foreach_job_p, utc_job_scheduler_foreach_job_p_startup, utc_job_scheduler_foreach_job_p_cleanup},
	{"utc_job_scheduler_foreach_job_n1", utc_job_scheduler_foreach_job_n1, NULL, NULL},
	{"utc_job_scheduler_foreach_job_n2", utc_job_scheduler_foreach_job_n2, NULL, NULL},
	{"utc_job_scheduler_foreach_job_n3", utc_job_scheduler_foreach_job_n3, utc_job_scheduler_foreach_job_n3_startup, utc_job_scheduler_foreach_job_n3_cleanup},
	{"utc_job_scheduler_service_add_p", utc_job_scheduler_service_add_p, utc_job_scheduler_service_add_p_startup, utc_job_scheduler_service_add_p_cleanup},
	{"utc_job_scheduler_service_add_n1", utc_job_scheduler_service_add_n1, NULL, NULL},
	{"utc_job_scheduler_service_add_n2", utc_job_scheduler_service_add_n2, NULL, NULL},
	{"utc_job_scheduler_service_add_n3", utc_job_scheduler_service_add_n3, NULL, NULL},
	{"utc_job_scheduler_service_add_n4", utc_job_scheduler_service_add_n4, NULL, NULL},
	{"utc_job_scheduler_service_add_n5", utc_job_scheduler_service_add_n5, NULL, NULL},
	{"utc_job_scheduler_service_add_n6", utc_job_scheduler_service_add_n6, NULL, NULL},
	{"utc_job_scheduler_service_add_n7", utc_job_scheduler_service_add_n7, NULL, NULL},
	{"utc_job_scheduler_service_remove_p", utc_job_scheduler_service_remove_p, utc_job_scheduler_service_remove_p_startup, utc_job_scheduler_service_remove_p_cleanup},
	{"utc_job_scheduler_service_remove_n1", utc_job_scheduler_service_remove_n1, NULL, NULL},
	{"utc_job_scheduler_service_remove_n2", utc_job_scheduler_service_remove_n2, utc_job_scheduler_service_remove_n2_startup, utc_job_scheduler_service_remove_n2_cleanup},
	{NULL, NULL, NULL, NULL}
};

#endif /* __TCT_JOB_SCHEDULER_NATIVE_H__ */
