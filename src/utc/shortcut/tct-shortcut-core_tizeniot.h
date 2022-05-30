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
#ifndef __TCT_SHORTCUT-NATIVE_H__
#define __TCT_SHORTCUT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_shortcut_startup(void);

extern int utc_shortcut_add_to_home_n(void);
extern int utc_shortcut_add_to_home_p(void);
extern int utc_shortcut_add_to_home_widget_n(void);
extern int utc_shortcut_add_to_home_widget_p(void);
extern int utc_shortcut_remove_from_home_n(void);
extern int utc_shortcut_remove_from_home_p(void);
extern int utc_shortcut_set_request_cb_n(void);
extern int utc_shortcut_set_request_cb_p(void);
extern int utc_shortcut_set_remove_cb_n(void);
extern int utc_shortcut_set_remove_cb_p(void);
extern int utc_shortcut_unset_request_cb_n(void);
extern int utc_shortcut_unset_request_cb_p(void);
extern int utc_shortcut_unset_remove_cb_n(void);
extern int utc_shortcut_unset_remove_cb_p(void);
extern int utc_shortcut_get_list_n(void);
extern int utc_shortcut_get_list_p(void);

testcase tc_array[] = {
	{"utc_shortcut_add_to_home_n",utc_shortcut_add_to_home_n,utc_shortcut_startup,NULL},
	{"utc_shortcut_add_to_home_p",utc_shortcut_add_to_home_p,utc_shortcut_startup,NULL},
	{"utc_shortcut_add_to_home_widget_n",utc_shortcut_add_to_home_widget_n,utc_shortcut_startup,NULL},
	{"utc_shortcut_add_to_home_widget_p",utc_shortcut_add_to_home_widget_p,utc_shortcut_startup,NULL},
	{"utc_shortcut_remove_from_home_n",utc_shortcut_remove_from_home_n,utc_shortcut_startup,NULL},
	{"utc_shortcut_remove_from_home_p",utc_shortcut_remove_from_home_p,utc_shortcut_startup,NULL},
	{"utc_shortcut_set_request_cb_n",utc_shortcut_set_request_cb_n,utc_shortcut_startup,NULL},
	{"utc_shortcut_set_request_cb_p",utc_shortcut_set_request_cb_p,utc_shortcut_startup,NULL},
	{"utc_shortcut_set_remove_cb_n",utc_shortcut_set_remove_cb_n,utc_shortcut_startup,NULL},
	{"utc_shortcut_set_remove_cb_p",utc_shortcut_set_remove_cb_p,utc_shortcut_startup,NULL},
	{"utc_shortcut_unset_request_cb_n",utc_shortcut_unset_request_cb_n,utc_shortcut_startup,NULL},
	{"utc_shortcut_unset_request_cb_p",utc_shortcut_unset_request_cb_p,utc_shortcut_startup,NULL},
	{"utc_shortcut_unset_remove_cb_n",utc_shortcut_unset_remove_cb_n,utc_shortcut_startup,NULL},
	{"utc_shortcut_unset_remove_cb_p",utc_shortcut_unset_remove_cb_p,utc_shortcut_startup,NULL},
	{"utc_shortcut_get_list_n",utc_shortcut_get_list_n,utc_shortcut_startup,NULL},
	{"utc_shortcut_get_list_p",utc_shortcut_get_list_p,utc_shortcut_startup,NULL},
	{NULL, NULL}
};

#endif // __TCT_SHORTCUT-NATIVE_H__
