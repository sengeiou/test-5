#include "CTs-platform-permission-common.h"
#include <media/media_streamer.h>
#include <glib.h>
#include <string.h>
#include <Ecore.h>

#define VIDEO_WIDTH 1280
#define VIDEO_HEIGHT 720
#define AVG_BPS 1031
#define MAX_BPS 2063

const char *g_pszFilePath = NULL;
media_format_h vfmt_encoded;
media_streamer_h streamer;


static bool storage_device_cb(int storage_id, storage_type_e type, storage_state_e state, const char* path, void* user_data)
{
	if (type == STORAGE_TYPE_INTERNAL) {
		g_pszFilePath=(char*)calloc(strlen(path)+strlen("/res/test_10sec.mp4")+1, sizeof(char));
		if(g_pszFilePath == NULL)
		{
			FPRINTF("[Line : %d][%s] calloc failure inside storage_device_cb \\n", __LINE__, API_NAMESPACE);
			return true; //ambiguous call but true
		}
		snprintf(g_pszFilePath, strlen(path)+strlen("/res/test_10sec.mp4")+1, "%s/res/test_10sec.mp4.mp4", path);

		return false;
	}
	return true;
}



/**
* @function		MediaStreamerGetError
* @description		Maps error enums to string values
* @parameter		nRet : error code returned
* @return			error string
*/
char* MediaStreamerGetError(int nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
	case MEDIA_STREAMER_ERROR_NONE:						szErrorVal = "MEDIA_STREAMER_ERROR_NONE";					break;
	case MEDIA_STREAMER_ERROR_INVALID_PARAMETER:		szErrorVal = "MEDIA_STREAMER_ERROR_INVALID_PARAMETER";		break;
	case MEDIA_STREAMER_ERROR_INVALID_OPERATION:		szErrorVal = "MEDIA_STREAMER_ERROR_INVALID_OPERATION";		break;
	case MEDIA_STREAMER_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "MEDIA_STREAMER_ERROR_FILE_NO_SPACE_ON_DEVICE";break;
	case MEDIA_STREAMER_ERROR_NOT_SUPPORTED:			szErrorVal = "MEDIA_STREAMER_ERROR_NOT_SUPPORTED";			break;
	case MEDIA_STREAMER_ERROR_PERMISSION_DENIED:		szErrorVal = "MEDIA_STREAMER_ERROR_PERMISSION_DENIED";		break;
	case MEDIA_STREAMER_ERROR_INVALID_STATE:			szErrorVal = "MEDIA_STREAMER_ERROR_INVALID_STATE";			break;
	case MEDIA_STREAMER_ERROR_CONNECTION_FAILED:		szErrorVal = "MEDIA_STREAMER_ERROR_CONNECTION_FAILED";		break;
	case MEDIA_STREAMER_ERROR_RESOURCE_CONFLICT:		szErrorVal = "MEDIA_STREAMER_ERROR_RESOURCE_CONFLICT";		break;
	case MEDIA_STREAMER_ERROR_SEEK_FAILED:				szErrorVal = "MEDIA_STREAMER_ERROR_SEEK_FAILED";			break;
	}
	return szErrorVal;
}
/**
 * @function		CTs_platform_permission_media_streamer_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void CTs_platform_permission_media_streamer_startup(void)
{
	struct stat stBuff;
	int nRetVal =-1;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);

	storage_foreach_device_supported(storage_device_cb,NULL);

	nRetVal = media_streamer_create(&streamer);
	if(nRetVal < 0)
	{
		FPRINTF("[Line : %d][%s] media_streamer_create failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRetVal), nRetVal);
		return;
	}

	nRetVal = media_format_create(&vfmt_encoded);
	if(nRetVal < 0)
	{
		FPRINTF("[Line : %d][%s] media_format_create failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRetVal), nRetVal);
		return;
	}
	nRetVal = media_format_set_video_mime(vfmt_encoded, MEDIA_FORMAT_H263);
	if(nRetVal < 0)
	{
		FPRINTF("[Line : %d][%s] media_format_set_video_mime failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRetVal), nRetVal);
		return;
	}
	media_format_set_video_width(vfmt_encoded, VIDEO_WIDTH);
	media_format_set_video_height(vfmt_encoded, VIDEO_HEIGHT);
	media_format_set_video_avg_bps(vfmt_encoded, AVG_BPS);
	media_format_set_video_max_bps(vfmt_encoded, MAX_BPS);
	return;
}


/**
 * @function		CTs_platform_permission_media_streamer_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void CTs_platform_permission_media_streamer_cleanup(void)
{
	int nRetVal =-1;
	media_format_unref(vfmt_encoded);
	nRetVal = media_streamer_destroy(streamer);
	if(nRetVal < 0)
	{
		FPRINTF("[Line : %d][%s] media_streamer_destroy failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRetVal), nRetVal);
		return;
	}

	if (g_pszFilePath) {
		free(g_pszFilePath);
		g_pszFilePath = NULL;
	}

	return;
}

//& purpose: Checking tizen.org/privilege/internet privileges
/**
* @testcase			CTc_MediaStreamer_PrivilegeMediaStorage_node_create_src
* @since_tizen			3.0
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			media streamer node src creation
* @scenario			media streamer node src create
* @apicovered			media_streamer_node_create_src
* @passcase			if target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA
*/
int CTc_MediaStreamer_PrivilegeMediaStorage_node_create_src(void)
{
	START_TEST;

	media_streamer_node_h hSrc =NULL;
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_src_type_e eSetSrcType[] =
	{
	MEDIA_STREAMER_NODE_SRC_TYPE_HTTP,           /**<  Http src type, Network internet feature is required */
	MEDIA_STREAMER_NODE_SRC_TYPE_RTSP,           /**<  Rtsp src type, Network internet feature is required */
};
	int nEnumSize = sizeof(eSetSrcType) / sizeof(eSetSrcType[0]);
   	int nEnumCounter = 0;
   	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
    	{
	  ret = media_streamer_node_create_src(eSetSrcType[nEnumCounter], &hSrc);
	  if(ret == TIZEN_ERROR_PERMISSION_DENIED)
	  {
		FPRINTF("[Line : %d][%s] media_streamer_node_create_src Pass\\n", __LINE__, API_NAMESPACE);\
		return 0;
	  }
	}

	return 1;
}

