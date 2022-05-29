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
#ifndef __TCT_MEDIA-KEY-NATIVE_H__
#define __TCT_MEDIA-KEY-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_media_key_reserve_func_cleanup(void);

extern int utc_media_key_release_p(void);
extern int utc_media_key_reserve_p(void);
extern int utc_media_key_reserve_n(void);

testcase tc_array[] = {
	{"utc_media_key_release_p",utc_media_key_release_p,NULL,NULL},
	{"utc_media_key_reserve_p",utc_media_key_reserve_p,NULL,utc_media_key_reserve_func_cleanup},
	{"utc_media_key_reserve_n",utc_media_key_reserve_n,NULL,utc_media_key_reserve_func_cleanup},
	{NULL, NULL}
};

#endif // __TCT_MEDIA-KEY-NATIVE_H__
