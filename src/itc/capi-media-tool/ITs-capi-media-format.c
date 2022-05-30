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
#include "ITs-capi-media-tool-common.h"

/** @addtogroup itc-capi-media-tool
*  @ingroup itc
*  @{
*/

media_format_h g_hfmt;
static bool g_bMediaTools = false;

media_format_channel_position_e g_eSetPosition[] = {
	MEDIA_FORMAT_CHANNEL_POSITION_FRONT_LEFT,
	MEDIA_FORMAT_CHANNEL_POSITION_FRONT_RIGHT,
	MEDIA_FORMAT_CHANNEL_POSITION_FRONT_CENTER,
	MEDIA_FORMAT_CHANNEL_POSITION_LFE1,
	MEDIA_FORMAT_CHANNEL_POSITION_REAR_LEFT,
	MEDIA_FORMAT_CHANNEL_POSITION_REAR_RIGHT,
	MEDIA_FORMAT_CHANNEL_POSITION_FRONT_LEFT_OF_CENTER,
	MEDIA_FORMAT_CHANNEL_POSITION_FRONT_RIGHT_OF_CENTER,
	MEDIA_FORMAT_CHANNEL_POSITION_REAR_CENTER,
	MEDIA_FORMAT_CHANNEL_POSITION_LFE2,
	MEDIA_FORMAT_CHANNEL_POSITION_SIDE_LEFT,
	MEDIA_FORMAT_CHANNEL_POSITION_SIDE_RIGHT,
	MEDIA_FORMAT_CHANNEL_POSITION_TOP_FRONT_LEFT,
	MEDIA_FORMAT_CHANNEL_POSITION_TOP_FRONT_RIGHT,
	MEDIA_FORMAT_CHANNEL_POSITION_TOP_FRONT_CENTER,
	MEDIA_FORMAT_CHANNEL_POSITION_TOP_CENTER,
	MEDIA_FORMAT_CHANNEL_POSITION_TOP_REAR_LEFT,
	MEDIA_FORMAT_CHANNEL_POSITION_TOP_REAR_RIGHT,
	MEDIA_FORMAT_CHANNEL_POSITION_TOP_SIDE_LEFT,
	MEDIA_FORMAT_CHANNEL_POSITION_TOP_SIDE_RIGHT,
	MEDIA_FORMAT_CHANNEL_POSITION_TOP_REAR_CENTER,
	MEDIA_FORMAT_CHANNEL_POSITION_BOTTOM_FRONT_CENTER,
	MEDIA_FORMAT_CHANNEL_POSITION_BOTTOM_FRONT_LEFT,
	MEDIA_FORMAT_CHANNEL_POSITION_BOTTOM_FRONT_RIGHT,
	MEDIA_FORMAT_CHANNEL_POSITION_WIDE_LEFT,
	MEDIA_FORMAT_CHANNEL_POSITION_WIDE_RIGHT,
	MEDIA_FORMAT_CHANNEL_POSITION_SURROUND_LEFT,
	MEDIA_FORMAT_CHANNEL_POSITION_SURROUND_RIGHT
};

media_format_mimetype_e g_eFormateMime[] = {
	MEDIA_FORMAT_PCM,
        MEDIA_FORMAT_PCM_S16LE,
        MEDIA_FORMAT_PCM_S24LE,
        MEDIA_FORMAT_PCM_S32LE,
        MEDIA_FORMAT_PCM_S16BE,
        MEDIA_FORMAT_PCM_S24BE,
        MEDIA_FORMAT_PCM_S32BE,
        MEDIA_FORMAT_PCM_F32LE,
        MEDIA_FORMAT_PCM_F32BE,
        MEDIA_FORMAT_PCM_U16LE,
        MEDIA_FORMAT_PCM_U24LE,
        MEDIA_FORMAT_PCM_U32LE,
        MEDIA_FORMAT_PCM_U16BE,
        MEDIA_FORMAT_PCM_U24BE,
        MEDIA_FORMAT_PCM_U32BE
};

int g_nBitDepth[] = {
	16,
	16,
	24,
	32,
	16,
	24,
	32,
	32,
	32,
	16,
	24,
	32,
	16,
	24,
	32,
	32,
	32
};

void ITs_media_format_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Media_Tool_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = media_format_create(&g_hfmt);
	if ( nRet == MEDIA_FORMAT_ERROR_NONE )
	{
		g_bMediaTools = true;
	}
	return;
}

void ITs_media_format_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Media_Tool_p\\n", __LINE__, API_NAMESPACE);
#endif
	media_format_unref(g_hfmt);
	g_bMediaTools = false;

	return;
}

/** @addtogroup itc-capi-media-tool-testcases
*  @brief 		Integration testcases for module capi-media-tool
*  @ingroup 	itc-capi-media-tool
*  @{
*/

