#include "utc-dali-application-common.h"
#include "system_settings.h"

#define WINDOW_POSITION 10
#define WINDOW_SIZE 100

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

bool gResizeSignalStatus = false;

/**
 * @function        utc_Dali_Application_startup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */

void utc_Dali_Application_startup(void)
{
  test_return_value=0;
}


/**
 * @function        utc_Dali_Application_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */

void utc_Dali_Application_cleanup(void)
{
}



void ApplicationNewP(Application& application);
void ApplicationNewP2(Application& application);
void ApplicationNewP3(Application& application);
void ApplicationNewP4(Application& application);
void ApplicationNewP6(Application& application);
void ApplicationMemoryLowSignalP(Application& application);
void ApplicationMemoryLowSignalN ();
void ApplicationInitSignalN(Application& application);
void ApplicationBatteryLowSignalP(Application& application);
void ApplicationBatteryLowSignalN();
void ApplicationRegionChangedSignalP(Application& application);
void ApplicationRegionChangedSignalN();
void ApplicationLanguageChangedSignalP(Application& application);
void ApplicationLanguageChangedSignalN();
void ApplicationlControlSignalP(Application& application);
void ApplicationlControlSignalN();
void ApplicationResizeSignalP(Application& application);
void ApplicationResizeSignalN();
void ApplicationResetSignalP(Application& application);
void ApplicationResetSignalN();
void ApplicationResumeSignalP(Application& application);
void ApplicationResumeSignalN();
void ApplicationPauseSignalP(Application& application);
void ApplicationPauseSignalN();
void ApplicationTerminateSignalP(Application& application);
void ApplicationTerminateSignalN();
void ApplicationStereoBaseSetAndGetP(Application& application);
void ApplicationSetStereoBaseN();
void ApplicationGetStereoBaseN();
void ApplicationSetViewModeN();
void ApplicationGetViewModeN();
void ApplicationViewModeSetAndGetP(Application& application);
void ApplicationReplaceWindowP(Application& application);
void ApplicationReplaceWindowN();
void ApplicationGetWindowP(Application& application);
void ApplicationGetWindowN();
void ApplicationAddIdleN();
void ApplicationQuitN();
void ApplicationLowerN();
void ApplicationMainLoopN();
void ApplicationCopyAndAssignmentP(Application& application);
void ApplicationConstructorP();
void ApplicationCopyConstructorP();
void ApplicationGetResourcePathP(Application& application);
void ApplicationGetRegionP(Application& application);
void ApplicationGetLanguageP(Application& application);
void ApplicationLowBatterySignalP(Application& application);
void ApplicationLowBatterySignalN();
void ApplicationLowMemorySignalP(Application& application);
void ApplicationLowMemorySignalN();

namespace
{
  enum TEST_CASES_LIST_APPLICATION
  {
    APPLICATION_NEW,
    APPLICATION_LOWER,
    APPLICATION_GET_WINDOW,
    APPLICATION_REPLACE_WINDOW,
    APPLICATION_VIEW_MODE,
    APPLICATION_STEREO_BASE,
    APPLICATION_CONSTRUCTOR_P,
    APPLICATION_COPY_CONSTRUCTOR_P,
    APPLICATION_NEW_P,
    APPLICATION_NEW_P2,
    APPLICATION_NEW_P3,
    APPLICATION_NEW_P4,
    APPLICATION_NEW_P6,
    APPLICATION_MEMORY_LOW_SIGNAL_P,
    APPLICATION_MEMORY_LOW_SIGNAL_N,
    APPLICATION_INIT_SIGNAL_N,
    APPLICATION_INIT_SIGNAL_P,
    APPLICATION_BATTERY_LOW_SIGNAL_P,
    APPLICATION_BATTERY_LOW_SIGNAL_N,
    APPLICATION_REGION_CHANGED_SIGNAL_P,
    APPLICATION_REGION_CHANGED_SIGNAL_N,
    APPLICATION_LANGUAGE_CHANGED_SIGNAL_P,
    APPLICATION_LANGUAGE_CHANGED_SIGNAL_N,
    APPLICATION_CONTROL_SIGNAL_P,
    APPLICATION_CONTROL_SIGNAL_N,
    APPLICATION_RESIZE_SIGNAL_P,
    APPLICATION_RESIZE_SIGNAL_N,
    APPLICATION_RESET_SIGNAL_P,
    APPLICATION_RESET_SIGNAL_N,
    APPLICATION_RESUME_SIGNAL_P,
    APPLICATION_RESUME_SIGNAL_N,
    APPLICATION_PAUSE_SIGNAL_P,
    APPLICATION_PAUSE_SIGNAL_N,
    APPLICATION_TERMINATE_SIGNAL_P,
    APPLICATION_TERMINATE_SIGNAL_N,
    APPLICATION_SET_GET_STEREO_BASE_P,
    APPLICATION_SET_STEREO_BASE_N,
    APPLICATION_GET_STEREO_BASE_N,
    APPLICATION_SET_VIEW_MODE_N,
    APPLICATION_GET_VIEW_MODE_N,
    APPLICATION_SET_GET_VIEW_MODE_P,
    APPLICATION_REPLACE_WINDOW_P,
    APPLICATION_REPLACE_WINDOW_N,
    APPLICATION_GET_WINDOW_N,
    APPLICATION_GET_WINDOW_P,
    APPLICATION_ADD_IDLE_N,
    APPLICATION_ADD_IDLE_P,
    APPLICATION_QUIT_N,
    APPLICATION_LOWER_N,
    APPLICATION_MAIN_LOOP_CONTEXT_LOSS_P,
    APPLICATION_MAIN_LOOP_N,
    APPLICATION_COPY_ASSIGNMENT_P,
    APPLICATION_GET_RESOURCE_PATH_P,
    APPLICATION_GET_REGION_P,
    APPLICATION_GET_LANGUAGE_P,
    APPLICATION_LOW_BATTERY_SIGNAL_P,
    APPLICATION_LOW_BATTERY_SIGNAL_N,
    APPLICATION_LOW_MEMORY_SIGNAL_P,
    APPLICATION_LOW_MEMORY_SIGNAL_N

  };

