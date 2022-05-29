/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <glib.h>
#include <metadata_editor.h>
#include "tct_common.h"

#define CHANGE_NAME "change"
#define API_NAMESPACE "[METADATA-EDITOR]"

static char g_audio_path[PATH_MAX + 1];
static char g_tagless_audio_path[PATH_MAX + 1];
static char g_id3v1_audio_path[PATH_MAX + 1];
static char g_m4a_path[PATH_MAX + 1];
static char g_video_path[PATH_MAX + 1];
static char g_image_path[PATH_MAX + 1];
static char g_nonexist_path[PATH_MAX + 1];
static char g_wav_path[PATH_MAX + 1];
static char g_flac_path[PATH_MAX + 1];
static char g_vorbis_ogg_path[PATH_MAX + 1];
static char g_flac_ogg_path[PATH_MAX + 1];

static metadata_editor_h g_handle = NULL;
static int _startup_error = 0;

typedef enum {
	ME_CONTENT_TYPE_NO_TAG,
	ME_CONTENT_TYPE_NO_TAG_MP3,
	ME_CONTENT_TYPE_ID3v1,
	ME_CONTENT_TYPE_ID3v2,
	ME_CONTENT_TYPE_MP4,
	ME_CONTENT_TYPE_OGG,
	ME_CONTENT_TYPE_ID3v2_MODIFIED,
	ME_CONTENT_TYPE_MP4_MODIFIED,
	ME_CONTENT_TYPE_OGG_MODIFIED,
	ME_CONTENT_TYPE_MAX,
} content_type_e;

static char *tag_value[ME_CONTENT_TYPE_MAX][METADATA_EDITOR_ATTR_UNSYNCLYRICS + 1] = {
	//ME_CONTENT_TYPE_NO_TAG
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "0", NULL, NULL},

	//ME_CONTENT_TYPE_NO_TAG_MP3
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "1", NULL, NULL},

	//ME_CONTENT_TYPE_ID3v1
	{"Test artist",
	"Test title",
	"Test album",
	NULL,
	NULL,
	NULL,
	"2020",
	NULL,
	"Test comment",
	"0",
	"0",
	NULL,
	NULL},

	//ME_CONTENT_TYPE_ID3v2
	{"Test artist",
	"Test title",
	"Test album",
	"13",
	"Test composer",
	"Test copyright",
	"2015",
	"Test description",
	"Test comment",
	"01/01",
	"1",
	"Test conductor",
	"Test lyrics"},

	//ME_CONTENT_TYPE_MP4
	{"Test artist",
	"Test title",
	"Test album",
	"Rock",
	"Test composer",
	"Test copyright",
	"2020",
	"Test description",
	"Test comment",
	"15",
	"0",
	"Test conductor",
	"Test lyrics"},

	//ME_CONTENT_TYPE_OGG
	{"Test artist",
	"Test title",
	"Test album",
	"Rock",
	"Test composer",
	"Test copyright",
	"2020",
	"Test description",
	"Test comment",
	"15",
	"2",
	"Test conductor",
	"Test lyrics"},

	//ME_CONTENT_TYPE_ID3v2_MODIFIED
	{"Test artis modified",
	"Test title modified",
	"Test album modified",
	"15",
	"Test composer modified",
	"Test copyright modified",
	"2016",
	"Test description modified",
	"Test comment modified",
	"02/03",
	"1",
	"Test conductor modified",
	"Test lyrics modified"},

	//ME_CONTENT_TYPE_MP4_MODIFIED
	{"Test artist modified",
	"Test title modified",
	"Test album modified",
	"Pop",
	"Test composer modified",
	"Test copyright modified",
	"2019",
	"Test description modified",
	"Test comment modified",
	"10",
	"0",
	"Test conductor modified",
	"Test lyrics modified"},

	//ME_CONTENT_TYPE_OGG_MODIFIED
	{"Test artist modified",
	"Test title modified",
	"Test album modified",
	"Pop",
	"Test composer modified",
	"Test copyright modified",
	"2019",
	"Test description modified",
	"Test comment modified",
	"10",
	"2",
	"Test conductor modified",
	"Test lyrics modified"}
};

