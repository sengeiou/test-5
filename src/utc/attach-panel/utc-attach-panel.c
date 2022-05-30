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
#include <attach_panel.h>
#include <bundle.h>
#include <glib.h>
#include <system_info.h>

#define ATTACH_PANEL_INVALID_CATEGORY -1
#define ATTACH_PANEL_FEATURE "http://tizen.org/feature/attach_panel"

static struct info {
	Evas_Object *win;
	Evas_Object *conformant;
	GMainLoop *mainloop;
    int is_asserted;
} s_info = {
        .is_asserted = 0,
        .win = NULL,
        .conformant = NULL,
        .mainloop = NULL,
};

static int assert_eq_for_callback(int var, int value)
{
    assert_eq(var, value);
    return 0;
}

static int assert_neq_for_callback(void *var, void *value)
{
    assert_neq(var, value);
    return 0;
}

//& set: AttachPanel

/**
 * @function	utc_attach_panel_startup
 * @description	Called before each test
 * @parameter	NA
 * @return		NA
 */
void utc_attach_panel_startup(void)
{
	s_info.win = elm_win_add(NULL, "Attach Panel Sample", ELM_WIN_BASIC);
	if (!s_info.win) {
		printf("[attach panel] fail to create window");
	}
	evas_object_show(s_info.win);

	s_info.conformant = elm_conformant_add(s_info.win);
	if (!s_info.conformant) {
		printf("[attach panel] fail to create window");
	}

	evas_object_size_hint_weight_set(s_info.conformant,  EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(s_info.win, s_info.conformant);
	evas_object_show(s_info.conformant);
	s_info.is_asserted = 0;
}

/**
 * @function	utc_attach_panel_cleanup
 * @description	Called after each test
 * @parameter	NA
 * @return		NA
 */
void utc_attach_panel_cleanup(void)
{
	evas_object_del(s_info.conformant);
	s_info.conformant = NULL;
	evas_object_del(s_info.win);
	s_info.win = NULL;
}

/**
 * @testcase       utc_attach_panel_create_p
 * @since_tizen 2.4
 * @description   positive test case of attach_panel_create
 */
int utc_attach_panel_create_p(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);
	assert_neq(attach_panel, NULL);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_create_p2
 * @since_tizen 5.0
 * @description   positive test case of attach_panel_create
 */
int utc_attach_panel_create_p2(void)
{
	attach_panel_h attach_panel;
	int ret;
	bool is_supported = false;

	if (!system_info_get_platform_bool(ATTACH_PANEL_FEATURE, &is_supported)) {
		ret = attach_panel_create(s_info.conformant, &attach_panel);
		if (is_supported) {
			assert_eq(ret, ATTACH_PANEL_ERROR_NONE);
			assert_neq(attach_panel, NULL);

			ret = attach_panel_destroy(attach_panel);
			assert_eq(ret, ATTACH_PANEL_ERROR_NONE);
		}else{
			assert_eq(ret, ATTACH_PANEL_ERROR_NOT_SUPPORTED);
			assert_eq(attach_panel, NULL);
		}
	}

    return 0;
}

/**
 * @testcase       utc_attach_panel_create_n
 * @since_tizen 2.4
 * @description   Negative test case of attach_panel_create
 */
int utc_attach_panel_create_n(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(NULL, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_create(s_info.conformant, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase       utc_attach_panel_destroy_p
 * @since_tizen 2.4
 * @description   positive test case of attach_panel_destroy
 */
int utc_attach_panel_destroy_p(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_destroy_n
 * @since_tizen 2.4
 * @description   Negative test case of attach_panel_destroy
 */
int utc_attach_panel_destroy_n(void)
{
	int ret;

	ret = attach_panel_destroy(NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase       utc_attach_panel_add_content_category_p
 * @since_tizen 2.4
 * @description   positive test case of attach_panel_add_content_category
 */
int utc_attach_panel_add_content_category_p(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);
	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_TAKE_PICTURE, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);
	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_CAMERA, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_add_content_category_n
 * @since_tizen 2.4
 * @description   Negative test case of attach_panel_add_content_category
 */
int utc_attach_panel_add_content_category_n(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(NULL, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_INVALID_CATEGORY, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_remove_content_category_p
 * @since_tizen 2.4
 * @description   positive test case of attach_panel_remove_content_category
 */
int utc_attach_panel_remove_content_category_p(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_remove_content_category_n
 * @since_tizen 2.4
 * @description   Negative test case of attach_panel_remove_content_category
 */
int utc_attach_panel_remove_content_category_n(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_remove_content_category(NULL, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_INVALID_CATEGORY);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_set_extra_data_p
 * @since_tizen 2.4
 * @description   positive test case of attach_panel_set_extra_data
 */
int utc_attach_panel_set_extra_data_p(void)
{
	attach_panel_h attach_panel;
	bundle *extra_data;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	extra_data = bundle_create();
	assert_neq(extra_data, NULL);
	bundle_add_str(extra_data, "http://tizen.org/appcontrol/data/total_count", "3");

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, extra_data);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);
	bundle_free(extra_data);

	ret = attach_panel_show(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	extra_data = bundle_create();
	assert_neq(extra_data, NULL);
	bundle_add_str(extra_data, "http://tizen.org/appcontrol/data/total_size", "10240000");

	ret = attach_panel_set_extra_data(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, extra_data);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);
	bundle_free(extra_data);

    return 0;
}

/**
 * @testcase       utc_attach_panel_set_extra_data_n
 * @since_tizen 2.4
 * @description   Negative test case of attach_panel_set_extra_data
 */
int utc_attach_panel_set_extra_data_n(void)
{
	attach_panel_h attach_panel;
	bundle *extra_data;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	extra_data = bundle_create();
	assert_neq(extra_data, NULL);
	bundle_add_str(extra_data, "http://tizen.org/appcontrol/data/total_count", "3");

	ret = attach_panel_set_extra_data(NULL, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, extra_data);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_set_extra_data(attach_panel, ATTACH_PANEL_INVALID_CATEGORY, extra_data);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_set_extra_data(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);
	bundle_free(extra_data);

    return 0;

}

/**
 * @testcase       utc_attach_panel_show_p
 * @since_tizen 2.4
 * @description   positive test case of attach_panel_show
 */
int utc_attach_panel_show_p(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_show(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_show_n
 * @since_tizen 2.4
 * @description   Negative test case of attach_panel_show
 */
int utc_attach_panel_show_n(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_show(NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_hide_p
 * @since_tizen 2.4
 * @description   positive test case of attach_panel_hide
 */
int utc_attach_panel_hide_p(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_hide(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_hide_n
 * @since_tizen 2.4
 * @description   Negative test case of attach_panel_hide
 */
int utc_attach_panel_hide_n(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_hide(NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_get_visibility_p
 * @since_tizen 2.4
 * @description   positive test case of attach_panel_get_visibility
 */
int utc_attach_panel_get_visibility_p(void)
{
	attach_panel_h attach_panel;
	int ret;
	bool visible;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_show(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_get_visibility(attach_panel, &visible);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);
	assert_eq(visible, true);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_get_visibility_n
 * @since_tizen 2.4
 * @description   Negative test case of attach_panel_get_visibility
 */
int utc_attach_panel_get_visibility_n(void)
{
	attach_panel_h attach_panel;
	int ret;
	bool visible;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_show(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_get_visibility(NULL, &visible);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_get_visibility(attach_panel, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

void _result_cb(attach_panel_h attach_panel, attach_panel_content_category_e content_category, app_control_h result, app_control_result_e result_code, void *user_data)
{
	s_info.is_asserted = assert_neq_for_callback((void *)attach_panel, NULL);
	if (s_info.is_asserted == 1)
		return;

	s_info.is_asserted = assert_eq_for_callback(content_category, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	if (s_info.is_asserted == 1)
		return;

	s_info.is_asserted = assert_neq_for_callback((void *)result, NULL);
	if (s_info.is_asserted == 1)
		return;

	s_info.is_asserted = assert_eq_for_callback(result_code, APP_CONTROL_RESULT_SUCCEEDED);
	if (s_info.is_asserted == 1)
		return;
}

/**
 * @testcase       utc_attach_panel_set_result_cb_p
 * @since_tizen 2.4
 * @description   Positive test case of attach_panel_set_result_cb
 */
int utc_attach_panel_set_result_cb_p(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_set_result_cb(attach_panel, _result_cb, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_set_result_cb_n
 * @since_tizen 2.4
 * @description   Negative test case of attach_panel_set_result_cb
 */
int utc_attach_panel_set_result_cb_n(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_set_result_cb(NULL, _result_cb, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_set_result_cb(attach_panel, NULL, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_unset_result_cb_p
 * @since_tizen 2.4
 * @description   positive test case of attach_panel_unset_result_cb
 */
int utc_attach_panel_unset_result_cb_p(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_set_result_cb(attach_panel, _result_cb, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_unset_result_cb(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_unset_result_cb_n
 * @since_tizen 2.4
 * @description   Negative test case of attach_panel_unset_result_cb
 */
int utc_attach_panel_unset_result_cb_n(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_set_result_cb(attach_panel, _result_cb, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_unset_result_cb(NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

void _event_cb(attach_panel_h attach_panel, attach_panel_event_e event, void *event_info, void *user_data)
{
	s_info.is_asserted = assert_neq_for_callback((void *)attach_panel, NULL);
	if (s_info.is_asserted == 1)
		goto END;

	if (event == ATTACH_PANEL_EVENT_SHOW_START || event == ATTACH_PANEL_EVENT_SHOW_FINISH) {
		s_info.is_asserted = 0;
	} else {
		s_info.is_asserted = 1;
	}

END:
	ecore_main_loop_quit();
}

/**
 * @testcase       utc_attach_panel_set_event_cb_p
 * @since_tizen 2.4
 * @description   Positive test case of attach_panel_set_event_cb
 */
int utc_attach_panel_set_event_cb_p(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_set_event_cb(attach_panel, _event_cb, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_show(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_set_event_cb_n
 * @since_tizen 2.4
 * @description   Negative test case of attach_panel_set_event_cb
 */
int utc_attach_panel_set_event_cb_n(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_set_event_cb(NULL, _event_cb, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_set_event_cb(attach_panel, NULL, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_unset_event_cb_p
 * @since_tizen 2.4
 * @description   positive test case of attach_panel_unset_event_cb
 */
int utc_attach_panel_unset_event_cb_p(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_set_event_cb(attach_panel, _event_cb, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_unset_event_cb(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_unset_event_cb_n
 * @since_tizen 2.4
 * @description   Negative test case of attach_panel_unset_event_cb
 */
int utc_attach_panel_unset_event_cb_n(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_set_event_cb(attach_panel, _event_cb, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_unset_event_cb(NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	return 0;
}


/**
 * @testcase       utc_attach_panel_get_state_p
 * @since_tizen 3.0
 * @description   Positive test case of attach_panel_get_state
 */
int utc_attach_panel_get_state_p(void)
{
	attach_panel_h attach_panel;
	attach_panel_state_e state;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_get_state(attach_panel, &state);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	return 0;
}

/**
 * @testcase       utc_attach_panel_get_state_n
 * @since_tizen 3.0
 * @description   Negative test case of attach_panel_get_state
 */
int utc_attach_panel_get_state_n(void)
{
	attach_panel_state_e state;
	int ret;

	ret = attach_panel_get_state(NULL, &state);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	return 0;
}
/**
 * @testcase       utc_attach_panel_show_without_animation_p
 * @since_tizen 4.0
 * @description   positive test case of attach_panel_show_without_animation
 */
int utc_attach_panel_show_without_animation_p(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_IMAGE, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_show_without_animation(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_IMAGE);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_show_without_animation_n
 * @since_tizen 4.0
 * @description   Negative test case of attach_panel_show_without_animation
 */
int utc_attach_panel_show_without_animation_n(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_show_without_animation(NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_hide_without_animation_p
 * @since_tizen 4.0
 * @description   positive test case of attach_panel_hide_without_animation
 */
int utc_attach_panel_hide_without_animation_p(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_hide_without_animation(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}

/**
 * @testcase       utc_attach_panel_hide_without_animation_n
 * @since_tizen 4.0
 * @description   Negative test case of attach_panel_hide_without_animation
 */
int utc_attach_panel_hide_without_animation_n(void)
{
	attach_panel_h attach_panel;
	int ret;

	ret = attach_panel_create(s_info.conformant, &attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES, NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_hide_without_animation(NULL);
	assert_eq(ret, ATTACH_PANEL_ERROR_INVALID_PARAMETER);

	ret = attach_panel_remove_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_MYFILES);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

	ret = attach_panel_destroy(attach_panel);
	assert_eq(ret, ATTACH_PANEL_ERROR_NONE);

    return 0;
}
