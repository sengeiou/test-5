/**
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
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

#include <media/mv_barcode.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"

#include <system_info.h>
#include <json-glib/json-glib.h>

#define DICT_KEY_SIZE 255
#define DICT_STR_VALUE_SIZE 1024
#define DICT_ARRAY_STR_SIZE 3

static bool isVisionSupported = false;
static int gStartupError;

static const char *eng_conf_path = "/usr/share/capi-media-vision/media-vision-config.json";
static const char *eng_conf_json_attr_section_name = "attributes";

struct attr_dbl_entry
{
    char key[DICT_KEY_SIZE];
    double value;
};

struct attr_int_entry
{
    char key[DICT_KEY_SIZE];
    int value;
};

struct attr_bool_entry
{
    char key[DICT_KEY_SIZE];
    bool value;
};

struct attr_str_entry
{
    char key[DICT_KEY_SIZE];
    char value[DICT_STR_VALUE_SIZE];
};

struct attr_array_str_entry
{
    char key[DICT_KEY_SIZE];
    char value[DICT_ARRAY_STR_SIZE][DICT_STR_VALUE_SIZE];
    int str_n;
};

static mv_engine_config_h engine_config = NULL;
static bool _is_broken_config = false;

static struct attr_dbl_entry  *dict_dbl  = NULL;
static int dict_dbl_n = 0;
static struct attr_int_entry  *dict_int  = NULL;
static int dict_int_n = 0;
static struct attr_bool_entry *dict_bool = NULL;
static int dict_bool_n = 0;
static struct attr_str_entry  *dict_str  = NULL;
static int dict_str_n = 0;
static struct attr_array_str_entry *dict_array_str = NULL;
static int dict_array_n = 0;

bool _parse_attr_dictionaries(const char *conf_file)
{
    JsonParser *parser;
    GError *error = NULL;

    parser = json_parser_new();
    json_parser_load_from_file(parser, conf_file, &error);
    if (error)
    {
        g_print("Unable to parse file '%s': %s\n", conf_file, error->message);
        g_error_free(error);
        g_object_unref(parser);
        return false;
    }

    JsonNode *root = json_parser_get_root(parser);
    if (JSON_NODE_OBJECT != json_node_get_node_type(root))
    {
        printf("Can't parse tests configuration file. Incorrect json markup.\n");
        g_object_unref(parser);
        return false;
    }

    JsonObject *jobj = json_node_get_object(root);

    if (!json_object_has_member(jobj, eng_conf_json_attr_section_name))
    {
        printf("Can't parse tests configuration file. "
               "No '%s' section.\n", eng_conf_json_attr_section_name);
        g_object_unref(parser);
        return false;
    }

    JsonNode *attr_node =
                  json_object_get_member(jobj, eng_conf_json_attr_section_name);

    if (JSON_NODE_ARRAY != json_node_get_node_type(attr_node))
    {
        printf("Can't parse tests configuration file. "
               "'%s' section isn't array.\n", eng_conf_json_attr_section_name);
        g_object_unref(parser);
        return false;
    }

    JsonArray *attr_array = json_node_get_array(attr_node);

    const guint attr_num = json_array_get_length(attr_array);

    guint attr_ind = 0;
    for (; attr_ind < attr_num; ++attr_ind)
    {
        JsonNode *attr_node = json_array_get_element(attr_array, attr_ind);

        if (JSON_NODE_OBJECT != json_node_get_node_type(attr_node))
        {
            printf("Attribute %u wasn't parsed from json file.", attr_ind);
            continue;
        }

        JsonObject *attr_obj = json_node_get_object(attr_node);

        if (!json_object_has_member(attr_obj, "name") ||
            !json_object_has_member(attr_obj, "type") ||
            !json_object_has_member(attr_obj, "value"))
        {
            printf("Attribute %u wasn't parsed from json file.", attr_ind);
            continue;
        }

        const char *str_name =
                       (char*)json_object_get_string_member(attr_obj, "name");
        assert_geq(DICT_KEY_SIZE, strlen(str_name));
        const char *str_type =
                       (char*)json_object_get_string_member(attr_obj, "type");

        if (0 == strcmp("double", str_type))
        {
            dict_dbl = (struct attr_dbl_entry*)realloc(dict_dbl, ++dict_dbl_n * sizeof(struct attr_dbl_entry));
            snprintf(dict_dbl[dict_dbl_n-1].key, DICT_KEY_SIZE, "%s", str_name);
            dict_dbl[dict_dbl_n-1].value =
                    (double)json_object_get_double_member(attr_obj, "value");
        }
        else if (0 == strcmp("integer", str_type))
        {
            dict_int = (struct attr_int_entry*)realloc(dict_int, ++dict_int_n * sizeof(struct attr_int_entry));
            snprintf(dict_int[dict_int_n-1].key, DICT_KEY_SIZE, "%s", str_name);
            dict_int[dict_int_n-1].value =
                    (int)json_object_get_int_member(attr_obj, "value");
        }
        else if (0 == strcmp("boolean", str_type))
        {
            dict_bool = (struct attr_bool_entry*)realloc(dict_bool, ++dict_bool_n * sizeof(struct attr_bool_entry));
            snprintf(dict_bool[dict_bool_n-1].key, DICT_KEY_SIZE, "%s", str_name);
            dict_bool[dict_bool_n-1].value =
                    (bool)json_object_get_boolean_member(attr_obj, "value");
        }
        else if (0 == strcmp("string", str_type))
        {
            dict_str = (struct attr_str_entry*)realloc(dict_str, ++dict_str_n * sizeof(struct attr_str_entry));
            snprintf(dict_str[dict_str_n-1].key, DICT_KEY_SIZE, "%s", str_name);
            const char *str_value = (const char*)json_object_get_string_member(attr_obj, "value");
            assert_geq(DICT_STR_VALUE_SIZE, strlen(str_value));
            snprintf(dict_str[dict_str_n-1].value, DICT_STR_VALUE_SIZE, "%s", str_value);
        } else if (0 == strcmp("array", str_type)){
            const char *subTypeStr = (char*)json_object_get_string_member(attr_obj, "subtype");
            if (0 == strcmp("string", subTypeStr)) {
                dict_array_str = (struct attr_array_str_entry*)realloc(dict_array_str, ++dict_array_n * sizeof(struct attr_array_str_entry));
                snprintf(dict_array_str[dict_array_n-1].key, DICT_KEY_SIZE, "%s", str_name);

                JsonArray *attr_array = json_object_get_array_member(attr_obj, "value");
                dict_array_str[dict_array_n-1].str_n = json_array_get_length(attr_array);
                assert_geq(DICT_ARRAY_STR_SIZE, dict_array_str[dict_array_n-1].str_n);

                for (unsigned int item = 0; item < dict_array_str[dict_array_n-1].str_n; ++item) {
                    snprintf(dict_array_str[dict_array_n-1].value[item], DICT_STR_VALUE_SIZE, "%s", json_array_get_string_element(attr_array, item));
                }
            }
        }
        else
        {
            printf("Attribute %s wasn't parsed from json file. Type isn't supported.", str_name);
            continue;
        }
    }

    g_object_unref(parser);

    return true;
}

bool _is_supported_dbl_attr(const char *key, double *value)
{
    int ind = 0;
    for(; ind < dict_dbl_n; ++ind)
    {
        if (0 == strcmp(dict_dbl[ind].key, key))
        {
            if (value != NULL)
            {
                *value = dict_dbl[ind].value;
            }
            return true;
        }
    }

    return false;
}

bool _is_supported_int_attr(const char *key, int *value)
{
    int ind = 0;
    for(; ind < dict_int_n; ++ind)
    {
        if (0 == strcmp(dict_int[ind].key, key))
        {
            if (value != NULL)
            {
                *value = dict_int[ind].value;
            }
            return true;
        }
    }

    return false;
}

bool _is_supported_bool_attr(const char *key, bool *value)
{
    int ind = 0;
    for(; ind < dict_bool_n; ++ind)
    {
        if (0 == strcmp(dict_bool[ind].key, key))
        {
            if (value != NULL)
            {
                *value = dict_bool[ind].value;
            }
            return true;
        }
    }

    return false;
}

bool _is_supported_str_attr(const char *key, char *value)
{
    int ind = 0;
    for(; ind < dict_str_n; ++ind)
    {
        if (0 == strcmp(dict_str[ind].key, key))
        {
            if (value != NULL)
            {
                snprintf(value, 1024, "%s", dict_str[ind].value);
            }
            return true;
        }
    }

    return false;
}

bool _is_supported_array_str_attr(const char *key, char (*value)[DICT_ARRAY_STR_SIZE][DICT_STR_VALUE_SIZE], int *size)
{
    int ind = 0;
    for(; ind < dict_array_n; ++ind)
    {
        if (0 == strcmp(dict_array_str[ind].key, key))
        {
            if (value != NULL && size != NULL)
            {
                *size = dict_array_str[ind].str_n;
                for (int item = 0; item < (*size); ++item) {
                    snprintf((*value)[item], 1024, "%s", dict_array_str[ind].value[item]);
                }
            }
            return true;
        }
    }

    return false;
}

/**
 * @function		utc_capi_media_vision_common_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_media_vision_common_startup(void)
{
    printf("capi-media-vision tests STARTUP is launched\n");

    bool isFaceRecognitionSupported = false;
    bool isImageRecognitionSupported = false;
    bool isBarcodeDetectionSupported = false;
    bool isBarcodeGenerationSupported = false;
    bool isVisionInferenceImageSupported = false;
    bool isVisionInferenceFaceSupported = false;

    system_info_get_platform_bool("http://tizen.org/feature/vision.face_recognition", &isFaceRecognitionSupported);
    system_info_get_platform_bool("http://tizen.org/feature/vision.image_recognition", &isImageRecognitionSupported);
    system_info_get_platform_bool("http://tizen.org/feature/vision.barcode_detection", &isBarcodeDetectionSupported);
    system_info_get_platform_bool("http://tizen.org/feature/vision.barcode_generation", &isBarcodeGenerationSupported);
    system_info_get_platform_bool("http://tizen.org/feature/vision.inference.image", &isVisionInferenceImageSupported);
    system_info_get_platform_bool("http://tizen.org/feature/vision.inference.face", &isVisionInferenceFaceSupported);

    if (isFaceRecognitionSupported || isImageRecognitionSupported ||
        isBarcodeDetectionSupported || isBarcodeGenerationSupported ||
        isVisionInferenceImageSupported || isVisionInferenceFaceSupported)
        isVisionSupported = true;
    else
        isVisionSupported = false;

    gStartupError = MEDIA_VISION_ERROR_NONE;

    if (!engine_config)
    {
        gStartupError = mv_create_engine_config(&engine_config);

        if (MEDIA_VISION_ERROR_NONE != gStartupError)
        {
            _is_broken_config = true;
            engine_config = NULL;

            printf("mv_engine_config_h create is failed\n");
        }

        if (!_parse_attr_dictionaries(eng_conf_path))
        {
            printf("Loading of attributes supported by engine "
                   "configuration is failed\n");
        }
    }

    printf("capi-media-vision tests STARTUP is completed\n");
}

/**
 * @function		utc_capi_media_vision_common_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_media_vision_common_cleanup(void)
{
    printf("capi-media-vision tests CLEANUP is launched\n");

    if (engine_config)
    {
        mv_destroy_engine_config(engine_config);
        engine_config = NULL;
    }

    if (NULL != dict_dbl)
    {
        free(dict_dbl);
        dict_dbl = NULL;
        dict_dbl_n = 0;
    }

    if (NULL != dict_int)
    {
        free(dict_int);
        dict_int = NULL;
        dict_int_n = 0;
    }

    if (NULL != dict_bool)
    {
        free(dict_bool);
        dict_bool = NULL;
        dict_bool_n = 0;
    }
    if (NULL != dict_str)
    {
        free(dict_str);
        dict_str = NULL;
        dict_str_n = 0;
    }

    if (NULL != dict_array_str)
    {
        free(dict_array_str);
        dict_array_str = NULL;
        dict_array_n = 0;
    }

    printf("capi-media-vision tests CLEANUP is completed\n");
}

void prepareTestBuffer(unsigned char **buffer)
{
    const size_t dataSize = 800 * 600 * 4; // Width * Height * Channels
    *buffer = (unsigned char *) malloc(dataSize * sizeof(unsigned char));
    if (*buffer == NULL)
    {
        return;
    }

    int i;
    for (i = 0; i < dataSize; ++i)
    {
        (*buffer)[i] = 255; // Black image
    }
}

int _finalize_callback(media_packet_h packet, int err, void *userdata)
{
    return MEDIA_PACKET_FINALIZE;
}

bool _attribute_supported_callback(
        mv_config_attribute_type_e attribute_type,
        const char *attribute_name, void *user_data)
{
    printf("\nCallback call for attribute [%s]\n", attribute_name);

    bool *isCorrect = false;
    if (user_data != NULL)
    {
        isCorrect = (bool*)user_data;
    }
    else
    {
        printf("user_data wasn't passed to the callback. Failed\n");
        return false;
    }

    double dbl_value = 0.0;
    double real_dbl_value = -1.0;
    int int_value = 0;
    int real_int_value = -1;
    bool bool_value = false;
    bool real_bool_value = true;
    char str_value[DICT_STR_VALUE_SIZE] = "a";
    char *real_str_value;
    char array_str_value[DICT_ARRAY_STR_SIZE][DICT_STR_VALUE_SIZE] = {"a",};
    int array_str_size = 0;
    char **real_array_str_value = NULL;
    int real_array_str_size = -1;
    bool is_supported = false;
    bool are_exp_act_equal = false;
    int item;

    switch (attribute_type)
    {
        case MV_ENGINE_CONFIG_ATTR_TYPE_DOUBLE:
            is_supported = _is_supported_dbl_attr(attribute_name, &dbl_value);
            if (MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE ==
                    mv_engine_config_get_double_attribute(
                            engine_config, attribute_name, &real_dbl_value))
            {
                printf("Default double attribute %s wasn't set in engine "
                        "configuration by default. Failed\n", attribute_name);
                *isCorrect = false;
                printf("FAILED\n");
                return true;
            }
            printf("Expected value: [%f] | Real value: [%f]\n", dbl_value, real_dbl_value);
            are_exp_act_equal = dbl_value == real_dbl_value;
            break;
        case MV_ENGINE_CONFIG_ATTR_TYPE_INTEGER:
            is_supported = _is_supported_int_attr(attribute_name, &int_value);
            if (MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE ==
                    mv_engine_config_get_int_attribute(
                            engine_config, attribute_name, &real_int_value))
            {
                printf("Default integer attribute %s wasn't set in engine "
                        "configuration by default. Failed\n", attribute_name);
                *isCorrect = false;
                printf("FAILED\n");
                return true;
            }
            printf("Expected value: [%i] | Real value: [%i]\n", int_value, real_int_value);
            are_exp_act_equal = int_value == real_int_value;
            break;
        case MV_ENGINE_CONFIG_ATTR_TYPE_BOOLEAN:
            is_supported = _is_supported_bool_attr(attribute_name, &bool_value);
            if (MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE ==
                    mv_engine_config_get_bool_attribute(
                            engine_config, attribute_name, &real_bool_value))
            {
                printf("Default bool attribute %s wasn't set in engine "
                        "configuration by default. Failed\n", attribute_name);
                *isCorrect = false;
                printf("FAILED\n");
                return true;
            }
            printf("Expected value: [%s] | Real value: [%s]\n",
                    bool_value ?      "TRUE" : "FALSE",
                    real_bool_value ? "TRUE" : "FALSE");
            are_exp_act_equal = bool_value == real_bool_value;
            break;
        case MV_ENGINE_CONFIG_ATTR_TYPE_STRING:
            is_supported = _is_supported_str_attr(attribute_name, str_value);
            if (MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE ==
                    mv_engine_config_get_string_attribute(
                            engine_config, attribute_name, &real_str_value))
            {
                printf("Default string attribute %s wasn't set in engine "
                        "configuration by default. Failed\n", attribute_name);
                *isCorrect = false;
                free(real_str_value);
                printf("FAILED\n");
                return true;
            }
            printf("Expected value: [%s] | Real value: [%s]\n", str_value, real_str_value);
            are_exp_act_equal = 0 == strcmp(str_value, real_str_value);
            free(real_str_value);
            break;
        case MV_ENGINE_CONFIG_ATTR_TYPE_ARRAY_STRING:
            is_supported = _is_supported_array_str_attr(attribute_name, &array_str_value, &array_str_size);
            if (MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE ==
                    mv_engine_config_get_array_string_attribute(
                            engine_config, attribute_name, &real_array_str_value, &real_array_str_size))
            {
                printf("Default string attribute %s wasn't set n engine "
                        "configuration by default. Failed\n", attribute_name);
                *isCorrect = false;
                for(item = 0; item < real_array_str_size; ++item) {
                    free(real_array_str_value[item]);
                }
                free(real_array_str_value);
                printf("FAILED\n");
                return true;
            }

            if (array_str_size != real_array_str_size)
                are_exp_act_equal = 1;
            else {
                for(item = 0; item < real_array_str_size; ++item) {
                    printf("Expected value: [%s] | Real value: [%s]\n",
                        array_str_value[item], real_array_str_value[item]);
                    are_exp_act_equal = 0 == strcmp(array_str_value[item], real_array_str_value[item]);
                    if (are_exp_act_equal != 0) {
                        break;
                    }
                }
            }

            for(item = 0; item < real_array_str_size; ++item) {
                free(real_array_str_value[item]);
            }
            free(real_array_str_value);

            break;
        default:
            printf("Attribute type received in mv_supported_attribute_cb "
                    "is not supported. Failed");
            *isCorrect = false;
            printf("FAILED\n");
            return true;
    }

    // Attribute has to be supported and has correct default value:
    if (is_supported && are_exp_act_equal)
    {
        printf("PASSED\n");
    }
    else
    {
        *isCorrect = false;
        printf("FAILED\n");
    }

    return true;
}

/**
 * @brief Positive test case of mv_create_source()
 * @testcase		utc_mediavision_mv_create_source_p
 * @since_tizen		2.4
 * @description		Create media source handle
 */
