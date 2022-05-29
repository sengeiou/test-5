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
#include <math.h>

//& set: Soundmanager

#define GET_LIST_N_GET_FIRST_DATA(list, device, ret) do { \
	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list); \
	if (ret == SOUND_MANAGER_ERROR_NO_DATA) \
		return 0; \
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE); \
	ret = sound_manager_get_next_device(list, &device); \
	/* ret can't be NO_DATA as return of get_device_list() is not NO_DATA */ \
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE); \
} while (0)

#define GET_LIST_N_GET_USB_OUTPUT_DEVICE(list, device, ret) do { \
	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list); \
	if (ret == SOUND_MANAGER_ERROR_NO_DATA) \
		return 0; \
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE); \
	while (!(ret = sound_manager_get_next_device(list, &device))) { \
		sound_device_type_e type; \
		sound_device_io_direction_e direction; \
		if (!(ret = sound_manager_get_device_type(device, &type)) && (type == SOUND_DEVICE_USB_AUDIO)) \
			if (!(ret = sound_manager_get_device_io_direction(device, &direction)) && (direction == SOUND_DEVICE_IO_DIRECTION_OUT)) \
				break; \
	} \
	if (ret == SOUND_MANAGER_ERROR_NONE) { \
		/* found */ \
	} else if (ret == SOUND_MANAGER_ERROR_NO_DATA) { \
		/* nomarl operation */ \
		return 0; \
	} else { \
		/* error */ \
		return 1; \
	} \
} while (0)

static void _sound_stream_focus_state_changed_cb(sound_stream_info_h stream_info, sound_stream_focus_mask_e focus_mask, sound_stream_focus_state_e focus_state, 
                                                 sound_stream_focus_change_reason_e reason_for_change, int sound_behaviors, const char *additional_info, void *user_data)
{
}

/**
 * @testcase		utc_media_sound_manager_get_max_volume_p1
 * @since_tizen		2.3
 * @description		Gets the maximum volume level supported for the system sound type
 */
