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
#include "assert.h"
#include <media/media_codec.h>
#include <glib.h>
#include <string.h>
#include <storage.h>
#include <pthread.h>
#include "tct_common.h"

#define API_NAMESPACE			"[MEDIACODEC]"

#define MAX_HANDLE			10
#define MAX_INPUT_BUF_NUM   5

#define TEST_FILE_SIZE  (10 * 1024 * 1024)
#define MAX_STRING_LEN	256

#define DEFAULT_OUT_BUF_WIDTH   640
#define DEFAULT_OUT_BUF_HEIGHT  480
#define OUTBUF_SIZE (DEFAULT_OUT_BUF_WIDTH * DEFAULT_OUT_BUF_HEIGHT * 3 / 2)
#define ES_DEFAULT_VIDEO_PTS_OFFSET 20000000
#define ES_NUMBER_OF_FEED           8
#define ADTS_HEADER_SIZE            7

static char* aenc_file = "test.pcm";
static char* vdec_file = "test.h264";
static char* adec_file = "test.aac";
static char* venc_file = "test.yuv";
static char* vdec_path = NULL;
static char* venc_path = NULL;
static char* adec_path = NULL;
static char* aenc_path = NULL;

char g_uri[MAX_STRING_LEN];
FILE *fp_aenc = NULL;
FILE *fp_adec = NULL;
FILE *fp_vdec = NULL;
FILE *fp_venc = NULL;
unsigned char buffer[1000000];

static mediacodec_h g_media_codec = NULL;

media_packet_h input_buf[MAX_INPUT_BUF_NUM];
media_packet_h output_buf = NULL;

media_format_h aenc_fmt = NULL;
media_format_h adec_fmt = NULL;
media_format_h vdec_fmt = NULL;
media_format_h venc_fmt = NULL;

media_packet_h video_pkt = NULL;
media_packet_h audio_pkt = NULL;
media_packet_pool_h pool = NULL;

static bool _is_broken = false;
static bool _is_positive = false;

void* empty_data;
void* fill_data;
void* error_data;
void *eos_data;
void *support_data;
void *buffer_data;

unsigned char sps[100];
unsigned char pps[100];
unsigned char tmp_buf[1000000];
static int sps_len, pps_len;

static bool _emptybufferCB_called = false;
static bool _fillbufferCB_called = false;
static bool _eosCB_called = false;
static bool _errorCB_called = false;
static bool _feed_called = false;
static bool _use_pool = false;
static bool _mediacodec_supported = false;

pthread_t feeding_thread_id;

static void (*feed_data)(int frame_count);
static void feed_vdec_data(int frame_count);
static void feed_vdec_data2(int frame_count);

static unsigned int extract_nal(FILE *fd, unsigned char* nal);
static unsigned int extract_yuv420(FILE *fd, unsigned char* yuv);
static unsigned int extract_pcm ( FILE *fd, unsigned char* pcm );
static unsigned int extract_aacdec(FILE *fd, unsigned char* aacdata);

unsigned int extract_yuv420(FILE *fd, unsigned char* yuv)
{
	size_t result;
	int read_size;
	unsigned char buffer[1000000];

	if (feof(fd))
		return 0;

	/* CIF */
	read_size = 352*288*3/2;

	result = fread(buffer, 1,read_size, fd);

	if (result != read_size) {
		return -1;
	}

	memcpy(yuv, buffer, read_size);

	return read_size;
}

unsigned int extract_pcm ( FILE *fd, unsigned char* pcm )
{
	size_t result;
	int read_size;
	unsigned char buffer[1000000];

	if (feof(fd))
		return 0;

	read_size = 1024*2*2;

	result = fread(buffer, 1,read_size, fd);

	if(result != read_size)	{
		return -1;
	}
	memcpy(pcm, buffer, read_size);

	return read_size;
}

unsigned int extract_aacdec(FILE *fd, unsigned char* aacdata)
{
	int readsize;
	size_t result;
	unsigned int hader_size = ADTS_HEADER_SIZE;
	unsigned char buffer[1000000];

	if (feof(fd))
		return 0;

	result = fread(buffer, 1, hader_size, fd);   /* adts header */
	if(result != hader_size) {
		return 0;
	}

	if ((buffer[0] == 0xff) && ((buffer[1] & 0xf6) == 0xf0)) {
		readsize = ((buffer[3] & 0x03) << 11) | (buffer[4] << 3) | ((buffer[5] & 0xe0) >> 5);
		result = fread(buffer + hader_size, 1,(readsize - hader_size), fd);
		if (result != (readsize - hader_size))
			return 0;
		memcpy(aacdata, buffer, readsize);
	} else {
		readsize = 0;
		g_print("[FAIL] Not found aac frame sync.....\n");
	}

	return readsize;
}

unsigned int extract_nal(FILE *fd, unsigned char* nal)
{
	int nal_length = 0;
	size_t result;
	int read_size = 1;
	unsigned char buffer[1000000];
	unsigned char val, zero_count, i;
	int nal_unit_type = 0;
	int init;

	zero_count = 0;
	if (feof(fd))
		return -1;

	result = fread(buffer, 1, read_size, fd);

	if(result != read_size)
		return -1;

	val = buffer[0];
	while (1) {

		if ((zero_count == 2 || zero_count == 3) && val == 1) {
			break;
		}

		zero_count++;
		result = fread(buffer, 1, read_size, fd);

		if(result != read_size)	{
			break;
		}
		val = buffer[0];
	}
	nal[nal_length++] = 0;
	nal[nal_length++] = 0;
	nal[nal_length++] = 0;
	nal[nal_length++] = 1;
	zero_count = 0;
	init = 1;
	while (1) {
		if (feof(fd))
			return nal_length;

		result = fread(buffer, 1, read_size, fd);
		if(result != read_size)
			break;

		val = buffer[0];

		if(init) {
			nal_unit_type = val & 0xf;
			init = 0;
		}
		if (!val)
			zero_count++;
		else {
			if ((zero_count == 2 || zero_count == 3 || zero_count == 4) && (val == 1)) {
				break;
			}
			else {
				for (i = 0; i<zero_count; i++) {
					nal[nal_length++] = 0;
				}
				nal[nal_length++] = val;
				zero_count = 0;
			}
		}
	}

	fseek(fd, -(zero_count + 1), SEEK_CUR);

	if (nal_unit_type == 0x7) {
		sps_len = nal_length;
		memcpy(sps, nal, nal_length);
		return 0;
	} else if (nal_unit_type == 0x8) {
		pps_len = nal_length;
		memcpy(pps, nal, nal_length);
		return 0;
	} else if (nal_unit_type == 0x5) {
		memcpy(tmp_buf, nal, nal_length);
		memcpy(nal, sps, sps_len);
		memcpy(nal + sps_len, pps, pps_len);
		memcpy(nal + sps_len + pps_len, tmp_buf, nal_length);
		nal_length += sps_len + pps_len;
	}

	return nal_length;
}

