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
/**
 * @function		utc_eom_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_eom_startup(void)
{
}

/**
 * @function		utc_eom_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_eom_cleanup(void)
{
}


/**
 * @testcase		utc_eom_init_p
 * @since_tizen		2.4
 * @description		Initialization test
 * @scenario		Calls eom_init function
 */
int utc_eom_init_p(void)
{
    int ret = EOM_ERROR_NONE;

    ret = eom_init();
    assert_eq(ret, EOM_ERROR_NONE);

    eom_deinit();

    return 0;
}

/**
 * @testcase		utc_eom_deinit_p
 * @since_tizen		2.4
 * @description		Finalization test
 * @scenario		Calls eom_deinit function
 */
int utc_eom_deinit_p(void)
{
    int ret = EOM_ERROR_NONE;

    eom_deinit();
    assert_eq(ret, EOM_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_eom_get_eom_output_ids_p
 * @since_tizen		2.4
 * @description		Gets the output id structures
 * @scenario		Calls utc_eom_get_eom_output_ids_p
			Can get output_id structure and output id number
 */
int utc_eom_get_eom_output_ids_p(void)
{
    eom_output_id *output_ids = NULL;
    int id_cnt = 0;
    int ret = EOM_ERROR_NONE;

    eom_init();

    output_ids = eom_get_eom_output_ids(&id_cnt);
    ret = get_last_result();
    assert_eq(ret, EOM_ERROR_NONE);

    if (output_ids != NULL)
        free(output_ids);

    eom_deinit();

    return 0;
}
/**
 * @testcase		utc_eom_get_eom_output_ids_n
 * @since_tizen		2.4
 * @description		Gets the output id in intended error case
 * @scenario		Calls eom_get_eom_output_ids with invalid parameter
 */
int utc_eom_get_eom_output_ids_n(void)
{
    eom_output_id *output_ids = NULL;
    int ret = EOM_ERROR_NONE;

    eom_init();

    output_ids = eom_get_eom_output_ids(0);
    ret = get_last_result();
    assert_eq(ret, EOM_ERROR_INVALID_PARAMETER);

    if (output_ids != NULL)
        free(output_ids);

    eom_deinit();

    return 0;
}
