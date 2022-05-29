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
#include "ITs-mediastreamrecorder-common.h"

/** @addtogroup itc-mediastreamrecorder
*  @ingroup itc
*  @{
*/

media_format_h g_hMediaFormat[MAX_MEDIA_PACKET_CNT];
media_packet_h g_hMediaPkt[MAX_MEDIA_PACKET_CNT];

//Add helper function definitions here

/**
* @function 		StreamRecorderGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* StreamRecorderGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case STREAMRECORDER_ERROR_INVALID_PARAMETER:	szErrorVal = "STREAMRECORDER_ERROR_INVALID_PARAMETER";		break;
	case STREAMRECORDER_ERROR_INVALID_STATE:		szErrorVal = "STREAMRECORDER_ERROR_INVALID_STATE";			break;
	case STREAMRECORDER_ERROR_OUT_OF_MEMORY:		szErrorVal = "STREAMRECORDER_ERROR_OUT_OF_MEMORY";			break;
	case STREAMRECORDER_ERROR_INVALID_OPERATION:	szErrorVal = "STREAMRECORDER_ERROR_INVALID_OPERATION";		break;
	case STREAMRECORDER_ERROR_OUT_OF_STORAGE:		szErrorVal = "STREAMRECORDER_ERROR_OUT_OF_STORAGE";			break;
	case STREAMRECORDER_ERROR_PERMISSION_DENIED:	szErrorVal = "STREAMRECORDER_ERROR_PERMISSION_DENIED";		break;
	case STREAMRECORDER_ERROR_NOT_SUPPORTED:		szErrorVal = "STREAMRECORDER_ERROR_NOT_SUPPORTED";			break;
	default:										szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

/**
* @function             MediaFormatGetError
* @description          Maps error enums to string values
* @parameter            nRet : error code returned
* @return               error string
*/
char* MediaFormatGetError(int nRet)
{
    char *szErrorVal = NULL;

    switch ( nRet )
    {
    case MEDIA_FORMAT_ERROR_NONE:                          szErrorVal = "MEDIA_FORMAT_ERROR_NONE";                     break;
    case MEDIA_FORMAT_ERROR_OUT_OF_MEMORY:                 szErrorVal = "MEDIA_FORMAT_ERROR_OUT_OF_MEMORY";            break;
    case MEDIA_FORMAT_ERROR_INVALID_PARAMETER:             szErrorVal = "MEDIA_FORMAT_ERROR_INVALID_PARAMETER";        break;
    case MEDIA_FORMAT_ERROR_INVALID_OPERATION:             szErrorVal = "MEDIA_FORMAT_ERROR_INVALID_OPERATION";        break;
    case MEDIA_FORMAT_ERROR_FILE_NO_SPACE_ON_DEVICE:       szErrorVal = "MEDIA_FORMAT_ERROR_FILE_NO_SPACE_ON_DEVICE";  break;
    default:                                               szErrorVal = "Unknown Error";                               break;
    }

    return szErrorVal;
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
	default:											szErrorVal = "Unknown Error";									break;
	}
	return szErrorVal;
}

/**
 * @function 		StreamRecorderGetDataPath
 * @description	 	Returns the application data path
 * @parameter		pAppDataPath: application data path
 * @return 			0 if pass else 1
 */
bool StreamRecorderGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get application data path; app_get_data_path returned null value \\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, PATH_LEN-1);

	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}

/**
 * @function 		StreamRecoderAppendToAppDataPath
 * @description	 	Appends the input string to application data path
 * @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
 * @return 			true if succeed else false
 */
bool StreamRecoderAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( (NULL == pInputPath) || (NULL == pFinalPath) )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == StreamRecorderGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, PATH_LEN-1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF("[Line : %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);

	return true;
}

/**
* @function 		TimeoutFunction
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean TimeoutFunction(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

/**
* @function 		SetParam
* @description	 	SET PARAM
* @parameter		NA
* @return 			0 if succeed else 1
*/
int SetParam(streamrecorder_h g_hRecorder)
{
	int nWidth = 1280;
	int nHeight = 720;
	int nSetFrameRate = 30;

	int nRet = streamrecorder_enable_source_buffer(g_hRecorder, STREAMRECORDER_SOURCE_VIDEO);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));

    nRet = streamrecorder_set_video_source_format(g_hRecorder, STREAMRECORDER_VIDEO_SOURCE_FORMAT_I420);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_source_format", StreamRecorderGetError(nRet));

    nRet = streamrecorder_set_file_format(g_hRecorder, STREAMRECORDER_FILE_FORMAT_MP4);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_file_format", StreamRecorderGetError(nRet));

	nRet = streamrecorder_set_video_encoder(g_hRecorder, STREAMRECORDER_VIDEO_CODEC_MPEG4);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_encoder", StreamRecorderGetError(nRet));

	nRet = streamrecorder_set_video_resolution(g_hRecorder, nWidth, nHeight);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_resolution", StreamRecorderGetError(nRet));

	nRet = streamrecorder_set_video_framerate(g_hRecorder, nSetFrameRate);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_framerate", StreamRecorderGetError(nRet));

	return 0;
}

