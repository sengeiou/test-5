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

iotcon_representation_h g_hRepr = NULL;
iotcon_attributes_h g_hAttributes = NULL;

//& set: Iotcon

/** @addtogroup itc-iotcon
*  @ingroup itc
*  @{
*/

/**
* @function 		IotconListIntCB
* @description	 	Callback Function
* @parameter		int pos, bool value, void *user_data
* @return 			NA
*/
bool IotconListIntCB(int pos, int value, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside IotconListIntCB callback\\n", __LINE__, API_NAMESPACE);
	if (user_data)
		++ (*((int *)user_data));

	g_bCheckCb = true;

	return IOTCON_FUNC_CONTINUE;

}

/**
* @function 		IotconListBoolCB
* @description	 	Callback Function
* @parameter		int pos, bool value, void *user_data
* @return 			NA
*/
bool IotconListBoolCB(int pos, bool value, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside IotconListBoolCB callback\\n", __LINE__, API_NAMESPACE);
	if (user_data)
		++ (*((int *)user_data));

	g_bCheckCb = true;

	return IOTCON_FUNC_CONTINUE;
}

/**
* @function 		IotconListDoubleCB
* @description	 	Callback Function
* @parameter		int pos, const double value, void *user_data
* @return 			NA
*/
bool IotconListDoubleCB(int pos, const double value, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside IotconListDoubleCB callback\\n", __LINE__, API_NAMESPACE);
	if (user_data)
		++ (*((int *)user_data));

	g_bCheckCb = true;
	return IOTCON_FUNC_CONTINUE;
}

/**
* @function 		IotconListStrCB
* @description	 	Callback Function
* @parameter		int pos, const char *value, void *user_data
* @return 			NA
*/
bool IotconListStrCB(int pos, const char *value, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside IotconListStrCB callback\\n", __LINE__, API_NAMESPACE);
	if (user_data)
		++ (*((int *)user_data));

	if(value == NULL)
	{
		FPRINTF("[Line : %d][%s] IotconListStrCB callback  value is NULL\\n", __LINE__, API_NAMESPACE);
		return IOTCON_FUNC_CONTINUE;
	}

	g_bCheckCb = true;

	return IOTCON_FUNC_CONTINUE;
}

/**
* @function 		IotconListListCB
* @description	 	Callback Function
* @parameter		int pos, iotcon_list_h value, void *user_data
* @return 			NA
*/
bool IotconListListCB(int pos, iotcon_list_h value, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside IotconListListCB callback\\n", __LINE__, API_NAMESPACE);
	if (user_data)
		++ (*((int *)user_data));

	if(value == NULL)
	{
		FPRINTF("[Line : %d][%s] Inside IotconListListCB callback , value is NULL\\n", __LINE__, API_NAMESPACE);
		return IOTCON_FUNC_CONTINUE;
	}

	g_bCheckCb = true;

	return IOTCON_FUNC_CONTINUE;
}

/**
* @function 		IotconListStateCB
* @description	 	Callback Function
* @parameter		int pos, iotcon_attributes_h value, void *user_data
* @return 			NA
*/
bool IotconListStateCB(int pos, iotcon_attributes_h value, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside IotconListStateCB callback\\n", __LINE__, API_NAMESPACE);
	if (user_data)
		++ (*((int *)user_data));

	if(value == NULL)
	{
		FPRINTF("[Line : %d][%s] IotconListStateCB callback fails as value is NULL \\n", __LINE__, API_NAMESPACE);
		return IOTCON_FUNC_CONTINUE;
	}

	g_bCheckCb = true;

	return IOTCON_FUNC_CONTINUE;
}

