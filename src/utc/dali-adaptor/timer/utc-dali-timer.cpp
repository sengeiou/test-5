#include "utc-dali-timer-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function        utc_Dali_Timer_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */

void utc_Dali_Timer_startup(void)
{
  test_return_value=0;
}

/**
 * @function        utc_Dali_Timer_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */

void utc_Dali_Timer_cleanup(void)
{
}

unsigned int gTimerSetTimeInMilliSec = DEFAULT_TIME_INTERVAL_IN_MILLISEC;
unsigned int gTimerGetTimeInMilliSec = DEFAULT_TIME_INTERVAL_IN_MILLISEC;

void TimerSetGetIntervalP();
void TimerSetGetIntervalP2();
void TimerSetGetIntervalP3();
void TimerStartStopP();
void TimerAssignmentOperatorP();
void TimerTickSignalP();
void TimerCopyConstructorP();
void TimerDowncastP();
void TimerDowncastN();
void TimerNewP();
void TimerConstructorP();
void TimerIsRunningP();


namespace
{
  enum TEST_CASES_LIST_TIMER
  {
    TIMER_CONSTRUCTOR_P,
    TIMER_SET_GET_INTERVAL_P,
    TIMER_SET_GET_INTERVAL_P2,
    TIMER_SET_GET_INTERVAL_P3,
    TIMER_START_STOP_P,
    TIMER_ASSIGNMENT_OPERATOR_P,
    TIMER_TICK_SIGNAL_P,
    TIMER_COPY_CONSTRUCTOR_P,
    TIMER_DOWNCAST_P,
    TIMER_DOWNCAST_N,
    TIMER_NEW_P,
    TIMER_IS_RUNNING_P
  };

  struct Timer_TestApp : public ConnectionTracker
  {
    Timer_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Timer_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Timer_TestApp::Tick );
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
        case TIMER_CONSTRUCTOR_P:
          TimerConstructorP();
          break;

        case TIMER_SET_GET_INTERVAL_P:
          TimerSetGetIntervalP();
          break;

        case TIMER_SET_GET_INTERVAL_P2:
          TimerSetGetIntervalP2();
          break;

        case TIMER_SET_GET_INTERVAL_P3:
          TimerSetGetIntervalP3();
          break;

        case TIMER_START_STOP_P:
          TimerStartStopP();
          break;

        case TIMER_ASSIGNMENT_OPERATOR_P:
          TimerAssignmentOperatorP();
          break;

        case TIMER_TICK_SIGNAL_P:
          TimerTickSignalP();
          break;

        case TIMER_COPY_CONSTRUCTOR_P:
          TimerCopyConstructorP();
          break;

        case TIMER_DOWNCAST_P:
          TimerDowncastP();
          break;

        case TIMER_DOWNCAST_N:
          TimerDowncastN();
          break;

        case TIMER_NEW_P:
          TimerNewP();
          break;

        case TIMER_IS_RUNNING_P:
          TimerIsRunningP();
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
 * small class to test timer signal
 */

namespace
{
  class TimerTestClass : public ConnectionTracker
  {
    public:

      TimerTestClass(bool repeat):mbTimerCalled(false),mbReturnContiune(repeat),mnTickCount(0) {}

