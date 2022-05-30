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
#include <mime_type.h>
#include <string.h>
#include <app.h>

//& set: Mime-type

#define SAFE_FREE(src)      { if(src) {free(src); src = NULL;}}

#define TEST_FILE "test.html"
#define TEST_FILE_SIZE 50
#define TEST_FILE_TYPE "text/html"

static char *mime_type;
static char **file_extension;
static int length;
static char file_path[4096];
static char file_data[TEST_FILE_SIZE];

/**
 * @function		utc_mime_type_get_mime_type_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_mime_type_get_mime_type_startup(void)
{
    mime_type = NULL;
    file_extension = NULL;
    length = 0;
}
/**
 * @function		utc_mime_type_get_mime_type_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_mime_type_get_mime_type_cleanup(void)
{
    int i;

    SAFE_FREE(mime_type);

    if (file_extension) {
	for (i = 0; i < length; i++)
		free(file_extension[i]);
	free(file_extension);
    }
}


void utc_mime_type_get_mime_type_for_file_startup(void)
{
    char *res_path = NULL;
    utc_mime_type_get_mime_type_startup();

    if (file_path[0] != 0)
	return;

    res_path = app_get_resource_path();
    if (!res_path)
	return;

    snprintf(file_path, sizeof(file_path), "%s%s", res_path, TEST_FILE);
    free(res_path);
}

void utc_mime_type_get_mime_type_for_file_cleanup(void)
{
    utc_mime_type_get_mime_type_cleanup();
}

void utc_mime_type_get_mime_type_for_data_startup(void)
{
    FILE *file;
    int read;

    utc_mime_type_get_mime_type_for_file_startup();

    if (file_data[0] != 0)
	return;

    file = fopen(file_path, "r");
    if (!file) {
	fprintf(stderr, "unable to open file:%s\n", file_path);
	return;
    }

    read = fread(file_data, 1, TEST_FILE_SIZE, file);
    if (read < TEST_FILE_SIZE) {
	fprintf(stderr, "failed to read, bytes expected: %d actual: %d\n",
		TEST_FILE_SIZE, read);
    }

    fclose(file);
}

void utc_mime_type_get_mime_type_for_data_cleanup(void)
{
    utc_mime_type_get_mime_type_for_file_cleanup();
}


/**
 * @testcase		utc_mime_type_get_mime_type_p1
 * @since_tizen		2.3
 * @description		Get mime type
 * @scenario		Get png mime type, check return value and mime type.
 */
