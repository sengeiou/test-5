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
#include "ITs-fido-client-common.h"

//& set: FidoClient
bool g_bCheckCb = false;
bool g_bAttestationCb = false;
bool g_bAuthHandle = false;
bool g_bmsgCheckCb = false;
static char *g_pjson_reg = "[ { \"header\": { \"upv\": { \"major\": 1, \"minor\": 0 },\"op\":\"Reg\", \"serverData\": \"nwV8EPqS5raZdAgH3GD9Z-ytCA9MkiiWaCsr1GHHNJ2yUh3HaV1HHxd4Z67FefJOD5sQYZvipfg5BavhdWPMecD2SH39aJixoXN9ZaNwRlcftJe9WbtPNDC9q5V9WX7Z5jCwkAwehcI\" }, \"challenge\": \"9pIcUwwrY5eD9o3OwfhkeHLnoIl0vaeJUbxSHMe_XgE\", \"username\":\"ryan\", \"policy\": { \"accepted\": [ [ { \"aaid\": [ \"0001#8001\" ] } ], [ { \"aaid\": [ \"53EC#3101\" ] } ] ] } } ]";
#define JSON_INVALID_STRING "\{\"improperjson\": []}"
/** @addtogroup itc-fido-client
*  @ingroup itc
*  @{
*/

GET_TC_TYPE g_eGet_TC_Type = TITLE;


