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

static i18n_ubreak_iterator_h g_hUbrkIter = NULL;
static i18n_uchar *pszUchar = NULL;

//& set: BaseUtilsUtmscale 
void ITs_base_utils_utmscale_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_base_utils_utmscale_startup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

void ITs_base_utils_utmscale_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_base_utils_utmscale_startup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-base-utils-testcases
*  @brief 		Integration testcases for module base-utils utmscale
*  @ingroup 	itc-base-utils
*  @{
*/

//& type: auto
//& purpose: Gets a value associated with a particular time scale
/**
* @testcase				ITc_i18n_utmscale_get_time_scale_value_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				i18n_utmscale_get_time_scale_value
* @apitarget			i18n_utmscale_get_time_scale_value
* @apicovered			i18n_utmscale_get_time_scale_value
* @passcase				I18N_ERROR_NONE returned by i18n_utmscale_get_time_scale_value
* @failcase				I18N_ERROR_NONE not returned by i18n_utmscale_get_time_scale_value or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_utmscale_get_time_scale_value_p(void)
{
	START_TEST_PRINT;

	int64_t nGetValue = NULL;
	int nRetVal = i18n_utmscale_get_time_scale_value(I18N_UTMSCALE_JAVA_TIME, I18N_UTMSCALE_VALUE_UNITS, &nGetValue);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_utmscale_get_time_scale_value", BaseUtilsGetError(nRetVal));
	if(nGetValue == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] nGetValue is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Converts the time given as int64_t to universal time scale
/**
* @testcase				ITc_i18n_utmscale_from_int64_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				i18n_utmscale_from_int64
* @apitarget			i18n_utmscale_from_int64
* @apicovered			i18n_utmscale_from_int64
* @passcase				I18N_ERROR_NONE returned by i18n_utmscale_from_int64
* @failcase				I18N_ERROR_NONE not returned by i18n_utmscale_from_int64 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_utmscale_from_int64_p(void)
{
	START_TEST_PRINT;

	int64_t nGetValue = NULL;
	int64_t nGetUnivValue = NULL;
	int nRetVal = i18n_utmscale_get_time_scale_value(I18N_UTMSCALE_JAVA_TIME, I18N_UTMSCALE_VALUE_UNITS, &nGetValue);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_utmscale_get_time_scale_value", BaseUtilsGetError(nRetVal));
	if(nGetValue == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] nGetValue is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = i18n_utmscale_from_int64(nGetValue, I18N_UTMSCALE_ICU4C_TIME, &nGetUnivValue);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_utmscale_from_int64", BaseUtilsGetError(nRetVal));
	if(nGetUnivValue == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] nGetUnivValue is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Converts the time given as universal time to an int64_t
/**
* @testcase				ITc_i18n_utmscale_to_int64_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				i18n_utmscale_to_int64
* @apitarget			i18n_utmscale_to_int64
* @apicovered			i18n_utmscale_to_int64
* @passcase				I18N_ERROR_NONE returned by i18n_utmscale_to_int64
* @failcase				I18N_ERROR_NONE not returned by i18n_utmscale_to_int64 or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_utmscale_to_int64_p(void)
{
	START_TEST_PRINT;
	
	int64_t nGetValue = NULL;
	int64_t nGetOtherValue = NULL;
	int nRetVal = i18n_utmscale_get_time_scale_value(I18N_UTMSCALE_JAVA_TIME, I18N_UTMSCALE_VALUE_UNITS, &nGetValue);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_utmscale_get_time_scale_value", BaseUtilsGetError(nRetVal));
	if(nGetValue == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] nGetValue is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = i18n_utmscale_to_int64(nGetValue, I18N_UTMSCALE_ICU4C_TIME, &nGetOtherValue);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_utmscale_to_int64", BaseUtilsGetError(nRetVal));
	if(nGetOtherValue == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] nGetOtherValue is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/** @} */
/** @} */
