#include "CTs-platform-permission-common.h"
#include <pthread.h>
#include <account.h>
#include <glib.h>
#include <app.h>
#define TEST_PACKAGE_NAME		"org.tizen.platform-permission-native-ctc"	// app_id
#define USER_NAME				"user_name"
#define ICONPATH	            "icontexto_256.png"
#define SERVICEPROID	        "http://tizen.org/account/capability/contact"
#define TIMEOUT_CB				10000
#define ACCESSTOKEN             "access-token"
#define EMAILID					"TCTSampleAccount@tizen.org"
#define USERNAME				"TizenLite Test"
#define PATH_LEN				1024
#define BUFFERSIZE				256
#define BUFFERLEN					20
#define CALENDAR_CAPABILITY		ACCOUNT_SUPPORTS_CAPABILITY_CONTACT 
#define CONTACT_CAPABILITY		"http://tizen.org/account/capability/contact"
#define SERVICE_PROVIDER_ID		"http://www.tizen.org/"
#define MULTIPLE_ACCOUNT_SUPPORT 1


#define RUN_POLLING_LOOP {\
	mainloop = g_main_loop_new(NULL, false);\
	nAccountTimeoutId = g_timeout_add(TIMEOUT_CB, AccountTimeout, mainloop);\
	g_main_loop_run(mainloop);\
	g_source_remove(nAccountTimeoutId);\
	mainloop = NULL;\
}
bool g_bAccountLabelCB;
account_h g_account;
int g_AccId = -1;
account_capability_state_e g_capability_state;
char g_szAppID[BUFFERSIZE] = {0};
char g_szLocale[BUFFERLEN] = {0};
char g_szLabel[BUFFERLEN] = {0};
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

