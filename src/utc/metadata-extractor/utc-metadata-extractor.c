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

#include <metadata_extractor.h>
#include <limits.h>
#include "tct_common.h"

#define API_NAMESPACE "[METADATA-EXTRACTOR]"
#define MAX_LEN 64
#define READ_FROM_FILE(FILE_PATH, data, size) \
do{	\
	FILE *fp = fopen(FILE_PATH, "r");	\
	if (fp) {	\
			int read_size = 0;  \
			fseek(fp, 0, SEEK_END);	\
			size = (int)ftell(fp);	\
			fseek(fp, 0, SEEK_SET);	\
			data = malloc(size);	\
			assert_neq(data, NULL);	\
			read_size = (int)fread(data, size, sizeof(char), fp);	\
			fclose(fp);	\
			PRINT_UTC_LOG("file_size = %d read_size = %d\n", size, read_size);	\
			if (read_size == 0 && ferror(fp)) {	\
				free(data);	\
				assert(false);	\
			}	\
	}	\
}while(0)

static const char *video = "movie.mp4";
static const char *audio = "sound.mp3";
static char video_path[PATH_MAX + 1] = { 0, };
static char audio_path[PATH_MAX + 1] = { 0, };

static char audio_test_value[][MAX_LEN] = { "23646",
	"0",
	"0",
	"0",
	"0",
	"0",
	"32000",
	"2",
	"44100",
	"0",
	"1",
	"Test",
	"Test",
	"Test",
	"Test album artist",
	"Test",
	"Test",
	"Test",
	"2001",
	"METADATA_DESCRIPTION",
	"Test",
	"1",
	"METADATA_CLASSIFICATION",
	"METADATA_RATING",
	"0.000000",
	"0.000000",
	"0.000000",
	"Test",
	"Test",
	"0",
	"2001-1-1",
	"METADATA_ROTATE",
	"METADATA_VIDEO_CODEC",
	"MP3",
	"0"
};

static char video_test_value[][MAX_LEN] = { "11883",
	"909428",
	"30",
	"320",
	"240",
	"1",
	"44512",
	"2",
	"48000",
	"16",
	"1",
	"Test",
	"Test",
	"Test",
	"METADATA_ALBUM_ARTIST",
	"Test",
	"Test",
	"Test",
	"2001-1-1",
	"Test",
	"Test",
	"1/31144",
	"METADATA_CLASSIFICATION",
	"METADATA_RATING",
	"0.000000",
	"0.000000",
	"0.000000",
	"METADATA_CONDUCTOR",
	"Test",
	"0",
	"2014-01-01 09:01:11",
	"90",
	"MPEG4",
	"AAC",
	"0"
};

static metadata_extractor_h g_metadata_h = NULL;
static int _startup_error = 0;

/**
 * @function		utc_metadata_extractor_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_metadata_extractor_startup(void)
{
	char pszValue[CONFIG_VALUE_LEN_MAX] = { 0, };

	if (GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE, pszValue);

		snprintf(video_path, PATH_MAX, "%s/res/%s", pszValue, video);
		snprintf(audio_path, PATH_MAX, "%s/res/%s", pszValue, audio);
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	if (METADATA_EXTRACTOR_ERROR_NONE != metadata_extractor_create(&g_metadata_h)) {
		_startup_error = 1;
	}

}

/**
 * @function		utc_metadata_extractor_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_metadata_extractor_cleanup(void)
{
	if (g_metadata_h) {
		if (METADATA_EXTRACTOR_ERROR_NONE != metadata_extractor_destroy(g_metadata_h)) {
			fprintf(stderr, "Cleanup function error - can affect other tests.");
		}
		g_metadata_h = NULL;
	}

	memset(&audio_path, 0, PATH_MAX + 1);
	memset(&video_path, 0, PATH_MAX + 1);
}

/**
 * @testcase		utc_metadata_extractor_create_n
 * @since_tizen		2.3
 * @description		Negative test case of metadata_extractor_create()
 */
