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
#include "ITs-system-info-common.h"

/** @addtogroup itc-system-info
*  @ingroup itc
*  @{
*/
//& set: SystemInfo

/**
* @function 		ITs_system_info_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_system_info_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_System_Info_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_system_info_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_system_info_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_System_Info_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-system-info-testcases
*  @brief 		Integration testcases for module system-info
*  @ingroup 	itc-system-info
*  @{
*/
//& purpose: Gets a boolean value of the platform feature. 
//& type: auto
/**
* @testcase 			ITc_system_info_get_platform_bool_p
* @since_tizen			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets a boolean value of the platform feature. 
* @scenario				Gets a boolean value of the platform feature
* @apicovered			system_info_get_platform_bool 
* @passcase				if system_info_get_platform_bool return 0
* @failcase				if system_info_get_platform_bool return non zero
* @precondition			NA
* @postcondition		NA
*/
int ITc_system_info_get_platform_bool_p(void)
{
	START_TEST;
	const char *pszKey = "http://tizen.org/feature/camera";
	bool bValue;

	int nRetVal = system_info_get_platform_bool(pszKey, &bValue);//target api
	PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, nRetVal, "system_info_get_platform_bool", SystemInfoGetError(nRetVal));

	return 0;
}

//& purpose: Gets a string value of the platform feature.
//& type: auto
/**
* @testcase 			ITc_system_info_get_platform_double_p
* @since_tizen			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets a double value of the platform feature
* @scenario				Gets a double value of the platform feature
* @apicovered			system_info_get_platform_double
* @passcase				if system_info_get_platform_double return 0
* @failcase				if system_info_get_platform_double return non zero
* @precondition			NA
* @postcondition		NA
*/
int ITc_system_info_get_platform_double_p(void)
{
	START_TEST;
	const char *pszKey = "http://tizen.org/feature/screen.height";
	double dblValue = -1.0;

	int nRetVal = system_info_get_platform_double(pszKey,&dblValue);//target api
	if ( nRetVal != SYSTEM_INFO_ERROR_NONE )
	{
		if ( nRetVal != SYSTEM_INFO_ERROR_INVALID_PARAMETER )
		{
			FPRINTF("[Line : %d][%s] system_info_get_platform_double failed, error returned = %s\\n", __LINE__, API_NAMESPACE, SystemInfoGetError(nRetVal));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] system_info_get_platform_double skipped as no double key present in model-config file\\n", __LINE__, API_NAMESPACE);
		}
	}
	else if(dblValue == -1.0)
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_double failed, output value is not valid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Gets an integer value of the platform feature. 
//& type: auto
/**
* @testcase 			ITc_system_info_get_platform_int_p
* @since_tizen			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets an integer value of the platform feature
* @scenario				Gets an integer value of the platform feature
* @apicovered			system_info_get_platform_int
* @passcase				if system_info_get_platform_int return 0
* @failcase				if system_info_get_platform_int return non zero
* @precondition			NA
* @postcondition		NA
*/
int ITc_system_info_get_platform_int_p(void)
{
	START_TEST;
	const char *pszKey = "http://tizen.org/feature/multi_point_touch.point_count";
	int nValue = -1; 

	int nRetVal = system_info_get_platform_int(pszKey, &nValue);//target api
	PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, nRetVal, "system_info_get_platform_int", SystemInfoGetError(nRetVal));
	if(nValue == -1)
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_int failed, output value is not valid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Gets a string value of the platform feature
//& type: auto
/**
* @testcase 			ITc_system_info_get_platform_string_p
* @since_tizen			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets a string value of the platform feature
* @scenario				Gets a string value of the platform feature
* @apicovered			system_info_get_platform_string 
* @passcase				if system_info_get_platform_string  return 0
* @failcase				if system_info_get_platform_string  return non zero
* @precondition			NA
* @postcondition		NA
*/
int ITc_system_info_get_platform_string_p(void)
{
	START_TEST;
	const char *pszKey = "http://tizen.org/system/model_name";
	char *pszValue = NULL;

	int nRetVal = system_info_get_platform_string(pszKey, &pszValue);//target api
	PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, nRetVal, "system_info_get_platform_string", SystemInfoGetError(nRetVal));
	CHECK_VALUE_STRING(pszValue, "system_info_get_platform_string");
	FREE_MEMORY(pszValue);
	return 0;
}

/** @} */
/** @} */
