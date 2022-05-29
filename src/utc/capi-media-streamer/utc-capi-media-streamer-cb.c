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
#include <string.h>
#include <media/media_streamer.h>

	media_streamer_node_h app_src = NULL;
	media_streamer_node_h app_sink = NULL;
	media_streamer_h streamer;
	int ret = MEDIA_STREAMER_ERROR_NONE;
//& set: CapiMedia-streamer

/* Application source callback */
static void buffer_status_cb(media_streamer_node_h node,
                             media_streamer_custom_buffer_status_e status,
                             void *user_data) {

	char *test = "This is buffer_status_cb test!";
	int size = strlen(test);

	media_packet_h packet;
	media_packet_create_from_external_memory (NULL, (void*)test,
                                                  size, NULL, NULL, &packet);
	ret = media_streamer_node_push_packet(node, packet);
}

/* Application sink callback */
static void new_buffer_cb(media_streamer_node_h node, void *user_data) {

	char *received_data = NULL;
	media_packet_h packet;

	media_streamer_node_pull_packet(node, &packet);

	media_packet_get_buffer_data_ptr(packet, (void **)received_data);
	media_packet_destroy(packet);
}

/* End of stream callback */
static void eos_cb(media_streamer_node_h node, void *user_data) {

	printf("Got EOS cb from appsink\n");
}

/* Error callback */
static void error_cb(media_streamer_h streamer,
                     media_streamer_error_e error,
                     void *user_data) {

	printf("Got Error cb from appsink\n");
}

static void state_change_cb(media_streamer_h streamer,
                            media_streamer_state_e previous_state,
                            media_streamer_state_e current_state,
                            void *user_data) {

	printf("Got State change cb from appsink\n");
}

/* interrupted callback */
static void interrupted_cb(media_streamer_interrupted_code_e code, void *user_data) {
	printf("Got Interrupted cb for mediastreamer\n");
}

/**
 * @function		utc_capi_media_streamer_cb_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_capi_media_streamer_cb_startup(void)
{
	ret = media_streamer_create(&streamer);

	/*********************** app_src *********************************** */
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);

	ret = media_streamer_node_add(streamer, app_src);

	/*********************** app_sink *********************************** */
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &app_sink);

	ret = 	media_streamer_node_add(streamer, app_sink);

	ret = media_streamer_node_link(app_src, "src", app_sink, "sink");
}

/**
 * @function		utc_capi_media_streamer_cb_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_capi_media_streamer_cb_cleanup(void)
{
	ret = media_streamer_destroy(streamer);
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_set_error_cb_p
 * @since_tizen		3.0
 * @description		Registers an error callback function
 *			to be invoked when an error occurs.
 */
