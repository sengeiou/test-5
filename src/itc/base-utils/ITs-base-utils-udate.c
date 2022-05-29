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

static i18n_udate_format_h g_hUdateFormat = NULL;

//& set: BaseUtilsUdate
void ITs_base_utils_udate_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
	
	const char *pszDefaultLocale = I18N_ULOCALE_US;
	const i18n_uchar *pUcharPattern = NULL;
    int32_t nPatternLength = 0;
	
	
	i18n_uchar *pUcharDefaultTzid = (i18n_uchar*)calloc(strlen(I18N_DEFAULT_T_ZONE) + 1, sizeof(i18n_uchar));
    if (pUcharDefaultTzid == NULL) 
	{
		FPRINTF("\\n[Line : %d][%s] pUcharDefaultTzid, memory not allocated properly.\n", __LINE__, API_NAMESPACE);
        g_bBaseUtilsInitFlag = false;
		return;
    }
    
	i18n_uchar *pRet = i18n_ustring_copy_ua(pUcharDefaultTzid, (char *)I18N_DEFAULT_T_ZONE);
	int nLengthDefaultTimeZone = i18n_ustring_get_length(pUcharDefaultTzid);
	
	if(pRet == NULL || nLengthDefaultTimeZone < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in start-up.\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pUcharDefaultTzid);
		g_bBaseUtilsInitFlag = false;
		return;
	}
	
	int nRetVal = i18n_udate_create(I18N_UDATE_DEFAULT, I18N_UDATE_DEFAULT, pszDefaultLocale, pUcharDefaultTzid, nLengthDefaultTimeZone, pUcharPattern, nPatternLength, &g_hUdateFormat);
	if (nRetVal != I18N_ERROR_NONE || g_hUdateFormat == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_udate_create failed in startup, error returned = %s or handle is NULL \n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
		g_bBaseUtilsInitFlag = false;
		FREE_MEMORY(pUcharDefaultTzid);
		return;
	}
	
	g_bBaseUtilsInitFlag = true;
	FREE_MEMORY(pUcharDefaultTzid);

	return;
}

void ITs_base_utils_udate_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRetVal = i18n_udate_destroy(g_hUdateFormat);
	if (nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_udate_destroy failed in cleanup, error returned = %s \n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
	}
	
	g_hUdateFormat = NULL;
	g_bBaseUtilsInitFlag = false;	
	return;
}

/** @addtogroup itc-base-utils-testcases
*  @brief 		Integration testcases for module base-utils ucalendar
*  @ingroup 	itc-base-utils
*  @{
*/

