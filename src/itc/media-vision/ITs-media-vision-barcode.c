//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-media-vision-common.h"

//& set: MediaVision

/** @addtogroup itc-media-vision
*  @ingroup itc
*  @{
*/

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

static const char *pszJsonImgSection = "gen_positive";
static const char *pszJsonSrcSection = "gen_positive";
static const char *pszJsonDetectSection = "det_positive1";

static struct barcode_model *ImageModel = NULL;
static int nImageModelLength = 0;
static struct barcode_model *SourceModel = NULL;
static int nSourceModelLength = 0;
static struct barcode_model *DetectModel = NULL;
static int nDetectModelLength = 0;

/**
* @function 		GetBarcodeImageFormat
* @description	 	map image type strings
* @parameter		int nValue
* @return 			char pointer  value
*/
static char * GetBarcodeImageFormat(int nValue)
{
	char *pszVal = NULL;
	switch(nValue)
	{
		case MV_BARCODE_IMAGE_FORMAT_BMP:			pszVal = "bmp";			break;
		case MV_BARCODE_IMAGE_FORMAT_JPG:			pszVal = "jpg";			break;
		case MV_BARCODE_IMAGE_FORMAT_PNG:			pszVal = "png";			break;
		case MV_BARCODE_IMAGE_FORMAT_NUM:			pszVal = "num";			break;
		default:									pszVal = "unavailable";				break;
	}
	return pszVal;
}

/**
* @function 		GetErrorStringFormat
* @description	 	map error type strings
* @parameter		const char *str_type
* @return 			mv_error_e
*/
static mv_error_e GetErrorStringFormat(const char *str_type)
{
	size_t nLength = strlen(str_type);
	if (0 == strncmp("MEDIA_VISION_ERROR_NOT_SUPPORTED", str_type, nLength))
	{
		return MEDIA_VISION_ERROR_NOT_SUPPORTED;
	}
	else if (0 == strncmp("MEDIA_VISION_ERROR_MSG_TOO_LONG", str_type, nLength))
	{
		return MEDIA_VISION_ERROR_MSG_TOO_LONG;
	}
	else if (0 == strncmp("MEDIA_VISION_ERROR_NO_DATA", str_type, nLength))
	{
		return MEDIA_VISION_ERROR_NO_DATA;
	}
	else if (0 == strncmp("MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE", str_type, nLength))
	{
		return MEDIA_VISION_ERROR_KEY_NOT_AVAILABLE;
	}
	else if (0 == strncmp("MEDIA_VISION_ERROR_OUT_OF_MEMORY", str_type, nLength))
	{
		return MEDIA_VISION_ERROR_OUT_OF_MEMORY;
	}
	else if (0 == strncmp("MEDIA_VISION_ERROR_INVALID_PARAMETER", str_type, nLength))
	{
		return MEDIA_VISION_ERROR_INVALID_PARAMETER;
	}
	else if (0 == strncmp("MEDIA_VISION_ERROR_INVALID_OPERATION", str_type, nLength))
	{
		return MEDIA_VISION_ERROR_INVALID_OPERATION;
	}
	else if (0 == strncmp("MEDIA_VISION_ERROR_PERMISSION_DENIED", str_type, nLength))
	{
		return MEDIA_VISION_ERROR_PERMISSION_DENIED;
	}
	else if (0 == strncmp("MEDIA_VISION_ERROR_NOT_SUPPORTED_FORMAT", str_type, nLength))
	{
		return MEDIA_VISION_ERROR_NOT_SUPPORTED_FORMAT;
	}
	else if (0 == strncmp("MEDIA_VISION_ERROR_INTERNAL", str_type, nLength))
	{
		return MEDIA_VISION_ERROR_INTERNAL;
	}
	else if (0 == strncmp("MEDIA_VISION_ERROR_INVALID_DATA", str_type, nLength))
	{
		return MEDIA_VISION_ERROR_INVALID_DATA;
	}

	return MEDIA_VISION_ERROR_NONE;
}

