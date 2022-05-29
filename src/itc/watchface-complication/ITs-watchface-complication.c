//
// Copyright (c) 2018 Samsung Electronics Co., Ltd.
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
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <system_info.h>
#include <app_manager.h>
#include <watchface-complication-provider.h>
#include <watchface-editable.h>
#include <dlog.h>
#include <glib.h>
#include "ITs-watchface-complication-common.h"
#define PROVIDER_ID "org.tizen.watchface_sample_provider/test"
static int nComplicatoinId = 1;

/** @addtogroup itc-watchface-complication
*  @ingroup itc
*  @{
*/


//& set: watchface-complication

/**
* @function 		ITs_watchface_complication_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @nReturn 		NA
*/
void ITs_watchface_complication_startup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Watchface_Complication_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_bWatchApp = TCTCheckSystemInfoFeatureSupported(FEATURE_WATCH_APP, API_NAMESPACE);
	g_bFeatureNotSupported = false;
	g_bIsFeatureMismatched = false;
	return;
}

/**
* @function 		ITs_watchface_complication_cleanup
* @description	 	Called after each test
* @parameter		NA
* @nReturn 		NA
*/
void ITs_watchface_complication_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Watchface_Complication_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/****************************************************Callback Start****************************************************/

/**
* @function 		WatchfaceComplicationUpdatedCb
* @description	 	Callback Function
* @parameters		int nComplicationId, const char *pszProviderId, watchface_complication_type_e eType, const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void WatchfaceComplicationUpdatedCb(int nComplicationId, const char *pszProviderId, watchface_complication_type_e eType, const bundle *pszData, void *pszUserData)
{
	FPRINTF("[Line : %d][%s] %s invoked\\n", __LINE__, API_NAMESPACE, "WatchfaceComplicationUpdatedCb");
	g_bCallBackHit = true;
	return;
}

/**
* @function 		WatchfaceComplicationErrorCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,watchface_complication_error_e eError,void *pszUserData
* @return 		NA
*/
static void WatchfaceComplicationErrorCb(int nComplicationId, const char *pszProviderId,watchface_complication_type_e eType,watchface_complication_error_e eError,void *pszUserData)
{
	FPRINTF("[Line : %d][%s] %s invoked\\n", __LINE__, API_NAMESPACE, "WatchfaceComplicationErrorCb");
	g_bCallBackHit = true;
	return;
}

