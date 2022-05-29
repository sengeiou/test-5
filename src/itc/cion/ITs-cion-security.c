//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-cion-common.h"

//& set: Cion

/** @addtogroup itc-cion
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_cion_security_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_security_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	return;
}


/**
 * @function 		ITs_cion_security_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_security_cleanup(void)
{
	return;
}

/** @addtogroup itc-cion-testcases
*  @brief 		Integration testcases for module cion
*  @ingroup 	itc-cion
*  @{
*/

//& purpose:  Creates and destroy the Cion security handle.
//& type: auto
/**
* @testcase 			ITc_cion_security_create_destory_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and destroy the Cion security handle.
* @scenario				Creates and destroy the Cion security handle.
* @apicovered			cion_security_create,cion_security_destroy
* @passcase				If cion_security_create,cion_security_destroy is successfull
* @failcase 			If cion_security_create,cion_security_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_security_create_destory_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_security_h hSecurity = NULL;

	nRetVal = cion_security_create(&hSecurity);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_security_create", CionGetError(nRetVal));
	CHECK_HANDLE(hSecurity,"cion_security_create");

	nRetVal = cion_security_destroy(hSecurity);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_security_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:  Sets and Gets the path of certificate authority certificates.
//& type: auto
/**
* @testcase 			ITc_cion_security_create_destory_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and destroy the Cion security handle.
* @scenario				Creates and destroy the Cion security handle.
* @apicovered			cion_security_set_ca_path,cion_security_get_ca_path
* @passcase				If cion_security_set_ca_path,cion_security_get_ca_path is successfull
* @failcase 			If cion_security_set_ca_path,cion_security_get_ca_path fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_security_set_get_ca_path_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_security_h hSecurity = NULL;
	char *pszSetPath = "path";
	char *pszGetPath;

	nRetVal = cion_security_create(&hSecurity);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_security_create", CionGetError(nRetVal));
	CHECK_HANDLE(hSecurity,"cion_security_create");

	nRetVal = cion_security_set_ca_path(hSecurity, pszSetPath);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_security_set_ca_path", CionGetError(nRetVal),cion_security_destroy(hSecurity));

	nRetVal = cion_security_get_ca_path(hSecurity, &pszGetPath);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_security_get_ca_path", CionGetError(nRetVal),cion_security_destroy(hSecurity));
	if(strcmp(pszSetPath ,pszGetPath) != 0)
	{
		FREE_MEMORY(pszGetPath);
		nRetVal = cion_security_destroy(hSecurity);
		PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_security_destroy", CionGetError(nRetVal));
		return 1;
	}
	FREE_MEMORY(pszGetPath);
	nRetVal = cion_security_destroy(hSecurity);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_security_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:  Sets and Gets the path of certificate.
//& type: auto
/**
* @testcase 			ITc_cion_security_set_get_cert_path_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the path of certificate.
* @scenario				Sets and Gets the path of certificate.
* @apicovered			cion_security_set_cert_path,cion_security_get_cert_path
* @passcase				If cion_security_set_cert_path,cion_security_get_cert_path is successfull
* @failcase 			If cion_security_set_cert_path,cion_security_get_cert_path fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_security_set_get_cert_path_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_security_h hSecurity = NULL;
	char *pszSetPath = "path";
	char *pszGetPath;

	nRetVal = cion_security_create(&hSecurity);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_security_create", CionGetError(nRetVal));
	CHECK_HANDLE(hSecurity,"cion_security_create");

	nRetVal = cion_security_set_cert_path(hSecurity, pszSetPath);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_security_set_cert_path", CionGetError(nRetVal),cion_security_destroy(hSecurity));

	nRetVal = cion_security_get_cert_path(hSecurity, &pszGetPath);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_security_get_cert_path", CionGetError(nRetVal),cion_security_destroy(hSecurity));
	if(strcmp(pszSetPath ,pszGetPath) != 0)
	{
		FREE_MEMORY(pszGetPath);
		nRetVal = cion_security_destroy(hSecurity);
		PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_security_destroy", CionGetError(nRetVal));
		return 1;
	}	
	FREE_MEMORY(pszGetPath);
	nRetVal = cion_security_destroy(hSecurity);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_security_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose:  Sets and Gets the path of private key.
//& type: auto
/**
* @testcase 			ITc_cion_security_set_get_cert_path_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the path of private key.
* @scenario				Sets and Gets the path of private key.
* @apicovered			cion_security_set_private_key_path,cion_security_get_private_key_path
* @passcase				If cion_security_set_private_key_path,cion_security_get_private_key_path is successfull
* @failcase 			If cion_security_set_private_key_path,cion_security_get_private_key_path fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_security_set_get_private_key_path_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_security_h hSecurity = NULL;
	char *pszSetPath = "path";
	char *pszGetPath;

	nRetVal = cion_security_create(&hSecurity);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_security_create", CionGetError(nRetVal));
	CHECK_HANDLE(hSecurity,"cion_security_create");

	nRetVal = cion_security_set_private_key_path(hSecurity, pszSetPath);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_security_set_private_key_path", CionGetError(nRetVal),cion_security_destroy(hSecurity));

	nRetVal = cion_security_get_private_key_path(hSecurity, &pszGetPath);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_security_get_private_key_path", CionGetError(nRetVal),cion_security_destroy(hSecurity));
	if(strcmp(pszSetPath ,pszGetPath) != 0)
	{
		FREE_MEMORY(pszGetPath);
		nRetVal = cion_security_destroy(hSecurity);
		PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_security_destroy", CionGetError(nRetVal));
		return 1;
	}	
	FREE_MEMORY(pszGetPath);
	nRetVal = cion_security_destroy(hSecurity);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_security_destroy", CionGetError(nRetVal));

	return 0;
}
