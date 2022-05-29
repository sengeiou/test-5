//
// Copyright (c) 2020 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-capi-ui-gesture-common.h"

//& set: CapiUi-gesture

/** @addtogroup itc-capi-ui-gesture
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_capi_ui_gesture_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 		NA
 */
void ITs_capi_ui_gesture_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_capi_ui_gesture_startup\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsFeatureMismatched = false;
	g_bIsGestureFeatureSupported = false;
	g_hHandGesture = NULL;
	int nRet = HAND_GESTURE_ERROR_NONE;

	g_bIsGestureFeatureSupported = TCTCheckSystemInfoFeatureSupported(GESTURE_FEATURE, API_NAMESPACE);

	nRet = hand_gesture_create(&g_hHandGesture);
	if(!g_bIsGestureFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] hand_gesture_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] hand_gesture_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)", __FILE__, __LINE__, nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] hand_gesture_create is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] hand_gesture_create is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
		return;
	}
	else if ( nRet != HAND_GESTURE_ERROR_NONE )
	{
		FPRINTF("[%s:%d] hand_gesture_create failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] hand_gesture_create failed, error returned = (%d)", __FILE__, __LINE__,  nRet);
		g_bGestureHandleCreated = false;
                return;
	}
	if (g_hHandGesture == NULL)
	{
		g_bGestureHandleCreated = false;
		return;
	}
	g_bGestureHandleCreated = true;
}

/**
 * @function 		ITs_capi_ui_gesture_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 		NA
 */
void ITs_capi_ui_gesture_cleanup(void)
{
	int nRet = HAND_GESTURE_ERROR_NONE;

	if (g_hHandGesture)
	{
		nRet = hand_gesture_destroy(g_hHandGesture);
		if ( nRet != HAND_GESTURE_ERROR_NONE )
		{
			FPRINTF("[%s:%d] hand_gesture_destroy failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		}
	}
	return;
}

/**
* @function		HandGestureStartRecognitionCB
* @description		Callback function
* @parameter[IN]	hand_gesture_h hHandGesture, hand_gesture_type_e eTypeGesture,
*			double dnTimestamp, hand_gesture_error_e eGestureError, void *pszUserData
* @return		NA
*/
static void HandGestureStartRecognitionCB(hand_gesture_h hHandGesture, hand_gesture_type_e eTypeGesture, double dnTimestamp, hand_gesture_error_e eGestureError, void *pszUserData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] HandGestureStartRecognitionCB is called\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] In start recognition for HAND_GESTURE_WRIST_UP gesture type recieved error is %s \\n", __LINE__, API_NAMESPACE, GestureGetError(eGestureError));
#endif
}

/**
* @function		HandGestureErrorCB
* @description		Callback function
* @parameter[IN]	hand_gesture_h hHandGesture, hand_gesture_error_e eGestureError,
*			const char *pszMsg, void *pszUserData
* @return		NA
*/
static void HandGestureErrorCB(hand_gesture_h hHandGesture, hand_gesture_error_e eGestureError, const char *pszMsg, void *pszUserData)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] HandGestureErrorCB is called\\n", __LINE__, API_NAMESPACE);
#endif
}


/** @addtogroup itc-capi-ui-gesture-testcases
*  @brief 	Integration testcases for module capi-ui-gesture
*  @ingroup 	itc-capi-ui-gesture
*  @{
*/


//& purpose: To Creates and Destroy a gesture handle
//& type: auto
/**
* @testcase 			ITc_hand_gesture_create_destroy_p
* @since_tizen 			6.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Creates and destroy hand gesture handle.
* @scenario			Creates a gesture handle and destroy if successfully created
* @apicovered			hand_gesture_create, hand_gesture_destroy
* @passcase			If hand_gesture_create and hand_gesture_destroy are successfull
* @failcase 			If hand_gesture_create or hand_gesture_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_hand_gesture_create_destroy_p(void)
{
	START_TEST;

	int nRet = HAND_GESTURE_ERROR_NONE;
	hand_gesture_h hHandGesture = NULL;

	nRet = hand_gesture_create(&hHandGesture);
	PRINT_RESULT(HAND_GESTURE_ERROR_NONE, nRet, "hand_gesture_create", GestureGetError(nRet));
	CHECK_HANDLE(hHandGesture, "hand_gesture_create");

	nRet = hand_gesture_destroy(hHandGesture);
	PRINT_RESULT(HAND_GESTURE_ERROR_NONE, nRet, "hand_gesture_destroy", GestureGetError(nRet));

	return 0;
}

//& purpose: To check whether a gesture is supported or not.
//& type: auto
/**
* @testcase 			ITc_hand_gesture_is_supported_type_p
* @since_tizen 			6.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Checks whether a gesture is supported or not.
* @scenario			create gesture handle and check if supported,
*				destroy handle before cleanup.
* @apicovered			hand_gesture_is_supported_type
* @passcase			hand_gesture_create and hand_gesture_is_supported_type passed
* @failcase 			hand_gesture_create or hand_gesture_is_supported_type failed
* @precondition			NA
* @postcondition		NA
*/

