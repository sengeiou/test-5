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
#include "assert_common.h"
#include <app_resource_manager.h>
#include <unistd.h>
//& set: ApplicationResource

#define EDJ_ID "rsc1.edc"
#define IMAGE_ID "tizen_logo.png"
#define SOUND_ID "Kalimba.mp3"
#define BIN_ID "test.bin"

#define F_OK 0

/**
 * @function		utc_application_app_resource_manager_startup
 * @description		Called the app_resource_manager_init().
 * @parameter		NA
 * @return		NA
 */
void utc_application_app_resource_manager_startup(void)
{
	app_resource_manager_init();
}

/**
 * @function		utc_application_app_resource_manager_cleanup
 * @description		Called the app_resource_manager_release().
 * @parameter		NA
 * @return		NA
 */
void utc_application_app_resource_manager_cleanup(void)
{
	app_resource_manager_release();
}

/**
 * @testcase		utc_application_app_resource_manager_get_p1
 * @since_tizen		2.4
 * @type		Positive
 * @description		Convert resource ID to path name.
 * @scenario		Gets the layout type path.
 *			Calls the app_resource_manager_get() with the APP_RESOURCE_TYPE_LAYOUT
 *			parameter and then checks the return value.
 */
int utc_application_app_resource_manager_get_p1(void)
{
	int ret;
	char *ret_path;

	ret = app_resource_manager_get(APP_RESOURCE_TYPE_LAYOUT, EDJ_ID, &ret_path);
	assert_eq_with_exit(ret, APP_RESOURCE_ERROR_NONE);
	assert_eq_with_exit(access(ret_path, F_OK), 0);
	assert_with_exit(ret_path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_resource_manager_get_p2
 * @since_tizen		2.4
 * @type		Positive
 * @description		Convert resource ID to path name.
 * @scenario		Gets the image type path.
 *			Calls the app_resource_manager_get() with the APP_RESOURCE_TYPE_IMAGE
 *			parameter and then checks the return value.
 */
int utc_application_app_resource_manager_get_p2(void)
{
	int ret;
	char *ret_path;

	ret = app_resource_manager_get(APP_RESOURCE_TYPE_IMAGE, IMAGE_ID, &ret_path);
	assert_eq_with_exit(ret, APP_RESOURCE_ERROR_NONE);
	assert_eq_with_exit(access(ret_path, F_OK), 0);
	assert_with_exit(ret_path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_resource_manager_get_p3
 * @since_tizen		2.4
 * @type		Positive
 * @description		Convert resource ID to path name.
 * @scenario		Gets the sound type path.
 *			Calls the app_resource_manager_get() with the APP_RESOURCE_TYPE_SOUND
 *			parameter and then checks the return value.
 */
int utc_application_app_resource_manager_get_p3(void)
{
	int ret;
	char *ret_path;

	ret = app_resource_manager_get(APP_RESOURCE_TYPE_SOUND, SOUND_ID, &ret_path);
	assert_eq_with_exit(ret, APP_RESOURCE_ERROR_NONE);
	assert_eq_with_exit(access(ret_path, F_OK), 0);
	assert_with_exit(ret_path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_resource_manager_get_p4
 * @since_tizen		2.4
 * @type		Positive
 * @description		Convert resource ID to path name.
 * @scenario		Gets the bin type path.
 *			Calls the app_resource_manager_get() with the APP_RESOURCE_TYPE_BIN
 *			parameter and then checks the return value.
 */
int utc_application_app_resource_manager_get_p4(void)
{
	int ret;
	char *ret_path;

	ret = app_resource_manager_get(APP_RESOURCE_TYPE_BIN, BIN_ID, &ret_path);
	assert_eq_with_exit(ret, APP_RESOURCE_ERROR_NONE);
	assert_eq_with_exit(access(ret_path, F_OK), 0);
	assert_with_exit(ret_path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_resource_manager_get_p5
 * @since_tizen		2.4
 * @type		Positive
 * @description		Convert resource ID to path name.
 * @scenario		Gets the image type path.
 *			Calls the app_resource_manager_get() with the APP_RESOURCE_TYPE_IMAGE
 *			parameter and then checks the return value.
 */
int utc_application_app_resource_manager_get_p5(void)
{
	int ret;
	char *ret_path;

	ret = app_resource_manager_get(APP_RESOURCE_TYPE_IMAGE, IMAGE_ID, &ret_path);
	assert_eq_with_exit(ret, APP_RESOURCE_ERROR_NONE);
	assert_eq_with_exit(access(ret_path, F_OK), 0);

	ret = app_resource_manager_get(APP_RESOURCE_TYPE_IMAGE, IMAGE_ID, &ret_path);
        assert_eq_with_exit(ret, APP_RESOURCE_ERROR_NONE);
	assert_eq_with_exit(access(ret_path, F_OK), 0);

	assert_with_exit(ret_path);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_resource_manager_get_n1
 * @since_tizen		2.4
 * @type		Negative
 * @description		Convert resource ID to path name.
 * @scenario		Calls the app_resource_manager_get() with the invalid parameter
 *			that the type is 10, and then checks the return value.
 */
int utc_application_app_resource_manager_get_n1(void)
{
	int ret;
	char *ret_path;

	ret = app_resource_manager_get(10, SOUND_ID, &ret_path);
	assert_eq_with_exit(ret, APP_RESOURCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_resource_manager_get_n2
 * @since_tizen		2.4
 * @type		Negative
 * @description		Convert resource ID to path name.
 * @scenario		Calls the app_resource_manager_get() with the invalid parameter
 *			that the id is NULL, and then checks the return value.
 */
int utc_application_app_resource_manager_get_n2(void)
{
	int ret;
	char *ret_path;

	ret = app_resource_manager_get(APP_RESOURCE_TYPE_SOUND, NULL, &ret_path);
	assert_eq_with_exit(ret, APP_RESOURCE_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_resource_manager_get_n3
 * @since_tizen		2.4
 * @type		Negative
 * @description		Convert resource ID to path name.
 * @scenario		Calls the app_resource_manager_get() with the invalid prameter
 *			that the id is not exists, and then checks the return value.
 */
int utc_application_app_resource_manager_get_n3(void)
{
	int ret;
	char *ret_path;

	ret = app_resource_manager_get(APP_RESOURCE_TYPE_IMAGE, "dummy", &ret_path);
	assert_eq_with_exit(ret, APP_RESOURCE_ERROR_IO_ERROR);
	normal_exit(0);

	return 0;
}
