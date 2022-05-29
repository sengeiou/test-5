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

const i18n_uchar ustring_1[] = { 't', 0 }, ustring_2[] = { 'i', 0 }, ustring_3[] = { 'z', 0 }, ustring_4[] = { 'e', 0 }, ustring_5[] = { 'n', 0 };
const i18n_uchar* ustrings[] = { ustring_1, ustring_2, ustring_3, ustring_4, ustring_5 };
i18n_uenumeration_h g_uenum = NULL;


/**
* @function 		ITs_base_utils_enumeration_startup
* @description	 	Called before each test. Create the i18n_uenumeration_h handle
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_enumeration_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	int nRetVal = i18n_uenumeration_uchar_strings_enumeration_create(ustrings, sizeof(ustrings)/sizeof(ustrings[0]), &g_uenum);
    if (nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] i18n_uenumeration_uchar_strings_enumeration_create failed in startup. Error returned = %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
		g_bBaseUtilsInitFlag = false;
		return;
	}
	g_bBaseUtilsInitFlag = true;
	return;
}
/**
* @function 		ITs_base_utils_enumeration_cleanup
* @description	 	Called after each test. Destroy the created i18n_uenumeration_h handle
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_enumeration_cleanup(void)
{
	int nRetVal = i18n_uenumeration_destroy(g_uenum);
    g_uenum = NULL;
	if(nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] i18n_uenumeration_destroy failed in cleanup. Error returned = %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
	}
	g_bBaseUtilsInitFlag = false;
	return;
}

//& type: auto
//& purpose: Create/Destroy an i18n_uenumeration_h from const i18n_uchar* strings.
/**
* @testcase				ITc_i18n_uenumeration_uchar_strings_enumeration_create_destroy_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create an i18n_uenumeration_h handle.\n
*						Destroy the created i18n_uenumeration_h handle.
* @apitarget			i18n_uenumeration_uchar_strings_enumeration_create, i18n_uenumeration_destroy
* @apicovered			i18n_uenumeration_uchar_strings_enumeration_create, i18n_uenumeration_destroy
* @passcase				When i18n_uenumeration_uchar_strings_enumeration_create and i18n_uenumeration_destroy are successful
* @failcase				When i18n_uenumeration_uchar_strings_enumeration_create or i18n_uenumeration_destroy failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_uenumeration_uchar_strings_enumeration_create_destroy_p(void)
{
	START_TEST;
	i18n_uenumeration_h uenum = NULL;
	
	int nRetVal = i18n_uenumeration_uchar_strings_enumeration_create(ustrings, sizeof(ustrings)/sizeof(ustrings[0]), &uenum);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uenumeration_uchar_strings_enumeration_create", BaseUtilsGetError(nRetVal));
	
	nRetVal =i18n_uenumeration_destroy(uenum);
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uenumeration_destroy", BaseUtilsGetError(nRetVal));
	
	uenum = NULL;
	return 0;
}


//& type: auto
//& purpose: Create/Destroy an i18n_uenumeration_h from a const char* strings.
/**
* @testcase				ITc_i18n_uenumeration_char_strings_enumeration_create_destroy_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create an i18n_uenumeration_h handle.\n
*						Destroy the created i18n_uenumeration_h handle.
* @apitarget			i18n_uenumeration_char_strings_enumeration_create, i18n_uenumeration_destroy
* @apicovered			i18n_uenumeration_char_strings_enumeration_create, i18n_uenumeration_destroy
* @passcase				When i18n_uenumeration_char_strings_enumeration_create and i18n_uenumeration_destroy are successful
* @failcase				When i18n_uenumeration_char_strings_enumeration_create or i18n_uenumeration_destroy failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_uenumeration_char_strings_enumeration_create_destroy_p(void)
{
	START_TEST;
	const char string_1[] = { 't', 0 }, string_2[] = { 'e', 0 }, string_3[] = { 's', 0 }, string_4[] = { 't', 0 };
    const char* pStrings[] = { string_1, string_2, string_3, string_4 };

    i18n_uenumeration_h local_uenum;
	
	int nRetVal = i18n_uenumeration_char_strings_enumeration_create(pStrings, sizeof(pStrings)/sizeof(pStrings[0]), &local_uenum);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uenumeration_char_strings_enumeration_create", BaseUtilsGetError(nRetVal));
	
	nRetVal =i18n_uenumeration_destroy(local_uenum);
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uenumeration_destroy", BaseUtilsGetError(nRetVal));
	
	local_uenum = NULL;
	return 0;
}

//& type: auto
//& purpose: Returns the number of elements that the iterator traverses.
/**
* @testcase				ITc_i18n_uenumeration_count_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns the number of elements that the iterator traverses.\n
* @apitarget			i18n_uenumeration_count
* @apicovered			i18n_uenumeration_count
* @passcase				When i18n_uenumeration_count is successful
* @failcase				When i18n_uenumeration_count failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_uenumeration_count_p(void)
{
	START_TEST;
	int nRetVal = -1;
	
	nRetVal = i18n_uenumeration_count(g_uenum);
	if( nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s] i18n_uenumeration_count failed. Returned value = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns the next element in the iterator's list.
/**
* @testcase				ITc_i18n_uenumeration_unext_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Get the next element in the iterator's list.
* @apitarget			i18n_uenumeration_unext
* @apicovered			i18n_uenumeration_unext
* @passcase				When i18n_uenumeration_unext is successful
* @failcase				When i18n_uenumeration_unext failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_uenumeration_unext_p(void)
{
	START_TEST;
	const i18n_uchar *pRet = NULL;
	int32_t result_length = 0;
	
	pRet = i18n_uenumeration_unext(g_uenum, &result_length);
	if( pRet == NULL)
	{
		FPRINTF("[Line : %d][%s] i18n_uenumeration_unext failed. Returned value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns the next element in the iterator's list.
/**
* @testcase				ITc_i18n_uenumeration_next_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Get the next element in the iterator's list.
* @apitarget			i18n_uenumeration_next
* @apicovered			i18n_uenumeration_next
* @passcase				When i18n_uenumeration_next is successful
* @failcase				When i18n_uenumeration_next failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_uenumeration_next_p(void)
{
	START_TEST;
	int32_t result_length = 0;
	const char *pRet = NULL;
	
	pRet = i18n_uenumeration_next(g_uenum, &result_length);
	if( pRet == NULL)
	{
		FPRINTF("[Line : %d][%s] i18n_uenumeration_next failed. Returned value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Resets the iterator to the current list of service IDs.
/**
* @testcase				ITc_i18n_uenumeration_reset_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Resets the iterator to the current list of service IDs.
* @apitarget			i18n_uenumeration_reset
* @apicovered			i18n_uenumeration_reset
* @passcase				When i18n_uenumeration_reset is successful
* @failcase				When i18n_uenumeration_reset failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_uenumeration_reset_p(void)
{
	START_TEST;
	int nRetVal;
	
	nRetVal = i18n_uenumeration_reset(g_uenum);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uenumeration_reset", BaseUtilsGetError(nRetVal));
	
	return 0;
}