/**
* @function 		TypeComplicationUpdatedCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/

static void TypeComplicationUpdatedCb(int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData)
{
	char *pszText;
	watchface_complication_type_e eDataType;
	int nRet;

	FPRINTF("[Line : %d][%s] %s invoked\\n", __LINE__, API_NAMESPACE, "TypeComplicationUpdatedCb");
	nRet = watchface_complication_data_get_type(pszData, &eDataType);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_data_get_type", WatchfaceComplicationGetError(nRet));
	if( eDataType <  WATCHFACE_COMPLICATION_TYPE_NO_DATA || eDataType > WATCHFACE_COMPLICATION_TYPE_IMAGE )
	{
		FPRINTF("[Line : %d][%s] %s failed. eDataType = %d\\n", __LINE__, API_NAMESPACE, "watchface_complication_data_get_type", eDataType);
		QuitGmainLoop();
		return;
	}

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		ShortTextComplicationUpdatedCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void ShortTextComplicationUpdatedCb(int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData)
{
	char *pszText = NULL;
	FPRINTF("[Line : %d][%s] %s invoked\\n", __LINE__, API_NAMESPACE, "ShortTextComplicationUpdatedCb");
	int nRet = watchface_complication_data_get_short_text(pszData, &pszText);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_data_get_short_text", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(pszText, "watchface_complication_data_get_short_text");

	FREE_MEMORY(pszText);
	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		LongTextComplicationUpdatedCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void LongTextComplicationUpdatedCb(int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData)
{
	char *pszText = NULL;
	FPRINTF("[Line : %d][%s] %s invoked\\n", __LINE__, API_NAMESPACE, "LongTextComplicationUpdatedCb");
	int nRet = watchface_complication_data_get_long_text(pszData, &pszText);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_data_get_long_text", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(pszText, "watchface_complication_data_get_long_text");
	FREE_MEMORY(pszText);

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		TitleComplicationUpdatedCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void TitleComplicationUpdatedCb(int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData)
{
	char *pszText = NULL;
	FPRINTF("[Line : %d][%s] %s invoked\\n", __LINE__, API_NAMESPACE, "TitleComplicationUpdatedCb");
	int nRet = watchface_complication_data_get_title(pszData, &pszText);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_data_get_title", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(pszText, "watchface_complication_data_get_title");
	FREE_MEMORY(pszText);

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		ImageComplicationUpdatedCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void ImageComplicationUpdatedCb(int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData)
{
	char *pszText;
	int nRet;

	FPRINTF("[Line : %d][%s] %s invoked.\\n", __LINE__, API_NAMESPACE, "ImageComplicationUpdatedCb");
	nRet = watchface_complication_data_get_image_path(pszData, &pszText);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_data_get_image_path", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(pszText, "watchface_complication_data_get_image_path");
	FREE_MEMORY(pszText);

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		RangedValueComplicationUpdatedCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void RangedValueComplicationUpdatedCb(int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData)
{
	char *pszText;
	int nRet;
	double nCurrentValue = -1;
	double nMinValue = -1;
	double nMaxValue = -1;

	FPRINTF("[Line : %d][%s] %s invoked.\\n", __LINE__, API_NAMESPACE, "RangedValueComplicationUpdatedCb");
	nRet = watchface_complication_data_get_ranged_value(pszData, &nCurrentValue, &nMinValue, &nMaxValue);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_data_get_ranged_value", WatchfaceComplicationGetError(nRet));
	if( nCurrentValue < 0 )
	{
		FPRINTF("[Line : %d][%s] %s failed. nCurrentValue = %d\\n", __LINE__, API_NAMESPACE, "watchface_complication_data_get_ranged_value", nCurrentValue);
		QuitGmainLoop();
		return;
	}
	if( nMinValue < 0 )
	{
		FPRINTF("[Line : %d][%s] %s failed. nMinValue = %d\\n", __LINE__, API_NAMESPACE, "watchface_complication_data_get_ranged_value", nMinValue);
		QuitGmainLoop();
		return;
	}
	if( nMaxValue < 0 )
	{
		FPRINTF("[Line : %d][%s] %s failed. nMaxValue = %d\\n", __LINE__, API_NAMESPACE, "watchface_complication_data_get_ranged_value", nMaxValue);
		QuitGmainLoop();
		return;
	}

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		IconComplicationUpdatedCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void IconComplicationUpdatedCb(int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData)
{
	char *pszText = NULL;
	FPRINTF("[Line : %d][%s] %s invoked.\\n", __LINE__, API_NAMESPACE, "IconComplicationUpdatedCb");
	int nRet = watchface_complication_data_get_icon_path(pszData, &pszText);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_data_get_icon_path", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(pszText, "watchface_complication_data_get_icon_path");
	FREE_MEMORY(pszText);

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		ExtraDataComplicationUpdatedCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void ExtraDataComplicationUpdatedCb(int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData)
{
	char *pszExtraData = NULL;

	FPRINTF("[Line : %d][%s] %s invoked.\\n", __LINE__, API_NAMESPACE, "ExtraDataComplicationUpdatedCb");
	int nRet  = watchface_complication_data_get_extra_data(pszData, &pszExtraData);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_data_get_extra_data", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(pszExtraData, "watchface_complication_data_get_extra_data");
	FREE_MEMORY(pszExtraData);

	g_bCallBackHit = true;
	return;
}

static void ScreenReaderCb(int nComplicationId, const char *pszProviderId, watchface_complication_type_e eType, const bundle *pszData, void *pszUserData)
{
	char *pszText = NULL;

	FPRINTF("[Line : %d][%s] %s invoked.\\n", __LINE__, API_NAMESPACE, "ScreenReaderCb");
	int nRet = watchface_complication_data_get_screen_reader_text(pszData, &pszText);
	CALLBACK_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_data_get_screen_reader_text", WatchfaceComplicationGetError(nRet));
	CALLBACK_CHECK_HANDLE_EXIT(pszText, "watchface_complication_data_get_screen_reader_text");
	FREE_MEMORY(pszText);

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		GetTimeInfoComplicationCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void GetTimeInfoComplicationCb(int nComplicationId, const char *pszProviderId, watchface_complication_type_e eType, const bundle *pszData, void *pszUserData)
{
	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;
	complication_time_info_h hComlicationTimeInfo = NULL;
	watchface_complication_type_e eComplicationType;

	FPRINTF("[Line : %d][%s] %s invoked.\\n", __LINE__, API_NAMESPACE, "GetTimeInfoComplicationCb");

	nRet = watchface_complication_data_get_type(pszData, &eComplicationType);
	CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_type", WatchfaceComplicationGetError(nRet));

	if(eComplicationType == WATCHFACE_COMPLICATION_TYPE_TIME)
	{
		nRet = watchface_complication_data_get_timeinfo(pszData, &hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_timeinfo", WatchfaceComplicationGetError(nRet));
		CALLBACK_CHECK_HANDLE_EXIT(hComlicationTimeInfo, "watchface_complication_data_get_timeinfo");

		nRet = watchface_complication_timeinfo_destroy(hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_destroy", WatchfaceComplicationGetError(nRet));
	}

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		GetTimeZoneComplicationCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void GetTimeZoneComplicationCb(int nComplicationId, const char *pszProviderId, watchface_complication_type_e eType, const bundle *pszData, void *pszUserData)
{
	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;
	char *pszGetTimeZone = NULL;
	complication_time_info_h hComlicationTimeInfo = NULL;
	watchface_complication_type_e eComplicationType;

	FPRINTF("[Line : %d][%s] %s invoked.\\n", __LINE__, API_NAMESPACE, "GetTimeZoneComplicationCb");

	nRet = watchface_complication_data_get_type(pszData, &eComplicationType);
	CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_type", WatchfaceComplicationGetError(nRet));

	if(eComplicationType == WATCHFACE_COMPLICATION_TYPE_TIME)
	{
		nRet = watchface_complication_data_get_timeinfo(pszData, &hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_timeinfo", WatchfaceComplicationGetError(nRet));
		CALLBACK_CHECK_HANDLE_EXIT(hComlicationTimeInfo, "watchface_complication_data_get_timeinfo");

		nRet = watchface_complication_timeinfo_get_timezone(hComlicationTimeInfo, &pszGetTimeZone);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_get_timezone", WatchfaceComplicationGetError(nRet));
		CALLBACK_CHECK_HANDLE_EXIT(pszGetTimeZone, "watchface_complication_timeinfo_get_timezone");

		if(strncmp(pszGetTimeZone, "UTC+9", strlen("UTC+9")))
		{
			FPRINTF("[Line : %d][%s] watchface_complication_timeinfo_get_timezone failed. pszGetTimeZone = %s\\n", __LINE__, API_NAMESPACE, pszGetTimeZone);
			FREE_MEMORY(pszGetTimeZone);

			nRet = watchface_complication_timeinfo_destroy(hComlicationTimeInfo);
			CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_destroy", WatchfaceComplicationGetError(nRet));

			QuitGmainLoop();
			return;
		}
		FREE_MEMORY(pszGetTimeZone);

		nRet = watchface_complication_timeinfo_destroy(hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_destroy", WatchfaceComplicationGetError(nRet));
	}

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		GetTimeZoneIDComplicationCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void GetTimeZoneIDComplicationCb(int nComplicationId, const char *pszProviderId, watchface_complication_type_e eType, const bundle *pszData, void *pszUserData)
{
	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;
	char *pszGetTimeZoneID = NULL;
	complication_time_info_h hComlicationTimeInfo = NULL;
	watchface_complication_type_e eComplicationType;

	FPRINTF("[Line : %d][%s] %s invoked.\\n", __LINE__, API_NAMESPACE, "GetTimeZoneIDComplicationCb");

	nRet = watchface_complication_data_get_type(pszData, &eComplicationType);
	CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_type", WatchfaceComplicationGetError(nRet));

	if(eComplicationType == WATCHFACE_COMPLICATION_TYPE_TIME)
	{
		nRet = watchface_complication_data_get_timeinfo(pszData, &hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_timeinfo", WatchfaceComplicationGetError(nRet));
		CALLBACK_CHECK_HANDLE_EXIT(hComlicationTimeInfo, "watchface_complication_data_get_timeinfo");

		nRet = watchface_complication_timeinfo_get_timezone_id(hComlicationTimeInfo, &pszGetTimeZoneID);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_get_timezone_id", WatchfaceComplicationGetError(nRet));
		CALLBACK_CHECK_HANDLE_EXIT(pszGetTimeZoneID, "watchface_complication_timeinfo_get_timezone_id");

		if(strncmp(pszGetTimeZoneID, "Asia/Seoul", strlen("Asia/Seoul")))
		{
			FPRINTF("[Line : %d][%s] watchface_complication_timeinfo_get_timezone_id failed. pszGetTimeZoneID = %s\\n", __LINE__, API_NAMESPACE, pszGetTimeZoneID);
			FREE_MEMORY(pszGetTimeZoneID);

			nRet = watchface_complication_timeinfo_destroy(hComlicationTimeInfo);
			CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_destroy", WatchfaceComplicationGetError(nRet));

			QuitGmainLoop();
			return;
		}
		FREE_MEMORY(pszGetTimeZoneID);

		nRet = watchface_complication_timeinfo_destroy(hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_destroy", WatchfaceComplicationGetError(nRet));
	}

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		GetTimeZoneCountryComplicationCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void GetTimeZoneCountryComplicationCb(int nComplicationId, const char *pszProviderId, watchface_complication_type_e eType, const bundle *pszData, void *pszUserData)
{
	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;
	char *pszGetTimeZoneCtry = NULL;
	complication_time_info_h hComlicationTimeInfo = NULL;
	watchface_complication_type_e eComplicationType;

	FPRINTF("[Line : %d][%s] %s invoked.\\n", __LINE__, API_NAMESPACE, "GetTimeZoneCountryComplicationCb");

	nRet = watchface_complication_data_get_type(pszData, &eComplicationType);
	CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_type", WatchfaceComplicationGetError(nRet));

	if(eComplicationType == WATCHFACE_COMPLICATION_TYPE_TIME)
	{
		nRet = watchface_complication_data_get_timeinfo(pszData, &hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_timeinfo", WatchfaceComplicationGetError(nRet));
		CALLBACK_CHECK_HANDLE_EXIT(hComlicationTimeInfo, "watchface_complication_data_get_timeinfo");

		nRet = watchface_complication_timeinfo_get_timezone_country(hComlicationTimeInfo, &pszGetTimeZoneCtry);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_get_timezone_country", WatchfaceComplicationGetError(nRet));
		CALLBACK_CHECK_HANDLE_EXIT(pszGetTimeZoneCtry, "watchface_complication_timeinfo_get_timezone_country");

		if(strncmp(pszGetTimeZoneCtry, "Korea", strlen("Korea")))
		{
			FPRINTF("[Line : %d][%s] watchface_complication_timeinfo_get_timezone_country failed. pszGetTimeZoneCtry = %s\\n", __LINE__, API_NAMESPACE, pszGetTimeZoneCtry);
			FREE_MEMORY(pszGetTimeZoneCtry);

			nRet = watchface_complication_timeinfo_destroy(hComlicationTimeInfo);
			CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_destroy", WatchfaceComplicationGetError(nRet));

			QuitGmainLoop();
			return;
		}
		FREE_MEMORY(pszGetTimeZoneCtry);

		nRet = watchface_complication_timeinfo_destroy(hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_destroy", WatchfaceComplicationGetError(nRet));
	}

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		GetTimeZoneCityComplicationCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void GetTimeZoneCityComplicationCb(int nComplicationId, const char *pszProviderId, watchface_complication_type_e eType, const bundle *pszData, void *pszUserData)
{
	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;
	char *pszGetTimeZoneCity = NULL;
	complication_time_info_h hComlicationTimeInfo = NULL;
	watchface_complication_type_e eComplicationType;

	FPRINTF("[Line : %d][%s] %s invoked.\\n", __LINE__, API_NAMESPACE, "GetTimeZoneCityComplicationCb");

	nRet = watchface_complication_data_get_type(pszData, &eComplicationType);
	CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_type", WatchfaceComplicationGetError(nRet));

	if(eComplicationType == WATCHFACE_COMPLICATION_TYPE_TIME)
	{
		nRet = watchface_complication_data_get_timeinfo(pszData, &hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_timeinfo", WatchfaceComplicationGetError(nRet));
		CALLBACK_CHECK_HANDLE_EXIT(hComlicationTimeInfo, "watchface_complication_data_get_timeinfo");

		nRet = watchface_complication_timeinfo_get_timezone_city(hComlicationTimeInfo, &pszGetTimeZoneCity);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_get_timezone_city", WatchfaceComplicationGetError(nRet));
		CALLBACK_CHECK_HANDLE_EXIT(pszGetTimeZoneCity, "watchface_complication_timeinfo_get_timezone_city");

		if(strncmp(pszGetTimeZoneCity, "Seoul", strlen("Seoul")))
		{
			FPRINTF("[Line : %d][%s] watchface_complication_timeinfo_get_timezone_city failed. pszGetTimeZoneCity = %s\\n", __LINE__, API_NAMESPACE, pszGetTimeZoneCity);
			FREE_MEMORY(pszGetTimeZoneCity);

			nRet = watchface_complication_timeinfo_destroy(hComlicationTimeInfo);
			CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_destroy", WatchfaceComplicationGetError(nRet));

			QuitGmainLoop();
			return;
		}
		FREE_MEMORY(pszGetTimeZoneCity);

		nRet = watchface_complication_timeinfo_destroy(hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_destroy", WatchfaceComplicationGetError(nRet));
	}

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		GetTimeStampComplicationCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void GetTimeStampComplicationCb(int nComplicationId, const char *pszProviderId, watchface_complication_type_e eType, const bundle *pszData, void *pszUserData)
{
	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;
	time_t tTimeStamp;
	watchface_complication_type_e eComplicationType;
	complication_time_info_h hComlicationTimeInfo = NULL;

	FPRINTF("[Line : %d][%s] %s invoked.\\n", __LINE__, API_NAMESPACE, "GetTimeStampComplicationCb");

	nRet = watchface_complication_data_get_type(pszData, &eComplicationType);
	CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_type", WatchfaceComplicationGetError(nRet));

	if(eComplicationType == WATCHFACE_COMPLICATION_TYPE_TIME)
	{
		nRet = watchface_complication_data_get_timeinfo(pszData, &hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_timeinfo", WatchfaceComplicationGetError(nRet));
		CALLBACK_CHECK_HANDLE_EXIT(hComlicationTimeInfo, "watchface_complication_data_get_timeinfo");

		nRet = watchface_complication_timeinfo_get_timestamp(hComlicationTimeInfo, &tTimeStamp);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_get_timestamp", WatchfaceComplicationGetError(nRet));

		nRet = watchface_complication_timeinfo_destroy(hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_destroy", WatchfaceComplicationGetError(nRet));
	}

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/**
* @function 		TimeInfoDestroyComplicationCb
* @description	 	Callback Function
* @parameters		int nComplicationId,const char *pszProviderId,watchface_complication_type_e eType,const bundle *pszData, void *pszUserData
* @return 		NA
*/
static void TimeInfoDestroyComplicationCb(int nComplicationId, const char *pszProviderId, watchface_complication_type_e eType, const bundle *pszData, void *pszUserData)
{
	int nRet = WATCHFACE_COMPLICATION_ERROR_NONE;
	watchface_complication_type_e eComplicationType;
	complication_time_info_h hComlicationTimeInfo = NULL;

	FPRINTF("[Line : %d][%s] %s invoked.\\n", __LINE__, API_NAMESPACE, "TimeInfoDestroyComplicationCb");

	nRet = watchface_complication_data_get_type(pszData, &eComplicationType);
	CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_type", WatchfaceComplicationGetError(nRet));

	if(eComplicationType == WATCHFACE_COMPLICATION_TYPE_TIME)
	{
		nRet = watchface_complication_data_get_timeinfo(pszData, &hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_data_get_extra_data", WatchfaceComplicationGetError(nRet));
		CALLBACK_CHECK_HANDLE_EXIT(hComlicationTimeInfo, "watchface_complication_data_get_extra_data");

		nRet = watchface_complication_timeinfo_destroy(hComlicationTimeInfo);
		CALLBACK_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_timeinfo_destroy", WatchfaceComplicationGetError(nRet));
	}

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}


/*****************************************************Callback End*****************************************************/
//& purpose: To get the id of provider in the complication
//& type: auto
/**
* @testcase				ITc_watchface_complication_get_current_provider_id_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets the id of provider in the complication.
* @scenario				Gets the id of provider in the complication.
* @apicovered				watchface_complication_get_current_provider_id
* @passcase				watchface_complication_get_current_provider_id returns 0
* @failcase				watchface_complication_get_current_provider_id returns 1
* @precondition				Complication handle should be created by watchface_complication_create().
* @postcondition			N/A
* */
int ITc_watchface_complication_get_current_provider_id_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	char *pszCurProvider = NULL;
	int nRet = 0;

	nComplicatoinId++;
	nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_get_current_provider_id(hHandle, &pszCurProvider);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_get_current_provider_id", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));
	CHECK_HANDLE_EXIT_CLEANUP(pszCurProvider, "watchface_complication_get_current_provider_id", watchface_complication_destroy(hHandle));
	FREE_MEMORY(pszCurProvider);

	nRet = watchface_complication_destroy(hHandle);
	PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_destroy", WatchfaceComplicationGetError(nRet));

	service_app_exit();
	return 0;
}

