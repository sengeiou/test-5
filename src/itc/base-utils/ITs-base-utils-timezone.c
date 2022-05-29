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

bool g_CallbackCalled = false;
static bool g_CallBackValue = true;

/**
* @function             TimeZoneIdCallBack
* @description          callback for timezone id
* @parameter            timezone_id : timezone_id, user_data : user data
* @return                       NA
*/
bool TimeZoneIdCallBack(const char *timezone_id, void *user_data)
{
        FPRINTF("[Line : %d][%s] Inside TimeZoneIdCallBack. timezone_id = %s\\n", __LINE__, API_NAMESPACE, timezone_id);
        g_CallBackValue = true;
        g_CallbackCalled = true;
        if(timezone_id == NULL)
        {
                g_CallBackValue = false;
        }
        return false;
}

//& set: BaseUtilsTimezone
/**
* @function 		ITs_base_utils_timezone_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_base_utils_timezone_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bBaseUtilsInitFlag = true;
	return;
}

/**
* @function 		ITs_base_utils_timezone_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_timezone_cleanup(void)
{
	g_bBaseUtilsInitFlag = false;

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}


//& type: auto
//& purpose: Returns the unknown time zone.
/**
* @testcase				ITc_i18n_timezone_create_unknown_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns the unknown time zone.
* @apitarget			i18n_timezone_create_unknown
* @apicovered			i18n_timezone_create_unknown, i18n_timezone_destroy
* @passcase				When i18n_timezone_create_unknown is successful
* @failcase				If target i18n_timezone_create_unknown API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_create_unknown_p(void)
{
	START_TEST;

	i18n_timezone_h nTimeZone = NULL;

	int nRetVal = i18n_timezone_create_unknown(&nTimeZone);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create_unknown", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(nTimeZone, "i18n_timezone_create");
	
	nRetVal = i18n_timezone_destroy(nTimeZone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Returns the GMT time zone.
/**
* @testcase				ITc_i18n_timezone_create_gmt_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- returns the GMT time zone.
* @apitarget			i18n_timezone_create_gmt
* @apicovered			i18n_timezone_create_gmt, i18n_timezone_destroy
* @passcase				When i18n_timezone_create_gmt is successful
* @failcase				If target i18n_timezone_create_gmt API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_create_gmt_p(void)
{
	START_TEST;

	i18n_timezone_h nTimeZone = NULL;

	int nRetVal = i18n_timezone_create_gmt(&nTimeZone);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create_gmt", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(nTimeZone, "i18n_timezone_create");
	
	nRetVal = i18n_timezone_destroy(nTimeZone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Create and destroy an i18n_timezone_h for the given timezone_id.
/**
* @testcase				ITc_i18n_timezone_create_destroy_p
* @since_tizen			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Create and destroy an i18n_timezone_h for the given timezone_id.
* @apitarget			i18n_timezone_create, i18n_timezone_destroy
* @apicovered			i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_create and i18n_timezone_destroy are successful
* @failcase				If target i18n_timezone_create or i18n_timezone_destroy API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_create_destroy_p(void)
{
	START_TEST;

	i18n_timezone_h nTimeZone = NULL;
	char szZoneId[] = "India/New_Delhi";

	int nRetVal = i18n_timezone_create(&nTimeZone, szZoneId);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(nTimeZone, "i18n_timezone_create");
	
	nRetVal = i18n_timezone_destroy(nTimeZone);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Returns the no of IDs in the equivalency group that include the given id.
/**
* @testcase				ITc_i18n_timezone_count_equivalent_ids_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns the no of IDs in the equivalency group that include the given id.
* @apitarget			i18n_timezone_count_equivalent_ids
* @apicovered			i18n_timezone_count_equivalent_ids
* @passcase				When i18n_timezone_count_equivalent_ids is successful
* @failcase				If target i18n_timezone_count_equivalent_ids API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_count_equivalent_ids_p(void)
{
	START_TEST;

	int nIdCount;
	char szZoneId[] = "India/New_Delhi";

	int nRetVal = i18n_timezone_count_equivalent_ids(szZoneId, &nIdCount);
	FPRINTF("[Line : %d][%s] i18n_timezone_count_equivalent_ids returns id count = %d\\n", __LINE__, API_NAMESPACE, nIdCount);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_count_equivalent_ids", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Returns the ID in equivalency group that include the given id.
/**
* @testcase				ITc_i18n_timezone_get_equivalent_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns the ID in equivalency group that include the given id.
* @apitarget			i18n_timezone_get_equivalent_id
* @apicovered			i18n_timezone_get_equivalent_id
* @passcase				When i18n_timezone_get_equivalent_id is successful
* @failcase				If target i18n_timezone_get_equivalent_id API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_get_equivalent_id_p(void)
{
	START_TEST;

	int nIdCount;
	int nIndex = 0;
	char *pEquivalentId = NULL;
	char szZoneId[] = "India/New_Delhi";

	int nRetVal = i18n_timezone_count_equivalent_ids(szZoneId, &nIdCount);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_count_equivalent_ids", BaseUtilsGetError(nRetVal));

	if ( nIdCount == 0 )
	{
		FPRINTF("[Line : %d][%s] Given ID is not a system time zone\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	nIndex = nIdCount-1;
	nRetVal = i18n_timezone_get_equivalent_id(szZoneId, nIndex, &pEquivalentId);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_get_equivalent_id", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Create a new copy of the default i18n_timezone_h for this host.
/**
* @testcase				ITc_i18n_timezone_create_default_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create a new copy of the default i18n_timezone_h for this host.
* @apitarget			i18n_timezone_create_default
* @apicovered			i18n_timezone_create_default, i18n_timezone_destroy
* @passcase				When i18n_timezone_create_default is successful
* @failcase				If target i18n_timezone_create_default API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_create_default_p(void)
{
	START_TEST;

	i18n_timezone_h timezone; 

	int nRetVal = i18n_timezone_create_default(&timezone);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create_default", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Set the default time zone to be the specified time zone.
/**
* @testcase				ITc_i18n_timezone_set_default_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				-Set the default time zone to be the specified time zone.
* @apitarget			i18n_timezone_set_default
* @apicovered			i18n_timezone_set_default, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_set_default is successful
* @failcase				If target i18n_timezone_set_default API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_set_default_p(void)
{
	START_TEST;

	i18n_timezone_h timezone = NULL; 
	int nRetVal = i18n_timezone_create(&timezone, "India/New_Delhi");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	nRetVal = i18n_timezone_set_default(timezone);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_set_default", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));

	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose:Returns the timezone data version currently used by I18N. 
/**
* @testcase				ITc_i18n_timezone_get_tzdata_version_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns the timezone data version currently used by I18N. 
* @apitarget			i18n_timezone_get_tzdata_version
* @apicovered			i18n_timezone_get_tzdata_version
* @passcase				When i18n_timezone_get_tzdata_version is successful
* @failcase				If target i18n_timezone_get_tzdata_version API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_get_tzdata_version_p(void)
{
	START_TEST;

	const char *pRetVal = i18n_timezone_get_tzdata_version();
	if ( pRetVal == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_timezone_get_tzdata_version failed, returns : %s\n", __LINE__, API_NAMESPACE,pRetVal);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Get the region code associated with the given system time zone id.
/**
* @testcase				ITc_i18n_timezone_get_region_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Get the region code associated with the given system time zone id.
* @apitarget			i18n_timezone_get_region
* @apicovered			i18n_timezone_get_region
* @passcase				When i18n_timezone_get_region is successful
* @failcase				If target i18n_timezone_get_region API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_get_region_p(void)
{
	START_TEST;

	const char szTimeZoneId[] = "Europe/London"/*"UTC+05:30"*/;
	char szRegion[BUFFER] = {'\0'};
	int32_t region_len = -1;
	int32_t region_capacity = BUFFER;

	int nRetVal = i18n_timezone_get_region(szTimeZoneId, szRegion, &region_len, region_capacity);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_get_region", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(szRegion, "i18n_timezone_get_region");
	CHECK_RETURN_VAL(region_len, "i18n_timezone_get_region");

	return 0;
}


