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
#include <inputmethod.h>
#include <glib.h>
#include <Elementary.h>

typedef void (*void_f)(void);

ime_context_h _context = NULL;
Evas_Object *_win = NULL;
ime_device_info_h _dev_info = NULL;
Evas_Object *_opt_win = NULL;

//& set: CapiUi-inputmethod

static void _focus_in_cb(int context_id, void *user_data)
{
}
static void _focus_out_cb(int context_id, void *user_data)
{
}
static void _surrounding_text_updated_cb(int context_id, const char *text, int cursor_pos, void *user_data)
{
}
static void _input_context_reset_cb(void *user_data)
{
}
static void _cursor_position_updated_cb(int cursor_pos, void *user_data)
{
}
static void _language_requested_cb(void *user_data, char **lang_code)
{
}
static void _language_set_cb(Ecore_IMF_Input_Panel_Lang language, void *user_data)
{
}
static void _imdata_set_cb(void *data, unsigned int data_length, void *user_data)
{
}
static void _imdata_requested_cb(void *user_data, void **data, unsigned int *data_length)
{
}
static void _layout_set_cb(Ecore_IMF_Input_Panel_Layout layout, void *user_data)
{
}
static void _return_key_type_set_cb(Ecore_IMF_Input_Panel_Return_Key_Type type, void *user_data)
{
}
static void _return_key_state_set_cb(bool disabled, void *user_data)
{
}
static void _geometry_requested_cb(void *user_data, int *x, int *y, int *w, int *h)
{
}
static bool _process_key_event_cb(ime_key_code_e keycode, ime_key_mask_e keymask, ime_device_info_h dev_info, void *user_data)
{
    return true;
}
static void _display_language_changed_cb(const char *language, void *user_data)
{
}
static void _rotation_degree_changed_cb(int degree, void *user_data)
{
}
static void _accessibility_state_changed_cb(bool state, void *user_data)
{
}
static void _option_window_created_cb(Evas_Object *window, ime_option_window_type_e type, void *user_data)
{
    _opt_win = window;
}
static void _option_window_destroyed_cb(Evas_Object *window, void *user_data)
{
    _opt_win = NULL;
}
static void _prediction_hint_set_cb(const char *prediction_hint, void *user_data)
{
}
static void _mime_type_set_request_cb(const char *mime_type, void *user_data)
{
}
static void _prediction_hint_data_set_cb(const char *key, const char *value, void *user_data)
{
}
static bool _process_key_event_with_keycode_cb(unsigned int key_code, ime_key_code_e key_sym, ime_key_mask_e key_mask, ime_device_info_h dev_info, void *user_data)
{
    return true;
}

#ifndef TV
static void _input_hint_set_cb(Ecore_IMF_Input_Hints input_hint, void *user_data)
{
}
#endif

static int g_ret = -1;

static void _ime_exit()
{
    elm_exit();
}
static void _ime_send_key_event()
{
    g_ret = ime_send_key_event(IME_KEY_BackSpace, IME_KEY_MASK_PRESSED, true);
    elm_exit();
}
static void _ime_commit_string()
{
    g_ret = ime_commit_string("test");
    elm_exit();
}
static void _ime_show_preedit_string()
{
    g_ret = ime_show_preedit_string();
    elm_exit();
}
static void _ime_hide_preedit_string()
{
    g_ret = ime_hide_preedit_string();
    elm_exit();
}
static void _ime_update_preedit_string()
{
    g_ret = ime_update_preedit_string("test", NULL);
    elm_exit();
}
static void _ime_request_surrounding_text()
{
    g_ret = ime_request_surrounding_text(1, 1);
    elm_exit();
}
static void _ime_delete_surrounding_text()
{
    g_ret = ime_delete_surrounding_text(0, 1);
    elm_exit();
}
static void _ime_get_surrounding_text()
{
    char *text = NULL;
    int cursor_pos;
    g_ret = ime_get_surrounding_text(-1, -1, &text, &cursor_pos);
    if (text)
        free(text);
    elm_exit();
}
static void _ime_set_selection()
{
    g_ret = ime_set_selection(0, 0);
    elm_exit();
}
static void _ime_get_main_window()
{
    ime_get_main_window();
    g_ret = get_last_result();
    elm_exit();
}
static void _ime_set_size()
{
    g_ret = ime_set_size(100, 100, 100, 100);
    elm_exit();
}
static void _ime_create_option_window()
{
    g_ret = ime_create_option_window();
    elm_exit();
}
static void _ime_destroy_option_window()
{
    g_ret = ime_create_option_window();
    if(g_ret == IME_ERROR_NONE)
        g_ret = ime_destroy_option_window(_opt_win);
    elm_exit();
}
static void _ime_send_private_command()
{
    g_ret = ime_send_private_command("tizen::tc::test");
    elm_exit();
}
static void _ime_commit_content()
{
    g_ret = ime_commit_content("test1", "test2", "test3");
    elm_exit();
}
static void _ime_set_floating_mode()
{
    g_ret = ime_set_floating_mode(true);
    elm_exit();
}
static void _ime_set_floating_drag_start()
{
    g_ret = ime_set_floating_drag_start();
    elm_exit();
}
static void _ime_set_floating_drag_end()
{
    g_ret = ime_set_floating_drag_end();
    elm_exit();
}
static void _ime_get_selected_text()
{
    char *text = NULL;
    g_ret = ime_get_selected_text(&text);
    if (text)
        free(text);
    elm_exit();
}
static void _ime_request_hide()
{
    g_ret = ime_request_hide();
    elm_exit();
}
static void _ime_update_input_panel_event()
{
    g_ret = ime_update_input_panel_event(IME_EVENT_TYPE_LANGUAGE, 0);
    elm_exit();
}
static void _ime_set_candidate_visibility_state()
{
	g_ret = ime_set_candidate_visibility_state(true);
	elm_exit();
}

