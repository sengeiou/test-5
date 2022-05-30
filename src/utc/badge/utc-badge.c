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
#include <badge.h>
#include <system_info.h>

#include "assert.h"
#include "tct_app_common.h"

//& set: utc-badge

#define BADGE_FEATURE "http://tizen.org/feature/badge"

#define TEST_PKG "core.badge-tests"
#define TEST_COUNT 1

#define CHECK_BADGE_FEATURE() \
	do { \
		bool is_supported = false; \
		if (!system_info_get_platform_bool(BADGE_FEATURE, &is_supported)) { \
			if (is_supported == false) { \
				int check_suppoted = badge_add(TEST_PKG); \
				assert_eq(check_suppoted, BADGE_ERROR_NOT_SUPPORTED); \
				return 0; \
			} \
		} \
	} while (0)

int foreach_executed;

static void _badge_foreach_cb(const char *pkgname, unsigned int count,
			      void *data)
{
	foreach_executed = 1;
}

static void _badge_changed_cb(unsigned int action, const char *pkgname,
			      unsigned int count, void *data) {

}

static void _badge_changed_cb2(unsigned int action, const char *pkgname,
			       unsigned int count, void *data) {

}

static void _deferred_job_cb(void *data)
{
}

/**
 * @function		utc_badge_setting_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_badge_setting_startup(void)
{
	bool is_supported = false;
	if (!system_info_get_platform_bool(BADGE_FEATURE, &is_supported)) {
		if (is_supported == false)
			return;
	}

	badge_remove(TEST_PKG);
	TCT_UTCCheckInstalledApp(2, "org.tizen.badge_utc_app", "org.tizen.badge_noncert_app");
}

/**
 * @function		utc_badge_setting_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_badge_setting_cleanup(void)
{
	bool is_supported = false;
	if (!system_info_get_platform_bool(BADGE_FEATURE, &is_supported)) {
		if (is_supported == false)
			return;
	}

	badge_remove(TEST_PKG);
}

/**
 * @testcase		utc_badge_remove_1_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_remove()
 */
int utc_badge_remove_1_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_remove(NULL);
	assert_eq(ret, BADGE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_badge_remove_2_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_remove() - invalid app id
 */
int utc_badge_remove_2_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_remove("!&---^@#$UNDEFINED_APP_ID!&---^#$");
	assert_eq(ret, BADGE_ERROR_NOT_EXIST);

	return 0;
}

/**
 * @testcase		utc_badge_remove_p
 * @since_tizen		2.3
 * @description		Positive test case of badge_remove()
 */
