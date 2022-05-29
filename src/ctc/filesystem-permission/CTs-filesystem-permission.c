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
#include "CTs-filesystem-permission-common.h"


/** @addtogroup ctc-filesystem-permission
* @ingroup		ctc
* @{
*/

//& set: FilesystemPermission

static int internal_storage_id = -1;
static int external_storage_id = -1;

static bool get_storage(int storage_id, storage_type_e type,
		storage_state_e state, const char *path, void *user_data)
{
	if (type == STORAGE_TYPE_INTERNAL && internal_storage_id < 0)
		internal_storage_id = storage_id;
	else if (type == STORAGE_TYPE_EXTERNAL && external_storage_id < 0)
		external_storage_id = storage_id;

	return true;
}

/**
* @function 		CTs_filesystem_permission_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_filesystem_permission_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

	storage_foreach_device_supported(get_storage, NULL);
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_FileSystem_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_filesystem_permission_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_filesystem_permission_cleanup(void)
{
	internal_storage_id = -1;
	external_storage_id = -1;
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_FileSystem_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	ctc-filesystem-permission-testcases
* @brief 		Integration testcases for module filesystem-permission
* @ingroup		ctc-filesystem-permission
* @{
*/

//& purpose: Check for File system permission in STORAGE_DIRECTORY_IMAGES
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToImages_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the STORAGE_DIRECTORY_IMAGES directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFileToImages_p(void)
{
	START_TEST;
	if ( FilePermissionCreateFile(internal_storage_id, STORAGE_DIRECTORY_IMAGES) == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Check for File system permission in STORAGE_DIRECTORY_SOUNDS
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToSounds_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the STORAGE_DIRECTORY_SOUNDS directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFileToSounds_p(void)
{
	START_TEST;

	if ( FilePermissionCreateFile(internal_storage_id, STORAGE_DIRECTORY_SOUNDS) == false )
	{
		return 1;
	}	return 0;
}

//& purpose: Check for File system permission in STORAGE_DIRECTORY_VIDEOS
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToVideos_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the STORAGE_DIRECTORY_VIDEOS directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFileToVideos_p(void)
{
	START_TEST;

	if ( FilePermissionCreateFile(internal_storage_id, STORAGE_DIRECTORY_VIDEOS) == false )
	{
		return 1;
	}	return 0;
}

//& purpose: Check for File system permission in STORAGE_DIRECTORY_CAMERA
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToCamera_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the STORAGE_DIRECTORY_CAMERA directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFileToCamera_p(void)
{
	START_TEST;

	if ( FilePermissionCreateFile(internal_storage_id, STORAGE_DIRECTORY_CAMERA) == false )
	{
		return 1;
	}	return 0;
}

//& purpose: Check for File system permission in STORAGE_DIRECTORY_DOWNLOADS
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToDownloads_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the STORAGE_DIRECTORY_DOWNLOADS directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFileToDownloads_p(void)
{
	START_TEST;

	if ( FilePermissionCreateFile(internal_storage_id, STORAGE_DIRECTORY_DOWNLOADS) == false )
	{
		return 1;
	}	return 0;
}

//& purpose: Check for File system permission in STORAGE_DIRECTORY_MUSIC
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToMusic_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the STORAGE_DIRECTORY_MUSIC directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the files
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFileToMusic_p(void)
{
	START_TEST;

	if ( FilePermissionCreateFile(internal_storage_id, STORAGE_DIRECTORY_MUSIC) == false )
	{
		return 1;
	}	return 0;
}

//& purpose: Check for File system permission in STORAGE_DIRECTORY_DOCUMENTS
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToDocuments_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the STORAGE_DIRECTORY_DOCUMENTS directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFileToDocuments_p(void)
{
	START_TEST;

	if ( FilePermissionCreateFile(internal_storage_id, STORAGE_DIRECTORY_DOCUMENTS) == false )
	{
		return 1;
	}	return 0;
}

//& purpose: Check for File system permission in STORAGE_DIRECTORY_OTHERS
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToOthers_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the STORAGE_DIRECTORY_OTHERS directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFileToOthers_p(void)
{
	START_TEST;

	if ( FilePermissionCreateFile(internal_storage_id, STORAGE_DIRECTORY_OTHERS) == false )
	{
		return 1;
	}	return 0;
}

//& purpose: Check for File system permission in External STORAGE_DIRECTORY_IMAGES
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToExternalImages_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the External STORAGE_DIRECTORY_IMAGES directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFileToExternalImages_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateFile(external_storage_id, STORAGE_DIRECTORY_IMAGES) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for File system permission in External STORAGE_DIRECTORY_SOUNDS
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToExternalSounds_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the External STORAGE_DIRECTORY_SOUNDS directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFileToExternalSounds_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateFile(external_storage_id, STORAGE_DIRECTORY_SOUNDS) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for File system permission in External STORAGE_DIRECTORY_VIDEOS
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToExternalVideos_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the External STORAGE_DIRECTORY_VIDEOS directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFileToExternalVideos_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateFile(external_storage_id, STORAGE_DIRECTORY_VIDEOS) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for File system permission in External STORAGE_DIRECTORY_CAMERA
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToExternalCamera_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the External STORAGE_DIRECTORY_CAMERA directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFileToExternalCamera_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateFile(external_storage_id, STORAGE_DIRECTORY_CAMERA) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for File system permission in External STORAGE_DIRECTORY_DOWNLOADS
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToExternalDownloads_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the External STORAGE_DIRECTORY_DOWNLOADS directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFileToExternalDownloads_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateFile(external_storage_id, STORAGE_DIRECTORY_DOWNLOADS) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for File system permission in External STORAGE_DIRECTORY_MUSIC
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToExternalMusic_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the External STORAGE_DIRECTORY_MUSIC directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFileToExternalMusic_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateFile(external_storage_id, STORAGE_DIRECTORY_MUSIC) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for File system permission in External STORAGE_DIRECTORY_DOCUMENTS
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToExternalDocuments_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the External STORAGE_DIRECTORY_DOCUMENTS directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFileToExternalDocuments_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateFile(external_storage_id, STORAGE_DIRECTORY_DOCUMENTS) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for File system permission in External STORAGE_DIRECTORY_OTHERS
//& eType: auto
/**
* @testcase	 		CTc_CreateFileToExternalOthers_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Create a file to the External STORAGE_DIRECTORY_OTHERS directory\n
* 					Check whether file creation is permitted in this directory or not\n
* 					Close and remove the file
* @apicovered		storage_get_directory
* @passcase			If it successfully create a file in the given directory. 
* @failcase			If it fails to create a file in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFileToExternalOthers_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateFile(external_storage_id, STORAGE_DIRECTORY_OTHERS) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for Directory system permission in STORAGE_DIRECTORY_IMAGES
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToImages_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the STORAGE_DIRECTORY_IMAGES directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFolderToImages_p(void)
{
	START_TEST;

	if ( FilePermissionCreateDirectory(internal_storage_id, STORAGE_DIRECTORY_IMAGES) == false )
	{
		return 1;
	}	return 0;
}

//& purpose: Check for Directory system permission in STORAGE_DIRECTORY_SOUNDS
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToSounds_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the STORAGE_DIRECTORY_SOUNDS directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFolderToSounds_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateDirectory(external_storage_id, STORAGE_DIRECTORY_SOUNDS) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for Directory system permission in STORAGE_DIRECTORY_VIDEOS
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToVideos_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the STORAGE_DIRECTORY_VIDEOS directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFolderToVideos_p(void)
{
	START_TEST;

	if ( FilePermissionCreateDirectory(internal_storage_id, STORAGE_DIRECTORY_VIDEOS) == false )
	{
		return 1;
	}	return 0;
}

//& purpose: Check for Directory system permission in STORAGE_DIRECTORY_CAMERA
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToCamera_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the STORAGE_DIRECTORY_CAMERA directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFolderToCamera_p(void)
{
	START_TEST;

	if ( FilePermissionCreateDirectory(internal_storage_id, STORAGE_DIRECTORY_CAMERA) == false )
	{
		return 1;
	}	return 0;
}

//& purpose: Check for Directory system permission in STORAGE_DIRECTORY_DOWNLOADS
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToDownloads_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the STORAGE_DIRECTORY_DOWNLOADS directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFolderToDownloads_p(void)
{
	START_TEST;

	if ( FilePermissionCreateDirectory(internal_storage_id, STORAGE_DIRECTORY_DOWNLOADS) == false )
	{
		return 1;
	}	return 0;
}

//& purpose: Check for Directory system permission in STORAGE_DIRECTORY_MUSIC
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToMusic_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the STORAGE_DIRECTORY_MUSIC directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFolderToMusic_p(void)
{
	START_TEST;

	if ( FilePermissionCreateDirectory(internal_storage_id, STORAGE_DIRECTORY_MUSIC) == false )
	{
		return 1;
	}	return 0;
}

//& purpose: Check for Directory system permission in STORAGE_DIRECTORY_DOCUMENTS
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToDocuments_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the STORAGE_DIRECTORY_DOCUMENTS directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFolderToDocuments_p(void)
{
	START_TEST;

	if ( FilePermissionCreateDirectory(internal_storage_id, STORAGE_DIRECTORY_DOCUMENTS) == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Check for Directory system permission in STORAGE_DIRECTORY_OTHERS
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToOthers_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the STORAGE_DIRECTORY_OTHERS directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		NA
* @postcondition	NA
*/
int CTc_CreateFolderToOthers_p(void)
{
	START_TEST;

	if ( FilePermissionCreateDirectory(internal_storage_id, STORAGE_DIRECTORY_OTHERS) == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Check for Directory system permission in External STORAGE_DIRECTORY_IMAGES
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToExternalImages_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the External STORAGE_DIRECTORY_IMAGES directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFolderToExternalImages_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateDirectory(external_storage_id, STORAGE_DIRECTORY_IMAGES) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for Directory system permission in External STORAGE_DIRECTORY_SOUNDS
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToExternalSounds_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the External STORAGE_DIRECTORY_SOUNDS directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFolderToExternalSounds_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateDirectory(external_storage_id, STORAGE_DIRECTORY_SOUNDS) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for Directory system permission in External STORAGE_DIRECTORY_VIDEOS
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToExternalVideos_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the External STORAGE_DIRECTORY_VIDEOS directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFolderToExternalVideos_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateDirectory(external_storage_id, STORAGE_DIRECTORY_VIDEOS) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for Directory system permission in External STORAGE_DIRECTORY_CAMERA
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToExternalCamera_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the External STORAGE_DIRECTORY_CAMERA directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFolderToExternalCamera_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateDirectory(external_storage_id, STORAGE_DIRECTORY_CAMERA) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for Directory system permission in External STORAGE_DIRECTORY_DOWNLOADS
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToExternalDownloads_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the External STORAGE_DIRECTORY_DOWNLOADS directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFolderToExternalDownloads_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateDirectory(external_storage_id, STORAGE_DIRECTORY_DOWNLOADS) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for Directory system permission in External STORAGE_DIRECTORY_MUSIC
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToExternalMusic_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the External STORAGE_DIRECTORY_MUSIC directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFolderToExternalMusic_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateDirectory(external_storage_id, STORAGE_DIRECTORY_MUSIC) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for Directory system permission in External STORAGE_DIRECTORY_DOCUMENTS
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToExternalDocuments_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the External STORAGE_DIRECTORY_DOCUMENTS directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition		Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFolderToExternalDocuments_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateDirectory(external_storage_id, STORAGE_DIRECTORY_DOCUMENTS) == false )
		{
			return 1;
		}
	}
	return 0;
}

//& purpose: Check for Directory system permission in External STORAGE_DIRECTORY_OTHERS
//& eType: auto
/**
* @testcase	 		CTc_CreateFolderToExternalOthers_p
* @since_tizen		2.3
* @author            SRID(gaurav.m2)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Creates a folder to the External STORAGE_DIRECTORY_OTHERS directory\n
* 					Check whether folder creation is permitted in this directory or not\n
* 					Remove the folder
* @apicovered		storage_get_directory
* @passcase			If it successfully create a folder in the given directory. 
* @failcase			If it fails to create a folder in the given directory.
* @precondition			Insert an external sdcard to memory slot into device
* @postcondition	NA
*/
int CTc_CreateFolderToExternalOthers_p(void)
{
	START_TEST;

	if (external_storage_id >= 0 ) {
		if ( FilePermissionCreateDirectory(external_storage_id, STORAGE_DIRECTORY_OTHERS) == false )
		{
			return 1;
		}
	}
	return 0;
}

/** @} */ //end of ctc-filesystem-permission
/** @} */ //end of ctc-filesystem-permission-testcases
