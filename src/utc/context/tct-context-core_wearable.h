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

extern void utc_context_history_startup(void);
extern void utc_context_history_cleanup(void);

extern int utc_context_history_create_p(void);
extern int utc_context_history_create_n(void);
extern int utc_context_history_destroy_p(void);
extern int utc_context_history_destroy_n(void);
extern int utc_context_history_filter_create_p(void);
extern int utc_context_history_filter_create_n(void);
extern int utc_context_history_filter_destroy_p(void);
extern int utc_context_history_filter_destroy_n(void);
extern int utc_context_history_filter_set_int_p(void);
extern int utc_context_history_filter_set_int_n(void);
extern int utc_context_history_get_list_p(void);
extern int utc_context_history_get_list_n(void);
extern int utc_context_history_list_get_count_p(void);
extern int utc_context_history_list_get_count_n(void);
extern int utc_context_history_list_get_current_p(void);
extern int utc_context_history_list_get_current_n(void);
extern int utc_context_history_list_move_first_p(void);
extern int utc_context_history_list_move_first_n(void);
extern int utc_context_history_list_move_next_p(void);
extern int utc_context_history_list_move_next_n(void);
extern int utc_context_history_list_destroy_p(void);
extern int utc_context_history_list_destroy_n(void);
extern int utc_context_history_record_get_int_p(void);
extern int utc_context_history_record_get_int_n(void);
extern int utc_context_history_record_get_string_p(void);
extern int utc_context_history_record_get_string_n(void);
extern int utc_context_history_record_get_double_p(void);
extern int utc_context_history_record_get_double_n(void);
extern int utc_context_history_record_destroy_p(void);
extern int utc_context_history_record_destroy_n(void);

testcase tc_array[] = {
	{"utc_context_history_create_p",utc_context_history_create_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_create_n",utc_context_history_create_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_destroy_p",utc_context_history_destroy_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_destroy_n",utc_context_history_destroy_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_filter_create_p",utc_context_history_filter_create_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_filter_create_n",utc_context_history_filter_create_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_filter_destroy_p",utc_context_history_filter_destroy_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_filter_destroy_n",utc_context_history_filter_destroy_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_filter_set_int_p",utc_context_history_filter_set_int_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_filter_set_int_n",utc_context_history_filter_set_int_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_get_list_p",utc_context_history_get_list_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_get_list_n",utc_context_history_get_list_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_list_get_count_p",utc_context_history_list_get_count_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_list_get_count_n",utc_context_history_list_get_count_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_list_get_current_p",utc_context_history_list_get_current_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_list_get_current_n",utc_context_history_list_get_current_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_list_move_first_p",utc_context_history_list_move_first_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_list_move_first_n",utc_context_history_list_move_first_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_list_move_next_p",utc_context_history_list_move_next_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_list_move_next_n",utc_context_history_list_move_next_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_list_destroy_p",utc_context_history_list_destroy_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_list_destroy_n",utc_context_history_list_destroy_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_record_get_int_p",utc_context_history_record_get_int_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_record_get_int_n",utc_context_history_record_get_int_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_record_get_string_p",utc_context_history_record_get_string_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_record_get_string_n",utc_context_history_record_get_string_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_record_get_double_p",utc_context_history_record_get_double_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_record_get_double_n",utc_context_history_record_get_double_n,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_record_destroy_p",utc_context_history_record_destroy_p,utc_context_history_startup,utc_context_history_cleanup},
	{"utc_context_history_record_destroy_n",utc_context_history_record_destroy_n,utc_context_history_startup,utc_context_history_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CONTEXT-NATIVE_H__
