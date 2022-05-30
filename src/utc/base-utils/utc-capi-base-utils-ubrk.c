#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

#define STR_LEN 64

static i18n_error_code_e ret = I18N_ERROR_NONE;
static i18n_ubreak_iterator_h ubrk = NULL;
static i18n_uchar *_text = NULL;
static const char *locale = I18N_ULOCALE_US;
static const char *text = "text to be iterated";

/**
 * @function        utc_capi_base_utils_ubrk_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ubrk_startup(void)
{
    _text = (i18n_uchar*)calloc(strlen(text) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_text, text);

    ret = i18n_ubrk_create(I18N_UBRK_WORD, locale, _text, -1, &ubrk);
}

/**
 * @function        utc_capi_base_utils_ubrk_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_ubrk_cleanup(void)
{
    if(NULL != ubrk) {
        i18n_ubrk_destroy(ubrk);
        ubrk = NULL;
    }

    free(_text);
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_create_p
 * @since_tizen     2.3.1
 * @description     Creates i18n_ubreak_iterator_h
 * @scenario        Creates the handle and checks whether it has been created
 */
int utc_capi_base_utils_i18n_ubrk_create_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_create_p2
 * @since_tizen     2.3.1
 * @description     Creates i18n_ubreak_iterator_h
 * @scenario        Creates the handle for character type
 *                  and checks whether it has been created
 */
