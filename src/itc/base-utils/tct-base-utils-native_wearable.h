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
#ifndef __TCT_BASE-UTILS-NATIVE_H__
#define __TCT_BASE-UTILS-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_base_utils_ubrk_startup(void);
extern void ITs_base_utils_ubrk_cleanup(void);
extern void ITs_base_utils_ucalendar_startup(void);
extern void ITs_base_utils_ucalendar_cleanup(void);
extern void ITs_base_utils_udate_startup(void);
extern void ITs_base_utils_udate_cleanup(void);
extern void ITs_base_utils_udatepg_startup(void);
extern void ITs_base_utils_udatepg_cleanup(void);
extern void ITs_base_utils_enumeration_startup(void);
extern void ITs_base_utils_enumeration_cleanup(void);
extern void ITs_base_utils_uset_startup(void);
extern void ITs_base_utils_uset_cleanup(void);
extern void ITs_base_utils_unumber_startup(void);
extern void ITs_base_utils_unumber_cleanup(void);
extern void ITs_base_utils_ulocale_startup(void);
extern void ITs_base_utils_ulocale_cleanup(void);
extern void ITs_base_utils_timezone_startup(void);
extern void ITs_base_utils_timezone_cleanup(void);
extern void ITs_base_utils_uchar_startup(void);
extern void ITs_base_utils_uchar_cleanup(void);
extern void ITs_base_utils_ucollator_startup(void);
extern void ITs_base_utils_ucollator_cleanup(void);
extern void ITs_base_utils_unormalization_startup(void);
extern void ITs_base_utils_unormalization_cleanup(void);
extern void ITs_base_utils_usearch_startup(void);
extern void ITs_base_utils_usearch_cleanup(void);
extern void ITs_base_utils_ustring_startup(void);
extern void ITs_base_utils_ustring_cleanup(void);
extern void ITs_base_utils_field_position_startup(void);
extern void ITs_base_utils_field_position_cleanup(void);
extern void ITs_base_utils_format_startup(void);
extern void ITs_base_utils_format_cleanup(void);
extern void ITs_base_utils_measure_startup(void);
extern void ITs_base_utils_measure_cleanup(void);
extern void ITs_base_utils_measure_format_startup(void);
extern void ITs_base_utils_measure_format_cleanup(void);
extern void ITs_base_utils_measure_unit_startup(void);
extern void ITs_base_utils_measure_unit_cleanup(void);
extern void ITs_base_utils_parse_position_startup(void);
extern void ITs_base_utils_parse_position_cleanup(void);
extern void ITs_base_utils_alpha_startup(void);
extern void ITs_base_utils_alpha_cleanup(void);
extern void ITs_base_utils_formattable_startup(void);
extern void ITs_base_utils_formattable_cleanup(void);
extern void ITs_base_utils_utmscale_startup(void);
extern void ITs_base_utils_utmscale_cleanup(void);
extern void ITs_base_utils_ubidi_startup(void);
extern void ITs_base_utils_ubidi_cleanup(void);
extern void ITs_base_utils_uchar_iter_startup(void);
extern void ITs_base_utils_uchar_iter_cleanup(void);
extern void ITs_base_utils_uversion_startup(void);
extern void ITs_base_utils_uversion_cleanup(void);
extern void ITs_base_utils_plural_rules_startup(void);
extern void ITs_base_utils_plural_rules_cleanup(void);
extern void ITs_base_utils_immutable_idx_startup(void);
extern void ITs_base_utils_immutable_idx_cleanup(void);
extern void ITs_base_utils_plural_format_startup(void);
extern void ITs_base_utils_plural_format_cleanup(void);
extern void ITs_base_utils_date_interval_startup(void);
extern void ITs_base_utils_date_interval_cleanup(void);
extern void ITs_base_utils_date_interval_fmt_startup(void);
extern void ITs_base_utils_date_interval_fmt_cleanup(void);
extern void ITs_base_utils_simple_date_fmt_startup(void);
extern void ITs_base_utils_simple_date_fmt_cleanup(void);
extern void ITs_base_utils_loc_disp_names_startup(void);
extern void ITs_base_utils_loc_disp_names_cleanup(void);
extern void ITs_base_utils_utext_startup(void);
extern void ITs_base_utils_utext_cleanup(void);
extern void ITs_base_utils_uscript_startup(void);
extern void ITs_base_utils_uscript_cleanup(void);
extern void ITs_base_utils_unumsys_startup(void);
extern void ITs_base_utils_unumsys_cleanup(void);
extern void ITs_base_utils_uidna_startup(void);
extern void ITs_base_utils_uidna_cleanup(void);
extern void ITs_base_utils_ucsdet_startup(void);
extern void ITs_base_utils_ucsdet_cleanup(void);
extern void ITs_base_utils_ucnvsel_startup(void);
extern void ITs_base_utils_ucnvsel_cleanup(void);
extern void ITs_base_utils_ucnv_startup(void);
extern void ITs_base_utils_ucnv_cleanup(void);
extern void ITs_base_utils_ures_startup(void);
extern void ITs_base_utils_ures_cleanup(void);

