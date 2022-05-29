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
#include "CTs-platform-permission-common.h"
#include <oauth2.h>


#define OAUTH2_FEATURE	"http://tizen.org/feature/network.internet"
bool g_bOAuth2FeatureSupported = false;

/**
* @function         CTs_platform_permission_OAuth2_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_OAuth2_startup(void)
{
    struct stat stBuff;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
	if (remove(ERR_LOG))
	{
		FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
	}
    }

#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_OAuth2_startup\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_OAuth2_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_OAuth2_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_OAuth2_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

/**
* @function 			oauth2_token_cb_p
* @description 			Called when the token is received.
* @parameter	[IN]	response		Oauth2 Response
*				[IN]	user_data		user data
* @return				NA
*/
static void oauth2_token_cb_p (oauth2_response_h response, void* user_data)
{
	FPRINTF("[Line : %d][%s] oauth2_token_cb_p callback hit\\n", __LINE__, API_NAMESPACE);
	g_bOAuth2FeatureSupported = true;
	oauth2_response_destroy( response);
}


//& purpose:Checking "%http://tizen.org/privilege/internet" privilege
//& type: auto
/**
* @testcase			CTc_OAuth2_PrivilegeInternet_Request_Token
* @since_tizen		2.4
* @author			SRID(shekhar1.s)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Request OAuth 2.0 access token
* @apicovered		oauth2_manager_request_token
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_OAuth2_PrivilegeInternet_Request_Token(void)
{
	START_TEST;
	int nRet = -1;
	oauth2_manager_h hManager = NULL;
	oauth2_request_h hRequest = NULL;

	g_bOAuth2FeatureSupported = TCTCheckSystemInfoFeatureSupported(OAUTH2_FEATURE, API_NAMESPACE);
	if ( false == g_bOAuth2FeatureSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, OAUTH2_FEATURE);
		return 0;
	}
	nRet = oauth2_manager_create(&hManager);
	if(hManager == NULL)
	{
		FPRINTF("[Line : %d][%s] hManager is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_create", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_create(&hRequest);
	if(hRequest == NULL)
	{
		FPRINTF("[Line : %d][%s] hRequest is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_create", Oauth2InfoGetError(nRet));

	nRet = oauth2_manager_request_token( hManager, hRequest, oauth2_token_cb_p, NULL);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "oauth2_manager_request_token", Oauth2InfoGetError(nRet));

	return 0;
}

//& purpose:Checking "%http://tizen.org/privilege/internet" privilege
//& type: auto
/**
* @testcase			CTc_OAuth2_PrivilegeInternet_Authorization_Grant
* @since_tizen		2.4
* @author			SRID(shekhar1.s)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Request OAuth 2.0 access token
* @apicovered		oauth2_manager_request_authorization_grant
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
 */
int CTc_OAuth2_PrivilegeInternet_Authorization_Grant(void)
{
	START_TEST;
	int nRet = -1;

	oauth2_manager_h hManager = NULL;
	oauth2_request_h hRequest = NULL;

	g_bOAuth2FeatureSupported = TCTCheckSystemInfoFeatureSupported(OAUTH2_FEATURE, API_NAMESPACE);
	if ( false == g_bOAuth2FeatureSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, OAUTH2_FEATURE);
		return 0;
	}
	nRet = oauth2_manager_create(&hManager);
	if(hManager == NULL)
	{
		FPRINTF("[Line : %d][%s] hManager is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_create", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_create(&hRequest);
	if(hRequest == NULL)
	{
		FPRINTF("[Line : %d][%s] hRequest is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_create", Oauth2InfoGetError(nRet));

	nRet = oauth2_manager_request_authorization_grant( hManager, hRequest, oauth2_token_cb_p, NULL);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "oauth2_manager_request_token", Oauth2InfoGetError(nRet));

	nRet = oauth2_manager_destroy(hManager);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_destroy", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_destroy(hRequest);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_destroy", Oauth2InfoGetError(nRet));

	return 0;
}

//& purpose:Checking "%http://tizen.org/privilege/internet" privilege
//& type: auto
/**
 * @testcase			CTc_OAuth2_PrivilegeInternet_Request_Access_Token
 * @since_tizen		2.4
 * @author			SRID(shekhar1.s)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @scenario			Request OAuth 2.0 access token
 * @apicovered		oauth2_manager_request_access_token
 * @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
 * @precondition		NA
 * @postcondition	NA
 */
int CTc_OAuth2_PrivilegeInternet_Request_Access_Token(void)
{
	START_TEST;
	int nRet = -1;

	oauth2_manager_h hManager = NULL;
	oauth2_request_h hRequest = NULL;

	g_bOAuth2FeatureSupported = TCTCheckSystemInfoFeatureSupported(OAUTH2_FEATURE, API_NAMESPACE);
	if ( false == g_bOAuth2FeatureSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, OAUTH2_FEATURE);
		return 0;
	}
	nRet = oauth2_manager_create(&hManager);
	if(hManager == NULL)
	{
		FPRINTF("[Line : %d][%s] hManager is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_create", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_create(&hRequest);
	if(hRequest == NULL)
	{
		FPRINTF("[Line : %d][%s] hRequest is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_create", Oauth2InfoGetError(nRet));

	nRet = oauth2_manager_request_access_token( hManager, hRequest, oauth2_token_cb_p, NULL);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "oauth2_manager_request_access_token", Oauth2InfoGetError(nRet));

	nRet = oauth2_manager_destroy(hManager);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_destroy", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_destroy(hRequest);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_destroy", Oauth2InfoGetError(nRet));

	return 0;
}

