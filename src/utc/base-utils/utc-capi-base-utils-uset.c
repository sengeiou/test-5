#include "assert.h"
#include <string.h>
#include <utils_i18n.h>

//& set: capi-base-utils-uset

static i18n_error_code_e ret = I18N_ERROR_NONE;
static i18n_uset_h uset = NULL;
static i18n_uchar32 start = 0x41;
static i18n_uchar32 end = 0x50;
static i18n_uchar *upattern = NULL;
const i18n_uchar str[] = { 'm', 'a', 'r', 'k', '\0' };

/**
 * @function        utc_capi_base_utils_uset_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_uset_startup(void)
{
    ret = i18n_uset_create(start, end, &uset);
}

/**
 * @function        utc_capi_base_utils_uset_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_uset_cleanup(void)
{
    if (upattern) {
        free(upattern);
        upattern = NULL;
    }

    i18n_uset_destroy(uset);
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_empty_p
 * @since_tizen     2.3.1
 * @description     Creates an empty uset handle object,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_create_empty_p(void)
{
    i18n_uset_h uset = NULL;

    ret = i18n_uset_create_empty(&uset);
    assert_eq(ret, I18N_ERROR_NONE);
    i18n_uset_destroy(uset);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_empty_n
 * @since_tizen     2.3.1
 * @description     Creates an empty uset handle object,
 *                  passing invalid output handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_create_empty_n(void)
{
    ret = i18n_uset_create_empty(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_p
 * @since_tizen     2.3.1
 * @description     Creates an uset handle object that contains the range of character,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_create_p(void)
{
    assert_neq(uset, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_n
 * @since_tizen     2.3.1
 * @description     Creates an uset handle object that contains the range of character,
 *                  passing invalid output handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_create_n(void)
{
    ret = i18n_uset_create(start, end, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_pattern_p
 * @since_tizen     2.3.1
 * @description     Creates a set based on a given pattern,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_create_pattern_p(void)
{
    const char *pattern = "[:Hyphen:]";
    i18n_uchar *_pattern = NULL;
    _pattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_pattern, pattern);

    ret = i18n_uset_create_pattern(_pattern, 10, &uset);

    free(_pattern);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_pattern_n
 * @since_tizen     2.3.1
 * @description     Creates a set based on a given pattern,
 *                  passing invalid pattern, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_create_pattern_n(void)
{
    ret = i18n_uset_create_pattern(NULL, 10, &uset);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_pattern_n2
 * @since_tizen     2.3.1
 * @description     Creates a set based on a given pattern,
 *                  passing invalid pattern length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_create_pattern_n2(void)
{
    char *pattern = "[:Hyphen:]";
    i18n_uchar *_pattern = NULL;
    _pattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_pattern, pattern);

    ret = i18n_uset_create_pattern(_pattern, -2, &uset);

    free(_pattern);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_pattern_n3
 * @since_tizen     2.3.1
 * @description     Creates a set based on a given pattern,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_create_pattern_n3(void)
{
    char *pattern = "[:Hyphen:]";
    i18n_uchar *_pattern = NULL;
    _pattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_pattern, pattern);

    ret = i18n_uset_create_pattern(_pattern, 10, NULL);

    free(_pattern);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_pattern_options_p
 * @since_tizen     2.3.1
 * @description     Creates a set based on a given pattern,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_create_pattern_options_p(void)
{
    char *pattern = "[:Hyphen:]";
    i18n_uchar *_pattern = NULL;
    _pattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_pattern, pattern);

    ret = i18n_uset_create_pattern_options(_pattern, 10, I18N_USET_IGNORE_SPACE, &uset);

    free(_pattern);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_pattern_options_n
 * @since_tizen     2.3.1
 * @description     Creates a set based on a given pattern,
 *                  passing invalid pattern, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_create_pattern_options_n(void)
{
    ret = i18n_uset_create_pattern_options(NULL, 10, I18N_USET_IGNORE_SPACE, &uset);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_pattern_options_n2
 * @since_tizen     2.3.1
 * @description     Creates a set based on a given pattern,
 *                  passing invalid pattern length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_create_pattern_options_n2(void)
{
    const char *pattern = "[:Hyphen:]";
    i18n_uchar *_pattern = NULL;
    _pattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_pattern, pattern);

    ret = i18n_uset_create_pattern_options(_pattern, -2, I18N_USET_IGNORE_SPACE, &uset);

    free(_pattern);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_pattern_options_n3
 * @since_tizen     2.3.1
 * @description     Creates a set based on a given pattern,
 *                  passing invalid pattern options, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_create_pattern_options_n3(void)
{
    const char *pattern = "[:Hyphen:]";
    i18n_uchar *_pattern = NULL;
    _pattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_pattern, pattern);

    ret = i18n_uset_create_pattern_options(_pattern, 10, -1, &uset);

    free(_pattern);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_create_pattern_options_n4
 * @since_tizen     2.3.1
 * @description     Creates a set based on a given pattern,
 *                  passing invalid uset, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_create_pattern_options_n4(void)
{
    const char *pattern = "[:Hyphen:]";
    i18n_uchar *_pattern = NULL;
    _pattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_pattern, pattern);

    ret = i18n_uset_create_pattern_options(_pattern, 10, I18N_USET_IGNORE_SPACE, NULL);

    free(_pattern);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_destroy_p
 * @since_tizen     2.3.1
 * @description     Disposes of the storage used by a uset handle object,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_destroy_p(void)
{
    ret = i18n_uset_destroy(uset);
    assert_eq(ret, I18N_ERROR_NONE);
    uset = NULL;

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_destroy_n
 * @since_tizen     2.3.1
 * @description     Disposes of the storage used by a uset handle object,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_destroy_n(void)
{
    ret = i18n_uset_destroy(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_clone_p
 * @since_tizen     2.3.1
 * @description     Returns a copy of this object,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_clone_p(void)
{
    assert_neq(uset, NULL);
    i18n_uset_h uset_c = NULL;

    ret = i18n_uset_clone(uset, &uset_c);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_destroy(uset_c);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_clone_n
 * @since_tizen     2.3.1
 * @description     Returns a copy of this object,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_clone_n(void)
{
    i18n_uset_h set_clone = NULL;

    ret = i18n_uset_clone(NULL, &set_clone);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_clone_n2
 * @since_tizen     2.3.1
 * @description     Returns a copy of this object,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_clone_n2(void)
{
    ret = i18n_uset_clone(uset, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_is_frozen_p
 * @since_tizen     2.3.1
 * @description     Determines whether the set has been frozen,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_is_frozen_p(void)
{
    assert_neq(uset, NULL);

    i18n_uset_is_frozen(uset);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_is_frozen_n
 * @since_tizen     2.3.1
 * @description     Determines whether the set has been frozen,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_is_frozen_n(void)
{
    i18n_uset_is_frozen(NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_freeze_p
 * @since_tizen     2.3.1
 * @description     Freezes the set,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_freeze_p(void)
{
    assert_neq(uset, NULL);
    ret = i18n_uset_freeze(uset);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_freeze_n
 * @since_tizen     2.3.1
 * @description     Freezes the set,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_freeze_n(void)
{
    ret = i18n_uset_freeze(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_clone_as_thawed_p
 * @since_tizen     2.3.1
 * @description     Clones the set and make the clone mutable,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_clone_as_thawed_p(void)
{
    assert_neq(uset, NULL);
    i18n_uset_h uset_c = NULL;

    ret = i18n_uset_clone_as_thawed(uset, &uset_c);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_destroy(uset_c);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_clone_as_thawed_n
 * @since_tizen     2.3.1
 * @description     Clones the set and make the clone mutable,
 *                  passing invalid uset output handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_clone_as_thawed_n(void)
{
    ret = i18n_uset_clone_as_thawed(uset, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_clone_as_thawed_n2
 * @since_tizen     2.3.1
 * @description     Clones the set and make the clone mutable,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_clone_as_thawed_n2(void)
{
    i18n_uset_h set_copy = NULL;

    ret = i18n_uset_clone_as_thawed(NULL, &set_copy);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_set_p
 * @since_tizen     2.3.1
 * @description     Causes the uset handle object to represent the given range,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_set_p(void)
{
    assert_neq(uset, NULL);

    ret = i18n_uset_set(uset, start, end);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_set_n
 * @since_tizen     2.3.1
 * @description     Causes the uset handle object to represent the given range,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_set_n(void)
{
    ret = i18n_uset_set(NULL, start, end);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_pattern_p
 * @since_tizen     2.3.1
 * @description     Modifies the set to represent the set specified by the give,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_apply_pattern_p(void)
{
    assert_neq(uset, NULL);
    const char *pattern = "[:Hyphen:]";

    upattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(upattern, pattern);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_apply_pattern(uset, upattern, -1, I18N_USET_IGNORE_SPACE);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_pattern_n
 * @since_tizen     2.3.1
 * @description     Modifies the set to represent the set specified by the give,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_uset_apply_pattern_n(void)
{
    const char *pattern = "[:Hyphen:]";

    upattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(upattern, pattern);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_apply_pattern(NULL, upattern, -1, I18N_USET_IGNORE_SPACE);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_pattern_n2
 * @since_tizen     2.3.1
 * @description     Modifies the set to represent the set specified by the give,
 *                  passing invalid pattern, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_apply_pattern_n2(void)
{
    i18n_uset_apply_pattern(uset, NULL, -1, I18N_USET_IGNORE_SPACE);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_pattern_n3
 * @since_tizen     2.3.1
 * @description     Modifies the set to represent the set specified by the give,
 *                  passing invalid pattern length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_apply_pattern_n3(void)
{
    const char *pattern = "[:Hyphen:]";

    upattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(upattern, pattern);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_apply_pattern(uset, upattern, -2, I18N_USET_IGNORE_SPACE);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_pattern_n4
 * @since_tizen     2.3.1
 * @description     Modifies the set to represent the set specified by the give,
 *                  passing invalid pattern options, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_apply_pattern_n4(void)
{
    const char *pattern = "[:Hyphen:]";

    upattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(upattern, pattern);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_apply_pattern(uset, upattern, -1, -1);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_int_property_value_p
 * @since_tizen     2.3.1
 * @description     Modifies the set to contain those code points which have the given value,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_apply_int_property_value_p(void)
{
    i18n_uchar_uproperty_e prop = I18N_UCHAR_NUMERIC_TYPE;
    int32_t value = 10;

    ret = i18n_uset_apply_int_property_value(uset, prop, value);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_int_property_value_n
 * @since_tizen     2.3.1
 * @description     Modifies the set to contain those code points which have the given value,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_apply_int_property_value_n(void)
{
    i18n_uchar_uproperty_e prop = I18N_UCHAR_ALPHABETIC;
    int32_t value = (int32_t)false;

    ret = i18n_uset_apply_int_property_value(NULL, prop, value);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_int_property_value_n2
 * @since_tizen     2.3.1
 * @description     Modifies the set to contain those code points which have the given value,
 *                  passing invalid property parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_apply_int_property_value_n2(void)
{
    int32_t value = (int32_t)false;

    ret = i18n_uset_apply_int_property_value(uset, -1, value);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_int_property_value_n3
 * @since_tizen     2.3.1
 * @description     Modifies the set to contain those code points which have the given value,
 *                  passing value out of range, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_apply_int_property_value_n3(void)
{
    i18n_uchar_uproperty_e prop = I18N_UCHAR_ALPHABETIC;

    ret = i18n_uset_apply_int_property_value(uset, prop, -1);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_property_alias_p
 * @since_tizen     2.3.1
 * @description     Modifies the set to contain those code points which have the,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_apply_property_alias_p(void)
{
    const i18n_uchar prop[] = { 0x6C, 0x62, 0x0 }; /* "lb" */
    int32_t prop_length = 3;
    const i18n_uchar value[] = { 0x53, 0x50, 0x0 }; /* "SP" */
    int32_t value_length = 3;

    ret = i18n_uset_apply_property_alias(uset, prop, prop_length, value, value_length);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_property_alias_n
 * @since_tizen     2.3.1
 * @description     Modifies the set to contain those code points which have the,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_apply_property_alias_n(void)
{
    const i18n_uchar prop[] = { 0x6C, 0x62, 0x0 }; /* "lb" */
    int32_t prop_length = -1;
    const i18n_uchar value[] = { 0x53, 0x50, 0x0 }; /* "SP" */
    int32_t value_length = -1;

    ret = i18n_uset_apply_property_alias(NULL, prop, prop_length, value, value_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_property_alias_n2
 * @since_tizen     2.3.1
 * @description     Modifies the set to contain those code points which have the,
 *                  passing invalid property alias, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_apply_property_alias_n2(void)
{
    int32_t prop_length = -1;
    const i18n_uchar value[] = { 0x53, 0x50, 0x0 }; /* "SP" */
    int32_t value_length = -1;

    ret = i18n_uset_apply_property_alias(uset, NULL, prop_length, value, value_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_property_alias_n3
 * @since_tizen     2.3.1
 * @description     Modifies the set to contain those code points which have the,
 *                  passing invalid property length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_apply_property_alias_n3(void)
{
    const i18n_uchar prop[] = { 0x6C, 0x62, 0x0 }; /* "lb" */
    const i18n_uchar value[] = { 0x53, 0x50, 0x0 }; /* "SP" */
    int32_t value_length = -1;

    ret = i18n_uset_apply_property_alias(uset, prop, -2, value, value_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_property_alias_n4
 * @since_tizen     2.3.1
 * @description     Modifies the set to contain those code points which have the,
 *                  passing invalid property value, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_apply_property_alias_n4(void)
{
    const i18n_uchar prop[] = { 0x6C, 0x62, 0x0 }; /* "lb" */
    int32_t prop_length = -1;
    int32_t value_length = -1;

    ret = i18n_uset_apply_property_alias(uset, prop, prop_length, NULL, value_length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_apply_property_alias_n5
 * @since_tizen     2.3.1
 * @description     Modifies the set to contain those code points which have the,
 *                  passing invalid value length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_apply_property_alias_n5(void)
{
    const i18n_uchar prop[] = { 0x6C, 0x62, 0x0 }; /* "lb" */
    int32_t prop_length = -1;
    const i18n_uchar value[] = { 0x53, 0x50, 0x0 }; /* "SP" */

    ret = i18n_uset_apply_property_alias(uset, prop, prop_length, value, -2);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_resembles_pattern_p
 * @since_tizen     2.3.1
 * @description     Return true if the given position, in the given pattern,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_resembles_pattern_p(void)
{
    const char *pattern = "[:NewPattern:]";
    i18n_uchar *upattern = NULL;
    int32_t upattern_length = -1;
    int32_t pos = 0;

    upattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(upattern, pattern);

    i18n_uset_resembles_pattern(upattern, upattern_length, pos);

    free(upattern);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_resembles_pattern_n
 * @since_tizen     2.3.1
 * @description     Return true if the given position, in the given pattern,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_resembles_pattern_n(void)
{
    int32_t upattern_length = -1;
    int32_t pos = 0;

    i18n_uset_resembles_pattern(NULL, upattern_length, pos);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_resembles_pattern_n2
 * @since_tizen     2.3.1
 * @description     Return true if the given position, in the given pattern,
 *                  passing invalid pattern length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_resembles_pattern_n2(void)
{
    const char *pattern = "[:NewPattern:]";
    i18n_uchar *upattern = NULL;
    int32_t pos = 0;

    upattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(upattern, pattern);

    i18n_uset_resembles_pattern(upattern, -2, pos);

    free(upattern);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_resembles_pattern_n3
 * @since_tizen     2.3.1
 * @description     Return true if the given position, in the given pattern,
 *                  passing invalid position parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_resembles_pattern_n3(void)
{
    char *pattern = "[:NewPattern:]";
    i18n_uchar *upattern = NULL;
    int32_t upattern_length = -1;

    upattern = (i18n_uchar*)calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(upattern, pattern);

    i18n_uset_resembles_pattern(upattern, upattern_length, -1);

    free(upattern);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_to_pattern_p
 * @since_tizen     2.3.1
 * @description     Returns a string representation of the given set,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_to_pattern_p(void)
{
    i18n_uchar res[12] = { 0, };
    int32_t res_capacity = sizeof(res) / sizeof(res[0]);
    i18n_ubool escape_unprintable = true;

    i18n_uset_to_pattern(uset, res, res_capacity, escape_unprintable);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_to_pattern_n
 * @since_tizen     2.3.1
 * @description     Returns a string representation of the given set,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_to_pattern_n(void)
{
    i18n_uchar res[12] = { 0, };
    int32_t res_capacity = sizeof(res) / sizeof(res[0]);
    i18n_ubool escape_unprintable = true;

    i18n_uset_to_pattern(NULL, res, res_capacity, escape_unprintable);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_to_pattern_n2
 * @since_tizen     2.3.1
 * @description     Returns a string representation of the given set,
 *                  passing invalid output buffer, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_to_pattern_n2(void)
{
    i18n_uchar res[12] = { 0, };
    int32_t res_capacity = sizeof(res) / sizeof(res[0]);
    i18n_ubool escape_unprintable = true;

    i18n_uset_to_pattern(uset, NULL, res_capacity, escape_unprintable);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_to_pattern_n3
 * @since_tizen     2.3.1
 * @description     Returns a string representation of the given set,
 *                  passing invalid result capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_to_pattern_n3(void)
{
    i18n_uchar res[12] = { 0, };
    i18n_ubool escape_unprintable = true;

    i18n_uset_to_pattern(uset, res, -1, escape_unprintable);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_p
 * @since_tizen     2.3.1
 * @description     Adds the given character to the given uset handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_add_p(void)
{
    i18n_uchar32 c = 0x61;

    ret = i18n_uset_add(uset, c);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_n
 * @since_tizen     2.3.1
 * @description     Adds the given character to the given uset handle,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_add_n(void)
{
    i18n_uchar32 c = 0x61;

    ret = i18n_uset_add(NULL, c);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_all_p
 * @since_tizen     2.3.1
 * @description     Adds all of the elements in the specified set to this set if,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_add_all_p(void)
{
    i18n_uset_h uset_add = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset_add);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_uset_add_all(uset, uset_add);

    i18n_uset_destroy(uset_add);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_all_n
 * @since_tizen     2.3.1
 * @description     Adds all of the elements in the specified set to this set if,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_add_all_n(void)
{
    i18n_uset_h uset_add = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset_add);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_uset_add_all(NULL, uset_add);

    i18n_uset_destroy(uset_add);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_all_n2
 * @since_tizen     2.3.1
 * @description     Adds all of the elements in the specified set to this set if,
 *                  passing invalid addition set, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_add_all_n2(void)
{
    ret = i18n_uset_add_all(uset, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_range_p
 * @since_tizen     2.3.1
 * @description     Adds the given range of characters to the given uset handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_add_range_p(void)
{
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_add_range(uset, start, end);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_range_n
 * @since_tizen     2.3.1
 * @description     Adds the given range of characters to the given uset handle,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_add_range_n(void)
{
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_add_range(NULL, start, end);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_string_p
 * @since_tizen     2.3.1
 * @description     Adds the given string to the given uset handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_add_string_p(void)
{
    int32_t str_len = -1;

    ret = i18n_uset_add_string(uset, str, str_len);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_string_n
 * @since_tizen     2.3.1
 * @description     Adds the given string to the given uset handle,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_add_string_n(void)
{
    int32_t str_len = -1;

    ret = i18n_uset_add_string(NULL, str, str_len);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_string_n2
 * @since_tizen     2.3.1
 * @description     Adds the given string to the given uset handle,
 *                  passing invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_add_string_n2(void)
{
    int32_t str_len = -1;

    ret = i18n_uset_add_string(uset, NULL, str_len);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_string_n3
 * @since_tizen     2.3.1
 * @description     Adds the given string to the given uset handle,
 *                  passing invalid string length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_add_string_n3(void)
{
    ret = i18n_uset_add_string(uset, str, -2);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_all_code_points_p
 * @since_tizen     2.3.1
 * @description     Adds each of the characters in this string to the set,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_add_all_code_points_p(void)
{
    int32_t str_len = -1;

    ret = i18n_uset_add_all_code_points(uset, str, str_len);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_all_code_points_n
 * @since_tizen     2.3.1
 * @description     Adds each of the characters in this string to the set,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_add_all_code_points_n(void)
{
    int32_t str_len = -1;

    ret = i18n_uset_add_all_code_points(NULL, str, str_len);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_all_code_points_n2
 * @since_tizen     2.3.1
 * @description     Adds each of the characters in this string to the set,
 *                  passing invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_add_all_code_points_n2(void)
{
    int32_t str_len = -1;

    ret = i18n_uset_add_all_code_points(uset, NULL, str_len);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_add_all_code_points_n3
 * @since_tizen     2.3.1
 * @description     Adds each of the characters in this string to the set,
 *                  passing invalid string length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_add_all_code_points_n3(void)
{
    ret = i18n_uset_add_all_code_points(uset, str, -2);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_p
 * @since_tizen     2.3.1
 * @description     Removes the given character from the given uset handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_remove_p(void)
{
    i18n_uchar32 c = 0x51;

    ret = i18n_uset_remove(uset, c);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_n
 * @since_tizen     2.3.1
 * @description     Removes the given character from the given uset handle,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_remove_n(void)
{
    i18n_uchar32 c = 0x51;

    ret = i18n_uset_remove(NULL, c);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_range_p
 * @since_tizen     2.3.1
 * @description     Removes the given range of characters from the given uset handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_remove_range_p(void)
{
    i18n_uchar32 start = 0x41;
    i18n_uchar32 end = 0x45;

    ret = i18n_uset_remove_range(uset, start, end);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_range_n
 * @since_tizen     2.3.1
 * @description     Removes the given range of characters from the given uset handle,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_remove_range_n(void)
{
    i18n_uchar32 start = 0x41;
    i18n_uchar32 end = 0x45;

    ret = i18n_uset_remove_range(NULL, start, end);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_string_p
 * @since_tizen     2.3.1
 * @description     Removes the given string to the given uset handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_remove_string_p(void)
{
    int32_t str_len = -1;

    ret = i18n_uset_add_string(uset, str, str_len);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_uset_remove_string(uset, str, str_len);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_string_n
 * @since_tizen     2.3.1
 * @description     Removes the given string to the given uset handle,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_remove_string_n(void)
{
    int32_t str_len = -1;

    ret = i18n_uset_remove_string(NULL, str, str_len);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_string_n2
 * @since_tizen     2.3.1
 * @description     Removes the given string to the given uset handle,
 *                  passing invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_remove_string_n2(void)
{
    int32_t str_len = -1;

    ret = i18n_uset_remove_string(uset, NULL, str_len);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_string_n3
 * @since_tizen     2.3.1
 * @description     Removes the given string to the given uset handle,
 *                  passing invalid string length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_remove_string_n3(void)
{
    ret = i18n_uset_remove_string(uset, str, -2);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_all_p
 * @since_tizen     2.3.1
 * @description     Removes from this set all of its elements that are contained in the specified set,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_remove_all_p(void)
{
    i18n_uset_h uset_rv = NULL;
    i18n_uchar32 start = 0x45;
    i18n_uchar32 end = 0x50;

    ret = i18n_uset_create(start, end, &uset_rv);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_uset_remove_all(uset, uset_rv);

    i18n_uset_destroy(uset_rv);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_all_n
 * @since_tizen     2.3.1
 * @description     Removes from this set all of its elements that are contained in the specified set,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_remove_all_n(void)
{
    i18n_uset_h uset_rv = NULL;
    i18n_uchar32 start = 0x45;
    i18n_uchar32 end = 0x50;

    ret = i18n_uset_create(start, end, &uset_rv);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_uset_remove_all(NULL, uset_rv);

    i18n_uset_destroy(uset_rv);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_all_n2
 * @since_tizen     2.3.1
 * @description     Removes from this set all of its elements that are contained in the specified set,
 *                  passing invalid uset, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_remove_all_n2(void)
{
    ret = i18n_uset_remove_all(uset, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_retain_p
 * @since_tizen     2.3.1
 * @description     Retains only the elements in this set that are contained in the specified range,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_retain_p(void)
{
    i18n_uchar32 start = 0x41;
    i18n_uchar32 end = 0x42;

    ret = i18n_uset_retain(uset, start, end);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_retain_n
 * @since_tizen     2.3.1
 * @description     Retains only the elements in this set that are contained in the specified range,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_retain_n(void)
{
    i18n_uchar32 start = 0x41;
    i18n_uchar32 end = 0x42;

    ret = i18n_uset_retain(NULL, start, end);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_retain_all_p
 * @since_tizen     2.3.1
 * @description     Retains only the elements in this set that are contained in the,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_retain_all_p(void)
{
    i18n_uset_h uset_ret = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset_ret);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_uset_retain_all(uset, uset_ret);

    i18n_uset_destroy(uset_ret);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_retain_all_n
 * @since_tizen     2.3.1
 * @description     Retains only the elements in this set that are contained in the,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_retain_all_n(void)
{
    i18n_uset_h uset_ret = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset_ret);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_uset_retain_all(NULL, uset_ret);

    i18n_uset_destroy(uset_ret);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_retain_all_n2
 * @since_tizen     2.3.1
 * @description     Retains only the elements in this set that are contained in the,
 *                  passing invalid uset, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_retain_all_n2(void)
{
    ret = i18n_uset_retain_all(uset, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_compact_p
 * @since_tizen     2.3.1
 * @description     Reallocates this objects internal structures to take up the leas,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_compact_p(void)
{
    ret = i18n_uset_compact(uset);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_compact_n
 * @since_tizen     2.3.1
 * @description     Reallocates this objects internal structures to take up the leas,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_compact_n(void)
{
    ret = i18n_uset_compact(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_complement_p
 * @since_tizen     2.3.1
 * @description     Inverts this set.  This operation modifies this set so tha,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_complement_p(void)
{
    ret = i18n_uset_complement(uset);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_complement_n
 * @since_tizen     2.3.1
 * @description     Inverts this set.  This operation modifies this set so tha,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_complement_n(void)
{
    ret = i18n_uset_complement(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_complement_all_p
 * @since_tizen     2.3.1
 * @description     Complements in this set all elements contained in the specified set,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_complement_all_p(void)
{
    i18n_uset_h uset_com = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset_com);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_uset_complement_all(uset, uset_com);

    i18n_uset_destroy(uset_com);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_complement_all_n
 * @since_tizen     2.3.1
 * @description     Complements in this set all elements contained in the specified set,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_complement_all_n(void)
{
    i18n_uset_h uset_com = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset_com);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_uset_complement_all(NULL, uset_com);

    i18n_uset_destroy(uset_com);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_complement_all_n2
 * @since_tizen     2.3.1
 * @description     Complements in this set all elements contained in the specified set,
 *                  passing invalid uset, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_complement_all_n2(void)
{
    ret = i18n_uset_complement_all(uset, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_clear_p
 * @since_tizen     2.3.1
 * @description     Removes all of the elements from this set,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_clear_p(void)
{
    ret = i18n_uset_clear(uset);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_clear_n
 * @since_tizen     2.3.1
 * @description     Removes all of the elements from this set,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_clear_n(void)
{
    ret = i18n_uset_clear(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_destroy_over_p
 * @since_tizen     2.3.1
 * @description     Closes this set over the given attribute,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_destroy_over_p(void)
{
    ret = i18n_uset_destroy_over(uset, I18N_USET_CASE_INSENSITIVE);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_destroy_over_n
 * @since_tizen     2.3.1
 * @description     Closes this set over the given attribute,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_destroy_over_n(void)
{
    ret = i18n_uset_destroy_over(NULL, I18N_USET_CASE_INSENSITIVE);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_all_strings_p
 * @since_tizen     2.3.1
 * @description     Removes all strings from this set,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_remove_all_strings_p(void)
{
    ret = i18n_uset_remove_all_strings(uset);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_remove_all_strings_n
 * @since_tizen     2.3.1
 * @description     Removes all strings from this set,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_remove_all_strings_n(void)
{
    ret = i18n_uset_remove_all_strings(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_is_empty_p
 * @since_tizen     2.3.1
 * @description     Returns true if the given uset handle contains no characters and n,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_is_empty_p(void)
{
    i18n_uset_is_empty(uset);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_is_empty_n
 * @since_tizen     2.3.1
 * @description     Returns true if the given uset handle contains no characters and n,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_is_empty_n(void)
{
    i18n_uset_is_empty(NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_p
 * @since_tizen     2.3.1
 * @description     Returns @c true if the given uset handle contains the given character,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_contains_p(void)
{
    i18n_uchar32 c = 1;

    i18n_uset_contains(uset, c);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_n
 * @since_tizen     2.3.1
 * @description     Returns @c true if the given uset handle contains the given character,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_n(void)
{
    i18n_uchar32 c = 1;

    i18n_uset_contains(NULL, c);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_range_p
 * @since_tizen     2.3.1
 * @description     Returns true if the given uset handle contains all characters ,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_contains_range_p(void)
{
    i18n_uchar32 start = 0x41;
    i18n_uchar32 end = 0x51;

    i18n_uset_contains_range(uset, start, end);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_range_n
 * @since_tizen     2.3.1
 * @description     Returns true if the given uset handle contains all characters ,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_range_n(void)
{
    i18n_uchar32 start = 0x41;
    i18n_uchar32 end = 0x51;

    i18n_uset_contains_range(NULL, start, end);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_string_p
 * @since_tizen     2.3.1
 * @description     Returns true if the given uset handle contains the given string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_contains_string_p(void)
{
    int32_t str_len = -1;

    ret = i18n_uset_add_string(uset, str, str_len);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_contains_string(uset, str, str_len);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_string_n
 * @since_tizen     2.3.1
 * @description     Returns true if the given uset handle contains the given string,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_string_n(void)
{
    int32_t str_len = -1;

    i18n_uset_contains_string(NULL, str, str_len);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_string_n2
 * @since_tizen     2.3.1
 * @description     Returns true if the given uset handle contains the given string,
 *                  passing invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_string_n2(void)
{
    int32_t str_len = -1;

    ret = i18n_uset_add_string(uset, str, str_len);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_contains_string(uset, NULL, str_len);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_string_n3
 * @since_tizen     2.3.1
 * @description     Returns true if the given uset handle contains the given string,
 *                  passing invalid string length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_string_n3(void)
{
    int32_t str_len = -1;

    ret = i18n_uset_add_string(uset, str, str_len);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_contains_string(uset, str, -2);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_index_of_p
 * @since_tizen     2.3.1
 * @description     Returns the index of the given character within this set, wher,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_index_of_p(void)
{
    i18n_uchar32 c = 0x41;

    i18n_uset_index_of(uset, c);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_index_of_n
 * @since_tizen     2.3.1
 * @description     Returns the index of the given character within this set, wher,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_index_of_n(void)
{
    i18n_uchar32 c = 0x41;

    i18n_uset_index_of(NULL, c);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_char_at_p
 * @since_tizen     2.3.1
 * @description     Returns the character at the given index within this set, wher,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_char_at_p(void)
{
    int32_t char_index = 0;

    i18n_uset_char_at(uset, char_index);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_char_at_n
 * @since_tizen     2.3.1
 * @description     Returns the character at the given index within this set, wher,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_char_at_n(void)
{
    int32_t char_index = 0;

    i18n_uset_char_at(NULL, char_index);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_char_at_n2
 * @since_tizen     2.3.1
 * @description     Returns the character at the given index within this set, wher,
 *                  passing invalid character index, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_char_at_n2(void)
{
    i18n_uset_char_at(uset, -1);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_size_p
 * @since_tizen     2.3.1
 * @description     Returns the number of characters and strings contained in the given uset handle,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_size_p(void)
{
    i18n_uset_size(uset);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_size_n
 * @since_tizen     2.3.1
 * @description     Returns the number of characters and strings contained in the given uset handle,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_size_n(void)
{
    i18n_uset_size(NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_item_count_p
 * @since_tizen     2.3.1
 * @description     Returns the number of items in this set,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_get_item_count_p(void)
{
    i18n_uset_get_item_count(uset);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_item_count_n
 * @since_tizen     2.3.1
 * @description     Returns the number of items in this set,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_item_count_n(void)
{
    i18n_uset_get_item_count(NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_item_p
 * @since_tizen     2.3.1
 * @description     Returns an item of this set,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_get_item_p(void)
{
    int32_t item_index = 0;
    i18n_uchar32 start = 0;
    i18n_uchar32 end = 0;
    i18n_uchar str[12] = { 0, };
    int32_t str_capacity = sizeof(str) / sizeof(str[0]);

    i18n_uset_get_item(uset, item_index, &start, &end, str, str_capacity);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_item_n
 * @since_tizen     2.3.1
 * @description     Returns an item of this set,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_item_n(void)
{
    int32_t item_index = 0;
    i18n_uchar32 start = 0;
    i18n_uchar32 end = 0;
    i18n_uchar str[12] = { 0, };
    int32_t str_capacity = sizeof(str) / sizeof(str[0]);

    i18n_uset_get_item(NULL, item_index, &start, &end, str, str_capacity);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_item_n2
 * @since_tizen     2.3.1
 * @description     Returns an item of this set,
 *                  passing invalid item index, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_item_n2(void)
{
    i18n_uchar32 start = 0;
    i18n_uchar32 end = 0;
    i18n_uchar str[12] = { 0, };
    int32_t str_capacity = sizeof(str) / sizeof(str[0]);

    i18n_uset_get_item(uset, -1, &start, &end, str, str_capacity);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_item_n3
 * @since_tizen     2.3.1
 * @description     Returns an item of this set,
 *                  passing invalid start pointer, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_item_n3(void)
{
    int32_t item_index = 0;
    i18n_uchar32 end = 0;
    i18n_uchar str[12] = { 0, };
    int32_t str_capacity = sizeof(str) / sizeof(str[0]);

    i18n_uset_get_item(uset, item_index, NULL, &end, str, str_capacity);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_item_n4
 * @since_tizen     2.3.1
 * @description     Returns an item of this set,
 *                  passing invalid end pointer, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_item_n4(void)
{
    int32_t item_index = 0;
    i18n_uchar32 start = 0;
    i18n_uchar str[12] = { 0, };
    int32_t str_capacity = sizeof(str) / sizeof(str[0]);

    i18n_uset_get_item(uset, item_index, &start, NULL, str, str_capacity);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_item_n5
 * @since_tizen     2.3.1
 * @description     Returns an item of this set,
 *                  passing invalid output buffer, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_item_n5(void)
{
    int32_t item_index = 0;
    i18n_uchar32 start = 0;
    i18n_uchar32 end = 0;
    i18n_uchar str[12] = { 0, };
    int32_t str_capacity = sizeof(str) / sizeof(str[0]);

    i18n_uset_get_item(uset, item_index, &start, &end, NULL, str_capacity);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_item_n6
 * @since_tizen     2.3.1
 * @description     Returns an item of this set,
 *                  passing invalid strings capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_item_n6(void)
{
    int32_t item_index = 0;
    i18n_uchar32 start = 0;
    i18n_uchar32 end = 0;
    i18n_uchar str[12] = { 0, };

    i18n_uset_get_item(uset, item_index, &start, &end, str, -2);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_all_p
 * @since_tizen     2.3.1
 * @description     Returns true if set1 contains all the characters and strings of set2,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_contains_all_p(void)
{
    i18n_uset_h uset2 = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset2);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_contains_all(uset, uset2);

    ret = get_last_result();
    i18n_uset_destroy(uset2);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_all_n
 * @since_tizen     2.3.1
 * @description     Returns true if set1 contains all the characters and strings of set2,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_all_n(void)
{
    i18n_uset_h uset2 = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset2);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_contains_all(NULL, uset2);

    ret = get_last_result();
    i18n_uset_destroy(uset2);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_all_n2
 * @since_tizen     2.3.1
 * @description     Returns true if set1 contains all the characters and strings of set2,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_all_n2(void)
{
    i18n_uset_contains_all(uset, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_all_code_points_p
 * @since_tizen     2.3.1
 * @description     Returns true if this set contains all the characters of the given string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_contains_all_code_points_p(void)
{
    int32_t str_len = -1;

    i18n_uset_contains_all_code_points(uset, str, str_len);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_all_code_points_n
 * @since_tizen     2.3.1
 * @description     Returns true if this set contains all the characters of the given string,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_all_code_points_n(void)
{
    int32_t str_len = -1;

    i18n_uset_contains_all_code_points(NULL, str, str_len);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_all_code_points_n2
 * @since_tizen     2.3.1
 * @description     Returns true if this set contains all the characters of the given string,
 *                  passing invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_all_code_points_n2(void)
{
    int32_t str_len = -1;

    i18n_uset_contains_all_code_points(uset, NULL, str_len);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_all_code_points_n3
 * @since_tizen     2.3.1
 * @description     Returns true if this set contains all the characters of the given string,
 *                  passing invalid string length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_all_code_points_n3(void)
{
    i18n_uset_contains_all_code_points(uset, str, -2);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_none_p
 * @since_tizen     2.3.1
 * @description     Returns true if set1 contains none of the characters and strings of set2,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_contains_none_p(void)
{
    i18n_uset_h uset2 = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset2);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_contains_none(uset, uset2);

    ret = get_last_result();
    i18n_uset_destroy(uset2);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_none_n
 * @since_tizen     2.3.1
 * @description     Returns true if set1 contains none of the characters and strings of set2,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_none_n(void)
{
    i18n_uset_h uset2 = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset2);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_contains_none(NULL, uset2);

    ret = get_last_result();
    i18n_uset_destroy(uset2);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_none_n2
 * @since_tizen     2.3.1
 * @description     Returns true if set1 contains none of the characters and strings of set2,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_none_n2(void)
{
    i18n_uset_contains_none(uset, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_some_p
 * @since_tizen     2.3.1
 * @description     Returns true if set1 contains some of the characters and strings of set2,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_contains_some_p(void)
{
    i18n_uset_h uset2 = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset2);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_contains_some(uset, uset2);

    ret = get_last_result();
    i18n_uset_destroy(uset2);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_some_n
 * @since_tizen     2.3.1
 * @description     Returns true if set1 contains some of the characters and strings of set2,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_some_n(void)
{
    i18n_uset_h uset2 = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset2);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_contains_some(NULL, uset2);

    ret = get_last_result();
    i18n_uset_destroy(uset2);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_contains_some_n2
 * @since_tizen     2.3.1
 * @description     Returns true if set1 contains some of the characters and strings of set2,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_contains_some_n2(void)
{
    i18n_uset_contains_some(uset, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_p
 * @since_tizen     2.3.1
 * @description     Returns the length of the initial substring of the input string which,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_span_p(void)
{
    const i18n_uchar s[] = { 'q', 'w', 'e', 'r', '\0' };
    int32_t length = -1;
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span(uset, s, length, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_n
 * @since_tizen     2.3.1
 * @description     Returns the length of the initial substring of the input string which,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_n(void)
{
    const i18n_uchar s[] = { 'q', 'w', 'e', 'r', '\0' };
    int32_t length = -1;
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span(NULL, s, length, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_n2
 * @since_tizen     2.3.1
 * @description     Returns the length of the initial substring of the input string which,
 *                  passing invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_n2(void)
{
    int32_t length = -1;
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span(uset, NULL, length, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_n3
 * @since_tizen     2.3.1
 * @description     Returns the length of the initial substring of the input string which,
 *                  passing invalid string length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_n3(void)
{
    const i18n_uchar s[] = { 'q', 'w', 'e', 'r', '\0' };
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span(uset, s, -2, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_back_p
 * @since_tizen     2.3.1
 * @description     Returns the start of the trailing substring of the input string which,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_span_back_p(void)
{
    const i18n_uchar s[] = { 'q', 'w', 'e', 'r', '\0' };
    int32_t length = -1;
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span_back(uset, s, length, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_back_n
 * @since_tizen     2.3.1
 * @description     Returns the start of the trailing substring of the input string which,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_back_n(void)
{
    const i18n_uchar s[] = { 'q', 'w', 'e', 'r', '\0' };
    int32_t length = -1;
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span_back(NULL, s, length, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_back_n2
 * @since_tizen     2.3.1
 * @description     Returns the start of the trailing substring of the input string which,
 *                  passing invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_back_n2(void)
{
    int32_t length = -1;
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span_back(uset, NULL, length, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_back_n3
 * @since_tizen     2.3.1
 * @description     Returns the start of the trailing substring of the input string which,
 *                  passing invalid string length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_back_n3(void)
{
    const i18n_uchar s[] = { 'q', 'w', 'e', 'r', '\0' };
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span_back(uset, s, -2, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_back_n4
 * @since_tizen     2.3.1
 * @description     Returns the start of the trailing substring of the input string which,
 *                  passing invalid condition parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_back_n4(void)
{
    const i18n_uchar s[] = { 'q', 'w', 'e', 'r', '\0' };
    int32_t length = -1;

    i18n_uset_span_back(uset, s, length, -1);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_utf8_p
 * @since_tizen     2.3.1
 * @description     Returns the length of the initial substring of the input string which,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_span_utf8_p(void)
{
    const char *s = "qwer";
    int32_t length = -1;
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span_utf8(uset, s, length, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_utf8_n
 * @since_tizen     2.3.1
 * @description     Returns the length of the initial substring of the input string which,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_utf8_n(void)
{
    const char *s = "qwer";
    int32_t length = -1;
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span_utf8(NULL, s, length, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_utf8_n2
 * @since_tizen     2.3.1
 * @description     Returns the length of the initial substring of the input string which,
 *                  passing invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_utf8_n2(void)
{
    int32_t length = -1;
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span_utf8(uset, NULL, length, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_utf8_n3
 * @since_tizen     2.3.1
 * @description     Returns the length of the initial substring of the input string which,
 *                  passing invalid string length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_utf8_n3(void)
{
    const char *s = "qwer";
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span_utf8(uset, s, -2, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_utf8_n4
 * @since_tizen     2.3.1
 * @description     Returns the length of the initial substring of the input string which,
 *                  passing invalid condition parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_utf8_n4(void)
{
    const char *s = "qwer";
    int32_t length = -1;

    i18n_uset_span_utf8(uset, s, length, -1);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_back_utf8_p
 * @since_tizen     2.3.1
 * @description     Returns the start of the trailing substring of the input string which,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_span_back_utf8_p(void)
{
    const char *s = "qwer";
    int32_t length = -1;
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span_back_utf8(uset, s, length, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_back_utf8_n
 * @since_tizen     2.3.1
 * @description     Returns the start of the trailing substring of the input string which,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_back_utf8_n(void)
{
    const char *s = "qwer";
    int32_t length = -1;
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span_back_utf8(NULL, s, length, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_back_utf8_n2
 * @since_tizen     2.3.1
 * @description     Returns the start of the trailing substring of the input string which,
 *                  passing invalid string, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_back_utf8_n2(void)
{
    int32_t length = -1;
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span_back_utf8(uset, NULL, length, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_back_utf8_n3
 * @since_tizen     2.3.1
 * @description     Returns the start of the trailing substring of the input string which,
 *                  passing invalid string length, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_back_utf8_n3(void)
{
    const char *s = "qwer";
    i18n_uset_span_condition_e span_condition = I18N_USET_SPAN_NOT_CONTAINED;

    i18n_uset_span_back_utf8(uset, s, -2, span_condition);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_span_back_utf8_n4
 * @since_tizen     2.3.1
 * @description     Returns the start of the trailing substring of the input string which,
 *                  passing invalid condition parameter, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_span_back_utf8_n4(void)
{
    const char *s = "qwer";
    int32_t length = -1;

    i18n_uset_span_back_utf8(uset, s, length, -1);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_equals_p
 * @since_tizen     2.3.1
 * @description     Returns true if set1 contains all of the characters and string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_equals_p(void)
{
    i18n_uset_h uset2 = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset2);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_equals(uset, uset2);

    ret = get_last_result();
    i18n_uset_destroy(uset2);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_equals_n
 * @since_tizen     2.3.1
 * @description     Returns true if set1 contains all of the characters and string,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_equals_n(void)
{
    i18n_uset_h uset2 = NULL;
    i18n_uchar32 start = 0x51;
    i18n_uchar32 end = 0x60;

    ret = i18n_uset_create(start, end, &uset2);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_equals(NULL, uset2);

    ret = get_last_result();
    i18n_uset_destroy(uset2);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_equals_n2
 * @since_tizen     2.3.1
 * @description     Returns true if set1 contains all of the characters and string,
 *                  passing invalid uset, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_equals_n2(void)
{
    i18n_uset_equals(uset, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_serialize_p
 * @since_tizen     2.3.1
 * @description     Serializes this set into an array of 16-bit integers,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_serialize_p(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_uset_serialize(uset, dest, dest_capacity);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_serialize_n
 * @since_tizen     2.3.1
 * @description     Serializes this set into an array of 16-bit integers,
 *                  passing invalid uset handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_serialize_n(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_uset_serialize(NULL, dest, dest_capacity);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_serialize_n2
 * @since_tizen     2.3.1
 * @description     Serializes this set into an array of 16-bit integers,
 *                  passing invalid destination, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_serialize_n2(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_uset_serialize(uset, NULL, dest_capacity);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_serialize_n3
 * @since_tizen     2.3.1
 * @description     Serializes this set into an array of 16-bit integers,
 *                  passing invalid destination buffer capacity, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_serialize_n3(void)
{
    uint16_t dest[48] = { 0, };

    i18n_uset_serialize(uset, dest, -1);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_serialized_set_p
 * @since_tizen     2.3.1
 * @description     Serialzes array, the gets serialized set,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_get_serialized_set_p(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_uset_serialize(uset, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_userialized_set_s fill_set;

    i18n_uset_get_serialized_set(dest, dest_capacity, &fill_set);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_serialized_set_n
 * @since_tizen     2.3.1
 * @description     Serialzes array, the gets serialized set,
 *                  passing invalid pointer to the array, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_serialized_set_n(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_userialized_set_s fill_set;

    i18n_uset_get_serialized_set(NULL, dest_capacity, &fill_set);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_serialized_set_n2
 * @since_tizen     2.3.1
 * @description     Serialzes array, the gets serialized set,
 *                  passing invalid length of array, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_serialized_set_n2(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_uset_serialize(uset, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_userialized_set_s fill_set;

    i18n_uset_get_serialized_set(dest, -1, &fill_set);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_serialized_set_n3
 * @since_tizen     2.3.1
 * @description     Serialzes array, the gets serialized set,
 *                  passing invalid output set handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_serialized_set_n3(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_uset_serialize(uset, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_get_serialized_set(dest, dest_capacity, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_set_serialized_to_one_p
 * @since_tizen     2.3.1
 * @description     Sets the serialized set structure to contain the given character (and nothing else),
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_set_serialized_to_one_p(void)
{
    i18n_uchar32 c = 0x41;
    i18n_userialized_set_s fill_set;

    ret = i18n_uset_set_serialized_to_one(c, &fill_set);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_set_serialized_to_one_n
 * @since_tizen     2.3.1
 * @description     Sets the serialized set structure to contain the given character (and nothing else),
 *                  passing invalid output set pointer, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_set_serialized_to_one_n(void)
{
    i18n_uchar32 c = 0x41;

    ret = i18n_uset_set_serialized_to_one(c, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_serialized_contains_p
 * @since_tizen     2.3.1
 * @description     Returns @c true if the given serialized set structure contains the given character,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_serialized_contains_p(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_uset_serialize(uset, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_userialized_set_s fill_set;

    i18n_uset_get_serialized_set(dest, dest_capacity, &fill_set);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar32 c = 0x41;

    i18n_uset_serialized_contains(&fill_set, c);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_serialized_contains_n
 * @since_tizen     2.3.1
 * @description     Returns @c true if the given serialized set structure contains the given character,
 *                  passing invalid serialized set handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_serialized_contains_n(void)
{
    i18n_uchar32 c = 0x41;

    i18n_uset_serialized_contains(NULL, c);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_serialized_range_count_p
 * @since_tizen     2.3.1
 * @description     Returns the number of disjoint ranges of characters contained if,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_get_serialized_range_count_p(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_uset_serialize(uset, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_userialized_set_s fill_set;

    i18n_uset_get_serialized_set(dest, dest_capacity, &fill_set);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uset_get_serialized_range_count(&fill_set);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_serialized_range_count_n
 * @since_tizen     2.3.1
 * @description     Returns the number of disjoint ranges of characters contained if,
 *                  passing invalid serialized set handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_serialized_range_count_n(void)
{
    i18n_uset_get_serialized_range_count(NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_serialized_range_p
 * @since_tizen     2.3.1
 * @description     Returns a range of characters contained in the given serialized set,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_uset_get_serialized_range_p(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_uset_serialize(uset, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_userialized_set_s fill_set;

    i18n_uset_get_serialized_set(dest, dest_capacity, &fill_set);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t range_index = 0;
    i18n_uchar32 p_start = 0;
    i18n_uchar32 p_end = 0;

    i18n_uset_get_serialized_range(&fill_set, range_index, &p_start, &p_end);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_serialized_range_n
 * @since_tizen     2.3.1
 * @description     Returns a range of characters contained in the given serialized set,
 *                  passing invalid serialized set handle, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_serialized_range_n(void)
{
    int32_t range_index = 0;
    i18n_uchar32 p_start = 0;
    i18n_uchar32 p_end = 0;

    i18n_uset_get_serialized_range(NULL, range_index, &p_start, &p_end);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_serialized_range_n2
 * @since_tizen     2.3.1
 * @description     Returns a range of characters contained in the given serialized set,
 *                  passing invalid range index, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_serialized_range_n2(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_uset_serialize(uset, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_userialized_set_s fill_set;

    i18n_uset_get_serialized_set(dest, dest_capacity, &fill_set);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_uchar32 p_start = 0;
    i18n_uchar32 p_end = 0;

    i18n_uset_get_serialized_range(&fill_set, -1, &p_start, &p_end);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_serialized_range_n3
 * @since_tizen     2.3.1
 * @description     Returns a range of characters contained in the given serialized set,
 *                  passing invalid pointer to get first character, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_serialized_range_n3(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_uset_serialize(uset, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_userialized_set_s fill_set;

    i18n_uset_get_serialized_set(dest, dest_capacity, &fill_set);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t range_index = 0;
    i18n_uchar32 p_end = 0;

    i18n_uset_get_serialized_range(&fill_set, range_index, NULL, &p_end);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_uset_get_serialized_range_n4
 * @since_tizen     2.3.1
 * @description     Returns a range of characters contained in the given serialized set,
 *                  passing invalid pointer to get end character, so error is expected.
 */
int utc_capi_base_utils_i18n_uset_get_serialized_range_n4(void)
{
    uint16_t dest[48] = { 0, };
    int32_t dest_capacity = sizeof(dest) / sizeof(dest[0]);

    i18n_uset_serialize(uset, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_userialized_set_s fill_set;

    i18n_uset_get_serialized_set(dest, dest_capacity, &fill_set);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    int32_t range_index = 0;
    i18n_uchar32 p_start = 0;

    i18n_uset_get_serialized_range(&fill_set, range_index, &p_start, NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}
