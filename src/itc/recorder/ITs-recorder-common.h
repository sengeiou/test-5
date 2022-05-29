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
#ifndef _ITS_RECORDER_COMMON_H_
#define _ITS_RECORDER_COMMON_H_

#include "tct_common.h"
#include <glib.h>
#include <storage.h>
#include <Elementary.h>
#include "recorder.h"
#include <sound_manager.h>

/** @addtogroup itc-recorder
*  @ingroup itc
*  @{
*/

#define MICROSECONDS_PER_SECOND		1000000
#define API_NAMESPACE				"RECORDER_ITC"
#define FILENAME					"/Recorder.file"
#define SLEEP_TIME					5
#define TIMEOUT						20000


#define CAMERA_FEATURE				"http://tizen.org/feature/camera"
#define AUDIO_RECORDING_FEATURE     "http://tizen.org/feature/media.audio_recording"
#define VIDEO_RECORDING_FEATURE     "http://tizen.org/feature/media.video_recording"

#define START_TEST {\
	FPRINTF( "\\n [Line : %d][%s] Starting test : %s\\n", __LINE__,API_NAMESPACE, __FUNCTION__);\
}

#define ITC_AUDIO_CODEC_NUM 5
#define ITC_FILE_FORMAT_NUM 7

enum {
	USER_DATA_AUDIO_CODEC,
	USER_DATA_FILE_FORMAT,
	USER_DATA_MAX
};

static bool	audiocodec_fileformat_compatibility_table[ITC_AUDIO_CODEC_NUM][ITC_FILE_FORMAT_NUM] =
{        /* 3GP MP4 AMR ADTS WAV OGG M2TS */
/*AMR*/     {1,  0,  1,  0,   0,  0,  0},
/*AAC*/     {1,  1,  0,  0,   0,  0,  1},
/*VORBIS*/  {0,  0,  0,  0,   0,  1,  0},
/*PCM*/     {0,  0,  0,  0,   1,  0,  0},
/*MP3*/     {0,  1,  0,  0,   0,  0,  1}
};

GMainLoop *g_mainloop;
char* RecorderGetState(recorder_state_e RecordState);
char* RecorderGetError(int nRet);
recorder_h g_pstRecorder;
camera_h g_pstCamera;
int g_nWidth;
int g_nHeight;
char *g_RecorderFile;
int g_nStorageId;
bool g_bStorageFound;
bool g_bMismatch;
bool g_bCamFeatureNotSupported;
bool g_bAudioRecFeatureNotSupported;
bool g_bVideoRecFeatureNotSupported;
bool g_bIsCameraFeatureSupported;
bool g_bIsAudioRecordingFeatureSupported;
bool g_bIsVideoRecordingFeatureSupported;

//Add helper function declarations here

bool CreateAudioRecorder();
bool CreateVideoRecorder();
bool DestroyRecorderHandler();
bool ReadyRecorderHandler();
void GetFileName(void);
bool RecorderSupportedFileFormatCallback(recorder_file_format_e format, void *user_data);
bool RecorderSupportedAudioEncoderCallback(recorder_audio_codec_e codec, void *user_data);
gboolean RecorderTimeoutFunction(gpointer data);
void RecorderWaitForAsync();
char* SoundManagerGetError(int nRet);
/** @} */
#endif  //_ITS_RECORDER_COMMON_H_


