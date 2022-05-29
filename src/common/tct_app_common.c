//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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

#include "tct_app_common.h"

static bool bIsAppInstalled = false;

/**
 * @function         TCT_CheckInstalledApp
 * @description         Check wheather application is already installed in device or not
 * @parameter        char *pcAppID1 : APP ID , char *pcAppID2 : APP ID
 * @return         void
 */

void TCT_CheckInstalledApp(int num,...)
{
	if(bIsAppInstalled == true)
		return;

	int i;
	char *appId;
	app_info_h appHandle = NULL;
	int nRet;
	va_list valist;
	va_start ( valist, num);

	for ( i = 0; i < num; i++ )
	{
		appId = va_arg(valist, char *);
		nRet = app_info_create(appId, &appHandle);
		if (nRet != APP_MANAGER_ERROR_NONE)
		{
			FPRINTF("[Line : %d]app_info_create failed. Error code - %d \\n", __LINE__, nRet);
			FPRINTF("[Line : %d] WARNING: [%s] application is not installed.\\n", __LINE__, appId);
		}
		else
		{
			FPRINTF("[Line : %d] INFORMATION: [%s] application is installed.\\n", __LINE__, appId);
			app_info_destroy(appHandle);
		}
	}
	va_end(valist);
	bIsAppInstalled = true;
}

/**
 * @function         TCT_UTCCheckInstalledApp
 * @description         Check wheather application is already installed in device or not
 * @parameter        char *pcAppID1 : APP ID , char *pcAppID2 : APP ID
 * @return         void
 */

void TCT_UTCCheckInstalledApp(int num,...)
{
	if(bIsAppInstalled == true)
		return;

	int i;
	char *appId;
	app_info_h appHandle = NULL;
	int nRet;
	va_list valist;
	va_start ( valist, num);

	for ( i = 0; i < num; i++ )	{
		appId = va_arg(valist, char *);
		nRet = app_info_create(appId, &appHandle);
		if (nRet != APP_MANAGER_ERROR_NONE) {
			PRINT_UTC_LOG("[Line : %d]app_info_create failed. Error code - %d \\n", __LINE__, nRet);
			PRINT_UTC_LOG("[Line : %d] WARNING: [%s] application is not installed.\\n", __LINE__, appId);
		} else {
			PRINT_UTC_LOG("[Line : %d] INFORMATION: [%s] application is installed.\\n", __LINE__, appId);
			app_info_destroy(appHandle);
		}
	}
	va_end(valist);
	bIsAppInstalled = true;
}
