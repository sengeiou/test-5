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
bool g_CallbackComponent = false;

/** @addtogroup itc-component-manager
*  @ingroup itc
*  @{
*/

/**
* @function 		IsComponentManagerRunning
* @description	 	To check weather component manager running
* @parameter		edata : user data sent to function
* @return 		Status of component manager weather its running or not(True/False)
*/
static bool IsComponentManagerRunning(void *data)
{
        bool isRunning = false;

        component_manager_is_running("org.example.frame-component", &isRunning);
        if (isRunning) {
		FPRINTF("[Line : %d][%s] component is running\\n", __LINE__, API_NAMESPACE);
                return true;
        }

        return false;
}

/**
* @function 		ComponentInfoCB
* @description	 	callback for foreach component info
* @parameter		info: component info handle,data : user data sent to function
* @return 		Callback which will call and return status of callback
*/
static bool ComponentInfoCB(component_info_h info, void *data)
{
        bool *isMatched = (bool *)data;
        char *pszComponentID =  NULL;
	g_CallbackComponent = true;

	FPRINTF("[Line : %d][%s] Inside callback ComponentInfoCB\\n", __LINE__, API_NAMESPACE);

        int nRet = component_info_get_component_id(info, &pszComponentID);
        if (nRet != COMPONENT_MANAGER_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] Failed to get component ID. error(%d)\\n", __LINE__, API_NAMESPACE, nRet);
		 FREE_MEMORY(pszComponentID);
                return false;
        }

        if (!strcmp(pszComponentID, "org.example.frame-component")) {
		FPRINTF("[Line : %d][%s] Matched\\n", __LINE__, API_NAMESPACE);
                *isMatched = true;
                FREE_MEMORY(pszComponentID);
                return false;
        }
	
        FREE_MEMORY(pszComponentID);

        return true;
}

/**
* @function 		ComponentContextCB
* @description	 	callback for foreach component context
* @parameter		info: component context handle,data : user data sent to function
* @return 		Callback which will call and return status of callback
*/
static bool ComponentContextCB(component_context_h context, void *data)
{
        bool *matched = (bool *)data;
        char *pszComponentID = NULL;
	g_CallbackComponent = true;

	FPRINTF("[Line : %d][%s] Inside callback ComponentContextCB\\n", __LINE__, API_NAMESPACE);
        int nRet = component_context_get_component_id(context, &pszComponentID);
        if (nRet != COMPONENT_MANAGER_ERROR_NONE) {
                FPRINTF("[Line : %d][%s] Failed to get component ID. error(%d)\\n", __LINE__, API_NAMESPACE, nRet);
		FREE_MEMORY(pszComponentID);
                return false;
        }

        if (!strcmp(pszComponentID, "org.example.frame-component")) {
                FPRINTF("[Line : %d][%s] Matched\\n", __LINE__, API_NAMESPACE);
                *matched = true;
               FREE_MEMORY(pszComponentID);
                return false;
        }

        FREE_MEMORY(pszComponentID);

        return true;
}

//& set: Component-manager

/**
* @function 		ITs_component_manager_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/

void ITs_component_manager_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_component_manager_startup\\n", __LINE__, API_NAMESPACE);
#endif

	TCT_CheckInstalledApp(1, "org.example.componentbased");
	int nRet = AppControlCommonLaunchRequest("org.example.componentbased",
                        "org.example.frame-component", NULL);
        if (nRet < 0) {
                FPRINTF("[Line : %d][%s] Failed to send launch request\\n", __LINE__, API_NAMESPACE);
		g_bComponentManagerCreation = false;
                return;
        }

        if(CommonWaitUntilDone(IsComponentManagerRunning, NULL))
		g_bComponentManagerCreation = true;
}

/**
* @function 		ITs_component_manager_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_component_manager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_component_manager_startup\\n", __LINE__, API_NAMESPACE);
#endif
}

/** @addtogroup itc-component-manager-testcases
*  @brief 		Integration testcases for module component-manager
*  @ingroup 	itc-dlog
*  @{
*/

