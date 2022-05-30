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
#include "ITs-efl-extension-common.h"

//& set: EflExt

/** @addtogroup itc-efl-extension-testcases
*  @brief               Integration testcases for module efl-extension
*  @ingroup     itc-efl-extension
*  @{
*/

#if defined  (MOBILE ) || defined  (TIZENIOT) || defined (TV)          //Starts MOBILE
/**
 * @function            ITs_efl_ext_startup
 * @description         Called before each test
 * @parameter           NA
 * @return                      NA
 */
void ITs_efl_ext_startup(void)
{
        struct stat stBuff;
        if ( stat(ERR_LOG, &stBuff) == 0 )
        {
                remove(ERR_LOG);
        }
        return;
}


/**
 * @function            ITs_efl_ext_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return                      NA
 */
void ITs_efl_ext_cleanup(void)
{
        return;
}

#endif

#ifdef TV		//Starts TV
/** @addtogroup itc-efl-extension-testcases
*  @brief 		Integration testcases for module efl-extension
*  @ingroup 	itc-efl-extension
*  @{
*/

/**
* @testcase 			ITc_eext_win_keygrab_set_unset_p
* @since_tizen			2.4
* @author            	SRID(shobhit.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Test eext_win_keygrab_set, eext_win_keygrab_unset
* @scenario				Call eext_win_keygrab_set, eext_win_keygrab_unset
* @apicovered			eext_win_keygrab_set, eext_win_keygrab_unset
* @passcase				When eext_win_keygrab_set, eext_win_keygrab_unset is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_win_keygrab_set, eext_win_keygrab_unset
//& type: auto
int ITc_eext_win_keygrab_set_unset_p(void)
{
	START_TEST;

	Eina_Bool bRet;

	int nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Create Window failed");

	bRet = eext_win_keygrab_set(g_pEvasWindow, KEY_POWEROFF);
	if (!bRet)
	{
		FPRINTF("[Line : %d][%s] eext_win_keygrab_set failed, Returned false.\\n", __LINE__, API_NAMESPACE);
		DeleteEvasWindow();
		return 1;
	}

	bRet = eext_win_keygrab_unset(g_pEvasWindow, KEY_POWEROFF);
	if (!bRet)
	{
		FPRINTF("[Line : %d][%s] eext_win_keygrab_unset failed, Returned false.\\n", __LINE__, API_NAMESPACE);
		DeleteEvasWindow();
		return 1;
	}

	DeleteEvasWindow();
	return 0;
}

#endif  	//End TV

#if defined  (MOBILE ) || defined  (TIZENIOT) || defined (TV)
/**
* @testcase 			ITc_eext_floatingbutton_movement_block_set_get_p
* @since_tizen			2.4
* @author            	SRID(shobhit.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Test eext_floatingbutton_movement_block_set, eext_floatingbutton_movement_block_get
* @scenario				Call eext_floatingbutton_movement_block_set, eext_floatingbutton_movement_block_get
* @apicovered			eext_floatingbutton_movement_block_set, eext_floatingbutton_movement_block_get
* @passcase				When eext_floatingbutton_movement_block_set, eext_floatingbutton_movement_block_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_floatingbutton_movement_block_set, eext_floatingbutton_movement_block_get
//& type: auto
int ITc_eext_floatingbutton_movement_block_set_get_p(void)
{
	START_TEST;
	Eina_Bool setBlock = true;
	Eina_Bool getBlock;

	int nRet = CreateFloatingButon();
	PRINT_RESULT(0, nRet, "CreateFloatingButon", "Returned Value not correct");

	eext_floatingbutton_movement_block_set(g_pFloatingButton, setBlock);

	getBlock = eext_floatingbutton_movement_block_get(g_pFloatingButton);
	if (setBlock != getBlock)
	{
		FPRINTF("[Line : %d][%s] set and get position mismatch, Set is: %d Get is %d false.\\n", __LINE__, API_NAMESPACE, setBlock, getBlock);
		DeleteEvasWindow();
		return 1;
	}

	DeleteEvasWindow();
	return 0;
}


#if 0	//APIs not available in repo
/**
* @testcase 			ITc_eext_win_keygrab_set_unset_p
* @since_tizen			2.4
* @author            	SRID(shobhit.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Test eext_win_keygrab_set, eext_win_keygrab_unset
* @scenario				Call eext_win_keygrab_set, eext_win_keygrab_unset
* @apicovered			eext_win_keygrab_set, eext_win_keygrab_unset
* @passcase				When eext_win_keygrab_set, eext_win_keygrab_unset is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_win_keygrab_set, eext_win_keygrab_unset
//& type: auto
//int ITc_eext_win_keygrab_set_unset_p(void)
{
	START_TEST;

	Eina_Bool bRet;

	int nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Create Window failed");

	bRet = eext_win_keygrab_set(g_pEvasWindow, KEY_VOLUMEUP);
	if (!bRet)
	{
		FPRINTF("[Line : %d][%s] eext_win_keygrab_set failed, Returned false.\\n", __LINE__, API_NAMESPACE);
		DeleteEvasWindow();
		return 1;
	}

	bRet = eext_win_keygrab_unset(g_pEvasWindow, KEY_VOLUMEUP);
	if (!bRet)
	{
		FPRINTF("[Line : %d][%s] eext_win_keygrab_unset failed, Returned false.\\n", __LINE__, API_NAMESPACE);
		DeleteEvasWindow();
		return 1;
	}

	DeleteEvasWindow();
	return 0;
}

#endif	//APIs not available in repo


/**
* @testcase 			ITc_eext_floatingbutton_mode_set_get_p
* @since_tizen			2.4
* @author            	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Test eext_floatingbutton_mode_set, eext_floatingbutton_mode_get
* @scenario				Call eext_floatingbutton_mode_set, eext_floatingbutton_mode_get
* @apicovered			eext_floatingbutton_mode_set, eext_floatingbutton_mode_get
* @passcase				When eext_floatingbutton_mode_set, eext_floatingbutton_mode_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: 
//& type: auto
int ITc_eext_floatingbutton_mode_set_get_p(void)
{
	START_TEST;
	Eext_Floatingbutton_Mode ret = EEXT_FLOATINGBUTTON_MODE_DEFAULT;

	int nRet = CreateFloatingButon();
	PRINT_RESULT(0, nRet, "CreateFloatingButon", "Returned Value not correct");

	Eext_Floatingbutton_Mode FloatingButtonModeType[] = { EEXT_FLOATINGBUTTON_MODE_DEFAULT, 
														  EEXT_FLOATINGBUTTON_MODE_BOTH_SIDES}; 

	int nEnumSize = sizeof(FloatingButtonModeType) / sizeof(FloatingButtonModeType[0]);
	int nEnumCounter = 0;

	for(nEnumCounter=0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		eext_floatingbutton_mode_set(g_pFloatingButton, FloatingButtonModeType[nEnumCounter]);
		
		ret = eext_floatingbutton_mode_get(g_pFloatingButton);

		if(ret != FloatingButtonModeType[nEnumCounter])
		{
			FPRINTF("[Line : %d][%s] eext_floatingbutton_mode_get failed due to mismatch in set and get values\\n", __LINE__, API_NAMESPACE);
			FPRINTF("[Line : %d][%s] set mode = %s and get mode is %s \\n", __LINE__, API_NAMESPACE, EflExtGetFloatingButtonModeType(FloatingButtonModeType[nEnumCounter]), EflExtGetFloatingButtonModeType(ret));
			DeleteEvasWindow();
			return 1;
		}
	}

	DeleteEvasWindow();
	return 0;
}


/**
* @testcase 			ITc_eext_floatingbutton_pos_bring_in_p
* @since_tizen			2.4
* @author            	SRID(pushpa.singh)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Test eext_floatingbutton_pos_bring_in
* @scenario				set eext_floatingbutton_pos_bring_in for each condition.
* @apicovered			eext_floatingbutton_pos_bring_in
* @passcase				When eext_floatingbutton_pos_bring_in returns true.
* @failcase				When eext_floatingbutton_pos_bring_in returns false.
* @precondition			None
* @postcondition		None
*/
//& purpose: 
//& type: auto
int ITc_eext_floatingbutton_pos_bring_in_p(void)
{
	START_TEST;
	Eina_Bool bRet;

	int nRet = CreateFloatingButon();
	PRINT_RESULT(0, nRet, "CreateFloatingButon", "Returned Value not correct");

	Eext_Floatingbutton_Pos FloatingButtonPosType[] = { EEXT_FLOATINGBUTTON_LEFT_OUT,
														EEXT_FLOATINGBUTTON_LEFT,
														EEXT_FLOATINGBUTTON_CENTER,
														EEXT_FLOATINGBUTTON_RIGHT,
														EEXT_FLOATINGBUTTON_RIGHT_OUT};

	int nEnumSize = sizeof(FloatingButtonPosType) / sizeof(FloatingButtonPosType[0]);
	int nEnumCounter = 0;

	for(nEnumCounter=0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		bRet = eext_floatingbutton_pos_bring_in(g_pFloatingButton, FloatingButtonPosType[nEnumCounter]);
		if (!bRet)
		{
			FPRINTF("[Line : %d][%s] eext_floatingbutton_pos_bring_in failed, Returned false for position = %s \\n", __LINE__, API_NAMESPACE, 
					EflExtGetFloatingButtonPosType(FloatingButtonPosType[nEnumCounter]));
			DeleteEvasWindow();
			return 1;
		}
	}

	DeleteEvasWindow();
	return 0;
}

#endif  //MOBILE OR TIZENIOT

#ifdef WEARABLE	//Starts WEARABLE

/*********************************************************************CallBack Functions Start*********************************************************************/

/**
 * @function 		RotaryEventCallBack
 * @description	 	Called when rotary event has occurred
 * @parameter		void *data, Evas_Object *obj, Eext_Rotary_Event_Info *info
 * @return 			NA
 */
Eina_Bool RotaryEventCallBack(void *data, Evas_Object *obj, Eext_Rotary_Event_Info *info)
{
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "RotaryEventCallBack");
	return EINA_TRUE;
}

/**
 * @function 		RotaryHandlerCallBack
 * @description	 	Called when rotary handler is used
 * @parameter		void *data, Eext_Rotary_Event_Info *info
 * @return 			NA
 */
Eina_Bool RotaryHandlerCallBack(void *data, Eext_Rotary_Event_Info *info)
{
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "RotaryHandlerCallBack");
	return EINA_TRUE;
}
/**
 * @function 		WinDelete
 * @description	 	Called when delete of window is called for new circle scroller object
 * @parameter		void *data, Evas_Object *obj, void *event
 * @return 			NA
 */
static void WinDelete(void *data, Evas_Object *obj, void *event)
{
	elm_exit();
}
/**
 * @function 		CreateWin
 * @description	 	Called to create window for new circle scroller object
 * @parameter		const char *name
 * @return 			NA
 */
static Evas_Object* CreateWin(const char *name)
{
	Evas_Object *obj = NULL;

	obj = elm_win_add(NULL, name, ELM_WIN_BASIC);
	if (obj)
	{
		elm_win_title_set(obj, name);
		evas_object_smart_callback_add(obj, "delete,request",WinDelete, NULL);
	}

	return obj;
}
/**********************************************************************CallBack Functions End**********************************************************************/

/**
 * @function 		ITs_efl_ext_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_efl_ext_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_EflExt_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bEflExtCreation = true;
}


/**
 * @function 		ITs_efl_ext_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_efl_ext_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_EflExt_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/** @addtogroup itc-efl-extension-testcases
*  @brief 		Integration testcases for module efl-extension
*  @ingroup 	itc-efl-extension
*  @{
*/

