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
#ifndef __TCT_DALI-ADAPTOR-NATIVE_H__
#define __TCT_DALI-ADAPTOR-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_Dali_Timer_startup(void);
extern void utc_Dali_Timer_cleanup(void);
extern void utc_Dali_Window_startup(void);
extern void utc_Dali_Window_cleanup(void);
extern void utc_Dali_NativeImageSource_startup(void);
extern void utc_Dali_NativeImageSource_cleanup(void);
extern void utc_Dali_Key_startup(void);
extern void utc_Dali_Key_cleanup(void);
extern void utc_Dali_TtsPlayer_startup(void);
extern void utc_Dali_TtsPlayer_cleanup(void);
extern void utc_Dali_Application_startup(void);
extern void utc_Dali_Application_cleanup(void);
extern void utc_dali_watchapplication_startup(void);
extern void utc_dali_watchapplication_cleanup(void);
extern void utc_dali_watchtime_startup(void);
extern void utc_dali_watchtime_cleanup(void);
extern void utc_Dali_Capture_startup(void);
extern void utc_Dali_Capture_cleanup(void);

extern int UtcDaliTimerNewP(void);
extern int UtcDaliTimerSetGetIntervalP(void);
extern int UtcDaliTimerStartStopP(void);
extern int UtcDaliTimerAssignmentOperatorP(void);
extern int UtcDaliTimerTickSignalP(void);
extern int UtcDaliTimerCopyConstructorP(void);
extern int UtcDaliTimerConstructorP(void);
extern int UtcDaliTimerDowncastP(void);
extern int UtcDaliTimerDowncastN(void);
extern int UtcDaliTimerIsRunningP(void);
extern int UtcDaliTimerSetGetIntervalP2(void);
extern int UtcDaliTimerSetGetIntervalP3(void);
extern int UtcDaliWindowNewP(void);
extern int UtcDaliWindowNewP2(void);
extern int UtcDaliWindowIndicatorVisibilityChangeP(void);
extern int UtcDaliWindowConstructorP(void);
extern int UtcDaliWindowCopyConstructorP(void);
extern int UtcDaliWindowSetClassP(void);
extern int UtcDaliWindowConstructorNewAssignmentOperatorP(void);
extern int UtcDaliWindowSetPreferredOrientationP(void);
extern int UtcDaliWindowGetPreferredOrientationP(void);
extern int UtcDaliWindowGetNativeHandleP(void);
extern int UtcDaliWindowAddAvailableOrientationN(void);
extern int UtcDaliWindowRemoveAvailableOrientationN(void);
extern int UtcDaliWindowLowerP(void);
extern int UtcDaliWindowRaiseP(void);
extern int UtcDaliWindowActivateP(void);
extern int UtcDaliWindowSetClassSetIndicatorBgOpacityP(void);
extern int UtcDaliWindowShowIndicatorP(void);
extern int UtcDaliWindowRotateIndicatorP(void);
extern int UtcDaliWindowIndicatorVisibilityChangedSignalP(void);
extern int UtcDaliWindowSetAcceptFocusIsFocusAcceptableP(void);
extern int UtcDaliWindowShowHideIsVisibleP(void);
extern int UtcDaliWindowAuxiliaryHintTestP(void);
extern int UtcDaliWindowSetGetTypeP(void);
extern int UtcDaliWindowSetGetNotificationLevelP(void);
extern int UtcDaliWindowSetOpaqueStateIsOpaqueStateP(void);
extern int UtcDaliWindowSetGetScreenOffModeP(void);
extern int UtcDaliWindowSetGetBrightnessP(void);
extern int UtcDaliWindowSetGetSizeResizedSignalP(void);
extern int UtcDaliWindowSetGetSizeResizedSignalP2(void);
extern int UtcDaliWindowSetGetPositionP(void);
extern int UtcWindowAddRemoveActorP(void);
extern int UtcWindowSetGetBackgroundColorP(void);
extern int UtcWindowGetRootLayerP(void);
extern int UtcWindowGetLayerCountP(void);
extern int UtcWindowGetLayerP(void);
extern int UtcDaliNativeImageSourceColorDepthDefaultP(void);
extern int UtcDaliNativeImageSourceColorDepth24P(void);
extern int UtcDaliNativeImageSourceColorDepth32P(void);
extern int UtcDaliNativeImageSourceGetNativeImageSourceP(void);
extern int UtcDaliNativeImageSourceGetNativeImageSourceN(void);
extern int UtcDaliNativeImageSourceNewN(void);
extern int UtcDaliNativeImageSourceNewP(void);
extern int UtcDaliNativeImageSourceNewAnyP(void);
extern int UtcDaliNativeImageSourceEncodeToFileP(void);
extern int UtcDaliNativeImageSourceGetPixelsN(void);
extern int UtcDaliNativeImageSourceGetPixelsP(void);
extern int UtcDaliNativeImageSourceSetSourceP(void);
extern int UtcDaliNativeImageSourceIsColorDepthSupportedP(void);
extern int UtcDaliIsKeyP(void);
extern int UtcDaliTtsPlayerConstructorP(void);
extern int UtcDaliTtsPlayerCopyConstructorP(void);
extern int UtcDaliTtsPlayerAssignmentOperatorP(void);
extern int UtcDaliTtsPlayerGetP(void);
extern int UtcDaliTtsPlayerResumeN(void);
extern int UtcDaliTtsPlayerPlayN(void);
extern int UtcDaliTtsPlayerPauseN(void);
extern int UtcDaliTtsPlayerStopN(void);
extern int UtcDaliTtsPlayerGetStateN(void);
extern int UtcDaliApplicationCopyConstructorP(void);
extern int UtcDaliApplicationConstructorP(void);
extern int UtcDaliApplicationCopyAndAssignmentP(void);
extern int UtcDaliApplicationMainLoopN(void);
extern int UtcDaliApplicationMainLoopContextLossP(void);
extern int UtcDaliApplicationLowerN(void);
extern int UtcDaliApplicationQuitN(void);
extern int UtcDaliApplicationAddIdleN(void);
extern int UtcDaliApplicationAddIdleP(void);
extern int UtcDaliApplicationGetWindowN(void);
extern int UtcDaliApplicationGetWindowP(void);
extern int UtcDaliApplicationReplaceWindowP(void);
extern int UtcDaliApplicationReplaceWindowN(void);
extern int UtcDaliApplicationSetViewModeN(void);
extern int UtcDaliApplicationGetViewModeN(void);
extern int UtcDaliApplicationViewModeSetAndGetP(void);
extern int UtcDaliApplicationStereoBaseSetAndGetP(void);
extern int UtcDaliApplicationSetStereoBaseN(void);
extern int UtcDaliApplicationGetStereoBaseN(void);
extern int UtcDaliApplicationTerminateSignalP(void);
extern int UtcDaliApplicationTerminateSignalN(void);
extern int UtcDaliApplicationPauseSignalP(void);
extern int UtcDaliApplicationPauseSignalN(void);
extern int UtcDaliApplicationResumeSignalP(void);
extern int UtcDaliApplicationResumeSignalN(void);
extern int UtcDaliApplicationResetSignalP(void);
extern int UtcDaliApplicationResetSignalN(void);
extern int UtcDaliApplicationResizeSignalP(void);
extern int UtcDaliApplicationResizeSignalN(void);
extern int UtcDaliApplicationlControlSignalP(void);
extern int UtcDaliApplicationlControlSignalN(void);
extern int UtcDaliApplicationLanguageChangedSignalP(void);
extern int UtcDaliApplicationLanguageChangedSignalN(void);
extern int UtcDaliApplicationRegionChangedSignalP(void);
extern int UtcDaliApplicationRegionChangedSignalN(void);
extern int UtcDaliApplicationBatteryLowSignalP(void);
extern int UtcDaliApplicationBatteryLowSignalN(void);
extern int UtcDaliApplicationInitSignalP(void);
extern int UtcDaliApplicationInitSignalN(void);
extern int UtcDaliApplicationMemoryLowSignalP(void);
extern int UtcDaliApplicationMemoryLowSignalN(void);
extern int UtcDaliApplicationNewP(void);
extern int UtcDaliApplicationNewP2(void);
extern int UtcDaliApplicationNewP3(void);
extern int UtcDaliApplicationNewP4(void);
extern int UtcDaliApplicationNewP5(void);
extern int UtcDaliApplicationNewP6(void);
extern int UtcDaliApplicationGetResourcePathP(void);
extern int UtcDaliApplicationGetRegionP(void);
extern int UtcDaliApplicationGetLanguageP(void);
extern int UtcDaliApplicationLowBatterySignalP(void);
extern int UtcDaliApplicationLowBatterySignalN(void);
extern int UtcDaliApplicationLowMemorySignalP(void);
extern int UtcDaliApplicationLowMemorySignalN(void);
extern int UtcDaliWatchApplicationNew01(void);
extern int UtcDaliWatchApplicationNew02(void);
extern int UtcDaliWatchApplicationNew03(void);
extern int UtcDaliWatchApplicationCopyAndAssignment(void);
extern int UtcDaliWatchApplicationTimeTickSignalP(void);
extern int UtcDaliWatchApplicationTimeTickSignalN(void);
extern int UtcDaliWatchApplicationAmbientTickSignalP(void);
extern int UtcDaliWatchApplicationAmbientTickSignalN(void);
extern int UtcDaliWatchApplicationAmbientChangedSignalP(void);
extern int UtcDaliWatchApplicationAmbientChangedSignalN(void);
extern int UtcDaliWatchTimeNew(void);
extern int UtcDaliWatchTimeGetHour(void);
extern int UtcDaliWatchTimeGetHour24(void);
extern int UtcDaliWatchTimeGetMinute(void);
extern int UtcDaliWatchTimeGetSecond(void);
extern int UtcDaliWatchTimeGetMillisecond(void);
extern int UtcDaliWatchTimeGetYear(void);
extern int UtcDaliWatchTimeGetMonth(void);
extern int UtcDaliWatchTimeGetDay(void);
extern int UtcDaliWatchTimeGetDayOfWeek(void);
extern int UtcDaliWatchTimeGetUtcTime(void);
extern int UtcDaliWatchTimeGetUtcTimeStamp(void);
extern int UtcDaliWatchTimeGetTimeZone(void);
extern int UtcDaliWatchTimeGetDaylightSavingTimeStatus(void);
extern int UtcDaliCaptureConstructorP(void);
extern int UtcDaliCaptureNewP(void);
extern int UtcDaliCaptureNewCameraP(void);
extern int UtcDaliCaptureAssignmentP(void);
extern int UtcDaliCaptureDownCastP(void);
extern int UtcDaliCaptureStartP(void);
extern int UtcDaliCaptureStartColorP(void);
extern int UtcDaliCaptureStartColorAndQualityP(void);
extern int UtcDaliCaptureReturnNativeImageSourceP(void);
extern int UtcDaliCaptureStartColorAndQualityN(void);
extern int UtcDaliCaptureReturnNativeImageSourceN(void);
extern int UtcDaliCaptureFinishedN(void);

