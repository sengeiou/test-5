#include "CTs-platform-permission-common.h"
#include <thumbnail_util.h>
#include <storage.h>
#define MEDIA_IMAGE_WIDTH		1280
#define MEDIA_IMAGE_HEIGHT		720
#define SAMPLE_FILE_PATH_1		"PlatformPermission_test.jpg"
bool g_bCallbackHit;
bool g_bCallBackHit;
int errorcode;
GMainLoop *g_pDataControlMainLoop;
#define TIMEOUT_CB                              10000

#define RUN_POLLING_LOOP {\
        if ( !g_bCallbackHit )\
{\
        g_pDataControlMainLoop = g_main_loop_new(NULL, false);\
        nTimeoutId = g_timeout_add(TIMEOUT_CB, ThumbNailTimeout, g_pDataControlMainLoop);\
        g_main_loop_run(g_pDataControlMainLoop);\
        g_source_remove(nTimeoutId);\
        g_pDataControlMainLoop = NULL;\
}\
}

const char *target_image_source_path = NULL;

/**
* @function             storage_device_cb
* @description          Retrives the internal storage directory and set resource path
* @parameter            int storage_id, storage_type_e type, storage_state_e state, const char* path
, void* user_data
* @return               bool
*/
static bool storage_device_cb(int storage_id, storage_type_e type, storage_state_e state, const char* path, void* user_data)
{
	if (type == STORAGE_TYPE_INTERNAL)
	{
		target_image_source_path=(char*)calloc(strlen(path)+strlen("/Images/")+strlen(SAMPLE_FILE_PATH_1)+1, sizeof(char));
		if(target_image_source_path == NULL)
		{
			FPRINTF("[Line : %d][%s] calloc failure in storage_device_cb \\n", __LINE__, API_NAMESPACE);
			return true;//ambiguous but true
		}
		snprintf(target_image_source_path, strlen(path)+strlen("/Images/")+strlen(SAMPLE_FILE_PATH_1)+1,"%s/Images/%s",path,SAMPLE_FILE_PATH_1);
		FPRINTF("[Line : %d][%s] Thumbnail Image Path : %s\\n", __LINE__, API_NAMESPACE, target_image_source_path);
		return false;
	}
	return true;
}

/**
* @function             DataControlTimeout
* @description          Called if some callback is not invoked for a particular timeout
* @parameter            gpointer data
* @return                       gboolean
*/
gboolean ThumbNailTimeout(gpointer data)
{
        GMainLoop *pMainLoop = NULL;
        pMainLoop = (GMainLoop *)data;
        if ( pMainLoop != NULL )
        {
                g_main_loop_quit(pMainLoop);
        }
        FPRINTF("[Line : %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
        return false;
}

/**
* @function 			ThumbnailGetDataPath
* @description 			Get the path to application data directory
* @parameter	[IN]	char* pszFileName [file name]
* @return 				NA
*/
char* ThumbnailGetDataPath(char *pszFileName)
{
	char *pszAppData =  app_get_data_path(),*pszImgPath = NULL;
	if ( pszAppData == NULL || strlen(pszAppData) == 0 )
	{
		FPRINTF("[Line : %d][%s] app_get_data_path() returned invalid path\\n", __LINE__, API_NAMESPACE);
		return pszImgPath;
	}
	
	pszImgPath = (char*) calloc(1, strlen(pszAppData) + strlen(pszFileName)+1);
	if (pszImgPath == NULL)
		return pszImgPath;
	snprintf(pszImgPath, "%s%s",pszAppData, pszFileName, strlen(pszAppData) + strlen(pszFileName));
	FPRINTF("[Line : %d][%s] app_get_data_path() is %s\\n", __LINE__, API_NAMESPACE, pszImgPath);
	return pszImgPath;
}

/**
 * @function 		ThumbnailUtilGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* ThumbnailUtilGetError(int nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
		case THUMBNAIL_UTIL_ERROR_NONE:				
			szErrorVal = "THUMBNAIL_UTIL_ERROR_NONE";					
			break;
		case THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER:			
			szErrorVal = "THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER";			
			break;
		case THUMBNAIL_UTIL_ERROR_OUT_OF_MEMORY:		
			szErrorVal = "THUMBNAIL_UTIL_ERROR_OUT_OF_MEMORY";		
			break;
		case THUMBNAIL_UTIL_ERROR_INVALID_OPERATION:			
			szErrorVal = "THUMBNAIL_UTIL_ERROR_INVALID_OPERATION";			
			break;
		case THUMBNAIL_UTIL_ERROR_FILE_NO_SPACE_ON_DEVICE:	
			szErrorVal = "THUMBNAIL_UTIL_ERROR_FILE_NO_SPACE_ON_DEVICE";	
			break;
		case THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED:			
			szErrorVal = "THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED";				
			break;
	}

	return szErrorVal;
}
/**
* @function 		thumbnail_completed_cb
* @description	 	Called before each test extracting the thumbnail for the given media
* @parameter		NA
* @return 			NA
*/
void thumbnail_completed_cb(thumbnail_util_error_e error, const char *request_id, int thumb_width, int thumb_height, unsigned char *thumb_data, int thumb_size, void *user_data)
{
    g_bCallBackHit = true;
	//*(int*)user_data = error_code;
	if ( error == THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED )
    {
		FPRINTF("[Line : %d][%s] %s \\n", __LINE__, API_NAMESPACE,  "THUMBNAIL_UTIL_ERROR_PERMISSION_DENIED ");
    }
	errorcode = error;
	FPRINTF("[Line : %d][%s] thumbnail_completed_cb CallBack Invoked\\n", __LINE__, API_NAMESPACE);
	if ( g_pMainLoop )
    {
        g_main_loop_quit(g_pMainLoop);
    }	
	return;
}
 
/**
* @function         CTs_platform_permission_thumbnailutil_startup
* @description         Called before each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_thumbnailutil_startup(void)
{
    struct stat stBuff;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
	if (remove(ERR_LOG))
	{
		FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
	}
    }

#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);

	storage_foreach_device_supported(storage_device_cb,NULL);
}

/**
* @function         CTs_platform_permission_thumbnailutil_cleanup
* @description         Called after each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_thumbnailutil_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	if (target_image_source_path)
	{
		free(target_image_source_path);
		target_image_source_path = NULL;
	}
	return;
}