static void feed_vdec_data(int frame_count)
{
	int read = 0;
	static guint64 pts = 0L;
	void *buf_data_ptr = NULL;

	if (media_packet_create_alloc(vdec_fmt, NULL, NULL, &video_pkt) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_create_alloc failed\n");
		return;
	}

	if (media_packet_get_buffer_data_ptr(video_pkt, &buf_data_ptr) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_get_buffer_data_ptr failed\n");
		return;
	}

	if (media_packet_set_pts(video_pkt, (uint64_t)(pts/1000000)) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_set_pts failed\n");
		return;
	}
	/* NOTE: In case of H.264 video, stream format for feeding is NAL unit.
	 * And, SPS(0x67) and PPS(0x68) should be located before IDR.(0x65).
	 */
	read = extract_nal(fp_vdec, buf_data_ptr);
	fprintf(stderr, "real length = %d\n", read);
	if (read == 0) {
		fprintf(stderr, "input file read failed\n");
		media_packet_destroy(video_pkt);
		return;
	}

	if (media_packet_set_buffer_size(video_pkt, (uint64_t)read) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_set_buffer_size failed\n");
		return;
	}

	fprintf(stderr, "frame count : %d", frame_count);

	/* frame 0 --> sps, frame 1 --> pps */
	if (frame_count == 2 )
		media_packet_set_flags(video_pkt, MEDIA_PACKET_CODEC_CONFIG);
	else if ( frame_count == ES_NUMBER_OF_FEED -1 )
		media_packet_set_flags(video_pkt, MEDIA_PACKET_END_OF_STREAM);

	/* push media packet */
	if (mediacodec_process_input ( g_media_codec, video_pkt, 0) != MEDIACODEC_ERROR_NONE) {
		fprintf(stderr, "mediacodec_process_input failed\n");
		return;
	}
	pts += ES_DEFAULT_VIDEO_PTS_OFFSET;

	_feed_called = TRUE;
	return;
}

static void feed_vdec_data2(int frame_count)
{
	int read = 0;
	static guint64 pts = 0L;
	void *buf_data_ptr = NULL;

	if (media_packet_pool_acquire_packet(pool, &video_pkt, -1) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_pool_aquire_packet failed\n");
		return;
	}

	if (media_packet_get_buffer_data_ptr(video_pkt, &buf_data_ptr) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_get_buffer_data_ptr failed\n");
		return;
	}

	if (media_packet_set_pts(video_pkt, (uint64_t)(pts/1000000)) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_set_pts failed\n");
		return;
	}
	/* NOTE: In case of H.264 video, stream format for feeding is NAL unit.
	 * And, SPS(0x67) and PPS(0x68) should be located before IDR.(0x65).
	 */
	read = extract_nal(fp_vdec, buf_data_ptr);
	fprintf(stderr, "real length = %d\n", read);
	if (read == 0) {
		fprintf(stderr, "input file read failed\n");
		media_packet_destroy(video_pkt);
		return;
	}

	if (media_packet_set_buffer_size(video_pkt, (uint64_t)read) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_set_buffer_size failed\n");
		return;
	}

	fprintf(stderr, "frame count : %d", frame_count);

	/* frame 0 --> sps, frame 1 --> pps */
	if (frame_count == 2 )
		media_packet_set_flags(video_pkt, MEDIA_PACKET_CODEC_CONFIG);
	else if ( frame_count == ES_NUMBER_OF_FEED -1 )
		media_packet_set_flags(video_pkt, MEDIA_PACKET_END_OF_STREAM);

	/* push media packet */
	if (mediacodec_process_input ( g_media_codec, video_pkt, 0) != MEDIACODEC_ERROR_NONE) {
		fprintf(stderr, "mediacodec_process_input failed\n");
		return;
	}
	pts += ES_DEFAULT_VIDEO_PTS_OFFSET;

	_feed_called = TRUE;
	_use_pool = TRUE;
	return;
}

static void feed_venc_data(int frame_count)
{
	int read = 0;
	static guint64 pts = 0L;
	void *buf_data_ptr = NULL;
	int ret;

	if (media_packet_create_alloc(venc_fmt, NULL, NULL, &video_pkt) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_create_alloc failed\n");
		return;
	}

	if (media_packet_get_buffer_data_ptr(video_pkt, &buf_data_ptr) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_get_buffer_data_ptr failed\n");
		return;
	}

	read = extract_yuv420(fp_venc, buf_data_ptr);
	fprintf(stderr, "real length = %d\n", read);
	if (read == 0) {
		fprintf(stderr, "input file read failed\n");
		return;
	}

	if (media_packet_set_buffer_size(video_pkt, (uint64_t)read) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_set_buffer_size failed\n");
		return;
	}

	if ( frame_count == ES_NUMBER_OF_FEED -1 )
		media_packet_set_flags(video_pkt, MEDIA_PACKET_END_OF_STREAM);

	/* push media packet */
	ret = mediacodec_process_input ( g_media_codec, video_pkt, 0);

	_feed_called = TRUE;
	return;
}

