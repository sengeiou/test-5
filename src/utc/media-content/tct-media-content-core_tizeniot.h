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
#ifndef __TCT_MEDIA-CONTENT-NATIVE_H__
#define __TCT_MEDIA-CONTENT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_media_audio_startup(void);
extern void utc_media_audio_cleanup(void);
extern void utc_media_bookmark_delete_startup(void);
extern void utc_media_bookmark_delete_cleanup(void);
extern void utc_media_bookmark_insert_startup(void);
extern void utc_media_bookmark_insert_cleanup(void);
extern void utc_media_bookmark_startup(void);
extern void utc_media_bookmark_cleanup(void);
extern void utc_media_book_startup(void);
extern void utc_media_book_cleanup(void);
extern void utc_media_content_startup(void);
extern void utc_media_content_cleanup(void);
extern void utc_media_face_startup(void);
extern void utc_media_face_cleanup(void);
extern void utc_media_filter_create_cleanup(void);
extern void utc_media_filter_destroy_startup(void);
extern void utc_media_filter_destroy_cleanup(void);
extern void utc_media_filter_startup(void);
extern void utc_media_filter_cleanup(void);
extern void utc_media_folder_startup(void);
extern void utc_media_folder_cleanup(void);
extern void utc_media_group_startup(void);
extern void utc_media_group_cleanup(void);
extern void utc_media_image_startup(void);
extern void utc_media_image_cleanup(void);
extern void utc_media_info_startup(void);
extern void utc_media_info_cleanup(void);
extern void utc_media_playlist_startup(void);
extern void utc_media_playlist_cleanup(void);
extern void utc_media_storage_startup(void);
extern void utc_media_storage_cleanup(void);
extern void utc_media_tag_startup(void);
extern void utc_media_tag_cleanup(void);
extern void utc_media_video_startup(void);
extern void utc_media_video_cleanup(void);

