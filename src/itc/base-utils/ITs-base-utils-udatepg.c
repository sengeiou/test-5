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
i18n_udatepg_h dtpg = NULL;

/**
* @function 		ITs_base_utils_udatepg_startup
* @description	 	Called before each test. Creates a i18n_udatepg_h handle and get default locale
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_udatepg_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_base_utils_udatepg_startup\\n", __LINE__, API_NAMESPACE);
#endif
	g_bBaseUtilsInitFlag = false;
	int nRetVal = -1;
	g_pszDefaultLocale = I18N_ULOCALE_US;
	
	nRetVal = i18n_udatepg_create(g_pszDefaultLocale, &dtpg);
	if (nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_udatepg_create failed in STARTUP, error returned = %s \n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
		g_bBaseUtilsInitFlag = false;
		return;
	}
	g_bBaseUtilsInitFlag = true;
	return;
}

/**
* @function 		ITs_base_utils_udatepg_cleanup
* @description	 	Called after each test. Destroy the created i18n_udatepg_h handle
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_udatepg_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_base_utils_udatepg_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	i18n_udatepg_destroy(dtpg);
	g_bBaseUtilsInitFlag = false;	
	return;
}

//& type: auto
//& purpose: Opens and closes a generator according to a given locale.
/**
* @testcase				ITc_i18n_udatepg_create_destroy_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Opens a generator according to a given locale.
* 						Closes a given generator
* @apitarget			i18n_udatepg_create, i18n_udatepg_destroy	
* @apicovered			i18n_udatepg_create, i18n_udatepg_destroy	
* @passcase				When i18n_udatepg_create, i18n_udatepg_destroy are successful.
* @failcase				If target i18n_udatepg_create or i18n_udatepg_destroy fails or any precondition and postcondition api fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_create_destroy_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	i18n_udatepg_h udatepgHandle = NULL;
	
	nRetVal = i18n_udatepg_create(g_pszDefaultLocale, &udatepgHandle);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udatepg_create", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_udatepg_destroy(udatepgHandle);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udatepg_create", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Gets the best pattern matching the input skeleton.
/**
* @testcase				ITc_i18n_udatepg_get_best_pattern_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Opens a generator according to a given locale.
* 						Gets the best pattern matching the input skeleton.
*						Closes a given generator
* @apitarget			i18n_udatepg_get_best_pattern	
* @apicovered			i18n_udatepg_create, i18n_udatepg_get_best_pattern, i18n_udatepg_destroy
* @passcase				When i18n_udatepg_create, i18n_udatepg_get_best_pattern are successful.
* @failcase				If target i18n_udatepg_create or i18n_udatepg_get_best_pattern fails or any precondition and postcondition api fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_get_best_pattern_p(void)
{	
	START_TEST;
	i18n_udatepg_h udatepgHandle = NULL;
	int nRetVal = -1;
	
	nRetVal = i18n_udatepg_create(g_pszDefaultLocale, &udatepgHandle);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udatepg_create", BaseUtilsGetError(nRetVal));
	
	int nCustomFormatLength = 0;
    i18n_uchar ucharCustomFormat[I18N_DATEPG_PATTERN_CAPACITY];
	i18n_uchar *pRet  = NULL;
	
    pRet = i18n_ustring_copy_ua(ucharCustomFormat, (char *)I18N_DATE_TIME_CUSTOM_FORMAT);
	nCustomFormatLength = i18n_ustring_get_length(ucharCustomFormat);
	if (pRet == NULL || nCustomFormatLength <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed \n", __LINE__, API_NAMESPACE);
		i18n_udatepg_destroy(udatepgHandle);		
		return 1;
	}	

	i18n_uchar bestPattern[I18N_DATEPG_PATTERN_CAPACITY] = { 0, };   
	int nBestPatternCapacity = (int)(sizeof(bestPattern)/sizeof(bestPattern[0]));		
	int nBestPatternLength = 0;	
	
	nRetVal = i18n_udatepg_get_best_pattern(udatepgHandle, ucharCustomFormat, nCustomFormatLength, bestPattern, nBestPatternCapacity, &nBestPatternLength);       
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_udatepg_get_best_pattern", BaseUtilsGetError(nRetVal));
	
	i18n_udatepg_destroy(udatepgHandle);
	
	return 0;
}


//& type: auto
//& purpose: Set/Gets the decimal value used in formatting fractions of seconds.
/**
* @testcase				ITc_i18n_udatepg_set_get_decimal_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Set the decimal value used in formatting fractions of seconds\n.
* 						Gets the decimal value used in formatting fractions of seconds\n.
*						Match set value with get value
* @apitarget			i18n_udatepg_set_decimal, i18n_udatepg_get_decimal
* @apicovered			i18n_udatepg_set_decimal, i18n_udatepg_get_decimal
* @passcase				When i18n_udatepg_set_decimal, i18n_udatepg_get_decimal are successful
* @failcase				When i18n_udatepg_set_decimal or i18n_udatepg_get_decimal failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_set_get_decimal_p(void)
{
	START_TEST;
	
	int nSetLength = 0;
	i18n_uchar ucharCustomFormat[I18N_DATEPG_PATTERN_CAPACITY];
	const i18n_uchar *pRet = i18n_ustring_copy_ua(ucharCustomFormat, (char *)I18N_DATE_TIME_CUSTOM_FORMAT);
	nSetLength = i18n_ustring_get_length(ucharCustomFormat);
	int nRetVal = -1;
	if ( pRet == NULL || nSetLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua failed\\n", __LINE__, API_NAMESPACE);
		
		return 1;
	}

	nRetVal = i18n_udatepg_set_decimal(dtpg, ucharCustomFormat, nSetLength);       
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_set_decimal", BaseUtilsGetError(nRetVal));

	int nGetLength;
	pRet = i18n_udatepg_get_decimal(dtpg, &nGetLength);       
	if(pRet == NULL)
	{
		FPRINTF("[Line : %d][%s] i18n_udatepg_get_decimal failed, Returned value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	if(nGetLength != nSetLength)
	{
		FPRINTF("[Line : %d][%s] Set/Get Decimal Value mismatched\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Set/Gets the date time format in a message format pattern used to compose date and time patterns.
/**
* @testcase				ITc_i18n_udatepg_set_get_date_time_format_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Set the date time format in a message format\n
* 						Gets the date time format length in a message format\n
*						Match set length value with get length value
* @apitarget			i18n_udatepg_set_date_time_format, i18n_udatepg_get_date_time_format
* @apicovered			i18n_udatepg_set_date_time_format, i18n_udatepg_get_date_time_format
* @passcase				When i18n_udatepg_set_date_time_format, i18n_udatepg_get_date_time_format are successful
* @failcase				When i18n_udatepg_set_date_time_format or i18n_udatepg_get_date_time_format failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_set_get_date_time_format_p(void)
{
	START_TEST;

	int nSetLength = 0;
	i18n_uchar ucharDateTimeFormat[I18N_DATEPG_PATTERN_CAPACITY];
	const i18n_uchar *pRet = i18n_ustring_copy_ua(ucharDateTimeFormat, (char *)I18N_DATE_TIME_CUSTOM_FORMAT);
	nSetLength = i18n_ustring_get_length(ucharDateTimeFormat);
	int nRetVal = -1;
	if ( pRet == NULL || nSetLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = i18n_udatepg_set_date_time_format(dtpg, ucharDateTimeFormat, nSetLength);       
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_set_date_time_format", BaseUtilsGetError(nRetVal));

	int nGetLength;
	pRet = i18n_udatepg_get_date_time_format(dtpg, &nGetLength);       
	if(pRet == NULL)
	{
		FPRINTF("[Line : %d][%s] i18n_udatepg_get_date_time_format failed, Returned value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	if(nGetLength != nSetLength)
	{
		FPRINTF("[Line : %d][%s] Set/Get date time format length value mismatched\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Set/Gets the name of field.
/**
* @testcase				ITc_i18n_udatepg_set_get_append_item_name_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Set the name of field\n
* 						Gets the name of field\n
*						Match set filed length value with get filed length value
* @apitarget			i18n_udatepg_set_append_item_name, i18n_udatepg_get_append_item_name
* @apicovered			i18n_udatepg_set_append_item_name, i18n_udatepg_get_append_item_name
* @passcase				When i18n_udatepg_set_append_item_name, i18n_udatepg_get_append_item_name are successful
* @failcase				When i18n_udatepg_set_append_item_name or i18n_udatepg_get_append_item_name failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_set_get_append_item_name_p(void)
{
	START_TEST;

	int nSetFieldLength = 0;
	i18n_uchar ucharFieldName[I18N_DATEPG_PATTERN_CAPACITY];
	const i18n_uchar *pRet = i18n_ustring_copy_ua(ucharFieldName, (char *)I18N_DATE_TIME_CUSTOM_FORMAT);
	nSetFieldLength = i18n_ustring_get_length(ucharFieldName);
	int nRetVal = -1;
	int nSetLength = strlen(I18N_DATE_TIME_CUSTOM_FORMAT);
	if ( pRet == NULL || nSetFieldLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	} 
	i18n_udatepg_date_time_pattern_field_e eDateTimePatternField[] = {I18N_UDATEPG_ERA_FIELD,                  
																		I18N_UDATEPG_YEAR_FIELD,                
																		I18N_UDATEPG_QUARTER_FIELD,             
																		I18N_UDATEPG_MONTH_FIELD,               
																		I18N_UDATEPG_WEEK_OF_YEAR_FIELD,        
																		I18N_UDATEPG_WEEK_OF_MONTH_FIELD,       
																		I18N_UDATEPG_WEEKDAY_FIELD,             
																		I18N_UDATEPG_DAY_OF_YEAR_FIELD,         
																		I18N_UDATEPG_DAY_OF_WEEK_IN_MONTH_FIELD,
																		I18N_UDATEPG_DAY_FIELD,                 
																		I18N_UDATEPG_DAYPERIOD_FIELD,           
																		I18N_UDATEPG_HOUR_FIELD,                
																		I18N_UDATEPG_MINUTE_FIELD,              
																		I18N_UDATEPG_SECOND_FIELD,              
																		I18N_UDATEPG_FRACTIONAL_SECOND_FIELD,   
																		I18N_UDATEPG_ZONE_FIELD    
																	};
	int nPatternFieldSize = sizeof(eDateTimePatternField)/sizeof(eDateTimePatternField[0]);
	int nIndex = 0;		
	for(nIndex = 0; nIndex < nPatternFieldSize; nIndex++)
	{
		nRetVal = i18n_udatepg_set_append_item_name(dtpg, eDateTimePatternField[nIndex], ucharFieldName, nSetLength);       
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] i18n_udatepg_set_append_item_name failed for %s, Returned value is = %s\\n", __LINE__, API_NAMESPACE, UdatepgGetDateTimePatternField(eDateTimePatternField[nIndex]), BaseUtilsGetError(nRetVal));
			return 1;
		}
	
		int nGetLength;
		pRet = i18n_udatepg_get_append_item_name(dtpg, eDateTimePatternField[nIndex], &nGetLength); 
		if(pRet == NULL)
		{
			FPRINTF("[Line : %d][%s] i18n_udatepg_get_append_item_name failed for %s, Returned value is NULL\\n", __LINE__, API_NAMESPACE, UdatepgGetDateTimePatternField(eDateTimePatternField[nIndex]));
			return 1;
		}
		
		if(nGetLength != nSetLength)
		{
			FPRINTF("[Line : %d][%s] Set/Get field length mismatched\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}


//& type: auto
//& purpose: Set a pattern used to append a field and then Get the appended pattern length.
/**
* @testcase				ITc_i18n_udatepg_set_get_append_item_format_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Set a pattern used to append a field\n
* 						Gets the appended pattern length\n
*						Match set pattern length value with get pattern length value
* @apitarget			i18n_udatepg_set_append_item_format, i18n_udatepg_get_append_item_format
* @apicovered			i18n_udatepg_set_append_item_format, i18n_udatepg_get_append_item_format
* @passcase				When i18n_udatepg_set_append_item_format, i18n_udatepg_get_append_item_format are successful
* @failcase				When i18n_udatepg_set_append_item_format or i18n_udatepg_get_append_item_format failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_set_get_append_item_format_p(void)
{
	START_TEST;
	
	int nSetFieldLength = 0;
	i18n_uchar ucharFieldName[I18N_DATEPG_PATTERN_CAPACITY];
	const i18n_uchar *pRet = i18n_ustring_copy_ua(ucharFieldName, (char *)I18N_DATE_TIME_CUSTOM_FORMAT);
	nSetFieldLength = i18n_ustring_get_length(ucharFieldName);
	int nRetVal = -1;
	if ( pRet == NULL || nSetFieldLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_ustring_copy_ua failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
    int32_t nSetLength = strlen(I18N_DATE_TIME_CUSTOM_FORMAT);
	i18n_udatepg_date_time_pattern_field_e eDateTimePatternField[] = {I18N_UDATEPG_ERA_FIELD,                  
																		I18N_UDATEPG_YEAR_FIELD,                
																		I18N_UDATEPG_QUARTER_FIELD,             
																		I18N_UDATEPG_MONTH_FIELD,               
																		I18N_UDATEPG_WEEK_OF_YEAR_FIELD,        
																		I18N_UDATEPG_WEEK_OF_MONTH_FIELD,       
																		I18N_UDATEPG_WEEKDAY_FIELD,             
																		I18N_UDATEPG_DAY_OF_YEAR_FIELD,         
																		I18N_UDATEPG_DAY_OF_WEEK_IN_MONTH_FIELD,
																		I18N_UDATEPG_DAY_FIELD,                 
																		I18N_UDATEPG_DAYPERIOD_FIELD,           
																		I18N_UDATEPG_HOUR_FIELD,                
																		I18N_UDATEPG_MINUTE_FIELD,              
																		I18N_UDATEPG_SECOND_FIELD,              
																		I18N_UDATEPG_FRACTIONAL_SECOND_FIELD,   
																		I18N_UDATEPG_ZONE_FIELD                
																	};
	int nPatternFieldSize = sizeof(eDateTimePatternField)/sizeof(eDateTimePatternField[0]);
	int nIndex = 0;		
	for(nIndex = 0; nIndex < nPatternFieldSize; nIndex++)
	{
		nRetVal = i18n_udatepg_set_append_item_format(dtpg, eDateTimePatternField[nIndex], ucharFieldName, nSetLength);       
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] i18n_udatepg_set_append_item_format failed for %s, Returned value is = %s\\n", __LINE__, API_NAMESPACE, UdatepgGetDateTimePatternField(eDateTimePatternField[nIndex]), BaseUtilsGetError(nRetVal));
			return 1;
		}
	
		int nGetLength;
		pRet = i18n_udatepg_get_append_item_format(dtpg, eDateTimePatternField[nIndex], &nGetLength);       
		if(pRet == NULL)
		{
			FPRINTF("[Line : %d][%s] i18n_udatepg_get_append_item_format failed for %s, Returned value is NULL\\n", __LINE__, API_NAMESPACE, UdatepgGetDateTimePatternField(eDateTimePatternField[nIndex]));
			return 1;
		}
		
		if(nGetLength != nSetLength)
		{
			FPRINTF("[Line : %d][%s] Set/Get field length mismatched\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Adjusts the field types (width and subtype) of a pattern to match what is in a skeleton.
/**
* @testcase				ITc_i18n_udatepg_replace_field_types_with_options_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Adjusts the field types (width and subtype) of a pattern to match
* @apitarget			i18n_udatepg_replace_field_types_with_options
* @apicovered			i18n_udatepg_replace_field_types_with_options, 
* @passcase				When i18n_udatepg_replace_field_types_with_options is successful
* @failcase				When i18n_udatepg_replace_field_types_with_options failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_replace_field_types_with_options_p(void)
{
	START_TEST;

	const char *pSrcPattern = "d-M H:m";
    i18n_uchar szPattern[I18N_DATEPG_PATTERN_CAPACITY] = {0,};
    int32_t nPatternLength = strlen(pSrcPattern);
    i18n_uchar szSkeleton[I18N_DATEPG_PATTERN_CAPACITY] = {0,};

#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
    int32_t nSkeletonLength = strlen(I18N_UDATE_YEAR_MONTH);
#endif 	//End MOBILE	
#ifdef WEARABLE	//Starts WEARABLE
	const char *pSrcSkeleton = "MMMMddhhmm";
    int32_t nSkeletonLength = strlen(pSrcSkeleton);
#endif  //End WEARABLE

    i18n_udatepg_date_time_pattern_match_options_e nOptions[] = {I18N_UDATEPG_MATCH_NO_OPTIONS,                                  
						                                         I18N_UDATEPG_MATCH_HOUR_FIELD_LENGTH,       
																 I18N_UDATEPG_MATCH_ALL_FIELDS_LENGTH };
    int nDateTimePatternMatchSize = sizeof(nOptions)/sizeof(nOptions[0]);	
	int nIndex;
	
    i18n_uchar szDest[I18N_DATEPG_PATTERN_CAPACITY] = {0,};
    int32_t nDestCapacity = I18N_DATEPG_PATTERN_CAPACITY;
	int nRetVal = -1;
	for(nIndex = 0; nIndex < nDateTimePatternMatchSize; nIndex++)
	{
		nRetVal =i18n_udatepg_replace_field_types_with_options(dtpg, szPattern, nPatternLength, szSkeleton, nSkeletonLength, nOptions[nIndex], szDest, nDestCapacity);
		if(nRetVal == -1)
		{
			FPRINTF("[Line : %d][%s] i18n_udatepg_replace_field_types_with_options failed for %s, Returned value is negative\\n", __LINE__, API_NAMESPACE, UdatepgGetDateTimePatternMatchField(nOptions[nIndex]));
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Adjusts the field types (width and subtype) of a pattern to match what is in a skeleton.
/**
* @testcase				ITc_i18n_udatepg_replace_field_types_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Adjusts the field types (width and subtype) of a pattern to match
* @apitarget			i18n_udatepg_replace_field_types
* @apicovered			i18n_udatepg_replace_field_types
* @passcase				When i18n_udatepg_replace_field_types are successful
* @failcase				When i18n_udatepg_replace_field_types failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_replace_field_types_p(void)
{
	START_TEST;

	const char *pSrcPattern = "d-M H:m";
    i18n_uchar szPattern[I18N_DATEPG_PATTERN_CAPACITY] = {0,};
    int32_t nPatternLength = strlen(pSrcPattern);
    i18n_uchar szSkeleton[I18N_DATEPG_PATTERN_CAPACITY] = {0,};

#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
    int32_t nSkeletonLength = strlen(I18N_UDATE_YEAR_ABBR_QUARTER);
#endif 	//End MOBILE	
#ifdef WEARABLE	//Starts WEARABLE
	const char *pSrcSkeleton = "MMMMddhhmm";
    int32_t nSkeletonLength = strlen(pSrcSkeleton);
#endif  //End WEARABLE

    i18n_uchar szDest[I18N_DATEPG_PATTERN_CAPACITY] = {0,};
    int32_t nDestCapacity = I18N_DATEPG_PATTERN_CAPACITY;
	int nRetVal = -1;
	
	nRetVal =i18n_udatepg_replace_field_types(dtpg, szPattern, nPatternLength, szSkeleton, nSkeletonLength, szDest, nDestCapacity);
    if(nRetVal < 0)
	{
		FPRINTF("[Line : %d][%s] i18n_udatepg_replace_field_types failed, Returned value is negative\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: Adjusts the field types (width and subtype) of a pattern to match what is in a skeleton.
/**
* @testcase				ITc_i18n_udatepg_get_skeleton_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Adjusts the field types (width and subtype) of a pattern to match.
* @apitarget			i18n_udatepg_get_skeleton
* @apicovered			i18n_udatepg_get_best_pattern, i18n_udatepg_get_skeleton
* @passcase				When i18n_udatepg_get_best_pattern and i18n_udatepg_get_skeleton are successful
* @failcase				When i18n_udatepg_get_best_pattern or i18n_udatepg_get_skeleton failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_get_skeleton_p(void)
{
	START_TEST;

    i18n_uchar szBuffer[I18N_DATEPG_PATTERN_CAPACITY] = {0,};
    int nCapacityBuffer = I18N_DATEPG_PATTERN_CAPACITY;
    
#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
    int nLength = strlen(I18N_UDATE_MONTH);
#endif 	//End MOBILE	
#ifdef WEARABLE	//Starts WEARABLE
	const char *pSkeleton = "yyyyMMMdd";
    int nLength = strlen(pSkeleton);
#endif  //End WEARABLE

    i18n_uchar szBestPattern[I18N_DATEPG_PATTERN_CAPACITY] = {0,};
    int nCapacityBestPattern = I18N_DATEPG_PATTERN_CAPACITY;
    int32_t nBestPatternLen = -1;
	int nRetVal = -1;

#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
    nRetVal =i18n_udatepg_get_best_pattern(dtpg, i18n_ustring_copy_ua(szBuffer, I18N_UDATE_MONTH), nLength, szBestPattern, nCapacityBestPattern, &nBestPatternLen);
#endif 	//End MOBILE	
#ifdef WEARABLE	//Starts WEARABLE
	nRetVal =i18n_udatepg_get_best_pattern(dtpg, i18n_ustring_copy_ua(szBuffer, pSkeleton), nLength, szBestPattern, nCapacityBestPattern, &nBestPatternLen);
#endif  //End WEARABLE	
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_get_best_pattern", BaseUtilsGetError(nRetVal));
	
	nRetVal =i18n_udatepg_get_skeleton(dtpg, szBestPattern, i18n_ustring_get_length(szBestPattern), szBuffer, nCapacityBuffer);
    if(nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s] i18n_udatepg_get_skeleton failed, Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the best pattern matching the input skeleton.
/**
* @testcase				ITc_i18n_udatepg_get_best_pattern_with_options_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the best pattern matching the input skeleton.
* @apitarget			i18n_udatepg_get_best_pattern_with_options
* @apicovered			i18n_udatepg_get_best_pattern_with_options
* @passcase				When i18n_udatepg_get_best_pattern_with_options is successful
* @failcase				When i18n_udatepg_get_best_pattern_with_options failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_get_best_pattern_with_options_p(void)
{
	START_TEST;

	i18n_uchar szBuffer[I18N_DATEPG_PATTERN_CAPACITY] = {0,};

#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
    int nLength = strlen(I18N_UDATE_ABBR_MONTH);
#endif 	//End MOBILE	
#ifdef WEARABLE	//Starts WEARABLE
	const char *pSkeleton = "yyyyMMMdd";
    int nLength = strlen(pSkeleton);
#endif  //End WEARABLE

	i18n_uchar szBestPattern[I18N_DATEPG_PATTERN_CAPACITY] = {0,};
    int nCapacity = I18N_DATEPG_PATTERN_CAPACITY;
	i18n_udatepg_date_time_pattern_match_options_e nOptions[] = {I18N_UDATEPG_MATCH_NO_OPTIONS,                                  
						                                         I18N_UDATEPG_MATCH_HOUR_FIELD_LENGTH,       
																 I18N_UDATEPG_MATCH_ALL_FIELDS_LENGTH };
    int nDateTimePatternMatchSize = sizeof(nOptions)/sizeof(nOptions[0]);	
	int nIndex;
	int nRetVal = -1;
	for(nIndex = 0; nIndex < nDateTimePatternMatchSize; nIndex++)
	{

#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
    nRetVal =i18n_udatepg_get_best_pattern_with_options(dtpg, i18n_ustring_copy_ua(szBuffer, I18N_UDATE_ABBR_MONTH), nLength, nOptions[nIndex], szBestPattern, nCapacity);
#endif 	//End MOBILE	
#ifdef WEARABLE	//Starts WEARABLE
	nRetVal =i18n_udatepg_get_best_pattern_with_options(dtpg, i18n_ustring_copy_ua(szBuffer, pSkeleton), nLength, nOptions[nIndex], szBestPattern, nCapacity);
#endif  //End WEARABLE		
		if(nRetVal == -1)
		{
			FPRINTF("[Line : %d][%s] i18n_udatepg_get_best_pattern_with_options failed for %s, Returned value is = -1\\n", __LINE__, API_NAMESPACE, UdatepgGetDateTimePatternMatchField(nOptions[nIndex]));
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Gets a unique base skeleton from a given pattern.
/**
* @testcase				ITc_i18n_udatepg_get_base_skeleton_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets a unique base skeleton from a given pattern.
* @apitarget			i18n_udatepg_get_base_skeleton
* @apicovered			i18n_udatepg_get_best_pattern, i18n_udatepg_get_base_skeleton
* @passcase				When i18n_udatepg_get_best_pattern and i18n_udatepg_get_base_skeleton are successful
* @failcase				When i18n_udatepg_get_best_pattern or i18n_udatepg_get_base_skeleton failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_get_base_skeleton_p(void)
{
	START_TEST;

	i18n_uchar szBuffer[I18N_DATEPG_PATTERN_CAPACITY] = {0,};
	int nCapacityBuffer = I18N_DATEPG_PATTERN_CAPACITY;

#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
    int nLength = strlen(I18N_UDATE_NUM_MONTH);
#endif 	//End MOBILE	
#ifdef WEARABLE	//Starts WEARABLE
	const char *pSkeleton = "yyyyMMMdd";
    int nLength = strlen(pSkeleton);
#endif  //End WEARABLE

	i18n_uchar szBestPattern[I18N_DATEPG_PATTERN_CAPACITY] = {0,};
    int nCapacityBestPattern = I18N_DATEPG_PATTERN_CAPACITY;
	int32_t nBestPatternLen = -1;
	int nRetVal = -1;

#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
    nRetVal = i18n_udatepg_get_best_pattern(dtpg, i18n_ustring_copy_ua(szBuffer, I18N_UDATE_NUM_MONTH), nLength, szBestPattern, nCapacityBestPattern, &nBestPatternLen);
#endif 	//End MOBILE	
#ifdef WEARABLE	//Starts WEARABLE
	nRetVal = i18n_udatepg_get_best_pattern(dtpg, i18n_ustring_copy_ua(szBuffer, pSkeleton), nLength, szBestPattern, nCapacityBestPattern, &nBestPatternLen);
#endif  //End WEARABLE
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_get_best_pattern", BaseUtilsGetError(nRetVal));
	
	nRetVal =i18n_udatepg_get_base_skeleton(dtpg, szBestPattern, i18n_ustring_get_length(szBestPattern), szBuffer, nCapacityBuffer);
	if(nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s] i18n_udatepg_get_base_skeleton failed. Returned value is -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Adds a pattern to the generator.
/**
* @testcase				ITc_i18n_udatepg_add_pattern_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds a pattern to the generator.
* @scenario				Adds a pattern to the generator.
* @apitarget			i18n_udatepg_add_pattern
* @apicovered			i18n_udatepg_add_pattern
* @passcase				When i18n_udatepg_add_pattern is successful
* @failcase				When i18n_udatepg_add_pattern failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_add_pattern_p(void)
{
	START_TEST;

    i18n_uchar szPattern[I18N_DATEPG_PATTERN_CAPACITY] = {0,};

#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
    int32_t nPatternLength = strlen(I18N_UDATE_YEAR_ABBR_MONTH);
#endif 	//End MOBILE	
#ifdef WEARABLE	//Starts WEARABLE
	const char* pSrc = "yyyy/MM/dd";
    int32_t nPatternLength = strlen(pSrc);
#endif  //End WEARABLE

    i18n_ubool bOverride = false;
    i18n_uchar szConflictingPattern[I18N_DATEPG_PATTERN_CAPACITY] = {0,};
    int32_t nCapacity = I18N_DATEPG_PATTERN_CAPACITY;
    i18n_udatepg_date_time_pattern_conflict_e nConflictStatus;
	int nRetVal	= -1;

#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
    nRetVal =i18n_udatepg_add_pattern(dtpg, i18n_ustring_copy_ua(szPattern, I18N_UDATE_YEAR_ABBR_MONTH), nPatternLength, bOverride, szConflictingPattern, nCapacity, &nConflictStatus);
#endif 	//End MOBILE	
#ifdef WEARABLE	//Starts WEARABLE
	nRetVal =i18n_udatepg_add_pattern(dtpg, i18n_ustring_copy_ua(szPattern, pSrc), nPatternLength, bOverride, szConflictingPattern, nCapacity, &nConflictStatus);
#endif  //End WEARABLE
	if(nRetVal == -1)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_udatepg_add_pattern failed. Returned value is -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else if(nConflictStatus != I18N_UDATEPG_NO_CONFLICT && nConflictStatus != I18N_UDATEPG_BASE_CONFLICT && nConflictStatus != I18N_UDATEPG_CONFLICT)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_udatepg_add_pattern failed. Returned invalid output parameter \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: Gets the pattern corresponding to a given skeleton.
/**
* @testcase				ITc_i18n_udatepg_get_pattern_for_skeleton_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the pattern corresponding to a given skeleton.\n
* @apitarget			i18n_udatepg_get_pattern_for_skeleton
* @apicovered			i18n_udatepg_get_pattern_for_skeleton
* @passcase				When i18n_udatepg_create, i18n_udatepg_get_pattern_for_skeleton are successful
* @failcase				When i18n_udatepg_create or i18n_udatepg_get_pattern_for_skeleton failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_get_pattern_for_skeleton_p(void)
{
	START_TEST;

    i18n_uchar szSkeleton[I18N_DATEPG_PATTERN_CAPACITY] = {0,};
    
#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
    int32_t nSkeletonLength = strlen(I18N_UDATE_YEAR_NUM_MONTH_DAY);
#endif 	//End MOBILE	
#ifdef WEARABLE	//Starts WEARABLE
	const char *pSrc = "yMd";
    int32_t nSkeletonLength = strlen(pSrc);
#endif  //End WEARABLE

    int32_t szPatternLength = 0;
	const i18n_uchar *pRet = NULL;

#if defined(MOBILE) || defined(TIZENIOT) || defined(TV)
    pRet = i18n_udatepg_get_pattern_for_skeleton(dtpg, i18n_ustring_copy_ua(szSkeleton, I18N_UDATE_YEAR_NUM_MONTH_DAY), nSkeletonLength, &szPatternLength);
#endif 	//End MOBILE	
#ifdef WEARABLE	//Starts WEARABLE
	pRet = i18n_udatepg_get_pattern_for_skeleton(dtpg, i18n_ustring_copy_ua(szSkeleton, pSrc), nSkeletonLength, &szPatternLength);
#endif  //End WEARABLE	
    if(pRet == NULL)
	{
		FPRINTF("[Line : %d][%s] i18n_udatepg_get_pattern_for_skeleton failed. Returned value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Creates an i18n_uenumeration_h for list of all the skeletons in canonical form.
/**
* @testcase				ITc_i18n_udatepg_skeletons_create_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates an i18n_uenumeration_h for list of all the skeletons in canonical form.
* @scenario				Creates an i18n_uenumeration_h for list of all the skeletons in canonical form.
* @apitarget			i18n_udatepg_skeletons_create
* @apicovered			i18n_udatepg_skeletons_create
* @passcase				When i18n_udatepg_skeletons_create is successful
* @failcase				When i18n_udatepg_skeletons_create failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_skeletons_create_p(void)
{
	START_TEST;

	i18n_uenumeration_h enumeration = NULL;
	int nRetVal = -1;	
		
	nRetVal =i18n_udatepg_skeletons_create(dtpg, &enumeration);
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_skeletons_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(enumeration, "i18n_udatepg_skeletons_create");
	
	return 0;
}

//& type: auto
//& purpose: Creates an i18n_uenumeration_h for list of all the base skeletons in canonical form.
/**
* @testcase				ITc_i18n_udatepg_base_skeletons_create_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates an i18n_uenumeration_h for list of all the base skeletons in canonical form.
* @scenario				Creates an i18n_uenumeration_h for list of all the base skeletons in canonical form.
* @apitarget			i18n_udatepg_base_skeletons_create
* @apicovered			i18n_udatepg_base_skeletons_create
* @passcase				When i18n_udatepg_base_skeletons_create are successful
* @failcase				When i18n_udatepg_base_skeletons_create failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_base_skeletons_create_p(void)
{
	START_TEST;

	i18n_uenumeration_h enumeration = NULL;
	int nRetVal = -1;
	
	nRetVal =i18n_udatepg_base_skeletons_create(dtpg, &enumeration);
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_base_skeletons_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(enumeration, "i18n_udatepg_base_skeletons_create");
	
	return 0;
}

//& type: auto
//& purpose: Creates an empty generator.
/**
* @testcase				ITc_i18n_udatepg_create_empty_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates an empty generator.
* @scenario				Creates an empty generator.\n
*						Destroy the udatepg handle.
* @apitarget			i18n_udatepg_create_empty
* @apicovered			i18n_udatepg_create_empty, i18n_udatepg_destroy
* @passcase				When i18n_udatepg_create_empty are successful
* @failcase				When i18n_udatepg_create_empty failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_create_empty_p(void)
{
	START_TEST;
	i18n_udatepg_h udatepgHandle = NULL;
	int nRetVal = -1;
	
	nRetVal =i18n_udatepg_create_empty(&udatepgHandle);
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_create_empty", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(udatepgHandle, "i18n_udatepg_create_empty");

	nRetVal = i18n_udatepg_destroy(udatepgHandle);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Creates a copy of a generator.
/**
* @testcase				ITc_i18n_udatepg_clone_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates a copy of a generator.
* @scenario				Creates a copy of a generator.
* @apitarget			i18n_udatepg_clone
* @apicovered			i18n_udatepg_clone, i18n_udatepg_destroy
* @passcase				When i18n_udatepg_clone is successful
* @failcase				When i18n_udatepg_clone failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_udatepg_clone_p(void)
{
	START_TEST;
	
	i18n_udatepg_h udatepgCloneHandle = NULL;
	int nRetVal = -1;
	
	nRetVal = i18n_udatepg_clone(dtpg, &udatepgCloneHandle);
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_clone", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(udatepgCloneHandle, "i18n_udatepg_clone");
	
	nRetVal = i18n_udatepg_destroy(udatepgCloneHandle);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_udatepg_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}