//& type: auto
//& purpose: Creates and Destroy i18n_udate_format.
/**
* @testcase				ITc_i18n_udate_create_destroy_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates i18n_udate_format.\n
* 						Destroy i18n_udate_format. 	
* @apitarget			i18n_udate_create, i18n_udate_destroy
* @apicovered			i18n_udate_create, i18n_udate_destroy, i18n_ustring_copy_ua
* @passcase				When i18n_udate_create, i18n_udate_destroy are successful
* @failcase				If target i18n_udate_create or i18n_udate_destroy fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_create_destroy_p(void)
{
	START_TEST;

	i18n_udate_format_style_e eTimeFormatStyle[] = {I18N_UDATE_FULL, 
		I18N_UDATE_LONG, 
		I18N_UDATE_MEDIUM,
		I18N_UDATE_SHORT,
		I18N_UDATE_NONE};
	i18n_udate_format_style_e eDateFormatStyle[] = {I18N_UDATE_FULL, 
		I18N_UDATE_LONG, 
		I18N_UDATE_MEDIUM,
		I18N_UDATE_SHORT,
		I18N_UDATE_RELATIVE,
		I18N_UDATE_LONG_RELATIVE,
		I18N_UDATE_MEDIUM_RELATIVE,
		I18N_UDATE_SHORT_RELATIVE,
		I18N_UDATE_NONE};
	int nDateEnumSize = sizeof(eDateFormatStyle) / sizeof(eDateFormatStyle[0]);
	int nEnumDateCounter = 0;
	int nTimeEnumSize = sizeof(eTimeFormatStyle) / sizeof(eTimeFormatStyle[0]);
	int nEnumTimeCounter = 0;
	i18n_udatepg_h udatepgHandle = NULL;

	int nRetVal = i18n_udatepg_create(g_pszDefaultLocale, &udatepgHandle);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_create", BaseUtilsGetError(nRetVal));

	int nCustomFormatLength = 0;
	i18n_uchar ucharCustomFormat[I18N_DATEPG_BEST_PATTERN_CAPACITY];
	i18n_uchar *pRet = i18n_ustring_copy_ua(ucharCustomFormat, (char *)I18N_DATE_TIME_CUSTOM_FORMAT);
	nCustomFormatLength = i18n_ustring_get_length(ucharCustomFormat);
	if ( pRet == NULL || nCustomFormatLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua failed in precondition\\n", __LINE__, API_NAMESPACE);
		i18n_udatepg_destroy(udatepgHandle);
		return 1;
	} 
	i18n_uchar bestPattern[I18N_DATEPG_BEST_PATTERN_CAPACITY] = { 0, };   
	int nBestPatternCapacity = (int)(sizeof(bestPattern)/sizeof(bestPattern[0]));
	int nBestPatternLength = 0;
	nRetVal = i18n_udatepg_get_best_pattern(udatepgHandle, ucharCustomFormat, nCustomFormatLength, bestPattern, nBestPatternCapacity, &nBestPatternLength);       
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_get_best_pattern", BaseUtilsGetError(nRetVal), i18n_udatepg_destroy(udatepgHandle));

	for ( nEnumTimeCounter = 0; nEnumTimeCounter < nTimeEnumSize;  nEnumTimeCounter++ )
	{
		for ( nEnumDateCounter = 0; nEnumDateCounter < nDateEnumSize;  nEnumDateCounter++ )
		{
			i18n_udate_format_h uDate = NULL;
			FPRINTF("[Line : %d][%s] Executing i18n_udate_create with Time Format Style = %s, Date Format Style = %s and default Locale=%s\\n", __LINE__, API_NAMESPACE, UdateGetFormatStyle(eTimeFormatStyle[nEnumTimeCounter]), UdateGetFormatStyle(eDateFormatStyle[nEnumDateCounter]), g_pszDefaultLocale);

			nRetVal = i18n_udate_create(eTimeFormatStyle[nEnumTimeCounter], eDateFormatStyle[nEnumDateCounter], g_pszDefaultLocale, g_pDefaultTzid, g_nLengthDefaultTimeZone, bestPattern, nBestPatternLength, &uDate);
			PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_udate_create", BaseUtilsGetError(nRetVal), i18n_udatepg_destroy(udatepgHandle));


			nRetVal = i18n_udate_destroy(uDate);
			PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_udate_destroy", BaseUtilsGetError(nRetVal), i18n_udatepg_destroy(udatepgHandle));
		}
	}
	i18n_udatepg_destroy(udatepgHandle);
	return 0;
}

//& type: auto
//& purpose: Formats a date using an i18n_udate_format.
/**
* @testcase				ITc_i18n_udate_format_date_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Formats a date using an i18n_udate_format.	
* @apitarget			i18n_udate_format_date
* @apicovered			i18n_udate_format_date, i18n_ustring_copy_ua
* @passcase				When i18n_udate_format_date is successful
* @failcase				If target i18n_udate_format_date fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_format_date_p(void)
{
	START_TEST;

	i18n_udatepg_h udatepgHandle = NULL;
	i18n_uchar ucharCustomFormat[I18N_DATEPG_BEST_PATTERN_CAPACITY];

	i18n_uchar *pRet = i18n_ustring_copy_ua(ucharCustomFormat, (char *)I18N_DATE_TIME_CUSTOM_FORMAT);
	int nCustomFormatLength = i18n_ustring_get_length(ucharCustomFormat);
	if ( pRet == NULL || nCustomFormatLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua failed in precondition\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	i18n_uchar bestPattern[I18N_DATEPG_BEST_PATTERN_CAPACITY] = { 0, };   
	int nBestPatternCapacity = (int)(sizeof(bestPattern)/sizeof(bestPattern[0]));
	int nBestPatternLength = 0;

	int nRetVal = i18n_udatepg_create(g_pszDefaultLocale, &udatepgHandle);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_create", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_udatepg_get_best_pattern(udatepgHandle, ucharCustomFormat, nCustomFormatLength, bestPattern, nBestPatternCapacity, &nBestPatternLength);       
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_get_best_pattern", BaseUtilsGetError(nRetVal), i18n_udatepg_destroy(udatepgHandle));


	i18n_udate_format_h uDateFormat = NULL;
	nRetVal = i18n_udate_create(I18N_UDATE_DEFAULT, I18N_UDATE_DEFAULT, g_pszDefaultLocale, g_pDefaultTzid, g_nLengthDefaultTimeZone, bestPattern, nBestPatternLength, &uDateFormat);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_udate_create", BaseUtilsGetError(nRetVal), i18n_udatepg_destroy(udatepgHandle));

	i18n_udate uDate;
	nRetVal = i18n_ucalendar_get_now(&uDate);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_get_now", BaseUtilsGetError(nRetVal), i18n_udate_destroy(uDateFormat);i18n_udatepg_destroy(udatepgHandle));

	i18n_uchar resultFormattedDate[I18N_FORMATED_DATE_CAPACITY] = {0,};
	int nFormattedDateBufferSizeNeeded = 0;
	nRetVal = i18n_udate_format_date(uDateFormat, uDate, resultFormattedDate, I18N_FORMATED_DATE_CAPACITY, NULL, &nFormattedDateBufferSizeNeeded);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_udate_format_date", BaseUtilsGetError(nRetVal), i18n_udate_destroy(uDateFormat);i18n_udatepg_destroy(udatepgHandle));
	if ( nFormattedDateBufferSizeNeeded > I18N_FORMATED_DATE_CAPACITY )
	{
		FPRINTF("[Line : %d][%s] The Returned Formatted Date Buffer Size(%d) is greater than formatted date capacity(%d)\\n", __LINE__, API_NAMESPACE, nFormattedDateBufferSizeNeeded, I18N_FORMATED_DATE_CAPACITY);
	}
	char formattedDateChar[I18N_FORMATED_DATE_CAPACITY] = {0,};
	i18n_ustring_copy_au_n(formattedDateChar, resultFormattedDate, I18N_FORMATED_DATE_CAPACITY);
	if ( strlen(formattedDateChar) <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_udate_format_date failed  as The result Formatted Date Char Length is either less than or Equal to Zero.", __LINE__, API_NAMESPACE);
		i18n_udate_destroy(uDateFormat);
		i18n_udatepg_destroy(udatepgHandle);
		return 1;
	}
	i18n_udate_destroy(uDateFormat);
	i18n_udatepg_destroy(udatepgHandle);
	return 0;
}


//& type: auto
//& purpose: Maps from an date format to the corresponding date fields
/**
* @testcase				ITc_i18n_udate_to_calendar_date_field_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Maps from an date format to the corresponding date fields
* @scenario				- Maps from an date format to the corresponding date fields
* @apitarget			i18n_udate_to_calendar_date_field	
* @apicovered			i18n_udate_to_calendar_date_field
* @passcase				I18N_ERROR_NONE returned by i18n_udate_to_calendar_date_field
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_to_calendar_date_field
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_to_calendar_date_field_p(void)
{	
	START_TEST_PRINT;
	
	i18n_ucalendar_date_fields_e eDateField = -1;
	i18n_udate_format_field_e eDateFormat[] = {	I18N_UDATE_FORMAT_ERA_FIELD,                         
												I18N_UDATE_FORMAT_YEAR_FIELD,                        
												I18N_UDATE_FORMAT_MONTH_FIELD,                       
												I18N_UDATE_FORMAT_DATE_FIELD,                        
												I18N_UDATE_FORMAT_HOUR_OF_DAY1_FIELD,                
												I18N_UDATE_FORMAT_HOUR_OF_DAY0_FIELD,                
												I18N_UDATE_FORMAT_MINUTE_FIELD,                      
												I18N_UDATE_FORMAT_SECOND_FIELD,                      
												I18N_UDATE_FORMAT_FRACTIONAL_SECOND_FIELD,           
												I18N_UDATE_FORMAT_DAY_OF_WEEK_FIELD,                 
												I18N_UDATE_FORMAT_DAY_OF_YEAR_FIELD,                 
												I18N_UDATE_FORMAT_DAY_OF_WEEK_IN_MONTH_FIELD,        
												I18N_UDATE_FORMAT_WEEK_OF_YEAR_FIELD,                
												I18N_UDATE_FORMAT_WEEK_OF_MONTH_FIELD,               
												I18N_UDATE_FORMAT_AM_PM_FIELD,                       
												I18N_UDATE_FORMAT_HOUR1_FIELD,                       
												I18N_UDATE_FORMAT_HOUR0_FIELD,                       
												I18N_UDATE_FORMAT_TIMEZONE_FIELD,                    
												I18N_UDATE_FORMAT_YEAR_WOY_FIELD,                    
												I18N_UDATE_FORMAT_DOW_LOCAL_FIELD,                   
												I18N_UDATE_FORMAT_EXTENDED_YEAR_FIELD,               
												I18N_UDATE_FORMAT_JULIAN_DAY_FIELD,                  
												I18N_UDATE_FORMAT_MILLISECONDS_IN_DAY_FIELD,         
												I18N_UDATE_FORMAT_TIMEZONE_RFC_FIELD,                
												I18N_UDATE_FORMAT_TIMEZONE_GENERIC_FIELD,            
												I18N_UDATE_FORMAT_STANDALONE_DAY_FIELD,              
												I18N_UDATE_FORMAT_STANDALONE_MONTH_FIELD,            
												I18N_UDATE_FORMAT_QUARTER_FIELD,                     
												I18N_UDATE_FORMAT_STANDALONE_QUARTER_FIELD,          
												I18N_UDATE_FORMAT_TIMEZONE_SPECIAL_FIELD,            
												I18N_UDATE_FORMAT_YEAR_NAME_FIELD };
												
	int nEnumSize = sizeof(eDateFormat) / sizeof(eDateFormat[0]);
	int nEnumCounter = 0, nRetVal = -1;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for Date Format field value (%s) \\n", __LINE__, API_NAMESPACE, UdateGetDateFormatFieldValue(eDateFormat[nEnumCounter]));
		eDateField = -1;
		nRetVal = i18n_udate_to_calendar_date_field(eDateFormat[nEnumCounter], &eDateField);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_to_calendar_date_field", BaseUtilsGetError(nRetVal));
		if(eDateField < I18N_UCALENDAR_ERA || eDateField > I18N_UCALENDAR_FIELD_COUNT)
		{
			FPRINTF("\\n[Line : %d][%s] i18n_udate_to_calendar_date_field failed. Returned invalid output parameter (%d) = %s\\n", __LINE__, API_NAMESPACE, eDateField, UcalenderDateFieldValue(eDateField));
			return 1;
		}
	}

	return 0;
}

//& type: auto
//& purpose: Creates a copy of a date format handle
/**
* @testcase				ITc_i18n_udate_clone_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Creates a copy of a date format handle
* @apitarget			i18n_udate_clone	
* @apicovered			i18n_udate_clone
* @passcase				I18N_ERROR_NONE returned by i18n_udate_clone
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_clone or pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_clone_p(void)
{	
	START_TEST;
	i18n_udate_format_h hUdateClone = NULL;
												
	int nRetVal = i18n_udate_clone(g_hUdateFormat, &hUdateClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_clone", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hUdateClone, "i18n_udate_clone");

	return 0;
}

//& type: auto
//& purpose: Parses a string into an date/time udate format
/**
* @testcase				ITc_i18n_udate_parse_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Parses a string into an date/time udate format
* @apitarget			i18n_udate_parse	
* @apicovered			i18n_udate_parse, i18n_ustring_copy_ua
* @passcase				I18N_ERROR_NONE returned by i18n_udate_parse
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_parse or pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_parse_p(void)
{	
	START_TEST;
	i18n_uchar uCharDate[I18N_UNUMBER_SYMBOL_CAPACITY] = {0};
    char *pszDateText = "May 1, 2015, 6:00:00 AM";
	int32_t nTextLength = -1;
    int32_t nParsePos = 0;
    i18n_udate hParsedDate = -1;
	
	i18n_uchar *pRet = i18n_ustring_copy_ua(uCharDate, pszDateText);
	int nLengthDefaultTimeZone = i18n_ustring_get_length(uCharDate);
	
	if(pRet == NULL || nLengthDefaultTimeZone < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nRetVal = i18n_udate_parse(g_hUdateFormat, uCharDate, nTextLength, &nParsePos, &hParsedDate);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_parse", BaseUtilsGetError(nRetVal));
	CHECK_RETURN_VAL(hParsedDate, "i18n_udate_parse for parse date");

	return 0;
}

//& type: auto
//& purpose: The date will be parsed using the conventions
/**
* @testcase				ITc_i18n_udate_parse_calendar_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			The date will be parsed using the conventions
* @scenario				- The date will be parsed using the conventions
* @apitarget			i18n_udate_parse_calendar	
* @apicovered			i18n_udate_parse_calendar, i18n_ustring_copy_ua
* @passcase				I18N_ERROR_NONE returned by i18n_udate_parse_calendar
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_parse_calendar or pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_parse_calendar_p(void)
{	
	START_TEST;
	i18n_uchar uCharDate[I18N_UNUMBER_SYMBOL_CAPACITY] = {0};
    char *pszDateText = "May 1, 2015, 6:00:00 AM";
	int32_t nTextLength = -1;
    int32_t nParsePos = 0;
    i18n_ucalendar_h hUcalender = NULL;
	const char *pszDefaultLocale = I18N_ULOCALE_US;
	
	i18n_ustring_copy_ua(uCharDate, pszDateText);

	i18n_uchar *pszUcharTzone = (i18n_uchar*)calloc(strlen(I18N_DEFAULT_T_ZONE) + 1, sizeof(i18n_uchar));
	CHECK_HANDLE(pszUcharTzone, "Memory not allocated");
	
	i18n_uchar *pRet = i18n_ustring_copy_ua(pszUcharTzone, I18N_DEFAULT_T_ZONE);
	int32_t nLength = i18n_ustring_get_length(pszUcharTzone);
    
	if ( pRet == NULL || nLength <= 0 )
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in startup\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszUcharTzone);
		return 1;
	}
	
	int nRetVal = i18n_ucalendar_create(pszUcharTzone, nLength, pszDefaultLocale, I18N_UCALENDAR_TRADITIONAL, &hUcalender);
	CHECK_HANDLE_CLEANUP(hUcalender, "i18n_ucalendar_create",FREE_MEMORY(pszUcharTzone));
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_create", BaseUtilsGetError(nRetVal),FREE_MEMORY(pszUcharTzone));
	
	nRetVal = i18n_udate_parse_calendar(g_hUdateFormat, hUcalender, uCharDate, nTextLength, &nParsePos);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_udate_parse_calendar", BaseUtilsGetError(nRetVal),FREE_MEMORY(pszUcharTzone));

	FREE_MEMORY(pszUcharTzone);
	i18n_ucalendar_destroy(hUcalender);
	return 0;
}

//& type: auto
//& purpose: Determines if a format handle will perform lenient parsing and set/unset the lenient parsing
/**
* @testcase				ITc_i18n_udate_is_set_lenient_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Determines if a format handle will perform lenient parsing and set/unset the lenient parsing
* @apitarget			i18n_udate_is_lenient, i18n_udate_set_lenient	
* @apicovered			i18n_udate_is_lenient, i18n_udate_set_lenient
* @passcase				I18N_ERROR_NONE returned by i18n_udate_is_lenient and i18n_udate_set_lenient
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_is_lenient or i18n_udate_set_lenient or pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_is_set_lenient_p(void)
{	
	START_TEST;
	i18n_ubool bIsLenient = false;
	
	int nRetVal = i18n_udate_set_lenient(g_hUdateFormat, true);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_set_lenient", BaseUtilsGetError(nRetVal));
	
	bIsLenient = i18n_udate_is_lenient(g_hUdateFormat);
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_is_lenient", BaseUtilsGetError(nRetVal));
	if(bIsLenient != true)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_udate_is_lenient failed, return value is = %d \n", __LINE__, API_NAMESPACE, bIsLenient);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: Get and set the calendar handle associated with an udate format
/**
* @testcase				ITc_i18n_udate_get_set_calendar_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Get and set the calendar handle associated with an udate format
* @apitarget			i18n_udate_get_calendar, i18n_udate_set_calendar	
* @apicovered			i18n_udate_get_calendar, i18n_udate_set_calendar
* @passcase				I18N_ERROR_NONE returned by i18n_udate_get_calendar and i18n_udate_set_calendar
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_get_calendar or i18n_udate_set_calendar or pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_get_set_calendar_p(void)
{	
	START_TEST;
	i18n_ucalendar_h hCalendar = NULL;
	
	int nRetVal = i18n_udate_get_calendar(g_hUdateFormat, &hCalendar);
	CHECK_HANDLE(hCalendar, "i18n_udate_get_calendar");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_get_calendar", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_udate_set_calendar(g_hUdateFormat, hCalendar);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_set_calendar", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Get and set the unumber formath associated with an udate format
/**
* @testcase				ITc_i18n_udate_get_set_number_format_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Get and set the unumber formath associated with an udate format
* @apitarget			i18n_udate_get_number_format, i18n_udate_set_number_format	
* @apicovered			i18n_udate_get_number_format, i18n_udate_set_number_format
* @passcase				I18N_ERROR_NONE returned by i18n_udate_get_number_format and i18n_udate_set_number_format
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_get_number_format or i18n_udate_set_number_format or pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_get_set_number_format_p(void)
{	
	START_TEST;
	i18n_unumber_format_h hNumberFormat = NULL;
	
	int nRetVal = i18n_udate_get_number_format(g_hUdateFormat, &hNumberFormat);
	CHECK_HANDLE(hNumberFormat, "i18n_udate_get_number_format");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_get_number_format", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_udate_set_number_format(g_hUdateFormat, hNumberFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_set_number_format", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Get and set the year relative to which all 2-digit years are interpreted
/**
* @testcase				ITc_i18n_udate_get_set_2digit_year_start_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Get and set the year relative to which all 2-digit years are interpreted
* @apitarget			i18n_udate_get_2digit_year_start, i18n_udate_set_2digit_year_start	
* @apicovered			i18n_udate_get_2digit_year_start, i18n_udate_set_2digit_year_start
* @passcase				I18N_ERROR_NONE returned by i18n_udate_get_2digit_year_start and i18n_udate_set_2digit_year_start
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_get_2digit_year_start or i18n_udate_set_2digit_year_start or pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_get_set_2digit_year_start_p(void)
{	
	START_TEST;
	i18n_udate nUdate = 0;
	
	int nRetVal = i18n_udate_get_2digit_year_start(g_hUdateFormat, &nUdate);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_get_2digit_year_start", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_udate_set_2digit_year_start(g_hUdateFormat, nUdate);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_set_2digit_year_start", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Set and get the symbols associated with an udate format
/**
* @testcase				ITc_i18n_udate_set_get_symbols_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Set and get the symbols associated with an udate format
* @apitarget			i18n_udate_set_symbols, i18n_udate_get_symbols	
* @apicovered			i18n_udate_set_symbols, i18n_udate_get_symbols, i18n_ustring_copy_ua
* @passcase				I18N_ERROR_NONE returned by i18n_udate_set_symbols and i18n_udate_get_symbols
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_set_symbols or i18n_udate_get_symbols or pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_set_get_symbols_p(void)
{	
	START_TEST;
	int32_t nSymbolIndex = 0;
    const char *pszSymbol = "MAY";
    i18n_uchar uCharSymbolSet[I18N_UNUMBER_SYMBOL_CAPACITY] = {0};
    i18n_uchar uCharSymbolGet[I18N_UNUMBER_SYMBOL_CAPACITY] = {0};
    int nLength = -1;
	
	i18n_udate_format_symbol_type_e eSymbolType[] = {	I18N_UDATE_FORMAT_SYMBOL_TYPE_ERAS,                        
														I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS,                      
														I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORT_MONTHS,                
														I18N_UDATE_FORMAT_SYMBOL_TYPE_WEEKDAYS,                    
														I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORT_WEEKDAYS,              
														I18N_UDATE_FORMAT_SYMBOL_TYPE_AM_PMS,                      
														I18N_UDATE_FORMAT_SYMBOL_TYPE_LOCALIZED_CHARS,             
														I18N_UDATE_FORMAT_SYMBOL_TYPE_ERA_NAMES,                   
														I18N_UDATE_FORMAT_SYMBOL_TYPE_NARROW_MONTHS,               
														I18N_UDATE_FORMAT_SYMBOL_TYPE_NARROW_WEEKDAYS,             
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_MONTHS,           
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORT_MONTHS,     
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_NARROW_MONTHS,    
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_WEEKDAYS,         
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORT_WEEKDAYS,   
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_NARROW_WEEKDAYS,  
														I18N_UDATE_FORMAT_SYMBOL_TYPE_QUARTERS,                    
														I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORT_QUARTERS,              
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_QUARTERS,         
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORT_QUARTERS,   
														I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORTER_WEEKDAYS,            
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORTER_WEEKDAYS
													};
												
	int nEnumSize = sizeof(eSymbolType) / sizeof(eSymbolType[0]);
	int nEnumCounter = 0, nRetVal = -1;
	
	i18n_ustring_copy_ua(uCharSymbolSet, pszSymbol);
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for Format Symbol type (%s) \\n", __LINE__, API_NAMESPACE, UdateGetFormatSymbolType(eSymbolType[nEnumCounter]));
		
		nLength = i18n_udate_set_symbols(g_hUdateFormat, eSymbolType[nEnumCounter], nSymbolIndex, uCharSymbolSet, -1);
		CHECK_RETURN_VAL(nLength, "i18n_udate_set_symbols");
		nRetVal = get_last_result();
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_set_symbols", BaseUtilsGetError(nRetVal));
	
		nLength = -1;
		nLength = i18n_udate_get_symbols(g_hUdateFormat, eSymbolType[nEnumCounter], nSymbolIndex, uCharSymbolGet, I18N_UNUMBER_SYMBOL_CAPACITY);
		CHECK_RETURN_VAL(nLength, "i18n_udate_get_symbols");
		nRetVal = get_last_result();
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_get_symbols", BaseUtilsGetError(nRetVal));
		if(i18n_ustring_compare(uCharSymbolGet, uCharSymbolSet) != 0)
		{
			FPRINTF("\\n[Line : %d][%s] i18n_udate_get_symbols failed, get value is not same as set value \n", __LINE__, API_NAMESPACE);
			return 1;
		}
		nLength = -1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets a locale for which date/time formatting patterns are available
/**
* @testcase				ITc_i18n_udate_get_available_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Gets a locale for which date/time formatting patterns are available
* @apitarget			i18n_udate_get_available	
* @apicovered			i18n_udate_get_available
* @passcase				I18N_ERROR_NONE returned by i18n_udate_get_available
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_get_available
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_get_available_p(void)
{	
	START_TEST_PRINT;
	const char *pszLocale = NULL;
	int32_t nLocaleIndex = 1;
   
	pszLocale = i18n_udate_get_available(nLocaleIndex);
	CHECK_HANDLE(pszLocale, "i18n_udate_get_available");
	
	int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_get_available", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Determines how many locales have date/time formatting patterns available
/**
* @testcase				ITc_i18n_udate_count_available_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Determines how many locales have date/time formatting patterns available
* @apitarget			i18n_udate_count_available	
* @apicovered			i18n_udate_count_available
* @passcase				I18N_ERROR_NONE returned by i18n_udate_count_available
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_count_available
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_count_available_p(void)
{	
	START_TEST_PRINT;
	int32_t nLocaleCount = -1;
   
	nLocaleCount = i18n_udate_count_available();
	CHECK_RETURN_VAL(nLocaleCount, "i18n_udate_count_available");
	
	int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_count_available", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Sets the pattern in an udate format
/**
* @testcase				ITc_i18n_udate_apply_pattern_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Sets the pattern used by an udate format
* @apitarget			i18n_udate_apply_pattern
* @apicovered			i18n_udate_apply_pattern, i18n_ustring_copy_ua
* @passcase				I18N_ERROR_NONE returned by i18n_udate_apply_pattern
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_apply_pattern or any pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_apply_pattern_p(void)
{	
	START_TEST;
	i18n_ubool bLocalized = true;
	i18n_uchar uCharPatternSet[I18N_UNUMBER_SYMBOL_CAPACITY] = {0};
	const char *pszPattern = "MM, DD, YYYY";

	i18n_uchar *pRet = i18n_ustring_copy_ua(uCharPatternSet, pszPattern);
	int nLengthDefaultTimeZone = i18n_ustring_get_length(uCharPatternSet);
	
	if(pRet == NULL || nLengthDefaultTimeZone < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed \n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRetVal = i18n_udate_apply_pattern(g_hUdateFormat, bLocalized, uCharPatternSet, I18N_UNUMBER_SYMBOL_CAPACITY);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_apply_pattern", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Extracts the pattern from an udate format
/**
* @testcase				ITc_i18n_udate_apply_to_pattern_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Extracts the pattern from an udate format
* @apitarget			i18n_udate_to_pattern	
* @apicovered			i18n_udate_to_pattern, i18n_ustring_copy_ua
* @passcase				I18N_ERROR_NONE returned by i18n_udate_to_pattern
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_to_pattern or any pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_apply_to_pattern_p(void)
{	
	START_TEST;
	i18n_ubool bLocalized = true;
    i18n_uchar uCharPatternGet[I18N_UNUMBER_SYMBOL_CAPACITY] = {0};
	int32_t nPatternSize = -1;
	
	nPatternSize = i18n_udate_to_pattern(g_hUdateFormat, bLocalized, uCharPatternGet, I18N_UNUMBER_SYMBOL_CAPACITY);
	CHECK_RETURN_VAL(nPatternSize, "i18n_udate_to_pattern");
	CHECK_HANDLE(uCharPatternGet, "i18n_udate_to_pattern");	
	int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_to_pattern", BaseUtilsGetError(nRetVal));
		
	return 0;
}

//& type: auto
//& purpose: Counts the number of particular symbols for an udate format
/**
* @testcase				ITc_i18n_udate_count_symbols_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Counts the number of particular symbols for an udate format
* @apitarget			i18n_udate_count_symbols	
* @apicovered			i18n_udate_count_symbols
* @passcase				I18N_ERROR_NONE returned by i18n_udate_count_symbols 
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_count_symbols or pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_count_symbols_p(void)
{	
	START_TEST;
	
	i18n_udate_format_symbol_type_e eSymbolType[] = {	I18N_UDATE_FORMAT_SYMBOL_TYPE_ERAS,                        
														I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS,                      
														I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORT_MONTHS,                
														I18N_UDATE_FORMAT_SYMBOL_TYPE_WEEKDAYS,                    
														I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORT_WEEKDAYS,              
														I18N_UDATE_FORMAT_SYMBOL_TYPE_AM_PMS,                      
														I18N_UDATE_FORMAT_SYMBOL_TYPE_LOCALIZED_CHARS,             
														I18N_UDATE_FORMAT_SYMBOL_TYPE_ERA_NAMES,                   
														I18N_UDATE_FORMAT_SYMBOL_TYPE_NARROW_MONTHS,               
														I18N_UDATE_FORMAT_SYMBOL_TYPE_NARROW_WEEKDAYS,             
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_MONTHS,           
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORT_MONTHS,     
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_NARROW_MONTHS,    
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_WEEKDAYS,         
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORT_WEEKDAYS,   
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_NARROW_WEEKDAYS,  
														I18N_UDATE_FORMAT_SYMBOL_TYPE_QUARTERS,                    
														I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORT_QUARTERS,              
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_QUARTERS,         
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORT_QUARTERS,   
														I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORTER_WEEKDAYS,            
														I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORTER_WEEKDAYS};
												
	int nEnumSize = sizeof(eSymbolType) / sizeof(eSymbolType[0]);
	int nEnumCounter = 0, nRetVal = -1;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for Format Symbol type (%s) \\n", __LINE__, API_NAMESPACE, UdateGetFormatSymbolType(eSymbolType[nEnumCounter]));
		int nSymbolCount = i18n_udate_count_symbols(g_hUdateFormat, eSymbolType[nEnumCounter]);
		CHECK_RETURN_VAL(nSymbolCount, "i18n_udate_count_symbols");
		
		nRetVal = get_last_result();
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_count_symbols", BaseUtilsGetError(nRetVal));
	}
	return 0;
}

//& type: auto
//& purpose: Gets the locale for date format
/**
* @testcase				ITc_i18n_udate_get_locale_by_type_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Gets the locale for date format
* @apitarget			i18n_udate_get_locale_by_type	
* @apicovered			i18n_udate_get_locale_by_type
* @passcase				I18N_ERROR_NONE returned by i18n_udate_get_locale_by_type 
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_get_locale_by_type or pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_get_locale_by_type_p(void)
{	
	START_TEST;
	
	i18n_ulocale_data_locale_type_e eLocaleType[] = {	I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE,
														I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE};
												
	int nEnumSize = sizeof(eLocaleType) / sizeof(eLocaleType[0]);
	int nEnumCounter = 0, nRetVal = -1;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for Locale type (%s) \\n", __LINE__, API_NAMESPACE, UcalendarGetLocaleType(eLocaleType[nEnumCounter]));
		const char *pszLocale = i18n_udate_get_locale_by_type(g_hUdateFormat, eLocaleType[nEnumCounter]);
		CHECK_HANDLE(pszLocale, "i18n_udate_get_locale_by_type");
		
		nRetVal = get_last_result();
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_get_locale_by_type", BaseUtilsGetError(nRetVal));
	}
	return 0;
}

//& type: auto
//& purpose: Sets a display context value in the formatter
/**
* @testcase				ITc_i18n_udate_set_context_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Sets a display context value in the formatter
* @apitarget			i18n_udate_set_context	
* @apicovered			i18n_udate_set_context
* @passcase				I18N_ERROR_NONE returned by i18n_udate_set_context 
* @failcase				I18N_ERROR_NONE not returned by i18n_udate_set_context or pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udate_set_context_p(void)
{	
	START_TEST;
	
	i18n_udisplay_context_e eDisplayContext[] = {	I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_STANDALONE,
													/*I18N_UDISPLAY_CONTEXT_STANDARD_NAMES,                          
													I18N_UDISPLAY_CONTEXT_DIALECT_NAMES,*/ //As requested by developer 22-05-2015                          
													I18N_UDISPLAY_CONTEXT_CAPITALIZATION_NONE,
													I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_MIDDLE_OF_SENTENCE,
													I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_BEGINNING_OF_SENTENCE,
													I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_UI_LIST_OR_MENU };
												
	int nEnumSize = sizeof(eDisplayContext) / sizeof(eDisplayContext[0]);
	int nEnumCounter = 0, nRetVal = -1;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{	
		FPRINTF("[Line : %d][%s] Executing for Display context value (%s) \\n", __LINE__, API_NAMESPACE, UdateGetDisplayContext(eDisplayContext[nEnumCounter]));
		nRetVal = i18n_udate_set_context(g_hUdateFormat, eDisplayContext[nEnumCounter]);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udate_set_context", BaseUtilsGetError(nRetVal));
	}
	return 0;
}

/** @} */
/** @} */
