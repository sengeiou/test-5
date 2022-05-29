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


static i18n_uchar_iter_h uchar_iter = NULL;

static const i18n_uchar *uchar_string = "UChar test string";
static const char *utf16be_string = "UChar test string";
static const char *utf8_string = "UChar test string";




//& set: BaseUtilsUcharIter

/**
* @function 		ITs_base_utils_uchar_iter_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_uchar_iter_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int nRet = remove(ERR_LOG);
		PRINT_RESULT_NORETURN(0, nRet, "ITs_base_utils_uchar_iter_startup -remove", "Remove failed for ERR_LOG");
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_base_utils_uchar_iter_startup\\n", __LINE__, API_NAMESPACE);
#endif
	int nRetVal = i18n_uchar_iter_create(&uchar_iter);

	if(nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Error in TEST SUIT start-up: ITs_base_utils_uchar_iter_startup\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
		return;
	}
	g_bBaseUtilsInitFlag = true;
	return;
}

/**
* @function 		ITs_base_utils_uchar_iter_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_uchar_iter_cleanup(void)
{

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_base_utils_uchar_iter_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	if (uchar_iter != NULL){
		int nRetVal = i18n_uchar_iter_destroy(uchar_iter);
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] Error in TEST SUIT cleanup: ITs_base_utils_uchar_iter_cleanup\\n", __LINE__, API_NAMESPACE);
		}
	}
	g_bBaseUtilsInitFlag = false;

	return;
}



//& type: auto
//& purpose: Calls i18n_uchar_iter_create and i18n_uchar_iter_destroy to check whether Iterator is creator and destroyed
/**
* @testcase		ITc_i18n_uchar_iter_create_destroy_p
* @since_tizen 		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uchar_iter_create and i18n_uchar_iter_destroy to check whether Iterator is creator and destroyed
* @apitarget		i18n_uchar_iter_create and i18n_uchar_iter_destroy
* @apicovered		i18n_uchar_iter_create and i18n_uchar_iter_destroy
* @passcase		When i18n_uchar_iter_create and i18n_uchar_iter_destroy are successful
* @failcase		If target APIs i18n_uchar_iter_create and i18n_uchar_iter_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_iter_create_destroy_p(void)
{
	i18n_uchar_iter_h uIterTest = NULL;

	int nRetVal = i18n_uchar_iter_create(&uIterTest);

	if(nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_create\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if (uIterTest != NULL)
	{
		nRetVal = i18n_uchar_iter_destroy(uIterTest);
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_destroy\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}


//& type: auto
//& purpose: Calls i18n_uchar_iter_set_string to check whether the string will be set properly
/**
* @testcase		ITc_i18n_uchar_iter_set_string_p
* @since_tizen 		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uchar_iter_set_string to check whether the string will be set properly
* @apitarget		18n_uchar_iter_set_string
* @apicovered		18n_uchar_iter_set_string
* @passcase		When 18n_uchar_iter_set_string is successful
* @failcase		If target 18n_uchar_iter_set_string fails
* @precondition			NA
* @postcondition		NA
*/


int ITc_i18n_uchar_iter_set_string_p(void)
{

	START_TEST;

	int32_t ulen = strlen(uchar_string);

	int nRetVal = i18n_uchar_iter_set_string(uchar_iter, uchar_string, ulen);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_set_string", BaseUtilsGetError(nRetVal));

	return 0;
}




