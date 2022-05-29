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
#include "ITs-media-vision-common.h"

/** @addtogroup itc-media-vision
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		MediaVisionGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaVisionGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch(nRet)
	{
		case MEDIA_VISION_ERROR_NONE:					szErrorVal = "MEDIA_VISION_ERROR_NONE";						break;
		case MEDIA_VISION_ERROR_NOT_SUPPORTED:			szErrorVal = "MEDIA_VISION_ERROR_NOT_SUPPORTED";			break;
		case MEDIA_VISION_ERROR_MSG_TOO_LONG:			szErrorVal = "MEDIA_VISION_ERROR_MSG_TOO_LONG";				break;
		case MEDIA_VISION_ERROR_NO_DATA:				szErrorVal = "MEDIA_VISION_ERROR_NO_DATA";					break;
		case MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE:		szErrorVal = "MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE";		break;
		case MEDIA_VISION_ERROR_OUT_OF_MEMORY:			szErrorVal = "MEDIA_VISION_ERROR_OUT_OF_MEMORY";			break;
		case MEDIA_VISION_ERROR_INVALID_PARAMETER:		szErrorVal = "MEDIA_VISION_ERROR_INVALID_PARAMETER";		break;
		case MEDIA_VISION_ERROR_INVALID_OPERATION:		szErrorVal = "MEDIA_VISION_ERROR_INVALID_OPERATION";		break;
		case MEDIA_VISION_ERROR_PERMISSION_DENIED:		szErrorVal = "MEDIA_VISION_ERROR_PERMISSION_DENIED";		break;
		case MEDIA_VISION_ERROR_NOT_SUPPORTED_FORMAT:	szErrorVal = "MEDIA_VISION_ERROR_NOT_SUPPORTED_FORMAT";		break;
		case MEDIA_VISION_ERROR_INTERNAL:				szErrorVal = "MEDIA_VISION_ERROR_INTERNAL";					break;
		case MEDIA_VISION_ERROR_INVALID_DATA:			szErrorVal = "MEDIA_VISION_ERROR_INVALID_DATA";				break;
		case MEDIA_VISION_ERROR_INVALID_PATH:			szErrorVal = "MEDIA_VISION_ERROR_INVALID_PATH";				break;
		default:										szErrorVal = "MEDIA_VISION_ERROR_UNKNOWN";					break;
	}
	return szErrorVal;
}

/**
 * @function 		TimeoutFunction
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
gboolean TimeoutFunction(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	return false;
}

/**
* @function 		CreateMediaFormat
* @description	 	Create Media Format
* @parameter		NA
* @return 			NA
*/
bool CreateMediaFormat(void)
{
	int nRet = -1;
	nRet = media_format_create(&g_hMediaFormat);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s]  media_format_create API failed \\n", __LINE__, API_NAMESPACE);
		return false;
	}
	CHECK_HANDLE(g_hMediaFormat, "media_format_create");

	nRet = media_format_set_video_mime(g_hMediaFormat, MEDIA_FORMAT_RGB888);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_video_mime API failed \\n", __LINE__, API_NAMESPACE);
		return false;
	}

	nRet = media_format_set_video_height(g_hMediaFormat, BARCODEHEIGHT);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_video_height API failed \\n", __LINE__, API_NAMESPACE);
		return false;
	}
	nRet = media_format_set_video_width(g_hMediaFormat, BARCODEWIDTH);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_video_width API failed \\n", __LINE__, API_NAMESPACE);
		return false;
	}
	nRet = media_format_set_video_max_bps(g_hMediaFormat, 10);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_video_max_bps API failed \\n", __LINE__, API_NAMESPACE);
		return false;
	}
	nRet = media_format_set_video_avg_bps(g_hMediaFormat, 5);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_video_avg_bps API failed \\n", __LINE__, API_NAMESPACE);
		return false;
	}

	return 0;
}

