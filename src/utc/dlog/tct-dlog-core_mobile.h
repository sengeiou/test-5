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
#ifndef __TCT_DLOG-NATIVE_H__
#define __TCT_DLOG-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"


extern int utc_SystemFW_dlog_print_p(void);
extern int utc_SystemFW_dlog_print_n(void);
extern int utc_SystemFW_dlog_vprint_p(void);
extern int utc_SystemFW_dlog_vprint_n(void);

testcase tc_array[] = {
	{"utc_SystemFW_dlog_print_p",utc_SystemFW_dlog_print_p,NULL,NULL},
	{"utc_SystemFW_dlog_print_n",utc_SystemFW_dlog_print_n,NULL,NULL},
	{"utc_SystemFW_dlog_vprint_p",utc_SystemFW_dlog_vprint_p,NULL,NULL},
	{"utc_SystemFW_dlog_vprint_n",utc_SystemFW_dlog_vprint_n,NULL,NULL},
	{NULL, NULL}
};

#endif // __TCT_DLOG-NATIVE_H__
