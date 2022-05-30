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
#include "ITs-base-utils-common.h"

static char *pszRules = "&9 < a, A < b, B < c, C; ch, cH, Ch, CH < d, D, e, E";
static i18n_ucollator_h g_hUcollator = NULL;

/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/

//& set: BaseUtilsUcollator

/**
* @function 		ITs_base_utils_ucollator_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_base_utils_ucollator_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = i18n_ucollator_create("en_US", &g_hUcollator );
	if(nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] API i18n_ucollator_create failed in startup , returned error = %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
	}
	
	if(g_hUcollator == NULL)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] API i18n_ucollator_create returned handle = NULL\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
	}
	
	g_bBaseUtilsInitFlag = true;
	return;
}

/**
* @function 		IITs_base_utils_ucollator_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_ucollator_cleanup(void)
{
	g_bBaseUtilsInitFlag = false;

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
	if(g_hUcollator)
	{
		int nRet = i18n_ucollator_destroy(g_hUcollator);
		if(nRet != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] API i18n_ucollator_destroy failed in cleanup , returned error = %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
		}
		g_hUcollator = NULL;
	}
	
	return;
}


//& type: auto
//& purpose:  Creates a i18n_ucollator_h for comparing strings And Destroy given i18n_ucollator_h
/**
* @testcase				ITc_i18n_ucollator_create_destroy_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates a i18n_ucollator_h for comparing strings.\n
* 						Destroy given i18n_ucollator_h. 	
* @apitarget			i18n_ucollator_create, i18n_ucollator_destroy
* @apicovered			i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_create, i18n_ucollator_destroy are successful
* @failcase				If target i18n_ucollator_create or i18n_ucollator_destroy fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucollator_create_destroy_p(void)
{
	START_TEST_PRINT;

	i18n_ucollator_h uCollator = NULL;
	int nRetVal = i18n_ucollator_create(g_pszDefaultLocale, &uCollator);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_create", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_ucollator_destroy(uCollator);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Compares two strings with collator using the options already specified.
/**
* @testcase				ITc_i18n_ucollator_str_collator_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compares two strings using the options already specified.
* @apitarget			i18n_ucollator_str_collator
* @apicovered			i18n_ucollator_str_collator, i18n_ucollator_create, i18n_ustring_from_UTF8, i18n_ustring_get_length, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_str_collator is successful
* @failcase				If target i18n_ucollator_str_collator fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucollator_str_collator_p(void)
{
	START_TEST_PRINT;

	char *szSource = "Tizen";
	char *szTarget = "Bada";
	i18n_ucollator_h uCollator = NULL;

	int nRetVal = i18n_ucollator_create(g_pszDefaultLocale, &uCollator);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(uCollator, "i18n_ucollator_create");

	int nSourceLength = 0;
	int nTargetLength = 0;
	i18n_uchar ucharSource[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar ucharTarget[I18N_UCHAR_CAPACITY] = {0,};
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;

	i18n_uchar *pRet = i18n_ustring_from_UTF8(ucharSource, I18N_UCHAR_CAPACITY, NULL, (const char*)szSource, -1, &ErrorCode);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_from_UTF8", BaseUtilsGetError(ErrorCode), i18n_ucollator_destroy(uCollator));
	nSourceLength = i18n_ustring_get_length(ucharSource);
	if ( pRet == NULL || nSourceLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_from_UTF8 pre-requisite API failed\\n", __LINE__, API_NAMESPACE);
		nRetVal = i18n_ucollator_destroy(uCollator);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_destroy", BaseUtilsGetError(nRetVal));
		return 1;
	}

	pRet = i18n_ustring_from_UTF8(ucharTarget, I18N_UCHAR_CAPACITY, NULL,  (const char*)szTarget, -1, &ErrorCode);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_from_UTF8", BaseUtilsGetError(ErrorCode), i18n_ucollator_destroy(uCollator));
	nTargetLength = i18n_ustring_get_length(ucharTarget);
	if ( pRet == NULL || nTargetLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_from_UTF8 pre-requisite API failed\\n", __LINE__, API_NAMESPACE);
		nRetVal = i18n_ucollator_destroy(uCollator);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_destroy", BaseUtilsGetError(nRetVal));
		return 1;
	}
	i18n_ucollator_result_e collatorResult;
	nRetVal = i18n_ucollator_str_collator(uCollator, ucharSource, nSourceLength, ucharTarget, nTargetLength, &collatorResult);
	if ( nRetVal == I18N_ERROR_NONE && (strcmp(UcollatorResult(collatorResult), UNKNOWN_RESULT_VALUE) != 0) )
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_str_collator passed with Result Value = %s\\n", __LINE__, API_NAMESPACE, UcollatorResult(collatorResult));
	}
	else
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_str_collator failed as uCollator Compare Result Value = %s , error returned = %s\\n", __LINE__, API_NAMESPACE, UcollatorResult(collatorResult), BaseUtilsGetError(nRetVal));
		nRetVal = i18n_ucollator_destroy(uCollator);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_destroy", BaseUtilsGetError(nRetVal));
		return 1;
	}

	nRetVal = i18n_ucollator_destroy(uCollator);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Compares two strings for equality
/**
* @testcase				ITc_i18n_ucollator_equal_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compares two strings for equality
* @apitarget			i18n_ucollator_equal
* @apicovered			i18n_ucollator_create, i18n_ucollator_equal, i18n_ustring_from_UTF8, i18n_ustring_get_length, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_equal is successful
* @failcase				If target i18n_ucollator_equal fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucollator_equal_p(void)
{
	START_TEST_PRINT;

	char *szSource = "Tizen";
	char *szTarget = "Bada";
	i18n_ucollator_h uCollator = NULL;
	int nRetVal = i18n_ucollator_create(g_pszDefaultLocale, &uCollator);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(uCollator, "i18n_ucollator_create");

	int nSourceLength = 0;
	int nTargetLength = 0;
	i18n_uchar ucharSource[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar ucharTarget[I18N_UCHAR_CAPACITY] = {0,};
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;
	i18n_uchar *pRet = i18n_ustring_from_UTF8(ucharSource, I18N_UCHAR_CAPACITY, NULL, (const char*)szSource, -1, &ErrorCode );
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_from_UTF8", BaseUtilsGetError(ErrorCode), i18n_ucollator_destroy(uCollator));
	nSourceLength = i18n_ustring_get_length(ucharSource);
	if ( pRet == NULL || nSourceLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_from_UTF8 pre-requisite API failed\\n", __LINE__, API_NAMESPACE);
		nRetVal = i18n_ucollator_destroy(uCollator);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_destroy", BaseUtilsGetError(nRetVal));
		return 1;
	}

	pRet = i18n_ustring_from_UTF8(ucharTarget, I18N_UCHAR_CAPACITY, NULL,  (const char*)szTarget, -1, &ErrorCode);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_from_UTF8", BaseUtilsGetError(ErrorCode), i18n_ucollator_destroy(uCollator));
	nTargetLength = i18n_ustring_get_length(ucharTarget);
	if ( pRet == NULL || nTargetLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_from_UTF8 pre-requisite API failed\\n", __LINE__, API_NAMESPACE);
		nRetVal = i18n_ucollator_destroy(uCollator);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_destroy", BaseUtilsGetError(nRetVal));
		return 1;
	}
	i18n_ubool bEqualityResult = true;
	nRetVal = i18n_ucollator_equal(uCollator, ucharSource, nSourceLength, ucharTarget, nTargetLength, &bEqualityResult);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_equal", BaseUtilsGetError(nRetVal), i18n_ucollator_destroy(uCollator));
	if(bEqualityResult == true)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_equal API failed, bool value returned = %d\\n", __LINE__, API_NAMESPACE, bEqualityResult);
		nRetVal = i18n_ucollator_destroy(uCollator);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_destroy", BaseUtilsGetError(nRetVal));
		return 1;
	}

	nRetVal = i18n_ucollator_destroy(uCollator);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Compares two strings for equality
/**
* @testcase				ITc_i18n_ucollator_set_strength_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compares two strings for equality
* @apitarget			i18n_ucollator_set_strength
* @apicovered			i18n_ucollator_set_strength, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_set_strength is successful
* @failcase				If target i18n_ucollator_set_strength fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucollator_set_strength_p(void)
{
	START_TEST_PRINT;

	i18n_ucollator_h uCollator = NULL;
	int nRetVal = i18n_ucollator_create(g_pszDefaultLocale, &uCollator);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(uCollator, "i18n_ucollator_create");
	
	i18n_ucollator_strength_e eCollatorStrength[] = {I18N_UCOLLATOR_DEFAULT,
		I18N_UCOLLATOR_PRIMARY,
		I18N_UCOLLATOR_SECONDARY,
		I18N_UCOLLATOR_TERTIARY,
		//I18N_UCOLLATOR_DEFAULT_STRENGTH,
		I18N_UCOLLATOR_QUATERNARY,
		I18N_UCOLLATOR_IDENTICAL};

	int nEnumSize = sizeof(eCollatorStrength) / sizeof(eCollatorStrength[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		FPRINTF("[Line : %d][%s] Executing i18n_ucollator_set_strength with Strength Value = %s ,\\n", __LINE__, API_NAMESPACE, UcollatorStrengthValues(eCollatorStrength[nEnumCounter]));
		nRetVal = i18n_ucollator_set_strength(uCollator, eCollatorStrength[nEnumCounter]);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_set_strength", BaseUtilsGetError(nRetVal), i18n_ucollator_destroy(uCollator));
	}

	nRetVal = i18n_ucollator_destroy(uCollator);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Compares two strings for equality
/**
* @testcase				ITc_i18n_ucollator_set_attribute_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compares two strings for equality
* @apitarget			i18n_ucollator_set_attribute
* @apicovered			i18n_ucollator_set_attribute, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_set_attribute is successful
* @failcase				If target i18n_ucollator_set_attribute fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucollator_set_attribute_p(void)
{
	START_TEST_PRINT;

	i18n_ucollator_h uCollator = NULL;
	int nRetVal = i18n_ucollator_create(g_pszDefaultLocale, &uCollator);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(uCollator, "i18n_ucollator_create");

	i18n_ucollator_strength_e eCollatorAttributes[] = {I18N_UCOLLATOR_FRENCH_COLLATION,
		I18N_UCOLLATOR_ALTERNATE_HANDLING,
		I18N_UCOLLATOR_CASE_FIRST,
		I18N_UCOLLATOR_CASE_LEVEL,
		I18N_UCOLLATOR_NORMALIZATION_MODE,
		//I18N_UCOLLATOR_DECOMPOSITION_MODE,
		I18N_UCOLLATOR_STRENGTH,
		I18N_UCOLLATOR_NUMERIC_COLLATION};
	//I18N_UCOLLATOR_ATTRIBUTE_COUNT};

	int nEnumSize = sizeof(eCollatorAttributes) / sizeof(eCollatorAttributes[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		FPRINTF("[Line : %d][%s] Executing i18n_ucollator_set_attribute with Attribute Value = %s ,\\n", __LINE__, API_NAMESPACE, UcollatorAttributes(eCollatorAttributes[nEnumCounter]));
		nRetVal = i18n_ucollator_set_attribute(uCollator, eCollatorAttributes[nEnumCounter], I18N_UCOLLATOR_DEFAULT);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_set_attribute", BaseUtilsGetError(nRetVal), i18n_ucollator_destroy(uCollator));
	}
	nRetVal = i18n_ucollator_destroy(uCollator);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}


//& type: auto
//& purpose: Create a ucollator instance according to the rules supplied
/**
* @testcase				ITc_i18n_ucollator_create_rules_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Create a ucollator instance according to the rules supplied
* @apitarget			i18n_ucollator_create_rules
* @apicovered			i18n_ucollator_create_rules, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_create_rules is successful
* @failcase				If target i18n_ucollator_create_rules fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucollator_create_rules_p(void)
{
	START_TEST_PRINT;

	i18n_ucollator_h uCollator = NULL;
	i18n_uparse_error_s stParseError;
	i18n_uchar szRules[128];

	i18n_ustring_copy_ua(szRules, pszRules);

	i18n_ucollator_attribute_value_e eCollatorAttribVal[] = {I18N_UCOLLATOR_DEFAULT,
		I18N_UCOLLATOR_OFF,
		I18N_UCOLLATOR_ON};

	i18n_ucollator_strength_e eCollatorStrength[] = {I18N_UCOLLATOR_DEFAULT,
		I18N_UCOLLATOR_PRIMARY,
		I18N_UCOLLATOR_SECONDARY,
		I18N_UCOLLATOR_TERTIARY,
		I18N_UCOLLATOR_DEFAULT_STRENGTH,
		I18N_UCOLLATOR_QUATERNARY,
		I18N_UCOLLATOR_IDENTICAL};

	int nEnumSizeAttrib = sizeof(eCollatorAttribVal) / sizeof(eCollatorAttribVal[0]);
	int nEnumSize = sizeof(eCollatorStrength) / sizeof(eCollatorStrength[0]);
	int nEnumCounter1 = 0;
	int nEnumCounter2 = 0;

	for ( nEnumCounter1 = 0; nEnumCounter1 < nEnumSizeAttrib; nEnumCounter1++ )
	{
		for ( nEnumCounter2 = 0; nEnumCounter2 < nEnumSize; nEnumCounter2++ )
		{
			FPRINTF("[Line : %d][%s] Executing i18n_ucollator_create_rules with Strength Value = %s ,\\n", __LINE__, API_NAMESPACE, UcollatorStrengthValues(eCollatorStrength[nEnumCounter2]));
			int nRetVal = i18n_ucollator_create_rules(szRules, -1, eCollatorAttribVal[nEnumCounter1],  eCollatorStrength[nEnumCounter2],
										&stParseError, &uCollator);
			PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_create_rules", BaseUtilsGetError(nRetVal));
			CHECK_HANDLE(uCollator, "i18n_ucollator_create_rules");
			
			nRetVal = i18n_ucollator_destroy(uCollator);
			PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucollator_destroy", BaseUtilsGetError(nRetVal));
		}
	}
	
	return 0;
}

//& type: auto
//& purpose: Gets a set containing the expansions defined by the collator
/**
* @testcase				ITc_i18n_ucollator_get_contractions_and_expansions_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets a set containing the expansions defined by the collator
* @apitarget			i18n_ucollator_get_contractions_and_expansions
* @apicovered			i18n_ucollator_get_contractions_and_expansions, i18n_ucollator_create, i18n_ucollator_destroy, i18n_uset_create_empty, i18n_uset_destroy
* @passcase				When i18n_ucollator_get_contractions_and_expansions is successful
* @failcase				If target i18n_ucollator_get_contractions_and_expansions fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_contractions_and_expansions_p(void)
{
	START_TEST;

	i18n_uset_h hContractions = NULL;
	i18n_uset_h hExpansions = NULL;

	int nRet = i18n_uset_create_empty(&hContractions);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uset_create_empty", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hContractions, "i18n_uset_create_empty");

	nRet = i18n_uset_create_empty(&hExpansions);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_uset_create_empty", BaseUtilsGetError(nRet), i18n_uset_destroy(hContractions));
	CHECK_HANDLE_CLEANUP(hExpansions, "i18n_uset_create_empty", i18n_uset_destroy(hContractions));

	nRet = i18n_ucollator_get_contractions_and_expansions(g_hUcollator, true, hContractions, hExpansions);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_contractions_and_expansions", BaseUtilsGetError(nRet), i18n_uset_destroy(hContractions);i18n_uset_destroy(hExpansions));

	nRet = i18n_uset_destroy(hContractions);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uset_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_uset_destroy(hExpansions);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uset_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Compares two strings in UTF-8
/**
* @testcase				ITc_i18n_ucollator_str_collator_utf8_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Compares two strings in UTF-8
* @apitarget			i18n_ucollator_str_collator_utf8
* @apicovered			i18n_ucollator_str_collator_utf8, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_str_collator_utf8 is successful
* @failcase				If target i18n_ucollator_str_collator_utf8 fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_str_collator_utf8_p(void)
{
	START_TEST;

	const char *pszStr1 = "First test string";
	const char *pszStr2 = "Second test string";
	i18n_ucollator_result_e eResult;

	int nRet = i18n_ucollator_str_collator_utf8(g_hUcollator, pszStr1, strlen(pszStr1), pszStr2, strlen(pszStr2), &eResult);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_str_collator_utf8", BaseUtilsGetError(nRet));

	if(eResult != I18N_UCOLLATOR_LESS)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_str_collator_utf8 failed , string comparison not correct \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = i18n_ucollator_str_collator_utf8(g_hUcollator, pszStr1, strlen(pszStr1), pszStr1, strlen(pszStr1), &eResult);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_str_collator_utf8", BaseUtilsGetError(nRet));

	if(eResult != I18N_UCOLLATOR_EQUAL)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_str_collator_utf8 failed , string comparison not correct \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines if one string is greater than another
/**
* @testcase				ITc_i18n_ucollator_greater_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Determines if one string is greater than another
* @apitarget			i18n_ucollator_greater
* @apicovered			i18n_ucollator_greater, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_greater is successful
* @failcase				If target i18n_ucollator_greater fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_greater_p(void)
{
	START_TEST;

	const char *pszStr1 = "First test string";
	const char *pszStr2 = "Second test string";
	i18n_ubool bIsGreater;

	int nRet = i18n_ucollator_greater(g_hUcollator, pszStr1, strlen(pszStr1), pszStr2, strlen(pszStr2), &bIsGreater);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_greater", BaseUtilsGetError(nRet));

	if(bIsGreater != true)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_greater failed , string comparison not correct \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = i18n_ucollator_greater(g_hUcollator, pszStr2, strlen(pszStr2), pszStr1, strlen(pszStr1), &bIsGreater);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_greater", BaseUtilsGetError(nRet));

	if(bIsGreater != false)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_greater failed , string comparison not correct \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = i18n_ucollator_greater(g_hUcollator, pszStr1, strlen(pszStr1), pszStr1, strlen(pszStr1), &bIsGreater);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_greater", BaseUtilsGetError(nRet));

	if(bIsGreater != false)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_greater failed , string comparison not correct \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines if one string is greater than or equal to another
/**
* @testcase				ITc_i18n_ucollator_greater_or_equal_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Determines if one string is greater than or equal to another
* @apitarget			i18n_ucollator_greater_or_equal
* @apicovered			i18n_ucollator_greater_or_equal, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_greater_or_equal is successful
* @failcase				If target i18n_ucollator_greater_or_equal fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_greater_or_equal_p(void)
{
	START_TEST;

	const char *pszStr1 = "First test string";
	const char *pszStr2 = "Second test string";
	i18n_ubool bIsGreaterEqual;

	int nRet = i18n_ucollator_greater_or_equal(g_hUcollator, pszStr1, strlen(pszStr1), pszStr2, strlen(pszStr2), &bIsGreaterEqual);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_greater_or_equal", BaseUtilsGetError(nRet));

	if(bIsGreaterEqual != true)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_greater_or_equal failed , string comparison not correct \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = i18n_ucollator_greater_or_equal(g_hUcollator, pszStr2, strlen(pszStr2), pszStr1, strlen(pszStr1), &bIsGreaterEqual);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_greater_or_equal", BaseUtilsGetError(nRet));

	if(bIsGreaterEqual != false)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_greater_or_equal failed , string comparison not correct \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = i18n_ucollator_greater_or_equal(g_hUcollator, pszStr1, strlen(pszStr1), pszStr1, strlen(pszStr1), &bIsGreaterEqual);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_greater_or_equal", BaseUtilsGetError(nRet));

	if(bIsGreaterEqual != true)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_greater_or_equal failed , string comparison not correct \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Compares two UTF-8 encoded strings in iterator
/**
* @testcase				ITc_i18n_ucollator_str_collator_iter_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Compares two UTF-8 encoded strings in iterator
* @apitarget			i18n_ucollator_str_collator_iter
* @apicovered			i18n_ucollator_str_collator_iter, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_str_collator_iter is successful
* @failcase				If target i18n_ucollator_str_collator_iter fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_str_collator_iter_p(void)
{
	START_TEST;

	const char *pszStr1 = "First test string";
	const char *pszStr2 = "Second test string";
	i18n_uchar_iter_h hSrcIter = NULL;
	i18n_uchar_iter_h hTrgtIter = NULL;
	i18n_ucollator_result_e eResult;

	int nRet = i18n_uchar_iter_create(&hSrcIter);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uchar_iter_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hSrcIter, "i18n_uchar_iter_create");

	nRet = i18n_uchar_iter_create(&hTrgtIter);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_uchar_iter_create", BaseUtilsGetError(nRet), i18n_uchar_iter_destroy(hSrcIter));
	CHECK_HANDLE_CLEANUP(hTrgtIter, "i18n_uchar_iter_create", i18n_uchar_iter_destroy(hSrcIter));

	nRet = i18n_uchar_iter_set_utf8(hSrcIter, pszStr1, strlen(pszStr1));
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_uchar_iter_set_utf8", BaseUtilsGetError(nRet), i18n_uchar_iter_destroy(hSrcIter);i18n_uchar_iter_destroy(hTrgtIter));

	nRet = i18n_uchar_iter_set_utf8(hTrgtIter, pszStr2, strlen(pszStr2));
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_uchar_iter_set_utf8", BaseUtilsGetError(nRet), i18n_uchar_iter_destroy(hSrcIter);i18n_uchar_iter_destroy(hTrgtIter));

	nRet = i18n_ucollator_str_collator_iter(g_hUcollator, hSrcIter, hTrgtIter, &eResult);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucollator_str_collator_iter", BaseUtilsGetError(nRet), i18n_uchar_iter_destroy(hSrcIter);i18n_uchar_iter_destroy(hTrgtIter));

	if(eResult != I18N_UCOLLATOR_LESS)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_str_collator_iter failed , string comparison not correct \\n", __LINE__, API_NAMESPACE);
		i18n_uchar_iter_destroy(hSrcIter);
		i18n_uchar_iter_destroy(hTrgtIter);
		return 1;
	}

	nRet = i18n_uchar_iter_destroy(hSrcIter);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uchar_iter_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_uchar_iter_destroy(hTrgtIter);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uchar_iter_destroy", BaseUtilsGetError(nRet));

	return 0;
}


//& type: auto
//& purpose: Gets the collation strength
/**
* @testcase				ITc_i18n_ucollator_get_strength_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets the collation strength
* @apitarget			i18n_ucollator_get_strength
* @apicovered			i18n_ucollator_get_strength, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_get_strength is successful
* @failcase				If target i18n_ucollator_get_strength fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_strength_p(void)
{
	START_TEST;

	i18n_ucollator_strength_e eStrength;

	int nRet = i18n_ucollator_get_strength(g_hUcollator, &eStrength);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_strength", BaseUtilsGetError(nRet));

	if(eStrength != I18N_UCOLLATOR_PRIMARY && eStrength != I18N_UCOLLATOR_SECONDARY && eStrength != I18N_UCOLLATOR_TERTIARY
		&& eStrength != I18N_UCOLLATOR_QUATERNARY && eStrength != I18N_UCOLLATOR_IDENTICAL)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_get_strength failed , invalid strength \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Retrieves the reordering codes for the collator
/**
* @testcase				ITc_i18n_ucollator_get_reorder_codes_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Retrieves the reordering codes for the collator
* @apitarget			i18n_ucollator_get_reorder_codes
* @apicovered			i18n_ucollator_get_reorder_codes, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_get_reorder_codes is successful
* @failcase				If target i18n_ucollator_get_reorder_codes fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_reorder_codes_p(void)
{
	START_TEST;

	int32_t nDestSize = 64;
	int32_t nDest[nDestSize];
	int32_t nCodes;

	int nRet = i18n_ucollator_get_reorder_codes(g_hUcollator, nDestSize, nDest, &nCodes);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_reorder_codes", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Sets the reordering codes for the collator
/**
* @testcase				ITc_i18n_ucollator_set_reorder_codes_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Sets the reordering codes for the collator
* @apitarget			i18n_ucollator_set_reorder_codes
* @apicovered			i18n_ucollator_set_reorder_codes, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_set_reorder_codes is successful
* @failcase				If target i18n_ucollator_set_reorder_codes fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_set_reorder_codes_p(void)
{
	START_TEST;

	int32_t nRecorderSize = 3;
	int32_t nRecorderCodes[] = {I18N_UCOLLATOR_REORDER_CODE_SYMBOL, I18N_UCOLLATOR_REORDER_CODE_CURRENCY, I18N_UCOLLATOR_REORDER_CODE_DIGIT};

	int nRet = i18n_ucollator_set_reorder_codes(g_hUcollator, nRecorderCodes, nRecorderSize);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_set_reorder_codes", BaseUtilsGetError(nRet));

	return 0;
}


//& type: auto
//& purpose: Gets the display name for collator handle
/**
* @testcase				ITc_i18n_ucollator_get_display_name_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets the display name for collator handle
* @apitarget			i18n_ucollator_get_display_name
* @apicovered			i18n_ucollator_get_display_name
* @passcase				When i18n_ucollator_get_display_name is successful
* @failcase				If target i18n_ucollator_get_display_name fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_ucollator_get_display_name_p(void)
{
	START_TEST_PRINT;

	int32_t nDestSize = 64;
	int32_t nDispSize;
	i18n_uchar szDispName[nDestSize];
	char *pszObjLocale = "en_US";
	char *pszDispLocale = "en_US";

	int nRet = i18n_ucollator_get_display_name(pszObjLocale, pszDispLocale, nDestSize, szDispName, &nDispSize);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_display_name", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets locale for which collation rules are available
/**
* @testcase				ITc_i18n_ucollator_get_available_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets locale for which collation rules are available
* @apitarget			i18n_ucollator_get_available
* @apicovered			i18n_ucollator_get_available
* @passcase				When i18n_ucollator_get_available is successful
* @failcase				If target i18n_ucollator_get_available fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_ucollator_get_available_p(void)
{
	START_TEST_PRINT;

	const char *pszLocale = NULL;
	int32_t nLocaleIndex = 0;

	int nRet = i18n_ucollator_get_available(nLocaleIndex, &pszLocale);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_available", BaseUtilsGetError(nRet));
	CHECK_HANDLE(pszLocale, "i18n_ucollator_get_available");
	
	return 0;
}

//& type: auto
//& purpose: Determines count of locales having collation rules
/**
* @testcase				ITc_i18n_ucollator_count_available_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Determines count of locales having collation rules
* @apitarget			i18n_ucollator_count_available
* @apicovered			i18n_ucollator_count_available
* @passcase				When i18n_ucollator_count_available is successful
* @failcase				If target i18n_ucollator_count_available fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_ucollator_count_available_p(void)
{
	START_TEST_PRINT;

	int32_t nAvailable;

	int nRet = i18n_ucollator_count_available(&nAvailable);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_count_available", BaseUtilsGetError(nRet));
	
	return 0;
}


//& type: auto
//& purpose: Creates a string enumerator of all locales
/**
* @testcase				ITc_i18n_ucollator_create_available_locales_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Creates a string enumerator of all locales
* @apitarget			i18n_ucollator_create_available_locales
* @apicovered			i18n_ucollator_create_available_locales
* @passcase				When i18n_ucollator_create_available_locales is successful
* @failcase				If target i18n_ucollator_create_available_locales fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_ucollator_create_available_locales_p(void)
{
	START_TEST_PRINT;

	i18n_uenumeration_h hLocales = NULL;

	int nRet = i18n_ucollator_create_available_locales(&hLocales);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_create_available_locales", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hLocales, "i18n_ucollator_create_available_locales");
	
	nRet =  i18n_uenumeration_destroy(hLocales);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uenumeration_destroy", BaseUtilsGetError(nRet));
	
	return 0;
}


//& type: auto
//& purpose: Creates a string enumerator of all possible keywords
/**
* @testcase				ITc_i18n_ucollator_get_keywords_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Creates a string enumerator of all possible keywords
* @apitarget			i18n_ucollator_get_keywords
* @apicovered			i18n_ucollator_get_keywords
* @passcase				When i18n_ucollator_get_keywords is successful
* @failcase				If target i18n_ucollator_get_keywords fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_ucollator_get_keywords_p(void)
{
	START_TEST_PRINT;

	i18n_uenumeration_h hKeywords = NULL;

	int nRet = i18n_ucollator_get_keywords(&hKeywords);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_keywords", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hKeywords, "i18n_ucollator_get_keywords");
	
	nRet =  i18n_uenumeration_destroy(hKeywords);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uenumeration_destroy", BaseUtilsGetError(nRet));
	
	return 0;
}


//& type: auto
//& purpose: Creates a string enumeration of all values for given keyword
/**
* @testcase				ITc_i18n_ucollator_get_keyword_values_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Creates a string enumeration of all values for given keyword
* @apitarget			i18n_ucollator_get_keyword_values
* @apicovered			i18n_ucollator_get_keyword_values
* @passcase				When i18n_ucollator_get_keyword_values is successful
* @failcase				If target i18n_ucollator_get_keyword_values fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_ucollator_get_keyword_values_p(void)
{
	START_TEST_PRINT;

	i18n_uenumeration_h hKeywords = NULL;
	char *pszKeyword = "collation";
	
	int nRet = i18n_ucollator_get_keyword_values(pszKeyword, &hKeywords);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_keyword_values", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hKeywords, "i18n_ucollator_get_keyword_values");
	
	nRet =  i18n_uenumeration_destroy(hKeywords);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uenumeration_destroy", BaseUtilsGetError(nRet));
	
	return 0;
}


//& type: auto
//& purpose: Creates a string enumeration of all values for given keyword and a locale
/**
* @testcase				ITc_i18n_ucollator_get_keyword_values_for_locale_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Creates a string enumeration of all values for given keyword and a locale
* @apitarget			i18n_ucollator_get_keyword_values_for_locale
* @apicovered			i18n_ucollator_get_keyword_values_for_locale
* @passcase				When i18n_ucollator_get_keyword_values_for_locale is successful
* @failcase				If target i18n_ucollator_get_keyword_values_for_locale fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_ucollator_get_keyword_values_for_locale_p(void)
{
	START_TEST_PRINT;

	i18n_uenumeration_h hKeywords = NULL;
	char *pszKeyword = "collation";
	char *pszLocale = "en_US";
	
	int nRet = i18n_ucollator_get_keyword_values_for_locale(pszKeyword, pszLocale, false, &hKeywords);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_keyword_values_for_locale", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hKeywords, "i18n_ucollator_get_keyword_values_for_locale");
	
	nRet =  i18n_uenumeration_destroy(hKeywords);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uenumeration_destroy", BaseUtilsGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Returns the functionally equivalent locale for the specified input locale
/**
* @testcase				ITc_i18n_ucollator_get_functional_equivalent_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Returns the functionally equivalent locale for the specified input locale
* @apitarget			i18n_ucollator_get_functional_equivalent
* @apicovered			i18n_ucollator_get_functional_equivalent
* @passcase				When i18n_ucollator_get_functional_equivalent is successful
* @failcase				If target i18n_ucollator_get_functional_equivalent fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_ucollator_get_functional_equivalent_p(void)
{
	START_TEST_PRINT;

	char *pszKeyword = "collation";
	char *pszLocale = "en_US";
	int32_t nDestSize = 128;
	char szDest[nDestSize];
	int32_t nBuffSize;
	i18n_ubool bIsAvail;
	
	int nRet = i18n_ucollator_get_functional_equivalent(pszKeyword, pszLocale, nDestSize, szDest, &bIsAvail, &nBuffSize);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_functional_equivalent", BaseUtilsGetError(nRet));

	return 0;
}


//& type: auto
//& purpose: Gets the collation tailoring rules from collator handle
/**
* @testcase				ITc_i18n_ucollator_get_rules_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets the collation tailoring rules from collator handle
* @apitarget			i18n_ucollator_get_rules
* @apicovered			i18n_ucollator_get_rules, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_get_rules is successful
* @failcase				If target i18n_ucollator_get_rules fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_rules_p(void)
{
	START_TEST;

	int32_t nLength;
	const i18n_uchar *pszRules = NULL;

	int nRet = i18n_ucollator_get_rules(g_hUcollator, &nLength, &pszRules);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_rules", BaseUtilsGetError(nRet));
	CHECK_HANDLE(pszRules, "i18n_ucollator_get_rules");
	
	return 0;
}


//& type: auto
//& purpose: Gets a sort key for a string from collator handle
/**
* @testcase				ITc_i18n_ucollator_get_sort_key_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets a sort key for a string from collator handle
* @apitarget			i18n_ucollator_get_sort_key
* @apicovered			i18n_ucollator_get_sort_key, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_get_sort_key is successful
* @failcase				If target i18n_ucollator_get_sort_key fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_sort_key_p(void)
{
	START_TEST;

	int32_t nSrcLen = -1; 	// NULL terminated
	int32_t nDestLen = 64;
	char *pszTestStr = "Test string";
	i18n_uchar szSrcStr[nDestLen];
	i18n_ustring_copy_ua(szSrcStr, pszTestStr);
	uint8_t nArySortKey[nDestLen];
	int32_t nResultLen;

	int nRet = i18n_ucollator_get_sort_key(g_hUcollator, szSrcStr, nSrcLen, nDestLen, nArySortKey, &nResultLen);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_sort_key", BaseUtilsGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Gets the next count bytes of a sort key
/**
* @testcase				ITc_i18n_ucollator_next_sort_key_part_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets the next count bytes of a sort key
* @apitarget			i18n_ucollator_next_sort_key_part
* @apicovered			i18n_ucollator_next_sort_key_part, i18n_uchar_iter_create, i18n_uchar_iter_set_utf8, i18n_uchar_iter_destroy, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_next_sort_key_part is successful
* @failcase				If target i18n_ucollator_next_sort_key_part fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_next_sort_key_part_p(void)
{
	START_TEST;

	uint32_t nState[2];
	uint8_t nDest[64];
	int32_t nCount = 1;
	int32_t nResultLen;
	i18n_uchar_iter_h hIter = NULL;
	char *pszTestStr = "Test string";
	
	int nRet = i18n_uchar_iter_create(&hIter);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_uchar_iter_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hIter, "i18n_uchar_iter_create");
	
	nRet = i18n_uchar_iter_set_utf8(hIter, pszTestStr, strlen(pszTestStr));
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_uchar_iter_set_utf8", BaseUtilsGetError(nRet), i18n_uchar_iter_destroy(hIter));
	
	nRet = i18n_ucollator_next_sort_key_part(g_hUcollator, hIter, nState, nDest, nCount, &nResultLen);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucollator_next_sort_key_part", BaseUtilsGetError(nRet), i18n_uchar_iter_destroy(hIter));
	
	nRet = i18n_uchar_iter_destroy(hIter);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uchar_iter_destroy", BaseUtilsGetError(nRet));
	
	return 0;
}


//& type: auto
//& purpose: Produces a bound for a given sortkey and a number of levels
/**
* @testcase				ITc_i18n_ucollator_get_bound_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Produces a bound for a given sortkey and a number of levels
* @apitarget			i18n_ucollator_get_bound
* @apicovered			i18n_ucollator_get_bound, i18n_ucollator_get_sort_key, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_get_bound is successful
* @failcase				If target i18n_ucollator_get_bound fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_bound_p(void)
{
	START_TEST;

	int32_t nSrcLen = -1; 	// NULL terminated
	int32_t nDestLen = 64;
	char *pszTestStr = "Test string";
	i18n_uchar szSrcStr[nDestLen];
	i18n_ustring_copy_ua(szSrcStr, pszTestStr);
	uint8_t nArySortKey[nDestLen];
	int32_t nResultLen;
	uint32_t nLevels = 1;
	int32_t nDestSize = 128;
	uint8_t nAryBound[nDestSize];
	int32_t nBoundLen;
	
	i18n_ucollator_bound_mode_e eBoundMode[] = {I18N_UCOLLATOR_BOUND_LOWER ,        /**< Lower bound. */
												I18N_UCOLLATOR_BOUND_UPPER ,        /**< Upper bound that will match strings of exact size. */
												I18N_UCOLLATOR_BOUND_UPPER_LONG};   /**< Upper bound that will match all the strings that have the same initial substring as the given string. */
		
	int nEnumSize = sizeof(eBoundMode) / sizeof(eBoundMode[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		int nRet = i18n_ucollator_get_sort_key(g_hUcollator, szSrcStr, nSrcLen, nDestLen, nArySortKey, &nResultLen);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_sort_key", BaseUtilsGetError(nRet));
		
		FPRINTF("[Line : %d][%s] Executing i18n_ucollator_get_bound with Value = %d ,\\n", __LINE__, API_NAMESPACE, eBoundMode[nEnumCounter]);
		nRet = i18n_ucollator_get_bound(nArySortKey, nResultLen, eBoundMode[nEnumCounter], nLevels, nAryBound, nDestSize, &nBoundLen);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_bound", BaseUtilsGetError(nRet));
	}
	
	return 0;
}