int utc_capi_base_utils_i18n_ubrk_create_p2(void)
{
    if(NULL != ubrk) {
        i18n_ubrk_destroy(ubrk);
        ubrk = NULL;
    }

    ret = i18n_ubrk_create(I18N_UBRK_CHARACTER, locale, _text, -1, &ubrk);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_create_p3
 * @since_tizen     2.3.1
 * @description     Creates i18n_ubreak_iterator_h
 * @scenario        Creates the handle for line type
 */
int utc_capi_base_utils_i18n_ubrk_create_p3(void)
{
    if(NULL != ubrk) {
        i18n_ubrk_destroy(ubrk);
        ubrk = NULL;
    }

    ret = i18n_ubrk_create(I18N_UBRK_LINE, locale, _text, -1, &ubrk);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_create_p4
 * @since_tizen     2.3.1
 * @description     Creates i18n_ubreak_iterator_h
 * @scenario        Creates the handle for sentence type
 */
int utc_capi_base_utils_i18n_ubrk_create_p4(void)
{
    if(NULL != ubrk) {
        i18n_ubrk_destroy(ubrk);
        ubrk = NULL;
    }

    ret = i18n_ubrk_create(I18N_UBRK_SENTENCE, locale, _text, -1, &ubrk);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_create_n
 * @since_tizen     2.3.1
 * @description     Creates i18n_ubreak_iterator_h
 * @scenario        Creates the handle giving false type argument.
 */
int utc_capi_base_utils_i18n_ubrk_create_n(void)
{
    ret = i18n_ubrk_create(-1, locale, _text, -1, &ubrk);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_create_n2
 * @since_tizen     2.3.1
 * @description     Creates i18n_ubreak_iterator_h.
 * @scenario        Creates the handle giving false text length.
 */
int utc_capi_base_utils_i18n_ubrk_create_n2(void)
{
    ret = i18n_ubrk_create(I18N_UBRK_SENTENCE, locale, _text, -2, &ubrk);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_create_n3
 * @since_tizen     2.3.1
 * @description     Creates i18n_ubreak_iterator_h.
 * @scenario        Creates the handle giving false text length.
 */
int utc_capi_base_utils_i18n_ubrk_create_n3(void)
{
    ret = i18n_ubrk_create(I18N_UBRK_SENTENCE, locale, _text, -1, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_create_rules_p
 * @since_tizen     2.3.1
 * @description     Creates rule.
 * @scenario        Creates rule from a string.
 */
int utc_capi_base_utils_i18n_ubrk_create_rules_p(void)
{
    if(NULL != ubrk) {
        i18n_ubrk_destroy(ubrk);
        ubrk = NULL;
    }

    const char *rules = "[A-N]{100}; \n"
                        "[a-w]{200}; \n"
                        "[\\p{L}]{300}; \n"
                        "[\\p{N}]{400}; \n"
                        "[0-5]{500}; \n"
                        "!.*;\n";

    i18n_uchar *_rules = (i18n_uchar*)calloc(strlen(rules) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_rules, rules);

    i18n_uparse_error_s parse_err;

    ret = i18n_ubrk_create_rules(_rules, -1, _text, -1, &ubrk, &parse_err);
    free(_rules);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_create_rules_n
 * @since_tizen     2.3.1
 * @description     Tries to create a rule.
 * @scenario        Tries to create rule without rule set parameter.
 */
int utc_capi_base_utils_i18n_ubrk_create_rules_n(void)
{
    i18n_uparse_error_s parse_err;

    ret = i18n_ubrk_create_rules(NULL, 0, _text, -1, &ubrk, &parse_err);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_create_rules_n2
 * @since_tizen     2.3.1
 * @description     Tries to create a rule.
 * @scenario        Tries to create rule with false rule length.
 */
int utc_capi_base_utils_i18n_ubrk_create_rules_n2(void)
{
    if(NULL != ubrk) {
        i18n_ubrk_destroy(ubrk);
        ubrk = NULL;
    }

    const char *rules = "[A-N]{100}; \n"
                        "[a-w]{200}; \n"
                        "[\\p{L}]{300}; \n"
                        "[\\p{N}]{400}; \n"
                        "[0-5]{500}; \n"
                        "!.*;\n";

    i18n_uchar *_rules = (i18n_uchar*)calloc(strlen(rules) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_rules, rules);

    i18n_uparse_error_s parse_err;

    ret = i18n_ubrk_create_rules(_rules, -2, _text, -1, &ubrk, &parse_err);
    free(_rules);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_create_rules_n3
 * @since_tizen     2.3.1
 * @description     Tries to create a rule.
 * @scenario        Tries to create rule with false text length.
 */
int utc_capi_base_utils_i18n_ubrk_create_rules_n3(void)
{
    if(NULL != ubrk) {
        i18n_ubrk_destroy(ubrk);
        ubrk = NULL;
    }

    const char *rules = "[A-N]{100}; \n"
                        "[a-w]{200}; \n"
                        "[\\p{L}]{300}; \n"
                        "[\\p{N}]{400}; \n"
                        "[0-5]{500}; \n"
                        "!.*;\n";

    i18n_uchar *_rules = (i18n_uchar*)calloc(strlen(rules) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_rules, rules);

    i18n_uparse_error_s parse_err;

    ret = i18n_ubrk_create_rules(_rules, -1, _text, -2, &ubrk, &parse_err);
    free(_rules);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_create_rules_n4
 * @since_tizen     2.3.1
 * @description     Tries to create a rule.
 * @scenario        Tries to create rule without i18n_ubreak_iterator_h handle
 */
int utc_capi_base_utils_i18n_ubrk_create_rules_n4(void)
{
    if(NULL != ubrk) {
        i18n_ubrk_destroy(ubrk);
        ubrk = NULL;
    }

    const char *rules = "[A-N]{100}; \n"
                        "[a-w]{200}; \n"
                        "[\\p{L}]{300}; \n"
                        "[\\p{N}]{400}; \n"
                        "[0-5]{500}; \n"
                        "!.*;\n";

    i18n_uchar *_rules = (i18n_uchar*)calloc(strlen(rules) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(_rules, rules);

    i18n_uparse_error_s parse_err;

    ret = i18n_ubrk_create_rules(_rules, -1, _text, -1, NULL, &parse_err);
    free(_rules);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_safe_clone_p
 * @since_tizen     2.3.1
 * @description     Clones i18n_ubreak_iterator_h.
 * @scenario        Clones the break iterator instance and checks whether
 *                  it has been successfully created.
 */
int utc_capi_base_utils_i18n_ubrk_safe_clone_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    i18n_ubreak_iterator_h break_iter_clone = NULL;

    ret = i18n_ubrk_safe_clone(ubrk, NULL, NULL, &break_iter_clone);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_ubrk_destroy(break_iter_clone);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_safe_clone_n
 * @since_tizen     2.3.1
 * @description     Tries to clone i18n_ubreak_iterator_h.
 * @scenario        Tries to clone non-existing break iterator.
 */
int utc_capi_base_utils_i18n_ubrk_safe_clone_n(void)
{
    i18n_ubreak_iterator_h break_iter_clone = NULL;

    ret = i18n_ubrk_safe_clone(NULL, NULL, NULL, &break_iter_clone);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_safe_clone_n3
 * @since_tizen     2.3.1
 * @description     Tries to clone i18n_ubreak_iterator_h.
 * @scenario        Tries to clone non-existing break iterator.
 */
int utc_capi_base_utils_i18n_ubrk_safe_clone_n3(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    ret = i18n_ubrk_safe_clone(ubrk, NULL, NULL, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_destroy_p
 * @since_tizen     2.3.1
 * @description     Destroys the break iterator handle.
 * @scenario        Destroys the break iterator and checks whether
 *                  the operation succeeded.
 */
int utc_capi_base_utils_i18n_ubrk_destroy_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    ret = i18n_ubrk_destroy(ubrk);
    ubrk = NULL;
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_destroy_n
 * @since_tizen     2.3.1
 * @description     Destroys empty handle.
 * @scenario        Tries to destroy NULL handle.
 */
int utc_capi_base_utils_i18n_ubrk_destroy_n(void)
{
    ret = i18n_ubrk_destroy(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_set_text_p
 * @since_tizen     2.3.1
 * @description     Sets the text.
 * @scenario        Sets the text for the break iterator.
 */
int utc_capi_base_utils_i18n_ubrk_set_text_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    ret = i18n_ubrk_set_text(ubrk, _text, strlen(text));
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_set_text_n
 * @since_tizen     2.3.1
 * @description     Tries to set text with false argument.
 * @scenario        The text is set with invalid length of the text parameter.
 */
int utc_capi_base_utils_i18n_ubrk_set_text_n(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    ret = i18n_ubrk_set_text(ubrk, _text, -1);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_current_p
 * @since_tizen     2.3.1
 * @description     Gets current boundary index.
 * @scenario        Gets current boundary index and checks
 *                  whether the index is correct.
 */
int utc_capi_base_utils_i18n_ubrk_current_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    int32_t current = i18n_ubrk_current(ubrk);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(current, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_current_n
 * @since_tizen     2.3.1
 * @description     Gets index of non-existing break iterator.
 * @scenario        Tries to make error when giving NULL as break iterator.
 */
int utc_capi_base_utils_i18n_ubrk_current_n(void)
{
    i18n_ubrk_current(NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_next_p
 * @since_tizen     2.3.1
 * @description     Moves the iterator to the next position.
 * @scenario        Moves the iterator to the next position and 
 *                  checks whether it moved to the correct place.
 */
int utc_capi_base_utils_i18n_ubrk_next_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    int32_t next = i18n_ubrk_next(ubrk);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(next, 4);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_next_n
 * @since_tizen     2.3.1
 * @description     Moves the empty iterator.
 * @scenario        Moves the non-existing iterator and expects for the error.
 */
int utc_capi_base_utils_i18n_ubrk_next_n(void)
{
    int32_t next = i18n_ubrk_next(NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(next, -1);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_previous_p
 * @since_tizen     2.3.1
 * @description     Moves the iterator to the next position.
 * @scenario        Moves the iterator to the next position and 
 *                  checks whether it moved to the correct place.
 */
int utc_capi_base_utils_i18n_ubrk_previous_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    int32_t next = i18n_ubrk_next(ubrk);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(next, 4);

    int32_t previous = i18n_ubrk_previous(ubrk);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(previous, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_previous_n
 * @since_tizen     2.3.1
 * @description     Moves the empty iterator.
 * @scenario        Moves the non-existing iterator and expects for the error.
 */
int utc_capi_base_utils_i18n_ubrk_previous_n(void)
{
    int32_t previous = i18n_ubrk_previous(NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
    assert_eq(previous, -1);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_first_p
 * @since_tizen     2.3.1
 * @description     Moves the iterator to the start occurrence.
 * @scenario        Moves the iterator to the start occurrence and 
 *                  checks whether it moved to the correct place.
 */
int utc_capi_base_utils_i18n_ubrk_first_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    int32_t start = i18n_ubrk_first(ubrk);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(start, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_first_n
 * @since_tizen     2.3.1
 * @description     Moves the empty iterator.
 * @scenario        Moves the non-existing iterator to the first occurrence and expects for the error.
 */
int utc_capi_base_utils_i18n_ubrk_first_n(void)
{
    i18n_ubrk_first(NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_last_p
 * @since_tizen     2.3.1
 * @description     Moves the iterator to the last occurrence.
 * @scenario        Moves the iterator to the last occurrence and 
 *                  checks whether it moved to the correct place.
 */
int utc_capi_base_utils_i18n_ubrk_last_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    int32_t last = i18n_ubrk_last(ubrk);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(last, 19);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_last_n
 * @since_tizen     2.3.1
 * @description     Moves the empty iterator.
 * @scenario        Moves the non-existing iterator to the last occurrence
 *                  and expects for the error.
 */
int utc_capi_base_utils_i18n_ubrk_last_n(void)
{
    i18n_ubrk_last(NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_preceding_p
 * @since_tizen     2.3.1
 * @description     Moves the iterator to the preceding position.
 * @scenario        Moves the iterator to the preceding position and 
 *                  checks whether it moved to the correct place.
 */
int utc_capi_base_utils_i18n_ubrk_preceding_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    int32_t offset = 5;

    int32_t preceding = i18n_ubrk_preceding(ubrk, offset);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(preceding, 4);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_preceding_n
 * @since_tizen     2.3.1
 * @description     Moves the empty iterator.
 * @scenario        Moves the non-existing iterator to the preceding occurrence and expects for the error.
 */
int utc_capi_base_utils_i18n_ubrk_preceding_n(void)
{
    int32_t offset = 5;

    i18n_ubrk_preceding(NULL, offset);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_following_p
 * @since_tizen     2.3.1
 * @description     Moves the iterator to the following position.
 * @scenario        Moves the iterator to the following position and 
 *                  checks whether it moved to the correct place.
 */
int utc_capi_base_utils_i18n_ubrk_following_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    int32_t offset = 4;

    int32_t following = i18n_ubrk_following(ubrk, offset);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(following, 5);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_following_n
 * @since_tizen     2.3.1
 * @description     Moves the empty iterator.
 * @scenario        Moves the non-existing iterator to the following occurrence and expects for the error.
 */
int utc_capi_base_utils_i18n_ubrk_following_n(void)
{
    int32_t offset = 5;

    i18n_ubrk_following(NULL, offset);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_get_available_p
 * @since_tizen     2.3.1
 * @description     Gets available locale by index.
 * @scenario        Gets available locale by index and checks obtained name.
 */
int utc_capi_base_utils_i18n_ubrk_get_available_p(void)
{
    int32_t index = 0;

    const char *locale = i18n_ubrk_get_available(index);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(locale, NULL);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_get_available_n
 * @since_tizen     2.3.1
 * @description     Tries to get locale by invalid index.
 * @scenario        Invalid index is passed as the parameter.
 */
int utc_capi_base_utils_i18n_ubrk_get_available_n(void)
{
    i18n_ubrk_get_available(-1);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_count_available_p
 * @since_tizen     2.3.1
 * @description     Gets available locales.
 * @scenario        Gets available locals and checks whether
 *                  the count is greater than 0.
 */
int utc_capi_base_utils_i18n_ubrk_count_available_p(void)
{
    int32_t count_available = i18n_ubrk_count_available();

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_geq(count_available, 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_is_boundary_p
 * @since_tizen     2.3.1
 * @description     Checks whether the specified position is boundary.
 * @scenario        The test expects that the iterator is boundary.
 */
int utc_capi_base_utils_i18n_ubrk_is_boundary_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    int32_t offset = 5;

    i18n_ubool is_boundary = i18n_ubrk_is_boundary(ubrk, offset);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(is_boundary, 1);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_is_boundary_n
 * @since_tizen     2.3.1
 * @description     Checks whether non-existing iterator is on boundary position.
 * @scenario        The test expects I18N_ERROR_INVALID_PARAMETER error after the call.
 */
int utc_capi_base_utils_i18n_ubrk_is_boundary_n(void)
{
    int32_t offset = 5;

    i18n_ubrk_is_boundary(NULL, offset);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_get_rule_status_p
 * @since_tizen     2.3.1
 * @description     Gets the status of the iterator.
 * @scenario        Checks whether the function return no error.
 */
int utc_capi_base_utils_i18n_ubrk_get_rule_status_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    i18n_ubrk_get_rule_status(ubrk);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_get_rule_status_n
 * @since_tizen     2.3.1
 * @description     Gets the status of non-existing iterator.
 * @scenario        Checks whether the function return error.
 */
int utc_capi_base_utils_i18n_ubrk_get_rule_status_n(void)
{
    i18n_ubrk_get_rule_status(NULL);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_get_rule_status_vec_p
 * @since_tizen     2.3.1
 * @description     Gets the status of the iterator.
 * @scenario        Checks whether the function return no error.
 */
int utc_capi_base_utils_i18n_ubrk_get_rule_status_vec_p(void)
{
    const int32_t rule_string_length = 200;
    i18n_uchar rules[rule_string_length];

    i18n_ustring_copy_ua_n(rules, "[A-N]{100}; \n"
                                  "[a-w]{200}; \n"
                                  "[\\p{L}]{300}; \n"
                                  "[\\p{N}]{400}; \n"
                                  "[0-5]{500}; \n"
                                  "!.*;\n", rule_string_length);

    const int32_t test_string_length = 25;
    i18n_uchar testString[test_string_length];

    i18n_ustring_copy_ua_n(testString, "ABC", test_string_length);

    ret = i18n_ubrk_create_rules(rules, -1, testString, -1, &ubrk, NULL);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    int32_t pos = i18n_ubrk_next(ubrk);
    assert_eq(pos, 1);

    const int32_t capacity = 64;
    int32_t fill_in_vec[capacity];
    memset(fill_in_vec, -1, sizeof(fill_in_vec));

    int32_t rules_number = i18n_ubrk_get_rule_status_vec(ubrk, fill_in_vec, capacity);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);
    assert_eq(rules_number, 2);
    assert_eq(fill_in_vec[0], 100);
    assert_eq(fill_in_vec[1], 300);
    assert_eq(fill_in_vec[2], -1);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_get_rule_status_vec_n
 * @since_tizen     2.3.1
 * @description     Gets the status of non-existing iterator.
 * @scenario        Checks whether the function return error.
 */
int utc_capi_base_utils_i18n_ubrk_get_rule_status_vec_n(void)
{
    // Check invalid parameter error.
    i18n_error_code_e ret = I18N_ERROR_NONE;
    int32_t capacity = 64;
    int32_t fill_in_vec[capacity];

    i18n_ubrk_get_rule_status_vec(NULL, fill_in_vec, capacity);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    // Check buffer overflow error.
    const int32_t rule_string_length = 200;
    i18n_uchar rules[rule_string_length];

    i18n_ustring_copy_ua_n(rules, "[A-N]{100}; \n"
            "[a-w]{200}; \n"
            "[\\p{L}]{300}; \n"
            "[\\p{N}]{400}; \n"
            "[0-5]{500}; \n"
            "!.*;\n", rule_string_length);

    const int32_t test_string_length = 25;
    i18n_uchar testString[test_string_length];

    i18n_ustring_copy_ua_n(testString, "ABC", test_string_length);

    ret = i18n_ubrk_create_rules(rules, -1, testString, -1, &ubrk, NULL);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    int32_t pos = i18n_ubrk_next(ubrk);
    assert_eq(pos, 1);

    int32_t rules_number = i18n_ubrk_get_rule_status_vec(ubrk, fill_in_vec, 0);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);
    assert_eq(rules_number, 2);

    return 0;
}

/**
 * Compare two locale IDs.  If they are equal, return 0.  If `string'
 * starts with `prefix' plus an additional element, that is, string ==
 * prefix + '_' + x, then return 1.  Otherwise return a value < 0.
 */
static int _loccmp(const char *string, const char *prefix)
{
    if(NULL == string || NULL == prefix) {
        return -3;
    }

    /* 'root' is less than everything */
    if(strcmp(prefix, "root") == 0) {
        return (strcmp(string, "root") == 0) ? 0 : 1;
    }

    int32_t string_len = (int32_t)strlen(string);
    int32_t prefix_len = (int32_t)strlen(prefix);

    int32_t compare = strncmp(string, prefix, prefix_len);
    if(compare)
        return -1;
    if(string_len == prefix_len)
        return 0;
    if(string[prefix_len] == '_')
        return 1;
    return -2; // false match, e.g. "en_USX" compared with "en_US"
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_get_locale_by_type_p
 * @since_tizen     2.3
 * @description     Gets locale of specified type.
 * @scenario        Gets the locale and checks whether it is correct.
 */
int utc_capi_base_utils_i18n_ubrk_get_locale_by_type_p(void)
{
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    const char *locale = "ar_KW_ABDALI";
    ret = i18n_ubrk_create(I18N_UBRK_WORD, locale, _text, strlen(text), &ubrk);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(ubrk, NULL);

    const char *actual = i18n_ubrk_get_locale_by_type(ubrk, I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    const char *valid = i18n_ubrk_get_locale_by_type(ubrk, I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE);
    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_NONE);

    /*
     * We want the valid locale to be strictly ">" than the requested locale,
     * and the valid locale to be >= than the actual locale.
     */
    assert_gt(_loccmp(locale, valid), 0);
    assert_geq(_loccmp(valid, actual), 0);

    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_ubrk_get_locale_by_type_n
 * @since_tizen     2.3
 * @description     Gets locale of specified type from non-existing iterator.
 * @scenario        Pass NULL as the break iterator and expects fail.
 */
int utc_capi_base_utils_i18n_ubrk_get_locale_by_type_n(void)
{
    i18n_ubrk_get_locale_by_type(NULL, I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE);

    ret = get_last_result();
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
