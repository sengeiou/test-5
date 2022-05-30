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
#include "ITs-mediacodec-common.h"

/** @addtogroup itc-mediacodec
* @ingroup		itc
* @{
*/

//Add helper function definitions here

/**
* @function 		MediaCodecGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaCodecGetError(int nRet)
{
	char *szErrorVal = "Unknown error";
	switch ( nRet )
	{
	case MEDIACODEC_ERROR_NONE:							szErrorVal = "MEDIACODEC_ERROR_NONE";							break;
	case MEDIACODEC_ERROR_OUT_OF_MEMORY:				szErrorVal = "MEDIACODEC_ERROR_OUT_OF_MEMORY";					break;
	case MEDIACODEC_ERROR_INVALID_PARAMETER:			szErrorVal = "MEDIACODEC_ERROR_INVALID_PARAMETER";				break;
	case MEDIACODEC_ERROR_INVALID_OPERATION:			szErrorVal = "MEDIACODEC_ERROR_INVALID_OPERATION";				break;
	case MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE:		szErrorVal = "MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE";		break;
	case MEDIACODEC_ERROR_PERMISSION_DENIED:			szErrorVal = "MEDIACODEC_ERROR_PERMISSION_DENIED";				break;
	case MEDIACODEC_ERROR_INVALID_STATE:				szErrorVal = "MEDIACODEC_ERROR_INVALID_STATE";					break;
	case MEDIACODEC_ERROR_INVALID_INBUFFER:				szErrorVal = "MEDIACODEC_ERROR_INVALID_INBUFFER";				break;
	case MEDIACODEC_ERROR_INVALID_OUTBUFFER:			szErrorVal = "MEDIACODEC_ERROR_INVALID_OUTBUFFER";				break;
	case MEDIACODEC_ERROR_INTERNAL:						szErrorVal = "MEDIACODEC_ERROR_INTERNAL";						break;
	case MEDIACODEC_ERROR_NOT_INITIALIZED:				szErrorVal = "MEDIACODEC_ERROR_NOT_INITIALIZED";				break;
	case MEDIACODEC_ERROR_INVALID_STREAM:				szErrorVal = "MEDIACODEC_ERROR_INVALID_STREAM";					break;
	case MEDIACODEC_ERROR_CODEC_NOT_FOUND:				szErrorVal = "MEDIACODEC_ERROR_CODEC_NOT_FOUND";				break;
	case MEDIACODEC_ERROR_DECODE:						szErrorVal = "MEDIACODEC_ERROR_DECODE";							break;
	case MEDIACODEC_ERROR_NO_FREE_SPACE:				szErrorVal = "MEDIACODEC_ERROR_NO_FREE_SPACE";					break;
	case MEDIACODEC_ERROR_STREAM_NOT_FOUND:				szErrorVal = "MEDIACODEC_ERROR_STREAM_NOT_FOUND";				break;
	case MEDIACODEC_ERROR_NOT_SUPPORTED_FORMAT:			szErrorVal = "MEDIACODEC_ERROR_NOT_SUPPORTED_FORMAT";			break;
	case MEDIACODEC_ERROR_BUFFER_NOT_AVAILABLE:			szErrorVal = "MEDIACODEC_ERROR_BUFFER_NOT_AVAILABLE";			break;
	case MEDIACODEC_ERROR_OVERFLOW_INBUFFER:			szErrorVal = "MEDIACODEC_ERROR_OVERFLOW_INBUFFER";				break;
	case MEDIACODEC_ERROR_RESOURCE_CONFLICT:			szErrorVal = "MEDIACODEC_ERROR_RESOURCE_CONFLICT";			break;
	}
	return szErrorVal;
}

/**
* @function 		GetDataFromFile
* @description	 	Called to get data
* @parameter		NA
* @return 			NA
*/

unsigned int GetDataFromFile(unsigned char *pcm)
{	
	int read_size = 1024*2*2;
	unsigned char szBuffer[1000000];
	char pPath[CONFIG_VALUE_LEN_MAX] = {0,};
	static char* aenc_path = NULL;
	static char* aenc_file = "TestData.pcm";
	int size_of_path = 0;

	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pPath, API_NAMESPACE ))
	{
		size_of_path = strlen(pPath) + strlen(aenc_file) + 6;
		aenc_path = (char*)malloc(size_of_path);
		if (aenc_path == NULL)
		{
			FPRINTF("[Line : %d][%s] Memory allocation of aenc_path failed\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
		snprintf(aenc_path, size_of_path, "%s/res/%s", pPath, aenc_file);
	}

	FILE *pFile = NULL;
	pFile = fopen(aenc_path, "r");
	
	if (pFile == NULL)
	{
		FPRINTF("Unable to open Media File\\n");
		return 0;
	}

	size_t result = fread(szBuffer, 1, read_size, pFile);
	if(result != read_size)
	{
		fclose(pFile);
		return 0;
	}
	memcpy(pcm, szBuffer, read_size);
	fclose(pFile);
	return(read_size);
}

/**
* @function 		MediaCodecTimeoutFunction
* @description	 	Called if some callback is not invoked
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean MediaCodecTimeoutFunction(gpointer data)
{
	FPRINTF("[Line : %d][%s] Timeout Occurs\\n", __LINE__, API_NAMESPACE);
	GMainLoop *pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	return false;
}

/** @} */ //end of itc-mediacodec
