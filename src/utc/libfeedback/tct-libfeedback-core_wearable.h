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
#ifndef __TCT_LIBFEEDBACK-NATIVE_H__
#define __TCT_LIBFEEDBACK-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_feedback_startup(void);
extern void utc_feedback_cleanup(void);

extern int utc_system_feedback_initialize_p(void);
extern int utc_system_feedback_deinitialize_p(void);
extern int utc_system_feedback_deinitialize_n(void);
extern int utc_system_feedback_play_p(void);
extern int utc_system_feedback_play_n(void);
extern int utc_system_feedback_play_type_p_1(void);
extern int utc_system_feedback_play_type_p_2(void);
extern int utc_system_feedback_play_type_n_1(void);
extern int utc_system_feedback_play_type_n_2(void);
extern int utc_system_feedback_stop_p(void);
extern int utc_system_feedback_is_supported_pattern_p(void);
extern int utc_system_feedback_is_supported_pattern_n_1(void);
extern int utc_system_feedback_is_supported_pattern_n_2(void);
extern int utc_system_feedback_is_supported_pattern_n_3(void);

testcase tc_array[] = {
	{"utc_system_feedback_initialize_p",utc_system_feedback_initialize_p,utc_feedback_startup,utc_feedback_cleanup},
	{"utc_system_feedback_deinitialize_p",utc_system_feedback_deinitialize_p,utc_feedback_startup,utc_feedback_cleanup},
	{"utc_system_feedback_deinitialize_n",utc_system_feedback_deinitialize_n,NULL,NULL},
	{"utc_system_feedback_play_p",utc_system_feedback_play_p,utc_feedback_startup,utc_feedback_cleanup},
	{"utc_system_feedback_play_n",utc_system_feedback_play_n,utc_feedback_startup,utc_feedback_cleanup},
	{"utc_system_feedback_play_type_p_1",utc_system_feedback_play_type_p_1,utc_feedback_startup,utc_feedback_cleanup},
	{"utc_system_feedback_play_type_p_2",utc_system_feedback_play_type_p_2,utc_feedback_startup,utc_feedback_cleanup},
	{"utc_system_feedback_play_type_n_1",utc_system_feedback_play_type_n_1,utc_feedback_startup,utc_feedback_cleanup},
	{"utc_system_feedback_play_type_n_2",utc_system_feedback_play_type_n_2,utc_feedback_startup,utc_feedback_cleanup},
	{"utc_system_feedback_stop_p",utc_system_feedback_stop_p,utc_feedback_startup,utc_feedback_cleanup},
	{"utc_system_feedback_is_supported_pattern_p",utc_system_feedback_is_supported_pattern_p,utc_feedback_startup,utc_feedback_cleanup},
	{"utc_system_feedback_is_supported_pattern_n_1",utc_system_feedback_is_supported_pattern_n_1,utc_feedback_startup,utc_feedback_cleanup},
	{"utc_system_feedback_is_supported_pattern_n_2",utc_system_feedback_is_supported_pattern_n_2,utc_feedback_startup,utc_feedback_cleanup},
	{"utc_system_feedback_is_supported_pattern_n_3",utc_system_feedback_is_supported_pattern_n_3,utc_feedback_startup,utc_feedback_cleanup},
	{NULL, NULL}
};

#endif // __TCT_LIBFEEDBACK-NATIVE_H__
