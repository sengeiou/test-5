//
// Copyright (c) 2015 Samsung Electronics Co., Ltd.
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

#include "assert.h"
#include <media/mediamuxer.h>
#include <storage.h>
#include <glib.h>
#include "tct_common.h"

//& set: Mediamuxer
#define API_NAMESPACE			"[MEDIAMUXER]"

//& set: Mediamuxer
static mediamuxer_h g_media_muxer = NULL;
char *uri=NULL;
static char *file_path = NULL;
static char *file = "sample.mp4";

static char *h264_path = NULL;
static char *h264_file = "output3.h264";

static bool _is_broken = false;
media_format_h media_format = NULL;

static void app_err_cb(mediamuxer_error_e error, void *user_data)
{
	printf("Got Error %d from mediamuxer\n", error);
	return;
}

static void app_eos_cb(void *user_data)
{
	printf("Got EOS from mediamuxer\n");
	return;
}

/**
 * @function		utc_mediamuxer_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_mediamuxer_startup(void)
{
	int ret = 0;
	mediamuxer_output_format_e  format = MEDIAMUXER_CONTAINER_FORMAT_MP4;

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);

		if(h264_path == NULL) {
			h264_path = (char *)malloc(strlen(pszValue) + strlen(h264_file) + 6);
			if (!h264_path) {
				PRINT_UTC_LOG("[Line : %d][%s] Fail to malloc h264 path\n", __LINE__, API_NAMESPACE);
				_is_broken = true;
				return;
			}
		    snprintf(h264_path, strlen(pszValue) + strlen(h264_file) + 6, "%s/res/%s", pszValue, h264_file );
		}
		if(file_path == NULL){
		    file_path = (char *)malloc(strlen(pszValue)+ strlen(file) + 6);
			if (!file_path) {
				PRINT_UTC_LOG("[Line : %d][%s] Fail to malloc file_path\n", __LINE__, API_NAMESPACE);
				_is_broken = true;
				return;
			}
		    snprintf(file_path, strlen(pszValue)+ strlen(file) + 6, "%s/res/%s", pszValue, file );
		}
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	if (g_media_muxer == NULL) {
		ret = mediamuxer_create(&g_media_muxer);
		if (ret  != MEDIAMUXER_ERROR_NONE) {
			_is_broken = true;
			return;
		}
	}

	if (uri == NULL)
		uri = file_path;

	/* Create video format */
	if (media_format == NULL) {
		media_format_create(&media_format);
		ret = media_format_set_video_mime(media_format, MEDIA_FORMAT_H264_SP);
		if (ret !=	MEDIA_FORMAT_ERROR_NONE) {
			PRINT_UTC_LOG("[Line : %d][%s] media_format_set_video_mime failed, API returned %d. Invalid=%d, invalid ope=%d",
				__LINE__, API_NAMESPACE, ret, MEDIA_FORMAT_ERROR_INVALID_PARAMETER, MEDIA_FORMAT_ERROR_INVALID_OPERATION);
		}
		media_format_set_video_width(media_format, 640);
		media_format_set_video_height(media_format, 480);
		media_format_set_video_avg_bps(media_format, 1200);
		media_format_set_video_max_bps(media_format, 1580);
	}

	mediamuxer_set_data_sink(g_media_muxer, uri, format);
}

/**
 * @function		utc_mediamuxer_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_mediamuxer_cleanup(void)
{
	int ret;
	mediamuxer_state_e state;

	if(mediamuxer_get_state(g_media_muxer, &state) == MEDIAMUXER_ERROR_NONE) {
		if (state == MEDIAMUXER_STATE_MUXING ||	state == MEDIAMUXER_STATE_PAUSED ||
			state == MEDIAMUXER_STATE_READY) {
			ret = mediamuxer_stop(g_media_muxer);
			if (ret != MEDIAMUXER_ERROR_NONE)
				PRINT_UTC_LOG("[Line : %d][%s] Failed stop mediamuxer\n", __LINE__, API_NAMESPACE);
		}
	}
	if(mediamuxer_get_state(g_media_muxer, &state) == MEDIAMUXER_ERROR_NONE) {
		if(state == MEDIAMUXER_STATE_READY) {
			ret = mediamuxer_unprepare(g_media_muxer);
			if (ret != MEDIAMUXER_ERROR_NONE)
				PRINT_UTC_LOG("[Line : %d][%s] Failed unprepare mediamuxer\n", __LINE__, API_NAMESPACE);
		}
	}
	if (g_media_muxer != NULL) {
		ret = mediamuxer_destroy(g_media_muxer);
		if (ret != MEDIAMUXER_ERROR_NONE)
			PRINT_UTC_LOG("[Line : %d][%s] Failed destroy mediamuxer\n", __LINE__, API_NAMESPACE);
		g_media_muxer = NULL;
	}

	if (h264_path) {
		free(h264_path);
		h264_path = NULL;
	}

	if (file_path) {
		free(file_path);
		file_path = NULL;
		uri = NULL;
	}

	if (media_format) {
		media_format_unref(media_format);
		media_format = NULL;
	}
}


//& purpose: A purpose of a first positive TC.

/**
 * @testcase		utc_mediamuxer_create_p
 * @since_tizen		3.0
 * @description		Positive Test Case for creating muxer handle
 */
