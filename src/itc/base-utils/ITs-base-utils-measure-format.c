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

static i18n_measure_format_h g_hMeasureFormat = NULL;

/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/
#define MAX_MEASURES 3
#define BUFSIZE 256
static i18n_formattable_h g_hFormattable = NULL;
static i18n_field_position_h g_hFieldPos = NULL;
static char *g_pszStrAppend = NULL;
static int g_nMeasures = 0;
static i18n_measure_h g_hMeasureArr[MAX_MEASURES] = { NULL };
static i18n_measure_unit_h g_hMeasureUnit = NULL;
typedef int (*create_measure_unit_cb)(i18n_measure_unit_h *g_hMeasureUnit);

static int CreateMeasure(create_measure_unit_cb cb, double number, i18n_measure_h *h_measure)
{
	i18n_measure_unit_h g_hMeasureUnit = NULL;
	i18n_formattable_h g_hFormattable = NULL;
	*h_measure = NULL;

	int nRet = cb(&g_hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "cb", BaseUtilsGetError(nRet));
	CHECK_HANDLE(g_hMeasureUnit, "cb");

	nRet = i18n_formattable_create_with_double(number, &g_hFormattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_formattable_create_with_double", BaseUtilsGetError(nRet));
	CHECK_HANDLE(g_hFormattable, "i18n_formattable_create_with_double");

	nRet = i18n_measure_create(g_hFormattable, g_hMeasureUnit, h_measure);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(*h_measure, "i18n_measure_create");

	nRet = i18n_formattable_destroy(g_hFormattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_formattable_destroy", BaseUtilsGetError(nRet));

	return 0;
}

static int CreateMeasureLength(void)
{
	int nVal1 = 6378, nVal2 = 137;
	if(CreateMeasure(i18n_measure_unit_create_kilometer, nVal1, &g_hMeasureArr[0]) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] CreateMeasure fail in CreateMeasureLength call\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(CreateMeasure(i18n_measure_unit_create_meter, nVal2, &g_hMeasureArr[1]) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] CreateMeasure fail in CreateMeasureLength call\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	g_nMeasures = 2;

	return 0;
}

static int CreateMeasureUnit(void)
{
	int nVal1 = 300000;
	if(CreateMeasure(i18n_measure_unit_create_kilometer, nVal1, &g_hMeasureArr[0]) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] CreateMeasure fail in CreateMeasureUnit call\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	g_nMeasures = 1;

	return 0;
}

//& set: BaseUtilsUbrk 
void ITs_base_utils_measure_format_startup(void)
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

   const char *pszLocalId = "en_US";
    i18n_umeasure_format_width_e format_width = I18N_UMEASFMT_WIDTH_WIDE;

    int nRet =  i18n_measure_format_create_from_locale_id(pszLocalId, format_width, &g_hMeasureFormat);

    if (nRet != I18N_ERROR_NONE) {
       g_bBaseUtilsInitFlag = false;
    }
	else if(g_hMeasureFormat == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] g_hMeasureFormat is null\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
	}
	else
	{
		g_bBaseUtilsInitFlag = true;
	}
	
	return;
}

void ITs_base_utils_measure_format_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	if (g_hMeasureFormat != NULL) {
		i18n_measure_format_destroy(g_hMeasureFormat);
		g_hMeasureFormat = NULL;
	}
	g_bBaseUtilsInitFlag = false;

	if (g_hFormattable != NULL) {
		i18n_formattable_destroy(g_hFormattable);
		g_hFormattable = NULL;
	}

	if (g_hFieldPos != NULL) {
		i18n_field_position_destroy(g_hFieldPos);
		g_hFieldPos = NULL;
	}

	int i = 0;
	for (; i < g_nMeasures; ++i) {
		if (g_hMeasureArr[i] != NULL) {
			i18n_measure_destroy(g_hMeasureArr[i]);
			g_hMeasureArr[i] = NULL;
		}
	}
	g_nMeasures = 0;

	if (g_hMeasureUnit != NULL) {
		i18n_measure_unit_destroy(g_hMeasureUnit);
		g_hMeasureUnit = NULL;
	}

	free(g_pszStrAppend);
	g_pszStrAppend = NULL;

	return;
}

