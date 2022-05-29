/*
 * Copyright (c) 2017 Samsung Electronics Co., Ltd
 *
 * Licensed under the Flora License, Version 1.1 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://floralicense.org/license/
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "assert.h"
#include <utils_i18n.h>

#define BUFSIZE 128

static int ret = I18N_ERROR_NONE;
static i18n_uchar_iter_h uchar_iter = NULL;

static const char *char_string = "Uchar test string";
static i18n_uchar *uchar_string;
static const char *utf16be_string = "UChar test string";
static const char *utf8_string = "UChar test string";


/**
 * @function        utc_capi_base_utils_uchar_iter_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_uchar_iter_startup(void)
{
	ret = i18n_uchar_iter_create(&uchar_iter);
}

/**
 * @function        utc_capi_base_utils_uchar_iter_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_uchar_iter_cleanup(void)
{
	if (uchar_iter != NULL) {
		i18n_uchar_iter_destroy(uchar_iter);
		uchar_iter = NULL;
	}
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_set_string_p
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_set_string to check whether the string will be set properly.
 */
int utc_capi_base_utils_i18n_uchar_iter_set_string_p(void)
{
	i18n_ustring_copy_ua_n(uchar_string, char_string, BUFSIZE);

	int32_t ulen = i18n_ustring_get_length(uchar_string);

	ret = i18n_uchar_iter_set_string(uchar_iter, uchar_string, ulen);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_set_string_n
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_set_string passing invalid i18n_uchar_iter_h object and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_set_string_n(void)
{
	i18n_ustring_copy_ua_n(uchar_string, char_string, BUFSIZE);
	int32_t ulen = i18n_ustring_get_length(uchar_string);

	ret = i18n_uchar_iter_set_string(NULL, uchar_string, ulen);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_set_string_n2
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_set_string passing invalid length and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_set_string_n2(void)
{
	ret = i18n_uchar_iter_set_string(uchar_iter, uchar_string, -2);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_set_utf16be_p
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_set_utf16be to check whether the string will be set properly.
 */
int utc_capi_base_utils_i18n_uchar_iter_set_utf16be_p(void)
{
	int32_t len = strlen(utf16be_string);

	ret = i18n_uchar_iter_set_utf16be(uchar_iter, utf16be_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_set_utf16be_n
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_set_utf16be passing invalid i18n_uchar_iter_h object and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_set_utf16be_n(void)
{
	int32_t len = strlen(utf16be_string);

	ret = i18n_uchar_iter_set_utf16be(NULL, utf16be_string, len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_set_utf16be_n2
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_set_utf16be passing invalid length and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_set_utf16be_n2(void)
{
	ret = i18n_uchar_iter_set_utf16be(uchar_iter, utf16be_string, -2);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_set_utf8_p
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_set_utf8 to check whether the string will be set properly.
 */
int utc_capi_base_utils_i18n_uchar_iter_set_utf8_p(void)
{
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_set_utf8_n
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_set_utf8 passing invalid i18n_uchar_iter_h object and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_set_utf8_n(void)
{
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(NULL, utf8_string, len);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_set_utf8_n2
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_set_utf8 passing invalid length and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_set_utf8_n2(void)
{
	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, -2);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_get_index_p
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_get_index to check whether the returned index will be correct.
 */
int utc_capi_base_utils_i18n_uchar_iter_get_index_p(void)
{
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t index;
	ret = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 0);

	ret = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_LENGTH, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 17);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_get_index_n
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_get_index passing invalid i18n_uchar_iter_h object and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_get_index_n(void)
{
	int32_t index;
	ret = i18n_uchar_iter_get_index(NULL, I18N_UCHAR_ITER_CURRENT, &index);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_get_index_n2
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_get_index passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_get_index_n2(void)
{
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_move_p
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_move to check whether no error occures.
 */
int utc_capi_base_utils_i18n_uchar_iter_move_p(void)
{
	int32_t delta = 2;
	int32_t len = strlen(utf8_string);
	int32_t index;

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_START, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 2);

	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_CURRENT, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 4);

	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_START, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 2);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_move_n
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_move passing invalid i18n_uchar_iter_h object and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_move_n(void)
{
	int delta = 2;
	int32_t index;
	ret = i18n_uchar_iter_move(NULL, delta, I18N_UCHAR_ITER_CURRENT, &index);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_move_n2
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_move passing invalid index and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_move_n2(void)
{
	int32_t delta = 2;
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_START, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_has_next_p
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_has_next to check whether no error occures.
 */
int utc_capi_base_utils_i18n_uchar_iter_has_next_p(void)
{
	int delta = 0;
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t index;
	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_START, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 0);

	bool has_next;
	ret = i18n_uchar_iter_has_next(uchar_iter, &has_next);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(has_next, true);

	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_LENGTH, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 17);

	ret = i18n_uchar_iter_has_next(uchar_iter, &has_next);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(has_next, false);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_has_next_n
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_has_next passing invalid i18n_uchar_iter_h object and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_has_next_n(void)
{
	bool has_next;
	ret = i18n_uchar_iter_has_next(NULL, &has_next);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_has_next_n2
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_has_next passing invalid has_next and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_has_next_n2(void)
{
	int delta = 0;
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t index;
	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_START, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 0);

	ret = i18n_uchar_iter_has_next(uchar_iter, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_has_previous_p
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_has_previous to check whether no error occures.
 */
int utc_capi_base_utils_i18n_uchar_iter_has_previous_p(void)
{
	int delta = 0;
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t index;
	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_START, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 0);

	bool has_previous;
	ret = i18n_uchar_iter_has_previous(uchar_iter, &has_previous);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(has_previous, false);

	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_LENGTH, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 17);

	ret = i18n_uchar_iter_has_previous(uchar_iter, &has_previous);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(has_previous, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_has_previous_n
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_has_previous passing invalid i18n_uchar_iter_h object and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_has_previous_n(void)
{
	bool has_previous;
	ret = i18n_uchar_iter_has_previous(NULL, &has_previous);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_has_previous_n2
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_has_previous passing invalid has_previous and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_has_previous_n2(void)
{
	int delta = 0;
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t index;
	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_START, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 0);

	ret = i18n_uchar_iter_has_previous(uchar_iter, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_current_p
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_current to check whether no error occures.
 */
int utc_capi_base_utils_i18n_uchar_iter_current_p(void)
{
	int delta = 0;
	int delta2 = -1;
	int32_t len = strlen(utf8_string);

	i18n_uchar32 current;

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t index;
	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_START, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 0);

	ret = i18n_uchar_iter_current(uchar_iter, &current);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(current, 'U');

	ret = i18n_uchar_iter_move(uchar_iter, delta2, I18N_UCHAR_ITER_LENGTH, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 16);

	ret = i18n_uchar_iter_current(uchar_iter, &current);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(current, 'g');

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_current_n
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_current passing invalid i18n_uchar_iter_h object and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_current_n(void)
{
	int32_t current;

	ret = i18n_uchar_iter_current(NULL, &current);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_current_n2
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_current passing invalid current and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_current_n2(void)
{
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uchar_iter_current(uchar_iter, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_next_p
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_next to check whether no error occures.
 */
int utc_capi_base_utils_i18n_uchar_iter_next_p(void)
{
	int delta = 0;
	int32_t len = strlen(utf8_string);

	i18n_uchar32 current;

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t index;
	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_START, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 0);

	ret = i18n_uchar_iter_next(uchar_iter, &current);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(current, 'U');

	ret = i18n_uchar_iter_next(uchar_iter, &current);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(current, 'C');

	ret = i18n_uchar_iter_next(uchar_iter, &current);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(current, 'h');

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_next_n
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_next passing invalid i18n_uchar_iter_h object and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_next_n(void)
{
	i18n_uchar32 current;

	ret = i18n_uchar_iter_next(NULL, &current);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_next_n2
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_next passing invalid current and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_next_n2(void)
{
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uchar_iter_next(uchar_iter, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_previous_p
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_previous to check whether no error occures.
 */
int utc_capi_base_utils_i18n_uchar_iter_previous_p(void)
{
	int delta = 0;
	int32_t len = strlen(utf8_string);

	i18n_uchar32 current;

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t index;
	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_LENGTH, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 17);

	ret = i18n_uchar_iter_previous(uchar_iter, &current);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(current, 'g');

	ret = i18n_uchar_iter_previous(uchar_iter, &current);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(current, 'n');

	ret = i18n_uchar_iter_previous(uchar_iter, &current);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(current, 'i');

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_previous_n
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_previous passing invalid i18n_uchar_iter_h object and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_previous_n(void)
{
	i18n_uchar32 current;

	ret = i18n_uchar_iter_previous(NULL, &current);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_previous_n2
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_previous passing invalid current and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_previous_n2(void)
{
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uchar_iter_previous(uchar_iter, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_get_state_p
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_get_state to check whether the returned state is correct.
 */
int utc_capi_base_utils_i18n_uchar_iter_get_state_p(void)
{
	int delta = 0;
	int32_t len = strlen(utf8_string);

	uint32_t state;

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t index;
	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_LENGTH, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 17);

	ret = i18n_uchar_iter_get_state(uchar_iter, &state);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_get_state_n
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_get_state passing invalid i18n_uchar_iter_h object and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_get_state_n(void)
{
	uint32_t state;

	ret = i18n_uchar_iter_get_state(NULL, &state);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_get_state_n2
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_get_state passing invalid state and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_get_state_n2(void)
{
	int32_t len = strlen(utf8_string);

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uchar_iter_get_state(uchar_iter, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_set_state_p
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_set_state to check whether the state will be set properly.
 */
int utc_capi_base_utils_i18n_uchar_iter_set_state_p(void)
{
	int delta = 0;
	int32_t len = strlen(utf8_string);

	uint32_t state;

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t index;
	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_LENGTH, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	ret = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 17);

	ret = i18n_uchar_iter_get_state(uchar_iter, &state);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uchar_iter_move(uchar_iter, delta, I18N_UCHAR_ITER_START, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 0);

	ret = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 0);

	ret = i18n_uchar_iter_set_state(uchar_iter, state);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(index, 17);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_uchar_iter_set_state_n
 * @since_tizen 4.0
 * @description Calls i18n_uchar_iter_set_state passing invalid i18n_uchar_iter_h object and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_uchar_iter_set_state_n(void)
{
	int32_t len = strlen(utf8_string);
	uint32_t state;

	ret = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uchar_iter_get_state(uchar_iter, &state);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_uchar_iter_set_state(NULL, state);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}
