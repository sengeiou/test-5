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
#include "ITs-runtime-info-common.h"

#define IS_RESOURCED_DEACTIVATED	(access("/run/resourced", F_OK) != 0)

/** @addtogroup itc-runtime-info
*  @ingroup itc
*  @{
*/

//& set: runtime-info

/**
* @function 		ITs_runtime_info_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_runtime_info_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Runtime_Info_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_runtime_info_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_runtime_info_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Runtime_Info_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		runtime_info_changed_callback
* @description 		Callback function for any runtime-info event
* @parameter[IN]	runtime_info_e
*			[IN]	void *user_data
* @return			NA
*/ 
void runtime_info_changed_callback(runtime_info_key_e key, void *user_data)
{
	FPRINTF("[Line : %d][%s] runtime_info_changed_callback invoked, runtime-info key = %d\\n", __LINE__, API_NAMESPACE, key);
}

/** @addtogroup itc-runtime-info-testcases
*  @brief 		Integration testcases for module runtime-info
*  @ingroup 	itc-runtime-info
*  @{
*/

//& type: auto
//& purpose: Gets bool value for any runtime-info key
/**
* @testcase 			ITc_runtime_info_get_value_bool_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets bool value for any runtime-info key
* @scenario				Gets bool value for a runtime-info key
* @apicovered			runtime_info_get_value_bool
* @passcase				When runtime_info_get_value_bool is successful and return valid data
* @failcase				If target API fails or return invalid value.
* @precondition			audio jack should be connected;Silent mode and auto rotation should be enabled. 
* @postcondition		NA
*/
int ITc_runtime_info_get_value_bool_p(void)
{
	START_TEST;
	
	bool bValue = false;
	runtime_info_key_e key;
	runtime_info_key_e key_type[] = { RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED };

	char* pKey = "http://tizen.org/feature/screen.auto_rotation";
	bool bFeatureAutoRotationEnabled = TCTCheckSystemInfoFeatureSupported(pKey, API_NAMESPACE);
	int nRet = 0;
	int enum_size = sizeof(key_type) / sizeof(key_type[0]);
	int enum_counter = 0;
	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		bValue = false;
		key = key_type[enum_counter];
		if ( key == RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED )
		{
			if ( !bFeatureAutoRotationEnabled )
			{
				FPRINTF("[Line : %d][%s] RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED is not supported\\n", __LINE__, API_NAMESPACE);
				continue;
			}
		}

		//Target API
		nRet = runtime_info_get_value_bool(key, &bValue);
		if (nRet != RUNTIME_INFO_ERROR_NONE && nRet != RUNTIME_INFO_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("\\n[Line : %d][%s]runtime_info_get_value_bool failed  for key_type value = %s, error returned = %s ", __LINE__, API_NAMESPACE, RuntimeGetKeyString(key_type[enum_counter]), RuntimeInfoGetError(nRet));
			return 1;
		}
		if ( true != bValue )
		{
			FPRINTF("[Line : %d][%s] runtime_info_get_value_bool returned incorrect data;expected value = true, returned value = false for key_type value = %s\\n", __LINE__, API_NAMESPACE, RuntimeGetKeyString(key_type[enum_counter]));
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Gets string value for any runtime-info key
/**
* @testcase 			ITc_runtime_info_get_value_string_p
* @since_tizen			2.3
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets string value for any runtime-info key
* @scenario				Gets string value for a runtime-info key
* @apicovered			runtime_info_get_value_string
* @passcase				When runtime_info_get_value_string is successful and return valid data.
* @failcase				If target api fails or return invalid value.
* @precondition			none
* @postcondition		none
*/
int ITc_runtime_info_get_value_string_p(void)
{
	START_TEST;

	/* There are no string type keys in runtime-info currently.
	 * But this test will be around for when string keys are added in the future.
	 */
	runtime_info_key_e key_type[] = {};

	int enum_size = sizeof(key_type) / sizeof(key_type[0]);
	int enum_counter = 0;
	char* pStr = NULL;
	runtime_info_key_e key;
	int nRet  = 0;
	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		pStr = NULL;
		key = key_type[enum_counter];

		//Target API
		nRet = runtime_info_get_value_string(key, &pStr);
		if ( nRet != RUNTIME_INFO_ERROR_NONE && nRet != RUNTIME_INFO_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] runtime_info_get_value_string failed for key_type value = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, RuntimeGetKeyString(key_type[enum_counter]), RuntimeInfoGetError(nRet));
			return 1;
		}

		if ( NULL == pStr )
		{
			FPRINTF("[Line : %d][%s] runtime_info_get_value_string returned NULL data for key_type value = %s\\n", __LINE__, API_NAMESPACE, RuntimeGetKeyString(key_type[enum_counter]));
			return 1;
		}
		FREE_MEMORY(pStr);
	}
	return 0;
}

