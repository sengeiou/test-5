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

#include "ITs-notification-common.h"
/**
* @function 		NotiExItemGroupForeachChildCb
* @description	 	Callback Function
* @parameters		noti_ex_item_h hItem, void *pszData
* @return 		int
*/
static int NotiExItemGroupForeachChildCb(noti_ex_item_h hItem, void *pszData)
{
	int nRet;
	char *pszGetID = NULL;
	g_CallBackHit = false;

	FPRINTF("[Line : %d][%s] NotiExItemGroupForeachChildCb Callback Invoked\\n", __LINE__, API_NAMESPACE);
	g_CallBackHit = true;

	nRet = noti_ex_item_get_id(hItem, &pszGetID);
	if (nRet != NOTI_EX_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Error in running API noti_ex_item_get_id\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( strncmp(pszGetID, g_pszButtonID, strlen(g_pszButtonID) + 1) )
	{
		FPRINTF("[Line : %d][%s] Chiled id [%s] but recieved id is [%s] \\n", __LINE__, API_NAMESPACE, g_pszButtonID, pszGetID);
		return 1;
	}
	return 0;
}
/**
* @function		ITs_notification_ex_group_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_group_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_group_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_group_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_group_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_group_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type : auto
//& purpose: Creates the group of notification_ex items and destroys it.
/**
* @testcase			ITc_noti_ex_item_group_create_destroy_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates the notification_ex item handle for an group item.
* @scenario			Create the group item and set ID and destroy \n
* @apicovered			noti_ex_item_group_create, noti_ex_item_destroy
* @passcase			noti_ex_item_group_create, noti_ex_item_destroy are successful and return correct value
* @failcase			noti_ex_item_group_create, noti_ex_item_destroy failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_group_create_destroy_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemGroup = NULL;
	const char *pszGroupID = "group_id";

	//Target API
	nRet = noti_ex_item_group_create(&hItemGroup, pszGroupID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemGroup, "noti_ex_item_group_create");

	nRet = noti_ex_item_destroy(hItemGroup);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets the direction of children in the group item and Gets the vertical state of group item.
/**
* @testcase			ITc_noti_ex_item_group_set_direction_is_vertical_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets the direction of children in the group item and Gets the vertical state of group item
* @scenario			Set child direction and get vertical state \n
*				Compare set and returned state and check for Pass/Fail.
* @apicovered			noti_ex_item_group_set_direction, noti_ex_item_group_is_vertical
* @passcase			noti_ex_item_group_set_direction, noti_ex_item_group_is_vertical are successful and return correct value
* @failcase			noti_ex_item_group_set_direction, noti_ex_item_group_is_vertical failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_group_set_direction_is_vertical_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemGroup = NULL;
	const char *pszGroupID = "group_id";
	bool bSetVertical = true;
	bool bisVertical = false;

	nRet = noti_ex_item_group_create(&hItemGroup, pszGroupID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemGroup, "noti_ex_item_group_create");

	//Target API
	nRet = noti_ex_item_group_set_direction(hItemGroup, bSetVertical);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_set_direction", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup));

	//Target API
	nRet = noti_ex_item_group_is_vertical(hItemGroup, &bisVertical);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_is_vertical", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup));
	PRINT_RESULT_CLEANUP(bSetVertical, bisVertical, "noti_ex_item_group_is_vertical", "return state is not matching", noti_ex_item_destroy(hItemGroup));

	nRet = noti_ex_item_destroy(hItemGroup);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the label of application.
/**
* @testcase			ITc_noti_ex_item_group_get_app_label_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the label of application.
* @scenario			Create group item and set label and check for Pass/Fail.
* @apicovered			noti_ex_item_group_get_app_label
* @passcase			noti_ex_item_group_get_app_label is successful and return correct value
* @failcase			noti_ex_item_group_get_app_label failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_group_get_app_label_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemGroup = NULL;
	const char *pszGroupID = "group_id";
	char *pszGetAppLabel = NULL;

	nRet = noti_ex_item_group_create(&hItemGroup, pszGroupID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemGroup, "noti_ex_item_group_create");

	//Target API
	nRet = noti_ex_item_group_get_app_label(hItemGroup, &pszGetAppLabel);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_get_app_label", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup));
	CHECK_HANDLE_CLEANUP(pszGetAppLabel, "noti_ex_item_group_get_app_label", noti_ex_item_destroy(hItemGroup));

	FPRINTF("[Line : %d][%s] noti_ex_item_group_get_app_label: return app label is [%s]\\n", __LINE__, API_NAMESPACE, pszGetAppLabel);
	FREE_MEMORY(pszGetAppLabel);

	nRet = noti_ex_item_destroy(hItemGroup);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Adds and remove the child to and from the group item.
/**
* @testcase			ITc_noti_ex_item_group_add_remove_child_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Adds and remove the child to and from the group item.
* @scenario			Create group item, create child item\n
*				Add chile item and remove child item and check for Pass/Fail.
* @apicovered			noti_ex_item_group_add_child, noti_ex_item_group_remove_child
* @passcase			noti_ex_item_group_add_child, noti_ex_item_group_remove_child are successful and return correct value
* @failcase			noti_ex_item_group_add_child, noti_ex_item_group_remove_child failed or return null value
* @precondition			Create button and add child.
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_group_add_remove_child_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemGroup = NULL;
	const char *pszGroupID = "group_id";

	nRet = noti_ex_item_group_create(&hItemGroup, pszGroupID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemGroup, "noti_ex_item_group_create");

	nRet = CreateButton();
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup));
	CHECK_HANDLE_CLEANUP(g_hItemButton, "noti_ex_item_button_create", noti_ex_item_destroy(hItemGroup));

	//Target API
	nRet = noti_ex_item_group_add_child(hItemGroup, g_hItemButton);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_add_child", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_group_remove_child(hItemGroup, g_pszButtonID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_remove_child", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(hItemGroup);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));
	return 0;
}

//& type : auto
//& purpose: Gets the data of children from the group item.
/**
* @testcase			ITc_noti_ex_item_group_foreach_child_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the data of children from the group item.
* @scenario			Create group item, create child item\n
*				Register callback, check for callback hit and check for Pass/Fail.
* @apicovered			noti_ex_item_group_foreach_child
* @passcase			noti_ex_item_group_foreach_child is successful and return correct value
* @failcase			noti_ex_item_group_foreach_child failed or return null value
* @precondition			Create button, add button as child,
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_group_foreach_child_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemGroup = NULL;
	const char *pszGroupID = "group_id";

	nRet = noti_ex_item_group_create(&hItemGroup, pszGroupID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemGroup, "noti_ex_item_group_create");

	nRet = CreateButton();
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup));
	CHECK_HANDLE_CLEANUP(g_hItemButton, "noti_ex_item_button_create", noti_ex_item_destroy(hItemGroup));

	nRet = noti_ex_item_group_add_child(hItemGroup, g_hItemButton);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_add_child", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(g_hItemButton));

	g_CallBackHit = false;

	//Target API
	nRet = noti_ex_item_group_foreach_child(hItemGroup, NotiExItemGroupForeachChildCb, NULL);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_foreach_child", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(g_hItemButton));

	if(!g_CallBackHit)
	{
		FPRINTF("[Line : %d][%s] NotiExItemGroupForeachChildCb Callback not hit\\n", __LINE__, API_NAMESPACE);

		nRet = noti_ex_item_destroy(g_hItemButton);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		nRet = noti_ex_item_destroy(hItemGroup);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(hItemGroup);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));
	return 0;
}
