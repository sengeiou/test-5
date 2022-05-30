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
#include "ITs-libstorage-common.h"

/** @addtogroup itc-libstorage
*  @ingroup itc
*  @{
*/

//& set: Storage

#define STORAGE_FEATURE "http://tizen.org/feature/storage.external"

struct str_id {
	int num;
	int id;
	storage_type_e type;
	struct str_id *next;
};

static struct str_id storage_head;
static bool is_supported;

/**
* @function 		storage_device_supported_cb_p
* @description	 	callback for supported devices
* @parameter		storage_id : storage id, type : storage type, state : state, path : storage path, user_data : user data passed to callback
* @return 			bool
*/
bool storage_device_supported_cb_p(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
	struct str_id *id;

	switch (type)
	{
		case STORAGE_TYPE_INTERNAL:
		case STORAGE_TYPE_EXTERNAL:
			break;
		default:
			return true;
	}

	switch (state)
	{
		case STORAGE_STATE_UNMOUNTABLE:
		case STORAGE_STATE_REMOVED:
		case STORAGE_STATE_MOUNTED:
		case STORAGE_STATE_MOUNTED_READ_ONLY:
			break;
		default:
			return true;
	}

	FPRINTF("[Line : %d][%s] storage_device_supported_callback callback hit\\n", __LINE__, API_NAMESPACE);

	id = (struct str_id *)malloc(sizeof(struct str_id));
	if (!id)
		return true;

	id->id = storage_id;
	id->next = storage_head.next;
	id->type = type;
	storage_head.next = id;
	storage_head.num++;

	return true;
}

/**
* @function 		get_storage_id_callback
* @description	 	callback to get storage id
* @parameter		NA
* @return 			bool
*/
bool get_storage_id_callback()
{
	storage_error_e nRet = storage_foreach_device_supported(storage_device_supported_cb_p, NULL);
	if (nRet != STORAGE_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] Failed to get storage_foreach_device_supported, error returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetError(nRet));
		return false;
	}

	if (storage_head.num <= 0) {
		FPRINTF("[Line : %d][%s] After %s, callback could not find any internal storage id\\n", __LINE__, API_NAMESPACE, "storage_device_supported_callback");
		return false;
	}

	return true;
}

void release_storage_id_callback(void)
{
	struct str_id *id, *next;
	id = storage_head.next;

	while (id) {
		next = id->next;
		free(id);
		id = next;
	}
	storage_head.next = NULL;
	storage_head.num = 0;
}

