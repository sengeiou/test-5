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
#ifndef __TCT_CAPI-UI-INPUTMETHOD-MANAGER-NATIVE_H__
#define __TCT_CAPI-UI-INPUTMETHOD-MANAGER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_inputmethod_manager_startup(void);
extern void ITs_inputmethod_manager_cleanup(void);

extern int ITc_ime_manager_get_active_ime_p(void);
extern int ITc_ime_manager_is_ime_enabled_p(void);
extern int ITc_ime_manager_get_enabled_ime_count_p(void);
extern int ITc_ime_manager_prelaunch_ime(void);

testcase tc_array[] = {
	{"ITc_ime_manager_get_active_ime_p",ITc_ime_manager_get_active_ime_p,ITs_inputmethod_manager_startup,ITs_inputmethod_manager_cleanup},
	{"ITc_ime_manager_is_ime_enabled_p",ITc_ime_manager_is_ime_enabled_p,ITs_inputmethod_manager_startup,ITs_inputmethod_manager_cleanup},
	{"ITc_ime_manager_get_enabled_ime_count_p",ITc_ime_manager_get_enabled_ime_count_p,ITs_inputmethod_manager_startup,ITs_inputmethod_manager_cleanup},
	{"ITc_ime_manager_prelaunch_ime",ITc_ime_manager_prelaunch_ime,ITs_inputmethod_manager_startup,ITs_inputmethod_manager_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CAPI-UI-INPUTMETHOD-MANAGER-NATIVE_H__
