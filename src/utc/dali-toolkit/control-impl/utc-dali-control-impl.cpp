#include "utc-dali-control-impl-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: ControlImpl

/**
 * @function            utc_Dali_ControlImpl_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ControlImpl_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_ControlImpl_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ControlImpl_cleanup(void)
{

}

/**Check for key input focus status**/
bool gKeyInputFocusCallBackCalled1 = false;

/**
 * @function            CbControlKeyInputFocusGainCallback
 * @description         Callback for key input focus
 * @since_tizen         2.4
 */

void CbControlKeyInputFocusCallback1( Control control )
{
  // checking the pre-condition if the control has been initialized
  if( control )
  {
    LOG_I("Callback for key input focus is called.");
    gKeyInputFocusCallBackCalled1 = true;
  }
}

void ControlImplNewP();
void ControlImplEnableGestureDetectorP();
void ControlImplDisableGestureDetectorP();
void ControlImplGetLongPressGestureDetectorP();
void ControlImplGetPanGestureDetectorP();
void ControlImplGetPinchGestureDetectorP();
void ControlImplGetTapGestureDetectorP();
void ControlImplClearKeyInputFocusP();
void ControlImplSetAndHasKeyInputFocusP();
void ControlImplKeyInputFocusGainedSignalP();
void ControlImplKeyInputFocusLostSignalP();
void ControlImplSetGetStyleNameP();
void ControlImplKeyEventSignalP();
void ControlImplGetControlExtensionP();
void ControlImplGetNextKeyboardFocusableActorP();
void ControlImplOnAccessibilityPanP();
void ControlImplOnAccessibilityTouchP();
void ControlImplOnAccessibilityActivatedP();
void ControlImplOnKeyInputFocusGainedP();
void ControlImplOnKeyInputFocusLostP();
void ControlImplOnStyleChangeN();
void ControlImplOnInitializeP();
void ControlImpOnAccessibilityValueChangeP();
void ControlImpIsKeyboardNavigationSupportedP();
void ControlImpIsKeyboardFocusGroupP();
void ControlImpOnAccessibilityZoomP();
void ControlImpKeyboardEnterP();
void ControlImpOnControlChildAddP();
void ControlImpOnControlChildRemoveP();
void ControlImpOnKeyboardEnterP();
void ControlImpOnKeyboardFocusChangeCommittedP();
void ControlImpSetAsKeyboardFocusGroupP();
void ControlImpSetKeyboardNavigationSupportP();
void ControlImpSetBackgroundP();
void ControlImplCalculateChildSizeP();
void ControlImplOnSetSizeP();
void ControlImplOnSizeAnimationP();
void ControlImplOnSetResizePolicyP();
void ControlImplRelayoutDependentOnChildrenP();

namespace
{
  enum TEST_CASES_LIST_CONTROL
  {
    CONTROL_IMPL_NEW_P,
    CONTROL_IMPL_ENABLE_GESTURE_DETECTOR_P,
    CONTROL_IMPL_DISABLE_GESTURE_DETECTOR_P,
    CONTROL_IMPL_GET_PINCH_GESTURE_DETECTOR_P,
    CONTROL_IMPL_GET_PAN_GESTURE_DETECTOR_P,
    CONTROL_IMPL_GET_TAP_GESTURE_DETECTOR_P,
    CONTROL_IMPL_GET_LONG_PRESS_GESTURE_DETECTOR_P,
    CONTROL_IMPL_CLEAR_KEY_INPUT_FOCUS_P,
    CONTROL_IMPL_SET_AND_HAS_KEY_INPUT_FOCUS_P,
    CONTROL_IMPL_KEY_INPUT_FOCUS_GAINED_SIGNAL_P,
    CONTROL_IMPL_KEY_INPUT_FOCUS_LOST_SIGNAL_P,
    CONTROL_IMPL_SET_GET_STYLE_NAME_P,
    CONTROL_IMPL_KEY_EVENT_SIGNAL_P,
    CONTROL_IMPL_GET_CONTROL_EXTENSION_P,
    CONTROL_IMPL_GET_NEXT_KEYBOARD_FOCUSABLE_ACTOR_P,
    CONTROL_IMPL_ON_ACCESSIBILITY_PAN_P,
    CONTROL_IMPL_ON_ACCESSIBILITY_TOUCH_P,
    CONTROL_IMPL_ON_ACCESSIBILITY_ACTIVATED_P,
    CONTROL_IMPL_ON_KEY_INPUT_FOCUS_GAINED_P,
    CONTROL_IMPL_ON_KEY_INPUT_FOCUS_LOST_P,
    CONTROL_IMPL_ON_STYLE_CHANGE_P,
    CONTROL_IMPL_ON_INITIALIZE_P,
    CONTROL_IMPL_ON_ACCESSIBILITY_VALUE_CHANGE_P,
    CONTROL_IMPL_ON_ACCESSIBILITY_ZOOM_P,
    CONTROL_IMPL_IS_KEYBOARD_NAVIGATION_SUPPORTED_P,
    CONTROL_IMPL_IS_KEYBOARD_FOCUS_GROUP_P,
    CONTROL_IMPL_KEYBOARD_ENTER_P,
    CONTROL_IMPL_ON_CONTROL_CHILD_ADD_P,
    CONTROL_IMPL_ON_CONTROL_CHILD_REMOVE_P,
    CONTROL_IMPL_ON_KEYBOARD_ENTER_P,
    CONTROL_IMPL_ON_KEYBOARD_FOCUS_CHANGE_COMMITTED_P,
    CONTROL_IMPL_SET_AS_KEYBOARD_FOCUS_GROUP_P,
    CONTROL_IMPL_SET_KEYBOARD_NAVIGATION_SUPPORT_P,
    CONTROL_IMPL_SET_BACKGROUND_P,
    CONTROL_IMPL_CALCULATE_CHILD_SIZE_P,
    CONTROL_IMPL_ON_SET_SIZE_P,
    CONTROL_ON_SIZE_ANIMATION_P,
    CONTROL_ON_SET_RESIZE_POLICY_P,
    CONTROL_ON_RELAYOUT_DEPENDENT_ON_CHILDREN_P,
  };

