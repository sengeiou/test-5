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
* @function             ReporterEventsErrorCB
* @description          CallBack function
* @parameter            NA
* @return               NA
*/

void ReporterEventsErrorCB(noti_ex_reporter_h hExReporter, noti_ex_error_e eExError, int nReqID, void *data)
{
	g_CallBackHit = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] ReporterEventsErrorCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif
}
/**
* @function             ReporterEventsEventCB
* @description          CallBack function
* @parameter            NA
* @return               NA
*/

void ReporterEventsEventCB(noti_ex_reporter_h hExReporter, noti_ex_event_info_h hEventInfo, noti_ex_item_h *hAddedItem, int nCnt, void *pszData)
{
	g_CallBackHit = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] ReporterEventsEventCB Callback Invoked\\n", __LINE__, API_NAMESPACE);
#endif
}
/**
* @function		ITs_notification_ex_reporter_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_reporter_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_reporter_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_reporter_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_reporter_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_reporter_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/**
* @testcase			ITc_noti_ex_reporter_create_destroy_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates and Destroys the notification_ex manager handle.
* @scenario			Creates notification_ex reporter and reporter event handler \n
*				register event and error callbacks and Check for pass/fail.
* @apicovered			noti_ex_reporter_create, noti_ex_reporter_destroy
* @passcase			noti_ex_reporter_create and noti_ex_reporter_destroy are successful and return correct value
* @failcase			noti_ex_reporter_create and/or noti_ex_reporter_destroy failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_noti_ex_reporter_create_destroy_p(void)
{
	START_TEST;
        noti_ex_reporter_h hExReporter;
	int nRet = NOTI_EX_ERROR_NONE;
        int nTimeoutId = 0;

	noti_ex_reporter_events_s hEventReporter = {0};
	hEventReporter.event = ReporterEventsEventCB;
	hEventReporter.error = ReporterEventsErrorCB;

	//Target API
	nRet = noti_ex_reporter_create(&hExReporter, hEventReporter, NULL);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hExReporter, "noti_ex_reporter_create");

	//Target API
        nRet = noti_ex_reporter_destroy(hExReporter);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_destroy", NotificationExGetError(nRet));



	return 0;
}

//& type : auto
//& purpose: Posts a notification.
/**
* @testcase                     ITc_noti_ex_reporter_post_p
* @since_tizen                  5.5
* @author                       SRID(j.abhishek)
* @reviewer                     SRID(shobhit.v)
* @type                         auto
* @description                  Posts a notification.
* @scenario                     Creates notification_ex reporter handle and manager event handler \n
*                               register add callback, create Notification list with helper function \n
*                               post notification list on handler to invoke callback, check for callback hit.
* @apicovered                   noti_ex_reporter_post
* @passcase                     noti_ex_reporter_post is successful and return correct value
* @failcase                     callback not hit or noti_ex_reporter_post failed
* @precondition                 NA
* @postcondition                NA
*/

