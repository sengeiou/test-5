//
// Copyright (c)2014 Samsung Electronics Co., Ltd.
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
#include "ITs-accounts-svc-common.h"
//& set: accountsSvc

/** @addtogroup itc-accounts-svc
*  @ingroup itc
*  @{
*/

account_h g_account;
int g_AccId = -1;
account_capability_state_e g_capability_state;
char g_szAppID[BUFFERSIZE] = {0};
char g_szLocale[BUFFER] = {0};
char g_szLabel[BUFFER] = {0};
char g_szProviderFeature[BUFFERSIZE] = {0};
char g_szProviderFeatureArr[10][BUFFERSIZE];
char *g_pszValue = NULL;
char *g_event_type = NULL;
bool g_bAccountTypeCB = false;
int g_nPackageIdCB = 0;
bool g_bAccountCB = false;
bool g_bSubscribeNotification = false;
bool g_bAccountCreation = false;
bool g_bLabelMatch = false;
bool g_bAccountFeatureSupported = false;
char g_pstrAppId[CONFIG_VALUE_LEN_MAX] = {0};
static int g_nProviderCount = 0;
static GMainLoop *mainloop;
char g_eProviderFeature[10][BUFFERSIZE] = {CALENDAR_CAPABILITY, CONTACT_CAPABILITY};

tizen_profile_t profile;

static inline tizen_profile_t get_tizen_profile()
{
	char *profileName = NULL;

	if (__builtin_expect(profile != _PROFILE_UNKNOWN, 1))
		return profile;

	system_info_get_platform_string("http://tizen.org/feature/profile", &profileName);

	/* To pass the checking of g_ir */
	if (!profileName)
		return _PROFILE_UNKNOWN;

	switch (*profileName) {
		case 'm':
			case 'M':
			profile = _PROFILE_MOBILE;
		break;
		case 'w':
			case 'W':
			profile = _PROFILE_WEARABLE;
		break;
		case 't':
			case 'T':
			profile = _PROFILE_TV;
		break;
		case 'i':
			case 'I':
			profile = _PROFILE_IVI;
		break;
		default: // common or unknown ==> ALL ARE COMMON.
			profile = _PROFILE_COMMON;
	}

	free(profileName);
	return profile;
}


/**
* @function 		ITs_accounts_svc_startup
* @description	 	Called before each test. creates a account handle
* @parameter		NA
* @return 			NA
*/
void ITs_accounts_svc_startup(void)
{
	struct stat stBuff;
	g_bAccountNotSupported = false;
	g_bAccountMismatch = false;

	if ( stat(ERR_LOG, &stBuff)== 0 )
	{
		remove(ERR_LOG);
	}
	#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Accounts_Svc_p\\n", __LINE__, API_NAMESPACE);
	#endif

	bool bFeatureAccount  = TCTCheckSystemInfoFeatureSupported(ACCOUNT_FEATURE, API_NAMESPACE);
	int nRet = account_create(&g_account);

	if(!bFeatureAccount)
	{
		if(nRet == ACCOUNT_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] account_create() returned %s error for unsupported feature :success \\n", __LINE__,
				API_NAMESPACE, AccManagerGetErrorMSG(nRet));
			g_bAccountNotSupported = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] account_create() returned %s error for unsupported feature, error mismatch :Failure \\n",
			 __LINE__, API_NAMESPACE, AccManagerGetErrorMSG(nRet));
			g_bAccountMismatch = true;
		}

		return;
	}

	if ( nRet != ACCOUNT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] account_create failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AccManagerGetErrorMSG(nRet));
		g_bAccountCreation = false;
		return;
	}

	if(g_account == NULL)
	{
		FPRINTF("[Line : %d][%s] account_create failed, g_account is NULL\\n", __LINE__, API_NAMESPACE);
		g_bAccountCreation = false;
		return;
	}
	//Initialize APPID value from configuration file
	memset(g_pstrAppId, 0, sizeof(g_pstrAppId));
	strncpy(g_pstrAppId, APPID, strlen(APPID)+1);
	g_bAccountCreation = true;
	return;
}

/**
* @function 		ITs_accounts_svc_cleanup
* @description	 	Called after each test destroy the created account handle
* @parameter		NA
* @return 			NA
*/
void ITs_accounts_svc_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Accounts_Svc_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_bAccountCreation )
	{
		int nRet = account_destroy(g_account);
		if ( nRet != ACCOUNT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] account_destroy failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AccManagerGetErrorMSG(nRet));
		}
		g_account = NULL;
		g_bAccountCreation = false;
	}
	return;
}

/**
* @function 		AccountTimeout
* @description	 	Called if some callback is not invoked for a particular BundleTimeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean AccountTimeout(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	FPRINTF("[Line : %d][%s]Callback AccountTimeout\\n", __LINE__, API_NAMESPACE);
	return false;
}

/**
* @function 		AccountCallback
* @description	 	Called once for each account handle from database
* @parameter		account_h: Account Handle, user_data: User data sent to callback
* @return 			bool: Status of Callback
*/
static bool AccountCallback(account_h account, void *user_data)
{
	if(account == NULL)
	{
		FPRINTF("[Line : %d][%s] account is NULL in AccountCallback callback\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	if ( account != NULL )
	{
		g_bAccountCB = true;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] reached AccountCallback callback\\n", __LINE__, API_NAMESPACE);
#endif

	char *pszGetUserName = NULL;
	int nRet = account_get_user_name(g_account, &pszGetUserName);
	if ( nRet != ACCOUNT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] account_get_user_name failed in AccountCallback\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	if ( pszGetUserName != NULL )
	{
		free(pszGetUserName);
		pszGetUserName = NULL;
	}

	char *pszGetDomainName = NULL;
	nRet = account_get_domain_name(account, &pszGetDomainName);
	if ( nRet != ACCOUNT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] account_get_domain_name failed in AccountCallback\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	if ( pszGetDomainName != NULL )
	{
		free(pszGetDomainName);
		pszGetDomainName = NULL;
	}

	char *pszGetDisplayName = NULL;
	nRet = account_get_display_name(g_account, &pszGetDisplayName);
	if ( nRet != ACCOUNT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] account_get_display_name failed in AccountCallback\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	if ( pszGetDisplayName != NULL )
	{
		free(pszGetDisplayName);
		pszGetDisplayName = NULL;
	}

	char *pszGetPackName = NULL;
	nRet = account_get_package_name(g_account, &pszGetPackName);
	if ( nRet != ACCOUNT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] account_get_package_name failed in AccountCallback\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	if ( pszGetPackName != NULL )
	{
		free(pszGetPackName);
		pszGetPackName = NULL;
	}

	char *pszGetEmail = NULL;
	nRet = account_get_email_address(account, &pszGetEmail);
	if ( nRet != ACCOUNT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] account_get_email_address failed in AccountCallback\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	if ( pszGetEmail != NULL)
	{
		free(pszGetEmail);
		pszGetEmail = NULL;
	}
	if ( mainloop )
	{
		g_main_loop_quit(mainloop);
	}
	return true;
}

/**
* @function 		AccountTypeCallback
* @description	 	Called once for each account handle from database
* @parameter		account_type_h: Account Type Handle, user_data: User data sent to callback
* @return 			bool: Status of Callback
*/
static bool AccountTypeCallback(account_type_h account_type, void *user_data)
{
	if(account_type == NULL)
	{
		FPRINTF("[Line : %d][%s] account_type is NULL in  AccountTypeCallback function\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	char *pszGetAppId = NULL;
	int nRet = account_type_get_app_id(account_type, &pszGetAppId);
	if ( nRet != ACCOUNT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] account_type_get_app_id failed in  AccountTypeCallback callback\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	if ( pszGetAppId == NULL )
	{
		FPRINTF("[Line : %d][%s] pszGetAppId value is NULL\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	if ( strcmp(g_pstrAppId, pszGetAppId)== 0 )
	{
		g_bAccountTypeCB = true;
	}
	if ( pszGetAppId != NULL )
	{
		free(pszGetAppId);
		pszGetAppId = NULL;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] reached AccountTypeCallback callback\\n", __LINE__, API_NAMESPACE);
#endif
	if ( mainloop )
	{
		g_main_loop_quit(mainloop);
	}
	return true;
}

/**
* @function 		AccountCustomCB
* @description	 	The callback function to retrieve all custom text;the callback function gives key and value
* @parameter		key: Custom Key, value: value of given key, user_data: User data sent to callback
* @return 			bool: Status of Callback
*/
static bool AccountCustomCB(char *key, char *value, void *user_data)
{
	if(key == NULL || value == NULL)
	{
		FPRINTF("[Line : %d][%s] key or value is NULL\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	if ( key != NULL )
	{
		g_pszValue = value;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] reached AccountCustomCB callback\\n", __LINE__, API_NAMESPACE);
#endif
	if ( mainloop )
	{
		g_main_loop_quit(mainloop);
	}
	return true;
}

/**
* @function 		AccountCapabilityCB
* @description	 	The callback function to retrieve Capability Type and Corresponding Value/
* @parameter		capability_type: Capability type, capability_state: Corresponding capability value (on/off)of the specified capability type, user_data: User data sent to callback
* @return 			bool: Status of Callback
*/
static bool AccountCapabilityCB(const char *capability_type, account_capability_state_e capability_state, void *user_data)
{
	if(capability_type == NULL || (capability_state != ACCOUNT_CAPABILITY_STATE_INVALID && capability_state != ACCOUNT_CAPABILITY_DISABLED && capability_state != ACCOUNT_CAPABILITY_ENABLED))
	{
		FPRINTF("[Line : %d][%s] capability_type is NULL or capability_state is invalid in AccountCapabilityCB callback\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	if ( capability_type != NULL )
	{
		g_capability_state = capability_state;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] reached AccountCapabilityCB callback\\n", __LINE__, API_NAMESPACE);
#endif
	if ( mainloop )
	{
		g_main_loop_quit(mainloop);
	}
	return true;
}

/**
* @function 		AccountLabelCB
* @description	 	The callback function to retrieve Account AppId, Label and Locale Type Values for each Account Type Handle
* @parameter		app_id: App_id associated with given Account Type Handle, label: Corresponding Label Value, locale: Corresponding Locale Value, user_data: User data sent to callback
* @return 			bool: Status of Callback
*/
static bool AccountLabelCB(char* app_id, char* label, char* locale, void *user_data)
{
	if( app_id == NULL || label == NULL || locale == NULL )
	{
		FPRINTF("[Line : %d][%s] app_id or label or locale is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bAccountLabelCB = true;
	FPRINTF("[Line : %d][%s] reached AccountLabelCB with AppID = %s, Label = %s and Locale = %s\\n", __LINE__, API_NAMESPACE, app_id, label, locale);
#if DEBUG
	FPRINTF("[Line : %d][%s] reached AccountLabelCB callback\\n", __LINE__, API_NAMESPACE);
#endif
	if ( app_id != NULL )
	{
		strncpy(g_szAppID, app_id, strlen(app_id)+1);
	}
	if ( locale != NULL )
	{
		strncpy(g_szLocale, locale, strlen(locale)+1);
	}
	if ( label != NULL )
	{
		strncpy(g_szLabel, label, strlen(label)+1);
	}

	if ( mainloop )
	{
		g_main_loop_quit(mainloop);
	}
	return true;
}

/**
* @function 		ServiceProviderFeatureCB
* @description	 	The callback function to retrieve Account AppId, Label and Locale Type Values for each Account Type Handle
* @parameter		app_id: App_id associated with given Account Type Handle, key: Corresponding Service Provider Features, user_data: User data sent to callback
* @return 			bool: Status of Callback
*/
static bool ServiceProviderFeatureCB(char* app_id, char* key, void* user_data)
{
	if(app_id == NULL || key == NULL)
	{
		FPRINTF("[Line : %d][%s] app_id or key is NULL\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	
	g_bAccountTypeCB = true;
	g_nPackageIdCB = 1;
	if ( app_id != NULL )
	{
		strncpy(g_szAppID, app_id, strlen(app_id)+1);
	}
	if ( key != NULL )
	{
		strncpy(g_szProviderFeatureArr[g_nProviderCount++], key, strlen(key)+1);
	}

	if(user_data != NULL)
	{
		const char* _capability = (const char*)user_data;
		if(strcmp(key, _capability) != 0)
		{
			g_bAccountTypeCB = false;
			g_nPackageIdCB = 0;
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] reached ServiceProviderFeatureCB callback\\n", __LINE__, API_NAMESPACE);
#endif
	if ( mainloop )
	{
		g_main_loop_quit(mainloop);
	}
	return true;
}
/**
* @function 		AccountEventCB
* @description	 	The callback function will be called when an account is removed from the database
* @parameter		event_type: event type associated with given Account Type Handle, account_id: account id, user_data: User data sent to callback
* @return 			bool: Status of Callback
*/
static bool AccountEventCB(const char* event_type, int account_id, void* user_data)
{
	g_event_type = (char *)event_type;
	FPRINTF("[Line : %d][%s] The Value of Event Type == %s\\n", __LINE__, API_NAMESPACE, event_type);
	g_bSubscribeNotification = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] reached AccountEventCB callback\\n", __LINE__, API_NAMESPACE);
#endif
	if ( mainloop )
	{
		g_main_loop_quit(mainloop);
	}
	return true;
}

/**
* @function 		AccountProviderFeatureCallback
* @description	 	Called once for each account handle from database
* @parameter		account_type_h: Account Type Handle, user_data: User data sent to callback
* @return 			bool: Status of Callback
*/
static bool AccountProviderFeatureCallback(account_type_h account_type, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] reached AccountTypeCallback callback\\n", __LINE__, API_NAMESPACE);
#endif

	if(account_type == NULL)
	{
		FPRINTF("[Line : %d][%s] account_type is NULL in  AccountProviderFeatureCallback function\\n", __LINE__, API_NAMESPACE);
		g_bAccountTypeCB = false;
	}
	else
	{
		g_bAccountTypeCB = true;
	}

	if ( mainloop )
	{
		g_main_loop_quit(mainloop);
		mainloop = NULL;
	}
	return false;
}

/**
* @function 		AcountTypeDestroyHelper
* @description	 	Helper Function to Destroy Account Type Handle
* @parameter		account_type_h: Account Type Handler
* @return 			NA
*/
void AcountTypeDestroyHelper(account_type_h accountTypeHandle)
{
	int nRet = account_type_destroy(accountTypeHandle);
	if ( nRet != ACCOUNT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] account_type_destroy failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AccManagerGetErrorMSG(nRet));
	}
	if ( accountTypeHandle != NULL )
	{
		accountTypeHandle = NULL;
	}
	return;
}

/**
* @function 		AccountPreConditionHelper
* @description	 	Helper Function to clear the Desired Account from DB if Exist.
* @parameter		void
* @return 			boolean: result
*/
bool AccountPreConditionHelper(void)
{
	int nRet = account_set_user_name(g_account, (char *)USERNAME);
	if ( nRet != ACCOUNT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] account_set_user_name failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AccManagerGetErrorMSG(nRet));
		return false;
	}
	nRet = account_set_email_address(g_account, (char *)EMAILID);
	if ( nRet != ACCOUNT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] account_set_email_address failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AccManagerGetErrorMSG(nRet));
		return false;
	}
	nRet = account_set_package_name(g_account, g_pstrAppId);
	if ( nRet != ACCOUNT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] account_set_package_name failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AccManagerGetErrorMSG(nRet));
		return false;
	}
	int nUpdatedCount = -1;
	int nAccountTimeoutId = 0;
	g_AccId = -1;
	nRet = account_get_total_count_from_db(&nUpdatedCount);
	if ( nRet != ACCOUNT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] account_get_total_count_from_db failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AccManagerGetErrorMSG(nRet));
		return false;
	}
	if ( nUpdatedCount > 0 )
	{
		nRet = account_foreach_account_from_db(AccountCallback, NULL);
		if ( nRet != ACCOUNT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] account_foreach_account_from_db failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AccManagerGetErrorMSG(nRet));
				return false;
		}
		RUN_POLLING_LOOP;
		if ( g_AccId != -1 )
		{
			nRet = account_delete_from_db_by_id(g_AccId);
			if ( nRet != ACCOUNT_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] account_delete_from_db_by_id failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AccManagerGetErrorMSG(nRet));
						return false;
			}
		}
	}
	return true;
}

