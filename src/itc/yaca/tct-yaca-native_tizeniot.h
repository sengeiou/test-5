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
#ifndef __TCT_YACA-NATIVE_H__
#define __TCT_YACA-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_yaca_startup(void);
extern void ITs_yaca_cleanup(void);
extern void ITs_yaca_digest_startup(void);
extern void ITs_yaca_digest_cleanup(void);
extern void ITs_yaca_encrypt_startup(void);
extern void ITs_yaca_encrypt_cleanup(void);
extern void ITs_yaca_key_startup(void);
extern void ITs_yaca_key_cleanup(void);
extern void ITs_yaca_seal_startup(void);
extern void ITs_yaca_seal_cleanup(void);
extern void ITs_yaca_sign_startup(void);
extern void ITs_yaca_sign_cleanup(void);
extern void ITs_yaca_simple_startup(void);
extern void ITs_yaca_simple_cleanup(void);
extern void ITs_yaca_rsa_startup(void);
extern void ITs_yaca_rsa_cleanup(void);

extern int ITc_yaca_initialize_cleanup_p(void);
extern int ITc_yaca_malloc_free_p(void);
extern int ITc_yaca_zalloc_p(void);
extern int ITc_yaca_realloc_p(void);
extern int ITc_yaca_memcmp_p(void);
extern int ITc_yaca_randomize_bytes_p(void);
extern int ITc_yaca_context_set_get_property_p(void);
extern int ITc_yaca_digest_initialize_p(void);
extern int ITc_yaca_digest_update_p(void);
extern int ITc_yaca_digest_finalize_p(void);
extern int ITc_yaca_encrypt_get_iv_bit_length_p(void);
extern int ITc_yaca_encrypt_initialize_p(void);
extern int ITc_yaca_decrypt_initialize_p(void);
extern int ITc_yaca_encrypt_update_finalize_p(void);
extern int ITc_yaca_decrypt_update_finalize_p(void);
extern int ITc_yaca_key_generate_p(void);
extern int ITc_yaca_key_get_type_p(void);
extern int ITc_yaca_key_get_bit_length_p(void);
extern int ITc_yaca_key_export_import_p(void);
extern int ITc_yaca_key_generate_from_parameters_p(void);
extern int ITc_yaca_key_extract_parameters_p(void);
extern int ITc_yaca_key_derive_dh_p(void);
extern int ITc_yaca_key_derive_kdf_p(void);
extern int ITc_yaca_key_extract_public_p(void);
extern int ITc_yaca_key_derive_pbkdf2_p(void);
extern int ITc_yaca_seal_initialize_update_finalize_p(void);
extern int ITc_yaca_open_initialize_update_finalize_p(void);
extern int ITc_yaca_sign_initialize_p(void);
extern int ITc_yaca_sign_initialize_hmac_p(void);
extern int ITc_yaca_sign_initialize_cmac_p(void);
extern int ITc_yaca_sign_update_p(void);
extern int ITc_yaca_verify_initialize_update_finalize_p(void);
extern int ITc_yaca_simple_calculate_digest_p(void);
extern int ITc_yaca_simple_encrypt_p(void);
extern int ITc_yaca_simple_decrypt_p(void);
extern int ITc_yaca_simple_calculate_signature_p(void);
extern int ITc_yaca_simple_verify_signature_p(void);
extern int ITc_yaca_simple_calculate_hmac_p(void);
extern int ITc_yaca_simple_calculate_cmac_p(void);
extern int ITc_yaca_rsa_public_encrypt_private_decrypt_p(void);
extern int ITc_yaca_rsa_private_encrypt_public_decrypt_p(void);

