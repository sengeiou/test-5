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
#include "ITs-thumbnail-util-common.h"

/** @addtogroup itc-thumbnail-util
* @ingroup		itc
* @{
*/

//Add helper function definitions here

/**
 * @function 		ThumbnailUtilGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* ThumbnailUtilGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case THUMBNAIL_UTIL_ERROR_NONE:				
			szErrorVal = "THUMBNAIL_UTIL_ERROR_NONE";					
			break;
		case THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER:			
			szErrorVal = "THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER";			
			break;
		case THUMBNAIL_UTIL_ERROR_OUT_OF_MEMORY:		
			szErrorVal = "THUMBNAIL_UTIL_ERROR_OUT_OF_MEMORY";		
			break;
		case THUMBNAIL_UTIL_ERROR_INVALID_OPERATION:			
			szErrorVal = "THUMBNAIL_UTIL_ERROR_INVALID_OPERATION";			
			break;
		case THUMBNAIL_UTIL_ERROR_FILE_NO_SPACE_ON_DEVICE:	
			szErrorVal = "THUMBNAIL_UTIL_ERROR_FILE_NO_SPACE_ON_DEVICE";	
			break;
		case THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED:			
			szErrorVal = "THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED";				
			break;
		default:										
			szErrorVal = "Unknown Error";								
			break;
	}

	return szErrorVal;
}

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
	return false;
}

/**
* @function 			ThumbnailGetDataPath
* @description 			Get the path to application data directory
* @parameter	[IN]	char* pszFileName [file name]
* @return 				NA
*/
char* ThumbnailGetDataPath(char *pszFileName)
{
	char *pszAppData =  app_get_data_path(),*pszImgPath = NULL;
	if ( pszAppData == NULL || strlen(pszAppData) == 0 )
	{
		FPRINTF("[Line : %d][%s] app_get_data_path() returned invalid path\\n", __LINE__, API_NAMESPACE);
		return pszImgPath;
	}
	
	pszImgPath = (char*) calloc(1, strlen(pszAppData) + strlen(pszFileName)+1);
	if (pszImgPath == NULL)
		return pszImgPath;
	snprintf(pszImgPath, strlen(pszAppData) + strlen(pszFileName) + 1, "%s%s",pszAppData, pszFileName );
	FPRINTF("[Line : %d][%s] app_get_data_path() is %s\\n", __LINE__, API_NAMESPACE, pszImgPath);
	return pszImgPath;
}

/** @} */ //end of thumbnail-util