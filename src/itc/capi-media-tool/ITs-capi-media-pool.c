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

static media_packet_pool_h g_hpool = NULL;
static media_format_h g_hformat = NULL;
static bool g_bMediaTools = false;

void ITs_media_pool_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Media_Tool_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bMediaTools = true;
	
	int nRet = media_format_create(&g_hformat);
	if ( nRet != MEDIA_FORMAT_ERROR_NONE || g_hformat == NULL)
	{
		g_bMediaTools = false;
		return;
	}
	
	nRet = media_format_set_video_mime(g_hformat, MEDIA_FORMAT_H264_HP);
	if ( nRet != MEDIA_FORMAT_ERROR_NONE )
	{
		g_bMediaTools = false;
		return;
	}
	
	nRet = media_format_set_video_width(g_hformat, 480);
	if ( nRet != MEDIA_FORMAT_ERROR_NONE )
	{
		g_bMediaTools = false;
		return;
	}

    nRet = media_format_set_video_height(g_hformat, 640);
	if ( nRet != MEDIA_FORMAT_ERROR_NONE )
	{
		g_bMediaTools = false;
		return;
	}
	
	nRet = media_format_set_video_avg_bps(g_hformat, 10000000);
	if ( nRet != MEDIA_FORMAT_ERROR_NONE )
	{
		g_bMediaTools = false;
		return;
	}
	
	nRet = media_format_set_video_max_bps(g_hformat, 15000000);
	if ( nRet != MEDIA_FORMAT_ERROR_NONE )
	{
		g_bMediaTools = false;
		return;
	}
	
    nRet = media_format_set_video_frame_rate(g_hformat, 30);
	if ( nRet != MEDIA_FORMAT_ERROR_NONE )
	{
		g_bMediaTools = false;
		return;
	}

	nRet = media_packet_pool_create(&g_hpool);
	if ( nRet != MEDIA_FORMAT_ERROR_NONE || g_hpool == NULL)
	{
		g_bMediaTools = false;
		return;
	}
	
	return;
}

void ITs_media_pool_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Media_Tool_p\\n", __LINE__, API_NAMESPACE);
#endif
	if(g_hformat)
		media_format_unref(g_hformat);
	if(g_hpool)
		media_packet_pool_destroy(g_hpool);
	g_bMediaTools = false;

	return;
}

/** @addtogroup itc-capi-media-tool-testcases
*  @brief 		Integration testcases for module capi-media-tool
*  @ingroup 	itc-capi-media-tool
*  @{
*/

//& purpose: create media_packet_pool_h handle
//& type: auto
/**
* @testcase 			ITc_media_packet_pool_create_destroy_p
* @since_tizen			3.0
* @author            	SRID(asit.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			create media_packet_pool_h handle
* @scenario				Creates a pool handle\n
* @apicovered			media_packet_pool_create, media_packet_pool_destroy
* @passcase				When media_packet_pool_create, media_packet_pool_destroy is successful.
* @failcase				If target API media_packet_pool_create, media_packet_pool_destroy fails.
* @precondition			None
* @postcondition		None
*/
int ITc_media_packet_pool_create_destroy_p(void)
{
	START_TEST;
	media_packet_pool_h hpool = NULL;
    
    int nRet = media_packet_pool_create(&hpool);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_create", MediaPacketGetError(nRet));
	CHECK_HANDLE(hpool, "media_packet_pool_acquire_packet");
    	
	nRet = media_packet_pool_destroy(hpool);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_destroy", MediaPacketGetError(nRet));

    return 0;
}


//& purpose: Set the media format
//& type: auto
/**
* @testcase 			ITc_media_packet_pool_set_media_format_p
* @since_tizen			3.0
* @author            	SRID(asit.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Set the media format
* @scenario				Creates a pool handle,Set the media format.
* @apicovered			media_packet_pool_set_media_format
* @passcase				When media_packet_pool_set_media_format is successful.
* @failcase				If target API media_packet_pool_set_media_format fails or any precondition API fails.
* @precondition			Creates pool handle , Create media format handle.
* @postcondition		Destroy pool handle, unfer media format handle.
*/

int ITc_media_packet_pool_set_media_format_p(void)
{
	START_TEST;
	int nRet = media_packet_pool_set_media_format(g_hpool, g_hformat);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_set_media_format", MediaPacketGetError(nRet));

	return 0;
}

