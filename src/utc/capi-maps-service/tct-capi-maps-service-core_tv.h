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
#ifndef __TCT_CAPI-MAPS-SERVICE-NATIVE_H__
#define __TCT_CAPI-MAPS-SERVICE-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_maps_address_startup(void);
extern void utc_maps_address_cleanup(void);
extern void utc_maps_area_startup(void);
extern void utc_maps_area_cleanup(void);
extern void utc_maps_coordinates_startup(void);
extern void utc_maps_coordinates_cleanup(void);
extern void utc_maps_place_startup(void);
extern void utc_maps_place_cleanup(void);
extern void utc_maps_place_attribute_startup(void);
extern void utc_maps_place_attribute_cleanup(void);
extern void utc_maps_place_category_startup(void);
extern void utc_maps_place_category_cleanup(void);
extern void utc_maps_place_contact_startup(void);
extern void utc_maps_place_contact_cleanup(void);
extern void utc_maps_place_editorial_startup(void);
extern void utc_maps_place_editorial_cleanup(void);
extern void utc_maps_place_filter_startup(void);
extern void utc_maps_place_filter_cleanup(void);
extern void utc_maps_place_image_startup(void);
extern void utc_maps_place_image_cleanup(void);
extern void utc_maps_place_link_object_startup(void);
extern void utc_maps_place_link_object_cleanup(void);
extern void utc_maps_place_media_startup(void);
extern void utc_maps_place_media_cleanup(void);
extern void utc_maps_place_rating_startup(void);
extern void utc_maps_place_rating_cleanup(void);
extern void utc_maps_place_review_startup(void);
extern void utc_maps_place_review_cleanup(void);
extern void utc_maps_place_url_startup(void);
extern void utc_maps_place_url_cleanup(void);
extern void utc_maps_preference_startup(void);
extern void utc_maps_preference_cleanup(void);
extern void utc_maps_route_startup(void);
extern void utc_maps_route_cleanup(void);
extern void utc_maps_route_maneuver_startup(void);
extern void utc_maps_route_maneuver_cleanup(void);
extern void utc_maps_route_segment_startup(void);
extern void utc_maps_route_segment_cleanup(void);
extern void utc_maps_view_object_startup(void);
extern void utc_maps_view_object_cleanup(void);
extern void utc_maps_view_object_overlay_startup(void);
extern void utc_maps_view_object_overlay_cleanup(void);
extern void utc_maps_view_event_data_startup(void);
extern void utc_maps_view_event_data_cleanup(void);
extern void utc_maps_service_startup(void);
extern void utc_maps_service_cleanup(void);
extern void utc_maps_view_startup(void);
extern void utc_maps_view_cleanup(void);

