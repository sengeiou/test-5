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
#include <ui_viewmanager.h>
#include <dlog.h>

static bool view_load_cb(ui_view* view, void *user_data)
{
   return true;
}

static bool view2_load_cb(ui_view* view, void *user_data)
{
	Eo* base = ui_view_get_base(view);
	assert(base);

	Elm_Button* btn = elm_button_add(base);
	ui_view_set_content(view, btn);

   return true;
}

void utc_ui_viewmgr_startup(void)
{
}

void utc_ui_viewmgr_cleanup(void)
{
}

/**
 * @testcase        utc_ui_viewmgr_push_view_p
 * @since_tizen     3.0
 * @description     To add new view in the viewmgr's viewmgr
 * @scenario        View is created
 *                  Add view in the viewmgr
 */
int utc_ui_viewmgr_push_view_p(void)
{
	ui_view *view1, *view2;

	view1 = ui_view_create("Page1");
	assert(view1);
	ui_view_set_transition_style(view1, "none");

	ui_viewmgr_push_view(view1);

	view2 = ui_view_create("Page2");
	assert(view2);

	ui_viewmgr_push_view(view2);

	assert_eq(view2, ui_viewmgr_get_last_view());

	ui_view_destroy(view1);
	ui_view_destroy(view2);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_push_view_n
 * @since_tizen     3.0
 * @description     To add new view in the viewmgr's viewmgr
 * @scenario        Try to add invalid view in the viewmgr
 */
int utc_ui_viewmgr_push_view_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_viewmgr_push_view(view), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_insert_view_before_p
 * @since_tizen     3.0
 * @description     To add new view in the viewmgr's viewmgr before specific view
 * @scenario        View is created
 *                  Add view in the viewmgr before specific view
 */
int utc_ui_viewmgr_insert_view_before_p(void)
{
	ui_view *view1, *view2, *view3;

	view1 = ui_view_create("Page1");
	assert(view1);
	ui_view_set_transition_style(view1, "none");

	ui_viewmgr_push_view(view1);

	view2 = ui_view_create("Page2");
	assert(view2);
	ui_view_set_transition_style(view2, "none");

	assert_eq(ui_viewmgr_insert_view_before(view2, view1), UI_VIEWMGR_ERROR_NONE);

	view3 = ui_view_create("Page3");
	assert(view3);
	ui_view_set_transition_style(view3, "none");

	assert_eq(ui_viewmgr_insert_view_before(view3, NULL), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view1);
	ui_view_destroy(view2);
	ui_view_destroy(view3);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_insert_view_before_n
 * @since_tizen     3.0
 * @description     To add new view in the viewmgr's viewmgr before specific view
 * @scenario        Try to add invalid view in the viewmgr
 */
int utc_ui_viewmgr_insert_view_before_n(void)
{
	ui_view *view1, *view2 = NULL;

	view1 = ui_view_create("Page1");
	assert(view1);
	ui_view_set_transition_style(view1, "none");

	ui_viewmgr_push_view(view1);

	assert_eq(ui_viewmgr_insert_view_before(view2, view1), UI_VIEWMGR_ERROR_INVALID_PARAMETER);
	assert_eq(ui_viewmgr_insert_view_before(view1, view1), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	ui_view_destroy(view1);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_insert_view_after_p
 * @since_tizen     3.0
 * @description     To add new view in the viewmgr's viewmgr after specific view
 * @scenario        View is created
 *                  Add view in the viewmgr after specific view
 */
int utc_ui_viewmgr_insert_view_after_p(void)
{
	ui_view *view1, *view2, *view3, *view4;

	view1 = ui_view_create("Page1");
	assert(view1);
	ui_view_set_transition_style(view1, "none");

	ui_viewmgr_push_view(view1);

	view2 = ui_view_create("Page2");
	assert(view2);
	ui_view_set_transition_style(view2, "none");

	assert_eq(ui_viewmgr_insert_view_after(view2, view1), UI_VIEWMGR_ERROR_NONE);

	view3 = ui_view_create("Page3");
	assert(view3);
	ui_view_set_transition_style(view3, "none");

	assert_eq(ui_viewmgr_insert_view_after(view3, NULL), UI_VIEWMGR_ERROR_NONE);

	view4 = ui_view_create("Page4");
	assert(view4);
	ui_view_set_transition_style(view4, "none");

	assert_eq(ui_viewmgr_insert_view_after(view4, view1), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view1);
	ui_view_destroy(view2);
	ui_view_destroy(view3);
	ui_view_destroy(view4);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_insert_view_after_n
 * @since_tizen     3.0
 * @description     To add new view in the viewmgr's viewmgr after specific view
 * @scenario        Try to add invalid view in the viewmgr
 */
int utc_ui_viewmgr_insert_view_after_n(void)
{
	ui_view *view1, *view2 = NULL;

	view1 = ui_view_create("Page1");
	assert(view1);
	ui_view_set_transition_style(view1, "none");

	ui_viewmgr_push_view(view1);

	assert_eq(ui_viewmgr_insert_view_after(view2, view1), UI_VIEWMGR_ERROR_INVALID_PARAMETER);
	assert_eq(ui_viewmgr_insert_view_after(view1, view1), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	ui_view_destroy(view1);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_pop_view_p
 * @since_tizen     3.0
 * @description     To remove view in the viewmgr
 * @scenario        Push 3 views and Pop 3 views
 *                  Check view count
 */
int utc_ui_viewmgr_pop_view_p(void)
{
	ui_view* before = ui_viewmgr_get_last_view();
	int i;

	for (i = 0; i < 3; i++) {
		ui_view* view = ui_view_create(NULL);
		assert(view);
		ui_view_set_transition_style(view, "none");
		ui_viewmgr_push_view(view);
	}

	for (i = 0; i < 3; i++) {
		assert_eq(ui_viewmgr_pop_view(), UI_VIEWMGR_ERROR_NONE);
	}

	assert_eq(before, ui_viewmgr_get_last_view());

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_pop_view_n
 * @since_tizen     3.0
 * @description     To remove view in the viewmgr
 * @scenario        Pop view if the view is already on popping.
 */
int utc_ui_viewmgr_pop_view_n(void)
{
	ui_view* view = ui_view_create("Page1");
	assert(view);
	ui_view_set_transition_style(view, "none");
	ui_viewmgr_push_view(view);
	ui_view_set_transition_style(view, "default");

	ui_viewmgr_pop_view();

	assert_eq(ui_viewmgr_pop_view(), UI_VIEWMGR_ERROR_ALREADY_IN_PROGRESS);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_activate_p
 * @since_tizen     3.0
 * @description     Activate viewmgr
 * @scenario        Activate viewmgr multiple times.
 */
int utc_ui_viewmgr_activate_p(void)
{
	ui_viewmgr_deactivate();
	assert_eq(ui_viewmgr_activate(), UI_VIEWMGR_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_activate_n
 * @since_tizen     3.0
 * @description     Activate viewmgr
 * @scenario        Activate viewmgr multiple times.
 */
int utc_ui_viewmgr_activate_n(void)
{
	ui_viewmgr_activate();
	assert_eq(ui_viewmgr_activate(), UI_VIEWMGR_ERROR_ALREADY_IN_PROGRESS);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_deactivate_p
 * @since_tizen     3.0
 * @description     Deactivate viewmgr
 * @scenario        Deactivate viewmgr multiple times.
 */
int utc_ui_viewmgr_deactivate_p(void)
{
	ui_viewmgr_activate();
	assert_eq(ui_viewmgr_deactivate(), UI_VIEWMGR_ERROR_NONE);

	ui_viewmgr_activate();

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_deactivate_n
 * @since_tizen     3.0
 * @description     Deactivate viewmgr
 * @scenario        Deactivate viewmgr multiple times.
 */
int utc_ui_viewmgr_deactivate_n(void)
{
	ui_viewmgr_deactivate();
	assert_eq(ui_viewmgr_deactivate(), UI_VIEWMGR_ERROR_ALREADY_IN_PROGRESS);

	ui_viewmgr_activate();

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_get_window_p
 * @since_tizen     3.0
 * @description     Get window object
 * @scenario        Try to get window object
 */
int utc_ui_viewmgr_get_window_p(void)
{
	Elm_Win *win;

	win = ui_viewmgr_get_window();
	assert(win);

	assert_eq(strcmp(evas_object_type_get(win), "elm_win"), 0);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_get_last_view_p
 * @since_tizen     3.0
 * @description     Get last view
 * @scenario        Create a view
 *                  Add view in the viewmgr
 *                  Get last view and check the return value
 */
int utc_ui_viewmgr_get_last_view_p(void)
{
	ui_view *view, *view2;

	view = ui_view_create("page1");
	assert(view);
	ui_view_set_transition_style(view, "none");

	ui_viewmgr_push_view(view);

	view2 = ui_view_create("page2");
	assert(view2);
	ui_view_set_transition_style(view2, "none");

	ui_viewmgr_push_view(view2);

	assert_eq(view2, ui_viewmgr_get_last_view());

	ui_view_destroy(view);
	ui_view_destroy(view2);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_get_last_view_n
 * @since_tizen     3.0
 * @description     Get last view
 * @scenario        Create a view
 *                  Add view in the viewmgr
 */
int utc_ui_viewmgr_get_last_view_n(void)
{
	ui_view *view;

	view = ui_view_create("page1");
	assert(view);
	ui_view_set_transition_style(view, "none");

	ui_viewmgr_push_view(view);

	ui_viewmgr_push_view(NULL);

	assert_eq(view, ui_viewmgr_get_last_view());

	ui_view_destroy(view);

	assert_neq(view, ui_viewmgr_get_last_view());

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_get_view_by_idx_p
 * @since_tizen     3.0
 * @description     Get specific view using view index
 * @scenario        Create view
 *                  Add view in ther viewmgr
 *                  Get view by index and compare
 */
int utc_ui_viewmgr_get_view_by_idx_p(void)
{
	ui_view *view, *view2, *view3, *view4 = NULL;

	view = ui_view_create("page1");
	assert(view);
	ui_view_set_transition_style(view, "none");

	ui_viewmgr_push_view(view);

	view2 = ui_view_create("page2");
	assert(view2);
	ui_view_set_transition_style(view2, "none");

	ui_viewmgr_push_view(view2);

	view3 = ui_view_create("page3");
	assert(view3);
	ui_view_set_transition_style(view3, "none");

	ui_viewmgr_push_view(view3);

	ui_viewmgr_push_view(view4);

	assert_eq(view2, ui_viewmgr_get_view_by_idx(2));

	ui_view_destroy(view);
	ui_view_destroy(view2);
	ui_view_destroy(view3);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_get_view_by_idx_n
 * @since_tizen     3.0
 * @description     Get specific view using view index
 * @scenario        Try to get specific view with invalid index
 */
int utc_ui_viewmgr_get_view_by_idx_n(void)
{
	ui_view *view, *view2, *view3, *view4 = NULL;

	view = ui_view_create("page1");
	assert(view);
	ui_view_set_transition_style(view, "none");

	ui_viewmgr_push_view(view);

	view2 = ui_view_create("page2");
	assert(view2);
	ui_view_set_transition_style(view2, "none");

	ui_viewmgr_push_view(view2);

	view3 = ui_view_create("page3");
	assert(view3);
	ui_view_set_transition_style(view3, "none");

	ui_viewmgr_push_view(view3);

	ui_viewmgr_push_view(view4);

	assert_eq(NULL, ui_viewmgr_get_view_by_idx(10));

	ui_view_destroy(view);
	ui_view_destroy(view2);
	ui_view_destroy(view3);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_get_view_by_name_p
 * @since_tizen     3.0
 * @description     Get specific view using view name
 * @scenario        Create view
 *                  Add view in ther viewmgr
 *                  Get view by name and compare
 */
int utc_ui_viewmgr_get_view_by_name_p(void)
{
	ui_view *view, *view2, *view3, *view4 = NULL;

	view = ui_view_create("page1");
	assert(view);
	ui_view_set_transition_style(view, "none");

	ui_viewmgr_push_view(view);

	view2 = ui_view_create("page2");
	assert(view2);
	ui_view_set_transition_style(view2, "none");

	ui_viewmgr_push_view(view2);

	view3 = ui_view_create("page3");
	assert(view3);
	ui_view_set_transition_style(view3, "none");

	ui_viewmgr_push_view(view3);

	ui_viewmgr_push_view(view4);

	assert_eq(view3, ui_viewmgr_get_view_by_name("page3"));

	ui_view_destroy(view);
	ui_view_destroy(view2);
	ui_view_destroy(view3);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_get_view_by_name_n
 * @since_tizen     3.0
 * @description     Get specific view using view name
 * @scenario        Try to get specific view with invalid name
 */
int utc_ui_viewmgr_get_view_by_name_n(void)
{
	ui_view *view, *view2, *view3, *view4 = NULL;

	view = ui_view_create("page1");
	assert(view);
	ui_view_set_transition_style(view, "none");

	ui_viewmgr_push_view(view);

	view2 = ui_view_create("page2");
	assert(view2);
	ui_view_set_transition_style(view2, "none");

	ui_viewmgr_push_view(view2);

	view3 = ui_view_create("page3");
	assert(view3);
	ui_view_set_transition_style(view3, "none");

	ui_viewmgr_push_view(view3);

	ui_viewmgr_push_view(view4);

	assert_eq(NULL, ui_viewmgr_get_view_by_name("page4"));

	ui_viewmgr_get_view_by_name(NULL);
	assert_eq(get_last_result(), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	ui_view_destroy(view);
	ui_view_destroy(view2);
	ui_view_destroy(view3);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_get_base_p
 * @since_tizen     3.0
 * @description     Get viewmgr's base object
 * @scenario        Try to get base object of viewmgr
 */
int utc_ui_viewmgr_get_base_p(void)
{
	Evas_Object *base;

	base = ui_viewmgr_get_base();
	assert(base);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_get_view_index_p
 * @since_tizen     3.0
 * @description     Get index of view
 * @scenario        Create view
 *                  Add view in the viewmgr
 *                  Get index and compare
 */
int utc_ui_viewmgr_get_view_index_p(void)
{
	ui_view *view, *view2, *view3;

	view = ui_view_create("page1");
	assert(view);
	ui_view_set_transition_style(view, "none");

	ui_viewmgr_push_view(view);

	view2 = ui_view_create("page2");
	assert(view2);
	ui_view_set_transition_style(view2, "none");

	ui_viewmgr_push_view(view2);

	view3 = ui_view_create("page3");
	assert(view3);
	ui_view_set_transition_style(view3, "none");

	ui_viewmgr_push_view(view3);

	assert_eq(1, ui_viewmgr_get_view_index(view));
	assert_eq(2, ui_viewmgr_get_view_index(view2));
	assert_eq(3, ui_viewmgr_get_view_index(view3));

	ui_view_destroy(view);
	ui_view_destroy(view2);
	ui_view_destroy(view3);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_get_view_index_n
 * @since_tizen     3.0
 * @description     Get index of view
 * @scenario        Try to get index of invalid view
 */
int utc_ui_viewmgr_get_view_index_n(void)
{
	ui_view *view = NULL;

	assert_eq(UI_VIEWMGR_ERROR_INVALID_PARAMETER, ui_viewmgr_get_view_index(view));

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_get_view_count_p
 * @since_tizen     3.0
 * @description     Get view count
 * @scenario        Create view
 *                  Add view in the viewmgr
 *                  Get amount number of view and compare
 */
int utc_ui_viewmgr_get_view_count_p(void)
{
	int before = ui_viewmgr_get_view_count();

	ui_view *view;

	view = ui_view_create("page1");
	assert(view);
	ui_view_set_transition_style(view, "none");

	ui_viewmgr_push_view(view);

	assert_eq((before + 1), ui_viewmgr_get_view_count());

	ui_view_destroy(view);

	assert_eq(before, ui_viewmgr_get_view_count());

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_get_view_count_n
 * @since_tizen     3.0
 * @description     Get view count
 * @scenario        Push an invalid view
 *                  Check amount number of view and compare
 */
int utc_ui_viewmgr_get_view_count_n(void)
{
	int before = ui_viewmgr_get_view_count();

	ui_view *view = NULL;

	ui_viewmgr_push_view(view);

	assert_eq(before, ui_viewmgr_get_view_count());

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_create_p
 * @since_tizen     3.0
 * @description     Create a view
 * @scenario        Create a new view
 *                  Compare view name
 */
int utc_ui_viewmgr_view_create_p(void)
{
	ui_view *view, *view2;

	view = ui_view_create("@#!%!@#@");
	assert(view);

	assert_neq(view, NULL);

	ui_view_destroy(view);

	view2 = ui_view_create(NULL);
	assert(view2);

	assert_neq(view2, NULL);

	ui_view_destroy(view2);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_set_content_p
 * @since_tizen     3.0
 * @description     Set view's content
 * @scenario        Create view, content
 *                  Set content of view
 *                  Get content of view
 *                  Compare contents
 */
int utc_ui_viewmgr_view_set_content_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	Eo* base = ui_view_get_base(view);
	assert(base);

	assert_eq(ui_view_set_content(view, NULL), UI_VIEWMGR_ERROR_NONE);

	Elm_Button* btn = elm_button_add(base);
	assert(btn);

	assert_eq(ui_view_set_content(view, btn), UI_VIEWMGR_ERROR_NONE);

	assert_eq(ui_view_set_content(view, NULL), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_set_content_n
 * @since_tizen     3.0
 * @description     Set view's content
 * @scenario        Create a view
 *                  Set invalid content to view
 */
int utc_ui_viewmgr_view_set_content_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_view_set_content(view, NULL), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_content_p
 * @since_tizen     3.0
 * @description     Get view's content
 * @scenario        Create view, content
 *                  Set content of view
 *                  Get content of view
 *                  Compare contents
 */
int utc_ui_viewmgr_view_get_content_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	Eo* base = ui_view_get_base(view);
	assert(base);

	assert_eq(ui_view_get_content(view), NULL);

	Elm_Button* btn = elm_button_add(base);
	assert(btn);

	ui_view_set_content(view, btn);

	assert_eq(ui_view_get_content(view), btn);

	ui_view_set_content(view, btn);

	assert_eq(ui_view_get_content(view), btn);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_content_n
 * @since_tizen     3.0
 * @description     Get view's content
 * @scenario        Create a view
 *                  Get a view's content
 */
int utc_ui_viewmgr_view_get_content_n(void)
{
	ui_view* view = NULL;

	assert_eq(NULL, ui_view_get_content(view));

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_unset_content_p
 * @since_tizen     3.0
 * @description     Unset view's content
 * @scenario        Create view, content
 *                  Set content of view
 *                  Unset content of view
 */
int utc_ui_viewmgr_view_unset_content_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	Eo* base = ui_view_get_base(view);
	assert(base);

	assert_eq(NULL, ui_view_unset_content(view));

	Elm_Button* btn = elm_button_add(base);
	assert(btn);

	ui_view_set_content(view, btn);

	assert_eq(btn, ui_view_unset_content(view));
	assert_eq(NULL, ui_view_unset_content(view));

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_unset_content_n
 * @since_tizen     3.0
 * @description     Unset view's content
 * @scenario        Create a view
 *                  Unset a view's content
 */
int utc_ui_viewmgr_view_unset_content_n(void)
{
	ui_view* view = NULL;

	assert_eq(NULL, ui_view_unset_content(view));

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_set_event_cb_p
 * @since_tizen     3.0
 * @description     Set view event callbacks
 * @scenario        Create view
 *                  Set events of view
 */
int utc_ui_viewmgr_view_set_event_cb_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	assert_eq(ui_view_set_event_cb(view, UI_VIEW_EVENT_LOAD, view_load_cb, NULL), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_view_set_event_cb(view, UI_VIEW_EVENT_LOAD, NULL, NULL), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_set_event_cb_n
 * @since_tizen     3.0
 * @description     Unset view's content
 * @scenario        Create view
 *                  Set events with invalid params
 */
int utc_ui_viewmgr_view_set_event_cb_n(void)
{
	ui_view* view = NULL;

	assert_eq(ui_view_set_event_cb(view, -1, view_load_cb, NULL), UI_VIEWMGR_ERROR_INVALID_PARAMETER);
	assert_eq(ui_view_set_event_cb(view, -1, NULL, NULL), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	view = ui_view_create("page1");
	assert(view);

	assert_eq(ui_view_set_event_cb(view, -1, view_load_cb, NULL), UI_VIEWMGR_ERROR_INVALID_PARAMETER);
	assert_eq(ui_view_set_event_cb(view, -1, NULL, NULL), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_base_p
 * @since_tizen     3.0
 * @description     Get base object of view
 * @scenario        Try to get base object of view
 */
int utc_ui_viewmgr_view_get_base_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	assert_neq(ui_view_get_base(view), NULL);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_base_n
 * @since_tizen     3.0
 * @description     Get base object of view
 * @scenario        Try to get base object of invalid view.
 */
int utc_ui_viewmgr_view_get_base_n(void)
{
	ui_view* view = NULL;

	assert_eq(ui_view_get_base(view), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_set_indicator_p
 * @since_tizen     3.0
 * @description     Set indicator property
 * @scenario        Create view
 *                  Set indicator property of view
 */
int utc_ui_viewmgr_view_set_indicator_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	ui_viewmgr_push_view(view);

	assert_eq(ui_view_set_indicator(view, UI_VIEW_INDICATOR_HIDE), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_view_set_indicator(view, UI_VIEW_INDICATOR_DEFAULT), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_view_set_indicator(view, UI_VIEW_INDICATOR_OPTIMAL), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_view_set_indicator(view, UI_VIEW_INDICATOR_OVERLAP), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_view_set_indicator(view, UI_VIEW_INDICATOR_SHOW), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_set_indicator_n
 * @since_tizen     3.0
 * @description     Set indicator property
 * @scenario        Create view
 *                  Set indicator property of view
 *                  Get indicator property of view
 *                  Compare
 */
int utc_ui_viewmgr_view_set_indicator_n(void)
{
	ui_view* view = NULL;

	assert_eq(ui_view_set_indicator(view, UI_VIEW_INDICATOR_OVERLAP), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	view = ui_view_create("page1");
	assert(view);

	assert_eq(ui_view_set_indicator(view, UI_VIEW_INDICATOR_UNKNOWN), UI_VIEWMGR_ERROR_INVALID_PARAMETER);
	assert_eq(ui_view_set_indicator(view, -1), UI_VIEWMGR_ERROR_INVALID_PARAMETER);
	assert_eq(ui_view_set_indicator(view, UI_VIEW_INDICATOR_OVERLAP), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_indicator_p
 * @since_tizen     3.0
 * @description     Get indicator property
 * @scenario        Create view
 *                  Set indicator property of view
 *                  Get indicator property
 */
int utc_ui_viewmgr_view_get_indicator_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	assert_eq(ui_view_get_indicator(view), UI_VIEW_INDICATOR_DEFAULT);

	ui_view_set_indicator(view, UI_VIEW_INDICATOR_HIDE);
	assert_eq(ui_view_get_indicator(view), UI_VIEW_INDICATOR_HIDE);

	ui_view_set_indicator(view, UI_VIEW_INDICATOR_SHOW);
	assert_eq(ui_view_get_indicator(view), UI_VIEW_INDICATOR_SHOW);

	ui_view_set_indicator(view, UI_VIEW_INDICATOR_DEFAULT);
	assert_eq(ui_view_get_indicator(view), UI_VIEW_INDICATOR_DEFAULT);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_indicator_n
 * @since_tizen     3.0
 * @description     Get indicator property
 * @scenario        Try to get indicator property with invalid param
 */
int utc_ui_viewmgr_view_get_indicator_n(void)
{
	ui_view* view = NULL;

	assert_eq(ui_view_get_indicator(view), UI_VIEW_INDICATOR_UNKNOWN);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_set_available_rotations_p
 * @since_tizen     3.0
 * @description     Set rotations degree that viewmgr can be rotate
 * @scenario        Create view
 *                  Set rotations degree
 */
int utc_ui_viewmgr_view_set_available_rotations_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	int rot[4] = { 0, 90, 180, 270 };
	assert_eq(ui_view_set_available_rotations(view, rot, 4), UI_VIEWMGR_ERROR_NONE);

	int rot2[6] = { 0, -45, 90, -125, 180, 270 };
	assert_eq(ui_view_set_available_rotations(view, rot2, 6), UI_VIEWMGR_ERROR_NONE);

	int rot3[1] = { 0 };
	assert_eq(ui_view_set_available_rotations(view, rot3, 1), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_set_available_rotations_n
 * @since_tizen     3.0
 * @description     Set rotations degree that viewmgr can be rotate
 * @scenario        Try to set rotations degree with invalid param
 */
int utc_ui_viewmgr_view_set_available_rotations_n(void)
{
	ui_view* view = NULL;

	int rot[4] = { 0, 90, 180, 270 };
	assert_eq(ui_view_set_available_rotations(view, rot, 4), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	view = ui_view_create("page1");
	assert(view);

	assert_eq(ui_view_set_available_rotations(view, NULL, 4), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	assert_eq(ui_view_set_available_rotations(view, rot, 0), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_available_rotations_p
 * @since_tizen     3.0
 * @description     Get rotations degree that viewmgr can be rotate
 * @scenario        Create view
 *                  Set rotations degree
 *                  Get rotations degree
 *                  Compare
 */
int utc_ui_viewmgr_view_get_available_rotations_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	int rot[4] = { 0, 90, 180, 270 };
	ui_view_set_available_rotations(view, rot, 4);

	unsigned int count;
	const int* rot2 = ui_view_get_available_rotations(view, &count);

	assert_eq(count, 4);
	assert_eq(rot2[0], 0);
	assert_eq(rot2[1], 90);
	assert_eq(rot2[2], 180);
	assert_eq(rot2[3], 270);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_available_rotations_n
 * @since_tizen     3.0
 * @description     Get rotations degree that viewmgr can be rotate
 * @scenario        Try to get rotations degree with invalid param
 */
int utc_ui_viewmgr_view_get_available_rotations_n(void)
{
	ui_view* view = NULL;

	unsigned int cnt;
	assert_eq(ui_view_get_available_rotations(view, &cnt), NULL);

	view = ui_view_create("page1");
	assert(view);

	assert_eq(ui_view_get_available_rotations(view, NULL), NULL);

	ui_view_destroy(view);

	return 0;
}


/**
 * @testcase        utc_ui_viewmgr_view_set_removable_content_p
 * @since_tizen     3.0
 * @description     Set view's content removable
 * @scenario        Create view
 *                  Set content removable
 */
int utc_ui_viewmgr_view_set_removable_content_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	assert_eq(ui_view_set_removable_content(view, false), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_view_set_removable_content(view, true), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_set_removable_content_n
 * @since_tizen     3.0
 * @description     Set view's content removable
 * @scenario        Try to set removble state of view with invalid param
 */
int utc_ui_viewmgr_view_set_removable_content_n(void)
{
	ui_view* view = NULL;

	assert_eq(ui_view_set_removable_content(view, true), UI_VIEWMGR_ERROR_INVALID_PARAMETER);
	assert_eq(ui_view_set_removable_content(view, false), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_removable_content_p
 * @since_tizen     3.0
 * @description     Get view's content removable
 * @scenario        Create view
 *                  Set content removable
 *                  Get content removable state
 */
int utc_ui_viewmgr_view_get_removable_content_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	assert_eq(ui_view_get_removable_content(view), true);

	ui_view_set_removable_content(view, false);

	assert_eq(ui_view_get_removable_content(view), false);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_removable_content_n
 * @since_tizen     3.0
 * @description     Get view's content removable
 * @scenario        Try to get removble state of view with invalid param
 */
int utc_ui_viewmgr_view_get_removable_content_n(void)
{
	ui_view* view = NULL;

	assert_eq(ui_view_get_removable_content(view), false);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_degree_p
 * @since_tizen     3.0
 * @description     Get current view's degree
 * @scenario        Create view
 *                  Get current degree
 */
int utc_ui_viewmgr_view_get_degree_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	assert_neq(ui_view_get_degree(view), -1);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_degree_n
 * @since_tizen     3.0
 * @description     Get current view's degree
 * @scenario        Try to get degree with invalid param
 */
int utc_ui_viewmgr_view_get_degree_n(void)
{
	ui_view* view = NULL;

	assert_eq(ui_view_get_degree(view), -1);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_orientation_mode_p
 * @since_tizen     3.0
 * @description     Get view's orientation mode
 * @scenario        Create view
 *                  Get current orientation mode
 */
int utc_ui_viewmgr_view_get_orientation_mode_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	ui_view_orientation_mode mode = ui_view_get_orientation_mode(view);
	if (mode < UI_VIEW_ORIENTATION_MODE_UNKNOWN || mode > UI_VIEW_ORIENTATION_MODE_LANDSCAPE)
	  assert_eq(1, 0);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_orientation_mode_n
 * @since_tizen     3.0
 * @description     Get view's orientation mode
 * @scenario        Try to get orientation with invalid param
 */
int utc_ui_viewmgr_view_get_orientation_mode_n(void)
{
	ui_view* view = NULL;

	assert_eq(ui_view_get_orientation_mode(view), UI_VIEW_ORIENTATION_MODE_UNKNOWN);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_set_transition_style_p
 * @since_tizen     3.0
 * @description     Set view's transition style
 * @scenario        Create view
 *                  Set transition style of view
 */
int utc_ui_viewmgr_view_set_transition_style_p(void)
{
	ui_view* view;

	view = ui_view_create("page1");
	assert(view);

	assert_eq(ui_view_set_transition_style(view, "none"), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_set_transition_style_n
 * @since_tizen     3.0
 * @description     Get view's transition style
 * @scenario        Try to set transition style of view with invalid param
 */
int utc_ui_viewmgr_view_set_transition_style_n(void)
{
	ui_view* view = NULL;

	assert_eq(ui_view_set_transition_style(view, "none"), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_transition_style_p
 * @since_tizen     3.0
 * @description     Get view's transition style
 * @scenario        Create view
 *                  Get transition style
 */
int utc_ui_viewmgr_view_get_transition_style_p(void)
{
	ui_view* view = NULL;

	assert_eq(ui_view_get_transition_style(view), NULL);

	view = ui_view_create("page1");
	assert(view);

	assert_eq(ui_view_set_transition_style(view, "none"), UI_VIEWMGR_ERROR_NONE);

	assert_eq(strcmp(ui_view_get_transition_style(view), "none"), 0);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_transition_style_n
 * @since_tizen     3.0
 * @description     Get view's transition style
 * @scenario        Try to get transition style of view with invalid param
 */
int utc_ui_viewmgr_view_get_transition_style_n(void)
{
	ui_view* view = NULL;

	assert_eq(ui_view_get_transition_style(view), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_menu_p
 * @since_tizen     3.0
 * @description     Get menu object
 * @scenario        Create a view
 *                  Get a menu
 */
int utc_ui_viewmgr_view_get_menu_p(void)
{
	ui_view* view = NULL;

	view = ui_view_create("page1");
	assert(view);

	assert_eq(ui_view_get_menu(view), NULL);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_menu_n
 * @since_tizen     3.0
 * @description     Get menu object
 * @scenario        Create a view
 *                  Get a menu with invalid param
 */
int utc_ui_viewmgr_view_get_menu_n(void)
{
	ui_view* view = NULL;

	assert_eq(ui_view_get_menu(view), NULL);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_name_p
 * @since_tizen     3.0
 * @description     Get name of view
 * @scenario        Create view
 *                  Set name of view
 *                  Get name of view and compare
 */
int utc_ui_viewmgr_view_get_name_p(void)
{
	ui_view *view, *view2, *view3, *view4;

	view = ui_view_create("page1");
	assert(view);
	ui_view_set_transition_style(view, "none");

	ui_viewmgr_push_view(view);

	view2 = ui_view_create("page2");
	assert(view2);
	ui_view_set_transition_style(view2, "none");

	ui_viewmgr_push_view(view2);

	view3 = ui_view_create("page2");
	assert(view3);
	ui_view_set_transition_style(view3, "none");

	ui_viewmgr_push_view(view3);

	view4 = ui_view_create(NULL);
	assert(view4);
	ui_view_set_transition_style(view4, "none");

	ui_viewmgr_push_view(view4);

	if (strcmp(ui_view_get_name(view), "page1"))
	  assert_eq(1, 0);

	if (strcmp(ui_view_get_name(view2), "page2"))
	  assert_eq(1, 0);

	if (strcmp(ui_view_get_name(view3), "page2"))
	  assert_eq(1, 0);

	const char* name = ui_view_get_name(view4);
	assert(name);
	assert_eq(strcmp(name, ""), 0);

	ui_view_destroy(view);
	ui_view_destroy(view2);
	ui_view_destroy(view3);
	ui_view_destroy(view4);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_name_n
 * @since_tizen     3.0
 * @description     Get name object
 * @scenario        Try to get name of view with invalid param
 */
int utc_ui_viewmgr_view_get_name_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_view_get_name(view), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_state_p
 * @since_tizen     3.0
 * @description     Get state of view
 * @scenario        Create view
 *                  Get state of view
 */
int utc_ui_viewmgr_view_get_state_p(void)
{
	ui_view *view, *view2;

	view = ui_view_create("page1");
	assert(view);
	ui_view_set_transition_style(view, "none");

	assert_eq(ui_view_get_state(view), UI_VIEW_STATE_UNLOAD);

	assert_eq(ui_view_set_event_cb(view, UI_VIEW_EVENT_LOAD, view_load_cb, NULL), UI_VIEWMGR_ERROR_NONE);

	ui_viewmgr_push_view(view);

	assert_eq(ui_view_get_state(view), UI_VIEW_STATE_LOAD);

	view2 = ui_view_create("page2");
	assert(view2);
	ui_view_set_transition_style(view2, "none");

	assert_eq(ui_view_get_state(view2), UI_VIEW_STATE_UNLOAD);

	assert_eq(ui_view_set_event_cb(view2, UI_VIEW_EVENT_LOAD, view2_load_cb, NULL), UI_VIEWMGR_ERROR_NONE);

	ui_viewmgr_push_view(view2);

	assert_eq(ui_view_get_state(view2), UI_VIEW_STATE_ACTIVATE);

	ui_view_destroy(view);
	ui_view_destroy(view2);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_get_state_n
 * @since_tizen     3.0
 * @description     Get state of view
 * @scenario        Try to get state of view with invalid param
 */
int utc_ui_viewmgr_view_get_state_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_view_get_state(view), UI_VIEW_STATE_UNKNOWN);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_destroy_p
 * @since_tizen     3.0
 * @description     Destroy view
 * @scenario        Create view
 *                  Destroy view
 */
int utc_ui_viewmgr_view_destroy_p(void)
{
	ui_view *view, *view2;

	view = ui_view_create("page1");
	assert(view);
	ui_view_set_transition_style(view, "none");

	view2 = ui_view_create("page2");
	assert(view2);
	ui_view_set_transition_style(view2, "none");

	ui_viewmgr_push_view(view2);

	assert_eq(ui_view_destroy(view), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_view_destroy(view2), UI_VIEWMGR_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_view_destroy_n
 * @since_tizen     3.0
 * @description     Destroy view
 * @scenario        Try to destroy view with invalid param
 */
int utc_ui_viewmgr_view_destroy_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_view_destroy(view), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_create_p
 * @since_tizen     3.0
 * @description     Create standard view
 * @scenario        Create view
 */
int utc_ui_viewmgr_standard_view_create_p(void)
{
	ui_view *view, *view2;

	view = ui_standard_view_create("@#!%!@#@");
	assert(view);
	ui_view_set_transition_style(view, "none");

	Eo* base = ui_view_get_base(view);
	assert(base);

	Elm_Button* btn = elm_button_add(base);
	assert(btn);

	ui_view_set_content(view, btn);

	assert_eq(btn, ui_view_unset_content(view));

	view2 = ui_standard_view_create(NULL);
	assert(view2);
	ui_view_set_transition_style(view2, "none");

	assert_eq(ui_view_get_state(view2), UI_VIEW_STATE_UNLOAD);

	assert_eq(ui_view_set_event_cb(view2, UI_VIEW_EVENT_LOAD, view2_load_cb, NULL), UI_VIEWMGR_ERROR_NONE);

	ui_viewmgr_push_view(view2);

	assert_eq(ui_view_get_state(view2), UI_VIEW_STATE_ACTIVATE);

	ui_view_destroy(view);
	ui_view_destroy(view2);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_title_p
 * @since_tizen     3.0
 * @description     Set title of standard view
 * @scenario        Create standard view
 *                  Set title of standard view
 */
int utc_ui_viewmgr_standard_view_set_title_p(void)
{
	ui_view *view;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_set_title(view, "title"), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_title(view, ""), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_title(view, NULL), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_title_n
 * @since_tizen     3.0
 * @description     Set title of standard view
 * @scenario        Set title of standard view with invalid param
 */
int utc_ui_viewmgr_standard_view_set_title_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_standard_view_set_title(view, "title"), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_sub_title_p
 * @since_tizen     3.0
 * @description     Set sub title of standard view
 * @scenario        Create standard view
 *                  Set sub title of standard view
 */
int utc_ui_viewmgr_standard_view_set_sub_title_p(void)
{
	ui_view *view;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_set_sub_title(view, "subtitle"), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_sub_title(view, ""), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_sub_title(view, NULL), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_sub_title_n
 * @since_tizen     3.0
 * @description     Set sub title of standard view
 * @scenario        Set sub title of standard view with invalid param
 */
int utc_ui_viewmgr_standard_view_set_sub_title_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_standard_view_set_sub_title(view, "title"), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_title_badge_p
 * @since_tizen     3.0
 * @description     Set title badge of standard view
 * @scenario        Create standard view
 *                  Set title badge of standard view
 */
int utc_ui_viewmgr_standard_view_set_title_badge_p(void)
{
	ui_view *view;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_set_title_badge(view, "badge"), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_title_badge(view, ""), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_title_badge(view, NULL), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_title_badge_n
 * @since_tizen     3.0
 * @description     Set title badge of standard view
 * @scenario        Set title badge of standard view with invalid param
 */
int utc_ui_viewmgr_standard_view_set_title_badge_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_standard_view_set_title_badge(view, "badge"), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_title_right_btn_p
 * @since_tizen     3.0
 * @description     Set title right btn of standard view
 * @scenario        Create standard view
 *                  Set title right btn of standard view
 */
int utc_ui_viewmgr_standard_view_set_title_right_btn_p(void)
{
	ui_view *view;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_set_title_right_btn(view, NULL), UI_VIEWMGR_ERROR_ALREADY_IN_PROGRESS);

	Elm_Button *btn = elm_button_add(ui_view_get_base(view));
	assert_eq(ui_standard_view_set_title_right_btn(view, btn), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_title_right_btn(view, NULL), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_title_right_btn_n
 * @since_tizen     3.0
 * @description     Set title right btn of standard view
 * @scenario        Try to set title right btn with invalid param
 */
int utc_ui_viewmgr_standard_view_set_title_right_btn_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_standard_view_set_title_right_btn(view, NULL), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	view = ui_standard_view_create("page1");
	assert(view);

	Elm_Button *btn = elm_button_add(ui_view_get_base(view));

	ui_standard_view_set_title_right_btn(view, btn);
	assert_eq(ui_standard_view_set_title_right_btn(view, btn), UI_VIEWMGR_ERROR_ALREADY_IN_PROGRESS);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_get_title_right_btn_p
 * @since_tizen     3.0
 * @description     Get title right btn of standard view
 * @scenario        Create standard view
 *                  Set title right btn of standard view
 *                  Get title right btn and check
 */
int utc_ui_viewmgr_standard_view_get_title_right_btn_p(void)
{
	ui_view *view;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_get_title_right_btn(view), NULL);

	Elm_Button *btn = elm_button_add(ui_view_get_base(view));
	ui_standard_view_set_title_right_btn(view, btn);
	assert_eq(ui_standard_view_get_title_right_btn(view), btn);

	Elm_Button *btn2 = elm_button_add(ui_view_get_base(view));
	ui_standard_view_set_title_right_btn(view, btn2);
	assert_eq(ui_standard_view_get_title_right_btn(view), btn2);

	ui_standard_view_set_title_right_btn(view, NULL);
	assert_eq(ui_standard_view_get_title_right_btn(view), NULL);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_get_title_right_btn_n
 * @since_tizen     3.0
 * @description     Get title right btn of standard view
 * @scenario        Try to get title right btn with invalid param
 */
int utc_ui_viewmgr_standard_view_get_title_right_btn_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_standard_view_get_title_right_btn(view), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_unset_title_right_btn_p
 * @since_tizen     3.0
 * @description     Unset title right btn of standard view
 * @scenario        Create standard view
 *                  Set title right btn of standard view
 *                  Unset title right btn and check
 */
int utc_ui_viewmgr_standard_view_unset_title_right_btn_p(void)
{
	ui_view *view;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_unset_title_right_btn(view), NULL);

	Elm_Button *btn = elm_button_add(ui_view_get_base(view));
	ui_standard_view_set_title_right_btn(view, btn);
	assert_eq(ui_standard_view_unset_title_right_btn(view), btn);

	Elm_Button *btn2 = elm_button_add(ui_view_get_base(view));
	ui_standard_view_set_title_right_btn(view, btn2);
	assert_eq(ui_standard_view_unset_title_right_btn(view), btn2);

	ui_standard_view_set_title_right_btn(view, NULL);
	assert_eq(ui_standard_view_unset_title_right_btn(view), NULL);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_unset_title_right_btn_n
 * @since_tizen     3.0
 * @description     Unset title right btn of standard view
 * @scenario        Try to unset title right btn with invalid param
 */
int utc_ui_viewmgr_standard_view_unset_title_right_btn_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_standard_view_unset_title_right_btn(view), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_title_left_btn_p
 * @since_tizen     3.0
 * @description     Set title left btn of standard view
 * @scenario        Create standard view
 *                  Set title left btn of standard view
 */
int utc_ui_viewmgr_standard_view_set_title_left_btn_p(void)
{
	ui_view *view;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_set_title_left_btn(view, NULL), UI_VIEWMGR_ERROR_ALREADY_IN_PROGRESS);

	Elm_Button *btn = elm_button_add(ui_view_get_base(view));
	assert_eq(ui_standard_view_set_title_left_btn(view, btn), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_title_left_btn(view, NULL), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_title_left_btn_n
 * @since_tizen     3.0
 * @description     Set title left btn of standard view
 * @scenario        Try to set title left btn with invalid param
 */
int utc_ui_viewmgr_standard_view_set_title_left_btn_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_standard_view_set_title_left_btn(view, NULL), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	view = ui_standard_view_create("page1");
	assert(view);

	Elm_Button *btn = elm_button_add(ui_view_get_base(view));

	ui_standard_view_set_title_left_btn(view, btn);
	assert_eq(ui_standard_view_set_title_left_btn(view, btn), UI_VIEWMGR_ERROR_ALREADY_IN_PROGRESS);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_get_title_left_btn_p
 * @since_tizen     3.0
 * @description     Get title left btn of standard view
 * @scenario        Create standard view
 *                  Set title left btn of standard view
 *                  Get title left btn and check
 */
int utc_ui_viewmgr_standard_view_get_title_left_btn_p(void)
{
	ui_view *view;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_get_title_left_btn(view), NULL);

	Elm_Button *btn = elm_button_add(ui_view_get_base(view));
	ui_standard_view_set_title_left_btn(view, btn);
	assert_eq(ui_standard_view_get_title_left_btn(view), btn);

	Elm_Button *btn2 = elm_button_add(ui_view_get_base(view));
	ui_standard_view_set_title_left_btn(view, btn2);
	assert_eq(ui_standard_view_get_title_left_btn(view), btn2);

	ui_standard_view_set_title_left_btn(view, NULL);
	assert_eq(ui_standard_view_get_title_left_btn(view), NULL);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_get_title_left_btn_n
 * @since_tizen     3.0
 * @description     Get title left btn of standard view
 * @scenario        Try to get title left btn with invalid param
 */
int utc_ui_viewmgr_standard_view_get_title_left_btn_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_standard_view_get_title_left_btn(view), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_unset_title_left_btn_p
 * @since_tizen     3.0
 * @description     Unset title left btn of standard view
 * @scenario        Create standard view
 *                  Set title left btn of standard view
 *                  Unset title left btn and check
 */
int utc_ui_viewmgr_standard_view_unset_title_left_btn_p(void)
{
	ui_view *view;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_unset_title_left_btn(view), NULL);

	Elm_Button *btn = elm_button_add(ui_view_get_base(view));
	ui_standard_view_set_title_left_btn(view, btn);
	assert_eq(ui_standard_view_unset_title_left_btn(view), btn);

	Elm_Button *btn2 = elm_button_add(ui_view_get_base(view));
	ui_standard_view_set_title_left_btn(view, btn2);
	assert_eq(ui_standard_view_unset_title_left_btn(view), btn2);

	ui_standard_view_set_title_left_btn(view, NULL);
	assert_eq(ui_standard_view_unset_title_left_btn(view), NULL);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_unset_title_left_btn_n
 * @since_tizen     3.0
 * @description     Unset title left btn of standard view
 * @scenario        Try to unset title left btn with invalid param
 */
int utc_ui_viewmgr_standard_view_unset_title_left_btn_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_standard_view_unset_title_left_btn(view), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_toolbar_p
 * @since_tizen     3.0
 * @description     Set toolbar of standard view
 * @scenario        Create standard view
 *                  Set toolbar of standard view
 */
int utc_ui_viewmgr_standard_view_set_toolbar_p(void)
{
	ui_view *view;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_set_toolbar(view, NULL), UI_VIEWMGR_ERROR_ALREADY_IN_PROGRESS);

	Elm_Toolbar *toolbar = elm_toolbar_add(ui_view_get_base(view));
	assert_eq(ui_standard_view_set_toolbar(view, toolbar), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_toolbar(view, NULL), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_toolbar_n
 * @since_tizen     3.0
 * @description     Set toolbar of standard view
 * @scenario        Try to set toolbar with invalid param
 */
int utc_ui_viewmgr_standard_view_set_toolbar_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_standard_view_set_toolbar(view, NULL), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	view = ui_standard_view_create("page1");
	assert(view);

	Elm_Toolbar *toolbar = elm_toolbar_add(ui_view_get_base(view));
	assert_eq(ui_standard_view_set_toolbar(view, toolbar), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_toolbar(view, toolbar), UI_VIEWMGR_ERROR_ALREADY_IN_PROGRESS);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_get_toolbar_p
 * @since_tizen     3.0
 * @description     Get toolbar of standard view
 * @scenario        Create standard view
 *                  Set toolbar of standard view
 *                  Get toolbar and check
 */
int utc_ui_viewmgr_standard_view_get_toolbar_p(void)
{
	ui_view *view = NULL;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_get_toolbar(view), NULL);

	Elm_Toolbar *toolbar = elm_toolbar_add(ui_view_get_base(view));
	ui_standard_view_set_toolbar(view, toolbar);
	assert_eq(ui_standard_view_get_toolbar(view), toolbar);

	ui_standard_view_set_toolbar(view, NULL);
	assert_eq(ui_standard_view_get_toolbar(view), NULL);

	evas_object_del(toolbar);
	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_get_toolbar_n
 * @since_tizen     3.0
 * @description     Get toolbar of standard view
 * @scenario        Try to get toolbar with invalid param
 */
int utc_ui_viewmgr_standard_view_get_toolbar_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_standard_view_get_toolbar(view), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_unset_toolbar_p
 * @since_tizen     3.0
 * @description     Unset toolbar of standard view
 * @scenario        Create standard view
 *                  Set toolbar of standard view
 *                  Unset toolbar and check
 */
int utc_ui_viewmgr_standard_view_unset_toolbar_p(void)
{
	ui_view *view = NULL;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_unset_toolbar(view), NULL);

	Elm_Toolbar *toolbar = elm_toolbar_add(ui_view_get_base(view));
	ui_standard_view_set_toolbar(view, toolbar);
	assert_eq(ui_standard_view_unset_toolbar(view), toolbar);

	ui_standard_view_set_toolbar(view, NULL);
	assert_eq(ui_standard_view_unset_toolbar(view), NULL);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_unset_toolbar_n
 * @since_tizen     3.0
 * @description     Unset toolbar of standard view
 * @scenario        Try to unset toolbar with invalid param
 */
int utc_ui_viewmgr_standard_view_unset_toolbar_n(void)
{
	ui_view *view = NULL;

	assert_eq(ui_standard_view_unset_toolbar(view), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_title_visible_p
 * @since_tizen     3.0
 * @description     Set standard view's visible property
 * @scenario        Create standard view
 *                  Try to set title visible options and check the return value
 */
int utc_ui_viewmgr_standard_view_set_title_visible_p(void)
{
	ui_standard_view *view;

	view = ui_standard_view_create("page1");
	assert(view);

	assert_eq(ui_standard_view_set_title_visible(view, true, true), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_title_visible(view, true, false), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_title_visible(view, false, true), UI_VIEWMGR_ERROR_NONE);
	assert_eq(ui_standard_view_set_title_visible(view, false, false), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_standard_view_set_title_visible_n
 * @since_tizen     3.0
 * @description     Set standard view's visible property
 * @scenario        Try to set visible property with invalid param
 */
int utc_ui_viewmgr_standard_view_set_title_visible_n(void)
{
	ui_standard_view *view = NULL;

	assert_eq(ui_standard_view_set_title_visible(view, true, true), UI_VIEWMGR_ERROR_INVALID_PARAMETER);
	assert_eq(ui_standard_view_set_title_visible(view, true, false), UI_VIEWMGR_ERROR_INVALID_PARAMETER);
	assert_eq(ui_standard_view_set_title_visible(view, false, true), UI_VIEWMGR_ERROR_INVALID_PARAMETER);
	assert_eq(ui_standard_view_set_title_visible(view, false, false), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_create_p
 * @since_tizen     3.0
 * @description     Create popup
 * @scenario        Create popup and check the return value
 */
int utc_ui_viewmgr_popup_create_p(void)
{
	ui_view *view;
	ui_popup *popup;

	view = ui_view_create("page1");
	assert(view);

	popup = ui_popup_create(view);
	assert_neq(popup, NULL);
	assert_eq(get_last_result(), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_create_n
 * @since_tizen     3.0
 * @description     Create popup
 * @scenario        Try to create popup with invalid param
 */
int utc_ui_viewmgr_popup_create_n(void)
{
	ui_view* view = NULL;

	assert_eq(ui_popup_create(view), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_destroy_p
 * @since_tizen     3.0
 * @description     Destroy popup
 * @scenario        TODO
 */
int utc_ui_viewmgr_popup_destroy_p(void)
{
	ui_view *view;
	ui_popup *popup;

	view = ui_view_create("page1");
	assert(view);

	popup = ui_popup_create(view);
	assert(popup);

	assert_eq(ui_popup_destroy(popup), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_destroy_n
 * @since_tizen     3.0
 * @description     Destroy popup
 * @scenario        Try to destroy popup with invalid param
 */
int utc_ui_viewmgr_popup_destroy_n(void)
{
	ui_popup* popup = NULL;

	assert_eq(ui_popup_destroy(popup), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_set_content_n
 * @since_tizen     3.0
 * @description     Set popup's content
 * @scenario        Create popup
 *                  Set popup's content
 *                  Get popup's content and check
 */
int utc_ui_viewmgr_popup_set_content_p(void)
{
	ui_view *view;
	ui_popup *popup;
	Elm_Popup *elm_popup;

	view = ui_view_create("page1");
	assert(view);

	popup = ui_popup_create(view);
	assert(popup);

	elm_popup = elm_popup_add(ui_popup_get_base(popup));
	assert(elm_popup);

	assert_eq(ui_popup_set_content(popup, elm_popup), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_set_content_n
 * @since_tizen     3.0
 * @description     Set popup's content
 * @scenario        Try to set popup's content with invalid param
 */
int utc_ui_viewmgr_popup_set_content_n(void)
{
	ui_popup *popup = NULL;

	assert_eq(ui_popup_set_content(popup, NULL), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_get_content_p
 * @since_tizen     3.0
 * @description     Get popup's content
 * @scenario        Create popup
 *                  Set popup's content
 *                  Get popup's content and check
 */
int utc_ui_viewmgr_popup_get_content_p(void)
{
	ui_view *view;
	ui_popup *popup;
	Elm_Popup *content;

	view = ui_view_create("page1");
	assert(view);

	popup = ui_popup_create(view);
	assert(popup);

	content = elm_popup_add(ui_viewmgr_get_base());
	assert(content);

	ui_popup_set_content(popup, content);

	assert_eq(ui_popup_get_content(popup), content);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_get_content_n
 * @since_tizen     3.0
 * @description     Get popup's content
 * @scenario        Try to get popup's content with invalid param
 */
int utc_ui_viewmgr_popup_get_content_n(void)
{
	ui_popup* popup = NULL;

	assert_eq(ui_popup_get_content(popup), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_unset_content_p
 * @since_tizen     3.0
 * @description     Unset popup's content
 * @scenario        Create popup
 *                  Set popup's content
 *                  Unset popup's content and check
 */
int utc_ui_viewmgr_popup_unset_content_p(void)
{
	ui_view *view;
	ui_popup *popup;
	Elm_Popup *content;

	view = ui_view_create("page1");
	assert(view);

	popup = ui_popup_create(view);
	assert(popup);

	content = elm_popup_add(ui_popup_get_base(popup));
	assert(content);

	ui_popup_set_content(popup, content);

	assert_eq(ui_popup_unset_content(popup), content);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_unset_content_n
 * @since_tizen     3.0
 * @description     Unset popup's content
 * @scenario        Try to unset popup's content with invalid param
 */
int utc_ui_viewmgr_popup_unset_content_n(void)
{
	ui_popup *popup = NULL;

	assert_eq(ui_popup_unset_content(popup), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_activate_p
 * @since_tizen     3.0
 * @description     Activate popup
 * @scenario        Create popup
 *                  Activate popup
 *                  Check the return value
 */
int utc_ui_viewmgr_popup_activate_p(void)
{
	ui_view *view;
	ui_popup *popup;
	Elm_Popup *content;

	view = ui_view_create("page1");
	assert(view);

	ui_view_set_transition_style(view, "none");
	assert_eq(ui_view_set_event_cb(view, UI_VIEW_EVENT_LOAD, view2_load_cb, NULL), UI_VIEWMGR_ERROR_NONE);
	ui_viewmgr_push_view(view);

	popup = ui_popup_create(view);
	assert(popup);

	content = elm_popup_add(ui_popup_get_base(popup));
	assert(content);

	ui_popup_set_content(popup, content);

	assert_eq(ui_popup_activate(popup), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_activate_n
 * @since_tizen     3.0
 * @description     Activate popup
 * @scenario        Try to activate popup with invalid param
 */
int utc_ui_viewmgr_popup_activate_n(void)
{
	ui_popup *popup = NULL;
	ui_view *view;
	Elm_Popup *content;

	assert_eq(ui_popup_activate(popup), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	view = ui_view_create("page1");
	assert(view);

	popup = ui_popup_create(view);
	assert(popup);

	content = elm_popup_add(ui_popup_get_base(popup));
	assert(content);

	ui_popup_set_content(popup, content);

	assert_eq(ui_popup_activate(popup), UI_VIEWMGR_ERROR_NOT_PERMITTED);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_deactivate_p
 * @since_tizen     3.0
 * @description     Deactivate popup
 * @scenario        Create popup
 *                  Deactivate popup
 *                  Check the return value
 */
int utc_ui_viewmgr_popup_deactivate_p(void)
{
	ui_view *view;
	ui_popup *popup;
	Elm_Popup *content;

	view = ui_view_create("page1");
	assert(view);

	ui_view_set_transition_style(view, "none");
	assert_eq(ui_view_set_event_cb(view, UI_VIEW_EVENT_LOAD, view2_load_cb, NULL), UI_VIEWMGR_ERROR_NONE);
	ui_viewmgr_push_view(view);

	popup = ui_popup_create(view);
	assert(popup);

	content = elm_popup_add(ui_popup_get_base(popup));
	assert(content);

	ui_popup_set_content(popup, content);

	ui_popup_activate(popup);

	assert_eq(ui_popup_deactivate(popup), UI_VIEWMGR_ERROR_NONE);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_deactivate_n
 * @since_tizen     3.0
 * @description     Deactivate popup
 * @scenario        Try to deactivate popup with invalid param
 */
int utc_ui_viewmgr_popup_deactivate_n(void)
{
	ui_popup *popup = NULL;
	ui_view *view;
	Elm_Popup *content;

	assert_eq(ui_popup_activate(popup), UI_VIEWMGR_ERROR_INVALID_PARAMETER);

	view = ui_view_create("page1");
	assert(view);

	popup = ui_popup_create(view);
	assert(popup);

	content = elm_popup_add(ui_popup_get_base(popup));
	assert(content);

	ui_popup_set_content(popup, content);

	ui_popup_activate(popup);

	assert_eq(ui_popup_deactivate(popup), UI_VIEWMGR_ERROR_NOT_PERMITTED);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_get_activated_p
 * @since_tizen     3.0
 * @description     Get popup activated or not
 * @scenario        Create popup
 *                  Activate popup
 *                  Get state of popup
 */
int utc_ui_viewmgr_popup_get_activated_p(void)
{
	ui_view *view;
	ui_popup *popup;
	Elm_Popup *content;

	view = ui_view_create("page1");
	assert(view);

	ui_view_set_transition_style(view, "none");
	assert_eq(ui_view_set_event_cb(view, UI_VIEW_EVENT_LOAD, view2_load_cb, NULL), UI_VIEWMGR_ERROR_NONE);
	ui_viewmgr_push_view(view);

	popup = ui_popup_create(view);
	assert(popup);

	content = elm_popup_add(ui_popup_get_base(popup));
	assert(content);

	ui_popup_set_content(popup, content);

	ui_popup_activate(popup);

	assert_eq(ui_popup_get_activated(popup), true);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_get_activated_n
 * @since_tizen     3.0
 * @description     Get popup activated or not
 * @scenario        Try to get popup activated state popup with invalid param
 */
int utc_ui_viewmgr_popup_get_activated_n(void)
{
	ui_popup *popup = NULL;

	assert_eq(ui_popup_get_activated(popup), false);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_get_base_p
 * @since_tizen     3.0
 * @description     Get base object of popup
 * @scenario        Create popup
 *                  Get base object of popup
 */
int utc_ui_viewmgr_popup_get_base_p(void)
{
	ui_view *view;
	ui_popup *popup;

	view = ui_view_create("page1");
	assert(view);

	popup = ui_popup_create(view);
	assert(popup);

	assert_neq(ui_popup_get_base(popup), NULL);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_get_base_n
 * @since_tizen     3.0
 * @description     Get base object of view
 * @scenario        Try to get base object of popup with invalid param
 */
int utc_ui_viewmgr_popup_get_base_n(void)
{
	ui_popup *popup = NULL;

	assert_eq(ui_popup_get_base(popup), NULL);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_get_degree_p
 * @since_tizen     3.0
 * @description     Get degree of popup
 * @scenario        Create popup
 *                  Get degree of popup
 */
int utc_ui_viewmgr_popup_get_degree_p(void)
{
	ui_view *view;
	ui_popup *popup;

	view = ui_view_create("page1");
	assert(view);

	popup = ui_popup_create(view);
	assert(popup);

	assert_neq(ui_popup_get_degree(popup), -1);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_get_degree_n
 * @since_tizen     3.0
 * @description     Get degree of popup
 * @scenario        Try to get degree of popup with invalid param
 */
int utc_ui_viewmgr_popup_get_degree_n(void)
{
	ui_popup *popup = NULL;

	assert_eq(ui_popup_get_degree(popup), -1);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_get_view_p
 * @since_tizen     3.0
 * @description     Get view which connect with popup
 * @scenario        Create popup
 *                  Get view of popup and check the view instance
 */
int utc_ui_viewmgr_popup_get_view_p(void)
{
	ui_view *view;
	ui_popup *popup;

	view = ui_view_create("page1");
	assert(view);

	popup = ui_popup_create(view);
	assert(popup);

	assert_eq(ui_popup_get_view(popup), view);

	ui_view_destroy(view);

	return 0;
}

/**
 * @testcase        utc_ui_viewmgr_popup_get_degree_n
 * @since_tizen     3.0
 * @description     Get view which connect with popup
 * @scenario        Try to get view of popup with invalid param
 */
int utc_ui_viewmgr_popup_get_view_n(void)
{
	ui_popup *popup = NULL;

	assert_eq(ui_popup_get_view(popup), NULL);

	return 0;
}
