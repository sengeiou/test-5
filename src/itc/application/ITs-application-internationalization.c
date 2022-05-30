//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-application-common.h"

/** @addtogroup itc-application
*  @ingroup itc
*  @{
*/
//& set: Application

/**
* @function 		ITs_application_internationalization_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_internationalization_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Application_internationalization_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(2, TEST_HELLOWORLD_APPID, TEST_TESTAPPLICATION_APPID);
	return;
}

/**
* @function 		ITs_application_internationalization_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_internationalization_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Application_internationalization_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type: auto
//& purpose: Call i18n_get_text to get the localized translation for the specified string.
/**
* @testcase 			ITc_application_internationalization_i18n_get_text_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call i18n_get_text to get the localized translation for the specified string.
* @scenario				Call i18n_get_text to get the localized translation for the specified string.
* @apicovered			i18n_get_text
* @passcase				When i18n_get_text is successful and returns correct value
* @failcase				If target API fails or returns incorrect value
* @precondition			None
* @postcondition		None
*/
int ITc_application_internationalization_i18n_get_text_p(void)
{
	START_TEST;

	char* pMessage = "Sample Text for Internationalization";//sample message string

	//Target API
	char* pTranslatedMsg = i18n_get_text(pMessage);
	if ( NULL == pTranslatedMsg )
	{
		FPRINTF("[Line : %d][%s]i18n_get_text failed, values returned = NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

