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
* @function		ITs_notification_ex_multi_language_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_multi_language_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_multi_language_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_multi_language_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_multi_language_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_multi_language_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& type : auto
//& purpose: Creates and Destroys the multi-language item handle
/**
* @testcase			ITc_noti_ex_multi_lang_create_destroy_p
* @since_tizen			5.5
* @author			SRID(manu.tiwari)
* @reviewer			SRID(j.abhishek)
* @type				auto
* @description			Creates and Destroys the multi-language item handle
* @scenario			Creates the notification_ex multi langauge handle and destroy \n
*				and check for Pass/Fail.
* @apicovered			noti_ex_style_get_background_image
* @passcase			noti_ex_style_get_background_image is successful and return correct value
* @failcase			noti_ex_style_get_background_image failed or return null value
* @precondition			NA
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_multi_lang_create_destroy_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;

	//Target API
	nRet = CreateMultiLangHandle();
	PRINT_RESULT(0, nRet, "noti_ex_multi_lang_create", "API failed or handle not created successfully");

	//Target API
	nRet = noti_ex_multi_lang_destroy(g_hMultiLang);
	PRINT_RESULT(NOTI_EX_ERROR_NONE, nRet, "noti_ex_multi_lang_destroy", NotificationExGetError(nRet));

	return 0;
}
