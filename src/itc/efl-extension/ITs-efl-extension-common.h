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
#ifndef _ITS_EFL_EXT_COMMON_H_
#define _ITS_EFL_EXT_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include "assert.h"
#include <fcntl.h>
#include <Ecore.h>
#include <efl_extension.h>
//#include <appcore-efl.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <system_info.h>
#include <app.h>

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

//Common Macros
#define API_NAMESPACE				"EFL_EXT_ITC"
#define PACKAGE 					"EFL_EXT_ITC"
#define KEY_VOLUMEUP 				"XF86AudioRaiseVolume"

#ifdef TV	//Starts TV
#define KEY_POWEROFF 				"XF86PowerOff"
#endif  //End TV


#ifdef WEARABLE	//Starts WEARABLE
#define TESTSTRING					"TestTizen"

#define FPRINTF(...) {\
	g_fpLog = fopen(ERR_LOG, "a");\
	fprintf(g_fpLog, __VA_ARGS__);\
	fclose(g_fpLog);\
}
#endif  //End WEARABLE


#ifdef TV	//Starts TV
#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}
#endif  //End TV

#if defined  (MOBILE ) || defined  (TIZENIOT)	//Starts MOBILE
#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}
#endif  //MOBILE OR TIZENIOT

#ifdef WEARABLE	//Starts WEARABLE
#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bEflExtCreation )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of efl-extension failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}
#endif  //End WEARABLE

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#ifdef WEARABLE	//Starts WEARABLE

#define PRINT_RESULT(eCompare, eRetVal, API, Error) {\
	if ( eRetVal == eCompare )\
	{\
		if ( DEBUG )\
		{\
			FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
		}\
	}\
	else \
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, (int)eRetVal);\
		return 1;\
	}\
}

#define PRINT_RESULT_CLEANUP(eCompare, eRetVal, API, Error, FreeResource) {\
	if ( eRetVal == eCompare )\
	{\
		if ( DEBUG )\
		{\
			FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
		}\
	}\
	else \
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, (int)eRetVal);\
		FreeResource;\
		return 1;\
	}\
}

#define CHECK_HANDLE(Handle, API) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		return 1;\
	}\
}
#endif  //End WEARABLE

#ifdef WEARABLE	//Starts WEARABLE
FILE *g_fpLog;
bool g_bEflExtCreation;
Evas *g_pEvasCore;
Eext_Circle_Surface *g_pCircleSurfaceLayout;
Evas_Object *g_pSpinner;
Evas_Object *g_pScroller;
Evas_Object *g_pGenlist;
Evas_Object *g_pCircleObject;
Evas_Object *g_pCircleGenlist;
Evas_Object *g_pCircleScroller;
Evas_Object *g_pCircleSlider;
Evas_Object *g_pMoreOption;
Evas_Object *g_pCircleSelector;
Evas_Object *g_pImageObject;
Evas_Object *g_pCircleSpinner;
Elm_Object_Item *g_pEvasItem;
Eext_Object_Item *g_pEextItem;
#endif  //End WEARABLE

Evas_Object *g_pEvasWindow;
Evas_Object *g_pElmWindow;
Evas_Object *g_pEvasConformant;
Evas_Object *g_pEvasLayout;
Evas_Object *g_pEvasNaviframe;
void WinDel(void *data, Evas_Object *obj, void *event);
bool CreateEvasWindow(void);
void DeleteEvasWindow(void);

#if defined  (MOBILE ) || defined  (TIZENIOT) || defined (TV)//Starts MOBILE OR TIZENIOT
Evas_Object *g_pFloatingButton;
bool CreateFloatingButon();
char* EflExtGetFloatingButtonModeType(Eext_Floatingbutton_Mode eMode);
char* EflExtGetFloatingButtonPosType(Eext_Floatingbutton_Pos ePos);
#endif  //MOBILE OR TIZENIOT

#ifdef WEARABLE	//Starts WEARABLE
Evas_Object *g_pFloatingButton;
bool CreateCircleSurfaceLayout(void);
void DeleteCircleSurfaceLayout(void);
bool CreateCircle(void);
void DeleteCircle(void);
bool CreateCircleGenlist(void);
void DeleteCircleGenlist(void);
bool CreateCircleScroller(void);
void DeleteCircleScroller(void);
bool CreateCircleSlider(void);
void DeleteCircleSlider(void);
bool CreateMoreOption(void);
void DeleteMoreOption(void);
bool CreateCircleSelector(void);
void DeleteCircleSelector(void);
bool CreateCircleSpinner(void);
void DeleteCircleSpinner(void);
Evas_Object* CreateElmWindow(const char *WinName);
#endif  //End WEARABLE

/** @} */
#endif  //_ITS_EFL_EXT_COMMON_H_