/**
* @testcase 			ITc_component_manager_is_running_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			To Check weather component manager running
* @scenario			To Check weather component manager running
* @apicovered			component_manager_is_running
* @passcase			When component_manager_is_running successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To Check weather component manager running
//& type: auto
int ITc_component_manager_is_running_p(void)
{
	START_TEST;
	bool isRunning = false;
	int nRet = component_manager_is_running("org.example.frame-component", &isRunning);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_is_running", ComponentManagerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_component_manager_get_component_info_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			Get Component manager component info handle
* @scenario			Get Component manager component info handle
* @apicovered			ccomponent_manager_get_component_info
* @passcase			When component_manager_is_running successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		Info handle should be destroy
*/
//& purpose: Get Component manager component info handle
//& type: auto
int ITc_component_manager_get_component_info_p(void)
{
	START_TEST;
	component_info_h hinfo;

	int nRet = component_manager_get_component_info("org.example.frame-component", &hinfo);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_get_component_info", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hinfo, "component_manager_get_component_info");

	nRet = component_info_destroy(hinfo);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_destroy", ComponentManagerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_component_manager_get_component_context_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			Get Component manager component info context
* @scenario			Get Component manager component info context
* @apicovered			component_manager_get_component_context
* @passcase			When component_manager_get_component_context successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		context handle should be destroy
*/
//& purpose: Get Component manager component info context
//& type: auto
int ITc_component_manager_get_component_context_p(void)
{
	START_TEST;
	component_context_h hContext;

	int nRet = component_manager_get_component_context("org.example.frame-component", &hContext);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_get_component_context", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hContext, "component_manager_get_component_context");

	nRet = component_context_destroy(hContext);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_destroy", ComponentManagerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_component_manager_resume_component_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			Resume Component Manager Component
* @scenario			Resume Component Manager Component
* @apicovered			component_manager_resume_component
* @passcase			When component_manager_resume_component and Precondition API successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		context handle should be destroy
*/
//& purpose: Resume Component Manager Component
//& type: auto
int ITc_component_manager_resume_component_p(void)
{
	START_TEST;
	component_context_h hContext;

	int nRet = component_manager_get_component_context("org.example.frame-component", &hContext);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_get_component_context", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hContext, "component_manager_get_component_context");

	nRet = component_manager_resume_component(hContext);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_resume_component", ComponentManagerGetError(nRet), component_context_destroy(hContext));

	nRet = component_context_destroy(hContext);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_destroy", ComponentManagerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_component_manager_terminate_bg_component_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			Terminate Component Manager Bg Component
* @scenario			Terminate Component Manager Bg Component
* @apicovered			component_manager_terminate_bg_component
* @passcase			When component_manager_terminate_bg_component and Precondition API successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		context handle should be destroy
*/
//& purpose: Terminate Component Manager Bg Component
//& type: auto
int ITc_component_manager_terminate_bg_component_p(void)
{
	START_TEST;
	component_context_h hContext;

	int nRet = component_manager_get_component_context("org.example.frame-component", &hContext);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_get_component_context", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hContext, "component_manager_get_component_context");

	nRet = component_manager_terminate_bg_component(hContext);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_terminate_bg_component", ComponentManagerGetError(nRet), component_context_destroy(hContext));

	nRet = component_context_destroy(hContext);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_destroy", ComponentManagerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_component_manager_foreach_component_info_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			To Foreach Component manager info
* @scenario			To Foreach Component manager info
* @apicovered			component_manager_foreach_component_info
* @passcase			When component_manager_foreach_component_info successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: To Foreach Component manager info
//& type: auto
int ITc_component_manager_foreach_component_info_p(void)
{
	START_TEST;
	bool isMatched = false;

	g_CallbackComponent = false;
	int nRet = component_manager_foreach_component_info(ComponentInfoCB, (void *)&isMatched);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_foreach_component_info", ComponentManagerGetError(nRet));
	PRINT_RESULT(g_CallbackComponent, true, "callback not invoked for component_manager_foreach_component_info API", ComponentManagerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_component_manager_foreach_component_context_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			To Foreach Component manager context
* @scenario			To Foreach Component manager context
* @apicovered			component_manager_foreach_component_context
* @passcase			When component_manager_foreach_component_context successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: To Foreach Component manager context
//& type: auto
int ITc_component_manager_foreach_component_context_p(void)
{
	START_TEST;
	bool isMatched = false;

	g_CallbackComponent = false;
	int nRet = component_manager_foreach_component_context(ComponentContextCB, (void *)&isMatched);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_foreach_component_context", ComponentManagerGetError(nRet));
	PRINT_RESULT(g_CallbackComponent, true, "callback not invoked for component_manager_foreach_component_context API", ComponentManagerGetError(nRet));

	return 0;
}
