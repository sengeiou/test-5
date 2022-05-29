#include "utc-dali-render-task-impl.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

unsigned int gDelayedInterVal = INTERVAL;

//& set: Rendertask

/**
 * @function            utc_Dali_RenderTask_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_RenderTask_startup(void)
{
  test_return_value = TC_PASS;
  gRenderCountRenderTask=TC_PASS;
}

/**
 * @function            utc_Dali_RenderTask_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_RenderTask_cleanup(void)
{
}


namespace
{
  enum TEST_CASES_LIST
  {
    RENDER_TASK_SETGETVIEWPORTSIZE_P,
    RENDER_TASK_SETGETCULLMODE_P,
    RENDER_TASK_GETCULLMODE_N,
    RENDER_TASK_SETCULLMODE_N,
    RENDER_TASK_CONSTRUCTORASSIGNMENTOPERATOR_P,
    RENDER_TASK_DOWNCAST_P,
    RENDER_TASK_DOWNCAST_N,
    RENDER_TASK_FINISHEDSIGNAL_P,
    RENDER_TASK_SETGETSOURCEACTOR_P,
    RENDER_TASK_GETSOURCEACTOR_N,
    RENDER_TASK_SETGETSCREENTOFRAMEBUFFERMAPPINGACTOR_P,
    RENDER_TASK_SETSCREENTOFRAMEBUFFERMAPPINGACTOR_N,
    RENDER_TASK_SETGETCLEARCOLOR_P,
    RENDER_TASK_GETCLEARCOLOR_N,
    RENDER_TASK_SETCLEARCOLOR_N,
    RENDER_TASK_SETGETCLEARENABLED_P,
    RENDER_TASK_SETCLEARENABLED_N,
    RENDER_TASK_GETCLEARENABLED_N,
    RENDER_TASK_SETGETVIEWPORTPOSITION_P,
    RENDER_TASK_SETGETVIEWPORT_P,
    RENDER_TASK_GETVIEWPORT_N,
    RENDER_TASK_SETVIEWPORT_N,
    RENDER_TASK_SETGETTARGETFRAMEBUFFER_P,
    RENDER_TASK_SETGETREFRESHRATE_P,
    RENDER_TASK_SETGETINPUTENABLE_P,
    RENDER_TASK_SETGETCAMERAACTOR_P,
    RENDER_TASK_GETCAMERAACTOR_N,
    RENDER_TASK_SETISEXCLUSIVE_P,
    RENDER_TASK_SETEXCLUSIVE_N,
    RENDER_TASK_ISEXCLUSIVE_N,
    RENDER_TASK_SETGETSETSCREENTOFRAMEBUFFERFUNCTIONWITHFULLSCREEN_P,
    RENDER_TASK_SETGETSETSCREENTOFRAMEBUFFERFUNCTIONWITHDEFAULTSCREEN_P,
    RENDER_TASK_SETGETSETSCREENTOFRAMEBUFFERFUNCTION_N,
    RENDER_TASK_GETSCREENTOFRAMEBUFFERFUNCTION_N,
    RENDER_TASK_WORLDTOVIEWPORT_P,
    RENDER_TASK_VIEWPORTTOLOCAL_P
  };

  struct TestApp : public ConnectionTracker
  {
    TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      mApplication.GetWindow().ShowIndicator( Dali::Window::INVISIBLE );

      ExcuteTest();
      mTimer = Timer::New( gDelayedInterVal );
      mTimer.TickSignal().Connect( this, &TestApp::Tick );
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
        case RENDER_TASK_SETGETVIEWPORTSIZE_P:
          RenderTaskSetGetViewportSizeP();
          gDelayedInterVal = RENDER_DELAY_TIME;
          break;

        case RENDER_TASK_SETGETCULLMODE_P:
          RenderTaskSetGetCullModeP();
          break;

        case RENDER_TASK_SETCULLMODE_N:
          RenderTaskSetCullModeN();
          break;

        case RENDER_TASK_GETCULLMODE_N:
          RenderTaskGetCullModeN();
          break;

        case RENDER_TASK_CONSTRUCTORASSIGNMENTOPERATOR_P:
          RenderTaskConstructorAssignmentOperatorP();
          break;

        case RENDER_TASK_DOWNCAST_P:
          RenderTaskDownCastP();
          break;

        case RENDER_TASK_DOWNCAST_N:
          RenderTaskDownCastN();
          break;

        case RENDER_TASK_FINISHEDSIGNAL_P:
          RenderTaskFinishedSignalP();
          break;

        case RENDER_TASK_SETGETSOURCEACTOR_P:
          RenderTaskSetGetSourceActorP();
          break;

        case RENDER_TASK_GETSOURCEACTOR_N:
          RenderTaskGetSourceActorN();
          break;

        case RENDER_TASK_SETGETSCREENTOFRAMEBUFFERMAPPINGACTOR_P:
          RenderTaskSetGetScreenToFrameBufferMappingActorP();
          break;

        case RENDER_TASK_SETSCREENTOFRAMEBUFFERMAPPINGACTOR_N:
          RenderTaskSetScreenToFrameBufferMappingActorN();
          break;

        case RENDER_TASK_SETGETCLEARCOLOR_P:
          RenderTaskSetGetClearColorP();
          break;

        case RENDER_TASK_SETCLEARCOLOR_N:
          RenderTaskSetClearColorN();
          break;

        case RENDER_TASK_GETCLEARCOLOR_N:
          RenderTaskGetClearColorN();
          break;

        case RENDER_TASK_SETGETCLEARENABLED_P:
          RenderTaskSetGetClearEnabledP();
          break;

        case RENDER_TASK_SETCLEARENABLED_N:
          RenderTaskSetClearEnabledN();
          break;

        case RENDER_TASK_GETCLEARENABLED_N:
          RenderTaskGetClearEnabledN();
          break;

        case RENDER_TASK_SETGETVIEWPORTPOSITION_P:
          RenderTaskSetGetViewportPositionP();
          gDelayedInterVal = RENDER_DELAY_TIME;
          break;

        case RENDER_TASK_SETGETVIEWPORT_P:
          RenderTaskSetAndGetViewportP();
          gDelayedInterVal = RENDER_DELAY_TIME;
          break;

        case RENDER_TASK_SETVIEWPORT_N:
          RenderTaskSetViewportN();
          break;

        case RENDER_TASK_GETVIEWPORT_N:
          RenderTaskGetViewportN();
          break;

        case RENDER_TASK_SETGETTARGETFRAMEBUFFER_P:
          RenderTaskSetGetTargetFrameBufferP();
          break;

        case RENDER_TASK_SETGETREFRESHRATE_P:
          RenderTaskSetGetRefreshRateP();
          break;

        case RENDER_TASK_SETGETINPUTENABLE_P:
          RenderTaskSetGetInputEnableP();
          break;

        case RENDER_TASK_SETGETCAMERAACTOR_P:
          RenderTaskSetGetCameraActorP();
          break;

        case RENDER_TASK_GETCAMERAACTOR_N:
          RenderTaskGetCameraActorN();
          break;

        case RENDER_TASK_SETISEXCLUSIVE_P:
          RenderTaskSetIsExclusiveP();
          break;

        case RENDER_TASK_SETEXCLUSIVE_N:
          RenderTaskSetExclusiveN();
          break;

        case RENDER_TASK_ISEXCLUSIVE_N:
          RenderTaskIsExclusiveN();
          break;

        case RENDER_TASK_SETGETSETSCREENTOFRAMEBUFFERFUNCTIONWITHFULLSCREEN_P:
          RenderTaskSetGetSetScreenToFrameBufferFunctionWithFullScreenP();
          break;

        case RENDER_TASK_SETGETSETSCREENTOFRAMEBUFFERFUNCTIONWITHDEFAULTSCREEN_P:
          RenderTaskSetGetSetScreenToFrameBufferFunctionWithDefaultScreenP();
          break;

        case RENDER_TASK_SETGETSETSCREENTOFRAMEBUFFERFUNCTION_N:
          RenderTaskSetGetSetScreenToFrameBufferFunctionN();
          break;

        case RENDER_TASK_GETSCREENTOFRAMEBUFFERFUNCTION_N:
          RenderTaskGetScreenToFrameBufferFunctionN();
          break;

        case RENDER_TASK_WORLDTOVIEWPORT_P:
          RenderTaskWorldToViewportP();
          break;

        case RENDER_TASK_VIEWPORTTOLOCAL_P:
          RenderTaskViewportToLocalP();
          break;
      }
    }
    void VerdictTest()
    {
      switch (mTestCase)
      {
        case RENDER_TASK_SETGETVIEWPORTSIZE_P:
          switch (gRenderCountRenderTask)
          {
            case 0:
              VTRenderTaskSetGetViewportSize001();
              gRenderCountRenderTask++;
              break;

            case 1:
              VTRenderTaskSetGetViewportSize002();
              gRenderCountRenderTask++;
              break;

            case 2:
              VTRenderTaskSetGetViewportSize003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;
        case RENDER_TASK_SETGETVIEWPORTPOSITION_P:
          switch (gRenderCountRenderTask)
          {
            case 0:
              VTRenderTaskSetGetViewportPosition001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case RENDER_TASK_SETGETVIEWPORT_P:
          switch (gRenderCountRenderTask)
          {
            case 0:
              VTRenderTaskSetGetViewport001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case RENDER_TASK_WORLDTOVIEWPORT_P:
          switch (gRenderCountRenderTask)
          {
            case 0:
              VTRenderTaskWorldToViewport001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case RENDER_TASK_VIEWPORTTOLOCAL_P:
          switch (gRenderCountRenderTask)
          {
            case 0:
              VTRenderTaskViewportToLocal001();
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

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace


/**
 * @testcase        UtcDaliRenderTaskViewportToLocalP
 * @since_tizen     2.4
 * @description     Checks if ViewportToLocal is working or not.
 */
int UtcDaliRenderTaskViewportToLocalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_VIEWPORTTOLOCAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskWorldToViewportP
 * @since_tizen     2.4
 * @description     Checks if WorldToViewport is working or not.
 */
int UtcDaliRenderTaskWorldToViewportP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_WORLDTOVIEWPORT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetGetViewportSizeP
 * @since_tizen     2.4
 * @description     Retrieve the set GL viewport size used when rendering.
 */
int UtcDaliRenderTaskSetGetViewportSizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETVIEWPORTSIZE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetGetCullModeP
 * @since_tizen     2.4
 * @description     Check whether the render task will cull the actors to the camera's view frustum.
 */
int UtcDaliRenderTaskSetGetCullModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETCULLMODE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetCullModeN
 * @since_tizen     2.4
 * @description     Check whether the render task will cull the actors to the camera's view frustum, when RenderTask is uninitialzed.
 */
int UtcDaliRenderTaskSetCullModeN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETCULLMODE_N);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliRenderTaskGetCullModeN
 * @since_tizen     2.4
 * @description     Check whether the render task will cull the actors to the camera's view frustum, when RenderTask is uninitialzed.
 */
int UtcDaliRenderTaskGetCullModeN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_GETCULLMODE_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskConstructorOperatorAssignmentP
 * @since_tizen     2.4
 * @description     Checks whether RenderTask  constructor and copy constructor and assignment operator are executed successfully or not
 */
int UtcDaliRenderTaskConstructorOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_CONSTRUCTORASSIGNMENTOPERATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskDownCastP
 * @since_tizen     2.4
 * @description     Checks whether Downcast is executed successfully or not
 */
int UtcDaliRenderTaskDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskDownCastN
 * @since_tizen     2.4
 * @description     Checks whether Downcast is executed successfully or not
 */
int UtcDaliRenderTaskDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskFinishedSignalP
 * @since_tizen     2.4
 * @description     Checks whether render finished signal is works successfully or not
 */
int UtcDaliRenderTaskFinishedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_FINISHEDSIGNAL_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliRenderTaskSetGetSourceActorP
 * @since_tizen     2.4
 * @description     Checks whether SetSourceActor and GetSourceActor api is executed successfully or not
 */
int UtcDaliRenderTaskSetGetSourceActorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETSOURCEACTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskGetSourceActorN
 * @since_tizen     2.4
 * @description     Checks whether GetSourceActor api is executed successfully or not
 */
int UtcDaliRenderTaskSetGetSourceActorN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_GETSOURCEACTOR_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetGetScreenToFrameBufferMappingActorP
 * @since_tizen     2.4
 * @description     Checks whether SetScreenToFrameBufferMappingActor and GetScreenToFrameBufferMappingActor api is executed successfully or not
 */