//& purpose:Checking "%http://tizen.org/privilege/internet" privilege
//& type: auto
/**
 * @testcase			CTc_OAuth2_PrivilegeInternet_Refresh_Access_Token
 * @since_tizen		2.4
 * @author			SRID(shekhar1.s)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @scenario			Request OAuth 2.0 access token
 * @apicovered		oauth2_manager_refresh_access_token
 * @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
 * @precondition		NA
 * @postcondition	NA
 */
int CTc_OAuth2_PrivilegeInternet_Refresh_Access_Token(void)
{
	START_TEST;
	int nRet = -1;

	oauth2_manager_h hManager = NULL;
	oauth2_request_h hRequest = NULL;

	g_bOAuth2FeatureSupported = TCTCheckSystemInfoFeatureSupported(OAUTH2_FEATURE, API_NAMESPACE);
	if ( false == g_bOAuth2FeatureSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, OAUTH2_FEATURE);
		return 0;
	}
	nRet = oauth2_manager_create(&hManager);
	if(hManager == NULL)
	{
		FPRINTF("[Line : %d][%s] hManager is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_create", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_create(&hRequest);
	if(hRequest == NULL)
	{
		FPRINTF("[Line : %d][%s] hRequest is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_create", Oauth2InfoGetError(nRet));

	nRet = oauth2_manager_refresh_access_token( hManager, hRequest, oauth2_token_cb_p, NULL);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "oauth2_manager_refresh_access_token", Oauth2InfoGetError(nRet));

	nRet = oauth2_manager_destroy(hManager);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_destroy", Oauth2InfoGetError(nRet));

	nRet = oauth2_request_destroy(hRequest);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_request_destroy", Oauth2InfoGetError(nRet));

	return 0;
}

//& purpose:Checking "%http://tizen.org/privilege/internet" privilege
//& type: auto
/**
 * @testcase			CTc_OAuth2_PrivilegeInternet_Clear_Cookies
 * @since_tizen		2.4
 * @author			SRID(shekhar1.s)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @scenario			Request OAuth 2.0 access token
 * @apicovered		oauth2_manager_clear_cookies
 * @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
 * @precondition		NA
 * @postcondition	NA
 */
int CTc_OAuth2_PrivilegeInternet_Clear_Cookies(void)
{
	START_TEST;
	int nRet = -1;

	oauth2_manager_h hManager = NULL;

	g_bOAuth2FeatureSupported = TCTCheckSystemInfoFeatureSupported(OAUTH2_FEATURE, API_NAMESPACE);
	if ( false == g_bOAuth2FeatureSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, OAUTH2_FEATURE);
		return 0;
	}
	nRet = oauth2_manager_create(&hManager);
	if(hManager == NULL)
	{
		FPRINTF("[Line : %d][%s] hManager is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_create", Oauth2InfoGetError(nRet));

	nRet = oauth2_manager_clear_cookies( hManager);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "oauth2_manager_clear_cookies", Oauth2InfoGetError(nRet));

	nRet = oauth2_manager_destroy(hManager);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_destroy", Oauth2InfoGetError(nRet));

	return 0;
}

//& purpose:Checking "%http://tizen.org/privilege/internet" privilege
//& type: auto
/**
 * @testcase			CTc_OAuth2_PrivilegeInternet_Clear_Cache
 * @since_tizen		2.4
 * @author			SRID(shekhar1.s)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @scenario			Request OAuth 2.0 access token
 * @apicovered		oauth2_manager_clear_cache
 * @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
 * @precondition		NA
 * @postcondition	NA
 */
int CTc_OAuth2_PrivilegeInternet_Clear_Cache(void)
{
	START_TEST;
	int nRet = -1;

	oauth2_manager_h hManager = NULL;

	g_bOAuth2FeatureSupported = TCTCheckSystemInfoFeatureSupported(OAUTH2_FEATURE, API_NAMESPACE);
	if ( false == g_bOAuth2FeatureSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, OAUTH2_FEATURE);
		return 0;
	}
	nRet = oauth2_manager_create(&hManager);
	if(hManager == NULL)
	{
		FPRINTF("[Line : %d][%s] hManager is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_create", Oauth2InfoGetError(nRet));

	nRet = oauth2_manager_clear_cache( hManager);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "oauth2_manager_clear_cache", Oauth2InfoGetError(nRet));

	nRet = oauth2_manager_destroy(hManager);
	PRINT_RESULT(OAUTH2_ERROR_NONE, nRet, "oauth2_manager_destroy", Oauth2InfoGetError(nRet));

	return 0;
}
