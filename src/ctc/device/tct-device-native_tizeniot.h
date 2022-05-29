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
#ifndef __TCT_DEVICE-NATIVE_H__
#define __TCT_DEVICE-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void CTs_device_startup(void);
extern void CTs_device_cleanup(void);

extern int CTc_device_check_led_feature_p(void);

testcase tc_array[] = {
	{"CTc_device_check_led_feature_p",CTc_device_check_led_feature_p,CTs_device_startup,CTs_device_cleanup},
	{NULL, NULL}
};

#endif // __TCT_DEVICE-NATIVE_H__
