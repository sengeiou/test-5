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
#include "ITs-smartcard-common.h"

//Add helper function definitions here

/**
 * @function 		SmartcardGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* SmartcardGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case SMARTCARD_ERROR_NONE:						szErrorVal = "SMARTCARD_ERROR_NONE";				break;
		case SMARTCARD_ERROR_GENERAL:					szErrorVal = "SMARTCARD_ERROR_GENERAL";				break;
		case SMARTCARD_ERROR_IO_ERROR:					szErrorVal = "SMARTCARD_ERROR_IO_ERROR";			break;
		case SMARTCARD_ERROR_NO_SUCH_ELEMENT:			szErrorVal = "SMARTCARD_ERROR_NO_SUCH_ELEMENT";		break;
		case SMARTCARD_ERROR_ILLEGAL_STATE:				szErrorVal = "SMARTCARD_ERROR_ILLEGAL_STATE";		break;
		case SMARTCARD_ERROR_INVALID_PARAMETER:			szErrorVal = "SMARTCARD_ERROR_INVALID_PARAMETER";	break;
		case SMARTCARD_ERROR_ILLEGAL_REFERENCE:			szErrorVal = "SMARTCARD_ERROR_ILLEGAL_REFERENCE";	break;
		case SMARTCARD_ERROR_OPERATION_NOT_SUPPORTED:	szErrorVal = "SMARTCARD_ERROR_OPERATION_NOT_SUPPORTED";break;
		case SMARTCARD_ERROR_PERMISSION_DENIED:			szErrorVal = "SMARTCARD_ERROR_PERMISSION_DENIED";	break;
		case SMARTCARD_ERROR_CHANNEL_NOT_AVAILABLE:		szErrorVal = "SMARTCARD_ERROR_CHANNEL_NOT_AVAILABLE";break;
		case SMARTCARD_ERROR_NOT_INITIALIZED:			szErrorVal = "SMARTCARD_ERROR_NOT_INITIALIZED";		break;
		case SMARTCARD_ERROR_NOT_SUPPORTED:				szErrorVal = "SMARTCARD_ERROR_NOT_SUPPORTED";		break;
		case SMARTCARD_ERROR_OUT_OF_MEMORY:				szErrorVal = "SMARTCARD_ERROR_OUT_OF_MEMORY";		break;
		default:										szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}
