//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
#include "ITs-libfeedback-common.h"

/** @addtogroup itc-feedback
*  @ingroup itc
*  @{
*/

//& set: Feedback
bool bIsHAPTICFeatureSupported;

//Add  related feature here
#define HAPTIC_FEATURE				"http://tizen.org/feature/feedback.vibration"

stFeedbackType g_stFeedbackType[] = {
	{ FEEDBACK_TYPE_NONE, "FEEDBACK_TYPE_NONE" },
	{ FEEDBACK_TYPE_SOUND, "FEEDBACK_TYPE_SOUND" },
	{ FEEDBACK_TYPE_VIBRATION, "FEEDBACK_TYPE_VIBRATION" },
	{ FEEDBACK_TYPE_END, "FEEDBACK_TYPE_END" }
};

unsigned int g_nFeedbackTypeCount = sizeof(g_stFeedbackType) / sizeof(g_stFeedbackType[0]);

stFeedbackPattern g_stFeedbackPattern[] = {
	{ FEEDBACK_PATTERN_TAP, "FEEDBACK_PATTERN_TAP" },
	{ FEEDBACK_PATTERN_SIP, "FEEDBACK_PATTERN_SIP" },
	{ FEEDBACK_PATTERN_KEY0, "FEEDBACK_PATTERN_KEY0" },
	{ FEEDBACK_PATTERN_KEY1, "FEEDBACK_PATTERN_KEY1" },
	{ FEEDBACK_PATTERN_KEY2, "FEEDBACK_PATTERN_KEY2" },
	{ FEEDBACK_PATTERN_KEY3, "FEEDBACK_PATTERN_KEY3" },
	{ FEEDBACK_PATTERN_KEY4, "FEEDBACK_PATTERN_KEY4" },
	{ FEEDBACK_PATTERN_KEY5, "FEEDBACK_PATTERN_KEY5" },
	{ FEEDBACK_PATTERN_KEY6, "FEEDBACK_PATTERN_KEY6" },
	{ FEEDBACK_PATTERN_KEY7, "FEEDBACK_PATTERN_KEY7" },
	{ FEEDBACK_PATTERN_KEY8, "FEEDBACK_PATTERN_KEY8" },
	{ FEEDBACK_PATTERN_KEY9, "FEEDBACK_PATTERN_KEY9" },
	{ FEEDBACK_PATTERN_KEY_STAR, "FEEDBACK_PATTERN_KEY_STAR" },
	{ FEEDBACK_PATTERN_KEY_SHARP, "FEEDBACK_PATTERN_KEY_SHARP" },
	{ FEEDBACK_PATTERN_KEY_BACK, "FEEDBACK_PATTERN_KEY_BACK" },
	{ FEEDBACK_PATTERN_HOLD, "FEEDBACK_PATTERN_HOLD" },
	{ FEEDBACK_PATTERN_HW_TAP, "FEEDBACK_PATTERN_HW_TAP" },
	{ FEEDBACK_PATTERN_HW_HOLD, "FEEDBACK_PATTERN_HW_HOLD" },
	{ FEEDBACK_PATTERN_MESSAGE, "FEEDBACK_PATTERN_MESSAGE" },
	{ FEEDBACK_PATTERN_EMAIL, "FEEDBACK_PATTERN_EMAIL" },
	{ FEEDBACK_PATTERN_WAKEUP, "FEEDBACK_PATTERN_WAKEUP" },
	{ FEEDBACK_PATTERN_SCHEDULE, "FEEDBACK_PATTERN_SCHEDULE" }, 
	{ FEEDBACK_PATTERN_TIMER, "FEEDBACK_PATTERN_TIMER" },
	{ FEEDBACK_PATTERN_GENERAL, "FEEDBACK_PATTERN_GENERAL" },
	{ FEEDBACK_PATTERN_POWERON, "FEEDBACK_PATTERN_POWERON" },
	{ FEEDBACK_PATTERN_POWEROFF, "FEEDBACK_PATTERN_POWEROFF" },
	{ FEEDBACK_PATTERN_CHARGERCONN, "FEEDBACK_PATTERN_CHARGERCONN" },
	{ FEEDBACK_PATTERN_CHARGING_ERROR, "FEEDBACK_PATTERN_CHARGING_ERROR" },
	{ FEEDBACK_PATTERN_FULLCHARGED, "FEEDBACK_PATTERN_FULLCHARGED" },
	{ FEEDBACK_PATTERN_LOWBATT, "FEEDBACK_PATTERN_LOWBATT" },
	{ FEEDBACK_PATTERN_LOCK, "FEEDBACK_PATTERN_LOCK" },
	{ FEEDBACK_PATTERN_UNLOCK, "FEEDBACK_PATTERN_UNLOCK" },
	{ FEEDBACK_PATTERN_VIBRATION_ON, "FEEDBACK_PATTERN_VIBRATION_ON" },
	{ FEEDBACK_PATTERN_SILENT_OFF, "FEEDBACK_PATTERN_SILENT_OFF" },
	{ FEEDBACK_PATTERN_BT_CONNECTED, "FEEDBACK_PATTERN_BT_CONNECTED" },
	{ FEEDBACK_PATTERN_BT_DISCONNECTED, "FEEDBACK_PATTERN_BT_DISCONNECTED" },
	{ FEEDBACK_PATTERN_LIST_REORDER, "FEEDBACK_PATTERN_LIST_REORDER" },
	{ FEEDBACK_PATTERN_LIST_SLIDER, "FEEDBACK_PATTERN_LIST_SLIDER" },
	{ FEEDBACK_PATTERN_VOLUME_KEY, "FEEDBACK_PATTERN_VOLUME_KEY" }
};