extern int utc_media_audio_meta_destroy_n(void);
extern int utc_media_audio_meta_destroy_p(void);
extern int utc_media_audio_meta_clone_n(void);
extern int utc_media_audio_meta_clone_p(void);
extern int utc_media_audio_meta_get_media_id_n(void);
extern int utc_media_audio_meta_get_media_id_p(void);
extern int utc_media_audio_meta_get_album_n(void);
extern int utc_media_audio_meta_get_album_p(void);
extern int utc_media_audio_meta_get_artist_n(void);
extern int utc_media_audio_meta_get_artist_p(void);
extern int utc_media_audio_meta_get_album_artist_n(void);
extern int utc_media_audio_meta_get_album_artist_p(void);
extern int utc_media_audio_meta_get_genre_n(void);
extern int utc_media_audio_meta_get_genre_p(void);
extern int utc_media_audio_meta_get_composer_n(void);
extern int utc_media_audio_meta_get_composer_p(void);
extern int utc_media_audio_meta_get_year_n(void);
extern int utc_media_audio_meta_get_year_p(void);
extern int utc_media_audio_meta_get_recorded_date_n(void);
extern int utc_media_audio_meta_get_recorded_date_p(void);
extern int utc_media_audio_meta_get_copyright_n(void);
extern int utc_media_audio_meta_get_copyright_p(void);
extern int utc_media_audio_meta_get_track_num_n(void);
extern int utc_media_audio_meta_get_track_num_p(void);
extern int utc_media_audio_meta_get_bit_rate_n(void);
extern int utc_media_audio_meta_get_bit_rate_p(void);
extern int utc_media_audio_meta_get_sample_rate_n(void);
extern int utc_media_audio_meta_get_sample_rate_p(void);
extern int utc_media_audio_meta_get_channel_n(void);
extern int utc_media_audio_meta_get_channel_p(void);
extern int utc_media_audio_meta_get_duration_n(void);
extern int utc_media_audio_meta_get_duration_p(void);
extern int utc_media_audio_meta_get_bitpersample_n(void);
extern int utc_media_audio_meta_get_bitpersample_p(void);
extern int utc_media_book_meta_clone_n(void);
extern int utc_media_book_meta_clone_p(void);
extern int utc_media_book_meta_destroy_n(void);
extern int utc_media_book_meta_destroy_p(void);
extern int utc_media_book_meta_get_media_id_n(void);
extern int utc_media_book_meta_get_media_id_p(void);
extern int utc_media_book_meta_get_subject_n(void);
extern int utc_media_book_meta_get_subject_p(void);
extern int utc_media_book_meta_get_author_n(void);
extern int utc_media_book_meta_get_author_p(void);
extern int utc_media_book_meta_get_date_n(void);
extern int utc_media_book_meta_get_date_p(void);
extern int utc_media_book_meta_get_publisher_n(void);
extern int utc_media_book_meta_get_publisher_p(void);
extern int utc_media_book_meta_get_path_with_keyword_n(void);
extern int utc_media_book_meta_get_path_with_keyword_p(void);
extern int utc_media_bookmark_delete_from_db_n(void);
extern int utc_media_bookmark_delete_from_db_p(void);
extern int utc_media_bookmark_insert_to_db_n(void);
extern int utc_media_bookmark_insert_to_db_p(void);
extern int utc_media_bookmark_get_bookmark_count_from_db_n(void);
extern int utc_media_bookmark_get_bookmark_count_from_db_p(void);
extern int utc_media_bookmark_foreach_bookmark_from_db_n(void);
extern int utc_media_bookmark_foreach_bookmark_from_db_p(void);
extern int utc_media_bookmark_clone_n(void);
extern int utc_media_bookmark_clone_p(void);
extern int utc_media_bookmark_destroy_n(void);
extern int utc_media_bookmark_destroy_p(void);
extern int utc_media_bookmark_get_bookmark_id_n(void);
extern int utc_media_bookmark_get_bookmark_id_p(void);
extern int utc_media_bookmark_get_marked_time_n(void);
extern int utc_media_bookmark_get_marked_time_p(void);
extern int utc_media_bookmark_get_thumbnail_path_n(void);
extern int utc_media_bookmark_get_thumbnail_path_p(void);
extern int utc_media_bookmark_get_name_n(void);
extern int utc_media_bookmark_get_name_p(void);
extern int utc_media_bookmark_set_name_n(void);
extern int utc_media_bookmark_set_name_p(void);
extern int utc_media_bookmark_update_to_db_n(void);
extern int utc_media_bookmark_update_to_db_p(void);
extern int utc_media_content_connect_p(void);
extern int utc_media_content_connect_n(void);
extern int utc_media_content_disconnect_p(void);
extern int utc_media_content_disconnect_n(void);
extern int utc_media_content_scan_file_n(void);
extern int utc_media_content_scan_file_p(void);
extern int utc_media_content_scan_folder_n(void);
extern int utc_media_content_scan_folder_p(void);
extern int utc_media_content_cancel_scan_folder_n(void);
extern int utc_media_content_cancel_scan_folder_p(void);
extern int utc_media_content_add_db_updated_cb_n(void);
extern int utc_media_content_add_db_updated_cb_p(void);
extern int utc_media_content_remove_db_updated_cb_n(void);
extern int utc_media_content_remove_db_updated_cb_p(void);
extern int utc_media_face_clone_p(void);
extern int utc_media_face_clone_n(void);
extern int utc_media_face_destroy_p(void);
extern int utc_media_face_destroy_n(void);
extern int utc_media_face_get_face_id_p(void);
extern int utc_media_face_get_face_id_n(void);
extern int utc_media_face_get_media_id_p(void);
extern int utc_media_face_get_media_id_n(void);
extern int utc_media_face_get_face_rect_p(void);
extern int utc_media_face_get_face_rect_n(void);
extern int utc_media_face_get_orientation_p(void);
extern int utc_media_face_get_orientation_n(void);
extern int utc_media_face_get_tag_p(void);
extern int utc_media_face_get_tag_n(void);
extern int utc_media_face_create_p(void);
extern int utc_media_face_create_n(void);
extern int utc_media_face_set_face_rect_p(void);
extern int utc_media_face_set_face_rect_n(void);
extern int utc_media_face_set_orientation_p(void);
extern int utc_media_face_set_orientation_n(void);
extern int utc_media_face_set_tag_p(void);
extern int utc_media_face_set_tag_n(void);
extern int utc_media_face_insert_to_db_p(void);
extern int utc_media_face_insert_to_db_n(void);
extern int utc_media_face_update_to_db_p(void);
extern int utc_media_face_update_to_db_n(void);
extern int utc_media_face_delete_from_db_p(void);
extern int utc_media_face_delete_from_db_n(void);
extern int utc_media_face_get_face_count_from_db_p(void);
extern int utc_media_face_get_face_count_from_db_n(void);
extern int utc_media_face_foreach_face_from_db_p(void);
extern int utc_media_face_foreach_face_from_db_n(void);
extern int utc_media_filter_create_n(void);
extern int utc_media_filter_create_p(void);
extern int utc_media_filter_destroy_n(void);
extern int utc_media_filter_destroy_p(void);
extern int utc_media_filter_set_offset_n(void);
extern int utc_media_filter_set_offset_p(void);
extern int utc_media_filter_set_condition_n(void);
extern int utc_media_filter_set_condition_p(void);
extern int utc_media_filter_set_order_n(void);
extern int utc_media_filter_set_order_p(void);
extern int utc_media_filter_set_storage_n(void);
extern int utc_media_filter_set_storage_p(void);
extern int utc_media_filter_get_offset_n(void);
extern int utc_media_filter_get_offset_p(void);
extern int utc_media_filter_get_condition_n(void);
extern int utc_media_filter_get_condition_p(void);
extern int utc_media_filter_get_order_n(void);
extern int utc_media_filter_get_order_p(void);
extern int utc_media_filter_get_storage_n(void);
extern int utc_media_filter_get_storage_p(void);
extern int utc_media_folder_foreach_folder_from_db_n(void);
extern int utc_media_folder_foreach_folder_from_db_p(void);
extern int utc_media_folder_get_media_count_from_db_n(void);
extern int utc_media_folder_get_media_count_from_db_p(void);
extern int utc_media_folder_foreach_media_from_db_n(void);
extern int utc_media_folder_foreach_media_from_db_p(void);
extern int utc_media_folder_clone_n(void);
extern int utc_media_folder_clone_p(void);
extern int utc_media_folder_get_path_n(void);
extern int utc_media_folder_get_path_p(void);
extern int utc_media_folder_get_name_n(void);
extern int utc_media_folder_get_name_p(void);
extern int utc_media_folder_get_storage_type_n(void);
extern int utc_media_folder_get_storage_type_p(void);
extern int utc_media_folder_get_storage_id_n(void);
extern int utc_media_folder_get_storage_id_p(void);
extern int utc_media_folder_get_folder_id_n(void);
extern int utc_media_folder_get_folder_id_p(void);
extern int utc_media_folder_get_folder_from_db_n(void);
extern int utc_media_folder_get_folder_from_db_p(void);
extern int utc_media_folder_get_folder_count_from_db_n(void);
extern int utc_media_folder_get_folder_count_from_db_p(void);
extern int utc_media_folder_destroy_n(void);
extern int utc_media_folder_destroy_p(void);
extern int utc_media_album_get_album_count_from_db_n(void);
extern int utc_media_album_get_album_count_from_db_p(void);
extern int utc_media_album_foreach_album_from_db_n(void);
extern int utc_media_album_foreach_album_from_db_p(void);
extern int utc_media_album_get_media_count_from_db_n(void);
extern int utc_media_album_get_media_count_from_db_p(void);
extern int utc_media_album_foreach_media_from_db_n(void);
extern int utc_media_album_foreach_media_from_db_p(void);
extern int utc_media_album_get_album_from_db_n(void);
extern int utc_media_album_get_album_from_db_p(void);
extern int utc_media_album_get_album_id_n(void);
extern int utc_media_album_get_album_id_p(void);
extern int utc_media_album_get_name_n(void);
extern int utc_media_album_get_name_p(void);
extern int utc_media_album_get_artist_n(void);
extern int utc_media_album_get_artist_p(void);
extern int utc_media_album_get_album_art_n(void);
extern int utc_media_album_get_album_art_p(void);
extern int utc_media_album_clone_n(void);
extern int utc_media_album_clone_p(void);
extern int utc_media_album_destroy_n(void);
extern int utc_media_album_destroy_p(void);
extern int utc_media_group_get_group_count_from_db_n(void);
extern int utc_media_group_get_group_count_from_db_p(void);
extern int utc_media_group_get_media_count_from_db_n(void);
extern int utc_media_group_get_media_count_from_db_p(void);
extern int utc_media_group_foreach_group_from_db_n(void);
extern int utc_media_group_foreach_group_from_db_p(void);
extern int utc_media_group_foreach_media_from_db_n(void);
extern int utc_media_group_foreach_media_from_db_p(void);
extern int utc_image_meta_destroy_n(void);
extern int utc_image_meta_destroy_p(void);
extern int utc_image_meta_clone_n(void);
extern int utc_image_meta_clone_p(void);
extern int utc_image_meta_get_media_id_n(void);
extern int utc_image_meta_get_media_id_p(void);
extern int utc_image_meta_get_width_n(void);
extern int utc_image_meta_get_width_p(void);
extern int utc_image_meta_get_height_n(void);
extern int utc_image_meta_get_height_p(void);
extern int utc_image_meta_get_orientation_n(void);
extern int utc_image_meta_get_orientation_p(void);
extern int utc_image_meta_get_date_taken_n(void);
extern int utc_image_meta_get_date_taken_p(void);
extern int utc_image_meta_get_exposure_time_n(void);
extern int utc_image_meta_get_exposure_time_p(void);
extern int utc_image_meta_get_fnumber_n(void);
extern int utc_image_meta_get_fnumber_p(void);
extern int utc_image_meta_get_iso_n(void);
extern int utc_image_meta_get_iso_p(void);
extern int utc_image_meta_get_model_n(void);
extern int utc_image_meta_get_model_p(void);
extern int utc_media_info_insert_to_db_n(void);
extern int utc_media_info_insert_to_db_p(void);
extern int utc_media_info_insert_batch_to_db_n(void);
extern int utc_media_info_insert_batch_to_db_p(void);
extern int utc_media_info_set_favorite_n(void);
extern int utc_media_info_set_favorite_p(void);
extern int utc_media_info_update_to_db_n(void);
extern int utc_media_info_update_to_db_p(void);
extern int utc_media_info_create_thumbnail_n(void);
extern int utc_media_info_create_thumbnail_p(void);
extern int utc_media_info_start_face_detection_n(void);
extern int utc_media_info_start_face_detection_p(void);
extern int utc_media_info_move_to_db_n(void);
extern int utc_media_info_move_to_db_p(void);
extern int utc_media_info_delete_from_db_n(void);
extern int utc_media_info_delete_from_db_p(void);
extern int utc_media_info_foreach_media_from_db_n(void);
extern int utc_media_info_foreach_media_from_db_p(void);
extern int utc_media_info_destroy_n(void);
extern int utc_media_info_destroy_p(void);
extern int utc_media_info_clone_n(void);
extern int utc_media_info_clone_p(void);
extern int utc_media_info_get_media_id_n(void);
extern int utc_media_info_get_media_id_p(void);
extern int utc_media_info_get_file_path_n(void);
extern int utc_media_info_get_file_path_p(void);
extern int utc_media_info_get_display_name_n(void);
extern int utc_media_info_get_display_name_p(void);
extern int utc_media_info_get_media_type_n(void);
extern int utc_media_info_get_media_type_p(void);
extern int utc_media_info_get_mime_type_n(void);
extern int utc_media_info_get_mime_type_p(void);
extern int utc_media_info_get_thumbnail_path_n(void);
extern int utc_media_info_get_thumbnail_path_p(void);
extern int utc_media_info_get_modified_time_n(void);
extern int utc_media_info_get_modified_time_p(void);
extern int utc_media_info_get_size_n(void);
extern int utc_media_info_get_size_p(void);
extern int utc_media_info_get_storage_type_n(void);
extern int utc_media_info_get_storage_type_p(void);
extern int utc_media_info_get_storage_id_n(void);
extern int utc_media_info_get_storage_id_p(void);
extern int utc_media_info_is_drm_n(void);
extern int utc_media_info_is_drm_p(void);
extern int utc_media_info_get_altitude_n(void);
extern int utc_media_info_get_altitude_p(void);
extern int utc_media_info_get_latitude_n(void);
extern int utc_media_info_get_latitude_p(void);
extern int utc_media_info_get_longitude_n(void);
extern int utc_media_info_get_longitude_p(void);
extern int utc_media_info_get_description_n(void);
extern int utc_media_info_get_description_p(void);
extern int utc_media_info_get_rating_n(void);
extern int utc_media_info_get_rating_p(void);
extern int utc_media_info_get_added_time_n(void);
extern int utc_media_info_get_added_time_p(void);
extern int utc_media_info_get_favorite_n(void);
extern int utc_media_info_get_favorite_p(void);
extern int utc_media_info_get_media_from_db_n(void);
extern int utc_media_info_get_media_from_db_p(void);
extern int utc_media_info_get_media_from_db_by_path_n(void);
extern int utc_media_info_get_media_from_db_by_path_p(void);
extern int utc_media_info_get_image_n(void);
extern int utc_media_info_get_image_p(void);
extern int utc_media_info_get_video_n(void);
extern int utc_media_info_get_video_p(void);
extern int utc_media_info_get_audio_n(void);
extern int utc_media_info_get_audio_p(void);
extern int utc_media_info_get_book_n(void);
extern int utc_media_info_get_book_p(void);
extern int utc_media_info_foreach_tag_from_db_n(void);
extern int utc_media_info_foreach_tag_from_db_p(void);
extern int utc_media_info_foreach_bookmark_from_db_n(void);
extern int utc_media_info_foreach_bookmark_from_db_p(void);
extern int utc_media_info_get_bookmark_count_from_db_n(void);
extern int utc_media_info_get_bookmark_count_from_db_p(void);
extern int utc_media_info_get_media_count_from_db_n(void);
extern int utc_media_info_get_media_count_from_db_p(void);
extern int utc_media_info_get_tag_count_from_db_n(void);
extern int utc_media_info_get_tag_count_from_db_p(void);
extern int utc_media_info_get_timeline_n(void);
extern int utc_media_info_get_timeline_p(void);
extern int utc_media_info_get_title_n(void);
extern int utc_media_info_get_title_p(void);
extern int utc_media_info_is_360_content_n(void);
extern int utc_media_info_is_360_content_p(void);
extern int utc_media_info_cancel_thumbnail_n(void);
extern int utc_media_info_cancel_thumbnail_p(void);
extern int utc_media_info_cancel_face_detection_n(void);
extern int utc_media_info_cancel_face_detection_p(void);
extern int utc_media_info_get_face_count_from_db_n(void);
extern int utc_media_info_get_face_count_from_db_p(void);
extern int utc_media_info_foreach_face_from_db_n(void);
extern int utc_media_info_foreach_face_from_db_p(void);
extern int utc_media_info_generate_thumbnail_n(void);
extern int utc_media_info_generate_thumbnail_p(void);
extern int utc_media_playlist_insert_to_db_n(void);
extern int utc_media_playlist_insert_to_db_p(void);
extern int utc_media_playlist_delete_from_db_n(void);
extern int utc_media_playlist_delete_from_db_p(void);
extern int utc_media_playlist_get_playlist_count_from_db_n(void);
extern int utc_media_playlist_get_playlist_count_from_db_p(void);
extern int utc_media_playlist_foreach_playlist_from_db_n(void);
extern int utc_media_playlist_foreach_playlist_from_db_p(void);
extern int utc_media_playlist_get_media_count_from_db_n(void);
extern int utc_media_playlist_get_media_count_from_db_p(void);
extern int utc_media_playlist_foreach_media_from_db_n(void);
extern int utc_media_playlist_foreach_media_from_db_p(void);
extern int utc_media_playlist_destroy_n(void);
extern int utc_media_playlist_destroy_p(void);
extern int utc_media_playlist_clone_n(void);
extern int utc_media_playlist_clone_p(void);
extern int utc_media_playlist_get_playlist_from_db_n(void);
extern int utc_media_playlist_get_playlist_from_db_p(void);
extern int utc_media_playlist_get_playlist_id_n(void);
extern int utc_media_playlist_get_playlist_id_p(void);
extern int utc_media_playlist_get_name_n(void);
extern int utc_media_playlist_get_name_p(void);
extern int utc_media_playlist_get_play_order_n(void);
extern int utc_media_playlist_get_play_order_p(void);
extern int utc_media_playlist_update_to_db_n(void);
extern int utc_media_playlist_update_to_db_p(void);
extern int utc_media_playlist_set_name_n(void);
extern int utc_media_playlist_set_name_p(void);
extern int utc_media_playlist_add_media_n(void);
extern int utc_media_playlist_add_media_p(void);
extern int utc_media_playlist_set_play_order_n(void);
extern int utc_media_playlist_set_play_order_p(void);
extern int utc_media_playlist_remove_media_n(void);
extern int utc_media_playlist_remove_media_p(void);
extern int utc_media_playlist_get_thumbnail_path_n(void);
extern int utc_media_playlist_get_thumbnail_path_p(void);
extern int utc_media_playlist_set_thumbnail_path_n(void);
extern int utc_media_playlist_set_thumbnail_path_p(void);
extern int utc_media_playlist_import_from_file_n(void);
extern int utc_media_playlist_import_from_file_p(void);
extern int utc_media_playlist_export_to_file_n(void);
extern int utc_media_playlist_export_to_file_p(void);
extern int utc_media_storage_get_storage_info_from_db_n(void);
extern int utc_media_storage_get_storage_info_from_db_p(void);
extern int utc_media_storage_get_storage_count_from_db_n(void);
extern int utc_media_storage_get_storage_count_from_db_p(void);
extern int utc_media_storage_foreach_storage_from_db_n(void);
extern int utc_media_storage_foreach_storage_from_db_p(void);
extern int utc_media_storage_get_media_count_from_db_n(void);
extern int utc_media_storage_get_media_count_from_db_p(void);
extern int utc_media_storage_foreach_media_from_db_n(void);
extern int utc_media_storage_foreach_media_from_db_p(void);
extern int utc_media_storage_destroy_n(void);
extern int utc_media_storage_destroy_p(void);
extern int utc_media_storage_clone_n(void);
extern int utc_media_storage_clone_p(void);
extern int utc_media_storage_get_id_n(void);
extern int utc_media_storage_get_id_p(void);
extern int utc_media_storage_get_path_n(void);
extern int utc_media_storage_get_path_p(void);
extern int utc_media_storage_get_type_n(void);
extern int utc_media_storage_get_type_p(void);
extern int utc_media_tag_insert_to_db_n(void);
extern int utc_media_tag_insert_to_db_p(void);
extern int utc_media_tag_delete_from_db_n(void);
extern int utc_media_tag_delete_from_db_p(void);
extern int utc_media_tag_get_tag_count_from_db_n(void);
extern int utc_media_tag_get_tag_count_from_db_p(void);
extern int utc_media_tag_foreach_tag_from_db_n(void);
extern int utc_media_tag_foreach_tag_from_db_p(void);
extern int utc_media_tag_get_media_count_from_db_n(void);
extern int utc_media_tag_get_media_count_from_db_p(void);
extern int utc_media_tag_foreach_media_from_db_n(void);
extern int utc_media_tag_foreach_media_from_db_p(void);
extern int utc_media_tag_clone_n(void);
extern int utc_media_tag_clone_p(void);
extern int utc_media_tag_update_to_db_n(void);
extern int utc_media_tag_update_to_db_p(void);
extern int utc_media_tag_add_media_n(void);
extern int utc_media_tag_add_media_p(void);
extern int utc_media_tag_remove_media_n(void);
extern int utc_media_tag_remove_media_p(void);
extern int utc_media_tag_set_name_n(void);
extern int utc_media_tag_set_name_p(void);
extern int utc_media_tag_get_tag_id_n(void);
extern int utc_media_tag_get_tag_id_p(void);
extern int utc_media_tag_get_name_n(void);
extern int utc_media_tag_get_name_p(void);
extern int utc_media_tag_get_tag_from_db_n(void);
extern int utc_media_tag_get_tag_from_db_p(void);
extern int utc_media_tag_destroy_n(void);
extern int utc_media_tag_destroy_p(void);
extern int utc_video_meta_destroy_n(void);
extern int utc_video_meta_destroy_p(void);
extern int utc_video_meta_clone_n(void);
extern int utc_video_meta_clone_p(void);
extern int utc_video_meta_get_media_id_n(void);
extern int utc_video_meta_get_media_id_p(void);
extern int utc_video_meta_get_album_n(void);
extern int utc_video_meta_get_album_p(void);
extern int utc_video_meta_get_artist_n(void);
extern int utc_video_meta_get_artist_p(void);
extern int utc_video_meta_get_album_artist_n(void);
extern int utc_video_meta_get_album_artist_p(void);
extern int utc_video_meta_get_genre_n(void);
extern int utc_video_meta_get_genre_p(void);
extern int utc_video_meta_get_composer_n(void);
extern int utc_video_meta_get_composer_p(void);
extern int utc_video_meta_get_year_n(void);
extern int utc_video_meta_get_year_p(void);
extern int utc_video_meta_get_recorded_date_n(void);
extern int utc_video_meta_get_recorded_date_p(void);
extern int utc_video_meta_get_copyright_n(void);
extern int utc_video_meta_get_copyright_p(void);
extern int utc_video_meta_get_track_num_n(void);
extern int utc_video_meta_get_track_num_p(void);
extern int utc_video_meta_get_bit_rate_n(void);
extern int utc_video_meta_get_bit_rate_p(void);
extern int utc_video_meta_get_duration_n(void);
extern int utc_video_meta_get_duration_p(void);
extern int utc_video_meta_get_width_n(void);
extern int utc_video_meta_get_width_p(void);
extern int utc_video_meta_get_height_n(void);
extern int utc_video_meta_get_height_p(void);
extern int utc_video_meta_get_rotation_n(void);
extern int utc_video_meta_get_rotation_p(void);

