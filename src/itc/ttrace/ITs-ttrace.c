//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-ttrace-common.h"

//& set: Ttrace

/** @addtogroup itc-ttrace
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_ttrace_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_ttrace_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	g_bTTraceCreation = true;

	return;
}


/**
 * @function 		ITs_ttrace_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_ttrace_cleanup(void)
{
	return;
}

/** @addtogroup itc-ttrace-testcases
*  @brief 		Integration testcases for module ttrace
*  @ingroup 	itc-ttrace
*  @{
*/

/**
 * @testcase 				ITc_trace_begin_end_p
 * @author            		SRID(abhishek1.g)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test trace_begin and trace_end
 * @scenario				Call trace_begin, trace_end
 * @apicovered				trace_begin, trace_end
 * @passcase				If trace_begin and trace_end returns TRACE_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test trace_begin and trace_end
int ITc_trace_begin_end_p(void)
{
	START_TEST;

	trace_begin(TRACECOMMAND);
	CHECK_TRACE_RESULT(TRACE_ERROR_NONE, "trace_begin");

	trace_end();
	CHECK_TRACE_RESULT(TRACE_ERROR_NONE, "trace_end");

	return 0;
}

/**
 * @testcase 				ITc_trace_async_begin_end_p
 * @author            		SRID(abhishek1.g)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test trace_async_begin and trace_async_end
 * @scenario				Call trace_async_begin, trace_async_end
 * @apicovered				trace_async_begin, trace_async_end
 * @passcase				If trace_async_begin and trace_async_end returns TRACE_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test trace_async_begin and trace_async_end
int ITc_trace_async_begin_end_p(void)
{
	START_TEST;

	trace_async_begin(1, TRACECOMMAND);
	CHECK_TRACE_RESULT(TRACE_ERROR_NONE, "trace_async_begin");

	trace_async_end(1, TRACECOMMAND);
	CHECK_TRACE_RESULT(TRACE_ERROR_NONE, "trace_async_end");

	return 0;
}

/**
 * @testcase 				ITc_trace_update_counter_p
 * @author            		SRID(abhishek1.g)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @since_tizen 			2.4
 * @description				To test trace_update_counter
 * @scenario				Call trace_update_counter
 * @apicovered				trace_update_counter
 * @passcase				If trace_update_counter returns TRACE_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test trace_update_counter
int ITc_trace_update_counter_p(void)
{
	START_TEST;

	trace_async_begin(1, TRACECOMMAND);
	CHECK_TRACE_RESULT(TRACE_ERROR_NONE, "trace_async_begin");

	trace_update_counter(2, TRACECOMMAND);
	CHECK_TRACE_RESULT(TRACE_ERROR_NONE, "trace_update_counter");

	trace_async_end(1, TRACECOMMAND);
	CHECK_TRACE_RESULT(TRACE_ERROR_NONE, "trace_async_end");

	return 0;
}

/** @} */
/** @} */