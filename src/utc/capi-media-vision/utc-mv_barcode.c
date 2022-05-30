//
// Copyright (c) 2015 Samsung Electronics Co., Ltd.
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
#include <mv_barcode.h>

#include <storage.h>

#include <stdio.h>
#include <string.h>

#include <system_info.h>
#include <image_util.h>
#include <json-glib/json-glib.h>
#include <storage.h>
#include "tct_common.h"

#define DESCRIPTION_FIELD_SIZE 1024
#define MESSAGE_FIELD_SIZE 7100
#define IMAGE_PATH_FIELD_SIZE 1024

#define API_NAMESPACE "[MediaVision]"

struct barcode_model
{
    char description[DESCRIPTION_FIELD_SIZE];
    char message[MESSAGE_FIELD_SIZE];
    char image_path[IMAGE_PATH_FIELD_SIZE];
    int width;
    int height;
    mv_barcode_type_e type;
    mv_barcode_qr_mode_e qr_enc_mode;
    mv_barcode_qr_ecc_e qr_ecc;
    int qr_version;
    mv_colorspace_e colorspace;
    mv_error_e expected_res;
};

static bool isVisionSupported = false;
static int gStartupError;

static mv_source_h media_source = NULL;
static mv_engine_config_h engine_config = NULL;

static bool _is_broken_source = false;
static bool _is_broken_config = false;

static const char *test_res_path = NULL;
static const char *test_data_path = NULL;
static const char *conf_file = "media-vision-barcodes.json";
static const char *json_gen_img_pos_section = "gen_positive";
static const char *json_gen_img_neg_section = "gen_img_negative";
static const char *json_gen_src_pos_section = "gen_positive";
static const char *json_gen_src_neg_section = "gen_src_negative";
static const char *json_det_pos_section1 = "det_positive1";
static const char *json_det_pos_section2 = "det_positive2";
static const char *json_det_cs_pos_section = "det_colorspace_positive";

static struct barcode_model *gen_img_models_p = NULL;
static int gen_img_p_n = 0;
static struct barcode_model *gen_img_models_n = NULL;
static int gen_img_n_n = 0;
static struct barcode_model *gen_src_models_p = NULL;
static int gen_src_p_n = 0;
static struct barcode_model *gen_src_models_n = NULL;
static int gen_src_n_n = 0;
static struct barcode_model *det_models_p1 = NULL;
static int det_p1_n = 0;
static struct barcode_model *det_models_p2 = NULL;
static int det_p2_n = 0;
static struct barcode_model *det_cs_models_p = NULL;
static int det_cs_p_n = 0;

// Helpers:

static mv_barcode_type_e convert_str_type(const char *str_type)
{
    if (0 == strcmp("MV_BARCODE_QR", str_type))
    {
        return MV_BARCODE_QR;
    }
    else if (0 == strcmp("MV_BARCODE_UPC_A", str_type))
    {
        return MV_BARCODE_UPC_A;
    }
    else if (0 == strcmp("MV_BARCODE_UPC_E", str_type))
    {
        return MV_BARCODE_UPC_E;
    }
    else if (0 == strcmp("MV_BARCODE_EAN_8", str_type))
    {
        return MV_BARCODE_EAN_8;
    }
    else if (0 == strcmp("MV_BARCODE_EAN_13", str_type))
    {
        return MV_BARCODE_EAN_13;
    }
    else if (0 == strcmp("MV_BARCODE_CODE128", str_type))
    {
        return MV_BARCODE_CODE128;
    }
    else if (0 == strcmp("MV_BARCODE_CODE39", str_type))
    {
        return MV_BARCODE_CODE39;
    }
    else if (0 == strcmp("MV_BARCODE_I2_5", str_type))
    {
        return MV_BARCODE_I2_5;
    }
    else if (0 == strcmp("MV_BARCODE_EAN_2", str_type))
    {
        return MV_BARCODE_EAN_2;
    }
    else if (0 == strcmp("MV_BARCODE_EAN_5", str_type))
    {
        return MV_BARCODE_EAN_5;
    }
    else if (0 == strcmp("MV_BARCODE_CODE93", str_type))
    {
        return MV_BARCODE_CODE93;
    }
    else if (0 == strcmp("MV_BARCODE_CODABAR", str_type))
    {
        return MV_BARCODE_CODABAR;
    }
    else if (0 == strcmp("MV_BARCODE_DATABAR", str_type))
    {
        return MV_BARCODE_DATABAR;
    }
    else if (0 == strcmp("MV_BARCODE_DATABAR_EXPAND", str_type))
    {
        return MV_BARCODE_DATABAR_EXPAND;
    }

    return MV_BARCODE_UNDEFINED;
}

static mv_barcode_qr_mode_e convert_str_qr_enc_mode(const char *str_type)
{
    if (0 == strcmp("MV_BARCODE_QR_MODE_NUMERIC", str_type))
    {
        return MV_BARCODE_QR_MODE_NUMERIC;
    }
    else if (0 == strcmp("MV_BARCODE_QR_MODE_ALPHANUMERIC", str_type))
    {
        return MV_BARCODE_QR_MODE_ALPHANUMERIC;
    }
    else if (0 == strcmp("MV_BARCODE_QR_MODE_BYTE", str_type))
    {
        return MV_BARCODE_QR_MODE_BYTE;
    }
    else if (0 == strcmp("MV_BARCODE_QR_MODE_UTF8", str_type))
    {
        return MV_BARCODE_QR_MODE_UTF8;
    }

    return MV_BARCODE_QR_MODE_UNAVAILABLE;
}

static mv_barcode_qr_ecc_e convert_str_qr_ecc(const char *str_type)
{
    if (0 == strcmp("MV_BARCODE_QR_ECC_LOW", str_type))
    {
        return MV_BARCODE_QR_ECC_LOW;
    }
    else if (0 == strcmp("MV_BARCODE_QR_ECC_MEDIUM", str_type))
    {
        return MV_BARCODE_QR_ECC_MEDIUM;
    }
    else if (0 == strcmp("MV_BARCODE_QR_ECC_QUARTILE", str_type))
    {
        return MV_BARCODE_QR_ECC_QUARTILE;
    }
    else if (0 == strcmp("MV_BARCODE_QR_ECC_HIGH", str_type))
    {
        return MV_BARCODE_QR_ECC_HIGH;
    }

    return MV_BARCODE_QR_ECC_UNAVAILABLE;
}