/** @addtogroup itc-base-utils-testcases
*  @brief 		Integration testcases for module base-utils ubrk
*  @ingroup 	itc-base-utils
*  @{
*/

//& type: auto
//& purpose: Creates the measure format object using given locale
/**
* @testcase				ITc_i18n_measure_format_create_destroy_from_locale_id_p
* @since_tizen 			5.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				- Creates the measure format object using given locale
* @apitarget			i18n_measure_format_create_from_locale_id, i18n_measure_format_destroy
* @apicovered			i18n_measure_format_create_from_locale_id, i18n_measure_format_destroy
* @passcase				I18N_ERROR_NONE returned by i18n_measure_format_create_from_locale_id, i18n_measure_format_destroy
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_format_create_from_locale_id, i18n_measure_format_destroy	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_format_create_destroy_from_locale_id_p(void)
{	
	START_TEST;
	
	const char *pszLocalId = "en_US";

	i18n_umeasure_format_width_e eFormatWidth = I18N_UMEASFMT_WIDTH_WIDE;
	i18n_measure_format_h hMeasureFormat = NULL;

	//Target API
	int nRet = i18n_measure_format_create_from_locale_id(pszLocalId, eFormatWidth, &hMeasureFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_format_create_from_locale_id", BaseUtilsGetError(nRet));

	//Target API
	nRet = i18n_measure_format_destroy(hMeasureFormat);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_measure_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Creates a polymorphic clone of the given @a measure_format object
/**
* @testcase				ITc_i18n_measure_format_clone_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Creates a polymorphic clone of the given @a measure_format object
* @apitarget			i18n_measure_format_clone, i18n_measure_format_destroy	
* @apicovered			i18n_measure_format_clone, i18n_measure_format_destroy	
* @passcase				I18N_ERROR_NONE returned by i18n_measure_format_clone, i18n_measure_format_destroy	
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_format_clone, i18n_measure_format_destroy	 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_format_clone_p(void)
{	
	START_TEST;

	i18n_measure_format_h hMeasureFormat = NULL;
	
	//Target API
	int nRet = i18n_measure_format_clone(g_hMeasureFormat, &hMeasureFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_format_clone", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureFormat, "i18n_measure_format_clone");
		
	nRet = i18n_measure_format_destroy(hMeasureFormat);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_measure_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Formats an object to produce a string
/**
* @testcase				ITc_i18n_measure_format_format_p
* @since_tizen 			3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @scenario				- Formats an object to produce a string
* @apitarget			i18n_measure_format_format, i18n_formattable_create_with_double, i18n_formattable_destroy
* @apicovered			i18n_measure_format_format, i18n_formattable_create_with_double, i18n_formattable_destroy
* @passcase				I18N_ERROR_NONE returned by i18n_measure_format_format , i18n_formattable_destroy and i18n_formattable_create_with_double
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_format_format , i18n_formattable_destroy or i18n_formattable_create_with_double or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_format_format_p(void)
{
	START_TEST;

	double double_to_set = 13.0;
	i18n_formattable_h hFormattable = NULL;

	char *g_pszStrAppend = NULL;
	const char *pszInput = "Price: ";
	int length = strlen(pszInput);
	g_pszStrAppend = (char *) malloc (sizeof(pszInput[8]) * (length + 1));
	strncpy(g_pszStrAppend, pszInput, length + 1);
	i18n_field_position_h hFieldPosition = NULL;
	const char *pszLocalId = "en_US";
	i18n_measure_format_h hMeasureFormat = NULL;

	int nRet = i18n_measure_format_create_currency_format_from_locale_id(pszLocalId, &hMeasureFormat);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_format_create_currency_format_from_locale_id", BaseUtilsGetError(nRet),FREE_MEMORY(g_pszStrAppend));
	CHECK_HANDLE_CLEANUP(hMeasureFormat, "i18n_measure_format_create_currency_format_from_locale_id",FREE_MEMORY(g_pszStrAppend));

	nRet = i18n_formattable_create_with_double(double_to_set, &hFormattable);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_formattable_create_with_double", BaseUtilsGetError(nRet),FREE_MEMORY(g_pszStrAppend));
	CHECK_HANDLE_CLEANUP(hFormattable, "i18n_formattable_create_with_double",FREE_MEMORY(g_pszStrAppend));

	nRet = i18n_field_position_create_for_field(0, &hFieldPosition);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_field_position_create_for_field", BaseUtilsGetError(nRet), FREE_MEMORY(g_pszStrAppend);i18n_formattable_destroy(hFormattable));
	CHECK_HANDLE_CLEANUP(hFieldPosition, "i18n_field_position_create_for_field",FREE_MEMORY(g_pszStrAppend);i18n_formattable_destroy(hFormattable));

	nRet = i18n_field_position_set_field(hFieldPosition, 1);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_field_position_set_field", BaseUtilsGetError(nRet), FREE_MEMORY(g_pszStrAppend);i18n_formattable_destroy(hFormattable));

	//Target API
	nRet = i18n_measure_format_format(hMeasureFormat, hFormattable, &g_pszStrAppend, hFieldPosition);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_format_format", BaseUtilsGetError(nRet),FREE_MEMORY(g_pszStrAppend);i18n_formattable_destroy(hFormattable));

	if(strcmp(g_pszStrAppend, "Price: $13.00") != 0 )
	{
		FPRINTF("\\n[Line : %d][%s] g_pszStrAppend is not set \\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(g_pszStrAppend);
		i18n_formattable_destroy(hFormattable);
		return 1;
	}

	FREE_MEMORY(g_pszStrAppend);

	nRet = i18n_formattable_destroy(hFormattable);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_formattable_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Parses a string to produce an object
/**
* @testcase				ITc_i18n_measure_format_parse_object_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Parses a string to produce an object
* @apitarget			i18n_measure_format_parse_object, i18n_parse_position_create, i18n_formattable_destroy		
* @apicovered			i18n_measure_format_parse_object, i18n_parse_position_create, i18n_formattable_destroy
* @passcase				I18N_ERROR_NONE returned by i18n_measure_format_parse_object , i18n_formattable_destroy and i18n_parse_position_create
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_format_parse_object , i18n_formattable_destroy or i18n_parse_position_create or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_format_parse_object_p(void)
{	
	START_TEST;
	
	char *source = "$1,234.56";
    i18n_formattable_h hFormattable = NULL;
    i18n_parse_position_h hParsePosition = NULL;
	
	int nRet = i18n_parse_position_create(&hParsePosition);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_parse_position_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hParsePosition, "i18n_parse_position_create");
	
	//Target API
	nRet = i18n_measure_format_parse_object(g_hMeasureFormat, source, hParsePosition, &hFormattable);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_format_parse_object", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hFormattable, "i18n_measure_format_parse_object");
	
	nRet = i18n_parse_position_destroy(hParsePosition);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_parse_position_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_formattable_destroy(hFormattable);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_formattable_destroy", BaseUtilsGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Gets a formatter for currency amount objects in the given locale
/**
* @testcase				ITc_i18n_measure_format_create_currency_format_from_locale_id_p
* @since_tizen 			5.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				- Gets a formatter for currency amount objects in the given locale
* @apitarget			i18n_measure_format_create_currency_format_from_locale_id
* @apicovered			i18n_measure_format_create_currency_format_from_locale_id
* @passcase				I18N_ERROR_NONE returned by i18n_measure_format_create_currency_format_from_locale_id
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_format_create_currency_format_from_locale_id or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_format_create_currency_format_from_locale_id_p(void)
{	
	START_TEST;

	const char *pszLocalId = "en_US";
	
	 if (g_hMeasureFormat != NULL) {
        i18n_measure_format_destroy(g_hMeasureFormat);
        g_hMeasureFormat = NULL;
    }
	
	//Target API
	int nRet = i18n_measure_format_create_currency_format_from_locale_id(pszLocalId, &g_hMeasureFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_format_create_currency_format_from_locale_id", BaseUtilsGetError(nRet));
	CHECK_HANDLE(g_hMeasureFormat, "i18n_measure_format_create_currency_format_from_locale_id");
	
	return 0;
}

//& type: auto
//& purpose: Gets a formatter for currency amount objects in the given locale
/**
* @testcase				ITc_i18n_measure_format_create_currency_format_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				- Gets a formatter for currency amount objects in the given locale
* @apitarget			i18n_measure_format_create_currency_format	
* @apicovered			i18n_measure_format_create_currency_format
* @passcase				I18N_ERROR_NONE returned by i18n_measure_format_create_currency_format 
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_format_create_currency_format or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_format_create_currency_format_p(void)
{	
	START_TEST;
	
	if (g_hMeasureFormat != NULL) {
        i18n_measure_format_destroy(g_hMeasureFormat);
        g_hMeasureFormat = NULL;
    }
	
	//Target API
	int nRet = i18n_measure_format_create_currency_format(&g_hMeasureFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_format_create_currency_format", BaseUtilsGetError(nRet));
	CHECK_HANDLE(g_hMeasureFormat, "i18n_measure_format_create_currency_format");
	
	return 0;
}

//& type: auto
//& purpose: Formats an object to produce a string.
/**
* @testcase				ITc_i18n_measure_format_format_buff_p
* @since_tizen			4.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Formats an object to produce a string.
* @apitarget			i18n_measure_format_format_buff
* @apicovered			i18n_measure_format_format_buff
* @passcase				I18N_ERROR_NONE returned by i18n_measure_format_format_buff
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_format_format_buff or any pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_format_format_buff_p(void)
{
	START_TEST;

	const char *pszInputString = "Price: ";
	const char *pszOutputString = "Price: $13.00";
	i18n_uchar g_pszStrAppend[BUFSIZE] = { 0 };
	char nOutputBuf[BUFSIZE] = { 0 };
	i18n_formattable_h g_hFormattable = NULL;
	i18n_uchar *pRet = NULL;
	int nLength;
	i18n_measure_format_h hMeasureFormatHandle = NULL;
	i18n_field_position_h hFieldPosHandle = NULL;
	double nDoubleValue = 13.0;
	int nOutputLen = -1;
	const char *pszLocalId = "en_US";

	if(CreateMeasureLength() != 0)
	{
		FPRINTF("[Line : %d][%s] CreateMeasureLength Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	pRet = i18n_ustring_copy_ua_n(g_pszStrAppend, pszInputString, BUFSIZE);
	nLength = i18n_ustring_get_length(g_pszStrAppend);
	if ( pRet == NULL || nLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = i18n_measure_format_create_currency_format_from_locale_id(pszLocalId, &hMeasureFormatHandle);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_format_create_currency_format_from_locale_id(pszLocalId, &hMeasureFormat);", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hMeasureFormatHandle, "i18n_measure_format_create_currency_format_from_locale_id(pszLocalId, &hMeasureFormat);");

	nRet = i18n_formattable_create_with_double(nDoubleValue, &g_hFormattable);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_formattable_create_with_double", BaseUtilsGetError(nRet),i18n_measure_format_destroy(hMeasureFormatHandle));
	CHECK_HANDLE_CLEANUP(g_hFormattable, "i18n_formattable_create_with_double",i18n_measure_format_destroy(hMeasureFormatHandle));

	nRet = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &hFieldPosHandle);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_field_position_create_for_field", BaseUtilsGetError(nRet), i18n_measure_format_destroy(hMeasureFormatHandle));
	CHECK_HANDLE_CLEANUP(hFieldPosHandle, "i18n_field_position_create_for_field", i18n_measure_format_destroy(hMeasureFormatHandle));

	nRet = i18n_measure_format_format_buff(hMeasureFormatHandle, g_hFormattable, hFieldPosHandle, BUFSIZE, g_pszStrAppend, &nOutputLen);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_measure_format_format_buff", BaseUtilsGetError(nRet), i18n_measure_format_destroy(hMeasureFormatHandle);i18n_field_position_destroy(hFieldPosHandle));
	pRet = NULL;
	pRet = i18n_ustring_copy_au_n(nOutputBuf, g_pszStrAppend, BUFSIZE);
	nLength = i18n_ustring_get_length(g_pszStrAppend);
	if ( pRet == NULL || nLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n Failed\\n", __LINE__, API_NAMESPACE);
		i18n_measure_format_destroy(hMeasureFormatHandle);
		i18n_field_position_destroy(hFieldPosHandle);
		return 1;
	}
	if(strcmp(nOutputBuf, pszOutputString) != 0)
	{
		FPRINTF("[Line : %d][%s] Value Mismatch\\n", __LINE__, API_NAMESPACE);
		i18n_measure_format_destroy(hMeasureFormatHandle);
		i18n_field_position_destroy(hFieldPosHandle);
		return 1;
	}
	if(nOutputLen != strnlen(pszOutputString, BUFSIZE))
	{
		FPRINTF("[Line : %d][%s] Value Mismatch\\n", __LINE__, API_NAMESPACE);
		i18n_measure_format_destroy(hMeasureFormatHandle);
		i18n_field_position_destroy(hFieldPosHandle);
		return 1;
	}
	i18n_measure_format_destroy(hMeasureFormatHandle);
	i18n_field_position_destroy(hFieldPosHandle);
	return 0;
}

//& type: auto
//& purpose: Formats measure objects to produce a string.
/**
* @testcase				ITc_i18n_measure_format_format_measures_p
* @since_tizen			4.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Formats measure objects to produce a string.
* @apitarget			i18n_measure_format_format_measures
* @apicovered			i18n_measure_format_format_measures
* @passcase				I18N_ERROR_NONE returned by i18n_measure_format_format_measures
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_format_format_measures or any pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_format_format_measures_p(void)
{
	START_TEST;

	const char *pszString1 = "The equatorial radius of the Earth is about ";
	const char *pszString2 = "The equatorial radius of the Earth is about "
                                "6,378 kilometers, 137 meters";
	i18n_field_position_h g_hFieldPos = NULL;
	i18n_uchar *pRet = NULL;
	int nLength;
	i18n_uchar g_pszStrAppend[BUFSIZE] = { 0 };
	int nOutputLen = -1;
	char nOutputBuf[BUFSIZE] = { 0 };

	if(CreateMeasureLength() != 0)
	{
		FPRINTF("[Line : %d][%s] CreateMeasureLength Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	pRet = i18n_ustring_copy_ua_n(g_pszStrAppend, pszString1, BUFSIZE);
	nLength = i18n_ustring_get_length(g_pszStrAppend);
	if ( pRet == NULL || nLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &g_hFieldPos);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_field_position_create_for_field", BaseUtilsGetError(nRet));
	CHECK_HANDLE(g_hFieldPos, "i18n_field_position_create_for_field");


	nRet = i18n_measure_format_format_measures(g_hMeasureFormat, g_hMeasureArr, g_nMeasures, g_hFieldPos, BUFSIZE, g_pszStrAppend, &nOutputLen);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_format_format_measures", BaseUtilsGetError(nRet));

	pRet = NULL;
	pRet = i18n_ustring_copy_au_n(nOutputBuf, g_pszStrAppend, BUFSIZE);
	nLength = i18n_ustring_get_length(g_pszStrAppend);
	if ( pRet == NULL || nLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(strncmp(nOutputBuf, pszString2, strlen(pszString2)) != 0)
	{
		FPRINTF("[Line : %d][%s] Value Mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(nOutputLen != strnlen(pszString2, BUFSIZE))
	{
		FPRINTF("[Line : %d][%s] Value Mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
} 

//& type: auto
//& purpose: Formats a single measure per unit.
/**
* @testcase				ITc_i18n_measure_format_format_measure_per_unit_p
* @since_tizen			4.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Formats a single measure per unit.
* @apitarget			i18n_measure_format_format_measure_per_unit
* @apicovered			i18n_measure_format_format_measure_per_unit
* @passcase				I18N_ERROR_NONE returned by i18n_measure_format_format_measure_per_unit
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_format_format_measure_per_unit or any pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_measure_format_format_measure_per_unit_p(void)
{
	START_TEST;
	const char *pszString1 = "The speed of light in vacuum is approx. ";
	const char *pszString2 = "The speed of light in vacuum is approx. "
                                "300,000 kilometers per second";
	int nOutputLen = -1;
	i18n_uchar g_pszStrAppend[BUFSIZE] = { 0 };
	char nOutputBuf[BUFSIZE] = { 0 };
	i18n_uchar *pRet = NULL;
	int nLength;

	int nRet = i18n_measure_unit_create_second(&g_hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_second", BaseUtilsGetError(nRet));
	CHECK_HANDLE(g_hMeasureUnit, "i18n_measure_unit_create_second");

	if(CreateMeasureUnit() != 0)
	{
		FPRINTF("[Line : %d][%s] CreateMeasureUnit Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	pRet = i18n_ustring_copy_ua_n(g_pszStrAppend, pszString1, BUFSIZE);
	nLength = i18n_ustring_get_length(g_pszStrAppend);
	if ( pRet == NULL || nLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &g_hFieldPos);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_field_position_create_for_field", BaseUtilsGetError(nRet));
	CHECK_HANDLE(g_hFieldPos, "i18n_field_position_create_for_field");

	nRet = i18n_measure_format_format_measure_per_unit(g_hMeasureFormat, g_hMeasureArr[0], g_hMeasureUnit, g_hFieldPos, BUFSIZE, g_pszStrAppend, &nOutputLen);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_format_format_measure_per_unit", BaseUtilsGetError(nRet));

	pRet = NULL;
	pRet = i18n_ustring_copy_au_n(nOutputBuf, g_pszStrAppend, BUFSIZE);
	nLength = i18n_ustring_get_length(g_pszStrAppend);
	if ( pRet == NULL || nLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua_n Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(strcmp(nOutputBuf, pszString2) != 0)
	{
		FPRINTF("[Line : %d][%s] Value Mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(nOutputLen != strnlen(pszString2, BUFSIZE))
	{
		FPRINTF("[Line : %d][%s] Value Mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Gets the display name of the i18n_measure_unit_h corresponding to the locale and format width.
/**
* @testcase				ITc_i18n_measure_format_get_unit_display_name
* @since_tizen			5.0
* @author				SRID(j.abhishek)
* @reviewer				SRID(shilpa.jindal)
* @type					auto
* @scenario				Gets the display name for measure unit.
* @apitarget			i18n_measure_format_get_unit_display_name
* @apicovered			i18n_measure_format_get_unit_display_name
* @passcase				I18N_ERROR_NONE returned by i18n_measure_format_get_unit_display_name
* @failcase				I18N_ERROR_NONE not returned by i18n_measure_format_get_unit_display_name or any pre-condition APIs fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_measure_format_get_unit_display_name(void)
{
	START_TEST;
	const char *pszOutputString = "meters";

	int nRet = i18n_measure_unit_create_meter(&g_hMeasureUnit);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_unit_create_meter", BaseUtilsGetError(nRet));
	CHECK_HANDLE(g_hMeasureUnit, "i18n_measure_unit_create_meter");


	i18n_uchar g_pszgetBuffer[BUFSIZE] = { 0 };
	char nOutputBuf[BUFSIZE] = { 0 };
	int nOutputLen = -1;

	nRet = i18n_measure_format_get_unit_display_name(g_hMeasureFormat, g_hMeasureUnit, BUFSIZE, g_pszgetBuffer, &nOutputLen);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_measure_format_get_unit_display_name", BaseUtilsGetError(nRet));

	if ( nOutputLen <= 0)
	{
		FPRINTF("[Line : %d][%s] i18n_measure_format_get_unit_display_name Failed to return Output buffer length\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char *pszRet = NULL;
	int nLength;

	pszRet = i18n_ustring_copy_au_n(nOutputBuf, g_pszgetBuffer, BUFSIZE);
	nLength = i18n_ustring_get_length(g_pszgetBuffer);

	if ( pszRet == NULL || nLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_au_n Failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(strcmp(nOutputBuf, pszOutputString) != 0)
	{
		FPRINTF("[Line : %d][%s] Value Mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(nOutputLen != strnlen(pszOutputString, BUFSIZE))
	{
		FPRINTF("[Line : %d][%s] Value Mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
/** @} */
/** @} */