//& type: auto
//& purpose: Gets int value for any runtime-info key
/**
* @testcase 			ITc_runtime_info_get_value_int_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets int value for any runtime-info key
* @scenario				Gets int value for a runtime-info key
* @apicovered			runtime_info_get_value_int
* @passcase				When runtime_info_get_value_int is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			Audio jack should be connected
* @postcondition		NA
*/
int ITc_runtime_info_get_value_int_p(void)
{
	START_TEST;

	runtime_info_key_e key_type[] = {RUNTIME_INFO_KEY_AUDIO_JACK_STATUS};
	int enum_size = sizeof(key_type) / sizeof(key_type[0]);
	int enum_counter = 0;
	int nValue = -1;
	runtime_info_key_e key;
	int nRet = 0;
	
	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		key = key_type[enum_counter];

		//Target API
		nRet = runtime_info_get_value_int(key, &nValue);
		if (nRet != RUNTIME_INFO_ERROR_NONE && nRet != RUNTIME_INFO_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("\\n[Line : %d][%s] runtime_info_get_value_int failed  for key_type value = %s, error returned = %s ", __LINE__,  API_NAMESPACE, RuntimeGetKeyString(key_type[enum_counter]), RuntimeInfoGetError(nRet));
			return 1;
		}
		if ( key == RUNTIME_INFO_KEY_AUDIO_JACK_STATUS )
		{
			if ( nValue == RUNTIME_INFO_AUDIO_JACK_STATUS_UNCONNECTED )
			{
				FPRINTF("[Line : %d][%s] runtime_info_get_value_int returned RUNTIME_INFO_AUDIO_JACK_STATUS_UNCONNECTED for key_type value = %s\\n", __LINE__, API_NAMESPACE, RuntimeGetKeyString(key_type[enum_counter]));
				return 0;
			}
		}
	}
	return 0;
}

