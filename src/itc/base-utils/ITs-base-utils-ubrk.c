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

static i18n_ubreak_iterator_h g_hUbrkIter = NULL;
static i18n_uchar *pszUchar = NULL;

//& set: BaseUtilsUbrk 
void ITs_base_utils_ubrk_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	const char *pszLocale = I18N_ULOCALE_US;
    char *pszText = "Tizen Native Testing";
    pszUchar = (i18n_uchar*)calloc(strlen(pszText) + 1, sizeof(i18n_uchar));
	
	i18n_uchar *pRet = i18n_ustring_copy_ua(pszUchar, pszText);
    if ( pRet == NULL || i18n_ustring_get_length(pszUchar) <= 0 )
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in startup\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
		return;
	}

	int nRetVal = i18n_ubrk_create(I18N_UBRK_WORD, pszLocale, pszUchar, strlen(pszText), &g_hUbrkIter);
	if(nRetVal != I18N_ERROR_NONE || g_hUbrkIter == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ubrk_create failed in startup\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
		return;
	}
		
	g_bBaseUtilsInitFlag = true;
	return;
}

void ITs_base_utils_ubrk_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	if( i18n_ubrk_destroy(g_hUbrkIter) != I18N_ERROR_NONE)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ubrk_destroy failed in cleanup\\n", __LINE__, API_NAMESPACE);
	}
	FREE_MEMORY(pszUchar);
	g_bBaseUtilsInitFlag = false;
	return;
}

/** @addtogroup itc-base-utils-testcases
*  @brief 		Integration testcases for module base-utils ubrk
*  @ingroup 	itc-base-utils
*  @{
*/

