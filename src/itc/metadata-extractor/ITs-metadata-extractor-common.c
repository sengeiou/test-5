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
#include "ITs-metadata-extractor-common.h"

/** @addtogroup itc-metadata-extractor
* @ingroup		itc
* @{
*/

extern metadata_extractor_h g_hMetadataExtractorHandle;

//Add helper function definitions here

/**
* @function 		MetadataExtractorGetDataPath
* @description	 	Returns the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool MetadataExtractorGetDataPath(char* pAppDataPath)
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

	strncpy(pAppDataPath, pPath, PATH_LEN-1);

	FPRINTF("[Line: %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}

/**
* @function 		MetadataExtractorAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool MetadataExtractorAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( NULL == pInputPath || NULL == pFinalPath )
	{
		FPRINTF("[Line: %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == MetadataExtractorGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, PATH_LEN-1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF("[Line: %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);
	return true;
}

/**
* @function 		ExtractorGetError
* @description	 	Maps error enums to string values
* @parameter		nRet: error code returned
* @return 			error string
*/
char* Metadata_ExtractorGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case METADATA_EXTRACTOR_ERROR_NONE: 				szErrorVal = "METADATA_EXTRACTOR_ERROR_NONE"; 					break;
	case METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER: 	szErrorVal = "METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER"; 		break;
	case METADATA_EXTRACTOR_ERROR_OUT_OF_MEMORY: 		szErrorVal = "METADATA_EXTRACTOR_ERROR_OUT_OF_MEMORY";		 	break;
	case METADATA_EXTRACTOR_ERROR_OPERATION_FAILED: 	szErrorVal = "METADATA_EXTRACTOR_ERROR_OPERATION_FAILED"; 		break;
	case METADATA_EXTRACTOR_ERROR_FILE_EXISTS: 			szErrorVal = "METADATA_EXTRACTOR_ERROR_FILE_EXISTS"; 			break;
	default:											szErrorVal = "Unknown Error";									break;
	}
	return szErrorVal;
}

/**
* @function 		Metadata_ExtractorGetEnumAttributeError
* @description	 	get the string name of enum
* @parameter		nVal: enum value
* @return 			error string
*/
char* Metadata_ExtractorGetEnumAttributeString(int nVal)
{
	char *szString = NULL;
	switch ( nVal )
	{
	case METADATA_DURATION: 				szString = "METADATA_DURATION"; 			break;
	case METADATA_VIDEO_BITRATE: 			szString = "METADATA_VIDEO_BITRATE"; 		break;
	case METADATA_VIDEO_FPS: 				szString = "METADATA_VIDEO_FPS"; 			break;
	case METADATA_VIDEO_WIDTH: 				szString = "METADATA_VIDEO_WIDTH"; 			break;
	case METADATA_VIDEO_HEIGHT: 			szString = "METADATA_VIDEO_HEIGHT"; 		break;
	case METADATA_HAS_VIDEO: 				szString = "METADATA_HAS_VIDEO"; 			break;
	case METADATA_AUDIO_BITRATE: 			szString = "METADATA_AUDIO_BITRATE"; 		break;
	case METADATA_AUDIO_CHANNELS: 			szString = "METADATA_AUDIO_CHANNELS"; 		break;
	case METADATA_AUDIO_SAMPLERATE: 		szString = "METADATA_AUDIO_SAMPLERATE"; 	break;
	case METADATA_HAS_AUDIO: 				szString = "METADATA_HAS_AUDIO"; 			break;
	case METADATA_ARTIST: 					szString = "METADATA_ARTIST"; 				break;
	case METADATA_TITLE: 					szString = "METADATA_TITLE"; 				break;
	case METADATA_ALBUM: 					szString = "METADATA_ALBUM"; 				break;
	//case METADATA_ALBUM_ARTIST: 			szString = "METADATA_ALBUM_ARTIST";		 	break;
	case METADATA_GENRE: 					szString = "METADATA_GENRE"; 				break;
	case METADATA_COMPOSER: 				szString = "METADATA_COMPOSER"; 			break;
	case METADATA_COPYRIGHT: 				szString = "METADATA_COPYRIGHT"; 			break;
	case METADATA_DATE: 					szString = "METADATA_DATE"; 				break;
	case METADATA_DESCRIPTION: 				szString = "METADATA_DESCRIPTION"; 			break;
	case METADATA_COMMENT: 					szString = "METADATA_COMMENT"; 				break;
	case METADATA_TRACK_NUM: 				szString = "METADATA_TRACK_NUM"; 			break;
	case METADATA_CLASSIFICATION: 			szString = "METADATA_CLASSIFICATION"; 		break;
	case METADATA_RATING: 					szString = "METADATA_RATING"; 				break;
	case METADATA_LONGITUDE: 				szString = "METADATA_LONGITUDE"; 			break;
	case METADATA_LATITUDE: 				szString = "METADATA_LATITUDE"; 			break;
	case METADATA_ALTITUDE: 				szString = "METADATA_ALTITUDE"; 			break;
	case METADATA_CONDUCTOR: 				szString = "METADATA_CONDUCTOR"; 			break;
	case METADATA_UNSYNCLYRICS: 			szString = "METADATA_UNSYNCLYRICS"; 		break;
	case METADATA_SYNCLYRICS_NUM: 			szString = "METADATA_SYNCLYRICS_NUM"; 		break;
	case METADATA_RECDATE: 					szString = "METADATA_RECDATE"; 				break;
	case METADATA_ROTATE: 					szString = "METADATA_ROTATE"; 				break;
	case METADATA_VIDEO_CODEC:			szString = "METADATA_VIDEO_CODEC"; 				break;
	case METADATA_AUDIO_CODEC:		szString = "METADATA_AUDIO_CODEC"; 				break;
	}

	return szString;
}

