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
#ifndef __TCT_IMAGE-UTIL-NATIVE_H__
#define __TCT_IMAGE-UTIL-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_image_util_startup(void);
extern void ITs_image_util_cleanup(void);
extern void ITs_image_util_image_startup(void);
extern void ITs_image_util_image_cleanup(void);
extern void ITs_image_util_agif_encode_startup(void);
extern void ITs_image_util_agif_encode_cleanup(void);
extern void ITs_image_util_anim_encode_startup(void);
extern void ITs_image_util_anim_encode_cleanup(void);

extern int ITc_image_util_transform_create_destroy_p(void);
extern int ITc_image_util_transform_set_get_colorspace_p(void);
extern int ITc_image_util_transform_set_get_crop_area_p(void);
extern int ITc_image_util_transform_set_get_resolution_p(void);
extern int ITc_image_util_transform_set_get_rotation_p(void);
extern int ITc_image_util_transform_run_p(void);
extern int ITc_image_util_extract_color_from_memory_p(void);
extern int ITc_image_util_decode_create_destroy_p(void);
extern int ITc_image_util_decode_set_input_path_p(void);
extern int ITc_image_util_decode_set_input_buffer_p(void);
extern int ITc_image_util_encode_create_destroy_p(void);
extern int ITc_image_util_encode_set_png_compression_p(void);
extern int ITc_image_util_encode_set_webp_lossless_p(void);
extern int ITc_image_util_decode_run2_p(void);
extern int ITc_image_util_decode_run_async2_p(void);
extern int ITc_image_util_foreach_supported_colorspace_p(void);
extern int ITc_image_util_decode_set_colorspace_jpeg_p(void);
extern int ITc_image_util_decode_set_colorspace_png_p(void);
extern int ITc_image_util_decode_set_colorspace_gif_p(void);
extern int ITc_image_util_decode_set_colorspace_bmp_p(void);
extern int ITc_image_util_decode_set_jpeg_downscale_p(void);
extern int ITc_image_util_encode_set_quality_p(void);
extern int ITc_image_util_create_destroy_image_p(void);
extern int ITc_image_util_clone_image_p(void);
extern int ITc_image_util_get_image_p(void);
extern int ITc_image_util_transform_run2_p(void);
extern int ITc_image_util_transform_run2_async_p(void);
extern int ITc_image_util_encode_run_to_file_p(void);
extern int ITc_image_util_encode_run_to_buffer_p(void);
extern int ITc_image_util_encode_run_async_to_file_p(void);
extern int ITc_image_util_encode_run_async_to_buffer_p(void);
extern int ITc_image_util_agif_encode_create_destroy_p(void);
extern int ITc_image_util_agif_encode_add_frame_p(void);
extern int ITc_image_util_agif_encode_save_to_file_p(void);
extern int ITc_image_util_agif_encode_save_to_buffer_p(void);
extern int ITc_image_util_anim_encode_create_destroy_p(void);
extern int ITc_image_util_anim_encode_set_loop_count_p(void);
extern int ITc_image_util_anim_encode_set_background_color_p(void);
extern int ITc_image_util_anim_encode_set_lossless_p(void);
extern int ITc_image_util_anim_encode_add_frame_p(void);
extern int ITc_image_util_anim_encode_save_to_file_p(void);
extern int ITc_image_util_anim_encode_save_to_buffer_p(void);
extern int ITc_image_util_decode_set_colorspace_heif_p(void);