int utc_mediavision_mv_create_source_p(void)
{
    printf("Inside mv_create_source_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;

    int ret = mv_create_source(&source);
    assert_eq(ret, MEDIA_VISION_ERROR_NONE);
    assert_neq(source, (void*) NULL);

    ret = mv_destroy_source(source);
    assert_eq(ret, MEDIA_VISION_ERROR_NONE);

    printf("Before return mv_create_source_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_create_source()
 * @testcase		utc_mediavision_mv_create_source_n
 * @since_tizen		2.4
 * @description		Create media source handle,
 * 								but fail because input handle is null
 */
int utc_mediavision_mv_create_source_n(void)
{
    printf("Inside mv_create_source_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_create_source(NULL);
    assert_eq(ret, MEDIA_VISION_ERROR_INVALID_PARAMETER);

    printf("Before return mv_create_source_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_destroy_source()
 * @testcase		utc_mediavision_mv_destroy_source_p
 * @since_tizen		2.4
 * @description		Destroy media source handle
 */
int utc_mediavision_mv_destroy_source_p(void)
{
    printf("Inside mv_destroy_source_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;

    int ret = mv_create_source(&source);
    assert_eq(ret, MEDIA_VISION_ERROR_NONE);

    ret = mv_destroy_source(source);
    assert_eq(ret, MEDIA_VISION_ERROR_NONE);

    printf("Before return mv_destroy_source_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_destroy_source()
 * @testcase		utc_mediavision_mv_destroy_source_n
 * @since_tizen		2.4
 * @description		Destroy media source handle
 * 								but fail because input handle is null
 */
int utc_mediavision_mv_destroy_source_n(void)
{
    printf("Inside mv_destroy_source_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;

    const int ret = mv_destroy_source(source);
    assert_eq(ret, MEDIA_VISION_ERROR_INVALID_PARAMETER);

    printf("Before return mv_destroy_source_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_source_fill_by_media_packet()
 * @testcase		utc_mediavision_mv_source_fill_by_media_packet_p
 * @since_tizen		2.4
 * @description		Fill data of media source handle from media packet
 */
int utc_mediavision_mv_source_fill_by_media_packet_p(void)
{
    printf("Inside mv_source_fill_by_media_packet_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    tbm_format *tbm_formats = NULL;
    uint32_t format_num = 0;

    int ret = tbm_surface_query_formats(&tbm_formats, &format_num);
    if (TBM_SURFACE_ERROR_NONE != ret)
    {
        printf("Failed to get formats supported by the system. "
                "Impossible to create media packet.\n"
                "SKIPPED\n");
        printf("Before return mv_source_fill_by_media_packet_p\n");
    }

    assert_eq(TBM_SURFACE_ERROR_NONE, ret);

    const unsigned int width = 800;
    const unsigned int height = 600;

    tbm_surface_h tbm_surface = NULL;
    int ind = 0;
    for (; ind < format_num; ++ind)
    {
        if (TBM_FORMAT_YUV420 == tbm_formats[ind])
        {
            tbm_surface = tbm_surface_create(width, height, TBM_FORMAT_YUV420);
            if (NULL == tbm_surface)
            {
                printf("Failed to create tbm_surface. "
                        "Impossible to create media packet.\n"
                        "SKIPPED\n");
            }
            break;
        }
    }

    assert_neq(NULL, tbm_surface);

    if (ind == format_num)
    {
        printf("Format YUV420 isn't supported. "
                "Impossible to create media packet.\n"
                "SKIPPED\n");
        if (TBM_SURFACE_ERROR_NONE != tbm_surface_destroy(tbm_surface))
        {
            printf("Failed to destroy TBM surface. Memory leaked.\n");
        }
    }

    assert_lt(ind, format_num);

    tbm_surface_info_s surface_info;
    ret = tbm_surface_map(tbm_surface,
            TBM_SURF_OPTION_READ|TBM_SURF_OPTION_WRITE, &surface_info);
    if (TBM_SURFACE_ERROR_NONE != ret)
    {
        printf("Fail to map tbm_surface. "
                "Impossible to create media packet.\n"
                "SKIPPED\n");
        if (TBM_SURFACE_ERROR_NONE != tbm_surface_destroy(tbm_surface))
        {
            printf("Failed to destroy TBM surface. Memory leaked.\n");
        }
    }

    assert_eq(TBM_SURFACE_ERROR_NONE, ret);

    for (ind = 0; ind < surface_info.num_planes; ++ind)
    {
        memset(surface_info.planes[ind].ptr, 0xFF, surface_info.planes[ind].size);
    }

    media_format_h format = NULL;
    if (MEDIA_FORMAT_ERROR_NONE !=
            (ret = media_format_create(&format)) ||
        MEDIA_FORMAT_ERROR_NONE !=
            (ret = media_format_set_video_mime(format, MEDIA_FORMAT_RGB888)) ||
        MEDIA_FORMAT_ERROR_NONE !=
            (ret = media_format_set_video_width(format, width)) ||
        MEDIA_FORMAT_ERROR_NONE !=
            (ret = media_format_set_video_height(format, height)))
    {
        printf("Fail to create media_format_h handle. "
               "Impossible to create media packet.\n"
               "SKIPPED\n");
        if (format)
        {
            media_format_unref(format);
        }
        if (TBM_SURFACE_ERROR_NONE != tbm_surface_destroy(tbm_surface))
        {
            printf("Failed to destroy TBM surface. Memory leaked.\n");
        }
    }

    assert_eq(MEDIA_FORMAT_ERROR_NONE, ret);

    media_packet_h packet = NULL;
    ret = media_packet_create_from_tbm_surface(
            format, tbm_surface, _finalize_callback, NULL, &packet);
    if (MEDIA_PACKET_ERROR_NONE != ret)
    {
        printf("Impossible to create media packet.\n"
               "SKIPPED\n");

        if (packet && MEDIA_PACKET_ERROR_NONE != media_packet_destroy(packet))
        {
            printf("Failed to destroy media packet. Memory leaked.\n");
        }

        media_format_unref(format);
    }

    assert_eq(MEDIA_PACKET_ERROR_NONE, ret);

    mv_source_h source = NULL;
    assert_eq(MEDIA_VISION_ERROR_NONE, mv_create_source(&source));
    assert_eq(MEDIA_VISION_ERROR_NONE,
            mv_source_fill_by_media_packet(source, packet));

    assert_eq(MEDIA_VISION_ERROR_NONE, mv_destroy_source(source));
    assert_eq(MEDIA_PACKET_ERROR_NONE, media_packet_destroy(packet));
    assert_eq(MEDIA_FORMAT_ERROR_NONE, media_format_unref(format));
    assert_eq(TBM_SURFACE_ERROR_NONE, tbm_surface_destroy(tbm_surface));

    printf("PASSED\n");

    printf("Before return mv_source_fill_by_media_packet_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_source_fill_by_media_packet()
 * @testcase		utc_mediavision_mv_source_fill_by_media_packet_n
 * @since_tizen		2.4
 * @description		Fill data of media source handle
 * 								but fail because media packet is null
 */
int utc_mediavision_mv_source_fill_by_media_packet_n(void)
{
    printf("Inside mv_source_fill_by_media_packet_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;

    int ret = mv_create_source(&source);
    assert_eq(ret, MEDIA_VISION_ERROR_NONE);

    media_packet_h packet = NULL;

    ret = mv_source_fill_by_media_packet(source, packet);
    assert_eq(ret, MEDIA_VISION_ERROR_INVALID_PARAMETER);

    ret = mv_destroy_source(source);
    assert_eq(ret, MEDIA_VISION_ERROR_NONE);

    printf("Before return mv_source_fill_by_media_packet_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_source_fill_by_buffer()
 * @testcase		utc_mediavision_mv_source_fill_by_buffer_p
 * @since_tizen		2.4
 * @description		Fill data of media source handle from buffer
 */
int utc_mediavision_mv_source_fill_by_buffer_p(void)
{
    printf("Inside mv_source_fill_by_buffer_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;
    mv_create_source(&source);
    const size_t dataSize = 800 * 600 * 4;
    unsigned char *data = NULL;
    prepareTestBuffer(&data);

    const int ret = mv_source_fill_by_buffer(source, data, dataSize, 800, 600, 4);

    free(data);

    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_neq((void*)NULL, source);

    mv_destroy_source(source);

    printf("Before return mv_source_fill_by_buffer_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_source_fill_by_buffer()
 * @testcase		utc_mediavision_mv_source_fill_by_buffer_n
 * @since_tizen		2.4
 * @description		Fill data of media source handle
 * 								but fail because handle is null
 */
int utc_mediavision_mv_source_fill_by_buffer_n(void)
{
    printf("Inside mv_source_fill_by_buffer_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h fakeSource = NULL;
    unsigned char *data = NULL;
    const size_t dataSize = 800 * 600 * 4;
    prepareTestBuffer(&data);

    const int ret = mv_source_fill_by_buffer(fakeSource, data, dataSize, 800, 400, 4);

    free(data);

    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_source_fill_by_buffer_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_source_clear()
 * @testcase		utc_mediavision_mv_source_clear_p
 * @since_tizen		2.4
 * @description		Clear the data of media source handle
 */
int utc_mediavision_mv_source_clear_p(void)
{
    printf("Inside mv_source_clear_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;
    mv_create_source(&source);
    unsigned char *data = NULL;
    prepareTestBuffer(&data);

    int ret = mv_source_fill_by_buffer(source, data, 800 * 600 * 4, 800, 600, 4);

    free(data);

    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_source_clear(source);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    mv_destroy_source(source);

    printf("Before return mv_source_clear_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_source_clear()
 * @testcase		utc_mediavision_mv_source_clear_n
 * @since_tizen		2.4
 * @description		Clear the data of media source handle
 * 								but fail becaus handle is null
 */
int utc_mediavision_mv_source_clear_n(void)
{
    printf("Inside mv_source_clear_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;

    const int ret = mv_source_clear(source);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_source_clear_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_source_get_buffer()
 * @testcase		utc_mediavision_mv_source_get_buffer_p
 * @since_tizen		2.4
 * @description		Get the data pointer from media source handle
 */
int utc_mediavision_mv_source_get_buffer_p(void)
{
    printf("Inside mv_source_get_buffer_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;
    mv_create_source(&source);
    unsigned char *expectedData = NULL;
    size_t dataSize = 0;

    int ret = mv_source_get_buffer(source, &expectedData, &dataSize);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    prepareTestBuffer(&expectedData);

    ret = mv_source_fill_by_buffer(source, expectedData, 800 * 600 * 4, 800, 600, 4);
    if (ret != MEDIA_VISION_ERROR_NONE)
        goto _ERR;


    unsigned char *actualData = NULL;
    size_t actualDataSize = 0;

    ret = mv_source_get_buffer(source, &actualData, &actualDataSize);
    if (ret != MEDIA_VISION_ERROR_NONE || actualDataSize != (800 * 600 * 4))
        goto _ERR;

    int i;
    bool isEqual = true;
    for (i = 0; i < actualDataSize; ++i)
    {
        isEqual = (expectedData[i] == actualData[i]);
        if (isEqual == false)
           break;
    }

_ERR:
    free(expectedData);
    mv_destroy_source(source);

    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(actualDataSize, 800 * 600 * 4);
    assert_eq(true, isEqual);

    printf("Before return mv_source_get_buffer_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_source_get_buffer()
 * @testcase		utc_mediavision_mv_source_get_buffer_n
 * @since_tizen		2.4
 * @description		Get the data pointer from media source handle but fail
 * 								because handle is null
 */
int utc_mediavision_mv_source_get_buffer_n(void)
{
    printf("Inside mv_source_get_buffer_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h fakeSource = NULL;
    unsigned char *data = NULL;
    size_t dataSize = 0;

    const int ret = mv_source_get_buffer(fakeSource, &data, &dataSize);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_source_get_buffer_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_source_get_height()
 * @testcase		utc_mediavision_mv_source_get_height_p
 * @since_tizen		2.4
 * @description		Get the height from media source handle
 */
int utc_mediavision_mv_source_get_height_p(void)
{
    printf("Inside mv_source_get_height_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;
    mv_create_source(&source);
    size_t height = 0;
    unsigned char *data = NULL;
    prepareTestBuffer(&data);

    int ret = mv_source_fill_by_buffer(source, data, 800 * 600 * 4, 800, 600, 4);
    if (ret == MEDIA_VISION_ERROR_NONE)
	ret = mv_source_get_height(source, &height);

    free(data);
    mv_destroy_source(source);

    assert_eq(MEDIA_VISION_ERROR_NONE,ret);
    assert_eq(600, height);

    printf("Before return mv_source_get_height_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_source_get_height()
 * @testcase		utc_mediavision_mv_source_get_height_n
 * @since_tizen		2.4
 * @description		Get the height from media source handle but fail
 * 								because handle is null
 */
int utc_mediavision_mv_source_get_height_n(void)
{
    printf("Inside mv_source_get_height_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h fakeSource = NULL;
    size_t height = 0;

    const int ret = mv_source_get_height(fakeSource, &height);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_source_get_height_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_source_get_width()
 * @testcase		utc_mediavision_mv_source_get_width_p
 * @since_tizen		2.4
 * @description		Get the width from media source handle
 */
int utc_mediavision_mv_source_get_width_p(void)
{
    printf("Inside mv_source_get_width_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;
    mv_create_source(&source);
    size_t width = 0;
    unsigned char *data = NULL;
    prepareTestBuffer(&data);

    int ret = mv_source_fill_by_buffer(source, data, 800 * 600 * 4, 800, 600, 4);
    if (ret == MEDIA_VISION_ERROR_NONE)
        ret = mv_source_get_width(source, &width);

    free(data);
    mv_destroy_source(source);

    assert_eq(MEDIA_VISION_ERROR_NONE,ret);
    assert_eq(800, width);

    printf("Before return mv_source_get_width_p\n");
    return 0;
}

/**
 * @brief Negative test case of mv_source_get_width()
 * @testcase		utc_mediavision_mv_source_get_width_n
 * @since_tizen		2.4
 * @description		Get the width of media source handle but fail
 * 								because handle is null
 */
int utc_mediavision_mv_source_get_width_n(void)
{
    printf("Inside mv_source_get_width_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h fakeSource = NULL;
    size_t width = 0;

    const int ret = mv_source_get_width(fakeSource, &width);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_source_get_width_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_source_get_colorspace()
 * @testcase		utc_mediavision_mv_source_get_colorspace_p
 * @since_tizen		2.4
 * @description		Get the colorspace from media source handle
 */
int utc_mediavision_mv_source_get_colorspace_p(void)
{
    printf("Inside mv_source_get_colorspace_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h source = NULL;
    mv_create_source(&source);
    mv_colorspace_e colorspace = MEDIA_VISION_COLORSPACE_INVALID;
    unsigned char *data = NULL;
    prepareTestBuffer(&data);

    int ret = mv_source_fill_by_buffer(source, data, 800 * 600 * 4, 800, 600, MEDIA_VISION_COLORSPACE_RGBA);
    if (ret == MEDIA_VISION_ERROR_NONE)
        ret = mv_source_get_colorspace(source, &colorspace);

    free(data);
    mv_destroy_source(source);

    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(MEDIA_VISION_COLORSPACE_RGBA, colorspace);

    printf("Before return mv_source_get_colorspace_p\n");
    return 0;
}

/**
 * @brief Negative test case of mv_source_get_colorspace()
 * @testcase		utc_mediavision_mv_source_get_colorspace_n
 * @since_tizen		2.4
 * @description		Get the colorspace from media source handle but fail
 * 								because handle is null
 */
int utc_mediavision_mv_source_get_colorspace_n(void)
{
    printf("Inside mv_source_get_colorspace_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_source_h fakeSource = NULL;
    mv_colorspace_e colorspace = MEDIA_VISION_COLORSPACE_INVALID;

    const int ret = mv_source_get_colorspace(fakeSource, &colorspace);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_source_get_colorspace_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_create_engine_config()
 * @testcase		utc_mediavision_mv_create_engine_config_p
 * @since_tizen		2.4
 * @description		Create engine configuration handle
 */
int utc_mediavision_mv_create_engine_config_p(void)
{
    printf("Inside mv_create_engine_config_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_neq((void*)NULL, engHandler);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_create_engine_config_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_create_engine_config()
 * @testcase		utc_mediavision_mv_create_engine_config_n
 * @since_tizen		2.4
 * @description		Create engine configuration handle but fail
 * 								because input handle is null
 */
int utc_mediavision_mv_create_engine_config_n(void)
{
    printf("Inside mv_create_engine_config_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_create_engine_config((void*)NULL);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_create_engine_config_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_destroy_engine_config()
 * @testcase		utc_mediavision_mv_destroy_engine_config_p
 * @since_tizen		2.4
 * @description		Destroy engine configuration handle
 */
int utc_mediavision_mv_destroy_engine_config_p(void)
{
    printf("Inside mv_destroy_engine_config_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_neq((void*)NULL, engHandler);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_destroy_engine_config_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_destroy_engine_config()
 * @testcase		utc_mediavision_mv_destroy_engine_config_n
 * @since_tizen		2.4
 * @description		Destroy engine configuration handle but fail
 * 								because handle is null
 */
int utc_mediavision_mv_destroy_engine_config_n(void)
{
    printf("Inside mv_destroy_engine_config_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h actualEngHandler = NULL;

    const int ret = mv_destroy_engine_config(actualEngHandler);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_destroy_engine_config_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_engine_config_set_double_attribute()
 * @testcase		utc_mediavision_mv_engine_config_set_double_attribute_p
 * @since_tizen		2.4
 * @description		Set double type attribute
 */
int utc_mediavision_mv_engine_config_set_double_attribute_p(void)
{
    printf("Inside mv_engine_config_set_double_attribute_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    const double attributeValue = 2.0;
    ret = mv_engine_config_set_double_attribute(engHandler, "MV_IMAGE_TRACKING_EXPECTED_OFFSET", attributeValue);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_engine_config_set_double_attribute_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_engine_config_set_double_attribute()
 * @testcase		utc_mediavision_mv_engine_config_set_double_attribute_n
 * @since_tizen		2.4
 * @description		Set double type attribute but fail
 * 								because engine configuration handle is null
 */
int utc_mediavision_mv_engine_config_set_double_attribute_n(void)
{
    printf("Inside mv_engine_config_set_double_attribute_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;
    const double attributeValue = 0.;

    const int ret = mv_engine_config_set_double_attribute(engHandler, "test", attributeValue);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_engine_config_set_double_attribute_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_engine_config_set_int_attribute()
 * @testcase		utc_mediavision_mv_engine_config_set_int_attribute_p
 * @since_tizen		2.4
 * @description		Set integer type attribute
 */
int utc_mediavision_mv_engine_config_set_int_attribute_p(void)
{
    printf("Inside mv_engine_config_set_int_attribute_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    const int attributeValue = 2;
    ret = mv_engine_config_set_int_attribute(engHandler, "MV_FACE_RECOGNITION_MODEL_TYPE", attributeValue);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_engine_config_set_int_attribute_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_engine_config_set_int_attribute()
 * @testcase		utc_mediavision_mv_engine_config_set_int_attribute_n
 * @since_tizen		2.4
 * @description		Set integer type attribute but fail
 * 								because engine configuration handle is null
 */
int utc_mediavision_mv_engine_config_set_int_attribute_n(void)
{
    printf("Inside mv_engine_config_set_int_attribute_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;
    const int attributeValue = 255;

    const int ret = mv_engine_config_set_int_attribute(engHandler, "test", attributeValue);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_engine_config_set_int_attribute_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_engine_config_set_bool_attribute()
 * @testcase		utc_mediavision_mv_engine_config_set_bool_attribute_p
 * @since_tizen		2.4
 * @description		Set bool type attrbute
 */
int utc_mediavision_mv_engine_config_set_bool_attribute_p(void)
{
    printf("Inside mv_engine_config_set_bool_attribute_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    const bool attributeValue = true;

    ret = mv_engine_config_set_bool_attribute(engHandler, "MV_IMAGE_TRACKING_USE_STABLIZATION", attributeValue);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_engine_config_set_bool_attribute_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_engine_config_set_bool_attribute()
 * @testcase		utc_mediavision_mv_engine_config_set_bool_attribute_n
 * @since_tizen		2.4
 * @description		Set bool type attribute but fail
 * 								because engine configuration handle is null
 */
int utc_mediavision_mv_engine_config_set_bool_attribute_n(void)
{
    printf("Inside mv_engine_config_set_bool_attribute_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;
    const bool attributeValue = true;

    const int ret = mv_engine_config_set_bool_attribute(engHandler, "test", attributeValue);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_engine_config_set_bool_attribute_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_engine_config_set_string_attribute()
 * @testcase		utc_mediavision_mv_engine_config_set_string_attribute_p
 * @since_tizen		2.4
 * @description		Set string type attribute
 */
int utc_mediavision_mv_engine_config_set_string_attribute_p(void)
{
    printf("Inside mv_engine_config_set_string_attribute_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    const char *attributeValue = "/usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";

    ret = mv_engine_config_set_string_attribute(engHandler, "MV_FACE_DETECTION_MODEL_FILE_PATH", attributeValue);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_engine_config_set_string_attribute_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_engine_config_set_string_attribute()
 * @testcase		utc_mediavision_mv_engine_config_set_string_attribute_n
 * @since_tizen		2.4
 * @description		Set string type attribute but fail
 * 								because engine configuration handle is null
 */
int utc_mediavision_mv_engine_config_set_string_attribute_n(void)
{
    printf("Inside mv_engine_config_set_string_attribute_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;
    const char attributeValue[12] = "test string";

    const int ret = mv_engine_config_set_string_attribute(engHandler, "test", attributeValue);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_engine_config_set_string_attribute_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_engine_config_set_array_string_attribute()
 * @testcase		utc_mediavision_mv_engine_config_set_array_string_attribute_p
 * @since_tizen		5.5
 * @description		Set array string type attribute
 */
int utc_mediavision_mv_engine_config_set_array_string_attribute_p(void)
{
    printf("Inside mv_engine_config_set_array_string_attribute_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    const char *attributeValue[2] = {"output/node1", "output/node2"};

    ret = mv_engine_config_set_array_string_attribute(engHandler, "MV_INFERENCE_OUTPUT_NODE_NAMES", attributeValue, 2);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_engine_config_set_array_string_attribute_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_engine_config_set_array_string_attribute()
 * @testcase		utc_mediavision_mv_engine_config_set_array_string_attribute_n
 * @since_tizen		5.5
 * @description		Set array string type attribute but fail
 * 								because engine configuration handle is null
 */
int utc_mediavision_mv_engine_config_set_array_string_attribute_n(void)
{
    printf("Inside mv_engine_config_set_array_string_attribute_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;
    const char *attributeValue[2] = {"output/node1", "output/node2"};

    const int ret = mv_engine_config_set_array_string_attribute(engHandler, "MV_INFERENCE_OUTPUT_NODE_NAMES", attributeValue, 2);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before return mv_engine_config_set_string_attribute_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_engine_config_get_double_attribute()
 * @testcase		utc_mediavision_mv_engine_config_get_double_attribute_p
 * @since_tizen		2.4
 * @description		Get double type attribute
 */
int utc_mediavision_mv_engine_config_get_double_attribute_p(void)
{
    printf("Inside mv_engine_config_get_double_attribute_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    const double expectedAttributeValue = 2.0;

    ret = mv_engine_config_set_double_attribute(engHandler, "MV_IMAGE_TRACKING_EXPECTED_OFFSET", expectedAttributeValue);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    double actualAttributeValue = 0.0;

    ret = mv_engine_config_get_double_attribute(engHandler, "MV_IMAGE_TRACKING_EXPECTED_OFFSET", &actualAttributeValue);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    assert_eq(expectedAttributeValue, actualAttributeValue);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_engine_config_get_double_attribute_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_engine_config_get_double_attribute()
 * @testcase		utc_mediavision_mv_engine_config_get_double_attribute_n
 * @since_tizen		2.4
 * @description		Get double type attribute but fail
 * 								because engine configuration handle is null
 */
int utc_mediavision_mv_engine_config_get_double_attribute_n(void)
{
    printf("Inside mv_engine_config_get_double_attribute_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    double attributeValue = 0.0;

    ret = mv_engine_config_get_double_attribute(engHandler, "test", &attributeValue);
    assert_eq(MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE, ret);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_engine_config_get_double_attribute_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_engine_config_get_int_attribute()
 * @testcase		utc_mediavision_mv_engine_config_get_int_attribute_p
 * @since_tizen		2.4
 * @description		Get integer type attribute
 */
int utc_mediavision_mv_engine_config_get_int_attribute_p(void)
{
    printf("Inside mv_engine_config_get_int_attribute_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    const int expectedParameterValue = 2;

    ret = mv_engine_config_set_int_attribute(engHandler, "MV_FACE_RECOGNITION_MODEL_TYPE", expectedParameterValue);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    int actualParameterValue = 0;

    ret = mv_engine_config_get_int_attribute(engHandler, "MV_FACE_RECOGNITION_MODEL_TYPE", &actualParameterValue);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    assert_eq(expectedParameterValue, actualParameterValue);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_engine_config_get_int_attribute_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_engine_config_get_int_attribute()
 * @testcase		utc_mediavision_mv_engine_config_get_int_attribute_n
 * @since_tizen		2.4
 * @description		Get integer type attribute but fail
 * 								because engine configuration handle is null
 */
int utc_mediavision_mv_engine_config_get_int_attribute_n(void)
{
    printf("Inside mv_engine_config_get_int_attribute_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    int attributeValue = 0;

    ret = mv_engine_config_get_int_attribute(engHandler, "test", &attributeValue);
    assert_eq(MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE, ret);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_engine_config_get_int_attribute_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_engine_config_get_bool_attribute()
 * @testcase		utc_mediavision_mv_engine_config_get_bool_attribute_p
 * @since_tizen		2.4
 * @description		Get bool type attribute
 */
int utc_mediavision_mv_engine_config_get_bool_attribute_p(void)
{
    printf("Inside mv_engine_config_get_bool_attribute_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    const bool expectedParameterValue = true;

    ret = mv_engine_config_set_bool_attribute(engHandler, "MV_IMAGE_TRACKING_USE_STABLIZATION", expectedParameterValue);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    bool actualParameterValue = false;

    ret = mv_engine_config_get_bool_attribute(engHandler, "MV_IMAGE_TRACKING_USE_STABLIZATION", &actualParameterValue);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    assert_eq(expectedParameterValue, actualParameterValue);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_engine_config_get_bool_attribute_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_engine_config_get_bool_attribute()
 * @testcase		utc_mediavision_mv_engine_config_get_bool_attribute_n
 * @since_tizen		2.4
 * @description		Get bool type attribute but fail
 * 								because engine configuration handle is null
 */
int utc_mediavision_mv_engine_config_get_bool_attribute_n(void)
{
    printf("Inside mv_engine_config_get_bool_attribute_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    bool attributeValue = false;

    ret = mv_engine_config_get_bool_attribute(engHandler, "test", &attributeValue);
    assert_eq(MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE, ret);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Before return mv_engine_config_get_bool_attribute_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_engine_config_get_string_attribute()
 * @testcase		utc_mediavision_mv_engine_config_get_string_attribute_p
 * @since_tizen		2.4
 * @description		Get string attribute
 */
int utc_mediavision_mv_engine_config_get_string_attribute_p(void)
{
    printf("Inside mv_engine_config_get_string_attribute_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    const char *expectedParameterValue = "/usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";

    ret = mv_engine_config_set_string_attribute(engHandler, "MV_FACE_DETECTION_MODEL_FILE_PATH", expectedParameterValue);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char *actualParameterValue = NULL;

    ret = mv_engine_config_get_string_attribute(engHandler, "MV_FACE_DETECTION_MODEL_FILE_PATH", &actualParameterValue);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    assert_eq(strcmp(expectedParameterValue, actualParameterValue), 0);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    free(actualParameterValue);

    printf("Before return mv_engine_config_get_string_attribute_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_engine_config_get_string_attribute()
 * @testcase		utc_mediavision_mv_engine_config_get_string_attribute_n
 * @since_tizen		2.4
 * @description		Get string attribute but fail
 * 								because engine configuration handle is null
 */
int utc_mediavision_mv_engine_config_get_string_attribute_n(void)
{
    printf("Inside mv_engine_config_get_string_attribute_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    char *attributeValue = NULL;

    ret = mv_engine_config_get_string_attribute(engHandler, "test", &attributeValue);
    assert_eq(MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE, ret);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    free(attributeValue);

    printf("Before return mv_engine_config_get_string_attribute_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_engine_config_get_array_string_attribute()
 * @testcase		utc_mediavision_mv_engine_config_get_array_string_attribute_p
 * @since_tizen		5.5
 * @description		Get array string attribute
 */
int utc_mediavision_mv_engine_config_get_array_string_attribute_p(void)
{
    printf("Inside mv_engine_config_get_array_string_attribute_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    const int expectedSize = 2;
    const char *expectedParameterValue[2] = {"output/node1", "output/node2"};

    ret = mv_engine_config_set_array_string_attribute(engHandler, "MV_INFERENCE_OUTPUT_NODE_NAMES", expectedParameterValue, 2);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    int actualSize = 0;
    char **actualParameterValue = NULL;

    ret = mv_engine_config_get_array_string_attribute(engHandler, "MV_INFERENCE_OUTPUT_NODE_NAMES", &actualParameterValue, &actualSize);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    assert_eq(expectedSize, actualSize);
    for (int i = 0; i < expectedSize; ++i) {
        assert_eq(strcmp(expectedParameterValue[i], actualParameterValue[i]), 0);
    }

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    for (int i = 0; i < actualSize; ++i) {
        free(actualParameterValue[i]);
    }
    free(actualParameterValue);

    printf("Before return mv_engine_config_get_string_attribute_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_engine_config_get_array_string_attribute()
 * @testcase		utc_mediavision_mv_engine_config_get_array_string_attribute_n
 * @since_tizen		5.5
 * @description		Get array string attribute but fail
 * 								because key is not available
 */
int utc_mediavision_mv_engine_config_get_array_string_attribute_n(void)
{
    printf("Inside mv_engine_config_get_array_string_attribute_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    mv_engine_config_h engHandler = NULL;

    int ret = mv_create_engine_config(&engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    int size = 0;
    char **attributeValue = NULL;

    ret = mv_engine_config_get_array_string_attribute(engHandler, "test", &attributeValue, &size);
    assert_eq(MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE, ret);

    ret = mv_destroy_engine_config(engHandler);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(0, size);
    assert_eq(NULL, attributeValue);

    printf("Before return mv_engine_config_get_array_string_attribute_n\n");

    return 0;
}

/**
 * @brief Positive test case of mv_engine_config_foreach_supported_attribute()
 * @testcase		utc_mediavision_mv_engine_config_foreach_supported_attribute_p
 * @since_tizen		2.4
 * @description		Check supported all attributes
 */
int utc_mediavision_mv_engine_config_foreach_supported_attribute_p(void)
{
    printf("Inside mv_engine_config_foreach_supported_attribute_p\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_config);

    bool isCorrect = true;

    const int ret = mv_engine_config_foreach_supported_attribute(
            _attribute_supported_callback, &isCorrect);

    assert_eq(MEDIA_VISION_ERROR_NONE, ret);
    assert_eq(true, isCorrect);

    printf("Before mv_engine_config_foreach_supported_attribute_p\n");

    return 0;
}

/**
 * @brief Negative test case of mv_engine_config_foreach_supported_attribute()
 * @testcase		utc_mediavision_mv_engine_config_foreach_supported_attribute_n
 * @since_tizen		2.4
 * @description		Check supported all attributes but fail
 * 								because callback is null
 */
int utc_mediavision_mv_engine_config_foreach_supported_attribute_n(void)
{
    printf("Inside mv_engine_config_foreach_supported_attribute_n\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    const int ret = mv_engine_config_foreach_supported_attribute(
            NULL, NULL);

    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER, ret);

    printf("Before mv_engine_config_foreach_supported_attribute_n\n");

    return 0;
}