int utc_badge_remove_p(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_new(TEST_PKG);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_remove(TEST_PKG);
	assert_eq(ret, BADGE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_badge_set_count_1_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_set_count() - NULL package
 */
int utc_badge_set_count_1_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_set_count(NULL, 0);

	assert_eq(ret, BADGE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_badge_set_count_2_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_set_count() - invalid app id
 */
int utc_badge_set_count_2_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_set_count("!&^@#$UNDEFINED_APP_ID!&^#$", 0);
	assert_eq(ret, BADGE_ERROR_NOT_EXIST);

	return 0;
}

/**
 * @testcase		utc_badge_set_count_p
 * @since_tizen		2.3
 * @description		Positive test case of badge_set_count()
 */
int utc_badge_set_count_p(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_new(TEST_PKG);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_set_count(TEST_PKG, TEST_COUNT);
	assert_eq(ret, BADGE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_badge_set_count_2_p
 * @since_tizen		2.3
 * @description		Positive test case of badge_set_count()
 */
int utc_badge_set_count_2_p(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_add(NULL);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_add("org.tizen.badge_utc_app");
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_set_count("org.tizen.badge_utc_app", 1);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_remove("org.tizen.badge_utc_app");
	assert_eq(ret, BADGE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_badge_get_count_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_get_count() - all argument NULL
 */
int utc_badge_get_count_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_get_count(NULL, NULL);

	assert_eq(ret, BADGE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_badge_get_count_n2
 * @since_tizen		2.3
 * @description		Negative test case of badge_get_count() - value pointer NULL
 */
int utc_badge_get_count_n2(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_new(TEST_PKG);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_set_count(TEST_PKG, TEST_COUNT);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_get_count(TEST_PKG, NULL);
	assert_eq(ret, BADGE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_badge_get_count_p
 * @since_tizen		2.3
 * @description		Positive test case of badge_get_count()
 */
int utc_badge_get_count_p(void)
{
	int ret;
	unsigned int count = 0;

	CHECK_BADGE_FEATURE();

	ret = badge_new(TEST_PKG);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_set_count(TEST_PKG, TEST_COUNT);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_get_count(TEST_PKG, &count);
	assert_eq(ret, BADGE_ERROR_NONE);

	assert_eq(count, 1);

	return 0;
}

/**
 * @testcase		utc_badge_set_display_1_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_set_display()
 */
int utc_badge_set_display_1_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_set_display(NULL, 0);

	assert_eq(ret, BADGE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_badge_set_display_2_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_set_display() - invalid app id
 */
int utc_badge_set_display_2_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_set_display("!@#$UNDEFINED_APP_ID!@#$", 0);
	assert_eq(ret, BADGE_ERROR_NOT_EXIST);

	return 0;
}

/**
 * @testcase		utc_badge_set_display_p
 * @since_tizen		2.3
 * @description		Positive test case of badge_set_display()
 */
int utc_badge_set_display_p(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_new(TEST_PKG);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_set_display(TEST_PKG, TEST_COUNT);
	assert_eq(ret, BADGE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_badge_get_display_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_get_display() - all arguments NULL
 */
int utc_badge_get_display_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_get_display(NULL, NULL);

	assert_eq(ret, BADGE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_badge_get_display_n2
 * @since_tizen		2.3
 * @description		Negative test case of badge_get_display() - value pointer NULL
 */
int utc_badge_get_display_n2(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_new(TEST_PKG);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_set_display(TEST_PKG, TEST_COUNT);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_get_display(TEST_PKG, NULL);
	assert_eq(ret, BADGE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_badge_get_display_p
 * @since_tizen		2.3
 * @description		Positive test case of badge_get_display()
 */
int utc_badge_get_display_p(void)
{
	int ret;
	unsigned int count = 0;

	CHECK_BADGE_FEATURE();

	ret = badge_new(TEST_PKG);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_set_display(TEST_PKG, TEST_COUNT);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_get_display(TEST_PKG, &count);
	assert_eq(ret, BADGE_ERROR_NONE);

	assert_eq(count, TEST_COUNT);

	return 0;
}

/**
 * @testcase		utc_badge_new_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_new()
 */
int utc_badge_new_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_new(TEST_PKG);

	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_new(TEST_PKG);

	assert_eq(ret, BADGE_ERROR_ALREADY_EXIST);

	return 0;
}

/**
 * @testcase		utc_badge_new_p
 * @since_tizen		2.3
 * @description		Positive test case of badge_new()
 */
int utc_badge_new_p(void)
{
	int ret;
	bool exists;

	CHECK_BADGE_FEATURE();

	ret = badge_new(TEST_PKG);

	assert_eq(ret, BADGE_ERROR_NONE);

	return 0;
}


void change_cb(unsigned int action, const char *app_id, unsigned int count, void *user_data)
{

}

/**
 * @testcase		utc_badge_register_changed_cb_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_register_changed_cb()
 */
int utc_badge_register_changed_cb_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_register_changed_cb(NULL, NULL);
	assert_eq(ret, BADGE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_badge_register_changed_cb_p
 * @since_tizen		2.3
 * @description		Positive test case of badge_register_changed_cb()
 */
int utc_badge_register_changed_cb_p(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_register_changed_cb(change_cb, NULL);
	assert_eq(ret, BADGE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_badge_unregister_changed_cb_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_unregister_changed_cb()
 */
int utc_badge_unregister_changed_cb_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_unregister_changed_cb(NULL);
	assert_eq(ret, BADGE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_badge_unregister_changed_cb_p
 * @since_tizen		2.3
 * @description		Positive test case of badge_unregister_changed_cb()
 */
int utc_badge_unregister_changed_cb_p(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_register_changed_cb(change_cb, NULL);
	assert_eq(ret, BADGE_ERROR_NONE);

	ret = badge_unregister_changed_cb(change_cb);
	assert_eq(ret, BADGE_ERROR_NONE);

	return 0;
}

bool foreach_cb(const char *app_id, unsigned int count, void *user_data)
{
	return true;
}

/*
 * @testcase		utc_badge_foreach_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_foreach()
 */
int utc_badge_foreach_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_foreach(NULL, NULL);
	assert_eq(ret, BADGE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_badge_foreach_p
 * @since_tizen		2.3
 * @description		Positive test case of badge_foreach()
 */
int utc_badge_foreach_p(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	ret = badge_add(NULL);
	assert_eq(ret, BADGE_ERROR_NONE);
	ret = badge_foreach(foreach_cb, NULL);
	assert_eq(ret, BADGE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_badge_add_n
 * @since_tizen		2.3
 * @description		Negative test case of badge_add()
 */
int utc_badge_add_n(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	/* Creating a badge of other application which is not signed with same noncerticate should be failed */
	ret = badge_add("org.tizen.badge_noncert_app");
	assert_eq(ret, BADGE_ERROR_INVALID_PACKAGE);

	return 0;
}

/**
 * @testcase		utc_badge_add_p
 * @since_tizen		2.3
 * @description		Positive test case of badge_add()
 */
int utc_badge_add_p(void)
{
	int ret;

	CHECK_BADGE_FEATURE();

	/* Passing the null value to badge_add means creating a badge of myself */
	ret = badge_add(NULL);
	assert_eq(ret, BADGE_ERROR_NONE);

	return 0;
}
