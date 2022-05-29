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
#include "ITs-oauth2-common.h"

//& set: Oauth2Request

/** @addtogroup itc-oauth2
* @ingroup		itc
* @{
*/

oauth2_request_h g_hRequest = NULL;

/**
* @function 		ITs_oauth2_request_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
 */
void ITs_oauth2_request_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	FPRINTF("[Line : %d][%s] Start-up: Oauth2\\n", __LINE__, API_NAMESPACE);

	g_bIsRequestHandleCreated = false;

	int nRet = oauth2_request_create(&g_hRequest);
	if ( (nRet != OAUTH2_ERROR_NONE) || (g_hRequest == NULL))
	{
		FPRINTF("[Line : %d][%s] oauth2_request_create failed in start-up\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		g_bIsRequestHandleCreated = true;
	}

	return;
}

/**
* @function 		ITs_oauth2_request_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
 */
void ITs_oauth2_request_cleanup(void)
{
	FPRINTF("[Line : %d][%s] Clean-up: Oauth2\\n", __LINE__, API_NAMESPACE);

	if ( g_bIsRequestHandleCreated )
	{
		int nRet = oauth2_request_destroy(g_hRequest);
		if ( nRet != OAUTH2_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] oauth2_request_destroy failed in clean-up\\n", __LINE__, API_NAMESPACE);
		}
	}

	g_hRequest = NULL;

 	return;
}

/** @addtogroup	itc-oauth2-testcases
* @brief 		Integration testcases for module oauth2
* @ingroup		itc-oauth2
* @{
*/

