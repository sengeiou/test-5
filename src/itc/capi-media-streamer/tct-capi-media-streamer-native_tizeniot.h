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
#ifndef __TCT_CAPI-MEDIA-STREAMER-NATIVE_H__
#define __TCT_CAPI-MEDIA-STREAMER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_capi_media_streamer_startup(void);
extern void ITs_capi_media_streamer_cleanup(void);

extern int ITc_capi_media_streamer_prepare_unprepare_p(void);
extern int ITc_capi_media_streamer_play_pause_stop_p(void);
extern int ITc_capi_media_streamer_get_state_p(void);
extern int ITc_capi_media_streamer_node_create_src_p(void);
extern int ITc_capi_media_streamer_node_push_packet_p(void);
extern int ITc_capi_media_streamer_node_create_sink_p(void);
extern int ITc_capi_media_streamer_node_pull_packet_p(void);
extern int ITc_capi_media_streamer_node_add_remove_p(void);
extern int ITc_capi_media_streamer_node_link_p(void);
extern int ITc_capi_media_streamer_node_node_set_get_pad_format_p(void);
extern int ITc_capi_media_streamer_node_get_pad_name_p(void);
extern int ITc_capi_media_streamer_node_set_get_params_p(void);
extern int ITc_capi_media_streamer_set_get_play_position(void);
extern int ITc_capi_media_streamer_get_duration_p(void);
extern int ITc_capi_media_streamer_set_unset_interrupted_p(void);

testcase tc_array[] = {
	{"ITc_capi_media_streamer_prepare_unprepare_p",ITc_capi_media_streamer_prepare_unprepare_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_play_pause_stop_p",ITc_capi_media_streamer_play_pause_stop_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_get_state_p",ITc_capi_media_streamer_get_state_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_node_create_src_p",ITc_capi_media_streamer_node_create_src_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_node_push_packet_p",ITc_capi_media_streamer_node_push_packet_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_node_create_sink_p",ITc_capi_media_streamer_node_create_sink_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_node_pull_packet_p",ITc_capi_media_streamer_node_pull_packet_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_node_add_remove_p",ITc_capi_media_streamer_node_add_remove_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_node_link_p",ITc_capi_media_streamer_node_link_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_node_node_set_get_pad_format_p",ITc_capi_media_streamer_node_node_set_get_pad_format_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_node_get_pad_name_p",ITc_capi_media_streamer_node_get_pad_name_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_node_set_get_params_p",ITc_capi_media_streamer_node_set_get_params_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_set_get_play_position",ITc_capi_media_streamer_set_get_play_position,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_get_duration_p",ITc_capi_media_streamer_get_duration_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{"ITc_capi_media_streamer_set_unset_interrupted_p",ITc_capi_media_streamer_set_unset_interrupted_p,ITs_capi_media_streamer_startup,ITs_capi_media_streamer_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CAPI-MEDIA-STREAMER-NATIVE_H__