#if 0	//APIs not available in repo
/**
* @testcase 			ITc_eext_win_keygrab_set_unset_p
* @since_tizen			2.4
* @author            	SRID(shobhit.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Test eext_win_keygrab_set, eext_win_keygrab_unset
* @scenario				Call eext_win_keygrab_set, eext_win_keygrab_unset
* @apicovered			eext_win_keygrab_set, eext_win_keygrab_unset
* @passcase				When eext_win_keygrab_set, eext_win_keygrab_unset is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_win_keygrab_set, eext_win_keygrab_unset
//& type: auto
//int ITc_eext_win_keygrab_set_unset_p(void)
{
	START_TEST;

	Eina_Bool bRet;

	int nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Create Window failed");

	bRet = eext_win_keygrab_set(g_pEvasWindow, KEY_VOLUMEUP);
	if (!bRet)
	{
		FPRINTF("[Line : %d][%s] eext_win_keygrab_set failed, Returned false.\\n", __LINE__, API_NAMESPACE);
		DeleteEvasWindow();
		return 1;
	}

	bRet = eext_win_keygrab_unset(g_pEvasWindow, KEY_VOLUMEUP);
	if (!bRet)
	{
		FPRINTF("[Line : %d][%s] eext_win_keygrab_unset failed, Returned false.\\n", __LINE__, API_NAMESPACE);
		DeleteEvasWindow();
		return 1;
	}

	DeleteEvasWindow();
	return 0;
}
#endif	//APIs not available in repo

/**
* @testcase 			ITc_eext_circle_object_scroller_add_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_scroller_add
* @scenario				Call eext_circle_object_scroller_add
* @apicovered			eext_circle_object_scroller_add
* @passcase				When eext_circle_object_scroller_add is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_scroller_add
//& type: auto
int ITc_eext_circle_object_scroller_add_p(void)
{
	START_TEST;

	int nRet = 0;
	Evas_Object *pScroller = NULL;
	Evas_Object *pCircle = NULL;

	nRet = CreateCircleSurfaceLayout();
	PRINT_RESULT(0, nRet, "CreateCircleSurfaceLayout", "Returned Value not correct");

	pScroller = elm_scroller_add(g_pEvasLayout);
	pCircle = eext_circle_object_scroller_add(pScroller, g_pCircleSurfaceLayout);
	CHECK_HANDLE_CLEANUP(pCircle, "eext_circle_object_scroller_add", DeleteCircleSurfaceLayout());

	evas_object_del(pCircle);
	evas_object_del(pScroller);
	DeleteCircleSurfaceLayout();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_scroller_policy_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_scroller_policy_set, eext_circle_object_scroller_policy_get
* @scenario				Call eext_circle_object_scroller_policy_set, eext_circle_object_scroller_policy_get
* @apicovered			eext_circle_object_scroller_policy_set, eext_circle_object_scroller_policy_get
* @passcase				When eext_circle_object_scroller_policy_set and eext_circle_object_scroller_policy_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_scroller_policy_set, eext_circle_object_scroller_policy_get
//& type: auto
int ITc_eext_circle_object_scroller_policy_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Elm_Scroller_Policy eVerticalPolicy = ELM_SCROLLER_POLICY_OFF, eHorizontalPolicy = ELM_SCROLLER_POLICY_OFF;

	nRet = CreateCircleScroller();
	PRINT_RESULT(0, nRet, "CreateCircleScroller", "Returned Value not correct");

	eext_circle_object_scroller_policy_set(g_pCircleScroller, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_ON);

	eext_circle_object_scroller_policy_get(g_pCircleScroller, &eHorizontalPolicy, &eVerticalPolicy);
	PRINT_RESULT_CLEANUP(ELM_SCROLLER_POLICY_ON, eHorizontalPolicy, "eext_circle_object_scroller_policy_get", "Returned value not same as the value set previously", DeleteCircleScroller());
	PRINT_RESULT_CLEANUP(ELM_SCROLLER_POLICY_ON, eVerticalPolicy, "eext_circle_object_scroller_policy_get", "Returned value not same as the value set previously", DeleteCircleScroller());

	DeleteCircleScroller();

	return 0;
}

/**
* @testcase 			ITc_eext_rotary_object_event_callback_add_del_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_object_event_callback_add, eext_rotary_object_event_callback_del
* @scenario				Call eext_rotary_object_event_callback_add, eext_rotary_object_event_callback_del
* @apicovered			eext_rotary_object_event_callback_add, eext_rotary_object_event_callback_del
* @passcase				When eext_rotary_object_event_callback_add and eext_rotary_object_event_callback_del is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_object_event_callback_add, eext_rotary_object_event_callback_del
//& type: auto
int ITc_eext_rotary_object_event_callback_add_del_p(void)
{
	START_TEST;

	int nRet = 0;
	Eina_Bool bValue = EINA_FALSE;

	nRet = CreateCircle();
	PRINT_RESULT(0, nRet, "CreateCircle", "Returned Value not correct");

	bValue = eext_rotary_object_event_callback_add(g_pCircleObject, RotaryEventCallBack, NULL);
	PRINT_RESULT_CLEANUP(EINA_TRUE, bValue, "eext_rotary_object_event_callback_add", "Returned value not correct", DeleteCircle());

	eext_rotary_object_event_callback_del(g_pCircleObject, RotaryEventCallBack);
	DeleteCircle();

	return 0;
}

/**
* @testcase 			ITc_eext_rotary_object_event_callback_priority_add_del_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_object_event_callback_priority_add, eext_rotary_object_event_callback_del
* @scenario				Call eext_rotary_object_event_callback_priority_add, eext_rotary_object_event_callback_del
* @apicovered			eext_rotary_object_event_callback_priority_add, eext_rotary_object_event_callback_del
* @passcase				When eext_rotary_object_event_callback_priority_add and eext_rotary_object_event_callback_del is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_object_event_callback_priority_add, eext_rotary_object_event_callback_del
//& type: auto
int ITc_eext_rotary_object_event_callback_priority_add_del_p(void)
{
	START_TEST;

	int nRet = 0;
	Eina_Bool bValue = EINA_FALSE;

	nRet = CreateCircle();
	PRINT_RESULT(0, nRet, "CreateCircle", "Returned Value not correct");

	bValue = eext_rotary_object_event_callback_priority_add(g_pCircleObject, EEXT_CALLBACK_PRIORITY_BEFORE, RotaryEventCallBack, NULL);
	PRINT_RESULT_CLEANUP(EINA_TRUE, bValue, "eext_rotary_object_event_callback_priority_add", "Returned value not correct", DeleteCircle());

	eext_rotary_object_event_callback_del(g_pCircleObject, RotaryEventCallBack);
	DeleteCircle();

	return 0;
}

/**
* @testcase 			ITc_eext_rotary_event_handler_add_del_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_event_handler_add, eext_rotary_event_handler_del
* @scenario				Call eext_rotary_event_handler_add, eext_rotary_event_handler_del
* @apicovered			eext_rotary_event_handler_add, eext_rotary_event_handler_del
* @passcase				When eext_rotary_event_handler_add and eext_rotary_event_handler_del is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_event_handler_add, eext_rotary_event_handler_del
//& type: auto
int ITc_eext_rotary_event_handler_add_del_p(void)
{
	START_TEST;
	Eina_Bool bValue = EINA_FALSE;

	bValue = eext_rotary_event_handler_add(RotaryHandlerCallBack, NULL);
	PRINT_RESULT(EINA_TRUE, bValue, "eext_rotary_event_handler_add", "Returned value not correct");

	eext_rotary_event_handler_del(RotaryHandlerCallBack);

	return 0;
}

/**
* @testcase 			ITc_eext_rotary_object_event_activated_set_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_object_event_activated_set
* @scenario				Call eext_rotary_object_event_activated_set
* @apicovered			eext_rotary_object_event_activated_set
* @passcase				When eext_rotary_object_event_activated_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_object_event_activated_set
//& type: auto
int ITc_eext_rotary_object_event_activated_set_p(void)
{
	START_TEST;

	int nRet = 0;
	Eina_Bool bValue = EINA_FALSE;

	nRet = CreateCircle();
	PRINT_RESULT(0, nRet, "CreateCircle", "Returned Value not correct");

	bValue = eext_rotary_object_event_callback_priority_add(g_pCircleObject, EEXT_CALLBACK_PRIORITY_BEFORE, RotaryEventCallBack, NULL);
	PRINT_RESULT_CLEANUP(EINA_TRUE, bValue, "eext_rotary_object_event_callback_priority_add", "Returned value not correct", DeleteCircle());

	eext_rotary_object_event_activated_set(g_pCircleObject, EINA_TRUE);

	eext_rotary_object_event_callback_del(g_pCircleObject, RotaryEventCallBack);
	DeleteCircle();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_line_width_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_line_width_set, eext_circle_object_line_width_get
* @scenario				Call eext_circle_object_line_width_set, eext_circle_object_line_width_get
* @apicovered			eext_circle_object_line_width_set, eext_circle_object_line_width_get
* @passcase				When eext_circle_object_line_width_set and eext_circle_object_line_width_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_line_width_set, eext_circle_object_line_width_get
//& type: auto
int ITc_eext_circle_object_line_width_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	int nValue = 0;

	nRet = CreateCircle();
	PRINT_RESULT(0, nRet, "CreateCircle", "Returned Value not correct");

	eext_circle_object_line_width_set(g_pCircleObject, 10);

	nValue = eext_circle_object_line_width_get(g_pCircleObject);
	PRINT_RESULT_CLEANUP(10, nValue, "eext_circle_object_line_width_get", "Returned value not same as the value set previously", DeleteCircle());

	DeleteCircle();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_angle_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_angle_set, eext_circle_object_angle_get
* @scenario				Call eext_circle_object_angle_set, eext_circle_object_angle_get
* @apicovered			eext_circle_object_angle_set, eext_circle_object_angle_get
* @passcase				When eext_circle_object_angle_set and eext_circle_object_angle_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_angle_set, eext_circle_object_angle_get
//& type: auto
int ITc_eext_circle_object_angle_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	int nValue = 0;

	nRet = CreateCircle();
	PRINT_RESULT(0, nRet, "CreateCircle", "Returned Value not correct");

	eext_circle_object_angle_set(g_pCircleObject, 10);

	nValue = eext_circle_object_angle_get(g_pCircleObject);
	PRINT_RESULT_CLEANUP(10, nValue, "eext_circle_object_angle_get", "Returned value not same as the value set previously", DeleteCircle());

	DeleteCircle();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_angle_offset_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_angle_offset_set, eext_circle_object_angle_offset_get
* @scenario				Call eext_circle_object_angle_offset_set, eext_circle_object_angle_offset_get
* @apicovered			eext_circle_object_angle_offset_set, eext_circle_object_angle_offset_get
* @passcase				When eext_circle_object_angle_offset_set and eext_circle_object_angle_offset_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_angle_offset_set, eext_circle_object_angle_offset_get
//& type: auto
int ITc_eext_circle_object_angle_offset_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	int nValue = 0;

	nRet = CreateCircle();
	PRINT_RESULT(0, nRet, "CreateCircle", "Returned Value not correct");

	eext_circle_object_angle_offset_set(g_pCircleObject, 10);

	nValue = eext_circle_object_angle_offset_get(g_pCircleObject);
	PRINT_RESULT_CLEANUP(10, nValue, "eext_circle_object_angle_offset_get", "Returned value not same as the value set previously", DeleteCircle());

	DeleteCircle();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_angle_min_max_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_angle_min_max_set, eext_circle_object_angle_min_max_get
* @scenario				Call eext_circle_object_angle_min_max_set, eext_circle_object_angle_min_max_get
* @apicovered			eext_circle_object_angle_min_max_set, eext_circle_object_angle_min_max_get
* @passcase				When eext_circle_object_angle_min_max_set and eext_circle_object_angle_min_max_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_angle_min_max_set, eext_circle_object_angle_min_max_get
//& type: auto
int ITc_eext_circle_object_angle_min_max_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	double dMinValue = 0;
	double dMaxValue = 0;

	nRet = CreateCircle();
	PRINT_RESULT(0, nRet, "CreateCircle", "Returned Value not correct");

	eext_circle_object_angle_min_max_set(g_pCircleObject, 10, 100);

	eext_circle_object_angle_min_max_get(g_pCircleObject, &dMinValue, &dMaxValue);
	PRINT_RESULT_CLEANUP(10, (int)dMinValue, "eext_circle_object_angle_min_max_get", "Returned value not same as the value set previously", DeleteCircle());
	PRINT_RESULT_CLEANUP(100, (int)dMaxValue, "eext_circle_object_angle_min_max_get", "Returned value not same as the value set previously", DeleteCircle());

	DeleteCircle();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_value_min_max_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_value_min_max_set, eext_circle_object_value_min_max_get
* @scenario				Call eext_circle_object_value_min_max_set, eext_circle_object_value_min_max_get
* @apicovered			eext_circle_object_value_min_max_set, eext_circle_object_value_min_max_get
* @passcase				When eext_circle_object_value_min_max_set and eext_circle_object_value_min_max_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_value_min_max_set, eext_circle_object_value_min_max_get
//& type: auto
int ITc_eext_circle_object_value_min_max_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	double dMinValue = 0;
	double dMaxValue = 0;

	nRet = CreateCircle();
	PRINT_RESULT(0, nRet, "CreateCircle", "Returned Value not correct");

	eext_circle_object_value_min_max_set(g_pCircleObject, 10, 100);

	eext_circle_object_value_min_max_get(g_pCircleObject, &dMinValue, &dMaxValue);
	PRINT_RESULT_CLEANUP(10, (int)dMinValue, "eext_circle_object_value_min_max_get", "Returned value not same as the value set previously", DeleteCircle());
	PRINT_RESULT_CLEANUP(100, (int)dMaxValue, "eext_circle_object_value_min_max_get", "Returned value not same as the value set previously", DeleteCircle());

	DeleteCircle();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_value_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_value_set, eext_circle_object_value_get
* @scenario				Call eext_circle_object_value_set, eext_circle_object_value_get
* @apicovered			eext_circle_object_value_set, eext_circle_object_value_get
* @passcase				When eext_circle_object_value_set and eext_circle_object_value_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_value_set, eext_circle_object_value_get
//& type: auto
int ITc_eext_circle_object_value_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	int nValue = 0;

	nRet = CreateCircle();
	PRINT_RESULT(0, nRet, "CreateCircle", "Returned Value not correct");

	eext_circle_object_value_set(g_pCircleObject, 10);

	nValue = eext_circle_object_value_get(g_pCircleObject);
	PRINT_RESULT_CLEANUP(10, nValue, "eext_circle_object_value_get", "Returned value not same as the value set previously", DeleteCircle());

	DeleteCircle();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_color_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_color_set, eext_circle_object_color_get
* @scenario				Call eext_circle_object_color_set, eext_circle_object_color_get
* @apicovered			eext_circle_object_color_set, eext_circle_object_color_get
* @passcase				When eext_circle_object_color_set and eext_circle_object_color_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_color_set, eext_circle_object_color_get
//& type: auto
int ITc_eext_circle_object_color_set_get_p(void)
{
	START_TEST;

	int nRet = -1;
	int nColourR = 1;
	int nColourG = 1;
	int nColourB = 1;
	int nColourA = 1;

	nRet = CreateCircle();
	PRINT_RESULT(0, nRet, "CreateCircle", "Returned Value not correct");

	eext_circle_object_color_set(g_pCircleObject, 0, 0, 0, 0);

	eext_circle_object_color_get(g_pCircleObject, &nColourR, &nColourG, &nColourB, &nColourA);
	PRINT_RESULT_CLEANUP(0, nColourR+nColourG+nColourB+nColourA, "eext_circle_object_color_get", "Returned colour not same as the colour set previously", DeleteCircle());

	DeleteCircle();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_radius_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_radius_set, eext_circle_object_radius_get
* @scenario				Call eext_circle_object_radius_set, eext_circle_object_radius_get
* @apicovered			eext_circle_object_radius_set, eext_circle_object_radius_get
* @passcase				When eext_circle_object_radius_set and eext_circle_object_radius_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_radius_set, eext_circle_object_radius_get
//& type: auto
int ITc_eext_circle_object_radius_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	int nRadius = 0;

	nRet = CreateCircle();
	PRINT_RESULT(0, nRet, "CreateCircle", "Returned Value not correct");

	eext_circle_object_radius_set(g_pCircleObject, 10);

	nRadius = eext_circle_object_radius_get(g_pCircleObject);
	PRINT_RESULT_CLEANUP(10, nRadius, "eext_circle_object_radius_get", "Returned radius not same as the radius set previously", DeleteCircle());

	DeleteCircle();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_disabled_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_disabled_set, eext_circle_object_disabled_get
* @scenario				Call eext_circle_object_disabled_set, eext_circle_object_disabled_get
* @apicovered			eext_circle_object_disabled_set, eext_circle_object_disabled_get
* @passcase				When eext_circle_object_disabled_set and eext_circle_object_disabled_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_disabled_set, eext_circle_object_disabled_get
//& type: auto
int ITc_eext_circle_object_disabled_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eina_Bool bDisabled = EINA_FALSE;

	nRet = CreateCircle();
	PRINT_RESULT(0, nRet, "CreateCircle", "Returned Value not correct");

	eext_circle_object_disabled_set(g_pCircleObject, EINA_TRUE);

	bDisabled = eext_circle_object_disabled_get(g_pCircleObject);
	PRINT_RESULT_CLEANUP(EINA_TRUE, bDisabled, "eext_circle_object_disabled_get", "Returned value not same as the value set previously", DeleteCircle());

	DeleteCircle();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_add_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_add
* @scenario				Call eext_circle_object_add
* @apicovered			eext_circle_object_add
* @passcase				When eext_circle_object_add is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_add
//& type: auto
int ITc_eext_circle_object_add_p(void)
{
	START_TEST;

	int nRet = 0;
	Evas_Object *pCircle = NULL;

	nRet = CreateCircleSurfaceLayout();
	PRINT_RESULT(0, nRet, "CreateCircleSurfaceLayout", "Returned Value not correct");

	pCircle = eext_circle_object_add(g_pEvasLayout, g_pCircleSurfaceLayout);
	CHECK_HANDLE_CLEANUP(pCircle, "eext_circle_object_add", DeleteCircleSurfaceLayout());

	evas_object_del(pCircle);
	DeleteCircleSurfaceLayout();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_genlist_add_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_genlist_add
* @scenario				Call eext_circle_object_genlist_add
* @apicovered			eext_circle_object_genlist_add
* @passcase				When eext_circle_object_genlist_add is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_genlist_add
//& type: auto
int ITc_eext_circle_object_genlist_add_p(void)
{
	START_TEST;

	int nRet = 0;
	Evas_Object *pGenlist = NULL;
	Evas_Object *pCircle = NULL;

	nRet = CreateCircleSurfaceLayout();
	PRINT_RESULT(0, nRet, "CreateCircleSurfaceLayout", "Returned Value not correct");

	pGenlist = elm_genlist_add(g_pEvasLayout);
	pCircle = eext_circle_object_genlist_add(pGenlist, g_pCircleSurfaceLayout);
	CHECK_HANDLE_CLEANUP(pCircle, "eext_circle_object_genlist_add", DeleteCircleSurfaceLayout());

	evas_object_del(pCircle);
	evas_object_del(pGenlist);
	DeleteCircleSurfaceLayout();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_genlist_scroller_policy_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_genlist_scroller_policy_set, eext_circle_object_genlist_scroller_policy_get
* @scenario				Call eext_circle_object_genlist_scroller_policy_set, eext_circle_object_genlist_scroller_policy_get
* @apicovered			eext_circle_object_genlist_scroller_policy_set, eext_circle_object_genlist_scroller_policy_get
* @passcase				When eext_circle_object_genlist_scroller_policy_set and eext_circle_object_genlist_scroller_policy_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_genlist_scroller_policy_set, eext_circle_object_genlist_scroller_policy_get
//& type: auto
int ITc_eext_circle_object_genlist_scroller_policy_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Elm_Scroller_Policy eVerticalPolicy = ELM_SCROLLER_POLICY_OFF, eHorizontalPolicy = ELM_SCROLLER_POLICY_OFF;

	nRet = CreateCircleGenlist();
	PRINT_RESULT(0, nRet, "CreateCircleGenlist", "Returned Value not correct");

	eext_circle_object_genlist_scroller_policy_set(g_pCircleGenlist, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_ON);

	eext_circle_object_genlist_scroller_policy_get(g_pCircleGenlist, &eHorizontalPolicy, &eVerticalPolicy);
	PRINT_RESULT_CLEANUP(ELM_SCROLLER_POLICY_ON, eHorizontalPolicy, "eext_circle_object_genlist_scroller_policy_get", "Returned value not same as the value set previously", DeleteCircleGenlist());
	PRINT_RESULT_CLEANUP(ELM_SCROLLER_POLICY_ON, eVerticalPolicy, "eext_circle_object_genlist_scroller_policy_get", "Returned value not same as the value set previously", DeleteCircleGenlist());

	DeleteCircleGenlist();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_slider_add_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_slider_add
* @scenario				Call eext_circle_object_slider_add
* @apicovered			eext_circle_object_slider_add
* @passcase				When eext_circle_object_slider_add is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_slider_add
//& type: auto
int ITc_eext_circle_object_slider_add_p(void)
{
	START_TEST;

	int nRet = 0;
	Evas_Object *pCircle = NULL;

	nRet = CreateCircleSurfaceLayout();
	PRINT_RESULT(0, nRet, "CreateCircleSurfaceLayout", "Returned Value not correct");

	pCircle = eext_circle_object_slider_add(g_pEvasLayout, g_pCircleSurfaceLayout);
	CHECK_HANDLE_CLEANUP(pCircle, "eext_circle_object_slider_add", DeleteCircleSurfaceLayout());

	evas_object_del(pCircle);
	DeleteCircleSurfaceLayout();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_slider_step_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_slider_step_set, eext_circle_object_slider_step_get
* @scenario				Call eext_circle_object_slider_step_set, eext_circle_object_slider_step_get
* @apicovered			eext_circle_object_slider_step_set, eext_circle_object_slider_step_get
* @passcase				When eext_circle_object_slider_step_set and eext_circle_object_slider_step_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_slider_step_set, eext_circle_object_slider_step_get
//& type: auto
int ITc_eext_circle_object_slider_step_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	double dValue = 0;

	nRet = CreateCircleSlider();
	PRINT_RESULT(0, nRet, "CreateCircleSlider", "Returned Value not correct");

	eext_circle_object_slider_step_set(g_pCircleSlider, 10);

	dValue = eext_circle_object_slider_step_get(g_pCircleSlider);
	PRINT_RESULT_CLEANUP(10, (int)dValue, "eext_circle_object_slider_step_get", "Returned value not same as the value set previously", DeleteCircleSlider());

	DeleteCircleSlider();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_datetime_add_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_datetime_add
* @scenario				Call eext_circle_object_datetime_add
* @apicovered			eext_circle_object_datetime_add
* @passcase				When eext_circle_object_datetime_add is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_datetime_add
//& type: auto
int ITc_eext_circle_object_datetime_add_p(void)
{
	START_TEST;

	int nRet = 0;
	Evas_Object *pDatetime = NULL;
	Evas_Object *pCircle = NULL;

	nRet = CreateCircleSurfaceLayout();
	PRINT_RESULT(0, nRet, "CreateCircleSurfaceLayout", "Returned Value not correct");

	pDatetime = elm_datetime_add(g_pEvasLayout);
	pCircle = eext_circle_object_datetime_add(pDatetime, g_pCircleSurfaceLayout);
	CHECK_HANDLE_CLEANUP(pCircle, "eext_circle_object_datetime_add", DeleteCircleSurfaceLayout());

	evas_object_del(pCircle);
	evas_object_del(pDatetime);
	DeleteCircleSurfaceLayout();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_progressbar_add_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_progressbar_add
* @scenario				Call eext_circle_object_progressbar_add
* @apicovered			eext_circle_object_progressbar_add
* @passcase				When eext_circle_object_progressbar_add is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_progressbar_add
//& type: auto
int ITc_eext_circle_object_progressbar_add_p(void)
{
	START_TEST;

	int nRet = 0;
	Evas_Object *pCircle = NULL;

	nRet = CreateCircleSurfaceLayout();
	PRINT_RESULT(0, nRet, "CreateCircleSurfaceLayout", "Returned Value not correct");

	pCircle = eext_circle_object_progressbar_add(g_pEvasLayout, g_pCircleSurfaceLayout);
	CHECK_HANDLE_CLEANUP(pCircle, "eext_circle_object_progressbar_add", DeleteCircleSurfaceLayout());

	evas_object_del(pCircle);
	DeleteCircleSurfaceLayout();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_surface_conformant_add_delete_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_surface_conformant_add, eext_circle_surface_del
* @scenario				Call eext_circle_surface_conformant_add, eext_circle_surface_del
* @apicovered			eext_circle_surface_conformant_add, eext_circle_surface_del
* @passcase				When eext_circle_surface_conformant_add is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_surface_conformant_add, eext_circle_surface_del
//& type: auto
int ITc_eext_circle_surface_conformant_add_delete_p(void)
{
	START_TEST;

	Eext_Circle_Surface *pSurface = NULL;

	int nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Returned Value not correct");

	pSurface = eext_circle_surface_conformant_add(g_pEvasConformant);
	CHECK_HANDLE_CLEANUP(pSurface, "eext_circle_surface_conformant_add", DeleteEvasWindow());

	eext_circle_surface_del(pSurface);
	DeleteEvasWindow();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_surface_layout_add_delete_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_surface_layout_add, eext_circle_surface_del
* @scenario				Call eext_circle_surface_layout_add, eext_circle_surface_del
* @apicovered			eext_circle_surface_layout_add, eext_circle_surface_del
* @passcase				When eext_circle_surface_layout_add is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_surface_layout_add, eext_circle_surface_del
//& type: auto
int ITc_eext_circle_surface_layout_add_delete_p(void)
{
	START_TEST;

	Eext_Circle_Surface *pSurface = NULL;

	int nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Returned Value not correct");

	pSurface = eext_circle_surface_layout_add(g_pEvasLayout);
	CHECK_HANDLE_CLEANUP(pSurface, "eext_circle_surface_layout_add", DeleteEvasWindow());

	eext_circle_surface_del(pSurface);
	DeleteEvasWindow();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_surface_naviframe_add_delete_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_surface_naviframe_add, eext_circle_surface_del
* @scenario				Call eext_circle_surface_naviframe_add, eext_circle_surface_del
* @apicovered			eext_circle_surface_naviframe_add, eext_circle_surface_del
* @passcase				When eext_circle_surface_naviframe_add is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_surface_naviframe_add, eext_circle_surface_del
//& type: auto
int ITc_eext_circle_surface_naviframe_add_delete_p(void)
{
	START_TEST;

	Eext_Circle_Surface *pSurface = NULL;

	int nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Returned Value not correct");

	pSurface = eext_circle_surface_naviframe_add(g_pEvasNaviframe);
	CHECK_HANDLE_CLEANUP(pSurface, "eext_circle_surface_naviframe_add", DeleteEvasWindow());

	eext_circle_surface_del(pSurface);
	DeleteEvasWindow();

	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_add_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_add
* @scenario				Call eext_rotary_selector_add
* @apicovered			eext_rotary_selector_add
* @passcase				When eext_rotary_selector_add is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_add
//& type: auto
int ITc_eext_rotary_selector_add_p(void)
{
	START_TEST;

	int nRet = 0;
	Evas_Object *pCircle = NULL;

	nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Returned Value not correct");

	pCircle = eext_rotary_selector_add(g_pEvasLayout);
	CHECK_HANDLE_CLEANUP(pCircle, "eext_rotary_selector_add", DeleteEvasWindow());

	evas_object_del(pCircle);
	DeleteEvasWindow();

	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_item_append_del_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_item_append, eext_rotary_selector_item_del
* @scenario				Call eext_rotary_selector_item_append and eext_rotary_selector_item_del
* @apicovered			eext_rotary_selector_item_append, eext_rotary_selector_item_del
* @passcase				When eext_rotary_selector_item_append and eext_rotary_selector_item_del is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_item_append and eext_rotary_selector_item_del
//& type: auto
int ITc_eext_rotary_selector_item_append_del_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pItem = NULL;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	pItem = eext_rotary_selector_item_append(g_pCircleSelector);
	CHECK_HANDLE_CLEANUP(pItem, "eext_rotary_selector_item_append", DeleteCircleSelector());
	if ( pItem != NULL )
	{
		eext_rotary_selector_item_del(pItem);
		pItem = NULL;
	}

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_item_prepend_clear_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_item_prepend, eext_rotary_selector_items_clear
* @scenario				Call eext_rotary_selector_item_prepend and eext_rotary_selector_items_clear
* @apicovered			eext_rotary_selector_item_prepend, eext_rotary_selector_items_clear
* @passcase				When eext_rotary_selector_item_prepend and eext_rotary_selector_items_clear is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_item_prepend and eext_rotary_selector_items_clear
//& type: auto
int ITc_eext_rotary_selector_item_prepend_clear_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pItem = NULL;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	pItem = eext_rotary_selector_item_prepend(g_pCircleSelector);
	CHECK_HANDLE_CLEANUP(pItem, "eext_rotary_selector_item_prepend", DeleteCircleSelector());

	eext_rotary_selector_items_clear(g_pCircleSelector);

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_item_insert_after_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_item_insert_after
* @scenario				Call eext_rotary_selector_item_insert_after
* @apicovered			eext_rotary_selector_item_insert_after
* @passcase				When eext_rotary_selector_item_insert_after is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_item_insert_after
//& type: auto
int ITc_eext_rotary_selector_item_insert_after_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pItem = NULL;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	pItem = eext_rotary_selector_item_insert_after(g_pCircleSelector, g_pEextItem);
	CHECK_HANDLE_CLEANUP(pItem, "eext_rotary_selector_item_insert_after", DeleteCircleSelector());

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_item_insert_before_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_item_insert_before
* @scenario				Call eext_rotary_selector_item_insert_before
* @apicovered			eext_rotary_selector_item_insert_before
* @passcase				When eext_rotary_selector_item_insert_before is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_item_insert_before
//& type: auto
int ITc_eext_rotary_selector_item_insert_before_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pItem = NULL;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	pItem = eext_rotary_selector_item_insert_before(g_pCircleSelector, g_pEextItem);
	CHECK_HANDLE_CLEANUP(pItem, "eext_rotary_selector_item_insert_before", DeleteCircleSelector());

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_item_part_text_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_item_part_text_set, eext_rotary_selector_item_part_text_get
* @scenario				Call eext_rotary_selector_item_part_text_set, eext_rotary_selector_item_part_text_get
* @apicovered			eext_rotary_selector_item_part_text_set, eext_rotary_selector_item_part_text_get
* @passcase				When eext_rotary_selector_item_part_text_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_item_part_text_set, eext_rotary_selector_item_part_text_get
//& type: auto
int ITc_eext_rotary_selector_item_part_text_set_get_p(void)
{
	START_TEST;

	int nRet = 0;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	eext_rotary_selector_item_part_text_set(g_pEextItem, "selector,main_text", TESTSTRING);

	const char *pReturnedContent = eext_rotary_selector_item_part_text_get(g_pEextItem, "selector,main_text");
	PRINT_RESULT_CLEANUP(0, strcmp(pReturnedContent, TESTSTRING), "eext_rotary_selector_item_part_text_get", "Returned string not same as the string set previously", DeleteCircleSelector());

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_item_domain_translatable_part_text_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_item_domain_translatable_part_text_set, eext_rotary_selector_item_part_text_get
* @scenario				Call eext_rotary_selector_item_domain_translatable_part_text_set, eext_rotary_selector_item_part_text_get
* @apicovered			eext_rotary_selector_item_domain_translatable_part_text_set, eext_rotary_selector_item_part_text_get
* @passcase				When eext_rotary_selector_item_domain_translatable_part_text_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_item_domain_translatable_part_text_set, eext_rotary_selector_item_part_text_get
//& type: auto
int ITc_eext_rotary_selector_item_domain_translatable_part_text_set_get_p(void)
{
	START_TEST;

	int nRet = 0;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	eext_rotary_selector_item_domain_translatable_part_text_set(g_pEextItem, "selector,main_text", "selector,main_text", TESTSTRING);

	const char *pReturnedContent = eext_rotary_selector_item_part_text_get(g_pEextItem, "selector,main_text");
	PRINT_RESULT_CLEANUP(0, strcmp(pReturnedContent, TESTSTRING), "eext_rotary_selector_item_part_text_get", "Returned string not same as the string set previously", DeleteCircleSelector());

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_item_part_content_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_item_part_content_set, eext_rotary_selector_item_part_content_get
* @scenario				Call eext_rotary_selector_item_part_content_set, eext_rotary_selector_item_part_content_get
* @apicovered			eext_rotary_selector_item_part_content_set, eext_rotary_selector_item_part_content_get
* @passcase				When eext_rotary_selector_item_part_content_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_item_part_content_set, eext_rotary_selector_item_part_content_get
//& type: auto
int ITc_eext_rotary_selector_item_part_content_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Evas_Object *pObject = NULL;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	eext_rotary_selector_item_part_content_set(g_pEextItem, "item,bg_image", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, g_pImageObject);

	pObject = eext_rotary_selector_item_part_content_get(g_pEextItem, "item,bg_image", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL);
	CHECK_HANDLE_CLEANUP(pObject, "eext_rotary_selector_item_part_content_get", DeleteCircleSelector());
	if(pObject != g_pImageObject)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "eext_rotary_selector_item_part_content_get", "Content Mismatch");
		DeleteCircleSelector();
		return 1;
	}

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_part_content_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_part_content_set, eext_rotary_selector_part_content_get
* @scenario				Call eext_rotary_selector_part_content_set, eext_rotary_selector_part_content_get
* @apicovered			eext_rotary_selector_part_content_set, eext_rotary_selector_part_content_get
* @passcase				When eext_rotary_selector_part_content_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_part_content_set, eext_rotary_selector_part_content_get
//& type: auto
int ITc_eext_rotary_selector_part_content_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Evas_Object *pObject = NULL;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	eext_rotary_selector_part_content_set(g_pCircleSelector, "selector,bg_image", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, g_pImageObject);

	pObject = eext_rotary_selector_part_content_get(g_pCircleSelector, "selector,bg_image", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL);
	CHECK_HANDLE_CLEANUP(pObject, "eext_rotary_selector_part_content_get", DeleteCircleSelector());
	if(pObject != g_pImageObject)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "eext_rotary_selector_part_content_get", "Content Mismatch");
		DeleteCircleSelector();
		return 1;
	}

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_item_part_color_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_item_part_color_set, eext_rotary_selector_item_part_color_get
* @scenario				Call eext_rotary_selector_item_part_color_set, eext_rotary_selector_item_part_color_get
* @apicovered			eext_rotary_selector_item_part_color_set, eext_rotary_selector_item_part_color_get
* @passcase				When eext_rotary_selector_item_part_color_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_item_part_color_set, eext_rotary_selector_item_part_color_get
//& type: auto
int ITc_eext_rotary_selector_item_part_color_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	int nColourR = 1;
	int nColourG = 1;
	int nColourB = 1;
	int nColourA = 1;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	eext_rotary_selector_item_part_content_set(g_pEextItem, "item,bg_image", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, g_pImageObject);

	eext_rotary_selector_item_part_color_set(g_pEextItem, "item,bg_image", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, 0, 0, 0, 0);

	eext_rotary_selector_item_part_color_get(g_pEextItem, "item,bg_image", EEXT_ROTARY_SELECTOR_ITEM_STATE_NORMAL, &nColourR, &nColourG, &nColourB, &nColourA);
	PRINT_RESULT_CLEANUP(0, nColourR+nColourG+nColourB+nColourA, "eext_rotary_selector_item_part_color_get", "Returned colour not same as the colour set previously", DeleteCircleSelector());

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_part_color_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_part_color_set, eext_rotary_selector_part_color_get
* @scenario				Call eext_rotary_selector_part_color_set, eext_rotary_selector_part_color_get
* @apicovered			eext_rotary_selector_part_color_set, eext_rotary_selector_part_color_get
* @passcase				When eext_rotary_selector_part_color_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_part_color_set, eext_rotary_selector_part_color_get
//& type: auto
int ITc_eext_rotary_selector_part_color_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	int nColourR = 1;
	int nColourG = 1;
	int nColourB = 1;
	int nColourA = 1;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	eext_rotary_selector_part_content_set(g_pCircleSelector, "selector,bg_image", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, g_pImageObject);

	eext_rotary_selector_part_color_set(g_pCircleSelector, "selector,bg_image", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, 0, 0, 0, 0);

	eext_rotary_selector_part_color_get(g_pCircleSelector, "selector,bg_image", EEXT_ROTARY_SELECTOR_SELECTOR_STATE_NORMAL, &nColourR, &nColourG, &nColourB, &nColourA);
	PRINT_RESULT_CLEANUP(0, nColourR+nColourG+nColourB+nColourA, "eext_rotary_selector_part_color_get", "Returned colour not same as the colour set previously", DeleteCircleSelector());

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_selected_item_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_selected_item_set, eext_rotary_selector_selected_item_get
* @scenario				Call eext_rotary_selector_selected_item_set, eext_rotary_selector_selected_item_get
* @apicovered			eext_rotary_selector_selected_item_set, eext_rotary_selector_selected_item_get
* @passcase				When eext_rotary_selector_selected_item_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_selected_item_set, eext_rotary_selector_selected_item_get
//& type: auto
int ITc_eext_rotary_selector_selected_item_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pObject = NULL;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	eext_rotary_selector_selected_item_set(g_pCircleSelector, g_pEextItem);

	pObject = eext_rotary_selector_selected_item_get(g_pCircleSelector);
	CHECK_HANDLE_CLEANUP(pObject, "eext_rotary_selector_selected_item_get", DeleteCircleSelector());
	if(pObject != g_pEextItem)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "eext_rotary_selector_selected_item_get", "Content Mismatch");
		DeleteCircleSelector();
		return 1;
	}

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_items_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_rotary_selector_items_get
* @scenario				Call eext_rotary_selector_items_get
* @apicovered			eext_rotary_selector_items_get
* @passcase				When eext_rotary_selector_items_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_items_get
//& type: auto
int ITc_eext_rotary_selector_items_get_p(void)
{
	START_TEST;

	int nRet = 0;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	const Eina_List *pList = eext_rotary_selector_items_get(g_pCircleSelector);
	CHECK_HANDLE_CLEANUP(pList, "eext_rotary_selector_items_get", DeleteCircleSelector());

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_more_option_add_delete_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_more_option_add, eext_circle_surface_del
* @scenario				Call eext_more_option_add, eext_circle_surface_del
* @apicovered			eext_more_option_add, eext_circle_surface_del
* @passcase				When eext_more_option_add is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_add, eext_circle_surface_del
//& type: auto
int ITc_eext_more_option_add_delete_p(void)
{
	START_TEST;

	Evas_Object *pLayout = NULL;

	int nRet = CreateEvasWindow();
	PRINT_RESULT(0, nRet, "CreateEvasWindow", "Returned Value not correct");

	pLayout = eext_more_option_add(g_pEvasLayout);
	CHECK_HANDLE_CLEANUP(pLayout, "eext_more_option_add", DeleteEvasWindow());

	evas_object_del(pLayout);
	DeleteEvasWindow();

	return 0;
}

/**
* @testcase 			ITc_eext_more_option_direction_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_more_option_direction_set, eext_more_option_direction_get
* @scenario				Call eext_more_option_direction_set, eext_more_option_direction_get
* @apicovered			eext_more_option_direction_set, eext_more_option_direction_get
* @passcase				When eext_more_option_direction_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_direction_set, eext_more_option_direction_get
//& type: auto
int ITc_eext_more_option_direction_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_More_Option_Direction eDirection = EEXT_MORE_OPTION_DIRECTION_BOTTOM;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	eext_more_option_direction_set(g_pMoreOption, EEXT_MORE_OPTION_DIRECTION_RIGHT);

	eDirection = eext_more_option_direction_get(g_pMoreOption);
	PRINT_RESULT_CLEANUP(EEXT_MORE_OPTION_DIRECTION_RIGHT, eDirection, "eext_more_option_direction_get", "Returned Value not correct", DeleteMoreOption());

	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_more_option_item_append_del_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_more_option_item_append, eext_more_option_item_del
* @scenario				Call eext_more_option_item_append, eext_more_option_item_del
* @apicovered			eext_more_option_item_append, eext_more_option_item_del
* @passcase				When eext_more_option_item_append is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_item_append, eext_more_option_item_del
//& type: auto
int ITc_eext_more_option_item_append_del_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pObject = NULL;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	pObject = eext_more_option_item_append(g_pMoreOption);
	CHECK_HANDLE_CLEANUP(pObject, "eext_more_option_item_append", DeleteMoreOption());

	eext_more_option_item_del(pObject);
	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_more_option_item_prepend_del_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_more_option_item_prepend, eext_more_option_item_del
* @scenario				Call eext_more_option_item_prepend, eext_more_option_item_del
* @apicovered			eext_more_option_item_prepend, eext_more_option_item_del
* @passcase				When eext_more_option_item_prepend is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_item_prepend, eext_more_option_item_del
//& type: auto
int ITc_eext_more_option_item_prepend_del_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pObject = NULL;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	pObject = eext_more_option_item_prepend(g_pMoreOption);
	CHECK_HANDLE_CLEANUP(pObject, "eext_more_option_item_prepend", DeleteMoreOption());

	eext_more_option_item_del(pObject);
	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_more_option_item_insert_after_clear_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_more_option_item_insert_after, eext_more_option_items_clear
* @scenario				Call eext_more_option_item_insert_after, eext_more_option_items_clear
* @apicovered			eext_more_option_item_insert_after, eext_more_option_items_clear
* @passcase				When eext_more_option_item_insert_after is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_item_insert_after, eext_more_option_items_clear
//& type: auto
int ITc_eext_more_option_item_insert_after_clear_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pObject = NULL, *pNewObject = NULL;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	pObject = eext_more_option_item_append(g_pMoreOption);
	CHECK_HANDLE_CLEANUP(pObject, "eext_more_option_item_append", DeleteMoreOption());

	pNewObject = eext_more_option_item_insert_after(g_pMoreOption, pObject);
	CHECK_HANDLE_CLEANUP(pNewObject, "eext_more_option_item_insert_after", eext_more_option_items_clear(g_pMoreOption); DeleteMoreOption());

	eext_more_option_items_clear(g_pMoreOption);
	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_more_option_item_insert_before_clear_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_more_option_item_insert_before, eext_more_option_items_clear
* @scenario				Call eext_more_option_item_insert_before, eext_more_option_items_clear
* @apicovered			eext_more_option_item_insert_before, eext_more_option_items_clear
* @passcase				When eext_more_option_item_insert_before is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_item_insert_before, eext_more_option_items_clear
//& type: auto
int ITc_eext_more_option_item_insert_before_clear_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pObject = NULL, *pNewObject = NULL;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	pObject = eext_more_option_item_append(g_pMoreOption);
	CHECK_HANDLE_CLEANUP(pObject, "eext_more_option_item_append", DeleteMoreOption());

	pNewObject = eext_more_option_item_insert_before(g_pMoreOption, pObject);
	CHECK_HANDLE_CLEANUP(pNewObject, "eext_more_option_item_insert_before", eext_more_option_items_clear(g_pMoreOption); DeleteMoreOption());

	eext_more_option_items_clear(g_pMoreOption);
	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_more_option_item_part_text_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_more_option_item_part_text_set, eext_more_option_item_part_text_get
* @scenario				Call eext_more_option_item_part_text_set, eext_more_option_item_part_text_get
* @apicovered			eext_more_option_item_part_text_set, eext_more_option_item_part_text_get
* @passcase				When eext_more_option_item_part_text_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_item_part_text_set, eext_more_option_item_part_text_get
//& type: auto
int ITc_eext_more_option_item_part_text_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pObject = NULL;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	pObject = eext_more_option_item_append(g_pMoreOption);
	CHECK_HANDLE_CLEANUP(pObject, "eext_more_option_item_append", DeleteMoreOption());

	eext_more_option_item_part_text_set(pObject, "selector,main_text", TESTSTRING);

	const char *pReturnedContent = eext_more_option_item_part_text_get(pObject, "selector,main_text");
	PRINT_RESULT_CLEANUP(0, strcmp(pReturnedContent, TESTSTRING), "eext_more_option_item_part_text_get", "Returned string not same as the string set previously", eext_more_option_items_clear(g_pMoreOption); DeleteMoreOption());

	eext_more_option_items_clear(g_pMoreOption);
	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_more_option_item_domain_translatable_part_text_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_more_option_item_domain_translatable_part_text_set, eext_more_option_item_part_text_get
* @scenario				Call eext_more_option_item_domain_translatable_part_text_set, eext_more_option_item_part_text_get
* @apicovered			eext_more_option_item_domain_translatable_part_text_set, eext_more_option_item_part_text_get
* @passcase				When eext_more_option_item_domain_translatable_part_text_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_item_domain_translatable_part_text_set, eext_more_option_item_part_text_get
//& type: auto
int ITc_eext_more_option_item_domain_translatable_part_text_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pObject = NULL;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	pObject = eext_more_option_item_append(g_pMoreOption);
	CHECK_HANDLE_CLEANUP(pObject, "eext_more_option_item_append", DeleteMoreOption());

	eext_more_option_item_domain_translatable_part_text_set(pObject, "selector,main_text", "selector,main_text", TESTSTRING);

	const char *pReturnedContent = eext_more_option_item_part_text_get(pObject, "selector,main_text");
	PRINT_RESULT_CLEANUP(0, strcmp(pReturnedContent, TESTSTRING), "eext_more_option_item_part_text_get", "Returned string not same as the string set previously", eext_more_option_items_clear(g_pMoreOption); DeleteMoreOption());

	eext_more_option_items_clear(g_pMoreOption);
	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_more_option_item_part_content_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_more_option_item_part_content_set, eext_more_option_item_part_content_get
* @scenario				Call eext_more_option_item_part_content_set, eext_more_option_item_part_content_get
* @apicovered			eext_more_option_item_part_content_set, eext_more_option_item_part_content_get
* @passcase				When eext_more_option_item_part_content_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_item_part_content_set, eext_more_option_item_part_content_get
//& type: auto
int ITc_eext_more_option_item_part_content_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pObject = NULL;
	Evas_Object *pReturnedContent = NULL;
	Evas_Object *pContent = NULL;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	pObject = eext_more_option_item_append(g_pMoreOption);
	CHECK_HANDLE_CLEANUP(pObject, "eext_more_option_item_append", DeleteMoreOption());

	pContent = elm_button_add(g_pMoreOption);
	CHECK_HANDLE_CLEANUP(pObject, "elm_button_add", eext_more_option_items_clear(g_pMoreOption); DeleteMoreOption());
	evas_object_show(pContent);

	eext_more_option_item_part_content_set(pObject, "selector,content", pContent);

	pReturnedContent = eext_more_option_item_part_content_get(pObject, "selector,content");
	CHECK_HANDLE_CLEANUP(pReturnedContent, "eext_more_option_item_part_content_get", evas_object_del(pContent); eext_more_option_items_clear(g_pMoreOption); DeleteMoreOption());
	if(pContent != pReturnedContent)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "eext_more_option_item_part_content_get", "Content Mismatch");
		evas_object_del(pContent);
		eext_more_option_items_clear(g_pMoreOption);
		DeleteMoreOption();
		return 1;
	}

	evas_object_del(pContent);
	eext_more_option_items_clear(g_pMoreOption);
	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_more_option_opened_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_more_option_opened_set, eext_more_option_opened_get
* @scenario				Call eext_more_option_opened_set, eext_more_option_opened_get
* @apicovered			eext_more_option_opened_set, eext_more_option_opened_get
* @passcase				When eext_more_option_opened_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_opened_set, eext_more_option_opened_get
//& type: auto
int ITc_eext_more_option_opened_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eina_Bool bOpened = EINA_FALSE;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	eext_more_option_opened_set(g_pMoreOption, EINA_TRUE);

	bOpened = eext_more_option_opened_get(g_pMoreOption);
	PRINT_RESULT_CLEANUP(EINA_TRUE, bOpened, "eext_more_option_opened_get", "Returned Value not correct", DeleteMoreOption());

	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_more_option_items_get_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_more_option_items_get
* @scenario				Call eext_more_option_items_get
* @apicovered			eext_more_option_items_get
* @passcase				When eext_more_option_items_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_items_get
//& type: auto
int ITc_eext_more_option_items_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eext_Object_Item *pObject = NULL;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	pObject = eext_more_option_item_append(g_pMoreOption);
	CHECK_HANDLE_CLEANUP(pObject, "eext_more_option_item_append", DeleteMoreOption());

	const Eina_List *pList = eext_more_option_items_get(g_pMoreOption);
	CHECK_HANDLE_CLEANUP(pList, "eext_more_option_items_get", DeleteMoreOption());

	eext_more_option_items_clear(g_pMoreOption);
	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_spinner_add_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_spinner_add
* @scenario				Call eext_circle_object_spinner_add
* @apicovered			eext_circle_object_spinner_add
* @passcase				When eext_circle_object_spinner_add is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_spinner_add
//& type: auto
int ITc_eext_circle_object_spinner_add_p(void)
{
	START_TEST;

	int nRet = 0;
	Evas_Object *pSpinner = NULL;
	Evas_Object *pCircle = NULL;

	nRet = CreateCircleSurfaceLayout();
	PRINT_RESULT(0, nRet, "CreateCircleSurfaceLayout", "Returned Value not correct");

	pSpinner = elm_spinner_add(g_pEvasLayout);
	pCircle = eext_circle_object_spinner_add(pSpinner, g_pCircleSurfaceLayout);
	CHECK_HANDLE_CLEANUP(pCircle, "eext_circle_object_spinner_add", DeleteCircleSurfaceLayout());

	evas_object_del(pCircle);
	evas_object_del(pSpinner);
	DeleteCircleSurfaceLayout();

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_spinner_angle_set_p
* @since_tizen			2.3.1
* @author            	SRID(shekhar1.s)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_spinner_angle_set
* @scenario				Call eext_circle_object_spinner_angle_set
* @apicovered			eext_circle_object_spinner_angle_set
* @passcase				When eext_circle_object_spinner_angle_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_spinner_angle_set
//& type: auto
int ITc_eext_circle_object_spinner_angle_set_p(void)
{
	START_TEST;
	int nRet = 0;

	nRet = CreateCircleSpinner();
	PRINT_RESULT(0, nRet, "CreateCircleSpinner", "Returned Value not correct");

	eext_circle_object_spinner_angle_set(g_pCircleSpinner, 10);

	DeleteCircleSpinner();
	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_item_value_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_item_value_set, eext_circle_object_item_value_get
* @scenario				Create elm window and set title and callback
*						Set value by eext_circle_object_item_value_set and get value eext_circle_object_item_value_get
* @apicovered			elm_win_add, elm_win_title_set, evas_object_smart_callback_add, elm_scroller_add, eext_circle_object_add, 
*						eext_circle_object_item_value_set, eext_circle_object_item_value_get
* @passcase				When Set and Get values are same.
* @failcase				If Set and Get values are not same or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_item_value_set, eext_circle_object_item_value_get
//& type: auto
int ITc_eext_circle_object_item_value_set_get_p(void)
{
	START_TEST;

	const char *pszItemName = "default";
	double dSetValue = 30;
	double dGetValue = 0;

	Evas_Object *EvasWin = NULL;
	Evas_Object *EvasScrolr = NULL;
	Evas_Object *EvasCircleObj = NULL;

	EvasWin = CreateElmWindow("window");
	CHECK_HANDLE(EvasWin, "CreateElmWindow");

	EvasScrolr = elm_scroller_add(EvasWin);
	CHECK_HANDLE(EvasScrolr, "elm_scroller_add");

	EvasCircleObj = eext_circle_object_add(EvasScrolr, NULL);
	CHECK_HANDLE(EvasCircleObj, "eext_circle_object_add");

	eext_circle_object_item_value_set(EvasCircleObj, pszItemName, dSetValue);	
	dGetValue = eext_circle_object_item_value_get(EvasCircleObj, pszItemName);
	PRINT_RESULT(dSetValue, dGetValue, "eext_circle_object_item_value_get", "Set Get value mismatch");

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_item_color_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_item_color_set, eext_circle_object_item_color_get
* @scenario				Create elm window and set title and callback
*						Set value by eext_circle_object_item_color_set and get value by eext_circle_object_item_color_get
* @apicovered			elm_win_add, elm_win_title_set, evas_object_smart_callback_add, elm_scroller_add, eext_circle_object_add, 
*						eext_circle_object_item_color_set, eext_circle_object_item_color_get
* @passcase				When Set and Get values are same.
* @failcase				If Set and Get values are not same or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_item_color_set, eext_circle_object_item_color_get
//& type: auto
int ITc_eext_circle_object_item_color_set_get_p(void)
{
	START_TEST;

	const char *pszItemName = "default";
	int nRedSetVal = 5, nGreenSetVal = 10, nBlueSetVal = 15, nAlphaSetVal = 20;
	int nRedGetVal = 0, nGreenGetVal = 0, nBlueGetVal = 0, nAlphaGetVal = 0;

	Evas_Object *EvasWin = NULL;
	Evas_Object *EvasScrolr = NULL;
	Evas_Object *EvasCircleObj = NULL;

	EvasWin = CreateElmWindow("window");
	CHECK_HANDLE(EvasWin, "CreateElmWindow");

	EvasScrolr = elm_scroller_add(EvasWin);
	CHECK_HANDLE(EvasScrolr, "elm_scroller_add");

	EvasCircleObj = eext_circle_object_add(EvasScrolr, NULL);
	CHECK_HANDLE(EvasCircleObj, "eext_circle_object_add");

	eext_circle_object_item_color_set(EvasCircleObj, pszItemName, nRedSetVal, nGreenSetVal, nBlueSetVal, nAlphaSetVal);
	eext_circle_object_item_color_get(EvasCircleObj, pszItemName, &nRedGetVal, &nGreenGetVal, &nBlueGetVal, &nAlphaGetVal);

	PRINT_RESULT(nRedSetVal, nRedGetVal, "eext_circle_object_item_color_get", "Set Get Red value mismatch");
	PRINT_RESULT(nGreenSetVal, nGreenGetVal, "eext_circle_object_item_color_get", "Set Get Green value mismatch");
	PRINT_RESULT(nBlueSetVal, nBlueGetVal, "eext_circle_object_item_color_get", "Set Get Blue value mismatch");
	PRINT_RESULT(nAlphaSetVal, nAlphaGetVal, "eext_circle_object_item_color_get", "Set Get Alpha value mismatch");

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_item_radius_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_item_radius_set, eext_circle_object_item_radius_get
* @scenario				Create elm window and set title and callback
*						Set value by eext_circle_object_item_radius_set and get value by eext_circle_object_item_radius_get
* @apicovered			elm_win_add, elm_win_title_set, evas_object_smart_callback_add, elm_scroller_add, eext_circle_object_add, 
*						eext_circle_object_item_radius_set, eext_circle_object_item_radius_get
* @passcase				When Set and Get values are same.
* @failcase				If Set and Get values are not same or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_item_radius_set, eext_circle_object_item_radius_get
//& type: auto
int ITc_eext_circle_object_item_radius_set_get_p(void)
{
	START_TEST;

	const char *pszItemName = "default";
	double dSetRad = 10, dGetRad = 0;
	Evas_Object *EvasWin = NULL;
	Evas_Object *EvasScrolr = NULL;
	Evas_Object *EvasCircleObj = NULL;

	EvasWin = CreateElmWindow("window");
	CHECK_HANDLE(EvasWin, "CreateElmWindow");
	
	EvasScrolr = elm_scroller_add(EvasWin);
	CHECK_HANDLE(EvasScrolr, "elm_scroller_add");
	
	EvasCircleObj = eext_circle_object_add(EvasScrolr, NULL);
	CHECK_HANDLE(EvasCircleObj, "eext_circle_object_add");

	eext_circle_object_item_radius_set(EvasCircleObj, pszItemName, dSetRad);
	dGetRad = eext_circle_object_item_radius_get(EvasCircleObj, pszItemName);
	PRINT_RESULT(dSetRad, dGetRad, "eext_circle_object_item_radius_get", "Set Get Radius value mismatch");

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_item_line_width_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_item_line_width_set, eext_circle_object_item_line_width_get
* @scenario				Create elm window and set title and callback
*						Set value by eext_circle_object_item_line_width_set and get value by eext_circle_object_item_line_width_get
* @apicovered			elm_win_add, elm_win_title_set, evas_object_smart_callback_add, elm_scroller_add, eext_circle_object_add, 
*						eext_circle_object_item_line_width_set, eext_circle_object_item_line_width_get
* @passcase				When Set and Get values are same.
* @failcase				If Set and Get values are not same or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_item_line_width_set, eext_circle_object_item_line_width_get
//& type: auto
int ITc_eext_circle_object_item_line_width_set_get_p(void)
{
	START_TEST;

	const char *pszItemName = "default";
	int nSetLineWidth = 10, nGetLineWidth = 0;
	Evas_Object *EvasWin = NULL;
	Evas_Object *EvasScrolr = NULL;
	Evas_Object *EvasCircleObj = NULL;

	EvasWin = CreateElmWindow("window");
	CHECK_HANDLE(EvasWin, "CreateElmWindow");

	EvasScrolr = elm_scroller_add(EvasWin);
	CHECK_HANDLE(EvasScrolr, "elm_scroller_add");

	EvasCircleObj = eext_circle_object_add(EvasScrolr, NULL);
	CHECK_HANDLE(EvasCircleObj, "eext_circle_object_add");

	eext_circle_object_item_line_width_set(EvasCircleObj, pszItemName, nSetLineWidth);
	nGetLineWidth = eext_circle_object_item_line_width_get(EvasCircleObj, pszItemName);
	PRINT_RESULT(nSetLineWidth, nGetLineWidth, "eext_circle_object_item_line_width_get", "Set Get Line Width value mismatch");

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_item_angle_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_item_angle_set, eext_circle_object_item_angle_get
* @scenario				Create elm window and set title and callback
*						Set value by eext_circle_object_item_angle_set and get value by eext_circle_object_item_angle_get
* @apicovered			elm_win_add, elm_win_title_set, evas_object_smart_callback_add, elm_scroller_add, eext_circle_object_add, 
*						eext_circle_object_item_angle_set, eext_circle_object_item_angle_get
* @passcase				When Set and Get values are same.
* @failcase				If Set and Get values are not same or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_item_angle_set, eext_circle_object_item_angle_get
//& type: auto
int ITc_eext_circle_object_item_angle_set_get_p(void)
{
	START_TEST;

	const char *pszItemName = "default";
	double dSetItemAngle = 10, dGetItemAngle = 0;
	Evas_Object *EvasWin = NULL;
	Evas_Object *EvasScrolr = NULL;
	Evas_Object *EvasCircleObj = NULL;

	EvasWin = CreateElmWindow("window");
	CHECK_HANDLE(EvasWin, "CreateElmWindow");
	
	EvasScrolr = elm_scroller_add(EvasWin);
	CHECK_HANDLE(EvasScrolr, "elm_scroller_add");
	
	EvasCircleObj = eext_circle_object_add(EvasScrolr, NULL);
	CHECK_HANDLE(EvasCircleObj, "eext_circle_object_add");

	eext_circle_object_item_angle_set(EvasCircleObj, pszItemName, dSetItemAngle);
	dGetItemAngle = eext_circle_object_item_angle_get(EvasCircleObj, pszItemName);
	PRINT_RESULT(dSetItemAngle, dGetItemAngle, "eext_circle_object_item_angle_get", "Set Get Item Angle value mismatch");

   return 0;
}

/**
* @testcase 			ITc_eext_circle_object_item_angle_offset_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_item_angle_offset_set, eext_circle_object_item_angle_offset_get
* @scenario				Create elm window and set title and callback
*						Set value by eext_circle_object_item_angle_offset_set and get value by eext_circle_object_item_angle_offset_get
* @apicovered			elm_win_add, elm_win_title_set, evas_object_smart_callback_add, elm_scroller_add, eext_circle_object_add, 
*						eext_circle_object_item_angle_offset_set, eext_circle_object_item_angle_offset_get
* @passcase				When Set and Get values are same.
* @failcase				If Set and Get values are not same or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_item_angle_offset_set, eext_circle_object_item_angle_offset_get
//& type: auto
int ITc_eext_circle_object_item_angle_offset_set_get_p(void)
{
	START_TEST;

	const char *pszItemName = "default";
	double dSetItmAnglOfst = 10, dGetItmAnglOfst = 0;
	Evas_Object *EvasWin = NULL;
	Evas_Object *EvasScrolr = NULL;
	Evas_Object *EvasCircleObj = NULL;

	EvasWin = CreateElmWindow("window");
	CHECK_HANDLE(EvasWin, "CreateElmWindow");

	EvasScrolr = elm_scroller_add(EvasWin);
	CHECK_HANDLE(EvasScrolr, "elm_scroller_add");

	EvasCircleObj = eext_circle_object_add(EvasScrolr, NULL);
	CHECK_HANDLE(EvasCircleObj, "eext_circle_object_add");

	eext_circle_object_item_angle_offset_set(EvasCircleObj, pszItemName, dSetItmAnglOfst);
	dGetItmAnglOfst = eext_circle_object_item_angle_offset_get(EvasCircleObj, pszItemName);
	PRINT_RESULT(dSetItmAnglOfst, dGetItmAnglOfst, "eext_circle_object_item_angle_offset_get", "Set Get Item Angle Offset value mismatch");

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_item_angle_min_max_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_item_angle_min_max_set, eext_circle_object_item_angle_min_max_get
* @scenario				Create elm window and set title and callback
*						Set value by eext_circle_object_item_angle_min_max_set and get value by eext_circle_object_item_angle_min_max_get
* @apicovered			elm_win_add, elm_win_title_set, evas_object_smart_callback_add, elm_scroller_add, eext_circle_object_add, 
*						eext_circle_object_item_angle_min_max_set, eext_circle_object_item_angle_min_max_get
* @passcase				When Set and Get values are same.
* @failcase				If Set and Get values are not same or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_item_angle_min_max_set, eext_circle_object_item_angle_min_max_get
//& type: auto
int ITc_eext_circle_object_item_angle_min_max_set_get_p(void)
{
	START_TEST;

	const char *pszItemName = "default";
	double dSetItemAngleMin = 5, dGetItemAngleMin = 0;
	double dSetItemAngleMax = 10, dGetItemAngleMax = 0;
	Evas_Object *EvasWin = NULL;
	Evas_Object *EvasScrolr = NULL;
	Evas_Object *EvasCircleObj = NULL;

	EvasWin = CreateElmWindow("window");
	CHECK_HANDLE(EvasWin, "CreateElmWindow");

	EvasScrolr = elm_scroller_add(EvasWin);
	CHECK_HANDLE(EvasScrolr, "elm_scroller_add");
	
	EvasCircleObj = eext_circle_object_add(EvasScrolr, NULL);
	CHECK_HANDLE(EvasCircleObj, "eext_circle_object_add");

	eext_circle_object_item_angle_min_max_set(EvasCircleObj, pszItemName, dSetItemAngleMin, dSetItemAngleMax);
	eext_circle_object_item_angle_min_max_get(EvasCircleObj, pszItemName, &dGetItemAngleMin, &dGetItemAngleMax);
	PRINT_RESULT(dSetItemAngleMin, dGetItemAngleMin, "eext_circle_object_item_angle_min_max_get", "Set Get Item Angle Min value mismatch");
	PRINT_RESULT(dSetItemAngleMax, dGetItemAngleMax, "eext_circle_object_item_angle_min_max_get", "Set Get Item Angle Max value mismatch");

	return 0;
}

/**
* @testcase 			ITc_eext_circle_object_item_value_min_max_set_get_p
* @since_tizen			2.3.1
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Test eext_circle_object_item_value_min_max_set, eext_circle_object_item_value_min_max_get
* @scenario				Create elm window and set title and callback
*						Set value by eext_circle_object_item_value_min_max_set and get value by eext_circle_object_item_value_min_max_get
* @apicovered			elm_win_add, elm_win_title_set, evas_object_smart_callback_add, elm_scroller_add, eext_circle_object_add, 
*						eext_circle_object_item_value_min_max_set, eext_circle_object_item_value_min_max_get
* @passcase				When Set and Get values are same.
* @failcase				If Set and Get values are not same or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_circle_object_item_value_min_max_set, eext_circle_object_item_value_min_max_get
//& type: auto
int ITc_eext_circle_object_item_value_min_max_set_get_p(void)
{
	START_TEST;

	const char *pszItemName = "default";
	double dSetItemValueMin = 5, dGetItemValueMin = 0;
	double dSetItemValueMax = 10, dGetItemValueMax = 0;
	Evas_Object *EvasWin = NULL;
	Evas_Object *EvasScrolr = NULL;
	Evas_Object *EvasCircleObj = NULL;

	EvasWin = CreateElmWindow("window");
	CHECK_HANDLE(EvasWin, "CreateElmWindow");

	EvasScrolr = elm_scroller_add(EvasWin);
	CHECK_HANDLE(EvasScrolr, "elm_scroller_add");

	EvasCircleObj = eext_circle_object_add(EvasScrolr, NULL);
	CHECK_HANDLE(EvasCircleObj, "eext_circle_object_add");


	eext_circle_object_item_value_min_max_set(EvasCircleObj, pszItemName, dSetItemValueMin, dSetItemValueMax);
	eext_circle_object_item_value_min_max_get(EvasCircleObj, pszItemName, &dGetItemValueMin, &dGetItemValueMax);
	PRINT_RESULT(dSetItemValueMin, dSetItemValueMin, "eext_circle_object_item_value_min_max_get", "Set Get Item Value Min value mismatch");
	PRINT_RESULT(dSetItemValueMax, dGetItemValueMax, "eext_circle_object_item_value_min_max_get", "Set Get Item Value Max value mismatch");

	return 0;
}

/**
* @testcase						ITc_efl_ext_eext_circle_object_mirrored_set_get_p
* @since_tizen					3.0
* @author						SRID(bipin.k)
* @reviewer						SRID(shobhit.v)
* @type							auto
* @description					eext_circle_object_mirrored_set, eext_circle_object_mirrored_get values to be
*								same for the mirrorred state of the object.
* @scenario						Creating  a new circle scroller object and then setting and getting of a mirrorred state
*								of a given object.
* @apicovered					elm_scroller_add, eext_circle_object_scroller_add,eext_circle_object_mirrored_set,eext_circle_object_mirrored_get
* @passcase						When Set and Get values are same.
* @failcase						Set and Get values are not same or any precondition API fails
* @precondition					None
* @postcondition				None
*/
//& purpose: Test Set and Get of a  mirrored state of a given circle object.
//& type: auto

