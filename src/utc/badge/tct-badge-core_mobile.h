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
#ifndef __TCT_BADGE-NATIVE_H__
#define __TCT_BADGE-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_badge_setting_startup(void);
extern void utc_badge_setting_cleanup(void);

extern int utc_badge_remove_1_n(void);
extern int utc_badge_remove_2_n(void);
extern int utc_badge_remove_p(void);
extern int utc_badge_set_count_1_n(void);
extern int utc_badge_set_count_2_n(void);
extern int utc_badge_set_count_p(void);
extern int utc_badge_set_count_2_p(void);
extern int utc_badge_get_count_n(void);
extern int utc_badge_get_count_n2(void);
extern int utc_badge_get_count_p(void);
extern int utc_badge_set_display_1_n(void);
extern int utc_badge_set_display_2_n(void);
extern int utc_badge_set_display_p(void);
extern int utc_badge_get_display_n(void);
extern int utc_badge_get_display_n2(void);
extern int utc_badge_get_display_p(void);
extern int utc_badge_new_n(void);
extern int utc_badge_new_p(void);
extern int utc_badge_register_changed_cb_n(void);
extern int utc_badge_register_changed_cb_p(void);
extern int utc_badge_unregister_changed_cb_n(void);
extern int utc_badge_unregister_changed_cb_p(void);
extern int utc_badge_foreach_n(void);
extern int utc_badge_foreach_p(void);
extern int utc_badge_add_n(void);
extern int utc_badge_add_p(void);

testcase tc_array[] = {
	{"utc_badge_remove_1_n",utc_badge_remove_1_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_remove_2_n",utc_badge_remove_2_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_remove_p",utc_badge_remove_p,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_set_count_1_n",utc_badge_set_count_1_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_set_count_2_n",utc_badge_set_count_2_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_set_count_p",utc_badge_set_count_p,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_set_count_2_p",utc_badge_set_count_2_p,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_get_count_n",utc_badge_get_count_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_get_count_n2",utc_badge_get_count_n2,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_get_count_p",utc_badge_get_count_p,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_set_display_1_n",utc_badge_set_display_1_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_set_display_2_n",utc_badge_set_display_2_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_set_display_p",utc_badge_set_display_p,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_get_display_n",utc_badge_get_display_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_get_display_n2",utc_badge_get_display_n2,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_get_display_p",utc_badge_get_display_p,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_new_n",utc_badge_new_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_new_p",utc_badge_new_p,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_register_changed_cb_n",utc_badge_register_changed_cb_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_register_changed_cb_p",utc_badge_register_changed_cb_p,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_unregister_changed_cb_n",utc_badge_unregister_changed_cb_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_unregister_changed_cb_p",utc_badge_unregister_changed_cb_p,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_foreach_n",utc_badge_foreach_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_foreach_p",utc_badge_foreach_p,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_add_n",utc_badge_add_n,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{"utc_badge_add_p",utc_badge_add_p,utc_badge_setting_startup,utc_badge_setting_cleanup},
	{NULL, NULL}
};

#endif // __TCT_BADGE-NATIVE_H__
