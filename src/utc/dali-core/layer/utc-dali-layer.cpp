#include "utc-dali-layer-impl.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Image

/**
 * @function            utc_Dali_Layer_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Layer_startup(void)
{
  test_return_value=0;
  gRenderCountLinearLayer=0;
}

/**
 * @function            utc_Dali_Layer_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Layer_cleanup(void)
{
}

namespace
{
  enum TEST_CASES_LIST_LAYER
  {
    LAYER_CONSTRUCTOR_P,
    LAYER_COPY_CONSTRUCTOR_P,
    LAYER_OPERATOR_ASSIGNMENT_P,
    LAYER_NEW_P,
    LAYER_IS_HOVER_CONSUMED_P,
    LAYER_SET_HOVER_CONSUMED_P,
    LAYER_IS_TOUCH_CONSUMED_P,
    LAYER_SET_TOUCH_CONSUMED_P,
    LAYER_DOWNCAST_P,
    LAYER_DOWNCAST_P2,
    LAYER_GET_DEPTH_P,
    LAYER_LOWER_BELOW_TO_BOTTOM_P,
    LAYER_MOVE_ABOVE_BELOW_P,
    LAYER_RAISE_ABOVE_TO_TOP_P,
    LAYER_SET_CLIPPING_BOX_P,
    LAYER_SET_CLIPPING_BOX_P2,
    LAYER_GET_CLIPPING_BOX_P,
    LAYER_SET_DEPTH_TEST_DISABLED_P,
    LAYER_IS_DEPTH_TEST_DISABLED_P,
    LAYER_SET_CLIPPING_P,
    LAYER_IS_CLIPPING_P,
    LAYER_SET_SORT_FUNCTION_P,
    LAYER_SET_BEHAVIOR_P,
    LAYER_GET_BEHAVIOR_P
  };

  struct Layer_TestApp : public ConnectionTracker
  {
    Layer_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Layer_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Layer_TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      if(test_return_value==TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
        return true;
      }

      VerdictTest();

      if(test_return_value==TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
      }
      return true;
    }

    void ExcuteTest()
    {
      switch (mTestCase)
      {

        case LAYER_CONSTRUCTOR_P:
          LayerConstructorP();
          break;

        case LAYER_COPY_CONSTRUCTOR_P:
          LayerCopyConstructorP();
          break;

        case LAYER_OPERATOR_ASSIGNMENT_P:
          LayerOperatorAssignmentP();
          break;

        case LAYER_NEW_P:
          LayerNewP();
          break;

        case LAYER_IS_HOVER_CONSUMED_P:
          LayerIsHoverConsumedP();
          break;

        case LAYER_SET_HOVER_CONSUMED_P:
          LayerSetHoverConsumedP();
          break;

        case LAYER_IS_TOUCH_CONSUMED_P:
          LayerIsTouchConsumedP();
          break;

        case LAYER_SET_TOUCH_CONSUMED_P:
          LayerSetTouchConsumedP();
          break;

        case LAYER_DOWNCAST_P:
          LayerDownCastP();
          break;

        case LAYER_DOWNCAST_P2:
          LayerDownCastP2();
          break;

        case LAYER_GET_DEPTH_P:
          LayerGetDepthP();
          break;

        case LAYER_LOWER_BELOW_TO_BOTTOM_P:
          LayerLowerBelowToBottomP();
          break;

        case LAYER_MOVE_ABOVE_BELOW_P:
          LayerMoveAboveBelowP();
          break;

        case LAYER_RAISE_ABOVE_TO_TOP_P:
          LayerRaiseAboveToTopP();
          break;

        case LAYER_SET_CLIPPING_BOX_P:
          LayerSetClippingBoxP();
          break;

        case LAYER_SET_CLIPPING_BOX_P2:
          LayerSetClippingBoxP2();
          break;

        case LAYER_GET_CLIPPING_BOX_P:
          LayerGetClippingBoxP();
          break;

        case LAYER_SET_DEPTH_TEST_DISABLED_P:
          LayerSetDepthTestDisabledP();
          break;

        case LAYER_IS_DEPTH_TEST_DISABLED_P:
          LayerIsDepthTestDisabledP();
          break;

        case LAYER_SET_CLIPPING_P:
          LayerSetClippingP();
          break;

        case LAYER_IS_CLIPPING_P:
          LayerIsClippingP();
          break;

        case LAYER_SET_SORT_FUNCTION_P:
          LayerSetSortFunctionP();
          break;

        case LAYER_SET_BEHAVIOR_P:
          LayerSetBehaviorP();
          break;

        case LAYER_GET_BEHAVIOR_P:
          LayerGetBehaviorP();
          break;
      }
    }
    void VerdictTest()
    {
      switch (mTestCase)
      {
        case LAYER_SET_SORT_FUNCTION_P:
          switch (gRenderCountLinearLayer)
          {
            case 0:
              VTLayerSetSortFunction001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;
        default:
          mTimer.Stop();
          mApplication.Quit();
      }
    }
    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

} // unnamed namespace


/**
 * @testcase           UtcDaliLayerConstructorP
 * @since_tizen        2.4
 * @description        check if Constructor api works or not.
 */

int UtcDaliLayerConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerCopyConstructorP
 * @since_tizen        2.4
 * @description        check if CopyConstructor api works or not.
 */

int UtcDaliLayerCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerOperatorAssignmentP
 * @since_tizen        2.4
 * @description        check if OperatorAssignment api works or not.
 */

int UtcDaliLayerOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerNewP
 * @since_tizen        2.4
 * @description        check if New api works or not.
 */

int UtcDaliLayerNewP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerIsHoverConsumedP
 * @since_tizen        2.4
 * @description        check if IsHoverConsumed api works or not.
 */

int UtcDaliLayerIsHoverConsumedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_IS_HOVER_CONSUMED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerSetHoverConsumedP
 * @since_tizen        2.4
 * @description        check if SetHoverConsumed api works or not.
 */

int UtcDaliLayerSetHoverConsumedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_SET_HOVER_CONSUMED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerIsTouchConsumedP
 * @since_tizen        2.4
 * @description        check if IsTouchConsumed api works or not.
 */

int UtcDaliLayerIsTouchConsumedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_IS_TOUCH_CONSUMED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerSetTouchConsumedP
 * @since_tizen        2.4
 * @description        check if SetTouchConsumed api works or not.
 */

int UtcDaliLayerSetTouchConsumedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_SET_TOUCH_CONSUMED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerDownCastP
 * @since_tizen        2.4
 * @description        check if DownCast api works or not.
 */

int UtcDaliLayerDownCastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerDownCastP2
 * @since_tizen        2.4
 * @description        check if DownCast api works or not.
 */

int UtcDaliLayerDownCastP2(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_DOWNCAST_P2 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerGetDepthP
 * @since_tizen        2.4
 * @description        check if GetDepth api works or not.
 */

int UtcDaliLayerGetDepthP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_GET_DEPTH_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerLowerBelowToBottomP
 * @since_tizen        2.4
 * @description        check if LowerBelowToBottom api works or not.
 */

int UtcDaliLayerLowerBelowToBottomP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_LOWER_BELOW_TO_BOTTOM_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerMoveAboveBelowP
 * @since_tizen        2.4
 * @description        check if MoveAboveBelow api works or not.
 */

int UtcDaliLayerMoveAboveBelowP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_MOVE_ABOVE_BELOW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerRaiseAboveToTopP
 * @since_tizen        2.4
 * @description        check if RaiseAboveToTop api works or not.
 */

int UtcDaliLayerRaiseAboveToTopP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_RAISE_ABOVE_TO_TOP_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerSetClippingBoxP
 * @since_tizen        2.4
 * @description        check if SetClippingBox api works or not.
 */

int UtcDaliLayerSetClippingBoxP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_SET_CLIPPING_BOX_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerSetClippingBoxP2
 * @since_tizen        2.4
 * @description        check if SetClippingBox api works or not.
 */

int UtcDaliLayerSetClippingBoxP2(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_SET_CLIPPING_BOX_P2 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerGetClippingBoxP
 * @since_tizen        2.4
 * @description        check if GetClippingBox api works or not.
 */

int UtcDaliLayerGetClippingBoxP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_GET_CLIPPING_BOX_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerSetDepthTestDisabledP
 * @since_tizen        2.4
 * @description        check if SetDepthTestDisabled api works or not.
 */

int UtcDaliLayerSetDepthTestDisabledP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_SET_DEPTH_TEST_DISABLED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerIsDepthTestDisabledP
 * @since_tizen        2.4
 * @description        check if IsDepthTestDisabled api works or not.
 */

int UtcDaliLayerIsDepthTestDisabledP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_IS_DEPTH_TEST_DISABLED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerSetClippingP
 * @since_tizen        2.4
 * @description        check if SetClipping api works or not.
 */

int UtcDaliLayerSetClippingP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_SET_CLIPPING_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerIsClippingP
 * @since_tizen        2.4
 * @description        check if IsClipping api works or not.
 */

int UtcDaliLayerIsClippingP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_IS_CLIPPING_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerSetSortFunctionP
 * @since_tizen        2.4
 * @description        check if SetSortFunction api works or not.
 */

int UtcDaliLayerSetSortFunctionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_SET_SORT_FUNCTION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerSetBehaviorP
 * @since_tizen        2.4
 * @description        check if SetBehavior api works or not.
 */

int UtcDaliLayerSetBehaviorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_SET_BEHAVIOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase           UtcDaliLayerGetBehaviorP
 * @since_tizen        2.4
 * @description        check if GetBehavior api works or not.
 */

int UtcDaliLayerGetBehaviorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Layer_TestApp testApp(application, LAYER_GET_BEHAVIOR_P );
  application.MainLoop();

  return test_return_value;
}
