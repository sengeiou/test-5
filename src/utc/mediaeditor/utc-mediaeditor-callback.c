/*
 * Copyright (c) 2022 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "assert.h"
#include <media_editor.h>

static mediaeditor_h g_mediaeditor = NULL;

static void __mediaeditor_error_cb(mediaeditor_error_e error, mediaeditor_state_e state, void *user_data)
{
}

static void __mediaeditor_state_changed_cb(mediaeditor_state_e previous, mediaeditor_state_e current, void *user_data)
{
}

/**
 * @function    utc_mediaeditor_startup
 * @description Should be called before a test
 */
void utc_mediaeditor_startup_callback(void)
{
    int ret = mediaeditor_create(&g_mediaeditor);
    if (ret != MEDIAEDITOR_ERROR_NONE) {
        fprintf(stderr, "mediaeditor_create() is failed");
        return;
    }
}

/**
 * @function    utc_mediaeditor_cleanup
 * @description Should be called after a test
 */
void utc_mediaeditor_cleanup_callback(void)
{
    if (g_mediaeditor) {
        int ret = mediaeditor_destroy(g_mediaeditor);
        if (ret != MEDIAEDITOR_ERROR_NONE) {
            fprintf(stderr, "mediaeditor_destroy() is failed");
            return;
        }
    }
}

/**
 * @testcase    utc_mediaeditor_set_error_cb_p
 * @since_tizen 7.0
 * @description Sets error cb\n
 *              - Create a mediaeditor handle\n
 *              - Set error callback
 */
int utc_mediaeditor_set_error_cb_p(void)
{
    int ret = mediaeditor_set_error_cb(g_mediaeditor, __mediaeditor_error_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_error_cb_n1
 * @since_tizen 7.0
 * @description Sets error cb\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_set_error_cb_n1(void)
{
    int ret = mediaeditor_set_error_cb(NULL, __mediaeditor_error_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_error_cb_n2
 * @since_tizen 7.0
 * @description Sets error cb\n
 *              - Pass null cb function
 */
int utc_mediaeditor_set_error_cb_n2(void)
{
    int ret = mediaeditor_set_error_cb(g_mediaeditor, NULL, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_unset_error_cb_p
 * @since_tizen 7.0
 * @description Unsets error cb\n
 *              - Set error callback\n
 *              - Unset error callback
 */
int utc_mediaeditor_unset_error_cb_p(void)
{
    int ret = mediaeditor_set_error_cb(g_mediaeditor, __mediaeditor_error_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_unset_error_cb(g_mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_unset_error_cb_n1
 * @since_tizen 7.0
 * @description Unsets error cb
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_unset_error_cb_n1(void)
{
    int ret = mediaeditor_unset_error_cb(NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_unset_error_cb_n2
 * @since_tizen 7.0
 * @description Unsets error cb\n
 *              - Unset error cb without setting error cb
 */
int utc_mediaeditor_unset_error_cb_n2(void)
{
    int ret = mediaeditor_unset_error_cb(g_mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_OPERATION);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_state_changed_cb_p
 * @since_tizen 7.0
 * @description Sets state changed cb\n
 *              - Set state changed callback
 */
int utc_mediaeditor_set_state_changed_cb_p(void)
{
    int ret = mediaeditor_set_state_changed_cb(g_mediaeditor, __mediaeditor_state_changed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_state_changed_cb_n1
 * @since_tizen 7.0
 * @description Sets state changed cb\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_set_state_changed_cb_n1(void)
{
    int ret = mediaeditor_set_state_changed_cb(NULL, __mediaeditor_state_changed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_set_state_changed_cb_n2
 * @since_tizen 7.0
 * @description Sets state changed cb\n
 *              - Pass null cb function
 */
int utc_mediaeditor_set_state_changed_cb_n2(void)
{
    int ret = mediaeditor_set_state_changed_cb(g_mediaeditor, NULL, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_unset_state_changed_cb_p
 * @since_tizen 7.0
 * @description Unsets state changed cb\n
 *              - Set state changed callback\n
 *              - Unset state changed callback
 */
int utc_mediaeditor_unset_state_changed_cb_p(void)
{
    int ret = mediaeditor_set_state_changed_cb(g_mediaeditor, __mediaeditor_state_changed_cb, NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    ret = mediaeditor_unset_state_changed_cb(g_mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_unset_state_changed_cb_n1
 * @since_tizen 7.0
 * @description Unsets state changed cb\n
 *              - Pass null mediaeditor handle
 */
int utc_mediaeditor_unset_state_changed_cb_n1(void)
{
    int ret = mediaeditor_unset_state_changed_cb(NULL);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase    utc_mediaeditor_unset_state_changed_cb_n2
 * @since_tizen 7.0
 * @description Unsets state changed cb\n
 *              - Unset state changed cb without set error cb
 */
int utc_mediaeditor_unset_state_changed_cb_n2(void)
{
    int ret = mediaeditor_unset_state_changed_cb(g_mediaeditor);
    assert_eq(ret, MEDIAEDITOR_ERROR_INVALID_OPERATION);

    return 0;
}
