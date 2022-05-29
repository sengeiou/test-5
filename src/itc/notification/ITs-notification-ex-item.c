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
#include "ITs-notification-common.h"
/**
* @function		ITs_notification_ex_item_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_item_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_item_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_item_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_item_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_item_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	itc-notification-ex-testcases
* @brief 		Integration testcases for module notification-ex
* @ingroup		itc-notification-ex
* @{
*/


//& type : auto
//& purpose: Gets the type of an action. The action type is equal to one of the values of #noti_ex_action_type_e.
/**
* @testcase			ITc_noti_ex_action_get_type_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the type of an action. The action type is equal to one of the values of #noti_ex_action_type_e.
* @scenario			Creates the notification_ex action handle and Gets the type of an action\n
*				Check for Pass/Fail.
* @apicovered			noti_ex_action_get_type
* @passcase			noti_ex_action_get_type is successful and return correct value
* @failcase			noti_ex_action_get_type failed or return null value
* @precondition			NA.
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_action_get_type_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_action_h hAction = NULL;
	const char* pszExtra = "extra";
	int nType;

	nRet = noti_ex_action_visibility_create(&hAction, pszExtra);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_visibility_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hAction, "noti_ex_action_visibility_create");

	//Target API
	nRet = noti_ex_action_get_type(hAction, &nType);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_get_type", NotificationExGetError(nRet), noti_ex_action_destroy(hAction));
	PRINT_RESULT_CLEANUP(NOTI_EX_ACTION_TYPE_VISIBILITY, nType, "noti_ex_action_get_type", "return type of action handle is different", noti_ex_action_destroy(hAction));

	nRet = noti_ex_action_destroy(hAction);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the local state of an action.
/**
* @testcase			ITc_noti_ex_action_is_local_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the local state of an action.
* @scenario			Creates the notification_ex action handle and Gets the local state of an action\n
*				Check for Pass/Fail.
* @apicovered			noti_ex_action_is_local
* @passcase			noti_ex_action_is_local is successful and return correct value
* @failcase			noti_ex_action_is_local failed or return null value
* @precondition			NA.
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_action_is_local_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_action_h hAction = NULL;
	bool bIsLocal = false;

	nRet = noti_ex_action_visibility_create(&hAction, NULL);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_visibility_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hAction, "noti_ex_action_visibility_create");

	//Target API
	nRet = noti_ex_action_is_local(hAction, &bIsLocal);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_is_local", NotificationExGetError(nRet), noti_ex_action_destroy(hAction));
	PRINT_RESULT_CLEANUP(true, bIsLocal, "noti_ex_action_is_local", "bIsLocal is not set true", noti_ex_action_destroy(hAction));

	nRet = noti_ex_action_destroy(hAction);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Executes the action for a notification_ex item.
/**
* @testcase			ITc_noti_ex_action_execute_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Executes the action for a notification_ex item.
* @scenario			Creates the notification_ex action handle and Executes the action \n
*				for a notification_ex item. Check for Pass/Fail.
* @apicovered			noti_ex_action_execute
* @passcase			noti_ex_action_execute is successful and return correct value
* @failcase			noti_ex_action_execute failed or return null value
* @precondition			NA.
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_action_execute_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_action_h hAction = NULL;

	nRet = noti_ex_action_visibility_create(&hAction, NULL);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_visibility_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hAction, "noti_ex_action_visibility_create");

	nRet = CreateButton();
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), noti_ex_action_destroy(hAction));
	CHECK_HANDLE_CLEANUP(g_hItemButton, "noti_ex_item_button_create", noti_ex_action_destroy(hAction));

	nRet = noti_ex_item_set_action(g_hItemButton, hAction);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_action", NotificationExGetError(nRet), noti_ex_action_destroy(hAction); noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_action_execute(hAction, g_hItemButton);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_execute", NotificationExGetError(nRet), noti_ex_action_destroy(hAction); noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_action_destroy(hAction);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the extra data for an action.
/**
* @testcase			ITc_noti_ex_action_get_extra_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the extra data for an action.
* @scenario			Creates the notification_ex action handle and Gets the extra data\n
*				for an action. Check for Pass/Fail.
* @apicovered			noti_ex_action_get_extra
* @passcase			noti_ex_action_get_extra is successful and return correct value
* @failcase			noti_ex_action_get_extra failed or return null value
* @precondition			NA.
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_action_get_extra_p(void)
{
	START_TEST;

        int nRet = NOTI_EX_ERROR_NONE;

        noti_ex_action_h hAction = NULL;
        const char* pszSetExtra = "test";
        char* pszGetExtra = NULL;

	nRet = noti_ex_action_visibility_create(&hAction, pszSetExtra);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_visibility_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hAction, "noti_ex_action_visibility_create");

	//Target API
	nRet = noti_ex_action_get_extra(hAction, &pszGetExtra);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_get_extra", NotificationExGetError(nRet), noti_ex_action_destroy(hAction));
	CHECK_HANDLE_CLEANUP(pszGetExtra, "noti_ex_action_get_extra", noti_ex_action_destroy(hAction));

	if (strncmp(pszSetExtra, pszGetExtra, strlen(pszGetExtra) + 1))
	{
		FPRINTF("[Line : %d][%s] noti_ex_action_get_extra: return extra string is different from set extra [%s]\\n", __LINE__, API_NAMESPACE, pszGetExtra);

		nRet = noti_ex_action_destroy(hAction);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_destroy", NotificationExGetError(nRet));

		return 1;
	}

	nRet = noti_ex_action_destroy(hAction);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_destroy", NotificationExGetError(nRet));

	return 0;
}


//& type : auto
//& purpose: Finds the notification_ex item handle by notification_ex item id.
/**
* @testcase			ITc_noti_ex_item_find_by_id_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Finds the notification_ex item handle by notification_ex item id.
* @scenario			Creates the group of notification_ex items, create child item and add to group.\n
*				Find  item by ID, compare IDs and check for Pass/Fail.
* @apicovered			noti_ex_item_find_by_id
* @passcase			noti_ex_item_find_by_id is successful and return correct value
* @failcase			noti_ex_item_find_by_id failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_find_by_id_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemGroup = NULL;
	noti_ex_item_h hItemFind = NULL;

	const char *pszGroupID = "group_id";

	char *pszGetFindItemID = NULL;
	char *pszGetButtonItemID = NULL;

	nRet = noti_ex_item_group_create(&hItemGroup, pszGroupID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemGroup, "noti_ex_item_group_create");

	nRet = CreateButton();
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup));
	CHECK_HANDLE_CLEANUP(g_hItemButton, "noti_ex_item_button_create", noti_ex_item_destroy(hItemGroup));

	nRet = noti_ex_item_group_add_child(hItemGroup, g_hItemButton);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_add_child", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_find_by_id(hItemGroup, g_pszButtonID, &hItemFind);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_find_by_id", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(hItemFind, "noti_ex_item_find_by_id", noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_get_id(hItemFind, &pszGetFindItemID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_id", NotificationExGetError(nRet));
	CHECK_HANDLE_CLEANUP(pszGetFindItemID, "noti_ex_item_get_id", noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_get_id(g_hItemButton, &pszGetButtonItemID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_id", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton); FREE_MEMORY(pszGetFindItemID););
	CHECK_HANDLE_CLEANUP(pszGetButtonItemID, "noti_ex_item_get_id", noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(g_hItemButton));

	if( strncmp(pszGetButtonItemID, pszGetFindItemID, strlen(pszGetFindItemID) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_find_by_id: return item ID is different from set item ID [%s]\\n", __LINE__, API_NAMESPACE, pszGetFindItemID);
		FREE_MEMORY(pszGetFindItemID);
		FREE_MEMORY(pszGetButtonItemID);

		nRet = noti_ex_item_destroy(hItemGroup);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		nRet = noti_ex_item_destroy(g_hItemButton);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszGetFindItemID);
	FREE_MEMORY(pszGetButtonItemID);

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(hItemGroup);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));
	return 0;
}

//& type : auto
//& purpose: Gets the type of notification_ex item.
/**
* @testcase			ITc_noti_ex_item_get_type_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the type of notification_ex item.
* @scenario			Creates the notification_ex item, get the item type.\n
*				Compare type with created item and check for Pass/Fail.
* @apicovered			noti_ex_item_get_type
* @passcase			noti_ex_item_get_type is successful and return correct value
* @failcase			noti_ex_item_get_type failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_get_type_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_item_type_e eItemType = NOTI_EX_ITEM_TYPE_BUTTON;
	int nGetType;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	//Target API
	nRet = noti_ex_item_get_type(g_hItemButton, &nGetType);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_type", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	PRINT_RESULT_CLEANUP(eItemType, nGetType, "noti_ex_item_get_type", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and Gets the id of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_set_get_id_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and Gets the id of a notification_ex item.
* @scenario			Creates the notification_ex item, set item id and get item id.\n
*				Compare ids and check for Pass/Fail.
* @apicovered			noti_ex_item_set_id, noti_ex_item_get_id
* @passcase			noti_ex_item_set_id, noti_ex_item_get_id are successful and return correct value
* @failcase			noti_ex_item_set_id, noti_ex_item_get_id failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_set_get_id_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	const char *pszSetItemID = "testID";
	char *pszGetItemID = NULL;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	//Target API
	nRet = noti_ex_item_set_id(g_hItemButton, pszSetItemID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_id", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_get_id(g_hItemButton, &pszGetItemID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_id", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(pszGetItemID, "noti_ex_item_get_id", noti_ex_item_destroy(g_hItemButton));

	if( strncmp(pszSetItemID, pszGetItemID, strlen(pszGetItemID) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_get_id: return item ID is different from set item ID [%s]\\n", __LINE__, API_NAMESPACE, pszGetItemID);
		FREE_MEMORY(pszGetItemID);

		nRet = noti_ex_item_destroy(g_hItemButton);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszGetItemID);

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and Gets the action of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_set_get_action_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and Gets the action of a notification_ex item.
* @scenario			Creates the notification_ex action, create button, set item action and get item action.\n
*				Check get action handle and check for Pass/Fail.
* @apicovered			noti_ex_item_set_action, noti_ex_item_get_action
* @passcase			noti_ex_item_set_action, noti_ex_item_get_action are successful and return correct value
* @failcase			noti_ex_item_set_action, noti_ex_item_get_action failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_set_get_action_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_action_h hSetAction = NULL;
	noti_ex_action_h hGetAction = NULL;
	const char *pszSetExtra = "test";

	nRet = noti_ex_action_visibility_create(&hSetAction, pszSetExtra);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_action_visibility_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hSetAction, "noti_ex_action_visibility_create");

	nRet = CreateButton();
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), noti_ex_action_destroy(hSetAction));
	CHECK_HANDLE_CLEANUP(g_hItemButton, "noti_ex_item_button_create", noti_ex_action_destroy(hSetAction));

	//Target API
	nRet = noti_ex_item_set_action(g_hItemButton, hSetAction);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_action", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton); noti_ex_action_destroy(hSetAction));

	//Target API
	nRet = noti_ex_item_get_action(g_hItemButton, &hGetAction);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_action", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton); noti_ex_action_destroy(hSetAction));
	CHECK_HANDLE_CLEANUP(hGetAction, "noti_ex_item_get_action", noti_ex_item_destroy(g_hItemButton); noti_ex_action_destroy(hSetAction));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and Gets the style of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_set_get_style_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and Gets the action of a notification_ex item.
* @scenario			Creates the notification_ex style, set item style and get item style.\n
*				Get Padding from style and compare with set padding and check for Pass/Fail.
* @apicovered			noti_ex_item_set_style, noti_ex_item_get_style
* @passcase			noti_ex_item_set_style, noti_ex_item_get_style are successful and return correct value
* @failcase			noti_ex_item_set_style, noti_ex_item_get_style failed or return null value
* @precondition			NA
* @postcondition		Destroy handles.
*/
int ITc_noti_ex_item_set_get_style_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_style_h hGetStyle = NULL;
	noti_ex_padding_h hGetPadding = NULL;
	int nGetLeft, nGetTop, nGetRight, nGetBottom;

	nRet = CreateStyleAttributes();
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the prerequisite API inside CreateStyleAttributes() is failed \\n", __LINE__, API_NAMESPACE);
		return 1;

	}

	nRet = CreateButton();
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), DestroyStyleAttributes());
	CHECK_HANDLE_CLEANUP(g_hItemButton, "noti_ex_item_button_create", DestroyStyleAttributes());

	//Target API
	nRet = noti_ex_item_set_style(g_hItemButton, g_hStyle);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), DestroyStyleAttributes());

	//Target API
	nRet = noti_ex_item_get_style(g_hItemButton, &hGetStyle);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), DestroyStyleAttributes());
	CHECK_HANDLE_CLEANUP(hGetStyle, "noti_ex_item_button_create", DestroyStyleAttributes());

	nRet = noti_ex_style_get_padding(hGetStyle, &hGetPadding);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), DestroyStyleAttributes());

	nRet = noti_ex_padding_get_left(hGetPadding, &nGetLeft);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_get_left", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_nLeft, nGetLeft, "noti_ex_padding_get_left", "g_nLeft and nGetLeft are not same", DestroyStyleAttributes());

	nRet = noti_ex_padding_get_top(hGetPadding, &nGetTop);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_get_top", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_nTop, nGetTop, "noti_ex_padding_get_top", "g_nTop and nGetTop are not same", DestroyStyleAttributes());

	nRet = noti_ex_padding_get_right(hGetPadding, &nGetRight);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_get_right", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_nRight, nGetRight, "noti_ex_padding_get_right", "g_nRight and nGetRight are not same", DestroyStyleAttributes());

	nRet = noti_ex_padding_get_bottom(hGetPadding, &nGetBottom);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_get_bottom", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_nBottom, nGetBottom, "noti_ex_padding_get_bottom", "g_nBottom and nGetBottom are not same", DestroyStyleAttributes());

	DestroyStyleAttributes();
	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and Gets the visibility state of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_set_get_visible_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and Gets the visibility state of a notification_ex item.
