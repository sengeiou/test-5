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
#include "ITs-cbhm-common.h"

//& set: Cbhm

/** @addtogroup itc-cbhm
*  @ingroup itc
*  @{
*/

static cbhm_h g_CbhmHandle = NULL;
static bool g_bCallBackCheck = false;
static bool g_bCallBackDataCheck = false;
static char *g_pszData = NULL;

static int CbhmSelectionDataCb(cbhm_h cbhm_handle, const char *buf, size_t len, void *user_data)
{
    g_bCallBackCheck = true;
	FPRINTF("[Line : %d] [%s] Inside callcack function CbhmSelectionDataCb \\n", __LINE__, API_NAMESPACE);
	
	if(buf)
	{
		strncpy(g_pszData, buf, len);
		g_bCallBackDataCheck = true;
	}
	else
	{
		FPRINTF("[Line : %d] [%s] Invalid callback data \\n", __LINE__, API_NAMESPACE);
	}
	
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
	}
	return CBHM_ERROR_NONE;
}

static int CbhmSelectionCb(cbhm_h cbhm_handle, void *user_data)
{
   FPRINTF("[Line : %d] [%s] Inside callcack function CbhmSelectionCb \\n", __LINE__, API_NAMESPACE);
   return CBHM_ERROR_NONE;
}

/**
 * @function 		ITs_cbhm_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cbhm_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	elm_init(0, NULL);
	g_bCbhmInit = false;
		
	int nRet = cbhm_open_service(&g_CbhmHandle);
	if ( nRet != CBHM_ERROR_NONE )
	{
		FPRINTF("[Line : %d] [%s] cbhm_open_service failed in startup, error = %s\\n", __LINE__, API_NAMESPACE, CbhmGetError(nRet));
		return;
	}
	if ( g_CbhmHandle == NULL )
	{
		FPRINTF("[Line : %d] [%s] cbhm handle returned is NULL\\n", __LINE__, API_NAMESPACE);
		return;
	}
	
	g_bCbhmInit = true;
	return;
}


/**
 * @function 		ITs_cbhm_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cbhm_cleanup(void)
{
	if(g_CbhmHandle)
	{
		int nRet = cbhm_close_service(g_CbhmHandle);
		if ( nRet != CBHM_ERROR_NONE )
		{
			FPRINTF("[Line : %d] [%s] cbhm_close_service failed in cleanup, error = %s\\n", __LINE__, API_NAMESPACE, CbhmGetError(nRet));
		}
	}
	g_CbhmHandle = NULL;
	
	return;
}

/** @addtogroup itc-cbhm-testcases
*  @brief 		Integration testcases for module cbhm
*  @ingroup 	itc-cbhm
*  @{
*/