int ITc_hand_gesture_is_supported_type_p(void)
{
	START_TEST;

	int nRet = HAND_GESTURE_ERROR_NONE;
	bool bIsSupported = false;

	//Target API
	nRet = hand_gesture_is_supported_type(g_hHandGesture, HAND_GESTURE_WRIST_UP, &bIsSupported);
	PRINT_RESULT(HAND_GESTURE_ERROR_NONE, nRet, "hand_gesture_is_supported_type", GestureGetError(nRet));

	return 0;
}

//& purpose: To set an option for gesture recognition.
//& type: auto
/**
* @testcase 			ITc_hand_gesture_set_option_p
* @since_tizen 			6.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Sets an option for gesture recognition.
* @scenario			Creates and destroy hand gesture handle and set option.
* @apicovered			hand_gesture_create, hand_gesture_set_option
* @passcase			hand_gesture_create and hand_gesture_set_option passed
* @failcase 			hand_gesture_create or hand_gesture_set_option fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_hand_gesture_set_option_p(void)
{
	START_TEST;

	int nRet = HAND_GESTURE_ERROR_NONE;

	hand_gesture_option_e eHandGastureOption[] =
	{
		HAND_GESTURE_OPTION_DEFAULT,
		HAND_GESTURE_OPTION_ALWAYS_ON
	};

	int nEnumSize = sizeof(eHandGastureOption) / sizeof(eHandGastureOption[0]);
	int nEnumCounter;

	for (nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		//Target API
		nRet = hand_gesture_set_option(g_hHandGesture, eHandGastureOption[nEnumCounter]);
		PRINT_RESULT(HAND_GESTURE_ERROR_NONE, nRet, "hand_gesture_set_option", GestureGetError(nRet));
	}

	return 0;
}

//& purpose: To check start and stop to recognize a gesture.
//& type: auto
/**
* @testcase 			ITc_hand_gesture_start_stop_recognition_p
* @since_tizen 			6.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Starts and stops to recognize a gesture.
* @scenario			Creates and destroy hand gesture handle and check the start recognition
*				with the help of registered callback
* @apicovered			hand_gesture_start_recognition, hand_gesture_stop_recognition
* @passcase			hand_gesture_start_recognition and hand_gesture_stop_recognition passed
* @failcase 			hand_gesture_start_recognition or hand_gesture_stop_recognition fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_hand_gesture_start_stop_recognition_p(void)
{
	START_TEST;

	int nRet = HAND_GESTURE_ERROR_NONE;

	//Target API
	nRet = hand_gesture_start_recognition(g_hHandGesture, HAND_GESTURE_WRIST_UP, HandGestureStartRecognitionCB, NULL);
	PRINT_RESULT(HAND_GESTURE_ERROR_NONE, nRet, "hand_gesture_start_recognition", GestureGetError(nRet));

	//Target API
	nRet = hand_gesture_stop_recognition(g_hHandGesture);
	PRINT_RESULT(HAND_GESTURE_ERROR_NONE, nRet, "hand_gesture_stop_recognition", GestureGetError(nRet));

	return 0;
}

//& purpose: To get a gesture engine information.
//& type: auto
/**
* @testcase 			ITc_hand_gesture_get_engine_info_p
* @since_tizen 			6.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Gets a gesture engine information.
* @scenario			Creates hand gesture handle and get engine info.
* @apicovered			hand_gesture_get_engine_info
* @passcase			hand_gesture_get_engine_info is passed
* @failcase 			hand_gesture_get_engine_info failed.
* @precondition			NA
* @postcondition		NA
*/
int ITc_hand_gesture_get_engine_info_p(void)
{
	START_TEST;

	int nRet = HAND_GESTURE_ERROR_NONE;
	char *pszEngineAppID = NULL;
	char *pszEngineName = NULL;

	//Target API
	nRet = hand_gesture_get_engine_info(g_hHandGesture, &pszEngineAppID, &pszEngineName);
	PRINT_RESULT(HAND_GESTURE_ERROR_NONE, nRet, "hand_gesture_get_engine_info", GestureGetError(nRet));
	CHECK_HANDLE(pszEngineAppID, "hand_gesture_get_engine_info");
	CHECK_HANDLE(pszEngineName, "hand_gesture_get_engine_info");

	return 0;
}

//& purpose: To set and unset a callback function to be invoked when an error is occurred.
//& type: auto
/**
* @testcase 			ITc_hand_gesture_set_unset_error_cb_p
* @since_tizen 			6.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Sets and Unsets a callback function to be invoked when an error is occurred.
* @scenario			Creates hand gesture handle and set and unset callback function.
* @apicovered			hand_gesture_get_engine_info
* @passcase			hand_gesture_set_error_cb and hand_gesture_unset_error_cb
* @failcase 			hand_gesture_set_error_cb or hand_gesture_unset_error_cb failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_hand_gesture_set_unset_error_cb_p(void)
{
	START_TEST;

	int nRet = HAND_GESTURE_ERROR_NONE;

	//Target API
	nRet = hand_gesture_set_error_cb(g_hHandGesture, HandGestureErrorCB, NULL);
	PRINT_RESULT(HAND_GESTURE_ERROR_NONE, nRet, "hand_gesture_set_error_cb", GestureGetError(nRet));

	//Target API
	nRet = hand_gesture_unset_error_cb(g_hHandGesture);
	PRINT_RESULT(HAND_GESTURE_ERROR_NONE, nRet, "hand_gesture_unset_error_cb", GestureGetError(nRet));
	return 0;
}

/** @} */
/** @} */