int utc_mediamuxer_create_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;

	if(g_media_muxer != NULL) {
		ret = mediamuxer_destroy(g_media_muxer);
		g_media_muxer = NULL;
	}
	ret = mediamuxer_create(&g_media_muxer);
	assert_neq(g_media_muxer, NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_create_n
 * @since_tizen		3.0
 * @description		Negative Test Case for creating muxer handle
 */
int utc_mediamuxer_create_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;

	ret = mediamuxer_create(NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_set_data_sink_p
 * @since_tizen		3.0
 * @description		Positive Test Case for setting data sink
 */
int utc_mediamuxer_set_data_sink_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;
	mediamuxer_output_format_e format = MEDIAMUXER_CONTAINER_FORMAT_MP4;

	ret = mediamuxer_set_data_sink(g_media_muxer, uri, format);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_set_data_sink_n
 * @since_tizen		3.0
 * @description		Negative Test Case for setting data sink
 */
int utc_mediamuxer_set_data_sink_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;
	mediamuxer_output_format_e format = MEDIAMUXER_CONTAINER_FORMAT_MP4;

	ret = mediamuxer_set_data_sink(NULL, NULL, format);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_add_track_p
 * @since_tizen		3.0
 * @description		Positive Test Case for adding track
 */
int utc_mediamuxer_add_track_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;
	int track_index = -1;
	ret = mediamuxer_add_track(g_media_muxer, media_format, &track_index);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_add_track_n
 * @since_tizen		3.0
 * @description		Negative Test Case for adding track
 */
int utc_mediamuxer_add_track_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;
	int track_index = -1;

	ret = mediamuxer_add_track(NULL, NULL, &track_index);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_prepare_p
 * @since_tizen		3.0
 * @description		Positive Test Case for preparing muxer
 */
int utc_mediamuxer_prepare_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;
	int track_index = -1;
	ret = mediamuxer_add_track(g_media_muxer, media_format, &track_index);
	ret = mediamuxer_prepare(g_media_muxer);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_prepare_n
 * @since_tizen		3.0
 * @description		Negative Test Case for preparing muxer
 */
int utc_mediamuxer_prepare_n(void)
{
	assert(!_is_broken);
	int ret = mediamuxer_prepare(NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_start_p
 * @since_tizen		3.0
 * @description		Positive Test Case for starting muxer
 */
int utc_mediamuxer_start_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;
	int track_index = -1;
	ret = mediamuxer_add_track(g_media_muxer, media_format, &track_index);
	ret = mediamuxer_prepare(g_media_muxer);
	ret = mediamuxer_start(g_media_muxer);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_start_n
 * @since_tizen		3.0
 * @description		Negative Test Case for starting muxer
 */
int utc_mediamuxer_start_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;

	ret = mediamuxer_start(NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_write_sample_p
 * @since_tizen		3.0
 * @description		Positive Test Case for muxing and writing samples to file
 */
int utc_mediamuxer_write_sample_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;

	FILE *pvFile = NULL;
	unsigned int vsize = 5637;
	uint64_t pts_vid = 0;
	uint64_t dts_vid = 0;
	uint64_t duration_vid = 33000000;
	int track_index_vid = 1;
	int ret_scan;
	media_packet_h vid_pkt;
	unsigned char *dptr;
	media_format_h media_format2;

	mediamuxer_add_track(g_media_muxer, media_format, &track_index_vid);
	mediamuxer_prepare(g_media_muxer);
	mediamuxer_start(g_media_muxer);

	pvFile = fopen(h264_path, "rb");
	if (pvFile == NULL) {
		PRINT_UTC_LOG("[Line : %d][%s] data file cant be loaded...\n", __LINE__, API_NAMESPACE);
		return -1;
	}

	media_format_make_writable(media_format, &media_format2);
	media_format = NULL;

	if (media_format_set_video_width(media_format2, 640)) {
		PRINT_UTC_LOG("media_format_set_video_width failed\n");
		goto ERROR;
	}
	if (media_format_set_video_height(media_format2, 480)) {
		PRINT_UTC_LOG("media_format_set_video_height failed\n");
		goto ERROR;
	}

	/*frame rate is came from the caps filter of demuxer*/
	if (media_format_set_video_frame_rate(media_format2, 30)) {
		PRINT_UTC_LOG("media_format_set_video_frame_rate failed\n");
		goto ERROR;
	}

	if (media_packet_create(media_format2, NULL, NULL, &vid_pkt)) {
		PRINT_UTC_LOG("\ncreate v media packet failed tc\n");
		goto ERROR;
	}
	if (media_packet_alloc(vid_pkt)) {
		PRINT_UTC_LOG(" v media packet alloc failed\n");
		goto ERROR;
	}

	media_packet_get_buffer_data_ptr(vid_pkt, (void**)&dptr);
	vsize = fread(dptr, 1, vsize, pvFile);
	if (media_packet_set_buffer_size(vid_pkt, vsize)) {
		PRINT_UTC_LOG("set v buf size failed\n");
		goto ERROR;
	}

	if (media_packet_set_pts(vid_pkt, pts_vid)) {
		PRINT_UTC_LOG("unable to set the pts\n");
		goto ERROR;
	}
	if (media_packet_set_dts(vid_pkt, dts_vid)) {
		PRINT_UTC_LOG("unable to set the pts\n");
		goto ERROR;
	}
	if (media_packet_set_duration(vid_pkt, duration_vid)) {
		PRINT_UTC_LOG("unable to set the pts\n");
		goto ERROR;
	}

	PRINT_UTC_LOG("V write sample call. packet add:%x\n", (unsigned int)vid_pkt);
	ret = mediamuxer_write_sample(g_media_muxer, track_index_vid, vid_pkt);

	media_packet_destroy(vid_pkt);
	media_format_unref(media_format2);

	fclose(pvFile);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;

ERROR:
	media_format_unref(media_format2);
	fclose(pvFile);
	return -1;
}

/**
 * @testcase		utc_mediamuxer_write_sample_n
 * @since_tizen		3.0
 * @description		Negative Test Case for muxing and writing samples to file
 */
int utc_mediamuxer_write_sample_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;
	int track_index = -1;

	ret = mediamuxer_write_sample(g_media_muxer, track_index, NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_close_track_p
 * @since_tizen		3.0
 * @description		Positive Test Case for closing track
 */
int utc_mediamuxer_close_track_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;
	int track_index = 1;

	ret = mediamuxer_add_track(g_media_muxer, media_format, &track_index);

	ret = mediamuxer_close_track(g_media_muxer, track_index);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_close_track_n
 * @since_tizen		3.0
 * @description		Negative Test Case for closing track
 */
int utc_mediamuxer_close_track_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;
	int track_index = -1;

	ret = mediamuxer_close_track(NULL, track_index);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_pause_p
 * @since_tizen		3.0
 * @description		Positive Test Case for setting state to pause
 */
int utc_mediamuxer_pause_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;

	utc_mediamuxer_write_sample_p();

	ret = mediamuxer_pause(g_media_muxer);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_pause_n
 * @since_tizen		3.0
 * @description		Negative Test Case for setting state to pause
 */
int utc_mediamuxer_pause_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;

	ret = mediamuxer_pause(NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_resume_p
 * @since_tizen		3.0
 * @description		Positive Test Case for resuming muxer
 */
int utc_mediamuxer_resume_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;

	utc_mediamuxer_write_sample_p();

	ret = mediamuxer_pause(g_media_muxer);

	ret = mediamuxer_resume(g_media_muxer);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_resume_n
 * @since_tizen		3.0
 * @description		Negative Test Case for resuming muxer
 */
int utc_mediamuxer_resume_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;

	ret = mediamuxer_resume(NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_stop_p
 * @since_tizen		3.0
 * @description		Positive Test Case for stopping muxing process
 */
int utc_mediamuxer_stop_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;

	ret = mediamuxer_prepare(g_media_muxer);
	ret = mediamuxer_start(g_media_muxer);

	ret = mediamuxer_stop(g_media_muxer);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_stop_n
 * @since_tizen		3.0
 * @description		Negative Test Case for stopping muxing process
 */
int utc_mediamuxer_stop_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;

	ret = mediamuxer_stop(NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_unprepare_p
 * @since_tizen		3.0
 * @description		Positive Test Case for unpreparing muxer
 */
int utc_mediamuxer_unprepare_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;

	ret = mediamuxer_prepare(g_media_muxer);
	ret = mediamuxer_start(g_media_muxer);
	ret = mediamuxer_stop(g_media_muxer);
	ret = mediamuxer_unprepare(g_media_muxer);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_unprepare_n
 * @since_tizen		3.0
 * @description		Negative Test Case for unpreparing muxer
 */
int utc_mediamuxer_unprepare_n(void)
{
	assert(!_is_broken);
	int ret = mediamuxer_unprepare(NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_destroy_p
 * @since_tizen		3.0
 * @description		Positive Test Case for destroying muxer
 */
int utc_mediamuxer_destroy_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;

	ret = mediamuxer_destroy(g_media_muxer);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_destroy_n
 * @since_tizen		3.0
 * @description		Negative Test Case for destroying muxer
 */
int utc_mediamuxer_destroy_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;

	ret = mediamuxer_destroy(NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_get_state_p
 * @since_tizen		3.0
 * @description		Positive Test Case for getting state of muxer
 */
int utc_mediamuxer_get_state_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;
	mediamuxer_state_e state;

	ret = mediamuxer_get_state(g_media_muxer, &state);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_get_state_n
 * @since_tizen		3.0
 * @description		Negative Test Case for getting state of muxer
 */
int utc_mediamuxer_get_state_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;

	ret = mediamuxer_get_state(g_media_muxer, NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_OPERATION);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_set_error_cb_p
 * @since_tizen		3.0
 * @description		Positive Test Case for setting error callback
 */
int utc_mediamuxer_set_error_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;

	ret = mediamuxer_set_error_cb(g_media_muxer, (mediamuxer_error_cb)app_err_cb, g_media_muxer);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_set_error_cb_n
 * @since_tizen		3.0
 * @description		Negative Test Case for setting error callback
 */
int utc_mediamuxer_set_error_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;

	ret = mediamuxer_set_error_cb(NULL, NULL, NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_unset_error_cb_p
 * @since_tizen		3.0
 * @description		Positive Test Case for unsetting error callback
 */
int utc_mediamuxer_unset_error_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;

	ret = mediamuxer_unset_error_cb(g_media_muxer);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_unset_error_cb_n
 * @since_tizen		3.0
 * @description		Negative Test Case for unsetting error callback
 */
int utc_mediamuxer_unset_error_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;

	ret = mediamuxer_unset_error_cb(NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_set_eos_cb_p
 * @since_tizen		4.0
 * @description		Positive Test Case for setting eos callback
 */
int utc_mediamuxer_set_eos_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;

	ret = mediamuxer_set_eos_cb(g_media_muxer, (mediamuxer_eos_cb)app_eos_cb, g_media_muxer);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_set_eos_cb_n
 * @since_tizen		4.0
 * @description		Negative Test Case for setting eos callback
 */
int utc_mediamuxer_set_eos_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;

	ret = mediamuxer_set_eos_cb(NULL, NULL, NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_unset_eos_cb_p
 * @since_tizen		4.0
 * @description		Positive Test Case for unsetting eos callback
 */
int utc_mediamuxer_unset_eos_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_INVALID_PARAMETER;

	ret = mediamuxer_unset_eos_cb(g_media_muxer);
	assert_eq(ret, MEDIAMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediamuxer_unset_eos_cb_n
 * @since_tizen		4.0
 * @description		Negative Test Case for unsetting eos callback
 */
int utc_mediamuxer_unset_eos_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIAMUXER_ERROR_NONE;

	ret = mediamuxer_unset_eos_cb(NULL);
	assert_eq(ret, MEDIAMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

