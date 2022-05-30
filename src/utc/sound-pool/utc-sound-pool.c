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
#include "tct_common.h"
#include <string.h>
#include <glib.h>
#include <unistd.h>
#include <limits.h>
#include <media/sound_pool.h>

#define API_NAMESPACE "[SOUND_POOL]"
#define MAX_PATH 1024

#define MAX_POOLS 8
#define DEFAULT_PRIORITY 255
#define DEFAULT_SAMPLE_TAG "sound_pool_test_file"
#define DEFAULT_WRONG_SAMPLE_TAG "wrong_sample_tag"
#define DEFAULT_WRONG_FILE_PATH "wrong_file_name"

sound_pool_h g_test_pool = NULL;
static char *file_path = NULL;
static const char *test_wav_file = "sound_1.wav";
static const char *test_ogg_file = "sound_2.ogg";

/**
 * @function		_sound_pool_prepare_filepath
 * @description		Called at startup functions to prepare filepath.
 * @parameter		NA
 * @return			NA
 */
void static _sound_pool_prepare_filepath(const char *testfile_name)
{
	char pzs_value[MAX_PATH] = {0,};
	unsigned int size_of_path;

	if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pzs_value, API_NAMESPACE )) {
		PRINT_UTC_LOG("\\n [Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s \\n", __LINE__, API_NAMESPACE, pzs_value);
		size_of_path = strlen(pzs_value) + strlen(testfile_name) + 10;
		file_path = (char*)malloc(size_of_path);
		snprintf(file_path, size_of_path, "%s/res/res/%s", pzs_value, testfile_name);
	} else {
		PRINT_UTC_LOG("\\n [Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30' \\n", __LINE__, API_NAMESPACE);
	}
}
/**
 * @function		utc_sound_pool_startup
 * @description		Called before each test.
 * @parameter		NA
 * @return			NA
 */
void utc_sound_pool_startup(void)
{
	_sound_pool_prepare_filepath(test_ogg_file);

	sound_pool_create(&g_test_pool);

}

/**
 * @function		utc_sound_pool_cleanup
 * @description		Called after each test.
 * @parameter		NA
 * @return			NA
 */
void utc_sound_pool_cleanup(void)
{

	if (g_test_pool) {
		sound_pool_deactivate(g_test_pool);
		sound_pool_unload_source(g_test_pool, DEFAULT_SAMPLE_TAG);
		sound_pool_destroy(g_test_pool);
		g_test_pool = NULL;
	}

	if (file_path != NULL) {
		free(file_path);
		file_path = NULL;
	}
}

/**
 * @function		_sound_pool_stream_prepare_to_play
 * @description		Load the default source to the pool and activate it. Called in other test cases when ever steam play is needed.
 * @parameter		NA
 * @return			NA
 */
int static _sound_pool_stream_prepare_to_play(void)
{

	int ret = SOUND_POOL_ERROR_NONE;

	ret = sound_pool_load_source_from_file(g_test_pool, file_path, DEFAULT_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	return 0;
}

/**
 * @function		_stream_state_changed_cb
 * @description		It is a callback function needs to registered with sound_pool_stream_play. It will be called when ever the stream state change happens.
 * @return			NA
 */
void static _stream_state_changed_cb(sound_pool_h pool, unsigned id, sound_pool_stream_state_e prev_state,
		sound_pool_stream_state_e cur_state, void *data)
{

	PRINT_UTC_LOG("\\n [%s]: pool(%p), id(%d), data(%p), prev_state(%d), cur_state(%d) \\n", __FUNCTION__, pool, id, data, prev_state, cur_state);

	return;
}

/**
 * @function		_sound_pool_state_changed_cb
 * @description		It is a callback function needs to registered with sound_pool_set_state_changed_cb.
 *					It is used in sound pool state chage test cases. This callback function will be called when ever pool state changes.
 * @return			NA
 */
void static _sound_pool_state_changed_cb(sound_pool_h pool, sound_pool_state_e prev_state,
		sound_pool_state_e cur_state, void *data)
{

	sound_pool_state_e *state = (sound_pool_state_e *)data;
	*state = cur_state;

	return;
}

/**
 * @brief Positive test case of sound_pool_create()
 * @testcase		utc_sound_pool_create_p
 * @since_tizen		4.0
 * @description		Creates instances of sound pool up to its max number.
 *
 */
int utc_sound_pool_create_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	sound_pool_h test_pool [MAX_POOLS] = {NULL};
	int i;

	for (i = 0; i < MAX_POOLS; ++i) {
		ret = sound_pool_create(&test_pool[i]);
		assert_eq(ret, SOUND_POOL_ERROR_NONE);
		assert_neq(test_pool[i], NULL);
	}
	// TC clean-up
	for (i = 0; i < MAX_POOLS; ++i) {
		ret = sound_pool_destroy(test_pool[i]);
		assert_eq(ret, SOUND_POOL_ERROR_NONE);
		test_pool[i] = NULL;
	}

	return 0;
}