extern int ITc_i18n_ubrk_create_destroy_p(void);
extern int ITc_i18n_ubrk_create_rules_p(void);
extern int ITc_i18n_ubrk_safe_clone_p(void);
extern int ITc_i18n_ubrk_set_text_p(void);
extern int ITc_i18n_ubrk_current_p(void);
extern int ITc_i18n_ubrk_next_previous_p(void);
extern int ITc_i18n_ubrk_first_last_p(void);
extern int ITc_i18n_ubrk_preceding_following_p(void);
extern int ITc_i18n_ubrk_get_available_p(void);
extern int ITc_i18n_ubrk_count_available_p(void);
extern int ITc_i18n_ubrk_is_boundary_p(void);
extern int ITc_i18n_ubrk_get_rule_status_p(void);
extern int ITc_i18n_ubrk_get_rule_status_vec_p(void);
extern int ITc_i18n_ubrk_get_locale_by_type_p(void);
extern int ITc_i18n_ucalendar_get_now_p(void);
extern int ITc_i18n_ucalendar_create_destroy_p(void);
extern int ITc_i18n_ucalendar_add_get_p(void);
extern int ITc_i18n_ucalendar_set_date_time_get_milliseconds_p(void);
extern int ITc_i18n_ucalendar_set_get_attribute_p(void);
extern int ITc_i18n_ucalendar_get_timezone_displayname_p(void);
extern int ITc_i18n_ucalendar_set_milliseconds_p(void);
extern int ITc_i18n_ucalendar_is_in_daylight_time_p(void);
extern int ITc_i18n_ucalendar_is_equivalent_to_p(void);
extern int ITc_i18n_ucalendar_clone_p(void);
extern int ITc_i18n_ucalendar_set_p(void);
extern int ITc_i18n_ucalendar_set_default_timezone_p(void);
extern int ITc_i18n_ucalendar_timezone_id_enumeration_create_p(void);
extern int ITc_i18n_ucalendar_timezones_create_p(void);
extern int ITc_i18n_ucalendar_country_timezones_create_p(void);
extern int ITc_i18n_ucalendar_get_default_timezone_p(void);
extern int ITc_i18n_ucalendar_set_timezone_p(void);
extern int ITc_i18n_ucalendar_get_timezone_id_get_canonical_timezone_id_p(void);
extern int ITc_i18n_ucalendar_set_get_gregorian_change_p(void);
extern int ITc_i18n_ucalendar_get_available_p(void);
extern int ITc_i18n_ucalendar_count_available_p(void);
extern int ITc_i18n_ucalendar_roll_p(void);
extern int ITc_i18n_ucalendar_is_set_p(void);
extern int ITc_i18n_ucalendar_clear_field_p(void);
extern int ITc_i18n_ucalendar_clear_p(void);
extern int ITc_i18n_ucalendar_get_limit_p(void);
extern int ITc_i18n_ucalendar_get_locale_by_type_p(void);
extern int ITc_i18n_ucalendar_get_tz_data_version_p(void);
extern int ITc_i18n_ucalendar_get_type_p(void);
extern int ITc_i18n_ucalendar_get_keyword_values_for_locale_p(void);
extern int ITc_i18n_ucalendar_get_day_of_week_type_p(void);
extern int ITc_i18n_ucalendar_get_weekend_transition_p(void);
extern int ITc_i18n_ucalendar_is_weekend_p(void);
extern int ITc_i18n_ucalendar_get_field_difference_p(void);
extern int ITc_i18n_ucalendar_get_timezone_transition_date_p(void);
extern int ITc_i18n_udate_create_destroy_p(void);
extern int ITc_i18n_udate_format_date_p(void);
extern int ITc_i18n_udate_to_calendar_date_field_p(void);
extern int ITc_i18n_udate_clone_p(void);
extern int ITc_i18n_udate_parse_p(void);
extern int ITc_i18n_udate_parse_calendar_p(void);
extern int ITc_i18n_udate_is_set_lenient_p(void);
extern int ITc_i18n_udate_get_set_calendar_p(void);
extern int ITc_i18n_udate_get_set_number_format_p(void);
extern int ITc_i18n_udate_get_set_2digit_year_start_p(void);
extern int ITc_i18n_udate_set_get_symbols_p(void);
extern int ITc_i18n_udate_get_available_p(void);
extern int ITc_i18n_udate_count_available_p(void);
extern int ITc_i18n_udate_apply_pattern_p(void);
extern int ITc_i18n_udate_apply_to_pattern_p(void);
extern int ITc_i18n_udate_count_symbols_p(void);
extern int ITc_i18n_udate_get_locale_by_type_p(void);
extern int ITc_i18n_udate_set_context_p(void);
extern int ITc_i18n_udatepg_create_destroy_p(void);
extern int ITc_i18n_udatepg_get_best_pattern_p(void);
extern int ITc_i18n_udatepg_set_get_decimal_p(void);
extern int ITc_i18n_udatepg_set_get_date_time_format_p(void);
extern int ITc_i18n_udatepg_set_get_append_item_name_p(void);
extern int ITc_i18n_udatepg_set_get_append_item_format_p(void);
extern int ITc_i18n_udatepg_replace_field_types_with_options_p(void);
extern int ITc_i18n_udatepg_replace_field_types_p(void);
extern int ITc_i18n_udatepg_get_skeleton_p(void);
extern int ITc_i18n_udatepg_get_best_pattern_with_options_p(void);
extern int ITc_i18n_udatepg_get_base_skeleton_p(void);
extern int ITc_i18n_udatepg_add_pattern_p(void);
extern int ITc_i18n_udatepg_get_pattern_for_skeleton_p(void);
extern int ITc_i18n_udatepg_skeletons_create_p(void);
extern int ITc_i18n_udatepg_base_skeletons_create_p(void);
extern int ITc_i18n_udatepg_create_empty_p(void);
extern int ITc_i18n_udatepg_clone_p(void);
extern int ITc_i18n_uenumeration_uchar_strings_enumeration_create_destroy_p(void);
extern int ITc_i18n_uenumeration_char_strings_enumeration_create_destroy_p(void);
extern int ITc_i18n_uenumeration_count_p(void);
extern int ITc_i18n_uenumeration_unext_p(void);
extern int ITc_i18n_uenumeration_next_p(void);
extern int ITc_i18n_uenumeration_reset_p(void);
extern int ITc_i18n_uset_create_empty_p(void);
extern int ITc_i18n_uset_create_destroy_p(void);
extern int ITc_i18n_uset_create_pattern_p(void);
extern int ITc_i18n_uset_create_pattern_options_p(void);
extern int ITc_i18n_uset_clone_p(void);
extern int ITc_i18n_uset_freeze_p(void);
extern int ITc_i18n_uset_is_frozen_p(void);
extern int ITc_i18n_uset_clone_as_thawed_p(void);
extern int ITc_i18n_uset_set_p(void);
extern int ITc_i18n_uset_apply_pattern_p(void);
extern int ITc_i18n_uset_apply_int_property_value_p(void);
extern int ITc_i18n_uset_apply_property_alias_p(void);
extern int ITc_i18n_uset_resembles_pattern_p(void);
extern int ITc_i18n_uset_to_pattern_p(void);
extern int ITc_i18n_uset_add_remove_p(void);
extern int ITc_i18n_uset_add_remove_all_p(void);
extern int ITc_i18n_uset_add_remove_range_p(void);
extern int ITc_i18n_uset_add_remove_string_p(void);
extern int ITc_i18n_uset_add_all_code_points_p(void);
extern int ITc_i18n_uset_retain_p(void);
extern int ITc_i18n_uset_retain_all_p(void);
extern int ITc_i18n_uset_compact_p(void);
extern int ITc_i18n_uset_complement_p(void);
extern int ITc_i18n_uset_complement_all_p(void);
extern int ITc_i18n_uset_clear_p(void);
extern int ITc_i18n_uset_destroy_over_p(void);
extern int ITc_i18n_uset_remove_all_strings_p(void);
extern int ITc_i18n_uset_is_empty_p(void);
extern int ITc_i18n_uset_contains_p(void);
extern int ITc_i18n_uset_contains_range_p(void);
extern int ITc_i18n_uset_contains_string_p(void);
extern int ITc_i18n_uset_index_of_p(void);
extern int ITc_i18n_uset_char_at_p(void);
extern int ITc_i18n_uset_size_p(void);
extern int ITc_i18n_uset_get_item_count_p(void);
extern int ITc_i18n_uset_get_item_p(void);
extern int ITc_i18n_uset_contains_all_p(void);
extern int ITc_i18n_uset_contains_all_code_points_p(void);
extern int ITc_i18n_uset_contains_none_p(void);
extern int ITc_i18n_uset_contains_some_p(void);
extern int ITc_i18n_uset_span_p(void);
extern int ITc_i18n_uset_span_back_p(void);
extern int ITc_i18n_uset_span_utf8_p(void);
extern int ITc_i18n_uset_span_back_utf8_p(void);
extern int ITc_i18n_uset_equals_p(void);
extern int ITc_i18n_uset_serialize_p(void);
extern int ITc_i18n_uset_get_serialized_set_p(void);
extern int ITc_i18n_uset_set_serialized_to_one_p(void);
extern int ITc_i18n_uset_serialized_contains_p(void);
extern int ITc_i18n_uset_get_serialized_range_count_p(void);
extern int ITc_i18n_uset_get_serialized_range_p(void);
extern int ITc_i18n_unumber_get_symbol_p(void);
extern int ITc_i18n_unumber_create_destroy_p(void);
extern int ITc_i18n_unumber_apply_pattern_p(void);
extern int ITc_i18n_unumber_clone_p(void);
extern int ITc_i18n_unumber_count_available_p(void);
extern int ITc_i18n_unumber_format_decimal_p(void);
extern int ITc_i18n_unumber_format_double_p(void);
extern int ITc_i18n_unumber_format_double_currency_p(void);
extern int ITc_i18n_unumber_format_int64_p(void);
extern int ITc_i18n_unumber_set_get_attribute_p(void);
extern int ITc_i18n_unumber_get_available_p(void);
extern int ITc_i18n_unumber_set_get_double_attribute_p(void);
extern int ITc_i18n_unumber_get_locale_by_type_p(void);
extern int ITc_i18n_unumber_set_get_text_attribute_p(void);
extern int ITc_i18n_unumber_parse_p(void);
extern int ITc_i18n_unumber_parse_decimal_p(void);
extern int ITc_i18n_unumber_parse_double_p(void);
extern int ITc_i18n_unumber_parse_double_currency_p(void);
extern int ITc_i18n_unumber_parse_int64_p(void);
extern int ITc_i18n_unumber_to_pattern_p(void);
extern int ITc_i18n_unumber_set_get_symbol_p(void);
extern int ITc_i18n_ulocale_get_language_p(void);
extern int ITc_i18n_ulocale_get_display_name_p(void);
extern int ITc_i18n_ulocale_set_get_default_p(void);
extern int ITc_i18n_ulocale_get_available_p(void);
extern int ITc_i18n_ulocale_get_country_p(void);
extern int ITc_i18n_ulocale_count_available_p(void);
extern int ITc_i18n_ulocale_add_likely_subtags_p(void);
extern int ITc_i18n_ulocale_canonicalize_p(void);
extern int ITc_i18n_ulocale_for_language_tag_p(void);
extern int ITc_i18n_ulocale_get_base_name_p(void);
extern int ITc_i18n_ulocale_get_character_orientation_p(void);
extern int ITc_i18n_ulocale_get_display_country_p(void);
extern int ITc_i18n_ulocale_get_display_keyword_p(void);
extern int ITc_i18n_ulocale_get_display_keyword_value_p(void);
extern int ITc_i18n_ulocale_get_display_language_p(void);
extern int ITc_i18n_ulocale_get_display_script_p(void);
extern int ITc_i18n_ulocale_get_display_variant_p(void);
extern int ITc_i18n_ulocale_get_iso3_country_p(void);
extern int ITc_i18n_ulocale_get_iso3_language_p(void);
extern int ITc_i18n_ulocale_get_iso_countries_p(void);
extern int ITc_i18n_ulocale_get_iso_languages_p(void);
extern int ITc_i18n_ulocale_set_get_keyword_value_p(void);
extern int ITc_i18n_ulocale_get_lcid_p(void);
extern int ITc_i18n_ulocale_get_line_orientation_p(void);
extern int ITc_i18n_ulocale_get_locale_for_lcid_p(void);
extern int ITc_i18n_ulocale_get_name_p(void);
extern int ITc_i18n_ulocale_get_parent_p(void);
extern int ITc_i18n_ulocale_get_script_p(void);
extern int ITc_i18n_ulocale_get_variant_p(void);
extern int ITc_i18n_ulocale_keywords_create_p(void);
extern int ITc_i18n_ulocale_minimize_subtags_p(void);
extern int ITc_i18n_ulocale_to_language_tag_p(void);
extern int ITc_i18n_timezone_create_unknown_p(void);
extern int ITc_i18n_timezone_create_gmt_p(void);
extern int ITc_i18n_timezone_create_destroy_p(void);
extern int ITc_i18n_timezone_count_equivalent_ids_p(void);
extern int ITc_i18n_timezone_get_equivalent_id_p(void);
extern int ITc_i18n_timezone_create_default_p(void);
extern int ITc_i18n_timezone_set_default_p(void);
extern int ITc_i18n_timezone_get_tzdata_version_p(void);
extern int ITc_i18n_timezone_get_region_p(void);
extern int ITc_i18n_timezone_get_offset_with_date_p(void);
extern int ITc_i18n_timezone_set_get_raw_offset_p(void);
extern int ITc_i18n_timezone_set_get_id_p(void);
extern int ITc_i18n_timezone_get_display_name_p(void);
extern int ITc_i18n_timezone_get_display_name_with_locale_id_p(void);
extern int ITc_i18n_timezone_get_display_name_with_type_p(void);
extern int ITc_i18n_timezone_get_display_name_with_type_locale_id_p(void);
extern int ITc_i18n_timezone_use_daylight_time_p(void);
extern int ITc_i18n_timezone_has_same_rule_p(void);
extern int ITc_i18n_timezone_clone_p(void);
extern int ITc_i18n_timezone_get_dst_savings_p(void);
extern int ITc_i18n_timezone_foreach_timezone_id_by_region_p(void);
extern int ITc_i18n_timezone_foreach_timezone_id_p(void);
extern int ITc_i18n_timezone_foreach_timezone_id_with_offset_p(void);
extern int ITc_i18n_timezone_foreach_timezone_id_by_country_p(void);
extern int ITc_i18n_timezone_detect_host_timezone_p(void);
extern int ITc_i18n_uchar_get_int_property_value_p(void);
extern int ITc_i18n_uchar_get_ublock_code_p(void);
extern int ITc_i18n_ucollator_create_destroy_p(void);
extern int ITc_i18n_ucollator_str_collator_p(void);
extern int ITc_i18n_ucollator_equal_p(void);
extern int ITc_i18n_ucollator_set_strength_p(void);
extern int ITc_i18n_ucollator_set_attribute_p(void);
extern int ITc_i18n_ucollator_create_rules_p(void);
extern int ITc_i18n_ucollator_get_contractions_and_expansions_p(void);
extern int ITc_i18n_ucollator_str_collator_utf8_p(void);
extern int ITc_i18n_ucollator_greater_p(void);
extern int ITc_i18n_ucollator_greater_or_equal_p(void);
extern int ITc_i18n_ucollator_str_collator_iter_p(void);
extern int ITc_i18n_ucollator_get_strength_p(void);
extern int ITc_i18n_ucollator_get_reorder_codes_p(void);
extern int ITc_i18n_ucollator_set_reorder_codes_p(void);
extern int ITc_i18n_ucollator_get_display_name_p(void);
extern int ITc_i18n_ucollator_get_available_p(void);
extern int ITc_i18n_ucollator_count_available_p(void);
extern int ITc_i18n_ucollator_create_available_locales_p(void);
extern int ITc_i18n_ucollator_get_keywords_p(void);
extern int ITc_i18n_ucollator_get_keyword_values_p(void);
extern int ITc_i18n_ucollator_get_keyword_values_for_locale_p(void);
extern int ITc_i18n_ucollator_get_functional_equivalent_p(void);
extern int ITc_i18n_ucollator_get_rules_p(void);
extern int ITc_i18n_ucollator_get_sort_key_p(void);
extern int ITc_i18n_ucollator_next_sort_key_part_p(void);
extern int ITc_i18n_ucollator_get_bound_p(void);
extern int ITc_i18n_ucollator_get_version_p(void);
extern int ITc_i18n_ucollator_get_uca_version_p(void);
extern int ITc_i18n_ucollator_merge_sort_keys_p(void);
extern int ITc_i18n_ucollator_get_attribute_p(void);
extern int ITc_i18n_ucollator_set_get_max_variable_p(void);
extern int ITc_i18n_ucollator_get_variable_top_p(void);
extern int ITc_i18n_ucollator_safe_clone_p(void);
extern int ITc_i18n_ucollator_get_rules_ex_p(void);
extern int ITc_i18n_ucollator_get_locale_by_type_p(void);
extern int ITc_i18n_ucollator_get_tailored_set_p(void);
extern int ITc_i18n_ucollator_clone_binary_p(void);
extern int ITc_i18n_ucollator_create_binary_p(void);
extern int ITc_i18n_unormalization_get_instance_normalize_p(void);
extern int ITc_i18n_usearch_first_get_macthed_text_p(void);
extern int ITc_i18n_usearch_get_collator_p(void);
extern int ITc_i18n_usearch_create_new_p(void);
extern int ITc_i18n_ustring_copy_compare_p(void);
extern int ITc_i18n_ustring_get_length_to_upper_p(void);
extern int ITc_i18n_ustring_from_UTF8_to_UTF8_p(void);
extern int ITc_i18n_ustring_copy_au_p(void);
extern int ITc_i18n_ustring_copy_au_n_p(void);
extern int ITc_i18n_ustring_copy_ua_n_p(void);
extern int ITc_i18n_ustring_copy_ua_p(void);
extern int ITc_i18n_ustring_copy_n_p(void);
extern int ITc_i18n_ustring_to_upper_p(void);
extern int ITc_i18n_ustring_count_char32_p(void);
extern int ITc_i18n_ustring_has_more_char32_than_p(void);
extern int ITc_i18n_ustring_cat_p(void);
extern int ITc_i18n_ustring_cat_n_p(void);
extern int ITc_i18n_ustring_string_p(void);
extern int ITc_i18n_ustring_find_first_p(void);
extern int ITc_i18n_ustring_char_p(void);
extern int ITc_i18n_ustring_char32_p(void);
extern int ITc_i18n_ustring_r_string_p(void);
extern int ITc_i18n_ustring_find_last_p(void);
extern int ITc_i18n_ustring_r_char_p(void);
extern int ITc_i18n_ustring_r_char32_p(void);
extern int ITc_i18n_ustring_pbrk_p(void);
extern int ITc_i18n_ustring_cspn_p(void);
extern int ITc_i18n_ustring_spn_p(void);
extern int ITc_i18n_ustring_tokenizer_r_p(void);
extern int ITc_i18n_ustring_compare_code_point_order_p(void);
extern int ITc_i18n_ustring_compare_binary_order_p(void);
extern int ITc_i18n_ustring_case_compare_with_length_p(void);
extern int ITc_i18n_ustring_compare_n_p(void);
extern int ITc_i18n_ustring_compare_n_code_point_order_p(void);
extern int ITc_i18n_ustring_case_compare_p(void);
extern int ITc_i18n_ustring_case_compare_n_p(void);
extern int ITc_i18n_ustring_mem_case_compare_p(void);
extern int ITc_i18n_ustring_mem_copy_p(void);
extern int ITc_i18n_ustring_mem_move_p(void);
extern int ITc_i18n_ustring_mem_set_p(void);
extern int ITc_i18n_ustring_mem_compare_p(void);
extern int ITc_i18n_ustring_mem_compare_code_point_order_p(void);
extern int ITc_i18n_ustring_mem_char_p(void);
extern int ITc_i18n_ustring_mem_char32_p(void);
extern int ITc_i18n_ustring_mem_r_char_p(void);
extern int ITc_i18n_ustring_mem_r_char32_p(void);
extern int ITc_i18n_ustring_unescape_p(void);
extern int ITc_i18n_ustring_unescape_at_p(void);
extern int ITc_i18n_ustring_to_lower_p(void);
extern int ITc_i18n_ustring_fold_case_p(void);
extern int ITc_i18n_ustring_to_WCS_p(void);
extern int ITc_i18n_ustring_from_WCS_p(void);
extern int ITc_i18n_ustring_to_UTF8_with_sub_p(void);
extern int ITc_i18n_ustring_from_UTF8_with_sub_p(void);
extern int ITc_i18n_ustring_from_UTF8_lenient_p(void);
extern int ITc_i18n_ustring_to_UTF32_p(void);
extern int ITc_i18n_ustring_from_UTF32_p(void);
extern int ITc_i18n_ustring_from_UTF32_with_sub_p(void);
extern int ITc_i18n_ustring_to_UTF32_with_sub_p(void);
extern int ITc_i18n_ustring_to_title_new_p(void);
extern int ITc_i18n_ushape_shape_arabic_p(void);
extern int ITc_i18n_field_position_create_destroy_p(void);
extern int ITc_i18n_field_position_create_set_get_for_field_p(void);
extern int ITc_i18n_field_position_clone_p(void);
extern int ITc_i18n_field_position_set_get_begin_index_p(void);
extern int ITc_i18n_field_position_set_get_end_index_p(void);
extern int ITc_i18n_format_format_p(void);
extern int ITc_i18n_format_clone_destroy_p(void);
extern int ITc_i18n_format_format_with_field_position_p(void);
extern int ITc_i18n_format_parse_object_p(void);
extern int ITc_i18n_format_parse_object_with_parse_position_p(void);
extern int ITc_i18n_format_get_locale_id_p(void);
extern int ITc_i18n_measure_create_destroy_p(void);
extern int ITc_i18n_measure_clone_p(void);
extern int ITc_i18n_measure_get_number_p(void);
extern int ITc_i18n_measure_get_unit_p(void);
extern int ITc_i18n_measure_format_create_destroy_from_locale_id_p(void);
extern int ITc_i18n_measure_format_clone_p(void);
extern int ITc_i18n_measure_format_format_p(void);
extern int ITc_i18n_measure_format_parse_object_p(void);
extern int ITc_i18n_measure_format_create_currency_format_from_locale_id_p(void);
extern int ITc_i18n_measure_format_create_currency_format_p(void);
extern int ITc_i18n_measure_unit_create_destroy_p(void);
extern int ITc_i18n_measure_unit_clone_p(void);
extern int ITc_i18n_measure_unit_get_available_destroy_p(void);
extern int ITc_i18n_measure_unit_get_available_with_type_p(void);
extern int ITc_i18n_measure_unit_foreach_available_type_p(void);
extern int ITc_i18n_measure_unit_create_g_force_p(void);
extern int ITc_i18n_measure_unit_create_meter_per_second_squared_p(void);
extern int ITc_i18n_measure_unit_create_arc_minute_p(void);
extern int ITc_i18n_measure_unit_create_arc_second_p(void);
extern int ITc_i18n_measure_unit_create_degree_p(void);
extern int ITc_i18n_measure_unit_create_radian_p(void);
extern int ITc_i18n_measure_unit_create_acre_p(void);
extern int ITc_i18n_measure_unit_create_hectare_p(void);
extern int ITc_i18n_measure_unit_create_square_centimeter_p(void);
extern int ITc_i18n_measure_unit_create_square_foot_p(void);
extern int ITc_i18n_measure_unit_create_square_inch_p(void);
extern int ITc_i18n_measure_unit_create_square_kilometer_p(void);
extern int ITc_i18n_measure_unit_create_square_meter_p(void);
extern int ITc_i18n_measure_unit_create_square_mile_p(void);
extern int ITc_i18n_measure_unit_create_square_yard_p(void);
extern int ITc_i18n_measure_unit_create_liter_per_kilometer_p(void);
extern int ITc_i18n_measure_unit_create_mile_per_gallon_p(void);
extern int ITc_i18n_measure_unit_create_bit_p(void);
extern int ITc_i18n_measure_unit_create_byte_p(void);
extern int ITc_i18n_measure_unit_create_gigabit_p(void);
extern int ITc_i18n_measure_unit_create_gigabyte_p(void);
extern int ITc_i18n_measure_unit_create_kilobit_p(void);
extern int ITc_i18n_measure_unit_create_kilobyte_p(void);
extern int ITc_i18n_measure_unit_create_megabit_p(void);
extern int ITc_i18n_measure_unit_create_megabyte_p(void);
extern int ITc_i18n_measure_unit_create_terabit_p(void);
extern int ITc_i18n_measure_unit_create_terabyte_p(void);
extern int ITc_i18n_measure_unit_create_day_p(void);
extern int ITc_i18n_measure_unit_create_hour_p(void);
extern int ITc_i18n_measure_unit_create_microsecond_p(void);
extern int ITc_i18n_measure_unit_create_millisecond_p(void);
extern int ITc_i18n_measure_unit_create_minute_p(void);
extern int ITc_i18n_measure_unit_create_month_p(void);
extern int ITc_i18n_measure_unit_create_nanosecond_p(void);
extern int ITc_i18n_measure_unit_create_second_p(void);
extern int ITc_i18n_measure_unit_create_week_p(void);
extern int ITc_i18n_measure_unit_create_year_p(void);
extern int ITc_i18n_measure_unit_create_ampere_p(void);
extern int ITc_i18n_measure_unit_create_milliampere_p(void);
extern int ITc_i18n_measure_unit_create_ohm_p(void);
extern int ITc_i18n_measure_unit_create_volt_p(void);
extern int ITc_i18n_measure_unit_create_calorie_p(void);
extern int ITc_i18n_measure_unit_create_foodcalorie_p(void);
extern int ITc_i18n_measure_unit_create_joule_p(void);
extern int ITc_i18n_measure_unit_create_kilocalorie_p(void);
extern int ITc_i18n_measure_unit_create_kilojoule_p(void);
extern int ITc_i18n_measure_unit_create_kilowatt_hour_p(void);
extern int ITc_i18n_measure_unit_create_gigahertz_p(void);
extern int ITc_i18n_measure_unit_create_hertz_p(void);
extern int ITc_i18n_measure_unit_create_kilohertz_p(void);
extern int ITc_i18n_measure_unit_create_megahertz_p(void);
extern int ITc_i18n_measure_unit_create_astronomical_unit_p(void);
extern int ITc_i18n_measure_unit_create_centimeter_p(void);
extern int ITc_i18n_measure_unit_create_decimeter_p(void);
extern int ITc_i18n_measure_unit_create_fathom_p(void);
extern int ITc_i18n_measure_unit_create_foot_p(void);
extern int ITc_i18n_measure_unit_create_furlong_p(void);
extern int ITc_i18n_measure_unit_create_inch_p(void);
extern int ITc_i18n_measure_unit_create_kilometer_p(void);
extern int ITc_i18n_measure_unit_create_light_year_p(void);
extern int ITc_i18n_measure_unit_create_meter_p(void);
extern int ITc_i18n_measure_unit_create_micrometer_p(void);
extern int ITc_i18n_measure_unit_create_mile_p(void);
extern int ITc_i18n_measure_unit_create_millimeter_p(void);
extern int ITc_i18n_measure_unit_create_nanometer_p(void);
extern int ITc_i18n_measure_unit_create_nautical_mile_p(void);
extern int ITc_i18n_measure_unit_create_parsec_p(void);
extern int ITc_i18n_measure_unit_create_picometer_p(void);
extern int ITc_i18n_measure_unit_create_yard_p(void);
extern int ITc_i18n_measure_unit_create_lux_p(void);
extern int ITc_i18n_measure_unit_create_carat_p(void);
extern int ITc_i18n_measure_unit_create_gram_p(void);
extern int ITc_i18n_measure_unit_create_kilogram_p(void);
extern int ITc_i18n_measure_unit_create_metric_ton_p(void);
extern int ITc_i18n_measure_unit_create_microgram_p(void);
extern int ITc_i18n_measure_unit_create_milligram_p(void);
extern int ITc_i18n_measure_unit_create_ounce_p(void);
extern int ITc_i18n_measure_unit_create_ounce_troy_p(void);
extern int ITc_i18n_measure_unit_create_pound_p(void);
extern int ITc_i18n_measure_unit_create_stone_p(void);
extern int ITc_i18n_measure_unit_create_ton_p(void);
extern int ITc_i18n_measure_unit_create_gigawatt_p(void);
extern int ITc_i18n_measure_unit_create_horsepower_p(void);
extern int ITc_i18n_measure_unit_create_kilowatt_p(void);
extern int ITc_i18n_measure_unit_create_megawatt_p(void);
extern int ITc_i18n_measure_unit_create_milliwatt_p(void);
extern int ITc_i18n_measure_unit_create_watt_p(void);
extern int ITc_i18n_measure_unit_create_hectopascal_p(void);
extern int ITc_i18n_measure_unit_create_inch_hg_p(void);
extern int ITc_i18n_measure_unit_create_millibar_p(void);
extern int ITc_i18n_measure_unit_create_millimeter_of_mercury_p(void);
extern int ITc_i18n_measure_unit_create_pound_per_square_inch_p(void);
extern int ITc_i18n_measure_unit_create_karat_p(void);
extern int ITc_i18n_measure_unit_create_kilometer_per_hour_p(void);
extern int ITc_i18n_measure_unit_create_meter_per_second_p(void);
extern int ITc_i18n_measure_unit_create_mile_per_hour_p(void);
extern int ITc_i18n_measure_unit_create_celsius_p(void);
extern int ITc_i18n_measure_unit_create_fahrenheit_p(void);
extern int ITc_i18n_measure_unit_create_kelvin_p(void);
extern int ITc_i18n_measure_unit_create_acre_foot_p(void);
extern int ITc_i18n_measure_unit_create_bushel_p(void);
extern int ITc_i18n_measure_unit_create_centiliter_p(void);
extern int ITc_i18n_measure_unit_create_cubic_centimeter_p(void);
extern int ITc_i18n_measure_unit_create_cubic_foot_p(void);
extern int ITc_i18n_measure_unit_create_cubic_inch_p(void);
extern int ITc_i18n_measure_unit_create_cubic_kilometer_p(void);
extern int ITc_i18n_measure_unit_create_cubic_meter_p(void);
extern int ITc_i18n_measure_unit_create_cubic_mile_p(void);
extern int ITc_i18n_measure_unit_create_cubic_yard_p(void);
extern int ITc_i18n_measure_unit_create_cup_p(void);
extern int ITc_i18n_measure_unit_create_deciliter_p(void);
extern int ITc_i18n_measure_unit_create_fluid_ounce_p(void);
extern int ITc_i18n_measure_unit_create_gallon_p(void);
extern int ITc_i18n_measure_unit_create_hectoliter_p(void);
extern int ITc_i18n_measure_unit_create_liter_p(void);
extern int ITc_i18n_measure_unit_create_megaliter_p(void);
extern int ITc_i18n_measure_unit_create_milliliter_p(void);
extern int ITc_i18n_measure_unit_create_pint_p(void);
extern int ITc_i18n_measure_unit_create_quart_p(void);
extern int ITc_i18n_measure_unit_create_tablespoon_p(void);
extern int ITc_i18n_measure_unit_create_teaspoon_p(void);
extern int ITc_i18n_parse_position_create_destroy_p(void);
extern int ITc_i18n_parse_position_create_with_index_p(void);
extern int ITc_i18n_parse_position_set_get_index_p(void);
extern int ITc_i18n_parse_position_clone_p(void);
extern int ITc_i18n_parse_position_set_get_error_index_p(void);
extern int ITc_i18n_alpha_idx_create_destroy_from_locale_id_p(void);
extern int ITc_i18n_alpha_idx_add_labels_with_locale_id_p(void);
extern int ITc_i18n_alpha_idx_add_record_p(void);
extern int ITc_i18n_alpha_idx_get_record_name_p(void);
extern int ITc_i18n_alpha_idx_get_next_bucket_p(void);
extern int ITc_i18n_alpha_idx_get_next_record_p(void);
extern int ITc_i18n_alpha_idx_get_bucket_record_count_p(void);
extern int ITc_i18n_alpha_idx_get_bucket_label_p(void);
extern int ITc_i18n_alpha_idx_get_record_data_p(void);
extern int ITc_i18n_alpha_idx_set_get_inflow_label_p(void);
extern int ITc_i18n_alpha_idx_set_get_overflow_label_p(void);
extern int ITc_i18n_alpha_idx_set_get_underflow_label_p(void);
extern int ITc_i18n_alpha_idx_set_get_max_label_count_p(void);
extern int ITc_i18n_alpha_idx_get_bucket_count_p(void);
extern int ITc_i18n_alpha_idx_get_record_count_p(void);
extern int ITc_i18n_alpha_idx_get_bucket_index_p(void);
extern int ITc_i18n_alpha_idx_get_current_bucket_index_p(void);
extern int ITc_i18n_alpha_idx_get_bucket_label_type_p(void);
extern int ITc_i18n_alpha_idx_reset_bucket_iter_p(void);
extern int ITc_i18n_alpha_idx_reset_record_iter_p(void);
extern int ITc_i18n_alpha_idx_clear_records_p(void);
extern int ITc_i18n_formattable_create_default_destroy_p(void);
extern int ITc_i18n_formattable_create_with_udate_p(void);
extern int ITc_i18n_formattable_create_with_double_p(void);
extern int ITc_i18n_formattable_create_with_long_p(void);
extern int ITc_i18n_formattable_create_with_int64_p(void);
extern int ITc_i18n_formattable_create_with_char_string_p(void);
extern int ITc_i18n_formattable_create_with_formattable_array_p(void);
extern int ITc_i18n_formattable_clone_p(void);
extern int ITc_i18n_formattable_set_get_array_p(void);
extern int ITc_i18n_formattable_set_get_date_p(void);
extern int ITc_i18n_formattable_set_get_double_p(void);
extern int ITc_i18n_formattable_set_get_int64_p(void);
extern int ITc_i18n_formattable_set_get_long_p(void);
extern int ITc_i18n_formattable_set_get_string_p(void);
extern int ITc_i18n_formattable_get_type_p(void);
extern int ITc_i18n_formattable_is_numeric_p(void);
extern int ITc_i18n_formattable_not_equal_p(void);
extern int ITc_i18n_formattable_equal_p(void);
extern int ITc_i18n_formattable_element_at_p(void);
extern int ITc_i18n_utmscale_get_time_scale_value_p(void);
extern int ITc_i18n_utmscale_from_int64_p(void);
extern int ITc_i18n_utmscale_to_int64_p(void);
extern int ITc_i18n_ubidi_create_destroy_p(void);
extern int ITc_i18n_ubidi_count_paragraphs_p(void);
extern int ITc_i18n_ubidi_count_runs_p(void);
extern int ITc_i18n_ubidi_get_base_direction_p(void);
extern int ITc_i18n_ubidi_set_get_class_cb_p(void);
extern int ITc_i18n_ubidi_set_context_p(void);
extern int ITc_i18n_ubidi_set_inverse_p(void);
extern int ITc_i18n_ubidi_set_line_p(void);
extern int ITc_i18n_ubidi_set_para_p(void);
extern int ITc_i18n_ubidi_set_get_reordering_mode_p(void);
extern int ITc_i18n_ubidi_set_get_reordering_options_p(void);
extern int ITc_i18n_ubidi_get_customized_class_p(void);
extern int ITc_i18n_ubidi_get_direction_p(void);
extern int ITc_i18n_ubidi_get_length_p(void);
extern int ITc_i18n_ubidi_get_level_at_p(void);
extern int ITc_i18n_ubidi_get_logical_index_p(void);
extern int ITc_i18n_ubidi_get_logical_map_p(void);
extern int ITc_i18n_ubidi_get_logical_run_p(void);
extern int ITc_i18n_ubidi_get_paragraph_p(void);
extern int ITc_i18n_ubidi_get_paragraph_by_index_p(void);
extern int ITc_i18n_ubidi_get_para_level_p(void);
extern int ITc_i18n_ubidi_get_processed_length_p(void);
extern int ITc_i18n_ubidi_get_result_length_p(void);
extern int ITc_i18n_ubidi_get_text_p(void);
extern int ITc_i18n_ubidi_get_visual_index_p(void);
extern int ITc_i18n_ubidi_get_visual_map_p(void);
extern int ITc_i18n_ubidi_get_visual_run_p(void);
extern int ITc_i18n_ubidi_invert_map_p(void);
extern int ITc_i18n_ubidi_is_inverse_p(void);
extern int ITc_i18n_ubidi_is_order_paragraphs_ltr_p(void);
extern int ITc_i18n_ubidi_create_sized_p(void);
extern int ITc_i18n_ubidi_order_paragraphs_ltr_p(void);
extern int ITc_i18n_ubidi_reorder_logical_p(void);
extern int ITc_i18n_ubidi_reorder_visual_p(void);
extern int ITc_i18n_ubidi_write_reordered_p(void);
extern int ITc_i18n_ubidi_write_reverse_p(void);
extern int ITc_i18n_uchar_iter_create_destroy_p(void);
extern int ITc_i18n_uchar_iter_set_string_p(void);
extern int ITc_i18n_uchar_iter_set_utf16be_p(void);
extern int ITc_i18n_uchar_iter_set_utf8_p(void);
extern int ITc_i18n_uchar_iter_get_index_p(void);
extern int ITc_i18n_uchar_iter_move_p(void);
extern int ITc_i18n_uchar_iter_has_next_p(void);
extern int ITc_i18n_uchar_iter_has_previous_p(void);
extern int ITc_i18n_uchar_iter_current_p(void);
extern int ITc_i18n_uchar_iter_next_p(void);
extern int ITc_i18n_uchar_iter_previous_p(void);
extern int ITc_i18n_uchar_iter_get_set_state_p(void);
extern int ITc_base_utils_i18n_uversion_get_version_p(void);
extern int ITc_base_utils_i18n_uversion_to_string_p(void);
extern int ITc_base_utils_i18n_uversion_from_string_p(void);
extern int ITc_base_utils_i18n_uversion_from_ustring_p(void);
extern int ITc_i18n_measure_format_format_buff_p(void);
extern int ITc_i18n_measure_format_format_measures_p(void);
extern int ITc_i18n_measure_format_format_measure_per_unit_p(void);
extern int ITc_i18n_uchar_has_binary_property_p(void);
extern int ITc_i18n_uchar_is_alphabetic_p(void);
extern int ITc_i18n_uchar_is_lowercase_p(void);
extern int ITc_i18n_uchar_is_uppercase_p(void);
extern int ITc_i18n_uchar_is_white_space_p(void);
extern int ITc_i18n_uchar_get_int_property_min_value_p(void);
extern int ITc_i18n_uchar_get_int_property_max_value_p(void);
extern int ITc_i18n_uchar_get_numeric_value_p(void);
extern int ITc_i18n_uchar_is_lower_p(void);
extern int ITc_i18n_uchar_is_upper_p(void);
extern int ITc_i18n_uchar_is_title_p(void);
extern int ITc_i18n_uchar_is_digit_p(void);
extern int ITc_i18n_uchar_is_alpha_p(void);
extern int ITc_i18n_uchar_is_alnum_p(void);
extern int ITc_i18n_uchar_is_xdigit_p(void);
extern int ITc_i18n_uchar_is_punct_p(void);
extern int ITc_i18n_uchar_is_graph_p(void);
extern int ITc_i18n_uchar_is_blank_p(void);
extern int ITc_i18n_uchar_is_defined_p(void);
extern int ITc_i18n_uchar_is_space_p(void);
extern int ITc_i18n_uchar_is_java_space_char_p(void);
extern int ITc_i18n_uchar_is_whitespace_p(void);
extern int ITc_i18n_uchar_is_control_p(void);
extern int ITc_i18n_uchar_is_iso_control_p(void);
extern int ITc_i18n_uchar_is_printable_p(void);
extern int ITc_i18n_uchar_is_base_p(void);
extern int ITc_i18n_uchar_char_direction_p(void);
extern int ITc_i18n_uchar_is_mirrored_p(void);
extern int ITc_i18n_uchar_char_mirror_p(void);
extern int ITc_i18n_uchar_get_bidi_paired_bracket_p(void);
extern int ITc_i18n_uchar_char_type_p(void);
extern int ITc_i18n_uchar_enum_char_types_p(void);
extern int ITc_i18n_uchar_get_combining_class_p(void);
extern int ITc_i18n_uchar_char_digit_value_p(void);
extern int ITc_i18n_uchar_char_name_p(void);
extern int ITc_i18n_uchar_char_from_name_p(void);
extern int ITc_i18n_uchar_enum_char_names_p(void);
extern int ITc_i18n_uchar_get_property_name_p(void);
extern int ITc_i18n_uchar_get_property_enum_p(void);
extern int ITc_i18n_uchar_get_property_value_name_p(void);
extern int ITc_i18n_uchar_get_property_value_enum_p(void);
extern int ITc_i18n_uchar_is_id_start_p(void);
extern int ITc_i18n_uchar_is_id_part_p(void);
extern int ITc_i18n_uchar_is_id_ignorable_p(void);
extern int ITc_i18n_uchar_is_java_id_start_p(void);
extern int ITc_i18n_uchar_is_java_id_part_p(void);
extern int ITc_i18n_uchar_to_lower_p(void);
extern int ITc_i18n_uchar_to_upper_p(void);
extern int ITc_i18n_uchar_to_title_p(void);
extern int ITc_i18n_uchar_fold_case_p(void);
extern int ITc_i18n_uchar_digit_p(void);
extern int ITc_i18n_uchar_for_digit_p(void);
extern int ITc_i18n_uchar_char_age_p(void);
extern int ITc_i18n_uchar_get_unicode_version_p(void);
extern int ITc_i18n_uchar_get_fc_nfkc_closure_p(void);
extern int ITc_i18n_ulocale_is_bogus_p(void);
extern int ITc_i18n_plural_rules_create_destroy_p(void);
extern int ITc_i18n_plural_rules_clone_p(void);
extern int ITc_i18n_plural_rules_create_rules_from_descr_p(void);
extern int ITc_i18n_plural_rules_for_locale_id_p(void);
extern int ITc_i18n_plural_rules_select_int32_p(void);
extern int ITc_i18n_plural_rules_select_double_p(void);
extern int ITc_i18n_plural_rules_get_keywords_p(void);
extern int ITc_i18n_plural_rules_get_samples_p(void);
extern int ITc_i18n_plural_rules_is_keyword_p(void);
extern int ITc_i18n_plural_rules_get_keyword_other_p(void);
extern int ITc_i18n_immutable_idx_create_destroy(void);
extern int ITc_i18n_immutable_idx_get_bucket_count(void);
extern int ITc_i18n_immutable_idx_get_bucket_index(void);
extern int ITc_i18n_immutable_idx_get_bucket_label(void);
extern int ITc_i18n_immutable_idx_get_bucket_label_type(void);
extern int ITc_i18n_measure_format_get_unit_display_name(void);
extern int ITc_i18n_plural_format_create_destroy_p(void);
extern int ITc_i18n_plural_format_create_from_locale_p(void);
extern int ITc_i18n_plural_format_create_from_rules_pattern_p(void);
extern int ITc_i18n_plural_format_create_from_locale_type_pattern_p(void);
extern int ITc_i18n_plural_format_create_from_locale_type_p(void);
extern int ITc_i18n_plural_format_create_from_locale_pattern_p(void);
extern int ITc_i18n_plural_format_create_from_locale_rules_pattern_p(void);
extern int ITc_i18n_plural_format_clone_p(void);
extern int ITc_i18n_plural_format_apply_pattern_p(void);
extern int ITc_i18n_plural_format_format_int32_p(void);
extern int ITc_i18n_plural_format_format_double_p(void);
extern int ITc_i18n_plural_format_format_formattable_p(void);
extern int ITc_i18n_plural_format_set_number_format_p(void);
extern int ITc_i18n_plural_format_to_pattern_p(void);
extern int ITc_i18n_date_interval_create_destroy_p(void);
extern int ITc_i18n_date_interval_clone_p(void);
extern int ITc_i18n_date_interval_get_from_date_p(void);
extern int ITc_i18n_date_interval_get_to_date_p(void);
extern int ITc_i18n_date_interval_equals_p(void);
extern int ITc_i18n_date_interval_fmt_create_destroy_p(void);
extern int ITc_i18n_date_interval_fmt_clone_p(void);
extern int ITc_i18n_date_interval_fmt_create_from_locale_p(void);
extern int ITc_i18n_date_interval_fmt_set_get_time_zone_p(void);
extern int ITc_i18n_date_interval_fmt_adopt_time_zone_p(void);
extern int ITc_i18n_date_interval_fmt_format_with_date_interval_p(void);
extern int ITc_i18n_date_interval_fmt_format_with_calendar_p(void);
extern int ITc_i18n_date_interval_fmt_equals_p(void);
extern int ITc_i18n_simple_date_fmt_create_destroy_p(void);
extern int ITc_i18n_simple_date_fmt_create_from_pattern_p(void);
extern int ITc_i18n_simple_date_fmt_create_from_pattern_override_p(void);
extern int ITc_i18n_simple_date_fmt_create_from_pattern_locale_p(void);
extern int ITc_i18n_simple_date_fmt_create_from_pattern_override_locale_p(void);
extern int ITc_i18n_simple_date_fmt_clone_p(void);
extern int ITc_i18n_simple_date_fmt_equals_p(void);
extern int ITc_i18n_simple_date_fmt_format_with_field_position_p(void);
extern int ITc_i18n_simple_date_fmt_parse_p(void);
extern int ITc_i18n_simple_date_fmt_set_get_2digit_year_start_p(void);
extern int ITc_i18n_simple_date_fmt_to_pattern_p(void);
extern int ITc_i18n_simple_date_fmt_to_localized_pattern_p(void);
extern int ITc_i18n_simple_date_fmt_apply_pattern_p(void);
extern int ITc_i18n_simple_date_fmt_apply_localized_pattern_p(void);
extern int ITc_i18n_simple_date_fmt_adopt_calendar_p(void);
extern int ITc_i18n_simple_date_fmt_set_context_p(void);

