
#include "assert.h"
#include <mediademuxer.h>
#include <glib.h>
#include <media_packet.h>
#include <media_format.h>
#include <storage.h>
#include "tct_common.h"

#define API_NAMESPACE			"[MEDIAMUXER]"

//& set: Mediademuxer
static mediademuxer_h g_media_demuxer = NULL;

static bool _is_broken = false;
static bool audio_eos_track = false;

static char *file_path = NULL;
static char *uri = NULL;

static bool error_cb(mediademuxer_error_e error, void *user_data)
{
	g_print("error_cb is called\n");
	return true;
}

void eos_cb(int track_index, void *user_data)
{
	audio_eos_track = true;
	printf("Got EOS for track -- %d from Mediademuxer\n", track_index);
	return;
}

/**
 * @function		utc_mediademuxer_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_mediademuxer_startup(void)
{
	int ret;
	_is_broken = false;
	audio_eos_track = false;
	if (uri == NULL) {
		char pszValue[CONFIG_VALUE_LEN_MAX] = { 0, };
		if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
			PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE, pszValue);
			file_path = (char *)malloc(strlen(pszValue) + strlen("sample.mp4") + 6);
			if (!file_path) {
				PRINT_UTC_LOG("[Line : %d][%s] Fail to malloc file_path\n", __LINE__, API_NAMESPACE);
				_is_broken = true;
				return;
			}
			snprintf(file_path, strlen(pszValue) + strlen("sample.mp4") + 6, "%s/res/%s", pszValue, "sample.mp4");
		} else {
			PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
		}

		uri = file_path;
	}
	if (g_media_demuxer == NULL) {
		ret = mediademuxer_create(&g_media_demuxer);
		if (ret != MEDIADEMUXER_ERROR_NONE) {
			_is_broken = true;
			return;
		}
	}
	ret = mediademuxer_set_eos_cb(g_media_demuxer, (mediademuxer_eos_cb)eos_cb, g_media_demuxer);
	if (ret != MEDIADEMUXER_ERROR_NONE) {
		_is_broken = true;
		return;
	}
}

/**
 * @function		utc_mediademuxer_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_mediademuxer_cleanup(void)
{
	int ret;
	mediademuxer_state state;
	/*   if(storage_foreach_device_supported(storage_device_cb, NULL) != STORAGE_ERROR_NONE)
	   {
	   fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
	   } */
	if (g_media_demuxer != NULL) {
		if (mediademuxer_get_state(g_media_demuxer, &state) == MEDIADEMUXER_ERROR_NONE) {
			if (state == MEDIADEMUXER_STATE_DEMUXING) {
				ret = mediademuxer_stop(g_media_demuxer);
			}
		}
		if (mediademuxer_get_state(g_media_demuxer, &state) == MEDIADEMUXER_ERROR_NONE) {
			if (state == MEDIADEMUXER_STATE_READY) {
				ret = mediademuxer_unprepare(g_media_demuxer);
			}
		}

		ret = mediademuxer_unset_eos_cb(g_media_demuxer);

		ret = mediademuxer_destroy(g_media_demuxer);
		g_media_demuxer = NULL;
	}

	if (file_path) {
		free(file_path);
		file_path = NULL;
		uri = NULL;
	}

}

//& purpose: A purpose of a first positive TC.

//& purpose: A purpose of a first negative TC.

/**
 * @testcase		utc_mediademuxer_create_p
 * @since_tizen		3.0
 * @description		Positive Test Case for mediademuxer creation
 */