/**
* @function 		SetParam
* @description	 	SET PARAM
* @parameter		NA
* @return 			0 if succeed else 1
*/
int SetParamCall(streamrecorder_h g_hCallRecorder)
{
	int nWidth = 352;
	int nHeight = 288;
	int nSetFrameRate = 30;

	int nRet = streamrecorder_enable_source_buffer(g_hCallRecorder, STREAMRECORDER_SOURCE_VIDEO);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));

    nRet = streamrecorder_set_video_source_format(g_hCallRecorder, STREAMRECORDER_VIDEO_SOURCE_FORMAT_NV21);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_source_format", StreamRecorderGetError(nRet));

    nRet = streamrecorder_set_file_format(g_hCallRecorder, STREAMRECORDER_FILE_FORMAT_MP4);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_file_format", StreamRecorderGetError(nRet));

	nRet = streamrecorder_set_video_encoder(g_hCallRecorder, STREAMRECORDER_VIDEO_CODEC_MPEG4);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_encoder", StreamRecorderGetError(nRet));

	nRet = streamrecorder_set_video_resolution(g_hCallRecorder, nWidth, nHeight);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_resolution", StreamRecorderGetError(nRet));

	nRet = streamrecorder_set_video_framerate(g_hCallRecorder, nSetFrameRate);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_framerate", StreamRecorderGetError(nRet));

	return 0;
}

