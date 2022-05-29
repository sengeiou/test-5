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
#include "assert_common.h"
#include "tct_app_common.h"

#define SAMPLE_NAME            "sample"
#define SAMPLE_PKGNAME         "org.tizen.sample"
#define SAMPLE_PREVIEW         "/opt/apps/"SAMPLE_PKGNAME"/shared/preview.png"
#define SAMPLE_WIDGET          SAMPLE_PKGNAME // mouse_event = true, touch_effect = false, need_frame = false, nodisplay = false, 2x2
#define NEGATIVE_SAMPLE_WIDGET SAMPLE_PKGNAME"n"

static struct info {
	int is_asserted;
	bool appwidget_supported;
} s_info = {
	.is_asserted = 0,
	.appwidget_supported = 0
};

static int lifecycle_resume;
static int result = -1;

typedef int (*test_case_cb)(Evas_Object *widget);


/**
 * Setup the TC environment
 */
/**
 * @function		utc_widget_service_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_widget_service_startup(void)
{
	/**
	 * @note
	 * Install sample widget package
	 */
	s_info.is_asserted = 0;

	system_info_get_platform_bool("http://tizen.org/feature/shell.appwidget", &(s_info.appwidget_supported));

	TCT_UTCCheckInstalledApp(2, "org.tizen.sample", "org.tizen.sample_widget");
}

/**
 * @function		utc_widget_service_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_widget_service_cleanup(void)
{
	/**
	 * @note
	 * Uninstall sample widget package
	 */
	s_info.is_asserted = 0;
}

/**
 * Negative TC started
 */
int utc_widget_service_get_size_n(void)
{
	int w;
	int h;
	int ret;

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_UNKNOWN, &w, &h);

	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_size_type_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_size()
 */
