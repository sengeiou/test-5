//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include "ITs-capi-ui-sticker-common.h"

/** @addtogroup itc-capi-ui-sticker
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		Timeout
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean Timeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}

	FPRINTF("[Line : %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
	return false;
}

/**
* @function 		StickerGetError
* @description	 	Maps sticker_error_e enums
* @parameter		error : error level
* @return 			error string
*/

char* StickerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case STICKER_ERROR_NONE:				szErrorVal = "STICKER_ERROR_NONE";					break;
	case STICKER_ERROR_INVALID_PARAMETER:	szErrorVal = "STICKER_ERROR_INVALID_PARAMETER";	break;
	case STICKER_ERROR_OPERATION_FAILED:	szErrorVal = "STICKER_ERROR_OPERATION_FAILED";	break;
	case STICKER_ERROR_OUT_OF_MEMORY:	szErrorVal = "STICKER_ERROR_OUT_OF_MEMORY";	break;
	case STICKER_ERROR_NOT_SUPPORTED:		szErrorVal = "STICKER_ERROR_NOT_SUPPORTED";		break;
	case STICKER_ERROR_PERMISSION_DENIED:	szErrorVal = "STICKER_ERROR_PERMISSION_DENIED";	break;
	case STICKER_ERROR_FILE_EXISTS:			szErrorVal = "STICKER_ERROR_FILE_EXISTS"; break;
	case STICKER_ERROR_NO_DATA:				szErrorVal = "STICKER_ERROR_NO_DATA"; break;
	case STICKER_ERROR_NO_SUCH_FILE:		szErrorVal = "STICKER_ERROR_NO_SUCH_FILE"; break;
	}

	return szErrorVal;
}


/** @} */
