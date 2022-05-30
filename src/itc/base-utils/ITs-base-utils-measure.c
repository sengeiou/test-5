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

static i18n_measure_h g_hMeasure = NULL;
static i18n_formattable_h g_hFormattable = NULL;
static i18n_measure_unit_h g_hMeasure_unit = NULL;

/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/

//& set: BaseUtilsUbrk 
void ITs_base_utils_measure_startup(void)
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
    int32_t value = 7;
			
    int nRet = i18n_formattable_create_with_long(value, &g_hFormattable);
	if (nRet != I18N_ERROR_NONE || g_hFormattable == NULL)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_formattable_create_with_long: failed\\n", __LINE__, API_NAMESPACE);	
	}
	
    nRet = i18n_measure_unit_create_gigabit(&g_hMeasure_unit);
    if (nRet != I18N_ERROR_NONE || g_hMeasure_unit == NULL) 
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_measure_unit_create_gigabit: failed\\n", __LINE__, API_NAMESPACE);	
	}
	
    nRet = i18n_measure_create(g_hFormattable, g_hMeasure_unit, &g_hMeasure);
	if (nRet != I18N_ERROR_NONE || g_hMeasure == NULL) 
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_measure_create: failed\\n", __LINE__, API_NAMESPACE);	
	}
	else{
		g_bBaseUtilsInitFlag = true;
	}
	
	return;
}

void ITs_base_utils_measure_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
    if (g_hMeasure != NULL) {
        i18n_measure_destroy(g_hMeasure);
	    g_hMeasure = NULL;

        g_hMeasure_unit = NULL;
        g_hFormattable = NULL;
    }

    if (g_hMeasure_unit != NULL) {
        i18n_measure_unit_destroy(g_hMeasure_unit);
	    g_hMeasure_unit = NULL;
    }

    if (g_hFormattable != NULL) {
        i18n_formattable_destroy(g_hFormattable);
	    g_hFormattable = NULL;
    }
	
	return;
}

/** @addtogroup itc-base-utils-testcases
*  @brief 		Integration testcases for module base-utils ubrk
*  @ingroup 	itc-base-utils
*  @{
*/

//& type: auto
//& purpose: Creates an object with the given numeric amount and the given unit
/**
* @testcase				ITc_i18n_measure_create_destroy_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Creates an object with the given numeric amount and the given unit
* @apitarget			i18n_measure_create, i18n_measure_destroy	
* @apicovered			i18n_measure_create, i18n_measure_destroy	
* @passcase				I18N_ERROR_NONE returned by i18n_measure_create, i18n_measure_destroy	
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_create, i18n_measure_destroy	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_create_destroy_p(void)
{	
	START_TEST;
	
	if (g_hMeasure != NULL) {
        i18n_measure_destroy(g_hMeasure);
        g_hMeasure = NULL;

        g_hMeasure_unit = NULL;
        g_hFormattable = NULL;
    }

    if (g_hMeasure_unit != NULL) {
        i18n_measure_unit_destroy(g_hMeasure_unit);
        g_hMeasure_unit = NULL;
    }

    if (g_hFormattable != NULL) {
        i18n_formattable_destroy(g_hFormattable);
        g_hFormattable = NULL;
    }
	
	int nRet = i18n_measure_unit_create(&g_hMeasure_unit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(g_hMeasure_unit, "i18n_measure_unit_create");
		
	nRet = i18n_formattable_create_default(&g_hFormattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_formattable_create_default", BaseUtilsGetError(nRet));
	CHECK_HANDLE(g_hFormattable, "i18n_formattable_create_default");
		
	//Target API
	nRet = i18n_measure_create(g_hFormattable, g_hMeasure_unit, &g_hMeasure);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(g_hMeasure, "i18n_measure_create");

		//Target API
	nRet = i18n_measure_destroy(g_hMeasure);	
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_destroy", BaseUtilsGetError(nRet));
		   
    g_hMeasure = NULL;
    g_hMeasure_unit = NULL;
    g_hFormattable = NULL;
	
	return 0;
}

//& type: auto
//& purpose: Creates a polymorphic clone of the given @a clone object.
/**
* @testcase				ITc_i18n_measure_clone_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Creates a polymorphic clone of the given @a clone object.
* @apitarget			i18n_measure_clone,  i18n_measure_destroy	
* @apicovered			i18n_measure_clone,  i18n_measure_destroy	
* @passcase				I18N_ERROR_NONE returned by i18n_measure_clone,  i18n_measure_destroy	
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_clone,  i18n_measure_destroy	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_clone_p(void)
{	
	START_TEST;

	i18n_measure_h hMeasureClone = NULL;
	
	//Target API
	int nRet = i18n_measure_clone(g_hMeasure, &hMeasureClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_clone", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureClone, "i18n_measure_clone");

	nRet = i18n_measure_destroy(hMeasureClone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_measure_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets a reference to the numeric value of the measure object.
/**
* @testcase				ITc_i18n_measure_get_number_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Gets a reference to the numeric value of the measure object.
* @apitarget			i18n_measure_get_number, i18n_formattable_destroy	
* @apicovered			i18n_measure_get_number, i18n_formattable_destroy	
* @passcase				I18N_ERROR_NONE returned by i18n_measure_get_number, i18n_formattable_destroy	
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_get_number, i18n_formattable_destroy	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_get_number_p(void)
{	
	START_TEST;
	
	i18n_formattable_h hFormattableClone = NULL;

	//Target API
	int nRet = i18n_measure_get_number(g_hMeasure, &hFormattableClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_get_number", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hFormattableClone, "i18n_measure_get_number");

	nRet = i18n_formattable_destroy(hFormattableClone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_formattable_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets a reference to the unit of the measure object
/**
* @testcase				ITc_i18n_measure_get_unit_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Gets a reference to the unit of the measure object
* @apitarget			i18n_measure_get_unit, i18n_measure_unit_destroy
* @apicovered			i18n_measure_get_unit, i18n_measure_unit_destroy
* @passcase				I18N_ERROR_NONE returned by i18n_measure_get_unit, i18n_measure_unit_destroy
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_get_unit, i18n_measure_unit_destroy or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_get_unit_p(void)
{	
	START_TEST;
	
	i18n_measure_unit_h hMeasureUnitClone = NULL;
	
	//Target API
	int nRet = i18n_measure_get_unit(g_hMeasure, &hMeasureUnitClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_get_unit", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnitClone, "i18n_measure_get_unit");

	nRet = i18n_measure_unit_destroy(hMeasureUnitClone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

/** @} */
/** @} */