int ITc_noti_ex_reporter_post_p(void)
{
        START_TEST;

        noti_ex_item_h *hNotiList = NULL;
        int nTimeoutId = 0;
        int nReqID;
        int nRet = NOTI_EX_ERROR_NONE;
        g_CallBackHit = false;

        nRet = CreateNotificationList(&hNotiList);
        if(nRet)
        {
                FPRINTF("[Line : %d][%s] One of the API called inside CreateNotificationList() is failed and returned \\n", __LINE__, API_NAMESPACE);
                if(hNotiList != NULL)
                {
                        FREE_MEMORY(hNotiList);
                }
                return 1;
        }

        //Target API
        nRet = noti_ex_reporter_post(g_hEventinfoReporter, hNotiList[0], &nReqID);
        PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_post", NotificationExGetError(nRet), FREE_MEMORY(hNotiList));

        FREE_MEMORY(hNotiList);
        return 0;
}
//& type : auto
//& purpose: Posts notifications contained in a list.
/**
* @testcase			ITc_noti_ex_reporter_post_list_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Posts notifications contained in a list.
* @scenario			Creates notification_ex reporter handle and manager event handler \n
*				register add callback, create Notification list with helper function \n
*				post notification list on handler to invoke callback, check for callback hit.
* @apicovered			noti_ex_reporter_post_list
* @passcase			noti_ex_reporter_post_list is successful and return correct value
* @failcase			callback not hit or noti_ex_reporter_post_list failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_noti_ex_reporter_post_list_p(void)
{
	START_TEST;

	noti_ex_item_h *hNotiList = NULL;
	int nTimeoutId = 0;
	int nReqID;
	int nRet = NOTI_EX_ERROR_NONE;
	g_CallBackHit = false;

	nRet = CreateNotificationList(&hNotiList);
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the API called inside CreateNotificationList() is failed and returned \\n", __LINE__, API_NAMESPACE);
                if(hNotiList != NULL)
                {
                        FREE_MEMORY(hNotiList);
                }
		return 1;
	}

	//Target API
	nRet = noti_ex_reporter_post_list(g_hEventinfoReporter, hNotiList, 1, &nReqID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_post_list", NotificationExGetError(nRet), FREE_MEMORY(hNotiList));

        FREE_MEMORY(hNotiList);
	return 0;
}

//& type : auto
//& purpose: Updates a notification.
/**
* @testcase			ITc_noti_ex_reporter_update_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Updates a notification.
* @scenario			Creates notification_ex reporter handle and manager event handler \n
*				register add callback, create Notification list with helper function \n
*				post notification list on handler to invoke callback, check for callback hit.
* @apicovered			noti_ex_reporter_update
* @passcase			noti_ex_reporter_update is successful and return correct value
* @failcase			callback not hit or noti_ex_reporter_update failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_noti_ex_reporter_update_p(void)
{
	START_TEST;

	noti_ex_item_h *hNotiList = NULL;
        noti_ex_item_h hItem;
	int nTimeoutId = 0;
	int nReqID;
	int nRet = NOTI_EX_ERROR_NONE;
	g_CallBackHit = false;

	nRet = CreateNotificationList(&hNotiList);
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the API called inside CreateNotificationList() is failed and returned \\n", __LINE__, API_NAMESPACE);
                if(hNotiList != NULL)
                {
                        FREE_MEMORY(hNotiList);
                }
		return 1;
	}

	nRet = noti_ex_reporter_post(g_hEventinfoReporter, hNotiList[0], &nReqID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_post", NotificationExGetError(nRet), FREE_MEMORY(hNotiList));

	nRet = noti_ex_reporter_find_by_root_id(g_hEventinfoReporter, "test_group", &hItem);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_find_by_root_id", NotificationExGetError(nRet), FREE_MEMORY(hNotiList));

	nRet = noti_ex_reporter_update(g_hEventinfoReporter, hNotiList[0], &nReqID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_update", NotificationExGetError(nRet), FREE_MEMORY(hNotiList));

        FREE_MEMORY(hNotiList);
	return 0;
}

//& type : auto
//& purpose: Deletes a notification.
/**
* @testcase			ITc_noti_ex_reporter_delete_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Deletes a notification.
* @scenario			Creates notification_ex reporter handle and manager event handler \n
*				register add callback, create Notification list with helper function \n
*				post notification list on handler to invoke callback, check for callback hit.
* @apicovered			noti_ex_reporter_delete
* @passcase			noti_ex_reporter_delete is successful and return correct value
* @failcase			callback not hit or noti_ex_reporter_delete failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_noti_ex_reporter_delete_p(void)
{
	START_TEST;

	noti_ex_item_h *hNotiList = NULL;
        noti_ex_item_h hItem;
	int nTimeoutId = 0;
	int nReqID;
	int nRet = NOTI_EX_ERROR_NONE;
	g_CallBackHit = false;

	nRet = CreateNotificationList(&hNotiList);
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the API called inside CreateNotificationList() is failed and returned \\n", __LINE__, API_NAMESPACE);
                if(hNotiList != NULL)
                {
                        FREE_MEMORY(hNotiList);
                }
		return 1;
	}

	nRet = noti_ex_reporter_post(g_hEventinfoReporter, hNotiList[0], &nReqID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_post", NotificationExGetError(nRet), FREE_MEMORY(hNotiList));

        nRet = noti_ex_reporter_find_by_root_id(g_hEventinfoReporter, "test_group", &hItem);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_find_by_root_id", NotificationExGetError(nRet), FREE_MEMORY(hNotiList));

        nRet = noti_ex_reporter_delete(g_hEventinfoReporter, hNotiList[0], &nReqID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_delete", NotificationExGetError(nRet), FREE_MEMORY(hNotiList));

        FREE_MEMORY(hNotiList);

	return 0;
}

//& type : auto
//& purpose: Deletes all notification.
/**
* @testcase			ITc_noti_ex_reporter_delete_all_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Deletes all notification.
* @scenario			Creates notification_ex reporter handle and manager event handler \n
*				register add callback, create Notification list with helper function \n
*				post notification list on handler to invoke callback, check for callback hit.
* @apicovered			noti_ex_reporter_delete_all
* @passcase			noti_ex_reporter_delete_all is successful and return correct value
* @failcase			callback not hit or noti_ex_reporter_delete_all failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_noti_ex_reporter_delete_all_p(void)
{
	START_TEST;

	noti_ex_item_h *hNotiList = NULL;
	int nTimeoutId = 0;
	int nReqID;
	int nRet = NOTI_EX_ERROR_NONE;
	g_CallBackHit = false;

	nRet = CreateNotificationList(&hNotiList);
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the API called inside CreateNotificationList() is failed and returned \\n", __LINE__, API_NAMESPACE);
                if(hNotiList != NULL)
                {
                        FREE_MEMORY(hNotiList);
                }
		return 1;
	}

	nRet = noti_ex_reporter_post(g_hEventinfoReporter, hNotiList[0], &nReqID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_post", NotificationExGetError(nRet), FREE_MEMORY(hNotiList));

        nRet = noti_ex_reporter_delete_all(g_hEventinfoReporter, &nReqID);
        PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_delete_all", NotificationExGetError(nRet), FREE_MEMORY(hNotiList));

        FREE_MEMORY(hNotiList);

	return 0;
}

//& type : auto
//& purpose: Finds notification by root id.
/**
* @testcase			ITc_noti_ex_reporter_find_by_root_id_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Finds notification by root id.
* @scenario			Creates notification_ex reporter handle and manager event handler \n
*				register add callback, create Notification list with helper function \n
*				post notification list on handler to invoke callback, check for callback hit.
* @apicovered			noti_ex_reporter_find_by_root_id
* @passcase			noti_ex_reporter_find_by_root_id is successful and return correct value
* @failcase			callback not hit or noti_ex_reporter_find_by_root_id failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_noti_ex_reporter_find_by_root_id_p(void)
{
	START_TEST;

	noti_ex_item_h *hNotiList = NULL;
	int nTimeoutId = 0;
	int nReqID;
	int nRet = NOTI_EX_ERROR_NONE;
        noti_ex_item_h hItem;
	g_CallBackHit = false;

	nRet = CreateNotificationList(&hNotiList);
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the API called inside CreateNotificationList() is failed and returned \\n", __LINE__, API_NAMESPACE);
                if(hNotiList != NULL)
                {
                        FREE_MEMORY(hNotiList);
                }
		return 1;
	}

	nRet = noti_ex_reporter_post(g_hEventinfoReporter, hNotiList[0], &nReqID);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_post", NotificationExGetError(nRet), FREE_MEMORY(hNotiList));

        nRet = noti_ex_reporter_find_by_root_id(g_hEventinfoReporter, "test_group", &hItem);
        PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_reporter_find_by_root_id", NotificationExGetError(nRet), FREE_MEMORY(hNotiList));

        FREE_MEMORY(hNotiList);

	return 0;
}