int utc_media_sound_manager_get_max_volume_p1(void)
{
    int ret, max;

    ret = sound_manager_get_max_volume(SOUND_TYPE_SYSTEM, &max);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_media_sound_manager_get_max_volume_p2
 * @since_tizen     2.3
 * @description     Gets the maximum volume level supported for the media sound type
 */
int utc_media_sound_manager_get_max_volume_p2(void)
{
    int ret, max;

    ret = sound_manager_get_max_volume(SOUND_TYPE_MEDIA, &max);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_media_sound_manager_get_max_volume_p3
 * @since_tizen     2.3
 * @description     Gets the maximum volume level supported for the alarm sound type
 */
int utc_media_sound_manager_get_max_volume_p3(void)
{
    int ret, max;

    ret = sound_manager_get_max_volume(SOUND_TYPE_ALARM, &max);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_media_sound_manager_get_max_volume_p4
 * @since_tizen     2.3
 * @description     Gets the maximum volume level supported for the notification sound type
 */
int utc_media_sound_manager_get_max_volume_p4(void)
{
    int ret, max;

    ret = sound_manager_get_max_volume(SOUND_TYPE_NOTIFICATION, &max);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_get_max_volume_n
 * @since_tizen		2.3
 * @description		Gets the maximum volume level supported for a particular sound type
 *				- Pass invalid sound type to get negative result
 */
int utc_media_sound_manager_get_max_volume_n(void)
{
    int ret, max;

    ret = sound_manager_get_max_volume(SOUND_TYPE_SYSTEM-1, &max);
    assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_set_volume_p
 * @since_tizen		2.3
 * @description		Sets the volume level specified for a particular sound type
 *				- Get max volume of the sound type\n
 *				- Pass the proper volume level of the sound type
 */
int utc_media_sound_manager_set_volume_p(void)
{
    int ret, max;

    ret = sound_manager_get_max_volume(SOUND_TYPE_SYSTEM, &max);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_set_volume(SOUND_TYPE_NOTIFICATION, max/2);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_set_volume_n1
 * @since_tizen		2.3
 * @description		Sets the volume level specified for a particular sound type
 *				- Pass invalid sound type to get negative result
 */
int utc_media_sound_manager_set_volume_n1(void)
{
    int ret;

    ret = sound_manager_set_volume(SOUND_TYPE_SYSTEM-1, 10);
    assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_set_volume_n2
 * @since_tizen		2.3
 * @description		Sets the volume level specified for a particular sound type
 *				- Pass invalid volume level to get negative result
 */
int utc_media_sound_manager_set_volume_n2(void)
{
    int ret;

    ret = sound_manager_set_volume(SOUND_TYPE_SYSTEM, -1);
    assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_get_volume_p
 * @since_tizen		2.3
 * @description		Gets the volume level specified for a particular sound type
 *				- Set volume level for a particular sound type\n
 *				- Get and verify the volume level
 */
int utc_media_sound_manager_get_volume_p(void)
{
    int ret, vol;

    ret = sound_manager_set_volume(SOUND_TYPE_ALARM, 10);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_get_volume(SOUND_TYPE_ALARM, &vol);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    assert_eq(10, vol);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_get_volume_n1
 * @since_tizen		2.3
 * @description		Gets the volume level specified for a particular sound type
 *				 - Pass invalid parameter to get negative result
 */
int utc_media_sound_manager_get_volume_n1(void)
{
    int ret;

    ret = sound_manager_get_volume(SOUND_TYPE_ALARM, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_get_volume_n2
 * @since_tizen		2.3
 * @description		Gets the volume level specified for a particular sound type
 *				- Pass invalid invalid sound type to get negative result
 */
int utc_media_sound_manager_get_volume_n2(void)
{
    int ret, vol;

    ret = sound_manager_get_volume(SOUND_TYPE_SYSTEM-1, &vol);
    assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_get_current_sound_type_p
 * @since_tizen		2.3
 * @description		Gets the type of the sound being currently played
 *				- Get and verify the sound type
 */
int utc_media_sound_manager_get_current_sound_type_p(void)
{
    sound_type_e type;
    int ret;

    ret = sound_manager_get_current_sound_type(&type);
    assert (ret == SOUND_MANAGER_ERROR_NONE || ret == SOUND_MANAGER_ERROR_NO_PLAYING_SOUND);

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_get_current_sound_type_n
 * @since_tizen		2.3
 * @description		Gets the type of the sound being currently played
 *				- Pass invalid parameter to get negative result
 */
int utc_media_sound_manager_get_current_sound_type_n(void)
{
    int ret;

    ret = sound_manager_get_current_sound_type(NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_sound_manager_get_device_list_p
 * @since_tizen		2.3
 * @description		Gets the list consisting of connected devices
 */
int utc_sound_manager_get_device_list_p(void)
{
	int ret;
	sound_device_list_h list;

	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	if (ret == SOUND_MANAGER_ERROR_NO_DATA)
		return 0;
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_device_list_n
 * @since_tizen		2.3
 * @description		Gets the list consisting of connected devices
 *				- Pass invalid devie mask to get negative result
 */
int utc_sound_manager_get_device_list_n(void)
{
	int ret;
	sound_device_list_h list;

	ret = sound_manager_get_device_list(0, &list);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_next_device_p
 * @since_tizen		2.3
 * @description		Gets the next item of the device list
 *				- Get current device list before getting next device handle
 */
int utc_sound_manager_get_next_device_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_next_device_n
 * @since_tizen		2.3
 * @description		Gets the next item of the device list
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_next_device_n(void)
{
	int ret;
	sound_device_list_h list;

	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	if (ret == SOUND_MANAGER_ERROR_NO_DATA)
		return 0;
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_next_device(list, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_prev_device_p
 * @since_tizen		2.3
 * @description		Gets the previous item of the device list
 *				- Get current device list\n
 *				- Get next device handle\n
 *				- Get and verify the previous device handle
 */
int utc_sound_manager_get_prev_device_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device_fst;
	sound_device_h device_sec;
	sound_device_h device;

	/* Get List */
	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	if(ret == SOUND_MANAGER_ERROR_NO_DATA)
		return 0;
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	/* Get First : Must exists as return of get_device_list() is not NO_DATA */
	ret = sound_manager_get_next_device(list, &device_fst);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	/* Get Second */
	ret = sound_manager_get_next_device(list, &device_sec);
	if (ret == SOUND_MANAGER_ERROR_NO_DATA) {
		/* No Second : only one data exists, prev must be NO_DATA */
		ret = sound_manager_get_prev_device(list, &device);
		assert_eq(ret, SOUND_MANAGER_ERROR_NO_DATA);
	} else {
		/* more than one data exists, prev must be actual previous data */
		assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
		ret = sound_manager_get_prev_device(list, &device);
		assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
		assert_eq(device, device_fst);
	}

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_prev_device_n
 * @since_tizen		2.3
 * @description		Gets the previous item of the device list
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_prev_device_n(void)
{
	int ret;
	sound_device_list_h list;

	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	if(ret == SOUND_MANAGER_ERROR_NO_DATA)
		return 0;
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_get_prev_device(list, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_device_type_p
 * @since_tizen		2.3
 * @description		Gets the type of the device
 *				- Get current device list\n
 *				- Get device handle from the device list\n
 *				- Get device type from the device handle
 */
int utc_sound_manager_get_device_type_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_device_type_e type;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_get_device_type(device, &type);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_device_type_n
 * @since_tizen		2.3
 * @description		Gets the type of the device
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_device_type_n(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_device_type_e type;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_get_device_type(NULL, &type);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_device_io_direction_p
 * @since_tizen		2.3
 * @description		Gets the io direction of the device
 *				- Get current device list\n
 *				- Get device handle from the device list\n
 *				- Get device io direction from the device handle
 */
int utc_sound_manager_get_device_io_direction_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_device_io_direction_e direction;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_get_device_io_direction(device, &direction);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_device_io_direction_n
 * @since_tizen		2.3
 * @description		Gets the io direction of the device
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_device_io_direction_n(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_device_io_direction_e direction;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_get_device_io_direction(NULL, &direction);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_device_id_p
 * @since_tizen		2.3
 * @description		Gets the id of the device
 *				- Get current device list\n
 *				- Get device handle from the device list\n
 *				- Get device id from the device handle
 */
int utc_sound_manager_get_device_id_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	int id;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_get_device_id(device, &id);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_device_id_n
 * @since_tizen		2.3
 * @description		Gets the id of the device
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_device_id_n(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	int id;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_get_device_id(NULL, &id);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_device_name_p
 * @since_tizen		2.3
 * @description		Gets the name of the device
 *				- Get current device list\n
 *				- Get device handle from the device list\n
 *				- Get device name from the device handle
 */
int utc_sound_manager_get_device_name_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	char *name;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_get_device_name(device, &name);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_device_name_n
 * @since_tizen		2.3
 * @description		Gets the name of the device
 *				- pass invalid parameter to get negative result
 */
int utc_sound_manager_get_device_name_n(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	char *name;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_get_device_name(NULL, &name);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_is_device_running_p
 * @since_tizen		5.0
 * @description		Gets the state of the device
 *				- Get current device list\n
 *				- Get device handle from the device list\n
 *				- Get device state from the device handle
 */
int utc_sound_manager_is_device_running_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	bool is_running;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_is_device_running(device, &is_running);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_is_device_running_n
 * @since_tizen		5.0
 * @description		Gets the state of the device
 *				- pass invalid parameter to get negative result
 */
int utc_sound_manager_is_device_running_n(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	bool is_running;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_is_device_running(NULL, &is_running);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_device_state_p
 * @since_tizen		2.3
 * @description		Gets the state of the device
 *				- Get current device list\n
 *				- Get device handle from the device list\n
 *				- Get device state from the device handle
 */
int utc_sound_manager_get_device_state_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_device_state_e state;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_get_device_state(device, &state);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_device_state_n
 * @since_tizen		2.3
 * @description		Gets the state of the device
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_device_state_n(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_device_state_e state;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_get_device_state(NULL, &state);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_free_device_list_p
 * @since_tizen		3.0
 * @description		Destroys the device list
 *				- Get current device list\n
 *				- Frees the device list
 */
int utc_sound_manager_free_device_list_p(void)
{
	int ret;
	sound_device_list_h list;

	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	if (ret == SOUND_MANAGER_ERROR_NO_DATA)
		return 0;
	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_free_device_list_n
 * @since_tizen		3.0
 * @description		Destroys the device list
 *				- Pass invalid paramter to get negative result
 */
int utc_sound_manager_free_device_list_n(void)
{
	int ret;

	ret = sound_manager_free_device_list(NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_supported_sample_formats_p
 * @since_tizen		5.0
 * @description		Gets supported sample format list
 *				- Find USB output device before getting the supported sample formats
 */
int utc_sound_manager_get_supported_sample_formats_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_sample_format_e *formats = NULL;
	unsigned int num;

	GET_LIST_N_GET_USB_OUTPUT_DEVICE(list, device, ret);

	ret = sound_manager_get_supported_sample_formats(device, &formats, &num);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	free(formats);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_supported_sample_formats_n1
 * @since_tizen		5.0
 * @description		Gets supported sample format list
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_supported_sample_formats_n1(void)
{
	int ret;
	sound_sample_format_e *formats = NULL;
	unsigned int num;

	ret = sound_manager_get_supported_sample_formats(NULL, &formats, &num);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_supported_sample_formats_n2
 * @since_tizen		5.0
 * @description		Gets supported sample format list
 *				- Pass invalid device to get negative result
 */
int utc_sound_manager_get_supported_sample_formats_n2(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_sample_format_e *formats = NULL;
	unsigned int num;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_get_supported_sample_formats(device, &formats, &num);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_OPERATION);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_sample_format_p
 * @since_tizen		5.0
 * @description		Gets the current sample format
 *				- Find USB output device before getting the current sample format
 */
int utc_sound_manager_get_sample_format_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_sample_format_e format;

	GET_LIST_N_GET_USB_OUTPUT_DEVICE(list, device, ret);

	ret = sound_manager_get_sample_format(device, &format);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_sample_format_n
 * @since_tizen		5.0
 * @description		Gets the current sample format
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_sample_format_n(void)
{
	int ret;
	sound_sample_format_e format;

	ret = sound_manager_get_sample_format(NULL, &format);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_sound_manager_set_sample_format_p
 * @since_tizen		5.0
 * @description		Sets sample format
 *				- Find USB output device before setting the sample format
 */
int utc_sound_manager_set_sample_format_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_sample_format_e *formats = NULL;
	unsigned int num;

	GET_LIST_N_GET_USB_OUTPUT_DEVICE(list, device, ret);

	ret = sound_manager_get_supported_sample_formats(device, &formats, &num);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_set_sample_format(device, formats[0]);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	free(formats);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/*
 * @testcase		utc_sound_manager_set_sample_format_n
 * @since_tizen		5.0
 * @description		Sets sample format
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_set_sample_format_n(void)
{
	int ret;
	sound_sample_format_e format = SOUND_SAMPLE_FORMAT_S16_LE;

	ret = sound_manager_set_sample_format(NULL, format);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_supported_sample_rates_p
 * @since_tizen		5.0
 * @description		Gets supported sample rate list
 *				- Find USB output device before getting the supported sample rates
 */
int utc_sound_manager_get_supported_sample_rates_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_sample_rate_e *rates = NULL;
	unsigned int num;

	GET_LIST_N_GET_USB_OUTPUT_DEVICE(list, device, ret);

	ret = sound_manager_get_supported_sample_rates(device, &rates, &num);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	if (rates)
		free(rates);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_supported_sample_rates_n
 * @since_tizen		5.0
 * @description		Gets supported sample rate list
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_supported_sample_rates_n(void)
{
	int ret;
	sound_sample_rate_e *rates = NULL;
	unsigned int num;

	ret = sound_manager_get_supported_sample_rates(NULL, &rates, &num);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_sample_rate_p
 * @since_tizen		5.0
 * @description		Gets the current sample rate
 *				- Find USB output device before getting the current sample rate
 */
int utc_sound_manager_get_sample_rate_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_sample_rate_e rate;

	GET_LIST_N_GET_USB_OUTPUT_DEVICE(list, device, ret);

	ret = sound_manager_get_sample_rate(device, &rate);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_sample_rate_n
 * @since_tizen		5.0
 * @description		Gets the current sample rate
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_sample_rate_n(void)
{
	int ret;
	sound_sample_rate_e rate;

	ret = sound_manager_get_sample_rate(NULL, &rate);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_sound_manager_set_sample_rate_p
 * @since_tizen		5.0
 * @description		Sets sample rate
 *				- Find USB output device before setting the sample rate
 */
int utc_sound_manager_set_sample_rate_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	sound_sample_rate_e *rates = NULL;
	unsigned int num;

	GET_LIST_N_GET_USB_OUTPUT_DEVICE(list, device, ret);

	ret = sound_manager_get_supported_sample_rates(device, &rates, &num);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_set_sample_rate(device, rates[0]);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	free(rates);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/*
 * @testcase		utc_sound_manager_set_sample_rate_n
 * @since_tizen		5.0
 * @description		Sets sample rate
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_set_sample_rate_n(void)
{
	int ret;
	sound_sample_rate_e rate = SOUND_SAMPLE_RATE_44100;

	ret = sound_manager_set_sample_rate(NULL, rate);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_media_stream_only_p
 * @since_tizen		5.0
 * @description		Gets the value of 'media stream only' property
 *				- Find USB output device before getting the 'media stream only'
 */
int utc_sound_manager_get_media_stream_only_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	bool enabled;

	GET_LIST_N_GET_USB_OUTPUT_DEVICE(list, device, ret);

	ret = sound_manager_get_media_stream_only(device, &enabled);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_media_stream_only_n
 * @since_tizen		5.0
 * @description		Gets the value of 'media stream only' property
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_media_stream_only_n(void)
{
	int ret;
	bool enabled;

	ret = sound_manager_get_media_stream_only(NULL, &enabled);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_sound_manager_set_media_stream_only_p
 * @since_tizen		5.0
 * @description		Sets the value of 'media stream only' property
 *				- Find USB output device before setting the 'media stream only'
 */
int utc_sound_manager_set_media_stream_only_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;

	GET_LIST_N_GET_USB_OUTPUT_DEVICE(list, device, ret);

	ret = sound_manager_set_media_stream_only(device, false);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_set_media_stream_only_n
 * @since_tizen		5.0
 * @description		Sets the value of 'media stream only' property
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_set_media_stream_only_n(void)
{
	int ret;

	ret = sound_manager_set_media_stream_only(NULL, false);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_avoid_resampling_p
 * @since_tizen		5.0
 * @description		Gets the value of 'avoid resampling' property
 *				- Find USB output device before getting the 'avoid resampling'
 */
int utc_sound_manager_get_avoid_resampling_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;
	bool enabled;

	GET_LIST_N_GET_USB_OUTPUT_DEVICE(list, device, ret);

	ret = sound_manager_get_avoid_resampling(device, &enabled);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_avoid_resampling_n
 * @since_tizen		5.0
 * @description		Gets the value of 'avoid resampling' property
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_avoid_resampling_n(void)
{
	int ret;
	bool enabled;

	ret = sound_manager_get_avoid_resampling(NULL, &enabled);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_sound_manager_set_avoid_resampling_p
 * @since_tizen		5.0
 * @description		Sets the value of 'avoid resampling' property
 *				- Find USB output device before setting the 'avoid resampling'
 */
int utc_sound_manager_set_avoid_resampling_p(void)
{
	int ret;
	sound_device_list_h list;
	sound_device_h device;

	GET_LIST_N_GET_USB_OUTPUT_DEVICE(list, device, ret);

	ret = sound_manager_set_avoid_resampling(device, false);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_set_avoid_resampling_n
 * @since_tizen		5.0
 * @description		Sets the value of 'avoid resampling' property
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_set_avoid_resampling_n(void)
{
	int ret;

	ret = sound_manager_set_avoid_resampling(NULL, false);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_sound_manager_create_stream_information_p
 * @since_tizen		3.0
 * @description		Creates a handle for stream information
 */
int utc_sound_manager_create_stream_information_p(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	if (!stream_info)
		return 1;
	else
		sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase		utc_sound_manager_create_stream_information_n
 * @since_tizen		3.0
 * @description		Creates a handle for stream information
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_create_stream_information_n(void)
{
	int ret;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_sound_manager_destroy_stream_information_p
 * @since_tizen		3.0
 * @description		Destroys the handle for stream information
 *				- Create stream info handle\n
 *				- Pass stream info handle to destroy
 */
int utc_sound_manager_destroy_stream_information_p(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_destroy_stream_information(stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_destroy_stream_information_n
 * @since_tizen		3.0
 * @description		Destroys the handle for stream information
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_destroy_stream_information_n(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_destroy_stream_information(NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase		utc_sound_manager_add_device_for_stream_routing_p
 * @since_tizen		3.0
 * @description		Adds the device to the stream information for the stream routing
 *				- Create stream info handle\n
 *				- Get current device list\n
 *				- Get device handle from the device list\n
 *				- Add device handle to stream info handle
 */
int utc_sound_manager_add_device_for_stream_routing_p(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_device_list_h list;
	sound_device_h device;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_next_device(list, &device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_add_device_for_stream_routing(stream_info, device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_destroy_stream_information(stream_info);
	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_add_device_for_stream_routing_n1
 * @since_tizen		3.0
 * @description		Adds the device to the stream information for the stream routing
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_add_device_for_stream_routing_n1(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_device_list_h list;
	sound_device_h device;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_next_device(list, &device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_add_device_for_stream_routing(stream_info, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	sound_manager_destroy_stream_information(stream_info);
	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_add_device_for_stream_routing_n2
 * @since_tizen		3.0
 * @description		Adds the device to the stream information for the stream routing
 *				- Adds device hande for improper stream to get negative result
 */
int utc_sound_manager_add_device_for_stream_routing_n2(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_device_list_h list;
	sound_device_h device;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_next_device(list, &device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_add_device_for_stream_routing(stream_info, device);
	assert_eq(ret, SOUND_MANAGER_ERROR_POLICY);
	sound_manager_destroy_stream_information(stream_info);
	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_sound_manager_add_device_for_stream_routing_n3
 * @since_tizen     3.0
 * @description     Adds the device to the stream information for the stream routing
 *              - Adds the device twice to get negative result
 */
int utc_sound_manager_add_device_for_stream_routing_n3(void)
{
    int ret;
    sound_stream_info_h stream_info;
    sound_device_list_h list;
    sound_device_h device;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_get_next_device(list, &device);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_add_device_for_stream_routing(stream_info, device);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_add_device_for_stream_routing(stream_info, device);
    assert_eq(ret, SOUND_MANAGER_ERROR_POLICY);
    sound_manager_destroy_stream_information(stream_info);
    ret = sound_manager_free_device_list(list);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_sound_manager_remove_device_for_stream_routing_p
 * @since_tizen		3.0
 * @description		Removes the device to the stream information for the stream routing
 *				- Create stream info handle\n
 *				- Get current device list\n
 *				- Get device handle from the device list\n
 *				- Add device handle to stream info handle\n
 *				- Remove device handle from stream info handle
 */
int utc_sound_manager_remove_device_for_stream_routing_p(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_device_list_h list;
	sound_device_h device;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_next_device(list, &device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_add_device_for_stream_routing(stream_info, device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_remove_device_for_stream_routing(stream_info, device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_destroy_stream_information(stream_info);
	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_remove_device_for_stream_routing_n
 * @since_tizen		3.0
 * @description		Removes the device to the stream information for the stream routing
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_remove_device_for_stream_routing_n(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_device_list_h list;
	sound_device_h device;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_next_device(list, &device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_add_device_for_stream_routing(stream_info, device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_remove_device_for_stream_routing(stream_info, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	sound_manager_destroy_stream_information(stream_info);
	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_remove_all_devices_for_stream_routing_p
 * @since_tizen		4.0
 * @description		Removes all the devices from the stream information for the stream routing
 *				- Create stream info handle\n
 *				- Get current device list\n
 *				- Get device handle from the device list\n
 *				- Add device handle to stream info handle\n
 *				- Remove device handle from stream info handle
 */
int utc_sound_manager_remove_all_devices_for_stream_routing_p(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_device_list_h list;
	sound_device_h device;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_next_device(list, &device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_add_device_for_stream_routing(stream_info, device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_remove_all_devices_for_stream_routing(stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_destroy_stream_information(stream_info);
	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_remove_all_devices_for_stream_routing_n
 * @since_tizen		4.0
 * @description		Removes all the devices from the stream information for the stream routing
 *				- Pass stream info of MEDIA type that should return policy error
 */
int utc_sound_manager_remove_all_devices_for_stream_routing_n(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_remove_all_devices_for_stream_routing(stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_POLICY);
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase		utc_sound_manager_apply_stream_routing_p
 * @since_tizen		3.0
 * @description		Applies the stream routing
 *				- Create stream info handle\n
 *				- Get current device list\n
 *				- Get device handle from the device list\n
 *				- Add device handle to stream info handle\n
 *				- Apply stream routing
 */
int utc_sound_manager_apply_stream_routing_p(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_device_list_h list;
	sound_device_h device;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_next_device(list, &device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_add_device_for_stream_routing(stream_info, device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_apply_stream_routing(stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_destroy_stream_information(stream_info);
	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_apply_stream_routing_n
 * @since_tizen		3.0
 * @description		Applies the stream routing
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_apply_stream_routing_n(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_device_list_h list;
	sound_device_h device;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_next_device(list, &device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_add_device_for_stream_routing(stream_info, device);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_apply_stream_routing(NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	sound_manager_destroy_stream_information(stream_info);
	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_set_stream_preferred_device_p
 * @since_tizen		5.5
 * @description		Sets preferred built-in device
 *				- Create stream info handle\n
 *				- Get current device list\n
 *				- Get device handle from the device list\n
 *				- Find buit-in speaker or built-in mic device handle\n
 *				- Set the device handle as preferred device\n
 */
int utc_sound_manager_set_stream_preferred_device_p(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_device_list_h list;
	sound_device_h device;
	sound_device_type_e type;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_device_list(SOUND_DEVICE_TYPE_INTERNAL_MASK, &list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	while (!(ret = sound_manager_get_next_device(list, &device))) {
		if (!(ret = sound_manager_get_device_type(device, &type))) {
			 if (type == SOUND_DEVICE_BUILTIN_SPEAKER) {
				ret = sound_manager_set_stream_preferred_device(stream_info, SOUND_DEVICE_IO_DIRECTION_OUT, device);
				assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
			 } else if (type == SOUND_DEVICE_BUILTIN_MIC) {
				ret = sound_manager_set_stream_preferred_device(stream_info, SOUND_DEVICE_IO_DIRECTION_IN, device);
				assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
			 }
		}
	}

	ret = sound_manager_destroy_stream_information(stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_set_stream_preferred_device_n
 * @since_tizen		5.5
 * @description		Sets preferred built-in device
 *  			- Create stream info handle that is only for external device\n
 *				- Pass the stream info handle to get policy error
 */
int utc_sound_manager_set_stream_preferred_device_n(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA_EXTERNAL_ONLY, NULL, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_set_stream_preferred_device(stream_info, SOUND_DEVICE_IO_DIRECTION_OUT, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_POLICY);

	ret = sound_manager_destroy_stream_information(stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_stream_preferred_device_p
 * @since_tizen		5.5
 * @description		Gets preferred built-in device
 *				- Create stream info handle\n
 *				- Get current device list\n
 *				- Get device handle from the device list\n
 *				- Find buit-in speaker or built-in mic device handle\n
 *				- Set the device handle as preferred device\n
 *				- Get the preferred device\n
 */
int utc_sound_manager_get_stream_preferred_device_p(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_device_list_h list;
	sound_device_h device;
	int set_in_device_id = 0;
	int set_out_device_id = 0;
	int in_device_id = 0;
	int out_device_id = 0;
	sound_device_type_e type;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_device_list(SOUND_DEVICE_TYPE_INTERNAL_MASK, &list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	while (!(ret = sound_manager_get_next_device(list, &device))) {
		if (!(ret = sound_manager_get_device_type(device, &type))) {
			 if (type == SOUND_DEVICE_BUILTIN_SPEAKER) {
				ret = sound_manager_set_stream_preferred_device(stream_info, SOUND_DEVICE_IO_DIRECTION_OUT, device);
				assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
				ret = sound_manager_get_device_id(device, &set_out_device_id);
				assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
			 } else if (type == SOUND_DEVICE_BUILTIN_MIC) {
				ret = sound_manager_set_stream_preferred_device(stream_info, SOUND_DEVICE_IO_DIRECTION_IN, device);
				assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
				ret = sound_manager_get_device_id(device, &set_in_device_id);
				assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
			 }
		}
	}

	ret = sound_manager_get_stream_preferred_device(stream_info, &in_device_id, &out_device_id);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	if (in_device_id != SOUND_MANAGER_STREAM_NO_PREFERRED_DEVICE)
		assert_eq(in_device_id, set_in_device_id);

	if (out_device_id != SOUND_MANAGER_STREAM_NO_PREFERRED_DEVICE)
		assert_eq(out_device_id, set_out_device_id);

	ret = sound_manager_destroy_stream_information(stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_stream_preferred_device_n
 * @since_tizen		5.5
 * @description		Gets preferred built-in device
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_get_stream_preferred_device_n(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_get_stream_preferred_device(stream_info, NULL, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	ret = sound_manager_destroy_stream_information(stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_sound_manager_acquire_focus_p
 * @since_tizen		3.0
 * @description		Acquires the stream focus
 *				- Create stream info handle\n
 *				- Acquire focus using created stream info handle
 */
int utc_sound_manager_acquire_focus_p(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase		utc_sound_manager_acquire_focus_n1
 * @since_tizen		3.0
 * @description		Acquires the stream focus
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_acquire_focus_n1(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK -1, SOUND_BEHAVIOR_NONE, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase        utc_sound_manager_acquire_focus_n2
 * @since_tizen     3.0
 * @description     Acquires the stream focus
 *              - Try to acquire focus without passing callback function pointer
 */
int utc_sound_manager_acquire_focus_n2(void)
{
    int ret;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_POLICY);
    sound_manager_destroy_stream_information(stream_info);

    return 0;
}

/**
 * @testcase		utc_sound_manager_release_focus_p
 * @since_tizen		3.0
 * @description		Releases the acquired focus
 *				- Create stream info handle\n
 *				- Acquire focus using created stream info handle\n
 *				- Release the focus
 */
int utc_sound_manager_release_focus_p(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_release_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase		utc_sound_manager_release_focus_n1
 * @since_tizen		3.0
 * @description		Releases the acquired focus
 *				- Pass invalid parameter to get negative result
 */
int utc_sound_manager_release_focus_n1(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_release_focus(NULL, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase		utc_sound_manager_release_focus_n2
 * @since_tizen		3.0
 * @description		Releases the acquired focus
 *				- Acquire focus with a Particular focus type\n
 *				- Release focus with a different focus type from acquired to get negative result 
 */
int utc_sound_manager_release_focus_n2(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_release_focus(stream_info, SOUND_STREAM_FOCUS_FOR_RECORDING, SOUND_BEHAVIOR_NONE, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_STATE);
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase        utc_sound_manager_acquire_focus_all_p
 * @since_tizen     4.0
 * @description     Acquires all the stream focuses
 *              - Create stream info handle\n
 *              - Acquire playback focus\n
 *              - Acquire all focuses using created stream info handle
 */
int utc_sound_manager_acquire_focus_all_p(void)
{
    int ret;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_acquire_focus_all(stream_info, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    sound_manager_destroy_stream_information(stream_info);

    return 0;
}

/**
 * @testcase        utc_sound_manager_acquire_focus_all_n1
 * @since_tizen     4.0
 * @description     Acquires all the stream focuses
 *              - Pass invalid parameter to get negative result
 */
int utc_sound_manager_acquire_focus_all_n1(void)
{
    int ret;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_acquire_focus_all(NULL, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
    sound_manager_destroy_stream_information(stream_info);

    return 0;
}

/**
 * @testcase        utc_sound_manager_acquire_focus_all_n2
 * @since_tizen     4.0
 * @description     Acquires all the stream focuses
 *              - Try to acquire focus without passing callback function pointer
 */
int utc_sound_manager_acquire_focus_all_n2(void)
{
    int ret;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_acquire_focus_all(stream_info, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_POLICY);
    sound_manager_destroy_stream_information(stream_info);

    return 0;
}

/**
 * @testcase        utc_sound_manager_release_focus_all_p
 * @since_tizen     4.0
 * @description     Releases all the acquired focuses
 *              - Create stream info handle\n
 *              - Acquire focus using created stream info handle\n
 *              - Release all the focuses
 */
int utc_sound_manager_release_focus_all_p(void)
{
    int ret;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_release_focus_all(stream_info, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    sound_manager_destroy_stream_information(stream_info);

    return 0;
}

/**
 * @testcase        utc_sound_manager_release_focus_all_n
 * @since_tizen     4.0
 * @description     Releases all the acquired focuses
 *              - Pass invalid parameter to get negative result
 */
int utc_sound_manager_release_focus_all_n(void)
{
    int ret;
    sound_stream_info_h stream_info;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_release_focus_all(NULL, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
    sound_manager_destroy_stream_information(stream_info);

    return 0;
}

/**
 * @testcase        utc_sound_manager_deliver_focus_p
 * @since_tizen     4.0
 * @description     Deliver a focus to another stream info handle
 *              - Create stream info handle A and B\n
 *              - Acquire playback focus for stream info handle A\n
 *              - Deliver the focus from stream info handle A to handle B\n
 *              - Get focus state and destory handles
 */
int utc_sound_manager_deliver_focus_p(void)
{
    int ret;
    sound_stream_info_h stream_info_alarm;
    sound_stream_info_h stream_info_media;
    sound_stream_focus_state_e playback_focus_state;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_ALARM, _sound_stream_focus_state_changed_cb, NULL, &stream_info_alarm);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info_media);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = sound_manager_acquire_focus(stream_info_alarm, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = sound_manager_deliver_focus(stream_info_alarm, stream_info_media, SOUND_STREAM_FOCUS_FOR_PLAYBACK);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = sound_manager_get_focus_state(stream_info_alarm, &playback_focus_state, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    assert_eq(playback_focus_state, SOUND_STREAM_FOCUS_STATE_RELEASED);

    ret = sound_manager_get_focus_state(stream_info_media, &playback_focus_state, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    assert_eq(playback_focus_state, SOUND_STREAM_FOCUS_STATE_ACQUIRED);

    sound_manager_destroy_stream_information(stream_info_alarm);
    sound_manager_destroy_stream_information(stream_info_media);

    return 0;
}

/**
 * @testcase        utc_sound_manager_deliver_focus_n
 * @since_tizen     4.0
 * @description     Deliver a focus to another stream info handle
 *              - Create stream info handle A and B\n
 *              - Acquire playback focus for stream info handle A\n
 *              - Try to deliver recording focus from stream info handle A to handle B\n
 *              - Destory handles
 */
int utc_sound_manager_deliver_focus_n(void)
{
    int ret;
    sound_stream_info_h stream_info_alarm;
    sound_stream_info_h stream_info_media;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_ALARM, _sound_stream_focus_state_changed_cb, NULL, &stream_info_alarm);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info_media);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = sound_manager_acquire_focus(stream_info_alarm, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

    ret = sound_manager_deliver_focus(stream_info_alarm, stream_info_media, SOUND_STREAM_FOCUS_FOR_RECORDING);
    assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_STATE);

    sound_manager_destroy_stream_information(stream_info_alarm);
    sound_manager_destroy_stream_information(stream_info_media);

    return 0;
}

/**
 * @testcase		utc_sound_manager_get_focus_state_p
 * @since_tizen		3.0
 * @description		Gets the state of focus
 *				- Create stream info handle\n
 *				- Acquire focus using created stream info handle\n
 *				- Get the state of focus
 */
int utc_sound_manager_get_focus_state_p(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_stream_focus_state_e state_for_playback;
	sound_stream_focus_state_e state_for_recording;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_focus_state(stream_info, &state_for_playback, &state_for_recording);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	if (state_for_playback != SOUND_STREAM_FOCUS_STATE_ACQUIRED || state_for_recording != SOUND_STREAM_FOCUS_STATE_RELEASED) {
		sound_manager_destroy_stream_information(stream_info);
		return 1;
	}
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_focus_state_n
 * @since_tizen		3.0
 * @description		Gets the state of focus
 *				- Passing invalid parameter to get negative result
 */
int utc_sound_manager_get_focus_state_n(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_focus_state(stream_info, NULL, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase		utc_sound_manager_set_focus_reacquisition_p
 * @since_tizen		3.0
 * @description		Sets auto focus reacquisition property
 *				- Create stream info handle\n
 *				- Set auto focus reacquisition property
 */
int utc_sound_manager_set_focus_reacquisition_p(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_set_focus_reacquisition(stream_info, false);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase		utc_sound_manager_set_focus_reacquisition_n
 * @since_tizen		3.0
 * @description		Sets auto focus reacquisition property
 *				- Passing invalid parameter to get negative result
 */
int utc_sound_manager_set_focus_reacquisition_n(void)
{
	int ret;
	sound_stream_info_h stream_info;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_set_focus_reacquisition(NULL, false);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_focus_reacquisition_p
 * @since_tizen		3.0
 * @description		Gets auto focus reacquisition property
 * 				- Create stream info handle\n
 *				- Set auto focus reacquisition property\n
 *				- Get auto focus reacquisition property
 */
int utc_sound_manager_get_focus_reacquisition_p(void)
{
	int ret;
	sound_stream_info_h stream_info;
	bool enabled;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_set_focus_reacquisition(stream_info, false);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_focus_reacquisition(stream_info, &enabled);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	assert_eq(enabled, false);
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_focus_reacquisition_n
 * @since_tizen		3.0
 * @description		Gets auto focus reacquisition property
 *				- Passing invalid parameter to get negative result
 */
int utc_sound_manager_get_focus_reacquisition_n(void)
{
	int ret;
	sound_stream_info_h stream_info;
	bool enabled;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_set_focus_reacquisition(stream_info, false);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_focus_reacquisition(stream_info, NULL);
	assert_eq(ret ,SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	ret = sound_manager_get_focus_reacquisition(NULL, &enabled);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase		utc_sound_manager_get_sound_type_p1
 * @since_tizen		3.0
 * @description		Gets the sound type of the stream information
 *				- Create stream info handle\n
 *				- Get the sound type of the stream info handle
 */
int utc_sound_manager_get_sound_type_p1(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_type_e sound_type;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_sound_type(stream_info, &sound_type);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	if (sound_type > SOUND_TYPE_VOICE) {
		sound_manager_destroy_stream_information(stream_info);
		return 1;
	}
	sound_manager_destroy_stream_information(stream_info);

	return 0;
}

/**
 * @testcase        utc_sound_manager_get_sound_type_p2
 * @since_tizen     3.0
 * @description     Gets the sound type of the stream information
 *              - Create stream info handle\n
 *              - Get the sound type of the stream info handle
 */
int utc_sound_manager_get_sound_type_p2(void)
{
    int ret;
    sound_stream_info_h stream_info;
    sound_type_e sound_type;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_ALARM, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_get_sound_type(stream_info, &sound_type);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    if (sound_type > SOUND_TYPE_VOICE) {
        sound_manager_destroy_stream_information(stream_info);
        return 1;
    }
    sound_manager_destroy_stream_information(stream_info);

    return 0;
}

/**
 * @testcase        utc_sound_manager_get_sound_type_p3
 * @since_tizen     3.0
 * @description     Gets the sound type of the stream information
 *              - Create stream info handle\n
 *              - Get the sound type of the stream info handle
 */
int utc_sound_manager_get_sound_type_p3(void)
{
    int ret;
    sound_stream_info_h stream_info;
    sound_type_e sound_type;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOICE_INFORMATION, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_get_sound_type(stream_info, &sound_type);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    if (sound_type > SOUND_TYPE_VOICE) {
        sound_manager_destroy_stream_information(stream_info);
        return 1;
    }
    sound_manager_destroy_stream_information(stream_info);

    return 0;
}

/**
 * @testcase        utc_sound_manager_get_sound_type_p4
 * @since_tizen     3.0
 * @description     Gets the sound type of the stream information
 *              - Create stream info handle\n
 *              - Get the sound type of the stream info handle
 */
int utc_sound_manager_get_sound_type_p4(void)
{
    int ret;
    sound_stream_info_h stream_info;
    sound_type_e sound_type;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_get_sound_type(stream_info, &sound_type);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    if (sound_type > SOUND_TYPE_VOICE) {
        sound_manager_destroy_stream_information(stream_info);
        return 1;
    }
    sound_manager_destroy_stream_information(stream_info);

    return 0;
}

/**
 * @testcase		utc_sound_manager_get_sound_type_n
 * @since_tizen		3.0
 * @description		Gets the sound type of the stream information
 *				- Passing invalid parameter to get negative result
 */
int utc_sound_manager_get_sound_type_n(void)
{
	int ret;

	ret = sound_manager_get_sound_type(NULL, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_get_current_playback_focus_p1
 * @since_tizen		3.0
 * @description		Gets current playback focus
 *				- Create stream info handle\n
 *				- Acquire playback focus\n
 *				- Get the current playback focus
 */
int utc_media_sound_manager_get_current_playback_focus_p1(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_stream_focus_change_reason_e acquired_by;
	int sound_behavior;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_RINGTONE_VOIP, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_current_playback_focus(&acquired_by, &sound_behavior, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_destroy_stream_information(stream_info);
	if (acquired_by != SOUND_STREAM_FOCUS_CHANGED_BY_RINGTONE)
		return 1;

	return 0;
}

/**
 * @testcase        utc_media_sound_manager_get_current_playback_focus_p2
 * @since_tizen     3.0
 * @description     Gets current playback focus
 *              - Create stream info handle\n
 *              - Acquire playback focus\n
 *              - Get the current playback focus
 */
int utc_media_sound_manager_get_current_playback_focus_p2(void)
{
    int ret;
    sound_stream_info_h stream_info;
    sound_stream_focus_change_reason_e acquired_by;
    int sound_behavior;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA_EXTERNAL_ONLY, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_get_current_playback_focus(&acquired_by, &sound_behavior, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    sound_manager_destroy_stream_information(stream_info);
    if (acquired_by != SOUND_STREAM_FOCUS_CHANGED_BY_MEDIA_EXTERNAL_ONLY)
        return 1;

    return 0;
}

/**
 * @testcase        utc_media_sound_manager_get_current_playback_focus_p3
 * @since_tizen     3.0
 * @description     Gets current playback focus
 *              - Create stream info handle\n
 *              - Acquire playback focus\n
 *              - Get the current playback focus
 */
int utc_media_sound_manager_get_current_playback_focus_p3(void)
{
    int ret;
    sound_stream_info_h stream_info;
    sound_stream_focus_change_reason_e acquired_by;
    int sound_behavior;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_NOTIFICATION, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_get_current_playback_focus(&acquired_by, &sound_behavior, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    sound_manager_destroy_stream_information(stream_info);
    if (acquired_by != SOUND_STREAM_FOCUS_CHANGED_BY_NOTIFICATION)
        return 1;

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_get_current_playback_focus_n
 * @since_tizen		3.0
 * @description		Gets current playback focus
 *				- Passing invalid parameter to get the current playback focus
 */
int utc_media_sound_manager_get_current_playback_focus_n(void)
{
	int ret;
	sound_stream_focus_change_reason_e acquired_by;

	ret = sound_manager_get_current_playback_focus(&acquired_by, NULL, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_get_current_recording_focus_p1
 * @since_tizen		3.0
 * @description		Gets current recording focus
 *				- Create stream info handle\n
 *				- Acquire recording focus\n
 *				- Get the current recording focus
 */
int utc_media_sound_manager_get_current_recording_focus_p1(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_stream_focus_change_reason_e acquired_by;
	int sound_behavior;

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOICE_RECOGNITION, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_RECORDING, SOUND_BEHAVIOR_NONE, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	ret = sound_manager_get_current_recording_focus(&acquired_by, &sound_behavior, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	sound_manager_destroy_stream_information(stream_info);
	if (acquired_by != SOUND_STREAM_FOCUS_CHANGED_BY_VOICE_RECOGNITION)
		return 1;

	return 0;
}

/**
 * @testcase        utc_media_sound_manager_get_current_recording_focus_p2
 * @since_tizen     3.0
 * @description     Gets current recording focus
 *              - Create stream info handle\n
 *              - Acquire recording focus\n
 *              - Get the current recording focus
 */
int utc_media_sound_manager_get_current_recording_focus_p2(void)
{
    int ret;
    sound_stream_info_h stream_info;
    sound_stream_focus_change_reason_e acquired_by;
    int sound_behavior;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_RECORDING, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_get_current_recording_focus(&acquired_by, &sound_behavior, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    sound_manager_destroy_stream_information(stream_info);
    if (acquired_by != SOUND_STREAM_FOCUS_CHANGED_BY_VOIP)
        return 1;

    return 0;
}

/**
 * @testcase        utc_media_sound_manager_get_current_recording_focus_p3
 * @since_tizen     3.0
 * @description     Gets current recording focus
 *              - Create stream info handle\n
 *              - Acquire recording focus\n
 *              - Get the current recording focus
 */
int utc_media_sound_manager_get_current_recording_focus_p3(void)
{
    int ret;
    sound_stream_info_h stream_info;
    sound_stream_focus_change_reason_e acquired_by;
    int sound_behavior;

    ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, _sound_stream_focus_state_changed_cb, NULL, &stream_info);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_acquire_focus(stream_info, SOUND_STREAM_FOCUS_FOR_RECORDING, SOUND_BEHAVIOR_NONE, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    ret = sound_manager_get_current_recording_focus(&acquired_by, &sound_behavior, NULL);
    assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
    sound_manager_destroy_stream_information(stream_info);
    if (acquired_by != SOUND_STREAM_FOCUS_CHANGED_BY_MEDIA)
        return 1;

    return 0;
}

/**
 * @testcase		utc_media_sound_manager_get_current_recording_focus_n
 * @since_tizen		3.0
 * @description		Gets current recording focus
 *				- Passing invalid parameter to get the current recording focus
 */
int utc_media_sound_manager_get_current_recording_focus_n(void)
{
	int ret;
	sound_stream_focus_change_reason_e acquired_by;

	ret = sound_manager_get_current_recording_focus(&acquired_by, NULL, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_is_stream_on_device_p
 * @since_tizen		3.0
 * @description		Check whether stream is connected to given device or not
 *				- Passing proper parameter to check whether API returns no error.
 */
int utc_media_sound_manager_is_stream_on_device_p(void)
{
	int ret;
	sound_stream_info_h stream_info;
	sound_device_list_h list;
	sound_device_h device;
	bool is_on;

	GET_LIST_N_GET_FIRST_DATA(list, device, ret);

	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_is_stream_on_device(stream_info, device, &is_on);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_destroy_stream_information(stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_free_device_list(list);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_is_stream_on_device_n
 * @since_tizen		3.0
 * @description		Check whether stream is connected to given device or not
 *				- Passing invalid parameter to check whether API returns invalid parameter error.
 */
int utc_media_sound_manager_is_stream_on_device_n(void)
{
	int ret;

	ret = sound_manager_is_stream_on_device(NULL, NULL, NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_get_current_media_playback_device_type_p
 * @since_tizen		3.0
 * @description		Gets current media playback device type
 *				- Create stream info handle\n
 *				- Acquire recording focus\n
 *				- Get the current recording focus
 */
int utc_media_sound_manager_get_current_media_playback_device_type_p(void)
{
	int ret;
	sound_device_type_e device_type;
	sound_device_list_h list;

	ret = sound_manager_get_current_media_playback_device_type(&device_type);
	if (ret == SOUND_MANAGER_ERROR_NO_DATA) {
		/* check whether playback device exists, NO_DATA should be returnd also  */
		ret = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_OUT_MASK, &list);
		assert_eq(ret, SOUND_MANAGER_ERROR_NO_DATA);
	} else {
		assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_get_current_media_playback_device_type_n
 * @since_tizen		3.0
 * @description		Gets current media playback device type
 *				- Passing invalid parameter to check whether API returns invalid parameter error
 */
int utc_media_sound_manager_get_current_media_playback_device_type_n(void)
{
	int ret;

	ret = sound_manager_get_current_media_playback_device_type(NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_create_stream_ducking_p
 * @since_tizen		5.5
 * @description		Creates a handle for stream ducking
 */
int utc_media_sound_manager_create_stream_ducking_p(void)
{
	int ret;
	sound_stream_ducking_h stream_ducking;

	ret = sound_manager_create_stream_ducking(SOUND_STREAM_TYPE_MEDIA,
		NULL, NULL, &stream_ducking);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);
	if (!stream_ducking)
		return 1;

	sound_manager_destroy_stream_ducking(stream_ducking);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_create_stream_ducking_n
 * @since_tizen		5.5
 * @description		Creates a handle for stream ducking
 *				- Pass invalid parameter to get negative result
 */
int utc_media_sound_manager_create_stream_ducking_n(void)
{
	int ret;

	ret = sound_manager_create_stream_ducking(SOUND_STREAM_TYPE_MEDIA,
		NULL, NULL, NULL);

	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_is_ducked_p
 * @since_tizen		5.5
 * @description		Check whether stream is ducked or not
 *				- Passing proper parameter to check whether API returns no error.
 */
int utc_media_sound_manager_is_ducked_p(void)
{
	int ret;
	sound_stream_ducking_h stream_ducking;
	bool is_ducked;

	ret = sound_manager_create_stream_ducking(SOUND_STREAM_TYPE_MEDIA,
		NULL, NULL, &stream_ducking);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_is_ducked(stream_ducking, &is_ducked);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	sound_manager_destroy_stream_ducking(stream_ducking);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_is_ducked_n
 * @since_tizen		5.5
 * @description		Check whether stream is ducked or not
 *				- Passing invalid parameter to check whether API returns invalid parameter error.
 */
int utc_media_sound_manager_is_ducked_n(void)
{
	int ret;
	bool is_ducked;

	ret = sound_manager_is_ducked(NULL, &is_ducked);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_activate_ducking_p
 * @since_tizen		5.5
 * @description		Activates the stream ducking
 *				- Create stream ducking handle\n
 *				- Activates stream ducking using created stream ducking handle
 */
int utc_media_sound_manager_activate_ducking_p(void)
{
	int ret;
	sound_stream_ducking_h stream_ducking;

	ret = sound_manager_create_stream_ducking(SOUND_STREAM_TYPE_MEDIA,
		NULL, NULL, &stream_ducking);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_activate_ducking(stream_ducking, 500, 0.5);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	sound_manager_deactivate_ducking(stream_ducking);
	sound_manager_destroy_stream_ducking(stream_ducking);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_activate_ducking_n
 * @since_tizen		5.5
 * @description		Activates the stream ducking
 *				- Pass invalid parameter to get negative result
 */
int utc_media_sound_manager_activate_ducking_n(void)
{
	int ret;

	ret = sound_manager_activate_ducking(NULL, 500, 0.5);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_deactivate_ducking_p
 * @since_tizen		5.5
 * @description		Deactivates the stream ducking
 *				- Create stream ducking handle\n
 *				- Activates stream ducking using created stream ducking handle\n
 *				- Deactivates stream ducking using created stream ducking handle
 */
int utc_media_sound_manager_deactivate_ducking_p(void)
{
	int ret;
	sound_stream_ducking_h stream_ducking;

	ret = sound_manager_create_stream_ducking(SOUND_STREAM_TYPE_MEDIA,
		NULL, NULL, &stream_ducking);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_activate_ducking(stream_ducking, 500, 0.5);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_deactivate_ducking(stream_ducking);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	sound_manager_destroy_stream_ducking(stream_ducking);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_deactivate_ducking_n
 * @since_tizen		5.5
 * @description		Deactivates the stream ducking
 *				- Deactivates stream ducking without activation of it to get negative result
 */
int utc_media_sound_manager_deactivate_ducking_n(void)
{
	int ret;
	sound_stream_ducking_h stream_ducking;

	ret = sound_manager_create_stream_ducking(SOUND_STREAM_TYPE_MEDIA,
		NULL, NULL, &stream_ducking);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_deactivate_ducking(stream_ducking);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_STATE);

	sound_manager_destroy_stream_ducking(stream_ducking);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_destroy_stream_ducking_p
 * @since_tizen		5.5
 * @description		Destroys the handle for stream ducking
 *				- Create stream ducking handle\n
 *				- Pass stream ducking handle to destroy
 */
int utc_media_sound_manager_destroy_stream_ducking_p(void)
{
	int ret;
	sound_stream_ducking_h stream_ducking;

	ret = sound_manager_create_stream_ducking(SOUND_STREAM_TYPE_MEDIA,
		NULL, NULL, &stream_ducking);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	ret = sound_manager_destroy_stream_ducking(stream_ducking);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_sound_manager_destroy_stream_ducking_n
 * @since_tizen		5.5
 * @description		Destroys the handle for stream ducking
 *				- Pass invalid parameter to get negative result
 */
int utc_media_sound_manager_destroy_stream_ducking_n(void)
{
	int ret;

	ret = sound_manager_destroy_stream_ducking(NULL);
	assert_eq(ret, SOUND_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}