#ifndef TV
static void _ime_update_preedit_cursor()
{
	g_ret = ime_update_preedit_cursor(0);
	elm_exit();
}
#endif

static void _create_cb(void *user_data)
{
    ((void_f) user_data)();
}
static void _terminate_cb(void *user_data)
{
}
static void _show_cb(int ic, ime_context_h context, void *user_data)
{
}
static void _hide_cb(int ic, void *user_data)
{
}

static ime_callback_s basic_callback = {
    _create_cb,
    _terminate_cb,
    _show_cb,
    _hide_cb,
};


void ime_app_main(int argc, char **argv)
{
}

/**
 * @function		utc_capi_ui_inputmethod_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_ui_inputmethod_startup(void)
{
     _context = (ime_context_h)malloc(sizeof(ime_context_h));
     _dev_info = (ime_device_info_h)malloc(sizeof(ime_device_info_h));
     _win = elm_win_add(NULL, "test", ELM_WIN_BASIC);
}

/**
 * @function		utc_capi_ui_inputmethod_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_ui_inputmethod_cleanup(void)
{
    if(_context){
        free(_context);
        _context = NULL;
    }
    if(_dev_info){
        free(_dev_info);
        _dev_info = NULL;
    }
    if(_win){
        evas_object_del(_win);
        _win= NULL;
    }
}


//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_ime_run_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that runs the main loop of IME application.
 */
int utc_ime_run_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_exit);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_focus_in_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c focus_in event callback function.
 */
