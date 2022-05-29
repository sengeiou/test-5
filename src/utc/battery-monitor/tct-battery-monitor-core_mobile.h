/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
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

#ifndef __TCT_BATTERY_MONITOR_NATIVE_H__
#define __TCT_BATTERY_MONITOR_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_battery_monitor_startup(void);
extern void utc_battery_monitor_cleanup(void);
extern int utc_battery_monitor_battery_usage_data_destroy_p(void);
extern int utc_battery_monitor_battery_usage_data_destroy_n(void);

extern void utc_battery_monitor_startup(void);
extern void utc_battery_monitor_cleanup(void);
extern int utc_battery_monitor_usage_data_get_power_usage_per_resource_p(void);
extern int utc_battery_monitor_usage_data_get_power_usage_per_resource_n(void);

extern void utc_battery_monitor_startup(void);
extern void utc_battery_monitor_cleanup(void);
extern int utc_battery_monitor_get_power_usage_by_app_for_all_resources_p(void);
extern int utc_battery_monitor_get_power_usage_by_app_for_all_resources_n(void);

extern void utc_battery_monitor_startup(void);
extern void utc_battery_monitor_cleanup(void);
extern int utc_battery_monitor_get_power_usage_by_app_per_resource_p(void);
extern int utc_battery_monitor_get_power_usage_by_app_per_resource_n(void);

extern void utc_battery_monitor_startup(void);
extern void utc_battery_monitor_cleanup(void);
extern int utc_battery_monitor_get_power_usage_by_app_p(void);
extern int utc_battery_monitor_get_power_usage_by_app_n(void);

extern void utc_battery_monitor_startup(void);
extern void utc_battery_monitor_cleanup(void);
extern int utc_battery_monitor_get_power_usage_by_resource_p(void);
extern int utc_battery_monitor_get_power_usage_by_resource_n(void);

testcase tc_array[] = {
	{
		"utc_battery_monitor_battery_usage_data_destroy_p",
		utc_battery_monitor_battery_usage_data_destroy_p,
		utc_battery_monitor_startup,
		utc_battery_monitor_cleanup
	},
	{
		"utc_battery_monitor_battery_usage_data_destroy_n",
		utc_battery_monitor_battery_usage_data_destroy_n,
		utc_battery_monitor_startup,
		utc_battery_monitor_cleanup
	},
	{
		"utc_battery_monitor_usage_data_get_power_usage_per_resource_p",
		utc_battery_monitor_usage_data_get_power_usage_per_resource_p,
		utc_battery_monitor_startup,
		utc_battery_monitor_cleanup
	},
	{
		"utc_battery_monitor_usage_data_get_power_usage_per_resource_n",
		utc_battery_monitor_usage_data_get_power_usage_per_resource_n,
		utc_battery_monitor_startup,
		utc_battery_monitor_cleanup
	},
	{
		"utc_battery_monitor_get_power_usage_by_app_for_all_resources_p",
		utc_battery_monitor_get_power_usage_by_app_for_all_resources_p,
		utc_battery_monitor_startup,
		utc_battery_monitor_cleanup
	},
	{
		"utc_battery_monitor_get_power_usage_by_app_for_all_resources_n",
		utc_battery_monitor_get_power_usage_by_app_for_all_resources_n,
		utc_battery_monitor_startup,
		utc_battery_monitor_cleanup
	},
	{
		"utc_battery_monitor_get_power_usage_by_app_per_resource_p",
		utc_battery_monitor_get_power_usage_by_app_per_resource_p,
		utc_battery_monitor_startup,
		utc_battery_monitor_cleanup
	},
	{
		"utc_battery_monitor_get_power_usage_by_app_per_resource_n",
		utc_battery_monitor_get_power_usage_by_app_per_resource_n,
		utc_battery_monitor_startup,
		utc_battery_monitor_cleanup
	},
	{
		"utc_battery_monitor_get_power_usage_by_app_p",
		utc_battery_monitor_get_power_usage_by_app_p,
		utc_battery_monitor_startup,
		utc_battery_monitor_cleanup
	},
	{
		"utc_battery_monitor_get_power_usage_by_app_n",
		utc_battery_monitor_get_power_usage_by_app_n,
		utc_battery_monitor_startup,
		utc_battery_monitor_cleanup
	},
	{
		"utc_battery_monitor_get_power_usage_by_resource_p",
		utc_battery_monitor_get_power_usage_by_resource_p,
		utc_battery_monitor_startup,
		utc_battery_monitor_cleanup
	},
	{
		"utc_battery_monitor_get_power_usage_by_resource_n",
		utc_battery_monitor_get_power_usage_by_resource_n,
		utc_battery_monitor_startup,
		utc_battery_monitor_cleanup
	},
	{
		NULL,
		NULL,
		NULL,
		NULL
	}
};

#endif /* __TCT_BATTERY_MONITOR_NATIVE_H__ */