int utc_media_streamer_set_error_cb_p(void)
{
	ret = media_streamer_set_error_cb(streamer, error_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_set_error_cb_n
 * @since_tizen		3.0
 * @description		Registers an error callback function
 *			to be invoked when an error occurs.
 */
int utc_media_streamer_set_error_cb_n(void)
{
	ret = media_streamer_set_error_cb(NULL, error_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_unset_error_cb_p
 * @since_tizen		3.0
 * @description		Unregisters the error callback function.
 */
int utc_media_streamer_unset_error_cb_p(void)
{
	ret = media_streamer_set_error_cb(streamer, error_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_unset_error_cb(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_unset_error_cb_n
 * @since_tizen		3.0
 * @description		Unregisters the error callback function.
 */
int utc_media_streamer_unset_error_cb_n(void)
{
	ret = media_streamer_set_error_cb(streamer, error_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_unset_error_cb(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_set_state_change_cb_p
 * @since_tizen		3.0
 * @description		Registers a callback that will be triggered
 *			after media streamer state is changed.
 */
int utc_media_streamer_set_state_change_cb_p(void)
{
	ret = media_streamer_set_state_change_cb(streamer, state_change_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_set_state_change_cb_n
 * @since_tizen		3.0
 * @description		Registers a callback that will be triggered
 *			after media streamer state is changed.
 */
int utc_media_streamer_set_state_change_cb_n(void)
{
	ret = media_streamer_set_state_change_cb(NULL, state_change_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_unset_state_change_cb_p
 * @since_tizen		3.0
 * @description		Unregisters the state changed callback function.
 */
int utc_media_streamer_unset_state_change_cb_p(void)
{
	ret = media_streamer_set_state_change_cb(streamer, state_change_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_unset_state_change_cb(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_unset_state_change_cb_n
 * @since_tizen		3.0
 * @description		Unregisters the state changed callback function.
 */
int utc_media_streamer_unset_state_change_cb_n(void)
{
	ret = media_streamer_set_state_change_cb(streamer, state_change_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_unset_state_change_cb(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_src_set_buffer_status_cb_p
 * @since_tizen		3.0
 * @description		Registers a callback function to be invoked
 *			when buffer underrun or overflow is occurred.
 */
int utc_media_streamer_src_set_buffer_status_cb_p(void)
{
	ret = media_streamer_src_set_buffer_status_cb(app_src, buffer_status_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_src_set_buffer_status_cb_n
 * @since_tizen		3.0
 * @description		Registers a callback function to be invoked
 *			when buffer underrun or overflow is occurred.
 */
int utc_media_streamer_src_set_buffer_status_cb_n(void)
{
	ret = media_streamer_src_set_buffer_status_cb(NULL, buffer_status_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_src_unset_buffer_status_cb_p
 * @since_tizen		3.0
 * @description		Unregisters the source node
 *			buffer status callback function.
 */
int utc_media_streamer_src_unset_buffer_status_cb_p(void)
{
	ret = media_streamer_src_set_buffer_status_cb(app_src, buffer_status_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_src_unset_buffer_status_cb(app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_src_unset_buffer_status_cb_n
 * @since_tizen		3.0
 * @description		Unregisters the source node
 *			buffer status callback function.
 */
int utc_media_streamer_src_unset_buffer_status_cb_n(void)
{
	ret = media_streamer_src_set_buffer_status_cb(app_src, buffer_status_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_src_unset_buffer_status_cb(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_sink_set_data_ready_cb_p
 * @since_tizen		3.0
 * @description		Registers a callback function to be called
 *			when the custom sink is ready for data processing.
 */
int utc_media_streamer_sink_set_data_ready_cb_p(void)
{
	ret = media_streamer_sink_set_data_ready_cb(app_sink, new_buffer_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_sink_set_data_ready_cb_n
 * @since_tizen		3.0
 * @description		Registers a callback function to be called
 *			when the custom sink is ready for data processing.
 */
int utc_media_streamer_sink_set_data_ready_cb_n(void)
{
	ret = media_streamer_sink_set_data_ready_cb(NULL, new_buffer_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_sink_unset_data_ready_cb_p
 * @since_tizen		3.0
 * @description		Unregisters the sink data ready callback function.
 */
int utc_media_streamer_sink_unset_data_ready_cb_p(void)
{
	ret = media_streamer_sink_set_data_ready_cb(app_sink, new_buffer_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_sink_unset_data_ready_cb(app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_sink_unset_data_ready_cb_n
 * @since_tizen		3.0
 * @description		Unregisters the sink data ready callback function.
 */
int utc_media_streamer_sink_unset_data_ready_cb_n(void)
{
	ret = media_streamer_sink_set_data_ready_cb(app_sink, new_buffer_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_sink_unset_data_ready_cb(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_sink_set_eos_cb_p
 * @since_tizen		3.0
 * @description		Registers a callback function to be called
 *			when custom sink detect the end-of-stream.
 */
int utc_media_streamer_sink_set_eos_cb_p(void)
{
	ret = media_streamer_sink_set_eos_cb(app_sink, eos_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_sink_set_eos_cb_n
 * @since_tizen		3.0
 * @description		Registers a callback function to be called
 *			when custom sink detect the end-of-stream.
 */
int utc_media_streamer_sink_set_eos_cb_n(void)
{
	ret = media_streamer_sink_set_eos_cb(NULL, eos_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_sink_unset_eos_cb_p
 * @since_tizen		3.0
 * @description		Unregisters the sink end-of-stream callback function.
 */
int utc_media_streamer_sink_unset_eos_cb_p(void)
{
	ret = media_streamer_sink_set_eos_cb(app_sink, eos_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_sink_unset_eos_cb(app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_sink_unset_eos_cb_n
 * @since_tizen		3.0
 * @description		Unregisters the sink end-of-stream callback function.
 */
int utc_media_streamer_sink_unset_eos_cb_n(void)
{
	ret = media_streamer_sink_set_eos_cb(app_sink, eos_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_sink_unset_eos_cb(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_set_interrupted_cb_p
 * @since_tizen		3.0
 * @description		Registers the interrupted callback function.
 */
int utc_media_streamer_set_interrupted_cb_p(void)
{
	ret = media_streamer_set_interrupted_cb(streamer, interrupted_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_set_interrupted_cb_n
 * @since_tizen		3.0
 * @description		Registers the interrupted callback function.
 */
int utc_media_streamer_set_interrupted_cb_n(void)
{
	ret = media_streamer_set_interrupted_cb(NULL, interrupted_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_unset_interrupted_cb_p
 * @since_tizen		3.0
 * @description		Unregisters the interrupted callback function.
 */
int utc_media_streamer_unset_interrupted_cb_p(void)
{
	ret = media_streamer_set_interrupted_cb(streamer, interrupted_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_unset_interrupted_cb(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_unset_interrupted_cb_n
 * @since_tizen		3.0
 * @description		Unregisters the interrupted callback function.
 */
int utc_media_streamer_unset_interrupted_cb_n(void)
{
	ret = media_streamer_set_interrupted_cb(streamer, interrupted_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_unset_interrupted_cb(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	return 0;
}