//& type: auto
//& purpose: Calls i18n_uchar_iter_set_utf16be to check whether the string will be set properly.
/**
* @testcase		ITc_i18n_uchar_iter_set_utf16be_p
* @since_tizen			4.0
* @author			SRID(maneesha.k)
* @reviewer			SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uchar_iter_set_utf16be to check whether the string will be set properly.
* @apitarget		i18n_uchar_iter_set_utf16be
* @apicovered		i18n_uchar_iter_set_utf16be
* @passcase		When i18n_uchar_iter_set_utf16be is successful
* @failcase		If target i18n_uchar_iter_set_utf16be fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_i18n_uchar_iter_set_utf16be_p(void)
{
	START_TEST;
	int32_t len = strlen(utf16be_string);

	int nRetVal  = i18n_uchar_iter_set_utf16be(uchar_iter, utf16be_string, len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_set_utf16be", BaseUtilsGetError(nRetVal));

	return 0;
}


//& type: auto
//& purpose: Calls i18n_uchar_iter_set_utf8 to check whether the string will be set properly.
/**
* @testcase		ITc_i18n_uchar_iter_set_utf8_p
* @since_tizen 		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uchar_iter_set_utf8 to check whether the string will be set properly.
* @apitarget		i18n_uchar_iter_set_utf8
* @apicovered		i18n_uchar_iter_set_utf8
* @passcase		When i18n_uchar_iter_set_utf8 is successful
* @failcase		If target i18n_uchar_iter_set_utf8 fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/

int ITc_i18n_uchar_iter_set_utf8_p(void)
{
	START_TEST;
	int32_t len = strlen(utf8_string);

	int nRetVal = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_set_utf8", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Calls i18n_uchar_iter_get_index to check whether the returned index will be correct.
/**
* @testcase		ITc_i18n_uchar_iter_get_index_p
* @since_tizen 		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uchar_iter_get_index to check whether the returned index will be correct.
* @apitarget		i18n_uchar_iter_get_index
* @apicovered		i18n_uchar_iter_set_utf8, i18n_uchar_iter_get_index
* @passcase		When i18n_uchar_iter_get_index is successful
* @failcase		If target i18n_uchar_iter_get_index fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_iter_get_index_p(void)
{
	START_TEST;
	int32_t len = strlen(utf8_string);

	int nRetVal = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_set_utf8", BaseUtilsGetError(nRetVal));


	int32_t index;
	nRetVal = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_get_index", BaseUtilsGetError(nRetVal));

	if(index != 0)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_get_index the index returned(%d) for start of string is not Zero\\n", __LINE__, API_NAMESPACE, index);
		return 1;
	}


	nRetVal = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_LENGTH, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_get_index", BaseUtilsGetError(nRetVal));
	if(index != len)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_get_index the last index returned(%d) is not Length of String(%d)\\n", __LINE__, API_NAMESPACE, index, len);
		return 1;
	}

	return 0;
}


//& type: auto
//& purpose: Calls i18n_uchar_iter_move to check whether no error occurs.
/**
* @testcase		ITc_i18n_uchar_iter_move_p
* @since_tizen 		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uchar_iter_move to check whether no error occurs.
* @apitarget		i18n_uchar_iter_move
* @apicovered		i18n_uchar_iter_move,i18n_uchar_iter_set_utf8
* @passcase		When i18n_uchar_iter_move is successful
* @failcase		If target i18n_uchar_iter_move fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_iter_move_p(void)
{
	START_TEST;

	int32_t nDelta = 2;
	int32_t len = strlen(utf8_string);
	int32_t index;

	int nRetVal = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_set_utf8", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_uchar_iter_move(uchar_iter, nDelta, I18N_UCHAR_ITER_START, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_move", BaseUtilsGetError(nRetVal));
	if(index != nDelta)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_move the index returned(%d) is not Equal to nDelta(%d) from Start\\n", __LINE__, API_NAMESPACE, index, nDelta);
		return 1;
	}

	nRetVal = i18n_uchar_iter_move(uchar_iter, nDelta, I18N_UCHAR_ITER_CURRENT, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_move", BaseUtilsGetError(nRetVal));
	if(index != nDelta*2)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_move the index returned(%d) is not Equal to nDelta(%d) from Current Position\\n", __LINE__, API_NAMESPACE, index, nDelta);
		return 1;
	}
	return 0;
}


//& type: auto
//& purpose: Calls i18n_uchar_iter_has_next to check whether no error occurs.
/**
* @testcase		ITc_i18n_uchar_iter_has_next_p
* @since_tizen 		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uchar_iter_has_next to check whether no error occurs.
* @apitarget		i18n_uchar_iter_has_next
* @apicovered		i18n_uchar_iter_has_next, i18n_uchar_iter_move, i18n_uchar_iter_set_utf8, i18n_uchar_iter_get_index
* @passcase		When i18n_uchar_iter_has_next is successful
* @failcase		If target i18n_uchar_iter_has_next fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_iter_has_next_p(void)
{

	START_TEST;

	int nDelta = 0;
	int32_t len = strlen(utf8_string);

	int nRetVal = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_set_utf8", BaseUtilsGetError(nRetVal));

	int32_t index;
	nRetVal = i18n_uchar_iter_move(uchar_iter, nDelta, I18N_UCHAR_ITER_START, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_move", BaseUtilsGetError(nRetVal));
	if(index != nDelta)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_move the index returned(%d) is not Zero\\n", __LINE__, API_NAMESPACE, index);
		return 1;
	}

	bool bHasNext;
	nRetVal = i18n_uchar_iter_has_next(uchar_iter, &bHasNext);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, " i18n_uchar_iter_has_next", BaseUtilsGetError(nRetVal));
	if(!bHasNext)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_has_next returned a false bHasNext\\n", __LINE__, API_NAMESPACE);
		return 1;
	}


	nRetVal = i18n_uchar_iter_move(uchar_iter, nDelta, I18N_UCHAR_ITER_LENGTH, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_move", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_get_index", BaseUtilsGetError(nRetVal));
	if(index != len)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_move the index returned(%d) is not last Index(%d)\\n", __LINE__, API_NAMESPACE, index, len);
		return 1;
	}

	nRetVal = i18n_uchar_iter_has_next(uchar_iter, &bHasNext);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_has_next", BaseUtilsGetError(nRetVal));
	if(bHasNext)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_has_next returned a true bHasNext for last element of string\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}


//& type: auto
//& purpose: Calls i18n_uchar_iter_has_previous to check whether no error occurs.
/**
* @testcase		ITc_i18n_uchar_iter_has_previous_p
* @since_tizen 		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uchar_iter_has_previous to check whether no error occurs.
* @apitarget		i18n_uchar_iter_has_previous
* @apicovered		i18n_uchar_iter_has_previous, i18n_uchar_iter_move, i18n_uchar_iter_set_utf8, i18n_uchar_iter_get_index
* @passcase		When i18n_uchar_iter_has_previous is successful
* @failcase		If target i18n_uchar_iter_has_previous fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_iter_has_previous_p(void)
{
	START_TEST;
	int nDelta = 0;
	int32_t len = strlen(utf8_string);

	int nRetVal = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_set_utf8", BaseUtilsGetError(nRetVal));

	int32_t index;
	nRetVal = i18n_uchar_iter_move(uchar_iter, nDelta, I18N_UCHAR_ITER_START, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_move", BaseUtilsGetError(nRetVal));
	if(index != nDelta)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_move the index returned(%d) is not Zero\\n", __LINE__, API_NAMESPACE, index);
		return 1;
	}

	bool has_previous;
	nRetVal = i18n_uchar_iter_has_previous(uchar_iter, &has_previous);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_has_previous", BaseUtilsGetError(nRetVal));
	if(has_previous)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_has_previous returned a true has_previous for first element\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = i18n_uchar_iter_move(uchar_iter, nDelta, I18N_UCHAR_ITER_LENGTH, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_move", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_get_index", BaseUtilsGetError(nRetVal));
	if(index != len)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_move the index returned(%d) is not last Index(%d)\\n", __LINE__, API_NAMESPACE, index, len);
		return 1;
	}

	nRetVal = i18n_uchar_iter_has_previous(uchar_iter, &has_previous);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_has_previous", BaseUtilsGetError(nRetVal));
	if(!has_previous)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_has_previous returned a false has_previous for last element\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}



//& type: auto
//& purpose: Calls i18n_uchar_iter_current to check whether no error occurs.
/**
* @testcase		ITc_i18n_uchar_iter_current_p
* @since_tizen 		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uchar_iter_current to check whether no error occurs.
* @apitarget		i18n_uchar_iter_current
* @apicovered		i18n_uchar_iter_current, i18n_uchar_iter_move, i18n_uchar_iter_set_utf8, i18n_uchar_iter_get_index
* @passcase		When i18n_uchar_iter_current is successful
* @failcase		If target i18n_uchar_iter_current fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_iter_current_p(void)
{
	START_TEST;

	int nDelta = 0;
	int nDelta2 = -1;
	int32_t len = strlen(utf8_string);

	i18n_uchar32 current;

	int nRetVal = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_set_utf8", BaseUtilsGetError(nRetVal));


	int32_t index;
	nRetVal = i18n_uchar_iter_move(uchar_iter, nDelta, I18N_UCHAR_ITER_START, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_move", BaseUtilsGetError(nRetVal));
	if(index != nDelta)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_move the index returned(%d) is not Delta(%d)\\n", __LINE__, API_NAMESPACE, index, nDelta);
		return 1;
	}


	nRetVal = i18n_uchar_iter_current(uchar_iter, &current);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_current", BaseUtilsGetError(nRetVal));
	if(current != 'U')
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_current returned wrong value(%c) for first element(%c)\\n", __LINE__, API_NAMESPACE, current, utf8_string[0]);
		return 1;
	}

	nRetVal = i18n_uchar_iter_move(uchar_iter, nDelta2, I18N_UCHAR_ITER_LENGTH, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_move", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_get_index", BaseUtilsGetError(nRetVal));

	if(index != len + nDelta2)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_get_index the index returned(%d) is not %d\\n", __LINE__, API_NAMESPACE, index, len + nDelta2);
		return 1;
	}

	nRetVal = i18n_uchar_iter_current(uchar_iter, &current);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_current", BaseUtilsGetError(nRetVal));
	if(current != utf8_string[len + nDelta2])
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_current returned wrong value(%c) instead of %c \\n", __LINE__, API_NAMESPACE, current, utf8_string[len + nDelta2]);
		return 1;
	}

	return 0;
}



//& type: auto
//& purpose: Calls i18n_uchar_iter_next to check whether no error occurs
/**
* @testcase		ITc_i18n_uchar_iter_next_p
* @since_tizen 		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uchar_iter_next to check whether no error occurs
* @apitarget		i18n_uchar_iter_next
* @apicovered		i18n_uchar_iter_next, i18n_uchar_iter_move, i18n_uchar_iter_set_utf8
* @passcase		When i18n_uchar_iter_next is successful
* @failcase		If target i18n_uchar_iter_next fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/

int ITc_i18n_uchar_iter_next_p(void)
{

	START_TEST;

	int nDelta = 0;
	int32_t len = strlen(utf8_string);

	i18n_uchar32 current;

	int nRetVal = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_set_utf8", BaseUtilsGetError(nRetVal));

	int32_t index;
	nRetVal = i18n_uchar_iter_move(uchar_iter, nDelta, I18N_UCHAR_ITER_START, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_move", BaseUtilsGetError(nRetVal));
	if(index != nDelta)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_move the index returned(%d) is not nDelta(%d)\\n", __LINE__, API_NAMESPACE, index, nDelta);
		return 1;
	}

	nRetVal = i18n_uchar_iter_next(uchar_iter, &current);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_next", BaseUtilsGetError(nRetVal));
	if(current != utf8_string[nDelta])
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_current returned wrong value(%c) instead of First Element(%c) \\n", __LINE__, API_NAMESPACE, current,utf8_string[nDelta]);
		return 1;
	}

	nRetVal = i18n_uchar_iter_next(uchar_iter, &current);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_next", BaseUtilsGetError(nRetVal));
	if(current != utf8_string[nDelta+1])
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_current returned wrong value(%c) instead of Second Element(%c) \\n", __LINE__, API_NAMESPACE, current, utf8_string[nDelta+1]);
		return 1;
	}


	nRetVal = i18n_uchar_iter_next(uchar_iter, &current);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_next", BaseUtilsGetError(nRetVal));
	if(current != utf8_string[nDelta+2])
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_current returned wrong value(%c) instead of Third Element(%c) \\n", __LINE__, API_NAMESPACE, current, utf8_string[nDelta+2]);
		return 1;
	}

	return 0;
}


//& type: auto
//& purpose: Calls i18n_uchar_iter_previous to check whether no error occurs
/**
* @testcase		ITc_i18n_uchar_iter_previous_p
* @since_tizen 		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uchar_iter_previous to check whether no error occurs
* @apitarget		i18n_uchar_iter_previous
* @apicovered		i18n_uchar_iter_previous, i18n_uchar_iter_set_utf8, i18n_uchar_iter_move, i18n_uchar_iter_get_index
* @passcase		When i18n_uchar_iter_previous is successful
* @failcase		If target i18n_uchar_iter_previous fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_iter_previous_p(void)
{

	START_TEST;

	int nDelta = 0;
	int32_t len = strlen(utf8_string);

	i18n_uchar32 current;

	int nRetVal = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_set_utf8", BaseUtilsGetError(nRetVal));

	int32_t index;
	nRetVal = i18n_uchar_iter_move(uchar_iter, nDelta, I18N_UCHAR_ITER_LENGTH, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_move", BaseUtilsGetError(nRetVal));
	nRetVal = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_get_index", BaseUtilsGetError(nRetVal));
	if(index != len)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_get_index the index returned(%d) is not Length of String(%d)\\n", __LINE__, API_NAMESPACE, index, len);
		return 1;
	}

	nRetVal = i18n_uchar_iter_previous(uchar_iter, &current);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_previous", BaseUtilsGetError(nRetVal));
	if(current != utf8_string[len-1])
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_current returned wrong value(%c) instead of Last Element(%d) \\n", __LINE__, API_NAMESPACE, current, utf8_string[len-1]);
		return 1;
	}

	nRetVal = i18n_uchar_iter_previous(uchar_iter, &current);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_previous", BaseUtilsGetError(nRetVal));
	if(current != utf8_string[len-2])
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_current returned wrong value(%c) instead of Second Last Element(%c) \\n", __LINE__, API_NAMESPACE, current, utf8_string[len-2]);
		return 1;
	}

	nRetVal = i18n_uchar_iter_previous(uchar_iter, &current);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_previous", BaseUtilsGetError(nRetVal));
	if(current != utf8_string[len-3])
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_current returned wrong value(%c) instead of Third Last Element(%c) \\n", __LINE__, API_NAMESPACE, current, utf8_string[len-3]);
		return 1;
	}


	return 0;
}





//& type: auto
//& purpose: Calls i18n_uchar_iter_get_state and i18n_uchar_iter_set_state to check whether the state will be retrieved and set properly.
/**
* @testcase		ITc_i18n_uchar_iter_get_set_state_p
* @since_tizen 		4.0
* @author            	SRID(maneesha.k)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @scenario		Calls i18n_uchar_iter_get_state and i18n_uchar_iter_set_state to check whether the state will be retrieved and set properly.
* @apitarget		i18n_uchar_iter_get_state, i18n_uchar_iter_set_state
* @apicovered		i18n_uchar_iter_get_state, i18n_uchar_iter_set_state, i18n_uchar_iter_set_utf8, i18n_uchar_iter_move, i18n_uchar_iter_get_index
* @passcase		When i18n_uchar_iter_get_state, i18n_uchar_iter_set_state is successful
* @failcase		If target i18n_uchar_iter_get_state, i18n_uchar_iter_set_state fail or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_iter_get_set_state_p(void)
{

	START_TEST;

	int nDelta = 0;
	int32_t len = strlen(utf8_string);

	uint32_t state;

	int nRetVal = i18n_uchar_iter_set_utf8(uchar_iter, utf8_string, len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_set_utf8", BaseUtilsGetError(nRetVal));

	int32_t index;
	nRetVal = i18n_uchar_iter_move(uchar_iter, nDelta,  I18N_UCHAR_ITER_LENGTH, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_move", BaseUtilsGetError(nRetVal));
	nRetVal = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_get_index", BaseUtilsGetError(nRetVal));

	if(index != len)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_get_index the index returned(%d) is not Length of String(%d)\\n", __LINE__, API_NAMESPACE, index, len);
		return 1;
	}


	nRetVal = i18n_uchar_iter_get_state(uchar_iter, &state);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_get_state", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_uchar_iter_move(uchar_iter, nDelta, I18N_UCHAR_ITER_START, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_move", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_get_index", BaseUtilsGetError(nRetVal));
	if(index != nDelta)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_get_index the index returned(%d) is not %d\\n", __LINE__, API_NAMESPACE, index, nDelta);
		return 1;
	}

	nRetVal = i18n_uchar_iter_set_state(uchar_iter, state);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_set_state", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_uchar_iter_get_index(uchar_iter, I18N_UCHAR_ITER_CURRENT, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_iter_get_index", BaseUtilsGetError(nRetVal));
	if(index != len)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_iter_get_index the index returned(%d) is not Length of String(%d)\\n", __LINE__, API_NAMESPACE, index, len);
		return 1;
	}

	return 0;
}
