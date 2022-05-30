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

static i18n_field_position_h g_hFieldPosition = NULL;


/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/

//& set: BaseUtilsUbrk 
void ITs_base_utils_field_position_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bBaseUtilsInitFlag = false; 
	
    int nRet =  i18n_field_position_create(&g_hFieldPosition);
    if (nRet != I18N_ERROR_NONE) {
       g_bBaseUtilsInitFlag = false;	
    }
	else if(g_hFieldPosition == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] g_hFieldPosition is null\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;			
	}
	else
	{
		g_bBaseUtilsInitFlag = true;
	}
	
	return;
}

void ITs_base_utils_field_position_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	 if (g_hFieldPosition != NULL) {
        i18n_field_position_destroy(g_hFieldPosition);
        g_hFieldPosition = NULL;
    }
	g_bBaseUtilsInitFlag = false;
	return;
}

/** @addtogroup itc-base-utils-testcases
*  @brief 		Integration testcases for module base-utils ubrk
*  @ingroup 	itc-base-utils
*  @{
*/

//& type: auto
//& purpose: Creates a field position object with a non-specified field
/**
* @testcase				ITc_i18n_field_position_create_destroy_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Creates a field position object with a non-specified field
* @apitarget			i18n_field_position_create, i18n_field_position_destroy	
* @apicovered			i18n_field_position_create, i18n_field_position_destroy	
* @passcase				I18N_ERROR_NONE returned by i18n_field_position_create, i18n_field_position_destroy	
* @failcase				I18N_ERROR_NONE not returned by i18n_field_position_create, i18n_field_position_destroy	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_field_position_create_destroy_p(void)
{	
	START_TEST;
	
	i18n_field_position_h hFieldPosition = NULL;

	//Target API
	int nRet = i18n_field_position_create(&hFieldPosition);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_field_position_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hFieldPosition, "i18n_field_position_create");
	
	//Target API
	nRet = i18n_field_position_destroy(hFieldPosition);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_field_position_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Creates a field position object for the given field
/**
* @testcase				ITc_i18n_field_position_create_set_get_for_field_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Creates a field position object for the given field
* @apitarget			i18n_field_position_create_for_field, i18n_field_position_get_field, i18n_field_position_destroy	
* @apicovered			i18n_field_position_create_for_field, i18n_field_position_get_field, i18n_field_position_destroy	
* @passcase				I18N_ERROR_NONE returned by i18n_field_position_create_for_field, i18n_field_position_get_field, i18n_field_position_destroy	
* @failcase				I18N_ERROR_NONE not returned by i18n_field_position_create_for_field, i18n_field_position_get_field, i18n_field_position_destroy	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_field_position_create_set_get_for_field_p(void)
{	
	START_TEST;
	
	i18n_field_position_h hFieldPosition = NULL;
    int32_t nField = 13;
	int32_t nRetField = -1;
	
	//Target API
	int nRet = i18n_field_position_create_for_field(nField, &hFieldPosition);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_field_position_create_for_field", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hFieldPosition, "i18n_field_position_create_for_field");
	
	//Target API
	nRet = i18n_field_position_set_field(hFieldPosition, nField);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_field_position_set_field", BaseUtilsGetError(nRet));
	
	//Target API
	nRet = i18n_field_position_get_field(hFieldPosition, &nRetField);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_field_position_get_field", BaseUtilsGetError(nRet),i18n_field_position_destroy(hFieldPosition));
	
	if(nRetField != nField)
	{
		FPRINTF("\\n[Line : %d][%s] nRetField return value is not correct!!\\n", __LINE__, API_NAMESPACE);
		i18n_field_position_destroy(hFieldPosition);
		return 1;
	}

	nRet = i18n_field_position_destroy(hFieldPosition);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_field_position_destroy", BaseUtilsGetError(nRet));

	return 0;
}


//& type: auto
//& purpose: Creates a clone of the given @a field_position object
/**
* @testcase				ITc_i18n_field_position_clone_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Creates a clone of the given @a field_position object
* @apitarget			i18n_field_position_clone, i18n_field_position_get_field, i18n_field_position_destroy	
* @apicovered			i18n_field_position_clone, i18n_field_position_get_field, i18n_field_position_destroy	
* @passcase				I18N_ERROR_NONE returned by i18n_field_position_clone, i18n_field_position_get_field, i18n_field_position_destroy	
* @failcase				I18N_ERROR_NONE not returned by i18n_field_position_clone, i18n_field_position_get_field, i18n_field_position_destroy	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_field_position_clone_p(void)
{	
	START_TEST;
	i18n_field_position_h hClone = NULL;		
	
	//Target API
	int nRet = i18n_field_position_clone(g_hFieldPosition, &hClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_field_position_clone", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hClone, "i18n_field_position_clone");
	
	nRet = i18n_field_position_destroy(hClone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_field_position_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Sets/Gets the begin index
/**
* @testcase				ITc_i18n_field_position_set_get_begin_index_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Sets/Gets the begin index
* @apitarget			i18n_field_position_set_begin_index, i18n_field_position_get_begin_index	
* @apicovered			i18n_field_position_set_begin_index, i18n_field_position_get_begin_index	
* @passcase				I18N_ERROR_NONE returned by i18n_field_position_set_begin_index, i18n_field_position_get_begin_index	
* @failcase				I18N_ERROR_NONE not returned by i18n_field_position_set_begin_index, i18n_field_position_get_begin_index or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_field_position_set_get_begin_index_p(void)
{	
	START_TEST;
	
	int32_t nBeginIndex = 10;
    int32_t nRetBeginIndex = -1;
	
    int nRet = i18n_field_position_set_begin_index(g_hFieldPosition, nBeginIndex);
    PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_field_position_set_begin_index", BaseUtilsGetError(nRet));
	
	nRet = i18n_field_position_get_begin_index(g_hFieldPosition, &nRetBeginIndex);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_field_position_get_begin_index", BaseUtilsGetError(nRet));
		
	if(nBeginIndex != nRetBeginIndex)
	{
		FPRINTF("\\n[Line : %d][%s] nRetBeginIndex return value is not correct!!\\n", __LINE__, API_NAMESPACE);		
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: Sets/Gets the end index
/**
* @testcase				ITc_i18n_field_position_set_get_end_index_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Sets/Gets the end index
* @apitarget			i18n_field_position_set_end_index, i18n_field_position_get_end_index	
* @apicovered			i18n_field_position_set_end_index, i18n_field_position_get_end_index	
* @passcase				I18N_ERROR_NONE returned by i18n_field_position_set_end_index, i18n_field_position_get_end_index	
* @failcase				I18N_ERROR_NONE not returned by i18n_field_position_set_end_index, i18n_field_position_get_end_index or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_field_position_set_get_end_index_p(void)
{	
	START_TEST;
	
	int32_t nEndIndex = 15;
    int32_t nRetEndIndex = -1;
	
    int nRet = i18n_field_position_set_end_index(g_hFieldPosition, nEndIndex);
    PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_field_position_set_end_index", BaseUtilsGetError(nRet));
	
	nRet = i18n_field_position_get_end_index(g_hFieldPosition, &nRetEndIndex);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_field_position_get_end_index", BaseUtilsGetError(nRet));
		
	if(nEndIndex != nRetEndIndex)
	{
		FPRINTF("\\n[Line : %d][%s] nRetEndIndex return value is not correct!!\\n", __LINE__, API_NAMESPACE);		
		return 1;
	}
	
	return 0;
}

/** @} */
/** @} */