int ITc_efl_ext_eext_circle_object_mirrored_set_get_p(void)
{
	START_TEST;
	Evas_Object *win=NULL;
	Evas_Object *scroller=NULL;
	Evas_Object *circle_scroller=NULL;

	win = CreateWin("window");
	CHECK_HANDLE(win,"CreateWin");

	scroller = elm_scroller_add(win);
	CHECK_HANDLE_CLEANUP(scroller,"elm_scroller_add",evas_object_del(win));

	circle_scroller = eext_circle_object_scroller_add(scroller, NULL);
	CHECK_HANDLE_CLEANUP(circle_scroller,"eext_circle_object_scroller_add",evas_object_del(win));

	eext_circle_object_mirrored_set(circle_scroller, EEXT_CIRCLE_MIRRORED_ON);
	int mirror_mode = eext_circle_object_mirrored_get(circle_scroller);
	PRINT_RESULT_CLEANUP(EEXT_CIRCLE_MIRRORED_ON,mirror_mode, "eext_circle_object_mirrored_set and eext_circle_object_mirrored_get ","Returned value not correct ",evas_object_del(win) );
	evas_object_del(win);
   return 0;
}

/**
* @testcase					ITc_eext_panel_add
* @since_tizen					4.0
* @author					SRID(samuel.peter)
* @reviewer					SRID(nibha.sharma)
* @type						auto
* @description					eext_panel_add adds a panel to the window.
* @scenario					creates a new window.
*						adds a panel to the window
* @apicovered					eext_panel_add
* @passcase					when the panel is added successfully.
* @failcase					eext_panel_add fails.
* @precondition					None
* @postcondition				None
*/
//& purpose: Test eext_panel_add
//& type: auto
int ITc_eext_panel_add(void)
{
	START_TEST;

	Evas_Object *win = NULL;
	Evas_Object *panel=NULL;
	char *pszName = "window";

	win = CreateWin(pszName);
	CHECK_HANDLE(win,"CreateWin");

	panel = eext_panel_add(win);
	CHECK_HANDLE_CLEANUP(panel,"eext_panel_add", evas_object_del(win));

	evas_object_del(panel);
	evas_object_del(win);
	return 0;
}

