#include "assert.h"
#include <string.h>
#include <utils_i18n.h>

static i18n_udatepg_h dtpg = NULL;
static int ret = I18N_ERROR_NONE;

#define I18N_ret_LEN         100
#define SKELETON_LEN            6
#define BEST_PATTERN_CAPACITY   12

/**
 * @function        utc_capi_base_utils_udatepg_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_udatepg_startup(void)
{
    ret = i18n_udatepg_create(I18N_ULOCALE_US, &dtpg);
}

/**
 * @function        utc_capi_base_utils_udatepg_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_udatepg_cleanup(void)
{
    i18n_udatepg_destroy(dtpg);
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_create_p
 * @since_tizen     2.3
 * @description     Creates a generator according to a given locale.
 */
int utc_capi_base_utils_i18n_udatepg_create_p(void)
{
    assert_neq(dtpg, NULL);
    assert_eq(ret, I18N_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_create_n
 * @since_tizen     2.3
 * @description     Creates a generator according to a given locale passing NULL
 *                  to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_create_n(void)
{
    ret = i18n_udatepg_create(I18N_ULOCALE_US, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_destroy_p
 * @since_tizen     2.3
 * @description     Destroys a generator.
 */
int utc_capi_base_utils_i18n_udatepg_destroy_p(void)
{
    i18n_udatepg_h dtpg = NULL;
    i18n_udatepg_create(I18N_ULOCALE_US, &dtpg);
    assert_neq(dtpg, NULL);
    ret = i18n_udatepg_destroy(dtpg);
    assert_eq(ret, I18N_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_destroy_n
 * @since_tizen     2.3
 * @description     Destroys a generator passing NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_destroy_n(void)
{
    ret = i18n_udatepg_destroy(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_best_pattern_p
 * @since_tizen     2.3
 * @description     Gets the best pattern matching the input skeleton.
 */
int utc_capi_base_utils_i18n_udatepg_get_best_pattern_p(void)
{
    assert_neq(dtpg, NULL);
    const char *a_skeleton = "MMMdd";
    i18n_uchar skeleton[SKELETON_LEN] = { 0, };
    i18n_uchar best_pattern[I18N_ret_LEN] = { 0, };
    int skeleton_len;
    int best_pattern_len;
    int capacity;

    i18n_ustring_copy_ua(skeleton, a_skeleton);
    skeleton_len = i18n_ustring_get_length(skeleton);
    capacity = (int)(sizeof(best_pattern)/sizeof(best_pattern[0]));

    ret = i18n_udatepg_get_best_pattern(dtpg, skeleton, skeleton_len, best_pattern,
        capacity, &best_pattern_len);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_best_pattern_n
 * @since_tizen     2.3
 * @description     Gets the best pattern matching the input skeleton passing
 *                  NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_best_pattern_n(void)
{
    i18n_uchar *skeleton = NULL;
    i18n_uchar *best_pattern = NULL;
    int best_pattern_len = -1;

    ret = i18n_udatepg_get_best_pattern(NULL, skeleton, SKELETON_LEN, best_pattern,
        BEST_PATTERN_CAPACITY, &best_pattern_len);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_create_empty_p
 * @since_tizen     2.3.1
 * @description     Creates an empty generator, to be constructed with
 *                  i18n_udatepg_add_pattern() etc.
 */
int utc_capi_base_utils_i18n_udatepg_create_empty_p(void)
{
    i18n_udatepg_destroy(dtpg);

    ret = i18n_udatepg_create_empty(&dtpg);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_create_empty_n
 * @since_tizen     2.3.1
 * @description     Creates an empty generator, to be constructed with
 *                  i18n_udatepg_add_pattern() etc, passing NULL to dtpg
 *                  parameter.
 */
int utc_capi_base_utils_i18n_udatepg_create_empty_n(void)
{
    ret = i18n_udatepg_create_empty(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_clone_p
 * @since_tizen     2.3.1
 * @description     Creates a copy of a generator.
 */
int utc_capi_base_utils_i18n_udatepg_clone_p(void)
{
    i18n_udatepg_h dtpg_clone = NULL;

    ret = i18n_udatepg_clone(dtpg, &dtpg_clone);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(dtpg_clone, NULL);
    i18n_udatepg_destroy(dtpg_clone);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_clone_n
 * @since_tizen     2.3.1
 * @description     Creates a copy of a generator passing NULL to dtpg and
 *                  dtpg_clone parameters.
 */
int utc_capi_base_utils_i18n_udatepg_clone_n(void)
{
    i18n_udatepg_h dtpg_c = NULL;

    ret = i18n_udatepg_clone(NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(dtpg_c, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_best_pattern_with_options_p
 * @since_tizen     2.3.1
 * @description     Gets the best pattern matching the input skeleton.
 */
int utc_capi_base_utils_i18n_udatepg_get_best_pattern_with_options_p(void)
{
    const char *skeleton = "yyyyMMMdd";
    i18n_uchar buffer[24] = {0,};
    int length = strlen(skeleton);
    i18n_udatepg_date_time_pattern_match_options_e options = I18N_UDATEPG_MATCH_NO_OPTIONS;
    i18n_uchar best_pattern[24] = {0,};
    int capacity = sizeof(best_pattern)/sizeof(best_pattern[0]);

    i18n_udatepg_get_best_pattern_with_options(dtpg, i18n_ustring_copy_ua(buffer, skeleton),
        length, options, best_pattern, capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_udatepg_get_best_pattern_with_options_n
 * @since_tizen     2.3.1
 * @description     Gets the best pattern matching the input skeleton passing
 *                  NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_best_pattern_with_options_n(void)
{
    const char *skeleton = "yyyyMMMdd";
    i18n_uchar buffer[24] = {0,};
    int length = strlen(skeleton);
    i18n_udatepg_date_time_pattern_match_options_e options = I18N_UDATEPG_MATCH_NO_OPTIONS;
    i18n_uchar best_pattern[24] = {0,};
    int capacity = sizeof(best_pattern)/sizeof(best_pattern[0]);

    i18n_udatepg_get_best_pattern_with_options(NULL, i18n_ustring_copy_ua(buffer, skeleton),
        length, options, best_pattern, capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_best_pattern_with_options_n2
 * @since_tizen     2.3.1
 * @description     Gets the best pattern matching the input skeleton passing
 *                  NULL to skeleton parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_best_pattern_with_options_n2(void)
{
    int length = 1;
    i18n_udatepg_date_time_pattern_match_options_e options = I18N_UDATEPG_MATCH_NO_OPTIONS;
    i18n_uchar best_pattern[24] = {0,};
    int capacity = sizeof(best_pattern)/sizeof(best_pattern[0]);

    i18n_udatepg_get_best_pattern_with_options(dtpg, NULL, length, options, best_pattern, capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_udatepg_get_best_pattern_with_options_n3
 * @since_tizen     2.3.1
 * @description     Gets the best pattern matching the input skeleton passing
 *                  invalid length parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_best_pattern_with_options_n3(void)
{
    const char *skeleton = "yyyyMMMdd";
    i18n_uchar buffer[24] = {0,};
    i18n_udatepg_date_time_pattern_match_options_e options = I18N_UDATEPG_MATCH_NO_OPTIONS;
    i18n_uchar best_pattern[24] = {0,};
    int capacity = sizeof(best_pattern)/sizeof(best_pattern[0]);

    i18n_udatepg_get_best_pattern_with_options(dtpg, i18n_ustring_copy_ua(buffer, skeleton),
        -2, options, best_pattern, capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_best_pattern_with_options_n4
 * @since_tizen     2.3.1
 * @description     Gets the best pattern matching the input skeleton passing
 *                  NULL to best_pattern parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_best_pattern_with_options_n4(void)
{
    const char *skeleton = "yyyyMMMdd";
    i18n_uchar buffer[24] = {0,};
    int length = strlen(skeleton);
    i18n_udatepg_date_time_pattern_match_options_e options = I18N_UDATEPG_MATCH_NO_OPTIONS;
    i18n_uchar best_pattern[24] = {0,};
    int capacity = sizeof(best_pattern)/sizeof(best_pattern[0]);

    i18n_udatepg_get_best_pattern_with_options(dtpg, i18n_ustring_copy_ua(buffer, skeleton),
        length, options, NULL, capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_best_pattern_with_options_n5
 * @since_tizen     2.3.1
 * @description     Gets the best pattern matching the input skeleton passing
 *                  invalid capacity parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_best_pattern_with_options_n5(void)
{
    const char *skeleton = "yyyyMMMdd";
    i18n_uchar buffer[24] = {0,};
    int length = strlen(skeleton);
    i18n_udatepg_date_time_pattern_match_options_e options = I18N_UDATEPG_MATCH_NO_OPTIONS;
    i18n_uchar best_pattern[24] = {0,};

    i18n_udatepg_get_best_pattern_with_options(dtpg, i18n_ustring_copy_ua(buffer, skeleton),
        length, options, best_pattern, -2);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_skeleton_p
 * @since_tizen     2.3.1
 * @description     Gets a unique skeleton from a given pattern.
 */
int utc_capi_base_utils_i18n_udatepg_get_skeleton_p(void)
{
    const char *skeleton = "yyyyMMMdd";
    i18n_uchar buffer[24] = {0,};
    int capacity_buffer = sizeof(buffer)/sizeof(buffer[0]);
    int length = strlen(skeleton);
    i18n_uchar best_pattern[24] = {0,};
    int capacity_best_pattern = sizeof(best_pattern)/sizeof(best_pattern[0]);
    int32_t best_pattern_len = -1;

    ret = i18n_udatepg_get_best_pattern(dtpg, i18n_ustring_copy_ua(buffer, skeleton), length, best_pattern, capacity_best_pattern, &best_pattern_len);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udatepg_get_skeleton(dtpg, best_pattern, i18n_ustring_get_length(best_pattern), buffer, capacity_buffer);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_skeleton_n
 * @since_tizen     2.3.1
 * @description     Gets a unique skeleton from a given pattern passing NULL to
 *                  pattern parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_skeleton_n(void)
{
    i18n_uchar buffer[24] = {0,};
    int capacity_buffer = sizeof(buffer)/sizeof(buffer[0]);
    int length = 1;

    i18n_udatepg_get_skeleton(dtpg, NULL, length, buffer, capacity_buffer);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_base_skeleton_p
 * @since_tizen     2.3.1
 * @description     Gets a unique base skeleton from a given pattern.
 */
int utc_capi_base_utils_i18n_udatepg_get_base_skeleton_p(void)
{
    const char *skeleton = "yyyyMMMdd";
    i18n_uchar buffer[24] = {0,};
    int capacity_buffer = sizeof(buffer)/sizeof(buffer[0]);
    int length = strlen(skeleton);
    i18n_uchar best_pattern[24] = {0,};
    int capacity_best_pattern = sizeof(best_pattern)/sizeof(best_pattern[0]);
    int32_t best_pattern_len = -1;

    i18n_udatepg_get_best_pattern(dtpg, i18n_ustring_copy_ua(buffer, skeleton), length, best_pattern, capacity_best_pattern, &best_pattern_len);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udatepg_get_base_skeleton(dtpg, best_pattern, i18n_ustring_get_length(best_pattern), buffer, capacity_buffer);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_base_skeleton_n
 * @since_tizen     2.3.1
 * @description     Gets a unique base skeleton from a given pattern passing
 *                  NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_base_skeleton_n(void)
{
    const char *skeleton = "yyyyMMMdd";
    i18n_uchar buffer[24] = {0,};
    int capacity_buffer = sizeof(buffer)/sizeof(buffer[0]);
    int length = strlen(skeleton);
    i18n_uchar best_pattern[24] = {0,};
    int capacity_best_pattern = sizeof(best_pattern)/sizeof(best_pattern[0]);
    int32_t best_pattern_len = -1;

    i18n_udatepg_get_best_pattern(dtpg, i18n_ustring_copy_ua(buffer, skeleton), length, best_pattern, capacity_best_pattern, &best_pattern_len);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udatepg_get_base_skeleton(NULL, best_pattern, i18n_ustring_get_length(best_pattern), buffer, capacity_buffer);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_base_skeleton_n2
 * @since_tizen     2.3.1
 * @description     Gets a unique base skeleton from a given pattern passing
 *                  NULL to pattern parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_base_skeleton_n2(void)
{
    i18n_uchar buffer[24] = {0,};
    int capacity_buffer = sizeof(buffer)/sizeof(buffer[0]);
    int length = 1;

    i18n_udatepg_get_base_skeleton(dtpg, NULL, length, buffer, capacity_buffer);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_base_skeleton_n3
 * @since_tizen     2.3.1
 * @description     Gets a unique base skeleton from a given pattern passing
 *                  invalid length parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_base_skeleton_n3(void)
{
    const char *skeleton = "yyyyMMMdd";
    i18n_uchar buffer[24] = {0,};
    int capacity_buffer = sizeof(buffer)/sizeof(buffer[0]);
    int length = strlen(skeleton);
    i18n_uchar best_pattern[24] = {0,};
    int capacity_best_pattern = sizeof(best_pattern)/sizeof(best_pattern[0]);
    int32_t best_pattern_len = -1;

    i18n_udatepg_get_best_pattern(dtpg, i18n_ustring_copy_ua(buffer, skeleton), length, best_pattern, capacity_best_pattern, &best_pattern_len);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udatepg_get_base_skeleton(dtpg, best_pattern, -2, buffer, capacity_buffer);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_base_skeleton_n4
 * @since_tizen     2.3.1
 * @description     Gets a unique base skeleton from a given pattern passing
 *                  NULL to base_skeleton parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_base_skeleton_n4(void)
{
    const char *skeleton = "yyyyMMMdd";
    i18n_uchar buffer[24] = {0,};
    int capacity_buffer = sizeof(buffer)/sizeof(buffer[0]);
    int length = strlen(skeleton);
    i18n_uchar best_pattern[24] = {0,};
    int capacity_best_pattern = sizeof(best_pattern)/sizeof(best_pattern[0]);
    int32_t best_pattern_len = -1;

    i18n_udatepg_get_best_pattern(dtpg, i18n_ustring_copy_ua(buffer, skeleton), length, best_pattern, capacity_best_pattern, &best_pattern_len);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udatepg_get_base_skeleton(dtpg, best_pattern, i18n_ustring_get_length(best_pattern), NULL, capacity_buffer);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_base_skeleton_n5
 * @since_tizen     2.3.1
 * @description     Gets a unique base skeleton from a given pattern passing
 *                  invalid capacity parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_base_skeleton_n5(void)
{
    const char *skeleton = "yyyyMMMdd";
    i18n_uchar buffer[24] = {0,};
    int length = strlen(skeleton);
    i18n_uchar best_pattern[24] = {0,};
    int capacity_best_pattern = sizeof(best_pattern)/sizeof(best_pattern[0]);
    int32_t best_pattern_len = -1;

    i18n_udatepg_get_best_pattern(dtpg, i18n_ustring_copy_ua(buffer, skeleton), length, best_pattern, capacity_best_pattern, &best_pattern_len);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_udatepg_get_base_skeleton(dtpg, best_pattern, i18n_ustring_get_length(best_pattern), buffer, -2);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_add_pattern_p
 * @since_tizen     2.3.1
 * @description     Adds a pattern to the generator.
 */
int utc_capi_base_utils_i18n_udatepg_add_pattern_p(void)
{
    const char* src = "yyyy/MM/dd";
    i18n_uchar pattern[24] = {0,};
    int32_t pattern_length = strlen(src);
    i18n_ubool override = false;
    i18n_uchar conflicting_pattern[24] = {0,};
    int32_t capacity = sizeof(conflicting_pattern)/sizeof(conflicting_pattern[0]);
    i18n_udatepg_date_time_pattern_conflict_e conflict_status;

    i18n_udatepg_add_pattern(dtpg, i18n_ustring_copy_ua(pattern, src), pattern_length, override, conflicting_pattern, capacity, &conflict_status);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_add_pattern_n
 * @since_tizen     2.3.1
 * @description     Adds a pattern to the generator passing NULL to pattern
 *                  parameter.
 */
int utc_capi_base_utils_i18n_udatepg_add_pattern_n(void)
{
    int32_t pattern_length = 1;
    i18n_ubool override = false;
    i18n_uchar conflicting_pattern[24] = {0,};
    int32_t capacity = sizeof(conflicting_pattern)/sizeof(conflicting_pattern[0]);
    int32_t confliction_pattern_length = 0;

    confliction_pattern_length = i18n_udatepg_add_pattern(dtpg, NULL, pattern_length, override, conflicting_pattern, capacity, NULL);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(confliction_pattern_length, -1);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_set_append_item_format_p
 * @since_tizen     2.3.1
 * @description     Sets append_item_format - pattern used to append a field if
 *                  there is no good match.
 */
int utc_capi_base_utils_i18n_udatepg_set_append_item_format_p(void)
{
    i18n_udatepg_date_time_pattern_field_e field = I18N_UDATEPG_ERA_FIELD;
    const char *src = "{1}{2}{0}";
    i18n_uchar value[24] = {0,};
    int32_t length = strlen(src);

    ret = i18n_udatepg_set_append_item_format(dtpg, field, i18n_ustring_copy_ua(value, src), length);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_set_append_item_format_n
 * @since_tizen     2.3.1
 * @description     Sets append_item_format passing NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_set_append_item_format_n(void)
{
    i18n_udatepg_date_time_pattern_field_e field = I18N_UDATEPG_ERA_FIELD;
    const char *src = "{1}{2}{0}";
    i18n_uchar value[24] = {0,};
    int32_t length = strlen(src);

    ret = i18n_udatepg_set_append_item_format(NULL, field, i18n_ustring_copy_ua(value, src), length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_append_item_format_p
 * @since_tizen     2.3.1
 * @description     Gets append_item_format.
 */
int utc_capi_base_utils_i18n_udatepg_get_append_item_format_p(void)
{
    i18n_udatepg_date_time_pattern_field_e field = I18N_UDATEPG_ERA_FIELD;
    int32_t pattern_length;

    const i18n_uchar *format = i18n_udatepg_get_append_item_format(dtpg, field, &pattern_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(format, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_append_item_format_n
 * @since_tizen     2.3.1
 * @description     Gets append_item_format passing NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_append_item_format_n(void)
{
    i18n_udatepg_date_time_pattern_field_e field = I18N_UDATEPG_ERA_FIELD;

    int32_t pattern_length = 0;

    i18n_udatepg_get_append_item_format(NULL, field, &pattern_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_set_append_item_name_p
 * @since_tizen     2.3.1
 * @description     Sets the name of field.
 */
int utc_capi_base_utils_i18n_udatepg_set_append_item_name_p(void)
{
    i18n_udatepg_date_time_pattern_field_e field = I18N_UDATEPG_ERA_FIELD;
    const char *src = "tizen";
    i18n_uchar value[24] = {0,};
    int32_t length = strlen(src);

    ret = i18n_udatepg_set_append_item_name(dtpg, field, value, length);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_set_append_item_name_n
 * @since_tizen     2.3.1
 * @description     Sets the name of field passing NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_set_append_item_name_n(void)
{
    i18n_udatepg_date_time_pattern_field_e field = I18N_UDATEPG_ERA_FIELD;
    i18n_uchar value[24] = {0,};
    int32_t length = -1;

    ret = i18n_udatepg_set_append_item_name(NULL, field, value, length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_append_item_name_p
 * @since_tizen     2.3.1
 * @description     Gets the name of field.
 */
int utc_capi_base_utils_i18n_udatepg_get_append_item_name_p(void)
{
    i18n_udatepg_date_time_pattern_field_e field = I18N_UDATEPG_ERA_FIELD;
    const i18n_uchar *value;
    int32_t length;

    value = i18n_udatepg_get_append_item_name(dtpg, field, &length);
    ret = get_last_result();
    assert_neq(value, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_append_item_name_n
 * @since_tizen     2.3.1
 * @description     Gets the name of field passing NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_append_item_name_n(void)
{
    i18n_udatepg_date_time_pattern_field_e field = I18N_UDATEPG_ERA_FIELD;

    int32_t pattern_length = 0;

    i18n_udatepg_get_append_item_name(NULL, field, &pattern_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_set_date_time_format_p
 * @since_tizen     2.3.1
 * @description     Sets date time format.
 */
int utc_capi_base_utils_i18n_udatepg_set_date_time_format_p(void)
{
    const char *src = "{1} {0}";
    i18n_uchar date_time_format[16] = {0,};
    int32_t length = strlen(src);

    ret = i18n_udatepg_set_date_time_format(dtpg, i18n_ustring_copy_ua(date_time_format, src), length);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_set_date_time_format_n
 * @since_tizen     2.3.1
 * @description     Sets date time format passing NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_set_date_time_format_n(void)
{
    const char *src = "{1} {0}";
    i18n_uchar date_time_format[16] = {0,};
    int32_t length = strlen(src);

    ret = i18n_udatepg_set_date_time_format(NULL, i18n_ustring_copy_ua(date_time_format, src), length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_date_time_format_p
 * @since_tizen     2.3.1
 * @description     Gets date time format.
 */
int utc_capi_base_utils_i18n_udatepg_get_date_time_format_p(void)
{
    int32_t pattern_length = 0;

    i18n_udatepg_get_date_time_format(dtpg, &pattern_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_date_time_format_n
 * @since_tizen     2.3.1
 * @description     Gets date time format passing NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_date_time_format_n(void)
{
    int32_t pattern_length = 0;

    i18n_udatepg_get_date_time_format(NULL, &pattern_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_set_decimal_p
 * @since_tizen     2.3.1
 * @description     Sets the decimal.
 */
int utc_capi_base_utils_i18n_udatepg_set_decimal_p(void)
{
    const char *src = ",";
    i18n_uchar decimal;
    int32_t length = strlen(src);

    ret = i18n_udatepg_set_decimal(dtpg, i18n_ustring_copy_ua(&decimal, src), length);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_set_decimal_n
 * @since_tizen     2.3.1
 * @description     Sets the decimal passing NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_set_decimal_n(void)
{
    const char *src = ",";
    i18n_uchar *decimal = NULL;
    int32_t length = strlen(src);

    ret = i18n_udatepg_set_decimal(NULL, i18n_ustring_copy_ua(decimal, src), length);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_decimal_p
 * @since_tizen     2.3.1
 * @description     Gets the decimal.
 */
int utc_capi_base_utils_i18n_udatepg_get_decimal_p(void)
{
    int32_t pttern_length = 0;

    i18n_udatepg_get_decimal(dtpg, &pttern_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_decimal_n
 * @since_tizen     2.3.1
 * @description     Gets the decimal passing NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_decimal_n(void)
{
    int32_t pttern_length = 0;

    i18n_udatepg_get_decimal(NULL, &pttern_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_replace_field_types_p
 * @since_tizen     2.3.1
 * @description     Adjusts the field types (width and subtype) of a pattern to
 *                  match what is in a skeleton.
 */
int utc_capi_base_utils_i18n_udatepg_replace_field_types_p(void)
{
    const char *src_for_pattern = "d-M H:m";
    i18n_uchar pattern[32] = {0,};
    int32_t pattern_length = strlen(src_for_pattern);
    const char *src_for_skeleton = "MMMMddhhmm";
    i18n_uchar skeleton[32] = {0,};
    int32_t skeleton_length = strlen(src_for_skeleton);
    i18n_uchar dest[32] = {0,};
    int32_t dest_capacity = sizeof(dest)/sizeof(dest[0]);

    i18n_udatepg_replace_field_types(dtpg, pattern, pattern_length, skeleton, skeleton_length, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_replace_field_types_n
 * @since_tizen     2.3.1
 * @description     Adjusts the field types (width and subtype) of a pattern to
 *                  match what is in a skeleton passing NULL to pattern
 *                  parameter.
 */
int utc_capi_base_utils_i18n_udatepg_replace_field_types_n(void)
{
    int32_t pattern_length = 1;
    const char *src_for_skeleton = "MMMMddhhmm";
    i18n_uchar skeleton[32] = {0,};
    int32_t skeleton_length = strlen(src_for_skeleton);
    i18n_uchar dest[32] = {0,};
    int32_t dest_capacity = sizeof(dest)/sizeof(dest[0]);

    i18n_udatepg_replace_field_types(dtpg, NULL, pattern_length, skeleton, skeleton_length, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_udatepg_replace_field_types_with_options_p
 * @since_tizen     2.3.1
 * @description     Adjusts the field types (width and subtype) of a pattern to
 *                  match what is in a skeleton.
 */
int utc_capi_base_utils_i18n_udatepg_replace_field_types_with_options_p(void)
{
    const char *src_for_pattern = "d-M H:m";
    i18n_uchar pattern[32] = {0,};
    int32_t pattern_length = strlen(src_for_pattern);
    const char *src_for_skeleton = "MMMMddhhmm";
    i18n_uchar skeleton[32] = {0,};
    int32_t skeleton_length = strlen(src_for_skeleton);
    i18n_udatepg_date_time_pattern_match_options_e options = I18N_UDATEPG_MATCH_NO_OPTIONS;
    i18n_uchar dest[32] = {0,};
    int32_t dest_capacity = sizeof(dest)/sizeof(dest[0]);

    i18n_udatepg_replace_field_types_with_options(dtpg, pattern, pattern_length, skeleton, skeleton_length, options, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_udatepg_replace_field_types_with_options_n
 * @since_tizen     2.3.1
 * @description     Adjusts the field types (width and subtype) of a pattern to
 *                  match what is in a skeleton passing NULL to pattern parameter.
 */
int utc_capi_base_utils_i18n_udatepg_replace_field_types_with_options_n(void)
{
    int32_t pattern_length = 1;
    const char *src_for_skeleton = "MMMMddhhmm";
    i18n_uchar skeleton[32] = {0,};
    int32_t skeleton_length = strlen(src_for_skeleton);
    i18n_udatepg_date_time_pattern_match_options_e options = I18N_UDATEPG_MATCH_NO_OPTIONS;
    i18n_uchar dest[32] = {0,};
    int32_t dest_capacity = sizeof(dest)/sizeof(dest[0]);

    i18n_udatepg_replace_field_types_with_options(dtpg, NULL, pattern_length, skeleton, skeleton_length, options, dest, dest_capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_skeletons_create_p
 * @since_tizen     2.3.1
 * @description     Creates an i18n_uenumeration_h for list of all the skeletons
 *                  in canonical form.
 */
int utc_capi_base_utils_i18n_udatepg_skeletons_create_p(void)
{
    i18n_uenumeration_h enumeration = NULL;
    ret = i18n_udatepg_skeletons_create(dtpg, &enumeration);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_skeletons_create_n
 * @since_tizen     2.3.1
 * @description     Creates an i18n_uenumeration_h for list of all the skeletons
 *                  in canonical form passing NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_skeletons_create_n(void)
{
    i18n_uenumeration_h enumeration;

    ret = i18n_udatepg_skeletons_create(NULL, &enumeration);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_skeletons_create_n2
 * @since_tizen     2.3.1
 * @description     Creates an i18n_uenumeration_h for list of all the skeletons
 *                  in canonical form passing NULL to enumeration parameter.
 */
int utc_capi_base_utils_i18n_udatepg_skeletons_create_n2(void)
{
    ret = i18n_udatepg_skeletons_create(dtpg, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_base_skeletons_create_p
 * @since_tizen     2.3.1
 * @description     Creates an #i18n_uenumeration_h for list of all the base
 *                  skeletons in canonical form.
 */
int utc_capi_base_utils_i18n_udatepg_base_skeletons_create_p(void)
{
    i18n_uenumeration_h enumeration = NULL;
    ret = i18n_udatepg_base_skeletons_create(dtpg, &enumeration);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_base_skeletons_create_n
 * @since_tizen     2.3.1
 * @description     Creates an i18n_uenumeration_h for list of all the base
 *                  skeletons in canonical form passing NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_base_skeletons_create_n(void)
{
    i18n_uenumeration_h enumeration;

    ret = i18n_udatepg_base_skeletons_create(NULL, &enumeration);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_base_skeletons_create_n2
 * @since_tizen     2.3.1
 * @description     Creates an i18n_uenumeration_h for list of all the base
 *                  skeletons in canonical form passing NULL to enumeration
 *                  parameter.
 */
int utc_capi_base_utils_i18n_udatepg_base_skeletons_create_n2(void)
{
    ret = i18n_udatepg_base_skeletons_create(dtpg, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_pattern_for_skeleton_p
 * @since_tizen     2.3.1
 * @description     Gets the pattern corresponding to a given skeleton.
 */
int utc_capi_base_utils_i18n_udatepg_get_pattern_for_skeleton_p(void)
{
    const char *src = "yMd";
    i18n_uchar skeleton[8] = {0,};
    int32_t skeleton_length = strlen(src);
    int32_t pattern_length = 0;

    i18n_udatepg_get_pattern_for_skeleton(dtpg, i18n_ustring_copy_ua(skeleton, src), skeleton_length, &pattern_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_pattern_for_skeleton_n
 * @since_tizen     2.3.1
 * @description     Gets the pattern corresponding to a given skeleton passing
 *                  NULL to dtpg parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_pattern_for_skeleton_n(void)
{
    const char *src = "yMd";
    i18n_uchar skeleton[8] = {0,};
    int32_t skeleton_length = strlen(src);
    int32_t pattern_length = 0;

    i18n_udatepg_get_pattern_for_skeleton(NULL, i18n_ustring_copy_ua(skeleton, src), skeleton_length, &pattern_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_pattern_for_skeleton_n2
 * @since_tizen     2.3.1
 * @description     Gets the pattern corresponding to a given skeleton passing
 *                  NULL to skeleton parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_pattern_for_skeleton_n2(void)
{
    const char *src = "yMd";
    int32_t skeleton_length = strlen(src);
    int32_t pattern_length = 0;

    i18n_udatepg_get_pattern_for_skeleton(dtpg, NULL, skeleton_length, &pattern_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_udatepg_get_pattern_for_skeleton_n3
 * @since_tizen     2.3.1
 * @description     Gets the pattern corresponding to a given skeleton passing
 *                  invalid skeleton_length parameter.
 */
int utc_capi_base_utils_i18n_udatepg_get_pattern_for_skeleton_n3(void)
{
    const char *src = "yMd";
    i18n_uchar skeleton[8] = {0,};
    int32_t pattern_length = 0;

    i18n_udatepg_get_pattern_for_skeleton(dtpg, i18n_ustring_copy_ua(skeleton, src), -2, &pattern_length);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