/**
 * @brief Negative test case of sound_pool_create()
 * @testcase		utc_sound_pool_create_n
 * @since_tizen		4.0
 * @description		Creates instance of sound pool but fails if
 *					incorrect parameters are passed
 */
int utc_sound_pool_create_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;

	ret = sound_pool_create(NULL);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_create()
 * @testcase		utc_sound_pool_create_n2
 * @since_tizen		4.0
 * @description		Creates instances of sound pool up to its max number
 * 					but fails if maximum number of instances exceeded
 */
int utc_sound_pool_create_n2(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	sound_pool_h test_pool [MAX_POOLS] = {NULL};
	int i;

	ret = sound_pool_create(&g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	for (i = 0; i < MAX_POOLS-1; ++i) {
		ret = sound_pool_create(&test_pool[i]);
		assert_eq(ret, SOUND_POOL_ERROR_NONE);
		assert_neq(test_pool[i], NULL);
	}

	ret = sound_pool_create(&test_pool[MAX_POOLS-1]);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_OPERATION);
	assert_eq(test_pool[MAX_POOLS-1], NULL);

	// TC clean-up
	for (i = 0; i < MAX_POOLS-1; ++i) {
		ret = sound_pool_destroy(test_pool[i]);
		assert_eq(ret, SOUND_POOL_ERROR_NONE);
		test_pool[i] = NULL;
	}

	return 0;
}

/**
 * @brief Positive test case of sound_pool_destroy()
 * @testcase		utc_sound_pool_destroy_p
 * @since_tizen		4.0
 * @description		Destroys instance of sound pool created with
 * 					utc_sound_pool_startup
 */
