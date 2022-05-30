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

extern void utc_yaca_crypto_startup(void);
extern void utc_yaca_crypto_cleanup(void);
extern void utc_yaca_digest_startup(void);
extern void utc_yaca_digest_cleanup(void);
extern void utc_yaca_encrypt_startup(void);
extern void utc_yaca_encrypt_cleanup(void);
extern void utc_yaca_key_startup(void);
extern void utc_yaca_key_cleanup(void);
extern void utc_yaca_seal_startup(void);
extern void utc_yaca_seal_cleanup(void);
extern void utc_yaca_sign_startup(void);
extern void utc_yaca_sign_cleanup(void);
extern void utc_yaca_simple_startup(void);
extern void utc_yaca_simple_cleanup(void);
extern void utc_yaca_rsa_startup(void);
extern void utc_yaca_rsa_cleanup(void);

extern int utc_yaca_initialize_p(void);
extern int utc_yaca_cleanup_p(void);
extern int utc_yaca_malloc_p(void);
extern int utc_yaca_malloc_n(void);
extern int utc_yaca_zalloc_p(void);
extern int utc_yaca_zalloc_n(void);
extern int utc_yaca_realloc_p(void);
extern int utc_yaca_realloc_n(void);
extern int utc_yaca_free_p(void);
extern int utc_yaca_memcmp_p(void);
extern int utc_yaca_memcmp_n(void);
extern int utc_yaca_randomize_bytes_p(void);
extern int utc_yaca_randomize_bytes_n(void);
extern int utc_yaca_context_set_property_p(void);
extern int utc_yaca_context_set_property_n(void);
extern int utc_yaca_context_get_property_p(void);
extern int utc_yaca_context_get_property_n(void);
extern int utc_yaca_context_destroy_p(void);
extern int utc_yaca_context_get_output_length_p(void);
extern int utc_yaca_context_get_output_length_n(void);
extern int utc_yaca_digest_initialize_p(void);
extern int utc_yaca_digest_initialize_n(void);
extern int utc_yaca_digest_update_p(void);
extern int utc_yaca_digest_update_n(void);
extern int utc_yaca_digest_finalize_p(void);
extern int utc_yaca_digest_finalize_p2(void);
extern int utc_yaca_digest_finalize_p3(void);
extern int utc_yaca_digest_finalize_p4(void);
extern int utc_yaca_digest_finalize_p5(void);
extern int utc_yaca_digest_finalize_p6(void);
extern int utc_yaca_digest_finalize_n(void);
extern int utc_yaca_encrypt_get_iv_bit_length_p(void);
extern int utc_yaca_encrypt_get_iv_bit_length_n(void);
extern int utc_yaca_encrypt_initialize_p(void);
extern int utc_yaca_encrypt_initialize_n(void);
extern int utc_yaca_encrypt_update_p(void);
extern int utc_yaca_encrypt_update_n(void);
extern int utc_yaca_encrypt_finalize_p(void);
extern int utc_yaca_encrypt_finalize_n(void);
extern int utc_yaca_decrypt_initialize_p(void);
extern int utc_yaca_decrypt_initialize_n(void);
extern int utc_yaca_decrypt_update_p(void);
extern int utc_yaca_decrypt_update_n(void);
extern int utc_yaca_decrypt_finalize_p(void);
extern int utc_yaca_decrypt_finalize_p2(void);
extern int utc_yaca_decrypt_finalize_p3(void);
extern int utc_yaca_decrypt_finalize_p4(void);
extern int utc_yaca_decrypt_finalize_n(void);
extern int utc_yaca_key_get_type_p(void);
extern int utc_yaca_key_get_type_n(void);
extern int utc_yaca_key_get_bit_length_p(void);
extern int utc_yaca_key_get_bit_length_n(void);
extern int utc_yaca_key_import_p(void);
extern int utc_yaca_key_import_p2(void);
extern int utc_yaca_key_import_p3(void);
extern int utc_yaca_key_import_p4(void);
extern int utc_yaca_key_import_p5(void);
extern int utc_yaca_key_import_p6(void);
extern int utc_yaca_key_import_p7(void);
extern int utc_yaca_key_import_p8(void);
extern int utc_yaca_key_import_p9(void);
extern int utc_yaca_key_import_n(void);
extern int utc_yaca_key_export_p(void);
extern int utc_yaca_key_export_n(void);
extern int utc_yaca_key_generate_p(void);
extern int utc_yaca_key_generate_n(void);
extern int utc_yaca_key_generate_from_parameters_p(void);
extern int utc_yaca_key_generate_from_parameters_n(void);
extern int utc_yaca_key_extract_public_p(void);
extern int utc_yaca_key_extract_public_n(void);
extern int utc_yaca_key_extract_parameters_p(void);
extern int utc_yaca_key_extract_parameters_n(void);
extern int utc_yaca_key_destroy_p(void);
extern int utc_yaca_key_derive_pbkdf2_p(void);
extern int utc_yaca_key_derive_pbkdf2_n(void);
extern int utc_yaca_key_derive_dh_p(void);
extern int utc_yaca_key_derive_dh_n(void);
extern int utc_yaca_key_derive_kdf_p(void);
extern int utc_yaca_key_derive_kdf_n(void);
extern int utc_yaca_seal_initialize_p(void);
extern int utc_yaca_seal_initialize_n(void);
extern int utc_yaca_seal_update_p(void);
extern int utc_yaca_seal_update_n(void);
extern int utc_yaca_seal_finalize_p(void);
extern int utc_yaca_seal_finalize_n(void);
extern int utc_yaca_open_initialize_p(void);
extern int utc_yaca_open_initialize_n(void);
extern int utc_yaca_open_update_p(void);
extern int utc_yaca_open_update_n(void);
extern int utc_yaca_open_finalize_p(void);
extern int utc_yaca_open_finalize_n(void);
extern int utc_yaca_sign_initialize_p(void);
extern int utc_yaca_sign_initialize_n(void);
extern int utc_yaca_sign_initialize_hmac_p(void);
extern int utc_yaca_sign_initialize_hmac_n(void);
extern int utc_yaca_sign_initialize_cmac_p(void);
extern int utc_yaca_sign_initialize_cmac_n(void);
extern int utc_yaca_sign_update_p(void);
extern int utc_yaca_sign_update_n(void);
extern int utc_yaca_sign_finalize_p(void);
extern int utc_yaca_sign_finalize_n(void);
extern int utc_yaca_verify_initialize_p(void);
extern int utc_yaca_verify_initialize_n(void);
extern int utc_yaca_verify_update_p(void);
extern int utc_yaca_verify_update_n(void);
extern int utc_yaca_verify_finalize_p(void);
extern int utc_yaca_verify_finalize_n(void);
extern int utc_yaca_simple_calculate_digest_p(void);
extern int utc_yaca_simple_calculate_digest_n(void);
extern int utc_yaca_simple_encrypt_p(void);
extern int utc_yaca_simple_encrypt_n(void);
extern int utc_yaca_simple_decrypt_p(void);
extern int utc_yaca_simple_decrypt_n(void);
extern int utc_yaca_simple_calculate_signature_p(void);
extern int utc_yaca_simple_calculate_signature_n(void);
extern int utc_yaca_simple_verify_signature_p(void);
extern int utc_yaca_simple_verify_signature_n(void);
extern int utc_yaca_simple_calculate_hmac_p(void);
extern int utc_yaca_simple_calculate_hmac_n(void);
extern int utc_yaca_simple_calculate_cmac_p(void);
extern int utc_yaca_simple_calculate_cmac_n(void);
extern int utc_yaca_rsa_public_encrypt_p(void);
extern int utc_yaca_rsa_public_encrypt_n(void);
extern int utc_yaca_rsa_private_decrypt_p(void);
extern int utc_yaca_rsa_private_decrypt_n(void);
extern int utc_yaca_rsa_private_encrypt_p(void);
extern int utc_yaca_rsa_private_encrypt_n(void);
extern int utc_yaca_rsa_public_decrypt_p(void);
extern int utc_yaca_rsa_public_decrypt_n(void);