testcase tc_array[] = {
	{"ITc_image_util_transform_create_destroy_p",ITc_image_util_transform_create_destroy_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_transform_set_get_colorspace_p",ITc_image_util_transform_set_get_colorspace_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_transform_set_get_crop_area_p",ITc_image_util_transform_set_get_crop_area_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_transform_set_get_resolution_p",ITc_image_util_transform_set_get_resolution_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_transform_set_get_rotation_p",ITc_image_util_transform_set_get_rotation_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_transform_run_p",ITc_image_util_transform_run_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_extract_color_from_memory_p",ITc_image_util_extract_color_from_memory_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_decode_create_destroy_p",ITc_image_util_decode_create_destroy_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_decode_set_input_path_p",ITc_image_util_decode_set_input_path_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_decode_set_input_buffer_p",ITc_image_util_decode_set_input_buffer_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_encode_create_destroy_p",ITc_image_util_encode_create_destroy_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_encode_set_png_compression_p",ITc_image_util_encode_set_png_compression_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_encode_set_webp_lossless_p",ITc_image_util_encode_set_webp_lossless_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_decode_run2_p",ITc_image_util_decode_run2_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_decode_run_async2_p",ITc_image_util_decode_run_async2_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_foreach_supported_colorspace_p",ITc_image_util_foreach_supported_colorspace_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_decode_set_colorspace_jpeg_p",ITc_image_util_decode_set_colorspace_jpeg_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_decode_set_colorspace_png_p",ITc_image_util_decode_set_colorspace_png_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_decode_set_colorspace_gif_p",ITc_image_util_decode_set_colorspace_gif_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_decode_set_colorspace_bmp_p",ITc_image_util_decode_set_colorspace_bmp_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_decode_set_colorspace_heif_p",ITc_image_util_decode_set_colorspace_heif_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_decode_set_jpeg_downscale_p",ITc_image_util_decode_set_jpeg_downscale_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_encode_set_quality_p",ITc_image_util_encode_set_quality_p,ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_create_destroy_image_p",ITc_image_util_create_destroy_image_p,ITs_image_util_image_startup,ITs_image_util_image_cleanup},
	{"ITc_image_util_clone_image_p",ITc_image_util_clone_image_p,ITs_image_util_image_startup,ITs_image_util_image_cleanup},
	{"ITc_image_util_get_image_p",ITc_image_util_get_image_p,ITs_image_util_image_startup,ITs_image_util_image_cleanup},
	{"ITc_image_util_transform_run2_p",ITc_image_util_transform_run2_p,ITs_image_util_image_startup,ITs_image_util_image_cleanup},
	{"ITc_image_util_transform_run2_async_p",ITc_image_util_transform_run2_async_p,ITs_image_util_image_startup,ITs_image_util_image_cleanup},
	{"ITc_image_util_encode_run_to_file_p", ITc_image_util_encode_run_to_file_p, ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_encode_run_to_buffer_p", ITc_image_util_encode_run_to_buffer_p, ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_encode_run_async_to_file_p", ITc_image_util_encode_run_async_to_file_p, ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_encode_run_async_to_buffer_p", ITc_image_util_encode_run_async_to_buffer_p, ITs_image_util_startup,ITs_image_util_cleanup},
	{"ITc_image_util_agif_encode_create_destroy_p", ITc_image_util_agif_encode_create_destroy_p, ITs_image_util_agif_encode_startup, ITs_image_util_agif_encode_cleanup},
	{"ITc_image_util_agif_encode_add_frame_p", ITc_image_util_agif_encode_add_frame_p, ITs_image_util_agif_encode_startup, ITs_image_util_agif_encode_cleanup},
	{"ITc_image_util_agif_encode_save_to_file_p", ITc_image_util_agif_encode_save_to_file_p, ITs_image_util_agif_encode_startup, ITs_image_util_agif_encode_cleanup},
	{"ITc_image_util_agif_encode_save_to_buffer_p", ITc_image_util_agif_encode_save_to_buffer_p, ITs_image_util_agif_encode_startup, ITs_image_util_agif_encode_cleanup},
	{"ITc_image_util_anim_encode_create_destroy_p", ITc_image_util_anim_encode_create_destroy_p, ITs_image_util_anim_encode_startup, ITs_image_util_anim_encode_cleanup},
	{"ITc_image_util_anim_encode_set_loop_count_p", ITc_image_util_anim_encode_set_loop_count_p, ITs_image_util_anim_encode_startup, ITs_image_util_anim_encode_cleanup},
	{"ITc_image_util_anim_encode_set_background_color_p", ITc_image_util_anim_encode_set_background_color_p, ITs_image_util_anim_encode_startup, ITs_image_util_anim_encode_cleanup},
	{"ITc_image_util_anim_encode_set_lossless_p", ITc_image_util_anim_encode_set_lossless_p, ITs_image_util_anim_encode_startup, ITs_image_util_anim_encode_cleanup},
	{"ITc_image_util_anim_encode_add_frame_p", ITc_image_util_anim_encode_add_frame_p, ITs_image_util_anim_encode_startup, ITs_image_util_anim_encode_cleanup},
	{"ITc_image_util_anim_encode_save_to_file_p", ITc_image_util_anim_encode_save_to_file_p, ITs_image_util_anim_encode_startup, ITs_image_util_anim_encode_cleanup},
	{"ITc_image_util_anim_encode_save_to_buffer_p", ITc_image_util_anim_encode_save_to_buffer_p, ITs_image_util_anim_encode_startup, ITs_image_util_anim_encode_cleanup},
	{NULL, NULL}
};

#endif // __TCT_IMAGE-UTIL-NATIVE_H__