//& type: auto
//& purpose: Initializes and close the clipboard handle to use clipboard
/**
* @testcase 			ITc_cbhm_open_close_service_p
* @since_tizen			3.0
* @author				SRID(a.pandia1)
* @reviewer				SRID(nibha.sharma)
* @type 				auto
* @description			To create and remove a badge
* @scenario				Initializes and close the clipboard handle to use clipboard
* 						Initializes the clipboard handle to use clipboard\n
* 						Closes the clipboard handle\n
* @apicovered			cbhm_open_service, cbhm_close_service
* @passcase				If cbhm_open_service, cbhm_close_service returns success
* @failcase				If cbhm_open_service, cbhm_close_service returns false
* @precondition			NA
* @postcondition		NA
*/
int ITc_cbhm_open_close_service_p(void)
{
    START_TEST;
	
	cbhm_h h_Cbhm = NULL;
	
	int nRet = cbhm_open_service(&h_Cbhm);
	PRINT_RESULT(CBHM_ERROR_NONE, nRet, "cbhm_open_service", CbhmGetError(nRet));
	CHECK_HANDLE(h_Cbhm, "cbhm_open_service")
	
	nRet = cbhm_close_service(h_Cbhm);
	PRINT_RESULT(CBHM_ERROR_NONE, nRet, "cbhm_close_service", CbhmGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Sets and gets the clipboard selection type
/**
* @testcase 			ITc_cbhm_selection_type_set_get_p
* @since_tizen			3.0
* @author				SRID(a.pandia1)
* @reviewer				SRID(nibha.sharma)
* @type 				auto
* @description			Sets and gets the clipboard selection type
* @scenario				Sets the clipboard selection type
* 						Gets the clipboard selection type
* @apicovered			cbhm_selection_type_set, cbhm_selection_type_get
* @passcase				If cbhm_selection_type_set, cbhm_selection_type_get returns success
* @failcase				If cbhm_selection_type_set, cbhm_selection_type_get returns false
* @precondition			Initializes the clipboard handle to use clipboard
* @postcondition		Close the clipboard handle
*/
int ITc_cbhm_selection_type_set_get_p(void)
{
    START_TEST;
	
	int nRet = -1, nEnumCount = 0, nIterator = 0;
	cbhm_sel_type_e eGetSelType;
	
	cbhm_sel_type_e arrSelType[] = {
									//CBHM_SEL_TYPE_TARGETS, 	/** For matching every possible atom */
									CBHM_SEL_TYPE_NONE, 	/** Content is from outside of Elementary */
									CBHM_SEL_TYPE_TEXT, 	/** Plain unformatted text: Used for things that don't want rich markup */
									CBHM_SEL_TYPE_MARKUP,   /** Edje textblock markup, including inline images */
									CBHM_SEL_TYPE_IMAGE, 	/** Images */
									//CBHM_SEL_TYPE_VCARD, 	/** Vcards */
									CBHM_SEL_TYPE_HTML	 	/** Raw HTML-like data (eg. webkit) */
								  };
	
	nEnumCount = sizeof(arrSelType) / sizeof(arrSelType[0]);

	for ( nIterator = 0; nIterator < nEnumCount; nIterator++ )
	{
		nRet = cbhm_selection_type_set(g_CbhmHandle, arrSelType[nIterator]);
		PRINT_RESULT(CBHM_ERROR_NONE, nRet, "cbhm_selection_type_set", CbhmGetError(nRet));
		
		nRet = cbhm_selection_type_get(g_CbhmHandle, &eGetSelType);
		PRINT_RESULT(CBHM_ERROR_NONE, nRet, "cbhm_selection_type_get", CbhmGetError(nRet));
		
		if(eGetSelType != arrSelType[nIterator])
		{
			FPRINTF("[Line : %d] [%s] cbhm_sel_type_e set get values mismatch\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	
	return 0;
}

//& type: auto
//& purpose: Shows and hides the clipboard
/**
* @testcase 			ITc_cbhm_show_hide_p
* @since_tizen			3.0
* @author				SRID(a.pandia1)
* @reviewer				SRID(nibha.sharma)
* @type 				auto
* @description			Shows and hides the clipboard
* @scenario				Shows the clipboard
* 						Hides the clipboard
* @apicovered			cbhm_show, cbhm_hide
* @passcase				If cbhm_show, cbhm_hide returns success
* @failcase				If cbhm_show, cbhm_hide returns false
* @precondition			Initializes the clipboard handle to use clipboard
* @postcondition		Close the clipboard handle
*/
int ITc_cbhm_show_hide_p(void)
{
    START_TEST;
	
	int nRet = cbhm_selection_type_set(g_CbhmHandle, CBHM_SEL_TYPE_TEXT);
	PRINT_RESULT(CBHM_ERROR_NONE, nRet, "cbhm_selection_type_set", CbhmGetError(nRet));
	
	nRet = cbhm_show(g_CbhmHandle);
	PRINT_RESULT(CBHM_ERROR_NONE, nRet, "cbhm_show", CbhmGetError(nRet));
	
	nRet = cbhm_hide(g_CbhmHandle);
	PRINT_RESULT(CBHM_ERROR_NONE, nRet, "cbhm_hide", CbhmGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Shows and hides the clipboard
/**
* @testcase 			ITc_cbhm_selection_set_get_p
* @since_tizen			3.0
* @author				SRID(a.pandia1)
* @reviewer				SRID(nibha.sharma)
* @type 				auto
* @description			Shows and hides the clipboard
* @scenario				Shows the clipboard
* 						Hides the clipboard
* @apicovered			cbhm_selection_type_set, cbhm_selection_set, cbhm_selection_get
* @passcase				If cbhm_selection_set, cbhm_selection_get returns success
* @failcase				If cbhm_selection_set, cbhm_selection_get returns false
* @precondition			Initializes the clipboard handle to use clipboard
* @postcondition		Close the clipboard handle
*/
int ITc_cbhm_selection_set_get_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszData = "Test Data CBHM ITC";
	int nTimeoutId = 0;
	
	cbhm_h h_Cbhm = NULL;
	nRet = cbhm_open_service(&h_Cbhm);
	PRINT_RESULT(CBHM_ERROR_NONE, nRet, "cbhm_open_service", CbhmGetError(nRet));
	CHECK_HANDLE(h_Cbhm, "cbhm_open_service");
	
	g_bCallBackCheck = false;
	g_bCallBackDataCheck = false;

	nRet = cbhm_selection_type_set(h_Cbhm, CBHM_SEL_TYPE_TEXT);
	PRINT_RESULT_CLEANUP(CBHM_ERROR_NONE, nRet, "cbhm_selection_type_set", CbhmGetError(nRet), cbhm_close_service(h_Cbhm));

	nRet = cbhm_selection_set(h_Cbhm, CBHM_SEL_TYPE_TEXT, pszData, strlen(pszData));
	PRINT_RESULT_CLEANUP(CBHM_ERROR_NONE, nRet, "cbhm_selection_set", CbhmGetError(nRet), cbhm_close_service(h_Cbhm));
	
	sleep(2);
	nRet = cbhm_selection_get(h_Cbhm, CBHM_SEL_TYPE_TEXT, CbhmSelectionDataCb, NULL);
	PRINT_RESULT_CLEANUP(CBHM_ERROR_NONE, nRet, "cbhm_selection_get", CbhmGetError(nRet), cbhm_close_service(h_Cbhm));
		
	RUN_POLLING_LOOP;
	if (!g_bCallBackCheck)
	{
		FPRINTF("[Line : %d][%s] CbhmSelectionDataCb callback not hit\\n", __LINE__, API_NAMESPACE);
		cbhm_close_service(h_Cbhm);
		return 1;
	}
	if (!g_bCallBackDataCheck)
	{
		cbhm_close_service(h_Cbhm);
		return 1;
	}
	if(strcmp(pszData, g_pszData) != 0)
	{
		FPRINTF("[Line : %d] [%s] set get data values mismatch\\n", __LINE__, API_NAMESPACE);
		cbhm_close_service(h_Cbhm);
		return 1;
	}
	
	nRet = cbhm_close_service(h_Cbhm);
	PRINT_RESULT_NORETURN(CBHM_ERROR_NONE, nRet, "cbhm_close_service", CbhmGetError(nRet));
}

//& type: auto
//& purpose: Gets the count of clipboard items
/**
* @testcase 			ITc_cbhm_item_count_get_p
* @since_tizen			3.0
* @author				SRID(a.pandia1)
* @reviewer				SRID(nibha.sharma)
* @type 				auto
* @description			Gets the count of clipboard items
* @scenario				Gets the count of clipboard items
* @apicovered			cbhm_selection_type_set, cbhm_item_count_get
* @passcase				If cbhm_item_count_get returns success
* @failcase				If cbhm_item_count_get returns false
* @precondition			Initializes the clipboard handle to use clipboard
* @postcondition		Close the clipboard handle
*/
int ITc_cbhm_item_count_get_p(void)
{
    START_TEST;
	char *pszData = "Test Data CBHM ITC";
	
	int nRet = cbhm_selection_set(g_CbhmHandle, CBHM_SEL_TYPE_TEXT, pszData, strlen(pszData));
	PRINT_RESULT(CBHM_ERROR_NONE, nRet, "cbhm_selection_type_set", CbhmGetError(nRet));
	
	nRet = -1;
	nRet = cbhm_item_count_get(g_CbhmHandle);
	FPRINTF("[Line : %d][%s] Item count from recieved from cbhm_item_count_get = %d\\n", __LINE__, API_NAMESPACE, nRet);
	if(nRet < 0 || nRet == CBHM_ERROR_INVALID_PARAMETER)
	{
		FPRINTF("[Line : %d][%s] Invalid return value of API cbhm_item_count_get = %s\\n", __LINE__, API_NAMESPACE, CbhmGetError(nRet));
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: Adds the event callback for handling selection of clipboard item
/**
* @testcase 			ITc_cbhm_item_selected_callback_add_p
* @since_tizen			3.0
* @author				SRID(a.pandia1)
* @reviewer				SRID(nibha.sharma)
* @type 				auto
* @description			Adds the event callback for handling selection of clipboard item
* @scenario				Adds the event callback for handling selection of clipboard item
* @apicovered			cbhm_item_selected_callback_add
* @passcase				If cbhm_item_selected_callback_add returns success
* @failcase				If cbhm_item_selected_callback_add returns false
* @precondition			Initializes the clipboard handle to use clipboard
* @postcondition		Close the clipboard handle
*/
int ITc_cbhm_item_selected_callback_add_p(void)
{
    START_TEST;
	
	int nRet = cbhm_item_selected_callback_add(g_CbhmHandle, CbhmSelectionCb, NULL);
	PRINT_RESULT(CBHM_ERROR_NONE, nRet, "cbhm_item_selected_callback_add", CbhmGetError(nRet));
	
	return 0;
}

/** @} */
/** @} */