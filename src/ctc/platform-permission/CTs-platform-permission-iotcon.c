//iotcon_ap_refresh
#include "CTs-platform-permission-common.h"
#include "tct_common.h"
#include "assert.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <dlog.h>
#include <iotcon.h>

#define TIMEOUT_CB					5000
#define ICL_OPTIONID_MIN 			2048
#define GMAINTIMEOUT				30000 
#define REPRESENTATION_KEY          "key"
#define REP_NTH_CHILD          		1
#define IOTCON_TIMEOUT				10
#define LITE_RESOURCE_BR            "brightness"
#define KEY							"key"
#define VALUE						"value"
#define REMOTE_RESOURCE				"core.led"
#define LIGHT_RESOURCE              "core.light"
#define LIGHT_RESOURCE2             "core.light2"
#define REMOTE_IP					"11.22.33.44"
#define REMOTE_RESOURCE_LED			"/a/led"
#define REMOTE_RESOURCE_LIGHT       "/a/light"
#define VAL1						0	
#define VAL2						1
#define VAL3						2
#define VAL4						3
#define ASSIGNVAL1					10
#define ASSIGNVAL2					20
#define ASSIGNVAL3					30
#define IOTCON_FEATURE		    	"http://tizen.org/feature/iot.ocf"

#define LOCAL_HOST_ADDRESS "127.0.0.1"
#define LIGHT_RESOURCE_TYPE "core.light"
#define LIGHT_RESOURCE_TYPE2 "core.light2"
#define LIGHT_RESOURCE_TYPE3 "core.light3"
#define LIGHT_RESOURCE_URI "/a/light"
#define LED_RESOURCE_TYPE "core.led"
#define LED_RESOURCE_URI "/a/led"
#define TIMEOUT_COUNT_MAX 3


iotcon_lite_resource_h g_hLiteLightResource;
bool g_bCheckCb;
GMainLoop *g_pMainLoop;
gboolean TimeoutFunction(gpointer data);
static bool g_bRequestHandlerCB = false;
static bool g_bResult;
static iotcon_remote_resource_h g_hClient = NULL;
static iotcon_resource_types_h g_hTypes = NULL;
static iotcon_resource_interfaces_h g_hInterface = NULL;
iotcon_request_h g_hRequest = NULL;


#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
    if ( Handle == NULL )\
    {\
        FPRINTF("[Line: %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
        FreeResource;\
        return 1;\
    }\
}
#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	nIotconTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nIotconTimeoutId);\
	g_pMainLoop = NULL;\
}


/**
 * @function 		gmain_loop_quit_idle
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
static gboolean gmain_loop_quit_idle(gpointer p)
{
	
	g_main_loop_quit(g_pMainLoop);
	return G_SOURCE_REMOVE;
}

/**
* @function 		QuitGmainLoopIdle
* @description	 	Called to quit
* @parameter		NA
* @return 			NA
*/
static void QuitGmainLoopIdle(bool result)
{	
	g_bResult = result;
	g_idle_add(gmain_loop_quit_idle, NULL);
}


/**
* @function 		IotConGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* IotConGetError(int nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
		case IOTCON_ERROR_NONE:					szErrorVal = "IOTCON_ERROR_NONE";					break;
		case IOTCON_ERROR_IO_ERROR:   			szErrorVal = "IOTCON_ERROR_IO_ERROR";				break;
		case IOTCON_ERROR_OUT_OF_MEMORY:       	szErrorVal = "IOTCON_ERROR_OUT_OF_MEMORY";			break;
		case IOTCON_ERROR_PERMISSION_DENIED:   	szErrorVal = "IOTCON_ERROR_PERMISSION_DENIED";		break;
		case IOTCON_ERROR_NOT_SUPPORTED:       	szErrorVal = "IOTCON_ERROR_NOT_SUPPORTED";			break;
		case IOTCON_ERROR_INVALID_PARAMETER: 	szErrorVal = "IOTCON_ERROR_INVALID_PARAMETER";		break;
		case IOTCON_ERROR_NO_DATA: 				szErrorVal = "IOTCON_ERROR_NO_DATA";				break;
		case IOTCON_ERROR_TIMEOUT:   			szErrorVal = "IOTCON_ERROR_TIMEOUT";				break;
		case IOTCON_ERROR_IOTIVITY:   			szErrorVal = "IOTCON_ERROR_IOTIVITY";				break;
		case IOTCON_ERROR_REPRESENTATION:	    szErrorVal = "IOTCON_ERROR_REPRESENTATION";			break;
		case IOTCON_ERROR_INVALID_TYPE:         szErrorVal = "IOTCON_ERROR_INVALID_TYPE";			break;
		case IOTCON_ERROR_ALREADY:				szErrorVal = "IOTCON_ERROR_ALREADY";				break;
		case IOTCON_ERROR_SYSTEM:           	szErrorVal = "IOTCON_ERROR_SYSTEM";					break;
	}
	return szErrorVal;
}

/**
* @function			IotconRemoteResourceDummyResponseCB
* @description		Specifies the type of function passed to iotcon_remote_resource_observe_register()
* @parameter[IN]	iotcon_remote_resource_h resource
* @parameter[IN]	iotcon_error_e err
* @parameter[IN]	iotcon_request_type_e request_type
* @parameter[IN]	iotcon_response_h response
* @parameter[IN]	user_data The user data to pass to the function		
* @return			true to continue with the next iteration of the loop.
*/
static void IotconRemoteResourceDummyResponseCB(iotcon_remote_resource_h resource, iotcon_error_e err,iotcon_request_type_e request_type, iotcon_response_h response, void *user_data)
{
	if((resource == NULL)||(response == NULL))
	{
		FPRINTF("[Line : %d][%s] IotconRemoteResourceDummyResponseCB input resource and response is NULL failed !!!\\n", __LINE__, API_NAMESPACE);
	}
	
	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		//g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
		
	return;
}

