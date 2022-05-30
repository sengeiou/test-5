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
#include "CTs-libstorage-common.h"

/** @addtogroup	ctc-libstorage
* @ingroup		ctc
* @{
*/

//& set: Libstorage

#define STORAGE_FEATURE "http://tizen.org/feature/storage.external"
static bool is_supported;

/**
* @function 		CTs_libstorage_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_libstorage_startup(void)
{
	struct stat stBuff;
	int ret;
	ret = system_info_get_platform_bool(STORAGE_FEATURE, &is_supported);
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Libstorage_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_libstorage_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_libstorage_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Libstorage_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup ctc-libstorage-testcases
* @brief 		Integration testcases for module libstorage
* @ingroup		ctc-libstorage
* @{
*/

//& purpose: A purpose of getting internal and external memory size.
//&type : auto
/**
* @testcase 		CTc_Storage_StorageInfo_p
* @since_tizen		2.3
* @author			SRID(parshant.v)
* @reviewer         SRID(gupta.sanjay)
* @type 			auto
* @scenario			Gets an internal memory (total and available) size\n
* 					Gets an external memory (total and available) size.
* @apicovered		storage_get_internal_memory_size,storage_get_external_memory_size
* @passcase			covered api should return zero success value
* @failcase			covered api returns negative error value
* @precondition		Should present SD card in target device
* @postcondition	NA
*/
int CTc_Storage_StorageInfo_p(void)
{
	START_TEST;

	struct statvfs	stInternalMemoryBuf;
	struct statvfs	stExternalMemoryBuf;
	int nRet = -1;
	double dInternalTotalMemory = 0, dInternalAvailMemory = 0;
	double dExternalTotalMemory = 0, dExternalAvailMemory = 0;

	nRet = storage_get_internal_memory_size(&stInternalMemoryBuf);
	PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_get_internal_memory_size", StorageGetError(nRet));
	if ( (stInternalMemoryBuf.f_frsize == 0 ) || (stInternalMemoryBuf.f_blocks == 0) )
	{
		FPRINTF("[Line : %d][%s] Invalid internal memory size.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	dInternalTotalMemory = ((double)stInternalMemoryBuf.f_frsize*stInternalMemoryBuf.f_blocks)/(1024*1024);
	dInternalAvailMemory = ((double)stInternalMemoryBuf.f_bsize*stInternalMemoryBuf.f_bavail)/(1024*1024);

	FPRINTF("[Line : %d][%s] Total Internal memory : %lf MB, Avail internal memory : %lf MB\\n", __LINE__, API_NAMESPACE, dInternalTotalMemory, dInternalAvailMemory);

	if ( dInternalAvailMemory <=0 )
	{
		FPRINTF("[Line : %d][%s] Internal memory storage is Full! no available internal memory\\n", __LINE__, API_NAMESPACE);
	}

	nRet = storage_get_external_memory_size(&stExternalMemoryBuf);
	if (!is_supported) {
		PRINT_RESULT(STORAGE_ERROR_NOT_SUPPORTED, nRet, "storage_get_external_memory_size", StorageGetError(nRet));
		return 0;
	}

	PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_get_external_memory_size", StorageGetError(nRet));

	if ( (stExternalMemoryBuf.f_frsize == 0) || (stExternalMemoryBuf.f_blocks == 0) )
	{
		FPRINTF("[Line : %d][%s] Invalid external memory size.\\n", __LINE__, API_NAMESPACE);
	}

	dExternalTotalMemory = ((double)stExternalMemoryBuf.f_frsize*stExternalMemoryBuf.f_blocks)/(1024*1024);
	dExternalAvailMemory = ((double)stExternalMemoryBuf.f_bsize*stExternalMemoryBuf.f_bavail)/(1024*1024);

	FPRINTF("[Line : %d][%s] Total External memory : %lf MB, Avail external memory : %lf MB.\\n", __LINE__, API_NAMESPACE, dExternalTotalMemory, dExternalAvailMemory);

	if ( dExternalAvailMemory <=0 )
	{
		FPRINTF("[Line : %d][%s] External memory storage is Full! no available external memory\\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

#ifndef TIZENIOT
//& purpose: Getting minimum internal memory size (1 GB).
//&type : auto
/**
* @testcase 		CTc_Storage_Memory_p
* @since_tizen		2.3
* @author			SRID(parshant.v)
* @reviewer         SRID(gupta.sanjay)
* @type 			auto
* @scenario			Gets an internal memory (total) size\n
* 					Checks the internal memory with minimum configuration
* @apicovered		storage_get_internal_memory_size
* @passcase			covered api should return zero success value
* @failcase			covered api returns negative error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_Storage_Memory_p(void)
{
	START_TEST;

	struct statvfs stInternalMemoryBuf;
	int nRet = -1;
	double dInternalTotalMemory = 0, dInternalAvailMemory = 0, dTotalMemory = 0;

	nRet = storage_get_internal_memory_size(&stInternalMemoryBuf);
	PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_get_internal_memory_size", StorageGetError(nRet));

	if ( (stInternalMemoryBuf.f_frsize <= 0 ) || (stInternalMemoryBuf.f_blocks <=0) )
	{
		FPRINTF("[Line : %d][%s] Invalid internal memory size.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	dInternalTotalMemory = ((double)stInternalMemoryBuf.f_frsize*stInternalMemoryBuf.f_blocks);
	dInternalAvailMemory = ((double)stInternalMemoryBuf.f_bsize*stInternalMemoryBuf.f_bavail);

	FPRINTF("[Line : %d][%s] Total Internal memory : %lf , Avail internal memory : %lf\\n", __LINE__, API_NAMESPACE, dInternalTotalMemory, dInternalAvailMemory);

	if ( dInternalAvailMemory <=0 )
	{
		FPRINTF("[Line : %d][%s] Internal memory storage is Full! no available internal memory\\n", __LINE__, API_NAMESPACE);
	}

	dTotalMemory = dInternalTotalMemory + (double)SYSTEM_MEMORY;
	if ( dTotalMemory < (double)MIN_INTERNAL_MEMORY )
	{
		FPRINTF("[Line : %d][%s] Internal memory must have 1 GB\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}
#endif
/** @} */ //end of ctc-libstorage-testcases
/** @} */ //end of ctc-libstorage
