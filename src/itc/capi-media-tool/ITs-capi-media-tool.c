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

static bool g_bMediaTools  = false;
static bool g_bCallBackExt = false;
static bool g_bCallBackTbm = false;
unsigned int *g_nTbmFormatArray = NULL;
tbm_surface_h g_hSurface;
static void DisposeCallbackExtMem(media_packet_h packet, void * userdata)
{
	unsigned char *data = (unsigned char *)userdata;
	g_free(data);
	g_bCallBackExt =  true;

}

static void DisposeCallback(media_packet_h packet, void * userdata)
{
	g_nCheckCb = true;
}

static void DisposeCallbackTbmSurface(media_packet_h packet, void * userdata)
{
	g_bCallBackTbm =true;
	g_free(g_nTbmFormatArray);

}

void ITs_media_tools_startup(void)
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

void ITs_media_tools_cleanup(void)
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

//& purpose: Creates a media packet handle
//& type: auto
/**
* @testcase 			ITc_media_packet_new_p
* @since_tizen			6.5
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			It creates only media packet handle without allocated buffer
* @scenario			Creates a media format\n
* 				It creates only media packet handle without allocated buffer
* @apicovered			media_packet_new
* @passcase			When media_packet_new is successful.
* @failcase			If target API media_packet_new fails or any precondition API fails.
* @precondition			Must have media_format_h instance by media_format_create()
* @postcondition		None
*/
int ITc_media_packet_new_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	int nRet=-1;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_H264_HP);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));

	g_nCheckCb = false;
	//target API
	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));
	CHECK_HANDLE(hPacket,"media_packet_new");

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));
	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] DisposeCallback not invoked \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
//& purpose: Creates a media packet handle and increses and decreases ref count of media packet handle
//& type: auto
/**
* @testcase                     ITc_media_packet_ref_unref_p
* @since_tizen                  6.5
* @author                       SRID(manu.tiwari)
* @reviewer                     SRID(shobhit.v)
* @type                         auto
* @description                  It creates only media packet handle and increses and decreases ref count of media packet handle
* @scenario                     Creates a media format\n
*                               It creates only media packet handle and increses and decreses the ref count
* @apicovered                   media_packet_ref, media_packet_unref
* @passcase                     When media_packet_ref, media_packet_unref is successful.
* @failcase                     If target API media_packet_ref, media_packet_unref fails or any precondition API fails.
* @precondition                 Must have media_format_h instance by media_format_create()
* @postcondition                None
*/
int ITc_media_packet_ref_unref_p(void)
{
        START_TEST;

        media_packet_h hPacket;
        int nRet=-1;
        g_nCheckCb = false;

        nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_H264_HP);
        PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));

        nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
        PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));
	CHECK_HANDLE(hPacket,"media_packet_new");
        //target API
        nRet = media_packet_ref(hPacket);
        PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_ref", MediaPacketGetError(nRet), media_packet_unref(hPacket));    
       //target API
        nRet = media_packet_unref(hPacket);
        PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));
       //DisposeCallback will be invoked when media_packet_unref() is called once more because internal reference count is increased with media_packet_ref().
        nRet = media_packet_unref(hPacket);
        PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

        if(g_nCheckCb != true)
        {
                FPRINTF("[Line : %d][%s] DisposeCallback not invoked \\n", __LINE__, API_NAMESPACE);
                return 1;
 	}
        return 0;
}


//& purpose: Creates a media packet handle and allocates buffer
//& type: auto
/**
* @testcase 		ITc_media_packet_new_alloc_p
* @since_tizen		6.5
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Creates a media packet handle and allocates buffer.
* @scenario		Creates a media format\n
* 			Creates a media packet handle and allocates buffer
* @apicovered		media_packet_new_alloc
* @passcase		When media_packet_new_alloc is successful.
* @failcase		If target API media_packet_new_alloc fails or any precondition API fails.
* @precondition		Must have media_format_h instance by media_format_create()
* @postcondition	Must do media_format_unref()
*/
int ITc_media_packet_new_alloc_p(void)
{
	START_TEST;

	media_packet_h hPacket;

	int nRet = -1;
	g_nCheckCb = false;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_H264_HP);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));
	//target API
	nRet = media_packet_new_alloc(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new_alloc", MediaPacketGetError(nRet));
	CHECK_HANDLE(hPacket,"media_packet_new_alloc");

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));
        if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] DisposeCallback not invoked \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Creates media packet handle and allocates buffer with tbm_surface_h
