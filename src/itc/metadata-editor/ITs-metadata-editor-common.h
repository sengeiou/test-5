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
#ifndef _ITS_METADATA_EDITOR_COMMON_H_
#define _ITS_METADATA_EDITOR_COMMON_H_

//Add test package related includes here

#include "tct_common.h"
#include <metadata_editor.h>
#include <app.h>

/** @addtogroup itc-metadata-editor
* @ingroup		itc
* @{
*/

metadata_editor_h 	g_hMetadataEditorHandle;
bool				g_bMetadataEditorCreation;

#define API_NAMESPACE							"METADATA_EDITOR_ITC"
#define PATH_LEN								1024
#define MEDIA_VIDEO_PATH_2						"metadata_editor_video2.MP4"
#define MEDIA_VIDEO_PATH						"metadata_editor_video.MP4"
#define MEDIA_AUDIO_PATH						"metadata_editor_audio.MP3"
#define MEDIA_PICTURE_PATH						"metadata_editor_picture.JPG"
#define MEDIA_WAV_PATH							"metadata_editor_audio.wav"
#define MEDIA_FLAC_PATH							"metadata_editor_audio.flac"
#define MEDIA_OGG_PATH							"metadata_editor_audio.ogg"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

//Add helper function declarations here

char* Metadata_EditorGetError(int nRet);
bool MetadataEditorGetDataPath(char* pAppDataPath);
bool MetadataEditorAppendToAppDataPath(char* pInputPath, char* pFinalPath);

/** @} */ //end of itc-metadata-editor

#endif  //_ITS_METADATA_EDITOR_COMMON_H_
