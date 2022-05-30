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
#include "ITs-capi-media-tool-common.h"

/** @addtogroup itc-capi-media-tool
*  @ingroup itc
*  @{
*/
/**
* @function 		MediaToolGetDataPath
* @description	 	Returns the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool MediaToolGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line: %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line: %d][%s] Unable to get application data path; app_get_data_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, strlen(pAppDataPath)+1);

	FPRINTF("[Line: %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}
/**
* @function 		MediaToolCallbackTimeout
* @description	 	callback function to terminate g_main loop
* @parameter		data : user data sent to callback
* @return 			NA
*/
gboolean MediaToolCallbackTimeout(gpointer data)
{
	GMainLoop* pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	return false;
}
/**
* @function 		MediaToolAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool MediaToolAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( NULL == pInputPath || NULL == pFinalPath )
	{
		FPRINTF("[Line: %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == MediaToolGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, strlen(pFinalPath)+1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF("[Line: %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);
	return true;
}
/**
* @function 		MediaPacketGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaPacketGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{		
	case MEDIA_PACKET_ERROR_NONE:						szErrorVal = "MEDIA_PACKET_ERROR_NONE";							break;
	case MEDIA_PACKET_ERROR_INVALID_PARAMETER:			szErrorVal = "MEDIA_PACKET_ERROR_INVALID_PARAMETER";			break;
	case MEDIA_PACKET_ERROR_OUT_OF_MEMORY:				szErrorVal = "MEDIA_PACKET_ERROR_OUT_OF_MEMORY";				break;
	case MEDIA_PACKET_ERROR_INVALID_OPERATION:			szErrorVal = "MEDIA_PACKET_ERROR_INVALID_OPERATION";			break;
	case MEDIA_PACKET_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "MEDIA_PACKET_ERROR_FILE_NO_SPACE_ON_DEVICE";		break;
	case MEDIA_PACKET_ERROR_NO_AVAILABLE_PACKET:		szErrorVal = "MEDIA_PACKET_ERROR_NO_AVAILABLE_PACKET";			break;
	default:											szErrorVal = "Unknown Error";									break;
	}
	return szErrorVal;
}

/**
* @function 		MediaFormatGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaFormatGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{		
	case MEDIA_FORMAT_ERROR_NONE:						szErrorVal = "MEDIA_FORMAT_ERROR_NONE";							break;
	case MEDIA_FORMAT_ERROR_OUT_OF_MEMORY:				szErrorVal = "MEDIA_FORMAT_ERROR_OUT_OF_MEMORY";				break;
	case MEDIA_FORMAT_ERROR_INVALID_PARAMETER:			szErrorVal = "MEDIA_FORMAT_ERROR_INVALID_PARAMETER";			break;
	case MEDIA_FORMAT_ERROR_INVALID_OPERATION:			szErrorVal = "MEDIA_FORMAT_ERROR_INVALID_OPERATION";			break;
	case MEDIA_FORMAT_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "MEDIA_FORMAT_ERROR_FILE_NO_SPACE_ON_DEVICE";		break;
	default:											szErrorVal = "Unknown Error";									break;
	}
	return szErrorVal;
}

/**
* @function 		MediaBufferFlagsGetEnum
* @description	 	Maps Flags enums to string values
* @parameter		nEnumVal
* @return 			flag enum string
*/
char* MediaBufferFlagsGetEnum(media_buffer_flags_e nEnumVal)
{
	char *szEnumVal = NULL;
	
	switch ( nEnumVal )
	{
		case MEDIA_PACKET_CODEC_CONFIG:		szEnumVal = "MEDIA_PACKET_CODEC_CONFIG";		break;
		case MEDIA_PACKET_END_OF_STREAM:	szEnumVal = "MEDIA_PACKET_END_OF_STREAM";		break;
		case MEDIA_PACKET_SYNC_FRAME:		szEnumVal = "MEDIA_PACKET_SYNC_FRAME";			break;
	}
	return szEnumVal;
}

/**
* @function 		MediaFormatMimeTypeGetEnum
* @description	 	Maps Flags enums to string values
* @parameter		nEnumVal
* @return 			MimeType enum string
*/
char* MediaFormatMimeTypeGetEnum(media_format_mimetype_e nEnumVal)
{
	char *szGetEnumVal = NULL;
	
	switch ( nEnumVal)
	{
		case MEDIA_FORMAT_CONTAINER_MP4:		szGetEnumVal = "MEDIA_FORMAT_CONTAINER_MP4";		break;
		case MEDIA_FORMAT_CONTAINER_AVI:		szGetEnumVal = "MEDIA_FORMAT_CONTAINER_AVI";		break;
		case MEDIA_FORMAT_CONTAINER_MPEG2TS:	szGetEnumVal = "MEDIA_FORMAT_CONTAINER_MPEG2TS";	break;
		case MEDIA_FORMAT_CONTAINER_MPEG2PS:	szGetEnumVal = "MEDIA_FORMAT_CONTAINER_MPEG2PS";	break;
		case MEDIA_FORMAT_CONTAINER_MATROSKA:	szGetEnumVal = "MEDIA_FORMAT_CONTAINER_MATROSKA";	break;
		case MEDIA_FORMAT_CONTAINER_WEBM:		szGetEnumVal = "MEDIA_FORMAT_CONTAINER_WEBM";		break;
		case MEDIA_FORMAT_CONTAINER_3GP:		szGetEnumVal = "MEDIA_FORMAT_CONTAINER_3GP";		break;
		case MEDIA_FORMAT_CONTAINER_WAV:		szGetEnumVal = "MEDIA_FORMAT_CONTAINER_WAV";		break;
		case MEDIA_FORMAT_CONTAINER_OGG:		szGetEnumVal = "MEDIA_FORMAT_CONTAINER_OGG";		break;
		case MEDIA_FORMAT_CONTAINER_AAC_ADTS:	szGetEnumVal = "MEDIA_FORMAT_CONTAINER_AAC_ADTS";	break;
		case MEDIA_FORMAT_TEXT_MP4: 			szGetEnumVal = "MEDIA_FORMAT_TEXT_MP4";				break;
		case MEDIA_FORMAT_TEXT_3GP:				szGetEnumVal = "MEDIA_FORMAT_TEXT_3GP";				break;
	}
	return szGetEnumVal;
}

/**
* @function 		MediaFormatTextTypeGetEnum
* @description	 	Maps Flags enums to string values
* @parameter		nEnumVal
* @return 			TextType enum string
*/
char* MediaFormatTextTypeGetEnum(media_format_text_type_e nEnumVal)
{
	char *szGetEnumVal = NULL;
	
	switch ( nEnumVal)
	{
		case MEDIA_FORMAT_TEXT_TYPE_NONE:						szGetEnumVal = "MEDIA_FORMAT_TEXT_TYPE_NONE";						break;
		case MEDIA_FORMAT_TEXT_TYPE_TIMED_TEXT_MP4: 			szGetEnumVal = "MEDIA_FORMAT_TEXT_TYPE_TIMED_TEXT_MP4";				break;
		case MEDIA_FORMAT_TEXT_TYPE_TIMED_TEXT_3GPP:			szGetEnumVal = "MEDIA_FORMAT_TEXT_TYPE_TIMED_TEXT_3GPP";			break;
		case MEDIA_FORMAT_TEXT_TYPE_UNKNOWN:					szGetEnumVal = "MEDIA_FORMAT_TEXT_TYPE_UNKNOWN";					break;
	}
	return szGetEnumVal;
}
/** @} */ 
