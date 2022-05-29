#include "CTs-platform-permission-common.h"
/**
* @function 		CTs_platform_permission_runtimeinfo_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_runtimeinfo_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function 		CTs_platform_permission_runtimeinfo_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_runtimeinfo_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/**
* @function 		RuntimeInfoGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
/*char* RuntimeInfoGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch(nRet)
	{
	case RUNTIME_INFO_ERROR_NONE:					szErrorVal = "RUNTIME_INFO_ERROR_NONE";						break;
	case RUNTIME_INFO_ERROR_INVALID_PARAMETER:		szErrorVal = "RUNTIME_INFO_ERROR_INVALID_PARAMETER";		break;
	case RUNTIME_INFO_ERROR_OUT_OF_MEMORY:			szErrorVal = "RUNTIME_INFO_ERROR_OUT_OF_MEMORY";			break;
	case RUNTIME_INFO_ERROR_IO_ERROR:				szErrorVal = "RUNTIME_INFO_ERROR_IO_ERROR";					break;
	default:										szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}*/
//& type: auto
//& purpose: Gets CPU usage per process information
/**
* @testcase				CTc_RuntimeInfo_PrivilegeSystemMonitor_cpu_ucage
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets CPU usage per process information 
* @scenario				Get CPU usage per process information
* @apicovered			runtime_info_get_process_cpu_usage
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA
*/
int CTc_RuntimeInfo_PrivilegeSystemMonitor_cpu_ucage(void)
{
	START_TEST;
	
	int nArrPID[] = { getpid(), getppid() };
	int nSize = sizeof(nArrPID) / sizeof(int);
	process_cpu_usage_s* hArrUsage = NULL;
	
	runtime_info_error_e nRet = runtime_info_get_process_cpu_usage(nArrPID, nSize, &hArrUsage);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "runtime_info_get_process_cpu_usage", RuntimeInfoGetError(nRet),FREE_MEMORY(hArrUsage),RUNTIME_INFO_ERROR_NONE);
	
	return 0;
}

//& type: auto
//& purpose: Gets process memory information
/**
* @testcase				CTc_RuntimeInfo_PrivilegeSystemMonitor_get_process_memory_info
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets process memory information
* @scenario				Gets process memory information
* @apicovered			runtime_info_get_process_memory_info
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA
*/
int CTc_RuntimeInfo_PrivilegeSystemMonitor_get_process_memory_info(void)
{
	START_TEST;
	
	int nArrPID[] = { getpid(), getppid() };
	int nSize = sizeof(nArrPID) / sizeof(int);
	process_memory_info_s* hArrUsage = NULL;
	
	runtime_info_error_e nRet = runtime_info_get_process_memory_info(nArrPID, nSize, &hArrUsage);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "runtime_info_get_process_memory_info", RuntimeInfoGetError(nRet),FREE_MEMORY(hArrUsage),RUNTIME_INFO_ERROR_NONE);
	
	return 0;
}