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

extern void utc_eom_startup(void);
extern void utc_eom_cleanup(void);
extern void utc_eom_getinfo_startup(void);
extern void utc_eom_getinfo_cleanup(void);
extern void utc_eom_setinfo_startup(void);
extern void utc_eom_setinfo_cleanup(void);
extern void utc_eom_cb_startup(void);
extern void utc_eom_cb_cleanup(void);

extern int utc_eom_init_p(void);
extern int utc_eom_deinit_p(void);
extern int utc_eom_get_eom_output_ids_p(void);
extern int utc_eom_get_eom_output_ids_n(void);
extern int utc_eom_get_output_type_p(void);
extern int utc_eom_get_output_type_n1(void);
extern int utc_eom_get_output_type_n2(void);
extern int utc_eom_get_output_mode_p(void);
extern int utc_eom_get_output_mode_n1(void);
extern int utc_eom_get_output_mode_n2(void);
extern int utc_eom_get_output_attribute_p(void);
extern int utc_eom_get_output_attribute_n1(void);
extern int utc_eom_get_output_attribute_n2(void);
extern int utc_eom_get_output_attribute_state_p(void);
extern int utc_eom_get_output_attribute_state_n1(void);
extern int utc_eom_get_output_attribute_state_n2(void);
extern int utc_eom_get_output_resolution_p(void);
extern int utc_eom_get_output_resolution_n1(void);
extern int utc_eom_get_output_resolution_n2(void);
extern int utc_eom_get_output_physical_size_p(void);
extern int utc_eom_get_output_physical_size_n1(void);
extern int utc_eom_get_output_physical_size_n2(void);
extern int utc_eom_set_output_attribute_p(void);
extern int utc_eom_set_output_attribute_n(void);
extern int utc_eom_set_output_window_p(void);
extern int utc_eom_set_output_window_n(void);
extern int utc_eom_set_output_added_cb_p(void);
extern int utc_eom_set_output_added_cb_n(void);
extern int utc_eom_unset_output_added_cb_p(void);
extern int utc_eom_unset_output_added_cb_n(void);
extern int utc_eom_set_output_removeed_cb_p(void);
extern int utc_eom_set_output_removed_cb_n(void);
extern int utc_eom_unset_output_removed_cb_p(void);
extern int utc_eom_unset_output_removed_cb_n(void);
extern int utc_eom_set_mode_changed_cb_p(void);
extern int utc_eom_set_mode_changed_cb_n(void);
extern int utc_eom_unset_mode_changed_cb_p(void);
extern int utc_eom_unset_mode_changed_cb_n(void);
extern int utc_eom_set_attribute_changed_cb_p(void);
extern int utc_eom_set_attribute_changed_cb_n(void);
extern int utc_eom_unset_attribute_changed_cb_p(void);
extern int utc_eom_unset_attribute_chang_cb_n(void);

testcase tc_array[] = {
	{"utc_eom_init_p",utc_eom_init_p,utc_eom_startup,utc_eom_cleanup},
	{"utc_eom_deinit_p",utc_eom_deinit_p,utc_eom_startup,utc_eom_cleanup},
	{"utc_eom_get_eom_output_ids_p",utc_eom_get_eom_output_ids_p,utc_eom_startup,utc_eom_cleanup},
	{"utc_eom_get_eom_output_ids_n",utc_eom_get_eom_output_ids_n,utc_eom_startup,utc_eom_cleanup},
	{"utc_eom_get_output_type_p",utc_eom_get_output_type_p,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_type_n1",utc_eom_get_output_type_n1,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_type_n2",utc_eom_get_output_type_n2,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_mode_p",utc_eom_get_output_mode_p,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_mode_n1",utc_eom_get_output_mode_n1,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_mode_n2",utc_eom_get_output_mode_n2,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_attribute_p",utc_eom_get_output_attribute_p,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_attribute_n1",utc_eom_get_output_attribute_n1,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_attribute_n2",utc_eom_get_output_attribute_n2,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_attribute_state_p",utc_eom_get_output_attribute_state_p,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_attribute_state_n1",utc_eom_get_output_attribute_state_n1,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_attribute_state_n2",utc_eom_get_output_attribute_state_n2,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_resolution_p",utc_eom_get_output_resolution_p,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_resolution_n1",utc_eom_get_output_resolution_n1,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_resolution_n2",utc_eom_get_output_resolution_n2,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_physical_size_p",utc_eom_get_output_physical_size_p,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_physical_size_n1",utc_eom_get_output_physical_size_n1,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_get_output_physical_size_n2",utc_eom_get_output_physical_size_n2,utc_eom_getinfo_startup,utc_eom_getinfo_cleanup},
	{"utc_eom_set_output_attribute_p",utc_eom_set_output_attribute_p,utc_eom_setinfo_startup,utc_eom_setinfo_cleanup},
	{"utc_eom_set_output_attribute_n",utc_eom_set_output_attribute_n,utc_eom_setinfo_startup,utc_eom_setinfo_cleanup},
	{"utc_eom_set_output_window_p",utc_eom_set_output_window_p,utc_eom_setinfo_startup,utc_eom_setinfo_cleanup},
	{"utc_eom_set_output_window_n",utc_eom_set_output_window_n,utc_eom_setinfo_startup,utc_eom_setinfo_cleanup},
	{"utc_eom_set_output_added_cb_p",utc_eom_set_output_added_cb_p,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_set_output_added_cb_n",utc_eom_set_output_added_cb_n,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_unset_output_added_cb_p",utc_eom_unset_output_added_cb_p,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_unset_output_added_cb_n",utc_eom_unset_output_added_cb_n,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_set_output_removeed_cb_p",utc_eom_set_output_removeed_cb_p,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_set_output_removed_cb_n",utc_eom_set_output_removed_cb_n,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_unset_output_removed_cb_p",utc_eom_unset_output_removed_cb_p,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_unset_output_removed_cb_n",utc_eom_unset_output_removed_cb_n,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_set_mode_changed_cb_p",utc_eom_set_mode_changed_cb_p,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_set_mode_changed_cb_n",utc_eom_set_mode_changed_cb_n,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_unset_mode_changed_cb_p",utc_eom_unset_mode_changed_cb_p,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_unset_mode_changed_cb_n",utc_eom_unset_mode_changed_cb_n,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_set_attribute_changed_cb_p",utc_eom_set_attribute_changed_cb_p,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_set_attribute_changed_cb_n",utc_eom_set_attribute_changed_cb_n,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_unset_attribute_changed_cb_p",utc_eom_unset_attribute_changed_cb_p,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{"utc_eom_unset_attribute_chang_cb_n",utc_eom_unset_attribute_chang_cb_n,utc_eom_cb_startup,utc_eom_cb_cleanup},
	{NULL, NULL}
};

#endif // __TCT_EOM-NATIVE_H__
