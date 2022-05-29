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
#include "assert.h"
#include <wav_player.h>
#include <pthread.h>
#include <unistd.h>
#include <storage.h>
#include <glib.h>
#include <string.h>
#include <sound_manager.h>
#include "tct_common.h"

#define API_NAMESPACE        "[WAV_PLAYER]"

#define TIMEOUT_MSEC	10000 /* 10 sec, test content duration is 5 sec. */
static char* TESTFILE = NULL;
static const char* TESTFILENAME = "sound_5.wav";
static GMainLoop *g_mainloop;

//& set: WavPlayer

static void _sound_stream_focus_state_changed_cb(sound_stream_info_h stream_info, sound_stream_focus_mask_e focus_mask, sound_stream_focus_state_e focus_state,
                                                 sound_stream_focus_change_reason_e reason_for_change, int sound_behavior, const char *additional_info, void *user_data)
{
}

static void _playback_completed_cb(int id, void *user_data)
{
    fprintf(stderr, "playback complete!!! id = %d\n, user_data = %p, now quit mainloop", id, user_data);
    *(int*)user_data = 1;
    g_main_loop_quit(g_mainloop);
}

static gboolean _timeout_cb(gpointer data)
{
    fprintf(stderr, "Timeout! Test case failed!\n");
    g_main_loop_quit((GMainLoop *)data);
    return FALSE;
}

/**
 * @function		utc_wav_player_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_wav_player_startup(void)
{
    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    if ( true == GetValueForTCTSetting("DEVICE_PHYSICAL_STORAGE_30", pszValue, API_NAMESPACE ))
    {
        PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_STORAGEE_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
        unsigned int size_of_path = strlen(pszValue) + strlen(TESTFILENAME) + 6;
        TESTFILE = (char*)malloc(size_of_path);
        snprintf(TESTFILE, size_of_path, "%s/res/%s", pszValue, TESTFILENAME);
    }
    else
    {
        PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
    }
}

/**
 * @function		utc_wav_player_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_wav_player_cleanup(void)
{
    if(TESTFILE != NULL) {
        free(TESTFILE);
        TESTFILE = NULL;
    }
}

/**
 * @testcase		utc_wav_player_start_new_p
 * @since_tizen		3.0
 * @description		Positive test case to start wav player with stream info
 * @scenario		Create stream info with sound-manager API
 * 					start wav player with stream info
 */