extern int ITs_base_utils_i18n_loc_disp_names_create_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_create_from_dialect_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_create_from_context_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_get_locale_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_get_dialect_handling_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_get_context_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_get_loc_disp_name_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_get_language_disp_name_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_get_script_disp_name_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_get_script_disp_name_with_script_code_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_get_region_disp_name_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_get_variant_disp_name_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_get_key_disp_name_p(void);
extern int ITs_base_utils_i18n_loc_disp_names_get_key_value_disp_name_p(void);

extern int ITc_i18n_utext_create_for_UTF8_p(void);
extern int ITc_i18n_utext_create_for_uchars_p(void);
extern int ITc_i18n_utext_clone_p(void);
extern int ITc_i18n_utext_equals_p(void);
extern int ITc_i18n_utext_native_length_p(void);
extern int ITc_i18n_utext_is_length_expensive_p(void);
extern int ITc_i18n_utext_char32_at_p(void);
extern int ITc_i18n_utext_current32_p(void);
extern int ITc_i18n_utext_next32_p(void);
extern int ITc_i18n_utext_previous32_p(void);
extern int ITc_i18n_utext_next32_from_p(void);
extern int ITc_i18n_utext_previous32_from_p(void);
extern int ITc_i18n_utext_set_get_native_index_p(void);
extern int ITc_i18n_utext_move_index32_p(void);
extern int ITc_i18n_utext_get_previous_native_index_p(void);
extern int ITc_i18n_utext_extract_p(void);
extern int ITc_i18n_utext_is_writable_p(void);
extern int ITc_i18n_utext_has_meta_data_p(void);
extern int ITc_i18n_utext_freeze_p(void);

extern int ITc_i18n_uscript_get_codes_p(void);
extern int ITc_i18n_uscript_get_name_p(void);
extern int ITc_i18n_uscript_get_short_name_p(void);
extern int ITc_i18n_uscript_get_script_p(void);
extern int ITc_i18n_uscript_has_script_p(void);
extern int ITc_i18n_uscript_get_script_extensions_p(void);
extern int ITc_i18n_uscript_get_sample_string_p(void);
extern int ITc_i18n_uscript_get_usage_p(void);
extern int ITc_i18n_uscript_is_right_to_left_p(void);
extern int ITc_i18n_uscript_breaks_between_letters_p(void);
extern int ITc_i18n_uscript_is_cased_p(void);

extern int ITc_i18n_unormalization_get_nfc_instance_p(void);
extern int ITc_i18n_unormalization_get_nfd_instance_p(void);
extern int ITc_i18n_unormalization_get_nfkc_instance_p(void);
extern int ITc_i18n_unormalization_get_nfkc_casefold_instance_p(void);
extern int ITc_i18n_unormalization_get_nfkd_instance_p(void);
extern int ITc_i18n_unormalization_create_filtered_p(void);
extern int ITc_i18n_unormalization_destroy_p(void);
extern int ITc_i18n_unormalization_normalize_second_and_append_p(void);
extern int ITc_i18n_unormalization_append_p(void);
extern int ITc_i18n_unormalization_get_decomposition_p(void);
extern int ITc_i18n_unormalization_get_raw_decomposition_p(void);
extern int ITc_i18n_unormalization_compose_pair_p(void);
extern int ITc_i18n_unormalization_is_normalized_p(void);
extern int ITc_i18n_unormalization_quick_check_p(void);
extern int ITc_i18n_unormalization_span_quick_check_yes_p(void);
extern int ITc_i18n_unormalizer_has_boundary_before_p(void);
extern int ITc_i18n_unormalizer_has_boundary_after_p(void);
extern int ITc_i18n_unormalization_is_inert_p(void);

