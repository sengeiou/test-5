//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#include "assert_common.h"

#include <cion.h>

//& set: Cion

void utc_cion_group_startup(void)
{
}

void utc_cion_group_cleanup(void)
{
}

/**
 * @testcase		utc_cion_group_create_p
 * @since_tizen		6.5
 * @description		Creates a cion group with topic.
 */
int utc_cion_group_create_p(void)
{
	int ret;
	cion_group_h group;

	ret = cion_group_create(&group, "utc_cion_group_create_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_group_destroy(group);

	return 0;
}

/**
 * @testcase		utc_cion_group_create_n
 * @since_tizen		6.5
 * @description		Creates a cion group for negative case.
 */
int utc_cion_group_create_n(void)
{
	int ret;
	cion_group_h group = NULL;

	ret = cion_group_create(NULL, "utc_cion_group_create_n", NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_group_create(&group, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_group_create(NULL, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_group_destroy_p
 * @since_tizen		6.5
 * @description		Destroys a cion group.
 */
int utc_cion_group_destroy_p(void)
{
	int ret;
	cion_group_h group;

	ret = cion_group_create(&group, "utc_cion_group_destroy_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_group_destroy(group);
	assert_eq(ret, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_group_destroy_n
 * @since_tizen		6.5
 * @description		Destroys a cion group for negative case.
 */
int utc_cion_group_destroy_n(void)
{
	int ret;

	ret = cion_group_destroy(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_group_subscribe_p
 * @since_tizen		6.5
 * @description		Subscribes to a topic that the group handle has.
 */
int utc_cion_group_subscribe_p(void)
{
	int ret;
	cion_group_h group;

	ret = cion_group_create(&group, "utc_cion_group_subscribe_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_group_subscribe(group);
	assert_eq(ret, CION_ERROR_NONE);

	cion_group_destroy(group);

	return 0;
}

/**
 * @testcase		utc_cion_group_subscribe_n
 * @since_tizen		6.5
 * @description		Subscribes to a topic that the group handle has for negative case.
 */
int utc_cion_group_subscribe_n(void)
{
	int ret;

	ret = cion_group_subscribe(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_group_unsubscribe_p
 * @since_tizen		6.5
 * @description		Unsubscribes a topic that the group handle has.
 */
int utc_cion_group_unsubscribe_p(void)
{
	int ret;
	cion_group_h group;

	ret = cion_group_create(&group, "utc_cion_group_unsubscribe_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_group_subscribe(group);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_group_unsubscribe(group);
	assert_eq(ret, CION_ERROR_NONE);

	cion_group_destroy(group);

	return 0;
}

/**
 * @testcase		utc_cion_group_unsubscribe_p
 * @since_tizen		6.5
 * @description		Unsubscribes a topic that the group handle has for negative case.
 */
int utc_cion_group_unsubscribe_n(void)
{
	int ret;
	cion_group_h group = (cion_group_h)1;

	ret = cion_group_unsubscribe(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_group_create(&group, "utc_cion_group_unsubscribe_n", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	/* test unsubscribe without subscribe */
	ret = cion_group_unsubscribe(group);
	assert_eq(ret, CION_ERROR_NONE);

	cion_group_destroy(group);

	return 0;
}

/**
 * @testcase		utc_cion_group_publish_p
 * @since_tizen		6.5
 * @description		Publishes the payload.
 */
int utc_cion_group_publish_p(void)
{
	int ret;
	cion_group_h group;
	cion_payload_h payload;
	unsigned char data[] = "test data";

	ret = cion_group_create(&group, "utc_cion_group_publish_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_group_subscribe(group);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_DATA);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_set_data(payload, data, sizeof(data));
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_group_publish(group, payload);
	assert_eq(ret, CION_ERROR_NONE);

	cion_group_destroy(group);

	return 0;
}

/**
 * @testcase		utc_cion_group_publish_n
 * @since_tizen		6.5
 * @description		Publishes the payload for negative case.
 */
int utc_cion_group_publish_n(void)
{
	int ret;
	cion_group_h group = (cion_group_h)1;
	cion_payload_h payload = (cion_payload_h)1;

	ret = cion_group_publish(NULL, payload);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_group_create(&group, "utc_cion_group_publish_n", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_group_publish(group, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_FILE);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_group_publish(group, payload);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	cion_payload_destroy(payload);

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_DATA);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_group_publish(group, payload);
	assert_eq(ret, CION_ERROR_INVALID_OPERATION);

	cion_payload_destroy(payload);
	cion_group_destroy(group);

	return 0;
}