//& type: auto
//& purpose: Gets the version information for a collator handle
/**
* @testcase				ITc_i18n_ucollator_get_version_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets the version information for a collator handle
* @apitarget			i18n_ucollator_get_version
* @apicovered			i18n_ucollator_get_version, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_get_version is successful
* @failcase				If target i18n_ucollator_get_version fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_version_p(void)
{
	START_TEST;

	i18n_uversion_info hInfo;

	int nRet = i18n_ucollator_get_version(g_hUcollator, hInfo);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_version", BaseUtilsGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Gets the UCA version information for a collator handle
/**
* @testcase				ITc_i18n_ucollator_get_uca_version_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets the UCA version information for a collator handle
* @apitarget			i18n_ucollator_get_uca_version
* @apicovered			i18n_ucollator_get_uca_version, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_get_uca_version is successful
* @failcase				If target i18n_ucollator_get_uca_version fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_uca_version_p(void)
{
	START_TEST;

	i18n_uversion_info hInfo;

	int nRet = i18n_ucollator_get_uca_version(g_hUcollator, hInfo);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_uca_version", BaseUtilsGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Merges two sort keys
/**
* @testcase				ITc_i18n_ucollator_merge_sort_keys_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Merges two sort keys
* @apitarget			i18n_ucollator_merge_sort_keys
* @apicovered			i18n_ucollator_merge_sort_keys, i18n_ucollator_get_sort_key, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_merge_sort_keys is successful
* @failcase				If target i18n_ucollator_merge_sort_keys fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_merge_sort_keys_p(void)
{
	START_TEST;

	int32_t nSrcLen = -1; 	// NULL terminated
	int32_t nDestLen = 64;
	char *pszTestStr1 = "Test string one";
	char *pszTestStr2 = "Test string second";
	i18n_uchar szSrcStr1[nDestLen];
	i18n_uchar szSrcStr2[nDestLen];
	i18n_ustring_copy_ua(szSrcStr1, pszTestStr1);
	i18n_ustring_copy_ua(szSrcStr2, pszTestStr2);
	uint8_t nArySortKey1[nDestLen];
	uint8_t nArySortKey2[nDestLen];
	int32_t nResultLen1;
	int32_t nResultLen2;
	int32_t nDestSize = 128;
	uint8_t nAryMerged[nDestSize];
	int32_t nMergedLen;
	
	int nRet = i18n_ucollator_get_sort_key(g_hUcollator, szSrcStr1, nSrcLen, nDestLen, nArySortKey1, &nResultLen1);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_sort_key", BaseUtilsGetError(nRet));
	
	nRet = i18n_ucollator_get_sort_key(g_hUcollator, szSrcStr2, nSrcLen, nDestLen, nArySortKey2, &nResultLen2);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_sort_key", BaseUtilsGetError(nRet));
	
	nRet = i18n_ucollator_merge_sort_keys(nArySortKey1, nResultLen1, nArySortKey2, nResultLen2, nDestSize, nAryMerged, &nMergedLen);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_merge_sort_keys", BaseUtilsGetError(nRet));
	
	return 0;
}


//& type: auto
//& purpose: Get attribute value for a collator handle
/**
* @testcase				ITc_i18n_ucollator_get_attribute_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Get attribute value for a collator handle
* @apitarget			i18n_ucollator_get_attribute
* @apicovered			i18n_ucollator_get_attribute, i18n_ucollator_get_sort_key, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_get_attribute is successful
* @failcase				If target i18n_ucollator_get_attribute fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_attribute_p(void)
{
	START_TEST;

	i18n_ucollator_attribute_value_e eAttribVal;
	
	i18n_ucollator_attribute_e eAttribute[] =  {I18N_UCOLLATOR_FRENCH_COLLATION,					/**< Attribute for direction of secondary weights - used in Canadian French. Acceptable values are #I18N_UCOLLATOR_ON, which results in secondary weights being considered backwards, and #I18N_UCOLLATOR_OFF which treats secondary weights in the order they appear */
												I18N_UCOLLATOR_ALTERNATE_HANDLING,					/**< Attribute for handling variable elements. Acceptable values are #I18N_UCOLLATOR_NON_IGNORABLE (default) which treats all the codepoints with non-ignorable primary weights in the same way, and #I18N_UCOLLATOR_SHIFTED which causes codepoints with primary weights that are equal or below the variable top value to be ignored at the primary level and moved to the quaternary level */
												I18N_UCOLLATOR_CASE_FIRST,							/**< Controls the ordering of upper and lower case letters. Acceptable values are #I18N_UCOLLATOR_OFF (default), which orders upper and lower case letters in accordance to their tertiary weights, #I18N_UCOLLATOR_UPPER_FIRST which forces upper case letters to sort before lower case letters, and #I18N_UCOLLATOR_LOWER_FIRST which does the opposite */
												I18N_UCOLLATOR_CASE_LEVEL,							/**< Controls whether an extra case level (positioned before the third level) is generated or not. Acceptable values are #I18N_UCOLLATOR_OFF (default), when case level is not generated, and #I18N_UCOLLATOR_ON which causes the case level to be generated. Contents of the case level are affected by the value of the #I18N_UCOLLATOR_CASE_FIRST attribute. A simple way to ignore accent differences in a string is to set the strength to #I18N_UCOLLATOR_PRIMARY and enable case level */
												I18N_UCOLLATOR_NORMALIZATION_MODE,					/**< Controls whether the normalization check and necessary normalizations are performed. When set to #I18N_UCOLLATOR_OFF (default) no normalization check is performed. The correctness of the result is guaranteed only if the input data is in so-called FCD form (see users manual for more info). When set to #I18N_UCOLLATOR_ON, an incremental check is performed to see whether the input data is in the FCD form. If the data is not in the FCD form, incremental NFD normalization is performed */
												I18N_UCOLLATOR_DECOMPOSITION_MODE,					/**< An alias for the #I18N_UCOLLATOR_NORMALIZATION_MODE attribute */
												I18N_UCOLLATOR_STRENGTH,							/**< The strength attribute. Can be either #I18N_UCOLLATOR_PRIMARY, #I18N_UCOLLATOR_SECONDARY, #I18N_UCOLLATOR_TERTIARY, #I18N_UCOLLATOR_QUATERNARY, or #I18N_UCOLLATOR_IDENTICAL. The usual strength for most locales (except Japanese) is tertiary. Quaternary strength is useful when combined with shifted setting for the alternate handling attribute and for JIS X 4061 collation, when it is used to distinguish between Katakana and Hiragana. Otherwise, quaternary level is affected only by the number of non-ignorable code points in the string. Identical strength is rarely useful, as it amounts to codepoints of the NFD form of the string */
												I18N_UCOLLATOR_NUMERIC_COLLATION};					/**< When turned on, this attribute makes substrings of digits that are sort according to their numeric values. This is a way to get '100' to sort AFTER '2'. Note that the longest digit substring that can be treated as a single unit is 254 digits (not counting leading zeros). If a digit substring is longer than that, the digits beyond the limit will be treated as a separate digit substring. A "digit" in this sense is a code point with General_Category=Nd, which does not include circled numbers, roman numerals, and so on. Only a contiguous digit substring is considered, that is, non-negative integers without separators. There is no support for plus/minus signs, decimals, exponents, and so on */

	int nEnumSize = sizeof(eAttribute) / sizeof(eAttribute[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		FPRINTF("[Line : %d][%s] Executing i18n_ucollator_get_attribute with Value = %d ,\\n", __LINE__, API_NAMESPACE, eAttribute[nEnumCounter]);
		int nRet = i18n_ucollator_get_attribute(g_hUcollator, eAttribute[nEnumCounter], &eAttribVal);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_attribute", BaseUtilsGetError(nRet));
	}
	
	return 0;
}


