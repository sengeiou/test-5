//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include "ITs-component-manager-common.h"

/** @addtogroup itc-component-manager
*  @ingroup itc
*  @{
*/

/**
* @function 		ComponentManagerGetError
* @description	 	Maps component_manager_error_e enums
* @parameter		error : error level
* @return 			error string
*/
char* ComponentManagerGetError(component_manager_error_e error)
{
	char *szErrorVal = NULL;
	switch ( error )
	{
	case COMPONENT_MANAGER_ERROR_NONE:				szErrorVal = "COMPONENT_MANAGER_ERROR_NONE";					break;
	case COMPONENT_MANAGER_ERROR_INVALID_PARAMETER:	szErrorVal = "COMPONENT_MANAGER_ERROR_INVALID_PARAMETER";	break;
	case COMPONENT_MANAGER_ERROR_OUT_OF_MEMORY:		szErrorVal = "COMPONENT_MANAGER_ERROR_OUT_OF_MEMORY";		break;
	case COMPONENT_MANAGER_ERROR_IO_ERROR:				szErrorVal = "COMPONENT_MANAGER_ERROR_IO_ERROR";					break;
	case COMPONENT_MANAGER_ERROR_DB_FAILED:		szErrorVal = "COMPONENT_MANAGER_ERROR_DB_FAILED";		break;
	case COMPONENT_MANAGER_ERROR_INVALID_APPLICATION:				szErrorVal = "COMPONENT_MANAGER_ERROR_INVALID_APPLICATION";					break;
	case COMPONENT_MANAGER_ERROR_NOT_RUNNING:	szErrorVal = "COMPONENT_MANAGER_ERROR_NOT_RUNNING";	break;
	case COMPONENT_MANAGER_ERROR_PERMISSION_DENIED:		szErrorVal = "COMPONENT_MANAGER_ERROR_PERMISSION_DENIED";		break;
	default:							szErrorVal = "Unknown Error";					break;
	}

	return szErrorVal;
}

/**
* @function         AppControlResultAppCB
* @description      callback for send launch request
* @parameter        request : app_control request handle, result of callback, data : user data sent to callback
* @return           None
*/
static void AppControlResultAppCB(app_control_h request,
                app_control_error_e result, void *data)
{
	FPRINTF("[Line : %d][%s] \\n", __LINE__, API_NAMESPACE);
}

/**
* @function         AppControlCommonLaunchRequest
* @description      Function for application initial setting to launch app
* @parameter        app_id : application id to launch, component_id : component id, extra: extra data to be sent during app launch
* @return           error code
*/
int AppControlCommonLaunchRequest(const char *app_id, const char *component_id,
                const char *extra)
{
        app_control_h app_control = NULL;
        int nRet = -1;;

        nRet = app_control_create(&app_control);
        if (nRet != APP_CONTROL_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] Failed to create app_control handle. error(%d)\\n", __LINE__, API_NAMESPACE, nRet);
                return nRet;
        }

	if(app_control == NULL) {
		FPRINTF("[Line : %d][%s] app_control handle is NULL\\n", __LINE__, API_NAMESPACE);
                return 1;
	}

        nRet = app_control_set_app_id(app_control, app_id);
        if (nRet != APP_CONTROL_ERROR_NONE) {
                FPRINTF("[Line : %d][%s] Failed to set application ID. error(%d)\\n", __LINE__, API_NAMESPACE, nRet);
                app_control_destroy(app_control);
                return nRet;
        }

        nRet = app_control_set_component_id(app_control, component_id);
        if (nRet != APP_CONTROL_ERROR_NONE) {
                FPRINTF("[Line : %d][%s] Failed to set component ID. error(%d)\\n", __LINE__, API_NAMESPACE, nRet);
                app_control_destroy(app_control);
                return nRet;
        }

        if (extra) {
                nRet = app_control_add_extra_data(app_control, "extra", extra);
                if (nRet != APP_CONTROL_ERROR_NONE) {
                        FPRINTF("[Line : %d][%s] Failed to add extra data. error(%d)\\n", __LINE__, API_NAMESPACE, nRet);
                        app_control_destroy(app_control);
                        return nRet;
                }
        }

        nRet = app_control_send_launch_request_async(app_control,
                        AppControlResultAppCB, NULL, NULL);
        app_control_destroy(app_control);
        if (nRet != APP_CONTROL_ERROR_NONE) {
                FPRINTF("[Line : %d][%s] Failed to send launch request. error(%d)\\n", __LINE__, API_NAMESPACE, nRet);
                return nRet;
        }

        return 0;
}

/**
* @function         CommonWaitUntilDone
* @description      callback for waiting for specified operation
* @parameter        common_do_cb: callback , user_data : user data sent to callback
* @return           bool value
*/
bool CommonWaitUntilDone(common_do_cb callback, void *user_data)
{
        int retry_count = 0;

        do {
                if (callback(user_data))
                        return true;

                usleep(500);
                retry_count++;
        } while (retry_count <= 10);

        return false;
}

/** @} */