  struct Application_TestApp : public ConnectionTracker
  {
    Application_TestApp( Application& app, int test_case = APPLICATION_NEW )
      : mApplication( app ),
      mInitCalled( false ),
      mTerminateCalled( false ),
      mPauseCalled( false ),
      mIdleCalled( false ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Application_TestApp::OnInit );
      mApplication.TerminateSignal().Connect( this, &Application_TestApp::OnTerminate);
      mApplication.PauseSignal().Connect( this, &Application_TestApp::OnPause );
    }

    void OnInit(Application& app)
    {
      mInitCalled = true;

      mApplication.AddIdle( MakeCallback( this, &Application_TestApp::OnIdle ) );

      mTimer = Timer::New( 1000 );
      mTimer.TickSignal().Connect( this, &Application_TestApp::Tick );
      mTimer.Start();

      mTimer2 = Timer::New( 500 );
      mTimer2.TickSignal().Connect( this, &Application_TestApp::Tick2 );
      mTimer2.Start();

      ExcuteTest();
    }

    void OnTerminate(Application& app)
    {
      mTerminateCalled = true;
    }

    void OnPause(Application& app)
    {
      mPauseCalled = true;
    }

    void OnIdle()
    {
      mIdleCalled = true;
    }

    bool Tick2()
    {
      mOldWindow = mApplication.GetWindow();
      mApplication.ReplaceWindow( PositionSize( 0, 0, 100, 100 ), "dali-adaptor" );
      mTimer2.Stop();
      return false;
    }

    bool Tick()
    {
      if( mTestCase == APPLICATION_REPLACE_WINDOW_P )
      {
        ApplicationReplaceWindowP( mApplication );
      }

      mTimer.Stop();
      mApplication.Quit();
      return true;

    }

