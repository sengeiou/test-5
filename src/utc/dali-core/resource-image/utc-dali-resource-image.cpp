#include "utc-dali-resource-image-impl.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;


//& set: ResourceImage

/**
 * @function            utc_Dali_ResourceImage_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_ResourceImage_startup(void)
{
  test_return_value = 0;
  gRenderCountResourceImage=0;
  gSignalLoadFlag = 0;
  gSignalInvalidLoadFlag = 0;
}

/**
 * @function            utc_Dali_ResourceImage_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_ResourceImage_cleanup(void)
{
}

namespace
{
  enum TEST_CASES_LIST
  {
    RESOURCE_IMAGE_GET_IMAGE_SIZE_P,
    RESOURCE_IMAGE_RELOAD_P,
    RESOURCE_IMAGE_DOWNCAST_P,
    RESOURCE_IMAGE_DOWNCAST_N,
    RESOURCE_IMAGE_GET_URL_P,
    RESOURCE_IMAGE_COPY_CONSTRUCTOR_P,
    RESOURCE_IMAGE_OPERATOR_ASSIGNMENT_P,
    RESOURCE_IMAGE_NEW_P,
    RESOURCE_IMAGE_NEW_P2,
    RESOURCE_IMAGE_GET_LOADING_STATE_P,
    RESOURCE_IMAGE_LOADING_FINISHED_SIGNAL_P
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
        case RESOURCE_IMAGE_GET_IMAGE_SIZE_P:
          ResourceImageGetImageSizeP();
          break;

        case RESOURCE_IMAGE_RELOAD_P:
          ResourceImageReloadP();
          break;

        case RESOURCE_IMAGE_DOWNCAST_P:
          ResourceImageDownCastP();
          break;

        case RESOURCE_IMAGE_DOWNCAST_N:
          ResourceImageDownCastN();
          break;

        case RESOURCE_IMAGE_GET_URL_P:
          ResourceImageGetUrlP();
          break;

        case RESOURCE_IMAGE_COPY_CONSTRUCTOR_P:
          ResourceImageCopyConstructorP();
          break;

        case RESOURCE_IMAGE_OPERATOR_ASSIGNMENT_P:
          ResourceImageOperatorAssignmentP();
          break;

        case RESOURCE_IMAGE_NEW_P:
          ResourceImageNewP();
          break;

        case RESOURCE_IMAGE_NEW_P2:
          ResourceImageNewWithDimensionP();
          break;

        case RESOURCE_IMAGE_GET_LOADING_STATE_P:
          ResourceImageGetLoadingStateP();
          break;

        case RESOURCE_IMAGE_LOADING_FINISHED_SIGNAL_P:
          ResourceImageLoadingFinishedSignalP();
          break;


      }
    }
    void VerdictTest()
    {
      switch (mTestCase)
      {
        case RESOURCE_IMAGE_RELOAD_P:
          switch (gRenderCountResourceImage)
          {
            case 0:
              VTResourceImageReload001();
              gRenderCountResourceImage++;
              break;

            case 1:
              VTResourceImageReload002();
              gRenderCountResourceImage++;
              break;

            case 2:
              VTResourceImageReload003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case RESOURCE_IMAGE_LOADING_FINISHED_SIGNAL_P:
          VTResourceImageLoadingFinishedSignal001();
          mTimer.Stop();
          mApplication.Quit();
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
 * @testcase            UtcDaliResourceImageGetImageSizeP
 * @since_tizen         2.4
 * @description         check if GetImageSize api works or not.
 */
int UtcDaliResourceImageGetImageSizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RESOURCE_IMAGE_GET_IMAGE_SIZE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliResourceImageReloadP
 * @since_tizen         2.4
 * @description         check if Reload api works or not.
 */
int UtcDaliResourceImageReloadP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RESOURCE_IMAGE_RELOAD_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliResourceImageDowncastP
 * @since_tizen         2.4
 * @description         check if DownCast api works or not.
 */
int UtcDaliResourceImageDowncastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RESOURCE_IMAGE_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliResourceImageDowncastN
 * @since_tizen         2.4
 * @description         check if DownCast api works or not.
 */
int UtcDaliResourceImageDowncastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RESOURCE_IMAGE_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}



/**
 * @testcase            UtcDaliResourceImageGetUrlP
 * @since_tizen         2.4
 * @description         check if GetUrl api works or not.
 */
int UtcDaliResourceImageGetUrlP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RESOURCE_IMAGE_GET_URL_P);
  application.MainLoop();
  return test_return_value;
}



/**
 * @testcase            UtcDaliResourceImageCopyConstructorP
 * @since_tizen         2.4
 * @description         check if copy constructor works or not.
 */
int UtcDaliResourceImageCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RESOURCE_IMAGE_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliResourceImageOperatorAssignmentP
 * @since_tizen         2.4
 * @description         check if operator=() works or not.
 */
int UtcDaliResourceImageOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RESOURCE_IMAGE_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliResourceImageNewP
 * @since_tizen         2.4
 * @description         check if New api works or not.
 */
int UtcDaliResourceImageNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RESOURCE_IMAGE_NEW_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliResourceImageNewP2
 * @since_tizen         2.4
 * @description         check if New api works or not.
 */
int UtcDaliResourceImageNewP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RESOURCE_IMAGE_NEW_P2);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliResourceImageGetLoadingStateP
 * @since_tizen         2.4
 * @description         check if GetLoadingState api works or not.
 */
int UtcDaliResourceImageGetLoadingStateP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RESOURCE_IMAGE_GET_LOADING_STATE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliResourceImageLoadingFinishedSignalP
 * @since_tizen         2.4
 * @description         check if LoadingFinishedSingal api works or not.
 */
int UtcDaliResourceImageLoadingFinishedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, RESOURCE_IMAGE_LOADING_FINISHED_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}