int utc_ime_event_set_focus_in_cb_p(void)
{
    int ret = ime_event_set_focus_in_cb(_focus_in_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_focus_out_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c focus_out event callback function.
 */
int utc_ime_event_set_focus_out_cb_p(void)
{
    int ret = ime_event_set_focus_out_cb(_focus_out_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_surrounding_text_updated_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c surrounding_text_updated event callback function.
 */
int utc_ime_event_set_surrounding_text_updated_cb_p(void)
{
    int ret = ime_event_set_surrounding_text_updated_cb(_surrounding_text_updated_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_input_context_reset_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets #c input_context_reset event callback function.
 */
int utc_ime_event_set_input_context_reset_cb_p(void)
{
    int ret = ime_event_set_input_context_reset_cb(_input_context_reset_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_cursor_position_updated_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c cursor_position_updated event callback function.
 */
int utc_ime_event_set_cursor_position_updated_cb_p(void)
{
    int ret = ime_event_set_cursor_position_updated_cb(_cursor_position_updated_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_language_requested_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c language_requested event callback function.
 */
int utc_ime_event_set_language_requested_cb_p(void)
{
    int ret = ime_event_set_language_requested_cb(_language_requested_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_language_set_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c language_set event callback function.
 */
int utc_ime_event_set_language_set_cb_p(void)
{
    int ret = ime_event_set_language_set_cb(_language_set_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_imdata_set_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c imdata_set event callback function.
 */
int utc_ime_event_set_imdata_set_cb_p(void)
{
    int ret = ime_event_set_imdata_set_cb(_imdata_set_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_imdata_requested_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c imdata_requested event callback function.
 */
int utc_ime_event_set_imdata_requested_cb_p(void)
{
    int ret = ime_event_set_imdata_requested_cb(_imdata_requested_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_layout_set_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c layout_set event callback function.
 */
int utc_ime_event_set_layout_set_cb_p(void)
{
    int ret = ime_event_set_layout_set_cb(_layout_set_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_return_key_type_set_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c return_key_type_set event callback function.
 */
int utc_ime_event_set_return_key_type_set_cb_p(void)
{
    int ret = ime_event_set_return_key_type_set_cb(_return_key_type_set_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_return_key_state_set_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c return_key_state_set event callback function.
 */
int utc_ime_event_set_return_key_state_set_cb_p(void)
{
    int ret = ime_event_set_return_key_state_set_cb(_return_key_state_set_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_geometry_requested_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c geometry_requested event callback function.
 */
int utc_ime_event_set_geometry_requested_cb_p(void)
{
    int ret = ime_event_set_geometry_requested_cb(_geometry_requested_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_process_key_event_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c process_key_event event callback function.
 */
int utc_ime_event_set_process_key_event_cb_p(void)
{
    int ret = ime_event_set_process_key_event_cb(_process_key_event_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_display_language_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c display_language_changed event callback function.
 */
int utc_ime_event_set_display_language_changed_cb_p(void)
{
    int ret = ime_event_set_display_language_changed_cb(_display_language_changed_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_rotation_degree_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets #c rotation_degree_changed event callback function.
 */
int utc_ime_event_set_rotation_degree_changed_cb_p(void)
{
    int ret = ime_event_set_rotation_degree_changed_cb(_rotation_degree_changed_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_accessibility_state_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c accessibility_state_changed event callback function.
 */
int utc_ime_event_set_accessibility_state_changed_cb_p(void)
{
    int ret = ime_event_set_accessibility_state_changed_cb(_accessibility_state_changed_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_option_window_created_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c option_window_created event callback function.
 */
int utc_ime_event_set_option_window_created_cb_p(void)
{
    int ret = ime_event_set_option_window_created_cb(_option_window_created_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_option_window_destroyed_cb_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sets @c option_window_destroyed event callback function.
 */
int utc_ime_event_set_option_window_destroyed_cb_p(void)
{
    int ret = ime_event_set_option_window_destroyed_cb(_option_window_destroyed_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

#ifndef TV
/**
 * @testcase		utc_ime_event_set_input_hint_set_cb_p
 * @since_tizen		6.5
 * @description		Positive UTC of the function that sets @c input_hint_set event callback function.
 */
int utc_ime_event_set_input_hint_set_cb_p(void)
{
    int ret = ime_event_set_input_hint_set_cb(_input_hint_set_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_event_unset_input_hint_set_cb_p
 * @since_tizen		6.5
 * @description		Positive UTC of the function that unsets @c input_hint_set event callback function.
 */
int utc_ime_event_unset_input_hint_set_cb_p(void)
{
    int ret = ime_event_unset_input_hint_set_cb();
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}
#endif

/**
 * @testcase		utc_ime_send_key_event_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sends a key event to the associated text input UI control.
 */
int utc_ime_send_key_event_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_send_key_event);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_commit_string_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that sends the text to the associated text input UI control.
 */
int utc_ime_commit_string_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_commit_string);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_show_preedit_string_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that requests to show preedit string.
 */
int utc_ime_show_preedit_string_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_show_preedit_string);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_hide_preedit_string_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that requests to hide preedit string.
 */
int utc_ime_hide_preedit_string_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_hide_preedit_string);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_update_preedit_string_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that updates a new preedit string.
 */
int utc_ime_update_preedit_string_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_update_preedit_string);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_request_surrounding_text_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that requests the surrounding text from the position of the cursor, asynchronously.
 */
int utc_ime_request_surrounding_text_p(void)
{
    int ret = ime_event_set_surrounding_text_updated_cb(_surrounding_text_updated_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    ret = ime_run(&basic_callback, (void *)_ime_request_surrounding_text);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_delete_surrounding_text_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that requests to delete surrounding text.
 */
int utc_ime_delete_surrounding_text_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_delete_surrounding_text);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_get_surrounding_text_p
 * @since_tizen		3.0
 * @description		Positive UTC of the function that requests to get surrounding text.
 */
int utc_ime_get_surrounding_text_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_get_surrounding_text);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_set_selection_p
 * @since_tizen		3.0
 * @description		Positive UTC of the function that requests to set selection text.
 */
int utc_ime_set_selection_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_set_selection);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_get_main_window_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that returns the pointer of input panel main window.
 */
int utc_ime_get_main_window_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_get_main_window);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_set_size_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that updates the input panel window's size information.
 */
int utc_ime_set_size_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_set_size);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_create_option_window_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that requests to create an option window from the input panel.
 */
int utc_ime_create_option_window_p(void)
{
    int ret = ime_event_set_option_window_created_cb(_option_window_created_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    ret = ime_event_set_option_window_destroyed_cb(_option_window_destroyed_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    ret = ime_run(&basic_callback, (void *)_ime_create_option_window);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_ime_destroy_option_window_p
 * @since_tizen		2.4
 * @description		Positive UTC of the function that requests to destroy an option window.
 */
int utc_ime_destroy_option_window_p(void)
{
    int ret = ime_event_set_option_window_created_cb(_option_window_created_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    ret = ime_event_set_option_window_destroyed_cb(_option_window_destroyed_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    ret = ime_run(&basic_callback, (void *)_ime_destroy_option_window);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_event_set_prediction_hint_set_cb_p
 * @since_tizen     4.0
 * @description     Positive UTC of the function that sets @c prediction_hint event callback function.
 */
int utc_ime_event_set_prediction_hint_set_cb_p(void)
{
    int ret = ime_event_set_prediction_hint_set_cb(_prediction_hint_set_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_send_private_command_p
 * @since_tizen     4.0
 * @description     Positive UTC of the function that sends the private_command to the associated text input UI control.
 */
int utc_ime_send_private_command_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_send_private_command);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_event_set_mime_type_set_request_cb_p
 * @since_tizen     4.0
 * @description     Positive UTC of the function that sets @c mime_type event callback function.
 */
int utc_ime_event_set_mime_type_set_request_cb_p(void)
{
    int ret = ime_event_set_mime_type_set_request_cb(_mime_type_set_request_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_commit_content_p
 * @since_tizen     4.0
 * @description     Positive UTC of the function that sends the content to the associated text input UI control.
 */
int utc_ime_commit_content_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_commit_content);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_set_floating_mode_p
 * @since_tizen     4.0
 * @description     Positive UTC of the function that sets the floating mode of input panel window.
 */
int utc_ime_set_floating_mode_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_set_floating_mode);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_set_floating_drag_start_p
 * @since_tizen     4.0
 * @description     Positive UTC of the function that allows the movement of the floating input panel window.
 */
int utc_ime_set_floating_drag_start_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_set_floating_drag_start);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_set_floating_drag_end_p
 * @since_tizen     4.0
 * @description     Positive UTC of the function that disallows the movement of the floating input panel window.
 */
int utc_ime_set_floating_drag_end_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_set_floating_drag_end);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_get_selected_text_p
 * @since_tizen     4.0
 * @description     Positive UTC of the function that gets the selected text synchronously.
 */
int utc_ime_get_selected_text_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_get_selected_text);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_request_hide_p
 * @since_tizen     5.0
 * @description     Positive UTC of the function that sends the request to hide IME.
 */
int utc_ime_request_hide_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_request_hide);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_event_set_prediction_hint_data_set_cb_p
 * @since_tizen     5.0
 * @description     Positive UTC of the function that sets @c prediction_hint_data event callback function.
 */
int utc_ime_event_set_prediction_hint_data_set_cb_p(void)
{
    int ret = ime_event_set_prediction_hint_data_set_cb(_prediction_hint_data_set_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_update_input_panel_event_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that updates the state of input panel event.
 */
int utc_ime_update_input_panel_event_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_update_input_panel_event);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_event_set_process_key_event_with_keycode_cb_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets @c process_key_event_with_keycode event callback function.
 */
int utc_ime_event_set_process_key_event_with_keycode_cb_p(void)
{
    int ret = ime_event_set_process_key_event_with_keycode_cb(_process_key_event_with_keycode_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_ime_set_candidate_visibility_state_p
 * @since_tizen     5.5
 * @description     Positive UTC of the function that sets the candidate visibility state.
 */
int utc_ime_set_candidate_visibility_state_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_set_candidate_visibility_state);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}

#ifndef TV
/**
 * @testcase		utc_ime_update_preedit_cursor_p
 * @since_tizen		6.5
 * @description		Positive UTC of the function that updates the position of preedit cursor.
 */
int utc_ime_update_preedit_cursor_p(void)
{
    int ret = ime_run(&basic_callback, (void *)_ime_update_preedit_cursor);
    assert_eq(ret, IME_ERROR_NONE);
    assert_eq(g_ret, IME_ERROR_NONE);
    return 0;
}
#endif

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_ime_run_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that runs the main loop of IME application.
 */
int utc_ime_run_n(void)
{
    int ret = ime_run(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_run_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that runs the main loop of IME application.
 */
int utc_ime_run_n2(void)
{
    ime_callback_s ime_cb = {NULL, NULL, NULL, NULL};
    int ret = ime_run(&ime_cb, NULL);
    assert_eq(ret, IME_ERROR_NO_CALLBACK_FUNCTION);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_focus_in_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c focus_in event callback function.
 */
int utc_ime_event_set_focus_in_cb_n(void)
{
    int ret = ime_event_set_focus_in_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_focus_out_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c focus_out event callback function.
 */
int utc_ime_event_set_focus_out_cb_n(void)
{
    int ret = ime_event_set_focus_out_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_surrounding_text_updated_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests the surrounding text from the position of the cursor, asynchronously.
 */
int utc_ime_event_set_surrounding_text_updated_cb_n(void)
{
    int ret = ime_event_set_surrounding_text_updated_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_input_context_reset_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets #c input_context_reset event callback function.
 */
int utc_ime_event_set_input_context_reset_cb_n(void)
{
    int ret = ime_event_set_input_context_reset_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_cursor_position_updated_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c cursor_position_updated event callback function.
 */
int utc_ime_event_set_cursor_position_updated_cb_n(void)
{
    int ret = ime_event_set_cursor_position_updated_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_language_requested_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c language_requested event callback function.
 */
int utc_ime_event_set_language_requested_cb_n(void)
{
    int ret = ime_event_set_language_requested_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_language_set_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c language_set event callback function.
 */
int utc_ime_event_set_language_set_cb_n(void)
{
    int ret = ime_event_set_language_set_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_imdata_set_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c imdata_set event callback function.
 */
int utc_ime_event_set_imdata_set_cb_n(void)
{
    int ret = ime_event_set_imdata_set_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_imdata_requested_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c imdata_requested event callback function.
 */
int utc_ime_event_set_imdata_requested_cb_n(void)
{
    int ret = ime_event_set_imdata_requested_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_layout_set_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c layout_set event callback function.
 */
int utc_ime_event_set_layout_set_cb_n(void)
{
    int ret = ime_event_set_layout_set_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_return_key_type_set_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c return_key_type_set event callback function.
 */
int utc_ime_event_set_return_key_type_set_cb_n(void)
{
    int ret = ime_event_set_return_key_type_set_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_return_key_state_set_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c return_key_state_set event callback function.
 */
int utc_ime_event_set_return_key_state_set_cb_n(void)
{
    int ret = ime_event_set_return_key_state_set_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_geometry_requested_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c geometry_requested event callback function.
 */
int utc_ime_event_set_geometry_requested_cb_n(void)
{
    int ret = ime_event_set_geometry_requested_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_process_key_event_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c process_key_event event callback function.
 */
int utc_ime_event_set_process_key_event_cb_n(void)
{
    int ret = ime_event_set_process_key_event_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_display_language_changed_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c display_language_changed event callback function.
 */
int utc_ime_event_set_display_language_changed_cb_n(void)
{
    int ret = ime_event_set_display_language_changed_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_rotation_degree_changed_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets #c rotation_degree_changed event callback function.
 */
int utc_ime_event_set_rotation_degree_changed_cb_n(void)
{
    int ret = ime_event_set_rotation_degree_changed_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_accessibility_state_changed_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sets @c accessibility_state_changed event callback function.
 */
int utc_ime_event_set_accessibility_state_changed_cb_n(void)
{
    int ret = ime_event_set_accessibility_state_changed_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_option_window_created_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests to create an option window from the input panel.
 */
int utc_ime_event_set_option_window_created_cb_n(void)
{
    int ret = ime_event_set_option_window_created_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_event_set_option_window_destroyed_cb_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests to destroy an option window.
 */
int utc_ime_event_set_option_window_destroyed_cb_n(void)
{
    int ret = ime_event_set_option_window_destroyed_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

#ifndef TV
/**
 * @testcase		utc_ime_event_set_input_hint_set_cb_n
 * @since_tizen		6.5
 * @description		Negative UTC of the function that sets @c input_hint_set event callback function.
 */
int utc_ime_event_set_input_hint_set_cb_n(void)
{
    int ret = ime_event_set_input_hint_set_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}
#endif

/**
 * @testcase		utc_ime_send_key_event_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sends a key event to the associated text input UI control.
 */
int utc_ime_send_key_event_n(void)
{
    int ret = ime_send_key_event(IME_KEY_BackSpace, IME_KEY_MASK_PRESSED, true);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_commit_string_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sends the text to the associated text input UI control.
 */
int utc_ime_commit_string_n(void)
{
    int ret = ime_commit_string(NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_commit_string_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that sends the text to the associated text input UI control.
 */
int utc_ime_commit_string_n2(void)
{
    int ret = ime_commit_string("test");
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_show_preedit_string_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests to show preedit string.
 */
int utc_ime_show_preedit_string_n(void)
{
    int ret = ime_show_preedit_string();
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_hide_preedit_string_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests to hide preedit string.
 */
int utc_ime_hide_preedit_string_n(void)
{
    int ret = ime_hide_preedit_string();
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_update_preedit_string_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that updates a new preedit string.
 */
int utc_ime_update_preedit_string_n(void)
{
    int ret = ime_update_preedit_string(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_update_preedit_string_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that updates a new preedit string.
 */
int utc_ime_update_preedit_string_n2(void)
{
    int ret = ime_update_preedit_string("test", NULL);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_request_surrounding_text_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests the surrounding text from the position of the cursor, asynchronously.
 */
int utc_ime_request_surrounding_text_n(void)
{
    int ret = ime_request_surrounding_text(-1, -1);
    assert_eq(ret, IME_ERROR_NO_CALLBACK_FUNCTION);
    return 0;
}

/**
 * @testcase		utc_ime_request_surrounding_text_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests the surrounding text from the position of the cursor, asynchronously.
 */
int utc_ime_request_surrounding_text_n2(void)
{
    int ret = ime_event_set_surrounding_text_updated_cb(_surrounding_text_updated_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    ret = ime_request_surrounding_text(-1, -1);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_delete_surrounding_text_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests to delete surrounding text.
 */
int utc_ime_delete_surrounding_text_n(void)
{
    int ret = ime_delete_surrounding_text(0, 0);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_delete_surrounding_text_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests to delete surrounding text.
 */
int utc_ime_delete_surrounding_text_n2(void)
{
    int ret = ime_delete_surrounding_text(0, 1);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_get_surrounding_text_n
 * @since_tizen		3.0
 * @description		Negative UTC of the function that requests to get surrounding text.
 */
int utc_ime_get_surrounding_text_n(void)
{
    int ret = ime_get_surrounding_text(-1, -1, NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_set_selection_n
 * @since_tizen		3.0
 * @description		Negative UTC of the function that requests to set selection text.
 */
int utc_ime_set_selection_n(void)
{
    int ret = ime_set_selection(-1, -1);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_get_main_window_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that returns the pointer of input panel main window.
 */
int utc_ime_get_main_window_n(void)
{
    Evas_Object *win = ime_get_main_window();
    int ret = get_last_result();
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    assert_eq(win, NULL);
    return 0;
}

/**
 * @testcase		utc_ime_set_size_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that updates the input panel window's size information.
 */
int utc_ime_set_size_n(void)
{
    int ret = ime_set_size(0, 0, 0, 0);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_set_size_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that updates the input panel window's size information.
 */
int utc_ime_set_size_n2(void)
{
    int ret = ime_set_size(540, 400, 960, 300);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_create_option_window_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests to create an option window from the input panel.
 */
int utc_ime_create_option_window_n(void)
{
    int ret = ime_create_option_window();
    assert_eq(ret, IME_ERROR_NO_CALLBACK_FUNCTION);
    return 0;
}

/**
 * @testcase		utc_ime_create_option_window_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests to create an option window from the input panel.
 */
int utc_ime_create_option_window_n2(void)
{
    int ret = ime_event_set_option_window_created_cb(_option_window_created_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    ret = ime_event_set_option_window_destroyed_cb(_option_window_destroyed_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    ret = ime_create_option_window();
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_destroy_option_window_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests to destroy an option window.
 */
int utc_ime_destroy_option_window_n(void)
{
    int ret = ime_destroy_option_window(NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_destroy_option_window_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests to destroy an option window.
 */
int utc_ime_destroy_option_window_n2(void)
{
    int ret = ime_event_set_option_window_created_cb(_option_window_created_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    ret = ime_event_set_option_window_destroyed_cb(_option_window_destroyed_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    ret = ime_destroy_option_window(NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_destroy_option_window_n3
 * @since_tizen		2.4
 * @description		Negative UTC of the function that requests to destroy an option window.
 */
int utc_ime_destroy_option_window_n3(void)
{
    int ret = ime_event_set_option_window_created_cb(_option_window_created_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    ret = ime_event_set_option_window_destroyed_cb(_option_window_destroyed_cb, NULL);
    assert_eq(ret, IME_ERROR_NONE);
    ret = ime_destroy_option_window(_win);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_layout_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the layout information from the given input context.
 */
int utc_ime_context_get_layout_n(void)
{
    int ret = ime_context_get_layout(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_layout_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the layout information from the given input context.
 */
int utc_ime_context_get_layout_n2(void)
{
    Ecore_IMF_Input_Panel_Layout layout;
    int ret = ime_context_get_layout(_context, &layout);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_layout_variation_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the layout variation information from the given input context.
 */
int utc_ime_context_get_layout_variation_n(void)
{
    int ret = ime_context_get_layout_variation(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_layout_variation_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the layout variation information from the given input context.
 */
int utc_ime_context_get_layout_variation_n2(void)
{
    ime_layout_variation_e variation;
    int ret = ime_context_get_layout_variation(_context, &variation);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_cursor_position_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the cursor position information from the given input context.
 */
int utc_ime_context_get_cursor_position_n(void)
{
    int ret = ime_context_get_cursor_position(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_cursor_position_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the cursor position information from the given input context.
 */
int utc_ime_context_get_cursor_position_n2(void)
{
    int pos;
    int ret = ime_context_get_cursor_position(_context, &pos);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_autocapital_type_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the autocapital type information from the given input context.
 */
int utc_ime_context_get_autocapital_type_n(void)
{
    int ret = ime_context_get_autocapital_type(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_autocapital_type_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the autocapital type information from the given input context.
 */
int utc_ime_context_get_autocapital_type_n2(void)
{
    Ecore_IMF_Autocapital_Type type;
    int ret = ime_context_get_autocapital_type(_context, &type);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_return_key_type_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the @c Return key label type information from the given input context.
 */
int utc_ime_context_get_return_key_type_n(void)
{
    int ret = ime_context_get_return_key_type(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_return_key_type_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the @c Return key label type information from the given input context.
 */
int utc_ime_context_get_return_key_type_n2(void)
{
    Ecore_IMF_Input_Panel_Return_Key_Type type;
    int ret = ime_context_get_return_key_type(_context, &type);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_return_key_state_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the @c Return key state information from the given input context.
 */
int utc_ime_context_get_return_key_state_n(void)
{
    int ret = ime_context_get_return_key_state(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_return_key_state_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the @c Return key state information from the given input context.
 */
int utc_ime_context_get_return_key_state_n2(void)
{
    bool state;
    int ret = ime_context_get_return_key_state(_context, &state);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_prediction_mode_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the prediction mode information from the given input context.
 */
int utc_ime_context_get_prediction_mode_n(void)
{
    int ret = ime_context_get_prediction_mode(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_prediction_mode_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the prediction mode information from the given input context.
 */
int utc_ime_context_get_prediction_mode_n2(void)
{
    bool mode;
    int ret = ime_context_get_prediction_mode(_context, &mode);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_password_mode_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the password mode information from the given input context.
 */
int utc_ime_context_get_password_mode_n(void)
{
    int ret = ime_context_get_password_mode(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_password_mode_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the password mode information from the given input context.
 */
int utc_ime_context_get_password_mode_n2(void)
{
    bool mode;
    int ret = ime_context_get_password_mode(_context, &mode);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_input_hint_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the input hint information from the given input context.
 */
int utc_ime_context_get_input_hint_n(void)
{
    int ret = ime_context_get_input_hint(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_input_hint_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the input hint information from the given input context.
 */
int utc_ime_context_get_input_hint_n2(void)
{
    Ecore_IMF_Input_Hints hint;
    int ret = ime_context_get_input_hint(_context, &hint);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_bidi_direction_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the text bidirectional information from the given input context.
 */
int utc_ime_context_get_bidi_direction_n(void)
{
    int ret = ime_context_get_bidi_direction(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_bidi_direction_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the text bidirectional information from the given input context.
 */
int utc_ime_context_get_bidi_direction_n2(void)
{
    Ecore_IMF_BiDi_Direction dir;
    int ret = ime_context_get_bidi_direction(_context, &dir);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_language_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the preferred language information from the given input context.
 */
int utc_ime_context_get_language_n(void)
{
    int ret = ime_context_get_language(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_context_get_language_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the preferred language information from the given input context.
 */
int utc_ime_context_get_language_n2(void)
{
    Ecore_IMF_Input_Panel_Lang lang;
    int ret = ime_context_get_language(_context, &lang);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_device_info_get_name_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the device name of the key event.
 */
int utc_ime_device_info_get_name_n(void)
{
    int ret = ime_device_info_get_name(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_device_info_get_name_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the device name of the key event.
 */
int utc_ime_device_info_get_name_n2(void)
{
    char *dev_name;
    int ret = ime_device_info_get_name(_dev_info, &dev_name);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_device_info_get_class_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the device class of the key event.
 */
int utc_ime_device_info_get_class_n(void)
{
    int ret = ime_device_info_get_class(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_device_info_get_class_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the device class of the key event.
 */
int utc_ime_device_info_get_class_n2(void)
{
    Ecore_IMF_Device_Class dev_class;
    int ret = ime_device_info_get_class(_dev_info, &dev_class);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase		utc_ime_device_info_get_subclass_n
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the device subclass of the key event.
 */
int utc_ime_device_info_get_subclass_n(void)
{
    int ret = ime_device_info_get_subclass(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_device_info_get_subclass_n2
 * @since_tizen		2.4
 * @description		Negative UTC of the function that gets the device subclass of the key event.
 */
int utc_ime_device_info_get_subclass_n2(void)
{
    Ecore_IMF_Device_Subclass dev_subclass;
    int ret = ime_device_info_get_subclass(_dev_info, &dev_subclass);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase        utc_ime_event_set_prediction_hint_set_cb_n
 * @since_tizen     4.0
 * @description     Negative UTC of the function that sets @c prediction_hint event callback function.
 */
int utc_ime_event_set_prediction_hint_set_cb_n(void)
{
    int ret = ime_event_set_prediction_hint_set_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ime_send_private_command_n
 * @since_tizen     4.0
 * @description     Negative UTC of the function that sends the private_command to the associated text input UI control.
 */
int utc_ime_send_private_command_n(void)
{
    int ret = ime_send_private_command(NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ime_send_private_command_n2
 * @since_tizen     4.0
 * @description     Negative UTC of the function that sends the private_command to the associated text input UI control.
 */
int utc_ime_send_private_command_n2(void)
{
    int ret = ime_send_private_command("test");
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase        utc_ime_event_set_mime_type_set_request_cb_n
 * @since_tizen     4.0
 * @description     Negative UTC of the function that sets @c mime_type event callback function.
 */
int utc_ime_event_set_mime_type_set_request_cb_n(void)
{
    int ret = ime_event_set_mime_type_set_request_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ime_commit_content_n
 * @since_tizen     4.0
 * @description     Negative UTC of the function that sends the content to the associated text input UI control.
 */
int utc_ime_commit_content_n(void)
{
    int ret = ime_commit_content(NULL, NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ime_commit_content_n2
 * @since_tizen     4.0
 * @description     Negative UTC of the function that sends the content to the associated text input UI control.
 */
int utc_ime_commit_content_n2(void)
{
    int ret = ime_commit_content("test1", "test2", "test3");
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase        utc_ime_set_floating_mode_n
 * @since_tizen     4.0
 * @description     Negative UTC of the function that sets the floating mode of input panel window.
 */
int utc_ime_set_floating_mode_n(void)
{
    int ret = ime_set_floating_mode(true);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase        utc_ime_set_floating_drag_start_n
 * @since_tizen     4.0
 * @description     Negative UTC of the function that allows the movement of the floating input panel window.
 */
int utc_ime_set_floating_drag_start_n(void)
{
    int ret = ime_set_floating_drag_start();
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase        utc_ime_set_floating_drag_end_n
 * @since_tizen     4.0
 * @description     Negative UTC of the function that disallows the movement of the floating input panel window.
 */
int utc_ime_set_floating_drag_end_n(void)
{
    int ret = ime_set_floating_drag_end();
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase        utc_ime_get_selected_text_n
 * @since_tizen     4.0
 * @description     Negative UTC of the function that gets the selected text synchronously.
 */
int utc_ime_get_selected_text_n(void)
{
    char *text = NULL;
    int ret = ime_get_selected_text(&text);
    if (text)
        free(text);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase        utc_ime_get_selected_text_n2
 * @since_tizen     4.0
 * @description     Negative UTC of the function that gets the selected text synchronously.
 */
int utc_ime_get_selected_text_n2(void)
{
    int ret = ime_get_selected_text(NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ime_request_hide_n
 * @since_tizen     5.0
 * @description     Negative UTC of the function that sends the request to hide IME.
 */
int utc_ime_request_hide_n(void)
{
    int ret = ime_request_hide();
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase        utc_ime_event_set_prediction_hint_data_set_cb_n
 * @since_tizen     5.0
 * @description     Negative UTC of the function that sets @c prediction_hint_data event callback function.
 */
int utc_ime_event_set_prediction_hint_data_set_cb_n(void)
{
    int ret = ime_event_set_prediction_hint_data_set_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ime_update_input_panel_event_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that updates the state of input panel event.
 */
int utc_ime_update_input_panel_event_n(void)
{
    int ret = ime_update_input_panel_event(IME_EVENT_TYPE_SHIFT_MODE, 0);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

/**
 * @testcase        utc_ime_event_set_process_key_event_with_keycode_cb_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets @c process_key_event_with_keycode event callback function.
 */
int utc_ime_event_set_process_key_event_with_keycode_cb_n(void)
{
    int ret = ime_event_set_process_key_event_with_keycode_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_ime_set_candidate_visibility_state_n
 * @since_tizen     5.5
 * @description     Negative UTC of the function that sets the candidate visibility state.
 */
int utc_ime_set_candidate_visibility_state_n(void)
{
    int ret = ime_set_candidate_visibility_state(true);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}

#ifndef TV
/**
 * @testcase		utc_ime_update_preedit_cursor_n
 * @since_tizen		6.5
 * @description		Negative UTC of the function that updates the position of preedit cursor.
 */
int utc_ime_update_preedit_cursor_n(void)
{
    int ret = ime_update_preedit_cursor(0);
    assert_eq(ret, IME_ERROR_NOT_RUNNING);
    return 0;
}
#endif

#ifdef WEARABLE
/**
 * @testcase		utc_ime_event_set_process_input_device_event_cb_n
 * @since_tizen		3.0
 * @description		Negative UTC of the function that called when the input event is received from an unconventional input device that does not generate key events.
 */
int utc_ime_event_set_process_input_device_event_cb_n(void)
{
    int ret = ime_event_set_process_input_device_event_cb(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase		utc_ime_input_device_rotary_get_direction_n
 * @since_tizen		3.0
 * @description		Negative UTC of the function for Rotary input device event.
 */
int utc_ime_input_device_rotary_get_direction_n(void)
{
    int ret = ime_input_device_rotary_get_direction(NULL, NULL);
    assert_eq(ret, IME_ERROR_INVALID_PARAMETER);
    return 0;
}
#endif
