#include "utc-dali-control-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Control

/**
 * @function            utc_Dali_Control_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Control_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_Control_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Control_cleanup(void)
{

}

/**Check for key input focus status**/
bool gKeyInputFocusCallBackCalled = false;

/**
 * @function            CbControlKeyInputFocusGainCallback
 * @description         Callback for key input focus
 * @since_tizen         2.4
 */

void CbControlKeyInputFocusCallback( Control control )
{
  // checking the pre-condition if the control has been initialized
  if( control )
  {
    LOG_I("Callback for key input focus is called.");
    gKeyInputFocusCallBackCalled = true;
  }
}

void ControlNewP();
void ControlConstructorP();
void ControlCopyConstructorP();
void ControlOperatorAssignmentP();
void ControlDowncastP();
void ControlDowncastN();
void ControlSetAndHasKeyInputFocusP();
void ControlClearKeyInputFocusP();
void ControlGetPinchGestureDetectorP();
void ControlGetPanGestureDetectorP();
void ControlGetTapGestureDetectorP();
void ControlGetLongPressGestureDetectorP();
void ControlSetGetStyleNameP();
void ControlSetGetBackgroundImageColorP();
void ControlClearBackgroundP();
void ControlKeyEventSignalP();
void ControlKeyInputFocusGainedSignalP();
void ControlKeyInputFocusLostSignalP();

namespace
{
  enum TEST_CASES_LIST_CONTROL
  {
    CONTROL_NEW_P,
    CONTROL_CONSTRUCTOR_P,
    CONTROL_COPY_CONSTRUCTOR_P,
    CONTROL_OPERATOR_ASSIGNMENT_P,
    CONTROL_DOWNCAST_P,
    CONTROL_DOWNCAST_N,
    CONTROL_SET_AND_HAS_KEY_INPUT_FOCUS_P,
    CONTROL_CLEAR_KEY_INPUT_FOCUS_P,
    CONTROL_GET_PINCH_GESTURE_DETECTOR_P,
    CONTROL_GET_PAN_GESTURE_DETECTOR_P,
    CONTROL_GET_TAP_GESTURE_DETECTOR_P,
    CONTROL_GET_LONG_PRESS_GESTURE_DETECTOR_P,
    CONTROL_SET_GET_STYLE_NAME_P,
    CONTROL_SET_GET_BACKGROUND_IMAGE_COLOR_P,
    CONTROL_CLEAR_BACKGROUND_P,
    CONTROL_KEY_EVENT_SIGNAL_P,
    CONTROL_KEY_INPUT_FOCUS_GAINED_SIGNAL_P,
    CONTROL_KEY_INPUT_FOCUS_LOST_SIGNAL_P
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