char* AccManagerGetErrorMSG(int nRet)
{
	char* pszErrorMSG = NULL;

	switch ( nRet )
	{
	case ACCOUNT_ERROR_NONE:		    			pszErrorMSG = "ACCOUNT_ERROR_NONE";						break;
	case ACCOUNT_ERROR_INVALID_PARAMETER:			pszErrorMSG = "ACCOUNT_ERROR_INVALID_PARAMETER";		break;
	case ACCOUNT_ERROR_OUT_OF_MEMORY:				pszErrorMSG = "ACCOUNT_ERROR_OUT_OF_MEMORY";			break;
	case ACCOUNT_ERROR_DATABASE_BUSY:				pszErrorMSG = "ACCOUNT_ERROR_DATABASE_BUSY";			break;
	case ACCOUNT_ERROR_DUPLICATED:					pszErrorMSG = "ACCOUNT_ERROR_DUPLICATED";				break;
	case ACCOUNT_ERROR_NO_DATA:						pszErrorMSG = "ACCOUNT_ERROR_NO_DATA";					break;
	case ACCOUNT_ERROR_DB_FAILED:					pszErrorMSG = "ACCOUNT_ERROR_DB_FAILED";				break;
	case ACCOUNT_ERROR_NOT_ALLOW_MULTIPLE:			pszErrorMSG = "ACCOUNT_ERROR_NOT_ALLOW_MULTIPLE";		break;
	case ACCOUNT_ERROR_NOT_REGISTERED_PROVIDER:		pszErrorMSG = "ACCOUNT_ERROR_NOT_REGISTERED_PROVIDER";	break;
	case ACCOUNT_ERROR_EVENT_SUBSCRIPTION_FAIL:		pszErrorMSG = "ACCOUNT_ERROR_EVENT_SUBSCRIPTION_FAIL";	break;
	case ACCOUNT_ERROR_DB_NOT_OPENED:				pszErrorMSG = "ACCOUNT_ERROR_DB_NOT_OPENED";			break;
	case ACCOUNT_ERROR_QUERY_SYNTAX_ERROR:			pszErrorMSG = "ACCOUNT_ERROR_QUERY_SYNTAX_ERROR";		break;
	case ACCOUNT_ERROR_ITERATOR_END:				pszErrorMSG = "ACCOUNT_ERROR_ITERATOR_END";				break;
	case ACCOUNT_ERROR_NOTI_FAILED:					pszErrorMSG = "ACCOUNT_ERROR_NOTI_FAILED";				break;
	case ACCOUNT_ERROR_PERMISSION_DENIED:			pszErrorMSG = "ACCOUNT_ERROR_PERMISSION_DENIED";		break;
	case ACCOUNT_ERROR_XML_PARSE_FAILED:			pszErrorMSG = "ACCOUNT_ERROR_XML_PARSE_FAILED";			break;
	case ACCOUNT_ERROR_XML_FILE_NOT_FOUND:			pszErrorMSG = "ACCOUNT_ERROR_XML_FILE_NOT_FOUND";		break;
	default:										pszErrorMSG = "Unknown Error";
	}
	return pszErrorMSG;
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
* @function 		AccountEventCB
* @description	 	The callback function will be called when an account is removed from the database
* @parameter		event_type: event type associated with given Account Type Handle, account_id: account id, user_data: User data sent to callback
* @return 			bool: Status of Callback
*/
/*static bool AccountEventCB(const char* event_type, int account_id, void* user_data)
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
}*/
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
	account_get_user_name(g_account, &pszGetUserName);
	char *pszGetDomainName = NULL;
	account_get_domain_name(account, &pszGetDomainName);
	if ( pszGetDomainName != NULL )
	{
		free(pszGetDomainName);
		pszGetDomainName = NULL;
	}

	char *pszGetDisplayName = NULL;
	account_get_display_name(g_account, &pszGetDisplayName);
	if ( pszGetDisplayName != NULL )
	{
		free(pszGetDisplayName);
		pszGetDisplayName = NULL;
	}

	char *pszGetPackName = NULL;
	account_get_package_name(g_account, &pszGetPackName);
	if ( pszGetPackName != NULL )
	{
		free(pszGetPackName);
		pszGetPackName = NULL;
	}

	char *pszGetEmail = NULL;
	account_get_email_address(account, &pszGetEmail);

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
	account_type_get_app_id(account_type, &pszGetAppId);
	
	if ( pszGetAppId == NULL )
	{
		if ( mainloop )
		{
			g_main_loop_quit(mainloop);
		}
		return false;
	}

	if ( strncmp(g_pstrAppId, pszGetAppId, strlen(pszGetAppId))== 0 )
	{
		g_bAccountTypeCB = true;
	}

	if ( pszGetAppId != NULL )
	{
		FREE_MEMORY(pszGetAppId);
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
* @function 		AccountPreConditionHelper
* @description	 	Helper Function to clear the Desired Account from DB if Exist.
* @parameter		void
* @return 			boolean: result
*/
bool AccountPreConditionHelper(void)
{
	
	g_AccId = -1;
	int nRet = account_set_user_name(g_account, (char *)USER_NAME);
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
	
	
	return true;
}
/**
* @function 		CTs_platform_permission_accountsvc_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_accountsvc_startup(void)
{
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
	struct stat stBuff;
	int nRet = account_create(&g_account);
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
	memset(g_pstrAppId, 0, sizeof(g_pstrAppId));
	strncpy(g_pstrAppId, APPID, strlen(APPID)+1);

	g_bAccountCreation = true;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_platform_permission_accountsvc_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_accountsvc_cleanup(void)
{

	int nRet = account_destroy(g_account);
		if ( nRet != ACCOUNT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] account_destroy failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AccManagerGetErrorMSG(nRet));
		}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& purpose: Checking http://tizen.org/privilege/account.read and http://tizen.org/privilege/account.write privilege
//& type: auto
/**
* @testcase			CTc_AccountManager_PrivilegeAccountReadWrite_query_label_by_locale
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a handle to the account\n
* 					Gets the type query,app id,count of accounts and insert in the account database\n
* 					Destroys the account handle and releases all its resources
* @apicovered		account_type_query_label_by_locale
*					account_type_query_provider_feature_by_app_id
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_AccountManager_PrivilegeAccountReadWrite_query_label_by_locale(void)
{
	START_TEST;

	account_h hAccount = NULL;
	const char* locale = "en-us";
	const char* app_id = TEST_PACKAGE_NAME;
	char* ret_label = NULL;
	int nRet = account_create(&hAccount);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_create", AccManagerGetErrorMSG(nRet));
	if(hAccount == NULL)
	{
		FPRINTF("[Line : %d][%s] account_create failed. hAccount is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_type_query_label_by_locale(app_id, locale, &ret_label);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "account_type_query_label_by_locale", AccManagerGetErrorMSG(nRet), account_destroy(hAccount), ACCOUNT_ERROR_NONE);
	
	account_destroy(hAccount);
	
	return 0;
}
//& purpose: Checking http://tizen.org/privilege/account.read and http://tizen.org/privilege/account.write privilege
//& type: auto
/**
* @testcase			CTc_AccountManager_PrivilegeAccountReadWrite_query_app_id_exist
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a handle to the account\n
* 					Gets the type query,app id,count of accounts and insert in the account database\n
* 					Destroys the account handle and releases all its resources
* @apicovered		account_type_query_app_id_exist
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_AccountManager_PrivilegeAccountReadWrite_query_app_id_exist(void)
{
	START_TEST;

	account_h hAccount = NULL;
	const char* app_id1 = "account_type_query_app_id_exist";
	
	int nRet = account_create(&hAccount);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_create", AccManagerGetErrorMSG(nRet));
	if(hAccount == NULL)
	{
		FPRINTF("[Line : %d][%s] account_create failed. hAccount is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_type_query_app_id_exist(app_id1);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "account_type_query_app_id_exist", AccManagerGetErrorMSG(nRet), account_destroy(hAccount));

	account_destroy(hAccount);
	
	return 0;
}
//& purpose: Checking http://tizen.org/privilege/account.read and http://tizen.org/privilege/account.write privilege
//& type: auto
/**
* @testcase			CTc_AccountManager_PrivilegeAccountReadWrite_query_supported_feature
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a handle to the account\n
* 					Gets the type query,app id,count of accounts and insert in the account database\n
* 					Destroys the account handle and releases all its resources
* @apicovered		account_type_query_supported_feature
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_AccountManager_PrivilegeAccountReadWrite_query_supported_feature(void)
{
	START_TEST;

	account_h hAccount = NULL;
	int nRet = account_create(&hAccount);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_create", AccManagerGetErrorMSG(nRet));
	if(hAccount == NULL)
	{
		FPRINTF("[Line : %d][%s] account_create failed. hAccount is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bAccountFeatureSupported = account_type_query_supported_feature(g_pstrAppId, (char *)SERVICEPROID);
	nRet =get_last_result();
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "account_type_query_supported_feature", AccManagerGetErrorMSG(nRet), account_destroy(hAccount));
	
	account_destroy(hAccount);
	
	return 0;
}
//& purpose: Checking http://tizen.org/privilege/account.read and http://tizen.org/privilege/account.write privilege
//& type: auto
/**
* @testcase			CTc_AccountManager_PrivilegeAccountReadWrite_query_provider_feature_by_app_id
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a handle to the account\n
* 					Gets the type query,app id,count of accounts and insert in the account database\n
* 					Destroys the account handle and releases all its resources
* @apicovered		account_type_query_provider_feature_by_app_id					
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_AccountManager_PrivilegeAccountReadWrite_query_provider_feature_by_app_id(void)
{
	START_TEST;


	account_h hAccount = NULL;
	char *pProviderFeature = ACCOUNT_SUPPORTS_CAPABILITY_CONTACT;
	int nRet = account_create(&hAccount);
	PRINT_RESULT(ACCOUNT_ERROR_NONE, nRet, "account_create", AccManagerGetErrorMSG(nRet));
	if(hAccount == NULL)
	{
		FPRINTF("[Line : %d][%s] account_create failed. hAccount is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = account_type_query_provider_feature_by_app_id(ServiceProviderFeatureCB, g_pstrAppId, (void *)pProviderFeature);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "account_type_query_provider_feature_by_app_id", AccManagerGetErrorMSG(nRet), account_destroy(hAccount));
	
	account_destroy(hAccount);
	
	return 0;
}

//& purpose: Retrieves account details with the account database ID.
//& type: auto
/**
* @testcase 			CTc_AccountManager_PrivilegeAccountReadWrite_query_account_by_account_id
* @since_tizen 			2.3
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Retrieves account details with the account database ID
* @scenario				Retrieves accounts detail with the account database ID
* @apicovered			account_insert_to_db and account_delete_from_db_by_id
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int CTc_AccountManager_PrivilegeAccountReadWrite_query_account_by_account_id(void)
{
	START_TEST;
	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}
	
	int nRet =  account_query_account_by_account_id(11, &g_account);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "account_query_account_by_account_id", AccManagerGetErrorMSG(nRet));
	
	return 0;
}

//& purpose: Retrieves account details with the account database ID.
//& type: auto
/**
* @testcase 			CTc_AccountManager_PrivilegeAccountReadWrite_update_sync_status_by_id
* @since_tizen 			2.3
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Retrieves account details with the account database ID
* @scenario				Retrieves accounts detail with the account database ID
* @apicovered			aaccount_update_sync_status_by_id
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int CTc_AccountManager_PrivilegeAccountReadWrite_update_sync_status_by_id(void)
{
	START_TEST;
	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}
	int nRet = account_update_sync_status_by_id(11, ACCOUNT_SYNC_STATUS_IDLE);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "account_update_sync_status_by_id", AccManagerGetErrorMSG(nRet));
	

	return 0;
}

//& purpose: Retrieves account details with the account database Package Name.
//& type: auto
/**
* @testcase 			CTc_AccountManager_PrivilegeAccountReadWrite_insert_to_db
* @since_tizen 			2.3
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Retrieves account details with the account database ID
* @scenario				Retrieves accounts detail with the account database ID
* @apicovered			 account_delete_from_db_by_package_name 
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int CTc_AccountManager_PrivilegeAccountReadWrite_insert_to_db(void)
{
	START_TEST;
	int db_id = 11;
	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}
	int nRet =  account_insert_to_db(g_account, &db_id);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "account_insert_to_db", AccManagerGetErrorMSG(nRet));
	
	return 0;
}
//& purpose: Retrieves account details with the account database Package Name.
//& type: auto
/**
* @testcase 			CTc_AccountManager_PrivilegeAccountReadWrite_account_query_account_by_package_name
* @since_tizen 			2.3
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Retrieves account details with the account database ID
* @scenario				Retrieves accounts detail with the account database ID
* @apicovered			 account_query_account_by_package_name 
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int CTc_AccountManager_PrivilegeAccountReadWrite_account_query_account_by_package_name(void)
{
	START_TEST;
	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}
	
	int nRet = account_query_account_by_package_name(AccountCallback, g_pstrAppId, NULL);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "account_query_account_by_package_name", AccManagerGetErrorMSG(nRet));
	
	return 0;
}
//& purpose: Retrieves account details with the account database Package Name.
//& type: auto
/**
* @testcase 			CTc_AccountManager_PrivilegeAccountReadWrite_account_delete_from_db_by_package_name
* @since_tizen 			2.3
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Retrieves account details with the account database ID
* @scenario				Retrieves accounts detail with the account database ID
* @apicovered			 account_delete_from_db_by_package_name 
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			Creates a handle to the account
* @postcondition		Destroys the account handle and releases all its resources
*/
int CTc_AccountManager_PrivilegeAccountReadWrite_account_delete_from_db_by_package_name(void)
{
	START_TEST;
	if ( !AccountPreConditionHelper() )
	{
		return 1;
	}
	int nRet = account_delete_from_db_by_package_name(g_pstrAppId);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "account_delete_from_db_by_package_name", AccManagerGetErrorMSG(nRet));
	
	return 0;
}

//& purpose: Retrieves all account type information with the given application id.
//& type: auto
/**
* @testcase 			CTc_AccountManager_PrivilegeAccountReadWrite_account_type_query_by_app_id
* @since_tizen 			2.3
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Retrieves all account type information with the given application id
* @scenario				Create Account Type Handle and Set the application id\n
*						Insert Account Type  Handle with given application id into DB\n
*						Retrieves all account type information with the given application id\n
*						Deletes the account type from the account database by application id
* @apicovered			account_type_create
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			Creates a account type handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account type handle and releases all its resources
*/
int CTc_AccountManager_PrivilegeAccountReadWrite_account_type_query_by_app_id(void)
{
	START_TEST;
	account_type_h accountTypeHandle = NULL;

	int nRet = account_type_create(&accountTypeHandle);
	if ( accountTypeHandle == NULL )
	{
		FPRINTF("[Line : %d][%s] account_type_create API Call Failed as accountTypeHandle is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = account_type_query_by_app_id(g_pstrAppId, &accountTypeHandle);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "account_type_query_by_app_id", AccManagerGetErrorMSG(nRet),account_type_destroy(accountTypeHandle));
	
	account_type_destroy(accountTypeHandle);
	return 0;
}
//& purpose: Retrieves all account type information with the given application id.
//& type: auto
/**
* @testcase 			CTc_AccountManager_PrivilegeAccountReadWrite_query_label_by_app_id
* @since_tizen 			2.3
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Retrieves all account type information with the given application id
* @scenario				Create Account Type Handle and Set the application id\n
*						Insert Account Type  Handle with given application id into DB\n
*						Retrieves all account type information with the given application id\n
*						Deletes the account type from the account database by application id
* @apicovered			account_type_query_label_by_app_id
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			Creates a account type handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account type handle and releases all its resources
*/
int CTc_AccountManager_PrivilegeAccountReadWrite_query_label_by_app_id(void)
{
	START_TEST;
	account_type_h accountTypeHandle = NULL;

	int nRet = account_type_create(&accountTypeHandle);
	if ( accountTypeHandle == NULL )
	{
		FPRINTF("[Line : %d][%s] account_type_create API Call Failed as accountTypeHandle is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = account_type_query_label_by_app_id(AccountLabelCB, g_pstrAppId, NULL);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "account_type_query_label_by_app_id", AccManagerGetErrorMSG(nRet),account_type_destroy(accountTypeHandle));
	
	account_type_destroy(accountTypeHandle);
	
	return 0;
}
//& purpose: Retrieves all account type information with the given application id.
//& type: auto
/**
* @testcase 			CTc_AccountManager_PrivilegeAccountReadWrite_foreach_account_type_from_db
* @since_tizen 			2.3
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Retrieves all account type information with the given application id
* @scenario				Create Account Type Handle and Set the application id\n
*						Insert Account Type  Handle with given application id into DB\n
*						Retrieves all account type information with the given application id\n
*						Deletes the account type from the account database by application id
* @apicovered			account_type_create
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			Creates a account type handle and Connect to DB
* @postcondition		Disconnect DB, Destroys the account type handle and releases all its resources
*/
int CTc_AccountManager_PrivilegeAccountReadWrite_foreach_account_type_from_db(void)
{
	START_TEST;
	account_type_h accountTypeHandle = NULL;

	int nRet = account_type_create(&accountTypeHandle);
	if ( accountTypeHandle == NULL )
	{
		FPRINTF("[Line : %d][%s] account_type_create API Call Failed as accountTypeHandle is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = account_type_foreach_account_type_from_db(AccountTypeCallback, NULL);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "account_type_foreach_account_type_from_db", AccManagerGetErrorMSG(nRet),	account_type_destroy(accountTypeHandle);
	);

	account_type_destroy(accountTypeHandle);
	
	return 0;
}
