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

extern void ITs_feedback_startup(void);
extern void ITs_feedback_cleanup(void);

extern int ITc_feedback_initialize_deinitialize_p(void);
extern int ITc_feedback_play_stop_p(void);
extern int ITc_feedback_play_type_p(void);
extern int ITc_feedback_is_supported_pattern_p(void);

testcase tc_array[] = {
	{"ITc_feedback_initialize_deinitialize_p",ITc_feedback_initialize_deinitialize_p,ITs_feedback_startup,ITs_feedback_cleanup},
	{"ITc_feedback_play_stop_p",ITc_feedback_play_stop_p,ITs_feedback_startup,ITs_feedback_cleanup},
	{"ITc_feedback_play_type_p",ITc_feedback_play_type_p,ITs_feedback_startup,ITs_feedback_cleanup},
	{"ITc_feedback_is_supported_pattern_p",ITc_feedback_is_supported_pattern_p,ITs_feedback_startup,ITs_feedback_cleanup},
	{NULL, NULL}
};

#endif // __TCT_LIBFEEDBACK-NATIVE_H__
