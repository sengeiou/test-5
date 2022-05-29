#include "utc-dali-application-common.h"
#include "public-api/dali-wearable.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function        utc_dali_watchapplication_startup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_dali_watchapplication_startup(void)
{
  test_return_value=0;
}

/**
 * @function        utc_dali_watchapplication_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_dali_watchapplication_cleanup(void)
{
}

void WatchApplicationNew01(WatchApplication& application);
void WatchApplicationNew02(WatchApplication& application);
void WatchApplicationNew03(WatchApplication& application);
void WatchApplicationCopyAndAssignment(WatchApplication& application);
void WatchApplicationTimeTickSignalP(WatchApplication& application);
void WatchApplicationTimeTickSignalN(void);
void WatchApplicationAmbientTickSignalP(WatchApplication& application);
void WatchApplicationAmbientTickSignalN(void);
void WatchApplicationAmbientChangedSignalP(WatchApplication& application);
void WatchApplicationAmbientChangedSignalN(void);


namespace
{
  enum TEST_CASES_LIST_WATCH
  {
    WATCH_NEW_2,
    WATCH_NEW_3,
    WATCH_COPY_AND_ASSIGNMENT,
    WATCH_TIMETICK_SIGNAL_P,
    WATCH_TIMETICK_SIGNAL_N,
    WATCH_AMBIENT_TIMETICK_SIGNAL_P,
    WATCH_AMBIENT_TIMETICK_SIGNAL_N,
    WATCH_AMBIENT_CHANGED_SIGNAL_P,
    WATCH_AMBIENT_CHANGED_SIGNAL_N
  };

  class Watch_TestApp : public ConnectionTracker
  {
  public:
    Watch_TestApp( WatchApplication& app, int test_case = WATCH_NEW_2 )
    : initCalled( false ),
      mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Watch_TestApp::Create );
    }

  private:
    void Create(Application& app)
    {
      initCalled = true;

      mTimer = Timer::New( 1000 );
      mTimer.TickSignal().Connect( this, &Watch_TestApp::Tick );
      mTimer.Start();

      ExcuteTest();
      Quit();
    }

    void ExcuteTest()
    {
      switch (mTestCase)
      {
        case WATCH_NEW_2:
          WatchApplicationNew02(mApplication);
          break;
        case WATCH_NEW_3:
          WatchApplicationNew03(mApplication);
          break;
        case WATCH_COPY_AND_ASSIGNMENT:
          WatchApplicationCopyAndAssignment(mApplication);
          break;
        case WATCH_TIMETICK_SIGNAL_P:
          WatchApplicationTimeTickSignalP(mApplication);
          break;
        case WATCH_TIMETICK_SIGNAL_N:
          WatchApplicationTimeTickSignalN();
          break;
        case WATCH_AMBIENT_TIMETICK_SIGNAL_P:
          WatchApplicationAmbientTickSignalP(mApplication);
          break;
        case WATCH_AMBIENT_TIMETICK_SIGNAL_N:
          WatchApplicationAmbientTickSignalN();
          break;
        case WATCH_AMBIENT_CHANGED_SIGNAL_P:
          WatchApplicationAmbientChangedSignalP(mApplication);
          break;
        case WATCH_AMBIENT_CHANGED_SIGNAL_N:
          WatchApplicationAmbientChangedSignalN();
          break;
      }
    }

    void Quit()
    {
      mApplication.Quit();
    }

    bool Tick()
    {
      mTimer.Stop();
      mApplication.Quit();
      return true;
    }

    // Data
    bool initCalled;
    WatchApplication&  mApplication;
    int mTestCase;

    Timer mTimer;
  };

} // unnamed namespace


void WatchTimeSignalCallback( Application& app, const WatchTime& time)
{
}

void WatchChangedSignalCallback( Application& app, bool ambient)
{
}

void WatchApplicationNew01(WatchApplication& application)
{
  DALI_CHECK_FAIL(!application, "Application::New() has failed." );

  DaliLog::PrintPass();
}

void WatchApplicationNew02(WatchApplication& application)
{
  DALI_CHECK_FAIL(!application, "Application::New() has failed." );

  DaliLog::PrintPass();
}

void WatchApplicationNew03(WatchApplication& application)
{
  DALI_CHECK_FAIL(!application, "Application::New() has failed." );

  DaliLog::PrintPass();
}

void WatchApplicationCopyAndAssignment(WatchApplication& application)
{
  WatchApplication copy( application );

  DALI_CHECK_FAIL( copy != application,"WatchApplication::CopyAndAssignment is failing");

  WatchApplication assigned;
  DALI_CHECK_FAIL( assigned,"WatchApplication::CopyAndAssignment is failing");

  assigned = application;
  DALI_CHECK_FAIL( copy != assigned,"WatchApplication::CopyAndAssignment is failing");

  DaliLog::PrintPass();
}

void WatchApplicationTimeTickSignalP(WatchApplication& application)
{
  application.TimeTickSignal().Connect( &WatchTimeSignalCallback );

  DALI_CHECK_FAIL(!application,"WatchApplication::TimeTickSignalP is failing");

  DaliLog::PrintPass();
}

void WatchApplicationTimeTickSignalN()
{
  WatchApplication application;

  try
  {
    application.TimeTickSignal().Connect( &WatchTimeSignalCallback );
    DALI_CHECK_FAIL(true,"WatchApplication::TimeTickSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"WatchApplication::TimeTickSignalN is failing");
  }

  DaliLog::PrintPass();
}

void WatchApplicationAmbientTickSignalP(WatchApplication& application)
{
  application.AmbientTickSignal().Connect( &WatchTimeSignalCallback );
  DALI_CHECK_FAIL(!application,"WatchApplication::AmbientTimeTickSignalP is failing");

  DaliLog::PrintPass();
}

void WatchApplicationAmbientTickSignalN()
{
  WatchApplication application;

  try
  {
    application.AmbientTickSignal().Connect( &WatchTimeSignalCallback );
    DALI_CHECK_FAIL(true,"WatchApplication::AmbientTimeTickSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"WatchApplication::AmbientTimeTickSignalN is failing");
  }

  DaliLog::PrintPass();
}

void WatchApplicationAmbientChangedSignalP(WatchApplication& application)
{
  application.AmbientChangedSignal().Connect( &WatchChangedSignalCallback );
  DALI_CHECK_FAIL(!application,"WatchApplication::AmbientChangedSignalP is failing");

  DaliLog::PrintPass();
}

void WatchApplicationAmbientChangedSignalN()
{
  WatchApplication application;

  try
  {
    application.AmbientChangedSignal().Connect( &WatchChangedSignalCallback );
    DALI_CHECK_FAIL(true,"WatchApplication::AmbientChangedSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"WatchApplication::AmbientChangedSignalN is failing");
  }

  DaliLog::PrintPass();
}

int UtcDaliWatchApplicationTest(int testMode)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  WatchApplication application = WatchApplication::New( &gArgc, &gArgv );
  CHECK_GL;
  Watch_TestApp testApp( application, testMode);
  application.MainLoop();
  return test_return_value;
}

int UtcDaliWatchApplicationNew01(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  WatchApplication application = WatchApplication::New();
  CHECK_GL;
  Watch_TestApp testApp( application );

  WatchApplicationNew01( application );
  return test_return_value;
}

int UtcDaliWatchApplicationNew02(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  WatchApplication application = WatchApplication::New( &gArgc, &gArgv );
  CHECK_GL;
  Watch_TestApp testApp( application, WATCH_NEW_2);
  application.MainLoop();
  return test_return_value;
}

int UtcDaliWatchApplicationNew03(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  WatchApplication application = WatchApplication::New( &gArgc, &gArgv, "stylesheet" );
  CHECK_GL;
  Watch_TestApp testApp( application, WATCH_NEW_3);
  application.MainLoop();
  return test_return_value;
}

int UtcDaliWatchApplicationCopyAndAssignment(void)
{
  return UtcDaliWatchApplicationTest(WATCH_COPY_AND_ASSIGNMENT);
}

int UtcDaliWatchApplicationTimeTickSignalP(void)
{
  return UtcDaliWatchApplicationTest(WATCH_TIMETICK_SIGNAL_P);
}

int UtcDaliWatchApplicationTimeTickSignalN(void)
{
  return UtcDaliWatchApplicationTest(WATCH_TIMETICK_SIGNAL_N);
}

int UtcDaliWatchApplicationAmbientTickSignalP(void)
{
  return UtcDaliWatchApplicationTest(WATCH_AMBIENT_TIMETICK_SIGNAL_P);
}

int UtcDaliWatchApplicationAmbientTickSignalN(void)
{
  return UtcDaliWatchApplicationTest(WATCH_AMBIENT_TIMETICK_SIGNAL_N);
}

int UtcDaliWatchApplicationAmbientChangedSignalP(void)
{
  return UtcDaliWatchApplicationTest(WATCH_AMBIENT_CHANGED_SIGNAL_P);
}

int UtcDaliWatchApplicationAmbientChangedSignalN(void)
{
  return UtcDaliWatchApplicationTest(WATCH_AMBIENT_CHANGED_SIGNAL_N);
}