/**
* @testcase					ITc_eext_panel_part_content_get_set
* @since_tizen					4.0
* @author					SRID(samuel.peter)
* @reviewer					SRID(nibha.sharma)
* @type						auto
* @description					eext_panel_part_content_get will get the content set by eext_panel_part_content_set.
* @scenario					creates a new window.
*						adds a panel to the window
*						adds a button to the panel
*						content in the panel is set using eext_panel_part_content_set
*						content in the panel is fetched using eext_panel_part_content_get
* @apicovered					eext_panel_add, eext_panel_part_content_set, eext_panel_part_content_get
* @passcase					When Set and Get values are same.
* @failcase					Set and Get values are not same or any preceding API fails
* @precondition					None
* @postcondition				None
*/
//& purpose: Test setting and getting the content in a panel part.
//& type: auto
int ITc_eext_panel_part_content_get_set(void)
{
	START_TEST;

	Evas_Object *win = NULL;
	Evas_Object *panel=NULL;
	Evas_Object *button=NULL;
	Evas_Object *retObj=NULL;
	char *pszName = "window";
	char *pszPartName = "primary";

	win = CreateWin(pszName);
	CHECK_HANDLE(win,"CreateWin");

	panel = eext_panel_add(win);
	CHECK_HANDLE_CLEANUP(panel,"eext_panel_add", evas_object_del(win));

	button = elm_button_add(panel);
	CHECK_HANDLE_CLEANUP(button,"elm_button_add", evas_object_del(panel);evas_object_del(win));

	eext_panel_part_content_set(panel, pszPartName, button);
	retObj = eext_panel_part_content_get(panel, pszPartName);
	CHECK_HANDLE_CLEANUP(retObj,"eext_panel_part_content_get", evas_object_del(button);evas_object_del(panel);evas_object_del(win));

	if(retObj != button)
	{
		FPRINTF("[Line : %d][%s] eext_panel_part_content_get returned incorrect panel.\\n", __LINE__, API_NAMESPACE);

		evas_object_del(retObj);
		evas_object_del(button);
		evas_object_del(panel);
		evas_object_del(win);
		return 1;
	}

	evas_object_del(retObj);
	evas_object_del(button);
	evas_object_del(panel);
	evas_object_del(win);
	return 0;
}