static int __get_metadata(metadata_editor_h handle, content_type_e type)
{
	int ret = METADATA_EDITOR_ERROR_NONE;
	int i = 0;
	char *value = NULL;
	bool failed = false;

	for (i = 0; i <= METADATA_EDITOR_ATTR_UNSYNCLYRICS; i++) {
		ret = metadata_editor_get_metadata(handle, i, &value);
		assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

		if (g_strcmp0(value, tag_value[type][i]) != 0) {
			PRINT_UTC_LOG("[Line : %d][%s] expected [%s] for [%d] but [%s]\\n", __LINE__, __FUNCTION__, (tag_value[type][i]) ? tag_value[type][i] : "(null)", i, (value) ? value : "(null)");

			failed = true;
		}

		FREE_MEMORY(value);
	}

	if (failed)
		return METADATA_EDITOR_ERROR_OPERATION_FAILED;

	return METADATA_EDITOR_ERROR_NONE;
}

/**
 * @function		utc_metadata_editor_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_metadata_editor_startup(void)
{
	char pszValue[CONFIG_VALUE_LEN_MAX] = { 0, };

	if (GetValueForTCTSetting("DEVICE_OTHER_USER_APPS_ROOT_30", pszValue, API_NAMESPACE)) {
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_OTHER_USER_APPS_ROOT_30' Values Received = %s\\n", __LINE__, __FUNCTION__, pszValue);

		snprintf(g_audio_path, PATH_MAX, "%s/core-metadata-editor-tests/data/sample_audio.mp3", pszValue);
		snprintf(g_tagless_audio_path, PATH_MAX, "%s/core-metadata-editor-tests/data/no_tag.mp3", pszValue);
		snprintf(g_id3v1_audio_path, PATH_MAX, "%s/core-metadata-editor-tests/data/id3tag_v1.mp3", pszValue);
		snprintf(g_m4a_path, PATH_MAX, "%s/core-metadata-editor-tests/data/sample_m4a.m4a", pszValue);
		snprintf(g_video_path, PATH_MAX, "%s/core-metadata-editor-tests/data/sample_video.mp4", pszValue);
		snprintf(g_image_path, PATH_MAX, "%s/core-metadata-editor-tests/data/sample.jpg", pszValue);
		snprintf(g_nonexist_path, PATH_MAX, "%s/core-metadata-editor-tests/data/not_exist.mp3", pszValue);
		snprintf(g_wav_path, PATH_MAX, "%s/core-metadata-editor-tests/data/sample_audio.wav", pszValue);
		snprintf(g_flac_path, PATH_MAX, "%s/core-metadata-editor-tests/data/sample_audio.flac", pszValue);
		snprintf(g_vorbis_ogg_path, PATH_MAX, "%s/core-metadata-editor-tests/data/sample_audio.ogg", pszValue);
		snprintf(g_flac_ogg_path, PATH_MAX, "%s/core-metadata-editor-tests/data/sample_audio_flac.ogg", pszValue);
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_USER_30'\\n", __LINE__, __FUNCTION__);
	}

	if (METADATA_EDITOR_ERROR_NONE != metadata_editor_create(&g_handle)) {
		PRINT_UTC_LOG("[Line : %d][%s] fail to metadata_editor_create\\n", __LINE__, __FUNCTION__);
		_startup_error = 1;
	}
}

/**
 * @function		utc_metadata_editor_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_metadata_editor_cleanup(void)
{
	if (g_handle) {
		if (METADATA_EDITOR_ERROR_NONE != metadata_editor_destroy(g_handle))
			PRINT_UTC_LOG("[Line : %d][%s] fail to metadata_editor_destroy\\n", __LINE__, __FUNCTION__);
	}

	memset(&g_audio_path, 0, PATH_MAX + 1);
	memset(&g_tagless_audio_path, 0, PATH_MAX + 1);
	memset(&g_id3v1_audio_path, 0, PATH_MAX + 1);
	memset(&g_m4a_path, 0, PATH_MAX + 1);
	memset(&g_video_path, 0, PATH_MAX + 1);
	memset(&g_image_path, 0, PATH_MAX + 1);
	memset(&g_nonexist_path, 0, PATH_MAX + 1);
	memset(&g_wav_path, 0, PATH_MAX + 1);
	memset(&g_flac_path, 0, PATH_MAX + 1);
	memset(&g_vorbis_ogg_path, 0, PATH_MAX + 1);
	memset(&g_flac_ogg_path, 0, PATH_MAX + 1);
}

/**
 * @testcase		utc_metadata_editor_create_n
 * @since_tizen		2.4
 * @description		Negative test case of metadata_editor_create()
 */