testcase tc_array[] = {
	{"utc_yaca_initialize_p",utc_yaca_initialize_p,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_cleanup_p",utc_yaca_cleanup_p,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_malloc_p",utc_yaca_malloc_p,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_malloc_n",utc_yaca_malloc_n,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_zalloc_p",utc_yaca_zalloc_p,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_zalloc_n",utc_yaca_zalloc_n,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_realloc_p",utc_yaca_realloc_p,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_realloc_n",utc_yaca_realloc_n,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_free_p",utc_yaca_free_p,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_memcmp_p",utc_yaca_memcmp_p,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_memcmp_n",utc_yaca_memcmp_n,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_randomize_bytes_p",utc_yaca_randomize_bytes_p,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_randomize_bytes_n",utc_yaca_randomize_bytes_n,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_context_set_property_p",utc_yaca_context_set_property_p,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_context_set_property_n",utc_yaca_context_set_property_n,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_context_get_property_p",utc_yaca_context_get_property_p,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_context_get_property_n",utc_yaca_context_get_property_n,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_context_destroy_p",utc_yaca_context_destroy_p,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_context_get_output_length_p",utc_yaca_context_get_output_length_p,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_context_get_output_length_n",utc_yaca_context_get_output_length_n,utc_yaca_crypto_startup,utc_yaca_crypto_cleanup},
	{"utc_yaca_digest_initialize_p",utc_yaca_digest_initialize_p,utc_yaca_digest_startup,utc_yaca_digest_cleanup},
	{"utc_yaca_digest_initialize_n",utc_yaca_digest_initialize_n,utc_yaca_digest_startup,utc_yaca_digest_cleanup},
	{"utc_yaca_digest_update_p",utc_yaca_digest_update_p,utc_yaca_digest_startup,utc_yaca_digest_cleanup},
	{"utc_yaca_digest_update_n",utc_yaca_digest_update_n,utc_yaca_digest_startup,utc_yaca_digest_cleanup},
	{"utc_yaca_digest_finalize_p",utc_yaca_digest_finalize_p,utc_yaca_digest_startup,utc_yaca_digest_cleanup},
	{"utc_yaca_digest_finalize_p2",utc_yaca_digest_finalize_p2,utc_yaca_digest_startup,utc_yaca_digest_cleanup},
	{"utc_yaca_digest_finalize_p3",utc_yaca_digest_finalize_p3,utc_yaca_digest_startup,utc_yaca_digest_cleanup},
	{"utc_yaca_digest_finalize_p4",utc_yaca_digest_finalize_p4,utc_yaca_digest_startup,utc_yaca_digest_cleanup},
	{"utc_yaca_digest_finalize_p5",utc_yaca_digest_finalize_p5,utc_yaca_digest_startup,utc_yaca_digest_cleanup},
	{"utc_yaca_digest_finalize_p6",utc_yaca_digest_finalize_p6,utc_yaca_digest_startup,utc_yaca_digest_cleanup},
	{"utc_yaca_digest_finalize_n",utc_yaca_digest_finalize_n,utc_yaca_digest_startup,utc_yaca_digest_cleanup},
	{"utc_yaca_encrypt_get_iv_bit_length_p",utc_yaca_encrypt_get_iv_bit_length_p,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_encrypt_get_iv_bit_length_n",utc_yaca_encrypt_get_iv_bit_length_n,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_encrypt_initialize_p",utc_yaca_encrypt_initialize_p,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_encrypt_initialize_n",utc_yaca_encrypt_initialize_n,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_encrypt_update_p",utc_yaca_encrypt_update_p,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_encrypt_update_n",utc_yaca_encrypt_update_n,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_encrypt_finalize_p",utc_yaca_encrypt_finalize_p,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_encrypt_finalize_n",utc_yaca_encrypt_finalize_n,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_decrypt_initialize_p",utc_yaca_decrypt_initialize_p,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_decrypt_initialize_n",utc_yaca_decrypt_initialize_n,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_decrypt_update_p",utc_yaca_decrypt_update_p,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_decrypt_update_n",utc_yaca_decrypt_update_n,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_decrypt_finalize_p",utc_yaca_decrypt_finalize_p,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_decrypt_finalize_p2",utc_yaca_decrypt_finalize_p2,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_decrypt_finalize_p3",utc_yaca_decrypt_finalize_p3,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_decrypt_finalize_p4",utc_yaca_decrypt_finalize_p4,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_decrypt_finalize_n",utc_yaca_decrypt_finalize_n,utc_yaca_encrypt_startup,utc_yaca_encrypt_cleanup},
	{"utc_yaca_key_get_type_p",utc_yaca_key_get_type_p,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_get_type_n",utc_yaca_key_get_type_n,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_get_bit_length_p",utc_yaca_key_get_bit_length_p,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_get_bit_length_n",utc_yaca_key_get_bit_length_n,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_import_p",utc_yaca_key_import_p,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_import_p2",utc_yaca_key_import_p2,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_import_p3",utc_yaca_key_import_p3,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_import_p4",utc_yaca_key_import_p4,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_import_p5",utc_yaca_key_import_p5,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_import_p6",utc_yaca_key_import_p6,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_import_p7",utc_yaca_key_import_p7,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_import_p8",utc_yaca_key_import_p8,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_import_p9",utc_yaca_key_import_p9,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_import_n",utc_yaca_key_import_n,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_export_p",utc_yaca_key_export_p,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_export_n",utc_yaca_key_export_n,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_generate_p",utc_yaca_key_generate_p,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_generate_n",utc_yaca_key_generate_n,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_generate_from_parameters_p",utc_yaca_key_generate_from_parameters_p,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_generate_from_parameters_n",utc_yaca_key_generate_from_parameters_n,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_extract_public_p",utc_yaca_key_extract_public_p,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_extract_public_n",utc_yaca_key_extract_public_n,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_extract_parameters_p",utc_yaca_key_extract_parameters_p,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_extract_parameters_n",utc_yaca_key_extract_parameters_n,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_destroy_p",utc_yaca_key_destroy_p,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_derive_pbkdf2_p",utc_yaca_key_derive_pbkdf2_p,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_derive_pbkdf2_n",utc_yaca_key_derive_pbkdf2_n,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_derive_dh_p",utc_yaca_key_derive_dh_p,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_derive_dh_n",utc_yaca_key_derive_dh_n,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_derive_kdf_p",utc_yaca_key_derive_kdf_p,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_key_derive_kdf_n",utc_yaca_key_derive_kdf_n,utc_yaca_key_startup,utc_yaca_key_cleanup},
	{"utc_yaca_seal_initialize_p",utc_yaca_seal_initialize_p,utc_yaca_seal_startup,utc_yaca_seal_cleanup},
	{"utc_yaca_seal_initialize_n",utc_yaca_seal_initialize_n,utc_yaca_seal_startup,utc_yaca_seal_cleanup},
	{"utc_yaca_seal_update_p",utc_yaca_seal_update_p,utc_yaca_seal_startup,utc_yaca_seal_cleanup},
	{"utc_yaca_seal_update_n",utc_yaca_seal_update_n,utc_yaca_seal_startup,utc_yaca_seal_cleanup},
	{"utc_yaca_seal_finalize_p",utc_yaca_seal_finalize_p,utc_yaca_seal_startup,utc_yaca_seal_cleanup},
	{"utc_yaca_seal_finalize_n",utc_yaca_seal_finalize_n,utc_yaca_seal_startup,utc_yaca_seal_cleanup},
	{"utc_yaca_open_initialize_p",utc_yaca_open_initialize_p,utc_yaca_seal_startup,utc_yaca_seal_cleanup},
	{"utc_yaca_open_initialize_n",utc_yaca_open_initialize_n,utc_yaca_seal_startup,utc_yaca_seal_cleanup},
	{"utc_yaca_open_update_p",utc_yaca_open_update_p,utc_yaca_seal_startup,utc_yaca_seal_cleanup},
	{"utc_yaca_open_update_n",utc_yaca_open_update_n,utc_yaca_seal_startup,utc_yaca_seal_cleanup},
	{"utc_yaca_open_finalize_p",utc_yaca_open_finalize_p,utc_yaca_seal_startup,utc_yaca_seal_cleanup},
	{"utc_yaca_open_finalize_n",utc_yaca_open_finalize_n,utc_yaca_seal_startup,utc_yaca_seal_cleanup},
	{"utc_yaca_sign_initialize_p",utc_yaca_sign_initialize_p,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_sign_initialize_n",utc_yaca_sign_initialize_n,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_sign_initialize_hmac_p",utc_yaca_sign_initialize_hmac_p,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_sign_initialize_hmac_n",utc_yaca_sign_initialize_hmac_n,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_sign_initialize_cmac_p",utc_yaca_sign_initialize_cmac_p,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_sign_initialize_cmac_n",utc_yaca_sign_initialize_cmac_n,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_sign_update_p",utc_yaca_sign_update_p,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_sign_update_n",utc_yaca_sign_update_n,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_sign_finalize_p",utc_yaca_sign_finalize_p,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_sign_finalize_n",utc_yaca_sign_finalize_n,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_verify_initialize_p",utc_yaca_verify_initialize_p,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_verify_initialize_n",utc_yaca_verify_initialize_n,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_verify_update_p",utc_yaca_verify_update_p,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_verify_update_n",utc_yaca_verify_update_n,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_verify_finalize_p",utc_yaca_verify_finalize_p,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_verify_finalize_n",utc_yaca_verify_finalize_n,utc_yaca_sign_startup,utc_yaca_sign_cleanup},
	{"utc_yaca_simple_calculate_digest_p",utc_yaca_simple_calculate_digest_p,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_calculate_digest_n",utc_yaca_simple_calculate_digest_n,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_encrypt_p",utc_yaca_simple_encrypt_p,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_encrypt_n",utc_yaca_simple_encrypt_n,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_decrypt_p",utc_yaca_simple_decrypt_p,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_decrypt_n",utc_yaca_simple_decrypt_n,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_calculate_signature_p",utc_yaca_simple_calculate_signature_p,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_calculate_signature_n",utc_yaca_simple_calculate_signature_n,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_verify_signature_p",utc_yaca_simple_verify_signature_p,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_verify_signature_n",utc_yaca_simple_verify_signature_n,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_calculate_hmac_p",utc_yaca_simple_calculate_hmac_p,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_calculate_hmac_n",utc_yaca_simple_calculate_hmac_n,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_calculate_cmac_p",utc_yaca_simple_calculate_cmac_p,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_simple_calculate_cmac_n",utc_yaca_simple_calculate_cmac_n,utc_yaca_simple_startup,utc_yaca_simple_cleanup},
	{"utc_yaca_rsa_public_encrypt_p",utc_yaca_rsa_public_encrypt_p,utc_yaca_rsa_startup,utc_yaca_rsa_cleanup},
	{"utc_yaca_rsa_public_encrypt_n",utc_yaca_rsa_public_encrypt_n,utc_yaca_rsa_startup,utc_yaca_rsa_cleanup},
	{"utc_yaca_rsa_private_decrypt_p",utc_yaca_rsa_private_decrypt_p,utc_yaca_rsa_startup,utc_yaca_rsa_cleanup},
	{"utc_yaca_rsa_private_decrypt_n",utc_yaca_rsa_private_decrypt_n,utc_yaca_rsa_startup,utc_yaca_rsa_cleanup},
	{"utc_yaca_rsa_private_encrypt_p",utc_yaca_rsa_private_encrypt_p,utc_yaca_rsa_startup,utc_yaca_rsa_cleanup},
	{"utc_yaca_rsa_private_encrypt_n",utc_yaca_rsa_private_encrypt_n,utc_yaca_rsa_startup,utc_yaca_rsa_cleanup},
	{"utc_yaca_rsa_public_decrypt_p",utc_yaca_rsa_public_decrypt_p,utc_yaca_rsa_startup,utc_yaca_rsa_cleanup},
	{"utc_yaca_rsa_public_decrypt_n",utc_yaca_rsa_public_decrypt_n,utc_yaca_rsa_startup,utc_yaca_rsa_cleanup},
	{NULL, NULL}
};

#endif // __TCT_YACA-NATIVE_H__