/**
* @testcase 			ITc_oauth2_request_set_get_auth_end_point_url_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request set & get auth end point URL
* @scenario				oauth2_request_set_auth_end_point_url\n
*						oauth2_request_get_auth_end_point_url
* @apicovered			oauth2_request_set_auth_end_point_url, oauth2_request_get_auth_end_point_url
* @passcase				When oauth2_request_set_auth_end_point_url & oauth2_request_get_auth_end_point_url is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request set and get auth end point URL
//& type: auto
int ITc_oauth2_request_set_get_auth_end_point_url_p(void)
{
 	START_TEST;

	char pszSetAuthUrl[] = "www.tizen.org";
	char* pszGetAuthUrl = NULL;

	int nRet = oauth2_request_set_auth_end_point_url(g_hRequest, pszSetAuthUrl);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_auth_end_point_url", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_auth_end_point_url(g_hRequest, &pszGetAuthUrl);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_auth_end_point_url", Oauth2InfoGetError(nRet));
	if ( pszGetAuthUrl == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetAuthUrl is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( strcmp(pszSetAuthUrl, pszGetAuthUrl) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_auth_end_point_url return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetAuthUrl, pszSetAuthUrl);
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_token_end_point_url_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request set & get token end point URL
* @scenario				oauth2_request_set_token_end_point_url\n
*						oauth2_request_get_token_end_point_url
* @apicovered			oauth2_request_set_token_end_point_url, oauth2_request_get_token_end_point_url
* @passcase				When oauth2_request_set_token_end_point_url & oauth2_request_get_token_end_point_url is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request set & get token end point URL
//& type: auto
int ITc_oauth2_request_set_get_token_end_point_url_p(void)
{
 	START_TEST;

	char pszSetTokenUrl[] = "www.tizen.org";
	char* pszGetTokenUrl = NULL;

	int nRet = oauth2_request_set_token_end_point_url(g_hRequest, pszSetTokenUrl);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_token_end_point_url", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_token_end_point_url(g_hRequest, &pszGetTokenUrl);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_token_end_point_url", Oauth2InfoGetError(nRet));
	if ( pszGetTokenUrl == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetTokenUrl is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( strcmp(pszSetTokenUrl, pszGetTokenUrl) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_token_end_point_url return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetTokenUrl, pszSetTokenUrl);
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_redirection_url_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request set & get re-directional URL
* @scenario				oauth2_request_set_redirection_url\n
*						oauth2_request_get_redirection_url
* @apicovered			oauth2_request_set_redirection_url, oauth2_request_get_redirection_url
* @passcase				When oauth2_request_set_redirection_url & oauth2_request_get_redirection_url is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request set & get re-directional URL
//& type: auto
int ITc_oauth2_request_set_get_redirection_url_p(void)
{
 	START_TEST;

	char pszSetRedUrl[] = "www.tizen.org";
	char* pszGetRedUrl = NULL;

	int nRet = oauth2_request_set_redirection_url(g_hRequest, pszSetRedUrl);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_redirection_url", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_redirection_url(g_hRequest, &pszGetRedUrl);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_redirection_url", Oauth2InfoGetError(nRet));
	if ( pszGetRedUrl == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetRedUrl is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( strcmp(pszSetRedUrl, pszGetRedUrl) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_redirection_url return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetRedUrl, pszSetRedUrl);
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_refresh_token_url_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to set & get refresh token URL
* @scenario				oauth2_request_set_refresh_token_url\n
*						oauth2_request_get_refresh_token_url
* @apicovered			oauth2_request_set_refresh_token_url, oauth2_request_get_refresh_token_url
* @passcase				When oauth2_request_set_refresh_token_url & oauth2_request_get_refresh_token_url is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to set & get refresh token URL
//& type: auto
int ITc_oauth2_request_set_get_refresh_token_url_p(void)
{
 	START_TEST;

	char pszSetRefUrl[] = "www.tizen.org";
	char* pszGetRefUrl = NULL;

	int nRet = oauth2_request_set_refresh_token_url(g_hRequest, pszSetRefUrl);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_refresh_token_url", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_refresh_token_url(g_hRequest, &pszGetRefUrl);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_refresh_token_url", Oauth2InfoGetError(nRet));
	if ( pszGetRefUrl == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetRefUrl is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( strcmp(pszSetRefUrl, pszGetRefUrl) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_refresh_token_url return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetRefUrl, pszSetRefUrl);
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_refresh_token_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to set & get refresh token
* @scenario				oauth2_request_set_refresh_token\n
*						oauth2_request_get_refresh_token
* @apicovered			oauth2_request_set_refresh_token, oauth2_request_get_refresh_token
* @passcase				When oauth2_request_set_refresh_token & oauth2_request_get_refresh_token is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to set & get refresh token
//& type: auto
int ITc_oauth2_request_set_get_refresh_token_p(void)
{
 	START_TEST;

	char pszSetRefToken[] = "refresh_token";
	char* pszGetRefToken = NULL;

	int nRet = oauth2_request_set_refresh_token(g_hRequest, pszSetRefToken);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_refresh_token", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_refresh_token(g_hRequest, &pszGetRefToken);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_refresh_token", Oauth2InfoGetError(nRet));
	if ( pszGetRefToken == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetRefToken is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( pszGetRefToken == NULL || strcmp(pszSetRefToken, pszGetRefToken) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_refresh_token return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetRefToken, pszSetRefToken);
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_response_type_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to set & get response type
* @scenario				oauth2_request_set_response_type\n
*						oauth2_request_get_response_type
* @apicovered			oauth2_request_set_response_type, oauth2_request_get_response_type
* @passcase				When oauth2_request_set_response_type & oauth2_request_get_response_type is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to set & get response type
//& type: auto
int ITc_oauth2_request_set_get_response_type_p(void)
{
 	START_TEST;

	oauth2_response_type_e setType[] = {
		OAUTH2_RESPONSE_TYPE_CODE,
		OAUTH2_RESPONSE_TYPE_TOKEN
	};
	int enum_size = sizeof(setType) / sizeof(setType[0]);
	int enum_counter = 0;

	oauth2_request_h hRequest = NULL;
	oauth2_response_type_e getType;

	for ( enum_counter = 0; enum_counter < enum_size; enum_counter++ )
	{
		int nRet = oauth2_request_create(&hRequest);
		PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_create", Oauth2InfoGetError(nRet));

		nRet = oauth2_request_set_response_type(hRequest, setType[enum_counter]);
		PRINT_RESULT_CLEANUP(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_response_type", Oauth2InfoGetError(nRet), oauth2_request_destroy(hRequest));

		nRet = oauth2_request_get_response_type(hRequest, &getType);
		PRINT_RESULT_CLEANUP(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_response_type", Oauth2InfoGetError(nRet), oauth2_request_destroy(hRequest));

		if ( getType != setType[enum_counter] )
		{
			FPRINTF("[Line : %d][%s] oauth2_request_get_response_type return value %s mismatched with set value is: %s\\n", __LINE__, API_NAMESPACE, Oauth2ResponseType(getType), Oauth2ResponseType(setType[enum_counter]));
			oauth2_request_destroy(hRequest);
			return 1;
		}

		nRet = oauth2_request_destroy(hRequest);
		PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_destroy", Oauth2InfoGetError(nRet));
	}

	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_client_id_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to set & get client id
* @scenario				oauth2_request_set_client_id\n
*						oauth2_request_get_client_id
* @apicovered			oauth2_request_set_client_id, oauth2_request_get_client_id
* @passcase				When oauth2_request_set_client_id & oauth2_request_get_client_id is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to set & get client id
//& type: auto
int ITc_oauth2_request_set_get_client_id_p(void)
{
	START_TEST;

	char pszSetClientId[] = "client_id";
	char* pszGetClientId = NULL;

	int nRet = oauth2_request_set_client_id(g_hRequest, pszSetClientId);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_client_id", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_client_id(g_hRequest, &pszGetClientId);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_client_id", Oauth2InfoGetError(nRet));
	if ( pszGetClientId == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetClientId is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( strcmp(pszSetClientId, pszGetClientId) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_client_id return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetClientId, pszSetClientId);
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_client_secret_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to set & get client secret
* @scenario				oauth2_request_set_client_secret\n
*						oauth2_request_get_client_secret
* @apicovered			oauth2_request_set_client_secret, oauth2_request_get_client_secret
* @passcase				When oauth2_request_set_client_secret & oauth2_request_get_client_secret is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to set & get client secret
//& type: auto
int ITc_oauth2_request_set_get_client_secret_p(void)
{
	START_TEST;

	char pszSetClientSec[] = "client_id";
	char* pszGetClientSec = NULL;

	int nRet = oauth2_request_set_client_secret(g_hRequest, pszSetClientSec);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_client_secret", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_client_secret(g_hRequest, &pszGetClientSec);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_client_secret", Oauth2InfoGetError(nRet));
	if ( pszGetClientSec == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetClientSec is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( pszGetClientSec == NULL || strcmp(pszSetClientSec, pszGetClientSec) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_client_secret return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetClientSec, pszSetClientSec);
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_client_authentication_type_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to set client authentication type
* @scenario				oauth2_request_set_client_authentication_type
* @apicovered			oauth2_request_set_client_authentication_type
* @passcase				When oauth2_request_set_client_authentication_type is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to set client authentication type
//& type: auto
int ITc_oauth2_request_set_client_authentication_type_p(void)
{
	START_TEST;

	oauth2_client_authentication_type_e authType[] = {
		OAUTH2_CLIENT_AUTHENTICATION_TYPE_BASIC,
		OAUTH2_CLIENT_AUTHENTICATION_TYPE_DIGEST,
		OAUTH2_CLIENT_AUTHENTICATION_TYPE_REQUEST_BODY
	};

	int enum_size = sizeof(authType) / sizeof(authType[0]);
	int enum_counter = 0;

	oauth2_request_h hRequest = NULL;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++)
	{
		int nRet = oauth2_request_create(&hRequest);
		PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_create", Oauth2InfoGetError(nRet));

		nRet = oauth2_request_set_client_authentication_type(hRequest, authType[enum_counter]);
		PRINT_RESULT_CLEANUP(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_client_authentication_type", Oauth2InfoGetError(nRet), oauth2_request_destroy(hRequest));

		nRet = oauth2_request_destroy(hRequest);
		PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_destroy", Oauth2InfoGetError(nRet));
	}

	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_scope_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to set & get scope
* @scenario				oauth2_request_set_scope\n
*						oauth2_request_get_scope
* @apicovered			oauth2_request_set_scope, oauth2_request_get_scope
* @passcase				When oauth2_request_set_scope & oauth2_request_get_scope is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to set & get scope
//& type: auto
int ITc_oauth2_request_set_get_scope_p(void)
{
	START_TEST;

	char pszSetScope[] = "client_scope";
	char* pszGetScope = NULL;

	int nRet = oauth2_request_set_scope(g_hRequest, pszSetScope);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_scope", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_scope(g_hRequest, &pszGetScope);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_scope", Oauth2InfoGetError(nRet));
	if ( pszGetScope == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetScope is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if (strcmp(pszSetScope, pszGetScope) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_scope return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetScope, pszSetScope);
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_state_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to set & get state
* @scenario				oauth2_request_set_state\n
*						oauth2_request_get_state
* @apicovered			oauth2_request_set_state, oauth2_request_get_state
* @passcase				When oauth2_request_set_state & oauth2_request_get_state is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to set & get state
//& type: auto
int ITc_oauth2_request_set_get_state_p(void)
{
	START_TEST;

	char pszSetState[] = "client_state";
	char* pszGetState = NULL;

	int nRet = oauth2_request_set_state(g_hRequest, pszSetState);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_state", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_state(g_hRequest, &pszGetState);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_state", Oauth2InfoGetError(nRet));
	if ( pszGetState == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetState is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if (strcmp(pszSetState, pszGetState) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_state return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetState, pszSetState);
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_grant_type_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to set & get grant type
* @scenario				oauth2_request_set_grant_type\n
*						oauth2_request_get_grant_type
* @apicovered			oauth2_request_set_grant_type, oauth2_request_get_grant_type
* @passcase				When oauth2_request_set_grant_type & oauth2_request_get_grant_type is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to set & get grant type
//& type: auto
int ITc_oauth2_request_set_get_grant_type_p(void)
{
	START_TEST;

	oauth2_grant_type_e setGType[] ={
		OAUTH2_GRANT_TYPE_AUTH_CODE,
		OAUTH2_GRANT_TYPE_PASSWORD,
		OAUTH2_GRANT_TYPE_CLIENT_CREDENTIALS,
		OAUTH2_GRANT_TYPE_REFRESH
	};
	oauth2_grant_type_e getGType;
	oauth2_request_h hRequest = NULL;

	int enum_size = sizeof(setGType) / sizeof(setGType[0]), enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++)
	{
		int nRet = oauth2_request_create(&hRequest);
		PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_create", Oauth2InfoGetError(nRet));

		nRet = oauth2_request_set_grant_type(hRequest, setGType[enum_counter]);
		PRINT_RESULT_CLEANUP(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_grant_type", Oauth2InfoGetError(nRet), oauth2_request_destroy(hRequest));

		nRet = oauth2_request_get_grant_type(hRequest, &getGType);
		PRINT_RESULT_CLEANUP(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_grant_type", Oauth2InfoGetError(nRet), oauth2_request_destroy(hRequest));

		if ( getGType != setGType[enum_counter] )
		{
			FPRINTF("[Line : %d][%s] oauth2_request_get_grant_type return value %s mismatched with set value is: %s\\n", __LINE__, API_NAMESPACE, Oauth2GrantType(getGType), Oauth2GrantType(setGType[enum_counter]));
			oauth2_request_destroy(hRequest);
			return 1;
		}

		nRet = oauth2_request_destroy(hRequest);
		PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_destroy", Oauth2InfoGetError(nRet));
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_authorization_code_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to set & get authorization code
* @scenario				oauth2_request_set_authorization_code\n
*						oauth2_request_get_authorization_code
* @apicovered			oauth2_request_set_authorization_code, oauth2_request_get_authorization_code
* @passcase				When oauth2_request_set_authorization_code & oauth2_request_get_authorization_code is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to set & get authorization code
//& type: auto
int ITc_oauth2_request_set_get_authorization_code_p(void)
{
	START_TEST;

	char pszSetAuthCode[] = "authorization_code";
	char* pszGetAuthCode = NULL;

	int nRet = oauth2_request_set_authorization_code(g_hRequest, pszSetAuthCode);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_authorization_code", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_authorization_code(g_hRequest, &pszGetAuthCode);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_authorization_code", Oauth2InfoGetError(nRet));
	if ( pszGetAuthCode == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetAuthCode is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( strcmp(pszSetAuthCode, pszGetAuthCode) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_authorization_code return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetAuthCode, pszSetAuthCode);
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_user_name_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to set & get user name
* @scenario				oauth2_request_set_user_name\n
*						oauth2_request_get_user_name
* @apicovered			oauth2_request_set_user_name, oauth2_request_get_user_name
* @passcase				When oauth2_request_set_user_name & oauth2_request_get_user_name is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to set & get user name
//& type: auto
int ITc_oauth2_request_set_get_user_name_p(void)
{
	START_TEST;

	char pszSetUserName[] = "user_name";
	char* pszGetUserName = NULL;

	int nRet = oauth2_request_set_user_name(g_hRequest, pszSetUserName);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_user_name", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_user_name(g_hRequest, &pszGetUserName);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_user_name", Oauth2InfoGetError(nRet));
	if ( pszGetUserName == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetUserName is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if (strcmp(pszSetUserName, pszGetUserName) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_user_name return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetUserName, pszSetUserName);
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_set_get_password_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to set & get password
* @scenario				oauth2_request_set_password\n
*						oauth2_request_get_password
* @apicovered			oauth2_request_set_password, oauth2_request_get_password
* @passcase				When oauth2_request_set_password & oauth2_request_get_password is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to set & get password
//& type: auto
int ITc_oauth2_request_set_get_password_p(void)
{
	START_TEST;

	char pszSetPwd[] = "password";
	char* pszGetPwd = NULL;

	int nRet = oauth2_request_set_password(g_hRequest, pszSetPwd);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_set_password", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_password(g_hRequest, &pszGetPwd);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_password", Oauth2InfoGetError(nRet));
	if ( pszGetPwd == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetPwd is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if (strcmp(pszSetPwd, pszGetPwd) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_password return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetPwd, pszSetPwd);
		return 1;
	}
	return 0;
}

/**
* @testcase 			ITc_oauth2_request_add_get_custom_data_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Request to add & get custom data
* @scenario				oauth2_request_add_custom_data\n
*						oauth2_request_get_custom_data
* @apicovered			oauth2_request_add_custom_data, oauth2_request_get_custom_data
* @passcase				When oauth2_request_add_custom_data & oauth2_request_get_custom_data is successful and return valid data.
* @failcase				If target API fails or return invalid value.
* @precondition			None
* @postcondition		None
*/
//& purpose: Request to add & get custom data
//& type: auto
int ITc_oauth2_request_add_get_custom_data_p(void)
{
	START_TEST;

	char pszCKey[] = "custom_key";
	char pszCVal[] = "custom_value";
	char* pszGetCustData = NULL;

	int nRet = oauth2_request_add_custom_data(g_hRequest, pszCKey, pszCVal);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_add_custom_data", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_get_custom_data(g_hRequest, pszCKey, &pszGetCustData);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_get_custom_data", Oauth2InfoGetError(nRet));
	if ( pszGetCustData == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetCustData is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if (strcmp(pszCVal, pszGetCustData) != 0 )
	{
		FPRINTF("[Line : %d][%s] oauth2_request_get_custom_data return value %s mismatched with set value %s\\n", __LINE__, API_NAMESPACE, pszGetCustData, pszCVal);
		return 1;
	}
	return 0;
}

/** @}*/ //end of itc-oauth2
/** @}*/ //end of itc-oauth2-testcases
