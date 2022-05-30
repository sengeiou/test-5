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
#include <dlog.h>

//& set: dlog-print

#define LOG_BUF_SIZE 1024

static char *fmt = "dlog test message for tct-mgr\n";

/**
 * @testcase		utc_SystemFW_dlog_print_p
 * @since_tizen		2.3
 * @description		Positive test case of __dlog_print()
 */
int utc_SystemFW_dlog_print_p(void)
{
    int r = 0;

    r = dlog_print(DLOG_INFO, "DLOG_TEST", fmt);

    assert_gt(r , 0);

    return 0;
}

/**
 * @testcase		utc_SystemFW_dlog_print_n
 * @since_tizen		2.3
 * @description		Negative test case of ug_init __dlog_print()
 */
int utc_SystemFW_dlog_print_n(void)
{
    int r = 0;

    r = dlog_print(-1, NULL, NULL);

    assert_lt(r, 1);

    return 0;
}
