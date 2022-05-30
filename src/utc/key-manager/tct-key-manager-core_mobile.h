//
// Copyright (c) 2014 - 2019 Samsung Electronics Co., Ltd.
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
#ifndef __TCT_KEY_MANAGER_NATIVE_H__
#define __TCT_KEY_MANAGER_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_key_manager_crypto_startup(void);
extern void utc_key_manager_crypto_cleanup(void);
extern void utc_key_manager_store_startup(void);
extern void utc_key_manager_store_cleanup(void);
extern void utc_key_manager_type_startup(void);
extern void utc_key_manager_type_cleanup(void);

extern int utc_ckmc_create_key_pair_rsa_p(void);
extern int utc_ckmc_create_key_pair_rsa_n(void);
extern int utc_ckmc_create_key_pair_ecdsa_p(void);
extern int utc_ckmc_create_key_pair_ecdsa_n(void);
extern int utc_ckmc_create_key_pair_dsa_p(void);
extern int utc_ckmc_create_key_pair_dsa_n(void);
extern int utc_ckmc_create_signature_p(void);
extern int utc_ckmc_create_signature_n(void);
extern int utc_ckmc_verify_signature_p(void);
extern int utc_ckmc_verify_signature_n(void);
extern int utc_ckmc_get_cert_chain_p(void);
extern int utc_ckmc_get_cert_chain_n(void);
extern int utc_ckmc_get_cert_chain_with_alias_p(void);
extern int utc_ckmc_get_cert_chain_with_alias_n(void);
extern int utc_ckmc_get_cert_chain_with_trustedcert_p(void);
extern int utc_ckmc_get_cert_chain_with_trustedcert_n(void);
extern int utc_ckmc_ocsp_check_p(void);
extern int utc_ckmc_ocsp_check_n(void);
extern int utc_ckmc_create_key_aes_p(void);
extern int utc_ckmc_create_key_aes_n(void);
extern int utc_ckmc_encrypt_data_p(void);
extern int utc_ckmc_encrypt_data_n(void);
extern int utc_ckmc_decrypt_data_p(void);
extern int utc_ckmc_decrypt_data_p_2(void);
extern int utc_ckmc_decrypt_data_p_3(void);
extern int utc_ckmc_decrypt_data_p_4(void);
extern int utc_ckmc_decrypt_data_p_5(void);
extern int utc_ckmc_decrypt_data_n(void);
extern int utc_ckmc_save_key_p(void);
extern int utc_ckmc_save_key_n(void);
extern int utc_ckmc_remove_key_p(void);
extern int utc_ckmc_remove_key_n(void);
extern int utc_ckmc_get_key_p(void);
extern int utc_ckmc_get_key_n(void);
extern int utc_ckmc_get_key_n2(void);
extern int utc_ckmc_get_key_alias_list_p(void);
extern int utc_ckmc_get_key_alias_list_n(void);
extern int utc_ckmc_save_cert_p(void);
extern int utc_ckmc_save_cert_n(void);
extern int utc_ckmc_remove_cert_p(void);
extern int utc_ckmc_remove_cert_n(void);
extern int utc_ckmc_get_cert_p(void);
extern int utc_ckmc_get_cert_n(void);
extern int utc_ckmc_get_cert_n2(void);
extern int utc_ckmc_get_cert_n3(void);
extern int utc_ckmc_get_cert_alias_list_p(void);
extern int utc_ckmc_get_cert_alias_list_n(void);
extern int utc_ckmc_save_data_p(void);
extern int utc_ckmc_save_data_n(void);
extern int utc_ckmc_remove_data_p(void);
extern int utc_ckmc_remove_data_n(void);
extern int utc_ckmc_remove_data_n2(void);
extern int utc_ckmc_get_data_p(void);
extern int utc_ckmc_get_data_n(void);
extern int utc_ckmc_get_data_n2(void);
extern int utc_ckmc_get_data_alias_list_p(void);
extern int utc_ckmc_get_data_alias_list_n(void);
extern int utc_ckmc_save_pkcs12_p(void);
extern int utc_ckmc_save_pkcs12_n(void);
extern int utc_ckmc_get_pkcs12_p(void);
extern int utc_ckmc_get_pkcs12_n(void);
extern int utc_ckmc_remove_alias_p(void);
extern int utc_ckmc_remove_alias_n(void);
extern int utc_ckmc_set_permission_p(void);
extern int utc_ckmc_set_permission_n(void);
extern int utc_ckmc_allow_access_p(void);
extern int utc_ckmc_allow_access_p2(void);
extern int utc_ckmc_allow_access_n(void);
extern int utc_ckmc_allow_access_n2(void);
extern int utc_ckmc_deny_access_p(void);
extern int utc_ckmc_deny_access_p2(void);
extern int utc_ckmc_deny_access_p3(void);
extern int utc_ckmc_allow_deny_n(void);
extern int utc_ckmc_allow_deny_n2(void);
extern int utc_ckmc_alias_new_p(void);
extern int utc_ckmc_alias_new_n(void);
extern int utc_ckmc_alias_new_n2(void);
extern int utc_ckmc_alias_new_n3(void);
extern int utc_ckmc_key_new_p(void);
extern int utc_ckmc_key_new_p2(void);
extern int utc_ckmc_key_new_n(void);
extern int utc_ckmc_key_free_p(void);
extern int utc_ckmc_key_free_n(void);
extern int utc_ckmc_buffer_new_p(void);
extern int utc_ckmc_buffer_new_n(void);
extern int utc_ckmc_buffer_free_p(void);
extern int utc_ckmc_buffer_free_n(void);
extern int utc_ckmc_cert_new_p(void);
extern int utc_ckmc_cert_new_n(void);
extern int utc_ckmc_cert_free_p(void);
extern int utc_ckmc_cert_free_n(void);
extern int utc_ckmc_pkcs12_new_p(void);
extern int utc_ckmc_pkcs12_new_n(void);
extern int utc_ckmc_pkcs12_free_p(void);
extern int utc_ckmc_pkcs12_free_n(void);
extern int utc_ckmc_alias_list_new_p(void);
extern int utc_ckmc_alias_list_new_n(void);
extern int utc_ckmc_alias_list_add_p(void);
extern int utc_ckmc_alias_list_add_n(void);
extern int utc_ckmc_alias_list_free_p(void);
extern int utc_ckmc_alias_list_free_n(void);
extern int utc_ckmc_alias_list_all_free_p(void);
extern int utc_ckmc_alias_list_all_free_n(void);
extern int utc_ckmc_cert_list_new_p(void);
extern int utc_ckmc_cert_list_new_n(void);
extern int utc_ckmc_cert_list_add_p(void);
extern int utc_ckmc_cert_list_add_n(void);
extern int utc_ckmc_cert_list_free_p(void);
extern int utc_ckmc_cert_list_free_n(void);
extern int utc_ckmc_cert_list_all_free_p(void);
extern int utc_ckmc_cert_list_all_free_n(void);
extern int utc_ckmc_load_cert_from_file_p(void);
extern int utc_ckmc_load_cert_from_file_n(void);
extern int utc_ckmc_load_from_pkcs12_file_p(void);
extern int utc_ckmc_load_from_pkcs12_file_n(void);
extern int utc_ckmc_pkcs12_load_p(void);
extern int utc_ckmc_pkcs12_load_n(void);
extern int utc_ckmc_param_list_new_p(void);
extern int utc_ckmc_param_list_new_n(void);
extern int utc_ckmc_param_list_set_integer_p(void);
extern int utc_ckmc_param_list_set_integer_n(void);
extern int utc_ckmc_param_list_set_buffer_p(void);
extern int utc_ckmc_param_list_set_buffer_n(void);
extern int utc_ckmc_param_list_get_integer_p(void);
extern int utc_ckmc_param_list_get_integer_n(void);
extern int utc_ckmc_param_list_get_buffer_p(void);
extern int utc_ckmc_param_list_get_buffer_n(void);
extern int utc_ckmc_param_list_free_p(void);
extern int utc_ckmc_param_list_free_n(void);
extern int utc_ckmc_generate_new_params_p(void);
extern int utc_ckmc_generate_new_params_n(void);
extern int utc_ckmc_alias_info_get_alias_p(void);
extern int utc_ckmc_alias_info_get_alias_n(void);
extern int utc_ckmc_alias_info_is_password_protected_p(void);
extern int utc_ckmc_alias_info_is_password_protected_n(void);
extern int utc_ckmc_alias_info_list_all_free_p(void);
extern int utc_ckmc_get_key_alias_info_list_p(void);
extern int utc_ckmc_get_key_alias_info_list_n(void);
extern int utc_ckmc_get_cert_alias_info_list_p(void);
extern int utc_ckmc_get_cert_alias_info_list_n(void);
extern int utc_ckmc_get_data_alias_info_list_p1(void);
extern int utc_ckmc_get_data_alias_info_list_p2(void);
extern int utc_ckmc_get_data_alias_info_list_n(void);

