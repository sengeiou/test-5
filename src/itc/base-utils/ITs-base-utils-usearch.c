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

/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/

const char *g_pszDefaultLocale = I18N_ULOCALE_US;
int g_nLengthDefaultTimeZone = 0;
i18n_uchar *g_pDefaultTzid = NULL;


//static bool g_CallBackValue = true;

//& set: BaseUtilsUsearch

/**
* @function 		ITs_base_utils_usearch_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_base_utils_usearch_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	i18n_uchar *pRet  = NULL;
	g_bBaseUtilsInitFlag = false;
	g_nLengthDefaultTimeZone = 0;
	g_pDefaultTzid = NULL;

	/*int nRetVal = i18n_ulocale_get_default(&g_pszDefaultLocale); // Locale to be used I18N_ULOCALE_US as suggested by HQ
	if ( nRetVal != I18N_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_default failed in STARTUP, error returned = %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
		return;
	}*/

	g_pDefaultTzid = (i18n_uchar*)calloc(strlen(I18N_DEFAULT_T_ZONE) + 1, sizeof(i18n_uchar));
	if ( g_pDefaultTzid == NULL )
	{
		FPRINTF("[Line : %d][%s] g_pDefaultTzid, memory not allocated properly\\n", __LINE__, API_NAMESPACE);
		return;
	}
	pRet = i18n_ustring_copy_ua(g_pDefaultTzid, (char *)I18N_DEFAULT_T_ZONE);
	if ( i18n_ustring_get_length(pRet) == 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua failed in start-up\\n", __LINE__, API_NAMESPACE);
		return;
	}
	g_nLengthDefaultTimeZone = i18n_ustring_get_length(g_pDefaultTzid);
	FPRINTF("[Line : %d][%s] i18n_ustring_get_length returns value = %d\\n", __LINE__, API_NAMESPACE, g_nLengthDefaultTimeZone);

	g_pszDefaultLocale = I18N_ULOCALE_US;
	g_bBaseUtilsInitFlag = true;
	return;
}

