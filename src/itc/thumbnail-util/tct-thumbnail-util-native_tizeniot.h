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

extern void ITs_thumbnail_util_startup(void);
extern void ITs_thumbnail_util_cleanup(void);

extern int ITc_thumnail_util_create_destroy_p(void);
extern int ITc_thumnail_util_set_path_p(void);
extern int ITc_thumnail_util_set_size_p(void);
extern int ITc_thumnail_util_extract_p(void);
extern int ITc_thumnail_util_extract_cancel_p(void);
extern int ITc_thumbnail_util_extract_to_file(void);
extern int ITc_thumbnail_util_extract_to_buffer(void);

testcase tc_array[] = {
	{"ITc_thumnail_util_create_destroy_p",ITc_thumnail_util_create_destroy_p,ITs_thumbnail_util_startup,ITs_thumbnail_util_cleanup},
	{"ITc_thumnail_util_set_path_p",ITc_thumnail_util_set_path_p,ITs_thumbnail_util_startup,ITs_thumbnail_util_cleanup},
	{"ITc_thumnail_util_set_size_p",ITc_thumnail_util_set_size_p,ITs_thumbnail_util_startup,ITs_thumbnail_util_cleanup},
	{"ITc_thumnail_util_extract_p",ITc_thumnail_util_extract_p,ITs_thumbnail_util_startup,ITs_thumbnail_util_cleanup},
	{"ITc_thumnail_util_extract_cancel_p",ITc_thumnail_util_extract_cancel_p,ITs_thumbnail_util_startup,ITs_thumbnail_util_cleanup},
	{"ITc_thumbnail_util_extract_to_file",ITc_thumbnail_util_extract_to_file,ITs_thumbnail_util_startup,ITs_thumbnail_util_cleanup},
	{"ITc_thumbnail_util_extract_to_buffer",ITc_thumbnail_util_extract_to_buffer,ITs_thumbnail_util_startup,ITs_thumbnail_util_cleanup},
	{NULL, NULL}
};

#endif // __TCT_THUMBNAIL-UTIL-NATIVE_H__
