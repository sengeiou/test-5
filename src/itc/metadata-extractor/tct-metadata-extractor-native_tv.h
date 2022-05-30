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

extern void ITs_metadata_extractor_startup(void);
extern void ITs_metadata_extractor_cleanup(void);

extern int ITc_metadata_extractor_create_destroy_p(void);
extern int ITc_metadata_extractor_get_artwork_p(void);
extern int ITc_metadata_extractor_get_frame_p(void);
extern int ITc_metadata_extractor_get_frame_at_time_p(void);
extern int ITc_metadata_extractor_get_metadata_p(void);
extern int ITc_metadata_extractor_get_synclyrics_p(void);
extern int ITc_metadata_extractor_set_buffer_p(void);
extern int ITc_metadata_extractor_set_path_p(void);

testcase tc_array[] = {
	{"ITc_metadata_extractor_create_destroy_p",ITc_metadata_extractor_create_destroy_p,ITs_metadata_extractor_startup,ITs_metadata_extractor_cleanup},
	{"ITc_metadata_extractor_get_artwork_p",ITc_metadata_extractor_get_artwork_p,ITs_metadata_extractor_startup,ITs_metadata_extractor_cleanup},
	{"ITc_metadata_extractor_get_frame_p",ITc_metadata_extractor_get_frame_p,ITs_metadata_extractor_startup,ITs_metadata_extractor_cleanup},
	{"ITc_metadata_extractor_get_frame_at_time_p",ITc_metadata_extractor_get_frame_at_time_p,ITs_metadata_extractor_startup,ITs_metadata_extractor_cleanup},
	{"ITc_metadata_extractor_get_metadata_p",ITc_metadata_extractor_get_metadata_p,ITs_metadata_extractor_startup,ITs_metadata_extractor_cleanup},
	{"ITc_metadata_extractor_get_synclyrics_p",ITc_metadata_extractor_get_synclyrics_p,ITs_metadata_extractor_startup,ITs_metadata_extractor_cleanup},
	{"ITc_metadata_extractor_set_buffer_p",ITc_metadata_extractor_set_buffer_p,ITs_metadata_extractor_startup,ITs_metadata_extractor_cleanup},
	{"ITc_metadata_extractor_set_path_p",ITc_metadata_extractor_set_path_p,ITs_metadata_extractor_startup,ITs_metadata_extractor_cleanup},
	{NULL, NULL}
};

#endif // __TCT_METADATA-EXTRACTOR-NATIVE_H__
