//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#ifndef __TCT_PLAYER_DISPLAY_NATIVE_H__
#define __TCT_PLAYER_DISPLAY_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_player_display_startup(void);
extern void ITs_player_display_cleanup(void);
extern void ITs_player_360_startup(void);
extern void ITs_player_360_cleanup(void);

extern int ITc_player_set_get_video_roi_area_p(void);
extern int ITc_player_set_get_display_rotation_p(void);
extern int ITc_player_set_display_visible_p(void);
extern int ITc_player_set_get_display_mode_p(void);
extern int ITc_player_is_display_visible_p(void);
extern int ITc_player_set_display_roi_area_p(void);
extern int ITc_player_set_audio_only_p(void);
extern int ITc_player_is_audio_only_p(void);
extern int ITc_player_get_video_size_p(void);
extern int ITc_player_get_video_stream_info_p(void);
extern int ITc_player_capture_video_p(void);
extern int ITc_player_set_unset_video_stream_changed_cb_p(void);
extern int ITc_media_player_360_is_content_spherical_p(void);
extern int ITc_player_360_is_set_enabled_p(void);
extern int ITc_player_360_set_get_direction_of_view_p(void);
extern int ITc_player_360_set_get_zoom_p(void);
extern int ITc_player_360_set_get_field_of_view(void);
extern int ITc_player_360_set_zoom_with_field_of_view_p(void);
extern int ITc_player_set_display_p(void);

testcase tc_array[] = {
	{"ITc_player_set_get_video_roi_area_p",ITc_player_set_get_video_roi_area_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_player_set_display_p",ITc_player_set_display_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_player_set_get_display_rotation_p",ITc_player_set_get_display_rotation_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_player_set_display_visible_p",ITc_player_set_display_visible_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_player_set_get_display_mode_p",ITc_player_set_get_display_mode_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_player_is_display_visible_p",ITc_player_is_display_visible_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_player_set_display_roi_area_p",ITc_player_set_display_roi_area_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_player_set_audio_only_p",ITc_player_set_audio_only_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_player_is_audio_only_p",ITc_player_is_audio_only_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_player_get_video_size_p",ITc_player_get_video_size_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_player_get_video_stream_info_p",ITc_player_get_video_stream_info_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_player_capture_video_p",ITc_player_capture_video_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_player_set_unset_video_stream_changed_cb_p",ITc_player_set_unset_video_stream_changed_cb_p,ITs_player_display_startup,ITs_player_display_cleanup},
	{"ITc_media_player_360_is_content_spherical_p",ITc_media_player_360_is_content_spherical_p,ITs_player_360_startup,ITs_player_360_cleanup},
	{"ITc_player_360_is_set_enabled_p",ITc_player_360_is_set_enabled_p,ITs_player_360_startup,ITs_player_360_cleanup},
	{"ITc_player_360_set_get_direction_of_view_p",ITc_player_360_set_get_direction_of_view_p,ITs_player_360_startup,ITs_player_360_cleanup},
	{"ITc_player_360_set_get_zoom_p",ITc_player_360_set_get_zoom_p,ITs_player_360_startup,ITs_player_360_cleanup},
	{"ITc_player_360_set_get_field_of_view",ITc_player_360_set_get_field_of_view,ITs_player_360_startup,ITs_player_360_cleanup},
	{"ITc_player_360_set_zoom_with_field_of_view_p",ITc_player_360_set_zoom_with_field_of_view_p,ITs_player_360_startup,ITs_player_360_cleanup},
    {NULL, NULL}
};

#endif // __TCT_PLAYER_DISPLAY_NATIVE_H__