//& purpose: To get the currently set type of the complication
//& type: auto
/**
* @testcase				ITc_watchface_complication_get_current_type_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets the currently set type of the complication.
* @scenario				Gets the currently set type of the complication.
* @apicovered				watchface_complication_get_current_type
* @passcase				watchface_complication_get_current_type returns 0
* @failcase				watchface_complication_get_current_type returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_get_current_type_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	int nRet = 0;
	watchface_complication_type_e eCurType;

	nComplicatoinId++;
	nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(WATCHFACE_COMPLICATION_ERROR_NONE, nRet, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_get_current_type(hHandle, &eCurType);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_get_current_type", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));
	if( eCurType <  WATCHFACE_COMPLICATION_TYPE_NO_DATA || eCurType > WATCHFACE_COMPLICATION_TYPE_IMAGE )
	{
		FPRINTF("[Line : %d][%s] %s failed. eCurType = %d\\n", __LINE__, API_NAMESPACE, "watchface_complication_get_current_type", eCurType);
		watchface_complication_destroy(hHandle);
		service_app_exit();
		return 1;
	}

	nRet = watchface_complication_destroy(hHandle);
	PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_destroy", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To add and remove the callback function to use for complication update
//& type: auto
/**
* @testcase				ITc_watchface_complication_add__update_remove_updated_cb_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Adds and removes the callback function to use for complication update.
* @scenario				Adds and removes the callback function to use for complication update.
* @apicovered				watchface_complication_add_updated_cb, watchface_complication_send_update_request, watchface_complication_remove_updated_cb
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Complication handle should be created by watchface_complication_create().
* @postcondition			N/A
* */
int ITc_watchface_complication_add_update_remove_updated_cb_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	nComplicatoinId++;

	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, WatchfaceComplicationUpdatedCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	g_bCallBackHit = false;

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, WatchfaceComplicationUpdatedCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "WatchfaceComplicationUpdatedCb");
		nRet = watchface_complication_remove_updated_cb(hHandle, WatchfaceComplicationUpdatedCb);
		PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_remove_updated_cb", WatchfaceComplicationGetError(nRet));
		nRet = watchface_complication_destroy(hHandle);
		PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_destroy", WatchfaceComplicationGetError(nRet));
		service_app_exit();
		return 1;
	}

	nRet = watchface_complication_remove_updated_cb(hHandle, WatchfaceComplicationUpdatedCb);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_remove_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	nRet = watchface_complication_destroy(hHandle);
	PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_destroy", WatchfaceComplicationGetError(nRet));
	service_app_exit();

	return 0;
}