/**
* @function 		Storage_state_changed_cb_p
* @description	 	storage state change callback
* @parameter		storage_id : storage id, state : storage state, user_data : user data passed to callback
* @return 			NA
*/
void Storage_state_changed_cb_p(int storage_id, storage_state_e state, void *user_data)
{
	switch (state) {
	case STORAGE_STATE_UNMOUNTABLE:
	case STORAGE_STATE_REMOVED:
	case STORAGE_STATE_MOUNTED:
	case STORAGE_STATE_MOUNTED_READ_ONLY:
		break;
	default:
		return;
	}
	FPRINTF("[Line : %d][%s] Storage_state_changed_cb_p callback hit\\n", __LINE__, API_NAMESPACE);
}
/**
* @function 		Storage_changed_cb_p
* @description	 	Called when the state of a storage type changes
* @parameter		storage_id : storage id, dev : storage device, state: storage state, fstype, fsuuid, mountpath, primary, flags, user_data : user data passed to callback
* @return 			NA
*/
void Storage_changed_cb_p(int storage_id, storage_dev_e dev, storage_state_e state, const char *fstype, const char *fsuuid, const char *mountpath, bool primary, int flags, void *user_data)
{
	FPRINTF("[Line : %d][%s] Storage_changed_cb_p callback hit\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ITs_storage_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_storage_startup(void)
{
	struct stat stBuff;
	int ret;

	ret = system_info_get_platform_bool(STORAGE_FEATURE, &is_supported);
	if (ret < 0)
		is_supported = false;

	if (stat(ERR_LOG, &stBuff) == 0)
		remove(ERR_LOG);
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Libstorage_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		ITs_storage_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_storage_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Libstorage_p\\n", __LINE__, API_NAMESPACE);
#endif
}


/** @addtogroup itc-libstorage-testcases
*  @brief 		Integration testcases for module libstorage
*  @ingroup 	itc-libstorage
*  @{
*/

//& purpose: Gets an internal memory size.
//& type: auto

/**
* @testcase 			ITc_libstorage_get_internal_memory_size_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets an internal memory size.
* @apicovered			storage_get_internal_memory_size
* @passcase				When storage_get_internal_memory_size API return 0
* @failcase				If storage_get_internal_memory_size API returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_libstorage_get_internal_memory_size_p(void)
{
	START_TEST;

	struct statvfs stInternalMemSize;
	storage_error_e nRet = storage_get_internal_memory_size(&stInternalMemSize);//target api
	PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_get_internal_memory_size", StorageGetError(nRet));

	double dbInternalMemory = (double)stInternalMemSize.f_frsize*stInternalMemSize.f_blocks;
	if(dbInternalMemory < 0) {
		FPRINTF("\\n[Line : %d][%s] API storage_get_internal_memory_size returned internal memory = (%lf)\\n", __LINE__, API_NAMESPACE, dbInternalMemory);
		return 1;
	}
	return 0;
}

//& purpose: Gets an external SD card memory size .   
//& type: auto

/**
* @testcase 			ITc_libstorage_get_external_memory_size_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets an external SD card memory size 
* @apicovered			storage_get_external_memory_size
* @passcase				When storage_get_external_memory_size API return 0
* @failcase				If storage_get_external_memory_size API returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_libstorage_get_external_memory_size_p(void)
{
	START_TEST;

	struct statvfs stExternalMemSize;
	storage_error_e nRet = storage_get_external_memory_size(&stExternalMemSize);//target api

	if (!is_supported) {
		PRINT_RESULT(STORAGE_ERROR_NOT_SUPPORTED, nRet, "storage_get_external_memory_size", StorageGetError(nRet));
		return 0;
	}

	PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_get_external_memory_size", StorageGetError(nRet));

	double dbExternalMemory = (double)stExternalMemSize.f_frsize*stExternalMemSize.f_blocks;
	if(dbExternalMemory < 0)
	{
		FPRINTF("\\n[Line : %d][%s] API storage_get_external_memory_size returned external memory = (%lf)\\n", __LINE__, API_NAMESPACE, dbExternalMemory);
		return 1;
	}
	return 0;
}

//& purpose: Retrieves all storage in device.   
//& type: auto

/**
* @testcase 			ITc_libstorage_foreach_device_supported_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				startup function
* @apicovered			storage_foreach_device_supported
* @passcase				When storage_foreach_device_supported API return 0
* @failcase				If storage_foreach_device_supported API returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_libstorage_foreach_device_supported_p(void)
{
	START_TEST;

	storage_error_e nRet = storage_foreach_device_supported(storage_device_supported_cb_p, NULL);//target api
	PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_foreach_device_supported", StorageGetError(nRet));

	if (storage_head.num <= 0) {
		FPRINTF("\\n[Line : %d][%s] For storage_foreach_device_supported, callback has not been invoked.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	release_storage_id_callback();
	return 0;
}

//& purpose: Gets the absolute path to the each directory of the given storage.
//& type: auto

/**
* @testcase 			ITc_libstorage_get_directory_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the absolute path to the root directory of the given storage.
* @apicovered			storage_get_directory
* @passcase				When storage_get_directory API return 0
* @failcase				If storage_get_directory API returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_libstorage_get_directory_p(void)
{
	START_TEST;

	if (get_storage_id_callback() == false)
		return 1;

	storage_directory_e arDirectoryType[] = {
		STORAGE_DIRECTORY_IMAGES,
		STORAGE_DIRECTORY_SOUNDS,
		STORAGE_DIRECTORY_VIDEOS,
		STORAGE_DIRECTORY_CAMERA,
		STORAGE_DIRECTORY_DOWNLOADS,
		STORAGE_DIRECTORY_MUSIC,
		STORAGE_DIRECTORY_DOCUMENTS,
		STORAGE_DIRECTORY_OTHERS,
		STORAGE_DIRECTORY_SYSTEM_RINGTONES		//Only Available For Internal Storage
	};
	int nEnumSize2 = sizeof(arDirectoryType) / sizeof(arDirectoryType[0]);
	int nEnumCount2 = 0;
	struct str_id *id;

	char *pszPath = NULL;
	storage_error_e nRet;

	id = storage_head.next;
	while (id) {
		for (nEnumCount2 = 0; nEnumCount2 < nEnumSize2; nEnumCount2++) {
			if (id->type == STORAGE_TYPE_EXTERNAL && nEnumCount2 == nEnumSize2 - 1)
				break;
			nRet = storage_get_directory(id->id, arDirectoryType[nEnumCount2], &pszPath);//target api
			if (nRet != STORAGE_ERROR_NONE)	{
				FPRINTF("[Line : %d][%s] storage_get_directory failed to get %s for %s, error returned = %s\\n",
					__LINE__, API_NAMESPACE, StorageGetDirectory(arDirectoryType[nEnumCount2]), StorageGetType(id->type), StorageGetError(nRet));
				return 1;
			}
			if (pszPath == NULL) {
				FPRINTF("[Line : %d][%s] storage_get_directory failed to get %s for %s, value returned = %s\\n",
					__LINE__, API_NAMESPACE, StorageGetDirectory(arDirectoryType[nEnumCount2]), StorageGetType(id->type), pszPath);
				return 1;
			} else {
				FPRINTF("[Line : %d][%s] storage_get_directory passed to get %s for %s, value returned = %s\\n",
					__LINE__, API_NAMESPACE, StorageGetDirectory(arDirectoryType[nEnumCount2]), StorageGetType(id->type), pszPath);
				FREE_MEMORY(pszPath);
			}
		}
		id = id->next;
	}

	release_storage_id_callback();
	return 0;
}

//& purpose: Gets the absolute path to the root directory of the given storage.
//& type: auto

/**
* @testcase 			ITc_libstorage_get_root_directory_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the absolute path to the root directory of the given storage.
* @apicovered			storage_get_root_directory
* @passcase				When storage_get_root_directory API return 0
* @failcase				If storage_get_root_directory API returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_libstorage_get_root_directory_p(void)
{
	START_TEST;

	if ( get_storage_id_callback() == false )
		return 1;

	char *pszPath = NULL;
	struct str_id *id;

	id = storage_head.next;
	while (id) {
		storage_error_e nRet = storage_get_root_directory(id->id, &pszPath);//target api
		if (nRet != STORAGE_ERROR_NONE && nRet!= STORAGE_ERROR_NOT_SUPPORTED) {
			FPRINTF("[Line : %d][%s] storage_get_root_directory failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetError(nRet));
			return 1;
		} else if (pszPath == NULL) {
			FPRINTF("[Line : %d][%s] storage_get_root_directory failed for %s, value returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), pszPath);
			return 1;
		} else {
			FPRINTF("[Line : %d][%s] storage_get_root_directory passed for %s, value returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), pszPath);
			FREE_MEMORY(pszPath);
		}
		id = id->next;
	}

	release_storage_id_callback();
	return 0;
}

//& purpose: Gets the type of the given storage.   
//& type: auto

/**
* @testcase 			ITc_libstorage_get_type_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the type of the given storage.
* @apicovered			storage_get_type
* @passcase				When storage_get_type API return 0
* @failcase				If storage_get_type API returns non zero value
* @precondition			NA
* @postcondition		NA
*/

int ITc_libstorage_get_type_p(void)
{
	START_TEST;

	if (get_storage_id_callback() == false)
		return 1;

	struct str_id *id;
	storage_type_e nType;

	id = storage_head.next;
	while (id) {
		storage_error_e nRet = storage_get_type(id->id, &nType);//target api
		if (nRet != STORAGE_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] storage_get_type failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetError(nRet));
			return 1;
		} else if (nType != STORAGE_TYPE_INTERNAL && nType != STORAGE_TYPE_EXTERNAL) {
			FPRINTF("[Line : %d][%s] storage_get_type failed for %s, value returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetType(nType));
			return 1;
		} else if (nType != id->type) {
			FPRINTF("[Line : %d][%s] storage_get_type failed for %s, value returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetType(nType));
			return 1;
		} else
			FPRINTF("[Line : %d][%s] storage_get_type passed for %s, value returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetType(nType));

		id = id->next;
	}

	release_storage_id_callback();
	return 0;
}

//& purpose: Gets the current state of the given storage.  
//& type: auto

/**
* @testcase 			ITc_libstorage_get_state_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the current state of the given storage.
* @apicovered			storage_get_state
* @passcase				When storage_get_state API return 0
* @failcase				If storage_get_state API returns non zero value
* @precondition			This function is only supported when there is a valid privilege in your module.
* @postcondition		NA
*/
int ITc_libstorage_get_state_p(void)
{
	START_TEST;

	if ( get_storage_id_callback() == false )
		return 1;

	struct str_id *id;
	storage_state_e nState;

	id = storage_head.next;
	while (id) {
		storage_error_e nRet = storage_get_state(id->id, &nState);//target api
		if (nRet != STORAGE_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] storage_get_state failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetError(nRet));
			return 1;
		} else if (nState != STORAGE_STATE_UNMOUNTABLE &&
				nState != STORAGE_STATE_REMOVED &&
				nState != STORAGE_STATE_MOUNTED &&
				nState != STORAGE_STATE_MOUNTED_READ_ONLY) {
			FPRINTF("[Line : %d][%s] storage_get_state failed for %s, value returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetState(nState));
			return 1;
		} else
			FPRINTF("[Line : %d][%s] storage_get_state passed for %s, value returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetState(nState));

		id = id->next;
	}

	release_storage_id_callback();
	return 0;
}
#ifdef TV	//Starts TV
//& purpose: Gets the total space of the given storage in bytes.   
//& type: auto

/**
* @testcase 			ITc_libstorage_get_total_space_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the total space of the given storage in bytes.
* @apicovered			storage_get_total_space
* @passcase				When storage_get_total_space API return 0
* @failcase				If storage_get_total_space API returns non zero value
* @precondition			This function is only supported when there is a valid privilege in your module.
* @postcondition		NA
*/
int ITc_libstorage_get_total_space_p(void)
{
	START_TEST;

	if ( get_storage_id_callback() == false )
		return 1;

	struct str_id *id;
	storage_state_e nState;
	unsigned long long ullBytes;

	id = storage_head.next;
	while (id) {
		if (id->type == STORAGE_TYPE_EXTERNAL) {
			storage_get_state(id->id, &nState);
			if (nState != STORAGE_STATE_MOUNTED) {
				id = id->next;
				continue;
			}
		}
		storage_error_e nRet = storage_get_total_space(id->id, &ullBytes);//target api
		if (nRet != STORAGE_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] storage_get_total_space failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetError(nRet));
			return 1;
		} else if (id->type == STORAGE_TYPE_INTERNAL && ullBytes == 0)
		{
			FPRINTF("[Line : %d][%s] storage_get_total_space failed for %s, value returned = %llu\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), ullBytes);
			return 1;
		} else
			FPRINTF("[Line : %d][%s] storage_get_total_space passed for %s, value returned = %llu\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), ullBytes);

		id = id->next;
	}

	release_storage_id_callback();
	return 0;
}
#endif	//End TV

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) //Starts MOBILE or WEARABLE or TIZENIOT

//& purpose: Gets the total space of the given storage in bytes.   
//& type: auto

/**
* @testcase 			ITc_libstorage_get_total_space_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the total space of the given storage in bytes.
* @apicovered			storage_get_total_space
* @passcase				When storage_get_total_space API return 0
* @failcase				If storage_get_total_space API returns non zero value
* @precondition			This function is only supported when there is a valid privilege in your module.
* @postcondition		NA
*/
int ITc_libstorage_get_total_space_p(void)
{
	START_TEST;

	if ( get_storage_id_callback() == false )
		return 1;

	storage_state_e nState;
	unsigned long long ullBytes;
	struct str_id *id;

	id = storage_head.next;
	while (id) {
		if (id->type == STORAGE_TYPE_EXTERNAL) {
			storage_get_state(id->id, &nState);
			if ( nState != STORAGE_STATE_MOUNTED) {
				id = id->next;
				continue;
			}
		}
		storage_error_e nRet = storage_get_total_space(id->id, &ullBytes);//target api
		if (nRet != STORAGE_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] storage_get_total_space failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetError(nRet));
			return 1;
		} else if (ullBytes == 0) {
			FPRINTF("[Line : %d][%s] storage_get_total_space failed for %s, value returned = %llu\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), ullBytes);
			return 1;
		} else
			FPRINTF("[Line : %d][%s] storage_get_total_space passed for %s, value returned = %llu\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), ullBytes);

		id = id->next;
	}

	release_storage_id_callback();
	return 0;
}
#endif  // End MOBILE or WEARABLE or TIZENIOT

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) //Starts MOBILE or WEARABLE or TIZENIOT

//& purpose: Gets the available space size of the given storage in bytes.  
//& type: auto

/**
* @testcase 			ITc_libstorage_get_available_space_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the available space size of the given storage in bytes.
* @apicovered			storage_get_available_space
* @passcase				When storage_get_available_space API return 0
* @failcase				If storage_get_available_space API returns non zero value
* @precondition			This function is only supported when there is a valid privilege in your module.  
*						Please insert SD card with available space.
* @postcondition		NA
*/
int ITc_libstorage_get_available_space_p(void)
{
	START_TEST;

	if (get_storage_id_callback() == false)
		return 1;

	storage_state_e nState;
	unsigned long long ullBytes = 0;
	struct str_id *id;

	id = storage_head.next;
	while (id) {
		if (id->type == STORAGE_TYPE_EXTERNAL) {
			storage_get_state(id->id, &nState);
			if (nState != STORAGE_STATE_MOUNTED) {
				id = id->next;
				continue;
			}
		}
		storage_error_e nRet = storage_get_available_space(id->id, &ullBytes);//target api
		if (nRet != STORAGE_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] storage_get_available_space failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetError(nRet));
			return 1;
		} else
			FPRINTF("[Line : %d][%s] storage_get_available_space passed for %s, value returned = %llu\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), ullBytes);

		id = id->next;
	}

	release_storage_id_callback();
	return 0;
}
#endif  // End MOBILE or WEARABLE or TIZENIOT

