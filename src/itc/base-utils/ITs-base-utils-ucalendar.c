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

static i18n_ucalendar_h g_hUcalender = NULL;
static i18n_uchar *pszUcharTzone = NULL;

//& set: BaseUtilsUcalendar
void ITs_base_utils_ucalendar_startup(void)
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
	
	pszUcharTzone = (i18n_uchar*)calloc(strlen(I18N_DEFAULT_T_ZONE) + 1, sizeof(i18n_uchar));
	if (pszUcharTzone == NULL) 
	{
		FPRINTF("\\n[Line : %d][%s] pszUcharTzone, memory not allocated \n", __LINE__, API_NAMESPACE);
        g_bBaseUtilsInitFlag = false;
		return;
    }
	
	i18n_uchar *pRet = i18n_ustring_copy_ua(pszUcharTzone, I18N_DEFAULT_T_ZONE);
	int32_t nLength = i18n_ustring_get_length(pszUcharTzone);
    
	if ( pRet == NULL || nLength <= 0 )
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in startup\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
		return;
	}
	
	int nRetVal = i18n_ucalendar_create(pszUcharTzone, nLength, pszDefaultLocale, I18N_UCALENDAR_TRADITIONAL, &g_hUcalender);
	if (nRetVal != I18N_ERROR_NONE || g_hUcalender == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ucalendar_create failed in startup, error returned = %s or handle is NULL \n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
		g_bBaseUtilsInitFlag = false;
		return;
	}
	
	g_bBaseUtilsInitFlag = true;
	return;
}

void ITs_base_utils_ucalendar_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRetVal = i18n_ucalendar_destroy(g_hUcalender);
	if (nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ucalendar_destroy failed in cleanup, error returned = %s \n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
	}
	
	FREE_MEMORY(pszUcharTzone);
	g_hUcalender = NULL;
	g_bBaseUtilsInitFlag = false;	
	return;
}

/** @addtogroup itc-base-utils-testcases
*  @brief 		Integration testcases for module base-utils ucalendar
*  @ingroup 	itc-base-utils
*  @{
*/

