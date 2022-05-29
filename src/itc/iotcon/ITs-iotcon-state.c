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

static iotcon_attributes_h g_hAttributes;
static iotcon_representation_h g_hRepr;

/**
* @function 		IotconStateCB
* @description	 	Callback Function
* @parameter		iotcon_attributes_h hAttributes, const char *key, void *user_data
* @return 			NA
*/
bool IotconStateCB(iotcon_attributes_h hAttributes, const char *key, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside IotconStateCB callback\\n", __LINE__, API_NAMESPACE);

	if((hAttributes == NULL) || (key == NULL))
	{
		FPRINTF("[Line : %d][%s] Inside IotconStateCB fails as input values are NULL \\n", __LINE__, API_NAMESPACE);
	}
	g_bCheckCb = true;

	return IOTCON_FUNC_CONTINUE;
}

/**
 * @function 		ITs_iotcon_attributes_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_attributes_startup(void)
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
	if (IOTCON_ERROR_NONE != nRet)
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
	if (IOTCON_ERROR_NONE != nRet)
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
 * @function 		ITs_iotcon_attributes_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_attributes_cleanup(void)
{

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Iotcon_State_p\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_hRepr)
		iotcon_representation_destroy(g_hRepr);

	if (g_hAttributes)
		iotcon_attributes_destroy(g_hAttributes);

	if (g_bIotconConnect)
		iotcon_deinitialize();

	return;
}

/** @addtogroup itc-iotcon-testcases
*  @brief 		Integration testcases for module iotcon
*  @ingroup 	itc-iotcon
*  @{
*/