int utc_wav_player_start_new_p(void)
{
    int ret = WAV_PLAYER_ERROR_NONE;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = wav_player_start_new(TESTFILE, stream_info, NULL, NULL, NULL);
    assert_eq(WAV_PLAYER_ERROR_NONE, ret);

    ret = sound_manager_destroy_stream_information(stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wav_player_start_new_n1
 * @since_tizen		3.0
 * @description		Negative test case to start wav player with stream info, passing null pointer for file path
 * @scenario		Create stream info with sound-manager API
 * 					start wav player with proper stream info and invalid parameter(null pointer for file path)
 */
int utc_wav_player_start_new_n1(void)
{
    int ret = WAV_PLAYER_ERROR_NONE;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = wav_player_start_new(NULL, stream_info, NULL, NULL, NULL);
    assert_eq(WAV_PLAYER_ERROR_INVALID_PARAMETER, ret);

    ret = sound_manager_destroy_stream_information(stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wav_player_start_new_n2
 * @since_tizen		3.0
 * @description		Negative test case to start wav player with stream info, passing null pointer for stream info
 * @scenario		start wav player with invalid parameter (null pointer for stream info)
 */
int utc_wav_player_start_new_n2(void)
{
    int ret = WAV_PLAYER_ERROR_NONE;

    ret = wav_player_start_new(TESTFILE, NULL, NULL, NULL, NULL);
    assert_eq(WAV_PLAYER_ERROR_INVALID_PARAMETER, ret);
    return 0;
}

/**
 * @testcase		utc_wav_player_start_new_n3
 * @since_tizen		2.3
 * @description		Negative test case to start wav player, passing non-existing file path
 * @scenario		start wav player with invalid parameters (non-existing file for file path)
 */
int utc_wav_player_start_new_n3(void)
{
    int ret = WAV_PLAYER_ERROR_NONE;
    sound_stream_info_h stream_info;
    char file_name[100] = { '\0' };

    snprintf(file_name, 100, "%s", "something");

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = wav_player_start_new(file_name, stream_info, NULL, NULL, NULL);
    assert_eq(ret, WAV_PLAYER_ERROR_INVALID_OPERATION);

    ret = sound_manager_destroy_stream_information(stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wav_player_start_loop_p
 * @since_tizen		6.0
 * @description		Positive test case to start wav player with loop (loop count = 3)
 * @scenario		Create stream info with sound-manager API
 * 					start wav player loop
 */
int utc_wav_player_start_loop_p(void)
{
    int ret = WAV_PLAYER_ERROR_NONE;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_ALARM, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = wav_player_start_loop(TESTFILE, stream_info, 3, NULL, NULL, NULL);
    assert_eq(ret, WAV_PLAYER_ERROR_NONE);

    ret = sound_manager_destroy_stream_information(stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wav_player_start_loop_n1
 * @since_tizen		6.0
 * @description		Negative test case to start wav player with loop, passing null pointer for file path
 * @scenario		Create stream info with sound-manager API
 * 					start wav player loop and invalid parameter(null pointer for file path)
 */
int utc_wav_player_start_loop_n1(void)
{
    int ret = WAV_PLAYER_ERROR_NONE;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = wav_player_start_loop(NULL, stream_info, 1, NULL, NULL, NULL);
    assert_eq(ret, WAV_PLAYER_ERROR_INVALID_PARAMETER);

    ret = sound_manager_destroy_stream_information(stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wav_player_start_loop_n2
 * @since_tizen		6.0
 * @description		Negative test case to start wav player with loop, passing null pointer for stream info
 * @scenario		start wav player with invalid parameter (null pointer for stream info)
 */
int utc_wav_player_start_loop_n2(void)
{
    int ret = WAV_PLAYER_ERROR_NONE;

    ret = wav_player_start_loop(TESTFILE, NULL, 1, NULL, NULL, NULL);
    assert_eq(ret, WAV_PLAYER_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_wav_player_start_loop_n3
 * @since_tizen		6.0
 * @description		Negative test case to start wav player, passing non-existing file path
 * @scenario		start wav player with invalid parameters (non-existing file for file path)
 */
int utc_wav_player_start_loop_n3(void)
{
    int ret = WAV_PLAYER_ERROR_NONE;
    sound_stream_info_h stream_info;
    char file_name[100] = { '\0' };

    snprintf(file_name, 100, "%s", "something");

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = wav_player_start_loop(file_name, stream_info, 1, NULL, NULL, NULL);
    assert_eq(ret, WAV_PLAYER_ERROR_INVALID_OPERATION);

    ret = sound_manager_destroy_stream_information(stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wav_player_stop_p
 * @since_tizen		2.3
 * @description		Positive test case to stop wav player
 * @scenario		start wav player and get handle of it
 * 					stop wav player with handle
 */
int utc_wav_player_stop_p(void)
{
    int ret = WAV_PLAYER_ERROR_INVALID_PARAMETER;
    int id = 0;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = wav_player_start_new(TESTFILE, stream_info, NULL, NULL, &id);
    assert_eq(ret, WAV_PLAYER_ERROR_NONE);

    ret = wav_player_stop(id);
    assert_eq(ret, WAV_PLAYER_ERROR_NONE);

    ret = sound_manager_destroy_stream_information(stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_wav_player_stop_n
 * @since_tizen		2.3
 * @description		Negative test case to stop wav player, passing wrong id for handle
 * @scenario		stop wav player with wrong handle id
 */
int utc_wav_player_stop_n(void)
{
    int ret = WAV_PLAYER_ERROR_NONE;

    ret = wav_player_stop(-1);
    assert_eq(ret, WAV_PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase		utc_wav_player_callback_p
 * @since_tizen		3.0
 * @description		Positive test case for wav play completed callback
 * @scenario		start wav player with stream info and callback
 * 					wait for callback being called
 * 					In callbck function, send signal to notify
 * 					Test case context unblocked with signal
 * 					Check value which have been changed to some value
 */
int utc_wav_player_callback_p(void)
{
    int ret = WAV_PLAYER_ERROR_NONE;
    int timeout_id = 0;
    int cb_ret = 0;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = wav_player_start_new(TESTFILE, stream_info, _playback_completed_cb, &cb_ret, NULL);
    assert_eq(ret, WAV_PLAYER_ERROR_NONE);

    g_mainloop = g_main_loop_new(NULL, FALSE);
    timeout_id = g_timeout_add(TIMEOUT_MSEC, _timeout_cb, g_mainloop);

    g_main_loop_run(g_mainloop);
    g_source_remove(timeout_id);

    assert_eq(cb_ret, 1);

    ret = sound_manager_destroy_stream_information(stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}