/**
* @function 		Metadata_Extractor_SetPath_Audio
* @description	 	set file path for audio file
* @parameter		NA
* @return 			NA
* @Pre-Condition	NA
*/
bool Metadata_Extractor_SetPath_Audio(void)
{
	char szAudioFilePath[PATH_LEN] = {0,};
	if ( false == MetadataExtractorAppendToAppDataPath(MEDIA_AUDIO_PATH, szAudioFilePath) )
	{
		FPRINTF("[Line: %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	bool nRet = metadata_extractor_set_path(g_hMetadataExtractorHandle,szAudioFilePath)==0?0:1;
	FPRINTF("[Line: %d][%s] Metadata_Extractor_SetPath_Audio API- %s\\n", __LINE__, API_NAMESPACE, Metadata_ExtractorGetError(nRet));

	return nRet;
}

/**
* @function 		Metadata_Extractor_SetPath_Video
* @description	 	set file path for video file
* @parameter		NA
* @return 			NA
* @Pre-Condition	NA
*/ 
bool Metadata_Extractor_SetPath_Video(void)
{
	char szVideoFilePath[PATH_LEN] = {0,};
	if ( false == MetadataExtractorAppendToAppDataPath(MEDIA_VIDEO_PATH, szVideoFilePath) )
	{
		FPRINTF("[Line: %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	bool nRet = metadata_extractor_set_path(g_hMetadataExtractorHandle,szVideoFilePath)==0?0:1;
	FPRINTF("[Line: %d][%s] Metadata_Extractor_SetPath_Video API- %s\\n", __LINE__, API_NAMESPACE, Metadata_ExtractorGetError(nRet));

	return nRet;
}

/**
* @function 		ReadFromFile
* @description	 	Get file size and fill buffer with file content
* @parameter		NA
* @return 			void
*
*/
void ReadFromFile(char *pFilePath,void **pBuffer, int *pSize)
{
	FILE * fp = fopen (pFilePath, "r");	
	if ( fp )
	{
		fseek (fp, 0, SEEK_END);	
		*pSize = ftell(fp);	
		fseek (fp, 0, SEEK_SET);
		if(*pSize < 0)
		{
			*pBuffer = NULL;
			fclose (fp);
			return;
		}
		*pBuffer = malloc (*pSize);	
		if ( (fread(*pBuffer, *pSize, sizeof(char), fp) == 0) || ferror(fp) )
		{
			free(*pBuffer);
			*pBuffer = NULL;
		}
		fclose (fp);	
	}
}

/** @} */ //end of itc-metadata-extractor