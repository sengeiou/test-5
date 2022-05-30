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

#ifndef __TIZEN__
#define __TIZEN__
#endif

#include <AL/al.h>
#include <AL/alc.h>
#include <sound_manager.h>

#include <stdio.h>
#include "assert.h"
#include "tct_common.h"

/**
 * @testcase		utc_alcOpenDeviceNew_p
 * @since_tizen		3.0
 * @description		Positive test case to alcOpenDeviceNew
 * @scenario		open openal device with proper parameters
 */
int utc_alcOpenDeviceNew_p(void)
{
	int ret;
	ALCdevice *device = NULL;
	ALCboolean alret = ALC_FALSE;
	sound_stream_info_h stream_info;

	/* prepare sound stream information handle */
	ret = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	/* check for opening device with given sound stream info handle */
	device = alcOpenDeviceNew(NULL, stream_info);
	assert_neq(device, NULL);

	/* close opened device */
	alret = alcCloseDevice(device);
	assert_eq(alret, ALC_TRUE);

	/* cleanup sound stream information handle */
	ret = sound_manager_destroy_stream_information(stream_info);
	assert_eq(ret, SOUND_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_alcOpenDeviceNew_n
 * @since_tizen		3.0
 * @description		Negative test case to alcOpenDeviceNew, passing invalid parameter
 * @scenario		open openal device with invalid paremters(null stream info)
 */
int utc_alcOpenDeviceNew_n(void)
{
	ALCdevice *device;
	ALenum err;

	/* try open with NULL stream info handle, return should be NULL */
	device = alcOpenDeviceNew(NULL, NULL);
	assert_eq(device, NULL);

	/* error value must be invalid value */
	err = alGetError();
	assert_eq(err, ALC_INVALID_VALUE);

	return 0;
}