//& type: auto
//& purpose: Creates and Destroy a new iterator for locating text boundaries for a specified locale
/**
* @testcase				ITc_i18n_ubrk_create_destroy_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Get default locale and copy text to uchar 
* 						- Creates a new iterator for locating text boundaries for a specified locale
* 						- Destroys iterator 	
* @apitarget			i18n_ubrk_create, i18n_ubrk_destroy		
* @apicovered			i18n_ubrk_create, i18n_ubrk_destroy, i18n_ustring_copy_ua
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_create and i18n_ubrk_destroy
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_create or i18n_ubrk_destroy or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_create_destroy_p(void)
{	
	START_TEST_PRINT;
	int nRetVal = -1;
	i18n_ubreak_iterator_type_e eUbrkIteratorType[] = {	I18N_UBRK_CHARACTER,
														I18N_UBRK_WORD,     
														I18N_UBRK_LINE,     
														I18N_UBRK_SENTENCE};
	int nEnumSize = sizeof(eUbrkIteratorType) / sizeof(eUbrkIteratorType[0]);
	int nEnumCounter = 0;
	
	const char *pszLocale = I18N_ULOCALE_US;
    char *pszText = "Tizen Native Api Testing";
    i18n_uchar *pszUchar = (i18n_uchar*)calloc(strlen(pszText) + 1, sizeof(i18n_uchar));
	i18n_ubreak_iterator_h hUbrkIter = NULL;
	
	i18n_uchar *pRet = i18n_ustring_copy_ua(pszUchar, pszText);
    if ( pRet == NULL || i18n_ustring_get_length(pszUchar) <= 0 )
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszUchar);
		return 1;
	}

	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for Iterator type (%s) \\n", __LINE__, API_NAMESPACE, UbrkGetIteratorType(eUbrkIteratorType[nEnumCounter]));
		nRetVal = i18n_ubrk_create(eUbrkIteratorType[nEnumCounter], pszLocale, pszUchar, strlen(pszText), &hUbrkIter);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_create", BaseUtilsGetError(nRetVal),FREE_MEMORY(pszUchar));
		CHECK_HANDLE_CLEANUP(hUbrkIter, "i18n_ubrk_create",FREE_MEMORY(pszUchar));
		 
		nRetVal = i18n_ubrk_destroy(hUbrkIter);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_destroy", BaseUtilsGetError(nRetVal),FREE_MEMORY(pszUchar));
	}
	FREE_MEMORY(pszUchar);
	return 0;
}

//& type: auto
//& purpose: Creates new breaking rules
/**
* @testcase				ITc_i18n_ubrk_create_rules_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Creates new breaking rules
* 						- Creates a new iterator for locating text boundaries for a specified locale
* 						- Destroys iterator 	
* @apitarget			i18n_ubrk_create_rules	
* @apicovered			i18n_ubrk_create_rules, i18n_ustring_copy_ua
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_create_rules
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_create_rules or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_create_rules_p(void)
{	
	START_TEST_PRINT;
	int nRetVal = -1;
	const char *szRules = "[A-N]{100}; \n"
                        "[a-w]{200}; \n"
                        "[\\p{L}]{300}; \n"
                        "[\\p{N}]{400}; \n"
                        "[0-5]{500}; \n"
                        "!.*;\n";

	i18n_uchar *pUcharRules = (i18n_uchar*)calloc(strlen(szRules) + 1, sizeof(i18n_uchar));
	if(NULL ==pUcharRules)
	{
		return 1;
	}
	 
	char *pszText = "rules \n";
	i18n_uchar *pUcharText = (i18n_uchar*)calloc(strlen(pszText) + 1, sizeof(i18n_uchar));
	if(NULL ==pUcharText)
	{
		FREE_MEMORY(pUcharRules);
		return 1;
	}
	 
	i18n_ubreak_iterator_h hUbrkIter = NULL;
	
	i18n_uchar *pRet = i18n_ustring_copy_ua(pUcharRules, szRules);
	if ( pRet == NULL || i18n_ustring_get_length(pUcharRules) <= 0 )
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in copy rules\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pUcharRules);
		FREE_MEMORY(pUcharText);
		return 1;
	}
	
	i18n_uchar *pRet1 = i18n_ustring_copy_ua(pUcharText, pszText);
	if ( pRet1 == NULL || i18n_ustring_get_length(pUcharText) <= 0 )
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in copy text\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pUcharRules);
		FREE_MEMORY(pUcharText);
		return 1;
	}
	nRetVal = i18n_ubrk_create_rules(pUcharRules, -1, pUcharText, -1, &hUbrkIter, NULL);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_create_rules", BaseUtilsGetError(nRetVal),FREE_MEMORY(pUcharRules);FREE_MEMORY(pUcharText));
	CHECK_HANDLE_CLEANUP(hUbrkIter, "i18n_ubrk_create_rules",FREE_MEMORY(pUcharRules);FREE_MEMORY(pUcharText));
	
	FREE_MEMORY(pUcharRules);
	FREE_MEMORY(pUcharText);
	return 0;
}

//& type: auto
//& purpose: Thread safe cloning operation
/**
* @testcase				ITc_i18n_ubrk_safe_clone_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Thread safe cloning operation
* @apitarget			i18n_ubrk_safe_clone		
* @apicovered			i18n_ubrk_safe_clone
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_safe_clone
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_safe_clone or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_safe_clone_p(void)
{	
	START_TEST;
	int nRetVal = -1;
    i18n_ubreak_iterator_h hUbrkIterClone = NULL;
    
	nRetVal = i18n_ubrk_safe_clone(g_hUbrkIter, NULL, NULL, &hUbrkIterClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_safe_clone", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hUbrkIterClone, "i18n_ubrk_safe_clone");
	
	return 0;
}

//& type: auto
//& purpose: Sets an existing iterator to point a new text
/**
* @testcase				ITc_i18n_ubrk_set_text_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Sets an existing iterator to point a new text
* @apitarget			i18n_ubrk_set_text	
* @apicovered			i18n_ubrk_set_text, i18n_ustring_copy_ua
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_set_text
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_set_text or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_set_text_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	
	char *pszText = "APITESTING";
    i18n_uchar *pUcharText = (i18n_uchar*)calloc(strlen(pszText) + 1, sizeof(i18n_uchar));
	
    i18n_uchar *pRet = i18n_ustring_copy_ua(pUcharText, pszText);
    if ( pRet == NULL || i18n_ustring_get_length(pUcharText) <= 0 )
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed \\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pUcharText);
		return 1;
	}

	nRetVal = i18n_ubrk_set_text(g_hUbrkIter, pUcharText, strlen(pszText));
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_set_text", BaseUtilsGetError(nRetVal),FREE_MEMORY(pUcharText));
	
	FREE_MEMORY(pUcharText);
	return 0;
}

//& type: auto
//& purpose: Determines recently-returned text boundary
/**
* @testcase				ITc_i18n_ubrk_current_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Determines recently-returned text boundary
* @apitarget			i18n_ubrk_current		
* @apicovered			i18n_ubrk_current
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_current
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_current or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_current_p(void)
{	
	START_TEST;
	int32_t nIndex = -1;
	
	nIndex = i18n_ubrk_current(g_hUbrkIter);
	CHECK_RETURN_VAL(nIndex, "i18n_ubrk_current");
	
	int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_current", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Sets the iterator position to the boundary following and preceding the current boundary
/**
* @testcase				ITc_i18n_ubrk_next_previous_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Sets the iterator position to the boundary following and preceding the current boundary
* @apitarget			i18n_ubrk_next, i18n_ubrk_previous	
* @apicovered			i18n_ubrk_next, i18n_ubrk_previous
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_next and i18n_ubrk_previous
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_next, i18n_ubrk_previous or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_next_previous_p(void)
{	
	START_TEST;
	int32_t nIndex = -1;
	
	nIndex = i18n_ubrk_next(g_hUbrkIter);
	CHECK_RETURN_VAL(nIndex, "i18n_ubrk_next");
	int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_next", BaseUtilsGetError(nRetVal));
	
	nIndex = -1;
	nIndex = i18n_ubrk_previous(g_hUbrkIter);
	CHECK_RETURN_VAL(nIndex, "i18n_ubrk_previous");
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_previous", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Sets the iterator position zero and sets to the last character in the text
/**
* @testcase				ITc_i18n_ubrk_first_last_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Sets the iterator position to zero and sets to the last character in the text
* @apitarget			i18n_ubrk_first, i18n_ubrk_last	
* @apicovered			i18n_ubrk_first, i18n_ubrk_last
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_first and i18n_ubrk_last
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_first, i18n_ubrk_last or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_first_last_p(void)
{	
	START_TEST;
	int32_t nIndex = -1;
	
	nIndex = i18n_ubrk_first(g_hUbrkIter);
	CHECK_RETURN_VAL(nIndex, "i18n_ubrk_first");
	int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_first", BaseUtilsGetError(nRetVal));
	
	nIndex = -1;
	nIndex = i18n_ubrk_last(g_hUbrkIter);
	CHECK_RETURN_VAL(nIndex, "i18n_ubrk_last");
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_last", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Sets the iterator position to the first boundary preceding and following the specified offset
/**
* @testcase				ITc_i18n_ubrk_preceding_following_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Sets the iterator position to the first boundary preceding and following the specified offset
* @apitarget			i18n_ubrk_preceding, i18n_ubrk_following	
* @apicovered			i18n_ubrk_preceding, i18n_ubrk_following
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_preceding and i18n_ubrk_following
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_preceding, i18n_ubrk_following or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_preceding_following_p(void)
{	
	START_TEST;
	int32_t nIndex = -1, nOffset = 2;
	
	nIndex = i18n_ubrk_preceding(g_hUbrkIter, nOffset);
	CHECK_RETURN_VAL(nIndex, "i18n_ubrk_preceding");
	int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_preceding", BaseUtilsGetError(nRetVal));
	
	nIndex = -1;
	nIndex = i18n_ubrk_following(g_hUbrkIter, nOffset);
	CHECK_RETURN_VAL(nIndex, "i18n_ubrk_following");
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_following", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Gets a locale for which text breaking information is available
/**
* @testcase				ITc_i18n_ubrk_get_available_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Gets a locale for which text breaking information is available
* @apitarget			i18n_ubrk_get_available		
* @apicovered			i18n_ubrk_get_available
* @passcase				API i18n_ubrk_get_available doesn't crash
* @failcase				API i18n_ubrk_get_available crashes
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_get_available_p(void)
{	
	START_TEST_PRINT;
	int32_t nIndex = 1;
	
	i18n_ubrk_get_available(nIndex);

	return 0;
}

//& type: auto
//& purpose: Determines how many locales have text breaking information available
/**
* @testcase				ITc_i18n_ubrk_count_available_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Determines how many locales have text breaking information available
* @apitarget			i18n_ubrk_count_available		
* @apicovered			i18n_ubrk_count_available
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_count_available
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_count_available or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_count_available_p(void)
{	
	START_TEST_PRINT;
	int32_t nCount = -1;
	
	nCount = i18n_ubrk_count_available();
	CHECK_RETURN_VAL(nCount, "i18n_ubrk_count_available");

	return 0;
}

//& type: auto
//& purpose: Returns true/false for specified position is a boundary position or not
/**
* @testcase				ITc_i18n_ubrk_is_boundary_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Returns true/false for specified position is a boundary position or not
* @apitarget			i18n_ubrk_is_boundary		
* @apicovered			i18n_ubrk_is_boundary
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_is_boundary
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_is_boundary or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_is_boundary_p(void)
{	
	START_TEST;
	int32_t nOffset = 2;
	
	i18n_ubool bRetVal = i18n_ubrk_is_boundary(g_hUbrkIter, nOffset);
	if(bRetVal != true && bRetVal != false)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ubrk_is_boundary failed, return value is = %d \n", __LINE__, API_NAMESPACE, bRetVal);
		return 1;
	}
	
	int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_is_boundary", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Returns the status from the break rule that determined the most recently returned break position
/**
* @testcase				ITc_i18n_ubrk_get_rule_status_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Returns the status from the break rule that determined the most recently returned break position
* @apitarget			i18n_ubrk_get_rule_status		
* @apicovered			i18n_ubrk_get_rule_status
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_get_rule_status
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_get_rule_status or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_get_rule_status_p(void)
{	
	START_TEST;
	int32_t nIndex = -1;
	
	nIndex = i18n_ubrk_get_rule_status(g_hUbrkIter);
	CHECK_RETURN_VAL(nIndex, "i18n_ubrk_get_rule_status");
	
	int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_get_rule_status", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Returns the status vector from the break rule that determined the most recently returned break position
/**
* @testcase				ITc_i18n_ubrk_get_rule_status_vec_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Returns the status vector from the break rule that determined the most recently returned break position
* @apitarget			i18n_ubrk_get_rule_status_vec		
* @apicovered			i18n_ubrk_get_rule_status_vec
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_get_rule_status_vec
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_get_rule_status_vec or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_get_rule_status_vec_p(void)
{	
	START_TEST;
	int32_t nIndex = -1;
	int32_t nArrayStatusVal[I18N_UNUMBER_SYMBOL_CAPACITY]={0};
    int32_t nCapacity = I18N_UNUMBER_SYMBOL_CAPACITY;
    
	char *pszText = "Tizen Native Api Testing";
    i18n_uchar *pszUchar = (i18n_uchar*)calloc(strlen(pszText) + 1, sizeof(i18n_uchar));
	
    i18n_uchar *pRet = i18n_ustring_copy_ua(pszUchar, pszText);
    if ( pRet == NULL || i18n_ustring_get_length(pszUchar) <= 0 )
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszUchar);
		return 1;
	}
	
	nIndex = i18n_ubrk_get_rule_status_vec(g_hUbrkIter, nArrayStatusVal, nCapacity);
	CHECK_RETURN_VAL_CLEANUP(nIndex, "i18n_ubrk_get_rule_status_vec",FREE_MEMORY(pszUchar));
	
	int nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_get_rule_status_vec", BaseUtilsGetError(nRetVal),FREE_MEMORY(pszUchar));
	
	FREE_MEMORY(pszUchar);
	return 0;
}

//& type: auto
//& purpose: Returns the locale of the break iterator
/**
* @testcase				ITc_i18n_ubrk_get_locale_by_type_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Returns the locale of the break iterator
* @apitarget			i18n_ubrk_get_locale_by_type		
* @apicovered			i18n_ubrk_get_locale_by_type
* @passcase				I18N_ERROR_NONE returned by i18n_ubrk_get_locale_by_type
* @failcase				I18N_ERROR_NONE not returned by i18n_ubrk_get_locale_by_type or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubrk_get_locale_by_type_p(void)
{	
	START_TEST;
	i18n_ulocale_data_locale_type_e eLocaleType[] = {	I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE,
														I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE};
	int nEnumSize = sizeof(eLocaleType) / sizeof(eLocaleType[0]);
	int nEnumCounter = 0, nRetVal = -1;
	const char *pszLocale = NULL;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for Locale type (%s) \\n", __LINE__, API_NAMESPACE, UcalendarGetLocaleType(eLocaleType[nEnumCounter]));
		pszLocale = i18n_ubrk_get_locale_by_type(g_hUbrkIter, eLocaleType[nEnumCounter]);
		CHECK_HANDLE(pszLocale, "i18n_ubrk_get_locale_by_type");
		 
		nRetVal = get_last_result();
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubrk_get_locale_by_type", BaseUtilsGetError(nRetVal));
	}
	
	return 0;
}
/** @} */
/** @} */