    void ExcuteTest()
    {
      switch (mTestCase)
      {
        case APPLICATION_MAIN_LOOP_N:
          ApplicationMainLoopN();
          break;

        case APPLICATION_MAIN_LOOP_CONTEXT_LOSS_P:
          ApplicationMainLoopContextLossP();
          break;

        case APPLICATION_LOWER_N:
          ApplicationLowerN();
          break;

        case APPLICATION_QUIT_N:
          ApplicationQuitN();
          break;

        case APPLICATION_ADD_IDLE_P:
          ApplicationAddIdleP();
          break;

        case APPLICATION_ADD_IDLE_N:
          ApplicationAddIdleN();
          break;

        case APPLICATION_GET_WINDOW_P:
          ApplicationGetWindowP(mApplication);
          break;

        case APPLICATION_GET_WINDOW_N:
          ApplicationGetWindowN();
          break;

        case APPLICATION_NEW_P:
          ApplicationNewP(mApplication);
          break;

        case APPLICATION_NEW_P2:
          ApplicationNewP2(mApplication);
          break;

        case APPLICATION_NEW_P3:
          ApplicationNewP3(mApplication);
          break;

        case APPLICATION_NEW_P4:
          ApplicationNewP4(mApplication);
          break;

        case APPLICATION_NEW_P6:
          ApplicationNewP6( mApplication );
          break;

        case APPLICATION_MEMORY_LOW_SIGNAL_P:
          ApplicationMemoryLowSignalP (mApplication);
          break;

        case APPLICATION_MEMORY_LOW_SIGNAL_N:
          ApplicationMemoryLowSignalN ();
          break;

        case APPLICATION_INIT_SIGNAL_N:
          ApplicationInitSignalN (mApplication);
          break;

        case APPLICATION_INIT_SIGNAL_P:
          ApplicationInitSignalP();
          break;

        case APPLICATION_BATTERY_LOW_SIGNAL_P:
          ApplicationBatteryLowSignalP(mApplication);
          break;

        case APPLICATION_BATTERY_LOW_SIGNAL_N:
          ApplicationBatteryLowSignalN();
          break;

        case APPLICATION_REGION_CHANGED_SIGNAL_P:
          ApplicationRegionChangedSignalP(mApplication);
          break;

        case APPLICATION_REGION_CHANGED_SIGNAL_N:
          ApplicationRegionChangedSignalN();
          break;

        case APPLICATION_LANGUAGE_CHANGED_SIGNAL_P:
          ApplicationLanguageChangedSignalP(mApplication);
          break;

        case APPLICATION_LANGUAGE_CHANGED_SIGNAL_N:
          ApplicationLanguageChangedSignalN();
          break;

        case APPLICATION_CONTROL_SIGNAL_P:
          ApplicationlControlSignalP(mApplication);
          break;

        case APPLICATION_CONTROL_SIGNAL_N:
          ApplicationlControlSignalN();
          break;

        case APPLICATION_RESIZE_SIGNAL_P:
          ApplicationResizeSignalP(mApplication);
          break;

        case APPLICATION_RESIZE_SIGNAL_N:
          ApplicationResizeSignalN();
          break;

        case APPLICATION_RESET_SIGNAL_P:
          ApplicationResetSignalP(mApplication);
          break;

        case APPLICATION_RESET_SIGNAL_N:
          ApplicationResetSignalN();
          break;

        case APPLICATION_RESUME_SIGNAL_P:
          ApplicationResumeSignalP(mApplication);
          break;

        case APPLICATION_RESUME_SIGNAL_N:
          ApplicationResumeSignalN();
          break;

        case APPLICATION_PAUSE_SIGNAL_P:
          ApplicationPauseSignalP(mApplication);
          break;

        case APPLICATION_PAUSE_SIGNAL_N:
          ApplicationPauseSignalN();
          break;

        case APPLICATION_TERMINATE_SIGNAL_P:
          ApplicationTerminateSignalP(mApplication);
          break;

        case APPLICATION_TERMINATE_SIGNAL_N:
          ApplicationTerminateSignalN();
          break;

        case APPLICATION_SET_GET_STEREO_BASE_P:
          ApplicationStereoBaseSetAndGetP(mApplication);
          break;

        case APPLICATION_SET_STEREO_BASE_N:
          ApplicationSetStereoBaseN();
          break;

        case APPLICATION_GET_STEREO_BASE_N:
          ApplicationGetStereoBaseN();
          break;

        case APPLICATION_SET_VIEW_MODE_N:
          ApplicationSetViewModeN();
          break;

        case APPLICATION_GET_VIEW_MODE_N:
          ApplicationGetViewModeN();
          break;

        case APPLICATION_SET_GET_VIEW_MODE_P:
          ApplicationViewModeSetAndGetP(mApplication);
          break;

        case APPLICATION_REPLACE_WINDOW_N:
          ApplicationReplaceWindowN();
          break;

        case APPLICATION_COPY_ASSIGNMENT_P:
          ApplicationCopyAndAssignmentP(mApplication);
          break;

        case APPLICATION_CONSTRUCTOR_P:
          ApplicationConstructorP();
          break;

        case APPLICATION_COPY_CONSTRUCTOR_P:
          ApplicationCopyConstructorP();
          break;

        case APPLICATION_GET_RESOURCE_PATH_P:
          ApplicationGetResourcePathP(mApplication);
          break;

        case APPLICATION_GET_REGION_P:
          ApplicationGetRegionP(mApplication);
          break;

        case APPLICATION_GET_LANGUAGE_P:
          ApplicationGetLanguageP(mApplication);
          break;

        case APPLICATION_LOW_BATTERY_SIGNAL_P:
          ApplicationLowBatterySignalP(mApplication);
          break;

        case APPLICATION_LOW_BATTERY_SIGNAL_N:
          ApplicationLowBatterySignalN();
          break;

        case APPLICATION_LOW_MEMORY_SIGNAL_P:
          ApplicationLowMemorySignalP(mApplication);
          break;

        case APPLICATION_LOW_MEMORY_SIGNAL_N:
          ApplicationLowMemorySignalN();
          break;
      }
    }

    void TestLower()
    {
      mApplication.Lower();
    }

    void TestGetWindow()
    {
      Window window = mApplication.GetWindow();

    }

    void TestViewMode()
    {
      mApplication.SetViewMode(STEREO_HORIZONTAL);

      mApplication.SetViewMode(STEREO_VERTICAL);
    }

    void TestStereoBase()
    {

    }

    // Test functions
    void ApplicationInitSignalP()
    {
      DALI_CHECK_FAIL( !mInitCalled, "Application::InitSignalP is failing" );
      DaliLog::PrintPass();
    }

    void ApplicationAddIdleP()
    {
      DALI_CHECK_FAIL( mIdleCalled, "Application AddIdle is failed" );
      DaliLog::PrintPass();
    }

    void ApplicationMainLoopContextLossP()
    {
      DALI_CHECK_FAIL( !mInitCalled, "Application::MainLoopContextLossP is failing" );
      DaliLog::PrintPass();
    }

