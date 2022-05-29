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
#include "ITs-phonenumber-utils-common.h"

bool g_IsConnected = false;

#define TEST_BLOCKING_RULE_COUNT 8

typedef struct {
	char *number;
	phone_number_blocking_rule_match_type_e match_type;
} phn_blocking_rule_s;

phn_blocking_rule_s g_Blocking_rules[TEST_BLOCKING_RULE_COUNT] = {
	{"+821092381673", PHONE_NUMBER_MATCH_TYPE_EXACTLY},
	{"010-1234-1234", PHONE_NUMBER_MATCH_TYPE_EXACTLY},
	{"01028850863", PHONE_NUMBER_MATCH_TYPE_EXACTLY},
	{"07015001500", PHONE_NUMBER_MATCH_TYPE_EXACTLY},
	{"070", PHONE_NUMBER_MATCH_TYPE_STARTS_WITH},
	{"1588", PHONE_NUMBER_MATCH_TYPE_STARTS_WITH},
	{"0909", PHONE_NUMBER_MATCH_TYPE_ENDS_WITH},
	{"070", PHONE_NUMBER_MATCH_TYPE_INCLUDES},
};


/** @addtogroup itc-phonenumber-utils-blocking-rule
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_phonenumber_utils_blocking_rule_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 		NA
 */
