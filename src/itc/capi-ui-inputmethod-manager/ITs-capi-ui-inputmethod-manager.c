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
#include "ITs-capi-ui-inputmethod-manager-common.h"

/** @addtogroup itc-inputmethod-manager
* @ingroup		itc
* @{
*/

//& set: InputmethodManager

/**
 * @function 		ITs_inputmethod_manager_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_inputmethod_manager_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Input_Method_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
 * @function 		ITs_inputmethod_manager_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_inputmethod_manager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Input_Method_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	itc-inputmethod-manager-testcases
* @brief 		Integration testcases for module inputmethod-manager
* @ingroup		itc-inputmethod-manager
* @{
*/

//& purpose: Checks which IME is the current activated IME.
//& type: auto
/**
 * @testcase 				ITc_ime_manager_get_active_ime_p
 * @since_tizen				2.4
 * @author            		SRID(ajay.kr1)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Get the the current activated IME
 * @scenario				Get the the current activated IME
 * @apicovered				ime_manager_get_active_ime
 * @passcase				When ime_manager_get_active_ime is successful
 * @failcase				If target ime_manager_get_active_ime fails
 * @precondition			None
 * @postcondition			None
 */
int ITc_ime_manager_get_active_ime_p(void)
{
	START_TEST;

	char *pszAppid = NULL;

	//Target API
	int nRet = ime_manager_get_active_ime(&pszAppid);
	PRINT_RESULT(IME_MANAGER_ERROR_NONE, nRet, "ime_manager_get_active_ime", InputmethodManagerGetError(nRet));
	if ( pszAppid != NULL )
	{
		FPRINTF("[Line : %d][%s] current activated IME appid = %s\\n", __LINE__, API_NAMESPACE, pszAppid);
	}
	FREE_MEMORY(pszAppid);

	return 0;
}

//& purpose: Checks if the specific IME is enabled or disabled in the system keyboard setting.
//& type: auto
/**
 * @testcase 				ITc_ime_manager_is_ime_enabled_p
 * @since_tizen				2.4
 * @author            		SRID(ajay.kr1)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Checks if the specific IME is enabled or disabled in the system keyboard setting
 * @scenario				Checks the status specific IME
 * @apicovered				ime_manager_is_ime_enabled
 * @passcase				When ime_manager_is_ime_enabled is successful
 * @failcase				If target ime_manager_is_ime_enabled fails
 * @precondition			None
 * @postcondition			None
 */
int ITc_ime_manager_is_ime_enabled_p(void)
{
	START_TEST;

	bool bEnabled;
	char *pszAppid = NULL;

	//Target API
	int nRet = ime_manager_get_active_ime(&pszAppid);
	PRINT_RESULT(IME_MANAGER_ERROR_NONE, nRet, "ime_manager_get_active_ime", InputmethodManagerGetError(nRet));

	if ( pszAppid != NULL )
	{
		//Target API
		nRet = ime_manager_is_ime_enabled(pszAppid, &bEnabled);
		FREE_MEMORY(pszAppid);
		PRINT_RESULT(IME_MANAGER_ERROR_NONE, nRet, "ime_manager_is_ime_enabled", InputmethodManagerGetError(nRet));
	}

	return 0;
}

//& purpose: Gets the number of IMEs which are enabled
//& type: auto
/**
 * @testcase 				ITc_ime_manager_get_enabled_ime_count_p
 * @since_tizen			3.0
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(a.pandia1)
 * @type 						auto
 * @description			Gets the number of IMEs which are enabled
 * @scenario				Gets the number of IMEs which are enabled
 * @apicovered			ime_manager_get_enabled_ime_count
 * @passcase				When ime_manager_get_enabled_ime_count is successful
 * @failcase				If target ime_manager_get_enabled_ime_count fails
 * @precondition			None
 * @postcondition		None
 */
int ITc_ime_manager_get_enabled_ime_count_p(void)
{
	START_TEST;

	bool bEnabled;
	char *pszAppid = NULL;
	int count = -1;

	int nRet = ime_manager_get_active_ime(&pszAppid);
	PRINT_RESULT(IME_MANAGER_ERROR_NONE, nRet, "ime_manager_get_active_ime", InputmethodManagerGetError(nRet));

	if ( pszAppid != NULL )
	{
		nRet = ime_manager_is_ime_enabled(pszAppid, &bEnabled);
		FREE_MEMORY(pszAppid);
		PRINT_RESULT(IME_MANAGER_ERROR_NONE, nRet, "ime_manager_is_ime_enabled", InputmethodManagerGetError(nRet));
	
		//Target API
		count = ime_manager_get_enabled_ime_count();
		nRet = get_last_result();
		PRINT_RESULT(IME_MANAGER_ERROR_NONE, nRet, "ime_manager_get_enabled_ime_count", InputmethodManagerGetError(nRet));
		if(count < 0)
		{
			FPRINTF("[Line : %d][%s] ime_manager_get_enabled_ime_count returns invalid value\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	
	}
	else
	{
		FPRINTF("[Line : %d][%s]pszAppid is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose Pre-launch the IME
//& type: auto
/**
* @testcase			ITs_ime_manager_prelaunch_ime
* @since_tizen			5.0
* @author			SRID(samuel.peter)
* @reviewer			SRID(priya.kohli)
* @type				auto
* @description			Requests to pre-launch the IME
* @scenario			Requests to pre-launch the IME
* @apicovered			ime_manager_prelaunch_ime
* @passcase			pre-launch of IME is successful and api returns IME_MANAGER_ERROR_NONE
* @failcase			pre-launch of IME is unsuccessful.
* @precondition			NA
* @postcondition		NA
*/
int ITc_ime_manager_prelaunch_ime(void)
{
	START_TEST;

	int nRet = ime_manager_prelaunch_ime();
	PRINT_RESULT(IME_MANAGER_ERROR_NONE, nRet, "ime_manager_prelaunch_ime", InputmethodManagerGetError(nRet));

	return 0;
}
/** @} */ //end of inputmethod-manager
/** @} */ //end of inputmethod-manager-testcases
