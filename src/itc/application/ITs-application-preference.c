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
#include "ITs-application-common.h"

/** @addtogroup itc-application
*  @ingroup itc
*  @{
*/
//& set: Application

int g_bPreferenceChangedCallback = false;
int g_bPreferenceItemCallback = false;

bool g_bCallBackHit_preference = false;
bool g_bUserDataMismatch_preference = false;

void *g_pUserData_preference = "user_data_1";


/**
* @function 		ITs_application_preference_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_preference_startup(void)
{
	g_bCallBackHit_preference = false;
	g_bCallBackHit_preference = false;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Application_preference_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(2, TEST_HELLOWORLD_APPID, TEST_TESTAPPLICATION_APPID);
	return;
}

/**
* @function 		ITs_application_preference_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_preference_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Application_preference_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		application_preference_changed_cb
* @description	 	callback function for app preference change
* @parameter		pszKey : key, user_data : user data sent to callback
* @return 			NA
*/
void application_preference_changed_cb(const char *pszKey, void *user_data)
{
	g_bCallBackHit_preference = true;
	if(strcmp((char *)user_data,(char *)g_pUserData_preference) != 0)
	{
		g_bUserDataMismatch_preference = true;
	}

	g_bPreferenceChangedCallback = true;
	FPRINTF("[Line : %d][%s] preference_changed_callback invoked, key = %s\\n", __LINE__, API_NAMESPACE, pszKey);
	
	if(g_pApplicationMainLoop)
	{
		g_main_loop_quit(g_pApplicationMainLoop);
		g_pApplicationMainLoop = NULL;
	}
}

/**
* @function 		application_preference_item_cb
* @description	 	callback function for app preference item
* @parameter		pszKey : key, user_data : user data sent to callback
* @return 			true
*/
bool application_preference_item_cb(const char *pszKey, void *user_data)
{
	g_bCallBackHit_preference = true;
	if(strcmp((char *)user_data,(char *)g_pUserData_preference) != 0)
	{
		g_bUserDataMismatch_preference = true;
	}


	g_bPreferenceItemCallback = true;
	FPRINTF("[Line : %d][%s] preference_item_callback invoked, key = %s\\n", __LINE__, API_NAMESPACE, pszKey);

	return true;
}