int utc_mediademuxer_create_p(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	if (g_media_demuxer) {
		ret = mediademuxer_destroy(g_media_demuxer);
		g_media_demuxer = NULL;
	}
	ret = mediademuxer_create(&g_media_demuxer);
	assert_neq(g_media_demuxer, NULL);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mediademuxer_create_n
 * @since_tizen		3.0
 * @description		Negative Test Case for mediademuxer creation
 */
int utc_mediademuxer_create_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_create(&g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_mediademuxer_set_data_source_p
 * @since_tizen		3.0
 * @description		Positive Test Case for setting data source
 */
int utc_mediademuxer_set_data_source_p(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;

}

/**
 * @testcase		utc_mediademuxer_set_data_source_n
 * @since_tizen		3.0
 * @description		Negative Test Case for setting data source
 */
int utc_mediademuxer_set_data_source_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_data_source(g_media_demuxer, NULL);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_PATH);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_set_data_source_n2
 * @since_tizen		3.0
 * @description		Negative Test Case for setting data source
 */
int utc_mediademuxer_set_data_source_n2(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	ret = mediademuxer_prepare(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_STATE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_prepare_p
 * @since_tizen		3.0
 * @description		Positive Test Case for preparing demuxer
 */
int utc_mediademuxer_prepare_p(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_data_source(g_media_demuxer, uri);

	ret = mediademuxer_prepare(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_prepare_n
 * @since_tizen		3.0
 * @description		Negative Test Case for preparing demuxer
 */
int utc_mediademuxer_prepare_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	ret = mediademuxer_prepare(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	ret = mediademuxer_prepare(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_STATE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_get_track_count_p
 * @since_tizen		3.0
 * @description		Positive Test Case for getting track count
 */
int utc_mediademuxer_get_track_count_p(void)
{
	int count;
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	ret = mediademuxer_prepare(g_media_demuxer);
	ret = mediademuxer_get_track_count(g_media_demuxer, &count);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_get_track_count_n
 * @since_tizen		3.0
 * @description		Negative Test Case for getting track count
 */
int utc_mediademuxer_get_track_count_n(void)
{
	int count;
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_get_track_count(g_media_demuxer, &count);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_STATE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_get_track_info_p
 * @since_tizen		3.0
 * @description		Positive Test Case for getting track info
 */
int utc_mediademuxer_get_track_info_p(void)
{
	int count;
	int ret;
	int track_index = 0;
	media_format_h media_format = NULL;

	if (g_media_demuxer == NULL) {
		ret = mediademuxer_create(&g_media_demuxer);
	}

	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	ret = mediademuxer_prepare(g_media_demuxer);
	ret = mediademuxer_get_track_count(g_media_demuxer, &count);
	ret = mediademuxer_get_track_info(g_media_demuxer, track_index, &media_format);
	media_format_unref(media_format);

	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_get_track_info_n
 * @since_tizen		3.0
 * @description		Negative Test Case for getting track info
 */
int utc_mediademuxer_get_track_info_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;
	media_format_h media_format = NULL;
	ret = mediademuxer_get_track_info(g_media_demuxer, 1, &media_format);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_STATE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_select_track_p
 * @since_tizen		3.0
 * @description		Positive Test Case for selecting track
 */
int utc_mediademuxer_select_track_p(void)
{
	int track_index = 0;
	assert(!_is_broken);

	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	ret = mediademuxer_prepare(g_media_demuxer);
	ret = mediademuxer_select_track(g_media_demuxer, track_index);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_select_track_n
 * @since_tizen		3.0
 * @description		Negative Test Case for selecting track
 */
int utc_mediademuxer_select_track_n(void)
{

	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_select_track(g_media_demuxer, 0);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_STATE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_start_p
 * @since_tizen		3.0
 * @description		Positive Test Case for starting demuxing process
 */
int utc_mediademuxer_start_p(void)
{
	assert(!_is_broken);

	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_data_source(g_media_demuxer, uri);

	ret = mediademuxer_prepare(g_media_demuxer);
	ret = mediademuxer_select_track(g_media_demuxer, 0);
	ret = mediademuxer_start(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_start_n
 * @since_tizen		3.0
 * @description		Negative Test Case for starting demuxing process
 */
int utc_mediademuxer_start_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;
	ret = mediademuxer_start(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_STATE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_read_sample_p
 * @since_tizen		3.0
 * @description		Positive Test Case for reading a frame
 */
int utc_mediademuxer_read_sample_p(void)
{
	assert(!_is_broken);
	media_packet_h audbuf;
	media_format_h audfmt;

	int track_index = 0;
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	ret = mediademuxer_prepare(g_media_demuxer);
	ret = mediademuxer_get_track_info(g_media_demuxer, track_index, &audfmt);
	ret = mediademuxer_select_track(g_media_demuxer, 0);
	ret = mediademuxer_start(g_media_demuxer);
	while (1) {
		ret = mediademuxer_read_sample(g_media_demuxer, track_index, &audbuf);
		media_packet_destroy(audbuf);
		assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
		if (audio_eos_track)
			break;
	}
	media_format_unref(audfmt);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_read_sample_n
 * @since_tizen		3.0
 * @description		Negative Test Case for reading a frame
 */
int utc_mediademuxer_read_sample_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_read_sample(g_media_demuxer, -1, NULL);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_seek_p
 * @since_tizen		3.0
 * @description		Positive Test Case for seek operation
 */
int utc_mediademuxer_seek_p(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	ret = mediademuxer_prepare(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	ret = mediademuxer_select_track(g_media_demuxer, 0);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	ret = mediademuxer_start(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	ret = mediademuxer_seek(g_media_demuxer, 100);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_seek_n
 * @since_tizen		3.0
 * @description		Negative Test Case for seek operation
 */
int utc_mediademuxer_seek_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_seek(g_media_demuxer, 100);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_STATE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_set_error_cb_p
 * @since_tizen		3.0
 * @description		Positive Test Case for setting error callback
 */
int utc_mediademuxer_set_error_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_error_cb(g_media_demuxer, (mediademuxer_error_cb) error_cb, g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_set_error_cb_n
 * @since_tizen		3.0
 * @description		Negative Test Case for setting error callback
 */
int utc_mediademuxer_set_error_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_error_cb(NULL, NULL, NULL);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_unset_error_cb_p
 * @since_tizen		3.0
 * @description		Positive Test Case for unsetting error callback
 */
int utc_mediademuxer_unset_error_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;
	ret = mediademuxer_set_error_cb(NULL, NULL, NULL);
	ret = mediademuxer_unset_error_cb(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_unset_error_cb_n
 * @since_tizen		3.0
 * @description		Negative Test Case for unsetting error callback
 */
int utc_mediademuxer_unset_error_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_unset_error_cb(NULL);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_set_eos_cb_p
 * @since_tizen		3.0
 * @description		Positive Test Case for setting end of stream callback
 */
int utc_mediademuxer_set_eos_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_eos_cb(g_media_demuxer, (mediademuxer_eos_cb) eos_cb, g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_set_eos_cb_n
 * @since_tizen		3.0
 * @description		Negative Test Case for setting end of stream callback
 */
int utc_mediademuxer_set_eos_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_eos_cb(NULL, NULL, NULL);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_unset_eos_cb_p
 * @since_tizen		3.0
 * @description		Positive Test Case for unsetting end of stream callback
 */
int utc_mediademuxer_unset_eos_cb_p(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;
	ret = mediademuxer_set_eos_cb(g_media_demuxer, (mediademuxer_eos_cb)eos_cb, g_media_demuxer);
	ret = mediademuxer_unset_eos_cb(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_unset_eos_cb_n
 * @since_tizen		3.0
 * @description		Negative Test Case for unsetting end of stream callback
 */
int utc_mediademuxer_unset_eos_cb_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_unset_eos_cb(NULL);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_get_state_p
 * @since_tizen		3.0
 * @description		Positive Test Case for getting state of demuxer
 */
int utc_mediademuxer_get_state_p(void)
{
	assert(!_is_broken);
	mediademuxer_state state;

	int ret = MEDIADEMUXER_ERROR_NONE;
	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	ret = mediademuxer_get_state(g_media_demuxer, &state);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_get_state_n
 * @since_tizen		3.0
 * @description		Negative Test Case for getting state of demuxer
 */
int utc_mediademuxer_get_state_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_get_state(g_media_demuxer, NULL);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_OPERATION);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_unselect_track_p
 * @since_tizen		3.0
 * @description		Positive Test Case for unselecting track
 */
int utc_mediademuxer_unselect_track_p(void)
{
	int track_index = 0;

	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_data_source(g_media_demuxer, uri);

	ret = mediademuxer_prepare(g_media_demuxer);

	ret = mediademuxer_select_track(g_media_demuxer, track_index);
	ret = mediademuxer_unselect_track(g_media_demuxer, track_index);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_unselect_track_n
 * @since_tizen		3.0
 * @description		Negative Test Case for unselecting track
 */
int utc_mediademuxer_unselect_track_n(void)
{

	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;
	ret = mediademuxer_unselect_track(g_media_demuxer, 0);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_STATE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_stop_p
 * @since_tizen		3.0
 * @description		Positive Test Case for stopping demuxer
 */
int utc_mediademuxer_stop_p(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	ret = mediademuxer_prepare(g_media_demuxer);
	ret = mediademuxer_start(g_media_demuxer);
	ret = mediademuxer_stop(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_stop_n
 * @since_tizen		3.0
 * @description		Negative Test Case for stopping demuxer
 */
int utc_mediademuxer_stop_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;
	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	ret = mediademuxer_prepare(g_media_demuxer);
	ret = mediademuxer_stop(NULL);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_unprepare_p
 * @since_tizen		3.0
 * @description		Positive Test Case for unpreparing demuxer
 */
int utc_mediademuxer_unprepare_p(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;
	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	ret = mediademuxer_prepare(g_media_demuxer);
	ret = mediademuxer_unprepare(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_unprepare_n
 * @since_tizen		3.0
 * @description		Negative Test Case for unpreparing demuxer
 */
int utc_mediademuxer_unprepare_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;
	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	ret = mediademuxer_prepare(g_media_demuxer);
	ret = mediademuxer_start(g_media_demuxer);
	ret = mediademuxer_unprepare(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_STATE);
	return 0;
}

/**
 * @testcase		utc_mediademuxer_destroy_p
 * @since_tizen		3.0
 * @description		Positive Test Case for destroying demuxer
 */
int utc_mediademuxer_destroy_p(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;

	ret = mediademuxer_destroy(g_media_demuxer);
	g_media_demuxer = NULL;
	assert_eq(ret, MEDIADEMUXER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_mediademuxer_destroy_n
 * @since_tizen		3.0
 * @description		Negative Test Case for destroying demuxer
 */
int utc_mediademuxer_destroy_n(void)
{
	assert(!_is_broken);
	int ret = MEDIADEMUXER_ERROR_NONE;
	ret = mediademuxer_set_data_source(g_media_demuxer, uri);
	ret = mediademuxer_prepare(g_media_demuxer);
	ret = mediademuxer_destroy(g_media_demuxer);
	assert_eq(ret, MEDIADEMUXER_ERROR_INVALID_OPERATION);

	return 0;
}
