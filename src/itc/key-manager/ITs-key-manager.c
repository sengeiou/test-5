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
#include "ITs-key-manager-common.h"

/** @addtogroup itc-key-manager
*  @ingroup itc
*  @{
*/

//& set: KeyManager

void ITs_key_manager_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Key_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
}

void ITs_key_manager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Key_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-key-manager-testcases
*  @brief 		Integration testcases for module key-manager
*  @ingroup 	itc-key-manager
*  @{
*/


//& purpose: Stores a key inside key manager based on the provided policy
//& type: auto
/**
* @testcase 			ITc_ckmc_save_key_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Store a key inside key manager based on the provided policy
* @apicovered			ckmc_save_key
* @passcase				When ckmc_save_key API return 0
* @failcase				If ckmc_save_key API returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ckmc_save_key_p(void)
{
	START_TEST;

	ckmc_key_s test_key;
	test_key.raw_key = (unsigned char *)RSA_PUB_KEY_PEM;
	test_key.key_size = strlen(RSA_PUB_KEY_PEM);
	test_key.key_type = CKMC_KEY_RSA_PUBLIC;
	test_key.password = NULL;

	ckmc_policy_s test_policy;
	test_policy.password = NULL;
	test_policy.extractable = true;

	char *pszAlias = "AliasSaveKey";
	int nRet = ckmc_save_key(pszAlias, test_key, test_policy); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_save_key", KeyMngrGetError(nRet), RemoveAlias(pszAlias));

	RemoveAlias(pszAlias);

	return 0;
}

//& purpose: Gets a key from key manager
//& type: auto
/**
* @testcase 			ITc_ckmc_get_key_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets a key from key manager
* @apicovered			ckmc_get_key
* @passcase				When ckmc_get_key API return 0
* @failcase				If ckmc_get_key API returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ckmc_get_key_p(void)
{
	START_TEST;

	char* pszAlias = "get_key_p";
	char *pszPassword = NULL;
	int nRet = -1;

	//precondition
	SaveKey(pszAlias, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition failed for ITc_ckmc_get_key_p", KeyMngrGetError(nRet));
	ckmc_key_s * ppkey = NULL;
	nRet = ckmc_get_key(pszAlias, pszPassword, &ppkey); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_key", KeyMngrGetError(nRet), RemoveAlias(pszAlias));

	ckmc_key_free(ppkey);
	RemoveAlias(pszAlias);

	return 0;
}

//& purpose: Gets a all alias of keys to which the client can access.
//& type: auto
/**
* @testcase 			ITc_ckmc_get_key_alias_list_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets a all alias of keys to which the client can access.
* @apicovered			ckmc_get_key_alias_list
* @passcase				When ckmc_get_key_alias_list API return 0
* @failcase				If ckmc_get_key_alias_list API returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ckmc_get_key_alias_list_p(void)
{
	START_TEST;

	int nRet = -1;
	char* pszAlias1 = "Alias1";
	char* pszAlias2 = "Alias2";

	//precondition start
	SaveKey(pszAlias1, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition1 failed for ITc_ckmc_get_key_alias_list_p", KeyMngrGetError(nRet));

	SaveKey(pszAlias2, &nRet);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "Precondition2 failed for ITc_ckmc_get_key_alias_list_p", KeyMngrGetError(nRet), RemoveAlias(pszAlias1));
	//precondition end

	ckmc_alias_list_s *ppAlias_list = NULL;
	nRet = ckmc_get_key_alias_list(&ppAlias_list); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_key_alias_list", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));

	ckmc_alias_list_all_free(ppAlias_list);
	RemoveAlias(pszAlias1);
	RemoveAlias(pszAlias2);

	return 0;
}

//& purpose: Stores a certificate inside key manager based on the provided policy
//& type: auto
/**
* @testcase 			ITc_ckmc_save_cert_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Stores a certificate inside key manager based on the provided policy
* @apicovered			ckmc_save_cert
* @passcase				When ckmc_save_cert API return 0
* @failcase				If ckmc_save_cert API returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ckmc_save_cert_p(void)
{
	START_TEST;

	ckmc_cert_s cert;
	ckmc_policy_s cert_policy;

	char *pszAlias = "save_cert_p";
	char* policy_password = NULL;

	cert_policy.password = policy_password;
	cert_policy.extractable = true;

	cert.raw_cert = (unsigned char *)CERT_PEM;
	cert.cert_size = strlen(CERT_PEM);
	cert.data_format = CKMC_FORM_PEM;

	int nRet = ckmc_save_cert(pszAlias, cert, cert_policy); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_save_cert", KeyMngrGetError(nRet), RemoveAlias(pszAlias));

	RemoveAlias(pszAlias);
	return 0;
}

//& purpose: Removes a certificate from key manager.
//& type: auto
/**
* @testcase 			ITc_ckmc_get_cert_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Removes a certificate from key manager.
* @apicovered			ckmc_get_cert
* @passcase				When ckmc_get_cert API return 0
* @failcase				If ckmc_get_cert API returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ckmc_get_cert_p(void)
{
	START_TEST;

	int nRet = -1;
	char *policy_password = NULL;
	char* pszAlias = "get_cert_p";
	ckmc_cert_s *cert;

	//precondition
	SaveCertificate(pszAlias, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition failed to execute ckmc_save_cert", KeyMngrGetError(nRet));

	nRet = ckmc_get_cert(pszAlias, policy_password, &cert); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_cert", KeyMngrGetError(nRet), RemoveAlias(pszAlias));

	ckmc_cert_free(cert);
	RemoveAlias(pszAlias);

	return 0;
}

//& purpose: Gets a all alias of certificates to which the client can access.
//& type: auto
/**
* @testcase 			ITc_ckmc_get_cert_alias_list_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets a all alias of certificates to which the client can access.
* @apicovered			ckmc_get_cert_alias_list
* @passcase				When ckmc_get_cert_alias_list API return 0
* @failcase				If ckmc_get_cert_alias_list API returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ckmc_get_cert_alias_list_p(void)
{
	START_TEST;

	int nRet = -1;
	char* pszAlias1 = "get_cert1_p";
	char* pszAlias2 = "get_cert2_p";

	//precondition start
	SaveCertificate(pszAlias1, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition1 failed to execute ckmc_save_cert", KeyMngrGetError(nRet));

	SaveCertificate(pszAlias2, &nRet);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "Precondition2 failed to execute ckmc_save_cert", KeyMngrGetError(nRet), RemoveAlias(pszAlias1));
	//precondition end

	ckmc_alias_list_s* palias_list = NULL;
	nRet = ckmc_get_cert_alias_list(&palias_list); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_cert_alias_list", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));

	ckmc_alias_list_all_free(palias_list);
	RemoveAlias(pszAlias1);
	RemoveAlias(pszAlias2);

	return 0;
}

//& purpose: Stores a data inside key manager based on the provided policy
//& type: auto
/**
* @testcase 			ITc_ckmc_save_data_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Stores a data inside key manager based on the provided policy
* @apicovered			ckmc_save_data
* @passcase				When ckmc_save_data API return 0
* @failcase				If ckmc_save_data API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_save_data_p(void)
{
	START_TEST;

	char* pszPassword = NULL;
	char* pData = "My bin data";
	char* pszAlias = "save_data";

	ckmc_raw_buffer_s DataBuffer;
	ckmc_policy_s policy;

	DataBuffer.data = (unsigned char *) pData;
	DataBuffer.size = strlen(pData);

	policy.password = pszPassword;
	policy.extractable = true;

	int nRet = ckmc_save_data(pszAlias, DataBuffer, policy); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_save_data", KeyMngrGetError(nRet), RemoveAlias(pszAlias));

	RemoveAlias(pszAlias);

	return 0;
}

//& purpose: Gets a data from key manager
//& type: auto
/**
* @testcase 			ITc_ckmc_get_data_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets a data from key manager
* @apicovered			ckmc_get_data
* @passcase				When ckmc_get_data API return 0
* @failcase				If ckmc_get_data API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_get_data_p(void)
{
	START_TEST;

	int nRet = -1;
	char *pszAlias = "AliasSaveData";
	char *pszPassword = NULL;

	//precondition
	SaveData(pszAlias, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition failed to execute ITc_ckmc_get_data_p", KeyMngrGetError(nRet));

	ckmc_raw_buffer_s *pData = NULL;
	nRet = ckmc_get_data(pszAlias, pszPassword, &pData); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_data", KeyMngrGetError(nRet), RemoveAlias(pszAlias));

	ckmc_buffer_free(pData);

	RemoveAlias(pszAlias);

	return 0;
}

//& purpose: Gets a all alias of data to which the client can access
//& type: auto
/**
* @testcase 			ITc_ckmc_get_data_alias_list_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets a all alias of data to which the client can access
* @apicovered			ckmc_get_data_alias_list
* @passcase				When ckmc_get_data_alias_list API return 0
* @failcase				If ckmc_get_data_alias_list API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_get_data_alias_list_p(void)
{
	START_TEST;

	int nRet = -1;
	char *pszAlias1 = "AliasSaveData1";
	char *pszAlias2 = "AliasSaveData2";

	//precondition start
	SaveData(pszAlias1, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition1 failed to execute ITc_ckmc_get_data_p", KeyMngrGetError(nRet));

	SaveData(pszAlias2, &nRet);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "Precondition1 failed to execute ITc_ckmc_get_data_p", KeyMngrGetError(nRet), RemoveAlias(pszAlias1));
	//precondition end

	ckmc_alias_list_s* pAlias_list = NULL;
	nRet = ckmc_get_data_alias_list(&pAlias_list); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_data_alias_list", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));

	ckmc_alias_list_all_free(pAlias_list);
	RemoveAlias(pszAlias1);
	RemoveAlias(pszAlias2);

	return 0;
}

//& purpose: Creates RSA private/public key pair and stores them inside key manager based on each policy
//& type: auto
/**
* @testcase 			ITc_ckmc_create_key_pair_rsa_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates RSA private/public key pair and stores them inside key manager based on each policy
* @apicovered			ckmc_create_key_pair_rsa
* @passcase				When ckmc_create_key_pair_rsa API return 0
* @failcase				If ckmc_create_key_pair_rsa API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_create_key_pair_rsa_p(void)
{
	START_TEST;

	size_t size = 1024;
	char *pszPrivate_key_alias = "PRV_KEY1";
	char *pszPublic_key_alias = "PUB_KEY1";
	ckmc_policy_s policy_private_key;
	ckmc_policy_s policy_public_key;

	policy_private_key.password = NULL;
	policy_private_key.extractable = true;

	policy_public_key.password = NULL;
	policy_public_key.extractable = true;

	int nRet = ckmc_create_key_pair_rsa(size, pszPrivate_key_alias, pszPublic_key_alias, policy_private_key, policy_public_key); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_create_key_pair_rsa", KeyMngrGetError(nRet), RemoveAlias(pszPrivate_key_alias);RemoveAlias(pszPublic_key_alias));

	RemoveAlias(pszPrivate_key_alias);
	RemoveAlias(pszPublic_key_alias);

	return 0;
}

//& purpose: Creates DSA private/public key pair and stores them inside key manager based on each policy
//& type: auto
/**
* @testcase 			ITc_ckmc_create_key_pair_dsa_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates DSA private/public key pair and stores them inside key manager based on each policy
* @apicovered			ckmc_create_key_pair_dsa
* @passcase				When ckmc_create_key_pair_dsa API return 0
* @failcase				If ckmc_create_key_pair_dsa API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_create_key_pair_dsa_p(void)
{
	START_TEST;

	size_t size = 1024;
	char *pszPrivate_key_alias = "PRV_KEY2";
	char *pszPublic_key_alias = "PUB_KEY2";
	ckmc_policy_s policy_private_key;
	ckmc_policy_s policy_public_key;

	policy_private_key.password = NULL;
	policy_private_key.extractable = true;

	policy_public_key.password = NULL;
	policy_public_key.extractable = true;

	int nRet = ckmc_create_key_pair_dsa(size, pszPrivate_key_alias, pszPublic_key_alias, policy_private_key, policy_public_key); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_create_key_pair_dsa", KeyMngrGetError(nRet), RemoveAlias(pszPrivate_key_alias);RemoveAlias(pszPublic_key_alias));

	RemoveAlias(pszPrivate_key_alias);
	RemoveAlias(pszPublic_key_alias);

	return 0;
}

//& purpose: Creates ECDSA private/public key pair and stores them inside key manager based on each policy
//& type: auto
/**
* @testcase 			ITc_ckmc_create_key_pair_ecdsa_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates ECDSA private/public key pair and stores them inside key manager based on each policy
* @apicovered			ckmc_create_key_pair_ecdsa
* @passcase				When ckmc_create_key_pair_ecdsa API return 0
* @failcase				If ckmc_create_key_pair_ecdsa API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_create_key_pair_ecdsa_p(void)
{
	START_TEST;

	ckmc_ec_type_e ectype = CKMC_EC_PRIME192V1;
	char *pszPrivate_key_alias = "ecdsa-test-1";
	char *pszPublic_key_alias = "ecdsa-test-2";
	ckmc_policy_s policy_private_key;
	ckmc_policy_s policy_public_key;

	policy_private_key.password = NULL;
	policy_private_key.extractable = false;

	policy_public_key.password = NULL;
	policy_public_key.extractable = true;

	int nRet = ckmc_create_key_pair_ecdsa(ectype, pszPrivate_key_alias, pszPublic_key_alias, policy_private_key, policy_public_key); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_create_key_pair_ecdsa", KeyMngrGetError(nRet), RemoveAlias(pszPrivate_key_alias);RemoveAlias(pszPublic_key_alias));

	RemoveAlias(pszPrivate_key_alias);
	RemoveAlias(pszPublic_key_alias);

	return 0;
}

//& purpose: Creates and verify ECDSA private/public key pair and stores them inside key manager based on each policy
//& type: auto
/**
* @testcase 			ITc_ckmc_create_verify_signature_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates ECDSA private/public key pair and stores them inside key manager based on each policy
* @apicovered			ckmc_create_signature
* @passcase				When ckmc_create_signature API return 0
* @failcase				If ckmc_create_signature API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_create_verify_signature_p(void)
{
	START_TEST;

	char* pszMessage = "message test";

	ckmc_raw_buffer_s msg_buff;
	msg_buff.data = (unsigned char*) pszMessage;
	msg_buff.size = strlen(pszMessage);

	char *pszPri_alias = "create_signature_p_pri_alias";
	char *pszPub_alias = "create_signature_p_pub_alias";
	char *pszKey_passwd = NULL;
	char *pszPri_passwd = NULL;
	char *pszPub_passwd = NULL;

	ckmc_hash_algo_e hash_algo = CKMC_HASH_SHA256;
	ckmc_rsa_padding_algo_e pad_algo = CKMC_PKCS1_PADDING;
	ckmc_raw_buffer_s *signature;

	ckmc_cert_s cert;
	cert.raw_cert = (unsigned char *) CRY_CERT;
	cert.cert_size = strlen(CRY_CERT);
	cert.data_format = CKMC_FORM_PEM;

	ckmc_policy_s certpolicy;
	certpolicy.password = pszPub_passwd;
	certpolicy.extractable = true;

	ckmc_key_s prikey;
	prikey.raw_key = (unsigned char *) CRY_RSA_PRI_KEY;
	prikey.key_size = strlen(CRY_RSA_PRI_KEY);
	prikey.key_type = CKMC_KEY_NONE;
	prikey.password = pszKey_passwd;

	ckmc_policy_s pripolicy;
	pripolicy.password = pszPri_passwd;
	pripolicy.extractable = false;

	int nRet = ckmc_save_cert(pszPub_alias, cert, certpolicy);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_save_cert", KeyMngrGetError(nRet));
	nRet = ckmc_save_key(pszPri_alias, prikey, pripolicy);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_save_key", KeyMngrGetError(nRet), RemoveAlias(pszPub_alias));

	nRet = ckmc_create_signature(pszPri_alias, pszPri_passwd, msg_buff, hash_algo, pad_algo, &signature); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_create_signature", KeyMngrGetError(nRet), RemoveAlias(pszPub_alias); RemoveAlias(pszPri_alias));

	nRet = ckmc_verify_signature(pszPub_alias, pszPub_passwd, msg_buff, *signature, hash_algo, pad_algo);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_verify_signature", KeyMngrGetError(nRet), ckmc_buffer_free(signature); RemoveAlias(pszPub_alias); RemoveAlias(pszPri_alias));

	ckmc_buffer_free(signature);
	RemoveAlias(pszPub_alias);
	RemoveAlias(pszPri_alias);

	return 0;
}

//& purpose: Verifies a certificate chain and return that chain.
//& type: auto
/**
* @testcase 			ITc_ckmc_get_cert_chain_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Verifies a certificate chain and return that chain.
* @apicovered			ckmc_get_cert_chain
* @passcase				When ckmc_get_cert_chain API return 0
* @failcase				If ckmc_get_cert_chain API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_get_cert_chain_p(void)
{
	START_TEST;

	ckmc_cert_s c_cert;
	ckmc_cert_s c_cert1;
	ckmc_cert_list_s untrustedcerts;

	c_cert.raw_cert = (unsigned char *) CERT_CHAIN1;
	c_cert.cert_size = strlen(CERT_CHAIN1);
	c_cert.data_format = CKMC_FORM_PEM;

	c_cert1.raw_cert = (unsigned char *) CERT_CHAIN2;
	c_cert1.cert_size = strlen(CERT_CHAIN2);
	c_cert1.data_format = CKMC_FORM_PEM;

	untrustedcerts.cert = &c_cert1;
	untrustedcerts.next = NULL;

	ckmc_cert_list_s *cert_chain_list;

	int nRet = ckmc_get_cert_chain(&c_cert, &untrustedcerts, &cert_chain_list); //Target API
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_get_cert_chain", KeyMngrGetError(nRet));

	ckmc_cert_list_all_free(cert_chain_list);

	return 0;
}

//& purpose: Verifies a certificate chain using a alias list of untrusted certificates and return that chain.
//& type: auto
/**
* @testcase 			ITc_ckmc_get_cert_chain_with_alias_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Verifies a certificate chain using a alias list of untrusted certificates and return that chain.
* @apicovered			ckmc_get_cert_chain_with_alias
* @passcase				When ckmc_get_cert_chain_with_alias API return 0
* @failcase				If ckmc_get_cert_chain_with_alias API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_get_cert_chain_with_alias_p(void)
{
	START_TEST;

	ckmc_cert_s c_cert, c_cert1;
	ckmc_policy_s cert_policy;
	char* policy_password = NULL;

	c_cert.raw_cert = (unsigned char *) CERT_CHAIN1;
	c_cert.cert_size = strlen(CERT_CHAIN1);
	c_cert.data_format = CKMC_FORM_PEM;

	cert_policy.password = policy_password;
	cert_policy.extractable = true;

	c_cert1.raw_cert = (unsigned char *) CERT_CHAIN2;
	c_cert1.cert_size = strlen(CERT_CHAIN2);
	c_cert1.data_format = CKMC_FORM_PEM;

	int nRet = ckmc_save_cert("cert_untrusted", c_cert1, cert_policy);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_save_cert", KeyMngrGetError(nRet));

	ckmc_alias_list_s* alias_list = NULL;
	ckmc_cert_list_s *cert_list = NULL;

	nRet = ckmc_get_cert_alias_list(&alias_list);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_cert_alias_list", KeyMngrGetError(nRet), RemoveAlias("cert_untrusted"));

	nRet = ckmc_get_cert_chain_with_alias(&c_cert, alias_list, &cert_list); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_cert_chain_with_alias", KeyMngrGetError(nRet), ckmc_cert_list_all_free(cert_list); RemoveAlias("cert_untrusted"));

	ckmc_cert_list_all_free(cert_list);
	ckmc_alias_list_all_free(alias_list);
	RemoveAlias("cert_untrusted");

	return 0;
}

//& purpose: Destroys the ckmc_raw_buffer_s handle and releases all its resources.
//& type: auto
/**
* @testcase 			ITc_ckmc_buffer_free_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Destroys the ckmc_raw_buffer_s handle and releases all its resources.
* @apicovered			ckmc_buffer_free
* @passcase				When ckmc_buffer_free API return 0
* @failcase				If ckmc_buffer_free API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_buffer_free_p(void)
{
	START_TEST;

	int nRet = -1;
	char *pszAlias = "AliasSaveData1";
	char *pszPassword = NULL;

	//precondition
	SaveData(pszAlias, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition failed for ITc_ckmc_buffer_free_p", KeyMngrGetError(nRet));

	ckmc_raw_buffer_s *pData = NULL;

	//precondition
	nRet = ckmc_get_data(pszAlias, pszPassword, &pData);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_data", KeyMngrGetError(nRet), RemoveAlias(pszAlias));

	ckmc_buffer_free(pData); //Target API
	RemoveAlias(pszAlias);

	return 0;
}

//& purpose: Creates a new ckmc_cert_s handle and returns it.
//& type: auto
/**
* @testcase 			ITc_ckmc_load_cert_from_file_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates a new ckmc_cert_s handle and returns it.
* @apicovered			ckmc_load_cert_from_file
* @passcase				When ckmc_load_cert_from_file API return 0
* @failcase				If ckmc_load_cert_from_file API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_load_cert_from_file_p(void)
{
	START_TEST;

	char szPath[PATH_LEN] = {0,};
	if ( false == KeyManagerAppendToAppDataPath(PATH, szPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	ckmc_cert_s *pCert;
	int nRet = ckmc_load_cert_from_file(szPath, &pCert); //Target API
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_load_cert_from_file", KeyMngrGetError(nRet));

	ckmc_cert_free(pCert);

	return 0;
}

//& purpose: Destroys the ckmc_alias_list_s handle and releases all its resources from the provided first handle cascadingly.
//& type: auto
/**
* @testcase 			ITc_ckmc_alias_list_all_free_p
* @since_tizen 			2.3
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Destroys the ckmc_alias_list_s handle and releases all its resources from the provided first handle cascadingly.
* @apicovered			ckmc_alias_list_all_free
* @passcase				When ckmc_alias_list_all_free API return 0
* @failcase				If ckmc_alias_list_all_free API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_alias_list_all_free_p(void)
{
	START_TEST;

	int nRet = -1;
	char* pszAlias1 = "Alias1";
	char* pszAlias2 = "Alias2";

	//precondition start
	SaveKey(pszAlias1, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition1 failed for ITc_ckmc_alias_list_all_free_p", KeyMngrGetError(nRet));

	SaveKey(pszAlias2, &nRet);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "Precondition2 failed for ITc_ckmc_alias_list_all_free_p", KeyMngrGetError(nRet), RemoveAlias(pszAlias1));

	ckmc_alias_list_s *ppAlias_list = NULL;
	nRet = ckmc_get_key_alias_list(&ppAlias_list); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_key_alias_list", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));
	//precondition end

	ckmc_alias_list_all_free(ppAlias_list); //Target API

	RemoveAlias(pszAlias1);
	RemoveAlias(pszAlias2);
	return 0;
}


//& purpose: Creates a new ckmc_pkcs12_s handle from a given PKCS#12 file and returns it.
//& type: auto
/**
* @testcase 			ITc_ckmc_pkcs12_load_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates a new ckmc_pkcs12_s handle from a given PKCS#12 file and returns it.
* @apicovered			ckmc_pkcs12_load
* @passcase				When ckmc_pkcs12_load API return 0
* @failcase				If ckmc_pkcs12_load API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_pkcs12_load_p(void)
{
	START_TEST;

	char pszFilePath[PATH_LEN] = {0,};
	if ( false == KeyManagerAppendToAppDataPath(PATHPFX, pszFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	ckmc_pkcs12_s *pkcs12_bundle = NULL;

	int nRet = ckmc_pkcs12_load(pszFilePath, PASSPHRASEPFX, &pkcs12_bundle); //Target API
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_pkcs12_load", KeyMngrGetError(nRet));

	ckmc_pkcs12_free(pkcs12_bundle);

	return 0;
}


//& purpose: Allows another application to access client's application data
//& type: auto
/**
* @testcase 			ITc_ckmc_set_permission_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Allows another application to access client's application data
* @apicovered			ckmc_set_permission
* @passcase				When ckmc_set_permission API return 0
* @failcase				If ckmc_set_permission returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_set_permission_p(void)
{
	START_TEST;

	//precondition
	int nRet = -1;
	char *pszAlias = "AliasSaveData";
	SaveData(pszAlias, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition failed for ITc_ckmc_allow_deny_access_p", KeyMngrGetError(nRet));

	ckmc_permission_e arGranted[] = { CKMC_PERMISSION_READ, CKMC_PERMISSION_REMOVE, CKMC_PERMISSION_NONE };
	int nEnumSize = sizeof(arGranted) / sizeof(arGranted[0]);
	char *szAccessorPkgId = "0";
	int nEnum = 0;
	for ( nEnum = 0; nEnum < nEnumSize; ++nEnum )
	{
		nRet = ckmc_set_permission(pszAlias, szAccessorPkgId, arGranted[nEnum]); //Target API
		PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_set_permission", KeyMngrGetError(nRet), RemoveAlias(pszAlias));
	}

	RemoveAlias(pszAlias);

	return 0;
}


//& purpose: Removes a an entry (no matter of type) from the key manager.
//& type: auto
/**
* @testcase 			ITc_ckmc_remove_alias_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Removes a an entry (no matter of type) from the key manager.
* @apicovered			ckmc_remove_alias
* @passcase				When ckmc_remove_alias API return 0
* @failcase				If ckmc_remove_alias API returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ckmc_remove_alias_p(void)
{
	START_TEST;

	int nRet = -1;;
	char* pszAlias = "remove_key_p";

	//precondition
	SaveKey(pszAlias, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition failed for ITc_ckmc_remove_alias_p", KeyMngrGetError(nRet));

	nRet = ckmc_remove_alias(pszAlias); //Target API
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_remove_alias", KeyMngrGetError(nRet));

	return 0;
}

//& purpose: Verifies a certificate chain using a alias list of untrusted certificates and return that chain.
//& type: auto
/**
* @testcase 			ITc_ckmc_get_cert_chain_with_trustedcert_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Verifies a certificate chain using a alias list of untrusted certificates and return that chain.
* @apicovered			ckmc_get_cert_chain_with_trustedcert
* @passcase				When ckmc_get_cert_chain_with_trustedcert API return 0
* @failcase				If ckmc_get_cert_chain_with_trustedcert API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_get_cert_chain_with_trustedcert_p(void)
{
	START_TEST;

	ckmc_cert_s c_cert, c_cert1, c_cert2;

	ckmc_cert_list_s untrustedcerts;
	ckmc_cert_list_s trustedcerts;

	c_cert.raw_cert = (unsigned char *) CERT_CHAIN1;
	c_cert.cert_size = strlen(CERT_CHAIN1);
	c_cert.data_format = CKMC_FORM_PEM;

	c_cert1.raw_cert = (unsigned char *) CERT_CHAIN2;
	c_cert1.cert_size = strlen(CERT_CHAIN2);
	c_cert1.data_format = CKMC_FORM_PEM;

	c_cert2.raw_cert = (unsigned char *) CRY_CERT;
	c_cert2.cert_size = strlen(CRY_CERT);
	c_cert2.data_format = CKMC_FORM_PEM;

	untrustedcerts.cert = &c_cert1;
	untrustedcerts.next = NULL;

	trustedcerts.cert = &c_cert2;
	trustedcerts.next = NULL;

	ckmc_cert_list_s *cert_list = NULL;

	int nRet = ckmc_get_cert_chain_with_trustedcert(&c_cert, &untrustedcerts, &trustedcerts, true, &cert_list); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_cert_chain_with_trustedcert", KeyMngrGetError(nRet), ckmc_cert_list_all_free(cert_list));

	ckmc_cert_list_all_free(cert_list);

	return 0;
}
//& purpose: Gets and save pkcs12 from key manager.
//& type: auto
/**
* @testcase 			ITc_ckmc_get_save_pkcs12_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets and save pkcs12 from key manager.
* @apicovered			ckmc_get_pkcs12, ckmc_save_pkcs12
* @passcase				When ckmc_get_pkcs12 and ckmc_save_pkcs12 API return 0
* @failcase				If ckmc_get_pkcs12 or ckmc_save_pkcs12 API returns non zero value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_get_save_pkcs12_p(void)
{
	START_TEST;

	char* pszAlias = "get_pkcs12";
	const char *key_password = "key_password";
	const char *cert_password = "cert_password";
	ckmc_pkcs12_s *pkcs12 = NULL;
	char pszFilePath[PATH_LEN] = {0,};

	ckmc_policy_s cert_policy;
	ckmc_policy_s policy;

	cert_policy.password = NULL;
	cert_policy.extractable = true;

	policy.password = NULL;
	policy.extractable = true;

	if ( false == KeyManagerAppendToAppDataPath(PATHPFX, pszFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = ckmc_pkcs12_load(pszFilePath, PASSPHRASEPFX, &pkcs12); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_pkcs12_load", KeyMngrGetError(nRet), RemoveAlias(pszAlias));

	nRet = ckmc_save_pkcs12(pszAlias, pkcs12, cert_policy, policy);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_save_pkcs12", KeyMngrGetError(nRet), RemoveAlias(pszAlias));

	nRet = ckmc_get_pkcs12(pszAlias, key_password, cert_password, &pkcs12);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_pkcs12", KeyMngrGetError(nRet), ckmc_pkcs12_free(pkcs12);RemoveAlias(pszAlias););

	ckmc_pkcs12_free(pkcs12);
	RemoveAlias(pszAlias);

	return 0;
}

//& purpose: Creates a new ckmc_key_s handle and returns it.
//& type: auto
/**
* @testcase 			ITc_ckmc_key_new_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates a new ckmc_key_s handle
* @apicovered			ckmc_key_new
* @passcase				ckmc_key_new return #CKMC_ERROR_NONE on success
* @failcase				otherwise a negative error value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_key_new_p(void)
{
	START_TEST;

	ckmc_key_s *key;

	int nRet = ckmc_key_new((unsigned char *)RSA_PUBKEY,strlen(RSA_PUBKEY),CKMC_KEY_RSA_PUBLIC,NULL,&key);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_key_new", KeyMngrGetError(nRet));

	if(memcmp(key->raw_key,RSA_PUBKEY,strlen(RSA_PUBKEY)) != 0)
	{
		FPRINTF("[Line : %d][%s] invalid ckmc_key_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(key->key_type != CKMC_KEY_RSA_PUBLIC || key->password != NULL)
	{
		FPRINTF("[Line : %d][%s] invalid key ckmc_key_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	ckmc_key_free(key);

	return 0;
}

//& purpose: Creates a new ckmc_raw_buffer_s handle and returns it.
//& type: auto
/**
* @testcase 			ITc_ckmc_buffer_new_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates a new ckmc_raw_buffer_s handle and returns it.
* @apicovered			ckmc_buffer_new
* @passcase				ckmc_buffer_new return #CKMC_ERROR_NONE on success
* @failcase				otherwise a negative error value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_buffer_new_p(void)
{
	START_TEST;

	ckmc_raw_buffer_s *buff;
	int nRet = ckmc_buffer_new((unsigned char *)RSA_PUBKEY,strlen(RSA_PUBKEY),&buff);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_buffer_new", KeyMngrGetError(nRet));

	if(memcmp(buff->data,RSA_PUBKEY,strlen(RSA_PUBKEY)) != 0)
	{
		FPRINTF("[Line : %d][%s] invalid buffer ckmc_buffer_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	ckmc_buffer_free(buff);

	return 0;
}

//& purpose: Creates a new ckmc_cert_s handle and returns it.
//& type: auto
/**
* @testcase 			ITc_ckmc_cert_new_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates a new ckmc_cert_s handle and returns it.
* @apicovered			ckmc_cert_new
* @passcase				ckmc_cert_new return #CKMC_ERROR_NONE on success
* @failcase				otherwise a negative error value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_cert_new_p(void)
{
	START_TEST;

	ckmc_cert_s *cert;
	int nRet = ckmc_cert_new((unsigned char *)TEST_LEAF_CERT,strlen(TEST_LEAF_CERT),CKMC_FORM_PEM,&cert);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_new", KeyMngrGetError(nRet));

	if(memcmp(cert->raw_cert,TEST_LEAF_CERT,strlen(TEST_LEAF_CERT)) != 0)
	{
		FPRINTF("[Line : %d][%s] invalid cert ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(cert->data_format != CKMC_FORM_PEM)
	{
		FPRINTF("[Line : %d][%s] invalid cert format ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	ckmc_cert_free(cert);

	return 0;
}

//& purpose: Creates a new ckmc_pkcs12_s handle and returns it.
//& type: auto
/**
* @testcase 			ITc_ckmc_pkcs12_new_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates a new ckmc_pkcs12_s handle
* @apicovered			ckmc_pkcs12_new,ckmc_key_new,ckmc_cert_list_new,ckmc_cert_list_add
* @passcase				ckmc_pkcs12_new return #CKMC_ERROR_NONE on success
* @failcase				otherwise a negative error value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_pkcs12_new_p(void)
{
	START_TEST;

	ckmc_key_s *prikey;
	ckmc_cert_s *cert;

	ckmc_cert_list_s *ca_cert_list;
	ckmc_cert_s *cert1;
	ckmc_cert_s *cert2;
	ckmc_cert_list_s *cert_list_previous;
	ckmc_cert_list_s *cert_list_last;

	ckmc_pkcs12_s *pkcs12;

	// new private key
	int nRet = ckmc_key_new((unsigned char *)RSA_PRIKEY,strlen(RSA_PRIKEY),CKMC_KEY_RSA_PRIVATE,(char *)RSA_PRIKEY_PASS,&prikey);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_key_new", KeyMngrGetError(nRet));

	if(memcmp(prikey->raw_key,RSA_PRIKEY,strlen(RSA_PRIKEY)) != 0 || memcmp(prikey->password,RSA_PRIKEY_PASS,strlen(RSA_PRIKEY_PASS)) != 0)
	{
		FPRINTF("[Line : %d][%s] invalid key ckmc_key_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(prikey->key_size != strlen(RSA_PRIKEY) || prikey->key_type != CKMC_KEY_RSA_PRIVATE)
	{
		FPRINTF("[Line : %d][%s] invalid key ckmc_key_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// new cert
	nRet = ckmc_cert_new((unsigned char *)TEST_LEAF_CERT,strlen(TEST_LEAF_CERT),CKMC_FORM_PEM,&cert);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_new", KeyMngrGetError(nRet));

	if(memcmp(cert->raw_cert,TEST_LEAF_CERT,strlen(TEST_LEAF_CERT)) != 0)
	{
		FPRINTF("[Line : %d][%s] invalid cert ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(cert->cert_size != strlen(TEST_LEAF_CERT) || cert->data_format != CKMC_FORM_PEM)
	{
		FPRINTF("[Line : %d][%s] invalid cert ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// new ca_cert_list
	// new cert1 for ca_cert_list
	nRet = ckmc_cert_new((unsigned char *)TEST_IM_CA,strlen(TEST_IM_CA),CKMC_FORM_PEM,&cert1);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_new", KeyMngrGetError(nRet));

	if(memcmp(cert1->raw_cert,TEST_IM_CA,strlen(TEST_IM_CA)) != 0)
	{
		FPRINTF("[Line : %d][%s] invalid cert ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(cert1->cert_size != strlen(TEST_IM_CA) || cert1->data_format != CKMC_FORM_PEM)
	{
		FPRINTF("[Line : %d][%s] invalid cert ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// new cert_list for ca_cert_list
	nRet = ckmc_cert_list_new(cert1, &ca_cert_list);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_list_new", KeyMngrGetError(nRet));

	if(ca_cert_list->next != NULL || ca_cert_list->cert != cert1)
	{
		FPRINTF("[Line : %d][%s] invalid cert list ckmc_cert_list_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	cert_list_previous = ca_cert_list;

	// new cert2 for ca_cert_list
	nRet = ckmc_cert_new((unsigned char *)TEST_ROOT_CA,strlen(TEST_ROOT_CA),CKMC_FORM_PEM,&cert2);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_new", KeyMngrGetError(nRet));

	if(memcmp(cert2->raw_cert,TEST_ROOT_CA,strlen(TEST_ROOT_CA)) !=0 )
	{
		FPRINTF("[Line : %d][%s] invalid cert ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(cert2->cert_size != strlen(TEST_ROOT_CA) || cert2->data_format != CKMC_FORM_PEM)
	{
		FPRINTF("[Line : %d][%s] invalid cert ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// add cert to cert_list for ca_cert_list
	nRet = ckmc_cert_list_add(cert_list_previous,cert2,&cert_list_last);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_list_add", KeyMngrGetError(nRet));

	if(cert_list_previous->next != cert_list_last || cert_list_previous->cert != cert1 ||cert_list_last->next != NULL || cert_list_last->cert != cert2)
	{
		FPRINTF("[Line : %d][%s] invalid cert list ckmc_cert_list_add\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// new pkcs12
	nRet = ckmc_pkcs12_new(prikey,cert,ca_cert_list,&pkcs12);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_pkcs12_new", KeyMngrGetError(nRet));

	if(pkcs12->priv_key != prikey || pkcs12->cert != cert || pkcs12->ca_chain != ca_cert_list)
	{
		FPRINTF("[Line : %d][%s] invalid cert list ckmc_cert_list_add\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	ckmc_pkcs12_free(pkcs12);

	return 0;
}

//& purpose: Creates a new ckmc_alias_list_s handle and returns it.
//& type: auto
/**
* @testcase 			ITc_ckmc_alias_list_new_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates a new ckmc_alias_list_s handle and returns it.
* @apicovered			ckmc_alias_list_new
* @passcase				ckmc_alias_list_new return #CKMC_ERROR_NONE on success
* @failcase				otherwise a negative error value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_alias_list_new_p(void)
{
	START_TEST;

	const char *ALIAS = "alias";
	ckmc_alias_list_s *alias_list;

	int nRet = ckmc_alias_list_new((char *)ALIAS, &alias_list);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_alias_list_new", KeyMngrGetError(nRet));

	if(memcmp(alias_list->alias,ALIAS,strlen(ALIAS)) != 0 )
	{
		FPRINTF("[Line : %d][%s] invalid cert list ckmc_cert_list_add\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	ckmc_alias_list_free(alias_list);

	return 0;
}

//& purpose: Creates a new ckmc_alias_list_s handle, adds it to a previous @a ckmc_alias_list_s and
//		returns it. The alias pointer in the returned @a ckmc_alias_list_s handle points to the
//		provided characters and next is null.
//& type: auto
/**
* @testcase 			ITc_ckmc_alias_list_add_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates a new ckmc_alias_list_s handle
* @apicovered			ckmc_alias_list_add, ckmc_alias_list_new,ckmc_alias_list_free
* @passcase				ckmc_alias_list_add return #CKMC_ERROR_NONE on success
* @failcase				otherwise a negative error value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_alias_list_add_p(void)
{
	START_TEST;

	const char *ALIAS1 = "alias1";
	const char *ALIAS2 = "alias2";

	ckmc_alias_list_s *alias_list;
	ckmc_alias_list_s *alias_list_previous;
	ckmc_alias_list_s *alias_list_last;

	// new alias_list
	int nRet = ckmc_alias_list_new((char *)ALIAS1, &alias_list);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_alias_list_new", KeyMngrGetError(nRet));

	if(memcmp(alias_list->alias,ALIAS1,strlen(ALIAS1)) != 0)
	{
		FPRINTF("[Line : %d][%s] invalid new list ckmc_alias_list_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	alias_list_previous = alias_list;

	// add alias_list
	nRet = ckmc_alias_list_add(alias_list_previous,(char *)ALIAS2,&alias_list_last);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_alias_list_add", KeyMngrGetError(nRet));

	if(memcmp(alias_list_last->alias,ALIAS2,strlen(ALIAS2)) !=0 )
	PRINT_RESULT(CKMC_ERROR_NONE, -1, "ckmc_alias_list_add invalid key", KeyMngrGetError(nRet));

	if(alias_list_previous->next != alias_list_last || alias_list_last->next != NULL)
	{
		FPRINTF("[Line : %d][%s] invalid list ckmc_alias_list_add\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	ckmc_alias_list_free(alias_list);

	return 0;
}

//& purpose: Destroys the @a ckmc_alias_list_s handle and releases resources of @a ckmc_alias_list_s
//		from the provided first handle cascadingly.
//& type: auto
/**
* @testcase 			ITc_ckmc_alias_list_free_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Destroys the ckmc_alias_list_s handle
* @apicovered			ckmc_alias_list_new,ckmc_alias_list_free
* @passcase				void
* @failcase				ckmc_alias_list_new return negative error value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_alias_list_free_p(void)
{
	START_TEST;

	const char *ALIAS = "alias";
	ckmc_alias_list_s *alias_list;

	int nRet = ckmc_alias_list_new((char *)ALIAS, &alias_list);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_alias_list_new", KeyMngrGetError(nRet));

	if(memcmp(alias_list->alias,ALIAS,strlen(ALIAS)) !=0 )
	{
		FPRINTF("[Line : %d][%s] invalid list ckmc_alias_list_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// returns void
	ckmc_alias_list_free(alias_list);

	return 0;
}

//& purpose: Creates a new @a ckmc_cert_list_s handle and returns it.
//		The cert pointer in the returned @a ckmc_cert_list_s handle points to the provided
//		@a ckmc_cert_s and next is null.
//& type: auto
/**
* @testcase 			ITc_ckmc_cert_list_new_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates a new @a ckmc_cert_list_s handle and returns it
* @apicovered			ckmc_cert_list_new, ckmc_cert_new
* @passcase				ckmc_cert_list_new return #CKMC_ERROR_NONE on success
* @failcase				otherwise a negative error value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_cert_list_new_p(void)
{
	START_TEST;

	ckmc_cert_s *cert;
	ckmc_cert_list_s *cert_list;

	// new cert
	int nRet = ckmc_cert_new((unsigned char *)TEST_LEAF_CERT,strlen(TEST_LEAF_CERT),CKMC_FORM_PEM,&cert);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_new", KeyMngrGetError(nRet));

	if(memcmp(cert->raw_cert,TEST_LEAF_CERT,strlen(TEST_LEAF_CERT)) !=0 )
	{
		FPRINTF("[Line : %d][%s] invalid cert ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// new cert_list
	nRet = ckmc_cert_list_new(cert, &cert_list);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_new", KeyMngrGetError(nRet));

	ckmc_cert_list_all_free(cert_list);

	return 0;
}

//& purpose: Creates a new @a ckmc_cert_list_s handle, adds it to a previous @a ckmc_cert_list_s and
//		returns it. The cert pointer in the returned @a ckmc_alias_list_s handle points to the
//		provided @a ckmc_cert_s and next is null.
//& type: auto
/**
* @testcase 			ITc_ckmc_cert_list_add_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates a new @a ckmc_cert_list_s handle
* @apicovered			ckmc_cert_list_add, ckmc_cert_new
* @passcase				ckmc_cert_list_add return #CKMC_ERROR_NONE on success
* @failcase				otherwise a negative error value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_cert_list_add_p(void)
{
	START_TEST;

	ckmc_cert_s *cert1;
	ckmc_cert_s *cert2;
	ckmc_cert_list_s *cert_list_previous;
	ckmc_cert_list_s *cert_list_last;

	// new cert1
	int nRet = ckmc_cert_new((unsigned char *)TEST_LEAF_CERT,strlen(TEST_LEAF_CERT),CKMC_FORM_PEM,&cert1);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_new", KeyMngrGetError(nRet));

	if(memcmp(cert1->raw_cert,TEST_LEAF_CERT,strlen(TEST_LEAF_CERT)) !=0 )
	{
		FPRINTF("[Line : %d][%s] invalid cert ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(cert1->cert_size != strlen(TEST_LEAF_CERT) || cert1->data_format != CKMC_FORM_PEM)
	{
		FPRINTF("[Line : %d][%s] invalid cert size or data ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// new cert_list
	nRet = ckmc_cert_list_new(cert1, &cert_list_previous);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_list_new", KeyMngrGetError(nRet));

	if(cert_list_previous->next != NULL || cert_list_previous->cert != cert1)
	{
		FPRINTF("[Line : %d][%s] invalid previous cert list ckmc_cert_list_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// new cert2
	nRet = ckmc_cert_new((unsigned char *)TEST_IM_CA,strlen(TEST_IM_CA),CKMC_FORM_PEM,&cert2);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_new", KeyMngrGetError(nRet));

	if(memcmp(cert2->raw_cert,TEST_IM_CA,strlen(TEST_IM_CA)) != 0)
	{
		FPRINTF("[Line : %d][%s] invalid cert ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(cert2->cert_size != strlen(TEST_IM_CA) || cert2->data_format != CKMC_FORM_PEM)
	{
		FPRINTF("[Line : %d][%s] invalid cert size or data ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// add cert to cert_list
	nRet = ckmc_cert_list_add(cert_list_previous,cert2,&cert_list_last);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_list_add", KeyMngrGetError(nRet));

	ckmc_cert_list_all_free(cert_list_previous);

	return 0;
}


//& purpose: Destroys the @a ckmc_cert_list_s handle and releases resources of @a ckmc_cert_list_s
//		from the provided first handle cascadingly.
//& type: auto
/**
* @testcase 			ITc_ckmc_cert_list_free_p
* @since_tizen 			2.4
* @author				SRID(parshant.v)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Destroys the @a ckmc_cert_list_s handle
* @apicovered			ckmc_cert_list_free,ckmc_cert_new,ckmc_cert_list_new
* @passcase				void
* @failcase				ckmc_cert_new return a negative error value
* @precondition			User must be already logged in and his user key is already loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_cert_list_free_p(void)
{
	START_TEST;

	ckmc_cert_s *cert;
	ckmc_cert_list_s *cert_list;

	// new cert
	int nRet = ckmc_cert_new((unsigned char *)TEST_LEAF_CERT,strlen(TEST_LEAF_CERT),CKMC_FORM_PEM,&cert);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_new", KeyMngrGetError(nRet));

	if(memcmp(cert->raw_cert,TEST_LEAF_CERT,strlen(TEST_LEAF_CERT)) !=0 )
	{
		FPRINTF("[Line : %d][%s] invalid cert ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(cert->cert_size != strlen(TEST_LEAF_CERT) || cert->data_format != CKMC_FORM_PEM)
	{
		FPRINTF("[Line : %d][%s] invalid cert ckmc_cert_new\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// new cert_list
	nRet = ckmc_cert_list_new(cert, &cert_list);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_cert_list_new", KeyMngrGetError(nRet));

	// returns void
	ckmc_cert_list_free(cert_list);

	ckmc_cert_free(cert);
	return 0;
}

//& purpose: Encrypts and decrypts data using selected key and algorithm.
//& type: auto
/**
* @testcase				ITc_ckmc_encrypt_decrypt_data_p
* @since				3.0
* @author				SRID(jp.sahoo)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @scenario				Encrypts and decrypts data using selected key and algorithm
* @apicovered			ckmc_decrypt_data, ckmc_encrypt_data
* @passcase				When data encrypted matches with data decrypted
* @failcase				If data encrypted does not match data decrypted
* @precondition			AES key should have been created, param list for AES algorithm should be created and buffer parameter should be set
* @postcondition		NA
*/
int ITc_ckmc_encrypt_decrypt_data_p(void)
{
	START_TEST;

	size_t size = 256;
	const char *aes_key_alias = "decrypt_data_p_key";
	ckmc_policy_s aes_key_policy;

	ckmc_param_list_h params = NULL;
	ckmc_raw_buffer_s plaintext;
	ckmc_raw_buffer_s iv_buffer;

	ckmc_raw_buffer_s *encrypted = NULL;
	ckmc_raw_buffer_s *decrypted = NULL;

	unsigned char data[86] = {0, };
	unsigned char iv[16] = {0, };

	aes_key_policy.password = NULL;
	aes_key_policy.extractable = true;
	plaintext.data = data;
	plaintext.size = sizeof(data);
	iv_buffer.data = iv;
	iv_buffer.size = sizeof(iv);

	int nRet = ckmc_remove_alias(aes_key_alias);
	// If ckmc_remove_alias fails print result. Do not return as test case still hasn't failed.
	PRINT_RESULT_NORETURN(CKMC_ERROR_NONE, nRet, "ckmc_remove_alias", KeyMngrGetError(nRet));

	nRet = ckmc_create_key_aes(size, aes_key_alias, aes_key_policy);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Preconditon for ITc_ckmc_encrypt_decrypt_data_p (ckmc_create_key_aes)", KeyMngrGetError(nRet));

	nRet = ckmc_generate_new_params(CKMC_ALGO_AES_CTR, &params);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Preconditon for ITc_ckmc_encrypt_decrypt_data_p (ckmc_generate_new_params)", KeyMngrGetError(nRet));

	nRet = ckmc_param_list_set_buffer(params, CKMC_PARAM_ED_IV, &iv_buffer);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Preconditon for ITc_ckmc_encrypt_decrypt_data_p (ckmc_param_list_set_buffer)", KeyMngrGetError(nRet));

	nRet = ckmc_encrypt_data(params, aes_key_alias, NULL, plaintext, &encrypted);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_encrypt_data", KeyMngrGetError(nRet), ckmc_remove_alias(aes_key_alias);ckmc_param_list_free(params);ckmc_buffer_free(encrypted);ckmc_buffer_free(decrypted));

	nRet = ckmc_decrypt_data(params, aes_key_alias, NULL, *encrypted, &decrypted);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_decrypt_data", KeyMngrGetError(nRet), ckmc_remove_alias(aes_key_alias);ckmc_param_list_free(params);ckmc_buffer_free(encrypted);ckmc_buffer_free(decrypted));

	if ( memcmp(plaintext.data, decrypted->data, plaintext.size) != 0 )
	{
		FPRINTF("[Line : %d][%s] %s, %s failed, decrypted data does not match encrypted data\\n", __LINE__, API_NAMESPACE, "ckmc_encrypt_data", "ckmc_decrypt_data");
		ckmc_remove_alias(aes_key_alias);
		ckmc_param_list_free(params);
		ckmc_buffer_free(encrypted);
		ckmc_buffer_free(decrypted);
		return 1;
	}

	nRet = ckmc_remove_alias(aes_key_alias);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_remove_alias", KeyMngrGetError(nRet), ckmc_param_list_free(params);ckmc_buffer_free(encrypted);ckmc_buffer_free(decrypted));

	ckmc_param_list_free(params);
	ckmc_buffer_free(encrypted);
	ckmc_buffer_free(decrypted);

	return 0;
}

//& purpose: Creates AES key and stores it inside key manager based on the policy.
//& type: auto
/**
* @testcase				ITc_ckmc_create_key_aes_p
* @since				3.0
* @author				SRID(jp.sahoo)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @scenario				Creates AES key and stores it inside key manager based on the policy.
* @apicovered			ckmc_create_key_aes
* @passcase				When ckmc_create_key_aes API returns 0
* @failcase				If ckmc_create_key_aes returns non zero value
* @precondition			User must have logged in and user key must be loaded into memory in plain text form
* @postcondition		NA
*/
int ITc_ckmc_create_key_aes_p(void)
{
	START_TEST;

	size_t size = 256;
	char *aes_key_alias = "AES_P_KEY";
	ckmc_policy_s aes_key_policy;

	aes_key_policy.password = NULL;
	aes_key_policy.extractable = true;

	int nRet = ckmc_remove_alias(aes_key_alias);
	// If ckmc_remove_alias fails print result. Do not return as test case still hasn't failed.
	PRINT_RESULT_NORETURN(CKMC_ERROR_NONE, nRet, "ckmc_remove_alias", KeyMngrGetError(nRet));

	// Target API
	nRet = ckmc_create_key_aes(size, aes_key_alias, aes_key_policy);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_create_key_aes", KeyMngrGetError(nRet), ckmc_remove_alias(aes_key_alias));

	nRet = ckmc_remove_alias(aes_key_alias);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_remove_alias", KeyMngrGetError(nRet));

	return 0;
}

//& purpose: Creates new parameter list and frees it.
//& type: auto
/**
* @testcase				ITc_ckmc_param_list_new_free_p
* @since				3.0
* @author				SRID(jp.sahoo)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @scenario				Creates new parameter list and frees it
* @apicovered			ckmc_param_list_free, ckmc_param_list_new
* @passcase				When ckmc_param_list_new API returns 0
* @failcase				If ckmc_param_list_new returns non zero value
* @precondition			N/A
* @postcondition		NA
*/
int ITc_ckmc_param_list_new_free_p(void)
{
	START_TEST;

	ckmc_param_list_h params = NULL;

	int nRet = ckmc_param_list_new(&params);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_param_list_new", KeyMngrGetError(nRet));

	// Target API
	ckmc_param_list_free(params);

	return 0;
}

//& purpose: Generates algorithm parameters for a given algorithm type and set them to the list.
//& type: auto
/**
* @testcase				ITc_ckmc_generate_new_params_p
* @since				3.0
* @author				SRID(jp.sahoo)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @scenario				Generates algorithm parameters for a given algorithm type and set them to the list
* @apicovered			ckmc_generate_new_params
* @passcase				When ckmc_generate_new_params API returns 0
* @failcase				If ckmc_generate_new_params returns non zero value
* @precondition			N/A
* @postcondition		NA
*/
int ITc_ckmc_generate_new_params_p(void)
{
	START_TEST;

	ckmc_param_list_h params = NULL;
	ckmc_algo_type_e algo_type[] = {
									CKMC_ALGO_AES_CTR,
									CKMC_ALGO_AES_CBC,
									CKMC_ALGO_AES_GCM,
									CKMC_ALGO_AES_CFB,
									CKMC_ALGO_RSA_OAEP
									};

	int nEnumSize = sizeof(algo_type) / sizeof(algo_type[0]);
	int nRet = 0;
	int i = 0;
	for (; algo_type[i] < nEnumSize; i++)
	{
		// Target API
		nRet = ckmc_generate_new_params(algo_type[i], &params);
		PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_generate_new_params", KeyMngrGetError(nRet), ckmc_param_list_free(params));
		ckmc_param_list_free(params);
		params = NULL;
	}

	return 0;
}

//& purpose: Sets and gets integer parameter for parameter list.
//& type: auto
/**
* @testcase				ITc_ckmc_param_list_set_get_integer_p
* @since				3.0
* @author				SRID(jp.sahoo)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @scenario				Sets and gets integer parameter for parameter list
* @apicovered			ckmc_param_list_get_integer, ckmc_param_list_set_integer
* @passcase				When integer parameter set is equal to parameter fetched
* @failcase				If integet parameter set is not equal to parameter fetched
* @precondition			Parameter list should have been allocated
* @postcondition		NA
*/
int ITc_ckmc_param_list_set_get_integer_p(void)
{
	START_TEST;

	ckmc_param_list_h params = NULL;
	ckmc_param_name_e param_name = CKMC_PARAM_ED_CTR_LEN;

	uint64_t origvalue = 128;
	uint64_t value = 0;

	int nRet = ckmc_param_list_new(&params);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition for ITc_ckmc_param_list_set_get_integer_p (ckmc_param_list_new)", KeyMngrGetError(nRet));

	nRet = ckmc_param_list_set_integer(params, param_name, origvalue);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_param_list_set_integer", KeyMngrGetError(nRet), ckmc_param_list_free(params));

	nRet = ckmc_param_list_get_integer(params, param_name, &value);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_param_list_get_integer", KeyMngrGetError(nRet), ckmc_param_list_free(params));

	if (value != origvalue)
	{
		FPRINTF("[Line : %d][%s] %s, %s failed, value which API gets is not equal to value set\\n", __LINE__, API_NAMESPACE, "ckmc_param_list_set_integer", "ckmc_param_list_get_integer");
		ckmc_param_list_free(params);
		return 1;
	}

	ckmc_param_list_free(params);

	return 0;
}

//& purpose: Sets and gets buffer parameter for parameter list.
//& type: auto
/**
* @testcase				ITc_ckmc_param_list_set_get_buffer_p
* @since				3.0
* @author				SRID(jp.sahoo)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @scenario				Sets and gets buffer parameter for parameter list
* @apicovered			ckmc_param_list_get_buffer
* @passcase				When ckmc_param_list_get_buffer API returns 0
* @failcase				If ckmc_param_list_get_buffer returns non zero value
* @precondition			Parameter list should have been allocated and buffer parameter should have been set
* @postcondition		NA
*/
int ITc_ckmc_param_list_set_get_buffer_p(void)
{
	START_TEST;

	ckmc_param_list_h params = NULL;
	ckmc_param_name_e param_name = CKMC_PARAM_ED_IV;
	ckmc_raw_buffer_s origbuffer;
	ckmc_raw_buffer_s *buffer = NULL;

	unsigned char iv[32] = { 0, };

	origbuffer.data = iv;
	origbuffer.size = sizeof(iv);

	int nRet = ckmc_param_list_new(&params);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Preconditon for ITc_ckmc_param_list_get_buffer_p (ckmc_param_list_new)", KeyMngrGetError(nRet));

	nRet = ckmc_param_list_set_buffer(params, param_name, &origbuffer);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_param_list_set_buffer", KeyMngrGetError(nRet), ckmc_buffer_free(buffer);ckmc_param_list_free(params));

	nRet = ckmc_param_list_get_buffer(params, param_name, &buffer);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_param_list_get_buffer", KeyMngrGetError(nRet), ckmc_buffer_free(buffer);ckmc_param_list_free(params));

	if ( ( buffer->size != origbuffer.size ) || ( memcmp(buffer->data, origbuffer.data, sizeof(iv)) != 0 ) )
	{
		FPRINTF("[Line : %d][%s] %s, %s failed, data which API gets is not equal to data set\\n", __LINE__, API_NAMESPACE, "ckmc_param_list_set_buffer", "ckmc_param_list_get_buffer");
		ckmc_buffer_free(buffer);
		ckmc_param_list_free(params);
		return 1;
	}

	ckmc_buffer_free(buffer);
	ckmc_param_list_free(params);

	return 0;
}



//& purpose: Creates a new full alias which is a concatenation of @a owner_id and @a alias.
//& type: auto
/**
* @testcase				ITc_ckmc_alias_new_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(shohbit.v)
* @type					auto
* @scenario				Creates a new full alias which is a concatenation of @a owner_id and @a alias.
* @apicovered			ckmc_alias_new
* @passcase				When ckmc_alias_new API returns 0
* @failcase				If ckmc_alias_new returns non zero value
* @precondition			Parameter list should have been allocated and buffer parameter should have been set
* @postcondition		NA
*/
int ITc_ckmc_alias_new_p(void)
{
	START_TEST;

	char *pFullAlias = NULL;
    const char *pAalias = "ckmc_alias_new_p_alias";

    int nRet = ckmc_alias_new(ckmc_owner_id_system, pAalias, &pFullAlias);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "ckmc_alias_new", KeyMngrGetError(nRet));
	if(pFullAlias == NULL)
	{
		FPRINTF("[Line : %d][%s] failed,new alias not set\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
		
    FREE_MEMORY(pFullAlias);
	
	return 0;
}

//& purpose: Gets the information about all the aliases of keys that the client can access.
//& type: auto
/**
* @testcase				ITc_ckmc_get_key_alias_info_list_p
* @since				5.5
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @scenario				Gets the information about all the aliases of keys that the client can access.
* @apicovered			ckmc_get_key_alias_info_list
* @passcase				When ckmc_get_key_alias_info_list API returns 0
* @failcase				If ckmc_get_key_alias_info_list returns non zero value
* @precondition			User is already logged in and the user key is already loaded into memory in plain text form.
* @postcondition		NA
*/
int ITc_ckmc_get_key_alias_info_list_p(void)
{
	START_TEST;

	int nRet = -1;
	char* pszAlias1 = "Alias1";
	char* pszAlias2 = "Alias2";

	//precondition start
	SaveKey(pszAlias1, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition1 failed for ITc_ckmc_get_key_alias_info_list_p", KeyMngrGetError(nRet));

	SaveKey(pszAlias2, &nRet);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "Precondition2 failed for ITc_ckmc_get_key_alias_info_list_p", KeyMngrGetError(nRet), RemoveAlias(pszAlias1));
	//precondition end

	ckmc_alias_info_list_s *pszAliasList = NULL;
	nRet = ckmc_get_key_alias_info_list(&pszAliasList); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_key_alias_info_list", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));
	CHECK_HANDLE_CLEANUP(pszAliasList, "ckmc_get_key_alias_info_list", RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));

	ckmc_alias_info_list_all_free(pszAliasList);
	nRet = get_last_result();
	PRINT_RESULT_NORETURN(CKMC_ERROR_NONE, nRet, "ckmc_alias_info_list_all_free", KeyMngrGetError(nRet));
	RemoveAlias(pszAlias1);
	RemoveAlias(pszAlias2);

	return 0;
}

//& purpose: Destroys the #ckmc_alias_info_list_s handle and releases resources of #ckmc_alias_info_list_s from the provided first handle cascadingly.
//& type: auto
/**
* @testcase				ITc_ckmc_alias_info_list_all_free_p
* @since				5.5
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @scenario				Destroys the ckmc_alias_info_list_s handle and releases resources of ckmc_alias_info_list_s from the provided first 						handle cascadingly.
* @apicovered			ckmc_alias_info_list_all_free
* @passcase				When ckmc_alias_info_list_all_free API returns 0
* @failcase				If ckmc_alias_info_list_all_free returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ckmc_alias_info_list_all_free_p(void)
{
	START_TEST;

	int nRet = -1;
	char* pszAlias1 = "Alias1";
	char* pszAlias2 = "Alias2";

	//precondition start
	SaveKey(pszAlias1, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition1 failed for ITc_ckmc_alias_info_list_all_free_p", KeyMngrGetError(nRet));

	SaveKey(pszAlias2, &nRet);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "Precondition2 failed for ITc_ckmc_alias_info_list_all_free_p", KeyMngrGetError(nRet), RemoveAlias(pszAlias1));
	//precondition end

	ckmc_alias_info_list_s *pszAliasList = NULL;
	nRet = ckmc_get_key_alias_info_list(&pszAliasList);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_key_alias_info_list", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));
	CHECK_HANDLE_CLEANUP(pszAliasList, "ckmc_get_key_alias_info_list", RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));

	ckmc_alias_info_list_all_free(pszAliasList); //Target API
	nRet = get_last_result();
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_alias_info_list_all_free", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));
	RemoveAlias(pszAlias1);
	RemoveAlias(pszAlias2);

	return 0;
}

//& purpose: Gets the information about all the aliases of certificates that the client can access.
//& type: auto
/**
* @testcase				ITc_ckmc_get_cert_alias_info_list_p
* @since				5.5
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @scenario				Gets the information about all the aliases of certificates that the client can access.
* @apicovered			ckmc_get_cert_alias_info_list
* @passcase				When ckmc_get_cert_alias_info_list API returns 0
* @failcase				If ckmc_get_cert_alias_info_list returns non zero value
* @precondition			User is already logged in and the user key is already loaded into memory in plain text form.
* @postcondition		NA
*/
int ITc_ckmc_get_cert_alias_info_list_p(void)
{
	START_TEST;

	int nRet = -1;
	char* pszAlias1 = "get_cert1_p";
	char* pszAlias2 = "get_cert2_p";

	//precondition start
	SaveCertificate(pszAlias1, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition1 failed to execute ckmc_save_cert", KeyMngrGetError(nRet));

	SaveCertificate(pszAlias2, &nRet);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "Precondition2 failed to execute ckmc_save_cert", KeyMngrGetError(nRet), RemoveAlias(pszAlias1));
	//precondition end

	ckmc_alias_info_list_s* pszAliasList = NULL;
	nRet = ckmc_get_cert_alias_info_list(&pszAliasList); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_cert_alias_info_list", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));
	CHECK_HANDLE_CLEANUP(pszAliasList, "ckmc_get_cert_alias_info_list", RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));

	ckmc_alias_info_list_all_free(pszAliasList);
	nRet = get_last_result();
	PRINT_RESULT_NORETURN(CKMC_ERROR_NONE, nRet, "ckmc_alias_info_list_all_free", KeyMngrGetError(nRet));
	RemoveAlias(pszAlias1);
	RemoveAlias(pszAlias2);
}

