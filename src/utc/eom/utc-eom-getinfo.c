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
static eom_output_id getinfo_output_id = 0;
static bool g_getinfo_no_device = false;

/**
 * @function		utc_eom_getinfo_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_eom_getinfo_startup(void)
{
    eom_output_id *output_ids = NULL;
    int id_cnt;

    eom_init();

    getinfo_output_id = 0;
    g_getinfo_no_device = false;

    output_ids = eom_get_eom_output_ids(&id_cnt);
    if (id_cnt != 0)
    {
        getinfo_output_id = output_ids[0];
        free (output_ids);
    }

    if (getinfo_output_id == 0)
    {
        g_getinfo_no_device = true;
        getinfo_output_id = 999;
    }
}

/**
 * @function		utc_eom_getinfo_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_eom_getinfo_cleanup(void)
{
    eom_deinit();
}

/**
 * @testcase		utc_eom_get_output_type_p
 * @since_tizen		2.4
 * @description		Gets the output device's type
 * @scenario		Calls utc_eom_get_output_type with output id
 */
int utc_eom_get_output_type_p(void)
{
    eom_output_type_e type;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_type(getinfo_output_id, &type);
    if (g_getinfo_no_device == true)
    {
        assert_eq(ret, EOM_ERROR_NO_SUCH_DEVICE);
    }
    else
    {
        assert_eq(ret, EOM_ERROR_NONE);
    }

    return 0;
}
/**
 * @testcase		utc_eom_get_output_type_n1
 * @since_tizen		2.4
 * @description		Gets the output device's type in intended error case
 * @scenario		Calls utc_eom_get_output_type with invalid parameter
 */
int utc_eom_get_output_type_n1(void)
{
    eom_output_type_e type;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_type(0, &type);

    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}
/**
 * @testcase		utc_eom_get_output_type_n2
 * @since_tizen		2.4
 * @description		Gets the output device's type in intended error case
 * @scenario		Calls utc_eom_get_output_type with invalid parameter
 */
int utc_eom_get_output_type_n2(void)
{
    eom_output_type_e type;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_type(10000, &type);

    assert_eq(ret, EOM_ERROR_NO_SUCH_DEVICE);

    return 0;
}

/**
 * @testcase		utc_eom_get_output_mode_p
 * @since_tizen		2.4
 * @description		Gets the output devices's mode
 * @scenario		Calls eom_get_output_mode with output id
 */
int utc_eom_get_output_mode_p(void)
{
    eom_output_mode_e mode;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_mode(getinfo_output_id, &mode);
    if (g_getinfo_no_device == true)
    {
        assert_eq(ret, EOM_ERROR_NO_SUCH_DEVICE);
    }
    else
    {
        assert_eq(ret, EOM_ERROR_NONE);
    }

    return 0;
}
/**
 * @testcase		utc_eom_get_output_mode_n1
 * @since_tizen		2.4
 * @description		Gets the output devices's mode in intended error case
 * @scenario		Calls eom_get_output_mode with invalid parameter
 */
int utc_eom_get_output_mode_n1(void)
{
    eom_output_mode_e mode;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_mode(0, &mode);

    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}
/**
 * @testcase		utc_eom_get_output_mode_n2
 * @since_tizen		2.4
 * @description		Gets the output devices's mode in intended error case
 * @scenario		Calls eom_get_output_mode with invalid parameter
 */
int utc_eom_get_output_mode_n2(void)
{
    eom_output_mode_e mode;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_mode(10000, &mode);

    assert_eq(ret, EOM_ERROR_NO_SUCH_DEVICE);

    return 0;
}

/**
 * @testcase		utc_eom_get_output_attribute_p
 * @since_tizen		2.4
 * @description		Gets the output devices's attribute
 * @scenario		Calls eom_get_output_attribute with output id
 */
int utc_eom_get_output_attribute_p(void)
{
    eom_output_attribute_e attribute;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_attribute(getinfo_output_id, &attribute);
    if (g_getinfo_no_device == true)
    {
        assert_eq(ret, EOM_ERROR_NO_SUCH_DEVICE);
    }
    else
    {
        assert_eq(ret, EOM_ERROR_NONE);
    }

    return 0;
}
/**
 * @testcase		utc_eom_get_output_attribute_n1
 * @since_tizen		2.4
 * @description		Gets the output devices's attribute in intended error case
 * @scenario		Calls eom_get_output_attribute with invalid parameter
 */
int utc_eom_get_output_attribute_n1(void)
{
    eom_output_attribute_e attribute;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_attribute(0, &attribute);

    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}
/**
 * @testcase		utc_eom_get_output_attribute_n2
 * @since_tizen		2.4
 * @description		Gets the output devices's attribute in intended error case
 * @scenario		Calls eom_get_output_attribute with invalid parameter
 */
