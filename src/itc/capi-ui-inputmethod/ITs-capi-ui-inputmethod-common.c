//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-capi-ui-inputmethod-common.h"

/** @addtogroup itc-capi-ui-inputmethod
*  @ingroup itc
*  @{
*/

//Add helper function definitions here
char* InputGetError(int nRet)
{
	char *szErrorVal = "Undefined Error";

	switch ( nRet )
	{
	case IME_ERROR_NONE:									szErrorVal = "IME_ERROR_NONE";									break;
	case IME_ERROR_INVALID_PARAMETER:						szErrorVal = "IME_ERROR_INVALID_PARAMETER";						break;
	case IME_ERROR_PERMISSION_DENIED:						szErrorVal = "IME_ERROR_PERMISSION_DENIED";						break;
	case IME_ERROR_NO_CALLBACK_FUNCTION:					szErrorVal = "IME_ERROR_NO_CALLBACK_FUNCTION";					break;
	case IME_ERROR_NOT_RUNNING:								szErrorVal = "IME_ERROR_NOT_RUNNING";							break;
	case IME_ERROR_OPERATION_FAILED:						szErrorVal = "IME_ERROR_OPERATION_FAILED";						break;
	case IME_ERROR_OUT_OF_MEMORY:							szErrorVal = "IME_ERROR_OUT_OF_MEMORY";							break;
	}

	return szErrorVal;
}

#ifndef TV
static void WinDel(void *data, Evas_Object *obj, void *event)
{
	elm_exit();
}

Evas_Object* CreateNormalWin()
{
	Evas_Object *eo = NULL;

	eo = elm_win_add(NULL, "IME Window", ELM_WIN_BASIC);
	if (eo)
	{
		elm_win_title_set(eo, "IME Window");
		elm_win_borderless_set(eo, EINA_TRUE);
		evas_object_smart_callback_add(eo, "delete,request",WinDel, NULL);
		elm_win_indicator_mode_set(eo, ELM_WIN_INDICATOR_SHOW);
	}

	return eo;
}
#endif // Except for TV profile

/** @} */