extern int ITc_i18n_unumsys_create_p(void);
extern int ITc_i18n_unumsys_create_by_name_p(void);
extern int ITc_i18n_unumsys_get_available_names_p(void);
extern int ITc_i18n_unumsys_get_name_p(void);
extern int ITc_i18n_unumsys_is_algorithmic_p(void);
extern int ITc_i18n_unumsys_get_radix_p(void);
extern int ITc_i18n_unumsys_get_description_p(void);

extern int ITc_i18n_uidna_label_to_ascii_p(void);
extern int ITc_i18n_uidna_label_to_unicode_p(void);
extern int ITc_i18n_uidna_name_to_ascii_p(void);
extern int ITc_i18n_uidna_name_to_unicode_p(void);
extern int ITc_i18n_uidna_label_to_ascii_UTF8_p(void);
extern int ITc_i18n_uidna_label_to_unicode_UTF8_p(void);
extern int ITc_i18n_uidna_name_to_ascii_UTF8_p(void);
extern int ITc_i18n_uidna_name_to_unicode_UTF8_p(void);
extern int ITc_i18n_uidna_info_get_is_trans_different_p(void);
extern int ITc_i18n_uidna_info_get_errors_p(void);
extern int ITc_i18n_uidna_info_destroy_p(void);

extern int ITc_i18n_ucsdet_create_destroy_p(void);
extern int ITc_i18n_ucsdet_set_text_p(void);
extern int ITc_i18n_ucsdet_set_declared_encoding_p(void);
extern int ITc_i18n_ucsdet_detect_p(void);
extern int ITc_i18n_ucsdet_detect_all_p(void);
extern int ITc_i18n_ucsdet_get_name_p(void);
extern int ITc_i18n_ucsdet_get_confidence_p(void);
extern int ITc_i18n_ucsdet_get_language_p(void);
extern int ITc_i18n_ucsdet_get_uchars_p(void);
extern int ITc_i18n_ucsdet_get_all_detectable_charsets_p(void);
extern int ITc_i18n_ucsdet_is_input_filter_enabled(void);
extern int ITc_i18n_ucsdet_enable_input_filter_p(void);

extern int ITc_i18n_ucnvsel_create_destroy_p(void);
extern int ITc_i18n_ucnvsel_create_from_serialized_p(void);
extern int ITc_i18n_ucnvsel_serialize_p(void);
extern int ITc_i18n_ucnvsel_select_for_string_p(void);
extern int ITc_i18n_ucnvsel_select_for_utf8_p(void);

extern int ITc_i18n_ucnv_get_max_bytes_for_string_p(void);
extern int ITc_i18n_ucnv_compare_names_p(void);
extern int ITc_i18n_ucnv_create_destroy_p(void);
extern int ITc_i18n_ucnv_create_unicode_p(void);
extern int ITc_i18n_ucnv_create_ccsid_p(void);
extern int ITc_i18n_ucnv_safe_clone_p(void);
extern int ITc_i18n_ucnv_set_get_subst_chars_p(void);
extern int ITc_i18n_ucnv_set_subst_string_p(void);
extern int ITc_i18n_ucnv_get_invalid_chars_p(void);
extern int ITc_i18n_ucnv_get_invalid_uchars_p(void);
extern int ITc_i18n_ucnv_reset_p(void);
extern int ITc_i18n_ucnv_reset_to_unicode_p(void);
extern int ITc_i18n_ucnv_reset_from_unicode_p(void);
extern int ITc_i18n_ucnv_get_max_char_size_p(void);
extern int ITc_i18n_ucnv_get_min_char_size_p(void);
extern int ITc_i18n_ucnv_get_display_name_p(void);
extern int ITc_i18n_ucnv_get_name_p(void);
extern int ITc_i18n_ucnv_get_ccsid_p(void);
extern int ITc_i18n_ucnv_get_platform_p(void);
extern int ITc_i18n_ucnv_get_type_p(void);
extern int ITc_i18n_ucnv_get_starters_p(void);
extern int ITc_i18n_ucnv_get_unicode_set_p(void);
extern int ITc_i18n_ucnv_from_unicode_p(void);
extern int ITc_i18n_ucnv_to_unicode_p(void);
extern int ITc_i18n_ucnv_from_uchars_p(void);
extern int ITc_i18n_ucnv_to_uchars_p(void);
extern int ITc_i18n_ucnv_get_next_uchar_p(void);
extern int ITc_i18n_ucnv_convert_ex_p(void);
extern int ITc_i18n_ucnv_convert_p(void);
extern int ITc_i18n_ucnv_from_algorithmic_p(void);
extern int ITc_i18n_ucnv_to_algorithmic_p(void);
extern int ITc_i18n_ucnv_flush_cache_p(void);
extern int ITc_i18n_ucnv_count_available_p(void);
extern int ITc_i18n_ucnv_get_available_name_p(void);
extern int ITc_i18n_ucnv_create_all_names_p(void);
extern int ITc_i18n_ucnv_count_aliases_p(void);
extern int ITc_i18n_ucnv_get_aliases_p(void);
extern int ITc_i18n_ucnv_get_alias_p(void);
extern int ITc_i18n_ucnv_create_standard_names_p(void);
extern int ITc_i18n_ucnv_count_standards_p(void);
extern int ITc_i18n_ucnv_get_standard_p(void);
extern int ITc_i18n_ucnv_get_standard_name_p(void);
extern int ITc_i18n_ucnv_get_canonical_name_p(void);
extern int ITc_i18n_ucnv_set_get_default_name_p(void);
extern int ITc_i18n_ucnv_fix_file_separator_p(void);
extern int ITc_i18n_ucnv_is_ambiguous_p(void);
extern int ITc_i18n_ucnv_set_fallback_p(void);
extern int ITc_i18n_ucnv_uses_fallback_p(void);
extern int ITc_i18n_ucnv_detect_unicode_signature_p(void);
extern int ITc_i18n_ucnv_from_ucount_pending_p(void);
extern int ITc_i18n_ucnv_to_ucount_pending_p(void);
extern int ITc_i18n_ucnv_is_fixed_width_p(void);

extern int ITc_i18n_ures_create_destroy_p(void);
extern int ITc_i18n_ures_create_direct_p(void);
extern int ITc_i18n_ures_create_unicode_p(void);
extern int ITc_i18n_ures_get_version_p(void);
extern int ITc_i18n_ures_get_locale_by_type_p(void);
extern int ITc_i18n_ures_get_string_p(void);
extern int ITc_i18n_ures_get_UTF8_string_p(void);
extern int ITc_i18n_ures_get_binary_p(void);
extern int ITc_i18n_ures_get_int_vector_p(void);
extern int ITc_i18n_ures_get_uint_p(void);
extern int ITc_i18n_ures_get_int_p(void);
extern int ITc_i18n_ures_get_size_p(void);
extern int ITc_i18n_ures_get_type_p(void);
extern int ITc_i18n_ures_get_key_p(void);
extern int ITc_i18n_ures_reset_iterator_p(void);
extern int ITc_i18n_ures_has_next_p(void);
extern int ITc_i18n_ures_get_next_resource_p(void);
extern int ITc_i18n_ures_get_next_string_p(void);
extern int ITc_i18n_ures_get_by_index_p(void);
extern int ITc_i18n_ures_get_string_by_index_p(void);
extern int ITc_i18n_ures_get_UTF8_string_by_index_p(void);
extern int ITc_i18n_ures_get_by_key_p(void);
extern int ITc_i18n_ures_get_string_by_key_p(void);
extern int ITc_i18n_ures_get_UTF8_string_by_key_p(void);

