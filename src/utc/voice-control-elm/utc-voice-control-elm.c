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
#include <voice_control_elm.h>
#include <Evas.h>
#include <Elementary.h>


//& set: VoiceControl-elm

static int g_vc_elm_init = false;
static bool g_vc_elm_supported = false;

/**
 * @function		utc_voice_control_elm_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_voice_control_elm_startup(void)
{
	int ret = VC_ELM_ERROR_NONE;
	int i;

	bool mic_supported = false;
	bool vc_supported = false;
	g_vc_elm_supported = false;
	if (0 == system_info_get_platform_bool("http://tizen.org/feature/speech.control", &vc_supported)) {
		if (0 == system_info_get_platform_bool("http://tizen.org/feature/microphone", &mic_supported)) {
			if (true == vc_supported && true == mic_supported) {
				g_vc_elm_supported = true;
			}
		}
	}

	elm_init(0,NULL);
	ret = vc_elm_initialize();
	for (i = 0; i < 20; i++)
		ecore_main_loop_iterate();

	if (VC_ELM_ERROR_NONE == ret) {
		g_vc_elm_init = true;
	} else {
		g_vc_elm_init = false;
	}
}

/**
 * @function		utc_voice_control_elm_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_voice_control_elm_cleanup(void)
{
	int i;
	int ret = VC_ELM_ERROR_NONE;
	for (i = 0; i < 30; i++)
		ecore_main_loop_iterate();

	ret = vc_elm_deinitialize();
	assert_eq(ret, VC_ELM_ERROR_NONE);
	elm_shutdown();

	g_vc_elm_init = false;
}

static void _vc_elm_current_language_changed_cb(const char *previous, const char *current, void *user_data)
{
	(void)previous;
	(void)current;
	(void)user_data;
}

static bool _vc_elm_supported_language_cb(const char *language, void *user_data)
{
	(void)language;
	(void)user_data;
	return true;
}

static bool _vc_elm_widget_cb(const char *widget, void *user_data)
{
	(void)widget;
	(void)user_data;
	return false;
}

static bool _vc_elm_action_cb(const char *action, void *user_data)
{
	(void)action;
	(void)user_data;
	return false;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_initialize_p
 * @since_tizen		2.4
 * @description		test whether vc-elm is initialized properly.
 */