/** @addtogroup itc-accounts-svc-testcases
*  @brief 		Integration testcases for module accounts-svc
*  @ingroup 	itc-accounts-svc
*  @{
*/

//& purpose: Retrieves all account type information with the given application id.
//& type: auto
/**
* @testcase 			ITc_account_type_foreach_account_type_from_db_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all account type information with the given application id
* @scenario				Create Account Type Handle and Set the application id\n
*						Insert Account Type  Handle with given application id into DB\n
*						Retrieves all account type information with the given application id\n
*						Deletes the account type from the account database by application id
* @apicovered			account_type_create
* @passcase				When account_type_foreach_account_type_from_db is successful
* @failcase				If target API account_type_foreach_account_type_from_db or any precondition and postcondition API fails
* @precondition			Creates a account type handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account type handle and releases all its resources
*/
int ITc_account_type_foreach_account_type_from_db_p(void)
{
	START_TEST;
	int nAccountTimeoutId = 0;
	account_type_h accountTypeHandle = NULL;

	int nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));

	g_bAccountTypeCB = false;
	nRet = account_type_foreach_account_type_from_db(AccountTypeCallback, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_foreach_account_type_from_db", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	RUN_POLLING_LOOP;
	if ( !g_bAccountTypeCB )
	{
		FPRINTF("[Line : %d][%s] AccountType Callback not invoked\\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}

//& purpose: Retrieves provider feature information related to the application with given id.
//& type: auto
/**
* @testcase 			ITc_account_type_query_provider_feature_by_app_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves provider feature information related to the application with given id
* @scenario				Create Account Type Handle and Set the application id and Provider Feature Name\n
*						Insert/Update Account Type  Handle with given application id into DB\n
*						Retrieves provider feature information related to the application with given id
* @apicovered			account_type_create, account_type_query_provider_feature_by_app_id
* @passcase				When account_type_query_provider_feature_by_app_id are successful
* @failcase				If target account_type_query_provider_feature_by_app_id or any precondition and postcondition API fails
* @precondition			Creates a account type handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account type handle and releases all its resources
*/
int ITc_account_type_query_provider_feature_by_app_id_p(void)
{
	START_TEST;
	int nRet = -1, nAccountTimeoutId = 0;
	account_type_h accountTypeHandle = NULL;
	char *pProviderFeature = ACCOUNT_SUPPORTS_CAPABILITY_CONTACT;

	nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));

	g_nPackageIdCB = 0;
	nRet = account_type_query_app_id_exist(g_pstrAppId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_app_id_exist", AccManagerGetErrorMSG(nRet), AcountTypeDestroyHelper(accountTypeHandle););

	g_nProviderCount = 0;
	nRet = account_type_query_provider_feature_by_app_id(ServiceProviderFeatureCB, g_pstrAppId, (void *)pProviderFeature);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_provider_feature_by_app_id", AccManagerGetErrorMSG(nRet), AcountTypeDestroyHelper(accountTypeHandle););
	RUN_POLLING_LOOP;

	if ( !g_nPackageIdCB )
	{
		FPRINTF("\\n[Line : %d][%s] Unable to call callback function ServiceProviderFeatureCB \\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}

	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}
//& purpose: Retrieves all accounts with the given package name.
//& type: auto
/**
* @testcase 			ITc_account_query_from_db_by_package_name_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all accounts with the given package name
* @scenario				Connect to DB and fetch the AccountID and Account Handle\n
*						Set account handler properties like package name\n
*						Retrieves all accounts with the given package name
* @apicovered			account_insert_to_db , account_delete_from_db_by_id and account_query_account_by_package_name
* @passcase				When account_query_account_by_package_name is successful
* @failcase				If target API's account_query_account_by_package_name fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_query_from_db_by_package_name_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}
	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bAccountCB = false;
	int nAccountTimeoutId = 0;
	nRet = account_query_account_by_package_name(AccountCallback, g_pstrAppId, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_account_by_package_name", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););
	RUN_POLLING_LOOP;
	if ( !g_bAccountCB )
	{
		FPRINTF("[Line : %d][%s] AccountCallback not invoked\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Creates a handle to the account And then Destroy it.
//& type: auto
/**
* @testcase 			ITc_account_create_destroy_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates a handle to the account And then Destroy it
* @scenario				Creates a handle to the account\n
*						Destroys the account handle and releases all its resources
* @apicovered			account_create, account_destroy
* @passcase				When account_create, account_destroy are successful
* @failcase				If target account_create or account_destroy fails or any precondition and postcondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_account_create_destroy_p(void)
{
	START_TEST;

	account_h hAccount;
	int nRet = account_create(&hAccount);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_create", AccManagerGetErrorMSG(nRet));
	CHECK_HANDLE(hAccount, "account_create");

	nRet = account_destroy(hAccount);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_destroy", AccManagerGetErrorMSG(nRet));
	hAccount = NULL;
	return 0;
}

//& purpose: Set and Gets the user name of the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_user_name_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the user name of the account
* @scenario				Sets the user name of the account\n
*						Gets the user name of the account
* @apicovered			account_set_user_name, account_get_user_name
* @passcase				When account_set_user_name, account_get_user_name are successful
* @failcase				If target account_set_user_name or account_get_user_name fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_user_name_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	char pszSetUserName[] = "TEST_TIZEN";
	char* pszGetUserName = NULL;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_user_name(g_account, pszSetUserName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_user_name", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_get_user_name(g_account, &pszGetUserName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_user_name", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););
	if ( pszGetUserName == NULL || strcmp(pszSetUserName, pszGetUserName) != 0 )
	{
		FPRINTF("[Line : %d][%s] account_get_user_name API Call Failed Set and Get values mismatchSet value is: %s, Get value is: %s\\n", __LINE__, API_NAMESPACE, pszSetUserName, pszGetUserName);
		FREE_MEMORY(pszGetUserName);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	FREE_MEMORY(pszGetUserName);
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Set and Gets the user Text of the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_user_text_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the user Text of the account
* @scenario				Sets the user text of the account\n
*						Gets the user text of the account
* @apicovered			account_set_user_text, account_get_user_text
* @passcase				When account_set_user_text, account_get_user_text are successful
* @failcase				If target account_set_user_text or account_get_user_text fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_user_text_p(void)
{
	START_TEST;

	char pszSetUserText[] = "HELLO_TIZEN";
	char* pszGetUserText = NULL;


	//int nIndex =  0 + (rand()% 5);//The index of the user integer (must be in range from 0 to 4)
	int nIndex=0;
	for( nIndex= 0;nIndex<5;nIndex++)
	{
		int nRet = account_set_user_text(g_account, nIndex, pszSetUserText);
		PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_set_user_text", AccManagerGetErrorMSG(nRet));

		nRet = account_get_user_text(g_account, nIndex, &pszGetUserText);
		PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_get_user_text", AccManagerGetErrorMSG(nRet));
		if ( pszGetUserText == NULL || strcmp(pszSetUserText, pszGetUserText) != 0 )
		{
			FPRINTF("[Line : %d][%s] account_get_user_text API Call Failed Set and Get values mismatchSet value is: %s, Get value is: %s\\n", __LINE__, API_NAMESPACE, pszSetUserText, pszGetUserText);
			FREE_MEMORY(pszGetUserText);
			return 1;
		}
		FREE_MEMORY(pszGetUserText);
	}
	return 0;
}

//& purpose: Set and Gets the user int of the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_user_int_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the user int of the account
* @scenario				Sets the user integer for the given account\n
*						Gets the user integer for the given account
* @apicovered			account_set_user_int, account_get_user_int
* @passcase				When account_set_user_int, account_get_user_int are successful
* @failcase				If target account_set_user_int or account_get_user_int fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_user_int_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	int pszSetUserInt = 1;
	int pszGetUserInt = -1;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	//int nIndex =  0 + (rand()% 5);//The index of the user integer (must be in range from 0 to 4)
	int nIndex=0;
	for( nIndex= 0;nIndex<5;nIndex++)
	{
		nRet = account_set_user_int(g_account, nIndex, pszSetUserInt);
		PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_user_int", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

		nRet = account_update_to_db_by_id(g_account, g_AccId);
		PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

		nRet = account_get_user_int(g_account, nIndex, &pszGetUserInt);
		PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_user_int", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););
		if ( pszGetUserInt == -1 || pszGetUserInt != pszSetUserInt )
		{
			FPRINTF("[Line : %d][%s] account_get_user_int API Call Failed Set and Get values mismatchSet value is: %d, Get value is: %d\\n", __LINE__, API_NAMESPACE, pszSetUserInt, pszGetUserInt);
			account_delete_from_db_by_id(g_AccId);
			return 1;
		}
	}
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Sets and Get the display name of the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_display_name_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and Get the display name of the account
* @scenario				Sets the display name of the account\n
*						Gets the display name of the account
* @apicovered			account_set_display_name, account_get_display_name
* @passcase				When account_set_display_name, account_get_display_name are successful
* @failcase				If target account_set_display_name or account_get_display_name fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_display_name_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	char pszSetDisplayName[] = "TEST_TIZEN";
	char* pszGetDisplayName = NULL;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_display_name(g_account, pszSetDisplayName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_display_name", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_get_display_name(g_account, &pszGetDisplayName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_display_name", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););
	if ( pszGetDisplayName == NULL || strcmp(pszSetDisplayName, pszGetDisplayName) != 0 )
	{
		FPRINTF("[Line : %d][%s] account_get_display_name API Call Failed Set and Get values mismatchSet value is: %s, Get value is: %s\\n", __LINE__, API_NAMESPACE, pszSetDisplayName, pszGetDisplayName);
		FREE_MEMORY(pszGetDisplayName);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	FREE_MEMORY(pszGetDisplayName);
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Set and Gets the domain name of the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_domain_name_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the domain name of the account
* @scenario				Sets the domain name of the account\n
*						Gets the domain name of the account
* @apicovered			account_set_domain_name, account_get_domain_name
* @passcase				When account_set_domain_name, account_get_domain_name are successful
* @failcase				If target account_set_domain_name or account_get_domain_name fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_domain_name_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	char pszSetDomainName[] = "TEST_TIZEN";
	char* pszGetDomainName = NULL;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_domain_name(g_account, pszSetDomainName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_domain_name", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_get_domain_name(g_account, &pszGetDomainName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_domain_name", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););
	if ( pszGetDomainName == NULL || strcmp(pszSetDomainName, pszGetDomainName) != 0 )
	{
		FPRINTF("[Line : %d][%s] account_get_domain_name API Call Failed Set and Get values mismatchSet value is: %s, Get value is: %s\\n", __LINE__, API_NAMESPACE, pszSetDomainName, pszGetDomainName);
		FREE_MEMORY(pszGetDomainName);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	FREE_MEMORY(pszGetDomainName);
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Set and Gets the email address of the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_email_address_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the email address of the account.
* @scenario				Set the email address of the account\n
*						Get the email address of the account
* @apicovered			account_set_email_address, account_get_email_address
* @passcase				When account_set_email_address, account_get_email_address are successful
* @failcase				If target account_set_email_address or account_get_email_address fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_email_address_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	char* pszGetEmail = NULL;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet),);

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_email_address(g_account, EMAILID);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_email_address", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_get_email_address(g_account, &pszGetEmail);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_email_address", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););
	if ( pszGetEmail == NULL || strcmp((char *)EMAILID, pszGetEmail) != 0 )
	{
		FPRINTF("[Line : %d][%s] account_get_email_address API Call Failed Set and Get values mismatchSet value is: %s, Get value is: %s\\n", __LINE__, API_NAMESPACE, EMAILID, pszGetEmail);
		FREE_MEMORY(pszGetEmail);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	FREE_MEMORY(pszGetEmail);
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Set and Gets the auth type of the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_auth_type_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the auth type of the account
* @scenario				Sets the Auth Type for the given account\n
*						Gets the Auth Type for the given account
* @apicovered			account_set_auth_type, account_get_auth_type
* @passcase				When account_set_auth_type, account_get_auth_type are successful
* @failcase				If target account_set_auth_type or account_get_auth_type fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_auth_type_p(void)
{

	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	account_auth_type_e eAccountAuthType =  -1;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet),);

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_auth_type(g_account, ACCOUNT_AUTH_TYPE_XAUTH);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_auth_type", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_get_auth_type(g_account, &eAccountAuthType);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_auth_type", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););
	if ( eAccountAuthType != ACCOUNT_AUTH_TYPE_XAUTH )
	{
		FPRINTF("[Line : %d][%s] account_get_auth_type API Call Failed Set and Get values mismatchSet Auth Mode is: %s, Get value is: %s\\n", __LINE__, API_NAMESPACE, AccountGetAuthType(ACCOUNT_AUTH_TYPE_XAUTH), AccountGetAuthType( eAccountAuthType));
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Set and Gets the source of the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_source_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the source of the account
* @scenario				Sets the source of the account\n
*						Gets the source name of the account
* @apicovered			account_set_source, account_get_source
* @passcase				When account_set_source, account_get_source are successful
* @failcase				If target account_set_source or account_get_source fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_source_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	char pszSetSource[] = "SOURCE";
	char* pszGetSource = NULL;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet),);

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_source(g_account, pszSetSource);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_source", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_get_source(g_account, &pszGetSource);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_source", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););
	if ( pszGetSource == NULL || strcmp(pszSetSource, pszGetSource) != 0 )
	{
		FPRINTF("[Line : %d][%s] account_get_source API Call Failed Set and Get values mismatchSet value is: %s, Get value is: %s\\n", __LINE__, API_NAMESPACE, pszSetSource, pszGetSource);
		FREE_MEMORY(pszGetSource);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	FREE_MEMORY(pszGetSource);
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Set and Gets the icon's path associated with the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_icon_path_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the icon's path associated with the account
* @scenario				Sets the icon Path\n
*						Gets the icon path associated with the account
* @apicovered			account_set_icon_path, account_get_icon_path
* @passcase				When account_set_icon_path, account_get_icon_path are successful
* @failcase				If target account_set_icon_path or account_get_icon_path fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_icon_path_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	char* pszGetIconPath = NULL;
	char pIconPath[PATH_LEN] = {0,};
	if ( false == AccManagerAppendToAppDataPath(ICONPATH, pIconPath) )
	{
		FPRINTF( "[Line : %d][%s] unable to get the Icon data path", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet),);

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_icon_path(g_account, pIconPath);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_icon_path", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_get_icon_path(g_account, &pszGetIconPath);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_icon_path", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););
	if ( pszGetIconPath == NULL || strcmp(pIconPath, pszGetIconPath) != 0 )
	{
		FPRINTF("[Line : %d][%s] account_get_icon_path API Call Failed Set and Get values mismatchSet value is: %s, Get value is: %s\n", __LINE__, API_NAMESPACE, pIconPath, pszGetIconPath);
		FREE_MEMORY(pszGetIconPath);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	FREE_MEMORY(pszGetIconPath);
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Set and Gets the package name associated with the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_package_name_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the package name associated with the account
* @scenario				Sets the Package Name\n
*						Gets the Package Name associated with the account
* @apicovered			account_set_package_name, account_get_package_name
* @passcase				When account_set_package_name, account_get_package_name are successful
* @failcase				If target account_set_package_name or account_get_package_name fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_package_name_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	char* pszGetPackName = NULL;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet),);

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_package_name(g_account, g_pstrAppId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_package_name", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_get_package_name(g_account, &pszGetPackName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_package_name", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););
	if ( pszGetPackName == NULL || strcmp(g_pstrAppId, pszGetPackName) != 0 )
	{
		FPRINTF("[Line : %d][%s] account_get_package_name API Call Failed Set and Get values mismatchSet value is: %s, Get value is: %s\\n", __LINE__, API_NAMESPACE, g_pstrAppId, pszGetPackName);
		FREE_MEMORY(pszGetPackName);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	FREE_MEMORY(pszGetPackName);
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Set and Gets the access token associated with the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_access_token_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the access token associated with the account
* @scenario				Sets the Access Token\n
*						Gets the Access Token associated with the account
* @apicovered			account_set_access_token, account_get_access_token
* @passcase				When account_set_access_token, account_get_access_token are successful
* @failcase				If target account_set_access_token or account_get_access_token fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_access_token_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	char* pszGetAccessToken = NULL;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet),);

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_access_token(g_account, (char *)ACCESSTOKEN);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_access_token", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_get_access_token(g_account, &pszGetAccessToken);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_access_token", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););
	if ( pszGetAccessToken == NULL || strcmp((char *)ACCESSTOKEN, pszGetAccessToken) != 0 )
	{
		FPRINTF("[Line : %d][%s] account_get_access_token API Call Failed Set and Get values mismatchSet value is: %s, Get value is: %s\n", __LINE__, API_NAMESPACE, (char *)ACCESSTOKEN, pszGetAccessToken);
		FREE_MEMORY(pszGetAccessToken);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	FREE_MEMORY(pszGetAccessToken);
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Set and Gets the capability details of the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_capability_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the capability details of the account
* @scenario				Sets the capability state\n
*						Gets the capability details of the account
* @apicovered			account_set_capability, account_get_capability, account_get_capability_all
* @passcase				When account_set_capability, account_get_capability, account_get_capability_all are successful
* @failcase				If target account_set_capability or account_get_capability, account_get_capability_all fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_capability_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	int nAccountTimeoutId = 0;
	account_capability_state_e eAccountCapability =  -1;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet),);

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_capability(g_account, (char *)CALENDAR_CAPABILITY, ACCOUNT_CAPABILITY_ENABLED);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_capability", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_get_capability(g_account, (char *)CALENDAR_CAPABILITY, &eAccountCapability);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_capability", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););
	if ( eAccountCapability != ACCOUNT_CAPABILITY_ENABLED )
	{
		FPRINTF("[Line : %d][%s] account_get_capability API Call Failed Set and Get values mismatchSet Capability State is: %s, Get State is: %s\n", __LINE__, API_NAMESPACE, AccountGetCapabilityState(ACCOUNT_CAPABILITY_ENABLED), AccountGetCapabilityState( eAccountCapability));
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	g_capability_state = -1;
	nRet = account_get_capability_all(g_account, AccountCapabilityCB, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_capability_all", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););
	RUN_POLLING_LOOP;
	if ( g_capability_state != ACCOUNT_CAPABILITY_ENABLED )
	{
		FPRINTF("[Line : %d][%s] account_get_capability_all API Call Failed Set and Get values mismatchSet Capability State is: %s, Get State is: %s\n", __LINE__, API_NAMESPACE, AccountGetCapabilityState(ACCOUNT_CAPABILITY_ENABLED), AccountGetCapabilityState(g_capability_state));
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Set and Gets the user specific custom text of the given account key.
//& type: auto
/**
* @testcase 			ITc_account_set_get_custom_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the user specific custom text of the given account key
* @scenario				Sets the user custom key and value\n
*						Gets the user specific custom text of the given account key.
* @apicovered			account_set_custom, account_get_custom, account_get_custom_all
* @passcase				When account_set_custom, account_get_custom, account_get_custom_all are successful
* @failcase				If target account_set_custom or account_get_custom, account_get_custom_all fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_custom_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	int nAccountTimeoutId = 0;
	char szKey[] = "KEY";
	char szValue[] = "VALUE";
	char *pszTempValue = NULL;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet),);

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_custom(g_account, szKey, szValue);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_custom", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_get_custom(g_account, szKey, &pszTempValue);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_custom", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););
	if ( pszTempValue == NULL || strcmp(szValue, pszTempValue) != 0 )//not equal
	{
		FPRINTF("[Line : %d][%s] account_get_custom API Call Failed Set and Get values mismatchSet Custom Value is: %s, Get State is: %s\n", __LINE__, API_NAMESPACE, szValue, pszTempValue);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	g_pszValue = NULL;
	nRet = account_get_custom_all(g_account, AccountCustomCB, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_custom_all", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););
	RUN_POLLING_LOOP;
	if ( g_pszValue == NULL || strcmp(szValue, g_pszValue) != 0 )//not equal
	{
		FPRINTF("[Line : %d][%s] account_get_custom_all API Call Failed Set and Get values mismatchSet Custom Value is: %s, Get State is: %s\n", __LINE__, API_NAMESPACE, szValue, g_pszValue);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Set and Gets the secret of the account.
//& type: auto
/**
* @testcase 			ITc_account_set_get_secret_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the secret of the account
* @scenario				Sets the Secret\n
*						Gets the Secret
* @apicovered			account_set_secret, account_get_secret
* @passcase				When account_set_secret, account_get_secret are successful
* @failcase				If target account_set_secret or account_get_secret fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_secret_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	account_secrecy_state_e eAccountSecret =  -1;
	account_secrecy_state_e eSecrecyArray[] = { ACCOUNT_SECRECY_INVALID,
												ACCOUNT_SECRECY_INVISIBLE,
												ACCOUNT_SECRECY_VISIBLE
											};
	int nIndex = 0;
	int nSize = sizeof(eSecrecyArray)/sizeof(eSecrecyArray[0]);

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet),);

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	for(nIndex = 0; nIndex < nSize; nIndex++)
	{
		nRet = account_set_secret(g_account, eSecrecyArray[nIndex]);
		if( nRet != ACCOUNT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] account_set_secret API Call Failed for secrecy state = %s. Error returned = %s\\n", __LINE__, API_NAMESPACE, AccountGetSecret(eSecrecyArray[nIndex]), AccManagerGetErrorMSG(nRet));
			account_delete_from_db_by_id(g_AccId);
				return 1;
		}

		nRet = account_update_to_db_by_id(g_account, g_AccId);
		if( nRet != ACCOUNT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] account_update_to_db_by_id API Call Failed for secrecy state = %s. Error returned = %s\\n", __LINE__, API_NAMESPACE, AccountGetSecret(eSecrecyArray[nIndex]), AccManagerGetErrorMSG(nRet));
			account_delete_from_db_by_id(g_AccId);
				return 1;
		}

		nRet = account_get_secret(g_account, &eAccountSecret);
		if( nRet != ACCOUNT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] account_get_secret API Call Failed for secrecy state = %s. Error returned = %s\\n", __LINE__, API_NAMESPACE, AccountGetSecret(eSecrecyArray[nIndex]), AccManagerGetErrorMSG(nRet));
			account_delete_from_db_by_id(g_AccId);
				return 1;
		}

		if ( eAccountSecret != eSecrecyArray[nIndex] )
		{
			FPRINTF("[Line : %d][%s] account_get_secret API Call Failed Set and Get values mismatch. Set secret state is: %s, Get state is: %s\\n", __LINE__, API_NAMESPACE, AccountGetSecret(eSecrecyArray[nIndex]), AccountGetSecret( eAccountSecret));
			account_delete_from_db_by_id(g_AccId);
				return 1;
		}
	}
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Set and Gets the sync support.
//& type: auto
/**
* @testcase 			ITc_account_set_get_sync_support_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and Gets the sync support
* @scenario				Sets the sync support\n
*						Gets the sync support
* @apicovered			account_set_sync_support, account_get_sync_support
* @passcase				When account_set_sync_support, account_get_sync_support are successful
* @failcase				If target account_set_sync_support or account_get_sync_support fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_set_get_sync_support_p(void)
{
	START_TEST;

	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	account_sync_state_e eAccountSyncState =  -1;
	eAccountSyncState = -1;
	account_sync_state_e eSyncArray[] = { ACCOUNT_SYNC_INVALID,
										ACCOUNT_SYNC_NOT_SUPPORT,
 										ACCOUNT_SYNC_STATUS_OFF,
										ACCOUNT_SYNC_STATUS_IDLE,
										ACCOUNT_SYNC_STATUS_RUNNING,
										ACCOUNT_SUPPORTS_SYNC,
										/*ACCOUNT_NOT_SUPPORTS_SYNC,*/ /**<  NOT USED, WILL BE REMOVED TO PREVENT BUILD ERROR */
									};
	int nIndex = 0;
	int nSize = sizeof(eSyncArray)/sizeof(eSyncArray[0]);

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet),);

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	for(nIndex = 0; nIndex < nSize; nIndex++)
	{
		nRet = account_set_sync_support(g_account, eSyncArray[nIndex]);
		if(nRet != ACCOUNT_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] account_set_sync_support API Call Failed for sync state = %s. Error returned = %s\\n", __LINE__, API_NAMESPACE, AccountGetSyncState(eSyncArray[nIndex]), AccManagerGetErrorMSG(nRet));
			account_delete_from_db_by_id(g_AccId);
				return 1;
		}

		nRet = account_update_to_db_by_id(g_account, g_AccId);
		if( nRet != ACCOUNT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] account_update_to_db_by_id API Call Failed for sync state = %s. Error returned = %s\\n", __LINE__, API_NAMESPACE, AccountGetSyncState(eSyncArray[nIndex]), AccManagerGetErrorMSG(nRet));
			account_delete_from_db_by_id(g_AccId);
				return 1;
		}

		nRet = account_get_sync_support(g_account, &eAccountSyncState);
		if( nRet != ACCOUNT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] account_get_sync_support API Call Failed for sync state = %s. Error returned = %s\\n", __LINE__, API_NAMESPACE, AccountGetSyncState(eSyncArray[nIndex]), AccManagerGetErrorMSG(nRet));
			account_delete_from_db_by_id(g_AccId);
				return 1;
		}

		if ( eAccountSyncState != eSyncArray[nIndex] )
		{
			FPRINTF("[Line : %d][%s] account_get_sync_support API Call Failed. Set and Get values mismatchSet sync_support state is: %s, Get state is: %s\\n", __LINE__, API_NAMESPACE, AccountGetSyncState(eSyncArray[nIndex]), AccountGetSyncState( eAccountSyncState));
			account_delete_from_db_by_id(g_AccId);
				return 1;
		}
	}
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Creates a handle for account event subscription Subscribe And un-subscribe Notification of given account event.
//& type: auto
/**
* @testcase 			ITc_account_subscribe_unsubscribe_notification_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates a handle for account event subscription Subscribe And un-subscribe Notification of given account event
* @scenario				Creates a handle for account event subscription\n
*						Subscribes the given callback function for account events\n
*						Destroys the account subscription handle and releases all its resources
* @apicovered			account_subscribe_create, account_subscribe_notification, account_unsubscribe_notification
* @passcase				When account_subscribe_create, account_subscribe_notification, account_unsubscribe_notification are successful
* @failcase				If targetaccount_subscribe_create or account_subscribe_notification or account_unsubscribe_notification fails or any precondition and postcondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_account_subscribe_unsubscribe_notification_p(void)
{
	START_TEST;
	if(!AccountPreConditionHelper())
	{
		return 1;
	}
	account_subscribe_h hAccountSubscribe = NULL;
	hAccountSubscribe = NULL;
	int nAccountTimeoutId = 0;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_subscribe_create(&hAccountSubscribe);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_subscribe_create", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););
	if (hAccountSubscribe == NULL )
	{
		FPRINTF("[Line : %d][%s] account_subscribe_create API Call Failed with NULL\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	g_bSubscribeNotification = false;
	nRet = account_subscribe_notification(hAccountSubscribe, AccountEventCB, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_subscribe_notification", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	nRet = account_delete_from_db_by_id(g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_delete_from_db_by_id", AccManagerGetErrorMSG(nRet), account_unsubscribe_notification(hAccountSubscribe););

	RUN_POLLING_LOOP;

	if(g_bSubscribeNotification == false)
	{
		FPRINTF("[Line : %d][%s] account_subscribe_notification failed. Unable to call callback AccountEventCB\\n", __LINE__, API_NAMESPACE);
		account_unsubscribe_notification(hAccountSubscribe);
		return 1;
	}

	nRet =  account_unsubscribe_notification(hAccountSubscribe);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_unsubscribe_notification", AccManagerGetErrorMSG(nRet),);

	return 0;
}

//& purpose: Creates an account type handle And then Destroy it.
//& type: auto
/**
* @testcase 			ITc_account_type_create_destroy_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates an account type handle And then Destroy it
* @scenario				Creates a handle to the account\n
*						Destroys the account handle and releases all its resources
* @apicovered			account_type_create, account_type_destroy
* @passcase				When account_type_create, account_type_destroy are successful
* @failcase				If target account_type_create or account_type_destroy fails or any precondition and postcondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_account_type_create_destroy_p(void)
{
	START_TEST;

	account_type_h hAccountType;
	int nRet = account_type_create(&hAccountType);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));
	if ( hAccountType == NULL )
	{
		FPRINTF("[Line : %d][%s] account_type_create API Call Failed as accountTypeHandle is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = account_type_destroy(hAccountType);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_destroy", AccManagerGetErrorMSG(nRet));
	hAccountType = NULL;

	return 0;
}

//& purpose: Gets the icon id associated with the account type handle.
//& type: auto
/**
* @testcase 			ITc_account_type_get_icon_path_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the icon id associated with the account type handle
* @scenario				Get the Application Id associated with the account type handle
* @apicovered			account_type_create, account_type_get_icon_path
* @passcase				When account_type_get_icon_path are successful
* @failcase				If target account_type_get_icon_path fails or any precondition and postcondition API fails
* @precondition			Creates a account type handle
* @postcondition		Destroys the account type handle and releases all its resources
*/
int ITc_account_type_get_icon_path_p(void)
{
	START_TEST;

	char* pszGetIconPath = NULL;
	char pIconPath[PATH_LEN] = {0,};
	char pszUser[PATH_LEN] = {0,};
	char pszValue[PATH_LEN] = {0,};
	char* pszACTUAL_FILE_PATH = NULL;
	if ( false == AccManagerAppendToAppDataPath(ICONPATH, pIconPath) )
	{
		FPRINTF( "[Line : %d][%s] unable to get the Icon data path", __LINE__, API_NAMESPACE);
		return 1;
	}

	char* psz_pkg_id = NULL;
	int nRet = app_get_id(&psz_pkg_id);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "app_get_id", AppGetError(nRet));
	FPRINTF("[Line : %d][%s] app_get_id returned value = %s\\n", __LINE__, API_NAMESPACE, psz_pkg_id);
	if(0 == strncmp(TPK_APP_PREFIX,psz_pkg_id, strlen(TPK_APP_PREFIX)))
	{
		FPRINTF("[Line : %d][%s] Detected TPK execution\\n", __LINE__, API_NAMESPACE);
		if (true == GetValueForTCTSetting("DEVICE_EXECUTION_MODE_30", pszUser, API_NAMESPACE))
		{
			if (!strcmp(pszUser, "owner"))
			{
				if (true != GetValueForTCTSetting("DEVICE_ADMIN_USER_APPS_ROOT_30", pszValue, API_NAMESPACE))
				{
					FREE_MEMORY(psz_pkg_id);
					FPRINTF("[Line : %d][%s] GetValueForTCTSetting(DEVICE_ADMIN_USER_APPS_ROOT_30) failed\\n", __LINE__, API_NAMESPACE);
					return 1;
				}
			}
			else
			{
				if (true != GetValueForTCTSetting("DEVICE_OTHER_USER_APPS_ROOT_30", pszValue, API_NAMESPACE))
				{
					FREE_MEMORY(psz_pkg_id);
					FPRINTF("[Line : %d][%s] GetValueForTCTSetting(DEVICE_OTHER_USER_APPS_ROOT_30) failed\\n", __LINE__, API_NAMESPACE);
					return 1;
				}
			}

			/*if profile is TV then change the icon path*/
			if (get_tizen_profile() == _PROFILE_TV) {
				int str_len = strlen("/opt/usr/apps");
				memset(pszValue, 0, PATH_LEN);
				strncpy(pszValue, "/opt/usr/apps", str_len);
				pszValue[str_len+1] = '\0';
			}

			FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);

			int path_size = strlen(pszValue) + strlen(psz_pkg_id) + strlen(ACCOUNT_ICON_PATH) + 2;
			pszACTUAL_FILE_PATH = (char*)calloc(path_size, sizeof(char));
			if (pszACTUAL_FILE_PATH == NULL)
			{
				FPRINTF("[Line : %d][%s] Memory Allocation Failed for pszACTUAL_FILE_PATH \\n", __LINE__, API_NAMESPACE);
				return 1;
			}
			snprintf(pszACTUAL_FILE_PATH, path_size, "%s/%s%s", pszValue, psz_pkg_id, ACCOUNT_ICON_PATH);
			FREE_MEMORY(psz_pkg_id);
		}
		else
		{
			FREE_MEMORY(psz_pkg_id);
			FPRINTF("[Line : %d][%s] GetValueForTCTSetting(DEVICE_EXECUTION_MODE_30) failed\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	else
	{
		FREE_MEMORY(psz_pkg_id);
		FPRINTF("[Line : %d][%s] Detected RPM execution\\n", __LINE__, API_NAMESPACE);
			
		int path_size = strlen(RPM_INSTALL_LOCATION) + strlen(ACCOUNT_ICON_PATH) + 1;
		pszACTUAL_FILE_PATH = (char*)calloc(path_size, sizeof(char));
		if (pszACTUAL_FILE_PATH == NULL)
		{
			FPRINTF("[Line : %d][%s] Memory Allocation Failed for pszACTUAL_FILE_PATH \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		snprintf(pszACTUAL_FILE_PATH, path_size, "%s%s", RPM_INSTALL_LOCATION, ACCOUNT_ICON_PATH);
	}
	FPRINTF("[Line : %d][%s] pszACTUAL_FILE_PATH = %s\\n", __LINE__, API_NAMESPACE, pszACTUAL_FILE_PATH);

	account_type_h accountTypeHandle;
	nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));
	if ( accountTypeHandle == NULL )
	{
		FPRINTF("[Line : %d][%s] account_type_create API Call Failed as accountTypeHandle is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_type_query_by_app_id(g_pstrAppId, &accountTypeHandle);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_by_app_id", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	nRet = account_type_get_icon_path(accountTypeHandle, &pszGetIconPath);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_get_icon_path", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	if(pszGetIconPath == NULL)
	{
		FPRINTF("[Line : %d][%s] account_type_get_icon_path API Call Failed as pszGetIconPath is NULL\\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	else if( strcmp(pszGetIconPath, pszACTUAL_FILE_PATH) != 0)
	{
		FPRINTF("[Line : %d][%s] Set/Get value mismatch. Get value is = %s\\n", __LINE__, API_NAMESPACE, pszGetIconPath);
		FREE_MEMORY(pszGetIconPath);
		FREE_MEMORY(pszACTUAL_FILE_PATH);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	FREE_MEMORY(pszGetIconPath);
	FREE_MEMORY(pszACTUAL_FILE_PATH);
	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}

//& purpose: Gets the app id associated with the account.
//& type: auto
/**
* @testcase 			ITc_account_type_get_app_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the app id associated with the account
* @scenario				Get the Application Id associated with the account
* @apicovered			account_type_create, account_type_get_app_id
* @passcase				When account_type_get_app_id are successful
* @failcase				If target account_type_get_app_id fails or any precondition and postcondition API fails
* @precondition			Creates a account type handle
* @postcondition		Destroys the account type handle and releases all its resources
*/
int ITc_account_type_get_app_id_p(void)
{
	START_TEST;

	char* pszGetAppId = NULL;
	account_type_h accountTypeHandle;

	int nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));

	nRet = account_type_query_by_app_id(g_pstrAppId, &accountTypeHandle);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_by_app_id", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	nRet = account_type_get_app_id(accountTypeHandle, &pszGetAppId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_get_app_id", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));
	if ( pszGetAppId == NULL )
	{
		FPRINTF("[Line : %d][%s] account_type_get_app_id API Call Failed, pszGetAppId is NULL\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	else if ( strcmp(pszGetAppId, APPID) != 0 )
	{
		FPRINTF("[Line : %d][%s] Set/Get value mismatch. Get value is = %s\n", __LINE__, API_NAMESPACE, pszGetAppId);
		FREE_MEMORY(pszGetAppId);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	
	FREE_MEMORY(pszGetAppId);
	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}

//& purpose: Gets the small_icon id associated with the account type handle.
//& type: auto
/**
* @testcase 			ITc_account_type_get_small_icon_path_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the small_icon id associated with the account type handle
* @scenario				Get the Application Id associated with the account type handle
* @apicovered			account_type_create, account_type_get_small_icon_path
* @passcase				When account_type_get_small_icon_path are successful
* @failcase				If target account_type_get_small_icon_path fails or any precondition and postcondition API fails
* @precondition			Creates a account type handle
* @postcondition		Destroys the account type handle and releases all its resources
*/
int ITc_account_type_get_small_icon_path_p(void)
{
	START_TEST;

	char* pszGetIconPath = NULL;
	char pIconPath[PATH_LEN] = {0,};
	char pszUser[CONFIG_VALUE_LEN_MAX] = {0,};
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	char* pszACTUAL_FILE_PATH = NULL;
	if ( false == AccManagerAppendToAppDataPath(ICONPATH, pIconPath))
	{
		FPRINTF( "[Line : %d][%s] unable to get the Icon data path", __LINE__, API_NAMESPACE);
		return 1;
	}

	char* psz_pkg_id = NULL;
	int nRet = app_get_id(&psz_pkg_id);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "app_get_id", AppGetError(nRet));
	FPRINTF("[Line : %d][%s] app_get_id returned value = %s\\n", __LINE__, API_NAMESPACE, psz_pkg_id);
	if(0 == strncmp(TPK_APP_PREFIX,psz_pkg_id, strlen(TPK_APP_PREFIX)))
	{
		FPRINTF("[Line : %d][%s] Detected TPK execution\\n", __LINE__, API_NAMESPACE);
		if (true == GetValueForTCTSetting("DEVICE_EXECUTION_MODE_30", pszUser, API_NAMESPACE))
		{
			if (!strcmp(pszUser, "owner"))
			{
				if (true != GetValueForTCTSetting("DEVICE_ADMIN_USER_APPS_ROOT_30", pszValue, API_NAMESPACE))
				{
					FREE_MEMORY(psz_pkg_id);
					FPRINTF("[Line : %d][%s] GetValueForTCTSetting(DEVICE_ADMIN_USER_APPS_ROOT_30) failed\\n", __LINE__, API_NAMESPACE);
					return 1;
				}
			}
			else
			{
				if (true != GetValueForTCTSetting("DEVICE_OTHER_USER_APPS_ROOT_30", pszValue, API_NAMESPACE))
				{
					FREE_MEMORY(psz_pkg_id);
					FPRINTF("[Line : %d][%s] GetValueForTCTSetting(DEVICE_OTHER_USER_APPS_ROOT_30) failed\\n", __LINE__, API_NAMESPACE);
					return 1;
				}
			}

			/*if profile is TV then change the icon path*/
			if (get_tizen_profile() == _PROFILE_TV) {
				int str_len = strlen("/opt/usr/apps");
				memset(pszValue, 0, PATH_LEN);
				strncpy(pszValue, "/opt/usr/apps", str_len);
				pszValue[str_len+1] = '\0';
			}

			FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);

			int path_size = strlen(pszValue) + strlen(psz_pkg_id) + strlen(ACCOUNT_SMALL_ICON_PATH) + 2;
			pszACTUAL_FILE_PATH = (char*)calloc(path_size, sizeof(char));
			if (pszACTUAL_FILE_PATH == NULL)
			{
				FPRINTF("[Line : %d][%s] Memory Allocation Failed for pszACTUAL_FILE_PATH \\n", __LINE__, API_NAMESPACE);
				return 1;
			}
			snprintf(pszACTUAL_FILE_PATH, path_size, "%s/%s%s", pszValue, psz_pkg_id, ACCOUNT_SMALL_ICON_PATH);
			FREE_MEMORY(psz_pkg_id);
		}
		else
		{
			FREE_MEMORY(psz_pkg_id);
			FPRINTF("[Line : %d][%s] GetValueForTCTSetting(DEVICE_EXECUTION_MODE_30) failed\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	else
	{
		FREE_MEMORY(psz_pkg_id);
		FPRINTF("[Line : %d][%s] Detected RPM execution\\n", __LINE__, API_NAMESPACE);
			
		int path_size = strlen(RPM_INSTALL_LOCATION) + strlen(ACCOUNT_SMALL_ICON_PATH) + 1;
		pszACTUAL_FILE_PATH = (char*)calloc(path_size, sizeof(char));
		if (pszACTUAL_FILE_PATH == NULL)
		{
			FPRINTF("[Line : %d][%s] Memory Allocation Failed for pszACTUAL_FILE_PATH \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		snprintf(pszACTUAL_FILE_PATH, path_size, "%s%s", RPM_INSTALL_LOCATION, ACCOUNT_SMALL_ICON_PATH);
	}
	FPRINTF("[Line : %d][%s] pszACTUAL_FILE_PATH = %s\\n", __LINE__, API_NAMESPACE, pszACTUAL_FILE_PATH);

	account_type_h accountTypeHandle;

	nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));

	nRet = account_type_query_by_app_id(g_pstrAppId, &accountTypeHandle);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_by_app_id", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	nRet = account_type_get_small_icon_path(accountTypeHandle, &pszGetIconPath);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_get_small_icon_path", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	if(pszGetIconPath == NULL)
	{
		FPRINTF("[Line : %d][%s] account_type_get_small_icon_path API Call Failed as pszGetIconPath is NULL\\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	else if(strcmp(pszGetIconPath, pszACTUAL_FILE_PATH) != 0)
	{
		FPRINTF("[Line : %d][%s] Set/Get value mismatch. Get value is = %s\\n", __LINE__, API_NAMESPACE, pszGetIconPath);
		FREE_MEMORY(pszGetIconPath);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	FREE_MEMORY(pszGetIconPath);
	FREE_MEMORY(pszACTUAL_FILE_PATH);
	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}

//& purpose: Gets the service provider id of an account type.
//& type: auto
/**
* @testcase 			ITc_account_type_get_service_provider_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the service provider id of an account type
* @scenario				Gets the service provider id of an account type
* @apicovered			account_type_create, account_type_get_service_provider_id
* @passcase				When account_type_get_service_provider_id are successful
* @failcase				If target account_type_get_service_provider_id fails or any precondition and postcondition API fails
* @precondition			Creates a account type handle
* @postcondition		Destroys the account type handle and releases all its resources
*/
int ITc_account_type_get_service_provider_id_p(void)
{
	START_TEST;

	char* pszGetProviderId = NULL;
	account_type_h accountTypeHandle;

	int nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));

	nRet = account_type_query_by_app_id(g_pstrAppId, &accountTypeHandle);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_by_app_id", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	nRet = account_type_get_service_provider_id(accountTypeHandle, &pszGetProviderId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_get_service_provider_id", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	if(pszGetProviderId == NULL)
	{
		FPRINTF("[Line : %d][%s] account_type_get_service_provider_id API Call Failed as pszGetProviderId is NULL\\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	else if(strcmp(pszGetProviderId, SERVICE_PROVIDER_ID) != 0)
	{
		FPRINTF("[Line : %d][%s] Set/Get value mismatch. Get value = %s\\n", __LINE__, API_NAMESPACE, pszGetProviderId);
		FREE_MEMORY(pszGetProviderId);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	FREE_MEMORY(pszGetProviderId);
	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}

//& purpose: Retrieves provider feature information for the given account type.
//& type: auto
/**
* @testcase 			ITc_account_type_get_provider_feature_all_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves provider feature information for the given account type
* @scenario				Retrieves provider feature information for the given account type
* @apicovered			account_type_create, account_type_get_provider_feature_all
* @passcase				When account_type_get_provider_feature_all are successful
* @failcase				If target account_type_get_provider_feature_all fails or any precondition and postcondition API fails
* @precondition			Creates a account type handle
* @postcondition		Destroys the account type handle and releases all its resources
*/
int ITc_account_type_get_provider_feature_all_p(void)
{
	START_TEST;

	int nAccountTimeoutId = 0;
	account_type_h accountTypeHandle;

	int nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));

	nRet = account_type_query_by_app_id(g_pstrAppId, &accountTypeHandle);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_by_app_id", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	g_bAccountTypeCB = false;
	g_nProviderCount = 0;
	nRet = account_type_get_provider_feature_all(accountTypeHandle, ServiceProviderFeatureCB, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_get_provider_feature_all", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));
	RUN_POLLING_LOOP;
	
	if(g_bAccountTypeCB == false)
	{
		FPRINTF("[Line : %d][%s] account_type_get_provider_feature_all API Call Failed. Unable to call Callback\\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	
	if ( strlen(g_szProviderFeatureArr[0]) <= 0 )
	{
		FPRINTF("[Line : %d][%s] account_type_get_provider_feature_all API Call Failed\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	else
	{
		int nIndex = 0;
		while(nIndex < g_nProviderCount)
		{	
			if( strcmp(g_szProviderFeatureArr[nIndex], g_eProviderFeature[nIndex]) != 0)
			{
				FPRINTF("[Line : %d][%s] Set/Get value mismatch. Get value = %s, Set value = %s\n", __LINE__, API_NAMESPACE, g_szProviderFeatureArr[nIndex], g_eProviderFeature[nIndex]);
				AcountTypeDestroyHelper(accountTypeHandle);
						return 1;
			}
			nIndex++;
		}
	}
	
	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}

//& purpose: Gets the multiple account support.
//& type: auto
/**
* @testcase 			ITc_account_type_get_multiple_account_support_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the multiple account support
* @scenario				Get the multiple account support
* @apicovered			account_type_create, account_type_get_multiple_account_support
* @passcase				When account_type_get_multiple_account_support are successful
* @failcase				If target account_type_get_multiple_account_support fails or any precondition and postcondition API fails
* @precondition			Creates a account type handle
* @postcondition		Destroys the account type handle and releases all its resources
*/
int ITc_account_type_get_multiple_account_support_p(void)
{
	START_TEST;

	int nMultipleSupport = -1;
	account_type_h accountTypeHandle;

	int nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));

	nRet = account_type_query_by_app_id(g_pstrAppId, &accountTypeHandle);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_by_app_id", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	nMultipleSupport = -1;
	nRet = account_type_get_multiple_account_support(accountTypeHandle, &nMultipleSupport);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_get_multiple_account_support", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	if(nMultipleSupport == -1)
	{
		FPRINTF("[Line : %d][%s] account_type_get_multiple_account_support API Call Failed as nMultipleSupport is -1\\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	if(nMultipleSupport != MULTIPLE_ACCOUNT_SUPPORT)
	{
		FPRINTF("[Line : %d][%s] account_type_get_multiple_account_support API return invalid value of nMultipleSupport. nMultipleSupport = %d \\n", __LINE__, API_NAMESPACE, nMultipleSupport);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	nMultipleSupport = -1;
	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}

//& purpose: Retrieves account type information for the given application id.
//& type: auto
/**
* @testcase 			ITc_account_type_query_by_app_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves account type information for the given application id
* @scenario				Create Account Type Handle and Set the application id
*						Insert Account Type  Handle with given application id into DB
*						Retrieves account type information for the given application id
* @apicovered			account_type_create, account_type_query_by_app_id, account_type_get_app_id
* @passcase				When account_type_query_by_app_id are successful
* @failcase				If target account_type_query_by_app_id fails or any precondition and postcondition API fails
* @precondition			Creates a account type handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account type handle and releases all its resources
*/
int ITc_account_type_query_by_app_id_p(void)
{
	START_TEST;

	account_type_h accountTypeHandle = NULL;

	int nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));

	nRet = account_type_query_app_id_exist(g_pstrAppId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_app_id_exist", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	nRet = account_type_query_by_app_id(g_pstrAppId, &accountTypeHandle);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_by_app_id", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));
	if ( accountTypeHandle == NULL )
	{
		FPRINTF("[Line : %d][%s] account_type_query_by_app_id API Call Failed as accountTypeHandle is NULL.\\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}

	char * pszGetAppId = NULL;
	nRet = account_type_get_app_id(accountTypeHandle, &pszGetAppId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_get_app_id", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));
	if ( pszGetAppId == NULL || strcmp(g_pstrAppId, pszGetAppId) != 0 )
	{
		FPRINTF("[Line : %d][%s] account_type_get_app_id API Call Failed as Set and Get values mismatchSet value is: %s, Get value is: %s\\n", __LINE__, API_NAMESPACE, g_pstrAppId, pszGetAppId);
		FREE_MEMORY(pszGetAppId);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}

	FREE_MEMORY(pszGetAppId);
	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}

//& purpose: Gets the label information detail of an account type.
//& type: auto
/**
* @testcase 			ITc_account_type_get_label_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the label information detail of an account type
* @scenario				Gets the label information detail of an account type
* @apicovered			account_type_create, account_type_get_label, account_type_get_label_by_locale
* @passcase				When account_type_get_label, account_type_get_label_by_locale are successful
* @failcase				If target account_type_get_label or account_type_get_label_by_locale fails or any precondition and postcondition API fails
* @precondition			Creates a account type handle
* @postcondition		Destroys the account type handle and releases all its resources
*/
int ITc_account_type_get_label_p(void)
{
	START_TEST;

	int nAccountTimeoutId = 0;
	account_type_h accountTypeHandle;

	int nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));

	nRet = account_type_query_by_app_id(g_pstrAppId, &accountTypeHandle);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_by_app_id", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));
	if ( accountTypeHandle == NULL )
	{
		FPRINTF("[Line : %d][%s] account_type_query_by_app_id API Call Failed as accountTypeHandle is NULL.\\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}

	memset(g_szLocale, 0, sizeof(g_szLocale));
	memset(g_szLabel, 0, sizeof(g_szLabel));
	FPRINTF("[Line : %d][%s] Value of g_szAppID == %d\n", __LINE__, API_NAMESPACE, sizeof(g_szAppID));

	g_bAccountLabelCB = false;

	nRet = account_type_get_label(accountTypeHandle, AccountLabelCB, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_get_label", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));
	RUN_POLLING_LOOP;

	if(g_bAccountLabelCB == false)
	{
		FPRINTF("[Line : %d][%s] account_type_get_label API Call Failed. Unable to call callback.\\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	char * tempLabel = NULL;

	nRet = account_type_get_label_by_locale(accountTypeHandle,  (char *)g_szLocale, (char **)&tempLabel);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_get_label_by_locale", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));
	if (tempLabel == NULL )
	{
		FPRINTF("[Line : %d][%s] account_type_get_label_by_locale API Call Failed\n", __LINE__, API_NAMESPACE);
		memset(g_szLabel, 0, sizeof(g_szLabel));
		memset(g_szLocale, 0, sizeof(g_szLocale));
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	tempLabel = NULL;
	memset(g_szLabel, 0, sizeof(g_szLabel));
	memset(g_szLocale, 0, sizeof(g_szLocale));

	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}

//& purpose: Retrieves label information for the given application id.
//& type: auto
/**
* @testcase 			ITc_account_type_query_label_by_app_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves label information for the given application id
* @scenario				Create Account Type Handle and Set the application id and label\n
*						Insert Account Type  Handle with given application id into DB\n
*						Retrieves label information for the given application id
* @apicovered			account_type_create, account_type_query_app_id_exist, account_type_query_label_by_app_id
* @passcase				When account_type_query_label_by_app_id is successful
* @failcase				If target account_type_query_label_by_app_id fails or any precondition and postcondition API fails
* @precondition			Creates a account type handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account type handle and releases all its resources
*/
int ITc_account_type_query_label_by_app_id_p(void)
{
	START_TEST;

	int nAccountTimeoutId = 0;
	account_type_h accountTypeHandle = NULL;

	int nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));

	nRet = account_type_query_app_id_exist(g_pstrAppId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_app_id_exist", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	g_bAccountLabelCB = false;
	memset(g_szLabel, 0, sizeof(g_szLabel));

	nRet = account_type_query_label_by_app_id(AccountLabelCB, g_pstrAppId, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_label_by_app_id", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));
	RUN_POLLING_LOOP;
	if (!g_bAccountLabelCB)
	{
		FPRINTF("[Line : %d][%s] AccountLabelCB not invoked\n", __LINE__, API_NAMESPACE);
		memset(g_szLabel, 0, sizeof(g_szLabel));
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}
	memset(g_szLabel, 0, sizeof(g_szLabel));
	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}

//& purpose: Check whether in DB Account Handle exist with given APP ID and Service Provider ID.
//& type: auto
/**
* @testcase 			ITc_account_type_query_supported_feature_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Check whether in DB Account Handle exist with given APP ID and Service Provider ID
* @scenario				Create Account Type Handle and Set the application id and Service Provider Id\n
*						Insert/Update Account Type  Handle with given application id into DB\n
*						Check whether in DB Account Handle exist with given APP ID and Service Provider ID
* @apicovered			account_type_create, account_type_query_supported_feature
* @passcase				When account_type_query_supported_feature are successful
* @failcase				If target account_type_query_supported_feature or any precondition and postcondition API fails
* @precondition			Creates a account type handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account type handle and releases all its resources
*/
int ITc_account_type_query_supported_feature_p(void)
{
	START_TEST;

	account_type_h accountTypeHandle = NULL;

	int nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));

	nRet = account_type_query_app_id_exist(g_pstrAppId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_app_id_exist", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	g_bAccountFeatureSupported = false;
	g_bAccountFeatureSupported = account_type_query_supported_feature(g_pstrAppId, (char *)SERVICEPROID);
	if (!g_bAccountFeatureSupported)
	{
		FPRINTF("\\n[Line : %d][%s] account_type_query_supported_feature failed.\n", __LINE__, API_NAMESPACE);
		AcountTypeDestroyHelper(accountTypeHandle);
		return 1;
	}

	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}

//& purpose: Checks whether the given app id exists in database And then Updates the account details in the account database.
//& type: auto
/**
* @testcase 			ITc_account_type_query_app_id_exist_update_to_db_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Checks whether the given app id exists in database And then Updates the account details in the account database.
* @scenario				Create Account Type Handle and Set the application id
*						Insert Account Type  Handle with given application id into DB\n
*						Set the Label of the given account type handle\n
*						Checks whether the given app id exists in database\n
*						Updates the account details in the account database
* @apicovered			account_type_create
* @passcase				When account_type_query_app_id_exist is successful
* @failcase				If target APIs account_type_query_app_id_exist or any precondition and postcondition API fails
* @precondition			Creates a account type handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account type handle and releases all its resources
*/
int ITc_account_type_query_app_id_exist_update_to_db_p(void)
{
	START_TEST;

	account_type_h accountTypeHandle = NULL;

	int nRet = account_type_create(&accountTypeHandle);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_create", AccManagerGetErrorMSG(nRet));

	nRet = account_type_query_app_id_exist(g_pstrAppId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_app_id_exist", AccManagerGetErrorMSG(nRet),AcountTypeDestroyHelper(accountTypeHandle));

	AcountTypeDestroyHelper(accountTypeHandle);
	return 0;
}

//& purpose: Inserts the account details to the account database And Deletes the account from the account database by account ID..
//& type: auto
/**
* @testcase 			ITc_account_insert_to_db_delete_by_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Inserts the account details to the account database And Deletes the account from the account database by account ID
* @scenario				Set account handler various properties like user name, domain name, package name, etc.\n
*						Inserts the account details to the account database\n
*						Deletes the account from the account database by account ID
* @apicovered			account_insert_to_db, account_delete_from_db_by_id
* @passcase				When account_insert_to_db(), account_delete_from_db_by_id are successful
* @failcase				If target API's account_insert_to_db()or account_delete_from_db_by_id fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_insert_to_db_delete_by_id_p(void)
{
	START_TEST;

	g_AccId = -1;
	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}

	int nAccId = -1;
	int nRet = account_insert_to_db(g_account, &nAccId);
	FPRINTF("[Line : %d][%s] Value of Account ID is :: %d\\n", __LINE__, API_NAMESPACE, nAccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(nAccId  == -1)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db failed.  nAccId is -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_delete_from_db_by_id(nAccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_delete_from_db_by_id", AccManagerGetErrorMSG(nRet));

	return 0;
}

//& purpose: Retrieves account details with the account database ID.
//& type: auto
/**
* @testcase 			ITc_account_query_account_by_account_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves account details with the account database ID
* @scenario				Retrieves accounts detail with the account database ID
* @apicovered			account_insert_to_db and account_delete_from_db_by_id
* @passcase				When account_query_account_by_account_id is successful
* @failcase				If target account_query_account_by_account_id fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_query_account_by_account_id_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId  < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db failed.  g_AccId is -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet =  account_query_account_by_account_id(g_AccId, &g_account);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_account_by_account_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId));

	if(g_account == NULL)
	{
		FPRINTF("[Line : %d][%s] account_query_account_by_account_id failed.  g_account is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char *pszGetEmail = NULL;
	nRet = account_get_email_address(g_account, &pszGetEmail);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_email_address", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId));
	if ( pszGetEmail == NULL || strcmp((char *)EMAILID, pszGetEmail) != 0 )
	{
		FPRINTF("[Line : %d][%s] account_get_email_address API Call Failed as retrieved email ID Values mismatchexpected value is: %s, and retrieved value is: %s\\n", __LINE__, API_NAMESPACE, EMAILID, pszGetEmail);
		FREE_MEMORY(pszGetEmail);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	FREE_MEMORY(pszGetEmail);
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Retrieves all accounts with the given user name then updates the account details in database.
//& type: auto
/**
* @testcase 			ITc_account_query_from_db_update_by_user_name_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all accounts with the given user name then updates the account details in database
* @scenario				Connect to DB and fetch the AccountID and Account Handle\n
*						Set account handler properties like package name\n
*						Retrieves all accounts with the given user name\n
*						Set the display Name of the account\n
*						Updates the account details in the account database
* @apicovered			account_set_display_name and account_insert_to_db()
* @passcase				When account_query_account_by_user_name(), account_update_to_db_by_user_name are successful
* @failcase				If target API's account_query_account_by_user_name()or account_update_to_db_by_user_name fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_query_from_db_update_by_user_name_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}
	char *pszGetUserName = NULL;
	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nAccountTimeoutId = 0;
	g_bAccountCB = false;
	nRet = account_query_account_by_user_name(AccountCallback, (char *)USERNAME, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_account_by_user_name", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););
	RUN_POLLING_LOOP;
	if ( !g_bAccountCB )
	{
		FPRINTF("[Line : %d][%s] AccountCallback not invoked\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	char szSetDisplayName[] = "TEST_TIZEN";
	nRet = account_set_display_name(g_account, szSetDisplayName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_display_name", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_user_name(g_account, (char *)USERNAME, g_pstrAppId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_user_name", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_get_user_name(g_account, &pszGetUserName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_user_name", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	if(pszGetUserName == NULL)
	{
		FPRINTF("[Line : %d][%s] account_get_user_name failed. User name is NULL\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	if ( strcmp((char *)USERNAME, pszGetUserName) != 0 )
	{
		FPRINTF("[Line : %d][%s] account_get_user_name API Call Failed Set and Get values mismatch. Set value is: %s, Get value is: %s\\n", __LINE__, API_NAMESPACE, (char *)USERNAME, pszGetUserName);
		FREE_MEMORY(pszGetUserName);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	g_bAccountCB = false;
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Retrieves all accounts' details by iterative invocation of the given callback function.
//& type: auto
/**
* @testcase 			ITc_account_foreach_account_from_db_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all accounts' details by iterative invocation of the given callback function
* @scenario				Retrieves all accounts' details by iterative invocation of the given callback function
* @apicovered			account_foreach_account_from_db
* @passcase				When account_foreach_account_from_db is successful
* @failcase				If target API account_foreach_account_from_db or any precondition and postcondition API fails
* @precondition			Creates a account handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account handle and releases all its resources
*/
int ITc_account_foreach_account_from_db_p(void)
{
	START_TEST;

	int nAccountTimeoutId = 0;
	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	if(nRet == ACCOUNT_ERROR_DUPLICATED)
	{
		FPRINTF("[Line : %d][%s] Account already exists\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));
	}

	g_bAccountCB = false;
	nRet = account_foreach_account_from_db(AccountCallback, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_foreach_account_from_db", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););
	RUN_POLLING_LOOP;
	if ( !g_bAccountCB )
	{
		FPRINTF("[Line : %d][%s] AccountCallback not invoked\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Retrieves the number of accounts in the account database.
//& type: auto
/**
* @testcase 			ITc_account_get_total_count_from_db_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves the number of accounts in the account database
* @scenario				Retrieves the number of accounts in the account database.(As in TC precondition One Account is added manually)
* @apicovered			account_insert_to_db,account_get_total_count_from_db and account_delete_from_db_by_id
* @passcase				When account_get_total_count_from_db is successful
* @failcase				If target API account_get_total_count_from_db or any precondition and postcondition API fails
* @precondition			Creates a account handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account handle and releases all its resources
*/
int ITc_account_get_total_count_from_db_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nUpdatedCount = -1;
	nRet = account_get_total_count_from_db(&nUpdatedCount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_total_count_from_db", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););
	FPRINTF("[Line : %d][%s]Total Count = %d\\n", __LINE__, API_NAMESPACE, nUpdatedCount);
	if ( nUpdatedCount <= 0 )
	{
		FPRINTF("[Line : %d][%s] account_get_total_count_from_db Failed as Updated Count = %d\\n", __LINE__, API_NAMESPACE, nUpdatedCount);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Gets the id of the account.
//& type: auto
/**
* @testcase 			ITc_account_get_account_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the id of the account
* @scenario				Connect to DB and fetch the Account using for-each\n
*						Gets the id of the account and compare it with the Id returned by AccountCallback when account_foreach_account_from_db is invoked.
* @apicovered			account_insert_to_db ,account_get_account_id and account_delete_from_db_by_id
* @passcase				When account_get_account_id is successful
* @failcase				If target API account_get_account_id or any precondition and postcondition API fails
* @precondition			Creates a account handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account handle and releases all its resources
*/
int ITc_account_get_account_id_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s]  account_insert_to_db failed. g_AccId is negative\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_query_account_by_account_id(g_AccId, &g_account);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_account_by_account_id", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););


	int nReturnedAccId = -1;
	nRet = account_get_account_id(g_account, &nReturnedAccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_account_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId));

	if(nReturnedAccId < 0)
	{
		FPRINTF("[Line : %d][%s]  account_get_account_id failed. nReturnedAccId is negative\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(nReturnedAccId != g_AccId)
	{
		FPRINTF("[Line : %d][%s]  Id returned by account_get_account_id not matched with inserted id\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Updates the account details in the account database without checking the provider's permission.
//& type: auto
/**
* @testcase 			ITc_account_update_to_db_by_id_ex_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Updates the account details in the account database without checking the provider's permission
* @scenario				Connect to DB and fetch the AccountID\n
*						Retrieves accounts detail with the account database ID\n
*						Set the Display Name of Account and then Update the Account Details in DB
* @apicovered			account_query_account_by_account_id
* @passcase				When account_update_to_db_by_id_ex is successful
* @failcase				If target API account_update_to_db_by_id_ex or any precondition and postcondition API fails
* @precondition			Creates a account handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account handle and releases all its resources
*/
int ITc_account_update_to_db_by_id_ex_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s]  account_insert_to_db failed. g_AccId is negative\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char szSetDisplayName[] = "TEST_TIZEN";
	nRet = account_set_display_name(g_account, szSetDisplayName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_display_name", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id_ex(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id_ex", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	account_h hAccount = NULL;
	nRet = account_create(&hAccount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_create", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	if(hAccount == NULL)
	{
		FPRINTF("[Line : %d][%s]  account_create failed. hAccount is NULL\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	nRet = account_query_account_by_account_id(g_AccId, &hAccount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_account_by_account_id", AccManagerGetErrorMSG(nRet),account_destroy(hAccount);account_delete_from_db_by_id(g_AccId););

	if(hAccount == NULL)
	{
		FPRINTF("[Line : %d][%s]  account_query_account_by_account_id failed. hAccount is NULL\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	char *pszGetDisplayName = NULL;
	nRet = account_get_display_name(hAccount, &pszGetDisplayName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_display_name", AccManagerGetErrorMSG(nRet),account_destroy(hAccount);account_delete_from_db_by_id(g_AccId););
	if ( pszGetDisplayName == NULL || strcmp(szSetDisplayName, pszGetDisplayName) != 0 )
	{
		FPRINTF("[Line : %d][%s] account_get_display_name failed\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetDisplayName);
		account_destroy(hAccount);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}
	FREE_MEMORY(pszGetDisplayName);
	account_destroy(hAccount);
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Changes sync status of account with the given account id in DB.
//& type: auto
/**
* @testcase 			ITc_account_update_sync_status_by_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Changes sync status of account with the given account id in DB
* @scenario				Create Account Handle and Set the username and application package associated with Account\n
*						Connect to DB and fetch the AccountID\n
*						Insert Account Handle into DB if fetched Id is not greater then 0\n
*						Changes sync status of account with the given account id in DB\n
*						Deletes the inserted account from the account database by account ID
* @apicovered			account_insert_to_db and account_delete_from_db_by_id
* @passcase				When account_update_sync_status_by_id is successful
* @failcase				If target API account_update_sync_status_by_id or any precondition and postcondition API fails
* @precondition			Creates a account handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account handle and releases all its resources
*/
int ITc_account_update_sync_status_by_id_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}
	account_h lAccount = NULL;
	account_sync_state_e eSyncState = -1;

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s]  account_insert_to_db failed. g_AccId is negative\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

    nRet = account_update_sync_status_by_id(g_AccId, ACCOUNT_SYNC_STATUS_IDLE);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_sync_status_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_create(&lAccount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_create", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_query_account_by_account_id(g_AccId, &lAccount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_account_by_account_id", AccManagerGetErrorMSG(nRet), account_destroy(lAccount); account_delete_from_db_by_id(g_AccId););

	nRet = account_get_sync_support(lAccount, &eSyncState);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_sync_support", AccManagerGetErrorMSG(nRet), account_destroy(lAccount); account_delete_from_db_by_id(g_AccId););

	if(eSyncState != ACCOUNT_SYNC_STATUS_IDLE)
	{
		FPRINTF("[Line : %d][%s] Sync status does not match with existing account\\n", __LINE__, API_NAMESPACE);
		account_destroy(lAccount);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	account_destroy(lAccount);
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Retrieves capabilities with the given account database ID.
//& type: auto
/**
* @testcase 			ITc_account_query_capability_by_account_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves capabilities with the given account database ID
* @scenario				Connect to DB, Retrieves account with given ID using for-each API\n
*						Set the capability to retrieved Account and update it in DB\n
*						Retrieves capabilities with the given account database ID
* @apicovered			account_set_capability and  account_update_to_db_by_id_ex
* @passcase				When account_query_capability_by_account_id is successful
* @failcase				If target API account_query_capability_by_account_id or any precondition and postcondition API fails
* @precondition			Creates a account handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account handle and releases all its resources
*/
int ITc_account_query_capability_by_account_id_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_capability(g_account, (char *)CALENDAR_CAPABILITY, ACCOUNT_CAPABILITY_ENABLED);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_capability", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id_ex(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id_ex", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	g_capability_state = -1;
	int nAccountTimeoutId = 0;
	nRet = account_query_capability_by_account_id(AccountCapabilityCB, g_AccId, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_capability_by_account_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););
	RUN_POLLING_LOOP;
	if ( g_capability_state != ACCOUNT_CAPABILITY_ENABLED )
	{
		FPRINTF("[Line : %d][%s] account_query_capability_by_account_id API Call Failed Set and Get values mismatchSet Capability State is: %s, Get State is: %s\n", __LINE__, API_NAMESPACE, AccountGetCapabilityState(ACCOUNT_CAPABILITY_ENABLED), AccountGetCapabilityState(g_capability_state));
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	g_capability_state = -1;
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Retrieves all accounts with the given capability type.
//& type: auto
/**
* @testcase 			ITc_account_query_account_by_capability_type_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all accounts with the given capability type
* @scenario				Connect to DB, Retrieves account with given ID using for-each API\n
*						Set the capability to retrieved Account and update it in DB\n
*						Retrieves all accounts with the given capability type
* @apicovered			account_set_capability and account_update_to_db_by_id_ex
* @passcase				When  account_query_account_by_capability_type is successful
* @failcase				If target API  account_query_account_by_capability_type or any precondition and postcondition API fails
* @precondition			Creates a account handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account handle and releases all its resources
*/
int ITc_account_query_account_by_capability_type_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}
	account_capability_state_e eCapability = -1;
	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_capability(g_account, (char *)CALENDAR_CAPABILITY, ACCOUNT_CAPABILITY_ENABLED);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_capability", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id_ex(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id_ex", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	g_bAccountCB = false;
	int nAccountTimeoutId = 0;

	nRet =  account_query_account_by_capability_type(AccountCallback, (char *)CALENDAR_CAPABILITY, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_account_by_capability_type", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););
	RUN_POLLING_LOOP;
	if ( !g_bAccountCB )
	{
		FPRINTF("[Line : %d][%s] AccountCallback not invoked\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	nRet = account_get_capability(g_account, (char *)CALENDAR_CAPABILITY, &eCapability);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_capability", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	if(eCapability != ACCOUNT_CAPABILITY_ENABLED)
	{
		FPRINTF("[Line : %d][%s] Set and get value not matched\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	g_bAccountCB = false;
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Retrieves all accounts with the given capability type and capability value.
//& type: auto
/**
* @testcase 			ITc_account_query_account_by_capability_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all accounts with the given capability type and capability value
* @scenario				Connect to DB, Retrieves account with given ID using for-each API\n
*						Set the capability to retrieved Account and update it in DB\n
*						Retrieves all accounts with the given capability type and capability value
* @apicovered			account_set_capability and account_update_to_db_by_id_ex
* @passcase				When  account_query_account_by_capability is successful
* @failcase				If target API  account_query_account_by_capability or any precondition and postcondition API fails
* @precondition			Creates a account handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account handle and releases all its resources
*/
int ITc_account_query_account_by_capability_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}
	account_capability_state_e eCapability = -1;
	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. g_AccId is negative\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_set_capability(g_account, (char *)CALENDAR_CAPABILITY, ACCOUNT_CAPABILITY_ENABLED);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_capability", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id_ex(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id_ex", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	g_bAccountCB = false;
	int nAccountTimeoutId = 0;
	nRet =  account_query_account_by_capability(AccountCallback, (char *)CALENDAR_CAPABILITY, ACCOUNT_CAPABILITY_ENABLED, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_account_by_capability", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););
	RUN_POLLING_LOOP;
	if ( !g_bAccountCB )
	{
		FPRINTF("[Line : %d][%s] AccountCallback not invoked\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	nRet = account_get_capability(g_account, (char *)CALENDAR_CAPABILITY, &eCapability);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_capability", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	if(eCapability != ACCOUNT_CAPABILITY_ENABLED)
	{
		FPRINTF("[Line : %d][%s] Set and get value not matched\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	g_bAccountCB = false;
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Updates the account details in the account database.
//& type: auto
/**
* @testcase 			ITc_account_update_to_db_by_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Updates the account details in the account database
* @scenario				Connect to DB and fetch the AccountID\n
*						Retrieves accounts detail with the account database ID\n
*						Set the Display Name of Account and then Update the Account Details in DB
* @apicovered			account_insert_to_db, account_set_display_name, account_get_display_name, account_create and account_query_account_by_account_id
* @passcase				When account_update_to_db_by_id is successful
* @failcase				If target API account_update_to_db_by_id or any precondition and postcondition API fails
* @precondition			Creates a account handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account handle and releases all its resources
*/
int ITc_account_update_to_db_by_id_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}

	int nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(g_AccId < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db failed. g_AccId is negative\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char szSetDisplayName[] = "TEST_TIZEN";
	nRet = account_set_display_name(g_account, szSetDisplayName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_set_display_name", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_id(g_account, g_AccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_update_to_db_by_id", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	account_h hAccount = NULL;
	nRet = account_create(&hAccount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_create", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	if(hAccount == NULL)
	{
		FPRINTF("[Line : %d][%s] account_create failed. hAccount is NULL\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	nRet = account_query_account_by_account_id(g_AccId, &hAccount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_account_by_account_id", AccManagerGetErrorMSG(nRet),account_destroy(hAccount);account_delete_from_db_by_id(g_AccId););

	if(hAccount == NULL)
	{
		FPRINTF("[Line : %d][%s] account_query_account_by_account_id failed. hAccount is NULL\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	char *pszGetDisplayName = NULL;
	nRet = account_get_display_name(hAccount, &pszGetDisplayName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_display_name", AccManagerGetErrorMSG(nRet),account_destroy(hAccount);account_delete_from_db_by_id(g_AccId););
	if ( pszGetDisplayName == NULL || strcmp(szSetDisplayName, pszGetDisplayName) != 0 )
	{
		FPRINTF("[Line : %d][%s] Set and get value mismatch\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetDisplayName);
		account_destroy(hAccount);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	FREE_MEMORY(pszGetDisplayName);
	account_destroy(hAccount);
	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Retrieves label information for the given application Locale.
//& type: auto
/**
* @testcase             ITc_account_type_query_label_by_locale_p
* @since_tizen          2.3
* @author            	SRID(nibha.sharma)
* @reviewer             SRID(gupta.sanjay)
* @type                 auto
* @description          Retrieves label information for the given application Locale.
* @scenario				- Create Account Type Handle and Set the application id and label.
*						- Insert Account Type  Handle with given application id into DB.
* 						- Retrieves label information for the given application id.
* @apicovered			account_type_query_label_by_locale
* @passcase				When account_type_query_label_by_locale are successful.
* @failcase				If target account_type_query_label_by_locale fails or any precondition and postcondition api fails.
* @precondition			Creates a account type handle and Connect to DB.
* @postcondition		Disconnect DB, Destroys the account type handle and releases all its resources.
*/
int ITc_account_type_query_label_by_locale_p(void)
{
	START_TEST;

	char *pszLabelValue = NULL;
	const char* pszLocale = "en_US";

	int nRet = account_type_query_label_by_locale(APPID, pszLocale, &pszLabelValue);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_type_query_label_by_locale", AccManagerGetErrorMSG(nRet));

	if (pszLabelValue == NULL )
	{
		FPRINTF("[Line : %d][%s] account_type_query_label_by_locale API Call Failed\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(pszLabelValue);
	return 0;
}

//& purpose: Deletes the account from the account database by package name.
//& type: auto
/**
* @testcase 			ITc_account_delete_from_db_by_package_name_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Deletes the account from the account database by package name
* @scenario				Retrieves account with given ID using for-each API, and Delete it using given id\n
*						Set account handler properties like user name AND package name\n
*						Insert the Account(having username and package name) to DB\n
*						Deletes the account from the account database by package name
* @apicovered			account_insert_to_db and account_delete_from_db_by_id
* @passcase				When account_delete_from_db_by_package_name is successful
* @failcase				If target API account_delete_from_db_by_package_name fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_delete_from_db_by_package_name_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}

	int nAccId = -1;
	int nRet = account_insert_to_db(g_account, &nAccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(nAccId == -1)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. nAccId is -1\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_delete_from_db_by_package_name(g_pstrAppId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_delete_from_db_by_package_name", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_query_account_by_package_name(AccountCallback, g_pstrAppId, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_RECORD_NOT_FOUND, nRet, "account_query_account_by_package_name", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(g_AccId););

	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Deletes the account from the account database by user name.
//& type: auto
/**
* @testcase 			ITc_account_delete_by_user_name_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Deletes the account from the account database by user name
* @scenario				Retrieves account with given ID using for-each API, and Delete it using given id\n
*						Set account handler properties like user name AND package name\n
*						Insert the Account(having username and package name) to DB\n
*						Deletes the account from the account database by user name
* @apicovered			account_insert_to_db and account_delete_from_db_by_id
* @passcase				When account_delete_from_db_by_user_name is successful
* @failcase				If target API account_delete_from_db_by_user_name fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_delete_by_user_name_p(void)
{
	START_TEST;

	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}

	int nAccId = -1;
	int nRet = account_insert_to_db(g_account, &nAccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	if(nAccId == -1)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db API Call Failed. nAccId is -1\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_delete_from_db_by_user_name((char *)USERNAME, g_pstrAppId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_delete_from_db_by_user_name", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););

	nRet = account_update_to_db_by_user_name(g_account, (char *)USERNAME, g_pstrAppId);
	PRINT_RESULT(ACCOUNT_ERROR_RECORD_NOT_FOUND, nRet, "account_update_to_db_by_user_name", AccManagerGetErrorMSG(nRet));

	return 0;
}

//& purpose: Retrieves account details with the provider feature.
//& type: auto
/**
* @testcase 			ITc_account_type_query_by_provider_feature_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves account details with the provider feature
* @scenario				Retrieves accounts detail with the provider feature
* @apicovered			account_insert_to_db and account_delete_from_db_by_id
* @passcase				When account_type_query_by_provider_feature is successful
* @failcase				If target account_type_query_by_provider_feature fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_type_query_by_provider_feature_p(void)
{
	START_TEST;

	int nAccountTimeoutId = 0;
	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}

	int nRet = account_set_capability(g_account, (char *)CALENDAR_CAPABILITY, ACCOUNT_CAPABILITY_ENABLED);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));

	nRet =  account_insert_to_db(g_account, &g_AccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));
	if(g_AccId  < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db failed.  g_AccId is -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bAccountTypeCB = false;
	nRet =  account_type_query_by_provider_feature(AccountProviderFeatureCallback, CALENDAR_CAPABILITY, NULL);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_type_query_by_provider_feature", AccManagerGetErrorMSG(nRet),account_delete_from_db_by_id(g_AccId););
	RUN_POLLING_LOOP;
	if ( !g_bAccountTypeCB )
	{
		FPRINTF("[Line : %d][%s] AccountProviderFeatureCallback not invoked\\n", __LINE__, API_NAMESPACE);
		account_delete_from_db_by_id(g_AccId);
		return 1;
	}

	account_delete_from_db_by_id(g_AccId);
	return 0;
}

//& purpose: Retrieves deleted account with the account ID.
//& type: auto
/**
* @testcase			ITc_account_query_deleted_account_info_by_account_id_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type			auto
* @description			Retrieves deleted account with the account ID.
* @scenario			set user name, package name capabity and insert account to DB
*				query acc by acc ID, delete account by acc ID, retrive deleted acc by ID
*				compare all set attributes with retrived attributes.
* @apicovered			account_query_deleted_account_info_by_account_id
* @passcase			When Target API is successful and retrived value matches
* @failcase			If target API fails or any precondition and postcondition API fails
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int ITc_account_query_deleted_account_info_by_account_id_p(void)
{

	START_TEST;

	int nRet = ACCOUNT_ERROR_NONE;
	int nAccId = -1;
	account_h hRetAccount = NULL;
	account_h hDelAccount = NULL;
	char* pszRetUsrName = NULL;
	char* pszDelUsrName = NULL;
	char* pszRetPkgName = NULL;
	char* pszDelPkgName = NULL;

	account_capability_state_e eRetCapabilityType = 0;
	account_capability_state_e eDelCapabilityType = 0;
	char pszSetUserName[] = "TEST_TIZEN";

	nRet = account_set_user_name(g_account, pszSetUserName);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_set_user_name", AccManagerGetErrorMSG(nRet));

	nRet = account_set_package_name(g_account, g_pstrAppId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_set_package_name", AccManagerGetErrorMSG(nRet));

	nRet = account_set_capability(g_account, (char *)CALENDAR_CAPABILITY, ACCOUNT_CAPABILITY_ENABLED);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_set_capability", AccManagerGetErrorMSG(nRet));

	nRet =  account_insert_to_db(g_account, &nAccId);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));
	if(nAccId  < 0)
	{
		FPRINTF("[Line : %d][%s] account_insert_to_db failed. nAccId is -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_create(&hRetAccount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_create", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(nAccId););
	CHECK_HANDLE_CLEANUP(hRetAccount, "account_create", account_delete_from_db_by_id(nAccId));

	nRet = account_query_account_by_account_id(nAccId, &hRetAccount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_account_by_account_id", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(nAccId); account_destroy(hRetAccount));
	CHECK_HANDLE_CLEANUP(hRetAccount, "account_query_account_by_account_id", account_delete_from_db_by_id(nAccId); account_destroy(hRetAccount));

	nRet = account_delete_from_db_by_id(nAccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_delete_from_db_by_id", AccManagerGetErrorMSG(nRet), account_destroy(hRetAccount));

	nRet = account_create(&hDelAccount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_create", AccManagerGetErrorMSG(nRet), account_destroy(hRetAccount));
	CHECK_HANDLE_CLEANUP(hRetAccount, "account_create", account_destroy(hRetAccount));

	//Target API
	nRet = account_query_deleted_account_info_by_account_id(nAccId, &hDelAccount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_deleted_account_info_by_account_id", AccManagerGetErrorMSG(nRet), account_destroy(hRetAccount); account_destroy(hDelAccount));

	nRet = account_get_user_name(hRetAccount, &pszRetUsrName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_user_name", AccManagerGetErrorMSG(nRet), account_destroy(hRetAccount); account_destroy(hDelAccount));

	nRet = account_get_user_name(hDelAccount, &pszDelUsrName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_user_name", AccManagerGetErrorMSG(nRet), account_destroy(hRetAccount); account_destroy(hDelAccount); FREE_MEMORY(pszRetUsrName));

	nRet = account_get_package_name(hRetAccount, &pszRetPkgName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_package_name", AccManagerGetErrorMSG(nRet), account_destroy(hRetAccount); account_destroy(hDelAccount); FREE_MEMORY(pszRetUsrName); FREE_MEMORY(pszDelUsrName));

	nRet = account_get_package_name(hDelAccount, &pszDelPkgName);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_package_name", AccManagerGetErrorMSG(nRet), account_destroy(hRetAccount); account_destroy(hDelAccount); FREE_MEMORY(pszRetUsrName); FREE_MEMORY(pszDelUsrName); FREE_MEMORY(pszRetPkgName));

	nRet = account_get_capability(hRetAccount, (char *)CALENDAR_CAPABILITY, &eRetCapabilityType);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_capability", AccManagerGetErrorMSG(nRet), account_destroy(hRetAccount); account_destroy(hDelAccount); FREE_MEMORY(pszRetUsrName); FREE_MEMORY(pszDelUsrName); FREE_MEMORY(pszRetPkgName); FREE_MEMORY(pszDelPkgName));
	PRINT_RESULT_CLEANUP(ACCOUNT_CAPABILITY_ENABLED, eRetCapabilityType, "account_get_capability", "Set and Get values mismatch Capability State", account_destroy(hRetAccount); account_destroy(hDelAccount); FREE_MEMORY(pszRetUsrName); FREE_MEMORY(pszDelUsrName); FREE_MEMORY(pszRetPkgName); FREE_MEMORY(pszDelPkgName));

	nRet = account_get_capability(hDelAccount, (char *)CALENDAR_CAPABILITY, &eDelCapabilityType);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_get_capability", AccManagerGetErrorMSG(nRet), account_delete_from_db_by_id(nAccId); FREE_MEMORY(pszRetUsrName); FREE_MEMORY(pszDelUsrName); FREE_MEMORY(pszRetPkgName); FREE_MEMORY(pszDelPkgName));
	PRINT_RESULT_CLEANUP(ACCOUNT_CAPABILITY_ENABLED, eDelCapabilityType, "account_get_capability", "Set and Get values mismatch Capability State", account_destroy(hRetAccount); account_destroy(hDelAccount); FREE_MEMORY(pszRetUsrName); FREE_MEMORY(pszDelUsrName); FREE_MEMORY(pszRetPkgName); FREE_MEMORY(pszDelPkgName));

	PRINT_RESULT_CLEANUP(0, strncmp(pszRetUsrName, pszSetUserName, sizeof(pszSetUserName)-1) , "account_get_user_name", "Set and Get user names are different", account_delete_from_db_by_id(nAccId); FREE_MEMORY(pszRetUsrName); FREE_MEMORY(pszDelUsrName); FREE_MEMORY(pszRetPkgName); FREE_MEMORY(pszDelPkgName));

	PRINT_RESULT_CLEANUP(0, strncmp(pszDelUsrName, pszSetUserName, sizeof(pszSetUserName)-1) , "account_get_user_name", "Set and Get user names are different", account_delete_from_db_by_id(nAccId); FREE_MEMORY(pszRetUsrName); FREE_MEMORY(pszDelUsrName); FREE_MEMORY(pszRetPkgName); FREE_MEMORY(pszDelPkgName));

	PRINT_RESULT_CLEANUP(0, strncmp(pszRetPkgName, g_pstrAppId, sizeof(pszSetUserName)-1) , "account_get_package_name", "Set and Get package names are different", account_delete_from_db_by_id(nAccId); FREE_MEMORY(pszRetUsrName); FREE_MEMORY(pszDelUsrName); FREE_MEMORY(pszRetPkgName); FREE_MEMORY(pszDelPkgName));

	PRINT_RESULT_CLEANUP(0, strncmp(pszDelPkgName, g_pstrAppId, sizeof(pszSetUserName)-1) , "account_get_package_name", "Set and Get package names are different", account_delete_from_db_by_id(nAccId); FREE_MEMORY(pszRetUsrName); FREE_MEMORY(pszDelUsrName); FREE_MEMORY(pszRetPkgName); FREE_MEMORY(pszDelPkgName));

	FREE_MEMORY(pszRetUsrName);
	FREE_MEMORY(pszDelUsrName);
	FREE_MEMORY(pszRetPkgName);
	FREE_MEMORY(pszDelPkgName);

	nRet = account_destroy(hRetAccount);
	PRINT_RESULT_NORETURN(ACCOUNT_ERROR_NONE, nRet, "account_destroy", AccManagerGetErrorMSG(nRet));

	nRet = account_destroy(hDelAccount);
	PRINT_RESULT_NORETURN(ACCOUNT_ERROR_NONE, nRet, "account_destroy", AccManagerGetErrorMSG(nRet));

	return 0;
}

/** @} */
/** @} */
