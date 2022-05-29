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

static i18n_parse_position_h g_hParsePosition = NULL;


/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/

//& set: BaseUtilsUbrk 
void ITs_base_utils_parse_position_startup(void)
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
	
    int nRet =  i18n_parse_position_create(&g_hParsePosition);
    if (nRet != I18N_ERROR_NONE) {
       g_bBaseUtilsInitFlag = false;	
    }
	else if(g_hParsePosition == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] g_hParsePosition is null\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;			
	}
	else
	{
		g_bBaseUtilsInitFlag = true;
	}
	
	return;
}

void ITs_base_utils_parse_position_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	 if (g_hParsePosition != NULL) {
        i18n_parse_position_destroy(g_hParsePosition);
        g_hParsePosition = NULL;
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
//& purpose: Creates a parse position object
/**
* @testcase				ITc_i18n_parse_position_create_destroy_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Creates a parse position object
* @apitarget			i18n_parse_position_create, i18n_parse_position_destroy	
* @apicovered			i18n_parse_position_create, i18n_parse_position_destroy	
* @passcase				I18N_ERROR_NONE returned by i18n_parse_position_create, i18n_parse_position_destroy	
* @failcase				I18N_ERROR_NONE not returned by i18n_parse_position_create, i18n_parse_position_destroy	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_parse_position_create_destroy_p(void)
{	
	START_TEST;
	
	i18n_parse_position_h hParsePosition = NULL;

	//Target API
	int nRet = i18n_parse_position_create(&hParsePosition);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_parse_position_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hParsePosition, "i18n_parse_position_create");
	
	//Target API
	nRet = i18n_parse_position_destroy(hParsePosition);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_parse_position_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Creates a parse position object with the given initial index
/**
* @testcase				ITc_i18n_parse_position_create_with_index_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Creates a parse position object with the given initial index
* @apitarget			i18n_parse_position_create_with_index, i18n_parse_position_destroy	
* @apicovered			i18n_parse_position_create_with_index, i18n_parse_position_destroy	
* @passcase				I18N_ERROR_NONE returned by i18n_parse_position_create_with_index, i18n_parse_position_destroy	
* @failcase				I18N_ERROR_NONE not returned by i18n_parse_position_create_with_index, i18n_parse_position_destroy	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_parse_position_create_with_index_p(void)
{	
	START_TEST;
	
	i18n_parse_position_h hParsePosition = NULL;
	int32_t nIndex = 13;
	
	//Target API
	int nRet = i18n_parse_position_create_with_index(nIndex, &hParsePosition);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_parse_position_create_with_index", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hParsePosition, "i18n_parse_position_create_with_index");
	
	//Target API
	nRet = i18n_parse_position_destroy(hParsePosition);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_parse_position_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Sets/Gets the current parse position
/**
* @testcase				ITc_i18n_parse_position_set_get_index_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Sets/Gets the current parse position
* @apitarget			i18n_parse_position_set_index, i18n_parse_position_get_index	
* @apicovered			i18n_parse_position_set_index, i18n_parse_position_get_index	
* @passcase				I18N_ERROR_NONE returned by i18n_parse_position_set_index, i18n_parse_position_get_index	
* @failcase				I18N_ERROR_NONE not returned by i18n_parse_position_set_index, i18n_parse_position_get_index	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_parse_position_set_get_index_p(void)
{	
	START_TEST;
	
	int32_t nIndex = 13;
	int32_t ngetIndex = -1;
	
	//Target API
	int nRet = i18n_parse_position_set_index(g_hParsePosition, nIndex);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_parse_position_set_index", BaseUtilsGetError(nRet));
	
	//Target API
	nRet = i18n_parse_position_get_index(g_hParsePosition, &ngetIndex);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_parse_position_get_index", BaseUtilsGetError(nRet));

	if(nIndex != ngetIndex)
	{
		FPRINTF("\\n[Line : %d][%s] ngetIndex is retuned value is not correct!!\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Creates a clone of the given @a parse_position object
/**
* @testcase				ITc_i18n_parse_position_clone_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Creates a clone of the given @a parse_position object
* @apitarget			i18n_parse_position_clone, i18n_parse_position_destroy	
* @apicovered			i18n_parse_position_clone, i18n_parse_position_destroy	
* @passcase				I18N_ERROR_NONE returned by i18n_parse_position_clone, i18n_parse_position_destroy	
* @failcase				I18N_ERROR_NONE not returned by i18n_parse_position_clone, i18n_parse_position_destroy	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_parse_position_clone_p(void)
{	
	START_TEST;
	
	i18n_parse_position_h hClone = NULL;
	
	//Target API
	int nRet = i18n_parse_position_clone(g_hParsePosition, &hClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_parse_position_clone", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hClone, "i18n_parse_position_clone");

	nRet = i18n_parse_position_destroy(hClone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_parse_position_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Sets/Gets the index at which a parse error occurred
/**
* @testcase				ITc_i18n_parse_position_set_get_error_index_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Sets/Gets the index at which a parse error occurred
* @apitarget			i18n_parse_position_set_error_index, i18n_parse_position_get_error_index	
* @apicovered			i18n_parse_position_set_error_index, i18n_parse_position_get_error_index	
* @passcase				I18N_ERROR_NONE returned by i18n_parse_position_set_error_index, i18n_parse_position_get_error_index	
* @failcase				I18N_ERROR_NONE not returned by i18n_parse_position_set_error_index, i18n_parse_position_get_error_index	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_parse_position_set_get_error_index_p(void)
{	
	START_TEST;

	int32_t nErrorIndexToSet = 13;
	int32_t nGetErrorIndex = -1;
	
	//Target API
	int nRet = i18n_parse_position_set_error_index(g_hParsePosition, nErrorIndexToSet);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_parse_position_set_error_index", BaseUtilsGetError(nRet));
	
	//Target API
	nRet = i18n_parse_position_get_error_index(g_hParsePosition, &nGetErrorIndex);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_parse_position_get_error_index", BaseUtilsGetError(nRet));

	if(nErrorIndexToSet != nGetErrorIndex)
	{
		FPRINTF("\\n[Line : %d][%s] nGetErrorIndex is retuned value is not correct!!\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

/** @} */
/** @} */