//& type: auto
//& purpose: Gets the current date and time.
/**
* @testcase				ITc_i18n_ucalendar_get_now_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the current date and time.
* @apitarget			i18n_ucalendar_get_now
* @apicovered			i18n_ucalendar_get_now
* @passcase				When i18n_ucalendar_get_now is successful
* @failcase				If target i18n_ucalendar_get_now API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_now_p(void)
{	
	START_TEST;
	i18n_udate uDate;
	int nRetVal = i18n_ucalendar_get_now(&uDate);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_get_now", BaseUtilsGetError(nRetVal));
	return 0;
}
//& type: auto
//& purpose: Creates and Destroy i18n_ucalendar. 
/**
* @testcase				ITc_i18n_ucalendar_create_destroy_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates i18n_ucalendar.\n
* 						Destroy i18n_ucalendar. 	
* @apitarget			i18n_ucalendar_create, i18n_ucalendar_destroy
* @apicovered			i18n_ucalendar_create, i18n_ucalendar_destroy
* @passcase				When i18n_ucalendar_create, i18n_ucalendar_destroy are successful
* @failcase				If target i18n_ucalendar_create or i18n_ucalendar_destroy fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_create_destroy_p(void)
{
	START_TEST;

	i18n_ucalendar_type_e eCalenderType[] = {I18N_UCALENDAR_TRADITIONAL, 
		I18N_UCALENDAR_GREGORIAN};
	int nEnumSize = sizeof(eCalenderType) / sizeof(eCalenderType[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		i18n_ucalendar_h ucalender = NULL;
		FPRINTF("[Line : %d][%s] Executing i18n_ucalendar_create with Calender Type(%s) and default Locale=%s\\n", __LINE__, API_NAMESPACE, UcalenderGetType(eCalenderType[nEnumCounter]), g_pszDefaultLocale);
		int nRetVal = i18n_ucalendar_create(g_pDefaultTzid, g_nLengthDefaultTimeZone, g_pszDefaultLocale, eCalenderType[nEnumCounter], &ucalender);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal));

		nRetVal = i18n_ucalendar_destroy(ucalender);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	}
	return 0;
}

//& type: auto
//& purpose: Adds a specified signed amount to a particular field in a i18n_ucalendar. Gets the current value of a field from a i18n_ucalendar. 
/**
* @testcase				ITc_i18n_ucalendar_add_get_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Adds a specified signed amount to a particular field in a i18n_ucalendar.\n
* 						Gets the current value of a field from a i18n_ucalendar.. 	
* @apitarget			i18n_ucalendar_add, i18n_ucalendar_get
* @apicovered			i18n_ucalendar_add, i18n_ucalendar_get, i18n_ucalendar_create, i18n_ucalendar_destroy
* @passcase				When i18n_ucalendar_add, i18n_ucalendar_get are successful
* @failcase				If target i18n_ucalendar_add or i18n_ucalendar_get fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_add_get_p(void)
{
	START_TEST;

	i18n_ucalendar_h ucalender = NULL;
	int nRetVal = i18n_ucalendar_create(g_pDefaultTzid, g_nLengthDefaultTimeZone, g_pszDefaultLocale, I18N_UCALENDAR_DEFAULT, &ucalender);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal));

	i18n_ucalendar_date_fields_e eDateFields[] = {I18N_UCALENDAR_ERA, 
		I18N_UCALENDAR_YEAR,
		I18N_UCALENDAR_MONTH,
		I18N_UCALENDAR_WEEK_OF_YEAR,
		I18N_UCALENDAR_WEEK_OF_MONTH,
		I18N_UCALENDAR_DATE,
		I18N_UCALENDAR_DAY_OF_YEAR,
		I18N_UCALENDAR_DAY_OF_WEEK,
		I18N_UCALENDAR_DAY_OF_WEEK_IN_MONTH,
		I18N_UCALENDAR_AM_PM,
		I18N_UCALENDAR_HOUR,
		I18N_UCALENDAR_HOUR_OF_DAY,
		I18N_UCALENDAR_MINUTE,
		I18N_UCALENDAR_SECOND,
		I18N_UCALENDAR_MILLISECOND,
		/*I18N_UCALENDAR_ZONE_OFFSET,
		I18N_UCALENDAR_DST_OFFSET*/};
	int nEnumSize = sizeof(eDateFields) / sizeof(eDateFields[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		FPRINTF("[Line : %d][%s] Executing i18n_ucalendar_add with DateField Value(%s) and UCALENDER_AMOUNT_VALUE=%d\\n", __LINE__, API_NAMESPACE, UcalenderDateFieldValue(eDateFields[nEnumCounter]), UCALENDER_AMOUNT_VALUE);
		nRetVal = i18n_ucalendar_add(ucalender, eDateFields[nEnumCounter], UCALENDER_AMOUNT_VALUE);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_add", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender));

		int nValue = 0;
		nRetVal = i18n_ucalendar_get(ucalender, eDateFields[nEnumCounter], &nValue);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_get", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender));
	}
	
	nRetVal = i18n_ucalendar_destroy(ucalender);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Sets a i18n_ucalendar's current date. Gets a i18n_ucalendar's current time in millis. 
/**
* @testcase				ITc_i18n_ucalendar_set_date_time_get_milliseconds_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Sets a i18n_ucalendar's current date.\n
* 						Gets a i18n_ucalendar's current time in millis.
* @apitarget			i18n_ucalendar_set_date_time, i18n_ucalendar_get_milliseconds
* @apicovered			i18n_ucalendar_set_date_time, i18n_ucalendar_get_milliseconds, i18n_ucalendar_create, i18n_ucalendar_destroy
* @passcase				When i18n_ucalendar_set_date_time, i18n_ucalendar_get_milliseconds are successful
* @failcase				If target i18n_ucalendar_set_date_time or i18n_ucalendar_get_milliseconds fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_set_date_time_get_milliseconds_p(void)
{
	START_TEST;

	i18n_ucalendar_h ucalender = NULL;
	int nRetVal = i18n_ucalendar_create(g_pDefaultTzid, g_nLengthDefaultTimeZone, g_pszDefaultLocale, I18N_UCALENDAR_DEFAULT, &ucalender);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_ucalendar_set_date_time(ucalender, YEAR_VALUE, MONTH_VALUE, DATE_VALUE, HOUR_VALUE, MINUTE_VALUE, SEC_VALUE);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_set_date_time", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender));

	i18n_udate uDate;
	nRetVal = i18n_ucalendar_get_milliseconds(ucalender, &uDate);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_get_milliseconds", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender));

	nRetVal = i18n_ucalendar_destroy(ucalender);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Sets and gets numeric attribute associated with a i18n_ucalendar. 
/**
* @testcase				ITc_i18n_ucalendar_set_get_attribute_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Sets and gets numeric attribute associated with a i18n_ucalendar.
* @apitarget			i18n_ucalendar_set_attribute, i18n_ucalendar_get_attribute
* @apicovered			i18n_ucalendar_set_attribute, i18n_ucalendar_get_attribute, i18n_ucalendar_create, i18n_ucalendar_destroy
* @passcase				When i18n_ucalendar_set_attribute and i18n_ucalendar_get_attribute is successful
* @failcase				If target i18n_ucalendar_set_attribute or i18n_ucalendar_get_attribute fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_set_get_attribute_p(void)
{
	START_TEST;

	i18n_ucalendar_h ucalender = NULL;
	int nRetVal = i18n_ucalendar_create(g_pDefaultTzid, g_nLengthDefaultTimeZone, g_pszDefaultLocale, I18N_UCALENDAR_DEFAULT, &ucalender);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal));

	i18n_ucalendar_attribute_e eCalenderAttributeType[] = {I18N_UCALENDAR_LENIENT, 
		I18N_UCALENDAR_FIRST_DAY_OF_WEEK, 
		I18N_UCALENDAR_MINIMAL_DAYS_IN_FIRST_WEEK};
	int nEnumSize = sizeof(eCalenderAttributeType) / sizeof(eCalenderAttributeType[0]);
	int nEnumCounter = 0;
	int nGetVal;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		FPRINTF("[Line : %d][%s] Executing i18n_ucalendar_set_attribute with Attribute Type(%s) and Value = %d\\n", __LINE__, API_NAMESPACE, UcalenderGetAttributeType(eCalenderAttributeType[nEnumCounter]), nEnumCounter);
		nRetVal = i18n_ucalendar_set_attribute(ucalender, eCalenderAttributeType[nEnumCounter], nEnumCounter);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_set_attribute", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender));

		FPRINTF("[Line : %d][%s] Executing i18n_ucalendar_get_attribute with Attribute Type(%s)\\n", __LINE__, API_NAMESPACE, UcalenderGetAttributeType(eCalenderAttributeType[nEnumCounter]));

		nRetVal = i18n_ucalendar_get_attribute(ucalender, eCalenderAttributeType[nEnumCounter], &nGetVal);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_get_attribute", BaseUtilsGetError(nRetVal),i18n_ucalendar_destroy(ucalender));
		if ( nEnumCounter != nGetVal )
		{
			FPRINTF("[Line : %d][%s] Target API i18n_ucalendar_get_attribute Failed\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	nRetVal = i18n_ucalendar_destroy(ucalender);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Gets the display name for a i18n_ucalendar's TimeZone. 
/**
* @testcase				ITc_i18n_ucalendar_get_timezone_displayname_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the display name for a i18n_ucalendar's TimeZone.
* @apitarget			i18n_ucalendar_get_timezone_displayname
* @apicovered			i18n_ucalendar_get_timezone_displayname, i18n_ucalendar_create, i18n_ucalendar_destroy, i18n_ustring_copy_au_n
* @passcase				When i18n_ucalendar_get_timezone_displayname is successful
* @failcase				If target i18n_ucalendar_get_timezone_displayname fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_timezone_displayname_p(void)
{
	START_TEST;

	i18n_ucalendar_h ucalender = NULL;
	int nRetVal = i18n_ucalendar_create(g_pDefaultTzid, g_nLengthDefaultTimeZone, g_pszDefaultLocale, I18N_UCALENDAR_DEFAULT, &ucalender);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal));

	i18n_ucalendar_displayname_type_e eCalenderDisplayNameType[] = {I18N_UCALENDAR_STANDARD, 
		I18N_UCALENDAR_SHORT_STANDARD, 
		I18N_UCALENDAR_DST,
		I18N_UCALENDAR_SHORT_DST};
	int nEnumSize = sizeof(eCalenderDisplayNameType) / sizeof(eCalenderDisplayNameType[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		i18n_uchar timeZoneDisplayName[I18N_RESULT_LEN];
		int nDisplayNameSizeNeeded = 0;
		FPRINTF("[Line : %d][%s] Executing i18n_ucalendar_get_timezone_displayname with Display Name Type(%s) and default Locale=%s\\n", __LINE__, API_NAMESPACE, UcalenderGetDisplayNameType(eCalenderDisplayNameType[nEnumCounter]), g_pszDefaultLocale);

		nRetVal = i18n_ucalendar_get_timezone_displayname(ucalender, eCalenderDisplayNameType[nEnumCounter], g_pszDefaultLocale, timeZoneDisplayName, I18N_RESULT_LEN, &nDisplayNameSizeNeeded);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_get_timezone_displayname", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender));
		if ( nDisplayNameSizeNeeded > I18N_RESULT_LEN )
		{
			FPRINTF("[Line : %d][%s] The Returned TimeZone Display Name Buffer Size(%d) is greater than Display Name capacity(%d)\\n", __LINE__, API_NAMESPACE, nDisplayNameSizeNeeded, I18N_RESULT_LEN);
		}
		char pstTimeZoneDisplayName[I18N_RESULT_LEN] = {0,};
		i18n_ustring_copy_au_n(pstTimeZoneDisplayName, timeZoneDisplayName, I18N_RESULT_LEN);
		if ( strlen(pstTimeZoneDisplayName) <= 0 )
		{
			FPRINTF("[Line : %d][%s] i18n_ucalendar_get_timezone_displayname failed  as The result Formatted Date Char Length is either less than or Equal to Zero.", __LINE__, API_NAMESPACE);
			nRetVal = i18n_ucalendar_destroy(ucalender);
			PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
			return 1;
		}
	}
	nRetVal = i18n_ucalendar_destroy(ucalender);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Sets a i18n_ucalendar's current time in millis. 
/**
* @testcase				ITc_i18n_ucalendar_set_milliseconds_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Sets a i18n_ucalendar's current time in millis.
* @apitarget			i18n_ucalendar_set_milliseconds
* @apicovered			i18n_ucalendar_set_milliseconds, i18n_ucalendar_create, i18n_ucalendar_destroy, i18n_ucalendar_get_now
* @passcase				When i18n_ucalendar_set_milliseconds is successful
* @failcase				If target i18n_ucalendar_set_milliseconds fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_set_milliseconds_p(void)
{
	START_TEST;

	i18n_ucalendar_h ucalender = NULL;
	int nRetVal = i18n_ucalendar_create(g_pDefaultTzid, g_nLengthDefaultTimeZone, g_pszDefaultLocale, I18N_UCALENDAR_DEFAULT, &ucalender);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal));

	i18n_udate uDate;
	nRetVal = i18n_ucalendar_get_now(&uDate);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_get_now", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender));

	nRetVal = i18n_ucalendar_set_milliseconds(ucalender, uDate);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_set_milliseconds", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender));

	nRetVal = i18n_ucalendar_destroy(ucalender);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Determines if a i18n_ucalendar is currently in daylight savings time. 
/**
* @testcase				ITc_i18n_ucalendar_is_in_daylight_time_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Determines if a i18n_ucalendar is currently in daylight savings time.
* @apitarget			i18n_ucalendar_is_in_daylight_time
* @apicovered			i18n_ucalendar_is_in_daylight_time, i18n_ucalendar_create, i18n_ucalendar_destroy
* @passcase				When i18n_ucalendar_is_in_daylight_time is successful
* @failcase				If target i18n_ucalendar_is_in_daylight_time fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_is_in_daylight_time_p(void)
{
	START_TEST;

	i18n_ucalendar_h ucalender = NULL;

	int nRetVal = i18n_ucalendar_create(g_pDefaultTzid, g_nLengthDefaultTimeZone, g_pszDefaultLocale, I18N_UCALENDAR_DEFAULT, &ucalender);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal));

	i18n_ubool bEqualityResult = false;
	nRetVal = i18n_ucalendar_is_in_daylight_time(ucalender, &bEqualityResult);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_is_in_daylight_time", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender));

	nRetVal = i18n_ucalendar_destroy(ucalender);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Checks Two i18n_ucalendars are equivalent. 
/**
* @testcase				ITc_i18n_ucalendar_is_equivalent_to_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Checks Two i18n_ucalendars are equivalent.
* @apitarget			i18n_ucalendar_is_equivalent_to
* @apicovered			i18n_ucalendar_is_equivalent_to, i18n_ucalendar_create, i18n_ucalendar_destroy, i18n_ucalendar_set_date_time
* @passcase				When i18n_ucalendar_is_equivalent_to is successful
* @failcase				If target i18n_ucalendar_is_equivalent_to fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_is_equivalent_to_p(void)
{
	START_TEST;

	i18n_ucalendar_h ucalender1 = NULL;
	int nRetVal = i18n_ucalendar_create(g_pDefaultTzid, g_nLengthDefaultTimeZone, g_pszDefaultLocale, I18N_UCALENDAR_DEFAULT, &ucalender1);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_ucalendar_set_date_time(ucalender1, YEAR_VALUE, MONTH_VALUE, DATE_VALUE, HOUR_VALUE, MINUTE_VALUE, SEC_VALUE);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_set_date_time", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender1));

	i18n_ucalendar_h ucalender2 = NULL;
	nRetVal = i18n_ucalendar_create(g_pDefaultTzid, g_nLengthDefaultTimeZone, g_pszDefaultLocale, I18N_UCALENDAR_DEFAULT, &ucalender2);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender1));

	nRetVal = i18n_ucalendar_set_date_time(ucalender2, YEAR_VALUE, MONTH_VALUE, DATE_VALUE, HOUR_VALUE, MINUTE_VALUE, SEC_VALUE);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_set_date_time", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender2); i18n_ucalendar_destroy(ucalender1));

	i18n_ubool bEqualityResult = false;
	nRetVal = i18n_ucalendar_is_equivalent_to(ucalender1, ucalender2, &bEqualityResult);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_is_equivalent_to", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender2); i18n_ucalendar_destroy(ucalender1));
	if ( !bEqualityResult )
	{
		FPRINTF("[Line : %d][%s] i18n_ucalendar_is_equivalent_to failed as returned Equivalent value is False and Expected is True\n", __LINE__, API_NAMESPACE);
		nRetVal = i18n_ucalendar_destroy(ucalender1);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
		
		nRetVal = i18n_ucalendar_destroy(ucalender2);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
		return 1;
	}

	nRetVal = i18n_ucalendar_destroy(ucalender1);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_ucalendar_destroy(ucalender2);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose:  Making clone of existing calendar.
/**
* @testcase				ITc_i18n_ucalendar_clone_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Making clone  of existing calendar
* @apitarget			i18n_ucalendar_clone
* @apicovered			i18n_ucalendar_clone, i18n_ucalendar_create, i18n_ucalendar_destroy
* @passcase				When i18n_ucalendar_clone is successful
* @failcase				If target i18n_ucalendar_clone fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_clone_p(void)
{
	START_TEST;

	i18n_ucalendar_h ucalender = NULL;
	i18n_ucalendar_h ucalender_clone = NULL;

	int nRetVal = i18n_ucalendar_create(g_pDefaultTzid, g_nLengthDefaultTimeZone, g_pszDefaultLocale, I18N_UCALENDAR_DEFAULT, &ucalender);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(ucalender, "i18n_ucalendar_create");
	
	nRetVal = i18n_ucalendar_clone(ucalender, &ucalender_clone);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_clone", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender));
	CHECK_HANDLE(ucalender_clone, "i18n_ucalendar_clone");
	
	nRetVal = i18n_ucalendar_destroy(ucalender_clone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_ucalendar_destroy(ucalender);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}


//& type: auto
//& purpose: Used to set data fields.
/**
* @testcase				ITc_i18n_ucalendar_set_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Used to set data fields
* @apitarget			i18n_ucalendar_set
* @apicovered			i18n_ucalendar_set, i18n_ucalendar_create, i18n_ucalendar_destroy
* @passcase				When i18n_ucalendar_set is successful
* @failcase				If target i18n_ucalendar_set fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_set_p(void)
{
	START_TEST;

	i18n_ucalendar_h ucalender = NULL;
	int nVal = 0;
	i18n_ucalendar_date_fields_e eDateFields[] = {I18N_UCALENDAR_ERA, 
		I18N_UCALENDAR_YEAR,
		I18N_UCALENDAR_MONTH,
		I18N_UCALENDAR_WEEK_OF_YEAR,
		I18N_UCALENDAR_WEEK_OF_MONTH,
		I18N_UCALENDAR_DATE,
		I18N_UCALENDAR_DAY_OF_YEAR,
		I18N_UCALENDAR_DAY_OF_WEEK,
		I18N_UCALENDAR_DAY_OF_WEEK_IN_MONTH,
		I18N_UCALENDAR_AM_PM,
		I18N_UCALENDAR_HOUR,
		I18N_UCALENDAR_HOUR_OF_DAY,
		I18N_UCALENDAR_MINUTE,
		I18N_UCALENDAR_SECOND,
		I18N_UCALENDAR_MILLISECOND,
		/*I18N_UCALENDAR_ZONE_OFFSET,
		I18N_UCALENDAR_DST_OFFSET*/};
	int nEnumSize = sizeof(eDateFields) / sizeof(eDateFields[0]);
	int nEnumCounter = 0;
	int nRetVal = i18n_ucalendar_create(g_pDefaultTzid, g_nLengthDefaultTimeZone, g_pszDefaultLocale, I18N_UCALENDAR_DEFAULT, &ucalender);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_create", BaseUtilsGetError(nRetVal));

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		nRetVal = i18n_ucalendar_set(ucalender, eDateFields[nEnumCounter], nVal);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_set", BaseUtilsGetError(nRetVal), i18n_ucalendar_destroy(ucalender));
	}
	nRetVal = i18n_ucalendar_destroy(ucalender);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose:  Setting default time zone.
