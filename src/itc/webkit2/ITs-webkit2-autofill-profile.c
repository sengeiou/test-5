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
void ITs_webkit_efl_autofill_startup(void)
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
void ITs_webkit_efl_autofill_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& purpose: To Set & Get autofill profile data
//& type: auto
/**
* @testcase 			ITc_ewk_autofill_profile_data_set_get_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			To Set & Get autofill profile data
* @scenario				ewk_autofill_profile_new\n
*						ewk_autofill_profile_data_set\n
*						ewk_autofill_profile_data_get\n
*						ewk_autofill_profile_delete
* @apicovered			ewk_autofill_profile_new, ewk_autofill_profile_data_set, ewk_autofill_profile_data_get
* @passcase				When ewk_autofill_profile_data_set & ewk_autofill_profile_data_get is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_autofill_profile_data_set_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
	Ewk_Autofill_Profile* profileData = ewk_autofill_profile_new();
	const char* getData;
	if ( profileData == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_autofill_profile_new failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	ewk_autofill_profile_data_set(profileData, 1, "value");
	getData = ewk_autofill_profile_data_get(profileData, 1);
	if ( getData == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_autofill_profile_data_get failed\\n", __LINE__, API_NAMESPACE);
		ewk_autofill_profile_delete(profileData);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( strcmp(getData, "value") != 0 )
	{
		FPRINTF("[Line : %d][%s] got wrong value: \"%s\", expected \"value\" failed\\n", __LINE__, API_NAMESPACE, getData);
		ewk_autofill_profile_delete(profileData);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	ewk_autofill_profile_delete(profileData);
	Webkit_EFLDestroyWebKitView();
	return 0;

}

//& purpose: To Create & Delete autofill profile
//& type: auto
/**
* @testcase 			ITc_ewk_autofill_profile_new_delete_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			To Create & Delete autofill profile
* @scenario				ewk_autofill_profile_new\n
*						ewk_autofill_profile_delete
* @apicovered			ewk_autofill_profile_new, ewk_autofill_profile_delete
* @passcase				When ewk_autofill_profile_new & ewk_autofill_profile_delete is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_autofill_profile_new_delete_p(void)
{
	START_TEST;
	Ewk_Autofill_Profile* profileData = ewk_autofill_profile_new();
	if ( profileData == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_autofill_profile_new failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	ewk_autofill_profile_delete(profileData);
	return 0;
}

//& purpose: To Get autofill profile id
//& type: auto
/**
* @testcase 			ITc_ewk_autofill_profile_id_get_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			To Get autofill profile id
* @scenario				ewk_autofill_profile_new\n
*						ewk_autofill_profile_id_get\n
*						ewk_autofill_profile_delete
* @apicovered			ewk_autofill_profile_new, ewk_autofill_profile_id_get
* @passcase				When ewk_autofill_profile_id_get is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_autofill_profile_id_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
	Ewk_Autofill_Profile* profile = GetEwkAFillProf();
	unsigned int proID;

	proID = ewk_autofill_profile_id_get(profile);
	if ( proID != TEST_AUTOFILL_PROFILE_ID )
	{
		FPRINTF("[Line : %d][%s] ewk_autofill_profile_id_get failed\\n", __LINE__, API_NAMESPACE);
		ewk_autofill_profile_delete(profile);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	ewk_autofill_profile_delete(profile);
	Webkit_EFLDestroyWebKitView();
	return 0;
}
/** @} */
/** @} */
