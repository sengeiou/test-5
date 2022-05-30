//
// Copyright (c) 2018 Samsung Electronics Co., Ltd.
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
//& set: BaseUtilsSimpleDateFormat

/**
* @function 		ITs_base_utils_simple_date_fmt_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_simple_date_fmt_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int ret = remove(ERR_LOG);
		if(ret == -1)
		{
			FPRINTF("[Line: %d][%s] unlinking file name error =%s \\n", __LINE__, API_NAMESPACE,ERR_LOG);
			return;
		}
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_base_utils_simple_date_fmt_startup\\n", __LINE__, API_NAMESPACE);
#endif

	g_bBaseUtilsInitFlag = false;

	int nRet = i18n_simple_date_fmt_create_from_pattern_locale(g_pszPattern, g_pszLocale, &g_hDateFmt);
	if ( nRet != I18N_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to create date format, error returned = %s\\n", __LINE__,API_NAMESPACE,  BaseUtilsGetError(nRet));
		return;
	}

	if ( !g_hDateFmt )
	{
		FPRINTF("[Line : %d][%s] date_fmt is NULL \\n", __LINE__, API_NAMESPACE);
		return;
	}

	g_bBaseUtilsInitFlag = true;
	return;
}

/**
* @function 		ITs_base_utils_simple_date_fmt_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_simple_date_fmt_cleanup(void)
{
	int nRet = I18N_ERROR_NONE;

	if ( g_bBaseUtilsInitFlag )
	{
		if (g_hDateFmt != NULL) {
			nRet = i18n_simple_date_fmt_destroy(g_hDateFmt);
			PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_destroy", BaseUtilsGetError(nRet));
			g_hDateFmt = NULL;
		}

		if (g_hCalendar != NULL) {
			nRet = i18n_ucalendar_destroy(g_hCalendar);
			PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucalendar_destroy", BaseUtilsGetError(nRet));
			g_hCalendar = NULL;
		}
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_base_utils_simple_date_fmt_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type: auto
//& purpose: To create and destroy a simple date format object using the default pattern for the default locale.
/**
* @testcase				ITc_i18n_simple_date_fmt_create_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Creates a simple date format object using the default pattern for the default locale and destroys it.
* @apicovered			i18n_simple_date_fmt_create, i18n_simple_date_fmt_destroy
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_create_destroy_p(void)
{
	START_TEST;

	i18n_simple_date_fmt_h hDateFmt = NULL;

	int nRet = i18n_simple_date_fmt_create(&hDateFmt);
	CHECK_HANDLE(hDateFmt, "i18n_simple_date_fmt_create");
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_create", BaseUtilsGetError(nRet), i18n_simple_date_fmt_destroy(hDateFmt));

	nRet = i18n_simple_date_fmt_destroy(hDateFmt);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To create a simple date format object using the given pattern and the default locale.
/**
* @testcase				ITc_i18n_simple_date_fmt_create_from_pattern_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Creates a simple date format object using the given pattern and the default locale.
* @apicovered			i18n_simple_date_fmt_create_from_pattern, i18n_simple_date_fmt_destroy
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_create_from_pattern_p(void)
{
	START_TEST;

	i18n_simple_date_fmt_h hDateFmt = NULL;

	int nRet = i18n_simple_date_fmt_create_from_pattern(g_pszPattern, &hDateFmt);
	CHECK_HANDLE(hDateFmt, "i18n_simple_date_fmt_create_from_pattern");
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_create_from_pattern", BaseUtilsGetError(nRet), i18n_simple_date_fmt_destroy(hDateFmt));

	nRet = i18n_simple_date_fmt_destroy(hDateFmt);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To create a simple date format object using the given pattern, numbering system override and the default locale.
/**
* @testcase				ITc_i18n_simple_date_fmt_create_from_pattern_override_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Creates a simple date format object using the given pattern, numbering system override,
*						and the default locale.
* @apicovered			i18n_simple_date_fmt_create_from_pattern_override, i18n_simple_date_fmt_destroy
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_create_from_pattern_override_p(void)
{
	START_TEST;

	i18n_simple_date_fmt_h hDateFmt = NULL;

	int nRet = i18n_simple_date_fmt_create_from_pattern_override(g_pszPattern, g_pszOverride, &hDateFmt);
	CHECK_HANDLE(hDateFmt, "i18n_simple_date_fmt_create_from_pattern_override");
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_create_from_pattern_override", BaseUtilsGetError(nRet), i18n_simple_date_fmt_destroy(hDateFmt));

	nRet = i18n_simple_date_fmt_destroy(hDateFmt);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To create a simple date format object using the given pattern and locale.
/**
* @testcase				ITc_i18n_simple_date_fmt_create_from_pattern_locale_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Creates a simple date format object using the given pattern and locale.
* @apicovered			i18n_simple_date_fmt_create_from_pattern_locale, i18n_simple_date_fmt_destroy
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_create_from_pattern_locale_p(void)
{
	START_TEST;

	i18n_simple_date_fmt_h hDateFmt = NULL;

	int nRet = i18n_simple_date_fmt_create_from_pattern_locale(g_pszPattern, g_pszLocale, &hDateFmt);
	CHECK_HANDLE(hDateFmt, "i18n_simple_date_fmt_create_from_pattern_locale");
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_create_from_pattern_locale", BaseUtilsGetError(nRet), i18n_simple_date_fmt_destroy(hDateFmt));

	nRet = i18n_simple_date_fmt_destroy(hDateFmt);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To create a simple date format object using the given pattern, numbering system override and locale.
/**
* @testcase				ITc_i18n_simple_date_fmt_create_from_pattern_override_locale_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Creates a simple date format object using the given pattern, numbering system
*						override and locale.
* @apicovered			i18n_simple_date_fmt_create_from_pattern_override_locale, i18n_simple_date_fmt_destroy
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_create_from_pattern_override_locale_p(void)
{
	START_TEST;

	i18n_simple_date_fmt_h hDateFmt = NULL;

	int nRet = i18n_simple_date_fmt_create_from_pattern_override_locale(g_pszPattern, g_pszOverride, g_pszLocale, &hDateFmt);
	CHECK_HANDLE(hDateFmt, "i18n_simple_date_fmt_create_from_pattern_override_locale");
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_create_from_pattern_override_locale", BaseUtilsGetError(nRet), i18n_simple_date_fmt_destroy(hDateFmt));

	nRet = i18n_simple_date_fmt_destroy(hDateFmt);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To create a clone of the given simple_date_fmt object.
/**
* @testcase				ITc_i18n_simple_date_fmt_clone_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Creates a clone of the given simple_date_fmt object.
* @apicovered			i18n_simple_date_fmt_clone, i18n_simple_date_fmt_destroy
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_clone_p(void)
{
	START_TEST;

	i18n_simple_date_fmt_h hClone = NULL;

	int nRet = i18n_simple_date_fmt_clone(g_hDateFmt, &hClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_clone", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hClone, "i18n_simple_date_fmt_clone");

	nRet = i18n_simple_date_fmt_destroy(hClone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To checks whether two simple date format objects are equal.
/**
* @testcase				ITc_i18n_simple_date_fmt_equals_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Checks whether two simple date format objects are equal.
* @apicovered			i18n_simple_date_fmt_equals, i18n_simple_date_fmt_clone, i18n_simple_date_fmt_destroy
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_equals_p(void)
{
	START_TEST;

	i18n_simple_date_fmt_h hToCompare = NULL;
	bool bIsEqual = false;

	int nRet = i18n_simple_date_fmt_clone(g_hDateFmt, &hToCompare);
	CHECK_HANDLE(hToCompare, "i18n_simple_date_fmt_clone");
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_clone", BaseUtilsGetError(nRet), i18n_simple_date_fmt_destroy(hToCompare));

	nRet = i18n_simple_date_fmt_equals(g_hDateFmt, hToCompare, &bIsEqual);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_equals", BaseUtilsGetError(nRet), i18n_simple_date_fmt_destroy(hToCompare));

	nRet = i18n_simple_date_fmt_destroy(hToCompare);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_destroy", BaseUtilsGetError(nRet));

	if( !bIsEqual )
	{
		FPRINTF("[Line : %d][%s] g_hDateFmt value is not same as hToCompare value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: To format a date or time using field position.
/**
* @testcase				ITc_i18n_simple_date_fmt_format_with_field_position_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Formats a date or time (which is the standard millis since 24:00 GMT, Jan 1, 1970)
*						using field position.
* @apicovered			i18n_field_position_create_for_field, i18n_ucalendar_create, i18n_ucalendar_set_date_time, i18n_simple_date_fmt_format_with_field_position
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_format_with_field_position_p(void)
{
	START_TEST;

	i18n_field_position_h hFieldPos = NULL;
	const char *pszResult = "Date: Thu, Feb 1, 2018";
	char *pszAppendTo = malloc(sizeof(char) * BUFFER);
	if(pszAppendTo == NULL)
	{
		FPRINTF("[Line : %d][%s] Memory allocation failed for pszAppendTo \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	snprintf(pszAppendTo, BUFFER, "Date: ");

	int nRet = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &hFieldPos);
	CHECK_HANDLE_CLEANUP(hFieldPos, "i18n_field_position_create_for_field", FREE_MEMORY(pszAppendTo));
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_field_position_create_for_field", BaseUtilsGetError(nRet), i18n_field_position_destroy(hFieldPos);FREE_MEMORY(pszAppendTo));

	nRet = i18n_ucalendar_create(NULL, -1, g_pszLocale, I18N_UCALENDAR_DEFAULT, &g_hCalendar);
	CHECK_HANDLE_CLEANUP(g_hCalendar, "i18n_ucalendar_create", FREE_MEMORY(pszAppendTo));
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucalendar_create", BaseUtilsGetError(nRet), i18n_field_position_destroy(hFieldPos);FREE_MEMORY(pszAppendTo));

	int nYear = 2018;
	int nMonth = 1;
	int nDate = 1;
	int nHour = 12;
	int nMin = 0;
	int nSec = 0;

	nRet = i18n_ucalendar_set_date_time(g_hCalendar, nYear, nMonth, nDate, nHour, nMin, nSec);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ucalendar_set_date_time", BaseUtilsGetError(nRet), i18n_field_position_destroy(hFieldPos);FREE_MEMORY(pszAppendTo));

	nRet = i18n_simple_date_fmt_format_with_field_position(g_hDateFmt, g_hCalendar, &pszAppendTo, hFieldPos);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_format_with_field_position", BaseUtilsGetError(nRet), i18n_field_position_destroy(hFieldPos);FREE_MEMORY(pszAppendTo));
	if ( strncmp(pszResult, pszAppendTo, strlen(pszResult)) != 0 )
	{
		FPRINTF("[Line : %d][%s] pszResult and append_to value doesn't match\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszAppendTo)
		return 1;
	}

	nRet = i18n_field_position_destroy(hFieldPos);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_field_position_destroy", BaseUtilsGetError(nRet));

	FREE_MEMORY(pszAppendTo);

	return 0;
}

//& type: auto
//& purpose: To parse a date/time string beginning at the given parse position.
/**
* @testcase				ITc_i18n_simple_date_fmt_parse_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Parses a date/time string beginning at the given parse position.
* @apicovered			i18n_parse_position_create, i18n_simple_date_fmt_parse
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_parse_p(void)
{
	START_TEST;

	i18n_parse_position_h hParsePos = NULL;
	const char *pszSource = "08/12/2016 4:5 PM, PDT";

	int nRet = i18n_parse_position_create(&hParsePos);
	CHECK_HANDLE(hParsePos, "i18n_parse_position_create");
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_parse_position_create", BaseUtilsGetError(nRet), i18n_parse_position_destroy(hParsePos));

	nRet = i18n_simple_date_fmt_parse(g_hDateFmt, pszSource, hParsePos, &g_hCalendar);
	CHECK_HANDLE(g_hCalendar, "i18n_simple_date_fmt_parse");
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_parse", BaseUtilsGetError(nRet), i18n_parse_position_destroy(hParsePos));

	nRet = i18n_parse_position_destroy(hParsePos);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_parse_position_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To set and get the start i18n_udate used to interpret two-digit year strings.
/**
* @testcase				ITc_i18n_simple_date_fmt_set_get_2digit_year_start_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Sets and gets the start i18n_udate used to interpret two-digit year strings.
* @apicovered			i18n_simple_date_fmt_set_2digit_year_start, i18n_simple_date_fmt_get_2digit_year_start
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_set_get_2digit_year_start_p(void)
{
	START_TEST;

	i18n_udate uSetDate = 150000.0;
	i18n_udate uGetDate = 0.0;

	int nRet = i18n_simple_date_fmt_set_2digit_year_start(g_hDateFmt, uSetDate);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_set_2digit_year_start", BaseUtilsGetError(nRet));

	nRet = i18n_simple_date_fmt_get_2digit_year_start(g_hDateFmt, &uGetDate);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_get_2digit_year_start", BaseUtilsGetError(nRet));
	if ( uGetDate !=  uSetDate )
	{
	     FPRINTF("[Line : %d][%s] uGetDate is not same as uSetDate\\n", __LINE__, API_NAMESPACE);
		 return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Returns a pattern string that describes given simple format date object.
/**
* @testcase				ITc_i18n_simple_date_fmt_to_pattern_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Returns a pattern string that describes given simple format date object.
* @apicovered			i18n_simple_date_fmt_to_pattern
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_to_pattern_p(void)
{
	START_TEST;
	char *pszResult = malloc(BUFFER);
	if(pszResult == NULL)
	{
		FPRINTF("[Line : %d][%s] Memory allocation failed for pszResult \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = i18n_simple_date_fmt_to_pattern(g_hDateFmt, &pszResult);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_to_pattern", BaseUtilsGetError(nRet), FREE_MEMORY(pszResult););
	if ( strncmp(pszResult, g_pszPattern, strlen(g_pszPattern)) != 0 )
	{
		FPRINTF("[Line : %d][%s] pszResult and g_pszPattern value doesn't match\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszResult);
		return 1;
	}

	FREE_MEMORY(pszResult);

	return 0;
}

//& type: auto
//& purpose: Returns a localized pattern string that describes given simple date format object.
/**
* @testcase				ITc_i18n_simple_date_fmt_to_localized_pattern_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Returns a localized pattern string that describes given simple date format object.
* @apicovered			i18n_simple_date_fmt_to_localized_pattern
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_to_localized_pattern_p(void)
{
	START_TEST;

	char *pszResult = malloc(BUFFER);
	if(pszResult == NULL)
	{
		FPRINTF("[Line : %d][%s] Memory allocation failed for pszResult \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = i18n_simple_date_fmt_to_localized_pattern(g_hDateFmt, &pszResult);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_to_localized_pattern", BaseUtilsGetError(nRet), FREE_MEMORY(pszResult););
	if ( strncmp(pszResult, g_pszPattern, strlen(g_pszPattern)) != 0 )
	{
		FPRINTF("[Line : %d][%s] result and pattern value doesn't match\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszResult);
		return 1;
	}

	FREE_MEMORY(pszResult);
	return 0;
}

//& type: auto
//& purpose: To apply the given unlocalized pattern string to this date format.
/**
* @testcase				ITc_i18n_simple_date_fmt_apply_pattern_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Applies the given unlocalized pattern string to this date format.
* @apicovered			i18n_simple_date_fmt_apply_pattern
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_apply_pattern_p(void)
{
	START_TEST;

	const char *pszNewPattern = "yyyy.MM.dd G 'at' HH:mm:ss vvvv";

	int nRet = i18n_simple_date_fmt_apply_pattern(g_hDateFmt, pszNewPattern);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_apply_pattern", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To apply the given localized pattern string to this date format.
/**
* @testcase				ITc_i18n_simple_date_fmt_apply_localized_pattern_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Applies the given localized pattern string to this date format.
* @apicovered			i18n_simple_date_fmt_apply_localized_pattern
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_apply_localized_pattern_p(void)
{
	START_TEST;

	const char *pszNewPattern = "yyyy.MM.dd G 'at' HH:mm:ss vvvv";

	int nRet = i18n_simple_date_fmt_apply_localized_pattern(g_hDateFmt, pszNewPattern);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_apply_localized_pattern", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To set the calendar to be used by this date format.
/**
* @testcase				ITc_i18n_simple_date_fmt_adopt_calendar_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Sets the calendar to be used by this date format.
* @apicovered			i18n_ucalendar_create, i18n_simple_date_fmt_adopt_calendar
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_adopt_calendar_p(void)
{
	START_TEST;

	const char *pszZoneId = NULL;
	i18n_ucalendar_h hCalendar = NULL;
	int nZoneIdLen = -1;

	int nRet = i18n_ucalendar_create(pszZoneId, nZoneIdLen, g_pszLocale, I18N_UCALENDAR_DEFAULT, &hCalendar);
	CHECK_HANDLE(hCalendar, "i18n_ucalendar_create");
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ucalendar_create", BaseUtilsGetError(nRet));

	nRet = i18n_simple_date_fmt_adopt_calendar(g_hDateFmt, hCalendar);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_adopt_calendar", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To set a particular value in the formatter.
/**
* @testcase				ITc_i18n_simple_date_fmt_set_context_p
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Sets a particular #i18n_udisplay_context_e value in the formatter, such as
*						#I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_STANDALONE.
* @apicovered			i18n_simple_date_fmt_set_context
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_simple_date_fmt_set_context_p(void)
{
	START_TEST;

	int nRet = i18n_simple_date_fmt_set_context(g_hDateFmt, I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_MIDDLE_OF_SENTENCE);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_simple_date_fmt_set_context", BaseUtilsGetError(nRet));

	return 0;
}

/** @} */
/** @} */