//& type: auto
//& purpose: Returns the timezone raw and GMT offset for the given moment in time.
/**
* @testcase				ITc_i18n_timezone_get_offset_with_date_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns the timezone raw and GMT offset for the given moment in time.
* @apitarget			i18n_timezone_get_offset_with_date
* @apicovered			i18n_timezone_get_offset_with_date, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_get_offset_with_date is successful
* @failcase				If target i18n_timezone_get_offset_with_date API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_get_offset_with_date_p(void)
{
	START_TEST;

	i18n_timezone_h timezone = NULL; 
	i18n_udate date;
	i18n_ubool local = true;
	int32_t raw_offset = -1;
	int32_t dst_offset = -1;

	int nRetVal = i18n_timezone_create(&timezone, "India/New_Delhi");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	nRetVal = i18n_ucalendar_get_now(&date);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_ucalendar_get_now", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));

	nRetVal = i18n_timezone_get_offset_with_date(timezone, date, local, &raw_offset, &dst_offset);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_get_offset_with_date", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));
	CHECK_RETURN_VAL(raw_offset, "i18n_timezone_get_offset_with_date");
	CHECK_RETURN_VAL(dst_offset, "i18n_timezone_get_offset_with_date");
	
	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Get and set the region code associated with the given system time zone id.
/**
* @testcase				ITc_i18n_timezone_set_get_raw_offset_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Get and set the region code associated with the given system time zone id.
* @apitarget			i18n_timezone_set_raw_offset, i18n_timezone_get_raw_offset
* @apicovered			i18n_timezone_set_raw_offset, i18n_timezone_get_raw_offset, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_set_raw_offset and i18n_timezone_get_raw_offset is successful
* @failcase				If target i18n_timezone_set_raw_offset or i18n_timezone_get_raw_offset API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_set_get_raw_offset_p(void)
{
	START_TEST;

	i18n_timezone_h timezone = NULL;
	int32_t offset_milliseconds = 10000;

	int nRetVal = i18n_timezone_create(&timezone, "India/New_Delhi");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	int32_t nGetVal;
	nRetVal = i18n_timezone_set_raw_offset(timezone, offset_milliseconds);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_set_raw_offset", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));

	nRetVal = i18n_timezone_get_raw_offset(timezone, &nGetVal);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_get_raw_offset", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));

	if ( nGetVal != offset_milliseconds )
	{
		FPRINTF("[Line : %d][%s] Set and Get value didn't match\n", __LINE__, API_NAMESPACE);
		nRetVal = i18n_timezone_destroy(timezone);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
		return 1;
	}
	
	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}


//& type: auto
//& purpose: Get and set the i18n_timezone_h ID to the specified value.
/**
* @testcase				ITc_i18n_timezone_set_get_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Get and set the i18n_timezone_h ID to the specified value.
* @apitarget			i18n_timezone_set_id, i18n_timezone_get_id
* @apicovered			i18n_timezone_set_id, i18n_timezone_get_id, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_set_id and i18n_timezone_get_id is successful
* @failcase				If target i18n_timezone_set_id or i18n_timezone_get_id API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_set_get_id_p(void)
{
	START_TEST;

	i18n_timezone_h timezone = NULL;
	int nRetVal = i18n_timezone_create(&timezone, "India/New_Delhi");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	char szTimeZoneid[] = "India/Kolkata";
	char *pGetTimeZoneId;

	nRetVal = i18n_timezone_set_id(timezone, szTimeZoneid);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_set_id", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));

	nRetVal = i18n_timezone_get_id(timezone, &pGetTimeZoneId);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_get_id", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));

	if ( strcmp(szTimeZoneid, pGetTimeZoneId) != 0 )
	{
		FPRINTF("[Line : %d][%s] Set and Get value didn't match\n", __LINE__, API_NAMESPACE);
		nRetVal = i18n_timezone_destroy(timezone);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
		return 1;
	}
	
	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Returns a name of this time zone suitable for presentation to the user in the default locale.
/**
* @testcase				ITc_i18n_timezone_get_display_name_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns a name of this time zone suitable for presentation to the user in the default locale.
* @apitarget			i18n_timezone_get_display_name
* @apicovered			i18n_timezone_get_display_name, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_get_display_name is successful
* @failcase				If target i18n_timezone_get_display_name API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_get_display_name_p(void)
{
	START_TEST;

	i18n_timezone_h timezone = NULL;
	char *pDisplayName= NULL;

	int nRetVal = i18n_timezone_create(&timezone, "India/New_Delhi");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	nRetVal = i18n_timezone_get_display_name(timezone, &pDisplayName);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_get_display_name", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));
	CHECK_HANDLE(pDisplayName, "i18n_timezone_get_display_name");

	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Returns a name of this time zone suitable for presentation to the user in the default locale.
/**
* @testcase				ITc_i18n_timezone_get_display_name_with_locale_id_p
* @since_tizen 			5.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Returns a name of this time zone suitable for presentation to the user in the default locale.
* @apitarget			i18n_timezone_get_display_name_with_locale_id
* @apicovered			i18n_timezone_get_display_name_with_locale_id, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_get_display_name_with_locale_id is successful
* @failcase				If target i18n_timezone_get_display_name_with_locale_id API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_get_display_name_with_locale_id_p(void)
{
	START_TEST;

	i18n_timezone_h hTimezone = NULL;
	const char *pszLocalId = "en_US";
	char *pDisplayName = NULL;
	int nTimeEnd = 15;
	char szTimezoneId[10];
	int nGmt = -12;

	for(; nGmt < nTimeEnd; nGmt++)
	{
		snprintf(szTimezoneId, 10, "GMT%d:00", nGmt);
		int nRetVal = i18n_timezone_create(&hTimezone, szTimezoneId);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
		CHECK_HANDLE(hTimezone, "i18n_timezone_create");

		nRetVal = i18n_timezone_get_display_name_with_locale_id(hTimezone, pszLocalId, &pDisplayName);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_get_display_name_with_locale_id", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(hTimezone));
		CHECK_HANDLE(pDisplayName, "i18n_timezone_get_display_name_with_locale");
		FREE_MEMORY(pDisplayName);

		nRetVal = i18n_timezone_destroy(hTimezone);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));

	}
	return 0;
}

//& type: auto
//& purpose: Returns a name of this time zone suitable for presentation to the user in default locale.
/**
* @testcase				ITc_i18n_timezone_get_display_name_with_type_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns a name of this time zone suitable for presentation to the user in default locale.
* @apitarget			i18n_timezone_get_display_name_with_type
* @apicovered			i18n_timezone_get_display_name_with_type, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_get_display_name_with_type is successful
* @failcase				If target i18n_timezone_get_display_name_with_type API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_get_display_name_with_type_p(void)
{
	START_TEST;

	i18n_timezone_h timezone = NULL;
	i18n_ubool daylight = true;
	i18n_timezone_display_type_e style = I18N_TIMEZONE_DISPLAY_TYPE_LONG;
	char *pDisplayName = NULL;

	int nRetVal = i18n_timezone_create(&timezone, "India/New_Delhi");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	nRetVal = i18n_timezone_get_display_name_with_type(timezone, daylight, style, &pDisplayName);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_get_display_name_with_type", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));
	CHECK_HANDLE(pDisplayName, "i18n_timezone_get_display_name_with_type");
	
	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Returns a name of this time zone suitable for presentation to the user in the default locale. 
/**
* @testcase				ITc_i18n_timezone_get_display_name_with_type_locale_id_p
* @since_tizen 			5.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Returns a name of this time zone suitable for presentation to the user in the default locale.
* @apitarget			i18n_timezone_get_display_name_with_type_locale_id
* @apicovered			i18n_timezone_get_display_name_with_type_locale_id, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_get_display_name_with_type_locale_id is successful
* @failcase				If target i18n_timezone_get_display_name_with_type_locale_id API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_get_display_name_with_type_locale_id_p(void)
{
	START_TEST;

	i18n_timezone_h timezone = NULL;
	i18n_ubool daylight = true;
	i18n_timezone_display_type_e style = I18N_TIMEZONE_DISPLAY_TYPE_LONG;
	const char *pszLocalId = "en_US";
	char *pDisplayName = NULL;

	int nRetVal = i18n_timezone_create_default(&timezone);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	nRetVal = i18n_timezone_get_display_name_with_type_locale_id(timezone, daylight, style,pszLocalId, &pDisplayName);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_get_display_name_with_type_locale_id", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));
	CHECK_HANDLE(pDisplayName, "i18n_timezone_get_display_name_with_type_locale_id");
	FREE_MEMORY(pDisplayName);
	
	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Queries if the given date is in daylight saving time in this time zone.
/**
* @testcase				ITc_i18n_timezone_use_daylight_time_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Queries if the given date is in daylight saving time in this time zone.
* @apitarget			i18n_timezone_use_daylight_time
* @apicovered			i18n_timezone_use_daylight_time, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_use_daylight_time is successful
* @failcase				If target i18n_timezone_use_daylight_time API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_use_daylight_time_p(void)
{
	START_TEST;

	i18n_timezone_h timezone = NULL;
	i18n_ubool daylight_time;
	int nRetVal = i18n_timezone_create(&timezone, "India/New_Delhi");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	nRetVal = i18n_timezone_use_daylight_time(timezone, &daylight_time);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_use_daylight_time", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));
	if(daylight_time != true && daylight_time != false)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_timezone_use_daylight_time failed, bool return value is = %d \n", __LINE__, API_NAMESPACE, daylight_time);
		return 1;
	}
	
	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}



#ifdef WEARABLE	//Starts WEARABLE
#if 0
//& type: auto
//& purpose: Queries if this time zone uses daylight saving time. 
/**
* @testcase				ITc_i18n_timezone_in_daylight_time_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Queries if this time zone uses daylight saving time.
* @apitarget			i18n_timezone_in_daylight_time
* @apicovered			i18n_timezone_in_daylight_time, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_in_daylight_time is successful
* @failcase				If target i18n_timezone_in_daylight_time API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
//int ITc_i18n_timezone_in_daylight_time_p(void)
{
	START_TEST;
  //i18n_timezone_in_daylight_time -- API not found in src 
	i18n_timezone_h timezone = NULL;
	i18n_udate date;
	i18n_ubool daylight_time;
	int nRetVal = i18n_timezone_create(&timezone, "India/New_Delhi");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	i18n_ucalendar_get_now(&date);
	nRetVal = i18n_timezone_in_daylight_time(timezone, date, &daylight_time);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_in_daylight_time", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));
	if(daylight_time != true && daylight_time != false)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_timezone_in_daylight_time failed, bool return value is = %d \n", __LINE__, API_NAMESPACE, daylight_time);
		return 1;
	}
	
	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}
#endif
#endif  //WEARABLE	//End WEARABLE

//& type: auto
//& purpose: Returns true if this zone has the same rule and offset as another zone.
/**
* @testcase				ITc_i18n_timezone_has_same_rule_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns true if this zone has the same rule and offset as another zone.
* @apitarget			i18n_timezone_has_same_rule
* @apicovered			i18n_timezone_has_same_rule, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_has_same_rule is successful
* @failcase				If target i18n_timezone_has_same_rule API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_has_same_rule_p(void)
{
	START_TEST;

	i18n_timezone_h timezone = NULL;
	i18n_timezone_h other = NULL;
	i18n_ubool same_rule;

	int nRetVal = i18n_timezone_create(&timezone, "India/New_Delhi");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	nRetVal = i18n_timezone_create(&other, "India/Kolkata");
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));

	nRetVal = i18n_timezone_has_same_rule(timezone, other, &same_rule);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_has_same_rule", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(other);i18n_timezone_destroy(timezone));
	if(same_rule != true && same_rule != false)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_timezone_has_same_rule failed, bool return value is = %d \n", __LINE__, API_NAMESPACE, same_rule);
		return 1;
	}
	
	nRetVal = i18n_timezone_destroy(other);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}


//& type: auto
//& purpose: Clone i18n_timezone_h polymorphically.
/**
* @testcase				ITc_i18n_timezone_clone_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Clone i18n_timezone_h polymorphically.
* @apitarget			i18n_timezone_clone
* @apicovered			i18n_timezone_clone, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_clone is successful
* @failcase				If target i18n_timezone_clone API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_clone_p(void)
{
	START_TEST;

	i18n_timezone_h timezone = NULL;
	i18n_timezone_h clone;

	int nRetVal = i18n_timezone_create(&timezone, "India/New_Delhi");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	nRetVal = i18n_timezone_clone(timezone, &clone);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_clone", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));

	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_timezone_destroy(clone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Returns the amount of time to be added to local standard time to get local wall clock time.
/**
* @testcase				ITc_i18n_timezone_get_dst_savings_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns the amount of time to be added to local standard time to get local wall clock time.
* @apitarget			i18n_timezone_get_dst_savings
* @apicovered			i18n_timezone_get_dst_savings, i18n_timezone_create, i18n_timezone_destroy
* @passcase				When i18n_timezone_get_dst_savings is successful
* @failcase				If target i18n_timezone_get_dst_savings API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_get_dst_savings_p(void)
{
	START_TEST;

	i18n_timezone_h timezone = NULL;
	int32_t dst_savings = -1;

	int nRetVal = i18n_timezone_create(&timezone, "India/New_Delhi");
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(timezone, "i18n_timezone_create");
	
	nRetVal = i18n_timezone_get_dst_savings(timezone, &dst_savings);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_timezone_get_dst_savings", BaseUtilsGetError(nRetVal), i18n_timezone_destroy(timezone));
	CHECK_RETURN_VAL(dst_savings, "i18n_timezone_get_dst_savings");
	
	nRetVal = i18n_timezone_destroy(timezone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_timezone_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose:Returns an enumeration over system time zone ids with the given filter condition.
/**
* @testcase				ITc_i18n_timezone_foreach_timezone_id_by_region_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns an enumeration over system time zone ids with the given filter condition.
* @apitarget			i18n_timezone_foreach_timezone_id_by_region
* @apicovered			i18n_timezone_foreach_timezone_id_by_region
* @passcase				When i18n_timezone_foreach_timezone_id_by_region is successful
* @failcase				If target i18n_timezone_foreach_timezone_id_by_region API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_foreach_timezone_id_by_region_p(void)
{
	START_TEST;

	i18n_system_timezone_type_e timezone_type[] = {I18N_UCALENDAR_ZONE_TYPE_ANY, 
		I18N_UCALENDAR_ZONE_TYPE_CANONICAL,
		I18N_UCALENDAR_ZONE_TYPE_CANONICAL_LOCATION};
	char *pRegion = NULL;
	int32_t *raw_offset = NULL;
	int nEnumSize = sizeof(timezone_type) / sizeof(timezone_type[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		g_CallbackCalled = false;
		int nRetVal = i18n_timezone_foreach_timezone_id_by_region(timezone_type[nEnumCounter], pRegion, raw_offset, TimeZoneIdCallBack, NULL );
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_foreach_timezone_id_by_region", BaseUtilsGetError(nRetVal));
		if ( !g_CallbackCalled )
		{
			FPRINTF("[Line : %d][%s] TimeZoneIdCallBack function not called\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		if(!g_CallBackValue)
		{
			FPRINTF("[Line : %d][%s] Callback input values are NULL \n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Returns an enumeration over all recognized time zone IDs.
/**
* @testcase				ITc_i18n_timezone_foreach_timezone_id_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns an enumeration over all recognized time zone IDs.
* @apitarget			i18n_timezone_foreach_timezone_id
* @apicovered			i18n_timezone_foreach_timezone_id
* @passcase				When i18n_timezone_foreach_timezone_id is successful
* @failcase				If target i18n_timezone_foreach_timezone_id API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_foreach_timezone_id_p(void)
{
	START_TEST;

	g_CallbackCalled = false;
	int nRetVal = i18n_timezone_foreach_timezone_id(TimeZoneIdCallBack, NULL );
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_foreach_timezone_id", BaseUtilsGetError(nRetVal));
	if ( !g_CallbackCalled )
	{
		FPRINTF("[Line : %d][%s] TimeZoneIdCallBack function not called\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(!g_CallBackValue)
	{
		FPRINTF("[Line : %d][%s] Callback input values are NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
		
	return 0;
}

//& type: auto
//& purpose: Returns an enumeration over time zone IDs with a given raw offset from GMT.
/**
* @testcase				ITc_i18n_timezone_foreach_timezone_id_with_offset_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns an enumeration over time zone IDs with a given raw offset from GMT.
* @apitarget			i18n_timezone_foreach_timezone_id_with_offset
* @apicovered			i18n_timezone_foreach_timezone_id_with_offset
* @passcase				When i18n_timezone_foreach_timezone_id_with_offset is successful
* @failcase				If target i18n_timezone_foreach_timezone_id_with_offset API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_foreach_timezone_id_with_offset_p(void)
{
	START_TEST;

	int32_t raw_offset = 3600000;
	g_CallbackCalled = false;

	int nRetVal = i18n_timezone_foreach_timezone_id_with_offset(raw_offset, TimeZoneIdCallBack, NULL );
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_foreach_timezone_id_with_offset", BaseUtilsGetError(nRetVal));
	if ( !g_CallbackCalled )
	{
		FPRINTF("[Line : %d][%s] TimeZoneIdCallBack function not called\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(!g_CallBackValue)
	{
		FPRINTF("[Line : %d][%s] Callback input values are NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: Returns an enumeration over time zone IDs associated with the given country.
/**
* @testcase				ITc_i18n_timezone_foreach_timezone_id_by_country_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				returns an enumeration over time zone IDs associated with the given country.
* @apitarget			i18n_timezone_foreach_timezone_id_by_country
* @apicovered			i18n_timezone_foreach_timezone_id_by_country
* @passcase				When i18n_timezone_foreach_timezone_id_by_country is successful
* @failcase				If target i18n_timezone_foreach_timezone_id_by_country API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_timezone_foreach_timezone_id_by_country_p(void)
{
	START_TEST;

	char *pCountry = NULL;

	g_CallbackCalled = false;
	int nRetVal = i18n_timezone_foreach_timezone_id_by_country(pCountry, TimeZoneIdCallBack, NULL );
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_foreach_timezone_id_by_country", BaseUtilsGetError(nRetVal));
	if ( !g_CallbackCalled )
	{
		FPRINTF("[Line : %d][%s] TimeZoneIdCallBack function not called\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(!g_CallBackValue)
	{
		FPRINTF("[Line : %d][%s] Callback input values are NULL \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: Gets the time zone from the current host system configuration.
/**
* @testcase				ITc_i18n_timezone_detect_host_timezone_p
* @since_tizen 			3.0
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario				Gets the time zone from the current host system configuration
* @apitarget			i18n_timezone_detect_host_timezone
* @apicovered			i18n_timezone_detect_host_timezone
* @passcase				When i18n_timezone_detect_host_timezone is successful
* @failcase				If target i18n_timezone_detect_host_timezone API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_timezone_detect_host_timezone_p(void)
{
	START_TEST;

	i18n_timezone_h nTimeZone = NULL;

	int nRetVal = i18n_timezone_detect_host_timezone( &nTimeZone );
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_timezone_detect_host_timezone", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(nTimeZone, "i18n_timezone_detect_host_timezone");

	return 0;
}

/** @} */
/** @} */