  struct Control_TestApp : public ConnectionTracker
  {
    Control_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Control_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Control_TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      mTimer.Stop();
      mApplication.Quit();
      return true;
    }

    void ExcuteTest()
    {
      switch (mTestCase)
      {
        case CONTROL_IMPL_NEW_P:
          ControlImplNewP();
          break;
        case CONTROL_IMPL_ENABLE_GESTURE_DETECTOR_P:
          ControlImplEnableGestureDetectorP();
          break;
        case CONTROL_IMPL_DISABLE_GESTURE_DETECTOR_P:
          ControlImplDisableGestureDetectorP();
          break;
        case CONTROL_IMPL_GET_PINCH_GESTURE_DETECTOR_P:
          ControlImplGetPinchGestureDetectorP();
          break;
        case CONTROL_IMPL_GET_PAN_GESTURE_DETECTOR_P:
          ControlImplGetPanGestureDetectorP();
          break;
        case CONTROL_IMPL_GET_TAP_GESTURE_DETECTOR_P:
          ControlImplGetTapGestureDetectorP();
          break;
        case CONTROL_IMPL_GET_LONG_PRESS_GESTURE_DETECTOR_P:
          ControlImplGetLongPressGestureDetectorP();
          break;
        case CONTROL_IMPL_CLEAR_KEY_INPUT_FOCUS_P:
          ControlImplClearKeyInputFocusP();
          break;
        case CONTROL_IMPL_SET_AND_HAS_KEY_INPUT_FOCUS_P:
          ControlImplSetAndHasKeyInputFocusP();
          break;
        case CONTROL_IMPL_KEY_INPUT_FOCUS_GAINED_SIGNAL_P:
          ControlImplKeyInputFocusGainedSignalP();
          break;
        case CONTROL_IMPL_KEY_INPUT_FOCUS_LOST_SIGNAL_P:
          ControlImplKeyInputFocusLostSignalP();
          break;
        case CONTROL_IMPL_SET_GET_STYLE_NAME_P:
          ControlImplSetGetStyleNameP();
          break;
        case CONTROL_IMPL_KEY_EVENT_SIGNAL_P:
          ControlImplKeyEventSignalP();
          break;
        case CONTROL_IMPL_GET_CONTROL_EXTENSION_P:
          ControlImplGetControlExtensionP();
          break;
        case CONTROL_IMPL_GET_NEXT_KEYBOARD_FOCUSABLE_ACTOR_P:
          ControlImplGetNextKeyboardFocusableActorP();
          break;
        case CONTROL_IMPL_ON_ACCESSIBILITY_PAN_P:
          ControlImplOnAccessibilityPanP();
          break;
        case CONTROL_IMPL_ON_ACCESSIBILITY_TOUCH_P:
          ControlImplOnAccessibilityTouchP();
          break;
        case CONTROL_IMPL_ON_ACCESSIBILITY_ACTIVATED_P:
          ControlImplOnAccessibilityActivatedP();
          break;
        case CONTROL_IMPL_ON_KEY_INPUT_FOCUS_GAINED_P:
          ControlImplOnKeyInputFocusGainedP();
          break;
        case CONTROL_IMPL_ON_KEY_INPUT_FOCUS_LOST_P:
          ControlImplOnKeyInputFocusLostP();
          break;
        case CONTROL_IMPL_ON_STYLE_CHANGE_P:
          ControlImplOnStyleChangeN();
          break;
        case CONTROL_IMPL_ON_INITIALIZE_P:
          ControlImplOnInitializeP();
          break;
        case CONTROL_IMPL_SET_BACKGROUND_P:
          ControlImpSetBackgroundP();
          break;
        case CONTROL_IMPL_CALCULATE_CHILD_SIZE_P:
          ControlImplCalculateChildSizeP();
          break;
        case CONTROL_IMPL_ON_SET_SIZE_P:
          ControlImplOnSetSizeP();
          break;
        case CONTROL_ON_SIZE_ANIMATION_P:
          ControlImplOnSizeAnimationP();
          break;
        case CONTROL_ON_SET_RESIZE_POLICY_P:
          ControlImplOnSetResizePolicyP();
          break;
        case CONTROL_ON_RELAYOUT_DEPENDENT_ON_CHILDREN_P:
          ControlImplRelayoutDependentOnChildrenP();
          break;
        case CONTROL_IMPL_ON_CONTROL_CHILD_REMOVE_P:
          ControlImpOnControlChildRemoveP();
          break;
        case CONTROL_IMPL_ON_CONTROL_CHILD_ADD_P:
          ControlImpOnControlChildAddP();
          break;
        case CONTROL_IMPL_KEYBOARD_ENTER_P:
          ControlImpKeyboardEnterP();
          break;
        case CONTROL_IMPL_IS_KEYBOARD_FOCUS_GROUP_P:
          ControlImpIsKeyboardFocusGroupP();
          break;
        case CONTROL_IMPL_IS_KEYBOARD_NAVIGATION_SUPPORTED_P:
          ControlImpIsKeyboardNavigationSupportedP();
          break;
        case CONTROL_IMPL_ON_ACCESSIBILITY_ZOOM_P:
          ControlImpOnAccessibilityZoomP();
          break;
        case CONTROL_IMPL_ON_ACCESSIBILITY_VALUE_CHANGE_P:
          ControlImpOnAccessibilityValueChangeP();
          break;
        case CONTROL_IMPL_SET_KEYBOARD_NAVIGATION_SUPPORT_P:
          ControlImpSetKeyboardNavigationSupportP();
          break;
        case CONTROL_IMPL_SET_AS_KEYBOARD_FOCUS_GROUP_P:
          ControlImpSetAsKeyboardFocusGroupP();
          break;
        case CONTROL_IMPL_ON_KEYBOARD_FOCUS_CHANGE_COMMITTED_P:
          ControlImpOnKeyboardFocusChangeCommittedP();
          break;
        case CONTROL_IMPL_ON_KEYBOARD_ENTER_P:
          ControlImpOnKeyboardEnterP();
          break;
      }
    }

    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

} // unnamed namespace


