#include "utc-dali-custom-actor-impl-impl.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;
//& set: CustomActorImpl

/**
 * @function            utc_Dali_CustomActorImpl_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_CustomActorImpl_startup(void)
{
  test_return_value=TC_PASS;
  masterCallStack.clear();
  gRenderCountCustomActor1=TC_PASS;
}

/**
 * @function            utc_Dali_CustomActorImpl_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_CustomActorImpl_cleanup(void)
{
}

namespace
{
  enum TEST_CASES_LIST_CUSTOM_ACTOR
  {
    CUSTOM_ACTOR_IMPL_REQUIRES_HOVER_EVENTS_P,
    CUSTOM_ACTOR_IMPL_GET_NATURAL_SIZE_P,
    CUSTOM_ACTOR_IMPL_ON_CHILD_ADD_P,
    CUSTOM_ACTOR_IMPL_ON_CHILD_REMOVE_P,
    CUSTOM_ACTOR_IMPL_ON_KEY_EVENT_P,
    CUSTOM_ACTOR_IMPL_ON_KEY_INPUT_FOCUS_GAINED_P,
    CUSTOM_ACTOR_IMPL_ON_KEY_INPUT_FOCUS_LOST_P,
    CUSTOM_ACTOR_IMPL_ON_WHEEL_EVENT_P,
    CUSTOM_ACTOR_IMPL_ON_SIZE_SET_P,
    CUSTOM_ACTOR_IMPL_ON_STAGE_CONNECTION_P,
    CUSTOM_ACTOR_IMPL_ON_STAGE_DISCONNECTION_P,
    CUSTOM_ACTOR_IMPL_ON_TOUCH_EVENT_P,
    CUSTOM_ACTOR_IMPL_REQUIRES_WHEEL_EVENTS_P,
    CUSTOM_ACTOR_IMPL_REQUIRES_TOUCH_EVENTS_P,
    CUSTOM_ACTOR_IMPL_SELF_P,
    CUSTOM_ACTOR_IMPL_SET_REQUIRES_WHEEL_EVENTS_P,
    CUSTOM_ACTOR_IMPL_CUSTOM_ACTOR_IMPL_WITH_BOOL_PARAM_P,
    CUSTOM_ACTOR_IMPL_RELAYOUT_REQUEST_P,
    CUSTOM_ACTOR_IMPL_GET_EXTENSION_P,
    CUSTOM_ACTOR_IMPL_ON_PROPERTY_SET_P,
    CUSTOM_ACTOR_IMPL_ON_SIZE_ANIMATION_P,
    CUSTOM_ACTOR_IMPL_ON_HOVER_EVENT_P,
    CUSTOM_ACTOR_IMPL_GET_HEIGHT_FOR_WIDTH_BASE_P,
    CUSTOM_ACTOR_IMPL_GET_WIDTH_FOR_HEIGHT_BASE_P,
    CUSTOM_ACTOR_IMPL_CALCULATE_CHILD_SIZE_BASE_P,
    CUSTOM_ACTOR_IMPL_RELAYOUT_DEPENDENT_ON_CHILDREN_BASE_P
  };

  struct Custom_Actor_TestApp : public ConnectionTracker
  {
    Custom_Actor_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Custom_Actor_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Custom_Actor_TestApp::Tick );
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
        case CUSTOM_ACTOR_IMPL_REQUIRES_HOVER_EVENTS_P:
          CustomActorImplRequiresHoverEventsP();
          break;

        case CUSTOM_ACTOR_IMPL_GET_NATURAL_SIZE_P:
          CustomActorImplGetNaturalSizeP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_CHILD_ADD_P:
          CustomActorImplOnChildAddP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_CHILD_REMOVE_P:
          CustomActorImplOnChildRemoveP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_KEY_EVENT_P:
          CustomActorImplOnKeyEventP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_KEY_INPUT_FOCUS_GAINED_P:
          CustomActorImplOnKeyInputFocusGainedP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_KEY_INPUT_FOCUS_LOST_P:
          CustomActorImplOnKeyInputFocusLostP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_WHEEL_EVENT_P:
          CustomActorImplOnWheelEventP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_SIZE_SET_P:
          CustomActorImplOnSizeSetP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_STAGE_CONNECTION_P:
          CustomActorImplOnStageConnectionP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_STAGE_DISCONNECTION_P:
          CustomActorImplOnStageDisconnectionP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_TOUCH_EVENT_P:
          CustomActorImplOnTouchEventP();
          break;

        case CUSTOM_ACTOR_IMPL_REQUIRES_WHEEL_EVENTS_P:
          CustomActorImplRequiresWheelEventsP();
          break;

        case CUSTOM_ACTOR_IMPL_REQUIRES_TOUCH_EVENTS_P:
          CustomActorImplRequiresTouchEventsP();
          break;

        case CUSTOM_ACTOR_IMPL_SELF_P:
          CustomActorImplSelfP();
          break;

        case CUSTOM_ACTOR_IMPL_SET_REQUIRES_WHEEL_EVENTS_P:
          CustomActorImplSetRequiresWheelEventsP();
          break;

        case CUSTOM_ACTOR_IMPL_CUSTOM_ACTOR_IMPL_WITH_BOOL_PARAM_P:
          CustomActorImplCustomActorImplWithBoolParamP();
          break;

        case CUSTOM_ACTOR_IMPL_RELAYOUT_REQUEST_P:
          CustomActorImplRelayoutRequestP();
          break;

        case CUSTOM_ACTOR_IMPL_GET_EXTENSION_P:
          CustomActorImplGetExtensionP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_PROPERTY_SET_P:
          CustomActorImplOnPropertySetP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_SIZE_ANIMATION_P:
          CustomActorOnSizeAnimationP();
          break;

        case CUSTOM_ACTOR_IMPL_ON_HOVER_EVENT_P:
          CustomActorOnHoverEventP();
          break;

        case CUSTOM_ACTOR_IMPL_GET_HEIGHT_FOR_WIDTH_BASE_P:
          CustomActorImplGetHeightForWidthBaseP();
          break;

        case CUSTOM_ACTOR_IMPL_GET_WIDTH_FOR_HEIGHT_BASE_P:
          CustomActorImplGetWidthForHeightBaseP();
          break;

        case CUSTOM_ACTOR_IMPL_CALCULATE_CHILD_SIZE_BASE_P:
          CustomActorImplCalculateChildSizeBaseP();
          break;

        case CUSTOM_ACTOR_IMPL_RELAYOUT_DEPENDENT_ON_CHILDREN_BASE_P:
          CustomActorImplRelayoutDependentOnChildrenBaseP();
          break;
      }
    }
    void VerdictTest()
    {
      switch (mTestCase)
      {
        case CUSTOM_ACTOR_IMPL_GET_NATURAL_SIZE_P:
          switch (gRenderCountCustomActor1)
          {
            case 0:
              VTCustomActorImplGetNaturalSize001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CUSTOM_ACTOR_IMPL_ON_WHEEL_EVENT_P:
          switch (gRenderCountCustomActor1)
          {
            case 0:
              VTCustomActorImplOnWheelEvent001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CUSTOM_ACTOR_IMPL_REQUIRES_WHEEL_EVENTS_P:
          switch (gRenderCountCustomActor1)
          {
            case 0:
              VTCustomActorImplRequiresWheelEvents001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CUSTOM_ACTOR_IMPL_RELAYOUT_REQUEST_P:
          switch (gRenderCountCustomActor1)
          {
            case 0:
              VTCustomActorImplRelayoutRequest001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CUSTOM_ACTOR_IMPL_ON_SIZE_ANIMATION_P:
          switch (gRenderCountCustomActor1)
          {
            case 0:
              VTCustomActorOnSizeAnimation001();
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
 * @testcase           UtcDaliCustomActorImplRequiresHoverEventsP
 * @since_tizen        2.4
 * @description        check if RequiresHoverEvents api works or not.
 */

