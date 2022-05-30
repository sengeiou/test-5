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
#include "ITs-radio-common.h"

/** @addtogroup itc-radio
*  @ingroup itc
*  @{
*/

bool g_bCallbackHit;
bool g_bCallbackScanComplete;
bool g_bRadioNotSupported = false;
bool g_bMismatch = false;
static GMainLoop *g_pMainLoop = NULL;
radio_h g_pstRadio;
int g_nRadioCreated;

//& set: Radio

void ITs_radio_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Radio_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bRadioNotSupported = false;
	g_bMismatch = false;
	g_nRadioCreated = false;

	if ( !TCTCheckSystemInfoFeatureSupported(RADIO_FEATURE, API_NAMESPACE) )
	{
		if ( radio_create(&g_pstRadio) != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bMismatch = true;
		}
		else
		{
			g_bRadioNotSupported = true;
		}
		return;
	}

	int nRetVal = radio_create(&g_pstRadio);
	if ( nRetVal != RADIO_ERROR_NONE )
	{
		g_nRadioCreated = false;
		FPRINTF("[Line : %d][%s] radio_create failed in startup, error returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetError(nRetVal));
		return;
	}
	else
	{
		FPRINTF("[Line : %d][%s] radio_create successful in startup\\n", __LINE__, API_NAMESPACE);
		radio_state_e eState;
		nRetVal = radio_get_state(g_pstRadio, &eState);
		if ( nRetVal != RADIO_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] radio_get_state failed in startup, error returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetError(nRetVal));
			g_nRadioCreated = false;
			return;
		}
		else if ( eState != RADIO_STATE_READY )
		{
			FPRINTF("[Line : %d][%s] radio_get_state return wrong state in startup, state returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetState(eState));
			g_nRadioCreated = false;
			return;
		}
		else
		{
			g_nRadioCreated = true;
		}
	}
}

void ITs_radio_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Radio_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_nRadioCreated )
	{
		int nRetVal = radio_destroy(g_pstRadio);
		if ( nRetVal != RADIO_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] radio_destroy failed in cleanup, error returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetError(nRetVal));
		}
	}
}