int IotconCreateRemoteResource()
{
	int nRet = iotcon_resource_types_create(&g_hTypes);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	CHECK_HANDLE(g_hTypes,"iotcon_resource_types_create");

	nRet = iotcon_resource_types_add(g_hTypes,LIGHT_RESOURCE);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet), iotcon_resource_types_destroy(g_hTypes));

	nRet = iotcon_resource_interfaces_create(&g_hInterface);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_create", IotConGetError(nRet), iotcon_resource_types_destroy(g_hTypes));
	CHECK_HANDLE(g_hInterface,"iotcon_resource_interfaces_create");
	
	nRet = iotcon_resource_interfaces_add(g_hInterface, IOTCON_INTERFACE_DEFAULT);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet), iotcon_resource_interfaces_destroy(g_hInterface);iotcon_resource_types_destroy(g_hTypes));
	
	nRet = iotcon_remote_resource_create(REMOTE_IP, IOTCON_CONNECTIVITY_IP, REMOTE_RESOURCE_LIGHT,IOTCON_RESOURCE_DISCOVERABLE | IOTCON_RESOURCE_OBSERVABLE, g_hTypes, g_hInterface, &g_hClient);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_remote_resource_create", IotConGetError(nRet),  iotcon_resource_interfaces_destroy(g_hInterface);iotcon_resource_types_destroy(g_hTypes));									  
    CHECK_HANDLE(g_hClient,"iotcon_remote_resource_create");
	
    iotcon_resource_types_destroy(g_hTypes);
	iotcon_resource_interfaces_destroy(g_hInterface);

	return 0;
}

/**
* @function 		IotconGetDeviceInfoCB
* @description	 	Callback Function
* @parameter		iotcon_device_info_h info, iotcon_error_e result,void *user_data
* @return 			NA
*/
static void IotconGetDeviceInfoCB(iotcon_device_info_h info, iotcon_error_e result,void *user_data)
{
	
	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}
	
	/**
* @function 		IotconGetPlatformInfoCB
* @description	 	Callback Function
* @parameter		iotcon_platform_info_h info, iotcon_error_e result,void *user_data
* @return 			NA
*/
static void IotconGetPlatformInfoCB(iotcon_platform_info_h info,iotcon_error_e result, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] IotconGetPlatformInfoCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	
	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		RequestHandlerCB
* @description	 	Called when create iotcon resource to get request handle
* @parameter		iotcon_resource_h : The resource handle, iotcon_request_h : The request handle
*					user_data : The user data passed from function
* @return 			NA
*/
static void RequestHandlerCB(iotcon_resource_h resource, iotcon_request_h request,
		void *user_data)
{	
	g_bRequestHandlerCB = true;
	if(request == NULL){
		FPRINTF("Handle iotcon_request_h is null in RequestHandlerCB callback... \n");
	}else{
		g_hRequest = request;	
	}
	
	
	QuitGmainLoopIdle(false);
	
	return;
}

/**
* @function         CTs_platform_permission_iotcon_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_iotcon_startup(void)
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
* @function         CTs_platform_permission_iotcon_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_iotcon_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose: Checking http://tizen.org/privilege/network.get  & http://tizen.org/privilege/d2d.datasharing
/**
* @testcase 			CTc_Iotcon_PrivilegeNetworkGet_initialize_deinitialize_p
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			connect and disconnect iotcon.
* @scenario				connect iotcon \n
* 						disconnect iotcon\n
* @apicovered			iotcon_initialize, iotcon_deinitialize
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns error value
* @precondition			NA
* @postcondition		NA
*/
int CTc_Iotcon_PrivilegeNetworkGet_initialize_deinitialize_p(void)
{
	START_TEST;
	int nRet = 0;
	char *pSvrDBPath;

	if ( !TCTCheckSystemInfoFeatureSupported(IOTCON_FEATURE, API_NAMESPACE) )
	{
		return 0;
	}
	
	 IotconGetSvrDBPath(&pSvrDBPath);
         nRet = iotcon_initialize(pSvrDBPath);
	 free(pSvrDBPath);
	 PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "iotcon_initialize", IotConGetError(nRet));
	
	 iotcon_deinitialize();
		
	return 0;
}