        case CONTROL_NEW_P:
          ControlNewP();
          break;
        case CONTROL_CONSTRUCTOR_P:
          ControlConstructorP();
          break;
        case CONTROL_COPY_CONSTRUCTOR_P:
          ControlCopyConstructorP();
          break;
        case CONTROL_OPERATOR_ASSIGNMENT_P:
          ControlOperatorAssignmentP();
          break;
        case CONTROL_DOWNCAST_P:
          ControlDowncastP();
          break;
        case CONTROL_DOWNCAST_N:
          ControlDowncastN();
          break;
        case CONTROL_SET_AND_HAS_KEY_INPUT_FOCUS_P:
          ControlSetAndHasKeyInputFocusP();
          break;
        case CONTROL_CLEAR_KEY_INPUT_FOCUS_P:
          ControlClearKeyInputFocusP();
          break;
        case CONTROL_GET_PINCH_GESTURE_DETECTOR_P:
          ControlGetPinchGestureDetectorP();
          break;
        case CONTROL_GET_PAN_GESTURE_DETECTOR_P:
          ControlGetPanGestureDetectorP();
          break;
        case CONTROL_GET_TAP_GESTURE_DETECTOR_P:
          ControlGetTapGestureDetectorP();
          break;
        case CONTROL_GET_LONG_PRESS_GESTURE_DETECTOR_P:
          ControlGetLongPressGestureDetectorP();
          break;
        case CONTROL_SET_GET_STYLE_NAME_P:
          ControlSetGetStyleNameP();
          break;
        case CONTROL_SET_GET_BACKGROUND_IMAGE_COLOR_P:
          ControlSetGetBackgroundImageColorP();
          break;
        case CONTROL_CLEAR_BACKGROUND_P:
          ControlClearBackgroundP();
          break;
        case CONTROL_KEY_EVENT_SIGNAL_P:
          ControlKeyEventSignalP();
          break;
        case CONTROL_KEY_INPUT_FOCUS_GAINED_SIGNAL_P:
          ControlKeyInputFocusGainedSignalP();
          break;
        case CONTROL_KEY_INPUT_FOCUS_LOST_SIGNAL_P:
          ControlKeyInputFocusLostSignalP();
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

void ControlNewP()
{
  Control control = Control::New();
  DALI_CHECK_FAIL( !control, "Control::New() is failed." );

  DaliLog::PrintPass();
}

void ControlConstructorP()
{
  Control control;
  DALI_CHECK_FAIL( control, "Control constructor is failed." );

  DaliLog::PrintPass();
}

void ControlCopyConstructorP()
{
  Control control = Control::New();
  DALI_CHECK_FAIL( !control, "Control::New() is failed." );

  Control copyConstControl(control);

  DALI_CHECK_FAIL( copyConstControl != control, "Control Copy Constructor is Failed." );
  DaliLog::PrintPass();
}

void ControlOperatorAssignmentP()
{
  Control control = Control::New();
  DALI_CHECK_FAIL(!control, "Control::New() is failed." );

  Control emptyControl;
  emptyControl = control;
  DALI_CHECK_FAIL( emptyControl != control, "Assignmentoperator has failed because empty control does not match." );

  DaliLog::PrintPass();
}

void ControlDowncastP()
{
  Control control = Control::New();
  DALI_CHECK_FAIL(!control,  "Control::New() is failed." );

  BaseHandle  handleControl;
  handleControl = control;

  Control downCastControl = Control::DownCast( handleControl );

  DALI_CHECK_FAIL( !downCastControl, "Control::DownCast() is failed." );
  DALI_CHECK_FAIL( control != downCastControl, "Control::DownCast() is failed." );

  DaliLog::PrintPass();
}

void ControlDowncastN()
{
  BaseHandle unInitializedObject;

  Control control = Control::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(control, "Control handle is not empty." );

  Control control2 = DownCast< Control >( unInitializedObject );
  DALI_CHECK_FAIL(control2, "Control handle is not empty." );

  DaliLog::PrintPass();
}

void ControlSetAndHasKeyInputFocusP()
{
  bool bHasKeyFocus = false;
  Stage stage = Stage::GetCurrent();

  DALI_CHECK_FAIL(!stage, "Stage::GetCurrent() is failed." );

  Control control = PushButton::New();
  DALI_CHECK_FAIL( !control, "Control handle is not initialized with push button." );

  stage.Add( control );

  control.SetKeyInputFocus();
  bHasKeyFocus = control.HasKeyInputFocus();
  DALI_CHECK_FAIL( !bHasKeyFocus, "SetKeyInputFocus has failed because control has no focus." );

  stage.Remove(control);

  DaliLog::PrintPass();
}

void ControlClearKeyInputFocusP()
{
  bool bHasKeyFocus = false;
  Stage stage = Stage::GetCurrent();

  DALI_CHECK_FAIL(!stage, "Stage::GetCurrent() is failed." );

  Control control = PushButton::New();
  DALI_CHECK_FAIL( !control, "Control handle is not initialized with push button." );

  stage.Add( control );

  control.SetKeyInputFocus();
  bHasKeyFocus = control.HasKeyInputFocus();
  DALI_CHECK_FAIL( !bHasKeyFocus, "SetKeyInputFocus has failed because control has no focus." );

  control.ClearKeyInputFocus();
  bHasKeyFocus = control.HasKeyInputFocus();

  DALI_CHECK_FAIL( bHasKeyFocus, "ClearKeyInputFocus has failed because instead of clearing it is still on focus." );
  stage.Remove(control);

  DaliLog::PrintPass();
}

void ControlGetPinchGestureDetectorP()
{
  PinchGestureDetector pinchDetector ;
  Stage stage;
  Control control;

  DALI_CHECK_FAIL( !ControlGestureInit( stage, control), "Control GestureInit is Failed." );

  static_cast<Toolkit::Internal::Control&>( control.GetImplementation() ).EnableGestureDetection( Gesture::Pinch );

  pinchDetector = control.GetPinchGestureDetector();

  DALI_CHECK_FAIL( !pinchDetector, "GetPinchGestureDetector has failed because pinchDetector is empty." );

  stage.Remove(control);
  DaliLog::PrintPass();
}

void ControlGetPanGestureDetectorP()
{
  PanGestureDetector panDetector ;
  Stage stage;
  Control control;

  DALI_CHECK_FAIL( !ControlGestureInit(stage, control), "Control GestureInit is Failed." );

  static_cast<Toolkit::Internal::Control&>( control.GetImplementation() ).EnableGestureDetection( Gesture::Pan );

  panDetector = control.GetPanGestureDetector();

  DALI_CHECK_FAIL( !panDetector, "GetPanGestureDetector has failed because panDetector is empty." );

  stage.Remove(control);
  DaliLog::PrintPass();
}

void ControlGetTapGestureDetectorP()
{
  TapGestureDetector tapDetector ;
  Stage stage;
  Control control;

  DALI_CHECK_FAIL( !ControlGestureInit( stage, control), "Control GestureInit is Failed." );

  static_cast<Toolkit::Internal::Control&>( control.GetImplementation() ).EnableGestureDetection( Gesture::Tap );

  tapDetector = control.GetTapGestureDetector();

  DALI_CHECK_FAIL( !tapDetector,  "GetTapGestureDetector has failed because tapDetector is empty." );
  stage.Remove(control);

  DaliLog::PrintPass();
}

void ControlGetLongPressGestureDetectorP()
{
  LongPressGestureDetector longPressDetector;
  Stage stage;
  Control control;

  DALI_CHECK_FAIL( !ControlGestureInit(stage, control), "Control GestureInit is Failed." );

  static_cast<Toolkit::Internal::Control&>( control.GetImplementation() ).EnableGestureDetection( Gesture::LongPress );

  longPressDetector = control.GetLongPressGestureDetector();
  DALI_CHECK_FAIL( !longPressDetector, "GetLongPressGestureDetector has failed because longPressDetector is empty." );

  stage.Remove(control);
  DaliLog::PrintPass();
}

void ControlSetGetStyleNameP()
{
  const string STYLE_NAME = "textlabel";
  string strGetStyle = "";

  Control control = Control::New();
  DALI_CHECK_FAIL(!control, "Control::New() is failed." );

  control.SetStyleName(STYLE_NAME);
  strGetStyle = control.GetStyleName();

  DALI_CHECK_FAIL( strGetStyle != STYLE_NAME, "Set Style Name is mismatched with Get Style Name." );

  DaliLog::PrintPass();
}

void ControlSetGetBackgroundImageColorP()
{
  Control control = Control::New();
  DALI_CHECK_FAIL( !control, "Control::New() is failed." );

  control.SetBackgroundColor( Color::GREEN );
  Property::Value propValue = control.GetProperty( Control::Property::BACKGROUND );
  Property::Map* resultMap = propValue.GetMap();
  DALI_CHECK_FAIL( resultMap->Find( ColorVisual::Property::MIX_COLOR ) == NULL, "Control::SetBackgroundColor() is failed." );

  Vector4 color;
  resultMap->Find( ColorVisual::Property::MIX_COLOR )->Get( color );
  DALI_CHECK_FAIL( color != Color::GREEN, "Control Background Color is not GREEN." );

  control.ClearBackground();
  DALI_CHECK_FAIL( control.GetRendererCount() != 0u, "Control::ClearBackground() is failed." );

  DaliLog::PrintPass();
}

void ControlClearBackgroundP()
{
  Control control = Control::New();
  DALI_CHECK_FAIL( !control, "Control::New() is failed.");

  control.SetBackgroundColor( Color::MAGENTA );
  Property::Value propValue = control.GetProperty( Control::Property::BACKGROUND );
  Property::Map* resultMap = propValue.GetMap();
  DALI_CHECK_FAIL( resultMap->Find( ColorVisual::Property::MIX_COLOR ) == NULL, "Control::SetBackgroundColor() is failed." );

  Vector4 color;
  resultMap->Find( ColorVisual::Property::MIX_COLOR )->Get( color );
  DALI_CHECK_FAIL( color != Color::MAGENTA, "Control Background Color is not MAGENTA." );

  control.ClearBackground();
  DALI_CHECK_FAIL( control.GetRendererCount() != 0u, "Control::ClearBackground() is failed." );

  DaliLog::PrintPass();
}

void ControlKeyEventSignalP()
{
  Control control = Control::New();
  DALI_CHECK_FAIL(!control, "Control::New() is failed." );

  Stage::GetCurrent().Add( control );

  gKeyInputFocusCallBackCalled = false;
  try
  {
    control.KeyEventSignal();
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    if( control )
    {
      LOG_I("Callback for key input focus is called.");
      gKeyInputFocusCallBackCalled = true;
    }

  }

  Stage::GetCurrent().Remove(control);
  DaliLog::PrintPass();

}

void ControlKeyInputFocusGainedSignalP()
{
  Control control = Control::New();
  DALI_CHECK_FAIL(!control, "Control::New() is failed." );

  Stage::GetCurrent().Add( control );

  gKeyInputFocusCallBackCalled = false;
  control.KeyInputFocusGainedSignal().Connect(&CbControlKeyInputFocusCallback);

  control.SetKeyInputFocus();
  DALI_CHECK_FAIL( !gKeyInputFocusCallBackCalled, "Control KeyInputFocusGainedSignal is failed to connect the callback." );
  DALI_CHECK_FAIL( !control.HasKeyInputFocus(), "SetKeyInputFocus is failed to set Control Key Input Focus." );

  Stage::GetCurrent().Remove(control);
  DaliLog::PrintPass();
}

void ControlKeyInputFocusLostSignalP()
{
  Control control = Control::New();
  DALI_CHECK_FAIL(!control, "Control::New() is failed." );

  Stage::GetCurrent().Add( control );

  gKeyInputFocusCallBackCalled = false;
  control.KeyInputFocusLostSignal().Connect(&CbControlKeyInputFocusCallback);

  control.SetKeyInputFocus();
  DALI_CHECK_FAIL( !control.HasKeyInputFocus(), "SetKeyInputFocus is failed to set Control Key Input Focus." );
  DALI_CHECK_FAIL( gKeyInputFocusCallBackCalled, "Control KeyInputFocusLostSignal should not be emitted before clearing key input focus." );

  control.ClearKeyInputFocus();
  DALI_CHECK_FAIL( !gKeyInputFocusCallBackCalled, "Control KeyInputFocusLostSignal is failed to connect the callback." );
  DALI_CHECK_FAIL( control.HasKeyInputFocus(), "ClearKeyInputFocus is failed to clear Control Key Input Focus." );

  Stage::GetCurrent().Remove(control);
  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase            UtcDaliControlNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliControlNewP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliControlConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlCopyConstructorP
 * @since_tizen         2.4
 * @description         Creates another handle that points to the same real object.
 */

int UtcDaliControlCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Checks whether Assignmentoperator is executed successfully or not
 */

int UtcDaliControlOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlDowncastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliControlDowncastN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlDowncastP
 * @since_tizen         2.4
 * @description         Downcast an Object handle to Control.
 */

int UtcDaliControlDowncastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlSetAndHasKeyInputFocusP
 * @since_tizen         2.4
 * @description         Checks whether SetKeyInputFocus and HasKeyInputFocus apis are executed successfully or not
 */

int UtcDaliControlSetAndHasKeyInputFocusP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_SET_AND_HAS_KEY_INPUT_FOCUS_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlClearKeyInputFocusP
 * @since_tizen         2.4
 * @description         Checks whether ClearKeyInputFocus api are executed successfully or not
 */

int UtcDaliControlClearKeyInputFocusP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_CLEAR_KEY_INPUT_FOCUS_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlGetPinchGestureDetectorP
 * @since_tizen         2.4
 * @description         Checks whether GetPinchGestureDetector api is executed successfully or not
 */

int UtcDaliControlGetPinchGestureDetectorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_GET_PINCH_GESTURE_DETECTOR_P );
  application.MainLoop();