//& purpose: To create and destroy a complication handle
//& type: auto
/**
* @testcase				ITc_watchface_complication_create_destroy_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Creates and destroys a complication handle.
* @scenario				Creates and destroys a complication handle.
* @apicovered				watchface_complication_create, watchface_complication_destroy
* @passcase				watchface_complication_create_destroy returns 0
* @failcase				watchface_complication_create_destroy returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_create_destroy_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	int nRet = 0;

	nComplicatoinId++;
	nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_destroy(hHandle);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_destroy", WatchfaceComplicationGetError(nRet));
	service_app_exit();
	return 0;
}

//& purpose: To get data type of complication data.
//& type: auto
/**
* @testcase				ITc_watchface_complication_data_get_type_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets data type of complication data.
* @scenario				Gets data type of complication data.
* @apicovered				watchface_complication_data_get_type
* @passcase				watchface_complication_data_get_type returns 0
* @failcase				watchface_complication_data_get_type returns 1
* @precondition				N/A
* @postcondition			N/A
* */

int ITc_watchface_complication_data_get_type_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;

	nComplicatoinId++;
	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, TypeComplicationUpdatedCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	g_bCallBackHit = false;
	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, TypeComplicationUpdatedCb); watchface_complication_destroy(hHandle));
	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "TypeComplicationUpdatedCb");
		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, TypeComplicationUpdatedCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, TypeComplicationUpdatedCb, nRet);
	return 0;
}