//& type: auto
//& purpose: Sets and gets the variable to the top of the specified reordering group
/**
* @testcase				ITc_i18n_ucollator_set_get_max_variable_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Sets and gets the variable to the top of the specified reordering group
* @apitarget			i18n_ucollator_set_max_variable, i18n_ucollator_get_max_variable
* @apicovered			i18n_ucollator_set_max_variable, i18n_ucollator_get_max_variable, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_set_max_variable and i18n_ucollator_get_max_variable is successful
* @failcase				If target i18n_ucollator_set_max_variable or i18n_ucollator_get_max_variable fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_set_get_max_variable_p(void)
{
	START_TEST;

	i18n_ucollator_reorder_code_e eGetRecorderCode;	
	i18n_ucollator_reorder_code_e eSetRecorderCode[] = {I18N_UCOLLATOR_REORDER_CODE_SPACE,          /**< Characters with the space property. This is equivalent to the rule value "space". */
														I18N_UCOLLATOR_REORDER_CODE_PUNCTUATION,    /**< Characters with the punctuation property. This is equivalent to the rule value "punct". */
														I18N_UCOLLATOR_REORDER_CODE_SYMBOL,         /**< Characters with the symbol property. This is equivalent to the rule value "symbol". */
														I18N_UCOLLATOR_REORDER_CODE_CURRENCY,       /**< Characters with the currency property. This is equivalent to the rule value "currency". */
														I18N_UCOLLATOR_REORDER_CODE_DEFAULT};       /**< A special reordering code that is used to specify the default reordering codes for a locale. */

	int nEnumSize = sizeof(eSetRecorderCode) / sizeof(eSetRecorderCode[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		FPRINTF("[Line : %d][%s] Executing i18n_ucollator_set_max_variable with Value = %d ,\\n", __LINE__, API_NAMESPACE, eSetRecorderCode[nEnumCounter]);
		int nRet = i18n_ucollator_set_max_variable(g_hUcollator, eSetRecorderCode[nEnumCounter]);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_set_max_variable", BaseUtilsGetError(nRet));
		
		nRet = i18n_ucollator_get_max_variable(g_hUcollator, &eGetRecorderCode);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_max_variable", BaseUtilsGetError(nRet));

		//I18N_UCOLLATOR_REORDER_CODE_DEFAULT is an abstract reorder code type and depends on default settings configuration. It is also an alias for particular ordinary reorder code type, so it can be ommited in test case
		if(eSetRecorderCode[nEnumCounter] != I18N_UCOLLATOR_REORDER_CODE_DEFAULT)
		{
			if(eGetRecorderCode != eSetRecorderCode[nEnumCounter])
			{
				FPRINTF("[Line : %d][%s] API i18n_ucollator_get_max_variable failed, mismatch set value = %d and get value = %d,\\n", __LINE__, API_NAMESPACE, eSetRecorderCode[nEnumCounter], eGetRecorderCode);
				return 1;
			}
		}
	}
	
	return 0;
}


