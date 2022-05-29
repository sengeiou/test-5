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
#ifndef __TCT_MEDIADEMUXER-NATIVE_H__
#define __TCT_MEDIADEMUXER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_mediademuxer_startup(void);
extern void utc_mediademuxer_cleanup(void);

extern int utc_mediademuxer_create_p(void);
extern int utc_mediademuxer_create_n(void);
extern int utc_mediademuxer_set_data_source_p(void);
extern int utc_mediademuxer_set_data_source_n(void);
extern int utc_mediademuxer_set_data_source_n2(void);
extern int utc_mediademuxer_prepare_p(void);
extern int utc_mediademuxer_prepare_n(void);
extern int utc_mediademuxer_get_track_count_p(void);
extern int utc_mediademuxer_get_track_count_n(void);
extern int utc_mediademuxer_get_track_info_p(void);
extern int utc_mediademuxer_get_track_info_n(void);
extern int utc_mediademuxer_select_track_p(void);
extern int utc_mediademuxer_select_track_n(void);
extern int utc_mediademuxer_start_p(void);
extern int utc_mediademuxer_start_n(void);
extern int utc_mediademuxer_read_sample_p(void);
extern int utc_mediademuxer_read_sample_n(void);
extern int utc_mediademuxer_seek_p(void);
extern int utc_mediademuxer_seek_n(void);
extern int utc_mediademuxer_set_error_cb_p(void);
extern int utc_mediademuxer_set_error_cb_n(void);
extern int utc_mediademuxer_unset_error_cb_p(void);
extern int utc_mediademuxer_unset_error_cb_n(void);
extern int utc_mediademuxer_set_eos_cb_p(void);
extern int utc_mediademuxer_set_eos_cb_n(void);
extern int utc_mediademuxer_unset_eos_cb_p(void);
extern int utc_mediademuxer_unset_eos_cb_n(void);
extern int utc_mediademuxer_get_state_p(void);
extern int utc_mediademuxer_get_state_n(void);
extern int utc_mediademuxer_unselect_track_p(void);
extern int utc_mediademuxer_unselect_track_n(void);
extern int utc_mediademuxer_stop_p(void);
extern int utc_mediademuxer_stop_n(void);
extern int utc_mediademuxer_unprepare_p(void);
extern int utc_mediademuxer_unprepare_n(void);
extern int utc_mediademuxer_destroy_p(void);
extern int utc_mediademuxer_destroy_n(void);

testcase tc_array[] = {
	{"utc_mediademuxer_create_p",utc_mediademuxer_create_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_create_n",utc_mediademuxer_create_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_set_data_source_p",utc_mediademuxer_set_data_source_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_set_data_source_n",utc_mediademuxer_set_data_source_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_set_data_source_n2",utc_mediademuxer_set_data_source_n2,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_prepare_p",utc_mediademuxer_prepare_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_prepare_n",utc_mediademuxer_prepare_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_get_track_count_p",utc_mediademuxer_get_track_count_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_get_track_count_n",utc_mediademuxer_get_track_count_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_get_track_info_p",utc_mediademuxer_get_track_info_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_get_track_info_n",utc_mediademuxer_get_track_info_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_select_track_p",utc_mediademuxer_select_track_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_select_track_n",utc_mediademuxer_select_track_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_start_p",utc_mediademuxer_start_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_start_n",utc_mediademuxer_start_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_read_sample_p",utc_mediademuxer_read_sample_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_read_sample_n",utc_mediademuxer_read_sample_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_seek_p",utc_mediademuxer_seek_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_seek_n",utc_mediademuxer_seek_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_set_error_cb_p",utc_mediademuxer_set_error_cb_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_set_error_cb_n",utc_mediademuxer_set_error_cb_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_unset_error_cb_p",utc_mediademuxer_unset_error_cb_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_unset_error_cb_n",utc_mediademuxer_unset_error_cb_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_set_eos_cb_p",utc_mediademuxer_set_eos_cb_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_set_eos_cb_n",utc_mediademuxer_set_eos_cb_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_unset_eos_cb_p",utc_mediademuxer_unset_eos_cb_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_unset_eos_cb_n",utc_mediademuxer_unset_eos_cb_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_get_state_p",utc_mediademuxer_get_state_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_get_state_n",utc_mediademuxer_get_state_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_unselect_track_p",utc_mediademuxer_unselect_track_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_unselect_track_n",utc_mediademuxer_unselect_track_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_stop_p",utc_mediademuxer_stop_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_stop_n",utc_mediademuxer_stop_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_unprepare_p",utc_mediademuxer_unprepare_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_unprepare_n",utc_mediademuxer_unprepare_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_destroy_p",utc_mediademuxer_destroy_p,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{"utc_mediademuxer_destroy_n",utc_mediademuxer_destroy_n,utc_mediademuxer_startup,utc_mediademuxer_cleanup},
	{NULL, NULL}
};

#endif // __TCT_MEDIADEMUXER-NATIVE_H__
