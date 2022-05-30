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
#ifndef __TCT_NFC-NATIVE_H__
#define __TCT_NFC-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_nfc_se_startup(void);
extern void ITs_nfc_se_cleanup(void);
extern void ITs_nfc_ndef_startup(void);
extern void ITs_nfc_ndef_cleanup(void);
extern void ITs_nfc_snep_startup(void);
extern void ITs_nfc_snep_cleanup(void);
extern void ITs_nfc_manager_startup(void);
extern void ITs_nfc_manager_cleanup(void);

extern int ITc_nfc_se_get_card_emulation_mode_p(void);
extern int ITc_nfc_manager_get_se_type_p(void);
extern int ITc_nfc_se_set_default_route_p(void);
extern int ITc_nfc_se_register_unregister_aid_p(void);
extern int ITc_nfc_se_is_activated_handler_for_aid_p(void);
extern int ITc_nfc_se_is_activated_handler_for_category_p(void);
extern int ITc_nfc_se_foreach_registered_aids_p(void);
extern int ITc_nfc_ndef_record_create_destroy_p(void);
extern int ITc_nfc_ndef_record_create_text_p(void);
extern int ITc_nfc_ndef_record_create_uri_p(void);
extern int ITc_nfc_ndef_record_create_mime_p(void);
extern int ITc_nfc_ndef_message_create_destroy_p(void);
extern int ITc_nfc_ndef_message_get_record_count_p(void);
extern int ITc_nfc_ndef_message_append_record_p(void);
extern int ITc_nfc_ndef_message_insert_remove_record_p(void);
extern int ITc_nfc_ndef_message_get_record_p(void);
extern int ITc_nfc_ndef_message_get_rawdata_create_from_rawdata_p(void);
extern int ITc_nfc_ndef_record_get_payload_p(void);
extern int ITc_nfc_ndef_record_set_get_id_p(void);
extern int ITc_nfc_ndef_record_get_type_p(void);
extern int ITc_nfc_ndef_record_get_tnf_p(void);
extern int ITc_nfc_ndef_record_get_text_p(void);
extern int ITc_nfc_ndef_record_get_langcode_p(void);
extern int ITc_nfc_ndef_record_get_encode_type_p(void);
extern int ITc_nfc_ndef_record_get_uri_p(void);
extern int ITc_nfc_ndef_record_get_mime_type_p(void);
extern int ITc_nfc_snep_register_unregister_server_p(void);
extern int ITc_nfc_is_supported_p(void);
extern int ITc_nfc_manager_initialize_deinitialize_p(void);
extern int ITc_nfc_is_activated_p(void);
extern int ITc_nfc_manager_system_handler_enable_p(void);
extern int ITc_nfc_manager_set_unset_ndef_discovered_p(void);
extern int ITc_nfc_manager_set_get_tag_filter_p(void);
extern int ITc_nfc_manager_set_unset_se_event_cb_p(void);
extern int ITc_nfc_manager_set_unset_activation_changed_cb_p(void);
extern int ITc_nfc_manager_set_unset_se_transaction_event_cb_p(void);
extern int ITc_nfc_manager_set_unset_tag_discovered_cb_p(void);
extern int ITc_nfc_manager_set_unset_p2p_target_discovered_cb(void);
extern int ITc_nfc_manager_set_unset_hce_event_cb_p(void);

