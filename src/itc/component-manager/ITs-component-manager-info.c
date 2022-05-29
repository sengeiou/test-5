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
static component_info_h gComponentInfoHandle;

/** @addtogroup itc-component-manager
*  @ingroup itc
*  @{
*/

//& set: Component-manager

/**
* @function 		ITs_component_manager_info_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_component_manager_info_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_component_manager_info_startup\\n", __LINE__, API_NAMESPACE);
#endif

	TCT_CheckInstalledApp(1, "org.example.componentbased");
	g_bComponentManagerCreation = true;
}

/**
* @function 		ITs_component_manager_info_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_component_manager_info_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_component_manager_info_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
}


/** @addtogroup itc-component-manager-testcases
*  @brief 		Integration testcases for module component-manager
*  @ingroup 	itc-dlog
*  @{
*/

/**
* @testcase 			ITc_component_manager_create_destroy_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			To create and destroy component manager handle
* @scenario			create and destroy component manager handle
* @apicovered			component_info_create, component_info_destroy
* @passcase			When component_info_create and component_info_destroy successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API create and destroy component manager handle
//& type: auto
int ITc_component_manager_create_destroy_p(void)
{
	START_TEST;
	component_info_h hComponentInfoHandle = NULL;

	int nRet = component_info_create("org.example.frame-component", &hComponentInfoHandle);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_create", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hComponentInfoHandle, "component_info_create" );

	nRet = component_info_destroy(hComponentInfoHandle);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_destroy", ComponentManagerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_component_manager_info_get_app_id_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			To get component manager app id
* @scenario			To get component manager app id
* @apicovered			component_info_get_app_id
* @passcase			When Precondition and target API  successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			component manager handle should be created
* @postcondition		component manager handle should be destroyed
*/
//& purpose: API To get component manager app id
//& type: auto
int ITc_component_manager_info_get_app_id_p(void)
{
	START_TEST;
	component_info_h hComponentInfoHandle = NULL;
	char *pszAppID = NULL;

	int nRet = component_info_create("org.example.frame-component", &hComponentInfoHandle);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_create", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hComponentInfoHandle, "component_info_create");

	nRet = component_info_get_app_id(hComponentInfoHandle, &pszAppID);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_get_app_id", ComponentManagerGetError(nRet), component_info_destroy(hComponentInfoHandle));
	CHECK_HANDLE_CLEANUP(pszAppID, "component_info_get_app_id", component_info_destroy(hComponentInfoHandle));

	if (strcmp(pszAppID, "org.example.componentbased") != 0) {
                FPRINTF("[Line : %d][%s] get App ID %s and Set APP ID  %s is different\\n", __LINE__, API_NAMESPACE, pszAppID, "org.example.componentbased");
                free(pszAppID);
		component_info_destroy(hComponentInfoHandle);
                return 1;
        }

	nRet = component_info_destroy(hComponentInfoHandle);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_destroy", ComponentManagerGetError(nRet));

	free(pszAppID);

	return 0;
}

/**
* @testcase 			ITc_component_manager_info_get_component_id_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			To get component manager component id
* @scenario			to get component manager component id
* @apicovered			component_info_get_component_id
* @passcase			When Precondition and target API  successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			component manager handle should be created
* @postcondition		component manager handle should be destroyed
*/
//& purpose: To get component manager component id
//& type: auto
int ITc_component_manager_info_get_component_id_p(void)
{
	START_TEST;
	component_info_h hComponentInfoHandle = NULL;
	char *pszComponentID = NULL;

	int nRet = component_info_create("org.example.frame-component", &hComponentInfoHandle);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_create", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hComponentInfoHandle, "component_info_create");

	nRet = component_info_get_component_id(hComponentInfoHandle, &pszComponentID);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_get_component_id", ComponentManagerGetError(nRet), component_info_destroy(hComponentInfoHandle));
	CHECK_HANDLE_CLEANUP(pszComponentID, "component_info_get_component_id", component_info_destroy(hComponentInfoHandle));

	if (strcmp(pszComponentID, "org.example.frame-component") != 0) {
                FPRINTF("[Line : %d][%s] get Component ID %s and Set Component ID  %s is different\\n", __LINE__, API_NAMESPACE, pszComponentID, "org.example.frame-component");
                free(pszComponentID);
		component_info_destroy(hComponentInfoHandle);
                return 1;
        }

	nRet = component_info_destroy(hComponentInfoHandle);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_destroy", ComponentManagerGetError(nRet));

	free(pszComponentID);

	return 0;
}

