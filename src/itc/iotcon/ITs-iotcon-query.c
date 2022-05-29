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

iotcon_query_h g_hQuery = NULL;
bool g_bIotconQueryForeachCompletedCallback;
//& set: Iotcon

/** @addtogroup itc-iotcon
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_iotcon_query_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_query_startup(void)
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

	nRet = iotcon_query_create(&g_hQuery);
	if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] iotcon_query_create fail in startup error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
		iotcon_deinitialize();
		g_bIotconConnect = false;
		return;
	}
	if(g_hQuery == NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_query_create failed as g_hQuery is NULL\\n", __LINE__, API_NAMESPACE );
		iotcon_deinitialize();
		g_bIotconConnect = false;
		return;
	}
	return;
}


/**
 * @function 		ITs_iotcon_query_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_query_cleanup(void)
{
	if(g_hQuery)
	{
		iotcon_query_destroy(g_hQuery);
	}
	if( g_bIotconConnect )
	{
		iotcon_deinitialize();

	}
	return;
}

/** @addtogroup itc-iotcon-testcases
*  @brief 		Integration testcases for module iotcon
*  @ingroup 	itc-iotcon
*  @{
*/

//& purpose: Creates a new query handle.
//& type: auto
/**
* @testcase   			ITc_iotcon_query_create_destroy_p
* @since_tizen			3.0
* @author             	SRID(manu.tiwari)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Creates a new query handle.
* @scenario				call iotcon_query_create
* @apicovered			iotcon_query_create
* @passcase				When iotcon_query_create is successful.
* @failcase				If target API iotcon_query_create or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_query_create_destroy_p(void)
{
	START_TEST;

	iotcon_query_h hQuery = NULL;
	//target api
	int nRet = iotcon_query_create(&hQuery);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_create", IotConGetError(nRet));
	CHECK_HANDLE(hQuery,"iotcon_query_create");
	//target api
	nRet = iotcon_query_destroy(hQuery);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_destroy", IotConGetError(nRet));
	
    return 0;
}
//& purpose: Sets and gets resource types from the query.
//& type: auto
/**
* @testcase   			ITc_iotcon_query_set_get_resource_types_p
* @since_tizen			3.0
* @author             	SRID(manu.tiwari)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Sets and gets resource types from the query.
* @scenario				call iotcon_query_set_resource_types and iotcon_query_get_resource_types
* @apicovered			iotcon_query_set_resource_types and iotcon_query_get_resource_types
* @passcase				When iotcon_query_set_resource_types and iotcon_query_get_resource_types are successful.
* @failcase				If target API iotcon_query_set_resource_types and iotcon_query_get_resource_types or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/

//Commenting since the APIs are not available in the curtrent repo
/*int ITc_iotcon_query_set_get_resource_types_p(void)
{
	START_TEST;

	iotcon_resource_types_h types = NULL;
	char *Gettypes = NULL;

	int nRet = iotcon_resource_types_create(&types);
    PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	if(types == NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_resource_types_create failed as types is NULL\\n", __LINE__, API_NAMESPACE );
		return 1;
	}

	nRet = iotcon_resource_types_add(types, "core.led");
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet),iotcon_resource_types_destroy(types));

	//target api
	nRet = iotcon_query_set_resource_types(g_hQuery, "org.tizen.light");
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_resource_types", IotConGetError(nRet),iotcon_resource_types_destroy(types));

	//target api
	nRet = iotcon_query_get_resource_types(g_hQuery, &Gettypes);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_query_get_resource_types", IotConGetError(nRet),iotcon_resource_types_destroy(types););


	if( strcmp("org.tizen.light",Gettypes) != 0)
	{
		FPRINTF("[Line : %d][%s] Values of set get not matched!!!\\n", __LINE__, API_NAMESPACE);
		iotcon_resource_types_destroy(types);
        return 1;
	}

	iotcon_resource_types_destroy(types);
	return 0;
}*/


