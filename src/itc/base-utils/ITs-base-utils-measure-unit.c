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

//& set: BaseUtilsMeasureUnit
void ITs_base_utils_measure_unit_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif


	return;
}

void ITs_base_utils_measure_unit_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif


	return;
}

/** @addtogroup itc-base-utils-testcases
*  @brief 		Integration testcases for module base-utils ucalendar
*  @ingroup 	itc-base-utils
*  @{
*/

static bool MeasureUnitAvailableTypesCB(const char *type_id, void *user_data)
{
    FPRINTF("\\n[Line : %d][%s] MeasureUnitAvailableTypesCB hit type_id [%s]\\n", __LINE__, API_NAMESPACE,type_id);
	g_bCallbackHit = true;

    return false;
}

//& type: auto
//& purpose: Creates the default measure unit object
/**
* @testcase				ITc_i18n_measure_unit_create_destroy_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Creates the default measure unit object
* @apitarget			i18n_measure_unit_create, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_destroy_p(void)
{
	START_TEST_PRINT;
	i18n_measure_unit_h hMeasureUnit = NULL;

	//Target API
	int nRet = i18n_measure_unit_create(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit, "i18n_measure_unit_create");

	//Target API
	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Creates a polymorphic clone of the given @a clone object
/**
* @testcase				ITc_i18n_measure_unit_clone_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Creates a polymorphic clone of the given @a clone object
* @apitarget			i18n_measure_unit_clone, i18n_measure_unit_destroy, i18n_measure_unit_create_megahertz, i18n_measure_unit_get_type
* @apicovered			i18n_measure_unit_clone, i18n_measure_unit_destroy, i18n_measure_unit_create_megahertz, i18n_measure_unit_get_type
* @passcase				When i18n_measure_unit_clone, i18n_measure_unit_destroy, i18n_measure_unit_create_megahertz, i18n_measure_unit_get_type is successful
* @failcase				If target i18n_measure_unit_clone, i18n_measure_unit_destroy, i18n_measure_unit_create_megahertz, i18n_measure_unit_get_type API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_clone_p(void)
{
	START_TEST_PRINT;
	i18n_measure_unit_h hMeasureUnit = NULL;
	i18n_measure_unit_h hClone = NULL;
	char *pSubtype = NULL;
	char *type = NULL;
	char *pRefSubtype = "megahertz";
	const char *pRefType = "frequency";

	//Target API
	int nRet = i18n_measure_unit_create_megahertz(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_megahertz", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit, "i18n_measure_unit_create_megahertz");

	//Target API
	nRet = i18n_measure_unit_clone(hMeasureUnit, &hClone);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_clone", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	CHECK_HANDLE(hClone, "i18n_measure_unit_clone");

	//Target API
	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hClone);i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hClone);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	//Target API
	nRet = i18n_measure_unit_get_subtype(hClone, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hClone);i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hClone);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets all of the available units
/**
* @testcase				ITc_i18n_measure_unit_get_available_destroy_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets all of the available units
* @apitarget			i18n_measure_unit_get_available, i18n_measure_unit_array_destroy
* @apicovered			i18n_measure_unit_get_available, i18n_measure_unit_array_destroy
* @passcase				When i18n_measure_unit_get_available, i18n_measure_unit_array_destroy is successful
* @failcase				If target i18n_measure_unit_get_available, i18n_measure_unit_array_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_get_available_destroy_p(void)
{
	START_TEST_PRINT;

	int32_t available = -1;
    i18n_measure_unit_h *hDestAray = NULL;
    int32_t dest_capacity = 3000;

	//Target API
	int nRet = i18n_measure_unit_get_available(dest_capacity, &hDestAray, &available);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_available", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hDestAray, "i18n_measure_unit_get_available");

	//Target API
	nRet = i18n_measure_unit_array_destroy(hDestAray, available);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_array_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets all of the available units for a specific type.
/**
* @testcase				ITc_i18n_measure_unit_get_available_with_type_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets all of the available units for a specific type.
* @apitarget			i18n_measure_unit_get_available_with_type, i18n_measure_unit_array_destroy
* @apicovered			i18n_measure_unit_get_available_with_type, i18n_measure_unit_array_destroy
* @passcase				When i18n_measure_unit_get_available_with_type, i18n_measure_unit_array_destroy is successful
* @failcase				If target i18n_measure_unit_get_available_with_type, i18n_measure_unit_array_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_get_available_with_type_p(void)
{
	START_TEST_PRINT;

	int32_t available = -1;
	const char *type = "area";
    i18n_measure_unit_h *hDestAray = NULL;
    int32_t dest_capacity = 3000;


	//Target API
	int nRet = i18n_measure_unit_get_available_with_type(dest_capacity, type, &hDestAray, &available);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_available_with_type", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hDestAray, "i18n_measure_unit_get_available_with_type");

	nRet = i18n_measure_unit_array_destroy(hDestAray, available);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_array_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Invokes the given callback function for every available measure unit type
/**
* @testcase				ITc_i18n_measure_unit_foreach_available_type_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Invokes the given callback function for every available measure unit type.
* @apitarget			i18n_measure_unit_foreach_available_type, i18n_measure_unit_array_destroy
* @apicovered			i18n_measure_unit_foreach_available_type, i18n_measure_unit_array_destroy
* @passcase				When i18n_measure_unit_foreach_available_type, i18n_measure_unit_array_destroy is successful
* @failcase				If target i18n_measure_unit_foreach_available_type, i18n_measure_unit_array_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_foreach_available_type_p(void)
{
	START_TEST_PRINT;

	g_bCallbackHit = false;
	int nTimeoutId = 0;

	//Target API
	int nRet = i18n_measure_unit_foreach_available_type(MeasureUnitAvailableTypesCB, NULL);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_foreach_available_type", BaseUtilsGetError(nRet));
	RUN_POLLING_LOOP;
	if(!g_bCallbackHit)
	{
		FPRINTF("\\n[Line : %d][%s] MeasureUnitAvailableTypesCB callback not invoked in i18n_measure_unit_foreach_available_type!! \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Gets unit of acceleration: g-force
/**
* @testcase				ITc_i18n_measure_unit_create_g_force_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of acceleration: g-force
* @apitarget			i18n_measure_unit_create_g_force, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_g_force, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_g_force, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_g_force, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_g_force_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "acceleration";
    const char *pRefSubtype = "g-force";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_g_force(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_g_force", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_g_force");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of acceleration: meter-per-square-second
/**
* @testcase				ITc_i18n_measure_unit_create_meter_per_second_squared_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of acceleration: meter-per-square-second
* @apitarget			i18n_measure_unit_create_meter_per_second_squared, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_meter_per_second_squared, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_meter_per_second_squared, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_meter_per_second_squared, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_meter_per_second_squared_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "acceleration";
    const char *pRefSubtype_latest = "meter-per-square-second";
    const char *pRefSubtype_old = "meter-per-second-squared";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_meter_per_second_squared(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_meter_per_second_squared", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_meter_per_second_squared");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype_latest) != 0
				&& strcmp(pSubtype, pRefSubtype_old) !=0)
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of angle: arc-minute
/**
* @testcase				ITc_i18n_measure_unit_create_arc_minute_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of angle: arc-minute
* @apitarget			i18n_measure_unit_create_arc_minute, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_arc_minute, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_arc_minute, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_arc_minute, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_arc_minute_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "angle";
    const char *pRefSubtype = "arc-minute";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_arc_minute(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_arc_minute", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_arc_minute");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of angle: arc-second
/**
* @testcase				ITc_i18n_measure_unit_create_arc_second_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of angle: arc-second
* @apitarget			i18n_measure_unit_create_arc_second, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_arc_second, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_arc_second, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_arc_second, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_arc_second_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "angle";
    const char *pRefSubtype = "arc-second";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_arc_second(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_arc_second", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_arc_second");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of angle: degree
/**
* @testcase				ITc_i18n_measure_unit_create_degree_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of angle: degree
* @apitarget			i18n_measure_unit_create_degree, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_degree, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_degree, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_degree, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_degree_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "angle";
    const char *pRefSubtype = "degree";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_degree(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_degree", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_degree");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of angle: radian.
/**
* @testcase				ITc_i18n_measure_unit_create_radian_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of angle: radian.
* @apitarget			i18n_measure_unit_create_radian, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_radian, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_radian, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_radian, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_radian_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "angle";
    const char *pRefSubtype = "radian";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_radian(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_radian", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_radian");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of area: acre
/**
* @testcase				ITc_i18n_measure_unit_create_acre_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of area: acre
* @apitarget			i18n_measure_unit_create_acre, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_acre, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_acre, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_acre, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_acre_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "area";
    const char *pRefSubtype = "acre";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_acre(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_acre", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_acre");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of area: hectare
/**
* @testcase				ITc_i18n_measure_unit_create_hectare_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of area: hectare
* @apitarget			i18n_measure_unit_create_hectare, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_hectare, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_hectare, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_hectare, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_hectare_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "area";
    const char *pRefSubtype = "hectare";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_hectare(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_hectare", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_hectare");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of area: square-centimeter
/**
* @testcase				ITc_i18n_measure_unit_create_square_centimeter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of area: square-centimeter
* @apitarget			i18n_measure_unit_create_square_centimeter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_square_centimeter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_square_centimeter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_square_centimeter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_square_centimeter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "area";
    const char *pRefSubtype = "square-centimeter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_square_centimeter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_square_centimeter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_square_centimeter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}


//& type: auto
//& purpose: Gets unit of area: square-foot
/**
* @testcase				ITc_i18n_measure_unit_create_square_foot_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of area: square-foot
* @apitarget			i18n_measure_unit_create_square_foot, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_square_foot, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_square_foot, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_square_foot, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_square_foot_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "area";
    const char *pRefSubtype = "square-foot";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_square_foot(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_square_foot", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_square_foot");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of area: square-inch
/**
* @testcase				ITc_i18n_measure_unit_create_square_inch_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of area: square-inch
* @apitarget			i18n_measure_unit_create_square_inch, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_square_inch, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_square_inch, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_square_inch, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_square_inch_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "area";
    const char *pRefSubtype = "square-inch";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_square_inch(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_square_inch", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_square_inch");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of area: square-kilometer
/**
* @testcase				ITc_i18n_measure_unit_create_square_kilometer_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of area: square-kilometer
* @apitarget			i18n_measure_unit_create_square_kilometer, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_square_kilometer, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_square_kilometer, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_square_kilometer, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_square_kilometer_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "area";
    const char *pRefSubtype = "square-kilometer";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_square_kilometer(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_square_kilometer", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_square_kilometer");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of area: square-meter
/**
* @testcase				ITc_i18n_measure_unit_create_square_meter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of area: square-meter
* @apitarget			i18n_measure_unit_create_square_meter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_square_meter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_square_meter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_square_meter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_square_meter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "area";
    const char *pRefSubtype = "square-meter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_square_meter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_square_meter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_square_meter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of area: square-mile
/**
* @testcase				ITc_i18n_measure_unit_create_square_mile_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of area: square-mile
* @apitarget			i18n_measure_unit_create_square_mile, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_square_mile, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_square_mile, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_square_mile, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_square_mile_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "area";
    const char *pRefSubtype = "square-mile";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_square_mile(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_square_mile", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_square_mile");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of area: square-yard
/**
* @testcase				ITc_i18n_measure_unit_create_square_yard_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of area: square-yard
* @apitarget			i18n_measure_unit_create_square_yard, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_square_yard, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_square_yard, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_square_yard, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_square_yard_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "area";
    const char *pRefSubtype = "square-yard";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_square_yard(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_square_yard", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_square_yard");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of consumption: liter-per-kilometer
/**
* @testcase				ITc_i18n_measure_unit_create_liter_per_kilometer_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of consumption: liter-per-kilometer
* @apitarget			i18n_measure_unit_create_liter_per_kilometer, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_liter_per_kilometer, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_liter_per_kilometer, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_liter_per_kilometer, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_liter_per_kilometer_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "consumption";
    const char *pRefSubtype = "liter-per-kilometer";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_liter_per_kilometer(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_liter_per_kilometer", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_liter_per_kilometer");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of consumption: mile-per-gallon
/**
* @testcase				ITc_i18n_measure_unit_create_mile_per_gallon_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of consumption: mile-per-gallon
* @apitarget			i18n_measure_unit_create_mile_per_gallon, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_mile_per_gallon, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_mile_per_gallon, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_mile_per_gallon, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_mile_per_gallon_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "consumption";
    const char *pRefSubtype = "mile-per-gallon";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_mile_per_gallon(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_mile_per_gallon", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_mile_per_gallon");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of digital: bit
/**
* @testcase				ITc_i18n_measure_unit_create_bit_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of digital: bit
* @apitarget			i18n_measure_unit_create_bit, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_bit, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_bit, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_bit, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_bit_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "digital";
    const char *pRefSubtype = "bit";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_bit(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_bit", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_bit");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of digital: byte
/**
* @testcase				ITc_i18n_measure_unit_create_byte_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of digital: byte
* @apitarget			i18n_measure_unit_create_byte, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_byte, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_byte, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_byte, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_byte_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "digital";
    const char *pRefSubtype = "byte";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_byte(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_byte", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_byte");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of digital: gigabit
/**
* @testcase				ITc_i18n_measure_unit_create_gigabit_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of digital: gigabit
* @apitarget			i18n_measure_unit_create_gigabit, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_gigabit, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_gigabit, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_gigabit, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_gigabit_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "digital";
    const char *pRefSubtype = "gigabit";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_gigabit(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_gigabit", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_gigabit");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of digital: gigabyte
/**
* @testcase				ITc_i18n_measure_unit_create_gigabyte_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of digital: gigabyte
* @apitarget			i18n_measure_unit_create_gigabyte, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_gigabyte, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_gigabyte, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_gigabyte, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_gigabyte_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "digital";
    const char *pRefSubtype = "gigabyte";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_gigabyte(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_gigabyte", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_gigabyte");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of digital: kilobit
/**
* @testcase				ITc_i18n_measure_unit_create_kilobit_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of digital: kilobit
* @apitarget			i18n_measure_unit_create_kilobit, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_kilobit, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_kilobit, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_kilobit, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_kilobit_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "digital";
    const char *pRefSubtype = "kilobit";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_kilobit(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_kilobit", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_kilobit");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of digital: kilobyte
/**
* @testcase				ITc_i18n_measure_unit_create_kilobyte_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of digital: kilobyte
* @apitarget			i18n_measure_unit_create_kilobyte, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_kilobyte, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_kilobyte, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_kilobyte, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_kilobyte_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "digital";
    const char *pRefSubtype = "kilobyte";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_kilobyte(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_kilobyte", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_kilobyte");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of digital: megabit
/**
* @testcase				ITc_i18n_measure_unit_create_megabit_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of digital: megabit
* @apitarget			i18n_measure_unit_create_megabit, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_megabit, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_megabit, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_megabit, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_megabit_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "digital";
    const char *pRefSubtype = "megabit";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_megabit(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_megabit", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_megabit");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of digital: megabyte
/**
* @testcase				ITc_i18n_measure_unit_create_megabyte_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of digital: megabyte
* @apitarget			i18n_measure_unit_create_megabyte, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_megabyte, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_megabyte, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_megabyte, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_megabyte_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "digital";
    const char *pRefSubtype = "megabyte";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_megabyte(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_megabyte", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_megabyte");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of digital: terabit
/**
* @testcase				ITc_i18n_measure_unit_create_terabit_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of digital: terabit
* @apitarget			i18n_measure_unit_create_terabit, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_terabit, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_terabit, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_terabit, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_terabit_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "digital";
    const char *pRefSubtype = "terabit";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_terabit(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_terabit", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_terabit");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of digital: terabyte
/**
* @testcase				ITc_i18n_measure_unit_create_terabyte_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of digital: terabyte
* @apitarget			i18n_measure_unit_create_terabyte, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_terabyte, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_terabyte, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_terabyte, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_terabyte_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "digital";
    const char *pRefSubtype = "terabyte";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_terabyte(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_terabyte", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_terabyte");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of duration: day
/**
* @testcase				ITc_i18n_measure_unit_create_day_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of duration: day
* @apitarget			i18n_measure_unit_create_day, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_day, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_day, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_day, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_day_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "duration";
    const char *pRefSubtype = "day";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_day(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_day", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_day");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of duration: hour
/**
* @testcase				ITc_i18n_measure_unit_create_hour_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of duration: hour
* @apitarget			i18n_measure_unit_create_hour, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_hour, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_hour, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_hour, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_hour_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "duration";
    const char *pRefSubtype = "hour";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_hour(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_hour", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_hour");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of duration: microsecond
/**
* @testcase				ITc_i18n_measure_unit_create_microsecond_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of duration: microsecond
* @apitarget			i18n_measure_unit_create_microsecond, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_microsecond, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_microsecond, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_microsecond, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_microsecond_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "duration";
    const char *pRefSubtype = "microsecond";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_microsecond(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_microsecond", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_microsecond");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of duration: millisecond
/**
* @testcase				ITc_i18n_measure_unit_create_millisecond_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of duration: millisecond
* @apitarget			i18n_measure_unit_create_millisecond, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_millisecond, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_millisecond, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_millisecond, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_millisecond_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "duration";
    const char *pRefSubtype = "millisecond";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_millisecond(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_millisecond", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_millisecond");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of duration: minute
/**
* @testcase				ITc_i18n_measure_unit_create_minute_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of duration: minute
* @apitarget			i18n_measure_unit_create_minute, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_minute, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_minute, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_minute, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_minute_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "duration";
    const char *pRefSubtype = "minute";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_minute(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_minute", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_minute");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of duration: month
/**
* @testcase				ITc_i18n_measure_unit_create_month_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of duration: month
* @apitarget			i18n_measure_unit_create_month, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_month, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_month, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_month, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_month_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "duration";
    const char *pRefSubtype = "month";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_month(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_month", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_month");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of duration: nanosecond
/**
* @testcase				ITc_i18n_measure_unit_create_nanosecond_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of duration: nanosecond
* @apitarget			i18n_measure_unit_create_nanosecond, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_nanosecond, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_nanosecond, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_nanosecond, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_nanosecond_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "duration";
    const char *pRefSubtype = "nanosecond";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_nanosecond(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_nanosecond", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_nanosecond");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of duration: second
/**
* @testcase				ITc_i18n_measure_unit_create_second_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of duration: second
* @apitarget			i18n_measure_unit_create_second, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_second, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_second, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_second, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_second_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "duration";
    const char *pRefSubtype = "second";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_second(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_second", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_second");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of duration: week
/**
* @testcase				ITc_i18n_measure_unit_create_week_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of duration: week
* @apitarget			i18n_measure_unit_create_week, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_week, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_week, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_week, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_week_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "duration";
    const char *pRefSubtype = "week";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_week(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_week", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_week");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of duration: year
/**
* @testcase				ITc_i18n_measure_unit_create_year_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of duration: year
* @apitarget			i18n_measure_unit_create_year, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_year, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_year, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_year, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_year_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "duration";
    const char *pRefSubtype = "year";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_year(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_year", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_year");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of electric: ampere
/**
* @testcase				ITc_i18n_measure_unit_create_ampere_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of electric: ampere
* @apitarget			i18n_measure_unit_create_ampere, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_ampere, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_ampere, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_ampere, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_ampere_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "electric";
    const char *pRefSubtype = "ampere";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_ampere(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_ampere", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_ampere");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of electric: milliampere
/**
* @testcase				ITc_i18n_measure_unit_create_milliampere_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of electric: milliampere
* @apitarget			i18n_measure_unit_create_milliampere, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_milliampere, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_milliampere, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_milliampere, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_milliampere_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "electric";
    const char *pRefSubtype = "milliampere";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_milliampere(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_milliampere", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_milliampere");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of electric: ohm
/**
* @testcase				ITc_i18n_measure_unit_create_ohm_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of electric: ohm
* @apitarget			i18n_measure_unit_create_ohm, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_ohm, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_ohm, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_ohm, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_ohm_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "electric";
    const char *pRefSubtype = "ohm";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_ohm(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_ohm", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_ohm");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of electric: volt
/**
* @testcase				ITc_i18n_measure_unit_create_volt_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of electric: volt
* @apitarget			i18n_measure_unit_create_volt, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_volt, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_volt, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_volt, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_volt_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "electric";
    const char *pRefSubtype = "volt";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_volt(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_volt", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_volt");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of energy: calorie
/**
* @testcase				ITc_i18n_measure_unit_create_calorie_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of energy: calorie
* @apitarget			i18n_measure_unit_create_calorie, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_calorie, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_calorie, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_calorie, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_calorie_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "energy";
    const char *pRefSubtype = "calorie";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_calorie(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_calorie", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_calorie");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of energy: foodcalorie
/**
* @testcase				ITc_i18n_measure_unit_create_foodcalorie_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of energy: foodcalorie
* @apitarget			i18n_measure_unit_create_foodcalorie, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_foodcalorie, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_foodcalorie, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_foodcalorie, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_foodcalorie_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "energy";
    const char *pRefSubtype = "foodcalorie";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_foodcalorie(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_foodcalorie", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_foodcalorie");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of energy: joule
/**
* @testcase				ITc_i18n_measure_unit_create_joule_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of energy: joule
* @apitarget			i18n_measure_unit_create_joule, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_joule, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_joule, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_joule, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_joule_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "energy";
    const char *pRefSubtype = "joule";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_joule(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_joule", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_joule");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of energy: kilocalorie
/**
* @testcase				ITc_i18n_measure_unit_create_kilocalorie_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of energy: kilocalorie
* @apitarget			i18n_measure_unit_create_kilocalorie, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_kilocalorie, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_kilocalorie, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_kilocalorie, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_kilocalorie_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "energy";
    const char *pRefSubtype = "kilocalorie";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_kilocalorie(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_kilocalorie", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_kilocalorie");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of energy: kilojoule
/**
* @testcase				ITc_i18n_measure_unit_create_kilojoule_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of energy: kilojoule
* @apitarget			i18n_measure_unit_create_kilojoule, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_kilojoule, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_kilojoule, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_kilojoule, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_kilojoule_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "energy";
    const char *pRefSubtype = "kilojoule";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_kilojoule(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_kilojoule", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_kilojoule");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of energy: kilowatt-hour
/**
* @testcase				ITc_i18n_measure_unit_create_kilowatt_hour_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of energy: kilowatt-hour
* @apitarget			i18n_measure_unit_create_kilowatt_hour, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_kilowatt_hour, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_kilowatt_hour, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_kilowatt_hour, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_kilowatt_hour_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "energy";
    const char *pRefSubtype = "kilowatt-hour";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_kilowatt_hour(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_kilowatt_hour", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_kilowatt_hour");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of frequency: gigahertz
/**
* @testcase				ITc_i18n_measure_unit_create_gigahertz_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of frequency: gigahertz
* @apitarget			i18n_measure_unit_create_gigahertz, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_gigahertz, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_gigahertz, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_gigahertz, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_gigahertz_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "frequency";
    const char *pRefSubtype = "gigahertz";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_gigahertz(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_gigahertz", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_gigahertz");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of frequency: hertz
/**
* @testcase				ITc_i18n_measure_unit_create_hertz_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of frequency: hertz
* @apitarget			i18n_measure_unit_create_hertz, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_hertz, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_hertz, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_hertz, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_hertz_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "frequency";
    const char *pRefSubtype = "hertz";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_hertz(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_hertz", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_hertz");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of frequency: kilohertz
/**
* @testcase				ITc_i18n_measure_unit_create_kilohertz_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of frequency: kilohertz
* @apitarget			i18n_measure_unit_create_kilohertz, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_kilohertz, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_kilohertz, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_kilohertz, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_kilohertz_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "frequency";
    const char *pRefSubtype = "kilohertz";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_kilohertz(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_kilohertz", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_kilohertz");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of frequency: megahertz
/**
* @testcase				ITc_i18n_measure_unit_create_megahertz_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of frequency: megahertz
* @apitarget			i18n_measure_unit_create_megahertz, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_megahertz, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_megahertz, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_megahertz, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_megahertz_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "frequency";
    const char *pRefSubtype = "megahertz";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_megahertz(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_megahertz", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_megahertz");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: astronomical-unit
/**
* @testcase				ITc_i18n_measure_unit_create_astronomical_unit_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: astronomical-unit
* @apitarget			i18n_measure_unit_create_astronomical_unit, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_astronomical_unit, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_astronomical_unit, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_astronomical_unit, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_astronomical_unit_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "astronomical-unit";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_astronomical_unit(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_astronomical_unit", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_astronomical_unit");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: centimeter
/**
* @testcase				ITc_i18n_measure_unit_create_centimeter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: centimeter
* @apitarget			i18n_measure_unit_create_centimeter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_centimeter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_centimeter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_centimeter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_centimeter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "centimeter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_centimeter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_centimeter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_centimeter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: decimeter
/**
* @testcase				ITc_i18n_measure_unit_create_decimeter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: decimeter
* @apitarget			i18n_measure_unit_create_decimeter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_decimeter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_decimeter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_decimeter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_decimeter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "decimeter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_decimeter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_decimeter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_decimeter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: fathom
/**
* @testcase				ITc_i18n_measure_unit_create_fathom_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: fathom
* @apitarget			i18n_measure_unit_create_fathom, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_fathom, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_fathom, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_fathom, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_fathom_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "fathom";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_fathom(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_fathom", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_fathom");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: foot
/**
* @testcase				ITc_i18n_measure_unit_create_foot_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: foot
* @apitarget			i18n_measure_unit_create_foot, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_foot, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_foot, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_foot, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_foot_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "foot";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_foot(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_foot", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_foot");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: furlong
/**
* @testcase				ITc_i18n_measure_unit_create_furlong_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: furlong
* @apitarget			i18n_measure_unit_create_furlong, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_furlong, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_furlong, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_furlong, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_furlong_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "furlong";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_furlong(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_furlong", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_furlong");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: inch
/**
* @testcase				ITc_i18n_measure_unit_create_inch_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: inch
* @apitarget			i18n_measure_unit_create_inch, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_inch, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_inch, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_inch, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_inch_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "inch";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_inch(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_inch", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_inch");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: kilometer
/**
* @testcase				ITc_i18n_measure_unit_create_kilometer_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: kilometer
* @apitarget			i18n_measure_unit_create_kilometer, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_kilometer, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_kilometer, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_kilometer, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_kilometer_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "kilometer";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_kilometer(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_kilometer", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_kilometer");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: light-year
/**
* @testcase				ITc_i18n_measure_unit_create_light_year_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: light-year
* @apitarget			i18n_measure_unit_create_light_year, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_light_year, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_light_year, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_light_year, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_light_year_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "light-year";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_light_year(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_light_year", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_light_year");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: meter
/**
* @testcase				ITc_i18n_measure_unit_create_meter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: meter
* @apitarget			i18n_measure_unit_create_meter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_meter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_meter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_meter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_meter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "meter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_meter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_meter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_meter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: micrometer
/**
* @testcase				ITc_i18n_measure_unit_create_micrometer_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: micrometer
* @apitarget			i18n_measure_unit_create_micrometer, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_micrometer, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_micrometer, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_micrometer, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_micrometer_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "micrometer";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_micrometer(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_micrometer", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_micrometer");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: mile
/**
* @testcase				ITc_i18n_measure_unit_create_mile_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: mile
* @apitarget			i18n_measure_unit_create_mile, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_mile, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_mile, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_mile, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_mile_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "mile";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_mile(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_mile", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_mile");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: millimeter
/**
* @testcase				ITc_i18n_measure_unit_create_millimeter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: millimeter
* @apitarget			i18n_measure_unit_create_millimeter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_millimeter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_millimeter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_millimeter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_millimeter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "millimeter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_millimeter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_millimeter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_millimeter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: nanometer
/**
* @testcase				ITc_i18n_measure_unit_create_nanometer_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: nanometer
* @apitarget			i18n_measure_unit_create_nanometer, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_nanometer, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_nanometer, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_nanometer, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_nanometer_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "nanometer";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_nanometer(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_nanometer", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_nanometer");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: nautical-mile
/**
* @testcase				ITc_i18n_measure_unit_create_nautical_mile_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: nautical-mile
* @apitarget			i18n_measure_unit_create_nautical_mile, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_nautical_mile, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_nautical_mile, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_nautical_mile, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_nautical_mile_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "nautical-mile";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_nautical_mile(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_nautical_mile", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_nautical_mile");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: parsec
/**
* @testcase				ITc_i18n_measure_unit_create_parsec_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: parsec
* @apitarget			i18n_measure_unit_create_parsec, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_parsec, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_parsec, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_parsec, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_parsec_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "parsec";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_parsec(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_parsec", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_parsec");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: picometer
/**
* @testcase				ITc_i18n_measure_unit_create_picometer_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: picometer
* @apitarget			i18n_measure_unit_create_picometer, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_picometer, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_picometer, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_picometer, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_picometer_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "picometer";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_picometer(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_picometer", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_picometer");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: yard
/**
* @testcase				ITc_i18n_measure_unit_create_yard_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: yard
* @apitarget			i18n_measure_unit_create_yard, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_yard, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_yard, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_yard, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_yard_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "length";
    const char *pRefSubtype = "yard";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_yard(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_yard", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_yard");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets unit of length: lux
/**
* @testcase				ITc_i18n_measure_unit_create_lux_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of length: lux
* @apitarget			i18n_measure_unit_create_lux, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_lux, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_lux, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_lux, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_lux_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "light";
    const char *pRefSubtype = "lux";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_lux(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_lux", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_lux");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of mass: carat
/**
* @testcase				ITc_i18n_measure_unit_create_carat_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of mass: carat
* @apitarget			i18n_measure_unit_create_carat, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_carat, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_carat, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_carat, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_carat_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "mass";
    const char *pRefSubtype = "carat";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_carat(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_carat", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_carat");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of mass: gram
/**
* @testcase				ITc_i18n_measure_unit_create_gram_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of mass: gram
* @apitarget			i18n_measure_unit_create_gram, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_gram, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_gram, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_gram, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_gram_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "mass";
    const char *pRefSubtype = "gram";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_gram(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_gram", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_gram");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of mass: kilogram
/**
* @testcase				ITc_i18n_measure_unit_create_kilogram_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of mass: kilogram
* @apitarget			i18n_measure_unit_create_kilogram, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_kilogram, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_kilogram, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_kilogram, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_kilogram_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "mass";
    const char *pRefSubtype = "kilogram";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_kilogram(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_kilogram", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_kilogram");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of mass: metric-ton
/**
* @testcase				ITc_i18n_measure_unit_create_metric_ton_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of mass: metric-ton
* @apitarget			i18n_measure_unit_create_metric_ton, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_metric_ton, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_metric_ton, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_metric_ton, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_metric_ton_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "mass";
    const char *pRefSubtype = "metric-ton";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_metric_ton(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_metric_ton", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_metric_ton");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of mass: microgram
/**
* @testcase				ITc_i18n_measure_unit_create_microgram_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of mass: microgram
* @apitarget			i18n_measure_unit_create_microgram, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_microgram, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_microgram, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_microgram, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_microgram_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "mass";
    const char *pRefSubtype = "microgram";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_microgram(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_microgram", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_microgram");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of mass: milligram
/**
* @testcase				ITc_i18n_measure_unit_create_milligram_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of mass: milligram
* @apitarget			i18n_measure_unit_create_milligram, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_milligram, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_milligram, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_milligram, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_milligram_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "mass";
    const char *pRefSubtype = "milligram";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_milligram(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_milligram", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_milligram");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of mass: ounce
/**
* @testcase				ITc_i18n_measure_unit_create_ounce_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of mass: ounce
* @apitarget			i18n_measure_unit_create_ounce, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_ounce, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_ounce, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_ounce, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_ounce_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "mass";
    const char *pRefSubtype = "ounce";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_ounce(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_ounce", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_ounce");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of mass: ounce-troy
/**
* @testcase				ITc_i18n_measure_unit_create_ounce_troy_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of mass: ounce-troy
* @apitarget			i18n_measure_unit_create_ounce_troy, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_ounce_troy, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_ounce_troy, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_ounce_troy, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_ounce_troy_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "mass";
    const char *pRefSubtype = "ounce-troy";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_ounce_troy(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_ounce_troy", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_ounce_troy");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of mass: pound
/**
* @testcase				ITc_i18n_measure_unit_create_pound_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of mass: pound
* @apitarget			i18n_measure_unit_create_pound, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_pound, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_pound, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_pound, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_pound_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "mass";
    const char *pRefSubtype = "pound";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_pound(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_pound", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_pound");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of mass: stone
/**
* @testcase				ITc_i18n_measure_unit_create_stone_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of mass: stone
* @apitarget			i18n_measure_unit_create_stone, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_stone, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_stone, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_stone, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_stone_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "mass";
    const char *pRefSubtype = "stone";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_stone(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_stone", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_stone");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of mass: ton
/**
* @testcase				ITc_i18n_measure_unit_create_ton_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of mass: ton
* @apitarget			i18n_measure_unit_create_ton, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_ton, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_ton, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_ton, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_ton_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "mass";
    const char *pRefSubtype = "ton";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_ton(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_ton", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_ton");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of power: gigawatt
/**
* @testcase				ITc_i18n_measure_unit_create_gigawatt_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of power: gigawatt
* @apitarget			i18n_measure_unit_create_gigawatt, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_gigawatt, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_gigawatt, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_gigawatt, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_gigawatt_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "power";
    const char *pRefSubtype = "gigawatt";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_gigawatt(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_gigawatt", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_gigawatt");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of power: horsepower
/**
* @testcase				ITc_i18n_measure_unit_create_horsepower_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of power: horsepower
* @apitarget			i18n_measure_unit_create_horsepower, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_horsepower, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_horsepower, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_horsepower, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_horsepower_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "power";
    const char *pRefSubtype = "horsepower";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_horsepower(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_horsepower", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_horsepower");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of power: kilowatt
/**
* @testcase				ITc_i18n_measure_unit_create_kilowatt_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of power: kilowatt
* @apitarget			i18n_measure_unit_create_kilowatt, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_kilowatt, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_kilowatt, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_kilowatt, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_kilowatt_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "power";
    const char *pRefSubtype = "kilowatt";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_kilowatt(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_kilowatt", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_kilowatt");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of power: megawatt
/**
* @testcase				ITc_i18n_measure_unit_create_megawatt_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of power: megawatt
* @apitarget			i18n_measure_unit_create_megawatt, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_megawatt, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_megawatt, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_megawatt, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_megawatt_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "power";
    const char *pRefSubtype = "megawatt";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_megawatt(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_megawatt", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_megawatt");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of power: milliwatt
/**
* @testcase				ITc_i18n_measure_unit_create_milliwatt_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of power: milliwatt
* @apitarget			i18n_measure_unit_create_milliwatt, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_milliwatt, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_milliwatt, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_milliwatt, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_milliwatt_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "power";
    const char *pRefSubtype = "milliwatt";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_milliwatt(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_milliwatt", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_milliwatt");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of power: watt
/**
* @testcase				ITc_i18n_measure_unit_create_watt_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of power: watt
* @apitarget			i18n_measure_unit_create_watt, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_watt, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_watt, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_watt, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_watt_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "power";
    const char *pRefSubtype = "watt";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_watt(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_watt", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_watt");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of pressure: hectopascal
/**
* @testcase				ITc_i18n_measure_unit_create_hectopascal_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of pressure: hectopascal
* @apitarget			i18n_measure_unit_create_hectopascal, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_hectopascal, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_hectopascal, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_hectopascal, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_hectopascal_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "pressure";
    const char *pRefSubtype = "hectopascal";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_hectopascal(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_hectopascal", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_hectopascal");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of pressure: inch-ofhg
/**
* @testcase				ITc_i18n_measure_unit_create_inch_hg_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of pressure: inch-ofhg
* @apitarget			i18n_measure_unit_create_inch_hg, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_inch_hg, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_inch_hg, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_inch_hg, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_inch_hg_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "pressure";
    const char *pRefSubtype_latest = "inch-ofhg";
    const char *pRefSubtype_old = "inch-hg";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_inch_hg(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_inch_hg", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_inch_hg");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype_latest) != 0
				&& strcmp(pSubtype, pRefSubtype_old) !=0)
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of pressure: millibar
/**
* @testcase				ITc_i18n_measure_unit_create_millibar_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of pressure: millibar
* @apitarget			i18n_measure_unit_create_millibar, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_millibar, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_millibar, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_millibar, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_millibar_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "pressure";
    const char *pRefSubtype = "millibar";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_millibar(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_millibar", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_millibar");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of pressure: millimeter-ofhg
/**
* @testcase				ITc_i18n_measure_unit_create_millimeter_of_mercury_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of pressure: millimeter-ofhg
* @apitarget			i18n_measure_unit_create_millimeter_of_mercury, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_millimeter_of_mercury, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_millimeter_of_mercury, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_millimeter_of_mercury, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_millimeter_of_mercury_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "pressure";
    const char *pRefSubtype_latest = "millimeter-ofhg";
    const char *pRefSubtype_old = "millimeter-of-mercury";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_millimeter_of_mercury(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_millimeter_of_mercury", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_millimeter_of_mercury");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype_latest) != 0
				&& strcmp(pSubtype, pRefSubtype_old) !=0)
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of pressure: pound-force-per-square-inch
/**
* @testcase				ITc_i18n_measure_unit_create_pound_per_square_inch_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				 Gets unit of pressure: pound-force-per-square-inch
* @apitarget			i18n_measure_unit_create_pound_per_square_inch, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_pound_per_square_inch, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_pound_per_square_inch, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_pound_per_square_inch, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_pound_per_square_inch_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "pressure";
    const char *pRefSubtype_latest = "pound-force-per-square-inch";
    const char *pRefSubtype_old = "pound-per-square-inch";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_pound_per_square_inch(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_pound_per_square_inch", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_pound_per_square_inch");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype_latest) != 0
				&& strcmp(pSubtype, pRefSubtype_old) !=0)
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Gets unit of proportion: karat
/**
* @testcase				ITc_i18n_measure_unit_create_karat_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of proportion: karat
* @apitarget			i18n_measure_unit_create_karat, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_karat, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_karat, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_karat, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_karat_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "concentr";
    const char *pRefSubtype = "karat";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_karat(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_karat", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_karat");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of speed: kilometer-per-hour.
/**
* @testcase				ITc_i18n_measure_unit_create_kilometer_per_hour_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of speed: kilometer-per-hour.
* @apitarget			i18n_measure_unit_create_kilometer_per_hour, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_kilometer_per_hour, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_kilometer_per_hour, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_kilometer_per_hour, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_kilometer_per_hour_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "speed";
    const char *pRefSubtype = "kilometer-per-hour";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_kilometer_per_hour(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_kilometer_per_hour", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_kilometer_per_hour");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of speed: meter-per-second
/**
* @testcase				ITc_i18n_measure_unit_create_meter_per_second_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of speed: meter-per-second.
* @apitarget			i18n_measure_unit_create_meter_per_second, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_meter_per_second, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_meter_per_second, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_meter_per_second, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_meter_per_second_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "speed";
    const char *pRefSubtype = "meter-per-second";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_meter_per_second(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_meter_per_second", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_meter_per_second");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of speed: mile-per-hour
/**
* @testcase				ITc_i18n_measure_unit_create_mile_per_hour_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of speed: mile-per-hour
* @apitarget			i18n_measure_unit_create_mile_per_hour, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_mile_per_hour, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_mile_per_hour, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_mile_per_hour, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_mile_per_hour_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "speed";
    const char *pRefSubtype = "mile-per-hour";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_mile_per_hour(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_mile_per_hour", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_mile_per_hour");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of temperature: celsius
/**
* @testcase				ITc_i18n_measure_unit_create_celsius_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of temperature: celsius
* @apitarget			i18n_measure_unit_create_celsius, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_celsius, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_celsius, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_celsius, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_celsius_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "temperature";
    const char *pRefSubtype = "celsius";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_celsius(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_celsius", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_celsius");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of temperature: fahrenheit
/**
* @testcase				ITc_i18n_measure_unit_create_fahrenheit_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of temperature: fahrenheit
* @apitarget			i18n_measure_unit_create_fahrenheit, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_fahrenheit, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_fahrenheit, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_fahrenheit, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_fahrenheit_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "temperature";
    const char *pRefSubtype = "fahrenheit";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_fahrenheit(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_fahrenheit", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_fahrenheit");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of temperature: kelvin
/**
* @testcase				ITc_i18n_measure_unit_create_kelvin_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of temperature: kelvin
* @apitarget			i18n_measure_unit_create_kelvin, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_kelvin, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_kelvin, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_kelvin, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_kelvin_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "temperature";
    const char *pRefSubtype = "kelvin";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_kelvin(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_kelvin", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_kelvin");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: acre-foot
/**
* @testcase				ITc_i18n_measure_unit_create_acre_foot_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: acre-foot
* @apitarget			i18n_measure_unit_create_acre_foot, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_acre_foot, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_acre_foot, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_acre_foot, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_acre_foot_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "acre-foot";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_acre_foot(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_acre_foot", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_acre_foot");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: bushel
/**
* @testcase				ITc_i18n_measure_unit_create_bushel_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: bushel
* @apitarget			i18n_measure_unit_create_bushel, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_bushel, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_bushel, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_bushel, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_bushel_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "bushel";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_bushel(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_bushel", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_bushel");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: centiliter
/**
* @testcase				ITc_i18n_measure_unit_create_centiliter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: centiliter
* @apitarget			i18n_measure_unit_create_centiliter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_centiliter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_centiliter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_centiliter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_centiliter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "centiliter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_centiliter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_centiliter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_centiliter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: cubic-centimeter
/**
* @testcase				ITc_i18n_measure_unit_create_cubic_centimeter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: cubic-centimeter
* @apitarget			i18n_measure_unit_create_cubic_centimeter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_cubic_centimeter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_cubic_centimeter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_cubic_centimeter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_cubic_centimeter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "cubic-centimeter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_cubic_centimeter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_cubic_centimeter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_cubic_centimeter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: cubic-foot
/**
* @testcase				ITc_i18n_measure_unit_create_cubic_foot_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: cubic-foot
* @apitarget			i18n_measure_unit_create_cubic_foot, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_cubic_foot, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_cubic_foot, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_cubic_foot, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_cubic_foot_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "cubic-foot";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_cubic_foot(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_cubic_foot", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_cubic_foot");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: cubic-inch
/**
* @testcase				ITc_i18n_measure_unit_create_cubic_inch_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: cubic-inch
* @apitarget			i18n_measure_unit_create_cubic_inch, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_cubic_inch, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_cubic_inch, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_cubic_inch, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_cubic_inch_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "cubic-inch";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_cubic_inch(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_cubic_inch", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_cubic_inch");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: cubic-kilometer
/**
* @testcase				ITc_i18n_measure_unit_create_cubic_kilometer_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: cubic-kilometer
* @apitarget			i18n_measure_unit_create_cubic_kilometer, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_cubic_kilometer, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_cubic_kilometer, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_cubic_kilometer, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_cubic_kilometer_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "cubic-kilometer";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_cubic_kilometer(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_cubic_kilometer", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_cubic_kilometer");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: cubic-meter
/**
* @testcase				ITc_i18n_measure_unit_create_cubic_meter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: cubic-meter
* @apitarget			i18n_measure_unit_create_cubic_meter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_cubic_meter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_cubic_meter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_cubic_meter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_cubic_meter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "cubic-meter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_cubic_meter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_cubic_meter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_cubic_meter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: cubic-mile
/**
* @testcase				ITc_i18n_measure_unit_create_cubic_mile_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: cubic-mile
* @apitarget			i18n_measure_unit_create_cubic_mile, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_cubic_mile, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_cubic_mile, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_cubic_mile, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_cubic_mile_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "cubic-mile";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_cubic_mile(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_cubic_mile", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_cubic_mile");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: cubic-yard
/**
* @testcase				ITc_i18n_measure_unit_create_cubic_yard_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: cubic-yard
* @apitarget			i18n_measure_unit_create_cubic_yard, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_cubic_yard, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_cubic_yard, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_cubic_yard, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_cubic_yard_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "cubic-yard";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_cubic_yard(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_cubic_yard", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_cubic_yard");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: cup
/**
* @testcase				ITc_i18n_measure_unit_create_cup_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: cup
* @apitarget			i18n_measure_unit_create_cup, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_cup, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_cup, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_cup, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_cup_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "cup";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_cup(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_cup", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_cup");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: deciliter
/**
* @testcase				ITc_i18n_measure_unit_create_deciliter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: deciliter
* @apitarget			i18n_measure_unit_create_deciliter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_deciliter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_deciliter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_deciliter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_deciliter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "deciliter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_deciliter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_deciliter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_deciliter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: fluid-ounce
/**
* @testcase				ITc_i18n_measure_unit_create_fluid_ounce_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: fluid-ounce
* @apitarget			i18n_measure_unit_create_fluid_ounce, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_fluid_ounce, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_fluid_ounce, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_fluid_ounce, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_fluid_ounce_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "fluid-ounce";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_fluid_ounce(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_fluid_ounce", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_fluid_ounce");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: gallon
/**
* @testcase				ITc_i18n_measure_unit_create_gallon_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: gallon
* @apitarget			i18n_measure_unit_create_gallon, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_gallon, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_gallon, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_gallon, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_gallon_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "gallon";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_gallon(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_gallon", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_gallon");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: hectoliter
/**
* @testcase				ITc_i18n_measure_unit_create_hectoliter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: hectoliter
* @apitarget			i18n_measure_unit_create_hectoliter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_hectoliter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_hectoliter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_hectoliter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_hectoliter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "hectoliter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_hectoliter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_hectoliter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_hectoliter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: liter
/**
* @testcase				ITc_i18n_measure_unit_create_liter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: liter
* @apitarget			i18n_measure_unit_create_liter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_liter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_liter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_liter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_liter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "liter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_liter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_liter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_liter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: megaliter
/**
* @testcase				ITc_i18n_measure_unit_create_megaliter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: megaliter
* @apitarget			i18n_measure_unit_create_megaliter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_megaliter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_megaliter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_megaliter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_megaliter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "megaliter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_megaliter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_megaliter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_megaliter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: milliliter
/**
* @testcase				ITc_i18n_measure_unit_create_milliliter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: milliliter
* @apitarget			i18n_measure_unit_create_milliliter, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_milliliter, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_milliliter, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_milliliter, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_milliliter_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "milliliter";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_milliliter(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_milliliter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_milliliter");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: pint
/**
* @testcase				ITc_i18n_measure_unit_create_pint_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: pint
* @apitarget			i18n_measure_unit_create_pint, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_pint, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_pint, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_pint, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_pint_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "pint";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_pint(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_pint", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_pint");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: quart
/**
* @testcase				ITc_i18n_measure_unit_create_quart_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: quart
* @apitarget			i18n_measure_unit_create_quart, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_quart, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_quart, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_quart, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_quart_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "quart";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_quart(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_quart", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_quart");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: tablespoon
/**
* @testcase				ITc_i18n_measure_unit_create_tablespoon_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: tablespoon
* @apitarget			i18n_measure_unit_create_tablespoon, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_tablespoon, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_tablespoon, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_tablespoon, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_tablespoon_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "tablespoon";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_tablespoon(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_tablespoon", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_tablespoon");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:   Gets unit of volume: teaspoon
/**
* @testcase				ITc_i18n_measure_unit_create_teaspoon_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets unit of volume: teaspoon
* @apitarget			i18n_measure_unit_create_teaspoon, i18n_measure_unit_destroy
* @apicovered			i18n_measure_unit_create_teaspoon, i18n_measure_unit_destroy
* @passcase				When i18n_measure_unit_create_teaspoon, i18n_measure_unit_destroy is successful
* @failcase				If target i18n_measure_unit_create_teaspoon, i18n_measure_unit_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_unit_create_teaspoon_p(void)
{
	START_TEST_PRINT;

	i18n_measure_unit_h hMeasureUnit = NULL;
	const char *pRefType = "volume";
    const char *pRefSubtype = "teaspoon";
	char *pSubtype = NULL;
	char *type = NULL;

	//Target API
	int nRet = i18n_measure_unit_create_teaspoon(&hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_teaspoon", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureUnit,"i18n_measure_unit_create_teaspoon");

	nRet = i18n_measure_unit_get_type(hMeasureUnit, &type);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(type, pRefType) !=0 )
	{
		FPRINTF("\\n[Line : %d][%s] type is not set as pRefType\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(type);
		return 1;
	}
	FREE_MEMORY(type);

	nRet = i18n_measure_unit_get_subtype(hMeasureUnit, &pSubtype);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_unit_get_subtype", BaseUtilsGetError(nRet),i18n_measure_unit_destroy(hMeasureUnit));
	if(strcmp(pSubtype, pRefSubtype) != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] pSubtype is not set as pRefSubtype\\n", __LINE__, API_NAMESPACE);
		i18n_measure_unit_destroy(hMeasureUnit);
		FREE_MEMORY(pSubtype);
		return 1;
	}
	FREE_MEMORY(pSubtype);

	nRet = i18n_measure_unit_destroy(hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_destroy", BaseUtilsGetError(nRet));

	return 0;
}

/** @} */
/** @} */