static mv_colorspace_e convert_str_colorspace(const char *str_cs)
{
    if (0 == strcmp("MEDIA_VISION_COLORSPACE_Y800", str_cs))
    {
        return MEDIA_VISION_COLORSPACE_Y800;
    }
    else if (0 == strcmp("MEDIA_VISION_COLORSPACE_I420", str_cs))
    {
        return MEDIA_VISION_COLORSPACE_I420;
    }
    else if (0 == strcmp("MEDIA_VISION_COLORSPACE_NV12", str_cs))
    {
        return MEDIA_VISION_COLORSPACE_NV12;
    }
    else if (0 == strcmp("MEDIA_VISION_COLORSPACE_YV12", str_cs))
    {
        return MEDIA_VISION_COLORSPACE_YV12;
    }
    else if (0 == strcmp("MEDIA_VISION_COLORSPACE_NV21", str_cs))
    {
        return MEDIA_VISION_COLORSPACE_NV21;
    }
    else if (0 == strcmp("MEDIA_VISION_COLORSPACE_YUYV", str_cs))
    {
        return MEDIA_VISION_COLORSPACE_YUYV;
    }
    else if (0 == strcmp("MEDIA_VISION_COLORSPACE_UYVY", str_cs))
    {
        return MEDIA_VISION_COLORSPACE_UYVY;
    }
    else if (0 == strcmp("MEDIA_VISION_COLORSPACE_422P", str_cs))
    {
        return MEDIA_VISION_COLORSPACE_422P;
    }
    else if (0 == strcmp("MEDIA_VISION_COLORSPACE_RGB565", str_cs))
    {
        return MEDIA_VISION_COLORSPACE_RGB565;
    }
    else if (0 == strcmp("MEDIA_VISION_COLORSPACE_RGB888", str_cs))
    {
        return MEDIA_VISION_COLORSPACE_RGB888;
    }
    else if (0 == strcmp("MEDIA_VISION_COLORSPACE_RGBA", str_cs))
    {
        return MEDIA_VISION_COLORSPACE_RGBA;
    }

    return MEDIA_VISION_COLORSPACE_INVALID;
}

static mv_error_e convert_str_expected_res(const char *str_type)
{
    if (0 == strcmp("MEDIA_VISION_ERROR_NOT_SUPPORTED", str_type))
    {
        return MEDIA_VISION_ERROR_NOT_SUPPORTED;
    }
    else if (0 == strcmp("MEDIA_VISION_ERROR_MSG_TOO_LONG", str_type))
    {
        return MEDIA_VISION_ERROR_MSG_TOO_LONG;
    }
    else if (0 == strcmp("MEDIA_VISION_ERROR_NO_DATA", str_type))
    {
        return MEDIA_VISION_ERROR_NO_DATA;
    }
    else if (0 == strcmp("MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE", str_type))
    {
        return MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE;
    }
    else if (0 == strcmp("MEDIA_VISION_ERROR_OUT_OF_MEMORY", str_type))
    {
        return MEDIA_VISION_ERROR_OUT_OF_MEMORY;
    }
    else if (0 == strcmp("MEDIA_VISION_ERROR_INVALID_PARAMETER", str_type))
    {
        return MEDIA_VISION_ERROR_INVALID_PARAMETER;
    }
    else if (0 == strcmp("MEDIA_VISION_ERROR_INVALID_OPERATION", str_type))
    {
        return MEDIA_VISION_ERROR_INVALID_OPERATION;
    }
    else if (0 == strcmp("MEDIA_VISION_ERROR_PERMISSION_DENIED", str_type))
    {
        return MEDIA_VISION_ERROR_PERMISSION_DENIED;
    }
    else if (0 == strcmp("MEDIA_VISION_ERROR_NOT_SUPPORTED_FORMAT", str_type))
    {
        return MEDIA_VISION_ERROR_NOT_SUPPORTED_FORMAT;
    }
    else if (0 == strcmp("MEDIA_VISION_ERROR_INTERNAL", str_type))
    {
        return MEDIA_VISION_ERROR_INTERNAL;
    }
    else if (0 == strcmp("MEDIA_VISION_ERROR_INVALID_DATA", str_type))
    {
        return MEDIA_VISION_ERROR_INVALID_DATA;
    }

    return MEDIA_VISION_ERROR_NONE;
}

static void parse_model(JsonObject *jobj_model, struct barcode_model *model)
{
    // defaults:
    snprintf(model->description, DESCRIPTION_FIELD_SIZE, "%s", "");
    snprintf(model->message, MESSAGE_FIELD_SIZE, "%s", "");
    snprintf(model->image_path, IMAGE_PATH_FIELD_SIZE, "%s", "");
    model->width = 0;
    model->height = 0;
    model->type = MV_BARCODE_UNDEFINED;
    model->qr_enc_mode = MV_BARCODE_QR_MODE_UNAVAILABLE;
    model->qr_ecc = MV_BARCODE_QR_ECC_UNAVAILABLE;
    model->qr_version = 0;
    model->colorspace = MEDIA_VISION_COLORSPACE_INVALID;
    model->expected_res = MEDIA_VISION_ERROR_NONE;

    // parse attributes if available:
    if (json_object_has_member(jobj_model, "description"))
    {
        const char *str_attr =
                (char*)json_object_get_string_member(jobj_model, "description");
        snprintf(model->description, DESCRIPTION_FIELD_SIZE, "%s", str_attr);
    }

    if (json_object_has_member(jobj_model, "message"))
    {
        const char *str_attr =
                (char*)json_object_get_string_member(jobj_model, "message");
        snprintf(model->message, MESSAGE_FIELD_SIZE, "%s", str_attr);
    }

    if (json_object_has_member(jobj_model, "image_name"))
    {
        const char *str_attr =
                (char*)json_object_get_string_member(jobj_model, "image_name");
        snprintf(model->image_path, IMAGE_PATH_FIELD_SIZE, "%s/img/%s",
                 test_res_path, str_attr);
    }

    if (json_object_has_member(jobj_model, "width"))
    {
        model->width = (int)json_object_get_int_member(jobj_model, "width");
    }

    if (json_object_has_member(jobj_model, "height"))
    {
        model->height = (int)json_object_get_int_member(jobj_model, "height");
    }

    if (json_object_has_member(jobj_model, "type"))
    {
        model->type = convert_str_type(
                (char*)json_object_get_string_member(jobj_model, "type"));
    }

    if (json_object_has_member(jobj_model, "qr_enc_mode"))
    {
        model->qr_enc_mode = convert_str_qr_enc_mode(
                (char*)json_object_get_string_member(jobj_model, "qr_enc_mode"));
    }

    if (json_object_has_member(jobj_model, "qr_ecc"))
    {
        model->qr_ecc = convert_str_qr_ecc(
                (char*)json_object_get_string_member(jobj_model, "qr_ecc"));
    }

    if (json_object_has_member(jobj_model, "qr_version"))
    {
        model->qr_version =
                (int)json_object_get_int_member(jobj_model, "qr_version");
    }

    if (json_object_has_member(jobj_model, "colorspace"))
    {
        model->colorspace = convert_str_colorspace(
                (char*)json_object_get_string_member(jobj_model, "colorspace"));
    }

    if (json_object_has_member(jobj_model, "expected"))
    {
        model->expected_res = convert_str_expected_res(
                (char*)json_object_get_string_member(jobj_model, "expected"));
    }
}

