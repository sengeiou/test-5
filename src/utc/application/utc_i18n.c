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
#include "assert_common.h"
#include <string.h>
#include <app.h>

//& set: ApplicationI18n

/**
 * @testcase		utc_application_i18n_get_text_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the localized translation for the specified string.
 * @scenario		Calls the i18n_get_text() and then checks the return value.
 */
int utc_application_i18n_get_text_p(void)
{
	const char *msg_id = "HELLO";
	char *msg;

	msg = i18n_get_text(msg_id);
	assert_with_exit(!strcmp(msg_id, msg));
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_i18n_get_text_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the localized translation for the specified string.
 * @scenario		Calls the i18n_get_text() with the invalid parameter
 *			that the message is NULL, and then checks the return value.
 */
int utc_application_i18n_get_text_n1(void)
{
	char *msg;

	msg = i18n_get_text(NULL);
	assert_eq_with_exit(msg, NULL);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_i18n_get_text_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the localized translation for the specified string.
 * @scenario		Calls the i18n_get_text() and then checks the return value.
 *			This test application does not have Arabic language file.
 */
int utc_application_i18n_get_text_n2(void)
{
	const char *msg_id = "สวัสดีครั";
	char *msg;

	msg = i18n_get_text(msg_id);
	assert_neq_with_exit(strcmp("HELLO", msg), 0);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_i18n_get_text_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the localized translation for the specified string.
 * @scenario		Calls the i18n_get_text() and then checks the return value.
 *			This test application does not have Mongolian language file.
 */
int utc_application_i18n_get_text_n3(void)
{
	const char *msg_id = "Сайн байна уу.";
	char *msg;

	msg = i18n_get_text(msg_id);
	assert_neq_with_exit(strcmp("HELLO", msg), 0);
	normal_exit(0);

	return 0;
}