      bool Tick()
      {
        LOG_I("Tick is called .");
        mbTimerCalled = true;
        mnTickCount+= 1 ;
        if(mnTickCount > 10 )
          ecore_main_loop_quit();
        return mbReturnContiune;
      }
      bool mbTimerCalled;    // whether tick has been called or not
      bool mbReturnContiune; // whether to return true / false to continue
      int mnTickCount ;      // count the number of tick
  };
}


void TimerConstructorP()
{
  Timer timer;
  DALI_CHECK_FAIL(timer, "Timer default constructor is failed.");

  DaliLog::PrintPass();
}

void TimerSetGetIntervalP()
{
  gTimerSetTimeInMilliSec = 5000u;
  unsigned int gTimerGetTimeInMilliSec = DEFAULT_TIME_INTERVAL_IN_MILLISEC;

  Timer timer = TimerInit();
  DALI_CHECK_FAIL(!timer,"Timer object is not created");

  gTimerGetTimeInMilliSec= timer.GetInterval();
  DALI_CHECK_FAIL(gTimerGetTimeInMilliSec != PERIODIC_TICK_INTERVAL, "Failed to Get the default GetInterval.");

  timer.SetInterval(gTimerSetTimeInMilliSec);

  gTimerGetTimeInMilliSec= timer.GetInterval();
  DALI_CHECK_FAIL(gTimerGetTimeInMilliSec != gTimerSetTimeInMilliSec, "GetIntervaland SetInterval value mismatched.");

  timer.Reset();

  DaliLog::PrintPass();
}

void TimerSetGetIntervalP2()
{
  bool bIsRunning = false;
  gTimerSetTimeInMilliSec = 5000u;
  unsigned int gTimerGetTimeInMilliSec = DEFAULT_TIME_INTERVAL_IN_MILLISEC;

  Timer timer = TimerInit();
  DALI_CHECK_FAIL(!timer,"Timer object is not created");

  timer.SetInterval(PERIODIC_TICK_INTERVAL);

  gTimerGetTimeInMilliSec = timer.GetInterval();
  DALI_CHECK_FAIL(gTimerGetTimeInMilliSec != PERIODIC_TICK_INTERVAL, "Failed to Get the default GetInterval.");
  bIsRunning = timer.IsRunning();
  DALI_CHECK_FAIL(!bIsRunning, "Timer should be running after SetInterval.");

  timer.SetInterval(gTimerSetTimeInMilliSec, false);

  gTimerGetTimeInMilliSec = timer.GetInterval();
  DALI_CHECK_FAIL(gTimerGetTimeInMilliSec != gTimerSetTimeInMilliSec, "GetIntervaland SetInterval value mismatched.");
  bIsRunning = timer.IsRunning();
  DALI_CHECK_FAIL(bIsRunning, "Timer should be stopped after SetInterval(interval, false).");

  timer.Reset();

  DaliLog::PrintPass();
}

void TimerSetGetIntervalP3()
{
  bool bIsRunning = false;
  gTimerSetTimeInMilliSec = 5000u;
  unsigned int gTimerGetTimeInMilliSec = DEFAULT_TIME_INTERVAL_IN_MILLISEC;

  Timer timer = TimerInit();
  DALI_CHECK_FAIL(!timer,"Timer object is not created");

  timer.SetInterval(PERIODIC_TICK_INTERVAL);

  gTimerGetTimeInMilliSec = timer.GetInterval();
  DALI_CHECK_FAIL(gTimerGetTimeInMilliSec != PERIODIC_TICK_INTERVAL, "Failed to Get the default GetInterval.");
  bIsRunning = timer.IsRunning();
  DALI_CHECK_FAIL(!bIsRunning, "Timer should be running after SetInterval.");

  timer.SetInterval(gTimerSetTimeInMilliSec, true);

  gTimerGetTimeInMilliSec = timer.GetInterval();
  DALI_CHECK_FAIL(gTimerGetTimeInMilliSec != gTimerSetTimeInMilliSec, "GetIntervaland SetInterval value mismatched.");
  bIsRunning = timer.IsRunning();
  DALI_CHECK_FAIL(!bIsRunning, "Timer should be still running after SetInterval(interval, true).");

  timer.Reset();

  DaliLog::PrintPass();
}

void TimerStartStopP()
{
  bool bIsRunning = false;
  Timer timer = TimerInit();

  timer.Start();

  bIsRunning = timer.IsRunning();
  DALI_CHECK_FAIL(!bIsRunning, "IsRunning returning false after Start timer.");

  timer.Stop();

  bIsRunning = timer.IsRunning();
  DALI_CHECK_FAIL(bIsRunning, "IsRunning returning true after stop timer.");

  timer.Reset();

  DaliLog::PrintPass();
}

void TimerAssignmentOperatorP()
{
  Timer timer = Timer::New(10);
  DALI_CHECK_FAIL( !timer, "Timer::New failed." );
  DALI_CHECK_FAIL(timer.GetInterval() != 10, "Timer::GetInterval() has failed.");

  Timer anotherTimer = Timer::New(40);
  DALI_CHECK_FAIL( !anotherTimer, "Timer::New failed." );
  DALI_CHECK_FAIL(anotherTimer.GetInterval() != 40, "Timer::GetInterval() has failed.");


  DALI_CHECK_FAIL(timer == anotherTimer, "Timer::operator==() has failed.");

  timer = anotherTimer;

  DALI_CHECK_FAIL(timer != anotherTimer, "Timer::operator=() has failed.");

  DALI_CHECK_FAIL(timer.GetInterval() != 40, "Timer::GetInterval() has failed after assignment.");

  DaliLog::PrintPass();
}

void TimerTickSignalP()
{
  ecore_init();

  unsigned int gTimerGetTimeInMilliSec = DEFAULT_TIME_INTERVAL_IN_MILLISEC;

  Timer timer = TimerInit();
  DALI_CHECK_FAIL(!timer,"timer object is not created");

  gTimerGetTimeInMilliSec = timer.GetInterval();
  DALI_CHECK_FAIL(PERIODIC_TICK_INTERVAL != gTimerGetTimeInMilliSec,"Set and Get Interval missmatched. Set time:.");

  TimerTestClass bTestClass(true);

  timer.TickSignal().Connect(&bTestClass, &TimerTestClass::Tick);

  timer.Start();
  ecore_main_loop_begin();

  DALI_CHECK_FAIL(!bTestClass.mbTimerCalled,"Tick signal is failed to emmit signal.");

  DALI_CHECK_FAIL(!timer.IsRunning(),"Timer is not Running..");

  timer.Stop();
  DALI_CHECK_FAIL(timer.IsRunning(),"Timer is still Running after stop.");

  ecore_shutdown();
  gTimerGetTimeInMilliSec = DEFAULT_TIME_INTERVAL_IN_MILLISEC;

  DaliLog::PrintPass();
}

void TimerCopyConstructorP()
{
  Timer timer = Timer::New(10);
  DALI_CHECK_FAIL(!timer,"timer object is not created");

  Timer anotherTimer( timer );
  DALI_CHECK_FAIL(!anotherTimer,"timer object is not created");

  DALI_CHECK_FAIL( anotherTimer.GetInterval() != 10, "Timer::Timer(const Timer&) is failed.");

  DaliLog::PrintPass();
}

void TimerNewP()
{
  Timer timer = Timer::New(10);
  DALI_CHECK_FAIL(!timer,"Timer::New(int) is failed." );

  DaliLog::PrintPass();
}

void TimerDowncastP()
{
  Timer timer = Timer::New(100);
  DALI_CHECK_FAIL(!timer,"timer object is not created");

  Timer cast = Timer::DownCast( timer );
  DALI_CHECK_FAIL( !cast, "Timer::DownCast is Falied" );

  DaliLog::PrintPass();
}

void TimerDowncastN(void)
{
  Timer timer;

  Timer cast = Timer::DownCast( timer );
  DALI_CHECK_FAIL( cast, "Timer::DownCast is Falied" );

  DaliLog::PrintPass();
}

void TimerIsRunningP()
{
  Timer timer = Timer::New(100);
  timer.Start();
  DALI_CHECK_FAIL(!(timer.IsRunning()), "Timer::IsRunning() is failed." );
  timer.Stop();

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliTimerNewP
 * @since_tizen     2.4
 * @description     checks for Timer::NewP() functionality
 */

int UtcDaliTimerNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Timer_TestApp testApp( application, TIMER_NEW_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTimerSetGetIntervalP
 * @since_tizen     2.4
 * @description     checks for Timer::SetGetIntervalP() functionality
 */

int UtcDaliTimerSetGetIntervalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Timer_TestApp testApp( application, TIMER_SET_GET_INTERVAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTimerStartStopP
 * @since_tizen     2.4
 * @description     checks for Timer::StartStopP() functionality
 */

int UtcDaliTimerStartStopP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Timer_TestApp testApp( application, TIMER_START_STOP_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTimerAssignmentOperatorP
 * @since_tizen     2.4
 * @description     checks for Timer::AssignmentOperatorP() functionality
 */

int UtcDaliTimerAssignmentOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Timer_TestApp testApp( application, TIMER_ASSIGNMENT_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTimerTickSignalP
 * @since_tizen     2.4
 * @description     checks for Timer::TickSignalP() functionality
 */

int UtcDaliTimerTickSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Timer_TestApp testApp( application, TIMER_TICK_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTimerCopyConstructorP
 * @since_tizen     2.4
 * @description     checks for Timer::CopyConstructorP() functionality
 */

int UtcDaliTimerCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Timer_TestApp testApp( application, TIMER_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTimerConstructorP
 * @since_tizen     2.4
 * @description     checks for Timer::ConstructorP() functionality
 */

int UtcDaliTimerConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Timer_TestApp testApp( application, TIMER_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTimerDowncastP
 * @since_tizen     2.4
 * @description     checks for Timer::DowncastP() functionality
 */

int UtcDaliTimerDowncastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Timer_TestApp testApp( application, TIMER_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTimerDowncastN
 * @since_tizen     2.4
 * @description     checks for Timer::DowncastN() functionality
 */

int UtcDaliTimerDowncastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Timer_TestApp testApp( application, TIMER_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTimerIsRunningP
 * @since_tizen     2.4
 * @description     checks for Timer::IsRunningP() functionality
 */

int UtcDaliTimerIsRunningP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Timer_TestApp testApp( application, TIMER_IS_RUNNING_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTimerSetGetIntervalP2
 * @since_tizen     5.0
 * @description     checks for Timer::SetGetIntervalP2() functionality
 */

int UtcDaliTimerSetGetIntervalP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Timer_TestApp testApp( application, TIMER_SET_GET_INTERVAL_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTimerSetGetIntervalP3
 * @since_tizen     5.0
 * @description     checks for Timer::SetGetIntervalP3() functionality
 */

int UtcDaliTimerSetGetIntervalP3(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Timer_TestApp testApp( application, TIMER_SET_GET_INTERVAL_P3);
  application.MainLoop();
  return test_return_value;
}
