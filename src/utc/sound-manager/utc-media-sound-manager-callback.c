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
#include <media/sound_manager.h>

//& set: Soundmanager-Callback

static void _sound_volume_changed_cb(sound_type_e type, unsigned int volume, void *user_data)
{
}

static void _sound_device_connected_cb(sound_device_h device, bool is_connected, void *user_data)
{
}

static void _sound_device_running_changed_cb(sound_device_h device, bool is_running, void *user_data)
{
}

static void _sound_device_state_changed_cb(sound_device_h device, sound_device_state_e state, void *user_data)
{
}

static void _sound_stream_focus_state_watch_cb(int id, sound_stream_focus_mask_e changed_focus_mask, sound_stream_focus_state_e changed_focus_state, sound_stream_focus_change_reason_e reason_for_change, const char *additional_info, void *user_data)
{
}

/**
 * @testcase		utc_media_sound_manager_add_volume_changed_cb_p
 * @since_tizen		3.0
 * @description		Adds a callback function to be invoked when the volume level is changed
 */
int utc_media_sound_manager_add_volume_changed_cb_p(void)
{
    int ret;
    int cb_id;
    ret = sound_manager_add_volume_changed_cb(_sound_volume_changed_cb, NULL, &cb_id);
    assert_eq (ret, SOUND_MANAGER_ERROR_NONE);

    sound_manager_remove_volume_changed_cb(cb_id);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_add_volume_changed_cb_n
 * @since_tizen		3.0
 * @description		Adds a callback function to be invoked when the volume level is changed
 *				- Pass invalid parameter to get negative result
 */
int utc_media_sound_manager_add_volume_changed_cb_n(void)
{
    int ret;
    ret = sound_manager_add_volume_changed_cb(NULL, NULL, NULL);
    assert_eq (ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_remove_volume_changed_cb_p
 * @since_tizen		3.0
 * @description		Removes the volume change callback
 *				- Add the volume change callback before unsetting the callback
 */
int utc_media_sound_manager_remove_volume_changed_cb_p(void)
{
    int ret;
    int cb_id;
    ret = sound_manager_add_volume_changed_cb(_sound_volume_changed_cb, NULL, &cb_id);
    assert_eq (ret, SOUND_MANAGER_ERROR_NONE);

    ret = sound_manager_remove_volume_changed_cb(cb_id);
    assert_eq (ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_remove_volume_changed_cb_n
 * @since_tizen		3.0
 * @description		Removes the volume change callback
 *				- Unset the callback without setting callback to get negative result
 */
int utc_media_sound_manager_remove_volume_changed_cb_n(void)
{
    int ret = sound_manager_remove_volume_changed_cb(-1);
    assert_eq (ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_add_device_connection_changed_cb_p
 * @since_tizen		3.0
 * @description		Adds a callback function to be invoked when the state of connection of a sound device was changed
 */
int utc_media_sound_manager_add_device_connection_changed_cb_p(void)
{
	int ret;
	int cb_id;
	ret = sound_manager_add_device_connection_changed_cb(SOUND_DEVICE_ALL_MASK, _sound_device_connected_cb, NULL, &cb_id);
	assert_eq (ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_remove_device_connection_changed_cb(cb_id);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_add_device_connection_changed_cb_n
 * @since_tizen		3.0
 * @description		Adds a callback function to be invoked when the state of connection of a sound device was changed
 *				- Pass invalid parameter to get negative result
 */
int utc_media_sound_manager_add_device_connection_changed_cb_n(void)
{
	int ret = sound_manager_add_device_connection_changed_cb(0, NULL, NULL, NULL);
	assert_eq (ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_remove_device_connection_changed_cb_p
 * @since_tizen		3.0
 * @description		Removes the callback function which is called when the state of connection of a sound device was changed
 *				- Add the device connected callback before removing the callback
 */
int utc_media_sound_manager_remove_device_connection_changed_cb_p(void)
{
	int ret;
	int cb_id;

	ret = sound_manager_add_device_connection_changed_cb(SOUND_DEVICE_ALL_MASK, _sound_device_connected_cb, NULL, &cb_id);
	assert_eq (ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_remove_device_connection_changed_cb(cb_id);
	assert_eq (ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_remove_device_connection_changed_cb_n
 * @since_tizen		3.0
 * @description		Removes the callback function which is called when the state of connection of a sound device was changed
 *				- Remove the callback without adding callback to get negative result
 */
int utc_media_sound_manager_remove_device_connection_changed_cb_n(void)
{
	int ret = sound_manager_remove_device_connection_changed_cb(-1);
	assert_eq (ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_add_device_state_changed_cb_p
 * @since_tizen		3.0
 * @description		Adds a callback function to be invoked when the state of a sound device was changed
 */
int utc_media_sound_manager_add_device_state_changed_cb_p(void)
{
	int ret;
	int cb_id;
	ret = sound_manager_add_device_state_changed_cb(SOUND_DEVICE_ALL_MASK, _sound_device_state_changed_cb, NULL, &cb_id);
	assert_eq (ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_remove_device_state_changed_cb(cb_id);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_add_device_state_changed_cb_n
 * @since_tizen		3.0
 * @description		Adds a callback function to be invoked when the state of a sound device was changed
 *				- Pass invalid parameter to get negative result
 */
int utc_media_sound_manager_add_device_state_changed_cb_n(void)
{
	int ret = sound_manager_add_device_state_changed_cb(0, NULL, NULL, NULL);
	assert_eq (ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_remove_device_state_changed_cb_p
 * @since_tizen		3.0
 * @description		Removes the callback function which is called when the state of a sound device was changed
 *				- Add the device connected callback before removing the callback
 */
int utc_media_sound_manager_remove_device_state_changed_cb_p(void)
{
	int ret;
	int cb_id;

	ret = sound_manager_add_device_state_changed_cb(SOUND_DEVICE_ALL_MASK, _sound_device_state_changed_cb, NULL, &cb_id);
	assert_eq (ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_remove_device_state_changed_cb(cb_id);
	assert_eq (ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_remove_device_state_changed_cb_n
 * @since_tizen		3.0
 * @description		Removes the callback function which is called when the state of sound device was changed
 *				- Remove the callback without adding callback to get negative result
 */
int utc_media_sound_manager_remove_device_state_changed_cb_n(void)
{
	int ret = sound_manager_remove_device_state_changed_cb(-1);
	assert_eq (ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_add_focus_state_watch_cb_p
 * @since_tizen		3.0
 * @description		Registers the watch callback function to be invoked when the focus state for each sound stream type is changed regardless of the process
 */
int utc_media_sound_manager_add_focus_state_watch_cb_p(void)
{
	int ret;
	int id;

	ret = sound_manager_add_focus_state_watch_cb(SOUND_STREAM_FOCUS_FOR_PLAYBACK, _sound_stream_focus_state_watch_cb, NULL, &id);
	assert_eq (ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_remove_focus_state_watch_cb(id);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_add_focus_state_watch_cb_n
 * @since_tizen		3.0
 * @description		Registers the watch callback function to be invoked when the focus state for each sound stream type is changed regardless of the process
				- Pass invalid parameter to get negative result
 */
int utc_media_sound_manager_add_focus_state_watch_cb_n(void)
{
	int ret;

	ret = sound_manager_add_focus_state_watch_cb(SOUND_STREAM_FOCUS_FOR_PLAYBACK, NULL, NULL, NULL);
	assert_eq (ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_remove_focus_state_watch_cb_p
 * @since_tizen		3.0
 * @description		Unregisters the focus state watch callback
 *				- Register the focus state watch callback before unsetting the callback
 */
int utc_media_sound_manager_remove_focus_state_watch_cb_p(void)
{
	int ret;
	int id;

	ret = sound_manager_add_focus_state_watch_cb(SOUND_STREAM_FOCUS_FOR_PLAYBACK, _sound_stream_focus_state_watch_cb, NULL, &id);
	assert_eq (ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_remove_focus_state_watch_cb(id);
	assert_eq (ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_remove_focus_state_watch_cb_n
 * @since_tizen		3.0
 * @description		Unregisters the focus state watch callback
 *				- Unset the callback without setting callback to get negative result
 */
int utc_media_sound_manager_remove_focus_state_watch_cb_n(void)
{
	int ret;

	ret = sound_manager_remove_focus_state_watch_cb(-1);
	assert_eq (ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_add_device_running_changed_cb_p
 * @since_tizen		5.0
 * @description		Adds a callback function to be invoked when the state of a sound device was changed
 */
int utc_media_sound_manager_add_device_running_changed_cb_p(void)
{
	int ret;
	int cb_id;
	ret = sound_manager_add_device_running_changed_cb(SOUND_DEVICE_ALL_MASK, _sound_device_running_changed_cb, NULL, &cb_id);
	assert_eq (ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_remove_device_connection_changed_cb(cb_id);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_add_device_running_changed_cb_n
 * @since_tizen		5.0
 * @description		Adds a callback function to be invoked when the state of a sound device was changed
 *				- Pass invalid parameter to get negative result
 */
int utc_media_sound_manager_add_device_running_changed_cb_n(void)
{
	int ret = sound_manager_add_device_running_changed_cb(0, NULL, NULL, NULL);
	assert_eq (ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_remove_device_running_changed_cb_p
 * @since_tizen		5.0
 * @description		Removes the callback function which is called when the state of a sound device was changed
 *				- Add the device connected callback before removing the callback
 */
int utc_media_sound_manager_remove_device_running_changed_cb_p(void)
{
	int ret;
	int cb_id;

	ret = sound_manager_add_device_running_changed_cb(SOUND_DEVICE_ALL_MASK, _sound_device_running_changed_cb, NULL, &cb_id);
	assert_eq (ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_remove_device_running_changed_cb(cb_id);
	assert_eq (ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_remove_device_running_changed_cb_n
 * @since_tizen		5.0
 * @description		Removes the callback function which is called when the state of a sound device was changed
 *				- Remove the callback without adding callback to get negative result
 */
int utc_media_sound_manager_remove_device_running_changed_cb_n(void)
{
	int ret = sound_manager_remove_device_running_changed_cb(-1);
	assert_eq (ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}