int utc_eom_get_output_attribute_n2(void)
{
    eom_output_attribute_e attribute;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_attribute(10000, &attribute);

    assert_eq(ret, EOM_ERROR_NO_SUCH_DEVICE);

    return 0;
}

/**
 * @testcase		utc_eom_get_output_attribute_state_p
 * @since_tizen		2.4
 * @description		Gets the output devices's attribute state
 * @scenario		Calls eom_get_output_attribute_state with output id
 */
int utc_eom_get_output_attribute_state_p(void)
{
    eom_output_attribute_state_e state;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_attribute_state(getinfo_output_id, &state);
    if (g_getinfo_no_device == true)
    {
        assert_eq(ret, EOM_ERROR_NO_SUCH_DEVICE);
    }
    else
    {
        assert_eq(ret, EOM_ERROR_NONE);
    }

    return 0;
}
/**
 * @testcase		utc_eom_get_output_attribute_state_n1
 * @since_tizen		2.4
 * @description		Gets the output devices's attribute state in intended error case
 * @scenario		Calls eom_get_output_attribute_state with invalid parameter
 */
int utc_eom_get_output_attribute_state_n1(void)
{
    eom_output_attribute_state_e state;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_attribute_state(0, &state);

    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}
/**
 * @testcase		utc_eom_get_output_attribute_state_n2
 * @since_tizen		2.4
 * @description		Gets the output devices's attribute state in intended error case
 * @scenario		Calls eom_get_output_attribute_state with invalid parameter
 */
int utc_eom_get_output_attribute_state_n2(void)
{
    eom_output_attribute_state_e state;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_attribute_state(10000, &state);

    assert_eq(ret, EOM_ERROR_NO_SUCH_DEVICE);

    return 0;
}

/**
 * @testcase		utc_eom_get_output_resolution_p
 * @since_tizen		2.4
 * @description		Gets the output devices's resolution
 * @scenario		Calls eom_get_output_resolution with output id
 */
int utc_eom_get_output_resolution_p(void)
{
    int width;
    int height;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_resolution(getinfo_output_id, &width, &height);
    if (g_getinfo_no_device == true)
    {
        assert_eq(ret, EOM_ERROR_NO_SUCH_DEVICE);
    }
    else
    {
        assert_eq(ret, EOM_ERROR_NONE);
    }

    return 0;
}
/**
 * @testcase		utc_eom_get_output_resolution_n1
 * @since_tizen		2.4
 * @description		Gets the output devices's resolution in intended error case
 * @scenario		Calls eom_get_output_resolution with invalid parameter
 */
int utc_eom_get_output_resolution_n1(void)
{
    int width;
    int height;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_resolution(0, &width, &height);

    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}
/**
 * @testcase		utc_eom_get_output_resolution_n2
 * @since_tizen		2.4
 * @description		Gets the output devices's resolution in intended error case
 * @scenario		Calls eom_get_output_resolution with invalid parameter
 */
int utc_eom_get_output_resolution_n2(void)
{
    int width;
    int height;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_resolution(10000, &width, &height);

    assert_eq(ret, EOM_ERROR_NO_SUCH_DEVICE);

    return 0;
}

/**
 * @testcase		utc_eom_get_output_physical_size_p
 * @since_tizen		2.4
 * @description		Gets the output devices's physical size
 * @scenario		Calls eom_get_output_physical_size with output id
 */
int utc_eom_get_output_physical_size_p(void)
{
    int phy_width;
    int phy_height;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_physical_size(getinfo_output_id, &phy_width, &phy_height);
    if (g_getinfo_no_device == true)
    {
        assert_eq(ret, EOM_ERROR_NO_SUCH_DEVICE);
    }
    else
    {
        assert_eq(ret, EOM_ERROR_NONE);
    }

    return 0;
}
/**
 * @testcase		utc_eom_get_output_physical_size_n1
 * @since_tizen		2.4
 * @description		Gets the output devices's physical size in intended error case
 * @scenario		Calls eom_get_output_physical_size with invalid parameter
 */
int utc_eom_get_output_physical_size_n1(void)
{
    int phy_width;
    int phy_height;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_physical_size(0, &phy_width, &phy_height);

    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}
/**
 * @testcase		utc_eom_get_output_physical_size_n2
 * @since_tizen		2.4
 * @description		Gets the output devices's physical size in intended error case
 * @scenario		Calls eom_get_output_physical_size with invalid parameter
 */
int utc_eom_get_output_physical_size_n2(void)
{
    int phy_width;
    int phy_height;
    int ret = EOM_ERROR_NONE;

    ret = eom_get_output_physical_size(10000, &phy_width, &phy_height);

    assert_eq(ret, EOM_ERROR_NO_SUCH_DEVICE);

    return 0;
}
