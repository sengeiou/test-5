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

//& set: MediaCodec

mediacodec_h g_mediacodec = NULL;
bool g_bCallbackResult;

struct stMediaCodec {
	mediacodec_codec_type_e codec_id;
	int flags;
};

struct stMediaCodec g_arSupportedCodecs[100];
int g_nSupportedCodecCount = 0;
bool g_bMediaCodecNotSupported = false;
bool g_bMismatch = false;


/**
* @function			mediacodec_get_output_cb_p
* @description		Called when the output buffer, It will be invoked when mediacodec has output buffer
* @parameter[IN]	media_packet_h, void *
* @return			NA
*/
static void mediacodec_get_output_cb_p(media_packet_h pkt, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside Callaback : mediacodec_get_output_cb_p\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = false;

	//Target API
	int nRet = mediacodec_get_output(g_mediacodec, &hOutputBuff, 0);
	if ( nRet != MEDIACODEC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] mediacodec_get_output_cb_p callback returns error = %s\\n", __LINE__, API_NAMESPACE, MediaCodecGetError(nRet));
	}
	else
	{
		g_bCallbackResult = true;
	}

	if ( hOutputBuff != NULL )
	{
		media_packet_destroy(hOutputBuff);
		hOutputBuff = NULL;
	}
	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function			mediacodec_error_cb_p
* @description		Called when the error has occurred, It will be invoked when the error has occurred
* @parameter[IN]	mediacodec_error_e, void *
* @return			NA
*/
static void mediacodec_error_cb_p(mediacodec_error_e error, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside Callaback : mediacodec_error_cb_p; error = %d\\n", __LINE__, API_NAMESPACE, (int)error);
	g_bCallbackResult = true;
	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function			mediacodec_eos_cb_p
* @description		Called when there is no data to decode/encode, It will be invoked when the eos event has occurred
* @parameter[IN]	void *
* @return			NA
*/
static void mediacodec_eos_cb_p(void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside Callaback : mediacodec_eos_cb_p\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function			mediacodec_input_buffer_used_cb_p
* @description		Called when the input buffer(pkt) used, It will be invoked when mediacodec has used input buffer
* @parameter[IN]	media_packet_h, void *
* @return			NA
*/
static void mediacodec_input_buffer_used_cb_p(media_packet_h pkt, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside Callaback : mediacodec_input_buffer_used_cb_p\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( pkt != NULL )
	{
		media_packet_destroy(pkt);
	}
	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function			mediacodec_buffer_status_cb_p
* @description
* @parameter[IN]
* @return			NA
*/
static void mediacodec_buffer_status_cb_p(mediacodec_status_e status, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside Callaback : mediacodec_buffer_status_cb_p\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function			mediacodec_output_buffer_available_cb_p
* @description		Called when the input buffer(pkt) used, It will be invoked when mediacodec has used input buffer
* @parameter[IN]	media_packet_h, void *
* @return			NA
*/
static void mediacodec_output_buffer_available_cb_p(media_packet_h pkt, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside Callaback : mediacodec_output_buffer_available_cb_p\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	media_packet_h out_pkt = NULL;

	mediacodec_get_output(user_data, &out_pkt, 0);

	if ( out_pkt != NULL )
	{
		media_packet_destroy(out_pkt);
	}
	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function			mediacodec_supported_codec_cb_p
* @description		Called the codec supported, It will be invoked when mediacodec type supported
* @parameter[IN]	mediacodec_codec_type_e, void *
* @return			NA
*/
static bool mediacodec_supported_codec_cb_p(mediacodec_codec_type_e codec_type, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside mediacodec_supported_codec_cb_p\\n", __LINE__, API_NAMESPACE);
	int nType = 0;
	bool bEncoder = true;

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec_type, bEncoder, &nType);
	if ( nRet == MEDIACODEC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] mediacodec_get_supported_type for encoder\\n", __LINE__, API_NAMESPACE);
		if ( nType == MEDIACODEC_SUPPORT_TYPE_HW )
		{
			g_arSupportedCodecs[g_nSupportedCodecCount].codec_id = codec_type;
			g_arSupportedCodecs[g_nSupportedCodecCount].flags = MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_HW;
			g_nSupportedCodecCount++;
			g_bCallbackResult = true;
		}
		else if ( nType == MEDIACODEC_SUPPORT_TYPE_SW )
		{
			g_arSupportedCodecs[g_nSupportedCodecCount].codec_id = codec_type;
			g_arSupportedCodecs[g_nSupportedCodecCount].flags = MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW;
			g_nSupportedCodecCount++;
			g_bCallbackResult = true;
		}
	}

	nType = 0;
	bEncoder = false; // decoder

	nRet = mediacodec_get_supported_type(g_mediacodec, codec_type, bEncoder, &nType);
	if ( nRet == MEDIACODEC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] mediacodec_get_supported_type successful for decoder \\n", __LINE__, API_NAMESPACE);
		if ( nType == MEDIACODEC_SUPPORT_TYPE_HW )
		{
			g_arSupportedCodecs[g_nSupportedCodecCount].codec_id = codec_type;
			g_arSupportedCodecs[g_nSupportedCodecCount].flags = MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_HW;
			g_nSupportedCodecCount++;
			g_bCallbackResult = true;
		}
		else if ( nType == MEDIACODEC_SUPPORT_TYPE_SW )
		{
			g_arSupportedCodecs[g_nSupportedCodecCount].codec_id = codec_type;
			g_arSupportedCodecs[g_nSupportedCodecCount].flags = MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW;
			g_nSupportedCodecCount++;
			g_bCallbackResult = true;
		}
	}

	return true;
}

/**
* @function 		ITs_media_codec_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_media_codec_startup(void)
{
	ecore_main_loop_glib_integrate();

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Media_Codec_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsMediaCodecValidHandle = true;
	g_bMediaCodecNotSupported = false;
	g_bMismatch = false;

	if ( !TCTCheckSystemInfoFeatureSupported(MEDIACODEC_FEATURE, API_NAMESPACE) )
	{
		if ( mediacodec_create(&g_mediacodec) != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bMismatch = true;
		}
		else
		{
			g_bMediaCodecNotSupported = true;
		}
		return;
	}

	int nRet = mediacodec_create(&g_mediacodec);
	if ( nRet != MEDIACODEC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to create mediacodec handle for decoding/encoding, error returned = %s\\n", __LINE__, API_NAMESPACE, MediaCodecGetError(nRet));
		g_bIsMediaCodecValidHandle = false;
	}

	if ( !g_mediacodec )
	{
		FPRINTF("[Line : %d][%s] mediacodec_create return NULL, error returned = %s\\n", __LINE__, API_NAMESPACE, MediaCodecGetError(nRet));
		g_bIsMediaCodecValidHandle = false;
	}

	nRet = media_format_create(&hFormat);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_create API failed = %s \\n", __LINE__, API_NAMESPACE, MediaCodecGetError(nRet));
		g_bIsMediaCodecValidHandle = false;
		return;
	}
	if ( !hFormat )
	{
		FPRINTF("[Line : %d][%s] media_format_create return NULL\\n", __LINE__, API_NAMESPACE);
		g_bIsMediaCodecValidHandle = false;
	}

	nRet = media_format_set_audio_mime(hFormat, MEDIA_FORMAT_PCM);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_audio_mime API failed = %s\\n", __LINE__, API_NAMESPACE, MediaCodecGetError(nRet));
		return;
	}
	nRet = media_format_set_audio_samplerate(hFormat, 48000);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_audio_samplerate API failed = %s\\n", __LINE__, API_NAMESPACE, MediaCodecGetError(nRet));
		return;
	}
	nRet = media_format_set_audio_channel(hFormat, 2);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_audio_channel API failed = %s \\n", __LINE__, API_NAMESPACE, MediaCodecGetError(nRet));
		return;
	}
	nRet = media_format_set_audio_bit(hFormat, 16);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_audio_bit API failed = %s\\n", __LINE__, API_NAMESPACE, MediaCodecGetError(nRet));
		return;
	}
	nRet = media_format_set_audio_avg_bps(hFormat,128000);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_audio_avg_bps API failed = %s\\n", __LINE__, API_NAMESPACE, MediaCodecGetError(nRet));
		return;
	}
	nRet = media_packet_create_alloc(hFormat, NULL, NULL, &hInputBuff);
	if (nRet != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_audio_alloc API failed = %s\\n", __LINE__, API_NAMESPACE, MediaCodecGetError(nRet));
		return;
	}
}

/**
* @function 		ITs_media_codec_cleanup
* @description	 	Called after each test, destroys handle
* @parameter		NA
* @return 			NA
*/
void ITs_media_codec_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Media_Codec_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_bIsMediaCodecValidHandle )
	{
		mediacodec_destroy(g_mediacodec);
	}

	if ( hInputBuff != NULL )
	{
		media_packet_destroy(hInputBuff);
	}
	if ( hFormat != NULL)
	{
		media_format_unref(hFormat);
	}

	sleep(SLEEP_TIME);
	return;
}

