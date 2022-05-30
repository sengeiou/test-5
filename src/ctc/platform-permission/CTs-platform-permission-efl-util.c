#include "CTs-platform-permission-common.h"
#include <efl_util.h>

/**
* @function 			EFLUTILGetError
* @description 			print the error information
* @parameter[in]		nResult: the error code
* @return 			pszErrorMsg: return the error message
*/
char *EFLUTILGetError(int nResult)
{
	char *pszErrorMsg = "UNDEFINED ERROR \n";

	switch ( nResult )
	{
	case EFL_UTIL_ERROR_NONE :
		pszErrorMsg = "EFL_UTIL_ERROR_NONE  \n";
		break;
	case EFL_UTIL_ERROR_INVALID_PARAMETER :
		pszErrorMsg = "EFL_UTIL_ERROR_INVALID_PARAMETER  \n";
		break;
	case EFL_UTIL_ERROR_OUT_OF_MEMORY :
		pszErrorMsg = "EFL_UTIL_ERROR_OUT_OF_MEMORY  \n";
		break;
	case EFL_UTIL_ERROR_PERMISSION_DENIED :
		pszErrorMsg = "EFL_UTIL_ERROR_PERMISSION_DENIED  \n";
		break;
	case EFL_UTIL_ERROR_NO_SUCH_DEVICE :
		pszErrorMsg = "EFL_UTIL_ERROR_NO_SUCH_DEVICE  \n";
		break;
	case EFL_UTIL_ERROR_INVALID_OPERATION :
		pszErrorMsg = "EFL_UTIL_ERROR_INVALID_OPERATION  \n";
		break;
	case EFL_UTIL_ERROR_NOT_SUPPORTED :
		pszErrorMsg = "EFL_UTIL_ERROR_NOT_SUPPORTED  \n";
		break;
	case EFL_UTIL_ERROR_NOT_SUPPORTED_WINDOW_TYPE :
		pszErrorMsg = "EFL_UTIL_ERROR_NOT_SUPPORTED_WINDOW_TYPE  \n";
		break;
	case EFL_UTIL_ERROR_SCREENSHOT_INIT_FAIL :
		pszErrorMsg = "EFL_UTIL_ERROR_SCREENSHOT_INIT_FAIL  \n";
		break;
	case EFL_UTIL_ERROR_SCREENSHOT_EXECUTION_FAIL :
		pszErrorMsg = "EFL_UTIL_ERROR_SCREENSHOT_EXECUTION_FAIL  \n";
		break;
	}
	return pszErrorMsg;
}

/**
* @function 		CTs_platform_permission_efl_util_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_efl_util_startup(void)
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
}


/**
* @function 		CTs_platform_permission_efl_util_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_efl_util_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

static void _win_del(void *data, Evas_Object *obj, void *event)
{
    elm_exit();
}

static Evas_Object* _create_normal_win(const char *name)
{
    Evas_Object *eo = NULL;

    eo = elm_win_add(NULL, name, ELM_WIN_BASIC);
    if (eo)
    {
        elm_win_title_set(eo, name);
        elm_win_borderless_set(eo, EINA_TRUE);
        evas_object_smart_callback_add(eo, "delete,request", _win_del, NULL);
        elm_win_indicator_mode_set(eo, ELM_WIN_INDICATOR_SHOW);
    }

    return eo;
}

//& purpose: checking http://tizen.org/privilege/display
//& type: auto
/**
* @testcase			CTc_EflUtil_Privilege_efl_util_set_window_brightness
* @since_tizen		3.0
* @author			SRID(arvin.mittal)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			to verify whether efl_util_set_window_brightness API is
* 					working properly in the case a user sets the brightness to 50
* @apicovered		efl_util_set_window_brightness
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_EflUtil_Privilege_efl_util_set_window_brightness(void)
{
    Evas_Object *win = NULL;
    int nRet = -1;

    win = _create_normal_win("Brightness test");

    nRet = efl_util_set_window_brightness(win, 50);
    PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "efl_util_set_window_brightness", EFLUTILGetError(nRet));	
	
    return 0;
}