/**
* @function 		ITs_base_utils_usearch_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_usearch_cleanup(void)
{
	FREE_MEMORY(g_pDefaultTzid);
	g_bBaseUtilsInitFlag = false;
	g_nLengthDefaultTimeZone = 0;

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type: auto
//& purpose: Find the first index at which the string text matches the search and Returns the matched text.
/**
* @testcase				ITc_i18n_usearch_first_get_macthed_text_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the first index at which the string text matches the search.\n
* 						Returns the text that was matched by the most recent call to i18n_usearch_first.
* @apitarget			i18n_usearch_first, i18n_usearch_get_matched_text
* @apicovered			i18n_usearch_first, i18n_usearch_get_matched_text, i18n_ustring_from_UTF8, i18n_usearch_create, i18n_usearch_get_matched_text, i18n_usearch_destroy
* @passcase				When i18n_usearch_first, i18n_usearch_get_matched_text are successful
* @failcase				If target i18n_usearch_first or i18n_usearch_get_matched_text fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_usearch_first_get_macthed_text_p(void)
{
	START_TEST;

	i18n_uchar target[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar pattern[I18N_UCHAR_CAPACITY] = {0,};
	i18n_usearch_h uSearch = NULL;
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;
	i18n_ubreak_iterator_h break_iter = NULL;

	i18n_uchar *pRet = i18n_ustring_from_UTF8(target, I18N_UCHAR_CAPACITY, NULL, SOURCE_STRING, -1 , &ErrorCode);
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_from_UTF8", BaseUtilsGetError(ErrorCode));
	if ( pRet == NULL || i18n_ustring_get_length(target) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_from_UTF8 Failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	pRet = i18n_ustring_from_UTF8(pattern, I18N_UCHAR_CAPACITY, NULL, USEARCH_KEYWORD, -1, &ErrorCode);
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_from_UTF8", BaseUtilsGetError(ErrorCode));
	if ( pRet == NULL || i18n_ustring_get_length(pattern) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_from_UTF8 Failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRetVal = i18n_usearch_create_new(pattern, I18N_UCHAR_CAPACITY, target, I18N_UCHAR_CAPACITY, g_pszDefaultLocale, break_iter, &uSearch);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_usearch_create_new", BaseUtilsGetError(nRetVal));

	int nPosition = 0;
	nRetVal = i18n_usearch_first(uSearch, &nPosition);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_usearch_first", BaseUtilsGetError(nRetVal), i18n_usearch_destroy(uSearch));
	if ( nPosition != USEARCH_MATCHED_POSITION )
	{
		FPRINTF("[Line : %d][%s] Target API i18n_usearch_first Failed , as expected search position(%d) not matched with actual search position(%d)\\n", __LINE__, API_NAMESPACE, USEARCH_MATCHED_POSITION, nPosition);
		nRetVal = i18n_usearch_destroy(uSearch);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_usearch_destroy", BaseUtilsGetError(nRetVal));
		return 1;
	}
	i18n_uchar matchedPattern[I18N_UCHAR_CAPACITY] = {0,};
	int nMatchedLength = 0;
	nRetVal = i18n_usearch_get_matched_text(uSearch, matchedPattern, I18N_UCHAR_CAPACITY, &nMatchedLength);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_usearch_get_matched_text", BaseUtilsGetError(nRetVal), i18n_usearch_destroy(uSearch));
	if ( nMatchedLength != USEARCH_MATCHED_LENGTH )
	{
		FPRINTF("[Line : %d][%s] Target API i18n_usearch_get_matched_text Failed , as expected matched Length(%d) not equal with actual matched length(%d)\\n", __LINE__, API_NAMESPACE, USEARCH_MATCHED_LENGTH, nMatchedLength);
		nRetVal = i18n_usearch_destroy(uSearch);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_usearch_destroy", BaseUtilsGetError(nRetVal));
		return 1;
	}
	nRetVal = i18n_usearch_destroy(uSearch);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_usearch_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Gets the collator used for the language rules.
/**
* @testcase				ITc_i18n_usearch_get_collator_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the collator used for the language rules.
* @apitarget			i18n_usearch_get_collator
* @apicovered			i18n_usearch_get_collator, i18n_usearch_create, i18n_usearch_destroy
* @passcase				When i18n_usearch_get_collator is successful
* @failcase				If target i18n_usearch_get_collator fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_usearch_get_collator_p(void)
{
	START_TEST;

	i18n_uchar target[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar pattern[I18N_UCHAR_CAPACITY] = {0,};
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;
	i18n_ustring_from_UTF8(target, I18N_UCHAR_CAPACITY, NULL, SOURCE_STRING, -1, &ErrorCode );
	i18n_ustring_from_UTF8(pattern, I18N_UCHAR_CAPACITY, NULL, USEARCH_KEYWORD, -1, &ErrorCode);
	i18n_ubreak_iterator_h break_iter = NULL;

	i18n_usearch_h uSearch = NULL;
	i18n_ucollator_h uCollator = NULL;

	int nRetVal = i18n_usearch_create_new(pattern, I18N_UCHAR_CAPACITY, target, I18N_UCHAR_CAPACITY, g_pszDefaultLocale, break_iter, &uSearch);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_usearch_create_new", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_usearch_get_collator(uSearch, &uCollator);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_usearch_get_collator", BaseUtilsGetError(nRetVal), i18n_usearch_destroy(uSearch));
	if ( uCollator == NULL )
	{
		FPRINTF("[Line : %d][%s] Target API i18n_usearch_get_collator Failed , as ucollator is not initialized (NULL )\\n", __LINE__, API_NAMESPACE);
		nRetVal = i18n_usearch_destroy(uSearch);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_usearch_destroy", BaseUtilsGetError(nRetVal));
		return 1;
	}
	nRetVal = i18n_usearch_destroy(uSearch);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_usearch_destroy", BaseUtilsGetError(nRetVal));
		
	return 0;
}

//& purpose: Creates an #i18n_usearch_h using the argument locale language rule set.
/**
 * @testcase 				ITc_i18n_usearch_create_new_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Creates an #i18n_usearch_h using the argument locale language rule set.
 * @scenario				Creates an #i18n_usearch_h using the argument locale language rule set.\n
 *							Destroys an #i18n_usearch_h set. 
 * @api-covered				i18n_usearch_create_new, i18n_usearch_destroy
 * @pass-case				When i18n_usearch_create_new is successful.
 * @fail-case				If target i18n_usearch_create_new fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_usearch_create_new_p(void)
{		
	START_TEST;	
	i18n_uchar target[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar pattern[I18N_UCHAR_CAPACITY] = {0,};
	i18n_usearch_h uSearch = NULL;
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;
	i18n_ubreak_iterator_h break_iter = NULL;
	
	i18n_uchar *pRet = i18n_ustring_from_UTF8(target, I18N_UCHAR_CAPACITY, NULL, SOURCE_STRING, -1, &ErrorCode);
	if(pRet == NULL || ErrorCode != I18N_ERROR_NONE || i18n_ustring_get_length(target) <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_from_UTF8 API failed while testing target API i18n_usearch_create_new\n", __LINE__, API_NAMESPACE);
		return 1;	
	}
	pRet = i18n_ustring_from_UTF8(pattern, I18N_UCHAR_CAPACITY, NULL, USEARCH_KEYWORD, -1, &ErrorCode);		
	if(pRet == NULL || ErrorCode != I18N_ERROR_NONE || i18n_ustring_get_length(pattern) <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_from_UTF8 API failed while testing target API i18n_usearch_create_new\n", __LINE__, API_NAMESPACE);
		return 1;
	}		

	int nRetVal = i18n_usearch_create_new(pattern, I18N_UCHAR_CAPACITY, target, I18N_UCHAR_CAPACITY, g_pszDefaultLocale, break_iter, &uSearch);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_usearch_create_new", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_usearch_destroy(uSearch);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_usearch_destroy", BaseUtilsGetError(nRetVal));
	
    return 0;
}