/**
* @function 		CreatePacketAndFormatData
* @description	 	create format and media packet and fill data
* @parameter		NA
* @return 			0 if succeed else 1
*/
int CreatePacketAndFormatData(streamrecorder_h g_hRecorder)
{
	int nCounter,nRet;
	FILE *pvFile;
	unsigned char *pszPtr;
	int nWidth = 352;
	int nHeight = 288;
	size_t total_ysize = nWidth * nHeight;
	size_t total_uvsize = nWidth * nHeight / 4;
	size_t total_read = 0;
	size_t read_sum;
	g_ncount = 0;

	char pFilePath[PATH_LEN] = {0};
	if ( false == StreamRecoderAppendToAppDataPath(MEDIA_FILE_PATH, pFilePath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	pvFile = fopen(pFilePath, "rb");
	if (pvFile == NULL)
	{
		FPRINTF("[Line : %d][%s] File cant be loaded\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	for (nCounter = 0; nCounter < MAX_MEDIA_PACKET_CNT; nCounter++)
	{
		nRet = media_format_create(&g_hMediaFormat[nCounter]);
		PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet),fclose(pvFile));
		CHECK_HANDLE_CLEANUP(g_hMediaFormat[nCounter],"media_format_create",fclose(pvFile));

		nRet = media_format_set_video_mime(g_hMediaFormat[nCounter], MEDIA_FORMAT_I420);
		PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet),fclose(pvFile));

		nRet = media_format_set_video_width(g_hMediaFormat[nCounter], nWidth);
		PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaFormatGetError(nRet),fclose(pvFile));

		nRet = media_format_set_video_height(g_hMediaFormat[nCounter], nHeight);
		PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaFormatGetError(nRet),fclose(pvFile));

		nRet = media_packet_create(g_hMediaFormat[nCounter], NULL, NULL, &g_hMediaPkt[nCounter]);
		PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_create", MediaPacketGetError(nRet),fclose(pvFile));
		CHECK_HANDLE_CLEANUP(g_hMediaPkt[nCounter], "media_packet_create", fclose(pvFile));

		nRet = media_packet_alloc(g_hMediaPkt[nCounter]);
		PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_alloc", MediaPacketGetError(nRet),fclose(pvFile));

		read_sum = 0;
		media_packet_get_video_plane_data_ptr(g_hMediaPkt[nCounter], 0, (void**)&pszPtr);
		FPRINTF("[Line : %d][%s] video plane info : 0 %p\n", __LINE__, API_NAMESPACE, pszPtr);
		while (total_ysize - read_sum)
		{
			read_sum += fread(pszPtr + read_sum, 1, total_ysize - read_sum, pvFile);

			FPRINTF("[Line : %d][%s] Read %d frame data (read size %d, left %d)\\n", __LINE__, API_NAMESPACE, nCounter, read_sum, total_ysize - read_sum);
			if (feof(pvFile)) {
				FPRINTF("[Line : %d][%s] EoF occured in reading file\\n", __LINE__, API_NAMESPACE);
				fclose(pvFile);
				return 1;
			}
			if (ferror(pvFile)) {
				FPRINTF("[Line : %d][%s] Error occured in reading file\\n", __LINE__, API_NAMESPACE);
				fclose(pvFile);
				return 1;
			}
		}
		total_read += read_sum;
		read_sum = 0;
		media_packet_get_video_plane_data_ptr(g_hMediaPkt[nCounter], 1, (void**)&pszPtr);
		FPRINTF("[Line : %d][%s] video plane info : 1 %p\n", __LINE__, API_NAMESPACE, pszPtr);
		while (total_uvsize - read_sum)
		{
			read_sum += fread(pszPtr + read_sum, 1, total_uvsize - read_sum, pvFile);

			FPRINTF("[Line : %d][%s] Read %d frame data (read size %d, left %d)\\n", __LINE__, API_NAMESPACE, nCounter, read_sum, total_uvsize - read_sum);
			if (feof(pvFile)) {
				FPRINTF("[Line : %d][%s] EoF occured in reading file\\n", __LINE__, API_NAMESPACE);
				fclose(pvFile);
				return 1;
			}
			if (ferror(pvFile)) {
				FPRINTF("[Line : %d][%s] Error occured in reading file\\n", __LINE__, API_NAMESPACE);
				fclose(pvFile);
				return 1;
			}
		}

		total_read += read_sum;
		read_sum = 0;
		media_packet_get_video_plane_data_ptr(g_hMediaPkt[nCounter], 2, (void**)&pszPtr);
		FPRINTF("[Line : %d][%s] video plane info : 2 %p\n", __LINE__, API_NAMESPACE, pszPtr);
		while (total_uvsize - read_sum)
		{
			read_sum += fread(pszPtr + read_sum, 1, total_uvsize - read_sum, pvFile);

			FPRINTF("[Line : %d][%s] Read %d frame data (read size %d, left %d)\\n", __LINE__, API_NAMESPACE, nCounter, read_sum, total_uvsize - read_sum);
			if (feof(pvFile)) {
				FPRINTF("[Line : %d][%s] EoF occured in reading file\\n", __LINE__, API_NAMESPACE);
				fclose(pvFile);
				return 1;
			}
			if (ferror(pvFile)) {
				FPRINTF("[Line : %d][%s] Error occured in reading file\\n", __LINE__, API_NAMESPACE);
				fclose(pvFile);
				return 1;
			}
		}
		total_read += read_sum;

		FPRINTF("[Line : %d][%s] Read data file size : %d\\n", __LINE__, API_NAMESPACE, total_read);
		if (media_packet_set_buffer_size(g_hMediaPkt[nCounter], total_read))
		{
			FPRINTF("[Line : %d][%s]buf size failed\\n", __LINE__, API_NAMESPACE);
			fclose(pvFile);
			return 1;
		}

		if (media_packet_set_pts(g_hMediaPkt[nCounter], g_ncount))
		{
			FPRINTF("[Line : %d][%s]unable to set the pts\\n", __LINE__, API_NAMESPACE);
			fclose(pvFile);
			return 1;
		}

		nRet = streamrecorder_push_stream_buffer(g_hRecorder, g_hMediaPkt[nCounter]);
		PRINT_RESULT_CLEANUP(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_push_stream_buffer", StreamRecorderGetError(nRet),fclose(pvFile));
		g_ncount = g_ncount + 33000000;
	}
	fclose(pvFile);
	return 0;
}

