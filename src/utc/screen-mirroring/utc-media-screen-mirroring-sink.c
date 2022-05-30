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
#include <media/scmirroring_sink.h>
#include <media/scmirroring_type.h>
#include <glib.h>
#include <Elementary.h>
//& set: ScreenMirroringSink

#define PACKAGE "screen_mirroring_tc"
#define WFD_SINK_TEST_PORT "1122"
#define WFD_SINK_TEST_IP "192.168.0.1"

static scmirroring_sink_h scmirroring_sink = NULL;
static bool _is_WFD_supported = false;
static bool _is_broken = false;
static bool _is_pass = false;
static int _start_ret;
static GMainLoop *g_mainloop = NULL;
static Evas_Object* g_evas;

static Evas_Object* _create_win(const char *name);
static void create_win();
static void _win_del(void *data, Evas_Object *obj, void *event);
static void create_render_rect_and_bg(Evas_Object *win);

static gboolean timeout_func(gpointer data)
{
    fprintf(stderr, "Timeout! Test case failed!\n");
    g_main_loop_quit((GMainLoop *) data);
    return FALSE;
}

static void wait_for_async()
{
    int timeout_id = 0;
    g_mainloop = g_main_loop_new(NULL, FALSE);
    timeout_id = g_timeout_add(5000, timeout_func, g_mainloop);
    g_main_loop_run(g_mainloop);
    g_source_remove(timeout_id);
}

static void screen_mirroring_sink_state_cb(scmirroring_error_e error, scmirroring_sink_state_e state, void *user_data)
{
    _is_pass = true;
}

static void create_win()
{
	Evas_Object *win = NULL;
	/* create window */
	win = _create_win(PACKAGE);
	g_evas = win;
	create_render_rect_and_bg(g_evas);

	elm_win_activate(win);
	evas_object_show(win);
}

void create_render_rect_and_bg(Evas_Object *win)
{
	if (!win) {
		g_print("no win");
		return;
	}
	Evas_Object *bg, *rect;

	bg = elm_bg_add(win);
	elm_win_resize_object_add(win, bg);
	evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(bg);

	rect = evas_object_rectangle_add(evas_object_evas_get(win));
	if (!rect) {
		g_print("no rect");
		return;
	}
	evas_object_color_set(rect, 0, 0, 0, 0);
	evas_object_render_op_set(rect, EVAS_RENDER_COPY);

	elm_win_resize_object_add(win, rect);
	evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(rect);
	evas_object_show(win);
}

static Evas_Object* _create_win(const char *name)
{
	Evas_Object *eo = NULL;
	int w = 0;
	int h = 0;

	eo = elm_win_add(NULL, name, ELM_WIN_BASIC);
	if (eo) {
		elm_win_title_set(eo, name);
		elm_win_borderless_set(eo, EINA_TRUE);
		evas_object_smart_callback_add(eo, "delete,request", _win_del, NULL);
		elm_win_autodel_set(eo, EINA_TRUE);
		elm_win_screen_size_get(eo, NULL, NULL, &w, &h);
		elm_win_alpha_set(eo, EINA_TRUE);
	}
	return eo;
}

static void _win_del(void *data, Evas_Object *obj, void *event)
{
	elm_exit();
}
/**
 * @function		utc_media_screen_mirroring_sink_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_screen_mirroring_sink_startup(void)
{
    _is_WFD_supported = false;
    _is_broken = false;

    system_info_get_platform_bool("http://tizen.org/feature/network.wifi.direct.display", &_is_WFD_supported);

    _start_ret = scmirroring_sink_create(&scmirroring_sink);
    if (SCMIRRORING_ERROR_NONE != _start_ret) {
	_is_broken = true;
	return;
    }

    _start_ret = scmirroring_sink_set_state_changed_cb(scmirroring_sink, screen_mirroring_sink_state_cb, scmirroring_sink);
    if (SCMIRRORING_ERROR_NONE != _start_ret) {
	fprintf(stderr, "screen mirroring didn't set change callback\n");
	_is_broken = true;
	return;
    }
}

/**
 * @function		utc_media_screen_mirroring_sink_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_screen_mirroring_sink_cleanup(void)
{
    if (scmirroring_sink) {
	scmirroring_sink_destroy(scmirroring_sink);
	scmirroring_sink = NULL;
    }

	_is_broken = true;
	_is_pass = false;
}

/**
 * @testcase		utc_media_scmirroring_sink_create_p
 * @since_tizen		2.4
 * @description		Positive test case of scmirroring_sink_create()
 */