/**
* @function 		RadioTimeout
* @description	 	Called if some callback is not invoked for a particular serial Timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean RadioTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	FPRINTF("[Line : %d][%s] Callback RadioTimeout\\n", __LINE__, API_NAMESPACE);
	return false;
}

/**
* @function 		RadioSeekCompletedCB
* @description	 	Called when power state changes.
* @parameter		frequency of next station , user_data data that user passes for calling callback
* @return 			NA
*/
static void RadioSeekCompletedCB(int frequency, void* user_data)
{
	FPRINTF("[Line : %d][%s] callback function RadioSeekCompletedCB called successfully\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		RadioScanStoppedCB
* @description	 	Called when radio scan is stopped completed.
* @parameter		user_data data that user passes for calling callback
* @return 			NA
*/
static void RadioScanStoppedCB(void* user_data)
{
	FPRINTF("[Line : %d][%s] callback function RadioScanStoppedCB called successfully\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		RadioScanUpdatedCB
* @description	 	Called when scan updated.
* @parameter		frequency of next station, user_data data that user passes for calling callback
* @return 			NA
*/
static void RadioScanUpdatedCB(int frequency, void* user_data)
{
	FPRINTF("[Line : %d][%s] callback function RadioScanUpdatedCB called successfully\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;
}


/**
* @function 		RadioScanUpdatedCallBack
* @description	 	Called when scan updated.
* @parameter		frequency of next station, user_data data that user passes for calling callback
* @return 			NA
*/
static void RadioScanUpdatedCallBack(int frequency, void* user_data)
{
	FPRINTF("[Line : %d][%s] callback function RadioScanUpdatedCallBack called successfully\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		RadioScanCompletedCB
* @description	 	Called when radio scan is  completed.
* @parameter		user_data data that user passes for calling callback
* @return 			NA
*/
static void RadioScanCompletedCB(void* user_data)
{
	FPRINTF("[Line : %d][%s] callback function RadioScanCompletedCB called successfully\\n", __LINE__, API_NAMESPACE);
	g_bCallbackScanComplete = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		RadioInterruptedCB
* @description	 	Called when radio radio is interrupted.
* @parameter		radio interrupted code, user_data data that user passes for calling callback
* @return 			NA
*/
static void RadioInterruptedCB(radio_interrupted_code_e code, void* user_data)
{
	FPRINTF("[Line : %d][%s] callback function RadioInterruptedCB called successfully\\n", __LINE__, API_NAMESPACE);
}

/** @addtogroup itc-radio-testcases
*  @brief 		Integration testcases for module radio
*  @ingroup 	itc-radio
*  @{
*/

//& purpose: radio_create_destroy TC.
//& type: auto
/**
* @testcase   			ITc_radio_create_destroy_p
* @since_tizen			2.3
* @author             	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates and destroy a radio handle
* @scenario				Create a radio handle\n
*						Destroy the radio handle and release all resource
* @apicovered			radio_create, radio_destroy
* @passcse				When radio_create, radio_destroy are successful
* @failcase				If target API radio_create or radio_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_radio_create_destroy_p(void)
{
	START_TEST;

	radio_state_e eState;
	int nRetVal = radio_destroy(g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_destroy", RadioGetError(nRetVal));

	g_nRadioCreated = false;
	nRetVal = radio_create(&g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_create", RadioGetError(nRetVal));

	nRetVal = radio_get_state(g_pstRadio, &eState);
	PRINT_RESULT_CLEANUP(RADIO_ERROR_NONE, nRetVal, "radio_get_state", RadioGetError(nRetVal),radio_destroy(g_pstRadio));
	if ( eState != RADIO_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] radio_get_state returned invalid state , state returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetState(eState));
		radio_destroy(g_pstRadio);
		return 1;
	}

	nRetVal = radio_destroy(g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_destroy", RadioGetError(nRetVal));

	return 0;
}

//& purpose: radio_start_stop TC.
//& type: auto
/**
* @testcase   			ITc_radio_start_stop_p
* @since_tizen			2.3
* @author             	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			starts and stops a radio handle
* @scenario				Creates a radio handle and start the radio\n
*                          Stop the radio
* @apicovered			radio_start, radio_stop
* @passcse				When radio_start, radio_stop, radio_create and radio_destroy are successful
* @failcase				If target API radio_start, radio_stop, radio_create or radio_destroy fails
* @precondition			Radio state must be RADIO_STATE_READY by radio create for start\n
*                          The radio state must be RADIO_STATE_PLAYING by radio_start for stop
* @postcondition		The radio state will be RADIO_STATE_PLAYING after radio_start\n
*						    The radio state will be RADIO_STATE_READY after radio stop
*/
int ITc_radio_start_stop_p(void)
{
	START_TEST;
	radio_state_e eState;

	int nRetVal = radio_start(g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_start", RadioGetError(nRetVal));

	nRetVal = radio_get_state(g_pstRadio, &eState);
	PRINT_RESULT_CLEANUP(RADIO_ERROR_NONE, nRetVal, "radio_get_state", RadioGetError(nRetVal),radio_stop(g_pstRadio));
	if ( eState != RADIO_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] radio_get_state return invalid state , state returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetState(eState));
		radio_stop(g_pstRadio);
		return 1;
	}

	nRetVal = radio_stop(g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_stop", RadioGetError(nRetVal));

	return 0;
}

//& purpose:  radio_set_get_frequency TC.
//& type: auto
/**
* @testcase   			ITc_radio_set_get_frequency_p
* @since_tizen			2.3
* @author             	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			set and get radio frequency
* @scenario				Set radio frequency\n
*						Get radio frequency
* @apicovered			radio_set_frequency, radio_get_frequency
* @passcse				When radio_set_frequency, radio_get_frequency are successful
* @failcase				If target API radio_set_frequency or radio_get_frequency fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_radio_set_get_frequency_p(void)
{
	START_TEST;
	int nSetFrequency = 93100;
	int nGetFrequency = -1;

	int nRetVal = radio_set_frequency(g_pstRadio,nSetFrequency);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_set_frequency", RadioGetError(nRetVal));

	nRetVal = radio_get_frequency(g_pstRadio, &nGetFrequency);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_get_frequency", RadioGetError(nRetVal));

	if ( nSetFrequency != nGetFrequency )
	{
		FPRINTF("[Line : %d][%s] radio_get_frequency failed, error returned = set get values mismatched, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, nSetFrequency, nGetFrequency);
		return 1;
	}
	return 0;
}

//& purpose: radio_set_mute_muted TC.
//& type: auto
/**
* @testcase   			ITc_radio_set_mute_muted_p
* @since_tizen			2.3
* @author             	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			mute the radio and check whether it is muted or not
* @scenario				Mute radio\n
*						Check it is muted or not
* @apicovered			radio_set_mute, radio_is_muted
* @passcse				When radio_set_mute, radio_muted are successful
* @failcase				If target API radio_set_mute or radio_is_muted fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_radio_set_mute_muted_p(void)
{
	START_TEST;
	radio_state_e eState;
	bool bMute = false;
	bool bMuted = true;

	int nRetVal = radio_start(g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_start", RadioGetError(nRetVal));

	nRetVal = radio_get_state(g_pstRadio, &eState);
	PRINT_RESULT_CLEANUP(RADIO_ERROR_NONE, nRetVal, "radio_get_state", RadioGetError(nRetVal),radio_stop(g_pstRadio));
	if ( eState != RADIO_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] radio_get_state return wrong state in precondition, state returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetState(eState));
		radio_stop(g_pstRadio);
		return 1;
	}

	nRetVal = radio_set_mute(g_pstRadio, bMute);
	PRINT_RESULT_CLEANUP(RADIO_ERROR_NONE, nRetVal, "radio_set_mute", RadioGetError(nRetVal), radio_stop(g_pstRadio));

	nRetVal = radio_is_muted(g_pstRadio, &bMuted);
	PRINT_RESULT_CLEANUP(RADIO_ERROR_NONE, nRetVal, "radio_is_muted", RadioGetError(nRetVal), radio_stop(g_pstRadio));

	if ( bMuted != bMute )
	{
		FPRINTF("[Line : %d][%s] radio_is_muted failed , error returned = value mismatched\\n", __LINE__, API_NAMESPACE);
		radio_stop(g_pstRadio);
		return 1;
	}

	nRetVal = radio_stop(g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_stop", RadioGetError(nRetVal));

	nRetVal = radio_get_state(g_pstRadio, &eState);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_get_state", RadioGetError(nRetVal));
	if ( eState != RADIO_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] radio_get_state return wrong state, state returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetState(eState));
		return 1;
	}
	return 0;
}

//& purpose: radio_get_state TC.
//& type: auto
/**
* @testcase   			ITc_radio_get_state_p
* @since_tizen			2.3
* @author             	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			gets the radio state
* @scenario				Creates a radio handle\n
*						Gets the radio state
* @apicovered			radio_get_state
* @passcse				When radio_get_state if successful
* @failcase				If target API radio_get_state fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_radio_get_state_p(void)
{
	START_TEST;
	radio_state_e eState;

	int nRetVal = radio_start(g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_start", RadioGetError(nRetVal));

	nRetVal = radio_get_state(g_pstRadio, &eState);
	PRINT_RESULT_CLEANUP(RADIO_ERROR_NONE, nRetVal, "radio_get_state", RadioGetError(nRetVal),radio_stop(g_pstRadio));
	if ( eState != RADIO_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] radio_get_state return wrong state, State returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetState(eState));
		radio_stop(g_pstRadio);
		return 1;
	}

	nRetVal = radio_stop(g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_stop", RadioGetError(nRetVal));

	return 0;
}

//& purpose: radio_get_signal_strength TC.
//& type: auto
/**
* @testcase   			ITc_radio_get_signal_strength_p
* @since_tizen			2.3
* @author             	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			gets the radio state
* @scenario				Creates a radio handle\n
*						Gets the signal strength
* @apicovered			radio_get_signal_strength
* @passcse				When radio_create, radio_get_signal_strength are successful
* @failcase				If target API radio_create or radio_get_signal_strength fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_radio_get_signal_strength_p(void)
{
	START_TEST;
	int nStrength = 0;

	int nRetVal = radio_get_signal_strength(g_pstRadio, &nStrength);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_get_signal_strength", RadioGetError(nRetVal));

	if ( (nStrength <= -128) || (nStrength >= 128) )
	{
		FPRINTF("[Line : %d][%s] radio_get_signal_strength failed , received singnal strength = %d which is out of range. \\n", __LINE__, API_NAMESPACE, nStrength);
		return 1;
	}

	return 0;
}

//& purpose: radio_seek_up_down TC.
//& type: auto
/**
* @testcase   			ITc_radio_seek_up_down_p
* @since_tizen			2.3
* @author             	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			starts and stops a radio handle
* @scenario				Creates a radio handle and start the radio and seeks up or down
* @apicovered			radio_start, radio_stop, radio_seek_up, radio_seek_down
* @passcse				When radio_start, radio_stop, radio_seek_up and radio_seek_down are successful
* @failcase				If target API radio_start, radio_stop, radio_seek_up or radio_seek_down fails
* @precondition			The radio state must be RADIO_STATE_PLAYING by radio_start for radio_seek_up
* @postcondition		It invokes RadioSeekCompletedCB when seek completes
*/
int ITc_radio_seek_up_down_p(void)
{
	START_TEST;

	int nTimeoutId = -1;
	radio_state_e eState;

	int nRetVal = radio_start(g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_start", RadioGetError(nRetVal));

	nRetVal = radio_get_state(g_pstRadio, &eState);
	PRINT_RESULT_CLEANUP(RADIO_ERROR_NONE, nRetVal, "radio_get_state", RadioGetError(nRetVal),radio_stop(g_pstRadio));
	if ( eState != RADIO_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] radio_get_state return wrong state, State returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetState(eState));
		radio_stop(g_pstRadio);
		return 1;
	}

	g_bCallbackHit = false;
	nRetVal = radio_seek_up(g_pstRadio, RadioSeekCompletedCB, NULL);
	PRINT_RESULT_CLEANUP(RADIO_ERROR_NONE, nRetVal, "radio_seek_up", RadioGetError(nRetVal), radio_stop(g_pstRadio));

	RUN_POLLING_LOOP;
	CHECK_VALUE_INT(g_bCallbackHit, "radio_seek_up");
	usleep(2000);

	nRetVal = radio_get_state(g_pstRadio, &eState);
	PRINT_RESULT_CLEANUP(RADIO_ERROR_NONE, nRetVal, "radio_get_state", RadioGetError(nRetVal),radio_stop(g_pstRadio));
	if ( eState != RADIO_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] radio_get_state return wrong state , State returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetState(eState));
		radio_stop(g_pstRadio);
		return 1;
	}

	g_bCallbackHit = false;
	nRetVal = radio_seek_down(g_pstRadio, RadioSeekCompletedCB, NULL);
	PRINT_RESULT_CLEANUP(RADIO_ERROR_NONE, nRetVal, "radio_seek_down", RadioGetError(nRetVal), radio_stop(g_pstRadio));

	RUN_POLLING_LOOP;
	CHECK_VALUE_INT(g_bCallbackHit, "radio_seek_down");
	usleep(2000);

	nRetVal = radio_get_state(g_pstRadio, &eState);
	PRINT_RESULT_CLEANUP(RADIO_ERROR_NONE, nRetVal, "radio_get_state", RadioGetError(nRetVal),radio_stop(g_pstRadio));
	if ( eState != RADIO_STATE_PLAYING )
	{
		FPRINTF("[Line : %d][%s] radio_get_state return wrong state, State returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetState(eState));
		radio_stop(g_pstRadio);
		return 1;
	}

	nRetVal = radio_stop(g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_stop", RadioGetError(nRetVal));

	nRetVal = radio_get_state(g_pstRadio, &eState);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_get_state", RadioGetError(nRetVal));
	if ( eState != RADIO_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] radio_get_state return wrong state, state returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetState(eState));
		return 1;
	}
	return 0;
}

//& purpose: radio_scan_start_stop TC.
//& type: auto
/**
* @testcase   			ITc_radio_scan_start_stop_p
* @since_tizen			2.3
* @author             	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			starts scanning radio signal asynchronously
* @scenario				Creates a radio handle and start scanning the radio\n
*						Stop scanning
* @apicovered			radio_scan_start, radio_scan_stop
* @passcse				When radio_scan_start and radio_scan_stop are successful
* @failcase				If target API radio_scan_start or radio_scan_stop fails
* @precondition			The radio state must be RADIO_STATE_READY by radio_create for radio_scan_start\n
*						Radio state must be radio state scanning for radio_scan_stop.
* @postcondition		Radio_scan_start radio state will be RADIO_STATE_SCANNING during scanning\n
*						Radio_scan_stop radio state will be RADIO_STATE_READY
*/
int ITc_radio_scan_start_stop_p(void)
{
	START_TEST;

	radio_state_e eState;
	int nTimeoutId = -1;

	g_bCallbackHit = false;
	int nRetVal = radio_scan_start(g_pstRadio, RadioScanUpdatedCallBack, NULL);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_scan_start", RadioGetError(nRetVal));

	RUN_POLLING_LOOP;
	CHECK_VALUE_INT(g_bCallbackHit, "radio_scan_start");

	nRetVal = radio_get_state(g_pstRadio, &eState);
	PRINT_RESULT_CLEANUP(RADIO_ERROR_NONE, nRetVal, "radio_get_state", RadioGetError(nRetVal),radio_scan_stop(g_pstRadio, RadioScanStoppedCB, NULL));
	if ( eState != RADIO_STATE_SCANNING )
	{
		FPRINTF("[Line : %d][%s] radio_get_state return wrong state, State returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetState(eState));
		radio_scan_stop(g_pstRadio, RadioScanStoppedCB, NULL);
		return 1;
	}

	g_bCallbackHit = false;
	nRetVal = radio_scan_stop(g_pstRadio, RadioScanStoppedCB, NULL);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_scan_stop", RadioGetError(nRetVal));

	RUN_POLLING_LOOP;
	CHECK_VALUE_INT(g_bCallbackHit, "radio_scan_stop");
	usleep(2000);

	nRetVal = radio_get_state(g_pstRadio, &eState);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_get_state", RadioGetError(nRetVal));
	if ( eState != RADIO_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] radio_get_state return wrong state, State returned = %s\\n", __LINE__, API_NAMESPACE, RadioGetState(eState));
		return 1;
	}

	return 0;
}

//& purpose: radio_set_unset_scan_completed_cb TC.
//& type: auto
/**
* @testcase   			ITc_radio_set_unset_scan_completed_cb_p
* @since_tizen			2.3
* @author             	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers a callback function to be invoked when the scan finishes
* @scenario				Registers a callback function for scan\n
*						Unregister the callback function
* @apicovered			radio_scan_start,  radio_set_scan_completed_cb, radio_unset_scan_completed_cb
* @passcse				When radio_scan_start, radio_set_scan_completed_cb, radio_unset_scan_completed_cb are successful
* @failcase				If target API radio_scan_start, radio_set_scan_completed_cb or radio_unset_scan_completed_cb fails
* @precondition			NA
* @postcondition		Radio_scan_completed_cb will be invoked
*/
int ITc_radio_set_unset_scan_completed_cb_p(void)
{
	START_TEST;

	int nTimeoutId = -1;
	radio_state_e eState;
	g_bCallbackScanComplete = false;

	int nRetVal = radio_set_scan_completed_cb(g_pstRadio, RadioScanCompletedCB, NULL);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_set_scan_completed_cb", RadioGetError(nRetVal));

	nRetVal = radio_scan_start(g_pstRadio, RadioScanUpdatedCB, NULL);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_scan_start", RadioGetError(nRetVal));

	RUN_POLLING_LOOP;
	CHECK_VALUE_INT(g_bCallbackScanComplete, "radio_set_scan_completed_cb");
	usleep(2000);

	nRetVal = radio_get_state(g_pstRadio, &eState);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_get_state", RadioGetError(nRetVal));
	if ( eState != RADIO_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] Unable to get READY state in radio\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bCallbackScanComplete = false;
	nRetVal = radio_unset_scan_completed_cb(g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_unset_scan_completed_cb", RadioGetError(nRetVal));

	nRetVal = radio_scan_start(g_pstRadio, RadioScanUpdatedCB, NULL);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_scan_start", RadioGetError(nRetVal));

	RUN_POLLING_LOOP;
	CHECK_VALUE_INT(!g_bCallbackScanComplete, "radio_unset_scan_completed_cb");

	return 0;
}

//& purpose: radio_set_unset_interrupted_cb TC.
//& type : auto
/**
* @testcase   			ITc_radio_set_unset_interrupted_cb_p
* @since_tizen			2.3
* @author             	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers a callback function to be invoked when radio is interrupted
* @scenario				Registers a callback function for interrupt.\n
*						Unregister the callback function
* @apicovered			radio_set_interrupted_cb, radio_unset_interrupted_cb
* @passcase				When radio_set_interrupted_cb, radio_unset_interrupted_cb are successful
* @failcase				If target API radio_set_interrupted_cb or radio_unset_interrupted_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_radio_set_unset_interrupted_cb_p(void)
{
	START_TEST;
	int nTimeoutId = -1;

	int nRetVal = radio_set_interrupted_cb(g_pstRadio, RadioInterruptedCB, NULL);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_set_interrupted_cb", RadioGetError(nRetVal));

	nRetVal = radio_unset_interrupted_cb(g_pstRadio);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_unset_interrupted_cb", RadioGetError(nRetVal));

	return 0;
}

//& purpose: Gets the min, max frequency of the region
//& type: auto
/**
* @testcase   			ITc_radio_get_frequency_range_p
* @since_tizen			2.4
* @author             	SRID(ajay.kr1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the min, max frequency of the region
* @scenario				Get the minimum frequency of the region\n
*						Get the maximum frequency of the region
* @apicovered			radio_get_frequency_range
* @passcse				When radio_get_frequency_range is successful
* @failcase				If radio_get_frequency_range or any precondition fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_radio_get_frequency_range_p(void)
{
	START_TEST;
	int nMinFrequency = -1, nMaxFrequency = -1;

	int nRetVal = radio_get_frequency_range(g_pstRadio, &nMinFrequency, &nMaxFrequency);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_get_frequency_range", RadioGetError(nRetVal));
	if((nMinFrequency < 0) || (nMaxFrequency < 0) || (nMaxFrequency < nMinFrequency))
	{
		FPRINTF("[Line : %d][%s] radio_get_frequency_range failed because Frequency Range Not Correct\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets channel spacing
//& type: auto
/**
* @testcase   			ITc_radio_get_channel_spacing_p
* @since_tizen			2.4
* @author             	SRID(ajay.kr1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets channel spacing
* @scenario				Gets channel spacing
* @apicovered			radio_get_channel_spacing
* @passcse				When radio_get_channel_spacing is successful
* @failcase				If radio_get_channel_spacing or any precondition fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_radio_get_channel_spacing_p(void)
{
	START_TEST;
	int nChannelSpacing = -1;

	int nRetVal = radio_get_channel_spacing(g_pstRadio, &nChannelSpacing);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_get_channel_spacing", RadioGetError(nRetVal));
	if(nChannelSpacing < 0)
	{
		FPRINTF("[Line : %d][%s] radio_get_channel_spacing failed because channel spacing Not Correct\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose:  radio_set_get_volume TC.
//& type: auto
/**
* @testcase   			ITc_radio_set_get_volume_p
* @since_tizen			3.0
* @author             	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			set and get radio volume
* @scenario				Set radio volume\n
*						Get radio volume
* @apicovered			radio_set_volume, radio_get_volume
* @passcse				When radio_set_volume, radio_get_volume are successful
* @failcase				If target API radio_set_volume or radio_get_volume fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_radio_set_get_volume_p(void)
{
	START_TEST;
	float nSetVolume = 0.6;
	float nGetVolume = -1;

	int nRetVal = radio_set_volume(g_pstRadio,nSetVolume);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_set_volume", RadioGetError(nRetVal));

	nRetVal = radio_get_volume(g_pstRadio, &nGetVolume);
	PRINT_RESULT(RADIO_ERROR_NONE, nRetVal, "radio_get_volume", RadioGetError(nRetVal));

	if ( nSetVolume != nGetVolume )
	{
		FPRINTF("[Line : %d][%s] radio_get_volume failed, error returned = set get values mismatched, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, nSetVolume, nGetVolume);
		return 1;
	}
	return 0;
}

/** @} */
/** @} */