//& type: auto
//& purpose: Sets and unsets changed callback for runtime-info key
/**
* @testcase 			ITc_runtime_info_set_unset_changed_cb_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and unsets changed callback for runtime-info key
* @scenario				Sets changed callback for runtime-info key
* 						Unsets changed callback for runtime-info key
* @apicovered			runtime_info_unset_changed_cb, runtime_info_set_changed_cb
* @passcase				When runtime_info_unset_changed_cb and runtime_info_set_changed_cb are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_runtime_info_set_unset_changed_cb_p(void)
{
	START_TEST;
	
	runtime_info_key_e key = RUNTIME_INFO_KEY_AUDIO_JACK_STATUS;

	int nRet = runtime_info_set_changed_cb(key, runtime_info_changed_callback, NULL);
	if (nRet != RUNTIME_INFO_ERROR_NONE && nRet != RUNTIME_INFO_ERROR_NOT_SUPPORTED)
	{
		FPRINTF("\\n[Line : %d][%s] runtime_info_set_changed_cb failed , error returned = %s ", __LINE__,  API_NAMESPACE, RuntimeInfoGetError(nRet));
		return 1;
	}
	// Give some sleep between set and unset
	usleep(2000);
	nRet = runtime_info_unset_changed_cb(key);
	if (nRet != RUNTIME_INFO_ERROR_NONE && nRet != RUNTIME_INFO_ERROR_NOT_SUPPORTED)
	{
		FPRINTF("\\n[Line : %d][%s] runtime_info_unset_changed_cb failed  , error returned = %s ", __LINE__,  API_NAMESPACE, RuntimeInfoGetError(nRet));
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets system memory information
/**
* @testcase				ITc_runtime_info_get_system_memory_info_p
* @since_tizen			2.4
* @author				SRID(sharma.am)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets system memory information
* @scenario				Gets system memory information
* @apicovered			runtime_info_get_system_memory_info
* @passcase				When runtime_info_get_system_memory_info is successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_runtime_info_get_system_memory_info_p(void)
{
	START_TEST;
	
	runtime_memory_info_s hUsage;
	runtime_info_error_e nRet = runtime_info_get_system_memory_info(&hUsage);
	if (nRet != RUNTIME_INFO_ERROR_NONE && nRet != RUNTIME_INFO_ERROR_NOT_SUPPORTED)
	{
		FPRINTF("\\n[Line : %d][%s] runtime_info_get_system_memory_info failed , error returned = %s ", __LINE__,  API_NAMESPACE, RuntimeInfoGetError(nRet));
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets process memory information
/**
* @testcase				ITc_runtime_info_get_process_memory_info_p
* @since_tizen			2.4
* @author				SRID(sharma.am)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets process memory information
* @scenario				Gets process memory information
* @apicovered			runtime_info_get_process_memory_info
* @passcase				When runtime_info_get_process_memory_info is successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_runtime_info_get_process_memory_info_p(void)
{
	START_TEST;
	
	int nArrPID[] = { getpid(), getppid() };
	int nSize = sizeof(nArrPID) / sizeof(int);
	process_memory_info_s* hArrUsage = NULL;
	
	runtime_info_error_e nRet = runtime_info_get_process_memory_info(nArrPID, nSize, &hArrUsage);
	FREE_MEMORY(hArrUsage);
	if (nRet != RUNTIME_INFO_ERROR_NONE && nRet != RUNTIME_INFO_ERROR_NOT_SUPPORTED &&
		(IS_RESOURCED_DEACTIVATED && nRet != RUNTIME_INFO_ERROR_REMOTE_IO))
	{
		FPRINTF("\\n[Line : %d][%s] runtime_info_get_process_memory_info failed , error returned = %s ", __LINE__,  API_NAMESPACE, RuntimeInfoGetError(nRet));
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets Gets CPU usage information
/**
* @testcase				ITc_runtime_info_get_cpu_usage_p
* @since_tizen			2.4
* @author				SRID(sharma.am)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets CPU usage information
* @scenario				Gets CPU usage information
* @apicovered			runtime_info_get_cpu_usage
* @passcase				When runtime_info_get_cpu_usage is successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_runtime_info_get_cpu_usage_p(void)
{
	START_TEST;
	
	runtime_cpu_usage_s hUsage;
	runtime_info_error_e nRet = runtime_info_get_cpu_usage(&hUsage);
	if (nRet != RUNTIME_INFO_ERROR_NONE && nRet != RUNTIME_INFO_ERROR_NOT_SUPPORTED)
	{
		FPRINTF("\\n[Line : %d][%s] runtime_info_get_cpu_usage failed , error returned = %s ", __LINE__,  API_NAMESPACE, RuntimeInfoGetError(nRet));
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets CPU usage per process information
/**
* @testcase				ITc_runtime_info_get_process_cpu_usage_p
* @since_tizen			2.4
* @author				SRID(sharma.am)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets CPU usage per process information 
* @scenario				Get CPU usage per process information
* @apicovered			runtime_info_get_process_cpu_usage
* @passcase				When runtime_info_get_process_cpu_usage is successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_runtime_info_get_process_cpu_usage_p(void)
{
	START_TEST;
	
	int nArrPID[] = { getpid(), getppid() };
	int nSize = sizeof(nArrPID) / sizeof(int);
	process_cpu_usage_s* hArrUsage = NULL;
	
	runtime_info_error_e nRet = runtime_info_get_process_cpu_usage(nArrPID, nSize, &hArrUsage);
	FREE_MEMORY(hArrUsage);
	if (nRet != RUNTIME_INFO_ERROR_NONE && nRet != RUNTIME_INFO_ERROR_NOT_SUPPORTED &&
		(IS_RESOURCED_DEACTIVATED && nRet != RUNTIME_INFO_ERROR_REMOTE_IO))
	{
		FPRINTF("\\n[Line : %d][%s] runtime_info_get_process_cpu_usage failed , error returned = %s ", __LINE__,  API_NAMESPACE, RuntimeInfoGetError(nRet));
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the number of processors
/**
* @testcase				ITc_runtime_info_get_processor_count_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 					auto
* @description			Gets the number of processors
* @scenario				Gets the number of processors
* @apicovered				runtime_info_get_processor_count
* @passcase				When runtime_info_get_processor_count is successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition			NA
*/
int ITc_runtime_info_get_processor_count_p(void)
{
	START_TEST;
	
	int nNumCore = 0;
	
	//Target API
	int nRet = runtime_info_get_processor_count(&nNumCore);
	PRINT_RESULT(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_get_processor_count", RuntimeInfoGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Gets the current frequency of processors
/**
* @testcase				ITc_runtime_info_get_processor_current_frequency_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 					auto
* @description			Gets the current frequency of processors
* @scenario				Gets the current frequency of processors
* @apicovered				runtime_info_get_processor_current_frequency
* @passcase				When runtime_info_get_processor_current_frequency is successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition			NA
*/
int ITc_runtime_info_get_processor_current_frequency_p(void)
{
	START_TEST;
	
	int nCoreIndex =0;
	int nCPUFreq = 0;
	
	//Target API
	int nRet = runtime_info_get_processor_current_frequency(nCoreIndex, &nCPUFreq);
	PRINT_RESULT(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_get_processor_current_frequency", RuntimeInfoGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Gets the max frequency of processors
/**
* @testcase				ITc_runtime_info_get_processor_max_frequency_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 					auto
* @description			Gets the max frequency of processors
* @scenario				Gets the max frequency of processors
* @apicovered				runtime_info_get_processor_max_frequency
* @passcase				When runtime_info_get_processor_max_frequency is successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition			NA
*/
int ITc_runtime_info_get_processor_max_frequency_p(void)
{
	START_TEST;
	
	int nCoreIndex =0;
	int nCPUMaxFreq = 0;
	
	//Target API
	int nRet = runtime_info_get_processor_max_frequency(nCoreIndex, &nCPUMaxFreq);
	PRINT_RESULT(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_get_processor_max_frequency", RuntimeInfoGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Gets physical memory size
/**
* @testcase			ITc_runtime_info_get_physical_memory_size_p
* @since_tizen			4.0
* @author			SRID(maneesha.k)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Gets physical memory size
* @scenario			Gets physical memory size
* @apicovered			runtime_info_get_physical_memory_size
* @passcase			When runtime_info_get_physical_memory_size is successful
* @failcase			If runtime_info_get_physical_memory_size fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_runtime_info_get_physical_memory_size_p(void)
{
	START_TEST;
	
	int nMemSize = 0;
	
	//Target API
	int nRet = runtime_info_get_physical_memory_size( &nMemSize);
	PRINT_RESULT(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_get_physical_memory_size", RuntimeInfoGetError(nRet));
	
	
	return 0;
}

//& type: auto
//& purpose: Get all apps' memory usage and Destroy app usage handle
/**
* @testcase			ITc_runtime_info_app_usage_destroy_p
* @since_tizen		4.0
* @author			SRID(shilpa.j)
* @reviewer			SRID(nibha.sharma)
* @type 			auto
* @description		Get all apps' memory usage and destroys the app usage handle
* @scenario			Get all apps' memory usage and destroys the app usage handle
* @apicovered		runtime_info_get_all_apps_memory_usage,runtime_info_app_usage_destroy
* @passcase			When runtime_info_get_all_apps_memory_usage or runtime_info_app_usage_destroy is successful
* @failcase			If runtime_info_get_all_apps_memory_usage or runtime_info_app_usage_destroy fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_runtime_info_app_usage_destroy_p(void)
{
	START_TEST;
	
	app_usage_h hApphandle;
	//Target API
	int nRet = runtime_info_get_all_apps_memory_usage( &hApphandle);
	if (IS_RESOURCED_DEACTIVATED) {
		PRINT_RESULT(RUNTIME_INFO_ERROR_REMOTE_IO, nRet, "runtime_info_get_all_apps_memory_usage", RuntimeInfoGetError(nRet));
		return 0;
	} else
		PRINT_RESULT(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_get_all_apps_memory_usage", RuntimeInfoGetError(nRet));
	//CHECK_HANDLE(hApphandle, "runtime_info_get_all_apps_memory_usage");//hApphandle is a integer val

	//Target API
	nRet = runtime_info_app_usage_destroy( hApphandle );
	PRINT_RESULT(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_app_usage_destroy", RuntimeInfoGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  Get the app count
/**
* @testcase			ITc_runtime_info_app_usage_get_count_p
* @since_tizen		4.0
* @author			SRID(shilpa.j)
* @reviewer			SRID(nibha.sharma)
* @type 			auto
* @description		Get the app count
* @scenario			Get the app count
* @apicovered		runtime_info_get_all_apps_memory_usage,runtime_info_app_usage_get_count
* @passcase			When runtime_info_app_usage_get_count is successful
* @failcase			If runtime_info_app_usage_get_count fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_runtime_info_app_usage_get_count_p(void)
{
	START_TEST;
	
	app_usage_h hApphandle;
	int nCount;

	int nRet = runtime_info_get_all_apps_memory_usage( &hApphandle);
	if (IS_RESOURCED_DEACTIVATED) {
		PRINT_RESULT(RUNTIME_INFO_ERROR_REMOTE_IO, nRet, "runtime_info_get_all_apps_memory_usage", RuntimeInfoGetError(nRet));
		return 0;
	} else
		PRINT_RESULT(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_get_all_apps_memory_usage", RuntimeInfoGetError(nRet));

	//Target API
	nRet = runtime_info_app_usage_get_count( hApphandle,&nCount);
	PRINT_RESULT_CLEANUP(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_app_usage_get_count", RuntimeInfoGetError(nRet),runtime_info_app_usage_destroy( hApphandle ));

	nRet = runtime_info_app_usage_destroy( hApphandle );
	PRINT_RESULT_NORETURN(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_app_usage_destroy", RuntimeInfoGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  Get the app id
/**
* @testcase			ITc_runtime_info_app_usage_get_appid_p
* @since_tizen		4.0
* @author			SRID(shilpa.j)
* @reviewer			SRID(nibha.sharma)
* @type 			auto
* @description		Get the app id
* @scenario			Get the app id
* @apicovered		runtime_info_get_all_apps_cpu_rate,runtime_info_app_usage_get_appid
* @passcase			When runtime_info_app_usage_get_appid is successful
* @failcase			If runtime_info_app_usage_get_appid fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_runtime_info_app_usage_get_appid_p(void)
{
	START_TEST;
	
	app_usage_h hApphandle;
	char* pszAppId = NULL;
	int nIndex = 0;

	
	int nRet = runtime_info_get_all_apps_cpu_rate( &hApphandle);
	if (IS_RESOURCED_DEACTIVATED) {
		PRINT_RESULT(RUNTIME_INFO_ERROR_REMOTE_IO, nRet, "runtime_info_get_all_apps_memory_usage", RuntimeInfoGetError(nRet));
		return 0;
	} else
		PRINT_RESULT(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_get_all_apps_cpu_rate", RuntimeInfoGetError(nRet));

	//Target API
	nRet = runtime_info_app_usage_get_appid( hApphandle,nIndex,&pszAppId);
	PRINT_RESULT_CLEANUP(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_app_usage_get_appid", RuntimeInfoGetError(nRet),runtime_info_app_usage_destroy( hApphandle ));
	if(pszAppId == NULL)
	{
		FPRINTF("[Line : %d][%s] runtime_info_app_usage_get_appid returned NULL value \n", __LINE__, API_NAMESPACE);
		runtime_info_app_usage_destroy( hApphandle );
		return 1;
	}
	FREE_MEMORY(pszAppId);
	nRet = runtime_info_app_usage_destroy( hApphandle );
	PRINT_RESULT_NORETURN(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_app_usage_destroy", RuntimeInfoGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  Get the app usage
/**
* @testcase			ITc_runtime_info_app_usage_get_usage_p
* @since_tizen		4.0
* @author			SRID(shilpa.j)
* @reviewer			SRID(nibha.sharma)
* @type 			auto
* @description		Get the app usage
* @scenario			Get the app usage
* @apicovered		runtime_info_get_all_apps_memory_usage,runtime_info_app_usage_get_usage
* @passcase			When runtime_info_app_usage_get_usage is successful
* @failcase			If runtime_info_app_usage_get_usage fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_runtime_info_app_usage_get_usage_p(void)
{
	START_TEST;
	
	app_usage_h hApphandle;
	unsigned int nUsage;
	int nIndex = 0;

	int nRet = runtime_info_get_all_apps_memory_usage( &hApphandle);
	if (IS_RESOURCED_DEACTIVATED) {
		PRINT_RESULT(RUNTIME_INFO_ERROR_REMOTE_IO, nRet, "runtime_info_get_all_apps_memory_usage", RuntimeInfoGetError(nRet));
		return 0;
	} else
		PRINT_RESULT(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_get_all_apps_memory_usage", RuntimeInfoGetError(nRet));

	//Target API
	nRet = runtime_info_app_usage_get_usage( hApphandle,nIndex,&nUsage);
	PRINT_RESULT_CLEANUP(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_app_usage_get_usage", RuntimeInfoGetError(nRet),runtime_info_app_usage_destroy( hApphandle ));

	nRet = runtime_info_app_usage_destroy( hApphandle );
	PRINT_RESULT_NORETURN(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_app_usage_destroy", RuntimeInfoGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  Get all apps' CPU rate
/**
* @testcase			ITc_runtime_info_get_all_apps_cpu_rate_p
* @since_tizen		4.0
* @author			SRID(shilpa.j)
* @reviewer			SRID(nibha.sharma)
* @type 			auto
* @description		Get all apps' CPU rate
* @scenario			Get all apps' CPU rate
* @apicovered		runtime_info_get_all_apps_cpu_rate
* @passcase			When runtime_info_get_all_apps_cpu_rate is successful
* @failcase			If runtime_info_get_all_apps_cpu_rate fails
* @precondition		NA
* @postcondition	NA
*/
int ITc_runtime_info_get_all_apps_cpu_rate_p(void)
{
	START_TEST;

	app_usage_h hApphandle;

	//Target API
	int nRet = runtime_info_get_all_apps_cpu_rate( &hApphandle);
	if (IS_RESOURCED_DEACTIVATED) {
		PRINT_RESULT(RUNTIME_INFO_ERROR_REMOTE_IO, nRet, "runtime_info_get_all_apps_memory_usage", RuntimeInfoGetError(nRet));
		return 0;
	} else
		PRINT_RESULT(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_get_all_apps_cpu_rate", RuntimeInfoGetError(nRet));

	nRet = runtime_info_app_usage_destroy( hApphandle );
	PRINT_RESULT_NORETURN(RUNTIME_INFO_ERROR_NONE, nRet, "runtime_info_app_usage_destroy", RuntimeInfoGetError(nRet));
	
	return 0;
}


/** @} */
