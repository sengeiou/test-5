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
#include "ITs-webkit2-common.h"

/** @addtogroup itc-webkit2
*  @ingroup itc
*  @{
*/


/**
* @function 		ITs_webkit_efl_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_settings_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}


/**
* @function 		ITs_webkit_efl_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_settings_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
#if defined(MOBILE) ||  defined(TIZENIOT) || defined(TV) //Starts MOBILE or TIZENIOT or TV
//& type: auto
//& purpose: Requests setting of auto-fit
/**
* @testcase 			ITc_ewk_settings_auto_fitting_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Requests setting of auto-fit
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_settings_auto_fitting_set, ewk_settings_auto_fitting_get
* @passcase				When ewk_settings_auto_fitting_set behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_settings_auto_fitting_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	Eina_Bool bResultGet = EINA_FALSE;
	//Target API
	bResultSet = ewk_settings_auto_fitting_set(pViewSettings, EINA_TRUE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_auto_fitting_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	bResultGet = ewk_settings_auto_fitting_get(pViewSettings);
	if ( bResultGet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_auto_fitting_get returned wrong value; expected = EINA_TRUE, returned = EINA_FALSE\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Returns the auto-fit status
/**
* @testcase 			ITc_ewk_settings_auto_fitting_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns the auto-fit status
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_settings_auto_fitting_set, ewk_settings_auto_fitting_get
* @passcase				When ewk_settings_auto_fitting_get behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_settings_auto_fitting_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	Eina_Bool bResultGet = EINA_FALSE;

	bResultSet = ewk_settings_auto_fitting_set(pViewSettings, EINA_TRUE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_auto_fitting_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	bResultGet = ewk_settings_auto_fitting_get(pViewSettings);
	if ( bResultGet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_auto_fitting_get returned wrong value; expected = EINA_TRUE, returned = EINA_FALSE\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}
#endif  //End MOBILE or TIZENIOT or TV
//& type: auto
//& purpose: Set javascript execution
/**
* @testcase 			ITc_ewk_settings_javascript_enabled_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Set javascript execution
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_settings_javascript_enabled_set, ewk_settings_javascript_enabled_get
* @passcase				When ewk_settings_javascript_enabled_set behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_settings_javascript_enabled_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	Eina_Bool bResultGet = EINA_FALSE;
	//Target API
	bResultSet = ewk_settings_javascript_enabled_set(pViewSettings, EINA_TRUE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_javascript_enabled_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	bResultGet = ewk_settings_javascript_enabled_get(pViewSettings);
	if ( bResultGet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_javascript_enabled_get returned wrong value; expected = EINA_TRUE, returned = EINA_FALSE\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Returns javascript executable status
/**
* @testcase 			ITc_ewk_settings_javascript_enabled_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns javascript executable status
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_settings_javascript_enabled_set, ewk_settings_javascript_enabled_get
* @passcase				When ewk_settings_javascript_enabled_get behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_settings_javascript_enabled_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	Eina_Bool bResultGet = EINA_FALSE;
	bResultSet = ewk_settings_javascript_enabled_set(pViewSettings, EINA_TRUE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_javascript_enabled_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	bResultGet = ewk_settings_javascript_enabled_get(pViewSettings);
	if ( bResultGet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_javascript_enabled_get returned wrong value; expected = EINA_TRUE, returned = EINA_FALSE\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Set auto-loading of images
/**
* @testcase 			ITc_ewk_settings_loads_images_automatically_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Set auto-loading of images
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_settings_loads_images_automatically_set, ewk_settings_loads_images_automatically_get
* @passcase				When ewk_settings_loads_images_automatically_set behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_settings_loads_images_automatically_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	Eina_Bool bResultGet = EINA_FALSE;

	//Target API
	bResultSet = ewk_settings_loads_images_automatically_set(pViewSettings, EINA_TRUE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_loads_images_automatically_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	bResultGet = ewk_settings_loads_images_automatically_get(pViewSettings);
	if ( bResultGet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_loads_images_automatically_get returned wrong value; expected = EINA_TRUE, returned = EINA_FALSE\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Returns auto-loading of images status
/**
* @testcase 			ITc_ewk_settings_loads_images_automatically_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns auto-loading of images status
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_settings_loads_images_automatically_set, ewk_settings_loads_images_automatically_get
* @passcase				When ewk_settings_loads_images_automatically_get behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_settings_loads_images_automatically_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	Eina_Bool bResultGet = EINA_FALSE;
	bResultSet = ewk_settings_loads_images_automatically_set(pViewSettings, EINA_TRUE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_loads_images_automatically_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	bResultGet = ewk_settings_loads_images_automatically_get(pViewSettings);
	if ( bResultGet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_loads_images_automatically_get returned wrong value; expected = EINA_TRUE, returned = EINA_FALSE\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	Webkit_EFLDestroyWebKitView();
	return 0;
}


//& type: auto
//& purpose: Sets default text encoding name
/**
* @testcase 			ITc_ewk_settings_default_text_encoding_name_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Sets default text encoding name
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_settings_default_text_encoding_name_set, ewk_settings_default_text_encoding_name_get
* @passcase				When ewk_settings_default_text_encoding_name_set behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_settings_default_text_encoding_name_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	const char* pValue = NULL;

	//Target API
	bResultSet = ewk_settings_default_text_encoding_name_set(pViewSettings, SET_DEFAULT_ENCODING);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_default_text_encoding_name_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	pValue = ewk_settings_default_text_encoding_name_get(pViewSettings);
	if ( pValue == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_default_text_encoding_name_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( 0 != strcmp(SET_DEFAULT_ENCODING, pValue) )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_default_text_encoding_name_get returned wrong value; expected = %s, returned = %s\\n", __LINE__, API_NAMESPACE, SET_DEFAULT_ENCODING, pValue);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Gets default text encoding name
/**
* @testcase 			ITc_ewk_settings_default_text_encoding_name_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets default text encoding name
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_settings_default_text_encoding_name_set, ewk_settings_default_text_encoding_name_get
* @passcase				When ewk_settings_default_text_encoding_name_get behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_settings_default_text_encoding_name_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	const char* pValue = NULL;
	bResultSet = ewk_settings_default_text_encoding_name_set(pViewSettings, SET_DEFAULT_ENCODING);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_default_text_encoding_name_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	pValue = ewk_settings_default_text_encoding_name_get(pViewSettings);
	if ( pValue == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_default_text_encoding_name_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( 0 != strcmp(SET_DEFAULT_ENCODING, pValue) )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_default_text_encoding_name_get returned wrong value; expected = %s, returned = %s\\n", __LINE__, API_NAMESPACE, SET_DEFAULT_ENCODING, pValue);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Sets default font size
/**
* @testcase 			ITc_ewk_settings_default_font_size_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Sets default font size
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_settings_default_font_size_set, ewk_settings_default_font_size_get
* @passcase				When ewk_settings_default_font_size_set behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_settings_default_font_size_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	int nValue = 0;
	//Target API
	bResultSet = ewk_settings_default_font_size_set(pViewSettings, SET_DEFAULT_FONT_SIZE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_default_font_size_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	nValue = ewk_settings_default_font_size_get(pViewSettings);
	if ( SET_DEFAULT_FONT_SIZE != nValue )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_default_font_size_get returned wrong value; expected = %d, returned = %d\\n", __LINE__, API_NAMESPACE, SET_DEFAULT_FONT_SIZE, nValue);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Gets default font size
/**
* @testcase 			ITc_ewk_settings_default_font_size_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets default font size
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_settings_default_font_size_set, ewk_settings_default_font_size_get
* @passcase				When ewk_settings_default_font_size_get behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_settings_default_font_size_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	int nValue = 0;

	bResultSet = ewk_settings_default_font_size_set(pViewSettings, SET_DEFAULT_FONT_SIZE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_default_font_size_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	nValue = ewk_settings_default_font_size_get(pViewSettings);
	if ( SET_DEFAULT_FONT_SIZE != nValue )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_default_font_size_get returned wrong value; expected = %d, returned = %d\\n", __LINE__, API_NAMESPACE, SET_DEFAULT_FONT_SIZE, nValue);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Set Scripts ability to open windows
/**
* @testcase 			ITc_ewk_settings_scripts_can_open_windows_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Set Scripts ability to open windows
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_settings_scripts_can_open_windows_set, ewk_settings_scripts_can_open_windows_get
* @passcase				When ewk_settings_scripts_can_open_windows_set behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_settings_scripts_can_open_windows_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	Eina_Bool bResultGet = EINA_FALSE;

	//Target API
	bResultSet = ewk_settings_scripts_can_open_windows_set(pViewSettings, EINA_TRUE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_scripts_can_open_windows_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	bResultGet = ewk_settings_scripts_can_open_windows_get(pViewSettings);
	if ( bResultGet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_scripts_can_open_windows_get returned wrong value; expected = EINA_TRUE, returned = EINA_FALSE\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Get Scripts ability to open windows
/**
* @testcase 			ITc_ewk_settings_scripts_can_open_windows_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Get Scripts ability to open windows
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_settings_scripts_can_open_windows_set, ewk_settings_scripts_can_open_windows_get
* @passcase				When ewk_settings_scripts_can_open_windows_get behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_settings_scripts_can_open_windows_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	Eina_Bool bResultGet = EINA_FALSE;

	bResultSet = ewk_settings_scripts_can_open_windows_set(pViewSettings, EINA_TRUE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_scripts_can_open_windows_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	bResultGet = ewk_settings_scripts_can_open_windows_get(pViewSettings);
	if ( bResultGet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_scripts_can_open_windows_get returned wrong value; expected = EINA_TRUE, returned = EINA_FALSE\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}
#if defined(MOBILE) ||  defined(TIZENIOT) || defined(TV)		//Starts MOBILE or TIZENIOT
//& purpose: Requests enable/disable form candidate data for autofill
//& type: auto
/**
* @testcase 			ITc_ewk_settings_form_candidate_data_enabled_set_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Requests enable/disable form candidate data for autofill
* @scenario				ewk_view_settings_get\n
*						ewk_settings_form_candidate_data_enabled_set
* @apicovered			ewk_view_settings_get, ewk_settings_form_candidate_data_enabled_set
* @passcase				When ewk_settings_form_candidate_data_enabled_set is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_settings_form_candidate_data_enabled_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	//Target API
	bResultSet = ewk_settings_form_candidate_data_enabled_set(pViewSettings, EINA_TRUE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_form_candidate_data_enabled_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}


//& purpose: Enables/disables form autofill profile feature
//& type: auto
/**
* @testcase 			ITc_ewk_settings_form_profile_data_enabled_set_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Enables/disables form autofill profile feature
* @scenario				ewk_view_settings_get\n
*						ewk_settings_form_profile_data_enabled_set
* @apicovered			ewk_view_settings_get, ewk_settings_form_profile_data_enabled_set
* @passcase				When ewk_settings_form_profile_data_enabled_set is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_settings_form_profile_data_enabled_set_p(void)
{

	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	//Target API
	bResultSet = ewk_settings_form_profile_data_enabled_set(pViewSettings, EINA_TRUE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] eewk_settings_form_profile_data_enabled_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;

}

//& purpose: Requests enable/disable password form autofill
//& type: auto
/**
* @testcase 			ITc_ewk_settings_autofill_password_form_enabled_set_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Requests enable/disable password form autofill
* @scenario				ewk_view_settings_get\n
*						ewk_settings_autofill_password_form_enabled_set
* @apicovered			ewk_view_settings_get, ewk_settings_autofill_password_form_enabled_set
* @passcase				When ewk_settings_autofill_password_form_enabled_set is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_settings_autofill_password_form_enabled_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Settings* pViewSettings = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pViewSettings == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get View Settings from ewk_view_settings_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	//Target API
	bResultSet = ewk_settings_autofill_password_form_enabled_set(pViewSettings, EINA_TRUE);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_settings_autofill_password_form_enabled_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}
#endif  //End MOBILE or TIZENIOT
/** @} */
/** @} */
