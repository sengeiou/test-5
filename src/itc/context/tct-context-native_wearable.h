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
#ifndef __TCT_CONTEXT-NATIVE_H__
#define __TCT_CONTEXT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_context_history_startup(void);
extern void ITs_context_history_cleanup(void);

extern int ITc_context_history_create_destroy_p(void);
extern int ITc_context_history_filter_create_destroy_p(void);
extern int ITc_context_history_filter_set_int_p(void);
extern int ITc_context_history_filter_set_string_p(void);
extern int ITc_context_history_get_list_destroy_p(void);
extern int ITc_context_history_list_get_count_p(void);
extern int ITc_context_history_list_get_current_p(void);
extern int ITc_context_history_list_move_first_p(void);
extern int ITc_context_history_list_move_next_p(void);
extern int ITc_context_history_record_get_int_string_p(void);

testcase tc_array[] = {
	{"ITc_context_history_create_destroy_p",ITc_context_history_create_destroy_p,ITs_context_history_startup,ITs_context_history_cleanup},
	{"ITc_context_history_filter_create_destroy_p",ITc_context_history_filter_create_destroy_p,ITs_context_history_startup,ITs_context_history_cleanup},
	{"ITc_context_history_filter_set_int_p",ITc_context_history_filter_set_int_p,ITs_context_history_startup,ITs_context_history_cleanup},
	{"ITc_context_history_filter_set_string_p",ITc_context_history_filter_set_string_p,ITs_context_history_startup,ITs_context_history_cleanup},
	{"ITc_context_history_get_list_destroy_p",ITc_context_history_get_list_destroy_p,ITs_context_history_startup,ITs_context_history_cleanup},
	{"ITc_context_history_list_get_count_p",ITc_context_history_list_get_count_p,ITs_context_history_startup,ITs_context_history_cleanup},
	{"ITc_context_history_list_get_current_p",ITc_context_history_list_get_current_p,ITs_context_history_startup,ITs_context_history_cleanup},
	{"ITc_context_history_list_move_first_p",ITc_context_history_list_move_first_p,ITs_context_history_startup,ITs_context_history_cleanup},
	{"ITc_context_history_list_move_next_p",ITc_context_history_list_move_next_p,ITs_context_history_startup,ITs_context_history_cleanup},
	{"ITc_context_history_record_get_int_string_p",ITc_context_history_record_get_int_string_p,ITs_context_history_startup,ITs_context_history_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CONTEXT-NATIVE_H__