int UtcDaliCustomActorImplRequiresHoverEventsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_REQUIRES_HOVER_EVENTS_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplGetNaturalSizeP
 * @since_tizen        2.4
 * @description        check if GetNaturalSize api works or not.
 */

int UtcDaliCustomActorImplGetNaturalSizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_GET_NATURAL_SIZE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnChildAddP
 * @since_tizen        2.4
 * @description        check if OnChildAdd api works or not.
 */

int UtcDaliCustomActorImplOnChildAddP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_CHILD_ADD_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnChildRemoveP
 * @since_tizen        2.4
 * @description        check if OnChildRemove api works or not.
 */

int UtcDaliCustomActorImplOnChildRemoveP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_CHILD_REMOVE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnKeyEventP
 * @since_tizen        2.4
 * @description        check if OnKeyEvent api works or not.
 */

int UtcDaliCustomActorImplOnKeyEventP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_KEY_EVENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnKeyInputFocusGainedP
 * @since_tizen        2.4
 * @description        check if OnKeyInputFocusGained api works or not.
 */

int UtcDaliCustomActorImplOnKeyInputFocusGainedP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_KEY_INPUT_FOCUS_GAINED_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnKeyInputFocusLostP
 * @since_tizen        2.4
 * @description        check if OnKeyInputFocusLost api works or not.
 */

