//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
#include "ITs-metadata-editor-common.h"

/** @addtogroup itc-metadata-editor
* @ingroup		itc
* @{
*/

//& set: MetadataEditor

 metadata_editor_attr_e g_attribute[] = {
    METADATA_EDITOR_ATTR_ARTIST,
	METADATA_EDITOR_ATTR_TITLE,
	METADATA_EDITOR_ATTR_ALBUM,
	METADATA_EDITOR_ATTR_GENRE,
	METADATA_EDITOR_ATTR_AUTHOR,
	METADATA_EDITOR_ATTR_COPYRIGHT,
	METADATA_EDITOR_ATTR_DATE,
	METADATA_EDITOR_ATTR_DESCRIPTION,
	METADATA_EDITOR_ATTR_COMMENT,
	METADATA_EDITOR_ATTR_TRACK_NUM,
	METADATA_EDITOR_ATTR_CONDUCTOR,
	METADATA_EDITOR_ATTR_UNSYNCLYRICS
};

/**
 * @function 		ITs_metadata_editor_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_metadata_editor_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	char szAudioFilePath[PATH_LEN] = {0,};

	int nRet = metadata_editor_create(&g_hMetadataEditorHandle );

	if ( nRet != METADATA_EDITOR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] metadata_editor_create failed\\n", __LINE__, API_NAMESPACE);
		Metadata_EditorGetError(nRet);
		return;
	}

	if ( false == MetadataEditorAppendToAppDataPath(MEDIA_AUDIO_PATH, szAudioFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		metadata_editor_destroy(g_hMetadataEditorHandle);
		return;
	}

	nRet = metadata_editor_set_path(g_hMetadataEditorHandle, szAudioFilePath);

	if ( nRet != METADATA_EDITOR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] metadata_editor_set_path failed\\n", __LINE__, API_NAMESPACE);
		metadata_editor_destroy(g_hMetadataEditorHandle);
		Metadata_EditorGetError(nRet);
		return;
	}

	return;
}


/**
 * @function 		ITs_metadata_editor_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_metadata_editor_cleanup(void)
{
	int nRet = metadata_editor_destroy(g_hMetadataEditorHandle);

	if ( nRet != METADATA_EDITOR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] metadata_editor_destroy failed\\n", __LINE__, API_NAMESPACE);
		Metadata_EditorGetError(nRet);
		return;
	}
	return;
}

/** @addtogroup	itc-metadata-editor-testcases
* @brief 		Integration testcases for module metadata-editor
* @ingroup		itc-metadata-editor
* @{
*/

//& type: auto
//& purpose: create and destroy meta-data editor handle
/**
 * @testcase 				ITc_metadata_editor_create_destroy_p
 * @since_tizen				2.4
 * @author            		SRID(a.ankush)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				create and destroy meta-data editor handle
 * @scenario				NA
 * @apicovered				metadata_editor_create ,metadata_editor_destroy
 * @passcase				When metadata_editor_create and metadata_editor_destroy is successful
 * @failcase				If metadata_editor_create or metadata_editor_destroy fails.
 * @precondition			create a meta-data editor valid handle using metadata_editor_create API
 * @postcondition			NA
 */