static void parse_models_from_section(
        JsonObject *jobj,
        const char *section_name,
        struct barcode_model **models,
        guint *models_n)
{
    if (NULL == models || NULL == models_n)
    {
        printf("No available container for models from %s section. "
               "Some of tests may be skipped!\n", section_name);
        return;
    }

    if (!json_object_has_member(jobj, section_name))
    {
        printf("No available '%s' section in json file!\n", section_name);
        return;
    }

    JsonNode *jobject_models = json_object_get_member(jobj, section_name);
    if (JSON_NODE_ARRAY != json_node_get_node_type(jobject_models))
    {
        printf("Can't parse barcode models from %s section. Some of "
                "tests may be skipped!\n", section_name);
        return;
    }

    JsonArray *jobj_mdl_array = json_node_get_array(jobject_models);
    *models_n = json_array_get_length(jobj_mdl_array);
    *models = (struct barcode_model*)malloc(sizeof(struct barcode_model) * (*models_n));

    guint ind = 0;
    for (ind = 0; ind < *models_n; ++ind)
    {
        JsonNode *jobj_model =
                json_array_get_element(jobj_mdl_array, ind);
        if (JSON_NODE_OBJECT != json_node_get_node_type(jobj_model))
        {
            printf("Positive test case %u in section %s can't be parsed. "
                    "Some of tests may be skipped!\n", ind, section_name);
            continue;
        }

        parse_model(json_node_get_object(jobj_model), &(*models)[ind]);
    }
}

static void load_models(const char *conf_file_path)
{
    JsonParser *parser;
    GError *error = NULL;

    parser = json_parser_new();
    json_parser_load_from_file(parser, conf_file_path, &error);
    if (error)
    {
        g_print("Unable to parse file '%s': %s\n",
                conf_file_path, error->message);
        g_error_free(error);
        g_object_unref(parser);
        return;
    }

    JsonNode *root = json_parser_get_root(parser);
    if (JSON_NODE_OBJECT != json_node_get_node_type(root))
    {
        printf("Can't parse tests configuration file. Incorrect json markup.\n");
        g_object_unref(parser);
        return;
    }

    JsonObject *root_obj = json_node_get_object(root);

    parse_models_from_section(root_obj, json_gen_img_pos_section, &gen_img_models_p, &gen_img_p_n);
    parse_models_from_section(root_obj, json_gen_img_neg_section, &gen_img_models_n, &gen_img_n_n);
    parse_models_from_section(root_obj, json_gen_src_pos_section, &gen_src_models_p, &gen_src_p_n);
    parse_models_from_section(root_obj, json_gen_src_neg_section, &gen_src_models_n, &gen_src_n_n);
    parse_models_from_section(root_obj, json_det_pos_section1, &det_models_p1, &det_p1_n);
    parse_models_from_section(root_obj, json_det_pos_section2, &det_models_p2, &det_p2_n);
    parse_models_from_section(root_obj, json_det_cs_pos_section, &det_cs_models_p, &det_cs_p_n);

    g_object_unref(parser);
}

static int load_raw_file_to_media_source(
        const char *file_path,
        mv_source_h source,
        unsigned int width,
        unsigned int height,
        mv_colorspace_e colorspace)
{
    if (NULL == file_path || NULL == source)
    {
        printf("File path or source is NULL\n");
        return MEDIA_VISION_ERROR_INVALID_PARAMETER;
    }

    FILE *infile = fopen(file_path,"rb");
    if (!infile)
    {
        printf("File [%s] can't be read\n", file_path);
        return MEDIA_VISION_ERROR_PERMISSION_DENIED;
    }

    // obtain the buffer from raw image file:
    fseek(infile , 0 , SEEK_END);
    long int buffer_size = ftell(infile);
    if (buffer_size <= 0)
    {
        fclose(infile);
        printf("Fail : buffer size is less than 0\n");
        return 1;
    }

    rewind(infile);
    unsigned char *data_buffer = malloc(buffer_size);
    if (data_buffer == NULL)
    {
        fclose(infile);
        printf("Fail : data buffer is NULL\n");
        return MEDIA_VISION_ERROR_OUT_OF_MEMORY;
    }

    fread(data_buffer, buffer_size, 1, infile);

    int ret = mv_source_clear(source);
    if (ret != MEDIA_VISION_ERROR_NONE)
    {
        free(data_buffer);
        fclose(infile);
        printf("Fail : source is NULL\n");
        return ret;
    }

    ret = mv_source_fill_by_buffer(source, data_buffer, buffer_size,
                                       width, height, colorspace);

    free(data_buffer);
    fclose(infile);

    assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    return MEDIA_VISION_ERROR_NONE;
}