testcase tc_array[] = {
	{"UtcDaliTimerNewP",UtcDaliTimerNewP,utc_Dali_Timer_startup,utc_Dali_Timer_cleanup},
	{"UtcDaliTimerSetGetIntervalP",UtcDaliTimerSetGetIntervalP,utc_Dali_Timer_startup,utc_Dali_Timer_cleanup},
	{"UtcDaliTimerStartStopP",UtcDaliTimerStartStopP,utc_Dali_Timer_startup,utc_Dali_Timer_cleanup},
	{"UtcDaliTimerAssignmentOperatorP",UtcDaliTimerAssignmentOperatorP,utc_Dali_Timer_startup,utc_Dali_Timer_cleanup},
	{"UtcDaliTimerTickSignalP",UtcDaliTimerTickSignalP,utc_Dali_Timer_startup,utc_Dali_Timer_cleanup},
	{"UtcDaliTimerCopyConstructorP",UtcDaliTimerCopyConstructorP,utc_Dali_Timer_startup,utc_Dali_Timer_cleanup},
	{"UtcDaliTimerConstructorP",UtcDaliTimerConstructorP,utc_Dali_Timer_startup,utc_Dali_Timer_cleanup},
	{"UtcDaliTimerDowncastP",UtcDaliTimerDowncastP,utc_Dali_Timer_startup,utc_Dali_Timer_cleanup},
	{"UtcDaliTimerDowncastN",UtcDaliTimerDowncastN,utc_Dali_Timer_startup,utc_Dali_Timer_cleanup},
	{"UtcDaliTimerIsRunningP",UtcDaliTimerIsRunningP,utc_Dali_Timer_startup,utc_Dali_Timer_cleanup},
	{"UtcDaliTimerSetGetIntervalP2",UtcDaliTimerSetGetIntervalP2,utc_Dali_Timer_startup,utc_Dali_Timer_cleanup},
	{"UtcDaliTimerSetGetIntervalP3",UtcDaliTimerSetGetIntervalP3,utc_Dali_Timer_startup,utc_Dali_Timer_cleanup},
	{"UtcDaliWindowNewP",UtcDaliWindowNewP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowNewP2",UtcDaliWindowNewP2,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowIndicatorVisibilityChangeP",UtcDaliWindowIndicatorVisibilityChangeP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowConstructorP",UtcDaliWindowConstructorP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowCopyConstructorP",UtcDaliWindowCopyConstructorP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowSetClassP",UtcDaliWindowSetClassP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowConstructorNewAssignmentOperatorP",UtcDaliWindowConstructorNewAssignmentOperatorP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowSetPreferredOrientationP",UtcDaliWindowSetPreferredOrientationP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowGetPreferredOrientationP",UtcDaliWindowGetPreferredOrientationP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowGetNativeHandleP",UtcDaliWindowGetNativeHandleP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowAddAvailableOrientationN",UtcDaliWindowAddAvailableOrientationN,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowRemoveAvailableOrientationN",UtcDaliWindowRemoveAvailableOrientationN,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowLowerP",UtcDaliWindowLowerP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowRaiseP",UtcDaliWindowRaiseP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowActivateP",UtcDaliWindowActivateP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowSetClassSetIndicatorBgOpacityP",UtcDaliWindowSetClassSetIndicatorBgOpacityP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowShowIndicatorP",UtcDaliWindowShowIndicatorP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowRotateIndicatorP",UtcDaliWindowRotateIndicatorP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowIndicatorVisibilityChangedSignalP",UtcDaliWindowIndicatorVisibilityChangedSignalP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowSetAcceptFocusIsFocusAcceptableP",UtcDaliWindowSetAcceptFocusIsFocusAcceptableP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowShowHideIsVisibleP",UtcDaliWindowShowHideIsVisibleP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowAuxiliaryHintTestP",UtcDaliWindowAuxiliaryHintTestP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowSetGetTypeP",UtcDaliWindowSetGetTypeP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowSetGetNotificationLevelP",UtcDaliWindowSetGetNotificationLevelP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowSetOpaqueStateIsOpaqueStateP",UtcDaliWindowSetOpaqueStateIsOpaqueStateP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowSetGetScreenOffModeP",UtcDaliWindowSetGetScreenOffModeP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowSetGetBrightnessP",UtcDaliWindowSetGetBrightnessP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowSetGetSizeResizedSignalP",UtcDaliWindowSetGetSizeResizedSignalP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowSetGetSizeResizedSignalP2",UtcDaliWindowSetGetSizeResizedSignalP2,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliWindowSetGetPositionP",UtcDaliWindowSetGetPositionP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcWindowAddRemoveActorP",UtcWindowAddRemoveActorP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcWindowSetGetBackgroundColorP",UtcWindowSetGetBackgroundColorP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcWindowGetRootLayerP",UtcWindowGetRootLayerP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcWindowGetLayerCountP",UtcWindowGetLayerCountP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcWindowGetLayerP",UtcWindowGetLayerP,utc_Dali_Window_startup,utc_Dali_Window_cleanup},
	{"UtcDaliNativeImageSourceColorDepthDefaultP",UtcDaliNativeImageSourceColorDepthDefaultP,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliNativeImageSourceColorDepth24P",UtcDaliNativeImageSourceColorDepth24P,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliNativeImageSourceColorDepth32P",UtcDaliNativeImageSourceColorDepth32P,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliNativeImageSourceGetNativeImageSourceP",UtcDaliNativeImageSourceGetNativeImageSourceP,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliNativeImageSourceGetNativeImageSourceN",UtcDaliNativeImageSourceGetNativeImageSourceN,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliNativeImageSourceNewN",UtcDaliNativeImageSourceNewN,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliNativeImageSourceNewP",UtcDaliNativeImageSourceNewP,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliNativeImageSourceNewAnyP",UtcDaliNativeImageSourceNewAnyP,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliNativeImageSourceEncodeToFileP",UtcDaliNativeImageSourceEncodeToFileP,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliNativeImageSourceGetPixelsN",UtcDaliNativeImageSourceGetPixelsN,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliNativeImageSourceGetPixelsP",UtcDaliNativeImageSourceGetPixelsP,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliNativeImageSourceSetSourceP",UtcDaliNativeImageSourceSetSourceP,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliNativeImageSourceIsColorDepthSupportedP",UtcDaliNativeImageSourceIsColorDepthSupportedP,utc_Dali_NativeImageSource_startup,utc_Dali_NativeImageSource_cleanup},
	{"UtcDaliIsKeyP",UtcDaliIsKeyP,utc_Dali_Key_startup,utc_Dali_Key_cleanup},
	{"UtcDaliTtsPlayerConstructorP",UtcDaliTtsPlayerConstructorP,utc_Dali_TtsPlayer_startup,utc_Dali_TtsPlayer_cleanup},
	{"UtcDaliTtsPlayerCopyConstructorP",UtcDaliTtsPlayerCopyConstructorP,utc_Dali_TtsPlayer_startup,utc_Dali_TtsPlayer_cleanup},
	{"UtcDaliTtsPlayerAssignmentOperatorP",UtcDaliTtsPlayerAssignmentOperatorP,utc_Dali_TtsPlayer_startup,utc_Dali_TtsPlayer_cleanup},
	{"UtcDaliTtsPlayerGetP",UtcDaliTtsPlayerGetP,utc_Dali_TtsPlayer_startup,utc_Dali_TtsPlayer_cleanup},
	{"UtcDaliTtsPlayerResumeN",UtcDaliTtsPlayerResumeN,utc_Dali_TtsPlayer_startup,utc_Dali_TtsPlayer_cleanup},
	{"UtcDaliTtsPlayerPlayN",UtcDaliTtsPlayerPlayN,utc_Dali_TtsPlayer_startup,utc_Dali_TtsPlayer_cleanup},
	{"UtcDaliTtsPlayerPauseN",UtcDaliTtsPlayerPauseN,utc_Dali_TtsPlayer_startup,utc_Dali_TtsPlayer_cleanup},
	{"UtcDaliTtsPlayerStopN",UtcDaliTtsPlayerStopN,utc_Dali_TtsPlayer_startup,utc_Dali_TtsPlayer_cleanup},
	{"UtcDaliTtsPlayerGetStateN",UtcDaliTtsPlayerGetStateN,utc_Dali_TtsPlayer_startup,utc_Dali_TtsPlayer_cleanup},
	{"UtcDaliApplicationCopyConstructorP",UtcDaliApplicationCopyConstructorP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationConstructorP",UtcDaliApplicationConstructorP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationCopyAndAssignmentP",UtcDaliApplicationCopyAndAssignmentP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationMainLoopN",UtcDaliApplicationMainLoopN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationMainLoopContextLossP",UtcDaliApplicationMainLoopContextLossP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationLowerN",UtcDaliApplicationLowerN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationQuitN",UtcDaliApplicationQuitN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationAddIdleN",UtcDaliApplicationAddIdleN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationAddIdleP",UtcDaliApplicationAddIdleP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationGetWindowN",UtcDaliApplicationGetWindowN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationGetWindowP",UtcDaliApplicationGetWindowP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationReplaceWindowP",UtcDaliApplicationReplaceWindowP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationReplaceWindowN",UtcDaliApplicationReplaceWindowN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationSetViewModeN",UtcDaliApplicationSetViewModeN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationGetViewModeN",UtcDaliApplicationGetViewModeN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationViewModeSetAndGetP",UtcDaliApplicationViewModeSetAndGetP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationStereoBaseSetAndGetP",UtcDaliApplicationStereoBaseSetAndGetP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationSetStereoBaseN",UtcDaliApplicationSetStereoBaseN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationGetStereoBaseN",UtcDaliApplicationGetStereoBaseN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationTerminateSignalP",UtcDaliApplicationTerminateSignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationTerminateSignalN",UtcDaliApplicationTerminateSignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationPauseSignalP",UtcDaliApplicationPauseSignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationPauseSignalN",UtcDaliApplicationPauseSignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationResumeSignalP",UtcDaliApplicationResumeSignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationResumeSignalN",UtcDaliApplicationResumeSignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationResetSignalP",UtcDaliApplicationResetSignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationResetSignalN",UtcDaliApplicationResetSignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationResizeSignalP",UtcDaliApplicationResizeSignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationResizeSignalN",UtcDaliApplicationResizeSignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationlControlSignalP",UtcDaliApplicationlControlSignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationlControlSignalN",UtcDaliApplicationlControlSignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationLanguageChangedSignalP",UtcDaliApplicationLanguageChangedSignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationLanguageChangedSignalN",UtcDaliApplicationLanguageChangedSignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationRegionChangedSignalP",UtcDaliApplicationRegionChangedSignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationRegionChangedSignalN",UtcDaliApplicationRegionChangedSignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationBatteryLowSignalP",UtcDaliApplicationBatteryLowSignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationBatteryLowSignalN",UtcDaliApplicationBatteryLowSignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationInitSignalP",UtcDaliApplicationInitSignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationInitSignalN",UtcDaliApplicationInitSignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationMemoryLowSignalP",UtcDaliApplicationMemoryLowSignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationMemoryLowSignalN",UtcDaliApplicationMemoryLowSignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationNewP",UtcDaliApplicationNewP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationNewP2",UtcDaliApplicationNewP2,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationNewP3",UtcDaliApplicationNewP3,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationNewP4",UtcDaliApplicationNewP4,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationNewP5",UtcDaliApplicationNewP5,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationNewP6",UtcDaliApplicationNewP6,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationGetResourcePathP",UtcDaliApplicationGetResourcePathP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationGetRegionP",UtcDaliApplicationGetRegionP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationGetLanguageP",UtcDaliApplicationGetLanguageP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationLowBatterySignalP",UtcDaliApplicationLowBatterySignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationLowBatterySignalN",UtcDaliApplicationLowBatterySignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationLowMemorySignalP",UtcDaliApplicationLowMemorySignalP,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliApplicationLowMemorySignalN",UtcDaliApplicationLowMemorySignalN,utc_Dali_Application_startup,utc_Dali_Application_cleanup},
	{"UtcDaliWatchApplicationNew01",UtcDaliWatchApplicationNew01,utc_dali_watchapplication_startup,utc_dali_watchapplication_cleanup},
	{"UtcDaliWatchApplicationNew02",UtcDaliWatchApplicationNew02,utc_dali_watchapplication_startup,utc_dali_watchapplication_cleanup},
	{"UtcDaliWatchApplicationNew03",UtcDaliWatchApplicationNew03,utc_dali_watchapplication_startup,utc_dali_watchapplication_cleanup},
	{"UtcDaliWatchApplicationCopyAndAssignment",UtcDaliWatchApplicationCopyAndAssignment,utc_dali_watchapplication_startup,utc_dali_watchapplication_cleanup},
	{"UtcDaliWatchApplicationTimeTickSignalP",UtcDaliWatchApplicationTimeTickSignalP,utc_dali_watchapplication_startup,utc_dali_watchapplication_cleanup},
	{"UtcDaliWatchApplicationTimeTickSignalN",UtcDaliWatchApplicationTimeTickSignalN,utc_dali_watchapplication_startup,utc_dali_watchapplication_cleanup},
	{"UtcDaliWatchApplicationAmbientTickSignalP",UtcDaliWatchApplicationAmbientTickSignalP,utc_dali_watchapplication_startup,utc_dali_watchapplication_cleanup},
	{"UtcDaliWatchApplicationAmbientTickSignalN",UtcDaliWatchApplicationAmbientTickSignalN,utc_dali_watchapplication_startup,utc_dali_watchapplication_cleanup},
	{"UtcDaliWatchApplicationAmbientChangedSignalP",UtcDaliWatchApplicationAmbientChangedSignalP,utc_dali_watchapplication_startup,utc_dali_watchapplication_cleanup},
	{"UtcDaliWatchApplicationAmbientChangedSignalN",UtcDaliWatchApplicationAmbientChangedSignalN,utc_dali_watchapplication_startup,utc_dali_watchapplication_cleanup},
	{"UtcDaliWatchTimeNew",UtcDaliWatchTimeNew,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetHour",UtcDaliWatchTimeGetHour,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetHour24",UtcDaliWatchTimeGetHour24,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetMinute",UtcDaliWatchTimeGetMinute,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetSecond",UtcDaliWatchTimeGetSecond,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetMillisecond",UtcDaliWatchTimeGetMillisecond,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetYear",UtcDaliWatchTimeGetYear,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetMonth",UtcDaliWatchTimeGetMonth,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetDay",UtcDaliWatchTimeGetDay,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetDayOfWeek",UtcDaliWatchTimeGetDayOfWeek,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetUtcTime",UtcDaliWatchTimeGetUtcTime,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetUtcTimeStamp",UtcDaliWatchTimeGetUtcTimeStamp,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetTimeZone",UtcDaliWatchTimeGetTimeZone,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
	{"UtcDaliWatchTimeGetDaylightSavingTimeStatus",UtcDaliWatchTimeGetDaylightSavingTimeStatus,utc_dali_watchtime_startup,utc_dali_watchtime_cleanup},
  {"UtcDaliCaptureConstructorP",UtcDaliCaptureConstructorP,utc_Dali_Capture_startup,utc_Dali_Capture_cleanup},
  {"UtcDaliCaptureNewP",UtcDaliCaptureNewP,utc_Dali_Capture_startup,utc_Dali_Capture_cleanup},
  {"UtcDaliCaptureNewCameraP",UtcDaliCaptureNewCameraP,utc_Dali_Capture_startup,utc_Dali_Capture_cleanup},
  {"UtcDaliCaptureAssignmentP",UtcDaliCaptureAssignmentP,utc_Dali_Capture_startup,utc_Dali_Capture_cleanup},
  {"UtcDaliCaptureDownCastP",UtcDaliCaptureDownCastP,utc_Dali_Capture_startup,utc_Dali_Capture_cleanup},
  {"UtcDaliCaptureStartP",UtcDaliCaptureStartP,utc_Dali_Capture_startup,utc_Dali_Capture_cleanup},
  {"UtcDaliCaptureStartColorP",UtcDaliCaptureStartColorP,utc_Dali_Capture_startup,utc_Dali_Capture_cleanup},
  {"UtcDaliCaptureStartColorAndQualityP",UtcDaliCaptureStartColorAndQualityP,utc_Dali_Capture_startup,utc_Dali_Capture_cleanup},
  {"UtcDaliCaptureReturnNativeImageSourceP",UtcDaliCaptureReturnNativeImageSourceP,utc_Dali_Capture_startup,utc_Dali_Capture_cleanup},
  {"UtcDaliCaptureStartColorAndQualityN",UtcDaliCaptureStartColorAndQualityN,utc_Dali_Capture_startup,utc_Dali_Capture_cleanup},
  {"UtcDaliCaptureReturnNativeImageSourceN",UtcDaliCaptureReturnNativeImageSourceN,utc_Dali_Capture_startup,utc_Dali_Capture_cleanup},
  {"UtcDaliCaptureFinishedN",UtcDaliCaptureFinishedN,utc_Dali_Capture_startup,utc_Dali_Capture_cleanup},
	{NULL, NULL}
};

#endif // __TCT_DALI-ADAPTOR-NATIVE_H__