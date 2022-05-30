//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include <app.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <libintl.h>

#include <notification-ex/api/notification_ex.h>

#include "utc-notification.h"

void utc_notification_ex_item_startup(void)
{
}

void utc_notification_ex_item_cleanup(void)
{
}

/**
 * @testcase utc_noti_ex_color_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_color_create()
 */
int utc_noti_ex_color_create_p(void)
{
	int ret;
	noti_ex_color_h handle;
	ret = noti_ex_color_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_color_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_color_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_color_create()
 */
int utc_noti_ex_color_create_n(void)
{
	int ret;
	ret = noti_ex_color_create(NULL, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_color_destroy_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_color_destroy()
 */
int utc_noti_ex_color_destroy_p(void)
{
	int ret;
	noti_ex_color_h handle;
	ret = noti_ex_color_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_color_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_color_destroy_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_color_destroy()
 */
int utc_noti_ex_color_destroy_n(void)
{
	int ret;
	ret = noti_ex_color_destroy(NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_color_get_alpha_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_color_get_alpha()
 */
int utc_noti_ex_color_get_alpha_p(void)
{
	int ret;
	unsigned char val;
	noti_ex_color_h handle;
	ret = noti_ex_color_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_color_get_alpha(handle, &val);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(val, 1);
	noti_ex_color_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_color_get_alpha_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_color_get_alpha()
 */
int utc_noti_ex_color_get_alpha_n(void)
{
	int ret;
	ret = noti_ex_color_get_alpha(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_color_get_red_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_color_get_red()
 */
int utc_noti_ex_color_get_red_p(void)
{
	int ret;
	unsigned char val;
	noti_ex_color_h handle;
	ret = noti_ex_color_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_color_get_red(handle, &val);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(val, 2);
	noti_ex_color_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_color_get_red_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_color_get_red()
 */
int utc_noti_ex_color_get_red_n(void)
{
	int ret;
	ret = noti_ex_color_get_red(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_color_get_green_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_color_get_green()
 */
int utc_noti_ex_color_get_green_p(void)
{
	int ret;
	unsigned char val;
	noti_ex_color_h handle;
	ret = noti_ex_color_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_color_get_green(handle, &val);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(val, 3);
	noti_ex_color_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_color_get_green_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_color_get_green()
 */
int utc_noti_ex_color_get_green_n(void)
{
	int ret;
	ret = noti_ex_color_get_green(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_color_get_blue_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_color_get_blue()
 */
int utc_noti_ex_color_get_blue_p(void)
{
	int ret;
	unsigned char val;
	noti_ex_color_h handle;
	ret = noti_ex_color_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_color_get_blue(handle, &val);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(val, 4);
	noti_ex_color_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_color_get_blue_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_color_get_blue()
 */
int utc_noti_ex_color_get_blue_n(void)
{
	int ret;
	ret = noti_ex_color_get_blue(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_padding_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_padding_create()
 */
int utc_noti_ex_padding_create_p(void)
{
	int ret;
	noti_ex_padding_h handle;
	ret = noti_ex_padding_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_color_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_padding_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_padding_create()
 */
int utc_noti_ex_padding_create_n(void)
{
	int ret;
	ret = noti_ex_padding_create(NULL, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_padding_destroy_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_padding_destroy()
 */
int utc_noti_ex_padding_destroy_p(void)
{
	int ret;
	noti_ex_padding_h handle;
	ret = noti_ex_padding_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_padding_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_padding_destroy_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_padding_destroy()
 */
int utc_noti_ex_padding_destroy_n(void)
{
	int ret;
	ret = noti_ex_padding_destroy(NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_padding_get_left_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_padding_get_left()
 */
int utc_noti_ex_padding_get_left_p(void)
{
	int ret;
	int val;
	noti_ex_padding_h handle;
	ret = noti_ex_padding_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_padding_get_left(handle, &val);
	assert_eq_with_exit(val, 1);
	noti_ex_padding_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_padding_get_left_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_padding_get_left()
 */
int utc_noti_ex_padding_get_left_n(void)
{
	int ret;
	ret = noti_ex_padding_get_left(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_padding_get_top_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_padding_get_top()
 */
int utc_noti_ex_padding_get_top_p(void)
{
	int ret;
	int val;
	noti_ex_padding_h handle;
	ret = noti_ex_padding_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_padding_get_top(handle, &val);
	assert_eq_with_exit(val, 2);
	noti_ex_padding_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_padding_get_top_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_padding_get_top()
 */
int utc_noti_ex_padding_get_top_n(void)
{
	int ret;
	ret = noti_ex_padding_get_top(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_padding_get_right_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_padding_get_right()
 */
int utc_noti_ex_padding_get_right_p(void)
{
	int ret;
	int val;
	noti_ex_padding_h handle;
	ret = noti_ex_padding_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_padding_get_right(handle, &val);
	assert_eq_with_exit(val, 3);
	noti_ex_padding_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_padding_get_right_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_padding_get_right()
 */
int utc_noti_ex_padding_get_right_n(void)
{
	int ret;
	ret = noti_ex_padding_get_right(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_padding_get_bottom_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_padding_get_bottom()
 */
int utc_noti_ex_padding_get_bottom_p(void)
{
	int ret;
	int val;
	noti_ex_padding_h handle;
	ret = noti_ex_padding_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_padding_get_bottom(handle, &val);
	assert_eq_with_exit(val, 4);
	noti_ex_padding_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_padding_get_bottom_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_padding_get_bottom()
 */
int utc_noti_ex_padding_get_bottom_n(void)
{
	int ret;
	ret = noti_ex_padding_get_bottom(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_geometry_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_geometry_create()
 */
int utc_noti_ex_geometry_create_p(void)
{
	int ret;
	noti_ex_geometry_h handle;
	ret = noti_ex_geometry_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_geometry_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_geometry_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_geometry_create()
 */
int utc_noti_ex_geometry_create_n(void)
{
	int ret;
	ret = noti_ex_geometry_create(NULL, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_geometry_destroy_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_geometry_destroy()
 */
int utc_noti_ex_geometry_destroy_p(void)
{
	int ret;
	noti_ex_geometry_h handle;
	ret = noti_ex_geometry_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_geometry_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_geometry_destroy_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_geometry_destroy()
 */
int utc_noti_ex_geometry_destroy_n(void)
{
	int ret;
	ret = noti_ex_geometry_destroy(NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_geometry_get_x_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_geometry_get_x()
 */
int utc_noti_ex_geometry_get_x_p(void)
{
	int ret;
	int val;
	noti_ex_geometry_h handle;
	ret = noti_ex_geometry_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_geometry_get_x(handle, &val);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(1, val);
	noti_ex_geometry_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_geometry_get_x_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_geometry_get_x()
 */
int utc_noti_ex_geometry_get_x_n(void)
{
	int ret;
	ret = noti_ex_geometry_get_x(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_geometry_get_y_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_geometry_get_y()
 */
int utc_noti_ex_geometry_get_y_p(void)
{
	int ret;
	int val;
	noti_ex_geometry_h handle;
	ret = noti_ex_geometry_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_geometry_get_y(handle, &val);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(2, val);
	noti_ex_geometry_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_geometry_get_y_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_geometry_get_y()
 */
int utc_noti_ex_geometry_get_y_n(void)
{
	int ret;
	ret = noti_ex_geometry_get_y(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_geometry_get_width_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_geometry_get_width()
 */
int utc_noti_ex_geometry_get_width_p(void)
{
	int ret;
	int val;
	noti_ex_geometry_h handle;
	ret = noti_ex_geometry_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_geometry_get_width(handle, &val);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(3, val);
	noti_ex_geometry_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_geometry_get_width_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_geometry_get_width()
 */
int utc_noti_ex_geometry_get_width_n(void)
{
	int ret;
	ret = noti_ex_geometry_get_width(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_geometry_get_height_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_geometry_get_height()
 */
int utc_noti_ex_geometry_get_height_p(void)
{
	int ret;
	int val;
	noti_ex_geometry_h handle;
	ret = noti_ex_geometry_create(&handle, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_geometry_get_height(handle, &val);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(4, val);
	noti_ex_geometry_destroy(handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_geometry_get_height_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_geometry_get_height()
 */
int utc_noti_ex_geometry_get_height_n(void)
{
	int ret;
	ret = noti_ex_geometry_get_height(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_style_create()
 */
int utc_noti_ex_style_create_p(void)
{
	int ret;
	noti_ex_style_h handle;
	noti_ex_color_h color;
	noti_ex_padding_h padding;
	noti_ex_geometry_h geometry;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	noti_ex_padding_create(&padding, 1, 2, 3, 4);
	noti_ex_geometry_create(&geometry, 1, 2, 3, 4);
	ret = noti_ex_style_create(&handle, color, padding, geometry);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_style_destroy(handle);
	noti_ex_color_destroy(color);
	noti_ex_padding_destroy(padding);
	noti_ex_geometry_destroy(geometry);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_style_create()
 */
int utc_noti_ex_style_create_n(void)
{
	int ret;
	ret = noti_ex_style_create(NULL, NULL, NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_destroy_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_style_destroy()
 */
int utc_noti_ex_style_destroy_p(void)
{
	int ret;
	noti_ex_style_h handle;
	noti_ex_color_h color;
	noti_ex_padding_h padding;
	noti_ex_geometry_h geometry;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	noti_ex_padding_create(&padding, 1, 2, 3, 4);
	noti_ex_geometry_create(&geometry, 1, 2, 3, 4);
	ret = noti_ex_style_create(&handle, color, padding, geometry);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_style_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_color_destroy(color);
	noti_ex_padding_destroy(padding);
	noti_ex_geometry_destroy(geometry);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_destroy_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_style_destroy()
 */
int utc_noti_ex_style_destroy_n(void)
{
	int ret;
	ret = noti_ex_style_destroy(NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_get_padding_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_style_get_padding()
 */
int utc_noti_ex_style_get_padding_p(void)
{
	int ret;
	int left, top, right, bottom;
	int style_left, style_top, style_right, style_bottom;
	noti_ex_style_h handle;
	noti_ex_color_h color;
	noti_ex_padding_h padding;
	noti_ex_geometry_h geometry;
	noti_ex_padding_h style_padding;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	noti_ex_padding_create(&padding, 1, 2, 3, 4);
	noti_ex_geometry_create(&geometry, 1, 2, 3, 4);
	ret = noti_ex_style_create(&handle, color, padding, geometry);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_style_get_padding(handle, &style_padding);

	noti_ex_padding_get_left(padding, &left);
	noti_ex_padding_get_left(style_padding, &style_left);
	assert_eq_with_exit(left, style_left);

	noti_ex_padding_get_top(padding, &top);
	noti_ex_padding_get_top(style_padding, &style_top);
	assert_eq_with_exit(top, style_top);

	noti_ex_padding_get_right(padding, &right);
	noti_ex_padding_get_right(style_padding, &style_right);
	assert_eq_with_exit(right, style_right);

	noti_ex_padding_get_bottom(padding, &bottom);
	noti_ex_padding_get_bottom(style_padding, &style_bottom);
	assert_eq_with_exit(bottom, style_bottom);

	noti_ex_style_destroy(handle);
	noti_ex_color_destroy(color);
	noti_ex_padding_destroy(padding);
	noti_ex_geometry_destroy(geometry);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_get_padding_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_style_get_padding()
 */
int utc_noti_ex_style_get_padding_n(void)
{
	int ret;
	ret = noti_ex_style_get_padding(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_get_color_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_style_get_color()
 */
int utc_noti_ex_style_get_color_p(void)
{
	int ret;
	unsigned char a, r, g, b;
	unsigned char style_a, style_r, style_g, style_b;
	noti_ex_style_h handle;
	noti_ex_color_h color;
	noti_ex_padding_h padding;
	noti_ex_geometry_h geometry;
	noti_ex_color_h style_color;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	noti_ex_padding_create(&padding, 1, 2, 3, 4);
	noti_ex_geometry_create(&geometry, 1, 2, 3, 4);
	ret = noti_ex_style_create(&handle, color, padding, geometry);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_style_get_color(handle, &style_color);

	noti_ex_color_get_alpha(color, &a);
	noti_ex_color_get_alpha(style_color, &style_a);
	assert_eq_with_exit(a, style_a);

	noti_ex_color_get_red(color, &r);
	noti_ex_color_get_red(style_color, &style_r);
	assert_eq_with_exit(r, style_r);

	noti_ex_color_get_green(color, &g);
	noti_ex_color_get_green(style_color, &style_g);
	assert_eq_with_exit(g, style_g);

	noti_ex_color_get_blue(color, &b);
	noti_ex_color_get_blue(style_color, &style_b);
	assert_eq_with_exit(b, style_b);

	noti_ex_style_destroy(handle);
	noti_ex_color_destroy(color);
	noti_ex_padding_destroy(padding);
	noti_ex_geometry_destroy(geometry);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_get_color_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_style_get_color()
 */
int utc_noti_ex_style_get_color_n(void)
{
	int ret;
	ret = noti_ex_style_get_color(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_get_geometry_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_style_get_geometry()
 */
int utc_noti_ex_style_get_geometry_p(void)
{
	int ret;
	int h, w, x, y;
	int style_h, style_w, style_x, style_y;
	noti_ex_style_h handle;
	noti_ex_color_h color;
	noti_ex_padding_h padding;
	noti_ex_geometry_h geometry;
	noti_ex_geometry_h style_geometry;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	noti_ex_padding_create(&padding, 1, 2, 3, 4);
	noti_ex_geometry_create(&geometry, 1, 2, 3, 4);
	ret = noti_ex_style_create(&handle, color, padding, geometry);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_style_get_geometry(handle, &style_geometry);

	noti_ex_geometry_get_height(geometry, &h);
	noti_ex_geometry_get_height(style_geometry, &style_h);
	assert_eq_with_exit(h, style_h);

	noti_ex_geometry_get_width(geometry, &w);
	noti_ex_geometry_get_width(style_geometry, &style_w);
	assert_eq_with_exit(w, style_w);

	noti_ex_geometry_get_x(geometry, &x);
	noti_ex_geometry_get_x(style_geometry, &style_x);
	assert_eq_with_exit(x, style_x);

	noti_ex_geometry_get_y(geometry, &y);
	noti_ex_geometry_get_y(style_geometry, &style_y);
	assert_eq_with_exit(y, style_y);

	noti_ex_style_destroy(handle);
	noti_ex_color_destroy(color);
	noti_ex_padding_destroy(padding);
	noti_ex_geometry_destroy(geometry);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_get_geometry_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_style_get_geometry()
 */
int utc_noti_ex_style_get_geometry_n(void)
{
	int ret;
	ret = noti_ex_style_get_geometry(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_set_background_image_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_style_set_background_image()
 */
int utc_noti_ex_style_set_background_image_p(void)
{
	int ret;
	noti_ex_style_h handle = NULL;

	ret = noti_ex_style_create(&handle, NULL, NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_style_set_background_image(handle, "image_path");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_set_background_image_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_style_set_background_image()
 */
int utc_noti_ex_style_set_background_image_n(void)
{
	int ret;
	ret = noti_ex_style_set_background_image(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_get_background_image_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_style_get_background_image()
 */
int utc_noti_ex_style_get_background_image_p(void)
{
	int ret;
	noti_ex_style_h handle = NULL;
	char *path;

	ret = noti_ex_style_create(&handle, NULL, NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_style_set_background_image(handle, "image_path");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_style_get_background_image(handle, &path);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_get_background_image_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_style_get_background_image()
 */
int utc_noti_ex_style_get_background_image_n(void)
{
	int ret;
	ret = noti_ex_style_get_background_image(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_set_background_color_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_style_set_background_color()
 */
int utc_noti_ex_style_set_background_color_p(void)
{
	int ret;
	noti_ex_style_h handle = NULL;
	noti_ex_color_h color = NULL;

	ret = noti_ex_style_create(&handle, NULL, NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_color_create(&color, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_style_set_background_color(handle, color);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_set_background_color_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_style_set_background_color()
 */
int utc_noti_ex_style_set_background_color_n(void)
{
	int ret;
	ret = noti_ex_style_set_background_color(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_get_background_color_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_style_get_background_color()
 */
int utc_noti_ex_style_get_background_color_p(void)
{
	int ret;
	noti_ex_style_h handle = NULL;
	noti_ex_color_h color = NULL;
	noti_ex_color_h color_ = NULL;

	ret = noti_ex_style_create(&handle, NULL, NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_color_create(&color, 1, 2, 3, 4);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_style_set_background_color(handle, color);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_style_get_background_color(handle, &color_);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_style_get_background_color_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_style_get_background_color()
 */
int utc_noti_ex_style_get_background_color_n(void)
{
	int ret;
	ret = noti_ex_style_get_background_color(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_led_info_create()
 */
int utc_noti_ex_led_info_create_p(void)
{
	int ret;
	noti_ex_led_info_h handle;
	noti_ex_color_h color;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	ret = noti_ex_led_info_create(&handle, color);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_led_info_create()
 */
int utc_noti_ex_led_info_create_n(void)
{
	int ret;
	ret = noti_ex_led_info_create(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_destroy_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_led_info_destroy()
 */
int utc_noti_ex_led_info_destroy_p(void)
{
	int ret;
	noti_ex_led_info_h handle;
	noti_ex_color_h color;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	ret = noti_ex_led_info_create(&handle, color);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_destroy_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_led_info_destroy()
 */
int utc_noti_ex_led_info_destroy_n(void)
{
	int ret;
	ret = noti_ex_led_info_destroy(NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_set_on_period_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_led_info_set_on_period()
 */
int utc_noti_ex_led_info_set_on_period_p(void)
{
	int ret;
	noti_ex_led_info_h handle;
	noti_ex_color_h color;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	ret = noti_ex_led_info_create(&handle, color);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_led_info_set_on_period(handle, 5);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_set_on_period_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_led_info_set_on_period()
 */
int utc_noti_ex_led_info_set_on_period_n(void)
{
	int ret;
	ret = noti_ex_led_info_set_on_period(NULL, 5);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_get_on_period_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_led_info_get_on_period()
 */
int utc_noti_ex_led_info_get_on_period_p(void)
{
	int ret;
	noti_ex_led_info_h handle;
	noti_ex_color_h color;
	int ms;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	ret = noti_ex_led_info_create(&handle, color);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_led_info_set_on_period(handle, 5);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_led_info_get_on_period(handle, &ms);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(ms, 5);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_get_on_period_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_led_info_get_on_period()
 */
int utc_noti_ex_led_info_get_on_period_n(void)
{
	int ret;
	ret = noti_ex_led_info_get_on_period(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}


/**
 * @testcase utc_noti_ex_led_info_set_off_period_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_led_info_set_off_period()
 */
int utc_noti_ex_led_info_set_off_period_p(void)
{
	int ret;
	noti_ex_led_info_h handle;
	noti_ex_color_h color;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	ret = noti_ex_led_info_create(&handle, color);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_led_info_set_off_period(handle, 5);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_set_off_period_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_led_info_set_off_period()
 */
int utc_noti_ex_led_info_set_off_period_n(void)
{
	int ret;
	ret = noti_ex_led_info_set_off_period(NULL, 5);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_get_off_period_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_led_info_get_off_period()
 */
int utc_noti_ex_led_info_get_off_period_p(void)
{
	int ret;
	noti_ex_led_info_h handle;
	noti_ex_color_h color;
	int ms;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	ret = noti_ex_led_info_create(&handle, color);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_led_info_set_off_period(handle, 5);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_led_info_get_off_period(handle, &ms);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(ms, 5);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_get_off_period_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_led_info_get_off_period()
 */
int utc_noti_ex_led_info_get_off_period_n(void)
{
	int ret;
	ret = noti_ex_led_info_get_off_period(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_get_color_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_led_info_get_color()
 */
int utc_noti_ex_led_info_get_color_p(void)
{
	int ret;
	noti_ex_led_info_h handle;
	noti_ex_color_h color;
	noti_ex_color_h ret_color;
	unsigned char a, r, g, b;
	unsigned char ret_a, ret_r, ret_g, ret_b;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	ret = noti_ex_led_info_create(&handle, color);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_led_info_get_color(handle, &ret_color);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	noti_ex_color_get_alpha(color, &a);
	noti_ex_color_get_alpha(ret_color, &ret_a);
	assert_eq_with_exit(a, ret_a);

	noti_ex_color_get_red(color, &r);
	noti_ex_color_get_red(ret_color, &ret_r);
	assert_eq_with_exit(r, ret_r);

	noti_ex_color_get_green(color, &g);
	noti_ex_color_get_green(ret_color, &ret_g);
	assert_eq_with_exit(g, ret_g);

	noti_ex_color_get_blue(color, &b);
	noti_ex_color_get_blue(ret_color, &ret_b);
	assert_eq_with_exit(b, ret_b);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_led_info_get_color_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_led_info_get_color()
 */
int utc_noti_ex_led_info_get_color_n(void)
{
	int ret;
	ret = noti_ex_led_info_get_color(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_destroy_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_action_destroy()
 */
int utc_noti_ex_action_destroy_p(void)
{
	int ret;
	noti_ex_action_h handle;

	noti_ex_action_visibility_create(&handle, NULL);
	ret = noti_ex_action_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_destroy_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_action_destroy()
 */
int utc_noti_ex_action_destroy_n(void)
{
	int ret;
	ret = noti_ex_action_destroy(NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_get_type_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_action_get_type()
 */
int utc_noti_ex_action_get_type_p(void)
{
	int ret;
	int type;
	noti_ex_action_h handle;

	noti_ex_action_visibility_create(&handle, NULL);
	ret = noti_ex_action_get_type(handle, &type);
	assert_eq_with_exit(type, NOTI_EX_ACTION_TYPE_VISIBILITY);
	ret = noti_ex_action_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_get_type_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_action_get_type()
 */
int utc_noti_ex_action_get_type_n(void)
{
	int ret;
	ret = noti_ex_action_get_type(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_is_local_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_action_is_local()
 */
int utc_noti_ex_action_is_local_p(void)
{
	int ret;
	noti_ex_action_h handle;
	bool is_local;

	noti_ex_action_visibility_create(&handle, NULL);
	ret = noti_ex_action_is_local(handle, &is_local);
	assert_eq_with_exit(is_local, true);
	ret = noti_ex_action_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_is_local_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_action_is_local()
 */
int utc_noti_ex_action_is_local_n(void)
{
	int ret;
	ret = noti_ex_action_is_local(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_execute_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_action_execute()
 */
int utc_noti_ex_action_execute_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_action_h action = NULL;

	ret = noti_ex_action_visibility_create(&action, NULL);
	ret = noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_action(button_item, action);

	ret = noti_ex_action_execute(action, button_item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_execute_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_action_execute()
 */
int utc_noti_ex_action_execute_n(void)
{
	int ret;
	ret = noti_ex_action_execute(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_get_extra_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_action_get_extra()
 */
int utc_noti_ex_action_get_extra_p(void)
{
	int ret;
	noti_ex_action_h handle;
	char *extra;

	noti_ex_action_visibility_create(&handle, "test");
	ret = noti_ex_action_get_extra(handle, &extra);
	assert_eq_with_exit(strcmp(extra, "test"), 0);
	ret = noti_ex_action_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_get_extra_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_action_get_extra()
 */
int utc_noti_ex_action_get_extra_n(void)
{
	int ret;
	ret = noti_ex_action_get_extra(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_info_get_hide_time_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_info_get_hide_time()
 */
int utc_noti_ex_item_info_get_hide_time_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_item_info_h item_info = NULL;
	int hide_time;

	ret = noti_ex_item_button_create(&button_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_info(button_item, &item_info);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_info_set_hide_time(item_info, 10);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_info_get_hide_time(item_info, &hide_time);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(hide_time, 10);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_info_get_hide_time_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_info_get_hide_time()
 */
int utc_noti_ex_item_info_get_hide_time_n(void)
{
	int ret;
	ret = noti_ex_item_info_get_hide_time(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_info_set_hide_time_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_info_set_hide_time()
 */
int utc_noti_ex_item_info_set_hide_time_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_item_info_h item_info = NULL;

	ret = noti_ex_item_button_create(&button_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_info(button_item, &item_info);
	ret = noti_ex_item_info_set_hide_time(item_info, 10);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_info_set_hide_time_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_info_set_hide_time()
 */
int utc_noti_ex_item_info_set_hide_time_n(void)
{
	int ret;
	ret = noti_ex_item_info_set_hide_time(NULL, 10);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_info_get_delete_time_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_info_get_delete_time()
 */
int utc_noti_ex_item_info_get_delete_time_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_item_info_h item_info = NULL;
	int delete_time;

	ret = noti_ex_item_button_create(&button_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_info(button_item, &item_info);
	ret = noti_ex_item_info_set_delete_time(item_info, 10);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_info_get_delete_time(item_info, &delete_time);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(delete_time, 10);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_info_get_delete_time_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_info_get_delete_time()
 */
int utc_noti_ex_item_info_get_delete_time_n(void)
{
	int ret;
	ret = noti_ex_item_info_get_delete_time(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_info_set_delete_time_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_info_set_delete_time()
 */
int utc_noti_ex_item_info_set_delete_time_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_item_info_h item_info = NULL;

	ret = noti_ex_item_button_create(&button_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_info(button_item, &item_info);
	ret = noti_ex_item_info_set_delete_time(item_info, 10);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_info_set_delete_time_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_info_set_delete_time()
 */
int utc_noti_ex_item_info_set_delete_time_n(void)
{
	int ret;
	ret = noti_ex_item_info_set_delete_time(NULL, 10);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_info_get_time_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_info_get_time()
 */
int utc_noti_ex_item_info_get_time_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_item_info_h item_info = NULL;
	time_t t;

	ret = noti_ex_item_button_create(&button_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_info(button_item, &item_info);
	ret = noti_ex_item_info_get_time(item_info, &t);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_info_get_time_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_info_get_time()
 */
int utc_noti_ex_item_info_get_time_n(void)
{
	int ret;
	ret = noti_ex_item_info_get_time(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}


/**
 * @testcase utc_noti_ex_item_destroy_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_destroy()
 */
int utc_noti_ex_item_destroy_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;

	ret = noti_ex_item_button_create(&button_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_destroy(button_item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_destroy_p_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_destroy()
 */
int utc_noti_ex_item_destroy_p_n(void)
{
	int ret;
	ret = noti_ex_item_destroy(NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_find_by_id_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_find_by_id()
 */
int utc_noti_ex_item_find_by_id_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_item_h find_item = NULL;
	noti_ex_item_h group_item = NULL;
	char *find_id;
	char *id;

	noti_ex_item_group_create(&group_item, "group_id");
	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_group_add_child(group_item, button_item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_find_by_id(group_item, "button_id", &find_item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_item_get_id(find_item, &find_id);
	noti_ex_item_get_id(button_item, &id);
	assert_eq_with_exit(strcmp(id, find_id), 0);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_find_by_id_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_find_by_id()
 */
int utc_noti_ex_item_find_by_id_n(void)
{
	int ret;
	ret = noti_ex_item_find_by_id(NULL, NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_type_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_type()
 */
int utc_noti_ex_item_get_type_p(void)
{
	int ret;
	int type;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_get_type(button_item, &type);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(type, NOTI_EX_ITEM_TYPE_BUTTON);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_type_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_type()
 */
int utc_noti_ex_item_get_type_n(void)
{
	int ret;
	ret = noti_ex_item_get_type(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_id_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_id()
 */
int utc_noti_ex_item_get_id_p(void)
{
	int ret;
	char *id;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_get_id(button_item, &id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_id_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_id()
 */
int utc_noti_ex_item_get_id_n(void)
{
	int ret;
	ret = noti_ex_item_get_id(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_id_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_id()
 */
int utc_noti_ex_item_set_id_p(void)
{
	int ret;
	char *id;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_id(button_item, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_id(button_item, &id);
	assert_eq_with_exit(strcmp(id, "test"), 0);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_id_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_id()
 */
int utc_noti_ex_item_set_id_n(void)
{
	int ret;
	ret = noti_ex_item_set_id(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_action_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_action()
 */
int utc_noti_ex_item_get_action_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_action_h action = NULL;
	noti_ex_action_h ret_action = NULL;

	noti_ex_action_visibility_create(&action, NULL);
	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_action(button_item, action);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_action(button_item, &ret_action);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_action_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_action()
 */
int utc_noti_ex_item_get_action_n(void)
{
	int ret;
	ret = noti_ex_item_get_action(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_action_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_action()
 */
int utc_noti_ex_item_set_action_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_action_h action = NULL;

	noti_ex_action_visibility_create(&action, NULL);
	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_action(button_item, action);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_action_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_action()
 */
int utc_noti_ex_item_set_action_n(void)
{
	int ret;
	ret = noti_ex_item_set_action(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_style_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_style()
 */
int utc_noti_ex_item_get_style_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_style_h style = NULL;
	noti_ex_style_h ret_style = NULL;

	noti_ex_color_h color;
	noti_ex_padding_h padding;
	noti_ex_padding_h ret_padding;
	noti_ex_geometry_h geometry;
	int left, top, right, bottom;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	noti_ex_padding_create(&padding, 1, 2, 3, 4);
	noti_ex_geometry_create(&geometry, 1, 2, 3, 4);
	ret = noti_ex_style_create(&style, color, padding, geometry);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_item_button_create(&button_item, "button_id", "button_title");

	ret = noti_ex_item_set_style(button_item, style);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_style(button_item, &ret_style);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_style_get_padding(ret_style, &ret_padding);

	noti_ex_padding_get_left(ret_padding, &left);
	assert_eq_with_exit(left, 1);

	noti_ex_padding_get_top(ret_padding, &top);
	assert_eq_with_exit(top, 2);

	noti_ex_padding_get_right(ret_padding, &right);
	assert_eq_with_exit(right, 3);

	noti_ex_padding_get_bottom(ret_padding, &bottom);
	assert_eq_with_exit(bottom, 4);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_style_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_style()
 */
int utc_noti_ex_item_get_style_n(void)
{
	int ret;
	ret = noti_ex_item_get_style(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_style_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_style()
 */
int utc_noti_ex_item_set_style_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_style_h style = NULL;

	noti_ex_color_h color;
	noti_ex_padding_h padding;
	noti_ex_geometry_h geometry;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	noti_ex_padding_create(&padding, 1, 2, 3, 4);
	noti_ex_geometry_create(&geometry, 1, 2, 3, 4);
	ret = noti_ex_style_create(&style, color, padding, geometry);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_item_button_create(&button_item, "button_id", "button_title");

	ret = noti_ex_item_set_style(button_item, style);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_style_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_style()
 */
int utc_noti_ex_item_set_style_n(void)
{
	int ret;
	ret = noti_ex_item_get_style(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_visible_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_visible()
 */
int utc_noti_ex_item_set_visible_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_visible(button_item, true);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_visible_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_visible()
 */
int utc_noti_ex_item_set_visible_n(void)
{
	int ret;
	ret = noti_ex_item_set_visible(NULL, true);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_visible_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_visible()
 */
int utc_noti_ex_item_get_visible_p(void)
{
	int ret;
	bool visible;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_visible(button_item, true);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_visible(button_item, &visible);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(true, visible);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_visible_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_visible()
 */
int utc_noti_ex_item_get_visible_n(void)
{
	int ret;
	ret = noti_ex_item_get_visible(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_enable_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_enable()
 */
int utc_noti_ex_item_set_enable_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_enable(button_item, true);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_enable_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_enable()
 */
int utc_noti_ex_item_set_enable_n(void)
{
	int ret;
	ret = noti_ex_item_set_enable(NULL, true);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_enable_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_enable()
 */
int utc_noti_ex_item_get_enable_p(void)
{
	int ret;
	bool enable;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_enable(button_item, true);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_enable(button_item, &enable);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(true, enable);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_enable_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_enable()
 */
int utc_noti_ex_item_get_enable_n(void)
{
	int ret;
	ret = noti_ex_item_get_enable(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_add_receiver_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_add_receiver()
 */
int utc_noti_ex_item_add_receiver_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_add_receiver(button_item, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_add_receiver_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_add_receiver()
 */
int utc_noti_ex_item_add_receiver_n(void)
{
	int ret;
	ret = noti_ex_item_add_receiver(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_receiver_list_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_receiver_list()
 */
int utc_noti_ex_item_get_receiver_list_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	char **list = NULL;
	int count;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_add_receiver(button_item, "test1");
	ret = noti_ex_item_add_receiver(button_item, "test2");
	noti_ex_item_get_receiver_list(button_item, &list, &count);
	assert_eq_with_exit(2, count);

	ret = noti_ex_item_remove_receiver(button_item, "test1");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_item_get_receiver_list(button_item, &list, &count);
	assert_eq_with_exit(1, count);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_receiver_list_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_receiver_list()
 */
int utc_noti_ex_item_get_receiver_list_n(void)
{
	int ret;
	ret = noti_ex_item_get_receiver_list(NULL, NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_remove_receiver_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_remove_receiver()
 */
int utc_noti_ex_item_remove_receiver_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	char **list = NULL;
	int count;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_add_receiver(button_item, "test1");
	ret = noti_ex_item_add_receiver(button_item, "test2");
	noti_ex_item_get_receiver_list(button_item, &list, &count);
	assert_eq_with_exit(2, count);

	ret = noti_ex_item_remove_receiver(button_item, "test1");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	noti_ex_item_get_receiver_list(button_item, &list, &count);
	assert_eq_with_exit(1, count);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_remove_receiver_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_remove_receiver()
 */
int utc_noti_ex_item_remove_receiver_n(void)
{
	int ret;
	ret = noti_ex_item_remove_receiver(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_policy_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_policy()
 */
int utc_noti_ex_item_set_policy_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_policy(button_item, NOTI_EX_ITEM_POLICY_SIM_MODE);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_policy_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_policy()
 */
int utc_noti_ex_item_set_policy_n(void)
{
	int ret;
	ret = noti_ex_item_set_policy(NULL, NOTI_EX_ITEM_POLICY_SIM_MODE);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_policy_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_policy()
 */
int utc_noti_ex_item_get_policy_p(void)
{
	int ret;
	int policy;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_policy(button_item, NOTI_EX_ITEM_POLICY_SIM_MODE);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_policy(button_item, &policy);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(NOTI_EX_ITEM_POLICY_SIM_MODE, policy);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_policy_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_policy()
 */
int utc_noti_ex_item_get_policy_n(void)
{
	int ret;
	ret = noti_ex_item_get_policy(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_channel_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_channel()
 */
int utc_noti_ex_item_set_channel_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_channel(button_item, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_channel_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_channel()
 */
int utc_noti_ex_item_set_channel_n(void)
{
	int ret;
	ret = noti_ex_item_set_channel(NULL, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_channel_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_channel()
 */
int utc_noti_ex_item_get_channel_p(void)
{
	int ret;
	char *channel;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_channel(button_item, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_channel(button_item, &channel);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(strcmp(channel, "test"), 0);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_channel_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_channel()
 */
int utc_noti_ex_item_get_channel_n(void)
{
	int ret;
	ret = noti_ex_item_get_channel(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_led_info_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_led_info()
 */
int utc_noti_ex_item_set_led_info_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_led_info_h led_info;
	noti_ex_color_h color;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	ret = noti_ex_led_info_create(&led_info, color);

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_led_info(button_item, led_info);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_led_info_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_led_info()
 */
int utc_noti_ex_item_set_led_info_n(void)
{
	int ret;
	ret = noti_ex_item_set_led_info(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_led_info_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_led_info()
 */
int utc_noti_ex_item_get_led_info_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_led_info_h led_info;
	noti_ex_led_info_h ret_led_info;
	noti_ex_color_h color;

	noti_ex_color_create(&color, 1, 2, 3, 4);
	ret = noti_ex_led_info_create(&led_info, color);

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_led_info(button_item, led_info);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_led_info(button_item, &ret_led_info);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_led_info_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_led_info()
 */
int utc_noti_ex_item_get_led_info_n(void)
{
	int ret;
	ret = noti_ex_item_get_led_info(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}


/**
 * @testcase utc_noti_ex_item_set_sound_path_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_sound_path()
 */
int utc_noti_ex_item_set_sound_path_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_sound_path(button_item, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_sound_path_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_sound_path()
 */
int utc_noti_ex_item_set_sound_path_n(void)
{
	int ret;
	ret = noti_ex_item_set_sound_path(NULL, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_sound_path_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_sound_path()
 */
int utc_noti_ex_item_get_sound_path_p(void)
{
	int ret;
	char *sound_path;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_sound_path(button_item, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_sound_path(button_item, &sound_path);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(strcmp(sound_path, "test"), 0);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_sound_path_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_sound_path()
 */
int utc_noti_ex_item_get_sound_path_n(void)
{
	int ret;
	ret = noti_ex_item_get_sound_path(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_vibration_path_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_vibration_path()
 */
int utc_noti_ex_item_set_vibration_path_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_vibration_path(button_item, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_vibration_path_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_vibration_path()
 */
int utc_noti_ex_item_set_vibration_path_n(void)
{
	int ret;
	ret = noti_ex_item_set_vibration_path(NULL, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_vibration_path_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_vibration_path()
 */
int utc_noti_ex_item_get_vibration_path_p(void)
{
	int ret;
	char *vibration_path;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_vibration_path(button_item, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_vibration_path(button_item, &vibration_path);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(strcmp(vibration_path, "test"), 0);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_vibration_path_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_vibration_path()
 */
int utc_noti_ex_item_get_vibration_path_n(void)
{
	int ret;
	ret = noti_ex_item_get_vibration_path(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_info_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_info()
 */
int utc_noti_ex_item_get_info_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_item_info_h item_info = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_get_info(button_item, &item_info);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_info_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_info()
 */
int utc_noti_ex_item_get_info_n(void)
{
	int ret;
	ret = noti_ex_item_get_info(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_sender_app_id_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_sender_app_id()
 */
int utc_noti_ex_item_get_sender_app_id_p(void)
{
	int ret;
	char *sender_app_id;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_get_sender_app_id(button_item, &sender_app_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_sender_app_id_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_sender_app_id()
 */
int utc_noti_ex_item_get_sender_app_id_n(void)
{
	int ret;
	ret = noti_ex_item_get_sender_app_id(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_tag_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_tag()
 */
int utc_noti_ex_item_set_tag_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_tag(button_item, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_tag_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_tag()
 */
int utc_noti_ex_item_set_tag_n(void)
{
	int ret;
	ret = noti_ex_item_set_tag(NULL, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_tag_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_tag()
 */
int utc_noti_ex_item_get_tag_p(void)
{
	int ret;
	char *tag;
	noti_ex_item_h button_item = NULL;

	noti_ex_item_button_create(&button_item, "button_id", "button_title");
	ret = noti_ex_item_set_tag(button_item, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_tag(button_item, &tag);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(strcmp(tag, "test"), 0);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_tag_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_tag()
 */
int utc_noti_ex_item_get_tag_n(void)
{
	int ret;
	ret = noti_ex_item_get_tag(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_ongoing_state_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_ongoing_state()
 */
int utc_noti_ex_item_set_ongoing_state_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;

	ret = noti_ex_item_button_create(&button_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_set_ongoing_state(button_item, true);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_ongoing_state_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_ongoing_state()
 */
int utc_noti_ex_item_set_ongoing_state_n(void)
{
	int ret;
	ret = noti_ex_item_set_ongoing_state(NULL, false);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_ongoing_state_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_ongoing_state()
 */
int utc_noti_ex_item_get_ongoing_state_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	bool state = false;

	ret = noti_ex_item_button_create(&button_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_set_ongoing_state(button_item, true);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_get_ongoing_state(button_item, &state);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_ongoing_state_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_ongoing_state()
 */
int utc_noti_ex_item_get_ongoing_state_n(void)
{
	int ret;
	ret = noti_ex_item_get_ongoing_state(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_check_type_exist_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_check_type_exist()
 */
int utc_noti_ex_item_check_type_exist_p(void)
{
	int ret;
	noti_ex_item_h button_item = NULL;
	noti_ex_item_h item_handle = NULL;
	bool exist = false;

	ret = noti_ex_item_group_create(&item_handle, "group_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_button_create(&button_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_group_add_child(item_handle, button_item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_check_type_exist(item_handle, NOTI_EX_ITEM_TYPE_BUTTON, &exist);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_check_type_exist_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_check_type_exist()
 */
int utc_noti_ex_item_check_type_exist_n(void)
{
	int ret;
	ret = noti_ex_item_check_type_exist(NULL, NOTI_EX_ITEM_MAIN_TYPE_NONE, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_main_type_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_set_main_type()
 */
int utc_noti_ex_item_set_main_type_p(void)
{
	int ret;
	noti_ex_item_h handle;

	ret = noti_ex_item_text_create(&handle, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_set_main_type(handle, "text_id", NOTI_EX_ITEM_MAIN_TYPE_TITLE);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_main_type_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_main_type()
 */
int utc_noti_ex_item_set_main_type_n(void)
{
	int ret;
	ret = noti_ex_item_set_main_type(NULL, NULL, NOTI_EX_ITEM_MAIN_TYPE_NONE);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_main_type_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_main_type()
 */
int utc_noti_ex_item_get_main_type_p(void)
{
	int ret;
	noti_ex_item_h handle;
	int type = 0;

	ret = noti_ex_item_text_create(&handle, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_set_main_type(handle, "text_id", NOTI_EX_ITEM_MAIN_TYPE_TITLE);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_get_main_type(handle, &type);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_main_type_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_main_type()
 */
int utc_noti_ex_item_get_main_type_n(void)
{
	int ret;
	ret = noti_ex_item_get_main_type(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_find_by_main_type_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_find_by_main_type()
 */
int utc_noti_ex_item_find_by_main_type_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	noti_ex_item_h text_item = NULL;
	noti_ex_item_h button_item = NULL;
	noti_ex_item_h handle = NULL;

	ret = noti_ex_item_group_create(&item_handle, "group_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_text_create(&text_item, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_group_add_child(item_handle, text_item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_button_create(&button_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_group_add_child(item_handle, button_item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_set_main_type(item_handle, "text_id", NOTI_EX_ITEM_MAIN_TYPE_TITLE);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);


	ret = noti_ex_item_find_by_main_type(item_handle, NOTI_EX_ITEM_MAIN_TYPE_TITLE, &handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_find_by_main_type_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_find_by_main_type()
 */
int utc_noti_ex_item_find_by_main_type_n(void)
{
	int ret;
	ret = noti_ex_item_find_by_main_type(NULL, NOTI_EX_ITEM_MAIN_TYPE_NONE, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_extension_data_n1
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_extension_data()
*/
int utc_noti_ex_item_get_extension_data_n1(void)
{
	int ret;
	bundle *value;

	ret = noti_ex_item_get_extension_data(NULL, "key", &value);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_extension_data_n2
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_extension_data()
*/
int utc_noti_ex_item_get_extension_data_n2(void)
{
	noti_ex_item_h text_item = NULL;
	int ret;
	bundle *value;

	ret = noti_ex_item_text_create(&text_item, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_get_extension_data(text_item, NULL, &value);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_extension_data_n3
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_get_extension_data()
*/
int utc_noti_ex_item_get_extension_data_n3(void)
{
	noti_ex_item_h text_item = NULL;
	int ret;

	ret = noti_ex_item_text_create(&text_item, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_get_extension_data(text_item, "key", NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_get_extension_data_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_get_extension_data()
*/
int utc_noti_ex_item_get_extension_data_p(void)
{
	noti_ex_item_h text_item = NULL;
	int ret;

	bundle *r_value = NULL;
	bundle *value = bundle_create();
	bundle_add_str(value, "TEST_KEY", "TEST_VALUE");

	ret = noti_ex_item_text_create(&text_item, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_set_extension_data(text_item, "key", value);
	bundle_free(value);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_get_extension_data(text_item, "key", &r_value);
	bundle_free(r_value);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	noti_ex_item_destroy(text_item);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_extension_data_n1
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_extension_data()
*/
int utc_noti_ex_item_set_extension_data_n1(void)
{
	int ret;

	bundle *value = bundle_create();
	bundle_add_str(value, "TEST_KEY", "TEST_VALUE");

	ret = noti_ex_item_set_extension_data(NULL, "key", value);
	bundle_free(value);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_extension_data_n2
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_extension_data()
*/
int utc_noti_ex_item_set_extension_data_n2(void)
{
	noti_ex_item_h text_item = NULL;
	int ret;

	bundle *value = bundle_create();
	bundle_add_str(value, "TEST_KEY", "TEST_VALUE");

	ret = noti_ex_item_text_create(&text_item, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_set_extension_data(text_item, NULL, value);
	bundle_free(value);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_extension_data_n3
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_extension_data()
*/
int utc_noti_ex_item_set_extension_data_n3(void)
{
	noti_ex_item_h text_item = NULL;
	int ret;

	ret = noti_ex_item_text_create(&text_item, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_set_extension_data(text_item, "key", NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_set_extension_data_p
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_set_extension_data()
*/
int utc_noti_ex_item_set_extension_data_p(void)
{
	noti_ex_item_h text_item = NULL;
	int ret;

	bundle *value = bundle_create();
	bundle_add_str(value, "TEST_KEY", "TEST_VALUE");

	ret = noti_ex_item_text_create(&text_item, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_set_extension_data(text_item, "key", value);
	bundle_free(value);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	noti_ex_item_destroy(text_item);
	normal_exit(0);
}
