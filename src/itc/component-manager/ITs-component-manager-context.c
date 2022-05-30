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
* @function 		ITs_component_manager_context_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/


void ITs_component_manager_context_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_component_manager_context_startup\\n", __LINE__, API_NAMESPACE);
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
* @function 		ITs_component_manager_context_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 		NA
*/
void ITs_component_manager_context_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_component_manager_context_startup\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @testcase 			ITc_component_manager_context_clone_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			Clone component context handle
* @scenario			Clone component context handle
* @apicovered			component_context_clone
* @passcase			When component_context_clone and Pre condition API successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		context handle should be destroy
*/
//& purpose: Clone component context handle
//& type: auto
int ITc_component_manager_context_clone_p(void)
{
	START_TEST;
	component_context_h hContext =  NULL;
	component_context_h cContext = NULL;

	int nRet = component_manager_get_component_context("org.example.frame-component", &hContext);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_get_component_context", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hContext, "component_manager_get_component_context");

	nRet = component_context_clone(&cContext, hContext);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_clone", ComponentManagerGetError(nRet),component_context_destroy(hContext));
	CHECK_HANDLE_CLEANUP(cContext, "component_context_clone", component_context_destroy(hContext));

	nRet = component_context_destroy(hContext);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_destroy", ComponentManagerGetError(nRet));

	nRet = component_context_destroy(cContext);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_destroy", ComponentManagerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_component_manager_component_context_get_app_id_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			Get Context APP ID
* @scenario			Get Context APP ID
* @apicovered			component_context_get_app_id
* @passcase			When component_context_get_app_id and Pre condition API successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		context handle should be destroy
*/
//& purpose: Get Context APP ID
//& type: auto
int ITc_component_manager_component_context_get_app_id_p(void)
{
	START_TEST;
	component_context_h hContext = NULL;
	char *pszAppID = NULL;

	int nRet = component_manager_get_component_context("org.example.frame-component", &hContext);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_get_component_context", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hContext, "component_manager_get_component_context");

	nRet = component_context_get_app_id(hContext, &pszAppID);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_get_app_id", ComponentManagerGetError(nRet),component_context_destroy(hContext));
	CHECK_HANDLE_CLEANUP(pszAppID, "component_context_get_app_id", component_context_destroy(hContext));

	if (strcmp(pszAppID, "org.example.componentbased") != 0) {
                FPRINTF("[Line : %d][%s] get App ID %s and Set APP ID  %s is different\\n", __LINE__, API_NAMESPACE, pszAppID, "org.example.componentbased");
                free(pszAppID);
		component_context_destroy(hContext);
                return 1;
        }

	nRet = component_context_destroy(hContext);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_destroy", ComponentManagerGetError(nRet));

	free(pszAppID);

	return 0;
}

/**
* @testcase 			ITc_component_manager_component_context_get_component_id_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			Get Context APP ID
* @scenario			Get Context APP ID
* @apicovered			component_context_get_component_id and Pre condition API successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		context handle should be destroy
*/
//& purpose: Get Context component ID
//& type: auto
int ITc_component_manager_component_context_get_component_id_p(void)
{
	START_TEST;
	component_context_h hContext = NULL;
	char *pszComponentID = NULL;

	int nRet = component_manager_get_component_context("org.example.frame-component", &hContext);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_get_component_context", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hContext, "component_manager_get_component_context");

	nRet = component_context_get_component_id(hContext, &pszComponentID);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_get_component_id", ComponentManagerGetError(nRet),component_context_destroy(hContext));
	CHECK_HANDLE_CLEANUP(pszComponentID, "component_context_get_component_id", component_context_destroy(hContext));

	if (strcmp(pszComponentID, "org.example.frame-component") != 0) {
                FPRINTF("[Line : %d][%s] get App ID %s and Set APP ID  %s is different\\n", __LINE__, API_NAMESPACE, pszComponentID, "org.example.frame-component");
                free(pszComponentID);
		component_context_destroy(hContext);
                return 1;
        }

	nRet = component_context_destroy(hContext);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_destroy", ComponentManagerGetError(nRet));

	free(pszComponentID);

	return 0;
}

/**
* @testcase 			ITc_component_manager_component_context_get_component_state_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			Get Context APP state
* @scenario			Get Context APP state
* @apicovered			component_context_get_component_state
* @passcase			When component_context_get_component_id and Pre condition API successful..
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		context handle should be destroy
*/
//& purpose: Get Context component state
//& type: auto
int ITc_component_manager_component_context_get_component_state_p(void)
{
	START_TEST;
	component_context_h hContext = NULL;
	component_state_e estate = COMPONENT_STATE_INITIALIZED;

	int nRet = component_manager_get_component_context("org.example.frame-component", &hContext);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_get_component_context", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hContext, "component_manager_get_component_context");

	nRet = component_context_get_component_state(hContext, &estate);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_get_component_state", ComponentManagerGetError(nRet),component_context_destroy(hContext));

	if (estate == COMPONENT_STATE_INITIALIZED) {
		FPRINTF("[Line : %d][%s] should not be `COMPONENT_STATE_INITIALIZED\\n", __LINE__, API_NAMESPACE);
		component_context_destroy(hContext);
                return 1;
        }


	nRet = component_context_destroy(hContext);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_destroy", ComponentManagerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_component_manager_component_context_get_instance_id_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			Get Context instance ID
* @scenario			Get Context instance ID
* @apicovered			component_context_get_instance_id
* @passcase			When component_context_get_instance_id and Pre condition API successful..
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		context handle should be destroy
*/
//& purpose: Get Context instance ID
//& type: auto
int ITc_component_manager_component_context_get_instance_id_p(void)
{
	START_TEST;
	component_context_h hContext = NULL;
	char *pszInstanceID = NULL;

	int nRet = component_manager_get_component_context("org.example.frame-component", &hContext);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_get_component_context", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hContext, "component_manager_get_component_context");

	nRet = component_context_get_instance_id(hContext, &pszInstanceID);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_get_instance_id", ComponentManagerGetError(nRet),component_context_destroy(hContext));
	CHECK_HANDLE_CLEANUP(pszInstanceID, "component_context_get_instance_id", component_context_destroy(hContext));

	nRet = component_context_destroy(hContext);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_destroy", ComponentManagerGetError(nRet));

	free(pszInstanceID);

	return 0;
}

/**
* @testcase 			ITc_component_manager_component_context_is_terminated__p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @scenario			Check weather context is terminated
* @apicovered			component_context_is_terminated
* @passcase			When component_context_is_terminated and Pre condition API successful..
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		context handle should be destroy
*/
//& purpose: Check weather context is terminated
//& type: auto
int ITc_component_manager_component_context_is_terminated_p(void)
{
	START_TEST;
	component_context_h hContext = NULL;
	bool isTerminated = NULL;

	int nRet = component_manager_get_component_context("org.example.frame-component", &hContext);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_get_component_context", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hContext, "component_manager_get_component_context");

	nRet = component_context_is_terminated(hContext, &isTerminated);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_is_terminated", ComponentManagerGetError(nRet),component_context_destroy(hContext));

	nRet = component_context_destroy(hContext);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_destroy", ComponentManagerGetError(nRet));

	return 0;
}


/**
* @testcase 			ITc_component_manager_component_context_is_subcomponent__p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @scenario			Check weather context is subcomponent
* @apicovered			component_context_is_subcomponent
* @passcase			When component_context_is_subcomponent and Pre condition API successful..
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		context handle should be destroy
*/
//& purpose: Check weather context is subcomponent
//& type: auto
int ITc_component_manager_component_context_is_subcomponent_p(void)
{
	START_TEST;
	component_context_h hContext = NULL;
	bool isSubComponent = false;

	int nRet = component_manager_get_component_context("org.example.frame-component", &hContext);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_manager_get_component_context", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hContext, "component_manager_get_component_context");

	nRet = component_context_is_subcomponent(hContext, &isSubComponent);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_is_subcomponent", ComponentManagerGetError(nRet),component_context_destroy(hContext));

	nRet = component_context_destroy(hContext);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_context_destroy", ComponentManagerGetError(nRet));

	return 0;
}



