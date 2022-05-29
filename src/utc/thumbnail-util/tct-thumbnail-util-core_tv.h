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
#ifndef __TCT_THUMBNAIL-UTIL-NATIVE_H__
#define __TCT_THUMBNAIL-UTIL-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_thumbnail_util_startup(void);
extern void utc_thumbnail_util_cleanup(void);

extern int utc_thumbnail_util_create_n(void);
extern int utc_thumbnail_util_create_p(void);
extern int utc_thumbnail_util_extract_n1(void);
extern int utc_thumbnail_util_extract_n2(void);
extern int utc_thumbnail_util_extract_p(void);
extern int utc_thumbnail_util_set_path_n(void);
extern int utc_thumbnail_util_set_path_p(void);
extern int utc_thumbnail_util_set_size_n(void);
extern int utc_thumbnail_util_set_size_p(void);
extern int utc_thumbnail_util_cancel_n(void);
extern int utc_thumbnail_util_cancel_p(void);
extern int utc_thumbnail_util_destroy_n(void);
extern int utc_thumbnail_util_destroy_p(void);
extern int utc_thumbnail_util_extract_to_file_n1(void);
extern int utc_thumbnail_util_extract_to_file_n2(void);
extern int utc_thumbnail_util_extract_to_file_n3(void);
extern int utc_thumbnail_util_extract_to_file_p1(void);
extern int utc_thumbnail_util_extract_to_file_p2(void);
extern int utc_thumbnail_util_extract_to_buffer_n1(void);
extern int utc_thumbnail_util_extract_to_buffer_n2(void);
extern int utc_thumbnail_util_extract_to_buffer_p1(void);
extern int utc_thumbnail_util_extract_to_buffer_p2(void);

testcase tc_array[] = {
	{"utc_thumbnail_util_create_n",utc_thumbnail_util_create_n,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_create_p",utc_thumbnail_util_create_p,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_extract_n1",utc_thumbnail_util_extract_n1,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_extract_n2",utc_thumbnail_util_extract_n2,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_extract_p",utc_thumbnail_util_extract_p,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_set_path_n",utc_thumbnail_util_set_path_n,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_set_path_p",utc_thumbnail_util_set_path_p,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_set_size_n",utc_thumbnail_util_set_size_n,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_set_size_p",utc_thumbnail_util_set_size_p,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_cancel_n",utc_thumbnail_util_cancel_n,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_cancel_p",utc_thumbnail_util_cancel_p,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_destroy_n",utc_thumbnail_util_destroy_n,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_destroy_p",utc_thumbnail_util_destroy_p,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_extract_to_file_n1",utc_thumbnail_util_extract_to_file_n1,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_extract_to_file_n2",utc_thumbnail_util_extract_to_file_n2,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_extract_to_file_n3",utc_thumbnail_util_extract_to_file_n3,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_extract_to_file_p1",utc_thumbnail_util_extract_to_file_p1,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_extract_to_file_p2",utc_thumbnail_util_extract_to_file_p2,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_extract_to_buffer_n1",utc_thumbnail_util_extract_to_buffer_n1,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_extract_to_buffer_n2",utc_thumbnail_util_extract_to_buffer_n2,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_extract_to_buffer_p1",utc_thumbnail_util_extract_to_buffer_p1,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{"utc_thumbnail_util_extract_to_buffer_p2",utc_thumbnail_util_extract_to_buffer_p2,utc_thumbnail_util_startup,utc_thumbnail_util_cleanup},
	{NULL, NULL}
};

#endif // __TCT_THUMBNAIL-UTIL-NATIVE_H__
