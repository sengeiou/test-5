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
#include "ITs-cairo-common.h"

//Add helper function definitions here
/**
 * @function 		CairoGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* CairoGetError(int nRet)
{
	char *pszErrorVal = NULL;
	switch ( nRet )
	{
		case CAIRO_STATUS_SUCCESS:
			pszErrorVal = "CAIRO_STATUS_SUCCESS";
			break;
		case CAIRO_STATUS_NO_MEMORY:
			pszErrorVal = "CAIRO_STATUS_NO_MEMORY";
			break;
		case CAIRO_STATUS_INVALID_RESTORE:
			pszErrorVal = "CAIRO_STATUS_INVALID_RESTORE";
			break;
		case CAIRO_STATUS_INVALID_POP_GROUP:
			pszErrorVal = "CAIRO_STATUS_INVALID_POP_GROUP";
			break;
		case CAIRO_STATUS_NO_CURRENT_POINT:
			pszErrorVal = "CAIRO_STATUS_NO_CURRENT_POINT";
			break;
		case CAIRO_STATUS_INVALID_MATRIX:
			pszErrorVal = "CAIRO_STATUS_INVALID_MATRIX";
			break;
		case CAIRO_STATUS_INVALID_STATUS:
			pszErrorVal = "CAIRO_STATUS_INVALID_STATUS";
			break;
		case CAIRO_STATUS_NULL_POINTER:
			pszErrorVal = "CAIRO_STATUS_NULL_POINTER";
			break;
		case CAIRO_STATUS_INVALID_STRING:
			pszErrorVal = "CAIRO_STATUS_INVALID_STRING";
			break;
		case CAIRO_STATUS_INVALID_PATH_DATA:
			pszErrorVal = "CAIRO_STATUS_INVALID_PATH_DATA";
			break;
		case CAIRO_STATUS_READ_ERROR:
			pszErrorVal = "CAIRO_STATUS_READ_ERROR";
			break;
		case CAIRO_STATUS_WRITE_ERROR:
			pszErrorVal = "CAIRO_STATUS_WRITE_ERROR";
			break;
		case CAIRO_STATUS_SURFACE_FINISHED:
			pszErrorVal = "CAIRO_STATUS_SURFACE_FINISHED";
			break;
		case CAIRO_STATUS_SURFACE_TYPE_MISMATCH:
			pszErrorVal = "CAIRO_STATUS_SURFACE_TYPE_MISMATCH";
			break;
		case CAIRO_STATUS_PATTERN_TYPE_MISMATCH:
			pszErrorVal = "CAIRO_STATUS_PATTERN_TYPE_MISMATCH";
			break;
		case CAIRO_STATUS_INVALID_CONTENT:
			pszErrorVal = "CAIRO_STATUS_INVALID_CONTENT";
			break;
		case CAIRO_STATUS_INVALID_FORMAT:
			pszErrorVal = "CAIRO_STATUS_INVALID_FORMAT";
			break;
		case CAIRO_STATUS_INVALID_VISUAL:
			pszErrorVal = "CAIRO_STATUS_INVALID_VISUAL";
			break;
		case CAIRO_STATUS_FILE_NOT_FOUND:
			pszErrorVal = "CAIRO_STATUS_FILE_NOT_FOUND";
			break;
		case CAIRO_STATUS_INVALID_DASH:
			pszErrorVal = "CAIRO_STATUS_INVALID_DASH";
			break;
		case CAIRO_STATUS_INVALID_DSC_COMMENT:
			pszErrorVal = "CAIRO_STATUS_INVALID_DSC_COMMENT";
			break;
		case CAIRO_STATUS_INVALID_INDEX:
			pszErrorVal = "CAIRO_STATUS_INVALID_INDEX";
			break;
		case CAIRO_STATUS_CLIP_NOT_REPRESENTABLE:
			pszErrorVal = "CAIRO_STATUS_CLIP_NOT_REPRESENTABLE";
			break;
		case CAIRO_STATUS_TEMP_FILE_ERROR:
			pszErrorVal = "CAIRO_STATUS_TEMP_FILE_ERROR";
			break;
		case CAIRO_STATUS_INVALID_STRIDE:
			pszErrorVal = "CAIRO_STATUS_INVALID_STRIDE";
			break;
		case CAIRO_STATUS_FONT_TYPE_MISMATCH:
			pszErrorVal = "CAIRO_STATUS_FONT_TYPE_MISMATCH";
			break;
		case CAIRO_STATUS_USER_FONT_IMMUTABLE:
			pszErrorVal = "CAIRO_STATUS_USER_FONT_IMMUTABLE";
			break;
		case CAIRO_STATUS_USER_FONT_ERROR:
			pszErrorVal = "CAIRO_STATUS_USER_FONT_ERROR";
			break;
		case CAIRO_STATUS_NEGATIVE_COUNT:
			pszErrorVal = "CAIRO_STATUS_NEGATIVE_COUNT";
			break;
		case CAIRO_STATUS_INVALID_CLUSTERS:
			pszErrorVal = "CAIRO_STATUS_INVALID_CLUSTERS";
			break;
		case CAIRO_STATUS_INVALID_SLANT:
			pszErrorVal = "CAIRO_STATUS_INVALID_SLANT";
			break;
		case CAIRO_STATUS_INVALID_WEIGHT:
			pszErrorVal = "CAIRO_STATUS_INVALID_WEIGHT";
			break;
		case CAIRO_STATUS_INVALID_SIZE:
			pszErrorVal = "CAIRO_STATUS_INVALID_SIZE";
			break;
		case CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED:
			pszErrorVal = "CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED";
			break;
		case CAIRO_STATUS_DEVICE_TYPE_MISMATCH:
			pszErrorVal = "CAIRO_STATUS_DEVICE_TYPE_MISMATCH";
			break;
		case CAIRO_STATUS_DEVICE_ERROR:
			pszErrorVal = "CAIRO_STATUS_DEVICE_ERROR";
			break;
		case CAIRO_STATUS_INVALID_MESH_CONSTRUCTION:
			pszErrorVal = "CAIRO_STATUS_INVALID_MESH_CONSTRUCTION";
			break;
		case CAIRO_STATUS_DEVICE_FINISHED:
			pszErrorVal = "CAIRO_STATUS_DEVICE_FINISHED";
			break;
		case CAIRO_STATUS_LAST_STATUS:
			pszErrorVal = "CAIRO_STATUS_LAST_STATUS";
			break;
		default:
			pszErrorVal = "Unknown Error";
			break;
	}

	return pszErrorVal;
}
