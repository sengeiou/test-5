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
#include <fcntl.h>
#include <libintl.h>
#include <Evas.h>
#include <Elementary.h>
#include <glib.h>

#include <system_info.h>

#include <widget_errno.h>
#include <widget_service.h>
#include <widget_viewer_evas.h>

#include "assert.h"
#include "tct_app_common.h"

//& set: utc-widget_viewer_evas

#include "assert.h"
#define SAMPLE_NAME            "sample"
#define SAMPLE_PKGNAME         "org.tizen.sample"
#define SAMPLE_PREVIEW         "/opt/apps/"SAMPLE_PKGNAME"/shared/preview.png"
#define SAMPLE_WIDGET          SAMPLE_PKGNAME				// mouse_event = true, touch_effect = false, need_frame = false, nodisplay = false, 2x2
#define NEGATIVE_SAMPLE_WIDGET SAMPLE_PKGNAME".widgetn"
#define DEFAULT_PERIOD         0.0f
#define TIMEOUT			   30.0F
#define ABORT_WIDGET		"org.example.abortwidget"
#define SELF_EXIT_WIDGET	"org.example.selfexitwidget"

static struct info {
	int is_asserted;
	bool appwidget_supported;
} s_info = {
		.is_asserted = 0,
		.appwidget_supported = 0
};

typedef int (*test_case_cb)(Evas_Object *widget);

static char *content_info;

static int assert_eq_for_callback(int var, int value)
{
	assert_eq(var, value);
	return 0;
}

static int assert_neq_for_callback(int var, int value)
{
	assert_neq(var, value);
	return 0;
}

/**
 * Setup the TC environment
 */
/**
 * @function		utc_widget_viewer_evas_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_widget_viewer_evas_startup(void)
{
	/**
	 * @note
	 * Install sample widget package
	 */
	s_info.is_asserted = 0;

	system_info_get_platform_bool("http://tizen.org/feature/shell.appwidget", &(s_info.appwidget_supported));
	TCT_UTCCheckInstalledApp(3, SAMPLE_PKGNAME, "org.tizen.sample.crash", "org.example.swidget");

	elm_init(0, NULL);
}

static int tct_async_ret_callback(test_case_cb cb, struct widget_evas_event_info *info)
{
	assert_neq(info, NULL);
	assert_eq(info->error, WIDGET_ERROR_NONE);
	assert_neq(info->widget_app_id, NULL);
	assert_eq(strcmp(info->widget_app_id, SAMPLE_WIDGET), 0);
	assert_eq(info->event, WIDGET_EVENT_CREATED);

	return 0;
}

static void _widget_create_cb(void *data, Evas_Object *obj, void *event_info)
{
	struct widget_evas_event_info *info = event_info;
	test_case_cb cb = data;
	int ret;

	ret = tct_async_ret_callback(cb, info);
	s_info.is_asserted = ret;

	if (!ret && cb) {
		int w;
		int h;
		cb(obj);

		ret = widget_service_get_size(WIDGET_SIZE_TYPE_4x4, &w, &h);
		if (ret == WIDGET_ERROR_NONE) {
			evas_object_resize(obj, w, h);
			evas_object_color_set(obj, 255, 255, 255, 255); /* Just for the line-coverage */
			evas_object_hide(obj);
			evas_object_show(obj);
		}
	}

	elm_exit();
}

/**
 * @function		utc_widget_viewer_evas_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_widget_viewer_evas_cleanup(void)
{
	/**
	 * @note
	 * Uninstall sample widget package
	 */
	s_info.is_asserted = 0;
	elm_shutdown();
}

/**
 * @testcase		utc_widget_viewer_evas_init_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_init
 */
