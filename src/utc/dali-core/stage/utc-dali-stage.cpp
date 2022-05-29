#include "utc-dali-stage-impl.h"

/**
 * @function            utc_Dali_Stage_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Stage_startup(void)
{
  test_return_value = TC_PASS;
  gRenderCountStage=0;
}

/**
 * @function            utc_Dali_Stage_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Stage_cleanup(void)
{
}


namespace
{
  enum TEST_CASES_LIST
  {

    STAGE_CONSTRUCTOR,
    STAGE_GETCURRENT,
    STAGE_GETCURRENTN,
    STAGE_ISINSTALLED,
    STAGE_ISINSTALLEDN,
    STAGE_COPYCONSTRUCTOR,
    STAGE_ASSIGNMENTOPERATOR,
    STAGE_ADD,
    STAGE_ADDN,
    STAGE_REMOVE,
    STAGE_REMOVE_N1,
    STAGE_REMOVE_N2,
    STAGE_REMOVE_N3,
    STAGE_GET_SIZE,
    STAGE_GET_SIZEN,
    STAGE_GET_RENDER_TASKLIST,
    STAGE_GET_RENDER_TASKLISTN,
    STAGE_GETLAYERCOUNT,
    STAGE_GETLAYERCOUNTN,
    STAGE_GETLAYER,
    STAGE_GETLAYERN,
    STAGE_GETROOTLAYER,
    STAGE_GETROOTLAYERN,
    STAGE_SETBACKGROUNDCOLOR,
    STAGE_GETBACKGROUNDCOLOR,
    STAGE_GETDPI,
    STAGE_GETDPIN,
    STAGE_GETOBJECTREGISTRY,
    STAGE_GETOBJECTREGISTRYN,
    STAGE_KEEP_RENDERING,
    STAGE_KEEP_RENDERINGN,
    STAGE_KEYEVENT_SIGNAL,
    STAGE_KEYEVENT_SIGNALN,
    STAGE_EVENT_PROCESSINGFINISHED_SIGNAL,
    STAGE_EVENT_PROCESSINGFINISHED_SIGNALN,
    STAGE_TOUCHED_SIGNAL,
    STAGE_TOUCHED_SIGNALN,
    STAGE_CONTEXTLOST_SIGNAL,
    STAGE_CONTEXTLOST_SIGNALN,
    STAGE_CONTEXTREGAINED_SIGNAL,
    STAGE_CONTEXTREGAINED_SIGNALN,
    STAGE_SCENECREATED_SIGNAL,
    STAGE_SCENECREATED_SIGNALN

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
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &TestApp::Tick );
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

        case STAGE_CONSTRUCTOR:
          StageConstructor();
          break;

        case STAGE_GETCURRENT:
          StageGetCurrentP();
          break;

        case STAGE_GETCURRENTN:
          StageGetCurrentN();
          break;

        case STAGE_ISINSTALLED:
          StageIsInstalled();
          break;

        case STAGE_ISINSTALLEDN:
          StageIsInstalledN();
          break;

        case STAGE_COPYCONSTRUCTOR:
          StageCopyConstructor();
          break;

        case STAGE_ASSIGNMENTOPERATOR:
          StageOperatorAssignment();
          break;

        case STAGE_ADD:
          StageAdd();
          break;

        case STAGE_ADDN:
          StageAddN();
          break;

        case STAGE_REMOVE:
          StageRemove();
          break;

        case STAGE_REMOVE_N1:
          StageRemoveN1();
          break;

        case STAGE_REMOVE_N2:
          StageRemoveN2();
          break;

        case STAGE_REMOVE_N3:
          StageRemoveN3();
          break;
        case STAGE_GET_SIZE:
          StageGetSize();
          break;

        case STAGE_GET_SIZEN:
          StageGetSizeN();
          break;

        case STAGE_GET_RENDER_TASKLIST:
          StageGetRenderTaskList();
          break;

        case STAGE_GET_RENDER_TASKLISTN:
          StageGetRenderTaskListN();
          break;

        case STAGE_GETLAYERCOUNT:
          StageGetLayerCount();
          break;

        case STAGE_GETLAYERCOUNTN:
          StageGetLayerCountN();
          break;

        case STAGE_GETLAYER:
          StageGetLayer();
          break;

        case STAGE_GETLAYERN:
          StageGetLayerN();
          break;

        case STAGE_GETROOTLAYER:
          StageGetRootLayer();
          break;

        case STAGE_GETROOTLAYERN:
          StageGetRootLayerN();
          break;

        case STAGE_SETBACKGROUNDCOLOR:
          StageSetBackgroundColor();
          break;

        case STAGE_GETBACKGROUNDCOLOR:
          StageGetBackgroundColor();
          break;

        case STAGE_GETDPI:
          StageGetDpi();
          break;

        case STAGE_GETDPIN:
          StageGetDpiN();
          break;

        case STAGE_GETOBJECTREGISTRY:
          StageGetObjectRegistry();
          break;

        case STAGE_GETOBJECTREGISTRYN:
          StageGetObjectRegistryN();
          break;

        case STAGE_KEEP_RENDERING:
          StageKeepRendering();
          break;

        case STAGE_KEEP_RENDERINGN:
          StageKeepRenderingN();
          break;

        case STAGE_KEYEVENT_SIGNAL:
          StageKeyEventSignal();
          break;

        case STAGE_KEYEVENT_SIGNALN:
          StageKeyEventSignalN();
          break;

        case STAGE_EVENT_PROCESSINGFINISHED_SIGNAL:
          StageEventProcessingFinishedSignal();
          break;

        case STAGE_EVENT_PROCESSINGFINISHED_SIGNALN:
          StageEventProcessingFinishedSignalN();
          break;

        case STAGE_TOUCHED_SIGNAL:
          StageTouchedSignal();
          break;

        case STAGE_TOUCHED_SIGNALN:
          StageTouchedSignalN();
          break;

        case STAGE_CONTEXTLOST_SIGNAL:
          StageContextLostSignal();
          break;

        case STAGE_CONTEXTLOST_SIGNALN:
          StageContextLostSignalN();
          break;

        case STAGE_CONTEXTREGAINED_SIGNAL:
          StageContextRegainedSignal();
          break;

        case STAGE_CONTEXTREGAINED_SIGNALN:
          StageContextRegainedSignalN();
          break;

        case STAGE_SCENECREATED_SIGNAL:
          StageSceneCreatedSignal();
          break;

        case STAGE_SCENECREATED_SIGNALN:
          StageSceneCreatedSignalN();
          break;


      }
    }

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace


/**
 * @testcase             UtcDaliStageConstructorP
 * @since_tizen          2.4
 * @description          Checks whether constructor works or not.
 */
int UtcDaliStageConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetCurrentP
 * @since_tizen          2.4
 * @description          Checks GetCurrent works or not.
 */
int UtcDaliStageGetCurrentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETCURRENT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetCurrentN
 * @since_tizen          2.4
 * @description          Checks GetCurrent works or not.
 */
int UtcDaliStageGetCurrentN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETCURRENTN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageIsInstalledP
 * @since_tizen          2.4
 * @description          Query whether the Stage exists.
 */
int UtcDaliStageIsInstalledP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_ISINSTALLED);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageIsInstalledN
 * @since_tizen          2.4
 * @description          Query whether the Stage exists.
 */
int UtcDaliStageIsInstalledN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_ISINSTALLEDN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageCopyConstructorP
 * @since_tizen          2.4
 * @description          Checks whether copy constructor works or not.
 */
int UtcDaliStageCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_COPYCONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageOperatorAssignmentP
 * @since_tizen          2.4
 * @description          Assignment operator is Checked.
 */
int UtcDaliStageOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_ASSIGNMENTOPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageAddP
 * @since-tizen            2.4
 * @description          Adds an actor on stage.
 */
int UtcDaliStageAddP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_ADD);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageAddN
 * @since-tizen            2.4
 * @description          Adds an actor on stage.
 */
int UtcDaliStageAddN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_ADDN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageRemoveP
 * @since-tizen            2.4
 * @description          Removes an actor on stage.
 */
int UtcDaliStageRemoveP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_REMOVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageRemoveN1
 * @since-tizen            2.4
 * @description          Removes an actor on stage.
 */
int UtcDaliStageRemoveN1(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_REMOVE_N1);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageRemoveN2
 * @since-tizen            2.4
 * @description          Removes an actor on stage.
 */
int UtcDaliStageRemoveN2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_REMOVE_N2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageRemoveN3
 * @since-tizen            2.4
 * @description          Removes an actor on stage.
 */
int UtcDaliStageRemoveN3(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_REMOVE_N3);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetSizeP
 * @since-tizen            2.4
 * @description          Gets size of an actor on stage.
 */
int UtcDaliStageGetSizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GET_SIZE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetSizeN
 * @since-tizen            2.4
 * @description          Gets size of an actor on stage.
 */
int UtcDaliStageGetSizeN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GET_SIZEN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetRenderTaskListP
 * @since-tizen            2.4
 * @description          Gets RenderTaskList an actor on stage.
 */
int UtcDaliStageGetRenderTaskListP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GET_RENDER_TASKLIST);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetRenderTaskListN
 * @since-tizen            2.4
 * @description          Gets RenderTaskList an actor on stage.
 */
int UtcDaliStageGetRenderTaskListN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GET_RENDER_TASKLISTN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetLayerCountP
 * @since-tizen            2.4
 * @description          Gets LayerCount of an actor on stage.
 */
int UtcDaliStageGetLayerCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETLAYERCOUNT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetLayerCountN
 * @since-tizen            2.4
 * @description          Gets LayerCount of an actor on stage.
 */
int UtcDaliStageGetLayerCountN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETLAYERCOUNTN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetLayerP
 * @since-tizen            2.4
 * @description          Gets the layer of an actor on stage.
 */
