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
#ifndef __TCT_EFL-UTIL-NATIVE_H__
#define __TCT_EFL-UTIL-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_efl_util_startup(void);
extern void ITs_efl_util_cleanup(void);

extern int ITc_efl_util_efl_util_set_get_notification_window_level_p(void);
extern int ITc_efl_util_set_window_opaque_state_p(void);
extern int ITc_efl_util_set_get_window_screen_mode_p(void);
extern int ITc_efl_util_set_get_window_brightness_p(void);

testcase tc_array[] = {
	{"ITc_efl_util_efl_util_set_get_notification_window_level_p",ITc_efl_util_efl_util_set_get_notification_window_level_p,ITs_efl_util_startup,ITs_efl_util_cleanup},
	{"ITc_efl_util_set_window_opaque_state_p",ITc_efl_util_set_window_opaque_state_p,ITs_efl_util_startup,ITs_efl_util_cleanup},
	{"ITc_efl_util_set_get_window_screen_mode_p",ITc_efl_util_set_get_window_screen_mode_p,ITs_efl_util_startup,ITs_efl_util_cleanup},
	{"ITc_efl_util_set_get_window_brightness_p",ITc_efl_util_set_get_window_brightness_p,ITs_efl_util_startup,ITs_efl_util_cleanup},
	{NULL, NULL}
};

#endif // __TCT_EFL-UTIL-NATIVE_H__