testcase tc_array[] = {
	{"ITc_i18n_ubrk_create_destroy_p",ITc_i18n_ubrk_create_destroy_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_create_rules_p",ITc_i18n_ubrk_create_rules_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_safe_clone_p",ITc_i18n_ubrk_safe_clone_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_set_text_p",ITc_i18n_ubrk_set_text_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_current_p",ITc_i18n_ubrk_current_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_next_previous_p",ITc_i18n_ubrk_next_previous_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_first_last_p",ITc_i18n_ubrk_first_last_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_preceding_following_p",ITc_i18n_ubrk_preceding_following_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_get_available_p",ITc_i18n_ubrk_get_available_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_count_available_p",ITc_i18n_ubrk_count_available_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_is_boundary_p",ITc_i18n_ubrk_is_boundary_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_get_rule_status_p",ITc_i18n_ubrk_get_rule_status_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_get_rule_status_vec_p",ITc_i18n_ubrk_get_rule_status_vec_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ubrk_get_locale_by_type_p",ITc_i18n_ubrk_get_locale_by_type_p,ITs_base_utils_ubrk_startup,ITs_base_utils_ubrk_cleanup},
	{"ITc_i18n_ucalendar_get_now_p",ITc_i18n_ucalendar_get_now_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_create_destroy_p",ITc_i18n_ucalendar_create_destroy_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_add_get_p",ITc_i18n_ucalendar_add_get_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_set_date_time_get_milliseconds_p",ITc_i18n_ucalendar_set_date_time_get_milliseconds_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_set_get_attribute_p",ITc_i18n_ucalendar_set_get_attribute_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_timezone_displayname_p",ITc_i18n_ucalendar_get_timezone_displayname_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_set_milliseconds_p",ITc_i18n_ucalendar_set_milliseconds_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_is_in_daylight_time_p",ITc_i18n_ucalendar_is_in_daylight_time_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_is_equivalent_to_p",ITc_i18n_ucalendar_is_equivalent_to_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_clone_p",ITc_i18n_ucalendar_clone_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_set_p",ITc_i18n_ucalendar_set_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_set_default_timezone_p",ITc_i18n_ucalendar_set_default_timezone_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_timezone_id_enumeration_create_p",ITc_i18n_ucalendar_timezone_id_enumeration_create_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_timezones_create_p",ITc_i18n_ucalendar_timezones_create_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_country_timezones_create_p",ITc_i18n_ucalendar_country_timezones_create_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_default_timezone_p",ITc_i18n_ucalendar_get_default_timezone_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_set_timezone_p",ITc_i18n_ucalendar_set_timezone_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_timezone_id_get_canonical_timezone_id_p",ITc_i18n_ucalendar_get_timezone_id_get_canonical_timezone_id_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_set_get_gregorian_change_p",ITc_i18n_ucalendar_set_get_gregorian_change_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_available_p",ITc_i18n_ucalendar_get_available_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_count_available_p",ITc_i18n_ucalendar_count_available_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_roll_p",ITc_i18n_ucalendar_roll_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_is_set_p",ITc_i18n_ucalendar_is_set_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_clear_field_p",ITc_i18n_ucalendar_clear_field_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_clear_p",ITc_i18n_ucalendar_clear_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_limit_p",ITc_i18n_ucalendar_get_limit_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_locale_by_type_p",ITc_i18n_ucalendar_get_locale_by_type_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_tz_data_version_p",ITc_i18n_ucalendar_get_tz_data_version_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_type_p",ITc_i18n_ucalendar_get_type_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_keyword_values_for_locale_p",ITc_i18n_ucalendar_get_keyword_values_for_locale_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_day_of_week_type_p",ITc_i18n_ucalendar_get_day_of_week_type_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_weekend_transition_p",ITc_i18n_ucalendar_get_weekend_transition_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_is_weekend_p",ITc_i18n_ucalendar_is_weekend_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_field_difference_p",ITc_i18n_ucalendar_get_field_difference_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_ucalendar_get_timezone_transition_date_p",ITc_i18n_ucalendar_get_timezone_transition_date_p,ITs_base_utils_ucalendar_startup,ITs_base_utils_ucalendar_cleanup},
	{"ITc_i18n_udate_create_destroy_p",ITc_i18n_udate_create_destroy_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_format_date_p",ITc_i18n_udate_format_date_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_to_calendar_date_field_p",ITc_i18n_udate_to_calendar_date_field_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_clone_p",ITc_i18n_udate_clone_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_parse_p",ITc_i18n_udate_parse_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_parse_calendar_p",ITc_i18n_udate_parse_calendar_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_is_set_lenient_p",ITc_i18n_udate_is_set_lenient_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_get_set_calendar_p",ITc_i18n_udate_get_set_calendar_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_get_set_number_format_p",ITc_i18n_udate_get_set_number_format_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_get_set_2digit_year_start_p",ITc_i18n_udate_get_set_2digit_year_start_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_set_get_symbols_p",ITc_i18n_udate_set_get_symbols_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_get_available_p",ITc_i18n_udate_get_available_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_count_available_p",ITc_i18n_udate_count_available_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_apply_pattern_p",ITc_i18n_udate_apply_pattern_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_apply_to_pattern_p",ITc_i18n_udate_apply_to_pattern_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_count_symbols_p",ITc_i18n_udate_count_symbols_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_get_locale_by_type_p",ITc_i18n_udate_get_locale_by_type_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udate_set_context_p",ITc_i18n_udate_set_context_p,ITs_base_utils_udate_startup,ITs_base_utils_udate_cleanup},
	{"ITc_i18n_udatepg_create_destroy_p",ITc_i18n_udatepg_create_destroy_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_get_best_pattern_p",ITc_i18n_udatepg_get_best_pattern_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_set_get_decimal_p",ITc_i18n_udatepg_set_get_decimal_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_set_get_date_time_format_p",ITc_i18n_udatepg_set_get_date_time_format_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_set_get_append_item_name_p",ITc_i18n_udatepg_set_get_append_item_name_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_set_get_append_item_format_p",ITc_i18n_udatepg_set_get_append_item_format_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_replace_field_types_with_options_p",ITc_i18n_udatepg_replace_field_types_with_options_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_replace_field_types_p",ITc_i18n_udatepg_replace_field_types_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_get_skeleton_p",ITc_i18n_udatepg_get_skeleton_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_get_best_pattern_with_options_p",ITc_i18n_udatepg_get_best_pattern_with_options_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_get_base_skeleton_p",ITc_i18n_udatepg_get_base_skeleton_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_add_pattern_p",ITc_i18n_udatepg_add_pattern_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_get_pattern_for_skeleton_p",ITc_i18n_udatepg_get_pattern_for_skeleton_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_skeletons_create_p",ITc_i18n_udatepg_skeletons_create_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_base_skeletons_create_p",ITc_i18n_udatepg_base_skeletons_create_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_create_empty_p",ITc_i18n_udatepg_create_empty_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_udatepg_clone_p",ITc_i18n_udatepg_clone_p,ITs_base_utils_udatepg_startup,ITs_base_utils_udatepg_cleanup},
	{"ITc_i18n_uenumeration_uchar_strings_enumeration_create_destroy_p",ITc_i18n_uenumeration_uchar_strings_enumeration_create_destroy_p,ITs_base_utils_enumeration_startup,ITs_base_utils_enumeration_cleanup},
	{"ITc_i18n_uenumeration_char_strings_enumeration_create_destroy_p",ITc_i18n_uenumeration_char_strings_enumeration_create_destroy_p,ITs_base_utils_enumeration_startup,ITs_base_utils_enumeration_cleanup},
	{"ITc_i18n_uenumeration_count_p",ITc_i18n_uenumeration_count_p,ITs_base_utils_enumeration_startup,ITs_base_utils_enumeration_cleanup},
	{"ITc_i18n_uenumeration_unext_p",ITc_i18n_uenumeration_unext_p,ITs_base_utils_enumeration_startup,ITs_base_utils_enumeration_cleanup},
	{"ITc_i18n_uenumeration_next_p",ITc_i18n_uenumeration_next_p,ITs_base_utils_enumeration_startup,ITs_base_utils_enumeration_cleanup},
	{"ITc_i18n_uenumeration_reset_p",ITc_i18n_uenumeration_reset_p,ITs_base_utils_enumeration_startup,ITs_base_utils_enumeration_cleanup},
	{"ITc_i18n_uset_create_empty_p",ITc_i18n_uset_create_empty_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_create_destroy_p",ITc_i18n_uset_create_destroy_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_create_pattern_p",ITc_i18n_uset_create_pattern_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_create_pattern_options_p",ITc_i18n_uset_create_pattern_options_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_clone_p",ITc_i18n_uset_clone_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_freeze_p",ITc_i18n_uset_freeze_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_is_frozen_p",ITc_i18n_uset_is_frozen_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_clone_as_thawed_p",ITc_i18n_uset_clone_as_thawed_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_set_p",ITc_i18n_uset_set_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_apply_pattern_p",ITc_i18n_uset_apply_pattern_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_apply_int_property_value_p",ITc_i18n_uset_apply_int_property_value_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_apply_property_alias_p",ITc_i18n_uset_apply_property_alias_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_resembles_pattern_p",ITc_i18n_uset_resembles_pattern_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_to_pattern_p",ITc_i18n_uset_to_pattern_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_add_remove_p",ITc_i18n_uset_add_remove_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_add_remove_all_p",ITc_i18n_uset_add_remove_all_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_add_remove_range_p",ITc_i18n_uset_add_remove_range_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_add_remove_string_p",ITc_i18n_uset_add_remove_string_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_add_all_code_points_p",ITc_i18n_uset_add_all_code_points_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_retain_p",ITc_i18n_uset_retain_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_retain_all_p",ITc_i18n_uset_retain_all_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_compact_p",ITc_i18n_uset_compact_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_complement_p",ITc_i18n_uset_complement_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_complement_all_p",ITc_i18n_uset_complement_all_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_clear_p",ITc_i18n_uset_clear_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_destroy_over_p",ITc_i18n_uset_destroy_over_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_remove_all_strings_p",ITc_i18n_uset_remove_all_strings_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_is_empty_p",ITc_i18n_uset_is_empty_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_contains_p",ITc_i18n_uset_contains_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_contains_range_p",ITc_i18n_uset_contains_range_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_contains_string_p",ITc_i18n_uset_contains_string_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_index_of_p",ITc_i18n_uset_index_of_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_char_at_p",ITc_i18n_uset_char_at_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_size_p",ITc_i18n_uset_size_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_get_item_count_p",ITc_i18n_uset_get_item_count_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_get_item_p",ITc_i18n_uset_get_item_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_contains_all_p",ITc_i18n_uset_contains_all_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_contains_all_code_points_p",ITc_i18n_uset_contains_all_code_points_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_contains_none_p",ITc_i18n_uset_contains_none_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_contains_some_p",ITc_i18n_uset_contains_some_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_span_p",ITc_i18n_uset_span_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_span_back_p",ITc_i18n_uset_span_back_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_span_utf8_p",ITc_i18n_uset_span_utf8_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_span_back_utf8_p",ITc_i18n_uset_span_back_utf8_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_equals_p",ITc_i18n_uset_equals_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_serialize_p",ITc_i18n_uset_serialize_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_get_serialized_set_p",ITc_i18n_uset_get_serialized_set_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_set_serialized_to_one_p",ITc_i18n_uset_set_serialized_to_one_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_serialized_contains_p",ITc_i18n_uset_serialized_contains_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_get_serialized_range_count_p",ITc_i18n_uset_get_serialized_range_count_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_uset_get_serialized_range_p",ITc_i18n_uset_get_serialized_range_p,ITs_base_utils_uset_startup,ITs_base_utils_uset_cleanup},
	{"ITc_i18n_unumber_get_symbol_p",ITc_i18n_unumber_get_symbol_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_create_destroy_p",ITc_i18n_unumber_create_destroy_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_apply_pattern_p",ITc_i18n_unumber_apply_pattern_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_clone_p",ITc_i18n_unumber_clone_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_count_available_p",ITc_i18n_unumber_count_available_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_format_decimal_p",ITc_i18n_unumber_format_decimal_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_format_double_p",ITc_i18n_unumber_format_double_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_format_double_currency_p",ITc_i18n_unumber_format_double_currency_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_format_int64_p",ITc_i18n_unumber_format_int64_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_set_get_attribute_p",ITc_i18n_unumber_set_get_attribute_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_get_available_p",ITc_i18n_unumber_get_available_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_set_get_double_attribute_p",ITc_i18n_unumber_set_get_double_attribute_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_get_locale_by_type_p",ITc_i18n_unumber_get_locale_by_type_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_set_get_text_attribute_p",ITc_i18n_unumber_set_get_text_attribute_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_parse_p",ITc_i18n_unumber_parse_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_parse_decimal_p",ITc_i18n_unumber_parse_decimal_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_parse_double_p",ITc_i18n_unumber_parse_double_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_parse_double_currency_p",ITc_i18n_unumber_parse_double_currency_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_parse_int64_p",ITc_i18n_unumber_parse_int64_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_to_pattern_p",ITc_i18n_unumber_to_pattern_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_unumber_set_get_symbol_p",ITc_i18n_unumber_set_get_symbol_p,ITs_base_utils_unumber_startup,ITs_base_utils_unumber_cleanup},
	{"ITc_i18n_ulocale_get_language_p",ITc_i18n_ulocale_get_language_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_display_name_p",ITc_i18n_ulocale_get_display_name_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_set_get_default_p",ITc_i18n_ulocale_set_get_default_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_available_p",ITc_i18n_ulocale_get_available_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_country_p",ITc_i18n_ulocale_get_country_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_count_available_p",ITc_i18n_ulocale_count_available_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_add_likely_subtags_p",ITc_i18n_ulocale_add_likely_subtags_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_canonicalize_p",ITc_i18n_ulocale_canonicalize_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_for_language_tag_p",ITc_i18n_ulocale_for_language_tag_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_base_name_p",ITc_i18n_ulocale_get_base_name_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_character_orientation_p",ITc_i18n_ulocale_get_character_orientation_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_display_country_p",ITc_i18n_ulocale_get_display_country_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_display_keyword_p",ITc_i18n_ulocale_get_display_keyword_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_display_keyword_value_p",ITc_i18n_ulocale_get_display_keyword_value_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_display_language_p",ITc_i18n_ulocale_get_display_language_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_display_script_p",ITc_i18n_ulocale_get_display_script_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_display_variant_p",ITc_i18n_ulocale_get_display_variant_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_iso3_country_p",ITc_i18n_ulocale_get_iso3_country_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_iso3_language_p",ITc_i18n_ulocale_get_iso3_language_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_iso_countries_p",ITc_i18n_ulocale_get_iso_countries_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_iso_languages_p",ITc_i18n_ulocale_get_iso_languages_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_set_get_keyword_value_p",ITc_i18n_ulocale_set_get_keyword_value_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_lcid_p",ITc_i18n_ulocale_get_lcid_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_line_orientation_p",ITc_i18n_ulocale_get_line_orientation_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_locale_for_lcid_p",ITc_i18n_ulocale_get_locale_for_lcid_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_name_p",ITc_i18n_ulocale_get_name_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_parent_p",ITc_i18n_ulocale_get_parent_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_script_p",ITc_i18n_ulocale_get_script_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_get_variant_p",ITc_i18n_ulocale_get_variant_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_keywords_create_p",ITc_i18n_ulocale_keywords_create_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_minimize_subtags_p",ITc_i18n_ulocale_minimize_subtags_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_ulocale_to_language_tag_p",ITc_i18n_ulocale_to_language_tag_p,ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_timezone_create_unknown_p",ITc_i18n_timezone_create_unknown_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_create_gmt_p",ITc_i18n_timezone_create_gmt_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_create_destroy_p",ITc_i18n_timezone_create_destroy_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_count_equivalent_ids_p",ITc_i18n_timezone_count_equivalent_ids_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_get_equivalent_id_p",ITc_i18n_timezone_get_equivalent_id_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_create_default_p",ITc_i18n_timezone_create_default_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_set_default_p",ITc_i18n_timezone_set_default_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_get_tzdata_version_p",ITc_i18n_timezone_get_tzdata_version_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_get_region_p",ITc_i18n_timezone_get_region_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_get_offset_with_date_p",ITc_i18n_timezone_get_offset_with_date_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_set_get_raw_offset_p",ITc_i18n_timezone_set_get_raw_offset_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_set_get_id_p",ITc_i18n_timezone_set_get_id_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_get_display_name_p",ITc_i18n_timezone_get_display_name_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_get_display_name_with_locale_id_p",ITc_i18n_timezone_get_display_name_with_locale_id_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_get_display_name_with_type_p",ITc_i18n_timezone_get_display_name_with_type_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_get_display_name_with_type_locale_id_p",ITc_i18n_timezone_get_display_name_with_type_locale_id_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_use_daylight_time_p",ITc_i18n_timezone_use_daylight_time_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_has_same_rule_p",ITc_i18n_timezone_has_same_rule_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_clone_p",ITc_i18n_timezone_clone_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_get_dst_savings_p",ITc_i18n_timezone_get_dst_savings_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_foreach_timezone_id_by_region_p",ITc_i18n_timezone_foreach_timezone_id_by_region_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_foreach_timezone_id_p",ITc_i18n_timezone_foreach_timezone_id_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_foreach_timezone_id_with_offset_p",ITc_i18n_timezone_foreach_timezone_id_with_offset_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_foreach_timezone_id_by_country_p",ITc_i18n_timezone_foreach_timezone_id_by_country_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_timezone_detect_host_timezone_p",ITc_i18n_timezone_detect_host_timezone_p,ITs_base_utils_timezone_startup,ITs_base_utils_timezone_cleanup},
	{"ITc_i18n_uchar_get_int_property_value_p",ITc_i18n_uchar_get_int_property_value_p,ITs_base_utils_uchar_startup,ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_get_ublock_code_p",ITc_i18n_uchar_get_ublock_code_p,ITs_base_utils_uchar_startup,ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_ucollator_create_destroy_p",ITc_i18n_ucollator_create_destroy_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_str_collator_p",ITc_i18n_ucollator_str_collator_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_equal_p",ITc_i18n_ucollator_equal_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_set_strength_p",ITc_i18n_ucollator_set_strength_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_set_attribute_p",ITc_i18n_ucollator_set_attribute_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_create_rules_p",ITc_i18n_ucollator_create_rules_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_contractions_and_expansions_p",ITc_i18n_ucollator_get_contractions_and_expansions_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_str_collator_utf8_p",ITc_i18n_ucollator_str_collator_utf8_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_greater_p",ITc_i18n_ucollator_greater_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_greater_or_equal_p",ITc_i18n_ucollator_greater_or_equal_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_str_collator_iter_p",ITc_i18n_ucollator_str_collator_iter_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_strength_p",ITc_i18n_ucollator_get_strength_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_reorder_codes_p",ITc_i18n_ucollator_get_reorder_codes_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_set_reorder_codes_p",ITc_i18n_ucollator_set_reorder_codes_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_display_name_p",ITc_i18n_ucollator_get_display_name_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_available_p",ITc_i18n_ucollator_get_available_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_count_available_p",ITc_i18n_ucollator_count_available_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_create_available_locales_p",ITc_i18n_ucollator_create_available_locales_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_keywords_p",ITc_i18n_ucollator_get_keywords_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_keyword_values_p",ITc_i18n_ucollator_get_keyword_values_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_keyword_values_for_locale_p",ITc_i18n_ucollator_get_keyword_values_for_locale_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_functional_equivalent_p",ITc_i18n_ucollator_get_functional_equivalent_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_rules_p",ITc_i18n_ucollator_get_rules_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_sort_key_p",ITc_i18n_ucollator_get_sort_key_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_next_sort_key_part_p",ITc_i18n_ucollator_next_sort_key_part_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_bound_p",ITc_i18n_ucollator_get_bound_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_version_p",ITc_i18n_ucollator_get_version_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_uca_version_p",ITc_i18n_ucollator_get_uca_version_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_merge_sort_keys_p",ITc_i18n_ucollator_merge_sort_keys_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_attribute_p",ITc_i18n_ucollator_get_attribute_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_set_get_max_variable_p",ITc_i18n_ucollator_set_get_max_variable_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_variable_top_p",ITc_i18n_ucollator_get_variable_top_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_safe_clone_p",ITc_i18n_ucollator_safe_clone_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_rules_ex_p",ITc_i18n_ucollator_get_rules_ex_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_locale_by_type_p",ITc_i18n_ucollator_get_locale_by_type_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_get_tailored_set_p",ITc_i18n_ucollator_get_tailored_set_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_clone_binary_p",ITc_i18n_ucollator_clone_binary_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_ucollator_create_binary_p",ITc_i18n_ucollator_create_binary_p,ITs_base_utils_ucollator_startup,ITs_base_utils_ucollator_cleanup},
	{"ITc_i18n_unormalization_get_instance_normalize_p",ITc_i18n_unormalization_get_instance_normalize_p,ITs_base_utils_unormalization_startup,ITs_base_utils_unormalization_cleanup},
	{"ITc_i18n_usearch_first_get_macthed_text_p",ITc_i18n_usearch_first_get_macthed_text_p,ITs_base_utils_usearch_startup,ITs_base_utils_usearch_cleanup},
	{"ITc_i18n_usearch_get_collator_p",ITc_i18n_usearch_get_collator_p,ITs_base_utils_usearch_startup,ITs_base_utils_usearch_cleanup},
	{"ITc_i18n_usearch_create_new_p",ITc_i18n_usearch_create_new_p,ITs_base_utils_usearch_startup,ITs_base_utils_usearch_cleanup},
	{"ITc_i18n_ustring_copy_compare_p",ITc_i18n_ustring_copy_compare_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_get_length_to_upper_p",ITc_i18n_ustring_get_length_to_upper_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_from_UTF8_to_UTF8_p",ITc_i18n_ustring_from_UTF8_to_UTF8_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_copy_au_p",ITc_i18n_ustring_copy_au_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_copy_au_n_p",ITc_i18n_ustring_copy_au_n_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_copy_ua_n_p",ITc_i18n_ustring_copy_ua_n_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_copy_ua_p",ITc_i18n_ustring_copy_ua_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_copy_n_p",ITc_i18n_ustring_copy_n_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_to_upper_p",ITc_i18n_ustring_to_upper_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_count_char32_p",ITc_i18n_ustring_count_char32_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_has_more_char32_than_p",ITc_i18n_ustring_has_more_char32_than_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_cat_p",ITc_i18n_ustring_cat_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_cat_n_p",ITc_i18n_ustring_cat_n_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_string_p",ITc_i18n_ustring_string_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_find_first_p",ITc_i18n_ustring_find_first_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_char_p",ITc_i18n_ustring_char_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_char32_p",ITc_i18n_ustring_char32_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_r_string_p",ITc_i18n_ustring_r_string_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_find_last_p",ITc_i18n_ustring_find_last_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_r_char_p",ITc_i18n_ustring_r_char_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_r_char32_p",ITc_i18n_ustring_r_char32_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_pbrk_p",ITc_i18n_ustring_pbrk_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_cspn_p",ITc_i18n_ustring_cspn_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_spn_p",ITc_i18n_ustring_spn_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_tokenizer_r_p",ITc_i18n_ustring_tokenizer_r_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_compare_code_point_order_p",ITc_i18n_ustring_compare_code_point_order_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_compare_binary_order_p",ITc_i18n_ustring_compare_binary_order_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_case_compare_with_length_p",ITc_i18n_ustring_case_compare_with_length_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_compare_n_p",ITc_i18n_ustring_compare_n_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_compare_n_code_point_order_p",ITc_i18n_ustring_compare_n_code_point_order_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_case_compare_p",ITc_i18n_ustring_case_compare_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_case_compare_n_p",ITc_i18n_ustring_case_compare_n_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_mem_case_compare_p",ITc_i18n_ustring_mem_case_compare_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_mem_copy_p",ITc_i18n_ustring_mem_copy_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_mem_move_p",ITc_i18n_ustring_mem_move_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_mem_set_p",ITc_i18n_ustring_mem_set_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_mem_compare_p",ITc_i18n_ustring_mem_compare_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_mem_compare_code_point_order_p",ITc_i18n_ustring_mem_compare_code_point_order_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_mem_char_p",ITc_i18n_ustring_mem_char_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_mem_char32_p",ITc_i18n_ustring_mem_char32_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_mem_r_char_p",ITc_i18n_ustring_mem_r_char_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_mem_r_char32_p",ITc_i18n_ustring_mem_r_char32_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_unescape_p",ITc_i18n_ustring_unescape_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_unescape_at_p",ITc_i18n_ustring_unescape_at_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_to_lower_p",ITc_i18n_ustring_to_lower_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_fold_case_p",ITc_i18n_ustring_fold_case_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_to_WCS_p",ITc_i18n_ustring_to_WCS_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_from_WCS_p",ITc_i18n_ustring_from_WCS_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_to_UTF8_with_sub_p",ITc_i18n_ustring_to_UTF8_with_sub_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_from_UTF8_with_sub_p",ITc_i18n_ustring_from_UTF8_with_sub_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_from_UTF8_lenient_p",ITc_i18n_ustring_from_UTF8_lenient_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_to_UTF32_p",ITc_i18n_ustring_to_UTF32_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_from_UTF32_p",ITc_i18n_ustring_from_UTF32_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_from_UTF32_with_sub_p",ITc_i18n_ustring_from_UTF32_with_sub_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_to_UTF32_with_sub_p",ITc_i18n_ustring_to_UTF32_with_sub_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ustring_to_title_new_p",ITc_i18n_ustring_to_title_new_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_ushape_shape_arabic_p",ITc_i18n_ushape_shape_arabic_p,ITs_base_utils_ustring_startup,ITs_base_utils_ustring_cleanup},
	{"ITc_i18n_field_position_create_destroy_p",ITc_i18n_field_position_create_destroy_p,ITs_base_utils_field_position_startup,ITs_base_utils_field_position_cleanup},
	{"ITc_i18n_field_position_create_set_get_for_field_p",ITc_i18n_field_position_create_set_get_for_field_p,ITs_base_utils_field_position_startup,ITs_base_utils_field_position_cleanup},
	{"ITc_i18n_field_position_clone_p",ITc_i18n_field_position_clone_p,ITs_base_utils_field_position_startup,ITs_base_utils_field_position_cleanup},
	{"ITc_i18n_field_position_set_get_begin_index_p",ITc_i18n_field_position_set_get_begin_index_p,ITs_base_utils_field_position_startup,ITs_base_utils_field_position_cleanup},
	{"ITc_i18n_field_position_set_get_end_index_p",ITc_i18n_field_position_set_get_end_index_p,ITs_base_utils_field_position_startup,ITs_base_utils_field_position_cleanup},
	{"ITc_i18n_format_format_p",ITc_i18n_format_format_p,ITs_base_utils_format_startup,ITs_base_utils_format_cleanup},
	{"ITc_i18n_format_clone_destroy_p",ITc_i18n_format_clone_destroy_p,ITs_base_utils_format_startup,ITs_base_utils_format_cleanup},
	{"ITc_i18n_format_format_with_field_position_p",ITc_i18n_format_format_with_field_position_p,ITs_base_utils_format_startup,ITs_base_utils_format_cleanup},
	{"ITc_i18n_format_parse_object_p",ITc_i18n_format_parse_object_p,ITs_base_utils_format_startup,ITs_base_utils_format_cleanup},
	{"ITc_i18n_format_parse_object_with_parse_position_p",ITc_i18n_format_parse_object_with_parse_position_p,ITs_base_utils_format_startup,ITs_base_utils_format_cleanup},
	{"ITc_i18n_format_get_locale_id_p",ITc_i18n_format_get_locale_id_p,ITs_base_utils_format_startup,ITs_base_utils_format_cleanup},
	{"ITc_i18n_measure_create_destroy_p",ITc_i18n_measure_create_destroy_p,ITs_base_utils_measure_startup,ITs_base_utils_measure_cleanup},
	{"ITc_i18n_measure_clone_p",ITc_i18n_measure_clone_p,ITs_base_utils_measure_startup,ITs_base_utils_measure_cleanup},
	{"ITc_i18n_measure_get_number_p",ITc_i18n_measure_get_number_p,ITs_base_utils_measure_startup,ITs_base_utils_measure_cleanup},
	{"ITc_i18n_measure_get_unit_p",ITc_i18n_measure_get_unit_p,ITs_base_utils_measure_startup,ITs_base_utils_measure_cleanup},
	{"ITc_i18n_measure_format_create_destroy_from_locale_id_p",ITc_i18n_measure_format_create_destroy_from_locale_id_p,ITs_base_utils_measure_format_startup,ITs_base_utils_measure_format_cleanup},
	{"ITc_i18n_measure_format_clone_p",ITc_i18n_measure_format_clone_p,ITs_base_utils_measure_format_startup,ITs_base_utils_measure_format_cleanup},
	{"ITc_i18n_measure_format_format_p",ITc_i18n_measure_format_format_p,ITs_base_utils_measure_format_startup,ITs_base_utils_measure_format_cleanup},
	{"ITc_i18n_measure_format_parse_object_p",ITc_i18n_measure_format_parse_object_p,ITs_base_utils_measure_format_startup,ITs_base_utils_measure_format_cleanup},
	{"ITc_i18n_measure_format_create_currency_format_from_locale_id_p",ITc_i18n_measure_format_create_currency_format_from_locale_id_p,ITs_base_utils_measure_format_startup,ITs_base_utils_measure_format_cleanup},
	{"ITc_i18n_measure_format_create_currency_format_p",ITc_i18n_measure_format_create_currency_format_p,ITs_base_utils_measure_format_startup,ITs_base_utils_measure_format_cleanup},
	{"ITc_i18n_measure_unit_create_destroy_p",ITc_i18n_measure_unit_create_destroy_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_clone_p",ITc_i18n_measure_unit_clone_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_get_available_destroy_p",ITc_i18n_measure_unit_get_available_destroy_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_get_available_with_type_p",ITc_i18n_measure_unit_get_available_with_type_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_foreach_available_type_p",ITc_i18n_measure_unit_foreach_available_type_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_g_force_p",ITc_i18n_measure_unit_create_g_force_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_meter_per_second_squared_p",ITc_i18n_measure_unit_create_meter_per_second_squared_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_arc_minute_p",ITc_i18n_measure_unit_create_arc_minute_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_arc_second_p",ITc_i18n_measure_unit_create_arc_second_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_degree_p",ITc_i18n_measure_unit_create_degree_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_radian_p",ITc_i18n_measure_unit_create_radian_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_acre_p",ITc_i18n_measure_unit_create_acre_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_hectare_p",ITc_i18n_measure_unit_create_hectare_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_square_centimeter_p",ITc_i18n_measure_unit_create_square_centimeter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_square_foot_p",ITc_i18n_measure_unit_create_square_foot_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_square_inch_p",ITc_i18n_measure_unit_create_square_inch_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_square_kilometer_p",ITc_i18n_measure_unit_create_square_kilometer_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_square_meter_p",ITc_i18n_measure_unit_create_square_meter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_square_mile_p",ITc_i18n_measure_unit_create_square_mile_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_square_yard_p",ITc_i18n_measure_unit_create_square_yard_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_liter_per_kilometer_p",ITc_i18n_measure_unit_create_liter_per_kilometer_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_mile_per_gallon_p",ITc_i18n_measure_unit_create_mile_per_gallon_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_bit_p",ITc_i18n_measure_unit_create_bit_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_byte_p",ITc_i18n_measure_unit_create_byte_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_gigabit_p",ITc_i18n_measure_unit_create_gigabit_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_gigabyte_p",ITc_i18n_measure_unit_create_gigabyte_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_kilobit_p",ITc_i18n_measure_unit_create_kilobit_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_kilobyte_p",ITc_i18n_measure_unit_create_kilobyte_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_megabit_p",ITc_i18n_measure_unit_create_megabit_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_megabyte_p",ITc_i18n_measure_unit_create_megabyte_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_terabit_p",ITc_i18n_measure_unit_create_terabit_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_terabyte_p",ITc_i18n_measure_unit_create_terabyte_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_day_p",ITc_i18n_measure_unit_create_day_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_hour_p",ITc_i18n_measure_unit_create_hour_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_microsecond_p",ITc_i18n_measure_unit_create_microsecond_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_millisecond_p",ITc_i18n_measure_unit_create_millisecond_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_minute_p",ITc_i18n_measure_unit_create_minute_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_month_p",ITc_i18n_measure_unit_create_month_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_nanosecond_p",ITc_i18n_measure_unit_create_nanosecond_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_second_p",ITc_i18n_measure_unit_create_second_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_week_p",ITc_i18n_measure_unit_create_week_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_year_p",ITc_i18n_measure_unit_create_year_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_ampere_p",ITc_i18n_measure_unit_create_ampere_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_milliampere_p",ITc_i18n_measure_unit_create_milliampere_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_ohm_p",ITc_i18n_measure_unit_create_ohm_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_volt_p",ITc_i18n_measure_unit_create_volt_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_calorie_p",ITc_i18n_measure_unit_create_calorie_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_foodcalorie_p",ITc_i18n_measure_unit_create_foodcalorie_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_joule_p",ITc_i18n_measure_unit_create_joule_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_kilocalorie_p",ITc_i18n_measure_unit_create_kilocalorie_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_kilojoule_p",ITc_i18n_measure_unit_create_kilojoule_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_kilowatt_hour_p",ITc_i18n_measure_unit_create_kilowatt_hour_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_gigahertz_p",ITc_i18n_measure_unit_create_gigahertz_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_hertz_p",ITc_i18n_measure_unit_create_hertz_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_kilohertz_p",ITc_i18n_measure_unit_create_kilohertz_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_megahertz_p",ITc_i18n_measure_unit_create_megahertz_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_astronomical_unit_p",ITc_i18n_measure_unit_create_astronomical_unit_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_centimeter_p",ITc_i18n_measure_unit_create_centimeter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_decimeter_p",ITc_i18n_measure_unit_create_decimeter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_fathom_p",ITc_i18n_measure_unit_create_fathom_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_foot_p",ITc_i18n_measure_unit_create_foot_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_furlong_p",ITc_i18n_measure_unit_create_furlong_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_inch_p",ITc_i18n_measure_unit_create_inch_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_kilometer_p",ITc_i18n_measure_unit_create_kilometer_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_light_year_p",ITc_i18n_measure_unit_create_light_year_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_meter_p",ITc_i18n_measure_unit_create_meter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_micrometer_p",ITc_i18n_measure_unit_create_micrometer_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_mile_p",ITc_i18n_measure_unit_create_mile_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_millimeter_p",ITc_i18n_measure_unit_create_millimeter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_nanometer_p",ITc_i18n_measure_unit_create_nanometer_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_nautical_mile_p",ITc_i18n_measure_unit_create_nautical_mile_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_parsec_p",ITc_i18n_measure_unit_create_parsec_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_picometer_p",ITc_i18n_measure_unit_create_picometer_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_yard_p",ITc_i18n_measure_unit_create_yard_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_lux_p",ITc_i18n_measure_unit_create_lux_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_carat_p",ITc_i18n_measure_unit_create_carat_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_gram_p",ITc_i18n_measure_unit_create_gram_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_kilogram_p",ITc_i18n_measure_unit_create_kilogram_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_metric_ton_p",ITc_i18n_measure_unit_create_metric_ton_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_microgram_p",ITc_i18n_measure_unit_create_microgram_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_milligram_p",ITc_i18n_measure_unit_create_milligram_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_ounce_p",ITc_i18n_measure_unit_create_ounce_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_ounce_troy_p",ITc_i18n_measure_unit_create_ounce_troy_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_pound_p",ITc_i18n_measure_unit_create_pound_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_stone_p",ITc_i18n_measure_unit_create_stone_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_ton_p",ITc_i18n_measure_unit_create_ton_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_gigawatt_p",ITc_i18n_measure_unit_create_gigawatt_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_horsepower_p",ITc_i18n_measure_unit_create_horsepower_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_kilowatt_p",ITc_i18n_measure_unit_create_kilowatt_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_megawatt_p",ITc_i18n_measure_unit_create_megawatt_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_milliwatt_p",ITc_i18n_measure_unit_create_milliwatt_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_watt_p",ITc_i18n_measure_unit_create_watt_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_hectopascal_p",ITc_i18n_measure_unit_create_hectopascal_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_inch_hg_p",ITc_i18n_measure_unit_create_inch_hg_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_millibar_p",ITc_i18n_measure_unit_create_millibar_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_millimeter_of_mercury_p",ITc_i18n_measure_unit_create_millimeter_of_mercury_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_pound_per_square_inch_p",ITc_i18n_measure_unit_create_pound_per_square_inch_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_karat_p",ITc_i18n_measure_unit_create_karat_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_kilometer_per_hour_p",ITc_i18n_measure_unit_create_kilometer_per_hour_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_meter_per_second_p",ITc_i18n_measure_unit_create_meter_per_second_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_mile_per_hour_p",ITc_i18n_measure_unit_create_mile_per_hour_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_celsius_p",ITc_i18n_measure_unit_create_celsius_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_fahrenheit_p",ITc_i18n_measure_unit_create_fahrenheit_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_kelvin_p",ITc_i18n_measure_unit_create_kelvin_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_acre_foot_p",ITc_i18n_measure_unit_create_acre_foot_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_bushel_p",ITc_i18n_measure_unit_create_bushel_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_centiliter_p",ITc_i18n_measure_unit_create_centiliter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_cubic_centimeter_p",ITc_i18n_measure_unit_create_cubic_centimeter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_cubic_foot_p",ITc_i18n_measure_unit_create_cubic_foot_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_cubic_inch_p",ITc_i18n_measure_unit_create_cubic_inch_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_cubic_kilometer_p",ITc_i18n_measure_unit_create_cubic_kilometer_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_cubic_meter_p",ITc_i18n_measure_unit_create_cubic_meter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_cubic_mile_p",ITc_i18n_measure_unit_create_cubic_mile_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_cubic_yard_p",ITc_i18n_measure_unit_create_cubic_yard_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_cup_p",ITc_i18n_measure_unit_create_cup_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_deciliter_p",ITc_i18n_measure_unit_create_deciliter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_fluid_ounce_p",ITc_i18n_measure_unit_create_fluid_ounce_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_gallon_p",ITc_i18n_measure_unit_create_gallon_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_hectoliter_p",ITc_i18n_measure_unit_create_hectoliter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_liter_p",ITc_i18n_measure_unit_create_liter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_megaliter_p",ITc_i18n_measure_unit_create_megaliter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_milliliter_p",ITc_i18n_measure_unit_create_milliliter_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_pint_p",ITc_i18n_measure_unit_create_pint_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_quart_p",ITc_i18n_measure_unit_create_quart_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_tablespoon_p",ITc_i18n_measure_unit_create_tablespoon_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_measure_unit_create_teaspoon_p",ITc_i18n_measure_unit_create_teaspoon_p,ITs_base_utils_measure_unit_startup,ITs_base_utils_measure_unit_cleanup},
	{"ITc_i18n_parse_position_create_destroy_p",ITc_i18n_parse_position_create_destroy_p,ITs_base_utils_parse_position_startup,ITs_base_utils_parse_position_cleanup},
	{"ITc_i18n_parse_position_create_with_index_p",ITc_i18n_parse_position_create_with_index_p,ITs_base_utils_parse_position_startup,ITs_base_utils_parse_position_cleanup},
	{"ITc_i18n_parse_position_set_get_index_p",ITc_i18n_parse_position_set_get_index_p,ITs_base_utils_parse_position_startup,ITs_base_utils_parse_position_cleanup},
	{"ITc_i18n_parse_position_clone_p",ITc_i18n_parse_position_clone_p,ITs_base_utils_parse_position_startup,ITs_base_utils_parse_position_cleanup},
	{"ITc_i18n_parse_position_set_get_error_index_p",ITc_i18n_parse_position_set_get_error_index_p,ITs_base_utils_parse_position_startup,ITs_base_utils_parse_position_cleanup},
	{"ITc_i18n_alpha_idx_create_destroy_from_locale_id_p",ITc_i18n_alpha_idx_create_destroy_from_locale_id_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_add_labels_with_locale_id_p",ITc_i18n_alpha_idx_add_labels_with_locale_id_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_add_record_p",ITc_i18n_alpha_idx_add_record_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_get_record_name_p",ITc_i18n_alpha_idx_get_record_name_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_get_next_bucket_p",ITc_i18n_alpha_idx_get_next_bucket_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_get_next_record_p",ITc_i18n_alpha_idx_get_next_record_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_get_bucket_record_count_p",ITc_i18n_alpha_idx_get_bucket_record_count_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_get_bucket_label_p",ITc_i18n_alpha_idx_get_bucket_label_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_get_record_data_p",ITc_i18n_alpha_idx_get_record_data_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_set_get_inflow_label_p",ITc_i18n_alpha_idx_set_get_inflow_label_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_set_get_overflow_label_p",ITc_i18n_alpha_idx_set_get_overflow_label_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_set_get_underflow_label_p",ITc_i18n_alpha_idx_set_get_underflow_label_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_set_get_max_label_count_p",ITc_i18n_alpha_idx_set_get_max_label_count_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_get_bucket_count_p",ITc_i18n_alpha_idx_get_bucket_count_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_get_record_count_p",ITc_i18n_alpha_idx_get_record_count_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_get_bucket_index_p",ITc_i18n_alpha_idx_get_bucket_index_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_get_current_bucket_index_p",ITc_i18n_alpha_idx_get_current_bucket_index_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_get_bucket_label_type_p",ITc_i18n_alpha_idx_get_bucket_label_type_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_reset_bucket_iter_p",ITc_i18n_alpha_idx_reset_bucket_iter_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_reset_record_iter_p",ITc_i18n_alpha_idx_reset_record_iter_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_alpha_idx_clear_records_p",ITc_i18n_alpha_idx_clear_records_p,ITs_base_utils_alpha_startup,ITs_base_utils_alpha_cleanup},
	{"ITc_i18n_formattable_create_default_destroy_p",ITc_i18n_formattable_create_default_destroy_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_create_with_udate_p",ITc_i18n_formattable_create_with_udate_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_create_with_double_p",ITc_i18n_formattable_create_with_double_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_create_with_long_p",ITc_i18n_formattable_create_with_long_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_create_with_int64_p",ITc_i18n_formattable_create_with_int64_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_create_with_char_string_p",ITc_i18n_formattable_create_with_char_string_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_create_with_formattable_array_p",ITc_i18n_formattable_create_with_formattable_array_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_clone_p",ITc_i18n_formattable_clone_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_set_get_array_p",ITc_i18n_formattable_set_get_array_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_set_get_date_p",ITc_i18n_formattable_set_get_date_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_set_get_double_p",ITc_i18n_formattable_set_get_double_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_set_get_int64_p",ITc_i18n_formattable_set_get_int64_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_set_get_long_p",ITc_i18n_formattable_set_get_long_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_set_get_string_p",ITc_i18n_formattable_set_get_string_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_get_type_p",ITc_i18n_formattable_get_type_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_is_numeric_p",ITc_i18n_formattable_is_numeric_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_not_equal_p",ITc_i18n_formattable_not_equal_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_equal_p",ITc_i18n_formattable_equal_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_formattable_element_at_p",ITc_i18n_formattable_element_at_p,ITs_base_utils_formattable_startup,ITs_base_utils_formattable_cleanup},
	{"ITc_i18n_utmscale_get_time_scale_value_p",ITc_i18n_utmscale_get_time_scale_value_p,ITs_base_utils_utmscale_startup,ITs_base_utils_utmscale_cleanup},
	{"ITc_i18n_utmscale_from_int64_p",ITc_i18n_utmscale_from_int64_p,ITs_base_utils_utmscale_startup,ITs_base_utils_utmscale_cleanup},
	{"ITc_i18n_utmscale_to_int64_p",ITc_i18n_utmscale_to_int64_p,ITs_base_utils_utmscale_startup,ITs_base_utils_utmscale_cleanup},
	{"ITc_i18n_ubidi_create_destroy_p",ITc_i18n_ubidi_create_destroy_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_count_paragraphs_p",ITc_i18n_ubidi_count_paragraphs_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_count_runs_p",ITc_i18n_ubidi_count_runs_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_base_direction_p",ITc_i18n_ubidi_get_base_direction_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_set_get_class_cb_p",ITc_i18n_ubidi_set_get_class_cb_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_set_context_p",ITc_i18n_ubidi_set_context_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_set_inverse_p",ITc_i18n_ubidi_set_inverse_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_set_line_p",ITc_i18n_ubidi_set_line_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_set_para_p",ITc_i18n_ubidi_set_para_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_set_get_reordering_mode_p",ITc_i18n_ubidi_set_get_reordering_mode_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_set_get_reordering_options_p",ITc_i18n_ubidi_set_get_reordering_options_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_customized_class_p",ITc_i18n_ubidi_get_customized_class_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_direction_p",ITc_i18n_ubidi_get_direction_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_length_p",ITc_i18n_ubidi_get_length_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_level_at_p",ITc_i18n_ubidi_get_level_at_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_logical_index_p",ITc_i18n_ubidi_get_logical_index_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_logical_map_p",ITc_i18n_ubidi_get_logical_map_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_logical_run_p",ITc_i18n_ubidi_get_logical_run_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_paragraph_p",ITc_i18n_ubidi_get_paragraph_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_paragraph_by_index_p",ITc_i18n_ubidi_get_paragraph_by_index_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_para_level_p",ITc_i18n_ubidi_get_para_level_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_processed_length_p",ITc_i18n_ubidi_get_processed_length_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_result_length_p",ITc_i18n_ubidi_get_result_length_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_text_p",ITc_i18n_ubidi_get_text_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_visual_index_p",ITc_i18n_ubidi_get_visual_index_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_visual_map_p",ITc_i18n_ubidi_get_visual_map_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_get_visual_run_p",ITc_i18n_ubidi_get_visual_run_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_invert_map_p",ITc_i18n_ubidi_invert_map_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_is_inverse_p",ITc_i18n_ubidi_is_inverse_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_is_order_paragraphs_ltr_p",ITc_i18n_ubidi_is_order_paragraphs_ltr_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_create_sized_p",ITc_i18n_ubidi_create_sized_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_order_paragraphs_ltr_p",ITc_i18n_ubidi_order_paragraphs_ltr_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_reorder_logical_p",ITc_i18n_ubidi_reorder_logical_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_reorder_visual_p",ITc_i18n_ubidi_reorder_visual_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_write_reordered_p",ITc_i18n_ubidi_write_reordered_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_ubidi_write_reverse_p",ITc_i18n_ubidi_write_reverse_p,ITs_base_utils_ubidi_startup,ITs_base_utils_ubidi_cleanup},
	{"ITc_i18n_uchar_iter_create_destroy_p",ITc_i18n_uchar_iter_create_destroy_p,ITs_base_utils_uchar_iter_startup,ITs_base_utils_uchar_iter_cleanup},
	{"ITc_i18n_uchar_iter_set_string_p",ITc_i18n_uchar_iter_set_string_p,ITs_base_utils_uchar_iter_startup,ITs_base_utils_uchar_iter_cleanup},
	{"ITc_i18n_uchar_iter_set_utf16be_p",ITc_i18n_uchar_iter_set_utf16be_p,ITs_base_utils_uchar_iter_startup,ITs_base_utils_uchar_iter_cleanup},
	{"ITc_i18n_uchar_iter_set_utf8_p",ITc_i18n_uchar_iter_set_utf8_p,ITs_base_utils_uchar_iter_startup,ITs_base_utils_uchar_iter_cleanup},
	{"ITc_i18n_uchar_iter_get_index_p",ITc_i18n_uchar_iter_get_index_p,ITs_base_utils_uchar_iter_startup,ITs_base_utils_uchar_iter_cleanup},
	{"ITc_i18n_uchar_iter_move_p",ITc_i18n_uchar_iter_move_p,ITs_base_utils_uchar_iter_startup,ITs_base_utils_uchar_iter_cleanup},
	{"ITc_i18n_uchar_iter_has_next_p",ITc_i18n_uchar_iter_has_next_p,ITs_base_utils_uchar_iter_startup,ITs_base_utils_uchar_iter_cleanup},
	{"ITc_i18n_uchar_iter_has_previous_p",ITc_i18n_uchar_iter_has_previous_p,ITs_base_utils_uchar_iter_startup,ITs_base_utils_uchar_iter_cleanup},
	{"ITc_i18n_uchar_iter_current_p",ITc_i18n_uchar_iter_current_p,ITs_base_utils_uchar_iter_startup,ITs_base_utils_uchar_iter_cleanup},
	{"ITc_i18n_uchar_iter_next_p",ITc_i18n_uchar_iter_next_p,ITs_base_utils_uchar_iter_startup,ITs_base_utils_uchar_iter_cleanup},
	{"ITc_i18n_uchar_iter_previous_p",ITc_i18n_uchar_iter_previous_p,ITs_base_utils_uchar_iter_startup,ITs_base_utils_uchar_iter_cleanup},
	{"ITc_i18n_uchar_iter_get_set_state_p",ITc_i18n_uchar_iter_get_set_state_p,ITs_base_utils_uchar_iter_startup,ITs_base_utils_uchar_iter_cleanup},
	{"ITc_base_utils_i18n_uversion_get_version_p",ITc_base_utils_i18n_uversion_get_version_p,ITs_base_utils_uversion_startup,ITs_base_utils_uversion_cleanup},
	{"ITc_base_utils_i18n_uversion_to_string_p",ITc_base_utils_i18n_uversion_to_string_p,ITs_base_utils_uversion_startup,ITs_base_utils_uversion_cleanup},
	{"ITc_base_utils_i18n_uversion_from_string_p",ITc_base_utils_i18n_uversion_from_string_p,ITs_base_utils_uversion_startup,ITs_base_utils_uversion_cleanup},
	{"ITc_base_utils_i18n_uversion_from_ustring_p",ITc_base_utils_i18n_uversion_from_ustring_p,ITs_base_utils_uversion_startup,ITs_base_utils_uversion_cleanup},
	{"ITc_i18n_measure_format_format_buff_p",ITc_i18n_measure_format_format_buff_p,ITs_base_utils_measure_format_startup,ITs_base_utils_measure_format_cleanup},
	{"ITc_i18n_measure_format_format_measures_p", ITc_i18n_measure_format_format_measures_p, ITs_base_utils_measure_format_startup, ITs_base_utils_measure_format_cleanup},
	{"ITc_i18n_measure_format_format_measure_per_unit_p", ITc_i18n_measure_format_format_measure_per_unit_p, ITs_base_utils_measure_format_startup, ITs_base_utils_measure_format_cleanup},
	{"ITc_i18n_measure_format_get_unit_display_name", ITc_i18n_measure_format_get_unit_display_name, ITs_base_utils_measure_format_startup, ITs_base_utils_measure_format_cleanup},
	{"ITc_i18n_uchar_has_binary_property_p", ITc_i18n_uchar_has_binary_property_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_alphabetic_p", ITc_i18n_uchar_is_alphabetic_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_lowercase_p", ITc_i18n_uchar_is_lowercase_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_uppercase_p", ITc_i18n_uchar_is_uppercase_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_white_space_p", ITc_i18n_uchar_is_white_space_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_get_int_property_min_value_p", ITc_i18n_uchar_get_int_property_min_value_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_get_int_property_max_value_p", ITc_i18n_uchar_get_int_property_max_value_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_get_numeric_value_p", ITc_i18n_uchar_get_numeric_value_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_lower_p", ITc_i18n_uchar_is_lower_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_upper_p", ITc_i18n_uchar_is_upper_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_title_p", ITc_i18n_uchar_is_title_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_digit_p", ITc_i18n_uchar_is_digit_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_alpha_p", ITc_i18n_uchar_is_alpha_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_alnum_p", ITc_i18n_uchar_is_alnum_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_xdigit_p", ITc_i18n_uchar_is_xdigit_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_punct_p", ITc_i18n_uchar_is_punct_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_graph_p", ITc_i18n_uchar_is_graph_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_blank_p", ITc_i18n_uchar_is_blank_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_defined_p", ITc_i18n_uchar_is_defined_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_space_p", ITc_i18n_uchar_is_space_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_java_space_char_p", ITc_i18n_uchar_is_java_space_char_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_whitespace_p", ITc_i18n_uchar_is_whitespace_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_control_p", ITc_i18n_uchar_is_control_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_iso_control_p", ITc_i18n_uchar_is_iso_control_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_printable_p", ITc_i18n_uchar_is_printable_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_base_p", ITc_i18n_uchar_is_base_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_char_direction_p", ITc_i18n_uchar_char_direction_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_mirrored_p", ITc_i18n_uchar_is_mirrored_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_char_mirror_p" ,ITc_i18n_uchar_char_mirror_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_get_bidi_paired_bracket_p", ITc_i18n_uchar_get_bidi_paired_bracket_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_char_type_p", ITc_i18n_uchar_char_type_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_enum_char_types_p", ITc_i18n_uchar_enum_char_types_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_get_combining_class_p", ITc_i18n_uchar_get_combining_class_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_char_digit_value_p", ITc_i18n_uchar_char_digit_value_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_char_name_p", ITc_i18n_uchar_char_name_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_char_from_name_p", ITc_i18n_uchar_char_from_name_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_enum_char_names_p", ITc_i18n_uchar_enum_char_names_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_get_property_enum_p", ITc_i18n_uchar_get_property_enum_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_get_property_name_p", ITc_i18n_uchar_get_property_name_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_get_property_value_name_p", ITc_i18n_uchar_get_property_value_name_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_get_property_value_enum_p", ITc_i18n_uchar_get_property_value_enum_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_id_start_p", ITc_i18n_uchar_is_id_start_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_id_part_p", ITc_i18n_uchar_is_id_part_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_id_ignorable_p", ITc_i18n_uchar_is_id_ignorable_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_java_id_start_p", ITc_i18n_uchar_is_java_id_start_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_is_java_id_part_p", ITc_i18n_uchar_is_java_id_part_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_to_lower_p", ITc_i18n_uchar_to_lower_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_to_upper_p", ITc_i18n_uchar_to_upper_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_to_title_p", ITc_i18n_uchar_to_title_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_fold_case_p", ITc_i18n_uchar_fold_case_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_digit_p", ITc_i18n_uchar_digit_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_for_digit_p", ITc_i18n_uchar_for_digit_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_char_age_p", ITc_i18n_uchar_char_age_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_get_unicode_version_p", ITc_i18n_uchar_get_unicode_version_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_uchar_get_fc_nfkc_closure_p", ITc_i18n_uchar_get_fc_nfkc_closure_p, ITs_base_utils_uchar_startup, ITs_base_utils_uchar_cleanup},
	{"ITc_i18n_ulocale_is_bogus_p", ITc_i18n_ulocale_is_bogus_p, ITs_base_utils_ulocale_startup,ITs_base_utils_ulocale_cleanup},
	{"ITc_i18n_plural_rules_create_destroy_p", ITc_i18n_plural_rules_create_destroy_p, ITs_base_utils_plural_rules_startup, ITs_base_utils_plural_rules_cleanup},
	{"ITc_i18n_plural_rules_clone_p", ITc_i18n_plural_rules_clone_p, ITs_base_utils_plural_rules_startup, ITs_base_utils_plural_rules_cleanup},
	{"ITc_i18n_plural_rules_create_rules_from_descr_p", ITc_i18n_plural_rules_create_rules_from_descr_p, ITs_base_utils_plural_rules_startup, ITs_base_utils_plural_rules_cleanup},
	{"ITc_i18n_plural_rules_for_locale_id_p", ITc_i18n_plural_rules_for_locale_id_p, ITs_base_utils_plural_rules_startup, ITs_base_utils_plural_rules_cleanup},
	{"ITc_i18n_plural_rules_select_int32_p", ITc_i18n_plural_rules_select_int32_p, ITs_base_utils_plural_rules_startup, ITs_base_utils_plural_rules_cleanup},
	{"ITc_i18n_plural_rules_select_double_p", ITc_i18n_plural_rules_select_double_p, ITs_base_utils_plural_rules_startup, ITs_base_utils_plural_rules_cleanup},
	{"ITc_i18n_plural_rules_get_keywords_p", ITc_i18n_plural_rules_get_keywords_p, ITs_base_utils_plural_rules_startup, ITs_base_utils_plural_rules_cleanup},
	{"ITc_i18n_plural_rules_get_samples_p", ITc_i18n_plural_rules_get_samples_p, ITs_base_utils_plural_rules_startup, ITs_base_utils_plural_rules_cleanup},
	{"ITc_i18n_plural_rules_is_keyword_p", ITc_i18n_plural_rules_is_keyword_p, ITs_base_utils_plural_rules_startup, ITs_base_utils_plural_rules_cleanup},
	{"ITc_i18n_plural_rules_get_keyword_other_p", ITc_i18n_plural_rules_get_keyword_other_p, ITs_base_utils_plural_rules_startup, ITs_base_utils_plural_rules_cleanup},
	{"ITc_i18n_immutable_idx_create_destroy", ITc_i18n_immutable_idx_create_destroy, ITs_base_utils_immutable_idx_startup, ITs_base_utils_immutable_idx_cleanup},
	{"ITc_i18n_immutable_idx_get_bucket_count", ITc_i18n_immutable_idx_get_bucket_count, ITs_base_utils_immutable_idx_startup, ITs_base_utils_immutable_idx_cleanup},
	{"ITc_i18n_immutable_idx_get_bucket_index", ITc_i18n_immutable_idx_get_bucket_index, ITs_base_utils_immutable_idx_startup, ITs_base_utils_immutable_idx_cleanup},
	{"ITc_i18n_immutable_idx_get_bucket_label", ITc_i18n_immutable_idx_get_bucket_label, ITs_base_utils_immutable_idx_startup, ITs_base_utils_immutable_idx_cleanup},
	{"ITc_i18n_immutable_idx_get_bucket_label_type", ITc_i18n_immutable_idx_get_bucket_label_type, ITs_base_utils_immutable_idx_startup, ITs_base_utils_immutable_idx_cleanup},
	{"ITc_i18n_plural_format_create_destroy_p", ITc_i18n_plural_format_create_destroy_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_create_from_locale_p", ITc_i18n_plural_format_create_from_locale_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_create_from_rules_pattern_p" ,ITc_i18n_plural_format_create_from_rules_pattern_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_create_from_locale_type_pattern_p", ITc_i18n_plural_format_create_from_locale_type_pattern_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_create_from_locale_type_p", ITc_i18n_plural_format_create_from_locale_type_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_create_from_locale_pattern_p", ITc_i18n_plural_format_create_from_locale_pattern_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_create_from_locale_rules_pattern_p", ITc_i18n_plural_format_create_from_locale_rules_pattern_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_clone_p", ITc_i18n_plural_format_clone_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_apply_pattern_p", ITc_i18n_plural_format_apply_pattern_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_format_int32_p", ITc_i18n_plural_format_format_int32_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_format_double_p", ITc_i18n_plural_format_format_double_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_format_formattable_p", ITc_i18n_plural_format_format_formattable_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_set_number_format_p", ITc_i18n_plural_format_set_number_format_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_plural_format_to_pattern_p", ITc_i18n_plural_format_to_pattern_p, ITs_base_utils_plural_format_startup, ITs_base_utils_plural_format_cleanup},
	{"ITc_i18n_date_interval_create_destroy_p", ITc_i18n_date_interval_create_destroy_p, ITs_base_utils_date_interval_startup, ITs_base_utils_date_interval_cleanup},
	{"ITc_i18n_date_interval_clone_p", ITc_i18n_date_interval_clone_p, ITs_base_utils_date_interval_startup, ITs_base_utils_date_interval_cleanup},
	{"ITc_i18n_date_interval_get_from_date_p", ITc_i18n_date_interval_get_from_date_p, ITs_base_utils_date_interval_startup, ITs_base_utils_date_interval_cleanup},
	{"ITc_i18n_date_interval_get_to_date_p", ITc_i18n_date_interval_get_to_date_p, ITs_base_utils_date_interval_startup, ITs_base_utils_date_interval_cleanup},
	{"ITc_i18n_date_interval_equals_p", ITc_i18n_date_interval_equals_p, ITs_base_utils_date_interval_startup, ITs_base_utils_date_interval_cleanup},
	{"ITc_i18n_date_interval_fmt_create_destroy_p", ITc_i18n_date_interval_fmt_create_destroy_p, ITs_base_utils_date_interval_fmt_startup, ITs_base_utils_date_interval_fmt_cleanup},
	{"ITc_i18n_date_interval_fmt_clone_p", ITc_i18n_date_interval_fmt_clone_p, ITs_base_utils_date_interval_fmt_startup, ITs_base_utils_date_interval_fmt_cleanup},
	{"ITc_i18n_date_interval_fmt_create_from_locale_p", ITc_i18n_date_interval_fmt_create_from_locale_p, ITs_base_utils_date_interval_fmt_startup, ITs_base_utils_date_interval_fmt_cleanup},
	{"ITc_i18n_date_interval_fmt_set_get_time_zone_p", ITc_i18n_date_interval_fmt_set_get_time_zone_p, ITs_base_utils_date_interval_fmt_startup, ITs_base_utils_date_interval_fmt_cleanup},
	{"ITc_i18n_date_interval_fmt_adopt_time_zone_p", ITc_i18n_date_interval_fmt_adopt_time_zone_p, ITs_base_utils_date_interval_fmt_startup, ITs_base_utils_date_interval_fmt_cleanup},
	{"ITc_i18n_date_interval_fmt_format_with_date_interval_p", ITc_i18n_date_interval_fmt_format_with_date_interval_p, ITs_base_utils_date_interval_fmt_startup, ITs_base_utils_date_interval_fmt_cleanup},
	{"ITc_i18n_date_interval_fmt_format_with_calendar_p", ITc_i18n_date_interval_fmt_format_with_calendar_p, ITs_base_utils_date_interval_fmt_startup, ITs_base_utils_date_interval_fmt_cleanup},
	{"ITc_i18n_date_interval_fmt_equals_p", ITc_i18n_date_interval_fmt_equals_p, ITs_base_utils_date_interval_fmt_startup, ITs_base_utils_date_interval_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_create_destroy_p", ITc_i18n_simple_date_fmt_create_destroy_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_create_from_pattern_p", ITc_i18n_simple_date_fmt_create_from_pattern_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_create_from_pattern_override_p", ITc_i18n_simple_date_fmt_create_from_pattern_override_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_create_from_pattern_locale_p", ITc_i18n_simple_date_fmt_create_from_pattern_locale_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_create_from_pattern_override_locale_p", ITc_i18n_simple_date_fmt_create_from_pattern_override_locale_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_clone_p", ITc_i18n_simple_date_fmt_clone_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_equals_p", ITc_i18n_simple_date_fmt_equals_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_format_with_field_position_p", ITc_i18n_simple_date_fmt_format_with_field_position_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_parse_p", ITc_i18n_simple_date_fmt_parse_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_set_get_2digit_year_start_p", ITc_i18n_simple_date_fmt_set_get_2digit_year_start_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_to_pattern_p", ITc_i18n_simple_date_fmt_to_pattern_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_to_localized_pattern_p", ITc_i18n_simple_date_fmt_to_localized_pattern_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_apply_pattern_p", ITc_i18n_simple_date_fmt_apply_pattern_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_apply_localized_pattern_p", ITc_i18n_simple_date_fmt_apply_localized_pattern_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_adopt_calendar_p", ITc_i18n_simple_date_fmt_adopt_calendar_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup},
	{"ITc_i18n_simple_date_fmt_set_context_p", ITc_i18n_simple_date_fmt_set_context_p, ITs_base_utils_simple_date_fmt_startup, ITs_base_utils_simple_date_fmt_cleanup	 },
	{"ITs_base_utils_i18n_loc_disp_names_create_p", ITs_base_utils_i18n_loc_disp_names_create_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_create_from_dialect_p", ITs_base_utils_i18n_loc_disp_names_create_from_dialect_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_create_from_context_p", ITs_base_utils_i18n_loc_disp_names_create_from_context_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_get_locale_p", ITs_base_utils_i18n_loc_disp_names_get_locale_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_get_dialect_handling_p", ITs_base_utils_i18n_loc_disp_names_get_dialect_handling_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_get_context_p", ITs_base_utils_i18n_loc_disp_names_get_context_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_get_loc_disp_name_p", ITs_base_utils_i18n_loc_disp_names_get_loc_disp_name_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_get_language_disp_name_p", ITs_base_utils_i18n_loc_disp_names_get_language_disp_name_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_get_script_disp_name_p", ITs_base_utils_i18n_loc_disp_names_get_script_disp_name_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_get_script_disp_name_with_script_code_p", ITs_base_utils_i18n_loc_disp_names_get_script_disp_name_with_script_code_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_get_region_disp_name_p", ITs_base_utils_i18n_loc_disp_names_get_region_disp_name_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_get_variant_disp_name_p", ITs_base_utils_i18n_loc_disp_names_get_variant_disp_name_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_get_key_disp_name_p", ITs_base_utils_i18n_loc_disp_names_get_key_disp_name_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},
	{"ITs_base_utils_i18n_loc_disp_names_get_key_value_disp_name_p", ITs_base_utils_i18n_loc_disp_names_get_key_value_disp_name_p, ITs_base_utils_loc_disp_names_startup, ITs_base_utils_loc_disp_names_cleanup},

        {"ITc_i18n_utext_create_for_UTF8_p", ITc_i18n_utext_create_for_UTF8_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup },
        {"ITc_i18n_utext_create_for_uchars_p", ITc_i18n_utext_create_for_uchars_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_clone_p", ITc_i18n_utext_clone_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_equals_p", ITc_i18n_utext_equals_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_native_length_p", ITc_i18n_utext_native_length_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_is_length_expensive_p", ITc_i18n_utext_is_length_expensive_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_char32_at_p", ITc_i18n_utext_char32_at_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_current32_p", ITc_i18n_utext_current32_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_next32_p", ITc_i18n_utext_next32_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_previous32_p",ITc_i18n_utext_previous32_p , ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_next32_from_p", ITc_i18n_utext_next32_from_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_previous32_from_p", ITc_i18n_utext_previous32_from_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_set_get_native_index_p", ITc_i18n_utext_set_get_native_index_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_move_index32_p", ITc_i18n_utext_move_index32_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_get_previous_native_index_p", ITc_i18n_utext_get_previous_native_index_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_extract_p", ITc_i18n_utext_extract_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_is_writable_p", ITc_i18n_utext_is_writable_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_has_meta_data_p", ITc_i18n_utext_has_meta_data_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},
        {"ITc_i18n_utext_freeze_p", ITc_i18n_utext_freeze_p, ITs_base_utils_utext_startup, ITs_base_utils_utext_cleanup},

        {"ITc_i18n_uscript_get_codes_p", ITc_i18n_uscript_get_codes_p, ITs_base_utils_uscript_startup, ITs_base_utils_uscript_cleanup},
        {"ITc_i18n_uscript_get_name_p", ITc_i18n_uscript_get_name_p, ITs_base_utils_uscript_startup, ITs_base_utils_uscript_cleanup},
        {"ITc_i18n_uscript_get_short_name_p", ITc_i18n_uscript_get_short_name_p, ITs_base_utils_uscript_startup, ITs_base_utils_uscript_cleanup},
        {"ITc_i18n_uscript_get_script_p", ITc_i18n_uscript_get_script_p, ITs_base_utils_uscript_startup, ITs_base_utils_uscript_cleanup},
        {"ITc_i18n_uscript_has_script_p", ITc_i18n_uscript_has_script_p, ITs_base_utils_uscript_startup, ITs_base_utils_uscript_cleanup},
        {"ITc_i18n_uscript_get_script_extensions_p", ITc_i18n_uscript_get_script_extensions_p, ITs_base_utils_uscript_startup, ITs_base_utils_uscript_cleanup},
        {"ITc_i18n_uscript_get_sample_string_p", ITc_i18n_uscript_get_sample_string_p, ITs_base_utils_uscript_startup, ITs_base_utils_uscript_cleanup},
        {"ITc_i18n_uscript_get_usage_p", ITc_i18n_uscript_get_usage_p, ITs_base_utils_uscript_startup, ITs_base_utils_uscript_cleanup},
        {"ITc_i18n_uscript_is_right_to_left_p", ITc_i18n_uscript_is_right_to_left_p, ITs_base_utils_uscript_startup, ITs_base_utils_uscript_cleanup},
        {"ITc_i18n_uscript_breaks_between_letters_p", ITc_i18n_uscript_breaks_between_letters_p, ITs_base_utils_uscript_startup, ITs_base_utils_uscript_cleanup},
        {"ITc_i18n_uscript_is_cased_p", ITc_i18n_uscript_is_cased_p, ITs_base_utils_uscript_startup, ITs_base_utils_uscript_cleanup},

        {"ITc_i18n_unormalization_get_nfc_instance_p", ITc_i18n_unormalization_get_nfc_instance_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_get_nfd_instance_p", ITc_i18n_unormalization_get_nfd_instance_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_get_nfkc_instance_p", ITc_i18n_unormalization_get_nfkc_instance_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_get_nfkc_casefold_instance_p", ITc_i18n_unormalization_get_nfkc_casefold_instance_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_get_nfkd_instance_p", ITc_i18n_unormalization_get_nfkd_instance_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_create_filtered_p", ITc_i18n_unormalization_create_filtered_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_destroy_p", ITc_i18n_unormalization_destroy_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_normalize_second_and_append_p", ITc_i18n_unormalization_normalize_second_and_append_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_append_p", ITc_i18n_unormalization_append_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_get_decomposition_p", ITc_i18n_unormalization_get_decomposition_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_get_raw_decomposition_p", ITc_i18n_unormalization_get_raw_decomposition_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_compose_pair_p", ITc_i18n_unormalization_compose_pair_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_is_normalized_p", ITc_i18n_unormalization_is_normalized_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_quick_check_p", ITc_i18n_unormalization_quick_check_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_span_quick_check_yes_p", ITc_i18n_unormalization_span_quick_check_yes_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalizer_has_boundary_before_p", ITc_i18n_unormalizer_has_boundary_before_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalizer_has_boundary_after_p", ITc_i18n_unormalizer_has_boundary_after_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},
        {"ITc_i18n_unormalization_is_inert_p", ITc_i18n_unormalization_is_inert_p, ITs_base_utils_unormalization_startup, ITs_base_utils_unormalization_cleanup},

        {"ITc_i18n_unumsys_create_p", ITc_i18n_unumsys_create_p, ITs_base_utils_unumsys_startup, ITs_base_utils_unumsys_cleanup},
        {"ITc_i18n_unumsys_create_by_name_p", ITc_i18n_unumsys_create_by_name_p, ITs_base_utils_unumsys_startup, ITs_base_utils_unumsys_cleanup},
        {"ITc_i18n_unumsys_get_available_names_p", ITc_i18n_unumsys_get_available_names_p, ITs_base_utils_unumsys_startup, ITs_base_utils_unumsys_cleanup},
        {"ITc_i18n_unumsys_get_name_p", ITc_i18n_unumsys_get_name_p, ITs_base_utils_unumsys_startup, ITs_base_utils_unumsys_cleanup},
        {"ITc_i18n_unumsys_is_algorithmic_p", ITc_i18n_unumsys_is_algorithmic_p, ITs_base_utils_unumsys_startup, ITs_base_utils_unumsys_cleanup},
        {"ITc_i18n_unumsys_get_radix_p", ITc_i18n_unumsys_get_radix_p, ITs_base_utils_unumsys_startup, ITs_base_utils_unumsys_cleanup},
        {"ITc_i18n_unumsys_get_description_p", ITc_i18n_unumsys_get_description_p, ITs_base_utils_unumsys_startup, ITs_base_utils_unumsys_cleanup},

        {"ITc_i18n_uidna_label_to_ascii_p", ITc_i18n_uidna_label_to_ascii_p, ITs_base_utils_uidna_startup, ITs_base_utils_uidna_cleanup},
        {"ITc_i18n_uidna_label_to_unicode_p", ITc_i18n_uidna_label_to_unicode_p, ITs_base_utils_uidna_startup, ITs_base_utils_uidna_cleanup},
        {"ITc_i18n_uidna_name_to_ascii_p", ITc_i18n_uidna_name_to_ascii_p, ITs_base_utils_uidna_startup, ITs_base_utils_uidna_cleanup},
        {"ITc_i18n_uidna_name_to_unicode_p", ITc_i18n_uidna_name_to_unicode_p, ITs_base_utils_uidna_startup, ITs_base_utils_uidna_cleanup},
        {"ITc_i18n_uidna_label_to_ascii_UTF8_p", ITc_i18n_uidna_label_to_ascii_UTF8_p, ITs_base_utils_uidna_startup, ITs_base_utils_uidna_cleanup},
        {"ITc_i18n_uidna_label_to_unicode_UTF8_p", ITc_i18n_uidna_label_to_unicode_UTF8_p, ITs_base_utils_uidna_startup, ITs_base_utils_uidna_cleanup},
        {"ITc_i18n_uidna_name_to_ascii_UTF8_p", ITc_i18n_uidna_name_to_ascii_UTF8_p, ITs_base_utils_uidna_startup, ITs_base_utils_uidna_cleanup},
        {"ITc_i18n_uidna_name_to_unicode_UTF8_p", ITc_i18n_uidna_name_to_unicode_UTF8_p, ITs_base_utils_uidna_startup, ITs_base_utils_uidna_cleanup},
        {"ITc_i18n_uidna_info_get_is_trans_different_p", ITc_i18n_uidna_info_get_is_trans_different_p, ITs_base_utils_uidna_startup, ITs_base_utils_uidna_cleanup},
        {"ITc_i18n_uidna_info_get_errors_p", ITc_i18n_uidna_info_get_errors_p, ITs_base_utils_uidna_startup, ITs_base_utils_uidna_cleanup},
        {"ITc_i18n_uidna_info_destroy_p", ITc_i18n_uidna_info_destroy_p, ITs_base_utils_uidna_startup, ITs_base_utils_uidna_cleanup},

        {"ITc_i18n_ucsdet_create_destroy_p", ITc_i18n_ucsdet_create_destroy_p, ITs_base_utils_ucsdet_startup, ITs_base_utils_ucsdet_cleanup},
        {"ITc_i18n_ucsdet_set_text_p", ITc_i18n_ucsdet_set_text_p, ITs_base_utils_ucsdet_startup, ITs_base_utils_ucsdet_cleanup},
        {"ITc_i18n_ucsdet_set_declared_encoding_p", ITc_i18n_ucsdet_set_declared_encoding_p, ITs_base_utils_ucsdet_startup, ITs_base_utils_ucsdet_cleanup},
        {"ITc_i18n_ucsdet_detect_p", ITc_i18n_ucsdet_detect_p, ITs_base_utils_ucsdet_startup, ITs_base_utils_ucsdet_cleanup},
        {"ITc_i18n_ucsdet_detect_all_p", ITc_i18n_ucsdet_detect_all_p, ITs_base_utils_ucsdet_startup, ITs_base_utils_ucsdet_cleanup},
        {"ITc_i18n_ucsdet_get_name_p", ITc_i18n_ucsdet_get_name_p, ITs_base_utils_ucsdet_startup, ITs_base_utils_ucsdet_cleanup},
        {"ITc_i18n_ucsdet_get_confidence_p", ITc_i18n_ucsdet_get_confidence_p, ITs_base_utils_ucsdet_startup, ITs_base_utils_ucsdet_cleanup},
        {"ITc_i18n_ucsdet_get_language_p", ITc_i18n_ucsdet_get_language_p, ITs_base_utils_ucsdet_startup, ITs_base_utils_ucsdet_cleanup},
        {"ITc_i18n_ucsdet_get_uchars_p", ITc_i18n_ucsdet_get_uchars_p, ITs_base_utils_ucsdet_startup, ITs_base_utils_ucsdet_cleanup},
        {"ITc_i18n_ucsdet_get_all_detectable_charsets_p", ITc_i18n_ucsdet_get_all_detectable_charsets_p, ITs_base_utils_ucsdet_startup, ITs_base_utils_ucsdet_cleanup},
        {"ITc_i18n_ucsdet_is_input_filter_enabled", ITc_i18n_ucsdet_is_input_filter_enabled, ITs_base_utils_ucsdet_startup, ITs_base_utils_ucsdet_cleanup},
        {"ITc_i18n_ucsdet_enable_input_filter_p", ITc_i18n_ucsdet_enable_input_filter_p, ITs_base_utils_ucsdet_startup, ITs_base_utils_ucsdet_cleanup},

        {"ITc_i18n_ucnvsel_create_destroy_p", ITc_i18n_ucnvsel_create_destroy_p, ITs_base_utils_ucnvsel_startup, ITs_base_utils_ucnvsel_cleanup},
        {"ITc_i18n_ucnvsel_create_from_serialized_p", ITc_i18n_ucnvsel_create_from_serialized_p, ITs_base_utils_ucnvsel_startup, ITs_base_utils_ucnvsel_cleanup},
        {"ITc_i18n_ucnvsel_serialize_p", ITc_i18n_ucnvsel_serialize_p, ITs_base_utils_ucnvsel_startup, ITs_base_utils_ucnvsel_cleanup},
        {"ITc_i18n_ucnvsel_select_for_string_p", ITc_i18n_ucnvsel_select_for_string_p, ITs_base_utils_ucnvsel_startup, ITs_base_utils_ucnvsel_cleanup},
        {"ITc_i18n_ucnvsel_select_for_utf8_p", ITc_i18n_ucnvsel_select_for_utf8_p, ITs_base_utils_ucnvsel_startup, ITs_base_utils_ucnvsel_cleanup},

        {"ITc_i18n_ucnv_get_max_bytes_for_string_p", ITc_i18n_ucnv_get_max_bytes_for_string_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_compare_names_p", ITc_i18n_ucnv_compare_names_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_create_destroy_p", ITc_i18n_ucnv_create_destroy_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_create_unicode_p", ITc_i18n_ucnv_create_unicode_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_create_ccsid_p", ITc_i18n_ucnv_create_ccsid_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_safe_clone_p", ITc_i18n_ucnv_safe_clone_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_set_get_subst_chars_p", ITc_i18n_ucnv_set_get_subst_chars_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_set_subst_string_p", ITc_i18n_ucnv_set_subst_string_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_invalid_chars_p", ITc_i18n_ucnv_get_invalid_chars_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_invalid_uchars_p", ITc_i18n_ucnv_get_invalid_uchars_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_reset_p", ITc_i18n_ucnv_reset_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_reset_to_unicode_p", ITc_i18n_ucnv_reset_to_unicode_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_reset_from_unicode_p", ITc_i18n_ucnv_reset_from_unicode_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_max_char_size_p", ITc_i18n_ucnv_get_max_char_size_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_min_char_size_p", ITc_i18n_ucnv_get_min_char_size_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_display_name_p", ITc_i18n_ucnv_get_display_name_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_name_p", ITc_i18n_ucnv_get_name_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_ccsid_p", ITc_i18n_ucnv_get_ccsid_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_platform_p", ITc_i18n_ucnv_get_platform_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_type_p", ITc_i18n_ucnv_get_type_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_starters_p", ITc_i18n_ucnv_get_starters_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_unicode_set_p", ITc_i18n_ucnv_get_unicode_set_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_from_unicode_p", ITc_i18n_ucnv_from_unicode_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_to_unicode_p", ITc_i18n_ucnv_to_unicode_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_from_uchars_p", ITc_i18n_ucnv_from_uchars_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_to_uchars_p", ITc_i18n_ucnv_to_uchars_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_next_uchar_p", ITc_i18n_ucnv_get_next_uchar_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_convert_ex_p", ITc_i18n_ucnv_convert_ex_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_convert_p", ITc_i18n_ucnv_convert_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_from_algorithmic_p", ITc_i18n_ucnv_from_algorithmic_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_to_algorithmic_p", ITc_i18n_ucnv_to_algorithmic_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_flush_cache_p", ITc_i18n_ucnv_flush_cache_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_count_available_p", ITc_i18n_ucnv_count_available_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_available_name_p", ITc_i18n_ucnv_get_available_name_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_create_all_names_p", ITc_i18n_ucnv_create_all_names_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_count_aliases_p", ITc_i18n_ucnv_count_aliases_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_aliases_p", ITc_i18n_ucnv_get_aliases_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_alias_p", ITc_i18n_ucnv_get_alias_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_create_standard_names_p", ITc_i18n_ucnv_create_standard_names_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_count_standards_p", ITc_i18n_ucnv_count_standards_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_standard_p", ITc_i18n_ucnv_get_standard_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_standard_name_p", ITc_i18n_ucnv_get_standard_name_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_get_canonical_name_p", ITc_i18n_ucnv_get_canonical_name_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_set_get_default_name_p", ITc_i18n_ucnv_set_get_default_name_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_fix_file_separator_p", ITc_i18n_ucnv_fix_file_separator_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_is_ambiguous_p", ITc_i18n_ucnv_is_ambiguous_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_set_fallback_p", ITc_i18n_ucnv_set_fallback_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_uses_fallback_p", ITc_i18n_ucnv_uses_fallback_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_detect_unicode_signature_p", ITc_i18n_ucnv_detect_unicode_signature_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_from_ucount_pending_p", ITc_i18n_ucnv_from_ucount_pending_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_to_ucount_pending_p", ITc_i18n_ucnv_to_ucount_pending_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},
        {"ITc_i18n_ucnv_is_fixed_width_p", ITc_i18n_ucnv_is_fixed_width_p, ITs_base_utils_ucnv_startup, ITs_base_utils_ucnv_cleanup},

        {"ITc_i18n_ures_create_destroy_p", ITc_i18n_ures_create_destroy_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_create_direct_p", ITc_i18n_ures_create_direct_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_create_unicode_p", ITc_i18n_ures_create_unicode_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_version_p", ITc_i18n_ures_get_version_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_locale_by_type_p", ITc_i18n_ures_get_locale_by_type_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_string_p", ITc_i18n_ures_get_string_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_UTF8_string_p", ITc_i18n_ures_get_UTF8_string_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_binary_p", ITc_i18n_ures_get_binary_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_int_vector_p", ITc_i18n_ures_get_int_vector_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_uint_p", ITc_i18n_ures_get_uint_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_int_p", ITc_i18n_ures_get_int_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_size_p", ITc_i18n_ures_get_size_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_type_p", ITc_i18n_ures_get_type_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_key_p", ITc_i18n_ures_get_key_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_reset_iterator_p", ITc_i18n_ures_reset_iterator_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_has_next_p", ITc_i18n_ures_has_next_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_next_resource_p", ITc_i18n_ures_get_next_resource_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_next_string_p", ITc_i18n_ures_get_next_string_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_by_index_p", ITc_i18n_ures_get_by_index_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_string_by_index_p", ITc_i18n_ures_get_string_by_index_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_UTF8_string_by_index_p", ITc_i18n_ures_get_UTF8_string_by_index_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_by_key_p", ITc_i18n_ures_get_by_key_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_string_by_key_p", ITc_i18n_ures_get_string_by_key_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {"ITc_i18n_ures_get_UTF8_string_by_key_p", ITc_i18n_ures_get_UTF8_string_by_key_p, ITs_base_utils_ures_startup, ITs_base_utils_ures_cleanup},
        {NULL, NULL}

};

#endif // __TCT_BASE-UTILS-NATIVE_H__
