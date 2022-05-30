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
//& set: BaseUtilsDateIntervalFmt
const char *g_skeleton = "yMMMd";
int nlength = 50;

/**
* @function 		ITs_base_utils_date_interval_fmt_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_date_interval_fmt_startup(void)
{
	struct stat stBuff;
	int nRetVal = -1;

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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_base_utils_date_interval_fmt_startup\\n", __LINE__, API_NAMESPACE);
#endif
	g_date_int_fmt = NULL;
	nRetVal = i18n_date_interval_fmt_create(g_skeleton, &g_date_int_fmt);
	if ( nRetVal != I18N_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to create date interval format object, error returned = %s\\n", __LINE__,API_NAMESPACE,  BaseUtilsGetError(nRetVal));
		g_bBaseUtilsInitFlag = false;
		return;
	}
	if(g_date_int_fmt == NULL)
	{
		FPRINTF("[Line : %d][%s] date interval format object handle is NULL\\n", __LINE__,API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
		return;
	}

	g_bBaseUtilsInitFlag = true;
}

/**
* @function 		ITs_base_utils_date_interval_fmt_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_date_interval_fmt_cleanup(void)
{
	if ( g_bBaseUtilsInitFlag && g_date_int_fmt )
	{
		int nRetVal = i18n_date_interval_fmt_destroy(g_date_int_fmt);
		if ( nRetVal != I18N_ERROR_NONE )
		{
			FPRINTF("\\n[Line : %d][%s] ITs_base_utils_date_interval_fmt_cleanup failed in cleanup, error returned = %s \n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
		}
		g_date_int_fmt= NULL;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_base_utils_date_interval_fmt_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
}

//& type: auto
//& purpose: Create and Destroy date interval format object.
/**
* @testcase				ITc_i18n_date_interval_fmt_create_destroy_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(j.abhishek)
* @type 				auto
* @scenario				Creates and Distroys a date interval format object.
* @apicovered			i18n_date_interval_fmt_create, i18n_date_interval_fmt_destroy
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_fmt_create_destroy_p(void)
{
	START_TEST;

	i18n_date_interval_fmt_h hDateIntervalFmt = NULL;
	int nRetVal = -1;
	//target API
	nRetVal = i18n_date_interval_fmt_create(g_skeleton, &hDateIntervalFmt);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hDateIntervalFmt, "i18n_date_interval_fmt_create");

	//target API
	nRetVal = i18n_date_interval_fmt_destroy(hDateIntervalFmt);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Clone date interval format object.
/**
* @testcase				ITc_i18n_date_interval_fmt_clone_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(j.abhishek)
* @type 				auto
* @scenario				Clone a date interval format object.
* @apicovered			i18n_date_interval_fmt_clone
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_fmt_clone_p(void)
{
	START_TEST;

	i18n_date_interval_h hCloneDateIntervalFmt = NULL;
	int nRetVal = -1;
	//target API
	nRetVal = i18n_date_interval_fmt_clone(g_date_int_fmt, &hCloneDateIntervalFmt);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_clone", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hCloneDateIntervalFmt, "i18n_date_interval_fmt_clone");

	nRetVal = i18n_date_interval_fmt_destroy( hCloneDateIntervalFmt);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Creates a date interval format object for the given locale..
/**
* @testcase				ITc_i18n_date_interval_fmt_create_from_locale_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(j.abhishek)
* @type 				auto
* @scenario				Creates a date interval format object for the given locale..
* @apicovered			i18n_date_interval_fmt_create_from_locale
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_fmt_create_from_locale_p(void)
{
	START_TEST;

	const char *pszLocale = "en_US";
	i18n_date_interval_fmt_h hDateIntervalFmt = NULL;
	int nRetVal = -1;
	//target API
	nRetVal = i18n_date_interval_fmt_create_from_locale(g_skeleton, pszLocale, &hDateIntervalFmt);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_create_from_locale", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hDateIntervalFmt, "i18n_date_interval_fmt_create_from_locale");

	nRetVal = i18n_date_interval_fmt_destroy( hDateIntervalFmt );
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Sets and Gets the time zone for the calendar used by the #i18n_date_interval_fmt_h object.
/**
* @testcase				ITc_i18n_date_interval_fmt_set_get_time_zone_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(j.abhishek)
* @type 				auto
* @scenario				Sets and Gets the time zone for the calendar used by the #i18n_date_interval_fmt_h object.
* @apicovered			i18n_date_interval_fmt_set_time_zone, i18n_date_interval_fmt_get_time_zone
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_fmt_set_get_time_zone_p(void)
{
	START_TEST;

	i18n_timezone_h hSetTimezone = NULL;
	i18n_timezone_h hGetTimezone = NULL;
	const char *szTimeZoneid = "Europe/London";
	char *pGetTimeZoneId = "";
	int nRetVal = -1;

	nRetVal = i18n_timezone_create(&hSetTimezone, szTimeZoneid);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hSetTimezone, "i18n_timezone_create");

	//target API
	nRetVal = i18n_date_interval_fmt_set_time_zone(g_date_int_fmt, hSetTimezone);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_set_time_zone", BaseUtilsGetError(nRetVal),i18n_timezone_destroy(hSetTimezone));
	nRetVal = i18n_date_interval_fmt_get_time_zone(g_date_int_fmt, &hGetTimezone);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_get_time_zone", BaseUtilsGetError(nRetVal),i18n_timezone_destroy(hSetTimezone));
	CHECK_HANDLE(hGetTimezone, "i18n_date_interval_fmt_get_time_zone");

	nRetVal = i18n_timezone_get_id(hGetTimezone, &pGetTimeZoneId);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_get_id", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(hSetTimezone); i18n_timezone_destroy(hGetTimezone));
	if ( strncmp(szTimeZoneid, pGetTimeZoneId, nlength) != 0 )
	{
		FPRINTF("[Line : %d][%s] Set and Get Timezone value didn't match, GetTimezoneID: %s, SetTimezoneID: %s\\n", __LINE__, API_NAMESPACE, pGetTimeZoneId,szTimeZoneid);
		i18n_timezone_destroy(hSetTimezone);
		i18n_timezone_destroy(hGetTimezone);
		return 1;
	}
	nRetVal = i18n_timezone_destroy(hSetTimezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	nRetVal = i18n_timezone_destroy(hGetTimezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Adopts the time zone for the calendar used by the #i18n_date_interval_fmt_h object.
/**
* @testcase				ITc_i18n_date_interval_fmt_adopt_time_zone_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(j.abhishek)
* @type 				auto
* @scenario				Adopts the time zone for the calendar used by the #i18n_date_interval_fmt_h object.
* @apicovered			i18n_date_interval_fmt_adopt_time_zone
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_fmt_adopt_time_zone_p(void)
{
	START_TEST;

	i18n_timezone_h hTimezone = NULL;
	const char *szTimeZoneid = "Europe/London";
	int nRetVal = -1;

	nRetVal = i18n_timezone_create(&hTimezone, szTimeZoneid);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hTimezone, "i18n_timezone_create");
	//Target API
	nRetVal = i18n_date_interval_fmt_adopt_time_zone(g_date_int_fmt, hTimezone);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_adopt_time_zone", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Formats a date interval to produce a string.
/**
* @testcase				ITc_i18n_date_interval_fmt_format_with_date_interval_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(j.abhishek)
* @type 				auto
* @scenario				Formats a date interval to produce a string.
* @apicovered			i18n_date_interval_fmt_format_with_date_interval
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_fmt_format_with_date_interval_p(void)
{
	START_TEST;

	i18n_field_position_h hFieldPos = NULL;
	i18n_date_interval_h hDateInterval = NULL;
	i18n_udate nFromDate = 1000000.0;
	i18n_udate nToDate = 1500000.0;
	const char *nResult = "Date: Jan 1, 1970";
	const char *pszDefaultLocale = "en_US";
	i18n_date_interval_fmt_h hDateIntervalFmt = NULL;

	int nRetVal = -1;

	nRetVal = i18n_date_interval_create(nFromDate, nToDate, &hDateInterval);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hDateInterval, "i18n_date_interval_create");

	nRetVal = i18n_field_position_create(&hFieldPos);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_field_position_create", BaseUtilsGetError(nRetVal),i18n_date_interval_destroy(hDateInterval));
	CHECK_HANDLE_CLEANUP(hFieldPos, "i18n_field_position_create",i18n_date_interval_destroy(hDateInterval));

	nRetVal = i18n_date_interval_fmt_create_from_locale(g_skeleton, pszDefaultLocale, &hDateIntervalFmt);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_create_from_locale", BaseUtilsGetError(nRetVal), i18n_date_interval_destroy(hDateInterval); i18n_field_position_destroy(hFieldPos));
	CHECK_HANDLE_CLEANUP(hDateIntervalFmt, "i18n_date_interval_fmt_create_from_locale", i18n_date_interval_destroy(hDateInterval); i18n_field_position_destroy(hFieldPos));

	char *nAppendTo = malloc(sizeof(char) * BUFFER);
	if (!nAppendTo)
	{
		i18n_date_interval_destroy(hDateInterval);
		i18n_field_position_destroy(hFieldPos);
		i18n_date_interval_fmt_destroy(hDateIntervalFmt);
		FPRINTF("[Line : %d][%s] result and append value value didn't match, nAppendTo: %s, nResult: %s\\n", __LINE__, API_NAMESPACE, nAppendTo, nResult);
		return 1;
	}
	snprintf(nAppendTo, BUFFER, "Date: ");

	//Target API
	nRetVal = i18n_date_interval_fmt_format_with_date_interval(hDateIntervalFmt, hDateInterval, &nAppendTo, hFieldPos);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_format_with_date_interval", BaseUtilsGetError(nRetVal), i18n_date_interval_destroy(hDateInterval); i18n_field_position_destroy(hFieldPos); i18n_date_interval_fmt_destroy(hDateIntervalFmt); FREE_MEMORY(nAppendTo));
	if ( strncmp(nAppendTo, nResult, nlength) != 0 )
	{
		FPRINTF("[Line : %d][%s] result and append value value didn't match, nAppendTo: %s, nResult: %s\\n", __LINE__, API_NAMESPACE, nAppendTo, nResult);
		i18n_date_interval_destroy(hDateInterval);
		i18n_field_position_destroy(hFieldPos);
		i18n_date_interval_fmt_destroy(hDateIntervalFmt);
		FREE_MEMORY(nAppendTo);
		return 1;
	}

	FREE_MEMORY(nAppendTo);
	nRetVal = i18n_date_interval_destroy(hDateInterval);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_destroy", BaseUtilsGetError(nRetVal));
	nRetVal = i18n_field_position_destroy(hFieldPos);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_field_position_destroy", BaseUtilsGetError(nRetVal));
	nRetVal = i18n_date_interval_fmt_destroy(hDateIntervalFmt);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Formats two calendars to produce a string.
/**
* @testcase				ITc_i18n_date_interval_fmt_format_with_calendar_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(j.abhishek)
* @type 				auto
* @scenario				Formats two calendars to produce a string.
* @apicovered			i18n_date_interval_fmt_format_with_calendar
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_fmt_format_with_calendar_p(void)
{
	START_TEST;

	i18n_field_position_h hFieldPos = NULL;
	i18n_uchar *hDefaultTzid = NULL;
	int nLengthDefaultTimeZone = 0;
	i18n_ucalendar_h nFromUcalender = NULL;
	i18n_ucalendar_h nToUcalender = NULL;
	const char *pszDefaultLocale = "en_US";
	const char *nResult = "Date: Oct 11, 2000 \u2013 Oct 11, 2014";
	i18n_date_interval_fmt_h hDateIntervalFmt = NULL;

	int nRetVal = -1;

	nRetVal = i18n_ucalendar_create(hDefaultTzid, nLengthDefaultTimeZone, pszDefaultLocale, I18N_UCALENDAR_DEFAULT, &nFromUcalender);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_ucalendar_set_date_time(nFromUcalender, YEAR_FROM_VALUE, MONTH_VALUE, DATE_VALUE, HOUR_VALUE, MINUTE_VALUE, SEC_VALUE);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_set_date_time", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(nFromUcalender));

	nRetVal = i18n_ucalendar_create(hDefaultTzid, nLengthDefaultTimeZone, pszDefaultLocale, I18N_UCALENDAR_DEFAULT, &nToUcalender);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(nFromUcalender));

	nRetVal = i18n_ucalendar_set_date_time(nToUcalender, YEAR_VALUE, MONTH_VALUE, DATE_VALUE, HOUR_VALUE, MINUTE_VALUE, SEC_VALUE);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_set_date_time", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(nFromUcalender); i18n_ucalendar_destroy(nToUcalender));

	nRetVal = i18n_field_position_create(&hFieldPos);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_field_position_create", BaseUtilsGetError(nRetVal),i18n_ucalendar_destroy(nFromUcalender); i18n_ucalendar_destroy(nToUcalender));
	CHECK_HANDLE_CLEANUP(hFieldPos, "i18n_field_position_create",i18n_ucalendar_destroy(nFromUcalender); i18n_ucalendar_destroy(nToUcalender));

	nRetVal = i18n_date_interval_fmt_create_from_locale(g_skeleton, pszDefaultLocale, &hDateIntervalFmt);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_create_from_locale", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(nFromUcalender); i18n_ucalendar_destroy(nToUcalender); i18n_field_position_destroy(hFieldPos));
	CHECK_HANDLE_CLEANUP(hDateIntervalFmt, "i18n_date_interval_fmt_create_from_locale", i18n_ucalendar_destroy(nFromUcalender); i18n_ucalendar_destroy(nToUcalender); i18n_field_position_destroy(hFieldPos));

	char *nAppendTo = malloc(sizeof(char) * BUFFER);
	if (!nAppendTo)
	{
		i18n_ucalendar_destroy(nFromUcalender);
		i18n_ucalendar_destroy(nToUcalender);
		i18n_field_position_destroy(hFieldPos);
		i18n_date_interval_fmt_destroy(hDateIntervalFmt);
		FPRINTF("[Line : %d][%s] result and append value value didn't match, nAppendTo: %s, nResult: %s\\n", __LINE__, API_NAMESPACE, nAppendTo, nResult);
		return 1;
	}
	snprintf(nAppendTo, BUFFER, "Date: ");

	//Target API
	nRetVal = i18n_date_interval_fmt_format_with_calendar(hDateIntervalFmt, nFromUcalender, nToUcalender, &nAppendTo, hFieldPos);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_format_with_calendar", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(nFromUcalender); i18n_ucalendar_destroy(nToUcalender); i18n_field_position_destroy(hFieldPos); i18n_date_interval_fmt_destroy(hDateIntervalFmt); FREE_MEMORY(nAppendTo));
	if ( strncmp(nAppendTo, nResult, nlength) != 0 )
	{
		FPRINTF("[Line : %d][%s] result and append value value didn't match, nAppendTo: %s, nResult: %s\\n", __LINE__, API_NAMESPACE, nAppendTo, nResult);
		i18n_ucalendar_destroy(nFromUcalender);
		i18n_ucalendar_destroy(nToUcalender);
		i18n_field_position_destroy(hFieldPos);
		i18n_date_interval_fmt_destroy(hDateIntervalFmt);
		FREE_MEMORY(nAppendTo);
		return 1;
	}

	FREE_MEMORY(nAppendTo);
	nRetVal = i18n_ucalendar_destroy(nFromUcalender);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	nRetVal = i18n_ucalendar_destroy(nToUcalender);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	nRetVal = i18n_field_position_destroy(hFieldPos);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_field_position_destroy", BaseUtilsGetError(nRetVal));
	nRetVal = i18n_date_interval_fmt_destroy(hDateIntervalFmt);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Compares two date interval format objects.
/**
* @testcase				ITc_i18n_date_interval_fmt_equals_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(j.abhishek)
* @type 				auto
* @scenario				Compares two date interval format objects.
* @apicovered			i18n_date_interval_fmt_equals
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_fmt_equals_p(void)
{
	START_TEST;

	i18n_date_interval_fmt_h hDateIntervalFmt = NULL;
	const char *nskeleton = "yMEd";
	bool nIsEqual = true;
	int nRetVal = -1;

	nRetVal = i18n_date_interval_fmt_create(nskeleton, &hDateIntervalFmt);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hDateIntervalFmt, "i18n_date_interval_fmt_create");

	//target API
	nRetVal = i18n_date_interval_fmt_equals(g_date_int_fmt, hDateIntervalFmt, &nIsEqual);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_equals", BaseUtilsGetError(nRetVal), i18n_date_interval_fmt_destroy(hDateIntervalFmt));
	if ( nIsEqual == true )
	{
		FPRINTF("[Line : %d][%s] date_interval_format values mismatch\\n", __LINE__, API_NAMESPACE);
		i18n_date_interval_fmt_destroy(hDateIntervalFmt);
		return 1;
	}

	nRetVal = i18n_date_interval_fmt_destroy(hDateIntervalFmt);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_fmt_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}
