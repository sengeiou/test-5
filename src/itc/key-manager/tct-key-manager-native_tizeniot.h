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

extern void ITs_key_manager_startup(void);
extern void ITs_key_manager_cleanup(void);

extern int ITc_ckmc_save_key_p(void);
extern int ITc_ckmc_get_key_p(void);
extern int ITc_ckmc_get_key_alias_list_p(void);
extern int ITc_ckmc_save_cert_p(void);
extern int ITc_ckmc_get_cert_p(void);
extern int ITc_ckmc_get_cert_alias_list_p(void);
extern int ITc_ckmc_save_data_p(void);
extern int ITc_ckmc_get_data_p(void);
extern int ITc_ckmc_get_data_alias_list_p(void);
extern int ITc_ckmc_create_key_pair_rsa_p(void);
extern int ITc_ckmc_create_key_pair_dsa_p(void);
extern int ITc_ckmc_create_key_pair_ecdsa_p(void);
extern int ITc_ckmc_create_verify_signature_p(void);
extern int ITc_ckmc_get_cert_chain_p(void);
extern int ITc_ckmc_get_cert_chain_with_alias_p(void);
extern int ITc_ckmc_buffer_free_p(void);
extern int ITc_ckmc_load_cert_from_file_p(void);
extern int ITc_ckmc_alias_list_all_free_p(void);
extern int ITc_ckmc_pkcs12_load_p(void);
extern int ITc_ckmc_set_permission_p(void);
extern int ITc_ckmc_remove_alias_p(void);
extern int ITc_ckmc_get_cert_chain_with_trustedcert_p(void);
extern int ITc_ckmc_get_save_pkcs12_p(void);
extern int ITc_ckmc_key_new_p(void);
extern int ITc_ckmc_buffer_new_p(void);
extern int ITc_ckmc_cert_new_p(void);
extern int ITc_ckmc_pkcs12_new_p(void);
extern int ITc_ckmc_alias_list_new_p(void);
extern int ITc_ckmc_alias_list_add_p(void);
extern int ITc_ckmc_alias_list_free_p(void);
extern int ITc_ckmc_cert_list_new_p(void);
extern int ITc_ckmc_cert_list_add_p(void);
extern int ITc_ckmc_cert_list_free_p(void);
extern int ITc_ckmc_encrypt_decrypt_data_p(void);
extern int ITc_ckmc_create_key_aes_p(void);
extern int ITc_ckmc_param_list_new_free_p(void);
extern int ITc_ckmc_generate_new_params_p(void);
extern int ITc_ckmc_param_list_set_get_integer_p(void);
extern int ITc_ckmc_param_list_set_get_buffer_p(void);
extern int ITc_ckmc_alias_new_p(void);
extern int ITc_ckmc_get_key_alias_info_list_p(void);
extern int ITc_ckmc_alias_info_list_all_free_p(void);
extern int ITc_ckmc_get_cert_alias_info_list_p(void);
extern int ITc_ckmc_get_data_alias_info_list_p(void);
extern int ITc_ckmc_alias_info_is_password_protected_p(void);
extern int ITc_ckmc_alias_info_get_alias_p(void);

testcase tc_array[] = {
	{"ITc_ckmc_save_key_p",ITc_ckmc_save_key_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_key_p",ITc_ckmc_get_key_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_key_alias_list_p",ITc_ckmc_get_key_alias_list_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_save_cert_p",ITc_ckmc_save_cert_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_cert_p",ITc_ckmc_get_cert_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_cert_alias_list_p",ITc_ckmc_get_cert_alias_list_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_save_data_p",ITc_ckmc_save_data_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_data_p",ITc_ckmc_get_data_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_data_alias_list_p",ITc_ckmc_get_data_alias_list_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_create_key_pair_rsa_p",ITc_ckmc_create_key_pair_rsa_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_create_key_pair_dsa_p",ITc_ckmc_create_key_pair_dsa_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_create_key_pair_ecdsa_p",ITc_ckmc_create_key_pair_ecdsa_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_create_verify_signature_p",ITc_ckmc_create_verify_signature_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_cert_chain_p",ITc_ckmc_get_cert_chain_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_cert_chain_with_alias_p",ITc_ckmc_get_cert_chain_with_alias_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_buffer_free_p",ITc_ckmc_buffer_free_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_load_cert_from_file_p",ITc_ckmc_load_cert_from_file_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_alias_list_all_free_p",ITc_ckmc_alias_list_all_free_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_pkcs12_load_p",ITc_ckmc_pkcs12_load_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_set_permission_p",ITc_ckmc_set_permission_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_remove_alias_p",ITc_ckmc_remove_alias_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_cert_chain_with_trustedcert_p",ITc_ckmc_get_cert_chain_with_trustedcert_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_save_pkcs12_p",ITc_ckmc_get_save_pkcs12_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_key_new_p",ITc_ckmc_key_new_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_buffer_new_p",ITc_ckmc_buffer_new_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_cert_new_p",ITc_ckmc_cert_new_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_pkcs12_new_p",ITc_ckmc_pkcs12_new_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_alias_list_new_p",ITc_ckmc_alias_list_new_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_alias_list_add_p",ITc_ckmc_alias_list_add_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_alias_list_free_p",ITc_ckmc_alias_list_free_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_cert_list_new_p",ITc_ckmc_cert_list_new_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_cert_list_add_p",ITc_ckmc_cert_list_add_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_cert_list_free_p",ITc_ckmc_cert_list_free_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_encrypt_decrypt_data_p",ITc_ckmc_encrypt_decrypt_data_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_create_key_aes_p",ITc_ckmc_create_key_aes_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_param_list_new_free_p",ITc_ckmc_param_list_new_free_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_generate_new_params_p",ITc_ckmc_generate_new_params_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_param_list_set_get_integer_p",ITc_ckmc_param_list_set_get_integer_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_param_list_set_get_buffer_p",ITc_ckmc_param_list_set_get_buffer_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_alias_new_p",ITc_ckmc_alias_new_p,ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_key_alias_info_list_p", ITc_ckmc_get_key_alias_info_list_p, ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_alias_info_list_all_free_p", ITc_ckmc_alias_info_list_all_free_p, ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_cert_alias_info_list_p", ITc_ckmc_get_cert_alias_info_list_p, ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_get_data_alias_info_list_p", ITc_ckmc_get_data_alias_info_list_p, ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_alias_info_is_password_protected_p", ITc_ckmc_alias_info_is_password_protected_p, ITs_key_manager_startup,ITs_key_manager_cleanup},
	{"ITc_ckmc_alias_info_get_alias_p", ITc_ckmc_alias_info_get_alias_p, ITs_key_manager_startup,ITs_key_manager_cleanup},
	{NULL, NULL}
};

#endif // __TCT_KEY_MANAGER_NATIVE_H__
