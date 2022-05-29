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
#ifndef __TCT_EOM-NATIVE_H__
#define __TCT_EOM-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_eom_startup(void);
extern void ITs_eom_cleanup(void);
extern void ITs_eom_init_deinit_startup(void);
extern void ITs_eom_init_deinit_cleanup(void);

extern int ITc_eom_get_output_id_p(void);
extern int ITc_eom_get_output_type_p(void);
extern int ITc_eom_get_output_mode_p(void);
extern int ITc_eom_get_set_output_attribute_p(void);
extern int ITc_eom_get_output_attribute_state_p(void);
extern int ITc_eom_get_output_resolution_p(void);
extern int ITc_eom_get_output_physical_size_p(void);
extern int ITc_eom_set_output_window_p(void);
extern int ITc_eom_set_unset_attribute_changed_cb_p(void);
extern int ITc_eom_set_unset_mode_changed_cb_p(void);
extern int ITc_eom_set_unset_output_added_cb_p(void);
extern int ITc_eom_set_unset_output_removed_cb_p(void);
extern int ITc_eom_output_init_deinit_p(void);

testcase tc_array[] = {
	{"ITc_eom_get_output_id_p",ITc_eom_get_output_id_p,ITs_eom_startup,ITs_eom_cleanup},
	{"ITc_eom_get_output_type_p",ITc_eom_get_output_type_p,ITs_eom_startup,ITs_eom_cleanup},
	{"ITc_eom_get_output_mode_p",ITc_eom_get_output_mode_p,ITs_eom_startup,ITs_eom_cleanup},
	{"ITc_eom_get_set_output_attribute_p",ITc_eom_get_set_output_attribute_p,ITs_eom_startup,ITs_eom_cleanup},
	{"ITc_eom_get_output_attribute_state_p",ITc_eom_get_output_attribute_state_p,ITs_eom_startup,ITs_eom_cleanup},
	{"ITc_eom_get_output_resolution_p",ITc_eom_get_output_resolution_p,ITs_eom_startup,ITs_eom_cleanup},
	{"ITc_eom_get_output_physical_size_p",ITc_eom_get_output_physical_size_p,ITs_eom_startup,ITs_eom_cleanup},
	{"ITc_eom_set_output_window_p",ITc_eom_set_output_window_p,ITs_eom_startup,ITs_eom_cleanup},
	{"ITc_eom_set_unset_attribute_changed_cb_p",ITc_eom_set_unset_attribute_changed_cb_p,ITs_eom_startup,ITs_eom_cleanup},
	{"ITc_eom_set_unset_mode_changed_cb_p",ITc_eom_set_unset_mode_changed_cb_p,ITs_eom_startup,ITs_eom_cleanup},
	{"ITc_eom_set_unset_output_added_cb_p",ITc_eom_set_unset_output_added_cb_p,ITs_eom_startup,ITs_eom_cleanup},
	{"ITc_eom_set_unset_output_removed_cb_p",ITc_eom_set_unset_output_removed_cb_p,ITs_eom_startup,ITs_eom_cleanup},
	{"ITc_eom_output_init_deinit_p",ITc_eom_output_init_deinit_p,ITs_eom_init_deinit_startup,ITs_eom_init_deinit_cleanup},
	{NULL, NULL}
};

#endif // __TCT_EOM-NATIVE_H__