#ifdef TV	//Starts TV
//& purpose: Gets the available space size of the given storage in bytes.  
//& type: auto

/**
* @testcase 			ITc_libstorage_get_available_space_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the available space size of the given storage in bytes.
* @apicovered			storage_get_available_space
* @passcase				When storage_get_available_space API return 0
* @failcase				If storage_get_available_space API returns non zero value
* @precondition			This function is only supported when there is a valid privilege in your module.  
*						Please insert SD card with available space.
* @postcondition		NA
*/
int ITc_libstorage_get_available_space_p(void)
{
	START_TEST;

	if ( get_storage_id_callback() == false )
		return 1;

	storage_state_e nState;
	unsigned long long ullBytes = 0;
	struct str_id *id;

	id = storage_head.next;
	while (id) {
		if (id->type == STORAGE_TYPE_EXTERNAL) {
			storage_get_state(id->id, &nState);
			if (nState != STORAGE_STATE_MOUNTED) {
				id = id->next;
				continue;
			}
		}
		storage_error_e nRet = storage_get_available_space(id->id, &ullBytes);//target api
		if (nRet != STORAGE_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] storage_get_available_space failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetError(nRet));
			return 1;
		} else if (id->type == STORAGE_TYPE_INTERNAL && ullBytes == 0) {
			FPRINTF("[Line : %d][%s] storage_get_available_space failed for %s, value returned = %llu\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), ullBytes);
			return 1;
		} else
			FPRINTF("[Line : %d][%s] storage_get_available_space passed for %s, value returned = %llu\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), ullBytes);

		id = id->next;
	}

	release_storage_id_callback();
	return 0;
}
#endif	//End TV
//& purpose: Registers and Unregister a callback function to be invoked when the state of the storage changes. 
//& type: auto