void ITs_phonenumber_utils_blocking_rule_startup(void)
{
	struct stat stBuff;
	g_bPhoneSupported = false;

	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	g_bPhoneSupported  = TCTCheckSystemInfoFeatureSupported(PHONE_FEATURE, API_NAMESPACE);
	int nRet = phone_number_connect();

	if ( nRet != PHONE_NUMBER_ERROR_NONE )
	{
		g_IsConnected = false;
		FPRINTF("[Line : %d][%s] phone_number_connect fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , PhoneNumberUtilsGetError(nRet));
		return;
	}

	g_IsConnected = true;
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Phonenumber_Utils_Blocking_Rule_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
 * @function 		ITs_phonenumber_utils_blocking_rule_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 		NA
 */
void ITs_phonenumber_utils_blocking_rule_cleanup(void)
{
	int nRet = phone_number_disconnect();
	if ( nRet != PHONE_NUMBER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] phone_number_disconnect fail in cleanup error returned : %s \\n", __LINE__, API_NAMESPACE , PhoneNumberUtilsGetError(nRet));
		return;
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Phonenumber_Utils_Blocking_Rule_p\\n", __LINE__, API_NAMESPACE);
#endif

}

/** @addtogroup itc-phonenumber-utils-blocking-rule-testcases
*  @brief 	Integration testcases for module phonenumber-utils-blocking-rule
*  @ingroup 	itc-phonenumber-utils-blocking-rule
*  @{
*/


//& type: auto
//& purpose: This function create & destroy the blocking rules
/**
 * @testcase 				ITc_phone_number_utils_blocking_rule_create_destroy_p
 * @since_tizen				4.0
 * @author				SRID(sp.pradhan)
 * @reviewer				SRID(shobhit.v)
 * @type 				auto
 * @description				Creates and destroy blocking rule
 * @scenario				Creates and destroy blocking rule
 * @apicovered				phone_number_blocking_rule_create, phone_number_blocking_rule_destroy
 * @passcase				if phone_number_blocking_rule_create and phone_number_blocking_rule_destroy returns success
 * @failcase				if phone_number_blocking_rule_create and phone_number_blocking_rule_destroy returns failure
 * @precondition			NA
 * @postcondition			NA
 */

int ITc_phone_number_utils_blocking_rule_create_destroy_p(void)
{
	START_TEST;

	if (g_IsConnected == false)
	{
		return 1;
	}
	int nRet = PHONE_NUMBER_ERROR_NONE;
	phone_number_blocking_rule_h rule = NULL;

	nRet = phone_number_blocking_rule_create(&rule);
	if (g_bPhoneSupported)
        {
                PRINT_RESULT(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number_blocking_rule_create", PhoneNumberUtilsGetError(nRet));
        }
        else
        {
                PRINT_RESULT(PHONE_NUMBER_ERROR_NOT_SUPPORTED, nRet, "phone_number_blocking_rule_create", PhoneNumberUtilsGetError(nRet));
                return 0;
        }

	if (!rule)
	{
		FPRINTF("[Line : %d][%s] phone_number_blocking_rule_create returned NULL\\n", __LINE__, API_NAMESPACE);
                return 1;
	}

	nRet = phone_number_blocking_rule_destroy(rule);
	PRINT_RESULT(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number_blocking_rule_destroy", PhoneNumberUtilsGetError(nRet));

	return 0;
}


//& type: auto
//& purpose: This function set & get the blocking rules
/**
 * @testcase 				ITc_phone_number_utils_blocking_rule_set_get_number_p
 * @since_tizen				4.0
 * @author				SRID(sp.pradhan)
 * @reviewer				SRID(shobhit.v)
 * @type 				auto
 * @description				Sets and gets a number from the blocking rule.
 * @scenario				Sets and gets a number from the blocking rule.
 * @apicovered				phone_number_blocking_rule_create, phone_number_blocking_rule_set_number, phone_number_blocking_rule_get_number
 *					phone_number_blocking_rule_destroy
 * @passcase				if phone_number_blocking_rule_create, phone_number_blocking_rule_set_number, phone_number_blocking_rule_get_number and phone_number_blocking_rule_destroy returns success
 * @failcase				if phone_number_blocking_rule_create, phone_number_blocking_rule_set_number, phone_number_blocking_rule_get_number and phone_number_blocking_rule_destroy returns failure
 * @precondition			NA
 * @postcondition			NA
 */

int ITc_phone_number_utils_blocking_rule_set_get_number_p(void)
{
	START_TEST;

	if (g_IsConnected == false)
	{
		return 1;
	}
	int nRet = PHONE_NUMBER_ERROR_NONE;
	char *number = NULL;
	phone_number_blocking_rule_h rule = NULL;

	nRet = phone_number_blocking_rule_create(&rule);

	if (g_bPhoneSupported)
        {
                PRINT_RESULT(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number__blocking_rule_create", PhoneNumberUtilsGetError(nRet));
        }
        else
        {
                PRINT_RESULT(PHONE_NUMBER_ERROR_NOT_SUPPORTED, nRet, "phone_number_blocking_rule_create", PhoneNumberUtilsGetError(nRet));
                return 0;
        }

	if (!rule)
	{
		FPRINTF("[Line : %d][%s] phone_number_blocking_rule_create returned NULL[%s]\\n", __LINE__, API_NAMESPACE, PhoneNumberUtilsGetError(nRet));
                return 1;
	}

	nRet = phone_number_blocking_rule_set_number(rule, g_Blocking_rules[0].number);
	PRINT_RESULT_CLEANUP(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number_utils_blocking_rule_set_number", PhoneNumberUtilsGetError(nRet), phone_number_blocking_rule_destroy(rule));

	nRet = phone_number_blocking_rule_get_number(rule, &number);
	PRINT_RESULT_CLEANUP(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number_utils_blocking_rule_get_number", PhoneNumberUtilsGetError(nRet), phone_number_blocking_rule_destroy(rule));
	if (0 != strncmp(number, g_Blocking_rules[0].number, strlen(g_Blocking_rules[0].number))) {
		FREE_MEMORY(number);
		FPRINTF("[Line : %d][%s] phone number doesn't match\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	FREE_MEMORY(number);

	nRet = phone_number_blocking_rule_destroy(rule);
	PRINT_RESULT(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number_utils_blocking_rule_destroy", PhoneNumberUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: This function get & set a match_type from the blocking rules
/**
 * @testcase 				ITc_phone_number_utils_blocking_rule_set_get_match_type_p
 * @since_tizen				4.0
 * @author				SRID(sp.pradhan)
 * @reviewer				SRID(shobhit.v)
 * @type 				auto
 * @description				Gets and sets a match type from the blocking rule.
 * @scenario				Gets and sets a match type from the blocking rule.
 * @apicovered				phone_number_blocking_rule_create, phone_number_blocking_rule_set_match_type,
 *					phone_number_blocking_rule_get_match_type, phone_number_blocking_rule_destroy.
 * @passcase				if phone_number_blocking_rule_create, phone_number_blocking_rule_set_match_type, phone_number_blocking_rule_get_match_type and phone_number_blocking_rule_destroy returns success
 * @failcase				if phone_number_blocking_rule_create, phone_number_blocking_rule_set_match_type, phone_number_blocking_rule_get_match_type and phone_number_blocking_rule_destroy returns failure
 * @precondition			NA
 * @postcondition			NA
 */

int ITc_phone_number_utils_blocking_rule_set_get_match_type_p(void)
{
	START_TEST;

	if (g_IsConnected == false)
	{
		return 1;
	}
	int nRet = PHONE_NUMBER_ERROR_NONE;
	phone_number_blocking_rule_match_type_e match_type = -1;
	phone_number_blocking_rule_h rule = NULL;

	nRet = phone_number_blocking_rule_create(&rule);
	if (g_bPhoneSupported)
	{
		PRINT_RESULT(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number_blocking_rule_create", PhoneNumberUtilsGetError(nRet));
	}
	else
	{
		PRINT_RESULT(PHONE_NUMBER_ERROR_NOT_SUPPORTED, nRet, "phone_number_blocking_rule_create", PhoneNumberUtilsGetError(nRet));
		return 0;
	}
	if (!rule)
	{
		FPRINTF("[Line : %d][%s] phone_number_blocking_rule_create returned NULL\\n", __LINE__, API_NAMESPACE);
                return 1;
	}

	nRet = phone_number_blocking_rule_set_match_type(rule, g_Blocking_rules[0].match_type);
	PRINT_RESULT_CLEANUP(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number_utils_blocking_rule_set_match_type", PhoneNumberUtilsGetError(nRet), phone_number_blocking_rule_destroy(rule));

	nRet = phone_number_blocking_rule_get_match_type(rule, &match_type);
	PRINT_RESULT_CLEANUP(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number_utils_blocking_rule_get_match_type", PhoneNumberUtilsGetError(nRet), phone_number_blocking_rule_destroy(rule));
	if (g_Blocking_rules[0].match_type != match_type)
	{
		FPRINTF("[Line : %d][%s] match_type doesn't match after getting\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = phone_number_blocking_rule_destroy(rule);
	PRINT_RESULT(PHONE_NUMBER_ERROR_NONE, nRet, "phone_number_utils_blocking_rule_destroy", PhoneNumberUtilsGetError(nRet));

	return 0;
}


/** @}*/
/** @}*/