//& purpose: Increase/Decrease reference count of media_format_h object
//& type: auto
/**
* @testcase 			ITc_media_format_set_audio_avg_bps_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Increase/Decrease reference count of media_format_h object
* @scenario				Creates a media format\n
* 						Increase reference count of media_format_h object\n
* 						Decrease reference count of media_format_h object
* @apicovered			media_format_ref, media_format_unref
* @passcase				When media_format_ref, media_format_unref is successful.
* @failcase				If target API media_format_ref, media_format_unref fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_ref_p(void)
{
	START_TEST;
	int nRet=-1;

	nRet = media_format_ref(g_hfmt);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_ref", MediaFormatGetError(nRet));

	nRet = media_format_unref(g_hfmt);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Check whether the media_format_h is writable or not
//& type: auto
/**
* @testcase 			ITc_media_format_is_writable_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Check whether the media_format_h is writable or not
* @scenario				Creates a media format\n
* 						Check whether the media_format_h is writable or not
* @apicovered			media_format_is_writable
* @passcase				When media_format_is_writable is successful.
* @failcase				If target API media_format_is_writable fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_is_writable_p(void)
{
	START_TEST;
	int nRet = -1;
	media_format_h l_Newhfmt;

	bool bIsWritable=0;

	nRet = media_format_ref(g_hfmt);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_ref", MediaFormatGetError(nRet));
	
	nRet = media_format_make_writable(g_hfmt, &l_Newhfmt);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_make_writable", MediaFormatGetError(nRet));

	nRet = media_format_is_writable(l_Newhfmt, &bIsWritable);	
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_is_writable", MediaFormatGetError(nRet));
    if(bIsWritable == 0)
	{
		FPRINTF("[Line : %d][%s] ITc_media_format_is_writable_p:failure\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet = media_format_unref(l_Newhfmt);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));
	return 0;
}

//& purpose: Returns a writable copy of media_format_h
//& type: auto
/**
* @testcase 			ITc_media_format_make_writable_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Returns a writable copy of media_format_h
* @scenario				Creates a media format\n
* 						Returns a writable copy of media_format_h
* @apicovered			media_format_make_writable
* @passcase				When media_format_make_writable is successful.
* @failcase				If target API media_format_make_writable fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_make_writable_p(void)
{
	START_TEST;
	media_format_h l_Newhfmt;
	
	int nRet = media_format_ref(g_hfmt);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_ref", MediaFormatGetError(nRet));
	
	nRet = media_format_make_writable(g_hfmt, &l_Newhfmt);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_make_writable", MediaFormatGetError(nRet));
	
	nRet = media_format_unref(l_Newhfmt);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Sets video MIME type of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_video_mime_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets video MIME type of media format
* @scenario				Creates a media format\n
* 						Sets video MIME type of media format
* @apicovered			media_format_set_video_mime
* @passcase				When media_format_set_video_mime is successful.
* @failcase				If target API media_format_set_video_mime fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_video_mime_p(void)
{
	START_TEST;
	int nRet = -1;

	media_format_mimetype_e eSetMimeType[] = {
		MEDIA_FORMAT_MPEG1,		/**<media format mime type is MPEG1, VIDEO */
		MEDIA_FORMAT_AV1,		/**< media format mime type is AV1, VIDEO, (Since 6.0) */
	};

	int nEnumSize = sizeof(eSetMimeType) / sizeof(eSetMimeType[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		nRet = media_format_set_video_mime(g_hfmt, eSetMimeType[nEnumCounter]);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));
	}

	return 0;
}

//& purpose: Sets video width of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_video_width_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets video width of media format
* @scenario				Creates a media format\n
* 						Sets video width of media format
* @apicovered			media_format_set_video_width
* @passcase				When media_format_set_video_width is successful.
* @failcase				If target API media_format_set_video_width fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_video_width_p(void)
{
	START_TEST;

	int nWidth = 480;
	int nRet=-1;
	
	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_MPEG1);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_video_width(g_hfmt, nWidth);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Sets video height of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_video_height_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets video height of media format
* @scenario				Creates a media format\n
* 						Sets video height of media format
* @apicovered			media_format_set_video_height
* @passcase				When media_format_set_video_height is successful.
* @failcase				If target API media_format_set_video_height fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_video_height_p(void)
{
	START_TEST;

	int nHeight = 640;
	int nRet=-1;
	
	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_MPEG1);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_video_height(g_hfmt, nHeight);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Sets video avg_bps of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_video_avg_bps_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets video avg_bps of media format
* @scenario				Creates a media format\n
* 						Sets video avg_bps of media format
* @apicovered			media_format_set_video_avg_bps
* @passcase				When media_format_set_video_avg_bps is successful.
* @failcase				If target API media_format_set_video_avg_bps fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_video_avg_bps_p(void)
{
	START_TEST;

	int nAvgBps = 10000000;
	int nRet=-1;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_MPEG1);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_video_avg_bps(g_hfmt, nAvgBps);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_avg_bps", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Sets video max_bps of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_video_max_bps_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets video max_bps of media format