/**
* @function 		GetBarcodeType
* @description	 	map barcode type strings
* @parameter		const char *str_type
* @return 			mv_barcode_type_e
*/
static mv_barcode_type_e GetBarcodeType(const char *str_type)
{
	size_t nLength = strlen(str_type);
	if (0 == strncmp("MV_BARCODE_QR", str_type, nLength))
	{
		return MV_BARCODE_QR;
	}
	else if (0 == strncmp("MV_BARCODE_UPC_A", str_type, nLength))
	{
		return MV_BARCODE_UPC_A;
	}
	else if (0 == strncmp("MV_BARCODE_UPC_E", str_type, nLength))
	{
		return MV_BARCODE_UPC_E;
	}
	else if (0 == strncmp("MV_BARCODE_EAN_8", str_type, nLength))
	{
		return MV_BARCODE_EAN_8;
	}
	else if (0 == strncmp("MV_BARCODE_EAN_13", str_type, nLength))
	{
		return MV_BARCODE_EAN_13;
	}
	else if (0 == strncmp("MV_BARCODE_CODE128", str_type, nLength))
	{
		return MV_BARCODE_CODE128;
	}
	else if (0 == strncmp("MV_BARCODE_CODE39", str_type, nLength))
	{
		return MV_BARCODE_CODE39;
	}
	else if (0 == strncmp("MV_BARCODE_I2_5", str_type, nLength))
	{
		return MV_BARCODE_I2_5;
	}
	else if (0 == strncmp("MV_BARCODE_EAN_2", str_type, nLength))
	{
		return MV_BARCODE_EAN_2;
	}
	else if (0 == strncmp("MV_BARCODE_EAN_5", str_type, nLength))
	{
		return MV_BARCODE_EAN_5;
	}
	else if (0 == strncmp("MV_BARCODE_CODE93", str_type, nLength))
	{
		return MV_BARCODE_CODE93;
	}
	else if (0 == strncmp("MV_BARCODE_CODABAR", str_type, nLength))
	{
		return MV_BARCODE_CODABAR;
	}
	else if (0 == strncmp("MV_BARCODE_DATABAR", str_type, nLength))
	{
		return MV_BARCODE_DATABAR;
	}
	else if (0 == strncmp("MV_BARCODE_DATABAR_EXPAND", str_type, nLength))
	{
		return MV_BARCODE_DATABAR_EXPAND;
	}

	return MV_BARCODE_UNKNOWN;
}

/**
* @function 		GetBarcodeQrEcc
* @description	 	map barcode qr_ecc enc mode strings
* @parameter		const char *str_type
* @return 			mv_barcode_qr_mode_e
*/
static mv_barcode_qr_mode_e GetBarcodeQrEncMode(const char *str_type)
{
	size_t nLength = strlen(str_type);
	if (0 == strncmp("MV_BARCODE_QR_MODE_NUMERIC", str_type, nLength))
	{
		return MV_BARCODE_QR_MODE_NUMERIC;
	}
	else if (0 == strncmp("MV_BARCODE_QR_MODE_ALPHANUMERIC", str_type, nLength))
	{
		return MV_BARCODE_QR_MODE_ALPHANUMERIC;
	}
	else if (0 == strncmp("MV_BARCODE_QR_MODE_BYTE", str_type, nLength))
	{
		return MV_BARCODE_QR_MODE_BYTE;
	}
	else if (0 == strncmp("MV_BARCODE_QR_MODE_UTF8", str_type, nLength))
	{
		return MV_BARCODE_QR_MODE_UTF8;
	}

	return MV_BARCODE_QR_MODE_UNAVAILABLE;
}

/**
* @function 		GetBarcodeQrEcc
* @description	 	map barcode qr_ecc strings
* @parameter		const char *str_type
* @return 			mv_barcode_qr_ecc_e
*/
static mv_barcode_qr_ecc_e GetBarcodeQrEcc(const char *str_type)
{
	size_t nLength = strlen(str_type);
	if (0 == strncmp("MV_BARCODE_QR_ECC_LOW", str_type, nLength))
	{
		return MV_BARCODE_QR_ECC_LOW;
	}
	else if (0 == strncmp("MV_BARCODE_QR_ECC_MEDIUM", str_type, nLength))
	{
		return MV_BARCODE_QR_ECC_MEDIUM;
	}
	else if (0 == strncmp("MV_BARCODE_QR_ECC_QUARTILE", str_type, nLength))
	{
		return MV_BARCODE_QR_ECC_QUARTILE;
	}
	else if (0 == strncmp("MV_BARCODE_QR_ECC_HIGH", str_type, nLength))
	{
		return MV_BARCODE_QR_ECC_HIGH;
	}

	return MV_BARCODE_QR_ECC_UNAVAILABLE;
}

