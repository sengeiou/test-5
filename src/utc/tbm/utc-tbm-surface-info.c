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
#include <tbm_surface.h>
#include <stdlib.h>
#include "assert.h"

//& set: TbmSurfaceInfo

/**
 * @function		utc_tbm_surface_info_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_tbm_surface_info_startup(void)
{
}


/**
 * @function		utc_tbm_surface_info_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_tbm_surface_info_cleanup(void)
{
}

/**
 * @testcase		utc_tbm_surface_get_info_p
 * @since_tizen		2.3
 * @description		Positive test case for getting tbm surface info.
 */
int utc_tbm_surface_get_info_p(void)
{
    tbm_surface_h surface = NULL;
    tbm_surface_info_s surface_info;
    tbm_format *formats = NULL;
    uint32_t format_num = 0;
    int ret = 0;

    ret = tbm_surface_query_formats (&formats, &format_num);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    surface = tbm_surface_create (128, 256, formats[0]);
    assert (surface);

    ret = tbm_surface_get_info (surface, &surface_info);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    tbm_surface_destroy (surface);
    free (formats);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_get_info_n
 * @since_tizen		2.3
 * @description		Negative test case for getting tbm surface info.
 */
int utc_tbm_surface_get_info_n(void)
{
    tbm_surface_h surface = NULL;
    tbm_surface_info_s surface_info;
    int ret = 0;

    ret = tbm_surface_get_info (surface, &surface_info);
    assert_eq (ret, TBM_SURFACE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_get_width_p
 * @since_tizen		2.3
 * @description		Positive test case for getting width of tbm surface.
 */
int utc_tbm_surface_get_width_p(void)
{
    tbm_surface_h surface = NULL;
    tbm_format *formats = NULL;
    uint32_t format_num = 0;
    int ret = 0;

    ret = tbm_surface_query_formats (&formats, &format_num);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    surface = tbm_surface_create (128, 256, formats[0]);
    assert (surface);

    ret = tbm_surface_get_width (surface);
    assert_eq (ret, 128);

    tbm_surface_destroy (surface);
    free (formats);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_get_width_n
 * @since_tizen		2.3
 * @description		Negative test case for getting width of tbm surface.
 */
int utc_tbm_surface_get_width_n(void)
{
    tbm_surface_h surface = NULL;
    int ret = 0;

    ret = tbm_surface_get_width (surface);
    assert_eq (ret, TBM_SURFACE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_get_height_p
 * @since_tizen		2.3
 * @description		Positive test case for getting height of tbm surface.
 */
int utc_tbm_surface_get_height_p(void)
{
    tbm_surface_h surface = NULL;
    tbm_format *formats = NULL;
    uint32_t format_num = 0;
    int ret = 0;

    ret = tbm_surface_query_formats (&formats, &format_num);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    surface = tbm_surface_create (128, 256, formats[0]);
    assert (surface);

    ret = tbm_surface_get_height (surface);
    assert_eq (ret, 256);

    tbm_surface_destroy (surface);
    free (formats);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_get_height_n
 * @since_tizen		2.3
 * @description		Negative test case for getting height of tbm surface.
 */
int utc_tbm_surface_get_height_n(void)
{
    tbm_surface_h surface = NULL;
    int ret = 0;

    ret = tbm_surface_get_height (surface);
    assert_eq (ret, TBM_SURFACE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_get_format_p
 * @since_tizen		2.3
 * @description		Positive test case for getting format of tbm surface.
 */
int utc_tbm_surface_get_format_p(void)
{
    tbm_surface_h surface = NULL;
    tbm_format *formats = NULL;
    uint32_t format_num = 0;
    int ret = 0;

    ret = tbm_surface_query_formats (&formats, &format_num);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    surface = tbm_surface_create (128, 128, formats[0]);
    assert (surface);

    ret = tbm_surface_get_format (surface);
    assert_eq (ret, formats[0]);

    tbm_surface_destroy (surface);
    free (formats);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_get_format_n
 * @since_tizen		2.3
 * @description		Negative test case for getting format of tbm surface.
 */
int utc_tbm_surface_get_format_n(void)
{
    tbm_surface_h surface = NULL;
    int ret = 0;

    ret = tbm_surface_get_format (surface);
    assert (!ret);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_query_formats_p
 * @since_tizen		2.3
 * @description		Positive test case for querying number and list of tbm format supported by the system.
 */
int utc_tbm_surface_query_formats_p(void)
{
    tbm_format *formats = NULL;
    uint32_t format_num = 0;
    int ret = 0;

    ret = tbm_surface_query_formats (&formats, &format_num);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);
    assert (formats);
    assert_gt (format_num, 0);

    free (formats);

    return 0;
}