/**
* @function 		IotconListByteStrCB
* @description	 	Callback Function
* @parameter		int pos, iotcon_attributes_h value, void *user_data
* @return 			NA
*/
bool IotconListByteStrCB(int pos, const unsigned char *value, int len, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside IotconListByteStrCB callback\\n", __LINE__, API_NAMESPACE);
	if (user_data)
		++ (*((int *)user_data));

	if(value == NULL)
	{
		FPRINTF("[Line : %d][%s] IotconListByteStrCB callback fails as value is NULL \\n", __LINE__, API_NAMESPACE);
		return IOTCON_FUNC_CONTINUE;
	}

	g_bCheckCb = true;

	return IOTCON_FUNC_CONTINUE;
}
/**
 * @function 		ITs_iotcon_list_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_list_startup(void)
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

	nRet = iotcon_attributes_create(&g_hAttributes);
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] iotcon_attributes_create fail in startup \\n", __LINE__, API_NAMESPACE);
		iotcon_deinitialize();
		g_bIotconConnect = false;
		return;
	}
	if(g_hAttributes == NULL)
	{
		iotcon_deinitialize();
		g_bIotconConnect = false;
		FPRINTF("[Line : %d][%s] g_hAttributes is NULL\\n", __LINE__, API_NAMESPACE);
		return;
	}

	nRet = iotcon_representation_create(&g_hRepr);
	if ( nRet != IOTCON_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] iotcon_representation_create fail in startup \\n", __LINE__, API_NAMESPACE);
		iotcon_attributes_destroy(g_hAttributes);
		g_hAttributes = NULL;
		iotcon_deinitialize();
		g_bIotconConnect = false;
		return;
	}
	if(g_hRepr == NULL)
	{
		iotcon_attributes_destroy(g_hAttributes);
		iotcon_deinitialize();
		g_bIotconConnect = false;
		g_hAttributes = NULL;
		FPRINTF("[Line : %d][%s] g_hRepr is NULL\\n", __LINE__, API_NAMESPACE);
		return;
	}
}


/**
 * @function 		ITs_iotcon_list_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_list_cleanup(void)
{

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Iotcon_List_p\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_hRepr)
		iotcon_representation_destroy(g_hRepr);

	if (g_hAttributes)
		iotcon_attributes_destroy(g_hAttributes);

	if (g_bIotconConnect)
		iotcon_deinitialize();
}

/** @addtogroup itc-iotcon-testcases
*  @brief 		Integration testcases for module iotcon
*  @ingroup 	itc-iotcon
*  @{
*/

