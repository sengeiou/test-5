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

#define nCount 3

i18n_formattable_h g_hformattable;

//& set: BaseUtilsUsearch

/**
* @function 		ITs_base_utils_formattable_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_base_utils_formattable_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRetVal = i18n_formattable_create_default(&g_hformattable);
	if (nRetVal != I18N_ERROR_NONE || g_hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_default failed in startup, error returned = %s or handle is NULL \n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
		g_bBaseUtilsInitFlag = false;
		return;
	}
	
	g_bBaseUtilsInitFlag = true;
	return;
}

/**
* @function 		ITs_base_utils_formattable_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_formattable_cleanup(void)
{

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_hformattable)
	{
		int nRetVal = i18n_formattable_destroy(g_hformattable);
		if (nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("\\n[Line : %d][%s] i18n_formattable_destroy failed in cleanup, error returned = %s \n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
		}
	}
	
	g_bBaseUtilsInitFlag = false;	
	return;
}

//& type: auto
//& purpose: Creates a new default formattable handle and destroy it
/**
* @testcase				ITc_i18n_formattable_create_default_destroy_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Creates a new default formattable handle and destroy it
* @apitarget			i18n_formattable_create_default, i18n_formattable_destroy
* @apicovered			i18n_formattable_create_default, i18n_formattable_destroy
* @passcase				When i18n_formattable_create_default, i18n_formattable_destroy are successful
* @failcase				If target i18n_formattable_create_default or i18n_formattable_destroy fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_create_default_destroy_p(void)
{
	START_TEST;
	
	i18n_formattable_h hformattable = NULL;

	int nRetVal = i18n_formattable_create_default(&hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_default", BaseUtilsGetError(nRetVal));
	if (hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_default failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRetVal = i18n_formattable_destroy(hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Creates a new #i18n_formattable_h handle with an #i18n_udate instance.
/**
* @testcase				ITc_i18n_formattable_create_with_udate_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Creates a new #i18n_formattable_h handle with an #i18n_udate instance.
* @apitarget			i18n_formattable_create_with_udate
* @apicovered			i18n_formattable_create_with_udate, i18n_formattable_destroy
* @passcase				When i18n_formattable_create_with_udate is successful
* @failcase				If target i18n_formattable_create_with_udate or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_create_with_udate_p(void)
{
	START_TEST;
	
	i18n_formattable_h hformattable = NULL;
    i18n_udate nDate = 13.0;

    int nRetVal = i18n_formattable_create_with_udate(nDate, &hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_udate", BaseUtilsGetError(nRetVal));
	if (hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_udate failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRetVal = i18n_formattable_destroy(hformattable);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_formattable_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Creates a new #i18n_formattable_h handle with a double value.
/**
* @testcase				ITc_i18n_formattable_create_with_double_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Creates a new #i18n_formattable_h handle with a double value.
* @apitarget			i18n_formattable_create_with_double
* @apicovered			i18n_formattable_create_with_double, i18n_formattable_destroy
* @passcase				When i18n_formattable_create_with_double is successful
* @failcase				If target i18n_formattable_create_with_double or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_create_with_double_p(void)
{
	START_TEST;
	
	i18n_formattable_h hformattable = NULL;
	double nDouble = 13.0;

    int nRetVal = i18n_formattable_create_with_double(nDouble, &hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_double", BaseUtilsGetError(nRetVal));
	if (hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_double failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRetVal = i18n_formattable_destroy(hformattable);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_formattable_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Creates a new #i18n_formattable_h handle with a long value.
/**
* @testcase				ITc_i18n_formattable_create_with_long_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Creates a new #i18n_formattable_h handle with a long value.
* @apitarget			i18n_formattable_create_with_long
* @apicovered			i18n_formattable_create_with_long, i18n_formattable_destroy
* @passcase				When i18n_formattable_create_with_long is successful
* @failcase				If target i18n_formattable_create_with_long or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_create_with_long_p(void)
{
	START_TEST;
	
	i18n_formattable_h hformattable = NULL;
    int32_t nLong = 13;

    int nRetVal = i18n_formattable_create_with_long(nLong, &hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_long", BaseUtilsGetError(nRetVal));
	if (g_hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_long failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRetVal = i18n_formattable_destroy(hformattable);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_formattable_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Creates a new #i18n_formattable_h handle with an int64_t value.
/**
* @testcase				ITc_i18n_formattable_create_with_int64_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Creates a new #i18n_formattable_h handle with an int64_t value.
* @apitarget			i18n_formattable_create_with_int64
* @apicovered			i18n_formattable_create_with_int64, i18n_formattable_destroy
* @passcase				When i18n_formattable_create_with_int64 is successful
* @failcase				If target i18n_formattable_create_with_int64 or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_create_with_int64_p(void)
{
	START_TEST;
	
	i18n_formattable_h hformattable = NULL;
	int64_t nInt = 13;

    int nRetVal = i18n_formattable_create_with_int64(nInt, &hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_int64", BaseUtilsGetError(nRetVal));
	if (g_hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_int64 failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRetVal = i18n_formattable_destroy(hformattable);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_formattable_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Creates a new #i18n_formattable_h handle with a char string pointer.
/**
* @testcase				ITc_i18n_formattable_create_with_char_string_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Creates a new #i18n_formattable_h handle with a char string pointer.
* @apitarget			i18n_formattable_create_with_char_string
* @apicovered			i18n_formattable_create_with_char_string, i18n_formattable_destroy
* @passcase				When i18n_formattable_create_with_char_string is successful
* @failcase				If target i18n_formattable_create_with_char_string or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_create_with_char_string_p(void)
{
	START_TEST;
	
	i18n_formattable_h hformattable = NULL;
	const char *pszString = "Test string";

    int nRetVal = i18n_formattable_create_with_char_string(pszString, &hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_char_string", BaseUtilsGetError(nRetVal));
	if (g_hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_char_string failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRetVal = i18n_formattable_destroy(hformattable);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_formattable_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Creates a new #i18n_formattable_h handle with an array of #i18n_formattable_h handles.
/**
* @testcase				ITc_i18n_formattable_create_with_formattable_array_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Creates a new #i18n_formattable_h handle with an array of #i18n_formattable_h handles.
* @apitarget			i18n_formattable_create_with_formattable_array
* @apicovered			i18n_formattable_create_with_formattable_array, i18n_formattable_destroy
* @passcase				When i18n_formattable_create_with_formattable_array is successful
* @failcase				If target i18n_formattable_create_with_formattable_array or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_create_with_formattable_array_p(void)
{
	START_TEST;
	
	i18n_formattable_h hArr[nCount];
	i18n_formattable_h hformattable = NULL;
	int nRetVal;
	int32_t i;
	
    for (i = 0; i < nCount; ++i) 
	{
		double nValue = i;
		nRetVal = i18n_formattable_create_with_double(nValue, &hArr[i]);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_double", BaseUtilsGetError(nRetVal));
		if (hArr[i] == NULL)
		{
			FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_double failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
			return 1;
		}
    }

    nRetVal = i18n_formattable_create_with_formattable_array(hArr, nCount, &hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_formattable_array", BaseUtilsGetError(nRetVal));
	if (hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_formattable_array failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRetVal = i18n_formattable_destroy(hformattable);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_formattable_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose:  Clones the given formattable handle with the related object to the @a clone handle.
/**
* @testcase				ITc_i18n_formattable_clone_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Clones the given formattable handle with the related object to the @a clone handle.
* @apitarget			i18n_formattable_clone
* @apicovered			i18n_formattable_clone, i18n_formattable_destroy
* @passcase				When i18n_formattable_clone is successful
* @failcase				If target i18n_formattable_clone or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_clone_p(void)
{
	START_TEST;
	
	i18n_formattable_h hClone = NULL;
	
    int nRetVal = i18n_formattable_clone(g_hformattable, &hClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_clone", BaseUtilsGetError(nRetVal));
	if (hClone == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_clone failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
    nRetVal = i18n_formattable_destroy(hClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Sets and Gets the array value and count of the given formattable object.
/**
* @testcase				ITc_i18n_formattable_set_get_array_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets and Gets the array value and count of the given formattable object.
* @apitarget			i18n_formattable_set_array
* @apicovered			i18n_formattable_set_array, i18n_formattable_get_array,i18n_formattable_destroy
* @passcase				When i18n_formattable_set_array & i18n_formattable_get_array is successful
* @failcase				If target i18n_formattable_set_array , i18n_formattable_get_array or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_set_get_array_p(void)
{
	START_TEST;
		
	i18n_formattable_h hArr[nCount];
	i18n_formattable_h *hArray;
    int32_t ncount = 0;
	int nRetVal;
	int32_t i;
	
    for (i = 0; i < nCount; ++i) 
	{
		double nValue = i;
		nRetVal = i18n_formattable_create_with_double(nValue, &hArr[i]);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_double", BaseUtilsGetError(nRetVal));
		if (hArr[i] == NULL)
		{
			FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_double failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
			return 1;
		}
    }

    nRetVal = i18n_formattable_set_array(g_hformattable, hArr,nCount);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_set_array", BaseUtilsGetError(nRetVal));
	   
    nRetVal = i18n_formattable_get_array(g_hformattable, &hArray, &ncount);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_get_array", BaseUtilsGetError(nRetVal));
	
	if(hArray == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_get_array failed ,array is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
    if (nCount != ncount) 
	{
        free(hArray);
       	FPRINTF("\\n[Line : %d][%s] i18n_formattable_get_array failed ,Value mismatchL \n", __LINE__, API_NAMESPACE);
		return 1;
    }

	return 0;
}

//& type: auto
//& purpose: Sets and Gets the date value of the given formattable object.
/**
* @testcase				ITc_i18n_formattable_set_get_date_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets and Gets the date value of the given formattable object.
* @apitarget			i18n_formattable_set_date,i18n_formattable_get_date
* @apicovered			i18n_formattable_set_date, i18n_formattable_get_date,i18n_formattable_destroy
* @passcase				When i18n_formattable_set_date & i18n_formattable_get_date is successful
* @failcase				If target i18n_formattable_set_date , i18n_formattable_get_date or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_set_get_date_p(void)
{
	START_TEST;
		
	i18n_udate nSetDate = 13.0;
	i18n_udate nGetdate;
	
    int nRetVal = i18n_formattable_set_date(g_hformattable, nSetDate);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_set_date", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_formattable_get_date(g_hformattable, &nGetdate);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_get_date", BaseUtilsGetError(nRetVal));	
	
	if (nSetDate != nGetdate) 
	{
       	FPRINTF("\\n[Line : %d][%s] Value mismatch \n", __LINE__, API_NAMESPACE);
		return 1;
    }
 	
	return 0;
}

//& type: auto
//& purpose: Sets and Gets the double value of the given formattable object.
/**
* @testcase				ITc_i18n_formattable_set_get_double_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets and Gets the double value of the given formattable object.
* @apitarget			i18n_formattable_set_double,i18n_formattable_get_double
* @apicovered			i18n_formattable_set_double,i18n_formattable_get_double, i18n_formattable_destroy
* @passcase				When i18n_formattable_set_double & i18n_formattable_get_double is successful
* @failcase				If target i18n_formattable_set_double,i18n_formattable_get_double or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_set_get_double_p(void)
{
	START_TEST;
	
	double nSetVal = 7;
	double nGetVal;
	
	int nRetVal = i18n_formattable_set_double(g_hformattable, nSetVal);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_set_double", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_formattable_get_double(g_hformattable, &nGetVal);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_get_double", BaseUtilsGetError(nRetVal));	
	
	 if (nSetVal != nGetVal) 
	{
       	FPRINTF("\\n[Line : %d][%s] Value mismatch \n", __LINE__, API_NAMESPACE);
		return 1;
    }
		
	return 0;
}

//& type: auto
//& purpose: Sets and Gets the int64 value of the given formattable object.
/**
* @testcase				ITc_i18n_formattable_set_get_int64_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets and Gets the int64 value of the given formattable object.
* @apitarget			i18n_formattable_set_int64,i18n_formattable_get_int64
* @apicovered			i18n_formattable_set_int64, i18n_formattable_get_int64,i18n_formattable_destroy
* @passcase				When i18n_formattable_set_int64 & i18n_formattable_get_int64 is successful
* @failcase				If target i18n_formattable_set_int64,i18n_formattable_get_int64 or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_set_get_int64_p(void)
{
	START_TEST;
	
	int64_t nSetVal = 13;
	int64_t nGetValue = NULL;
		
    int nRetVal = i18n_formattable_set_int64(g_hformattable, nSetVal);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_set_int64", BaseUtilsGetError(nRetVal));
		
    nRetVal = i18n_formattable_get_int64(g_hformattable, &nGetValue);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_get_int64", BaseUtilsGetError(nRetVal));	
	
	 if (nSetVal != nGetValue) 
	{
       	FPRINTF("\\n[Line : %d][%s] Value mismatch \n", __LINE__, API_NAMESPACE);
		return 1;
    }
	
	return 0;
}

//& type: auto
//& purpose: Sets and Gets the long value of the given formattable object.
/**
* @testcase				ITc_i18n_formattable_set_get_long_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets and Gets the long value of the given formattable object.
* @apitarget			i18n_formattable_set_long,i18n_formattable_get_long
* @apicovered			i18n_formattable_set_long,i18n_formattable_get_long, i18n_formattable_destroy
* @passcase				When i18n_formattable_set_long & i18n_formattable_get_long is successful
* @failcase				If target i18n_formattable_set_long,i18n_formattable_get_long or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_set_get_long_p(void)
{
	START_TEST;
		
	int32_t nSetVal = 13;
	int32_t nGetValue ;
	
    int nRetVal = i18n_formattable_set_long(g_hformattable, nSetVal);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_set_long", BaseUtilsGetError(nRetVal));
	
    nRetVal = i18n_formattable_get_long(g_hformattable, &nGetValue);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_get_long", BaseUtilsGetError(nRetVal));	
	
	if (nSetVal != nGetValue) 
	{
       	FPRINTF("\\n[Line : %d][%s] Value mismatch \n", __LINE__, API_NAMESPACE);
		return 1;
    }
	
	return 0;
}

//& type: auto
//& purpose: Sets and Gets the string value of the given formattable object.
/**
* @testcase				ITc_i18n_formattable_set_get_string_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets and Gets the string value of the given formattable object.
* @apitarget			i18n_formattable_set_string,i18n_formattable_get_string
* @apicovered			i18n_formattable_set_string,i18n_formattable_get_string, i18n_formattable_destroy
* @passcase				When i18n_formattable_set_string & i18n_formattable_get_string is successful
* @failcase				If target i18n_formattable_set_string,i18n_formattable_get_string or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_set_get_string_p(void)
{
	START_TEST;
	
	const char *pszSetStr = "Test string";
	char *pszGetStr = NULL;
		
    int nRetVal = i18n_formattable_set_string(g_hformattable, pszSetStr);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_set_string", BaseUtilsGetError(nRetVal));
		
    nRetVal = i18n_formattable_get_string(g_hformattable, &pszGetStr);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_get_string", BaseUtilsGetError(nRetVal));	
	
	if (strcmp(pszSetStr, pszGetStr)!=0) 
	{
       	FPRINTF("\\n[Line : %d][%s] Value mismatchL \n", __LINE__, API_NAMESPACE);
		return 1;
    }
	
	return 0;
}

//& type: auto
//& purpose: Gets the data type of the given formattable object.
/**
* @testcase				ITc_i18n_formattable_get_type_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the data type of the given formattable object.
* @apitarget			i18n_formattable_get_type
* @apicovered			i18n_formattable_get_type, i18n_formattable_destroy
* @passcase				When i18n_formattable_get_type is successful
* @failcase				If target i18n_formattable_get_type or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_get_type_p(void)
{
	START_TEST;
	
	const char *pszSetStr = "Test string";
	i18n_formattable_h hformattable = NULL;
	i18n_formattable_type_e nGetTyp;

	int nRetVal = i18n_formattable_create_with_char_string(pszSetStr, &hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_char_string", BaseUtilsGetError(nRetVal));
	if (hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_char_string failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRetVal = i18n_formattable_get_type(hformattable, &nGetTyp);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_get_type", BaseUtilsGetError(nRetVal));
	if(nGetTyp != I18N_FORMATTABLE_TYPE_STRING)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_get_type failed ,wrong type \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRetVal = i18n_formattable_destroy(hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Sets the variable pointed by the @a is_numeric pointer to @c true if the data type of the given formattable object is	#I18N_FORMATTABLE_TYPE_DOUBLE,#I18N_FORMATTABLE_TYPE_LONG or #I18N_FORMATTABLE_TYPE_INT64.
/**
* @testcase				ITc_i18n_formattable_is_numeric_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				 Sets the variable pointed by the @a is_numeric pointer to @c true if the data type of the given formattable object is	#I18N_FORMATTABLE_TYPE_DOUBLE,#I18N_FORMATTABLE_TYPE_LONG or #I18N_FORMATTABLE_TYPE_INT64.
* @apitarget			i18n_formattable_is_numeric
* @apicovered			i18n_formattable_is_numeric, i18n_formattable_destroy
* @passcase				When i18n_formattable_is_numeric is successful
* @failcase				If target i18n_formattable_is_numeric or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_is_numeric_p(void)
{
	START_TEST;
	
	bool bNumb;
	
    int nRetVal = i18n_formattable_is_numeric(g_hformattable, &bNumb);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_is_numeric", BaseUtilsGetError(nRetVal));
	if(bNumb == false)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_is_numeric failed ,invalid bool value \n", __LINE__, API_NAMESPACE);
		return 1;
	}
		
	return 0;
}

//& type: auto
//& purpose:  Sets the variable pointed by the @a not_equal pointer to @c true if the given @a formattable object is not equal to the given @a other formattable object.
/**
* @testcase				ITc_i18n_formattable_not_equal_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets the variable pointed by the @a not_equal pointer to @c true if the given @a formattable object is not equal to the given @a other formattable object.
* @apitarget			i18n_formattable_not_equal
* @apicovered			i18n_formattable_not_equal, i18n_formattable_destroy
* @passcase				When i18n_formattable_not_equal is successful
* @failcase				If target i18n_formattable_not_equal or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_not_equal_p(void)
{
	START_TEST;
	
	double nValue = 7;
	i18n_formattable_h hformattable = NULL;
	bool bVal= false;
	
    int nRetVal = i18n_formattable_create_with_double(nValue, &hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_double", BaseUtilsGetError(nRetVal));
	if (hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_double failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
    nRetVal = i18n_formattable_not_equal(g_hformattable, hformattable, &bVal);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_not_equal", BaseUtilsGetError(nRetVal));
	
    nRetVal = i18n_formattable_destroy(hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_destroy", BaseUtilsGetError(nRetVal));
	
	if(bVal != true)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_not_equal failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: Sets the variable pointed by the @a equal pointer to @c true if the given @a formattable object is equal to the given @a other formattable object.
/**
* @testcase				ITc_i18n_formattable_equal_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets the variable pointed by the @a equal pointer to @c true if the given @a formattable object is equal to the given @a other formattable object.
* @apitarget			i18n_formattable_equal
* @apicovered			i18n_formattable_equal, i18n_formattable_destroy
* @passcase				When i18n_formattable_equal is successful
* @failcase				If target i18n_formattable_equal or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_equal_p(void)
{
	START_TEST;
	
	double nValue = 7;
	i18n_formattable_h hformattable = NULL;
	bool bVal;
	
    int nRetVal = i18n_formattable_create_with_double(nValue, &hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_double", BaseUtilsGetError(nRetVal));
	if (hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_double failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
    nRetVal = i18n_formattable_equal(g_hformattable, hformattable, &bVal);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_equal", BaseUtilsGetError(nRetVal));
	
    nRetVal = i18n_formattable_destroy(hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_destroy", BaseUtilsGetError(nRetVal));
	
	if(bVal != false)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_equal failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose:  Sets the object pointed by the @a element pointer to the element at the @a index position in the array stored by the given formattable object (if its type is #I18N_FORMATTABLE_TYPE_ARRAY).
/**
* @testcase				ITc_i18n_formattable_element_at_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets the object pointed by the @a element pointer to the element at the @a index position in the array stored by the given formattable object (if its type is #I18N_FORMATTABLE_TYPE_ARRAY).
* @apitarget			i18n_formattable_element_at
* @apicovered			i18n_formattable_element_at, i18n_formattable_destroy
* @passcase				When i18n_formattable_element_at is successful
* @failcase				If target i18n_formattable_element_at or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_formattable_element_at_p(void)
{
	START_TEST;
	
	i18n_formattable_h hArr[nCount];
	int nRetVal;
	int32_t i;
	bool bVal = false;
	int32_t index = 1;
	i18n_formattable_h hformattable = NULL;
	
    for (i = 0; i < nCount; ++i) 
	{
		double nValue = i;
		nRetVal = i18n_formattable_create_with_double(nValue, &hArr[i]);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_double", BaseUtilsGetError(nRetVal));
		if (hArr[i] == NULL)
		{
			FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_double failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
			return 1;
		}
    }
	
	nRetVal = i18n_formattable_destroy(g_hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_destroy", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_formattable_create_with_formattable_array(hArr, nCount, &g_hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_create_with_formattable_array", BaseUtilsGetError(nRetVal));
	if (g_hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_create_with_formattable_array failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	   
    nRetVal = i18n_formattable_element_at(g_hformattable, index, &hformattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_element_at", BaseUtilsGetError(nRetVal));
	if (hformattable == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_element_at failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
   	
	nRetVal = i18n_formattable_equal(hArr[index], hformattable, &bVal);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_formattable_equal", BaseUtilsGetError(nRetVal));
	if(bVal != true)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_formattable_equal failed ,handle is NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/** @} */
/** @} */