static void feed_aenc_data(int frame_count)
{
	int read = 0;
	static guint64 pts = 0L;
	void *buf_data_ptr = NULL;
	int ret;

	if (media_packet_create_alloc(aenc_fmt, NULL, NULL, &audio_pkt) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_create_alloc failed\n");
		return;
	}

	if (media_packet_get_buffer_data_ptr(audio_pkt, &buf_data_ptr) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_get_buffer_data_ptr failed\n");
		return;
	}

	/* NOTE: In case of H.264 video, stream format for feeding is NAL unit.
	 * And, SPS(0x67) and PPS(0x68) should be located before IDR.(0x65).
	 */
	read = extract_pcm(fp_aenc, buf_data_ptr);
	fprintf(stderr, "real length = %d\n", read);
	if (read == 0) {
		fprintf(stderr, "input file read failed\n");
		return;
	}

	if (media_packet_set_buffer_size(audio_pkt, (uint64_t)read) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_set_buffer_size failed\n");
		return;
	}

	if (frame_count == 0 )
		media_packet_set_flags(audio_pkt, MEDIA_PACKET_CODEC_CONFIG);
	else if ( frame_count == ES_NUMBER_OF_FEED -1 )
		media_packet_set_flags(audio_pkt, MEDIA_PACKET_END_OF_STREAM);

	/* push media packet */
	ret = mediacodec_process_input ( g_media_codec, audio_pkt, 0);

	_feed_called = TRUE;
	return;
}

static void feed_adec_data(int frame_count)
{
	int read = 0;
	static guint64 pts = 0L;
	void *buf_data_ptr = NULL;
	int ret;

	if (media_packet_create_alloc(adec_fmt, NULL, NULL, &audio_pkt) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_create_alloc failed\n");
		return;
	}

	if (media_packet_get_buffer_data_ptr(audio_pkt, &buf_data_ptr) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_get_buffer_data_ptr failed\n");
		return;
	}

	read = extract_aacdec(fp_adec, buf_data_ptr);
	fprintf(stderr, "real length = %d\n", read);
	if (read == 0) {
		fprintf(stderr, "input file read failed\n");
		return;
	}

	if (media_packet_set_buffer_size(audio_pkt, (uint64_t)read) != MEDIA_PACKET_ERROR_NONE) {
		fprintf(stderr, "media_packet_set_buffer_size failed\n");
		return;
	}

	/* push media packet */
	ret = mediacodec_process_input ( g_media_codec, audio_pkt, 0);

	_feed_called = TRUE;
	return;
}

static void feed_thread_func()
{
	gboolean exit = FALSE;
	static int frame_count = 0;

	while (!exit) {
		if (frame_count < ES_NUMBER_OF_FEED) {
			feed_data(frame_count);
			frame_count++;
		} else
			exit = TRUE;
	}
	pthread_exit(0);
}