bool CreateTBMSurface(void)
{
	tbm_format *tbm_formats = NULL;
    uint32_t format_num = 0;

    int ret = tbm_surface_query_formats(&tbm_formats, &format_num);
	 if (TBM_SURFACE_ERROR_NONE != ret)
	 {
		return 1;
	 }
	 
	 const unsigned int width = 800;
     const unsigned int height = 600;
	  
    int ind = 0;
    for (; ind < format_num; ++ind)
    {
        if (TBM_FORMAT_YUV420 == tbm_formats[ind])	
        {
            g_hTBMSurface = tbm_surface_create(width, height, TBM_FORMAT_YUV420);
			break;
         }
    }

	CHECK_HANDLE(g_hTBMSurface, "tbm_surface_create");
    return 0;
}

/**
* @function 		CreateMediaPacket
* @description	 	Create Media Packet
* @parameter		NA
* @return 			NA
*/
bool CreateMediaPacket(void)
{
	int nRet = CreateMediaFormat();
	PRINT_RESULT(0, nRet, "CreateMediaFormat", "Return Value Not Correct");

	nRet = CreateTBMSurface();
	PRINT_RESULT(0, nRet, "CreateTBMSurface", "Return Value Not Correct");

	nRet = media_packet_create_from_tbm_surface(g_hMediaFormat, g_hTBMSurface, NULL, NULL, &g_hMediaPacket);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s]  media_packet_create_from_tbm_surface API failed \\n", __LINE__, API_NAMESPACE);
		return false;
	}
	CHECK_HANDLE_CLEANUP(g_hMediaPacket, "media_packet_create", DestroyMediaPacket());

	nRet = media_packet_get_buffer_data_ptr(g_hMediaPacket, &g_pBufferData);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s]  media_packet_get_buffer_data_ptr API failed \\n", __LINE__, API_NAMESPACE);
		return false;
	}
	nRet = media_packet_set_buffer_size(g_hMediaPacket, BUFFERSIZE);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s]  media_packet_set_buffer_size API failed \\n", __LINE__, API_NAMESPACE);
		return false;
	}
	g_pBufferData = calloc(1, BUFFERSIZE);
	CHECK_HANDLE_CLEANUP(g_pBufferData, "calloc", DestroyMediaPacket());

	return 0;
}
/**
* @function 		DestroyMediaPacket
* @description	 	Destroy Media Packet
* @parameter		NA
* @return 			NA
*/
bool DestroyMediaPacket(void)
{
	FREE_MEMORY(g_pBufferData);
	if(g_hMediaPacket != NULL)
	{
		media_packet_destroy(g_hMediaPacket);
		g_hMediaPacket = NULL;
	}
	
	if(g_hTBMSurface)
	{
		tbm_surface_destroy(g_hTBMSurface);
		g_hTBMSurface = NULL;
	}

	return 0;
}

/**
* @function 		CreateFilledMediaSource
* @description	 	Create Filled Media Source
* @parameter		NA
* @return 			NA
*/
bool CreateFilledMediaSource(void)
{
	int nRet = -1;

	nRet = CreateMediaPacket();
	PRINT_RESULT(0, nRet, "CreateMediaPacket", "Return Value Not Correct");

	nRet = mv_source_fill_by_media_packet(g_hMvSource, g_hMediaPacket);
    PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_fill_by_media_packet", MediaVisionGetError(nRet), DestroyMediaPacket());

	return 0;
}

/**
* @function 		IterateGmainLoop
* @description	 	Called to wait
* @parameter		NA
* @return 			NA
*/
void IterateGmainLoop(void)
{
	g_pMainLoop = g_main_loop_new(NULL, false);
	g_nTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(g_nTimeoutId);
	g_nTimeoutId = 0;
	g_pMainLoop = NULL;
}

/**
* @function 		QuitGmainLoop
* @description	 	Called to quit
* @parameter		NA
* @return 			NA
*/
void QuitGmainLoop(void)
{
	if(g_pMainLoop != NULL)
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
 * @function 		MediaVisionGetDataPath
 * @description	 	Returns the application data path
 * @parameter		pAppDataPath: application data path
 * @return 			0 if pass else 1
 */
bool MediaVisionGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATHLEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get application data path; app_get_data_path returned null value \\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, PATHLEN-1);

	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}