//& purpose: To get short text from complication data
//& type: auto
/**
* @testcase				ITc_watchface_complication_data_get_short_text_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets short text from complication data.
* @scenario				Gets short text from complication data.
* @apicovered				watchface_complication_data_get_short_text
* @passcase				watchface_complication_data_get_short_text returns 0
* @failcase				watchface_complication_data_get_short_text returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_data_get_short_text_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	g_bCallBackHit = false;

	nComplicatoinId++;
	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, ShortTextComplicationUpdatedCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, ShortTextComplicationUpdatedCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "ShortTextComplicationUpdatedCb");
		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, ShortTextComplicationUpdatedCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, ShortTextComplicationUpdatedCb, nRet);
	return 0;
}

//& purpose: To get long text from complication data
//& type: auto
/**
* @testcase				ITc_watchface_complication_data_get_long_text_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets long text from complication data.
* @scenario				Gets long text from complication data.
* @apicovered				watchface_complication_data_get_long_text
* @passcase				watchface_complication_data_get_long_text returns 0
* @failcase				watchface_complication_data_get_long_text returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_data_get_long_text_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;

	nComplicatoinId++;
	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_LONG_TEXT, WATCHFACE_COMPLICATION_TYPE_LONG_TEXT, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, LongTextComplicationUpdatedCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	g_bCallBackHit = false;
	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, LongTextComplicationUpdatedCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "LongTextComplicationUpdatedCb");
		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, LongTextComplicationUpdatedCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, LongTextComplicationUpdatedCb, nRet);
	return 0;
}

//& purpose: To get title text from complication data
//& type: auto
/**
* @testcase				ITc_watchface_complication_data_get_title_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets title text from complication data.
* @scenario				Gets title text from complication data.
* @apicovered				watchface_complication_data_get_title
* @passcase				watchface_complication_data_get_title returns 0
* @failcase				watchface_complication_data_get_title returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_data_get_title_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	nComplicatoinId++;

	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_LONG_TEXT, WATCHFACE_COMPLICATION_TYPE_LONG_TEXT, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, TitleComplicationUpdatedCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	g_bCallBackHit = false;

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, TitleComplicationUpdatedCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "TitleComplicationUpdatedCb");
		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, TitleComplicationUpdatedCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, TitleComplicationUpdatedCb, nRet);
	return 0;
}

//& purpose: To get image path from complication data
//& type: auto
/**
* @testcase				ITc_watchface_complication_data_get_image_path_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets image path from complication data.
* @scenario				Gets image path from complication data.
* @apicovered				watchface_complication_data_get_image_path
* @passcase				watchface_complication_data_get_image_path returns 0
* @failcase				watchface_complication_data_get_image_path returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_data_get_image_path_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	g_bCallBackHit = false;

	nComplicatoinId++;
	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_IMAGE, WATCHFACE_COMPLICATION_TYPE_IMAGE, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, ImageComplicationUpdatedCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));


	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, ImageComplicationUpdatedCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "ImageComplicationUpdatedCb");
		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, ImageComplicationUpdatedCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, ImageComplicationUpdatedCb, nRet);
	return 0;
}

//& purpose: To get ranged value from complication data
//& type: auto
/**
* @testcase				ITc_watchface_complication_data_get_ranged_value_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets ranged value from complication data.
* @scenario				Gets ranged value from complication data.
* @apicovered				watchface_complication_data_get_ranged_value
* @passcase				watchface_complication_data_get_ranged_value returns 0
* @failcase				watchface_complication_data_get_ranged_value returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_data_get_ranged_value_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	g_bCallBackHit = false;

	nComplicatoinId++;
	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_RANGED_VALUE, WATCHFACE_COMPLICATION_TYPE_RANGED_VALUE, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, RangedValueComplicationUpdatedCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, RangedValueComplicationUpdatedCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "RangedValueComplicationUpdatedCb");
		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, RangedValueComplicationUpdatedCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, RangedValueComplicationUpdatedCb, nRet);
	return 0;
}

//& purpose: To get icon path from complication data
//& type: auto
/**
* @testcase				ITc_watchface_complication_data_get_icon_path_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets icon path from complication data.
* @scenario				Gets icon path from complication data.
* @apicovered				watchface_complication_data_get_icon_path
* @passcase				watchface_complication_data_get_icon_path returns 0
* @failcase				watchface_complication_data_get_icon_path returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_data_get_icon_path_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	g_bCallBackHit = false;

	nComplicatoinId++;
	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_ICON, WATCHFACE_COMPLICATION_TYPE_ICON, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, IconComplicationUpdatedCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, IconComplicationUpdatedCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "IconComplicationUpdatedCb");
		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, IconComplicationUpdatedCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, IconComplicationUpdatedCb, nRet);
	return 0;
}

//& purpose: To get extra data from complication data
//& type: auto
/**
* @testcase				ITc_watchface_complication_data_get_extra_data_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets extra data from complication data.
* @scenario				Gets extra data from complication data.
* @apicovered				watchface_complication_data_get_extra_data
* @passcase				watchface_complication_data_get_extra_data returns 0
* @failcase				watchface_complication_data_get_extra_data returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_data_get_extra_data_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	g_bCallBackHit = false;
	nComplicatoinId++;

	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_ICON, WATCHFACE_COMPLICATION_TYPE_ICON, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, ExtraDataComplicationUpdatedCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, ExtraDataComplicationUpdatedCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "ExtraDataComplicationUpdatedCb");
		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, ExtraDataComplicationUpdatedCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, ExtraDataComplicationUpdatedCb, nRet);
	return 0;
}

//& purpose: To create and destroy allowed list
//& type: auto
/**
* @testcase				ITc_watchface_complication_allowed_list_create_destroy_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Creates and destroys allowed list.
* @scenario				Creates and destroys allowed list.
* @apicovered				watchface_complication_allowed_list_create, watchface_complication_allowed_list_destroy
* @passcase				watchface_complication_allowed_list_create, watchface_complication_allowed_list_destroy return 0
* @failcase				watchface_complication_allowed_list_create, watchface_complication_allowed_list_destroy return 1
* @precondition				N/A
* @postcondition			N/A
* */

