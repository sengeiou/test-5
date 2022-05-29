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

static i18n_format_h g_hFormat = NULL;


/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/

//& set: BaseUtilsUbrk 
void ITs_base_utils_format_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	i18n_measure_format_h measure_format = NULL;
    const char *language = I18N_ULOCALE_ENGLISH;
    const char *country = "US";

    int nRet = i18n_measure_format_create_currency_format_from_locale(language, country, &measure_format);
    if (nRet == I18N_ERROR_NONE) {
        nRet = i18n_measure_format_clone(measure_format, &g_hFormat);
		if(nRet != I18N_ERROR_NONE)
		{
			FPRINTF("\\n[Line : %d][%s] i18n_measure_format_clone failed in startup\\n", __LINE__, API_NAMESPACE);
			g_bBaseUtilsInitFlag = false;
		}
        i18n_measure_format_destroy(measure_format);
    }
	g_bBaseUtilsInitFlag = true;
	
	return;
}

void ITs_base_utils_format_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	if (g_hFormat != NULL) {
        i18n_format_destroy(g_hFormat);
        g_hFormat = NULL;
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
//& purpose: Formats an object to produce a string
/**
* @testcase				ITc_i18n_format_format_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Formats an object to produce a string
* @apitarget			i18n_format_format, i18n_formattable_create_with_double, i18n_formattable_destroy		
* @apicovered			i18n_format_format, i18n_formattable_create_with_double, i18n_formattable_destroy
* @passcase				I18N_ERROR_NONE returned by i18n_format_format , i18n_formattable_destroy and i18n_formattable_create_with_double
* @failcase				I18N_ERROR_NONE not returned by i18n_format_format , i18n_formattable_destroy or i18n_formattable_create_with_double or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_format_format_p(void)
{	
	START_TEST;
	
	double double_to_set = 13.0;
    i18n_formattable_h hFormattable = NULL;
    char *append_to = "Price: ";

	int nRet = i18n_formattable_create_with_double(double_to_set, &hFormattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_formattable_create_with_double", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hFormattable, "i18n_formattable_create_with_double");
	
	//Target API
	nRet = i18n_format_format(g_hFormat, hFormattable, &append_to);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_format_format", BaseUtilsGetError(nRet));
	
	if(strcmp(append_to, "Price: $13.00") != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] append_to is not set \\n", __LINE__, API_NAMESPACE);		
		i18n_formattable_destroy(hFormattable);
		FREE_MEMORY(append_to);
		return 1;		
	}
	FREE_MEMORY(append_to);
	
	nRet = i18n_formattable_destroy(hFormattable);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_formattable_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Creates a polymorphic clone of the given @a format object.
/**
* @testcase				ITc_i18n_format_clone_destroy_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Creates a polymorphic clone of the given @a format object.
* @apitarget			i18n_format_clone, i18n_format_destroy		
* @apicovered			i18n_format_clone, i18n_format_destroy 
* @passcase				I18N_ERROR_NONE returned by i18n_format_clone and i18n_format_destroy
* @failcase				I18N_ERROR_NONE not returned by i18n_format_clone or i18n_format_destroy or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_format_clone_destroy_p(void)
{	
	START_TEST;
	
	i18n_format_h hClone = NULL;
	
	//Target API
	int nRet = i18n_format_clone(g_hFormat, &hClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_format_clone", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hClone, "i18n_format_clone");
	
	//Target API
	nRet = i18n_format_destroy(hClone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Formats an object to produce a string.
/**
* @testcase				ITc_i18n_format_format_with_field_position_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Formats an object to produce a string.
* @apitarget			i18n_format_format_with_field_position, i18n_formattable_create_with_double, i18n_formattable_destroy		
* @apicovered			i18n_format_format_with_field_position, i18n_formattable_create_with_double, i18n_formattable_destroy
* @passcase				I18N_ERROR_NONE returned by i18n_format_format_with_field_position , i18n_formattable_destroy and i18n_formattable_create_with_double
* @failcase				I18N_ERROR_NONE not returned by i18n_format_format_with_field_position , i18n_formattable_destroy or i18n_formattable_create_with_double or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_format_format_with_field_position_p(void)
{	
	START_TEST;
	
	double double_to_set = 13.0;
    i18n_formattable_h hFormattable = NULL;
    i18n_field_position_h hFieldPosition = NULL;
	char *append_to = "Price: ";

	int nRet = i18n_formattable_create_with_double(double_to_set, &hFormattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_formattable_create_with_double", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hFormattable, "i18n_formattable_create_with_double");
		
    nRet = i18n_field_position_create(&hFieldPosition);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_field_position_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE_CLEANUP(hFieldPosition, "i18n_field_position_create",i18n_formattable_destroy(hFormattable));
	
	//Target API
	nRet = i18n_format_format_with_field_position(g_hFormat, hFormattable, &append_to, hFieldPosition);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_format_format_with_field_position", BaseUtilsGetError(nRet));
	
	if(strcmp(append_to, "Price: $13.00") != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] append_to is not set \\n", __LINE__, API_NAMESPACE);		
		i18n_formattable_destroy(hFormattable);
		i18n_field_position_destroy(hFieldPosition);
		FREE_MEMORY(append_to);
		return 1;		
	}
	FREE_MEMORY(append_to);
	
	nRet = i18n_field_position_destroy(hFieldPosition);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_field_position_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_formattable_destroy(hFormattable);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_formattable_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Parses a string to produce an object
/**
* @testcase				ITc_i18n_format_parse_object_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Parses a string to produce an object
* @apitarget			i18n_format_parse_object, i18n_formattable_get_double, i18n_formattable_destroy		
* @apicovered			i18n_format_parse_object, i18n_formattable_get_double, i18n_formattable_destroy
* @passcase				I18N_ERROR_NONE returned by i18n_format_parse_object , i18n_formattable_destroy and i18n_formattable_get_double
* @failcase				I18N_ERROR_NONE not returned by i18n_format_parse_object , i18n_formattable_destroy or i18n_formattable_get_doubley or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_format_parse_object_p(void)
{	
	START_TEST;
	
	char *source = "$1,234.56";
    i18n_formattable_h hFormattable = NULL;
    double value = 0;

	//Target API
	int nRet = i18n_format_parse_object(g_hFormat, source, &hFormattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_format_parse_object", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hFormattable, "i18n_format_parse_object");
	
	nRet = i18n_formattable_get_double(hFormattable, &value);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_formattable_get_double", BaseUtilsGetError(nRet));
	
	if(value != 1234.56 )
	{
		FPRINTF("\\n[Line : %d][%s] In i18n_format_parse_object object not parsed!! \\n", __LINE__, API_NAMESPACE);		
		i18n_formattable_destroy(hFormattable);	
		return 1;		
	}

	nRet = i18n_formattable_destroy(hFormattable);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_formattable_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Parses a string to produce an object
/**
* @testcase				ITc_i18n_format_parse_object_with_parse_position_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Parses a string to produce an object
* @apitarget			i18n_format_parse_object_with_parse_position, i18n_parse_position_create, i18n_formattable_destroy		
* @apicovered			i18n_format_parse_object_with_parse_position, i18n_parse_position_create, i18n_formattable_destroy
* @passcase				I18N_ERROR_NONE returned by i18n_format_parse_object_with_parse_position , i18n_formattable_destroy and i18n_parse_position_create
* @failcase				I18N_ERROR_NONE not returned by i18n_format_parse_object_with_parse_position , i18n_formattable_destroy or i18n_parse_position_create or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_format_parse_object_with_parse_position_p(void)
{	
	START_TEST;
	
	char *source = "$1,234.56";
    i18n_formattable_h hFormattable = NULL;
    i18n_parse_position_h hParsePosition = NULL;

	double value = 0;

	int nRet = i18n_parse_position_create(&hParsePosition);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_parse_position_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hParsePosition, "i18n_parse_position_create");
	
	//Target API
	nRet = i18n_format_parse_object_with_parse_position(g_hFormat, source, hParsePosition, &hFormattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_format_parse_object_with_parse_position", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hFormattable, "i18n_format_parse_object_with_parse_position");
	
	nRet = i18n_formattable_get_double(hFormattable, &value);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_formattable_get_double", BaseUtilsGetError(nRet));
	
	if(value != 1234.56 )
	{
		FPRINTF("\\n[Line : %d][%s] In i18n_format_parse_object_with_parse_position object not parsed!! \\n", __LINE__, API_NAMESPACE);		
		i18n_formattable_destroy(hFormattable);	
		i18n_parse_position_destroy(hParsePosition);
		return 1;
	}
	
	nRet = i18n_formattable_destroy(hFormattable);	
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_formattable_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_parse_position_destroy(hParsePosition);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_parse_position_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: ets the locale for the given format object
/**
* @testcase				ITc_i18n_format_get_locale_id_p
* @since_tizen 			5.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				-gets the locale for the given format object
* @apitarget			i18n_format_get_locale_id,
* @apicovered			i18n_format_get_locale_id,
* @passcase				I18N_ERROR_NONE returned by i18n_format_get_locale_id , i18n_formattable_destroy and i18n_formattable_create_with_double
* @failcase				I18N_ERROR_NONE not returned by i18n_format_get_locale_id , i18n_formattable_destroy or i18n_formattable_create_with_double or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_format_get_locale_id_p(void)
{	
	START_TEST;
	
	i18n_ulocale_data_locale_type_e type = I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE;

    char *pszLocalId = NULL;

	//Target API
	int nRet = i18n_format_get_locale_id(g_hFormat, type, &pszLocalId);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "ITc_i18n_format_get_locale_id_p", BaseUtilsGetError(nRet));
	CHECK_HANDLE(pszLocalId, "i18n_format_get_locale");
	if(strcmp(pszLocalId, "en_US")!= 0 )
	{
		FPRINTF("\\n[Line : %d][%s] locale_id is wrong \\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszLocalId);
		return 1;
	}

	FREE_MEMORY(pszLocalId);

	return 0;
}


/** @} */
/** @} */