/**
* @testcase				ITc_i18n_ucalendar_set_default_timezone_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Setting default time zone.
* @apitarget			i18n_ucalendar_set_default_timezone
* @apicovered			i18n_ucalendar_set_default_timezone
* @passcase				When i18n_ucalendar_set_default_timezone is successful
* @failcase				If target i18n_ucalendar_set_default_timezone fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_set_default_timezone_p(void)
{
	START_TEST;

	i18n_uchar nZoneId = 0; 

	int nRetVal = i18n_ucalendar_set_default_timezone(&nZoneId);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_set_default_timezone", BaseUtilsGetError(nRetVal));

	return 0;
}


//& type: auto
//& purpose: Creates an enumeration over system time zone IDs with given filter conditions
/**
* @testcase				ITc_i18n_ucalendar_timezone_id_enumeration_create_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Creates an enumeration over system time zone IDs with given filter conditions
* @apitarget			i18n_ucalendar_timezone_id_enumeration_create	
* @apicovered			i18n_ucalendar_timezone_id_enumeration_create, i18n_uenumeration_destroy
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_timezone_id_enumeration_create
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_timezone_id_enumeration_create or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_timezone_id_enumeration_create_p(void)
{	
	START_TEST_PRINT;
	char *pszCountryCode = "KR";
	i18n_uenumeration_h hEnumeration = NULL;

	i18n_system_timezone_type_e eTimezoneType[] = {	I18N_UCALENDAR_ZONE_TYPE_ANY,                 
													I18N_UCALENDAR_ZONE_TYPE_CANONICAL,           
													I18N_UCALENDAR_ZONE_TYPE_CANONICAL_LOCATION};
	int nEnumSize = sizeof(eTimezoneType) / sizeof(eTimezoneType[0]);
	int nEnumCounter = 0, nRetVal = -1;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for TimeZone type (%s) \\n", __LINE__, API_NAMESPACE, UcalendarGetTimezoneType(eTimezoneType[nEnumCounter]));
		nRetVal = i18n_ucalendar_timezone_id_enumeration_create(eTimezoneType[nEnumCounter], pszCountryCode, NULL, &hEnumeration);
		CHECK_HANDLE(hEnumeration, "i18n_ucalendar_timezone_id_enumeration_create");
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_timezone_id_enumeration_create", BaseUtilsGetError(nRetVal));
		
		i18n_uenumeration_destroy(hEnumeration);
		hEnumeration = NULL;
	}

	return 0;
}

//& type: auto
//& purpose: Creates an enumeration over all time zones
/**
* @testcase				ITc_i18n_ucalendar_timezones_create_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Creates an enumeration over all time zones
* @apitarget			i18n_ucalendar_timezones_create	
* @apicovered			i18n_ucalendar_timezones_create, i18n_uenumeration_destroy
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_timezones_create
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_timezones_create or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_timezones_create_p(void)
{	
	START_TEST_PRINT;
	int nRetVal = -1;
	i18n_uenumeration_h hEnumeration = NULL;

	nRetVal = i18n_ucalendar_timezones_create(&hEnumeration);
	CHECK_HANDLE(hEnumeration, "i18n_ucalendar_timezones_create");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_timezones_create", BaseUtilsGetError(nRetVal));

	i18n_uenumeration_destroy(hEnumeration);
	hEnumeration = NULL;

	return 0;
}

//& type: auto
//& purpose:  Creates an enumeration over all time zones associated with the given country
/**
* @testcase				ITc_i18n_ucalendar_country_timezones_create_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				-  Creates an enumeration over all time zones associated with the given country
* @apitarget			i18n_ucalendar_country_timezones_create	
* @apicovered			i18n_ucalendar_country_timezones_create, i18n_uenumeration_destroy
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_country_timezones_create
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_country_timezones_create or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_country_timezones_create_p(void)
{	
	START_TEST_PRINT;
	int nRetVal = -1;
	char *pszCountryCode = "KR";
	i18n_uenumeration_h hEnumeration = NULL;

	nRetVal = i18n_ucalendar_country_timezones_create(pszCountryCode, &hEnumeration);
	CHECK_HANDLE(hEnumeration, "i18n_ucalendar_country_timezones_create");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_country_timezones_create", BaseUtilsGetError(nRetVal));

	i18n_uenumeration_destroy(hEnumeration);
	hEnumeration = NULL;

	return 0;
}

//& type: auto
//& purpose:  Returns the default time zone
/**
* @testcase				ITc_i18n_ucalendar_get_default_timezone_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				-  Returns the default time zone
* @apitarget			i18n_ucalendar_get_default_timezone	
* @apicovered			i18n_ucalendar_get_default_timezone
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_get_default_timezone
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_get_default_timezone or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_default_timezone_p(void)
{	
	START_TEST_PRINT;
	int nRetVal = -1;
	int32_t nLength = -1;
	i18n_uchar szTimeZone[I18N_UNUMBER_SYMBOL_CAPACITY] = {0};
    int nCapacity = I18N_UNUMBER_SYMBOL_CAPACITY;
	
	nLength = i18n_ucalendar_get_default_timezone(szTimeZone, nCapacity);
	CHECK_RETURN_VAL(nLength, "i18n_ucalendar_get_default_timezone");
	CHECK_HANDLE(szTimeZone, "i18n_ucalendar_get_default_timezone");
	
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_default_timezone", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Sets the TimeZone
/**
* @testcase				ITc_i18n_ucalendar_set_timezone_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Sets the TimeZone
* @apitarget			i18n_ucalendar_set_timezone	
* @apicovered			i18n_ucalendar_set_timezone
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_set_timezone
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_set_timezone or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_set_timezone_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	int32_t nLength = -1;
	int nCapacity = -1;
	char *pszCountryCode = "US";
	i18n_uchar *pszUcharCountryCode = (i18n_uchar*)calloc(strlen(pszCountryCode) + 1, sizeof(i18n_uchar));
	i18n_uchar *pRet = i18n_ustring_copy_ua(pszUcharCountryCode, pszCountryCode);
	nCapacity = i18n_ustring_get_length(pszUcharCountryCode);
	if ( pRet == NULL || i18n_ustring_get_length(pszUcharCountryCode) <= 0 )
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszUcharCountryCode);
		return 1;
	}
	nLength =i18n_ucalendar_set_timezone(g_hUcalender, pszUcharCountryCode, nCapacity);
	CHECK_RETURN_VAL_CLEANUP(nLength, "i18n_ucalendar_set_timezone",FREE_MEMORY(pszUcharCountryCode));

	nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_set_timezone", BaseUtilsGetError(nRetVal),FREE_MEMORY(pszUcharCountryCode));

	FREE_MEMORY(pszUcharCountryCode);
	return 0;
}

//& type: auto
//& purpose:  Gets the TimeZone ID and cannonical TimeZone ID
/**
* @testcase				ITc_i18n_ucalendar_get_timezone_id_get_canonical_timezone_id_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				-  Sets the TimeZone and gets the TimeZone ID and cannonical TimeZone ID
* @apitarget			i18n_ucalendar_get_timezone_id, i18n_ucalendar_get_canonical_timezone_id
* @apicovered			i18n_ucalendar_get_timezone_id, i18n_ucalendar_get_canonical_timezone_id
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_get_timezone_id and i18n_ucalendar_get_canonical_timezone_id
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_get_timezone_id, i18n_ucalendar_get_canonical_timezone_id or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_timezone_id_get_canonical_timezone_id_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	int32_t nLength = -1, nLengthTzId = -1;
	i18n_uchar szTimeZone[I18N_UNUMBER_SYMBOL_CAPACITY] = {0};
	i18n_uchar szCanTimeZone[I18N_UNUMBER_SYMBOL_CAPACITY] = {0};
    int nCapacity = I18N_UNUMBER_SYMBOL_CAPACITY;
	i18n_ubool bSystemId = false;
	
	/* Target API i18n_ucalendar_get_timezone_id */
	nLength = i18n_ucalendar_get_timezone_id(g_hUcalender, szTimeZone, nCapacity);
    CHECK_RETURN_VAL(nLength, "i18n_ucalendar_get_timezone_id");
	CHECK_HANDLE(szTimeZone, "i18n_ucalendar_get_timezone_id");
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_timezone_id", BaseUtilsGetError(nRetVal));

	/* Target API i18n_ucalendar_get_canonical_timezone_id */
	nLengthTzId = i18n_ucalendar_get_canonical_timezone_id(szTimeZone, nLength, szCanTimeZone, nCapacity, &bSystemId);
    CHECK_RETURN_VAL(nLengthTzId, "i18n_ucalendar_get_canonical_timezone_id");
	CHECK_HANDLE(szCanTimeZone, "i18n_ucalendar_get_canonical_timezone_id");
	if(bSystemId != true && bSystemId != false)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ucalendar_get_canonical_timezone_id failed, bool return value is = %d \n", __LINE__, API_NAMESPACE, bSystemId);
		return 1;
	}
		
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_canonical_timezone_id", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose:  Sets and gets the Gregorian Calendar change date
/**
* @testcase				ITc_i18n_ucalendar_set_get_gregorian_change_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				-  Sets and gets the Gregorian Calendar change date
* @apitarget			i18n_ucalendar_set_gregorian_change, i18n_ucalendar_get_gregorian_change
* @apicovered			i18n_ucalendar_set_gregorian_change, i18n_ucalendar_get_gregorian_change
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_set_gregorian_change and i18n_ucalendar_get_gregorian_change
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_set_gregorian_change, i18n_ucalendar_get_gregorian_change or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_set_get_gregorian_change_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	i18n_udate nUdateSet = 1500;
	i18n_udate nUdateGet = 0;
	
	nRetVal = i18n_ucalendar_set_gregorian_change(g_hUcalender, nUdateSet);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_set_gregorian_change", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_ucalendar_get_gregorian_change(g_hUcalender, &nUdateGet);
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_gregorian_change", BaseUtilsGetError(nRetVal));

	if(nUdateGet != nUdateSet)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ucalendar_get_gregorian_change failed, set and get values are different \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose:  Gets a locale for which calendars are available
/**
* @testcase				ITc_i18n_ucalendar_get_available_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				-  Gets a locale for which calendars are available
* @apitarget			i18n_ucalendar_get_available
* @apicovered			i18n_ucalendar_get_available
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_get_available 
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_get_available
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_available_p(void)
{	
	START_TEST_PRINT;
	int nRetVal = -1;
	int32_t nLocaleIndex = 1;
	const char *pszLocale = NULL;
	
	pszLocale = i18n_ucalendar_get_available(nLocaleIndex);
	CHECK_HANDLE(pszLocale, "i18n_ucalendar_get_available");
	
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_available", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose:  Determines how many locales have calendars available
/**
* @testcase				ITc_i18n_ucalendar_count_available_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				-  Determines how many locales have calendars available
* @apitarget			i18n_ucalendar_count_available
* @apicovered			i18n_ucalendar_count_available
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_count_available 
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_count_available
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_count_available_p(void)
{	
	START_TEST_PRINT;
	int nRetVal = -1;
	int32_t nLocaleCount = -1;
	
	nLocaleCount = i18n_ucalendar_count_available();
	CHECK_RETURN_VAL(nLocaleCount, "i18n_ucalendar_count_available");
	
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_count_available", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose:  Adds a specified signed amount to a particular field in the calendar
/**
* @testcase				ITc_i18n_ucalendar_roll_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Adds a specified signed amount to a particular field in the calendar
* @apitarget			i18n_ucalendar_roll
* @apicovered			i18n_ucalendar_roll
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_roll or pre-condition APIs fail
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_roll
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_roll_p(void)
{	
	START_TEST;
	int32_t nAmount = 2;
	int nEnumCounter = 0, nRetVal = -1;
	
	i18n_ucalendar_date_fields_e eDateFields[] = {	I18N_UCALENDAR_ERA,
													I18N_UCALENDAR_YEAR,
													I18N_UCALENDAR_MONTH,
													I18N_UCALENDAR_WEEK_OF_YEAR,
													I18N_UCALENDAR_WEEK_OF_MONTH,
													I18N_UCALENDAR_DATE, 
													I18N_UCALENDAR_DAY_OF_YEAR,
													I18N_UCALENDAR_DAY_OF_WEEK, 
													I18N_UCALENDAR_DAY_OF_WEEK_IN_MONTH, 
													I18N_UCALENDAR_AM_PM,
													I18N_UCALENDAR_HOUR, 
													I18N_UCALENDAR_HOUR_OF_DAY, 
													I18N_UCALENDAR_MINUTE,
													I18N_UCALENDAR_SECOND,
													I18N_UCALENDAR_MILLISECOND,
													/*I18N_UCALENDAR_ZONE_OFFSET,
													I18N_UCALENDAR_DST_OFFSET*/  //As requested by developer 22-05-2015
												};
	int nEnumSize = sizeof(eDateFields) / sizeof(eDateFields[0]);
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for DateField Value (%s) \\n", __LINE__, API_NAMESPACE, UcalenderDateFieldValue(eDateFields[nEnumCounter]));
		nRetVal = i18n_ucalendar_roll(g_hUcalender, eDateFields[nEnumCounter], nAmount);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_roll", BaseUtilsGetError(nRetVal));
	}
	return 0;
}

