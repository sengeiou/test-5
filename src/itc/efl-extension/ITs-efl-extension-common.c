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
#include "ITs-efl-extension-common.h"

/** @addtogroup itc-efl-extension
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		WinDel
* @description 		Callback function registered by evas_object_smart_callback_add API
* @parameter[IN]    void*, Evas_Object*, void*
* @return 			NA
*/
void WinDel(void *data, Evas_Object *obj, void *event)
{
	elm_exit();
}


/**
* @function 		CreateEvasWindow
* @description 		Creates an Evas window object
* @parameter[IN]    NA
* @return 			0 if successful, otherwise 1
*/
bool CreateEvasWindow(void)
{
	elm_config_accel_preference_set("3d");

	g_pEvasWindow = elm_win_util_standard_add(PACKAGE, PACKAGE);
	CHECK_HANDLE(g_pEvasWindow, "elm_win_util_standard_add");
	elm_win_borderless_set(g_pEvasWindow, EINA_TRUE);
	evas_object_smart_callback_add(g_pEvasWindow, "delete,request",WinDel, NULL);
	elm_win_autodel_set(g_pEvasWindow, EINA_TRUE);
	elm_win_activate(g_pEvasWindow);
	evas_object_show(g_pEvasWindow);

	g_pEvasConformant = elm_conformant_add(g_pEvasWindow);
	CHECK_HANDLE_CLEANUP(g_pEvasConformant, "elm_conformant_add", DeleteEvasWindow());
	evas_object_show(g_pEvasConformant);

	g_pEvasLayout = elm_layout_add(g_pEvasWindow);
	CHECK_HANDLE_CLEANUP(g_pEvasLayout, "elm_layout_add", DeleteEvasWindow());
	evas_object_size_hint_weight_set(g_pEvasLayout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(g_pEvasLayout);

	g_pEvasNaviframe = elm_naviframe_add(g_pEvasWindow);
	CHECK_HANDLE_CLEANUP(g_pEvasNaviframe, "elm_naviframe_add", DeleteEvasWindow());
	evas_object_show(g_pEvasNaviframe);

#ifdef WEARABLE	//Starts WEARABLE
	g_pImageObject = elm_image_add(g_pEvasWindow);
	evas_object_show(g_pImageObject);
#endif  //End WEARABLE

	return 0;
}


#ifdef TV		//Starts TV

/**
* @function 		DeleteEvasWindow
* @description 		Delete Evas window object
* @parameter[IN]    NA
* @return 			NA
*/
void DeleteEvasWindow(void)
{
	if(g_pEvasNaviframe)
	{
		evas_object_del(g_pEvasNaviframe);
		g_pEvasNaviframe = NULL;
	}
	if(g_pEvasLayout)
	{
		evas_object_del(g_pEvasLayout);
		g_pEvasLayout = NULL;
	}
	if(g_pEvasConformant)
	{
		evas_object_del(g_pEvasConformant);
		g_pEvasConformant = NULL;
	}
	if(g_pEvasWindow)
	{
		evas_object_del(g_pEvasWindow);
		g_pEvasWindow = NULL;
	}
}

#endif	//TV	//End TV


#if defined  (MOBILE ) || defined  (TIZENIOT)		//Starts MOBILE OR TIZENIOT


/**
* @function 		DeleteEvasWindow
* @description 		Delete Evas window object
* @parameter[IN]    NA
* @return 			NA
*/
void DeleteEvasWindow(void)
{
	if(g_pFloatingButton)
	{
		evas_object_del(g_pFloatingButton);
		g_pFloatingButton = NULL;
	}
	if(g_pEvasNaviframe)
	{
		evas_object_del(g_pEvasNaviframe);
		g_pEvasNaviframe = NULL;
	}
	if(g_pEvasLayout)
	{
		evas_object_del(g_pEvasLayout);
		g_pEvasLayout = NULL;
	}
	if(g_pEvasConformant)
	{
		evas_object_del(g_pEvasConformant);
		g_pEvasConformant = NULL;
	}
	if(g_pEvasWindow)
	{
		evas_object_del(g_pEvasWindow);
		g_pEvasWindow = NULL;
	}
}
#endif

#if defined  (MOBILE ) || defined  (TIZENIOT)|| defined (TV)

/**
* @function 		CreateFloatingButon
* @description 		Creates an Elm floating button
* @parameter[IN]    NA
* @return 			0 if successful, otherwise 1
*/
bool CreateFloatingButon()
{
	if (CreateEvasWindow() != 0)
	{
		return 1;
	}
	
	Evas_Object *pBtn = NULL;
	
	g_pFloatingButton = eext_floatingbutton_add(g_pEvasLayout);
	CHECK_HANDLE_CLEANUP(g_pFloatingButton, "eext_floatingbutton_add", DeleteEvasWindow());
	elm_object_part_content_set(g_pEvasLayout, "elm.swallow.floatingbutton", g_pFloatingButton);

	pBtn = elm_button_add(g_pFloatingButton);
	CHECK_HANDLE_CLEANUP(pBtn, "elm_button_add", DeleteEvasWindow());
	elm_object_part_content_set(g_pFloatingButton, "button1", pBtn);
	
	return 0;
}


/**
* @function 		EflExtGetFloatingButtonModeType
* @description	 	Maps Floating Button Mode Type enums to string values
* @parameter		eMode : Floating Button Mode Type
* @return 			Floating Button Mode Type string
*/
char* EflExtGetFloatingButtonModeType(Eext_Floatingbutton_Mode eMode)
{
	char *szModeType = "Unknown Mode Type";

	switch ( eMode )
	{
	case EEXT_FLOATINGBUTTON_MODE_DEFAULT:		szModeType = "EEXT_FLOATINGBUTTON_MODE_DEFAULT";		break;
	case EEXT_FLOATINGBUTTON_MODE_BOTH_SIDES:	szModeType = "EEXT_FLOATINGBUTTON_MODE_BOTH_SIDES";		break;
	case EEXT_FLOATINGBUTTON_MODE_LAST:			szModeType = "EEXT_FLOATINGBUTTON_MODE_LAST";			break;
	}

	return szModeType;
}

/**
* @function 		EflExtGetFloatingButtonPosType
* @description	 	Maps Floating Button Pos Type enums to string values
* @parameter		ePos : Floating Button Pos Type
* @return 			Floating Button Pos Type string
*/
char* EflExtGetFloatingButtonPosType(Eext_Floatingbutton_Pos ePos)
{
	char *szPosType = "Unknown Mode Type";

	switch ( ePos )
	{
	case EEXT_FLOATINGBUTTON_LEFT_OUT:		szPosType = "EEXT_FLOATINGBUTTON_LEFT_OUT";		break;
	case EEXT_FLOATINGBUTTON_LEFT:			szPosType = "EEXT_FLOATINGBUTTON_LEFT";			break;
	case EEXT_FLOATINGBUTTON_CENTER:		szPosType = "EEXT_FLOATINGBUTTON_CENTER";		break;
	case EEXT_FLOATINGBUTTON_RIGHT:			szPosType = "EEXT_FLOATINGBUTTON_RIGHT";		break;
	case EEXT_FLOATINGBUTTON_RIGHT_OUT:		szPosType = "EEXT_FLOATINGBUTTON_RIGHT_OUT";	break;
	case EEXT_FLOATINGBUTTON_LAST:			szPosType = "EEXT_FLOATINGBUTTON_LAST";			break;
	}

	return szPosType;
}

#endif  //MOBILE	//End MOBILE


#ifdef WEARABLE	//Starts WEARABLE

/**
* @function 		DeleteEvasWindow
* @description 		Delete Evas window object
* @parameter[IN]    NA
* @return 			NA
*/
void DeleteEvasWindow(void)
{
	if(g_pFloatingButton)
	{
		evas_object_del(g_pFloatingButton);
		g_pFloatingButton = NULL;
	}
	if(g_pEvasNaviframe)
	{
		evas_object_del(g_pEvasNaviframe);
		g_pEvasNaviframe = NULL;
	}
	if(g_pEvasLayout)
	{
		evas_object_del(g_pEvasLayout);
		g_pEvasLayout = NULL;
	}
	if(g_pEvasConformant)
	{
		evas_object_del(g_pEvasConformant);
		g_pEvasConformant = NULL;
	}
	if(g_pEvasWindow)
	{
		evas_object_del(g_pEvasWindow);
		g_pEvasWindow = NULL;
	}
}


/**
* @function 		CreateCircleSurfaceLayout
* @description 		Creates a circle surface
* @parameter		NA
* @return 			Evas_Object if successful, otherwise NULL.
*/
bool CreateCircleSurfaceLayout(void)
{
	int nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Returned Value not correct");

	g_pCircleSurfaceLayout = eext_circle_surface_layout_add(g_pEvasLayout);
	CHECK_HANDLE_CLEANUP(g_pCircleSurfaceLayout, "eext_circle_surface_layout_add", DeleteEvasWindow());

	return 0;
}

/**
* @function 		DeleteCircleSurfaceLayout
* @description 		Delete a circle surface
* @parameter		NA
* @return 			NA
*/
void DeleteCircleSurfaceLayout(void)
{
	if ( g_pCircleSurfaceLayout )
	{
		eext_circle_surface_del(g_pCircleSurfaceLayout);
		g_pCircleSurfaceLayout = NULL;
	}
	DeleteEvasWindow();
}

/**
* @function 		CreateCircle
* @description 		Creates a circle
* @parameter		NA
* @return 			Evas_Object if successful, otherwise NULL.
*/
bool CreateCircle(void)
{
	int nRet = CreateCircleSurfaceLayout();
	PRINT_RESULT(0, nRet, "CreateCircleSurfaceLayout", "Returned Value not correct");

	g_pCircleObject = eext_circle_object_add(g_pEvasLayout, g_pCircleSurfaceLayout);
	CHECK_HANDLE_CLEANUP(g_pCircleObject, "eext_circle_object_add", DeleteCircleSurfaceLayout());

	return 0;
}

/**
* @function 		DeleteCircle
* @description 		Delete a circle
* @parameter		NA
* @return 			NA
*/
void DeleteCircle(void)
{
	if ( g_pCircleObject )
	{
		evas_object_del(g_pCircleObject);
		g_pCircleObject = NULL;
	}
	DeleteCircleSurfaceLayout();
}

/**
* @function 		CreateCircleGenlist
* @description 		Creates a genlist
* @parameter		NA
* @return 			Evas_Object if successful, otherwise NULL.
*/
bool CreateCircleGenlist(void)
{
	int nRet = CreateCircleSurfaceLayout();
	PRINT_RESULT(0, nRet, "CreateCircleSurfaceLayout", "Returned Value not correct");

	Elm_Genlist_Item_Class *pListClass = NULL;
	pListClass = elm_genlist_item_class_new();
	pListClass->item_style = "default";
	pListClass->func.text_get = NULL;
	pListClass->func.content_get = NULL;
	pListClass->func.state_get = NULL;
	pListClass->func.del = NULL;

	g_pGenlist = elm_genlist_add(g_pEvasLayout);
	g_pCircleGenlist = eext_circle_object_genlist_add(g_pGenlist, g_pCircleSurfaceLayout);
	CHECK_HANDLE_CLEANUP(g_pCircleGenlist, "eext_circle_object_genlist_add", DeleteCircleSurfaceLayout());

	g_pEvasItem = elm_genlist_item_append(g_pGenlist, pListClass, NULL, NULL, ELM_GENLIST_ITEM_GROUP, NULL, NULL);
	CHECK_HANDLE_CLEANUP(g_pEvasItem, "elm_genlist_item_append", DeleteEvasWindow());

	return 0;
}

/**
* @function 		DeleteCircleGenlist
* @description 		Delete a circle genlist
* @parameter		NA
* @return 			NA
*/
void DeleteCircleGenlist(void)
{
	if ( g_pEvasItem )
	{
		elm_object_item_del(g_pEvasItem);
		g_pEvasItem = NULL;
	}
	if ( g_pCircleGenlist )
	{
		evas_object_del(g_pCircleGenlist);
		g_pCircleGenlist = NULL;
	}
	if ( g_pGenlist )
	{
		evas_object_del(g_pGenlist);
		g_pGenlist = NULL;
	}
	DeleteCircleSurfaceLayout();
}

/**
* @function 		CreateCircleScroller
* @description 		Creates a scroller
* @parameter		NA
* @return 			Evas_Object if successful, otherwise NULL.
*/
bool CreateCircleScroller(void)
{
	int nRet = CreateCircleSurfaceLayout();
	PRINT_RESULT(0, nRet, "CreateCircleSurfaceLayout", "Returned Value not correct");

	g_pScroller = elm_scroller_add(g_pEvasLayout);
	g_pCircleScroller = eext_circle_object_scroller_add(g_pScroller, g_pCircleSurfaceLayout);
	CHECK_HANDLE_CLEANUP(g_pCircleScroller, "eext_circle_object_scroller_add", DeleteCircleSurfaceLayout());

	return 0;
}

/**
* @function 		DeleteCircleScroller
* @description 		Delete a circle scroller
* @parameter		NA
* @return 			NA
*/
void DeleteCircleScroller(void)
{
	if ( g_pCircleScroller )
	{
		evas_object_del(g_pCircleScroller);
		g_pCircleScroller = NULL;
	}
	if ( g_pScroller )
	{
		evas_object_del(g_pScroller);
		g_pScroller = NULL;
	}
	DeleteCircleSurfaceLayout();
}

/**
* @function 		CreateCircleSlider
* @description 		Creates a slider
* @parameter		NA
* @return 			Evas_Object if successful, otherwise NULL.
*/
bool CreateCircleSlider(void)
{
	int nRet = CreateCircleSurfaceLayout();
	PRINT_RESULT(0, nRet, "CreateCircleSurfaceLayout", "Returned Value not correct");

	g_pCircleSlider = eext_circle_object_slider_add(g_pEvasLayout, g_pCircleSurfaceLayout);
	CHECK_HANDLE_CLEANUP(g_pCircleSlider, "eext_circle_object_slider_add", DeleteCircleSurfaceLayout());

	return 0;
}

/**
* @function 		DeleteCircleSlider
* @description 		Delete a circle slider
* @parameter		NA
* @return 			NA
*/
void DeleteCircleSlider(void)
{
	if ( g_pCircleSlider )
	{
		evas_object_del(g_pCircleSlider);
		g_pCircleSlider = NULL;
	}
	DeleteCircleSurfaceLayout();
}

/**
* @function 		CreateMoreOption
* @description 		Creates an more option
* @parameter		NA
* @return 			Evas_Object if successful, otherwise NULL.
*/
bool CreateMoreOption(void)
{
	int nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Returned Value not correct");

	g_pMoreOption = eext_more_option_add(g_pEvasLayout);
	CHECK_HANDLE_CLEANUP(g_pMoreOption, "eext_more_option_add", DeleteEvasWindow());

	return 0;
}

/**
* @function 		DeleteMoreOption
* @description 		Delete more option
* @parameter		NA
* @return 			NA
*/
void DeleteMoreOption(void)
{
	if ( g_pMoreOption )
	{
		evas_object_del(g_pMoreOption);
		g_pMoreOption = NULL;
	}
	DeleteEvasWindow();
}

/**
* @function 		CreateCircleSelector
* @description 		Creates a selector
* @parameter		NA
* @return 			Evas_Object if successful, otherwise NULL.
*/
bool CreateCircleSelector(void)
{
	int nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Returned Value not correct");

	g_pCircleSelector = eext_rotary_selector_add(g_pEvasLayout);
	CHECK_HANDLE_CLEANUP(g_pCircleSelector, "eext_rotary_selector_add", DeleteCircleSelector());

	g_pEextItem = eext_rotary_selector_item_append(g_pCircleSelector);
	CHECK_HANDLE_CLEANUP(g_pEextItem, "elm_list_item_append", DeleteCircleSelector());

	return 0;
}

/**
* @function 		DeleteCircleSelector
* @description 		Delete a circle selector
* @parameter		NA
* @return 			NA
*/
void DeleteCircleSelector(void)
{
	if ( g_pCircleSelector )
	{
		eext_rotary_selector_items_clear(g_pCircleSelector);
		evas_object_del(g_pCircleSelector);
		g_pCircleSelector = NULL;
	}
	DeleteEvasWindow();
}

/**
* @function 		CreateCircleSpinner
* @description 		Creates a spinner
* @parameter		NA
* @return 			Evas_Object if successful, otherwise NULL.
*/
bool CreateCircleSpinner(void)
{
	int nRet = CreateCircleSurfaceLayout();
	PRINT_RESULT(0, nRet, "CreateCircleSurfaceLayout", "Returned Value not correct");

	g_pSpinner = elm_spinner_add(g_pEvasLayout);
	g_pCircleSpinner = eext_circle_object_spinner_add(g_pSpinner, g_pCircleSurfaceLayout);
	CHECK_HANDLE_CLEANUP(g_pCircleSpinner, "eext_circle_object_spinner_add", DeleteCircleSurfaceLayout());

	return 0;
}

/**
* @function 		DeleteCircleSpinner
* @description 		Delete a circle spinner
* @parameter		NA
* @return 			NA
*/
void DeleteCircleSpinner(void)
{
	if ( g_pCircleSpinner )
	{
		evas_object_del(g_pCircleSpinner);
		g_pCircleSpinner = NULL;
	}
	if ( g_pSpinner )
	{
		evas_object_del(g_pSpinner);
		g_pSpinner = NULL;
	}
	DeleteCircleSurfaceLayout();
}

/**
* @function 		CreateElmWindow
* @description 		Creates an Elm window
* @parameter		NA
* @return 			Evas_Object if successful, otherwise NULL.
*/
Evas_Object* CreateElmWindow(const char *WinName)
{	
	Evas_Object *EvasWin = NULL;

	EvasWin = elm_win_add(NULL, WinName, ELM_WIN_BASIC);
	if (EvasWin != NULL)
	{
		elm_win_title_set(EvasWin, WinName);
		evas_object_smart_callback_add(EvasWin, "delete,request", WinDel, NULL);
	}

	return EvasWin;
}

/*****************************************Commented Code Start*****************************************/
///**
//* @function 		CreateMoreOptionLayout
//* @description 		Creates an more option layout
//* @parameter		NA
//* @return 			Evas_Object if successful, otherwise NULL.
//*/
//bool CreateMoreOptionLayout(void)
//{
//	int nRet = CreateEvasWindow();
//	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Returned Value not correct");
//
//	g_pMoreOptionLayout = eext_more_option_layout_add(g_pEvasLayout);
//	CHECK_HANDLE_CLEANUP(g_pMoreOptionLayout, "eext_more_option_layout_add", DeleteEvasWindow());
//
//	return 0;
//}
//
///**
//* @function 		DeleteMoreOptionLayout
//* @description 		Delete more option layout
//* @parameter		NA
//* @return 			NA
//*/
//void DeleteMoreOptionLayout(void)
//{
//	if ( g_pMoreOptionLayout )
//	{
//		evas_object_del(g_pMoreOptionLayout);
//		g_pMoreOptionLayout = NULL;
//	}
//	DeleteEvasWindow();
//}
/******************************************Commented Code End******************************************/


#endif  //WEARABLE	//End WEARABLE


/** @} */
