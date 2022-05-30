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
#include "ITs-iotcon-common.h"

//& set: Iotcon

/** @addtogroup itc-iotcon
*  @ingroup itc
*  @{
*/

iotcon_options_h g_hOptions = NULL;
/**
* @function 		IotconOptionsForeachCB
* @description	 	Callback Function
* @parameter		unsigned short id, const char *data, void *user_data
* @return 			NA
*/
static bool IotconOptionsForeachCB(unsigned short id, const char *data, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside IotconOptionsForeachCB callback\\n", __LINE__, API_NAMESPACE);
	if (user_data)
		++ (*((int *)user_data));

	if(data== NULL)
	{
		FPRINTF("[Line : %d][%s] IotconOptionsForeachCB callback, data is NULL\\n", __LINE__, API_NAMESPACE);
		return IOTCON_FUNC_CONTINUE;
	}

	g_bCheckCb = true;

	return IOTCON_FUNC_CONTINUE;
}


/**
 * @function 		ITs_iotcon_options_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_options_startup(void)
{
	struct stat stBuff;
	char *svr_db_path;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bIotconConnect = true;
	g_bFeatureUnsupported = false;

	ic_get_svr_db_path(&svr_db_path);
   int nRet = iotcon_initialize(svr_db_path);
	free(svr_db_path);

	if ( !TCTCheckSystemInfoFeatureSupported(IOTCON_FEATURE, API_NAMESPACE) )
	{

		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] iotcon_initialize API call returned mismatch %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			g_bIotconConnect = false;
		}
		else
		{
			FPRINTF("[Line : %d][%s] iotcon_initialize API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			g_bFeatureUnsupported = true;
		}
		return;
	}

	if ( nRet != IOTCON_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] iotcon_initialize failed API return %s error \\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
		g_bIotconConnect = false;
		return;
	}

	nRet = iotcon_options_create(&g_hOptions);
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] iotcon_options_create fail in startup \\n", __LINE__, API_NAMESPACE);
		iotcon_deinitialize();
		g_bIotconConnect = false;
		return;
	}
	if(g_hOptions == NULL)
	{
		FPRINTF("[Line : %d][%s] g_hOptions is NULL\\n", __LINE__, API_NAMESPACE);
		iotcon_deinitialize();
		g_bIotconConnect = false;
		return;
	}
}


/**
 * @function 		ITs_iotcon_options_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_options_cleanup(void)
{

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Iotcon_Options_p\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_hOptions)
		iotcon_options_destroy(g_hOptions);

	if ( g_bIotconConnect )
		iotcon_deinitialize();

	return;
}

/** @addtogroup itc-iotcon-testcases
*  @brief 		Integration testcases for module iotcon
*  @ingroup 	itc-iotcon
*  @{
*/

//& type: auto
//& purpose:  scenario to create & destroy options
/**
* @testcase 			ITc_iotcon_options_create_destroy_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to create & destroy options
* @scenario				create options \n
* 						destroy options
* @apicovered			iotcon_options_create, iotcon_options_destroy
* @passcase				if iotcon_options_create and iotcon_options_destroy passes
* @failcase				if iotcon_options_create or iotcon_options_destroy fails
* @precondition			iotcon should be connected
* @postcondition		iotcon should be disconnected
*/
int ITc_iotcon_options_create_destroy_p(void)
{
	START_TEST;

	iotcon_options_h hOptions = NULL;

	int nRet = iotcon_options_create(&hOptions);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_options_create", IotConGetError(nRet));
	CHECK_HANDLE(hOptions,"iotcon_options_create");

	nRet = iotcon_options_destroy(hOptions);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_options_destroy", IotConGetError(nRet));
	hOptions = NULL;

    return 0;
}