unsigned int g_nFeedbackPatternCount = sizeof(g_stFeedbackPattern) / sizeof(g_stFeedbackPattern[0]);

bool g_bFeedbackInit;

/**
* @function 		ITs_feedback_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_feedback_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Feedback_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = feedback_initialize();
	if ( nRet == FEEDBACK_ERROR_NONE )
	{
		g_bFeedbackInit = true;
	}
	else
	{
		FPRINTF("[Line : %d][%s] feedback_initialize failed in startup, error = %s\\n", __LINE__, API_NAMESPACE, FeedbackGetError(nRet));
		g_bFeedbackInit = false;
	}

	bIsHAPTICFeatureSupported = false;
	IS_FEATURE_SUPPORTED(HAPTIC_FEATURE, bIsHAPTICFeatureSupported, API_NAMESPACE);
}

/**
* @function 		ITs_feedback_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_feedback_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Feedback_p\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_bFeedbackInit )
	{
		int eRetValue = feedback_deinitialize();
		if ( FEEDBACK_ERROR_NONE == eRetValue )
		{
			g_bFeedbackInit = false;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feedback_deinitialize failed in cleanup, error = %s\\n", __LINE__, API_NAMESPACE, FeedbackGetError(eRetValue));
		}
	}
}

/** @addtogroup itc-feedback-testcases
*  @brief 		Integration testcases for module feedback
*  @ingroup 	itc-feedback
*  @{
*/

//& purpose: Initializes and deinitializes feedback
//& type: auto
/**
* @testcase 			ITc_feedback_initialize_deinitialize_p
* @since_tizen			2.4
* @author            	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To initialize and deinitialize feedback API
* @scenario				Initialize feedback\n
* 						Deinitialize feedback
* @apicovered			feedback_initialize, feedback_deinitialize
* @passcase				If feedback_initialize and feedback_deinitialize APIs are successful
* @failcase				If feedback_initialize or feedback_deinitialize API is failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_feedback_initialize_deinitialize_p(void)
{
	START_TEST;

	//Precondition
	int nRet = feedback_deinitialize();
	PRINT_RESULT(FEEDBACK_ERROR_NONE, nRet, "feedback_deinitialize", FeedbackGetError(nRet));

	//Target API
	nRet = feedback_initialize();
	PRINT_RESULT(FEEDBACK_ERROR_NONE, nRet, "feedback_initialize", FeedbackGetError(nRet));

	//Target API
	nRet = feedback_deinitialize();
	PRINT_RESULT(FEEDBACK_ERROR_NONE, nRet, "feedback_deinitialize", FeedbackGetError(nRet));

	nRet = feedback_initialize();
	PRINT_RESULT(FEEDBACK_ERROR_NONE, nRet, "feedback_initialize", FeedbackGetError(nRet));

	return 0;
}

//& purpose: Plays and stops various type of reactions e.g media or vibration patterns
//& type: auto
/**
* @testcase 			ITc_feedback_play_stop_p
* @since_tizen			2.4
* @author            	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Play and stop various type of reactions e.g media or vibration patterns
* @scenario				Play all type of reactions supported\n
*						Stop all type of reactions supported
* @apicovered			feedback_play, feedback_stop
* @passcase				If feedback_play returns success
* @failcase				If feedback_play returns fail
* @precondition			play feedback before calling feedback_stop
* @postcondition		NA
*/
int ITc_feedback_play_stop_p(void)
{
	START_TEST;

	int nRet = 0, nPatternCount = 0;

	if (!bIsHAPTICFeatureSupported)
		return 0;

	for ( nPatternCount = 0; nPatternCount < g_nFeedbackPatternCount; nPatternCount++ )
	{
		//Target API
		FPRINTF("[Line : %d][%s] feedback_play API execution for ePattern (%s)\\n", __LINE__, API_NAMESPACE, g_stFeedbackPattern[nPatternCount].szPattern);
		nRet = feedback_play(g_stFeedbackPattern[nPatternCount].ePattern);
		PRINT_RESULT(FEEDBACK_ERROR_NONE, nRet, "feedback_play", FeedbackGetError(nRet));
	}

	nRet = feedback_stop();
	PRINT_RESULT(FEEDBACK_ERROR_NONE, nRet, "feedback_stop", FeedbackGetError(nRet));

	return 0;
}

