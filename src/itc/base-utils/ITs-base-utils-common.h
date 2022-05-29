//
// Copyright (c) 2018 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef _ITS_BASE_UTILS_COMMON_H_
#define _ITS_BASE_UTILS_COMMON_H_

#include "tct_common.h"

//Add test package related includes here
#include <app_common.h>
#include <uchar.h>
#include <glib.h>
#include <stdbool.h>
#include <utils_i18n.h>
#include <utils_i18n_date_interval_format.h>
#include <math.h>
#include <string.h>

/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/

//#define ms2sec(ms) (long long int)(ms)/1000.0
#define BUFFER								256
#define API_NAMESPACE						"BASE_UTILS_ITC"
#define LOCALE								I18N_ULOCALE_US
#define I18N_RESULT_LEN						100
#define I18N_LANG_CAPACITY					64
#define I18N_ULOCALE_CAPACITY				64
#define I18N_DEFAULT_T_ZONE 				"Etc/GMT"
#define I18N_DATE_TIME_CUSTOM_FORMAT		"yyyy.MM.dd G 'at' HH:mm:ss zzz"
#define I18N_DATEPG_BEST_PATTERN_CAPACITY	64
#define I18N_FORMATED_DATE_CAPACITY			64
#define I18N_UCHAR_CAPACITY					256
#define UNKNOWN_RESULT_VALUE				"Unknown Result"
#define UCALENDER_AMOUNT_VALUE				10
#define YEAR_VALUE							2014
#define MONTH_VALUE							9
#define DATE_VALUE							11
#define HOUR_VALUE							18
#define MINUTE_VALUE						35
#define SEC_VALUE							20
#define YEAR_FROM_VALUE						2000
#define SOURCE_STRING						"Test TIZEN"
#define USEARCH_KEYWORD						"TI"
#define USEARCH_MATCHED_POSITION			5
#define USEARCH_MATCHED_LENGTH				2
#define UNORMALIZATION_NFC_NAME				"nfkc"
#define I18N_UNUMBER_SYMBOL_CAPACITY		64
#define I18N_DATEPG_PATTERN_CAPACITY		64
#define I18N_LOCALE_ID						"zh_Hans_HK_USD@currency=USD;president=WHO"

#define TIMEOUT_CB				10000
GMainLoop *g_pBaseUtilsMainLoop;
bool g_bCallbackHit;

static i18n_simple_date_fmt_h g_hDateFmt = NULL;
static i18n_ucalendar_h g_hCalendar = NULL;
static const char *g_pszPattern = "EEE, MMM d, yyyy";
static const char *g_pszOverride = "y=hanidec;M=hans;d=hans";
static const char *g_pszLocale = "en_US";
static i18n_uidna_h h_uidna = NULL;
static i18n_ucharset_detector_h g_hUcsd = NULL;
static i18n_uconverter_selector_h g_UconvSel = NULL;
static i18n_uset_h g_hUcnvExcludedSet = NULL;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n",__LINE__, API_NAMESPACE,__FUNCTION__);\
	if ( !g_bBaseUtilsInitFlag )\
	{\
	FPRINTF("[Line : %d][%s] Precondition of Base-Utils create pkglist failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
}

#define START_TEST_PRINT {\
	FPRINTF("\\n[Line : %d][%s] Starting test : %s\\n",__LINE__, API_NAMESPACE,__FUNCTION__);\
}

#define CHECK_RETURN_VAL(nVal, API) {\
	if(nVal < 0)\
	{\
		FPRINTF("\\n[Line : %d][%s] %s failed, return value is less than zero \n", __LINE__, API_NAMESPACE, API);\
		return 1;\
	}\
}

#define CHECK_RETURN_ENUM_VAL(EnumMin, EnumMax, API) {\
	if(nRetVal < EnumMin || nRetVal > EnumMax)\
	{\
		FPRINTF("\\n[Line : %d][%s] %s failed, error returned = invalid return type \n", __LINE__, API_NAMESPACE, API);\
		return 1;\
	}\
}

#define CHECK_RETURN_VAL_CLEANUP(nVal, API,FreeResource) {\
	if(nVal < 0)\
	{\
		FPRINTF("\\n[Line : %d][%s] %s failed, return value is less than zero \n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#define FREE_MEMORY1(MEM1) {\
	if(MEM1 != NULL) \
	{\
		free(MEM1);\
		MEM1 = NULL;\
	}\
}

#define RUN_POLLING_LOOP {\
	if ( !g_bCallbackHit )\
{\
	g_pBaseUtilsMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, baseUtilTimeout, g_pBaseUtilsMainLoop);\
	g_main_loop_run(g_pBaseUtilsMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pBaseUtilsMainLoop = NULL;\
}\
}

gboolean baseUtilTimeout(gpointer data);
bool g_bBaseUtilsInitFlag;
i18n_date_interval_h g_dateInterval;
i18n_date_interval_fmt_h g_date_int_fmt;
const char *g_pszDefaultLocale;
i18n_uchar *g_pDefaultTzid;
int g_nLengthDefaultTimeZone;
char* BaseUtilsGetError(int nRet);
char* uCharPropertyName(int nRet);
char *uCharBlockCode(int nRet);
char* UcalenderGetAttributeType(int nRet);
char* UnormalizationModeValue(int nRet);
char* UcalenderGetType(int nRet);
char* UcalenderGetDisplayNameType(int nRet);
char* UcalenderDateFieldValue(int nRet);
char* UcollatorAttributes(int nRet);
char* UcollatorStrengthValues(int nRet);
char* UnumberGetFormatSymbol(int nRet);
char* UnumberGetFormatStyle(int nRet);
char* UdateGetFormatStyle(int nRet);
char* UcollatorResult(int nRet);
char* UcalendarGetTimezoneType(int nRet);
char* UcalendarGetLimitType(int nRet);
char* UcalendarGetLocaleType(int nRet);
char* UcalendarGetDaysOfWeek(int nRet);
char* UcalendarGetTimezoneTransitionType(int nRet);
char* UdateGetDateFormatFieldValue(int nRet);
char* UdateGetFormatSymbolType(int nRet);
char* UdateGetDisplayContext(int nRet);
char* UbrkGetIteratorType(int nRet);
char* UdatepgGetDateTimePatternField(int nRet);
char* UdatepgGetDateTimePatternMatchField(int nRet);
char* UnumberGetFormatAttr(int nRet);
char* UnumberGetFormatTextAttr(int nRet);
int32_t UcsdetGetPreFlight(const i18n_uchar *src, int32_t length, i18n_ucnv_h cnv);
char *UcsdetGetBytes(const i18n_uchar *src, int32_t length, const char *codepage, int32_t *byte_length);
/** @} */
#endif  //_ITS_BASE_UTILS_COMMON_H_
