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

static noti_ex_item_h name;
static noti_ex_item_h text;
static noti_ex_item_h image;
static noti_ex_item_h time_handle;
static time_t current_time;

void utc_notification_ex_chat_message_startup(void)
{
	noti_ex_item_text_create(&name, "name_id", "test_name", NULL);
	noti_ex_item_text_create(&text, "text_id", "test_text", NULL);
	noti_ex_item_image_create(&image, "image_id", "test_image_path");

	time(&current_time);
	noti_ex_item_time_create(&time_handle, "time_id", current_time);
}

void utc_notification_ex_chat_message_cleanup(void)
{
	if (name)
		noti_ex_item_destroy(name);

	if (text)
		noti_ex_item_destroy(text);

	if (image)
		noti_ex_item_destroy(image);

	if (time_handle)
		noti_ex_item_destroy(time_handle);
}

/**
 * @testcase utc_noti_ex_item_chat_message_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_chat_message_create()
 */
int utc_noti_ex_item_chat_message_create_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;

	ret = noti_ex_item_chat_message_create(&item_handle, "chat_id", name,
				text, image, time_handle, NOTI_EX_ITEM_CHAT_MESSAGE_TYPE_USER);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_chat_message_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_chat_message_create()
 */
int utc_noti_ex_item_chat_message_create_n(void)
{
	int ret;
	ret = noti_ex_item_chat_message_create(NULL, "chat_id", name,
				text, image, time_handle, NOTI_EX_ITEM_CHAT_MESSAGE_TYPE_USER);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_noti_ex_item_chat_message_get_name_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_chat_message_get_name()
 */
int utc_noti_ex_item_chat_message_get_name_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	noti_ex_item_h name_handle = NULL;
	char *chat_name = NULL;

	ret = noti_ex_item_chat_message_create(&item_handle, "chat_id", name,
				text, image, time_handle, NOTI_EX_ITEM_CHAT_MESSAGE_TYPE_USER);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_chat_message_get_name(item_handle, &name_handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_text_get_contents(name_handle, &chat_name);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(strcmp(chat_name, "test_name"), 0);

	noti_ex_item_destroy(item_handle);
	free(chat_name);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_chat_message_get_name_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_chat_message_get_name()
 */
int utc_noti_ex_item_chat_message_get_name_n(void)
{
	int ret;
	noti_ex_item_h name_handle = NULL;

	ret = noti_ex_item_chat_message_get_name(NULL, &name_handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_chat_message_get_text_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_chat_message_get_text()
 */
int utc_noti_ex_item_chat_message_get_text_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	noti_ex_item_h text_handle = NULL;
	char *chat_text = NULL;

	ret = noti_ex_item_chat_message_create(&item_handle, "chat_id", name,
				text, image, time_handle, NOTI_EX_ITEM_CHAT_MESSAGE_TYPE_USER);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_chat_message_get_text(item_handle, &text_handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_text_get_contents(text_handle, &chat_text);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(strcmp(chat_text, "test_text"), 0);

	noti_ex_item_destroy(item_handle);
	free(chat_text);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_chat_message_get_text_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_chat_message_get_text()
 */
int utc_noti_ex_item_chat_message_get_text_n(void)
{
	int ret;
	noti_ex_item_h text_handle = NULL;

	ret = noti_ex_item_chat_message_get_text(NULL, &text_handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_chat_message_get_image_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_chat_message_get_image()
 */
int utc_noti_ex_item_chat_message_get_image_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	noti_ex_item_h image_handle = NULL;
	char *image_path = NULL;

	ret = noti_ex_item_chat_message_create(&item_handle, "chat_id", name,
				text, image, time_handle, NOTI_EX_ITEM_CHAT_MESSAGE_TYPE_USER);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_chat_message_get_image(item_handle, &image_handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_image_get_image_path(image_handle, &image_path);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(strcmp(image_path, "test_image_path"), 0);

	noti_ex_item_destroy(item_handle);
	free(image_path);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_chat_message_get_image_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_chat_message_get_image()
 */
int utc_noti_ex_item_chat_message_get_image_n(void)
{
	int ret;
	noti_ex_item_h image_handle = NULL;

	ret = noti_ex_item_chat_message_get_image(NULL, &image_handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_chat_message_get_time_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_chat_message_get_time()
 */
int utc_noti_ex_item_chat_message_get_time_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	noti_ex_item_h chat_time_handle = NULL;
	time_t time_info;

	ret = noti_ex_item_chat_message_create(&item_handle, "chat_id", name,
				text, image, time_handle, NOTI_EX_ITEM_CHAT_MESSAGE_TYPE_USER);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_chat_message_get_time(item_handle, &chat_time_handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_time_get_time(chat_time_handle, &time_info);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(current_time, time_info);

	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_chat_message_get_time_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_chat_message_get_time()
 */
int utc_noti_ex_item_chat_message_get_time_n(void)
{
	int ret;
	noti_ex_item_h time_handle = NULL;

	ret = noti_ex_item_chat_message_get_time(NULL, &time_handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_chat_message_get_message_type_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_chat_message_get_message_type()
 */
int utc_noti_ex_item_chat_message_get_message_type_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	noti_ex_item_chat_message_type_e type;

	ret = noti_ex_item_chat_message_create(&item_handle, "chat_id", name,
				text, image, time_handle, NOTI_EX_ITEM_CHAT_MESSAGE_TYPE_USER);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_chat_message_get_message_type(item_handle, &type);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	assert_eq_with_exit(type, NOTI_EX_ITEM_CHAT_MESSAGE_TYPE_USER);

	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_chat_message_get_message_type_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_chat_message_get_message_type()
 */
int utc_noti_ex_item_chat_message_get_message_type_n(void)
{
	int ret;
	noti_ex_item_chat_message_type_e type;

	ret = noti_ex_item_chat_message_get_message_type(NULL, &type);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}