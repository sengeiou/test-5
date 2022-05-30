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
#include "ITs-bundle-common.h"

/** @addtogroup itc-bundle
*  @ingroup itc
*  @{
*/

/**
* @function 		BundleGetType
* @description	 	Maps Types of given values to string.
* @parameter		nRet : result code returned
* @return 			Type represented as string
*/
char* BundleGetType(int nRet)
{
	char *szTypeVal = NULL;

	switch ( nRet )
	{
	case BUNDLE_TYPE_NONE:			szTypeVal = "BUNDLE_TYPE_NONE";			break;
	case BUNDLE_TYPE_ANY:			szTypeVal = "BUNDLE_TYPE_ANY";			break;
	case BUNDLE_TYPE_STR:			szTypeVal = "BUNDLE_TYPE_STR";			break;
	case BUNDLE_TYPE_STR_ARRAY:		szTypeVal = "BUNDLE_TYPE_STR_ARRAY";	break;
	case BUNDLE_TYPE_BYTE:			szTypeVal = "BUNDLE_TYPE_BYTE";			break;
	case BUNDLE_TYPE_BYTE_ARRAY:	szTypeVal = "BUNDLE_TYPE_BYTE_ARRAY";	break;
	default:						szTypeVal = "Unknown Type";				break;
	}
	return szTypeVal;
}

/**
* @function 		BundleGetTypePropertyValue
* @description	 	Maps Types of given values to string.
* @parameter		nRet : result code returned
* @return 			Type represented as string
*/
char* BundleGetTypePropertyValue(int nRet)
{
	char *szTypeVal = NULL;
	switch ( nRet )
	{
	case BUNDLE_TYPE_ARRAY:			szTypeVal = "BUNDLE_TYPE_ARRAY";		break;
	case BUNDLE_TYPE_PRIMITIVE:		szTypeVal = "BUNDLE_TYPE_PRIMITIVE";	break;
	case BUNDLE_TYPE_MEASURABLE:	szTypeVal = "BUNDLE_TYPE_MEASURABLE";	break;
	default:						szTypeVal = "Unknown Type";				break;
	}
	return szTypeVal;
}

/**
* @function 		BundleGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* BundleGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case BUNDLE_ERROR_NONE:					szErrorVal = "BUNDLE_ERROR_NONE";					break;
	case BUNDLE_ERROR_OUT_OF_MEMORY:		szErrorVal = "BUNDLE_ERROR_OUT_OF_MEMORY";			break;
	case BUNDLE_ERROR_INVALID_PARAMETER:	szErrorVal = "BUNDLE_ERROR_INVALID_PARAMETER";		break;
	case BUNDLE_ERROR_KEY_NOT_AVAILABLE:	szErrorVal = "BUNDLE_ERROR_KEY_NOT_AVAILABLE";		break;
	case BUNDLE_ERROR_KEY_EXISTS:			szErrorVal = "BUNDLE_ERROR_KEY_EXISTS";				break;
	default:								szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}
/** @} */