//& type: auto
//& purpose:  Determines if a field in a calendar is set
/**
* @testcase				ITc_i18n_ucalendar_is_set_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Determines if a field in a calendar is set
* @apitarget			i18n_ucalendar_is_set
* @apicovered			i18n_ucalendar_is_set
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_is_set or pre-condition APIs fail
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_is_set
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_is_set_p(void)
{	
	START_TEST;
	i18n_ubool bIsSet = false;
	int nEnumCounter = 0, nRetVal = -1;
	
	i18n_ucalendar_date_fields_e eDateFields[] = {	I18N_UCALENDAR_ERA,
													I18N_UCALENDAR_YEAR, 
													I18N_UCALENDAR_MONTH,
													I18N_UCALENDAR_WEEK_OF_YEAR,
													I18N_UCALENDAR_WEEK_OF_MONTH,
													I18N_UCALENDAR_DATE,
													I18N_UCALENDAR_DAY_OF_YEAR,
													I18N_UCALENDAR_DAY_OF_WEEK,
													I18N_UCALENDAR_DAY_OF_WEEK_IN_MONTH,
													I18N_UCALENDAR_AM_PM,                            
													I18N_UCALENDAR_HOUR,                             
													I18N_UCALENDAR_HOUR_OF_DAY,                      
													I18N_UCALENDAR_MINUTE,                           
													I18N_UCALENDAR_SECOND,                           
													I18N_UCALENDAR_MILLISECOND,                      
													I18N_UCALENDAR_ZONE_OFFSET,                      
													I18N_UCALENDAR_DST_OFFSET,                       
													I18N_UCALENDAR_YEAR_WOY,                         
													I18N_UCALENDAR_DOW_LOCAL,
													I18N_UCALENDAR_EXTENDED_YEAR,                    
													I18N_UCALENDAR_JULIAN_DAY,                       
													I18N_UCALENDAR_MILLISECONDS_IN_DAY,              
													I18N_UCALENDAR_IS_LEAP_MONTH,                    
													I18N_UCALENDAR_FIELD_COUNT,                      
													I18N_UCALENDAR_DAY_OF_MONTH };
	int nEnumSize = sizeof(eDateFields) / sizeof(eDateFields[0]);
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for DateField Value (%s) \\n", __LINE__, API_NAMESPACE, UcalenderDateFieldValue(eDateFields[nEnumCounter]));
		bIsSet = i18n_ucalendar_is_set(g_hUcalender, eDateFields[nEnumCounter]);
		if(bIsSet != true && bIsSet != false)
		{
			FPRINTF("\\n[Line : %d][%s] i18n_ucalendar_is_set failed, return value is = %d \n", __LINE__, API_NAMESPACE, bIsSet);
			return 1;
		}
	
		nRetVal = get_last_result();
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_is_set", BaseUtilsGetError(nRetVal));
	}
	return 0;
}

//& type: auto
//& purpose:  Clears a field in a calendar
/**
* @testcase				ITc_i18n_ucalendar_clear_field_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Clears a field in a calendar
* @apitarget			i18n_ucalendar_clear_field
* @apicovered			i18n_ucalendar_clear_field
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_clear_field or pre-condition APIs fail
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_clear_field
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_clear_field_p(void)
{	
	START_TEST;
	int nEnumCounter = 0, nRetVal = -1;
	
	i18n_ucalendar_date_fields_e eDateFields[] = {	I18N_UCALENDAR_ERA,
													I18N_UCALENDAR_YEAR, 
													I18N_UCALENDAR_MONTH,
													I18N_UCALENDAR_WEEK_OF_YEAR,
													I18N_UCALENDAR_WEEK_OF_MONTH,
													I18N_UCALENDAR_DATE,
													I18N_UCALENDAR_DAY_OF_YEAR,
													I18N_UCALENDAR_DAY_OF_WEEK,
													I18N_UCALENDAR_DAY_OF_WEEK_IN_MONTH,
													I18N_UCALENDAR_AM_PM,                            
													I18N_UCALENDAR_HOUR,                             
													I18N_UCALENDAR_HOUR_OF_DAY,                      
													I18N_UCALENDAR_MINUTE,                           
													I18N_UCALENDAR_SECOND,                           
													I18N_UCALENDAR_MILLISECOND,                      
													I18N_UCALENDAR_ZONE_OFFSET,                      
													I18N_UCALENDAR_DST_OFFSET,                       
													I18N_UCALENDAR_YEAR_WOY,                         
													I18N_UCALENDAR_DOW_LOCAL,
													I18N_UCALENDAR_EXTENDED_YEAR,                    
													I18N_UCALENDAR_JULIAN_DAY,                       
													I18N_UCALENDAR_MILLISECONDS_IN_DAY,              
													I18N_UCALENDAR_IS_LEAP_MONTH,                    
													I18N_UCALENDAR_FIELD_COUNT,                      
													I18N_UCALENDAR_DAY_OF_MONTH };
	int nEnumSize = sizeof(eDateFields) / sizeof(eDateFields[0]);
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for DateField Value (%s) \\n", __LINE__, API_NAMESPACE, UcalenderDateFieldValue(eDateFields[nEnumCounter]));
		nRetVal = i18n_ucalendar_clear_field(g_hUcalender, eDateFields[nEnumCounter]);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_clear_field", BaseUtilsGetError(nRetVal));
	}
	return 0;
}

//& type: auto
//& purpose:  Clears all fields in a calendar
/**
* @testcase				ITc_i18n_ucalendar_clear_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Clears all fields in a calendar
* @apitarget			i18n_ucalendar_clear
* @apicovered			i18n_ucalendar_clear
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_clear or pre-condition APIs fail
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_clear
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_clear_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	
	nRetVal = i18n_ucalendar_clear(g_hUcalender);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_clear", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Determines a limit for a field in a calendar
/**
* @testcase				ITc_i18n_ucalendar_get_limit_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Determines a limit for a field in a calendar
* @apitarget			i18n_ucalendar_get_limit
* @apicovered			i18n_ucalendar_get_limit
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_get_limit or pre-condition APIs fail
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_get_limit
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_limit_p(void)
{	
	START_TEST;
	int nEnumCounter1 = 0, nEnumCounter2 = 0, nRetVal = -1;
	int32_t nLimit = -1;
	
	i18n_ucalendar_date_fields_e eDateFields[] = {	I18N_UCALENDAR_ERA,
													I18N_UCALENDAR_YEAR, 
													I18N_UCALENDAR_MONTH,
													I18N_UCALENDAR_WEEK_OF_YEAR,
													I18N_UCALENDAR_WEEK_OF_MONTH,
													I18N_UCALENDAR_DATE,
													I18N_UCALENDAR_DAY_OF_YEAR,
													I18N_UCALENDAR_DAY_OF_WEEK,
													I18N_UCALENDAR_DAY_OF_WEEK_IN_MONTH,
													I18N_UCALENDAR_AM_PM,                            
													I18N_UCALENDAR_HOUR,                             
													I18N_UCALENDAR_HOUR_OF_DAY,                      
													I18N_UCALENDAR_MINUTE,                           
													I18N_UCALENDAR_SECOND,                           
													I18N_UCALENDAR_MILLISECOND,                      
													I18N_UCALENDAR_ZONE_OFFSET,                      
													I18N_UCALENDAR_DST_OFFSET };
										
	i18n_ucalendar_limit_type_e eLimitType[] = {	I18N_UCALENDAR_MINIMUM,         
													I18N_UCALENDAR_MAXIMUM,         
													I18N_UCALENDAR_GREATEST_MINIMUM,
													I18N_UCALENDAR_LEAST_MAXIMUM,   
													I18N_UCALENDAR_ACTUAL_MINIMUM,  
													I18N_UCALENDAR_ACTUAL_MAXIMUM  }; 

	int nEnumSize1 = sizeof(eDateFields) / sizeof(eDateFields[0]);
	int nEnumSize2 = sizeof(eLimitType) / sizeof(eLimitType[0]);
	
	for (nEnumCounter1 = 0; nEnumCounter1 < nEnumSize1;  nEnumCounter1++)
	{
		for (nEnumCounter2 = 0; nEnumCounter2 < nEnumSize2;  nEnumCounter2++)
		{
			FPRINTF("[Line : %d][%s] Executing for DateField Value (%s) and Limit type (%s)\\n", __LINE__, API_NAMESPACE, UcalenderDateFieldValue(eDateFields[nEnumCounter1]),UcalendarGetLimitType(eLimitType[nEnumCounter2]));
			nLimit = i18n_ucalendar_get_limit(g_hUcalender, eDateFields[nEnumCounter1], eLimitType[nEnumCounter2]);
			FPRINTF("[Line : %d][%s] i18n_ucalendar_get_limit return limit value = %d for DateField Value (%s) and Limit type (%s)\\n", __LINE__, API_NAMESPACE, nLimit, UcalenderDateFieldValue(eDateFields[nEnumCounter1]),UcalendarGetLimitType(eLimitType[nEnumCounter2]));
			
			nRetVal = get_last_result();
			PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_limit", BaseUtilsGetError(nRetVal));
		}
	}
	
	return 0;
}

//& type: auto
//& purpose: Gets the locale for calendar object
/**
* @testcase				ITc_i18n_ucalendar_get_locale_by_type_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Gets the locale for calendar object
* @apitarget			i18n_ucalendar_get_locale_by_type
* @apicovered			i18n_ucalendar_get_locale_by_type
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_get_locale_by_type or pre-condition APIs fail
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_get_locale_by_type
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_locale_by_type_p(void)
{	
	START_TEST;
	int nEnumCounter = 0, nRetVal = -1;
	
	i18n_ulocale_data_locale_type_e eLocaleType[] = {	I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE,
														I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE	};   
										
	int nEnumSize = sizeof(eLocaleType) / sizeof(eLocaleType[0]);
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for Locale type (%s)\\n", __LINE__, API_NAMESPACE, UcalendarGetLocaleType(eLocaleType[nEnumCounter]));
		const char *pszLocale = i18n_ucalendar_get_locale_by_type(g_hUcalender, eLocaleType[nEnumCounter]);
		CHECK_HANDLE(pszLocale, "i18n_ucalendar_get_locale_by_type");
		
		nRetVal = get_last_result();
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_locale_by_type", BaseUtilsGetError(nRetVal));
	}
	
	return 0;
}

//& type: auto
//& purpose: Gets the current timezone data version 
/**
* @testcase				ITc_i18n_ucalendar_get_tz_data_version_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Gets the current timezone data version 
* @apitarget			i18n_ucalendar_get_tz_data_version
* @apicovered			i18n_ucalendar_get_tz_data_version
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_get_tz_data_version
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_get_tz_data_version
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_tz_data_version_p(void)
{	
	START_TEST_PRINT;
	int nRetVal = -1;
	const char *pszVersion = NULL;
	
	pszVersion = i18n_ucalendar_get_tz_data_version();
	CHECK_HANDLE(pszVersion, "i18n_ucalendar_get_tz_data_version");
	
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_tz_data_version", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Gets the resource keyword value string designating the calendar type
/**
* @testcase				ITc_i18n_ucalendar_get_type_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Gets the resource keyword value string designating the calendar type
* @apitarget			i18n_ucalendar_get_type
* @apicovered			i18n_ucalendar_get_type
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_get_type
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_get_type or any pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_type_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	const char *pszKeyType = NULL;
	
	pszKeyType = i18n_ucalendar_get_type(g_hUcalender);
	CHECK_HANDLE(pszKeyType, "i18n_ucalendar_get_type");
	
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_type", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Gets an array of string values in a preferred order for a given key and locale
/**
* @testcase				ITc_i18n_ucalendar_get_keyword_values_for_locale_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Gets an array of string values in a preferred order for a given key and locale
* @apitarget			i18n_ucalendar_get_keyword_values_for_locale
* @apicovered			i18n_ucalendar_get_keyword_values_for_locale, i18n_ucalendar_get_type, i18n_ucalendar_get_available
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_get_keyword_values_for_locale
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_get_keyword_values_for_locale or any pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_keyword_values_for_locale_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	const char *pszKeyType = NULL, *pszLocale = NULL;
	int32_t nLocaleIndex = 1;
	i18n_ubool bCommonlyUsed = false;
	i18n_uenumeration_h hEnumeration = NULL;
	
	pszKeyType = i18n_ucalendar_get_type(g_hUcalender);
	CHECK_HANDLE(pszKeyType, "i18n_ucalendar_get_type");	
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_type", BaseUtilsGetError(nRetVal));

	pszLocale = i18n_ucalendar_get_available(nLocaleIndex);
	CHECK_HANDLE(pszLocale, "i18n_ucalendar_get_available");
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_available", BaseUtilsGetError(nRetVal));
	
    nRetVal = i18n_ucalendar_get_keyword_values_for_locale(pszKeyType, pszLocale, bCommonlyUsed, &hEnumeration);
	CHECK_HANDLE(hEnumeration, "i18n_ucalendar_get_keyword_values_for_locale");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_keyword_values_for_locale", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Gets the given day of the week is a weekday or a weekend day
/**
* @testcase				ITc_i18n_ucalendar_get_day_of_week_type_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Gets the given day of the week is a weekday or a weekend day
* @apitarget			i18n_ucalendar_get_day_of_week_type
* @apicovered			i18n_ucalendar_get_day_of_week_type
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_get_day_of_week_type or pre-condition APIs fail
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_get_day_of_week_type
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_day_of_week_type_p(void)
{	
	START_TEST;
	int nEnumCounter = 0, nRetVal = -1;
	i18n_ucalendar_weekday_type_e eWeekdayType;
	 
	i18n_ucalendar_days_of_week_e eDayOfWeek[] = {	I18N_UCALENDAR_SUNDAY,
													I18N_UCALENDAR_MONDAY,    
													I18N_UCALENDAR_TUESDAY,   
													I18N_UCALENDAR_WEDNESDAY, 
													I18N_UCALENDAR_THURSDAY,  
													I18N_UCALENDAR_FRIDAY,    
													I18N_UCALENDAR_SATURDAY };
	int nEnumSize = sizeof(eDayOfWeek) / sizeof(eDayOfWeek[0]);
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for Day (%s)\\n", __LINE__, API_NAMESPACE, UcalendarGetDaysOfWeek(eDayOfWeek[nEnumCounter]));
		nRetVal = i18n_ucalendar_get_day_of_week_type(g_hUcalender, eDayOfWeek[nEnumCounter], &eWeekdayType);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_day_of_week_type", BaseUtilsGetError(nRetVal));
		FPRINTF("[Line : %d][%s] Week day type : (%d)\\n", __LINE__, API_NAMESPACE, eWeekdayType);
	}
	return 0;
}

//& type: auto
//& purpose: Gets the time during the day at which the weekend begins or ends
/**
* @testcase				ITc_i18n_ucalendar_get_weekend_transition_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Gets the time during the day at which the weekend begins or ends
* @apitarget			i18n_ucalendar_get_weekend_transition
* @apicovered			i18n_ucalendar_get_weekend_transition
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_get_weekend_transition or pre-condition APIs fail
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_get_weekend_transition
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_weekend_transition_p(void)
{	
	START_TEST;
	int nEnumCounter = 0, nRetVal = -1;
	int32_t nMiliSec = -1;
	
	i18n_ucalendar_days_of_week_e eDayOfWeek[] = {	I18N_UCALENDAR_SATURDAY,
													I18N_UCALENDAR_SUNDAY};
	int nEnumSize = sizeof(eDayOfWeek) / sizeof(eDayOfWeek[0]);
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for Day (%s)\\n", __LINE__, API_NAMESPACE, UcalendarGetDaysOfWeek(eDayOfWeek[nEnumCounter]));
		nMiliSec = i18n_ucalendar_get_weekend_transition(g_hUcalender, eDayOfWeek[nEnumCounter]);
		CHECK_RETURN_VAL(nMiliSec, "i18n_ucalendar_get_weekend_transition");
		
		nRetVal = get_last_result();
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_weekend_transition", BaseUtilsGetError(nRetVal));
	}
	return 0;
}

//& type: auto
//& purpose: Gets if the given udate is in weekend
/**
* @testcase				ITc_i18n_ucalendar_is_weekend_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Gets if the given udate is in weekend
* @apitarget			i18n_ucalendar_is_weekend
* @apicovered			i18n_ucalendar_is_weekend
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_is_weekend
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_is_weekend or any pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_is_weekend_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	i18n_udate nUdate;
	i18n_ubool bIsWeekend = false;
	
    nRetVal = i18n_ucalendar_get_milliseconds(g_hUcalender, &nUdate);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_milliseconds", BaseUtilsGetError(nRetVal));
	
	bIsWeekend = i18n_ucalendar_is_weekend(g_hUcalender, nUdate);
	if(bIsWeekend != true && bIsWeekend != false)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ucalendar_is_weekend failed, bool return value is = %d \n", __LINE__, API_NAMESPACE, bIsWeekend);
		return 1;
	}
	
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_is_weekend", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Gets the difference between the target time and the time of calendar object
/**
* @testcase				ITc_i18n_ucalendar_get_field_difference_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Gets the difference between the target time and the time of calendar object
* @apitarget			i18n_ucalendar_get_field_difference
* @apicovered			i18n_ucalendar_get_field_difference
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_get_field_difference
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_get_field_difference or any pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_field_difference_p(void)
{	
	START_TEST;
	i18n_udate nUdateTarget;
	i18n_error_code_e eErrorCode = I18N_ERROR_NONE;
	int32_t nFieldDiff = -1;
	int nEnumCounter = 0;
	
	i18n_ucalendar_date_fields_e eDateFields[] = {	I18N_UCALENDAR_YEAR, 
													I18N_UCALENDAR_MONTH,
													I18N_UCALENDAR_WEEK_OF_YEAR,
													I18N_UCALENDAR_WEEK_OF_MONTH,
													I18N_UCALENDAR_DATE,
													I18N_UCALENDAR_DAY_OF_YEAR,
													I18N_UCALENDAR_DAY_OF_WEEK,
													I18N_UCALENDAR_DAY_OF_WEEK_IN_MONTH,
													I18N_UCALENDAR_AM_PM,                            
													I18N_UCALENDAR_HOUR,                             
													I18N_UCALENDAR_HOUR_OF_DAY,                      
													I18N_UCALENDAR_MINUTE,                           
													I18N_UCALENDAR_SECOND,                           
													I18N_UCALENDAR_MILLISECOND,                      
													I18N_UCALENDAR_ZONE_OFFSET,                      
													I18N_UCALENDAR_DST_OFFSET, 
                                                    I18N_UCALENDAR_ERA,                       
													I18N_UCALENDAR_YEAR_WOY,
													I18N_UCALENDAR_DOW_LOCAL,
													I18N_UCALENDAR_EXTENDED_YEAR,                    
													I18N_UCALENDAR_JULIAN_DAY,                       
													I18N_UCALENDAR_MILLISECONDS_IN_DAY,              
													I18N_UCALENDAR_IS_LEAP_MONTH,                    
													I18N_UCALENDAR_FIELD_COUNT,                      
													I18N_UCALENDAR_DAY_OF_MONTH };
	int nEnumSize = sizeof(eDateFields) / sizeof(eDateFields[0]);
	
	int nRetVal = i18n_ucalendar_get_now(&nUdateTarget);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_now", BaseUtilsGetError(nRetVal));
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for Datefield value (%s)\\n", __LINE__, API_NAMESPACE, UcalenderDateFieldValue(eDateFields[nEnumCounter]));
		nFieldDiff = i18n_ucalendar_get_field_difference(g_hUcalender, nUdateTarget, eDateFields[nEnumCounter], &eErrorCode);
		CHECK_RETURN_VAL(nFieldDiff, "i18n_ucalendar_get_field_difference");
		PRINT_RESULT(I18N_ERROR_NONE, eErrorCode,"i18n_ucalendar_get_field_difference", BaseUtilsGetError(nRetVal));
	}
	return 0;
}

//& type: auto
//& purpose: Gets the next/previous time zone transition relative
/**
* @testcase				ITc_i18n_ucalendar_get_timezone_transition_date_p
* @since_tizen 			2.3.1
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Gets the next/previous time zone transition relative
* @apitarget			i18n_ucalendar_get_timezone_transition_date
* @apicovered			i18n_ucalendar_get_timezone_transition_date
* @passcase				I18N_ERROR_NONE returned by i18n_ucalendar_get_timezone_transition_date
* @failcase				I18N_ERROR_NONE not returned by i18n_ucalendar_get_timezone_transition_date or any pre-condition API fails
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ucalendar_get_timezone_transition_date_p(void)
{	
	START_TEST;
	i18n_udate nUdateTransition = -1;
	int nEnumCounter = 0;
	i18n_ubool bIsWeekend = false;
	
	i18n_utimezone_transition_type_e eTransitionType[] = {	I18N_UCALENDAR_TZ_TRANSITION_NEXT,          
															I18N_UCALENDAR_TZ_TRANSITION_NEXT_INCLUSIVE,
															I18N_UCALENDAR_TZ_TRANSITION_PREVIOUS,      
															I18N_UCALENDAR_TZ_TRANSITION_PREVIOUS_INCLUSIVE };
	int nEnumSize = sizeof(eTransitionType) / sizeof(eTransitionType[0]);

	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		FPRINTF("[Line : %d][%s] Executing for Timezone transition type (%s)\\n", __LINE__, API_NAMESPACE, UcalendarGetTimezoneTransitionType(eTransitionType[nEnumCounter]));
		bIsWeekend = i18n_ucalendar_get_timezone_transition_date(g_hUcalender, eTransitionType[nEnumCounter], &nUdateTransition);
		if(bIsWeekend != true && bIsWeekend != false)
		{
			FPRINTF("\\n[Line : %d][%s] i18n_ucalendar_get_timezone_transition_date failed, bool return value is = %d \n", __LINE__, API_NAMESPACE, bIsWeekend);
			return 1;
		}
		
		int nRetVal = get_last_result();
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ucalendar_get_timezone_transition_date", BaseUtilsGetError(nRetVal));
		if(bIsWeekend == true)
		{
			CHECK_RETURN_VAL(nUdateTransition, "i18n_ucalendar_get_timezone_transition_date");
		}
	}
	return 0;
}

/** @} */
/** @} */