testcase tc_array[] = {
	{"ITc_yaca_initialize_cleanup_p",ITc_yaca_initialize_cleanup_p,ITs_yaca_startup,ITs_yaca_cleanup},
	{"ITc_yaca_malloc_free_p",ITc_yaca_malloc_free_p,ITs_yaca_startup,ITs_yaca_cleanup},
	{"ITc_yaca_zalloc_p",ITc_yaca_zalloc_p,ITs_yaca_startup,ITs_yaca_cleanup},
	{"ITc_yaca_realloc_p",ITc_yaca_realloc_p,ITs_yaca_startup,ITs_yaca_cleanup},
	{"ITc_yaca_memcmp_p",ITc_yaca_memcmp_p,ITs_yaca_startup,ITs_yaca_cleanup},
	{"ITc_yaca_randomize_bytes_p",ITc_yaca_randomize_bytes_p,ITs_yaca_startup,ITs_yaca_cleanup},
	{"ITc_yaca_context_set_get_property_p",ITc_yaca_context_set_get_property_p,ITs_yaca_startup,ITs_yaca_cleanup},
	{"ITc_yaca_digest_initialize_p",ITc_yaca_digest_initialize_p,ITs_yaca_digest_startup,ITs_yaca_digest_cleanup},
	{"ITc_yaca_digest_update_p",ITc_yaca_digest_update_p,ITs_yaca_digest_startup,ITs_yaca_digest_cleanup},
	{"ITc_yaca_digest_finalize_p",ITc_yaca_digest_finalize_p,ITs_yaca_digest_startup,ITs_yaca_digest_cleanup},
	{"ITc_yaca_encrypt_get_iv_bit_length_p",ITc_yaca_encrypt_get_iv_bit_length_p,ITs_yaca_encrypt_startup,ITs_yaca_encrypt_cleanup},
	{"ITc_yaca_encrypt_initialize_p",ITc_yaca_encrypt_initialize_p,ITs_yaca_encrypt_startup,ITs_yaca_encrypt_cleanup},
	{"ITc_yaca_decrypt_initialize_p",ITc_yaca_decrypt_initialize_p,ITs_yaca_encrypt_startup,ITs_yaca_encrypt_cleanup},
	{"ITc_yaca_encrypt_update_finalize_p",ITc_yaca_encrypt_update_finalize_p,ITs_yaca_encrypt_startup,ITs_yaca_encrypt_cleanup},
	{"ITc_yaca_decrypt_update_finalize_p",ITc_yaca_decrypt_update_finalize_p,ITs_yaca_encrypt_startup,ITs_yaca_encrypt_cleanup},
	{"ITc_yaca_key_generate_p",ITc_yaca_key_generate_p,ITs_yaca_key_startup,ITs_yaca_key_cleanup},
	{"ITc_yaca_key_get_type_p",ITc_yaca_key_get_type_p,ITs_yaca_key_startup,ITs_yaca_key_cleanup},
	{"ITc_yaca_key_get_bit_length_p",ITc_yaca_key_get_bit_length_p,ITs_yaca_key_startup,ITs_yaca_key_cleanup},
	{"ITc_yaca_key_export_import_p",ITc_yaca_key_export_import_p,ITs_yaca_key_startup,ITs_yaca_key_cleanup},
	{"ITc_yaca_key_generate_from_parameters_p",ITc_yaca_key_generate_from_parameters_p,ITs_yaca_key_startup,ITs_yaca_key_cleanup},
	{"ITc_yaca_key_extract_parameters_p",ITc_yaca_key_extract_parameters_p,ITs_yaca_key_startup,ITs_yaca_key_cleanup},
	{"ITc_yaca_key_derive_dh_p",ITc_yaca_key_derive_dh_p,ITs_yaca_key_startup,ITs_yaca_key_cleanup},
	{"ITc_yaca_key_derive_kdf_p",ITc_yaca_key_derive_kdf_p,ITs_yaca_key_startup,ITs_yaca_key_cleanup},
	{"ITc_yaca_key_extract_public_p",ITc_yaca_key_extract_public_p,ITs_yaca_key_startup,ITs_yaca_key_cleanup},
	{"ITc_yaca_key_derive_pbkdf2_p",ITc_yaca_key_derive_pbkdf2_p,ITs_yaca_key_startup,ITs_yaca_key_cleanup},
	{"ITc_yaca_seal_initialize_update_finalize_p",ITc_yaca_seal_initialize_update_finalize_p,ITs_yaca_seal_startup,ITs_yaca_seal_cleanup},
	{"ITc_yaca_open_initialize_update_finalize_p",ITc_yaca_open_initialize_update_finalize_p,ITs_yaca_seal_startup,ITs_yaca_seal_cleanup},
	{"ITc_yaca_sign_initialize_p",ITc_yaca_sign_initialize_p,ITs_yaca_sign_startup,ITs_yaca_sign_cleanup},
	{"ITc_yaca_sign_initialize_hmac_p",ITc_yaca_sign_initialize_hmac_p,ITs_yaca_sign_startup,ITs_yaca_sign_cleanup},
	{"ITc_yaca_sign_initialize_cmac_p",ITc_yaca_sign_initialize_cmac_p,ITs_yaca_sign_startup,ITs_yaca_sign_cleanup},
	{"ITc_yaca_sign_update_p",ITc_yaca_sign_update_p,ITs_yaca_sign_startup,ITs_yaca_sign_cleanup},
	{"ITc_yaca_verify_initialize_update_finalize_p",ITc_yaca_verify_initialize_update_finalize_p,ITs_yaca_sign_startup,ITs_yaca_sign_cleanup},
	{"ITc_yaca_simple_calculate_digest_p",ITc_yaca_simple_calculate_digest_p,ITs_yaca_simple_startup,ITs_yaca_simple_cleanup},
	{"ITc_yaca_simple_encrypt_p",ITc_yaca_simple_encrypt_p,ITs_yaca_simple_startup,ITs_yaca_simple_cleanup},
	{"ITc_yaca_simple_decrypt_p",ITc_yaca_simple_decrypt_p,ITs_yaca_simple_startup,ITs_yaca_simple_cleanup},
	{"ITc_yaca_simple_calculate_signature_p",ITc_yaca_simple_calculate_signature_p,ITs_yaca_simple_startup,ITs_yaca_simple_cleanup},
	{"ITc_yaca_simple_verify_signature_p",ITc_yaca_simple_verify_signature_p,ITs_yaca_simple_startup,ITs_yaca_simple_cleanup},
	{"ITc_yaca_simple_calculate_hmac_p",ITc_yaca_simple_calculate_hmac_p,ITs_yaca_simple_startup,ITs_yaca_simple_cleanup},
	{"ITc_yaca_simple_calculate_cmac_p",ITc_yaca_simple_calculate_cmac_p,ITs_yaca_simple_startup,ITs_yaca_simple_cleanup},
	{"ITc_yaca_rsa_public_encrypt_private_decrypt_p",ITc_yaca_rsa_public_encrypt_private_decrypt_p,ITs_yaca_rsa_startup,ITs_yaca_rsa_cleanup},
	{"ITc_yaca_rsa_private_encrypt_public_decrypt_p",ITc_yaca_rsa_private_encrypt_public_decrypt_p,ITs_yaca_rsa_startup,ITs_yaca_rsa_cleanup},
	{NULL, NULL}
};

#endif // __TCT_YACA-NATIVE_H__