/**
 * ##############################
 * TC Logic Implementation Area.
 * ##############################
 **/

void ControlImplNewP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL( !dummy, "ControlImpl::New() is failed." );

  DaliLog::PrintPass();
}

void ControlImplEnableGestureDetectorP()
{
  DummyControl dummy = DummyControl::New();
  DummyControlImpl& dummyImpl = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  DALI_CHECK_FAIL( dummyImpl.GetPinchGestureDetector(), "Wrong Gesture" );
  dummyImpl.EnableGestureDetection(Gesture::Pinch);
  DALI_CHECK_FAIL( !dummyImpl.GetPinchGestureDetector(), "EnableGestureDetection is failed" );

  DALI_CHECK_FAIL( dummyImpl.GetPanGestureDetector(), "Wrong Gesture" );
  dummyImpl.EnableGestureDetection(Gesture::Pan);
  DALI_CHECK_FAIL( !dummyImpl.GetPanGestureDetector(), "EnableGestureDetection is failed" );

  DALI_CHECK_FAIL( dummyImpl.GetTapGestureDetector(), "Wrong Gesture" );
  dummyImpl.EnableGestureDetection(Gesture::Tap);
  DALI_CHECK_FAIL( !dummyImpl.GetTapGestureDetector(), "EnableGestureDetection is failed" );

  DALI_CHECK_FAIL( dummyImpl.GetLongPressGestureDetector(), "Wrong Gesture" );
  dummyImpl.EnableGestureDetection(Gesture::LongPress);
  DALI_CHECK_FAIL( !dummyImpl.GetLongPressGestureDetector(), "EnableGestureDetection is failed" );

  DaliLog::PrintPass();
}

void ControlImplDisableGestureDetectorP()
{
  DummyControl dummy = DummyControl::New();
  DummyControlImpl& dummyImpl = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  dummyImpl.EnableGestureDetection( Gesture::Type(Gesture::Pinch | Gesture::Pan | Gesture::Tap | Gesture::LongPress) );

  DALI_CHECK_FAIL( !dummyImpl.GetPinchGestureDetector(), "EnableGestureDetection is failed" );
  dummyImpl.DisableGestureDetection(Gesture::Pinch);
  DALI_CHECK_FAIL( dummyImpl.GetPinchGestureDetector(), "DisableGestureDetection is failed" );

  DALI_CHECK_FAIL( !dummyImpl.GetPanGestureDetector(), "EnableGestureDetection is failed" );
  dummyImpl.DisableGestureDetection(Gesture::Pan);
  DALI_CHECK_FAIL( dummyImpl.GetPanGestureDetector(), "DisableGestureDetection is failed" );

  DALI_CHECK_FAIL( !dummyImpl.GetTapGestureDetector(), "EnableGestureDetection is failed" );
  dummyImpl.DisableGestureDetection(Gesture::Tap);
  DALI_CHECK_FAIL( dummyImpl.GetTapGestureDetector(), "DisableGestureDetection is failed" );

  DALI_CHECK_FAIL( !dummyImpl.GetLongPressGestureDetector(), "EnableGestureDetection is failed" );
  dummyImpl.DisableGestureDetection(Gesture::LongPress);
  DALI_CHECK_FAIL( dummyImpl.GetLongPressGestureDetector(), "DisableGestureDetection is failed" );

  DaliLog::PrintPass();
}

