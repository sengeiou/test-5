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
* @function		ITs_notification_ex_image_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_image_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_image_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_image_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_image_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_image_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type : auto
//& purpose: Creates the notification_ex item handle with an image.
/**
* @testcase			ITc_noti_ex_item_image_create_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates the notification_ex item handle with an image.
* @scenario			Create notification_ex item handle with an image\n
*				Check for handle and check for Pass/Fail.
* @apicovered			noti_ex_item_image_create
* @passcase			noti_ex_item_image_create is successful and return correct value
* @failcase			noti_ex_item_image_create failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_image_create_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemImage = NULL;
	const char *pszImageID = "image_id";
	const char *pszImagePath = "image_path";

	//Target API
	nRet = noti_ex_item_image_create(&hItemImage, pszImageID, pszImagePath);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_image_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemImage, "noti_ex_item_image_create");

	nRet = noti_ex_item_destroy(hItemImage);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the path of image.
/**
* @testcase			ITc_noti_ex_item_image_get_image_path_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the path of image.
* @scenario			Create notification_ex item handle with an image\n
*				Gets the path of image, and compare with set path and check for Pass/Fail.
* @apicovered			noti_ex_item_image_get_image_path
* @passcase			noti_ex_item_image_get_image_path is successful and return correct value
* @failcase			noti_ex_item_image_get_image_path failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_image_get_image_path_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemImage = NULL;
	const char *pszImageID = "image_id";
	const char *pszImagePath = "image_path";
	char *pszGetImagePath = NULL;

	nRet = noti_ex_item_image_create(&hItemImage, pszImageID, pszImagePath);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_image_create", NotificationExGetError(nRet));
	CHECK_HANDLE(hItemImage, "noti_ex_item_image_create");

	//Target API
	nRet = noti_ex_item_image_get_image_path(hItemImage, &pszGetImagePath);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_image_get_image_path", NotificationExGetError(nRet), noti_ex_item_destroy(hItemImage));
	CHECK_HANDLE_CLEANUP(pszGetImagePath, "noti_ex_item_image_get_image_path", noti_ex_item_destroy(hItemImage));

	if( strncmp(pszImagePath, pszGetImagePath, strlen(pszGetImagePath) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_image_get_image_path: return image path is different from set image path [%s]\\n", __LINE__, API_NAMESPACE, pszGetImagePath);
		FREE_MEMORY(pszGetImagePath);

		nRet = noti_ex_item_destroy(hItemImage);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

		return 1;
	}

	FREE_MEMORY(pszGetImagePath);

	nRet = noti_ex_item_destroy(hItemImage);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}