//& type: auto
//& purpose: Set and Get Preference Boolean.
/**
* @testcase 			ITc_application_preference_set_get_boolean_p
* @since_tizen			2.3
* @type 				auto
* @description			Set Preference Boolean, Get Preference Boolean and then checks the set value should match the get value
* @scenario				Set Preference Boolean\n
*						Get Preference Boolean
* @apicovered			preference_set_boolean, preference_get_boolean
* @passcase				When preference_set_boolean, preference_get_boolean are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_preference_set_get_boolean_p(void)
{
	START_TEST;

	char *pszKey = "Sample_Key";//sample key-value pair
	bool bValue = true;
	bool bGetVal = 0;

	int nRet = preference_set_boolean(pszKey, bValue);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_set_boolean", PreferenceGetError(nRet));

	nRet = preference_get_boolean(pszKey, &bGetVal);
	preference_remove(pszKey);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_get_boolean", PreferenceGetError(nRet));

	//check for value mis-match
	if ( bValue != bGetVal )
	{
		FPRINTF("[Line : %d][%s]set and get mis-match occurs, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, bValue, bGetVal);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Set and Get Preference Double.
/**
* @testcase 			ITc_application_preference_set_get_double_p
* @since_tizen			2.3
* @type 				auto
* @description			Set Preference Double, Get Preference Double and then checks the set value should match the get value
* @scenario				Set Preference Double\n
*						Get Preference Double
* @apicovered			preference_set_double, preference_get_double
* @passcase				When preference_set_double, preference_get_double are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_preference_set_get_double_p(void)
{
	START_TEST;

	char *pszKey = "Sample_Key";//sample key-value pair
	double dValue = 1911;
	double dGetVal = 0;

	int nRet = preference_set_double(pszKey, dValue);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_set_double", PreferenceGetError(nRet));

	nRet = preference_get_double(pszKey, &dGetVal);
	preference_remove(pszKey);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_get_double", PreferenceGetError(nRet));

	//check for value mis-match
	if ( dValue != dGetVal )
	{
		FPRINTF("[Line : %d][%s]set and get mis-match occurs, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, (int)dValue, (int)dGetVal);
	}

	return 0;
}

//& type: auto
//& purpose: Set and Get Preference String.
/**
* @testcase 			ITc_application_preference_set_get_string_p
* @type 				auto
* @since_tizen			2.3
* @non-functional-test 	Stability, Memory, Speed
* @description			Set Preference String, Get Preference String and then checks the set value should match the get value
* @scenario				Set Preference String
*						Get Preference String
* @apicovered			preference_set_string, preference_get_string
* @passcase				When preference_set_string, preference_get_string are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_preference_set_get_string_p(void)
{
	START_TEST;

	char *pszKey = "Sample_Key";//sample key-value pair
	char *pszValue = "Sample_Value";
	char* pszGetVal = NULL;

	int nRet = preference_set_string(pszKey, pszValue);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_set_string", PreferenceGetError(nRet));

	nRet = preference_get_string(pszKey, &pszGetVal);
	preference_remove(pszKey);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_get_string", PreferenceGetError(nRet));

	//check for value mis-match
	if ( 0 != strcmp(pszValue, pszGetVal) )
	{
		FPRINTF("[Line : %d][%s] set and get mis-match occurs, set value = %s, get value = %s\\n", __LINE__, API_NAMESPACE, pszValue, pszGetVal);
		FREE_MEMORY(pszGetVal);
		return 1;
	}

	FREE_MEMORY(pszGetVal);

	return 0;
}

//& type: auto
//& purpose: Set Preference Int for a specified key and check if the key is existing and remove it.
/**
* @testcase 			ITc_application_preference_is_existing_remove_p
* @type 				auto
* @since_tizen			2.3
* @non-functional-test 	Stability, Memory, Speed
* @description			Set Preference Int for a specified key, check if the key is existing and then remove it.
* @scenario				Set Preference Int for a specified key
*						check if the key is existing.
*						remove the key.
* @apicovered			preference_set_int, preference_is_existing, preference_remove
* @passcase				When preference_is_existing, preference_remove are successful and return correct value.
* @failcase				If target API fails or return value is incorrect.
* @precondition			None
* @postcondition		None
*/
int ITc_application_preference_is_existing_remove_p(void)
{
	START_TEST;

	char *pszKey = "Sample_Key";//sample key-value pair
	int nValue = 1911;
	bool bExisting = false;

	//Target API
	int nRet = preference_set_int(pszKey, nValue);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_set_int", PreferenceGetError(nRet));

	nRet = preference_is_existing(pszKey, &bExisting);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_is_existing", PreferenceGetError(nRet));
	if ( true != bExisting )
	{
		FPRINTF("[Line : %d][%s] preference_is_existing failed, error returned = false\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = preference_remove(pszKey);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_remove", PreferenceGetError(nRet));

	nRet = preference_is_existing(pszKey, &bExisting);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_is_existing", PreferenceGetError(nRet));

	//check for value mis-match
	if ( bExisting == true )
	{
		FPRINTF("[Line : %d][%s] preference_is_existing returns key existing after preference_remove call\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Set Preference Int for some specified keys and then remove it all.
/**
* @testcase 			ITc_application_preference_remove_all_p
* @since_tizen			2.3
* @type 				auto
* @description			Set Preference Int for a specified key and then remove it all.
* @scenario				Set Preference Int for some specified keys\n
*						remove all the keys.\n
*						check if any key is existing.
* @apicovered			preference_set_int, preference_is_existing, preference_remove_all
* @passcase				When preference_remove_all is successful and it properly remove all the keys.
* @failcase				If target API fails or didn't receive the key properly.
* @precondition			None
* @postcondition		None
*/
int ITc_application_preference_remove_all_p(void)
{
	START_TEST;

	char *pszKey1 = "Sample_Key1";//sample key-value pair
	char *pszKey2 = "Sample_Key2";//sample key-value pair
	int nValue1 = 1911;//sample value
	int nValue2 = 1912;//sample value
	bool bExisting = true;

	//Target API
	int nRet = preference_set_int(pszKey1, nValue1);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_set_int", PreferenceGetError(nRet));

	nRet = preference_set_int(pszKey2, nValue2);
	PRINT_RESULT_CLEANUP(PREFERENCE_ERROR_NONE, nRet, "preference_set_int", PreferenceGetError(nRet), preference_remove_all());

	nRet = preference_remove_all();
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_remove_all", PreferenceGetError(nRet));

	nRet = preference_is_existing(pszKey1, &bExisting);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_is_existing", PreferenceGetError(nRet));
	if ( true == bExisting )
	{
		FPRINTF("[Line : %d][%s] preference_is_existing returns key existing for key value = %s after preference_remove_all call\\n", __LINE__, API_NAMESPACE, pszKey1 );
		return 1;
	}

	nRet = preference_is_existing(pszKey2, &bExisting);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_is_existing", PreferenceGetError(nRet));
	if ( true == bExisting )
	{
		FPRINTF("[Line : %d][%s] preference_is_existing returns key existing for key value = %s after preference_remove_all call\\n", __LINE__, API_NAMESPACE, pszKey2);
		return 1;
	}

	return 0;
}


//& type: auto
//& purpose: Set Preference Int for a specified key, set state change callback, update set value, checks the callback for updated value and then unset the callback.
/**
* @testcase 			ITc_application_preference_set_unset_changed_callback_p
* @since_tizen			2.3
* @type 				auto
* @description			Set Preference Int for a specified key, set state change callback, update set value, checks the callback for updated value and then unset the callback.
* @scenario				Set Preference Int for a specified key\n
*						set state change callback\n
*						update set value\n
*						checks the callback for updated value\n
*						unset state change callback
* @apicovered			preference_set_int, preference_set_changed_cb, preference_unset_changed_cb, preference_remove
* @passcase				When preference_set_changed_cb, preference_unset_changed_cb are successful and callback is invoked properly for updated set value.
* @failcase				If target API fails or callback not invoked properly.
* @precondition			None
* @postcondition		None
*/
int ITc_application_preference_set_unset_changed_callback_p(void)
{
	START_TEST;

	char *pszKey = "Sample_Key";//sample key-value pair
	int nValue = 1911;//sample value
    int nTimeoutId = 0;
	int nNewValue = 1093;//any sample new value different from original
	int nRet = preference_set_int(pszKey, nValue);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_set_int", PreferenceGetError(nRet));

	g_bPreferenceChangedCallback = false;

	nRet = preference_set_changed_cb( pszKey, application_preference_changed_cb, g_pUserData_preference);
	PRINT_RESULT_CLEANUP(PREFERENCE_ERROR_NONE, nRet, "preference_set_changed_cb", PreferenceGetError(nRet), preference_remove(pszKey));

	nRet = preference_set_int(pszKey, nNewValue);
	PRINT_RESULT_CLEANUP(PREFERENCE_ERROR_NONE, nRet, "preference_set_int", PreferenceGetError(nRet), preference_unset_changed_cb(pszKey);preference_remove(pszKey));
	
	RUN_POLLING_LOOP;

	if(false == g_bPreferenceChangedCallback)
	{
		FPRINTF("[Line : %d][%s] Callback not invoked\\n", __LINE__, API_NAMESPACE);
		preference_unset_changed_cb(pszKey);
		preference_remove(pszKey);
		return 1;
	}
	
	if(g_bUserDataMismatch_preference)
	{
		FPRINTF("[Line : %d][%s] User data in callback is not same which is passed through caller function.\\n", __LINE__, API_NAMESPACE);
		preference_unset_changed_cb(pszKey);
		preference_remove(pszKey);
		return 1;
	}

	nRet = preference_unset_changed_cb(pszKey);
	PRINT_RESULT_CLEANUP(PREFERENCE_ERROR_NONE, nRet, "preference_unset_changed_cb", PreferenceGetError(nRet), preference_remove(pszKey));
	preference_remove(pszKey);

	return 0;
}


//& type: auto
//& purpose: Set Preference Int for a specified key, set item callback, checks the callback for item value.
/**
* @testcase 			ITc_application_preference_for_each_item_callback_p
* @since_tizen			2.4
* @type 				auto
* @description			Set Preference Int for a specified key, set item callback, checks the callback for item value.
* @scenario				Set Preference Int for a specified key\n
*						set item callback\n
*						checks the callback for item value
* @apicovered			preference_set_int, preference_foreach_item, preference_remove
* @passcase				When preference_foreach_item is successful and callback is invoked properly for set value.
* @failcase				If target API fails or callback not invoked properly.
* @precondition			None
* @postcondition		None
*/
int ITc_application_preference_for_each_item_callback_p(void)
{
	START_TEST;

	char *pszKey = "Sample_Key";//sample key-value pair
	int nValue = 1911;//sample value

	int nRet = preference_set_int(pszKey, nValue);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_set_int", PreferenceGetError(nRet));

	g_bPreferenceItemCallback = false;

	nRet = preference_foreach_item(application_preference_item_cb, g_pUserData_preference);
	PRINT_RESULT_CLEANUP(PREFERENCE_ERROR_NONE, nRet, "preference_foreach_item", PreferenceGetError(nRet), preference_remove(pszKey));

	int nTimer = 0;
	for ( ;nTimer<WAIT_CALLBACK;++nTimer )
	{
		if ( true == g_bPreferenceItemCallback )
		{
			break;
		}
		usleep(2000);
	}

	if ( nTimer >= WAIT_CALLBACK )
	{
		FPRINTF("[Line : %d][%s] preference_item_cb callback not hit\\n", __LINE__, API_NAMESPACE);
		preference_remove(pszKey);
		return 1;
	}

	if(false == g_bCallBackHit_preference)
	{
		FPRINTF("[Line : %d][%s] Callback not invoked\\n", __LINE__, API_NAMESPACE);
		preference_remove(pszKey);
		return 1;
	}
	
	if(g_bUserDataMismatch_preference)
	{
		FPRINTF("[Line : %d][%s] User data in callback is not same which is passed through caller function.\\n", __LINE__, API_NAMESPACE);
		preference_remove(pszKey);
		return 1;
	}

	preference_remove(pszKey);

	return 0;
}

//& type: auto
//& purpose: To set the string value for the preference type and get the type for the preference.
/**
* @testcase 			ITc_application_preference_get_type_string_p
* @since_tizen			6.0
* @type 				auto
* @description			Sets the string type and gets the type of the preference.
* @scenario				Set Preference String for a specified key\n
*						Gets the preference type\n
*						Compares get and set values
* @apicovered			preference_get_type
* @passcase				Target API is succesfull and returns prefernce_type as PREFERENCE_TYPE_STRING.
* @failcase				Target API fails or doesn't returns prefernce_type as PREFERENCE_TYPE_STRING.
* @precondition			None
* @postcondition		None
*/
int ITc_application_preference_get_type_string_p(void)
{
	START_TEST;

	char *pszKey = "Sample_Key";
	preference_type_e eType;
	char *pszValue = "Sample_Value";

	int nRet = preference_set_string(pszKey, pszValue);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_set_string", PreferenceGetError(nRet));

	nRet = preference_get_type(pszKey, &eType);
	preference_remove(pszKey);

	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_get_type", PreferenceGetError(nRet));
	PRINT_RESULT(PREFERENCE_TYPE_STRING, eType, "preference_get_type", PreferenceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To set the int value for the preference type and get the type for the preference.
/**
* @testcase 			ITc_application_preference_get_type_int_p
* @since_tizen			6.0
* @type 				auto
* @description			Sets the int type and gets the type of the preference.
* @scenario				Set Preference INT for a specified key\n
*						Gets the preference type\n
*						Compares get and set values
* @apicovered			preference_get_type
* @passcase				Target API is succesfull and returns prefernce_type as PREFERENCE_TYPE_INT.
* @failcase				Target API fails or doesn't returns prefernce_type as PREFERENCE_TYPE_INT.
* @precondition			None
* @postcondition		None
*/
int ITc_application_preference_get_type_int_p(void)
{
	START_TEST;

	const char *pszKey = "preference_key";
	preference_type_e eType;
	int nValue = 1;

	int nRet = preference_set_int(pszKey, nValue);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_set_int", PreferenceGetError(nRet));

	nRet = preference_get_type(pszKey, &eType);
	preference_remove(pszKey);

	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_get_type", PreferenceGetError(nRet));
	PRINT_RESULT(PREFERENCE_TYPE_INT, eType, "preference_get_type", PreferenceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To set the double value for the preference type and get the type for the preference.
/**
* @testcase 			ITc_application_preference_get_type_double_p
* @since_tizen			6.0
* @type 				auto
* @description			Sets the double type and gets the type of the preference.
* @scenario				Set Preference DOUBLE for a specified key\n
*						Gets the preference type\n
*						Compares get and set values
* @apicovered			preference_get_type
* @passcase				Target API is succesfull and returns prefernce_type as PREFERENCE_TYPE_DOUBLE.
* @failcase				Target API fails or doesn't returns prefernce_type as PREFERENCE_TYPE_DOUBLE.
* @precondition			None
* @postcondition		None
*/
int ITc_application_preference_get_type_double_p(void)
{
	START_TEST;

	char *pszKey = "Sample_Key";
	preference_type_e eType;
	double dValue = 1911;

	int nRet = preference_set_double(pszKey, dValue);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_set_double", PreferenceGetError(nRet));

	nRet = preference_get_type(pszKey, &eType);
	preference_remove(pszKey);

	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_get_type", PreferenceGetError(nRet));
	PRINT_RESULT(PREFERENCE_TYPE_DOUBLE, eType, "preference_get_type", PreferenceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To set the boolean value for the preference type and get the type for the preference.
/**
* @testcase 			ITc_application_preference_get_type_boolean_p
* @since_tizen			6.0
* @type 				auto
* @description			Sets the boolean type and gets the type of the preference.
* @scenario				Set Preference BOOLEAN for a specified key\n
*						Gets the preference type\n
*						Compares get and set values
* @apicovered			preference_get_type
* @passcase				Target API is succesfull and returns prefernce_type as PREFERENCE_TYPE_BOOLEAN.
* @failcase				Target API fails or doesn't returns prefernce_type as PREFERENCE_TYPE_BOOLEAN.
* @precondition			None
* @postcondition		None
*/
int ITc_application_preference_get_type_boolean_p(void)
{
	START_TEST;

	char *pszKey = "Sample_Key";
	preference_type_e eType;
	bool bValue = true;

	int nRet = preference_set_boolean(pszKey, bValue);
	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_set_boolean", PreferenceGetError(nRet));

	nRet = preference_get_type(pszKey, &eType);
	preference_remove(pszKey);

	PRINT_RESULT(PREFERENCE_ERROR_NONE, nRet, "preference_get_type", PreferenceGetError(nRet));
	PRINT_RESULT(PREFERENCE_TYPE_BOOLEAN, eType, "preference_get_type", PreferenceGetError(nRet));

	return 0;
}

/** @} */
/** @} */