//& type: auto
//& purpose:  scenario to add and remove options
/**
* @testcase 			ITc_iotcon_options_add_remove_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add and remove options
* @scenario				create options \n
*						add options \n
* 						remove  options\n
* @apicovered			iotcon_options_create,iotcon_options_add, iotcon_options_remove
* @passcase				if iotcon_options_add and iotcon_options_remove passes
* @failcase				if iotcon_options_add or iotcon_options_remove fails
* @precondition			iotcon should be connected
* @postcondition		iotcon should be disconnected
*/
int ITc_iotcon_options_add_remove_p(void)
{
	START_TEST;

	int nRet = iotcon_options_add(g_hOptions, ICL_OPTIONID_MIN, VALUE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_options_add", IotConGetError(nRet),iotcon_options_destroy(g_hOptions));

	nRet = iotcon_options_remove(g_hOptions, ICL_OPTIONID_MIN);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_options_remove", IotConGetError(nRet),iotcon_options_destroy(g_hOptions));

    return 0;
}

//& type: auto
//& purpose:  scenario to looks up data at the given id from the options.
/**
* @testcase 			ITc_iotcon_options_lookup_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to looks up data at the given id from the options.
* @scenario				option create and add \n
* 						option lookup \n
* @apicovered			iotcon_options_lookup
* @passcase				if iotcon_options_lookup passes
* @failcase				if iotcon_options_lookup fails
* @precondition			iotcon should be connected
* @postcondition		iotcon should be disconnected
*/
int ITc_iotcon_options_lookup_p(void)
{
	START_TEST;

	char *pszGetData;

	int nRet = iotcon_options_add(g_hOptions, ICL_OPTIONID_MIN, VALUE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_options_add", IotConGetError(nRet),iotcon_options_destroy(g_hOptions));

	nRet = iotcon_options_lookup(g_hOptions, ICL_OPTIONID_MIN, &pszGetData);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_options_lookup", IotConGetError(nRet),iotcon_options_destroy(g_hOptions));

	if (0 != strcmp(pszGetData, VALUE))
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_options_destroy(g_hOptions);
		return 1;
	}

	nRet = iotcon_options_remove(g_hOptions, ICL_OPTIONID_MIN);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_options_remove", IotConGetError(nRet));

    return 0;
}

//& type: auto
//& purpose:  scenario to get all datas of the options by invoking the callback function.
/**
* @testcase 			ITc_iotcon_options_foreach_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get all datas of the options by invoking the callback function.
* @scenario				option create and add  \n
* 						iotcon_options_foreach
* @apicovered			iotcon_options_foreach
* @passcase				if iotcon_options_foreach passes
* @failcase				if iotcon_options_foreach fails
* @precondition			iotcon should be connected
* @postcondition		iotcon should be disconnected
*/
int ITc_iotcon_options_foreach_p(void)
{
	START_TEST;

	int nCount =0;
	g_bCheckCb = false;
	char *pszSetData1 = "data1";
	char *pszSetData2 = "data2";

	int nRet = iotcon_options_add(g_hOptions, ICL_OPTIONID_MIN, pszSetData1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_options_add", IotConGetError(nRet),iotcon_options_destroy(g_hOptions));

	nRet = iotcon_options_add(g_hOptions, ICL_OPTIONID_MIN + 1, pszSetData2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_options_add", IotConGetError(nRet),iotcon_options_destroy(g_hOptions));


	nRet = iotcon_options_foreach(g_hOptions, IotconOptionsForeachCB, &nCount);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_options_foreach", IotConGetError(nRet),iotcon_options_destroy(g_hOptions));

	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		iotcon_options_destroy(g_hOptions);
		return 1;
	}
	if ( nCount != 2 )
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_options_destroy(g_hOptions);
		return 1;
	}

	nRet = iotcon_options_remove(g_hOptions, ICL_OPTIONID_MIN);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_options_remove", IotConGetError(nRet));

	nRet = iotcon_options_remove(g_hOptions, ICL_OPTIONID_MIN + 1);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_options_remove", IotConGetError(nRet));

    return 0;
}



/** @} */
/** @} */