/**
 * @function 		MediaVisionAppendToAppDataPath
 * @description	 	Appends the input string to application data path
 * @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
 * @return 			true if succeed else false
 */
bool MediaVisionAppendToAppDataPath(const char* pInputPath, char* pFinalPath)
{
	if ( (NULL == pInputPath) || (NULL == pFinalPath) )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATHLEN] = {0,};
	if ( false == MediaVisionGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATHLEN);
	strncpy(pFinalPath, pAppDataPath, PATHLEN-1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);
	
	FPRINTF("[Line : %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);

	return true;
}

/**
* @function 		ImageUtilGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ImageUtilGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case IMAGE_UTIL_ERROR_INVALID_PARAMETER:	szErrorVal = "IMAGE_UTIL_ERROR_INVALID_PARAMETER";		break;
	case IMAGE_UTIL_ERROR_OUT_OF_MEMORY:		szErrorVal = "IMAGE_UTIL_ERROR_OUT_OF_MEMORY";			break;
	case IMAGE_UTIL_ERROR_NO_SUCH_FILE:			szErrorVal = "IMAGE_UTIL_ERROR_NO_SUCH_FILE";			break;
	case IMAGE_UTIL_ERROR_INVALID_OPERATION:	szErrorVal = "IMAGE_UTIL_ERROR_INVALID_OPERATION";		break;
	case IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT:	szErrorVal = "IMAGE_UTIL_ERROR_NOT_SUPPORTED_FORMAT";	break;
	case IMAGE_UTIL_ERROR_NONE:					szErrorVal = "IMAGE_UTIL_ERROR_NONE";					break;
	default:									szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}

int image_load(const char *file_path, mv_source_h source)
{
    if (NULL == file_path || NULL == source)
    {
        FPRINTF("[Line : %d][%s] File path or source is NULL\\n", __LINE__, API_NAMESPACE);
        return MEDIA_VISION_ERROR_INVALID_PARAMETER;
    }

    unsigned long width = 0;
    unsigned long height = 0;
    unsigned long long buffer_size = 0;
    unsigned char *data_buffer = NULL;
    image_util_decode_h hDecoder = NULL;

    int ret = image_util_decode_create(&hDecoder);
    if (IMAGE_UTIL_ERROR_NONE != ret)
    {
        FPRINTF("[Line : %d][%s] image_util_decode_create Failed\\n", __LINE__, API_NAMESPACE);
        return ret;
    }
    ret = image_util_decode_set_input_path(hDecoder, file_path);
    if (IMAGE_UTIL_ERROR_NONE != ret)
    {
        ret = image_util_decode_destroy(hDecoder);
        if (IMAGE_UTIL_ERROR_NONE != ret)
        {
            FPRINTF("[Line : %d][%s] image_util_decode_destroy Failed\\n", __LINE__, API_NAMESPACE);
            return ret;
        }
        FPRINTF("[Line : %d][%s] image_util_decode_set_input_path Failed\\n", __LINE__, API_NAMESPACE);
        return ret;
    }
    ret = image_util_decode_set_colorspace(hDecoder, IMAGE_UTIL_COLORSPACE_RGB888);
    if (IMAGE_UTIL_ERROR_NONE != ret)
    {
        ret = image_util_decode_destroy(hDecoder);
        if (IMAGE_UTIL_ERROR_NONE != ret)
        {
            FPRINTF("[Line : %d][%s] image_util_decode_destroy Failed\\n", __LINE__, API_NAMESPACE);
            return ret;
        }
        FPRINTF("[Line : %d][%s] image_util_decode_set_colorspace Failed\\n", __LINE__, API_NAMESPACE);
        return ret;
    }
    ret = image_util_decode_set_output_buffer(hDecoder, &data_buffer);
    if (IMAGE_UTIL_ERROR_NONE != ret)
    {
        ret = image_util_decode_destroy(hDecoder);
        if (IMAGE_UTIL_ERROR_NONE != ret)
        {
            FPRINTF("[Line : %d][%s] image_util_decode_destroy Failed\\n", __LINE__, API_NAMESPACE);
            return ret;
        }
        FPRINTF("[Line : %d][%s] image_util_decode_set_output_buffer Failed\\n", __LINE__, API_NAMESPACE);
        return ret;
    }

    ret = image_util_decode_run(hDecoder, &width, &height, &buffer_size);
    if (IMAGE_UTIL_ERROR_NONE != ret)
    {
        if (data_buffer)
        {
            free(data_buffer);
            data_buffer = NULL;
        }
        ret = image_util_decode_destroy(hDecoder);
        if (IMAGE_UTIL_ERROR_NONE != ret)
        {
            FPRINTF("[Line : %d][%s] image_util_decode_destroy Failed\\n", __LINE__, API_NAMESPACE);
            return ret;
        }
        FPRINTF("[Line : %d][%s] image_util_decode_run Failed\\n", __LINE__, API_NAMESPACE);
        return ret;
    }

    mv_colorspace_e source_colorspace = MEDIA_VISION_COLORSPACE_RGB888;

    ret = mv_source_clear(source);
    if (MEDIA_VISION_ERROR_NONE != ret)
    {
        if (data_buffer)
        {
            free(data_buffer);
            data_buffer = NULL;
        }
        ret = image_util_decode_destroy(hDecoder);
        if (IMAGE_UTIL_ERROR_NONE != ret)
        {
            FPRINTF("[Line : %d][%s] image_util_decode_destroy Failed\\n", __LINE__, API_NAMESPACE);
            return ret;
        }
        FPRINTF("[Line : %d][%s] Error occured when clearing the source\\n", __LINE__, API_NAMESPACE);
        return ret;
    }

    ret = mv_source_fill_by_buffer(source, data_buffer, buffer_size, width, height, source_colorspace);
    if (MEDIA_VISION_ERROR_NONE != ret)
    {
        if (data_buffer)
        {
            free(data_buffer);
            data_buffer = NULL;
        }
        ret = image_util_decode_destroy(hDecoder);
        if (IMAGE_UTIL_ERROR_NONE != ret)
        {
            FPRINTF("[Line : %d][%s] image_util_decode_destroy Failed\\n", __LINE__, API_NAMESPACE);
            return ret;
        }
        FPRINTF("[Line : %d][%s] Error occured when filling the source by buffer\\n", __LINE__, API_NAMESPACE);
        return ret;
    }

    if (data_buffer)
    {
        free(data_buffer);
        data_buffer = NULL;
    }
    ret = image_util_decode_destroy(hDecoder);
    if (IMAGE_UTIL_ERROR_NONE != ret)
    {
        FPRINTF("[Line : %d][%s] image_util_decode_destroy Failed\\n", __LINE__, API_NAMESPACE);
        return ret;
    }

    return MEDIA_VISION_ERROR_NONE;
}

bool checkModelFile( const char *fSrcPath, const char *fDstPath)
{
    FILE *file1, *file2;
    int ch1, ch2;

    file1 = fopen(fSrcPath, "r");
    if (file1 == NULL)
    {
		FPRINTF("[Line : %d][%s] Cannot open %s for reading\\n", __LINE__, API_NAMESPACE,fSrcPath);
        return FALSE;
    }
	file2 = fopen(fDstPath, "r");
    if (file2 == NULL)
    {
		FPRINTF("[Line : %d][%s] Cannot open %s for reading\\n", __LINE__, API_NAMESPACE,fDstPath);
		fclose(file1);
        return FALSE;
    }
    else
    {
        ch1 = getc(file1);
        ch2 = getc(file2);

        while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2))
        {
            ch1 = getc(file1);
            ch2 = getc(file2);
        }

        if (ch1 == ch2)
        {
            fclose(file1);
            fclose(file2);
            return TRUE;
        }
	}

	FPRINTF("[Line : %d][%s] Model files are Not identical\\n", __LINE__, API_NAMESPACE);
    fclose(file1);
    fclose(file2);
    return FALSE;
}

/** @} */