/**
* @function 		CreatePacketAndFormatData
* @description	 	create format and media packet and fill data
* @parameter		NA
* @return 			0 if succeed else 1
*/
int CreatePacketAndFormatDataCall(streamrecorder_h g_hCallRecorder)
{
	int nCounter,nRet;
	FILE *pvFile;
	unsigned char *pszPtr;
	int nWidth = 352;
	int nHeight = 288;
	size_t total_ysize = nWidth * nHeight;
	size_t total_uvsize = nWidth * nHeight / 2;
	size_t total_read = 0;
	size_t read_sum;
	g_ncount = 0;

	char pFilePath[PATH_LEN] = {0};
	if ( false == StreamRecoderAppendToAppDataPath(MEDIA_FILE_PATH, pFilePath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	pvFile = fopen(pFilePath, "rb");
	if (pvFile == NULL)
	{
		FPRINTF("[Line : %d][%s] File cant be loaded\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	for (nCounter = 0; nCounter < MAX_MEDIA_PACKET_CNT; nCounter++)
	{
		nRet = media_format_create(&g_hMediaFormat[nCounter]);
		PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet),fclose(pvFile));
		CHECK_HANDLE_CLEANUP(g_hMediaFormat[nCounter],"media_format_create",fclose(pvFile));

		nRet = media_format_set_video_mime(g_hMediaFormat[nCounter], MEDIA_FORMAT_NV21);
		PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet),fclose(pvFile));

		nRet = media_format_set_video_width(g_hMediaFormat[nCounter], nWidth);
		PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaFormatGetError(nRet),fclose(pvFile));

		nRet = media_format_set_video_height(g_hMediaFormat[nCounter], nHeight);
		PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaFormatGetError(nRet),fclose(pvFile));

		nRet = media_packet_create(g_hMediaFormat[nCounter], NULL, NULL, &g_hMediaPkt[nCounter]);
		PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_create", MediaPacketGetError(nRet),fclose(pvFile));
		CHECK_HANDLE_CLEANUP(g_hMediaPkt[nCounter], "media_packet_create",fclose(pvFile));

		nRet = media_packet_alloc(g_hMediaPkt[nCounter]);
		PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_alloc", MediaPacketGetError(nRet),fclose(pvFile));

		read_sum = 0;
		media_packet_get_video_plane_data_ptr(g_hMediaPkt[nCounter], 0, (void**)&pszPtr);
		FPRINTF("[Line : %d][%s] video plane info : 0 %p\n", __LINE__, API_NAMESPACE, pszPtr);
		while (total_ysize - read_sum)
		{
			read_sum += fread(pszPtr + read_sum, 1, total_ysize - read_sum, pvFile);

			FPRINTF("[Line : %d][%s] Read %d frame data (read size %d, left %d)\\n", __LINE__, API_NAMESPACE, nCounter, read_sum, total_ysize - read_sum);
			if (feof(pvFile)) {
				FPRINTF("[Line : %d][%s] EoF occured in reading file\\n", __LINE__, API_NAMESPACE);
				fclose(pvFile);
				return 1;
			}
			if (ferror(pvFile)) {
				FPRINTF("[Line : %d][%s] Error occured in reading file\\n", __LINE__, API_NAMESPACE);
				fclose(pvFile);
				return 1;
			}
		}
		total_read += read_sum;

		read_sum = 0;
		media_packet_get_video_plane_data_ptr(g_hMediaPkt[nCounter], 1, (void**)&pszPtr);
		FPRINTF("[Line : %d][%s] video plane info : 1 %p\n", __LINE__, API_NAMESPACE, pszPtr);
		while (total_uvsize - read_sum)
		{
			read_sum += fread(pszPtr + read_sum, 1, total_uvsize - read_sum, pvFile);

			FPRINTF("[Line : %d][%s] Read %d frame data (read size %d, left %d)\\n", __LINE__, API_NAMESPACE, nCounter, read_sum, total_uvsize - read_sum);
			if (feof(pvFile)) {
				FPRINTF("[Line : %d][%s] EoF occured in reading file\\n", __LINE__, API_NAMESPACE);
				fclose(pvFile);
				return 1;
			}
			if (ferror(pvFile)) {
				FPRINTF("[Line : %d][%s] Error occured in reading file\\n", __LINE__, API_NAMESPACE);
				fclose(pvFile);
				return 1;
			}
		}
		total_read += read_sum;

		FPRINTF("[Line : %d][%s] Read data file size : %zu\\n", __LINE__, API_NAMESPACE, total_read);
		if (media_packet_set_buffer_size(g_hMediaPkt[nCounter], total_read))
		{
			FPRINTF("[Line : %d][%s]buf size failed\\n", __LINE__, API_NAMESPACE);
			fclose(pvFile);
			return 1;
		}

		if (media_packet_set_pts(g_hMediaPkt[nCounter], g_ncount))
		{
			FPRINTF("[Line : %d][%s]unable to set the pts\\n", __LINE__, API_NAMESPACE);
			fclose(pvFile);
			return 1;
		}

		nRet = streamrecorder_push_stream_buffer(g_hCallRecorder, g_hMediaPkt[nCounter]);
		PRINT_RESULT_CLEANUP(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_push_stream_buffer", StreamRecorderGetError(nRet),fclose(pvFile));
		g_ncount = g_ncount + 33000000;
	}
	fclose(pvFile);
	return 0;
}

/**
* @function 		DestroyPacketAndFormatData
* @description	 	destroy format and media packet
* @parameter		NA
* @return 			NA
*/
void DestroyPacketAndFormatData(void)
{
	int nCounter;
	int nRet = MEDIA_FORMAT_ERROR_NONE;

	for (nCounter = 0; nCounter < MAX_MEDIA_PACKET_CNT; nCounter++)
	{
		nRet = media_format_unref(g_hMediaFormat[nCounter]);
		PRINT_RESULT_NORETURN(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

		nRet = media_packet_destroy(g_hMediaPkt[nCounter]);
		PRINT_RESULT_NORETURN(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_destroy", MediaPacketGetError(nRet));
	}
}

/** @} */
