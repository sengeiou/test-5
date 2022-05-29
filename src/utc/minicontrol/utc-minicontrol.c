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
#include <glib.h>
#include <Evas.h>
#include <Elementary.h>

#include <system_info.h>

#include <minicontrol-provider.h>
#include <minicontrol-viewer.h>
#include <minicontrol-type.h>
#include <minicontrol-error.h>

#define MINICONTROL_FEATURE "http://tizen.org/feature/minicontrol"

#define CHECK_MINICONTROL_FEATURE_WITH_RET(function) \
	do { \
		bool is_supported = false; \
		if (!system_info_get_platform_bool(MINICONTROL_FEATURE, &is_supported)) { \
			if (is_supported == false) { \
				int check_suppoted = function; \
				assert_eq(check_suppoted, MINICONTROL_ERROR_NOT_SUPPORTED); \
				return 0; \
			} \
		} \
	} while (0)

#define CHECK_MINICONTROL_FEATURE_WITHOUT_RET(function) \
	do { \
		bool is_supported = false; \
		if (!system_info_get_platform_bool(MINICONTROL_FEATURE, &is_supported)) { \
			if (is_supported == false) { \
				function; \
				assert_eq(get_last_result(), MINICONTROL_ERROR_NOT_SUPPORTED); \
				return 0; \
			} \
		} \
	} while (0)

#define MINICONTROL_NAME "minicontrol-utc"
#define TARGET_APP_ID "org.tizen.music-player"

static int event_result;

/**
 * @function		utc_minicontrol_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_minicontrol_startup(void)
{
}

/**
 * @function		utc_minicontrol_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_minicontrol_cleanup(void)
{
}


static void _minicontrol_cb(minicontrol_viewer_event_e event_type, bundle *event_arg)
{
}


/**
 * @testcase		utc_minicontrol_create_window_p
 * @since_tizen		2.4
 * @description		Positive test case of minicontrol_create_window()
 */
int utc_minicontrol_create_window_p(void)
{
	Evas_Object *minicontrol_window = NULL;

	CHECK_MINICONTROL_FEATURE_WITHOUT_RET(minicontrol_create_window(MINICONTROL_NAME, MINICONTROL_TARGET_VIEWER_QUICK_PANEL, _minicontrol_cb));

	minicontrol_window = minicontrol_create_window(MINICONTROL_NAME, MINICONTROL_TARGET_VIEWER_QUICK_PANEL, _minicontrol_cb);
	assert_neq(minicontrol_window, NULL);
	evas_object_del(minicontrol_window);

	return 0;
}

/**
 * @testcase		utc_minicontrol_create_window_n
 * @since_tizen		2.4
 * @description		Negative test case of minicontrol_create_window()
 */
int utc_minicontrol_create_window_n(void)
{
	Evas_Object *minicontrol_window = NULL;

	CHECK_MINICONTROL_FEATURE_WITHOUT_RET(minicontrol_create_window(NULL, MINICONTROL_TARGET_VIEWER_QUICK_PANEL, NULL));

	minicontrol_window = minicontrol_create_window(NULL, MINICONTROL_TARGET_VIEWER_QUICK_PANEL, NULL);
	assert_eq(minicontrol_window, NULL);

	return 0;
}

/**
 * @testcase		utc_minicontrol_send_event_p
 * @since_tizen		2.4
 * @description		Positive test case of minicontrol_send_event()
 */
int utc_minicontrol_send_event_p(void)
{
	int err = MINICONTROL_ERROR_NONE;
	Evas_Object *minicontrol_window = NULL;

	CHECK_MINICONTROL_FEATURE_WITHOUT_RET(minicontrol_create_window(MINICONTROL_NAME, MINICONTROL_TARGET_VIEWER_QUICK_PANEL, _minicontrol_cb));

	minicontrol_window = minicontrol_create_window(MINICONTROL_NAME, MINICONTROL_TARGET_VIEWER_QUICK_PANEL, _minicontrol_cb);
	assert_neq(minicontrol_window, NULL);

	err = minicontrol_send_event(minicontrol_window, MINICONTROL_PROVIDER_EVENT_REQUEST_HIDE, NULL);
	assert_eq(err, MINICONTROL_ERROR_NONE);

	evas_object_del(minicontrol_window);

	return 0;
}

/**
 * @testcase		utc_minicontrol_send_event_n
 * @since_tizen		2.4
 * @description		Negative test case of minicontrol_send_event()
 */
