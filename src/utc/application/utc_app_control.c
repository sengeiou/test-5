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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <app.h>
#include <bundle.h>
#include <dlog.h>
#include <app_control.h>

#include "tct_app_common.h"
#include "assert.h"
#include "assert_common.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "NativeTCT"

/**
 * @function            utc_application_app_control_startup
 * @description         Called before some test
 * @parameter           NA
 * @return              NA
 */
void utc_application_app_control_startup(void)
{
	TCT_UTCCheckInstalledApp(1, "org.tizen.helloworld");
}


//& set: ApplicationService

/**
 * @testcase		utc_application_app_control_create_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Creates an app_control handle.
 * @scenario		Creates an app_control handle and destroys the handle.
 */
int utc_application_app_control_create_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	ret = app_control_create(&app_control);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_create_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Creates an app_control handle.
 * @scenario		Creates an app_control handle with the invalid parameter
 *			that the app_control is NULL, and then checks return value.
 */
int utc_application_app_control_create_n(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_create(NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_destroy_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Destroys the app_control handle and releases all its resources.
 * @scenario		Creates an app_control handle and destroys the handle.
 */
int utc_application_app_control_destroy_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	normal_exit(0);


	return 0;
}

/**
 * @testcase		utc_application_app_control_destroy_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Destroys the app_control handle and releases all its resources.
 * @scenario		Calls the app_control_destroy() with the NULL parameter,
 *			and then checks the return value.
 */
int utc_application_app_control_destroy_n(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_destroy(NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_operation_p1
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets the operation to be performed.
 * @scenario		Creates an app_control handle and sets the operation,
 *			and then gets the operation. Next, destorys the handle.
 */
int utc_application_app_control_set_operation_p1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *output_value;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_operation(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output_value, NULL);
	assert_with_exit(!strcmp(output_value, APP_CONTROL_OPERATION_DEFAULT));

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_operation_p2
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets the operation to be performed.
 * @scenario		Create the app_control handle and sets the operation,
 *			and then gets the operation. Next, destroys the handle.
 */
int utc_application_app_control_set_operation_p2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *output_value = NULL;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_operation(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output_value, NULL);
	assert_with_exit(!strcmp(output_value, APP_CONTROL_OPERATION_DEFAULT));

	ret = app_control_set_operation(app_control, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_operation(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_eq_with_exit(output_value, NULL);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_operation_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets the operation to be performed.
 * @scenario		Sets the operation with the NULL parameter,
 *			and then checks the return value.
 */
int utc_application_app_control_set_operation_n(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_set_operation(NULL, APP_CONTROL_OPERATION_DEFAULT);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_operation_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the operation to be performed.
 * @scenario		Creates an app_control handler and sets the operation,
 *			and then gets the operation. checks the return value.
 */
int utc_application_app_control_get_operation_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *output_value;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_operation(app_control, &output_value);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_eq_with_exit(output_value, NULL);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_operation_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the operation to be performed.
 * @scenario		Gets the operation with the NULL parameter,
 *			and then checks the return value.
 */
int utc_application_app_control_get_operation_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *output_value;

	ret = app_control_get_operation(NULL, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_operation_n2
 * @since_tizen		2.3
 * @scenario		Negative
 * @description		Gets the operation to be performed.
 * @scenario		Creates an app_control handle and gets the operation,
 *			and then checks the return value.
 */
int utc_application_app_control_get_operation_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_operation(app_control, NULL);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_operation_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the operation to be performed.
 * @scenario		Gets the operation with the NULL parameters,
 *			and then checks the return value.
 */
int utc_application_app_control_get_operation_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	app_control_create(&app_control);

	ret = app_control_get_operation(NULL, NULL);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}


/**
 * @testcase		utc_application_app_control_set_uri_p1
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets the URI of the data.
 * @scenario		Creates an app_control handle and sets the URI,
 *			and then gets the URI.
 */
int utc_application_app_control_set_uri_p1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	const char *input_value = "http://tizen.org/example.html";
	char *output_value = NULL;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_uri(app_control, input_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_uri(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output_value, NULL);
	assert_with_exit(!strcmp(output_value, input_value));

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_uri_p2
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets the URI of the data.
 * @scenario		Creates an app_control handle and sets the URI,
 *			and then gets the URI.
 */
int utc_application_app_control_set_uri_p2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *input_value = "http://tizen.org/example.html";
	char *output_value = NULL;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_uri(app_control, input_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_uri(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output_value, NULL);
	assert_with_exit(!strcmp(output_value, input_value));

	ret = app_control_set_uri(app_control, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_uri(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_eq_with_exit(output_value, NULL);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_uri_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets the URI of the data.
 * @scenario		Sets the URI with the NULL parameter,
 *			and then checks the return value.
 */
int utc_application_app_control_set_uri_n(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *input_value = NULL;

	ret = app_control_set_uri(NULL, input_value);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_uri_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the URI of the data.
 * @scenario		Sets the URI and gets the URI.
 */
int utc_application_app_control_get_uri_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *output_value;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_uri(app_control, &output_value);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_eq_with_exit(output_value, NULL);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_uri_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the URI of the data.
 * @scenario		Gets the URI with the NULL parameter,
 *			and then checks the return value.
 */
int utc_application_app_control_get_uri_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *output_value;

	ret = app_control_get_uri(NULL, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_uri_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the URI of the data.
 * @scenario		Gets the URI with the NULL parameter,
 *			and then checks the return value.
 */
int utc_application_app_control_get_uri_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	app_control_create(&app_control);

	ret = app_control_get_uri(app_control, NULL);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_uri_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the URI of the data.
 * @scenario		Gets the URI with the NULL parameters,
 *			and then checks the return value.
 */
int utc_application_app_control_get_uri_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	app_control_create(&app_control);

	ret = app_control_get_uri(NULL, NULL);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_mime_p1
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets the explicit MIME type of the data.
 * @scenario		Sets the MIME and gets the MIME.
 */
int utc_application_app_control_set_mime_p1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	const char *input_value = "application/xml";
	char *output_value = NULL;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_mime(app_control, input_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_mime(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output_value, NULL);
	assert_with_exit(!strcmp(output_value, input_value));

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_mime_p2
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets the explicit MIME type of the data.
 * @scenario		Sets the MIME and gets the MIME.
 */
int utc_application_app_control_set_mime_p2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *input_value = "application/xml";
	char *output_value = NULL;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_mime(app_control, input_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_mime(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output_value, NULL);
	assert_with_exit(!strcmp(output_value, input_value));

	ret = app_control_set_mime(app_control, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_mime(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_eq_with_exit(output_value, NULL);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_mime_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets the explicit MIME type of the data.
 * @scenario		Calls the app_control_set_mime() with the NULL parameter
 *			that the app_control is NULL, and then checks the return value.
 */
int utc_application_app_control_set_mime_n(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *input_value = "application/xml";

	ret = app_control_set_mime(NULL, input_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_mime_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the explicit MIME type of the data.
 * @scenario		Sets the MIME and gets the MIME.
 */
int utc_application_app_control_get_mime_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *output_value;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_mime(app_control, &output_value);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_eq_with_exit(output_value, NULL);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_mime_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the explicit MIME type of the data.
 * @scenario		Calls the app_control_get_mime() with the invalid parameter
 *			that the app_control is NULL, and then checks the return value.
 */
int utc_application_app_control_get_mime_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *output_value;

	ret = app_control_get_mime(NULL, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_mime_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the explicit MIME type of the data.
 * @scenario		Cals the app_control_get_mime() with the invalid parameter
 *			that the mime is NULL, and then checks the return value.
 */
int utc_application_app_control_get_mime_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	app_control_create(&app_control);
	ret = app_control_get_mime(app_control, NULL);
	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_mime_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the explicit MIME type of the data.
 * @scenario		Calls the app_control_get_mime() with the invalid parameters,
 *			and then checks the return value.
 */
int utc_application_app_control_get_mime_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	app_control_create(&app_control);

	ret = app_control_get_mime(NULL, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_app_id_p1
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets the ID of the application to explicitly launch.
 * @scenario		Sets the appid and gets the appid.
 */
int utc_application_app_control_set_app_id_p1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	const char *input_value = "org.tizen.helloworld";
	char *output_value = NULL;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, input_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_app_id(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output_value, NULL);
	assert_with_exit(!strcmp(output_value, input_value));

	free(output_value);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_app_id_p2
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets the ID of the application to explicitly launch.
 * @scenario		Sets the appid and gets the appid.
 */
int utc_application_app_control_set_app_id_p2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *input_value = "org.tizen.helloworld";
	char *output_value = NULL;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, input_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_app_id(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output_value, NULL);
	assert_with_exit(!strcmp(output_value, input_value));

	ret = app_control_set_app_id(app_control, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_app_id(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_eq_with_exit(output_value, NULL);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_app_id_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets the ID of the application to explicitly launch.
 * @scenario		Calls the app_control_set_app_id() with the invalid parameters,
 *			and then checks the return value.
 */
int utc_application_app_control_set_app_id_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_set_app_id(NULL, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_app_id_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets the ID of the application to explicitly launch.
 * @scenario		Calls the app_control_set_app_id() with the invalid paramter
 *			that the app_control is NULL, and then checks the return value.
 */
int utc_application_app_control_set_app_id_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *input_value = "org.tizen.helloworld";

	ret = app_control_set_app_id(NULL, input_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_app_id_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the ID of the application to explicitly launch.
 * @scenario		Gets the appid.
 */
int utc_application_app_control_get_app_id_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *output_value;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_app_id(app_control, &output_value);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_eq_with_exit(output_value, NULL);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_app_id_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the ID of the application to explicitly launch.
 * @scenario		Calls the app_control_get_app_id() with the invalid parameter
 *			that the app_control is NULL, and then checks the return value.
 */
int utc_application_app_control_get_app_id_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *output_value;

	ret = app_control_get_app_id(NULL, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_app_id_n2
 * @since_tizen		2.3
 * #type		Negative
 * @description		Gets the ID of the application to explicitly launch.
 * @scenario		Calls the app_control_get_app_id() with the invalid parameter
 *			that the app_id is NULL, and then checks the return value.
 */
int utc_application_app_control_get_app_id_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	app_control_create(&app_control);

	ret = app_control_get_app_id(app_control, NULL);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_app_id_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the ID of the application to explicitly launch.
 * @scenario		Calls the app_control_get_app_id() with the invalid parameters
 *			and then checks the return value.
 */
int utc_application_app_control_get_app_id_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	app_control_create(&app_control);

	ret = app_control_get_app_id(NULL, NULL);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_category_p1
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets the explicit category.
 * @scenario		Sets the category and gets the category.
 */
int utc_application_app_control_set_category_p1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	const char *input_value = "Category:Tizen";
	char *output_value = NULL;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_category(app_control, input_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_category(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output_value, NULL);
	assert_with_exit(!strcmp(output_value, input_value));

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_category_p2
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets the explicit category.
 * @scenario		Sets the category and gets the category.
 */
int utc_application_app_control_set_category_p2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *input_value = "Category:Tizen";
	char *output_value = NULL;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_category(app_control, input_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_category(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output_value, NULL);
	assert_with_exit(!strcmp(output_value, input_value));

	ret = app_control_set_category(app_control, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_category(app_control, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_with_exit(output_value == NULL);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_category_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets the explicit category.
 * @scenario		Calls the app_control_set_category() with the invalid parameters,
 *			and then checks the return value.
 */
int utc_application_app_control_set_category_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_set_category(NULL, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_category_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets the explicit category.
 * @scenario		Calls the app_control_set_category() with the invalid parameter
 *			that the app_contrl is NULL, and then checks the return value.
 */
int utc_application_app_control_set_category_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *input_value = "Category:Tizen";

	ret = app_control_set_category(NULL, input_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_category_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the explicit category.
 * @scenario		Sets the category and gets the category.
 */
int utc_application_app_control_get_category_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *output_value;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_category(app_control, &output_value);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_eq_with_exit(output_value, NULL);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_category_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the explicit category.
 * @scenario		Calls the app_control_get_category() with the invalid parameter
 *			that the app_control is NULL, and then checks the return value.
 */
int utc_application_app_control_get_category_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *output_value;

	ret = app_control_get_category(NULL, &output_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_category_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the explicit category.
 * @scenario		Calls the app_control_get_categroy() with the invalid parameter
 *			that the category is NULL, and then checks the return value.
 */
int utc_application_app_control_get_category_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_category(app_control, NULL);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_category_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the explicit category.
 * @scenario		Calls the app_control_get_category() with the invalid parameters,
 *			and then checks the return value.
 */
int utc_application_app_control_get_category_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_category(NULL, NULL);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_add_extra_data_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Adds extra data to the app_control.
 * @scenario		Adds extra data and gets extra data.
 */
int utc_application_app_control_add_extra_data_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key1 = "EXTRA_KEY1";
	char *value1 = "EXTRA_VALUE1";
	char *key2 = "EXTRA_KEY2";
	char *value2 = "EXTRA_VALUE2";
	char *output1 = NULL;
	char *output2 = NULL;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data(app_control, key1, value1);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data(app_control, key1, &output1);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output1, NULL);
	assert_with_exit(!strcmp(output1, value1));
	free(output1);

	ret = app_control_add_extra_data(app_control, key2, value2);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data(app_control, key1, &output1);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output1, NULL);
	assert_with_exit(!strcmp(output1, value1));
	free(output1);

	ret = app_control_get_extra_data(app_control, key2, &output2);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output2, NULL);
	assert_with_exit(!strcmp(output2, value2));
	free(output2);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_add_extra_data_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Adds extra data to the app_control.
 * @scenario		Adds extra data with the invalid parameter.
 */
int utc_application_app_control_add_extra_data_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	int ret1 = APP_CONTROL_ERROR_NONE;
	int ret2 = APP_CONTROL_ERROR_NONE;
	int ret3 = APP_CONTROL_ERROR_NONE;
	int ret4 = APP_CONTROL_ERROR_NONE;
	char *key = "EXTRA_KEY";
	char *value = "EXTRA_VALUE";

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	// key : null
	ret1 = app_control_add_extra_data(app_control, NULL, value);

	// key : zero-length
	ret2 = app_control_add_extra_data(app_control, "", value);

	// value : null
	ret3 = app_control_add_extra_data(app_control, key, NULL);

	// value : zero-length
	ret4 = app_control_add_extra_data(app_control, key, "");

	app_control_destroy(app_control);

	assert_eq_with_exit(ret1, APP_CONTROL_ERROR_INVALID_PARAMETER);
	assert_eq_with_exit(ret2, APP_CONTROL_ERROR_INVALID_PARAMETER);
	assert_eq_with_exit(ret3, APP_CONTROL_ERROR_INVALID_PARAMETER);
	assert_eq_with_exit(ret4, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_add_extra_data_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Adds extra data to the app_control.
 * @scenario		Calls the app_control_add_extra_data() with the invalid parameter
 *			that the app_control is NULL, and then checks the return value.
 */
int utc_application_app_control_add_extra_data_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key = "EXTRA_KEY";
	char *value = "EXTRA_VALUE";

	ret = app_control_add_extra_data(NULL, key, value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_add_extra_data_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Adds extra data to the app_control.
 * @scenario		Calls the app_control_add_extra_data() with the invalid parameters,
 *			and then checks the return value.
 */
int utc_application_app_control_add_extra_data_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key = "__APP_SVC_KEY";
	char *value = "__APP_SVC_VALUE";

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data(app_control, key, value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_KEY_REJECTED);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_remove_extra_data_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Removes the extra data from the app_control.
 * @scenario		Adds the extra data and removes the extra data.
 */
int utc_application_app_control_remove_extra_data_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *key = "EXTRA_KEY";
	char *value = "EXTRA_VALUE";
	char *output = NULL;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data(app_control, key, value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data(app_control, key, &output);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(output, NULL);
	assert_with_exit(!strcmp(output, value));
	free(output);

	ret = app_control_remove_extra_data(app_control, key);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	output = NULL;
	ret = app_control_get_extra_data(app_control, key, &output);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_KEY_NOT_FOUND);
	assert_eq_with_exit(output, NULL);

	app_control_destroy(app_control);
        normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_remove_extra_data_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Removes the extra data from the app_control.
 * @scenario		Removes the extra data with the specified key
 *			that the app_control does not have, and then checks the return value.
 */
int utc_application_app_control_remove_extra_data_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key = "EXTRA_KEY";

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_remove_extra_data(app_control, key);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_KEY_NOT_FOUND);
        normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_remove_extra_data_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Removes the extra data from the app_control.
 * @scenario		Calls the app_control_remove_extra_data() with the invalid parameter
 *			that the app_control is NULL, and then checks the return value.
 */
int utc_application_app_control_remove_extra_data_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key = "EXTRA_KEY";

	ret = app_control_remove_extra_data(NULL, key);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_remove_extra_data_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Removes the extra data from the app_control.
 * @scenario		Calls the app_control_remove_extra_data() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_app_control_remove_extra_data_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_remove_extra_data(app_control, NULL);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_remove_extra_data_n4
 * @since_tizen		2.3
 * @type		Negative
 * @description		Removes the extra data from the app_control.
 * @scenario		Calls the app_control_remove_extra_data() with the invalid key,
 *			and then checks the return value.
 */
int utc_application_app_control_remove_extra_data_n4(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key = "__APP_SVC__KEY";

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_remove_extra_data(app_control, key);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_KEY_REJECTED);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the extra data from the app_control.
 * @scenario		Adds the extra data and gets the extra data.
 */
int utc_application_app_control_get_extra_data_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key = "EXTRA_KEY";
	char *value = "EXTRA_VALUE";
	char *ret_value = NULL;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data(app_control, key, value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data(app_control, key, &ret_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_with_exit(!strcmp(ret_value, value));
	free(ret_value);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the extra data from the app_control.
 * @scenario		Calls the app_control_get_extra_data() with the specified key
 *			that the app_control does not have, and then checks the return value.
 */
int utc_application_app_control_get_extra_data_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key = "EXTRA_KEY";
	char *ret_value;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data(app_control, key, &ret_value);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_KEY_NOT_FOUND);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the extra data from the app_control.
 * @scenario		Calls the app_control_get_extra_data() with the invalid parameter
 *			that the app_control is NULL, and then checks the return value.
 */
int utc_application_app_control_get_extra_data_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key = "EXTRA_KEY";
	char *ret_value;

	ret = app_control_get_extra_data(NULL, key, &ret_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the extra data from the app_control.
 * @scenario		Calls the app_control_get_extra_data() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_app_control_get_extra_data_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	char *ret_value;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data(app_control, NULL, &ret_value);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_n4
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the extra data from the app_control.
 * @scenario		Calls the app_control_get_extra_data() with the invalid paramter
 *			that the value is NULL, and then checks the return value.
 */
int utc_application_app_control_get_extra_data_n4(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key = "EXTRA_KEY";

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data(app_control, key, NULL);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_n5
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the extra data from the app_control.
 * @scenario		Calls the app_control_get_extra_data() with the invalid key
 *			and then checks the return value.
 */
int utc_application_app_control_get_extra_data_n5(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key = "__APP_SVC__KEY";
	char *ret_value;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data(app_control, key, &ret_value);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_KEY_REJECTED);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_array_n6
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the extra data array from the app_control.
 * @scenario		Calls the app_control_get_extra_data_array() with the invalid key
 *			and then checks the return value.
 */
int utc_application_app_control_get_extra_data_array_n6(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *array_key = "__APP_SVC__key";
	char **out_array = NULL;
	int out_length = -1;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data_array(app_control, array_key, &out_array, &out_length);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_KEY_REJECTED);
	normal_exit(0);

	return 0;
}

#define NUM_EXTRA_DATA 32
bool app_control_extra_data(app_control_h app_control, const char *key, void *user_data)
{
	bool *passed = (bool*)user_data;
	char *value;

	app_control_get_extra_data(app_control, key, &value);

	if (!strcmp(key, value)) {
		int index = atoi(key);
		passed[index] = true;
	}

	return true;
}

/**
 * @testcase		utc_application_app_control_foreach_extra_data_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Retrieves all extra data contained in app_control.
 * @scenario		Adds the extra data and retrieves all extra data.
 */
int utc_application_app_control_foreach_extra_data_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	int i;
	bool passed[NUM_EXTRA_DATA] = {0, };
	int num_passed = 0;
	char buf[32] = {0, };

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	for (i=0; i<NUM_EXTRA_DATA; i++) {
		snprintf(buf, sizeof(buf), "%d", i);
		ret = app_control_add_extra_data(app_control, buf, buf);
		assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	}

	ret = app_control_foreach_extra_data(app_control, app_control_extra_data, &passed);

	for (i=0; i<NUM_EXTRA_DATA; i++) {
		if (passed[i] == true) {
			num_passed++;
		}
	}

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_eq_with_exit(num_passed, NUM_EXTRA_DATA);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_foreach_extra_data_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Retrieves all extra data contained in app_control.
 * @scenario		Calls the app_control_foreach_extra_data() with the invalid parameter
 *			that the callback function is NULL, and then checks the return value.
 */
int utc_application_app_control_foreach_extra_data_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_foreach_extra_data(app_control, NULL, NULL);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_foreach_extra_data_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Retrieves all extra data contained in app_control.
 * @scenario		Calls the app_control_foreach_extra_data() with the invalid parameter
 *			that the app_control is NULL, and then checks the return value.
 */
int utc_application_app_control_foreach_extra_data_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_foreach_extra_data(NULL, app_control_extra_data, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_clone_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Creates and returns a copy of the given app_control handle.
 * @scenario		Creates an app_control handle and copies the app_control.
 */
int utc_application_app_control_clone_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	char *operation = "OPERATION_VALUE";
	char *operation_clone;

	char *uri = "URI_VALUE";
	char *uri_clone;

	char *mime = "MIME_VALUE";
	char *mime_clone;

	char *app_id = "APP_ID_VALUE";
	char *app_id_clone;

	char *extra_key = "EXTRA_KEY";

	char *extra_value = "EXTRA_VALUE";
	char *extra_value_clone;

	app_control_h app_control;
	app_control_h app_control_cloned;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	ret = app_control_set_operation(app_control, operation);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	ret = app_control_set_uri(app_control, uri);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	ret = app_control_set_mime(app_control, mime);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	ret = app_control_add_extra_data(app_control, extra_key, extra_value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_clone(&app_control_cloned, app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_operation(app_control_cloned, &operation_clone);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	ret = app_control_get_uri(app_control_cloned, &uri_clone);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	ret = app_control_get_mime(app_control_cloned, &mime_clone);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	ret = app_control_get_app_id(app_control_cloned, &app_id_clone);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	ret = app_control_get_extra_data(app_control_cloned, extra_key, &extra_value_clone);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	ret = app_control_destroy(app_control_cloned);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	assert_with_exit(!strcmp(operation, operation_clone));
	free(operation_clone);

	assert_with_exit(!strcmp(uri, uri_clone));
	free(uri_clone);

	assert_with_exit(!strcmp(mime, mime_clone));
	free(mime_clone);

	assert_with_exit(!strcmp(app_id, app_id_clone));
	free(app_id_clone);

	assert_with_exit(!strcmp(extra_value, extra_value_clone));
	free(extra_value_clone);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_clone_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Creates and returns a copy of the given app_control handle.
 * @scenario		Calls the app_control_clone() with the NULL parameter
 *			and then checks the return value.
 */
int utc_application_app_control_clone_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_h app_control_cloned;

	ret = app_control_clone(&app_control_cloned, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_clone_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Creates and returns a copy of the given app_control handle.
 * @scenario		Calls the app_control_clone() with the NULL parameter,
 *			and then checks the return value.
 */
int utc_application_app_control_clone_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_clone(NULL, app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

void dts_app_control_reply_cb(app_control_h request, app_control_h reply,
				app_control_result_e result, void *user_data)
{
}

/**
 * @testcase		utc_application_app_control_send_launch_request_p1
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sends the launch request.
 * @scenario		Sets the appid and sends the launch request.
 */
int utc_application_app_control_send_launch_request_p1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *app_id = "org.tizen.helloworld";

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	// explicit launch without reply callback
	ret = app_control_send_launch_request(app_control, NULL, NULL);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_send_launch_request_p2
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sends the launch request.
 * @scenario		Sends the launch request with the reply callback.
 */
int utc_application_app_control_send_launch_request_p2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *app_id = "org.tizen.helloworld";

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	// explicit launch with reply callback
	ret = app_control_send_launch_request(app_control, dts_app_control_reply_cb, NULL);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_send_launch_request_p3
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sends the launch request.
 * @scenario		Sets the operation, the mime and the appid,
 *			and then sends the launch request.
 */
int utc_application_app_control_send_launch_request_p3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *app_id = "org.tizen.helloworld";
	const char *mime = "type/custom";

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_mime(app_control, mime);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_send_launch_request(app_control, dts_app_control_reply_cb, NULL);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_send_launch_request_p4
 * @since_tizen		2.3
 * @remarks		This testcase is for app_control privilege feature
 * 			which is enabled since tizen 4.0
 * @type		Positive
 * @description		Sends the launch request.
 * @scenario		Sets the operation, the appid, and then sends the
 * 			launch request. This target application requires
 * 			privilege(http://tizen.org/privilege/alarm.get) to
 *			send app_control.
 */
int utc_application_app_control_send_launch_request_p4(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *app_id = "org.example.appcontrolprivilegetest";

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_send_launch_request(app_control, dts_app_control_reply_cb, NULL);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_send_launch_request_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sends the launch request.
 * @scenario		Calls the app_control_send_launch_request() with the invalid parameters.
 */
int utc_application_app_control_send_launch_request_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_send_launch_request(NULL, NULL, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_send_launch_request_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sends the launch request.
 * @scenario		Sends the launch request without the given appid.
 *			If the operation is APP_CONTROL_OPERATION_DEFAULT,
 *			the app_control requires the appid for sending the launch request.
 */
int utc_application_app_control_send_launch_request_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_send_launch_request(app_control, NULL, NULL);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_APP_NOT_FOUND);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_send_launch_request_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sends the launch request.
 * @scenario		Sends the launch request with the invalid appid.
 */
int utc_application_app_control_send_launch_request_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *app_id = "org.tizen.hellohelloworld";

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	// explicit launch without reply callback
	ret = app_control_send_launch_request(app_control, NULL, NULL);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_APP_NOT_FOUND);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_send_launch_request_n4
 * @since_tizen		2.3
 * @remarks		This testcase is for app_control privilege feature
 * 			which is enabled since tizen 4.0
 * @type		Negative
 * @description		Sends the launch request.
 * @scenario		Sends the launch request to application which requires
 *			privilege(http://tizen.org/privilege/notification).
 */
int utc_application_app_control_send_launch_request_n4(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *app_id = "org.example.appcontrolprivilegetest2";

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	// explicit launch without reply callback
	ret = app_control_send_launch_request(app_control, NULL, NULL);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_PERMISSION_DENIED);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_reply_to_launch_request_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Replies to the launch request sent by the caller.
 * @scenario		Calls the app_control_reply_to_launch_request() with the invalid parameter
 *			that the reply is NULL, and then checks the return value.
 */
int utc_application_app_control_reply_to_launch_request_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h request;

	ret = app_control_create(&request);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_reply_to_launch_request(NULL, request, APP_CONTROL_RESULT_CANCELED);

	app_control_destroy(request);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_reply_to_launch_request_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Replies to the launch request sent by the caller.
 * @scenario		Calls the app_control_reply_to_launch_request() with the invalid parameter
 *			that the request is NULL, and then checks the return value.
 */
int utc_application_app_control_reply_to_launch_request_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h reply;

	ret = app_control_create(&reply);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_reply_to_launch_request(reply, NULL, APP_CONTROL_RESULT_CANCELED);

	app_control_destroy(reply);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_reply_to_launch_request_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Replies to the launch request sent by the caller.
 * @scenario		Calls the app_control_reply_to_launch_request() with the invalid parameters
 *			and then checks the return value.
 */
int utc_application_app_control_reply_to_launch_request_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h reply;
	app_control_h request;

	ret = app_control_create(&reply);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_create(&request);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_reply_to_launch_request(reply, request, APP_CONTROL_RESULT_FAILED);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);

	app_control_destroy(reply);
	app_control_destroy(request);
	normal_exit(0);

	return 0;
}

bool dts_app_control_app_matched_cb(app_control_h app_control, const char *package, void *user_data)
{
	return true;
}

/**
 * @testcase		utc_application_app_control_foreach_app_matched_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Retrieves all applications that can be launched to handle the given app_control request.
 * @scenario		Sets the operation and Retrieves all applications.
 */
int utc_application_app_control_foreach_app_matched_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	app_control_set_operation(app_control, APP_CONTROL_OPERATION_VIEW);

	ret = app_control_foreach_app_matched(app_control, dts_app_control_app_matched_cb, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_foreach_app_matched_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Retrieves all applications that can be launched to handle the given app_control request.
 * @scenario		Calls the app_control_foreach_app_matched() with the invalid parameter
 *			that the app_control is NULL, and then checks the return value.
 */
int utc_application_app_control_foreach_app_matched_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_foreach_app_matched(NULL, dts_app_control_app_matched_cb, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_foreach_app_matched_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Retrieves all applications that can be launched to handle the given app_control request.
 * @scenario		Calls the app_control_foreach_app_matched() with the invalid parameter
 *			that the callback is NULL, and then checks the return value.
 */
int utc_application_app_control_foreach_app_matched_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_foreach_app_matched(app_control, NULL, NULL);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_add_extra_data_array_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Adds the extra data array to the app_control.
 * @scenario		Adds the extra data array and gets the extra data arrays.
 */
int utc_application_app_control_add_extra_data_array_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	const char *array_key1 = "array_key1";
	const char *array_value1[] = {"array_value1_1", "array_value2_1", "array_value3_1", "array_value4_1"};
	int array_length1 = 4;

	const char *array_key2 = "array_key2";
	const char *array_value2[] = {"array_value1_2", "array_value2_2", "array_value3_2"};
	int array_length2 = 3;

	char **out_array = NULL;
	int out_length = -1;
	int i;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data_array(app_control, array_key1, array_value1, array_length1);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data_array(app_control, array_key1, &out_array, &out_length);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(out_array, NULL);
	assert_eq_with_exit(out_length, array_length1);

	for (i = 0; i < out_length; i ++) {
		assert_with_exit(!strcmp(out_array[i], array_value1[i]));
		free(out_array[i]);
	}

	free(out_array);
	out_array = NULL;

	out_length = -1;
	ret = app_control_add_extra_data_array(app_control, array_key2, array_value2, array_length2);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data_array(app_control, array_key2, &out_array, &out_length);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(out_array, NULL);
	assert_eq_with_exit(out_length, array_length2);

	for (i = 0; i < out_length; i ++) {
		assert(!strcmp(out_array[i], array_value2[i]));
		free(out_array[i]);
	}

	free(out_array);
	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_add_extra_data_array_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Adds the extra data array to the app_control.
 * @scenario		Calls the app_control_add_extra_data_array() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_app_control_add_extra_data_array_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char* array_value[] = {"array_value1", "array_value2", "array_value3", "array_value4"};
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data_array(app_control, NULL, array_value, 4);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_add_extra_data_array_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Adds the extra data array to the app_control.
 * @scenario		Calls the app_control_add_extra_data_array() with the invalid parameter
 *			that the value is NULL, and then checks the return value.
 */
int utc_application_app_control_add_extra_data_array_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *array_key = "array_key";
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data_array(app_control, array_key, NULL, 4);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_add_extra_data_array_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Adds the extra data array to the app_control.
 * @scenario		Calls the app_control_add_extra_data_array() with the invalid parameter
 *			that the length is -1, and then checks the return value.
 */
int utc_application_app_control_add_extra_data_array_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *array_key = "array_key";
	const char *array_value[] = {"array_value1", "array_value2", "array_value3", "array_value4"};
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data_array(app_control, array_key, array_value, -1);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_add_extra_data_array_n4
 * @since_tizen		2.3
 * @type		Negative
 * @description		Adds the extra data array to the app_control.
 * @scenario		Calls the app_control_add_extra_data_array() with the invalid key.
 */
int utc_application_app_control_add_extra_data_array_n4(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	const char *array_key = "__APP_SVC_KEY";
	const char *array_value[] = {"array_value1", "array_value2", "array_value3", "array_value4"};

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data_array(app_control, array_key, array_value, 4);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_KEY_REJECTED);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_array_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the extra data array from the app_control.
 * @scenario		Adds the extra data array and gets the extra data array.
 */
int utc_application_app_control_get_extra_data_array_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *array_key = "array_key";
	const char *array_value[] = {"array_value1", "array_value2", "array_value3", "array_value4"};
	int array_length = 4;
	char **out_array = NULL;
	int out_length = -1;
	int i;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data_array(app_control, array_key, array_value, array_length);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data_array(app_control, array_key, &out_array, &out_length);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_neq_with_exit(out_array, NULL);
	assert_eq_with_exit(out_length, array_length);

	for (i = 0; i < out_length; i ++) {
		assert_with_exit(!strcmp(out_array[i], array_value[i]));
		free(out_array[i]);
	}

	free(out_array);
	app_control_destroy(app_control);
	assert_eq_with_exit(out_length, array_length);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_array_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the extra data array from the app_control.
 * @scenario		Calls the app_control_get_extra_data_array() with the invalid parameter
 *			that the app_control does not have the extra data, and then checks the return value.
 */
int utc_application_app_control_get_extra_data_array_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *array_key = "array_key";
	char **out_array;
	int out_length = -1;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data_array(app_control, array_key, &out_array, &out_length);
	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_KEY_NOT_FOUND);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_array_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the extra data array from the app_control.
 * @scenario		Calls the app_control_get_extra_data_array() with the invalid parameter
 *			that the app_control is NULL, and then checks the return value.
 */
int utc_application_app_control_get_extra_data_array_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *array_key = "array_key";
	const char *array_value[] = {"array_value1", "array_value2", "array_value3", "array_value4"};
	int array_length = 4;
	char **out_array = NULL;
	int out_length = -1;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	app_control_add_extra_data_array(app_control, array_key, array_value, array_length);

	ret = app_control_get_extra_data_array(NULL, array_key, &out_array, &out_length);
	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_array_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the extra data array from the app_control.
 * @scenario		Calls the app_control_get_extra_data_arrary() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_app_control_get_extra_data_array_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *array_key = "array_key";
	const char *array_value[] = {"array_value1", "array_value2", "array_value3", "array_value4"};
	int array_length = 4;
	char **out_array = NULL;
	int out_length = -1;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	app_control_add_extra_data_array(app_control, array_key, array_value, array_length);

	ret = app_control_get_extra_data_array(app_control, NULL, &out_array, &out_length);
	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_array_n4
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the extra data array from the app_control.
 * @scenario		Calls the app_control_get_extra_data_array() with the invalid parameter
 *			that the value is NULL, and then checks the return value.
 */
int utc_application_app_control_get_extra_data_array_n4(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *array_key = "array_key";
	const char *array_value[] = {"array_value1", "array_value2", "array_value3", "array_value4"};
	int array_length = 4;
	int out_length = -1;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data_array(app_control, array_key, array_value, array_length);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data_array(app_control, array_key, NULL, &out_length);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_extra_data_array_n5
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the extra data array from the app_control.
 * @scenario		Calls the app_control_get_extra_data_array() with the invalid parameter
 *			that the length is NULL, and then checks the return value.
 */
int utc_application_app_control_get_extra_data_array_n5(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *array_key = "array_key";
	const char *array_value[] = {"array_value1", "array_value2", "array_value3", "array_value4"};
	int array_length = 4;
	char **out_array = NULL;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data_array(app_control, array_key, array_value, array_length);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_extra_data_array(app_control, array_key, &out_array, NULL);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_is_extra_data_array_p1
 * @since_tizen		2.3
 * @type		Positive
 * @description		Checks whether the extra data associated with the given @a key is of array data type.
 * @scenario		Adds the extra data array and checks the extra data array.
 */
int utc_application_app_control_is_extra_data_array_p1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *array_key = "array_key";
	const char* array_value[] = {"array_value1", "array_value2", "array_value3", "array_value4"};
	int array_length = 4;
	bool is_array;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data_array(app_control, array_key, array_value, array_length);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_is_extra_data_array(app_control, array_key, &is_array);
	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_eq_with_exit(is_array, true);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_is_extra_data_array_p2
 * @since_tizen		2.3
 * @type		Positive
 * @description		Checks whether the extra data associated with the given @a key is of array data type.
 * @scenario		Adds the extra data and checks the extra data array.
 *			The return value is false.
 */
int utc_application_app_control_is_extra_data_array_p2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key = "EXTRA_KEY";
	char *value = "EXTRA_VALUE";
	bool is_array;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data(app_control, key, value);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_is_extra_data_array(app_control, key, &is_array);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_eq_with_exit(is_array, false);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_is_extra_data_array_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Checks whether the extra data associated with the given @a key is of array data type.
 * @scenario		Calls the app_control_is_extra_data_array() with the invalid parameter
 *			that the app_control is NULL, and then checks the return value.
 */
int utc_application_app_control_is_extra_data_array_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *key = "key";
	bool is_array;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_is_extra_data_array(NULL, key, &is_array);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_is_extra_data_array_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Checks whether the extra data associated with the given @a key is of array data type.
 * @scenario		Calls the app_control_is_extra_data_array() with the invalid parameter
 *			that the key is NULL, and then checks the return value.
 */
int utc_application_app_control_is_extra_data_array_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	bool is_array;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_is_extra_data_array(app_control, NULL, &is_array);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_is_extra_data_array_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Checks whether the extra data associated with the given @a key is of array data type.
 * @scenario		Calls the app_control_is_extra_data_array() with the invalid parameter
 *			that the array is NULL, and then checks the return value.
 */
int utc_application_app_control_is_extra_data_array_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *key = "key";
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_is_extra_data_array(app_control, key, NULL);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_is_extra_data_array_n4
 * @since_tizen		2.3
 * @type		Negative
 * @description		Checks whether the extra data associated with the given @a key is of array data type.
 * @scenario		Calls the app_control_is_extra_data_array() with the invalid key.
 */
int utc_application_app_control_is_extra_data_array_n4(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *key = "__APP_SVC_KEY";

	bool is_array;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_is_extra_data_array(app_control, key, &is_array);

	app_control_destroy(app_control);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_KEY_REJECTED);
	normal_exit(0);

	return 0;
}

int dts_app_control_host_res_fn(void *data)
{
	return 0;
}

/**
 * @testcase		utc_application_app_control_is_reply_requested_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Checks whether the caller is requesting a reply from the launch request.
 * @scenario		Calls the app_control_is_replay_requested() with the invalid parameter.
 */
int utc_application_app_control_is_reply_requested_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_h app_control;
	bool requested;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_is_reply_requested(app_control, &requested);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_is_reply_requested_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Checks whether the caller is requesting a reply from the launch request.
 * @scenario		Calls the app_control_is_reply_requested() with the invalid parameter.
 */
int utc_application_app_control_is_reply_requested_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_is_reply_requested(app_control, NULL);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_is_reply_requested_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Checks whether the caller is requesting a reply from the launch request.
 * @scenario		Calls the app_control_is_reply_requested() with the invalid parameter.
 */
int utc_application_app_control_is_reply_requested_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	bool requested = false;

	ret = app_control_is_reply_requested(NULL, &requested);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_is_reply_requested_n4
 * @since_tizen		2.3
 * @type		Negative
 * @description		Checks whether the caller is requesting a reply from the launch request.
 * @scenario		Calls the app_control_is_reply_requested() with the invalid parameters.
 */
int utc_application_app_control_is_reply_requested_n4(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_is_reply_requested(NULL, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_caller_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the application ID of the caller from the launch request.
 * @scenario		Calls the app_control_get_caller() with the invalid parameter.
 */
int utc_application_app_control_get_caller_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_caller(app_control, NULL);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_caller_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the application ID of the caller from the launch request.
 * @scenario		Calls the app_control_get_caller() with the invalid parameter.
 */
int utc_application_app_control_get_caller_n2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	char *caller = NULL;

	ret = app_control_get_caller(NULL, &caller);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_caller_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the application ID of the caller from the launch request.
 * @scenario		Calls the app_control_get_caller() with the invalid parameters.
 */
int utc_application_app_control_get_caller_n3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_get_caller(NULL, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_send_terminate_request_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sends the terminate request to the application that is launched
 *			by app_control. This API is only effective for some applications that
 *			are provided by default for handling platform default app_controls.
 *			You are not allowed to terminate other general applications using this API.
 * @scenario		Sends the launch request and send the terminate request.
 */
int utc_application_app_control_send_terminate_request_p(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *app_id = "org.tizen.helloworld";
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	// explicit launch without reply callback
	ret = app_control_send_launch_request(app_control, NULL, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	usleep(1000000);

	ret = app_control_send_terminate_request(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_send_terminate_request_n
 * @since_tizen		2.3
 * @type		Negative
 * @description         Sends the terminate request to the application that is launched
 *                      by app_control. This API is only effective for some applications that
 *                      are provided by default for handling platform default app_controls.
 *                      You are not allowed to terminate other general applications using this API.
 * @scenario		Calls the app_control_send_terminate_request() with the invalid parameter.
 */
int utc_application_app_control_send_terminate_request_n(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_send_terminate_request(NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_launch_mode_p1
 * @since_tizen		2.4
 * @type		Positive
 * @description		Sets the launch mode of the application.
 * @scenario		Creates an app_control handle and sets the launch mode.
 */
int utc_application_app_control_set_launch_mode_p1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_launch_mode(app_control,
			APP_CONTROL_LAUNCH_MODE_SINGLE);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_launch_mode_p2
 * @since_tizen		2.4
 * @type		Positive
 * @description		Sets the launch mode of the application.
 * @scenario		Creates an app_control_handle and sets the launch mode.
 */
int utc_application_app_control_set_launch_mode_p2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_launch_mode(app_control,
			APP_CONTROL_LAUNCH_MODE_GROUP);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_launch_mode_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		Sets the launch mode of the application.
 * @scenario		Calls the app_control_set_launch_mode() with the invalid parameter.
 */
int utc_application_app_control_set_launch_mode_n(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_launch_mode(app_control, -1);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_launch_mode_p1
 * @since_tizen		2.4
 * @type		Positive
 * @description		Gets the launch mode of the application.
 * @scenario		Sets the launch mode and gets the launch mode.
 */
int utc_application_app_control_get_launch_mode_p1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_launch_mode_e mode;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_launch_mode(app_control,
			APP_CONTROL_LAUNCH_MODE_SINGLE);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_launch_mode(app_control, &mode);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_launch_mode_p2
 * @since_tizen		2.4
 * @type		Positive
 * @description		Gets the launch mode of the application.
 * @scenario		Sets the launch mode and gets the launch mode.
 */
int utc_application_app_control_get_launch_mode_p2(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_launch_mode_e mode;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_launch_mode(app_control,
		APP_CONTROL_LAUNCH_MODE_GROUP);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_launch_mode(app_control, &mode);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_launch_mode_p3
 * @since_tizen		2.4
 * @remarks Since Tizen 3.0, if launch mode not set in the caller app control,
 *	the function returns #APP_CONTROL_LAUNCH_MODE_SINGLE launch mode.
 * @type		Positive
 * @description		Gets the launch mode of the application.
 * @scenario		Gets the launch mode.
 */
int utc_application_app_control_get_launch_mode_p3(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_launch_mode_e mode;

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_launch_mode(app_control, &mode);

	app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_get_launch_mode_n1
 * @since_tizen		2.4
 * @type		Negative
 * @description		Gets the launch mode of the application.
 * @scenario		Calls the app_control_get_launch_mode() with the invalid parameter.
 */
int utc_application_app_control_get_launch_mode_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_launch_mode_e mode;

	ret = app_control_get_launch_mode(NULL, &mode);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

static void dts_app_control_launch_reply_cb(app_control_h request, app_control_h reply,
				app_control_result_e result, void *user_data)
{
	char *app_id = NULL;
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_get_app_id(reply, &app_id);
	if (ret != APP_CONTROL_ERROR_NONE) {
		normal_exit(1);
		return;
	}

	if (result != APP_CONTROL_RESULT_APP_STARTED) {
		normal_exit(1);
		return;
	}

	if (strcmp(app_id, "org.tizen.helloworld") != 0) {
		normal_exit(1);
		return;
	}

	normal_exit(0);
}

/**
 * @testcase		utc_application_app_control_enable_app_started_result_event_p1
 * @since_tizen		2.4
 * @type		Positive
 * @description		Enables additional launch result event on launch request.
 * @scenario		Sets the appid and Enables additional launch result event.
 *			And then, sends the launch request.
 */
int utc_application_app_control_enable_app_started_result_event_p1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	const char *app_id = "org.tizen.helloworld";

	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_enable_app_started_result_event(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	// explicit launch with reply callback
	ret = app_control_send_launch_request(app_control, dts_app_control_launch_reply_cb, NULL);

	app_control_destroy(app_control);
	return 0;
}

/**
 * @testcase		utc_application_app_control_enable_app_started_result_event_n1
 * @since_tizen		2.4
 * @type		Negative
 * @description		Enables additional launch result event on launch request.
 * @scenario		Calls the app_control_enable_app_started_result_event() with the invalid parameter.
 */
int utc_application_app_control_enable_app_started_result_event_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_enable_app_started_result_event(NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

static void __app_control_result_cb(app_control_h request,
		app_control_error_e result, void *user_data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "Result: %d", result);
	if (result == APP_CONTROL_ERROR_NONE)
		normal_exit(0);
	else
		normal_exit(1);
}

/**
 * @testcase            utc_application_app_control_send_launch_request_async_p1
 * @since_tizen         5.0
 * @type                Positive
 * @description         Sends the launch request asynchronously.
 * @scenario            Sends the launch request asynchronously.
 */
int utc_application_app_control_send_launch_request_async_p1(void)
{
	app_control_h handle;
	int ret;

	ret = app_control_create(&handle);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create app control handle");
		normal_exit(1);
		return -1;
	}

	ret = app_control_set_operation(handle,
			APP_CONTROL_OPERATION_DEFAULT);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set operation");
		normal_exit(1);
		goto end;
	}

	ret = app_control_set_app_id(handle, "org.tizen.helloworld");
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set application ID");
		normal_exit(1);
		goto end;
	}

	ret = app_control_send_launch_request_async(handle, __app_control_result_cb,
			NULL, NULL);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to send launch request async");
		normal_exit(1);
	}

end:
	app_control_destroy(handle);

	return ret;
}

static void __app_control_reply_cb(app_control_h request, app_control_h reply,
		app_control_result_e result, void *user_data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "Result: %d", result);
	if (result == APP_CONTROL_RESULT_SUCCEEDED)
		normal_exit(0);
	else
		normal_exit(1);
}

static void __app_control_result_cb_with_reply(app_control_h request,
		app_control_error_e result, void *user_data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "Result: %d", result);
	if (result != APP_CONTROL_ERROR_NONE)
		normal_exit(1);
}


/**
 * @testcase            utc_application_app_control_send_launch_request_async_p2
 * @since_tizen         5.0
 * @type                Positive
 * @description         Sends the launch request asynchronously.
 * @scenario            Sends the launch request asynchronously with the reply callback.
 */
int utc_application_app_control_send_launch_request_async_p2(void)
{
	app_control_h handle;
	int ret;

	ret = app_control_create(&handle);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create app control handle");
		normal_exit(1);
		return -1;
	}

	ret = app_control_set_operation(handle,
			APP_CONTROL_OPERATION_DEFAULT);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set operation");
		normal_exit(1);
		goto end;
	}

	ret = app_control_set_app_id(handle, "org.example.reply");
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set application ID");
		normal_exit(1);
		goto end;
	}

	ret = app_control_send_launch_request_async(handle,
			__app_control_result_cb_with_reply,
			__app_control_reply_cb, NULL);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to send launch request async");
		normal_exit(1);
	}

end:
	app_control_destroy(handle);

	return ret;
}

/**
 * @testcase            utc_application_app_control_send_launch_request_async_p3
 * @since_tizen         5.0
 * @type                Positive
 * @description         Sends the launch request asynchronously..
 * @scenario            Sets the operation, the mime and the appid,
 *                      and then sends the launch request asynchronously.
 */
int utc_application_app_control_send_launch_request_async_p3(void)
{
	app_control_h handle;
	int ret;

	ret = app_control_create(&handle);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create app control handle");
		normal_exit(1);
		return -1;
	}

	ret = app_control_set_operation(handle,
			APP_CONTROL_OPERATION_DEFAULT);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set operation");
		normal_exit(1);
		goto end;
	}

	ret = app_control_set_mime(handle, "type/custom");
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set MIME-Type");
		normal_exit(1);
		goto end;
	}

	ret = app_control_set_app_id(handle, "org.tizen.helloworld");
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set application ID");
		normal_exit(1);
		goto end;
	}

	ret = app_control_send_launch_request_async(handle, __app_control_result_cb,
			NULL, NULL);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to send launch request async");
		normal_exit(1);
	}

end:
	app_control_destroy(handle);

	return ret;
}

/**
 * @testcase            utc_application_app_control_send_launch_request_async_p4
 * @since_tizen         5.0
 * @type                Positive
 * @description         Sends the launch request asynchronously.
 * @scenario            Sets the operation, the appid, and then sends the
 *                      launch request asynchronously. This target application requires
 *                      privilege(http://tizen.org/privilege/alarm.get) to
 *                      send app_control.
 */
int utc_application_app_control_send_launch_request_async_p4(void)
{
	app_control_h handle;
	int ret;

	ret = app_control_create(&handle);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create app control handle");
		normal_exit(1);
		return -1;
	}

	ret = app_control_set_operation(handle,
			APP_CONTROL_OPERATION_DEFAULT);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set operation");
		normal_exit(1);
		goto end;
	}

	ret = app_control_set_app_id(handle, "org.example.appcontrolprivilegetest");
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set application ID");
		normal_exit(1);
		goto end;
	}

	ret = app_control_send_launch_request_async(handle, __app_control_result_cb,
			NULL, NULL);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to send launch request async");
		normal_exit(1);
	}

end:
	app_control_destroy(handle);

	return ret;
}

/**
 * @testcase            utc_application_app_control_send_launch_request_async_n1
 * @since_tizen         5.0
 * @type                Negative
 * @description         Sends the launch request asynchronously.
 * @scenario            Calls the app_control_send_launch_request() with the invalid parameters.
 */
int utc_application_app_control_send_launch_request_async_n1(void)
{
	app_control_h handle;
	int ret;

	ret = app_control_create(&handle);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create app control handle");
		normal_exit(1);
		return -1;
	}

	ret = app_control_send_launch_request_async(NULL, NULL, NULL, NULL);
	if (ret != APP_CONTROL_ERROR_INVALID_PARAMETER) {
		dlog_print(DLOG_ERROR, LOG_TAG, "error: %d", ret);
		normal_exit(1);
		goto end;
	}

	ret = app_control_send_launch_request_async(handle, NULL, NULL, NULL);
	if (ret != APP_CONTROL_ERROR_INVALID_PARAMETER) {
		dlog_print(DLOG_ERROR, LOG_TAG, "error: %d", ret);
		normal_exit(1);
		goto end;
	}

	normal_exit(0);

end:
	app_control_destroy(handle);

	return 0;
}

/**
 * @testcase		utc_application_app_control_send_launch_request_async_n2
 * @since_tizen		5.0
 * @type                Negative
 * @description         Sends the launch request asynchronously.
 * @scenario            Sends the launch request without the given appid.
 *                      If the operation is APP_CONTROL_OPERATION_DEFAULT,
 *                      the app_control requires the appid for sending the launch request asynchronously.
 */
int utc_application_app_control_send_launch_request_async_n2(void)
{
	app_control_h handle;
	int ret;

	ret = app_control_create(&handle);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create app control handle");
		normal_exit(1);
		return -1;
	}

	ret = app_control_set_operation(handle,
			APP_CONTROL_OPERATION_DEFAULT);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set operation");
		normal_exit(1);
		goto end;
	}

	ret = app_control_send_launch_request_async(handle, __app_control_result_cb,
			NULL, NULL);
	if (ret != APP_CONTROL_ERROR_APP_NOT_FOUND) {
		dlog_print(DLOG_ERROR, LOG_TAG, "error: %d", ret);
		normal_exit(1);
	}
	normal_exit(0);

end:
	app_control_destroy(handle);

	return 0;
}

static void __app_control_result_cb_n3(app_control_h request,
		app_control_error_e result, void *user_data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "Result: %d", result);
	if (result == APP_CONTROL_ERROR_APP_NOT_FOUND)
		normal_exit(0);
	else
		normal_exit(1);
}

/**
 * @testcase            utc_application_app_control_send_launch_request_async_n3
 * @since_tizen         5.0
 * @type                Negative
 * @description         Sends the launch request asynchronously.
 * @scenario            Sends the launch request asynchronously with the invalid appid.
 */
int utc_application_app_control_send_launch_request_async_n3(void)
{
	app_control_h handle;
	int ret;

	ret = app_control_create(&handle);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create app control handle");
		normal_exit(1);
		return -1;
	}

	ret = app_control_set_operation(handle,
			APP_CONTROL_OPERATION_DEFAULT);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set operation");
		normal_exit(1);
		goto end;
	}

	ret = app_control_set_app_id(handle, "org.tizen.hellohelloworld");
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set application ID");
		normal_exit(1);
		goto end;
	}

	ret = app_control_send_launch_request_async(handle,
			__app_control_result_cb_n3,
			NULL, NULL);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "error: %d", ret);
		normal_exit(1);
	}

end:
	app_control_destroy(handle);

	return 0;
}

static void __app_control_result_cb_n4(app_control_h request,
		app_control_error_e result, void *user_data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "Result: %d", result);
	if (result == APP_CONTROL_ERROR_PERMISSION_DENIED)
		normal_exit(0);
	else
		normal_exit(1);
}

/**
 * @testcase            utc_application_app_control_send_launch_request_async_n4
 * @since_tizen         5.0
 * @type                Negative
 * @description         Sends the launch request asynchronously.
 * @scenario            Sends the launch request asynchronously to application which requires
 *                      privilege(http://tizen.org/privilege/notification).
 */
int utc_application_app_control_send_launch_request_async_n4(void)
{
	app_control_h handle;
	int ret;

	ret = app_control_create(&handle);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create app control handle");
		normal_exit(1);
		return -1;
	}

	ret = app_control_set_operation(handle,
			APP_CONTROL_OPERATION_DEFAULT);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set operation");
		normal_exit(1);
		goto end;
	}

	ret = app_control_set_app_id(handle, "org.example.appcontrolprivilegetest2");
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set application ID");
		normal_exit(1);
		goto end;
	}

	ret = app_control_send_launch_request_async(handle,
			__app_control_result_cb_n4,
			NULL, NULL);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "error: %d", ret);
		normal_exit(1);
	}

end:
	app_control_destroy(handle);

	return 0;
}

/**
 * @testcase            utc_application_app_control_create_with_parameters_p
 * @since_tizen         5.5
 * @type                Positive
 * @description         Creates an app_control handle and sets its attributes.
 * @scenario            Creates an app_control handle and sets its attributes.
 *                      The application ID is "org.tizen.test", the launch mode is "Single",
 *                      the extra data are "key1"-"value1" and "key2"-"value2".
 */
int utc_application_app_control_create_with_parameters_p(void)
{
	app_control_h handle = NULL;
	char *app_id = NULL;
	char *value = NULL;
	int ret;

	ret = app_control_create_with_parameters(&handle,
			NULL, NULL, NULL, NULL,
			"org.tizen.test", APP_CONTROL_LAUNCH_MODE_SINGLE, 2,
			"key1", "value1", "key2", "value2");
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to create appcontrol handle. error: %d",
				ret);
		normal_exit(1);
		return -1;
	}

	ret = app_control_get_app_id(handle, &app_id);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to get app id. error: %d", ret);
		app_control_destroy(handle);
		normal_exit(1);
		return -1;
	}
	free(app_id);

	ret = app_control_get_extra_data(handle, "key1", &value);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to get extra data. error: %d", ret);
		app_control_destroy(handle);
		normal_exit(1);
		return -1;
	}
	free(value);

	app_control_destroy(handle);
	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_create_with_parameters_n
 * @since_tizen         5.5
 * @type                Negative
 * @description         Creates an app_control handle and sets its attributes.
 * @scenario            Creates an app_control handle with invalid parameters.
 *                      The function returns a negative error value.
 *                      It's APP_CONTROL_ERROR_INVALID_PARAMETER.
 */
int utc_application_app_control_create_with_parameters_n(void)
{
	int ret;

	ret = app_control_create_with_parameters(NULL,
			NULL, NULL, NULL, NULL,
			NULL, APP_CONTROL_LAUNCH_MODE_SINGLE, 1,
			"key", "value");
	if (ret != APP_CONTROL_ERROR_INVALID_PARAMETER) {
		dlog_print(DLOG_ERROR, LOG_TAG, "error: %d", ret);
		normal_exit(1);
		return -1;
	}

	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_send_launch_request_sync_p
 * @since_tizen         5.5
 * @type                Positive
 * @description         Sends the launch request synchronously.
 * @scenario            Sends the launch request synchronously.
 *                      If the callee application doesn't response,
 *                      the function returns a negative error value.
 *
 */
int utc_application_app_control_send_launch_request_sync_p(void)
{
	app_control_h handle = NULL;
	app_control_h reply = NULL;
	app_control_result_e result;
	int ret;

	ret = app_control_create_with_parameters(&handle,
			APP_CONTROL_OPERATION_DEFAULT,
			NULL, NULL, NULL,
			"org.example.reply", APP_CONTROL_LAUNCH_MODE_SINGLE,
			0);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create app control handle");
		normal_exit(1);
		goto end;
	}

	ret = app_control_send_launch_request_sync(handle, &reply, &result);
	if (ret != APP_CONTROL_ERROR_NONE || result != APP_CONTROL_RESULT_SUCCEEDED) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to send launch request async");
		normal_exit(1);
		goto end;
	}

	normal_exit(0);
end:
	if (reply)
		app_control_destroy(reply);
	if (handle)
		app_control_destroy(handle);

	return ret;
}

/**
 * @testcase            utc_application_app_control_send_launch_request_sync_n1
 * @since_tizen         5.5
 * @type                Negative
 * @description         Sends the launch request synchronously.
 * @scenario            Calls app_control_send_launch_request_sync() with nullptrs.
 *                      The function returns APP_CONTROL_ERROR_INVALID_PARAMETER.
 */
int utc_application_app_control_send_launch_request_sync_n1(void)
{
	int ret;

	ret = app_control_send_launch_request_sync(NULL, NULL, NULL);
	if (ret != APP_CONTROL_ERROR_INVALID_PARAMETER) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		normal_exit(1);
		return -1;
	}

	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_send_launch_request_sync_n2
 * @since_tizen         5.5
 * @type                Negative
 * @description         Sends the launch request synchronously.
 * @scenario            Sends the launch request synchronously.
 *                      The callee application doesn't response.
 *                      And then, the function returns a negative error value.
 *                      If the callee application sends the reply, the function
 *                      returns APP_CONTROL_ERROR_NONE.
 */
int utc_application_app_control_send_launch_request_sync_n2(void)
{
	app_control_h handle = NULL;
	app_control_h reply = NULL;
	app_control_result_e result;
	int ret;

	ret = app_control_create_with_parameters(&handle,
			APP_CONTROL_OPERATION_DEFAULT,
			NULL, NULL, NULL,
			"org.tizen.helloworld", APP_CONTROL_LAUNCH_MODE_SINGLE,
			0);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create app control handle");
		normal_exit(1);
		goto end;
	}

	ret = app_control_send_launch_request_sync(handle, &reply, &result);
	if (ret == APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		normal_exit(1);
		goto end;
	}

	normal_exit(0);
end:
	if (reply)
		app_control_destroy(reply);
	if (handle)
		app_control_destroy(handle);

	return 0;
}

static void __action_cb(const char *action, app_control_h app_control,
		void *user_data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "action: %s", action);
}

/**
 * @testcase            utc_application_app_control_add_action_handler_p
 * @since_tizen         5.5
 * @type                Positive
 * @description         Adds the app-control action handle.
 * @scenario            Calls app_control_add_action_handler().
 *                      And then, checks the return value.
 *                      The action name must be defined in the tizen-manifest.xml
 */
int utc_application_app_control_add_action_handler_p(void)
{
	app_control_action_h handle = NULL;
	int ret;

	ret = app_control_add_action_handler("action", __action_cb, NULL,
			&handle);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to add action handler");
		normal_exit(1);
		return -1;
	}

	app_control_remove_action_handler(handle);
	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_add_action_handler_n1
 * @since_tizen         5.5
 * @type                Negative
 * @description         Adds the app-control action handle.
 * @scenario            Calls app_control_remove_action_handler() with null parameter.
 */
int utc_application_app_control_add_action_handler_n1(void)
{
	app_control_action_h handle = NULL;
	int ret;

	ret = app_control_add_action_handler(NULL, __action_cb, NULL,
			&handle);
	if (ret != APP_CONTROL_ERROR_INVALID_PARAMETER) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		normal_exit(1);
		return -1;
	}

	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_add_action_handler_n2
 * @since_tizen         5.5
 * @type                Negative
 * @description         Adds the app-control action handle.
 * @scenario            Calls app_control_remove_action_handler() with null parameter.
 */
int utc_application_app_control_add_action_handler_n2(void)
{
	app_control_action_h handle = NULL;
	int ret;

	ret = app_control_add_action_handler("action", NULL, NULL, &handle);
	if (ret != APP_CONTROL_ERROR_INVALID_PARAMETER) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		normal_exit(1);
		return -1;
	}

	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_add_action_handler_n3
 * @since_tizen         5.5
 * @type                Negative
 * @description         Adds the app-control action handle.
 * @scenario            Calls app_control_remove_action_handler() with null parameter.
 */
int utc_application_app_control_add_action_handler_n3(void)
{
	int ret;

	ret = app_control_add_action_handler("action", __action_cb, NULL, NULL);
	if (ret != APP_CONTROL_ERROR_INVALID_PARAMETER) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		normal_exit(1);
		return -1;
	}

	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_add_action_handler_n4
 * @since_tizen         5.5
 * @type                Negative
 * @description         Adds the app-control action handle.
 * @scenario            Calls app_control_remove_action_handler() with "NotFound" action key.
 *                      The function returns APP_CONTROL_ERROR_KEY_NOT_FOUND error.
 */
int utc_application_app_control_add_action_handler_n4(void)
{
	app_control_action_h handle = NULL;
	int ret;

	ret = app_control_add_action_handler("NotFound", __action_cb, NULL,
			&handle);
	if (ret != APP_CONTROL_ERROR_KEY_NOT_FOUND) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		normal_exit(1);
		return -1;
	}

	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_remove_action_handler_p
 * @since_tizen         5.5
 * @type                Positive
 * @description         Removes the registered app-control action handle.
 * @scenario            Calls app_control_add_action_handler().
 *                      And then, Calls app_control_remove_action_handler().
 */
int utc_application_app_control_remove_action_handler_p(void)
{
	app_control_action_h handle = NULL;
	int ret;

	/* Pre-condition */
	app_control_add_action_handler("action", __action_cb, NULL, &handle);

	ret = app_control_remove_action_handler(handle);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to remove action handler");
		normal_exit(1);
		return -1;
	}

	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_remove_action_handler_n
 * @since_tizen         5.5
 * @type                Negative
 * @description         Removes the registered app-control action handle.
 * @scenario            Calls app_control_remove_action_handler() with null parameter.
 */
int utc_application_app_control_remove_action_handler_n(void)
{
	int ret;

	ret = app_control_remove_action_handler(NULL);
	if (ret != APP_CONTROL_ERROR_INVALID_PARAMETER) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		normal_exit(1);
		return -1;
	}

	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_create_from_uri_handle_p
 * @since_tizen         5.5
 * @type                Positive
 * @description         Creates the app-control handle from URI handle.
 * @scenario            Creates app_control_uri_handle.
 *                      And then, Calls app_control_create_from_uri_handle()
 *                      with the URI handle.
 */
int utc_application_app_control_create_from_uri_handle_p(void)
{
	int ret;

	app_control_h app_control = NULL;
	app_control_uri_h uri = NULL;
	app_control_uri_builder_h builder = NULL;

	app_control_uri_builder_create(&builder);
	app_control_uri_builder_set_scheme(builder, "https");
	app_control_uri_builder_set_authority(builder,
			"//john.doe@www.example.com:123");
	app_control_uri_builder_set_path(builder, "/forum/questions/");
	app_control_uri_builder_set_fragment(builder, "top");
	app_control_uri_builder_add_query(builder, "tag", "networking");
	app_control_uri_builder_add_query(builder, "order", "newest");

	app_control_uri_builder_build(builder, &uri);

	ret = app_control_create_from_uri_handle(&app_control, uri);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		app_control_uri_builder_destroy(builder);
		app_control_uri_destroy(uri);
		normal_exit(1);
		return -1;
	}

	app_control_uri_builder_destroy(builder);
	app_control_uri_destroy(uri);
	app_control_destroy(app_control);

	normal_exit(0);
	return 0;
}

/**
 * @testcase            utc_application_app_control_create_from_uri_handle_n1
 * @since_tizen         5.5
 * @type                Negative
 * @description         Creates the app-control handle from URI handle.
 * @scenario            Calls app_control_create_from_uri_handle() with
 *                      app_control null parameter.
 */
int utc_application_app_control_create_from_uri_handle_n1(void)
{
	int ret;

	app_control_uri_h uri = NULL;
	app_control_uri_builder_h builder = NULL;

	app_control_uri_builder_create(&builder);
	app_control_uri_builder_set_scheme(builder, "https");
	app_control_uri_builder_set_authority(builder,
			"//john.doe@www.example.com:123");
	app_control_uri_builder_set_path(builder, "/forum/questions/");
	app_control_uri_builder_set_fragment(builder, "top");
	app_control_uri_builder_add_query(builder, "tag", "networking");
	app_control_uri_builder_add_query(builder, "order", "newest");

	app_control_uri_builder_build(builder, &uri);

	ret = app_control_create_from_uri_handle(NULL, uri);
	if (ret != APP_CONTROL_ERROR_INVALID_PARAMETER) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		app_control_uri_builder_destroy(builder);
		app_control_uri_destroy(uri);
		normal_exit(1);
		return -1;
	}

	app_control_uri_builder_destroy(builder);
	app_control_uri_destroy(uri);
	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_create_from_uri_handle_n2
 * @since_tizen         5.5
 * @type                Negative
 * @description         Creates the app-control handle from URI handle.
 * @scenario            Calls app_control_create_from_uri_handle() with
 *                      URI null parameter.
 */
int utc_application_app_control_create_from_uri_handle_n2(void)
{
	int ret;

	app_control_h app_control;

	ret = app_control_create_from_uri_handle(&app_control, NULL);
	if (ret != APP_CONTROL_ERROR_INVALID_PARAMETER) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		normal_exit(1);
		return -1;
	}

	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_set_uri_by_handle_p
 * @since_tizen         5.5
 * @type                Positive
 * @description         Sets uri to app-control by URI handle.
 * @scenario            Creates app_control_uri_handle.
 *                      And then, Calls app_control_set_uri_by_handle()
 *                      with the URI handle.
 */
int utc_application_app_control_set_uri_by_handle_p(void)
{
	int ret;

	app_control_h app_control = NULL;
	app_control_uri_h uri = NULL;
	app_control_uri_builder_h builder = NULL;

	app_control_uri_builder_create(&builder);
	app_control_uri_builder_set_scheme(builder, "https");
	app_control_uri_builder_set_authority(builder,
			"//john.doe@www.example.com:123");
	app_control_uri_builder_set_path(builder, "/forum/questions/");
	app_control_uri_builder_set_fragment(builder, "top");
	app_control_uri_builder_add_query(builder, "tag", "networking");
	app_control_uri_builder_add_query(builder, "order", "newest");

	app_control_uri_builder_build(builder, &uri);

	app_control_create(&app_control);

	ret = app_control_set_uri_by_handle(app_control, uri);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		app_control_uri_builder_destroy(builder);
		app_control_uri_destroy(uri);
		app_control_destroy(app_control);
		normal_exit(1);
		return -1;
	}

	app_control_uri_builder_destroy(builder);
	app_control_uri_destroy(uri);
	app_control_destroy(app_control);

	normal_exit(0);
	return 0;
}

/**
 * @testcase            utc_application_app_control_set_uri_by_handle_n1
 * @since_tizen         5.5
 * @type                Negative
 * @description         Sets uri to app-control by URI handle.
 * @scenario            Creates app_control_uri_handle.
 *                      And then, Calls app_control_set_uri_by_handle()
 *                      with app_control null parameter.
 */
int utc_application_app_control_set_uri_by_handle_n1(void)
{
	int ret;

	app_control_uri_h uri = NULL;
	app_control_uri_builder_h builder = NULL;

	app_control_uri_builder_create(&builder);
	app_control_uri_builder_set_scheme(builder, "https");
	app_control_uri_builder_set_authority(builder,
			"//john.doe@www.example.com:123");
	app_control_uri_builder_set_path(builder, "/forum/questions/");
	app_control_uri_builder_set_fragment(builder, "top");
	app_control_uri_builder_add_query(builder, "tag", "networking");
	app_control_uri_builder_add_query(builder, "order", "newest");

	app_control_uri_builder_build(builder, &uri);

	ret = app_control_set_uri_by_handle(NULL, uri);
	if (ret != APP_CONTROL_ERROR_INVALID_PARAMETER) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		app_control_uri_builder_destroy(builder);
		app_control_uri_destroy(uri);
		normal_exit(1);
		return -1;
	}

	app_control_uri_builder_destroy(builder);
	app_control_uri_destroy(uri);
	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_control_set_uri_by_handle_n2
 * @since_tizen         5.5
 * @type                Negative
 * @description         Sets uri to app-control by URI handle.
 * @scenario            Creates app_control_uri_handle.
 *                      And then, Calls app_control_set_uri_by_handle()
 *                      with URI null parameter.
 */
int utc_application_app_control_set_uri_by_handle_n2(void)
{
	int ret;

	app_control_h app_control;

	app_control_create(&app_control);

	ret = app_control_set_uri_by_handle(app_control, NULL);
	if (ret != APP_CONTROL_ERROR_INVALID_PARAMETER) {
		app_control_destroy(app_control);
		dlog_print(DLOG_ERROR, LOG_TAG, "Error: %d", ret);
		normal_exit(1);
		return -1;
	}

	app_control_destroy(app_control);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_control_set_component_id_p1
 * @since_tizen		5.5
 * @type		Positive
 * @description		Sets component ID to app-control.
 * @scenario		Sets the component ID.
 */
int utc_application_app_control_set_component_id_p1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_h app_control;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_component_id(app_control, "comp_id");
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	app_control_destroy(app_control);
	normal_exit(0);
	return 0;
}

/**
 * @testcase            utc_application_app_control_set_component_id_n1
 * @since_tizen         5.5
 * @type                Negative
 * @description         Sets component ID to app-control.
 * @scenario            Sets component ID with NULL value.
 */
int utc_application_app_control_set_component_id_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_set_component_id(NULL, "comp_id");
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_application_app_control_get_component_id_p1
 * @since_tizen		5.5
 * @type		Positive
 * @description		Gets the component ID from app-control
 * @scenario		Create app-control with a component ID.
 *                      Sets component ID and gets component ID from it.
 *                      Check returned value.
 */
int utc_application_app_control_get_component_id_p1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;
	app_control_h app_control;
	char *comp_id;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_component_id(app_control, "comp_id");
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_get_component_id(app_control, &comp_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);
	assert_with_exit(!strcmp(comp_id, "comp_id"));

	app_control_destroy(app_control);
	normal_exit(0);
	return 0;
}

/**
 * @testcase            utc_application_app_control_get_component_id_n1
 * @since_tizen         5.5
 * @type                Negative
 * @description         Gets component ID to app-control.
 * @scenario            Gets component ID with NULL value.
 */
int utc_application_app_control_get_component_id_n1(void)
{
	int ret = APP_CONTROL_ERROR_NONE;

	ret = app_control_get_component_id(NULL, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_INVALID_PARAMETER);
	normal_exit(0);
	return 0;
}