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
#include <Elementary.h>

//& set: Eom
static eom_output_id setinfo_output_id = 0;
static bool g_setinfo_no_device = false;
Evas_Object *g_external_window = NULL;

/**
 * @function		utc_eom_setinfo_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_eom_setinfo_startup(void)
{
    eom_output_id *output_ids = NULL;
    int id_cnt;

    elm_init(0, NULL);
    eom_init();

    setinfo_output_id = 0;
    g_setinfo_no_device = false;

    output_ids = eom_get_eom_output_ids(&id_cnt);
    if (id_cnt != 0)
    {
        setinfo_output_id = output_ids[0];
        free (output_ids);
    }

    if (setinfo_output_id == 0)
    {
        g_setinfo_no_device = true;
        setinfo_output_id = 999;
    }

    g_external_window = elm_win_add(NULL, "output_window", ELM_WIN_BASIC);
}

/**
 * @function		utc_eom_setinfo_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_eom_setinfo_cleanup(void)
{
    if (g_external_window)
        evas_object_del(g_external_window);
    eom_deinit();
    elm_shutdown();
}

/**
 * @testcase		utc_eom_set_output_attribute_p
 * @since_tizen		2.4
 * @description		Sets the attribute to output device
 * @scenario		Calls eom_set_output_attribute with output id
 */
int utc_eom_set_output_attribute_p(void)
{
    eom_output_attribute_e attribute = EOM_OUTPUT_ATTRIBUTE_NORMAL;
    int ret = EOM_ERROR_NONE;

    ret = eom_set_output_attribute(setinfo_output_id, attribute);
    if (g_setinfo_no_device == true)
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
 * @testcase		utc_eom_set_output_attribute_n
 * @since_tizen		2.4
 * @description		Sets the attribute to output device in intended error case
 * @scenario		Calls eom_set_output_attribute with invalid parameter
 */
int utc_eom_set_output_attribute_n(void)
{
    eom_output_attribute_e attribute = EOM_OUTPUT_ATTRIBUTE_NORMAL;
    int ret = EOM_ERROR_NONE;

    ret = eom_set_output_attribute(0, attribute);

    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_eom_set_output_window_p
 * @since_tizen		2.4
 * @description		Sets the window to output device to extended full size
 * @scenario		Calls eom_set_output_attribute for attribute setting
			Calls eom_set_output_window after set attribute
 */
int utc_eom_set_output_window_p(void)
{
    eom_output_attribute_e attribute = EOM_OUTPUT_ATTRIBUTE_NORMAL;
    int ret = EOM_ERROR_NONE;

    eom_set_output_attribute(setinfo_output_id, attribute);
    ret = eom_set_output_window(setinfo_output_id, g_external_window);
    if (g_setinfo_no_device == true)
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
 * @testcase		utc_eom_set_output_window_n
 * @since_tizen		2.4
 * @description		Sets the window to output device in intended error case
 * @scenario		Calls eom_set_output_window with invalid parameter
 */
int utc_eom_set_output_window_n(void)
{
    Evas_Object *external_window = NULL;
    eom_output_attribute_e attribute = EOM_OUTPUT_ATTRIBUTE_NORMAL;
    int ret = EOM_ERROR_NONE;

    eom_set_output_attribute(setinfo_output_id, attribute);
    ret = eom_set_output_window(setinfo_output_id, external_window);

    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    return 0;
}