/**
* @testcase 			ITc_libstorage_set_unset_state_changed_cb_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Registers and Unregister a callback function to be invoked when the state of the storage changes.  
* @apicovered			storage_set_state_changed_cb
* @passcase				When storage_set_state_changed_cb API return 0
* @failcase				If storage_set_state_changed_cb API returns non zero value
* @precondition			This function is only supported when there is a valid privilege in your module.
* @postcondition		NA
*/
int ITc_libstorage_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	if (get_storage_id_callback() == false)
		return 1;

	struct str_id *id;

	id = storage_head.next;
	while (id)
	{
		storage_error_e nRet = storage_set_state_changed_cb(id->id, &Storage_state_changed_cb_p, NULL);//target api//register callback
		if (nRet != STORAGE_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] storage_set_state_changed_cb failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetError(nRet));
			return 1;
		}

		//as we need manual intruption to invoke callback like mount, unmount sdcard
		//so we are not checking callback status
		//CHECK_CALLBACK_STATUS("storage_set_state_changed_cb", nSetFailCount);
		//Unregisters the callback function.
		nRet = storage_unset_state_changed_cb (id->id, &Storage_state_changed_cb_p);//target api//unregister callback
		if (nRet != STORAGE_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] storage_unset_state_changed_cb failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, StorageGetType(id->type), StorageGetError(nRet));
			return 1;
		}

		id = id->next;
	}

	release_storage_id_callback();
	return 0;
}
//& purpose: Registers and Unregisters a callback function to be invoked when the state of the specified storage device type changes. 
//& type: auto