* @scenario				Creates a media format\n
* 						Sets video max_bps of media format
* @apicovered			media_format_set_video_max_bps
* @passcase				When media_format_set_video_max_bps is successful.
* @failcase				If target API media_format_set_video_max_bps fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_video_max_bps_p(void)
{
	START_TEST;

	int nMaxBps = 15000000;
	int nRet=-1;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_MPEG1);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_video_max_bps(g_hfmt, nMaxBps);	
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_max_bps", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Gets video information of media format
//& type: auto
/**
* @testcase 			ITc_media_format_get_video_info_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets video information of media format
* @scenario				Creates a media format\n
* 						Gets video information of media format
* @apicovered			media_format_get_video_info
* @passcase				When media_format_get_video_info is successful.
* @failcase				If target API media_format_get_video_info fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_get_video_info_p(void)
{
	START_TEST;
	int nRet=-1;

	int nWwidth = 0, nHeight = 0, nAvgBps = 0, nMaxBps = 0;

	media_format_mimetype_e eMediaFormatMimetype;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_MPEG1);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_video_width(g_hfmt, 640);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaFormatGetError(nRet));

	nRet = media_format_set_video_height(g_hfmt, 480);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaFormatGetError(nRet));

	nRet = media_format_set_video_avg_bps(g_hfmt, 10000);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_avg_bps", MediaFormatGetError(nRet));
	
	nRet = media_format_set_video_max_bps(g_hfmt, 15000);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_max_bps", MediaFormatGetError(nRet));

	nRet = media_format_get_video_info(g_hfmt, &eMediaFormatMimetype, &nWwidth, &nHeight, &nAvgBps, &nMaxBps);	
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_get_video_info", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Sets audio MIME type of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_audio_mime_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets audio MIME type of media format
* @scenario				Creates a media format\n
* 						Sets audio MIME type of media format
* @apicovered			media_format_set_audio_mime
* @passcase				When media_format_set_audio_mime is successful.
* @failcase				If target API media_format_set_audio_mime fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_audio_mime_p(void)
{
	START_TEST;
	int nRet=-1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Sets audio channel of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_audio_channel_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets audio channel of media format
* @scenario				Creates a media format\n
* 						Sets audio channel of media format
* @apicovered			media_format_set_audio_channel
* @passcase				When media_format_set_audio_channel is successful.
* @failcase				If target API media_format_set_audio_channel fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_audio_channel_p(void)
{
	START_TEST;

	int nChannel = 1;
	int nRet=-1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_audio_channel(g_hfmt, nChannel);	
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Sets audio samplerate of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_audio_samplerate_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets audio samplerate of media format
* @scenario				Creates a media format\n
* 						Sets audio samplerate of media format
* @apicovered			media_format_set_audio_samplerate
* @passcase				When media_format_set_audio_samplerate is successful.
* @failcase				If target API media_format_set_audio_samplerate fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_audio_samplerate_p(void)
{
	START_TEST;

	int nSamplerate = 30;
	int nRet=-1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_audio_samplerate(g_hfmt, nSamplerate);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Sets audio bit of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_audio_bit_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets audio bit of media format
* @scenario				Creates a media format\n
* 						Sets audio bit of media format
* @apicovered			media_format_set_audio_bit
* @passcase				When media_format_set_audio_bit is successful.
* @failcase				If target API media_format_set_audio_bit fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_audio_bit_p(void)
{
	START_TEST;

	int nBit = 20;
	int nRet=-1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_audio_bit(g_hfmt, nBit);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_bit", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Sets audio avg_bps of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_audio_avg_bps_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets audio avg_bps of media format
* @scenario				Creates a media format\n
* 						Sets audio avg_bps of media format
* @apicovered			media_format_set_audio_avg_bps
* @passcase				When media_format_set_audio_avg_bps is successful.
* @failcase				If target API media_format_set_audio_avg_bps fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_audio_avg_bps_p(void)
{
	START_TEST;

	int nAvgBps = 15;
	int nRet=-1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_audio_avg_bps(g_hfmt, nAvgBps);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_avg_bps", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Get audio information of media format
//& type: auto
/**
* @testcase 			ITc_media_format_get_audio_info_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Get audio information of media format
* @scenario				Creates a media format\n
* 						Get audio information of media format
* @apicovered			media_format_get_audio_info
* @passcase				When media_format_get_audio_info is successful.
* @failcase				If target API media_format_get_audio_info fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_get_audio_info_p(void)
{
	START_TEST;

	int  nChannel = 0 , nSamplerate = 0, nBit = 0, nAvgBps = 0;
	int  nRet=-1;
	media_format_mimetype_e eMediaFormatMimetype;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));
	
	nRet = media_format_set_audio_channel(g_hfmt, 1);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet));

	nRet = media_format_set_audio_samplerate(g_hfmt, 30);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_samplerate", MediaFormatGetError(nRet));
	
	nRet = media_format_set_audio_bit(g_hfmt, 20);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_bit", MediaFormatGetError(nRet));
	
	nRet = media_format_set_audio_avg_bps(g_hfmt, 15);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_avg_bps", MediaFormatGetError(nRet));

	nRet = media_format_get_audio_info(g_hfmt, &eMediaFormatMimetype, &nChannel, &nSamplerate, &nBit, &nAvgBps);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_get_audio_info", MediaFormatGetError(nRet));

	return 0;
}


//& purpose: Sets audio aac data type of this media format 
//& type: auto
/**
* @testcase 			ITc_media_format_set_audio_aac_type_p
* @since_tizen			2.4
* @author            	SRID(sk.pal)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets audio aac type of media format 
* @scenario				Creates a media format\n
* 						Sets audio aac data type of this media format 
* @apicovered			media_format_set_audio_aac_type
* @passcase				When media_format_set_audio_aac_type is successful.
* @failcase				If target API media_format_set_audio_aac_type fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_audio_aac_type_p(void)
{
	START_TEST;
	
	bool is_adts = 1;
	int nRet=-1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_AAC_HE);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));
	
	nRet = media_format_set_audio_aac_type(g_hfmt, is_adts);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_aac_type", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Gets audio aac data type of this media format 
//& type: auto
/**
* @testcase 			ITc_media_format_get_audio_avg_bps_p
* @since_tizen			2.4
* @author            	SRID(sk.pal)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets audio aac type of media format 
* @scenario				Creates a media format\n
* 						Gets audio aac data type of this media format 
* @apicovered			media_format_get_audio_aac_type
* @passcase				When media_format_get_audio_aac_type is successful.
* @failcase				If target API media_format_get_audio_aac_type fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_get_audio_aac_type_p(void)
{
	START_TEST;
	
	bool is_adts = 1;
	int nRet=-1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_AAC_HE);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));
	
	nRet = media_format_set_audio_aac_type(g_hfmt, is_adts);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_aac_type", MediaFormatGetError(nRet));
	
	nRet = media_format_get_audio_aac_type(g_hfmt, &is_adts);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_get_audio_aac_type", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Gets type of media format
//& type: auto
/**
* @testcase 			ITc_media_format_get_type_p
* @since_tizen			3.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets type of media format
* @scenario				Creates a media format\n
* 						Gets type of media format
* @apicovered			media_format_get_type
* @passcase				When media_format_get_type is successful.
* @failcase				If target API media_format_get_type fails or any precondition API fails.
* @precondition			Creates a media format and set properties
* @postcondition		None
*/
int ITc_media_format_get_type_p(void)
{
	START_TEST;
	int nRet=-1;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_MPEG1);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_video_width(g_hfmt, 640);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaFormatGetError(nRet));

	nRet = media_format_set_video_height(g_hfmt, 480);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaFormatGetError(nRet));

	nRet = media_format_set_video_avg_bps(g_hfmt, 10000);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_avg_bps", MediaFormatGetError(nRet));

	nRet = media_format_set_video_max_bps(g_hfmt, 15000);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_max_bps", MediaFormatGetError(nRet));

	nRet = media_format_set_video_frame_rate(g_hfmt, 30);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_frame_rate", MediaFormatGetError(nRet));

	media_format_type_e eFormatType;

	nRet = media_format_get_type(g_hfmt, &eFormatType);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_get_type", MediaFormatGetError(nRet));
	if(eFormatType == MEDIA_FORMAT_VIDEO)
	{
		FPRINTF("[Line : %d][%s] eFormatType = MEDIA_FORMAT_VIDEO\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Wrong Format\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Set/Get video frame rate of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_get_video_frame_rate_p
* @since_tizen			3.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets video frame rate of media format
* @scenario				Creates a media format\n
* 						Sets and Gets video frame rate of media format
* @apicovered			media_format_set_video_frame_rate,media_format_get_video_frame_rate
* @passcase				When values of set and get is matching.
* @failcase				If target API fails or any precondition API fails or value mismatch occurs.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_get_video_frame_rate_p(void)
{
	START_TEST;

	int nGetFramerate = 0;
	int nRet=-1;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_MPEG1);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_video_frame_rate(g_hfmt, 30);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_frame_rate", MediaFormatGetError(nRet));

	nRet = media_format_get_video_frame_rate(g_hfmt, &nGetFramerate);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_get_video_frame_rate", MediaFormatGetError(nRet));

	if ( nGetFramerate != 30 )
	{
		FPRINTF("[Line : %d][%s]Frame rate mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Set/Get media_format_mimetype_e of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_get_container_mime_p
* @since_tizen			3.0
* @author				SRID(manu.tiwari))
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and Gets container mime of media format
* @scenario				Creates a media format\n
* 						Set and Get audio container mime of this media format
* @apicovered			media_format_set_container_mime, media_format_get_container_mime
* @passcase				When media_format_set_container_mime, media_format_get_container_mime is successful.
* @failcase				If target API fails or any precondition API fails or mismatch occurs.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_get_container_mime_p(void)
{
	START_TEST;
	media_format_h fmt_container;
	int nRet = -1;

	media_format_mimetype_e eGetMimeType;

	media_format_mimetype_e eMimeType[] = {
		/* CONTAINER VIDEO */
		MEDIA_FORMAT_CONTAINER_MP4,                        /**< media format mime type is MP4 container, VIDEO, (Since 3.0) */
		MEDIA_FORMAT_CONTAINER_AVI,                        /**< media format mime type is AVI container, VIDEO, (Since 3.0) */
		MEDIA_FORMAT_CONTAINER_MPEG2TS,                    /**< media format mime type is MPEG2TS container, VIDEO, (Since 3.0) */
		MEDIA_FORMAT_CONTAINER_MPEG2PS,                    /**< media format mime type is MPEG2PS container, VIDEO, (Since 3.0) */
		MEDIA_FORMAT_CONTAINER_MATROSKA,                /**< media format mime type is MATROSKA container, VIDEO, (Since 3.0) */
		MEDIA_FORMAT_CONTAINER_WEBM,                    /**< media format mime type is WEBM container, VIDEO, (Since 3.0) */
		MEDIA_FORMAT_CONTAINER_3GP,                        /**< media format mime type is 3GP container, VIDEO, (Since 3.0) */

		/*CONTAINER AUDIO */
		MEDIA_FORMAT_CONTAINER_WAV,                        /**< media format mime type is WAV container, AUDIO, (Since 3.0) */
		MEDIA_FORMAT_CONTAINER_OGG,                        /**< media format mime type is OGG container, AUDIO, (Since 3.0) */
		MEDIA_FORMAT_CONTAINER_AAC_ADTS,                /**< media format mime type is AAC_ADTS container, AUDIO, (Since 3.0) */
	};

	int nEnumSize = sizeof(eMimeType) / sizeof(eMimeType[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		nRet = media_format_set_container_mime(g_hfmt,eMimeType[nEnumCounter]);
		if ( nRet != MEDIA_FORMAT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed , for enum = [ %s ]\\n", __LINE__, API_NAMESPACE, MediaFormatMimeTypeGetEnum(eMimeType[nEnumCounter]), MediaFormatGetError(nRet));
			return 1;
		}
		nRet = media_format_get_container_mime(g_hfmt,&eGetMimeType);
		if ( nRet != MEDIA_FORMAT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed , for enum = [ %s ]\\n", __LINE__, API_NAMESPACE, MediaFormatMimeTypeGetEnum(eGetMimeType), MediaFormatGetError(nRet));
			return 1;
		}
		if (eMimeType[nEnumCounter] != eGetMimeType)
		{
			FPRINTF("Line : %d][%s] %s != %s\\n",__LINE__, API_NAMESPACE, MediaFormatMimeTypeGetEnum(eMimeType[nEnumCounter]), MediaFormatMimeTypeGetEnum(eGetMimeType));
			return 1;
		}
	}

	return 0;
}

//& purpose: Sets text MIME type & text TYPE and Gets text track information of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_text_mime_set_text_type_get_text_info_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			Sets text MIME type & text TYPE and Gets text track information of media format
* @scenario				Creates a media format\n
* 						Sets text MIME type,Sets text TYPE and Gets text track information of media format
* @apicovered			media_format_set_text_mime,media_format_set_text_type & media_format_get_text_info
* @passcase				When media_format_set_text_mime & media_format_set_text_type & media_format_get_text_info is successful.
* @failcase				If target API fails or any precondition API fails or mismatch occurs.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_text_mime_set_text_type_get_text_info_p(void)
{
    START_TEST;

    media_format_h hFmtContainer = NULL;
    media_format_mimetype_e eGetMimeType;
    media_format_text_type_e eGetTextType;
    int nRet = -1;


    media_format_mimetype_e eSetMimeType[] = {
        /* Text */                
        MEDIA_FORMAT_TEXT_MP4,                            /**< media format mime type is MP4, TEXT, (Since 3.0) */
        MEDIA_FORMAT_TEXT_3GP,                            /**< media format mime type is 3GP, TEXT, (Since 3.0) */
    };

    media_format_text_type_e eSetTextType[] = {
        MEDIA_FORMAT_TEXT_TYPE_TIMED_TEXT_MP4,              /**< media format text type is MPEG-4 Timed Text */
        MEDIA_FORMAT_TEXT_TYPE_TIMED_TEXT_3GPP,              /**< media format text type is 3GPP Timed Text */
    };

    int nEnumSize = sizeof(eSetMimeType) / sizeof(eSetMimeType[0]);
    int nEnumCounter = 0;
    for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
    {
        nRet = media_format_set_text_mime(g_hfmt, eSetMimeType[nEnumCounter]);
        PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_text_mime",MediaFormatGetError(nRet), MediaFormatMimeTypeGetEnum(eSetMimeType[nEnumCounter]));

        nRet = media_format_set_text_type(g_hfmt, eSetTextType[nEnumCounter]);
        PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_text_type", MediaFormatGetError(nRet),MediaFormatTextTypeGetEnum(eSetTextType[nEnumCounter]));

        nRet = media_format_get_text_info(g_hfmt,&eGetMimeType,&eGetTextType);
        PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_get_text_info", MediaFormatGetError(nRet),MediaFormatMimeTypeGetEnum(eGetMimeType);MediaFormatTextTypeGetEnum(eGetTextType));
        if ((eSetMimeType[nEnumCounter] != eGetMimeType) || (eSetTextType[nEnumCounter] != eGetTextType))
        {
            FPRINTF("Line : %d][%s]value mismatch\\n",__LINE__, API_NAMESPACE);
            return 1;
        }
    }

    return 0;
}

#if defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)//Starts MOBILE or WEARABLE or TIZENIOT
//& purpose: Sets/Gets audio aac header type of this media format 
//& type: auto
/**
* @testcase 			ITc_media_format_set_get_audio_aac_header_type_p
* @since_tizen			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Sets/Gets audio aac header type of this media format
* @scenario				Creates a media format\n
* 						Sets/Gets audio aac header type of this media format
* @apicovered			media_format_set_audio_aac_header_type & media_format_get_audio_aac_header_type
* @passcase				When media_format_set_audio_aac_header_type and media_format_get_audio_aac_header_type is successful.
* @failcase				If target API media_format_set_audio_aac_header_type or media_format_get_audio_aac_header_type fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_get_audio_aac_header_type_p(void)
{
	START_TEST;
	
	media_format_aac_header_type_e eGetAacHdrType;
	int nRet=-1;

	media_format_aac_header_type_e eSetAacHdrType[] = {
		MEDIA_FORMAT_AAC_HEADER_ADTS,		   				/**< media format aac header type is ADTS header */
		MEDIA_FORMAT_AAC_HEADER_ADIF,		    /**< media format aac header type is ADIF header */
	};

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_AAC_HE);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	int nEnumSize = sizeof(eSetAacHdrType) / sizeof(eSetAacHdrType[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		nRet = media_format_set_audio_aac_header_type(g_hfmt, eSetAacHdrType[nEnumCounter]);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_aac_header_type", MediaFormatGetError(nRet));
	
		nRet = media_format_get_audio_aac_header_type(g_hfmt,&eGetAacHdrType);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_get_audio_aac_header_type",MediaFormatGetError(nRet));
		if (eSetAacHdrType[nEnumCounter] != eGetAacHdrType)
		{
			FPRINTF("Line : %d][%s]value mismatch\\n",__LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}
#endif // End MOBILE or WEARABLE or TIZENIOT

#ifdef TV	//Starts TV
//& purpose: Sets/Gets audio aac header type of this media format 
//& type: auto
/**
* @testcase 			ITc_media_format_set_get_audio_aac_header_type_p
* @since_tizen			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Sets/Gets audio aac header type of this media format
* @scenario				Creates a media format\n
* 						Sets/Gets audio aac header type of this media format
* @apicovered			media_format_set_audio_aac_header_type & media_format_get_audio_aac_header_type
* @passcase				When media_format_set_audio_aac_header_type and media_format_get_audio_aac_header_type is successful.
* @failcase				If target API media_format_set_audio_aac_header_type or media_format_get_audio_aac_header_type fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_format_set_get_audio_aac_header_type_p(void)
{
	START_TEST;
	
	media_format_aac_header_type_e eGetAacHdrType;
	int nRet=-1;

	media_format_aac_header_type_e eSetAacHdrType[] = {
		MEDIA_FORMAT_MPEG1,		   				/**< media format aac header type is ADTS header */
		MEDIA_FORMAT_AAC_HEADER_ADIF,		    /**< media format aac header type is ADIF header */
	};

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_AAC_HE);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	int nEnumSize = sizeof(eSetAacHdrType) / sizeof(eSetAacHdrType[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		nRet = media_format_set_audio_aac_header_type(g_hfmt, eSetAacHdrType[nEnumCounter]);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_aac_header_type", MediaFormatGetError(nRet));
	
		nRet = media_format_get_audio_aac_header_type(g_hfmt,&eGetAacHdrType);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_get_audio_aac_header_type",MediaFormatGetError(nRet));
		if (eSetAacHdrType[nEnumCounter] != eGetAacHdrType)
		{
			FPRINTF("Line : %d][%s]value mismatch\\n",__LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}
#endif  //TV	//End TV
//& purpose: Checks  whether set data pointer is successfully set
//& type: auto
/**
* @testcase                     ITc_media_format_set_extra_p
* @since_tizen                  4.0
* @author                       SRID(bipin.k)
* @reviewer                     SRID(shobhit.v)
* @type                         auto
* @description                  Positive test case to set extra data pointer
* @scenario                     Creates a media format\n
*                               Checks  whether the extra data pointer is set properly
* @apicovered                   media_format_set_extra
* @passcase                     When extra data pointer is set correctly with no error returned.
* @failcase                     When error is returned while setting extra data pointer.
* @precondition                 Creates a media format
* @postcondition                None
*/
int ITc_media_format_set_extra_p(void)
{
	START_TEST;

	int nRet = MEDIA_FORMAT_ERROR_NONE;
	char* extra = "extra";

	nRet = media_format_set_extra(g_hfmt, (void*)extra);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_extra", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Checks  whether the extra data pointer is set and get correctly
//& type: auto
/**
* @testcase                     ITc_media_format_get_extra_p
* @since_tizen                  4.0
* @author                       SRID(bipin.k)
* @reviewer                     SRID(shobhit.v)
* @type                         auto
* @description                  Positive test case to set and get extra data pointer
* @scenario                     Creates a media format\n
*                               Checks  whether the given media packet of extra type
* @apicovered                   media_format_get_extra
* @passcase                     When set and get extra data pointer has same data
* @failcase                     When set and get data of extra data pointer is differrent
* @precondition                 Creates a media format
* @postcondition                None
*/
int ITc_media_format_get_extra_p(void)
{
	START_TEST;
	int nRet = MEDIA_FORMAT_ERROR_NONE;
	void* get_extra=NULL;
	char* extra = "extra";

	nRet = media_format_set_extra(g_hfmt, (void*)extra);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_extra", MediaFormatGetError(nRet));
	nRet = media_format_get_extra(g_hfmt, &get_extra);

	if(get_extra == NULL)
	{
		FPRINTF("[Line : %d][%s] media format received , get_extra =NULL:failure\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else
	{
		if (strcmp (extra, (char*)get_extra) != 0)
		{
			FPRINTF("[Line : %d][%s] media format received , get_extra = %s:failure\\n", __LINE__, API_NAMESPACE,get_extra);
			return 1;
		}
	}
	return 0;
}

//& purpose: Converts the channels in the channel mask to a positions array \n
//& and Converts the positions array to a bitmask
//& type: auto
/**
* @testcase 			ITc_media_format_channel_positions_to_from_mask_p
* @since_tizen			5.5
* @author            	SRID(j.abhishek)
* @reviewer         	SRID(manoj.g2)
* @type 				auto
* @description			Converts the channels in the channel mask to a positions array \n
*				and Converts the positions array to a bitmask
* @scenario				Creates a media format, set audio channel \n
* 						Convert channel position to mask and mask to position array
* @apicovered			media_format_channel_positions_to_mask & media_format_channel_positions_from_mask
* @passcase				When media_format_channel_positions_to_mask and media_format_channel_positions_from_mask is successful.
* @failcase				If target API media_format_channel_positions_to_mask or media_format_channel_positions_from_mask fails or any precondition API fails.
* @precondition			Creates a media format and set audio channel
* @postcondition		None
*/
int ITc_media_format_channel_positions_to_from_mask_p(void)
{
	START_TEST;

	int nRet = MEDIA_FORMAT_ERROR_NONE;
	uint64_t nsetChMask;
	uint64_t ngetChMask;
	int nAudioCh = 1;
	int nChannels;
	media_format_channel_position_e *eGetPositions;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_audio_channel(g_hfmt, nAudioCh);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet));

	nRet = media_format_channel_positions_to_mask(g_hfmt, g_eSetPosition, &nsetChMask);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_channel_positions_to_mask", MediaFormatGetError(nRet));

	nRet = media_format_get_audio_info(g_hfmt, NULL, &nChannels, NULL, NULL, NULL);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_get_audio_info", MediaFormatGetError(nRet));

	eGetPositions = malloc(nChannels * sizeof(media_format_channel_position_e));

	nRet = media_format_channel_positions_from_mask(g_hfmt, ngetChMask, &eGetPositions);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_channel_positions_from_mask", MediaFormatGetError(nRet), FREE_MEMORY(eGetPositions));

	FREE_MEMORY(eGetPositions);

	return 0;
}

//& purpose: Sets/Gets audio channel mask of media format
//& type: auto
/**
* @testcase 			ITc_media_format_set_get_audio_channel_mask_p
* @since_tizen			5.5
* @author            	SRID(j.abhishek)
* @reviewer         	SRID(manoj.g2)
* @type 				auto
* @description			Sets/Gets audio channel mask of media format
* @scenario				Creates a media format\n
* 						Sets/Gets audio channel mask of media format
* @apicovered			media_format_set_audio_channel_mask & media_format_get_audio_channel_mask
* @passcase				When media_format_set_audio_channel_mask and media_format_get_audio_channel_mask is successful.
* @failcase				If target API media_format_set_audio_channel_mask or media_format_get_audio_channel_mask fails or any precondition API fails.
* @precondition			Creates a media format and set audio channel
* @postcondition		None
*/
int ITc_media_format_set_get_audio_channel_mask_p(void)
{
	START_TEST;

	int nRet = MEDIA_FORMAT_ERROR_NONE;
	uint64_t nsetChMask;
	uint64_t ngetChMask;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_audio_channel(g_hfmt, 1);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel", MediaFormatGetError(nRet));

	nRet = media_format_channel_positions_to_mask(g_hfmt, g_eSetPosition, &nsetChMask);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_channel_positions_to_mask", MediaFormatGetError(nRet));

	media_format_set_audio_channel_mask(g_hfmt, nsetChMask);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_channel_mask", MediaFormatGetError(nRet));

	media_format_get_audio_channel_mask(g_hfmt, &ngetChMask);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_get_audio_channel_mask",MediaFormatGetError(nRet));

	if (nsetChMask != ngetChMask)
	{
		FPRINTF("Line : %d] [Function: %s][%s]value mismatch\\n",__LINE__, __FUNCTION__,API_NAMESPACE);

		return 1;
	}
	return 0;
}

//& purpose: Checks whether the given media format is little endian.
//& type: auto
/**
* @testcase 			ITc_media_format_is_little_endian_p
* @since_tizen			5.5
* @author            	SRID(j.abhishek)
* @reviewer         	SRID(manoj.g2)
* @type 				auto
* @description			Checks whether the given media format is little endian.
* @scenario				Creates a media format\n
* 						Checks whether the given media format is little endian.
* @apicovered			media_format_is_little_endian
* @passcase				When media_format_is_little_endian is successful.
* @failcase				If target API media_format_is_little_endian fails or any precondition API fails.
* @precondition			Creates a media format and set audio mime
* @postcondition		None
*/
int ITc_media_format_is_little_endian_p(void)
{
	START_TEST;
	int nRet = MEDIA_FORMAT_ERROR_NONE;
	bool bIsLittleEndian;

	int nEnumSize = sizeof(g_eFormateMime) / sizeof(g_eFormateMime[0]);
	int nEnumCounter;

	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		nRet = media_format_set_audio_mime(g_hfmt, g_eFormateMime[nEnumCounter]); //MEDIA_FORMAT_PCM);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

		nRet = media_format_is_little_endian(g_hfmt, &bIsLittleEndian);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_is_little_endian", MediaFormatGetError(nRet));

		if(bIsLittleEndian)
		{
			FPRINTF("Line : %d] [Function: %s][%s] audio format is little endian\\n",__LINE__, __FUNCTION__,API_NAMESPACE);
		}
		else
		{
			FPRINTF("Line : %d] [Function: %s][%s] audio format is big endian\\n",__LINE__, __FUNCTION__,API_NAMESPACE);
		}
	}
	return 0;
}

//& purpose: Gets the number of bits of information in digital audio using pulse-code modulation (PCM).
//& type: auto
/**
* @testcase 			ITc_media_format_get_audio_bit_depth_p
* @since_tizen			5.5
* @author            	SRID(j.abhishek)
* @reviewer         	SRID(manoj.g2)
* @type 				auto
* @description			Gets the number of bits of information in digital audio using pulse-code modulation (PCM).
* @scenario				Creates a media format\n
* 						Gets the number of bits of information in digital audio using pulse-code modulation (PCM).
* @apicovered			media_format_get_audio_bit_depth
* @passcase				When media_format_get_audio_bit_depth is successful.
* @failcase				If target API media_format_get_audio_bit_depth fails or any precondition API fails.
* @precondition			Creates a media format and set audio mime
* @postcondition		None
*/
int ITc_media_format_get_audio_bit_depth_p(void)
{
	START_TEST;
	int nRet = MEDIA_FORMAT_ERROR_NONE;
	int nBitDepth;

	int nEnumSize = sizeof(g_eFormateMime) / sizeof(g_eFormateMime[0]);
	int nEnumCounter;

	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		nRet = media_format_set_audio_mime(g_hfmt, g_eFormateMime[nEnumCounter]);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

		nRet = media_format_get_audio_bit_depth(g_hfmt, &nBitDepth);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_get_audio_bit_depth", MediaFormatGetError(nRet));
		if (g_nBitDepth[nEnumCounter] != nBitDepth)
		{
			FPRINTF("Line : %d] [Function: %s][%s] Expected audio bit depth [%d] but retrieved audio bit depth [%d] \\n",__LINE__, __FUNCTION__,API_NAMESPACE, g_nBitDepth[nEnumCounter], nBitDepth);
			return 1;
		}
	}
	return 0;
}

/** @} */ 
/** @} */
