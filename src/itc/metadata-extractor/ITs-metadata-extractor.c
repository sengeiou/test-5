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

//& set: MetadataExtractor

/**
* @function 		ITs_metadata_extractor_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_metadata_extractor_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Metadata_Extractor_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsValidHandle = true;
	int nRet = metadata_extractor_create(&g_hMetadataExtractorHandle);
	if ( nRet != METADATA_EXTRACTOR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to create extractor handle, error returned = %s\\n", __LINE__, API_NAMESPACE, Metadata_ExtractorGetError(nRet));
		g_bIsValidHandle = false;
	}
}

/**
* @function 		ITs_metadata_extractor_cleanup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_metadata_extractor_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Metadata_Extractor_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = metadata_extractor_destroy(g_hMetadataExtractorHandle);
	if ( nRet != METADATA_EXTRACTOR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to destroy extractor handle, error returned = %s\\n", __LINE__, API_NAMESPACE, Metadata_ExtractorGetError(nRet));
	}
}

/** @addtogroup	itc-metadata-extractor-testcases
* @brief 		Integration testcases for module metadata-extractor
* @ingroup		itc-metadata-extractor
* @{
*/

//& purpose: create and destroy meta-data extractor handle
//& type: auto
/**
* @testcase 			ITc_metadata_extractor_create_destroy_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			create and destroy meta-data extractor handle
* @scenario				NA							
* @apicovered			metadata_extractor_create, metadata_extractor_destroy
* @passcase				When metadata_extractor_create and metadata_extractor_destroy is successful
* @failcase				If metadata_extractor_create or metadata_extractor_destroy fails
* @precondition			create a meta-data extractor valid handle using metadata_extractor_create API
* @postcondition		NA.
*/
int ITc_metadata_extractor_create_destroy_p(void)
{
	START_TEST;

	metadata_extractor_h hHandle = NULL;

	//Target APIs
	int nRet = metadata_extractor_create(&hHandle);	
	PRINT_RESULT(METADATA_EXTRACTOR_ERROR_NONE, nRet, "metadata_extractor_create", Metadata_ExtractorGetError(nRet));

	//Target APIs
	nRet = metadata_extractor_destroy(hHandle);
	PRINT_RESULT(METADATA_EXTRACTOR_ERROR_NONE, nRet, "metadata_extractor_destroy", Metadata_ExtractorGetError(nRet));

	return 0;
}

