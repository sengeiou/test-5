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
#include "ITs-efl-util-common.h"

/** @addtogroup itc-efl-util
 *  @ingroup itc
 *  @{
 */

//Add helper function definitions here
/**
* @function 		EflUtilGetError
* @description	 	Maps error enumerators to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* EflUtilGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch(nRet)
	{
	case EFL_UTIL_ERROR_NONE : 								szErrorVal = " EFL_UTIL_ERROR_NONE " ; 						break; 		
	case EFL_UTIL_ERROR_INVALID_PARAMETER : 				szErrorVal = " EFL_UTIL_ERROR_INVALID_PARAMETER " ; 		break; 
	case EFL_UTIL_ERROR_NOT_SUPPORTED_WINDOW_TYPE : 		szErrorVal = " EFL_UTIL_ERROR_NOT_SUPPORTED_WINDOW_TYPE " ; break; 
	case EFL_UTIL_ERROR_PERMISSION_DENIED: 					szErrorVal = " EFL_UTIL_ERROR_PERMISSION_DENIED " ;			break; 
	default:												szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

/**
* @function			EflUtilDeleteWindow
* @description		Callback function invoked while deleting ELM window
* @parameter[OUT]	pData [User data if any]
*					pstWindow [Pointer to EFL window]
*					pEvent [Type of Event]
* @return			NA
*/
void EflUtilDeleteWindow(void *pData, Evas_Object *pstWindow, void *pEvent)
{
	elm_exit();
}

/**
* @function			EflUtilCreateNotificationWindow
* @description		Creates a notification window
* @parameter[OUT]	pstWindow [Pointer to Evas_Object type to get a new window created]
* @return			NA
*/
bool EflUtilCreateNotificationWindow(Evas_Object **pstWindow)
{
	*pstWindow = elm_win_add(NULL, "Notification Window", ELM_WIN_NOTIFICATION);
	if (*pstWindow)
	{
		elm_win_title_set(*pstWindow, "Notification Window");
		elm_win_borderless_set(*pstWindow, EINA_TRUE);
		evas_object_smart_callback_add(*pstWindow, "Delete Request", EflUtilDeleteWindow, NULL);
		elm_win_indicator_mode_set(*pstWindow, ELM_WIN_INDICATOR_SHOW);
                evas_object_show(*pstWindow);
		return true;
	}
	else
	{
		return false;
	}
}

/**
* @function 		TimeoutFunction
* @description	 	Called if some callback is not invoked for a particular Timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean TimeoutFunction(gpointer data)
{
	FPRINTF("Timeout after 30 seconds\n");
	ecore_main_loop_quit();
	return FALSE;
}

/**
* @function 		WaitForAsync
* @description	 	Called to wait
* @parameter		NA
* @return 			NA
*/
void WaitForAsync()
{
	g_main_loop_new(NULL, false);
	int nTimeOutID = g_timeout_add(TIMEOUT, TimeoutFunction, NULL);
	ecore_main_loop_glib_integrate();
	ecore_main_loop_begin();
	g_source_remove(nTimeOutID);
}

/**
* @function 		GetScreenMode
* @description	 	Maps Set mode enumerators to string values
* @parameter		nMode : enum Set Mode
* @return 			Set mode as string
*/
char* GetScreenMode(int nMode)
{
	char *szModeVal = NULL;

	switch ( nMode )
	{
	case EFL_UTIL_SCREEN_MODE_DEFAULT:					szModeVal = "EFL_UTIL_SCREEN_MODE_DEFAULT";							break; 		
	case EFL_UTIL_SCREEN_MODE_ALWAYS_ON:				szModeVal = "EFL_UTIL_SCREEN_MODE_ALWAYS_ON";				break; 
	default:											szModeVal = "Unknown Set Mode";								break;
	}

	return szModeVal;
}

/** @} */