//& purpose: set get size
//& type: auto
/**
* @testcase 			ITc_media_packet_pool_set_get_size_p
* @since_tizen			3.0
* @author            	SRID(asit.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			set get size
* @scenario				Creates a pool handle,set get size.
* @apicovered			media_packet_pool_set_media_format, media_packet_pool_set_size and media_packet_pool_get_size
* @passcase				When media_packet_pool_set_media_format, media_packet_pool_set_size and media_packet_pool_get_size is successful.
* @failcase				If target API media_packet_pool_set_media_format, media_packet_pool_set_size or media_packet_pool_get_size fails or any precondition API fails.
* @precondition			Creates pool handle , Create media format handle.
* @postcondition		Destroy pool handle, unfer media format handle.
*/

int ITc_media_packet_pool_set_get_size_p(void)
{
	START_TEST;

	int min = -1, max = -1, curr = -1;

	int nRet = media_packet_pool_set_media_format(g_hpool, g_hformat);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_set_media_format", MediaPacketGetError(nRet));

	nRet = media_packet_pool_set_size(g_hpool, 3, 5);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_set_size", MediaPacketGetError(nRet));

	nRet = media_packet_pool_get_size(g_hpool, &min, &max, &curr);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_get_size", MediaPacketGetError(nRet));

	if(min != 3 || max != 5)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	
	if(curr == -1)
	{
		FPRINTF("[Line : %d][%s] value of curr is not correct \\n" , __LINE__, API_NAMESPACE);
		return 1;
	}
	
	
	return 0;
}

//& purpose: acquire relase packet to the pool
//& type: auto
/**
* @testcase 			ITc_media_packet_pool_acquire_release_packet_p
* @since_tizen			3.0
* @author            	SRID(asit.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			acquire relase packet to the pool.
* @scenario				Creates a pool handle,acquire relase packet to the pool.
* @apicovered			media_packet_pool_acquire_packet, media_packet_pool_release_packet
* @passcase				When media_packet_pool_acquire_packet, media_packet_pool_release_packet is successful.
* @failcase				If target API media_packet_pool_acquire_packet, media_packet_pool_release_packet fails or any precondition API fails.
* @precondition			Creates pool handle , Create media format handle.
* @postcondition		Destroy pool handle, unfer media format handle.
*/
int ITc_media_packet_pool_acquire_release_packet_p(void)
{
	START_TEST;

	media_packet_h hpkt = NULL;

	int nRet = media_packet_pool_set_media_format(g_hpool, g_hformat);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_set_media_format", MediaPacketGetError(nRet));

	nRet = media_packet_pool_set_size(g_hpool, 3, 5);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_set_size", MediaPacketGetError(nRet));

	nRet = media_packet_pool_allocate(g_hpool);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_allocate", MediaPacketGetError(nRet));

	nRet = media_packet_pool_acquire_packet(g_hpool, &hpkt, 3000);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_acquire_packet", MediaPacketGetError(nRet),media_packet_pool_deallocate(g_hpool) );
	CHECK_HANDLE(hpkt, "media_packet_pool_acquire_packet");
	
	nRet = media_packet_pool_release_packet(g_hpool, hpkt);
	PRINT_RESULT_CLEANUP(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_release_packet", MediaPacketGetError(nRet),media_packet_pool_deallocate(g_hpool));

	nRet = media_packet_pool_deallocate(g_hpool);
	PRINT_RESULT_NORETURN(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_deallocate", MediaPacketGetError(nRet));

	return 0;
}

//& purpose: allocate deallocate pool
//& type: auto
/**
* @testcase 			ITc_media_packet_pool_allocate_deallocate_p
* @since_tizen			3.0
* @author            	SRID(asit.s)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			allocate deallocate pool
* @scenario				Creates a pool handle,allocate deallocate pool.
* @apicovered			media_packet_pool_allocate, media_packet_pool_deallocate
* @passcase				When media_packet_pool_allocate, media_packet_pool_deallocate is successful.
* @failcase				If target API media_packet_pool_allocate, media_packet_pool_deallocate fails or any precondition API fails.
* @precondition			Creates pool handle , Create media format handle.
* @postcondition		Destroy pool handle, unfer media format handle.
*/
int ITc_media_packet_pool_allocate_deallocate_p(void)
{
	START_TEST;

	int nRet = media_packet_pool_set_media_format(g_hpool, g_hformat);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_set_media_format", MediaPacketGetError(nRet));

	nRet = media_packet_pool_set_size(g_hpool, 3, 5);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_set_size", MediaPacketGetError(nRet));

	nRet = media_packet_pool_allocate(g_hpool);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_allocate", MediaPacketGetError(nRet));

	nRet = media_packet_pool_deallocate(g_hpool);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_pool_deallocate", MediaPacketGetError(nRet));

	return 0;
}

/** @} */ 
/** @} */