void ControlImplGetPinchGestureDetectorP()
{
  PinchGestureDetector pinchDetector;
  Vector3 vec3ControlSize(100.0f, 100.0f, 100.0f);
  Stage stage;

  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created.");

  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is not created.");

  dummy.SetSize( vec3ControlSize );
  dummy.SetAnchorPoint(AnchorPoint::TOP_LEFT);
  stage.Add(dummy);

  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());
  DALI_CHECK_FAIL( control.GetPinchGestureDetector(), "Wrong Gesture" );

  control.EnableGestureDetection(Gesture::Pinch);
  pinchDetector = control.GetPinchGestureDetector();

  DALI_CHECK_FAIL( !pinchDetector, "GetPinchGestureDetector has failed because pinchDetector is empty." );
  stage.Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImplGetPanGestureDetectorP()
{
  PanGestureDetector panDetector;
  Stage stage;
  Vector3 vec3ControlSize(100.0f, 100.0f, 100.0f);

  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created.");

  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is not created.");

  dummy.SetSize( vec3ControlSize );
  dummy.SetAnchorPoint(AnchorPoint::TOP_LEFT);
  stage.Add(dummy);

  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());
  DALI_CHECK_FAIL( control.GetPanGestureDetector(), "Wrong Gesture" );

  control.EnableGestureDetection(Gesture::Pan);
  panDetector = control.GetPanGestureDetector();

  DALI_CHECK_FAIL( !panDetector, "GetPanGestureDetector has failed because panDetector is empty." );
  stage.Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImplGetTapGestureDetectorP()
{
  TapGestureDetector tapDetector;
  Stage stage;
  Vector3 vec3ControlSize(100.0f, 100.0f, 100.0f);

  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created.");

  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is not created.");

  dummy.SetSize( vec3ControlSize );
  dummy.SetAnchorPoint(AnchorPoint::TOP_LEFT);
  stage.Add(dummy);

  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());
  DALI_CHECK_FAIL( control.GetTapGestureDetector(), "Wrong Gesture" );

  control.EnableGestureDetection(Gesture::Tap);
  tapDetector = control.GetTapGestureDetector();

  DALI_CHECK_FAIL( !tapDetector,  "GetTapGestureDetector has failed because tapDetector is empty." );
  stage.Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImplGetLongPressGestureDetectorP()
{
  LongPressGestureDetector longPressDetector;
  Stage stage;
  Vector3 vec3ControlSize(100.0f, 100.0f, 100.0f);

  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created.");

  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is not created.");

  dummy.SetSize( vec3ControlSize );
  dummy.SetAnchorPoint(AnchorPoint::TOP_LEFT);
  stage.Add(dummy);

  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());
  DALI_CHECK_FAIL( control.GetLongPressGestureDetector(), "Wrong Gesture" );

  control.EnableGestureDetection(Gesture::LongPress);
  longPressDetector = control.GetLongPressGestureDetector();

  DALI_CHECK_FAIL( !longPressDetector, "GetLongPressGestureDetector has failed because longPressDetector is empty." );
  stage.Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImplClearKeyInputFocusP()
{
  bool bHasKeyFocus = false;
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage::GetCurrent() is failed." );

  Control dummy = PushButton::New();
  DALI_CHECK_FAIL( !dummy, "Control handle is not initialized with push button." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  stage.Add( dummy );

  control.SetKeyInputFocus();
  bHasKeyFocus = control.HasKeyInputFocus();
  DALI_CHECK_FAIL( !bHasKeyFocus, "SetKeyInputFocus has failed because control has no focus." );

  control.ClearKeyInputFocus();
  bHasKeyFocus = control.HasKeyInputFocus();

  DALI_CHECK_FAIL( bHasKeyFocus, "ClearKeyInputFocus has failed because instead of clearing it is still on focus." );
  stage.Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImplSetAndHasKeyInputFocusP()
{
  bool bHasKeyFocus = false;
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage::GetCurrent() is failed." );

  Control dummy = PushButton::New();
  DALI_CHECK_FAIL( !dummy, "Control handle is not initialized with push button." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  stage.Add( dummy );

  control.SetKeyInputFocus();
  bHasKeyFocus = control.HasKeyInputFocus();

  DALI_CHECK_FAIL( !bHasKeyFocus, "SetKeyInputFocus has failed because control has no focus." );
  stage.Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImplKeyInputFocusGainedSignalP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Stage::GetCurrent().Add( dummy );

  gKeyInputFocusCallBackCalled1 = false;
  control.KeyInputFocusGainedSignal().Connect(&CbControlKeyInputFocusCallback1);

  control.SetKeyInputFocus();
  DALI_CHECK_FAIL( !gKeyInputFocusCallBackCalled1, "Control KeyInputFocusGainedSignal is failed to connect the callback." );
  DALI_CHECK_FAIL( !control.HasKeyInputFocus(), "SetKeyInputFocus is failed to set Control Key Input Focus." );
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImplKeyInputFocusLostSignalP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Stage::GetCurrent().Add( dummy );

  gKeyInputFocusCallBackCalled1 = false;
  control.KeyInputFocusLostSignal().Connect(&CbControlKeyInputFocusCallback1);

  control.SetKeyInputFocus();
  DALI_CHECK_FAIL( !control.HasKeyInputFocus(), "SetKeyInputFocus is failed to set Control Key Input Focus." );
  DALI_CHECK_FAIL( gKeyInputFocusCallBackCalled1, "Control KeyInputFocusLostSignal should not be emitted before clearing key input focus." );

  control.ClearKeyInputFocus();
  DALI_CHECK_FAIL( !gKeyInputFocusCallBackCalled1, "Control KeyInputFocusLostSignal is failed to connect the callback." );
  DALI_CHECK_FAIL( control.HasKeyInputFocus(), "ClearKeyInputFocus is failed to clear Control Key Input Focus." );
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImplSetGetStyleNameP()
{
  const string STYLE_NAME = "textlabel";
  string strGetStyle = "";

  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  control.SetStyleName(STYLE_NAME);
  strGetStyle = control.GetStyleName();
  DALI_CHECK_FAIL( strGetStyle != STYLE_NAME, "Set Style Name is mismatched with Get Style Name." );

  DaliLog::PrintPass();
}

void ControlImplKeyEventSignalP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Stage::GetCurrent().Add( dummy );
  try
  {
    control.KeyEventSignal();
  }
  catch(DaliException& de)
  {
    LOG_E("KeyEventSignal with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    if( dummy )
    {
      LOG_I("Callback for key input focus is called.");
      gKeyInputFocusCallBackCalled1 = true;
    }

  }
  control.SetKeyInputFocus();
  DALI_CHECK_FAIL( !control.HasKeyInputFocus(), "SetKeyInputFocus is failed to set Control Key Input Focus." );
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImplGetControlExtensionP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  DALI_CHECK_FAIL( NULL != control.GetControlExtension(), "GetControlExtension is failed" );

  DaliLog::PrintPass();
}

void ControlImplGetNextKeyboardFocusableActorP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Actor currentFocusedActor;
  Actor result = control.GetNextKeyboardFocusableActor( currentFocusedActor, Control::KeyboardFocus::LEFT, false );

  DALI_CHECK_FAIL( result != currentFocusedActor, "GetNextKeyboardFocusableActor is failed" );

  DaliLog::PrintPass();
}

void ControlImplOnAccessibilityPanP(void)
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  PanGesture pan;
  DALI_CHECK_FAIL( control.OnAccessibilityPan( pan ), "OnAccessibilityPan is failed" );

  DaliLog::PrintPass();
}

void ControlImplOnAccessibilityTouchP(void)
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  TouchEvent touch;
  DALI_CHECK_FAIL( control.OnAccessibilityTouch( touch ), "OnAccessibilityTouch is failed" );

  DaliLog::PrintPass();
}

void ControlImplOnAccessibilityActivatedP(void)
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  DALI_CHECK_FAIL( control.OnAccessibilityActivated(), "OnAccessibilityActivated is failed" );

  // Invoke the control's activate action
  TypeInfo type = TypeRegistry::Get().GetTypeInfo( "Control" );
  DALI_CHECK_FAIL( !type, "TypeRegistry is failed" );

  BaseHandle handle = type.CreateInstance();
  DALI_CHECK_FAIL( !handle, "CreateInstance is failed" );

  Property::Map attributes;
  DALI_CHECK_FAIL( handle.DoAction("accessibilityActivated",  attributes), "OnAccessibilityTouch is failed" );

  DaliLog::PrintPass();
}