int ITc_watchface_complication_allowed_list_create_destroy_p(void)
{
	START_TEST;
	complication_allowed_list_h hHandle = NULL;
	int nRet = 0;

	nRet = watchface_complication_allowed_list_create(&hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_allowed_list_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE(hHandle, "watchface_complication_allowed_list_create");

	nRet = watchface_complication_allowed_list_destroy(hHandle);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_destroy", WatchfaceComplicationGetError(nRet));

	service_app_exit();
	return 0;
}

//& purpose: To add and delete provider info from the allowed list
//& type: auto
/**
* @testcase				ITc_watchface_complication_allowed_list_add_delete_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Adds and deletes provider info from the allowed list.
* @scenario				Adds and deletes provider info from the allowed list.
* @apicovered				watchface_complication_allowed_list_add, watchface_complication_allowed_list_delete
* @passcase				watchface_complication_allowed_list_add, watchface_complication_allowed_list_delete returns 0
* @failcase				watchface_complication_allowed_list_add, watchface_complication_allowed_list_delete returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_allowed_list_add_delete_p(void)
{
	START_TEST;
	complication_allowed_list_h hHandle = NULL;
	int nRet = 0;

	nRet = watchface_complication_allowed_list_create(&hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_allowed_list_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_allowed_list_create");

	nRet = watchface_complication_allowed_list_add(hHandle, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_add", WatchfaceComplicationGetError(nRet), watchface_complication_allowed_list_destroy(hHandle));

	nRet = watchface_complication_allowed_list_delete(hHandle, PROVIDER_ID);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_delete", WatchfaceComplicationGetError(nRet), watchface_complication_allowed_list_destroy(hHandle));

	nRet = watchface_complication_allowed_list_destroy(hHandle);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_destroy", WatchfaceComplicationGetError(nRet));

	service_app_exit();
	return 0;
}

//& purpose: To get n-th item of the allowed list
//& type: auto
/**
* @testcase				ITc_watchface_complication_allowed_list_get_nth_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets n-th item of the allowed list.
* @scenario				Gets n-th item of the allowed list.
* @apicovered				watchface_complication_allowed_list_get_nth
* @passcase				watchface_complication_allowed_list_get_nth returns 0
* @failcase				watchface_complication_allowed_list_get_nth returns 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_allowed_list_get_nth_p(void)
{
	START_TEST;
	complication_allowed_list_h hHandle = NULL;
	char *pszProviderId = NULL;
	int nIndex = 0;
	int nTypes = -1;
	int nRet = 0;

	nRet = watchface_complication_allowed_list_create(&hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_allowed_list_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_allowed_list_create");

	nRet = watchface_complication_allowed_list_add(hHandle, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_add", WatchfaceComplicationGetError(nRet), watchface_complication_allowed_list_destroy(hHandle));

	nRet = watchface_complication_allowed_list_get_nth(hHandle, nIndex, &pszProviderId, &nTypes);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_get_nth", WatchfaceComplicationGetError(nRet), watchface_complication_allowed_list_destroy(hHandle));
	CHECK_HANDLE_EXIT_CLEANUP(pszProviderId, "watchface_complication_allowed_list_get_nth", watchface_complication_allowed_list_destroy(hHandle));

	if(strncmp(pszProviderId, PROVIDER_ID, strlen(pszProviderId)) != 0)
	{
		FPRINTF("[Line : %d][%s] %s failed. pszProviderId = %s\\n", __LINE__, API_NAMESPACE, "watchface_complication_allowed_list_get_nth", pszProviderId);
		FREE_MEMORY(pszProviderId);
		watchface_complication_allowed_list_destroy(hHandle);
		return 1;
	}
	FREE_MEMORY(pszProviderId);

	if( nTypes < 0 )
	{
		FPRINTF("[Line : %d][%s] %s failed. nTypes = %d\\n", __LINE__, API_NAMESPACE, "watchface_complication_allowed_list_get_nth", nTypes);
		watchface_complication_allowed_list_destroy(hHandle);
		return 1;
	}

	nRet = watchface_complication_allowed_list_destroy(hHandle);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_destroy", WatchfaceComplicationGetError(nRet));

	service_app_exit();
	return 0;
}

//& purpose: To apply and clear the allowed list to a complication
//& type: auto
/**
* @testcase				ITc_watchface_complication_allowed_list_apply_clear_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Applies and clears the allowed list to a complication.
* @scenario				Applies and clears the allowed list to a complication.
* @apicovered				watchface_complication_allowed_list_apply, watchface_complication_allowed_list_clear
* @passcase				watchface_complication_allowed_list_apply, watchface_complication_allowed_list_clear return 0
* @failcase				watchface_complication_allowed_list_apply, watchface_complication_allowed_list_clear return 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_allowed_list_apply_clear_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	complication_allowed_list_h hListHandle = NULL;

	nComplicatoinId++;
	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_allowed_list_create(&hListHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_create", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));
	CHECK_HANDLE_EXIT_CLEANUP(hListHandle, "watchface_complication_allowed_list_create", watchface_complication_destroy(hHandle));

	nRet = watchface_complication_allowed_list_add(hListHandle, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_SHORT_TEXT);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_add", WatchfaceComplicationGetError(nRet), watchface_complication_allowed_list_destroy(hListHandle); watchface_complication_destroy(hHandle));

	nRet = watchface_complication_allowed_list_apply(hHandle, hListHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_apply", WatchfaceComplicationGetError(nRet), watchface_complication_allowed_list_destroy(hListHandle); watchface_complication_destroy(hHandle));

	nRet = watchface_complication_allowed_list_clear(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_clear", WatchfaceComplicationGetError(nRet), watchface_complication_allowed_list_destroy(hListHandle); watchface_complication_destroy(hHandle));

	nRet = watchface_complication_allowed_list_destroy(hListHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_allowed_list_destroy", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	nRet = watchface_complication_destroy(hHandle);
	PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_destroy", WatchfaceComplicationGetError(nRet));

	service_app_exit();
	return 0;
}

//& purpose: To get screen reader text from complication data
//& type: auto
/**
* @testcase				ITc_watchface_complication_data_get_screen_reader_text_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Gets screen reader text from complication data.
* @scenario				Gets screen reader text from complication data.
* @apicovered				watchface_complication_data_get_screen_reader_text
* @passcase				watchface_complication_data_get_screen_reader_text return 0
* @failcase				watchface_complication_data_get_screen_reader_text return 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_data_get_screen_reader_text_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	nComplicatoinId++;
	g_bCallBackHit = false;

	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_ICON, WATCHFACE_COMPLICATION_TYPE_ICON,
			WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, ScreenReaderCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet));

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "ScreenReaderCb");
		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, RangedValueComplicationUpdatedCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, RangedValueComplicationUpdatedCb, nRet);
	return 0;
}

//& purpose: To transfer touch event to the complication provider
//& type: auto
/**
* @testcase				ITc_watchface_complication_transfer_event_p
* @since_tizen				5.0
* @author				SRID(samuel.peter)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description				Transfers touch event to the complication provider.
* @scenario				Transfers touch event to the complication provider.
* @apicovered				watchface_complication_transfer_event
* @passcase				watchface_complication_transfer_event return 0
* @failcase				watchface_complication_transfer_event return 1
* @precondition				N/A
* @postcondition			N/A
* */
int ITc_watchface_complication_transfer_event_p(void)
{
	START_TEST;
	complication_h hHandle;
	nComplicatoinId++;

	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_ICON, WATCHFACE_COMPLICATION_TYPE_ICON,
			WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));

	nRet = watchface_complication_add_updated_cb(hHandle, ScreenReaderCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet));

	nRet = watchface_complication_transfer_event(hHandle, WATCHFACE_COMPLICATION_EVENT_TAP);
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_transfer_event", WatchfaceComplicationGetError(nRet));

	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, ScreenReaderCb, nRet);
	return 0;
}