int utc_metadata_editor_create_n(void)
{
	int ret = metadata_editor_create(NULL);

	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_create_p
 * @since_tizen		2.4
 * @description		Positive test case of metadata_editor_create()
 */
int utc_metadata_editor_create_p(void)
{
	assert_eq(_startup_error, 0);

	int ret;
	ret = metadata_editor_destroy(g_handle);
	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_set_path_n
 * @since_tizen		2.4
 * @description		Negative test case of metadata_editor_set_path()
 */
int utc_metadata_editor_set_path_n(void)
{
	assert_eq(_startup_error, 0);

	int ret = metadata_editor_set_path(NULL, g_audio_path);

	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	ret = metadata_editor_set_path(g_handle, NULL);

	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	ret = metadata_editor_set_path(g_handle, g_nonexist_path);

	assert_eq(ret, METADATA_EDITOR_ERROR_FILE_EXISTS);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_set_path_p
 * @since_tizen		2.4
 * @description		Positive test case of metadata_editor_set_path()
 */
int utc_metadata_editor_set_path_p(void)
{
	assert_eq(_startup_error, 0);

	int ret = metadata_editor_set_path(g_handle, g_audio_path);
	ret = metadata_editor_set_path(g_handle, g_video_path);

	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_metadata_n1
 * @since_tizen		2.4
 * @description		Negative test case of metadata_editor_get_metadata()
 */
int utc_metadata_editor_get_metadata_n1(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;
	char *c_value = NULL;

	ret = metadata_editor_get_metadata(NULL, METADATA_EDITOR_ATTR_TITLE, &c_value);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_metadata_n2
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_get_metadata()
 */
int utc_metadata_editor_get_metadata_n2(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;
	char *c_value = NULL;

	ret = metadata_editor_get_metadata(g_handle, METADATA_EDITOR_ATTR_TITLE, &c_value);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_metadata_n3
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_get_metadata()
 */
int utc_metadata_editor_get_metadata_n3(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;
	char *c_value = NULL;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_get_metadata(g_handle, METADATA_EDITOR_ATTR_UNSYNCLYRICS + 1, &c_value);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_metadata_n4
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_get_metadata()
 */
int utc_metadata_editor_get_metadata_n4(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_get_metadata(g_handle, METADATA_EDITOR_ATTR_TITLE, NULL);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_metadata_p1
 * @since_tizen		2.4
 * @description		Positive test case of metadata_editor_get_metadata() for No tag mp3 format
 */
int utc_metadata_editor_get_metadata_p1(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_tagless_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_NO_TAG);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_metadata_p2
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_get_metadata() for ID3tag1 mp3 format
 */
int utc_metadata_editor_get_metadata_p2(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_id3v1_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_ID3v1);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_metadata_p3
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_get_metadata() for ID3tag2 mp3 format
 */
int utc_metadata_editor_get_metadata_p3(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_ID3v2);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_metadata_p4
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_get_metadata() for mp4 format
 */
int utc_metadata_editor_get_metadata_p4(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_video_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_MP4);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_metadata_p5
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_get_metadata() for wav format
 */
int utc_metadata_editor_get_metadata_p5(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_wav_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_ID3v2);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_metadata_p6
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_get_metadata() for flac format
 */
int utc_metadata_editor_get_metadata_p6(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_flac_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_MP4);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_metadata_p7
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_get_metadata() for vorbis ogg format
 */
int utc_metadata_editor_get_metadata_p7(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_vorbis_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_OGG);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_metadata_p8
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_get_metadata() for flac ogg format
 */
int utc_metadata_editor_get_metadata_p8(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_flac_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_OGG);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

static int __set_metadata(metadata_editor_h handle, content_type_e type)
{
	int ret = METADATA_EDITOR_ERROR_NONE;
	int i = 0;

	for (i = 0; i <= METADATA_EDITOR_ATTR_UNSYNCLYRICS; i++) {
		if (i == METADATA_EDITOR_ATTR_PICTURE_NUM)
			continue;

		ret = metadata_editor_set_metadata(handle, i, tag_value[type][i]);
		assert_eq(ret, METADATA_EDITOR_ERROR_NONE);
	}

	return METADATA_EDITOR_ERROR_NONE;
}

/**
 * @testcase		utc_metadata_editor_set_metadata_n1
 * @since_tizen		2.4
 * @description		Negative test case of metadata_editor_set_metadata()
 */
int utc_metadata_editor_set_metadata_n1(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_metadata(NULL, METADATA_EDITOR_ATTR_TITLE, CHANGE_NAME);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_set_metadata_n2
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_set_metadata()
 */
int utc_metadata_editor_set_metadata_n2(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_metadata(g_handle, METADATA_EDITOR_ATTR_TITLE, CHANGE_NAME);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_set_metadata_n3
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_set_metadata()
 */
int utc_metadata_editor_set_metadata_n3(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_metadata(g_handle, METADATA_EDITOR_ATTR_PICTURE_NUM, CHANGE_NAME);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_set_metadata_n4
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_set_metadata()
 */
int utc_metadata_editor_set_metadata_n4(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_metadata(g_handle, METADATA_EDITOR_ATTR_UNSYNCLYRICS + 1, CHANGE_NAME);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_set_metadata_p1
 * @since_tizen		2.4
 * @description		Positive test case of metadata_editor_set_metadata() for mp3 format
 */
int utc_metadata_editor_set_metadata_p1(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_ID3v2_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_set_metadata_p2
 * @since_tizen 	6.0
 * @description 	Positive test case of metadata_editor_set_metadata() for mp4 format
 */
int utc_metadata_editor_set_metadata_p2(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_video_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_MP4_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_set_metadata_p3
 * @since_tizen 	6.0
 * @description 	Positive test case of metadata_editor_set_metadata() for wav format
 */
int utc_metadata_editor_set_metadata_p3(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_wav_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_ID3v2_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_set_metadata_p4
 * @since_tizen 	6.0
 * @description 	Positive test case of metadata_editor_set_metadata() for flac format
 */
int utc_metadata_editor_set_metadata_p4(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_flac_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_MP4_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_set_metadata_p5
 * @since_tizen 	6.0
 * @description 	Positive test case of metadata_editor_set_metadata() for vorbis ogg format
 */
int utc_metadata_editor_set_metadata_p5(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_vorbis_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_OGG_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_set_metadata_p6
 * @since_tizen 	6.0
 * @description 	Positive test case of metadata_editor_set_metadata() for flac ogg format
 */
int utc_metadata_editor_set_metadata_p6(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_flac_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_OGG_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_update_metadata_n
 * @since_tizen		2.4
 * @description		Negative test case of metadata_editor_update_metadata()
 */
int utc_metadata_editor_update_metadata_n(void)
{
	assert_eq(_startup_error, 0);

	int ret = metadata_editor_update_metadata(NULL);

	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_update_metadata_p1
 * @since_tizen		2.4
 * @description		Positive test case of metadata_editor_update_metadata() for mp3 format
 */
int utc_metadata_editor_update_metadata_p1(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_ID3v2_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_ID3v2_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_update_metadata_p2
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_update_metadata() for mp4 format
 */
int utc_metadata_editor_update_metadata_p2(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_video_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_MP4_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_video_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_MP4_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

static int __get_picture(metadata_editor_h handle, const char *num)
{
	int ret = METADATA_EDITOR_ERROR_NONE;
	char *value = NULL;
	int pic_num = 0;
	int i = 0;
	void *picture = NULL;
	int picture_size = 0;
	char *type = NULL;

	ret = metadata_editor_get_metadata(handle, METADATA_EDITOR_ATTR_PICTURE_NUM, &value);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	if (g_strcmp0(value, num) != 0) {
		PRINT_UTC_LOG("[Line : %d][%s] expected [%s] but [%s]\\n", __LINE__, __FUNCTION__, num, (value) ? value : "(null)");
		ret = METADATA_EDITOR_ERROR_OPERATION_FAILED;
	}

	FREE_MEMORY(value);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	pic_num = g_ascii_strtoll(num, NULL, 10);

	for (i = 0; i < pic_num; i++) {

		ret = metadata_editor_get_picture(handle, i, &picture, &picture_size, &type);
		assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

		if (!picture) {
			PRINT_UTC_LOG("[Line : %d][%s] fail to get picture\\n", __LINE__, __FUNCTION__);
			ret = METADATA_EDITOR_ERROR_OPERATION_FAILED;
		}

		if (picture_size == 0) {
			PRINT_UTC_LOG("[Line : %d][%s] fail to get picture size\\n", __LINE__, __FUNCTION__);
			ret = METADATA_EDITOR_ERROR_OPERATION_FAILED;
		}

		if (!type) {
			PRINT_UTC_LOG("[Line : %d][%s] fail to get picture type\\n", __LINE__, __FUNCTION__);
			ret = METADATA_EDITOR_ERROR_OPERATION_FAILED;
		}

		FREE_MEMORY(picture);
		FREE_MEMORY(type);

		assert_eq(ret, METADATA_EDITOR_ERROR_NONE);
	}

	return METADATA_EDITOR_ERROR_NONE;
}

/**
 * @testcase		utc_metadata_editor_update_metadata_p3
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_update_metadata() for mp3 format
 */
int utc_metadata_editor_update_metadata_p3(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_NO_TAG);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_NO_TAG_MP3);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_update_metadata_p4
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_update_metadata() for mp4 format
 */
int utc_metadata_editor_update_metadata_p4(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_video_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_NO_TAG);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_video_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_NO_TAG);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_update_metadata_p5
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_update_metadata() for wav format
 */
int utc_metadata_editor_update_metadata_p5(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_wav_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_ID3v2_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_wav_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_ID3v2_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_update_metadata_p6
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_update_metadata() for flac format
 */
int utc_metadata_editor_update_metadata_p6(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_flac_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_MP4_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_flac_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_MP4_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_update_metadata_p7
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_update_metadata() for vorbis ogg format
 */
int utc_metadata_editor_update_metadata_p7(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_vorbis_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_OGG_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_vorbis_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_OGG_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_update_metadata_p8
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_update_metadata() for flac ogg format
 */
int utc_metadata_editor_update_metadata_p8(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_flac_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __set_metadata(g_handle, ME_CONTENT_TYPE_OGG_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_flac_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_metadata(g_handle, ME_CONTENT_TYPE_OGG_MODIFIED);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_picture_n1
 * @since_tizen		2.4
 * @description		Negative test case of metadata_editor_get_picture()
 */
int utc_metadata_editor_get_picture_n1(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;
	int size = 0;
	void *picture = NULL;
	char *type = NULL;

	ret = metadata_editor_get_picture(NULL, 0, &picture, &size, &type);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_picture_n2
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_get_picture()
 */
int utc_metadata_editor_get_picture_n2(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;
	int size = 0;
	void *picture = NULL;
	char *type = NULL;

	ret = metadata_editor_get_picture(g_handle, 0, &picture, &size, &type);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_picture_n3
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_get_picture()
 */
int utc_metadata_editor_get_picture_n3(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;
	char *type = NULL;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_get_picture(g_handle, 0, NULL, NULL, &type);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_picture_n4
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_get_picture()
 */
int utc_metadata_editor_get_picture_n4(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;
	int size = 0;
	void *picture = NULL;
	char *type = NULL;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_get_picture(g_handle, 1, &picture, &size, &type);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_get_picture_p
 * @since_tizen		2.4
 * @description		Positive test case of metadata_editor_get_picture()
 */
int utc_metadata_editor_get_picture_p(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "1");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_append_picture_n1
 * @since_tizen		2.4
 * @description		Negative test case of metadata_editor_append_picture()
 */
int utc_metadata_editor_append_picture_n1(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_append_picture(NULL, g_image_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_append_picture_n2
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_append_picture()
 */
int utc_metadata_editor_append_picture_n2(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_append_picture(g_handle, g_image_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_append_picture_n3
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_append_picture()
 */
int utc_metadata_editor_append_picture_n3(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_append_picture(g_handle, NULL);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_append_picture_n4
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_append_picture()
 */
int utc_metadata_editor_append_picture_n4(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_append_picture(g_handle, g_nonexist_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_FILE_EXISTS);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_append_picture_p1
 * @since_tizen		2.4
 * @description		Positive test case of metadata_editor_append_picture() for mp3 format
 */
int utc_metadata_editor_append_picture_p1(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_append_picture(g_handle, g_image_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "2");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_append_picture_p2
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_append_picture() for mp4 format
 */
int utc_metadata_editor_append_picture_p2(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_video_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_append_picture(g_handle, g_image_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_video_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "1");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_append_picture_p3
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_append_picture() for m4a format
 */
int utc_metadata_editor_append_picture_p3(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_m4a_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_append_picture(g_handle, g_image_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_append_picture(g_handle, g_image_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_m4a_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "3");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_append_picture_p4
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_append_picture() for wav format
 */
int utc_metadata_editor_append_picture_p4(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_wav_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_append_picture(g_handle, g_image_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_wav_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "2");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_append_picture_p5
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_append_picture() for flac format
 */
int utc_metadata_editor_append_picture_p5(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_flac_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_append_picture(g_handle, g_image_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_flac_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "1");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_append_picture_p6
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_append_picture() for vorbis ogg format
 */
int utc_metadata_editor_append_picture_p6(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_vorbis_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_append_picture(g_handle, g_image_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_vorbis_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "3");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_append_picture_p7
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_append_picture() for flac ogg format
 */
int utc_metadata_editor_append_picture_p7(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_flac_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_append_picture(g_handle, g_image_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_flac_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "3");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_remove_picture_n1
 * @since_tizen		2.4
 * @description		Negative test case of metadata_editor_remove_picture()
 */
int utc_metadata_editor_remove_picture_n1(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_remove_picture(NULL, 0);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_remove_picture_n2
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_remove_picture()
 */
int utc_metadata_editor_remove_picture_n2(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_remove_picture(g_handle, 0);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_remove_picture_n3
 * @since_tizen		6.0
 * @description		Negative test case of metadata_editor_remove_picture()
 */
int utc_metadata_editor_remove_picture_n3(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_remove_picture(g_handle, 3);
	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_remove_picture_p1
 * @since_tizen		2.4
 * @description		Positive test case of metadata_editor_remove_picture() for mp3 format
 */
int utc_metadata_editor_remove_picture_p1(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_remove_picture(g_handle, 1);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_audio_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "1");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_remove_picture_p2
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_remove_picture() for mp4 format
 */
int utc_metadata_editor_remove_picture_p2(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_m4a_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_remove_picture(g_handle, 0);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_m4a_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "2");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_remove_picture_p3
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_remove_picture() for wav format
 */
int utc_metadata_editor_remove_picture_p3(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_wav_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_remove_picture(g_handle, 0);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_wav_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "1");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_remove_picture_p4
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_remove_picture() for flac format
 */
int utc_metadata_editor_remove_picture_p4(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_flac_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_remove_picture(g_handle, 0);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_flac_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "0");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_remove_picture_p5
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_remove_picture() for vorbis ogg format
 */
int utc_metadata_editor_remove_picture_p5(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_vorbis_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_remove_picture(g_handle, 0);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_vorbis_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "2");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_remove_picture_p6
 * @since_tizen		6.0
 * @description		Positive test case of metadata_editor_remove_picture() for flac ogg format
 */
int utc_metadata_editor_remove_picture_p6(void)
{
	assert_eq(_startup_error, 0);

	int ret = METADATA_EDITOR_ERROR_NONE;

	ret = metadata_editor_set_path(g_handle, g_flac_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_remove_picture(g_handle, 0);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_update_metadata(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_destroy(g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_create(&g_handle);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = metadata_editor_set_path(g_handle, g_flac_ogg_path);
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	ret = __get_picture(g_handle, "2");
	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of metadata_editor_destroy()
 */
int utc_metadata_editor_destroy_n(void)
{
	assert_eq(_startup_error, 0);
	int ret = metadata_editor_destroy(NULL);

	assert_eq(ret, METADATA_EDITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_metadata_editor_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of metadata_editor_destroy()
 */
int utc_metadata_editor_destroy_p(void)
{
	assert_eq(_startup_error, 0);

	int ret = metadata_editor_set_path(g_handle, g_audio_path);
	ret = metadata_editor_destroy(g_handle);
	g_handle = NULL;

	assert_eq(ret, METADATA_EDITOR_ERROR_NONE);

	return 0;
}
