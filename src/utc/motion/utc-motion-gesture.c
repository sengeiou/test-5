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
#include <stdio.h>
#include <gesture_recognition.h>
#include <system_info.h>

//& set: Motion - Gesture
static bool support = false;
static gesture_type_e gesture_type = GESTURE_SHAKE;
static gesture_h handle = NULL;
static bool is_supported = false;


//& purpose: Gesture callback function
static void gesture_cb(gesture_type_e gesture, const gesture_data_h data, double timestamp, gesture_error_e error, void *user_data)
{
}


/**
 * @function		utc_motion_gesture_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_motion_gesture_startup(void)
{
	system_info_get_platform_bool("http://tizen.org/feature/sensor.gesture_recognition", &is_supported);
	gesture_is_supported(gesture_type, &support);
	gesture_create(&handle);
}

/**
 * @function		utc_motion_gesture_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_motion_gesture_cleanup(void)
{
	if (handle) {
		gesture_release(handle);
		handle = NULL;
	}
}


//& purpose: Checks whether the given gesture is supported or not.
/**
 * @testcase		utc_motion_gesture_is_supported_p
 * @since_tizen		2.3
 * @description		Positive test case of motion_gesture_is_supported()
 */
int utc_motion_gesture_is_supported_p(void)
{
	int error = GESTURE_ERROR_NONE;
	bool s;

	error = gesture_is_supported(gesture_type, &s);
	if(is_supported)
	{
		assert(error == GESTURE_ERROR_NONE);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Checks whether it is supported with an invalid parameter
/**
 * @testcase		utc_motion_gesture_is_supported_n
 * @since_tizen		2.3
 * @description		Negative test case of motion_gesture_is_supported()
 */
int utc_motion_gesture_is_supported_n(void)
{
	int error = GESTURE_ERROR_NONE;

	error = gesture_is_supported(gesture_type, NULL);
	if(is_supported)
	{
		assert(error == GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}


//& purpose: Initializes a handle object for gesture recognition.
/**
 * @testcase		utc_motion_gesture_create_p
 * @since_tizen		2.3
 * @description		Positive test case of motion_gesture_create()
 */
int utc_motion_gesture_create_p(void)
{
	int error = GESTURE_ERROR_NONE;
	gesture_h h;

	error = gesture_create(&h);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_NONE);
		gesture_release(h);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//& purpose: Initializes a handle object with invalid parameter.
/**
 * @testcase		utc_motion_gesture_create_n
 * @since_tizen		2.3
 * @description		Negative test case of motion_gesture_create()
 */
int utc_motion_gesture_create_n(void)
{
	int error = GESTURE_ERROR_NONE;

	error = gesture_create(NULL);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Releases resources allocated for the handle.
/**
 * @testcase		utc_motion_gesture_release_p
 * @since_tizen		2.3
 * @description		Positive test case of motion_gesture_release()
 */
int utc_motion_gesture_release_p(void)
{
	int error = GESTURE_ERROR_NONE;
	gesture_h h;

	gesture_create(&h);

	error = gesture_release(h);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_NONE);
	}
	else
	{
		assert_eq(error ,GESTURE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Releases resources with an invalid parameter
/**
 * @testcase		utc_motion_gesture_release_n
 * @since_tizen		2.3
 * @description		Negative test case of motion_gesture_release()
 */
int utc_motion_gesture_release_n(void)
{
	int error = GESTURE_ERROR_NONE;

	error = gesture_release(NULL);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Starts recognition
/**
 * @testcase		utc_motion_gesture_start_recognition_p
 * @since_tizen		2.3
 * @description		Positive test case of motion_gesture_start_recognition()
 */
int utc_motion_gesture_start_recognition_p(void)
{
	int error = GESTURE_ERROR_NONE;

	error = gesture_start_recognition(handle, gesture_type, GESTURE_OPTION_DEFAULT, gesture_cb, NULL);

	if(is_supported)
	{
		if (support) {
			assert_eq(error, GESTURE_ERROR_NONE);
			gesture_stop_recognition(handle);
		} else {
			assert_eq(error, GESTURE_ERROR_NOT_SUPPORTED);
		}
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Starts recognition with invalid parameters
/**
 * @testcase		utc_motion_gesture_start_recognition_n
 * @since_tizen		2.3
 * @description		Negative test case of motion_gesture_start_recognition()
 */
int utc_motion_gesture_start_recognition_n(void)
{
	int error = GESTURE_ERROR_NONE;

	error = gesture_start_recognition(NULL, gesture_type, GESTURE_OPTION_DEFAULT, gesture_cb, NULL);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}

	error = gesture_start_recognition(handle, -1, GESTURE_OPTION_DEFAULT, gesture_cb, NULL);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}
	error = gesture_start_recognition(handle, gesture_type, -1, gesture_cb, NULL);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}

	error = gesture_start_recognition(handle, gesture_type, GESTURE_OPTION_DEFAULT, NULL, NULL);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Stops recognition
/**
 * @testcase		utc_motion_gesture_stop_recognition_p
 * @since_tizen		2.3
 * @description		Positive test case of motion_gesture_stop_recognition()
 */
int utc_motion_gesture_stop_recognition_p(void)
{
	int error = GESTURE_ERROR_NONE;

	error = gesture_start_recognition(handle, gesture_type, GESTURE_OPTION_DEFAULT, gesture_cb, NULL);

	if(is_supported)
	{
		if (support)
		{
			assert_eq(error, GESTURE_ERROR_NONE);
			error = gesture_stop_recognition(handle);
			if(is_supported)
			{
				if (support)
				{
					assert_eq(error, GESTURE_ERROR_NONE);
				}
				else
				{
					assert_eq(error, GESTURE_ERROR_NOT_STARTED);
				}
			}
			else
			{
				assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
			}
		}
		else
		{
			assert_eq(error, GESTURE_ERROR_NOT_SUPPORTED);
		}
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Stops recognizing the gesture with invalid parameter
/**
 * @testcase		utc_motion_gesture_stop_recognition_n
 * @since_tizen		2.3
 * @description		Negative test case of motion_gesture_stop_recognition()
 */
int utc_motion_gesture_stop_recognition_n(void)
{
	int error = GESTURE_ERROR_NONE;

	error = gesture_stop_recognition(NULL);

	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Gets a gesture event with invalid parameter
/**
 * @testcase		utc_motion_gesture_get_event_n
 * @since_tizen		2.3
 * @description		Negative test case of motion_gesture_get_event()
 */
int utc_motion_gesture_get_event_n(void)
{
	int error = GESTURE_ERROR_NONE;
	gesture_event_e event;
	gesture_data_h data = NULL;

	error = gesture_get_event(NULL, &event);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}
	error = gesture_get_event(data, NULL);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//& purpose: Gets tilting degrees with invalid parameter
/**
 * @testcase		utc_motion_gesture_get_tilt_n
 * @since_tizen		2.3
 * @description		Negative test case of motion_gesture_get_tilt()
 */
int utc_motion_gesture_get_tilt_n(void)
{
	int error = GESTURE_ERROR_NONE;
	int tilt_x, tilt_y;
	gesture_data_h data = NULL;

	error = gesture_get_tilt(NULL, &tilt_x, &tilt_y);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}
	error = gesture_get_tilt(data, NULL, &tilt_y);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}

	error = gesture_get_tilt(data, &tilt_x, NULL);
	if(is_supported)
	{
		assert_eq(error, GESTURE_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , GESTURE_ERROR_NOT_SUPPORTED);
	}
	return 0;
}
