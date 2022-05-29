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
#include "ITs-capi-mediamuxer-common.h"

/** @addtogroup itc-mediamuxer
*  @ingroup itc
*  @{
*/
unsigned char sps[100];
unsigned char pps[100];
unsigned char tmp_buf[1000000];
static int sps_len, pps_len;


//Add helper function definitions here

/**
* @function 		MediamuxerGetState
* @description	 	Maps mediamuxer_state_e enums
* @parameter		state : state level
* @return 			state level string
*/
char* MediamuxerGetState(mediamuxer_state_e state)
{
	char *szStateVal = NULL;
	switch ( state )
	{
	case MEDIAMUXER_STATE_NONE:				szStateVal = "MEDIAMUXER_STATE_NONE";			break;
	case MEDIAMUXER_STATE_IDLE:				szStateVal = "MEDIAMUXER_STATE_IDLE";			break;
	case MEDIAMUXER_STATE_READY:			szStateVal = "MEDIAMUXER_STATE_READY";			break;
	case MEDIAMUXER_STATE_MUXING:			szStateVal = "MEDIAMUXER_STATE_MUXING";			break;
	case MEDIAMUXER_STATE_PAUSED:			szStateVal = "MEDIAMUXER_STATE_PAUSED";			break;
	}
	return szStateVal;
}

/**
* @function 		MediamuxerGetError
* @description	 	Maps mediamuxer_error_e enums
* @parameter		error : error level
* @return 			error string
*/
char* MediamuxerGetError(mediamuxer_error_e error)
{
	char *szErrorVal = NULL;
	switch ( error )
	{
	case MEDIAMUXER_ERROR_NONE:						szErrorVal = "MEDIAMUXER_ERROR_NONE";					break;
	case MEDIAMUXER_ERROR_OUT_OF_MEMORY:			szErrorVal = "MEDIAMUXER_ERROR_OUT_OF_MEMORY";			break;
	case MEDIAMUXER_ERROR_INVALID_PARAMETER:		szErrorVal = "MEDIAMUXER_ERROR_INVALID_PARAMETER";		break;
	case MEDIAMUXER_ERROR_INVALID_OPERATION:		szErrorVal = "MEDIAMUXER_ERROR_INVALID_OPERATION";		break;
	case MEDIAMUXER_ERROR_NOT_SUPPORTED:			szErrorVal = "MEDIAMUXER_ERROR_NOT_SUPPORTED";			break;
	case MEDIAMUXER_ERROR_PERMISSION_DENIED:		szErrorVal = "MEDIAMUXER_ERROR_PERMISSION_DENIED";		break;
	case MEDIAMUXER_ERROR_INVALID_STATE:			szErrorVal = "MEDIAMUXER_ERROR_INVALID_STATE";			break;
	case MEDIAMUXER_ERROR_INVALID_PATH:				szErrorVal = "MEDIAMUXER_ERROR_INVALID_PATH";			break;
	case MEDIAMUXER_ERROR_RESOURCE_LIMIT:			szErrorVal = "MEDIAMUXER_ERROR_RESOURCE_LIMIT";			break;
	default:										szErrorVal = "Unknown Error";							break;
	}

	return szErrorVal;
}

/**
* @function 		MediamuxerGetFormat
* @description	 	Maps mediamuxer_output_format_e enums
* @parameter		state : state level
* @return 			state level string
*/
char* MediamuxerGetFormat(mediamuxer_output_format_e format)
{
	char *szFormatVal = NULL;
	switch ( format )
	{
	case MEDIAMUXER_CONTAINER_FORMAT_MP4:				szFormatVal = "MEDIAMUXER_CONTAINER_FORMAT_MP4";				break;
	}
	return szFormatVal;
}

/**
* @function		MediamuxerExtractNal
* @description		Obtain 1 frame(1 Nal) size in video encoded file.
* @parameter		fd : Read file fd
*			nal : buffer pointer
* @return		nal size
*/
int MediamuxerExtractNal(FILE *fd, unsigned char* nal)
{
	int nal_length = 0;
	size_t result;
	int read_size = 1;
	unsigned char buffer[1000];
	unsigned char val, zero_count, i;
	int nal_unit_type = 0;
	int init;

	zero_count = 0;
	if (feof(fd))
		return -1;

	result = fread(buffer, 1, read_size, fd);

	if(result != read_size)
		return -1;

	val = buffer[0];
	while (!val) {
		if ((zero_count == 2 || zero_count == 3) && val == 1) {
			break;
		}
		zero_count++;
		result = fread(buffer, 1, read_size, fd);

		if(result != read_size)	{
			break;
		}
		val = buffer[0];
	}
	nal[nal_length++] = 0;
	nal[nal_length++] = 0;
	nal[nal_length++] = 0;
	nal[nal_length++] = 1;
	zero_count = 0;
	init = 1;
	while (1) {
		if (feof(fd))
			return nal_length;

		result = fread(buffer, 1, read_size, fd);
		if(result != read_size)
			break;

		val = buffer[0];

		if(init) {
			nal_unit_type = val & 0xf;
			init = 0;
		}
		if (!val)
			zero_count++;
		else {
			if ((zero_count == 2 || zero_count == 3 || zero_count == 4) && (val == 1)) {
				break;
			}
			else {
				for (i = 0; i<zero_count; i++) {
					nal[nal_length++] = 0;
				}
				nal[nal_length++] = val;
				zero_count = 0;
			}
		}
	}

	if(fseek(fd, -(zero_count + 1), SEEK_CUR) != 0)
	{
		return -1;
	}

	if (nal_unit_type == 0x7) {
		sps_len = nal_length;
		memcpy(sps, nal, nal_length);
		return -2;
	} else if (nal_unit_type == 0x8) {
		pps_len = nal_length;
		memcpy(pps, nal, nal_length);
		return -2;
	} else if (nal_unit_type == 0x5) {
		memcpy(tmp_buf, nal, nal_length);
		memcpy(nal, sps, sps_len);
		memcpy(nal + sps_len, pps, pps_len);
		memcpy(nal + sps_len + pps_len, tmp_buf, nal_length);
		nal_length += sps_len + pps_len;
	}

	return nal_length;
}

/** @} */
