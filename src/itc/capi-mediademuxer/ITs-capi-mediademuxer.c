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
#include "ITs-capi-mediademuxer-common.h"

static GMainLoop *g_pMainLoop;
static bool g_bCallbackResult = false;
int g_bEOScallbackResult = false;
gboolean Timeout_Function(gpointer data);
static char* g_file_path = NULL;
static char *g_uri = NULL;


/**
 * @function 		Timeout_Function
 * @description	 	callback function to terminate g_main loop
 * @parameter		data : user data sent to callback
 * @return 			NA
 */
gboolean Timeout_Function(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

/** @addtogroup itc-mediademuxer
 *  @ingroup itc
 *  @{
 */

//& set: Mediademuxer

/**
 * @function 		mediademuxer_error_callback
 * @description	 	Called when error occurs in media demuxer.
 * @parameter		mediademuxer error: error, user_data: User data sent to callback
 * @return 			NA
 */
void mediademuxer_error_callback(mediademuxer_error_e error, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"mediademuxer_error_callback\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
	FPRINTF("[Line : %d][%s] Outside from callback \"mediademuxer_error_callback\"\\n", __LINE__, API_NAMESPACE);
}

/**
 * @function 		mediademuxer_eos_callback
 * @description		Called when eos occurs in media demuxer.
 * @parameter		int track_index: the track number on which EOS reached, user_data: User data sent to callback
 * @return			NA
 */
void mediademuxer_eos_callback(int track_index, void *user_data)
{

	g_bEOScallbackResult = true;
	printf("Call back received\n");

}


/**
 * @function 		ITs_mediademuxer_startup
 * @description	 	Called before each test, set the service boolean true
 * @parameter		NA
 * @return 			NA
 */
void ITs_mediademuxer_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Mediademuxer_p\\n", __LINE__, API_NAMESPACE);
#endif
	if(g_uri == NULL)
	{
		char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
		if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
		{
			FPRINTF("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
			g_file_path=(char*)malloc(strlen(pszValue)+ strlen( "sample.mp4" ) + 6);
			snprintf(g_file_path, strlen(pszValue) + strlen("/res/sample.mp4") + 1, "%s/res/sample.mp4", pszValue);
		}
		else
		{
			FPRINTF("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
		}
		g_uri = g_file_path;
	}

	g_bMediademuxerCreation = true;
}

/**
 * @function 		ITs_mediademuxer_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_mediademuxer_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Mediademuxer_p\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_file_path)
	{
		free(g_file_path);
		g_file_path = NULL;
		g_uri = NULL;
	}
}

/** @addtogroup itc-mediademuxer-testcases
 *  @brief 		Integration testcases for module mediademuxer
 *  @ingroup 	itc-mediademuxer
 *  @{
 */

/**
 * @testcase 			ITc_mediademuxer_create_destroy_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Create and destroy a media demuxer handle for demuxing.
 * @scenario				Create and destroy a media demuxer handle for demuxing.
 * @apicovered			mediademuxer_create, mediademuxer_destroy
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: API to test mediademuxer_create & mediademuxer_destroy
//& type: auto
int ITc_mediademuxer_create_destroy_p(void)
{
	START_TEST;

	mediademuxer_h demuxer = NULL;

	int nRetVal = mediademuxer_create(&demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_create", MediademuxerGetError(nRetVal));
	CHECK_HANDLE(demuxer, "mediademuxer_create");

	nRetVal = mediademuxer_destroy(demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediademuxer_set_data_source_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Set the source path of input stream.
 * @scenario				Create media demuxer handle for demuxing.\n
 set the source path of input stream.
 * @apicovered			mediademuxer_create, mediademuxer_destroy, mediademuxer_set_data_source
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Set the source path of input stream.
//& type: auto
int ITc_mediademuxer_set_data_source_p(void)
{
	START_TEST;

	mediademuxer_h demuxer = NULL;

	int nRetVal = mediademuxer_create(&demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_create", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_set_eos_cb(demuxer, mediademuxer_eos_callback, demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_set_data_source(demuxer, g_uri);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_data_source", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_unset_eos_cb(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unset_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_destroy(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediademuxer_prepare_unprepare_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Prepare and unprepare the media demuxer for demuxing.
 * @scenario				Create media demuxer handle for demuxing.\n
 prepare and unprepare the media demuxer for demuxing.
 * @apicovered			mediademuxer_create, mediademuxer_destroy, mediademuxer_set_data_source, mediademuxer_prepare, mediademuxer_unprepare
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Prepare the media demuxer for demuxing.
//& type: auto
int ITc_mediademuxer_prepare_unprepare_p(void)
{
	START_TEST;

	mediademuxer_h demuxer = NULL;

	int nRetVal = mediademuxer_create(&demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_create", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_set_eos_cb(demuxer, mediademuxer_eos_callback, demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_set_data_source(demuxer, g_uri);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_data_source", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_prepare(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_prepare", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_unprepare(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unprepare", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_unset_eos_cb(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unset_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_destroy(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediademuxer_get_track_count_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Get the total track count present in the container stream.
 * @scenario				Create media demuxer handle for demuxing.\n
 get the total track count present in the container stream.
 * @apicovered			mediademuxer_create, mediademuxer_destroy, mediademuxer_set_data_source, mediademuxer_prepare, mediademuxer_get_track_count, mediademuxer_unprepare.
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Get the total track count present in the container stream.
//& type: auto
int ITc_mediademuxer_get_track_count_p(void)
{
	START_TEST;

	mediademuxer_h demuxer = NULL;
	int count = -1;

	int nRetVal = mediademuxer_create(&demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_create", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_set_eos_cb(demuxer, mediademuxer_eos_callback, demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_set_data_source(demuxer, g_uri);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_data_source", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_prepare(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_prepare", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_get_track_count(demuxer, &count);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_get_track_count", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	if(count<0)
	{
		FPRINTF("[Line : %d][%s] Invalid count \\n", __LINE__, API_NAMESPACE);
		nRetVal = mediademuxer_destroy(demuxer);
		PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));
		return 1;
	}

	nRetVal = mediademuxer_unprepare(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unprepare", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unset_eos_cb(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unset_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_destroy(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediademuxer_select_unselect_track_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Select and unselect the track to be performed.
 * @scenario				Create media demuxer handle for demuxing.\n
 select and unselect the track to be performed.
 * @apicovered			mediademuxer_create, mediademuxer_destroy, mediademuxer_set_data_source, mediademuxer_prepare, mediademuxer_select_track, mediademuxer_unselect_track ,mediademuxer_unprepare.
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Select and unselect the track to be performed.
//& type: auto
int ITc_mediademuxer_select_unselect_track_p(void)
{
	START_TEST;

	mediademuxer_h demuxer = NULL;

	int nRetVal = mediademuxer_create(&demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_create", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_set_eos_cb(demuxer, mediademuxer_eos_callback, demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_set_data_source(demuxer, g_uri);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_data_source", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_prepare(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_prepare", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_select_track(demuxer, TRACK_INDEX);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_select_track", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_unselect_track(demuxer, TRACK_INDEX);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unselect_track", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_unprepare(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unprepare", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unset_eos_cb(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unset_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_destroy(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediademuxer_start_stop_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Start and stop the media demuxer.
 * @scenario				Create media demuxer handle for demuxing.\n
 start and stop the media demuxer.
 * @apicovered			mediademuxer_create, mediademuxer_destroy, mediademuxer_set_data_source, mediademuxer_prepare, mediademuxer_select_track, mediademuxer_start, mediademuxer_stop, mediademuxer_unselect_track ,mediademuxer_unprepare.
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Start and stop the media demuxer.
//& type: auto
int ITc_mediademuxer_start_stop_p(void)
{
	START_TEST;

	mediademuxer_h demuxer = NULL;

	int nRetVal = mediademuxer_create(&demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_create", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_set_eos_cb(demuxer, mediademuxer_eos_callback, demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_set_data_source(demuxer, g_uri);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_data_source", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_prepare(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_prepare", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_select_track(demuxer, TRACK_INDEX);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_select_track", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_start(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_start", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_stop(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_stop", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_unselect_track(demuxer, TRACK_INDEX);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unselect_track", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unprepare(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unprepare", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unset_eos_cb(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unset_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_destroy(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediademuxer_get_track_info_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Retrieve the track format of the read sample.
 * @scenario				Create media demuxer handle for demuxing.\n
 retrieve the track format of the read sample.
 * @apicovered			mediademuxer_create, mediademuxer_destroy, mediademuxer_set_data_source, mediademuxer_prepare, mediademuxer_select_track, mediademuxer_start, mediademuxer_get_track_info, mediademuxer_stop, mediademuxer_unselect_track ,mediademuxer_unprepare.
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Retrieve the track format of the read sample.
//& type: auto
int ITc_mediademuxer_get_track_info_p(void)
{
	START_TEST;

	mediademuxer_h demuxer = NULL;
	media_format_h format;

	int nRetVal = mediademuxer_create(&demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_create", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_set_eos_cb(demuxer, mediademuxer_eos_callback, demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_set_data_source(demuxer, g_uri);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_data_source", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_prepare(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_prepare", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_select_track(demuxer, TRACK_INDEX);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_select_track", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_start(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_start", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_get_track_info(demuxer, TRACK_INDEX, &format);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_get_track_info", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));
	CHECK_HANDLE(format, "mediademuxer_get_track_info");

	nRetVal = mediademuxer_stop(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_stop", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unselect_track(demuxer, TRACK_INDEX);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unselect_track", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unprepare(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unprepare", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unset_eos_cb(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unset_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_destroy(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediademuxer_read_sample_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Read a frame(sample) of one single track.
 * @scenario				Create media demuxer handle for demuxing.\n
 read a frame(sample) of one single track.
 * @apicovered			mediademuxer_create, mediademuxer_destroy, mediademuxer_set_data_source, mediademuxer_prepare, mediademuxer_get_track_info, mediademuxer_select_track, mediademuxer_start, mediademuxer_read_sample, mediademuxer_stop, mediademuxer_unselect_track ,mediademuxer_unprepare.
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Read a frame(sample) of one single track.
//& type: auto
int ITc_mediademuxer_read_sample_p(void)
{
	START_TEST;

	mediademuxer_h demuxer = NULL;
	media_packet_h outbuf;
	media_format_h audfmt;

	int nRetVal = mediademuxer_create(&demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_create", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_set_eos_cb(demuxer, mediademuxer_eos_callback, demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_set_data_source(demuxer, g_uri);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_data_source", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_prepare(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_prepare", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_get_track_info(demuxer, TRACK_INDEX, &audfmt);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_get_track_info", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_select_track(demuxer, TRACK_INDEX);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_select_track", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_start(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_start", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_read_sample(demuxer, TRACK_INDEX, &outbuf);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_read_sample", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));
	CHECK_HANDLE(outbuf, "mediademuxer_read_sample");

	nRetVal = mediademuxer_stop(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_stop", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unselect_track(demuxer, TRACK_INDEX);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unselect_track", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unprepare(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unprepare", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unset_eos_cb(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unset_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_destroy(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediademuxer_seek_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Seek to a particular instance of time (in micro seconds).
 * @scenario				Create media demuxer handle for demuxing.\n
 seek to a particular instance of time (in micro seconds).
 * @apicovered			mediademuxer_create, mediademuxer_destroy, mediademuxer_set_data_source, mediademuxer_prepare, mediademuxer_select_track, mediademuxer_start, mediademuxer_seek, mediademuxer_stop, mediademuxer_unselect_track ,mediademuxer_unprepare.
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Seek to a particular instance of time (in micro seconds).
//& type: auto
int ITc_mediademuxer_seek_p(void)
{
	START_TEST;

	mediademuxer_h demuxer = NULL;

	int nRetVal = mediademuxer_create(&demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_create", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_set_eos_cb(demuxer, mediademuxer_eos_callback, demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_set_data_source(demuxer, g_uri);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_data_source", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_prepare(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_prepare", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_select_track(demuxer, TRACK_INDEX);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_select_track", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_start(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_start", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_seek(demuxer, POSITION);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_seek", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_stop(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_stop", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unselect_track(demuxer, TRACK_INDEX);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unselect_track", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unprepare(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unprepare", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_unset_eos_cb(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unset_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_destroy(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediademuxer_get_state_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Get media demuxer state.
 * @scenario				Create and destroy a media demuxer handle for demuxing.\n
 get media demuxer state.
 * @apicovered			mediademuxer_create, mediademuxer_get_state, mediademuxer_destroy
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Get media demuxer state.
//& type: auto
int ITc_mediademuxer_get_state_p(void)
{
	START_TEST;

	mediademuxer_h demuxer = NULL;
	mediademuxer_state state = -1;

	int nRetVal = mediademuxer_create(&demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_create", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_set_eos_cb(demuxer, mediademuxer_eos_callback, demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_get_state(demuxer, &state);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_get_state", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	if( state < MEDIADEMUXER_STATE_NONE || state > MEDIADEMUXER_STATE_DEMUXING)
	{
		nRetVal = mediademuxer_destroy(demuxer);
		PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));
		return 1;
	}

	nRetVal = mediademuxer_unset_eos_cb(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unset_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_destroy(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediademuxer_set_unset_error_cb_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Register and unregister an error callback function to be invoked when an error occurs.
 * @scenario				Create and destroy a media demuxer handle for demuxing.\n
 register and unregister an error callback function to be invoked when an error occurs.
 * @apicovered			mediademuxer_create, mediademuxer_get_state, mediademuxer_destroy
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Register and unregister an error callback function to be invoked when an error occurs.
//& type: auto
int ITc_mediademuxer_set_unset_error_cb_p(void)
{
	START_TEST;

	mediademuxer_h demuxer = NULL;

	int nRetVal = mediademuxer_create(&demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_create", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_set_error_cb(demuxer, mediademuxer_error_callback, NULL);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_error_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_unset_error_cb(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unset_error_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_destroy(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediademuxer_set_unset_eos_cb_p
 * @since_tizen			3.0
 * @author				SRID(satheesan e n)
 * @reviewer			HQ(Joungkook Seo)
 * @type 				auto
 * @description			Register and unregister an eos callback function to be invoked when an end of stream occurs.
 * @scenario				Create and destroy a media demuxer handle for demuxing.\n
 register and unregister an eos callback function to be invoked when an eos occurs.
 * @apicovered			mediademuxer_create, mediademuxer_destroy, mediademuxer_set_data_source, mediademuxer_set_eos_cb, mediademuxer_prepare, mediademuxer_select_track, mediademuxer_start, mediademuxer_read_sample, mediademuxer_stop, mediademuxer_unselect_track ,mediademuxer_unprepare, mediademuxer_unset_eos_cb
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
int ITc_mediademuxer_set_unset_eos_cb_p(void)
{
	START_TEST;

	mediademuxer_h demuxer = NULL;
	media_packet_h outbuf;
	media_format_h audfmt=NULL;

	int count;
	uint64_t buf_size = 0;
	void *data = NULL;

	int nRetVal = mediademuxer_create(&demuxer);
	PRINT_RESULT(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_create", MediademuxerGetError(nRetVal));

	nRetVal = mediademuxer_set_eos_cb(demuxer, mediademuxer_eos_callback, demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_set_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_unset_eos_cb(demuxer);
	PRINT_RESULT_CLEANUP(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_unset_eos_cb", MediademuxerGetError(nRetVal), mediademuxer_destroy(demuxer));

	nRetVal = mediademuxer_destroy(demuxer);
	PRINT_RESULT_NORETURN(MEDIADEMUXER_ERROR_NONE, nRetVal, "mediademuxer_destroy", MediademuxerGetError(nRetVal));

	return 0;
}

/** @} */
/** @} */
