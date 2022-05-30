//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#ifndef __TCT_%{HEADER_TOP}_NATIVE_H__
#define __TCT_%{HEADER_TOP}_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_%{MODULE_NAME_U}_startup(void);
extern void utc_%{MODULE_NAME_U}_cleanup(void);

extern int utc_first_tc_p(void);
extern int utc_first_tc_n(void);

testcase tc_array[] = {
    {"utc_first_tc_p", utc_first_tc_p, utc_%{MODULE_NAME_U}_startup, utc_%{MODULE_NAME_U}_cleanup},
    {"utc_first_tc_n", utc_first_tc_n, utc_%{MODULE_NAME_U}_startup, utc_%{MODULE_NAME_U}_cleanup},
    {NULL, NULL}
};

#endif // __TCT_%{HEADER_TOP}_NATIVE_H__