//& purpose: Sets and gets the interface from the query.
//& type: auto
/**
* @testcase   			ITc_iotcon_query_set_get_interface_p
* @since_tizen			3.0
* @author             	SRID(manu.tiwari)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Sets and gets the interface from the query.
* @scenario				call iotcon_query_set_interface and iotcon_query_get_interface
* @apicovered			iotcon_query_set_interface and iotcon_query_get_interface
* @passcase				When iotcon_query_set_interface and iotcon_query_get_interface are successful.
* @failcase				If target API iotcon_query_set_interface and iotcon_query_get_interface or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_query_set_get_interface_p(void)
{
	START_TEST;

	char *pszface = NULL;

	//target api
	int nRet = iotcon_query_set_interface(g_hQuery, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_set_interface", IotConGetError(nRet));
	//target api
	nRet = iotcon_query_get_interface(g_hQuery, &pszface);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_get_interface", IotConGetError(nRet));

	if (0 != strcmp(IOTCON_INTERFACE_DEFAULT, pszface))
	{
		FPRINTF("[Line : %d][%s] Values of set get not matched!!!\\n", __LINE__, API_NAMESPACE);
        return 1;
	}

	return 0;
}
//& purpose: Add and remove a new key and corresponding value into the query.
//& type: auto
/**
* @testcase   			ITc_iotcon_query_add_remove_p
* @since_tizen			3.0
* @author             	SRID(manu.tiwari)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Add and remove a new key and corresponding value into the query.
* @scenario				call iotcon_query_add and iotcon_query_remove
* @apicovered			iotcon_query_add and iotcon_query_remove
* @passcase				When iotcon_query_add and iotcon_query_remove are successful.
* @failcase				If target API iotcon_query_add and iotcon_query_remove or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_query_add_remove_p(void)
{
	START_TEST;
    //target api
	int nRet = iotcon_query_add(g_hQuery, KEY, VALUE);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_add", IotConGetError(nRet));
	//target api
	nRet = iotcon_query_remove(g_hQuery, KEY);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_remove", IotConGetError(nRet));
    return 0;
}
//& purpose: Looks up data at the given key from the query.
//& type: auto
/**
* @testcase   			ITc_iotcon_query_lookup_p
* @since_tizen			3.0
* @author             	SRID(manu.tiwari)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Looks up data at the given key from the query.
* @scenario				call iotcon_query_lookup
* @apicovered			iotcon_query_lookup
* @passcase				When iotcon_query_lookup is successful.
* @failcase				If target API iotcon_query_lookup or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_query_lookup_p(void)
{
	START_TEST;
	char *data = NULL;
	int nRet = iotcon_query_add(g_hQuery, KEY, VALUE);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_add", IotConGetError(nRet));

	//target api
	nRet = iotcon_query_lookup(g_hQuery, KEY, &data);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_lookup", IotConGetError(nRet));
	if(data == NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_query_lookup failed as data is NULL\\n", __LINE__, API_NAMESPACE );
		nRet = iotcon_query_remove(g_hQuery, KEY);
	    PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_remove", IotConGetError(nRet));
		return 1;
	}
	if (0 != strcmp(VALUE, data))
	{
		FPRINTF("[Line : %d][%s] look up data does not match with actual data!!!\\n", __LINE__, API_NAMESPACE);
		nRet = iotcon_query_remove(g_hQuery, KEY);
		PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_remove", IotConGetError(nRet));
        return 1;
	}

	nRet = iotcon_query_remove(g_hQuery, KEY);
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_remove", IotConGetError(nRet));

	return 0;
}
/**
* @function			IotconQueryForeachCB
* @description		Specifies the type of function passed to iotcon_query_foreach()
* @parameter[IN]	key The key of the query
* @parameter[IN]	value The value of the query
* @parameter[IN]	user_data The user data to pass to the function
* @return			true to continue with the next iteration of the loop.
*/
static bool IotconQueryForeachCB(const char *key, const char *value,void *user_data)
{
	if(key == NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_query_foreach_cb failed as key is NULL\\n", __LINE__, API_NAMESPACE );
	}
    if(value == NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_query_foreach_cb failed as value is NULL\\n", __LINE__, API_NAMESPACE );
	}
	g_bIotconQueryForeachCompletedCallback = true;
	if (user_data)
		++ (*((int *)user_data));

	return IOTCON_FUNC_CONTINUE;
}
//& purpose: Gets all data of the query by invoking the callback function.
//& type: auto
/**
* @testcase   			ITc_iotcon_query_foreach_p
* @since_tizen			3.0
* @author             	SRID(manu.tiwari)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Gets all data of the query by invoking the callback function
* @scenario				call iotcon_query_foreach
* @apicovered			iotcon_query_foreach
* @passcase				When iotcon_query_foreach is successful.
* @failcase				If target API iotcon_query_foreach or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_query_foreach_p(void)
{
	START_TEST;

	int count = 0;

	int nRet = iotcon_query_add(g_hQuery, "key1", "val1");
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_add", IotConGetError(nRet));

	nRet = iotcon_query_add(g_hQuery, "key2", "val2");
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_add", IotConGetError(nRet));

	nRet = iotcon_query_add(g_hQuery, "key3", "val3");
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_add", IotConGetError(nRet));
	g_bIotconQueryForeachCompletedCallback = false;

	//target api
	nRet = iotcon_query_foreach(g_hQuery, IotconQueryForeachCB, &count);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_query_foreach", IotConGetError(nRet));

	if ( !g_bIotconQueryForeachCompletedCallback )
	{
		FPRINTF("[Line : %d][%s] callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] iotcon_query_foreach is successful\\n", __LINE__, API_NAMESPACE);
#endif
	}
	if (count != VAL4)
	{
		FPRINTF("[Line : %d][%s] iotcon_query_foreach is not successful!!!\\n", __LINE__, API_NAMESPACE);
        return 1;
	}

	nRet = iotcon_query_remove(g_hQuery, "key1");
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_remove", IotConGetError(nRet));

	nRet = iotcon_query_remove(g_hQuery, "key2");
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_remove", IotConGetError(nRet));

	nRet = iotcon_query_remove(g_hQuery, "key3");
	PRINT_RESULT_NORETURN(IOTCON_ERROR_NONE, nRet, "iotcon_query_remove", IotConGetError(nRet));

    return 0;
}

/** @} */
/** @} */