int UtcDaliRenderTaskSetGetScreenToFrameBufferMappingActorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETSCREENTOFRAMEBUFFERMAPPINGACTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetScreenToFrameBufferMappingActorN
 * @since_tizen     2.4
 * @description     Checks whether SetScreenToFrameBufferMappingActor api is executed successfully or not, for unintialized RenderTask handle
 */
int UtcDaliRenderTaskSetScreenToFrameBufferMappingActorN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETSCREENTOFRAMEBUFFERMAPPINGACTOR_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetGetClearColorP
 * @since_tizen     2.4
 * @description     Checks whether SetClearColor and GetClearColor api is executed successfully or not
 */
int UtcDaliRenderTaskSetGetClearColorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETCLEARCOLOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetClearColorN
 * @since_tizen     2.4
 * @description     Checks whether SetClearColor api is executed successfully or not, with uninitialized RenderTask handle
 */
int UtcDaliRenderTaskSetClearColorN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETCLEARCOLOR_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskGetClearColorN
 * @since_tizen     2.4
 * @description     Checks whether GetClearColor api is executed successfully or not, with uninitialized RenderTask handle
 */
int UtcDaliRenderTaskGetClearColorN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_GETCLEARCOLOR_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetGetClearEnabledP
 * @since_tizen     2.4
 * @description     Checks whether SetClearEnabled and GetClearEnabled api is executed successfully or not
 */
int UtcDaliRenderTaskSetGetClearEnabledP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETCLEARENABLED_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetClearEnabledN
 * @since_tizen     2.4
 * @description     Checks whether SetClearEnabled api is executed successfully or not, with uninitialized RenderTask handle
 */
int UtcDaliRenderTaskSetClearEnabledN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETCLEARENABLED_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskGetClearEnabledN
 * @since_tizen     2.4
 * @description     Checks whether GetClearEnabled api is executed successfully or not, with uninitialized RenderTask handle
 */
int UtcDaliRenderTaskGetClearEnabledN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_GETCLEARENABLED_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetGetViewportPositionP
 * @since_tizen     2.4
 * @description     Checks whether SetViewportPosition and GetViewportPosition api is executed successfully or not
 */
int UtcDaliRenderTaskSetGetViewportPositionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETVIEWPORTPOSITION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetAndGetViewportP
 * @since_tizen     2.4
 * @description     Checks whether SetViewport and GetViewport api is executed successfully or not
 */
int UtcDaliRenderTaskSetAndGetViewportP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETVIEWPORT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliRenderTaskGetViewportN
 * @since_tizen     2.4
 * @description     Checks whether GetViewport api is executed successfully or not, for uninitialized RenderTask handle
 */
int UtcDaliRenderTaskGetViewportN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_GETVIEWPORT_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetViewportN
 * @since_tizen     2.4
 * @description     Checks whether GetViewport api is executed successfully or not, for uninitialized RenderTask handle
 */