//& type: auto
//& purpose:  scenario to create and destroy iotcon list
/**
* @testcase 			ITc_iotcon_list_create_destroy_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to create and destroy iotcon list
* @scenario				create list \n
* 						destroy list
* @apicovered			iotcon_list_create, iotcon_list_destroy
* @passcase				if iotcon_list_create and iotcon_list_destroy passes
* @failcase				if iotcon_list_create or iotcon_list_destroy fails
* @precondition			iotcon should be connected
* @postcondition		iotcon should be disconnected
*/
int ITc_iotcon_list_create_destroy_p(void)
{
	START_TEST;

	int nRet = 0;
	iotcon_list_h hList = NULL;
	iotcon_type_e eSetIconType [] = { IOTCON_TYPE_INT, IOTCON_TYPE_BOOL,
	IOTCON_TYPE_DOUBLE, IOTCON_TYPE_STR, IOTCON_TYPE_NULL,	IOTCON_TYPE_LIST, IOTCON_TYPE_ATTRIBUTES};

	int nEnumSize = sizeof(eSetIconType) / sizeof(eSetIconType[0]);
	int nEnumCounter = 0;

	for (nEnumCounter = 0;nEnumCounter < nEnumSize;nEnumCounter++)
	{
		nRet = iotcon_list_create(eSetIconType[nEnumCounter],&hList);
		PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
		CHECK_HANDLE(hList,"iotcon_list_create");

		if(hList)
		{
			nRet = iotcon_list_destroy(hList);
			PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_destroy", IotConGetError(nRet));
			hList = NULL;
		}
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to add int value and get nth int value from the iotcon list
/**
* @testcase 			ITc_iotcon_list_add_get_nth_int_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add int value and get nth int value from the iotcon list
* @scenario				create list \n
*						iotcon_list_add_int \n
*						iotcon_list_get_nth_int \n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_add_int,iotcon_list_add_int,iotcon_list_get_nth_int
* @passcase				if iotcon_list_add_int and iotcon_list_get_nth_int passes
* @failcase				if iotcon_list_add_int or iotcon_list_get_nth_int fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_add_get_nth_int_p(void)
{
	START_TEST;

	iotcon_list_h hList = NULL;
	int nVal;

	int nRet = iotcon_list_create(IOTCON_TYPE_INT,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_add_int(hList, ASSIGNVAL1, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_int", IotConGetError(nRet), iotcon_list_destroy(hList));

	nRet =iotcon_list_add_int(hList, ASSIGNVAL2, VAL2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_int", IotConGetError(nRet), iotcon_list_destroy(hList));

	nRet =iotcon_list_add_int(hList, ASSIGNVAL3, VAL3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_int", IotConGetError(nRet), iotcon_list_destroy(hList));

	nRet = iotcon_list_get_nth_int(hList, VAL1, &nVal);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_int", IotConGetError(nRet), iotcon_list_destroy(hList));
	if(ASSIGNVAL1 != nVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	nRet = iotcon_list_get_nth_int(hList, VAL2, &nVal);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_int", IotConGetError(nRet), iotcon_list_destroy(hList));
	if(ASSIGNVAL2 != nVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	nRet = iotcon_list_get_nth_int(hList, VAL3, &nVal);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_int", IotConGetError(nRet), iotcon_list_destroy(hList));
	if(ASSIGNVAL3 != nVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& purpose: scenario to add bool value & get nth bool value from the iotcon list
/**
* @testcase 			ITc_iotcon_list_add_get_nth_bool_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			 scenario to add bool value & get nth bool value from the iotcon list
* @scenario				create list \n
*						iotcon_list_add_bool \n
*						iotcon_list_get_nth_bool\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_add_bool,iotcon_list_get_nth_bool
* @passcase				if iotcon_list_add_bool and iotcon_list_get_nth_bool passes
* @failcase				if iotcon_list_add_bool or iotcon_list_get_nth_bool fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_add_get_nth_bool_p(void)
{
	START_TEST;

	bool bVal;
	iotcon_list_h hList = NULL;
	bool bTrue = true;
	bool bFalse = false;

	int nRet = iotcon_list_create(IOTCON_TYPE_BOOL,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_add_bool(hList, bTrue, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_bool", IotConGetError(nRet), iotcon_list_destroy(hList));

	nRet =iotcon_list_add_bool(hList, bFalse, VAL2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_bool", IotConGetError(nRet), iotcon_list_destroy(hList));;

	nRet =iotcon_list_add_bool(hList, bTrue, VAL3);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_bool", IotConGetError(nRet));


	nRet = iotcon_list_get_nth_bool(hList, VAL1, &bVal);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_bool", IotConGetError(nRet), iotcon_list_destroy(hList));
	if(bTrue != bVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	nRet = iotcon_list_get_nth_bool(hList, VAL2, &bVal);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_bool", IotConGetError(nRet), iotcon_list_destroy(hList));
	if(bFalse != bVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	nRet = iotcon_list_get_nth_bool(hList, VAL3, &bVal);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_bool", IotConGetError(nRet), iotcon_list_destroy(hList));
	if(bTrue != bVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to add double value and get nth double value from the iotcon list
/**
* @testcase 			ITc_iotcon_list_add_get_nth_double_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add double value and get nth double value from the iotcon list
* @scenario				create list \n
*						iotcon_list_add_double \n
*						iotcon_list_get_nth_double\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_add_double,iotcon_list_get_nth_double
* @passcase				if iotcon_list_add_double and iotcon_list_get_nth_double passes
* @failcase				if iotcon_list_add_double or iotcon_list_get_nth_double fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_add_get_nth_double_p(void)
{
	START_TEST;

	double nGetVal = 0.0;
	iotcon_list_h hList = NULL;
	double nVal1 = 1.0 ,nVal2 = 2.0, nVal3 = 3.0;

	int nRet = iotcon_list_create(IOTCON_TYPE_DOUBLE,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_add_double(hList, nVal1, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_double", IotConGetError(nRet), iotcon_list_destroy(hList));

	nRet =iotcon_list_add_double(hList, nVal2, VAL2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_double", IotConGetError(nRet), iotcon_list_destroy(hList));

	nRet =iotcon_list_add_double(hList, nVal3, VAL3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_double", IotConGetError(nRet), iotcon_list_destroy(hList));

	nRet = iotcon_list_get_nth_double(hList, VAL1, &nGetVal);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_double", IotConGetError(nRet), iotcon_list_destroy(hList));
	if(nVal1 != nGetVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	nRet = iotcon_list_get_nth_double(hList, VAL2, &nGetVal);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_double", IotConGetError(nRet), iotcon_list_destroy(hList));
	if(nVal2 != nGetVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	nRet = iotcon_list_get_nth_double(hList, VAL3, &nGetVal);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_double", IotConGetError(nRet), iotcon_list_destroy(hList));
	if(nVal3 != nGetVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& type: auto
//& purpose: scenario to add str value and get nth str value from the iotcon list
/**
* @testcase 			ITc_iotcon_list_add_get_nth_str_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add str value and get nth str value from the iotcon list
* @scenario				create list \n
*						iotcon_list_add_str \n
*						iotcon_list_get_nth_str\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_get_nth_str,iotcon_list_add_str
* @passcase				if iotcon_list_add_str and iotcon_list_get_nth_str passes
* @failcase				if iotcon_list_add_str or iotcon_list_get_nth_str fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_add_get_nth_str_p(void)
{
	START_TEST;

	char *pszGetVal;
	iotcon_list_h hList = NULL;
	char *pszSetVal1 = "first";
	char *pszSetVal2 = "second";

	int nRet = iotcon_list_create(IOTCON_TYPE_STR,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_add_str(hList, pszSetVal1, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_str", IotConGetError(nRet), iotcon_list_destroy(hList));

	nRet =iotcon_list_add_str(hList, pszSetVal2, VAL2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_str", IotConGetError(nRet), iotcon_list_destroy(hList));

	nRet =iotcon_list_add_str(hList, pszSetVal1, VAL3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_str", IotConGetError(nRet), iotcon_list_destroy(hList));

	nRet = iotcon_list_get_nth_str(hList, VAL1, &pszGetVal);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_str", IotConGetError(nRet), iotcon_list_destroy(hList));
	if ( strcmp(pszGetVal,pszSetVal1) != 0 )
	{
		FPRINTF("[Line : %d][%s] iotcon_list_get_nth_str failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		iotcon_list_destroy(hList);
		return 1;
	}

	nRet = iotcon_list_get_nth_str(hList, VAL2, &pszGetVal);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_str", IotConGetError(nRet), iotcon_list_destroy(hList));
	if ( strcmp(pszGetVal,pszSetVal2) != 0 )
	{
		FPRINTF("[Line : %d][%s] iotcon_list_get_nth_str failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		iotcon_list_destroy(hList);
		return 1;
	}

	nRet = iotcon_list_get_nth_str(hList, VAL3, &pszGetVal);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_str", IotConGetError(nRet), iotcon_list_destroy(hList));
	if ( strcmp(pszGetVal,pszSetVal1) != 0 )
	{
		FPRINTF("[Line : %d][%s] iotcon_list_get_nth_str failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		iotcon_list_destroy(hList);
		return 1;
	}

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to add list value and get nth list value from the iotcon list
/**
* @testcase 			ITc_iotcon_list_add_get_nth_list_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add list value and get nth list value from the iotcon list
* @scenario				create list \n
*						iotcon_list_add_list \n
*						iotcon_list_get_nth_list\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_get_nth_list,iotcon_list_add_list,iotcon_list_destroy
* @passcase				if iotcon_list_add_list and iotcon_list_get_nth_list passes
* @failcase				if iotcon_list_add_list or iotcon_list_get_nth_list fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_add_get_nth_list_p(void)
{
	START_TEST;

	iotcon_list_h hList1 = NULL;
	iotcon_list_h hList2 = NULL;
	iotcon_list_h hList3 = NULL;

	int nRet = iotcon_list_create(IOTCON_TYPE_LIST,&hList1);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList1,"iotcon_list_create");

	nRet = iotcon_list_create(IOTCON_TYPE_INT,&hList2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet),iotcon_list_destroy(hList1));
	CHECK_HANDLE(hList2,"iotcon_list_create");

	nRet =iotcon_list_add_list(hList1, hList2, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_list", IotConGetError(nRet),iotcon_list_destroy(hList2); iotcon_list_destroy(hList1));

	nRet = iotcon_list_get_nth_list(hList1, VAL1, &hList3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_list", IotConGetError(nRet),iotcon_list_destroy(hList2); iotcon_list_destroy(hList1));

	if( hList3 == NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_list_get_nth_list failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		iotcon_list_destroy(hList1);
		iotcon_list_destroy(hList2);
		hList1 = NULL;
		hList2 = NULL;
		return 1;
	}

	if(hList1)
	{
		iotcon_list_destroy(hList1);
		hList1 = NULL;
	}
	if(hList2)
	{
		iotcon_list_destroy(hList2);
		hList2 = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to add state value and get nth state value from the iotcon list
/**
* @testcase 			ITc_iotcon_list_add_get_nth_attributes_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add state value and get nth state value from the iotcon list
* @scenario				create list \n
*						iotcon_list_add_attributes \n
*						iotcon_list_get_nth_attributes\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_get_nth_attributes,iotcon_list_add_attributes, iotcon_list_destroy
* @passcase				if iotcon_list_add_attributes and iotcon_list_get_nth_attributes passes
* @failcase				if iotcon_list_add_attributes or iotcon_list_get_nth_attributes fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_add_get_nth_attributes_p(void)
{
	START_TEST;

	iotcon_attributes_h hState = NULL;
	iotcon_list_h hList = NULL;

	int nRet = iotcon_list_create(IOTCON_TYPE_ATTRIBUTES,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_attributes_create(&hState);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet),iotcon_list_destroy(hList));
	CHECK_HANDLE(hState,"iotcon_attributes_create");

	nRet = iotcon_list_add_attributes(hList, hState, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_attributes", IotConGetError(nRet),iotcon_list_destroy(hList); iotcon_attributes_destroy(hState));

	nRet = iotcon_list_get_nth_attributes(hList, VAL1, &hState);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_attributes", IotConGetError(nRet),iotcon_list_destroy(hList); iotcon_attributes_destroy(hState));

	if( hState == NULL )
	{
		FPRINTF("[Line : %d][%s] iotcon_list_get_nth_attributes failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		iotcon_list_destroy(hList);
		return 1;
	}

	iotcon_attributes_destroy(hState);
	hState = NULL;

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to removes the value at the given position
/**
* @testcase 			ITc_iotcon_list_remove_nth_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to removes the value at the given position
* @scenario				create list and state \n
*						iotcon_list_add_attributes \n
*						iotcon_list_remove_nth\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_attributes_create,iotcon_list_add_attributes,iotcon_list_remove_nth,iotcon_attributes_destroy,iotcon_list_destroy
* @passcase				if iotcon_list_remove_nth passes
* @failcase				if iotcon_list_remove_nth fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_remove_nth_p(void)
{
    START_TEST;

    int i,nTotal =5;
    iotcon_list_h hList = NULL;

    int nRet = iotcon_list_create(IOTCON_TYPE_INT, &hList);
    PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
    CHECK_HANDLE(hList,"iotcon_list_create");

    for (i = 0; i < nTotal; i++)
    {
        nRet = iotcon_list_add_int(hList, i, -1);
        PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_attributes", IotConGetError(nRet),iotcon_list_destroy(hList));
    }

    for (i = nTotal-1; 0 <= i; i--) {
        nRet = iotcon_list_remove_nth(hList, i);
        PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_remove_nth", IotConGetError(nRet),iotcon_list_destroy(hList));
    }
    if(hList)
    {
        iotcon_list_destroy(hList);
        hList = NULL;
    }

    return 0;
}


//& type: auto
//& purpose:  scenario to gets the type of the list
/**
* @testcase 			ITc_iotcon_list_get_type_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to gets the type of the list
* @scenario				create list \n
*						iotcon_list_get_type\n
* 						destroy list\n
* @apicovered			iotcon_list_create,iotcon_list_get_type
* @passcase				if iotcon_list_get_type passes
* @failcase				if iotcon_list_get_type fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_get_type_p(void)
{
	START_TEST;

	iotcon_type_e eType;
	iotcon_list_h hList = NULL;

	int nRet = iotcon_list_create(IOTCON_TYPE_INT,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_get_type(hList, &eType);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_type", IotConGetError(nRet),iotcon_list_destroy(hList));
	PRINT_RESULT_CLEANUP(IOTCON_TYPE_INT, eType, "iotcon_list_get_type", IotConGetError(nRet),iotcon_list_destroy(hList));

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to gets the number of elements in a list
/**
* @testcase 			ITc_iotcon_list_get_length_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to gets the number of elements in a list
* @scenario				create list \n
*						iotcon_list_add_int \n
*						iotcon_list_get_length\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_add_int,iotcon_list_get_length
* @passcase				if iotcon_list_get_length passes
* @failcase				if iotcon_list_get_length fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_get_length_p(void)
{
	START_TEST;

	unsigned int nLength;
	iotcon_list_h hList = NULL;

	int nRet = iotcon_list_create(IOTCON_TYPE_INT,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet =iotcon_list_add_int(hList, ASSIGNVAL1, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_int", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet =iotcon_list_add_int(hList, ASSIGNVAL1, VAL2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_int", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet =iotcon_list_add_int(hList, ASSIGNVAL1, VAL3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_int", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet = iotcon_list_get_length(hList, &nLength);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_length", IotConGetError(nRet),iotcon_list_destroy(hList));
	if(3 != nLength)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to gets all integer values of the given list by invoking the callback function.
/**
* @testcase 			ITc_iotcon_list_foreach_int_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to gets all integer values of the given list by invoking the callback function.
* @scenario				create list \n
*						iotcon_list_add_int \n
*						iotcon_list_foreach_int\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_foreach_int,iotcon_list_add_int, iotcon_list_destroy
* @passcase				if iotcon_list_foreach_int passes
* @failcase				if iotcon_list_foreach_int fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_foreach_int_p(void)
{
	START_TEST;

	int nCount = 0;
	g_bCheckCb = false;

	iotcon_list_h hList = NULL;

	int nRet = iotcon_list_create(IOTCON_TYPE_INT,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_add_int(hList, ASSIGNVAL2, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_int", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet =iotcon_list_add_int(hList, ASSIGNVAL2, VAL2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_int", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet =iotcon_list_add_int(hList, ASSIGNVAL2, VAL3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_int", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet = iotcon_list_foreach_int(hList, IotconListIntCB, &nCount);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_foreach_int", IotConGetError(nRet),iotcon_list_destroy(hList));

	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	if(3 != nCount)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to gets all bool values of the given list by invoking the callback function.
/**
* @testcase 			ITc_iotcon_list_foreach_bool_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to gets all bool values of the given list by invoking the callback function.
* @scenario				create list \n
*						iotcon_list_add_bool \n
*						iotcon_list_foreach_bool\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_foreach_bool, iotcon_list_add_bool,iotcon_list_destroy
* @passcase				if iotcon_list_foreach_bool passes
* @failcase				if iotcon_list_foreach_bool fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_foreach_bool_p(void)
{
	START_TEST;

	int nCount = 0;
	g_bCheckCb = false;
	iotcon_list_h hList = NULL;
	bool bFalse = false;
	bool bTrue = true;

	int nRet = iotcon_list_create(IOTCON_TYPE_BOOL,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_add_bool(hList, bTrue, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_bool", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet =iotcon_list_add_bool(hList, bFalse, VAL2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_bool", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet =iotcon_list_add_bool(hList, bTrue, VAL3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_bool", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet = iotcon_list_foreach_bool(hList, IotconListBoolCB, &nCount);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_foreach_bool", IotConGetError(nRet),iotcon_list_destroy(hList));

	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	if(3 != nCount)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to gets all double values of the given list by invoking the callback function.
/**
* @testcase 			ITc_iotcon_list_foreach_double_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to gets all double values of the given list by invoking the callback function.
* @scenario				create list \n
*						iotcon_list_add_double \n
*						iotcon_list_foreach_double\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_foreach_double,iotcon_list_add_double, iotcon_list_destroy
* @passcase				if iotcon_list_foreach_double passes
* @failcase				if iotcon_list_foreach_double fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_foreach_double_p(void)
{
	START_TEST;

	int nCount = 0;
	g_bCheckCb = false;

	iotcon_list_h hList = NULL;
	double nVal = 3.0;

	int nRet = iotcon_list_create(IOTCON_TYPE_DOUBLE,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_add_double(hList, nVal, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_double", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet =iotcon_list_add_double(hList, nVal, VAL2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_double", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet =iotcon_list_add_double(hList, nVal, VAL3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_double", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet = iotcon_list_foreach_double(hList, IotconListDoubleCB, &nCount);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_foreach_double", IotConGetError(nRet),iotcon_list_destroy(hList));

	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	if(3 != nCount)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to gets all str values of the given list by invoking the callback function.
/**
* @testcase 			ITc_iotcon_list_foreach_str_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to gets all str values of the given list by invoking the callback function.
* @scenario				create list \n
*						iotcon_list_add_str \n
*						iotcon_list_foreach_str\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_foreach_str,iotcon_list_add_str, iotcon_list_destroy
* @passcase				if iotcon_list_foreach_str passes
* @failcase				if iotcon_list_foreach_str fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_foreach_str_p(void)
{
	START_TEST;

	int nCount = 0;
	g_bCheckCb = false;

	iotcon_list_h hList = NULL;

	int nRet = iotcon_list_create(IOTCON_TYPE_STR,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_add_str(hList, VALUE, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_str", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet =iotcon_list_add_str(hList, VALUE, VAL2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_str", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet =iotcon_list_add_str(hList, VALUE, VAL3);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_str", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet = iotcon_list_foreach_str(hList, IotconListStrCB, &nCount);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_foreach_str", IotConGetError(nRet),iotcon_list_destroy(hList));

	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	if(3 != nCount)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		return 1;
	}

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to gets all list values of the given list by invoking the callback function.
/**
* @testcase 			ITc_iotcon_list_foreach_list_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to gets all list values of the given list by invoking the callback function.
* @scenario				create list \n
*						iotcon_list_add_list \n
*						iotcon_list_foreach_list\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_foreach_list,iotcon_list_add_list, iotcon_list_destroy
* @passcase				if iotcon_list_foreach_list passes
* @failcase				if iotcon_list_foreach_list fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_foreach_list_p(void)
{
	START_TEST;

	int nCount = 0;
	iotcon_list_h hList1, hList2;
	g_bCheckCb = false;
	iotcon_list_h hList = NULL;

	int nRet = iotcon_list_create(IOTCON_TYPE_LIST,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_create(IOTCON_TYPE_INT,&hList1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet),iotcon_list_destroy(hList));
	CHECK_HANDLE(hList1,"iotcon_list_create");

	nRet = iotcon_list_create(IOTCON_TYPE_DOUBLE,&hList2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet),iotcon_list_destroy(hList1);iotcon_list_destroy(hList));
	CHECK_HANDLE(hList2,"iotcon_list_create");

	nRet =iotcon_list_add_list(hList, hList1, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_list", IotConGetError(nRet),iotcon_list_destroy(hList2);iotcon_list_destroy(hList1);iotcon_list_destroy(hList));

	nRet =iotcon_list_add_list(hList, hList2, VAL2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_list", IotConGetError(nRet),iotcon_list_destroy(hList2);iotcon_list_destroy(hList1);iotcon_list_destroy(hList));

	nRet = iotcon_list_foreach_list(hList, IotconListListCB, &nCount);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_foreach_list", IotConGetError(nRet),iotcon_list_destroy(hList2);iotcon_list_destroy(hList1);iotcon_list_destroy(hList));


	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList2);
		hList2 = NULL;
		iotcon_list_destroy(hList1);
		hList1 = NULL;
		iotcon_list_destroy(hList);
		hList = NULL;
		return 1;
	}

	if (2 != nCount)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList2);hList2 = NULL;
		iotcon_list_destroy(hList1);hList1 = NULL;
		iotcon_list_destroy(hList);
		hList = NULL;
		return 1;
	}

	iotcon_list_destroy(hList2);hList2 = NULL;
	iotcon_list_destroy(hList1);hList1 = NULL;

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to gets all state values of the given list by invoking the callback function.
/**
* @testcase 			ITc_iotcon_list_foreach_attributes_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to gets all state values of the given list by invoking the callback function.
* @scenario				create list and state\n
*						iotcon_list_add_attributes \n
*						iotcon_list_foreach_attributes\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_foreach_attributes,iotcon_list_add_attributes, iotcon_list_destroy
* @passcase				if iotcon_list_foreach_attributes passes
* @failcase				if iotcon_list_foreach_attributes fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_foreach_attributes_p(void)
{
	START_TEST;

	int nCount = 0;
	iotcon_attributes_h hState1, hState2;
	g_bCheckCb = false;

	iotcon_list_h hList = NULL;

	int nRet = iotcon_list_create(IOTCON_TYPE_ATTRIBUTES,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_attributes_create(&hState1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet),iotcon_list_destroy(hList));
	CHECK_HANDLE(hState1,"iotcon_attributes_create");

	nRet = iotcon_attributes_create(&hState2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet),iotcon_attributes_destroy(hState1);iotcon_list_destroy(hList));
	CHECK_HANDLE(hState2,"iotcon_attributes_create");

	nRet = iotcon_list_add_attributes(hList, hState1, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_attributes", IotConGetError(nRet),iotcon_attributes_destroy(hState2);iotcon_attributes_destroy(hState1);iotcon_list_destroy(hList));

	nRet = iotcon_list_add_attributes(hList, hState2, VAL2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_attributes", IotConGetError(nRet),iotcon_attributes_destroy(hState2);iotcon_attributes_destroy(hState1);iotcon_list_destroy(hList));

	nRet = iotcon_list_foreach_attributes(hList, IotconListStateCB, &nCount);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_foreach_attributes", IotConGetError(nRet),iotcon_attributes_destroy(hState2);iotcon_attributes_destroy(hState1);iotcon_list_destroy(hList));



	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		iotcon_attributes_destroy(hState2);
		hState2 = NULL;
		iotcon_attributes_destroy(hState1);
		hState1 = NULL;
		iotcon_list_destroy(hList);
		hList = NULL;
		return 1;
	}

	if (2 != nCount)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_attributes_destroy(hState2);hState2 = NULL;
		iotcon_attributes_destroy(hState1);hState1 = NULL;
		iotcon_list_destroy(hList);
		hList = NULL;
		return 1;
	}

	iotcon_attributes_destroy(hState2);
	hState2 = NULL;
	iotcon_attributes_destroy(hState1);
	hState1 = NULL;

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to gets all state values of the given list by invoking the callback function.
/**
* @testcase 			ITc_iotcon_list_add_byte_str_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to gets all state values of the given list by invoking the callback function.
* @scenario				create list and state\n
*						iotcon_list_add_attributes \n
*						iotcon_list_foreach_attributes\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_add_byte_str,iotcon_list_add_attributes, iotcon_list_destroy
* @passcase				if iotcon_list_add_byte_str passes
* @failcase				if iotcon_list_add_byte_str fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_add_byte_str_p(void)
{
	START_TEST;
	iotcon_list_h hList = NULL;
	unsigned char temp_byte_str[3] = {70, 71, 72};
	int nStrLen = 3;

	int nRet = iotcon_list_create(IOTCON_TYPE_BYTE_STR,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_add_byte_str(hList, temp_byte_str, nStrLen, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_byte_str", IotConGetError(nRet),iotcon_list_destroy(hList));

	iotcon_list_destroy(hList);
	hList = NULL;
	return 0;

}


//& type: auto
//& purpose:  scenario to gets all state values of the given list by invoking the callback function.
/**
* @testcase 			ITc_iotcon_list_get_nth_byte_str_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to gets all state values of the given list by invoking the callback function.
* @scenario				create list and state\n
*						iotcon_list_add_attributes \n
*						iotcon_list_get_nth_byte_str\n
* 						destroy list
* @apicovered			iotcon_list_create,iotcon_list_get_nth_byte_str,iotcon_list_add_attributes, iotcon_list_destroy
* @passcase				if iotcon_list_get_nth_byte_str passes
* @failcase				if iotcon_list_get_nth_byte_str fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_get_nth_byte_str_p(void)
{
	START_TEST;
	iotcon_list_h hList = NULL;
	unsigned char *val = NULL;
	int len ;
	unsigned char temp_byte_str[3] = {70, 71, 72};
	int nStrLen = 3;

	int nRet = iotcon_list_create(IOTCON_TYPE_BYTE_STR,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_add_byte_str(hList, temp_byte_str, nStrLen, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_byte_str", IotConGetError(nRet),iotcon_list_destroy(hList));

	nRet = iotcon_list_get_nth_byte_str(hList,VAL1, &val, &len);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_get_nth_byte_str", IotConGetError(nRet),iotcon_list_destroy(hList));

	if(val == NULL)
	{
		FPRINTF("[Line : %d][%s] ITc_iotcon_list_get_nth_byte_str_p failed as val or len is NULL : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		hList = NULL;
		return 1;
	}

	iotcon_list_destroy(hList);
	hList = NULL;
	return 0;
}


//& type: auto
//& purpose:  scenario to gets all state values of the given list by invoking the callback function.
/**
* @testcase 			ITc_iotcon_list_foreach_byte_str_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to gets all state values of the given list by invoking the callback function.
* @scenario				create list and state\n
*						iotcon_list_add_attributes \n
*						ITc_iotcon_list_foreach_byte_str_p\n
* 						destroy list
* @apicovered			iotcon_list_create,ITc_iotcon_list_foreach_byte_str_p,iotcon_list_add_attributes, iotcon_list_destroy
* @passcase				if ITc_iotcon_list_foreach_byte_str_p passes
* @failcase				if ITc_iotcon_list_foreach_byte_str_p fails
* @precondition			iotcon should be connected & create list
* @postcondition		iotcon should be disconnected & destroy list
*/
int ITc_iotcon_list_foreach_byte_str_p(void)
{
	START_TEST;
	iotcon_list_h hList = NULL;
	unsigned char temp_byte_str[3] = {70, 71, 72};
	int count =0;
	int nStrLen = 3;

	int nRet = iotcon_list_create(IOTCON_TYPE_BYTE_STR,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_list_add_byte_str(hList, temp_byte_str, nStrLen, VAL1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_add_byte_str", IotConGetError(nRet),iotcon_list_destroy(hList));

	g_bCheckCb =false;
	nRet = iotcon_list_foreach_byte_str( hList,IotconListByteStrCB,&count);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_list_foreach_byte_str", IotConGetError(nRet),iotcon_list_destroy(hList));

	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback IotconListByteStrCB not invoked : \\n", __LINE__, API_NAMESPACE );
		iotcon_list_destroy(hList);
		hList = NULL;
		return 1;
	}

	iotcon_list_destroy(hList);
	hList = NULL;
	return 0;
}


/** @} */
/** @} */
