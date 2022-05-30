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
#include <app_manager.h>
#include <app_context.h>
#include <app_info.h>
#include <system_info.h>
#include <stdbool.h>
#include <string.h>
#include <app.h>
#include <glib.h>
#include "tct_app_common.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "NativeTCT"

#define TEST_APPID "org.tizen.helloworld"
#define TEST_APPID2 "org.tizen.helloworld2"
#define TEST_MULTIRES_ICON_APPID "org.tizen.multiresolutionicon"

#define SHARED_TRUSTED_TEST_APPID "org.tizen.sharedtrustedchecker"
#define SHARED_APPID "org.tizen.sharedtrustedtest"
#define NON_SHARED_APPID "org.tizen.nonsharedtrustedtest"
#define TIMEOUT_CB 15000

GMainLoop *g_MainLoop;
int g_nTimeoutId;
bool g_bRequestCBCallbackHit;
int test_ret;
int test_err;

gboolean TimeoutFunction(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if (pMainLoop != NULL)
		g_main_loop_quit(pMainLoop);

	return false;
}

#define RUN_POLLING_LOOP {\
	g_MainLoop = g_main_loop_new(NULL, false); \
		g_nTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, g_MainLoop); \
		g_main_loop_run(g_MainLoop); \
		g_source_remove(g_nTimeoutId); \
		g_MainLoop = NULL; \
		g_nTimeoutId = 0; \
}

#define QUIT_GMAIN_LOOP { \
	if (g_MainLoop) { \
		g_main_loop_quit(g_MainLoop); \
			g_MainLoop = NULL; \
	} \
}

static app_context_h app_context = NULL;

static void event_cb(const char *type, const char *app_id,
		app_manager_event_type_e event_type,
		app_manager_event_state_e event_state,
		app_manager_event_h handle, void *user_data)
{
	return;
}

static void reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	if (result == APP_CONTROL_RESULT_SUCCEEDED)
		fprintf(stderr, "org.tizen.helloworld was Launched!!");
	else
		fprintf(stderr, "Failed to launch org.tizen.helloworld!!");
}

/**
 * @function		utc_app_manager_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_app_manager_startup(void)
{
	bool running = false;
	app_control_h request;
	int ret = APP_ERROR_NONE;

	app_manager_is_running(TEST_APPID, &running);
	if (!running) {
		app_control_create(&request);
		if (!request) {
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "app_control_create() failed (code: %d)\n", ret);
			return;
		}

		ret = app_control_set_app_id(request, TEST_APPID);
		if (ret != APP_ERROR_NONE) {
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "app_control_set_app_id() failed (code: %d)\n", ret);
			return;
		}

		ret = app_control_send_launch_request(request, reply_cb, NULL);
		if (ret != APP_ERROR_NONE) {
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "app_control_send_launch_request() failed (code: %d)\n", ret);
			return;
		}
	}

	TCT_UTCCheckInstalledApp(4, TEST_APPID, TEST_APPID2, "org.tizen.shared_data", "org.example.componentbased");
}

/**
 * @function		utc_app_manager_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_app_manager_cleanup(void)
{
	if (app_context) {
		app_context_destroy(app_context);
	}
}

static bool metadata_cb(const char *key, const char *value, void *user_data)
{
	return true;
}

static bool filter_cb(app_info_h app_info, void *user_data)
{
	return true;
}

static bool res_control_cb(const char *res_type,
		const char *min_res_version, const char *max_res_version,
		const char *auto_close, void *user_data)
{
	return true;
}

/**
 * @testcase		utc_app_manager_app_context_clone_p
 * @since_tizen		2.3
 * @description		Clones the application context handle.
 * @scenario		Get app_context and clone. After check cloned handle, destroy it.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_clone_p(void)
{
	int ret = 0;
	app_context_h app_context_cloned = NULL;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_context_clone(&app_context_cloned, app_context);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	if (app_context_cloned) {
		app_context_destroy(app_context_cloned);
	}

	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_clone_n
 * @since_tizen		2.3
 * @description		Clones the application context handle.
 * @scenario		Clone the app_context with no handle.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_clone_n(void)
{
	int ret = 0;
	app_context_h app_context_cloned = NULL;

	ret = app_context_clone(&app_context_cloned, NULL);
	assert_neq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_destroy_p
 * @since_tizen		2.3
 * @description		Destroys the application context handle and releases all its resources.
 * @scenario		Get app_context and destroy it.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_destroy_p(void)
{
	int ret = 0;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_context_destroy(app_context);
	app_context = NULL;
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_destroy_n
 * @since_tizen		2.3
 * @description		If there is no object to destroy, func has to return an error.
 * @scenario		Call app_context_destory func with no handle of app_context.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_destroy_n(void)
{
	int ret = 0;

	ret = app_context_destroy(NULL);
	assert_neq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_get_app_id_p
 * @since_tizen		2.3
 * @description		Gets the application ID with the given application context.
 * @scenario		Get app_context and get app_id from context handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_get_app_id_p(void)
{
	int ret = 0;
	char *app_id = NULL;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_context_get_app_id(app_context, &app_id);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	free(app_id);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_get_app_id_n
 * @since_tizen		2.3
 * @description		If there is no object to get an an app id, func has to return an error.
 * @scenario		Call app_context_get_app_id func with handle of app_context.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_get_app_id_n(void)
{
	int ret = 0;
	char *app_id = NULL;

	ret = app_context_get_app_id(NULL, &app_id);
	assert_neq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_get_package_p
 * @since_tizen		2.3
 * @description		Gets the package with the given application context.
 * @scenario		Get app_context for TEST_APPID and get package from it.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_get_package_p(void)
{
	int ret = 0;
	char *package = NULL;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_context_get_package(app_context, &package);
	free(package);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_get_package_n
 * @since_tizen		2.3
 * @description		If there is no object to get pacakge, func has to return an error.
 * @scenario		Call app_context_get_package func with no handle of app_context.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_get_package_n(void)
{
	int ret = 0;
	char *package = NULL;

	ret = app_context_get_package(NULL, &package);
	assert_neq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_get_package_id_p
 * @since_tizen		3.0
 * @description		Gets the package id with the given application context.
 * @scenario		Get app_context for TEST_APPID and get package id from it.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_get_package_id_p(void)
{
	int ret = 0;
	char *package_id;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_context_get_package_id(app_context, &package_id);
	free(package_id);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}


/**
 * @testcase		utc_app_manager_app_context_get_package_id_n1
 * @since_tizen		3.0
 * @description		If there is no object to get pacakge id, func has to return an error.
 * @scenario		Call app_context_get_package_id func with no handle of app_context.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_get_package_id_n1(void)
{
	int ret = 0;
	char *package_id;

	ret = app_context_get_package_id(NULL, &package_id);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_app_manager_app_context_get_package_id_n2
 * @since_tizen         3.0
 * @description         If there is no output pointer to get pacakge id, func has to return an error.
 * @scenario            Call app_context_get_package_id func with no output pointer.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_get_package_id_n2(void)
{
	int ret = 0;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_context_get_package_id(app_context, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_get_app_state_p
 * @since_tizen		3.0
 * @description		Gets the application state with the given application context.
 * @scenario		Get app_context and get app state from context handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_get_app_state_p(void)
{
	int ret = 0;
	app_state_e state;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_context_get_app_state(app_context, &state);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_app_manager_app_context_get_app_state_n
 * @since_tizen         3.0
 * @description         If there is no object to get app state, func has to return an error.
 * @scenario            Call app_context_get_app_state func with no handle of app_context.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_get_app_state_n(void)
{
	int ret = 0;
	app_state_e state;

	ret = app_context_get_app_state(NULL, &state);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_get_pid_p
 * @since_tizen		2.3
 * @description		Gets the process ID with the given application context.
 * @scenario		Get app_context and get pid from context handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_get_pid_p(void)
{
	int ret = 0;
	int pid = 0;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_context_get_pid(app_context, &pid);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_get_pid_n
 * @since_tizen		2.3
 * @description		If there is no object to get pid, func has to return an error.
 * @scenario		Call app_context_get_pid func with no handle of app_context.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_get_pid_n(void)
{
	int ret = 0;
	int pid = 0;

	ret = app_context_get_pid(NULL, &pid);
	assert_neq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_is_equal_p
 * @since_tizen		2.3
 * @description		Checks whether two application contexts are equal.
 * @scenario		Get app_context 1, 2 and compare whether both is identical.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_is_equal_p(void)
{
	int ret = 0;
	app_context_h app_context2 = NULL;
	bool equal = false;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_manager_get_app_context(TEST_APPID, &app_context2);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_context_is_equal(app_context, app_context2, &equal);
	assert_with_exit(equal==true);

	ret = app_context_destroy(app_context2);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_is_equal_n
 * @since_tizen		2.3
 * @description		If there is no object to compare, func has to return an error.
 * @scenario		Call app_context_is_equal func with no handle of app_context.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_is_equal_n(void)
{
	int ret = app_context_is_equal(NULL, NULL, NULL);
	assert_neq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_is_terminated_p
 * @since_tizen		2.3
 * @description		Checks whether the application with the given application context is terminated.
 * @scenario		Get app_context and check whether app is terminated.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_is_terminated_p(void)
{
	int ret = 0;
	bool terminated = false;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_context_is_terminated(app_context, &terminated);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_app_context_is_terminated_n
 * @since_tizen		2.3
 * @description		If there is no object to check, func has to return an error.
 * @scenario		Call app_context_is_terminated func with no handle of app_context.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_is_terminated_n(void)
{
	int ret = 0;
	bool terminated = false;

	ret = app_context_is_terminated(NULL, &terminated);
	assert_neq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_utc_app_manager_get_external_shared_data_path_p
 * @since_tizen         3.0
 * @description         Checks whether the application with the given application is sub app of group.
 * @scenario            Get app_context and check whether app is sub app.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_is_sub_app_p(void)
{
	int ret = 0;
	bool is_sub_app = false;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_context_is_sub_app(app_context, &is_sub_app);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_utc_app_manager_get_external_shared_data_path_n
 * @since_tizen         3.0
 * @description         If there is no object to check, func has to return an error.
 * @scenario            Call app_context_is_sub_app func with no handle of app_context.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_app_context_is_sub_app_n(void)
{
	int ret = 0;
	bool is_sub_app = false;

	ret = app_context_is_sub_app(NULL, &is_sub_app);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_external_shared_data_path_p
 * @since_tizen		2.3
 * @description		Gets the absolute path to the shared trusted directory of the application specified with an application ID.
 * @scenario		Call app_manager_get_external_shared_data_path func with an app id for test.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_get_external_shared_data_path_p(void)
{
	int ret = 0;
	char *path = NULL;

	ret = app_manager_get_external_shared_data_path(TEST_APPID, &path);
	free(path);

	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_external_shared_data_path_n1
 * @since_tizen		2.3
 * @description		If there is no path to return, func has to return an error.
 * @scenario		Call app_manager_get_external_shared_data_path func with no address of path.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_external_shared_data_path_n1(void)
{
	int ret = 0;

	ret = app_manager_get_external_shared_data_path(TEST_APPID, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_external_shared_data_path_n2
 * @since_tizen		2.3
 * @description		If there is no an app id to find, func has to return an error.
 * @scenario		Call app_manager_get_external_shared_data_path func with an app id for test.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_external_shared_data_path_n2(void)
{
	int ret = 0;
	char *path = NULL;

	ret = app_manager_get_external_shared_data_path(NULL, &path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_external_shared_data_path_n3
 * @since_tizen		2.3
 * @description		If there is wrong an app id to find, func has to return an error.
 * @scenario		Call app_manager_get_external_shared_data_path func with wrong app id for test.\n
 * Check whether result is APP_MANAGER_ERROR_NO_SUCH_APP.
 */