extern int utc_maps_address_create_p(void);
extern int utc_maps_address_create_n(void);
extern int utc_maps_address_destroy_p(void);
extern int utc_maps_address_destroy_n(void);
extern int utc_maps_address_clone_p(void);
extern int utc_maps_address_clone_n(void);
extern int utc_maps_address_set_building_number_p(void);
extern int utc_maps_address_set_building_number_n(void);
extern int utc_maps_address_set_street_p(void);
extern int utc_maps_address_set_street_n(void);
extern int utc_maps_address_set_district_p(void);
extern int utc_maps_address_set_district_n(void);
extern int utc_maps_address_set_city_p(void);
extern int utc_maps_address_set_city_n(void);
extern int utc_maps_address_set_state_p(void);
extern int utc_maps_address_set_state_n(void);
extern int utc_maps_address_set_country_p(void);
extern int utc_maps_address_set_country_n(void);
extern int utc_maps_address_set_country_code_p(void);
extern int utc_maps_address_set_country_code_n(void);
extern int utc_maps_address_set_county_p(void);
extern int utc_maps_address_set_county_n(void);
extern int utc_maps_address_set_postal_code_p(void);
extern int utc_maps_address_set_postal_code_n(void);
extern int utc_maps_address_set_freetext_p(void);
extern int utc_maps_address_set_freetext_n(void);
extern int utc_maps_address_get_building_number_p(void);
extern int utc_maps_address_get_building_number_n(void);
extern int utc_maps_address_get_street_p(void);
extern int utc_maps_address_get_street_n(void);
extern int utc_maps_address_get_district_p(void);
extern int utc_maps_address_get_district_n(void);
extern int utc_maps_address_get_city_p(void);
extern int utc_maps_address_get_city_n(void);
extern int utc_maps_address_get_state_p(void);
extern int utc_maps_address_get_state_n(void);
extern int utc_maps_address_get_country_p(void);
extern int utc_maps_address_get_country_n(void);
extern int utc_maps_address_get_country_code_p(void);
extern int utc_maps_address_get_country_code_n(void);
extern int utc_maps_address_get_county_p(void);
extern int utc_maps_address_get_county_n(void);
extern int utc_maps_address_get_postal_code_p(void);
extern int utc_maps_address_get_postal_code_n(void);
extern int utc_maps_address_get_freetext_p(void);
extern int utc_maps_address_get_freetext_n(void);
extern int utc_maps_address_list_create_p(void);
extern int utc_maps_address_list_create_n(void);
extern int utc_maps_address_list_destroy_p(void);
extern int utc_maps_address_list_destroy_n(void);
extern int utc_maps_address_list_append_p(void);
extern int utc_maps_address_list_append_n(void);
extern int utc_maps_address_list_remove_p(void);
extern int utc_maps_address_list_remove_n(void);
extern int utc_maps_address_list_get_length_p(void);
extern int utc_maps_address_list_get_length_n(void);
extern int utc_maps_address_list_foreach_p(void);
extern int utc_maps_address_list_foreach_n(void);
extern int utc_maps_area_create_rectangle_p(void);
extern int utc_maps_area_create_rectangle_n(void);
extern int utc_maps_area_create_circle_p(void);
extern int utc_maps_area_create_circle_n(void);
extern int utc_maps_area_destroy_p(void);
extern int utc_maps_area_destroy_n(void);
extern int utc_maps_area_clone_p(void);
extern int utc_maps_area_clone_n(void);
extern int utc_maps_coordinates_create_p(void);
extern int utc_maps_coordinates_create_n(void);
extern int utc_maps_coordinates_destroy_p(void);
extern int utc_maps_coordinates_destroy_n(void);
extern int utc_maps_coordinates_clone_p(void);
extern int utc_maps_coordinates_clone_n(void);
extern int utc_maps_coordinates_get_latitude_p(void);
extern int utc_maps_coordinates_get_latitude_n(void);
extern int utc_maps_coordinates_get_longitude_p(void);
extern int utc_maps_coordinates_get_longitude_n(void);
extern int utc_maps_coordinates_set_latitude_p(void);
extern int utc_maps_coordinates_set_latitude_n(void);
extern int utc_maps_coordinates_set_longitude_p(void);
extern int utc_maps_coordinates_set_longitude_n(void);
extern int utc_maps_coordinates_get_latitude_longitude_p(void);
extern int utc_maps_coordinates_get_latitude_longitude_n(void);
extern int utc_maps_coordinates_set_latitude_longitude_p(void);
extern int utc_maps_coordinates_set_latitude_longitude_n(void);
extern int utc_maps_coordinates_list_create_p(void);
extern int utc_maps_coordinates_list_create_n(void);
extern int utc_maps_coordinates_list_destroy_p(void);
extern int utc_maps_coordinates_list_destroy_n(void);
extern int utc_maps_coordinates_list_append_p(void);
extern int utc_maps_coordinates_list_append_n(void);
extern int utc_maps_coordinates_list_remove_p(void);
extern int utc_maps_coordinates_list_remove_n(void);
extern int utc_maps_coordinates_list_get_length_p(void);
extern int utc_maps_coordinates_list_get_length_n(void);
extern int utc_maps_coordinates_list_foreach_p(void);
extern int utc_maps_coordinates_list_foreach_n(void);
extern int utc_maps_place_destroy_n(void);
extern int utc_maps_place_clone_n(void);
extern int utc_maps_place_get_id_n(void);
extern int utc_maps_place_get_name_n(void);
extern int utc_maps_place_get_uri_n(void);
extern int utc_maps_place_get_location_n(void);
extern int utc_maps_place_get_distance_n(void);
extern int utc_maps_place_get_address_n(void);
extern int utc_maps_place_get_rating_n(void);
extern int utc_maps_place_foreach_category_n(void);
extern int utc_maps_place_foreach_attribute_n(void);
extern int utc_maps_place_foreach_contact_n(void);
extern int utc_maps_place_foreach_editorial_n(void);
extern int utc_maps_place_foreach_image_n(void);
extern int utc_maps_place_foreach_review_n(void);
extern int utc_maps_place_get_supplier_link_n(void);
extern int utc_maps_place_get_related_link_n(void);
extern int utc_maps_place_foreach_property_n(void);
extern int utc_maps_place_list_destroy_n(void);
extern int utc_maps_place_attribute_destroy_n(void);
extern int utc_maps_place_attribute_clone_n(void);
extern int utc_maps_place_attribute_get_id_n(void);
extern int utc_maps_place_attribute_get_text_n(void);
extern int utc_maps_place_attribute_get_label_n(void);
extern int utc_maps_place_category_create_p(void);
extern int utc_maps_place_category_create_n(void);
extern int utc_maps_place_category_destroy_p(void);
extern int utc_maps_place_category_destroy_n(void);
extern int utc_maps_place_category_clone_p(void);
extern int utc_maps_place_category_clone_n(void);
extern int utc_maps_place_category_set_id_p(void);
extern int utc_maps_place_category_set_id_n(void);
extern int utc_maps_place_category_get_id_p(void);
extern int utc_maps_place_category_get_id_n(void);
extern int utc_maps_place_category_set_name_p(void);
extern int utc_maps_place_category_set_name_n(void);
extern int utc_maps_place_category_get_name_p(void);
extern int utc_maps_place_category_get_name_n(void);
extern int utc_maps_place_category_set_url_p(void);
extern int utc_maps_place_category_set_url_n(void);
extern int utc_maps_place_category_get_url_p(void);
extern int utc_maps_place_category_get_url_n(void);
extern int utc_maps_place_contact_destroy_n(void);
extern int utc_maps_place_contact_clone_n(void);
extern int utc_maps_place_contact_get_label_n(void);
extern int utc_maps_place_contact_get_type_n(void);
extern int utc_maps_place_contact_get_value_n(void);
extern int utc_maps_place_editorial_destroy_n(void);
extern int utc_maps_place_editorial_clone_n(void);
extern int utc_maps_place_editorial_get_description_n(void);
extern int utc_maps_place_editorial_get_language_n(void);
extern int utc_maps_place_editorial_get_media_n(void);
extern int utc_maps_place_filter_create_p(void);
extern int utc_maps_place_filter_create_n(void);
extern int utc_maps_place_filter_destroy_p(void);
extern int utc_maps_place_filter_destroy_n(void);
extern int utc_maps_place_filter_clone_p(void);
extern int utc_maps_place_filter_clone_n(void);
extern int utc_maps_place_filter_get_p(void);
extern int utc_maps_place_filter_get_n(void);
extern int utc_maps_place_filter_get_keyword_p(void);
extern int utc_maps_place_filter_get_keyword_n(void);
extern int utc_maps_place_filter_get_category_p(void);
extern int utc_maps_place_filter_get_category_n(void);
extern int utc_maps_place_filter_foreach_property_p(void);
extern int utc_maps_place_filter_foreach_property_n(void);
extern int utc_maps_place_filter_get_place_name_p(void);
extern int utc_maps_place_filter_get_place_name_n(void);
extern int utc_maps_place_filter_set_p(void);
extern int utc_maps_place_filter_set_n(void);
extern int utc_maps_place_filter_set_category_p(void);
extern int utc_maps_place_filter_set_category_n(void);
extern int utc_maps_place_filter_set_keyword_p(void);
extern int utc_maps_place_filter_set_keyword_n(void);
extern int utc_maps_place_filter_set_place_name_p(void);
extern int utc_maps_place_filter_set_place_name_n(void);
extern int utc_maps_place_filter_set_place_address_p(void);
extern int utc_maps_place_filter_set_place_address_n(void);
extern int utc_maps_place_filter_get_place_address_p(void);
extern int utc_maps_place_filter_get_place_address_n(void);
extern int utc_maps_place_image_destroy_n(void);
extern int utc_maps_place_image_clone_n(void);
extern int utc_maps_place_image_get_url_n(void);
extern int utc_maps_place_image_get_id_n(void);
extern int utc_maps_place_image_get_height_n(void);
extern int utc_maps_place_image_get_width_n(void);
extern int utc_maps_place_image_get_media_n(void);
extern int utc_maps_place_image_get_user_link_n(void);
extern int utc_maps_place_link_object_destroy_n(void);
extern int utc_maps_place_link_object_clone_n(void);
extern int utc_maps_place_link_object_get_id_n(void);
extern int utc_maps_place_link_object_get_name_n(void);
extern int utc_maps_place_link_object_get_type_n(void);
extern int utc_maps_place_link_object_get_string_n(void);
extern int utc_maps_place_media_destroy_n(void);
extern int utc_maps_place_media_clone_n(void);
extern int utc_maps_place_media_get_attribution_n(void);
extern int utc_maps_place_media_get_supplier_n(void);
extern int utc_maps_place_media_get_via_n(void);
extern int utc_maps_place_rating_destroy_n(void);
extern int utc_maps_place_rating_clone_n(void);
extern int utc_maps_place_rating_get_count_n(void);
extern int utc_maps_place_rating_get_average_n(void);
extern int utc_maps_place_review_destroy_n(void);
extern int utc_maps_place_review_clone_n(void);
extern int utc_maps_place_review_get_date_n(void);
extern int utc_maps_place_review_get_title_n(void);
extern int utc_maps_place_review_get_description_n(void);
extern int utc_maps_place_review_get_language_n(void);
extern int utc_maps_place_review_get_rating_n(void);
extern int utc_maps_place_review_get_media_n(void);
extern int utc_maps_place_review_get_user_link_n(void);
extern int utc_maps_place_url_destroy_n(void);
extern int utc_maps_place_url_clone_n(void);
extern int utc_maps_place_url_get_path_n(void);
extern int utc_maps_place_url_get_description_n(void);
extern int utc_maps_preference_create_p(void);
extern int utc_maps_preference_create_n(void);
extern int utc_maps_preference_destroy_p(void);
extern int utc_maps_preference_destroy_n(void);
extern int utc_maps_preference_clone_p(void);
extern int utc_maps_preference_clone_n(void);
extern int utc_maps_preference_get_distance_unit_p(void);
extern int utc_maps_preference_get_distance_unit_n(void);
extern int utc_maps_preference_get_language_p(void);
extern int utc_maps_preference_get_language_n(void);
extern int utc_maps_preference_get_max_results_p(void);
extern int utc_maps_preference_get_max_results_n(void);
extern int utc_maps_preference_get_country_code_p(void);
extern int utc_maps_preference_get_country_code_n(void);
extern int utc_maps_preference_get_route_optimization_p(void);
extern int utc_maps_preference_get_route_optimization_n(void);
extern int utc_maps_preference_get_route_transport_mode_p(void);
extern int utc_maps_preference_get_route_transport_mode_n(void);
extern int utc_maps_preference_get_route_feature_weight_p(void);
extern int utc_maps_preference_get_route_feature_weight_n(void);
extern int utc_maps_preference_get_route_feature_p(void);
extern int utc_maps_preference_get_route_feature_n(void);
extern int utc_maps_preference_get_p(void);
extern int utc_maps_preference_get_n(void);
extern int utc_maps_preference_foreach_property_p(void);
extern int utc_maps_preference_foreach_property_n(void);
extern int utc_maps_preference_set_distance_unit_p(void);
extern int utc_maps_preference_set_distance_unit_n(void);
extern int utc_maps_preference_set_language_p(void);
extern int utc_maps_preference_set_language_n(void);
extern int utc_maps_preference_set_max_results_p(void);
extern int utc_maps_preference_set_max_results_n(void);
extern int utc_maps_preference_set_country_code_p(void);
extern int utc_maps_preference_set_country_code_n(void);
extern int utc_maps_preference_set_route_optimization_p(void);
extern int utc_maps_preference_set_route_optimization_n(void);
extern int utc_maps_preference_set_route_transport_mode_p(void);
extern int utc_maps_preference_set_route_transport_mode_n(void);
extern int utc_maps_preference_set_route_feature_weight_p(void);
extern int utc_maps_preference_set_route_feature_weight_n(void);
extern int utc_maps_preference_set_route_feature_p(void);
extern int utc_maps_preference_set_route_feature_n(void);
extern int utc_maps_preference_set_property_p(void);
extern int utc_maps_preference_set_property_n(void);
extern int utc_maps_preference_set_route_alternatives_enabled_p(void);
extern int utc_maps_preference_set_route_alternatives_enabled_n(void);
extern int utc_maps_preference_get_route_alternatives_enabled_p(void);
extern int utc_maps_preference_get_route_alternatives_enabled_n(void);
extern int utc_maps_route_destroy_n(void);
extern int utc_maps_route_clone_n(void);
extern int utc_maps_route_get_route_id_n(void);
extern int utc_maps_route_get_origin_n(void);
extern int utc_maps_route_get_destination_n(void);
extern int utc_maps_route_get_bounding_box_n(void);
extern int utc_maps_route_get_total_distance_n(void);
extern int utc_maps_route_get_transport_mode_n(void);
extern int utc_maps_route_get_total_duration_n(void);
extern int utc_maps_route_get_distance_unit_n(void);
extern int utc_maps_route_foreach_property_n(void);
extern int utc_maps_route_foreach_path_n(void);
extern int utc_maps_route_foreach_segment_n(void);
extern int utc_maps_route_maneuver_destroy_n(void);
extern int utc_maps_route_maneuver_clone_n(void);
extern int utc_maps_route_maneuver_get_direction_id_n(void);
extern int utc_maps_route_maneuver_get_turn_type_n(void);
extern int utc_maps_route_maneuver_get_position_n(void);
extern int utc_maps_route_maneuver_get_road_name_n(void);
extern int utc_maps_route_maneuver_get_instruction_text_n(void);
extern int utc_maps_route_maneuver_get_locale_n(void);
extern int utc_maps_route_maneuver_get_time_to_next_instruction_n(void);
extern int utc_maps_route_maneuver_get_distance_to_next_instruction_n(void);
extern int utc_maps_route_segment_destroy_n(void);
extern int utc_maps_route_segment_clone_n(void);
extern int utc_maps_route_segment_get_origin_n(void);
extern int utc_maps_route_segment_get_destination_n(void);
extern int utc_maps_route_segment_get_bounding_box_n(void);
extern int utc_maps_route_segment_get_distance_n(void);
extern int utc_maps_route_segment_get_duration_n(void);
extern int utc_maps_route_segment_foreach_path_n(void);
extern int utc_maps_route_segment_foreach_maneuver_n(void);
extern int utc_maps_view_object_create_marker_p(void);
extern int utc_maps_view_object_create_marker_n(void);
extern int utc_maps_view_object_destroy_p(void);
extern int utc_maps_view_object_destroy_n(void);
extern int utc_maps_view_object_get_type_p(void);
extern int utc_maps_view_object_get_type_n(void);
extern int utc_maps_view_object_set_visible_p(void);
extern int utc_maps_view_object_set_visible_n(void);
extern int utc_maps_view_object_get_visible_p(void);
extern int utc_maps_view_object_get_visible_n(void);
extern int utc_maps_view_object_marker_set_coordinates_p(void);
extern int utc_maps_view_object_marker_set_coordinates_n(void);
extern int utc_maps_view_object_marker_resize_p(void);
extern int utc_maps_view_object_marker_resize_n(void);
extern int utc_maps_view_object_marker_set_image_file_p(void);
extern int utc_maps_view_object_marker_set_image_file_n(void);
extern int utc_maps_view_object_marker_get_image_file_p(void);
extern int utc_maps_view_object_marker_get_image_file_n(void);
extern int utc_maps_view_object_marker_get_coordinates_p(void);
extern int utc_maps_view_object_marker_get_coordinates_n(void);
extern int utc_maps_view_object_marker_get_size_p(void);
extern int utc_maps_view_object_marker_get_size_n(void);
extern int utc_maps_view_object_marker_get_type_p(void);
extern int utc_maps_view_object_marker_get_type_n(void);
extern int utc_maps_view_object_marker_set_z_order_p(void);
extern int utc_maps_view_object_marker_set_z_order_n(void);
extern int utc_maps_view_object_marker_get_z_order_p(void);
extern int utc_maps_view_object_marker_get_z_order_n(void);
extern int utc_maps_view_object_create_polyline_p(void);
extern int utc_maps_view_object_create_polyline_n(void);
extern int utc_maps_view_object_polyline_set_polyline_p(void);
extern int utc_maps_view_object_polyline_set_polyline_n(void);
extern int utc_maps_view_object_polyline_foreach_point_p(void);
extern int utc_maps_view_object_polyline_foreach_point_n(void);
extern int utc_maps_view_object_polyline_set_color_p(void);
extern int utc_maps_view_object_polyline_set_color_n(void);
extern int utc_maps_view_object_polyline_get_color_p(void);
extern int utc_maps_view_object_polyline_get_color_n(void);
extern int utc_maps_view_object_polyline_set_width_p(void);
extern int utc_maps_view_object_polyline_set_width_n(void);
extern int utc_maps_view_object_polyline_get_width_p(void);
extern int utc_maps_view_object_polyline_get_width_n(void);
extern int utc_maps_view_object_create_polygon_p(void);
extern int utc_maps_view_object_create_polygon_n(void);
extern int utc_maps_view_object_polygon_set_polygon_p(void);
extern int utc_maps_view_object_polygon_set_polygon_n(void);
extern int utc_maps_view_object_polygon_foreach_point_p(void);
extern int utc_maps_view_object_polygon_foreach_point_n(void);
extern int utc_maps_view_object_polygon_set_fill_color_p(void);
extern int utc_maps_view_object_polygon_set_fill_color_n(void);
extern int utc_maps_view_object_polygon_get_fill_color_p(void);
extern int utc_maps_view_object_polygon_get_fill_color_n(void);
extern int utc_maps_view_object_create_overlay_p(void);
extern int utc_maps_view_object_create_overlay_n(void);
extern int utc_maps_view_object_overlay_get_object_p(void);
extern int utc_maps_view_object_overlay_get_object_n(void);
extern int utc_maps_view_object_overlay_set_coordinates_p(void);
extern int utc_maps_view_object_overlay_set_coordinates_n(void);
extern int utc_maps_view_object_overlay_get_coordinates_p(void);
extern int utc_maps_view_object_overlay_get_coordinates_n(void);
extern int utc_maps_view_object_overlay_set_min_zoom_level_p(void);
extern int utc_maps_view_object_overlay_set_min_zoom_level_n(void);
extern int utc_maps_view_object_overlay_get_min_zoom_level_p(void);
extern int utc_maps_view_object_overlay_get_min_zoom_level_n(void);
extern int utc_maps_view_object_overlay_set_max_zoom_level_p(void);
extern int utc_maps_view_object_overlay_set_max_zoom_level_n(void);
extern int utc_maps_view_object_overlay_get_max_zoom_level_p(void);
extern int utc_maps_view_object_overlay_get_max_zoom_level_n(void);
extern int utc_maps_view_event_data_destroy_n(void);
extern int utc_maps_view_event_data_clone_n(void);
extern int utc_maps_view_event_data_get_type_n(void);
extern int utc_maps_view_event_data_get_gesture_type_n(void);
extern int utc_maps_view_event_data_get_action_type_n(void);
extern int utc_maps_view_event_data_get_center_n(void);
extern int utc_maps_view_event_data_get_delta_n(void);
extern int utc_maps_view_event_data_get_position_n(void);
extern int utc_maps_view_event_data_get_fingers_n(void);
extern int utc_maps_view_event_data_get_zoom_factor_n(void);
extern int utc_maps_view_event_data_get_rotation_angle_n(void);
extern int utc_maps_view_event_data_get_object_n(void);
extern int utc_maps_view_event_data_get_coordinates_n(void);
extern int utc_maps_service_foreach_provider_p(void);
extern int utc_maps_service_foreach_provider_n(void);
extern int utc_maps_service_create_p(void);
extern int utc_maps_service_create_n(void);
extern int utc_maps_service_destroy_p(void);
extern int utc_maps_service_destroy_n(void);
extern int utc_maps_service_set_provider_key_p(void);
extern int utc_maps_service_set_provider_key_n(void);
extern int utc_maps_service_get_provider_key_p(void);
extern int utc_maps_service_get_provider_key_n(void);
extern int utc_maps_service_set_preference_p(void);
extern int utc_maps_service_set_preference_n(void);
extern int utc_maps_service_get_preference_p(void);
extern int utc_maps_service_get_preference_n(void);
extern int utc_maps_service_provider_is_service_supported_p(void);
extern int utc_maps_service_provider_is_service_supported_n(void);
extern int utc_maps_service_provider_is_data_supported_p(void);
extern int utc_maps_service_provider_is_data_supported_n(void);
extern int utc_maps_service_geocode_p(void);
extern int utc_maps_service_geocode_n(void);
extern int utc_maps_service_geocode_inside_area_p(void);
extern int utc_maps_service_geocode_inside_area_n(void);
extern int utc_maps_service_geocode_by_structured_address_p(void);
extern int utc_maps_service_geocode_by_structured_address_n(void);
extern int utc_maps_service_reverse_geocode_p(void);
extern int utc_maps_service_reverse_geocode_n(void);
extern int utc_maps_service_cancel_request_p(void);
extern int utc_maps_service_cancel_request_n(void);
extern int utc_maps_service_search_route_p(void);
extern int utc_maps_service_search_route_n(void);
extern int utc_maps_service_search_route_waypoints_p(void);
extern int utc_maps_service_search_route_waypoints_n(void);
extern int utc_maps_service_search_place_p(void);
extern int utc_maps_service_search_place_n(void);
extern int utc_maps_service_search_place_by_area_p(void);
extern int utc_maps_service_search_place_by_area_n(void);
extern int utc_maps_service_search_place_by_address_p(void);
extern int utc_maps_service_search_place_by_address_n(void);
extern int utc_maps_service_multi_reverse_geocode_p(void);
extern int utc_maps_service_multi_reverse_geocode_n(void);
extern int utc_maps_service_search_place_list_p(void);
extern int utc_maps_service_search_place_list_n(void);
extern int utc_maps_service_get_place_details_p(void);
extern int utc_maps_service_get_place_details_n(void);
extern int utc_maps_service_request_user_consent_p(void);
extern int utc_maps_service_request_user_consent_n(void);
extern int utc_maps_view_create_p(void);
extern int utc_maps_view_create_n(void);
extern int utc_maps_view_get_center_p(void);
extern int utc_maps_view_get_center_n(void);
extern int utc_maps_view_set_center_p(void);
extern int utc_maps_view_set_center_n(void);
extern int utc_maps_view_get_zoom_level_p(void);
extern int utc_maps_view_get_zoom_level_n(void);
extern int utc_maps_view_set_zoom_level_p(void);
extern int utc_maps_view_set_zoom_level_n(void);
extern int utc_maps_view_get_min_zoom_level_p(void);
extern int utc_maps_view_get_min_zoom_level_n(void);
extern int utc_maps_view_get_max_zoom_level_p(void);
extern int utc_maps_view_get_max_zoom_level_n(void);
extern int utc_maps_view_set_orientation_p(void);
extern int utc_maps_view_set_orientation_n(void);
extern int utc_maps_view_get_orientation_p(void);
extern int utc_maps_view_get_orientation_n(void);
extern int utc_maps_view_screen_to_geolocation_p(void);
extern int utc_maps_view_screen_to_geolocation_n(void);
extern int utc_maps_view_geolocation_to_screen_p(void);
extern int utc_maps_view_geolocation_to_screen_n(void);
extern int utc_maps_view_set_type_p(void);
extern int utc_maps_view_set_type_n(void);
extern int utc_maps_view_get_type_p(void);
extern int utc_maps_view_get_type_n(void);
extern int utc_maps_view_set_buildings_enabled_p(void);
extern int utc_maps_view_set_buildings_enabled_n(void);
extern int utc_maps_view_get_buildings_enabled_p(void);
extern int utc_maps_view_get_buildings_enabled_n(void);
extern int utc_maps_view_set_traffic_enabled_p(void);
extern int utc_maps_view_set_traffic_enabled_n(void);
extern int utc_maps_view_get_traffic_enabled_p(void);
extern int utc_maps_view_get_traffic_enabled_n(void);
extern int utc_maps_view_set_public_transit_enabled_p(void);
extern int utc_maps_view_set_public_transit_enabled_n(void);
extern int utc_maps_view_get_public_transit_enabled_p(void);
extern int utc_maps_view_get_public_transit_enabled_n(void);
extern int utc_maps_view_set_language_p(void);
extern int utc_maps_view_set_language_n(void);
extern int utc_maps_view_get_language_p(void);
extern int utc_maps_view_get_language_n(void);
extern int utc_maps_view_get_viewport_p(void);
extern int utc_maps_view_get_viewport_n(void);
extern int utc_maps_view_set_screen_location_p(void);
extern int utc_maps_view_set_screen_location_n(void);
extern int utc_maps_view_get_screen_location_p(void);
extern int utc_maps_view_get_screen_location_n(void);
extern int utc_maps_view_move_p(void);
extern int utc_maps_view_move_n(void);
extern int utc_maps_view_resize_p(void);
extern int utc_maps_view_resize_n(void);
extern int utc_maps_view_set_visibility_p(void);
extern int utc_maps_view_set_visibility_n(void);
extern int utc_maps_view_get_visibility_p(void);
extern int utc_maps_view_get_visibility_n(void);
extern int utc_maps_view_set_event_cb_p(void);
extern int utc_maps_view_set_event_cb_n(void);
extern int utc_maps_view_unset_event_cb_p(void);
extern int utc_maps_view_unset_event_cb_n(void);
extern int utc_maps_view_set_gesture_enabled_p(void);
extern int utc_maps_view_set_gesture_enabled_n(void);
extern int utc_maps_view_get_gesture_enabled_p(void);
extern int utc_maps_view_get_gesture_enabled_n(void);
extern int utc_maps_view_set_scalebar_enabled_p(void);
extern int utc_maps_view_set_scalebar_enabled_n(void);
extern int utc_maps_view_get_scalebar_enabled_p(void);
extern int utc_maps_view_get_scalebar_enabled_n(void);
extern int utc_maps_view_add_object_p(void);
extern int utc_maps_view_add_object_n(void);
extern int utc_maps_view_remove_object_p(void);
extern int utc_maps_view_remove_object_n(void);
extern int utc_maps_view_remove_all_objects_p(void);
extern int utc_maps_view_remove_all_objects_n(void);
extern int utc_maps_view_foreach_object_p(void);
extern int utc_maps_view_foreach_object_n(void);
extern int utc_maps_view_set_min_zoom_level_p(void);
extern int utc_maps_view_set_min_zoom_level_n(void);
extern int utc_maps_view_set_max_zoom_level_p(void);
extern int utc_maps_view_set_max_zoom_level_n(void);
extern int utc_maps_view_capture_snapshot_p(void);
extern int utc_maps_view_capture_snapshot_n(void);
extern int utc_maps_view_destroy_p(void);
extern int utc_maps_view_destroy_n(void);

