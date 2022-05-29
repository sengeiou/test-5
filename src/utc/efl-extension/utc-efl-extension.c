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
#include <efl_extension.h>

//& set: EflExt



static void
_naviframe_cb(void *data, Evas_Object *obj, void *event_info)
{
   elm_exit();
}

/**
 * @function		utc_efl_ext_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_efl_ext_startup(void)
{
   elm_init(0, NULL);
}

/**
 * @function		utc_efl_ext_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_efl_ext_cleanup(void)
{
   elm_shutdown();
}

static void
_win_del(void *data, Evas_Object *obj, void *event)
{
    elm_exit();
}

static Evas_Object*
_create_win(const char *name)
{
    Evas_Object *obj = NULL;

    obj = elm_win_add(NULL, name, ELM_WIN_BASIC);
    if (obj)
    {
        elm_win_title_set(obj, name);
        evas_object_smart_callback_add(obj, "delete,request",
                _win_del, NULL);
    }

    return obj;
}

/**
 * @testcase		utc_efl_ext_popup_back_p
 * @since_tizen		2.3
 * @description		To delete popup
 * @scenario		Popup is created
 *          		Remove popup
 */
int utc_efl_ext_popup_back_p(void)
{
    Evas_Object *win = NULL, *popup = NULL;

    win = _create_win("window");
    assert(win);
    popup = elm_popup_add(win);
    assert(popup);
    elm_win_resize_object_add(win, popup);
    evas_object_show(popup);
    evas_object_show(win);

    eext_popup_back_cb(NULL, popup, NULL);
    int refno = evas_object_ref_get(popup);
    assert_eq(refno, 0);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_ctxpopup_back_p
 * @since_tizen		2.3
 * @description		To dismiss ctxpopup
 * @scenario		Ctxpopup is created
 *          		Dismiss ctxpopup
 */
int utc_efl_ext_ctxpopup_back_p(void)
{
    Evas_Object *win = NULL, *ctx = NULL;

    win = _create_win("window");
    assert(win);
    evas_object_resize(win, 100, 100);

    ctx = elm_ctxpopup_add(win);
    assert(ctx);
    evas_object_size_hint_weight_set(ctx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_ctxpopup_item_append(ctx, "test", NULL, NULL, NULL);
    elm_win_resize_object_add(win, ctx);
    evas_object_show(ctx);
    evas_object_show(win);

    eext_ctxpopup_back_cb(NULL, ctx, NULL);
    int refno = evas_object_ref_get(ctx);
    assert_eq(refno, 0);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_naviframe_more_cb_p
 * @since_tizen		2.3
 * @description		Send the more key event to the naviframe top item
 * @scenario		Naviframe is created and item is pushed to it
 *          		Send the more key event to the item
 */
int utc_efl_ext_naviframe_more_cb_p(void)
{
    Evas_Object *win = NULL, *nf = NULL, *content = NULL;

    win = _create_win("window");
    assert(win);
    nf = elm_naviframe_add(win);
    assert(nf);
    content = elm_box_add(win);
    assert(content);
    elm_naviframe_item_push(nf, "title", NULL, NULL, content, NULL);
    elm_win_resize_object_add(win, nf);
    evas_object_show(nf);
    evas_object_show(win);

    eext_naviframe_more_cb(NULL, nf, NULL);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_naviframe_back_cb_p
 * @since_tizen		2.3
 * @description		Send the back key event to the naviframe top item
 * @scenario		Naviframe is created and item is pushed to it
 *          		Send the back key event to the item
 */
int utc_efl_ext_naviframe_back_cb_p(void)
{
    Evas_Object *win = NULL, *nf = NULL, *content = NULL;

    win = _create_win("window");
    assert(win);
    nf = elm_naviframe_add(win);
    assert(nf);
    content = elm_box_add(win);
    assert(content);
    elm_naviframe_item_push(nf, "title", NULL, NULL, content, NULL);
    elm_win_resize_object_add(win, nf);
    evas_object_show(nf);
    evas_object_show(win);

    eext_naviframe_back_cb(NULL, nf, NULL);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_object_event_callback_add_p1
 * @since_tizen		2.3
 * @description		Register an event callback for the naviframe
 * @scenario		Naviframe is created and item is pushed to it
 *          		Register the back key event callback for the naviframe
 */
int utc_efl_ext_object_event_callback_add_p1(void)
{
    Evas_Object *win = NULL, *nf = NULL, *content = NULL;

    win = _create_win("window");
    assert(win);
    nf = elm_naviframe_add(win);
    assert(nf);
    content = elm_box_add(win);
    assert(content);
    elm_naviframe_item_push(nf, "title", NULL, NULL, content, NULL);
    elm_win_resize_object_add(win, nf);
    evas_object_show(nf);
    evas_object_show(win);

    eext_object_event_callback_add(nf, EEXT_CALLBACK_BACK, _naviframe_cb, nf);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_object_event_callback_add_p2
 * @since_tizen		2.3
 * @description		Register an event callback for the naviframe
 * @scenario		Naviframe is created and item is pushed to it
 *          		Register the more key event callback for the naviframe
 */
int utc_efl_ext_object_event_callback_add_p2(void)
{
    Evas_Object *win = NULL, *nf = NULL, *content = NULL;

    win = _create_win("window");
    assert(win);
    nf = elm_naviframe_add(win);
    assert(nf);
    content = elm_box_add(win);
    assert(content);
    elm_naviframe_item_push(nf, "title", NULL, NULL, content, NULL);
    elm_win_resize_object_add(win, nf);
    evas_object_show(nf);
    evas_object_show(win);

    eext_object_event_callback_add(nf, EEXT_CALLBACK_MORE, _naviframe_cb, nf);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_object_event_callback_del_p
 * @since_tizen		2.3
 * @description		Delete an event callback from the naviframe
 * @scenario		Naviframe is created and item is pushed to it
 *          		Register an event callback for the naviframe
 *          		Delete the event callback from the naviframe
 */
int utc_efl_ext_object_event_callback_del_p(void)
{
    Evas_Object *win = NULL, *nf = NULL, *content = NULL;

    win = _create_win("window");
    assert(win);
    nf = elm_naviframe_add(win);
    assert(nf);
    content = elm_box_add(win);
    assert(content);
    elm_naviframe_item_push(nf, "title", NULL, NULL, content, NULL);
    elm_win_resize_object_add(win, nf);
    evas_object_show(nf);
    evas_object_show(win);

    eext_object_event_callback_add(nf, EEXT_CALLBACK_BACK, _naviframe_cb, nf);
    eext_object_event_callback_del(nf, EEXT_CALLBACK_BACK, _naviframe_cb);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

   return 0;
}

/**
 * @testcase		utc_efl_ext_entry_back_cb_p
 * @since_tizen		2.3
 * @description		Cancel selection in the entry
 * @scenario		Entry is created
 *          		Selection is made in the entry
 *          		Cancel selection in the entry
 */
int utc_efl_ext_entry_back_cb_p(void)
{
    Evas_Object *win = NULL, *en = NULL;
    const char *sel = NULL;

    win = _create_win("window");
    assert(win);
    en = elm_entry_add(win);
    assert(en);

    evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_object_text_set(en, "text");
    elm_win_resize_object_add(win, en);
    evas_object_show(en);
    evas_object_show(win);

    elm_entry_select_all(en);
    sel = elm_entry_selection_get(en);
    assert(sel);
    eext_entry_back_cb(NULL, en, NULL);
    sel = elm_entry_selection_get(en);
    assert_eq(sel, NULL);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

   return 0;
}

/**
 * @testcase		utc_efl_ext_entry_selection_start_cb_p
 * @since_tizen		2.3
 * @description		Register the back key callback for the entry
 * @scenario		Entry is created
 *          		Register the back key callback for the entry
 */
int utc_efl_ext_entry_selection_start_cb_p(void)
{
    Evas_Object *win = NULL, *en = NULL;

    win = _create_win("window");
    assert(win);
    en = elm_entry_add(win);
    assert(en);
    elm_entry_entry_set(en, "text");
    elm_win_resize_object_add(win, en);
    evas_object_show(en);
    evas_object_show(win);

    eext_entry_selection_start_cb(NULL, en, NULL);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_entry_selection_cleared_cb_p
 * @since_tizen		2.3
 * @description		Clear the back key callback from the entry
 * @scenario		Entry is created
 *          		Remove the back key callback from the entry
 */
int utc_efl_ext_entry_selection_cleared_cb_p(void)
{
    Evas_Object *win = NULL, *en = NULL;

    win = _create_win("window");
    assert(win);
    en = elm_entry_add(win);
    assert(en);
    elm_entry_entry_set(en, "text");
    evas_object_show(en);
    evas_object_show(win);

    eext_entry_selection_cleared_cb(NULL, en, NULL);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_entry_selection_back_event_allow_set_p1
 * @since_tizen		2.3
 * @description		Set selection handling (allow back key event) in the entry
 * @scenario		Entry is created
 *          		Enable selection handling in the entry
 */
int utc_efl_ext_entry_selection_back_event_allow_set_p1(void)
{
    Evas_Object *win = NULL, *en = NULL;

    win = _create_win("window");
    assert(win);
    en = elm_entry_add(win);
    elm_entry_entry_set(en, "text");
    elm_win_resize_object_add(win, en);
    evas_object_show(en);
    evas_object_show(win);

    eext_entry_selection_back_event_allow_set(en, EINA_TRUE);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_entry_selection_back_event_allow_set_p2
 * @since_tizen		2.3
 * @description		Set selection handling (do not allow back key event) in the entry
 * @scenario		Entry is created
 *          		Disable selection handling in the entry
 */
int utc_efl_ext_entry_selection_back_event_allow_set_p2(void)
{
    Evas_Object *win = NULL, *en = NULL;

    win = _create_win("window");
    assert(win);
    en = elm_entry_add(win);
    elm_entry_entry_set(en, "text");
    elm_win_resize_object_add(win, en);
    evas_object_show(en);
    evas_object_show(win);

    eext_entry_selection_back_event_allow_set(en, EINA_FALSE);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_win_keygrab_set_p
 * @since_tizen		2.4
 * @description		Set keygrab value of a window
 * @scenario		Window is created
 *          		Set a keygrab value for the window
 */
int utc_efl_ext_win_keygrab_set_p(void)
{
    Evas_Object *win = NULL;
    Eina_Bool ret = EINA_FALSE;
    Ecore_Timer *timer = NULL;

    win = _create_win("window");
    assert(win);
    evas_object_show(win);

#ifdef MOBILE
    ret = eext_win_keygrab_set(win, "XF86PowerOff");
#endif
#ifdef WEARABLE
    ret = eext_win_keygrab_set(win, "XF86PowerOff");
#endif
#ifdef TV
    ret = eext_win_keygrab_set(win, "XF86PowerOff");
#endif
#ifdef TIZENIOT
    ret = eext_win_keygrab_set(win, "XF86PowerOff");
#endif

    assert(ret);

#ifdef MOBILE
    eext_win_keygrab_unset(win, "XF86PowerOff");
#endif
#ifdef WEARABLE
    eext_win_keygrab_unset(win, "XF86PowerOff");
#endif
#ifdef TV
    eext_win_keygrab_unset(win, "XF86PowerOff");
#endif
#ifdef TIZENIOT
    eext_win_keygrab_unset(win, "XF86PowerOff");
#endif

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_win_keygrab_unset_p
 * @since_tizen		2.4
 * @description		Unset keygrab value of a window
 * @scenario		Window is created
 *          		Unset a keygrab value for the window
 */
int utc_efl_ext_win_keygrab_unset_p(void)
{
    Evas_Object *win = NULL;
    Eina_Bool ret = EINA_FALSE;
    Ecore_Timer *timer = NULL;

    win = _create_win("window");
    assert(win);
    evas_object_show(win);

#ifdef MOBILE
    ret = eext_win_keygrab_set(win, "XF86PowerOff");
#endif
#ifdef WEARABLE
    ret = eext_win_keygrab_set(win, "XF86PowerOff");
#endif
#ifdef TV
    ret = eext_win_keygrab_set(win, "XF86PowerOff");
#endif
#ifdef TIZENIOT
    ret = eext_win_keygrab_set(win, "XF86PowerOff");
#endif

    assert(ret);

#ifdef MOBILE
    ret = eext_win_keygrab_unset(win, "XF86PowerOff");
#endif
#ifdef WEARABLE
    ret = eext_win_keygrab_unset(win, "XF86PowerOff");
#endif
#ifdef TV
    ret = eext_win_keygrab_unset(win, "XF86PowerOff");
#endif
#ifdef TIZENIOT
    ret = eext_win_keygrab_unset(win, "XF86PowerOff");
#endif

    assert(ret);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

#if (defined(MOBILE) || defined(TV))
/**
 * @testcase		utc_efl_ext_floatingbutton_add_p
 * @since_tizen		2.4
 * @description		Add new floating button
 * @scenario		Add new floating button with suitable parent
 */
int utc_efl_ext_floatingbutton_add_p(void)
{
    Evas_Object *win = NULL, *fb = NULL;

    win = _create_win("window");
    assert(win);
    fb = eext_floatingbutton_add(win);
    assert(fb);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_floatingbutton_add_n
 * @since_tizen		2.4
 * @description		Add new floating button
 * @scenario		Try to add new floating button with incorrect parent
 */
int utc_efl_ext_floatingbutton_add_n(void)
{
    Evas_Object *win = NULL, *fb = NULL;

    win = _create_win("window");
    assert(win);
    fb = eext_floatingbutton_add(NULL);
    assert_eq(fb, NULL);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_floatingbutton_pos_set_p
 * @since_tizen		2.4
 * @description		Set position of floating button
 * @scenario		Add new floating button
 *          		Set position for the floating button with valid position
 */
int utc_efl_ext_floatingbutton_pos_set_p(void)
{
    Evas_Object *win = NULL, *fb = NULL;
    Eina_Bool ret = EINA_FALSE;

    win = _create_win("window");
    assert(win);
    fb = eext_floatingbutton_add(win);
    assert(fb);
    elm_win_resize_object_add(win, fb);
    evas_object_show(fb);
    evas_object_show(win);

    ret = eext_floatingbutton_pos_set(fb, EEXT_FLOATINGBUTTON_RIGHT);
    assert_eq(ret, EINA_TRUE);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_floatingbutton_pos_set_n
 * @since_tizen		2.4
 * @description		Set position of floating button
 * @scenario		Add new floating button
 *          		Try to set position for the floating button with invalid position
 */
int utc_efl_ext_floatingbutton_pos_set_n(void)
{
    Evas_Object *win = NULL, *fb = NULL;
    Eina_Bool ret = EINA_FALSE;

    win = _create_win("window");
    assert(win);
    fb = eext_floatingbutton_add(win);
    assert(fb);
    elm_win_resize_object_add(win, fb);
    evas_object_show(fb);
    evas_object_show(win);

    ret = eext_floatingbutton_pos_set(fb, -1);
    assert_eq(ret, EINA_FALSE);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}


/**
 * @testcase		utc_efl_ext_floatingbutton_pos_get_p
 * @since_tizen		2.4
 * @description		Get position of a floating button
 * @scenario		Add new floating button
 *          		Set the position for the floating button
 *          		Get the position of the floating button
 */
int utc_efl_ext_floatingbutton_pos_get_p(void)
{
    Evas_Object *win = NULL, *fb = NULL;
    Eina_Bool ret = EINA_FALSE;

    win = _create_win("window");
    assert(win);
    fb = eext_floatingbutton_add(win);
    assert(fb);
    ret = eext_floatingbutton_pos_set(fb, EEXT_FLOATINGBUTTON_RIGHT);
    assert_eq(ret, EINA_TRUE);
    elm_win_resize_object_add(win, fb);
    evas_object_show(fb);
    evas_object_show(win);

    ret = eext_floatingbutton_pos_get(fb);
    assert_eq(ret, EEXT_FLOATINGBUTTON_RIGHT);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_floatingbutton_movement_block_set_p1
 * @since_tizen		2.4
 * @description		Enable the movement of a floating button
 * @scenario		Add new floating button
 *          		Enable the movement of the floating button
 */
int utc_efl_ext_floatingbutton_movement_block_set_p1(void)
{
    Evas_Object *win = NULL, *fb = NULL;

    win = _create_win("window");
    assert(win);
    fb = eext_floatingbutton_add(win);
    assert(fb);
    elm_win_resize_object_add(win, fb);
    evas_object_show(fb);
    evas_object_show(win);

    eext_floatingbutton_movement_block_set(fb, EINA_TRUE);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_floatingbutton_movement_block_set_p2
 * @since_tizen		2.4
 * @description		Disable the movement of a floating button
 * @scenario		Add new floating button
 *          		Disable the movement of the floating button
 */
int utc_efl_ext_floatingbutton_movement_block_set_p2(void)
{
    Evas_Object *win = NULL, *fb = NULL;

    win = _create_win("window");
    assert(win);
    fb = eext_floatingbutton_add(win);
    assert(fb);
    elm_win_resize_object_add(win, fb);
    evas_object_show(fb);
    evas_object_show(win);

    eext_floatingbutton_movement_block_set(fb, EINA_FALSE);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_floatingbutton_movement_block_get_p
 * @since_tizen		2.4
 * @description		Get whether a floating button can be moved around or not
 * @scenario		Add new floating button
 *          		Enable the movement of the floating button
 *          		Get whether the floating button can be moved around or not
 */
int utc_efl_ext_floatingbutton_movement_block_get_p(void)
{
    Evas_Object *win = NULL, *fb = NULL;
    Eina_Bool ret = EINA_FALSE;

    win = _create_win("window");
    assert(win);
    fb = eext_floatingbutton_add(win);
    assert(fb);
    elm_win_resize_object_add(win, fb);
    evas_object_show(fb);
    evas_object_show(win);

    eext_floatingbutton_movement_block_set(fb, EINA_TRUE);
    ret = eext_floatingbutton_movement_block_get(fb);
    assert_eq(ret, EINA_TRUE);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_floatingbutton_mode_set_p1
 * @since_tizen		2.4
 * @description		Set floating button mode: can be moved around or not
 * @scenario		Add new floating button
 *          		Set mode of the floating button to default
 */
int utc_efl_ext_floatingbutton_mode_set_p1(void)
{
    Evas_Object *win = NULL, *fb = NULL;

    win = _create_win("window");
    assert(win);
    fb = eext_floatingbutton_add(win);
    assert(fb);
    elm_win_resize_object_add(win, fb);
    evas_object_show(fb);
    evas_object_show(win);

    eext_floatingbutton_mode_set(fb, EEXT_FLOATINGBUTTON_MODE_DEFAULT);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_floatingbutton_mode_set_p2
 * @since_tizen		2.4
 * @description		Set floating button mode: can be moved around or not
 * @scenario		Add new floating button
 *          		Set mode of the floating button to both sides
 */
int utc_efl_ext_floatingbutton_mode_set_p2(void)
{
    Evas_Object *win = NULL, *fb = NULL;

    win = _create_win("window");
    assert(win);
    fb = eext_floatingbutton_add(win);
    assert(fb);
    elm_win_resize_object_add(win, fb);
    evas_object_show(fb);
    evas_object_show(win);

    eext_floatingbutton_mode_set(fb, EEXT_FLOATINGBUTTON_MODE_BOTH_SIDES);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_floatingbutton_mode_get_p
 * @since_tizen		2.4
 * @description		Get floating button mode
 * @scenario		Add new floating button
 *          		Set mode of the floating button to default
 *          		Get mode of the floating button
 */
int utc_efl_ext_floatingbutton_mode_get_p(void)
{
    Evas_Object *win = NULL, *fb = NULL;
    Eext_Floatingbutton_Mode mode = EEXT_FLOATINGBUTTON_MODE_LAST;

    win = _create_win("window");
    assert(win);
    fb = eext_floatingbutton_add(win);
    assert(fb);
    elm_win_resize_object_add(win, fb);
    evas_object_show(fb);
    evas_object_show(win);

    eext_floatingbutton_mode_set(fb, EEXT_FLOATINGBUTTON_MODE_DEFAULT);
    mode = eext_floatingbutton_mode_get(fb);
    assert_eq(mode, EEXT_FLOATINGBUTTON_MODE_DEFAULT);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}

/**
 * @testcase		utc_efl_ext_floatingbutton_pos_bring_in_p
 * @since_tizen		2.4
 * @description		Set floating button position with animation
 * @scenario		Add new floating button
 *          		Set floating button position
 *          		Bring floating button to position with animation
 */
int utc_efl_ext_floatingbutton_pos_bring_in_p(void)
{
    Evas_Object *win = NULL, *fb = NULL;
    Eina_Bool ret = EINA_FALSE;

    win = _create_win("window");
    assert(win);
    fb = eext_floatingbutton_add(win);
    assert(fb);
    elm_win_resize_object_add(win, fb);
    evas_object_show(fb);
    evas_object_show(win);

    ret = eext_floatingbutton_pos_set(fb, EEXT_FLOATINGBUTTON_RIGHT);
    assert_eq(ret, EINA_TRUE);

    ret = EINA_FALSE;
    ret = eext_floatingbutton_pos_bring_in(fb, EEXT_FLOATINGBUTTON_RIGHT);
    assert_eq(ret, EINA_TRUE);

	/* Free memory for small memory device (e.g. iot device) even if elm_init
	 * count and elm_shutdown count are not matched. */
	evas_object_del(win);

    return 0;
}
#endif

#ifdef WEARABLE
Eina_Bool _rotary_callback(void *data, Evas_Object *obj, Eext_Rotary_Event_Info *info)
{
   return EINA_TRUE;
}

static char *_genlist_text_get(void *data, Evas_Object *obj, const char *part)
{
   return strdup("default");
}

int utc_efl_ext_rotary_object_event_callback_add_p(void)
{
   Eina_Bool ret = EINA_FALSE;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);

   ret = eext_rotary_object_event_callback_add(scr, _rotary_callback, NULL);
   assert(ret);

   return 0;
}

int utc_efl_ext_rotary_object_event_callback_add_n1(void)
{
   Eina_Bool ret = EINA_TRUE;

   ret = eext_rotary_object_event_callback_add(NULL, _rotary_callback, NULL);
   assert_eq(ret, EINA_FALSE);

   return 0;
}

int utc_efl_ext_rotary_object_event_callback_add_n2(void)
{
   Eina_Bool ret = EINA_TRUE;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);

   ret = eext_rotary_object_event_callback_add(scr, NULL, NULL);
   assert_eq(ret, EINA_FALSE);

   return 0;
}

int utc_efl_ext_rotary_object_event_callback_priority_add_p(void)
{
   Eina_Bool ret = EINA_FALSE;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);

   ret = eext_rotary_object_event_callback_priority_add(scr, EEXT_CALLBACK_PRIORITY_BEFORE,
                                                        _rotary_callback, NULL);
   assert(ret);

   return 0;
}

int utc_efl_ext_rotary_object_event_callback_priority_add_n1(void)
{
   Eina_Bool ret = EINA_TRUE;
   ret = eext_rotary_object_event_callback_priority_add(NULL, EEXT_CALLBACK_PRIORITY_BEFORE,
                                                        _rotary_callback, NULL);
   assert_eq(ret, EINA_FALSE);

   return 0;
}

int utc_efl_ext_rotary_object_event_callback_priority_add_n2(void)
{
   Eina_Bool ret = EINA_TRUE;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);

   ret = eext_rotary_object_event_callback_priority_add(scr, EEXT_CALLBACK_PRIORITY_BEFORE,
                                                        NULL, NULL);
   assert_eq(ret, EINA_FALSE);

   return 0;
}

int utc_efl_ext_rotary_object_event_callback_del_p1(void)
{
   Eina_Bool ret = EINA_FALSE;
   char s[] = "test";
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);

   ret = eext_rotary_object_event_callback_add(scr, _rotary_callback, s);
   assert(ret);

   char *s2 = (char *)eext_rotary_object_event_callback_del(scr, _rotary_callback);
   assert(s2);
   assert(ret);

   return 0;
}

int utc_efl_ext_rotary_object_event_callback_del_p2(void)
{
   Eina_Bool ret = EINA_FALSE;
   char s[] = "test";
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);

   ret = eext_rotary_object_event_callback_priority_add(scr, EEXT_CALLBACK_PRIORITY_BEFORE,
                                                        _rotary_callback, s);
   assert(ret);

   char *s2 = (char *)eext_rotary_object_event_callback_del(scr, _rotary_callback);
   assert(s2);
   assert(ret);

   return 0;
}

Eina_Bool _rotary_handler(void *data, Eext_Rotary_Event_Info *info)
{
   return EINA_TRUE;
}

int utc_efl_ext_rotary_event_handler_add_p(void)
{
   Eina_Bool ret = EINA_FALSE;

   ret = eext_rotary_event_handler_add(_rotary_handler, NULL);
   assert(ret);
   eext_rotary_event_handler_del(_rotary_handler);

   return 0;
}

int utc_efl_ext_rotary_event_handler_add_n(void)
{
   Eina_Bool ret = EINA_TRUE;

   ret = eext_rotary_event_handler_add(NULL, NULL);
   assert_eq(ret, EINA_FALSE);

   return 0;
}

int utc_efl_ext_rotary_event_handler_del_p(void)
{
   Eina_Bool ret = EINA_FALSE;
   char s[] = "test";

   ret = eext_rotary_event_handler_add(_rotary_handler, s);
   assert(ret);

   char *s2 = (char *)eext_rotary_event_handler_del(_rotary_handler);
   assert(s2);

   return 0;
}

int utc_efl_ext_rotary_object_event_activated_set_p(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);

   eext_rotary_object_event_activated_set(scr, EINA_TRUE);

   return 0;
}

int utc_efl_ext_rotary_object_event_activated_set_n(void)
{
   eext_rotary_object_event_activated_set(NULL, EINA_TRUE);

   return 0;
}

///////// efl_extension_circle_object.h //////////////////
int utc_efl_ext_eext_circle_object_line_width_set_p(void)
{
   int w = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *scr_cir = eext_circle_object_add(scr, NULL);
   assert(scr_cir);

   eext_circle_object_line_width_set(scr_cir, 10);
   w = eext_circle_object_line_width_get(scr_cir);
   assert_eq(w, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_line_width_set_n(void)
{
   int w = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_line_width_set(win, 10);
   w = eext_circle_object_line_width_get(win);
   assert_eq(w, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_line_width_get_p(void)
{
   int w = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *scr_cir = eext_circle_object_add(scr, NULL);
   assert(scr_cir);

   eext_circle_object_line_width_set(scr_cir, 10);
   w = eext_circle_object_line_width_get(scr_cir);
   assert_eq(w, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_line_width_get_n(void)
{
   int w = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_line_width_set(win, 10);
   w = eext_circle_object_line_width_get(win);
   assert_eq(w, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_angle_set_p(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_angle_set(cir_obj, 10);
   a = eext_circle_object_angle_get(cir_obj);
   assert_eq(a, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_angle_set_n(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_angle_set(win, 10);
   a = eext_circle_object_angle_get(win);
   assert_eq(a, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_angle_get_p(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_angle_set(cir_obj, 10);
   a = eext_circle_object_angle_get(cir_obj);
   assert_eq(a, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_angle_get_n(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_angle_set(win, 10);
   a = eext_circle_object_angle_get(win);
   assert_eq(a, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_angle_offset_set_p(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_angle_offset_set(cir_obj, 10);
   a = eext_circle_object_angle_offset_get(cir_obj);
   assert_eq(a, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_angle_offset_set_n(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_angle_offset_set(win, 10);
   a = eext_circle_object_angle_offset_get(win);
   assert_eq(a, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_angle_offset_get_p(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_angle_offset_set(cir_obj, 10);
   a = eext_circle_object_angle_offset_get(cir_obj);
   assert_eq(a, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_angle_offset_get_n(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_angle_offset_set(win, 10);
   a = eext_circle_object_angle_offset_get(win);
   assert_eq(a, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_angle_min_max_set_p(void)
{
   double min = 0, max = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_angle_min_max_set(cir_obj, 5, 10);
   eext_circle_object_angle_min_max_get(cir_obj, &min, &max);
   assert_eq(min, 5);
   assert_eq(max, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_angle_min_max_set_n(void)
{
   double min = -1, max = -1;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_angle_min_max_set(win, 5, 10);
   eext_circle_object_angle_min_max_get(win, &min, &max);
   assert_eq(min, 0);
   assert_eq(max, 0);

   return 0;
}

int utc_efl_ext_eext_circle_object_angle_min_max_get_p(void)
{
   double min = 0, max = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_angle_min_max_set(cir_obj, 5, 10);
   eext_circle_object_angle_min_max_get(cir_obj, &min, &max);
   assert_eq(min, 5);
   assert_eq(max, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_angle_min_max_get_n(void)
{
   double min = -1, max = -1;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_angle_min_max_set(win, 5, 10);
   eext_circle_object_angle_min_max_get(win, &min, &max);
   assert_eq(min, 0);
   assert_eq(max, 0);

   return 0;
}

int utc_efl_ext_eext_circle_object_value_min_max_set_p(void)
{
   double min = 0, max = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_value_min_max_set(cir_obj, 5, 10);
   eext_circle_object_value_min_max_get(cir_obj, &min, &max);
   assert_eq(min, 5);
   assert_eq(max, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_value_min_max_set_n(void)
{
   double min = -1, max = -1;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_value_min_max_set(win, 5, 10);
   eext_circle_object_value_min_max_get(win, &min, &max);
   assert_eq(min, 0);
   assert_eq(max, 0);

   return 0;
}

int utc_efl_ext_eext_circle_object_value_min_max_get_p(void)
{
   double min = 0, max = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_value_min_max_set(cir_obj, 5, 10);
   eext_circle_object_value_min_max_get(cir_obj, &min, &max);
   assert_eq(min, 5);
   assert_eq(max, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_value_min_max_get_n(void)
{
   double min = -1, max = -1;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_value_min_max_set(win, 5, 10);
   eext_circle_object_value_min_max_get(win, &min, &max);
   assert_eq(min, 0);
   assert_eq(max, 0);

   return 0;
}

int utc_efl_ext_eext_circle_object_value_set_p(void)
{
   double val = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_value_set(cir_obj, 10);
   val = eext_circle_object_value_get(cir_obj);
   assert_eq(val, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_value_set_n(void)
{
   double val = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_value_set(win, 10);
   val = eext_circle_object_value_get(win);
   assert_eq(val, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_value_get_p(void)
{
   double val = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_value_set(cir_obj, 10);
   val = eext_circle_object_value_get(cir_obj);
   assert_eq(val, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_value_get_n(void)
{
   double val = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_value_set(win, 10);
   val = eext_circle_object_value_get(win);
   assert_eq(val, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_color_set_p(void)
{
   int r = 0, g = 0, b = 0, a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_color_set(cir_obj, 10, 20, 30, 40);
   eext_circle_object_color_get(cir_obj, &r, &g, &b, &a);
   assert_eq(r, 10);
   assert_eq(g, 20);
   assert_eq(b, 30);
   assert_eq(a, 40);

   return 0;
}

int utc_efl_ext_eext_circle_object_color_set_n(void)
{
   int r = -1, g = -1, b = -1, a = -1;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_color_set(win, 10, 20, 30, 40);
   eext_circle_object_color_get(win, &r, &g, &b, &a);
   assert_eq(r, 0);
   assert_eq(g, 0);
   assert_eq(b, 0);
   assert_eq(a, 0);

   return 0;
}

int utc_efl_ext_eext_circle_object_color_get_p(void)
{
   int r = 0, g = 0, b = 0, a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_color_set(cir_obj, 10, 20, 30, 40);
   eext_circle_object_color_get(cir_obj, &r, &g, &b, &a);
   assert_eq(r, 10);
   assert_eq(g, 20);
   assert_eq(b, 30);
   assert_eq(a, 40);

   return 0;
}

int utc_efl_ext_eext_circle_object_color_get_n(void)
{
   int r = -1, g = -1, b = -1, a = -1;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_color_set(win, 10, 20, 30, 40);
   eext_circle_object_color_get(win, &r, &g, &b, &a);
   assert_eq(r, 0);
   assert_eq(g, 0);
   assert_eq(b, 0);
   assert_eq(a, 0);

   return 0;
}

int utc_efl_ext_eext_circle_object_radius_set_p(void)
{
   double rad = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_radius_set(cir_obj, 10);
   rad = eext_circle_object_radius_get(cir_obj);
   assert_eq(rad, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_radius_set_n(void)
{
   double rad = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_radius_set(win, 10);
   rad = eext_circle_object_radius_get(win);
   assert_eq(rad, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_radius_get_p(void)
{
   double rad = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_radius_set(cir_obj, 10);
   rad = eext_circle_object_radius_get(cir_obj);
   assert_eq(rad, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_radius_get_n(void)
{
   double rad = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_radius_set(win, 10);
   rad = eext_circle_object_radius_get(win);
   assert_eq(rad, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_disabled_set_p(void)
{
   Eina_Bool ret = EINA_FALSE;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_disabled_set(cir_obj, EINA_TRUE);
   ret = eext_circle_object_disabled_get(cir_obj);
   assert_eq(ret, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_circle_object_disabled_set_n(void)
{
   Eina_Bool ret = EINA_TRUE;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_disabled_set(win, 10);
   ret = eext_circle_object_disabled_get(win);
   assert_eq(ret, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_circle_object_disabled_get_p(void)
{
   Eina_Bool ret = EINA_FALSE;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_disabled_set(cir_obj, EINA_TRUE);
   ret = eext_circle_object_disabled_get(cir_obj);
   assert_eq(ret, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_circle_object_disabled_get_n(void)
{
   Eina_Bool ret = EINA_TRUE;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_disabled_set(win, 10);
   ret = eext_circle_object_disabled_get(win);
   assert_eq(ret, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_circle_object_add_p(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_line_width_set_p(void)
{
   int w = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *scr_cir = eext_circle_object_add(scr, NULL);
   assert(scr_cir);

   eext_circle_object_item_line_width_set(scr_cir, "default", 10);
   w = eext_circle_object_item_line_width_get(scr_cir, "default");
   assert_eq(w, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_line_width_set_n(void)
{
   int w = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_line_width_set(win, "default", 10);
   w = eext_circle_object_item_line_width_get(win, "default");
   assert_eq(w, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_line_width_get_p(void)
{
   int w = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *scr_cir = eext_circle_object_add(scr, NULL);
   assert(scr_cir);

   eext_circle_object_item_line_width_set(scr_cir, "default", 10);
   w = eext_circle_object_item_line_width_get(scr_cir, "default");
   assert_eq(w, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_line_width_get_n(void)
{
   int w = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_line_width_set(win, "default", 10);
   w = eext_circle_object_item_line_width_get(win, "default");
   assert_eq(w, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_angle_set_p(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_angle_set(cir_obj, "default", 10);
   a = eext_circle_object_item_angle_get(cir_obj, "default");
   assert_eq(a, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_angle_set_n(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_angle_set(win, "default", 10);
   a = eext_circle_object_item_angle_get(win, "default");
   assert_eq(a, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_angle_get_p(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_angle_set(cir_obj, "default", 10);
   a = eext_circle_object_item_angle_get(cir_obj, "default");
   assert_eq(a, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_angle_get_n(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_angle_set(win, "default", 10);
   a = eext_circle_object_item_angle_get(win, "default");
   assert_eq(a, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_angle_offset_set_p(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_angle_offset_set(cir_obj, "default", 10);
   a = eext_circle_object_item_angle_offset_get(cir_obj, "default");
   assert_eq(a, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_angle_offset_set_n(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_angle_offset_set(win, "default", 10);
   a = eext_circle_object_item_angle_offset_get(win, "default");
   assert_eq(a, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_angle_offset_get_p(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_angle_offset_set(cir_obj, "default", 10);
   a = eext_circle_object_item_angle_offset_get(cir_obj, "default");
   assert_eq(a, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_angle_offset_get_n(void)
{
   double a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_angle_offset_set(win, "default", 10);
   a = eext_circle_object_item_angle_offset_get(win, "default");
   assert_eq(a, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_angle_min_max_set_p(void)
{
   double min = 0, max = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_angle_min_max_set(cir_obj, "default", 5, 10);
   eext_circle_object_item_angle_min_max_get(cir_obj, "default", &min, &max);
   assert_eq(min, 5);
   assert_eq(max, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_angle_min_max_set_n(void)
{
   double min = -1, max = -1;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_angle_min_max_set(win, "default", 5, 10);
   eext_circle_object_item_angle_min_max_get(win, "default", &min, &max);
   assert_eq(min, 0);
   assert_eq(max, 0);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_angle_min_max_get_p(void)
{
   double min = 0, max = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_angle_min_max_set(cir_obj, "default", 5, 10);
   eext_circle_object_item_angle_min_max_get(cir_obj, "default", &min, &max);
   assert_eq(min, 5);
   assert_eq(max, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_angle_min_max_get_n(void)
{
   double min = -1, max = -1;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_angle_min_max_set(win, "default", 5, 10);
   eext_circle_object_item_angle_min_max_get(win, "default", &min, &max);
   assert_eq(min, 0);
   assert_eq(max, 0);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_value_min_max_set_p(void)
{
   double min = 0, max = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_value_min_max_set(cir_obj, "default", 5, 10);
   eext_circle_object_item_value_min_max_get(cir_obj, "default", &min, &max);
   assert_eq(min, 5);
   assert_eq(max, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_value_min_max_set_n(void)
{
   double min = -1, max = -1;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_value_min_max_set(win, "default", 5, 10);
   eext_circle_object_item_value_min_max_get(win, "default", &min, &max);
   assert_eq(min, 0);
   assert_eq(max, 0);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_value_min_max_get_p(void)
{
   double min = 0, max = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_value_min_max_set(cir_obj, "default", 5, 10);
   eext_circle_object_item_value_min_max_get(cir_obj, "default", &min, &max);
   assert_eq(min, 5);
   assert_eq(max, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_value_min_max_get_n(void)
{
   double min = -1, max = -1;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_value_min_max_set(win, "default", 5, 10);
   eext_circle_object_item_value_min_max_get(win, "default", &min, &max);
   assert_eq(min, 0);
   assert_eq(max, 0);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_value_set_p(void)
{
   double val = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_value_set(cir_obj, "default", 10);
   val = eext_circle_object_item_value_get(cir_obj, "default");
   assert_eq(val, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_value_set_n(void)
{
   double val = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_value_set(win, "default", 10);
   val = eext_circle_object_item_value_get(win, "default");
   assert_eq(val, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_value_get_p(void)
{
   double val = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_value_set(cir_obj, "default", 10);
   val = eext_circle_object_item_value_get(cir_obj, "default");
   assert_eq(val, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_value_get_n(void)
{
   double val = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_value_set(win, "default", 10);
   val = eext_circle_object_item_value_get(win, "default");
   assert_eq(val, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_color_set_p(void)
{
   int r = 0, g = 0, b = 0, a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_color_set(cir_obj, "default", 10, 20, 30, 40);
   eext_circle_object_item_color_get(cir_obj, "default", &r, &g, &b, &a);
   assert_eq(r, 10);
   assert_eq(g, 20);
   assert_eq(b, 30);
   assert_eq(a, 40);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_color_set_n(void)
{
   int r = -1, g = -1, b = -1, a = -1;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_color_set(win, "default", 10, 20, 30, 40);
   eext_circle_object_item_color_get(win, "default", &r, &g, &b, &a);
   assert_eq(r, 0);
   assert_eq(g, 0);
   assert_eq(b, 0);
   assert_eq(a, 0);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_color_get_p(void)
{
   int r = 0, g = 0, b = 0, a = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_color_set(cir_obj, "default", 10, 20, 30, 40);
   eext_circle_object_item_color_get(cir_obj, "default", &r, &g, &b, &a);
   assert_eq(r, 10);
   assert_eq(g, 20);
   assert_eq(b, 30);
   assert_eq(a, 40);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_color_get_n(void)
{
   int r = -1, g = -1, b = -1, a = -1;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_color_set(win, "default", 10, 20, 30, 40);
   eext_circle_object_item_color_get(win, "default", &r, &g, &b, &a);
   assert_eq(r, 0);
   assert_eq(g, 0);
   assert_eq(b, 0);
   assert_eq(a, 0);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_radius_set_p(void)
{
   double rad = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_radius_set(cir_obj, "default", 10);
   rad = eext_circle_object_item_radius_get(cir_obj, "default");
   assert_eq(rad, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_radius_set_n(void)
{
   double rad = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_radius_set(win, "default", 10);
   rad = eext_circle_object_item_radius_get(win, "default");
   assert_eq(rad, -1);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_radius_get_p(void)
{
   double rad = 0;
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *scr = elm_scroller_add(win);
   assert(scr);
   Evas_Object *cir_obj = eext_circle_object_add(scr, NULL);
   assert(cir_obj);

   eext_circle_object_item_radius_set(cir_obj, "default", 10);
   rad = eext_circle_object_item_radius_get(cir_obj, "default");
   assert_eq(rad, 10);

   return 0;
}

int utc_efl_ext_eext_circle_object_item_radius_get_n(void)
{
   double rad = 0;
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_object_item_radius_set(win, "default", 10);
   rad = eext_circle_object_item_radius_get(win, "default");
   assert_eq(rad, -1);

   return 0;
}

//////////

/////////// efl_extension_circle_surface.h ////////////////////
int utc_efl_ext_eext_circle_surface_conformant_add_p(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *cfm = elm_conformant_add(win);
   assert(cfm);
   Eext_Circle_Surface *sur = eext_circle_surface_conformant_add(cfm);
   assert(sur);

   return 0;
}

int utc_efl_ext_eext_circle_surface_conformant_add_n1(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);
   Eext_Circle_Surface *sur = eext_circle_surface_conformant_add(NULL);
   assert_eq(sur, NULL);

   return 0;
}

int utc_efl_ext_eext_circle_surface_conformant_add_n2(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);
   Eext_Circle_Surface *sur = eext_circle_surface_conformant_add(win);
   assert_eq(sur, NULL);

   return 0;
}

int utc_efl_ext_eext_circle_surface_layout_add_p(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *cfm = elm_layout_add(win);
   assert(cfm);
   Eext_Circle_Surface *sur = eext_circle_surface_layout_add(cfm);
   assert(sur);

   return 0;
}

int utc_efl_ext_eext_circle_surface_layout_add_n1(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);
   Eext_Circle_Surface *sur = eext_circle_surface_layout_add(NULL);
   assert_eq(sur, NULL);

   return 0;
}

int utc_efl_ext_eext_circle_surface_layout_add_n2(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);
   Eext_Circle_Surface *sur = eext_circle_surface_layout_add(win);
   assert_eq(sur, NULL);

   return 0;
}

int utc_efl_ext_eext_circle_surface_naviframe_add_p(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *nf = elm_naviframe_add(win);
   assert(nf);
   Eext_Circle_Surface *sur = eext_circle_surface_naviframe_add(nf);
   assert(sur);

   return 0;
}

int utc_efl_ext_eext_circle_surface_naviframe_add_n1(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);
   Eext_Circle_Surface *sur = eext_circle_surface_naviframe_add(NULL);
   assert_eq(sur, NULL);

   return 0;
}

int utc_efl_ext_eext_circle_surface_naviframe_add_n2(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);
   Eext_Circle_Surface *sur = eext_circle_surface_naviframe_add(win);
   assert_eq(sur, NULL);

   return 0;
}

int utc_efl_ext_eext_circle_surface_del_p(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);
   Evas_Object *cfm = elm_conformant_add(win);
   assert(cfm);
   Eext_Circle_Surface *sur = eext_circle_surface_conformant_add(cfm);
   assert(sur);

   eext_circle_surface_del(sur);

   return 0;
}

int utc_efl_ext_eext_circle_surface_del_n(void)
{
   Evas_Object *win = _create_win("window");
   assert(win);

   eext_circle_surface_del(NULL);

   return 0;
}
//////////

int utc_efl_ext_eext_circle_object_datetime_add_p(void)
{
   Evas_Object *win;
   Evas_Object *datetime, *circle_datetime;

   win = _create_win("window");
   assert(win);

   datetime = elm_datetime_add(win);
   assert(datetime);

   circle_datetime = eext_circle_object_datetime_add(datetime, NULL);
   assert(circle_datetime);

   return 0;
}

int utc_efl_ext_eext_circle_object_datetime_add_n(void)
{
   Evas_Object *circle_datetime;

   circle_datetime = eext_circle_object_datetime_add(NULL, NULL);
   assert_eq(circle_datetime, NULL);

   return 0;
}

int utc_efl_ext_eext_circle_object_genlist_add_p(void)
{
   Evas_Object *win;
   Evas_Object *genlist, *circle_genlist;

   win = _create_win("window");
   assert(win);

   genlist = elm_genlist_add(win);
   assert(win);

   circle_genlist = eext_circle_object_genlist_add(genlist, NULL);
   assert(circle_genlist);

   return 0;
}

int utc_efl_ext_eext_circle_object_genlist_add_n(void)
{
   Evas_Object *circle_genlist;

   circle_genlist = eext_circle_object_genlist_add(NULL, NULL);
   assert_eq(circle_genlist, NULL);

   return 0;
}

int utc_efl_ext_eext_circle_object_genlist_scroller_policy_get_p(void)
{
   Evas_Object *win;
   Evas_Object *genlist, *circle_genlist;
   Elm_Scroller_Policy policy_h = ELM_SCROLLER_POLICY_AUTO;
   Elm_Scroller_Policy policy_v = ELM_SCROLLER_POLICY_AUTO;

   win = _create_win("window");
   assert(win);

   genlist = elm_genlist_add(win);
   assert(win);

   circle_genlist = eext_circle_object_genlist_add(genlist, NULL);
   assert(circle_genlist);

   eext_circle_object_genlist_scroller_policy_get(circle_genlist, &policy_h, &policy_v);

   assert_eq(policy_h, ELM_SCROLLER_POLICY_AUTO);
   assert_eq(policy_v, ELM_SCROLLER_POLICY_AUTO);

   return 0;
}

int utc_efl_ext_eext_circle_object_genlist_scroller_policy_get_n(void)
{
   Elm_Scroller_Policy policy_h = ELM_SCROLLER_POLICY_OFF;
   Elm_Scroller_Policy policy_v = ELM_SCROLLER_POLICY_OFF;

   eext_circle_object_genlist_scroller_policy_get(NULL, &policy_h, &policy_v);

   assert_eq(policy_h, ELM_SCROLLER_POLICY_AUTO);
   assert_eq(policy_v, ELM_SCROLLER_POLICY_AUTO);

   return 0;
}

int utc_efl_ext_eext_circle_object_genlist_scroller_policy_set_p(void)
{
   Evas_Object *win;
   Evas_Object *genlist, *circle_genlist;
   Elm_Scroller_Policy policy_h = ELM_SCROLLER_POLICY_AUTO;
   Elm_Scroller_Policy policy_v = ELM_SCROLLER_POLICY_AUTO;

   win = _create_win("window");
   assert(win);

   genlist = elm_genlist_add(win);
   assert(win);

   circle_genlist = eext_circle_object_genlist_add(genlist, NULL);
   assert(circle_genlist);

   eext_circle_object_genlist_scroller_policy_set(circle_genlist, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_OFF);
   eext_circle_object_genlist_scroller_policy_get(circle_genlist, &policy_h, &policy_v);

   assert_eq(policy_h, ELM_SCROLLER_POLICY_ON);
   assert_eq(policy_v, ELM_SCROLLER_POLICY_OFF);

   return 0;
}

int utc_efl_ext_eext_circle_object_genlist_scroller_policy_set_n(void)
{
   Evas_Object *win;
   Evas_Object *genlist, *circle_genlist;

   win = _create_win("window");
   assert(win);

   genlist = elm_genlist_add(win);
   assert(win);

   circle_genlist = eext_circle_object_genlist_add(genlist, NULL);
   assert(circle_genlist);

   eext_circle_object_genlist_scroller_policy_set(NULL, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_OFF);
   eext_circle_object_genlist_scroller_policy_set(circle_genlist, ELM_SCROLLER_POLICY_AUTO - 1, ELM_SCROLLER_POLICY_OFF);
   eext_circle_object_genlist_scroller_policy_set(circle_genlist, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_AUTO - 1);

   return 0;
}

int utc_efl_ext_eext_circle_object_progressbar_add_p(void)
{
   Evas_Object *win;
   Evas_Object *progressbar;

   win = _create_win("window");
   assert(win);

   progressbar = eext_circle_object_progressbar_add(win, NULL);
   assert(progressbar);

   return 0;
}

int utc_efl_ext_eext_circle_object_progressbar_add_n(void)
{
   Evas_Object *progressbar;

   progressbar = eext_circle_object_progressbar_add(NULL, NULL);
   assert_eq(progressbar, NULL);

   return 0;
}

int utc_efl_ext_eext_circle_object_slider_add_p(void)
{
   Evas_Object *win;
   Evas_Object *slider;

   win = _create_win("window");
   assert(win);

   slider = eext_circle_object_slider_add(win, NULL);
   assert(slider);

   return 0;
}

int utc_efl_ext_eext_circle_object_slider_add_n(void)
{
   Evas_Object *slider;

   slider = eext_circle_object_slider_add(NULL, NULL);
   assert_eq(slider, NULL);

   return 0;
}

int utc_efl_ext_eext_circle_object_slider_step_set_p(void)
{
   Evas_Object *win;
   Evas_Object *slider;
   double step = 0;

   win = _create_win("window");
   assert(win);

   slider = eext_circle_object_slider_add(win, NULL);
   assert(slider);

   eext_circle_object_slider_step_set(slider, 5.0);
   step = eext_circle_object_slider_step_get(slider);

   assert(step);

   return 0;
}

int utc_efl_ext_eext_circle_object_slider_step_set_n(void)
{
   Evas_Object *win;
   Evas_Object *slider;
   double step = 1.0;

   win = _create_win("window");
   assert(win);

   slider = eext_circle_object_slider_add(win, NULL);
   assert(slider);

   eext_circle_object_slider_step_set(NULL, 5.0);
   step = eext_circle_object_slider_step_get(slider);

   assert_eq(step, 1.0);

   return 0;
}

int utc_efl_ext_eext_circle_object_slider_step_get_p(void)
{
   Evas_Object *win;
   Evas_Object *slider;
   double step = 0;

   win = _create_win("window");
   assert(win);

   slider = eext_circle_object_slider_add(win, NULL);
   assert(slider);

   eext_circle_object_slider_step_set(slider, 5.0);
   step = eext_circle_object_slider_step_get(slider);

   assert(step);

   return 0;
}

int utc_efl_ext_eext_circle_object_slider_step_get_n(void)
{
   Evas_Object *win;
   Evas_Object *slider;
   double step = 1.0;

   win = _create_win("window");
   assert(win);

   slider = eext_circle_object_slider_add(win, NULL);
   assert(slider);

   eext_circle_object_slider_step_set(slider, 5.0);
   step = eext_circle_object_slider_step_get(NULL);

   assert_neq(step, 1.0);

   return 0;
}

int utc_efl_ext_eext_circle_object_scroller_add_p(void)
{
   Evas_Object *win;
   Evas_Object *scroller;

   win = _create_win("window");
   assert(win);

   scroller = eext_circle_object_scroller_add(win, NULL);
   assert(scroller);

   return 0;
}

int utc_efl_ext_eext_circle_object_scroller_add_n(void)
{
   Evas_Object *scroller;

   scroller = eext_circle_object_scroller_add(NULL, NULL);
   assert_eq(scroller, NULL);

   return 0;
}

int utc_efl_ext_eext_circle_object_scroller_policy_get_p(void)
{
   Evas_Object *win;
   Evas_Object *scroller, *circle_scroller;
   Elm_Scroller_Policy policy_h = ELM_SCROLLER_POLICY_AUTO;
   Elm_Scroller_Policy policy_v = ELM_SCROLLER_POLICY_AUTO;

   win = _create_win("window");
   assert(win);

   scroller = elm_scroller_add(win);
   assert(win);

   circle_scroller = eext_circle_object_scroller_add(scroller, NULL);
   assert(circle_scroller);

   eext_circle_object_scroller_policy_get(circle_scroller, &policy_h, &policy_v);

   assert_eq(policy_h, ELM_SCROLLER_POLICY_AUTO);
   assert_eq(policy_v, ELM_SCROLLER_POLICY_AUTO);

   return 0;
}

int utc_efl_ext_eext_circle_object_scroller_policy_get_n(void)
{
   Evas_Object *win;
   Evas_Object *scroller, *circle_scroller;
   Elm_Scroller_Policy policy_h = ELM_SCROLLER_POLICY_AUTO;
   Elm_Scroller_Policy policy_v = ELM_SCROLLER_POLICY_AUTO;

   win = _create_win("window");
   assert(win);

   scroller = elm_scroller_add(win);
   assert(win);

   circle_scroller = eext_circle_object_scroller_add(scroller, NULL);
   assert(circle_scroller);

   eext_circle_object_scroller_policy_set(circle_scroller, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_OFF);
   eext_circle_object_scroller_policy_get(NULL, &policy_h, &policy_v);

   assert_eq(policy_h, ELM_SCROLLER_POLICY_AUTO);
   assert_eq(policy_v, ELM_SCROLLER_POLICY_AUTO);

   return 0;
}

int utc_efl_ext_eext_circle_object_scroller_policy_set_p(void)
{
   Evas_Object *win;
   Evas_Object *scroller, *circle_scroller;
   Elm_Scroller_Policy policy_h = ELM_SCROLLER_POLICY_AUTO;
   Elm_Scroller_Policy policy_v = ELM_SCROLLER_POLICY_AUTO;

   win = _create_win("window");
   assert(win);

   scroller = elm_scroller_add(win);
   assert(win);

   circle_scroller = eext_circle_object_scroller_add(scroller, NULL);
   assert(circle_scroller);

   eext_circle_object_scroller_policy_set(circle_scroller, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_OFF);
   eext_circle_object_scroller_policy_get(circle_scroller, &policy_h, &policy_v);

   assert_eq(policy_h, ELM_SCROLLER_POLICY_ON);
   assert_eq(policy_v, ELM_SCROLLER_POLICY_OFF);

   return 0;
}

int utc_efl_ext_eext_circle_object_scroller_policy_set_n(void)
{
   Evas_Object *win;
   Evas_Object *scroller, *circle_scroller;

   win = _create_win("window");
   assert(win);

   scroller = elm_scroller_add(win);
   assert(win);

   circle_scroller = eext_circle_object_scroller_add(scroller, NULL);
   assert(circle_scroller);

   eext_circle_object_scroller_policy_set(NULL, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_ON);
   eext_circle_object_scroller_policy_set(circle_scroller, ELM_SCROLLER_POLICY_AUTO - 1, ELM_SCROLLER_POLICY_OFF);
   eext_circle_object_scroller_policy_set(circle_scroller, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_AUTO - 1);

   return 0;
}

int utc_efl_ext_eext_circle_object_mirrored_set_p(void)
{
   Evas_Object *win;
   Evas_Object *scroller, *circle_scroller;

   win = _create_win("window");
   assert(win);

   scroller = elm_scroller_add(win);
   assert(win);

   circle_scroller = eext_circle_object_scroller_add(scroller, NULL);
   assert(circle_scroller);

   eext_circle_object_mirrored_set(circle_scroller, EEXT_CIRCLE_MIRRORED_ON);
   int mirror_mode = eext_circle_object_mirrored_get(circle_scroller);

   assert_eq(mirror_mode, EEXT_CIRCLE_MIRRORED_ON);

   return 0;
}

int utc_efl_ext_eext_circle_object_mirrored_set_n(void)
{
   Evas_Object *win;
   Evas_Object *scroller, *circle_scroller;

   win = _create_win("window");
   assert(win);

   scroller = elm_scroller_add(win);
   assert(win);

   circle_scroller = eext_circle_object_scroller_add(scroller, NULL);
   assert(circle_scroller);

   eext_circle_object_mirrored_set(NULL, EEXT_CIRCLE_MIRRORED_ON);

   return 0;
}

int utc_efl_ext_eext_circle_object_mirrored_get_p(void)
{
   Evas_Object *win;
   Evas_Object *scroller, *circle_scroller;

   win = _create_win("window");
   assert(win);

   scroller = elm_scroller_add(win);
   assert(win);

   circle_scroller = eext_circle_object_scroller_add(scroller, NULL);
   assert(circle_scroller);

   eext_circle_object_mirrored_set(circle_scroller, EEXT_CIRCLE_MIRRORED_ON);
   int mirror_mode = eext_circle_object_mirrored_get(circle_scroller);

   assert_eq(mirror_mode, EEXT_CIRCLE_MIRRORED_ON);

   return 0;
}

int utc_efl_ext_eext_circle_object_mirrored_get_n(void)
{
   Evas_Object *win;
   Evas_Object *scroller, *circle_scroller;

   win = _create_win("window");
   assert(win);

   scroller = elm_scroller_add(win);
   assert(win);

   circle_scroller = eext_circle_object_scroller_add(scroller, NULL);
   assert(circle_scroller);

   int mirror_mode = eext_circle_object_mirrored_get(NULL);

   assert_eq(mirror_mode, EEXT_CIRCLE_MIRRORED_OFF);

   return 0;
}


int utc_efl_ext_eext_more_option_add_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   return 0;
}

int utc_efl_ext_eext_more_option_add_n(void)
{
   Evas_Object *more_option;

   more_option = eext_more_option_add(NULL);
   assert_eq(more_option, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_direction_set_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_More_Option_Direction direction;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   eext_more_option_direction_set(more_option, EEXT_MORE_OPTION_DIRECTION_BOTTOM);
   direction = eext_more_option_direction_get(more_option);

   assert_eq(direction, EEXT_MORE_OPTION_DIRECTION_BOTTOM);

   return 0;
}

int utc_efl_ext_eext_more_option_direction_set_n(void)
{
   Evas_Object *win;

   win = _create_win("window");
   assert(win);

   eext_more_option_direction_set(NULL, EEXT_MORE_OPTION_DIRECTION_BOTTOM);
   eext_more_option_direction_set(win, EEXT_MORE_OPTION_DIRECTION_BOTTOM);
   
   return 0;
}

int utc_efl_ext_eext_more_option_direction_get_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_More_Option_Direction direction;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   direction = eext_more_option_direction_get(more_option);
   assert_eq(direction, EEXT_MORE_OPTION_DIRECTION_RIGHT);

   eext_more_option_direction_set(more_option, EEXT_MORE_OPTION_DIRECTION_BOTTOM);
   direction = eext_more_option_direction_get(more_option);
   assert_eq(direction, EEXT_MORE_OPTION_DIRECTION_BOTTOM);

   return 0;
}

int utc_efl_ext_eext_more_option_direction_get_n(void)
{
   Evas_Object *win;
   Eext_More_Option_Direction direction;

   win = _create_win("window");
   assert(win);

   direction = eext_more_option_direction_get(NULL);
   assert_eq(direction, EEXT_MORE_OPTION_DIRECTION_RIGHT);

   direction = eext_more_option_direction_get(win);
   assert_eq(direction, EEXT_MORE_OPTION_DIRECTION_RIGHT);

   return 0;
}

int utc_efl_ext_eext_more_option_item_append_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   return 0;
}

int utc_efl_ext_eext_more_option_item_append_n(void)
{
   Evas_Object *win;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   item = eext_more_option_item_append(NULL);
   assert_eq(item, NULL);

   item = eext_more_option_item_append(win);
   assert_eq(item, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_item_prepend_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_prepend(more_option);
   assert(item);

   return 0;
}

int utc_efl_ext_eext_more_option_item_prepend_n(void)
{
   Evas_Object *win;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   item = eext_more_option_item_prepend(NULL);
   assert_eq(item, NULL);

   item = eext_more_option_item_prepend(win);
   assert_eq(item, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_item_insert_after_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;
   Eext_Object_Item *inserted_item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   inserted_item = eext_more_option_item_insert_after(more_option, item);
   assert(inserted_item);

   return 0;
}

int utc_efl_ext_eext_more_option_item_insert_after_n(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;
   Eext_Object_Item *inserted_item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   inserted_item = eext_more_option_item_insert_after(NULL, item);
   assert_eq(inserted_item, NULL);

   inserted_item = eext_more_option_item_insert_after(NULL, NULL);
   assert_eq(inserted_item, NULL);

   inserted_item = eext_more_option_item_insert_after(win, item);
   assert_eq(inserted_item, NULL);

   inserted_item = eext_more_option_item_insert_after(win, NULL);
   assert_eq(inserted_item, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_item_insert_before_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;
   Eext_Object_Item *inserted_item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   inserted_item = eext_more_option_item_insert_before(more_option, item);
   assert(inserted_item);

   return 0;
}

int utc_efl_ext_eext_more_option_item_insert_before_n(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;
   Eext_Object_Item *inserted_item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   inserted_item = eext_more_option_item_insert_before(NULL, item);
   assert_eq(inserted_item, NULL);

   inserted_item = eext_more_option_item_insert_before(NULL, NULL);
   assert_eq(inserted_item, NULL);

   inserted_item = eext_more_option_item_insert_before(win, item);
   assert_eq(inserted_item, NULL);

   inserted_item = eext_more_option_item_insert_before(win, NULL);
   assert_eq(inserted_item, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_item_del_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;
   Eina_List *items;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   eext_more_option_item_del(item);
   items = eext_more_option_items_get(more_option);
   assert_eq(items, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_item_del_n(void)
{
   eext_more_option_item_del(NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_items_clear_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;
   Eina_List *items;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   eext_more_option_items_clear(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   item = eext_more_option_item_append(more_option);
   assert(item);

   eext_more_option_items_clear(more_option);
   items = eext_more_option_items_get(more_option);
   assert_eq(items, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_items_clear_n(void)
{
   Evas_Object *win;

   win = _create_win("window");
   assert(win);

   eext_more_option_items_clear(NULL);
   eext_more_option_items_clear(win);

   return 0;
}

int utc_efl_ext_eext_more_option_item_part_text_set_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;
   const char *text;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   eext_more_option_item_part_text_set(item, "selector,main_text", "elm.text test");
   text = eext_more_option_item_part_text_get(item, "selector,main_text");
   assert(!strcmp(text, "elm.text test"));

   eext_more_option_item_part_text_set(item, "selector,sub_text", "elm.text.sub test");
   text = eext_more_option_item_part_text_get(item, "selector,sub_text");
   assert(!strcmp(text, "elm.text.sub test"));

   return 0;
}

int utc_efl_ext_eext_more_option_item_part_text_set_n(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;
   const char *text;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   eext_more_option_item_part_text_set(item, NULL, NULL);
   text = eext_more_option_item_part_text_get(item, "selector,main_text");
   assert(!text || !strcmp(text, ""));

   eext_more_option_item_part_text_set(NULL, NULL, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_item_part_text_get_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;
   const char *text;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   eext_more_option_item_part_text_set(item, "selector,main_text", "elm.text test");
   text = eext_more_option_item_part_text_get(item, "selector,main_text");
   assert(!strcmp(text, "elm.text test"));

   eext_more_option_item_part_text_set(item, "selector,sub_text", "elm.text.sub test");
   text = eext_more_option_item_part_text_get(item, "selector,sub_text");
   assert(!strcmp(text, "elm.text.sub test"));

   return 0;
}

int utc_efl_ext_eext_more_option_item_part_text_get_n(void)
{
   const char *text;

   text = eext_more_option_item_part_text_get(NULL, NULL);
   assert_eq(text, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_item_domain_translatable_part_text_set_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;
   const char *text;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   eext_more_option_item_domain_translatable_part_text_set(item, "selector,main_text", "Korea", "elm.text test");
   text = eext_more_option_item_part_text_get(item, "selector,main_text");
   assert(text);

   eext_more_option_item_domain_translatable_part_text_set(item, "selector,sub_text", "Korea", "elm.text.sub test");
   text = eext_more_option_item_part_text_get(item, "selector,sub_text");
   assert(text);

   return 0;
}

int utc_efl_ext_eext_more_option_item_domain_translatable_part_text_set_n(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   eext_more_option_item_domain_translatable_part_text_set(item, NULL, NULL, NULL);
   eext_more_option_item_domain_translatable_part_text_set(NULL, NULL, NULL, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_item_part_content_set_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Evas_Object *img;
   Evas_Object *ret_obj;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   img = elm_image_add(more_option);
   eext_more_option_item_part_content_set(item, "item,icon", img);
   ret_obj = eext_more_option_item_part_content_get(item, "item,icon");
   assert_eq(ret_obj, img);

   return 0;
}

int utc_efl_ext_eext_more_option_item_part_content_set_n(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Evas_Object *img;
   Evas_Object *contents;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   img = elm_image_add(more_option);
   eext_more_option_item_part_content_set(item, NULL, img);
   contents = eext_more_option_item_part_content_get(item, "item,icon");
   assert_eq(contents, NULL);

   eext_more_option_item_part_content_set(NULL, NULL, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_item_part_content_get_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Evas_Object *img;
   Evas_Object *ret_obj;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   ret_obj = eext_more_option_item_part_content_get(item, "item,icon");
   assert_eq(ret_obj, NULL);

   img = elm_image_add(more_option);
   eext_more_option_item_part_content_set(item, "item,icon", img);
   ret_obj = eext_more_option_item_part_content_get(item, "item,icon");
   assert_eq(ret_obj, img);

   return 0;
}

int utc_efl_ext_eext_more_option_item_part_content_get_n(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Evas_Object *img;
   Evas_Object *ret_obj;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   img = elm_image_add(more_option);
   eext_more_option_item_part_content_set(item, "item,icon", img);
   ret_obj = eext_more_option_item_part_content_get(item, NULL);
   assert_eq(ret_obj, NULL);

   ret_obj = eext_more_option_item_part_content_get(NULL, NULL);
   assert_eq(ret_obj, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_opened_set_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eina_Bool opened;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   eext_more_option_opened_set(more_option, EINA_TRUE);
   opened = eext_more_option_opened_get(more_option);
   assert(opened);

   eext_more_option_opened_set(more_option, EINA_FALSE);
   opened = eext_more_option_opened_get(more_option);
   assert_eq(opened, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_more_option_opened_set_n(void)
{
   Evas_Object *win;

   win = _create_win("window");
   assert(win);

   eext_more_option_opened_set(NULL, EINA_TRUE);
   eext_more_option_opened_set(win, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_more_option_opened_get_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eina_Bool opened;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   opened = eext_more_option_opened_get(more_option);
   assert_eq(opened, EINA_FALSE);

   eext_more_option_opened_set(more_option, EINA_TRUE);
   opened = eext_more_option_opened_get(more_option);
   assert(opened);

   eext_more_option_opened_set(more_option, EINA_FALSE);
   opened = eext_more_option_opened_get(more_option);
   assert_eq(opened, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_more_option_opened_get_n(void)
{
   Evas_Object *win;
   Eina_Bool opened;

   win = _create_win("window");
   assert(win);

   opened = eext_more_option_opened_get(NULL);
   assert_eq(opened, EINA_FALSE);

   opened = eext_more_option_opened_get(win);
   assert_eq(opened, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_more_option_items_get_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   const Eina_List *list;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   list = eext_more_option_items_get(more_option);
   assert_eq(list, NULL);

   item = eext_more_option_item_append(more_option);
   assert(item);
   item = eext_more_option_item_append(more_option);
   assert(item);

   list = eext_more_option_items_get(more_option);
   assert(list);

   return 0;
}

int utc_efl_ext_eext_more_option_items_get_n(void)
{
   Evas_Object *win;
   const Eina_List *list;

   win = _create_win("window");
   assert(win);

   list = eext_more_option_items_get(NULL);
   assert_eq(list, NULL);
   list = eext_more_option_items_get(win);
   assert_eq(list, NULL);

   return 0;
}

int utc_efl_ext_eext_more_option_editing_enabled_get_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eina_Bool enabled;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   enabled = eext_more_option_editing_enabled_get(more_option);
   assert_eq(enabled, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_more_option_editing_enabled_get_n(void)
{
   Evas_Object *win;
   Eina_Bool enabled;

   win = _create_win("window");
   assert(win);

   enabled = eext_more_option_editing_enabled_get(NULL);
   assert_eq(enabled, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_more_option_editing_enabled_set_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eina_Bool enabled;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   enabled = eext_more_option_editing_enabled_get(more_option);
   assert_eq(enabled, EINA_FALSE);

   eext_more_option_editing_enabled_set(more_option, EINA_TRUE);
   enabled = eext_more_option_editing_enabled_get(more_option);
   assert_eq(enabled, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_more_option_editing_enabled_set_n(void)
{
   Evas_Object *win;
   Evas_Object *more_option;

   win = _create_win("window");
   assert(win);

   eext_more_option_editing_enabled_set(NULL, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_more_option_add_item_enabled_get_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eina_Bool enabled;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   enabled = eext_more_option_add_item_enabled_get(more_option);
   assert_eq(enabled, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_more_option_add_item_enabled_get_n(void)
{
   Evas_Object *win;
   Evas_Object *more_option;

   win = _create_win("window");
   assert(win);

   eext_more_option_add_item_enabled_set(NULL, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_more_option_add_item_enabled_set_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eina_Bool enabled;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   eext_more_option_add_item_enabled_set(more_option, EINA_TRUE);
   enabled = eext_more_option_add_item_enabled_get(more_option);
   assert_eq(enabled, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_more_option_add_item_enabled_set_n(void)
{
   Evas_Object *win;
   Evas_Object *more_option;

   win = _create_win("window");
   assert(win);

   eext_more_option_add_item_enabled_set(NULL, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_more_option_item_delete_enabled_get_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eina_Bool enabled;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   enabled = eext_more_option_add_item_enabled_get(item);
   assert_eq(enabled, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_more_option_item_delete_enabled_get_n(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eina_Bool enabled;

   win = _create_win("window");
   assert(win);

   enabled = eext_more_option_item_delete_enabled_get(NULL);
   assert_eq(enabled, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_more_option_item_delete_enabled_set_p(void)
{
   Evas_Object *win;
   Evas_Object *more_option;
   Eina_Bool enabled;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   more_option = eext_more_option_add(win);
   assert(more_option);

   item = eext_more_option_item_append(more_option);
   assert(item);

   eext_more_option_item_delete_enabled_set(item, EINA_TRUE);
   enabled = eext_more_option_item_delete_enabled_get(item);
   assert_eq(enabled, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_more_option_item_delete_enabled_set_n(void)
{
   Evas_Object *win;
   Evas_Object *more_option;

   win = _create_win("window");
   assert(win);

   eext_more_option_item_delete_enabled_set(NULL, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_circle_object_spinner_add_p(void)
{
   Evas_Object *win;
   Evas_Object *spinner;

   win = _create_win("window");
   assert(win);

   spinner = eext_circle_object_spinner_add(win, NULL);
   assert(spinner);

   return 0;
}

int utc_efl_ext_eext_circle_object_spinner_add_n(void)
{
   Evas_Object *spinner;

   spinner = eext_circle_object_spinner_add(NULL, NULL);
   assert_eq(spinner, NULL);

   return 0;
}

int utc_efl_ext_eext_circle_object_spinner_angle_set_p(void)
{
   Evas_Object *win;
   Evas_Object *spinner;

   win = _create_win("window");
   assert(win);

   spinner = eext_circle_object_spinner_add(win, NULL);
   assert(spinner);
   eext_circle_object_spinner_angle_set(spinner, 5.0);

   return 0;
}

int utc_efl_ext_eext_circle_object_spinner_angle_set_n(void)
{
   Evas_Object *win;
   Evas_Object *spinner;
   win = _create_win("window");
   assert(win);

   spinner = eext_circle_object_spinner_add(win, NULL);
   assert(spinner);

   eext_circle_object_spinner_angle_set(NULL, 5.0);
   return 0;
}

int utc_efl_ext_eext_rotary_selector_add_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_add_n(void)
{
   Evas_Object *rotary_selector;

   rotary_selector = eext_rotary_selector_add(NULL);
   assert_eq(rotary_selector, NULL);

   return 0;
}


int utc_efl_ext_eext_rotary_selector_item_append_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_append_n(void)
{
   Evas_Object *win;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   item = eext_rotary_selector_item_append(NULL);
   assert_eq(item, NULL);

   item = eext_rotary_selector_item_append(win);
   assert_eq(item, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_prepend_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_prepend(rotary_selector);
   assert(item);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_prepend_n(void)
{
   Evas_Object *win;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   item = eext_rotary_selector_item_prepend(NULL);
   assert_eq(item, NULL);

   item = eext_rotary_selector_item_prepend(win);
   assert_eq(item, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_insert_after_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   Eext_Object_Item *inserted_item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   inserted_item = eext_rotary_selector_item_insert_after(rotary_selector, item);
   assert(inserted_item);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_insert_after_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   Eext_Object_Item *inserted_item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   inserted_item = eext_rotary_selector_item_insert_after(NULL, item);
   assert_eq(inserted_item, NULL);

   inserted_item = eext_rotary_selector_item_insert_after(NULL, NULL);
   assert_eq(inserted_item, NULL);

   inserted_item = eext_rotary_selector_item_insert_after(win, item);
   assert_eq(inserted_item, NULL);

   inserted_item = eext_rotary_selector_item_insert_after(win, NULL);
   assert_eq(inserted_item, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_insert_before_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   Eext_Object_Item *inserted_item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   inserted_item = eext_rotary_selector_item_insert_before(rotary_selector, item);
   assert(inserted_item);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_insert_before_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   Eext_Object_Item *inserted_item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   inserted_item = eext_rotary_selector_item_insert_before(NULL, item);
   assert_eq(inserted_item, NULL);

   inserted_item = eext_rotary_selector_item_insert_before(NULL, NULL);
   assert_eq(inserted_item, NULL);

   inserted_item = eext_rotary_selector_item_insert_before(win, item);
   assert_eq(inserted_item, NULL);

   inserted_item = eext_rotary_selector_item_insert_before(win, NULL);
   assert_eq(inserted_item, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_del_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   Eina_List *items;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_item_del(item);
   items = eext_rotary_selector_items_get(rotary_selector);
   assert_eq(items, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_del_n(void)
{
   eext_rotary_selector_item_del(NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_items_clear_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   eext_rotary_selector_items_clear(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_items_clear(rotary_selector);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_part_text_set_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   const char *text;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_item_part_text_set(item, "selector,main_text", "selector,main_text test");
   text = eext_rotary_selector_item_part_text_get(item, "selector,main_text");
   assert(!strcmp(text, "selector,main_text test"));

   eext_rotary_selector_item_part_text_set(item, "selector,sub_text", "selector,sub_text test");
   text = eext_rotary_selector_item_part_text_get(item, "selector,sub_text");
   assert(!strcmp(text, "selector,sub_text test"));

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_part_text_set_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   const char *text;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_item_part_text_set(item, NULL, NULL);

   text = eext_rotary_selector_item_part_text_get(item, "selector,main_text");
   assert(!text || !strcmp(text, ""));

   eext_rotary_selector_item_part_text_set(NULL, NULL, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_part_text_get_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   const char *text;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_item_part_text_set(item, "selector,main_text", "selector,main_text test");
   text = eext_rotary_selector_item_part_text_get(item, "selector,main_text");
   assert(!strcmp(text, "selector,main_text test"));

   eext_rotary_selector_item_part_text_set(item, "selector,sub_text", "selector,sub_text test");
   text = eext_rotary_selector_item_part_text_get(item, "selector,sub_text");
   assert(!strcmp(text, "selector,sub_text test"));

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_part_text_get_n(void)
{
   const char *text;

   text = eext_rotary_selector_item_part_text_get(NULL, NULL);
   assert_eq(text, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_domain_translatable_part_text_set_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   const char *text;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_item_domain_translatable_part_text_set(item, "selector,main_text", "test", "selector,main_text test");
   text = eext_rotary_selector_item_part_text_get(item, "selector,main_text");
   assert(text);

   eext_rotary_selector_item_domain_translatable_part_text_set(item, "selector,sub_text", "test", "selector,sub_text test");
   text = eext_rotary_selector_item_part_text_get(item, "selector,sub_text");
   assert(text);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_domain_translatable_part_text_set_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_item_domain_translatable_part_text_set(item, NULL, NULL, NULL);
   eext_rotary_selector_item_domain_translatable_part_text_set(NULL, NULL, NULL, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_part_content_set_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Evas_Object *button;
   Evas_Object *ret_obj;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   button = elm_button_add(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_item_part_content_set(item, "item,icon", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, button);
   ret_obj = eext_rotary_selector_item_part_content_get(item, "item,icon", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL);
   assert_eq(ret_obj, button);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_part_content_set_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Evas_Object *button;
   Evas_Object *contents;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   button = elm_button_add(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_item_part_content_set(item, NULL, EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, button);
   contents = eext_rotary_selector_item_part_content_get(item, "item,icon", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL);
   assert_eq(contents, NULL);

   eext_rotary_selector_item_part_content_set(NULL, NULL, EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_part_content_get_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Evas_Object *button;
   Evas_Object *ret_obj;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   button = elm_button_add(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   ret_obj = eext_rotary_selector_item_part_content_get(item, "item,icon", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL);
   assert_eq(ret_obj, NULL);

   eext_rotary_selector_item_part_content_set(item, "item,icon", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, button);
   ret_obj = eext_rotary_selector_item_part_content_get(item, "item,icon", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL);
   assert_eq(ret_obj, button);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_part_content_get_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Evas_Object *button;
   Evas_Object *ret_obj;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   button = elm_button_add(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_item_part_content_set(item, NULL, EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, button);
   ret_obj = eext_rotary_selector_item_part_content_get(NULL, NULL, EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL);
   assert_eq(ret_obj, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_part_content_set_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Evas_Object *button;
   Evas_Object *ret_obj;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   button = elm_button_add(rotary_selector);

   eext_rotary_selector_part_content_set(rotary_selector, "selector,bg_image", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, button);
   ret_obj = eext_rotary_selector_part_content_get(rotary_selector, "selector,bg_image", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL);
   assert_eq(ret_obj, button);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_part_content_set_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Evas_Object *button;
   Evas_Object *contents;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   button = elm_button_add(rotary_selector);

   eext_rotary_selector_part_content_set(rotary_selector, NULL, EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, button);
   contents = eext_rotary_selector_part_content_get(rotary_selector, NULL, EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL);
   assert_eq(contents, NULL);

   eext_rotary_selector_part_content_set(NULL, NULL, EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_part_content_get_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Evas_Object *button;
   Evas_Object *ret_obj;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   button = elm_button_add(rotary_selector);

   eext_rotary_selector_part_content_set(rotary_selector, "selector,bg_image", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, button);
   ret_obj = eext_rotary_selector_part_content_get(rotary_selector, "selector,bg_image", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL);
   assert_eq(ret_obj, button);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_part_content_get_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Evas_Object *button;
   Evas_Object *ret_obj;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   button = elm_button_add(rotary_selector);

   eext_rotary_selector_part_content_set(rotary_selector, NULL, EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, button);
   ret_obj = eext_rotary_selector_part_content_get(NULL, NULL, EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL);
   assert_eq(ret_obj, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_part_color_get_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   int r, g, b, a;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);


   eext_rotary_selector_item_part_color_set(item, "item,icon", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, 255, 255, 255, 255);
   eext_rotary_selector_item_part_color_get(item, "item,icon", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, &r, &g, &b, &a);

   assert_eq(r, 255);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_part_color_get_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_item_part_color_get(item, NULL, EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, NULL, NULL, NULL, NULL);
   eext_rotary_selector_item_part_color_get(NULL, NULL, EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, NULL, NULL, NULL, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_part_color_set_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   int r, g, b, a;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);


   eext_rotary_selector_item_part_color_set(item, "item,icon", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, 255, 255, 255, 255);
   eext_rotary_selector_item_part_color_get(item, "item,icon", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, &r, &g, &b, &a);

   assert_eq(r, 255);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_part_color_set_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_item_part_color_set(item, NULL, EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, NULL, NULL, NULL, NULL);
   eext_rotary_selector_item_part_color_set(NULL, NULL, EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, NULL, NULL, NULL, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_part_color_get_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   int r, g, b, a;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   eext_rotary_selector_part_color_set(rotary_selector, "item,icon", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, 255, 255, 255, 255);
   eext_rotary_selector_part_color_get(rotary_selector, "item,icon", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, &r, &g, &b, &a);

   assert_eq(r, 255);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_part_color_get_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   eext_rotary_selector_part_color_get(rotary_selector, NULL, EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, NULL, NULL, NULL, NULL);
   eext_rotary_selector_part_color_get(NULL, NULL, EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, NULL, NULL, NULL, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_part_color_set_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   int r, g, b, a;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   eext_rotary_selector_part_color_set(rotary_selector, "item,icon", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, 255, 255, 255, 255);
   eext_rotary_selector_part_color_get(rotary_selector, "item,icon", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, &r, &g, &b, &a);

   assert_eq(r, 255);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_part_color_set_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   eext_rotary_selector_part_color_set(rotary_selector, NULL, EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, NULL, NULL, NULL, NULL);
   eext_rotary_selector_part_color_set(NULL, NULL, EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, NULL, NULL, NULL, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_selected_item_set_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   Eext_Object_Item *ret_item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_selected_item_set(rotary_selector, item);
   ret_item = eext_rotary_selector_selected_item_get(rotary_selector);
   assert_eq(item, ret_item);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_selected_item_set_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   eext_rotary_selector_selected_item_set(rotary_selector, NULL);
   item = eext_rotary_selector_selected_item_get(rotary_selector);
   assert_eq(item, NULL);
   eext_rotary_selector_selected_item_set(NULL, NULL);

   return 0;
}


int utc_efl_ext_eext_rotary_selector_selected_item_get_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   Eext_Object_Item *ret_item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_selected_item_set(rotary_selector, item);
   ret_item = eext_rotary_selector_selected_item_get(rotary_selector);
   assert_eq(item, ret_item);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_selected_item_get_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_selected_item_get(rotary_selector);
   assert_eq(item, NULL);
   item = eext_rotary_selector_selected_item_get(NULL);
   assert_eq(item, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_items_get_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eext_Object_Item *item;
   Eina_List *ret_item_list;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   ret_item_list = eext_rotary_selector_items_get(rotary_selector);
   assert(ret_item_list);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_items_get_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eina_List *ret_item_list;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   ret_item_list = eext_rotary_selector_items_get(NULL);
   assert_eq(ret_item_list, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_editing_enabled_get_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eina_Bool enabled;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   enabled = eext_rotary_selector_editing_enabled_get(rotary_selector);
   assert_eq(enabled, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_editing_enabled_get_n(void)
{
   Evas_Object *win;
   Eina_Bool enabled;

   win = _create_win("window");
   assert(win);

   enabled = eext_rotary_selector_editing_enabled_get(NULL);
   assert_eq(enabled, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_editing_enabled_set_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eina_Bool enabled;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   enabled = eext_rotary_selector_editing_enabled_get(rotary_selector);
   assert_eq(enabled, EINA_FALSE);

   eext_rotary_selector_editing_enabled_set(rotary_selector, EINA_TRUE);
   enabled = eext_rotary_selector_editing_enabled_get(rotary_selector);
   assert_eq(enabled, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_editing_enabled_set_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;

   win = _create_win("window");
   assert(win);

   eext_rotary_selector_editing_enabled_set(NULL, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_add_item_enabled_get_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eina_Bool enabled;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   enabled = eext_rotary_selector_add_item_enabled_get(rotary_selector);
   assert_eq(enabled, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_add_item_enabled_get_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;

   win = _create_win("window");
   assert(win);

   eext_rotary_selector_add_item_enabled_set(NULL, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_add_item_enabled_set_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eina_Bool enabled;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   eext_rotary_selector_add_item_enabled_set(rotary_selector, EINA_TRUE);
   enabled = eext_rotary_selector_add_item_enabled_get(rotary_selector);
   assert_eq(enabled, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_add_item_enabled_set_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;

   win = _create_win("window");
   assert(win);

   eext_rotary_selector_add_item_enabled_set(NULL, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_delete_enabled_get_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eina_Bool enabled;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   enabled = eext_rotary_selector_add_item_enabled_get(item);
   assert_eq(enabled, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_delete_enabled_get_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eina_Bool enabled;

   win = _create_win("window");
   assert(win);

   enabled = eext_rotary_selector_item_delete_enabled_get(NULL);
   assert_eq(enabled, EINA_FALSE);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_delete_enabled_set_p(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;
   Eina_Bool enabled;
   Eext_Object_Item *item;

   win = _create_win("window");
   assert(win);

   rotary_selector = eext_rotary_selector_add(win);
   assert(rotary_selector);

   item = eext_rotary_selector_item_append(rotary_selector);
   assert(item);

   eext_rotary_selector_item_delete_enabled_set(item, EINA_TRUE);
   enabled = eext_rotary_selector_item_delete_enabled_get(item);
   assert_eq(enabled, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_rotary_selector_item_delete_enabled_set_n(void)
{
   Evas_Object *win;
   Evas_Object *rotary_selector;

   win = _create_win("window");
   assert(win);

   eext_rotary_selector_item_delete_enabled_set(NULL, EINA_TRUE);

   return 0;
}

int utc_efl_ext_eext_panel_add_p(void)
{
   Evas_Object *win;
   Evas_Object *panel;

   win = _create_win("window");
   assert(win);

   panel = eext_panel_add(win);
   assert(panel);

   return 0;
}

int utc_efl_ext_eext_panel_add_n(void)
{
   Evas_Object *panel;

   panel = eext_panel_add(NULL);
   assert_eq(panel, NULL);

   return 0;
}

int utc_efl_ext_eext_panel_part_content_set_p(void)
{
   Evas_Object *win;
   Evas_Object *panel;
   Evas_Object *button;
   Evas_Object *ret_obj;

   win = _create_win("window");
   assert(win);

   panel = eext_panel_add(win);
   assert(panel);

   button = elm_button_add(panel);

   eext_panel_part_content_set(panel, "primary", button);
   ret_obj = eext_panel_part_content_get(panel, "primary");
   assert_eq(ret_obj, button);

   return 0;
}

int utc_efl_ext_eext_panel_part_content_set_n(void)
{
   Evas_Object *win;
   Evas_Object *panel;
   Evas_Object *button;
   Evas_Object *contents;

   win = _create_win("window");
   assert(win);

   panel = eext_panel_add(win);
   assert(panel);

   button = elm_button_add(panel);

   eext_panel_part_content_set(panel, NULL, button);
   contents = eext_panel_part_content_get(panel, NULL);
   assert_eq(contents, NULL);

   eext_panel_part_content_set(NULL, NULL, NULL);

   return 0;
}

int utc_efl_ext_eext_panel_part_content_get_p(void)
{
   Evas_Object *win;
   Evas_Object *panel;
   Evas_Object *button;
   Evas_Object *ret_obj;

   win = _create_win("window");
   assert(win);

   panel = eext_panel_add(win);
   assert(panel);

   button = elm_button_add(panel);

   eext_panel_part_content_set(panel, "primary", button);
   ret_obj = eext_panel_part_content_get(panel, "primary");
   assert_eq(ret_obj, button);

   return 0;
}

int utc_efl_ext_eext_panel_part_content_get_n(void)
{
   Evas_Object *win;
   Evas_Object *panel;
   Evas_Object *button;
   Evas_Object *ret_obj;

   win = _create_win("window");
   assert(win);

   panel = eext_panel_add(win);
   assert(panel);

   button = elm_button_add(panel);

   eext_panel_part_content_set(panel, NULL, button);
   ret_obj = eext_panel_part_content_get(NULL, NULL);
   assert_eq(ret_obj, NULL);

   return 0;
}

int utc_efl_ext_eext_rotary_event_activated_object_get_p(void)
{
   Evas_Object *win;
   Evas_Object *circle_slider;

   win = _create_win("window");
   assert(win);

   circle_slider = eext_circle_object_slider_add(win, NULL);
   eext_rotary_object_event_activated_set(circle_slider, EINA_TRUE);
   Evas_Object *activate_obj = eext_rotary_event_activated_object_get();

   assert_eq(activate_obj, circle_slider);

   return 0;
}

int utc_efl_ext_eext_rotary_event_activated_object_get_n(void)
{
   Evas_Object *win;
   Evas_Object *circle_slider;

   win = _create_win("window");
   assert(win);

   circle_slider = eext_circle_object_slider_add(win, NULL);
   eext_rotary_object_event_activated_set(circle_slider, EINA_TRUE);
   eext_rotary_object_event_activated_set(circle_slider, EINA_FALSE);
   Evas_Object *activate_obj = eext_rotary_event_activated_object_get();

   assert_eq(activate_obj, NULL);

   return 0;
}

int utc_efl_ext_eext_popup_add_p(void)
{
   Evas_Object *win;
   Evas_Object *popup;

   win = _create_win("window");
   assert(win);

   popup = eext_popup_add(win);
   assert(popup);

   return 0;
}

int utc_efl_ext_eext_popup_add_n(void)
{
   Evas_Object *win;
   Evas_Object *popup;

   popup = eext_popup_add(NULL);
   assert_eq(popup, NULL);

   return 0;
}

#endif
