#include "utc-dali-sampling-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Sampling_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Sampling_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_Sampling_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Sampling_cleanup(void)
{

}

void SamplingSetFilterMode();
void SamplingSetWrapMode();

namespace
{
  enum TEST_CASES_LIST_PROPERTY_ARRAY
  {
    SAMPLING_FILTER_MODE,
    SAMPLING_WRAP_MODE
  };

  struct Sampling_TestApp : public ConnectionTracker
  {
    Sampling_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Sampling_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Sampling_TestApp::Tick );
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
        case SAMPLING_FILTER_MODE:
          SamplingSetFilterMode();
          break;

        case SAMPLING_WRAP_MODE:
          SamplingSetWrapMode();
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
void SamplingSetFilterMode()
{
  DALI_CHECK_FAIL(FilterMode::NONE    != 0, "FilterMode value check failed which is not expected ")
  DALI_CHECK_FAIL(FilterMode::DEFAULT != 1, "FilterMode value check failed which is not expected ")
  DALI_CHECK_FAIL(FilterMode::NEAREST != 2, "FilterMode value check failed which is not expected ")
  DALI_CHECK_FAIL(FilterMode::LINEAR  != 3, "FilterMode value check failed which is not expected ")
  DaliLog::PrintPass();
}
void SamplingSetWrapMode(void)
{
  DALI_CHECK_FAIL(WrapMode::DEFAULT != 0, "WrapMode value check failed which is not expected ")
  DALI_CHECK_FAIL(WrapMode::CLAMP_TO_EDGE != 1, "WrapMode value check failed which is not expected ")
  DALI_CHECK_FAIL(WrapMode::REPEAT != 2, "WrapMode value check failed which is not expected ")
  DALI_CHECK_FAIL(WrapMode::MIRRORED_REPEAT != 3, "WrapMode value check failed which is not expected ")
  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase             UtcDaliSamplingFilterModeP
 * @since_tizen          2.4
 * @description          To Check Sampling SetFilterMode is working properly or not
 */
int UtcDaliSamplingFilterModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Sampling_TestApp testApp( application, SAMPLING_FILTER_MODE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliSamplingWrapModeP
 * @since_tizen          2.4
 * @description          To Check Sampling SetWrapMode is working properly or not
 */
int UtcDaliSamplingWrapModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Sampling_TestApp testApp( application, SAMPLING_WRAP_MODE);
  application.MainLoop();
  return test_return_value;
}
