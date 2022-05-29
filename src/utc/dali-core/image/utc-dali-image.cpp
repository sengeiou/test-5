#include "utc-dali-image-impl.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;
//& set: Image

/**
 * @function            utc_Dali_Image_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Image_startup(void)
{
  test_return_value=TC_PASS;
}

/**
 * @function            utc_Dali_Image_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Image_cleanup(void)
{
}


namespace
{
  enum TEST_CASES_LIST_IMAGE
  {
    IMAGE_DOWNCAST_P,
    IMAGE_DOWNCAST_N,
    IMAGE_DEFAULT_CONSTRUCTOR_P,
    IMAGE_COPY_CONSTRUCTOR_P,
    IMAGE_GET_WIDTH_P,
    IMAGE_GET_HEIGHT_P,
    IMAGE_ASSIGNMENT_OPERATOR_P
  };

  struct Image_TestApp : public ConnectionTracker
  {
    Image_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Image_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Image_TestApp::Tick );
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
        case IMAGE_DOWNCAST_P:
          ImageDownCastP();
          break;

        case IMAGE_DOWNCAST_N:
          ImageDownCastN();
          break;

        case IMAGE_DEFAULT_CONSTRUCTOR_P:
          ImageDefaultConstructorP();
          break;

        case IMAGE_COPY_CONSTRUCTOR_P:
          ImageCopyConstructorP();
          break;

        case IMAGE_GET_WIDTH_P:
          ImageGetWidthP();
          break;

        case IMAGE_GET_HEIGHT_P:
          ImageGetHeightP();
          break;

        case IMAGE_ASSIGNMENT_OPERATOR_P:
          ImageAssignmentOperatorP();
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
 * @testcase            UtcDaliImageDownCastP
 * @since_tizen         2.4
 * @description         check if DownCast api works or not.
 */
int UtcDaliImageDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliImageDownCastN
 * @since_tizen         2.4
 * @description         check if DownCast api works or not.
 */
int UtcDaliImageDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliImageConstructorP
 * @since_tizen         2.4
 * @description         check if default constructor works or not.
 */
int UtcDaliImageConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_DEFAULT_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliImageCopyConstructorP
 * @since_tizen         2.4
 * @description         check if copy constructor works or not.
 */
int UtcDaliImageCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliImageGetWidthP
 * @since_tizen         2.4
 * @description         check if GetWidth api works or not.
 */
int UtcDaliImageGetWidthP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_GET_WIDTH_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliImageGetHeightP
 * @since_tizen         2.4
 * @description         check if GetHeight api works or not.
 */
int UtcDaliImageGetHeightP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_GET_HEIGHT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliImageOperatorAssignmentP
 * @since_tizen         2.4
 * @description         checks if operator=() works or not.
 */
int UtcDaliImageOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_ASSIGNMENT_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}