/**
* @testcase 			ITc_libstorage_storage_set_unset_changed_cb_p
* @since_tizen 			3.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @scenario				Registers and Unregister a callback function to be invoked when the state of the storage device type changes.  
* @apicovered			storage_set_changed_cb, storage_unset_changed_cb
* @passcase				When storage_set_changed_cb and storage_unset_changed_cb API passed
* @failcase				If storage_set_state_changed_cb and storage_unset_changed_cb API fails
* @precondition			NA
* @postcondition		storage_changed_cb() will be invoked if the state of the registered storage type changes. 
*/
int ITc_libstorage_storage_set_unset_changed_cb_p(void)
{
	START_TEST;
	if (get_storage_id_callback() == false)
		return 1;

	struct str_id *id;

	id = storage_head.next;

	while (id)
   {
	   if(id->type == STORAGE_TYPE_EXTERNAL)
	   {
			//target api
			storage_error_e nRet = storage_set_changed_cb(id->type, Storage_changed_cb_p, NULL);
			PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_set_changed_cb", StorageGetError(nRet));

			//as we need manual intervention to invoke callback like mount, unmount sdcard
			//so we are not checking callback status

			//target api
			nRet = storage_unset_changed_cb(id->type, Storage_changed_cb_p);
			PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_unset_changed_cb", StorageGetError(nRet));

	   }
	   else
	   {
		   FPRINTF("[Line : %d][%s]Storage type not supported\\n", __LINE__, API_NAMESPACE);
	   }
	   id = id->next;
	}

	release_storage_id_callback();
	return 0;
}

