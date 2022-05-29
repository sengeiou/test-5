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
#include <app.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <libintl.h>
#include <notification.h>
#include "utc-notification.h"

//& set: Notification

#define TEST_PKG "org.tizen.tetware"
#define TEST_TEXT "test"
#define TEST_UPDATE "updated"
#define TEST_APP "org.tizen.app"
#define TEST_PATH "path"
#define TEST_IMAGE "test.png"
#define TEST_INT 10
#define TEST_DOUBLE 0.5
#define TEST_TIME 0xFFFFFFF
#define TEST_TAG_FOR_NOTI    "TAG1_NOTI"
#define TEST_TAG_FOR_ONGOING "TAG1_ONGOING"

/**
 * @function		utc_notification_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_notification_startup(void)
{
	notification_h notification = NULL;

	/* NOTIFICATION_TYPE_NOTI */
	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	notification_set_time(notification, TEST_TIME);
	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_ICON, TEST_IMAGE);
	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_THUMBNAIL, TEST_IMAGE);
	notification_set_tag(notification, TEST_TAG_FOR_NOTI);
	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, time(NULL));
	notification_set_sound(notification, NOTIFICATION_SOUND_TYPE_USER_DATA, TEST_PATH);
	notification_set_layout(notification, NOTIFICATION_LY_NOTI_EVENT_SINGLE);
	notification_set_progress(notification, TEST_DOUBLE);
	notification_set_size(notification, TEST_DOUBLE);
	notification_set_display_applist(notification, NOTIFICATION_DISPLAY_APP_ALL);
	notification_set_property(notification, NOTIFICATION_PROP_DISABLE_AUTO_DELETE);
	notification_set_led_time_period(notification, TEST_INT, TEST_INT);
	notification_set_led(notification, NOTIFICATION_LED_OP_ON, 0);
	notification_set_vibration(notification, NOTIFICATION_VIBRATION_TYPE_USER_DATA, TEST_PATH);
	notification_post(notification);
	notification_free(notification);

	/* NOTIFICATION_TYPE_ONGOING */
	notification = notification_create(NOTIFICATION_TYPE_ONGOING);
	notification_set_time(notification, TEST_TIME);
	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_ICON, TEST_IMAGE);
	notification_set_tag(notification, TEST_TAG_FOR_ONGOING);
	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, time(NULL));
	notification_set_sound(notification, NOTIFICATION_SOUND_TYPE_USER_DATA, TEST_PATH);
	notification_set_layout(notification, NOTIFICATION_LY_NOTI_EVENT_SINGLE);
	notification_set_progress(notification, TEST_DOUBLE);
	notification_set_size(notification, TEST_DOUBLE);
	notification_set_display_applist(notification, NOTIFICATION_DISPLAY_APP_ALL);
	notification_set_property(notification, NOTIFICATION_PROP_DISABLE_AUTO_DELETE);
	notification_set_led_time_period(notification, TEST_INT, TEST_INT);
	notification_set_led(notification, NOTIFICATION_LED_OP_ON, 0);
	notification_set_vibration(notification, NOTIFICATION_VIBRATION_TYPE_USER_DATA, TEST_PATH);
	notification_post(notification);
	notification_free(notification);
}

/**
 * @function		utc_notification_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_notification_cleanup(void)
{
	notification_h notification = NULL;
	notification_h notification_ongoing = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);
	if (notification) {
		notification_delete(notification);
		notification_free(notification);
	}

	notification_ongoing = notification_load_by_tag(TEST_TAG_FOR_ONGOING);
	if (notification_ongoing) {
		notification_delete(notification_ongoing);
		notification_free(notification_ongoing);
	}
}

/**
 * @testcase		utc_notification_create_1_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_create()
 */
int utc_notification_create_1_n(void)
{
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NONE);

	assert(!notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_create_2_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_create()
 */
int utc_notification_create_2_n(void)
{
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_ONGOING + 1);

	assert(!notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_create_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_create()
 */
int utc_notification_create_1_p(void)
{
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_free(notification);
	normal_exit(0);
}

/**
 * @testcase		utc_notification_create_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_create()
 */
int utc_notification_create_2_p(void)
{
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_ONGOING);

	assert(notification);

	notification_free(notification);
	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_image()
 */
int utc_notification_set_image_n(void)
{
	int ret = 0;

	ret = notification_set_image(NULL, NOTIFICATION_IMAGE_TYPE_ICON, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_image()
 */
int utc_notification_set_image_1_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_ICON, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);
	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_ICON_FOR_INDICATOR
 */
int utc_notification_set_image_2_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_ICON_FOR_INDICATOR, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);
	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_3_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_ICON_FOR_LOCK
 */
int utc_notification_set_image_3_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_ICON_FOR_LOCK, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);
	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_4_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_THUMBNAIL
 */
int utc_notification_set_image_4_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_THUMBNAIL, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_5_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_THUMBNAIL_FOR_LOCK
 */
int utc_notification_set_image_5_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_THUMBNAIL_FOR_LOCK, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_6_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_ICON_SUB
 */
int utc_notification_set_image_6_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_ICON_SUB, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_7_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_BACKGROUND
 */
int utc_notification_set_image_7_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BACKGROUND, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_8_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_LIST_1
 */
int utc_notification_set_image_8_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_1, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_9_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_LIST_2
 */
int utc_notification_set_image_9_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_2, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_10_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_LIST_3
 */
int utc_notification_set_image_10_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_3, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_11_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_LIST_4
 */
int utc_notification_set_image_11_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_4, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_12_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_LIST_5
 */
int utc_notification_set_image_12_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_5, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_13_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_1
 */
int utc_notification_set_image_13_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_1, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_14_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_2
 */
int utc_notification_set_image_14_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_2, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_15_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_3
 */
int utc_notification_set_image_15_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_3, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_16_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_4
 */
int utc_notification_set_image_16_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_4, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_17_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_5
 */
int utc_notification_set_image_17_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_5, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_18_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_6
 */
int utc_notification_set_image_18_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_6, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_19_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_ICON
 */
int utc_notification_set_image_19_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	char img_path[128];
	char *res_path = NULL;

	res_path = app_get_resource_path();
	snprintf(img_path, sizeof(img_path), "%s/%s", res_path, "notification_icon.png");

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_ICON, img_path);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_post(notification);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_delete(notification);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_20_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_7
 */
