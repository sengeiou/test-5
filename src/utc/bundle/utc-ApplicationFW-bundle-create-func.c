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
#include <bundle.h>

//& set: BundleCreateFunc

/**
 * @testcase		utc_ApplicationFW_bundle_create_p
 * @since_tizen		2.3
 * @description		Create a bundle object
 */
int utc_ApplicationFW_bundle_create_p(void)
{
    bundle *b = NULL;

    b = bundle_create();
    assert_neq(b, NULL);

    /* If assert above passed than bundle object has been created
     * and have to be removed. */
    bundle_free(b);

    return 0;
}
