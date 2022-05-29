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
#include "ITs-dlog-common.h"

/** @addtogroup itc-dlog
*  @ingroup itc
*  @{
*/

//& set: Dlog

/**
* @function 		ITs_dlog_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_dlog_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Dlog_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bDlogCreation = true;
}

/**
* @function 		ITs_dlog_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_dlog_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Dlog_p\\n", __LINE__, API_NAMESPACE);
#endif
}


/** @addtogroup itc-dlog-testcases
*  @brief 		Integration testcases for module dlog
*  @ingroup 	itc-dlog
*  @{
*/

/**
* @testcase 			ITc_dlog_dlog_print_p
* @since_tizen			2.3
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Send a log
* @scenario				Send a dlog
* @apicovered			dlog_print				
* @passcase				When dlog_print is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test dlog_print
//& type: auto
int ITc_dlog_dlog_print_p(void)
{
	START_TEST;

	log_priority earrPriority[MAXENUMSIZE] = {0};
	int nTotalEnums = 0;
	int nEnumCount = 0;

	DLOG_INITIALIZE_LOGS_SINGLE_ENUM_FN(DlogGetPriorityListValue, earrPriority, nTotalEnums);
	for ( nEnumCount = 0; nEnumCount < nTotalEnums; nEnumCount++ )
	{
		int nRetVal = dlog_print(earrPriority[nEnumCount], "DLOG_TEST", "[Dlog_ITC] Dlog Test Message\n");
		if ( nRetVal < 0 )
		{
			FPRINTF("[Line : %d][%s] dlog_print failed for Enumerator %s\\n", __LINE__, API_NAMESPACE,  DlogGetPriorityListValue(earrPriority, &nEnumCount, GETENUM));
			return 1;
		}
	}
	return 0;
}

static int dlog_vprint_wrap_va_list(log_priority pri, const char *tag, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	int ret = dlog_vprint(pri, tag, fmt, ap);

	va_end(ap);
	return ret;
}

/**
* @testcase 			ITc_dlog_dlog_vprint_p
* @since_tizen			2.3
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Send a log using va_list
* @scenario				Send a dlog
* @apicovered			dlog_vprint				
* @passcase				When dlog_vprint is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
* 
*/
//& purpose: API to test dlog_vprint
//& type: auto
int ITc_dlog_dlog_vprint_p(void)
{
	START_TEST;
	int nRetVal = -1;
	log_priority earrPriority[MAXENUMSIZE] = {0};
	int nTotalEnums = 0;
	int nEnumCount = 0;

	DLOG_INITIALIZE_LOGS_SINGLE_ENUM_FN(DlogGetPriorityListValue, earrPriority, nTotalEnums);
	for ( nEnumCount = 0; nEnumCount < nTotalEnums; nEnumCount++ )
	{
		// Target API
		nRetVal = dlog_vprint_wrap_va_list(earrPriority[nEnumCount], "DLOG_TEST", "[Dlog_ITC] Dlog Test Message\n");
		if ( nRetVal < 0 )
		{
			FPRINTF("[Line : %d][%s] dlog_vprint failed for Enumerator %s\\n", __LINE__, API_NAMESPACE, DlogGetPriorityListValue(earrPriority, &nEnumCount, GETENUM));
			return 1;
		}
	}
	return 0;
}	
/** @} */
/** @} */