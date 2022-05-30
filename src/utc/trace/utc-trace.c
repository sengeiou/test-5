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
#include <trace.h>

//& set: Trace

static char *fmt = "test messages";


/**
 * @function		utc_trace_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_trace_startup(void)
{
	system("atrace --async_start app");
}

/**
 * @function		utc_trace_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_trace_cleanup(void)
{
	system("atrace --async_stop");
}



/**
 * @testcase		utc_trace_begin_p
 * @since_tizen		2.3
 * @description		
 */
int utc_trace_begin_p(void)
{
	int ret;

	trace_begin(fmt);

	ret = get_last_result();

	assert_neq(ret,TRACE_ERROR_IO_ERROR);

	return 0;
}

/**
 * @testcase		utc_trace_end_p
 * @since_tizen		2.3
 * @description		
 */
int utc_trace_end_p(void)
{
	int ret;

	trace_end();

	ret = get_last_result();

	assert_neq(ret,TRACE_ERROR_IO_ERROR);

	return 0;
}

/**
 * @testcase		utc_trace_async_begin_p
 * @since_tizen		2.3
 * @description		
 */
int utc_trace_async_begin_p(void)
{
	int ret;

	trace_async_begin(1, fmt);

	ret = get_last_result();

	assert_neq(ret,TRACE_ERROR_IO_ERROR);

	return 0;
}

/**
 * @testcase		utc_trace_async_end_p
 * @since_tizen		2.3
 * @description		
 */
int utc_trace_async_end_p(void)
{
	int ret;

	trace_async_end(1, fmt);

	ret = get_last_result();

	assert_neq(ret,TRACE_ERROR_IO_ERROR);

	return 0;
}

/**
 * @testcase		utc_trace_update_counter_p
 * @since_tizen		2.3
 * @description		
 */
int utc_trace_update_counter_p(void)
{
	int ret;

	trace_update_counter(1, fmt);

	ret = get_last_result();

	assert_neq(ret,TRACE_ERROR_IO_ERROR);

	return 0;
}
