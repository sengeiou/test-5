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
#ifndef __TCT_OPENAL-NATIVE_H__
#define __TCT_OPENAL-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"


extern int utc_alcOpenDeviceNew_p(void);
extern int utc_alcOpenDeviceNew_n(void);

testcase tc_array[] = {
	{"utc_alcOpenDeviceNew_p",utc_alcOpenDeviceNew_p,NULL,NULL},
	{"utc_alcOpenDeviceNew_n",utc_alcOpenDeviceNew_n,NULL,NULL},
	{NULL, NULL}
};

#endif // __TCT_OPENAL-NATIVE_H__