int utc_metadata_extractor_create_n(void)
{
	int ret = metadata_extractor_create(NULL);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_create_p
 * @since_tizen		2.3
 * @description		Positive test case of metadata_extractor_create()
 */
int utc_metadata_extractor_create_p(void)
{
	assert_eq(_startup_error, 0);

	int ret;

	ret = metadata_extractor_destroy(g_metadata_h);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	ret = metadata_extractor_create(&g_metadata_h);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_set_path_n1
 * @since_tizen		2.3
 * @description		First negative test case of metadata_extractor_set_path() - invalid metadata_extractor_h
 */
int utc_metadata_extractor_set_path_n1(void)
{
	int ret = metadata_extractor_set_path(NULL, NULL);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_set_path_n2
 * @since_tizen		2.3
 * @description		Second negative test case of metadata_extractor_set_path() - invalid path
 */
int utc_metadata_extractor_set_path_n2(void)
{
	assert_eq(_startup_error, 0);

	int ret = metadata_extractor_set_path(g_metadata_h, NULL);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);

	ret = metadata_extractor_set_path(g_metadata_h, "file_exist_test.mp3");

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_FILE_EXISTS);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_set_path_p
 * @since_tizen		2.3
 * @description		Positive test case of metadata_extractor_set_path()
 */
int utc_metadata_extractor_set_path_p(void)
{
	assert_eq(_startup_error, 0);

	int ret = metadata_extractor_set_path(g_metadata_h, video_path);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	ret = metadata_extractor_set_path(g_metadata_h, audio_path);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_set_buffer_n1
 * @since_tizen		2.3
 * @description		First negative test case of metadata_extractor_set_buffer() - invalid metadata_extractor_h
 */
int utc_metadata_extractor_set_buffer_n1(void)
{
	void *buffer = NULL;
	int size = 0, ret;

	READ_FROM_FILE(audio_path, buffer, size);

	ret = metadata_extractor_set_buffer(NULL, buffer, size);
	FREE_MEMORY(buffer);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_set_buffer_n2
 * @since_tizen		2.3
 * @description		Second negative test case of metadata_extractor_set_buffer() - invalid buffer
 */
int utc_metadata_extractor_set_buffer_n2(void)
{
	assert_eq(_startup_error, 0);

	int ret = metadata_extractor_set_buffer(g_metadata_h, NULL, 0);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_set_buffer_p
 * @since_tizen		2.3
 * @description		Positive test case of metadata_extractor_set_buffer()
 */
int utc_metadata_extractor_set_buffer_p(void)
{
	assert_eq(_startup_error, 0);

	void *buffer = NULL;
	int size = 0, ret;

	READ_FROM_FILE(audio_path, buffer, size);

	ret = metadata_extractor_set_buffer(g_metadata_h, buffer, size);
	FREE_MEMORY(buffer);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	READ_FROM_FILE(video_path, buffer, size);

	ret = metadata_extractor_set_buffer(g_metadata_h, buffer, size);
	FREE_MEMORY(buffer);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_metadata_n
 * @since_tizen		2.3
 * @description		Negative test case of metadata_extractor_get_metadata()
 */
int utc_metadata_extractor_get_metadata_n(void)
{
	int attr, ret;
	char *value = NULL;

	for (attr = 0; attr < (METADATA_360 + 1); attr++) {
		ret = metadata_extractor_get_metadata(NULL, attr, &value);
		FREE_MEMORY(value);

		assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);
	}

	ret = metadata_extractor_set_path(g_metadata_h, audio_path);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	ret = metadata_extractor_get_metadata(g_metadata_h, -1, &value);
	FREE_MEMORY(value);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_metadata_p1
 * @since_tizen		2.3
 * @description		Positive test case of metadata_extractor_get_metadata() to file
 */
int utc_metadata_extractor_get_metadata_p1(void)
{
	assert_eq(_startup_error, 0);

	int attr, ret;
	char *value = NULL;

	ret = metadata_extractor_set_path(g_metadata_h, audio_path);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	for (attr = 0; attr < (METADATA_360 + 1); attr++) {
		if (attr == METADATA_VIDEO_CODEC)
			continue;

		ret = metadata_extractor_get_metadata(g_metadata_h, attr, &value);
		assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

		if (value) {
			if (strcmp(value, audio_test_value[attr]) == 0)
				ret = METADATA_EXTRACTOR_ERROR_NONE;
			else
				ret = METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER;
		}
		FREE_MEMORY(value);

		assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_metadata_p2
 * @since_tizen		2.3
 * @description		Positive test case of metadata_extractor_get_metadata() to buffer
 */
int utc_metadata_extractor_get_metadata_p2(void)
{
	assert_eq(_startup_error, 0);

	int attr, ret;
	char *value = NULL;
	void *buffer = NULL;
	int size = 0;

	READ_FROM_FILE(audio_path, buffer, size);

	ret = metadata_extractor_set_buffer(g_metadata_h, buffer, size);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	for (attr = 0; attr < (METADATA_360 + 1); attr++) {
		if (attr == METADATA_VIDEO_CODEC)
			continue;

		ret = metadata_extractor_get_metadata(g_metadata_h, attr, &value);
		assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

		if (value) {
			if (strcmp(value, audio_test_value[attr]) == 0)
				ret = METADATA_EXTRACTOR_ERROR_NONE;
			else
				ret = METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER;
		}
		FREE_MEMORY(value);

		assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);
	}

	FREE_MEMORY(buffer);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_metadata_p3
 * @since_tizen		2.3
 * @description		Positive test case of metadata_extractor_get_metadata()
 */
int utc_metadata_extractor_get_metadata_p3(void)
{
	assert_eq(_startup_error, 0);

	int attr, ret;
	char *value = NULL;

	ret = metadata_extractor_set_path(g_metadata_h, video_path);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	for (attr = 0; attr < (METADATA_360 + 1); attr++) {
		ret = metadata_extractor_get_metadata(g_metadata_h, attr, &value);
		assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

		if (value) {
			if (strcmp(value, video_test_value[attr]) == 0)
				ret = METADATA_EXTRACTOR_ERROR_NONE;
			else
				ret = METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER;
		}
		FREE_MEMORY(value);

		assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_artwork_n
 * @since_tizen		2.3
 * @description		Negative test case of metadata_extractor_get_artwork()
 */
int utc_metadata_extractor_get_artwork_n(void)
{
	int ret, artwork_size = 0;
	void *artwork = NULL;
	char *artwork_mime = NULL;

	ret = metadata_extractor_get_artwork(NULL, &artwork, &artwork_size, &artwork_mime);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_artwork_p
 * @since_tizen		2.3
 * @description		Positive test case of metadata_extractor_get_artwork()
 */
int utc_metadata_extractor_get_artwork_p(void)
{
	assert_eq(_startup_error, 0);

	int ret, artwork_size = 0;
	void *artwork = NULL;
	char *artwork_mime = NULL;

	ret = metadata_extractor_set_path(g_metadata_h, audio_path);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	ret = metadata_extractor_get_artwork(g_metadata_h, &artwork, &artwork_size, &artwork_mime);

	FREE_MEMORY(artwork);
	FREE_MEMORY(artwork_mime);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	ret = metadata_extractor_set_path(g_metadata_h, video_path);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	ret = metadata_extractor_get_artwork(g_metadata_h, &artwork, &artwork_size, &artwork_mime);

	FREE_MEMORY(artwork);
	FREE_MEMORY(artwork_mime);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_frame_n
 * @since_tizen		2.3
 * @description		Negative test case of metadata_extractor_get_frame()
 */
int utc_metadata_extractor_get_frame_n(void)
{
	int ret, frame_size = 0;
	void *frame = NULL;

	ret = metadata_extractor_get_frame(NULL, &frame, &frame_size);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_frame_p
 * @since_tizen		2.3
 * @description		Positive test case of metadata_extractor_get_frame()
 */
int utc_metadata_extractor_get_frame_p(void)
{
	assert_eq(_startup_error, 0);

	int ret, frame_size = 0;
	void *frame = NULL;

	ret = metadata_extractor_set_path(g_metadata_h, video_path);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	ret = metadata_extractor_get_frame(g_metadata_h, &frame, &frame_size);
	FREE_MEMORY(frame);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_frame_at_time_n
 * @since_tizen		2.3
 * @description		Negative test case of metadata_extractor_get_frame_at_time()
 */
int utc_metadata_extractor_get_frame_at_time_n(void)
{
	int ret, frame_size = 0;
	void *frame = NULL;

	ret = metadata_extractor_get_frame_at_time(NULL, 0, true, &frame, &frame_size);
	FREE_MEMORY(frame);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_frame_at_time_p
 * @since_tizen		2.3
 * @description		Positive test case of metadata_extractor_get_frame_at_time()
 */
int utc_metadata_extractor_get_frame_at_time_p(void)
{
	assert_eq(_startup_error, 0);

	int ret, frame_size = 0;
	void *frame = NULL;

	ret = metadata_extractor_set_path(g_metadata_h, video_path);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	ret = metadata_extractor_get_frame_at_time(g_metadata_h, 1, true, &frame, &frame_size);
	FREE_MEMORY(frame);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_synclyrics_n1
 * @since_tizen		2.3
 * @description		First negative test case of metadata_extractor_get_synclyrics() - invalid metadata_extractor_h
 */
int utc_metadata_extractor_get_synclyrics_n1(void)
{
	int ret;
	unsigned long time_info = 0;
	char *lyrics = NULL;

	ret = metadata_extractor_get_synclyrics(NULL, 1, &time_info, &lyrics);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_synclyrics_n2
 * @since_tizen		2.3
 * @description		Second negative test case of metadata_extractor_get_synclyrics() - invalid index of lyric
 */
int utc_metadata_extractor_get_synclyrics_n2(void)
{
	int ret, lyricsNum;
	unsigned long time_info = 0;
	char *lyrics = NULL;
	char *value = NULL;

	ret = metadata_extractor_set_path(g_metadata_h, video_path);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	ret = metadata_extractor_get_metadata(g_metadata_h, METADATA_SYNCLYRICS_NUM, &value);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	lyricsNum = atoi((char *)value);
	FREE_MEMORY(value);

	ret = metadata_extractor_get_synclyrics(NULL, lyricsNum + 1, &time_info, &lyrics);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_get_synclyrics_p
 * @since_tizen		2.3
 * @description		Positive test case of metadata_extractor_get_synclyrics()
 */
int utc_metadata_extractor_get_synclyrics_p(void)
{
	assert_eq(_startup_error, 0);

	int ret;
	unsigned long time_info = 0;
	char *lyrics = NULL;
	char *value = NULL;

	ret = metadata_extractor_set_path(g_metadata_h, video_path);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	ret = metadata_extractor_get_metadata(g_metadata_h, METADATA_SYNCLYRICS_NUM, &value);
	assert(value);
	FREE_MEMORY(value);
	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	ret = metadata_extractor_get_synclyrics(g_metadata_h, 1, &time_info, &lyrics);
	FREE_MEMORY(lyrics);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of metadata_extractor_destroy()
 */
int utc_metadata_extractor_destroy_n(void)
{
	int ret = metadata_extractor_destroy(NULL);

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_extractor_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of metadata_extractor_destroy()
 */
int utc_metadata_extractor_destroy_p(void)
{
	assert_eq(_startup_error, 0);

	int ret = metadata_extractor_destroy(g_metadata_h);
	g_metadata_h = NULL;

	assert_eq(ret, METADATA_EXTRACTOR_ERROR_NONE);

	return 0;
}
