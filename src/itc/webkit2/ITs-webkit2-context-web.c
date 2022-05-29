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
#include "ITs-webkit2-common.h"

/** @addtogroup itc-webkit2
*  @ingroup itc
*  @{
*/

Ewk_Context* ewkContext;

/**
* @function 		ITs_webkit_efl_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_context_web_startup(void)
{
	
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}


/**
* @function 		ITs_webkit_efl_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_context_web_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}


//& purpose: Requests for deleting all web indexed databases
//& type: auto
/**
* @testcase 			ITc_ewk_context_web_indexed_database_delete_all_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Requests for deleting all web indexed databases
* @scenario				ewk_view_context_get\n
*						ewk_context_web_indexed_database_delete_all
* @apicovered			ewk_view_context_get, ewk_context_web_indexed_database_delete_all
* @passcase				When ewk_context_web_indexed_database_delete_all is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_web_indexed_database_delete_all_p(void)
{
	START_TEST;
	Eina_Bool bData;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
	Ewk_Context* ewkContext = ewk_view_context_get(objWebkit_EFL_view.webview);
	if (ewkContext == NULL)
	{
		FPRINTF("[Line : %d][%s] Unable to create context\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	bData = ewk_context_web_indexed_database_delete_all(ewkContext);
	if (bData != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_context_web_indexed_database_delete_all failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: Deletes all web storage
//& type: auto
/**
* @testcase 			ITc_ewk_context_web_storage_delete_all_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Deletes all web storage
* @scenario				ewk_view_context_get\n
*						ewk_context_web_storage_delete_all
* @apicovered			ewk_view_context_get, ewk_context_web_storage_delete_all
* @passcase				When ewk_context_web_storage_delete_all is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_web_storage_delete_all_p(void)
{
	START_TEST;
	Eina_Bool bWebDel;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Context* ewkContext = ewk_view_context_get(objWebkit_EFL_view.webview);
	if (ewkContext == NULL)
	{
		FPRINTF("[Line : %d][%s] unabel to create context\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	bWebDel = ewk_context_web_storage_delete_all(ewkContext);
	if (bWebDel != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_context_web_storage_delete_all failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	Webkit_EFLDestroyWebKitView();
	return 0;
}


/** @} */
/** @} */