//& purpose: Gets an artwork image of a media file
//& type: auto
/**
* @testcase 			ITc_metadata_extractor_get_artwork_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets an artwork image of a media file
* @scenario				get the artwork image of a media file
* @apicovered			metadata_extractor_get_artwork
* @passcase				When metadata_extractor_get_artwork and metadata_extractor_get_artwork is successful
* @failcase				If metadata_extractor_set_path or metadata_extractor_get_artwork fails
* @precondition			Set path to extract by calling metadata_extractor_set_path().
* @precondition			None
* @postcondition		return artwork, size and mime-type of file.
*/
int ITc_metadata_extractor_get_artwork_p(void)
{
	START_TEST;

	//precondition API,//set path
	int nRet = Metadata_Extractor_SetPath_Audio();
	PRINT_RESULT(METADATA_EXTRACTOR_ERROR_NONE, nRet, "Metadata_Extractor_SetPath_Audio", Metadata_ExtractorGetError(nRet));
	
	void *vpArtwork=NULL;
	int nSize = 0;
	char *pcMime_type = NULL;

	//Target API
	nRet = metadata_extractor_get_artwork(g_hMetadataExtractorHandle, &vpArtwork, &nSize, &pcMime_type);
	PRINT_RESULT(METADATA_EXTRACTOR_ERROR_NONE, nRet, "metadata_extractor_get_artwork", Metadata_ExtractorGetError(nRet));
	if ( vpArtwork == NULL || pcMime_type == NULL || nSize == 0 )
	{
		FPRINTF("[Line : %d][%s] metadata_extractor_get_artwork failed, output parameter having invalid value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(vpArtwork);
	FREE_MEMORY(pcMime_type);

	return 0;
}

//& purpose: Gets frame of a video media file.  
//& type: auto
/**
* @testcase 			ITc_metadata_extractor_get_frame_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets frame of a video media file.  
* @scenario				Before getting frame of file, set file path						
* @apicovered			metadata_extractor_get_frame
* @passcase				When metadata_extractor_get_frame is successful
* @failcase				If metadata_extractor_get_frame fails
* @precondition			Set path to extract by calling metadata_extractor_set_path
* @postcondition		return frame of file and frame size
*/
int ITc_metadata_extractor_get_frame_p(void)
{
	START_TEST;
	
	//precondition API,//set path
	int nRet = Metadata_Extractor_SetPath_Video();
	PRINT_RESULT(METADATA_EXTRACTOR_ERROR_NONE, nRet, "Metadata_Extractor_SetPath_Video", Metadata_ExtractorGetError(nRet));

	void *pvFrame =NULL; 
	int nFramesize = 0;

	//Target API
	nRet = metadata_extractor_get_frame(g_hMetadataExtractorHandle, &pvFrame, &nFramesize);
	PRINT_RESULT(METADATA_EXTRACTOR_ERROR_NONE, nRet, "metadata_extractor_get_frame", Metadata_ExtractorGetError(nRet));
	if ( pvFrame == NULL || nFramesize <= 0 )
	{
		FPRINTF("[Line : %d][%s] metadata_extractor_get_frame failed, output parameter having invalid value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(pvFrame);
	return 0;
}

//& purpose: Gets a frame of video media.  
//& type: auto
/**
* @testcase 			ITc_metadata_extractor_get_frame_at_time_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets a frame of video media. . 
* @scenario				Before getting frame, set file path							
* @apicovered			metadata_extractor_get_frame_at_time 
* @passcase				When ITc_metadata_extractor_get_frame_at_time is successful
* @failcase				If ITc_metadata_extractor_get_frame_at_time fails
* @precondition			Set path to extract by calling metadata_extractor_set_path
* @postcondition		return frame and size of a frame
*/
int ITc_metadata_extractor_get_frame_at_time_p(void)
{
	START_TEST;

	//precondition API,//set path
	int nRet = Metadata_Extractor_SetPath_Video();
	PRINT_RESULT(METADATA_EXTRACTOR_ERROR_NONE, nRet, "Metadata_Extractor_SetPath_Video", Metadata_ExtractorGetError(nRet));

	unsigned long ulTimestamp = 1;
	bool bIs_accurate = false; 
	void *pvFrame = NULL;
	int nSize = 0;

	//Target API
	nRet = metadata_extractor_get_frame_at_time(g_hMetadataExtractorHandle, ulTimestamp, bIs_accurate, &pvFrame, &nSize);
	PRINT_RESULT(METADATA_EXTRACTOR_ERROR_NONE, nRet, "metadata_extractor_get_frame_at_time", Metadata_ExtractorGetError(nRet));
	if ( pvFrame == NULL || nSize <= 0 )
	{
		FPRINTF("[Line : %d][%s] metadata_extractor_get_frame_at_time failed, output parameter having invalid value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	FREE_MEMORY(pvFrame);
	return 0;
}

//& purpose: Gets meta-data of multimedia file.  
//& type: auto
/**
* @testcase 			ITc_metadata_extractor_get_metadata_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets meta-data of multimedia file.   
* @scenario				Before getting artwork of file need to set file path							
* @apicovered			metadata_extractor_get_metadata
* @passcase				When metadata_extractor_get_metadata is successful
* @failcase				If metadata_extractor_get_metadata fails
* @precondition			Set path to extract by calling metadata_extractor_set_path
* @postcondition		return buffer on success
*/
int ITc_metadata_extractor_get_metadata_p(void)
{
	START_TEST;

	//precondition API,//set path
	int nRet = Metadata_Extractor_SetPath_Video();
	PRINT_RESULT(METADATA_EXTRACTOR_ERROR_NONE, nRet, "Metadata_Extractor_SetPath_Video", Metadata_ExtractorGetError(nRet));

	int nAttributes[] = { 	METADATA_DURATION, 
		METADATA_VIDEO_BITRATE, 
		METADATA_VIDEO_FPS, 
		METADATA_VIDEO_WIDTH, 
		METADATA_VIDEO_HEIGHT, 
		METADATA_HAS_VIDEO, 
		METADATA_AUDIO_BITRATE, 
		METADATA_AUDIO_CHANNELS, 
		METADATA_AUDIO_SAMPLERATE, 
		//METADATA_AUDIO_BITPERSAMPLE,
		METADATA_HAS_AUDIO, 
		METADATA_ARTIST, 
		METADATA_TITLE, 
		METADATA_ALBUM, 
		//METADATA_ALBUM_ARTIST, 
		METADATA_GENRE, 
		METADATA_COMPOSER,
		METADATA_COPYRIGHT, 
		METADATA_DATE, 
		/*METADATA_DESCRIPTION,*/ 
		METADATA_COMMENT, 
		METADATA_TRACK_NUM,
		/*METADATA_CLASSIFICATION, 
		METADATA_RATING,*/ 
		METADATA_LONGITUDE, 
		METADATA_LATITUDE, 
		METADATA_ALTITUDE, 
		/*METADATA_CONDUCTOR, 
		METADATA_UNSYNCLYRICS,*/ 
		METADATA_SYNCLYRICS_NUM, 
		METADATA_RECDATE, 
		/*METADATA_ROTATE,*/
		METADATA_VIDEO_CODEC,		
		METADATA_AUDIO_CODEC,
		METADATA_360
		};
	int nEnum_Size = sizeof(nAttributes) / sizeof(nAttributes[0]);
	int nEnum_Counter;

	char *pcValue = NULL;

	for ( nEnum_Counter = 0; nEnum_Counter < nEnum_Size; nEnum_Counter++ )
	{	
		//Target API
		int nRet = metadata_extractor_get_metadata(g_hMetadataExtractorHandle, nAttributes[nEnum_Counter], &pcValue);
		if ( nRet != METADATA_EXTRACTOR_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] metadata_extractor_get_metadata failed for attribute = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, Metadata_ExtractorGetEnumAttributeString(nAttributes[nEnum_Counter]), Metadata_ExtractorGetError(nRet));
			return 1;
		}
		if ( pcValue == NULL ) // pcValue can be NULL if the sample video file doesn't have data.
		{
			FPRINTF("[Line : %d][%s] output parameter for enum %s is NULL\\n", __LINE__, API_NAMESPACE,
				Metadata_ExtractorGetEnumAttributeString(nAttributes[nEnum_Counter]));
		}
		else
		{
			FPRINTF("[Line : %d][%s] metadata_extractor_get_metadata succeeded for attribute = %s\\n", __LINE__, API_NAMESPACE, Metadata_ExtractorGetEnumAttributeString(nAttributes[nEnum_Counter]));
		}
		FREE_MEMORY(pcValue);
	}
	return 0;
}

//& purpose: Gets sync-lyric of a media file  
//& type: auto
/**
* @testcase 			ITc_metadata_extractor_get_synclyrics_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets sync-lyric of a media file.   
* @scenario				Before getting sync-lyrics of file, set file path							
* @apicovered			metadata_extractor_get_synclyrics
* @passcase				When metadata_extractor_get_synclyrics is successful
* @failcase				If metadata_extractor_get_synclyrics fails
* @precondition			Set path to extract by calling metadata_extractor_set_path. Get time/lyrics set number by calling metadata_extractor_get_metadata 
* @postcondition		return buffer on success
*/
int ITc_metadata_extractor_get_synclyrics_p(void)
{
	START_TEST;

	//precondition API,//set path
	int nRet = Metadata_Extractor_SetPath_Video();
	PRINT_RESULT(METADATA_EXTRACTOR_ERROR_NONE, nRet, "Metadata_Extractor_SetPath_Video", Metadata_ExtractorGetError(nRet));

	unsigned long ulTimestamp = 0;
	char *pcLyrics = NULL;

	//Target API
	nRet = metadata_extractor_get_synclyrics (g_hMetadataExtractorHandle, 1, &ulTimestamp, &pcLyrics);
	PRINT_RESULT(METADATA_EXTRACTOR_ERROR_NONE, nRet, "metadata_extractor_get_synclyrics", Metadata_ExtractorGetError(nRet));
	FREE_MEMORY(pcLyrics);
	return 0;
}

//& purpose: Sets a buffer for meta-data extraction. . 
//& type: auto
/**
* @testcase 			ITc_metadata_extractor_set_buffer_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets a buffer for meta-data extraction. 
* @scenario				Before getting artwork of file need to set file path							
* @apicovered			metadata_extractor_set_buffer
* @passcase				When metadata_extractor_set_buffer is successful
* @failcase				If metadata_extractor_set_buffer fails
* @precondition			create a meta-data extractor valid handle using metadata_extractor_create API
* @postcondition		return 0 on success
*/
int ITc_metadata_extractor_set_buffer_p(void)
{
	START_TEST;

	char szAudioFilePath[PATH_LEN] = {0,};
	if ( false == MetadataExtractorAppendToAppDataPath(MEDIA_AUDIO_PATH, szAudioFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	void *pBuffer = NULL;
	int nSize = 0;
	CHECK_HANDLE(szAudioFilePath,"MetadataExtractorAppendToAppDataPath");
	ReadFromFile(szAudioFilePath, &pBuffer,&nSize);
	if ( pBuffer == NULL )
	{
		FPRINTF("[Line : %d][%s] Precondition failed. Could not allocate memory to buffer", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(nSize < 0)
	{
		FPRINTF("[Line : %d][%s] nSize is not set", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pBuffer);
		return 1;
	
	}
	//Target API
	int nRet = metadata_extractor_set_buffer(g_hMetadataExtractorHandle, pBuffer, nSize);	
	PRINT_RESULT_CLEANUP(METADATA_EXTRACTOR_ERROR_NONE, nRet, "metadata_extractor_set_buffer", Metadata_ExtractorGetError(nRet),FREE_MEMORY(pBuffer));

	FREE_MEMORY(pBuffer);
	return 0;
}

//& purpose: Sets a file path for meta-data extraction. 
//& type: auto
/**
* @testcase 				ITc_metadata_extractor_set_path_p
* @since_tizen 				2.3
* @author            		SRID(parshant.v)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Sets a file path for meta-data extraction. 
* @scenario					Before getting artwork of file need to set file path							
* @apicovered				metadata_extractor_set_path
* @passcase					When metadata_extractor_set_path is successful
* @failcase					If metadata_extractor_set_path fails
* @precondition				create a meta-data extractor valid handle using metadata_extractor_create API
* @postcondition			return 0 on success
*/
int ITc_metadata_extractor_set_path_p(void)
{
	START_TEST;

	char szAudioFilePath[PATH_LEN] = {0,};
	if ( false == MetadataExtractorAppendToAppDataPath(MEDIA_AUDIO_PATH, szAudioFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}	
	
	//Target API
	int nRet = metadata_extractor_set_path(g_hMetadataExtractorHandle, szAudioFilePath);
	PRINT_RESULT(METADATA_EXTRACTOR_ERROR_NONE, nRet, "metadata_extractor_set_path", Metadata_ExtractorGetError(nRet));

	return 0;
}

/** @} */ //end of itc-metadata-extractor
/** @} */ //end of itc-metadata-extractor-testcases