//& purpose: Checking tizen.org/privilege/internet privilege
/**
* @testcase			CTc_MediaStreamer_PrivilegeMediaStorage_node_create_sink
* @since_tizen			3.0
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Prepare and unprepare media streamer
* @scenario			create media streamer node sink\n
* @apicovered			media_streamer_node_create_sink
* @passcase			if target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA
*/
int  CTc_MediaStreamer_PrivilegeMediaStorage_node_create_sink(void)
{
	START_TEST;

	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h hSink = NULL;
	media_streamer_node_sink_type_e eSetSinkType[] = {
	MEDIA_STREAMER_NODE_SINK_TYPE_RTSP,   /**<  Rtsp sink type, Network internet feature is required */
	MEDIA_STREAMER_NODE_SINK_TYPE_HTTP,   /**<  Http sink type, Network internet feature is required */
};
	int nEnumSize = sizeof(eSetSinkType) / sizeof(eSetSinkType[0]);
   	int nEnumCounter = 0;
   	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
    	{
	   ret = media_streamer_node_create_sink(eSetSinkType[nEnumCounter], &hSink);
	   if(ret == TIZEN_ERROR_PERMISSION_DENIED)
	   {
		FPRINTF("[Line : %d][%s]media_streamer_node_create_sink Pass\\n", __LINE__, API_NAMESPACE);\
		return 0;
	   }
	}

	return 1;
}

//& purpose: Checking tizen.org/privilege/mediastorage privilege
/**
* @testcase			CTc_MediaStreamer_PrivilegeMediaStorage_node_set_param
* @since_tizen			3.0
* @author			SRID(nibha.sharma)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Set  media streamer node param
* @scenario			media streamer node src create,media_streamer_node_set_param
* @apicovered			media_streamer_node_create_src,media_streamer_node_set_param
* @passcase			if target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA
*/
int CTc_MediaStreamer_PrivilegeMediaStorage_node_set_param(void)
{
	START_TEST;
	media_streamer_node_h hSrc =NULL;

	int ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_FILE, &hSrc);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create_src", MediaStreamerGetError(ret));
	CHECK_HANDLE(hSrc,"media_streamer_node_create_src");

	ret = media_streamer_node_set_param(hSrc,MEDIA_STREAMER_PARAM_URI, g_pszFilePath);
    	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, ret, "media_streamer_node_set_param", MediaStreamerGetError(ret));

	return 0;
}

//& purpose: Checking tizen.org/privilege/mediastorage privilege
/**
* @testcase			CTc_MediaStreamer_PrivilegeMediaStorage_node_set_params
* @since_tizen			3.0
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Set  media streamer node params
* @scenario			media streamer node src create,media_streamer_node_set_params
* @apicovered			media_streamer_node_create_src,media_streamer_node_set_params
* @passcase			if target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA
*/
int CTc_MediaStreamer_PrivilegeMediaStorage_node_set_params(void)
{
	START_TEST;
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_streamer_node_h vid_test = NULL;
	bundle *param_list = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_FILE, &vid_test);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create_src", MediaStreamerGetError(ret));
	CHECK_HANDLE(vid_test,"media_streamer_node_create_src");

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_IS_LIVE_STREAM, "true");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_URI, g_pszFilePath);
	bundle_add_str(params, MEDIA_STREAMER_PARAM_USER_AGENT, "bob");

	ret = media_streamer_node_set_params(vid_test, params);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, ret, "media_streamer_node_set_params", MediaStreamerGetError(ret),bundle_free(params));
	bundle_free(params);
	return 0;
}