int ITc_metadata_editor_create_destroy_p(void)
{
	START_TEST;
	metadata_editor_h hMetadata;

	int nRet = metadata_editor_create(&hMetadata);
	PRINT_RESULT(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_create", Metadata_EditorGetError(nRet));

	char szAudioFilePath[PATH_LEN] = {0,};
	if ( false == MetadataEditorAppendToAppDataPath(MEDIA_AUDIO_PATH, szAudioFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		metadata_editor_destroy(hMetadata);
		return 1;
	}

	nRet = metadata_editor_set_path(hMetadata, szAudioFilePath);
	PRINT_RESULT_CLEANUP(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_set_path", Metadata_EditorGetError(nRet), metadata_editor_destroy(hMetadata));

	char szWavFilePath[PATH_LEN] = {0,};
	if ( false == MetadataEditorAppendToAppDataPath(MEDIA_WAV_PATH, szWavFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		metadata_editor_destroy(g_hMetadataEditorHandle);
		return 1;
	}

	nRet = metadata_editor_set_path(hMetadata, szWavFilePath);
	PRINT_RESULT_CLEANUP(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_set_path", Metadata_EditorGetError(nRet), metadata_editor_destroy(hMetadata));

	char szFlacFilePath[PATH_LEN] = {0,};
	if ( false == MetadataEditorAppendToAppDataPath(MEDIA_FLAC_PATH, szFlacFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		metadata_editor_destroy(g_hMetadataEditorHandle);
		return 1;
	}

	nRet = metadata_editor_set_path(hMetadata, szFlacFilePath);
	PRINT_RESULT_CLEANUP(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_set_path", Metadata_EditorGetError(nRet), metadata_editor_destroy(hMetadata));

	char szOggFilePath[PATH_LEN] = {0,};
	if ( false == MetadataEditorAppendToAppDataPath(MEDIA_OGG_PATH, szOggFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		metadata_editor_destroy(g_hMetadataEditorHandle);
		return 1;
	}

	nRet = metadata_editor_set_path(hMetadata, szOggFilePath);
	PRINT_RESULT_CLEANUP(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_set_path", Metadata_EditorGetError(nRet), metadata_editor_destroy(hMetadata));

	nRet = metadata_editor_destroy(hMetadata);
	PRINT_RESULT(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_destroy", Metadata_EditorGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Sets a file path for meta-data editor.
/**
 * @testcase 				ITc_metadata_editor_set_path_p
 * @since_tizen				2.4
 * @author            		SRID(a.ankush)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Sets a file path for meta-data extraction.
 * @scenario				Before getting artwork of file need to set file path.
 * @apicovered				metadata_editor_set_path
 * @passcase				When metadata_editor_set_path is successful
 * @failcase				If metadata_editor_set_path fails.
 * @precondition			create a meta-data editor valid handle using metadata_editor_create API
 * @postcondition			NA
 */
int ITc_metadata_editor_set_path_p(void)
{
	START_TEST;

	char szAudioFilePath[PATH_LEN] = {0,};
	if ( false == MetadataEditorAppendToAppDataPath(MEDIA_AUDIO_PATH, szAudioFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = metadata_editor_set_path(g_hMetadataEditorHandle,szAudioFilePath );
	PRINT_RESULT(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_set_path", Metadata_EditorGetError(nRet));

	char szWavFilePath[PATH_LEN] = {0,};
	if ( false == MetadataEditorAppendToAppDataPath(MEDIA_WAV_PATH, szWavFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		metadata_editor_destroy(g_hMetadataEditorHandle);
		return 1;
	}

	nRet = metadata_editor_set_path(g_hMetadataEditorHandle,szWavFilePath );
        PRINT_RESULT(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_set_path", Metadata_EditorGetError(nRet));

	char szFlacFilePath[PATH_LEN] = {0,};
	if ( false == MetadataEditorAppendToAppDataPath(MEDIA_FLAC_PATH, szFlacFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		metadata_editor_destroy(g_hMetadataEditorHandle);
		return 1;
	}

	nRet = metadata_editor_set_path(g_hMetadataEditorHandle, szFlacFilePath);
	PRINT_RESULT_CLEANUP(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_set_path", Metadata_EditorGetError(nRet), metadata_editor_destroy(g_hMetadataEditorHandle));

	char szOggFilePath[PATH_LEN] = {0,};
	if ( false == MetadataEditorAppendToAppDataPath(MEDIA_OGG_PATH, szOggFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		metadata_editor_destroy(g_hMetadataEditorHandle);
		return 1;
	}

	nRet = metadata_editor_set_path(g_hMetadataEditorHandle, szOggFilePath);
	PRINT_RESULT_CLEANUP(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_set_path", Metadata_EditorGetError(nRet), metadata_editor_destroy(g_hMetadataEditorHandle));

	return 0;

}

//& purpose: Gets meta-data and sets meta-data of multimedia file.
//& type: auto
/**
 * @testcase 			ITc_metadata_editor_set_get_metadata_p
 * @since_tizen			2.4
 * @author            	SRID(a.ankush)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Gets meta-data and sets meta-data of multimedia file.
 * @scenario			Before getting artwork of file need to set file path.
 * @apicovered			metadata_editor_get_metadata ,metadata_editor_set_metadata.
 * @passcase			When metadata_editor_set_metadata & metadata_editor_get_metadata is successful
 * @failcase			If metadata_editor_set_metadata or metadata_editor_get_metadata fails
 * @precondition		Set path to extract by calling metadata_extractor_set_path
 * @postcondition		return buffer on success
 */
int ITc_metadata_editor_set_get_metadata_p(void)
{
	START_TEST;

	char input_data[] = "Metadata_editor_attributes_info";
	int nRet = 0;
	char * pMetadataInfo = NULL;
	int i = 0;
	for( i = 0; i < (sizeof(g_attribute)/sizeof(int)); ++i)
	{
		nRet = metadata_editor_set_metadata(g_hMetadataEditorHandle, g_attribute[i], input_data );
		PRINT_RESULT(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_set_metadata", Metadata_EditorGetError(nRet));

		nRet = metadata_editor_get_metadata(g_hMetadataEditorHandle, g_attribute[i], &pMetadataInfo );

		//check for value mis-match
		if ( 0 != strcmp(input_data, pMetadataInfo) )
		{
			FPRINTF("[Line : %d][%s] set and get mis-match occurs, set value = %s, get value = %s\\n", __LINE__, API_NAMESPACE, input_data, pMetadataInfo);
			FREE_MEMORY(pMetadataInfo);
			return 1;
		}

		FREE_MEMORY(pMetadataInfo);
		PRINT_RESULT(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_get_metadata", Metadata_EditorGetError(nRet));
	}
	return 0;
}

//& purpose: Updates meta-data of multimedia file.
//& type: auto
/**
 * @testcase 			ITc_metadata_editor_update_metadata_p
 * @since_tizen 		2.4
 * @author            	SRID(a.ankush)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Updates meta-data of multimedia file.
 * @scenario			Before getting artwork of file need to set file path\n
 *						Set or change meta-data attribute of multimedia file.
 * @apicovered			metadata_editor_set_metadata,metadata_editor_update_metadata.
 * @passcase			When metadata_editor_set_metadata and metadata_editor_update_metadata is successful.
 * @failcase			If metadata_editor_set_metadata and metadata_editor_update_metadata fails.
 * @precondition		Set path to extract by calling metadata_extractor_set_path.
 * @postcondition		NA.
 */
int ITc_metadata_editor_update_metadata_p(void)
{
	START_TEST;

	int nRet = metadata_editor_set_metadata(g_hMetadataEditorHandle, METADATA_EDITOR_ATTR_ARTIST, "metadata_editor");
	PRINT_RESULT(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_set_path", Metadata_EditorGetError(nRet));

	nRet = metadata_editor_update_metadata(g_hMetadataEditorHandle);
	PRINT_RESULT(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_update_metadata", Metadata_EditorGetError(nRet));

	return 0;
}

//& purpose: Append the picture to the media file.
//& type: auto
/**
 * @testcase 			ITc_metadata_editor_get_picture_p
 * @since_tizen 		2.4
 * @author            	SRID(a.ankush)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Append the picture to the media file.
 * @scenario			Before getting artwork of file need to set file path.
 * @apicovered			metadata_editor_append_picture.
 * @passcase			When metadata_editor_append_picture is successful.
 * @failcase			If metadata_editor_append_picture fails.
 * @precondition		Set path to extract by calling metadata_extractor_set_path.
 * @postcondition		NA.
 */
int ITc_metadata_editor_append_picture_p(void)
{
	START_TEST;
	char szVideoFilePath[PATH_LEN] = {0,};
	char szPicturePath[PATH_LEN] = {0,};

	if ( false == MetadataEditorAppendToAppDataPath(MEDIA_VIDEO_PATH, szVideoFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == MetadataEditorAppendToAppDataPath(MEDIA_PICTURE_PATH, szPicturePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = metadata_editor_append_picture(g_hMetadataEditorHandle,szPicturePath );
	PRINT_RESULT(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_append_picture", Metadata_EditorGetError(nRet));

	return 0;
}

//& purpose: Get the picture in the multimedia file.
//& type: auto
/**
 * @testcase 			ITc_metadata_editor_get_picture_p
 * @since_tizen 		2.3
 * @author            	SRID(a.ankush)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Get the picture in the multimedia file.
 * @scenario			Before getting artwork of file need to set file path\n
 *						Get the picture index attribute from the multimedia file.
 * @apicovered			metadata_editor_get_metadata,metadata_editor_get_picture.
 * @passcase			When metadata_editor_get_metadata and metadata_editor_get_picture is successful.
 * @failcase			If metadata_editor_get_metadata and metadata_editor_get_picture fails.
 * @precondition		Set path to extract by calling metadata_extractor_set_path.
 * @postcondition		NA.
 */
int ITc_metadata_editor_get_picture_p(void)
{
	START_TEST;

	char *szMimeType_handle = NULL;//"JPG";
	int size =0;
	char szAudioFilePath[PATH_LEN] = {0,};
	metadata_editor_attr_e attribute = METADATA_EDITOR_ATTR_PICTURE_NUM;
	char* picture_index = NULL;
	metadata_editor_h g_hMetadata_local;

	int nRet = metadata_editor_create(&g_hMetadata_local );
	PRINT_RESULT(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_create", Metadata_EditorGetError(nRet));

	if ( false == MetadataEditorAppendToAppDataPath(MEDIA_AUDIO_PATH, szAudioFilePath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	void *picture_val = NULL;
	nRet = metadata_editor_set_path(g_hMetadata_local, szAudioFilePath);
	PRINT_RESULT_CLEANUP(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_set_path", Metadata_EditorGetError(nRet), metadata_editor_destroy(g_hMetadata_local));

	nRet = metadata_editor_get_metadata(g_hMetadata_local, attribute, &picture_index);
	PRINT_RESULT_CLEANUP(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_get_metadata", Metadata_EditorGetError(nRet),metadata_editor_destroy(g_hMetadata_local));

	uint num = 0;
	num = atoi(picture_index);
	FPRINTF("[Line : %d][%s] Number value is %d \\n", __LINE__, API_NAMESPACE,num);
	nRet = metadata_editor_get_picture(g_hMetadata_local,num-1 ,&picture_val ,&size,&szMimeType_handle );
	PRINT_RESULT_CLEANUP(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_get_picture", Metadata_EditorGetError(nRet),metadata_editor_destroy(g_hMetadata_local));

	FREE_MEMORY(picture_val);
	FREE_MEMORY(picture_index);

	nRet = metadata_editor_destroy(g_hMetadata_local);
	PRINT_RESULT(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_destroy", Metadata_EditorGetError(nRet));

	return 0;
}

//& purpose: Remove artwork image from media file.
//& type: auto
/**
 * @testcase 			ITc_metadata_editor_remove_picture_p
 * @since_tizen 		2.3
 * @author            	SRID(a.ankush)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Remove artwork image from media file.
 * @scenario			Before getting artwork of file need to set file path.
 * @apicovered			metadata_editor_remove_picture.
 * @passcase			When metadata_editor_remove_picture is successful.
 * @failcase			If metadata_editor_remove_picture fails.
 * @precondition		Set path to extract by calling metadata_extractor_set_path.
 * @postcondition		NA
 */
int ITc_metadata_editor_remove_picture_p(void)
{
	START_TEST;
	int index = 0;

	int nRet = metadata_editor_remove_picture(g_hMetadataEditorHandle,index);
	PRINT_RESULT(METADATA_EDITOR_ERROR_NONE, nRet, "metadata_editor_remove_picture", Metadata_EditorGetError(nRet));

	return 0;
}

/** @} */ //end of itc-metadata-editor
/** @} */ //end of itc-metadata-editor-testcases