/**
* @function 		fido_client_attestation_type_cb_p
* @description	 	Callback Function
* @parameter		void *fido_auth_attestation_type_e, void *user_data
* @return 			NA
*/
void fido_client_attestation_type_cb_p(fido_auth_attestation_type_e att_type, void *user_data)
{
	char *pszAtt = (char *) user_data;

	FPRINTF("[Line : %d][%s] reached inside fido_client_attestation_type_cb_p callback\\n", __LINE__, API_NAMESPACE);
	if ( strcmp(pszAtt,"DISCOVER RESPONSE") != 0 )
	{
		FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
		if ( g_pMainLoop )
		{
			g_main_loop_quit(g_pMainLoop);
		}
		return;
	}
	g_bAttestationCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @function 		fido_client_auth_list_cb_p
* @description	 	Callback Functionchar *pszTitle =  NULL;
* @parameter		void const fido_authenticator_h auth, void *user_data
* @return 			NA
*/
static void fido_client_auth_list_cb_p(const fido_authenticator_h auth, void *user_data)
{
	int nRet=0;
	char *pszTitle =  NULL;
	char *pszAaid =  NULL;
	char *pszDescription =  NULL;
	char *pszScheme =  NULL;
	fido_auth_algo_e get_algo = -1;
	fido_auth_user_verify_type_e user_ver = -1;
	fido_auth_key_protection_type_e key_protection = -1;
	fido_auth_attachment_hint_e attachment_hint = -1;
	char *pszTc_Display_type = NULL;
	fido_auth_tc_display_type_e tc_discplay = -1;
	char *pszIcon = NULL;
	fido_auth_matcher_protection_type_e matcher_protection = -1;

	const char *pszAttStr = "DISCOVER RESPONSE";

	if ( auth == NULL )
	{
		FPRINTF("[Line : %d][%s] Callback fido_client_auth_list_cb invoked auth == NULL \\n", __LINE__, API_NAMESPACE);
		g_bAuthHandle = false;
		return;
	}
	g_bAuthHandle = true;

	g_bCheckCb = true;
	g_bAttestationCb = false;

	FPRINTF("[Line : %d][%s] reached fido_client_auth_list_cb callback\\n", __LINE__, API_NAMESPACE);

	//check result
	int i=0;
	for(i=0; i<NUM_GET_TC_TYPE; ++i)
	{
		GET_TC_TYPE eGet_TC_Type = g_eGet_TC_Type;
		switch(eGet_TC_Type)
		{
			case TITLE:
				nRet = fido_authenticator_get_title(auth, &pszTitle);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_title API calls return  error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else if (pszTitle == NULL)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_title failed pszTitle = NULL , \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_title API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
					free(pszTitle);
				}
				break;	
			case AAID:
				nRet = fido_authenticator_get_aaid(auth, &pszAaid);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_aaid API calls return  error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else if (pszAaid == NULL)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_aaid failed paaid = NULL , \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_aaid API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
					free(pszAaid);
				}
				break;
			case DESCRIPTION:
				nRet = fido_authenticator_get_description(auth, &pszDescription);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_description API calls return  error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else if (pszDescription == NULL)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_description failed pDescription = NULL , \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_description API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
					free(pszDescription);
				}
				break;	
			case SCHEME:
				nRet = fido_authenticator_get_assertion_scheme(auth, &pszScheme);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_assertion_scheme API calls return  error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else if (pszScheme == NULL)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_assertion_scheme failed pszScheme = NULL , \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_assertion_scheme API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
					free(pszScheme);
				}
				break;	
			case ALGORITHM:
				nRet = fido_authenticator_get_algorithm(auth, &get_algo);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_algorithm API calls return  error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else if (get_algo == -1)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_algorithm failed get_algo = -1, \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_algorithm API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
				}
				break;	
			case VERIFICATION_METHOD:
				nRet = fido_authenticator_get_verification_method(auth, &user_ver);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_verification_method API calls return  error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else if (user_ver == -1)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_verification_method failed user_ver = -1, \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_verification_method API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
				}
				break;	
			case KEY_PROTECTION:
				nRet = fido_authenticator_get_key_protection_method(auth, &key_protection);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_key_protection_method API calls return  error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else if (key_protection == -1)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_key_protection_method failed key_protection = -1, \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_key_protection_method API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
				}
				break;
			case ATTACHMENT_HINT:
				nRet = fido_authenticator_get_attachment_hint(auth, &attachment_hint);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_attachment_hint API calls return  error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else if (attachment_hint == -1)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_attachment_hint failed attachment_hint = -1, \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_attachment_hint API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
				}
				break;
			case IS_SECOND_FACTOR:
				//Since API return bool value so it will either return true or false so fail condition cannot be checked
	// by return value so  we are checking it through int return value	
				nRet = fido_authenticator_get_is_second_factor_only(auth);
				if (nRet != true && nRet != false)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_is_second_factor_only API calls failed with return value = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_is_second_factor_only API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
				}
				break;
			case TC_DISPLAY_TYPE:
				nRet = fido_authenticator_get_tc_display_type(auth, &pszTc_Display_type);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_tc_display_type API calls return  error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else if (pszTc_Display_type == NULL)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_tc_display_type failed pszTc_Display_type = NULL , \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_tc_display_type API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
					free(pszTc_Display_type);
				}
				break;
			case TC_DISPLAY:
				nRet = fido_authenticator_get_tc_discplay(auth, &tc_discplay);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_tc_discplay API calls return  error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else if (tc_discplay == -1)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_tc_discplay failed tc_discplay = -1 , \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_tc_discplay API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
				}
				break;
			case ICON:
				nRet = fido_authenticator_get_icon(auth, &pszIcon);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_icon API calls return  error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else if (pszIcon == NULL)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_icon failed pszIcon = NULL , \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_icon API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
					free(pszIcon);
				}
				break;
			case MATCHER_PROTECTION_METHOD:
				nRet = fido_authenticator_get_matcher_protection_method(auth, &matcher_protection);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_matcher_protection_method API calls return  error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}
				else if (matcher_protection == -1)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_matcher_protection_method failed matcher_protection = -1, \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_get_matcher_protection_method API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
				}
				break;
			case ATTESTATION:

				nRet = fido_authenticator_foreach_attestation_type(auth, fido_client_attestation_type_cb_p, pszAttStr);
				if(nRet != FIDO_ERROR_NONE)
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_foreach_attestation_type API calls return error code = %s , \\n", __LINE__, API_NAMESPACE, FidoClientGetError(nRet));
				}

				else if(!g_bAttestationCb)
				{
					FPRINTF("[Line : %d][%s] fido_client_attestation_type_cb_p - Callback not invoked \\n", __LINE__, API_NAMESPACE);
				}
				else
				{
					FPRINTF("[Line : %d][%s] fido_authenticator_foreach_attestation_type API is Passed \\n", __LINE__, API_NAMESPACE);
					stArr_Key_Value[i].bResult = true;
				}
				break;
			default:
				break;
		}
	}

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
	return;
	

}
/**
 * @function 		ITs_fido_client_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_fido_client_startup(void)
{
	struct stat stBuff;
	int i=0;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	
	if ( !TCTCheckSystemInfoFeatureSupported(FIDOCLIENT_FEATURE, API_NAMESPACE) )
	{
		g_bFidoClientNotSupported = true;
		FPRINTF("[Line : %d][%s] TEST SUIT start-up: TCTCheckSystemInfoFeatureSupported = true\\n", __LINE__, API_NAMESPACE);
		return;
	}

	//initialize structure
	for(i=0; i<NUM_GET_TC_TYPE; ++i)
	{
		stArr_Key_Value[i].e_Get_TC_Type = i;
		stArr_Key_Value[i].bResult = false;
	}

	g_bCheckCb = false;
	g_bFidoClientCreation = true;
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_fido_client_startup\\n", __LINE__, API_NAMESPACE);

	// Launch fido-asm service daemon in advance
	bool is_supported = true;
	fido_uaf_is_supported(JSON_INVALID_STRING, &is_supported);
	
	return;
}


/**
 * @function 		ITs_fido_client_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_fido_client_cleanup(void)
{
	return;
}


/** @addtogroup itc-fido-client-testcases
*  @brief 		Integration testcases for module fido-client
*  @ingroup 	itc-fido-client
*  @{
*/
//& purpose: To get the  authenticator handle
//& type: auto
/**
* @testcase 			ITc_fidoclient_fido_foreach_authenticator_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			To get the  authenticator handle 			
* @scenario						
* @apicovered			fido_foreach_authenticator						
* @passcase				When fido_foreach_authenticator is successful.
* @failcase				If target API bfido_foreach_authenticator fails 
* @precondition
* @postcondition
*/
int ITc_fido_foreach_authenticator_p(void)
{
	START_TEST;
	g_eGet_TC_Type = MAX_ENUM;
	g_bCheckCb = false;
	g_bAuthHandle = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));

	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(!g_bAuthHandle)
	{
		FPRINTF("[Line : %d][%s] auth hanlde recieved in fido_client_auth_list_cb_p as NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Get the title for Authenticator 
//& type: auto
/**
* @testcase 			ITc_fidoclient_fido_authenticator_getTitle_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the title for Authenticator
* @scenario				
* @apicovered			fido_authenticator_get_title						
* @passcase				When fido_authenticator_get_title is successful.
* @failcase				If target API bundle_encode or bundle_decode fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fidoclient_fido_authenticator_getTitle_p(void)
{
	START_TEST;

	g_eGet_TC_Type = TITLE;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}

//& purpose: Get the aaid for Authenticator 
//& type: auto
/**
* @testcase 			ITc_fido_authenticator_get_aaid_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the aaid for Authenticator
* @scenario				fido_authenticator_get_aaid
* @apicovered			fido_authenticator_get_aaid						
* @passcase				When fido_authenticator_get_aaid is successful.
* @failcase				If target API bundle_encode or bundle_decode fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_authenticator_get_aaid_p(void)
{
	START_TEST;
	
	g_eGet_TC_Type = AAID;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}

//& purpose: Get the description for Authenticator 
//& type: auto
/**
* @testcase 			ITc_fidoclient_fido_authenticator_getdescription_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the description for Authenticator
* @scenario				
* @apicovered			fido_authenticator_get_description						
* @passcase				When fido_authenticator_get_description is successful.
* @failcase				If target API bundle_encode or bundle_decode fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fidoclient_fido_authenticator_getdescription_p(void)
{
	START_TEST;

	g_eGet_TC_Type = DESCRIPTION;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}

//& purpose: Get the scheme for Authenticator 
//& type: auto
/**
* @testcase 			ITc_fidoclient_fido_authenticator_getscheme_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the assertion scheme for Authenticator
* @scenario				
* @apicovered			fido_authenticator_get_assertion_scheme						
* @passcase				When fido_authenticator_get_assertion_scheme is successful.
* @failcase				If target API bundle_encode or bundle_decode fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fidoclient_fido_authenticator_getscheme_p(void)
{
	START_TEST;

	g_eGet_TC_Type = SCHEME;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}

//& purpose: Get the algorithm for Authenticator 
//& type: auto
/**
* @testcase 			ITc_fidoclient_fido_authenticator_getalgorithm_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the assertion scheme for Authenticator
* @scenario				
* @apicovered			fido_authenticator_get_algorithm						
* @passcase				When fido_authenticator_get_algorithm is successful.
* @failcase				If target API bundle_encode or bundle_decode fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fidoclient_fido_authenticator_getalgorithm_p(void)
{
	START_TEST;

	g_eGet_TC_Type = ALGORITHM;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}

//& purpose: Get the attestation_type for Authenticator
//& type: auto
/**
* @testcase 			ITc_fido_authenticator_foreach_attestation_type_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the attestation_type for Authenticator
* @scenario				Get the attestation_type for Authenticator
* @apicovered			fido_authenticator_foreach_attestation_type
* @passcase				When fido_authenticator_foreach_attestation_type is successful.
* @failcase				If target API bundle_encode or bundle_decode fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/

int ITc_fido_authenticator_foreach_attestation_type_p(void)
{
	START_TEST;

	g_eGet_TC_Type = ATTESTATION;
	g_bCheckCb = false;
	g_bAttestationCb = false;

	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(!g_bAttestationCb)
	{
		FPRINTF("[Line : %d][%s] fido_client_attestation_type_cb_p - Callback function not invoked \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;
	}

	return 0;
}

//& purpose: Get the verification method for Authenticator 
//& type: auto
/**
* @testcase 			ITc_fido_authenticator_get_verification_method_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the verification method for Authenticator 
* @scenario				Get the verification method for Authenticator 
* @apicovered			fido_authenticator_get_verification_method						
* @passcase				When fido_authenticator_get_verification_method is successful.
* @failcase				If target API fido_authenticator_get_verification_method fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_authenticator_get_verification_method_p(void)
{
	START_TEST;

	g_eGet_TC_Type = VERIFICATION_METHOD;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}


//& purpose: Get the key protection method for Authenticator 
//& type: auto
/**
* @testcase 			ITc_fido_authenticator_get_key_protection_method_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the key protection method for Authenticator
* @scenario				Get the key protection method for Authenticator
* @apicovered			fido_authenticator_get_key_protection_method						
* @passcase				When fido_authenticator_get_key_protection_method is successful.
* @failcase				If target API fido_authenticator_get_key_protection_method fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_authenticator_get_key_protection_method_p(void)
{
	START_TEST;
	
	g_eGet_TC_Type = KEY_PROTECTION;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}

//& purpose: Get the key protection method for Authenticator 
//& type: auto
/**
* @testcase 			ITc_fido_authenticator_get_attachment_hint_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the key protection method for Authenticator
* @scenario				Get the key protection method for Authenticator
* @apicovered			fido_authenticator_get_attachment_hint						
* @passcase				When fido_authenticator_get_attachment_hint is successful.
* @failcase				If target API fido_authenticator_get_attachment_hint fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_authenticator_get_attachment_hint_p(void)
{
	START_TEST;
	
	g_eGet_TC_Type = ATTACHMENT_HINT;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}

//& purpose: check whether the Authenticator is Second factor only which is supported by U2F standards.
//& type: auto
/**
* @testcase 			ITc_fido_authenticator_get_is_second_factor_only_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Check whether the Authenticator is Second factor only which is supported by U2F standards
* @scenario				Check whether the Authenticator is Second factor only which is supported by U2F standards
* @apicovered			fido_authenticator_get_is_second_factor_only						
* @passcase				When fido_authenticator_get_is_second_factor_only is successful.
* @failcase				If target API fido_authenticator_get_is_second_factor_only fails 
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_authenticator_get_is_second_factor_only_p(void)
{
	START_TEST;

	g_eGet_TC_Type = IS_SECOND_FACTOR;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}

//& purpose: Retrieves the Transaction Confirmation display content type of this Authenticator

//& type: auto
/**
* @testcase 			ITc_fido_authenticator_get_tc_display_type_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the Transaction Confirmation display content type of this Authenticator
* @scenario				Get the Transaction Confirmation display content type of this Authenticator
* @apicovered			fido_authenticator_get_tc_display_type						
* @passcase				When fido_authenticator_get_tc_display_type is successful.
* @failcase				If target API fido_authenticator_get_tc_display_type fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_authenticator_get_tc_display_type_p(void)
{
	START_TEST;

	g_eGet_TC_Type = TC_DISPLAY_TYPE;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}

//& purpose: Retrieves the Transaction Confirmation display type of this Authenticator. 
//& type: auto
/**
* @testcase 			ITc_fido_authenticator_get_tc_discplay_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the Transaction Confirmation display type of this Authenticator.
* @scenario				Get the Transaction Confirmation display type of this Authenticator.
* @apicovered			fido_authenticator_get_tc_discplay						
* @passcase				When fido_authenticator_get_tc_discplay is successful.
* @failcase				If target API fido_authenticator_get_tc_discplay fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_authenticator_get_tc_discplay_p(void)
{
	START_TEST;

	g_eGet_TC_Type = TC_DISPLAY;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}

//& purpose: Retrieves the icon of this Authenticator

//& type: auto
/**
* @testcase 			ITc_fido_authenticator_get_icon_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the icon of this Authenticator
* @scenario				Get the icon of this Authenticator
* @apicovered			fido_authenticator_get_icon						
* @passcase				When fido_authenticator_get_icon is successful.
* @failcase				If target API fido_authenticator_get_icon fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_authenticator_get_icon_p(void)
{
	START_TEST;

	g_eGet_TC_Type = ICON;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}
//& purpose: Gets the FIDO client vendor name.

//& type: auto
/**
* @testcase 			ITc_fido_get_client_vendor_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Gets the FIDO client vendor name
* @scenario				Gets the FIDO client vendor name
* @apicovered			fido_get_client_vendor						
* @passcase				When fido_get_client_vendor is successful.
* @failcase				If target API fido_get_client_vendor fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_get_client_vendor_p(void)
{
	START_TEST;
	
	char *pszVendor = NULL;
	
	int nRet = fido_get_client_vendor(&pszVendor);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_get_client_vendor", FidoClientGetError(nRet));
	if (pszVendor == NULL)
	{
		FPRINTF("[Line : %d][%s] fido_get_client_vendor failed pszVendor = NULL , \\n", __LINE__, API_NAMESPACE);
				
		return 1;
	}
	free(pszVendor);
	return 0;
}

//& purpose: Gets the FIDO client vendor version information

//& type: auto
/**
* @testcase 			ITc_fido_get_client_version_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Gets the FIDO client vendor version information
* @scenario				Gets the FIDO client vendor version information
* @apicovered			fido_get_client_version						
* @passcase				When fido_get_client_version is successful.
* @failcase				If target API fido_get_client_version fails 
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_get_client_version_p(void)
{
	START_TEST;
	
	int nClient_major_version = -1;
	int nClient_minor_version = -1;
	
	int nRet = fido_get_client_version(&nClient_major_version,&nClient_minor_version);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_get_client_version", FidoClientGetError(nRet));
	if ((nClient_minor_version == -1) || (nClient_major_version == -1))
	{
		FPRINTF("[Line : %d][%s] fido_get_client_version failed , \\n", __LINE__, API_NAMESPACE);
				
		return 1;
	}
	
	return 0;
}
//& purpose: Checks whether the FIDO message can be processed

//& type: auto
/**
* @testcase 			ITc_fido_uaf_is_supported_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Checks whether the FIDO message can be processed
* @scenario				Checks whether the FIDO message can be processed
* @apicovered			fido_uaf_is_supported						
* @passcase				When fido_uaf_is_supported is successful.
* @failcase				If target API fido_uaf_is_supported fails 
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_uaf_is_supported_p(void)
{
	START_TEST;
	bool is_supported = false;	
	
	int nRet = fido_uaf_is_supported(g_pjson_reg, &is_supported);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_uaf_is_supported", FidoClientGetError(nRet));
	//output parameter is boolean, which implies if the message (FIDO message in JSON format) can be handled by the device. This is device specific, so omitting output value check.
			
	return 0;
}

/**
* @function 		fido_client_process_cb_p
* @description	 	Callback Function
* @parameter		fido_error_e tizen_error_code, const char *uaf_response, void *user_data
* @return 			NA
*/
static void fido_client_process_cb_p(fido_error_e tizen_error_code, const char *uaf_response, void *user_data)
{
	if (tizen_error_code != 0)
	{
		FPRINTF("[Line : %d][%s] Callback fido_client_process_cb_p invoked; but tizen_error_code = %s \\n", __LINE__, API_NAMESPACE, FidoClientGetError(tizen_error_code));
		return;
	}
	if (uaf_response == NULL)
	{
		FPRINTF("[Line : %d][%s] Callback fido_client_process_cb_p invoked with uaf_response == NULL \\n", __LINE__, API_NAMESPACE);
		return;
	}
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
	g_bCheckCb = true;
	return;
	
}
//& purpose: Processes the given FIDO UAF message.

//& type: auto
/**
* @testcase 			ITc_fido_uaf_get_response_message_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Processes the given FIDO UAF message.
* @scenario				Processes the given FIDO UAF message.
* @apicovered			fido_uaf_get_response_message						
* @passcase				When fido_uaf_get_response_message is successful.
* @failcase				If target API fido_uaf_get_response_message fails 
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_uaf_get_response_message_p(void)
{
	START_TEST;	
	g_eGet_TC_Type = MAX_ENUM;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bCheckCb = false;
	int nTimeoutId = 0;
	nRet = fido_uaf_get_response_message(g_pjson_reg, NULL, fido_client_process_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_uaf_get_response_message", FidoClientGetError(nRet));
	RUN_POLLING_LOOP;
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] fido_uaf_get_response_message -Callback function not invoked  \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
		
	return 0;
}

/**
* @function 		fido_client_process_message_cb_p
* @description	 	Callback Function
* @parameter		fido_error_e tizen_error_code, const char *uaf_response, void *user_data
* @return 			NA
*/
static void fido_client_process_message_cb_p(fido_error_e tizen_error_code, const char *uaf_response, void *user_data)
{
	if (tizen_error_code != 0)
	{
		FPRINTF("[Line : %d][%s] Callback fido_client_process_message_cb_p invoked; but tizen_error_code = %s \\n", __LINE__, API_NAMESPACE, FidoClientGetError(tizen_error_code));
		return;
	}
	if (uaf_response == NULL)
	{
		FPRINTF("[Line : %d][%s] Callback fido_client_process_cb_p invoked with uaf_response == NULL \\n", __LINE__, API_NAMESPACE);
		return;
	}
	if (tizen_error_code == 0)
		{
			int ret = fido_uaf_set_server_result(FIDO_SERVER_STATUS_CODE_OK, uaf_response);
			if(ret != FIDO_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s]  fido_uaf_set_server_result  failed \\n", __LINE__, API_NAMESPACE);
				g_bmsgCheckCb = false;
				return;
			}
			else
			{
				g_bmsgCheckCb = true;	
			}
		
		}
	
	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
	
	return;
	
}
//& purpose: Processes the given FIDO UAF message.

//& type: auto
/**
* @testcase 			ITc_fido_uaf_set_server_result_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Processes the given FIDO UAF message.
* @scenario				Processes the given FIDO UAF message.
* @apicovered			fido_uaf_get_response_message,fido_uaf_set_server_result						
* @passcase				When fido_uaf_set_server_result is successful.
* @failcase				If target API fido_uaf_set_server_result fails or any precondition and postcondition API fails
* @precondition			fido_uaf_get_response_message is sucessfully executed
* @postcondition		
*/
int ITc_fido_uaf_set_server_result_p(void)
{
	START_TEST;
	g_eGet_TC_Type = MAX_ENUM;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bCheckCb = false;
	g_bmsgCheckCb = false;
	int nTimeoutId = 0;
	nRet = fido_uaf_get_response_message(g_pjson_reg, NULL, fido_client_process_message_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_uaf_get_response_message", FidoClientGetError(nRet));
	RUN_POLLING_LOOP;
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] fido_uaf_get_response_message -Callback function not invoked  \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(!g_bmsgCheckCb)
	{
		FPRINTF("[Line : %d][%s] fido_uaf_set_server_result failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
		
	return 0;
}

#if defined(MOBILE) || defined(TIZENIOT)//Starts MOBILE or TIZENIOT
//& purpose: Get the matcher protection method for Authenticator 
//& type: auto
/**
* @testcase 			ITc_fido_authenticator_get_matcher_protection_method_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Get the matcher protection method for Authenticator
* @scenario				Get matcher protection method for Authenticator
* @apicovered			fido_authenticator_get_matcher_protection_method						
* @passcase				When fido_authenticator_get_matcher_protection_method is successful.
* @failcase				If target API fido_authenticator_get_matcher_protection_method fails or any precondition and postcondition API fails
* @precondition			Authenticator Handle  must be created
* @postcondition		Authenticator Handle must be released
*/
int ITc_fido_authenticator_get_matcher_protection_method_p(void)
{
	START_TEST;
	
	g_eGet_TC_Type = MATCHER_PROTECTION_METHOD;
	g_bCheckCb = false;
	int nRet = fido_foreach_authenticator(fido_client_auth_list_cb_p, NULL);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_foreach_authenticator", FidoClientGetError(nRet));	
	if(!g_bCheckCb)
	{
		FPRINTF("[Line : %d][%s] Callback function not invoked in fido_foreach_authenticator \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nIndex = (int)g_eGet_TC_Type;
	if(stArr_Key_Value[nIndex].bResult == false)
	{
		return 1;	
	}
	
	return 0;
}

#endif  //End MOBILE or TIZENIOT

//& purpose: Gets the FIDO uaf version information

//& type: auto
/**
* @testcase 			ITc_fido_get_uaf_version_p
* @since_tizen			3.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Gets the FIDO uaf version information
* @scenario				Gets the FIDO uaf version information
* @apicovered			fido_get_uaf_version						
* @passcase				When fido_get_uaf_version is successful.
* @failcase				If target API fido_get_uaf_version fails 
* @precondition			
* @postcondition		
*/
/*int ITc_fido_get_uaf_version_p(void)
{
	START_TEST;
	
	int nUaf_major_version = -1;
	int nUaf_minor_version = -1;
	
	int nRet = fido_get_uaf_version(&nUaf_major_version,&nUaf_minor_version);
	PRINT_RESULT(FIDO_ERROR_NONE, nRet, "fido_get_uaf_version", FidoClientGetError(nRet));
	if ((nUaf_minor_version == -1) || (nUaf_major_version == -1))
	{
		FPRINTF("[Line : %d][%s] fido_get_uaf_version failed , \\n", __LINE__, API_NAMESPACE);
				
		return 1;
	}
	
	return 0;
}*/
