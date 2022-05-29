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
#ifndef _ITS_MEDIA_VISION_COMMON_H_
#define _ITS_MEDIA_VISION_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <glib.h>
#include <mv_common.h>
#include <mv_face.h>
#include <mv_face_type.h>
#include <mv_image.h>
#include <mv_image_type.h>
#include <mv_inference.h>
#include <mv_barcode_detect.h>
#include <mv_barcode_generate.h>
#include <app.h>
#include <dirent.h>
#include <setjmp.h>
#include <app_common.h>
#include <mv_surveillance.h>
#include <image_util.h>
#include <storage.h>
#include <dlog.h>
#include <mv_barcode.h>


#include <stdio.h>
#include <string.h>

#include <system_info.h>
#include <json-glib/json-glib.h>
/** @addtogroup itc-media-vision
*  @ingroup itc
*  @{
*/

//Add test package related defines here
#define API_NAMESPACE			"MEDIA_VISION_ITC"
#define TIMEOUT_CB				15000
#define FACERECOGFEATURE		"http://tizen.org/feature/vision.face_recognition"
#define IMAGERECOGFEATURE		"http://tizen.org/feature/vision.image_recognition"

#define BARCODEDETFEATURE       "http://tizen.org/feature/vision.barcode_detection"
#define BARCODEGENFEATURE       "http://tizen.org/feature/vision.barcode_generation"
#define VISIONINFERENCEFEATURE		"http://tizen.org/feature/vision.inference"
#define VISIONINFERENCEFACEFEATURE		"http://tizen.org/feature/vision.inference.face"

#define PATHLEN					1024
#define BUFFERSIZE				1024
#define DESCRIPTION_FIELD_SIZE 	1024
#define MESSAGE_FIELD_SIZE 		7100
#define IMAGE_PATH_FIELD_SIZE	1024
#define PATHPFX					"/tmp/00.jpg"
#define PATHPFX01				"/tmp/01.jpg"
#define PATHPFX09				"/tmp/09.jpg"
#define PATHPFX05				"/tmp/05.jpg"
#define PATHPFXNEUT				"/tmp/neutral.jpg"
#define PATHPFXTREC				"test_rec_model"
#define PATHPFXSCENE			"/tmp/scene.jpg"
#define PATHPFXTAR				"/tmp/target.jpg"
#define TESTVALUE				"1000"
#define TESTSTRING				"Test"
#define MAX_EVENT_TYPE_LEN               255
#define BARCODEHEIGHT			45
#define BARCODEWIDTH			45
#define TESTBARCODE				"TestBarcode.jpg"

bool g_bforeach_event_typeCompletedCallback;
bool g_bforeach_event_result_value_nameCompletedCallback;
mv_point_s g_sPoint;

#define START_TEST_BARCODE {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bMediavisionCreation )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of media-vision failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	else if((g_bMediavisionCreation == true) && ((false == g_bIsBarcodeDetectionFeatureSupported) || (false == g_bIsBarcodeGenerationFeatureSupported)))\
	{\
		FPRINTF("[Line : %d][%s] Barcode feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
}

#define START_TEST_INFERENCE {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bMismatch )\
	{\
		FPRINTF("[Line : %d][%s]Featuer mismatch for  media-vision so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	if( g_bIsVisionInferenceFeatureSupported == false )\
	{\
		FPRINTF("[Line : %d][%s] Face Inference feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( g_bMediavisionInferenceModelCreation == false )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of media-vision failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define START_TEST_FACE {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bMismatch )\
	{\
		FPRINTF("[Line : %d][%s] mv_face_recognition_model_create and TCTCheckSystemInfoFeatureSupported returned different feature for media-vision so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	if( g_bIsFaceRecognitionFeatureSupported == false )\
	{\
		FPRINTF("[Line : %d][%s] Face recognition feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( g_bMediavisionFaceRecognitionModelCreation == false )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of media-vision failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}
#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}
#define START_TEST_IMAGE {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if( g_bIsImageRecognitionFeatureSupported == false )\
	{\
		FPRINTF("[Line : %d][%s] Image recognition feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
}
#define START_TEST_SURVEILLANCE {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if( !(g_bIsImageRecognitionFeatureSupported || g_bIsFaceRecognitionFeatureSupported) )\
	{\
		FPRINTF("[Line : %d][%s] Image ,Face recognition feature is not supported and api also returned not supported so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#define CHECK_HANDLE_NONE(Handle, API) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		return;\
	}\
}

#define PRINT_RESULTNONE_CLEANUP(eCompare, eRetVal, API, Error, FreeResource) {\
	if ( eRetVal == eCompare )\
	{\
		if ( DEBUG )\
		{\
			FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
		}\
	}\
	else \
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
		FreeResource;\
		return;\
	}\
}

#define PRINT_RESULTNONE(eCompare, eRetVal, API, Error) {\
	if ( eRetVal == eCompare )\
	{\
		if ( DEBUG )\
		{\
			FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
		}\
	}\
	else \
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
		return;\
	}\
}

//Add CallBack function declarations here
bool MvSupportedAttributeCallBack(mv_config_attribute_type_e attribute_type, const char *attribute_name, void *user_data);

//Add test package related global variables here
static const char *g_pszResPath = NULL;
static const char *g_pszDataPath = NULL;
static const char *g_pszCconfFile = "media-vision-barcodes.json";
bool g_bMediavisionCreation;
bool g_CallBackHit;
bool g_bMediavisionFaceRecognitionModelCreation;
int g_nTimeoutId;
GMainLoop *g_pMainLoop;
mv_face_recognition_model_h g_hRecognitionModel;
mv_source_h g_hMvSource;
bool g_bIsFaceRecognitionFeatureSupported;
bool g_bIsImageRecognitionFeatureSupported;
bool g_bMismatch;
void *g_pBufferData;
mv_engine_config_h g_hMvEngineConfig;
//Add helper function declarations here
char* MediaVisionGetError(int nRet);
gboolean TimeoutFunction(gpointer data);
void IterateGmainLoop(void);
void QuitGmainLoop(void);
bool MediaVisionGetDataPath(char* pAppDataPath);
bool MediaVisionAppendToAppDataPath(const char* pInputPath, char* pFinalPath);

bool g_bIsBarcodeGenerationFeatureSupported;
bool g_bIsBarcodeDetectionFeatureSupported;
bool checkModelFile( const char *fSrcPath, const char *fDstPath);
int image_load(const char *file_path, mv_source_h source);

bool g_bIsDetectionFeatureSupported;
bool g_bIsGenerationFeatureSupported;
bool g_bMediavisionInferenceModelCreation;
bool g_bIsVisionInferenceFeatureSupported;
media_packet_h g_hMediaPacket;
media_format_h g_hMediaFormat;
tbm_surface_h g_hTBMSurface;
char g_szDoubleAttribute[PATHLEN];
char g_szIntAttribute[PATHLEN];
char g_szBoolAttribute[PATHLEN];
char g_szStringAttribute[PATHLEN];
char g_szArrayStringAttribute[PATHLEN];
int nCount;
mv_rectangle_s g_sRectangle;
mv_point_s g_sPoint;
char g_szBarcodePath[PATHLEN];

bool CreateMediaFormat(void);
bool CreateMediaPacket(void);
bool DestroyMediaPacket(void);
bool CreateFilledMediaSource(void);
char* ImageUtilGetError(int nRet);
/** @} */
#endif  //_ITS_MEDIA_VISION_COMMON_H_