int utc_app_manager_get_external_shared_data_path_n3(void)
{
	int ret = 0;
	char *path = NULL;

	ret = app_manager_get_external_shared_data_path("no.such.app", &path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NO_SUCH_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_data_path_p
 * @since_tizen		2.3
 * @description		Gets the absolute path to the shared data directory of the application specified with an application ID.
 * @scenario		Call app_manager_get_shared_data_path func with an app id and address of path.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_get_shared_data_path_p(void)
{
	int ret = 0;
	char *path = NULL;

	ret = app_manager_get_shared_data_path("org.tizen.shared_data", &path);
	free(path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_data_path_n1
 * @since_tizen		2.3
 * @description		If there is no path to return, func has to return an error.
 * @scenario		Call app_manager_get_shared_data_path func with no address of path.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_shared_data_path_n1(void)
{
	int ret = 0;

	ret = app_manager_get_shared_data_path(TEST_APPID, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_data_path_n2
 * @since_tizen		2.3
 * @description		If there is no an app id to find, func has to return an error.
 * @scenario		Call app_manager_get_shared_data_path func with no an app id for test.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_shared_data_path_n2(void)
{
	int ret = 0;
	char *path = NULL;

	ret = app_manager_get_shared_data_path(NULL, &path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_data_path_n3
 * @since_tizen		2.3
 * @description		If there is wrong an app id to find, func has to return an error.
 * @scenario		Call app_manager_get_shared_data_path func with wrong an app id for test.\n
 * Check whether result is APP_MANAGER_ERROR_NO_SUCH_APP.
 */
int utc_app_manager_get_shared_data_path_n3(void)
{
	int ret = 0;
	char *path = NULL;

	ret = app_manager_get_shared_data_path("no.such.app", &path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NO_SUCH_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_data_path_n4
 * @since_tizen		2.3
 * @description		If the privilege is not declared, func has to return an error.
 * @scenario		Call app_manager_get_shared_data_path func with an app id for test.\n
 * Check whether result is APP_MANAGER_ERROR_NOT_SUPPORTED.
 */
int utc_app_manager_get_shared_data_path_n4(void)
{
	int ret;
	char *path = NULL;

	ret = app_manager_get_shared_data_path(TEST_APPID, &path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NOT_SUPPORTED);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_resource_path_p
 * @since_tizen		2.3
 * @description		Gets the absolute path to the shared resource directory of the application specified with an application ID.
 * @scenario		Call app_manager_get_shared_resource_path func with an app id and address of path.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_get_shared_resource_path_p(void)
{
	int ret = 0;
	char *path = NULL;

	ret = app_manager_get_shared_resource_path(TEST_APPID, &path);
	free(path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_resource_path_n1
 * @since_tizen		2.3
 * @description		If there is no path to return, func has to return an error.
 * @scenario		Call app_manager_get_shared_resource_path func with no address of path.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_shared_resource_path_n1(void)
{
	int ret = 0;

	ret = app_manager_get_shared_resource_path(TEST_APPID, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_resource_path_n2
 * @since_tizen		2.3
 * @description		If there is no an app id to find, func has to return an error.
 * @scenario		Call app_manager_get_shared_resource_path func with no an app id for test.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_shared_resource_path_n2(void)
{
	int ret = 0;
	char *path = NULL;

	ret = app_manager_get_shared_resource_path(NULL, &path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_resource_path_n3
 * @since_tizen		2.3
 * @description		If there is wrong an app id to find, func has to return an error.
 * @scenario		Call app_manager_get_shared_resource_path func with wrong an app id for test.\n
 * Check whether result is APP_MANAGER_ERROR_NO_SUCH_APP.
 */
int utc_app_manager_get_shared_resource_path_n3(void)
{
	int ret = 0;
	char *path = NULL;

	ret = app_manager_get_shared_resource_path("no.such.app", &path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NO_SUCH_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_trusted_path_p1
 * @since_tizen		2.3
 * @description		Gets the absolute path to the shared trusted directory of the application specified with an application ID.
 * @scenario		Call app_manager_get_shared_trusted_path func with an app id and address of path.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_get_shared_trusted_path_p1(void)
{
	int ret = 0;
	char *path = NULL;

	ret = app_manager_get_shared_trusted_path(TEST_APPID, &path);
	free(path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

static void shared_trusted_reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
	char *ret_key = "__test_ret__";
	char *err_key = "__test_err__";
	char *ret = NULL;
	char *err = NULL;

	if (reply == NULL)
		QUIT_GMAIN_LOOP;

	app_control_get_extra_data(reply, ret_key, &ret);
	app_control_get_extra_data(reply, err_key, &err);

	test_ret = 1;
	test_err = 1;
	if (ret)
		test_ret = atoi(ret);
	if (err)
		test_err = atoi(err);

	g_bRequestCBCallbackHit = true;
	QUIT_GMAIN_LOOP;
}

/**
 * @testcase		utc_app_manager_get_shared_trusted_path_p2
 * @since_tizen		2.3
 * @description		Gets the absolute path to the shared trusted directory of the application specified with an application ID.
 *			If the certificate is same, success to access directory
 * @scenario		Call app_manager_get_shared_trusted_path func with an app id and address of path.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_get_shared_trusted_path_p2(void)
{
	int ret;
	app_control_h request;

	ret = app_control_create(&request);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(request, SHARED_TRUSTED_TEST_APPID);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data(request, "__test_app__", SHARED_APPID);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_send_launch_request(request, shared_trusted_reply_cb, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	g_bRequestCBCallbackHit = false;
	RUN_POLLING_LOOP;

	assert_eq_with_exit(g_bRequestCBCallbackHit, true);
	assert_eq_with_exit(test_ret, 0);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_trusted_path_n1
 * @since_tizen		2.3
 * @description		If there is no path to return, func has to return an error.
 * @scenario		Call app_manager_get_shared_trusted_path func with no address of path.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_shared_trusted_path_n1(void)
{
	int ret = 0;

	ret = app_manager_get_shared_trusted_path(TEST_APPID, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_trusted_path_n2
 * @since_tizen		2.3
 * @description		If there is no an app id to find, func has to return an error.
 * @scenario		Call app_manager_get_shared_trusted_path func with no an app id for test.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_shared_trusted_path_n2(void)
{
	int ret = 0;
	char *path = NULL;

	ret = app_manager_get_shared_trusted_path(NULL, &path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_trusted_path_n3
 * @since_tizen		2.3
 * @description		If there is wrong an app id to find, func has to return an error.
 * @scenario		Call app_manager_get_shared_trusted_path func wrong an app id for test.\n
 * Check whether result is APP_MANAGER_ERROR_NO_SUCH_APP.
 */
int utc_app_manager_get_shared_trusted_path_n3(void)
{
	int ret = 0;
	char *path = NULL;

	ret = app_manager_get_shared_trusted_path("no.such.app", &path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NO_SUCH_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_shared_trusted_path_n4
 * @since_tizen		2.3
 * @description		If certificate is different, fail to access directory.
 * @scenario		Call app_manager_get_shared_trusted_path func wrong certificate for test.\n
 * Check whether result is APP_MANAGER_ERROR_NO_SUCH_APP.
 */

int utc_app_manager_get_shared_trusted_path_n4(void)
{
	int ret;
	app_control_h request;

	ret = app_control_create(&request);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(request, SHARED_TRUSTED_TEST_APPID);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_add_extra_data(request, "__test_app__", NON_SHARED_APPID);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_send_launch_request(request, shared_trusted_reply_cb, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	g_bRequestCBCallbackHit = false;
	RUN_POLLING_LOOP;

	assert_eq_with_exit(g_bRequestCBCallbackHit, true);
	assert_eq_with_exit(test_ret, -1);
	assert_eq_with_exit(test_err, EACCES);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_app_info_app_info_clone_p
 * @since_tizen		2.3
 * @description		Clones the application information handle.
 * @scenario		Get app_info handle for test application and clone. And destroy handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_app_info_clone_p(void)
{
	app_info_h clone = NULL;
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_info_clone(&clone, app_info);
	app_info_destroy(app_info);
	app_info_destroy(clone);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_app_info_clone_n
 * @since_tizen		2.3
 * @description		If there is no source or target, func has to return an error.
 * @scenario		Call app_info_clone func with no source app_info and target app_info struct.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_app_info_clone_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_clone(NULL, NULL);
	assert_neq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_metadata_filter_add_p
 * @since_tizen		2.3
 * @description		Adds filter condition for the query API.
 * @scenario		Create filter and add key, value. And destory handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_metadata_filter_add_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_metadata_filter_h filter = NULL;
	char *key = "Test key";
	char *value = "Test value";

	ret = app_info_metadata_filter_create(&filter);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_info_metadata_filter_add(filter, key, value);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	app_info_metadata_filter_destroy(filter);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_metadata_filter_add_n
 * @since_tizen		2.3
 * @description		If there is no filter, key, value, func has to return an error.
 * @scenario		Call app_info_metadata_filter_add func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_metadata_filter_add_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_metadata_filter_add(NULL, NULL, NULL);
	assert_neq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_app_info_destroy_p
 * @since_tizen		2.3
 * @description		Destroys the application information handle and releases all its resources.
 * @scenario		Get app_info handle for test app and destroy handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_app_info_destroy_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_info_destroy(app_info);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_app_info_destroy_n
 * @since_tizen		2.3
 * @description		If there is no object to destroy, func has to return an error.
 * @scenario		Call app_info_destroy func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_app_info_destroy_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_destroy(NULL);
	assert_neq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_app_info_create_p
 * @since_tizen		2.3
 * @description		Creates the application information handle.
 * @scenario		Create app_info handle for test app and destroy handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_app_info_create_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;

	ret = app_info_create(TEST_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_destroy(app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_app_info_create_n1
 * @since_tizen		2.3
 * @description		If there is no an app id or app_info struct, func has to return an error.
 * @scenario		Call app_info_create func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_app_info_create_n1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_create(NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_app_info_create_n2
 * @since_tizen		2.3
 * @description		If there is wrong an app id, func has to return 'APP_MANAGER_ERROR_NO_SUCH_APP' an error.
 * @scenario		Call app_info_create func with wrong an app id such as "org.tizen.nosuchapp".\n
 * Check whether result is APP_MANAGER_ERROR_NO_SUCH_APP.
 */
int utc_app_info_app_info_create_n2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;

	ret = app_info_create("org.tizen.nosuchapp", &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NO_SUCH_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_app_id_p
 * @since_tizen		2.3
 * @description		Gets the application ID with the given application context.
 * @scenario		Get app_info handle for test application and get an app id from it. And destroy handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_app_id_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	char *app_id = NULL;
	app_info_h app_info = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_get_app_id(app_info, &app_id);
	app_info_destroy(app_info);
	free(app_id);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_app_id_n
 * @since_tizen		2.3
 * @description		If there is no app info or address to return, func has to return an error.
 * @scenario		Call app_info_get_app_id func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_app_id_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_get_app_id(NULL, NULL);
	assert_neq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_icon_p
 * @since_tizen		2.3
 * @description		Gets the absolute path to the icon image.
 * @scenario		Get app_info handle for test application and get path of icon. And destory handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_icon_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	char *path = NULL;
	app_info_h app_info = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_get_icon(app_info, &path);
	app_info_destroy(app_info);
	free(path);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_icon_n
 * @since_tizen		2.3
 * @description		If there is no app info or address to return, func has to retunn an error.
 * @scenario		Call app_info_get_icon func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_icon_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_get_icon(NULL, NULL);
	assert_neq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_label_p
 * @since_tizen		2.3
 * @description		Gets the label of the application.
 * @scenario		Get app_info handle for test application and get label from it. And destory handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_label_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;
	char *label = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_info_get_label(app_info, &label);
	app_info_destroy(app_info);
	free(label);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_label_n
 * @since_tizen		2.3
 * @description		If there is no app info or address to return, func has to return an error.
 * @scenario		Call app_info_get_label func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_label_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_get_label(NULL, NULL);
	assert_neq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_package_p
 * @since_tizen		2.3
 * @description		Gets the package name.
 * @scenario		Get app_info handle for test application and get pacakge name from it. And destory handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_package_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	char *package = NULL;
	app_info_h app_info = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_info_get_package(app_info, &package);
	app_info_destroy(app_info);
	free(package);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_package_n
 * @since_tizen		2.3
 * @description		If there is no app info or address to return, func has to return an error.
 * @scenario		Call app_info_get_package func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_package_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_get_package(NULL, NULL);
	assert_neq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_type_p
 * @since_tizen		2.3
 * @description		Gets the package type name.
 * @scenario		Get app_info handle for test application and get type from it. And destroy handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_type_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	char *type = NULL;
	app_info_h app_info = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_get_type(app_info, &type);
	app_info_destroy(app_info);
	free(type);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_type_n
 * @since_tizen		2.3
 * @description		If there is no app info or address to return, func has to return an error.
 * @scenario		Call app_info_get_type func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_type_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_get_type(NULL, NULL);
	assert_neq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_app_component_type_p
 * @since_tizen		4.0
 * @description		Gets the application component type.
 * @scenario		Get app_info handle for test application and get application component type from it. And destroy handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_app_component_type_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_app_component_type_e component;
	app_info_h app_info = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_get_app_component_type(app_info, &component);
	app_info_destroy(app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_app_component_type_p1
 * @since_tizen		4.0
 * @description		Gets the application component type.
 * @scenario            Calls the app_info_get_app_component_type() and checks the return value.
 *                      The component must be APP_INFO_APP_COMPONENT_TYPE_COMPONENT_BASED_APP (since 5.5).
 */
int utc_app_info_get_app_component_type_p1(void)
{
	app_info_app_component_type_e component;
	app_info_h app_info;
	int ret;

	ret = app_manager_get_app_info("org.example.componentbased", &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_get_app_component_type(app_info, &component);
	app_info_destroy(app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	assert_eq_with_exit(component, APP_INFO_APP_COMPONENT_TYPE_COMPONENT_BASED_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_app_component_type_n
 * @since_tizen		4.0
 * @description		If there is no app info or address to return, func has to return an error.
 * @scenario		Call app_info_get_app_component_type func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_app_component_type_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_get_app_component_type(NULL, NULL);
	assert_neq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_foreach_metadata_p
 * @since_tizen		2.3
 * @description		Gets the list of metadata for a particular application.
 * @scenario		Get app info for test application and register callback func by app_info_foreach_metadata func.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_foreach_metadata_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_foreach_metadata(app_info, metadata_cb, NULL);
	app_info_destroy(app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_foreach_metadata_n
 * @since_tizen		2.3
 * @description		If there is no argument what app_info or callback func, func has to return an error.
 * @scenario		Call app_info_foreach_metadata func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_foreach_metadata_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_foreach_metadata(NULL, NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_is_nodisplay_p
 * @since_tizen		2.3
 * @description		Checks whether application information is nodisplay.
 * @scenario		Get app_info handle for test application and find whether nodisplay. And destory handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_is_nodisplay_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;
	bool nodisplay = false;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_is_nodisplay(app_info, &nodisplay);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	app_info_destroy(app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_is_nodisplay_n
 * @since_tizen		2.3
 * @description		If there is no app info or address to return, func has to return an error.
 * @scenario		Call app_info_is_nodisplay func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_is_nodisplay_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_is_nodisplay(NULL, NULL);
	assert_neq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_is_equal_p
 * @since_tizen		2.3
 * @description		Checks whether two application information are equal.
 * @scenario		Get app_info handle 1, 2 for test application and compare whether both is identical. And destory handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_is_equal_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h lhs, rhs;
	bool equal = false;

	ret = app_manager_get_app_info(TEST_APPID, &lhs);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_manager_get_app_info(TEST_APPID, &rhs);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_is_equal(lhs,rhs,&equal);
	app_info_destroy(rhs);
	app_info_destroy(lhs);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_is_equal_n
 * @since_tizen		2.3
 * @description		If there is no object to compare, func has to return an error.
 * @scenario		Call app_info_is_equal with no handle of app_info\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_is_equal_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	bool equal = false;

	ret = app_info_is_equal(NULL, NULL, &equal);
	assert_neq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_is_enabled_p
 * @since_tizen		2.3
 * @description		Checks whether application is enabled.
 * @scenario		Get app_info handle for test application and check whether enabled. And destory handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_is_enabled_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info;
	bool enabled = false;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_is_enabled(app_info,&enabled);
	app_info_destroy(app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_is_enabled_n
 * @since_tizen		2.3
 * @description		If there is no handle of app info, func has to return an error.
 * @scenario		Call app_info_is_enabled func with no app_info handle.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_is_enabled_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	bool enabled;

	ret = app_info_is_enabled(NULL, &enabled);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_destroy_p1
 * @since_tizen		2.3
 * @description		Destroys the application information filter handle, freeing up all the resources.
 * @scenario		Create filter and destroy it. Check whether result is APP_MANAGER_ERROR_NONE.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_filter_destroy_p1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_filter_h filter = NULL;

	ret = app_info_filter_create(&filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_destroy_p2
 * @since_tizen		2.3
 * @description		Destroys the application information filter handle, freeing up all the resources.
 * @scenario		Create filter and add key, value. And destory handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_filter_destroy_p2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_filter_h filter = NULL;

	ret = app_info_filter_create(&filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_add_string(filter, PACKAGE_INFO_PROP_APP_TYPE, "capp");
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_create_p1
 * @since_tizen		2.3
 * @description		Creates the application information filter handle from DB.
 * @scenario		Create filter and destroy it.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_filter_create_p1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_filter_h filter = NULL;

	ret = app_info_filter_create(&filter);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_create_p2
 * @since_tizen		2.3
 * @description		Creates the application information filter handle from DB.
 * @scenario		Create filter and add key, value. And destory handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_filter_create_p2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_filter_h filter = NULL;

	ret = app_info_filter_create(&filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_add_string(filter, PACKAGE_INFO_PROP_APP_TYPE, "capp");
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_create_n
 * @since_tizen		2.3
 * @description		If there is no address to return, fucn has to return an error.
 * @scenario		Call app_info_filter_create func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_filter_create_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_filter_create(NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_destroy_n
 * @since_tizen		2.3
 * @description		If there is no object to destroy, func has to return an error.
 * @scenario		Call app_info_filter_destroy func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_filter_destroy_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_filter_destroy(NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_add_bool_p
 * @since_tizen		2.3
 * @description		Adds a boolean filter property to the filter handle.
 * @scenario		Create filter and add key, value which bool type. And destory handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_filter_add_bool_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_filter_h filter = NULL;

	ret = app_info_filter_create(&filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_add_bool(filter, PACKAGE_INFO_PROP_APP_NODISPLAY, true);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_add_bool(filter, PACKAGE_INFO_PROP_APP_TASKMANAGE, true);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_add_bool(filter, PACKAGE_INFO_PROP_APP_DISABLED, false);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_add_bool_n1
 * @since_tizen		2.3
 * @description		If there is no filter and key, value, func has to return an error.
 * @scenario		Call app_info_filter_add_bool func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_filter_add_bool_n1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_filter_add_bool(NULL, NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_add_bool_n2
 * @since_tizen		2.3
 * @description		If filter handle is null, func has to return an error.
 * @scenario		Call app_info_filter_add_bool func with filter which value is NULL.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_filter_add_bool_n2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	app_info_filter_h filter = NULL;
	ret = app_info_filter_add_bool(filter, PACKAGE_INFO_PROP_APP_NODISPLAY, true);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_add_bool_n3
 * @since_tizen		2.3
 * @description		If key is invalid, func has to return an error.
 * @scenario		Call app_info_filter_add_bool func with invalid key.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_filter_add_bool_n3(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_filter_h filter = NULL;
	const char *property = "Invalid property";
	bool value = false;

	ret = app_info_filter_create(&filter);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_add_bool(filter, property, value);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_add_string_p
 * @since_tizen		2.3
 * @description		Adds a string filter property to the filter handle.
 * @scenario		Create filter and add key, value which string type. And destory handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_filter_add_string_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_filter_h filter = NULL;

	ret = app_info_filter_create(&filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_add_string(filter, PACKAGE_INFO_PROP_APP_TYPE, "capp");
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_add_string_n1
 * @since_tizen		2.3
 * @description		If there is no filter and key, value, func has to return an error.
 * @scenario		Call app_info_filter_add_string func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_filter_add_string_n1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_filter_add_string(NULL, NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_add_string_n2
 * @since_tizen		2.3
 * @description		If filter handle is null, func has to return an error.
 * @scenario		Call app_info_filter_add_string func with filter which value is NULL.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_filter_add_string_n2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	app_info_filter_h filter = NULL;
	ret = app_info_filter_add_string(filter, PACKAGE_INFO_PROP_APP_TYPE, "capp");
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_add_string_n3
 * @since_tizen		2.3
 * @description		If key is invalid, func has to return an error.
 * @scenario		Call app_info_filter_add_string func with invalid key.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_filter_add_string_n3(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	int r;
	app_info_filter_h filter = NULL;
	const char *property = "Invalid property";
	const char *value = "Value";

	ret = app_info_filter_create(&filter);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_add_string(filter, property, value);
	r = app_info_filter_destroy(filter);
	assert_eq_with_exit(r, APP_MANAGER_ERROR_NONE);

	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/*
TODO: See comments for app_info_metadata_filter_foreach
*/
/**
 * @testcase		utc_app_info_filter_foreach_appinfo_p1
 * @since_tizen		2.3
 * @description		Executes the user supplied callback function for each application that satisfy the filter conditions.
 * @scenario		Create filter and add key, value which bool type.\n
 * Call app_info_filter_foreach_appinfo func with callback func. And destory filter.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_filter_foreach_appinfo_p1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_filter_h filter = NULL;

	ret = app_info_filter_create(&filter);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_add_bool(filter, PACKAGE_INFO_PROP_APP_NODISPLAY, false);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_foreach_appinfo(filter, filter_cb, NULL);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_foreach_appinfo_p2
 * @since_tizen		2.3
 * @description		Executes the user supplied callback function for each application that satisfy the filter conditions.
 * @scenario		Create filter and add key, value which string type.\n
 * Call app_info_filter_foreach_appinfo func with callback func. And destory filter. \n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_filter_foreach_appinfo_p2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_filter_h filter = NULL;

	ret = app_info_filter_create(&filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_add_string(filter, PACKAGE_INFO_PROP_APP_TYPE, "capp");
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_foreach_appinfo(filter, filter_cb, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_foreach_appinfo_n1
 * @since_tizen		2.3
 * @description		If there is no argument, func has to return an error.
 * @scenario		Call app_info_filter_foreach_appinfo func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_filter_foreach_appinfo_n1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_filter_foreach_appinfo(NULL, NULL, NULL);
	assert_neq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_foreach_appinfo_n2
 * @since_tizen		2.3
 * @description		If there is no filter, func has to return an error.
 * @scenario		Call app_info_filter_foreach_appinfo func with no filter.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_filter_foreach_appinfo_n2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_filter_foreach_appinfo(NULL, filter_cb, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_metadata_filter_create_p1
 * @since_tizen		2.3
 * @description		Creates the application's metadata information filter handle from DB.
 * @scenario		Create metada filter and destory it.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_metadata_filter_create_p1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_metadata_filter_h filter = NULL;

	ret = app_info_metadata_filter_create(&filter);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_info_metadata_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_metadata_filter_create_p2
 * @since_tizen		2.3
 * @description		Creates the application's metadata information filter handle from DB.
 * @scenario		Create metadata filter and add key, value. And destory it.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_metadata_filter_create_p2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	char *mkey = "http://developer.tizen.org/metadata/disablescreenread";
	char *mvalue = "shared/res/720x1280/Splash_Tizen_resolution_720x1280_landscape.p";

	app_info_metadata_filter_h filter = NULL;

	ret = app_info_metadata_filter_create(&filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_metadata_filter_add(filter, mkey, mvalue);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_metadata_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_metadata_filter_create_n
 * @since_tizen		2.3
 * @description		If there is no address to return metadata fileter, func has to return en error.
 * @scenario		Call app_info_metadata_filter_create func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_metadata_filter_create_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_metadata_filter_create(NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_metadata_filter_destroy_p1
 * @since_tizen		2.3
 * @description		Destroys the application's metadata information filter handle.
 * @scenario		Create metadata filter and destroy it.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_metadata_filter_destroy_p1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_metadata_filter_h filter = NULL;

	ret = app_info_metadata_filter_create(&filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	app_info_metadata_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_metadata_filter_destroy_p2
 * @since_tizen		2.3
 * @description		Destroys the application's metadata information filter handle.
 * @scenario		Create metadata filter and add key, value. And destory it.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_metadata_filter_destroy_p2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	const char *mkey = "http://developer.tizen.org/metadata/disablescreenread";
	const char *mvalue = "shared/res/720x1280/Splash_Tizen_resolution_720x1280_landscape.p";

	app_info_metadata_filter_h filter;

	ret = app_info_metadata_filter_create(&filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_metadata_filter_add(filter, mkey, mvalue);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_metadata_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_metadata_filter_destroy_n
 * @since_tizen		2.3
 * @description		If there is no object to destroy, func has to return an error.
 * @scenario		Call app_info_metadata_filter_destroy func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_metadata_filter_destroy_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_metadata_filter_destroy(NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/*
TODO: No criteria added to the filter, this is probably the cause of failing.
It's not clear what criteria will be always met
We need such criteria to make sure that the callback is called,
so that the test is more extensive.

Similar issues for app_info_filter_foreach_appinfo.
*/
/**
 * @testcase		utc_app_info_metadata_filter_foreach_p1
 * @since_tizen		2.3
 * @description		Executes the filter query.
 * @scenario		Create metadata filter and add key with no value.\n
 * Call app_info_filter_foreach_appinfo func with callback func. And destory filter.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_metadata_filter_foreach_p1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	const char *mkey = "http://developer.tizen.org/metadata/mode/emergency";

	app_info_metadata_filter_h filter = NULL;

	ret = app_info_metadata_filter_create(&filter);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_info_metadata_filter_add(filter, mkey, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_metadata_filter_foreach(filter, filter_cb, NULL);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	app_info_metadata_filter_destroy(filter);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_metadata_filter_foreach_p2
 * @since_tizen		2.3
 * @description		Executes the filter query.
 * @scenario		Create metadata filter and add key, value.\n
 * Call app_info_filter_foreach_appinfo func with callback func. And destory filter.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_metadata_filter_foreach_p2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	const char *mkey = "http://developer.tizen.org/metadata/disablescreenread";
	const char *mvalue = "shared/res/720x1280/Splash_Tizen_resolution_720x1280_landscape.p";

	app_info_metadata_filter_h filter;

	ret = app_info_metadata_filter_create(&filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_metadata_filter_add(filter, mkey, mvalue);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_metadata_filter_foreach(filter, filter_cb, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_metadata_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_metadata_filter_foreach_n1
 * @since_tizen		2.3
 * @description		If there is no metadata filter, func has to return an error.
 * @scenario		Call app_info_metadata_filter_foreach func with no metadata filter.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_metadata_filter_foreach_n1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_metadata_filter_foreach(NULL, filter_cb, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_metadata_filter_foreach_n2
 * @since_tizen		2.3
 * @description		If there is no callback func, func has to return an error.
 * @scenario		Call app_info_metadata_filter_foreach func with no callback func.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_metadata_filter_foreach_n2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_metadata_filter_h filter;

	ret = app_info_metadata_filter_create(&filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_metadata_filter_foreach(filter, NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);

	ret = app_info_metadata_filter_destroy(filter);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

static bool app_context_cb(app_context_h app_context, void * user_data)
{
	normal_exit(0);

	return true;
}

static bool app_info_cb(app_info_h app_info, void * user_data)
{
	normal_exit(0);

	return true;
}

/**
 * @testcase		utc_app_manager_is_running_p
 * @since_tizen		2.3
 * @description		Checks whether the application with the given package name is running.
 * @scenario		Call app_manager_is_running func with an app id and address to return result.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_is_running_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	bool is_running = false;

	ret = app_manager_is_running(TEST_APPID, &is_running);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_is_running_n1
 * @since_tizen		2.3
 * @description		If there is no address to return, func has to return an error.
 * @scenario		Call app_manager_is_running func with no address to return result.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_is_running_n1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_is_running(TEST_APPID, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_is_running_n2
 * @since_tizen		2.3
 * @description		If there is no an app id of test application, func has to return an error.
 * @scenario		Call app_manager_is_running func with no an app id.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_is_running_n2(void)
{
	bool is_running = false;
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_is_running(NULL, &is_running);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_is_running_n3
 * @since_tizen		2.3
 * @description		If there is no argument, func ahs to return an error.
 * @scenario		Call app_manager_is_running func with no argument. And check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_is_running_n3(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_is_running(NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_foreach_app_context_p
 * @since_tizen		2.3
 * @description		Retrieves all application contexts of running applications.
 * @scenario		Call app_manager_foreach_app_context with callback func.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_foreach_app_context_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_foreach_app_context(app_context_cb, NULL);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_app_manager_foreach_app_context_n
 * @since_tizen		2.3
 * @description		If there is no argument, func has to return an error.
 * @scenario		Call app_manager_foreach_app_context func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_foreach_app_context_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_foreach_app_context(NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_foreach_running_app_context_p
 * @since_tizen		3.0
 * @description		Retrieves all application contexts of running applications including sub apps.
 * @scenario		Call app_manager_foreach_running_app_context with callback func.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_foreach_running_app_context_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_foreach_running_app_context(app_context_cb, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_app_manager_foreach_running_app_context_n
 * @since_tizen         3.0
 * @description         If there is no argument, func has to return an error.
 * @scenario            Call app_manager_foreach_running_app_context with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_foreach_running_app_context_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_foreach_running_app_context(NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

        return 0;
}

/**
 * @testcase		utc_app_manager_foreach_app_info_p
 * @since_tizen		2.3
 * @description		Retrieves all installed applications information.
 * @scenario		Call app_manager_foreach_app_info func with app_info_cb.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_foreach_app_info_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_foreach_app_info(app_info_cb, NULL);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_app_manager_foreach_app_info_n
 * @since_tizen		2.3
 * @description		If there is no argument, func has to return an error.
 * @scenario		Call app_manager_foreach_app_info func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_foreach_app_info_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_foreach_app_info(NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_app_id_n1
 * @since_tizen		2.3
 * @description		If process id is 0, func has to return an error.
 * @scenario		Call app_manager_get_app_id func with pid 0 and no address to return result.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_app_id_n1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_get_app_id(0, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_app_id_n2
 * @since_tizen		2.3
 * @description		If process id is 0, func has to return an error.
 * @scenario		Call app_manager_get_app_id func with pid 0.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_app_id_n2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	char *appid;

	ret = app_manager_get_app_id(0, &appid);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_app_id_p
 * @since_tizen		2.3
 * @description		Gets the ID of the application for the given process ID.
 * @scenario		Get app_context handle for test application and get pid from it.\n
 * Call app_manager_get_app_id func with pid and address to return result.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_get_app_id_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	pid_t pid;
	char *appid;
	app_context_h app_context;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_context_get_pid(app_context, &pid);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_manager_get_app_id(pid, &appid);
	assert_eq_with_exit(strcmp(appid, TEST_APPID), 0);
	free(appid);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_resume_app_p
 * @since_tizen		2.3
 * @description		Resumes the application.
 * @scenario		Get app_context handle for test application. Call app_manager_resume_app func with handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_resume_app_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_context_h app_context = NULL;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);

	ret = app_manager_resume_app(app_context);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_resume_app_n
 * @since_tizen		2.3
 * @description		If there is no argument, func has to return an error.
 * @scenario		Call app_manager_resume_app func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_resume_app_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_resume_app(NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_app_context_p
 * @since_tizen		2.3
 * @description		Gets the application context for the given ID of the application.
 * @scenario		Call app_manager_get_app_context func with add id of test application and address to return handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_get_app_context_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_context_h app_context = NULL;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_app_context_n1
 * @since_tizen		2.3
 * @description		If there is no an app id, func has to return an error.
 * @scenario		Call app_manager_get_app_context func with no TEST_APPID.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_app_context_n1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_context_h app_context = NULL;

	ret = app_manager_get_app_context(NULL, &app_context);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_app_context_n2
 * @since_tizen		2.3
 * @description		If there is no address to return handle, func has to return an error.
 * @scenario		Call app_manager_get_app_context func with no address to return.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_app_context_n2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_get_app_context(TEST_APPID, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_app_context_n3
 * @since_tizen		2.3
 * @description		If there is no argument, func has to return an error.
 * @scenario		Call app_manager_get_app_context func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_app_context_n3(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_get_app_context(NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_app_info_p
 * @since_tizen		2.3
 * @description		Gets the application information for the given application ID.
 * @scenario		Get app_info handle for TEST_APPID, destory it.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_get_app_info_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_destroy(app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_app_info_n1
 * @since_tizen		2.3
 * @description		If there is no an app id, func has to return an error.
 * @scenario		Call app_manager_get_app_info func with no TEST_APPID.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_app_info_n1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;

	ret = app_manager_get_app_info(NULL, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_app_info_n2
 * @since_tizen		2.3
 * @description		If there is no address to return handle, func has to return an error.
 * @scenario		Call app_manager_get_app_info func with no address to return.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_app_info_n2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_get_app_info(TEST_APPID, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_get_app_info_n3
 * @since_tizen		2.3
 * @description		If there is no argument, func has to return an error.
 * @scenario		Call app_manager_get_app_info func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_get_app_info_n3(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_get_app_info(NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_request_terminate_bg_app_p
 * @since_tizen		2.4
 * @description		Terminates the back ground application.\n
 *         UI applications that are in paused state or some service applications could be required to terminate by this API.
 * @scenario		Get app_context handle of TEST_APPID, call app_manager_request_terminate_bg_app func with handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_request_terminate_bg_app_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_context_h app_context = NULL;

	ret = app_manager_get_app_context(TEST_APPID, &app_context);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_manager_request_terminate_bg_app(app_context);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_request_terminate_bg_app_n
 * @since_tizen		2.4
 * @description		If there is no argument, func has to return an error.
 * @scenario		Call app_manager_request_terminate_bg_app func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_manager_request_terminate_bg_app_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_request_terminate_bg_app(NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

static gboolean unset_app_context_event_cb(gpointer user_data)
{
	dlog_print(DLOG_INFO, "NativeTCT", "%s(%d) START",
			__FUNCTION__, __LINE__);
	app_manager_unset_app_context_event_cb();
	normal_exit(0);
	dlog_print(DLOG_INFO, "NativeTCT", "%s(%d) END",
			__FUNCTION__, __LINE__);

	return FALSE;
}

static void app_context_event_cb(app_context_h app_context, app_context_event_e event, void *user_data)
{
	char *str = (char *)user_data;
	bool touched = false;

	dlog_print(DLOG_INFO, "NativeTCT", "%s(%d) START",
			__FUNCTION__, __LINE__);
	if (str == NULL) {
		normal_exit(1);
		return;
	}

	if (event == APP_CONTEXT_EVENT_LAUNCHED) {
		if (!strcmp(str, "launched"))
			touched = true;
	} else if (event == APP_CONTEXT_EVENT_TERMINATED) {
		if (!strcmp(str, "terminated"))
			touched = true;
	}

	if (touched) {
		dlog_print(DLOG_INFO, "NativeTCT",
				"Deregister app_context_event_cb()");
		g_idle_add(unset_app_context_event_cb, NULL);
	}

	dlog_print(DLOG_INFO, "NativeTCT", "%s(%d) END",
			__FUNCTION__, __LINE__);
}

/**
 * @testcase		utc_app_manager_set_app_context_event_cb_p1
 * @since_tizen		2.4
 * @description		Registers a callback function to be invoked when the applications get launched or terminated.
 * @scenario		Create app_control handle and set an app id of TEST_APPID2.\n
 * Call app_manager_set_app_context_event_cb func with callback func. It will be invoked when app is launched.\n
 * Send launch request and wait. Destory handle. \n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_set_app_context_event_cb_p1(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_control_h request;

	app_control_create(&request);
	assert_with_exit(request);

	ret = app_control_set_app_id(request, TEST_APPID2);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_manager_set_app_context_event_cb(app_context_event_cb, "launched");
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_control_send_launch_request(request, NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	app_control_destroy(request);

	return 0;
}

/**
 * @testcase		utc_app_manager_set_app_context_event_cb_p2
 * @since_tizen		2.4
 * @description		Registers a callback function to be invoked when the applications get launched or terminated.
 * @scenario		Create app_control handle and set app id of TEST_APPID2.\n
 * Add extra data to terminate by itself. Call app_manager_set_app_context_event_cb func with callback func.\n
 * It will be invoked when app is terminated. Send launch request and wait. Destory handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_set_app_context_event_cb_p2(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_control_h request;

	app_control_create(&request);
	assert_with_exit(request);

	ret = app_control_set_app_id(request, TEST_APPID2);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_send_launch_request(request, NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_control_add_extra_data(request, "KEY_TERM", "ui_app_exit");
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_manager_set_app_context_event_cb(app_context_event_cb, "terminated");
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	/* org.tizen.hellworld2 will call ui_app_exit() function. */
	ret = app_control_send_launch_request(request, NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	app_control_destroy(request);

	return 0;
}

/**
 * @testcase		utc_app_manager_set_app_context_event_cb_n
 * @since_tizen		2.4
 * @description		If there is no argument, func has to return an error.
 * @scenario		Call app_manager_set_app_context_event_cb func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_set_app_context_event_cb_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_set_app_context_event_cb(NULL, NULL);
	assert_neq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_app_manager_unset_app_context_event_cb_p
 * @since_tizen         2.4
 * @description         Unregisters the callback function.
 * @scenario            Calls app_manager_set_app_context_event_cb().
 *                      And then, calls app_manager_unset_app_context_event_cb().
 */
int utc_app_manager_unset_app_context_event_cb_p(void)
{
	int ret;

	/* Precondition */
	ret = app_manager_set_app_context_event_cb(app_context_event_cb,
			"launched");
	if (ret != APP_MANAGER_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to set app_context event callback");
		normal_exit(1);
		return;
	}

	/* Test */
	app_manager_unset_app_context_event_cb();
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_app_manager_event_create_p
 * @since_tizen		3.0
 * @description		Creates the app manager event handle
 * @scenario		Create app_manager_event_h handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_event_create_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_manager_event_h handle = NULL;

	ret = app_manager_event_create(&handle);
	app_manager_event_destroy(handle);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_event_create_n
 * @since_tizen		3.0
 * @description		If there is no argument, func has to return an error.
 * @scenario		Call app_manager_event_create func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_event_create_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_event_create(NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_event_set_status_p
 * @since_tizen		3.0
 * @description		Sets the event to handle to listen.
 * @scenario		Create app_manager_event_h handle and set event to listen.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_event_set_status_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_manager_event_h handle = NULL;

	app_manager_event_create(&handle);

	ret = app_manager_event_set_status(handle,
			APP_MANAGER_EVENT_STATUS_TYPE_ALL);
	app_manager_event_destroy(handle);

	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_event_set_status_n
 * @since_tizen		3.0
 * @description		Func has to return an error if given handle is null.
 * @scenario		Call app_manager_event_set_status func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_event_set_status_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_event_set_status(NULL,
			APP_MANAGER_EVENT_STATUS_TYPE_ALL);

	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_set_event_cb_p
 * @since_tizen		3.0
 * @description		Registers a callback function to be invoked when the app is event has occurred.
 * @scenario		Create handle and register a callback function.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_set_event_cb_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_manager_event_h handle = NULL;

	app_manager_event_create(&handle);
	ret = app_manager_set_event_cb(handle,
			event_cb, NULL);
	app_manager_event_destroy(handle);

	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_set_event_cb_n
 * @since_tizen		3.0
 * @description		Func has to return an error if given handle is null.
 * @scenario		Call app_manager_set_event_cb func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_set_event_cb_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_set_event_cb(NULL,
			APP_MANAGER_EVENT_STATUS_TYPE_ALL, NULL);

	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_unset_event_cb_p
 * @since_tizen		3.0
 * @description		Unregisters the event callback.
 * @scenario		Register a callback function and unregister it.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_unset_event_cb_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_manager_event_h handle = NULL;

	app_manager_event_create(&handle);
	app_manager_set_event_cb(handle, event_cb, NULL);

	ret = app_manager_unset_event_cb(handle);
	app_manager_event_destroy(handle);

	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_unset_event_cb_n
 * @since_tizen		3.0
 * @description		Func has to return an error if given handle is null.
 * @scenario		Call app_manager_unset_event_cb func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_unset_event_cb_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_unset_event_cb(NULL);

	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_event_destroy_p
 * @since_tizen		3.0
 * @description		Destroys given event handle.
 * @scenario		Create and free event handle.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_event_destroy_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_manager_event_h handle = NULL;

	app_manager_event_create(&handle);
	ret = app_manager_event_destroy(handle);

	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_manager_event_destroy_n
 * @since_tizen		3.0
 * @description		Func has to return an error if given handle is null.
 * @scenario		Call app_manager_event_destroy func with no argument.\n
 * Check whether result is not APP_MANAGER_ERROR_NONE.
 */
int utc_app_manager_event_destroy_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_manager_event_destroy(NULL);

	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_count_appinfo_p
 * @since_tizen		2.3
 * @description		Gets the count of filtered apps.
 * @scenario		Create app_inf filter and add string to it.\n
 * Get count of filter. And destory fileter.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_filter_count_appinfo_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	int count = 0;
	app_info_filter_h filter = NULL;

	ret = app_info_filter_create(&filter);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	assert_with_exit(filter);

	ret = app_info_filter_add_string(filter, PACKAGE_INFO_PROP_APP_TYPE, "capp");
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_count_appinfo(filter, &count);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_filter_destroy(filter);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_filter_count_appinfo_n
 * @since_tizen		2.3
 * @description		If there is no filter, func has to return an error.
 * @scenario		Call app_info_filter_count_appinfo func with no filter.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_filter_count_appinfo_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	int *count = NULL;

	ret = app_info_filter_count_appinfo(NULL, count);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_exec_p
 * @since_tizen		2.3
 * @description		Gets the executable path of the application
 * @scenario		Get app_info handle for TEST_APPID. Get the executable path from handle.\n
 * Destory handle. Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_exec_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	char *exec = NULL;
	app_info_h app_info = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	assert_with_exit(app_info);

	ret = app_info_get_exec(app_info, &exec);
	app_info_destroy(app_info);
	free(exec);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_exec_n
 * @since_tizen		2.3
 * @description		If there is no app_info handle, func has to return an error.
 * @scenario		Call app_info_get_exec func with no handle.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_get_exec_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	char *exec = NULL;

	ret = app_info_get_exec(NULL, &exec);
	free(exec);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_localed_label_p
 * @since_tizen		2.3
 * @description		Gets the localed name of the application.
 * @scenario		Get app_info handle for TEST_APPID and get an app id from it.\n
 * Call app_info_get_localed_label func with an app id and address to return label.\n
 * Destory app_info handle. Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_get_localed_label_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;
	char *app_id = "app_id";
	const char *locale = "locale";
	char *label = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_get_app_id(app_info, &app_id);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_get_localed_label(app_id, locale, &label);
	app_info_destroy(app_info);
	free(label);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_get_localed_label_n
 * @since_tizen		2.3
 * @description		If there is no app_info handle, func has to return an error.
 * @scenario		Call app_info_get_localed_label with no app_info handle.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_get_localed_label_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	const char *locale = "locale";
	char *label = NULL;

	ret = app_info_get_localed_label(NULL, locale, &label);
	free(label);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_is_onboot_p
 * @since_tizen		2.3
 * @description		Checks whether application is launched on booting time.
 * @scenario		Get app_info handle for TEST_APPID and get onboot value from app_info_is_onboot func.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_is_onboot_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;
	bool onboot = false;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	assert_with_exit(app_info);

	ret = app_info_is_onboot(app_info, &onboot);
	app_info_destroy(app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_is_onboot_n
 * @since_tizen		2.3
 * @description		If there is no app_info handle, func has to return an error.
 * @scenario		Call app_info_is_onboot func with no handle.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_is_onboot_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	bool onboot = false;

	ret = app_info_is_onboot(NULL, &onboot);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_is_preload_p
 * @since_tizen		2.3
 * @description		Checks whether application is preloaded.
 * @scenario		Get app_info handle for TEST_APPID and get preload value form app_info_is_preload func.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_is_preload_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;
	bool preload = false;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret,APP_MANAGER_ERROR_NONE);
	assert_with_exit(app_info);

	ret = app_info_is_preload(app_info, &preload);
	app_info_destroy(app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_is_preload_n
 * @since_tizen		2.3
 * @description		If there is no app_info handle, func has to return an error.
 * @scenario		Call app_info_is_preload func with no handle.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_is_preload_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	bool preload = false;

	ret = app_info_is_preload(NULL, &preload);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_is_support_ambient_p
 * @since_tizen		5.5
 * @description		Checks whether application is ambient supported.
 * @scenario		Get app_info handle for TEST_APPID and get preload value from app_info_is_preload func.\n
 * Check wheter result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_is_support_ambient_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;
	bool ambient_supported = false;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	assert_with_exit(app_info);

	ret = app_info_is_support_ambient(app_info, &ambient_supported);
	app_info_destroy(app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_is_support_ambient_n
 * @since_tizen		5.5
 * @description		If there is no app_info handle, func has to return an error.
 * @scenario		Call app_info_is_support_ambient func with no handle.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_is_support_ambient_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	bool ambient_supported = false;

	ret = app_info_is_support_ambient(NULL, &ambient_supported);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_multi_resolution_icon_test_p
 * @since_tizen		3.0
 * @description		Checks whether icon path is returned properly for device's resolution.
 * @scenario		Call app_info handle for TEST_APPID_MULTI_RESOLUTION and get icon path.\n
 * Check whether result contains proper value for test device's resolution.
 */
int utc_app_multi_resolution_icon_test_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	char *path = NULL;
	app_info_h app_info = NULL;
	static const char ldpi[] = "ldpi";
	static const char mdpi[] = "mdpi";
	static const char hdpi[] = "hdpi";
	static const char xhdpi[] = "xhdpi";
	static const char xxhdpi[] = "xxhdpi";
	static const int ldpi_min = 0;
	static const int ldpi_max = 240;
	static const int mdpi_min = 241;
	static const int mdpi_max = 300;
	static const int hdpi_min = 301;
	static const int hdpi_max = 380;
	static const int xhdpi_min = 381;
	static const int xhdpi_max = 480;
	static const int xxhdpi_min = 481;
	static const int xxhdpi_max = 600;
	char *tmp_ptr = NULL;
	int dpi = -1;

	ret = app_manager_get_app_info(TEST_MULTIRES_ICON_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	ret = app_info_get_icon(app_info, &path);

	system_info_get_platform_int("http://tizen.org/feature/screen.dpi", &dpi);
	assert_neq_with_exit(dpi, -1);

	if (dpi >= ldpi_min && dpi <= ldpi_max)
		tmp_ptr = strstr(path, ldpi);
	else if (dpi >= mdpi_min && dpi <= mdpi_max)
		tmp_ptr = strstr(path, mdpi);
	else if (dpi >= hdpi_min && dpi <= hdpi_max)
		tmp_ptr = strstr(path, hdpi);
	else if (dpi >= xhdpi_min && dpi <= xhdpi_max)
		tmp_ptr = strstr(path, xhdpi);
	else if (dpi >= xxhdpi_min && dpi <= xxhdpi_max)
		tmp_ptr = strstr(path, xxhdpi);
	else
		assert_with_exit(false);

	assert_neq_with_exit(tmp_ptr, NULL);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_multi_resolution_icon_test_n
 * @since_tizen		3.0
 * @description		If icon path does not contain proper value, func has to return an error.
 * @scenario		Call app_info handle for TEST_APPID_MULTI_RESOLUTION and get icon path and compare it with wrong value.\n
 * Check whether result contains wrong value for test device's resolution.
 */
int utc_app_multi_resolution_icon_test_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	char *path = NULL;
	app_info_h app_info = NULL;
	static const char ldpi[] = "ldpi";
	static const char mdpi[] = "mdpi";
	static const int ldpi_max = 240;
	char *tmp_ptr = NULL;
	int dpi = -1;

	ret = app_manager_get_app_info(TEST_MULTIRES_ICON_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	ret = app_info_get_icon(app_info, &path);

	system_info_get_platform_int("http://tizen.org/feature/screen.dpi", &dpi);
	assert_neq_with_exit(dpi, -1);

	if (dpi >= ldpi_max)
		tmp_ptr = strstr(path, ldpi);
	else
		tmp_ptr = strstr(path, mdpi);

	assert_eq_with_exit(tmp_ptr, NULL);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_foreach_res_control_p
 * @since_tizen		6.5
 * @description		Gets the list of res control for a particular application.
 * @scenario		Get app info for test application and register callback func by app_info_foreach_res_control func.\n
 * Check whether result is APP_MANAGER_ERROR_NONE.
 */
int utc_app_info_foreach_res_control_p(void)
{
	int ret = APP_MANAGER_ERROR_NONE;
	app_info_h app_info = NULL;

	ret = app_manager_get_app_info(TEST_APPID, &app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	ret = app_info_foreach_res_control(app_info, res_control_cb, NULL);
	app_info_destroy(app_info);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_app_info_foreach_res_control_n
 * @since_tizen		6.5
 * @description		If there is no argument what app_info or callback func, func has to return an error.
 * @scenario		Call app_info_foreach_res_control func with no argument.\n
 * Check whether result is APP_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_app_info_foreach_res_control_n(void)
{
	int ret = APP_MANAGER_ERROR_NONE;

	ret = app_info_foreach_res_control(NULL, NULL, NULL);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
