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
#include "ITs-webkit2-common.h"

/** @addtogroup itc-webkit2
*  @ingroup itc
*  @{
*/


/**
* @function 		ITs_webkit_efl_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_context_form_startup(void)
{
struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}


/**
* @function 		ITs_webkit_efl_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_context_form_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& purpose: Saves & Removes Autofill Form profile completely
//& type: auto
/**
* @testcase 			ITc_ewk_context_form_autofill_profile_add_remove_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Saves & Removes Autofill Form profile completely
* @scenario				ewk_autofill_profile_new\n
*						ewk_view_settings_get\n
*						ewk_view_context_get\n
*						ewk_context_form_autofill_profile_add\n
*						ewk_context_form_autofill_profile_remove\n
*						ewk_context_form_autofill_profile_get\n
*						ewk_autofill_profile_delete
* @apicovered			ewk_view_settings_get, ewk_view_context_get, ewk_context_form_autofill_profile_add, ewk_context_form_autofill_profile_remove, ewk_context_form_autofill_profile_get
* @passcase				When ewk_context_form_autofill_profile_add & ewk_context_form_autofill_profile_remove is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_form_autofill_profile_add_remove_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* settings = ewk_view_settings_get(objWebkit_EFL_view.webview);

	Eina_Bool result = ewk_settings_form_profile_data_enabled_set(settings, EINA_TRUE);
	if ( result == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_form_profile_data_enabled_set failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Ewk_Autofill_Profile* profile = GetEwkAFillProf();

	if ( profile == NULL )
	{
		FPRINTF("[Line : %d][%s] GetEwkAFillProf failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}


	result = ewk_context_form_autofill_profile_add(ewk_view_context_get(objWebkit_EFL_view.webview), profile);
	EventLoopWait(3.0);
	if (result == EINA_FALSE)
	{
		FPRINTF("[Line : %d][%s] ewk_context_form_autofill_profile_add failed\\n", __LINE__, API_NAMESPACE);
		ewk_autofill_profile_delete(profile);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	result = ewk_context_form_autofill_profile_remove(ewk_view_context_get(objWebkit_EFL_view.webview), TEST_AUTOFILL_PROFILE_ID);
	if (result == EINA_FALSE)
	{
		FPRINTF("[Line : %d][%s] ewk_context_form_autofill_profile_remove failed\\n", __LINE__, API_NAMESPACE);
		ewk_autofill_profile_delete(profile);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	profile = ewk_context_form_autofill_profile_get(ewk_view_context_get(objWebkit_EFL_view.webview), TEST_AUTOFILL_PROFILE_ID);
	if (profile == NULL)
	{
		FPRINTF("[Line : %d][%s] ewk_context_form_autofill_profile_get failed\\n", __LINE__, API_NAMESPACE);
		ewk_autofill_profile_delete(profile);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	ewk_autofill_profile_delete(profile);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: To Get list of all existing profiles
//& type: auto
/**
* @testcase 			ITc_ewk_context_form_autofill_profile_get_all_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			To Get list of all existing profiles
* @scenario				ewk_autofill_profile_new\n
*						ewk_view_settings_get\n
*						ewk_settings_form_profile_data_enabled_set\n
*						ewk_view_context_get\n
*						ewk_context_form_autofill_profile_add\n
*						ewk_context_form_autofill_profile_get_all\n
*						ewk_context_form_autofill_profile_remove\n
*						ewk_autofill_profile_delete
* @apicovered			ewk_view_settings_get, ewk_settings_form_profile_data_enabled_set, ewk_view_context_get, ewk_context_form_autofill_profile_get_all
* @passcase				When ewk_context_form_autofill_profile_get_all is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_form_autofill_profile_get_all_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* settings = ewk_view_settings_get(objWebkit_EFL_view.webview);

	Eina_Bool result = ewk_settings_form_profile_data_enabled_set(settings, EINA_TRUE);
	if (result == EINA_FALSE)
	{
		FPRINTF("[Line : %d][%s] ewk_settings_form_profile_data_enabled_set failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Ewk_Autofill_Profile* profile = GetEwkAFillProf();

	if ( profile == NULL )
	{
		FPRINTF("[Line : %d][%s] GetEwkAFillProf failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Ewk_Context* context = ewk_view_context_get(objWebkit_EFL_view.webview);
	if (context == NULL)
	{
		FPRINTF("[Line : %d][%s] ewk_context_get failed\\n", __LINE__, API_NAMESPACE);
		ewk_autofill_profile_delete(profile);
		Webkit_EFLDestroyWebKitView();
		return 1;

	}

	result = ewk_context_form_autofill_profile_add(context, profile);
	if (result == EINA_FALSE)
	{
		FPRINTF("[Line : %d][%s] ewk_context_form_autofill_profile_add failed\\n", __LINE__, API_NAMESPACE);
		ewk_autofill_profile_delete(profile);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	EventLoopWait(3.0);

	Eina_List* List = ewk_context_form_autofill_profile_get_all(context);
	if (List == NULL)
	{
		FPRINTF("[Line : %d][%s] ewk_context_form_autofill_profile_get_all failed\\n", __LINE__, API_NAMESPACE);
		ewk_autofill_profile_delete(profile);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	result = ewk_context_form_autofill_profile_remove(context, TEST_AUTOFILL_PROFILE_ID);
	if (result == EINA_FALSE)
	{
		FPRINTF("[Line : %d][%s] ewk_context_form_autofill_profile_remove failed\\n", __LINE__, API_NAMESPACE);
		ewk_autofill_profile_delete(profile);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	ewk_autofill_profile_delete(profile);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: Sets the given profile for the given id
//& type: auto
/**
* @testcase 			ITc_ewk_context_form_autofill_profile_set_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Sets the given profile for the given id
* @scenario				ewk_autofill_profile_new\n
*						ewk_view_settings_get\n
*						ewk_settings_form_profile_data_enabled_set\n
*						ewk_view_context_get\n
*						ewk_context_form_autofill_profile_add\n
*						ewk_autofill_profile_data_set\n
*						ewk_context_form_autofill_profile_set\n
*						ewk_autofill_profile_data_get\n
*						ewk_autofill_profile_delete
* @apicovered			ewk_view_settings_get, ewk_settings_form_profile_data_enabled_set, ewk_view_context_get, ewk_autofill_profile_data_set, ewk_context_form_autofill_profile_set, ewk_autofill_profile_data_get
* @passcase				When ewk_context_form_autofill_profile_set is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_form_autofill_profile_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* settings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	Eina_Bool result = ewk_settings_form_profile_data_enabled_set(settings, EINA_TRUE);
	if (result == EINA_FALSE)
	{
		FPRINTF("[Line : %d][%s] ewk_settings_form_profile_data_enabled_set failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Ewk_Autofill_Profile* profile = GetEwkAFillProf();
	if ( profile == NULL )
	{
		FPRINTF("[Line : %d][%s] GetEwkAFillProf failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;

	}

	const char *NEW_COMPANY = "12345";

	ewk_autofill_profile_data_set(profile, EWK_PROFILE_COMPANY, NEW_COMPANY);
	result = ewk_context_form_autofill_profile_set( ewk_view_context_get(objWebkit_EFL_view.webview), TEST_AUTOFILL_PROFILE_ID, profile);
	if (result == EINA_FALSE)
	{
		FPRINTF("[Line : %d][%s] ewk_context_form_autofill_profile_set failed\\n", __LINE__, API_NAMESPACE);
		ewk_autofill_profile_delete(profile);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	const char *CHECK_COMPANY_NAME = ewk_autofill_profile_data_get(profile, EWK_PROFILE_COMPANY);
	if (strcmp(CHECK_COMPANY_NAME, NEW_COMPANY) != 0)
	{
		FPRINTF("[Line : %d][%s] ewk_autofill_profile_data_get failed\\n", __LINE__, API_NAMESPACE);
		ewk_autofill_profile_delete(profile);
		Webkit_EFLDestroyWebKitView();
		return 1;

	}
	ewk_autofill_profile_delete(profile);
	Webkit_EFLDestroyWebKitView();
	return 0;

}

//& purpose: Gets the existing profile for given index
//& type: auto
/**
* @testcase 			ITc_ewk_context_form_autofill_profile_get_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Gets the existing profile for given index
* @scenario				ewk_autofill_profile_new\n
*						ewk_view_settings_get\n
*						ewk_settings_form_profile_data_enabled_set\n
*						ewk_context_form_autofill_profile_get\n
*						ewk_autofill_profile_delete
* @apicovered			ewk_view_settings_get, ewk_settings_form_profile_data_enabled_set, ewk_context_form_autofill_profile_get
* @passcase				When ewk_context_form_autofill_profile_get is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_form_autofill_profile_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* settings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	Eina_Bool result = ewk_settings_form_profile_data_enabled_set(settings, EINA_TRUE);
	if (result == EINA_FALSE)
	{
		FPRINTF("[Line : %d][%s] ewk_settings_form_profile_data_enabled_set failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Ewk_Autofill_Profile* profile = GetEwkAFillProf();
	Ewk_Autofill_Profile* profile2 = ewk_context_form_autofill_profile_get(ewk_view_context_get(objWebkit_EFL_view.webview), TEST_AUTOFILL_PROFILE_ID);
	if (profile == profile2)
	{
		FPRINTF("[Line : %d][%s] ewk_settings_form_profile_data_enabled_set failed\\n", __LINE__, API_NAMESPACE);
		ewk_autofill_profile_delete(profile);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	ewk_autofill_profile_delete(profile);
	ewk_autofill_profile_delete(profile2);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: Deletes all candidate form data from DB
//& type: auto
/**
* @testcase 			ITc_ewk_context_form_candidate_data_delete_all_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Deletes all candidate form data from DB
* @scenario				ewk_view_context_get\n
*						ewk_context_form_candidate_data_delete_all
* @apicovered			ewk_view_context_get, ewk_context_form_candidate_data_delete_all
* @passcase				When ewk_context_form_candidate_data_delete_all is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_form_candidate_data_delete_all_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
	Ewk_Context* ewkContext = ewk_view_context_get(objWebkit_EFL_view.webview);
	if (ewkContext == NULL)
	{
		FPRINTF("[Line : %d][%s] ewk_context_new failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	ewk_context_form_candidate_data_delete_all(ewkContext);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: Deletes whole password data from DB
//& type: auto
/**
* @testcase 			ITc_ewk_context_form_password_data_delete_all_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Deletes whole password data from DB
* @scenario				ewk_view_context_get\n
*						ewk_context_form_password_data_delete_all
* @apicovered			ewk_view_context_get, ewk_context_form_password_data_delete_all
* @passcase				When ewk_context_form_password_data_delete_all is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_form_password_data_delete_all_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
	Ewk_Context* ewkContext = ewk_view_context_get(objWebkit_EFL_view.webview);
	if (ewkContext == NULL)
	{
		FPRINTF("[Line : %d][%s] Unable to create context\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	ewk_context_form_password_data_delete_all(ewkContext);
	Webkit_EFLDestroyWebKitView();
	return 0;
}
/** @} */
/** @} */
