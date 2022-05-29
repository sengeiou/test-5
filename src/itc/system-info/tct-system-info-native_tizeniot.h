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
#ifndef __TCT_SYSTEM-INFO-NATIVE_H__
#define __TCT_SYSTEM-INFO-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_system_info_startup(void);
extern void ITs_system_info_cleanup(void);

extern int ITc_system_info_get_platform_bool_p(void);
extern int ITc_system_info_get_platform_double_p(void);
extern int ITc_system_info_get_platform_int_p(void);
extern int ITc_system_info_get_platform_string_p(void);

testcase tc_array[] = {
	{"ITc_system_info_get_platform_bool_p",ITc_system_info_get_platform_bool_p,ITs_system_info_startup,ITs_system_info_cleanup},
	{"ITc_system_info_get_platform_double_p",ITc_system_info_get_platform_double_p,ITs_system_info_startup,ITs_system_info_cleanup},
	{"ITc_system_info_get_platform_int_p",ITc_system_info_get_platform_int_p,ITs_system_info_startup,ITs_system_info_cleanup},
	{"ITc_system_info_get_platform_string_p",ITc_system_info_get_platform_string_p,ITs_system_info_startup,ITs_system_info_cleanup},
	{NULL, NULL}
};

#endif // __TCT_SYSTEM-INFO-NATIVE_H__