int _mediacodec_get_output(void)
{
	int ret = MEDIACODEC_ERROR_NONE;

	if (_is_positive) {
		ret = mediacodec_get_output(g_media_codec, &output_buf, 0);
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
		media_packet_destroy(output_buf);
	} else {
		ret = mediacodec_get_output(NULL, &output_buf, 0);
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

static bool _mediacodec_empty_buffer_cb(media_packet_h pkt, void *user_data)
{
	int ret = 0;
	_emptybufferCB_called = true;
	if (!_use_pool)
		media_packet_destroy(pkt);
	else {
		ret = media_packet_pool_release_packet(pool, pkt);
		if (ret != MEDIA_PACKET_ERROR_NONE) {
			fprintf(stderr, "media_packet_pool_release_packet failed");
			return false;
		}
	}
	return true;
}

static bool _mediacodec_fill_buffer_cb(media_packet_h * pkt, void *user_data)
{
	fprintf(stderr, "output available callback invoked\n");
	if (pkt != NULL) {
		_mediacodec_get_output();
	}

	_fillbufferCB_called = true;
	return true;
}

static bool _mediacodec_eos_cb(void *user_data)
{
	fprintf(stderr, "eos callback invoked!\n");
	_eosCB_called = true;
	return true;
}

static bool fill_cb(media_packet_h * pkt, void *user_data)
{
	g_print("fill_cb is called\n");
	return true;
}

static bool error_cb(mediacodec_error_e error, void *user_data)
{
	g_print("error_cb is called\n");
	_errorCB_called = true;
	return true;
}

static bool eos_cb(void *user_data)
{
	g_print("eos_cb is called\n");
	return true;
}

static bool _mcdiacodec_supported_cb(mediacodec_codec_type_e type, void *user_data)
{
	if(type != -1)
		g_print("type : %x\n", type);
	return true;
}

static bool _mediacodec_buffer_status_cb(mediacodec_status_e status, void *user_data)
{
	g_print("_mediacodec_buffer_status_cb is called\n");
	return true;
}

/**
 * @function		utc_media_mediacodec_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_mediacodec_startup(void)
{
	int ret = 0;
	int i;

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	system_info_get_platform_bool("http://tizen.org/feature/multimedia.media_codec", &_mediacodec_supported);
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);

		int size_of_path = 0;
		size_of_path = strlen(pszValue) + strlen(vdec_file) + 6;
		vdec_path = (char*)malloc(size_of_path);

		if (!vdec_path) {
			_is_broken = true;
			return;
		}
		snprintf(vdec_path, size_of_path, "%s/res/%s", pszValue, vdec_file);

		size_of_path = strlen(pszValue) + strlen(venc_file) + 6;
		venc_path = (char*)malloc(size_of_path);

		if (!venc_path) {
			_is_broken = true;
			return;
		}
		snprintf(venc_path, size_of_path, "%s/res/%s", pszValue, venc_file);

		size_of_path = strlen(pszValue) + strlen(aenc_file) + 6;
		aenc_path = (char*)malloc(size_of_path);

		if (!aenc_path) {
			_is_broken = true;
			return;
		}
		snprintf(aenc_path, size_of_path, "%s/res/%s", pszValue, aenc_file);

		size_of_path = strlen(pszValue) + strlen(adec_file) + 6;
		adec_path = (char*)malloc(size_of_path);
		if (!adec_path) {
			_is_broken = true;
			return;
		}

		snprintf(adec_path, size_of_path, "%s/res/%s", pszValue, adec_file);
	}
	else
	{
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	if ( (fp_vdec = fopen(vdec_path, "r")) == -1 ) {
		fprintf(stderr, "File %s not exist\n", vdec_path);
	}

	if ( (fp_venc = fopen(venc_path, "r")) == -1 ) {
		fprintf(stderr, "File %s not exist\n", venc_path);
	}

	if ( (fp_adec = fopen(adec_path, "r")) == -1 ) {
		fprintf(stderr, "File %s not exist\n", adec_path);
	}

	if ( (fp_aenc = fopen(aenc_path, "r")) == -1 ) {
		fprintf(stderr, "File %s not exist\n", aenc_path);
	}

	ret = mediacodec_create(&g_media_codec);
	if (ret == MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE) {
		PRINT_UTC_LOG("[Line : %d][%s] mediacodec is not supported\n", __LINE__, API_NAMESPACE);
		return;
	} else if (ret  != MEDIACODEC_ERROR_NONE) {
		_is_broken = true;
		PRINT_UTC_LOG("[Line : %d][%s] mediacodec create is failed\n", __LINE__, API_NAMESPACE);
		return;
	}

	/* get media format format */
	ret = media_format_create(&vdec_fmt);
	if (ret != MEDIA_FORMAT_ERROR_NONE) {
		fprintf(stderr, "media_format_create(v) is failed");
	}
	ret = media_format_create(&venc_fmt);
	if (ret != MEDIA_FORMAT_ERROR_NONE) {
		fprintf(stderr, "media_format_create(v) is failed");
	}
	ret = media_format_create(&aenc_fmt);
	if (ret != MEDIA_FORMAT_ERROR_NONE) {
		fprintf(stderr, "media_format_create(a) is failed");
	}
	ret = media_format_create(&adec_fmt);
	if (ret != MEDIA_FORMAT_ERROR_NONE) {
		fprintf(stderr, "media_format_create(a) is failed");
	}

	/* set vdec format */
	media_format_set_video_mime(vdec_fmt, MEDIA_FORMAT_H264_SP);
	media_format_set_video_width(vdec_fmt, 640);
	media_format_set_video_height(vdec_fmt, 480);

	/* set venc format */
	media_format_set_video_mime(venc_fmt, MEDIA_FORMAT_I420);
	media_format_set_video_width(venc_fmt, 352);
	media_format_set_video_height(venc_fmt, 288);
	media_format_set_video_avg_bps(venc_fmt, 1000);

	/* set aenc format */
	media_format_set_audio_mime(aenc_fmt, MEDIA_FORMAT_PCM);
	media_format_set_audio_samplerate(aenc_fmt, 48000);
	media_format_set_audio_channel(aenc_fmt, 2);
	media_format_set_audio_bit(aenc_fmt, 16);
	media_format_set_audio_avg_bps(aenc_fmt,128000);

	/* set adec format */
	media_format_set_audio_mime(adec_fmt, MEDIA_FORMAT_AAC);
	media_format_set_audio_channel(adec_fmt, 2);
	media_format_set_audio_bit(adec_fmt, 16);
	media_format_set_audio_samplerate(adec_fmt, 48000);

}

/**
 * @function		utc_media_mediacodec_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_mediacodec_cleanup(void)
{
	int i;
	int ret;

	if (aenc_fmt)
		media_format_unref(aenc_fmt);

	if (adec_fmt)
		media_format_unref(adec_fmt);

	if (vdec_fmt)
		media_format_unref(vdec_fmt);

	if (venc_fmt)
		media_format_unref(venc_fmt);

	if (g_media_codec) {
		mediacodec_unprepare(g_media_codec);
		mediacodec_destroy(g_media_codec);
		g_media_codec = NULL;
	}

	if (_use_pool) {
		ret = media_packet_pool_deallocate(pool);
		if (ret != MEDIA_PACKET_ERROR_NONE) {
			_is_broken = true;
			fprintf(stderr, "media_packet_pool_deallocate failed");
			return;
		}
		ret = media_packet_pool_destroy(pool);
		if (ret != MEDIA_PACKET_ERROR_NONE) {
			_is_broken = true;
			fprintf(stderr, "media_packet_pool_deallocate failed");
			return;
		}
		_use_pool = FALSE;
	}

	if (fp_vdec) {
		if (vdec_path)
			free(vdec_path);
		fclose(fp_vdec);
		fp_vdec = NULL;
	}

	if (fp_venc) {
		if (venc_path)
			free(venc_path);
		fclose(fp_venc);
		fp_venc = NULL;
	}

	if (fp_aenc) {
		if (aenc_path)
			free(aenc_path);
		fclose(fp_aenc);
		fp_aenc = NULL;
	}

	if (fp_adec) {
		if (adec_path)
			free(adec_path);
		fclose(fp_adec);
		fp_adec = NULL;
	}
}

/**
 * @testcase		utc_mediacodec_create_p
 * @since_tizen		2.3
 * @description	To create mediacodec handle
 */
int utc_mediacodec_create_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_create(&g_media_codec);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_create_n
 * @since_tizen		2.3
 * @description	To create mediacodec handle
 * */
int utc_mediacodec_create_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_create(NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_destroy_p
 * @since_tizen		2.3
 * @description		To destroy mediacodec handle
 */
int utc_mediacodec_destroy_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_destroy(g_media_codec);
	g_media_codec = NULL;
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_destroy_n
 * @since_tizen		2.3
 * @description		To destroy mediacodec handle
 * */
int utc_mediacodec_destroy_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_destroy(NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}
/**
 * @testcase		utc_media_mediacodec_set_codec_p
 * @since_tizen		2.3
 * @description		To set the codec type
 */
int utc_media_mediacodec_set_codec_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_set_codec_n
 * @since_tizen		2.3
 * @description		To set the codec type
 */
int utc_media_mediacodec_set_codec_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_NONE, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_set_venc_info_p
 * @since_tizen		2.3
 * @description		To set configuration for video encoder
 */
int utc_media_mediacodec_set_venc_info_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	if (!_mediacodec_supported) {
		ret = mediacodec_set_venc_info(g_media_codec, 352, 288, 30, 10000);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_H263, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_set_venc_info(g_media_codec, 352, 288, 30, 10000);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_set_venc_info_n
 * @since_tizen		2.3
 * @description		To set configuration for video encoder
 */
int utc_media_mediacodec_set_venc_info_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	if (!_mediacodec_supported) {
		ret = mediacodec_set_venc_info(g_media_codec, -640, -480, 30, 1000000);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_H263, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_set_venc_info(g_media_codec, -640, -480, 30, 1000000);
	assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_set_vdec_info_p
 * @since_tizen		2.3
 * @description		To set configuration for video decoder
 */
int utc_media_mediacodec_set_vdec_info_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	if (!_mediacodec_supported) {
		ret = mediacodec_set_vdec_info(g_media_codec, 640, 480);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_H264, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_set_vdec_info(g_media_codec, 640, 480);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_set_vdec_info_n
 * @since_tizen		2.3
 * @description		To set configuration for video decoder
 */
int utc_media_mediacodec_set_vdec_info_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	if (!_mediacodec_supported) {
		ret = mediacodec_set_vdec_info(g_media_codec, -640, -480);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_H264, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_set_vdec_info(g_media_codec, -640, -480);
	assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_set_aenc_info_p
 * @since_tizen		2.3
 * @description		To set configuration for audio encoder
 */
int utc_media_mediacodec_set_aenc_info_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_set_aenc_info(g_media_codec, 48000, 2, 16, 128000);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	for (i = 0; i < 2; i++) {
		ret = mediacodec_set_aenc_info(g_media_codec, 48000, 2, bit_depth[i], 128000);
		if (ret == MEDIACODEC_ERROR_NONE)
			break;
	}
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_set_aenc_info_n
 * @since_tizen		2.3
 * @description		To set configuration for audio encoder
 */
int utc_media_mediacodec_set_aenc_info_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	if (!_mediacodec_supported) {
		ret = mediacodec_set_aenc_info(g_media_codec, -48000, 0, 0, 0);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_set_aenc_info(g_media_codec, -48000, 0, 0, 0);
	assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_set_adec_info_p
 * @since_tizen		2.3
 * @description		To set configuration for audio decoder
 */
int utc_media_mediacodec_set_adec_info_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_set_adec_info(g_media_codec, 48000, 2, 16);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	for (i = 0; i < 2; i++) {
		ret = mediacodec_set_adec_info(g_media_codec, 48000, 2, bit_depth[i]);
		if (ret == MEDIACODEC_ERROR_NONE)
			break;
	}
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_set_adec_info_n
 * @since_tizen		2.3
 * @description		To set configuration for audio decoder
 */
int utc_media_mediacodec_set_adec_info_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	if (!_mediacodec_supported) {
		ret = mediacodec_set_adec_info(g_media_codec, -48000, 0, 0);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_set_adec_info(g_media_codec, -48000, 0, 0);
	assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_prepare_p
 * @since_tizen		2.3
 * @description		To prepare mediacodec before feeding data
 */
int utc_media_mediacodec_prepare_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_prepare(g_media_codec);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	for (i = 0; i < 2; i++) {
		ret = mediacodec_set_aenc_info(g_media_codec, 48000, 2, bit_depth[i], 128000);
		if (ret == MEDIACODEC_ERROR_NONE)
			break;
	}
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_prepare_n
 * @since_tizen		2.3
 * @description		To prepare mediacodec before feeding data
 */
int utc_media_mediacodec_prepare_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_prepare(NULL);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	for (i = 0; i < 2; i++) {
		ret = mediacodec_set_aenc_info(g_media_codec, 48000, 2, bit_depth[i], 128000);
		if (ret == MEDIACODEC_ERROR_NONE)
			break;
	}
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_prepare(NULL);
	assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_unprepare_p
 * @since_tizen		2.3
 * @description		To unprepare mediacodec before destroying mediacodec
 */
int utc_media_mediacodec_unprepare_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_unprepare(g_media_codec);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	for (i = 0; i < 2; i++) {
		ret = mediacodec_set_aenc_info(g_media_codec, 48000, 2, bit_depth[i], 128000);
		if (ret == MEDIACODEC_ERROR_NONE)
			break;
	}
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_unprepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_unprepare_n
 * @since_tizen		2.3
 * @description		To unprepare mediacodec before destroying mediacodec
 */
int utc_media_mediacodec_unprepare_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_unprepare(NULL);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	for (i = 0; i < 2; i++) {
		ret = mediacodec_set_aenc_info(g_media_codec, 48000, 2, bit_depth[i], 128000);
		if (ret == MEDIACODEC_ERROR_NONE)
			break;
	}
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_unprepare(NULL);
	assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_process_input_p
 * @since_tizen		2.3
 * @description		To queue input buffer to the codec
 */
int utc_media_mediacodec_process_input_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	void *data = NULL;
	unsigned int data_size = 0;
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_process_input(g_media_codec, NULL, NULL);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_H264, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_set_vdec_info(g_media_codec, 640, 480);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	mediacodec_set_input_buffer_used_cb(g_media_codec,
			(mediacodec_input_buffer_used_cb)_mediacodec_empty_buffer_cb,
			g_media_codec);

	_is_positive = true;

	mediacodec_set_output_buffer_available_cb(g_media_codec,
			(mediacodec_output_buffer_available_cb)_mediacodec_fill_buffer_cb,
			g_media_codec);

	mediacodec_set_buffer_status_cb(g_media_codec, _mediacodec_buffer_status_cb, g_media_codec);
	mediacodec_set_eos_cb(g_media_codec,(mediacodec_eos_cb) _mediacodec_eos_cb, g_media_codec);
	mediacodec_set_error_cb(g_media_codec, error_cb, g_media_codec);

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	/* set func. */
	feed_data = feed_vdec_data;

	if(pthread_create(&feeding_thread_id, NULL, (void*)feed_thread_func, NULL)<0) {
		fprintf(stderr, "pthread_create is failed\n");
		return 0;
	}

	usleep(1000);
	pthread_join(feeding_thread_id, NULL);

	sleep(3);

	assert_eq(_feed_called, TRUE);
	_feed_called = FALSE;

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_process_input_n
 * @since_tizen		2.3
 * @description		To queue input buffer to the codec
 */
int utc_media_mediacodec_process_input_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	void *data = NULL;
	unsigned int data_size = 0;
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_process_input(NULL, NULL, NULL);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_MPEG4, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_set_vdec_info(g_media_codec, 640, 480);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	mediacodec_set_input_buffer_used_cb(g_media_codec,
			(mediacodec_input_buffer_used_cb)_mediacodec_empty_buffer_cb,
			g_media_codec);

	_is_positive = true;

	mediacodec_set_output_buffer_available_cb(g_media_codec,
			(mediacodec_output_buffer_available_cb)_mediacodec_fill_buffer_cb,
			g_media_codec);

	mediacodec_set_buffer_status_cb(g_media_codec, _mediacodec_buffer_status_cb, g_media_codec);
	mediacodec_set_eos_cb(g_media_codec,(mediacodec_eos_cb) _mediacodec_eos_cb, g_media_codec);
	mediacodec_set_error_cb(g_media_codec, error_cb, g_media_codec);

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	/* set func. */
	feed_data = feed_vdec_data;

	if(pthread_create(&feeding_thread_id, NULL, (void*)feed_thread_func, NULL) < 0) {
		fprintf(stderr, "pthread_create is failed\n");
		return 0;
	}

	usleep(1000);
	pthread_join(feeding_thread_id, NULL);

	sleep(3);

	assert_eq(_feed_called, TRUE);
	_feed_called = FALSE;

	assert_eq(_errorCB_called, TRUE);
	_errorCB_called = FALSE;

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_get_output_p
 * @since_tizen		2.3
 * @description		To get output packet from dequeued output buffer
 */
int utc_media_mediacodec_get_output_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	void *data = NULL;
	void *input_data = NULL;
	unsigned int data_size = 0;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_get_output(g_media_codec, NULL, NULL);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	for (i = 0; i < 2; i++) {
		ret = mediacodec_set_aenc_info(g_media_codec, 48000, 2, bit_depth[i], 128000);
		if (ret == MEDIACODEC_ERROR_NONE)
			break;
	}
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	mediacodec_set_input_buffer_used_cb(g_media_codec,
			(mediacodec_input_buffer_used_cb)_mediacodec_empty_buffer_cb,
			g_media_codec);

	mediacodec_set_output_buffer_available_cb(g_media_codec,
			(mediacodec_output_buffer_available_cb)_mediacodec_fill_buffer_cb,
			g_media_codec);

	ret = mediacodec_set_error_cb(g_media_codec, error_cb, g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	_is_positive = true;

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	/* set func. */
	feed_data = feed_aenc_data;

	if(pthread_create(&feeding_thread_id, NULL, (void*)feed_thread_func, NULL) < 0) {
		fprintf(stderr, "pthread_create is failed\n");
		return 0;
	}

	usleep(1000);
	pthread_join(feeding_thread_id, NULL);

	sleep(3);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_get_output_n
 * @since_tizen		2.3
 * @description		To get output packet from dequeued output buffer
 */
int utc_media_mediacodec_get_output_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	void *data = NULL;
	void *input_data = NULL;
	unsigned int data_size = 0;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_get_output(NULL, NULL, NULL);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	for (i = 0; i < 2; i++) {
		ret = mediacodec_set_aenc_info(g_media_codec, 48000, 2, bit_depth[i], 128000);
		if (ret == MEDIACODEC_ERROR_NONE)
			break;
	}
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	mediacodec_set_input_buffer_used_cb(g_media_codec,
			(mediacodec_input_buffer_used_cb)_mediacodec_empty_buffer_cb,
			g_media_codec);

	mediacodec_set_output_buffer_available_cb(g_media_codec,
			(mediacodec_output_buffer_available_cb)_mediacodec_fill_buffer_cb,
			g_media_codec);

	ret = mediacodec_set_error_cb(g_media_codec, error_cb, g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	_is_positive = false;

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	/* set func. */
	feed_data = feed_aenc_data;

	if(pthread_create(&feeding_thread_id, NULL, (void*)feed_thread_func, NULL) < 0) {
		fprintf(stderr, "pthread_create is failed\n");
		return 0;
	}

	usleep(1000);
	pthread_join(feeding_thread_id, NULL);

	sleep(3);
	return 0;
}

/**
 * @testcase		utc_media_mediacodec_flush_buffers_p
 * @since_tizen		2.3
 * @description		To flush buffers
 */
int utc_media_mediacodec_flush_buffers_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	void *data = NULL;
	void *input_data = NULL;
	unsigned int data_size = 0;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_flush_buffers(g_media_codec);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	for (i = 0; i < 2; i++) {
		ret = mediacodec_set_adec_info(g_media_codec, 48000, 2, bit_depth[i]);
		if (ret == MEDIACODEC_ERROR_NONE)
			break;
	}
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	mediacodec_set_input_buffer_used_cb(g_media_codec,
			(mediacodec_input_buffer_used_cb)_mediacodec_empty_buffer_cb,
			g_media_codec);

	mediacodec_set_output_buffer_available_cb(g_media_codec,
			(mediacodec_output_buffer_available_cb)_mediacodec_fill_buffer_cb,
			g_media_codec);

	ret = mediacodec_set_error_cb(g_media_codec, error_cb, g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	_is_positive = true;

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	/* set func. */
	feed_data = feed_adec_data;

	if(pthread_create(&feeding_thread_id, NULL, (void*)feed_thread_func, NULL) < 0) {
		fprintf(stderr, "pthread_create is failed\n");
		return 0;
	}

	usleep(1000);
	pthread_join(feeding_thread_id, NULL);


	ret = mediacodec_flush_buffers(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_flush_buffers_n
 * @since_tizen		2.3
 * @description		To flush buffers
 */
int utc_media_mediacodec_flush_buffers_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;
	int bit_depth[] = { 16, 32 };
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_flush_buffers(NULL);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_AAC, (MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	for (i = 0; i < 2; i++) {
		ret = mediacodec_set_aenc_info(g_media_codec, 48000, 2, bit_depth[i], 128000);
		if (ret == MEDIACODEC_ERROR_NONE)
			break;
	}
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_flush_buffers(NULL);
	assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mediacodec_set_input_buffer_used_cb_p
 * @since_tizen		2.3
 * @description		To set the callback for notification of queued buffer
 */
int utc_mediacodec_set_input_buffer_used_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	int i;
	void *data = NULL;
	unsigned int data_size = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_set_input_buffer_used_cb(g_media_codec,
			(mediacodec_input_buffer_used_cb)_mediacodec_empty_buffer_cb,
			g_media_codec);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_H264, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_set_vdec_info(g_media_codec, 640, 480);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	mediacodec_set_input_buffer_used_cb(g_media_codec,
			(mediacodec_input_buffer_used_cb)_mediacodec_empty_buffer_cb,
			g_media_codec);

	_is_positive = true;

	mediacodec_set_output_buffer_available_cb(g_media_codec,
			(mediacodec_output_buffer_available_cb)_mediacodec_fill_buffer_cb,
			g_media_codec);

	mediacodec_set_buffer_status_cb(g_media_codec, _mediacodec_buffer_status_cb, g_media_codec);
	mediacodec_set_eos_cb(g_media_codec,(mediacodec_eos_cb) _mediacodec_eos_cb, g_media_codec);
	mediacodec_set_error_cb(g_media_codec, error_cb, g_media_codec);

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	/* set func. */
	feed_data = feed_vdec_data;

	if(pthread_create(&feeding_thread_id, NULL, (void*)feed_thread_func, NULL) < 0) {
		fprintf(stderr, "pthread_create is failed\n");
		return 0;
	}

	usleep(1000);
	pthread_join(feeding_thread_id, NULL);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	sleep(3);
	assert_eq(_emptybufferCB_called, TRUE);
	_emptybufferCB_called = FALSE;

	return 0;
}

/**
 * @testcase		utc_mediacodec_set_input_buffer_used_cb_n
 * @since_tizen		2.3
 * @description		To set the callback for notification of queued input buffer
 */
int utc_mediacodec_set_input_buffer_used_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_set_input_buffer_used_cb(NULL, NULL, NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_unset_input_buffer_used_cb_p
 * @since_tizen		2.3
 * @description		To unset callback of input_buffer_used_cb
 */
int utc_mediacodec_unset_input_buffer_used_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_unset_input_buffer_used_cb(g_media_codec);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_unset_input_buffer_used_cb_n
 * @since_tizen		2.3
 * @description		To unset callback of input_buffer_used_cb
 */
int utc_mediacodec_unset_input_buffer_used_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_unset_input_buffer_used_cb(NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_set_output_buffer_available_cb_p
 * @since_tizen		2.3
 * @description		To set the callback for notification of dequeued output buffer
 */
int utc_mediacodec_set_output_buffer_available_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_set_output_buffer_available_cb(g_media_codec, fill_cb, fill_data);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_set_output_buffer_available_cb_n
 * @since_tizen		2.3
 * @description		To set the callback for notification of dequeued output buffer
 */
int utc_mediacodec_set_output_buffer_available_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_set_output_buffer_available_cb(NULL, NULL, NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_unset_output_buffer_available_cb_p
 * @since_tizen		2.3
 * @description		To unset callback of output_buffer_available_cb
 */
int utc_mediacodec_unset_output_buffer_available_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_unset_output_buffer_available_cb(g_media_codec);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_unset_output_buffer_available_cb_n
 * @since_tizen		2.3
 * @description		To unset callback of output_buffer_available_cb
 */
int utc_mediacodec_unset_output_buffer_available_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_unset_output_buffer_available_cb(NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_set_error_cb_p
 * @since_tizen		2.3
 * @description		To set the callback for notification of error
 */
int utc_mediacodec_set_error_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_set_error_cb(g_media_codec, error_cb, error_data);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_set_error_cb_n
 * @since_tizen		2.3
 * @description		To set the callback for notification of error
 */
int utc_mediacodec_set_error_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_set_error_cb(NULL, NULL, NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_unset_error_cb_p
 * @since_tizen		2.3
 * @description		To unset error_cb
 */
int utc_mediacodec_unset_error_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_unset_error_cb(g_media_codec);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_unset_error_cb_n
 * @since_tizen		2.3
 * @description		To unset error_cb
 */
int utc_mediacodec_unset_error_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_unset_error_cb(NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_set_eos_cb_p
 * @since_tizen		2.3
 * @description		To set the callback for notification of end-of-stream
 */
int utc_mediacodec_set_eos_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_set_eos_cb(g_media_codec, eos_cb, eos_data);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_set_eos_cb_n
 * @since_tizen		2.3
 * @description		To set the callback for notification of end-of-stream
 */
int utc_mediacodec_set_eos_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_set_eos_cb(NULL,NULL,NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_unset_eos_cb_p
 * @since_tizen		2.3
 * @description		To unset eos_cb
 */
int utc_mediacodec_unset_eos_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_unset_eos_cb(g_media_codec);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_unset_eos_cb_n
 * @since_tizen		2.3
 * @description		To unset eos_cb
 */
int utc_mediacodec_unset_eos_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_unset_eos_cb(NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_foreach_supported_codec_p
 * @since_tizen		2.3
 * @description		To get information of supported codecs
 */
int utc_mediacodec_foreach_supported_codec_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	if (!_mediacodec_supported) {
		ret = mediacodec_foreach_supported_codec(g_media_codec, _mcdiacodec_supported_cb, g_media_codec);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_H264, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_set_vdec_info(g_media_codec, 640, 480);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_foreach_supported_codec(g_media_codec, _mcdiacodec_supported_cb, g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_foreach_supported_codec_n
 * @since_tizen		2.3
 * @description		To get information of supported codecs
 */
int utc_mediacodec_foreach_supported_codec_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_foreach_supported_codec(NULL, NULL, NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_get_supported_type_p
 * @since_tizen		2.3
 * @description		To check if codecs support h/w or s/w
 */
int utc_mediacodec_get_supported_type_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;
	int supported_type;

	ret = mediacodec_get_supported_type(g_media_codec, MEDIACODEC_H264, 1, &supported_type);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_get_supported_type_n
 * @since_tizen		2.3
 * @description		To check if codecs support h/w or s/w
 */
int utc_mediacodec_get_supported_type_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;
	int supported_type;

	ret = mediacodec_get_supported_type(NULL, MEDIACODEC_NONE,  1, &supported_type);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_set_buffer_status_cb_p
 * @since_tizen		2.3
 * @description		To set the callback for notification of buffer status
 */
int utc_mediacodec_set_buffer_status_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_set_buffer_status_cb(g_media_codec, _mediacodec_buffer_status_cb, buffer_data);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_set_buffer_status_cb_n
 * @since_tizen		2.3
 * @description		To set the callback for notification of buffer status
 */
int utc_mediacodec_set_buffer_status_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_set_buffer_status_cb(NULL,NULL,NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_unset_buffer_status_cb_p
 * @since_tizen		2.3
 * @description		To unset buffer_status_cb
 */
int utc_mediacodec_unset_buffer_status_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_unset_buffer_status_cb(g_media_codec);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_mediacodec_unset_buffer_status_cb_n
 * @since_tizen		2.3
 * @description		To unset buffer_status_cb
 */
int utc_mediacodec_unset_buffer_status_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_unset_buffer_status_cb(NULL);
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_get_packet_pool_p
 * @since_tizen		3.0
 * @description		To get the media packet pool from mediacodec
 */
int utc_mediacodec_get_packet_pool_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	void *data = NULL;
	unsigned int data_size = 0;
	int i = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_get_packet_pool(g_media_codec, &pool);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_H264, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_set_vdec_info(g_media_codec, 640, 480);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	mediacodec_set_input_buffer_used_cb(g_media_codec,
			(mediacodec_input_buffer_used_cb)_mediacodec_empty_buffer_cb,
			g_media_codec);

	_is_positive = true;

	mediacodec_set_output_buffer_available_cb(g_media_codec,
			(mediacodec_output_buffer_available_cb)_mediacodec_fill_buffer_cb,
			g_media_codec);

	mediacodec_set_buffer_status_cb(g_media_codec, _mediacodec_buffer_status_cb, g_media_codec);
	mediacodec_set_eos_cb(g_media_codec,(mediacodec_eos_cb) _mediacodec_eos_cb, g_media_codec);
	mediacodec_set_error_cb(g_media_codec, error_cb, g_media_codec);

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_get_packet_pool(g_media_codec, &pool);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	/* set func. */
	feed_data = feed_vdec_data2;

	if(pthread_create(&feeding_thread_id, NULL, (void*)feed_thread_func, NULL)<0) {
		fprintf(stderr, "pthread_create is failed\n");
		return 0;
	}

	usleep(1000);
	pthread_join(feeding_thread_id, NULL);

	sleep(3);

	assert_eq(_feed_called, TRUE);
	_feed_called = FALSE;

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_get_packet_pool_n
 * @since_tizen		3.0
 * @description		Negetive test for getting pool
 */
int utc_mediacodec_get_packet_pool_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	void *data = NULL;
	unsigned int data_size = 0;

	if (!_mediacodec_supported) {
		ret = mediacodec_get_packet_pool(NULL, &pool);
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_set_codec(g_media_codec, MEDIACODEC_H264, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_set_vdec_info(g_media_codec, 640, 480);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	mediacodec_set_input_buffer_used_cb(g_media_codec,
			(mediacodec_input_buffer_used_cb)_mediacodec_empty_buffer_cb,
			g_media_codec);

	_is_positive = true;

	mediacodec_set_output_buffer_available_cb(g_media_codec,
			(mediacodec_output_buffer_available_cb)_mediacodec_fill_buffer_cb,
			g_media_codec);

	mediacodec_set_buffer_status_cb(g_media_codec, _mediacodec_buffer_status_cb, g_media_codec);
	mediacodec_set_eos_cb(g_media_codec,(mediacodec_eos_cb) _mediacodec_eos_cb, g_media_codec);
	mediacodec_set_error_cb(g_media_codec, error_cb, g_media_codec);

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	ret = mediacodec_get_packet_pool(NULL, &pool);
	assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);


	return 0;
}

/**
 * @testcase		utc_media_mediacodec_configure_from_media_format_p
 * @since_tizen		4.0
 * @description		To Sets the codec type and codec default info via media format
 */
int utc_mediacodec_configure_from_media_format_p(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	ret = mediacodec_configure_from_media_format(g_media_codec, vdec_fmt, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	if (_mediacodec_supported) {
		assert_eq(ret, MEDIACODEC_ERROR_NONE);
	} else {
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	ret = mediacodec_prepare(g_media_codec);
	assert_eq(ret, MEDIACODEC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_mediacodec_configure_from_media_format_n
 * @since_tizen		4.0
 * @description		Negative test for configuration via media format
 */
int utc_mediacodec_configure_from_media_format_n(void)
{
	assert(!_is_broken);
	int ret = MEDIACODEC_ERROR_NONE;

	media_format_h format;

	media_format_create(&format);
	media_format_set_video_mime(format, MEDIA_FORMAT_H264_SP);
	media_format_set_video_width(format, 0);	/* invalid width */
	media_format_set_video_height(format, 480);

	ret = mediacodec_configure_from_media_format(g_media_codec, format, (MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW));
	if (_mediacodec_supported)
		assert_eq(ret, MEDIACODEC_ERROR_INVALID_PARAMETER);
	else
		assert_eq(ret, MEDIACODEC_ERROR_NOT_SUPPORTED_ON_DEVICE);

	media_format_unref(format);

	return 0;
}