testcase tc_array[] = {
	{"utc_media_audio_meta_destroy_n",utc_media_audio_meta_destroy_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_destroy_p",utc_media_audio_meta_destroy_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_clone_n",utc_media_audio_meta_clone_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_clone_p",utc_media_audio_meta_clone_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_media_id_n",utc_media_audio_meta_get_media_id_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_media_id_p",utc_media_audio_meta_get_media_id_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_album_n",utc_media_audio_meta_get_album_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_album_p",utc_media_audio_meta_get_album_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_artist_n",utc_media_audio_meta_get_artist_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_artist_p",utc_media_audio_meta_get_artist_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_album_artist_n",utc_media_audio_meta_get_album_artist_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_album_artist_p",utc_media_audio_meta_get_album_artist_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_genre_n",utc_media_audio_meta_get_genre_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_genre_p",utc_media_audio_meta_get_genre_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_composer_n",utc_media_audio_meta_get_composer_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_composer_p",utc_media_audio_meta_get_composer_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_year_n",utc_media_audio_meta_get_year_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_year_p",utc_media_audio_meta_get_year_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_recorded_date_n",utc_media_audio_meta_get_recorded_date_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_recorded_date_p",utc_media_audio_meta_get_recorded_date_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_copyright_n",utc_media_audio_meta_get_copyright_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_copyright_p",utc_media_audio_meta_get_copyright_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_track_num_n",utc_media_audio_meta_get_track_num_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_track_num_p",utc_media_audio_meta_get_track_num_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_bit_rate_n",utc_media_audio_meta_get_bit_rate_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_bit_rate_p",utc_media_audio_meta_get_bit_rate_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_sample_rate_n",utc_media_audio_meta_get_sample_rate_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_sample_rate_p",utc_media_audio_meta_get_sample_rate_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_channel_n",utc_media_audio_meta_get_channel_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_channel_p",utc_media_audio_meta_get_channel_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_duration_n",utc_media_audio_meta_get_duration_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_duration_p",utc_media_audio_meta_get_duration_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_bitpersample_n",utc_media_audio_meta_get_bitpersample_n,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_audio_meta_get_bitpersample_p",utc_media_audio_meta_get_bitpersample_p,utc_media_audio_startup,utc_media_audio_cleanup},
	{"utc_media_book_meta_clone_n", utc_media_book_meta_clone_n,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_clone_p", utc_media_book_meta_clone_p,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_destroy_n", utc_media_book_meta_destroy_n,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_destroy_p", utc_media_book_meta_destroy_p,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_get_media_id_n", utc_media_book_meta_get_media_id_n,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_get_media_id_p", utc_media_book_meta_get_media_id_p,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_get_subject_n", utc_media_book_meta_get_subject_n,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_get_subject_p", utc_media_book_meta_get_subject_p,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_get_author_n", utc_media_book_meta_get_author_n,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_get_author_p", utc_media_book_meta_get_author_p,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_get_date_n", utc_media_book_meta_get_date_n,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_get_date_p", utc_media_book_meta_get_date_p,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_get_publisher_n", utc_media_book_meta_get_publisher_n,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_get_publisher_p", utc_media_book_meta_get_publisher_p,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_get_path_with_keyword_n", utc_media_book_meta_get_path_with_keyword_n,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_book_meta_get_path_with_keyword_p", utc_media_book_meta_get_path_with_keyword_p,utc_media_book_startup,utc_media_book_cleanup},
	{"utc_media_bookmark_delete_from_db_n",utc_media_bookmark_delete_from_db_n,utc_media_bookmark_delete_startup,utc_media_bookmark_delete_cleanup},
	{"utc_media_bookmark_delete_from_db_p",utc_media_bookmark_delete_from_db_p,utc_media_bookmark_delete_startup,utc_media_bookmark_delete_cleanup},
	{"utc_media_bookmark_insert_to_db_n",utc_media_bookmark_insert_to_db_n,utc_media_bookmark_insert_startup,utc_media_bookmark_insert_cleanup},
	{"utc_media_bookmark_insert_to_db_p",utc_media_bookmark_insert_to_db_p,utc_media_bookmark_insert_startup,utc_media_bookmark_insert_cleanup},
	{"utc_media_bookmark_get_bookmark_count_from_db_n",utc_media_bookmark_get_bookmark_count_from_db_n,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_get_bookmark_count_from_db_p",utc_media_bookmark_get_bookmark_count_from_db_p,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_foreach_bookmark_from_db_n",utc_media_bookmark_foreach_bookmark_from_db_n,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_foreach_bookmark_from_db_p",utc_media_bookmark_foreach_bookmark_from_db_p,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_clone_n",utc_media_bookmark_clone_n,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_clone_p",utc_media_bookmark_clone_p,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_destroy_n",utc_media_bookmark_destroy_n,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_destroy_p",utc_media_bookmark_destroy_p,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_get_bookmark_id_n",utc_media_bookmark_get_bookmark_id_n,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_get_bookmark_id_p",utc_media_bookmark_get_bookmark_id_p,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_get_marked_time_n",utc_media_bookmark_get_marked_time_n,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_get_marked_time_p",utc_media_bookmark_get_marked_time_p,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_get_thumbnail_path_n",utc_media_bookmark_get_thumbnail_path_n,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_get_thumbnail_path_p",utc_media_bookmark_get_thumbnail_path_p,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_get_name_n",utc_media_bookmark_get_name_n,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_get_name_p",utc_media_bookmark_get_name_p,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_set_name_n",utc_media_bookmark_set_name_n,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_set_name_p",utc_media_bookmark_set_name_p,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_update_to_db_n",utc_media_bookmark_update_to_db_n,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_bookmark_update_to_db_p",utc_media_bookmark_update_to_db_p,utc_media_bookmark_startup,utc_media_bookmark_cleanup},
	{"utc_media_content_connect_p",utc_media_content_connect_p,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_connect_n",utc_media_content_connect_n,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_disconnect_p",utc_media_content_disconnect_p,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_disconnect_n",utc_media_content_disconnect_n,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_scan_file_n",utc_media_content_scan_file_n,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_scan_file_p",utc_media_content_scan_file_p,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_scan_folder_n",utc_media_content_scan_folder_n,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_scan_folder_p",utc_media_content_scan_folder_p,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_cancel_scan_folder_n",utc_media_content_cancel_scan_folder_n,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_cancel_scan_folder_p",utc_media_content_cancel_scan_folder_p,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_add_db_updated_cb_n",utc_media_content_add_db_updated_cb_n,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_add_db_updated_cb_p",utc_media_content_add_db_updated_cb_p,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_remove_db_updated_cb_n",utc_media_content_remove_db_updated_cb_n,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_content_remove_db_updated_cb_p",utc_media_content_remove_db_updated_cb_p,utc_media_content_startup,utc_media_content_cleanup},
	{"utc_media_face_clone_p",utc_media_face_clone_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_clone_n",utc_media_face_clone_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_destroy_p",utc_media_face_destroy_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_destroy_n",utc_media_face_destroy_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_get_face_id_p",utc_media_face_get_face_id_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_get_face_id_n",utc_media_face_get_face_id_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_get_media_id_p",utc_media_face_get_media_id_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_get_media_id_n",utc_media_face_get_media_id_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_get_face_rect_p",utc_media_face_get_face_rect_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_get_face_rect_n",utc_media_face_get_face_rect_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_get_orientation_p",utc_media_face_get_orientation_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_get_orientation_n",utc_media_face_get_orientation_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_get_tag_p",utc_media_face_get_tag_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_get_tag_n",utc_media_face_get_tag_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_create_p",utc_media_face_create_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_create_n",utc_media_face_create_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_set_face_rect_p",utc_media_face_set_face_rect_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_set_face_rect_n",utc_media_face_set_face_rect_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_set_orientation_p",utc_media_face_set_orientation_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_set_orientation_n",utc_media_face_set_orientation_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_set_tag_p",utc_media_face_set_tag_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_set_tag_n",utc_media_face_set_tag_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_insert_to_db_p",utc_media_face_insert_to_db_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_insert_to_db_n",utc_media_face_insert_to_db_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_update_to_db_p",utc_media_face_update_to_db_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_update_to_db_n",utc_media_face_update_to_db_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_delete_from_db_p",utc_media_face_delete_from_db_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_delete_from_db_n",utc_media_face_delete_from_db_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_get_face_count_from_db_p",utc_media_face_get_face_count_from_db_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_get_face_count_from_db_n",utc_media_face_get_face_count_from_db_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_foreach_face_from_db_p",utc_media_face_foreach_face_from_db_p,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_face_foreach_face_from_db_n",utc_media_face_foreach_face_from_db_n,utc_media_face_startup,utc_media_face_cleanup},
	{"utc_media_filter_create_n",utc_media_filter_create_n,NULL,utc_media_filter_create_cleanup},
	{"utc_media_filter_create_p",utc_media_filter_create_p,NULL,utc_media_filter_create_cleanup},
	{"utc_media_filter_destroy_n",utc_media_filter_destroy_n,utc_media_filter_destroy_startup,utc_media_filter_destroy_cleanup},
	{"utc_media_filter_destroy_p",utc_media_filter_destroy_p,utc_media_filter_destroy_startup,utc_media_filter_destroy_cleanup},
	{"utc_media_filter_set_offset_n",utc_media_filter_set_offset_n,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_set_offset_p",utc_media_filter_set_offset_p,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_set_condition_n",utc_media_filter_set_condition_n,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_set_condition_p",utc_media_filter_set_condition_p,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_set_order_n",utc_media_filter_set_order_n,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_set_order_p",utc_media_filter_set_order_p,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_set_storage_n",utc_media_filter_set_storage_n,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_set_storage_p",utc_media_filter_set_storage_p,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_get_offset_n",utc_media_filter_get_offset_n,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_get_offset_p",utc_media_filter_get_offset_p,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_get_condition_n",utc_media_filter_get_condition_n,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_get_condition_p",utc_media_filter_get_condition_p,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_get_order_n",utc_media_filter_get_order_n,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_get_order_p",utc_media_filter_get_order_p,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_get_storage_n",utc_media_filter_get_storage_n,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_filter_get_storage_p",utc_media_filter_get_storage_p,utc_media_filter_startup,utc_media_filter_cleanup},
	{"utc_media_folder_foreach_folder_from_db_n",utc_media_folder_foreach_folder_from_db_n,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_foreach_folder_from_db_p",utc_media_folder_foreach_folder_from_db_p,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_media_count_from_db_n",utc_media_folder_get_media_count_from_db_n,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_media_count_from_db_p",utc_media_folder_get_media_count_from_db_p,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_foreach_media_from_db_n",utc_media_folder_foreach_media_from_db_n,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_foreach_media_from_db_p",utc_media_folder_foreach_media_from_db_p,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_clone_n",utc_media_folder_clone_n,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_clone_p",utc_media_folder_clone_p,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_path_n",utc_media_folder_get_path_n,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_path_p",utc_media_folder_get_path_p,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_name_n",utc_media_folder_get_name_n,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_name_p",utc_media_folder_get_name_p,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_storage_type_n",utc_media_folder_get_storage_type_n,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_storage_type_p",utc_media_folder_get_storage_type_p,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_storage_id_n",utc_media_folder_get_storage_id_n,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_storage_id_p",utc_media_folder_get_storage_id_p,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_folder_id_n",utc_media_folder_get_folder_id_n,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_folder_id_p",utc_media_folder_get_folder_id_p,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_folder_from_db_n",utc_media_folder_get_folder_from_db_n,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_folder_from_db_p",utc_media_folder_get_folder_from_db_p,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_folder_count_from_db_n",utc_media_folder_get_folder_count_from_db_n,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_get_folder_count_from_db_p",utc_media_folder_get_folder_count_from_db_p,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_destroy_n",utc_media_folder_destroy_n,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_folder_destroy_p",utc_media_folder_destroy_p,utc_media_folder_startup,utc_media_folder_cleanup},
	{"utc_media_album_get_album_count_from_db_n",utc_media_album_get_album_count_from_db_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_album_count_from_db_p",utc_media_album_get_album_count_from_db_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_foreach_album_from_db_n",utc_media_album_foreach_album_from_db_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_foreach_album_from_db_p",utc_media_album_foreach_album_from_db_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_media_count_from_db_n",utc_media_album_get_media_count_from_db_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_media_count_from_db_p",utc_media_album_get_media_count_from_db_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_foreach_media_from_db_n",utc_media_album_foreach_media_from_db_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_foreach_media_from_db_p",utc_media_album_foreach_media_from_db_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_album_from_db_n",utc_media_album_get_album_from_db_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_album_from_db_p",utc_media_album_get_album_from_db_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_album_id_n",utc_media_album_get_album_id_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_album_id_p",utc_media_album_get_album_id_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_name_n",utc_media_album_get_name_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_name_p",utc_media_album_get_name_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_artist_n",utc_media_album_get_artist_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_artist_p",utc_media_album_get_artist_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_album_art_n",utc_media_album_get_album_art_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_get_album_art_p",utc_media_album_get_album_art_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_clone_n",utc_media_album_clone_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_clone_p",utc_media_album_clone_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_destroy_n",utc_media_album_destroy_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_album_destroy_p",utc_media_album_destroy_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_group_get_group_count_from_db_n",utc_media_group_get_group_count_from_db_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_group_get_group_count_from_db_p",utc_media_group_get_group_count_from_db_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_group_get_media_count_from_db_n",utc_media_group_get_media_count_from_db_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_group_get_media_count_from_db_p",utc_media_group_get_media_count_from_db_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_group_foreach_group_from_db_n",utc_media_group_foreach_group_from_db_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_group_foreach_group_from_db_p",utc_media_group_foreach_group_from_db_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_group_foreach_media_from_db_n",utc_media_group_foreach_media_from_db_n,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_media_group_foreach_media_from_db_p",utc_media_group_foreach_media_from_db_p,utc_media_group_startup,utc_media_group_cleanup},
	{"utc_image_meta_destroy_n",utc_image_meta_destroy_n,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_destroy_p",utc_image_meta_destroy_p,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_clone_n",utc_image_meta_clone_n,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_clone_p",utc_image_meta_clone_p,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_media_id_n",utc_image_meta_get_media_id_n,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_media_id_p",utc_image_meta_get_media_id_p,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_width_n",utc_image_meta_get_width_n,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_width_p",utc_image_meta_get_width_p,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_height_n",utc_image_meta_get_height_n,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_height_p",utc_image_meta_get_height_p,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_orientation_n",utc_image_meta_get_orientation_n,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_orientation_p",utc_image_meta_get_orientation_p,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_date_taken_n",utc_image_meta_get_date_taken_n,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_date_taken_p",utc_image_meta_get_date_taken_p,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_exposure_time_n",utc_image_meta_get_exposure_time_n,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_exposure_time_p",utc_image_meta_get_exposure_time_p,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_fnumber_n",utc_image_meta_get_fnumber_n,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_fnumber_p",utc_image_meta_get_fnumber_p,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_iso_n",utc_image_meta_get_iso_n,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_iso_p",utc_image_meta_get_iso_p,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_model_n",utc_image_meta_get_model_n,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_image_meta_get_model_p",utc_image_meta_get_model_p,utc_media_image_startup,utc_media_image_cleanup},
	{"utc_media_info_insert_to_db_n",utc_media_info_insert_to_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_insert_to_db_p",utc_media_info_insert_to_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_insert_batch_to_db_n",utc_media_info_insert_batch_to_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_insert_batch_to_db_p",utc_media_info_insert_batch_to_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_set_favorite_n",utc_media_info_set_favorite_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_set_favorite_p",utc_media_info_set_favorite_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_update_to_db_n",utc_media_info_update_to_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_update_to_db_p",utc_media_info_update_to_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_create_thumbnail_n",utc_media_info_create_thumbnail_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_create_thumbnail_p",utc_media_info_create_thumbnail_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_start_face_detection_n",utc_media_info_start_face_detection_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_start_face_detection_p",utc_media_info_start_face_detection_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_move_to_db_n",utc_media_info_move_to_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_move_to_db_p",utc_media_info_move_to_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_delete_from_db_n",utc_media_info_delete_from_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_delete_from_db_p",utc_media_info_delete_from_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_foreach_media_from_db_n",utc_media_info_foreach_media_from_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_foreach_media_from_db_p",utc_media_info_foreach_media_from_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_destroy_n",utc_media_info_destroy_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_destroy_p",utc_media_info_destroy_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_clone_n",utc_media_info_clone_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_clone_p",utc_media_info_clone_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_media_id_n",utc_media_info_get_media_id_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_media_id_p",utc_media_info_get_media_id_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_file_path_n",utc_media_info_get_file_path_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_file_path_p",utc_media_info_get_file_path_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_display_name_n",utc_media_info_get_display_name_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_display_name_p",utc_media_info_get_display_name_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_media_type_n",utc_media_info_get_media_type_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_media_type_p",utc_media_info_get_media_type_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_mime_type_n",utc_media_info_get_mime_type_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_mime_type_p",utc_media_info_get_mime_type_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_thumbnail_path_n",utc_media_info_get_thumbnail_path_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_thumbnail_path_p",utc_media_info_get_thumbnail_path_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_modified_time_n",utc_media_info_get_modified_time_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_modified_time_p",utc_media_info_get_modified_time_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_size_n",utc_media_info_get_size_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_size_p",utc_media_info_get_size_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_storage_type_n",utc_media_info_get_storage_type_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_storage_type_p",utc_media_info_get_storage_type_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_storage_id_n",utc_media_info_get_storage_id_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_storage_id_p",utc_media_info_get_storage_id_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_is_drm_n",utc_media_info_is_drm_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_is_drm_p",utc_media_info_is_drm_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_altitude_n",utc_media_info_get_altitude_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_altitude_p",utc_media_info_get_altitude_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_latitude_n",utc_media_info_get_latitude_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_latitude_p",utc_media_info_get_latitude_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_longitude_n",utc_media_info_get_longitude_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_longitude_p",utc_media_info_get_longitude_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_description_n",utc_media_info_get_description_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_description_p",utc_media_info_get_description_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_rating_n",utc_media_info_get_rating_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_rating_p",utc_media_info_get_rating_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_added_time_n",utc_media_info_get_added_time_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_added_time_p",utc_media_info_get_added_time_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_favorite_n",utc_media_info_get_favorite_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_favorite_p",utc_media_info_get_favorite_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_media_from_db_n",utc_media_info_get_media_from_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_media_from_db_p",utc_media_info_get_media_from_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_media_from_db_by_path_n",utc_media_info_get_media_from_db_by_path_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_media_from_db_by_path_p",utc_media_info_get_media_from_db_by_path_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_image_n",utc_media_info_get_image_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_image_p",utc_media_info_get_image_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_video_n",utc_media_info_get_video_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_video_p",utc_media_info_get_video_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_audio_n",utc_media_info_get_audio_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_audio_p",utc_media_info_get_audio_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_book_n",utc_media_info_get_book_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_book_p",utc_media_info_get_book_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_foreach_tag_from_db_n",utc_media_info_foreach_tag_from_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_foreach_tag_from_db_p",utc_media_info_foreach_tag_from_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_foreach_bookmark_from_db_n",utc_media_info_foreach_bookmark_from_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_foreach_bookmark_from_db_p",utc_media_info_foreach_bookmark_from_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_bookmark_count_from_db_n",utc_media_info_get_bookmark_count_from_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_bookmark_count_from_db_p",utc_media_info_get_bookmark_count_from_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_media_count_from_db_n",utc_media_info_get_media_count_from_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_media_count_from_db_p",utc_media_info_get_media_count_from_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_tag_count_from_db_n",utc_media_info_get_tag_count_from_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_tag_count_from_db_p",utc_media_info_get_tag_count_from_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_timeline_n",utc_media_info_get_timeline_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_timeline_p",utc_media_info_get_timeline_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_title_n",utc_media_info_get_title_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_title_p",utc_media_info_get_title_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_is_360_content_n",utc_media_info_is_360_content_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_is_360_content_p",utc_media_info_is_360_content_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_cancel_thumbnail_n",utc_media_info_cancel_thumbnail_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_cancel_thumbnail_p",utc_media_info_cancel_thumbnail_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_cancel_face_detection_n",utc_media_info_cancel_face_detection_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_cancel_face_detection_p",utc_media_info_cancel_face_detection_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_face_count_from_db_n",utc_media_info_get_face_count_from_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_get_face_count_from_db_p",utc_media_info_get_face_count_from_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_foreach_face_from_db_n",utc_media_info_foreach_face_from_db_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_foreach_face_from_db_p",utc_media_info_foreach_face_from_db_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_generate_thumbnail_n",utc_media_info_generate_thumbnail_n,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_info_generate_thumbnail_p",utc_media_info_generate_thumbnail_p,utc_media_info_startup,utc_media_info_cleanup},
	{"utc_media_playlist_insert_to_db_n",utc_media_playlist_insert_to_db_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_insert_to_db_p",utc_media_playlist_insert_to_db_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_delete_from_db_n",utc_media_playlist_delete_from_db_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_delete_from_db_p",utc_media_playlist_delete_from_db_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_playlist_count_from_db_n",utc_media_playlist_get_playlist_count_from_db_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_playlist_count_from_db_p",utc_media_playlist_get_playlist_count_from_db_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_foreach_playlist_from_db_n",utc_media_playlist_foreach_playlist_from_db_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_foreach_playlist_from_db_p",utc_media_playlist_foreach_playlist_from_db_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_media_count_from_db_n",utc_media_playlist_get_media_count_from_db_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_media_count_from_db_p",utc_media_playlist_get_media_count_from_db_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_foreach_media_from_db_n",utc_media_playlist_foreach_media_from_db_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_foreach_media_from_db_p",utc_media_playlist_foreach_media_from_db_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_destroy_n",utc_media_playlist_destroy_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_destroy_p",utc_media_playlist_destroy_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_clone_n",utc_media_playlist_clone_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_clone_p",utc_media_playlist_clone_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_playlist_from_db_n",utc_media_playlist_get_playlist_from_db_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_playlist_from_db_p",utc_media_playlist_get_playlist_from_db_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_playlist_id_n",utc_media_playlist_get_playlist_id_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_playlist_id_p",utc_media_playlist_get_playlist_id_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_name_n",utc_media_playlist_get_name_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_name_p",utc_media_playlist_get_name_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_play_order_n",utc_media_playlist_get_play_order_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_play_order_p",utc_media_playlist_get_play_order_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_update_to_db_n",utc_media_playlist_update_to_db_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_update_to_db_p",utc_media_playlist_update_to_db_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_set_name_n",utc_media_playlist_set_name_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_set_name_p",utc_media_playlist_set_name_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_add_media_n",utc_media_playlist_add_media_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_add_media_p",utc_media_playlist_add_media_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_set_play_order_n",utc_media_playlist_set_play_order_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_set_play_order_p",utc_media_playlist_set_play_order_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_remove_media_n",utc_media_playlist_remove_media_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_remove_media_p",utc_media_playlist_remove_media_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_thumbnail_path_n",utc_media_playlist_get_thumbnail_path_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_get_thumbnail_path_p",utc_media_playlist_get_thumbnail_path_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_set_thumbnail_path_n",utc_media_playlist_set_thumbnail_path_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_set_thumbnail_path_p",utc_media_playlist_set_thumbnail_path_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_import_from_file_n",utc_media_playlist_import_from_file_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_import_from_file_p",utc_media_playlist_import_from_file_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_export_to_file_n",utc_media_playlist_export_to_file_n,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_playlist_export_to_file_p",utc_media_playlist_export_to_file_p,utc_media_playlist_startup,utc_media_playlist_cleanup},
	{"utc_media_storage_get_storage_info_from_db_n",utc_media_storage_get_storage_info_from_db_n,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_get_storage_info_from_db_p",utc_media_storage_get_storage_info_from_db_p,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_get_storage_count_from_db_n",utc_media_storage_get_storage_count_from_db_n,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_get_storage_count_from_db_p",utc_media_storage_get_storage_count_from_db_p,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_foreach_storage_from_db_n",utc_media_storage_foreach_storage_from_db_n,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_foreach_storage_from_db_p",utc_media_storage_foreach_storage_from_db_p,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_get_media_count_from_db_n",utc_media_storage_get_media_count_from_db_n,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_get_media_count_from_db_p",utc_media_storage_get_media_count_from_db_p,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_foreach_media_from_db_n",utc_media_storage_foreach_media_from_db_n,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_foreach_media_from_db_p",utc_media_storage_foreach_media_from_db_p,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_destroy_n",utc_media_storage_destroy_n,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_destroy_p",utc_media_storage_destroy_p,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_clone_n",utc_media_storage_clone_n,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_clone_p",utc_media_storage_clone_p,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_get_id_n",utc_media_storage_get_id_n,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_get_id_p",utc_media_storage_get_id_p,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_get_path_n",utc_media_storage_get_path_n,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_get_path_p",utc_media_storage_get_path_p,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_get_type_n",utc_media_storage_get_type_n,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_storage_get_type_p",utc_media_storage_get_type_p,utc_media_storage_startup,utc_media_storage_cleanup},
	{"utc_media_tag_insert_to_db_n",utc_media_tag_insert_to_db_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_insert_to_db_p",utc_media_tag_insert_to_db_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_delete_from_db_n",utc_media_tag_delete_from_db_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_delete_from_db_p",utc_media_tag_delete_from_db_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_get_tag_count_from_db_n",utc_media_tag_get_tag_count_from_db_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_get_tag_count_from_db_p",utc_media_tag_get_tag_count_from_db_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_foreach_tag_from_db_n",utc_media_tag_foreach_tag_from_db_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_foreach_tag_from_db_p",utc_media_tag_foreach_tag_from_db_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_get_media_count_from_db_n",utc_media_tag_get_media_count_from_db_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_get_media_count_from_db_p",utc_media_tag_get_media_count_from_db_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_foreach_media_from_db_n",utc_media_tag_foreach_media_from_db_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_foreach_media_from_db_p",utc_media_tag_foreach_media_from_db_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_clone_n",utc_media_tag_clone_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_clone_p",utc_media_tag_clone_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_update_to_db_n",utc_media_tag_update_to_db_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_update_to_db_p",utc_media_tag_update_to_db_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_add_media_n",utc_media_tag_add_media_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_add_media_p",utc_media_tag_add_media_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_remove_media_n",utc_media_tag_remove_media_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_remove_media_p",utc_media_tag_remove_media_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_set_name_n",utc_media_tag_set_name_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_set_name_p",utc_media_tag_set_name_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_get_tag_id_n",utc_media_tag_get_tag_id_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_get_tag_id_p",utc_media_tag_get_tag_id_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_get_name_n",utc_media_tag_get_name_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_get_name_p",utc_media_tag_get_name_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_get_tag_from_db_n",utc_media_tag_get_tag_from_db_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_get_tag_from_db_p",utc_media_tag_get_tag_from_db_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_destroy_n",utc_media_tag_destroy_n,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_media_tag_destroy_p",utc_media_tag_destroy_p,utc_media_tag_startup,utc_media_tag_cleanup},
	{"utc_video_meta_destroy_n",utc_video_meta_destroy_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_destroy_p",utc_video_meta_destroy_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_clone_n",utc_video_meta_clone_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_clone_p",utc_video_meta_clone_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_media_id_n",utc_video_meta_get_media_id_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_media_id_p",utc_video_meta_get_media_id_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_album_n",utc_video_meta_get_album_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_album_p",utc_video_meta_get_album_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_artist_n",utc_video_meta_get_artist_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_artist_p",utc_video_meta_get_artist_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_album_artist_n",utc_video_meta_get_album_artist_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_album_artist_p",utc_video_meta_get_album_artist_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_genre_n",utc_video_meta_get_genre_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_genre_p",utc_video_meta_get_genre_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_composer_n",utc_video_meta_get_composer_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_composer_p",utc_video_meta_get_composer_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_year_n",utc_video_meta_get_year_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_year_p",utc_video_meta_get_year_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_recorded_date_n",utc_video_meta_get_recorded_date_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_recorded_date_p",utc_video_meta_get_recorded_date_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_copyright_n",utc_video_meta_get_copyright_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_copyright_p",utc_video_meta_get_copyright_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_track_num_n",utc_video_meta_get_track_num_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_track_num_p",utc_video_meta_get_track_num_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_bit_rate_n",utc_video_meta_get_bit_rate_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_bit_rate_p",utc_video_meta_get_bit_rate_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_duration_n",utc_video_meta_get_duration_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_duration_p",utc_video_meta_get_duration_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_width_n",utc_video_meta_get_width_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_width_p",utc_video_meta_get_width_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_height_n",utc_video_meta_get_height_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_height_p",utc_video_meta_get_height_p,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_rotation_n",utc_video_meta_get_rotation_n,utc_media_video_startup,utc_media_video_cleanup},
	{"utc_video_meta_get_rotation_p",utc_video_meta_get_rotation_p,utc_media_video_startup,utc_media_video_cleanup},
	{NULL, NULL}
};

#endif // __TCT_MEDIA-CONTENT-NATIVE_H__
