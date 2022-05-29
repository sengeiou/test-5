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
#include "ITs-libstorage-common.h"

/** @addtogroup itc-libstorage
*  @ingroup itc
*  @{
*/
//Add helper function definitions here

/**
* @function 		StorageGetError
* @description	 	Maps storage_error_e enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* StorageGetError(storage_error_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case STORAGE_ERROR_NONE:				szErrorVal = "STORAGE_ERROR_NONE";					break;
	case STORAGE_ERROR_INVALID_PARAMETER:	szErrorVal = "STORAGE_ERROR_INVALID_PARAMETER";		break;
	case STORAGE_ERROR_OUT_OF_MEMORY:		szErrorVal = "STORAGE_ERROR_OUT_OF_MEMORY";			break;
	case STORAGE_ERROR_NOT_SUPPORTED:		szErrorVal = "STORAGE_ERROR_NOT_SUPPORTED";			break;
	case STORAGE_ERROR_OPERATION_FAILED:	szErrorVal = "STORAGE_ERROR_OPERATION_FAILED";		break;
	default:								szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}

/**
* @function 		StorageGetType
* @description	 	Maps storage_type_e enums to string values
* @parameter		nType : storage type enum
* @return 			storage type string
*/
char* StorageGetType(storage_type_e nType)
{
	char *szType = "Unknown Storage Type";
	switch ( nType )
	{
	case STORAGE_TYPE_INTERNAL:				szType = "STORAGE_TYPE_INTERNAL";			break;
	case STORAGE_TYPE_EXTERNAL:				szType = "STORAGE_TYPE_EXTERNAL";			break;
	case STORAGE_TYPE_EXTENDED_INTERNAL:	szType = "STORAGE_TYPE_EXTENDED_INTERNAL";	break;
	}

	return szType;
}

/**
* @function 		StorageGetDirectory
* @description	 	Maps storage_directory_e enum to string value
* @parameter		nType : directory type enum
* @return 			directory type string
*/
char* StorageGetDirectory(storage_directory_e nType)
{
	char *szType = NULL;
	switch ( nType )
	{
	case STORAGE_DIRECTORY_IMAGES:				szType = "STORAGE_DIRECTORY_IMAGES";				break;
	case STORAGE_DIRECTORY_SOUNDS:				szType = "STORAGE_DIRECTORY_SOUNDS";				break;
	case STORAGE_DIRECTORY_VIDEOS:				szType = "STORAGE_DIRECTORY_VIDEOS";				break;
	case STORAGE_DIRECTORY_CAMERA:				szType = "STORAGE_DIRECTORY_CAMERA";				break;
	case STORAGE_DIRECTORY_DOWNLOADS:			szType = "STORAGE_DIRECTORY_DOWNLOADS";				break;
	case STORAGE_DIRECTORY_MUSIC:				szType = "STORAGE_DIRECTORY_MUSIC";					break;
	case STORAGE_DIRECTORY_DOCUMENTS:			szType = "STORAGE_DIRECTORY_DOCUMENTS";				break;
	case STORAGE_DIRECTORY_OTHERS:				szType = "STORAGE_DIRECTORY_OTHERS";				break;
	case STORAGE_DIRECTORY_SYSTEM_RINGTONES:	szType = "STORAGE_DIRECTORY_SYSTEM_RINGTONES";		break;
	case STORAGE_DIRECTORY_MAX:					szType = "STORAGE_DIRECTORY_MAX";					break;
	}

	return szType;
}

/**
* @function 		StorageGetState
* @description	 	Maps storage_state_e enums to string values
* @parameter		nState : storage state enum
* @return 			storage state string
*/
char* StorageGetState(storage_state_e nState)
{
	char *szType = NULL;
	switch ( nState )
	{
	case STORAGE_STATE_UNMOUNTABLE:			szType = "STORAGE_STATE_UNMOUNTABLE";			break;
	case STORAGE_STATE_REMOVED:				szType = "STORAGE_STATE_REMOVED";				break;
	case STORAGE_STATE_MOUNTED:				szType = "STORAGE_STATE_MOUNTED";				break;
	case STORAGE_STATE_MOUNTED_READ_ONLY:	szType = "STORAGE_STATE_MOUNTED_READ_ONLY";		break;
	default:								szType = "Unknown Storage Type";				break;
	}

	return szType;
}
/** @} */