void ControlImplOnKeyInputFocusGainedP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  try
  {
    control.OnKeyInputFocusGained();
  }
  catch(DaliException& de)
  {
    LOG_E("OnKeyInputFocusGained with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    if( dummy )
    {
      LOG_I("Callback for key input focus is called.");
      gKeyInputFocusCallBackCalled1 = true;
    }

  }

  DaliLog::PrintPass();
}

void ControlImplOnKeyInputFocusLostP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  try
  {
    control.OnKeyInputFocusLost();
  }
  catch(DaliException& de)
  {
    LOG_E("OnKeyInputFocusLost with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    if( dummy )
    {
      LOG_I("Callback for key input focus is called.");
      gKeyInputFocusCallBackCalled1 = true;
    }

  }

  DaliLog::PrintPass();
}

void ControlImplOnStyleChangeN()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  // test that style manager is being used, passing an empty handle does nothing but does not crash either
  Dali::Toolkit::StyleManager styleManager;

  try
  {
    control.OnStyleChange( styleManager, StyleChange::THEME_CHANGE );
  }
  catch(DaliException& de)
  {
    LOG_E("OnStyleChange with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    if( dummy )
    {
      LOG_I("Callback for key input focus is called.");
      gKeyInputFocusCallBackCalled1 = true;
    }

  }

  DaliLog::PrintPass();
}

