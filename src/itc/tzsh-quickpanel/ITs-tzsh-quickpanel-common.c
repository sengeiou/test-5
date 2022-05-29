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
#include "ITs-tzsh-quickpanel-common.h"

/** @addtogroup itc-tzsh-quickpanel
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		TzshQuickpanelGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* TzshQuickpanelGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case TZSH_ERROR_NONE:				szErrorVal = "TZSH_ERROR_NONE";								break;
	case TZSH_ERROR_NO_SERVICE:			szErrorVal = "TZSH_ERROR_NO_SERVICE";						break;
	case TZSH_ERROR_OUT_OF_MEMORY:		szErrorVal = "TZSH_ERROR_OUT_OF_MEMORY";					break;
	case TZSH_ERROR_INVALID_PARAMETER:	szErrorVal = "TZSH_ERROR_INVALID_PARAMETER";				break;
	case TIZEN_ERROR_PERMISSION_DENIED:	szErrorVal = "TIZEN_ERROR_PERMISSION_DENIED";				break;
	default:							szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}

/**
* @function 		DeleteWin
* @description	 	Delete the elm window
* @parameter		void *data, Evas_Object *obj, void *event
* @return 			NA
*/
void DeleteWin(void *data, Evas_Object *obj, void *event)
{
    elm_exit();
}
/**
* @function 		CreateWindow
* @description	 	Creates the elm window
* @parameter		const char *name
* @return 			Evas_Object*
*/
Evas_Object* CreateWindow(const char *name)
{
    Evas_Object *evObj = NULL;
    Evas_Object *conform = NULL;

    evObj = elm_win_add(NULL, name, ELM_WIN_BASIC);
    if (evObj)
    {
        elm_win_title_set(evObj, name);
        evas_object_smart_callback_add(evObj, "delete,request",
                                       DeleteWin, NULL);

        elm_win_conformant_set(evObj, EINA_TRUE);

        /* Conformant */
        conform = elm_conformant_add(evObj);
        evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        elm_win_resize_object_add(evObj, conform);
        evas_object_show(conform);

        elm_win_indicator_mode_set(evObj, ELM_WIN_INDICATOR_SHOW);
        elm_win_indicator_opacity_set(evObj, ELM_WIN_INDICATOR_TRANSPARENT);
    }

    return evObj;
}

/** @} */