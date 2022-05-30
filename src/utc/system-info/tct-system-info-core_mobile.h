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


extern int utc_system_info_get_platform_bool_p(void);
extern int utc_system_info_get_platform_bool_n(void);
extern int utc_system_info_get_platform_int_p(void);
extern int utc_system_info_get_platform_int_n(void);
extern int utc_system_info_get_platform_double_p(void);
extern int utc_system_info_get_platform_double_n(void);
extern int utc_system_info_get_platform_string_p(void);
extern int utc_system_info_get_platform_string_n(void);
extern int utc_system_info_get_custom_bool_n(void);
extern int utc_system_info_get_custom_int_n(void);
extern int utc_system_info_get_custom_double_n(void);
extern int utc_system_info_get_custom_string_n(void);

testcase tc_array[] = {
	{"utc_system_info_get_platform_bool_p",utc_system_info_get_platform_bool_p,NULL,NULL},
	{"utc_system_info_get_platform_bool_n",utc_system_info_get_platform_bool_n,NULL,NULL},
	{"utc_system_info_get_platform_int_p",utc_system_info_get_platform_int_p,NULL,NULL},
	{"utc_system_info_get_platform_int_n",utc_system_info_get_platform_int_n,NULL,NULL},
	{"utc_system_info_get_platform_double_p",utc_system_info_get_platform_double_p,NULL,NULL},
	{"utc_system_info_get_platform_double_n",utc_system_info_get_platform_double_n,NULL,NULL},
	{"utc_system_info_get_platform_string_p",utc_system_info_get_platform_string_p,NULL,NULL},
	{"utc_system_info_get_platform_string_n",utc_system_info_get_platform_string_n,NULL,NULL},
	{"utc_system_info_get_custom_bool_n",utc_system_info_get_custom_bool_n,NULL,NULL},
	{"utc_system_info_get_custom_int_n",utc_system_info_get_custom_int_n,NULL,NULL},
	{"utc_system_info_get_custom_double_n",utc_system_info_get_custom_double_n,NULL,NULL},
	{"utc_system_info_get_custom_string_n",utc_system_info_get_custom_string_n,NULL,NULL},
	{NULL, NULL}
};

#endif // __TCT_SYSTEM-INFO-NATIVE_H__