int UtcDaliStageGetLayerP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETLAYER);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetLayerN
 * @since-tizen            2.4
 * @description          Gets the layer of an actor on stage.
 */
int UtcDaliStageGetLayerN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETLAYERN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetRootLayerP
 * @since-tizen            2.4
 * @description          Gets RootLayer of an actor on stage.
 */
int UtcDaliStageGetRootLayerP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETROOTLAYER);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetRootLayerN
 * @since-tizen            2.4
 * @description          Gets RootLayer of an actor on stage.
 */
int UtcDaliStageGetRootLayerN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETROOTLAYERN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageSetBackgroundColorP
 * @since_tizen            2.4
 * @description          Sets the background color of a stage.
 */
int UtcDaliStageSetBackgroundColorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_SETBACKGROUNDCOLOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetBackgroundColorP
 * @since_tizen            2.4
 * @description          Gets the background color of a stage.
 */
int UtcDaliStageGetBackgroundColorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETBACKGROUNDCOLOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetDpiP
 * @since_tizen            2.4
 * @description          Gets the Dpi of a stage.
 */
int UtcDaliStageGetDpiP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETDPI);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetDpiN
 * @since_tizen            2.4
 * @description          Gets the Dpi of a stage.
 */
int UtcDaliStageGetDpiN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETDPIN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetObjectRegistryP
 * @since_tizen          2.4
 * @description          Checks whether the GetObjectRegistry api is working properly or not.
 */
int UtcDaliStageGetObjectRegistryP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETOBJECTREGISTRY);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageGetObjectRegistryN
 * @since_tizen          2.4
 * @description          Checks whether the GetObjectRegistry api is working properly or not.
 */
int UtcDaliStageGetObjectRegistryN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_GETOBJECTREGISTRYN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageKeepRenderingP
 * @since_tizen          2.4
 * @description          Checks whether the KeepRendering api is working properly or not.
 */
int UtcDaliStageKeepRenderingP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_KEEP_RENDERING);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageKeepRenderingN
 * @since_tizen          2.4
 * @description          Checks whether the KeepRendering api is working properly or not.
 */
int UtcDaliStageKeepRenderingN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_KEEP_RENDERINGN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageKeepEventSignalP
 * @since_tizen          2.4
 * @description          Checks whether the KeepEventSignal api is working properly or not.
 */
int UtcDaliStageKeepEventSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_KEYEVENT_SIGNAL);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageKeepEventSignalN
 * @since_tizen          2.4
 * @description          Checks whether the KeepEventSignal api is working properly or not.
 */
int UtcDaliStageKeepEventSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_KEYEVENT_SIGNALN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageEventProcessingFinishedSignalP
 * @since_tizen          2.4
 * @description          Checks whether the EventProcessingFinishedSignal api is working properly or not.
 */
int UtcDaliStageEventProcessingFinishedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_EVENT_PROCESSINGFINISHED_SIGNAL);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageEventProcessingFinishedSignalN
 * @since_tizen          2.4
 * @description          Checks whether the EventProcessingFinishedSignal api is working properly or not.
 */
int UtcDaliStageEventProcessingFinishedSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_EVENT_PROCESSINGFINISHED_SIGNALN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageTouchedSignalP
 * @since_tizen          2.4
 * @description          Checks whether the StageTouchedSignalP api is working properly or not.
 */
int UtcDaliStageTouchedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_TOUCHED_SIGNAL);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageTouchedSignalN
 * @since_tizen          2.4
 * @description          Checks whether the StageTouchedSignalP api is working properly or not.
 */
int UtcDaliStageTouchedSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_TOUCHED_SIGNALN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageContextLostSignalP
 * @since_tizen          2.4
 * @description          Checks whether the ContextLostSignal api is working properly or not.
 */
int UtcDaliStageContextLostSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_CONTEXTLOST_SIGNAL);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageContextLostSignalN
 * @since_tizen          2.4
 * @description          Checks whether the ContextLostSignal api is working properly or not.
 */
int UtcDaliStageContextLostSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_CONTEXTLOST_SIGNALN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageContextRegainedSignalP
 * @since_tizen          2.4
 * @description          Checks whether the ContextRegainedSignal api is working properly or not.
 */
int UtcDaliStageContextRegainedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_CONTEXTREGAINED_SIGNAL);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageContextRegainedSignalN
 * @since_tizen          2.4
 * @description          Checks whether the ContextRegainedSignal api is working properly or not.
 */
int UtcDaliStageContextRegainedSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_CONTEXTREGAINED_SIGNALN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageSceneCreatedSignalP
 * @since_tizen          2.4
 * @description          Checks whether the SceneCreatedSignal api is working properly or not.
 */
int UtcDaliStageSceneCreatedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_SCENECREATED_SIGNAL);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliStageSceneCreatedSignalN
 * @since_tizen          2.4
 * @description          Checks whether the SceneCreatedSignal api is working properly or not.
 */
int UtcDaliStageSceneCreatedSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, STAGE_SCENECREATED_SIGNALN);
  application.MainLoop();
  return test_return_value;
}