  return test_return_value;

}

/**
 * @testcase            UtcDaliControlGetPanGestureDetectorP
 * @since_tizen         2.4
 * @description         Checks whether GetPanGestureDetector api is executed successfully or not
 */

int UtcDaliControlGetPanGestureDetectorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_GET_PAN_GESTURE_DETECTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlGetTapGestureDetectorP
 * @since_tizen         2.4
 * @description         Checks whether GetTapGestureDetector api is executed successfully or not
 */

int UtcDaliControlGetTapGestureDetectorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_GET_TAP_GESTURE_DETECTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlGetLongPressGestureDetectorP
 * @since_tizen         2.4
 * @description         Checks whether GetLongPressGestureDetector api is executed successfully or not
 */

int UtcDaliControlGetLongPressGestureDetectorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_GET_LONG_PRESS_GESTURE_DETECTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlSetGetStyleNameP
 * @since_tizen         2.4
 * @description         Checks whether Sets the name of the style to be applied to the control is executed successfully or not
 */

int UtcDaliControlSetGetStyleNameP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_SET_GET_STYLE_NAME_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlSetGetBackgroundImageColorP
 * @since_tizen         2.4
 * @description         Checks whether Sets Background Color or Image can properly set the control Background color or not.
 */

int UtcDaliControlSetGetBackgroundImageColorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_SET_GET_BACKGROUND_IMAGE_COLOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlClearBackgroundP
 * @since_tizen         2.4
 * @description         Clears the background of control handle
 */

int UtcDaliControlClearBackgroundP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_CLEAR_BACKGROUND_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlKeyEventSignalP
 * @since_tizen         2.4
 * @description         Checks whether KeyEventSignal can emmit and call to callback function.
 */

int UtcDaliControlKeyEventSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_KEY_EVENT_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlKeyInputFocusGainedSignalP
 * @since_tizen         2.4
 * @description         Checks whether KeyInputFocusGainedSignal can emmit and call to callback function.
 */

int UtcDaliControlKeyInputFocusGainedSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_KEY_INPUT_FOCUS_GAINED_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}
/**
 * @testcase            UtcDaliControlKeyInputFocusLostSignalP
 * @since_tizen         2.4
 * @description         Checks whether KeyInputFocusLostSignal can emmit and call to callback function.
 */

int UtcDaliControlKeyInputFocusLostSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Control_TestApp testApp( application, CONTROL_KEY_INPUT_FOCUS_LOST_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}