/**
* @function 		GetColorspace
* @description	 	map colorspace strings
* @parameter		const char *str_cs
* @return 			mv_colorspace_e
*/
static mv_colorspace_e GetColorspace(const char *str_cs)
{
	size_t nLength = strlen(str_cs);
	if (0 == strncmp("MEDIA_VISION_COLORSPACE_Y800", str_cs, nLength))
	{
		return MEDIA_VISION_COLORSPACE_Y800;
	}
	else if (0 == strncmp("MEDIA_VISION_COLORSPACE_I420", str_cs, nLength))
	{
		return MEDIA_VISION_COLORSPACE_I420;
	}
	else if (0 == strncmp("MEDIA_VISION_COLORSPACE_NV12", str_cs, nLength))
	{
		return MEDIA_VISION_COLORSPACE_NV12;
	}
	else if (0 == strncmp("MEDIA_VISION_COLORSPACE_YV12", str_cs, nLength))
	{
		return MEDIA_VISION_COLORSPACE_YV12;
	}
	else if (0 == strncmp("MEDIA_VISION_COLORSPACE_NV21", str_cs, nLength))
	{
		return MEDIA_VISION_COLORSPACE_NV21;
	}
	else if (0 == strncmp("MEDIA_VISION_COLORSPACE_YUYV", str_cs, nLength))
	{
		return MEDIA_VISION_COLORSPACE_YUYV;
	}
	else if (0 == strncmp("MEDIA_VISION_COLORSPACE_UYVY", str_cs, nLength))
	{
		return MEDIA_VISION_COLORSPACE_UYVY;
	}
	else if (0 == strncmp("MEDIA_VISION_COLORSPACE_422P", str_cs, nLength))
	{
		return MEDIA_VISION_COLORSPACE_422P;
	}
	else if (0 == strncmp("MEDIA_VISION_COLORSPACE_RGB565", str_cs, nLength))
	{
		return MEDIA_VISION_COLORSPACE_RGB565;
	}
	else if (0 == strncmp("MEDIA_VISION_COLORSPACE_RGB888", str_cs, nLength))
	{
		return MEDIA_VISION_COLORSPACE_RGB888;
	}
	else if (0 == strncmp("MEDIA_VISION_COLORSPACE_RGBA", str_cs, nLength))
	{
		return MEDIA_VISION_COLORSPACE_RGBA;
	}

	return MEDIA_VISION_COLORSPACE_INVALID;
}

/**
* @function 		ParseModelFromSection
* @description	 	Intialize json section and parse them
* @parameter		JsonObject *jobj_model, struct barcode_model *model
* @return 			NA
*/
void ParseModel(JsonObject *jobj_model, struct barcode_model *model)
{
	snprintf(model->description, BUFFERSIZE, "%s", "");
	snprintf(model->message, MESSAGE_FIELD_SIZE, "%s", "");
	snprintf(model->image_path, BUFFERSIZE, "%s", "");
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
		snprintf(model->description, BUFFERSIZE, "%s", str_attr);
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
		snprintf(model->image_path, BUFFERSIZE, "%s/img/%s",
				 g_pszResPath, str_attr);
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
		model->type = GetBarcodeType((char*)json_object_get_string_member(jobj_model, "type"));
	}

	if (json_object_has_member(jobj_model, "qr_enc_mode"))
	{
		model->qr_enc_mode = GetBarcodeQrEncMode(
				(char*)json_object_get_string_member(jobj_model, "qr_enc_mode"));
	}

	if (json_object_has_member(jobj_model, "qr_ecc"))
	{
		model->qr_ecc = GetBarcodeQrEcc(
				(char*)json_object_get_string_member(jobj_model, "qr_ecc"));
	}

	if (json_object_has_member(jobj_model, "qr_version"))
	{
		model->qr_version =
				(int)json_object_get_int_member(jobj_model, "qr_version");
	}

	if (json_object_has_member(jobj_model, "colorspace"))
	{
		model->colorspace = GetColorspace(
				(char*)json_object_get_string_member(jobj_model, "colorspace"));
	}

	if (json_object_has_member(jobj_model, "expected"))
	{
		model->expected_res = GetErrorStringFormat((char*)json_object_get_string_member(jobj_model, "expected"));
	}
}

