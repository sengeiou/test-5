//
// Copyright (c) 2014-2020 Samsung Electronics Co., Ltd.
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
#include <dlog.h>
#include <privilege_information.h>
#include <stdio.h>
#include <glib.h>
#include "assert.h"

#define _free(var) \
    if (var != NULL) { \
        free(var); \
    }

static bool privacy_supported = true;

/**
 * @function        utc_privilege_info_startup
 * @description     Called before each test
 */
void utc_privilege_info_startup(void)
{
    system_info_get_platform_bool("http://tizen.org/feature/security.privacy_privilege", &privacy_supported);
}

/**
 * @testcase        utc_privilege_info_get_display_name_p1
 * @since_tizen     2.3
 * @description     Get privilege display name
 *                  - get privilege display name with valid core/web privilege name
 */
int utc_privilege_info_get_display_name_p1(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version = "2.3";
    char* display_name = NULL;
    char* privilege_name = "http://tizen.org/privilege/internet";

    ret = privilege_info_get_display_name(api_version, privilege_name, &display_name);
    _free(display_name);
    assert_eq(ret, PRVINFO_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_display_name_p2
 * @since_tizen     2.3
 * @description     Get privilege display name
 *                  - get privilege display name with valid web privilege name
 */
int utc_privilege_info_get_display_name_p2(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version = "2.3";
    char* display_name = NULL;
    char* web_privilege_name = "http://tizen.org/privilege/mediacapture";

    ret = privilege_info_get_display_name(api_version, web_privilege_name, &display_name);
    _free(display_name);
    assert_eq(ret, PRVINFO_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_display_name_n1
 * @since_tizen     2.3
 * @description     Get privilege display name
 *                  - get privilege display name with null input parameters
 */
int utc_privilege_info_get_display_name_n1(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* display_name = NULL;

    ret = privilege_info_get_display_name(NULL, NULL, &display_name);
    _free(display_name);
    assert_eq(ret, PRVINFO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_display_name_n2
 * @since_tizen     6.0
 * @description     Get privilege display name
 *                  - get privilege display name with invalid privilege name
 */
int utc_privilege_info_get_display_name_n2(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version = "2.3";
    char* display_name = NULL;
    char* not_exist_privilege_name = "http://tizen.org/privilege/badge.adminnnnnnnnn";

    ret = privilege_info_get_display_name(api_version, not_exist_privilege_name, &display_name);
    _free(display_name);
    assert_eq(ret, PRVINFO_ERROR_NO_MATCHING_PRIVILEGE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_description_p1
 * @since_tizen     2.3
 * @description     Get privilege description
 *                  - get privilege description with valid core/web privilege name
 */
int utc_privilege_info_get_description_p1(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version="2.3";
    char* description = NULL;
    char* privilege_name = "http://tizen.org/privilege/internet";

    ret = privilege_info_get_description(api_version, privilege_name, &description);
    _free(description);
    assert_eq(ret, PRVINFO_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_description_p2
 * @since_tizen     2.3
 * @description     Get privilege description
 *                  - get privilege description with valid web privilege name
 */
int utc_privilege_info_get_description_p2(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version="2.3";
    char* description = NULL;
    char* web_privilege_name = "http://tizen.org/privilege/mediacapture";

    ret = privilege_info_get_description(api_version, web_privilege_name, &description);
    _free(description);
    assert_eq(ret, PRVINFO_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_description_n1
 * @since_tizen     2.3
 * @description     Get privilege description
 *                  - get privilege description with null input parameters
 */
int utc_privilege_info_get_description_n1(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* description = NULL;

    ret = privilege_info_get_description(NULL, NULL, &description);
    _free(description);
    assert_eq(ret, PRVINFO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_description_n2
 * @since_tizen     6.0
 * @description     Get privilege description
 *                  - get privilege description with invalid privilege name
 */
int utc_privilege_info_get_description_n2(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version = "2.3";
    char* description = NULL;
    char* not_exist_privilege_name = "http://tizen.org/privilege/badge.adminnnnnnnnn";

    ret = privilege_info_get_description(api_version, not_exist_privilege_name, &description);
    _free(description);
    assert_eq(ret, PRVINFO_ERROR_NO_MATCHING_PRIVILEGE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_display_name_by_pkgtype_p1
 * @since_tizen     2.3
 * @description     Get privilege display name with package type
 *                  - get privilege display name with valid privilege name and package type
 */
int utc_privilege_info_get_display_name_by_pkgtype_p1(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version = "2.3";
    const char* package_type = "PRVINFO_PACKAGE_TYPE_NATIVE";
    char* display_name = NULL;
    char* core_privilege_name = "http://tizen.org/privilege/internet";

    ret = privilege_info_get_display_name_by_pkgtype(package_type, api_version, core_privilege_name, &display_name);
    _free(display_name);
    assert_eq(ret, PRVINFO_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_display_name_by_pkgtype_p2
 * @since_tizen     2.3
 * @description     Get privilege display name with package type
 *                  - get privilege display name with valid web privilege name and package type
 */
int utc_privilege_info_get_display_name_by_pkgtype_p2(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version = "2.3";
    const char* package_type = "PRVINFO_PACKAGE_TYPE_WEB";
    char* display_name = NULL;
    char* web_privilege_name = "http://tizen.org/privilege/mediacapture";

    ret = privilege_info_get_display_name_by_pkgtype(package_type, api_version, web_privilege_name, &display_name);
    _free(display_name);
    assert_eq(ret, PRVINFO_ERROR_NONE);
    return 0;
}


/**
 * @testcase        utc_privilege_info_get_display_name_by_pkgtype_n1
 * @since_tizen     2.3
 * @description     Get privilege display name with package type
 *                  - get privilege display name with null input parameters
 */
int utc_privilege_info_get_display_name_by_pkgtype_n1(void)
{
    int ret = PRVINFO_ERROR_NONE;
    const char* package_type = "PRVINFO_PACKAGE_TYPE_NATIVE";
    char* display_name = NULL;

    ret = privilege_info_get_display_name_by_pkgtype(package_type, NULL, NULL, &display_name);
    _free(display_name);
    assert_eq(ret, PRVINFO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_display_name_by_pkgtype_n2
 * @since_tizen     2.3
 * @description     Get privilege display name with package type
 *                  - get privilege display name with invalid package type parameters
 */
int utc_privilege_info_get_display_name_by_pkgtype_n2(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version = "2.3";
    const char* package_type = "PRVINFO_PACKAGE_TYPE_WRONG";
    char* display_name = NULL;
    char* privilege_name = "http://tizen.org/privilege/internet";

    ret = privilege_info_get_display_name_by_pkgtype(package_type, api_version, privilege_name, &display_name);
    _free(display_name);
    assert_eq(ret, PRVINFO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_display_name_by_pkgtype_n3
 * @since_tizen     6.0
 * @description     Get privilege display name with package type
 *                  - get privilege display name with invalid privilege name and valid package type
 */
int utc_privilege_info_get_display_name_by_pkgtype_n3(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version = "2.3";
    const char* package_type = "PRVINFO_PACKAGE_TYPE_WEB";
    char* display_name = NULL;
    char* not_exist_privilege_name = "http://tizen.org/privilege/badge.adminnnnnnnnn";

    ret = privilege_info_get_display_name_by_pkgtype(package_type, api_version, not_exist_privilege_name, &display_name);
    _free(display_name);
    assert_eq(ret, PRVINFO_ERROR_NO_MATCHING_PRIVILEGE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_display_name_by_pkgtype_n4
 * @since_tizen     6.0
 * @description     Get privilege display name with package type
 *                  - get privilege display name with valid privilege name and mismatched package type
 */
int utc_privilege_info_get_display_name_by_pkgtype_n4(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version = "2.3";
    const char* native_package_type = "PRVINFO_PACKAGE_TYPE_NATIVE";
    char* display_name = NULL;
    char* web_privilege_name = "http://tizen.org/privilege/filesystem.read";

    ret = privilege_info_get_display_name_by_pkgtype(native_package_type, api_version, web_privilege_name, &display_name);
    _free(display_name);
    assert_eq(ret, PRVINFO_ERROR_NO_MATCHING_PRIVILEGE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_description_by_pkgtype_p1
 * @since_tizen     2.3
 * @description     Get privilege description with package type
 *                  - get privilege description with valid privilege name and package type
 */
int utc_privilege_info_get_description_by_pkgtype_p1(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version="2.3";
    const char* package_type = "PRVINFO_PACKAGE_TYPE_NATIVE";
    char* description = NULL;
    char* core_privilege_name = "http://tizen.org/privilege/internet";

    ret = privilege_info_get_description_by_pkgtype(package_type, api_version, core_privilege_name, &description);
    _free(description);
    assert_eq(ret, PRVINFO_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_description_by_pkgtype_p2
 * @since_tizen     2.3
 * @description     Get privilege description with package type
 *                  - get privilege description with valid web privilege name and package type
 */
int utc_privilege_info_get_description_by_pkgtype_p2(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version="2.3";
    const char* package_type = "PRVINFO_PACKAGE_TYPE_WEB";
    char* description = NULL;
    char* web_privilege_name = "http://tizen.org/privilege/mediacapture";

    ret = privilege_info_get_description_by_pkgtype(package_type, api_version, web_privilege_name, &description);
    _free(description);
    assert_eq(ret, PRVINFO_ERROR_NONE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_description_by_pkgtype_n1
 * @since_tizen     2.3
 * @description     Get privilege description with package type
 *                  - get privilege description with null input parameters
 */
int utc_privilege_info_get_description_by_pkgtype_n1(void)
{
    int ret = PRVINFO_ERROR_NONE;
    const char* package_type = "PRVINFO_PACKAGE_TYPE_NATIVE";
    char* description = NULL;

    ret = privilege_info_get_description_by_pkgtype(package_type, NULL, NULL, &description);
    _free(description);
    assert_eq(ret, PRVINFO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_description_by_pkgtype_n2
 * @since_tizen     2.3
 * @description     Get privilege description with package type
 *                  - get privilege description with invalid package type parameters
 */
int utc_privilege_info_get_description_by_pkgtype_n2(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version = "2.3";
    const char* package_type = "PRVINFO_PACKAGE_TYPE_WRONG";
    char* description = NULL;
    char* privilege_name = "http://tizen.org/privilege/internet";

    ret = privilege_info_get_description_by_pkgtype(package_type, api_version, privilege_name, &description);
    _free(description);
    assert_eq(ret, PRVINFO_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_description_by_pkgtype_n3
 * @since_tizen     6.0
 * @description     Get privilege description with package type
 *                  - get privilege description with invalid privilege name and valid package type
 */
int utc_privilege_info_get_description_by_pkgtype_n3(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version = "2.3";
    const char* package_type = "PRVINFO_PACKAGE_TYPE_WEB";
    char* description = NULL;
    char* not_exist_privilege_name = "http://tizen.org/privilege/badge.adminnnnnnnnn";

    ret = privilege_info_get_description_by_pkgtype(package_type, api_version, not_exist_privilege_name, &description);
    _free(description);
    assert_eq(ret, PRVINFO_ERROR_NO_MATCHING_PRIVILEGE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_description_by_pkgtype_n4
 * @since_tizen     6.0
 * @description     Get privilege description with package type
 *                  - get privilege description with valid privilege name and mismatched package type
 */
int utc_privilege_info_get_description_by_pkgtype_n4(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* api_version = "2.3";
    const char* native_package_type = "PRVINFO_PACKAGE_TYPE_NATIVE";
    char* description = NULL;
    char* web_privilege_name = "http://tizen.org/privilege/filesystem.read";

    ret = privilege_info_get_display_name_by_pkgtype(native_package_type, api_version, web_privilege_name, &description);
    _free(description);
    assert_eq(ret, PRVINFO_ERROR_NO_MATCHING_PRIVILEGE);
    return 0;
}

/**
 * @testcase        utc_privilege_info_get_privacy_display_name_p
 * @since_tizen     3.0
 * @description     Gets privacy group's display name in which the given privilege is included
 *                  - get privacy display name with privacy related privilege
 */
int utc_privilege_info_get_privacy_display_name_p(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* privacy_display_name = NULL;
    const char* privilege = "http://tizen.org/privilege/account.read";

    ret = privilege_info_get_privacy_display_name(privilege, &privacy_display_name);

    if (privacy_supported) {
        _free(privacy_display_name);
        assert_eq(ret, PRVINFO_ERROR_NONE);
    } else {
        assert_eq(ret, PRVINFO_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_privacy_display_name_n1
 * @since_tizen     3.0
 * @description     Gets privacy group's display name in which the given privilege is included
 *                  - get privacy display name with privilege that is not related to privacy
 */
int utc_privilege_info_get_privacy_display_name_n1(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* privacy_display_name = NULL;
    const char* privilege = "http://tizen.org/privilege/aaaaaa";

    ret = privilege_info_get_privacy_display_name(privilege, &privacy_display_name);
    if (privacy_supported) {
        _free(privacy_display_name);
        assert_eq(ret, PRVINFO_ERROR_INVALID_PARAMETER);
    } else {
        assert_eq(ret, PRVINFO_ERROR_NOT_SUPPORTED);
    }
    assert_eq(privacy_display_name, NULL);

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_privacy_display_name_n2
 * @since_tizen     3.0
 * @description     Gets privacy group's display name in which the given privilege is included
 *                  - get privacy display name with null input parameter
 */
int utc_privilege_info_get_privacy_display_name_n2(void)
{
    int ret = PRVINFO_ERROR_NONE;
    char* privacy_display_name = NULL;

    ret = privilege_info_get_privacy_display_name(NULL, &privacy_display_name);

    if (privacy_supported) {
        _free(privacy_display_name);
        assert_eq(ret, PRVINFO_ERROR_INVALID_PARAMETER);
    } else {
        assert_eq(ret, PRVINFO_ERROR_NOT_SUPPORTED);
    }
    assert_eq(privacy_display_name, NULL);

    return 0;
}

static void __free_privilege_info(privilege_info_s* privilege_info)
{
    if (privilege_info->privilege_name)
        free(privilege_info->privilege_name);

    if (privilege_info->display_name)
        free(privilege_info->display_name);

    if (privilege_info->description)
        free(privilege_info->description);
}

static void __free_privilege_info_list(gpointer privilege_info_list)
{
    __free_privilege_info((privilege_info_s*)privilege_info_list);
}

/**
 * @testcase        utc_privilege_info_get_privilege_info_list_p1
 * @since_tizen     5.5
 * @description     Gets privilege info list with valid locale and privilege names
 */
int utc_privilege_info_get_privilege_info_list_p1(void)
{
    int ret = PRVINFO_ERROR_NONE;
    privilege_consumer_return_code_e return_result = PRIVILEGE_CONSUMER_RETURN_CODE_SUCCESS;

    GList* privilege_name_list = NULL;
    GList* privilege_info_list = NULL;

    const char* locale = "ko_KR.UTF8";

    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/internet");
    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/call");
    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/mediastorage");

    ret = privilege_info_get_privilege_info_list(locale, privilege_name_list, &privilege_info_list, &return_result);

    g_list_free(privilege_name_list);
    g_list_free_full(privilege_info_list, __free_privilege_info_list);

    assert_eq(ret, PRVINFO_ERROR_NONE);
    assert_eq(return_result, PRIVILEGE_CONSUMER_RETURN_CODE_SUCCESS);

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_privilege_info_list_p2
 * @since_tizen     5.5
 * @description     Gets privilege info list with valid locale and some invalid privilege names
 */
int utc_privilege_info_get_privilege_info_list_p2(void)
{
    int ret = PRVINFO_ERROR_NONE;
    privilege_consumer_return_code_e return_result = PRIVILEGE_CONSUMER_RETURN_CODE_SUCCESS;

    GList* privilege_name_list = NULL;
    GList* privilege_info_list = NULL;

    const char* locale = "ko_KR.UTF8";

    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/internet");
    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/mediastorage");
    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/not_exist_privilege_name");
    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/unknown_privilege");

    ret = privilege_info_get_privilege_info_list(locale, privilege_name_list, &privilege_info_list, &return_result);

    g_list_free(privilege_name_list);
    g_list_free_full(privilege_info_list, __free_privilege_info_list);

    assert_eq(ret, PRVINFO_ERROR_NONE);
    assert_eq(return_result, PRIVILEGE_CONSUMER_RETURN_CODE_SUCCESS);

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_privilege_info_list_p3
 * @since_tizen     5.5
 * @description     Gets privilege info list with valid locale and all invalid privilege names
 */
int utc_privilege_info_get_privilege_info_list_p3(void)
{
    int ret = PRVINFO_ERROR_NONE;
    privilege_consumer_return_code_e return_result = PRIVILEGE_CONSUMER_RETURN_CODE_SUCCESS;

    GList* privilege_name_list = NULL;
    GList* privilege_info_list = NULL;

    const char* locale = "ko_KR.UTF8";

    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/not_exist_privilege_name");
    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/unknown_privilege");
    privilege_name_list = g_list_append(privilege_name_list, "xxxxxx");

    ret = privilege_info_get_privilege_info_list(locale, privilege_name_list, &privilege_info_list, &return_result);

    g_list_free(privilege_name_list);
    g_list_free_full(privilege_info_list, __free_privilege_info_list);

    assert_eq(ret, PRVINFO_ERROR_NONE);
    assert_eq(return_result, PRIVILEGE_CONSUMER_RETURN_CODE_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_privilege_info_list_p4
 * @since_tizen     5.5
 * @description     Gets privilege info list with invalid locale and valid privilege names
 */
int utc_privilege_info_get_privilege_info_list_p4(void)
{
    int ret = PRVINFO_ERROR_NONE;
    privilege_consumer_return_code_e return_result = PRIVILEGE_CONSUMER_RETURN_CODE_SUCCESS;

    GList* privilege_name_list = NULL;
    GList* privilege_info_list = NULL;

    const char* locale = "xxx";

    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/internet");
    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/call");
    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/mediastorage");

    ret = privilege_info_get_privilege_info_list(locale, privilege_name_list, &privilege_info_list, &return_result);

    g_list_free(privilege_name_list);
    g_list_free_full(privilege_info_list, __free_privilege_info_list);

    assert_eq(ret, PRVINFO_ERROR_NONE);
    assert_eq(return_result, PRIVILEGE_CONSUMER_RETURN_CODE_UNKNOWN_LOCALE_CODE);

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_privilege_info_list_p5
 * @since_tizen     5.5
 * @description     Gets privilege info list with invalid locale and all invalid privilege names
 */
int utc_privilege_info_get_privilege_info_list_p5(void)
{
    int ret = PRVINFO_ERROR_NONE;
    privilege_consumer_return_code_e return_result = PRIVILEGE_CONSUMER_RETURN_CODE_SUCCESS;

    GList* privilege_name_list = NULL;
    GList* privilege_info_list = NULL;

    const char* locale = "xxx";

    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/not_exist_privilege_name");
    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/unknown_privilege");
    privilege_name_list = g_list_append(privilege_name_list, "xxxxxx");

    ret = privilege_info_get_privilege_info_list(locale, privilege_name_list, &privilege_info_list, &return_result);

    g_list_free(privilege_name_list);
    g_list_free_full(privilege_info_list, __free_privilege_info_list);

    assert_eq(ret, PRVINFO_ERROR_NONE);
    assert_eq(return_result, PRIVILEGE_CONSUMER_RETURN_CODE_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_privilege_info_get_privilege_info_list_n1
 * @since_tizen     5.5
 * @description     Gets privilege info list with null input parameter - privilege_name_list
 */
int utc_privilege_info_get_privilege_info_list_n1(void)
{
    int ret = PRVINFO_ERROR_NONE;
    privilege_consumer_return_code_e return_result = PRIVILEGE_CONSUMER_RETURN_CODE_SUCCESS;

    GList* privilege_name_list = NULL;
    GList* privilege_info_list = NULL;

    const char* locale = "ko_KR.UTF8";

    ret = privilege_info_get_privilege_info_list(locale, privilege_name_list, &privilege_info_list, &return_result);

    g_list_free(privilege_name_list);
    g_list_free_full(privilege_info_list, __free_privilege_info_list);

    assert_eq(ret, PRVINFO_ERROR_INVALID_PARAMETER);
    assert_eq(return_result, PRIVILEGE_CONSUMER_RETURN_CODE_SUCCESS);

    return 0;
}

/**
 * @testcase        utc_privilege_info_free_privilege_info_list_p1
 * @since_tizen     5.5
 * @description     Free privilege info list after getting it by using privilege_info_get_privilege_info_list()
 */

int utc_privilege_info_free_privilege_info_list_p1(void)
{
    int ret = PRVINFO_ERROR_NONE;
    privilege_consumer_return_code_e return_result = PRIVILEGE_CONSUMER_RETURN_CODE_SUCCESS;

    GList* privilege_name_list = NULL;
    GList* privilege_info_list = NULL;

    const char* locale = "ko_KR.UTF8";

    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/internet");
    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/call");
    privilege_name_list = g_list_append(privilege_name_list, "http://tizen.org/privilege/mediastorage");

    ret = privilege_info_get_privilege_info_list(locale, privilege_name_list, &privilege_info_list, &return_result);

    g_list_free(privilege_name_list);

    ret = privilege_info_free_privilege_info_list(privilege_info_list);

    assert_eq(ret, PRVINFO_ERROR_NONE);

    return 0;
}

/**
 * @testcase        utc_privilege_info_free_privilege_info_list_n1
 * @since_tizen     5.5
 * @description     Free privilege info list with null input parameter
 */

int utc_privilege_info_free_privilege_info_list_n1(void)
{
    int ret = PRVINFO_ERROR_NONE;

    ret = privilege_info_free_privilege_info_list(NULL);

    assert_eq(ret, PRVINFO_ERROR_INVALID_PARAMETER);

    return 0;
}