int utc_sound_pool_destroy_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;

	ret = sound_pool_create(&g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(g_test_pool, NULL);

	ret = sound_pool_destroy(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	g_test_pool = NULL;

	return 0;
}

/**
 * @brief Negative test case of sound_pool_destroy()
 * @testcase		utc_sound_pool_destroy_n
 * @since_tizen		4.0
 * @description		Fails when trying to destroy NULL instance of sound pool
 */
int utc_sound_pool_destroy_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;

	ret = sound_pool_destroy(NULL);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_load_source_from_file()
 * @testcase		utc_sound_pool_load_source_from_file_p
 * @since_tizen		4.0
 * @description		Loads source to sound pool from specified file and
 * 					sets a tag
 */
int utc_sound_pool_load_source_from_file_p(void)
{
	int ret;

	ret = sound_pool_load_source_from_file(g_test_pool, file_path, DEFAULT_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_load_source_from_file()
 * @testcase		utc_sound_pool_load_source_from_file_p
 * @since_tizen		4.0
 * @description		Loads source to sound pool from wav file and
 * 					sets a tag. Startup and Cleanup not called for this test case.
 */
int utc_sound_pool_load_source_from_file_p2(void)
{
	int ret;
	_sound_pool_prepare_filepath(test_wav_file);

	ret = sound_pool_create(&g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_load_source_from_file(g_test_pool, file_path, DEFAULT_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	return 0;
}

/**
  * @brief Negative test case of sound_pool_load_source_from_file()
  * @testcase		utc_sound_pool_load_source_from_file_n
  * @since_tizen		4.0
  * @description		Loads source to sound pool from specified file and
  * 					sets a tag but fails if incorrect parameters are passed
*/
int utc_sound_pool_load_source_from_file_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;


	ret = sound_pool_load_source_from_file(NULL, file_path, DEFAULT_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_load_source_from_file(g_test_pool, DEFAULT_WRONG_FILE_PATH, DEFAULT_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_NO_SUCH_FILE);

	ret = sound_pool_load_source_from_file(g_test_pool, NULL, DEFAULT_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_load_source_from_file(g_test_pool, file_path, NULL);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_load_source_from_file(g_test_pool, file_path, DEFAULT_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	/* Load source with same sample tag again */
	ret = sound_pool_load_source_from_file(g_test_pool, file_path, DEFAULT_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_unload_source()
 * @testcase		utc_sound_pool_unload_source_p
 * @since_tizen		4.0
 * @description		Unloads source with specified tag from sound pool
 */
int utc_sound_pool_unload_source_p(void)
{
	int ret;

	sound_pool_load_source_from_file(g_test_pool, file_path, DEFAULT_SAMPLE_TAG);
	ret = sound_pool_unload_source(g_test_pool, DEFAULT_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_unload_source()
 * @testcase		utc_sound_pool_unload_source_n
 * @since_tizen		4.0
 * @description		Unloads source with specified tag from sound pool but fails if
 * 					NULL sound pool instance or non-existent source tag is passed
 */
int utc_sound_pool_unload_source_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;

	ret = sound_pool_unload_source(NULL, DEFAULT_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_unload_source(g_test_pool, DEFAULT_WRONG_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_KEY_NOT_AVAILABLE);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_get_state()
 * @testcase		utc_sound_pool_get_state_p
 * @since_tizen		4.0
 * @description		Gets enum value of a current pool state.
 */
int utc_sound_pool_get_state_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	sound_pool_state_e state = SOUND_POOL_STATE_INACTIVE;

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_get_state(g_test_pool, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STATE_ACTIVE);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_get_state()
 * @testcase		utc_sound_pool_get_state_n
 * @since_tizen		4.0
 * @description		Gets enum value of a current pool state.
 * 					Fails when incorrect parameters are passed.
 */
int utc_sound_pool_get_state_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;

	sound_pool_state_e state = SOUND_POOL_STATE_INACTIVE;

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_get_state(NULL, &state);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_get_state(g_test_pool, NULL);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_activate()
 * @testcase		utc_sound_pool_activate_p
 * @since_tizen		4.0
 * @description		Sets sound pool to active state.
 */
int utc_sound_pool_activate_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	sound_pool_h test_pool [MAX_POOLS-1] = {NULL};
	int i;

	for (i = 0; i < MAX_POOLS-1; ++i) {
		ret = sound_pool_create(&test_pool[i]);
		assert_eq(ret, SOUND_POOL_ERROR_NONE);
		assert_neq(test_pool[i], NULL);

		ret = sound_pool_activate(test_pool[i]);
		assert_eq(ret, SOUND_POOL_ERROR_NONE);
	}

	// TC clean-up
	for (i = 0; i < MAX_POOLS-1; ++i) {
		sound_pool_destroy(test_pool[i]);
		test_pool[i] = NULL;
	}
	return 0;
}

/**
 * @brief Negative test case of sound_pool_activate()
 * @testcase		utc_sound_pool_activate_n
 * @since_tizen		4.0
 * @description		Sets sound pool to active state.
 * 					Fails if NULL sound pool handle is passed.
 */
int utc_sound_pool_activate_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_activate(NULL);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_deactivate()
 * @testcase		utc_sound_pool_deactivate_p
 * @since_tizen		4.0
 * @description		Sets sound pool to inactive state.
 */
int utc_sound_pool_deactivate_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	int i;

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_deactivate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	sound_pool_h test_pool [MAX_POOLS-1] = {NULL};

	for (i = 0; i < MAX_POOLS-1; ++i) {
		ret = sound_pool_create(&test_pool[i]);
		assert_eq(ret, SOUND_POOL_ERROR_NONE);
		assert_neq(test_pool[i], NULL);

		ret = sound_pool_activate(test_pool[i]);
		assert_eq(ret, SOUND_POOL_ERROR_NONE);
	}
	// TC clean-up
	for (i = 0; i < MAX_POOLS-1; ++i) {
		ret = sound_pool_deactivate(test_pool[i]);
		assert_eq(ret, SOUND_POOL_ERROR_NONE);
		ret = sound_pool_destroy(test_pool[i]);
		assert_eq(ret, SOUND_POOL_ERROR_NONE);
		test_pool[i] = NULL;
	}

	return 0;
}

/**
 * @brief Negative test case of sound_pool_deactivate()
 * @testcase		utc_sound_pool_deactivate_n
 * @since_tizen		4.0
 * @description		Sets sound pool to inactive state.
 * 					Fails if NULL sound pool handle is passed.
 */
int utc_sound_pool_deactivate_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_deactivate(NULL);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_deactivate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_deactivate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_set_volume()
 * @testcase		utc_sound_pool_set_volume_p
 * @since_tizen		4.0
 * @description		Sets a value for volume of sound pool.
 */
int utc_sound_pool_set_volume_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;

	ret = sound_pool_set_volume(g_test_pool, 0.5f);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_set_volume()
 * @testcase		utc_sound_pool_set_volume_n
 * @since_tizen		4.0
 * @description		Sets a value for volume of sound pool.
 * 					Fails if NULL sound pool handle or incorrect
 * 					volume value are passed.
 */
int utc_sound_pool_set_volume_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;

	ret = sound_pool_set_volume(NULL, 0.5f);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_set_volume(g_test_pool, 2.0f);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_get_volume()
 * @testcase		utc_sound_pool_get_volume_p
 * @since_tizen		4.0
 * @description		Gets a value for volume of sound pool.
 */
int utc_sound_pool_get_volume_p(void)
{
	float volume = 0.0;
	int ret = SOUND_POOL_ERROR_NONE;

	sound_pool_get_volume(g_test_pool, &volume);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_get_volume()
 * @testcase		utc_sound_pool_get_volume_n
 * @since_tizen		4.0
 * @description		Sets a value for volume of sound pool.
 * 					Fails when incorrect parameters are passed.
 */
int utc_sound_pool_get_volume_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	float volume = 0.0;

	ret = sound_pool_get_volume(NULL, &volume);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_get_volume(g_test_pool, NULL);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_set_state_changed_cb()
 * @testcase		utc_sound_pool_set_state_changed_cb_p
 * @since_tizen		4.0
 * @description		Passes testing callback function to sound pool. Then changes
 * 					sound pool states and checks if testing callback returns
 * 					correct values.
 */
int utc_sound_pool_set_state_changed_cb_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	sound_pool_state_e data = SOUND_POOL_STATE_INACTIVE;

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_set_state_changed_cb(g_test_pool, _sound_pool_state_changed_cb, &data);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_deactivate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(data, SOUND_POOL_STATE_INACTIVE);

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(data, SOUND_POOL_STATE_ACTIVE);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_set_state_changed_cb()
 * @testcase		utc_sound_pool_set_state_changed_cb_n
 * @since_tizen		4.0
 * @description		Fails when incorrect parameters are passed
 * 					i.e. NULL sound pool handle or NULL pointer instead
 * 					of callback function.

 */
int utc_sound_pool_set_state_changed_cb_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	sound_pool_state_e data = SOUND_POOL_STATE_INACTIVE;

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_set_state_changed_cb(NULL, _sound_pool_state_changed_cb, &data);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_set_state_changed_cb(g_test_pool, NULL, &data);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_unset_state_changed_cb()
 * @testcase		utc_sound_pool_unset_state_changed_cb_p
 * @since_tizen		4.0
 * @description		Passes testing callback function to sound pool and then unsets it.
 * 					Then changes sound pool states and checks if testing callback
 * 					stopped returning of values.
 */
int utc_sound_pool_unset_state_changed_cb_p(void)
{
	sound_pool_state_e data = SOUND_POOL_STATE_INACTIVE;
	int ret = SOUND_POOL_ERROR_NONE;

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_set_state_changed_cb(g_test_pool, _sound_pool_state_changed_cb, &data);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_deactivate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	assert_eq(data, SOUND_POOL_STATE_INACTIVE);

	ret = sound_pool_unset_state_changed_cb(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	sound_pool_activate(g_test_pool);
	assert_eq(data, SOUND_POOL_STATE_INACTIVE);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_unset_state_changed_cb()
 * @testcase		utc_sound_pool_unset_state_changed_cb_n
 * @since_tizen		4.0
 * @description		Fails when NULL sound pool handle was passed as parameter
 */
int utc_sound_pool_unset_state_changed_cb_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;

	ret = sound_pool_unset_state_changed_cb(NULL);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_stream_play()
 * @testcase		utc_sound_pool_stream_play_p
 * @since_tizen		4.0
 * @description		Creates stream from a source with specified tag
 * 					and 1st time plays once, 2nd on a highest priority
 * 					and 3rd plays maximum available (but not infinite)
 * 					number of loops
 */
int utc_sound_pool_stream_play_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int loop = 1;
	float volume = 0.5;
	unsigned int priority = DEFAULT_PRIORITY;
	void *data = NULL;
	unsigned int id = 100;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;
	sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
								loop, volume, priority, priority_policy, _stream_state_changed_cb,
								data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PLAYING);

	priority = INT_MAX;
	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
								loop, volume, priority, priority_policy, _stream_state_changed_cb,
								data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PLAYING);

	loop = INT_MAX;
	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
								loop, volume, priority, priority_policy, _stream_state_changed_cb,
								data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PLAYING);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_stream_play()
 * @testcase		utc_sound_pool_stream_play_p2
 * @since_tizen		4.0
 * @description		Checks stream creation in inactive sound pool
 */
int utc_sound_pool_stream_play_p2(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int id = 100;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;

	ret = sound_pool_load_source_from_file(g_test_pool, file_path, DEFAULT_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
								1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED,
								NULL, NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_SUSPENDED);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_stream_play()
 * @testcase		utc_sound_pool_stream_play_p3
 * @since_tizen		4.0
 * @description		Checks streams policy behaviour.
 * 					stream1(Mute policy) and stream2 (Suspended policy) with same priority(1)
 * 					starts playing. stream3 played with priority 2.
 * 					stream1 will be playing with mute and stream2 will be suspended.
 */
int utc_sound_pool_stream_play_p3(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int id1, id2, id3;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
								1, 0.5, 1, SOUND_POOL_STREAM_PRIORITY_POLICY_MUTE,
								NULL, NULL, &id1);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
								1, 0.5, 1, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED,
								NULL, NULL, &id2);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
								1, 0.5, 2, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED,
								NULL, NULL, &id3);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id1, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PLAYING);

	ret = sound_pool_stream_get_state(g_test_pool, id2, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_SUSPENDED);

	ret = sound_pool_stream_get_state(g_test_pool, id3, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PLAYING);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_stream_play()
 * @testcase		utc_sound_pool_stream_play_n
 * @since_tizen		4.0
 * @description		Creates and plays a stream from a source and
 * 					fails when incorrect parameters are passed
 */
int utc_sound_pool_stream_play_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int loop = 1;
	float volume = 0.5;
	unsigned int priority = DEFAULT_PRIORITY;
	sound_pool_stream_state_changed_cb callback = NULL;
	void *data = NULL;
	unsigned int id = 100;
	sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(NULL, DEFAULT_SAMPLE_TAG,
								loop, volume, priority, priority_policy, callback,
								data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);
	assert_eq(id, 100);

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_WRONG_SAMPLE_TAG,
									loop, volume, priority, priority_policy, callback,
									data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_KEY_NOT_AVAILABLE);
	assert_eq(id, 100);

	ret = sound_pool_stream_play(g_test_pool, NULL,
									loop, volume, priority, priority_policy, callback,
									data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);
	assert_eq(id, 100);

	volume = 1.1;
	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
									loop, volume, priority, priority_policy, callback,
									data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);
	assert_eq(id, 100);

	volume = -0.5;
	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
									loop, volume, priority, priority_policy, callback,
									data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);
	assert_eq(id, 100);

	priority_policy = 99;
	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
									loop, volume, priority, priority_policy, callback,
									data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);
	assert_eq(id, 100);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_stream_pause()
 * @testcase		utc_sound_pool_stream_pause_p
 * @since_tizen		4.0
 * @description		Creates and plays a stream from a source and
 * 					sets a paused state
 */
int utc_sound_pool_stream_pause_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;
	unsigned int id = 100;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
							NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_pause(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PAUSED);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_stream_pause()
 * @testcase		utc_sound_pool_stream_pause_p2
 * @since_tizen		4.0
 * @description		Checks stream pause in inactive sound pool
 */
int utc_sound_pool_stream_pause_p2(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;
	unsigned int id = 100;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
							NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_deactivate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(state, SOUND_POOL_STREAM_STATE_SUSPENDED);

	ret = sound_pool_stream_pause(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PAUSED);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_stream_pause()
 * @testcase		utc_sound_pool_stream_pause_n
 * @since_tizen		4.0
 * @description		Creates and plays a stream from a source, then sets
 * 					a pause but fails when incorrect parameters are passed
 * 					i.e. NULL sound pool handle, pausing of already paused
 * 					stream or pausing of non-existing stream.
 */
int utc_sound_pool_stream_pause_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int loop = 1;
	float volume = 0.5;
	unsigned int priority = DEFAULT_PRIORITY;
	sound_pool_stream_state_changed_cb callback = NULL;
	void *data = NULL;
	unsigned int id = 100;
    sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							loop, volume, priority, priority_policy, callback,
							data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_pause(NULL, id);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_stream_pause(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_pause(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_OPERATION);

	id = 1000;
	ret = sound_pool_stream_pause(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_KEY_NOT_AVAILABLE);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_stream_resume()
 * @testcase		utc_sound_pool_stream_resume_p
 * @since_tizen		4.0
 * @description		Creates and plays a stream from a source,
 * 					sets it on a pause and then resumes.
 */
int utc_sound_pool_stream_resume_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int loop = 1;
	float volume = 0.5;
	unsigned int priority = DEFAULT_PRIORITY;
	sound_pool_stream_state_changed_cb callback = NULL;
	void *data = NULL;
	unsigned int id = 100;
    sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							loop, volume, priority, priority_policy, callback,
							data, &id);
	assert_neq(id, 100);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	ret = sound_pool_stream_pause(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_resume(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_stream_resume()
 * @testcase		utc_sound_pool_stream_resume_p2
 * @since_tizen		4.0
 * @description		Checks paused stream resume in inactive sound pool
 */
int utc_sound_pool_stream_resume_p2(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;
	unsigned int id = 100;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
							NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_pause(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_deactivate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PAUSED);

	ret = sound_pool_stream_resume(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_SUSPENDED);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_stream_resume()
 * @testcase		utc_sound_pool_stream_resume_n
 * @since_tizen		4.0
 * @description		Creates and plays a stream from a source, sets
 * 					a pause and then resumes it. Fails if incorrect
 * 					parameters are passed i.e. NULL sound pool
 * 					handle or when resuming a non-existing stream.
 */
int utc_sound_pool_stream_resume_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int loop = 1;
	float volume = 0.5;
	unsigned int priority = DEFAULT_PRIORITY;
	sound_pool_stream_state_changed_cb callback = NULL;
	void *data = NULL;
	unsigned int id = 100;

	sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							loop, volume, priority, priority_policy, callback,
							data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);
	ret = sound_pool_stream_pause(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_resume(NULL, id);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	id = 1000;
	ret = sound_pool_stream_resume(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_KEY_NOT_AVAILABLE);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_stream_stop()
 * @testcase		utc_sound_pool_stream_stop_p
 * @since_tizen		4.0
 * @description		Creates and plays a stream from a source, then stops it.
 */
int utc_sound_pool_stream_stop_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int loop = 1;
	float volume = 0.5;
	unsigned int priority = DEFAULT_PRIORITY;
	sound_pool_stream_state_changed_cb callback = NULL;
	void *data = NULL;
	unsigned int id = 100;
	sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							loop, volume, priority, priority_policy, callback,
							data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_stop(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_stream_stop()
 * @testcase		utc_sound_pool_stream_stop_n
 * @since_tizen		4.0
 * @description		Creates and plays a stream from a source, then stops it.
 * 					Fails when NULL sound pool handle is passed as parameter.
 */
int utc_sound_pool_stream_stop_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int loop = 1;
	float volume = 0.5;
	unsigned int priority = DEFAULT_PRIORITY;
	sound_pool_stream_state_changed_cb callback = NULL;
	void *data = NULL;
	unsigned int id = 100;
	sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							loop, volume, priority, priority_policy, callback,
							data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_stop(NULL, id);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_stream_stop()
 * @testcase		utc_sound_pool_stream_stop_n2
 * @since_tizen		4.0
 * @description		Creates and plays a stream from a source, then stops it.
 * 					Fails when attempting to stop a non-existing stream.
 */
int utc_sound_pool_stream_stop_n2(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int loop = 1;
	float volume = 0.5;
	unsigned int priority = DEFAULT_PRIORITY;
	sound_pool_stream_state_changed_cb callback = NULL;
	void *data = NULL;
	unsigned int id = 0;
	sound_pool_stream_priority_policy_e priority_policy = SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							loop, volume, priority, priority_policy, callback,
							data, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	id = 1000;
	ret = sound_pool_stream_stop(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_KEY_NOT_AVAILABLE);

	return 0;
}


/**
 * @brief Positive test case of sound_pool_stream_set_volume()
 * @testcase		utc_sound_pool_stream_set_volume_p
 * @since_tizen		4.0
 * @description		Sets boundary values for volume of stream in sound pool.
 */
int utc_sound_pool_stream_set_volume_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int id = 100;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
							NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_set_volume(g_test_pool, id, 0.0);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_set_volume(g_test_pool, id, 1.0);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_stream_set_volume()
 * @testcase		utc_sound_pool_stream_set_volume_n
 * @since_tizen		4.0
 * @description		Sets a value for volume of stream in sound pool.
 * 					Fails when incorrect parameters are passed
 * 					i.e. NULL sound pool handle, id of non-existing
 * 					stream, incorrect volume value.
 */
int utc_sound_pool_stream_set_volume_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int id = 100;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
							NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_set_volume(NULL, id, 0.5);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_stream_set_volume(g_test_pool, 1000, 0.5);
	assert_eq(ret, SOUND_POOL_ERROR_KEY_NOT_AVAILABLE);

	ret = sound_pool_stream_set_volume(g_test_pool, id, 2.0);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_stream_set_volume(g_test_pool, id, -0.5);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_stream_get_volume()
 * @testcase		utc_sound_pool_stream_get_volume_p
 * @since_tizen		4.0
 * @description		Gets a value for volume of stream in sound pool.
 */
int utc_sound_pool_stream_get_volume_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int id = 100;
	float volume = -1.0;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
							NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_get_volume(g_test_pool, id, &volume);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(volume, 0.5);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_stream_get_volume()
 * @testcase		utc_sound_pool_stream_get_volume_n
 * @since_tizen		4.0
 * @description		Gets a value of stream volume in sound pool.
 * 					Fails when incorrect parameters are passed
 * 					i.e. NULL sound pool handle, id of non-existing
 * 					stream, NULL pointer to output parameter.
 */
int utc_sound_pool_stream_get_volume_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int id = 100;
	float volume = 0.0;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
							NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_get_volume(NULL, id, &volume);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_stream_get_volume(g_test_pool, 1000, &volume);
	assert_eq(ret, SOUND_POOL_ERROR_KEY_NOT_AVAILABLE);

	ret = sound_pool_stream_get_volume(g_test_pool, id, NULL);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_stream_set_priority()
 * @testcase		utc_sound_pool_stream_set_priority_p
 * @since_tizen		4.0
 * @description		Sets boundary values for priority of stream in sound pool.
 */
int utc_sound_pool_stream_set_priority_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int id = 100;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
							NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_set_priority(g_test_pool, id, 0);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_set_priority(g_test_pool, id, UINT_MAX);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_stream_set_priority()
 * @testcase		utc_sound_pool_stream_set_priority_n
 * @since_tizen		4.0
 * @description		Sets a value for priority of stream in sound pool.
 * 					Fails when incorrect parameters are passed
 * 					i.e. NULL sound pool handle, id of non-existing
 * 					stream.
 */
int utc_sound_pool_stream_set_priority_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int id = 100;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
							NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_set_priority(NULL, id, 0);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_stream_set_priority(g_test_pool, 1000, 0);
	assert_eq(ret, SOUND_POOL_ERROR_KEY_NOT_AVAILABLE);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_stream_get_priority()
 * @testcase		utc_sound_pool_stream_get_priority_p
 * @since_tizen		4.0
 * @description		Gets a value of stream priority in sound pool.
 */
int utc_sound_pool_stream_get_priority_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int id = 100;
	unsigned int priority = 0;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
							NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_get_priority(g_test_pool, id, &priority);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(priority, DEFAULT_PRIORITY);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_stream_get_priority()
 * @testcase		utc_sound_pool_stream_get_priority_n
 * @since_tizen		4.0
 * @description		Gets a value of stream priority in sound pool.
 * 					Fails when incorrect parameters are passed
 * 					i.e. NULL sound pool handle, id of non-existing
 * 					stream, NULL pointer to output parameter.
 */
int utc_sound_pool_stream_get_priority_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int id = 100;
	unsigned int priority = 0;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
								1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
								NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_get_priority(NULL, id, &priority);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_stream_get_priority(g_test_pool, 1000, &priority);
	assert_eq(ret, SOUND_POOL_ERROR_KEY_NOT_AVAILABLE);

	ret = sound_pool_stream_get_priority(g_test_pool, id, NULL);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @brief Positive test case of sound_pool_stream_get_state()
 * @testcase		utc_sound_pool_stream_get_state_p
 * @since_tizen		4.0
 * @description		Create and plays a stream in sound pool. Then changes
 * 					state, gets and checks a value of stream state.
 */
int utc_sound_pool_stream_get_state_p(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int id = 100;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;

	ret = sound_pool_load_source_from_file(g_test_pool, file_path, DEFAULT_SAMPLE_TAG);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
							NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_SUSPENDED);

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PLAYING);

	ret = sound_pool_stream_pause(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PAUSED);

	ret = sound_pool_stream_resume(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PLAYING);

	ret = sound_pool_deactivate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_SUSPENDED);

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PLAYING);

	ret = sound_pool_deactivate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_SUSPENDED);

	ret = sound_pool_stream_pause(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PAUSED);

	ret = sound_pool_stream_resume(g_test_pool, id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_SUSPENDED);

	ret = sound_pool_activate(g_test_pool);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);

	ret = sound_pool_stream_get_state(g_test_pool, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_eq(state, SOUND_POOL_STREAM_STATE_PLAYING);

	return 0;
}

/**
 * @brief Negative test case of sound_pool_stream_get_state()
 * @testcase		utc_sound_pool_stream_get_state_n
 * @since_tizen		4.0
 * @description		Create and plays a stream in sound pool, then gets
 * 					a value of stream state.
 * 					Fails when incorrect parameters are passed
 * 					i.e. NULL sound pool handle, id of non-existing
 * 					stream, NULL pointer to output parameter.
 */
int utc_sound_pool_stream_get_state_n(void)
{
	int ret = SOUND_POOL_ERROR_NONE;
	unsigned int id = 100;
	sound_pool_stream_state_e state = SOUND_POOL_STREAM_STATE_NONE;

	_sound_pool_stream_prepare_to_play();

	ret = sound_pool_stream_play(g_test_pool, DEFAULT_SAMPLE_TAG,
							1, 0.5, DEFAULT_PRIORITY, SOUND_POOL_STREAM_PRIORITY_POLICY_SUSPENDED, NULL,
							NULL, &id);
	assert_eq(ret, SOUND_POOL_ERROR_NONE);
	assert_neq(id, 100);

	ret = sound_pool_stream_get_state(NULL, id, &state);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	ret = sound_pool_stream_get_state(g_test_pool, 1000, &state);
	assert_eq(ret, SOUND_POOL_ERROR_KEY_NOT_AVAILABLE);

	ret = sound_pool_stream_get_state(g_test_pool, id, NULL);
	assert_eq(ret, SOUND_POOL_ERROR_INVALID_PARAMETER);

	return 0;
}



