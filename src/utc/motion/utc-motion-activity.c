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
#include <activity_recognition.h>
#include <system_info.h>


//& set: Motion - Activity
static bool support = false;
static activity_h handle = NULL;
static bool is_supported = false;

static void activity_cb(activity_type_e activity, const activity_data_h data, double timestamp, activity_error_e error, void *user_data)
{
}

/**
 * @function		utc_motion_activity_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_motion_activity_startup(void)
{
	system_info_get_platform_bool("http://tizen.org/feature/sensor.activity_recognition", &is_supported);
	activity_is_supported(ACTIVITY_WALK, &support);
	activity_create(&handle);
}

/**
 * @function		utc_motion_activity_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_motion_activity_cleanup(void)
{
	if (handle) {
		activity_release(handle);
		handle = NULL;
	}
}


//& purpose: Checks whether the given activity is recognizable or not.
/**
 * @testcase		utc_motion_activity_is_supported_p
 * @since_tizen		2.3
 * @description		Positive test case of motion_activity_is_supported()
 */
int utc_motion_activity_is_supported_p(void)
{
	int error = ACTIVITY_ERROR_NONE;
	bool s;

	error = activity_is_supported(ACTIVITY_WALK, &s);
	if(is_supported)
	{
		assert(error == ACTIVITY_ERROR_NONE);
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Checks whether the given activity is recognizable with an invalid parameter.
/**
 * @testcase		utc_motion_activity_is_supported_n
 * @since_tizen		2.3
 * @description		Nagative test case of motion_activity_is_suported()
 */
int utc_motion_activity_is_supported_n(void)
{
	int error = ACTIVITY_ERROR_NONE;

	error = activity_is_supported(ACTIVITY_WALK, NULL);
	if(is_supported)
	{
		assert_eq(error , ACTIVITY_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


//& purpose: Initializes a handle object for activity recognition.
/**
 * @testcase		utc_motion_activity_create_p
 * @since_tizen		2.3
 * @description		Positive test case of motion_activity_create()
 */
int utc_motion_activity_create_p(void)
{
	int error = ACTIVITY_ERROR_NONE;
	activity_h h;

	error = activity_create(&h);
	if(is_supported)
	{
		assert_eq(error, ACTIVITY_ERROR_NONE);
		activity_release(h);
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//& purpose: Initializes a handle object for activity recognition with an invalid parameter
/**
 * @testcase		utc_motion_activity_create_n
 * @since_tizen		2.3
 * @description		Negative test case of motion_activity_create()
 */
int utc_motion_activity_create_n(void)
{
	int error = ACTIVITY_ERROR_NONE;

	error = activity_create(NULL);
	if(is_supported)
	{
		assert_eq(error, ACTIVITY_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}
	return 0;
}


//& purpose: Releases resources allocated for the handle.
/**
 * @testcase		utc_motion_activity_release_p
 * @since_tizen		2.3
 * @description		Positive test case of motion_activity_release()
 */
int utc_motion_activity_release_p(void)
{
	int error = ACTIVITY_ERROR_NONE;
	activity_h h;

	activity_create(&h);

	error = activity_release(h);
	if(is_supported)
	{
		assert_eq(error, ACTIVITY_ERROR_NONE);
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Releases resources with an invalid parameter
/**
 * @testcase		utc_motion_activity_release_n
 * @since_tizen		2.3
 * @description		Negative test case of motion_activity_release()
 */
int utc_motion_activity_release_n(void)
{
	int error = ACTIVITY_ERROR_NONE;

	error = activity_release(NULL);
	if(is_supported)
	{
		assert_eq(error, ACTIVITY_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}
	return 0;
}


//& purpose: Starts recognition
/**
 * @testcase		utc_motion_activity_start_recognition_p
 * @since_tizen		2.3
 * @description		Positive test case of motion_activity_start_recognition()
 */
int utc_motion_activity_start_recognition_p(void)
{
	int error = ACTIVITY_ERROR_NONE;

	error = activity_start_recognition(handle, ACTIVITY_WALK, activity_cb, NULL);
	if(is_supported)
	{
		if (support) {
			assert_eq(error, ACTIVITY_ERROR_NONE);
			activity_stop_recognition(handle);
		} else {
			assert_eq(error, ACTIVITY_ERROR_NOT_SUPPORTED);
		}
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Starts recognition with an invalid parameter
/**
 * @testcase		utc_motion_activity_start_recognition_n
 * @since_tizen		2.3
 * @description		Negative test case of motion_activity_start_recognition()
 */
int utc_motion_activity_start_recognition_n(void)
{
	int error = ACTIVITY_ERROR_NONE;

	error = activity_start_recognition(handle, ACTIVITY_WALK, NULL, NULL);
	if(is_supported)
	{
		assert_eq(error, ACTIVITY_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}

	error = activity_start_recognition(NULL, ACTIVITY_WALK, activity_cb, NULL);
	if(is_supported)
	{
		assert_eq(error, ACTIVITY_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}
	return 0;
}


//& purpose: Stops recognition
/**
 * @testcase		utc_motion_activity_stop_recognition_p
 * @since_tizen		2.3
 * @description		Positive test case of motion_activity_stop_recognition()
 */
int utc_motion_activity_stop_recognition_p(void)
{
	int error = ACTIVITY_ERROR_NONE;

	activity_start_recognition(handle, ACTIVITY_WALK, activity_cb, NULL);

	error = activity_stop_recognition(handle);
	if(is_supported)
	{
		if (support) {
			assert_eq(error, ACTIVITY_ERROR_NONE);
		} else {
			assert_eq(error, ACTIVITY_ERROR_NOT_STARTED);
		}
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Stops recogntion with an invalid parameter
/**
 * @testcase		utc_motion_activity_stop_recognition_n
 * @since_tizen		2.3
 * @description		Negative test case of motion_activity_stop_recognition()
 */
int utc_motion_activity_stop_recognition_n(void)
{
	int error = ACTIVITY_ERROR_NONE;

	error = activity_stop_recognition(NULL);
	if(is_supported)
	{
		assert_eq(error, ACTIVITY_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

//& purpose: Gets the recognition accuracy
/**
 * @testcase		utc_motion_activity_get_accuracy_n
 * @since_tizen		2.3
 * @description		Negative test case of motion_activity_get_accuracy()
 */
int utc_motion_activity_get_accuracy_n(void)
{
	int error = ACTIVITY_ERROR_NONE;
	activity_accuracy_e acc;
	activity_data_h data = NULL;

	error = activity_get_accuracy(NULL, &acc);
	if(is_supported)
	{
		assert_eq(error, ACTIVITY_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}

	error = activity_get_accuracy(data, NULL);
	if(is_supported)
	{
		assert_eq(error, ACTIVITY_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(error , ACTIVITY_ERROR_NOT_SUPPORTED);
	}
	return 0;
}