static int load_image_to_media_source(
        const char *file_path,
        mv_source_h source)
{
    if (NULL == file_path || NULL == source)
    {
        printf("File path or source is NULL\n");
        return MEDIA_VISION_ERROR_INVALID_PARAMETER;
    }

    unsigned long width = 0;
    unsigned long height = 0;
    unsigned long long buffer_size = 0;
    unsigned char *data_buffer = NULL;
    int ret1 = IMAGE_UTIL_ERROR_NONE;
    int ret2 = MEDIA_VISION_ERROR_NONE;
    image_util_decode_h _decoder = NULL;

    ret1 = image_util_decode_create(&_decoder);
    if (ret1 != IMAGE_UTIL_ERROR_NONE) goto _LOAD_IMAGE_FAIL;
    ret1 = image_util_decode_set_input_path(_decoder, file_path);
    if (ret1 != IMAGE_UTIL_ERROR_NONE) goto _LOAD_IMAGE_FAIL;
    ret1 = image_util_decode_set_colorspace(_decoder, IMAGE_UTIL_COLORSPACE_RGB888);
    if (ret1 != IMAGE_UTIL_ERROR_NONE) goto _LOAD_IMAGE_FAIL;
    ret1 = image_util_decode_set_output_buffer(_decoder, &data_buffer);
    if (ret1 != IMAGE_UTIL_ERROR_NONE) goto _LOAD_IMAGE_FAIL;
    ret1 = image_util_decode_run(_decoder, &width, &height, &buffer_size);
    if (ret1 != IMAGE_UTIL_ERROR_NONE) goto _LOAD_IMAGE_FAIL;

    // Only grayscale and RGB jpegs in test set:
    mv_colorspace_e source_colorspace = MEDIA_VISION_COLORSPACE_RGB888;

    ret2 = mv_source_clear(source);
    if (ret2 != MEDIA_VISION_ERROR_NONE) goto _LOAD_IMAGE_FAIL;

    ret2 = mv_source_fill_by_buffer(
                    source, data_buffer, (unsigned int)buffer_size,
                    (unsigned int)width, (unsigned int)height,
                    source_colorspace);

_LOAD_IMAGE_FAIL:
    image_util_decode_destroy(_decoder);
    if(data_buffer)
        free(data_buffer);

    assert_eq(IMAGE_UTIL_ERROR_NONE, ret1);
    assert_eq(MEDIA_VISION_ERROR_NONE, ret2);

    return MEDIA_VISION_ERROR_NONE;
}

void barcode_detected_p_cb(mv_source_h source, mv_engine_config_h engine_cfg,
        const mv_quadrangle_s *barcode_locations,
        const char* messages[], const mv_barcode_type_e *types,
        int number_of_barcodes, void *user_data)
{
    if (number_of_barcodes != 1)
    {
        return;
    }

    struct barcode_model *model = (struct barcode_model*)user_data;

    if (strcmp(model->message, messages[0]) !=0 )
    {
        return;
    }

    if (model->type != types[0])
    {
        return;
    }
}

void barcode_detected_n_cb(mv_source_h source, mv_engine_config_h engine_cfg,
        const mv_quadrangle_s *barcode_locations,
        const char* messages[], const mv_barcode_type_e *types,
        int number_of_barcodes, void *user_data)
{
    if (number_of_barcodes != 0)
    {
        return;
    }
}

//& set: CapiMedia-vision barcode generate and detect tests:

/**
 * @function		utc_capi_media_vision_barcode_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_media_vision_barcode_startup(void)
{
    printf("capi-media-vision tests STARTUP is launched\n");

    bool isBarcodeDetectionSupported = false;
    bool isBarcodeGenerationSupported = false;

    system_info_get_platform_bool("http://tizen.org/feature/vision.barcode_detection", &isBarcodeDetectionSupported);
    system_info_get_platform_bool("http://tizen.org/feature/vision.barcode_generation", &isBarcodeGenerationSupported);

    char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
    if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
        PRINT_UTC_LOG("[Line: %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE, pszValue);
        unsigned int path_size = strlen(pszValue) + sizeof(char)*9;
        test_res_path = (char*)calloc(path_size, sizeof(char));
        snprintf(test_res_path, path_size, "%s/res/res", pszValue);

        path_size = strlen(pszValue) + sizeof(char)*16;
        test_data_path = (char*)calloc(path_size, sizeof(char));
        snprintf(test_data_path, path_size, "%s/data", pszValue);
    } else {
        PRINT_UTC_LOG("[Line: %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
    }


    if (isBarcodeDetectionSupported || isBarcodeGenerationSupported)
        isVisionSupported = true;
    else
        isVisionSupported = false;

    gStartupError = mv_create_source(&media_source);
    if (MEDIA_VISION_ERROR_NONE != gStartupError)
    {
        _is_broken_source = true;
        media_source = NULL;
        printf("mv_source_h create is failed\n");
        return;
    }

    gStartupError = mv_create_engine_config(&engine_config);
    if (MEDIA_VISION_ERROR_NONE != gStartupError)
    {
        _is_broken_config = true;
        engine_config = NULL;
        printf("mv_engine_config_h create is failed\n");
        return;
    }

    char *test_conf_file_path =
            (char*)malloc(strlen(test_res_path) + strlen(conf_file) + 2);

    if(test_conf_file_path == NULL) {
        printf("test_conf_file_path malloc is failed\n");
        return;
    }

    snprintf(test_conf_file_path, strlen(test_res_path) + strlen(conf_file) + 2, "%s/%s", test_res_path, conf_file);
    test_conf_file_path[strlen(test_res_path) + strlen(conf_file) + 1] = '\0';

    load_models(test_conf_file_path);

    free(test_conf_file_path);

    printf("capi-media-vision tests STARTUP is completed\n");
}

/**
 * @function		utc_capi_media_vision_barcode_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_media_vision_barcode_cleanup(void)
{
    printf("capi-media-vision tests CLEANUP is launched\n");

    if (media_source)
    {
        mv_destroy_source(media_source);
        media_source = NULL;
    }

    if (engine_config)
    {
        mv_destroy_engine_config(engine_config);
        engine_config = NULL;
    }

    if (NULL != gen_img_models_p)
    {
        free(gen_img_models_p);
        gen_img_models_p = NULL;
    }

    if (NULL != gen_img_models_n)
    {
        free(gen_img_models_n);
        gen_img_models_n = NULL;
    }

    if (NULL != gen_src_models_p)
    {
        free(gen_src_models_p);
        gen_src_models_p = NULL;
    }

    if (NULL != gen_src_models_n)
    {
        free(gen_src_models_n);
        gen_src_models_n = NULL;
    }

    if (NULL != det_models_p1)
    {
        free(det_models_p1);
        det_models_p1 = NULL;
    }

    if (NULL != det_models_p2)
    {
        free(det_models_p2);
        det_models_p2 = NULL;
    }

    if (NULL != det_cs_models_p)
    {
        free(det_cs_models_p);
        det_cs_models_p = NULL;
    }

    if (test_res_path) {
        free(test_res_path);
        test_res_path = NULL;
    }

    if (test_data_path) {
        free(test_data_path);
        test_data_path = NULL;
    }

    printf("capi-media-vision tests CLEANUP is completed\n");
}

//& purpose: Tests mv_barcode_generate_image() function for all positive
//           test cases parsed from configuration file.
/**
 * @testcase		utc_mediavision_mv_barcode_generate_image_p
 * @since_tizen		2.4
 * @description		Generate barcode and save it as image file
 */