int UtcDaliRenderTaskSetViewportN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETVIEWPORT_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetGetTargetFrameBufferP
 * @since_tizen     2.4
 * @description     Checks whether SetTargetFrameBuffer and GetTargetFrameBuffer api is executed successfully or not
 */
int UtcDaliRenderTaskSetGetTargetFrameBufferP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETTARGETFRAMEBUFFER_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetGetRefreshRateP
 * @since_tizen     2.4
 * @description     Checks whether SetRefreshRate and GetRefreshRate api is executed successfully or not
 */
int UtcDaliRenderTaskSetGetRefreshRateP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETREFRESHRATE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetGetInputEnableP
 * @since_tizen     2.4
 * @description     Checks whether SetInputEnabled and GetInputEnabled api is executed successfully or not
 */
int UtcDaliRenderTaskSetGetInputEnableP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETINPUTENABLE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetGetCameraActorP
 * @since_tizen     2.4
 * @description     Checks whether SetCameraActor and GetCameraActor api is executed successfully or not
 */
int UtcDaliRenderTaskSetGetCameraActorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETCAMERAACTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskGetCameraActorN
 * @since_tizen     2.4
 * @description     Checks whether GetCameraActor api is executed successfully or not
 */
int UtcDaliRenderTaskGetCameraActorN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_GETCAMERAACTOR_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetIsExclusiveP
 * @since_tizen     2.4
 * @description     Checks whether SetExclusive and IsExclusive api is executed successfully or not
 */
int UtcDaliRenderTaskSetIsExclusiveP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETISEXCLUSIVE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetExclusiveN
 * @since_tizen     2.4
 * @description     Checks whether SetExclusive api is executed successfully or not
 */
int UtcDaliRenderTaskSetExclusiveN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_ISEXCLUSIVE_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskIsExclusiveN
 * @since_tizen     2.4
 * @description     Checks whether IsExclusive api is executed successfully or not
 */
int UtcDaliRenderTaskIsExclusiveN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_ISEXCLUSIVE_N);
  application.MainLoop();
  return test_return_value;
}
/**
 * @testcase        UtcDaliRenderTaskSetGetSetScreenToFrameBufferFunctionWithFullScreenP
 * @since_tizen     2.4
 * @description     Checks whether SetScreenToFrameBufferFunction and GetScreenToFrameBufferFunction api for FULLSCREEN_FRAMEBUFFER_FUNCTION is executed successfully or not
 */
int UtcDaliRenderTaskSetGetSetScreenToFrameBufferFunctionWithFullScreenP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETSETSCREENTOFRAMEBUFFERFUNCTIONWITHFULLSCREEN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetGetSetScreenToFrameBufferFunctionWithDefaultScreenP
 * @since_tizen     2.4
 * @description     Checks whether SetScreenToFrameBufferFunction and GetScreenToFrameBufferFunction api for DEFAULT_SCREEN_TO_FRAMEBUFFER_FUNCTION is executed successfully or not
 */
int UtcDaliRenderTaskSetGetSetScreenToFrameBufferFunctionWithDefaultScreenP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETSETSCREENTOFRAMEBUFFERFUNCTIONWITHDEFAULTSCREEN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskSetScreenToFrameBufferFunctionN
 * @since_tizen     2.4
 * @description     Checks whether SetScreenToFrameBufferFunction api for DEFAULT_SCREEN_TO_FRAMEBUFFER_FUNCTION is executed successfully or not, with unintialized RenderTask handle
 */
int UtcDaliRenderTaskSetScreenToFrameBufferFunctionN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_SETGETSETSCREENTOFRAMEBUFFERFUNCTION_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRenderTaskGetScreenToFrameBufferFunctionN
 * @since_tizen     2.4
 * @description     Checks whether GetScreenToFrameBufferFunction api is executed successfully or not, with unintialized RenderTask handle
 */
int UtcDaliRenderTaskGetScreenToFrameBufferFunctionN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RENDER_TASK_GETSCREENTOFRAMEBUFFERFUNCTION_N);
  application.MainLoop();
  return test_return_value;
}

