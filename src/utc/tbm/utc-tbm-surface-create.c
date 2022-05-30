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

//& set: TbmSurfaceCreate

/**
 * @function		utc_tbm_surface_create_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_tbm_surface_create_startup(void)
{
}


/**
 * @function		utc_tbm_surface_create_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_tbm_surface_create_cleanup(void)
{
}

/**
 * @testcase		utc_tbm_surface_create_p
 * @since_tizen		2.3
 * @description		Positive test case for creating tbm surface.
 */
int utc_tbm_surface_create_p(void)
{
    tbm_surface_h surface = NULL;
    tbm_format *formats = NULL;
    uint32_t format_num = 0;
    int ret = 0;
    int i = 0;

    ret = tbm_surface_query_formats (&formats, &format_num);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    for ( i = 0 ; i < format_num ; i++)
    {
        surface = tbm_surface_create (128, 128, formats[i]);
        assert (surface);

        tbm_surface_destroy (surface);
    }

    free (formats);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_create_n
 * @since_tizen		2.3
 * @description		Negative test case for creating tbm surface.
 */
int utc_tbm_surface_create_n(void)
{
    tbm_surface_h surface = NULL;
    tbm_format *formats = NULL;
    uint32_t format_num = 0;
    int ret = 0;

    ret = tbm_surface_query_formats (&formats, &format_num);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    surface = tbm_surface_create (-1, 128, formats[0]);
    assert (!surface);

    tbm_surface_destroy (surface);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case for destroying tbm surface.
 */
int utc_tbm_surface_destroy_p(void)
{
    tbm_surface_h surface = NULL;
    tbm_format *formats = NULL;
    uint32_t format_num = 0;
    int ret = 0;

    ret = tbm_surface_query_formats (&formats, &format_num);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    surface = tbm_surface_create (128, 128, formats[0]);
    assert (surface);

    ret = tbm_surface_destroy (surface);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    free (formats);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case for destroying tbm surface.
 */
int utc_tbm_surface_destroy_n(void)
{
    tbm_surface_h surface = NULL;
    int ret = 0;

    ret = tbm_surface_destroy (surface);

    assert_eq (ret, TBM_SURFACE_ERROR_INVALID_PARAMETER);

    return 0;
}