int utc_mediavision_mv_barcode_generate_image_p(void)
{
    printf("capi-media-vision mv_barcode_generate_image POSITIVE tests are launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_config);
    assert_neq(NULL, gen_img_models_p);

    int ind = 0;

    char path_to_save[1024] = "";
    for (ind = 0; ind < gen_img_p_n; ++ind)
    {
        printf("\nTest description: %s\n", gen_img_models_p[ind].description);

        int image_format = MV_BARCODE_IMAGE_FORMAT_BMP - 1;
        while (image_format < MV_BARCODE_IMAGE_FORMAT_PNG)
        {
            ++image_format;

            snprintf(path_to_save, 1024, "%s/test-barcode-%i", test_data_path, ind);

            assert_eq(MEDIA_VISION_ERROR_NONE,
                      mv_barcode_generate_image(
                              engine_config, gen_img_models_p[ind].message,
                              gen_img_models_p[ind].width,
                              gen_img_models_p[ind].height,
                              gen_img_models_p[ind].type,
                              gen_img_models_p[ind].qr_enc_mode,
                              gen_img_models_p[ind].qr_ecc,
                              gen_img_models_p[ind].qr_version,
                              path_to_save, image_format));
        }

        printf("PASSED\n");
    }

    printf("capi-media-vision mv_barcode_generate_image POSITIVE tests are completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_generate_source() function for all positive
//           test cases parsed from configuration file.
/**
 * @testcase		utc_mediavision_mv_barcode_generate_source_p
 * @since_tizen		2.4
 * @description		Generate barcode and save it in memory
 */
int utc_mediavision_mv_barcode_generate_source_p(void)
{
    printf("capi-media-vision mv_barcode_generate_source POSITIVE tests are launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_source);
    assert_eq(false, _is_broken_config);

    if (NULL == gen_src_models_p)
    {
        printf("capi-media-vision mv_barcode_generate_source POSITIVE tests "
                "can't be launched due to unexisted test cases.\n"
                "SKIPPED\n");
        assert_neq(NULL, gen_src_models_p);
        return 0;
    }

    int ind = 0;

    for (ind = 0; ind < gen_src_p_n; ++ind)
    {
        printf("\nTest description: %s\n", gen_src_models_p[ind].description);

        assert_eq(MEDIA_VISION_ERROR_NONE,
                  mv_barcode_generate_source(
                          engine_config, gen_src_models_p[ind].message,
                          gen_src_models_p[ind].type,
                          gen_src_models_p[ind].qr_enc_mode,
                          gen_src_models_p[ind].qr_ecc,
                          gen_src_models_p[ind].qr_version,
                          media_source));

        assert_neq(NULL, media_source);
        unsigned char *data_buffer = NULL;
        unsigned int buffer_size = 0;
        mv_source_get_buffer(media_source, &data_buffer, &buffer_size);
        assert_neq(NULL, data_buffer);
        assert_neq(0, buffer_size);

        unsigned int width = 0;
        unsigned int height = 0;
        int ret1 = mv_source_get_width(media_source, &width);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret1);

        int ret2 = mv_source_get_height(media_source, &height);
        assert_eq(MEDIA_VISION_ERROR_NONE, ret2);

        assert_neq(0, width);
        assert_neq(0, height);

        assert_eq(MEDIA_VISION_ERROR_NONE, mv_source_clear(media_source));

        printf("PASSED\n");
    }

    printf("capi-media-vision mv_barcode_generate_source POSITIVE tests are completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_detect() function for all positive (QR code)
//           test cases parsed from configuration file and generated previously
//           to the image files.
/**
 * @testcase		utc_mediavision_mv_barcode_detect_p1
 * @since_tizen		2.4
 * @description		Detect barcode
 */
int utc_mediavision_mv_barcode_detect_p1(void)
{
    printf("capi-media-vision mv_barcode_detect POSITIVE tests (QR code) are launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_source);
    assert_eq(false, _is_broken_config);

    if (NULL == det_models_p1)
    {
        printf("capi-media-vision mv_barcode_detect POSITIVE tests (QR code) "
                "can't be launched due to unexisted test cases.\n"
                "SKIPPED\n");
        assert_neq(NULL, det_models_p1);
        return 0;
    }

    int ind = 0;

    for (ind = 0; ind < det_p1_n; ++ind)
    {
        printf("\nTest description: %s\n[%s]\n", det_models_p1[ind].description,
                det_models_p1[ind].image_path);

        assert_eq(MEDIA_VISION_ERROR_NONE,
                  load_image_to_media_source(det_models_p1[ind].image_path,
                                             media_source));

        mv_rectangle_s roi;
        roi.point.x = 0;
        roi.point.y = 0;
        assert_eq(MEDIA_VISION_ERROR_NONE,
                mv_source_get_width(media_source, &(roi.width)));
        assert_eq(MEDIA_VISION_ERROR_NONE,
                mv_source_get_height(media_source, &(roi.height)));

        assert_eq(MEDIA_VISION_ERROR_NONE,
                  mv_barcode_detect(
                          media_source, engine_config, roi,
                          barcode_detected_p_cb, &det_models_p1[ind]));

        assert_eq(MEDIA_VISION_ERROR_NONE, mv_source_clear(media_source));

        printf("PASSED\n");
    }

    printf("capi-media-vision mv_barcode_detect POSITIVE tests (QR code) are completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_detect() function for the barcode image buffer
//           of different supported colorspaces.
/**
 * @testcase		utc_mediavision_mv_barcode_detect_p2
 * @since_tizen		2.4
 * @description		Detect barcode
 */
int utc_mediavision_mv_barcode_detect_p2(void)
{
    printf("capi-media-vision mv_barcode_detect POSITIVE tests for colorspaces "
            "are launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_source);
    assert_eq(false, _is_broken_config);

    if (NULL == det_cs_models_p)
    {
        printf("capi-media-vision mv_barcode_detect POSITIVE tests for "
                "colorspaces can't be launched due to unexisted test cases.\n"
                "SKIPPED\n");
        assert_neq(NULL, det_cs_models_p);
        return 0;
    }

    int ind = 0;

    for (ind = 0; ind < det_cs_p_n; ++ind)
    {
        printf("\nTest description: %s\n[%s]\n", det_cs_models_p[ind].description,
                det_cs_models_p[ind].image_path);

        assert_eq(MEDIA_VISION_ERROR_NONE,
                load_raw_file_to_media_source(
                        det_cs_models_p[ind].image_path,
                        media_source,
                        det_cs_models_p[ind].width,
                        det_cs_models_p[ind].height,
                        det_cs_models_p[ind].colorspace));

        mv_rectangle_s roi;
        roi.point.x = 0;
        roi.point.y = 0;
        assert_eq(MEDIA_VISION_ERROR_NONE,
                mv_source_get_width(media_source, &(roi.width)));
        assert_eq(MEDIA_VISION_ERROR_NONE,
                mv_source_get_height(media_source, &(roi.height)));

        assert_eq(MEDIA_VISION_ERROR_NONE,
                  mv_barcode_detect(
                          media_source, engine_config, roi,
                          barcode_detected_p_cb, &det_cs_models_p[ind]));

        assert_eq(MEDIA_VISION_ERROR_NONE, mv_source_clear(media_source));

        printf("PASSED\n");
    }

    printf("capi-media-vision mv_barcode_detect POSITIVE tests for colorspaces "
            "are completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_detect() function for all positive (1D Barcode)
//           test cases parsed from configuration file and generated previously
//           to the image files.
/**
 * @testcase		utc_mediavision_mv_barcode_detect_p3
 * @since_tizen		2.4
 * @description		Detect barcode
 */
int utc_mediavision_mv_barcode_detect_p3(void)
{
    printf("capi-media-vision mv_barcode_detect POSITIVE tests (1D Barcode) are launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_source);
    assert_eq(false, _is_broken_config);

    if (NULL == det_models_p2)
    {
        printf("capi-media-vision mv_barcode_detect POSITIVE tests (1D Barcode) "
                "can't be launched due to unexisted test cases.\n"
                "SKIPPED\n");
        assert_neq(NULL, det_models_p2);
        return 0;
    }

    int ind = 0;

    for (ind = 0; ind < det_p2_n; ++ind)
    {
        printf("\nTest description: %s\n[%s]\n", det_models_p2[ind].description,
                det_models_p2[ind].image_path);

        assert_eq(MEDIA_VISION_ERROR_NONE,
                  load_image_to_media_source(det_models_p2[ind].image_path,
                                             media_source));

        mv_rectangle_s roi;
        roi.point.x = 0;
        roi.point.y = 0;
        assert_eq(MEDIA_VISION_ERROR_NONE,
                mv_source_get_width(media_source, &(roi.width)));
        assert_eq(MEDIA_VISION_ERROR_NONE,
                mv_source_get_height(media_source, &(roi.height)));

        assert_eq(MEDIA_VISION_ERROR_NONE,
                  mv_barcode_detect(
                          media_source, engine_config, roi,
                          barcode_detected_p_cb, &det_models_p2[ind]));

        assert_eq(MEDIA_VISION_ERROR_NONE, mv_source_clear(media_source));

        printf("PASSED\n");
    }

    printf("capi-media-vision mv_barcode_detect POSITIVE tests (1D Barcode) are completed\n");

    return 0;
}


//& purpose: Tests mv_barcode_generate_image() function for all negative
//           test cases parsed from configuration file.
/**
 * @testcase		utc_mediavision_mv_barcode_generate_image_n1
 * @since_tizen		2.4
 * @description		Generate barcode image but fail because of invalid specification.
 *                  For example, UPC-A barcode doesn't support text input
 */
int utc_mediavision_mv_barcode_generate_image_n1(void)
{
    printf("capi-media-vision mv_barcode_generate_image NEGATIVE test is launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_config);

    if (NULL == gen_img_models_n)
    {
        printf("capi-media-vision mv_barcode_generate_image NEGATIVE tests "
                "can't be launched due to unexisted test cases.\n"
                "SKIPPED\n");
        assert_neq(NULL, gen_img_models_n);
        return 0;
    }

    int ind = 0;

    char path_to_save[1024] = "";
    for (ind = 0; ind < gen_img_n_n; ++ind)
    {
        printf("\nTest description: %s\n", gen_img_models_n[ind].description);

        int image_format = MV_BARCODE_IMAGE_FORMAT_BMP - 1;
        while (image_format < MV_BARCODE_IMAGE_FORMAT_PNG)
        {
            ++image_format;

            snprintf(path_to_save, 1024, "%s/test-barcode-%i", test_data_path, ind);
            int ret = mv_barcode_generate_image(
                    engine_config,
                    gen_img_models_n[ind].message,
                    gen_img_models_n[ind].width, gen_img_models_n[ind].height,
                    gen_img_models_n[ind].type, gen_img_models_n[ind].qr_enc_mode,
                    gen_img_models_n[ind].qr_ecc, gen_img_models_n[ind].qr_version,
                    path_to_save, image_format);

            assert(gen_img_models_n[ind].expected_res == ret);
        }

        printf("PASSED\n");
    }

    printf("capi-media-vision mv_barcode_generate_image NEGATIVE test is completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_generate_image() function for the following case:
//           input message parameter is NULL.
/**
 * @testcase		utc_mediavision_mv_barcode_generate_image_n2
 * @since_tizen		2.4
 * @description		Generate barcode image but fail because input message is null
 */
int utc_mediavision_mv_barcode_generate_image_n2(void)
{
    printf("capi-media-vision mv_barcode_generate_image NEGATIVE test is launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_config);

    char path_to_save[1024] = "";
    snprintf(path_to_save, 1024, "%s/foo", test_data_path);

    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER,
              mv_barcode_generate_image(
                        engine_config, NULL, 500, 500,
                        MV_BARCODE_QR, MV_BARCODE_QR_MODE_UTF8,
                        MV_BARCODE_QR_ECC_HIGH, 25,
                        path_to_save, MV_BARCODE_IMAGE_FORMAT_PNG));

    printf("PASSED\n");
    printf("capi-media-vision mv_barcode_generate_image NEGATIVE test is completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_generate_image() function for the following case:
//           input image_path parameter is NULL.
/**
 * @testcase		utc_mediavision_mv_barcode_generate_image_n3
 * @since_tizen		2.4
 * @description		Generate barcode image but fail because image_path is null
 */
int utc_mediavision_mv_barcode_generate_image_n3(void)
{
    printf("capi-media-vision mv_barcode_generate_image NEGATIVE test is launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_config);

    assert_eq(MEDIA_VISION_ERROR_INVALID_PATH,
            mv_barcode_generate_image(
                        engine_config, "test message", 500, 500,
                        MV_BARCODE_QR, MV_BARCODE_QR_MODE_UTF8,
                        MV_BARCODE_QR_ECC_HIGH, 25,
                        NULL, MV_BARCODE_IMAGE_FORMAT_PNG));

    printf("PASSED\n");
    printf("capi-media-vision mv_barcode_generate_image NEGATIVE test is completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_generate_image() function for the following case:
//           image foramt is MV_BARCODE_IMAGE_FORMAT_UNAVAILABLE.
/**
 * @testcase		utc_mediavision_mv_barcode_generate_image_n4
 * @since_tizen		2.4
 * @description		Generate barcode image but fail because image format is not supported
 */
int utc_mediavision_mv_barcode_generate_image_n4(void)
{
    printf("capi-media-vision mv_barcode_generate_image NEGATIVE test is launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_config);

    char path_to_save[1024] = "";
    snprintf(path_to_save, 1024, "%s/foo", test_data_path);

    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER,
            mv_barcode_generate_image(
                        engine_config, "test message", 500, 500,
                        MV_BARCODE_QR, MV_BARCODE_QR_MODE_BYTE,
                        MV_BARCODE_QR_ECC_HIGH, 25,
                        path_to_save, MV_BARCODE_IMAGE_FORMAT_UNAVAILABLE));

    printf("PASSED\n");
    printf("capi-media-vision mv_barcode_generate_image NEGATIVE test is completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_generate_source() function for all negative
//           test cases parsed from configuration file.
/**
 * @testcase		utc_mediavision_mv_barcode_generate_source_n1
 * @since_tizen		2.4
 * @description		Generate barcode into source but fail because of invalid specification.
 *                  For example, UPC-A barcode doesn't support text input
 */
int utc_mediavision_mv_barcode_generate_source_n1(void)
{
    printf("capi-media-vision mv_barcode_generate_source NEGATIVE test is launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_source);
    assert_eq(false, _is_broken_config);

    if (NULL == gen_src_models_n)
    {
        printf("capi-media-vision mv_barcode_generate_source NEGATIVE tests "
                "can't be launched due to unexisted test cases.\n"
                "SKIPPED\n");
        assert_neq(NULL, gen_src_models_n);
        return 0;
    }

    int ind = 0;

    for (ind = 0; ind < gen_src_n_n; ++ind)
    {
        printf("\nTest description: %s\n", gen_src_models_n[ind].description);

        int ret = mv_barcode_generate_source(
                engine_config,
                gen_src_models_n[ind].message, gen_src_models_n[ind].type,
                gen_src_models_n[ind].qr_enc_mode, gen_src_models_n[ind].qr_ecc,
                gen_src_models_n[ind].qr_version,
                media_source);

        assert_eq(gen_src_models_n[ind].expected_res, ret);
        printf("PASSED\n");
    }

    printf("capi-media-vision mv_barcode_generate_source NEGATIVE test is completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_generate_source() function for the following case:
//           input source parameter is NULL
/**
 * @testcase		utc_mediavision_mv_barcode_generate_source_n2
 * @since_tizen		2.4
 * @description		Generate barcode into source but fail because input source is null
 */
int utc_mediavision_mv_barcode_generate_source_n2(void)
{
    printf("capi-media-vision mv_barcode_generate_source NEGATIVE test is launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_source);
    assert_eq(false, _is_broken_config);

    printf("Input parameter source = NULL\n");

    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER,
              mv_barcode_generate_source(
                    engine_config, "test message", MV_BARCODE_QR,
                    MV_BARCODE_QR_MODE_UTF8, MV_BARCODE_QR_ECC_HIGH, 25, NULL));
    printf("PASSED\n");

    printf("capi-media-vision mv_barcode_generate_source NEGATIVE test is completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_detect() function for the following negative case:
//           input source parameter is NULL
/**
 * @testcase		utc_mediavision_mv_barcode_detect_n1
 * @since_tizen		2.4
 * @description		Detect barcode but fail because input source is null
 */
int utc_mediavision_mv_barcode_detect_n1(void)
{
    printf("capi-media-vision mv_barcode_detect NEGATIVE test is launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_config);

    mv_rectangle_s roi;
    roi.point.x = 0;
    roi.point.y = 0;
    roi.width = 0;
    roi.height = 0;

    printf("Input parameter source = NULL\n");
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER,
              mv_barcode_detect(NULL, engine_config, roi,
                                barcode_detected_n_cb, NULL));
    printf("PASSED\n");

    printf("capi-media-vision mv_barcode_detect NEGATIVE test is completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_detect() function for the following negative case:
//           input detect_cb parameter is NULL
/**
 * @testcase		utc_mediavision_mv_barcode_detect_n2
 * @since_tizen		2.4
 * @description		Detect barcode but fail because callback is null
 */
int utc_mediavision_mv_barcode_detect_n2(void)
{
    printf("capi-media-vision mv_barcode_detect NEGATIVE test is launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_source);
    assert_eq(false, _is_broken_config);

    mv_rectangle_s roi;
    roi.point.x = 0;
    roi.point.y = 0;
    roi.width = 0;
    roi.height = 0;

    printf("Input parameter detect_cb = NULL\n");
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER,
              mv_barcode_detect(media_source, engine_config, roi, NULL, NULL));
    printf("PASSED\n");

    printf("capi-media-vision mv_barcode_detect NEGATIVE test is completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_detect() function for the following negative case:
//           input media_source colorspace isn't supported
/**
 * @testcase		utc_mediavision_mv_barcode_detect_n3
 * @since_tizen		2.4
 * @description		Detect barcode but fail because colorspace is not supported
 */
int utc_mediavision_mv_barcode_detect_n3(void)
{
    printf("capi-media-vision mv_barcode_detect NEGATIVE test is launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_source);
    assert_eq(false, _is_broken_config);

    unsigned char *buffer = NULL;
    const unsigned int width = 800;
    const unsigned int height = 600;
    const size_t buffer_size = width * height;
    buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));
    assert(buffer);

    int ind = 0;
    for (; ind < buffer_size; ++ind)
    {
        buffer[ind] = 255; // Black image
    }

    mv_rectangle_s roi;
    roi.point.x = 0;
    roi.point.y = 0;
    roi.width = width;
    roi.height = height;

	int ret = mv_source_fill_by_buffer(media_source, buffer,
		buffer_size, width, height,
		MEDIA_VISION_COLORSPACE_INVALID);

	free(buffer);
	assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("Colorspace of the media source is "
            "MEDIA_VISION_COLORSPACE_INVALID (i.e. not supported)\n");
    assert_eq(MEDIA_VISION_ERROR_NOT_SUPPORTED_FORMAT,
              mv_barcode_detect(media_source, engine_config, roi,
                                barcode_detected_n_cb, NULL));
    printf("PASSED\n");

    printf("capi-media-vision mv_barcode_detect NEGATIVE test is completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_detect() function for the following negative case:
//           input roi is out of area
/**
 * @testcase		utc_mediavision_mv_barcode_detect_n4
 * @since_tizen		2.4
 * @description		Detect Bacode but fail because input roi is out of area
 */
int utc_mediavision_mv_barcode_detect_n4(void)
{
    printf("capi-media-vision mv_barcode_detect NEGATIVE test is launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_source);
    assert_eq(false, _is_broken_config);

    unsigned char *buffer = NULL;
    const unsigned int width = 800;
    const unsigned int height = 600;
    const size_t buffer_size = width * height;
    buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));
    assert(buffer);

    int ind = 0;
    for (; ind < buffer_size; ++ind)
    {
        buffer[ind] = 255; // Black image
    }

    mv_rectangle_s roi;
    roi.point.x = -1;
    roi.point.y = -1;
    roi.width = width;
    roi.height = height;

	int ret = mv_source_fill_by_buffer(media_source, buffer,
		buffer_size, width, height,
		MEDIA_VISION_COLORSPACE_Y800);

	free(buffer);
	assert_eq(MEDIA_VISION_ERROR_NONE, ret);

    printf("roi is out of area: the left-top corner is (%d,%d)\n", roi.point.x, roi.point.y);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER,
              mv_barcode_detect(media_source, engine_config, roi,
                                barcode_detected_n_cb, NULL));
    printf("PASSED\n");

    printf("capi-media-vision mv_barcode_detect NEGATIVE test is completed\n");

    return 0;
}

//& purpose: Tests mv_barcode_detect() function for the following negative case:
//           input roi is out of area
/**
 * @testcase		utc_mediavision_mv_barcode_detect_n5
 * @since_tizen		2.4
 * @description		Detect barcode but fail because input roi is out of area
 */
int utc_mediavision_mv_barcode_detect_n5(void)
{
    printf("capi-media-vision mv_barcode_detect NEGATIVE test is launched\n");

    if (!isVisionSupported) {
        assert_eq(gStartupError, MEDIA_VISION_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(false, _is_broken_source);
    assert_eq(false, _is_broken_config);

    unsigned char *buffer = NULL;
    const unsigned int width = 800;
    const unsigned int height = 600;
    const size_t buffer_size = width * height;
    buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));
    assert(buffer);

    int ind = 0;
    for (; ind < buffer_size; ++ind)
    {
        buffer[ind] = 255; // Black image
    }

    mv_rectangle_s roi;
    roi.point.x = width;
    roi.point.y = height;
    roi.width = width;
    roi.height = height;

	int ret = mv_source_fill_by_buffer(media_source, buffer,
		buffer_size, width, height,
		MEDIA_VISION_COLORSPACE_Y800);

	free(buffer);
	assert_eq(MEDIA_VISION_ERROR_NONE,ret);

    printf("roi is out of area: the right-bottom corner is (%d,%d)\n",
            roi.point.x + roi.width, roi.point.y + roi.height);
    assert_eq(MEDIA_VISION_ERROR_INVALID_PARAMETER,
              mv_barcode_detect(media_source, engine_config, roi,
                                barcode_detected_n_cb, NULL));
    printf("PASSED\n");

    printf("capi-media-vision mv_barcode_detect NEGATIVE test is completed\n");

    return 0;
}