void ControlImplOnInitializeP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  try
  {
    control.OnInitialize();
  }
  catch(DaliException& de)
  {
    LOG_E("OnInitialize with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    if( dummy )
    {
      LOG_I("Callback for key input focus is called.");
      gKeyInputFocusCallBackCalled1 = true;
    }

  }

  DaliLog::PrintPass();
}

void ControlImpOnAccessibilityValueChangeP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Stage::GetCurrent().Add(dummy);
  control.OnAccessibilityValueChange( true );
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImpIsKeyboardNavigationSupportedP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Stage::GetCurrent().Add(dummy);
  control.IsKeyboardNavigationSupported();
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImpIsKeyboardFocusGroupP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Stage::GetCurrent().Add(dummy);
  control.IsKeyboardFocusGroup();
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImpOnAccessibilityZoomP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Stage::GetCurrent().Add(dummy);
  control.OnAccessibilityZoom();
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImpKeyboardEnterP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Stage::GetCurrent().Add(dummy);
  control.OnKeyboardEnter();
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImpOnControlChildAddP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(dummy);
  control.OnControlChildAdd(actor);
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImpSetBackgroundP()
{
  Control control = Control::New();
  DALI_CHECK_FAIL( !control, "ControlImpl::New() is failed." );

  Toolkit::Internal::Control& controlImpl = Toolkit::Internal::GetImplementation( control );

  Property::Map map;
  DALI_CHECK_FAIL(!map.Empty(), "property is not empty which is not expected");

  Vector4 vec4Black(0.0f, 0.0f, 0.0f, 0.0f);

  map[ Visual::Property::TYPE ] = Visual::COLOR;
  map[ ColorVisual::Property::MIX_COLOR ] = vec4Black;

  DALI_CHECK_FAIL(map.Empty(), "property is empty which is not expected");

  controlImpl.SetBackground(map);

  DaliLog::PrintPass();
}

void ControlImplCalculateChildSizeP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Actor child = Actor::New();
  child.SetResizePolicy(Dali::ResizePolicy::FIXED, Dali::Dimension::ALL_DIMENSIONS);
  child.SetSize(150, 150);

  float v = 9.99f;
  v = control.CalculateChildSize( child, Dali::Dimension::ALL_DIMENSIONS );
  DALI_CHECK_FAIL( v != 0.0f, "CalculateChildSize is failed " );

  DaliLog::PrintPass();
}

void ControlImplOnSetSizeP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImplOverride& control = static_cast<DummyControlImplOverride&>(dummy.GetImplementation());
  Vector3 vec3ControlSize(100.0f, 100.0f, 100.0f);

  try
  {
    control.OnSizeSet(vec3ControlSize);
  }
  catch(DaliException& de)
  {
    LOG_E("OnSizeSet is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    if( dummy )
    {
      LOG_I("Callback for key input focus is called.");
      gKeyInputFocusCallBackCalled1 = true;
    }

  }

  DaliLog::PrintPass();
}

void ControlImplOnSizeAnimationP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImplOverride& control = static_cast<DummyControlImplOverride&>(dummy.GetImplementation());
  Vector3 vec3ControlSize(100.0f, 100.0f, 100.0f);
  Animation anim = Animation::New( 1.0f );

  try
  {
    control.OnSizeAnimation( anim, vec3ControlSize );
  }
  catch(DaliException& de)
  {
    LOG_E("OnSizeAnimation is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    if( dummy )
    {
      LOG_I("Callback for key input focus is called.");
      gKeyInputFocusCallBackCalled1 = true;
    }

  }

  DaliLog::PrintPass();
}

void ControlImplOnSetResizePolicyP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImplOverride& control = static_cast<DummyControlImplOverride&>(dummy.GetImplementation());
  Vector3 vec3ControlSize(100.0f, 100.0f, 100.0f);
  Animation anim = Animation::New( 1.0f );

  try
  {
    control.OnSetResizePolicy( ResizePolicy::DIMENSION_DEPENDENCY, Dimension::HEIGHT );
  }
  catch(DaliException& de)
  {
    LOG_E("OnSetResizePolicy is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    if( dummy )
    {
      LOG_I("Callback for key input focus is called.");
      gKeyInputFocusCallBackCalled1 = true;
    }

  }

  DaliLog::PrintPass();
}

void ControlImplRelayoutDependentOnChildrenP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  try
  {
    control.RelayoutDependentOnChildren( Dali::Dimension::ALL_DIMENSIONS );
  }
  catch(DaliException& de)
  {
    LOG_E("RelayoutDependentOnChildren is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    if( dummy )
    {
      LOG_I("Callback for key input focus is called.");
      gKeyInputFocusCallBackCalled1 = true;
    }

  }

  DaliLog::PrintPass();
}

void ControlImpOnControlChildRemoveP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(dummy);
  control.OnControlChildAdd(actor);
  control.OnControlChildRemove(actor);
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImpOnKeyboardEnterP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Stage::GetCurrent().Add(dummy);
  control.OnKeyboardEnter();
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImpOnKeyboardFocusChangeCommittedP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(dummy);
  control.OnKeyboardFocusChangeCommitted(actor);
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImpSetAsKeyboardFocusGroupP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(dummy);
  control.SetAsKeyboardFocusGroup(true);
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}