int utc_media_scmirroring_sink_create_p(void)
{

    if(!_is_WFD_supported){
	fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
	assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
    }
    assert(!_is_broken);

    int ret = scmirroring_sink_destroy(scmirroring_sink);
    assert_eq(ret, SCMIRRORING_ERROR_NONE);
    scmirroring_sink = NULL;

    int ret2 = scmirroring_sink_create(&scmirroring_sink);
    assert_eq(ret2, SCMIRRORING_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_create_n
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_create()
 */
int utc_media_scmirroring_sink_create_n(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_create(NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of scmirroring_sink_destroy()
 */
int utc_media_scmirroring_sink_destroy_p(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;

	ret = scmirroring_sink_destroy(scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);
	scmirroring_sink = NULL;

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_destroy()
 */
int utc_media_scmirroring_sink_destroy_n(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_destroy(NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_state_changed_cb_p1
 * @since_tizen		2.4
 * @description		Positive test case of scmirroring_sink_set_state_changed_cb()
 */
int utc_media_scmirroring_sink_set_state_changed_cb_p1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_unset_state_changed_cb(scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);

	int ret2 = scmirroring_sink_set_state_changed_cb(scmirroring_sink, screen_mirroring_sink_state_cb, scmirroring_sink);
	assert_eq(ret2, SCMIRRORING_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_state_changed_cb_p2
 * @since_tizen		2.4
 * @description		Positive test case of scmirroring_sink_set_state_changed_cb()
 */
int utc_media_scmirroring_sink_set_state_changed_cb_p2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_set_state_changed_cb(scmirroring_sink, screen_mirroring_sink_state_cb, scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_state_changed_cb_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_set_state_changed_cb()
 */
int utc_media_scmirroring_sink_set_state_changed_cb_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_set_state_changed_cb(NULL, screen_mirroring_sink_state_cb, scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_state_changed_cb_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_set_state_changed_cb()
 */
int utc_media_scmirroring_sink_set_state_changed_cb_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_set_state_changed_cb(scmirroring_sink, NULL, scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_unset_state_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive test case of scmirroring_sink_unset_state_changed_cb()
 */
int utc_media_scmirroring_sink_unset_state_changed_cb_p(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_unset_state_changed_cb(scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_unset_state_changed_cb_n
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_unset_state_changed_cb()
 */
int utc_media_scmirroring_sink_unset_state_changed_cb_n(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_unset_state_changed_cb(NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_ip_and_port_p
 * @since_tizen		2.4
 * @description		Positive test case of scmirroring_sink_set_ip_and_port()
 */
int utc_media_scmirroring_sink_set_ip_and_port_p(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_set_ip_and_port(scmirroring_sink, WFD_SINK_TEST_IP, WFD_SINK_TEST_PORT);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_ip_and_port_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_set_ip_and_port()
 */
int utc_media_scmirroring_sink_set_ip_and_port_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_set_ip_and_port(NULL, WFD_SINK_TEST_IP, WFD_SINK_TEST_PORT);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_ip_and_port_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_set_ip_and_port()
 */
int utc_media_scmirroring_sink_set_ip_and_port_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_set_ip_and_port(scmirroring_sink, NULL, WFD_SINK_TEST_PORT);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_ip_and_port_n3
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_set_ip_and_port()
 */
int utc_media_scmirroring_sink_set_ip_and_port_n3(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_set_ip_and_port(scmirroring_sink, WFD_SINK_TEST_IP, NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_display_p1
 * @since_tizen		2.4
 * @description		Positive test case of scmirroring_sink_set_display()
 */
int utc_media_scmirroring_sink_set_display_p1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;
	create_win();
	evas_object_show(g_evas);

	ret = scmirroring_sink_set_display(scmirroring_sink, SCMIRRORING_DISPLAY_TYPE_OVERLAY, (void *)g_evas);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_display_p2
 * @since_tizen		2.4
 * @description		Positive test case of scmirroring_sink_set_display()
 */
int utc_media_scmirroring_sink_set_display_p2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;
	create_win();
	evas_object_show(g_evas);

	ret = scmirroring_sink_set_display(scmirroring_sink, SCMIRRORING_DISPLAY_TYPE_EVAS, (void *)g_evas);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);

	return 0;
}


/**
 * @testcase		utc_media_scmirroring_sink_set_display_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_set_display()
 */
int utc_media_scmirroring_sink_set_display_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;
	int test_display;

	ret = scmirroring_sink_set_display(NULL, SCMIRRORING_DISPLAY_TYPE_OVERLAY, &test_display);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_display_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_set_display()
 */
int utc_media_scmirroring_sink_set_display_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;
	int test_display;

	ret = scmirroring_sink_set_display(scmirroring_sink, -1, &test_display);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_display_n3
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_set_display()
 */
int utc_media_scmirroring_sink_set_display_n3(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_set_display(scmirroring_sink, SCMIRRORING_DISPLAY_TYPE_OVERLAY, NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_resolution_p
 * @since_tizen		2.4
 * @description		Positive test case of scmirroring_sink_set_resolution()
 */
int utc_media_scmirroring_sink_set_resolution_p(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_set_resolution(scmirroring_sink, SCMIRRORING_RESOLUTION_1920x1080_P30);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_resolution_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_set_resolution()
 */
int utc_media_scmirroring_sink_set_resolution_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_set_resolution(NULL, SCMIRRORING_RESOLUTION_1920x1080_P30);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_set_resolution_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_set_resolution()
 */
int utc_media_scmirroring_sink_set_resolution_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);
	int ret;

	ret = scmirroring_sink_set_resolution(scmirroring_sink, -1);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_prepare_p
 * @since_tizen		5.0
 * @description		Negative test case of scmirroring_sink_prepare()
 */
int utc_media_scmirroring_sink_prepare_p(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_prepare(scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);

	scmirroring_sink = NULL;
	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_prepare_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_prepare()
 */
int utc_media_scmirroring_sink_prepare_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_prepare(NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_prepare_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_prepare()
 */
int utc_media_scmirroring_sink_prepare_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_destroy(scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);
	scmirroring_sink = NULL;

	ret = scmirroring_sink_prepare(scmirroring_sink);
	assert_neq(ret, SCMIRRORING_ERROR_NONE);

	scmirroring_sink = NULL;
	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_connect_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_connect()
 */
int utc_media_scmirroring_sink_connect_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_connect(NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_connect_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_connect()
 */
int utc_media_scmirroring_sink_connect_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_connect(scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_connect_n3
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_connect()
 */
int utc_media_scmirroring_sink_connect_n3(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_set_ip_and_port(scmirroring_sink, WFD_SINK_TEST_IP, WFD_SINK_TEST_PORT);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);

	ret = scmirroring_sink_connect(scmirroring_sink);
	assert_neq(ret, SCMIRRORING_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_start_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_start()
 */
int utc_media_scmirroring_sink_start_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_start(NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_start_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_start()
 */
int utc_media_scmirroring_sink_start_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_start(scmirroring_sink);
	assert_neq(ret, SCMIRRORING_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_disconnect_n
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_disconnect()
 */
int utc_media_scmirroring_sink_disconnect_n(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_disconnect(NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_unprepare_p
 * @since_tizen		5.0
 * @description		Negative test case of scmirroring_sink_unprepare()
 */
int utc_media_scmirroring_sink_unprepare_p(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_prepare(scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);

	ret = scmirroring_sink_unprepare(scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_unprepare_n
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_unprepare()
 */
int utc_media_scmirroring_sink_unprepare_n(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_unprepare(NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_pause_n
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_pause()
 */
int utc_media_scmirroring_sink_pause_n(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_pause(NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_pause_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_pause()
 */
int utc_media_scmirroring_sink_pause_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_pause(NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_media_scmirroring_sink_pause_n2
 * @since_tizen		5.0
 * @description		Negative test case of scmirroring_sink_pause()
 */
int utc_media_scmirroring_sink_pause_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_pause(scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_resume_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_resume()
 */
int utc_media_scmirroring_sink_resume_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_resume(NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_resume_n2
 * @since_tizen		5.0
 * @description		Negative test case of scmirroring_sink_resume()
 */
int utc_media_scmirroring_sink_resume_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	int ret;

	ret = scmirroring_sink_resume(scmirroring_sink);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_video_codec_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_video_codec()
 */
int utc_media_scmirroring_sink_get_negotiated_video_codec_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	scmirroring_video_codec_e codec;

	ret = scmirroring_sink_get_negotiated_video_codec(NULL, &codec);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_video_codec_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_video_codec()
 */
int utc_media_scmirroring_sink_get_negotiated_video_codec_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;

	ret = scmirroring_sink_get_negotiated_video_codec(&scmirroring_sink, NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_video_codec_n3
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_video_codec()
 */
int utc_media_scmirroring_sink_get_negotiated_video_codec_n3(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	scmirroring_video_codec_e codec;

	ret = scmirroring_sink_get_negotiated_video_codec(&scmirroring_sink, &codec);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_video_resolution_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_video_resolution()
 */
int utc_media_scmirroring_sink_get_negotiated_video_resolution_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int width;
	int height;

	ret = scmirroring_sink_get_negotiated_video_resolution(NULL, &width, &height);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_video_resolution_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_video_resolution()
 */
int utc_media_scmirroring_sink_get_negotiated_video_resolution_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int width;
	int height;

	ret = scmirroring_sink_get_negotiated_video_resolution(&scmirroring_sink, NULL, &height);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_video_resolution_n3
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_video_resolution()
 */
int utc_media_scmirroring_sink_get_negotiated_video_resolution_n3(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int width;
	int height;

	ret = scmirroring_sink_get_negotiated_video_resolution(&scmirroring_sink, &width, NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_video_resolution_n4
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_video_resolution()
 */
int utc_media_scmirroring_sink_get_negotiated_video_resolution_n4(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int width;
	int height;

	ret = scmirroring_sink_get_negotiated_video_resolution(&scmirroring_sink, &width, &height);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_video_frame_rate_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_video_frame_rate()
 */
int utc_media_scmirroring_sink_get_negotiated_video_frame_rate_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int frame_rate;

	ret = scmirroring_sink_get_negotiated_video_frame_rate(NULL, &frame_rate);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_video_frame_rate_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_video_frame_rate()
 */
int utc_media_scmirroring_sink_get_negotiated_video_frame_rate_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;

	ret = scmirroring_sink_get_negotiated_video_frame_rate(&scmirroring_sink, NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_video_frame_rate_n3
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_video_frame_rate()
 */
int utc_media_scmirroring_sink_get_negotiated_video_frame_rate_n3(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int frame_rate;

	ret = scmirroring_sink_get_negotiated_video_frame_rate(&scmirroring_sink, &frame_rate);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_audio_codec_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_audio_codec()
 */
int utc_media_scmirroring_sink_get_negotiated_audio_codec_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	scmirroring_audio_codec_e codec;

	ret = scmirroring_sink_get_negotiated_audio_codec(NULL, &codec);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_audio_codec_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_audio_codec()
 */
int utc_media_scmirroring_sink_get_negotiated_audio_codec_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;

	ret = scmirroring_sink_get_negotiated_audio_codec(&scmirroring_sink, NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_audio_codec_n3
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_audio_codec()
 */
int utc_media_scmirroring_sink_get_negotiated_audio_codec_n3(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	scmirroring_audio_codec_e codec;

	ret = scmirroring_sink_get_negotiated_audio_codec(&scmirroring_sink, &codec);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_audio_channel_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_audio_channel()
 */
int utc_media_scmirroring_sink_get_negotiated_audio_channel_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int channel;

	ret = scmirroring_sink_get_negotiated_audio_channel(NULL, &channel);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_audio_channel_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_audio_channel()
 */
int utc_media_scmirroring_sink_get_negotiated_audio_channel_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;

	ret = scmirroring_sink_get_negotiated_audio_channel(&scmirroring_sink, NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_audio_channel_n3
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_audio_channel()
 */
int utc_media_scmirroring_sink_get_negotiated_audio_channel_n3(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int channel;

	ret = scmirroring_sink_get_negotiated_audio_channel(&scmirroring_sink, &channel);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_audio_sample_rate_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_audio_sample_rate()
 */
int utc_media_scmirroring_sink_get_negotiated_audio_sample_rate_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int sample_rate;

	ret = scmirroring_sink_get_negotiated_audio_sample_rate(NULL, &sample_rate);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_audio_sample_rate_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_audio_sample_rate()
 */
int utc_media_scmirroring_sink_get_negotiated_audio_sample_rate_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;

	ret = scmirroring_sink_get_negotiated_audio_sample_rate(&scmirroring_sink, NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_audio_sample_rate_n3
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_audio_sample_rate()
 */
int utc_media_scmirroring_sink_get_negotiated_audio_sample_rate_n3(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int sample_rate;

	ret = scmirroring_sink_get_negotiated_audio_sample_rate(&scmirroring_sink, &sample_rate);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_audio_bitwidth_n1
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_audio_bitwidth()
 */
int utc_media_scmirroring_sink_get_negotiated_audio_bitwidth_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int bitwidth;

	ret = scmirroring_sink_get_negotiated_audio_bitwidth(NULL, &bitwidth);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_audio_bitwidth_n2
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_audio_bitwidth()
 */
int utc_media_scmirroring_sink_get_negotiated_audio_bitwidth_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;

	ret = scmirroring_sink_get_negotiated_audio_bitwidth(&scmirroring_sink, NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_scmirroring_sink_get_negotiated_audio_bitwidth_n3
 * @since_tizen		2.4
 * @description		Negative test case of scmirroring_sink_get_negotiated_audio_bitwidth()
 */
int utc_media_scmirroring_sink_get_negotiated_audio_bitwidth_n3(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int bitwidth;

	ret = scmirroring_sink_get_negotiated_audio_bitwidth(&scmirroring_sink, &bitwidth);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase	    utc_media_scmirroring_sink_get_current_state_p1
 * @since_tizen	 5.0
 * @description	 Positive test case of scmirroring_sink_get_current_state()
 */
int utc_media_scmirroring_sink_get_current_state_p1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int state;

	ret = scmirroring_sink_get_current_state(scmirroring_sink, &state);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);
	assert_eq(state, SCMIRRORING_SINK_STATE_NULL);

	return 0;
}

/**
 * @testcase	    utc_media_scmirroring_sink_get_current_state_p2
 * @since_tizen	 5.0
 * @description	 Positive test case of scmirroring_sink_get_current_state()
 */
int utc_media_scmirroring_sink_get_current_state_p2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int state;
	scmirroring_sink_prepare(scmirroring_sink);
	ret = scmirroring_sink_get_current_state(scmirroring_sink, &state);
	assert_eq(ret, SCMIRRORING_ERROR_NONE);
	assert_eq(state, SCMIRRORING_SINK_STATE_PREPARED);

	return 0;
}

/**
 * @testcase	    utc_media_scmirroring_sink_get_current_state_n1
 * @since_tizen	 5.0
 * @description	 Negative test case of scmirroring_sink_get_current_state()
 */
int utc_media_scmirroring_sink_get_current_state_n1(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int state;
	ret = scmirroring_sink_get_current_state(NULL, &state);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase	    utc_media_scmirroring_sink_get_current_state_n2
 * @since_tizen	 5.0
 * @description	 Negative test case of scmirroring_sink_get_current_state()
 */
int utc_media_scmirroring_sink_get_current_state_n2(void)
{
	if(!_is_WFD_supported){
		fprintf(stderr, "This device is not support Wi-Fi Direct!\n");
		assert_eq(_start_ret, SCMIRRORING_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert(!_is_broken);

	int ret;
	int state;
	ret = scmirroring_sink_get_current_state(scmirroring_sink, NULL);
	assert_eq(ret, SCMIRRORING_ERROR_INVALID_PARAMETER);

	return 0;
}