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

//& set: TbmSurfaceMap


/**
 * @function		utc_tbm_surface_map_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_tbm_surface_map_startup(void)
{
}

/**
 * @function		utc_tbm_surface_map_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_tbm_surface_map_cleanup(void)
{
}

/**
 * @testcase		utc_tbm_surface_map_p
 * @since_tizen		2.3
 * @description		Positive test case for mapping tbm surface.
 */
int utc_tbm_surface_map_p(void)
{
    tbm_surface_h surface = NULL;
    tbm_surface_info_s surface_info;
    int access[3] = {
        TBM_SURF_OPTION_READ,
        TBM_SURF_OPTION_READ,
        TBM_SURF_OPTION_READ|TBM_SURF_OPTION_READ,
    };
    tbm_format *formats = NULL;
    uint32_t format_num = 0;
    int i = 0;
    int ret = 0;

    ret = tbm_surface_query_formats (&formats, &format_num);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    for (i=0; i<3; i++) {
        surface = tbm_surface_create (128, 128, formats[0]);
        assert (surface);
        ret = tbm_surface_map (surface, access[i], &surface_info);
        assert_eq (ret, TBM_SURFACE_ERROR_NONE);

        tbm_surface_unmap (surface);

        tbm_surface_destroy (surface);
    }

    free (formats);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_map_n
 * @since_tizen		2.3
 * @description		Negative test case for mapping tbm surface.
 */
int utc_tbm_surface_map_n(void)
{
    tbm_surface_h surface = NULL;
    tbm_surface_info_s surface_info;
    int ret = 0;

    ret = tbm_surface_map (surface, TBM_SURF_OPTION_READ|TBM_SURF_OPTION_READ, &surface_info);
    assert_eq (ret, TBM_SURFACE_ERROR_INVALID_PARAMETER);

    tbm_surface_destroy (surface);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_unmap_p
 * @since_tizen		2.3
 * @description		Positive test case for unmapping tbm surface.
 */
int utc_tbm_surface_unmap_p(void)
{
    tbm_surface_h surface = NULL;
    tbm_surface_info_s surface_info;
    tbm_format *formats = NULL;
    uint32_t format_num = 0;
    int ret = 0;

    ret = tbm_surface_query_formats (&formats, &format_num);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    surface = tbm_surface_create (128, 128, formats[0]);
    assert (surface);

    ret = tbm_surface_map (surface, TBM_SURF_OPTION_READ|TBM_SURF_OPTION_READ, &surface_info);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    ret = tbm_surface_unmap (surface);
    assert_eq (ret, TBM_SURFACE_ERROR_NONE);

    tbm_surface_destroy (surface);
    free (formats);

    return 0;
}

/**
 * @testcase		utc_tbm_surface_unmap_n
 * @since_tizen		2.3
 * @description		Negative test case for unmapping tbm surface.
 */
int utc_tbm_surface_unmap_n(void)
{
    tbm_surface_h surface = NULL;
    int ret = 0;

    ret = tbm_surface_unmap (surface);

    assert_eq (ret, TBM_SURFACE_ERROR_INVALID_PARAMETER);

    tbm_surface_destroy (surface);

    return 0;
}
