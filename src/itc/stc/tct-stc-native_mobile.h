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

extern void ITs_stc_startup(void);
extern void ITs_stc_cleanup(void);

extern int ITs_stc_initialize_deinitialize_p(void);
extern int ITs_stc_stats_rule_create_destroy_p(void);
extern int ITs_stc_stats_rule_set_get_app_id_p(void);
extern int ITs_stc_stats_rule_set_get_time_interval_p(void);
extern int ITs_stc_stats_rule_set_get_iface_type_p(void);
extern int ITs_stc_stats_rule_set_get_time_period_p(void);
extern int ITs_stc_foreach_all_stats_p(void);
extern int ITs_stc_stats_info_get_app_id_p(void);
extern int ITs_stc_stats_info_get_iface_name_p(void);
extern int ITs_stc_stats_info_get_time_interval_p(void);
extern int ITs_stc_stats_info_get_iface_type_p(void);
extern int ITs_stc_stats_info_get_counter_p(void);
extern int ITs_stc_stats_info_get_roaming_type_p(void);
extern int ITs_stc_stats_info_get_protocol_type_p(void);
extern int ITs_stc_stats_info_get_process_state_p(void);
extern int ITs_stc_stats_info_clone_destroy_p(void);
extern int ITs_stc_get_all_stats_p(void);

testcase tc_array[] = {
	{"ITs_stc_initialize_deinitialize_p",ITs_stc_initialize_deinitialize_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_rule_create_destroy_p",ITs_stc_stats_rule_create_destroy_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_rule_set_get_app_id_p",ITs_stc_stats_rule_set_get_app_id_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_rule_set_get_time_interval_p",ITs_stc_stats_rule_set_get_time_interval_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_rule_set_get_iface_type_p",ITs_stc_stats_rule_set_get_iface_type_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_rule_set_get_time_period_p",ITs_stc_stats_rule_set_get_time_period_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_foreach_all_stats_p",ITs_stc_foreach_all_stats_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_info_get_app_id_p",ITs_stc_stats_info_get_app_id_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_info_get_iface_name_p",ITs_stc_stats_info_get_iface_name_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_info_get_time_interval_p",ITs_stc_stats_info_get_time_interval_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_info_get_iface_type_p",ITs_stc_stats_info_get_iface_type_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_info_get_counter_p",ITs_stc_stats_info_get_counter_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_info_get_roaming_type_p",ITs_stc_stats_info_get_roaming_type_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_info_get_protocol_type_p",ITs_stc_stats_info_get_protocol_type_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_info_get_process_state_p",ITs_stc_stats_info_get_process_state_p,ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_stats_info_clone_destroy_p", ITs_stc_stats_info_clone_destroy_p, ITs_stc_startup,ITs_stc_cleanup},
	{"ITs_stc_get_all_stats_p", ITs_stc_get_all_stats_p, ITs_stc_startup,ITs_stc_cleanup},
	{NULL, NULL}
};

#endif // __TCT_STC_NATIVE_H__