//& type: auto
/**
* @testcase 		ITc_media_packet_new_from_tbm_surface_p
* @since_tizen		6.5
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Creates media packet handle and allocates buffer with tbm_surface_h
* @scenario		Creates a media format\n
* 			Creates media packet handle\n
*			Allocates buffer with tbm_surface_h
* @apicovered		media_packet_new_from_tbm_surface
* @passcase		When media_packet_new_from_tbm_surface is successful.
* @failcase		If target API media_packet_new_from_tbm_surface fails or any precondition API fails.
* @precondition		Creates a media format
* @postcondition	None
*/
int ITc_media_packet_new_from_tbm_surface_p(void)
{
	START_TEST;

	unsigned int *nTbmFormatArray = NULL;
	unsigned int g_nTotalFormatCount = 0;
	media_packet_h hPacketTbm;
	int nRet = -1;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_H264_HP);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));

	tbm_surface_query_formats(&nTbmFormatArray, &g_nTotalFormatCount);
	tbm_surface_h hSurface = tbm_surface_create(128,128, nTbmFormatArray[0]);
	CHECK_HANDLE(hSurface,"tbm_surface_create");
	FREE_MEMORY(nTbmFormatArray);

	g_bCallBackTbm = false;
	//target API
        nRet = media_packet_new_from_tbm_surface(g_hfmt, hSurface, DisposeCallbackTbmSurface, NULL, &hPacketTbm);
        PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new_from_tbm_surface", MediaPacketGetError(nRet), tbm_surface_destroy(hSurface));
        CHECK_HANDLE_CLEANUP(hPacketTbm,"media_packet_new_from_tbm_surface", tbm_surface_destroy(hSurface));

	nRet = media_packet_unref(hPacketTbm);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet), tbm_surface_destroy(hSurface));
	if(g_bCallBackTbm != true)
	{
		FPRINTF("[Line : %d][%s] DisposeCallback not invoked \\n", __LINE__, API_NAMESPACE);
		tbm_surface_destroy(hSurface);
		return 1;
	}
	nRet = tbm_surface_destroy(hSurface);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "tbm_surface_destroy", MediaPacketGetError(nRet));

	return 0;
}
//& purpose: Creates media packet handle with already allocated external buffer or memory
//& type: auto
/**
* @testcase 		ITc_media_packet_new_from_external_memory_p
* @since_tizen		6.5
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Creates media packet handle with already allocated external buffer or memory
* @scenario		Creates a media format\n
* 			Gets audio aac data type of this media format
* @apicovered		media_packet_new_from_external_memory
* @passcase		When media_packet_new_from_external_memory is successful.
* @failcase		If target API media_packet_new_from_external_memory fails or any precondition API fails.
* @precondition		must have media_format_h instance by media_format_create()
* @postcondition	must do media_format_unref()
*/
int ITc_media_packet_new_from_external_memory_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	unsigned char *data = NULL;
	uint64_t size = 640*480*3/2;
	int nRet = -1;
	g_bCallBackExt = false;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_H264_HP);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));
	data = g_malloc(size);
	CHECK_HANDLE(data,"g_malloc");

	g_bCallBackExt = false;
	//target API
        nRet = media_packet_new_from_external_memory(g_hfmt, data, size, DisposeCallbackExtMem, data, &hPacket);
        PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_new_from_external_memory", MediaFormatGetError(nRet),g_free(data));
        CHECK_HANDLE_CLEANUP(hPacket,"media_packet_new_from_external_memory", g_free(data));

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet), g_free(data));
	if(g_bCallBackExt != true)
	{
		FPRINTF("[Line : %d][%s] DisposeCallbackExtMem not invoked \\n", __LINE__, API_NAMESPACE);
		g_free(data);
		return 1;
	}

	return 0;
}

