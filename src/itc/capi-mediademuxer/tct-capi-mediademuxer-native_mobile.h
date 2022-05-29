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
#ifndef __TCT_CAPI-MEDIADEMUXER-NATIVE_H__
#define __TCT_CAPI-MEDIADEMUXER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_mediademuxer_startup(void);
extern void ITs_mediademuxer_cleanup(void);

extern int ITc_mediademuxer_create_destroy_p(void);
extern int ITc_mediademuxer_set_data_source_p(void);
extern int ITc_mediademuxer_prepare_unprepare_p(void);
extern int ITc_mediademuxer_get_track_count_p(void);
extern int ITc_mediademuxer_select_unselect_track_p(void);
extern int ITc_mediademuxer_start_stop_p(void);
extern int ITc_mediademuxer_get_track_info_p(void);
extern int ITc_mediademuxer_read_sample_p(void);
extern int ITc_mediademuxer_seek_p(void);
extern int ITc_mediademuxer_get_state_p(void);
extern int ITc_mediademuxer_set_unset_error_cb_p(void);
extern int ITc_mediademuxer_set_unset_eos_cb_p(void);

testcase tc_array[] = {
	{"ITc_mediademuxer_create_destroy_p",ITc_mediademuxer_create_destroy_p,ITs_mediademuxer_startup,ITs_mediademuxer_cleanup},
	{"ITc_mediademuxer_set_data_source_p",ITc_mediademuxer_set_data_source_p,ITs_mediademuxer_startup,ITs_mediademuxer_cleanup},
	{"ITc_mediademuxer_prepare_unprepare_p",ITc_mediademuxer_prepare_unprepare_p,ITs_mediademuxer_startup,ITs_mediademuxer_cleanup},
	{"ITc_mediademuxer_get_track_count_p",ITc_mediademuxer_get_track_count_p,ITs_mediademuxer_startup,ITs_mediademuxer_cleanup},
	{"ITc_mediademuxer_select_unselect_track_p",ITc_mediademuxer_select_unselect_track_p,ITs_mediademuxer_startup,ITs_mediademuxer_cleanup},
	{"ITc_mediademuxer_start_stop_p",ITc_mediademuxer_start_stop_p,ITs_mediademuxer_startup,ITs_mediademuxer_cleanup},
	{"ITc_mediademuxer_get_track_info_p",ITc_mediademuxer_get_track_info_p,ITs_mediademuxer_startup,ITs_mediademuxer_cleanup},
	{"ITc_mediademuxer_read_sample_p",ITc_mediademuxer_read_sample_p,ITs_mediademuxer_startup,ITs_mediademuxer_cleanup},
	{"ITc_mediademuxer_seek_p",ITc_mediademuxer_seek_p,ITs_mediademuxer_startup,ITs_mediademuxer_cleanup},
	{"ITc_mediademuxer_get_state_p",ITc_mediademuxer_get_state_p,ITs_mediademuxer_startup,ITs_mediademuxer_cleanup},
	{"ITc_mediademuxer_set_unset_error_cb_p",ITc_mediademuxer_set_unset_error_cb_p,ITs_mediademuxer_startup,ITs_mediademuxer_cleanup},
	{"ITc_mediademuxer_set_unset_eos_cb_p",ITc_mediademuxer_set_unset_eos_cb_p,ITs_mediademuxer_startup,ITs_mediademuxer_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CAPI-MEDIADEMUXER-NATIVE_H__