int utc_minicontrol_send_event_n(void)
{
	int err = MINICONTROL_ERROR_NONE;

	CHECK_MINICONTROL_FEATURE_WITH_RET(minicontrol_send_event(NULL, MINICONTROL_PROVIDER_EVENT_REQUEST_HIDE, NULL));

	err = minicontrol_send_event(NULL, MINICONTROL_PROVIDER_EVENT_REQUEST_HIDE, NULL);
	assert_eq(err, MINICONTROL_ERROR_INVALID_PARAMETER);

	return 0;
}

static int g_utc_minicontrol_viewer_add_p_result = 0;
static GMainLoop *g_mainloop = NULL;
static guint g_timeout_id = 0;

static gboolean timeout_function(gpointer data)
{
	g_main_loop_quit(g_mainloop);
	g_timeout_id = 0;
	g_utc_minicontrol_viewer_add_p_result = 1;
	return FALSE;
}

static inline void wait_for_async(void)
{
	if (g_mainloop) {
		if (g_timeout_id) {
			g_source_remove(g_timeout_id);
			g_timeout_id = 0;
		}
		g_main_loop_quit(g_mainloop);
		g_mainloop = NULL;
	}

    g_mainloop = g_main_loop_new(NULL, FALSE);

    g_timeout_id = g_timeout_add(5000, timeout_function, NULL);

    g_main_loop_run(g_mainloop);

	if (g_timeout_id > 0) {
		g_source_remove(g_timeout_id);
		g_timeout_id = 0;
	}
	g_mainloop = NULL;
}

void viewer_event_callback(minicontrol_event_e event, const char *minicontrol_name, bundle *event_arg, void *data)
{
	Evas_Object *parent_window = NULL;
	Evas_Object *viewer = NULL;

	event_result = 1;
	parent_window = elm_win_add(NULL, "parent_window", ELM_WIN_BASIC);

	evas_object_resize(parent_window, 480, 800);

	viewer = minicontrol_viewer_add(parent_window, minicontrol_name);
	g_utc_minicontrol_viewer_add_p_result = (viewer != NULL) ? 0 : 1;

	evas_object_del(viewer);
	evas_object_del(parent_window);

	g_main_loop_quit(g_mainloop);
	g_mainloop = NULL;
}

/**
 * @testcase		utc_minicontrol_viewer_add_p
 * @since_tizen		2.4
 * @description		Positive test case of minicontrol_viewer_add()
 */
int utc_minicontrol_viewer_add_p(void)
{
	int err = MINICONTROL_ERROR_NONE;
	Evas_Object *minicontrol_window = NULL;

	CHECK_MINICONTROL_FEATURE_WITHOUT_RET(minicontrol_viewer_add(NULL, NULL));

	g_utc_minicontrol_viewer_add_p_result = 0;

	err = minicontrol_viewer_set_event_cb(viewer_event_callback, "user_data");
	assert_eq(err, MINICONTROL_ERROR_NONE);

	minicontrol_window = minicontrol_create_window(MINICONTROL_NAME, MINICONTROL_TARGET_VIEWER_QUICK_PANEL, _minicontrol_cb);
	assert_neq(minicontrol_window, NULL);

	elm_win_alpha_set(minicontrol_window, EINA_TRUE);
	evas_object_resize(minicontrol_window, 480, 800);
	evas_object_show(minicontrol_window);

	wait_for_async();

	assert_eq(g_utc_minicontrol_viewer_add_p_result, 0);
	minicontrol_viewer_unset_event_cb();
	evas_object_del(minicontrol_window);

	return 0;
}

/**
 * @testcase		utc_minicontrol_viewer_add_n
 * @since_tizen		2.4
 * @description		Negative test case of minicontrol_viewer_add()
 */
int utc_minicontrol_viewer_add_n(void)
{
	Evas_Object *viewer = NULL;

	CHECK_MINICONTROL_FEATURE_WITHOUT_RET(minicontrol_viewer_add(NULL, NULL));

	viewer = minicontrol_viewer_add(NULL, NULL);
	assert_eq(viewer, NULL);

	return 0;
}

/**
 * @testcase		utc_minicontrol_viewer_send_event_p1
 * @since_tizen		2.4
 * @description		Positive test case of minicontrol_viewer_send_event()
 */