    // Data
    bool mInitCalled;
    bool mTerminateCalled;
    bool mPauseCalled;
    bool mIdleCalled;

    Application& mApplication;

    Timer mTimer2;
    Window mOldWindow;

    // Data
    int mTestCase;
    Timer mTimer;
  };

}

void ApplicationSignalCallback( Application& app )
{
}

void ApplicationLowBatterySignalCallback( DeviceStatus::Battery::Status state )
{
}

void ApplicationLowMemorySignalCallback( DeviceStatus::Memory::Status state )
{
}

void ApplicationControlSignalCallback(Application&, void *)
{
}

void ApplicationResizeSignalCallback(Application& app)
{
  gResizeSignalStatus = true;
}

void ApplicationConstructorP()
{
  Dali::Application application;
  DALI_CHECK_FAIL(application,"Application::ConstructorP is failing");

  DaliLog::PrintPass();
}

void ApplicationInitSignalN(Application& application)
{

  try
  {
    application.InitSignal().Connect( &ApplicationSignalCallback );
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(true,"Application::InitSignalN is failing");
  }

  DaliLog::PrintPass();
}


void ApplicationMemoryLowSignalP(Application& application)
{
  application.MemoryLowSignal().Connect( &ApplicationSignalCallback );

  DALI_CHECK_FAIL(!application,"Application::MemoryLowSignalN is failing");

  DaliLog::PrintPass();
}