//& type: auto
//& purpose:  scenario to create and destroy hAttributes
/**
* @testcase 			ITc_iotcon_attributes_create_destroy_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to create and destroy hAttributes
* @scenario				iotcon_attributes_create \n
*						iotcon_attributes_destroy
* @apicovered			iotcon_attributes_create,iotcon_attributes_destroy
* @passcase				if iotcon_attributes_create and iotcon_attributes_destroy  passes
* @failcase				if iotcon_attributes_create or iotcon_attributes_destroy fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_create_destroy_p(void)
{
	START_TEST;

	iotcon_attributes_h hState = NULL;

	int nRet = iotcon_attributes_create(&hState);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet));
	CHECK_HANDLE(hState,"iotcon_attributes_create");

	nRet = iotcon_attributes_destroy(hState);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_destroy", IotConGetError(nRet));
	
	hState = NULL;

    return 0;
}

//& type: auto
//& purpose:  scenario to clone hAttributes
/**
* @testcase 			ITc_iotcon_attributes_clone_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to clone hAttributes
* @scenario				iotcon_attributes_clone \n
* @apicovered			iotcon_attributes_clone
* @passcase				if iotcon_attributes_clone passes
* @failcase				if iotcon_attributes_clone fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_clone_p(void)
{
	START_TEST;

	iotcon_attributes_h hState = NULL;

	int nRet = iotcon_attributes_clone(g_hAttributes, &hState);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_clone", IotConGetError(nRet));
	CHECK_HANDLE(hState,"iotcon_attributes_create");

	iotcon_attributes_destroy(hState);
	hState = NULL;

	return 0;
}

 //& type: auto
//& purpose:  scenario to add and get int values of hAttributes
/**
* @testcase 			ITc_iotcon_attributes_add_get_int_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add and get int values of hAttributes
* @scenario				iotcon_attributes_add_int \n
*						iotcon_attributes_get_int
* @apicovered			iotcon_attributes_add_int , iotcon_attributes_get_int
* @passcase				if iotcon_attributes_add_int and iotcon_attributes_get_int passes
* @failcase				if iotcon_attributes_add_int or iotcon_attributes_get_int fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_add_get_int_p(void)
{
	START_TEST;

	int nSetIntVal = 10;
	int nGetIntVal;

	int nRet = iotcon_attributes_add_int(g_hAttributes, KEY, nSetIntVal);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_int", IotConGetError(nRet));

	nRet = iotcon_attributes_get_int(g_hAttributes, KEY, &nGetIntVal);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_get_int", IotConGetError(nRet));
	if(nGetIntVal != nSetIntVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE );
		return 1;
	}
	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to add and get bool values of hAttributes
/**
* @testcase 			ITc_iotcon_attributes_add_get_bool_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add and get bool values of hAttributes
* @scenario				iotcon_attributes_add_bool \n
*						iotcon_attributes_get_bool
* @apicovered			iotcon_attributes_add_bool, iotcon_attributes_get_bool
* @passcase				if iotcon_attributes_add_bool and iotcon_attributes_get_bool passes
* @failcase				if iotcon_attributes_add_bool or iotcon_attributes_get_bool fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_add_get_bool_p(void)
{
	START_TEST;

	bool bSetBoolVal = true;
	bool bGetBoolVal;

	int nRet = iotcon_attributes_add_bool(g_hAttributes, KEY, bSetBoolVal);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_bool", IotConGetError(nRet));

	nRet = iotcon_attributes_get_bool(g_hAttributes, KEY, &bGetBoolVal);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_get_bool", IotConGetError(nRet));
	if(bGetBoolVal != bSetBoolVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE );
		return 1;
	}

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to add and get double values of hAttributes
/**
* @testcase 			ITc_iotcon_attributes_add_get_double_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add and get double values of hAttributes
* @scenario				iotcon_attributes_add_double \n
*						iotcon_attributes_get_double
* @apicovered			iotcon_attributes_add_double ,iotcon_attributes_get_double
* @passcase				if iotcon_attributes_add_double and iotcon_attributes_get_double passes
* @failcase				if iotcon_attributes_add_double or iotcon_attributes_get_double fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_add_get_double_p(void)
{
	START_TEST;

	double nSetdoubleVal = 3.4;
	double nGetdoubleVal;

	int nRet = iotcon_attributes_add_double(g_hAttributes, KEY, nSetdoubleVal);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_double", IotConGetError(nRet));

	nRet = iotcon_attributes_get_double(g_hAttributes, KEY, &nGetdoubleVal);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_get_double", IotConGetError(nRet));
	if(nSetdoubleVal != nGetdoubleVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE );
		return 1;
	}

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to add and get str values of hAttributes
/**
* @testcase 			ITc_iotcon_attributes_add_get_str_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add and get str values of hAttributes
* @scenario				iotcon_attributes_add_str \n
*						iotcon_attributes_get_str
* @apicovered			iotcon_attributes_add_str ,iotcon_attributes_get_str
* @passcase				if iotcon_attributes_add_str and iotcon_attributes_get_str passes
* @failcase				if iotcon_attributes_add_str or iotcon_attributes_get_str fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_add_get_str_p(void)
{
	START_TEST;

	char *GetValue;

	int nRet = iotcon_attributes_add_str(g_hAttributes, KEY, VALUE);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_str", IotConGetError(nRet));

	nRet = iotcon_attributes_get_str(g_hAttributes, KEY, &GetValue);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_get_str", IotConGetError(nRet));
	if(0 != strcmp(VALUE, GetValue))
	{
		FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE );
		return 1;
	}

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	return 0;

}

//& type: auto
//& purpose:  scenario to add and get list values of hAttributes
/**
* @testcase 			ITc_iotcon_attributes_add_get_list_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add and get list values of hAttributes
* @scenario				iotcon_list_create \n
*						iotcon_attributes_add_list \n
*						iotcon_attributes_get_list
* @apicovered			iotcon_attributes_add_list, iotcon_attributes_add_list ,iotcon_attributes_get_list
* @passcase				if iotcon_attributes_add_list and iotcon_attributes_get_list passes
* @failcase				if iotcon_attributes_add_list or iotcon_attributes_get_list fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_add_get_list_p(void)
{
	START_TEST;

	iotcon_list_h hList;

	int nRet = iotcon_list_create(IOTCON_TYPE_INT,&hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_list_create", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_list_create");

	nRet = iotcon_attributes_add_list(g_hAttributes, KEY, hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_list", IotConGetError(nRet));

	nRet = iotcon_attributes_get_list(g_hAttributes, KEY, &hList);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_get_list", IotConGetError(nRet));
	CHECK_HANDLE(hList,"iotcon_attributes_get_list");

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	if(hList)
	{
		iotcon_list_destroy(hList);
		hList = NULL;
	}

	return 0;
}

//& type: auto
//& purpose:  scenario to add and get hAttributes values of hAttributes
/**
* @testcase 			ITc_iotcon_attributes_add_get_attributes_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to clone hAttributes
* @scenario				iotcon_attributes_create \n
*						iotcon_attributes_add_attributes \n
*						iotcon_attributes_get_attributes
* @apicovered			iotcon_attributes_create,iotcon_attributes_add_attributes , iotcon_attributes_get_attributes,iotcon_attributes_destroy
* @passcase				if iotcon_attributes_add_attributes and iotcon_attributes_get_attributes passes
* @failcase				if iotcon_attributes_add_attributes or iotcon_attributes_get_attributes fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_add_get_attributes_p(void)
{
	START_TEST;

	iotcon_attributes_h hState1, hState2;

	int nRet = iotcon_attributes_create(&hState1);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet));
	CHECK_HANDLE(hState1,"iotcon_attributes_create");

	nRet = iotcon_attributes_add_attributes(g_hAttributes, KEY, hState1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_attributes", IotConGetError(nRet),iotcon_attributes_destroy(hState1));

	iotcon_attributes_destroy(hState1);

	nRet = iotcon_attributes_get_attributes(g_hAttributes, KEY, &hState2);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_get_attributes", IotConGetError(nRet));
	CHECK_HANDLE(hState2,"iotcon_attributes_get_attributes");

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to add null and check is null
/**
* @testcase 			ITc_iotcon_attributes_add_is_null_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to add null and check is null
* @scenario				iotcon_attributes_add_null & iotcon_attributes_is_null \n
* @apicovered			iotcon_attributes_add_null , iotcon_attributes_is_null
* @passcase				if iotcon_attributes_add_null and iotcon_attributes_is_null passes
* @failcase				if iotcon_attributes_add_null or iotcon_attributes_is_null fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_add_is_null_p(void)
{
	START_TEST;

	bool bVal;

	int nRet = iotcon_attributes_add_null(g_hAttributes, KEY);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_null", IotConGetError(nRet));

	nRet = iotcon_attributes_is_null(g_hAttributes, KEY, &bVal);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_is_null", IotConGetError(nRet));
	if(bVal != true)
	{
		FPRINTF("[Line : %d][%s] value is not null  : \\n", __LINE__, API_NAMESPACE );
		return 1;
	}

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	return 0;
}


//& type: auto
//& purpose:  scenario to remove hAttributes
/**
* @testcase 			ITc_iotcon_attributes_remove_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to remove hAttributes
* @scenario				add different states like int,double,bool,null \n
*						iotcon_attributes_remove
* @apicovered			iotcon_attributes_remove
* @passcase				if iotcon_attributes_remove passes
* @failcase				if iotcon_attributes_remove fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_remove_p(void)
{
	START_TEST;

	int nSetIntVal = 10;
	bool bSetVal = true;
	double nSetDbVal = 3.4;

	int nRet = iotcon_attributes_add_int(g_hAttributes, KEY, nSetIntVal);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_int", IotConGetError(nRet));

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	nRet = iotcon_attributes_add_bool(g_hAttributes, KEY, bSetVal);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_bool", IotConGetError(nRet));

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	nRet = iotcon_attributes_add_double(g_hAttributes, KEY, nSetDbVal);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_double", IotConGetError(nRet));

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	nRet = iotcon_attributes_add_str(g_hAttributes, KEY, VALUE);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_str", IotConGetError(nRet));

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	nRet = iotcon_attributes_add_null(g_hAttributes, KEY);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_null", IotConGetError(nRet));

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	return 0;
}


//& type: auto
//& purpose:  scenario to get type of hAttributes
/**
* @testcase 			ITc_iotcon_attributes_get_type_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get type of hAttributes
* @scenario				iotcon_attributes_add_int \n
*						iotcon_attributes_get_type
* @apicovered			iotcon_attributes_add_int,iotcon_attributes_get_type
* @passcase				if iotcon_attributes_get_type passes
* @failcase				if iotcon_attributes_get_type fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_get_type_p(void)
{
	START_TEST;

	iotcon_type_e eType;

	int nSetIntVal = 10;

	int nRet = iotcon_attributes_add_int(g_hAttributes, KEY, nSetIntVal);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_int", IotConGetError(nRet));

	nRet = iotcon_attributes_get_type(g_hAttributes, KEY, &eType);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_get_type", IotConGetError(nRet));

	if(eType != IOTCON_TYPE_INT)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		return 1;
	}

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	return 0;
}


//& type: auto
//& purpose:  scenario to call a function for each element of hAttributes.
/**
* @testcase 			ITc_iotcon_attributes_foreach_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to call a function for each element of hAttributes.
* @scenario				create and add hAttributes \n
*						iotcon_attributes_foreach
* @apicovered			iotcon_attributes_foreach
* @passcase				if iotcon_attributes_foreach passes
* @failcase				if iotcon_attributes_foreach fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_foreach_p(void)
{
	START_TEST;

	iotcon_attributes_h hState1, hState2;
	g_bCheckCb = false;

	int nRet = iotcon_attributes_create(&hState1);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet));
	CHECK_HANDLE(hState1,"iotcon_attributes_create");

	nRet = iotcon_attributes_create(&hState2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet),iotcon_attributes_destroy(hState2);iotcon_attributes_destroy(hState1));
	CHECK_HANDLE(hState2,"iotcon_attributes_create");

	nRet = iotcon_attributes_add_attributes(g_hAttributes, VALUE, hState1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_attributes", IotConGetError(nRet),iotcon_attributes_destroy(hState2);iotcon_attributes_destroy(hState1));

	nRet = iotcon_attributes_add_attributes(g_hAttributes, KEY, hState2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_attributes", IotConGetError(nRet),iotcon_attributes_destroy(hState2);iotcon_attributes_destroy(hState1));

	nRet = iotcon_attributes_foreach(g_hAttributes, IotconStateCB, "user_data");
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_foreach", IotConGetError(nRet),iotcon_attributes_destroy(hState2);iotcon_attributes_destroy(hState1));

	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		iotcon_attributes_destroy(hState2);hState2 = NULL;
		iotcon_attributes_destroy(hState1);hState1 = NULL;
		return 1;
	}

	nRet = iotcon_attributes_remove(g_hAttributes, VALUE);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	iotcon_attributes_destroy(hState2);hState2 = NULL;
	iotcon_attributes_destroy(hState1);hState1 = NULL;

	return 0;
}

//& type: auto
//& purpose:  scenario to get keys count of hAttributes
/**
* @testcase 			ITc_iotcon_attributes_get_keys_count_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get keys count of hAttributes
* @scenario				create and add hAttributes \n
*						iotcon_attributes_get_keys_count
* @apicovered			iotcon_attributes_get_keys_count
* @passcase				if iotcon_attributes_get_keys_count passes
* @failcase				if iotcon_attributes_get_keys_count fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_get_keys_count_p(void)
{
	START_TEST;

	unsigned int nCount =0;
	iotcon_attributes_h hState1, hState2;

	int nRet = iotcon_attributes_create(&hState1);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet));
	CHECK_HANDLE(hState1,"iotcon_attributes_create");

	nRet = iotcon_attributes_create(&hState2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet),iotcon_attributes_destroy(hState1));
	CHECK_HANDLE(hState2,"iotcon_attributes_create");

	nRet = iotcon_attributes_add_attributes(g_hAttributes, VALUE, hState1);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_attributes", IotConGetError(nRet),iotcon_attributes_destroy(hState2);iotcon_attributes_destroy(hState1));

	nRet = iotcon_attributes_add_attributes(g_hAttributes, KEY, hState2);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_attributes", IotConGetError(nRet),iotcon_attributes_destroy(hState2);iotcon_attributes_destroy(hState1));

	nRet = iotcon_attributes_get_keys_count(g_hAttributes, &nCount);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_get_keys_count", IotConGetError(nRet),iotcon_attributes_destroy(hState2);iotcon_attributes_destroy(hState1));

	if (2 != nCount)
	{
		FPRINTF("[Line : %d][%s] value mismatch  : \\n", __LINE__, API_NAMESPACE );
		iotcon_attributes_destroy(hState2);hState2 = NULL;
		iotcon_attributes_destroy(hState1);hState1 = NULL;
		return 1;
	}

	nRet = iotcon_attributes_remove(g_hAttributes, VALUE);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));

	iotcon_attributes_destroy(hState2);hState2 = NULL;
	iotcon_attributes_destroy(hState1);hState1 = NULL;

	return 0;
}

//& type: auto
//& purpose:  scenario to get keys count of hAttributes
/**
* @testcase 			ITc_iotcon_attributes_add_get_byte_str_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get keys count of hAttributes
* @scenario				create and add hAttributes \n
*						iotcon_attributes_add_byte_str
* @apicovered			iotcon_attributes_add_byte_str
* @passcase				if iotcon_attributes_add_byte_str passes
* @failcase				if iotcon_attributes_add_byte_str fails
* @precondition			iotcon should be connected & create hAttributes
* @postcondition		iotcon should be disconnected & destroy hAttributes
*/
int ITc_iotcon_attributes_add_get_byte_str_p(void)
{
	START_TEST;

	unsigned char *GetValue = NULL;
	unsigned char SetValue[5] = { 1, 2, 3, 4, 5 };
	int len =  0;
	int i;

	int nRet = iotcon_attributes_add_byte_str(g_hAttributes, KEY, SetValue, sizeof(SetValue)/sizeof(unsigned char));
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_str", IotConGetError(nRet));

	nRet = iotcon_attributes_get_byte_str(g_hAttributes, KEY, &GetValue, &len);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_get_str", IotConGetError(nRet));

	if( sizeof(SetValue)/sizeof(unsigned char) != len )
	{
		FPRINTF("[Line : %d][%s] len mismatch \\n", __LINE__, API_NAMESPACE );
		iotcon_attributes_remove(g_hAttributes, KEY);
		return 1;
	}

	for (i = 0; i < sizeof(SetValue)/sizeof(unsigned char); i++) {
		if (GetValue[i] != SetValue[i]) {
			FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE );
			nRet = iotcon_attributes_remove(g_hAttributes, KEY);
			PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));
			return 1;
		}
	}

	nRet = iotcon_attributes_remove(g_hAttributes, KEY);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_remove", IotConGetError(nRet));
	return 0;
}

/** @} */
/** @} */