/** @addtogroup	itc-mediacodec-testcases
* @brief 		Integration testcases for module mediacodec
* @ingroup		itc-mediacodec
* @{
*/

//& purpose: Create and destroy a mediacodec handle for decoding/encoding
//& type: auto
/**
* @testcase 				ITc_mediacodec_create_destroy_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Create and destroy a mediacodec handle for decoding/encoding
* @scenario					Create a mediacodec handle for decoding/encoding\n
*							Destroy the mediacodec handle
* @apicovered				mediacodec_create, mediacodec_destroy
* @passcase					If mediacodec_create and mediacodec_destroy is successful
* @failcase					If mediacodec_create or mediacodec_destroy fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_create_destroy_p(void)
{
	START_TEST;
	mediacodec_h mediacodec = NULL;

	//Target API
	int nRet = mediacodec_create(&mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_create", MediaCodecGetError(nRet));
	CHECK_HANDLE(mediacodec, "mediacodec_create");

	//Target API
	nRet = mediacodec_destroy(mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_destroy", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Prepares and unprepares a mediacodec for encoding/decoding
//& type: auto
/**
* @testcase 				ITc_mediacodec_prepare_unprepare_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Prepares and unprepares a mediacodec for encoding/decoding
* @scenario					Prepare a mediacodec for encoding/decoding\n
*							Unprepare the mediacodec
* @apicovered				mediacodec_set_codec, mediacodec_set_aenc_info, mediacodec_prepare, mediacodec_unprepare
* @passcase					If mediacodec_prepare and mediacodec_unprepare is successful
* @failcase					If mediacodec_prepare or mediacodec_unprepare fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_prepare_unprepare_p(void)
{
	START_TEST;

	//precondition
	mediacodec_codec_type_e codec = MEDIACODEC_AAC;
	int flags;
	bool bEncoder = true; // checking encoder type
	int nType = 0;
	int i = 0;
	int bit_depth[] = { 16, 32 };

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ( nType != MEDIACODEC_SUPPORT_TYPE_SW )
	{
		FPRINTF("[Line : %d][%s] Audio encoder MEDIACODEC_AAC is not supported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Setting flag after validation
	flags = MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW;

	nRet = mediacodec_set_codec(g_mediacodec, codec, flags);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));

	for (i = 0; i < 2; i++) {
		nRet = mediacodec_set_aenc_info(g_mediacodec, 48000, 2, bit_depth[i], 128000);
		if (nRet == MEDIACODEC_ERROR_NONE)
			break;
	}
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_aenc_info", MediaCodecGetError(nRet));

	//Target API
	nRet = mediacodec_prepare(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_prepare", MediaCodecGetError(nRet));

	//Target API
	nRet = mediacodec_unprepare(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unprepare", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Sets the default info for the video encoder
//& type: auto
/**
* @testcase 				ITc_mediacodec_set_venc_info_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets the default info for the video encoder
* @scenario					Set the default info for the video encoder
* @apicovered				mediacodec_set_codec, mediacodec_set_venc_info
* @passcase					If mediacodec_set_venc_info is successful
* @failcase					If mediacodec_set_venc_info fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_set_venc_info_p(void)
{
	START_TEST;

	//precondition
	mediacodec_codec_type_e codec = MEDIACODEC_H264;
	int flags;
	bool bEncoder = true; // checking encoder type
	int nType = 0;

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ((nType & MEDIACODEC_SUPPORT_TYPE_SW) != MEDIACODEC_SUPPORT_TYPE_SW)
	{
		FPRINTF("[Line : %d][%s] Video encoder MEDIACODEC_H264 is not supported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Setting flag after validation
	flags = MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW;

	nRet = mediacodec_set_codec(g_mediacodec, codec, flags);
	if ( nRet != MEDIACODEC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to set mediacodec for MEDIACODEC_H264, error returned = %s\\n", __LINE__, API_NAMESPACE, MediaCodecGetError(nRet));
		nRet = mediacodec_set_codec(g_mediacodec, MEDIACODEC_H263, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
		PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));
		FPRINTF("[Line : %d][%s] MEDIACODEC_H263 codec set successfully\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] MEDIACODEC_H264 codec set successfully\\n", __LINE__, API_NAMESPACE);
	}

	//Target API
	nRet = mediacodec_set_venc_info(g_mediacodec, 100, 100, 32, 0);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_venc_info", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Sets the default info for the audio decoder
//& type: auto
/**
* @testcase 				ITc_mediacodec_set_adec_info_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets the default info for the audio decoder
* @scenario					Set the default info for the audio decoder
* @apicovered				mediacodec_set_adec_info, mediacodec_set_codec
* @passcase					If mediacodec_set_adec_info is successful
* @failcase					If mediacodec_set_adec_info fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_set_adec_info_p(void)
{
	START_TEST;

	//precondition
	mediacodec_codec_type_e codec = MEDIACODEC_AAC;
	int flags;
	bool bEncoder = false; // checking encoder type
	int nType = 0;
	int i = 0;
	int bit_depth[] = { 16, 32 };

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ( nType != MEDIACODEC_SUPPORT_TYPE_SW )
	{
		FPRINTF("[Line : %d][%s] Audio decoder MEDIACODEC_AAC is not supported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Setting flag after validation
	flags = MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW;

	nRet = mediacodec_set_codec(g_mediacodec, codec, flags);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));

	//Target API
	for (i = 0; i < 2; i++) {
		nRet = mediacodec_set_adec_info(g_mediacodec, 48000, 2, bit_depth[i]);
		if (nRet == MEDIACODEC_ERROR_NONE)
			break;
	}
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_adec_info", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Sets the default info for the audio encoder
//& type: auto
/**
* @testcase 				ITc_mediacodec_set_aenc_info_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets the default info for the audio encoder
* @scenario					Set the default info for the audio encoder
* @apicovered				mediacodec_set_aenc_info, mediacodec_set_codec
* @passcase					If mediacodec_set_aenc_info is successful
* @failcase					If mediacodec_set_aenc_info fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_set_aenc_info_p(void)
{
	START_TEST;

	//precondition
	mediacodec_codec_type_e codec = MEDIACODEC_AAC;
	int flags;
	bool bEncoder = true; // checking encoder type
	int nType = 0;
	int i = 0;
	int bit_depth[] = { 16, 32 };

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ( nType != MEDIACODEC_SUPPORT_TYPE_SW )
	{
		FPRINTF("[Line : %d][%s] Audio encoder MEDIACODEC_AAC is not supported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Setting flag after validation
	flags = MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW;

	nRet = mediacodec_set_codec(g_mediacodec, codec, flags);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));

	//Target API
	for (i = 0; i < 2; i++) {
		nRet = mediacodec_set_aenc_info(g_mediacodec, 48000, 2, bit_depth[i], 128000);
		if (nRet == MEDIACODEC_ERROR_NONE)
			break;
	}
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_aenc_info", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Sets the default info for the video decoder
//& type: auto
/**
* @testcase 				ITc_mediacodec_set_vdec_info_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets the default info for the video decoder
* @scenario					Set the default info for the video decoder
* @apicovered				mediacodec_set_vdec_info, mediacodec_set_codec
* @passcase					If mediacodec_set_vdec_info is successful
* @failcase					If mediacodec_set_vdec_info fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_set_vdec_info_p(void)
{
	START_TEST;

	//precondition
	mediacodec_codec_type_e codec = MEDIACODEC_H264;
	int flags;
	bool bEncoder = false; // checking encoder type
	int nType = 0;

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ((nType & MEDIACODEC_SUPPORT_TYPE_SW) != MEDIACODEC_SUPPORT_TYPE_SW)
	{
		FPRINTF("[Line : %d][%s] Video encoder MEDIACODEC_H264 is not supported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Setting flag after validation
	flags = MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW;

	nRet = mediacodec_set_codec(g_mediacodec, codec, flags);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));

	//Target API
	nRet = mediacodec_set_vdec_info(g_mediacodec, 100, 100);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_vdec_info", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Sets the codec type and decoder/encoder
//& type: auto
/**
* @testcase 				ITc_mediacodec_set_codec_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets the codec type and decoder/encoder
* @scenario					Set the codec type and decoder/encoder
* @apicovered				mediacodec_set_codec, mediacodec_foreach_supported_codec
* @passcase					If mediacodec_set_codec is successful
* @failcase					If mediacodec_set_codec fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_set_codec_p(void)
{
	START_TEST;

	g_bCallbackResult = false;

	int nRet = mediacodec_foreach_supported_codec(g_mediacodec, mediacodec_supported_codec_cb_p, NULL);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_foreach_supported_codec", MediaCodecGetError(nRet));

	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Sync callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nSupportedCodecCounter = 0;
	for ( nSupportedCodecCounter = 0; nSupportedCodecCounter < g_nSupportedCodecCount; ++nSupportedCodecCounter )
	{
		//Target API
		nRet = mediacodec_set_codec(g_mediacodec, g_arSupportedCodecs[nSupportedCodecCounter].codec_id, g_arSupportedCodecs[nSupportedCodecCounter].flags);
		PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));
	}

	return 0;
}

//& purpose: Decodes/Encodes a single picture and then transfer the output buffers to the queue
//& type: auto
/**
* @testcase 				ITc_mediacodec_process_input_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Decodes/Encodes a single picture and then transfer the output buffers to the queue
* @scenario					Decode/Encode a single picture\n
*							Transfer the output buffers to the queue
* @apicovered				mediacodec_set_codec, mediacodec_set_aenc_info, mediacodec_prepare, mediacodec_unprepare, mediacodec_process_input
* @passcase					If mediacodec_process_input is successful
* @failcase					If mediacodec_process_input fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_process_input_p(void)
{
	START_TEST;

	mediacodec_codec_type_e codec = MEDIACODEC_AAC;
	int flags;
	bool bEncoder = true; // checking encoder type
	int nType = 0;
	int i = 0;
	int bit_depth[] = { 16, 32 };

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ( nType != MEDIACODEC_SUPPORT_TYPE_SW )
	{
		FPRINTF("[Line : %d][%s] Audio encoder MEDIACODEC_AAC is not supported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Setting flag after validation
	flags = MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW;

	nRet = mediacodec_set_codec(g_mediacodec, codec, flags);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));

	for (i = 0; i < 2; i++) {
		nRet = mediacodec_set_aenc_info(g_mediacodec, 48000, 2, bit_depth[i], 128000);
		if (nRet == MEDIACODEC_ERROR_NONE)
			break;
	}
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_aenc_info", MediaCodecGetError(nRet));

	nRet = mediacodec_prepare(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_prepare", MediaCodecGetError(nRet));

	void *szData = NULL;
	media_packet_get_buffer_data_ptr(hInputBuff, &szData);
	unsigned int unSize = GetDataFromFile(szData);
	media_packet_set_buffer_size(hInputBuff, unSize);

	//Target API
	nRet = mediacodec_process_input(g_mediacodec, hInputBuff, 1000);
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_process_input", MediaCodecGetError(nRet), mediacodec_unprepare(g_mediacodec));

	nRet = mediacodec_unprepare(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unprepare", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Gets the output from the queue
//& type: auto
/**
* @testcase 				ITc_mediacodec_get_output_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Gets the output from the queue
* @scenario					Get the output from the queue
* @apicovered				mediacodec_set_codec, mediacodec_set_aenc_info, mediacodec_set_output_buffer_available_cb, mediacodec_prepare\n
*							mediacodec_get_output, mediacodec_process_input, mediacodec_unprepare, mediacodec_unset_output_buffer_available_cb
* @passcase					If mediacodec_get_output is successful
* @failcase					If mediacodec_get_output fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_get_output_p(void)
{
	START_TEST;

	mediacodec_codec_type_e codec = MEDIACODEC_AAC;
	int flags;
	bool bEncoder = true; // checking encoder type
	int nType = 0, i = 0;
	int bit_depth[] = { 16, 32 };

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ( nType != MEDIACODEC_SUPPORT_TYPE_SW )
	{
		FPRINTF("[Line : %d][%s] Audio encoder MEDIACODEC_AAC is not supported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Setting flag after validation
	flags = MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW;

	nRet = mediacodec_set_codec(g_mediacodec, codec, flags);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));

	for (i = 0; i < 2; i++) {
		nRet = mediacodec_set_aenc_info(g_mediacodec, 48000, 2, bit_depth[i], 128000);
		if (nRet == MEDIACODEC_ERROR_NONE)
			break;
	}
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_aenc_info", MediaCodecGetError(nRet));

	nRet = mediacodec_set_output_buffer_available_cb(g_mediacodec, mediacodec_get_output_cb_p, NULL);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_output_buffer_available_cb", MediaCodecGetError(nRet));

	nRet = mediacodec_prepare(g_mediacodec);
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_prepare", MediaCodecGetError(nRet), mediacodec_unset_output_buffer_available_cb(g_mediacodec));

	g_bCallbackResult = false;

	for ( i = 0; i < FRAME_COUNT; i++ )
	{
		media_packet_h hInputBuffNew = NULL;
		media_packet_create_alloc(hFormat, NULL, NULL, &hInputBuffNew);
		void *szData = NULL;
		media_packet_get_buffer_data_ptr(hInputBuffNew, &szData);
		unsigned int unSize = GetDataFromFile(szData);
		media_packet_set_buffer_size(hInputBuffNew, unSize);
		nRet = mediacodec_process_input(g_mediacodec, hInputBuffNew, 0);
		PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_process_input", MediaCodecGetError(nRet), mediacodec_unprepare(g_mediacodec);mediacodec_unset_output_buffer_available_cb(g_mediacodec));
	}

	RUN_POLLING_LOOP("mediacodec");

	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Async callback not invoked\\n", __LINE__, API_NAMESPACE);
		mediacodec_unprepare(g_mediacodec);
		mediacodec_unset_output_buffer_available_cb(g_mediacodec);
		return 1;
	}

	nRet = mediacodec_unprepare(g_mediacodec);
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unprepare", MediaCodecGetError(nRet), mediacodec_unset_output_buffer_available_cb(g_mediacodec));

	return 0;
}

//& purpose: set and unset error callback the media codec for process, asynchronously
//& type: auto
/**
* @testcase 				ITc_mediacodec_set_unset_error_cb_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets and unsets error callback the media codec for process, asynchronously
* @scenario					Set error callback the media codec for process, asynchronously\n
*							Unset error callback the media codec for process, asynchronously
* @apicovered				mediacodec_set_error_cb, mediacodec_unset_error_cb
* @passcase					If mediacodec_set_error_cb and mediacodec_unset_error_cb is successful
* @failcase					If mediacodec_set_error_cb or mediacodec_unset_error_cb fails
* @precondition				mediacodec_set_error_cb should be called before mediacodec_preare
* @postcondition			mediacodec_error_cb will be invoked
*/
int ITc_mediacodec_set_unset_error_cb_p(void)
{
	START_TEST;

	//Target API
	int nRet = mediacodec_set_error_cb(g_mediacodec, mediacodec_error_cb_p, NULL);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_error_cb", MediaCodecGetError(nRet));

	//Target API
	nRet = mediacodec_unset_error_cb(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unset_error_cb", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: set and unset eos callback the media codec for process, asynchronously
//& type: auto
/**
* @testcase 				ITc_mediacodec_set_eos_cb_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets and unsets error callback the media codec for process, asynchronously
* @scenario					Set error callback the media codec for process, asynchronously\n
*							Unset error callback the media codec for process, asynchronously
* @apicovered				mediacodec_set_eos_cb, mediacodec_unset_eos_cb
* @passcase					If mediacodec_set_eos_cb and mediacodec_unset_eos_cb is successful
* @failcase					If mediacodec_set_eos_cb or mediacodec_unset_eos_cb fails
* @precondition				mediacodec_set_eos_cb should be called before mediacodec_preare
* @postcondition			mediacodec_eos_cb will be invoked
*/
int ITc_mediacodec_set_eos_cb_p(void)
{
	START_TEST;

	//Target API
	int nRet = mediacodec_set_eos_cb(g_mediacodec, mediacodec_eos_cb_p, NULL);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_eos_cb", MediaCodecGetError(nRet));

	//Target API
	nRet = mediacodec_unset_eos_cb(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unset_eos_cb", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: set and unset empty buffer callback the media codec for process, asynchronously
//& type: auto
/**
* @testcase 				ITc_mediacodec_set_unset_input_buffer_used_cb_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets and unsets empty buffer callback the media codec for process, asynchronously
* @scenario					Set empty buffer callback the media codec for process, asynchronously\n
*							Unset empty buffer callback the media codec for process, asynchronously
* @apicovered				mediacodec_set_codec, mediacodec_set_aenc_info, mediacodec_set_input_buffer_used_cb\n
*							mediacodec_prepare, mediacodec_process_input, mediacodec_unprepare, mediacodec_unset_input_buffer_used_cb
* @passcase					If mediacodec_set_input_buffer_used_cb and mediacodec_unset_input_buffer_used_cb is successful
* @failcase					If mediacodec_set_input_buffer_used_cb or mediacodec_unset_input_buffer_used_cb fails
* @precondition				mediacodec_set_input_buffer_used_cb should be called before mediacodec_preare
* @postcondition			mediacodec_input_buffer_used_cb will be invoked
*/
int ITc_mediacodec_set_unset_input_buffer_used_cb_p(void)
{
	START_TEST;

	mediacodec_codec_type_e codec = MEDIACODEC_AAC;
	int flags;
	bool bEncoder = true; // checking encoder type
	int nType = 0, i = 0;
	int bit_depth[] = { 16, 32 };

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ( nType != MEDIACODEC_SUPPORT_TYPE_SW )
	{
		FPRINTF("[Line : %d][%s] Audio encoder MEDIACODEC_AAC is not supported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Setting flag after validation
	flags = MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW;

	nRet = mediacodec_set_codec(g_mediacodec, codec, flags);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));

	for (i = 0; i < 2; i++) {
		nRet = mediacodec_set_aenc_info(g_mediacodec, 48000, 2, bit_depth[i], 128000);
		if (nRet == MEDIACODEC_ERROR_NONE)
			break;
	}
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_aenc_info", MediaCodecGetError(nRet));

	//Target API
	nRet = mediacodec_set_input_buffer_used_cb(g_mediacodec, mediacodec_input_buffer_used_cb_p, NULL);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_input_buffer_used_cb", MediaCodecGetError(nRet));

	nRet = mediacodec_prepare(g_mediacodec);
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_prepare", MediaCodecGetError(nRet), mediacodec_unset_input_buffer_used_cb(g_mediacodec));

	g_bCallbackResult = false;

	for ( i = 0; i < FRAME_COUNT; i++ )
	{
		media_packet_h hInputBuffNew = NULL;
		media_packet_create_alloc(hFormat, NULL, NULL, &hInputBuffNew);
		void *szData = NULL;
		media_packet_get_buffer_data_ptr(hInputBuffNew, &szData);
		unsigned int unSize = GetDataFromFile(szData);
		media_packet_set_buffer_size(hInputBuffNew, unSize);
		nRet = mediacodec_process_input(g_mediacodec, hInputBuffNew, 0);
		PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_process_input", MediaCodecGetError(nRet), mediacodec_unprepare(g_mediacodec);mediacodec_unset_input_buffer_used_cb(g_mediacodec));
	}

	RUN_POLLING_LOOP("mediacodec");

	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Async callback not invoked\\n", __LINE__, API_NAMESPACE);
		mediacodec_unprepare(g_mediacodec);
		mediacodec_unset_input_buffer_used_cb(g_mediacodec);
		return 1;
	}

	nRet = mediacodec_unprepare(g_mediacodec);
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unprepare", MediaCodecGetError(nRet), mediacodec_unset_input_buffer_used_cb(g_mediacodec));

	//Target API
	nRet = mediacodec_unset_input_buffer_used_cb(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unset_input_buffer_used_cb", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Set and unset output buffer available callback for the media codec for process, asynchronously
//& type: auto
/**
* @testcase 				ITc_mediacodec_set_unset_output_buffer_available_cb_p
* @since_tizen				2.3
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets and unsets output buffer available callback for the media codec for process, asynchronously
* @scenario					Prepares a mediacodec for encoding/decoding\n
*							Set output buffer available callback for the media codec for process, asynchronously\n
*							Unset output buffer available callback for the media codec for process, asynchronously
* @apicovered				mediacodec_set_codec, mediacodec_set_aenc_info, mediacodec_set_output_buffer_available_cb\n
*							mediacodec_prepare, mediacodec_process_input, mediacodec_unprepare, mediacodec_unset_output_buffer_available_cb*
* @passcase					If mediacodec_set_output_buffer_available_cb and mediacodec_unset_output_buffer_available_cb is successful
* @failcase					If mediacodec_set_output_buffer_available_cb or mediacodec_unset_output_buffer_available_cb fails
* @precondition				mediacodec_set_fill_buffer_cb should be called before mediacodec_preare
* @postcondition			mediacodec_output_buffer_available_cb will be invoked
*/
int ITc_mediacodec_set_unset_output_buffer_available_cb_p(void)
{
	START_TEST;

	mediacodec_codec_type_e codec = MEDIACODEC_AAC;
	int flags;
	bool bEncoder = true; // checking encoder type
	int nType = 0, i = 0;
	int bit_depth[] = { 16, 32 };

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ( nType != MEDIACODEC_SUPPORT_TYPE_SW )
	{
		FPRINTF("[Line : %d][%s] Audio encoder MEDIACODEC_AAC is not supported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Setting flag after validation
	flags = MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW;

	nRet = mediacodec_set_codec(g_mediacodec, codec, flags);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));

	for (i = 0; i < 2; i++) {
		nRet = mediacodec_set_aenc_info(g_mediacodec, 48000, 2, bit_depth[i], 128000);
		if (nRet == MEDIACODEC_ERROR_NONE)
			break;
	}
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_aenc_info", MediaCodecGetError(nRet));

	//Target API
	nRet = mediacodec_set_output_buffer_available_cb(g_mediacodec, mediacodec_output_buffer_available_cb_p, g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_output_buffer_available_cb", MediaCodecGetError(nRet));

	nRet = mediacodec_prepare(g_mediacodec);
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_prepare", MediaCodecGetError(nRet), mediacodec_unset_output_buffer_available_cb(g_mediacodec));

	g_bCallbackResult = false;

	for ( i = 0; i < FRAME_COUNT; i++ )
	{
		media_packet_h hInputBuffNew = NULL;
		media_packet_create_alloc(hFormat, NULL, NULL, &hInputBuffNew);
		void *szData = NULL;
		media_packet_get_buffer_data_ptr(hInputBuffNew, &szData);
		unsigned int unSize = GetDataFromFile(szData);
		media_packet_set_buffer_size(hInputBuffNew, unSize);
		nRet = mediacodec_process_input(g_mediacodec, hInputBuffNew, 0);
		PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_process_input", MediaCodecGetError(nRet), mediacodec_unprepare(g_mediacodec);mediacodec_unset_output_buffer_available_cb(g_mediacodec));
	}

	RUN_POLLING_LOOP("mediacodec");

	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Async callback not invoked\\n", __LINE__, API_NAMESPACE);
		mediacodec_unprepare(g_mediacodec);
		mediacodec_unset_output_buffer_available_cb(g_mediacodec);
		return 1;
	}

	nRet = mediacodec_unprepare(g_mediacodec);
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unprepare", MediaCodecGetError(nRet), mediacodec_unset_output_buffer_available_cb(g_mediacodec));

	//Target API
	nRet = mediacodec_unset_output_buffer_available_cb(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unset_output_buffer_available_cb", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Gets the output from the queue
//& type: auto
/**
* @testcase 				ITc_mediacodec_flush_buffers_p
* @since_tizen				2.4
* @owner					SRID(pushpa.singh)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Gets the output from the queue
* @scenario					Get the output from the queue
* @apicovered				mediacodec_set_codec, mediacodec_flush_buffers, mediacodec_set_aenc_info
* @passcase					If mediacodec_flush_buffers is successful
* @failcase					If mediacodec_flush_buffers fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_flush_buffers_p(void)
{
	START_TEST;

	mediacodec_codec_type_e codec = MEDIACODEC_AAC;
	int flags;
	bool bEncoder = true; // checking encoder type
	int nType = 0;
	int bit_depth[] = { 16, 32 };
	int i;

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ( nType != MEDIACODEC_SUPPORT_TYPE_SW )
	{
		FPRINTF("[Line : %d][%s] Audio encoder MEDIACODEC_AAC is not supported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Setting flag after validation
	flags = MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW;

	nRet = mediacodec_set_codec(g_mediacodec, codec, flags);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));

	for (i = 0; i < 2; i++) {
		nRet = mediacodec_set_aenc_info(g_mediacodec, 48000, 2, bit_depth[i], 128000);
		if (nRet == MEDIACODEC_ERROR_NONE)
			break;
	}
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_aenc_info", MediaCodecGetError(nRet));

	//Target API
	nRet = mediacodec_prepare(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_prepare", MediaCodecGetError(nRet));

	//Target API
	nRet = mediacodec_flush_buffers(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_flush_buffers", MediaCodecGetError(nRet));

	//Target API
	nRet = mediacodec_unprepare(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unprepare", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Retrieves all supported codecs for the device
//& type: auto
/**
* @testcase 				ITc_mediacodec_foreach_supported_codec_p
* @since_tizen				2.4
* @owner					SRID(pushpa.singh)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Retrieves all supported codecs for the device
* @scenario					Retrieve all supported codecs for the device
* @apicovered				mediacodec_foreach_supported_codec
* @passcase					If mediacodec_foreach_supported_codec is successful
* @failcase					If mediacodec_foreach_supported_codec fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_foreach_supported_codec_p(void)
{
	START_TEST;

	g_bCallbackResult = false;

	//Target API
	int nRet = mediacodec_foreach_supported_codec(g_mediacodec, mediacodec_supported_codec_cb_p, NULL);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_foreach_supported_codec", MediaCodecGetError(nRet));

	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Sync callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the supported media codec type
//& type: auto
/**
* @testcase 				ITc_mediacodec_get_supported_type_p
* @since_tizen				2.4
* @owner					SRID(pushpa.singh)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Checks supported media codec type
* @scenario					check supported media codec type
* @apicovered				NA
* @passcase					If mediacodec_get_supported_type is successful
* @failcase					If mediacodec_get_supported_type fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_get_supported_type_p(void)
{
	START_TEST;

	mediacodec_codec_type_e codec = MEDIACODEC_AAC;
	bool bEncoder = true; // checking encoder type
	int nType = -1;

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ( nType < 0 )
	{
		FPRINTF("[Line : %d][%s] mediacodec_get_supported_type returned invalid parameter \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: set and unset buffer status callback for the media codec
//& type: auto
/**
* @testcase 				ITc_mediacodec_set_unset_buffer_status_cb_p
* @since_tizen				2.4
* @author					SRID(parshant.v)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets and unsets buffer status callback for the media codec
* @scenario					Set buffer status callback for the media codec for process asynchronously\n
*							Unset buffer status callback for the media codec
* @apicovered				mediacodec_set_codec, mediacodec_set_aenc_info, mediacodec_set_buffer_status_cb\n
*							mediacodec_prepare, mediacodec_process_input, mediacodec_unprepare, mediacodec_unset_buffer_status_cb
* @passcase					If mediacodec_set_buffer_status_cb and mediacodec_unset_buffer_status_cb is successful
* @failcase					If mediacodec_set_buffer_status_cb or mediacodec_unset_buffer_status_cb fails
* @precondition				mediacodec_set_buffer_status_cb should be called before mediacodec_preare
* @postcondition			mediacodec_input_buffer_used_cb will be invoked
*/
int ITc_mediacodec_set_unset_buffer_status_cb_p(void)
{
	START_TEST;

	mediacodec_codec_type_e codec = MEDIACODEC_AAC;
	int flags;
	bool bEncoder = true; // checking encoder type
	int nType = 0, i = 0;
	int bit_depth[] = { 16, 32 };

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ( nType != MEDIACODEC_SUPPORT_TYPE_SW )
	{
		FPRINTF("[Line : %d][%s] Audio encoder MEDIACODEC_AAC is not supported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Setting flag after validation
	flags = MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW;

	nRet = mediacodec_set_codec(g_mediacodec, codec, flags);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));

	for (i = 0; i < 2; i++) {
		nRet = mediacodec_set_aenc_info(g_mediacodec, 48000, 2, bit_depth[i], 128000);
		if (nRet == MEDIACODEC_ERROR_NONE)
			break;
	}
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_aenc_info", MediaCodecGetError(nRet));

	//Target API
	nRet = mediacodec_set_buffer_status_cb(g_mediacodec, mediacodec_buffer_status_cb_p, NULL);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_buffer_status_cb", MediaCodecGetError(nRet));

	g_bCallbackResult = false;
	nRet = mediacodec_prepare(g_mediacodec);
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_prepare", MediaCodecGetError(nRet), mediacodec_unset_buffer_status_cb(g_mediacodec));


	for ( i = 0; i < FRAME_COUNT; i++ )
	{
		media_packet_h hInputBuffNew = NULL;
		media_packet_create_alloc(hFormat, NULL, NULL, &hInputBuffNew);
		void *szData = NULL;
		media_packet_get_buffer_data_ptr(hInputBuffNew, &szData);
		unsigned int unSize = GetDataFromFile(szData);
		media_packet_set_buffer_size(hInputBuffNew, unSize);
		nRet = mediacodec_process_input(g_mediacodec, hInputBuffNew, 0);
		PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_process_input", MediaCodecGetError(nRet), mediacodec_unset_buffer_status_cb(g_mediacodec));
	}

	RUN_POLLING_LOOP("mediacodec");

	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Async callback not invoked\\n", __LINE__, API_NAMESPACE);
		mediacodec_unprepare(g_mediacodec);
		mediacodec_unset_buffer_status_cb(g_mediacodec);
		return 1;
	}

	nRet = mediacodec_unprepare(g_mediacodec);
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unprepare", MediaCodecGetError(nRet), mediacodec_unset_buffer_status_cb(g_mediacodec));

	//Target API
	nRet = mediacodec_unset_buffer_status_cb(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unset_buffer_status_cb", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Gets the media packet pool allocated for recycling media packets.
//& type: auto
/**
* @testcase 				ITc_mediacodec_get_packet_pool_p
* @since_tizen				3.0
* @author					SRID(shilpa.j)
* @reviewer					SRID(gaurav.m2)
* @type 					auto
* @description				Gets the media packet pool allocated for recycling media packets.
* @scenario					Gets the media packet pool allocated for recycling media packets
* @apicovered				mediacodec_set_codec, mediacodec_set_aenc_info, mediacodec_prepare, mediacodec_unprepare, mediacodec_get_packet_pool
* @passcase					If mediacodec_get_packet_pool is successful
* @failcase					If mediacodec_get_packet_pool fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_get_packet_pool_p(void)
{
	START_TEST;

	mediacodec_codec_type_e codec = MEDIACODEC_AAC;
	int flags;
	bool bEncoder = true; // checking encoder type
	int nType = 0;
	media_packet_pool_h hpacket_pool;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	int nRet = mediacodec_get_supported_type(g_mediacodec, codec, bEncoder, &nType);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_supported_type", MediaCodecGetError(nRet));

	if ( nType != MEDIACODEC_SUPPORT_TYPE_SW )
	{
		FPRINTF("[Line : %d][%s] Audio encoder MEDIACODEC_AAC is not supported. Skipping test\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Setting flag after validation
	flags = MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW;

	nRet = mediacodec_set_codec(g_mediacodec, codec, flags);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_codec", MediaCodecGetError(nRet));

	for (i = 0; i < 2; i++) {
		nRet = mediacodec_set_aenc_info(g_mediacodec, 48000, 2, bit_depth[i], 128000);
		if (nRet == MEDIACODEC_ERROR_NONE)
			break;
	}
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_set_aenc_info", MediaCodecGetError(nRet));

	nRet = mediacodec_prepare(g_mediacodec);
	PRINT_RESULT(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_prepare", MediaCodecGetError(nRet));


	//Target API
	nRet = mediacodec_get_packet_pool(g_mediacodec, &hpacket_pool);
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_get_packet_pool", MediaCodecGetError(nRet), mediacodec_unprepare(g_mediacodec));
	CHECK_HANDLE_CLEANUP(hpacket_pool, "mediacodec_get_packet_pool", mediacodec_unprepare(g_mediacodec));

	nRet = media_packet_pool_deallocate(hpacket_pool);
	PRINT_RESULT_NORETURN(MEDIACODEC_ERROR_NONE, nRet, "media_packet_pool_deallocate", MediaCodecGetError(nRet));

	nRet =  media_packet_pool_destroy(hpacket_pool);
	PRINT_RESULT_NORETURN(MEDIACODEC_ERROR_NONE, nRet, "media_packet_pool_destroy", MediaCodecGetError(nRet));

	nRet = mediacodec_unprepare(g_mediacodec);
	PRINT_RESULT_NORETURN(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_unprepare", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Sets the audio and video decoder codec type info via media format.
//& type: auto
/**
* @testcase 				ITc_mediacodec_configure_from_media_format_audio_video_decoder_p
* @since_tizen				4.0
* @author				SRID(s.bhadula)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description				Sets the audio and video decoder codec type info via media format.
* @scenario				Use Video decoder and Audio decoder media format for setting decoder codec type
* @apicovered				media_format_create, media_format_set_audio_mime, media_format_set_audio_channel, media_format_set_audio_bit,
					media_format_set_audio_samplerate, media_format_set_video_mime, media_format_set_video_width,
					media_format_set_video_height, mediacodec_configure_from_media_format
* @passcase				If mediacodec_configure_from_media_format is successful
* @failcase				If mediacodec_configure_from_media_format fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_configure_from_media_format_audio_video_decoder_p(void)
{
	START_TEST;
	int nRet =  0;
	media_format_h audioDecoderformat = NULL;
	media_format_h videoDecoderformat = NULL;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	nRet = media_format_create(&audioDecoderformat);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaCodecGetError(nRet));

	CHECK_HANDLE(audioDecoderformat, "media_format_create");

	/* set audio decoder format */
	nRet = media_format_set_audio_mime(audioDecoderformat, MEDIA_FORMAT_AAC);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaCodecGetError(nRet), media_format_unref(audioDecoderformat));
	nRet = media_format_set_audio_channel(audioDecoderformat, 2);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaCodecGetError(nRet), media_format_unref(audioDecoderformat));
	nRet = media_format_set_audio_samplerate(audioDecoderformat, 48000);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaCodecGetError(nRet), media_format_unref(audioDecoderformat));

	for (i = 0; i < 2; i++) {
		nRet = media_format_set_audio_bit(audioDecoderformat, bit_depth[i]);
		PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_bit", MediaCodecGetError(nRet), media_format_unref(audioDecoderformat));
		nRet = mediacodec_configure_from_media_format(g_mediacodec, audioDecoderformat, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
		if (nRet == MEDIACODEC_ERROR_NONE)
			break;
	}
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_configure_from_media_format", MediaCodecGetError(nRet), media_format_unref(audioDecoderformat));

	nRet = media_format_unref(audioDecoderformat);
	PRINT_RESULT_NORETURN(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaCodecGetError(nRet));

	nRet = media_format_create(&videoDecoderformat);
	CHECK_HANDLE(videoDecoderformat, "media_format_create");
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaCodecGetError(nRet), media_format_unref(videoDecoderformat));

	/* set video decoder format */
	nRet = media_format_set_video_mime(videoDecoderformat, MEDIA_FORMAT_H264_SP);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaCodecGetError(nRet), media_format_unref(videoDecoderformat));
	nRet = media_format_set_video_width(videoDecoderformat, 640);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaCodecGetError(nRet), media_format_unref(videoDecoderformat));
	nRet = media_format_set_video_height(videoDecoderformat, 480);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaCodecGetError(nRet), media_format_unref(videoDecoderformat));

	nRet = mediacodec_configure_from_media_format(g_mediacodec, videoDecoderformat, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_configure_from_media_format", MediaCodecGetError(nRet), media_format_unref(videoDecoderformat));
	nRet = media_format_unref(videoDecoderformat);
	PRINT_RESULT_NORETURN(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaCodecGetError(nRet));

	return 0;
}

//& purpose: Sets the audio and video encoder codec type info via media format.
//& type: auto
/**
* @testcase 				ITc_mediacodec_configure_from_media_format_audio_video_encoder_p
* @since_tizen				4.0
* @author				SRID(s.bhadula)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description				Sets the audio and video encoder codec type info via media format.
* @scenario				Use Video encoder and Audio encoder media format for setting encoder codec type
* @apicovered				media_format_create, media_format_set_audio_mime, media_format_set_audio_samplerate, media_format_set_audio_channel,
					media_format_set_audio_bit, media_format_set_audio_avg_bps, media_format_set_video_mime, 						media_format_set_video_width, media_format_set_video_height, media_format_set_video_avg_bps,
					media_format_set_video_frame_rate, mediacodec_configure_from_media_format
* @passcase				If mediacodec_configure_from_media_format is successful
* @failcase				If mediacodec_configure_from_media_format fails
* @precondition				NA
* @postcondition			NA
*/
int ITc_mediacodec_configure_from_media_format_audio_video_encoder_p(void)
{
	START_TEST;
	int nRet =  0;
	media_format_h audioEncoderformat = NULL;
	media_format_h videoEncoderformat = NULL;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	nRet = media_format_create(&audioEncoderformat);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaCodecGetError(nRet), media_format_unref(audioEncoderformat));
	CHECK_HANDLE(audioEncoderformat, "media_format_create");

	/* set audio encoder format */
	nRet = media_format_set_audio_mime(audioEncoderformat, MEDIA_FORMAT_AAC);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaCodecGetError(nRet), media_format_unref(audioEncoderformat));
	nRet = media_format_set_audio_samplerate(audioEncoderformat, 48000);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaCodecGetError(nRet), media_format_unref(audioEncoderformat));
	nRet = media_format_set_audio_channel(audioEncoderformat, 2);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaCodecGetError(nRet), media_format_unref(audioEncoderformat));
	nRet = media_format_set_audio_avg_bps(audioEncoderformat,128000);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_avg_bps", MediaCodecGetError(nRet), media_format_unref(audioEncoderformat));

	for (i = 0; i < 2; i++) {
		nRet = media_format_set_audio_bit(audioEncoderformat, bit_depth[i]);
		PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_bit", MediaCodecGetError(nRet), media_format_unref(audioEncoderformat));
		nRet = mediacodec_configure_from_media_format(g_mediacodec, audioEncoderformat, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
		if (nRet == MEDIACODEC_ERROR_NONE)
			break;
	}
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_configure_from_media_format", MediaCodecGetError(nRet), media_format_unref(audioEncoderformat));

	nRet = media_format_unref(audioEncoderformat);
	PRINT_RESULT_NORETURN(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaCodecGetError(nRet));

	nRet = media_format_create(&videoEncoderformat);
	CHECK_HANDLE(videoEncoderformat, "media_format_create");
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaCodecGetError(nRet), media_format_unref(videoEncoderformat));

	/* set video encoder format */
	nRet = media_format_set_video_mime(videoEncoderformat, MEDIA_FORMAT_MPEG4_SP);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaCodecGetError(nRet), media_format_unref(videoEncoderformat));
	nRet = media_format_set_video_width(videoEncoderformat, 352);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaCodecGetError(nRet), media_format_unref(videoEncoderformat));
	nRet = media_format_set_video_height(videoEncoderformat, 288);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaCodecGetError(nRet), media_format_unref(videoEncoderformat));
	nRet = media_format_set_video_avg_bps(videoEncoderformat, 1000);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_avg_bps", MediaCodecGetError(nRet), media_format_unref(videoEncoderformat));
	nRet = media_format_set_video_frame_rate(videoEncoderformat, 500);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_frame_rate", MediaCodecGetError(nRet), media_format_unref(videoEncoderformat));

	nRet = mediacodec_configure_from_media_format(g_mediacodec, videoEncoderformat, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	PRINT_RESULT_CLEANUP(MEDIACODEC_ERROR_NONE, nRet, "mediacodec_configure_from_media_format", MediaCodecGetError(nRet), media_format_unref(videoEncoderformat));

	nRet = media_format_unref(videoEncoderformat);
	PRINT_RESULT_NORETURN(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaCodecGetError(nRet));

	return 0;
}
/** @} */ //end of itc-mediacodec
/** @} */ //end of itc-mediacodec-testcases
