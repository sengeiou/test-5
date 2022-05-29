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
//& set: BaseUtilsDateInterval
i18n_udate g_fromDate = 1000000000.0;
i18n_udate g_toDate = 1500000000.0;

/**
* @function 		ITs_base_utils_date_interval_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_date_interval_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_base_utils_date_interval_startup\\n", __LINE__, API_NAMESPACE);
#endif
	g_dateInterval = NULL;
	int nRetVal = i18n_date_interval_create(g_fromDate, g_toDate, &g_dateInterval);
	if ( nRetVal != I18N_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to create date interval object, error returned = %s\\n", __LINE__,API_NAMESPACE,  BaseUtilsGetError(nRetVal));
		g_bBaseUtilsInitFlag = false;
		return;
	}
	if(g_dateInterval == NULL)
	{
		FPRINTF("[Line : %d][%s] error returned = g_dateInterval object returned is NULL\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
		return;
	}
	g_bBaseUtilsInitFlag = true;
	return;
}

/**
* @function 		ITs_base_utils_date_interval_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_date_interval_cleanup(void)
{
	if ( g_bBaseUtilsInitFlag && g_dateInterval )
	{
		int nRetVal = i18n_date_interval_destroy(g_dateInterval);
		if ( nRetVal != I18N_ERROR_NONE )
		{
			FPRINTF("\\n[Line : %d][%s] i18n_date_interval_destroy failed in cleanup, error returned = %s \n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
		}
		g_dateInterval = NULL;
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_base_utils_date_interval_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type: auto
//& purpose: Create and Distroy date interval object.
/**
* @testcase				ITc_i18n_date_interval_create_destroy_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(j.abhishek)
* @type 				auto
* @scenario				Creates and Distroys a date interval object.
* @apicovered			i18n_date_interval_create, i18n_date_interval_destroy
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_create_destroy_p(void)
{
	START_TEST;

	i18n_date_interval_h hDateInterval = NULL;
	//target API
	int nRetVal = i18n_date_interval_create(g_fromDate, g_toDate, &hDateInterval);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hDateInterval, "i18n_date_interval_create");

	//target API
	nRetVal = i18n_date_interval_destroy(hDateInterval);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Clone date interval object.
/**
* @testcase				ITc_i18n_date_interval_clone_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(j.abhishek)
* @type 				auto
* @scenario				Clone a date interval object.
* @apicovered			i18n_date_interval_clone
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_clone_p(void)
{
	START_TEST;

	i18n_date_interval_h hCloneDateInterval = NULL;
	//target API
	int nRetVal = i18n_date_interval_clone(g_dateInterval, &hCloneDateInterval);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_clone", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hCloneDateInterval, "i18n_date_interval_clone");

	nRetVal = i18n_date_interval_destroy(hCloneDateInterval);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Get 'from date' for a given date interval object.
/**
* @testcase				ITc_i18n_date_interval_get_from_date_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(j.abhishek)
* @type 				auto
* @scenario				Get 'from date' for a given date interval object.
* @apicovered			i18n_date_interval_get_from_date
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_get_from_date_p(void)
{
	START_TEST;

	i18n_udate nGetFromDate = 0.0;
	//target API
	int nRetVal = i18n_date_interval_get_from_date(g_dateInterval, &nGetFromDate);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_get_from_date", BaseUtilsGetError(nRetVal));
	if ( g_fromDate != nGetFromDate )
	{
	     FPRINTF("[Line : %d][%s] error returned: from date values mismatched, from_date = %f, get_from_date = %f\\n", __LINE__, API_NAMESPACE, g_fromDate, nGetFromDate);
		 return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Get 'to date' for a given date interval object.
/**
* @testcase				ITc_i18n_date_interval_get_to_date_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(j.abhishek)
* @type 				auto
* @scenario				Get 'to date' for a given date interval object.
* @apicovered			i18n_date_interval_get_to_date
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_get_to_date_p(void)
{
	START_TEST;

	i18n_udate nGetToDate = 0.0;
	//target API
	int nRetVal = i18n_date_interval_get_to_date(g_dateInterval, &nGetToDate);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_get_to_date", BaseUtilsGetError(nRetVal));
	if ( g_toDate != nGetToDate )
	{
	     FPRINTF("[Line : %d][%s] error returned: to date values mismatched, to_date = %f, get_to_date = %f\\n", __LINE__, API_NAMESPACE, g_toDate, nGetToDate);
		 return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Compares two date interval objects.
/**
* @testcase				ITc_i18n_date_interval_equals_p
* @since_tizen 			5.0
* @author            	SRID(manu.tiwari)
* @type 				auto
* @scenario				Compares two date interval objects.
* @apicovered			i18n_date_interval_equals
* @passcase				When API return I18N_ERROR_NONE
* @failcase				If target API fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_date_interval_equals_p(void)
{
	START_TEST;

	i18n_date_interval_h hDateInterval = NULL;
	i18n_ubool nIsEqual = false;
	i18n_udate nfromDate = 1000000000.0;
	i18n_udate ntoDate = 1500000000.0;

	int nRetVal = i18n_date_interval_create(nfromDate, ntoDate, &hDateInterval);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hDateInterval, "i18n_date_interval_create");

	//target API
	nRetVal = i18n_date_interval_equals(g_dateInterval, hDateInterval, &nIsEqual);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_equals", BaseUtilsGetError(nRetVal), i18n_date_interval_destroy(hDateInterval));
	if ( nIsEqual == false )
	{
		FPRINTF("[Line : %d][%s] date_interval values mismatch\\n", __LINE__, API_NAMESPACE);
		i18n_date_interval_destroy(hDateInterval);
		return 1;
	}
	nRetVal = i18n_date_interval_destroy(hDateInterval);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_date_interval_destroy", BaseUtilsGetError(nRetVal));
	return 0;
}