void ApplicationMemoryLowSignalN()
{
  Application application;
  try
  {
    application.MemoryLowSignal().Connect( &ApplicationSignalCallback );

    DALI_CHECK_FAIL(true,"Application::MemoryLowSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::MemoryLowSignalN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationNewP(Application& application)
{

  DALI_CHECK_FAIL(!application, "Application::New() has failed." );

  DaliLog::PrintPass();
}

void ApplicationNewP2(Application& application)
{

  DALI_CHECK_FAIL(!application, "Application::New() has failed." );

  DaliLog::PrintPass();
}

void ApplicationNewP3(Application& application)
{

  DALI_CHECK_FAIL(!application, "Application::New() has failed." );

  DaliLog::PrintPass();
}

void ApplicationNewP4(Application& application)
{

  DALI_CHECK_FAIL(!application, "Application::New() has failed." );

  DaliLog::PrintPass();
}

void ApplicationNewP6( Application& application )
{
  Window window = application.GetWindow();

  Window::WindowPosition position = window.GetPosition();
  Window::WindowSize size = window.GetSize();

  DALI_CHECK_FAIL( position != Window::WindowPosition( WINDOW_POSITION, WINDOW_POSITION ), "Window position is not equal." );
  DALI_CHECK_FAIL( size != Window::WindowSize( WINDOW_SIZE, WINDOW_SIZE ), "Window size is not equal." );

  DaliLog::PrintPass();
}

void ApplicationBatteryLowSignalP(Application& application)
{
  application.BatteryLowSignal().Connect( &ApplicationSignalCallback );

  DALI_CHECK_FAIL(!application,"Application::BatteryLowSignalP is failing");

  DaliLog::PrintPass();
}

void ApplicationBatteryLowSignalN()
{
  Application application;

  try
  {
    application.BatteryLowSignal().Connect( &ApplicationSignalCallback );

    DALI_CHECK_FAIL(true,"Application::MemoryLowSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::BatteryLowSignalN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationRegionChangedSignalP(Application& application)
{
  application.RegionChangedSignal().Connect( &ApplicationSignalCallback );

  DALI_CHECK_FAIL(!application,"Application::RegionChangedSignalP is failing");

  DaliLog::PrintPass();
}

void ApplicationRegionChangedSignalN()
{
  Application application;

  try
  {
    application.RegionChangedSignal().Connect( &ApplicationSignalCallback );
    DALI_CHECK_FAIL(true,"Application::RegionChangedSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::RegionChangedSignalN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationLanguageChangedSignalP(Application& application)
{
  application.LanguageChangedSignal().Connect( &ApplicationSignalCallback );
  DALI_CHECK_FAIL(!application,"Application::LanguageChangedSignalP is failing");

  DaliLog::PrintPass();
}

void ApplicationLanguageChangedSignalN()
{
  Application application;

  try
  {
    application.LanguageChangedSignal().Connect( &ApplicationSignalCallback );
    DALI_CHECK_FAIL(true,"Application::LanguageChangedSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::LanguageChangedSignalN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationlControlSignalP(Application& application)
{
  application.AppControlSignal().Connect( &ApplicationControlSignalCallback );

  DALI_CHECK_FAIL(!application,"Application::ControlSignalP is failing");

  DaliLog::PrintPass();
}

void ApplicationlControlSignalN()
{
  Application application;

  try
  {
    application.AppControlSignal().Connect( &ApplicationControlSignalCallback );

    DALI_CHECK_FAIL(true,"Application::ControlSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::ControlSignalN is failing");
  }

  DaliLog::PrintPass();
}


void ApplicationResizeSignalP(Application& application)
{
  application.ResizeSignal().Connect( &ApplicationSignalCallback );

  DALI_CHECK_FAIL(!application,"Application::ResizeSignalP is failing");

  DaliLog::PrintPass();
}

void ApplicationResizeSignalN()
{
  Application application;

  try
  {
    application.ResizeSignal().Connect( &ApplicationSignalCallback );

    DALI_CHECK_FAIL(true,"Application::ResizeSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::ResizeSignalN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationResetSignalP(Application& application)
{
  application.ResetSignal().Connect( &ApplicationSignalCallback );

  DALI_CHECK_FAIL(!application,"Application::ResetSignalP is failing");

  DaliLog::PrintPass();
}

void ApplicationResetSignalN()
{
  Application application;

  try
  {
    application.ResetSignal().Connect( &ApplicationSignalCallback );

    DALI_CHECK_FAIL(true,"Application::ResetSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::ResetSignalN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationResumeSignalP(Application& application)
{
  application.ResumeSignal().Connect( &ApplicationSignalCallback );

  DALI_CHECK_FAIL(!application,"Application::ResumeSignalP is failing");

  DaliLog::PrintPass();
}

void ApplicationResumeSignalN()
{
  Application application;

  try
  {
    application.ResumeSignal().Connect( &ApplicationSignalCallback );

    DALI_CHECK_FAIL(true,"Application::ResumeSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::ResumeSignalN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationPauseSignalP(Application& application)
{
  application.PauseSignal().Connect( &ApplicationSignalCallback );

  DALI_CHECK_FAIL(!application,"Application::PauseSignalP is failing");

  DaliLog::PrintPass();
}


void ApplicationPauseSignalN()
{
  Application application;

  try
  {
    application.PauseSignal().Connect( &ApplicationSignalCallback );

    DALI_CHECK_FAIL(true,"Application::PauseSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::PauseSignalN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationTerminateSignalP(Application& application)
{
  application.TerminateSignal().Connect( &ApplicationSignalCallback );

  DALI_CHECK_FAIL(!application,"Application::TerminateSignalP is failing");

  DaliLog::PrintPass();
}

void ApplicationTerminateSignalN()
{
  Application application;

  try
  {
    application.TerminateSignal().Connect( &ApplicationSignalCallback );

    DALI_CHECK_FAIL(true,"Application::TerminateSignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::TerminateSignalN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationLowBatterySignalP(Application& application)
{
  application.LowBatterySignal().Connect( &ApplicationLowBatterySignalCallback );

  DALI_CHECK_FAIL(!application,"Application::LowBatterySignalP is failing");

  DaliLog::PrintPass();
}

void ApplicationLowBatterySignalN()
{
  Application application;

  try
  {
    application.LowBatterySignal().Connect( &ApplicationLowBatterySignalCallback );

    DALI_CHECK_FAIL(true,"Application::LowBatterySignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::LowBatterySignalN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationLowMemorySignalP(Application& application)
{
  application.LowMemorySignal().Connect( &ApplicationLowMemorySignalCallback );

  DALI_CHECK_FAIL(!application,"Application::LowMemorySignalP is failing");

  DaliLog::PrintPass();
}

void ApplicationLowMemorySignalN()
{
  Application application;

  try
  {
    application.LowMemorySignal().Connect( &ApplicationLowMemorySignalCallback );

    DALI_CHECK_FAIL(true,"Application::LowMemorySignalN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::LowMemorySignalN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationSetStereoBaseN()
{
  Application application;

  try
  {
    application.SetStereoBase( 1.0f );

    DALI_CHECK_FAIL(true,"Application::SetStereoBaseN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::SetStereoBaseN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationGetStereoBaseN()
{
  Application application;

  try
  {
    (void) application.GetStereoBase();

    DALI_CHECK_FAIL(true,"Application::GetStereoBaseN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::GetStereoBaseN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationStereoBaseSetAndGetP(Application& application)
{
  float setStereoBase = 1.0f;
  application.SetStereoBase( setStereoBase );
  float getStereoBase = application.GetStereoBase();
  DALI_CHECK_FAIL( setStereoBase != getStereoBase, "Stereo base set and get is failed." );
  DaliLog::PrintPass();
}

void ApplicationSetViewModeN()
{
  Application application;

  try
  {
    application.SetViewMode( STEREO_VERTICAL );

    DALI_CHECK_FAIL(true,"Application::SetViewModeN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::SetViewModeN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationGetViewModeN()
{
  Application application;

  try
  {
    (void) application.GetViewMode();

    DALI_CHECK_FAIL(true,"Application::GetViewModeN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::GetViewModeN is failing");
  }

  DaliLog::PrintPass();
}


void ApplicationViewModeSetAndGetP(Application& application)
{
  application.SetViewMode( STEREO_HORIZONTAL );
  ViewMode viewMode = application.GetViewMode();
  DALI_CHECK_FAIL( viewMode != STEREO_HORIZONTAL, "View mode set and get is failed." );

  DaliLog::PrintPass();
}

void ApplicationReplaceWindowN()
{
  Application application;

  try
  {
    application.ReplaceWindow( PositionSize(), "window" );

    DALI_CHECK_FAIL(true,"Application::ReplaceWindowN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::ReplaceWindowN is failing");
  }

  DaliLog::PrintPass();
}


void ApplicationReplaceWindowP(Application& application)
{
  Window window = application.GetWindow();
  application.ResizeSignal().Connect( &ApplicationResizeSignalCallback );
  application.ReplaceWindow( PositionSize( 0, 0, Stage::GetCurrent().GetSize().width - 1, Stage::GetCurrent().GetSize().height - 1), "New Window" );
  DALI_CHECK_FAIL( !gResizeSignalStatus, "Application Resize Signal is not fired" );
  DALI_CHECK_FAIL( window == application.GetWindow(), "Application ReplaceWindow is failed" );
  DaliLog::PrintPass();
}

void ApplicationGetWindowN()
{
  Application application;

  try
  {
    (void) application.GetWindow();
    DALI_CHECK_FAIL(true,"Application::GetWindowN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::GetWindowN is failing");
  }

  DaliLog::PrintPass();
}


void ApplicationGetWindowP(Application& application)
{
  Window window = application.GetWindow();

  DALI_CHECK_FAIL( !window, "Application::GetWindowP is failing" );

  DaliLog::PrintPass();
}

void ApplicationAddIdleN()
{
  Application application;

  try
  {
    CallbackBase* callback = NULL;
    application.AddIdle( callback );

    DALI_CHECK_FAIL(true,"Application::AddIdleN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::AddIdleN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationQuitN()
{
  Application application;

  try
  {
    application.Quit();

    DALI_CHECK_FAIL(true,"Application::QuitN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::QuitN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationLowerN()
{
  Application application;

  try
  {
    application.Lower();

    DALI_CHECK_FAIL(true,"Application::LowerN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::LowerN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationMainLoopN()
{
  Application application;

  try
  {
    application.MainLoop();
    DALI_CHECK_FAIL(true,"Application::MainLoopN is failing");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(false,"Application::MainLoopN is failing");
  }

  DaliLog::PrintPass();
}

void ApplicationCopyAndAssignmentP(Application& application)
{
  Application copy( application );
  Application assigned;

  DALI_CHECK_FAIL(assigned,"Application::CopyAndAssignment is failing");

  assigned = application;

  DALI_CHECK_FAIL(copy != assigned,"Application::CopyAndAssignment is failing");

  DaliLog::PrintPass();
}

void ApplicationCopyConstructorP(void)
{

  Dali::Application application;

  DALI_CHECK_FAIL(application,"Application::ConstructorP is failing");

  Dali::Application copy( application );

  DALI_CHECK_FAIL(copy != application,"TtsPlayer::CopyConstructorP is failing");

  DaliLog::PrintPass();
}

void ApplicationGetResourcePathP(Application& application)
{
  std::string result ("**invalid path**"); // Calling GetResourcePath should replace this with a system dependent path or "".

  result = application.GetResourcePath();
  DALI_CHECK_FAIL( result == "**invalid path**", "Application::GetResourcePathP is failed." );

  DaliLog::PrintPass();
}

void ApplicationGetRegionP(Application& application)
{
  char* compareString;
  system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY, &compareString);

  std::string result = application.GetRegion();
  DALI_CHECK_FAIL( result.compare( std::string(compareString) ), "Application::GetRegionP is failed." );

  DaliLog::PrintPass();
}

void ApplicationGetLanguageP(Application& application)
{
  char* compareString;
  system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &compareString);

  std::string result = application.GetLanguage();
  DALI_CHECK_FAIL( result.compare( std::string(compareString) ), "Application::GetLanguageP is failed." );

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliApplicationCopyConstructorP
 * @since_tizen     2.4
 * @description     checks for Application::CopyConstructorP() functionality
 */

int UtcDaliApplicationCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationConstructorP
 * @since_tizen     2.4
 * @description     checks for Application::ConstructorP() functionality
 */

int UtcDaliApplicationConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationCopyAndAssignment
 * @since_tizen     2.4
 * @description     checks for Application::CopyAndAssignment() functionality
 */

int UtcDaliApplicationCopyAndAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_COPY_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationMainLoopN
 * @since_tizen     2.4
 * @description     checks for Application::MainLoopN() functionality
 */


int UtcDaliApplicationMainLoopN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_MAIN_LOOP_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationMainLoopContextLossP
 * @since_tizen     2.4
 * @description     checks for Application::MainLoopContextLossP() functionality
 */

int UtcDaliApplicationMainLoopContextLossP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_MAIN_LOOP_CONTEXT_LOSS_P);
  application.MainLoop( Configuration::APPLICATION_HANDLES_CONTEXT_LOSS );
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationLowerN
 * @since_tizen     2.4
 * @description     checks for Application::LowerN() functionality
 */

int UtcDaliApplicationLowerN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_LOWER_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationQuitN
 * @since_tizen     2.4
 * @description     checks for Application::QuitN() functionality
 */

int UtcDaliApplicationQuitN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_QUIT_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationAddIdleN
 * @since_tizen     2.4
 * @description     checks for Application::AddIdleN() functionality
 */

int UtcDaliApplicationAddIdleN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_ADD_IDLE_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationAddIdleP
 * @since_tizen     2.4
 * @description     checks for Application::AddIdleP() functionality
 */

int UtcDaliApplicationAddIdleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_ADD_IDLE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationGetWindowN
 * @since_tizen     2.4
 * @description     checks for Application::GetWindowN() functionality
 */

int UtcDaliApplicationGetWindowN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_GET_WINDOW_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationGetWindowP
 * @since_tizen     2.4
 * @description     checks for Application::GetWindowP() functionality
 */

int UtcDaliApplicationGetWindowP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_GET_WINDOW_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationReplaceWindowP
 * @since_tizen     2.4
 * @description     checks for Application::ReplaceWindowP() functionality
 */

int UtcDaliApplicationReplaceWindowP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_REPLACE_WINDOW_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationReplaceWindowN
 * @since_tizen     2.4
 * @description     checks for Application::ReplaceWindowN() functionality
 */

int UtcDaliApplicationReplaceWindowN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_REPLACE_WINDOW_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationSetViewModeN
 * @since_tizen     2.4
 * @description     checks for Application::SetViewModeN() functionality
 */

int UtcDaliApplicationSetViewModeN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_SET_VIEW_MODE_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationGetViewModeN
 * @since_tizen     2.4
 * @description     checks for Application::GetViewModeN() functionality
 */

int UtcDaliApplicationGetViewModeN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_GET_VIEW_MODE_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationViewModeSetAndGetP
 * @since_tizen     2.4
 * @description     checks for Application::ViewModeSetAndGetP() functionality
 */

int UtcDaliApplicationViewModeSetAndGetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_SET_GET_VIEW_MODE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationStereoBaseSetAndGetP
 * @since_tizen     2.4
 * @description     checks for Application::StereoBaseSetAndGetP() functionality
 */

int UtcDaliApplicationStereoBaseSetAndGetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_SET_GET_STEREO_BASE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationSetStereoBaseN
 * @since_tizen     2.4
 * @description     checks for Application::SetStereoBaseN() functionality
 */

int UtcDaliApplicationSetStereoBaseN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_SET_STEREO_BASE_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationGetStereoBaseN
 * @since_tizen     2.4
 * @description     checks for Application::GetStereoBaseN() functionality
 */

int UtcDaliApplicationGetStereoBaseN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_GET_STEREO_BASE_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationTerminateSignalP
 * @since_tizen     2.4
 * @description     checks for Application::TerminateSignalP() functionality
 */

int UtcDaliApplicationTerminateSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_TERMINATE_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationTerminateSignalN
 * @since_tizen     2.4
 * @description     checks for Application::TerminateSignalN() functionality
 */

int UtcDaliApplicationTerminateSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_TERMINATE_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationPauseSignalP
 * @since_tizen     2.4
 * @description     checks for Application::PauseSignalP() functionality
 */

int UtcDaliApplicationPauseSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_PAUSE_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationPauseSignalN
 * @since_tizen     2.4
 * @description     checks for Application::PauseSignalN() functionality
 */

int UtcDaliApplicationPauseSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_PAUSE_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationResumeSignalP
 * @since_tizen     2.4
 * @description     checks for Application::ResumeSignalP() functionality
 */

int UtcDaliApplicationResumeSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_RESUME_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationResumeSignalN
 * @since_tizen     2.4
 * @description     checks for Application::ResumeSignalN() functionality
 */

int UtcDaliApplicationResumeSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_RESUME_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationResetSignalP
 * @since_tizen     2.4
 * @description     checks for Application::ResetSignalP() functionality
 */

int UtcDaliApplicationResetSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_RESET_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationResetSignalN
 * @since_tizen     2.4
 * @description     checks for Application::ResetSignalN() functionality
 */

int UtcDaliApplicationResetSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_RESET_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationResizeSignalP
 * @since_tizen     2.4
 * @description     checks for Application::ResizeSignalP() functionality
 */

int UtcDaliApplicationResizeSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_RESIZE_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationResizeSignalN
 * @since_tizen     2.4
 * @description     checks for Application::ResizeSignalN() functionality
 */

int UtcDaliApplicationResizeSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_RESIZE_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationlControlSignalP
 * @since_tizen     2.4
 * @description     checks for Application::ControlSignalP() functionality
 */

int UtcDaliApplicationlControlSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_CONTROL_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationlControlSignalN
 * @since_tizen     2.4
 * @description     checks for Application::ControlSignalN() functionality
 */

int UtcDaliApplicationlControlSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_CONTROL_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationLanguageChangedSignalP
 * @since_tizen     2.4
 * @description     checks for Application::LanguageChangedSignalP() functionality
 */

int UtcDaliApplicationLanguageChangedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_LANGUAGE_CHANGED_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationLanguageChangedSignalN
 * @since_tizen     2.4
 * @description     checks for Application::LanguageChangedSignalN() functionality
 */

int UtcDaliApplicationLanguageChangedSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_LANGUAGE_CHANGED_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationRegionChangedSignalP
 * @since_tizen     2.4
 * @description     checks for Application::RegionChangedSignalP() functionality
 */

int UtcDaliApplicationRegionChangedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_REGION_CHANGED_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationRegionChangedSignalN
 * @since_tizen     2.4
 * @description     checks for Application::RegionChangedSignalN() functionality
 */

int UtcDaliApplicationRegionChangedSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_REGION_CHANGED_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationBatteryLowSignalP
 * @since_tizen     2.4
 * @description     checks for Application::BatteryLowSignalP() functionality
 */

int UtcDaliApplicationBatteryLowSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_BATTERY_LOW_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationBatteryLowSignalN
 * @since_tizen     2.4
 * @description     checks for Application::BatteryLowSignalN() functionality
 */

int UtcDaliApplicationBatteryLowSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_BATTERY_LOW_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationInitSignalP
 * @since_tizen     2.4
 * @description     checks for Application::InitSignalP() functionality
 */

int UtcDaliApplicationInitSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_INIT_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationInitSignalN
 * @since_tizen     2.4
 * @description     checks for Application::InitSignalN() functionality
 */

int UtcDaliApplicationInitSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_INIT_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationMemoryLowSignalP
 * @since_tizen     2.4
 * @description     checks for Application::nMemoryLowSignalP() functionality
 */

int UtcDaliApplicationMemoryLowSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_MEMORY_LOW_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationMemoryLowSignalN
 * @since_tizen     2.4
 * @description     checks for Application::MemoryLowSignalN() functionality
 */

int UtcDaliApplicationMemoryLowSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_MEMORY_LOW_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationNewP
 * @since_tizen     2.4
 * @description     checks for Application::New() functionality
 */

int UtcDaliApplicationNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_NEW_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationNewP2
 * @since_tizen     2.4
 * @description     checks for Application::New() functionality with parameters
 */

int UtcDaliApplicationNewP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv, "stylesheet" );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_NEW_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationNewP3
 * @since_tizen     2.4
 * @description     checks for Application::New() functionality with parameters
 */

int UtcDaliApplicationNewP3(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv, "stylesheet", Application::TRANSPARENT );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_NEW_P3);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationNewP4
 * @since_tizen     2.4
 * @description     checks for Application::New() functionality with parameters
 */

int UtcDaliApplicationNewP4(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv, "stylesheet", Application::OPAQUE );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_NEW_P4);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationNewP5
 * @since_tizen     2.4
 * @description     checks for Application::New() functionality with no parameters
 */

int UtcDaliApplicationNewP5(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New();
  CHECK_GL;

  DALI_TEST_CHECK(application);
  DaliLog::PrintPass();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationNewP6
 * @since_tizen     4.0
 * @description     checks for Application::New() functionality with window position and size
 */

int UtcDaliApplicationNewP6(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv, "stylesheet", Application::OPAQUE, PositionSize( WINDOW_POSITION, WINDOW_POSITION, WINDOW_SIZE, WINDOW_SIZE ) );
  CHECK_GL;

  Application_TestApp testApp( application, APPLICATION_NEW_P6);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationGetResourcePathP
 * @since_tizen     4.0
 * @description     Gets path application resources are stored at.
 */

int UtcDaliApplicationGetResourcePathP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_GET_RESOURCE_PATH_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationGetRegionP
 * @since_tizen     4.0
 * @description     checks for Application::GetRegionP() functionality
 */

int UtcDaliApplicationGetRegionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_GET_REGION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationGetLanguageP
 * @since_tizen     4.0
 * @description     checks for Application::GetLanguage() functionality
 */

int UtcDaliApplicationGetLanguageP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_GET_LANGUAGE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationLowBatterySignalP
 * @since_tizen     4.0
 * @description     checks for Application::LowBatterySignalP() functionality
 */

int UtcDaliApplicationLowBatterySignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_LOW_BATTERY_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationLowBatterySignalN
 * @since_tizen     4.0
 * @description     checks for Application::LowBatterySignalN() functionality
 */

int UtcDaliApplicationLowBatterySignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_LOW_BATTERY_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationLowMemorySignalP
 * @since_tizen     4.0
 * @description     checks for Application::LowMemorySignalN() functionality
 */

int UtcDaliApplicationLowMemorySignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_LOW_MEMORY_SIGNAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliApplicationLowMemorySignalN
 * @since_tizen     4.0
 * @description     checks for Application::LowMemorySignalN() functionality
 */

int UtcDaliApplicationLowMemorySignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Application_TestApp testApp( application, APPLICATION_LOW_MEMORY_SIGNAL_N);
  application.MainLoop();
  return test_return_value;
}
