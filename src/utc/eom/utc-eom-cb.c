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
#include <eom.h>

//& set: Eom
static void cb_function(eom_output_id output_id, void *user_data)
{
}

/**
 * @function		utc_eom_cb_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_eom_cb_startup(void)
{
    eom_init();
}

/**
 * @function		utc_eom_cb_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_eom_cb_cleanup(void)
{
    eom_deinit();
}

/**
 * @testcase		utc_eom_set_output_added_cb_p
 * @since_tizen		2.4
 * @description		Sets the output device added callback function
 * @scenario		Calls eom_set_output_added_cb
 */
int utc_eom_set_output_added_cb_p(void)
{
    int ret = EOM_ERROR_NONE;
    ret = eom_set_output_added_cb(cb_function, NULL);
    assert_eq(ret, EOM_ERROR_NONE);

    return 0;
}
/**
 * @testcase		utc_eom_set_output_added_cb_n
 * @since_tizen		2.4
 * @description		Sets the output device added callback function in intended error case
 * @scenario 		Calls eom_set_output_added_cb with invalid parameter
 */
int utc_eom_set_output_added_cb_n(void)
{
    int ret = EOM_ERROR_NONE;
    ret = eom_set_output_added_cb(NULL, NULL);
    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_eom_unset_output_added_cb_p
 * @since_tizen		2.4
 * @description		Unsets the output device added callback function
 * @scenario		Calls eom_unset_output_added_cb with set callback
 */
int utc_eom_unset_output_added_cb_p(void)
{
    int ret = EOM_ERROR_NONE;
    eom_set_output_added_cb(cb_function, NULL);
    ret = eom_unset_output_added_cb(cb_function);
    assert_eq(ret, EOM_ERROR_NONE);

    return 0;
}
/**
 * @testcase		utc_eom_unset_output_added_cb_n
 * @since_tizen		2.4
 * @description		Unsets the output device added callback function in intended error case
 * @scenario		Calls eom_unset_output_added_cb with invalid parameter
 */
int utc_eom_unset_output_added_cb_n(void)
{
    int ret = EOM_ERROR_NONE;
    ret = eom_unset_output_added_cb(NULL);
    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_eom_set_output_removeed_cb_p
 * @since_tizen		2.4
 * @description		Sets the output device removed callback function
 * @scenario		Calls eom_set_output_removed_cb
 */
int utc_eom_set_output_removeed_cb_p(void)
{
    int ret = EOM_ERROR_NONE;
    ret = eom_set_output_removed_cb(cb_function, NULL);
    assert_eq(ret, EOM_ERROR_NONE);

    return 0;
}
/**
 * @testcase		utc_eom_set_output_removed_cb_n
 * @since_tizen		2.4
 * @description		Sets the output device removed callback function in intended error case
 * @scenario		Calls eom_set_output_removed_cb with invalid parameter
 */
int utc_eom_set_output_removed_cb_n(void)
{
    int ret = EOM_ERROR_NONE;
    ret = eom_set_output_removed_cb(NULL, NULL);
    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_eom_unset_output_removed_cb_p
 * @since_tizen		2.4
 * @description		Unsets the output device removed callback function
 * @scenario		Calls eom_unset_output_removed_cb with set callback
 */
int utc_eom_unset_output_removed_cb_p(void)
{
    int ret = EOM_ERROR_NONE;
    eom_set_output_removed_cb(cb_function, NULL);
    ret = eom_unset_output_removed_cb(cb_function);
    assert_eq(ret, EOM_ERROR_NONE);

    return 0;
}
/**
 * @testcase		utc_eom_unset_output_removed_cb_n
 * @since_tizen		2.4
 * @description		Unsets the output device removed callback function in intended error case
 * @scenario		Calls eom_unset_output_removed_cb with invalid parameter
 */
int utc_eom_unset_output_removed_cb_n(void)
{
    int ret = EOM_ERROR_NONE;
    ret = eom_unset_output_removed_cb(NULL);
    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_eom_set_mode_changed_cb_p
 * @since_tizen		2.4
 * @description		Sets the output device mode changed callback function
 * @scenario		Calls eom_set_mode_changed_cb
 */
int utc_eom_set_mode_changed_cb_p(void)
{
    int ret = EOM_ERROR_NONE;
    ret = eom_set_mode_changed_cb(cb_function, NULL);
    assert_eq(ret, EOM_ERROR_NONE);

    return 0;
}
/**
 * @testcase		utc_eom_set_mode_changed_cb_n
 * @since_tizen		2.4
 * @description		Sets the output device mode changed callback function in intended error case
 * @scenario		Calls eom_set_mode_changed_cb with invalid parameter
 */
int utc_eom_set_mode_changed_cb_n(void)
{
    int ret = EOM_ERROR_NONE;
    ret = eom_set_mode_changed_cb(NULL, NULL);
    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_eom_unset_mode_changed_cb_p
 * @since_tizen		2.4
 * @description		Unsets the output device mode changed callback function
 * @scenario		Calls eom_unset_mode_changed_cb with set callback
 */
int utc_eom_unset_mode_changed_cb_p(void)
{
    int ret = EOM_ERROR_NONE;
    eom_set_mode_changed_cb(cb_function, NULL);
    ret = eom_unset_mode_changed_cb(cb_function);
    assert_eq(ret, EOM_ERROR_NONE);

    return 0;
}
/**
 * @testcase		utc_eom_unset_mode_changed_cb_n
 * @since_tizen		2.4
 * @description		Unsets the output device mode changed callback function in intended error case
 * @scenario		Calls eom_unset_mode_changed_cb with invalid parameter
 */
int utc_eom_unset_mode_changed_cb_n(void)
{
    int ret = EOM_ERROR_NONE;
    ret = eom_unset_mode_changed_cb(NULL);
    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_eom_set_attribute_changed_cb_p
 * @since_tizen		2.4
 * @description		Sets the output device attribute changed callback function
 * @scenario		Calls eom_set_attribute_changed_cb
 */
int utc_eom_set_attribute_changed_cb_p(void)
{
    int ret = EOM_ERROR_NONE;
    ret = eom_set_attribute_changed_cb(cb_function, NULL);
    assert_eq(ret, EOM_ERROR_NONE);

    return 0;
}
/**
 * @testcase		utc_eom_set_attribute_changed_cb_n
 * @since_tizen		2.4
 * @description		Sets the output device attribute changed callback function in intended error case
 * @scenario		Calls eom_set_attribute_changed_cb with invalid parameter
 */
int utc_eom_set_attribute_changed_cb_n(void)
{
    int ret = EOM_ERROR_NONE;
    ret = eom_set_attribute_changed_cb(NULL, NULL);
    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_eom_unset_attribute_changed_cb_p
 * @since_tizen		2.4
 * @description		Unsets the output device attribute changed callback function
 * @scenario		Calls eom_unset_attribute_changed_cb with set callback
 */
int utc_eom_unset_attribute_changed_cb_p(void)
{
    int ret = EOM_ERROR_NONE;
    eom_set_attribute_changed_cb(cb_function, NULL);
    ret = eom_unset_attribute_changed_cb(cb_function);
    assert_eq(ret, EOM_ERROR_NONE);

    return 0;
}
/**
 * @testcase		utc_eom_unset_attribute_chang_cb_n
 * @since_tizen		2.4
 * @description		Unsets the output device attribute changed callback function in intended error case
 * @scenario		Calls eom_unset_attribute_changed_cb with invalid parameter
 */
int utc_eom_unset_attribute_chang_cb_n(void)
{
    int ret = EOM_ERROR_NONE;
    ret = eom_unset_attribute_changed_cb(NULL);
    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}
