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
#ifndef __TCT_STC_NATIVE_H__
#define __TCT_STC_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_stc_startup(void);
extern void utc_stc_cleanup(void);

extern int utc_stc_initialize_p(void);
extern int utc_stc_initialize_n(void);
extern int utc_stc_deinitialize_p(void);
extern int utc_stc_deinitialize_n(void);
extern int utc_stc_stats_rule_create_p(void);
extern int utc_stc_stats_rule_create_n(void);
extern int utc_stc_stats_rule_destroy_p(void);
extern int utc_stc_stats_rule_destroy_n(void);
extern int utc_stc_stats_rule_set_app_id_p(void);
extern int utc_stc_stats_rule_set_app_id_n(void);
extern int utc_stc_stats_rule_set_time_interval_p(void);
extern int utc_stc_stats_rule_set_time_interval_n(void);
extern int utc_stc_stats_rule_set_iface_type_p(void);
extern int utc_stc_stats_rule_set_iface_type_n(void);
extern int utc_stc_stats_rule_set_time_period_p(void);
extern int utc_stc_stats_rule_set_time_period_n(void);
extern int utc_stc_stats_rule_get_app_id_p(void);
extern int utc_stc_stats_rule_get_app_id_n(void);
extern int utc_stc_stats_rule_get_time_interval_p(void);
extern int utc_stc_stats_rule_get_time_interval_n(void);
extern int utc_stc_stats_rule_get_iface_type_p(void);
extern int utc_stc_stats_rule_get_iface_type_n(void);
extern int utc_stc_stats_rule_get_time_period_p(void);
extern int utc_stc_stats_rule_get_time_period_n(void);
extern int utc_stc_get_stats_p(void);
extern int utc_stc_get_stats_n(void);
extern int utc_stc_get_all_stats_p(void);
extern int utc_stc_get_all_stats_n(void);
extern int utc_stc_foreach_stats_p(void);
extern int utc_stc_foreach_stats_n(void);
extern int utc_stc_foreach_all_stats_p(void);
extern int utc_stc_foreach_all_stats_n(void);
extern int utc_stc_get_total_stats_p(void);
extern int utc_stc_get_total_stats_n(void);
extern int utc_stc_stats_info_clone_p(void);
extern int utc_stc_stats_info_clone_n(void);
extern int utc_stc_stats_info_destroy_p(void);
extern int utc_stc_stats_info_destroy_n(void);
extern int utc_stc_stats_info_get_app_id_p(void);
extern int utc_stc_stats_info_get_app_id_n(void);
extern int utc_stc_stats_info_get_iface_name_p(void);
extern int utc_stc_stats_info_get_iface_name_n(void);
extern int utc_stc_stats_info_get_time_interval_p(void);
extern int utc_stc_stats_info_get_time_interval_n(void);
extern int utc_stc_stats_info_get_iface_type_p(void);
extern int utc_stc_stats_info_get_iface_type_n(void);
extern int utc_stc_stats_info_get_counter_p(void);
extern int utc_stc_stats_info_get_counter_n(void);
extern int utc_stc_stats_info_get_roaming_type_p(void);
extern int utc_stc_stats_info_get_roaming_type_n(void);
extern int utc_stc_stats_info_get_protocol_type_p(void);
extern int utc_stc_stats_info_get_protocol_type_n(void);
extern int utc_stc_stats_info_get_process_state_p(void);
extern int utc_stc_stats_info_get_process_state_n(void);

testcase tc_array[] = {
	{"utc_stc_initialize_p",utc_stc_initialize_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_initialize_n",utc_stc_initialize_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_deinitialize_p",utc_stc_deinitialize_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_deinitialize_n",utc_stc_deinitialize_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_create_p",utc_stc_stats_rule_create_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_create_n",utc_stc_stats_rule_create_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_destroy_p",utc_stc_stats_rule_destroy_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_destroy_n",utc_stc_stats_rule_destroy_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_set_app_id_p",utc_stc_stats_rule_set_app_id_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_set_app_id_n",utc_stc_stats_rule_set_app_id_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_set_time_interval_p",utc_stc_stats_rule_set_time_interval_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_set_time_interval_n",utc_stc_stats_rule_set_time_interval_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_set_iface_type_p",utc_stc_stats_rule_set_iface_type_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_set_iface_type_n",utc_stc_stats_rule_set_iface_type_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_set_time_period_p",utc_stc_stats_rule_set_time_period_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_set_time_period_n",utc_stc_stats_rule_set_time_period_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_get_app_id_p",utc_stc_stats_rule_get_app_id_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_get_app_id_n",utc_stc_stats_rule_get_app_id_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_get_time_interval_p",utc_stc_stats_rule_get_time_interval_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_get_time_interval_n",utc_stc_stats_rule_get_time_interval_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_get_iface_type_p",utc_stc_stats_rule_get_iface_type_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_get_iface_type_n",utc_stc_stats_rule_get_iface_type_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_get_time_period_p",utc_stc_stats_rule_get_time_period_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_rule_get_time_period_n",utc_stc_stats_rule_get_time_period_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_get_stats_p",utc_stc_get_stats_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_get_stats_n",utc_stc_get_stats_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_get_all_stats_p",utc_stc_get_all_stats_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_get_all_stats_n",utc_stc_get_all_stats_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_foreach_stats_p",utc_stc_foreach_stats_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_foreach_stats_n",utc_stc_foreach_stats_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_foreach_all_stats_p",utc_stc_foreach_all_stats_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_foreach_all_stats_n",utc_stc_foreach_all_stats_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_get_total_stats_p",utc_stc_get_total_stats_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_get_total_stats_n",utc_stc_get_total_stats_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_clone_p",utc_stc_stats_info_clone_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_clone_n",utc_stc_stats_info_clone_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_destroy_p",utc_stc_stats_info_destroy_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_destroy_n",utc_stc_stats_info_destroy_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_app_id_p",utc_stc_stats_info_get_app_id_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_app_id_n",utc_stc_stats_info_get_app_id_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_iface_name_p",utc_stc_stats_info_get_iface_name_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_iface_name_n",utc_stc_stats_info_get_iface_name_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_time_interval_p",utc_stc_stats_info_get_time_interval_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_time_interval_n",utc_stc_stats_info_get_time_interval_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_iface_type_p",utc_stc_stats_info_get_iface_type_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_iface_type_n",utc_stc_stats_info_get_iface_type_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_counter_p",utc_stc_stats_info_get_counter_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_counter_n",utc_stc_stats_info_get_counter_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_roaming_type_p",utc_stc_stats_info_get_roaming_type_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_roaming_type_n",utc_stc_stats_info_get_roaming_type_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_protocol_type_p",utc_stc_stats_info_get_protocol_type_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_protocol_type_n",utc_stc_stats_info_get_protocol_type_n,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_process_state_p",utc_stc_stats_info_get_process_state_p,utc_stc_startup,utc_stc_cleanup},
	{"utc_stc_stats_info_get_process_state_n",utc_stc_stats_info_get_process_state_n,utc_stc_startup,utc_stc_cleanup},
	{NULL, NULL}
};

#endif // __TCT_STC_NATIVE_H__
