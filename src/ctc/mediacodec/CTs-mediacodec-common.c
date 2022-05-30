//
// Copyright (c) 2012-2013 Samsung Electronics Co., Ltd.
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
#include "CTs-mediacodec-common.h"

/** @addtogroup ctc-mediacodec
* @ingroup		ctc
* @{
*/

//Add helper function definitions here

/**
* @function 				MediaCodecGetCodecName
* @description 				get the name of codec
* @parameter[IN]			nType : codec enum
* @return 					name of codec type
*/
char *MediaCodecGetCodecName(int nType)
{
	char *pCodecName =NULL;
	switch ( nType )
	{
	case MEDIACODEC_L16:			pCodecName = "MEDIACODEC_L16";		break;
	case MEDIACODEC_ALAW:			pCodecName = "MEDIACODEC_ALAW";		break;
	case MEDIACODEC_ULAW:			pCodecName = "MEDIACODEC_ULAW";		break;
	case MEDIACODEC_AMR:			pCodecName = "MEDIACODEC_AMR";		break;
	case MEDIACODEC_G729:			pCodecName = "MEDIACODEC_G729";		break;
	case MEDIACODEC_AAC:			pCodecName = "MEDIACODEC_AAC";		break;
	case MEDIACODEC_MP3:			pCodecName = "MEDIACODEC_MP3";		break;
	case MEDIACODEC_H261:			pCodecName = "MEDIACODEC_H261";		break;
	case MEDIACODEC_H263:			pCodecName = "MEDIACODEC_H263";		break;
	case MEDIACODEC_H264:			pCodecName = "MEDIACODEC_H264";		break;
	case MEDIACODEC_MJPEG:			pCodecName = "MEDIACODEC_MJPEG";	break;
	case MEDIACODEC_MPEG1:			pCodecName = "MEDIACODEC_MPEG1";	break;
	case MEDIACODEC_MPEG2:			pCodecName = "MEDIACODEC_MPEG2";	break;
	case MEDIACODEC_MPEG4:			pCodecName = "MEDIACODEC_MPEG4";	break;
	}

	return pCodecName;
}

/**
* @function 				MediaCodecGetCodecSupportedTypeName
* @description 				get the name of supported type for codec
* @parameter[IN]			nType : codec Support enum
* @return 					name of codec type
*/
char *MediaCodecGetCodecSupportedTypeName(int nIndex)
{
	char *pCodecSupportName =NULL;
	switch ( nIndex )
	{
	case MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW:		pCodecSupportName = "MEDIACODEC_ENCODER | MEDIACODEC_SUPPORT_TYPE_SW"; 	break;
	case MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW:		pCodecSupportName = "MEDIACODEC_DECODER | MEDIACODEC_SUPPORT_TYPE_SW"; 	break;
	}
	
	return pCodecSupportName;
}

/** @} */ //end of ctc-mediacodec