testcase tc_array[] = {
	{"ITc_nfc_se_get_card_emulation_mode_p",ITc_nfc_se_get_card_emulation_mode_p,ITs_nfc_se_startup,ITs_nfc_se_cleanup},
	{"ITc_nfc_manager_get_se_type_p",ITc_nfc_manager_get_se_type_p,ITs_nfc_se_startup,ITs_nfc_se_cleanup},
	{"ITc_nfc_se_set_default_route_p",ITc_nfc_se_set_default_route_p,ITs_nfc_se_startup,ITs_nfc_se_cleanup},
	{"ITc_nfc_se_register_unregister_aid_p",ITc_nfc_se_register_unregister_aid_p,ITs_nfc_se_startup,ITs_nfc_se_cleanup},
	{"ITc_nfc_se_is_activated_handler_for_aid_p",ITc_nfc_se_is_activated_handler_for_aid_p,ITs_nfc_se_startup,ITs_nfc_se_cleanup},
	{"ITc_nfc_se_is_activated_handler_for_category_p",ITc_nfc_se_is_activated_handler_for_category_p,ITs_nfc_se_startup,ITs_nfc_se_cleanup},
	{"ITc_nfc_se_foreach_registered_aids_p",ITc_nfc_se_foreach_registered_aids_p,ITs_nfc_se_startup,ITs_nfc_se_cleanup},
	{"ITc_nfc_ndef_record_create_destroy_p",ITc_nfc_ndef_record_create_destroy_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_record_create_text_p",ITc_nfc_ndef_record_create_text_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_record_create_uri_p",ITc_nfc_ndef_record_create_uri_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_record_create_mime_p",ITc_nfc_ndef_record_create_mime_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_message_create_destroy_p",ITc_nfc_ndef_message_create_destroy_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_message_get_record_count_p",ITc_nfc_ndef_message_get_record_count_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_message_append_record_p",ITc_nfc_ndef_message_append_record_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_message_insert_remove_record_p",ITc_nfc_ndef_message_insert_remove_record_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_message_get_record_p",ITc_nfc_ndef_message_get_record_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_message_get_rawdata_create_from_rawdata_p",ITc_nfc_ndef_message_get_rawdata_create_from_rawdata_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_record_get_payload_p",ITc_nfc_ndef_record_get_payload_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_record_set_get_id_p",ITc_nfc_ndef_record_set_get_id_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_record_get_type_p",ITc_nfc_ndef_record_get_type_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_record_get_tnf_p",ITc_nfc_ndef_record_get_tnf_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_record_get_text_p",ITc_nfc_ndef_record_get_text_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_record_get_langcode_p",ITc_nfc_ndef_record_get_langcode_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_record_get_encode_type_p",ITc_nfc_ndef_record_get_encode_type_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_record_get_uri_p",ITc_nfc_ndef_record_get_uri_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_ndef_record_get_mime_type_p",ITc_nfc_ndef_record_get_mime_type_p,ITs_nfc_ndef_startup,ITs_nfc_ndef_cleanup},
	{"ITc_nfc_snep_register_unregister_server_p",ITc_nfc_snep_register_unregister_server_p,ITs_nfc_snep_startup,ITs_nfc_snep_cleanup},
	{"ITc_nfc_is_supported_p",ITc_nfc_is_supported_p,ITs_nfc_manager_startup,ITs_nfc_manager_cleanup},
	{"ITc_nfc_manager_initialize_deinitialize_p",ITc_nfc_manager_initialize_deinitialize_p,ITs_nfc_manager_startup,ITs_nfc_manager_cleanup},
	{"ITc_nfc_is_activated_p",ITc_nfc_is_activated_p,ITs_nfc_manager_startup,ITs_nfc_manager_cleanup},
	{"ITc_nfc_manager_system_handler_enable_p",ITc_nfc_manager_system_handler_enable_p,ITs_nfc_manager_startup,ITs_nfc_manager_cleanup},
	{"ITc_nfc_manager_set_unset_ndef_discovered_p",ITc_nfc_manager_set_unset_ndef_discovered_p,ITs_nfc_manager_startup,ITs_nfc_manager_cleanup},
	{"ITc_nfc_manager_set_get_tag_filter_p",ITc_nfc_manager_set_get_tag_filter_p,ITs_nfc_manager_startup,ITs_nfc_manager_cleanup},
	{"ITc_nfc_manager_set_unset_se_event_cb_p",ITc_nfc_manager_set_unset_se_event_cb_p,ITs_nfc_manager_startup,ITs_nfc_manager_cleanup},
	{"ITc_nfc_manager_set_unset_activation_changed_cb_p",ITc_nfc_manager_set_unset_activation_changed_cb_p,ITs_nfc_manager_startup,ITs_nfc_manager_cleanup},
	{"ITc_nfc_manager_set_unset_se_transaction_event_cb_p",ITc_nfc_manager_set_unset_se_transaction_event_cb_p,ITs_nfc_manager_startup,ITs_nfc_manager_cleanup},
	{"ITc_nfc_manager_set_unset_tag_discovered_cb_p",ITc_nfc_manager_set_unset_tag_discovered_cb_p,ITs_nfc_manager_startup,ITs_nfc_manager_cleanup},
	{"ITc_nfc_manager_set_unset_p2p_target_discovered_cb",ITc_nfc_manager_set_unset_p2p_target_discovered_cb,ITs_nfc_manager_startup,ITs_nfc_manager_cleanup},
	{"ITc_nfc_manager_set_unset_hce_event_cb_p",ITc_nfc_manager_set_unset_hce_event_cb_p,ITs_nfc_manager_startup,ITs_nfc_manager_cleanup},
	{NULL, NULL}
};

#endif // __TCT_NFC-NATIVE_H__