//& purpose: To get timeinfo from complication data.
//& type: auto
/**
* @testcase				ITc_watchface_complication_data_get_timeinfo_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Gets timeinfo from complication data.
* @scenario				Gets timeinfo from complication data.
* @apicovered				watchface_complication_data_get_timeinfo
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Complication handle should be created by watchface_complication_create().
* @postcondition			Complication handle should be created by watchface_complication_destroy().
* */
int ITc_watchface_complication_data_get_timeinfo_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	nComplicatoinId++;

	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, GetTimeInfoComplicationCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	g_bCallBackHit = false;

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, GetTimeInfoComplicationCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] GetTimeInfoComplicationCb was not hit.\\n", __LINE__, API_NAMESPACE);

		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, GetTimeInfoComplicationCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, GetTimeInfoComplicationCb, nRet);
	return 0;
}

//& purpose: To get timezone from timeinfo.
//& type: auto
/**
* @testcase				ITc_watchface_complication_timeinfo_get_timezone_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Gets timezone from timeinfo.
* @scenario				Gets timezone from timeinfo.
* @apicovered				watchface_complication_timeinfo_get_timezone
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Complication handle should be created by watchface_complication_create().
* @postcondition			Complication handle should be created by watchface_complication_destroy().
* */
int ITc_watchface_complication_timeinfo_get_timezone_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	nComplicatoinId++;

	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, GetTimeZoneComplicationCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	g_bCallBackHit = false;

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, GetTimeZoneComplicationCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "GetTimeZoneComplicationCb");

		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, GetTimeZoneComplicationCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, GetTimeZoneComplicationCb, nRet);
	return 0;
}