* @scenario			Creates the notification_ex button, set item visibility and get item visibility.\n
*				compare the get visiblity wiht set visibility and check for Pass/Fail.
* @apicovered			noti_ex_item_set_visible, noti_ex_item_get_visible
* @passcase			noti_ex_item_set_visible, noti_ex_item_get_visible are successful and return correct value
* @failcase			noti_ex_item_set_visible, noti_ex_item_get_visible failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_set_get_visible_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	bool bSetVisible = true;
	bool bIsVisible = false;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	//Target API
	nRet = noti_ex_item_set_visible(g_hItemButton, bSetVisible);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_visible", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_get_visible(g_hItemButton, &bIsVisible);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_visible", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	PRINT_RESULT_CLEANUP(bSetVisible, bIsVisible, "noti_ex_item_get_visible", "get visible return state is not same as set visible state", noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and Gets the enabled state of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_set_get_enable_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and Gets the enable state of a notification_ex item.
* @scenario			Creates the notification_ex button, set item enable state and get item enable state.\n
*				compare the get enable state with set enable state and check for Pass/Fail.
* @apicovered			noti_ex_item_set_enable, noti_ex_item_get_enable
* @passcase			noti_ex_item_set_enable, noti_ex_item_get_enable are successful and return correct value
* @failcase			noti_ex_item_set_enable, noti_ex_item_get_enable failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_set_get_enable_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	bool bSetEnable = true;
	bool bIsEnable = false;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	//Target API
	nRet = noti_ex_item_set_enable(g_hItemButton, bSetEnable);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_enable", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_get_enable(g_hItemButton, &bIsEnable);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_enable", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	PRINT_RESULT_CLEANUP(bSetEnable, bIsEnable, "noti_ex_item_get_enable", "get enable return state is not same as set enable state", noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Adds and removes the receiver group of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_add_remove_receiver_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Adds and removes the receiver group of a notification_ex item.
* @scenario			Creates the notification_ex button, add reciever and remove reciever.\n
*				get reciever list and compate with set reciever count and check for Pass/Fail.
* @apicovered			noti_ex_item_add_receiver, noti_ex_item_remove_receiver
* @passcase			noti_ex_item_add_receiver, noti_ex_item_remove_receiver are successful and return correct value
* @failcase			noti_ex_item_add_receiver, noti_ex_item_remove_receiver failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_add_remove_receiver_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	char **pszGetList = NULL;
	const char* pszRecvOne = "TestRecv1";
	const char* pszRecvTwo = "TestRecv2";
	int nGetRecvCnt;
	int nSetRecvCnt = 2;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	//Target API
	nRet = noti_ex_item_add_receiver(g_hItemButton, pszRecvOne);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_add_receiver", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_add_receiver(g_hItemButton, pszRecvTwo);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_add_receiver", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_get_receiver_list(g_hItemButton, &pszGetList, &nGetRecvCnt);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_receiver_list", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	PRINT_RESULT_CLEANUP(nSetRecvCnt, nGetRecvCnt, "noti_ex_item_get_receiver_list", "returned different value of receiver", noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_remove_receiver(g_hItemButton, pszRecvOne);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_remove_receiver", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	nSetRecvCnt = 1;

	nRet = noti_ex_item_get_receiver_list(g_hItemButton, &pszGetList, &nGetRecvCnt);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_receiver_list", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	PRINT_RESULT_CLEANUP(nSetRecvCnt, nGetRecvCnt, "noti_ex_item_get_receiver_list", "noti_ex_item_remove_receiver does not work and returned diffrent value of reciever", noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the list of receiver group of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_get_receiver_list_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the list of receiver group of a notification_ex item.
* @scenario			Creates the notification_ex button, add reciever and get the reciever list.\n
*				Compate with set reciever count and check for Pass/Fail.
* @apicovered			noti_ex_item_get_receiver_list
* @passcase			noti_ex_item_get_receiver_list is successful and return correct value
* @failcase			noti_ex_item_get_receiver_list failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_get_receiver_list_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	char **pszGetList = NULL;
	const char* pszRecvOne = "TestRecv1";
	const char* pszRecvTwo = "TestRecv2";
	int nGetRecvCnt;
	int nSetRecvCnt = 2;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	nRet = noti_ex_item_add_receiver(g_hItemButton, pszRecvOne);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_add_receiver", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_add_receiver(g_hItemButton, pszRecvTwo);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_add_receiver", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_get_receiver_list(g_hItemButton, &pszGetList, &nGetRecvCnt);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_receiver_list", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	PRINT_RESULT_CLEANUP(nSetRecvCnt, nGetRecvCnt, "noti_ex_item_get_receiver_list", "returned different value of receiver", noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(pszGetList, "noti_ex_item_get_receiver_list", noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and gets the policy of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_get_receiver_list_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and gets the policy of a notification_ex item.
* @scenario			Creates the notification_ex button, Set different policies of type noti_ex_item_policy_e.\n
*				get policy and compare with set policy and check for Pass/Fail.
* @apicovered			noti_ex_item_set_policy, noti_ex_item_get_policy
* @passcase			noti_ex_item_set_policy, noti_ex_item_get_policy are successful and return correct value
* @failcase			noti_ex_item_set_policy, noti_ex_item_get_policy failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_set_get_policy_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	int nGetPolicy;

	noti_ex_item_policy_e eSetPolicy[] =
	{
		NOTI_EX_ITEM_POLICY_NONE,
		NOTI_EX_ITEM_POLICY_ON_BOOT_CLEAR,
		NOTI_EX_ITEM_POLICY_SIM_MODE,
		NOTI_EX_ITEM_POLICY_DISABLE_AUTO_DELETE
	};

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	int nEnumSize = sizeof(eSetPolicy) / sizeof(eSetPolicy[0]);
	int nEnumCounter;

	for(nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		//Target API
		nRet = noti_ex_item_set_policy(g_hItemButton, eSetPolicy[nEnumCounter]);
		PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_policy", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

		//Target API
		nRet = noti_ex_item_get_policy(g_hItemButton, &nGetPolicy);
		PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_policy", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
		PRINT_RESULT_CLEANUP(eSetPolicy[nEnumCounter], nGetPolicy, "noti_ex_item_get_policy", "returned different value of policy", noti_ex_item_destroy(g_hItemButton));
	}

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and gets the channel of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_set_get_channel_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and gets the channel of a notification_ex item.
* @scenario			Creates the notification_ex button, Set channel\n
*				get channel and compare with set channel and check for Pass/Fail.
* @apicovered			noti_ex_item_set_channel, noti_ex_item_get_channel
* @passcase			noti_ex_item_set_channel, noti_ex_item_get_channel are successful and return correct value
* @failcase			noti_ex_item_set_channel, noti_ex_item_get_channel failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_set_get_channel_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	const char *pszSetChannel = "testID";
	char *pszGetChannel = NULL;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	//Target API
	nRet = noti_ex_item_set_channel(g_hItemButton, pszSetChannel);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_channel", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_get_channel(g_hItemButton, &pszGetChannel);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_channel", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(pszGetChannel, "noti_ex_item_get_channel", noti_ex_item_destroy(g_hItemButton));

	if( strncmp(pszSetChannel, pszGetChannel, strlen(pszGetChannel) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_get_channel: return Channel is different from set Channel [%s]\\n", __LINE__, API_NAMESPACE, pszGetChannel);
		FREE_MEMORY(pszGetChannel);

		nRet = noti_ex_item_destroy(g_hItemButton);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszGetChannel);

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and gets the LED information of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_set_get_led_info_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and gets the LED information of a notification_ex item.
* @scenario			Creates color, led info, button and set led info\n
*				get led info and check get led info handle and check for Pass/Fail.
* @apicovered			noti_ex_item_set_led_info, noti_ex_item_get_led_info
* @passcase			noti_ex_item_set_led_info, noti_ex_item_get_led_info are successful and return correct value
* @failcase			noti_ex_item_set_led_info, noti_ex_item_get_led_info failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_set_get_led_info_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_color_h hColor = NULL;
	noti_ex_led_info_h hSetLedInfo = NULL;
	noti_ex_led_info_h hGetLedInfo = NULL;

	unsigned char cAlpha = 1;
	unsigned char cRed = 2;
	unsigned char cGreen = 3;
	unsigned char cBlue = 4;

	nRet = noti_ex_color_create(&hColor, cAlpha, cRed, cGreen, cBlue);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hColor, "noti_ex_color_create");

	nRet = noti_ex_led_info_create(&hSetLedInfo, hColor);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_create", NotificationExGetError(nRet), noti_ex_color_destroy(hColor));
	CHECK_HANDLE_CLEANUP(hSetLedInfo, "noti_ex_led_info_create", noti_ex_color_destroy(hColor));

	nRet = CreateButton();
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet), noti_ex_color_destroy(hColor); noti_ex_led_info_destroy(hSetLedInfo));
	CHECK_HANDLE_CLEANUP(g_hItemButton, "noti_ex_item_button_create", noti_ex_color_destroy(hColor); noti_ex_led_info_destroy(hSetLedInfo));

	//Target API
	nRet = noti_ex_item_set_led_info(g_hItemButton, hSetLedInfo);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_led_info", NotificationExGetError(nRet), noti_ex_color_destroy(hColor); noti_ex_led_info_destroy(hSetLedInfo); noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_get_led_info(g_hItemButton, &hGetLedInfo);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_led_info", NotificationExGetError(nRet), noti_ex_color_destroy(hColor); noti_ex_led_info_destroy(hSetLedInfo); noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(hGetLedInfo, "noti_ex_item_get_led_info", noti_ex_color_destroy(hColor); noti_ex_led_info_destroy(hSetLedInfo); noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_led_info_destroy(hGetLedInfo);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_led_info_destroy(hSetLedInfo);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_color_destroy(hColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and gets the sound path of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_set_get_sound_path_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and gets the sound path of a notification_ex item.
* @scenario			Creates notification_ex button and set sound path\n
*				get sound path and compare with set sound path and check for Pass/Fail.
* @apicovered			noti_ex_item_set_sound_path, noti_ex_item_get_sound_path
* @passcase			noti_ex_item_set_sound_path, noti_ex_item_get_sound_path are successful and return correct value
* @failcase			noti_ex_item_set_sound_path, noti_ex_item_get_sound_path failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_set_get_sound_path_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	const char *pszSetSoundPath = "testPath";
	char *pszGetSoundPath = NULL;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	//Target API
	nRet = noti_ex_item_set_sound_path(g_hItemButton, pszSetSoundPath);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_sound_path", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_get_sound_path(g_hItemButton, &pszGetSoundPath);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_sound_path", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(pszGetSoundPath, "noti_ex_item_get_sound_path", noti_ex_item_destroy(g_hItemButton));

	if( strncmp(pszSetSoundPath, pszGetSoundPath, strlen(pszGetSoundPath) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_get_sound_path: return Sound Path is different from set Sound Path [%s]\\n", __LINE__, API_NAMESPACE, pszGetSoundPath);
		FREE_MEMORY(pszGetSoundPath);

		nRet = noti_ex_item_destroy(g_hItemButton);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszGetSoundPath);

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and gets the vibration path of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_set_get_vibration_path_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and gets the vibration path of a notification_ex item.
* @scenario			Creates notification_ex button and set vibration path\n
*				get vibration path and compare with set vibration path and check for Pass/Fail.
* @apicovered			noti_ex_item_set_vibration_path, noti_ex_item_get_vibration_path
* @passcase			noti_ex_item_set_vibration_path, noti_ex_item_get_vibration_path are successful and return correct value
* @failcase			noti_ex_item_set_vibration_path, noti_ex_item_get_vibration_path failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_set_get_vibration_path_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	const char *pszSetVibPath = "testVibPath";
	char *pszGetVibPath = NULL;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	//Target API
	nRet = noti_ex_item_set_vibration_path(g_hItemButton, pszSetVibPath);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_vibration_path", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_get_vibration_path(g_hItemButton, &pszGetVibPath);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_vibration_path", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(pszGetVibPath, "noti_ex_item_get_vibration_path", noti_ex_item_destroy(g_hItemButton));

	if( strncmp(pszSetVibPath, pszGetVibPath, strlen(pszGetVibPath) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_get_vibration_path: return vibration Path is different from set vibration Path [%s]\\n", __LINE__, API_NAMESPACE, pszGetVibPath);
		FREE_MEMORY(pszGetVibPath);

		nRet = noti_ex_item_destroy(g_hItemButton);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszGetVibPath);

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the information of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_get_info_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the information of a notification_ex item.
* @scenario			Creates notification_ex button and get item info handle\n
*				check item info handle and check for Pass/Fail.
* @apicovered			noti_ex_item_get_info
* @passcase			noti_ex_item_get_info is successful and return correct value
* @failcase			noti_ex_item_get_info failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_get_info_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_info_h hItemInfo = NULL;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	//Target API
	nRet = noti_ex_item_get_info(g_hItemButton, &hItemInfo);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_info", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(hItemInfo, "noti_ex_item_get_info", noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the sender app id of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_get_sender_app_id_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the sender app id of a notification_ex item.
* @scenario			Creates notification_ex button and get sender app id\n
*				check sender app strin handle and check for Pass/Fail.
* @apicovered			noti_ex_item_get_sender_app_id
* @passcase			noti_ex_item_get_sender_app_id is successful and return correct value
* @failcase			noti_ex_item_get_sender_app_id failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_get_sender_app_id_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	char *pszSenderAppID = NULL;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	//Target API
	nRet = noti_ex_item_get_sender_app_id(g_hItemButton, &pszSenderAppID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_sender_app_id", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(pszSenderAppID, "noti_ex_item_get_sender_app_id", noti_ex_item_destroy(g_hItemButton));
	FPRINTF("[Line : %d][%s] noti_ex_item_get_sender_app_id: Sender App ID [%s]\\n", __LINE__, API_NAMESPACE, pszSenderAppID);

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and gets the tag of a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_set_get_tag_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and gets the tag of a notification_ex item.
* @scenario			Creates notification_ex button and set buttons tag\n
*				get buttons tag and compare with set tag and check for Pass/Fail.
* @apicovered			noti_ex_item_set_tag, noti_ex_item_get_tag
* @passcase			noti_ex_item_set_tag, noti_ex_item_get_tag are successful and return correct value
* @failcase			noti_ex_item_set_tag, noti_ex_item_get_tag failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_set_get_tag_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	const char *pszSetTag = "testTag_ONE";
	char *pszGetTag = NULL;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	//Target API
	nRet = noti_ex_item_set_tag(g_hItemButton, pszSetTag);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_tag", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_get_tag(g_hItemButton, &pszGetTag);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_tag", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(pszGetTag, "noti_ex_item_get_tag", noti_ex_item_destroy(g_hItemButton));

	if( strncmp(pszSetTag, pszGetTag, strlen(pszGetTag) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_get_tag: return Tag is different from set Tag [%s]\\n", __LINE__, API_NAMESPACE, pszGetTag);
		FREE_MEMORY(pszGetTag);

		nRet = noti_ex_item_destroy(g_hItemButton);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszGetTag);

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Creates and destroy the notification_ex color handle.
/**
* @testcase			ITc_noti_ex_color_create_destroy_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates and destroy the notification_ex color handle.
* @scenario			Creates notification_ex color item \n
*				Check handle and Check for Pass/Fail.
* @apicovered			noti_ex_color_create, noti_ex_color_destroy
* @passcase			noti_ex_color_create, noti_ex_color_destroy are successful and return correct value
* @failcase			noti_ex_color_create, noti_ex_color_destroy failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_color_create_destroy_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_color_h hColor = NULL;
	unsigned char cAlpha = 1;
	unsigned char cRed = 2;
	unsigned char cGreen = 3;
	unsigned char cBlue = 4;

	//Target API
	nRet = noti_ex_color_create(&hColor, cAlpha, cRed, cGreen, cBlue);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hColor, "noti_ex_color_create");

	//Target API
	nRet = noti_ex_color_destroy(hColor);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the alpha value of a color.
/**
* @testcase			ITc_noti_ex_color_get_alpha_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the alpha value of a color.
* @scenario			Creates notification_ex color item \n
*				Get alpha value and compare with set value and Check for Pass/Fail.
* @apicovered			noti_ex_color_get_alpha
* @passcase			noti_ex_color_get_alpha is successful and return correct value
* @failcase			noti_ex_color_get_alpha failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_color_get_alpha_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_color_h hColor = NULL;
	unsigned char cAlpha = 1;
	unsigned char cRed = 2;
	unsigned char cGreen = 3;
	unsigned char cBlue = 4;
	unsigned char cGetAlpha;

	nRet = noti_ex_color_create(&hColor, cAlpha, cRed, cGreen, cBlue);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hColor, "noti_ex_color_create");

	//Target API
	nRet = noti_ex_color_get_alpha(hColor, &cGetAlpha);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_get_alpha", NotificationExGetError(nRet), noti_ex_color_destroy(hColor));
	PRINT_RESULT_CLEANUP(cAlpha, cGetAlpha, "noti_ex_color_get_alpha", "Set and Get alpha value is not same", noti_ex_color_destroy(hColor));

	nRet = noti_ex_color_destroy(hColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the red value of a color.
/**
* @testcase			ITc_noti_ex_color_get_red_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the red value of a color.
* @scenario			Creates notification_ex color item \n
*				Get red value and compare with set value and Check for Pass/Fail.
* @apicovered			noti_ex_color_get_red
* @passcase			noti_ex_color_get_red is successful and return correct value
* @failcase			noti_ex_color_get_red failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_color_get_red_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_color_h hColor = NULL;
	unsigned char cAlpha = 1;
	unsigned char cRed = 2;
	unsigned char cGreen = 3;
	unsigned char cBlue = 4;
	unsigned char cGetRed;

	nRet = noti_ex_color_create(&hColor, cAlpha, cRed, cGreen, cBlue);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hColor, "noti_ex_color_create");

	//Target API
	nRet = noti_ex_color_get_red(hColor, &cGetRed);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_get_red", NotificationExGetError(nRet), noti_ex_color_destroy(hColor));
	PRINT_RESULT_CLEANUP(cRed, cGetRed, "noti_ex_color_get_red", "Set and Get red color value is not same", noti_ex_color_destroy(hColor));

	nRet = noti_ex_color_destroy(hColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the green value of a color.
/**
* @testcase			ITc_noti_ex_color_get_green_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the green value of a color.
* @scenario			Creates notification_ex color item \n
*				Get green value and compare with set value and Check for Pass/Fail.
* @apicovered			noti_ex_color_get_green
* @passcase			noti_ex_color_get_green is successful and return correct value
* @failcase			noti_ex_color_get_green failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_color_get_green_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_color_h hColor = NULL;
	unsigned char cAlpha = 1;
	unsigned char cRed = 2;
	unsigned char cGreen = 3;
	unsigned char cBlue = 4;
	unsigned char cGetGreen;

	nRet = noti_ex_color_create(&hColor, cAlpha, cRed, cGreen, cBlue);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hColor, "noti_ex_color_create");

	//Target API
	nRet = noti_ex_color_get_green(hColor, &cGetGreen);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_get_green", NotificationExGetError(nRet), noti_ex_color_destroy(hColor));
	PRINT_RESULT_CLEANUP(cGreen, cGetGreen, "noti_ex_color_get_green", "Set and Get green color value is not same", noti_ex_color_destroy(hColor));

	nRet = noti_ex_color_destroy(hColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the blue value of a color.
/**
* @testcase			ITc_noti_ex_color_get_blue_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the blue value of a color.
* @scenario			Creates notification_ex color item \n
*				Get blue value and compare with set value and Check for Pass/Fail.
* @apicovered			noti_ex_color_get_blue
* @passcase			noti_ex_color_get_blue is successful and return correct value
* @failcase			noti_ex_color_get_blue failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_color_get_blue_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_color_h hColor = NULL;
	unsigned char cAlpha = 1;
	unsigned char cRed = 2;
	unsigned char cGreen = 3;
	unsigned char cBlue = 4;
	unsigned char cGetBlue;

	nRet = noti_ex_color_create(&hColor, cAlpha, cRed, cGreen, cBlue);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hColor, "noti_ex_color_create");

	//Target API
	nRet = noti_ex_color_get_blue(hColor, &cGetBlue);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_get_blue", NotificationExGetError(nRet), noti_ex_color_destroy(hColor));
	PRINT_RESULT_CLEANUP(cBlue, cGetBlue, "noti_ex_color_get_blue", "Set and Get blue color value is not same", noti_ex_color_destroy(hColor));

	nRet = noti_ex_color_destroy(hColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Creates and destroy the notification_ex padding handle.
/**
* @testcase			ITc_noti_ex_padding_create_destroy_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates and destroy the notification_ex padding handle.
* @scenario			Creates notification_ex padding item \n
*				check handle and Check for Pass/Fail.
* @apicovered			noti_ex_padding_create, noti_ex_padding_destroy
* @passcase			noti_ex_padding_create, noti_ex_padding_destroy are successful and return correct value
* @failcase			noti_ex_padding_create, noti_ex_padding_destroy failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_padding_create_destroy_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_padding_h hPadding = NULL;
	int nLeft = 1;
	int nTop = 2;
	int nRight = 3;
	int nBottom = 4;

	//Target API
	nRet = noti_ex_padding_create(&hPadding, nLeft, nTop, nRight, nBottom);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hPadding, "noti_ex_padding_create");

	nRet = noti_ex_padding_destroy(hPadding);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the left value of padding.
/**
* @testcase			ITc_noti_ex_padding_get_left_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the left value of padding.
* @scenario			Creates notification_ex padding item \n
*				get left padding and compare with set value and Check for Pass/Fail.
* @apicovered			noti_ex_padding_get_left
* @passcase			noti_ex_padding_get_left is successful and return correct value
* @failcase			noti_ex_padding_get_left failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_padding_get_left_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_padding_h hPadding = NULL;
	int nLeft = 1;
	int nTop = 2;
	int nRight = 3;
	int nBottom = 4;
	int nGetLeft;

	nRet = noti_ex_padding_create(&hPadding, nLeft, nTop, nRight, nBottom);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hPadding, "noti_ex_padding_create");

	//Target API
	nRet = noti_ex_padding_get_left(hPadding, &nGetLeft);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_get_left", NotificationExGetError(nRet), noti_ex_padding_destroy(hPadding));
	PRINT_RESULT_CLEANUP(nLeft, nGetLeft, "noti_ex_padding_get_left", "Set and Get left padding value is not same", noti_ex_padding_destroy(hPadding));

	nRet = noti_ex_padding_destroy(hPadding);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the top value of padding.
/**
* @testcase			ITc_noti_ex_padding_get_top_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the top value of padding.
* @scenario			Creates notification_ex padding item \n
*				get top padding and compare with set value and Check for Pass/Fail.
* @apicovered			noti_ex_padding_get_top
* @passcase			noti_ex_padding_get_top is successful and return correct value
* @failcase			noti_ex_padding_get_top failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_padding_get_top_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_padding_h hPadding = NULL;
	int nLeft = 1;
	int nTop = 2;
	int nRight = 3;
	int nBottom = 4;
	int nGetTop;

	nRet = noti_ex_padding_create(&hPadding, nLeft, nTop, nRight, nBottom);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hPadding, "noti_ex_padding_create");

	//Target API
	nRet = noti_ex_padding_get_top(hPadding, &nGetTop);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_get_top", NotificationExGetError(nRet), noti_ex_padding_destroy(hPadding));
	PRINT_RESULT_CLEANUP(nTop, nGetTop, "noti_ex_padding_get_top", "Set and Get top padding value is not same", noti_ex_padding_destroy(hPadding));

	nRet = noti_ex_padding_destroy(hPadding);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the right value of padding.
/**
* @testcase			ITc_noti_ex_padding_get_right_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the right value of padding.
* @scenario			Creates notification_ex padding item \n
*				get right padding and compare with set value and Check for Pass/Fail.
* @apicovered			noti_ex_padding_get_right
* @passcase			noti_ex_padding_get_right is successful and return correct value
* @failcase			noti_ex_padding_get_right failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_padding_get_right_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_padding_h hPadding = NULL;
	int nLeft = 1;
	int nTop = 2;
	int nRight = 3;
	int nBottom = 4;
	int nGetRight;

	nRet = noti_ex_padding_create(&hPadding, nLeft, nTop, nRight, nBottom);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hPadding, "noti_ex_padding_create");

	//Target API
	nRet = noti_ex_padding_get_right(hPadding, &nGetRight);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_get_right", NotificationExGetError(nRet), noti_ex_padding_destroy(hPadding));
	PRINT_RESULT_CLEANUP(nRight, nGetRight, "noti_ex_padding_get_right", "Set and Get right padding value is not same", noti_ex_padding_destroy(hPadding));

	nRet = noti_ex_padding_destroy(hPadding);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the bottom value of padding.
/**
* @testcase			ITc_noti_ex_padding_get_bottom_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the bottom value of padding.
* @scenario			Creates notification_ex padding item \n
*				get bottom padding and compare with set value and Check for Pass/Fail.
* @apicovered			noti_ex_padding_get_bottom
* @passcase			noti_ex_padding_get_bottom is successful and return correct value
* @failcase			noti_ex_padding_get_bottom failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_padding_get_bottom_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_padding_h hPadding = NULL;
	int nLeft = 1;
	int nTop = 2;
	int nRight = 3;
	int nBottom = 4;
	int nGetBottom;

	nRet = noti_ex_padding_create(&hPadding, nLeft, nTop, nRight, nBottom);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hPadding, "noti_ex_padding_create");

	//Target API
	nRet = noti_ex_padding_get_bottom(hPadding, &nGetBottom);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_get_bottom", NotificationExGetError(nRet), noti_ex_padding_destroy(hPadding));
	PRINT_RESULT_CLEANUP(nBottom, nGetBottom, "noti_ex_padding_get_bottom", "Set and Get bottom padding value is not same", noti_ex_padding_destroy(hPadding));

	nRet = noti_ex_padding_destroy(hPadding);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Creates the notification_ex geometry handle.
/**
* @testcase			ITc_noti_ex_geometry_create_destroy_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates the notification_ex geometry handle.
* @scenario			Creates notification_ex geometry item \n
*				check handle and Check for Pass/Fail.
* @apicovered			noti_ex_geometry_create, noti_ex_geometry_destroy
* @passcase			noti_ex_geometry_create, noti_ex_geometry_destroy are successful and return correct value
* @failcase			noti_ex_geometry_create, noti_ex_geometry_destroy failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_geometry_create_destroy_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_geometry_h hGeometry = NULL;
	int nX = 1;
	int nY = 2;
	int nW = 3;
	int nH = 4;

	//Target API
	nRet = noti_ex_geometry_create(&hGeometry, nX, nY, nW, nH);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hGeometry, "noti_ex_geometry_create");

	//Target API
	nRet = noti_ex_geometry_destroy(hGeometry);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the x position value.
/**
* @testcase			ITc_noti_ex_geometry_get_x_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the x position value.
* @scenario			Creates notification_ex geometry item \n
*				get x position and compare with set x position and Check for Pass/Fail.
* @apicovered			noti_ex_geometry_get_x
* @passcase			noti_ex_geometry_get_x is successful and return correct value
* @failcase			noti_ex_geometry_get_x failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_geometry_get_x_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_geometry_h hGeometry = NULL;
	int nX = 1;
	int nY = 2;
	int nW = 3;
	int nH = 4;

	int nGetX;

	nRet = noti_ex_geometry_create(&hGeometry, nX, nY, nW, nH);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hGeometry, "noti_ex_geometry_create");

	//Target API
	nRet = noti_ex_geometry_get_x(hGeometry, &nGetX);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_get_x", NotificationExGetError(nRet), noti_ex_geometry_destroy(hGeometry));
	PRINT_RESULT_CLEANUP(nGetX, nX, "noti_ex_geometry_get_x", "Set X position is not same as get X", noti_ex_geometry_destroy(hGeometry));

	nRet = noti_ex_geometry_destroy(hGeometry);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the y position value.
/**
* @testcase			ITc_noti_ex_geometry_get_y_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the y position value.
* @scenario			Creates notification_ex geometry item \n
*				get y position and compare with set y position and Check for Pass/Fail.
* @apicovered			noti_ex_geometry_get_y
* @passcase			noti_ex_geometry_get_y is successful and return correct value
* @failcase			noti_ex_geometry_get_y failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_geometry_get_y_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_geometry_h hGeometry = NULL;
	int nX = 1;
	int nY = 2;
	int nW = 3;
	int nH = 4;

	int nGetY;

	nRet = noti_ex_geometry_create(&hGeometry, nX, nY, nW, nH);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hGeometry, "noti_ex_geometry_create");

	//Target API
	nRet = noti_ex_geometry_get_y(hGeometry, &nGetY);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_get_y", NotificationExGetError(nRet), noti_ex_geometry_destroy(hGeometry));
	PRINT_RESULT_CLEANUP(nGetY, nY, "noti_ex_geometry_get_y", "Set Y position is not same as get Y", noti_ex_geometry_destroy(hGeometry));

	nRet = noti_ex_geometry_destroy(hGeometry);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the width value.
/**
* @testcase			ITc_noti_ex_geometry_get_width_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the width value.
* @scenario			Creates notification_ex geometry item \n
*				get width value and compare with set width value and Check for Pass/Fail.
* @apicovered			noti_ex_geometry_get_width
* @passcase			noti_ex_geometry_get_width is successful and return correct value
* @failcase			noti_ex_geometry_get_width failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_geometry_get_width_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_geometry_h hGeometry = NULL;
	int nX = 1;
	int nY = 2;
	int nW = 3;
	int nH = 4;

	int nGetW;

	nRet = noti_ex_geometry_create(&hGeometry, nX, nY, nW, nH);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hGeometry, "noti_ex_geometry_create");

	//Target API
	nRet = noti_ex_geometry_get_width(hGeometry, &nGetW);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_get_width", NotificationExGetError(nRet), noti_ex_geometry_destroy(hGeometry));
	PRINT_RESULT_CLEANUP(nGetW, nW, "noti_ex_geometry_get_width", "Set Width position is not same as get Width", noti_ex_geometry_destroy(hGeometry));

	nRet = noti_ex_geometry_destroy(hGeometry);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the height value.
/**
* @testcase			ITc_noti_ex_geometry_get_height_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the height value.
* @scenario			Creates notification_ex geometry item \n
*				get height value and compare with set height value and Check for Pass/Fail.
* @apicovered			noti_ex_geometry_get_height
* @passcase			noti_ex_geometry_get_height is successful and return correct value
* @failcase			noti_ex_geometry_get_height failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_geometry_get_height_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_geometry_h hGeometry = NULL;
	int nX = 1;
	int nY = 2;
	int nW = 3;
	int nH = 4;

	int nGetH;

	nRet = noti_ex_geometry_create(&hGeometry, nX, nY, nW, nH);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hGeometry, "noti_ex_geometry_create");

	//Target API
	nRet = noti_ex_geometry_get_height(hGeometry, &nGetH);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_get_height", NotificationExGetError(nRet), noti_ex_geometry_destroy(hGeometry));
	PRINT_RESULT_CLEANUP(nGetH, nH, "noti_ex_geometry_get_height", "Set height position is not same as get height", noti_ex_geometry_destroy(hGeometry));

	nRet = noti_ex_geometry_destroy(hGeometry);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Creates and destroys the notification_ex style handle.
/**
* @testcase			ITc_noti_ex_style_create_destroy_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates and destroys the notification_ex style handle.
* @scenario			Creates notification_ex color, padding, geometry and then create style item \n
*				Check handle and Check for Pass/Fail.
* @apicovered			noti_ex_style_create, noti_ex_style_destroy
* @passcase			noti_ex_style_create, noti_ex_style_destroy are successful and return correct value
* @failcase			noti_ex_style_create, noti_ex_style_destroy failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_style_create_destroy_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_style_h hStyle = NULL;
	noti_ex_color_h hColor = NULL;
	noti_ex_padding_h hPadding = NULL;
	noti_ex_geometry_h hGeometry = NULL;

	unsigned char cAlpha = 1;
	unsigned char cRed = 2;
	unsigned char cGreen = 3;
	unsigned char cBlue = 4;

	int nLeft = 1;
	int nTop = 2;
	int nRight = 3;
	int nBottom = 4;

	int nX = 1;
	int nY = 2;
	int nW = 3;
	int nH = 4;

	nRet = noti_ex_color_create(&hColor, cAlpha, cRed, cGreen, cBlue);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hColor, "noti_ex_color_create");

	nRet = noti_ex_padding_create(&hPadding, nLeft, nTop, nRight, nBottom);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_create", NotificationExGetError(nRet), noti_ex_color_destroy(hColor));
	CHECK_HANDLE_CLEANUP(hPadding, "noti_ex_padding_create", noti_ex_color_destroy(hColor));

	nRet = noti_ex_geometry_create(&hGeometry, nX, nY, nW, nH);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_create", NotificationExGetError(nRet), noti_ex_color_destroy(hColor); noti_ex_padding_destroy(hPadding));
	CHECK_HANDLE_CLEANUP(hGeometry, "noti_ex_geometry_create", noti_ex_color_destroy(hColor); noti_ex_padding_destroy(hPadding));

	//Target API
	nRet = noti_ex_style_create(&hStyle, hColor, hPadding, hGeometry);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_style_create", NotificationExGetError(nRet), noti_ex_color_destroy(hColor); noti_ex_padding_destroy(hPadding); noti_ex_geometry_destroy(hGeometry));
	CHECK_HANDLE_CLEANUP(hStyle, "noti_ex_style_create", noti_ex_color_destroy(hColor); noti_ex_padding_destroy(hPadding); noti_ex_geometry_destroy(hGeometry));

	//Target API
	nRet = noti_ex_style_destroy(hStyle);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_style_destroy", NotificationExGetError(nRet), noti_ex_color_destroy(hColor); noti_ex_padding_destroy(hPadding); noti_ex_geometry_destroy(hGeometry));

	nRet = noti_ex_color_destroy(hColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_padding_destroy(hPadding);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_geometry_destroy(hGeometry);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the padding information from a style.
/**
* @testcase			ITc_noti_ex_style_get_padding_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the padding information from a style.
* @scenario			Creates notification_ex color, padding, geometry and then create style item \n
*				Get padding from style, compare with set padding attributes and Check for Pass/Fail.
* @apicovered			noti_ex_style_get_padding
* @passcase			noti_ex_style_get_padding is successful and return correct value
* @failcase			noti_ex_style_get_padding failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_style_get_padding_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_padding_h hGetPadding;
	int nGetStyleLeft, nGetStyleTop, nGetStyleRight, nGetStyleBottom;

	nRet = CreateStyleAttributes();
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the prerequisite API inside CreateStyleAttributes() is failed \\n", __LINE__, API_NAMESPACE);
		return 1;

	}
	//Target API
	nRet = noti_ex_style_get_padding(g_hStyle, &hGetPadding);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_style_get_padding", NotificationExGetError(nRet), DestroyStyleAttributes());
	CHECK_HANDLE_CLEANUP(hGetPadding, "noti_ex_style_get_padding", DestroyStyleAttributes());

	nRet = noti_ex_padding_get_left(hGetPadding, &nGetStyleLeft);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_get_left", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_nLeft, nGetStyleLeft, "noti_ex_style_get_padding", "noti_ex_style_get_padding returned different left value", DestroyStyleAttributes());

	nRet = noti_ex_padding_get_top(hGetPadding, &nGetStyleTop);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_get_top", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_nTop, nGetStyleTop, "noti_ex_style_get_padding", "noti_ex_style_get_padding returned different top value", DestroyStyleAttributes());

	nRet = noti_ex_padding_get_right(hGetPadding, &nGetStyleRight);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_get_right", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_nRight, nGetStyleRight, "noti_ex_style_get_padding", "noti_ex_style_get_padding returned different right value", DestroyStyleAttributes());

	nRet = noti_ex_padding_get_bottom(hGetPadding, &nGetStyleBottom);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_padding_get_bottom", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_nBottom, nGetStyleBottom, "noti_ex_style_get_padding", "noti_ex_style_get_padding returned different bottom value", DestroyStyleAttributes());

	DestroyStyleAttributes();
	return 0;
}

//& type : auto
//& purpose: Gets the color information from a style.
/**
* @testcase			ITc_noti_ex_style_get_color_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the color information from a style.
* @scenario			Creates notification_ex color, padding, geometry and then create style item \n
*				Get color from style, compare with set color attributes and Check for Pass/Fail.
* @apicovered			noti_ex_style_get_color
* @passcase			noti_ex_style_get_color is successful and return correct value
* @failcase			noti_ex_style_get_color failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_style_get_color_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_color_h hGetColor;
	unsigned char cGetStyleAplha, cGetStyleRed, cGetStyleGreen, cGetStyleBlue;

	nRet = CreateStyleAttributes();
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the prerequisite API inside CreateStyleAttributes() is failed \\n", __LINE__, API_NAMESPACE);
		return 1;

	}

	//Target API
	nRet = noti_ex_style_get_color(g_hStyle, &hGetColor);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_style_get_color", NotificationExGetError(nRet), DestroyStyleAttributes());
	CHECK_HANDLE_CLEANUP(hGetColor, "noti_ex_style_get_color", DestroyStyleAttributes());

	nRet = noti_ex_color_get_alpha(hGetColor, &cGetStyleAplha);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_get_alpha", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_cAlpha, cGetStyleAplha, "noti_ex_style_get_color", "noti_ex_style_get_color returned different alpha value", DestroyStyleAttributes());

	nRet = noti_ex_color_get_red(hGetColor, &cGetStyleRed);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_get_red", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_cRed, cGetStyleRed, "noti_ex_style_get_color", "noti_ex_style_get_color returned different red value", DestroyStyleAttributes());

	nRet = noti_ex_color_get_green(hGetColor, &cGetStyleGreen);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_get_green", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_cGreen, cGetStyleGreen, "noti_ex_style_get_color", "noti_ex_style_get_color returned different green value", DestroyStyleAttributes());

	nRet = noti_ex_color_get_blue(hGetColor, &cGetStyleBlue);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_get_blue", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_cBlue, cGetStyleBlue, "noti_ex_style_get_color", "noti_ex_style_get_color returned different blue value", DestroyStyleAttributes());

	DestroyStyleAttributes();
	return 0;
}

//& type : auto
//& purpose: Gets the geometry information from a style.
/**
* @testcase			ITc_noti_ex_style_get_geometry_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the color information from a style.
* @scenario			Creates notification_ex color, padding, geometry and then create style item \n
*				Get geometry from style, compare with set geometry attributes and Check for Pass/Fail.
* @apicovered			noti_ex_style_get_geometry
* @passcase			noti_ex_style_get_geometry is successful and return correct value
* @failcase			noti_ex_style_get_geometry failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_style_get_geometry_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_geometry_h hGetGeometry;
	int nGetStyleX, nGetStyleY, nGetStyleW, nGetStyleH;

	nRet = CreateStyleAttributes();
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the prerequisite API inside CreateStyleAttributes() is failed \\n", __LINE__, API_NAMESPACE);
		return 1;

	}
	//Target API
	nRet = noti_ex_style_get_geometry(g_hStyle, &hGetGeometry);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_style_get_geometry", NotificationExGetError(nRet), DestroyStyleAttributes());
	CHECK_HANDLE_CLEANUP(hGetGeometry, "noti_ex_style_get_geometry", DestroyStyleAttributes());

	nRet = noti_ex_geometry_get_x(hGetGeometry, &nGetStyleX);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_get_x", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_nX, nGetStyleX, "noti_ex_style_get_geometry", "noti_ex_style_get_geometry returned different X value", DestroyStyleAttributes());

	nRet = noti_ex_geometry_get_y(hGetGeometry, &nGetStyleY);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_get_y", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_nY, nGetStyleY, "noti_ex_style_get_geometry", "noti_ex_style_get_geometry returned different Y value", DestroyStyleAttributes());

	nRet = noti_ex_geometry_get_width(hGetGeometry, &nGetStyleW);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_get_width", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_nW, nGetStyleW, "noti_ex_style_get_geometry", "noti_ex_style_get_geometry returned different width value", DestroyStyleAttributes());

	nRet = noti_ex_geometry_get_height(hGetGeometry, &nGetStyleH);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_geometry_get_height", NotificationExGetError(nRet), DestroyStyleAttributes());
	PRINT_RESULT_CLEANUP(g_nH, nGetStyleH, "noti_ex_style_get_geometry", "noti_ex_style_get_geometry returned different height value", DestroyStyleAttributes());

	DestroyStyleAttributes();
	return 0;
}

//& type : auto
//& purpose: Creates and destroys the notification_ex LED info handle.
/**
* @testcase			ITc_noti_ex_led_info_create_destroy_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates and destroys the notification_ex LED info handle.
* @scenario			Creates notification_ex color and LED info item \n
*				Check handle and Check for Pass/Fail.
* @apicovered			noti_ex_led_info_create, noti_ex_led_info_destroy
* @passcase			noti_ex_led_info_create, noti_ex_led_info_destroy are successful and return correct value
* @failcase			noti_ex_led_info_create, noti_ex_led_info_destroy failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_led_info_create_destroy_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_color_h hColor = NULL;
	noti_ex_led_info_h hLedInfo = NULL;

	unsigned char cAlpha = 1;
	unsigned char cRed = 2;
	unsigned char cGreen = 3;
	unsigned char cBlue = 4;

	nRet = noti_ex_color_create(&hColor, cAlpha, cRed, cGreen, cBlue);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hColor, "noti_ex_color_create");

	//Target API
	nRet = noti_ex_led_info_create(&hLedInfo, hColor);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_create", NotificationExGetError(nRet), noti_ex_color_destroy(hColor));
	CHECK_HANDLE_CLEANUP(hLedInfo, "noti_ex_led_info_create", noti_ex_color_destroy(hColor));

	//Target API
	nRet = noti_ex_led_info_destroy(hLedInfo);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_destroy", NotificationExGetError(nRet), noti_ex_color_destroy(hColor));

	nRet = noti_ex_color_destroy(hColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and Gets the time period for turning on the LED.
/**
* @testcase			ITc_noti_ex_led_info_set_get_on_period_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and Gets the time period for turning on the LED.
* @scenario			Creates notification_ex color and LED info item \n
*				set On time period and get On time period and Check for Pass/Fail.
* @apicovered			noti_ex_led_info_set_on_period, noti_ex_led_info_get_on_period
* @passcase			noti_ex_led_info_set_on_period, noti_ex_led_info_get_on_period are successful and return correct value
* @failcase			noti_ex_led_info_set_on_period, noti_ex_led_info_get_on_period failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_led_info_set_get_on_period_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_color_h hColor = NULL;
	noti_ex_led_info_h hLedInfo = NULL;

	unsigned char cAlpha = 1;
	unsigned char cRed = 2;
	unsigned char cGreen = 3;
	unsigned char cBlue = 4;

	int nSetPeriod = 5;
	int nGetPeriod;

	nRet = noti_ex_color_create(&hColor, cAlpha, cRed, cGreen, cBlue);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hColor, "noti_ex_color_create");

	nRet = noti_ex_led_info_create(&hLedInfo, hColor);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_create", NotificationExGetError(nRet), noti_ex_color_destroy(hColor));
	CHECK_HANDLE_CLEANUP(hLedInfo, "noti_ex_led_info_create", noti_ex_color_destroy(hColor));

	//Target API
	nRet = noti_ex_led_info_set_on_period(hLedInfo, nSetPeriod);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_set_on_period", NotificationExGetError(nRet), noti_ex_color_destroy(hColor); noti_ex_led_info_destroy(hLedInfo));

	//Target API
	nRet = noti_ex_led_info_get_on_period(hLedInfo, &nGetPeriod);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_get_on_period", NotificationExGetError(nRet), noti_ex_color_destroy(hColor); noti_ex_led_info_destroy(hLedInfo));
	PRINT_RESULT_CLEANUP(nSetPeriod, nGetPeriod, "noti_ex_led_info_get_on_period", "noti_ex_led_info_get_on_period return value is different from nSetPeriod", noti_ex_color_destroy(hColor); noti_ex_led_info_destroy(hLedInfo));

	nRet = noti_ex_led_info_destroy(hLedInfo);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_color_destroy(hColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and Gets the time period for turning off the LED.
/**
* @testcase			ITc_noti_ex_led_info_set_get_off_period_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and Gets the time period for turning off the LED.
* @scenario			Creates notification_ex color and LED info item \n
*				set off time period and get off time period and Check for Pass/Fail.
* @apicovered			noti_ex_led_info_set_off_period, noti_ex_led_info_get_off_period
* @passcase			noti_ex_led_info_set_off_period, noti_ex_led_info_get_off_period are successful and return correct value
* @failcase			noti_ex_led_info_set_off_period, noti_ex_led_info_get_off_period failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_led_info_set_get_off_period_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_color_h hColor = NULL;
	noti_ex_led_info_h hLedInfo = NULL;

	unsigned char cAlpha = 1;
	unsigned char cRed = 2;
	unsigned char cGreen = 3;
	unsigned char cBlue = 4;

	int nSetPeriod = 5;
	int nGetPeriod;

	nRet = noti_ex_color_create(&hColor, cAlpha, cRed, cGreen, cBlue);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hColor, "noti_ex_color_create");

	nRet = noti_ex_led_info_create(&hLedInfo, hColor);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_create", NotificationExGetError(nRet), noti_ex_color_destroy(hColor));
	CHECK_HANDLE_CLEANUP(hLedInfo, "noti_ex_led_info_create", noti_ex_color_destroy(hColor));

	//Target API
	nRet = noti_ex_led_info_set_off_period(hLedInfo, nSetPeriod);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_set_off_period", NotificationExGetError(nRet), noti_ex_color_destroy(hColor); noti_ex_led_info_destroy(hLedInfo));

	//Target API
	nRet = noti_ex_led_info_get_off_period(hLedInfo, &nGetPeriod);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_get_off_period", NotificationExGetError(nRet), noti_ex_color_destroy(hColor); noti_ex_led_info_destroy(hLedInfo));
	PRINT_RESULT_CLEANUP(nSetPeriod, nGetPeriod, "noti_ex_led_info_get_off_period", "noti_ex_led_info_get_off_period return value is different from nSetPeriod", noti_ex_color_destroy(hColor); noti_ex_led_info_destroy(hLedInfo));

	nRet = noti_ex_led_info_destroy(hLedInfo);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_color_destroy(hColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the color information from LED info.
/**
* @testcase			ITc_noti_ex_led_info_get_color_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the color information from LED info.
* @scenario			Creates notification_ex color and LED info item \n
*				get color and compare color attributes with set color attributes and Check for Pass/Fail.
* @apicovered			noti_ex_led_info_get_color
* @passcase			noti_ex_led_info_get_color is successful and return correct value
* @failcase			noti_ex_led_info_get_color failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_led_info_get_color_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_led_info_h hLedInfo = NULL;
	noti_ex_color_h hColor = NULL;
	noti_ex_color_h hGetColor = NULL;

	unsigned char cAlpha = 1;
	unsigned char cRed = 2;
	unsigned char cGreen = 3;
	unsigned char cBlue = 4;

	unsigned char cGetStyleAplha, cGetStyleRed, cGetStyleGreen, cGetStyleBlue;

	nRet = noti_ex_color_create(&hColor, cAlpha, cRed, cGreen, cBlue);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hColor, "noti_ex_color_create");

	nRet = noti_ex_led_info_create(&hLedInfo, hColor);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_create", NotificationExGetError(nRet), noti_ex_color_destroy(hColor));
	CHECK_HANDLE_CLEANUP(hLedInfo, "noti_ex_led_info_create", noti_ex_color_destroy(hColor));

	//Target API
	nRet = noti_ex_led_info_get_color(hLedInfo, &hGetColor);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_get_color", NotificationExGetError(nRet), noti_ex_led_info_destroy(hLedInfo); noti_ex_color_destroy(hColor));
	CHECK_HANDLE_CLEANUP(hGetColor, "noti_ex_led_info_get_color", noti_ex_led_info_destroy(hLedInfo); noti_ex_color_destroy(hColor));

	nRet = noti_ex_color_get_alpha(hGetColor, &cGetStyleAplha);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_get_alpha", NotificationExGetError(nRet), noti_ex_led_info_destroy(hLedInfo); noti_ex_color_destroy(hColor));
	PRINT_RESULT_CLEANUP(cAlpha, cGetStyleAplha, "noti_ex_led_info_get_color", "noti_ex_led_info_get_color returned different alpha value", noti_ex_led_info_destroy(hLedInfo); noti_ex_color_destroy(hColor));

	nRet = noti_ex_color_get_red(hGetColor, &cGetStyleRed);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_get_red", NotificationExGetError(nRet), noti_ex_led_info_destroy(hLedInfo); noti_ex_color_destroy(hColor));
	PRINT_RESULT_CLEANUP(cRed, cGetStyleRed, "noti_ex_led_info_get_color", "noti_ex_led_info_get_color returned different red value", noti_ex_led_info_destroy(hLedInfo); noti_ex_color_destroy(hColor));

	nRet = noti_ex_color_get_green(hGetColor, &cGetStyleGreen);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_get_green", NotificationExGetError(nRet), noti_ex_led_info_destroy(hLedInfo); noti_ex_color_destroy(hColor));
	PRINT_RESULT_CLEANUP(cGreen, cGetStyleGreen, "noti_ex_led_info_get_color", "noti_ex_led_info_get_color returned different green value", noti_ex_led_info_destroy(hLedInfo); noti_ex_color_destroy(hColor));

	nRet = noti_ex_color_get_blue(hGetColor, &cGetStyleBlue);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_get_blue", NotificationExGetError(nRet), noti_ex_led_info_destroy(hLedInfo); noti_ex_color_destroy(hColor));
	PRINT_RESULT_CLEANUP(cBlue, cGetStyleBlue, "noti_ex_led_info_get_color", "noti_ex_led_info_get_color returned different blue value", noti_ex_led_info_destroy(hLedInfo); noti_ex_color_destroy(hColor));

	nRet = noti_ex_led_info_destroy(hLedInfo);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_led_info_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_color_destroy(hColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and gets the time to hide the notification_ex item.
/**
* @testcase			ITc_noti_ex_item_info_set_get_hide_time_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and gets the time to hide the notification_ex item.
* @scenario			Creates notification_ex button and get item info\n
*				set and get hide time from item info and compare them and Check for Pass/Fail.
* @apicovered			noti_ex_item_info_set_hide_time, noti_ex_item_info_get_hide_time
* @passcase			noti_ex_item_info_set_hide_time, noti_ex_item_info_get_hide_time are successful and return correct value
* @failcase			noti_ex_item_info_set_hide_time, noti_ex_item_info_get_hide_time failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_info_set_get_hide_time_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_info_h hItemInfo = NULL;
	int nSetHideTime = 10;
	int nGetHideTime;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	nRet = noti_ex_item_get_info(g_hItemButton, &hItemInfo);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_info", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(hItemInfo, "noti_ex_item_get_info", noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_info_set_hide_time(hItemInfo, nSetHideTime);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_info_set_hide_time", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_info_get_hide_time(hItemInfo, &nGetHideTime);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_info_get_hide_time", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	PRINT_RESULT_CLEANUP(nSetHideTime, nGetHideTime, "noti_ex_item_info_get_hide_time", "noti_ex_item_info_get_hide_time return value is different from nSetHideTime", noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Sets and gets the time to delete the notification_ex item.
/**
* @testcase			ITc_noti_ex_item_info_set_get_delete_time_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Sets and gets the time to delete the notification_ex item.
* @scenario			Creates notification_ex button and get item info\n
*				set and get delete time from item info and compare them and Check for Pass/Fail.
* @apicovered			noti_ex_item_info_set_delete_time, noti_ex_item_info_get_delete_time
* @passcase			noti_ex_item_info_set_delete_time, noti_ex_item_info_get_delete_time are successful and return correct value
* @failcase			noti_ex_item_info_set_delete_time, noti_ex_item_info_get_delete_time failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_info_set_get_delete_time_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_info_h hItemInfo = NULL;
	int nSetDeleteTime = 10;
	int nGetDeleteTime;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	nRet = noti_ex_item_get_info(g_hItemButton, &hItemInfo);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_info", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(hItemInfo, "noti_ex_item_get_info", noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_info_set_delete_time(hItemInfo, nSetDeleteTime);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_info_set_delete_time", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_info_get_delete_time(hItemInfo, &nGetDeleteTime);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_info_get_delete_time", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	PRINT_RESULT_CLEANUP(nSetDeleteTime, nGetDeleteTime, "noti_ex_item_info_get_delete_time", "noti_ex_item_info_get_delete_time return value is different from nSetDeleteTime", noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}


//& type : auto
//& purpose: Set and Get the background image path of a style.
/**
* @testcase			ITc_noti_ex_style_set_get_background_image_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Set and Get the background image path from style
* @scenario			Creates the noti_ex_style_h handle \n
*				Get the background image and compare with set image \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_style_set_background_image, noti_ex_style_get_background_image
* @passcase			noti_ex_style_set_background_image, noti_ex_style_get_background_image are successful and return correct value
* @failcase			noti_ex_style_set_background_image, noti_ex_style_get_background_image failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_style_set_get_background_image_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	char pszSetImagePath[PATH_LEN];
	char *pszGetImagePath = NULL;
	char *pszResPath = NULL;

	nRet = CreateStyleAttributes();
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the prerequisite API inside CreateStyleAttributes() is failed \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	pszResPath = app_get_shared_resource_path();
	if ( pszResPath == NULL )
	{
		FPRINTF("[Line : %d][%s] app_get_shared_resource_path failed, error = NULL resource path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	snprintf(pszSetImagePath, sizeof(pszResPath), "%s", pszResPath);

	//Target API
	nRet = noti_ex_style_set_background_image(g_hStyle, pszSetImagePath);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_style_set_background_image", NotificationExGetError(nRet), DestroyStyleAttributes(); FREE_MEMORY(pszResPath));

	//Target API
	nRet = noti_ex_style_get_background_image(g_hStyle, &pszGetImagePath);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_style_get_background_image", NotificationExGetError(nRet), DestroyStyleAttributes(); FREE_MEMORY(pszResPath));
	CHECK_HANDLE_CLEANUP(pszGetImagePath, "noti_ex_style_get_background_image", DestroyStyleAttributes(); FREE_MEMORY(pszResPath));

	if( strncmp(pszSetImagePath, pszGetImagePath, strlen(pszGetImagePath) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_style_get_background_image: return image Path [%s] is different from set image Path [%s]\\n", __LINE__, API_NAMESPACE, pszGetImagePath, pszSetImagePath);
		DestroyStyleAttributes();
		FREE_MEMORY(pszResPath);
		FREE_MEMORY(pszGetImagePath);

		return 1;
	}

	DestroyStyleAttributes();
	FREE_MEMORY(pszResPath);
	FREE_MEMORY(pszGetImagePath);

	return 0;
}

//& type : auto
//& purpose: Set and Get the background color of a style.
/**
* @testcase			ITc_noti_ex_style_set_get_background_color_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Set and Get the background color of a style
* @scenario			Creates the notification_ex item handle for the checkbox \n
*				Get checkbox title and compare with set title \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_style_set_background_color, noti_ex_style_get_background_image
* @passcase			noti_ex_style_set_background_color, noti_ex_style_get_background_image are successful and return correct value
* @failcase			noti_ex_style_set_background_color, noti_ex_style_get_background_image failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_style_set_get_background_color_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_color_h hSetColor = NULL;
	noti_ex_color_h hGetColor = NULL;
	unsigned char cAlpha = 10;
	unsigned char cRed = 20;
	unsigned char cGreen = 30;
	unsigned char cBlue = 40;

	nRet = CreateStyleAttributes();
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the prerequisite API inside CreateStyleAttributes() is failed \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = noti_ex_color_create(&hSetColor, cAlpha, cRed, cGreen, cBlue);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_create", NotificationExGetError(nRet), DestroyStyleAttributes());
	CHECK_HANDLE_CLEANUP(hSetColor, "noti_ex_color_create", DestroyStyleAttributes());

	//Target API
	nRet = noti_ex_style_set_background_color(g_hStyle, hSetColor);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_style_set_background_color", NotificationExGetError(nRet), DestroyStyleAttributes(); noti_ex_color_destroy(hSetColor));

	//Target API
	nRet = noti_ex_style_get_background_color(g_hStyle, &hGetColor);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_style_get_background_color", NotificationExGetError(nRet), DestroyStyleAttributes(); noti_ex_color_destroy(hSetColor));
	CHECK_HANDLE_CLEANUP(hGetColor, "noti_ex_style_get_background_color", DestroyStyleAttributes(); noti_ex_color_destroy(hSetColor));

	DestroyStyleAttributes();

	nRet = noti_ex_color_destroy(hSetColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_color_destroy(hGetColor);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_color_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Checks if an item of a specified type is included in a notification_ex item.
/**
* @testcase			ITc_noti_ex_item_check_type_exist_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Checks if an item of a specified type is included in a notification_ex item.
* @scenario			Creates the notification_ex entry item, get the item type.\n
*				Compare type with created item and check for Pass/Fail.
* @apicovered			noti_ex_item_check_type_exist
* @passcase			noti_ex_item_check_type_exist is successful and return correct value
* @failcase			noti_ex_item_check_type_exist failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_check_type_exist_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_item_h hItemEntry = NULL;
	noti_ex_item_type_e eItemType = NOTI_EX_ITEM_TYPE_ENTRY;
	const char *pszEntryID = "entry_id";
	bool bEntryType = true;
	bool bIsExist = false;

	nRet = noti_ex_item_entry_create(&hItemEntry, pszEntryID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_entry_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemEntry, "noti_ex_item_entry_create");

	//Target API
	nRet = noti_ex_item_check_type_exist(hItemEntry, eItemType, &bIsExist);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_check_type_exist", NotificationExGetError(nRet), noti_ex_item_destroy(hItemEntry));
	PRINT_RESULT_CLEANUP(bEntryType, bIsExist, "noti_ex_item_check_type_exist", NotificationExGetError(nRet), noti_ex_item_destroy(hItemEntry));

	nRet = noti_ex_item_destroy(hItemEntry);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Set and Get the value indicating whether a notification is currently ongoing.
/**
* @testcase			ITc_noti_ex_item_set_get_ongoing_state_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Set and Get the value indicating whether a notification is currently ongoing.
* @scenario			Creates the notification_ex item handle for entry \n
*				Set Ongoing state to true and get state and compare with set state \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_item_set_ongoing_state, noti_ex_item_get_ongoing_state
* @passcase			noti_ex_item_set_ongoing_state, noti_ex_item_get_ongoing_state are successful and return correct value
* @failcase			noti_ex_item_set_ongoing_state, noti_ex_item_get_ongoing_state failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_set_get_ongoing_state_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_item_h hItemEntry = NULL;
	const char *pszEntryID = "entry_id";

	bool bSetOngoing = true;
	bool bIsOngoing = false;

	nRet = noti_ex_item_entry_create(&hItemEntry, pszEntryID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_entry_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemEntry, "noti_ex_item_entry_create");

	//Target API
	nRet = noti_ex_item_set_ongoing_state(hItemEntry, bSetOngoing);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_ongoing_state", NotificationExGetError(nRet), noti_ex_item_destroy(hItemEntry));

	//Target API
	nRet = noti_ex_item_get_ongoing_state(hItemEntry, &bIsOngoing);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_ongoing_state", NotificationExGetError(nRet), noti_ex_item_destroy(hItemEntry));
	PRINT_RESULT_CLEANUP(bSetOngoing, bIsOngoing, "noti_ex_item_get_ongoing_state", "get ongoing return state is not same as set state", noti_ex_item_destroy(hItemEntry));

	nRet = noti_ex_item_destroy(hItemEntry);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}


//& type : auto
//& purpose: Set and Get the main type of a notification item.
/**
* @testcase			ITc_noti_ex_item_set_get_main_type_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Set and Get the main type of a notification item
* @scenario			Creates the notification_ex item handle \n
*				Set Main type for handle of different type \n
*				compare set and get type and check for Pass/Fail.
* @apicovered			noti_ex_item_set_main_type, noti_ex_item_get_main_type
* @passcase			noti_ex_item_set_main_type, noti_ex_item_get_main_type are successful and return correct value
* @failcase			noti_ex_item_set_main_type, noti_ex_item_get_main_type failed or return null value
* @precondition			Create specific item of that type
* @postcondition		Destroy specific handle created to set and get main type.
*/
int ITc_noti_ex_item_set_get_main_type_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_item_h hItemText = NULL;
	const char *pszTextID = "text_id";
	const char *pszTextTitle = "textTitle";
	const char *pszTextHyperLink = "testHyperLink";
	int nMainType = -1;

	noti_ex_item_h hItemImage = NULL;
	const char *pszImageID = "image_id";
	const char *pszImagePath = "image_path";

	noti_ex_item_main_type_e eMainType[] = {
		NOTI_EX_ITEM_MAIN_TYPE_TITLE,
		NOTI_EX_ITEM_MAIN_TYPE_CONTENTS
	};

	nRet = noti_ex_item_text_create(&hItemText, pszTextID, pszTextTitle, pszTextHyperLink);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemText, "noti_ex_item_text_create");

	int nEnumSize = sizeof(eMainType) / sizeof(eMainType[0]);
	int nEnumCounter;

	for ( nEnumCounter=0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		nRet = noti_ex_item_set_main_type(hItemText, pszTextID, eMainType[nEnumCounter]);
		PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_main_type", NotificationExGetError(nRet), noti_ex_item_destroy(hItemText));

		nRet = noti_ex_item_get_main_type(hItemText, &nMainType);
		PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_main_type", NotificationExGetError(nRet), noti_ex_item_destroy(hItemText));
		PRINT_RESULT_CLEANUP(eMainType[nEnumCounter], nMainType, "noti_ex_item_get_main_type", "get main type is not same as set type", noti_ex_item_destroy(hItemText));
	}

	nRet = noti_ex_item_destroy(hItemText);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_image_create(&hItemImage, pszImageID, pszImagePath);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_image_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemImage, "noti_ex_item_image_create");

	nRet = noti_ex_item_set_main_type(hItemImage, pszImageID, NOTI_EX_ITEM_MAIN_TYPE_ICON);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_main_type", NotificationExGetError(nRet), noti_ex_item_destroy(hItemImage));

	nRet = noti_ex_item_get_main_type(hItemImage, &nMainType);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_main_type", NotificationExGetError(nRet), noti_ex_item_destroy(hItemImage));
	PRINT_RESULT_CLEANUP(NOTI_EX_ITEM_MAIN_TYPE_ICON, nMainType, "noti_ex_item_get_main_type", "get main type is not same as set type", noti_ex_item_destroy(hItemImage));

	nRet = noti_ex_item_destroy(hItemImage);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	nRet = noti_ex_item_set_main_type(g_hItemButton, g_pszButtonID, NOTI_EX_ITEM_MAIN_TYPE_BUTTON);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_main_type", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_get_main_type(g_hItemButton, &nMainType);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_main_type", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	PRINT_RESULT_CLEANUP(NOTI_EX_ITEM_MAIN_TYPE_BUTTON, nMainType, "noti_ex_item_get_main_type", "get main type is not same as set type", noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Set and Get the main type of a notification item.
/**
* @testcase			ITc_noti_ex_item_find_by_main_type_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Set and Get the main type of a notification item
* @scenario			Creates the notification_ex item handle for the checkbox \n
*				Get checkbox title and compare with set title \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_style_get_background_image
* @passcase			noti_ex_style_get_background_image is successful and return correct value
* @failcase			noti_ex_style_get_background_image failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_find_by_main_type_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	noti_ex_item_h hItemGroup = NULL;
	noti_ex_item_h hItemText = NULL;
	noti_ex_item_h hGetItemText = NULL;
	const char *pszGroupID = "group_id";
	const char *pszTextID = "text_id";
	const char *pszTextTitle = "textTitle";
	const char *pszTextHyperLink = "testHyperLink";
	int nMainType = NOTI_EX_ITEM_MAIN_TYPE_TITLE;

	nRet = noti_ex_item_group_create(&hItemGroup, pszGroupID);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemGroup, "noti_ex_item_group_create");

	nRet = noti_ex_item_text_create(&hItemText, pszTextID, pszTextTitle, pszTextHyperLink);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_create", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup));
	CHECK_HANDLE_CLEANUP(hItemText, "noti_ex_item_text_create", noti_ex_item_destroy(hItemGroup));

	nRet = noti_ex_item_group_add_child(hItemGroup, hItemText);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_add_child", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(hItemText));

	nRet = noti_ex_item_set_main_type(hItemText, pszTextID, nMainType);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_main_type", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(hItemText));

	//Taregt API
	nRet = noti_ex_item_find_by_main_type(hItemGroup, nMainType, &hGetItemText);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_find_by_main_type", NotificationExGetError(nRet), noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(hItemText));
	CHECK_HANDLE_CLEANUP(hGetItemText, "noti_ex_item_find_by_main_type", noti_ex_item_destroy(hItemGroup); noti_ex_item_destroy(hItemText));

	nRet = noti_ex_item_group_remove_child(hItemGroup, pszTextID);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_group_remove_child", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(hItemText);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(hGetItemText);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(hItemGroup);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}


//& type : auto
//& purpose: Sets and gets extenasion data for notification_ex item.
/**
* @testcase			ITc_noti_ex_item_set_get_extension_data_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type			auto
* @description			Sets and gets extenasion data for notification_ex item.
* @scenario			Creates the notification_ex text item and create bundle value.\n
*				Set items extension, Get it again with the same key and check for Pass/Fail.
* @apicovered			noti_ex_item_set_extension_data, noti_ex_item_get_extension_data
* @passcase			noti_ex_item_set_extension_data, noti_ex_item_get_extension_data are successful and return correct value
* @failcase			noti_ex_item_set_extension_data, noti_ex_item_get_extension_data failed.
* @precondition		NA
* @postcondition		free bundle and Destroy handle.
*/
int ITc_noti_ex_item_set_get_extension_data_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemText = NULL;

	const char *pszTextID = "text_id";
	const char *pszTextTitle = "textTitle";
	const char *pszTextHyperLink = "testHyperLink";
	const char *pszKey = "TEST_KEY";
	const char *pszVal = "TEST_VALUE";
	const char *pszExtKey = "key";

	nRet = noti_ex_item_text_create(&hItemText, pszTextID, pszTextTitle, pszTextHyperLink);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemText, "noti_ex_item_text_create");

	bundle *retBundleVal = NULL;
	bundle *BundleVal = NULL;

	BundleVal = bundle_create();
	CHECK_HANDLE_CLEANUP(BundleVal, "bundle_create", noti_ex_item_destroy(hItemText));

	nRet = bundle_add_str(BundleVal, pszKey, pszVal);
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRet, "bundle_add_str", NotificationExGetError(nRet), bundle_free(BundleVal);noti_ex_item_destroy(hItemText));

	//Target API
	nRet = noti_ex_item_set_extension_data(hItemText, pszExtKey, BundleVal);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_set_extension_data", NotificationExGetError(nRet), bundle_free(BundleVal);noti_ex_item_destroy(hItemText));
	bundle_free(BundleVal);

	//Target API
	nRet = noti_ex_item_get_extension_data(hItemText, pszExtKey, &retBundleVal);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_extension_data", NotificationExGetError(nRet), bundle_free(retBundleVal);noti_ex_item_destroy(hItemText));
	CHECK_HANDLE_CLEANUP(retBundleVal, "noti_ex_item_get_extension_data", noti_ex_item_destroy(hItemText); bundle_free(retBundleVal));
	bundle_free(retBundleVal);

	nRet = noti_ex_item_destroy(hItemText);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
//& type : auto
//& purpose: Gets the time information.
/**
* @testcase			ITc_noti_ex_item_info_get_time_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the time information.
* @scenario			Creates notification_ex button and get item info\n
*				get time information from item info and Check for Pass/Fail.
* @apicovered			noti_ex_item_info_get_time
* @passcase			noti_ex_item_info_get_time is successful and return correct value
* @failcase			noti_ex_item_info_get_time failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_info_get_time_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_info_h hItemInfo = NULL;
	time_t tGetTime;

	nRet = CreateButton();
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_button_create", NotificationExGetError(nRet));
	CHECK_HANDLE(g_hItemButton, "noti_ex_item_button_create");

	nRet = noti_ex_item_get_info(g_hItemButton, &hItemInfo);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_get_info", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));
	CHECK_HANDLE_CLEANUP(hItemInfo, "noti_ex_item_get_info", noti_ex_item_destroy(g_hItemButton));

	//Target API
	nRet = noti_ex_item_info_get_time(hItemInfo, &tGetTime);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_info_get_time", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemButton));

	nRet = noti_ex_item_destroy(g_hItemButton);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

