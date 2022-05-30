#include "CTs-platform-permission-common.h"

#include <feedback.h>


typedef struct {
	feedback_type_e eType;
	char* szType;
} stFeedbackType;

typedef struct {
	feedback_pattern_e ePattern;
	char* szPattern;
} stFeedbackPattern;


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

/**
 * @function 		FeedbackGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char *FeedbackGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch(nRet)
	{
		case FEEDBACK_ERROR_NONE : szErrorVal = "FEEDBACK_ERROR_NONE " ; break; 
		case FEEDBACK_ERROR_INVALID_PARAMETER : szErrorVal = "FEEDBACK_ERROR_INVALID_PARAMETER" ; break; 
		case FEEDBACK_ERROR_NOT_INITIALIZED : szErrorVal = "FEEDBACK_ERROR_NOT_INITIALIZED" ; break; 
		case FEEDBACK_ERROR_OPERATION_FAILED : szErrorVal = "FEEDBACK_ERROR_OPERATION_FAILED" ; break;
		case FEEDBACK_ERROR_PERMISSION_DENIED : szErrorVal = "FEEDBACK_ERROR_PERMISSION_DENIED" ; break; 
		case FEEDBACK_ERROR_NOT_SUPPORTED : szErrorVal = "FEEDBACK_ERROR_NOT_SUPPORTED" ; break;
		default : szErrorVal = "Unknown Error" ; break;
	}

	return szErrorVal;
}
/**
* @function         CTs_platform_permission_Libfeedback_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_Libfeedback_startup(void)
{
    struct stat stBuff;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
	if (remove(ERR_LOG))
	{
		FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
	}
    }

#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_Libfeedback_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_Libfeedback_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_Libfeedback_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_Libfeedback_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}


//& purpose:Checking tizen.org/privilege/haptic privilege
//& type: auto
/**
* @testcase			CTc_Libfeedback_PrivilegeHaptic_feedback_is_supported_pattern
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario			Play specific type of reactions that are predefined
* @apicovered		feedback_is_supported_pattern
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Libfeedback_PrivilegeHaptic_feedback_is_supported_pattern(void)
{
	START_TEST;
	int nRet = -1;
	bool bStatus;

	nRet = feedback_initialize();
	PRINT_RESULT(FEEDBACK_ERROR_NONE, nRet, "feedback_initialize", FeedbackGetError(nRet));

	
	nRet = feedback_is_supported_pattern(FEEDBACK_TYPE_VIBRATION, FEEDBACK_PATTERN_VIBRATION_ON, &bStatus);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "feedback_is_supported_pattern", FeedbackGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/haptic privilege
//& type: auto
/**
* @testcase			CTc_Libfeedback_PrivilegeHaptic_feedback_play_type
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario			Play specific type of reactions that are predefined
* @apicovered		feedback_play_type
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Libfeedback_PrivilegeHaptic_feedback_play_type(void)
{
	START_TEST;
	int nRet = -1;
	
	nRet = feedback_initialize();
	PRINT_RESULT(FEEDBACK_ERROR_NONE, nRet, "feedback_initialize", FeedbackGetError(nRet));

	//Target API
	nRet = feedback_play_type(FEEDBACK_TYPE_VIBRATION, FEEDBACK_PATTERN_VIBRATION_ON);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "feedback_play_type", FeedbackGetError(nRet));
	
	return 0;
}
