#include "CTs-platform-permission-common.h"

#include "tct_common.h"
#include "assert.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "maps_service.h"
#include "maps_address.h"
#include "maps_error.h"
#include "maps_area.h"
#include "maps_coordinates.h"
#include "maps_place_filter.h"
#include "maps_preference.h"
#include <glib-object.h>
#include <glib-2.0/glib.h>

#define BUFFER						50

char g_szMapsProvider[BUFFER];


/**
* @function 		MapServiceGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
/*char* MapServiceGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case MAPS_ERROR_NONE:					szErrorVal = "MAPS_ERROR_NONE";						break;
		case MAPS_ERROR_PERMISSION_DENIED:   	szErrorVal = "MAPS_ERROR_PERMISSION_DENIED";		break;
		case MAPS_ERROR_OUT_OF_MEMORY:       	szErrorVal = "MAPS_ERROR_OUT_OF_MEMORY";			break;
		case MAPS_ERROR_INVALID_PARAMETER:   	szErrorVal = "MAPS_ERROR_INVALID_PARAMETER";		break;
		case MAPS_ERROR_NOT_SUPPORTED:       	szErrorVal = "MAPS_ERROR_NOT_SUPPORTED";			break;
		case MAPS_ERROR_CONNECTION_TIME_OUT: 	szErrorVal = "MAPS_ERROR_CONNECTION_TIME_OUT";		break;
		case MAPS_ERROR_NETWORK_UNREACHABLE: 	szErrorVal = "MAPS_ERROR_NETWORK_UNREACHABLE";		break;
		case MAPS_ERROR_INVALID_OPERATION:   	szErrorVal = "MAPS_ERROR_INVALID_OPERATION";		break;
		case MAPS_ERROR_KEY_NOT_AVAILABLE:   	szErrorVal = "MAPS_ERROR_KEY_NOT_AVAILABLE";		break;
		case MAPS_ERROR_RESOURCE_BUSY:	    	szErrorVal = "MAPS_ERROR_RESOURCE_BUSY";			break;
		case MAPS_ERROR_CANCELED:            	szErrorVal = "MAPS_ERROR_CANCELED";					break;
		case MAPS_ERROR_UNKNOWN:				szErrorVal = "MAPS_ERROR_UNKNOWN";					break;
		case MAPS_ERROR_SERVICE_NOT_AVAILABLE:	szErrorVal = "MAPS_ERROR_SERVICE_NOT_AVAILABLE";	break;
		case MAPS_ERROR_NOT_FOUND:           	szErrorVal = "MAPS_ERROR_NOT_FOUND";				break;
		default : 					           	szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}*/

/**
* @function         CTs_platform_permission_MapsService_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_MapsService_startup(void)
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
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_MapsService_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_MapsService_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_MapsService_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_MapsService_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose:Checking tizen.org/privilege/mapservice network.get privilege
//& type: auto
/**
* @testcase			CTc_MapsService_PrivilegeMapSservice_maps_service_create
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			scenario to creates and destroy new maps service handle		
* @apicovered		maps_service_create, maps_service_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_MapsService_PrivilegeMapSservice_maps_service_create(void)
{
	START_TEST;
	maps_service_h hMapsService = NULL;
	bool bIsFeatureSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CAPI_MAPS, bIsFeatureSupported, API_NAMESPACE);
	if ( false == bIsFeatureSupported  )
		{
			FPRINTF("[Line : %d][%s] Feature [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CAPI_MAPS);
			return 0;
		}

	memset( g_szMapsProvider, '\0', sizeof(char)*BUFFER);
	strncpy(g_szMapsProvider, "HERE", strlen("HERE")+1);
	FPRINTF("[Line : %d][%s] Provider list from maps_service_foreach_provider is = %s\\n", __LINE__, API_NAMESPACE, g_szMapsProvider);

	int nRet = maps_service_create(g_szMapsProvider, &hMapsService);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "maps_service_create", MapServiceGetError(nRet), maps_service_destroy(hMapsService),MAPS_ERROR_NONE);

	return 0;
}