int utc_widget_service_get_size_type_n(void)
{
	widget_size_type_e type;
	int ret;

	/* Out-param is NULL */
	ret = widget_service_get_size_type(1, 1, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}
	/* Invalid width & height */
	ret = widget_service_get_size_type(1, 1, &type);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_need_of_mouse_event_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_need_of_mouse_event()
 */
int utc_widget_service_get_need_of_mouse_event_n(void)
{
	int ret;
	bool mouse_event;

	/* Package name is not valid */
	ret = widget_service_get_need_of_mouse_event(NULL, WIDGET_SIZE_TYPE_2x2, &mouse_event);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_need_of_touch_effect_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_need_of_touch_effect()
 */
int utc_widget_service_get_need_of_touch_effect_n(void)
{
	int ret;
	bool touch_effect;

	ret = widget_service_get_need_of_touch_effect(NULL, WIDGET_SIZE_TYPE_2x2, &touch_effect);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_need_of_frame_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_need_of_frame()
 */
int utc_widget_service_get_need_of_frame_n(void)
{
	int ret;
	bool frame;

	ret = widget_service_get_need_of_frame(NULL, WIDGET_SIZE_TYPE_2x2, &frame);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_trigger_update_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_trigger_update()
 */
int utc_widget_service_trigger_update_n(void)
{
	int ret;

	ret = widget_service_trigger_update(NULL, NULL, NULL, 0);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	/**
	 * @TODO:
	 *  This case, return value should be WIDGET_ERROR_NOT_EXIST
	 *  If it is okay for security view.
	 */

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_change_period_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_change_period()
 */
int utc_widget_service_change_period_n(void)
{
	int ret;

	ret = widget_service_change_period(NULL, NULL, -0.1f);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_widget_list_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_widget_list()
 */
int utc_widget_service_get_widget_list_n(void)
{
	int ret;

	ret = widget_service_get_widget_list(NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_main_app_id_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_main_app_id()
 */
int utc_widget_service_get_main_app_id_n(void)
{
	char *ret;

	ret = widget_service_get_main_app_id(NEGATIVE_SAMPLE_WIDGET);
	assert_eq_with_exit(ret, NULL);

	ret = widget_service_get_main_app_id(NULL);
	assert_eq_with_exit(ret, NULL);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_widget_list_by_pkgid_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_widget_list_by_pkgid()
 */
int utc_widget_service_get_widget_list_by_pkgid_n(void)
{
	int ret;

	ret = widget_service_get_widget_list_by_pkgid(NULL, NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_widget_id_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_widget_id()
 */
int utc_widget_service_get_widget_id_n(void)
{
	char *ret;

	ret = widget_service_get_widget_id(NULL);
	assert_eq_with_exit(ret, NULL);

	ret = widget_service_get_widget_id(NEGATIVE_SAMPLE_WIDGET);
	assert_eq_with_exit(ret, NULL);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_app_id_of_setup_app_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_app_id_of_setup_app()
 */
int utc_widget_service_get_app_id_of_setup_app_n(void)
{
	char *ret;

	ret = widget_service_get_app_id_of_setup_app(NULL);
	assert_eq_with_exit(ret, NULL);

	ret = widget_service_get_app_id_of_setup_app(NEGATIVE_SAMPLE_WIDGET);
	assert_eq_with_exit(ret, NULL);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_package_id_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_package_id()
 */
int utc_widget_service_get_package_id_n(void)
{
	char *ret;

	ret = widget_service_get_package_id(NULL);
	assert_eq_with_exit(ret, NULL);

	ret = widget_service_get_package_id(NEGATIVE_SAMPLE_WIDGET);
	assert_eq_with_exit(ret, NULL);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_name_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_name()
 */
int utc_widget_service_get_name_n(void)
{
	char *ret;

	ret = widget_service_get_name(NULL, NULL);
	assert_eq_with_exit(ret, NULL);

	ret = widget_service_get_name(NEGATIVE_SAMPLE_WIDGET, NULL);
	assert_eq_with_exit(ret, NULL);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_preview_image_path_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_preview_image_path()
 */
int utc_widget_service_get_preview_image_path_n(void)
{
	char *ret;

	ret = widget_service_get_preview_image_path(NULL, WIDGET_SIZE_TYPE_UNKNOWN);
	assert_eq_with_exit(ret, NULL);

	ret = widget_service_get_preview_image_path(NEGATIVE_SAMPLE_WIDGET, WIDGET_SIZE_TYPE_UNKNOWN);
	assert_eq_with_exit(ret, NULL);

	ret = widget_service_get_preview_image_path(SAMPLE_WIDGET, WIDGET_SIZE_TYPE_1x1);
	assert_eq_with_exit(ret, NULL);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_icon_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_icon()
 */
int utc_widget_service_get_icon_n(void)
{
	char *ret;

	ret = widget_service_get_icon(NULL, NULL);
	assert_eq_with_exit(ret, NULL);

	ret = widget_service_get_icon(NEGATIVE_SAMPLE_WIDGET, NULL);
	assert_eq_with_exit(ret, NULL);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_nodisplay_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_nodisplay()
 */
int utc_widget_service_get_nodisplay_n(void)
{
	int ret;

	ret = widget_service_get_nodisplay(NULL);
	if (ret == 0)
		ret = get_last_result();
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_supported_sizes_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_supported_sizes()
 */
int utc_widget_service_get_supported_sizes_n(void)
{
	int ret;
	int cnt = 20;
	int *w = NULL;
	int *h = NULL;

	ret = widget_service_get_supported_sizes(NULL, NULL, NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_supported_sizes(SAMPLE_WIDGET, NULL, NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_supported_sizes(SAMPLE_WIDGET, &cnt, NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_supported_sizes(SAMPLE_WIDGET, &cnt, (int **)&w, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_supported_sizes(NEGATIVE_SAMPLE_WIDGET, &cnt, (int **)&w, (int **)&h);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_EXIST);
	}
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_supported_size_types_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_supported_size_types()
 */
int utc_widget_service_get_supported_size_types_n(void)
{
	int ret;
	int cnt = 20;
	int *size_types = NULL;

	ret = widget_service_get_supported_size_types(NULL, NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_supported_size_types(SAMPLE_WIDGET, NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_supported_size_types(NULL, &cnt, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_supported_size_types(NULL, NULL, &size_types);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_supported_size_types(SAMPLE_WIDGET, &cnt, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_supported_size_types(NULL, &cnt, &size_types);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_supported_size_types(SAMPLE_WIDGET, NULL, &size_types);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_supported_size_types(NEGATIVE_SAMPLE_WIDGET, &cnt, &size_types);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
		assert_eq_with_exit(cnt, 0);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_widget_instance_list_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_widget_instance_list()
 */
int utc_widget_service_get_widget_instance_list_n(void)
{
	int ret;

	ret = widget_service_get_widget_instance_list(NULL, NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_set_lifecycle_event_cb_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_set_lifecycle_event_cb()
 */
int utc_widget_service_set_lifecycle_event_cb_n(void)
{
	int ret;

	ret = widget_service_set_lifecycle_event_cb(NULL, NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
return 0;;
}

/**
 * @testcase		utc_widget_service_unset_lifecycle_event_cb_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_unset_lifecycle_event_cb()
 */
int utc_widget_service_unset_lifecycle_event_cb_n(void)
{
	int ret;
	ret = widget_service_unset_lifecycle_event_cb(SAMPLE_WIDGET, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_EXIST);
	}
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_content_of_widget_instance_n
 * @since_tizen		2.3.1
 * @description		Negative test case of widget_service_get_content_of_widget_instance()
 */
int utc_widget_service_get_content_of_widget_instance_n(void)
{
	int ret;

	ret = widget_service_get_content_of_widget_instance(NULL, NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_content_of_widget_instance(SAMPLE_WIDGET, NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_content_of_widget_instance(SAMPLE_WIDGET, "error", NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	ret = widget_service_get_content_of_widget_instance(SAMPLE_WIDGET, "error", NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * Positive TC started
 */
/**
 * @testcase		utc_widget_service_get_size_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_size()
 */
int utc_widget_service_get_size_p(void)
{
	int w;
	int h;
	int ret;

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_size_type_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_size()
 */
int utc_widget_service_get_size_type_p(void)
{
	widget_size_type_e type;
	int ret;
	int w;
	int h;

	ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &w, &h);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	ret = widget_service_get_size_type(w, h, &type);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
		assert_eq_with_exit(type, WIDGET_SIZE_TYPE_2x2);
	}


	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_need_of_mouse_event_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_need_of_mouse_event()
 */
int utc_widget_service_get_need_of_mouse_event_p(void)
{
	int ret;
	bool mouse_event;

	/* Package name is not valid */
	ret = widget_service_get_need_of_mouse_event(SAMPLE_WIDGET, WIDGET_SIZE_TYPE_2x2, &mouse_event);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_need_of_touch_effect_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_need_of_touch_effect()
 */
int utc_widget_service_get_need_of_touch_effect_p(void)
{
	int ret;
	bool touch_effect;

	ret = widget_service_get_need_of_touch_effect(SAMPLE_WIDGET, WIDGET_SIZE_TYPE_2x2, &touch_effect);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
		assert_eq_with_exit(touch_effect, false);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_need_of_frame_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_need_of_frame()
 */
int utc_widget_service_get_need_of_frame_p(void)
{
	int ret;
	bool frame;

	ret = widget_service_get_need_of_frame(SAMPLE_WIDGET, WIDGET_SIZE_TYPE_2x2, &frame);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	normal_exit(0);
	return 0;
}

static int widget_list_cb_p(const char *pkgid, const char *widget_id, int is_prime, void *data)
{
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_widget_list_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_widget_list
 */
int utc_widget_service_get_widget_list_p(void)
{
	int ret;
	/**
	 * @note
	 * There is only one package SAMPLE_WIDGET
	 */
	ret = widget_service_get_widget_list(widget_list_cb_p, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	} else {
		assert_neq(ret, WIDGET_ERROR_NOT_EXIST);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_main_app_id_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_main_app_id
 */
int utc_widget_service_get_main_app_id_p(void)
{
	char *ret;
	int result;

	ret = widget_service_get_main_app_id(SAMPLE_WIDGET);


	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, NULL);
	}
	else {
		assert_neq(ret, NULL);
		result = strcmp(ret, SAMPLE_WIDGET);
		free(ret);
		assert_eq_with_exit(result, 0);
	}

	normal_exit(0);
	return 0;
}


static int utc_widget_service_get_widget_list_by_pkgid_p_cb(const char *widget_id, int is_primary, void *data)
{
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_widget_list_by_pkgid_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_widget_list_by_pkgid
 */
int utc_widget_service_get_widget_list_by_pkgid_p(void)
{
	int ret;
	ret = widget_service_get_widget_list_by_pkgid(SAMPLE_WIDGET, utc_widget_service_get_widget_list_by_pkgid_p_cb, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, 1);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_widget_id_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_widget_id
 */
int utc_widget_service_get_widget_id_p(void)
{
	char *ret;
	int result;

	ret = widget_service_get_widget_id(SAMPLE_WIDGET);

	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, NULL);
	}
	else {
		assert_neq(ret, NULL);

		result = strcmp(ret, SAMPLE_WIDGET);
		free(ret);

		assert_eq_with_exit(result, 0);
	}


	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_app_id_of_setup_app_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_app_id_of_setup_app
 */
int utc_widget_service_get_app_id_of_setup_app_p(void)
{
	char *ret;

	ret = widget_service_get_app_id_of_setup_app(SAMPLE_WIDGET);
	assert_eq_with_exit(ret, NULL);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_package_id_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_package_id
 */
int utc_widget_service_get_package_id_p(void)
{
	char *ret;
	int result;

	ret = widget_service_get_package_id(SAMPLE_WIDGET);

	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, NULL);
	}
	else {
		assert_neq(ret, NULL);

		result = strcmp(ret, SAMPLE_PKGNAME);
		free(ret);

		assert_eq_with_exit(result, 0);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_name_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_name
 */
int utc_widget_service_get_name_p(void)
{
	char *ret;

	ret = widget_service_get_name(SAMPLE_WIDGET, NULL);

	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, NULL);
	}
	else {
		assert_neq(ret, NULL);
		free(ret);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_preview_image_path_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_preview_image_path
 */
int utc_widget_service_get_preview_image_path_p(void)
{
	char *ret;
	int result;

	ret = widget_service_get_preview_image_path(SAMPLE_WIDGET, WIDGET_SIZE_TYPE_2x2);

	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, NULL);
	}
	else {
		assert_neq(ret, NULL);
		result = strcmp(ret, SAMPLE_PREVIEW);
		free(ret);
		assert_neq(result, 0);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_icon_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_icon
 */
int utc_widget_service_get_icon_p(void)
{
	char *ret;
	int result;

	ret = widget_service_get_icon(SAMPLE_WIDGET, NULL);

	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, NULL);
	}
	else {
		assert_neq(ret, NULL);
		result = strcmp(ret, "/opt/apps/"SAMPLE_PKGNAME"/shared/icon/"SAMPLE_WIDGET".png");
		free(ret);
		assert_neq(result, 0);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_nodisplay_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_nodisplay
 */
int utc_widget_service_get_nodisplay_p(void)
{
	int ret;

	if (s_info.appwidget_supported == true) {
		ret = widget_service_get_nodisplay(SAMPLE_WIDGET);
		assert_eq_with_exit(ret, 0);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_supported_sizes_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_supported_sizes
 */
int utc_widget_service_get_supported_sizes_p(void)
{
	int ret;
	int cnt = 20;
	int *w;
	int *h;
	int sw;
	int sh;

	ret = widget_service_get_supported_sizes(SAMPLE_WIDGET, &cnt, &w, &h);

	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);

		assert_eq_with_exit(cnt, 1);

		ret = widget_service_get_size(WIDGET_SIZE_TYPE_2x2, &sw, &sh);
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);

		assert_eq_with_exit(w[0], sw);
		assert_eq_with_exit(h[0], sh);

		free(w);
		free(h);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_supported_size_types_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_get_supported_size_types
 */
int utc_widget_service_get_supported_size_types_p(void)
{
	int ret;
	int cnt = 20;
	int *size_types = NULL;

	ret = widget_service_get_supported_size_types(SAMPLE_WIDGET, &cnt, &size_types);

	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
		assert_eq_with_exit(cnt, 1);
		assert_eq_with_exit(size_types[0], WIDGET_SIZE_TYPE_2x2);

		free(size_types);
	}



	normal_exit(0);
	return 0;
}

static int widget_lifecycle_event_cb_p(const char *widget_id, widget_lifecycle_event_e lifecycle_event, const char *widget_instance_id, void *data)
{
	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_set_lifecycle_event_cb_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_set_lifecycle_event_cb
 */
int utc_widget_service_set_lifecycle_event_cb_p(void)
{
	int ret;

	ret = widget_service_set_lifecycle_event_cb(NULL, widget_lifecycle_event_cb_p, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	ret = widget_service_unset_lifecycle_event_cb(NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_unset_lifecycle_event_cb_p
 * @since_tizen		2.3.1
 * @description		Positive test case of widget_service_unset_lifecycle_event_cb
 */
int utc_widget_service_unset_lifecycle_event_cb_p(void)
{
	int ret;

	ret = widget_service_set_lifecycle_event_cb(NULL, widget_lifecycle_event_cb_p, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	ret = widget_service_unset_lifecycle_event_cb(NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	}
	else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	normal_exit(0);
	return 0;
}

void _widget_disable_event_cb(const char *widget_id, bool is_disabled, void *user_data)
{
}

/**
 * @testcase		utc_widget_service_set_disable_event_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of widget_service_set_disable_event_cb()
 */
int utc_widget_service_set_disable_event_cb_p(void)
{
	int ret;

	ret = widget_service_set_disable_event_cb(_widget_disable_event_cb, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	ret = widget_service_unset_disable_event_cb();
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_set_disable_event_cb_n
 * @since_tizen		5.5
 * @description		Nagative test case of widget_service_set_disable_event_cb()
 */
int utc_widget_service_set_disable_event_cb_n(void)
{
	int ret;

	ret = widget_service_set_disable_event_cb(NULL , NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_unset_disable_event_cb_p
 * @since_tizen		5.5
 * @description		Positive test case of widget_service_unset_disable_event_cb()
 */
int utc_widget_service_unset_disable_event_cb_p(void)
{
	int ret;

	ret = widget_service_set_disable_event_cb(_widget_disable_event_cb, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	ret = widget_service_unset_disable_event_cb();
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_unset_disable_event_cb_n
 * @since_tizen		5.5
 * @description		Negative test case of widget_service_unset_disable_event_cb()
 */
int utc_widget_service_unset_disable_event_cb_n(void)
{
	int ret;

	ret = widget_service_unset_disable_event_cb();
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq_with_exit(ret, WIDGET_ERROR_IO_ERROR);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_widget_disabled_p
 * @since_tizen		5.5
 * @description		Positive test case of widget_service_get_widget_disabled()
 */
int utc_widget_service_get_widget_disabled_p(void)
{
	int ret;
	bool is_disabled = true;

	ret = widget_service_get_widget_disabled(SAMPLE_PKGNAME, &is_disabled);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq_with_exit(ret, WIDGET_ERROR_NONE);
	}

	assert_eq_with_exit(is_disabled, false);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_get_widget_disabled_n
 * @since_tizen		5.5
 * @description		Negative test case of utc_widget_service_get_widget_disabled()
 */
int utc_widget_service_get_widget_disabled_n(void)
{
	int ret;

	ret = widget_service_get_widget_disabled(NULL, NULL);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_set_widget_disabled_n
 * @since_tizen		5.5
 * @description		Negative test case of widget_service_set_widget_disabled()
 */
int utc_widget_service_set_widget_disabled_n(void)
{
	int ret;
	ret = widget_service_set_widget_disabled(NULL, true);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq_with_exit(ret, WIDGET_ERROR_INVALID_PARAMETER);
	}

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_widget_service_set_widget_disabled_n2
 * @since_tizen		5.5
 * @description		Negative test case of widget_service_set_widget_disabled()
 */
int utc_widget_service_set_widget_disabled_n2(void)
{
	int ret;
	ret = widget_service_set_widget_disabled(SAMPLE_PKGNAME, true);
	if (s_info.appwidget_supported == false) {
		assert_eq_with_exit(ret, WIDGET_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq_with_exit(ret, WIDGET_ERROR_PERMISSION_DENIED);
	}

	normal_exit(0);
	return 0;
}


/* End of a file */