void ControlImpSetKeyboardNavigationSupportP()
{
  DummyControl dummy = DummyControl::New();
  DALI_CHECK_FAIL(!dummy, "Control::New() is failed." );
  DummyControlImpl& control = static_cast<DummyControlImpl&>(dummy.GetImplementation());

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(dummy);
  control.SetKeyboardNavigationSupport(true);
  Stage::GetCurrent().Remove(dummy);

  DaliLog::PrintPass();
}


/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase            UtcDaliControlImplNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliControlImplNewP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplEnableGestureDetectorP
 * @since_tizen         2.4
 * @description         Enables Gestures as Pinch, Pan, Tap, LongPress.
 */

int UtcDaliControlImplEnableGestureDetectorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ENABLE_GESTURE_DETECTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplDisableGestureDetectorP
 * @since_tizen         2.4
 * @description         Disables Gestures as Pinch, Pan, Tap, LongPress.
 */

int UtcDaliControlImplDisableGestureDetectorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_DISABLE_GESTURE_DETECTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplGetPinchGestureDetectorP
 * @since_tizen         2.4
 * @description         Checks whether GetPinchGestureDetector api is executed successfully or not
 */

int UtcDaliControlImplGetPinchGestureDetectorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_GET_PINCH_GESTURE_DETECTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplGetPanGestureDetectorP
 * @since_tizen         2.4
 * @description         Checks whether GetPanGestureDetector api is executed successfully or not
 */

int UtcDaliControlImplGetPanGestureDetectorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_GET_PAN_GESTURE_DETECTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplGetTapGestureDetectorP
 * @since_tizen         2.4
 * @description         Checks whether GetTapGestureDetector api is executed successfully or not
 */

int UtcDaliControlImplGetTapGestureDetectorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_GET_TAP_GESTURE_DETECTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplGetLongPressGestureDetectorP
 * @since_tizen         2.4
 * @description         Checks whether GetLongPressGestureDetector api is executed successfully or not
 */

int UtcDaliControlImplGetLongPressGestureDetectorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_GET_LONG_PRESS_GESTURE_DETECTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplClearKeyInputFocusP
 * @since_tizen         2.4
 * @description         Checks whether ClearKeyInputFocus api are executed successfully or not
 */

int UtcDaliControlImplClearKeyInputFocusP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_CLEAR_KEY_INPUT_FOCUS_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplSetAndHasKeyInputFocusP
 * @since_tizen         2.4
 * @description         Checks whether SetKeyInputFocus and HasKeyInputFocus apis are executed successfully or not
 */

int UtcDaliControlImplSetAndHasKeyInputFocusP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_SET_AND_HAS_KEY_INPUT_FOCUS_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplKeyInputFocusGainedSignalP
 * @since_tizen         2.4
 * @description         Checks whether KeyInputFocusGainedSignal can emmit and call to callback function.
 */

int UtcDaliControlImplKeyInputFocusGainedSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_KEY_INPUT_FOCUS_GAINED_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplKeyInputFocusLostSignalP
 * @since_tizen         2.4
 * @description         Checks whether KeyInputFocusLostSignal can emmit and call to callback function.
 */

int UtcDaliControlImplKeyInputFocusLostSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_KEY_INPUT_FOCUS_LOST_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplSetGetStyleNameP
 * @since_tizen         2.4
 * @description         Checks whether Sets the name of the style to be applied to the control is executed successfully or not
 */

int UtcDaliControlImplSetGetStyleNameP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_SET_GET_STYLE_NAME_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplKeyEventSignalP
 * @since_tizen         2.4
 * @description         Checks whether KeyEventSignal can emmit and call to callback function.
 */

int UtcDaliControlImplKeyEventSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_KEY_EVENT_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplGetControlExtensionP
 * @since_tizen         2.4
 * @description         Retrieve the extension for this control
 */

int UtcDaliControlImplGetControlExtensionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_GET_CONTROL_EXTENSION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplGetNextKeyboardFocusableActorP
 * @since_tizen         2.4
 * @description         Gets the next keyboard focusable actor in this control towards the given direction.
 */

int UtcDaliControlImplGetNextKeyboardFocusableActorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_GET_NEXT_KEYBOARD_FOCUSABLE_ACTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplOnAccessibilityActivatedP
 * @since_tizen         2.4
 * @description         This method is called when the control is accessibility activated.
 */

int UtcDaliControlImplOnAccessibilityActivatedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_ACCESSIBILITY_ACTIVATED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplOnAccessibilityTouchP
 * @since_tizen         2.4
 * @description         This method is used to respond to the accessibility touch
 */

int UtcDaliControlImplOnAccessibilityTouchP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_ACCESSIBILITY_TOUCH_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplOnAccessibilityPanP
 * @since_tizen         2.4
 * @description         This method is used to respond to the accessibility pan
 */