int utc_minicontrol_viewer_send_event_p1(void)
{
	int err = MINICONTROL_ERROR_NONE;
	bundle *event_arg = NULL;

	CHECK_MINICONTROL_FEATURE_WITH_RET(minicontrol_viewer_send_event(TARGET_APP_ID, MINICONTROL_VIEWER_EVENT_REPORT_ANGLE, event_arg));

	err = minicontrol_viewer_send_event(TARGET_APP_ID, MINICONTROL_VIEWER_EVENT_REPORT_ANGLE, event_arg);
	assert_eq(err, MINICONTROL_ERROR_NONE);
	return 0;
}

static gboolean __send_event(gpointer data)
{
	minicontrol_viewer_send_event(MINICONTROL_NAME, MINICONTROL_VIEWER_EVENT_REPORT_ANGLE, NULL);

	return FALSE;
}

/**
 * @testcase		utc_minicontrol_viewer_send_event_p2
 * @since_tizen		2.4
 * @description		Positive test case of minicontrol_viewer_send_event()
 */
int utc_minicontrol_viewer_send_event_p2(void)
{
	int ret;
	Evas_Object *minicontrol_window = NULL;

	CHECK_MINICONTROL_FEATURE_WITH_RET(minicontrol_viewer_send_event(MINICONTROL_NAME, MINICONTROL_VIEWER_EVENT_REPORT_ANGLE, NULL));

	minicontrol_window = minicontrol_create_window(MINICONTROL_NAME, MINICONTROL_TARGET_VIEWER_QUICK_PANEL, _minicontrol_cb);
	assert_neq(minicontrol_window, NULL);

	elm_win_alpha_set(minicontrol_window, EINA_TRUE);
	evas_object_resize(minicontrol_window, 480, 800);
	evas_object_show(minicontrol_window);

	ret = minicontrol_viewer_set_event_cb(viewer_event_callback, NULL);
	assert_eq(ret, MINICONTROL_ERROR_NONE);

	g_idle_add(__send_event, NULL);

	wait_for_async();

	assert_eq(event_result, 1);
	minicontrol_viewer_unset_event_cb();
	evas_object_del(minicontrol_window);

	return 0;
}

/**
 * @testcase		utc_minicontrol_viewer_send_event_n
 * @since_tizen		2.4
 * @description		Negative test case of minicontrol_viewer_send_event()
 */
int utc_minicontrol_viewer_send_event_n(void)
{
	int err = MINICONTROL_ERROR_NONE;

	CHECK_MINICONTROL_FEATURE_WITH_RET(minicontrol_viewer_send_event(NULL, 0, NULL));

	err = minicontrol_viewer_send_event(NULL, 0, NULL);
	assert_eq(err, MINICONTROL_ERROR_INVALID_PARAMETER);
	return 0;
}

void viewer_event_empty_callback(minicontrol_event_e event, const char *minicontrol_name, bundle *event_arg, void *data)
{

}

/**
 * @testcase		utc_minicontrol_viewer_set_event_cb_p
 * @since_tizen		2.4
 * @description		Positive test case of minicontrol_viewer_set_event_cb()
 */
int utc_minicontrol_viewer_set_event_cb_p(void)
{
	int err = MINICONTROL_ERROR_NONE;

	CHECK_MINICONTROL_FEATURE_WITH_RET(minicontrol_viewer_set_event_cb(viewer_event_empty_callback, "user_data"));

	err = minicontrol_viewer_set_event_cb(viewer_event_empty_callback, "user_data");
	assert_eq(err, MINICONTROL_ERROR_NONE);
	minicontrol_viewer_unset_event_cb();
	return 0;
}

/**
 * @testcase		utc_minicontrol_viewer_set_event_cb_n
 * @since_tizen		2.4
 * @description		Negative test case of minicontrol_viewer_set_event_cb()
 */
int utc_minicontrol_viewer_set_event_cb_n(void)
{
	int err = MINICONTROL_ERROR_NONE;

	CHECK_MINICONTROL_FEATURE_WITH_RET(minicontrol_viewer_set_event_cb(NULL, NULL));

	err = minicontrol_viewer_set_event_cb(NULL, NULL);
	assert_eq(err, MINICONTROL_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_minicontrol_viewer_unset_event_cb_p
 * @since_tizen		2.4
 * @description		Positive test case of minicontrol_viewer_unset_event_cb()
 */
int utc_minicontrol_viewer_unset_event_cb_p(void)
{
	int err = MINICONTROL_ERROR_NONE;

	CHECK_MINICONTROL_FEATURE_WITH_RET(minicontrol_viewer_unset_event_cb());

	err = minicontrol_viewer_unset_event_cb();
	assert_eq(err, MINICONTROL_ERROR_NONE);

	return 0;
}
