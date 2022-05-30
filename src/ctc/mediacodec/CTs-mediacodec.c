//
// Copyright (c) 2012-2013 Samsung Electronics Co., Ltd.
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
#include "CTs-mediacodec-common.h"

/** @addtogroup ctc-mediacodec
* @ingroup		ctc
* @{
*/

//& set: MediaCodec
bool g_bMediaCodecNotSupported = false;
bool g_bMismatch = false;

/**
* @function 		CTs_media_codec_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_media_codec_startup(void)
{
	struct stat stBuff;
	mediacodec_h stMediacodec = NULL;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}

	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Media_Codec_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bMediaCodecNotSupported = false;
	g_bMismatch = false;


	if ( !TCTCheckSystemInfoFeatureSupported(MEDIACODEC_FEATURE, API_NAMESPACE) )
	{
		if ( mediacodec_create(&stMediacodec) != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bMismatch = true;
		}
		else
		{
			g_bMediaCodecNotSupported = true;
		}
		return;
	}
}

/**
* @function 		CTs_media_codec_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_media_codec_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Media_Codec_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}


/** @addtogroup	ctc-mediacodec-testcases
* @brief 		Integration testcases for module mediacodec
* @ingroup		ctc-mediacodec
* @{
*/

//& purpose: check the supported codec for decoder/encoder.
//& type: auto
/**
* @testcase			CTc_media_codec_check_codec_p
* @since_tizen		2.3
* @author           SRID(parshant.v)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			create handler for media codec
* 					Check supported codecs using API mediacodec_set_codec
* @apicovered		mediacodec_set_codec
* @passcase			If mediacodec_set_codec return other than MEDIACODEC_ERROR_NOT_SUPPORTED_FORMAT
* @failcase			If mediacodec_set_codec returns MEDIACODEC_ERROR_NOT_SUPPORTED_FORMAT
* @precondition		NA
* @postcondition	NA
*/
int CTc_media_codec_check_codec_p(void)
{
	START_TEST;

	mediacodec_h stMediacodec = NULL;
	int nRet = mediacodec_create(&stMediacodec);
	if ( nRet != MEDIACODEC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to create mediacodec handle for decoding/encoding\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	typedef struct SupportedCodec {
		mediacodec_codec_type_e codec_type;
		mediacodec_support_type_e support_type;
	} stSupportedCodec;

	static const stSupportedCodec arSupportedCodecs[] = {
		{MEDIACODEC_H264,  MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW},
		{MEDIACODEC_H263,  MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW}
	};
	int nCodecTypeSize = sizeof(arSupportedCodecs) / sizeof(arSupportedCodecs[0]);

	int nCounter;
	for(nCounter = 0; nCounter < nCodecTypeSize; ++nCounter)
	{
		int nRetVal = mediacodec_set_codec(stMediacodec, arSupportedCodecs[nCounter].codec_type, arSupportedCodecs[nCounter].support_type);//Target API
		if ( nRetVal == MEDIACODEC_ERROR_CODEC_NOT_FOUND )
		{
			FPRINTF("[Line : %d][%s] Unsupported codec - %s for %s\\n",
				__LINE__, API_NAMESPACE, MediaCodecGetCodecName(arSupportedCodecs[nCounter].codec_type),
					MediaCodecGetCodecSupportedTypeName(arSupportedCodecs[nCounter].support_type));
			mediacodec_destroy(stMediacodec);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] Supported codec - %s for %s\\n",
				__LINE__, API_NAMESPACE, MediaCodecGetCodecName(arSupportedCodecs[nCounter].codec_type),
					MediaCodecGetCodecSupportedTypeName(arSupportedCodecs[nCounter].support_type));
		}
	}
	mediacodec_destroy(stMediacodec);
	return 0;
}

/** @} */ //end of ctc-mediacodec
/** @} */ //end of ctc-mediacodec-testcases
