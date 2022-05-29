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
#ifndef __TCT_RUNTIME-INFO-NATIVE_H__
#define __TCT_RUNTIME-INFO-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_runtime_info_startup(void);
extern void ITs_runtime_info_cleanup(void);

extern int ITc_runtime_info_get_value_bool_p(void);
extern int ITc_runtime_info_get_value_string_p(void);
extern int ITc_runtime_info_get_value_int_p(void);
extern int ITc_runtime_info_set_unset_changed_cb_p(void);
extern int ITc_runtime_info_get_system_memory_info_p(void);
extern int ITc_runtime_info_get_process_memory_info_p(void);
extern int ITc_runtime_info_get_cpu_usage_p(void);
extern int ITc_runtime_info_get_process_cpu_usage_p(void);
extern int ITc_runtime_info_get_processor_count_p(void);
extern int ITc_runtime_info_get_processor_current_frequency_p(void);
extern int ITc_runtime_info_get_processor_max_frequency_p(void);
extern int ITc_runtime_info_get_physical_memory_size_p(void);
extern int ITc_runtime_info_get_all_apps_cpu_rate_p(void);
extern int ITc_runtime_info_app_usage_get_usage_p(void);
extern int ITc_runtime_info_app_usage_get_appid_p(void);
extern int ITc_runtime_info_app_usage_get_count_p(void);
extern int ITc_runtime_info_app_usage_destroy_p(void);

testcase tc_array[] = {
	{"ITc_runtime_info_get_value_bool_p",ITc_runtime_info_get_value_bool_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_get_value_string_p",ITc_runtime_info_get_value_string_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_get_value_int_p",ITc_runtime_info_get_value_int_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_set_unset_changed_cb_p",ITc_runtime_info_set_unset_changed_cb_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_get_system_memory_info_p",ITc_runtime_info_get_system_memory_info_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_get_process_memory_info_p",ITc_runtime_info_get_process_memory_info_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_get_cpu_usage_p",ITc_runtime_info_get_cpu_usage_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_get_process_cpu_usage_p",ITc_runtime_info_get_process_cpu_usage_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_get_processor_count_p",ITc_runtime_info_get_processor_count_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_get_processor_current_frequency_p",ITc_runtime_info_get_processor_current_frequency_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_get_processor_max_frequency_p",ITc_runtime_info_get_processor_max_frequency_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_get_physical_memory_size_p",ITc_runtime_info_get_physical_memory_size_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},	
	{"ITc_runtime_info_get_all_apps_cpu_rate_p",ITc_runtime_info_get_all_apps_cpu_rate_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_app_usage_get_usage_p",ITc_runtime_info_app_usage_get_usage_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_app_usage_get_appid_p",ITc_runtime_info_app_usage_get_appid_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_app_usage_get_count_p",ITc_runtime_info_app_usage_get_count_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{"ITc_runtime_info_app_usage_destroy_p",ITc_runtime_info_app_usage_destroy_p,ITs_runtime_info_startup,ITs_runtime_info_cleanup},
	{NULL, NULL}
};

#endif // __TCT_RUNTIME-INFO-NATIVE_H__
