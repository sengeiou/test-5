#include "utc-dali-random-common.h"


extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Random

/**
 * @function      utc_Dali_Random_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_Random_startup(void)
{
  test_return_value=0;
}

/**
 * @function      utc_Dali_Random_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_Random_cleanup(void)
{

}

void RandomRangeP();
void RandomAxisP();

namespace
{
  enum TEST_CASES_LIST_RANDOM
  {
    RANDOM_RANGE_P,
    RANDOM_AXIS_P
  };

  struct Random_TestApp : public ConnectionTracker
  {
    Random_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Random_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Random_TestApp::Tick );
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
        case RANDOM_RANGE_P:
          RandomRangeP();
          break;

        case RANDOM_AXIS_P:
          RandomAxisP();
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
void RandomRangeP()
{
  float fLower = 0.0f, fUpper = 1.0f;
  float fRandomNumber = 0.0f;

  fRandomNumber = Random::Range( fLower, fUpper );
  DALI_CHECK_FAIL( fRandomNumber <  fLower || fRandomNumber > fUpper , "Random::Range() is failed" );
  fRandomNumber = 0.0f;

  DaliLog::PrintPass();
}

void RandomAxisP()
{
  Vector4 vec4Axis = Vector4::ZERO, vec4Zero = Vector4::ZERO, vec4Get;
  vec4Axis = Random::Axis();
  if( vec4Axis == vec4Zero )
  {
    vec4Axis = Vector4::ZERO;
    LOG_E("Random::Axis is failed is return vector with direction" );
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}
/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase      UtcDaliRandomRangeP
 * @since_tizen   2.4
 * @description   check if Range api works or not.
 */
int UtcDaliRandomRangeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Random_TestApp testApp( application, RANDOM_RANGE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliRandomAxisP
 * @since_tizen   2.4
 * @description   check if Axis api works or not.
 */
int UtcDaliRandomAxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Random_TestApp testApp( application, RANDOM_AXIS_P);
  application.MainLoop();
  return test_return_value;
}