//& purpose: Gets the information about all the aliases of data that the client can access.
//& type: auto
/**
* @testcase				ITc_ckmc_get_data_alias_info_list_p
* @since				5.5
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @scenario				Gets the information about all the aliases of data that the client can access.
* @apicovered			ckmc_get_data_alias_info_list
* @passcase				When ckmc_get_data_alias_info_list API returns 0
* @failcase				If ckmc_get_data_alias_info_list returns non zero value
* @precondition			User is already logged in and the user key is already loaded into memory in plain text form.
* @postcondition		NA
*/
int ITc_ckmc_get_data_alias_info_list_p(void)
{
	START_TEST;

	int nRet = -1;
	char *pszAlias1 = "AliasSaveData1";
	char *pszAlias2 = "AliasSaveData2";

	//precondition start
	SaveData(pszAlias1, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition1 failed to execute ITc_ckmc_get_data_p", KeyMngrGetError(nRet));

	SaveData(pszAlias2, &nRet);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "Precondition1 failed to execute ITc_ckmc_get_data_p", KeyMngrGetError(nRet), RemoveAlias(pszAlias1));
	//precondition end

	ckmc_alias_info_list_s* pszAliasList = NULL;
	nRet = ckmc_get_data_alias_info_list(&pszAliasList); //Target API
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_data_alias_info_list", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));
	CHECK_HANDLE_CLEANUP(pszAliasList, "ckmc_get_data_alias_info_list", RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));

	ckmc_alias_info_list_all_free(pszAliasList);
	nRet = get_last_result();
	PRINT_RESULT_NORETURN(CKMC_ERROR_NONE, nRet, "ckmc_alias_info_list_all_free", KeyMngrGetError(nRet));
	RemoveAlias(pszAlias1);
	RemoveAlias(pszAlias2);

	return 0;
}