testcase tc_array[] = {
	{"utc_ckmc_create_key_pair_rsa_p",utc_ckmc_create_key_pair_rsa_p,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_create_key_pair_rsa_n",utc_ckmc_create_key_pair_rsa_n,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_create_key_pair_ecdsa_p",utc_ckmc_create_key_pair_ecdsa_p,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_create_key_pair_ecdsa_n",utc_ckmc_create_key_pair_ecdsa_n,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_create_key_pair_dsa_p",utc_ckmc_create_key_pair_dsa_p,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_create_key_pair_dsa_n",utc_ckmc_create_key_pair_dsa_n,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_create_signature_p",utc_ckmc_create_signature_p,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_create_signature_n",utc_ckmc_create_signature_n,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_verify_signature_p",utc_ckmc_verify_signature_p,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_verify_signature_n",utc_ckmc_verify_signature_n,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_get_cert_chain_p",utc_ckmc_get_cert_chain_p,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_get_cert_chain_n",utc_ckmc_get_cert_chain_n,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_get_cert_chain_with_alias_p",utc_ckmc_get_cert_chain_with_alias_p,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_get_cert_chain_with_alias_n",utc_ckmc_get_cert_chain_with_alias_n,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_get_cert_chain_with_trustedcert_p",utc_ckmc_get_cert_chain_with_trustedcert_p,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_get_cert_chain_with_trustedcert_n",utc_ckmc_get_cert_chain_with_trustedcert_n,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_ocsp_check_p",utc_ckmc_ocsp_check_p,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_ocsp_check_n",utc_ckmc_ocsp_check_n,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_create_key_aes_p",utc_ckmc_create_key_aes_p,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_create_key_aes_n",utc_ckmc_create_key_aes_n,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_encrypt_data_p",utc_ckmc_encrypt_data_p,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_encrypt_data_n",utc_ckmc_encrypt_data_n,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_decrypt_data_p",utc_ckmc_decrypt_data_p,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_decrypt_data_p_2",utc_ckmc_decrypt_data_p_2,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_decrypt_data_p_3",utc_ckmc_decrypt_data_p_3,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_decrypt_data_p_4",utc_ckmc_decrypt_data_p_4,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_decrypt_data_p_5",utc_ckmc_decrypt_data_p_5,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_decrypt_data_n",utc_ckmc_decrypt_data_n,utc_key_manager_crypto_startup,utc_key_manager_crypto_cleanup},
	{"utc_ckmc_save_key_p",utc_ckmc_save_key_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_save_key_n",utc_ckmc_save_key_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_remove_key_p",utc_ckmc_remove_key_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_remove_key_n",utc_ckmc_remove_key_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_key_p",utc_ckmc_get_key_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_key_n",utc_ckmc_get_key_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_key_n2",utc_ckmc_get_key_n2,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_key_alias_list_p",utc_ckmc_get_key_alias_list_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_key_alias_list_n",utc_ckmc_get_key_alias_list_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_save_cert_p",utc_ckmc_save_cert_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_save_cert_n",utc_ckmc_save_cert_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_remove_cert_p",utc_ckmc_remove_cert_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_remove_cert_n",utc_ckmc_remove_cert_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_cert_p",utc_ckmc_get_cert_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_cert_n",utc_ckmc_get_cert_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_cert_n2",utc_ckmc_get_cert_n2,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_cert_n3",utc_ckmc_get_cert_n3,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_cert_alias_list_p",utc_ckmc_get_cert_alias_list_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_cert_alias_list_n",utc_ckmc_get_cert_alias_list_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_save_data_p",utc_ckmc_save_data_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_save_data_n",utc_ckmc_save_data_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_remove_data_p",utc_ckmc_remove_data_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_remove_data_n",utc_ckmc_remove_data_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_remove_data_n2",utc_ckmc_remove_data_n2,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_data_p",utc_ckmc_get_data_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_data_n",utc_ckmc_get_data_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_data_n2",utc_ckmc_get_data_n2,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_data_alias_list_p",utc_ckmc_get_data_alias_list_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_data_alias_list_n",utc_ckmc_get_data_alias_list_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_save_pkcs12_p",utc_ckmc_save_pkcs12_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_save_pkcs12_n",utc_ckmc_save_pkcs12_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_pkcs12_p",utc_ckmc_get_pkcs12_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_get_pkcs12_n",utc_ckmc_get_pkcs12_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_remove_alias_p",utc_ckmc_remove_alias_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_remove_alias_n",utc_ckmc_remove_alias_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_set_permission_p",utc_ckmc_set_permission_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_set_permission_n",utc_ckmc_set_permission_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_allow_access_p",utc_ckmc_allow_access_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_allow_access_p2",utc_ckmc_allow_access_p2,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_allow_access_n",utc_ckmc_allow_access_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_allow_access_n2",utc_ckmc_allow_access_n2,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_deny_access_p",utc_ckmc_deny_access_p,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_deny_access_p2",utc_ckmc_deny_access_p2,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
        {"utc_ckmc_deny_access_p3",utc_ckmc_deny_access_p3,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_allow_deny_n",utc_ckmc_allow_deny_n,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_allow_deny_n2",utc_ckmc_allow_deny_n2,utc_key_manager_store_startup,utc_key_manager_store_cleanup},
	{"utc_ckmc_alias_new_p",utc_ckmc_alias_new_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_new_n",utc_ckmc_alias_new_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_new_n2",utc_ckmc_alias_new_n2,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_new_n3",utc_ckmc_alias_new_n3,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_key_new_p",utc_ckmc_key_new_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_key_new_p2",utc_ckmc_key_new_p2,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_key_new_n",utc_ckmc_key_new_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_key_free_p",utc_ckmc_key_free_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_key_free_n",utc_ckmc_key_free_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_buffer_new_p",utc_ckmc_buffer_new_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_buffer_new_n",utc_ckmc_buffer_new_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_buffer_free_p",utc_ckmc_buffer_free_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_buffer_free_n",utc_ckmc_buffer_free_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_cert_new_p",utc_ckmc_cert_new_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_cert_new_n",utc_ckmc_cert_new_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_cert_free_p",utc_ckmc_cert_free_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_cert_free_n",utc_ckmc_cert_free_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_pkcs12_new_p",utc_ckmc_pkcs12_new_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_pkcs12_new_n",utc_ckmc_pkcs12_new_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_pkcs12_free_p",utc_ckmc_pkcs12_free_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_pkcs12_free_n",utc_ckmc_pkcs12_free_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_list_new_p",utc_ckmc_alias_list_new_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_list_new_n",utc_ckmc_alias_list_new_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_list_add_p",utc_ckmc_alias_list_add_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_list_add_n",utc_ckmc_alias_list_add_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_list_free_p",utc_ckmc_alias_list_free_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_list_free_n",utc_ckmc_alias_list_free_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_list_all_free_p",utc_ckmc_alias_list_all_free_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_list_all_free_n",utc_ckmc_alias_list_all_free_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_cert_list_new_p",utc_ckmc_cert_list_new_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_cert_list_new_n",utc_ckmc_cert_list_new_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_cert_list_add_p",utc_ckmc_cert_list_add_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_cert_list_add_n",utc_ckmc_cert_list_add_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_cert_list_free_p",utc_ckmc_cert_list_free_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_cert_list_free_n",utc_ckmc_cert_list_free_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_cert_list_all_free_p",utc_ckmc_cert_list_all_free_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_cert_list_all_free_n",utc_ckmc_cert_list_all_free_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_load_cert_from_file_p",utc_ckmc_load_cert_from_file_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_load_cert_from_file_n",utc_ckmc_load_cert_from_file_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_load_from_pkcs12_file_p",utc_ckmc_load_from_pkcs12_file_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_load_from_pkcs12_file_n",utc_ckmc_load_from_pkcs12_file_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_pkcs12_load_p",utc_ckmc_pkcs12_load_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_pkcs12_load_n",utc_ckmc_pkcs12_load_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_param_list_new_p",utc_ckmc_param_list_new_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_param_list_new_n",utc_ckmc_param_list_new_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_param_list_set_integer_p",utc_ckmc_param_list_set_integer_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_param_list_set_integer_n",utc_ckmc_param_list_set_integer_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_param_list_set_buffer_p",utc_ckmc_param_list_set_buffer_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_param_list_set_buffer_n",utc_ckmc_param_list_set_buffer_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_param_list_get_integer_p",utc_ckmc_param_list_get_integer_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_param_list_get_integer_n",utc_ckmc_param_list_get_integer_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_param_list_get_buffer_p",utc_ckmc_param_list_get_buffer_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_param_list_get_buffer_n",utc_ckmc_param_list_get_buffer_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_param_list_free_p",utc_ckmc_param_list_free_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_param_list_free_n",utc_ckmc_param_list_free_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_generate_new_params_p",utc_ckmc_generate_new_params_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_generate_new_params_n",utc_ckmc_generate_new_params_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_info_get_alias_p",utc_ckmc_alias_info_get_alias_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_info_get_alias_n",utc_ckmc_alias_info_get_alias_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_info_is_password_protected_p",utc_ckmc_alias_info_is_password_protected_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_info_is_password_protected_n",utc_ckmc_alias_info_is_password_protected_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_alias_info_list_all_free_p",utc_ckmc_alias_info_list_all_free_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_get_key_alias_info_list_p",utc_ckmc_get_key_alias_info_list_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_get_key_alias_info_list_n",utc_ckmc_get_key_alias_info_list_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_get_cert_alias_info_list_p",utc_ckmc_get_cert_alias_info_list_p,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_get_cert_alias_info_list_n",utc_ckmc_get_cert_alias_info_list_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_get_data_alias_info_list_p1",utc_ckmc_get_data_alias_info_list_p1,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_get_data_alias_info_list_p2",utc_ckmc_get_data_alias_info_list_p2,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{"utc_ckmc_get_data_alias_info_list_n",utc_ckmc_get_data_alias_info_list_n,utc_key_manager_type_startup,utc_key_manager_type_cleanup},
	{NULL, NULL}
};

#endif // __TCT_KEY_MANAGER_NATIVE_H__