/**
* @testcase 			ITc_eext_more_option_editing_enable_set_get_p
* @since_tizen			4.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Test eext_more_option_editing_enable_set, eext_more_option_editing_enable_get
* @scenario				Call eext_more_option_editing_enable_set, eext_more_option_editing_enable_get
* @apicovered			eext_more_option_editing_enable_set, eext_more_option_editing_enable_get
* @passcase				When eext_more_option_editing_enable_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_editing_enable_set, eext_more_option_editing_enable_get
//& type: auto
int ITc_eext_more_option_editing_enable_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eina_Bool bEnable = EINA_FALSE;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	eext_more_option_editing_enabled_set(g_pMoreOption, EINA_TRUE);

	bEnable = eext_more_option_editing_enabled_get(g_pMoreOption);
	PRINT_RESULT_CLEANUP(EINA_TRUE, bEnable, "eext_more_option_editing_enabled_get", "Returned Value not correct", DeleteMoreOption());

	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_more_option_add_item_enabled_set_get_p
* @since_tizen			4.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Test eext_more_option_add_item_enabled_set, eext_more_option_add_item_enabled_get
* @scenario				Call eext_more_option_add_item_enabled_set, eext_more_option_add_item_enabled_get
* @apicovered			eext_more_option_add_item_enabled_set, eext_more_option_add_item_enabled_get
* @passcase				When eext_more_option_add_item_enabled_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_add_item_enabled_set, eext_more_option_add_item_enabled_get
//& type: auto
int ITc_eext_more_option_add_item_enabled_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eina_Bool bEnable = EINA_FALSE;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	eext_more_option_add_item_enabled_set(g_pMoreOption, EINA_TRUE);

	bEnable = eext_more_option_add_item_enabled_get(g_pMoreOption);
	PRINT_RESULT_CLEANUP(EINA_TRUE, bEnable, "eext_more_option_add_item_enabled_get", "Returned Value not correct", DeleteMoreOption());

	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_more_option_item_delete_enabled_set_get_p
* @since_tizen			4.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Test eext_more_option_item_delete_enabled_set, eext_more_option_item_delete_enabled_get
* @scenario				Call eext_more_option_item_delete_enabled_set, eext_more_option_item_delete_enabled_get
* @apicovered			eext_more_option_item_delete_enabled_set, eext_more_option_item_delete_enabled_get
* @passcase				When eext_more_option_item_delete_enabled_set is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_more_option_item_delete_enabled_set, eext_more_option_item_delete_enabled_get
//& type: auto
int ITc_eext_more_option_item_delete_enabled_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eina_Bool bEnable = EINA_FALSE;
	Eext_Object_Item *pObject = NULL;

	nRet = CreateMoreOption();
	PRINT_RESULT(0, nRet, "CreateMoreOption", "Returned Value not correct");

	pObject = eext_more_option_item_append(g_pMoreOption);
	CHECK_HANDLE_CLEANUP(pObject, "eext_more_option_item_append", DeleteMoreOption());

	eext_more_option_item_delete_enabled_set(pObject, EINA_TRUE);

	bEnable = eext_more_option_item_delete_enabled_get(pObject);
	PRINT_RESULT_CLEANUP(EINA_TRUE, bEnable, "eext_more_option_item_delete_enabled_get", "Returned Value not correct", DeleteMoreOption());

	DeleteMoreOption();

	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_editing_enabled_set_get_p
* @since_tizen			4.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Test eext_rotary_selector_editing_enabled_set, eext_rotary_selector_editing_enabled_get
* @scenario				Call eext_rotary_selector_editing_enabled_set, eext_rotary_selector_editing_enabled_get
* @apicovered			eext_rotary_selector_editing_enabled_set, eext_rotary_selector_editing_enabled_get
* @passcase				When eext_rotary_selector_editing_enabled_set and eext_rotary_selector_editing_enabled_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_editing_enabled_set, eext_rotary_selector_editing_enabled_get
//& type: auto
int ITc_eext_rotary_selector_editing_enabled_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eina_Bool bEnable = EINA_FALSE;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	eext_rotary_selector_editing_enabled_set(g_pCircleSelector, EINA_TRUE);

	bEnable = eext_rotary_selector_editing_enabled_get(g_pCircleSelector);
	PRINT_RESULT_CLEANUP(EINA_TRUE, bEnable, "eext_rotary_selector_editing_enabled_get", "Returned Value not correct", DeleteCircleSelector());

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_add_item_enabled_set_get_p
* @since_tizen			4.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Test eext_rotary_selector_add_item_enabled_set, eext_rotary_selector_add_item_enabled_get
* @scenario				Call eext_rotary_selector_add_item_enabled_set, eext_rotary_selector_add_item_enabled_get
* @apicovered			eext_rotary_selector_add_item_set, eext_rotary_selector_add_item_get
* @passcase				When eext_rotary_selector_add_item_enabled_set and eext_rotary_selector_add_item_enabled_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_add_item_enabled_set, eext_rotary_selector_add_item_enabled_get
//& type: auto
int ITc_eext_rotary_selector_add_item_enabled_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eina_Bool bEnable = EINA_FALSE;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	eext_rotary_selector_add_item_enabled_set(g_pCircleSelector, EINA_TRUE);

	bEnable = eext_rotary_selector_add_item_enabled_get(g_pCircleSelector);
	PRINT_RESULT_CLEANUP(EINA_TRUE, bEnable, "eext_rotary_selector_add_item_enabled_get", "Returned Value not correct", DeleteCircleSelector());

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase 			ITc_eext_rotary_selector_item_delete_enabled_set_get_p
* @since_tizen			4.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Test eext_rotary_selector_item_delete_enabled_set, eext_rotary_selector_item_delete_enabled_get
* @scenario				Call eext_rotary_selector_item_delete_enabled_set, eext_rotary_selector_item_delete_enabled_get
* @apicovered			eext_rotary_selector_item_delete_set, eext_rotary_selector_item_delete_get
* @passcase				When eext_rotary_selector_item_delete_enabled_set and eext_rotary_selector_item_delete_enabled_get is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test eext_rotary_selector_item_delete_enabled_set, eext_rotary_selector_item_delete_enabled_get
//& type: auto
int ITc_eext_rotary_selector_item_delete_enabled_set_get_p(void)
{
	START_TEST;

	int nRet = 0;
	Eina_Bool bEnable = EINA_FALSE;
	Eext_Object_Item *pObject = NULL;

	nRet = CreateCircleSelector();
	PRINT_RESULT(0, nRet, "CreateCircleSelector", "Returned Value not correct");

	pObject = eext_rotary_selector_item_append(g_pCircleSelector);
	CHECK_HANDLE_CLEANUP(pObject, "eext_rotary_selector_item_append", DeleteCircleSelector());

	eext_rotary_selector_item_delete_enabled_set(pObject, EINA_TRUE);

	bEnable = eext_rotary_selector_item_delete_enabled_get(pObject);
	PRINT_RESULT_CLEANUP(EINA_TRUE, bEnable, "eext_rotary_selector_item_delete_enabled_get", "Returned Value not correct", DeleteCircleSelector());

	DeleteCircleSelector();
	return 0;
}

/**
* @testcase		ITc_eext_rotary_event_activated_object_get_p
* @since_tizen		5.5
* @author		SRID(j.abhishek)
* @reviewer		SRID(shobhit.v)
* @type		auto
* @description		Get the activated object which can receive the current rotary event
* @scenario		get return object, should be non NULL
* @apicovered		eext_rotary_event_activated_object_get
* @passcase		When eext_rotary_event_activated_object_get is successful.
* @failcase		If target API fails or any precondition API fails
* @precondition	None
* @postcondition	None
*/
//& purpose: Get the activated object which can receive the current rotary event
//& type: auto
int ITc_eext_rotary_event_activated_object_get_p(void)
{
        START_TEST;

        Evas_Object *h_win = NULL;
        Eext_Circle_Surface *surface = NULL;
        Evas_Object *pCircle = NULL;
        Evas_Object *pszActiveObj = NULL;
        char *pszName = "window";

        h_win = CreateWin(pszName);
        CHECK_HANDLE(h_win,"CreateWin");

        pCircle = eext_circle_object_slider_add(h_win, surface);
        CHECK_HANDLE_CLEANUP(pCircle, "eext_circle_object_slider_add", evas_object_del(h_win));

        eext_rotary_object_event_activated_set(pCircle, EINA_TRUE);
        pszActiveObj = eext_rotary_event_activated_object_get();

        PRINT_RESULT_CLEANUP(pszActiveObj, pCircle, "eext_rotary_event_activated_object_get", "values are not correct", evas_object_del(pCircle); evas_object_del(h_win));
        evas_object_del(pCircle);
        evas_object_del(h_win);

        return 0;
}

/**
* @testcase		ITc_eext_popup_add_p
* @since_tizen		5.5
* @author		SRID(j.abhishek)
* @reviewer		SRID(shobhit.v)
* @type		auto
* @description		Eext Popup has a circle scroller and the content of Eext Popup
*			is controlled by rotary event.
* @scenario		Creating window and add popup.
* @apicovered		eext_popup_add
* @passcase		eext_popup_add API created popup is not NULL
* @failcase		eext_popup_add API returned NULL or any precondition API fails
* @precondition	None
* @postcondition	None
*/
//& purpose: Eext Popup has a circle scroller and the content of Eext Popup is controlled by rotary event
//& type: auto
int ITc_eext_popup_add_p(void)
{
	START_TEST;
	Evas_Object *hWindow = NULL;
	Evas_Object *hPopup = NULL;

	hWindow = CreateWin("window");
	CHECK_HANDLE(hWindow, "CreateWin");

	// Target API
	hPopup =  eext_popup_add(hWindow);
	CHECK_HANDLE_CLEANUP(hPopup, "eext_popup_add", evas_object_del(hWindow));

	evas_object_del(hWindow);

	return 0;
}
#endif  //WEARABLE	//End WEARABLE

/** @} */
/** @} */
