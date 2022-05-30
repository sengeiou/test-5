//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "assert.h"
#include <account.h>
#include <account-types.h>
#include <account-error.h>
#include <string.h>
#include <glib.h>
#include <dlog.h>
#include <app.h>
#include <tct_common.h>
#include <system_info.h>

#define TEST_PACKAGE_NAME		"core.accounts-svc-tests"	// app_id
#define USER_NAME			"user_name"
#define ICON_PATH			"/shared/res/account.png"
#define SMALL_ICON_PATH			"/shared/res/account_small.png"
#define LABEL_DEFAULT			"AccountTest"
#define LABEL_EN_GB			"English AccountTest"
#define SERVICE_PROVIDER_ID		"http://www.tizen.org/"
#define BUFFERSIZE			1024
#define RPM_INSTALL_LOCATION		"/usr/apps/core-accounts-svc-tests"
#define TPK_APP_PREFIX			"org.tizen."
#define API_NAMESPACE			"accounts-svc"

#define ACCOUNT_FEATURE			"http://tizen.org/feature/account"

#define check_fail(exp) \
	if (!(exp)) { \
		_is_fail = true; \
		return true; \
	}

#define check_fail_eq(var, ref) \
	if (var != ref) { \
		_is_fail = true; \
		return true; \
	}


#define is_callback_fail() \
	if (_is_fail == true) \
		return 1;

#define assert_eq_free(var, ref, var1) \
    do { \
        if (var != ref) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert fail; Values (%s == 0x%x) and (%s == 0x%x) are not equal\\n", \
                __FILE__, __LINE__, #var, (int)var, #ref, (int)ref); \
            account_destroy(var1); \
            return 1; \
        } \
    } while (0)


#define assert_eq_free_text(var, ref, var1, var2) \
    do { \
        if (var != ref) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert fail; Values (%s == 0x%x) and (%s == 0x%x) are not equal\\n", \
                __FILE__, __LINE__, #var, (int)var, #ref, (int)ref); \
            _account_free_text(var1); \
            account_destroy(var2); \
            return 1; \
        } \
    } while (0)


enum ICON_PATH_TYPE {
	ICON,
	SMALL_ICON
};

typedef enum {
	_PROFILE_UNKNOWN = 0,
	_PROFILE_MOBILE = 0x1,
	_PROFILE_WEARABLE = 0x2,
	_PROFILE_TV = 0x4,
	_PROFILE_IVI = 0x8,
	_PROFILE_COMMON = 0x10,
} tizen_profile_t;

/* Accessing system info */
int system_info_get_platform_string(const char *key, char **value);

//& set: AccountsSvc
static bool created = false;
static account_h account = NULL;
static int _is_fail = true;
static bool is_account_supported = false;
static const char* package_name = TEST_PACKAGE_NAME;
static const char* test_label_default = LABEL_DEFAULT;
static const char* test_label_en_gb = LABEL_EN_GB;
static const char* contact_capability = ACCOUNT_SUPPORTS_CAPABILITY_CONTACT;
static const char* calendar_capability = ACCOUNT_SUPPORTS_CAPABILITY_CALENDAR;
static const char* user_name = USER_NAME;
static const account_capability_state_e capability_state = ACCOUNT_CAPABILITY_ENABLED;
static const int test_multi_account_support = 1;

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


static gboolean timeout_cb(gpointer data) {
	printf("timeout!\n");
	_is_fail = true;
	g_main_loop_quit((GMainLoop*)data);
	return FALSE;
}

/**
* @function 		AppGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AppGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case APP_ERROR_NONE :					szErrorVal = "APP_ERROR_NONE";					break;
	case APP_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_ERROR_INVALID_PARAMETER";		break;
	case APP_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_ERROR_OUT_OF_MEMORY";			break;
	case APP_ERROR_INVALID_CONTEXT:			szErrorVal = "APP_ERROR_INVALID_CONTEXT";		break;
	case APP_ERROR_NO_SUCH_FILE:			szErrorVal = "APP_ERROR_NO_SUCH_FILE";			break;
	case APP_ERROR_ALREADY_RUNNING:			szErrorVal = "APP_ERROR_ALREADY_RUNNING";		break;
	default:								szErrorVal = "Undefined error";					break;
	}

	return szErrorVal;
}

/**
 * @function		utc_account_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_account_startup(void)
{
	/* start of TC */
	system_info_get_platform_bool(ACCOUNT_FEATURE, &is_account_supported);
	
	int ret1 = account_create(&account);
	if (ACCOUNT_ERROR_NONE == ret1) {
		created = true;
	}
}

/**
 * @function		utc_account_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_account_cleanup(void)
{
	int ret1 = ACCOUNT_ERROR_NONE;
	ret1 = account_destroy(account);
	if (ACCOUNT_ERROR_NONE == ret1) {
		created = false;
	}
}

static void _account_free_text(char *text)
{
	if (text != NULL) {
		free(text);
		text = NULL;
	}
}

char *_account_get_path(int type)
{
	char pszUser[BUFFERSIZE] = {0,};
	char pszValue[BUFFERSIZE] = {0,};
	char *pszACTUAL_FILE_PATH = NULL;
	int path_size = 0;

	//testing
	char* psz_pkg_id = NULL;
	int nRet = app_get_id(&psz_pkg_id);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "app_get_id", AppGetError(nRet));
	PRINT_UTC_LOG("[Line : %d][%s] app_get_id returned value = %s\\n", __LINE__, API_NAMESPACE, psz_pkg_id);
	if(0 == strncmp(TPK_APP_PREFIX,psz_pkg_id, strlen(TPK_APP_PREFIX)))
	{
		PRINT_UTC_LOG("[Line : %d][%s] Detected TPK execution\\n", __LINE__, API_NAMESPACE);
		if (true == GetValueForTCTSetting("DEVICE_EXECUTION_MODE_30", pszUser, API_NAMESPACE))
		{
			if (!strcmp(pszUser, "owner"))
			{
				if (true != GetValueForTCTSetting("DEVICE_ADMIN_USER_APPS_ROOT_30", pszValue, API_NAMESPACE))
				{
					FREE_MEMORY(psz_pkg_id);
					PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting(DEVICE_ADMIN_USER_APPS_ROOT_30) failed\\n", __LINE__, API_NAMESPACE);
					return NULL;
				}
			}
			else
			{
				if (true != GetValueForTCTSetting("DEVICE_OTHER_USER_APPS_ROOT_30", pszValue, API_NAMESPACE))
				{
					FREE_MEMORY(psz_pkg_id);
					PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting(DEVICE_OTHER_USER_APPS_ROOT_30) failed\\n", __LINE__, API_NAMESPACE);
					return NULL;
				}
			}

			/*if profile is TV then change the icon path*/
			if (get_tizen_profile() == _PROFILE_TV) {
				int str_len = strlen("/opt/usr/apps");
				memset(pszValue, 0, BUFFERSIZE);
				strncpy(pszValue, "/opt/usr/apps", str_len);
				pszValue[str_len+1] = '\0';
			}

			PRINT_UTC_LOG("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
			if (type == ICON)
			{
				path_size = strlen(pszValue) + strlen(psz_pkg_id) + strlen(ICON_PATH) + 2;
				pszACTUAL_FILE_PATH = (char*)calloc(path_size, sizeof(char));
				snprintf(pszACTUAL_FILE_PATH, path_size, "%s/%s%s", pszValue, psz_pkg_id, ICON_PATH);
			}
			else
			{
				path_size = strlen(pszValue) + strlen(psz_pkg_id) + strlen(SMALL_ICON_PATH) + 2;
				pszACTUAL_FILE_PATH = (char*)calloc(path_size, sizeof(char));
				snprintf(pszACTUAL_FILE_PATH, path_size, "%s/%s%s", pszValue, psz_pkg_id, SMALL_ICON_PATH);
			}
			FREE_MEMORY(psz_pkg_id);
		}
		else
		{
			FREE_MEMORY(psz_pkg_id);
			PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting(DEVICE_EXECUTION_MODE_30) failed\\n", __LINE__, API_NAMESPACE);
			return NULL;
		}
	}
	else
	{
		FREE_MEMORY(psz_pkg_id);
		PRINT_UTC_LOG("[Line : %d][%s] Detected RPM execution\\n", __LINE__, API_NAMESPACE);
		
		if (type == ICON)
		{	
			path_size = strlen(RPM_INSTALL_LOCATION) + strlen(ICON_PATH) + 1;
			pszACTUAL_FILE_PATH = (char*)calloc(path_size, sizeof(char));
			snprintf(pszACTUAL_FILE_PATH, path_size, "%s%s", RPM_INSTALL_LOCATION, ICON_PATH);
		}
		else
		{
			path_size = strlen(RPM_INSTALL_LOCATION) + strlen(SMALL_ICON_PATH) + 1;
			pszACTUAL_FILE_PATH = (char*)calloc(path_size, sizeof(char));
			snprintf(pszACTUAL_FILE_PATH, path_size, "%s%s", RPM_INSTALL_LOCATION, SMALL_ICON_PATH);
		}
	}
	PRINT_UTC_LOG("[Line : %d][%s] pszACTUAL_FILE_PATH = %s\\n", __LINE__, API_NAMESPACE, pszACTUAL_FILE_PATH);
	
	dlog_print(DLOG_ERROR, "ACCOUNT_TC", "pszACTUAL_FILE_PATH %s", pszACTUAL_FILE_PATH);
	return pszACTUAL_FILE_PATH;
}

//#ifdef MOBILE || TV
#if defined(MOBILE) || defined(TV)
/* This API has been deprecated since 2.4 */
/**
 * @testcase		utc_account_connect_p
 * @since_tizen		2.3
 * @description		Positive test case of account_connect()
 *					This API has been deprecated since 2.4
 */
int utc_account_connect_p(void)
{
	int ret = account_connect();
	assert_eq(ret, ACCOUNT_ERROR_NONE);

	return 0;
}

/* This API has been deprecated since 2.4 */
/**
 * @testcase		utc_account_connect_readonly_p
 * @since_tizen		2.3
 * @description		Positive test case of account_connect_readonly()\n
 *					This API has been deprecated since 2.4
 */
int utc_account_connect_readonly_p(void)
{
	int ret = account_connect_readonly();
	assert_eq(ret, ACCOUNT_ERROR_NONE);

	return 0;
}

/* This API has been deprecated since 2.4 */
/**
 * @testcase		utc_account_disconnect_p
 * @since_tizen		2.3
 * @description		Positive test case of account_disconnect()
 */
int utc_account_disconnect_p(void)
{
	int ret = account_disconnect();
	assert_eq(ret, ACCOUNT_ERROR_NONE);

	return 0;
}
#endif


/**
 * @testcase		utc_account_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of account_destroy()
 */
