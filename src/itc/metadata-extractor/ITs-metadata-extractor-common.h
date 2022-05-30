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
#ifndef _ITS_METADATA_EXTRACTOR_COMMON_H_
#define _ITS_METADATA_EXTRACTOR_COMMON_H_

#include "tct_common.h"

#include <pthread.h>
#include <app.h>

#include <metadata_extractor.h>

/** @addtogroup itc-metadata-extractor
* @ingroup		itc
* @{
*/

metadata_extractor_h g_hMetadataExtractorHandle;
bool g_bIsValidHandle;

#define PATH_LEN					1024
#define API_NAMESPACE				"METADATA_EXTRACTOR_ITC"
#define MEDIA_VIDEO_PATH			"metadata_video.mp4"
#define MEDIA_AUDIO_PATH			"metadata_audio.mp3"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__,API_NAMESPACE,__FUNCTION__);\
	if ( !g_bIsValidHandle )\
{\
	FPRINTF("[Line : %d][%s] Precondition of metadata extractor failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

char* Metadata_ExtractorGetError(int nRet);
bool Metadata_Extractor_SetPath_Audio(void);
bool Metadata_Extractor_SetPath_Video(void);
void ReadFromFile(char *pFilePath,void **pBuffer, int *pSize);
void MetadataExtractorGetFileSize(int *pnSize);
char* Metadata_ExtractorGetEnumAttributeString(int nVal);
bool MetadataExtractorGetDataPath(char* pAppDataPath);
bool MetadataExtractorAppendToAppDataPath(char* pInputPath, char* pFinalPath);

/** @} */ //end of itc-metadata-extractor

#endif  //_ITS_METADATA_EXTRACTOR_COMMON_H_
