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
#include <media_key.h>

//& set: MediaKeyReserve

/**
 * @function		utc_media_key_reserve_func_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_key_reserve_func_cleanup(void)
{
    media_key_release();
}

static void _event_cb(media_key_e key, media_key_event_e status, void* user_data)
{
}

/**
 * @testcase		utc_media_key_reserve_p
 * @since_tizen		2.3
 * @description		Registers a change event callback for all media keys
 * @scenario		Calls media_key_reserve()
 */
int utc_media_key_reserve_p(void)
{
    int r = media_key_reserve(_event_cb, NULL);
    assert_eq(r, MEDIA_KEY_ERROR_NONE);
    return 0;
}

/**
 * @testcase		utc_media_key_reserve_n
 * @since_tizen		2.3
 * @description		Registers a change event callback for all media keys in intended error case
 * @scenario		Calls media_key_reserve() with invalid parameter
 */
int utc_media_key_reserve_n(void)
{
    int r = media_key_reserve(NULL, NULL);
    assert_eq(r, MEDIA_KEY_ERROR_INVALID_PARAMETER);
    return 0;
}
