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
#include <stdarg.h>
#include <dlog.h>

//& set: dlog-vprint

#define LOG_BUF_SIZE 1024

static int dlog_vprint_wrap_va_list(log_priority pri, const char *tag, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    int ret = dlog_vprint(pri, tag, fmt, ap);

    va_end(ap);
    return ret;
}

/**
 * @testcase		utc_SystemFW_dlog_vprint_p
 * @since_tizen		2.3
 * @description		Positive test case of __dlog_vprint()
 */
int utc_SystemFW_dlog_vprint_p(void)
{
    int ret = 0;
    char buf[LOG_BUF_SIZE] = "dlog test message for tct-mgr\n";

    ret = dlog_vprint_wrap_va_list(DLOG_INFO, "DLOG_TEST", buf);

    assert_gt(ret, 0);

    return 0;
}

/**
 * @testcase		utc_SystemFW_dlog_vprint_n
 * @since_tizen		2.3
 * @description		Negative test case of ug_init __dlog_vprint()
 */
int utc_SystemFW_dlog_vprint_n(void)
{
    int ret = 0;

    ret = dlog_vprint_wrap_va_list(-1, NULL, NULL);

    assert_lt(ret, 1);

    return 0;
}