/**
* @function 		ParseModelFromSection
* @description	 	parse json sections
* @parameter		JsonObject *jobj, const char *section_name, struct barcode_model **models, guint *models_n
* @return 			NA
*/
void ParseModelFromSection(
        JsonObject *jobj,
        const char *section_name,
        struct barcode_model **models,
        guint *models_n)
{
	if (NULL == models || NULL == models_n)
	{
		FPRINTF("[Line : %d][%s] No available container for models from %s section. "
			   "Some of tests may be skipped!\\n", __LINE__, API_NAMESPACE, section_name);
		return;
	}

	if (!json_object_has_member(jobj, section_name))
	{
		FPRINTF("[Line : %d][%s] No available '%s' section in json file!\\n", __LINE__, API_NAMESPACE, section_name);
		return;
	}

	JsonNode *jobject_models = json_object_get_member(jobj, section_name);
	if (JSON_NODE_ARRAY != json_node_get_node_type(jobject_models))
	{
		FPRINTF("[Line : %d][%s] Can't parse barcode models from %s section. Some of "
				"tests may be skipped!\\n", __LINE__, API_NAMESPACE, section_name);
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
			FPRINTF("[Line : %d][%s] Positive test case %u in section %s can't be parsed. "
					"Some of tests may be skipped!\\n", __LINE__, API_NAMESPACE, ind, section_name);
			continue;
		}

		ParseModel(json_node_get_object(jobj_model), &(*models)[ind]);
	}
}

/**
* @function 		LoadModels
* @description	 	Load json conf file
* @parameter		const char *conf_file_path)
* @return 			NA
*/
void LoadModels(const char *conf_file_path)
{
	JsonParser *parser;
	GError *error = NULL;

	parser = json_parser_new();
	json_parser_load_from_file(parser, conf_file_path, &error);
	FPRINTF("[Line : %d][%s]conf_file_path %s\\n", __LINE__, API_NAMESPACE,conf_file_path);
	if (error)
	{
		FPRINTF("[Line : %d][%s] Unable to parse file '%s' : %s\\n", __LINE__, API_NAMESPACE, conf_file_path, error->message);
		g_error_free(error);
		g_object_unref(parser);
		return;
	}

	JsonNode *root = json_parser_get_root(parser);
	if (JSON_NODE_OBJECT != json_node_get_node_type(root))
	{
		FPRINTF("[Line : %d][%s]Can't parse tests configuration file. Incorrect json markup.\\n", __LINE__, API_NAMESPACE);
		g_object_unref(parser);
		return;
	}

	JsonObject *root_obj = json_node_get_object(root);
	ParseModelFromSection(root_obj, pszJsonImgSection, &ImageModel, &nImageModelLength);
	ParseModelFromSection(root_obj, pszJsonSrcSection, &SourceModel, &nSourceModelLength);
	ParseModelFromSection(root_obj, pszJsonDetectSection, &DetectModel, &nDetectModelLength);

	g_object_unref(parser);
}

