#include "CTs-platform-permission-common.h"

/**
* @function 		CTs_platform_permission_soundmanager_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_soundmanager_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_soundmanager_startup\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function 		CTs_platform_permission_soundmanager_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_soundmanager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_soundmanager_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/**
* @function 		SoundManagerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* SoundManagerGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SOUND_MANAGER_ERROR_NONE:					szErrorVal = "SOUND_MANAGER_ERROR_NONE";					break;
	case SOUND_MANAGER_ERROR_OUT_OF_MEMORY:			szErrorVal = "SOUND_MANAGER_ERROR_OUT_OF_MEMORY";			break;
	case SOUND_MANAGER_ERROR_INVALID_PARAMETER:		szErrorVal = "SOUND_MANAGER_ERROR_INVALID_PARAMETER";		break;
	case SOUND_MANAGER_ERROR_INVALID_OPERATION:		szErrorVal = "SOUND_MANAGER_ERROR_INVALID_OPERATION";		break;
	case SOUND_MANAGER_ERROR_PERMISSION_DENIED:		szErrorVal = "SOUND_MANAGER_ERROR_PERMISSION_DENIED";		break;
	case SOUND_MANAGER_ERROR_NOT_SUPPORTED:			szErrorVal = "SOUND_MANAGER_ERROR_NOT_SUPPORTED";			break;
	case SOUND_MANAGER_ERROR_NO_DATA:				szErrorVal = "SOUND_MANAGER_ERROR_NO_DATA";					break;
	case SOUND_MANAGER_ERROR_NO_PLAYING_SOUND:		szErrorVal = "SOUND_MANAGER_ERROR_NO_PLAYING_SOUND";		break;
	case SOUND_MANAGER_ERROR_INTERNAL:				szErrorVal = "SOUND_MANAGER_ERROR_INTERNAL";				break;
	case SOUND_MANAGER_ERROR_POLICY:				szErrorVal = "SOUND_MANAGER_ERROR_POLICY";					break;
	default:										szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}
//& purpose:Checking tizen.org/privilege/volume.set privilege
//& type: auto
/**
* @testcase			CTc_SoundManager_PrivilegeVolumeSet_getvolume
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID((shobhit.v)
* @type 			auto
* @scenario			Gets the volume level specified for a particular sound type\n
*					Sets the volume level specified for a particular sound type
* @apicovered		sound_manager_get_volume and sound_manager_set_volume
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_SoundManager_PrivilegeVolumeSet_getvolume(void)
{
	START_TEST;
	int nVolumeLevel = SOUND_MANAGER_VOLUME_LEVEL;

	int nRet = sound_manager_set_volume(SOUND_TYPE_MEDIA, nVolumeLevel);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "sound_manager_set_volume", SoundManagerGetError(nRet));
	
	return 0;
}