int UtcDaliControlImplOnAccessibilityPanP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_ACCESSIBILITY_PAN_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplOnStyleChangeN
 * @since_tizen         2.4
 * @description         This method gives notifications when the style changes.
 */

int UtcDaliControlImplOnStyleChangeN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_STYLE_CHANGE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplOnKeyInputFocusLostP
 * @since_tizen         2.4
 * @description         Called when the control loses key input focus.
 */

int UtcDalilControlImplOnKeyInputFocusLostP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_KEY_INPUT_FOCUS_LOST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplOnKeyInputFocusGainedP
 * @since_tizen         2.4
 * @description         Called when the control gains key input focus.
 */

int UtcDaliControlImplOnKeyInputFocusGainedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_KEY_INPUT_FOCUS_GAINED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplOnInitializeP
 * @since_tizen         2.4
 * @description         Check that the Control has been initialized.
 */

int UtcDaliControlImplOnInitializeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_INITIALIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImpOnAccessibilityValueChangeP
 * @since_tizen         2.4
 * @description         check response to the accessibility up and down action
 */

int UtcDaliControlImpOnAccessibilityValueChangeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_ACCESSIBILITY_VALUE_CHANGE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImpIsKeyboardNavigationSupportedP
 * @since_tizen         2.4
 * @description         Gets whether this control supports two dimensional keyboard navigation.
 */

int UtcDaliControlImpIsKeyboardNavigationSupportedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_IS_KEYBOARD_NAVIGATION_SUPPORTED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImpIsKeyboardFocusGroupP
 * @since_tizen         2.4
 * @description         Gets whether this control is a focus group for keyboard navigation.
 */

int UtcDaliControlImpIsKeyboardFocusGroupP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_IS_KEYBOARD_FOCUS_GROUP_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImpOnAccessibilityZoomP
 * @since_tizen         2.4
 * @description         check response to the accessibility zoom action.
 */

int UtcDaliControlImpOnAccessibilityZoomP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_ACCESSIBILITY_ZOOM_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImpKeyboardEnterP
 * @since_tizen         2.4
 * @description         Check when the control has enter pressed on it.
 */

int UtcDaliControlImpKeyboardEnterP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_KEYBOARD_ENTER_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImpOnControlChildAddP
 * @since_tizen         2.4
 * @description         Checks whether an Actor is added to the control.
 */

int UtcDaliControlImpOnControlChildAddP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_CONTROL_CHILD_ADD_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImpOnControlChildRemoveP
 * @since_tizen         2.4
 * @description         Checks whether an Actor is added to the control.
 */

int UtcDaliControlImpOnControlChildRemoveP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_CONTROL_CHILD_REMOVE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImpOnKeyboardEnterP
 * @since_tizen         2.4
 * @description         checks when the control has enter pressed on it.
 */

int UtcDaliControlImpOnKeyboardEnterP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_KEYBOARD_ENTER_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImpOnKeyboardFocusChangeCommittedP
 * @since_tizen         2.4
 * @description         Checks when control has chosen focusable actor will be focused.
 */

int UtcDaliControlImpOnKeyboardFocusChangeCommittedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_KEYBOARD_FOCUS_CHANGE_COMMITTED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImpSetAsKeyboardFocusGroupP
 * @since_tizen         2.4
 * @description         checks whether this control is a focus group for keyboard navigation.
 */

int UtcDaliControlImpSetAsKeyboardFocusGroupP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_SET_AS_KEYBOARD_FOCUS_GROUP_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImpSetKeyboardNavigationSupportP
 * @since_tizen         2.4
 * @description         Sets whether this control supports two dimensional
 */

int UtcDaliControlImpSetKeyboardNavigationSupportP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_SET_KEYBOARD_NAVIGATION_SUPPORT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImpSetBackgroundP
 * @since_tizen         2.4
 * @description         check the setting of the background with a property map.
 */

int UtcDaliControlImpSetBackgroundP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_SET_BACKGROUND_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplCalculateChildSizeP
 * @since_tizen         2.4
 * @description         Check the calculation of size for the given dimension.
 */

int UtcDaliControlImplCalculateChildSizeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_CALCULATE_CHILD_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplOnSetSizeP
 * @since_tizen         2.4
 * @description         Test to check the functionality of OnSetSize
 */

int UtcDaliControlImplOnSetSizeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_IMPL_ON_SET_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplOnSizeAnimationP
 * @since_tizen         2.4
 * @description         Test to check the functionality of OnSizeAnimation.
 */

int UtcDaliControlImplOnSizeAnimationP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_ON_SIZE_ANIMATION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplOnSetResizePolicyP
 * @since_tizen         2.4
 * @description         checks dimension of the policy that is being set.
 */

int UtcDaliControlImplOnSetResizePolicyP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_ON_SET_RESIZE_POLICY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlImplRelayoutDependentOnChildrenP
 * @since_tizen         2.4
 * @description         Test to check the functionality of RelayoutDependentOnChildren.
 */

int UtcDaliControlImplRelayoutDependentOnChildrenP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_ON_RELAYOUT_DEPENDENT_ON_CHILDREN_P );
  application.MainLoop();

  return test_return_value;
}