int utc_notification_set_image_20_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_7, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_21_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_8
 */
int utc_notification_set_image_21_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_8, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_22_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_9
 */
int utc_notification_set_image_22_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_9, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_image_23_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_set_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_10
 */
int utc_notification_set_image_23_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_10, TEST_IMAGE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_image()
 */
int utc_notification_get_image_n(void)
{
	int ret = 0;

	ret = notification_get_image(NULL, NOTIFICATION_IMAGE_TYPE_ICON, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image()
 */
int utc_notification_get_image_1_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_THUMBNAIL, &image);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_eq_with_exit(strcmp(image, TEST_IMAGE), 0);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_ICON
 */
int utc_notification_get_image_2_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_ICON, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_ICON, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_3_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_ICON_FOR_INDICATOR
 */
int utc_notification_get_image_3_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_ICON_FOR_INDICATOR, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_ICON_FOR_INDICATOR, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_4_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_ICON_FOR_LOCK
 */
int utc_notification_get_image_4_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_ICON_FOR_LOCK, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_ICON_FOR_LOCK, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_5_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_THUMBNAIL
 */
int utc_notification_get_image_5_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_THUMBNAIL, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_THUMBNAIL, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_6_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_THUMBNAIL_FOR_LOCK
 */
int utc_notification_get_image_6_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_THUMBNAIL_FOR_LOCK, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_THUMBNAIL_FOR_LOCK, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_7_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_ICON_SUB
 */
int utc_notification_get_image_7_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_ICON_SUB, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_ICON_SUB, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_8_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_BACKGROUND
 */
int utc_notification_get_image_8_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BACKGROUND, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_BACKGROUND, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_get_image_9_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_LIST_1
 */
int utc_notification_get_image_9_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_1, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_1, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_10_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_LIST_2
 */
int utc_notification_get_image_10_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_2, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_2, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_11_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_LIST_3
 */
int utc_notification_get_image_11_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_3, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_3, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_12_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_LIST_4
 */
int utc_notification_get_image_12_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_4, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_4, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_13_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_LIST_5
 */
int utc_notification_get_image_13_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_5, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_LIST_5, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_14_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_1
 */
int utc_notification_get_image_14_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_1, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_1, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_15_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_2
 */
int utc_notification_get_image_15_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_2, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_2, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_16_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_3
 */
int utc_notification_get_image_16_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_3, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_3, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_17_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_4
 */
int utc_notification_get_image_17_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_4, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_4, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_18_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_5
 */
int utc_notification_get_image_18_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_5, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_5, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_19_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_6
 */
int utc_notification_get_image_19_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_6, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_6, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_20_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_7
 */
int utc_notification_get_image_20_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_7, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_7, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_21_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_8
 */
int utc_notification_get_image_21_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_8, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_8, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_22_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_9
 */
int utc_notification_get_image_22_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_9, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_9, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_image_23_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_get_image() - NOTIFICATION_IMAGE_TYPE_BUTTON_10
 */
int utc_notification_get_image_23_p(void)
{
	int ret = 0;
	char *image = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_10, TEST_IMAGE);
	ret = notification_get_image(notification, NOTIFICATION_IMAGE_TYPE_BUTTON_10, &image);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(image, NULL);
	image = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_time_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_time()
 */
int utc_notification_set_time_n(void)
{
	int ret = 0;

	ret = notification_set_time(NULL, 0);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_time_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time()
 */
int utc_notification_set_time_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time(notification, TEST_TIME);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_time()
 */
int utc_notification_get_time_n(void)
{
	int ret = 0;

	ret = notification_get_time(NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time()
 */
int utc_notification_get_time_1_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_time(notification, TEST_TIME);

	ret = notification_get_time(notification, &t);

	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time()
 */
int utc_notification_get_time_2_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_get_time(notification, &t);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_eq_with_exit(t, TEST_TIME);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_insert_time_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_insert_time()
 */
int utc_notification_get_insert_time_n(void)
{
	int ret = 0;

	ret = notification_get_insert_time(NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_insert_time_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_insert_time()
 */
int utc_notification_get_insert_time_1_p(void)
{
	int ret = 0;
	time_t t = -1;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_get_insert_time(notification, &t);

	assert_neq(t, -1);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_insert_time_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_insert_time()
 */
int utc_notification_get_insert_time_2_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_get_insert_time(notification, &t);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_neq(t, 0);

	notification_free(notification);

	normal_exit(0);
}


/**
 * @testcase		utc_notification_set_text_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_text()
 */
int utc_notification_set_text_n(void)
{
	int ret = 0;

	ret = notification_set_text(NULL, NOTIFICATION_TEXT_TYPE_NONE, NULL, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text()
 */
int utc_notification_set_text_1_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT, "I'm Content", "[%s] *** [%s], [%d], [%f]",
				NOTIFICATION_VARIABLE_TYPE_STRING, "FIRST_ONE",
				NOTIFICATION_VARIABLE_TYPE_STRING, "NEXT_ONE",
				NOTIFICATION_VARIABLE_TYPE_INT, 0,
				NOTIFICATION_VARIABLE_TYPE_DOUBLE, 0.0,
				NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_TITLE
 */
int utc_notification_set_text_2_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_3_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_CONTENT
 */
int utc_notification_set_text_3_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_4_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_CONTENT_FOR_DISPLAY_OPTION_IS_OFF
 */
int utc_notification_set_text_4_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_5_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_EVENT_COUNT
 */
int utc_notification_set_text_5_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_EVENT_COUNT, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_6_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_INFO_1
 */
int utc_notification_set_text_6_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_INFO_1, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_7_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_INFO_SUB_1
 */
int utc_notification_set_text_7_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_1, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_8_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_INFO_2
 */
int utc_notification_set_text_8_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_INFO_2, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_9_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_INFO_SUB_2
 */
int utc_notification_set_text_9_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_2, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_10_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_INFO_3
 */
int utc_notification_set_text_10_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_INFO_3, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_11_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_INFO_SUB_3
 */
int utc_notification_set_text_11_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_3, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_12_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_GROUP_TITLE
 */
int utc_notification_set_text_12_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_TITLE, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_13_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_GROUP_CONTENT
 */
int utc_notification_set_text_13_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_CONTENT, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_14_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_GROUP_CONTENT_FOR_DISPLAY_OPTION_IS_OFF
 */
int utc_notification_set_text_14_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_15_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_BUTTON_1
 */
int utc_notification_set_text_15_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_1, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_16_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_BUTTON_2
 */
int utc_notification_set_text_16_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_2, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_17_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_BUTTON_3
 */
int utc_notification_set_text_17_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_3, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_18_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_BUTTON_4
 */
int utc_notification_set_text_18_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);


	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_4, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_19_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_BUTTON_5
 */
int utc_notification_set_text_19_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_5, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_post(notification);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_20_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_BUTTON_6
 */
int utc_notification_set_text_20_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_6, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_21_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_COUNT
 */
int utc_notification_set_text_21_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_EVENT_COUNT, "3", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_22_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_BUTTON_7
 */
int utc_notification_set_text_22_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_7, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_23_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_BUTTON_8
 */
int utc_notification_set_text_23_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_8, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_24_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_BUTTON_9
 */
int utc_notification_set_text_24_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_9, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_25_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_set_text() - NOTIFICATION_TEXT_TYPE_BUTTON_10
 */
int utc_notification_set_text_25_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_10, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_text()
 */
int utc_notification_get_text_n(void)
{
	int ret = 0;

	ret = notification_get_text(NULL, NOTIFICATION_TEXT_TYPE_TITLE, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_text()
 */
int utc_notification_get_text_1_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_CONTENT
 */
int utc_notification_get_text_2_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_3_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_CONTENT_FOR_DISPLAY_OPTION_IS_OFF
 */
int utc_notification_get_text_3_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_4_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_EVENT_COUNT
 */
int utc_notification_get_text_4_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);


	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_EVENT_COUNT, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_EVENT_COUNT, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_5_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_INFO_SUB_1
 */
int utc_notification_get_text_5_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_1, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_1, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_6_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_INFO_2
 */
int utc_notification_get_text_6_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_INFO_2, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_INFO_2, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_7_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_INFO_SUB_2
 */
int utc_notification_get_text_7_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_2, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_2, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_8_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_INFO_3
 */
int utc_notification_get_text_8_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_INFO_3, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_INFO_3, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_9_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_INFO_SUB_3
 */
int utc_notification_get_text_9_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_3, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_3, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_10_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_GROUP_TITLE
 */
int utc_notification_get_text_10_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_TITLE, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_TITLE, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_11_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_GROUP_CONTENT
 */
int utc_notification_get_text_11_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_CONTENT, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_CONTENT, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_12_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_GROUP_CONTENT_FOR_DISPLAY_OPTION_IS_OFF
 */
int utc_notification_get_text_12_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_13_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_BUTTON_1
 */
int utc_notification_get_text_13_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_1, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_1, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_14_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_BUTTON_2
 */
int utc_notification_get_text_14_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_2, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_2, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_15_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_BUTTON_3
 */
int utc_notification_get_text_15_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_3, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_3, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_16_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_BUTTON_4
 */
int utc_notification_get_text_16_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_4, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_4, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_17_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_BUTTON_5
 */
int utc_notification_get_text_17_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_5, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_5, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_18_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_BUTTON_6
 */
int utc_notification_get_text_18_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_6, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_6, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_19_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_BUTTON_6
 */
int utc_notification_get_text_19_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification,
				    NOTIFICATION_TEXT_TYPE_CONTENT,
				    "%f %d %s %d", NULL,
				    NOTIFICATION_VARIABLE_TYPE_COUNT, NOTIFICATION_COUNT_POS_LEFT,
				    NOTIFICATION_VARIABLE_TYPE_DOUBLE, 0.0,
				    NOTIFICATION_VARIABLE_TYPE_COUNT, NOTIFICATION_COUNT_POS_IN,
				    NOTIFICATION_VARIABLE_TYPE_STRING, "Content",
				    NOTIFICATION_VARIABLE_TYPE_INT, 0,
				    NOTIFICATION_VARIABLE_TYPE_COUNT, NOTIFICATION_COUNT_POS_RIGHT,
				    NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_20_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_BUTTON_7
 */
int utc_notification_get_text_20_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_7, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_7, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_21_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_BUTTON_8
 */
int utc_notification_get_text_21_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_8, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_8, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_22_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_BUTTON_9
 */
int utc_notification_get_text_22_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_9, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_9, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_text_23_p
 * @since_tizen		5.0
 * @description		Positive test case of notification_get_text() - NOTIFICATION_TEXT_TYPE_BUTTON_10
 */
int utc_notification_get_text_23_p(void)
{
	int ret = 0;
	char *value = NULL;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_10, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	ret = notification_get_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_10, &value);
	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}


/**
 * @testcase		utc_notification_set_time_to_text_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_time_to_text()
 */
int utc_notification_set_time_to_text_n(void)
{
	int ret = 0;

	ret = notification_set_time_to_text(NULL, NOTIFICATION_TEXT_TYPE_NONE, 0);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_time_to_text_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text()
 */
int utc_notification_set_time_to_text_1_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_CONTENT
 */
int utc_notification_set_time_to_text_2_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_3_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_CONTENT_FOR_DISPLAY_OPTION_IS_OFF
 */
int utc_notification_set_time_to_text_3_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_4_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_EVENT_COUNT
 */
int utc_notification_set_time_to_text_4_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_EVENT_COUNT, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_5_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_INFO_1
 */
int utc_notification_set_time_to_text_5_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_INFO_1, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_6_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_INFO_SUB_1
 */
int utc_notification_set_time_to_text_6_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_1, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_7_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_INFO_2
 */
int utc_notification_set_time_to_text_7_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_INFO_2, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_8_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_INFO_2
 */
int utc_notification_set_time_to_text_8_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_2, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_9_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_INFO_3
 */
int utc_notification_set_time_to_text_9_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_INFO_3, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_10_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_INFO_SUB_3
 */
int utc_notification_set_time_to_text_10_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_3, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_11_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_GROUP_TITLE
 */
int utc_notification_set_time_to_text_11_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_TITLE, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_12_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_GROUP_CONTENT
 */
int utc_notification_set_time_to_text_12_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_CONTENT, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_13_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_GROUP_CONTENT_FOR_DISPLAY_OPTION_IS_OFF
 */
int utc_notification_set_time_to_text_13_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_14_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_BUTTON_1
 */
int utc_notification_set_time_to_text_14_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_1, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_15_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_BUTTON_2
 */
int utc_notification_set_time_to_text_15_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_2, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_16_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_BUTTON_3
 */
int utc_notification_set_time_to_text_16_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_3, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_17_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_BUTTON_4
 */
int utc_notification_set_time_to_text_17_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_4, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_18_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_BUTTON_5
 */
int utc_notification_set_time_to_text_18_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_5, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
/**
 * @testcase		utc_notification_set_time_to_text_19_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_time_to_text() - NOTIFICATION_TEXT_TYPE_BUTTON_6
 */
int utc_notification_set_time_to_text_19_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_6, time(NULL));
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_time_from_text()
 */
int utc_notification_get_time_from_text_n(void)
{
	int ret = 0;

	ret = notification_get_time_from_text(NULL, NOTIFICATION_TEXT_TYPE_TITLE, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text()
 */
int utc_notification_get_time_from_text_1_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_CONTENT
 */
int utc_notification_get_time_from_text_2_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_3_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_CONTENT_FOR_DISPLAY_OPTION_IS_OFF
 */
int utc_notification_get_time_from_text_3_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_4_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_EVENT_COUNT
 */
int utc_notification_get_time_from_text_4_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_EVENT_COUNT, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_EVENT_COUNT, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_5_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_INFO_1
 */
int utc_notification_get_time_from_text_5_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_INFO_1, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_INFO_1, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_6_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_INFO_SUB_1
 */
int utc_notification_get_time_from_text_6_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_1, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_1, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_7_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_INFO_2
 */
int utc_notification_get_time_from_text_7_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_INFO_2, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_INFO_2, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_8_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_INFO_SUB_2
 */
int utc_notification_get_time_from_text_8_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_2, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_2, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_9_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_INFO_3
 */
int utc_notification_get_time_from_text_9_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_INFO_3, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_INFO_3, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_10_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_INFO_SUB_3
 */
int utc_notification_get_time_from_text_10_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_3, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_INFO_SUB_3, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_11_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_GROUP_TITLE
 */
int utc_notification_get_time_from_text_11_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_TITLE, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_TITLE, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_12_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_GROUP_CONTENT
 */
int utc_notification_get_time_from_text_12_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_CONTENT, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_CONTENT, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_13_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_GROUP_CONTENT_FOR_DISPLAY_OPTION_IS_OFF
 */
int utc_notification_get_time_from_text_13_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_GROUP_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_14_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_BUTTON_1
 */
int utc_notification_get_time_from_text_14_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_1, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_1, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_15_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_BUTTON_2
 */
int utc_notification_get_time_from_text_15_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_2, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_2, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_16_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_BUTTON_3
 */
int utc_notification_get_time_from_text_16_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_3, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_3, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_17_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_BUTTON_4
 */
int utc_notification_get_time_from_text_17_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_4, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_4, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_18_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_BUTTON_5
 */
int utc_notification_get_time_from_text_18_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_5, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_5, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_19_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_BUTTON_6
 */
int utc_notification_get_time_from_text_19_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);
	notification_set_time_to_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_6, time(NULL));
	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_BUTTON_6, &t);
	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_time_from_text_20_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_time_from_text() - NOTIFICATION_TEXT_TYPE_TITLE
 */
int utc_notification_get_time_from_text_20_p(void)
{
	int ret = 0;
	time_t t = 0;
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_get_time_from_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, &t);

	assert_neq(t, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_sound_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_sound()
 */
int utc_notification_set_sound_n(void)
{
	int ret = 0;

	ret = notification_set_sound(NULL, NOTIFICATION_SOUND_TYPE_USER_DATA + 1, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_sound_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_sound()
 */
int utc_notification_set_sound_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_sound(notification, NOTIFICATION_SOUND_TYPE_DEFAULT, TEST_PATH);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_sound_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_sound()
 */
int utc_notification_get_sound_n(void)
{
	int ret = 0;

	ret = notification_get_sound(NULL, NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_sound_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_sound()
 */
int utc_notification_get_sound_1_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	notification_sound_type_e type;
	const char *value = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_sound(notification, NOTIFICATION_SOUND_TYPE_USER_DATA, TEST_PATH);

	ret = notification_get_sound(notification, &type, &value);

	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_sound_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_sound()
 */
int utc_notification_get_sound_2_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	notification_sound_type_e type;
	const char *value = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_get_sound(notification, &type, &value);

	assert_eq_with_exit(type, NOTIFICATION_SOUND_TYPE_USER_DATA);
	assert_eq_with_exit(strcmp(value, TEST_PATH), 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_vibration_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_vibration()
 */
int utc_notification_set_vibration_n(void)
{
	int ret = 0;

	ret = notification_set_vibration(NULL, NOTIFICATION_VIBRATION_TYPE_USER_DATA + 1, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_vibration_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_vibration()
 */
int utc_notification_set_vibration_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_vibration(notification, NOTIFICATION_VIBRATION_TYPE_DEFAULT, TEST_PATH);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_vibration_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_vibration()
 */
int utc_notification_get_vibration_n(void)
{
	int ret = 0;

	ret = notification_get_vibration(NULL, NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_vibration_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_vibration()
 */
int utc_notification_get_vibration_1_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	notification_vibration_type_e type = NOTIFICATION_VIBRATION_TYPE_USER_DATA;
	const char *value = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_vibration(notification, type, TEST_PATH);
	ret = notification_get_vibration(notification, &type, &value);

	assert_neq(value, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_vibration_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_vibration()
 */
int utc_notification_get_vibration_2_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	notification_vibration_type_e type;
	const char *value = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_get_vibration(notification, &type, &value);

	assert_eq_with_exit(type, NOTIFICATION_VIBRATION_TYPE_USER_DATA);
	assert_eq_with_exit(strcmp(value, TEST_PATH), 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	value = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_led_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_led()
 */
int utc_notification_set_led_n(void)
{
	int ret = 0;

	ret = notification_set_led(NULL, NOTIFICATION_LED_OP_ON_CUSTOM_COLOR + 1, 0);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_led_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_led()
 */
int utc_notification_set_led_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_led(notification, NOTIFICATION_LED_OP_ON, 0);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_led_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_led()
 */
int utc_notification_get_led_n(void)
{
	int ret = 0;

	ret = notification_get_led(NULL, NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_led_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_led()
 */
int utc_notification_get_led_1_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	notification_led_op_e type = NOTIFICATION_LED_OP_OFF;
	int value = -1;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_led(notification, NOTIFICATION_LED_OP_ON_CUSTOM_COLOR, TEST_INT);

	ret = notification_get_led(notification, &type, &value);

	assert_neq(type, NOTIFICATION_LED_OP_OFF);
	assert_neq(value, -1);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_led_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_led()
 */
int utc_notification_get_led_2_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	notification_led_op_e type;
	int value = 0;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_get_led(notification, &type, &value);

	assert_eq_with_exit(type, NOTIFICATION_LED_OP_ON);
	assert_eq_with_exit(value, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_led_time_period_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_led_time_period()
 */
int utc_notification_set_led_time_period_n(void)
{
	int ret = 0;

	ret = notification_set_led_time_period(NULL, 0, 0);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_led_time_period_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_led_time_period()
 */
int utc_notification_set_led_time_period_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_led_time_period(notification, TEST_INT, TEST_INT);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_led_time_period_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_led_time_period()
 */
int utc_notification_get_led_time_period_n(void)
{
	int ret = 0;

	ret = notification_get_led_time_period(NULL, NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_led_time_period_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_led_time_period()
 */
int utc_notification_get_led_time_period_1_p(void)
{
	int ret = 0;
	int value1 = -1;
	int value2 = -1;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_get_led_time_period(notification, &value1, &value2);

	assert_neq(value1, -1);
	assert_neq(value2, -1);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_led_time_period_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_led_time_period()
 */
int utc_notification_get_led_time_period_2_p(void)
{
	int ret = 0;
	int value1 = 0;
	int value2 = 0;
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_get_led_time_period(notification, &value1, &value2);

	assert_eq_with_exit(value1, TEST_INT);
	assert_eq_with_exit(value2, TEST_INT);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}



/**
 * @testcase		utc_notification_set_property_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_property()
 */
int utc_notification_set_property_n(void)
{
	int ret = 0;

	ret = notification_set_property(NULL, 0);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}


/**
 * @testcase		utc_notification_set_property_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_property()
 */
int utc_notification_set_property_1_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_property(notification, NOTIFICATION_PROP_DISABLE_AUTO_DELETE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_property_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_property() - NOTIFICATION_PROP_DISABLE_APP_LAUNCH
 */
int utc_notification_set_property_2_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_property(notification, NOTIFICATION_PROP_DISABLE_APP_LAUNCH);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_property_3_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_property() - NOTIFICATION_PROP_DISABLE_AUTO_DELETE
 */
int utc_notification_set_property_3_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_property(notification, NOTIFICATION_PROP_DISABLE_AUTO_DELETE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_property_4_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_property() - NOTIFICATION_PROP_DISABLE_UPDATE_ON_INSERT
 */
int utc_notification_set_property_4_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_property(notification, NOTIFICATION_PROP_DISABLE_UPDATE_ON_INSERT);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_property_5_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_property() - NOTIFICATION_PROP_DISABLE_UPDATE_ON_DELETE
 */
int utc_notification_set_property_5_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_property(notification, NOTIFICATION_PROP_DISABLE_UPDATE_ON_DELETE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_property_6_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_property() - NOTIFICATION_PROP_VOLATILE_DISPLAY
 */
int utc_notification_set_property_6_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_property(notification, NOTIFICATION_PROP_VOLATILE_DISPLAY);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_property_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_property()
 */
int utc_notification_get_property_n(void)
{
	int ret = 0;

	ret = notification_get_property(NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_property_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_property()
 */
int utc_notification_get_property_1_p(void)
{
	int ret = 0;
	int value = -1;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_get_property(notification, &value);

	assert_neq(value, -1);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_property_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_property()
 */
int utc_notification_get_property_2_p(void)
{
	int ret = 0;
	int value = 0;
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_get_property(notification, &value);

	assert_eq_with_exit(value, NOTIFICATION_PROP_DISABLE_AUTO_DELETE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_display_applist_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_display_applist()
 */
int utc_notification_set_display_applist_n(void)
{
	int ret = 0;

	ret = notification_set_display_applist(NULL, 0);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_display_applist_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_display_applist()
 */
int utc_notification_set_display_applist_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_display_applist(notification, NOTIFICATION_DISPLAY_APP_ALL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_display_applist_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_display_applist()
 */
int utc_notification_get_display_applist_n(void)
{
	int ret = 0;

	ret = notification_get_display_applist(NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_display_applist_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_display_applist()
 */
int utc_notification_get_display_applist_1_p(void)
{
	int ret = 0;
	int value = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_display_applist(notification, NOTIFICATION_DISPLAY_APP_ALL);

	ret = notification_get_display_applist(notification, &value);

	assert_neq(value, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase            utc_notification_get_display_applist_2_p
 * @since_tizen         2.3
 * @description         Positive test case of notification_get_display_applist()
 */
int utc_notification_get_display_applist_2_p(void)
{
	int ret;
	int applist;
	int applist_default = NOTIFICATION_DISPLAY_APP_NOTIFICATION_TRAY |
				NOTIFICATION_DISPLAY_APP_LOCK |
				NOTIFICATION_DISPLAY_APP_TICKER |
				NOTIFICATION_DISPLAY_APP_INDICATOR;

	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_get_display_applist(notification, &applist);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_eq_with_exit(applist, applist_default);

        notification_free(notification);
        normal_exit(0);
}

/**
 * @testcase		utc_notification_set_size_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_size()
 */
int utc_notification_set_size_n(void)
{
	int ret = 0;

	ret = notification_set_size(NULL, 0.0);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_size_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_size()
 */
int utc_notification_set_size_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_size(notification, TEST_DOUBLE);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_size_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_size()
 */
int utc_notification_get_size_n(void)
{
	int ret = 0;

	ret = notification_get_size(NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_size_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_size()
 */
int utc_notification_get_size_1_p(void)
{
	int ret = 0;
	double value = -1.0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_get_size(notification, &value);

	assert_neq(value, -1.0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_size_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_size()
 */
int utc_notification_get_size_2_p(void)
{
	int ret = 0;
	double value = 0.0;
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_ONGOING);

	assert(notification);

	ret = notification_get_size(notification, &value);

	assert_eq_with_exit(value, TEST_DOUBLE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_progress_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_progress()
 */
int utc_notification_set_progress_n(void)
{
	int ret = 0;

	ret = notification_set_progress(NULL, 0.0);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_progress_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_progress()
 */
int utc_notification_set_progress_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_progress(notification, TEST_DOUBLE);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_progress_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_progress()
 */
int utc_notification_get_progress_n(void)
{
	int ret = 0;

	ret = notification_get_progress(NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_progress_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_progress()
 */
int utc_notification_get_progress_1_p(void)
{
	int ret = 0;
	double value = -1.0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_get_progress(notification, &value);

	assert_neq(value, -1.0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_progress_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_progress()
 */
int utc_notification_get_progress_2_p(void)
{
	int ret = 0;
	double value = 0.0;
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_ONGOING);

	assert(notification);

	ret = notification_get_progress(notification, &value);

	assert_eq_with_exit(value, TEST_DOUBLE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}


/**
 * @testcase		utc_notification_set_layout_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_layout()
 */
int utc_notification_set_layout_n(void)
{
	int ret = 0;

	ret = notification_set_layout(NULL, NOTIFICATION_LY_NONE);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}


/**
 * @testcase		utc_notification_set_layout_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_layout()
 */
int utc_notification_set_layout_1_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_layout(notification, NOTIFICATION_LY_NOTI_EVENT_SINGLE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_layout_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_layout() - NOTIFICATION_LY_NOTI_EVENT_MULTIPLE
 */
int utc_notification_set_layout_2_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_layout(notification, NOTIFICATION_LY_NOTI_EVENT_MULTIPLE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_layout_3_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_layout() - NOTIFICATION_LY_NOTI_THUMBNAIL
 */
int utc_notification_set_layout_3_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_layout(notification, NOTIFICATION_LY_NOTI_THUMBNAIL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_layout_4_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_layout() - NOTIFICATION_LY_ONGOING_EVENT
 */
int utc_notification_set_layout_4_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_layout(notification, NOTIFICATION_LY_ONGOING_EVENT);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_layout_5_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_layout() - NOTIFICATION_LY_ONGOING_PROGRESS
 */
int utc_notification_set_layout_5_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_layout(notification, NOTIFICATION_LY_ONGOING_PROGRESS);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_layout_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_layout()
 */
int utc_notification_get_layout_n(void)
{
	int ret = 0;

	ret = notification_get_layout(NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_layout_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_layout()
 */
int utc_notification_get_layout_1_p(void)
{
	int ret = 0;
	notification_ly_type_e type = NOTIFICATION_LY_NONE;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_layout(notification, NOTIFICATION_LY_NOTI_EVENT_SINGLE);
	ret = notification_get_layout(notification, &type);

	assert_eq_with_exit(type, NOTIFICATION_LY_NOTI_EVENT_SINGLE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_layout_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_layout()
 */
int utc_notification_get_layout_2_p(void)
{
	int ret = 0;
	notification_ly_type_e type;
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_get_layout(notification, &type);

	assert_eq_with_exit(type, NOTIFICATION_LY_NOTI_EVENT_SINGLE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}


/**
 * @testcase		utc_notification_get_type_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_type()
 */
int utc_notification_get_type_n(void)
{
	int ret = 0;

	ret = notification_get_type(NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_type_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_type()
 */
int utc_notification_get_type_1_p(void)
{
	int ret = 0;
	notification_type_e type = NOTIFICATION_TYPE_NONE;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_get_type(notification, &type);

	assert_neq(type, NOTIFICATION_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_type_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_type()
 */
int utc_notification_get_type_2_p(void)
{
	int ret = 0;
	notification_type_e type;
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_get_type(notification, &type);

	assert_eq_with_exit(type, NOTIFICATION_TYPE_NOTI);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_update_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_update()
 */
int utc_notification_update_n(void)
{
	int ret = 0;

	ret = notification_update(NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_update_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_update()
 */
int utc_notification_update_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, TEST_UPDATE, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);

	ret = notification_update(notification);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}


/**
 * @testcase		utc_notification_delete_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_delete()
 */
int utc_notification_delete_n(void)
{
	int ret = 0;

	ret = notification_delete(NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_delete_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_delete()
 */
int utc_notification_delete_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_delete(notification);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}





/**
 * @testcase		utc_notification_clone_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_clone()
 */
int utc_notification_clone_n(void)
{
	int ret = 0;

	ret = notification_clone(NULL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_clone_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_clone()
 */
int utc_notification_clone_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	notification_h notification_cloned = NULL;

	notification = notification_create(NOTIFICATION_TYPE_ONGOING);

	assert(notification);

	ret = notification_clone(notification, &notification_cloned);
	assert(notification_cloned);

	notification_free(notification_cloned);
	notification_free(notification);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_free_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_free()
 */
int utc_notification_free_n(void)
{
	int ret = 0;

	ret = notification_free(NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_free_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_free()
 */
int utc_notification_free_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_ONGOING);

	assert(notification);

	ret = notification_free(notification);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_status_message_post_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_status_message_post()
 */
int utc_notification_status_message_post_n(void)
{
	int ret;

	ret = notification_status_message_post(NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_status_message_post_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_status_message_post()
 */
int utc_notification_status_message_post_p(void)
{
	int ret;

	ret = notification_status_message_post("TESTKIT-P");

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_tag_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_tag()
 */
int utc_notification_set_tag_n(void)
{
	int ret = 0;
	notification_h notification = NULL;

	ret = notification_set_tag(notification, TEST_TEXT);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_tag_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_tag()
 */
int utc_notification_set_tag_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_tag(notification, TEST_TEXT);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_tag_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_tag()
 */
int utc_notification_get_tag_n(void)
{
	int ret = 0;
	notification_h notification = NULL;
	const char *tag = NULL;

	ret = notification_get_tag(notification, &tag);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_tag_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_tag()
 */
int utc_notification_get_tag_1_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	const char *tag = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_tag(notification, TEST_TEXT);

	ret = notification_get_tag(notification, &tag);

	assert_neq(tag, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	tag = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_tag_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_tag()
 */
int utc_notification_get_tag_2_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	const char *tag = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	ret = notification_get_tag(notification, &tag);

	assert_eq_with_exit(strcmp(tag, TEST_TAG_FOR_NOTI), 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	tag = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_load_by_tag_1_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_load_by_tag()
 */
int utc_notification_load_by_tag_1_n(void)
{
	notification_h notification = NULL;

	notification = notification_load_by_tag(NULL);

	assert(!notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_load_by_tag_2_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_load_by_tag() - Invalid tag
 */
int utc_notification_load_by_tag_2_n(void)
{
	notification_h notification = NULL;

	notification = notification_load_by_tag("!@#$UNDEFINED_TAG!@#$");

	assert(!notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_load_by_tag_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_load_by_tag()
 */
int utc_notification_load_by_tag_p(void)
{
	notification_h notification = NULL;

	notification = notification_load_by_tag(TEST_TAG_FOR_NOTI);

	assert(notification);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_delete_all_1_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_delete_all() - NOTIFICATION_TYPE_NOTI
 */
int utc_notification_delete_all_1_p(void)
{
	int ret = 0;

	ret = notification_delete_all(NOTIFICATION_TYPE_NOTI);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_delete_all_2_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_delete_all() - NOTIFICATION_TYPE_ONGOING
 */
int utc_notification_delete_all_2_p(void)
{
	int ret = 0;

	ret = notification_delete_all(NOTIFICATION_TYPE_ONGOING);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_post_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_post()
 */
int utc_notification_post_n(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);

	ret = notification_post(NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_post_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_post()
 */
int utc_notification_post_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);

	ret = notification_post(notification);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_delete(notification);
	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_launch_option_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_set_launch()
 */
int utc_notification_set_launch_option_n(void)
{
	int ret = 0;

	ret = notification_set_launch_option(NULL, NOTIFICATION_LAUNCH_OPTION_APP_CONTROL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_launch_option_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_set_launch_option()
 */
int utc_notification_set_launch_option_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	app_control_h app_control = NULL;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, TEST_APP);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	//Invalid parameter test
	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_launch_option(notification, NOTIFICATION_LAUNCH_OPTION_APP_CONTROL, app_control);
	app_control_destroy(app_control);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_launch_option_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_launch_option()
 */
int utc_notification_get_launch_option_n(void)
{
	int ret = 0;

	ret = notification_get_launch_option(NULL, NOTIFICATION_LAUNCH_OPTION_APP_CONTROL, NULL);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_launch_option_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_launch_option()
 */
int utc_notification_get_launch_option_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	app_control_h app_control = NULL;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, TEST_APP);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_launch_option(notification, NOTIFICATION_LAUNCH_OPTION_APP_CONTROL, app_control);
	app_control_destroy(app_control);
	app_control = NULL;

	ret = notification_get_launch_option(notification, NOTIFICATION_LAUNCH_OPTION_APP_CONTROL, &app_control);
	notification_free(notification);
	app_control_destroy(app_control);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_pkgname_n
 * @since_tizen		2.3
 * @description		Negative test case of notification_get_pkgname()
 */
int utc_notification_get_pkgname_n(void)
{
	int ret = 0;
	notification_h notification = NULL;
	char *tag = NULL;

	ret = notification_get_pkgname(notification, &tag);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_pkgname_p
 * @since_tizen		2.3
 * @description		Positive test case of notification_get_pkgname()
 */
int utc_notification_get_pkgname_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	char *tag = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_get_pkgname(notification, &tag);

	assert_neq(tag, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	tag = NULL;

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_event_handler_n
 * @since_tizen		2.4
 * @description		Negative test case of notification_set_event_handler()
 */
int utc_notification_set_event_handler_n(void)
{
	int ret = 0;
	notification_h notification = NULL;

	ret = notification_set_event_handler(notification, 0, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_event_handler_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_event_handler()
 */
int utc_notification_set_event_handler_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	app_control_h app_control = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, "org.tizen.app");
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret  = notification_set_event_handler(notification, NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_1, app_control);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);
	app_control_destroy(app_control);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_event_handler_n
 * @since_tizen		2.4
 * @description		Negative test case of notification_get_event_handler()
 */
int utc_notification_get_event_handler_n(void)
{
	int ret = 0;
	notification_h notification = NULL;

	ret = notification_get_event_handler(notification, 0, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_event_handler_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_event_handler()
 */
int utc_notification_get_event_handler_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	app_control_h app_control = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, "org.tizen.app");
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = notification_set_event_handler(notification, NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_1, app_control);
	app_control_destroy(app_control);
	app_control = NULL;

	ret = notification_get_event_handler(notification, NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_1, &app_control);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);
	app_control_destroy(app_control);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_add_button_n
 * @since_tizen		2.4
 * @description		Negative test case of notification_add_button()
 */
int utc_notification_add_button_n(void)
{
	int ret = 0;
	notification_h notification = NULL;

	ret = notification_add_button(notification, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_add_button_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_add_button()
 */
int utc_notification_add_button_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_add_button(notification, NOTIFICATION_BUTTON_1);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_remove_button_n
 * @since_tizen		2.4
 * @description		Negative test case of notification_remove_button()
 */
int utc_notification_remove_button_n(void)
{
	int ret = 0;
	notification_h notification = NULL;

	ret = notification_remove_button(notification, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_remove_button_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_remove_button()
 */
int utc_notification_remove_button_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_add_button(notification, NOTIFICATION_BUTTON_1);

	ret = notification_remove_button(notification, NOTIFICATION_BUTTON_1);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_auto_remove_n
 * @since_tizen		2.4
 * @description		Negative test case of notification_set_auto_remove()
 */
int utc_notification_set_auto_remove_n(void)
{
	int ret = 0;
	notification_h notification = NULL;

	ret = notification_set_auto_remove(notification, false);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_auto_remove_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_set_auto_remove()
 */
int utc_notification_set_auto_remove_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_auto_remove(notification, false);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_auto_remove_n
 * @since_tizen		2.4
 * @description		Negative test case of notification_get_auto_remove()
 */
int utc_notification_get_auto_remove_n(void)
{
	int ret = 0;
	notification_h notification = NULL;
	bool auto_remove = false;

	ret = notification_get_auto_remove(notification, &auto_remove);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_auto_remove_p
 * @since_tizen		2.4
 * @description		Positive test case of notification_get_auto_remove()
 */
int utc_notification_get_auto_remove_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	bool auto_remove = true;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	notification_set_auto_remove(notification, false);

	ret = notification_get_auto_remove(notification, &auto_remove);

	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);
	assert_eq_with_exit(auto_remove, false);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_save_as_template_n
 * @since_tizen		3.0
 * @description		Negative test case of notification_save_as_template()
 */
int utc_notification_save_as_template_n(void)
{
	int ret = 0;
	notification_h notification = NULL;

	ret =  notification_save_as_template(notification, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_save_as_template_p
 * @since_tizen		3.0
 * @description		Positive test case of notification_save_as_template()
 */
int utc_notification_save_as_template_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret  = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, "I'm Title", "TITLE", NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_save_as_template(notification, "noti_test");
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);
	normal_exit(0);
}

/**
 * @testcase		utc_notification_create_from_template_n1
 * @since_tizen		3.0
 * @description		Negative test case of notification_create_from_template()
 */
int utc_notification_create_from_template_n1(void)
{
	notification_h notification = NULL;

	notification = notification_create_from_template(NULL);
	assert(!notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_create_from_template_n2
 * @since_tizen		3.0
 * @description		Negative test case of notification_create_from_template() - Invalid name
 */
int utc_notification_create_from_template_n2(void)
{
	notification_h notification = NULL;

	notification = notification_create_from_template("dummy");
	assert(!notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_create_from_template_p
 * @since_tizen		3.0
 * @description		Positive test case of notification_create_from_template()
 */
int utc_notification_create_from_template_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret  = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, "I'm Title", "TITLE", NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_save_as_template(notification, "noti_test");
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	notification = notification_create_from_template("noti_test");
	assert(notification);

	notification_free(notification);
	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_noti_block_state_n
 * @since_tizen		3.0
 * @description		Negative test case of notification_get_noti_block_state()
 */
int utc_notification_get_noti_block_state_n(void)
{
	int ret = 0;

	ret = notification_get_noti_block_state(NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_noti_block_state_p
 * @since_tizen		3.0
 * @description		Positive test case of notification_get_noti_block_state()
 */
int utc_notification_get_noti_block_state_p(void)
{
	int ret = 0;
	notification_block_state_e state;

	ret = notification_get_noti_block_state(&state);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_input_n
 * @since_tizen		3.0
 * @description		Negative test case of notification_set_text_input()
 */
int utc_notification_set_text_input_n(void)
{
	int ret = 0;

	ret = notification_set_text_input(NULL, 0);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_text_input_p
 * @since_tizen		3.0
 * @description		Positive test case of notification_set_text_input()
 */
int utc_notification_set_text_input_p(void)
{
	int ret = 0;
	notification_h notification = NULL;
	app_control_h app_control = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	assert(notification);

	ret = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_TITLE,
			TEST_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_set_text_input(notification, 160);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_set_text(notification,
			NOTIFICATION_TEXT_TYPE_TEXT_INPUT_PLACEHOLDER,
			"Text message",
			NULL,
			NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_set_text(notification,
			NOTIFICATION_TEXT_TYPE_TEXT_INPUT_BUTTON,
			"SEND",
			NULL,
			NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_set_display_applist(notification, NOTIFICATION_DISPLAY_APP_ACTIVE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, TEST_APP);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = notification_set_event_handler(notification, NOTIFICATION_EVENT_TYPE_CLICK_ON_TEXT_INPUT_BUTTON, app_control);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_post(notification);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	app_control = NULL;

	ret = notification_get_event_handler(notification, NOTIFICATION_EVENT_TYPE_CLICK_ON_TEXT_INPUT_BUTTON, &app_control);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_free(notification);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_extension_image_size_n
 * @since_tizen		4.0
 * @description		Negative test case of notification_set_extension_image_size()
 */
int utc_notification_set_extension_image_size_n(void)
{
	int ret = 0;

	ret = notification_set_extension_image_size(NULL, -1);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_set_extension_image_size_p
 * @since_tizen		4.0
 * @description		Positive test case of notification_set_extension_image_size()
 */
int utc_notification_set_extension_image_size_p(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_extension_image_size(notification, 20);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_extension_image_size_n
 * @since_tizen		4.0
 * @description		Negative test case of notification_get_extension_image_size()
 */
int utc_notification_get_extension_image_size_n(void)
{
	int ret = 0;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_extension_image_size(notification, 20);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_get_extension_image_size(NULL, NULL);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_INVALID_PARAMETER);

	notification_free(notification);

	normal_exit(0);
}

/**
 * @testcase		utc_notification_get_extension_image_size_p
 * @since_tizen		4.0
 * @description		Positive test case of notification_get_extension_image_size()
 */
int utc_notification_get_extension_image_size_p(void)
{
	int ret = 0;
	int size;
	notification_h notification = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);

	assert(notification);

	ret = notification_set_extension_image_size(notification, 20);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_get_extension_image_size(notification, &size);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	notification_free(notification);

	normal_exit(0);
}