/**
* @testcase 			ITc_component_manager_info_get_component_type_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			To get component manager component type
* @scenario			to get component manager component type
* @apicovered			component_info_get_component_type
* @passcase			When Precondition and target API  successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			component manager handle should be created
* @postcondition		component manager handle should be destroyed
*/
//& purpose: To get component manager component type
//& type: auto
int ITc_component_manager_info_get_component_type_p(void)
{
	START_TEST;
	component_info_h hComponentInfoHandle = NULL;
	component_info_component_type_e etype = -1;

	int nRet = component_info_create("org.example.frame-component", &hComponentInfoHandle);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_create", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hComponentInfoHandle, "component_info_create");

	nRet = component_info_get_component_type(hComponentInfoHandle, &etype);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_get_component_type", ComponentManagerGetError(nRet), component_info_destroy(hComponentInfoHandle));

	if (etype != COMPONENT_INFO_COMPONENT_TYPE_FRAME) {
                FPRINTF("[Line : %d][%s] get Component type and Set Component type is different\\n", __LINE__, API_NAMESPACE);
		component_info_destroy(hComponentInfoHandle);
                return 1;
        }

	nRet = component_info_destroy(hComponentInfoHandle);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_destroy", ComponentManagerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_component_manager_info_get_icon_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			To get component manager icon
* @scenario			to get component manager icon
* @apicovered			component_info_get_icon
* @passcase			When Precondition and target API  successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			component manager handle should be created
* @postcondition		component manager handle should be destroyed
*/
//& purpose: To get component manager component icon
//& type: auto
int ITc_component_manager_info_get_icon_p(void)
{
	START_TEST;
	char *pszComponentIcon = NULL;
	component_info_h hComponentInfoHandle = NULL;

	int nRet = component_info_create("org.example.frame-component", &hComponentInfoHandle);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_create", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hComponentInfoHandle, "component_info_create");

	nRet = component_info_get_icon(hComponentInfoHandle, &pszComponentIcon);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_get_icon", ComponentManagerGetError(nRet), component_info_destroy(hComponentInfoHandle));
	CHECK_HANDLE_CLEANUP(pszComponentIcon, "component_info_get_icon", component_info_destroy(hComponentInfoHandle));

	nRet = component_info_destroy(hComponentInfoHandle);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_destroy", ComponentManagerGetError(nRet));

	free(pszComponentIcon);

	return 0;
}

/**
* @testcase 			ITc_component_manager_info_get_localized_label_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			To get component manager localized_label
* @scenario			to get component manager localized_label
* @apicovered			component_info_get_localized_label
* @passcase			When Precondition and target API  successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			component manager handle should be created
* @postcondition		component manager handle should be destroyed
*/
//& purpose: To get component manager component localized_label
//& type: auto
int ITc_component_manager_info_get_localized_label_p(void)
{
	START_TEST;
	char *pszLocalizedLabel = NULL;
	component_info_h hComponentInfoHandle = NULL;

	int nRet = component_info_create("org.example.frame-component", &hComponentInfoHandle);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_create", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hComponentInfoHandle, "component_info_create");

	nRet = component_info_get_localized_label(hComponentInfoHandle, "ko-kr", &pszLocalizedLabel);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_get_localized_label", ComponentManagerGetError(nRet), component_info_destroy(hComponentInfoHandle));
	CHECK_HANDLE_CLEANUP(pszLocalizedLabel, "component_info_get_localized_label", component_info_destroy(hComponentInfoHandle));

	nRet = component_info_destroy(hComponentInfoHandle);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_destroy", ComponentManagerGetError(nRet));

	free(pszLocalizedLabel);

	return 0;
}

/**
* @testcase 			ITc_component_manager_info_clone_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			To clone component manager handle
* @scenario			clone component manager handle
* @apicovered			component_info_clone
* @passcase			hen Precondition and target API  successful
* @failcase			If target API fails or any precondition API fails
* @precondition			component manager handle should be created
* @postcondition		component manager handle should be destroyed
*/
//& purpose: API clone component info handle
//& type: auto
int ITc_component_manager_info_clone_p(void)
{
	START_TEST;
	component_info_h hComponentInfoHandle = NULL;
	component_info_h hCloneinfo = NULL;

	int nRet = component_info_create("org.example.frame-component", &hComponentInfoHandle);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_create", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hComponentInfoHandle, "component_info_create" );

	nRet = component_info_clone(&hCloneinfo, hComponentInfoHandle);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_clone", ComponentManagerGetError(nRet), component_info_destroy(hComponentInfoHandle));
	CHECK_HANDLE_CLEANUP(hCloneinfo, "component_info_clone", component_info_destroy(hComponentInfoHandle));

	nRet = component_info_destroy(hComponentInfoHandle);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_destroy", ComponentManagerGetError(nRet));

	nRet = component_info_destroy(hCloneinfo);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_destroy", ComponentManagerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_component_manager_info_is_icon_display_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			To check icon display status
* @scenario			To check icon display status
* @apicovered			 component_info_is_icon_display
* @passcase			When Precondition and target API  successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			component manager handle should be created
* @postcondition		component manager handle should be destroyed
*/
//& purpose: To check icon display status
//& type: auto
int ITc_component_manager_info_is_icon_display_p(void)
{
	START_TEST;
	bool isIconDisplay = false;
	component_info_h hComponentInfoHandle = NULL;

	int nRet = component_info_create("org.example.frame-component", &hComponentInfoHandle);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_create", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hComponentInfoHandle, "component_info_create");

	nRet = component_info_is_icon_display(hComponentInfoHandle, &isIconDisplay);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_is_icon_display", ComponentManagerGetError(nRet), component_info_destroy(hComponentInfoHandle));

	nRet = component_info_destroy(hComponentInfoHandle);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_destroy", ComponentManagerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_component_manager_info_is_managed_by_task_manager_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			Auto
* @description			To check weather it is managed by task manager
* @scenario			To check weather it is managed by task manager
* @apicovered			 component_info_is_managed_by_task_manager
* @passcase			When Precondition and target API  successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			component manager handle should be created
* @postcondition		component manager handle should be destroyed
*/
//& purpose: To check weather it is managed by task manager
//& type: auto
int ITc_component_manager_info_is_managed_by_task_manager_p(void)
{
	START_TEST;
	bool isManagedbyTask = false;
	component_info_h hComponentInfoHandle =  NULL;

	int nRet = component_info_create("org.example.frame-component", &hComponentInfoHandle);
	PRINT_RESULT(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_create", ComponentManagerGetError(nRet));
	CHECK_HANDLE(hComponentInfoHandle, "component_info_create");

	nRet = component_info_is_managed_by_task_manager(hComponentInfoHandle, &isManagedbyTask);
	PRINT_RESULT_CLEANUP(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_is_managed_by_task_manager", ComponentManagerGetError(nRet), component_info_destroy(hComponentInfoHandle));

	nRet = component_info_destroy(hComponentInfoHandle);
	PRINT_RESULT_NORETURN(COMPONENT_MANAGER_ERROR_NONE, nRet, "component_info_destroy", ComponentManagerGetError(nRet));

	return 0;
}

/** @} */
/** @} */