//& type: auto
//& purpose: Gets the variable top value of a collator handle
/**
* @testcase				ITc_i18n_ucollator_get_variable_top_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets the variable top value of a collator handle
* @apitarget			i18n_ucollator_get_variable_top
* @apicovered			i18n_ucollator_get_variable_top, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_get_variable_top is successful
* @failcase				If target i18n_ucollator_get_variable_top fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_variable_top_p(void)
{
	START_TEST;

	uint32_t nWeight;

	int nRet = i18n_ucollator_get_variable_top(g_hUcollator, &nWeight);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_variable_top", BaseUtilsGetError(nRet));
	
	return 0;
}


//& type: auto
//& purpose: Creates clone of a collator handle
/**
* @testcase				ITc_i18n_ucollator_safe_clone_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Creates clone of a collator handle
* @apitarget			i18n_ucollator_safe_clone
* @apicovered			i18n_ucollator_safe_clone, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_safe_clone is successful
* @failcase				If target i18n_ucollator_safe_clone fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_safe_clone_p(void)
{
	START_TEST;

	i18n_ucollator_h hCloneCollator = NULL;

	int nRet = i18n_ucollator_safe_clone(g_hUcollator, &hCloneCollator);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_safe_clone", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hCloneCollator, "i18n_ucollator_safe_clone");
	
	nRet = i18n_ucollator_destroy(hCloneCollator);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucollator_safe_clone", BaseUtilsGetError(nRet));
	
	return 0;
}


//& type: auto
//& purpose: Get current rules of a collator handle
/**
* @testcase				ITc_i18n_ucollator_get_rules_ex_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Get current rules of a collator handle
* @apitarget			i18n_ucollator_get_rules_ex
* @apicovered			i18n_ucollator_get_rules_ex, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_get_rules_ex is successful
* @failcase				If target i18n_ucollator_get_rules_ex fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_rules_ex_p(void)
{
	START_TEST;

	int32_t nDestLen = 64;
	i18n_uchar nAryDest[nDestLen];
	int32_t nCurrentRules;
	
	i18n_ucollator_rule_option_e eRuleOpt[] =  {I18N_UCOLLATOR_TAILORING_ONLY,  /**< Retrieves the tailoring rules only. Same as calling the version of i18n_ucollator_get_rules() without #i18n_ucollator_rule_option_e. */
												I18N_UCOLLATOR_FULL_RULES};     /**< Retrieves the "UCA rules" concatenated with the tailoring rules. The "UCA rules" are an approximation of the root collator's sort order.
																					 They are almost never used or useful at runtime and can be removed from the data.
																					 See http://userguide.icu-project.org/collation/customization#TOC-Building-on-Existing-Locales. */

	int nEnumSize = sizeof(eRuleOpt) / sizeof(eRuleOpt[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		FPRINTF("[Line : %d][%s] Executing i18n_ucollator_get_rules_ex with Value = %d,\\n", __LINE__, API_NAMESPACE, eRuleOpt[nEnumCounter]);
		int nRet = i18n_ucollator_get_rules_ex(g_hUcollator, eRuleOpt[nEnumCounter], nDestLen, nAryDest, &nCurrentRules);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_rules_ex", BaseUtilsGetError(nRet));
	}
	
	return 0;
}