int UtcDaliCustomActorImplOnKeyInputFocusLostP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_KEY_INPUT_FOCUS_LOST_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnWheelEventP
 * @since_tizen        2.4
 * @description        check if OnWheelEvent api works or not.
 */

int UtcDaliCustomActorImplOnWheelEventP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_WHEEL_EVENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnSizeSetP
 * @since_tizen        2.4
 * @description        check if OnSizeSet api works or not.
 */

int UtcDaliCustomActorImplOnSizeSetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_SIZE_SET_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnStageConnectionP
 * @since_tizen        2.4
 * @description        check if OnStageConnection api works or not.
 */

int UtcDaliCustomActorImplOnStageConnectionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_STAGE_CONNECTION_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnStageDisconnectionP
 * @since_tizen        2.4
 * @description        check if OnStageDisconnection api works or not.
 */

int UtcDaliCustomActorImplOnStageDisconnectionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_STAGE_DISCONNECTION_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnTouchEventP
 * @since_tizen        2.4
 * @description        check if OnTouchEvent api works or not.
 */

int UtcDaliCustomActorImplOnTouchEventP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_TOUCH_EVENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplRequiresWheelEventsP
 * @since_tizen        2.4
 * @description        check if RequiresWheelEvents api works or not.
 */

int UtcDaliCustomActorImplRequiresWheelEventsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_REQUIRES_WHEEL_EVENTS_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplRequiresTouchEventsP
 * @since_tizen        2.4
 * @description        check if RequiresTouchEvents api works or not.
 */

int UtcDaliCustomActorImplRequiresTouchEventsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_REQUIRES_TOUCH_EVENTS_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplSelfP
 * @since_tizen        2.4
 * @description        check if Self api works or not.
 */

int UtcDaliCustomActorImplSelfP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_SELF_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplSetRequiresWheelEventsP
 * @since_tizen        2.4
 * @description        check if RequiresWheelEvents api works or not.
 */

int UtcDaliCustomActorImplSetRequiresWheelEventsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_SET_REQUIRES_WHEEL_EVENTS_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplCustomActorImplWithBoolParamP
 * @since_tizen        2.4
 * @description        check if CustomActorImplWithBoolParam api works or not.
 */

int UtcDaliCustomActorImplCustomActorImplWithBoolParamP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_CUSTOM_ACTOR_IMPL_WITH_BOOL_PARAM_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplRelayoutRequestP
 * @since_tizen        2.4
 * @description        check if RelayoutRequest api works or not.
 */

int UtcDaliCustomActorImplRelayoutRequestP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_RELAYOUT_REQUEST_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplGetExtensionP
 * @since_tizen        2.4
 * @description        check if GetExtension api works or not.
 */

int UtcDaliCustomActorImplGetExtensionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_GET_EXTENSION_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnPropertySetP
 * @since_tizen        2.4
 * @description        check if OnPropertySet api works or not.
 */

int UtcDaliCustomActorImplOnPropertySetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_PROPERTY_SET_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnSizeAnimationP
 * @since_tizen        2.4
 * @description        check if OnSizeAnimation api works or not.
 */

int UtcDaliCustomActorImplOnSizeAnimationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_SIZE_ANIMATION_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplOnHoverEventP
 * @since_tizen        2.4
 * @description        check if OnHoverEvent api works or not.
 */

int UtcDaliCustomActorImplOnHoverEventP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_ON_HOVER_EVENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplGetHeightForWidthBaseP
 * @since_tizen        2.4
 * @description        check if GetHeightForWidthBase api works or not.
 */

int UtcDaliCustomActorImplGetHeightForWidthBaseP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_GET_HEIGHT_FOR_WIDTH_BASE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplGetWidthForHeightBaseP
 * @since_tizen        2.4
 * @description        check if GetWidthForHeightBase api works or not.
 */

int UtcDaliCustomActorImplGetWidthForHeightBaseP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_GET_WIDTH_FOR_HEIGHT_BASE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase           UtcDaliCustomActorImplCalculateChildSizeBaseP
 * @since_tizen        2.4
 * @description        check if CalculateChildSizeBase api works or not.
 */

int UtcDaliCustomActorImplCalculateChildSizeBaseP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_CALCULATE_CHILD_SIZE_BASE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorImplRelayoutDependentOnChildrenBaseP
 * @since_tizen        2.4
 * @description        check if RelayoutDependentOnChildrenBase api works or not.
 */

int UtcDaliCustomActorImplRelayoutDependentOnChildrenBaseP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_IMPL_RELAYOUT_DEPENDENT_ON_CHILDREN_BASE_P);
  application.MainLoop();
  return test_return_value;
}