testcase tc_array[] = {
	{"utc_maps_address_create_p",utc_maps_address_create_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_create_n",utc_maps_address_create_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_destroy_p",utc_maps_address_destroy_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_destroy_n",utc_maps_address_destroy_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_clone_p",utc_maps_address_clone_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_clone_n",utc_maps_address_clone_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_building_number_p",utc_maps_address_set_building_number_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_building_number_n",utc_maps_address_set_building_number_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_street_p",utc_maps_address_set_street_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_street_n",utc_maps_address_set_street_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_district_p",utc_maps_address_set_district_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_district_n",utc_maps_address_set_district_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_city_p",utc_maps_address_set_city_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_city_n",utc_maps_address_set_city_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_state_p",utc_maps_address_set_state_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_state_n",utc_maps_address_set_state_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_country_p",utc_maps_address_set_country_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_country_n",utc_maps_address_set_country_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_country_code_p",utc_maps_address_set_country_code_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_country_code_n",utc_maps_address_set_country_code_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_county_p",utc_maps_address_set_county_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_county_n",utc_maps_address_set_county_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_postal_code_p",utc_maps_address_set_postal_code_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_postal_code_n",utc_maps_address_set_postal_code_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_freetext_p",utc_maps_address_set_freetext_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_set_freetext_n",utc_maps_address_set_freetext_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_building_number_p",utc_maps_address_get_building_number_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_building_number_n",utc_maps_address_get_building_number_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_street_p",utc_maps_address_get_street_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_street_n",utc_maps_address_get_street_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_district_p",utc_maps_address_get_district_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_district_n",utc_maps_address_get_district_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_city_p",utc_maps_address_get_city_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_city_n",utc_maps_address_get_city_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_state_p",utc_maps_address_get_state_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_state_n",utc_maps_address_get_state_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_country_p",utc_maps_address_get_country_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_country_n",utc_maps_address_get_country_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_country_code_p",utc_maps_address_get_country_code_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_country_code_n",utc_maps_address_get_country_code_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_county_p",utc_maps_address_get_county_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_county_n",utc_maps_address_get_county_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_postal_code_p",utc_maps_address_get_postal_code_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_postal_code_n",utc_maps_address_get_postal_code_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_freetext_p",utc_maps_address_get_freetext_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_get_freetext_n",utc_maps_address_get_freetext_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_list_create_p",utc_maps_address_list_create_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_list_create_n",utc_maps_address_list_create_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_list_destroy_p",utc_maps_address_list_destroy_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_list_destroy_n",utc_maps_address_list_destroy_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_list_append_p",utc_maps_address_list_append_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_list_append_n",utc_maps_address_list_append_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_list_remove_p",utc_maps_address_list_remove_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_list_remove_n",utc_maps_address_list_remove_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_list_get_length_p",utc_maps_address_list_get_length_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_list_get_length_n",utc_maps_address_list_get_length_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_list_foreach_p",utc_maps_address_list_foreach_p,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_address_list_foreach_n",utc_maps_address_list_foreach_n,utc_maps_address_startup,utc_maps_address_cleanup},
	{"utc_maps_area_create_rectangle_p",utc_maps_area_create_rectangle_p,utc_maps_area_startup,utc_maps_area_cleanup},
	{"utc_maps_area_create_rectangle_n",utc_maps_area_create_rectangle_n,utc_maps_area_startup,utc_maps_area_cleanup},
	{"utc_maps_area_create_circle_p",utc_maps_area_create_circle_p,utc_maps_area_startup,utc_maps_area_cleanup},
	{"utc_maps_area_create_circle_n",utc_maps_area_create_circle_n,utc_maps_area_startup,utc_maps_area_cleanup},
	{"utc_maps_area_destroy_p",utc_maps_area_destroy_p,utc_maps_area_startup,utc_maps_area_cleanup},
	{"utc_maps_area_destroy_n",utc_maps_area_destroy_n,utc_maps_area_startup,utc_maps_area_cleanup},
	{"utc_maps_area_clone_p",utc_maps_area_clone_p,utc_maps_area_startup,utc_maps_area_cleanup},
	{"utc_maps_area_clone_n",utc_maps_area_clone_n,utc_maps_area_startup,utc_maps_area_cleanup},
	{"utc_maps_coordinates_create_p",utc_maps_coordinates_create_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_create_n",utc_maps_coordinates_create_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_destroy_p",utc_maps_coordinates_destroy_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_destroy_n",utc_maps_coordinates_destroy_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_clone_p",utc_maps_coordinates_clone_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_clone_n",utc_maps_coordinates_clone_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_get_latitude_p",utc_maps_coordinates_get_latitude_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_get_latitude_n",utc_maps_coordinates_get_latitude_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_get_longitude_p",utc_maps_coordinates_get_longitude_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_get_longitude_n",utc_maps_coordinates_get_longitude_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_set_latitude_p",utc_maps_coordinates_set_latitude_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_set_latitude_n",utc_maps_coordinates_set_latitude_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_set_longitude_p",utc_maps_coordinates_set_longitude_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_set_longitude_n",utc_maps_coordinates_set_longitude_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_get_latitude_longitude_p",utc_maps_coordinates_get_latitude_longitude_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_get_latitude_longitude_n",utc_maps_coordinates_get_latitude_longitude_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_set_latitude_longitude_p",utc_maps_coordinates_set_latitude_longitude_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_set_latitude_longitude_n",utc_maps_coordinates_set_latitude_longitude_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_list_create_p",utc_maps_coordinates_list_create_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_list_create_n",utc_maps_coordinates_list_create_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_list_destroy_p",utc_maps_coordinates_list_destroy_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_list_destroy_n",utc_maps_coordinates_list_destroy_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_list_append_p",utc_maps_coordinates_list_append_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_list_append_n",utc_maps_coordinates_list_append_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_list_remove_p",utc_maps_coordinates_list_remove_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_list_remove_n",utc_maps_coordinates_list_remove_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_list_get_length_p",utc_maps_coordinates_list_get_length_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_list_get_length_n",utc_maps_coordinates_list_get_length_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_list_foreach_p",utc_maps_coordinates_list_foreach_p,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_coordinates_list_foreach_n",utc_maps_coordinates_list_foreach_n,utc_maps_coordinates_startup,utc_maps_coordinates_cleanup},
	{"utc_maps_place_destroy_n",utc_maps_place_destroy_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_clone_n",utc_maps_place_clone_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_get_id_n",utc_maps_place_get_id_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_get_name_n",utc_maps_place_get_name_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_get_uri_n",utc_maps_place_get_uri_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_get_location_n",utc_maps_place_get_location_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_get_distance_n",utc_maps_place_get_distance_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_get_address_n",utc_maps_place_get_address_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_get_rating_n",utc_maps_place_get_rating_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_foreach_category_n",utc_maps_place_foreach_category_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_foreach_attribute_n",utc_maps_place_foreach_attribute_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_foreach_contact_n",utc_maps_place_foreach_contact_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_foreach_editorial_n",utc_maps_place_foreach_editorial_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_foreach_image_n",utc_maps_place_foreach_image_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_foreach_review_n",utc_maps_place_foreach_review_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_get_supplier_link_n",utc_maps_place_get_supplier_link_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_get_related_link_n",utc_maps_place_get_related_link_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_foreach_property_n",utc_maps_place_foreach_property_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_list_destroy_n",utc_maps_place_list_destroy_n,utc_maps_place_startup,utc_maps_place_cleanup},
	{"utc_maps_place_attribute_destroy_n",utc_maps_place_attribute_destroy_n,utc_maps_place_attribute_startup,utc_maps_place_attribute_cleanup},
	{"utc_maps_place_attribute_clone_n",utc_maps_place_attribute_clone_n,utc_maps_place_attribute_startup,utc_maps_place_attribute_cleanup},
	{"utc_maps_place_attribute_get_id_n",utc_maps_place_attribute_get_id_n,utc_maps_place_attribute_startup,utc_maps_place_attribute_cleanup},
	{"utc_maps_place_attribute_get_text_n",utc_maps_place_attribute_get_text_n,utc_maps_place_attribute_startup,utc_maps_place_attribute_cleanup},
	{"utc_maps_place_attribute_get_label_n",utc_maps_place_attribute_get_label_n,utc_maps_place_attribute_startup,utc_maps_place_attribute_cleanup},
	{"utc_maps_place_category_create_p",utc_maps_place_category_create_p,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_create_n",utc_maps_place_category_create_n,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_destroy_p",utc_maps_place_category_destroy_p,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_destroy_n",utc_maps_place_category_destroy_n,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_clone_p",utc_maps_place_category_clone_p,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_clone_n",utc_maps_place_category_clone_n,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_set_id_p",utc_maps_place_category_set_id_p,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_set_id_n",utc_maps_place_category_set_id_n,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_get_id_p",utc_maps_place_category_get_id_p,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_get_id_n",utc_maps_place_category_get_id_n,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_set_name_p",utc_maps_place_category_set_name_p,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_set_name_n",utc_maps_place_category_set_name_n,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_get_name_p",utc_maps_place_category_get_name_p,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_get_name_n",utc_maps_place_category_get_name_n,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_set_url_p",utc_maps_place_category_set_url_p,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_set_url_n",utc_maps_place_category_set_url_n,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_get_url_p",utc_maps_place_category_get_url_p,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_category_get_url_n",utc_maps_place_category_get_url_n,utc_maps_place_category_startup,utc_maps_place_category_cleanup},
	{"utc_maps_place_contact_destroy_n",utc_maps_place_contact_destroy_n,utc_maps_place_contact_startup,utc_maps_place_contact_cleanup},
	{"utc_maps_place_contact_clone_n",utc_maps_place_contact_clone_n,utc_maps_place_contact_startup,utc_maps_place_contact_cleanup},
	{"utc_maps_place_contact_get_label_n",utc_maps_place_contact_get_label_n,utc_maps_place_contact_startup,utc_maps_place_contact_cleanup},
	{"utc_maps_place_contact_get_type_n",utc_maps_place_contact_get_type_n,utc_maps_place_contact_startup,utc_maps_place_contact_cleanup},
	{"utc_maps_place_contact_get_value_n",utc_maps_place_contact_get_value_n,utc_maps_place_contact_startup,utc_maps_place_contact_cleanup},
	{"utc_maps_place_editorial_destroy_n",utc_maps_place_editorial_destroy_n,utc_maps_place_editorial_startup,utc_maps_place_editorial_cleanup},
	{"utc_maps_place_editorial_clone_n",utc_maps_place_editorial_clone_n,utc_maps_place_editorial_startup,utc_maps_place_editorial_cleanup},
	{"utc_maps_place_editorial_get_description_n",utc_maps_place_editorial_get_description_n,utc_maps_place_editorial_startup,utc_maps_place_editorial_cleanup},
	{"utc_maps_place_editorial_get_language_n",utc_maps_place_editorial_get_language_n,utc_maps_place_editorial_startup,utc_maps_place_editorial_cleanup},
	{"utc_maps_place_editorial_get_media_n",utc_maps_place_editorial_get_media_n,utc_maps_place_editorial_startup,utc_maps_place_editorial_cleanup},
	{"utc_maps_place_filter_create_p",utc_maps_place_filter_create_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_create_n",utc_maps_place_filter_create_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_destroy_p",utc_maps_place_filter_destroy_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_destroy_n",utc_maps_place_filter_destroy_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_clone_p",utc_maps_place_filter_clone_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_clone_n",utc_maps_place_filter_clone_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_get_p",utc_maps_place_filter_get_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_get_n",utc_maps_place_filter_get_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_get_keyword_p",utc_maps_place_filter_get_keyword_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_get_keyword_n",utc_maps_place_filter_get_keyword_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_get_category_p",utc_maps_place_filter_get_category_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_get_category_n",utc_maps_place_filter_get_category_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_foreach_property_p",utc_maps_place_filter_foreach_property_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_foreach_property_n",utc_maps_place_filter_foreach_property_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_get_place_name_p",utc_maps_place_filter_get_place_name_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_get_place_name_n",utc_maps_place_filter_get_place_name_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_set_p",utc_maps_place_filter_set_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_set_n",utc_maps_place_filter_set_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_set_category_p",utc_maps_place_filter_set_category_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_set_category_n",utc_maps_place_filter_set_category_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_set_keyword_p",utc_maps_place_filter_set_keyword_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_set_keyword_n",utc_maps_place_filter_set_keyword_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_set_place_name_p",utc_maps_place_filter_set_place_name_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_set_place_name_n",utc_maps_place_filter_set_place_name_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_set_place_address_p",utc_maps_place_filter_set_place_address_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_set_place_address_n",utc_maps_place_filter_set_place_address_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_get_place_address_p",utc_maps_place_filter_get_place_address_p,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_filter_get_place_address_n",utc_maps_place_filter_get_place_address_n,utc_maps_place_filter_startup,utc_maps_place_filter_cleanup},
	{"utc_maps_place_image_destroy_n",utc_maps_place_image_destroy_n,utc_maps_place_image_startup,utc_maps_place_image_cleanup},
	{"utc_maps_place_image_clone_n",utc_maps_place_image_clone_n,utc_maps_place_image_startup,utc_maps_place_image_cleanup},
	{"utc_maps_place_image_get_url_n",utc_maps_place_image_get_url_n,utc_maps_place_image_startup,utc_maps_place_image_cleanup},
	{"utc_maps_place_image_get_id_n",utc_maps_place_image_get_id_n,utc_maps_place_image_startup,utc_maps_place_image_cleanup},
	{"utc_maps_place_image_get_height_n",utc_maps_place_image_get_height_n,utc_maps_place_image_startup,utc_maps_place_image_cleanup},
	{"utc_maps_place_image_get_width_n",utc_maps_place_image_get_width_n,utc_maps_place_image_startup,utc_maps_place_image_cleanup},
	{"utc_maps_place_image_get_media_n",utc_maps_place_image_get_media_n,utc_maps_place_image_startup,utc_maps_place_image_cleanup},
	{"utc_maps_place_image_get_user_link_n",utc_maps_place_image_get_user_link_n,utc_maps_place_image_startup,utc_maps_place_image_cleanup},
	{"utc_maps_place_link_object_destroy_n",utc_maps_place_link_object_destroy_n,utc_maps_place_link_object_startup,utc_maps_place_link_object_cleanup},
	{"utc_maps_place_link_object_clone_n",utc_maps_place_link_object_clone_n,utc_maps_place_link_object_startup,utc_maps_place_link_object_cleanup},
	{"utc_maps_place_link_object_get_id_n",utc_maps_place_link_object_get_id_n,utc_maps_place_link_object_startup,utc_maps_place_link_object_cleanup},
	{"utc_maps_place_link_object_get_name_n",utc_maps_place_link_object_get_name_n,utc_maps_place_link_object_startup,utc_maps_place_link_object_cleanup},
	{"utc_maps_place_link_object_get_type_n",utc_maps_place_link_object_get_type_n,utc_maps_place_link_object_startup,utc_maps_place_link_object_cleanup},
	{"utc_maps_place_link_object_get_string_n",utc_maps_place_link_object_get_string_n,utc_maps_place_link_object_startup,utc_maps_place_link_object_cleanup},
	{"utc_maps_place_media_destroy_n",utc_maps_place_media_destroy_n,utc_maps_place_media_startup,utc_maps_place_media_cleanup},
	{"utc_maps_place_media_clone_n",utc_maps_place_media_clone_n,utc_maps_place_media_startup,utc_maps_place_media_cleanup},
	{"utc_maps_place_media_get_attribution_n",utc_maps_place_media_get_attribution_n,utc_maps_place_media_startup,utc_maps_place_media_cleanup},
	{"utc_maps_place_media_get_supplier_n",utc_maps_place_media_get_supplier_n,utc_maps_place_media_startup,utc_maps_place_media_cleanup},
	{"utc_maps_place_media_get_via_n",utc_maps_place_media_get_via_n,utc_maps_place_media_startup,utc_maps_place_media_cleanup},
	{"utc_maps_place_rating_destroy_n",utc_maps_place_rating_destroy_n,utc_maps_place_rating_startup,utc_maps_place_rating_cleanup},
	{"utc_maps_place_rating_clone_n",utc_maps_place_rating_clone_n,utc_maps_place_rating_startup,utc_maps_place_rating_cleanup},
	{"utc_maps_place_rating_get_count_n",utc_maps_place_rating_get_count_n,utc_maps_place_rating_startup,utc_maps_place_rating_cleanup},
	{"utc_maps_place_rating_get_average_n",utc_maps_place_rating_get_average_n,utc_maps_place_rating_startup,utc_maps_place_rating_cleanup},
	{"utc_maps_place_review_destroy_n",utc_maps_place_review_destroy_n,utc_maps_place_review_startup,utc_maps_place_review_cleanup},
	{"utc_maps_place_review_clone_n",utc_maps_place_review_clone_n,utc_maps_place_review_startup,utc_maps_place_review_cleanup},
	{"utc_maps_place_review_get_date_n",utc_maps_place_review_get_date_n,utc_maps_place_review_startup,utc_maps_place_review_cleanup},
	{"utc_maps_place_review_get_title_n",utc_maps_place_review_get_title_n,utc_maps_place_review_startup,utc_maps_place_review_cleanup},
	{"utc_maps_place_review_get_description_n",utc_maps_place_review_get_description_n,utc_maps_place_review_startup,utc_maps_place_review_cleanup},
	{"utc_maps_place_review_get_language_n",utc_maps_place_review_get_language_n,utc_maps_place_review_startup,utc_maps_place_review_cleanup},
	{"utc_maps_place_review_get_rating_n",utc_maps_place_review_get_rating_n,utc_maps_place_review_startup,utc_maps_place_review_cleanup},
	{"utc_maps_place_review_get_media_n",utc_maps_place_review_get_media_n,utc_maps_place_review_startup,utc_maps_place_review_cleanup},
	{"utc_maps_place_review_get_user_link_n",utc_maps_place_review_get_user_link_n,utc_maps_place_review_startup,utc_maps_place_review_cleanup},
	{"utc_maps_place_url_destroy_n",utc_maps_place_url_destroy_n,utc_maps_place_url_startup,utc_maps_place_url_cleanup},
	{"utc_maps_place_url_clone_n",utc_maps_place_url_clone_n,utc_maps_place_url_startup,utc_maps_place_url_cleanup},
	{"utc_maps_place_url_get_path_n",utc_maps_place_url_get_path_n,utc_maps_place_url_startup,utc_maps_place_url_cleanup},
	{"utc_maps_place_url_get_description_n",utc_maps_place_url_get_description_n,utc_maps_place_url_startup,utc_maps_place_url_cleanup},
	{"utc_maps_preference_create_p",utc_maps_preference_create_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_create_n",utc_maps_preference_create_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_destroy_p",utc_maps_preference_destroy_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_destroy_n",utc_maps_preference_destroy_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_clone_p",utc_maps_preference_clone_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_clone_n",utc_maps_preference_clone_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_distance_unit_p",utc_maps_preference_get_distance_unit_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_distance_unit_n",utc_maps_preference_get_distance_unit_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_language_p",utc_maps_preference_get_language_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_language_n",utc_maps_preference_get_language_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_max_results_p",utc_maps_preference_get_max_results_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_max_results_n",utc_maps_preference_get_max_results_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_country_code_p",utc_maps_preference_get_country_code_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_country_code_n",utc_maps_preference_get_country_code_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_route_optimization_p",utc_maps_preference_get_route_optimization_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_route_optimization_n",utc_maps_preference_get_route_optimization_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_route_transport_mode_p",utc_maps_preference_get_route_transport_mode_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_route_transport_mode_n",utc_maps_preference_get_route_transport_mode_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_route_feature_weight_p",utc_maps_preference_get_route_feature_weight_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_route_feature_weight_n",utc_maps_preference_get_route_feature_weight_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_route_feature_p",utc_maps_preference_get_route_feature_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_route_feature_n",utc_maps_preference_get_route_feature_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_p",utc_maps_preference_get_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_n",utc_maps_preference_get_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_foreach_property_p",utc_maps_preference_foreach_property_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_foreach_property_n",utc_maps_preference_foreach_property_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_distance_unit_p",utc_maps_preference_set_distance_unit_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_distance_unit_n",utc_maps_preference_set_distance_unit_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_language_p",utc_maps_preference_set_language_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_language_n",utc_maps_preference_set_language_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_max_results_p",utc_maps_preference_set_max_results_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_max_results_n",utc_maps_preference_set_max_results_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_country_code_p",utc_maps_preference_set_country_code_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_country_code_n",utc_maps_preference_set_country_code_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_route_optimization_p",utc_maps_preference_set_route_optimization_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_route_optimization_n",utc_maps_preference_set_route_optimization_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_route_transport_mode_p",utc_maps_preference_set_route_transport_mode_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_route_transport_mode_n",utc_maps_preference_set_route_transport_mode_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_route_feature_weight_p",utc_maps_preference_set_route_feature_weight_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_route_feature_weight_n",utc_maps_preference_set_route_feature_weight_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_route_feature_p",utc_maps_preference_set_route_feature_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_route_feature_n",utc_maps_preference_set_route_feature_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_property_p",utc_maps_preference_set_property_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_property_n",utc_maps_preference_set_property_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_route_alternatives_enabled_p",utc_maps_preference_set_route_alternatives_enabled_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_set_route_alternatives_enabled_n",utc_maps_preference_set_route_alternatives_enabled_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_route_alternatives_enabled_p",utc_maps_preference_get_route_alternatives_enabled_p,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_preference_get_route_alternatives_enabled_n",utc_maps_preference_get_route_alternatives_enabled_n,utc_maps_preference_startup,utc_maps_preference_cleanup},
	{"utc_maps_route_destroy_n",utc_maps_route_destroy_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_clone_n",utc_maps_route_clone_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_get_route_id_n",utc_maps_route_get_route_id_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_get_origin_n",utc_maps_route_get_origin_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_get_destination_n",utc_maps_route_get_destination_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_get_bounding_box_n",utc_maps_route_get_bounding_box_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_get_total_distance_n",utc_maps_route_get_total_distance_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_get_transport_mode_n",utc_maps_route_get_transport_mode_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_get_total_duration_n",utc_maps_route_get_total_duration_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_get_distance_unit_n",utc_maps_route_get_distance_unit_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_foreach_property_n",utc_maps_route_foreach_property_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_foreach_path_n",utc_maps_route_foreach_path_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_foreach_segment_n",utc_maps_route_foreach_segment_n,utc_maps_route_startup,utc_maps_route_cleanup},
	{"utc_maps_route_maneuver_destroy_n",utc_maps_route_maneuver_destroy_n,utc_maps_route_maneuver_startup,utc_maps_route_maneuver_cleanup},
	{"utc_maps_route_maneuver_clone_n",utc_maps_route_maneuver_clone_n,utc_maps_route_maneuver_startup,utc_maps_route_maneuver_cleanup},
	{"utc_maps_route_maneuver_get_direction_id_n",utc_maps_route_maneuver_get_direction_id_n,utc_maps_route_maneuver_startup,utc_maps_route_maneuver_cleanup},
	{"utc_maps_route_maneuver_get_turn_type_n",utc_maps_route_maneuver_get_turn_type_n,utc_maps_route_maneuver_startup,utc_maps_route_maneuver_cleanup},
	{"utc_maps_route_maneuver_get_position_n",utc_maps_route_maneuver_get_position_n,utc_maps_route_maneuver_startup,utc_maps_route_maneuver_cleanup},
	{"utc_maps_route_maneuver_get_road_name_n",utc_maps_route_maneuver_get_road_name_n,utc_maps_route_maneuver_startup,utc_maps_route_maneuver_cleanup},
	{"utc_maps_route_maneuver_get_instruction_text_n",utc_maps_route_maneuver_get_instruction_text_n,utc_maps_route_maneuver_startup,utc_maps_route_maneuver_cleanup},
	{"utc_maps_route_maneuver_get_locale_n",utc_maps_route_maneuver_get_locale_n,utc_maps_route_maneuver_startup,utc_maps_route_maneuver_cleanup},
	{"utc_maps_route_maneuver_get_time_to_next_instruction_n",utc_maps_route_maneuver_get_time_to_next_instruction_n,utc_maps_route_maneuver_startup,utc_maps_route_maneuver_cleanup},
	{"utc_maps_route_maneuver_get_distance_to_next_instruction_n",utc_maps_route_maneuver_get_distance_to_next_instruction_n,utc_maps_route_maneuver_startup,utc_maps_route_maneuver_cleanup},
	{"utc_maps_route_segment_destroy_n",utc_maps_route_segment_destroy_n,utc_maps_route_segment_startup,utc_maps_route_segment_cleanup},
	{"utc_maps_route_segment_clone_n",utc_maps_route_segment_clone_n,utc_maps_route_segment_startup,utc_maps_route_segment_cleanup},
	{"utc_maps_route_segment_get_origin_n",utc_maps_route_segment_get_origin_n,utc_maps_route_segment_startup,utc_maps_route_segment_cleanup},
	{"utc_maps_route_segment_get_destination_n",utc_maps_route_segment_get_destination_n,utc_maps_route_segment_startup,utc_maps_route_segment_cleanup},
	{"utc_maps_route_segment_get_bounding_box_n",utc_maps_route_segment_get_bounding_box_n,utc_maps_route_segment_startup,utc_maps_route_segment_cleanup},
	{"utc_maps_route_segment_get_distance_n",utc_maps_route_segment_get_distance_n,utc_maps_route_segment_startup,utc_maps_route_segment_cleanup},
	{"utc_maps_route_segment_get_duration_n",utc_maps_route_segment_get_duration_n,utc_maps_route_segment_startup,utc_maps_route_segment_cleanup},
	{"utc_maps_route_segment_foreach_path_n",utc_maps_route_segment_foreach_path_n,utc_maps_route_segment_startup,utc_maps_route_segment_cleanup},
	{"utc_maps_route_segment_foreach_maneuver_n",utc_maps_route_segment_foreach_maneuver_n,utc_maps_route_segment_startup,utc_maps_route_segment_cleanup},
	{"utc_maps_view_object_create_marker_p",utc_maps_view_object_create_marker_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_create_marker_n",utc_maps_view_object_create_marker_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_destroy_p",utc_maps_view_object_destroy_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_destroy_n",utc_maps_view_object_destroy_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_get_type_p",utc_maps_view_object_get_type_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_get_type_n",utc_maps_view_object_get_type_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_set_visible_p",utc_maps_view_object_set_visible_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_set_visible_n",utc_maps_view_object_set_visible_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_get_visible_p",utc_maps_view_object_get_visible_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_get_visible_n",utc_maps_view_object_get_visible_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_set_coordinates_p",utc_maps_view_object_marker_set_coordinates_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_set_coordinates_n",utc_maps_view_object_marker_set_coordinates_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_resize_p",utc_maps_view_object_marker_resize_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_resize_n",utc_maps_view_object_marker_resize_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_set_image_file_p",utc_maps_view_object_marker_set_image_file_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_set_image_file_n",utc_maps_view_object_marker_set_image_file_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_get_image_file_p",utc_maps_view_object_marker_get_image_file_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_get_image_file_n",utc_maps_view_object_marker_get_image_file_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_get_coordinates_p",utc_maps_view_object_marker_get_coordinates_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_get_coordinates_n",utc_maps_view_object_marker_get_coordinates_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_get_size_p",utc_maps_view_object_marker_get_size_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_get_size_n",utc_maps_view_object_marker_get_size_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_get_type_p",utc_maps_view_object_marker_get_type_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_get_type_n",utc_maps_view_object_marker_get_type_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_set_z_order_p",utc_maps_view_object_marker_set_z_order_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_set_z_order_n",utc_maps_view_object_marker_set_z_order_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_get_z_order_p",utc_maps_view_object_marker_get_z_order_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_marker_get_z_order_n",utc_maps_view_object_marker_get_z_order_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_create_polyline_p",utc_maps_view_object_create_polyline_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_create_polyline_n",utc_maps_view_object_create_polyline_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polyline_set_polyline_p",utc_maps_view_object_polyline_set_polyline_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polyline_set_polyline_n",utc_maps_view_object_polyline_set_polyline_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polyline_foreach_point_p",utc_maps_view_object_polyline_foreach_point_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polyline_foreach_point_n",utc_maps_view_object_polyline_foreach_point_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polyline_set_color_p",utc_maps_view_object_polyline_set_color_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polyline_set_color_n",utc_maps_view_object_polyline_set_color_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polyline_get_color_p",utc_maps_view_object_polyline_get_color_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polyline_get_color_n",utc_maps_view_object_polyline_get_color_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polyline_set_width_p",utc_maps_view_object_polyline_set_width_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polyline_set_width_n",utc_maps_view_object_polyline_set_width_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polyline_get_width_p",utc_maps_view_object_polyline_get_width_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polyline_get_width_n",utc_maps_view_object_polyline_get_width_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_create_polygon_p",utc_maps_view_object_create_polygon_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_create_polygon_n",utc_maps_view_object_create_polygon_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polygon_set_polygon_p",utc_maps_view_object_polygon_set_polygon_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polygon_set_polygon_n",utc_maps_view_object_polygon_set_polygon_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polygon_foreach_point_p",utc_maps_view_object_polygon_foreach_point_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polygon_foreach_point_n",utc_maps_view_object_polygon_foreach_point_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polygon_set_fill_color_p",utc_maps_view_object_polygon_set_fill_color_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polygon_set_fill_color_n",utc_maps_view_object_polygon_set_fill_color_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polygon_get_fill_color_p",utc_maps_view_object_polygon_get_fill_color_p,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_polygon_get_fill_color_n",utc_maps_view_object_polygon_get_fill_color_n,utc_maps_view_object_startup,utc_maps_view_object_cleanup},
	{"utc_maps_view_object_create_overlay_p",utc_maps_view_object_create_overlay_p,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_create_overlay_n",utc_maps_view_object_create_overlay_n,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_get_object_p",utc_maps_view_object_overlay_get_object_p,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_get_object_n",utc_maps_view_object_overlay_get_object_n,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_set_coordinates_p",utc_maps_view_object_overlay_set_coordinates_p,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_set_coordinates_n",utc_maps_view_object_overlay_set_coordinates_n,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_get_coordinates_p",utc_maps_view_object_overlay_get_coordinates_p,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_get_coordinates_n",utc_maps_view_object_overlay_get_coordinates_n,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_set_min_zoom_level_p",utc_maps_view_object_overlay_set_min_zoom_level_p,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_set_min_zoom_level_n",utc_maps_view_object_overlay_set_min_zoom_level_n,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_get_min_zoom_level_p",utc_maps_view_object_overlay_get_min_zoom_level_p,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_get_min_zoom_level_n",utc_maps_view_object_overlay_get_min_zoom_level_n,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_set_max_zoom_level_p",utc_maps_view_object_overlay_set_max_zoom_level_p,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_set_max_zoom_level_n",utc_maps_view_object_overlay_set_max_zoom_level_n,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_get_max_zoom_level_p",utc_maps_view_object_overlay_get_max_zoom_level_p,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_object_overlay_get_max_zoom_level_n",utc_maps_view_object_overlay_get_max_zoom_level_n,utc_maps_view_object_overlay_startup,utc_maps_view_object_overlay_cleanup},
	{"utc_maps_view_event_data_destroy_n",utc_maps_view_event_data_destroy_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_view_event_data_clone_n",utc_maps_view_event_data_clone_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_view_event_data_get_type_n",utc_maps_view_event_data_get_type_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_view_event_data_get_gesture_type_n",utc_maps_view_event_data_get_gesture_type_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_view_event_data_get_action_type_n",utc_maps_view_event_data_get_action_type_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_view_event_data_get_center_n",utc_maps_view_event_data_get_center_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_view_event_data_get_delta_n",utc_maps_view_event_data_get_delta_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_view_event_data_get_position_n",utc_maps_view_event_data_get_position_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_view_event_data_get_fingers_n",utc_maps_view_event_data_get_fingers_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_view_event_data_get_zoom_factor_n",utc_maps_view_event_data_get_zoom_factor_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_view_event_data_get_rotation_angle_n",utc_maps_view_event_data_get_rotation_angle_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_view_event_data_get_object_n",utc_maps_view_event_data_get_object_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_view_event_data_get_coordinates_n",utc_maps_view_event_data_get_coordinates_n,utc_maps_view_event_data_startup,utc_maps_view_event_data_cleanup},
	{"utc_maps_service_foreach_provider_p",utc_maps_service_foreach_provider_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_foreach_provider_n",utc_maps_service_foreach_provider_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_create_p",utc_maps_service_create_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_create_n",utc_maps_service_create_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_destroy_p",utc_maps_service_destroy_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_destroy_n",utc_maps_service_destroy_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_set_provider_key_p",utc_maps_service_set_provider_key_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_set_provider_key_n",utc_maps_service_set_provider_key_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_get_provider_key_p",utc_maps_service_get_provider_key_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_get_provider_key_n",utc_maps_service_get_provider_key_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_set_preference_p",utc_maps_service_set_preference_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_set_preference_n",utc_maps_service_set_preference_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_get_preference_p",utc_maps_service_get_preference_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_get_preference_n",utc_maps_service_get_preference_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_provider_is_service_supported_p",utc_maps_service_provider_is_service_supported_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_provider_is_service_supported_n",utc_maps_service_provider_is_service_supported_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_provider_is_data_supported_p",utc_maps_service_provider_is_data_supported_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_provider_is_data_supported_n",utc_maps_service_provider_is_data_supported_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_geocode_p",utc_maps_service_geocode_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_geocode_n",utc_maps_service_geocode_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_geocode_inside_area_p",utc_maps_service_geocode_inside_area_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_geocode_inside_area_n",utc_maps_service_geocode_inside_area_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_geocode_by_structured_address_p",utc_maps_service_geocode_by_structured_address_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_geocode_by_structured_address_n",utc_maps_service_geocode_by_structured_address_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_reverse_geocode_p",utc_maps_service_reverse_geocode_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_reverse_geocode_n",utc_maps_service_reverse_geocode_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_cancel_request_p",utc_maps_service_cancel_request_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_cancel_request_n",utc_maps_service_cancel_request_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_search_route_p",utc_maps_service_search_route_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_search_route_n",utc_maps_service_search_route_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_search_route_waypoints_p",utc_maps_service_search_route_waypoints_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_search_route_waypoints_n",utc_maps_service_search_route_waypoints_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_search_place_p",utc_maps_service_search_place_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_search_place_n",utc_maps_service_search_place_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_search_place_by_area_p",utc_maps_service_search_place_by_area_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_search_place_by_area_n",utc_maps_service_search_place_by_area_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_search_place_by_address_p",utc_maps_service_search_place_by_address_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_search_place_by_address_n",utc_maps_service_search_place_by_address_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_multi_reverse_geocode_p",utc_maps_service_multi_reverse_geocode_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_multi_reverse_geocode_n",utc_maps_service_multi_reverse_geocode_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_search_place_list_p",utc_maps_service_search_place_list_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_search_place_list_n",utc_maps_service_search_place_list_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_get_place_details_p",utc_maps_service_get_place_details_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_get_place_details_n",utc_maps_service_get_place_details_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_request_user_consent_p",utc_maps_service_request_user_consent_p,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_service_request_user_consent_n",utc_maps_service_request_user_consent_n,utc_maps_service_startup,utc_maps_service_cleanup},
	{"utc_maps_view_create_p",utc_maps_view_create_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_create_n",utc_maps_view_create_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_center_p",utc_maps_view_get_center_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_center_n",utc_maps_view_get_center_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_center_p",utc_maps_view_set_center_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_center_n",utc_maps_view_set_center_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_zoom_level_p",utc_maps_view_get_zoom_level_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_zoom_level_n",utc_maps_view_get_zoom_level_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_zoom_level_p",utc_maps_view_set_zoom_level_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_zoom_level_n",utc_maps_view_set_zoom_level_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_min_zoom_level_p",utc_maps_view_get_min_zoom_level_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_min_zoom_level_n",utc_maps_view_get_min_zoom_level_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_max_zoom_level_p",utc_maps_view_get_max_zoom_level_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_max_zoom_level_n",utc_maps_view_get_max_zoom_level_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_orientation_p",utc_maps_view_set_orientation_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_orientation_n",utc_maps_view_set_orientation_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_orientation_p",utc_maps_view_get_orientation_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_orientation_n",utc_maps_view_get_orientation_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_screen_to_geolocation_p",utc_maps_view_screen_to_geolocation_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_screen_to_geolocation_n",utc_maps_view_screen_to_geolocation_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_geolocation_to_screen_p",utc_maps_view_geolocation_to_screen_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_geolocation_to_screen_n",utc_maps_view_geolocation_to_screen_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_type_p",utc_maps_view_set_type_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_type_n",utc_maps_view_set_type_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_type_p",utc_maps_view_get_type_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_type_n",utc_maps_view_get_type_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_buildings_enabled_p",utc_maps_view_set_buildings_enabled_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_buildings_enabled_n",utc_maps_view_set_buildings_enabled_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_buildings_enabled_p",utc_maps_view_get_buildings_enabled_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_buildings_enabled_n",utc_maps_view_get_buildings_enabled_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_traffic_enabled_p",utc_maps_view_set_traffic_enabled_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_traffic_enabled_n",utc_maps_view_set_traffic_enabled_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_traffic_enabled_p",utc_maps_view_get_traffic_enabled_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_traffic_enabled_n",utc_maps_view_get_traffic_enabled_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_public_transit_enabled_p",utc_maps_view_set_public_transit_enabled_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_public_transit_enabled_n",utc_maps_view_set_public_transit_enabled_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_public_transit_enabled_p",utc_maps_view_get_public_transit_enabled_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_public_transit_enabled_n",utc_maps_view_get_public_transit_enabled_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_language_p",utc_maps_view_set_language_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_language_n",utc_maps_view_set_language_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_language_p",utc_maps_view_get_language_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_language_n",utc_maps_view_get_language_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_viewport_p",utc_maps_view_get_viewport_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_viewport_n",utc_maps_view_get_viewport_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_screen_location_p",utc_maps_view_set_screen_location_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_screen_location_n",utc_maps_view_set_screen_location_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_screen_location_p",utc_maps_view_get_screen_location_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_screen_location_n",utc_maps_view_get_screen_location_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_move_p",utc_maps_view_move_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_move_n",utc_maps_view_move_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_resize_p",utc_maps_view_resize_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_resize_n",utc_maps_view_resize_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_visibility_p",utc_maps_view_set_visibility_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_visibility_n",utc_maps_view_set_visibility_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_visibility_p",utc_maps_view_get_visibility_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_visibility_n",utc_maps_view_get_visibility_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_event_cb_p",utc_maps_view_set_event_cb_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_event_cb_n",utc_maps_view_set_event_cb_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_unset_event_cb_p",utc_maps_view_unset_event_cb_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_unset_event_cb_n",utc_maps_view_unset_event_cb_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_gesture_enabled_p",utc_maps_view_set_gesture_enabled_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_gesture_enabled_n",utc_maps_view_set_gesture_enabled_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_gesture_enabled_p",utc_maps_view_get_gesture_enabled_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_gesture_enabled_n",utc_maps_view_get_gesture_enabled_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_scalebar_enabled_p",utc_maps_view_set_scalebar_enabled_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_scalebar_enabled_n",utc_maps_view_set_scalebar_enabled_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_scalebar_enabled_p",utc_maps_view_get_scalebar_enabled_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_get_scalebar_enabled_n",utc_maps_view_get_scalebar_enabled_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_add_object_p",utc_maps_view_add_object_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_add_object_n",utc_maps_view_add_object_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_remove_object_p",utc_maps_view_remove_object_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_remove_object_n",utc_maps_view_remove_object_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_remove_all_objects_p",utc_maps_view_remove_all_objects_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_remove_all_objects_n",utc_maps_view_remove_all_objects_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_foreach_object_p",utc_maps_view_foreach_object_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_foreach_object_n",utc_maps_view_foreach_object_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_min_zoom_level_p",utc_maps_view_set_min_zoom_level_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_min_zoom_level_n",utc_maps_view_set_min_zoom_level_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_max_zoom_level_p",utc_maps_view_set_max_zoom_level_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_set_max_zoom_level_n",utc_maps_view_set_max_zoom_level_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_capture_snapshot_p",utc_maps_view_capture_snapshot_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_capture_snapshot_n",utc_maps_view_capture_snapshot_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_destroy_p",utc_maps_view_destroy_p,utc_maps_view_startup,utc_maps_view_cleanup},
	{"utc_maps_view_destroy_n",utc_maps_view_destroy_n,utc_maps_view_startup,utc_maps_view_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CAPI-MAPS-SERVICE-NATIVE_H__