int utc_voice_control_elm_vc_elm_initialize_p(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_initialize(), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_deinitialize(), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_initialize_n
 * @since_tizen		2.4
 * @description		test whether function returns error when vc-elm is already initialized.
 */
int utc_voice_control_elm_vc_elm_initialize_n(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_initialize(), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(vc_elm_initialize(), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_deinitialize_p
 * @since_tizen		2.4
 * @description		test whether vc-elm is deinitialized properly.
 */
int utc_voice_control_elm_vc_elm_deinitialize_p(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_deinitialize(), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_deinitialize(), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_deinitialize_n
 * @since_tizen		2.4
 * @description		test whether function returns error when vc-elm is already deinitialized.
 */
int utc_voice_control_elm_vc_elm_deinitialize_n(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(vc_elm_deinitialize(), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(vc_elm_deinitialize(), VC_ELM_ERROR_NONE);
		assert_neq(vc_elm_deinitialize(), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_current_language_p
 * @since_tizen		2.4
 * @description		test whether it is to get current language properly.
 */
int utc_voice_control_elm_vc_elm_get_current_language_p(void)
{
	char *current_language = NULL;

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_current_language(&current_language), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_get_current_language(&current_language), VC_ELM_ERROR_NONE);
		assert_neq(current_language, NULL);

		free(current_language);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_current_language_n
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL parameter.
 */
int utc_voice_control_elm_vc_elm_get_current_language_n(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_current_language(NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_get_current_language(NULL), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_p1
 * @since_tizen		2.4
 * @description		test whether it is to create handle for button object properly.
 */
int utc_voice_control_elm_vc_elm_create_object_p1(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_p2
 * @since_tizen		2.4
 * @description		test whether it is to create handle for checkbox object properly.
 */
int utc_voice_control_elm_vc_elm_create_object_p2(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_check_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NOT_SUPPORTED);

	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_p3
 * @since_tizen		2.4
 * @description		test whether it is to create handle for radio button object properly.
 */
int utc_voice_control_elm_vc_elm_create_object_p3(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_radio_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_p4
 * @since_tizen		2.4
 * @description		test whether it is to create handle for slider object properly.
 */
int utc_voice_control_elm_vc_elm_create_object_p4(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_slider_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_p5
 * @since_tizen		2.4
 * @description		test whether it is to create handle for spinner object properly.
 */
int utc_voice_control_elm_vc_elm_create_object_p5(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_spinner_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_p6
 * @since_tizen		2.4
 * @description		test whether it is to create handle for entry object properly.
 */
int utc_voice_control_elm_vc_elm_create_object_p6(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_entry_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_p7
 * @since_tizen		2.4
 * @description		test whether it is to create handle for scroller object properly.
 */
int utc_voice_control_elm_vc_elm_create_object_p7(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_scroller_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_p8
 * @since_tizen		2.4
 * @description		test whether it is to create handle for label object properly.
 */
int utc_voice_control_elm_vc_elm_create_object_p8(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_label_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_p9
 * @since_tizen		2.4
 * @description		test whether it is to create handle for genlist object properly.
 */
int utc_voice_control_elm_vc_elm_create_object_p9(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_genlist_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_p10
 * @since_tizen		2.4
 * @description		test whether it is to create handle for gengrid object properly.
 */
int utc_voice_control_elm_vc_elm_create_object_p10(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_gengrid_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_n1
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as handler parameter.
 */
int utc_voice_control_elm_vc_elm_create_object_n1(void)
{
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(object, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_create_object(object, NULL), VC_ELM_ERROR_INVALID_PARAMETER);
	}		
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_n2
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as object parameter.
 */
int utc_voice_control_elm_vc_elm_create_object_n2(void)
{
	vc_elm_h handler = NULL;

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(NULL, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_create_object(NULL, &handler), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_object_n3
 * @since_tizen		2.4
 * @description		test whether function returns error when vc-elm is not initialized.
 */
int utc_voice_control_elm_vc_elm_create_object_n3(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_deinitialize(), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_INVALID_STATE);
	}
	return 0;
}



/**
 * @testcase		utc_voice_control_elm_vc_elm_create_item_p
 * @since_tizen		2.4
 * @description		test whether it is to create handle for item object properly.
 */
int utc_voice_control_elm_vc_elm_create_item_p(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

	Evas_Object* glist = elm_list_add(win);
	Elm_Object_Item *it = elm_list_item_append(glist, "test", NULL, NULL, NULL, NULL);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_item(it, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(it, NULL);

		assert_eq(vc_elm_create_item(it, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_item_n1
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as handler parameter.
 */
int utc_voice_control_elm_vc_elm_create_item_n1(void)
{
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

	Evas_Object* glist = elm_list_add(win);
	Elm_Object_Item *it = elm_list_item_append(glist, "test", NULL, NULL, NULL, NULL);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_neq(it, NULL);
		assert_eq(vc_elm_create_item(it, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(it, NULL);
		assert_eq(vc_elm_create_item(it, NULL), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_item_n2
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as item object parameter.
 */
int utc_voice_control_elm_vc_elm_create_item_n2(void)
{
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

	vc_elm_h handler = NULL;

	Evas_Object* glist = elm_list_add(win);
	Elm_Object_Item *it = elm_list_item_append(glist, "test", NULL, NULL, NULL, NULL);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_neq(it, NULL);
		assert_eq(vc_elm_create_item(NULL, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(it, NULL);
		assert_eq(vc_elm_create_item(NULL, &handler), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_create_item_n3
 * @since_tizen		2.4
 * @description		test whether function returns error when vc-elm is not initialized.
 */
int utc_voice_control_elm_vc_elm_create_item_n3(void)
{
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

	vc_elm_h handler = NULL;

	Evas_Object* glist = elm_list_add(win);
	Elm_Object_Item *it = elm_list_item_append(glist, "test", NULL, NULL, NULL, NULL);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_create_item(it, &handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_deinitialize(), VC_ELM_ERROR_NONE);

		assert_neq(it, NULL);
		assert_eq(vc_elm_create_item(it, &handler), VC_ELM_ERROR_INVALID_STATE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_destroy_p
 * @since_tizen		2.4
 * @description		test whether it is to destroy handle for object properly.
 */
int utc_voice_control_elm_vc_elm_destroy_p(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_destroy_n1
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as handler parameter.
 */
int utc_voice_control_elm_vc_elm_destroy_n1(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);

		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(NULL), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_destroy_n2
 * @since_tizen		2.4
 * @description		test whether function returns error when try to destroy handle that is not created.
 */
int utc_voice_control_elm_vc_elm_destroy_n2(void)
{
	vc_elm_h handler = NULL;

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_destroy_n3
 * @since_tizen		2.4
 * @description		test whether function returns error when vc-elm is not initialized.
 */
int utc_voice_control_elm_vc_elm_destroy_n3(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_command_p1
 * @since_tizen		2.4
 * @description		test whether it is to set command on object properly.
 */
int utc_voice_control_elm_vc_elm_set_command_p1(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_command_p2
 * @since_tizen		2.4
 * @description		test whether it is to set command on item object properly.
 */
int utc_voice_control_elm_vc_elm_set_command_p2(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

        Evas_Object* glist = elm_list_add(win);
	Elm_Object_Item *it = elm_list_item_append(glist, "test", NULL, NULL, NULL, NULL);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(it, NULL);

		assert_eq(vc_elm_create_item(it, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_command_n
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as handler parameter.
 */
int utc_voice_control_elm_vc_elm_set_command_n(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_command(NULL, "TEST"), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_set_command(NULL, "TEST"), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_unset_command_p1
 * @since_tizen		2.4
 * @description		test whether it is to unset command on object properly.
 */
int utc_voice_control_elm_vc_elm_unset_command_p1(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_unset_command(handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_unset_command(handler), VC_ELM_ERROR_NONE);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_unset_command_p2
 * @since_tizen		2.4
 * @description		test whether it is to unset command on item object properly.
 */
int utc_voice_control_elm_vc_elm_unset_command_p2(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

	Evas_Object* glist = elm_list_add(win);
	Elm_Object_Item *it = elm_list_item_append(glist, "test", NULL, NULL, NULL, NULL);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_unset_command(handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(it, NULL);

		assert_eq(vc_elm_create_item(it, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_unset_command(handler), VC_ELM_ERROR_NONE);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_unset_command_n
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as handler parameter.
 */
int utc_voice_control_elm_vc_elm_unset_command_n(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_unset_command(NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_unset_command(NULL), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_command_hint_p1
 * @since_tizen		2.4
 * @description		test whether it is to set command hint on object properly.
 */
int utc_voice_control_elm_vc_elm_set_command_hint_p1(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NONE);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_command_hint_p2
 * @since_tizen		2.4
 * @description		test whether it is to set command hint on item object properly.
 */
int utc_voice_control_elm_vc_elm_set_command_hint_p2(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

	Evas_Object* glist = elm_list_add(win);
	Elm_Object_Item *it = elm_list_item_append(glist, "test", NULL, NULL, NULL, NULL);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(it, NULL);

		assert_eq(vc_elm_create_item(it, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);
		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_command_hint_n
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as handler parameter.
 */
int utc_voice_control_elm_vc_elm_set_command_hint_n(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_command_hint(NULL, "TEST"), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_set_command_hint(NULL, "TEST"), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_unset_command_hint_p1
 * @since_tizen		2.4
 * @description		test whether it is to unset command hint on object properly.
 */
int utc_voice_control_elm_vc_elm_unset_command_hint_p1(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_unset_command_hint(handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_unset_command_hint(handler), VC_ELM_ERROR_NONE);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_unset_command_hint_p2
 * @since_tizen		2.4
 * @description		test whether it is to unset command hint on item object properly.
 */
int utc_voice_control_elm_vc_elm_unset_command_hint_p2(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

	Evas_Object* glist = elm_list_add(win);
	Elm_Object_Item *it = elm_list_item_append(glist, "test", NULL, NULL, NULL, NULL);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_unset_command_hint(handler), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(it, NULL);

		assert_eq(vc_elm_create_item(it, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_unset_command_hint(handler), VC_ELM_ERROR_NONE);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_unset_command_hint_n
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as handler parameter.
 */
int utc_voice_control_elm_vc_elm_unset_command_hint_n(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_unset_command_hint(NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_unset_command_hint(NULL), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_command_hint_direction_p1
 * @since_tizen		2.4
 * @description		test whether it is to set command hint direction on object properly.
 */
int utc_voice_control_elm_vc_elm_set_command_hint_direction_p1(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_command_hint_direction(handler, VC_ELM_DIRECTION_TOP), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint_direction(handler, VC_ELM_DIRECTION_TOP), VC_ELM_ERROR_NONE);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_command_hint_direction_p2
 * @since_tizen		2.4
 * @description		test whether it is to set command hint direction on item object properly.
 */
int utc_voice_control_elm_vc_elm_set_command_hint_direction_p2(void)
{

	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

	Evas_Object* glist = elm_list_add(win);
	Elm_Object_Item *it = elm_list_item_append(glist, "test", NULL, NULL, NULL, NULL);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_command_hint_direction(handler, VC_ELM_DIRECTION_TOP), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(it, NULL);

		assert_eq(vc_elm_create_item(it, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint_direction(handler, VC_ELM_DIRECTION_TOP), VC_ELM_ERROR_NONE);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_command_hint_direction_n
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as handler parameter.
 */
int utc_voice_control_elm_vc_elm_set_command_hint_direction_n(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_command_hint_direction(NULL, VC_ELM_DIRECTION_TOP), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_set_command_hint_direction(NULL, VC_ELM_DIRECTION_TOP), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_command_hint_direction_p1
 * @since_tizen		2.4
 * @description		test whether it is to get command hint direction on object properly.
 */
int utc_voice_control_elm_vc_elm_get_command_hint_direction_p1(void)
{
	vc_elm_h handler = NULL;
	vc_elm_direction_e direction;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_command_hint_direction(handler, &direction), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint_direction(handler, VC_ELM_DIRECTION_TOP), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_get_command_hint_direction(handler, &direction), VC_ELM_ERROR_NONE);
		assert_eq(direction, VC_ELM_DIRECTION_TOP);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_command_hint_direction_p2
 * @since_tizen		2.4
 * @description		test whether it is to get command hint direction on item object properly.
 */
int utc_voice_control_elm_vc_elm_get_command_hint_direction_p2(void)
{
	vc_elm_h handler = NULL;
	vc_elm_direction_e direction;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

	Evas_Object* glist = elm_list_add(win);
	Elm_Object_Item *it = elm_list_item_append(glist, "test", NULL, NULL, NULL, NULL);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_command_hint_direction(handler, &direction), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(it, NULL);

		assert_eq(vc_elm_create_item(it, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint_direction(handler, VC_ELM_DIRECTION_TOP), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_get_command_hint_direction(handler, &direction), VC_ELM_ERROR_NONE);
		assert_eq(direction, VC_ELM_DIRECTION_TOP);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_command_hint_direction_n
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as handler parameter.
 */
int utc_voice_control_elm_vc_elm_get_command_hint_direction_n(void)
{
	vc_elm_direction_e direction;
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_command_hint_direction(NULL, &direction), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_get_command_hint_direction(NULL, &direction), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_command_hint_offset_p1
 * @since_tizen		2.4
 * @description		test whether it is to set command hint offset on object properly.
 */
int utc_voice_control_elm_vc_elm_set_command_hint_offset_p1(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_command_hint_offset(handler, 100, 100), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint_offset(handler, 100, 100), VC_ELM_ERROR_NONE);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_command_hint_offset_p2
 * @since_tizen		2.4
 * @description		test whether it is to set command hint offset on item object properly.
 */
int utc_voice_control_elm_vc_elm_set_command_hint_offset_p2(void)
{

	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

	Evas_Object* glist = elm_list_add(win);
	Elm_Object_Item *it = elm_list_item_append(glist, "test", NULL, NULL, NULL, NULL);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_command_hint_offset(handler, 100, 100), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(it, NULL);

		assert_eq(vc_elm_create_item(it, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint_offset(handler, 100, 100), VC_ELM_ERROR_NONE);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_command_hint_offset_n
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as handler parameter.
 */
int utc_voice_control_elm_vc_elm_set_command_hint_offset_n(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_command_hint_offset(NULL, 100, 100), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_set_command_hint_offset(NULL, 100, 100), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_command_hint_offset_p1
 * @since_tizen		2.4
 * @description		test whether it is to get command hint offset on object properly.
 */
int utc_voice_control_elm_vc_elm_get_command_hint_offset_p1(void)
{
	vc_elm_h handler = NULL;
	int x, y;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_command_hint_offset(handler, &x, &y), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint_offset(handler, 100, 100), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_get_command_hint_offset(handler, &x, &y), VC_ELM_ERROR_NONE);
		assert_eq(x, 100);
		assert_eq(y, 100);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_command_hint_offset_p2
 * @since_tizen		2.4
 * @description		test whether it is to get command hint offset on item object properly.
 */
int utc_voice_control_elm_vc_elm_get_command_hint_offset_p2(void)
{
	vc_elm_h handler = NULL;
	int x, y;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);

	Evas_Object* glist = elm_list_add(win);
	Elm_Object_Item *it = elm_list_item_append(glist, "test", NULL, NULL, NULL, NULL);

	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_command_hint_offset(handler, &x, &y), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(it, NULL);

		assert_eq(vc_elm_create_item(it, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(vc_elm_set_command(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint(handler, "TEST"), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_command_hint_offset(handler, 100, 100), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_get_command_hint_offset(handler, &x, &y), VC_ELM_ERROR_NONE);
		assert_eq(x, 100);
		assert_eq(y, 100);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_command_hint_offset_n1
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as handler parameter.
 */
int utc_voice_control_elm_vc_elm_get_command_hint_offset_n1(void)
{
	int x, y;
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_command_hint_offset(NULL, &x, &y), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_get_command_hint_offset(NULL, &x, &y), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_command_hint_offset_n2
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as position x and y.
 */
int utc_voice_control_elm_vc_elm_get_command_hint_offset_n2(void)
{
	vc_elm_h handler = NULL;
	Evas_Object* win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
	Evas_Object* object = elm_button_add(win);
	
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_command_hint_offset(handler, NULL, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(vc_elm_create_object(object, &handler), VC_ELM_ERROR_NONE);
		assert_neq(handler, NULL);

		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_get_command_hint_offset(handler, NULL, NULL), VC_ELM_ERROR_INVALID_PARAMETER);

		assert_eq(vc_elm_destroy(handler), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_current_language_changed_cb_p
 * @since_tizen		2.4
 * @description		test whether it is to set current_language_changed callback function properly.
 */
int utc_voice_control_elm_vc_elm_set_current_language_changed_cb_p(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_current_language_changed_cb(_vc_elm_current_language_changed_cb, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_set_current_language_changed_cb(_vc_elm_current_language_changed_cb, NULL), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_current_language_changed_cb_n1
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as callback pointer.
 */
int utc_voice_control_elm_vc_elm_set_current_language_changed_cb_n1(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_current_language_changed_cb(NULL, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(vc_elm_set_current_language_changed_cb(NULL, NULL), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_set_current_language_changed_cb_n2
 * @since_tizen		2.4
 * @description		test whether function returns error when vc-elm is not initialized.
 */
int utc_voice_control_elm_vc_elm_set_current_language_changed_cb_n2(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_set_current_language_changed_cb(NULL, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_deinitialize(), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_set_current_language_changed_cb(NULL, NULL), VC_ELM_ERROR_INVALID_STATE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_p
 * @since_tizen		2.4
 * @description		test whether it is to unset current_language_changed callback function properly.
 */
int utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_p(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_unset_current_language_changed_cb(), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_set_current_language_changed_cb(_vc_elm_current_language_changed_cb, NULL), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_unset_current_language_changed_cb(), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_n1
 * @since_tizen		2.4
 * @description		test whether function returns error when current_language_changed callback is not set.
 */
int utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_n1(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_unset_current_language_changed_cb(), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(vc_elm_unset_current_language_changed_cb(), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_n2
 * @since_tizen		2.4
 * @description		test whether function returns error when vc-elm is not initialized.
 */
int utc_voice_control_elm_vc_elm_unset_current_language_changed_cb_n2(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_unset_current_language_changed_cb(), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_deinitialize(), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_unset_current_language_changed_cb(), VC_ELM_ERROR_INVALID_STATE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_foreach_supported_languages_p
 * @since_tizen		2.4
 * @description		test whether it is to get each supported languages properly.
 */
int utc_voice_control_elm_vc_elm_foreach_supported_languages_p(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_foreach_supported_languages(_vc_elm_supported_language_cb, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_foreach_supported_languages(_vc_elm_supported_language_cb, NULL), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_foreach_supported_languages_n
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as callback function pointer.
 */
int utc_voice_control_elm_vc_elm_foreach_supported_languages_n(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_foreach_supported_languages(NULL, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(vc_elm_foreach_supported_languages(NULL, NULL), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_foreach_supported_widgets_p
 * @since_tizen		2.4
 * @description		test whether it is to get each supported widgets properly.
 */
int utc_voice_control_elm_vc_elm_foreach_supported_widgets_p(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_foreach_supported_widgets(_vc_elm_widget_cb, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_foreach_supported_widgets(_vc_elm_widget_cb, NULL), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_foreach_supported_widgets_n1
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as callback function pointer.
 */
int utc_voice_control_elm_vc_elm_foreach_supported_widgets_n1(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_foreach_supported_widgets(NULL, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_foreach_supported_widgets(NULL, NULL), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_foreach_supported_widgets_n2
 * @since_tizen		2.4
 * @description		test whether function returns error when vc-elm is not initialized.
 */
int utc_voice_control_elm_vc_elm_foreach_supported_widgets_n2(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_foreach_supported_widgets(_vc_elm_widget_cb, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_deinitialize(), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_foreach_supported_widgets(_vc_elm_widget_cb, NULL), VC_ELM_ERROR_INVALID_STATE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_foreach_supported_actions_p
 * @since_tizen		2.4
 * @description		test whether it is to get each supported actions properly.
 */
int utc_voice_control_elm_vc_elm_foreach_supported_actions_p(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_foreach_supported_actions("Elm_List", _vc_elm_action_cb, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_foreach_supported_actions("Elm_List", _vc_elm_action_cb, NULL), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_foreach_supported_actions_n1
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as callback function pointer.
 */
int utc_voice_control_elm_vc_elm_foreach_supported_actions_n1(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_foreach_supported_actions("Elm_List", NULL, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_foreach_supported_actions("Elm_List", NULL, NULL), VC_ELM_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_foreach_supported_actions_n2
 * @since_tizen		2.4
 * @description		test whether function returns error when vc-elm is not initialized.
 */
int utc_voice_control_elm_vc_elm_foreach_supported_actions_n2(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_foreach_supported_actions("Elm_List", _vc_elm_action_cb, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_deinitialize(), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_foreach_supported_actions("Elm_List", _vc_elm_action_cb, NULL), VC_ELM_ERROR_INVALID_STATE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_foreach_supported_actions_n3
 * @since_tizen		2.4
 * @description		test whether function returns error when widget is not supported.
 */
int utc_voice_control_elm_vc_elm_foreach_supported_actions_n3(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_foreach_supported_actions("Elm_None", _vc_elm_action_cb, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_foreach_supported_actions("Elm_None", _vc_elm_action_cb, NULL), VC_ELM_ERROR_OPERATION_FAILED);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_action_command_p
 * @since_tizen		2.4
 * @description		test whether it is to get action command properly.
 */
int utc_voice_control_elm_vc_elm_get_action_command_p(void)
{
	char *command;
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_action_command("scroll_up", &command), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_get_action_command("scroll_up", &command), VC_ELM_ERROR_NONE);
		assert_neq(command, NULL);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_action_command_n1
 * @since_tizen		2.4
 * @description		test whether function returns error with NULL as action and command parameter.
 */
int utc_voice_control_elm_vc_elm_get_action_command_n1(void)
{
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_action_command(NULL, NULL), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_neq(vc_elm_get_action_command(NULL, NULL), VC_ELM_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_action_command_n2
 * @since_tizen		2.4
 * @description		test whether function returns error when vc-elm is not initialized.
 */
int utc_voice_control_elm_vc_elm_get_action_command_n2(void)
{
	char *command;
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_action_command("scroll_up", &command), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_deinitialize(), VC_ELM_ERROR_NONE);
		assert_eq(vc_elm_get_action_command("scroll_up", &command), VC_ELM_ERROR_INVALID_STATE);
	}
	return 0;
}

/**
 * @testcase		utc_voice_control_elm_vc_elm_get_action_command_n3
 * @since_tizen		2.4
 * @description		test whether function returns error when action is not supported.
 */
int utc_voice_control_elm_vc_elm_get_action_command_n3(void)
{
	char *command;
	if (false == g_vc_elm_supported) {
		assert_eq(g_vc_elm_init, false);
		assert_eq(vc_elm_get_action_command("no_command", &command), VC_ELM_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(g_vc_elm_init, true);
		assert_eq(vc_elm_get_action_command("no_command", &command), VC_ELM_ERROR_OPERATION_FAILED);
	}
	return 0;
}