/**
* @function 		LoadImageMediaSource
* @description	 	Load image source
* @parameter		const char *file_path, mv_source_h source
* @return 			Media vision error map value
*/
int LoadImageMediaSource(const char *file_path, mv_source_h source)
{
	if (NULL == file_path || NULL == source)
	{
		FPRINTF("[Line : %d][%s] File path or source is NULL\\n", __LINE__, API_NAMESPACE);
		return MEDIA_VISION_ERROR_INVALID_PARAMETER;
	}

	unsigned long nWidth = 0;
	unsigned long nHeight = 0;
	unsigned long long nBufSize = 0;
	unsigned char *pszDataBuf = NULL;
	int nRet1 = IMAGE_UTIL_ERROR_NONE;
	int nRet2 = MEDIA_VISION_ERROR_NONE;
	image_util_decode_h hDecoder = NULL;

	nRet1 = image_util_decode_create(&hDecoder);
	PRINT_RESULT(IMAGE_UTIL_ERROR_NONE, nRet1, "image_util_decode_create",ImageUtilGetError(nRet1));
	CHECK_HANDLE(&hDecoder, "image_util_decode_create");
	nRet1 = image_util_decode_set_input_path(hDecoder, file_path);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet1, "image_util_decode_set_input_path", ImageUtilGetError(nRet1),image_util_decode_destroy(hDecoder));
	nRet1 = image_util_decode_set_colorspace(hDecoder, IMAGE_UTIL_COLORSPACE_RGB888);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet1, "image_util_decode_set_colorspace",ImageUtilGetError(nRet1),image_util_decode_destroy(hDecoder));
	nRet1 = image_util_decode_set_output_buffer(hDecoder, &pszDataBuf);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet1, "image_util_decode_set_output_buffer",ImageUtilGetError(nRet1),image_util_decode_destroy(hDecoder));
	nRet1 = image_util_decode_run(hDecoder, &nWidth, &nHeight, &nBufSize);
	PRINT_RESULT_CLEANUP(IMAGE_UTIL_ERROR_NONE, nRet1, "image_util_decode_run",ImageUtilGetError(nRet1),image_util_decode_destroy(hDecoder);FREE_MEMORY(pszDataBuf));

	// Only grayscale and RGB jpegs in test set:
	mv_colorspace_e source_colorspace = MEDIA_VISION_COLORSPACE_RGB888;

	nRet2 = mv_source_clear(source);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet2, "mv_source_clear",MediaVisionGetError(nRet2),image_util_decode_destroy(hDecoder); FREE_MEMORY(pszDataBuf));
	nRet2 = mv_source_fill_by_buffer(source, pszDataBuf, (unsigned int)nBufSize,(unsigned int)nWidth, (unsigned int)nHeight,source_colorspace);
	PRINT_RESULT_CLEANUP(MEDIA_VISION_ERROR_NONE, nRet2, "mv_source_fill_by_buffer",MediaVisionGetError(nRet2),image_util_decode_destroy(hDecoder); FREE_MEMORY(pszDataBuf));

	image_util_decode_destroy(hDecoder);
	FREE_MEMORY(pszDataBuf);
	return MEDIA_VISION_ERROR_NONE;
}

