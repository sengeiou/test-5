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
#include <tone_player.h>
#include <sound_manager.h>

#include "assert.h"

//& set: Tone-player
#define DURATION 1000

static void _sound_stream_focus_state_changed_cb(sound_stream_info_h stream_info, sound_stream_focus_mask_e focus_mask, sound_stream_focus_state_e focus_state,
sound_stream_focus_change_reason_e reason_for_change, int sound_behavior, const char *additional_info, void *user_data)
{
}

/**
 * @testcase		utc_tone_player_start_new_p
 * @since_tizen		3.0
 * @description		Positive test case to start tone player with stream info
 * @scenario		Create stream info with sound-manager API
 * 					start tone player with stream info
 */
int utc_tone_player_start_new_p(void)
{
    int ret = TONE_PLAYER_ERROR_NONE;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = tone_player_start_new(TONE_TYPE_DEFAULT, stream_info, DURATION, NULL);
    assert_eq(ret, TONE_PLAYER_ERROR_NONE);

    ret = sound_manager_destroy_stream_information(stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_tone_player_start_new_n1
 * @since_tizen		3.0
 * @description		Negative test case to start tone player with stream info, passing invalid tone type
 * @scenario		Create stream info with sound-manager API
 * 					start tone player with proper stream info and wrong parameter(invalid tone type)
 */
int utc_tone_player_start_new_n1(void)
{
    int ret = TONE_PLAYER_ERROR_NONE;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = tone_player_start_new(-1, stream_info, DURATION, NULL);
    assert_eq(ret, TONE_PLAYER_ERROR_INVALID_PARAMETER);

    ret = sound_manager_destroy_stream_information(stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_tone_player_start_new_n2
 * @since_tizen		3.0
 * @description		Negative test case to start tone player with stream info, passing null pointer for stream info
 * @scenario		Create stream info with sound-manager API
 * 					start tone player with proper stream info and wrong parameter(null pointer for stream info)
 */
int utc_tone_player_start_new_n2(void)
{
    int ret = TONE_PLAYER_ERROR_NONE;

    ret = tone_player_start_new(TONE_TYPE_DEFAULT, NULL, DURATION, NULL);
    assert_eq(ret, TONE_PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_tone_player_stop_p
 * @since_tizen		3.0
 * @description		Positive test case to stop tone player which have been started with stream info
 * @scenario		Create stream info with sound-manager API
 * 					start tone player with stream info
 * 					stop tone player with handle
 */
int utc_tone_player_stop_p(void)
{
    int ret = TONE_PLAYER_ERROR_INVALID_PARAMETER;
    int id;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = tone_player_start_new(TONE_TYPE_DEFAULT, stream_info, DURATION, &id);
    assert_eq(ret, TONE_PLAYER_ERROR_NONE);

    ret = tone_player_stop(id);
    assert_eq(ret, TONE_PLAYER_ERROR_NONE);

    ret = sound_manager_destroy_stream_information(stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_tone_player_stop_n
 * @since_tizen		2.3
 * @description		Negative test case to stop tone player, passing wrong handle id to stop
 * @scenario		stop tone player with wrong parameter (wrong handle id)
 */
int utc_tone_player_stop_n(void)
{
    int ret = TONE_PLAYER_ERROR_NONE;
    int id = -1;
    ret = tone_player_stop(id);
    assert_eq(ret, TONE_PLAYER_ERROR_INVALID_PARAMETER);
    return 0;
}
