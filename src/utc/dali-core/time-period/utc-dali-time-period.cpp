#include "utc-dali-time-period-impl.h"


/**
 * @function            utc_Dali_TimePeriod_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_TimePeriod_startup(void)
{
  test_return_value=0;
  gRenderCountTimePeriod = 0;
}


/**
 * @function            utc_Dali_TimePeriod_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_TimePeriod_cleanup(void)
{

}

namespace
{
  enum TEST_CASES_LIST_TIME_PERIOD
  {
    TIME_PERIOD_WITH_DURATION_IN_SECONDS,
    TIME_PERIOD_WITH_DELAY_DURATION_SECONDS
  };

  struct TimePeriod_TestApp : public ConnectionTracker
  {
    TimePeriod_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &TimePeriod_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &TimePeriod_TestApp::Tick );
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
        case TIME_PERIOD_WITH_DURATION_IN_SECONDS:
          TimePeriodWithDurationSeconds();
          break;

        case TIME_PERIOD_WITH_DELAY_DURATION_SECONDS:
          TimePeriodWithDelayDurationSeconds();
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case TIME_PERIOD_WITH_DURATION_IN_SECONDS:
          switch(gRenderCountTimePeriod)
          {
            case 0:
              VTTimePeriodWithDurationSeconds001();
              gRenderCountTimePeriod++;
              break;

            case 1:
              VTTimePeriodWithDurationSeconds002();
              gRenderCountTimePeriod++;
              break;

            case 2:
              VTTimePeriodWithDurationSeconds003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case TIME_PERIOD_WITH_DELAY_DURATION_SECONDS:
          switch(gRenderCountTimePeriod)
          {
            case 0:
              VTTimePeriodWithDelayDurationSeconds001();
              gRenderCountTimePeriod++;
              break;

            case 1:
              VTTimePeriodWithDelayDurationSeconds002();
              gRenderCountTimePeriod++;
              break;

            case 2:
              VTTimePeriodWithDelayDurationSeconds003();
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
 * @testcase                UtcDaliTimePeriodWithDurationInSecondsP
 * @since_tizen             2.4
 * @description             Check if TimePeriod can construct required time period for animation with required delay time and time duration properly
 */

int UtcDaliTimePeriodWithDurationInSecondsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TimePeriod_TestApp testApp( application, TIME_PERIOD_WITH_DURATION_IN_SECONDS );
  application.MainLoop();
  return test_return_value;
}
/**
 * @testcase                UtcDaliTimePeriodWithDelayDurationSecondsP
 * @since_tizen             2.4
 * @description             Check if TimePeriod can construct required time period for animation with required delay time and time duration properly
 */

int UtcDaliTimePeriodWithDelayDurationSecondsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TimePeriod_TestApp testApp( application, TIME_PERIOD_WITH_DELAY_DURATION_SECONDS );
  application.MainLoop();
  return test_return_value;
}