//& purpose: To get timezone ID from timeinfo
//& type: auto
/**
* @testcase				ITc_watchface_complication_timeinfo_get_timezone_id_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Gets timezone ID from timeinfo
* @scenario				Gets timezone ID from timeinfo
* @apicovered				watchface_complication_timeinfo_get_timezone_id
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Complication handle should be created by watchface_complication_create().
* @postcondition			Complication handle should be created by watchface_complication_destroy().
* */
int ITc_watchface_complication_timeinfo_get_timezone_id_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	nComplicatoinId++;

	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, GetTimeZoneIDComplicationCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	g_bCallBackHit = false;

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, GetTimeZoneIDComplicationCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "GetTimeZoneIDComplicationCb");

		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, GetTimeZoneIDComplicationCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, GetTimeZoneIDComplicationCb, nRet);
	return 0;
}

//& purpose: To get timezone country from timeinfo
//& type: auto
/**
* @testcase				ITc_watchface_complication_timeinfo_get_timezone_country_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Gets timezone country from timeinfo.
* @scenario				Gets timezone country from timeinfo.
* @apicovered				watchface_complication_timeinfo_get_timezone_country
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Complication handle should be created by watchface_complication_create().
* @postcondition			Complication handle should be created by watchface_complication_destroy().
* */
int ITc_watchface_complication_timeinfo_get_timezone_country_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	nComplicatoinId++;

	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, GetTimeZoneCountryComplicationCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	g_bCallBackHit = false;

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, GetTimeZoneCountryComplicationCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "GetTimeZoneCountryComplicationCb");

		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, GetTimeZoneCountryComplicationCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, GetTimeZoneCountryComplicationCb, nRet);
	return 0;
}

//& purpose: To get timezone city from timeinfo
//& type: auto
/**
* @testcase				ITc_watchface_complication_timeinfo_get_timezone_city_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Gets timezone city from timeinfo
* @scenario				Gets timezone city from timeinfo
* @apicovered				watchface_complication_timeinfo_get_timezone_city
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Complication handle should be created by watchface_complication_create().
* @postcondition			Complication handle should be created by watchface_complication_destroy().
* */
int ITc_watchface_complication_timeinfo_get_timezone_city_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	nComplicatoinId++;

	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, GetTimeZoneCityComplicationCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	g_bCallBackHit = false;

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, GetTimeZoneCityComplicationCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "GetTimeZoneCityComplicationCb");

		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, GetTimeZoneCityComplicationCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, GetTimeZoneCityComplicationCb, nRet);
	return 0;
}

//& purpose: To get timestamp from timeinfo
//& type: auto
/**
* @testcase				ITc_watchface_complication_timeinfo_get_timestamp_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Gets timestamp from timeinfo
* @scenario				Gets timestamp from timeinfo
* @apicovered				watchface_complication_timeinfo_get_timestamp
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Complication handle should be created by watchface_complication_create().
* @postcondition			Complication handle should be created by watchface_complication_destroy().
* */
int ITc_watchface_complication_timeinfo_get_timestamp_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	nComplicatoinId++;

	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, GetTimeStampComplicationCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	g_bCallBackHit = false;

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, GetTimeStampComplicationCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "GetTimeStampComplicationCb");

		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, GetTimeStampComplicationCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, GetTimeStampComplicationCb, nRet);
	return 0;
}

//& purpose: To destroy time information handle
//& type: auto
/**
* @testcase				ITc_watchface_complication_timeinfo_destroy_p
* @since_tizen				5.5
* @author				SRID(j.abhishek)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description				Destroys time information handle
* @scenario				Destroys time information handle
* @apicovered				watchface_complication_timeinfo_destroy
* @passcase				Target APIs return 0
* @failcase				Target APIs return 1
* @precondition				Complication handle should be created by watchface_complication_create().
* @postcondition			Complication handle should be created by watchface_complication_destroy().
* */
int ITc_watchface_complication_timeinfo_destroy_p(void)
{
	START_TEST;
	complication_h hHandle = NULL;
	nComplicatoinId++;

	int nRet = watchface_complication_create(nComplicatoinId, PROVIDER_ID, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_TYPE_TIME, WATCHFACE_COMPLICATION_EVENT_NONE, &hHandle);
	ISFEATURE_SUPPORTED_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED, "watchface_complication_create");
	PRINT_RESULT_EXIT(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_create", WatchfaceComplicationGetError(nRet));
	CHECK_HANDLE_EXIT(hHandle, "watchface_complication_create");

	nRet = watchface_complication_add_updated_cb(hHandle, TimeInfoDestroyComplicationCb, WatchfaceComplicationErrorCb, NULL);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_add_updated_cb", WatchfaceComplicationGetError(nRet), watchface_complication_destroy(hHandle));

	g_bCallBackHit = false;

	nRet = watchface_complication_send_update_request(hHandle);
	PRINT_RESULT_EXIT_CLEANUP(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_send_update_request", WatchfaceComplicationGetError(nRet), watchface_complication_remove_updated_cb(hHandle, TimeInfoDestroyComplicationCb); watchface_complication_destroy(hHandle));

	IterateGmainLoop();
	if(!g_bCallBackHit)
	{
		FPRINTF("[Line : %d][%s] %s was not hit.\\n", __LINE__, API_NAMESPACE, "TimeInfoDestroyComplicationCb");

		WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, TimeInfoDestroyComplicationCb, nRet);
		return 1;
	}
	WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, TimeInfoDestroyComplicationCb, nRet);
	return 0;
}