//& purpose: Plays specific type of reactions that are predefined
//& type: auto
/**
* @testcase 			ITc_feedback_play_type_p
* @since_tizen			2.4
* @author            	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Play specific type of reactions that are predefined
* @scenario				Play all specific type of reactions supported
* @apicovered			feedback_play_type, feedback_stop
* @passcase				If feedback_play_type returns success
* @failcase				If feedback_play_type returns fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_feedback_play_type_p(void)
{
	START_TEST;

	int nRet = 0, nPatternCount = 0, nTypeCount = 0;
	bool bStatus;
	for ( nTypeCount = 1; nTypeCount < g_nFeedbackTypeCount-1; nTypeCount++ )
	{
		for ( nPatternCount = 0; nPatternCount < g_nFeedbackPatternCount; nPatternCount++ )
		{
			if (g_stFeedbackType[nTypeCount].eType == FEEDBACK_TYPE_VIBRATION && !bIsHAPTICFeatureSupported)
				return 0;

			nRet = feedback_is_supported_pattern(g_stFeedbackType[nTypeCount].eType, g_stFeedbackPattern[nPatternCount].ePattern, &bStatus);
			FPRINTF("[Line : %d][%s] feedback_is_supported_pattern API execution for type = (%s) and pattern = (%s) : %d\\n", __LINE__, API_NAMESPACE, g_stFeedbackType[nTypeCount].szType, g_stFeedbackPattern[nPatternCount].szPattern , bStatus);

			PRINT_RESULT(FEEDBACK_ERROR_NONE, nRet, "feedback_is_supported_pattern", FeedbackGetError(nRet));

			if (!bStatus)
				continue;

			//Target API
			nRet = feedback_play_type(g_stFeedbackType[nTypeCount].eType, g_stFeedbackPattern[nPatternCount].ePattern);
			PRINT_RESULT(FEEDBACK_ERROR_NONE, nRet, "feedback_play_type", FeedbackGetError(nRet));

		}
	}

	nRet = feedback_stop();
	PRINT_RESULT(FEEDBACK_ERROR_NONE, nRet, "feedback_stop", FeedbackGetError(nRet));

	return 0;
}

//& purpose: Checks if the feedback pattern of a specific type is supported
//& type: auto
/**
 * @testcase 				ITc_feedback_is_supported_pattern_p
 * @since_tizen				2.4
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Checks if the feedback pattern of a specific type is supported
 * @scenario				Check if the feedback pattern of a specific type is supported
 * @apicovered				feedback_is_supported_pattern
 * @passcase				If feedback_is_supported_pattern  is successful
 * @failcase				If feedback_is_supported_pattern is failed
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_feedback_is_supported_pattern_p(void)
{
	START_TEST;

	int nRet = 0, nPatternCount = 0, nTypeCount = 0;
	bool bStatus;
	for ( nTypeCount = 1; nTypeCount < g_nFeedbackTypeCount-1; nTypeCount++ )
	{
		for ( nPatternCount=0; nPatternCount<g_nFeedbackPatternCount; nPatternCount++ )
		{
			if (g_stFeedbackType[nTypeCount].eType == FEEDBACK_TYPE_VIBRATION && !bIsHAPTICFeatureSupported)
				return 0;

			//Target API
			nRet = feedback_is_supported_pattern(g_stFeedbackType[nTypeCount].eType, g_stFeedbackPattern[nPatternCount].ePattern, &bStatus);
			PRINT_RESULT(FEEDBACK_ERROR_NONE, nRet, "feedback_is_supported_pattern", FeedbackGetError(nRet));
		}
	}
	return 0;
}

/** @} */
/** @} */