int utc_mime_type_get_mime_type_p1(void)
{
    int retcode;

    retcode = mime_type_get_mime_type("png", &mime_type);

    assert_eq(retcode, MIME_TYPE_ERROR_NONE);
    assert_eq(strcmp(mime_type, "image/png"), 0);

    return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_type_p2
 * @since_tizen		2.3
 * @description		Get mime type
 * @scenario		Get jpg mime type, check return value and mime type.
 */
int utc_mime_type_get_mime_type_p2(void)
{
    int retcode;

    retcode = mime_type_get_mime_type("jpg", &mime_type);

    assert_eq(retcode, MIME_TYPE_ERROR_NONE);
    assert_eq(strcmp(mime_type, "image/jpeg"), 0);

    return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_type_p3
 * @since_tizen		2.3
 * @description		Get mime type
 * @scenario		Get mpg mime type, check return value and mime type.
 */
int utc_mime_type_get_mime_type_p3(void)
{
    int retcode;

    retcode = mime_type_get_mime_type("mpg", &mime_type);

    assert_eq(retcode, MIME_TYPE_ERROR_NONE);
    assert_eq(strcmp(mime_type, "video/mpeg"), 0);

    return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_type_p4
 * @since_tizen		2.3
 * @description		Get mime type
 * @scenario		Get mp3 mime type, check return value and mime type.
 */
int utc_mime_type_get_mime_type_p4(void)
{
    int retcode;

    retcode = mime_type_get_mime_type("mp3", &mime_type);

    assert_eq(retcode, MIME_TYPE_ERROR_NONE);
    assert_eq(strcmp(mime_type, "audio/mpeg"), 0);

    return 0;
}


/**
 * @testcase		utc_mime_type_get_mime_type_p5
 * @since_tizen		2.3
 * @description		Get mime type
 * @scenario		Get bin mime type, check return value and mime type.
 */
int utc_mime_type_get_mime_type_p5(void)
{
    int retcode;

    retcode = mime_type_get_mime_type("bin", &mime_type);

    assert_eq(retcode, MIME_TYPE_ERROR_NONE);
    assert_eq(strcmp(mime_type, "application/octet-stream"), 0);

    return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_type_p6
 * @since_tizen		2.3
 * @description		Get mime type
 * @scenario		Get abcdef mime type, check return value and mime type.
 */
int utc_mime_type_get_mime_type_p6(void)
{
    int retcode;

    retcode = mime_type_get_mime_type("abcdef", &mime_type);

    assert_eq(retcode, MIME_TYPE_ERROR_NONE);
    assert_eq(strcmp(mime_type, "application/octet-stream"), 0);

    return 0;
}


/**
 * @testcase		utc_mime_type_get_mime_type_n1
 * @since_tizen		2.3
 * @description		Get mime type
 * @scenario		Get mime type with invalid parameter and check return value.
 */
int utc_mime_type_get_mime_type_n1(void)
{
    int retcode;

    retcode = mime_type_get_mime_type(NULL, &mime_type);

    assert_eq(retcode, MIME_TYPE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_type_n2
 * @since_tizen		2.3
 * @description		Get mime type
 * @scenario		Get mime type with invalid parameter and check return value.
 */
int utc_mime_type_get_mime_type_n2(void)
{
    int retcode;

    retcode = mime_type_get_mime_type("", &mime_type);

    assert_eq(retcode, MIME_TYPE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_type_n3
 * @since_tizen		2.3
 * @description		Get mime type
 * @scenario		Get mime type with invalid parameter and check return value.
 */
int utc_mime_type_get_mime_type_n3(void)
{
    int retcode;

    retcode = mime_type_get_mime_type("mp3", NULL);

    assert_eq(retcode, MIME_TYPE_ERROR_INVALID_PARAMETER);

    return 0;
}


/**
 * @testcase		utc_mime_type_get_file_extension_p1
 * @since_tizen		2.3
 * @description		Get file extension
 * @scenario		Get file extension and check return value.
 */
int utc_mime_type_get_file_extension_p1(void)
{
    int retcode;
    const char *mime_type = "video/mpeg";

    retcode = mime_type_get_file_extension(mime_type, &file_extension, &length);

    assert_eq(retcode, MIME_TYPE_ERROR_NONE);
    assert_gt(length, 0);

    return 0;
}

/**
 * @testcase		utc_mime_type_get_file_extension_p2
 * @since_tizen		2.3
 * @description		Get file extension
 * @scenario		Get file extension, check return value and length.
 */
int utc_mime_type_get_file_extension_p2(void)
{
    int retcode;
    const char *mime_type = "image/jpeg";

    retcode = mime_type_get_file_extension(mime_type, &file_extension, &length);

    assert_eq(retcode, MIME_TYPE_ERROR_NONE);
    assert_gt(length, 0);

    return 0;
}

/**
 * @testcase		utc_mime_type_get_file_extension_n1
 * @since_tizen		2.3
 * @description		Get file extension
 * @scenario		Get file extension with invalid argument and check return value.
 */
int utc_mime_type_get_file_extension_n1(void)
{
    int retcode;

    retcode = mime_type_get_file_extension(NULL, &file_extension, &length);

    assert_eq(retcode, MIME_TYPE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_mime_type_get_file_extension_n2
 * @since_tizen		2.3
 * @description		Get file extension
 * @scenario		Get file extension with invalid argument and check return value.
 */
int utc_mime_type_get_file_extension_n2(void)
{
    int retcode;

    retcode = mime_type_get_file_extension("", &file_extension, &length);

    assert_eq(retcode, MIME_TYPE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_mime_type_get_file_extension_n3
 * @since_tizen		2.3
 * @description		Get file extension
 * @scenario		Get file extension with invalid argument and check return value.
 */
int utc_mime_type_get_file_extension_n3(void)
{
    int retcode;
    const char *mime_type = "image/jpeg";

    retcode = mime_type_get_file_extension(mime_type, NULL, &length);

    assert_eq(retcode, MIME_TYPE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_mime_type_get_file_extension_n4
 * @since_tizen		2.3
 * @description		Get file extension
 * @scenario		Get file extension with invalid argument and check return value.
 */
int utc_mime_type_get_file_extension_n4(void)
{
    int retcode;

    const char *mime_type = "image/jpeg";

    retcode = mime_type_get_file_extension(mime_type, &file_extension, NULL);

    assert_eq(retcode, MIME_TYPE_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_type_for_file_p1
 * @since_tizen		4.0
 * @description		Get mime type of file
 * @scenario		Get mime type with file path and check return value
 */
int utc_mime_type_get_mime_type_for_file_p1(void)
{
	int retcode;
	char *mime_type = NULL;

	retcode = mime_type_get_mime_type_for_file(file_path, &mime_type);

	assert_eq(retcode, MIME_TYPE_ERROR_NONE);
	assert_eq(strcmp(TEST_FILE_TYPE, mime_type), 0);

	return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_type_for_file_n1
 * @since_tizen		4.0
 * @description		Get mime type of file
 * @scenario		Get mime type with file path and check return value
 */
int utc_mime_type_get_mime_type_for_file_n1(void)
{
	int retcode;
	char *mime_type = NULL;

	retcode = mime_type_get_mime_type_for_file(NULL, &mime_type);

	assert_eq(retcode, MIME_TYPE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_type_for_file_n2
 * @since_tizen		4.0
 * @description		Get mime type of file
 * @scenario		Get mime type with file path and check return value
 */
int utc_mime_type_get_mime_type_for_file_n2(void)
{
	int retcode;
	char *mime_type = NULL;

	retcode = mime_type_get_mime_type_for_file("", &mime_type);

	assert_eq(retcode, MIME_TYPE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_type_for_file_n3
 * @since_tizen		4.0
 * @description		Get mime type of file
 * @scenario		Get mime type with file path and check return value
 */
int utc_mime_type_get_mime_type_for_file_n3(void)
{
	int retcode;

	retcode = mime_type_get_mime_type_for_file(file_path, NULL);

	assert_eq(retcode, MIME_TYPE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_data_for_file_p1
 * @since_tizen		4.0
 * @description		Get mime type of data
 * @scenario		Get mime type with data and check return value
 */
int utc_mime_type_get_mime_type_for_data_p1(void)
{
	int retcode;
	char *mime_type = NULL;
	char *data = file_data;
	size_t size = sizeof(file_data);

	retcode = mime_type_get_mime_type_for_data(data, size, &mime_type);

	assert_eq(retcode, MIME_TYPE_ERROR_NONE);
	assert_eq(strncmp(TEST_FILE_TYPE, mime_type, sizeof(TEST_FILE_TYPE)), 0);

	free(mime_type);

	return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_type_for_data_n1
 * @since_tizen		4.0
 * @description		Get mime type of data
 * @scenario		Get mime type with data and check return value
 */
int utc_mime_type_get_mime_type_for_data_n1(void)
{
	int retcode;
	char *mime_type = NULL;

	retcode = mime_type_get_mime_type_for_data(NULL, 0, &mime_type);

	assert_eq(retcode, MIME_TYPE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_mime_type_get_mime_type_for_data_n3
 * @since_tizen		4.0
 * @description		Get mime type of data
 * @scenario		Get mime type with data and check return value
 */
int utc_mime_type_get_mime_type_for_data_n2(void)
{
	int retcode;
	char *data = file_data;
	size_t size = sizeof(file_data);

	retcode = mime_type_get_mime_type_for_data(data, size, NULL);

	assert_eq(retcode, MIME_TYPE_ERROR_INVALID_PARAMETER);

	return 0;
}