//& purpose: Creates a media packet handle and allocates buffer
//& type: auto
/**
* @testcase 			ITc_media_packet_alloc_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Allocates buffer with media packet handle
* @scenario				Creates a media format\n
* 						Allocates buffer with media packet handle
* @apicovered			media_packet_alloc
* @passcase				When media_packet_alloc is successful.
* @failcase				If target API media_packet_alloc fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_alloc_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	int nRet = -1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new_alloc(g_hfmt, NULL, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new_alloc", MediaPacketGetError(nRet));

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Gets buffer data pointer of media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_get_buffer_data_ptr_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets buffer data pointer of media packet
* @scenario				Creates a media format\n
* 						Gets buffer data pointer of media packet
* @apicovered			media_packet_get_buffer_data_ptr
* @passcase				When media_packet_get_buffer_data_ptr is successful.
* @failcase				If target API media_packet_get_buffer_data_ptr fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_get_buffer_data_ptr_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	void* pData;
	int nRet =-1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new_alloc(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_get_buffer_data_ptr(hPacket, &pData);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_buffer_data_ptr", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Checks whether the given media packet is for video
//& type: auto
/**
* @testcase 			ITc_media_packet_is_video_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Checks whether the given media packet is for video
* @scenario				Creates a media format\n
* 						Checks whether the given media packet is for video
* @apicovered			media_packet_is_video
* @passcase				When media_packet_is_video is successful.
* @failcase				If target API media_packet_is_video fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_is_video_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	bool bIsVideo = false;
	int nRet =-1;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_NV12);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_is_video(hPacket, &bIsVideo);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_is_video", MediaPacketGetError(nRet), media_packet_unref(hPacket));
	if ( bIsVideo == false )
	{
		FPRINTF("[Line : %d][%s] given media packet is not of  video\\n", __LINE__, API_NAMESPACE);
		nRet = media_packet_unref(hPacket);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));
		return 1;
	}
	FPRINTF("[Line : %d][%s] given media packet is of  video\\n", __LINE__, API_NAMESPACE);
	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Checks whether the given media packet is for audio
//& type: auto
/**
* @testcase 			ITc_media_packet_is_audio_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Checks whether the given media packet is for audio
* @scenario				Creates a media format\n
* 						Checks whether the given media packet is for audio
* @apicovered			media_packet_is_audio
* @passcase				When media_packet_is_audio is successful.
* @failcase				If target API media_packet_is_audio fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_is_audio_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	bool bIsAudio = false;
	int nRet = -1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new",  MediaPacketGetError(nRet));

	nRet = media_packet_is_audio(hPacket, &bIsAudio);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_is_audio", MediaPacketGetError(nRet), media_packet_unref(hPacket));
	if ( bIsAudio == true )
	{
		FPRINTF("[Line : %d][%s] given media packet is for audio\\n", __LINE__, API_NAMESPACE);
	}

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Checks whether the given media packet is codec data
//& type: auto
/**
* @testcase 			ITc_media_packet_is_codec_config_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Checks whether the given media packet is codec data
* @scenario				Creates a media format\n
* 						Checks whether the given media packet is codec data
* @apicovered			media_packet_is_codec_config
* @passcase				When media_packet_is_codec_config is successful.
* @failcase				If target API media_packet_is_codec_config fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_is_codec_config_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	bool  bIsCodecConfig = false;
	int nRet = -1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_is_codec_config(hPacket, &bIsCodecConfig);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_is_codec_config", MediaPacketGetError(nRet), media_packet_unref(hPacket));
	if ( bIsCodecConfig == true )
	{
		FPRINTF("[Line : %d][%s] given media packet is codec data\\n", __LINE__, API_NAMESPACE);
	}

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Checks whether the given media packet is encoded type
//& type: auto
/**
* @testcase 			ITc_media_packet_is_encoded_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Checks whether the given media packet is encoded type
* @scenario				Creates a media format\n
* 						Checks whether the given media packet is encoded type
* @apicovered			media_packet_is_encoded
* @passcase				When media_packet_is_encoded is successful.
* @failcase				If target API media_packet_is_encoded fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_is_encoded_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	bool  bIsEncoded = false;
	int nRet=-1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_is_encoded(hPacket, &bIsEncoded);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_is_encoded", MediaPacketGetError(nRet), media_packet_unref(hPacket));
	if ( bIsEncoded == false )
	{
		FPRINTF("[Line : %d][%s] given media packet is not encoded type\\n", __LINE__, API_NAMESPACE);
		nRet = media_packet_unref(hPacket);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));
		return 1;
	}
	FPRINTF("[Line : %d][%s] given media packet is  encoded type\\n", __LINE__, API_NAMESPACE);
	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Checks whether the given media packet is eos
//& type: auto
/**
* @testcase 			ITc_media_packet_is_end_of_stream_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Checks whether the given media packet is eos
* @scenario				Creates a media format\n
* 						Checks whether the given media packet is eos
* @apicovered			media_packet_is_end_of_stream
* @passcase				When media_packet_is_end_of_stream is successful.
* @failcase				If target API media_packet_is_end_of_stream fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_is_end_of_stream_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	bool  bIsEos = false;
	int nRet = -1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_set_flags(hPacket, MEDIA_PACKET_END_OF_STREAM);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_set_flags", MediaPacketGetError(nRet));

	nRet = media_packet_is_end_of_stream(hPacket, &bIsEos);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_is_end_of_stream", MediaPacketGetError(nRet), media_packet_unref(hPacket));
	if ( bIsEos == false )
	{
		FPRINTF("[Line : %d][%s] given media packet is not  eos\\n", __LINE__, API_NAMESPACE);
		nRet = media_packet_unref(hPacket);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));
		return 1;
	}
	FPRINTF("[Line : %d][%s] given media packet is  eos\\n", __LINE__, API_NAMESPACE);
	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Checks whether the given media packet is raw type
//& type: auto
/**
* @testcase 			ITc_media_packet_is_raw_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Checks whether the given media packet is raw type
* @scenario				Creates a media format\n
* 						Checks whether the given media packet is raw type
* @apicovered			media_packet_is_raw
* @passcase				When media_packet_is_raw is successful.
* @failcase				If target API media_packet_is_raw fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_is_raw_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	bool  bIsRaw = false;
	int nRet = -1;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_I420);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_is_raw(hPacket, &bIsRaw);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_is_raw", MediaPacketGetError(nRet), media_packet_unref(hPacket));
	if ( bIsRaw == false )
	{
		FPRINTF("[Line : %d][%s] given media packet is not raw type\\n", __LINE__, API_NAMESPACE);
		nRet = media_packet_unref(hPacket);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));
		return 1;
	}
	FPRINTF("[Line : %d][%s] given media packet is  raw type\\n", __LINE__, API_NAMESPACE);
	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Checks whether the given media packet is sync frame
//& type: auto
/**
* @testcase 			ITc_media_packet_is_sync_frame_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Checks whether the given media packet is sync frame
* @scenario				Creates a media format\n
* 						Checks whether the given media packet is sync frame
* @apicovered			media_packet_is_sync_frame
* @passcase				When media_packet_is_sync_frame is successful.
* @failcase				If target API media_packet_is_sync_frame fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_is_sync_frame_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	bool  bIsSync = false;
	int nRet = -1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_set_flags(hPacket,MEDIA_PACKET_SYNC_FRAME);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_set_flags", MediaPacketGetError(nRet));

	nRet = media_packet_is_sync_frame(hPacket, &bIsSync);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_is_sync_frame", MediaPacketGetError(nRet), media_packet_unref(hPacket));
	if ( bIsSync == false )
	{
		FPRINTF("[Line : %d][%s] given media packet is not sync frame\\n", __LINE__, API_NAMESPACE);
		nRet = media_packet_unref(hPacket);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));
		return 1;
	}
	FPRINTF("[Line : %d][%s] given media packet is sync frame\\n", __LINE__, API_NAMESPACE);
	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Set/Gets media_format_h of media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_set_get_format_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Gets media_format_h of media packet.
* @scenario				Creates a media format\n
* 						Sets media_format_h of media packet\n
*						Gets media_format_h of media packet
* @apicovered			media_packet_get_format, media_packet_set_format
* @passcase				When media_packet_get_format, media_packet_set_format is successful.
* @failcase				If target API media_packet_get_format, media_packet_set_format fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_set_get_format_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	media_format_h hfmt;
	media_format_h hfmt2;
	int nRet=-1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_format_ref(g_hfmt);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_ref", MediaFormatGetError(nRet));

	nRet = media_format_make_writable(g_hfmt, &hfmt2);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_make_writable", MediaFormatGetError(nRet));

	nRet = media_format_set_audio_mime(hfmt2, MEDIA_FORMAT_AAC_HE);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_set_format(hPacket, hfmt2);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_set_format", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	nRet = media_packet_get_format(hPacket, &hfmt);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_format", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	nRet = media_format_unref(hfmt2);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));
	return 0;
}

//& purpose:  Set/Gets PTS of media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_set_get_pts_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Gets PTS of media packet
* @scenario				Creates a media format\n
* 						Sets PTS of media packet\n
*						Gets PTS of media packet
* @apicovered			media_packet_set_pts, media_packet_get_pts
* @passcase				When media_packet_set_pts, media_packet_get_pts is successful.
* @failcase				If target API media_packet_set_pts, media_packet_get_pts fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_set_get_pts_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	uint64_t nPts = 1234567;
	uint64_t nGetPts = 0;
	int nRet=-1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_set_pts(hPacket, nPts);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_set_pts", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	nRet = media_packet_get_pts(hPacket, &nGetPts);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_pts", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	if ( nPts != nGetPts )
	{
		FPRINTF("[Line : %d][%s] nPts !=  nGetPts\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose:  Set/Gets DTS of media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_set_get_pts_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Gets DTS of media packet
* @scenario				Creates a media format\n
* 						Sets DTS of media packet\n
*						Gets DTS of media packet
* @apicovered			media_packet_set_dts, media_packet_get_dts
* @passcase				When media_packet_set_dts, media_packet_get_dts is successful.
* @failcase				If target API media_packet_set_dts, media_packet_get_pts fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_set_get_dts_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	uint64_t nDts = 7654321;
	uint64_t nGetDts = 0;
	int nRet = -1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_set_dts(hPacket, nDts);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_set_dts", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	nRet = media_packet_get_dts(hPacket, &nGetDts);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_dts", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	if ( nDts != nGetDts )
	{
		FPRINTF("[Line : %d][%s]  nDts != nGetDts\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose:  Set/Gets duration of media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_set_get_duration_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Gets duration of media packet
* @scenario				Creates a media format\n
* 						Sets duration of media packet\n
*						Gets duration of media packet
* @apicovered			media_packet_set_duration, media_packet_get_duration
* @passcase				When media_packet_set_duration, media_packet_get_duration is successful.
* @failcase				If target API media_packet_set_duration, media_packet_get_duration fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_set_get_duration_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	uint64_t nDuration = 5000000;
	uint64_t nGetDuration = 0;
	int nRet = -1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_set_duration(hPacket, nDuration);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_set_duration", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	nRet = media_packet_get_duration(hPacket, &nGetDuration);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_duration", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	if ( nDuration != nGetDuration )
	{
		FPRINTF("[Line : %d][%s] nDuration != nGetDuration \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose:  Set/Gets buffer size of media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_set_get_buffer_size_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Gets buffer size of media packet
* @scenario				Creates a media format\n
* 						Sets buffer size of media packet\n
*						Gets buffer size of media packet
* @apicovered			media_packet_set_buffer_size, media_packet_get_buffer_size
* @passcase				When media_packet_set_buffer_size, media_packet_get_buffer_size is successful.
* @failcase				If target API media_packet_set_buffer_size, media_packet_get_buffer_size fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_set_get_buffer_size_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	uint64_t nBuff = 1024;
	uint64_t nGetBuff = 0;
	int nRet = -1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_set_buffer_size(hPacket, nBuff);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_set_buffer_size", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	nRet = media_packet_get_buffer_size(hPacket, &nGetBuff);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_buffer_size", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	if ( nBuff != nGetBuff )
	{
		FPRINTF("[Line : %d][%s]  nBuff != nGetBuff \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose:  Set/Gets extra data of media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_set_get_extra_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Gets extra data of media packet
* @scenario				Creates a media format\n
* 						Sets extra data of media packet\n
*						Gets extra data of media packet
* @apicovered			media_packet_set_extra, media_packet_get_extra
* @passcase				When media_packet_set_extra, media_packet_get_extra is successful.
* @failcase				If target API media_packet_set_extra, media_packet_get_extra fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_set_get_extra_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	char* pExtra = "extra";
	void *pGetExtra = NULL;
	int nRet = -1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_set_extra(hPacket, pExtra);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_set_extra", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	nRet = media_packet_get_extra(hPacket, &pGetExtra);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_extra", MediaPacketGetError(nRet), media_packet_unref(hPacket));

	if ( pExtra != pGetExtra )
	{
		FPRINTF("[Line : %d][%s] pExtra != pGetExtra\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose:  Set/unset media_buffer_flags_e of media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_set_unset_flags_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/unset media_buffer_flags_e of media packet
* @scenario				Creates a media format\n
* 						Sets media_buffer_flags_e of media packet\n
*						unset media_buffer_flags_e of media packet
* @apicovered			media_packet_set_flags, media_packet_unset_flags
* @passcase				When media_packet_set_flags, media_packet_unset_flags is successful.
* @failcase				If target API media_packet_set_flags, media_packet_unset_flags fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_set_unset_flags_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	int nRet = -1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	media_buffer_flags_e eMediaBufferFlags[] = {
		MEDIA_PACKET_CODEC_CONFIG,
		MEDIA_PACKET_END_OF_STREAM,
		MEDIA_PACKET_SYNC_FRAME
	};

	int nEnumSize = sizeof(eMediaBufferFlags) / sizeof(eMediaBufferFlags[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		char *szEnumVal = NULL;

		nRet = media_packet_set_flags(hPacket, eMediaBufferFlags[nEnumCounter]);
		PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_set_flags", MediaPacketGetError(nRet),media_packet_unref(hPacket));

		switch ( eMediaBufferFlags[nEnumCounter] )
		{
		case MEDIA_PACKET_CODEC_CONFIG : szEnumVal = "MEDIA_PACKET_CODEC_CONFIG" ; break;
		case MEDIA_PACKET_END_OF_STREAM : szEnumVal = "MEDIA_PACKET_END_OF_STREAM" ; break;
		case MEDIA_PACKET_SYNC_FRAME : szEnumVal = "MEDIA_PACKET_SYNC_FRAME" ; break;
		}
		if ( nRet != MEDIA_PACKET_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed , for enum = [ %s ]\\n", __LINE__, API_NAMESPACE,  szEnumVal);
			media_packet_unref(hPacket);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] pass for enum = [ %s ]\\n", __LINE__, API_NAMESPACE,  szEnumVal);
		}

		nRet = media_packet_unset_flags(hPacket, eMediaBufferFlags[nEnumCounter]);
		PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_unset_flags", MediaPacketGetError(nRet),media_packet_unref(hPacket));

		switch ( eMediaBufferFlags[nEnumCounter] )
		{
		case MEDIA_PACKET_CODEC_CONFIG : szEnumVal = "MEDIA_PACKET_CODEC_CONFIG" ; break;
		case MEDIA_PACKET_END_OF_STREAM : szEnumVal = "MEDIA_PACKET_END_OF_STREAM" ; break;
		case MEDIA_PACKET_SYNC_FRAME : szEnumVal = "MEDIA_PACKET_SYNC_FRAME" ; break;
		}
		if ( nRet != MEDIA_PACKET_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed , for enum = [ %s ]\\n", __LINE__, API_NAMESPACE,  szEnumVal);
			media_packet_unref(hPacket);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] pass for enum = [ %s ]\\n", __LINE__, API_NAMESPACE,  szEnumVal);
		}
	}

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Set/Get media_buffer_flags_e of media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_set_get_flags_p
* @since_tizen			3.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get media_buffer_flags_e of media packet
* @scenario				Creates a media format\n
* 						Sets media_buffer_flags_e of media packet\n
*						Gets media_buffer_flags_e of media packet
* @apicovered			media_packet_set_flags, media_packet_get_flags
* @passcase				When media_packet_set_flags, media_packet_get_flags is successful.
* @failcase				If target API fails or any precondition API fails or mismatch occurs.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_set_get_flags_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	int nRet = -1;

	nRet = media_format_set_audio_mime(g_hfmt, MEDIA_FORMAT_MP3);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	media_buffer_flags_e eGetMediaBufferFlags;
	media_buffer_flags_e eMediaBufferFlags[] = {
		MEDIA_PACKET_CODEC_CONFIG,
		MEDIA_PACKET_END_OF_STREAM,
		MEDIA_PACKET_SYNC_FRAME
	};

	int nEnumSize = sizeof(eMediaBufferFlags) / sizeof(eMediaBufferFlags[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		char *szEnumVal = NULL;
		char *szGetEnumVal = NULL;

		nRet = media_packet_set_flags(hPacket, eMediaBufferFlags[nEnumCounter]);
		if ( nRet != MEDIA_PACKET_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed , for enum = [ %s ]\\n", __LINE__, API_NAMESPACE, MediaBufferFlagsGetEnum(eMediaBufferFlags[nEnumCounter]), MediaPacketGetError(nRet));
			media_packet_unref(hPacket);
			return 1;
		}
		nRet = media_packet_get_flags(hPacket, &eGetMediaBufferFlags);
		if ( nRet != MEDIA_PACKET_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed , for enum = [ %s ]\\n", __LINE__, API_NAMESPACE, MediaBufferFlagsGetEnum(eGetMediaBufferFlags), MediaPacketGetError(nRet));
			media_packet_unref(hPacket);
			return 1;
		}
		if ( eMediaBufferFlags[nEnumCounter] != eGetMediaBufferFlags )
		{
			FPRINTF("Line : %d][%s] %s != %s\\n",__LINE__, API_NAMESPACE, MediaBufferFlagsGetEnum(eMediaBufferFlags[nEnumCounter]), MediaBufferFlagsGetEnum(eGetMediaBufferFlags));
			media_packet_unref(hPacket);
			return 1;
		}
		nRet = media_packet_unset_flags(hPacket, eMediaBufferFlags[nEnumCounter]);
		if ( nRet != MEDIA_PACKET_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed , for enum = [ %s ]\\n", __LINE__, API_NAMESPACE, MediaBufferFlagsGetEnum(eMediaBufferFlags[nEnumCounter]), MediaPacketGetError(nRet));
			media_packet_unref(hPacket);
			return 1;
		}
	}

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Gets TBM surface data of media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_get_tbm_surface_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets TBM surface data of media packet
* @scenario				Creates a media format\n
* 						Gets TBM surface data of media packet
* @apicovered			media_packet_get_tbm_surface
* @passcase				When media_packet_get_tbm_surface is successful.
* @failcase				If target API media_packet_get_tbm_surface fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_get_tbm_surface_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	tbm_surface_h hSurface;
	int nRet=-1;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_I420);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));

	nRet = media_format_set_video_width(g_hfmt, 128);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaFormatGetError(nRet));

	nRet = media_format_set_video_height(g_hfmt, 128);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaFormatGetError(nRet));

	nRet = media_format_set_video_avg_bps(g_hfmt, 10000000);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_avg_bps", MediaFormatGetError(nRet));

	nRet = media_format_set_video_max_bps(g_hfmt, 15000000);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_max_bps", MediaFormatGetError(nRet));

	nRet = media_packet_new_alloc(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_get_tbm_surface(hPacket, &hSurface);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_tbm_surface", MediaPacketGetError(nRet),media_packet_unref(hPacket));

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose: Checks whether the allocated buffer is tbm surface or not
//& type: auto
/**
* @testcase 			ITc_media_packet_has_tbm_surface_buffer_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Checks whether the allocated buffer is tbm surface or not
* @scenario				Creates a media format\n
* 						Checks whether the allocated buffer is tbm surface or not
* @apicovered			media_packet_has_tbm_surface_buffer
* @passcase				When media_packet_has_tbm_surface_buffer is successful.
* @failcase				If target API media_packet_has_tbm_surface_buffer fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_has_tbm_surface_buffer_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	bool  bHasTbmSurface = false;
	int nRet = -1;

	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_I420);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_audio_mime", MediaFormatGetError(nRet));
	nRet = media_format_set_video_width(g_hfmt, 640);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaFormatGetError(nRet),media_format_unref(g_hfmt));

	nRet = media_format_set_video_height(g_hfmt, 480);
	PRINT_RESULT_CLEANUP(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaFormatGetError(nRet),media_format_unref(g_hfmt));
	nRet = media_packet_new_alloc(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));

	nRet = media_packet_has_tbm_surface_buffer(hPacket, &bHasTbmSurface);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_has_tbm_surface_buffer", MediaPacketGetError(nRet),media_packet_unref(hPacket));
	if ( bHasTbmSurface == true )
	{
		nRet = media_packet_unref(hPacket);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));
		FPRINTF("[Line : %d][%s] allocated buffer is tbm surface \\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	else
	{
		nRet = media_packet_unref(hPacket);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));
		return 1;
	}

	return 0;
}
//& purpose: Gets the number of planes from tbm surface in the given media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_get_number_of_video_planes_p
* @since_tizen			2.4
* @author            	SRID(ajay.kr1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the number of planes from tbm surface in the given media packet
* @scenario				Gets the number of planes from tbm surface
* @apicovered			media_packet_get_number_of_video_planes
* @passcase				When media_packet_get_number_of_video_planes is successful.
* @failcase				If target API media_packet_get_number_of_video_planes fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_get_number_of_video_planes_p(void)
{
	START_TEST;

	media_packet_h hPacketTbm;
	unsigned int *nTbmFormatArray = NULL;
	unsigned int g_nTotalFormatCount = 0;
	int nNum = -1;
	int nRet = -1;

	CHECK_HANDLE(g_hfmt, "media_format_make_writable");

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

	tbm_surface_query_formats(&nTbmFormatArray, &g_nTotalFormatCount);
	tbm_surface_h hSurface = tbm_surface_create(128,128, nTbmFormatArray[0]);
	FREE_MEMORY(nTbmFormatArray);

	nRet = media_packet_new_from_tbm_surface(g_hfmt, hSurface, DisposeCallback, NULL, &hPacketTbm);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new_from_tbm_surface", MediaPacketGetError(nRet));

	nRet = media_packet_get_number_of_video_planes(hPacketTbm, &nNum);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_number_of_video_planes", MediaPacketGetError(nRet), media_packet_unref(hPacketTbm));

	if (nNum < 0)
	{
		FPRINTF("[Line : %d][%s] media_packet_get_number_of_video_planes is failed since no of planes returned is not correct \\n", __LINE__, API_NAMESPACE);

		nRet =  media_packet_unref(hPacketTbm);
		PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_unref", MediaPacketGetError(nRet));

		return 1;
	}

	nRet =  media_packet_unref(hPacketTbm);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_unref", MediaPacketGetError(nRet));

	return 0;
}

//& purpose: Gets stride width from tbm surface in the given media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_get_video_stride_width_p
* @since_tizen			2.4
* @author            	SRID(ajay.kr1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets stride width from tbm surface in the given media packet
* @scenario				Gets stride width from tbm surface
* @apicovered			media_packet_get_video_stride_width
* @passcase				When media_packet_get_video_stride_width is successful.
* @failcase				If target API media_packet_get_video_stride_width fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_get_video_stride_width_p(void)
{
	START_TEST;

	media_packet_h hPacketTbm;
	unsigned int nTotalFormatCount = 0;
	int nStrideWidth = -1;
	int nPlaneIndex = 0;
	int nRet = -1;
	g_bCallBackTbm =false;

	CHECK_HANDLE(g_hfmt, "media_format_make_writable");

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

	tbm_surface_query_formats(&g_nTbmFormatArray, &nTotalFormatCount);
	g_hSurface = tbm_surface_create(128,128, g_nTbmFormatArray[0]);

	nRet = media_packet_new_from_tbm_surface(g_hfmt, g_hSurface, DisposeCallbackTbmSurface, NULL, &hPacketTbm);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new_from_tbm_surface", MediaPacketGetError(nRet),tbm_surface_destroy (g_hSurface);g_free(g_nTbmFormatArray));

	nRet = media_packet_get_video_stride_width(hPacketTbm, nPlaneIndex, &nStrideWidth);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_video_stride_width", MediaPacketGetError(nRet), media_packet_unref(hPacketTbm);tbm_surface_destroy (g_hSurface);g_free(g_nTbmFormatArray));

	if (nStrideWidth < 0)
	{
		FPRINTF("[Line : %d][%s] media_packet_get_video_stride_width is failed since returned width is not correct \\n", __LINE__, API_NAMESPACE);

		nRet =  media_packet_unref(hPacketTbm);
		PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_unref", MediaPacketGetError(nRet),media_packet_unref(hPacketTbm);tbm_surface_destroy (g_hSurface);g_free(g_nTbmFormatArray));
		tbm_surface_destroy (g_hSurface);
		g_free(g_nTbmFormatArray);
		return 1;
	}
	nRet =  media_packet_unref(hPacketTbm);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_unref", MediaPacketGetError(nRet),tbm_surface_destroy (g_hSurface);g_free(g_nTbmFormatArray));

	if(g_bCallBackTbm == false)
	{
		nRet = tbm_surface_destroy (g_hSurface);
		PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "tbm_surface_destroy", MediaPacketGetError(nRet),g_free(g_nTbmFormatArray));
		g_free(g_nTbmFormatArray);
		return 1;
	}

	nRet = tbm_surface_destroy (g_hSurface);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "tbm_surface_destroy", MediaPacketGetError(nRet));

	g_bCallBackTbm =false;

	return 0;
}

//& purpose: Gets stride height from tbm surface in the given media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_get_video_stride_height_p
* @since_tizen			2.4
* @author            	SRID(ajay.kr1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets stride height from tbm surface in the given media packet
* @scenario				Gets stride height from tbm surface
* @apicovered			media_packet_get_video_stride_height
* @passcase				When media_packet_get_video_stride_height is successful.
* @failcase				If target API media_packet_get_video_stride_height fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_get_video_stride_height_p(void)
{
	START_TEST;

	media_packet_h hPacketTbm;
	unsigned int nTotalFormatCount = 0;
	int nStrideHeight = -1;
	int nPlaneIndex = 0;
	int nRet = -1;
	g_bCallBackTbm=false;

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

	tbm_surface_query_formats(&g_nTbmFormatArray, &nTotalFormatCount);
	g_hSurface = tbm_surface_create(128,128, g_nTbmFormatArray[0]);

	nRet = media_packet_new_from_tbm_surface(g_hfmt, g_hSurface, DisposeCallbackTbmSurface, NULL, &hPacketTbm);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new_from_tbm_surface", MediaPacketGetError(nRet),tbm_surface_destroy (g_hSurface);g_free(g_nTbmFormatArray));

	nRet = media_packet_get_video_stride_height(hPacketTbm, nPlaneIndex, &nStrideHeight);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_video_stride_height", MediaPacketGetError(nRet), media_packet_unref(hPacketTbm);tbm_surface_destroy (g_hSurface);g_free(g_nTbmFormatArray));

	if (nStrideHeight < 0)
	{
		FPRINTF("[Line : %d][%s] media_packet_get_video_stride_height is failed since returned height is not correct \\n", __LINE__, API_NAMESPACE);

		nRet =  media_packet_unref(hPacketTbm);
		PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_unref", MediaPacketGetError(nRet),tbm_surface_destroy (g_hSurface);g_free(g_nTbmFormatArray));
		tbm_surface_destroy (g_hSurface);
		g_free(g_nTbmFormatArray);
		return 1;
	}
	nRet =  media_packet_unref(hPacketTbm);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_unref", MediaPacketGetError(nRet),tbm_surface_destroy (g_hSurface);g_free(g_nTbmFormatArray));

	if(g_bCallBackTbm == false)
	{
		nRet = tbm_surface_destroy (g_hSurface);
		PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "tbm_surface_destroy", MediaPacketGetError(nRet),g_free(g_nTbmFormatArray));
		g_free(g_nTbmFormatArray);
		return 1;
	}

	nRet = tbm_surface_destroy (g_hSurface);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "tbm_surface_destroy", MediaPacketGetError(nRet));

	g_bCallBackTbm = false;

	return 0;
}

//& purpose: Gets plane data pointer from tbm surface in the given media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_get_video_plane_data_ptr_p
* @since_tizen			2.4
* @author            	SRID(ajay.kr1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets plane data pointer from tbm surface in the given media packet
* @scenario				Gets plane data pointer from tbm surface
* @apicovered			media_packet_get_video_plane_data_ptr
* @passcase				When media_packet_get_video_plane_data_ptr is successful.
* @failcase				If target API media_packet_get_video_plane_data_ptr fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_get_video_plane_data_ptr_p(void)
{
	START_TEST;

	media_packet_h hPacketTbm;
	unsigned int *nTbmFormatArray = NULL;
	unsigned int g_nTotalFormatCount = 0;
	void *pPlanedata = NULL;
	int nPlaneIndex = 0;
	int nRet = -1;

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

	tbm_surface_query_formats(&nTbmFormatArray, &g_nTotalFormatCount);
	tbm_surface_h hSurface = tbm_surface_create(128,128, nTbmFormatArray[0]);
	FREE_MEMORY(nTbmFormatArray);

	nRet = media_packet_new_from_tbm_surface(g_hfmt, hSurface, DisposeCallback, NULL, &hPacketTbm);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new_from_tbm_surface", MediaPacketGetError(nRet));

        nRet = media_packet_get_video_plane_data_ptr(hPacketTbm, nPlaneIndex, &pPlanedata);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_video_plane_data_ptr", MediaPacketGetError(nRet), media_packet_unref(hPacketTbm));

	if ( pPlanedata == NULL )
	{
		FPRINTF("[Line : %d][%s] media_packet_get_video_plane_data_ptr is failed since returned Plane data is not correct \\n", __LINE__, API_NAMESPACE);

		nRet =  media_packet_unref(hPacketTbm);
		PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_unref", MediaPacketGetError(nRet));

		return 1;
	}

	nRet =  media_packet_unref(hPacketTbm);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_unref", MediaPacketGetError(nRet));

	return 0;
}

//& purpose: Checks  whether the given media packet is for text
//& type: auto
/**
* @testcase 			ITc_media_packet_is_text_p
* @since_tizen			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			Checks  whether the given media packet is for text
* @scenario				Creates a media format\n
* 						Checks  whether the given media packet is for text
* @apicovered			media_packet_is_text
* @passcase				When media_packet_is_text is successful.
* @failcase				If target API media_packet_is_text fails or any precondition API fails.
* @precondition			Creates a media format
* @postcondition		None
*/
int ITc_media_packet_is_text_p(void)
{
	START_TEST;

	media_packet_h hPacket;
	bool  bIsText = false;
	int nRet = -1;

	nRet = media_format_set_text_mime(g_hfmt, MEDIA_FORMAT_TEXT_MP4);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_text_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));
	CHECK_HANDLE(hPacket,"media_packet_new");

	nRet = media_packet_is_text(hPacket, &bIsText);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_is_text", MediaPacketGetError(nRet), media_packet_unref(hPacket));
	if ( bIsText == true )
	{
		FPRINTF("[Line : %d][%s] given media packet is text type\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] given media packet is not text type\\n", __LINE__, API_NAMESPACE);
		nRet = media_packet_unref(hPacket);
		PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));
		return 1;
	}

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