//& purpose: Get storage dev type
//& type: auto

/**
* @testcase 			ITc_libstorage_storage_get_type_dev_p
* @since_tizen 			5.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(nibha.sharma)
* @type 				auto
* @scenario				Get storage dev type.
* @apicovered			storage_get_type_dev
* @passcase				When storage_get_type_dev API passed
* @failcase				If storage_get_type_dev API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_libstorage_storage_get_type_dev_p(void)
{
	START_TEST;

	struct str_id *id;
	int nRet = -1;
	storage_type_e type;
	storage_dev_e dev;

	if (get_storage_id_callback() == false)
		return 1;

	id = storage_head.next;

	while (id) {
		if (id->type != STORAGE_TYPE_EXTERNAL) {
			id = id->next;
			continue;
		}

		nRet = storage_get_type_dev(id->id, &type, &dev);
		if (nRet != STORAGE_ERROR_NONE) {
			FPRINTF("[Line : %d][%s] storage_get_type_dev failed for %d, error returned = %s\\n", __LINE__, API_NAMESPACE, id, StorageGetError(nRet));
			return 1;
		}

		if(type < STORAGE_TYPE_INTERNAL || type > STORAGE_TYPE_EXTENDED_INTERNAL || dev < STORAGE_DEV_EXT_SDCARD || dev > STORAGE_DEV_EXTENDED_INTERNAL)
		{
			FPRINTF("[Line : %d][%s]Storage type %d or dev type %d is not valid\\n", __LINE__, API_NAMESPACE, type, dev);
			return 1;
		}
		id = id->next;
	}

	release_storage_id_callback();
	return 0;
}
/** @} */
/** @} */
