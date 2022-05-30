//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include "assert_common.h"
#include "tct_app_common.h"

#include <stdio.h>
#include <app_control_uri.h>

static app_control_uri_h uri;
static app_control_uri_builder_h builder;

/**
 * @function            utc_application_app_control_uri_startup
 * @description         Called before some test
 * @parameter           NA
 * @return              NA
 */
void utc_application_app_control_uri_startup(void)
{
	uri = NULL;
	app_control_uri_builder_create(&builder);
}

void utc_application_app_control_uri_cleanup(void)
{
	app_control_uri_builder_destroy(builder);

	if (uri) {
		app_control_uri_destroy(uri);
		uri = NULL;
	}
}

void __query_cb(const char *key, const char *val, void *user_data)
{
	char **query_val = user_data;
	*query_val = strdup(val);

	return;
}

/**
 * @testcase		utc_application_app_control_uri_create_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Creates the uri handle.
 * @scenario		Creates the uri handle.
 */
int utc_application_app_control_uri_create_p(void)
{
	const char encoded_uri[] = "https:%2F%2Fjohn.doe%40www.example.com%3A123%2Fforum%2Fquestions%2F?tag=networking&order=newest#top";
	app_control_uri_h uri;
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_create(encoded_uri, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_destroy(uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_create_n1
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Creates the uri handle.
 * @scenario		Creates the uri handle with the invalid parameter.
 */
int utc_application_app_control_uri_create_n1(void)
{
	const char encoded_uri[] = "https:%2F%2Fjohn.doe%40www.example.com%3A123%2Fforum%2Fquestions%2F?tag=networking&order=newest#top";
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_create(encoded_uri, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_create_n2
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Creates the uri handle.
 * @scenario		Creates the uri handle with the invalid parameter.
 */
int utc_application_app_control_uri_create_n2(void)
{
	app_control_uri_h uri;
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_create(NULL, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_destroy_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Destroys the uri handle.
 * @scenario		Destroys the uri handle.
 */
int utc_application_app_control_uri_destroy_p(void)
{
	const char encoded_uri[] = "https:%2F%2Fjohn.doe%40www.example.com%3A123%2Fforum%2Fquestions%2F?tag=networking&order=newest#top";
	app_control_uri_h uri;
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_create(encoded_uri, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_destroy(uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_application_app_control_uri_destroy_n
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Destroys the uri handle.
 * @scenario		Destroys the uri handle with the invalid parameter.
 */
int utc_application_app_control_uri_destroy_n(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_destroy(NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_create_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Creates the uri builder handle.
 * @scenario		Creates the uri builder handle.
 */
int utc_application_app_control_uri_builder_create_p(void)
{
	app_control_uri_builder_h _builder;
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_builder_create(&_builder);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_builder_destroy(_builder);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_create_n
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Creates the uri builder handle.
 * @scenario		Creates the uri builder handle with the invalid parameter.
 */
int utc_application_app_control_uri_builder_create_n(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_builder_create(NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_set_scheme_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Sets the scheme to uri builder handle.
 * @scenario		Sets the scheme data to uri builder handle.
 */
int utc_application_app_control_uri_set_scheme_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *scheme = "https";

	ret = app_control_uri_builder_set_scheme(builder, scheme);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_set_scheme_n1
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Sets the scheme to uri builder handle.
 * @scenario		Sets the scheme data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_set_scheme_n1(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_builder_set_scheme(builder, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_set_scheme_n2
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Sets the scheme to uri builder handle.
 * @scenario		Sets the scheme data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_set_scheme_n2(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *scheme = "https";

	ret = app_control_uri_builder_set_scheme(NULL, scheme);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_set_authority_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Sets the authority to uri builder handle.
 * @scenario		Sets the authority data to uri builder handle.
 */
int utc_application_app_control_uri_set_authority_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *authority = "//john.doe@www.example.com:123";

	ret = app_control_uri_builder_set_authority(builder, authority);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_set_authority_n1
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Sets the authority to uri builder handle.
 * @scenario		Sets the authority data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_set_authority_n1(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_builder_set_authority(builder, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_set_authority_n2
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Sets the authority to uri builder handle.
 * @scenario		Sets the authority data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_set_authority_n2(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *authority = "//john.doe@www.example.com:123";

	ret = app_control_uri_builder_set_authority(NULL, authority);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_set_path_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Sets the path to uri builder handle.
 * @scenario		Sets the path data to uri builder handle.
 */
int utc_application_app_control_uri_set_path_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *path = "/forum/questions/";

	ret = app_control_uri_builder_set_path(builder, path);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_set_path_n1
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Sets the path to uri builder handle.
 * @scenario		Sets the path data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_set_path_n1(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_builder_set_path(builder, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_set_path_n2
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Sets the path to uri builder handle.
 * @scenario		Sets the path data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_set_path_n2(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *path = "/forum/questions/";

	ret = app_control_uri_builder_set_path(NULL, path);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_add_path_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Adds the path to uri builder handle.
 * @scenario		Adds the path data to uri builder handle.
 */
int utc_application_app_control_uri_add_path_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *path = "/questions/";

	ret = app_control_uri_builder_add_path(builder, path);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_add_path_n1
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Adds the path to uri builder handle.
 * @scenario		Adds the path data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_add_path_n1(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_builder_add_path(builder, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_add_path_n2
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Adds the path to uri builder handle.
 * @scenario		Adds the path data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_add_path_n2(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *path = "/questions/";

	ret = app_control_uri_builder_add_path(NULL, path);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_set_fragment_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Sets the fragment to uri builder handle.
 * @scenario		Sets the fragment data to uri builder handle.
 */
int utc_application_app_control_uri_set_fragment_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *fragment = "top";

	ret = app_control_uri_builder_set_fragment(builder, fragment);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_set_fragment_n1
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Sets the fragment to uri builder handle.
 * @scenario		Sets the fragment data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_set_fragment_n1(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_builder_set_fragment(builder, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_set_fragment_n22
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Sets the fragment to uri builder handle.
 * @scenario		Sets the fragment data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_set_fragment_n2(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *fragment = "top";

	ret = app_control_uri_builder_set_fragment(NULL, fragment);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_add_query_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Adds the query to uri builder handle.
 * @scenario		Adds the query data to uri builder handle.
 */
int utc_application_app_control_uri_add_query_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *query_key = "tag";
	const char *query_val = "networking";

	ret = app_control_uri_builder_add_query(builder, query_key, query_val);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_add_query_n1
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Adds the query to uri builder handle.
 * @scenario		Adds the query data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_add_query_n1(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *query_val = "networking";

	ret = app_control_uri_builder_add_query(builder, NULL, query_val);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_add_query_n2
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Adds the query to uri builder handle.
 * @scenario		Adds the query data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_add_query_n2(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *query_key = "tag";

	ret = app_control_uri_builder_add_query(builder, query_key, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_add_query_n3
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Adds the query to uri builder handle.
 * @scenario		Adds the query data to uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_add_query_n3(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *query_key = "tag";
	const char *query_val = "networking";

	ret = app_control_uri_builder_add_query(NULL, query_key, query_val);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_build_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Creates a uri builder handle.
 * @scenario		Creates a uri builder handle with the attributes.
 */
int utc_application_app_control_uri_builder_build_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");
    app_control_uri_builder_add_query(builder, "order", "newest");

	ret = app_control_uri_builder_build(builder, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_build_n1
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Creates a uri builder handle.
 * @scenario		Creates a uri builder handle with invalid parameter.
 */
int utc_application_app_control_uri_builder_build_n1(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");
    app_control_uri_builder_add_query(builder, "order", "newest");

	ret = app_control_uri_builder_build(builder, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/*
 * @testcase		utc_application_app_control_uri_builder_build_n2
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Creates a uri builder handle.
 * @scenario		Creates a uri builder handle with invalid parameter.
 */
int utc_application_app_control_uri_builder_build_n2(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_builder_build(NULL, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_destroy_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Destroys a uri builder handle.
 * @scenario		Destroys a uri builder handle.
 */
int utc_application_app_control_uri_builder_destroy_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	app_control_uri_builder_h _builder;

	ret = app_control_uri_builder_create(&_builder);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_builder_destroy(_builder);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_destroy_n
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Destroys a uri builder handle.
 * @scenario		Destroys a uri builder handle with invalid parameter.
 */
int utc_application_app_control_uri_builder_destroy_n(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_builder_destroy(NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_encode_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Encodes the URI handle to string.
 * @scenario		Encodes the URI handle to string by using uri builder.
 */
int utc_application_app_control_uri_encode_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	char *encoded_app_control_uri;

	const char ENCODED_URI1[] = "https:%2F%2Fjohn.doe%40www.example.com%3A123%2Fforum%2Fquestions%2F?tag=networking&order=newest#top";

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");
    app_control_uri_builder_add_query(builder, "order", "newest");

	ret = app_control_uri_builder_build(builder, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_encode(uri, &encoded_app_control_uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	assert_with_exit(!strcmp(encoded_app_control_uri, ENCODED_URI1));

	if (encoded_app_control_uri)
		free(encoded_app_control_uri);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_encode_n
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Encodes the URI handle to string.
 * @scenario		Encodes the URI handle to string with invalid parameter.
 */
int utc_application_app_control_uri_encode_n(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	char *encoded_app_control_uri;

	ret = app_control_uri_encode(NULL, &encoded_app_control_uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_scheme_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Gets the scheme from uri builder handle.
 * @scenario		Gets the scheme data from uri builder handle.
 */
int utc_application_app_control_uri_get_scheme_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_scheme;

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");
    app_control_uri_builder_add_query(builder, "order", "newest");

	ret = app_control_uri_builder_build(builder, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_get_scheme(uri, &get_scheme);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	assert_with_exit(!strcmp("https", get_scheme));

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_scheme_n
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Gets the scheme from uri builder handle.
 * @scenario		Gets the scheme data from uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_get_scheme_n(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_scheme;

	ret = app_control_uri_get_scheme(NULL, &get_scheme);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_authority_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Gets the authority from uri builder handle.
 * @scenario		Gets the authority data from uri builder handle.
 */
int utc_application_app_control_uri_get_authority_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_authority;

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");
    app_control_uri_builder_add_query(builder, "order", "newest");

	ret = app_control_uri_builder_build(builder, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_get_authority(uri, &get_authority);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	assert_with_exit(!strcmp("//john.doe@www.example.com:123", get_authority));

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_authority_n
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Gets the authority from uri builder handle.
 * @scenario		Gets the authority data from uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_get_authority_n(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_authority;

	ret = app_control_uri_get_authority(NULL, &get_authority);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_path_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Gets the path from uri builder handle.
 * @scenario		Gets the path data from uri builder handle.
 */
int utc_application_app_control_uri_get_path_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_path;

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");
    app_control_uri_builder_add_query(builder, "order", "newest");

	ret = app_control_uri_builder_build(builder, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_get_path(uri, &get_path);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	assert_with_exit(!strcmp("/forum/questions/", get_path));

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_path_n
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Gets the path from uri builder handle.
 * @scenario		Gets the path data from uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_get_path_n(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_path;

	ret = app_control_uri_get_path(NULL, &get_path);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_fragment_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Gets the fragment from uri builder handle.
 * @scenario		Gets the fragment data from uri builder handle.
 */
int utc_application_app_control_uri_get_fragment_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_fragment;

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");
    app_control_uri_builder_add_query(builder, "order", "newest");

	ret = app_control_uri_builder_build(builder, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_get_fragment(uri, &get_fragment);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	assert_with_exit(!strcmp("top", get_fragment));

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_fragment_n
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Gets the fragment from uri builder handle.
 * @scenario		Gets the fragment data from uri builder handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_get_fragment_n(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_fragment;

	ret = app_control_uri_get_fragment(NULL, &get_fragment);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_host_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Gets the host from uri builder handle.
 * @scenario		Gets the host data from uri builder handle.
 */
int utc_application_app_control_uri_get_host_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_host;

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");
    app_control_uri_builder_add_query(builder, "order", "newest");

	ret = app_control_uri_builder_build(builder, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_get_host(uri, &get_host);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	assert_with_exit(!strcmp("www.example.com", get_host));

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_host_n
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Gets the host from uri handle.
 * @scenario		Gets the host data from uri handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_get_host_n(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_host;

	ret = app_control_uri_get_host(NULL, &get_host);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_port_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Gets the port from uri handle.
 * @scenario		Gets the port data from uri handle.
 */
int utc_application_app_control_uri_get_port_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_port;

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");
    app_control_uri_builder_add_query(builder, "order", "newest");

	ret = app_control_uri_builder_build(builder, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_get_port(uri, &get_port);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	assert_with_exit(!strcmp("123", get_port));

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_port_n
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Gets the port from uri handle.
 * @scenario		Gets the port data from uri handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_get_port_n(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_port;

	ret = app_control_uri_get_port(NULL, &get_port);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_user_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Gets the user from uri handle.
 * @scenario		Gets the user data from uri handle.
 */
int utc_application_app_control_uri_get_user_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_user;

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");
    app_control_uri_builder_add_query(builder, "order", "newest");

	ret = app_control_uri_builder_build(builder, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_get_user(uri, &get_user);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	assert_with_exit(!strcmp("john.doe", get_user));

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_user_n
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Gets the user from uri handle.
 * @scenario		Gets the user data from uri handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_get_user_n(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	const char *get_user;

	ret = app_control_uri_get_user(NULL, &get_user);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_query_p
 * @since_tizen		5.5
 * @type	 	 	Positive
 * @description		Gets the query from uri handle.
 * @scenario		Gets the query data from uri handle.
 */
int utc_application_app_control_uri_get_query_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	app_control_uri_query_h query;

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");
    app_control_uri_builder_add_query(builder, "order", "newest");

	ret = app_control_uri_builder_build(builder, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_get_query(uri, &query);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_builder_get_query_n
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Gets the query from uri handle.
 * @scenario		Gets the query data from uri handle with invalid
 *                  parameter.
 */
int utc_application_app_control_uri_get_query_n(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	app_control_uri_query_h query;

	ret = app_control_uri_get_query(NULL, &query);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_query_foreach_p
 * @since_tizen		5.5
 * @type			Positive
 * @description		Retrieves the key-value pairs attributes in the query.
 * @scenario		Retrieves the key-value pairs attributes in the query handle.
 */
int utc_application_app_control_uri_query_foreach_p(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	app_control_uri_query_h query;
	char *get_query_val = NULL;

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");

	ret = app_control_uri_builder_build(builder, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_get_query(uri, &query);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_query_foreach(query, __query_cb, &get_query_val);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	assert_with_exit(!strcmp("networking", get_query_val));

	if (get_query_val)
		free(get_query_val);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_query_foreach_n1
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Retrieves the key-value pairs attributes in the query.
 * @scenario		Retrieves the key-value pairs attributes in the query
 * 					handle with invalid parameter.
 */
int utc_application_app_control_uri_query_foreach_n1(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;

	ret = app_control_uri_query_foreach(NULL, __query_cb, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_application_app_control_uri_query_foreach_n2
 * @since_tizen		5.5
 * @type	 	 	Negative
 * @description		Retrieves the key-value pairs attributes in the query.
 * @scenario		Retrieves the key-value pairs attributes in the query
 * 					handle with invalid parameter.
 */
int utc_application_app_control_uri_query_foreach_n2(void)
{
	int ret = APP_CONTROL_URI_ERROR_NONE;
	app_control_uri_query_h query;

    app_control_uri_builder_set_scheme(builder, "https");
    app_control_uri_builder_set_authority(builder,
        "//john.doe@www.example.com:123");
    app_control_uri_builder_set_path(builder, "/forum/questions/");
    app_control_uri_builder_set_fragment(builder, "top");
    app_control_uri_builder_add_query(builder, "tag", "networking");

	ret = app_control_uri_builder_build(builder, &uri);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_get_query(uri, &query);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_NONE);

	ret = app_control_uri_query_foreach(query, NULL, NULL);
	assert_eq_with_exit(ret, APP_CONTROL_URI_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}