//& purpose:  Set/Get rotate method of media packet
//& type: auto
/**
* @testcase 			ITc_media_packet_set_get_rotate_method
* @since_tizen			5.0
* @author            		SRID(samuel.peter)
* @reviewer         		SRID(priya.kohli)
* @type 			auto
* @description			Set/Get rotate method of media packet
* @scenario			Creates a media packet\n
* 				Sets rotate method of media packet\n
*				Gets rotate method of media packet
* @apicovered			media_packet_set_rotate_method, media_packet_get_rotate_method
* @passcase			When media_packet_get_rotate_method successfully gets the rotate method set by media_packet_set_rotate_method.
* @failcase			If target API media_packet_set_rotate_method, media_packet_get_method fails or if method got is different from method set.
* @precondition			Creates a media packet
* @postcondition		None
*/
int ITc_media_packet_set_get_rotate_method(void)
{
	START_TEST;

	media_packet_h hPacket;
	int nRet = -1;
	media_packet_rotate_method_e eSetMethod, eGetMethod;
	media_packet_rotate_method_e eMethodArray[] = { MEDIA_PACKET_ROTATE_IDENTITY,
							MEDIA_PACKET_ROTATE_90,
							MEDIA_PACKET_ROTATE_180,
							MEDIA_PACKET_ROTATE_270,
							MEDIA_PACKET_ROTATE_HORIZONTAL_FLIP,
							MEDIA_PACKET_ROTATE_VERTICAL_FLIP};


	nRet = media_format_set_video_mime(g_hfmt, MEDIA_FORMAT_MPEG1);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));

	nRet = media_packet_new(g_hfmt, DisposeCallback, NULL, &hPacket);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_new", MediaPacketGetError(nRet));
	CHECK_HANDLE(hPacket,"media_packet_new");

	int nSize = sizeof(eMethodArray)/sizeof(eMethodArray[0]);

	for(int i=0; i<nSize; i++)
	{
		eSetMethod = eMethodArray[i];

		nRet = media_packet_set_rotate_method(hPacket, eSetMethod);
		PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_set_rotate_method", MediaPacketGetError(nRet), media_packet_unref(hPacket));

		nRet = media_packet_get_rotate_method(hPacket, &eGetMethod);
		PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_get_rotate_method", MediaPacketGetError(nRet), media_packet_unref(hPacket));

		if(eSetMethod != eGetMethod)
		{
			FPRINTF("[Line : %d][%s] Incorrect value of eGetMethod obtained.\\n", __LINE__, API_NAMESPACE);
			media_packet_unref(hPacket);
			return 1;
		}
	}

	nRet = media_packet_unref(hPacket);
	PRINT_RESULT_NORETURN(MEDIA_FORMAT_ERROR_NONE, nRet, "media_packet_unref", MediaFormatGetError(nRet));

	return 0;
}

/** @} */
/** @} */
