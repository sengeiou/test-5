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
void *g_pContext = NULL;
int32_t g_Offset = 0;
int g_UnescapeCallback = false;
i18n_uchar UStringUnescapeCharAtCB(int32_t offset, void *context)
{
        FPRINTF("[Line : %d][%s] Inside UStringUnescapeCharAtCB. Offset value = %d\\n", __LINE__, API_NAMESPACE, offset);
        g_UnescapeCallback = true;
        return (i18n_uchar)offset;
}

//& set: BaseUtilsUstring

/**
* @function 		ITs_base_utils_ustring_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_base_utils_ustring_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bBaseUtilsInitFlag = true;
	return;
}

/**
* @function 		ITs_base_utils_ustring_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_ustring_cleanup(void)
{
	g_bBaseUtilsInitFlag = false;

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}




//& type: auto
//& purpose: Copies a ustring. Adds a null terminator. And Compare Two Unicode Strings.
/**
* @testcase				ITc_i18n_ustring_copy_compare_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Copies a ustring. Adds a null terminator
* 						Compares two Unicode strings for bitwise equality
* @apitarget			i18n_ustring_copy, i18n_ustring_compare
* @apicovered			i18n_ustring_copy, i18n_ustring_compare
* @passcase				When i18n_ustring_copy, i18n_ustring_compare are successful
* @failcase				If target i18n_ustring_copy or i18n_ustring_compare fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_copy_compare_p(void)
{	
	START_TEST;

	i18n_uchar uSourceStr[I18N_UCHAR_CAPACITY] = { 0, };
	i18n_uchar *pRet = i18n_ustring_copy_ua_n(uSourceStr, (char *)SOURCE_STRING, strlen(SOURCE_STRING));
	if ( pRet == NULL || i18n_ustring_get_length(uSourceStr) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n Failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar uDestStr[I18N_UCHAR_CAPACITY] = { 0, };
	pRet = i18n_ustring_copy(uDestStr, uSourceStr);
	if ( pRet == NULL || i18n_ustring_get_length(uDestStr) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy Failed ,\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int nResult = -1;
	nResult = i18n_ustring_compare(uSourceStr, uDestStr);
	if ( nResult != 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_compare Failed ,return value = %d\\n", __LINE__, API_NAMESPACE, nResult);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines the length of an array of i18n_uchar. And Upper cases the characters in a string.
/**
* @testcase				ITc_i18n_ustring_get_length_to_upper_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Determines the length of an array of i18n_uchar
* 						Upper-cases the characters in a string.
* @apitarget			i18n_ustring_get_length, i18n_ustring_to_upper
* @apicovered			i18n_ustring_get_length, i18n_ustring_to_upper
* @passcase				When i18n_ustring_get_length, i18n_ustring_to_upper are successful
* @failcase				If target i18n_ustring_get_length or i18n_ustring_to_upper fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_get_length_to_upper_p(void)
{	
	START_TEST;

	i18n_uchar uSourceStr[I18N_UCHAR_CAPACITY] = { 0, };
	i18n_uchar *pRet = i18n_ustring_copy_ua_n(uSourceStr, (char *)SOURCE_STRING, strlen(SOURCE_STRING));
	if ( pRet == NULL || i18n_ustring_get_length(uSourceStr) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n Failed in precondition\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	const char *pszDefaultLocale = I18N_ULOCALE_US;
	int nSourceLength = 0;
	nSourceLength = i18n_ustring_get_length(uSourceStr);
	if ( nSourceLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar uDestStr[I18N_UCHAR_CAPACITY] = { 0, };
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;
	int nRetVal = i18n_ustring_to_upper(uDestStr, I18N_UCHAR_CAPACITY, uSourceStr, nSourceLength, pszDefaultLocale, &ErrorCode);
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_to_upper", BaseUtilsGetError(ErrorCode));
	if ( nRetVal != nSourceLength )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_to_upper Failed as Source Uchar String Length value is %d, but Destination Uchar String Length value is %d\\n", __LINE__, API_NAMESPACE, nSourceLength, nRetVal);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Converts a UTF-8 string to UTF-16. Converts a UTF-16 string to UTF-8.
/**
* @testcase				ITc_i18n_ustring_from_UTF8_to_UTF8_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Converts a UTF-8 string to UTF-16
* 						Converts a UTF-16 string to UTF-8.
* @apitarget			i18n_ustring_from_UTF8, i18n_ustring_to_UTF8
* @apicovered			i18n_ustring_from_UTF8, i18n_ustring_to_UTF8
* @passcase				When i18n_ustring_from_UTF8, i18n_ustring_to_UTF8 are successful
* @failcase				If target i18n_ustring_from_UTF8 or i18n_ustring_to_UTF8 fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_from_UTF8_to_UTF8_p(void)
{	
	START_TEST;

	char szSource[I18N_UCHAR_CAPACITY] = {0};
	char szDest[I18N_UCHAR_CAPACITY] = {0};

	memset(szSource, 0, sizeof(szSource));
	memset(szDest, 0, sizeof(szDest));
	snprintf(szSource, sizeof(szSource)-1, "Tizen");
	int nSourceLength = strlen((const char*)szSource);
	i18n_uchar ucharSource[I18N_UCHAR_CAPACITY] = {0,};
	int nUcharSourceLength = 0;
	int nDestLength = 0;
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;

	i18n_uchar *pRet = i18n_ustring_from_UTF8(ucharSource, I18N_UCHAR_CAPACITY, &nUcharSourceLength, szSource, nSourceLength,&ErrorCode);
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_from_UTF8", BaseUtilsGetError(ErrorCode));
	if ( pRet == NULL || i18n_ustring_get_length(ucharSource) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_from_UTF8 failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	ErrorCode = I18N_ERROR_NONE;
	char *pRetVal = i18n_ustring_to_UTF8(szDest, I18N_UCHAR_CAPACITY, &nDestLength, ucharSource, nUcharSourceLength,&ErrorCode);
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_to_UTF8", BaseUtilsGetError(ErrorCode));
	if (  pRetVal == NULL || strlen(szDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_to_UTF8 Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( strcmp((char *)szSource, (char *)szDest) != 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_to_UTF8 Failed as Source String and Destination String Contents Mismatched. Source String = %s, Destination String = %s,\\n", __LINE__, API_NAMESPACE, (char *)szSource, (char *)szDest);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Copies ustring to a byte string encoded in the default codepage.
/**
* @testcase				ITc_i18n_ustring_copy_au_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Copies ustring to a byte string encoded in the default codepage.
* @apitarget			i18n_ustring_copy_au
* @apicovered			i18n_ustring_copy_au
* @passcase				When i18n_ustring_copy_au is successful
* @failcase				If target i18n_ustring_copy_au fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_copy_au_p(void)
{	
	START_TEST;

	char szSource[I18N_UCHAR_CAPACITY] = {0};
	char szDest[I18N_UCHAR_CAPACITY] = {0};

	memset(szSource, 0, sizeof(szSource));
	memset(szDest, 0, sizeof(szDest));
	snprintf(szSource, sizeof(szSource)-1, "Tizen");
	i18n_uchar ucharSource[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar *pRet = i18n_ustring_copy_ua_n(ucharSource, szSource, strlen(szSource));
	if ( i18n_ustring_get_length(ucharSource) <= 0 || pRet == NULL )
	{
		FPRINTF("[Line : %d][%s]Pre-Requisite API i18n_ustring_copy_ua_n Failed during the testing of target API i18n_ustring_copy_au\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char *pRetVal = i18n_ustring_copy_au(szDest, ucharSource);
	if ( pRetVal == NULL || strlen(szDest) == 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_au Failed ,\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( strcmp((char *)szSource, (char *)szDest) != 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_au Failed as Source String and Destination String Contents Mismatched. Source String = %s, Destination String = %s,\\n", __LINE__, API_NAMESPACE, szSource, szDest);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Copies ustring to a byte string encoded in the default codepage. Copies at most n characters.
/**
* @testcase				ITc_i18n_ustring_copy_au_n_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Copies ustring to a byte string encoded in the default codepage. Copies at most n characters.
* @apitarget			i18n_ustring_copy_au_n
* @apicovered			i18n_ustring_copy_au_n
* @passcase				When i18n_ustring_copy_au_n is successful
* @failcase				If target i18n_ustring_copy_au_n fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_copy_au_n_p(void)
{	
	START_TEST;

	char szSource[I18N_UCHAR_CAPACITY] = {0};
	char szDest[I18N_UCHAR_CAPACITY] = {0};

	int nUcharSourceLength = 0;
	memset(szSource, 0, sizeof(szSource));
	memset(szDest, 0, sizeof(szDest));
	i18n_uchar ucharSource[I18N_UCHAR_CAPACITY] = {0,};
	snprintf(szSource, sizeof(szSource)-1, "Tizen");
	i18n_uchar *pRet = i18n_ustring_copy_ua_n(ucharSource, szSource, strlen(szSource));
	nUcharSourceLength = i18n_ustring_get_length(ucharSource);
	if ( nUcharSourceLength <= 0 || pRet == NULL )
	{
		FPRINTF("[Line : %d][%s]Pre-Requisite API i18n_ustring_copy_ua_n Failed during the testing of target API i18n_ustring_copy_au_n\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char *pRetVal = i18n_ustring_copy_au_n(szDest, ucharSource, nUcharSourceLength);
	if ( pRetVal == NULL || strlen(szDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_au_n Failed ,\\n", __LINE__, API_NAMESPACE);
		return 1;;
	}
	if ( strcmp((char *)szSource, (char *)szDest) != 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_au_n Failed as Source String and Destination String Contents Mismatched. Source String = %s, Destination String = %s,\\n", __LINE__, API_NAMESPACE, szSource, szDest);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Copies a byte string encoded in the default codepage to a ustring. Copies at most n characters.
/**
* @testcase				ITc_i18n_ustring_copy_ua_n_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Copies a byte string encoded in the default codepage to a ustring. Copies at most n characters.
* @apitarget			i18n_ustring_copy_ua_n
* @apicovered			i18n_ustring_copy_ua_n
* @passcase				When i18n_ustring_copy_ua_n is successful
* @failcase				If target i18n_ustring_copy_ua_n fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_copy_ua_n_p(void)
{	
	START_TEST;

	char szSource[I18N_UCHAR_CAPACITY] = {0};
	memset(szSource, 0, sizeof(szSource));
	snprintf(szSource, sizeof(szSource)-1, "Tizen");
	i18n_uchar ucharSource[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar ucharDest[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(ucharSource, szSource, strlen(szSource));


	int nUcharSourceLength = i18n_ustring_get_length(ucharSource);
	if ( nUcharSourceLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar *pRet = i18n_ustring_copy_ua_n(ucharDest, szSource, nUcharSourceLength);
	if ( pRet == NULL || i18n_ustring_get_length(ucharDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n Failed\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nResult = i18n_ustring_compare(ucharSource, ucharDest);
	if ( nResult != 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_compare failed, return value = %d\\n", __LINE__, API_NAMESPACE, nResult);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Copies a byte string encoded in the default codepage to a ustring.
/**
* @testcase				ITc_i18n_ustring_copy_ua_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Copies a byte string encoded in the default codepage to a ustring.
* @apitarget			i18n_ustring_copy_ua
* @apicovered			i18n_ustring_copy_ua
* @passcase				When i18n_ustring_copy_ua is successful
* @failcase				If target i18n_ustring_copy_ua fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_copy_ua_p(void)
{	
	START_TEST;

	char szSource[I18N_UCHAR_CAPACITY] = {0};
	memset(szSource, 0, sizeof(szSource));
	snprintf(szSource, sizeof(szSource)-1, "Tizen");
	i18n_uchar ucharSource[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar ucharDest[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua(ucharSource, szSource);

	i18n_uchar *pRet = i18n_ustring_copy_ua(ucharDest, szSource);
	if ( pRet == NULL || i18n_ustring_get_length(ucharDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nResult = i18n_ustring_compare(ucharSource, ucharDest);
	if ( nResult != 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_compare failed, return value = %d\\n", __LINE__, API_NAMESPACE, nResult);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Copies a ustring. Copies at most n characters.
/**
* @testcase				ITc_i18n_ustring_copy_n_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Copies a ustring. Adds a null terminator.  Copies at most n characters.
* @apitarget			i18n_ustring_copy_n
* @apicovered			i18n_ustring_copy_n
* @passcase				When i18n_ustring_copy_n is successful
* @failcase				If target i18n_ustring_copy_n fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_copy_n_p(void)
{	
	START_TEST;

	i18n_uchar uSourceStr[I18N_UCHAR_CAPACITY] = { 0, };
	i18n_uchar *pRet = i18n_ustring_copy_ua_n(uSourceStr, (char *)SOURCE_STRING, strlen(SOURCE_STRING));
	int nSourceLength = i18n_ustring_get_length(uSourceStr);
	if ( pRet == NULL || nSourceLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in pre-condition\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar uDestStr[I18N_UCHAR_CAPACITY] = { 0, };
	pRet = i18n_ustring_copy_n(uDestStr, uSourceStr, nSourceLength);
	if ( pRet == NULL || i18n_ustring_get_length(uDestStr) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_n failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int nResult = -1;
	nResult = i18n_ustring_compare(uSourceStr, uDestStr);
	if ( nResult != 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_compare failed, return value = %d\\n", __LINE__, API_NAMESPACE, nResult);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Upper case the character in a string.
/**
* @testcase				ITc_i18n_ustring_to_upper_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Upper case the character in a string.
* @apitarget			i18n_ustring_to_upper
* @apicovered			i18n_ustring_to_upper
* @passcase				When i18n_ustring_to_upper is successful
* @failcase				If target i18n_ustring_to_upper API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_to_upper_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, SOURCE_STRING, strlen(SOURCE_STRING));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar szDest[I18N_UCHAR_CAPACITY] = {0,};
	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	int32_t src_len = -1;
	const char *locale = NULL;
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;

	int nRetVal = i18n_ustring_to_upper(szDest, dest_capacity, szSrc, src_len, locale, &ErrorCode);
	if ( nRetVal < 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_to_upper failed, return value = %d\\n", __LINE__, API_NAMESPACE, nRetVal);
		return 1;
	}
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_to_upper", BaseUtilsGetError(ErrorCode));

	return 0;
}


//& type: auto
//& purpose: Count unicode code points in the length i18n_uchar code units of the string.
/**
* @testcase				ITc_i18n_ustring_count_char32_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Count unicode code points in the length i18n_uchar code units of the string.
* @apitarget			i18n_ustring_count_char32
* @apicovered			i18n_ustring_count_char32
* @passcase				When i18n_ustring_count_char32 is successful
* @failcase				If target i18n_ustring_count_char32 API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_count_char32_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, SOURCE_STRING, strlen(SOURCE_STRING));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int32_t length = -1;
	int nRetVal = i18n_ustring_count_char32(szSrc, length);
	if ( nRetVal < 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_count_char32 failed . Returned value =  %d\\n", __LINE__, API_NAMESPACE, nRetVal);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Check if the string contain more unicode code than a certain number.
/**
* @testcase				ITc_i18n_ustring_has_more_char32_than_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Check if the string contain more unicode code than a certain number.
* @apitarget			i18n_ustring_has_more_char32_than
* @apicovered			i18n_ustring_has_more_char32_than
* @passcase				When i18n_ustring_has_more_char32_than is successful
* @failcase				If target i18n_ustring_has_more_char32_than API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_has_more_char32_than_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, SOURCE_STRING, strlen(SOURCE_STRING));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int32_t length = -1;
	int32_t number = 1;
	bool bRetVal = i18n_ustring_has_more_char32_than(szSrc, length, number);
	if ( bRetVal == false )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_has_more_char32_than failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Concatenate two string.
/**
* @testcase				ITc_i18n_ustring_cat_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Concatenate two string.
* @apitarget			i18n_ustring_cat
* @apicovered			i18n_ustring_cat
* @passcase				When i18n_ustring_cat is successful
* @failcase				If target i18n_ustring_cat API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_cat_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, (char *)SOURCE_STRING, strlen((char *)SOURCE_STRING));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar szDest[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar *pRet = i18n_ustring_cat(szDest, szSrc);
	if ( i18n_ustring_get_length(szDest) <= 0 || pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_cat failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Concatenate two string.
/**
* @testcase				ITc_i18n_ustring_cat_n_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Concatenate two string.
* @apitarget			i18n_ustring_cat_n
* @apicovered			i18n_ustring_cat_n
* @passcase				When i18n_ustring_cat_n is successful
* @failcase				If target i18n_ustring_cat_n API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_cat_n_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, SOURCE_STRING, strlen(SOURCE_STRING));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar szDest[I18N_UCHAR_CAPACITY] = {0,};
	int32_t number = 5;
	i18n_uchar *pRet = i18n_ustring_cat_n(szDest, szSrc, number);
	if ( i18n_ustring_get_length(szDest) <= 0 || pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_cat_n failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& type: auto
//& purpose: Find the first occurrence of a substring in a string.
/**
* @testcase				ITc_i18n_ustring_string_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the first occurrence of a substring in a string.
* @apitarget			i18n_ustring_string
* @apicovered			i18n_ustring_string
* @passcase				When i18n_ustring_string is successful
* @failcase				If target i18n_ustring_string API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_string_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "XYZABC", strlen("XYZABC"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar szSubStr[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSubStr, "ABC", strlen("ABC"));
	if ( i18n_ustring_get_length(szSubStr) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar *pRet = i18n_ustring_string(szSrc, szSubStr);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_string failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Find the first occurrence of a substring in a string.
/**
* @testcase				ITc_i18n_ustring_find_first_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the first occurrence of a substring in a string.
* @apitarget			i18n_ustring_find_first
* @apicovered			i18n_ustring_find_first
* @passcase				When i18n_ustring_find_first is successful
* @failcase				If target i18n_ustring_find_first API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_find_first_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "XYZABC", strlen("XYZABC"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int32_t length = -1;
	i18n_uchar szSubStr[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSubStr, "ABC", strlen("ABC"));
	if ( i18n_ustring_get_length(szSubStr) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int32_t sub_length = -1;
	i18n_uchar *pRet = i18n_ustring_find_first(szSrc, length, szSubStr, sub_length);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_find_first failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Find the first occurrence of a BMP code point in a string.
/**
* @testcase				ITc_i18n_ustring_char_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the first occurrence of a BMP code point in a string.
* @apitarget			i18n_ustring_char
* @apicovered			i18n_ustring_char
* @passcase				When i18n_ustring_char is successful
* @failcase				If target i18n_ustring_char API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_char_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "XYZABC", strlen("XYZABC"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar szBMPPoint = 'A';
	i18n_uchar *pRet = i18n_ustring_char(szSrc, szBMPPoint);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_char failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Find the first occurrence of a code point in a string.
/**
* @testcase				ITc_i18n_ustring_char32_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the first occurrence of a code point in a string.
* @apitarget			i18n_ustring_char32
* @apicovered			i18n_ustring_char32
* @passcase				When i18n_ustring_char32 is successful
* @failcase				If target i18n_ustring_char32 API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_char32_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "XYZABC", strlen("XYZABC"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar szPoint = 'A';
	i18n_uchar *pRet = i18n_ustring_char32(szSrc, szPoint);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_char32 failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Find the last occurrence of a substring in a string.
/**
* @testcase				ITc_i18n_ustring_r_string_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the last occurrence of a substring in a string.
* @apitarget			i18n_ustring_r_string
* @apicovered			i18n_ustring_r_string
* @passcase				When i18n_ustring_r_string is successful
* @failcase				If target i18n_ustring_r_string API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_r_string_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "XYZABCQWEABC", strlen("XYZABCQWEABC"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar szSubStr[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSubStr, "ABC", strlen("ABC"));
	if ( i18n_ustring_get_length(szSubStr) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar *pRet = i18n_ustring_r_string(szSrc, szSubStr);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_r_string failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Find the last occurrence of a substring in a string.
/**
* @testcase				ITc_i18n_ustring_find_last_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the last occurrence of a substring in a string.
* @apitarget			i18n_ustring_find_last
* @apicovered			i18n_ustring_find_last
* @passcase				When i18n_ustring_find_last is successful
* @failcase				If target i18n_ustring_find_last API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_find_last_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "XYZABCQWEABC", strlen("XYZABCQWEABC"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar szSubStr[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSubStr, "ABC", strlen("ABC"));
	if ( i18n_ustring_get_length(szSubStr) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int32_t length = -1;
	int32_t sub_length = -1;
	i18n_uchar *pRet = i18n_ustring_find_last(szSrc, length, szSubStr, sub_length);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_find_last failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Find the last occurrence of a BMP code point in a string.
/**
* @testcase				ITc_i18n_ustring_r_char_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the last occurrence of a BMP code point in a string.
* @apitarget			i18n_ustring_r_char
* @apicovered			i18n_ustring_r_char
* @passcase				When i18n_ustring_r_char is successful
* @failcase				If target i18n_ustring_r_char API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_r_char_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "AXZABC", strlen("AXZABC"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar chBMPPoint =  'C';
	i18n_uchar *pRet = i18n_ustring_r_char(szSrc, chBMPPoint);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_r_char failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Find the last occurrence of a BMP code point in a string.
/**
* @testcase				ITc_i18n_ustring_r_char32_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the last occurrence of a BMP code point in a string.
* @apitarget			i18n_ustring_r_char32
* @apicovered			i18n_ustring_r_char32
* @passcase				When i18n_ustring_r_char32 is successful
* @failcase				If target i18n_ustring_r_char32 API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_r_char32_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "AXZABC", strlen("AXZABC"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar32 chBMPPoint = 'B';
	i18n_uchar *pRet = i18n_ustring_r_char32(szSrc, chBMPPoint);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_r_char32 failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Locate the first occurrence in the string string of any of the character in the string matche_set.
/**
* @testcase				ITc_i18n_ustring_pbrk_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Locate the first occurrence in the string string of any of the character in the string matche_set.
* @apitarget			i18n_ustring_pbrk
* @apicovered			i18n_ustring_pbrk
* @passcase				When i18n_ustring_pbrk is successful
* @failcase				If target i18n_ustring_pbrk API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_pbrk_p(void)
{	
	START_TEST;

	i18n_uchar string[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(string, "ABC3XYZ4", strlen("ABC3XYZ4"));
	if ( i18n_ustring_get_length(string) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar match_set[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(match_set, "34", strlen("34"));
	if ( i18n_ustring_get_length(match_set) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar *pRet = i18n_ustring_pbrk(string, match_set);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_pbrk failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns the number of consecutive character in string, beginning with the first, that do not occur somewhere in match set.
/**
* @testcase				ITc_i18n_ustring_cspn_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns the number of consecutive character in string, beginning with the first, that do not occur somewhere in match set.
* @apitarget			i18n_ustring_cspn
* @apicovered			i18n_ustring_cspn
* @passcase				When i18n_ustring_cspn is successful
* @failcase				If target i18n_ustring_cspn API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_cspn_p(void)
{	
	START_TEST;

	i18n_uchar string[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(string, "ABCXYZ01234", strlen("ABCXYZ01234"));
	if ( i18n_ustring_get_length(string) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar match_set[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(match_set, "015", strlen("015"));
	if ( i18n_ustring_get_length(match_set) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = i18n_ustring_cspn(string, match_set);
	if ( nRet == -1 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_cspn failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns the number of consecutive character in string, beginning with the first, that occur somewhere in match set.
/**
* @testcase				ITc_i18n_ustring_spn_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns the number of consecutive character in string, beginning with the first, that occur somewhere in match set.
* @apitarget			i18n_ustring_spn
* @apicovered			i18n_ustring_spn
* @passcase				When i18n_ustring_spn is successful
* @failcase				If target i18n_ustring_spn API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_spn_p(void)
{	
	START_TEST;

	i18n_uchar string[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(string, "ABCDEFGHXYZ01234", strlen("ABCDEFGHXYZ01234"));
	if ( i18n_ustring_get_length(string) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar match_set[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(match_set, "ABCD", strlen("ABCD"));
	if ( i18n_ustring_get_length(match_set) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = i18n_ustring_spn(string, match_set);
	if ( nRet == -1 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_spn failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: The string tokenizer API allows to break a string into tokens.
/**
* @testcase				ITc_i18n_ustring_tokenizer_r_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				The string tokenizer API allows to break a string into tokens.
* @apitarget			i18n_ustring_tokenizer_r
* @apicovered			i18n_ustring_tokenizer_r
* @passcase				When i18n_ustring_tokenizer_r is successful
* @failcase				If target i18n_ustring_tokenizer_r API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_tokenizer_r_p(void)
{	
	START_TEST;

	i18n_uchar src[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(src, "This-is-just-testing", strlen("This-is-just-testing"));
	if ( i18n_ustring_get_length(src) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar delim[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(delim, "-", strlen("-"));
	if ( i18n_ustring_get_length(delim) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar *save_state;
	i18n_uchar *pRet = i18n_ustring_tokenizer_r(src, delim, &save_state);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_tokenizer_r failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Compare two unicode string in code point order.
/**
* @testcase				ITc_i18n_ustring_compare_code_point_order_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compare two unicode string in code point order.
* @apitarget			i18n_ustring_compare_code_point_order
* @apicovered			i18n_ustring_compare_code_point_order
* @passcase				When i18n_ustring_compare_code_point_order is successful
* @failcase				If target i18n_ustring_compare_code_point_order API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_compare_code_point_order_p(void)
{	
	START_TEST;

	i18n_uchar s1[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s1, "ABCD", strlen("ABCD"));
	if ( i18n_ustring_get_length(s1) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar s2[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s2, "ADBC", strlen("ADBC")); 
	if ( i18n_ustring_get_length(s2) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = i18n_ustring_compare_code_point_order(s1, s2);
	if ( nRet == 0 )
	{
		FPRINTF("[Line : %d][%s] First string is equal to second one in code point order\\n", __LINE__, API_NAMESPACE);
	}
	else if ( nRet > 0 )
	{
		FPRINTF("[Line : %d][%s] First string is greater than second one in code point order\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] First string is less than second one in code point order\\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

//& type: auto
//& purpose: Compare two unicode string in binary order.
/**
* @testcase				ITc_i18n_ustring_compare_binary_order_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compare two unicode string in binary order.
* @apitarget			i18n_ustring_compare_binary_order
* @apicovered			i18n_ustring_compare_binary_order
* @passcase				When i18n_ustring_compare_binary_order is successful
* @failcase				If target i18n_ustring_compare_binary_order API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_compare_binary_order_p(void)
{	
	START_TEST;

	i18n_uchar s1[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s1, "ABCD", strlen("ABCD"));
	if ( i18n_ustring_get_length(s1) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar s2[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s2, "ADBC", strlen("ADBC"));
	if ( i18n_ustring_get_length(s2) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int32_t length1 = -1;
	int32_t length2 = -1;
	i18n_ubool code_point_order = false;
	int nRet = i18n_ustring_compare_binary_order(s1, length1, s2, length2, code_point_order);
	if ( nRet == 0 )
	{
		FPRINTF("[Line : %d][%s] First string is equal to second one in binary order\\n", __LINE__, API_NAMESPACE);
	}
	else if ( nRet > 0 )
	{
		FPRINTF("[Line : %d][%s] First string is greater than second one in binary order\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] First string is less than second one in binary order\\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

//& type: auto
//& purpose: Compare two string case-insensitively using full case folding.
/**
* @testcase				ITc_i18n_ustring_case_compare_with_length_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compare two string case-insensitively using full case folding.
* @apitarget			i18n_ustring_case_compare_with_length
* @apicovered			i18n_ustring_case_compare_with_length
* @passcase				When i18n_ustring_case_compare_with_length is successful
* @failcase				If target i18n_ustring_case_compare_with_length API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_case_compare_with_length_p(void)
{	
	START_TEST;

	i18n_uchar s1[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s1, "ABCD", strlen("ABCD"));
	if ( i18n_ustring_get_length(s1) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_uchar s2[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s2, "ADBC", strlen("ADBC"));
	if ( i18n_ustring_get_length(s2) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int32_t length1 = -1;
	int32_t length2 = -1;
	uint32_t options[] =
	{
		I18N_USTRING_U_FOLD_CASE_DEFAULT,
		I18N_USTRING_U_COMPARE_CODE_POINT_ORDER,
		I18N_USTRING_U_FOLD_CASE_EXCLUDE_SPECIAL_I
	};
	int nEnumSize = sizeof(options)/sizeof(options[0]);
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		int nRet = i18n_ustring_case_compare_with_length(s1, length1, s2, length2, options[nEnumCounter], &ErrorCode);
		PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_case_compare_with_length", BaseUtilsGetError(ErrorCode));
		if ( nRet == 0 )
		{
			FPRINTF("[Line : %d][%s] First string is equal to second one\\n", __LINE__, API_NAMESPACE);
		}
		else if ( nRet > 0 )
		{
			FPRINTF("[Line : %d][%s] First string is greater than second\\n", __LINE__, API_NAMESPACE);
		}
		else
		{
			FPRINTF("[Line : %d][%s] First string is less than second\\n", __LINE__, API_NAMESPACE);
		}
	}
	return 0;
}

//& type: auto
//& purpose: Compare two string for bitwise equally. Compare at most n character.
/**
* @testcase				ITc_i18n_ustring_compare_n_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compare two string for bitwise equally. Compare at most n character.
* @apitarget			i18n_ustring_compare_n
* @apicovered			i18n_ustring_compare_n
* @passcase				When i18n_ustring_compare_n is successful
* @failcase				If target i18n_ustring_compare_n API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_compare_n_p(void)
{	
	START_TEST;

	i18n_uchar s1[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s1, "ABCDEFGH113", strlen("ABCDEFGH113"));
	if ( i18n_ustring_get_length(s1) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar s2[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s2, "ABCD1234", strlen("ABCD1234"));
	if ( i18n_ustring_get_length(s2) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int32_t n = 4;
	int nRet = i18n_ustring_compare_n(s1, s2, n);
	if ( nRet == 0 )
	{
		FPRINTF("[Line : %d][%s] First string is equal to second one\\n", __LINE__, API_NAMESPACE);
	}
	else if ( nRet > 0 )
	{
		FPRINTF("[Line : %d][%s] First string is greater than second one\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] First string is less than second one\\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

//& type: auto
//& purpose: Compare two uni code string in code point order.
/**
* @testcase				ITc_i18n_ustring_compare_n_code_point_order_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compare two uni code string in code point order.
* @apitarget			i18n_ustring_compare_n_code_point_order
* @apicovered			i18n_ustring_compare_n_code_point_order
* @passcase				When i18n_ustring_compare_n_code_point_order is successful
* @failcase				If target i18n_ustring_compare_n_code_point_order API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_compare_n_code_point_order_p(void)
{	
	START_TEST;

	i18n_uchar s1[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s1, "ABCDEFGH113", strlen("ABCDEFGH113"));
	if ( i18n_ustring_get_length(s1) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar s2[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s2, "ABCD1234", strlen("ABCD1234"));
	if ( i18n_ustring_get_length(s2) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int32_t n = 4;
	int nRet = i18n_ustring_compare_n_code_point_order(s1, s2, n);
	if ( nRet == 0 )
	{
		FPRINTF("[Line : %d][%s] First string is equal to second one in code point order\\n", __LINE__, API_NAMESPACE);
	}
	else if ( nRet > 0 )
	{
		FPRINTF("[Line : %d][%s] First string is greater than second one in code point order\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] First string is less than second one in code point order\\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

//& type: auto
//& purpose: Compare two string case-insensitively using full case folding.
/**
* @testcase				ITc_i18n_ustring_case_compare_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compare two string case-insensitively using full case folding.
* @apitarget			i18n_ustring_case_compare
* @apicovered			i18n_ustring_case_compare
* @passcase				When i18n_ustring_case_compare is successful
* @failcase				If target i18n_ustring_case_compare API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_case_compare_p(void)
{	
	START_TEST;


	i18n_uchar s1[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s1, "ABCDE", strlen("ABCDE"));
	if ( i18n_ustring_get_length(s1) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar s2[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s2, "ABDCE", strlen("ABDCE"));
	if ( i18n_ustring_get_length(s2) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	uint32_t options[] = {I18N_USTRING_U_FOLD_CASE_DEFAULT, I18N_USTRING_U_COMPARE_CODE_POINT_ORDER,
		I18N_USTRING_U_FOLD_CASE_EXCLUDE_SPECIAL_I};
	int nEnumSize = sizeof(options)/sizeof(options[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{	
		int nRet = i18n_ustring_case_compare(s1, s2, options[nEnumCounter]);
		if ( nRet == 0 )
		{
			FPRINTF("[Line : %d][%s] First string is equal to second one\\n", __LINE__, API_NAMESPACE);
		}
		else if ( nRet > 0 )
		{
			FPRINTF("[Line : %d][%s] First string is greater than second one\\n", __LINE__, API_NAMESPACE);
		}
		else
		{
			FPRINTF("[Line : %d][%s] First string is less than second one\\n", __LINE__, API_NAMESPACE);
		}
	}
	return 0;
}

//& type: auto
//& purpose: Compare two string case-insensitively using full case folding.
/**
* @testcase				ITc_i18n_ustring_case_compare_n_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compare two string case-insensitively using full case folding.
* @apitarget			i18n_ustring_case_compare_n
* @apicovered			i18n_ustring_case_compare_n
* @passcase				When i18n_ustring_case_compare_n is successful
* @failcase				If target i18n_ustring_case_compare_n API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_case_compare_n_p(void)
{	
	START_TEST;

	i18n_uchar s1[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s1, "ABCDE234", strlen("ABCDE234"));
	if ( i18n_ustring_get_length(s1) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar s2[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s2, "ABCD1234", strlen("ABCD1234"));
	if ( i18n_ustring_get_length(s2) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	uint32_t options[] = {I18N_USTRING_U_FOLD_CASE_DEFAULT, I18N_USTRING_U_COMPARE_CODE_POINT_ORDER,
		I18N_USTRING_U_FOLD_CASE_EXCLUDE_SPECIAL_I};
	int nEnumSize = sizeof(options)/sizeof(options[0]);
	int32_t n = 4;
	int nEnumCounter = 0;
	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{	
		int nRet = i18n_ustring_case_compare_n(s1, s2, n, options[nEnumCounter]);
		if ( nRet == 0 )
		{
			FPRINTF("[Line : %d][%s] First string is equal to second one\\n", __LINE__, API_NAMESPACE);
		}
		else if ( nRet > 0 )
		{
			FPRINTF("[Line : %d][%s] First string is greater than second one\\n", __LINE__, API_NAMESPACE);
		}
		else
		{
			FPRINTF("[Line : %d][%s] First string is less than second one\\n", __LINE__, API_NAMESPACE);
		}
	}
	return 0;
}

//& type: auto
//& purpose: Compare two string case-insensitively using full case folding.
/**
* @testcase				ITc_i18n_ustring_mem_case_compare_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compare two string case-insensitively using full case folding.
* @apitarget			i18n_ustring_mem_case_compare
* @apicovered			i18n_ustring_mem_case_compare
* @passcase				When i18n_ustring_mem_case_compare is successful
* @failcase				If target i18n_ustring_mem_case_compare API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_mem_case_compare_p(void)
{	
	START_TEST;

	i18n_uchar s1[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s1, "ABCDE234", strlen("ABCDE234"));
	if ( i18n_ustring_get_length(s1) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar s2[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s2, "ABCD1234", strlen("ABCD1234"));
	if ( i18n_ustring_get_length(s2) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	uint32_t options[] = {I18N_USTRING_U_FOLD_CASE_DEFAULT, I18N_USTRING_U_COMPARE_CODE_POINT_ORDER,
		I18N_USTRING_U_FOLD_CASE_EXCLUDE_SPECIAL_I};
	int nEnumSize = sizeof(options)/sizeof(options[0]);
	int32_t n = 4;
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{	
		int nRet = i18n_ustring_mem_case_compare(s1, s2, n, options[nEnumCounter]);
		if ( nRet == 0 )
		{
			FPRINTF("[Line : %d][%s] First string is equal to second one\\n", __LINE__, API_NAMESPACE);
		}
		else if ( nRet > 0 )
		{
			FPRINTF("[Line : %d][%s] First string is greater than second one\\n", __LINE__, API_NAMESPACE);
		}
		else
		{
			FPRINTF("[Line : %d][%s] First string is less than second one\\n", __LINE__, API_NAMESPACE);
		}
	}
	return 0;
}

//& type: auto
//& purpose: Synonym for memcpy but with i18n_uchar only.
/**
* @testcase				ITc_i18n_ustring_mem_copy_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Synonym for memcpy but with i18n_uchar only.
* @apitarget			i18n_ustring_mem_copy
* @apicovered			i18n_ustring_mem_copy
* @passcase				When i18n_ustring_mem_copy is successful
* @failcase				If target i18n_ustring_mem_copy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_mem_copy_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "ABCDE234", strlen("ABCDE234"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar szDest[I18N_UCHAR_CAPACITY] = {0,};
	int32_t count = 4;
	i18n_uchar *pRet = i18n_ustring_mem_copy(szDest, szSrc, count);
	if ( pRet == NULL || i18n_ustring_get_length(szDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_mem_copy failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Synonym for memmove but with i18n_uchar only.
/**
* @testcase				ITc_i18n_ustring_mem_move_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Synonym for memmove but with i18n_uchar only.
* @apitarget			i18n_ustring_mem_move
* @apicovered			i18n_ustring_mem_move
* @passcase				When i18n_ustring_mem_move is successful
* @failcase				If target i18n_ustring_mem_move API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_mem_move_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "ABCDE234", strlen("ABCDE234"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar szDest[I18N_UCHAR_CAPACITY] = {0,};
	int32_t count = 4;
	i18n_uchar *pRet = i18n_ustring_mem_move(szDest, szSrc, count);
	if ( pRet == NULL || i18n_ustring_get_length(szDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_mem_move failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Initialize count characters of dest to c.
/**
* @testcase				ITc_i18n_ustring_mem_set_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Initialize count characters of dest to c.
* @apitarget			i18n_ustring_mem_set
* @apicovered			i18n_ustring_mem_set
* @passcase				When i18n_ustring_mem_set is successful
* @failcase				If target i18n_ustring_mem_set API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_mem_set_p(void)
{	
	START_TEST;

	const i18n_uchar c = 'a';
	int32_t count = 5;
	i18n_uchar szDest[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szDest, "ABCDE234", strlen("ABCDE234"));
	if ( i18n_ustring_get_length(szDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar *pRet = i18n_ustring_mem_set(szDest, c, count);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_mem_set failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Compare the first count i18n_uchar of each buffer.
/**
* @testcase				ITc_i18n_ustring_mem_compare_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compare the first count i18n_uchar of each buffer.
* @apitarget			i18n_ustring_mem_compare
* @apicovered			i18n_ustring_mem_compare
* @passcase				When i18n_ustring_mem_compare is successful
* @failcase				If target i18n_ustring_mem_compare API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_mem_compare_p(void)
{	
	START_TEST;

	i18n_uchar s1[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s1, "ABCDEFGHI", strlen("ABCDEFGHI"));
	if ( i18n_ustring_get_length(s1) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar s2[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s2, "ABCDEXYZ12", strlen("ABCDEXYZ12"));
	if ( i18n_ustring_get_length(s2) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int32_t count = 5;
	int nRet = i18n_ustring_mem_compare(s1, s2, count);
	if ( nRet == 0 )
	{
		FPRINTF("[Line : %d][%s] First string is equal to second one\\n", __LINE__, API_NAMESPACE);
	}
	else if ( nRet > 0 )
	{
		FPRINTF("[Line : %d][%s] First string is greater than second one\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] First string is less than second one\\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

//& type: auto
//& purpose: Compare two uni code string in code point order.
/**
* @testcase				ITc_i18n_ustring_mem_compare_code_point_order_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Compare two uni code string in code point order.
* @apitarget			i18n_ustring_mem_compare_code_point_order
* @apicovered			i18n_ustring_mem_compare_code_point_order
* @passcase				When i18n_ustring_mem_compare_code_point_order is successful
* @failcase				If target i18n_ustring_mem_compare_code_point_order API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_mem_compare_code_point_order_p(void)
{	
	START_TEST;

	i18n_uchar s1[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s1, "ABCD123XYZI", strlen("ABCD123XYZI"));
	if ( i18n_ustring_get_length(s1) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar s2[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s2, "ABCDEXYZ12", strlen("ABCDEXYZ12"));
	if ( i18n_ustring_get_length(s2) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int32_t count = 8;
	int nRet = i18n_ustring_mem_compare_code_point_order(s1, s2, count);
	if ( nRet == 0 )
	{
		FPRINTF("[Line : %d][%s] First string is equal to second one\\n", __LINE__, API_NAMESPACE);
	}
	else if ( nRet > 0 )
	{
		FPRINTF("[Line : %d][%s] First string is greater than second one\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] First string is less than second one\\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

//& type: auto
//& purpose: Find the first occurrence of a BMP code point in a string.
/**
* @testcase				ITc_i18n_ustring_mem_char_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the first occurrence of a BMP code point in a string.
* @apitarget			i18n_ustring_mem_char
* @apicovered			i18n_ustring_mem_char
* @passcase				When i18n_ustring_mem_char is successful
* @failcase				If target i18n_ustring_mem_char API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_mem_char_p(void)
{	
	START_TEST;

	i18n_uchar s[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s, "ABCDE12FGH", strlen("ABCDE12FGH"));
	int32_t count = i18n_ustring_get_length(s);
	if ( count <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar c = '1';
	i18n_uchar *pRet = i18n_ustring_mem_char(s, c, count);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_mem_char failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Find the first occurrence of a code point in a string.
/**
* @testcase				ITc_i18n_ustring_mem_char32_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the first occurrence of a code point in a string.
* @apitarget			i18n_ustring_mem_char32
* @apicovered			i18n_ustring_mem_char32
* @passcase				When i18n_ustring_mem_char32 is successful
* @failcase				If target i18n_ustring_mem_char32 API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_mem_char32_p(void)
{	
	START_TEST;

	i18n_uchar s[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s, "ABCD13XYZ", strlen("ABCD13XYZ"));
	int32_t count = i18n_ustring_get_length(s);
	if ( count <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar c = 'D';
	i18n_uchar *pRet = i18n_ustring_mem_char32(s, c, count);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_mem_char32 failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Find the last occurrence of a BMP code point in a string.
/**
* @testcase				ITc_i18n_ustring_mem_r_char_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the last occurrence of a BMP code point in a string.
* @apitarget			i18n_ustring_mem_r_char
* @apicovered			i18n_ustring_mem_r_char
* @passcase				When i18n_ustring_mem_r_char is successful
* @failcase				If target i18n_ustring_mem_r_char API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_mem_r_char_p(void)
{	
	START_TEST;

	i18n_uchar s[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s, "XYZ1ABCD", strlen("XYZ1ABCD"));
	int32_t count = i18n_ustring_get_length(s);
	if ( count <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar c = 'Y';
	i18n_uchar *pRet = i18n_ustring_mem_r_char(s, c, count);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_mem_r_char failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Find the last occurrence of a code point in a string.
/**
* @testcase				ITc_i18n_ustring_mem_r_char32_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Find the last occurrence of a code point in a string.
* @apitarget			i18n_ustring_mem_r_char32
* @apicovered			i18n_ustring_mem_r_char32
* @passcase				When i18n_ustring_mem_r_char32 is successful
* @failcase				If target i18n_ustring_mem_r_char32 API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_mem_r_char32_p(void)
{	
	START_TEST;

	i18n_uchar s[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(s, "ABCD13XYZ", strlen("ABCD13XYZ"));
	int32_t count = i18n_ustring_get_length(s);
	if ( count <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar c = 'X';
	i18n_uchar *pRet = i18n_ustring_mem_r_char32(s, c, count);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_mem_r_char32 failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Unescape a string of characters and write the resulting uni code characters to the destination buffer.
/**
* @testcase				ITc_i18n_ustring_unescape_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Unescape a string of characters and write the resulting uni code characters to the destination buffer.
* @apitarget			i18n_ustring_unescape
* @apicovered			i18n_ustring_unescape
* @passcase				When i18n_ustring_unescape is successful
* @failcase				If target i18n_ustring_unescape API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_unescape_p(void)
{	
	START_TEST;


	const char szSrc[I18N_UCHAR_CAPACITY] = "[a-z]";
	i18n_uchar szDest[I18N_UCHAR_CAPACITY] = {'\0'};
	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	int nRet = i18n_ustring_unescape(szSrc, szDest, dest_capacity);
	FPRINTF("[Line : %d][%s] Length of unescape string is = %d\n",__LINE__, API_NAMESPACE, nRet);

	return 0;
}

//& type: auto
//& purpose: Unescape a single sequence.
/**
* @testcase				ITc_i18n_ustring_unescape_at_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Unescape a single sequence.
* @apitarget			i18n_ustring_unescape_at
* @apicovered			i18n_ustring_unescape_at
* @passcase				When i18n_ustring_unescape_at is successful
* @failcase				If target i18n_ustring_unescape_at API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_unescape_at_p(void)
{	
	START_TEST;

	int32_t dest_capacity = BUFFER;
	g_UnescapeCallback = false;
	int nRet = i18n_ustring_unescape_at(UStringUnescapeCharAtCB, &g_Offset, dest_capacity, g_pContext);
	if ( nRet == -1 || g_UnescapeCallback == false )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_unescape_at failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Lower case the characters in a string.
/**
* @testcase				ITc_i18n_ustring_to_lower_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Lower case the characters in a string.
* @apitarget			i18n_ustring_to_lower
* @apicovered			i18n_ustring_to_lower
* @passcase				When i18n_ustring_to_lower is successful
* @failcase				If target i18n_ustring_to_lower API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_to_lower_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "ABCDXYZ", strlen("ABCDXYZ"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int32_t src_len = -1;
	i18n_uchar szDest[I18N_UCHAR_CAPACITY] = {0,};
	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	const char *locale = NULL;
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;
	int nRet = i18n_ustring_to_lower(szDest, dest_capacity, szSrc, src_len, locale, &ErrorCode);
	if ( nRet < 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_to_lower failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_to_lower", BaseUtilsGetError(ErrorCode));
	return 0;
}

//& type: auto
//& purpose: Case-folds the character in a string.
/**
* @testcase				ITc_i18n_ustring_fold_case_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Case-folds the character in a string.
* @apitarget			i18n_ustring_fold_case
* @apicovered			i18n_ustring_fold_case
* @passcase				When i18n_ustring_fold_case is successful
* @failcase				If target i18n_ustring_fold_case API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_fold_case_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "ABCDXYZ", strlen("ABCDXYZ"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int32_t src_len = -1;
	i18n_uchar szDest[I18N_UCHAR_CAPACITY] = {0,};
	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;

	uint32_t options[] = {I18N_USTRING_U_FOLD_CASE_DEFAULT, I18N_USTRING_U_FOLD_CASE_EXCLUDE_SPECIAL_I};
	int nEnumSize = sizeof(options)/sizeof(options[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter  < nEnumSize; nEnumCounter++ )
	{
		int nRet = i18n_ustring_fold_case(szDest, dest_capacity, szSrc, src_len, options[nEnumCounter], &ErrorCode);
		if ( nRet < 0 )
		{
			FPRINTF("[Line : %d][%s] i18n_ustring_fold_case failed \n",__LINE__, API_NAMESPACE);
			return 1;;
		}
		PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_fold_case", BaseUtilsGetError(ErrorCode));
	}
	return 0;
}

//& type: auto
//& purpose: Convert a UTF-16 string to wchar_t string.
/**
* @testcase				ITc_i18n_ustring_to_WCS_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Convert a UTF-16 string to wchar_t string.
* @apitarget			i18n_ustring_to_WCS
* @apicovered			i18n_ustring_to_WCS
* @passcase				When i18n_ustring_to_WCS is successful
* @failcase				If target i18n_ustring_to_WCS API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_to_WCS_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "ABCDXYZ", strlen("ABCDXYZ"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int32_t src_len = -1;
	wchar_t szDest[I18N_UCHAR_CAPACITY] = {'\0'};
	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	int32_t dest_len;
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;

	wchar_t *wpRet = i18n_ustring_to_WCS(szDest, dest_capacity, &dest_len, szSrc, src_len, &ErrorCode);
	if ( wpRet == NULL || wcslen(szDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_to_WCS failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_to_WCS", BaseUtilsGetError(ErrorCode));
	return 0;
}

//& type: auto
//& purpose: Convert a wchar_t  string to UTF-16 string.
/**
* @testcase				ITc_i18n_ustring_from_WCS_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Convert a wchar_t  string to UTF-16 string.
* @apitarget			i18n_ustring_from_WCS
* @apicovered			i18n_ustring_from_WCS
* @passcase				When i18n_ustring_from_WCS is successful
* @failcase				If target i18n_ustring_from_WCS API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_from_WCS_p(void)
{	
	START_TEST;

	const wchar_t szSrc[I18N_UCHAR_CAPACITY] = L"ABCDXYZ";
	int32_t src_len = -1;
	i18n_uchar  szDest[I18N_UCHAR_CAPACITY] = {0,};
	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	int32_t dest_len;
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;

	i18n_uchar *pRet = i18n_ustring_from_WCS(szDest, dest_capacity, &dest_len, szSrc, src_len, &ErrorCode);
	if ( pRet == NULL || i18n_ustring_get_length(szDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_from_WCS failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_from_WCS", BaseUtilsGetError(ErrorCode));
	return 0;
}

//& type: auto
//& purpose: Convert a UTF-16  string to UTF-8.
/**
* @testcase				ITc_i18n_ustring_to_UTF8_with_sub_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Convert a UTF-16  string to UTF-8.
* @apitarget			i18n_ustring_to_UTF8_with_sub
* @apicovered			i18n_ustring_to_UTF8_with_sub
* @passcase				When i18n_ustring_to_UTF8_with_sub is successful
* @failcase				If target i18n_ustring_to_UTF8_with_sub API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_to_UTF8_with_sub_p(void)
{	
	START_TEST;

	char  szDest[I18N_UCHAR_CAPACITY] = {'\0'};
	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	int32_t dest_len;
	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "ABCDXYZ", strlen("ABCDXYZ"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int32_t src_len = -1;
	i18n_uchar32 sub_char = 0xFFFD;
	int32_t num_substitutions;
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;

	char *pRet = i18n_ustring_to_UTF8_with_sub(szDest, dest_capacity, &dest_len, szSrc, src_len, sub_char, &num_substitutions, &ErrorCode);
	if ( pRet == NULL || strlen(szDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_to_UTF8_with_sub failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_to_UTF8_with_sub", BaseUtilsGetError(ErrorCode));
	return 0;
}

//& type: auto
//& purpose: Convert a UTF-8 string to UTF-16.
/**
* @testcase				ITc_i18n_ustring_from_UTF8_with_sub_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Convert a UTF-8  string to UTF-16.
* @apitarget			i18n_ustring_from_UTF8_with_sub
* @apicovered			i18n_ustring_from_UTF8_with_sub
* @passcase				When i18n_ustring_from_UTF8_with_sub is successful
* @failcase				If target i18n_ustring_from_UTF8_with_sub API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_from_UTF8_with_sub_p(void)
{	
	START_TEST;

	i18n_uchar  szDest[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar32 sub_char = 0xFFFD;
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;

	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	int32_t dest_len;
	int32_t src_len = -1;
	int32_t num_substitutions;
	const char szSrc[I18N_UCHAR_CAPACITY] = "ABCDXYZ";

	i18n_uchar *pRet = i18n_ustring_from_UTF8_with_sub(szDest, dest_capacity, &dest_len, szSrc, src_len, sub_char, &num_substitutions, &ErrorCode);
	if ( pRet == NULL || i18n_ustring_get_length(szDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_from_UTF8_with_sub failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_from_UTF8_with_sub", BaseUtilsGetError(ErrorCode));

	return 0;
}

//& type: auto
//& purpose: Convert a UTF-8 string to UTF-16.
/**
* @testcase				ITc_i18n_ustring_from_UTF8_lenient_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Convert a UTF-8  string to UTF-16.
* @apitarget			i18n_ustring_from_UTF8_lenient
* @apicovered			i18n_ustring_from_UTF8_lenient
* @passcase				When i18n_ustring_from_UTF8_lenient is successful
* @failcase				If target i18n_ustring_from_UTF8_lenient API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_from_UTF8_lenient_p(void)
{	
	START_TEST;

	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;
	i18n_uchar  szDest[I18N_UCHAR_CAPACITY] = {0,};

	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	int32_t dest_len;
	int32_t src_len = -1;
	const char szSrc[I18N_UCHAR_CAPACITY] = "ABCDXYZ";

	i18n_uchar *pRet = i18n_ustring_from_UTF8_lenient(szDest, dest_capacity, &dest_len, szSrc, src_len, &ErrorCode);
	if ( pRet == NULL || i18n_ustring_get_length(szDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_from_UTF8_lenient failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_from_UTF8_lenient", BaseUtilsGetError(ErrorCode));
	return 0;
}

//& type: auto
//& purpose: Convert a UTF-16 string to UTF-32.
/**
* @testcase				ITc_i18n_ustring_to_UTF32_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Convert a UTF-16 string to UTF-32.
* @apitarget			i18n_ustring_to_UTF32
* @apicovered			i18n_ustring_to_UTF32
* @passcase				When i18n_ustring_to_UTF32 is successful
* @failcase				If target i18n_ustring_to_UTF32 API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_to_UTF32_p(void)
{	
	START_TEST;

	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar32 szDest[I18N_UCHAR_CAPACITY] = {0,};
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;

	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	int32_t dest_len;
	int32_t src_len = -1;

	i18n_ustring_copy_ua_n(szSrc, "ABCDXYZ", strlen("ABCDXYZ"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}


	i18n_uchar32 *pRet = i18n_ustring_to_UTF32(szDest, dest_capacity, &dest_len, szSrc, src_len, &ErrorCode);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_to_UTF32 failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_to_UTF32", BaseUtilsGetError(ErrorCode));
	return 0;
}

//& type: auto
//& purpose: Convert a UTF-32 string to UTF-16.
/**
* @testcase				ITc_i18n_ustring_from_UTF32_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Convert a UTF-32 string to UTF-16.
* @apitarget			i18n_ustring_from_UTF32
* @apicovered			i18n_ustring_from_UTF32
* @passcase				When i18n_ustring_from_UTF32 is successful
* @failcase				If target i18n_ustring_from_UTF32 API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_from_UTF32_p(void)
{	
	START_TEST;

	i18n_uchar szTemp[I18N_UCHAR_CAPACITY] = {0,};
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;
	i18n_uchar  szDest[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar32 szSrc[I18N_UCHAR_CAPACITY] = {0,};

	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	int32_t dest_len;
	int32_t nDestLen;
	int32_t src_len = -1;

	i18n_ustring_copy_ua_n(szTemp, "ABCDXYZ", strlen("ABCDXYZ"));
	if ( i18n_ustring_get_length(szTemp) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_ustring_to_UTF32(szSrc, I18N_UCHAR_CAPACITY, &nDestLen, szTemp, i18n_ustring_get_length(szTemp), &ErrorCode);
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_to_UTF32", BaseUtilsGetError(ErrorCode));

	i18n_uchar *pRet = i18n_ustring_from_UTF32(szDest, dest_capacity, &dest_len, szSrc, src_len, &ErrorCode);
	if ( pRet == NULL || i18n_ustring_get_length(szDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_from_UTF32 failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_from_UTF32", BaseUtilsGetError(ErrorCode));
	return 0;
}

//& type: auto
//& purpose: Convert a UTF-32 string to UTF-16.
/**
* @testcase				ITc_i18n_ustring_from_UTF32_with_sub_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Convert a UTF-32 string to UTF-16.
* @apitarget			i18n_ustring_from_UTF32_with_sub
* @apicovered			i18n_ustring_from_UTF32_with_sub
* @passcase				When i18n_ustring_from_UTF32_with_sub is successful
* @failcase				If target i18n_ustring_from_UTF32_with_sub API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_from_UTF32_with_sub_p(void)
{	
	START_TEST;

	i18n_uchar szTemp[I18N_UCHAR_CAPACITY] = {0,};
	i18n_uchar32 szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;
	i18n_uchar32 sub_char = (i18n_uchar32)0xFFFD;
	i18n_uchar  szDest[I18N_UCHAR_CAPACITY] = {0,};

	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	int32_t dest_len;
	int32_t nDestLen;
	int32_t src_len = -1;
	int32_t num_substituitions;

	i18n_ustring_copy_ua_n(szTemp, "ABCDXYZ", strlen("ABCDXYZ"));
	if ( i18n_ustring_get_length(szTemp) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_ustring_to_UTF32(szSrc, I18N_UCHAR_CAPACITY, &nDestLen, szTemp, i18n_ustring_get_length(szTemp), &ErrorCode);
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_to_UTF32", BaseUtilsGetError(ErrorCode));

	i18n_uchar *pRet = i18n_ustring_from_UTF32_with_sub(szDest, dest_capacity, &dest_len, szSrc, src_len, sub_char, &num_substituitions, &ErrorCode);
	if ( pRet == NULL || i18n_ustring_get_length(szDest) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_from_UTF32_with_sub failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_from_UTF32_with_sub", BaseUtilsGetError(ErrorCode));

	return 0;
}

//& type: auto
//& purpose: Convert a UTF-16 string to UTF-32.
/**
* @testcase				ITc_i18n_ustring_to_UTF32_with_sub_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Convert a UTF-16 string to UTF-32.
* @apitarget			i18n_ustring_to_UTF32_with_sub
* @apicovered			i18n_ustring_to_UTF32_with_sub
* @passcase				When i18n_ustring_to_UTF32_with_sub is successful
* @failcase				If target i18n_ustring_to_UTF32_with_sub API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ustring_to_UTF32_with_sub_p(void)
{	
	START_TEST;

	i18n_uchar32 szDest[I18N_UCHAR_CAPACITY] = {0,};
	int32_t dest_capacity = I18N_UCHAR_CAPACITY;
	int32_t dest_len;
	i18n_uchar szSrc[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szSrc, "ABCDXYZ", strlen("ABCDXYZ"));
	if ( i18n_ustring_get_length(szSrc) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition\n",__LINE__, API_NAMESPACE);
		return 1;
	}
	int32_t src_len = -1;
	i18n_uchar32 sub_char = 0xFFFD;
	int32_t num_substituitions;
	i18n_error_code_e ErrorCode = I18N_ERROR_NONE;

	i18n_uchar32 *pRet = i18n_ustring_to_UTF32_with_sub(szDest, dest_capacity, &dest_len, szSrc, src_len, (i18n_uchar32)sub_char, &num_substituitions, &ErrorCode);
	if ( pRet == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_to_UTF32_with_sub failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PRINT_RESULT(I18N_ERROR_NONE, ErrorCode, "i18n_ustring_to_UTF32_with_sub", BaseUtilsGetError(ErrorCode));

	return 0;
}

//& type: auto
//& purpose: Titlecases a string.
/**
 * @testcase 				ITc_i18n_ustring_to_title_new_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Titlecasing uses a break iterator to find the first characters of wordsthat are to be titlecased.
 * @scenario				Titlecases a string.					
 * @api-covered				i18n_ustring_to_title_new, i18n_ustring_copy_ua_n
 * @pass-case				When i18n_ustring_to_title_new is successful.
 * @fail-case				If target i18n_ustring_to_title_new fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_ustring_to_title_new_p(void)
{	
	START_TEST;
	i18n_uchar uSourceStr[I18N_UCHAR_CAPACITY] = { 0, };
	
	i18n_uchar *pRet = i18n_ustring_copy_ua_n(uSourceStr, (char *)SOURCE_STRING, strlen(SOURCE_STRING));
	int32_t nSourceLength = i18n_ustring_get_length(uSourceStr);

	if(pRet == NULL || nSourceLength <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua_n failed in precondition \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	const char *pszDefaultLocale = I18N_ULOCALE_US;
	i18n_uchar uDestStr[I18N_UCHAR_CAPACITY] = { 0, };
	
	i18n_ustring_to_title_new(uDestStr, I18N_UCHAR_CAPACITY, uSourceStr, nSourceLength, NULL, pszDefaultLocale);
	int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ustring_to_title_new", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Shapes Arabic text on a character basis
/**
* @testcase				ITc_i18n_ushape_shape_arabic_p
* @since_tizen 			3.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Shapes Arabic text on a character basis
* @apitarget			i18n_ushape_shape_arabic		
* @apicovered			i18n_ushape_shape_arabic
* @passcase				I18N_ERROR_NONE returned by i18n_ushape_shape_arabic
* @failcase				I18N_ERROR_NONE not returned by i18n_ushape_shape_arabic
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ushape_shape_arabic_p(void)
{	
	START_TEST;
	
	i18n_uchar en_digits[] = {
        0x30,   /* Unicode Digit Zero */
        0x31,   /* Unicode Digit One */
        0x32,   /* Unicode Digit Two */
        0x33,   /* Unicode Digit Three */
        0x34,   /* Unicode Digit Four */
        0x35,   /* Unicode Digit Five */
        0x36,   /* Unicode Digit Six */
        0x37,   /* Unicode Digit Seven */
        0x38,   /* Unicode Digit Eight */
        0x39,   /* Unicode Digit Nine */
        0
	};

	//Target API
	
	i18n_uchar dest[12];
    int32_t nOutDestLen;
	int32_t nSourceLen = sizeof(en_digits)/sizeof((en_digits)[0]);
	int32_t nDestLen = sizeof(dest)/sizeof((dest)[0]);

    int nRet = i18n_ushape_shape_arabic(en_digits, nSourceLen, I18N_USHAPE_DIGITS_NOOP, nDestLen, dest, &nOutDestLen);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ushape_shape_arabic", BaseUtilsGetError(nRet));
	PRINT_RESULT(nSourceLen, nOutDestLen, "i18n_ushape_shape_arabic", "Length of source and destination mismatch");

	
	nRet = i18n_ushape_shape_arabic(en_digits, nSourceLen, I18N_USHAPE_DIGITS_EN2AN, nDestLen, dest, &nOutDestLen);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ushape_shape_arabic", BaseUtilsGetError(nRet));
	PRINT_RESULT(nSourceLen, nOutDestLen, "i18n_ushape_shape_arabic", "Length of source and destination mismatch");

	
	nRet = i18n_ushape_shape_arabic(en_digits, nSourceLen, I18N_USHAPE_DIGITS_AN2EN, nDestLen, dest, &nOutDestLen);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ushape_shape_arabic", BaseUtilsGetError(nRet));
	PRINT_RESULT(nSourceLen, nOutDestLen, "i18n_ushape_shape_arabic", "Length of source and destination mismatch");

	
    return 0;
}
/** @} */
/** @} */