int utc_widget_viewer_evas_init_n(void)
{
	int ret;

	ret = widget_viewer_evas_init(NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_fini_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_fini
 */
int utc_widget_viewer_evas_fini_n(void)
{
	int ret;
	/**
	 * Not initialized
	 */
	ret = widget_viewer_evas_fini();
	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq(ret, WIDGET_ERROR_FAULT);
	}

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_add_widget_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_add_widget
 */
int utc_widget_viewer_evas_add_widget_n(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int ret;

	if (s_info.appwidget_supported == false) {
		widget = widget_viewer_evas_add_widget(NULL, NULL, NULL, 0.0f);
		assert_eq(widget, NULL);
		return 0;
	}

	/**
	 * @NOTE
	 * Not initialized
	 */
	widget = widget_viewer_evas_add_widget(NULL, NULL, NULL, 0.0f);
	assert_eq(widget, NULL);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	/**
	 * @NOTE
	 * Initialized but parent object(window) is invalid
	 */
	widget = widget_viewer_evas_add_widget(NULL, NULL, NULL, 0.0f);
	assert_eq(widget, NULL);

	/**
	 * @NOTE
	 * Initialized but widget package id is invalid
	 */
	widget = widget_viewer_evas_add_widget(win, NULL, NULL, 0.0f);
	assert_eq(widget, NULL);

	/**
	 * @NOTE
	 * Initialized but widget package id is invalid.
	 */
	widget = widget_viewer_evas_add_widget(win, NEGATIVE_SAMPLE_WIDGET, NULL, 0.0f);
	assert_eq(widget, NULL);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_add_widget_n2
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_add_widget
 */
int utc_widget_viewer_evas_add_widget_n2(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	Evas_Object *widget2;
	bundle *b;
	bundle_raw *r;
	int ret;
	int len;

	if (s_info.appwidget_supported == false) {
		widget = widget_viewer_evas_add_widget(NULL, "org.example.swidget", NULL, 0.0f);
		assert_eq(widget, NULL);
		return 0;
	}

	win = elm_win_add(NULL, "swidget", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	b = bundle_create();
	bundle_add_str(b, "example_widget", "swidget");
	bundle_encode(b, &r, &len);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, "org.example.swidget", (const char *)r, 0.0f);
	assert_neq(widget, NULL);

	widget2 = widget_viewer_evas_add_widget(win, "org.example.swidget", (const char *)r, 0.0f);
	assert_eq(widget2, NULL);
	assert_eq(get_last_result(), WIDGET_ERROR_MAX_EXCEEDED);

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_notify_resumed_status_of_viewer_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_notify_resumed_status_of_viewer
 */
int utc_widget_viewer_evas_notify_resumed_status_of_viewer_n(void)
{
	int ret;

	/**
	 * Not initialized
	 */
	ret = widget_viewer_evas_notify_resumed_status_of_viewer();
	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq(ret, WIDGET_ERROR_FAULT);
	}

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_notify_paused_status_of_viewer_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_notify_paused_status_of_viewer
 */
int utc_widget_viewer_evas_notify_paused_status_of_viewer_n(void)
{
	int ret;

	/**
	 * Not initialized
	 */
	ret = widget_viewer_evas_notify_paused_status_of_viewer();
	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq(ret, WIDGET_ERROR_FAULT);
	}

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_notify_orientation_of_viewer_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_notify_orientation_of_viewer
 */
int utc_widget_viewer_evas_notify_orientation_of_viewer_n(void)
{
	int ret;
	Evas_Object *win;

	/**
	 * Not initialized
	 */
	ret = widget_viewer_evas_notify_orientation_of_viewer(90);
	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, WIDGET_ERROR_FAULT);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	/**
	 * Invalid parameter
	 */
	ret = widget_viewer_evas_notify_orientation_of_viewer(-30);
	assert_eq(ret, WIDGET_ERROR_INVALID_PARAMETER);

	/**
	 * Invalid parameter
	 */
	ret = widget_viewer_evas_notify_orientation_of_viewer(390);
	assert_eq(ret, WIDGET_ERROR_INVALID_PARAMETER);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_pause_widget_n1
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_pause_widget
 */
int utc_widget_viewer_evas_pause_widget_n1(void)
{
	int ret;
	Evas_Object *win;

	ret = widget_viewer_evas_pause_widget(NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, WIDGET_ERROR_FAULT);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_pause_widget(NULL);
	assert_eq(ret, WIDGET_ERROR_INVALID_PARAMETER);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);

	return 0;
}


static void _widget_aborted_cb(void *data, Evas_Object *obj, void *event_info)
{
	elm_exit();
}

Eina_Bool _timer_cb(void *data)
{
	s_info.is_asserted = 1;
	elm_exit();
	return ECORE_CALLBACK_DONE;
}

/**
 * @testcase		utc_widget_viewer_evas_pause_widget_n2
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_pause_widget
 */
int utc_widget_viewer_evas_pause_widget_n2(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	bundle *b;
	bundle_raw *r;
	int w, h;
	int ret;
	int len;

	if (s_info.appwidget_supported == false) {
		widget = widget_viewer_evas_add_widget(NULL, SAMPLE_PKGNAME, NULL, 0.0f);
		assert_eq(widget, NULL);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	b = bundle_create();
	bundle_add_str(b, "sample", "sample");
	bundle_encode(b, &r, &len);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, ABORT_WIDGET, (const char *)r, 0.0f);
	assert_neq(widget, NULL);

	ret = widget_viewer_evas_pause_widget(widget);
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATE_ABORTED, _widget_aborted_cb, NULL);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_color_set(widget, 255, 255, 255, 255); /* Just for the line-coverage */
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	bundle_free(b);
	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);

	return s_info.is_asserted;
}

/**
 * @testcase		utc_widget_viewer_evas_resume_widget_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_resume_widget
 */
int utc_widget_viewer_evas_resume_widget_n(void)
{
	int ret;
	Evas_Object *win;

	ret = widget_viewer_evas_resume_widget(NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, WIDGET_ERROR_FAULT);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_resume_widget(NULL);
	assert_eq(ret, WIDGET_ERROR_INVALID_PARAMETER);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_set_option_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_set_option
 */
int utc_widget_viewer_evas_set_option_n(void)
{
	int ret;

	ret = widget_viewer_evas_set_option((widget_evas_conf_e)-1, 0);
	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, WIDGET_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_get_content_info_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_get_content_info
 */
int utc_widget_viewer_evas_get_content_info_n(void)
{
	const char *str;
	Evas_Object *win;
	int ret;

	str = widget_viewer_evas_get_content_info(NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq(str, NULL);
		return 0;
	}

	assert_eq(str, NULL);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	str = widget_viewer_evas_get_content_info(NULL);
	assert_eq(str, NULL);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_get_title_string_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_get_title_string
 */
int utc_widget_viewer_evas_get_title_string_n(void)
{
	const char *str;
	Evas_Object *win;
	Evas_Object *widgetn;
	int ret;

	str = widget_viewer_evas_get_title_string(NULL);

	if (s_info.appwidget_supported == false) {
		assert_eq(str, NULL);
		return 0;
	}

	assert_eq(str, NULL);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	widgetn = evas_object_rectangle_add(evas_object_evas_get(win));
	evas_object_resize(widgetn, 100, 100);
	evas_object_show(widgetn);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	str = widget_viewer_evas_get_title_string(NULL);
	assert_eq(str, NULL);

	str = widget_viewer_evas_get_title_string(widgetn);
	assert_eq(str, NULL);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(widgetn);
	evas_object_del(win);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_get_widget_id_n1
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_get_widget_id
 */
int utc_widget_viewer_evas_get_widget_id_n1(void)
{
	const char *str;
	Evas_Object *win;
	Evas_Object *widgetn;
	int ret;

	str = widget_viewer_evas_get_widget_id(NULL);

	if (s_info.appwidget_supported == false) {
		assert_eq(str, NULL);
		return 0;
	}

	assert_eq(str, NULL);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	widgetn = evas_object_rectangle_add(evas_object_evas_get(win));
	evas_object_resize(widgetn, 100, 100);
	evas_object_show(widgetn);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	str = widget_viewer_evas_get_widget_id(NULL);
	assert_eq(str, NULL);

	str = widget_viewer_evas_get_widget_id(widgetn);
	assert_eq(str, NULL);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(widgetn);
	evas_object_del(win);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_get_widget_id_n2
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_get_widget_id
 */
int utc_widget_viewer_evas_get_widget_id_n2(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int ret;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget_viewer_evas_get_widget_id(NULL);
	assert_eq(get_last_result(), WIDGET_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_get_period_n1
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_get_period
 */
int utc_widget_viewer_evas_get_period_n1(void)
{
	double period;
	int ret;
	Evas_Object *win;
	Evas_Object *widgetn;

	period = widget_viewer_evas_get_period(NULL);

	if (s_info.appwidget_supported == false) {
		assert_eq(period, -1.0f);
		return 0;
	}

	assert_eq(period, -1.0f);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	widgetn = evas_object_rectangle_add(evas_object_evas_get(win));
	evas_object_resize(widgetn, 100, 100);
	evas_object_show(widgetn);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	period = widget_viewer_evas_get_period(NULL);
	assert_eq(period, -1.0f);

	period = widget_viewer_evas_get_period(widgetn);
	assert_eq(period, -1.0f);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(widgetn);
	evas_object_del(win);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_get_period_n2
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_get_period
 */
int utc_widget_viewer_evas_get_period_n2(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int ret;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget_viewer_evas_get_widget_id(NULL);
	assert_eq(get_last_result(), WIDGET_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_cancel_click_event_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_cancel_click_event
 */
int utc_widget_viewer_evas_cancel_click_event_n(void)
{
	int ret;
	Evas_Object *win;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	widget_viewer_evas_cancel_click_event(NULL);
	/** There is no returns */
	/** void widget_viewer_evas_cancel_click_event(Evas_Object *widget); */
	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget_viewer_evas_cancel_click_event(NULL);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_disable_preview_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_disable_preview
 */
int utc_widget_viewer_evas_disable_preview_n(void)
{
	Evas_Object *win;
	int ret;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	widget_viewer_evas_disable_preview(NULL);
	/** There is no returns */
	/** void widget_viewer_evas_disable_preview(Evas_Object *widget); */
	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget_viewer_evas_disable_preview(NULL);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_disable_overlay_text_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_disable_overlay_text
 */
int utc_widget_viewer_evas_disable_overlay_text_n(void)
{
	Evas_Object *win;
	int ret;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	widget_viewer_evas_disable_overlay_text(NULL);
	/** There is no returns */
	/** void widget_viewer_evas_disable_overlay_text(Evas_Object *widget); */
	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget_viewer_evas_disable_overlay_text(NULL);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_disable_loading_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_disable_loading
 */
int utc_widget_viewer_evas_disable_loading_n(void)
{
	Evas_Object *win;
	int ret;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	widget_viewer_evas_disable_loading(NULL);
	/** There is no returns */
	/** void widget_viewer_evas_disable_loading(Evas_Object *widget); */

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget_viewer_evas_disable_loading(NULL);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return 0;
}

static void _widget_mouse_up_cb(void *data, Evas_Object *obj, void *event_info)
{
	int ret;

	ret = widget_viewer_evas_feed_mouse_up_event(obj);
	s_info.is_asserted = assert_eq_for_callback(ret, WIDGET_ERROR_NONE);
	elm_exit();
}

/**
 * @testcase		utc_widget_viewer_evas_feed_mouse_up_event_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_activate_faulted_widget
 */
int utc_widget_viewer_evas_feed_mouse_up_event_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_WIDGET, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_mouse_up_cb, NULL);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

/**
 * @testcase		utc_widget_viewer_evas_feed_mouse_up_event_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_feed_mouse_up_event
 */
int utc_widget_viewer_evas_feed_mouse_up_event_n(void)
{
	int ret;
	Evas_Object *win;
	Evas_Object *widgetn;

	ret = widget_viewer_evas_feed_mouse_up_event(NULL);

	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, WIDGET_ERROR_FAULT);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	widgetn = evas_object_rectangle_add(evas_object_evas_get(win));
	evas_object_resize(widgetn, 100, 100);
	evas_object_show(widgetn);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_feed_mouse_up_event(NULL);
	assert_eq(ret, WIDGET_ERROR_INVALID_PARAMETER);

	ret = widget_viewer_evas_feed_mouse_up_event(widgetn);
	assert_eq(ret, WIDGET_ERROR_INVALID_PARAMETER);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(widgetn);
	evas_object_del(win);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_activate_faulted_widget_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_activate_faulted_widget
 */
int utc_widget_viewer_evas_activate_faulted_widget_n(void)
{
	int ret;
	Evas_Object *win;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	widget_viewer_evas_activate_faulted_widget(NULL);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget_viewer_evas_activate_faulted_widget(NULL);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_is_faulted_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_is_faulted
 */
int utc_widget_viewer_evas_is_faulted_n(void)
{
	int ret;
	Evas_Object *win;

	/* Not initialized */
	ret = widget_viewer_evas_is_faulted(NULL);

	if (s_info.appwidget_supported == false) {
		assert_eq(ret, 0);
		return 0;
	}

	assert_eq(ret, 0);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_is_faulted(NULL);
	assert_eq(ret, 0);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_freeze_visibility_n1
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_freeze_visibility
 */
int utc_widget_viewer_evas_freeze_visibility_n1(void)
{
	int ret;
	Evas_Object *win;
	Evas_Object *widgetn;

	/* Not initialized */
	ret = widget_viewer_evas_freeze_visibility(NULL, WIDGET_VISIBILITY_STATUS_SHOW_FIXED);

	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, WIDGET_ERROR_FAULT);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	widgetn = evas_object_rectangle_add(evas_object_evas_get(win));
	evas_object_resize(widgetn, 100, 100);
	evas_object_show(widgetn);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_freeze_visibility(NULL, WIDGET_VISIBILITY_STATUS_SHOW_FIXED);
	assert_eq(ret, WIDGET_ERROR_INVALID_PARAMETER);

	ret = widget_viewer_evas_freeze_visibility(widgetn, WIDGET_VISIBILITY_STATUS_SHOW_FIXED);
	assert_eq(ret, WIDGET_ERROR_INVALID_PARAMETER);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(widgetn);
	evas_object_del(win);
	return 0;
}

static int tc_freeze_n(Evas_Object *widget)
{
	int ret;

	ret = widget_viewer_evas_freeze_visibility(widget, -1);
	s_info.is_asserted = assert_eq_for_callback(ret, WIDGET_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_freeze_visibility_n2
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_freeze_visibility
 */
int utc_widget_viewer_evas_freeze_visibility_n2(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		ret = widget_viewer_evas_freeze_visibility(NULL, WIDGET_VISIBILITY_STATUS_SHOW_FIXED);
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_freeze_n);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

/**
 * @testcase		utc_widget_viewer_evas_thaw_visibility_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_thaw_visibility
 */
int utc_widget_viewer_evas_thaw_visibility_n(void)
{
	int ret;
	Evas_Object *win;
	Evas_Object *widgetn;

	ret = widget_viewer_evas_thaw_visibility(NULL);

	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, WIDGET_ERROR_FAULT);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	widgetn = evas_object_rectangle_add(evas_object_evas_get(win));
	evas_object_resize(widgetn, 100, 100);
	evas_object_show(widgetn);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_thaw_visibility(NULL);
	assert_eq(ret, WIDGET_ERROR_INVALID_PARAMETER);

	ret = widget_viewer_evas_thaw_visibility(widgetn);
	assert_eq(ret, WIDGET_ERROR_INVALID_PARAMETER);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(widgetn);
	evas_object_del(win);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_is_visibility_frozen_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_is_visibility_frozen
 */
int utc_widget_viewer_evas_is_visibility_frozen_n(void)
{
	bool ret;
	Evas_Object *win;
	Evas_Object *widgetn;

	ret = widget_viewer_evas_is_visibility_frozen(NULL);

	if (s_info.appwidget_supported == false) {
		assert_eq(ret, false);
		return 0;
	}

	assert_eq(ret, false);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	widgetn = evas_object_rectangle_add(evas_object_evas_get(win));
	evas_object_resize(widgetn, 100, 100);
	evas_object_show(widgetn);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_is_visibility_frozen(NULL);
	assert_eq(ret, false);

	ret = widget_viewer_evas_is_visibility_frozen(widgetn);
	assert_eq(ret, false);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(widgetn);
	evas_object_del(win);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_is_widget_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_is_widget
 */
int utc_widget_viewer_evas_is_widget_n(void)
{
	int ret;
	bool tmp;
	Evas_Object *win;
	Evas_Object *widgetn;

	tmp = widget_viewer_evas_is_widget(NULL);

	if (s_info.appwidget_supported == false) {
		assert_eq(tmp, false);
		return 0;
	}

	assert_eq(tmp, false);

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	widgetn = evas_object_rectangle_add(evas_object_evas_get(win));
	evas_object_resize(widgetn, 100, 100);
	evas_object_show(widgetn);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	tmp = widget_viewer_evas_is_widget(NULL);
	assert_eq(tmp, false);

	tmp = widget_viewer_evas_is_widget(widgetn);
	assert_eq(tmp, false);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(widgetn);
	evas_object_del(win);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_set_permanent_delete_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_viewer_evas_set_permanent_delete
 */
int utc_widget_viewer_evas_set_permanent_delete_n(void)
{
	int ret;
	Evas_Object *win;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	widget_viewer_evas_set_permanent_delete(NULL, 0);
	/** No returns */
	/** void widget_viewer_evas_set_permanent_delete(Evas_Object *widget, int flag); */

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	/**
	 * For the line coverage
	 */
	widget_viewer_evas_set_permanent_delete(NULL, 0);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);

	return 0;
}


/**
 * @testcase		utc_widget_viewer_evas_init_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_init
 */
int utc_widget_viewer_evas_init_p(void)
{
	Evas_Object *win;
	int ret;

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);

	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);
	evas_object_del(win);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_fini_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_fini
 */
int utc_widget_viewer_evas_fini_p(void)
{
	Evas_Object *win;
	int ret;

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq(ret, WIDGET_ERROR_NONE);
	}

	ret = widget_viewer_evas_fini();

	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, WIDGET_ERROR_NONE);
	evas_object_del(win);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_add_widget_p1
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_add_widget
 */
int utc_widget_viewer_evas_add_widget_p1(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	bundle *b;
	bundle_raw *r;
	int w, h;
	int ret;
	int len;

	if (s_info.appwidget_supported == false) {
		widget = widget_viewer_evas_add_widget(NULL, SAMPLE_PKGNAME, NULL, 0.0f);
		assert_eq(widget, NULL);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	b = bundle_create();
	bundle_add_str(b, "sample", "sample");
	bundle_encode(b, &r, &len);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, (const char *)r, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, NULL);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_color_set(widget, 255, 255, 255, 255); /* Just for the line-coverage */
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	bundle_free(b);
	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);

	return s_info.is_asserted;
}

static void _widget_deleted_cb(void *data, Evas_Object *obj, void *event_info)
{
	s_info.is_asserted = WIDGET_ERROR_NONE;
	elm_exit();
}

/**
 * @testcase		utc_widget_viewer_evas_add_widget_p2
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_add_widget
 */
int utc_widget_viewer_evas_add_widget_p2(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	bundle *b;
	bundle_raw *r;
	int w, h;
	int ret;
	int len;

	if (s_info.appwidget_supported == false) {
		widget = widget_viewer_evas_add_widget(NULL, SAMPLE_PKGNAME, NULL, 0.0f);
		assert_eq(widget, NULL);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);

	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	b = bundle_create();
	bundle_add_str(b, "sample", "sample");
	bundle_encode(b, &r, &len);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SELF_EXIT_WIDGET, (const char *)r, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, NULL);
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_DELETED, _widget_deleted_cb, NULL);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_color_set(widget, 255, 255, 255, 255); /* Just for the line-coverage */
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	bundle_free(b);
	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);

	return s_info.is_asserted;
}

static int tc_notify_resume(Evas_Object *widget)
{
	int ret;

	ret = widget_viewer_evas_notify_resumed_status_of_viewer();
	s_info.is_asserted = assert_eq_for_callback(ret, WIDGET_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_notify_resumed_status_of_viewer_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_notify_resumed_status_of_viewer
 */
int utc_widget_viewer_evas_notify_resumed_status_of_viewer_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		ret = widget_viewer_evas_notify_resumed_status_of_viewer();
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_notify_resume);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

static int tc_notify_pause(Evas_Object *widget)
{
	int ret;

	ret = widget_viewer_evas_notify_paused_status_of_viewer();
	s_info.is_asserted = assert_eq_for_callback(ret, WIDGET_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_notify_paused_status_of_viewer_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_notify_paused_status_of_viewer
 */
int utc_widget_viewer_evas_notify_paused_status_of_viewer_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		ret = widget_viewer_evas_notify_paused_status_of_viewer();
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_notify_pause);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

/**
 * @testcase		utc_widget_viewer_evas_notify_orientation_of_viewer_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_notify_orientation_of_viewer
 */
int utc_widget_viewer_evas_notify_orientation_of_viewer_p(void)
{
	Evas_Object *win;
	int ret;

	if (s_info.appwidget_supported == false) {
		ret = widget_viewer_evas_notify_orientation_of_viewer(90);
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_notify_orientation_of_viewer(90);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);

	return 0;
}

static int tc_pause(Evas_Object *widget)
{
	int ret;

	ret = widget_viewer_evas_pause_widget(widget);
	s_info.is_asserted = assert_eq_for_callback(ret, WIDGET_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_pause_widget_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_pause_widget
 */
int utc_widget_viewer_evas_pause_widget_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		ret = widget_viewer_evas_pause_widget(NULL);
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_pause);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

static int tc_resume(Evas_Object *widget)
{
	int ret;

	ret = widget_viewer_evas_resume_widget(widget);
	if (ret != WIDGET_ERROR_ALREADY_EXIST)
		s_info.is_asserted = assert_eq_for_callback(ret, WIDGET_ERROR_NONE);
	else
		s_info.is_asserted = 0;

	return s_info.is_asserted;
}

/**
 * @testcase		utc_widget_viewer_evas_resume_widget_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_resume_widget
 */
int utc_widget_viewer_evas_resume_widget_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		ret = widget_viewer_evas_resume_widget(NULL);
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_resume);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

/**
 * @testcase		utc_widget_viewer_evas_set_option_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_set_option
 */
int utc_widget_viewer_evas_set_option_p(void)
{
	int ret;

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_EVENT_AUTO_FEED, 0);

	if (s_info.appwidget_supported == false) {
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_SENSITIVE_MOVE, 0);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_EVENT_AUTO_FEED, 0);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_EASY_MODE, 0);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_USE_FIXED_SIZE, 0);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_MANUAL_PAUSE_RESUME, 0);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_SCROLL_X, 0);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_SCROLL_Y, 0);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_DELAYED_RESUME, 0);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_AUTO_RENDER_SELECTION, 0);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_DIRECT_UPDATE, 0);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_USE_RENDER_ANIMATOR, 0);
	assert_eq(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_set_option(WIDGET_VIEWER_EVAS_SKIP_ACQUIRE, 0);
	assert_eq(ret, WIDGET_ERROR_NONE);

	return 0;
}

static int tc_get_content(Evas_Object *widget)
{
	const char *str;

	/**
	 * There is no contents available
	 */
	str = widget_viewer_evas_get_content_info(widget);
	if (str && content_info && strcmp(str, content_info) == 0)
		s_info.is_asserted = 0;
	else
		s_info.is_asserted = 1;

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_get_content_info_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_get_content_info
 */
int utc_widget_viewer_evas_get_content_info_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;
	const char *str = NULL;
	bundle *b;
	int len;

	if (s_info.appwidget_supported == false) {
		str = widget_viewer_evas_get_content_info(NULL);
		assert_eq(str, NULL);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	b = bundle_create();
	assert_neq(b, NULL);

	ret = bundle_add_str(b, "CONTENT_INFO_TEST", "CONTENT_INFO_VALUE");
	assert_eq(ret, BUNDLE_ERROR_NONE);

	ret = bundle_encode(b, (bundle_raw **)&content_info, &len);
	assert_eq(ret, BUNDLE_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, content_info, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_get_content);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	bundle_free(b);
	evas_object_del(win);
	free(content_info);

	return s_info.is_asserted;
}

static int tc_get_title_string(Evas_Object *widget)
{
	const char *str;
	str = widget_viewer_evas_get_title_string(widget);
	s_info.is_asserted = assert_neq_for_callback((int)str, 0);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_get_title_string_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_get_title_string
 */
int utc_widget_viewer_evas_get_title_string_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;
	const char *str = NULL;

	if (s_info.appwidget_supported == false) {
		str = widget_viewer_evas_get_title_string(NULL);
		assert_eq(str, NULL);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_get_title_string);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

static int tc_get_widget_id(Evas_Object *widget)
{
	const char *str;

	str = widget_viewer_evas_get_widget_id(widget);
	s_info.is_asserted = assert_neq_for_callback((int)str, 0);
	s_info.is_asserted = s_info.is_asserted || assert_eq_for_callback(strcmp(str, SAMPLE_PKGNAME), 0);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_get_widget_id_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_get_widget_id
 */
int utc_widget_viewer_evas_get_widget_id_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;
	const char *str = NULL;

	if (s_info.appwidget_supported == false) {
		str = widget_viewer_evas_get_widget_id(NULL);
		assert_eq(str, NULL);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_get_widget_id);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

static int tc_get_period(Evas_Object *widget)
{
	double period;

	period = widget_viewer_evas_get_period(widget);
	s_info.is_asserted = assert_eq_for_callback((int)period, 0);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_get_period_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_get_period
 */
int utc_widget_viewer_evas_get_period_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;
	double period;

	if (s_info.appwidget_supported == false) {
		period = widget_viewer_evas_get_period(NULL);
		assert_eq((int)period, -1);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_get_period);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

static int tc_cancel_click(Evas_Object *widget)
{
	widget_viewer_evas_cancel_click_event(widget);
	/** No returns */
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_cancel_click_event_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_cancel_click_event
 */
int utc_widget_viewer_evas_cancel_click_event_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_cancel_click);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

static int tc_disable_preview_p(Evas_Object *widget)
{
	widget_viewer_evas_disable_preview(widget);
	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_disable_preview_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_disable_preview
 */
int utc_widget_viewer_evas_disable_preview_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int ret;
	int w;
	int h;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_disable_preview_p);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return ret;
}

/**
 * @testcase		utc_widget_viewer_evas_disable_overlay_text_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_disable_overlay_text
 */
int utc_widget_viewer_evas_disable_overlay_text_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	/* No created callback required */
	widget_viewer_evas_disable_overlay_text(widget);

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

/**
 * @testcase		utc_widget_viewer_evas_disable_loading_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_disable_loading
 */
int utc_widget_viewer_evas_disable_loading_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	/* No created callback required */
	widget_viewer_evas_disable_loading(widget);

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

static void _widget_activate_faulted_cb(void *data, Evas_Object *obj, void *event_info)
{
	widget_viewer_evas_activate_faulted_widget(obj);
	s_info.is_asserted = WIDGET_ERROR_NONE;
}

/**
 * @testcase		utc_widget_viewer_evas_activate_faulted_widget_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_activate_faulted_widget
 */
int utc_widget_viewer_evas_activate_faulted_widget_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SELF_EXIT_WIDGET, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, NULL);
	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_DELETED, _widget_activate_faulted_cb, NULL);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

static int tc_faulted(Evas_Object *widget)
{
	int ret;

	ret = widget_viewer_evas_is_faulted(widget);
	s_info.is_asserted = assert_neq_for_callback(ret, 1);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_is_faulted_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_is_faulted
 */
int utc_widget_viewer_evas_is_faulted_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		ret = widget_viewer_evas_is_faulted(NULL); /* Return type is boolean */
		assert_eq(ret, false);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_WIDGET, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_faulted);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return 0;
}

static int tc_freeze(Evas_Object *widget)
{
	int ret;

	ret = widget_viewer_evas_freeze_visibility(widget, WIDGET_VISIBILITY_STATUS_SHOW_FIXED);
	s_info.is_asserted = assert_eq_for_callback(ret, WIDGET_ERROR_NONE);

	ret = widget_viewer_evas_freeze_visibility(widget, WIDGET_VISIBILITY_STATUS_HIDE_FIXED);
	s_info.is_asserted = assert_eq_for_callback(ret, WIDGET_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_freeze_visibility_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_freeze_visibility
 */
int utc_widget_viewer_evas_freeze_visibility_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		ret = widget_viewer_evas_freeze_visibility(NULL, WIDGET_VISIBILITY_STATUS_SHOW_FIXED);
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_freeze);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

static int tc_thaw(Evas_Object *widget)
{
	int ret;

	ret = widget_viewer_evas_thaw_visibility(widget);
	s_info.is_asserted = assert_eq_for_callback(ret, WIDGET_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_thaw_visibility_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_thaw_visibility
 */
int utc_widget_viewer_evas_thaw_visibility_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		ret = widget_viewer_evas_thaw_visibility(NULL);
		assert_eq(ret, WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_thaw);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

static int tc_get_visiblity_cb(Evas_Object *widget)
{
	bool ret;

	ret = widget_viewer_evas_is_visibility_frozen(widget);
	s_info.is_asserted = assert_eq_for_callback(ret, false);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_is_visibility_frozen_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_is_visibility_frozen
 */
int utc_widget_viewer_evas_is_visibility_frozen_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		ret = widget_viewer_evas_is_visibility_frozen(NULL); /* Return type is boolean */
		assert_eq(ret, false);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_get_visiblity_cb);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

/**
 * @testcase		utc_widget_viewer_evas_is_widget_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_is_widget
 */
int utc_widget_viewer_evas_is_widget_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int ret;

	if (s_info.appwidget_supported == false) {
		ret = widget_viewer_evas_is_widget(NULL); /* Return type is boolean */
		assert_eq(ret, false);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	ret = widget_viewer_evas_is_widget(widget);
	assert_eq(ret, 1);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

/**
 * @testcase		utc_widget_viewer_evas_set_permanent_delete_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_viewer_evas_set_permanent_delete
 */
int utc_widget_viewer_evas_set_permanent_delete_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		/* Can not be tested */
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	/* No returns */
	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

static int tc_instance_id(Evas_Object *widget)
{
	const char *instance_id;

	instance_id = widget_viewer_evas_get_widget_instance_id(widget);
	s_info.is_asserted = assert_neq_for_callback((int)instance_id, 0);

	return 0;
}

/**
 * @testcase		utc_widget_viewer_evas_get_widget_instance_id_p
 * @since_tizen		4.0
 * @description		Positive test case of widget_viewer_evas_get_widget_instance_id
 */
int utc_widget_viewer_evas_get_widget_instance_id_p(void)
{
	Evas_Object *win;
	Evas_Object *widget;
	int w, h;
	int ret;

	if (s_info.appwidget_supported == false) {
		widget_viewer_evas_get_widget_instance_id(NULL);
		assert_eq(get_last_result(), WIDGET_ERROR_NOT_SUPPORTED);
		return 0;
	}

	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	assert_neq(win, NULL);
	evas_object_resize(win, 480, 800);
	evas_object_show(win);

	ret = widget_viewer_evas_init(win);
	assert_eq(ret, WIDGET_ERROR_NONE);

	widget = widget_viewer_evas_add_widget(win, SAMPLE_PKGNAME, NULL, 0.0f);
	assert_neq(widget, NULL);

	evas_object_smart_callback_add(widget, WIDGET_SMART_SIGNAL_WIDGET_CREATED, _widget_create_cb, tc_instance_id);

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_resize(widget, w, h);
	evas_object_show(widget);

	ecore_timer_add(TIMEOUT, _timer_cb, NULL);
	elm_run();

	widget_viewer_evas_set_permanent_delete(widget, 1);
	evas_object_del(widget);

	ret = widget_viewer_evas_fini();
	assert_eq(ret, WIDGET_ERROR_NONE);

	evas_object_del(win);
	return s_info.is_asserted;
}

/* End of a file */
