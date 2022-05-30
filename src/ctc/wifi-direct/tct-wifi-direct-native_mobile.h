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
#ifndef __TCT_WIFI-DIRECT-NATIVE_H__
#define __TCT_WIFI-DIRECT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void CTs_wifi_direct_startup(void);
extern void CTs_wifi_direct_cleanup(void);

extern int CTc_wifi_direct_check_wifi_support(void);

testcase tc_array[] = {
	{"CTc_wifi_direct_check_wifi_support",CTc_wifi_direct_check_wifi_support,CTs_wifi_direct_startup,CTs_wifi_direct_cleanup},
	{NULL, NULL}
};

#endif // __TCT_WIFI-DIRECT-NATIVE_H__