/**
* @function 		CreateAndGetEngineAttributes
* @description	 	Create Engine and get supported attributes
* @parameter		NA
* @return 			bool value
*/
bool CreateAndGetEngineAttributes(void)
{
	int nRet = -1;
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	char *pszConfPath = NULL;

	nRet = mv_create_engine_config(&g_hMvEngineConfig);
	PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_engine_config", MediaVisionGetError(nRet));
	CHECK_HANDLE(g_hMvEngineConfig, "mv_create_source");

	if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE))
	{
		FPRINTF("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE, pszValue);
		unsigned int nPathLength = strlen(pszValue) + sizeof(char)*9;
		g_pszResPath = (char*)calloc(nPathLength, sizeof(char));
		snprintf(g_pszResPath, nPathLength, "%s/res/res", pszValue);
		g_pszDataPath = app_get_data_path();
	}
	else
	{
		FPRINTF("[Line: %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	pszConfPath = (char*)malloc(strlen(g_pszResPath) + strlen(g_pszCconfFile) + 2);
	if(pszConfPath == NULL)
	{
		FPRINTF("[Line : %d][%s] pszConfPath malloc is failed\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	snprintf(pszConfPath, strlen(g_pszResPath) + strlen(g_pszCconfFile) + 2, "%s/%s", g_pszResPath, g_pszCconfFile);
	pszConfPath[strlen(g_pszResPath) + strlen(g_pszCconfFile) + 1] = '\0';
	LoadModels(pszConfPath);
	free(pszConfPath);
	return true;
}

/**
 * @function 		BarcodeDetectedCB
 * @description	 	Callback Function
 * @parameter		mv_source_h source, mv_engine_config_h engine_cfg, const mv_quadrangle_s *barcode_locations, const char* messages[], const mv_barcode_type_e *types, int number_of_barcodes, void *user_data
 * @return 			NA
 */
void BarcodeDetectedCB(mv_source_h source, mv_engine_config_h engine_cfg, const mv_quadrangle_s *barcode_locations, const char* messages[], const mv_barcode_type_e *types, int number_of_barcodes, void *user_data)
{
	FPRINTF("[Line : %d][%s]Callback Invoked\\n", __LINE__, API_NAMESPACE, "BarcodeDetectedCB");
	if (number_of_barcodes != 1)
	{
		FPRINTF("[Line : %d][%s] number_of_barcodes is not equal to 1\\n", __LINE__, API_NAMESPACE);
		return;
	}

	struct barcode_model *model = (struct barcode_model*)user_data;
	int nLengthMsg = strlen(messages[0]);
	if (strncmp(model->message, messages[0] , nLengthMsg) !=0 )
	{
		FPRINTF("[Line : %d][%s] message mismatch\\n", __LINE__, API_NAMESPACE);
		return;
	}

	if (model->type != types[0])
	{
		FPRINTF("[Line : %d][%s] Barcode type is not zero\\n", __LINE__, API_NAMESPACE);
		return;
	}
}
//& set: CapiMedia-vision barcode generate and detect tests:

/**
 * @function		ITs_media_vision_barcode_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void ITs_media_vision_barcode_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bMediavisionCreation = false;
	g_bIsBarcodeDetectionFeatureSupported = TCTCheckSystemInfoFeatureSupported(BARCODEDETFEATURE, API_NAMESPACE);;
	g_bIsBarcodeGenerationFeatureSupported = TCTCheckSystemInfoFeatureSupported(BARCODEGENFEATURE, API_NAMESPACE);;

	int nRet = mv_create_source(&g_hMvSource);
	if((false == g_bIsBarcodeDetectionFeatureSupported) || (false == g_bIsBarcodeGenerationFeatureSupported))
	{
		FPRINTF("[Line : %d][%s] Barcode feature not supported\\n", __LINE__, API_NAMESPACE);
		PRINT_RESULTNONE(MEDIA_VISION_ERROR_NOT_SUPPORTED, nRet, "mv_create_source", MediaVisionGetError(nRet));
	}
	else
	{
		PRINT_RESULTNONE(MEDIA_VISION_ERROR_NONE, nRet, "mv_create_source", MediaVisionGetError(nRet));
		CHECK_HANDLE_NONE(g_hMvSource, "mv_create_source");
	}
	if( CreateAndGetEngineAttributes() != true  )
	{
		FPRINTF("[Line : %d][%s]  CreateAndGetEngineAttributes failed\\n", __LINE__, API_NAMESPACE);
		return;
	}
	g_bMediavisionCreation = true;
}

/**
 * @function		ITs_media_vision_barcode_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void ITs_media_vision_barcode_cleanup(void)
{
	if (g_hMvSource)
	{
		mv_destroy_source(g_hMvSource);
		g_hMvSource = NULL;
	}

	if (g_hMvEngineConfig)
	{
		mv_destroy_engine_config(g_hMvEngineConfig);
		g_hMvEngineConfig = NULL;
	}

	if (NULL != ImageModel)
	{
		free(ImageModel);
		ImageModel = NULL;
	}

	if (NULL != SourceModel)
	{
		free(SourceModel);
		SourceModel = NULL;
	}

	if (NULL != DetectModel)
	{
		free(DetectModel);
		DetectModel = NULL;
	}

	if (g_pszResPath) {
		free(g_pszResPath);
		g_pszResPath = NULL;
	}

	if (g_pszDataPath) {
		free(g_pszDataPath);
		g_pszDataPath = NULL;
	}
}

/**
 * @testcase 				ITc_mv_barcode_generate_image_p
 * @author            		SRID(gaurav.m2)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_barcode_generate_image
 * @scenario				Call mv_barcode_generate_image
 * @apicovered				mv_barcode_generate_image
 * @passcase				If mv_barcode_generate_image returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_barcode_generate_image
int ITc_mv_barcode_generate_image_p(void)
{
	START_TEST_BARCODE;

	int nIndex = 0, nRet = -1;
	char pszOutputPath[IMAGE_PATH_FIELD_SIZE] = "";

	for (nIndex = 0; nIndex < nImageModelLength; ++nIndex)
	{
		int nImageFormat = MV_BARCODE_IMAGE_FORMAT_BMP - 1;
		while (nImageFormat < MV_BARCODE_IMAGE_FORMAT_PNG)
		{
			++nImageFormat;
			snprintf(pszOutputPath, 1024, "%s/test-barcode-%i", g_pszDataPath, nIndex);
			nRet = mv_barcode_generate_image(g_hMvEngineConfig, ImageModel[nIndex].message, ImageModel[nIndex].width,ImageModel[nIndex].height,
                              ImageModel[nIndex].type,
                              ImageModel[nIndex].qr_enc_mode,
                              ImageModel[nIndex].qr_ecc,
                              ImageModel[nIndex].qr_version,
                              pszOutputPath, nImageFormat);
			PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_barcode_generate_image", MediaVisionGetError(nRet));
			FPRINTF("[Line : %d][%s] Data path = %s\\n", __LINE__, API_NAMESPACE, g_pszDataPath);
			FPRINTF("[Line : %d][%s] Output Image path= %s.%s\\n", __LINE__, API_NAMESPACE, pszOutputPath,GetBarcodeImageFormat(nImageFormat));
		}
	}
	return 0;
}

/**
 * @testcase				ITc_mv_barcode_generate_source_p
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_barcode_generate_source
 * @scenario				Call mv_barcode_generate_source
 * @apicovered				mv_barcode_generate_source
 * @passcase				If mv_barcode_generate_source returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_barcode_generate_source
int ITc_mv_barcode_generate_source_p(void)
{
	START_TEST_BARCODE;

	if (NULL == SourceModel)
	{
		FPRINTF("[Line : %d][%s] src model cannot be parsed.\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nIndex = 0, nRet = -1;
	for (nIndex = 0; nIndex < nSourceModelLength; ++nIndex)
	{
		nRet = mv_barcode_generate_source(
                          g_hMvEngineConfig, SourceModel[nIndex].message,
                          SourceModel[nIndex].type,
                          SourceModel[nIndex].qr_enc_mode,
                          SourceModel[nIndex].qr_ecc,
                          SourceModel[nIndex].qr_version,
                          g_hMvSource);
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_barcode_generate_source", MediaVisionGetError(nRet));
		FPRINTF("[Line : %d][%s] Generate source for barcode type = %d\\n", __LINE__, API_NAMESPACE, SourceModel[nIndex].type);
		nRet = mv_source_clear(g_hMvSource);
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_clear", MediaVisionGetError(nRet));
	}
	return 0;
}

/**
 * @testcase 				ITc_mv_barcode_detect_p
 * @author            		SRID(gaurav.m2)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @since_tizen 			3.0
 * @description				To test mv_barcode_detect
 * @scenario				Call mv_barcode_detect
 * @apicovered				mv_barcode_detect
 * @passcase				If mv_barcode_detect returns MEDIA_VISION_ERROR_NONE
 * @failcase				If Precondition API or Target API Fails
 * @precondition			NA
 * @postcondition			NA
 * */
//& type: auto
//& purpose: To test mv_barcode_detect
int ITc_mv_barcode_detect_p(void)
{
	START_TEST_BARCODE;

	if (NULL == DetectModel)
	{
		FPRINTF("[Line : %d][%s] barcode detect model cannot be parsed.\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	int nIndex = 0, nRet = -1;

	for (nIndex = 0; nIndex < nDetectModelLength; ++nIndex)
	{
		nRet = LoadImageMediaSource(DetectModel[nIndex].image_path, g_hMvSource);
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "LoadImageMediaSource", MediaVisionGetError(nRet));
		FPRINTF("[Line : %d][%s] LoadImageMediaSource done successfully\\n", __LINE__, API_NAMESPACE);

		mv_rectangle_s roi;
		roi.point.x = 0;
		roi.point.y = 0;
		nRet = mv_source_get_width(g_hMvSource, &(roi.width));
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_get_width", MediaVisionGetError(nRet));
		nRet = mv_source_get_height(g_hMvSource, &(roi.height));
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_get_height", MediaVisionGetError(nRet));

		nRet = mv_barcode_detect(g_hMvSource, g_hMvEngineConfig, roi, BarcodeDetectedCB, &DetectModel[nIndex]);
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_barcode_detect", MediaVisionGetError(nRet));
		FPRINTF("[Line : %d][%s] Barcode of height= %i and width=%i are generated succesfully\\n", __LINE__, API_NAMESPACE,roi.height,roi.width);

		nRet = mv_source_clear(g_hMvSource);
		PRINT_RESULT(MEDIA_VISION_ERROR_NONE, nRet, "mv_source_clear", MediaVisionGetError(nRet));
	}
	return 0;
}