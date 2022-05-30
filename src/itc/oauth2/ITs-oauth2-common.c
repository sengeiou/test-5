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
#include "ITs-oauth2-common.h"

/** @addtogroup itc-oauth2
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		Oauth2InfoGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* Oauth2InfoGetError(int nRet)
{
    char *szErrorVal = NULL;

    switch ( nRet )
    {
    case OAUTH2_ERROR_NONE:					szErrorVal = "OAUTH2_ERROR_NONE";						break;
    case OAUTH2_ERROR_INVALID_PARAMETER:	szErrorVal = "OAUTH2_ERROR_INVALID_PARAMETER";			break;
    case OAUTH2_ERROR_ALREADY_IN_PROGRESS:	szErrorVal = "OAUTH2_ERROR_ALREADY_IN_PROGRESS";		break;
    case OAUTH2_ERROR_OUT_OF_MEMORY:		szErrorVal = "OAUTH2_ERROR_OUT_OF_MEMORY";				break;
    case OAUTH2_ERROR_NOT_SUPPORTED:		szErrorVal = "OAUTH2_ERROR_NOT_SUPPORTED";				break;
    case OAUTH2_ERROR_PERMISSION_DENIED:	szErrorVal = "OAUTH2_ERROR_PERMISSION_DENIED";			break;
    case OAUTH2_ERROR_PARSE_FAILED:			szErrorVal = "OAUTH2_ERROR_PARSE_FAILED";				break;
    case OAUTH2_ERROR_NETWORK_ERROR:		szErrorVal = "OAUTH2_ERROR_NETWORK_ERROR";				break;
    case OAUTH2_ERROR_SERVER:				szErrorVal = "OAUTH2_ERROR_SERVER";						break;
    case OAUTH2_ERROR_USER_CANCELLED:		szErrorVal = "OAUTH2_ERROR_USER_CANCELLED";				break;
    case OAUTH2_ERROR_VALUE_NOT_FOUND:		szErrorVal = "OAUTH2_ERROR_VALUE_NOT_FOUND";			break;
    default:								szErrorVal = "Unknown Error";							break;
    }

    return szErrorVal;
}

/**
* @function 		Oauth2GrantType
* @description	 	Maps oauth2_grant_type_e enums to string values
* @parameter		nRet : oauth2_grant_type_e code returned
* @return 			equivalent string
*/
char* Oauth2GrantType(oauth2_grant_type_e nRet)
{
    char *szGrantVal = "Unknown Type";

    switch ( nRet )
    {
    case OAUTH2_GRANT_TYPE_AUTH_CODE:			szGrantVal = "OAUTH2_GRANT_TYPE_AUTH_CODE";				break;
    case OAUTH2_GRANT_TYPE_PASSWORD:			szGrantVal = "OAUTH2_GRANT_TYPE_PASSWORD";				break;
    case OAUTH2_GRANT_TYPE_CLIENT_CREDENTIALS:	szGrantVal = "OAUTH2_GRANT_TYPE_CLIENT_CREDENTIALS";	break;
    case OAUTH2_GRANT_TYPE_REFRESH:				szGrantVal = "OAUTH2_GRANT_TYPE_REFRESH";				break;
    }

    return szGrantVal;
}

/**
* @function 		Oauth2ResponseType
* @description	 	Maps oauth2_response_type_e enums to string values
* @parameter		nRet : oauth2_response_type_e code returned
* @return 			equivalent string
*/
char* Oauth2ResponseType(oauth2_response_type_e nRet)
{
    char *szResponseVal = "Unknown Type";

    switch ( nRet )
    {
    case OAUTH2_RESPONSE_TYPE_CODE:			szResponseVal = "OAUTH2_RESPONSE_TYPE_CODE";		break;
    case OAUTH2_RESPONSE_TYPE_TOKEN:		szResponseVal = "OAUTH2_RESPONSE_TYPE_TOKEN";		break;
    }

    return szResponseVal;
}

/**
* @function 		Oauth2GetAuthType
* @description	 	Maps oauth2_client_authentication_type_e enums to string values
* @parameter		nRet : oauth2_client_authentication_type_e code returned
* @return 			equivalent string
*/
char* Oauth2GetAuthType(oauth2_client_authentication_type_e nRet)
{
    char *szAuthVal = "Unknown Type";

    switch (nRet)
    {
    case OAUTH2_CLIENT_AUTHENTICATION_TYPE_BASIC:			szAuthVal = "OAUTH2_CLIENT_AUTHENTICATION_TYPE_BASIC";			break;
    case OAUTH2_CLIENT_AUTHENTICATION_TYPE_DIGEST:			szAuthVal = "OAUTH2_CLIENT_AUTHENTICATION_TYPE_DIGEST";			break;
    case OAUTH2_CLIENT_AUTHENTICATION_TYPE_REQUEST_BODY:	szAuthVal = "OAUTH2_CLIENT_AUTHENTICATION_TYPE_REQUEST_BODY";	break;
    }

    return szAuthVal;
}

/** @} */