//& type: auto
//& purpose: Gets the locale name of the collator
/**
* @testcase				ITc_i18n_ucollator_get_locale_by_type_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets the locale name of the collator
* @apitarget			i18n_ucollator_get_locale_by_type
* @apicovered			i18n_ucollator_get_locale_by_type, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_get_locale_by_type is successful
* @failcase				If target i18n_ucollator_get_locale_by_type fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_locale_by_type_p(void)
{
	START_TEST;

	const char *pszLocale = NULL;
	
	i18n_ulocale_data_locale_type_e eDataType[] =  {I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE,     /**< Actual locale */
												    I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE};	 /**< Valid locale */
	
	int nEnumSize = sizeof(eDataType) / sizeof(eDataType[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		FPRINTF("[Line : %d][%s] Executing i18n_ucollator_get_locale_by_type with Value = %d,\\n", __LINE__, API_NAMESPACE, eDataType[nEnumCounter]);
		int nRet = i18n_ucollator_get_locale_by_type(g_hUcollator, eDataType[nEnumCounter], &pszLocale);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_locale_by_type", BaseUtilsGetError(nRet));
		CHECK_HANDLE(pszLocale, "i18n_ucollator_get_locale_by_type");
	}
	
	return 0;
}


//& type: auto
//& purpose: Gets a Unicode set having all characters and sequences tailored in collator handle
/**
* @testcase				ITc_i18n_ucollator_get_tailored_set_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets a Unicode set having all characters and sequences tailored in collator handle
* @apitarget			i18n_ucollator_get_tailored_set
* @apicovered			i18n_ucollator_get_tailored_set, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_get_tailored_set is successful
* @failcase				If target i18n_ucollator_get_tailored_set fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_get_tailored_set_p(void)
{
	START_TEST;

	i18n_uset_h hUset = NULL;

	int nRet = i18n_ucollator_get_tailored_set(g_hUcollator, &hUset);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_get_tailored_set", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUset, "i18n_ucollator_get_tailored_set");
	
	nRet = i18n_uset_destroy(hUset);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uset_destroy", BaseUtilsGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Creates a binary image of a collator
/**
* @testcase				ITc_i18n_ucollator_clone_binary_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Creates a binary image of a collator
* @apitarget			i18n_ucollator_clone_binary
* @apicovered			i18n_ucollator_clone_binary, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_clone_binary is successful
* @failcase				If target i18n_ucollator_clone_binary fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_clone_binary_p(void)
{
	START_TEST;

	int32_t nDestSize = 64;
	uint8_t nAryDest[nDestSize];
	int32_t nImageSize;

	int nRet = i18n_ucollator_clone_binary(g_hUcollator, nDestSize, nAryDest, &nImageSize);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_clone_binary", BaseUtilsGetError(nRet));
	
	if(nImageSize == 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_clone_binary failed returning invalid out val = %d,\\n", __LINE__, API_NAMESPACE, nImageSize);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: Creates a collator from a collator binary image
/**
* @testcase				ITc_i18n_ucollator_create_binary_p
* @since_tizen 			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Creates a collator from a collator binary image
* @apitarget			i18n_ucollator_create_binary
* @apicovered			i18n_ucollator_create_binary, i18n_ucollator_create, i18n_ucollator_destroy
* @passcase				When i18n_ucollator_create_binary is successful
* @failcase				If target i18n_ucollator_create_binary fails or any precondition and postcondition API fails.
* @precondition			Create a i18n_ucollator_h
* @postcondition		Destroy a i18n_ucollator_h 
*/
int ITc_i18n_ucollator_create_binary_p(void)
{
	START_TEST;

	int32_t nDestSize = 64;
	uint8_t nAryDest[nDestSize];
	int32_t nImageSize;
	i18n_ucollator_h hBinColl = NULL;

	int nRet = i18n_ucollator_clone_binary(g_hUcollator, nDestSize, nAryDest, &nImageSize);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_clone_binary", BaseUtilsGetError(nRet));
	
	if(nImageSize == 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ucollator_clone_binary failed returning invalid out val = %d,\\n", __LINE__, API_NAMESPACE, nImageSize);
		return 1;
	}
	
	nRet = i18n_ucollator_create_binary(nAryDest, nImageSize, g_hUcollator, &hBinColl);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucollator_create_binary", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hBinColl, "i18n_ucollator_create_binary");
	
	nRet = i18n_ucollator_destroy(hBinColl);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucollator_destroy", BaseUtilsGetError(nRet));
	
	return 0;
}