//& purpose: Gets the password protection status from ckmc_alias_info_s structure.
//& type: auto
/**
* @testcase				ITc_ckmc_alias_info_is_password_protected_p
* @since				5.5
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @scenario				Gets the password protection status from ckmc_alias_info_s structure.
* @apicovered			ckmc_alias_info_is_password_protected
* @passcase				When ckmc_alias_info_is_password_protected API returns 0
* @failcase				If ckmc_alias_info_is_password_protected returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ckmc_alias_info_is_password_protected_p(void)
{
	START_TEST;

	int nRet = -1;
	char* pszAlias1 = "Alias1";
	char* pszAlias2 = "Alias2";
	bool bIsPasswordProtected = false;

	//precondition start
	SaveKey(pszAlias1, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition1 failed for ITc_ckmc_get_key_alias_info_list_p", KeyMngrGetError(nRet));

	SaveKey(pszAlias2, &nRet);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "Precondition2 failed for ITc_ckmc_get_key_alias_info_list_p", KeyMngrGetError(nRet), RemoveAlias(pszAlias1));
	//precondition end

	ckmc_alias_info_list_s *pszAliasList = NULL;
	nRet = ckmc_get_key_alias_info_list(&pszAliasList);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_key_alias_info_list", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));
	CHECK_HANDLE_CLEANUP(pszAliasList, "ckmc_get_key_alias_info_list", RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));

	nRet = ckmc_alias_info_is_password_protected(pszAliasList->info, &bIsPasswordProtected);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_alias_info_is_password_protected", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2);ckmc_alias_info_list_all_free(pszAliasList));

	ckmc_alias_info_list_all_free(pszAliasList);
	nRet = get_last_result();
	PRINT_RESULT_NORETURN(CKMC_ERROR_NONE, nRet, "ckmc_alias_info_list_all_free", KeyMngrGetError(nRet));
	RemoveAlias(pszAlias1);
	RemoveAlias(pszAlias2);
}

//& purpose: Gets the alias from #ckmc_alias_info_s structure.
//& type: auto
/**
* @testcase				ITc_ckmc_alias_info_get_alias_p
* @since				5.5
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @scenario				Gets the alias from ckmc_alias_info_s structure.
* @apicovered			ckmc_alias_info_get_alias
* @passcase				When ckmc_alias_info_get_alias API returns 0
* @failcase				If ckmc_alias_info_get_alias returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ckmc_alias_info_get_alias_p(void)
{
	START_TEST;

	int nRet = -1;
	char* pszAlias1 = "Alias1";
	char* pszAlias2 = "Alias2";
	char *pszAlias = NULL;

	//precondition start
	SaveKey(pszAlias1, &nRet);
	PRINT_RESULT(CKMC_ERROR_NONE, nRet, "Precondition1 failed for ITc_ckmc_get_key_alias_info_list_p", KeyMngrGetError(nRet));

	SaveKey(pszAlias2, &nRet);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "Precondition2 failed for ITc_ckmc_get_key_alias_info_list_p", KeyMngrGetError(nRet), RemoveAlias(pszAlias1));
	//precondition end

	ckmc_alias_info_list_s *pszAliasList = NULL;
	nRet = ckmc_get_key_alias_info_list(&pszAliasList);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_get_key_alias_info_list", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));
	CHECK_HANDLE_CLEANUP(pszAliasList, "ckmc_get_key_alias_info_list", RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));

	nRet = ckmc_alias_info_get_alias(pszAliasList->info, &pszAlias);
	PRINT_RESULT_CLEANUP(CKMC_ERROR_NONE, nRet, "ckmc_alias_info_get_alias", KeyMngrGetError(nRet), RemoveAlias(pszAlias1);RemoveAlias(pszAlias2);ckmc_alias_info_list_all_free(pszAliasList));
	CHECK_HANDLE_CLEANUP(pszAlias, "ckmc_alias_info_get_alias", ckmc_alias_info_list_all_free(pszAliasList);RemoveAlias(pszAlias1);RemoveAlias(pszAlias2));

	ckmc_alias_info_list_all_free(pszAliasList);
	nRet = get_last_result();
	PRINT_RESULT_NORETURN(CKMC_ERROR_NONE, nRet, "ckmc_alias_info_list_all_free", KeyMngrGetError(nRet));
	RemoveAlias(pszAlias1);
	RemoveAlias(pszAlias2);
}
/** @} */
/** @} */