int utc_account_destroy_p(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	account_h account_data = NULL;

	ret = account_create(&account_data);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_destroy(account_data);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of account_destroy()
 */
int utc_account_destroy_n(void)
{
	assert(created);
	utc_account_cleanup();
	int ret = ACCOUNT_ERROR_NONE;

	ret = rename("/opt/usr/dbspace/.account.db", "/opt/usr/dbspace/.account-tmp.db");

	ret = rename("/opt/usr/dbspace/.account.db-journal", "/opt/usr/dbspace/.account-tmp.db-journal");

	ret = account_destroy(NULL);

	assert_neq(ret, ACCOUNT_ERROR_NONE);

	ret = rename("/opt/usr/dbspace/.account-tmp.db", "/opt/usr/dbspace/.account.db");
	ret = rename("/opt/usr/dbspace/.account-tmp.db-journal", "/opt/usr/dbspace/.account.db-journal");

	utc_account_startup();

	return 0;
}


/**
 * @testcase		utc_account_create_p
 * @since_tizen		2.3
 * @description		Positive test case of account_create()
 */
int utc_account_create_p(void)
{
	assert(created);

	return 0;
}

/**
 * @testcase		utc_account_create_n
 * @since_tizen		2.3
 * @description		Negative test case of account_create()
 */
int utc_account_create_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_create(NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_insert_to_db_p
 * @since_tizen		2.3
 * @description		Positive test case of account_insert_to_db()
 */
int utc_account_insert_to_db_p(void)
{
	assert(created);
	int account_id = -1;
	int ret = ACCOUNT_ERROR_NONE;
	char* ret_user_name = NULL;
	char* ret_package_name = NULL;
	const char* display_name = "display_name";
	char* ret_display_name = NULL;
	const char* icon_path = "icon_path";
	char* ret_icon_path = NULL;
	const char* domain_name = "domain_name";
	char* ret_domain_name = NULL;
	const char* email_address = "email_address";
	char* ret_email_address = NULL;
	const char* source = "source";
	char* ret_source = NULL;
	const char* key = "key";
	const char* value = "value";
	char* ret_value = NULL;
	const char* user_text = "user_text";
	char* ret_user_text = NULL;
	const char* access_token = "access_token";
	char* ret_access_token = NULL;
	const account_auth_type_e auth_type = ACCOUNT_AUTH_TYPE_OAUTH;
	account_auth_type_e ret_auth_type = 0;
	const account_capability_state_e capability_state = ACCOUNT_CAPABILITY_ENABLED;
	account_capability_state_e ret_capability_state = 0;
	const account_secrecy_state_e secrecy_state = ACCOUNT_SECRECY_VISIBLE;
	account_secrecy_state_e ret_secrecy_state = 0;
	const account_sync_state_e sync_state = ACCOUNT_SYNC_STATUS_OFF;
	account_sync_state_e ret_sync_state = 0;
	account_h ret_account = NULL;
	int i = -1;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_display_name(account, display_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_icon_path(account, icon_path);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_domain_name(account, domain_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_email_address(account, email_address);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_source(account, source);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_custom(account, key, value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, contact_capability, capability_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_access_token(account, access_token);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	for (i = 0; i < 5; i++){
		ret = account_set_user_text(account, i, user_text);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	for (i = 0; i < 5; i++){
		ret = account_set_user_int(account, i, i*10);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	ret = account_set_auth_type(account, auth_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_secret(account, secrecy_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_sync_support(account, sync_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_create(&ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_account_by_account_id(account_id, &ret_account);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		if(ret != ACCOUNT_ERROR_NONE) {
			account_destroy(ret_account);
		}
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}

	// User Name
	ret = account_get_user_name(ret_account, &ret_user_name);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		_account_free_text(ret_user_name);
	}
	else
	{
		assert_eq_free_text(ret, ACCOUNT_ERROR_NONE, ret_user_name, ret_account);
		assert_eq_free_text(strcmp(ret_user_name, user_name), 0, ret_user_name, ret_account);
		_account_free_text(ret_user_name);
	}

	// Package Name
	ret = account_get_package_name(ret_account, &ret_package_name);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		_account_free_text(ret_package_name);
	}
	else
	{
		assert_eq_free_text(ret, ACCOUNT_ERROR_NONE, ret_package_name, ret_account);
		assert_eq_free_text(strcmp(ret_package_name, package_name), 0, ret_package_name, ret_account);
		_account_free_text(ret_package_name);
	}

	// Display Name
	ret = account_get_display_name(ret_account, &ret_display_name);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		_account_free_text(ret_display_name);
	}
	else
	{
		assert_eq_free_text(ret, ACCOUNT_ERROR_NONE, ret_display_name, ret_account);
		assert_eq_free_text(strcmp(ret_display_name, display_name), 0, ret_display_name, ret_account);
		_account_free_text(ret_display_name);
	}

	// Icon Path
	ret = account_get_icon_path(ret_account, &ret_icon_path);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		_account_free_text(ret_icon_path);
	}
	else
	{
		assert_eq_free_text(ret, ACCOUNT_ERROR_NONE, ret_icon_path, ret_account);
		assert_eq_free_text(strcmp(ret_icon_path, icon_path), 0, ret_icon_path, ret_account);
		_account_free_text(ret_icon_path);
	}

	// Domain Name
	ret = account_get_domain_name(ret_account, &ret_domain_name);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		_account_free_text(ret_domain_name);
	}
	else
	{
		assert_eq_free_text(ret, ACCOUNT_ERROR_NONE, ret_domain_name, ret_account);
		assert_eq_free_text(strcmp(ret_domain_name, domain_name), 0, ret_domain_name, ret_account);
		_account_free_text(ret_domain_name);
	}

	// Email Address
	ret = account_get_email_address(ret_account, &ret_email_address);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		_account_free_text(ret_email_address);
	}
	else
	{
		assert_eq_free_text(ret, ACCOUNT_ERROR_NONE, ret_email_address, ret_account);
		assert_eq_free_text(strcmp(ret_email_address, email_address), 0, ret_email_address, ret_account);
		_account_free_text(ret_email_address);
	}

	// Source
	ret = account_get_source(ret_account, &ret_source);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		_account_free_text(ret_source);
	}
	else
	{
		assert_eq_free_text(ret, ACCOUNT_ERROR_NONE, ret_source, ret_account);
		assert_eq_free_text(strcmp(ret_source, source), 0, ret_source, ret_account);
		_account_free_text(ret_source);
	}

	// Custom
	ret = account_get_custom(ret_account, key, &ret_value);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		_account_free_text(ret_value);
	}
	else
	{
		assert_eq_free_text(ret, ACCOUNT_ERROR_NONE, ret_value, ret_account);
		assert_eq_free_text(strcmp(ret_value, value), 0, ret_value, ret_account);
		_account_free_text(ret_value);
	}

	// Capability
	ret = account_get_capability(ret_account, contact_capability, &ret_capability_state);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq_free(ret, ACCOUNT_ERROR_NONE, ret_account);
		assert_eq_free(ret_capability_state, capability_state, ret_account);
	}

	// Access Token
	ret = account_get_access_token(ret_account, &ret_access_token);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		_account_free_text(ret_access_token);
	}
	else
	{
		assert_eq_free_text(ret, ACCOUNT_ERROR_NONE, ret_access_token, ret_account);
		if (ret_access_token != NULL && access_token != NULL) {
			assert_eq_free_text(strcmp(ret_access_token, access_token), 0, ret_access_token, ret_account);
		}
		_account_free_text(ret_access_token);
	}

	// User Text
	for (i = 0; i < 5; i++){
		ret = account_get_user_text(ret_account, i, &ret_user_text);
		if(!is_account_supported)
		{
			assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
			_account_free_text(ret_user_text);
		}
		else
		{
			assert_eq_free_text(ret, ACCOUNT_ERROR_NONE, ret_user_text, ret_account);
			assert_eq_free_text(strcmp(ret_user_text, user_text), 0, ret_user_text, ret_account);
			_account_free_text(ret_user_text);
		}
	}

	// User Int
	for (i = 0; i < 5; i++){
		int ret_user_int = -1;
		ret = account_get_user_int(ret_account, i, &ret_user_int);
		if(!is_account_supported)
		{
			assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		}
		else
		{
			assert_eq_free(ret, ACCOUNT_ERROR_NONE, ret_account);
			assert_eq_free(ret_user_int, i*10, ret_account);
		}
	}

	// Auth Type
	ret = account_get_auth_type(ret_account, &ret_auth_type);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq_free(ret, ACCOUNT_ERROR_NONE, ret_account);
		assert_eq_free(ret_auth_type, auth_type, ret_account);
	}

	// Secret
	ret = account_get_secret(ret_account, &ret_secrecy_state);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq_free(ret, ACCOUNT_ERROR_NONE, ret_account);
		assert_eq_free(ret_secrecy_state, secrecy_state, ret_account);
	}

	// Sync Support
	ret = account_get_sync_support(ret_account, &ret_sync_state);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq_free(ret, ACCOUNT_ERROR_NONE, ret_account);
		assert_eq_free(ret_sync_state, sync_state, ret_account);
	}

	ret = account_destroy(ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_insert_to_db_n
 * @since_tizen		2.3
 * @description		Negative test case of account_insert_to_db()
 */
int utc_account_insert_to_db_n(void)
{
	assert(created);
	int account_id = -1;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_insert_to_db(NULL, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_insert_to_db(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_display_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_display_name()
 */
int utc_account_set_display_name_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* display_name = "display_name";

	ret = account_set_display_name(account, display_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_set_display_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_display_name()
 */
int utc_account_set_display_name_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* display_name = "display_name";

	ret = account_set_display_name(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_display_name(NULL, display_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_user_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_user_name()
 */
int utc_account_set_user_name_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_set_user_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_user_name()
 */
int utc_account_set_user_name_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_user_name(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_user_name(NULL, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_icon_path_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_icon_path()
 */
int utc_account_set_icon_path_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* icon_path = "icon_path";

	ret = account_set_icon_path(account, icon_path);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_set_icon_path_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_icon_path()
 */
int utc_account_set_icon_path_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* icon_path = "icon_path";

	ret = account_set_icon_path(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_icon_path(NULL, icon_path);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_domain_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_domain_name()
 */
int utc_account_set_domain_name_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* domain_name = "domain_name";

	ret = account_set_domain_name(account, domain_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_set_domain_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_domain_name()
 */
int utc_account_set_domain_name_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* domain_name = "domain_name";

	ret = account_set_domain_name(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_domain_name(NULL, domain_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_email_address_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_email_address()
 */
int utc_account_set_email_address_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* email_address = "email_address";

	ret = account_set_email_address(account, email_address);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_set_email_address_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_email_address()
 */
int utc_account_set_email_address_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* email_address = "email_address";

	ret = account_set_email_address(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_email_address(NULL, email_address);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_source_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_source()
 */
int utc_account_set_source_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* source = "source";

	ret = account_set_source(account, source);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_set_source_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_source()
 */
int utc_account_set_source_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* source = "source";

	ret = account_set_source(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_source(NULL, source);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_custom_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_custom()
 */
int utc_account_set_custom_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* key = "key";
	const char* value = "value";

	ret = account_set_custom(account, key, value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_custom(account, key, value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_set_custom_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_custom()
 */
int utc_account_set_custom_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* key = "key";
	const char* value = "value";

	ret = account_set_custom(account, NULL, value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_custom(account, key, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_custom(NULL, key, value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_custom_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_custom()
 */
int utc_account_get_custom_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* key = "key";
	const char* value = "value";
	char* ret_value = NULL;

	ret = account_set_custom(account, key, value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_custom(account, key, &ret_value);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		_account_free_text(ret_value);
	}
	else{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_value, value), 0);
		_account_free_text(ret_value);
	}

	return 0;
}

/**
 * @testcase		utc_account_get_custom_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_custom()
 */
int utc_account_get_custom_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	char *not_set_key = "not_set_key";
	char *returned_val = NULL;

	ret = account_get_custom(account, not_set_key, &returned_val);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_RECORD_NOT_FOUND);}

	ret = account_get_custom(account, NULL, &returned_val);
	free(returned_val);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

static bool account_custom_cb_func (char* key, char* value, void *user_data) {
	const char* original_value = (const char*)user_data;
//	if(strcmp(value, original_value) == 0) {
//		_is_fail = false;
//	}

	if(strcmp(value, original_value) != 0) {
		_is_fail = true;
	}

	return true;
}

/**
 * @testcase		utc_account_get_custom_all_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_custom_all()
 */
int utc_account_get_custom_all_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* key = "key";
	const char* key2 = "key2";
	const char* value = "value";

	ret = account_set_custom(account, key, value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_custom(account, key2, value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	_is_fail = false;
	ret = account_get_custom_all(account, account_custom_cb_func, value);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}
	_is_fail = true;

	return 0;
}

/**
 * @testcase		utc_account_get_custom_all_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_custom_all()
 */
int utc_account_get_custom_all_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_custom_all(account, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_custom_all(NULL, account_custom_cb_func, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_package_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_package_name()
 */
int utc_account_set_package_name_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_set_package_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_package_name()
 */
int utc_account_set_package_name_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_package_name(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_package_name(NULL, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_access_token_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_access_token()
 */
int utc_account_set_access_token_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* access_token = "access_token";

	ret = account_set_access_token(account, access_token);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_set_access_token_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_access_token()
 */
int utc_account_set_access_token_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_access_token(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_auth_type_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_auth_type()
 */
int utc_account_set_auth_type_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_auth_type(account, ACCOUNT_AUTH_TYPE_OAUTH);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_set_auth_type_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_auth_type()
 */
int utc_account_set_auth_type_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_auth_type(account, -999);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_auth_type(NULL, ACCOUNT_AUTH_TYPE_OAUTH);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_secret_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_secret()
 */
int utc_account_set_secret_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_secret(account, ACCOUNT_SECRECY_INVISIBLE);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_set_secret_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_secret()
 */
int utc_account_set_secret_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_secret(account, -999);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_secret(NULL, ACCOUNT_SECRECY_INVISIBLE);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_sync_support_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_sync_support()
 */
int utc_account_set_sync_support_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_sync_support(account, ACCOUNT_SYNC_STATUS_IDLE);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_set_sync_support_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_sync_support()
 */
int utc_account_set_sync_support_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_sync_support(account, -999);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_sync_support(NULL, ACCOUNT_SYNC_STATUS_IDLE);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_user_text_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_user_text()
 */
int utc_account_set_user_text_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* user_text = "user_text";

	int i;
	for ( i = 0; i < 5; i++){
		ret = account_set_user_text(account, i, user_text);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	return 0;
}

/**
 * @testcase		utc_account_set_user_text_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_user_text()
 */
int utc_account_set_user_text_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const char* user_text = "user_text";

	int i;
	for (i = 0; i < 5; i++){
		ret = account_set_user_text(account, i, NULL);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}
	}
	ret = account_set_user_text(account, 100, user_text);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_user_text(account, -1, user_text);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_user_text(NULL, 1, user_text);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_user_int_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_user_int()
 */
int utc_account_set_user_int_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	int i;
	for (i = 0; i < 5; i++){
		ret = account_set_user_int(account, i, 999);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	return 0;
}

/**
 * @testcase		utc_account_set_user_int_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_user_int()
 */
int utc_account_set_user_int_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	int i;
	for (i = 0; i < 5; i++){
		ret = account_set_user_int(NULL, i, 999);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}
	}

	ret = account_set_user_int(account, 100, 999);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_user_int(account, -1, 999);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_set_capability_p
 * @since_tizen		2.3
 * @description		Positive test case of account_set_capability()
 */
int utc_account_set_capability_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_capability(account, contact_capability, ACCOUNT_CAPABILITY_ENABLED);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, contact_capability, ACCOUNT_CAPABILITY_ENABLED);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}


/**
 * @testcase		utc_account_set_capability_n
 * @since_tizen		2.3
 * @description		Negative test case of account_set_capability()
 */
int utc_account_set_capability_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_capability(NULL, contact_capability, ACCOUNT_CAPABILITY_ENABLED);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_capability(account, NULL, ACCOUNT_CAPABILITY_ENABLED);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_set_capability(account, contact_capability, -1);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

static bool capability_cb_func (const char* capability_type, account_capability_state_e capability_state, void *user_data) {
	account_capability_state_e* _capability_state = (account_capability_state_e*)user_data;

	if(capability_state != *_capability_state)
		_is_fail = true;

	return true;
}

/**
 * @testcase		utc_account_get_capability_all_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_capability_all()
 */
int utc_account_get_capability_all_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	const account_capability_state_e capability_state = ACCOUNT_CAPABILITY_ENABLED;

	ret = account_set_capability(account, contact_capability, capability_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, calendar_capability, capability_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	_is_fail = false;

	ret = account_get_capability_all(account, capability_cb_func, &capability_state);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}
	
	_is_fail = true;

	return 0;
}

/**
 * @testcase		utc_account_get_capability_all_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_capability_all()
 */
int utc_account_get_capability_all_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_capability_all(NULL, capability_cb_func, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_capability_all(account, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_display_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_display_name()
 */
int utc_account_get_display_name_p(void)
{
	assert(created);
	const char* display_name = "display_name";
	char * ret_display_name = NULL;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_display_name(account, display_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_display_name(account, &ret_display_name);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_display_name, display_name), 0);
	}
	_account_free_text(ret_display_name);

	return 0;
}

/**
 * @testcase		utc_account_get_display_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_display_name()
 */
int utc_account_get_display_name_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	char * display_name;

	ret = account_get_display_name(NULL, &display_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_display_name(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_account_id_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_account_id()
 */
int utc_account_get_account_id_p(void)
{
	assert(created);
	int account_id = -1;
	int ret_account_id = -2;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_account_by_account_id(account_id, &account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_account_id(account, &ret_account_id);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(account_id, ret_account_id);
	}

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_get_account_id_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_account_id()
 */
int utc_account_get_account_id_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	int account_id = -1;

	ret = account_get_account_id(NULL, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_account_id(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_user_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_user_name()
 */
int utc_account_get_user_name_p(void)
{
	assert(created);
	char *ret_user_name;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_user_name(account, &ret_user_name);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_user_name, user_name), 0);
	}
	_account_free_text(ret_user_name);

	return 0;
}

/**
 * @testcase		utc_account_get_user_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_user_name()
 */
int utc_account_get_user_name_n(void)
{
	assert(created);
	char *get_user_name;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_user_name(NULL, &get_user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_user_name(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_icon_path_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_icon_path()
 */
int utc_account_get_icon_path_p(void)
{
	assert(created);
	char *ret_icon_path = NULL;
	const char* icon_path = "icon_path";
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_icon_path(account, icon_path);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_icon_path(account, &ret_icon_path);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_icon_path, icon_path), 0);
	}
	_account_free_text(ret_icon_path);

	return 0;
}

/**
 * @testcase		utc_account_get_icon_path_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_icon_path()
 */
int utc_account_get_icon_path_n(void)
{
	assert(created);
	char *ret_icon_path;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_icon_path(NULL, &ret_icon_path);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_icon_path(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_domain_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_domain_name()
 */
int utc_account_get_domain_name_p(void)
{
	assert(created);
	char *ret_domain_name;
	const char* domain_name = "domain_name";
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_domain_name(account, domain_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_domain_name(account, &ret_domain_name);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_domain_name, domain_name), 0);
	}
	_account_free_text(ret_domain_name);

	return 0;
}

/**
 * @testcase		utc_account_get_domain_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_domain_name()
 */
int utc_account_get_domain_name_n(void)
{
	assert(created);
	char *domain_name;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_domain_name(NULL, &domain_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_domain_name(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_email_address_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_email_address()
 */
int utc_account_get_email_address_p(void)
{
	assert(created);
	char *ret_email_address;
	const char* email_address = "email_address";
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_email_address(account, email_address);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_email_address(account, &ret_email_address);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_email_address, email_address), 0);
	}
	_account_free_text(ret_email_address);

	return 0;
}

/**
 * @testcase		utc_account_get_email_address_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_email_address()
 */
int utc_account_get_email_address_n(void)
{
	assert(created);
	char *ret_email_address;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_email_address(NULL, &ret_email_address);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_email_address(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_source_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_source()
 */
int utc_account_get_source_p(void)
{
	assert(created);
	char *ret_source = NULL;
	const char* source = "source";
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_source(account, source);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_source(account, &ret_source);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_source, source), 0);
	}
	_account_free_text(ret_source);

	return 0;
}

/**
 * @testcase		utc_account_get_source_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_source()
 */
int utc_account_get_source_n(void)
{
	assert(created);
	char *ret_source = NULL;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_source(NULL, &ret_source);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_source(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_package_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_package_name()
 */
int utc_account_get_package_name_p(void)
{
	assert(created);
	char *ret_package_name = NULL;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_package_name(account, &ret_package_name);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_package_name, package_name), 0);
	}
	_account_free_text(ret_package_name);

	return 0;
}

/**
 * @testcase		utc_account_get_package_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_package_name()
 */
int utc_account_get_package_name_n(void)
{
	assert(created);
	char *ret_package_name = NULL;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_package_name(NULL, &ret_package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_package_name(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_access_token_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_access_token()
 */
int utc_account_get_access_token_p(void)
{
	assert(created);
	char *ret_access_token = NULL;
	const char* access_token = "access_token";
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_access_token(account, access_token);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_access_token(account, &ret_access_token);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(access_token, ret_access_token), 0);
	}
	_account_free_text(ret_access_token);

	return 0;
}

/**
 * @testcase		utc_account_get_access_token_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_access_token()
 */
int utc_account_get_access_token_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	char *ret_access_token = NULL;

	ret = account_get_access_token(NULL, &ret_access_token);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_access_token(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_auth_type_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_auth_type()
 */
int utc_account_get_auth_type_p(void)
{
	assert(created);
	account_auth_type_e auth_type;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_auth_type(account, ACCOUNT_AUTH_TYPE_XAUTH);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_auth_type(account, &auth_type);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(auth_type, ACCOUNT_AUTH_TYPE_XAUTH);
	}

	return 0;
}

/**
 * @testcase		utc_account_get_auth_type_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_auth_type()
 */
int utc_account_get_auth_type_n(void)
{
	assert(created);
	account_auth_type_e auth_type;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_auth_type(NULL, &auth_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_auth_type(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_secret_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_secret()
 */
int utc_account_get_secret_p(void)
{
	assert(created);
	account_secrecy_state_e secret;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_secret(account, ACCOUNT_SECRECY_INVISIBLE);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_secret(account, &secret);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(secret, ACCOUNT_SECRECY_INVISIBLE);
	}

	return 0;
}

/**
 * @testcase		utc_account_get_sync_support_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_sync_support()
 */
int utc_account_get_sync_support_p(void)
{
	assert(created);
	account_sync_state_e sync_support;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_sync_support(account, ACCOUNT_SYNC_STATUS_IDLE);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_sync_support(account, &sync_support);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(sync_support, ACCOUNT_SYNC_STATUS_IDLE);
	}

	return 0;
}

/**
 * @testcase		utc_account_get_secret_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_secret()
 */
int utc_account_get_secret_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	account_secrecy_state_e secret;

	ret = account_get_secret(NULL, &secret);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_secret(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_sync_support_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_sync_support()
 */
int utc_account_get_sync_support_n(void)
{
	assert(created);
	account_sync_state_e sync_support;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_sync_support(NULL, &sync_support);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_sync_support(account, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_user_text_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_user_text()
 */
int utc_account_get_user_text_p(void)
{
	assert(created);
	char *ret_user_text = NULL;
	const char* user_text = "user_text";
	int ret = ACCOUNT_ERROR_NONE;

	int i;
	for ( i = 0; i < 5; i++){
		ret = account_set_user_text(account, i, user_text);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}
	for ( i = 0; i < 5; i++){
		ret = account_get_user_text(account, i, &ret_user_text);
		if(!is_account_supported)
		{
			assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		}
		else
		{
			assert_eq(ret, ACCOUNT_ERROR_NONE);
			assert_eq(strcmp(ret_user_text, user_text), 0);
		}
		_account_free_text(ret_user_text);
	}

	return 0;
}

/**
 * @testcase		utc_account_get_user_text_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_user_text()
 */
int utc_account_get_user_text_n(void)
{
	assert(created);
	char *ret_user_text = NULL;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_user_text(NULL, 0, &ret_user_text);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_user_text(account, 100, &ret_user_text);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_user_text(account, -1, &ret_user_text);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_user_text(account, 0, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_user_int_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_user_int()
 */
int utc_account_get_user_int_p(void)
{
	assert(created);
	int user_int;
	int ret = ACCOUNT_ERROR_NONE;

	int i;
	for (i = 0; i < 5; i++){
		ret = account_set_user_int(account, i, i*10);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	for (i = 0; i < 5; i++){
		ret = account_get_user_int(account, i, &user_int);
		if(!is_account_supported)
		{
			assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
		}
		else
		{
			assert_eq(ret, ACCOUNT_ERROR_NONE);
			assert_eq(user_int, i*10);
		}
	}

	return 0;
}

/**
 * @testcase		utc_account_get_user_int_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_user_int()
 */
int utc_account_get_user_int_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_user_int(NULL, 0, 100);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_user_int(account, 100, 100);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_user_int(account, -1, 100);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_user_int(account, 0, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

static bool capability_call_back_return_false(const char* capability_type, account_capability_state_e capability_state, void *user_data)
{
	return false;
}
static bool capability_call_back(const char* capability_type, account_capability_state_e capability_state, void *user_data)
{
	char* str = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	check_fail(user_data!=NULL);
	check_fail(capability_type!=NULL);
	account_capability_state_e _capability_state = ACCOUNT_CAPABILITY_ENABLED;
	account_h account_data = *((account_h*)user_data);
	const char* capability = contact_capability;

	ret = account_get_package_name(account_data, &str);
	if(is_account_supported)
	{
		if(ret != ACCOUNT_ERROR_NONE) {
			_account_free_text(str);
			_is_fail = true;
			return true;
		}
		if(strcmp(str, package_name) !=0) {
			_account_free_text(str);
			_is_fail = true;
			return true;
		}
	}

	ret = account_get_user_name(account_data, &str);
	if(is_account_supported)
	{
		if(ret != ACCOUNT_ERROR_NONE) {
			_account_free_text(str);
			_is_fail = true;
			return true;
		}
		if(strcmp(str, user_name) !=0) {
			_account_free_text(str);
			_is_fail = true;
			return true;
		}
	}

	if( strcmp(capability_type, capability)==0 ) {
		ret = account_get_capability(account_data, capability, &_capability_state);
		if(is_account_supported) {
			if(ret != ACCOUNT_ERROR_NONE) {
				_account_free_text(str);
				_is_fail = true;
				return true;
			}
			if(_capability_state != capability_state) {
				_account_free_text(str);
				_is_fail = true;
				return true;
			}
		}
	}

	_account_free_text(str);
	_is_fail = false;

	return 0;
}

/**
 * @testcase		utc_account_get_capability_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_capability()
 */
int utc_account_get_capability_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	account_capability_state_e value;

	ret = account_set_capability(account, contact_capability, ACCOUNT_CAPABILITY_ENABLED);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_capability(account, contact_capability, &value);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(value, ACCOUNT_CAPABILITY_ENABLED);
	}

	return 0;
}

/**
 * @testcase		utc_account_get_capability_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_capability()
 */
int utc_account_get_capability_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	account_capability_state_e value;

	ret = account_get_capability(NULL, contact_capability, &value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_capability(account, NULL, &value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_get_capability(account, contact_capability, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

static bool account_call_back_return_false(account_h account, void *user_data)
{
	return false;
}
static bool account_call_back(account_h account, void *user_data)
{
	const char* key = "key";
	char* str = NULL;
	char* comparison_str = NULL;
	int value = -1;
	int comparison_value = -1;
	int ret = ACCOUNT_ERROR_NONE;
	int i = -1;
	check_fail(user_data!=NULL);
	account_h _account = *((account_h*)user_data);

	ret = account_get_package_name(_account, &str);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_package_name(account, &comparison_str);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(str, comparison_str)==0);
	}
	_account_free_text(str);
	_account_free_text(comparison_str);

	ret = account_get_user_name(_account, &str);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_user_name(account, &comparison_str);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(str, comparison_str)==0);
	}
	_account_free_text(str);
	_account_free_text(comparison_str);

	ret = account_get_display_name(_account, &str);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_display_name(account, &comparison_str);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(str, comparison_str)==0);
	}
	_account_free_text(str);
	_account_free_text(comparison_str);

	ret = account_get_icon_path(_account, &str);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_icon_path(account, &comparison_str);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(str, comparison_str)==0);
	}
	_account_free_text(str);
	_account_free_text(comparison_str);

	ret = account_get_domain_name(_account, &str);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_domain_name(account, &comparison_str);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(str, comparison_str)==0);
	}
	_account_free_text(str);
	_account_free_text(comparison_str);

	ret = account_get_email_address(_account, &str);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_email_address(account, &comparison_str);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(str, comparison_str)==0);
	}
	_account_free_text(str);
	_account_free_text(comparison_str);

	ret = account_get_email_address(_account, &str);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_email_address(account, &comparison_str);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(str, comparison_str)==0);
	}
	_account_free_text(str);
	_account_free_text(comparison_str);

	ret = account_get_source(_account, &str);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_source(account, &comparison_str);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(str, comparison_str)==0);
	}
	_account_free_text(str);
	_account_free_text(comparison_str);

	ret = account_get_custom(_account, key, &str);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_custom(account, key, &comparison_str);
	if(is_account_supported) {
		check_fail_eq(ret, ACCOUNT_ERROR_NONE);
		check_fail(strcmp(str, comparison_str)==0);
	}
	_account_free_text(str);
	_account_free_text(comparison_str);

	ret = account_get_capability(_account, contact_capability, &value);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_capability(account, contact_capability, &comparison_value);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(value == comparison_value);
	}

	ret = account_get_access_token(_account, &str);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_access_token(account, &comparison_str);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		if (str != NULL && comparison_str != NULL)
			check_fail(strcmp(str, comparison_str)==0);
	}
	_account_free_text(str);
	_account_free_text(comparison_str);

	for (i = 0; i < 5; i++){
		ret = account_get_user_text(_account, i, &str);
		if(is_account_supported)
			check_fail(ret == ACCOUNT_ERROR_NONE);

		ret = account_get_user_text(account, i, &comparison_str);
		if(is_account_supported) {
			check_fail(ret == ACCOUNT_ERROR_NONE);
			check_fail(strcmp(str, comparison_str)==0);
		}
		_account_free_text(str);
		_account_free_text(comparison_str);
	}

	for (i = 0; i < 5; i++){
		ret = account_get_user_int(_account, i, &value);
		if(is_account_supported)
			check_fail(ret == ACCOUNT_ERROR_NONE);

		ret = account_get_user_int(account, i, &comparison_value);
		if(is_account_supported) {
			check_fail(ret == ACCOUNT_ERROR_NONE);
			check_fail(value == comparison_value);
		}
	}

	ret = account_get_auth_type(_account, &value);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_auth_type(account, &comparison_value);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(value == comparison_value);
	}

	ret = account_get_secret(_account, &value);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_secret(account, &comparison_value);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(value == comparison_value);
	}

	ret = account_get_sync_support(_account, &value);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_sync_support(account, &comparison_value);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(value == comparison_value);
	}

	_is_fail = false;

	return true;
}

/**
 * @testcase		utc_account_foreach_account_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of account_foreach_account_from_db()
 */
int utc_account_foreach_account_from_db_p(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	int account_id = -1;
	char* ret_user_name = NULL;
	const char* display_name = "display_name";
	const char* icon_path = "icon_path";
	const char* domain_name = "domain_name";
	const char* email_address = "email_address";
	const char* source = "source";
	const char* key = "key";
	const char* value = "value";
	const char* user_text = "user_text";
	const char* access_token = "access_token";
	const account_auth_type_e auth_type = ACCOUNT_AUTH_TYPE_OAUTH;
	const account_capability_state_e capability_state = ACCOUNT_CAPABILITY_ENABLED;
	const account_secrecy_state_e secrecy_state = ACCOUNT_SECRECY_VISIBLE;
	const account_sync_state_e sync_state = ACCOUNT_SYNC_STATUS_OFF;
	int i = -1;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_display_name(account, display_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_icon_path(account, icon_path);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_domain_name(account, domain_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_email_address(account, email_address);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_source(account, source);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_custom(account, key, value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, contact_capability, capability_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_access_token(account, access_token);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	for (i = 0; i < 5; i++){
		ret = account_set_user_text(account, i, user_text);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	for (i = 0; i < 5; i++){
		ret = account_set_user_int(account, i, i*10);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	ret = account_set_auth_type(account, auth_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_secret(account, secrecy_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_sync_support(account, sync_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_foreach_account_from_db(account_call_back, &account);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}

	ret = account_foreach_account_from_db(account_call_back_return_false, &account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	_is_fail = true;

	return 0;
}

/**
 * @testcase		utc_account_foreach_account_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of account_foreach_account_from_db()
 */
int utc_account_foreach_account_from_db_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_foreach_account_from_db(NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_query_account_by_account_id_p
 * @since_tizen		2.3
 * @description		Positive test case of account_query_account_by_account_id()
 */
int utc_account_query_account_by_account_id_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	int account_id = -1;
	account_h ret_account = NULL;
	char* ret_user_name = NULL;
	char* ret_package_name = NULL;
	account_capability_state_e ret_capability_type = 0;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, contact_capability, ACCOUNT_CAPABILITY_ENABLED);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_create(&ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_account_by_account_id(account_id, &ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_user_name(ret_account, &ret_user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_package_name(ret_account, &ret_package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_capability(ret_account, contact_capability, &ret_capability_type);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_user_name, user_name), 0);
		assert_eq(strcmp(ret_package_name, package_name), 0);
		assert_eq(ret_capability_type, ACCOUNT_CAPABILITY_ENABLED);
	}
	_account_free_text(ret_user_name);
	_account_free_text(ret_package_name);

	ret = account_destroy(ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_query_account_by_account_id_n
 * @since_tizen		2.3
 * @description		Negative test case of account_query_account_by_account_id()
 */
int utc_account_query_account_by_account_id_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_query_account_by_account_id(100, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_query_account_by_account_id(-999, &account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_query_deleted_account_info_by_account_id_p
 * @since_tizen		5.5
 * @description		Positive test case of account_query_deleted_account_info_by_account_id()
 */
int utc_account_query_deleted_account_info_by_account_id_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	int account_id = -1;
	account_h ret_account = NULL;
	account_h del_account = NULL;
	char* ret_user_name = NULL;
	char* del_user_name = NULL;
	char* ret_package_name = NULL;
	char* del_package_name = NULL;

	account_capability_state_e ret_capability_type = 0;
	account_capability_state_e del_capability_type = 0;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, contact_capability, ACCOUNT_CAPABILITY_ENABLED);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	/* insert account */
	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	/* get inserted account handle */
	ret = account_create(&ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_account_by_account_id(account_id, &ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	/* delete account */
	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	/* get deleted account handle */
	ret = account_create(&del_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_deleted_account_info_by_account_id(account_id, &del_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	/* get user-names of both inserted & deleted account handles */
	ret = account_get_user_name(ret_account, &ret_user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_user_name(del_account, &del_user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	/* get package-names of both inserted & deleted account handles */
	ret = account_get_package_name(ret_account, &ret_package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_package_name(del_account, &del_package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	/* get capabilities */
	ret = account_get_capability(ret_account, contact_capability, &ret_capability_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_capability(del_account, contact_capability, &del_capability_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	/* compare inserted info with original info */
	assert_eq(strcmp(ret_user_name, user_name), 0);
	assert_eq(strcmp(ret_package_name, package_name), 0);
	assert_eq(ret_capability_type, ACCOUNT_CAPABILITY_ENABLED);

	/* compare deleted info with inserted info */
	assert_eq(strcmp(ret_user_name, del_user_name), 0);
	assert_eq(strcmp(ret_package_name, del_package_name), 0);
	assert_eq(del_capability_type, ACCOUNT_CAPABILITY_ENABLED);

	_account_free_text(ret_user_name);
	_account_free_text(ret_package_name);

	_account_free_text(del_user_name);
	_account_free_text(del_package_name);

	ret = account_destroy(ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_destroy(del_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_query_deleted_account_info_by_account_id_n
 * @since_tizen		5.5
 * @description		Negative test case of account_query_deleted_account_info_by_account_id()
 */
int utc_account_query_deleted_account_info_by_account_id_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	int account_id = -1;
	account_h ret_account = NULL;

	ret = account_query_deleted_account_info_by_account_id(10000, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_query_deleted_account_info_by_account_id(-9999, &account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_query_account_by_user_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_query_account_by_user_name()
 */
int utc_account_query_account_by_user_name_p(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	int account_id = -1;
	char* ret_user_name = NULL;
	const char* display_name = "display_name";
	const char* icon_path = "icon_path";
	const char* domain_name = "domain_name";
	const char* email_address = "email_address";
	const char* source = "source";
	const char* key = "key";
	const char* value = "value";
	const char* user_text = "user_text";
	const char* access_token = "access_token";
	const account_auth_type_e auth_type = ACCOUNT_AUTH_TYPE_OAUTH;
	const account_capability_state_e capability_state = ACCOUNT_CAPABILITY_ENABLED;
	const account_secrecy_state_e secrecy_state = ACCOUNT_SECRECY_VISIBLE;
	const account_sync_state_e sync_state = ACCOUNT_SYNC_STATUS_OFF;
	int i = -1;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_display_name(account, display_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_icon_path(account, icon_path);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_domain_name(account, domain_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_email_address(account, email_address);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_source(account, source);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_custom(account, key, value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, contact_capability, capability_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_access_token(account, access_token);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	for (i = 0; i < 5; i++){
		ret = account_set_user_text(account, i, user_text);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	for (i = 0; i < 5; i++){
		ret = account_set_user_int(account, i, i*10);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	ret = account_set_auth_type(account, auth_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_secret(account, secrecy_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_sync_support(account, sync_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}


	ret = account_query_account_by_user_name(account_call_back, user_name, &account);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}

	ret = account_query_account_by_user_name(account_call_back_return_false, user_name, &account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	_is_fail = true;

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_query_account_by_user_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_query_account_by_user_name()
 */
int utc_account_query_account_by_user_name_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_query_account_by_user_name(account_call_back, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_query_account_by_user_name(NULL, user_name, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_query_account_by_package_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_query_account_by_package_name()
 */
int utc_account_query_account_by_package_name_p(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	int account_id = -1;
	char* ret_user_name = NULL;
	const char* display_name = "display_name";
	const char* icon_path = "icon_path";
	const char* domain_name = "domain_name";
	const char* email_address = "email_address";
	const char* source = "source";
	const char* key = "key";
	const char* value = "value";
	const char* user_text = "user_text";
	const char* access_token = "access_token";
	const account_auth_type_e auth_type = ACCOUNT_AUTH_TYPE_OAUTH;
	const account_capability_state_e capability_state = ACCOUNT_CAPABILITY_ENABLED;
	const account_secrecy_state_e secrecy_state = ACCOUNT_SECRECY_VISIBLE;
	const account_sync_state_e sync_state = ACCOUNT_SYNC_STATUS_OFF;
	int i = -1;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_display_name(account, display_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_icon_path(account, icon_path);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_domain_name(account, domain_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_email_address(account, email_address);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_source(account, source);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_custom(account, key, value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, contact_capability, capability_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_access_token(account, access_token);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	for (i = 0; i < 5; i++){
		ret = account_set_user_text(account, i, user_text);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	for (i = 0; i < 5; i++){
		ret = account_set_user_int(account, i, i*10);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	ret = account_set_auth_type(account, auth_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_secret(account, secrecy_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_sync_support(account, sync_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_account_by_package_name(account_call_back, package_name, &account);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}

	ret = account_query_account_by_package_name(account_call_back_return_false, package_name, &account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	_is_fail = true;

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_query_account_by_package_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_query_account_by_package_name()
 */
int utc_account_query_account_by_package_name_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_query_account_by_package_name(account_call_back, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_query_account_by_package_name(NULL, package_name, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_query_account_by_capability_p
 * @since_tizen		2.3
 * @description		Positive test case of account_query_account_by_capability()
 */
int utc_account_query_account_by_capability_p(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	int account_id = -1;
	char* ret_user_name = NULL;
	const char* display_name = "display_name";
	const char* icon_path = "icon_path";
	const char* domain_name = "domain_name";
	const char* email_address = "email_address";
	const char* source = "source";
	const char* key = "key";
	const char* value = "value";
	const char* user_text = "user_text";
	const char* access_token = "access_token";
	const account_auth_type_e auth_type = ACCOUNT_AUTH_TYPE_OAUTH;
	const account_capability_state_e capability_state = ACCOUNT_CAPABILITY_ENABLED;
	const account_secrecy_state_e secrecy_state = ACCOUNT_SECRECY_VISIBLE;
	const account_sync_state_e sync_state = ACCOUNT_SYNC_STATUS_OFF;
	int i = -1;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_display_name(account, display_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_icon_path(account, icon_path);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_domain_name(account, domain_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_email_address(account, email_address);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_source(account, source);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_custom(account, key, value);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, contact_capability, capability_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_access_token(account, access_token);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	for (i = 0; i < 5; i++){
		ret = account_set_user_text(account, i, user_text);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	for (i = 0; i < 5; i++){
		ret = account_set_user_int(account, i, i*10);
		if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
		else{assert_eq(ret, ACCOUNT_ERROR_NONE);}
	}

	ret = account_set_auth_type(account, auth_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_secret(account, secrecy_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_sync_support(account, sync_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_account_by_capability(account_call_back, contact_capability, capability_state, &account);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}

	ret = account_query_account_by_capability(account_call_back_return_false, contact_capability, capability_state, &account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	_is_fail = true;

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_query_account_by_capability_n
 * @since_tizen		2.3
 * @description		Negative test case of account_query_account_by_capability()
 */
int utc_account_query_account_by_capability_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_query_account_by_capability(NULL, contact_capability, ACCOUNT_CAPABILITY_ENABLED, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_query_account_by_capability(account_call_back, NULL, ACCOUNT_CAPABILITY_ENABLED, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_query_account_by_capability(account_call_back, contact_capability, -1, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

static bool account_cb_func_return_false(account_h account, void *user_data)
{
	return false;
}
static bool account_cb_func(account_h account, void *user_data)
{
	char* str = NULL;
	char* comparison_str = NULL;
	int value = -1;
	int comparison_value = -1;
	int ret = ACCOUNT_ERROR_NONE;
	check_fail(user_data!=NULL);
	account_h _account = *((account_h*)user_data);

	ret = account_get_package_name(_account, &str);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_package_name(account, &comparison_str);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(str, comparison_str)==0);
	}
	_account_free_text(str);
	_account_free_text(comparison_str);

	ret = account_get_user_name(_account, &str);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_user_name(account, &comparison_str);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(str, comparison_str)==0);
	}
	_account_free_text(str);
	_account_free_text(comparison_str);

	ret = account_get_capability(_account, contact_capability, &value);
	if(is_account_supported)
		check_fail(ret == ACCOUNT_ERROR_NONE);

	ret = account_get_capability(account, contact_capability, &comparison_value);
	if(is_account_supported) {
		check_fail_eq(ret, ACCOUNT_ERROR_NONE);
		check_fail(value == comparison_value);
	}

	_is_fail = false;

	return true;
}

/**
 * @testcase		utc_account_query_account_by_capability_type_p
 * @since_tizen		2.3
 * @description		Positive test case of account_query_account_by_capability_type()
 */
int utc_account_query_account_by_capability_type_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	int account_id = -1;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, contact_capability, ACCOUNT_CAPABILITY_ENABLED);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_account_by_capability_type(account_cb_func, contact_capability, &account);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}

	ret = account_query_account_by_capability_type(account_cb_func_return_false, contact_capability, &account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	_is_fail = true;

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_query_account_by_capability_type_n
 * @since_tizen		2.3
 * @description		Negative test case of account_query_account_by_capability_type()
 */
int utc_account_query_account_by_capability_type_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	const char* type = "type";

	ret = account_query_account_by_capability_type(NULL, type, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_query_account_by_capability_type(account_cb_func, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_query_capability_by_account_id_p
 * @since_tizen		2.3
 * @description		Positive test case of account_query_capability_by_account_id()
 */
int utc_account_query_capability_by_account_id_p(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;
	int account_id = -1;
	account_capability_state_e capability_state = ACCOUNT_CAPABILITY_ENABLED;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, contact_capability, capability_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, contact_capability, capability_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_capability_by_account_id(capability_call_back, account_id, &account);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}

	ret = account_query_capability_by_account_id(capability_call_back_return_false, account_id, &account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	_is_fail = true;

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_query_capability_by_account_id_n
 * @since_tizen		2.3
 * @description		Negative test case of account_query_capability_by_account_id()
 */
int utc_account_query_capability_by_account_id_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_query_capability_by_account_id(capability_call_back, -1, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_query_capability_by_account_id(NULL, 1, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_get_total_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of account_get_total_count_from_db()
 */
int utc_account_get_total_count_from_db_p(void)
{
	int count = -1;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_total_count_from_db(&count);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_get_total_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of account_get_total_count_from_db()
 */
int utc_account_get_total_count_from_db_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_get_total_count_from_db(NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_update_sync_status_by_id_p
 * @since_tizen		2.3
 * @description		Positive test case of account_update_sync_status_by_id()
 */
int utc_account_update_sync_status_by_id_p(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	int account_id = -1;
	account_h ret_account = NULL;
	account_sync_state_e sync_state = -1;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_update_sync_status_by_id(account_id, ACCOUNT_SYNC_STATUS_IDLE);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_create(&ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_account_by_account_id(account_id, &ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_sync_support(ret_account, &sync_state);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(sync_state, ACCOUNT_SYNC_STATUS_IDLE);
	}

	ret = account_destroy(ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_update_sync_status_by_id_n
 * @since_tizen		2.3
 * @description		Negative test case of account_update_sync_status_by_id()
 */
int utc_account_update_sync_status_by_id_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_update_sync_status_by_id(-1, ACCOUNT_SYNC_STATUS_IDLE);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_neq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_delete_from_db_by_id_p
 * @since_tizen		2.3
 * @description		Positive test case of account_delete_from_db_by_id()
 */
int utc_account_delete_from_db_by_id_p(void)
{
	assert(created);
	int account_id = -1;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_delete_from_db_by_id_n
 * @since_tizen		2.3
 * @description		Negative test case of account_delete_from_db_by_id()
 */
int utc_account_delete_from_db_by_id_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_delete_from_db_by_id(-1);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_delete_from_db_by_id(1000000);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_RECORD_NOT_FOUND);}

	return 0;
}

/**
 * @testcase		utc_account_delete_from_db_by_user_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_delete_from_db_by_user_name()
 */
int utc_account_delete_from_db_by_user_name_p(void)
{
	assert(created);
	int account_id = -1;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_delete_from_db_by_user_name(user_name, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_delete_from_db_by_user_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_delete_from_db_by_user_name()
 */
int utc_account_delete_from_db_by_user_name_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	char *delete_package_name = "non_registered_package_name";
	char *delete_user_name = "non_registered_user_name";

	ret = account_delete_from_db_by_user_name(NULL, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_delete_from_db_by_user_name(user_name, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_delete_from_db_by_user_name(delete_user_name, delete_package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_RECORD_NOT_FOUND);}

	return 0;
}

/**
 * @testcase		utc_account_delete_from_db_by_package_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_delete_from_db_by_package_name()
 */
int utc_account_delete_from_db_by_package_name_p(void)
{
	assert(created);

	int account_id = -1;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_delete_from_db_by_package_name(package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_delete_from_db_by_package_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_delete_from_db_by_package_name()
 */
int utc_account_delete_from_db_by_package_name_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	char *delete_package_name = "non_registered_package_name";

	ret = account_delete_from_db_by_package_name(NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_delete_from_db_by_package_name(delete_package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_RECORD_NOT_FOUND);}

	return 0;
}

/**
 * @testcase		utc_account_update_to_db_by_id_p
 * @since_tizen		2.3
 * @description		Positive test case of account_update_to_db_by_id()
 */
int utc_account_update_to_db_by_id_p(void)
{
	assert(created);
	int account_id = -1;
	int ret = ACCOUNT_ERROR_NONE;
	char* update_user_name = "update_user_name";
	char* ret_user_name = NULL;
	account_h ret_account = NULL;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_user_name(account, update_user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_update_to_db_by_id(account, account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_create(&ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_account_by_account_id(account_id, &ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_user_name(account, &ret_user_name);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_user_name, update_user_name), 0);
	}
	_account_free_text(ret_user_name);

	ret = account_destroy(ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_update_to_db_by_id_n
 * @since_tizen		2.3
 * @description		Negative test case of account_update_to_db_by_id()
 */
int utc_account_update_to_db_by_id_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_update_to_db_by_id(account, -1);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_update_to_db_by_id(account, 1000000);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_RECORD_NOT_FOUND);}

	return 0;
}

/**
 * @testcase		utc_account_update_to_db_by_user_name_p
 * @since_tizen		2.3
 * @description		Positive test case of account_update_to_db_by_user_name()
 */
int utc_account_update_to_db_by_user_name_p(void)
{
	assert(created);
	int account_id = -1;
	int ret = ACCOUNT_ERROR_NONE;
	int value = -1;
	char* ret_user_name = NULL;
	account_h ret_account = NULL;
	account_capability_state_e capability_state = ACCOUNT_CAPABILITY_ENABLED;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_capability(account, contact_capability, capability_state);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_update_to_db_by_user_name(account, user_name, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_create(&ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_account_by_account_id(account_id, &ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_user_name(account, &ret_user_name);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_user_name, user_name), 0);
	}
	_account_free_text(ret_user_name);

	ret = account_get_capability(account, contact_capability, &value);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(value, ACCOUNT_CAPABILITY_ENABLED);
	}

	ret = account_destroy(ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_update_to_db_by_user_name_n
 * @since_tizen		2.3
 * @description		Negative test case of account_update_to_db_by_user_name()
 */
int utc_account_update_to_db_by_user_name_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_update_to_db_by_user_name(NULL, user_name, package_name);
	assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);

	ret = account_update_to_db_by_user_name(account, NULL, package_name);
	assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);

	ret = account_update_to_db_by_user_name(account, user_name, NULL);
	assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);

	return 0;
}



/**
 * @testcase		utc_account_subscribe_create_p
 * @since_tizen		2.3
 * @description		Positive test case of account_subscribe_create()
 */
int utc_account_subscribe_create_p(void)
{
	account_subscribe_h account_subscribe;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_subscribe_create(&account_subscribe);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_subscribe_notification(account_subscribe, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_unsubscribe_notification(account_subscribe);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}


/**
 * @testcase		utc_account_subscribe_create_n
 * @since_tizen		2.3
 * @description		Negative test case of account_subscribe_create()
 */
int utc_account_subscribe_create_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_subscribe_create(NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}


/**
 * @testcase		utc_account_subscribe_notification_p
 * @since_tizen		2.3
 * @description		Positive test case of account_subscribe_notification()
 */
int utc_account_subscribe_notification_p(void)
{
	account_subscribe_h account_subscribe;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_subscribe_create(&account_subscribe);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_subscribe_notification(account_subscribe, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_unsubscribe_notification(account_subscribe);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}


/**
 * @testcase		utc_account_subscribe_notification_n
 * @since_tizen		2.3
 * @description		Negative test case of account_subscribe_notification()
 */
int utc_account_subscribe_notification_n(void)
{
	account_subscribe_h account_subscribe;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_subscribe_create(&account_subscribe);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_subscribe_notification(NULL, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_subscribe_notification(account_subscribe, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_unsubscribe_notification(account_subscribe);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_unsubscribe_notification_p
 * @since_tizen		2.3
 * @description		Positive test case of account_unsubscribe_notification()
 */
int utc_account_unsubscribe_notification_p(void)
{
	account_subscribe_h account_subscribe;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_subscribe_create(&account_subscribe);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_subscribe_notification(account_subscribe, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_unsubscribe_notification(account_subscribe);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}


/**
 * @testcase		utc_account_unsubscribe_notification_n
 * @since_tizen		2.3
 * @description		Negative test case of account_unsubscribe_notification()
 */
int utc_account_unsubscribe_notification_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_unsubscribe_notification(NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_type_create_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_create()
 */
int utc_account_type_create_p(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_create_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_create()
 */
int utc_account_type_create_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_type_create(NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_type_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_destroy()
 */
int utc_account_type_destroy_p(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_destroy()
 */
int utc_account_type_destroy_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_type_destroy(NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_app_id_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_get_app_id()
 */
int utc_account_type_get_app_id_p(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	const char* app_id = TEST_PACKAGE_NAME;
	char* ret_app_id = NULL;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_query_by_app_id(app_id, &account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_app_id(account_type, &ret_app_id);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_app_id, app_id), 0);
	}
	_account_free_text(ret_app_id);

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_app_id_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_get_app_id()
 */
int utc_account_type_get_app_id_n(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	char* ret_app_id = NULL;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_app_id(NULL, &ret_app_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_get_app_id(account_type, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_icon_path_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_get_icon_path()
 */
int utc_account_type_get_icon_path_p(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	char *app_id = TEST_PACKAGE_NAME;
	char *ret_icon_path = NULL;
	char* icon_path = NULL;

	icon_path = _account_get_path(ICON);
	dlog_print(DLOG_ERROR, "ACCOUNT_TC", "icon_path %s", icon_path);

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_query_by_app_id(app_id, &account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_icon_path(account_type, &ret_icon_path);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		dlog_print(DLOG_ERROR, "ACCOUNT_TC", "ret_icon_path %s", ret_icon_path);
		assert_eq(strcmp(ret_icon_path, icon_path), 0);
	}
	_account_free_text(ret_icon_path);
	_account_free_text(icon_path);

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_icon_path_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_get_icon_path()
 */
int utc_account_type_get_icon_path_n(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	char* ret_icon_path = NULL;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_icon_path(NULL, &ret_icon_path);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_get_icon_path(account_type, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_label_by_locale_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_get_label_by_locale()
 */
int utc_account_type_get_label_by_locale_p(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	const char* app_id = TEST_PACKAGE_NAME;
	const char* locale = "en_GB";
	char* ret_label = NULL;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_query_by_app_id(app_id, &account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_label_by_locale(account_type, locale, &ret_label);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_label, test_label_en_gb), 0);
	}
	_account_free_text(ret_label);

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_label_by_locale_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_get_label_by_locale()
 */
int utc_account_type_get_label_by_locale_n(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	char* ret_label = NULL;
	const char* locale = "locale";

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_label_by_locale(NULL, locale, &ret_label);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_get_label_by_locale(account_type, locale, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

static bool account_label_cb_func(char* app_id, char* label, char* locale, void *user_data) {
	//this callback function checks that query function implements normally through confirmming whether same labels or not.
	if(user_data != NULL)
	{
		const char* _label = (const char*)user_data;
		if(strcmp(label, _label)==0)
			_is_fail = false;
	}

	return TRUE;
}

/**
 * @testcase		utc_account_type_get_label_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_get_label()
 */
int utc_account_type_get_label_p(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	const char* app_id = TEST_PACKAGE_NAME;
	const char* label = "label";
	const char* locale = "locale";

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_query_by_app_id(app_id, &account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_label(account_type, account_label_cb_func, (void*)test_label_en_gb);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}

	_is_fail = true;

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_label_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_get_label()
 */
int utc_account_type_get_label_n(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_label(NULL, account_label_cb_func, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_get_label(account_type, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_multiple_account_support_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_get_multiple_account_support()
 */
int utc_account_type_get_multiple_account_support_p(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	int ret_val = 0;
	const char *app_id = TEST_PACKAGE_NAME;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_query_by_app_id(app_id, &account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_multiple_account_support(account_type, &ret_val);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(ret_val, true);
	}

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_multiple_account_support_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_get_multiple_account_support()
 */
int utc_account_type_get_multiple_account_support_n(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	bool ret_val = true;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_multiple_account_support(NULL, &ret_val);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_get_multiple_account_support(account_type, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

static bool provider_feature_cb_func_return_false(char* app_id, char* key, void* user_data)
{
	_is_fail = false;
	return false;
}
static bool provider_feature_cb_func(char* app_id, char* key, void* user_data)
{
	//this callback function checks that query function implements normally through confirmming whether same provider feature or not.

	if( strcmp(key, contact_capability) != 0 ) {
		check_fail( strcmp(key, calendar_capability)==0 );
	}

	_is_fail = false;

	return TRUE;
}

/**
 * @testcase		utc_account_type_get_provider_feature_all_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_get_provider_feature_all()
 */
int utc_account_type_get_provider_feature_all_p(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	const char* provider_feature = "provider_feature";
	const char* app_id = TEST_PACKAGE_NAME;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_query_by_app_id(app_id, &account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	_is_fail = true;
	ret = account_type_get_provider_feature_all(account_type, provider_feature_cb_func, (void *)provider_feature);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}

	_is_fail = true;

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_provider_feature_all_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_get_provider_feature_all()
 */
int utc_account_type_get_provider_feature_all_n(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_provider_feature_all(NULL, provider_feature_cb_func, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_get_provider_feature_all(account_type, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_service_provider_id_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_get_service_provider_id()
 */
int utc_account_type_get_service_provider_id_p(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	const char *app_id = TEST_PACKAGE_NAME;
	const char *service_provider_id = SERVICE_PROVIDER_ID;
	char* ret_service_provider_id = NULL;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_query_by_app_id(app_id, &account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_service_provider_id(account_type, &ret_service_provider_id);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_service_provider_id, service_provider_id), 0);
	}

	_account_free_text(ret_service_provider_id);

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_service_provider_id_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_get_service_provider_id()
 */
int utc_account_type_get_service_provider_id_n(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	char* ret_service_provider_id = NULL;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_service_provider_id(account_type, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_get_service_provider_id(NULL, &ret_service_provider_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_small_icon_path_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_get_small_icon_path()
 */
int utc_account_type_get_small_icon_path_p(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	char *ret_small_icon_path = NULL;
	const char *app_id = TEST_PACKAGE_NAME;
	char *small_icon_path = NULL;

	small_icon_path = _account_get_path(SMALL_ICON);
	dlog_print(DLOG_ERROR, "ACCOUNT_TC", "small_icon_path %s", small_icon_path);

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_query_by_app_id(app_id, &account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_small_icon_path(account_type, &ret_small_icon_path);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		dlog_print(DLOG_ERROR, "ACCOUNT_TC", "ret_small_icon_path %s", ret_small_icon_path);
		assert_eq(strcmp(ret_small_icon_path, small_icon_path), 0);
	}
	_account_free_text(ret_small_icon_path);
	_account_free_text(small_icon_path);

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_get_small_icon_path_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_get_small_icon_path()
 */
int utc_account_type_get_small_icon_path_n(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	char* ret_small_icon_path = NULL;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_small_icon_path(NULL, &ret_small_icon_path);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_get_small_icon_path(account_type, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_query_by_app_id_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_query_by_app_id()
 */
int utc_account_type_query_by_app_id_p(void)
{
	account_type_h ret_account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	const char* app_id = TEST_PACKAGE_NAME;
	char* ret_app_id = NULL;
	int account_type_id = 0;

	ret = account_type_create(&ret_account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_query_by_app_id(app_id, &ret_account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_get_app_id(ret_account_type, &ret_app_id);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_app_id, app_id), 0);
	}

	_account_free_text(ret_app_id);

	ret = account_type_destroy(ret_account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}


/**
 * @testcase		utc_account_type_query_by_app_id_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_query_by_app_id()
 */
int utc_account_type_query_by_app_id_n(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	const char* app_id = "account_type_query_by_app_id";

	ret = account_type_query_by_app_id(app_id, &account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_query_by_app_id(NULL, &account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_query_by_app_id(app_id, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}


/**
 * @testcase		utc_account_type_query_app_id_exist_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_query_app_id_exist()
 */
int utc_account_type_query_app_id_exist_p(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	const char* not_registered_app_id = "account_type_query_app_id_exist";
	const char* app_id = TEST_PACKAGE_NAME;
	int a_type_id = -1;

	ret = account_type_query_app_id_exist(not_registered_app_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_RECORD_NOT_FOUND);}

	ret = account_type_query_app_id_exist(app_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_query_app_id_exist_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_query_app_id_exist()
 */
int utc_account_type_query_app_id_exist_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_type_query_app_id_exist(NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

static bool account_type_for_query_by_provider_cb_return_false(account_type_h account_type, void *user_data)
{
	_is_fail = false;
	return false;
}

static bool account_type_for_query_by_provider_cb(account_type_h account_type, void *user_data)
{
	//this callback function checks that query function implements normally through confirmming whether same app_id or not.
	int ret = ACCOUNT_ERROR_NONE;
	char* app_id = NULL;
	char* service_provider_id = NULL;
	char* icon_path = NULL;
	char* small_icon_path = NULL;
	bool multi_account_support = true;
	char* label = NULL;
	const char* locale = "en_GB";
	char* capability = contact_capability;
	char* test_icon_path = NULL;
	char* test_small_icon_path = NULL;

	check_fail(account_type != NULL);

	test_icon_path = _account_get_path(ICON);
	test_small_icon_path = _account_get_path(SMALL_ICON);
	dlog_print(DLOG_ERROR, "ACCOUNT_TC", "test_icon_path %s", test_icon_path);
	dlog_print(DLOG_ERROR, "ACCOUNT_TC", "test_small_icon_path %s", test_small_icon_path);

	ret = account_type_get_app_id(account_type, &app_id);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(package_name, app_id)==0);
	}
	_account_free_text(app_id);

	ret = account_type_get_icon_path(account_type, &icon_path);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(test_icon_path, icon_path)==0);
	}
	_account_free_text(icon_path);
	_account_free_text(test_icon_path);

	ret = account_type_get_small_icon_path(account_type, &small_icon_path);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(test_small_icon_path, small_icon_path)==0);
	}
	_account_free_text(small_icon_path);
	_account_free_text(test_small_icon_path);

	ret = account_type_get_multiple_account_support(account_type, &multi_account_support);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(test_multi_account_support == multi_account_support);
	}

	ret = account_type_get_label_by_locale(account_type, locale, &label);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(test_label_en_gb, label) == 0);
	}
	_account_free_text(label);

	_is_fail = true;
	ret = account_type_get_provider_feature_all(account_type, provider_feature_cb_func,  capability);
	if(is_account_supported) {
		check_fail(_is_fail == false);
		check_fail(ret == ACCOUNT_ERROR_NONE);
	}

	_is_fail = false;

	return true;
}


/**
 * @testcase		utc_account_type_query_by_provider_feature_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_query_by_provider_feature()
 */
int utc_account_type_query_by_provider_feature_p(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	const char* app_id = "account_type_query_by_provider_feature";
	const char* service_provider_id = TEST_PACKAGE_NAME;
	const char* icon_path = "icon_path";
	const char* small_icon_path = "small_icon_path";
	const char* capability = "capability";
	const bool multi_account_support = true;
	const char* label = "label";
	const char* locale = "locale";

	int a_type_id = -1;

	ret = account_type_query_by_provider_feature(account_type_for_query_by_provider_cb, contact_capability, NULL);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}

	ret = account_type_query_by_provider_feature(account_type_for_query_by_provider_cb_return_false, contact_capability, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	_is_fail = true;

	return 0;
}


/**
 * @testcase		utc_account_type_query_by_provider_feature_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_query_by_provider_feature()
 */
int utc_account_type_query_by_provider_feature_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	const char* key = contact_capability;

	ret = account_type_query_by_provider_feature(account_type_for_query_by_provider_cb, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_query_by_provider_feature(NULL, key, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

static bool account_type_for_query_by_app_id_cb_return_false(char* app_id, char* label, char* locale, void *user_data)
{
	return false;
}

static bool account_type_for_query_by_app_id_cb(char* app_id, char* label, char* locale, void *user_data)
{
	//this callback function checks that query function implements normally through confirmming whether same label or not.
	int ret = ACCOUNT_ERROR_NONE;
	account_type_h account_type = NULL;
	char* ret_label = NULL;

	check_fail( app_id!=NULL && label!=NULL && locale!=NULL && user_data!=NULL );
	ret_label = (char *)user_data;

	if (app_id == package_name)
		check_fail(strcmp(ret_label, label) == 0);

	_is_fail = false;

	return TRUE;
}

/**
 * @testcase		utc_account_type_query_label_by_app_id_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_query_label_by_app_id()
 */
int utc_account_type_query_label_by_app_id_p(void)
{
	account_type_h account_type = NULL;
	int ret = ACCOUNT_ERROR_NONE;
	int a_type_id = -1;

	const char* label_t = "label_test";
	const char* locale_t = "locale_test";
	const char* app_id = "account_type_query_label_by_app_id";
	const char* service_provider_id = TEST_PACKAGE_NAME;

	ret = account_type_create(&account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_type_query_label_by_app_id(account_type_for_query_by_app_id_cb, package_name, test_label_en_gb);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}

	ret = account_type_query_label_by_app_id(account_type_for_query_by_app_id_cb_return_false, package_name, test_label_en_gb);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	_is_fail = true;

	account_type_destroy(account_type);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_type_query_label_by_app_id_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_query_label_by_app_id()
 */
int utc_account_type_query_label_by_app_id_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	const char* app_id = "account_type_query_label_by_app_id";

	ret = account_type_query_label_by_app_id(NULL, app_id, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_query_label_by_app_id(account_type_for_query_by_app_id_cb, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_type_query_label_by_locale_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_query_label_by_locale()
 */
int utc_account_type_query_label_by_locale_p(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	const char* locale = "en_GB";
	const char* app_id = TEST_PACKAGE_NAME;
	char* ret_label = NULL;

	ret = account_type_query_label_by_locale(app_id, locale, &ret_label);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_label, test_label_en_gb), 0);
	}
	_account_free_text(ret_label);

	return 0;
}

/**
 * @testcase		utc_account_type_query_label_by_locale_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_query_label_by_locale()
 */
int utc_account_type_query_label_by_locale_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	const char* app_id = "account_type_query_label_by_locale";
	const char* locale = "locale";
	char* ret_label = NULL;

	ret = account_type_get_label_by_locale(NULL, locale, &ret_label);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_get_label_by_locale(app_id, locale, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_type_query_provider_feature_by_app_id_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_query_provider_feature_by_app_id()
 */
int utc_account_type_query_provider_feature_by_app_id_p(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	account_type_h account_type = NULL;
	const char* app_id = TEST_PACKAGE_NAME;
	int account_type_id = -1;

	ret = account_type_query_provider_feature_by_app_id(provider_feature_cb_func, app_id, NULL);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}
	_is_fail = true;

	return 0;
}

/**
 * @testcase		utc_account_type_query_provider_feature_by_app_id_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_query_provider_feature_by_app_id()
 */
int utc_account_type_query_provider_feature_by_app_id_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;
	const char* app_id = "application_id";
	const char* provider_feature = "provider_feature";

	ret = account_type_query_provider_feature_by_app_id(provider_feature_cb_func, app_id,provider_feature);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_RECORD_NOT_FOUND);}

	ret = account_type_query_provider_feature_by_app_id(NULL, app_id, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_type_query_provider_feature_by_app_id(provider_feature_cb_func, NULL, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}

/**
 * @testcase		utc_account_type_query_supported_feature_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_query_supported_feature()
 */
int utc_account_type_query_supported_feature_p(void)
{
	bool ret = true;
	const char* app_id = TEST_PACKAGE_NAME;
	const char* capability = contact_capability;

	ret = account_type_query_supported_feature(app_id, capability);
	assert_eq(ret, true);

	return 0;
}

/**
 * @testcase		utc_account_type_query_supported_feature_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_query_supported_feature()
 */
int utc_account_type_query_supported_feature_n(void)
{
	bool ret = true;
	const char* app_id = "application_id";
	const char* capability = "capability";

	ret = account_type_query_supported_feature(app_id, capability);
	if(!is_account_supported)
	{
		assert_eq(ret, true);
	}
	else
	{
		assert_eq(ret, false);
		assert_eq(get_last_result(), ACCOUNT_ERROR_RECORD_NOT_FOUND);
	}

	ret = account_type_query_supported_feature(NULL, capability);
	if(!is_account_supported)
	{
		assert_eq(ret, true);
	}
	else
	{
		assert_eq(ret, false);
		assert_eq(get_last_result(), ACCOUNT_ERROR_INVALID_PARAMETER);
	}

	ret = account_type_query_supported_feature(app_id, NULL);
	if(!is_account_supported)
	{
		assert_eq(ret, true);
	}
	else
	{
		assert_eq(ret, FALSE);
	}

	return 0;
}

/**
 * @testcase		utc_account_update_to_db_by_id_ex_p
 * @since_tizen		2.3
 * @description		Positive test case of account_update_to_db_by_id_ex()
 */
int utc_account_update_to_db_by_id_ex_p(void)
{
	assert(created);
	int account_id = -1;
	int ret = ACCOUNT_ERROR_NONE;
	char* update_user_name = "update_user_name";
	char* ret_user_name = NULL;
	account_h ret_account = NULL;

	ret = account_set_user_name(account, user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_package_name(account, package_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_insert_to_db(account, &account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_set_user_name(account, update_user_name);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_update_to_db_by_id_ex(account, account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_create(&ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_query_account_by_account_id(account_id, &ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_get_user_name(account, &ret_user_name);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		assert_eq(ret, ACCOUNT_ERROR_NONE);
		assert_eq(strcmp(ret_user_name, update_user_name), 0);
	}
	_account_free_text(ret_user_name);

	ret = account_destroy(ret_account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	ret = account_delete_from_db_by_id(account_id);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	return 0;
}

/**
 * @testcase		utc_account_update_to_db_by_id_ex_n
 * @since_tizen		2.3
 * @description		Negative test case of account_update_to_db_by_id_ex()
 */
int utc_account_update_to_db_by_id_ex_n(void)
{
	assert(created);
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_update_to_db_by_id_ex(account, -1);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_update_to_db_by_id_ex(NULL, 1);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	ret = account_update_to_db_by_id(account, 1000000);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_RECORD_NOT_FOUND);}

	return 0;
}

static bool account_type_cb_func_return_false(account_type_h account_type, void *user_data)
{
	_is_fail = false;
	return false;
}

static bool account_type_cb_func(account_type_h account_type, void *user_data) {
	//this callback function checks that query function implements normally through confirmming whether same app_id or not.
	int ret = ACCOUNT_ERROR_NONE;
	account_type_h ret_account_type = NULL;
	char* app_id = NULL;
	char* service_provider_id = NULL;
	char* icon_path = NULL;
	char* small_icon_path = NULL;
	bool multi_account_support = true;
	char* label = NULL;
	const char* locale = "en_GB";
	char* capability = NULL;
	char* test_icon_path = NULL;
	char* test_small_icon_path = NULL;

	check_fail(account_type != NULL);

	test_icon_path = _account_get_path(ICON);
	test_small_icon_path = _account_get_path(SMALL_ICON);
	dlog_print(DLOG_ERROR, "ACCOUNT_TC", "test_icon_path %s", test_icon_path);
	dlog_print(DLOG_ERROR, "ACCOUNT_TC", "test_small_icon_path %s", test_small_icon_path);

	ret = account_type_get_app_id(account_type, &app_id);
	if(is_account_supported) {
		if(ret != ACCOUNT_ERROR_NONE) {
			_is_fail=true;
			_account_free_text(app_id);
			return true;
		}
		if( strcmp(app_id, package_name) != 0 )
		{
			_is_fail=true;
			_account_free_text(app_id);
			return true;
		}
	}
	_account_free_text(app_id);

	ret = account_type_get_icon_path(account_type, &icon_path);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(test_icon_path, icon_path)==0);
	}
	_account_free_text(icon_path);
	_account_free_text(test_icon_path);

	ret = account_type_get_small_icon_path(account_type, &small_icon_path);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(test_small_icon_path, small_icon_path)==0);
	}
	_account_free_text(small_icon_path);
	_account_free_text(test_small_icon_path);

	ret = account_type_get_multiple_account_support(account_type, &multi_account_support);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(test_multi_account_support == multi_account_support);
	}

	ret = account_type_get_label_by_locale(account_type, locale, &label);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(strcmp(test_label_en_gb, label) == 0);
	}
	_account_free_text(label);

	_is_fail = true;
	ret = account_type_get_provider_feature_all(account_type, provider_feature_cb_func, (void *)contact_capability);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(_is_fail == false);
	}

	_is_fail = true;
	ret = account_type_get_provider_feature_all(account_type, provider_feature_cb_func_return_false, (void *)contact_capability);
	if(is_account_supported) {
		check_fail(ret == ACCOUNT_ERROR_NONE);
		check_fail(_is_fail == false);
	}

	_is_fail = false;

	return false;
}

/**
 * @testcase		utc_account_type_foreach_account_type_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of account_type_foreach_account_type_from_db()
 */
int utc_account_type_foreach_account_type_from_db_p(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	_is_fail = true;

	ret = account_type_foreach_account_type_from_db(account_type_cb_func, NULL);
	if(!is_account_supported)
	{
		assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);
	}
	else
	{
		is_callback_fail();
		assert_eq(ret, ACCOUNT_ERROR_NONE);
	}

	ret = account_type_foreach_account_type_from_db(account_type_cb_func_return_false, NULL);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_NONE);}

	_is_fail = false;

	return 0;
}

/**
 * @testcase		utc_account_type_foreach_account_type_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of account_type_foreach_account_type_from_db()
 */
int utc_account_type_foreach_account_type_from_db_n(void)
{
	int ret = ACCOUNT_ERROR_NONE;

	ret = account_type_foreach_account_type_from_db(NULL, account);
	if(!is_account_supported){assert_eq(ret, ACCOUNT_ERROR_NOT_SUPPORTED);}
	else{assert_eq(ret, ACCOUNT_ERROR_INVALID_PARAMETER);}

	return 0;
}
