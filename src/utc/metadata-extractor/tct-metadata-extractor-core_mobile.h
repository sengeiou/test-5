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
#ifndef __TCT_METADATA-EXTRACTOR-NATIVE_H__
#define __TCT_METADATA-EXTRACTOR-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_metadata_extractor_startup(void);
extern void utc_metadata_extractor_cleanup(void);

extern int utc_metadata_extractor_create_n(void);
extern int utc_metadata_extractor_create_p(void);
extern int utc_metadata_extractor_set_path_n1(void);
extern int utc_metadata_extractor_set_path_n2(void);
extern int utc_metadata_extractor_set_path_p(void);
extern int utc_metadata_extractor_set_buffer_n1(void);
extern int utc_metadata_extractor_set_buffer_n2(void);
extern int utc_metadata_extractor_set_buffer_p(void);
extern int utc_metadata_extractor_get_metadata_n(void);
extern int utc_metadata_extractor_get_metadata_p1(void);
extern int utc_metadata_extractor_get_metadata_p2(void);
extern int utc_metadata_extractor_get_metadata_p3(void);
extern int utc_metadata_extractor_get_artwork_n(void);
extern int utc_metadata_extractor_get_artwork_p(void);
extern int utc_metadata_extractor_get_frame_n(void);
extern int utc_metadata_extractor_get_frame_p(void);
extern int utc_metadata_extractor_get_frame_at_time_n(void);
extern int utc_metadata_extractor_get_frame_at_time_p(void);
extern int utc_metadata_extractor_get_synclyrics_n1(void);
extern int utc_metadata_extractor_get_synclyrics_n2(void);
extern int utc_metadata_extractor_get_synclyrics_p(void);
extern int utc_metadata_extractor_destroy_n(void);
extern int utc_metadata_extractor_destroy_p(void);

testcase tc_array[] = {
	{"utc_metadata_extractor_create_n",utc_metadata_extractor_create_n,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_create_p",utc_metadata_extractor_create_p,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_set_path_n1",utc_metadata_extractor_set_path_n1,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_set_path_n2",utc_metadata_extractor_set_path_n2,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_set_path_p",utc_metadata_extractor_set_path_p,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_set_buffer_n1",utc_metadata_extractor_set_buffer_n1,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_set_buffer_n2",utc_metadata_extractor_set_buffer_n2,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_set_buffer_p",utc_metadata_extractor_set_buffer_p,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_metadata_n",utc_metadata_extractor_get_metadata_n,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_metadata_p1",utc_metadata_extractor_get_metadata_p1,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_metadata_p2",utc_metadata_extractor_get_metadata_p2,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_metadata_p3",utc_metadata_extractor_get_metadata_p3,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_artwork_n",utc_metadata_extractor_get_artwork_n,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_artwork_p",utc_metadata_extractor_get_artwork_p,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_frame_n",utc_metadata_extractor_get_frame_n,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_frame_p",utc_metadata_extractor_get_frame_p,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_frame_at_time_n",utc_metadata_extractor_get_frame_at_time_n,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_frame_at_time_p",utc_metadata_extractor_get_frame_at_time_p,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_synclyrics_n1",utc_metadata_extractor_get_synclyrics_n1,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_synclyrics_n2",utc_metadata_extractor_get_synclyrics_n2,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_get_synclyrics_p",utc_metadata_extractor_get_synclyrics_p,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_destroy_n",utc_metadata_extractor_destroy_n,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{"utc_metadata_extractor_destroy_p",utc_metadata_extractor_destroy_p,utc_metadata_extractor_startup,utc_metadata_extractor_cleanup},
	{NULL, NULL}
};

#endif // __TCT_METADATA-EXTRACTOR-NATIVE_H__
