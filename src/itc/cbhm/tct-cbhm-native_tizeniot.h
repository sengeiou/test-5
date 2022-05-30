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
#ifndef __TCT_CBHM-NATIVE_H__
#define __TCT_CBHM-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_cbhm_startup(void);
extern void ITs_cbhm_cleanup(void);

extern int ITc_cbhm_open_close_service_p(void);
extern int ITc_cbhm_selection_type_set_get_p(void);
extern int ITc_cbhm_show_hide_p(void);
extern int ITc_cbhm_selection_set_get_p(void);
extern int ITc_cbhm_item_count_get_p(void);
extern int ITc_cbhm_item_selected_callback_add_p(void);

testcase tc_array[] = {
	{"ITc_cbhm_open_close_service_p",ITc_cbhm_open_close_service_p,ITs_cbhm_startup,ITs_cbhm_cleanup},
	{"ITc_cbhm_selection_type_set_get_p",ITc_cbhm_selection_type_set_get_p,ITs_cbhm_startup,ITs_cbhm_cleanup},
	{"ITc_cbhm_show_hide_p",ITc_cbhm_show_hide_p,ITs_cbhm_startup,ITs_cbhm_cleanup},
	{"ITc_cbhm_selection_set_get_p",ITc_cbhm_selection_set_get_p,ITs_cbhm_startup,ITs_cbhm_cleanup},
	{"ITc_cbhm_item_count_get_p",ITc_cbhm_item_count_get_p,ITs_cbhm_startup,ITs_cbhm_cleanup},
	{"ITc_cbhm_item_selected_callback_add_p",ITc_cbhm_item_selected_callback_add_p,ITs_cbhm_startup,ITs_cbhm_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CBHM-NATIVE_H__
