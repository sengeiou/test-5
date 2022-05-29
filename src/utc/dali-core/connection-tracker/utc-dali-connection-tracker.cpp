#include "utc-dali-connection-tracker-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: ConnectionTracker

void CbConnectionTrackerReset(void *pData)
{
  ConnectionTrackerReset();
}

void CbConnectionTrackerResetSlotObserver(void *pData)
{
  delete gConnectionTrackerSlotObserver;
  gConnectionTrackerSlotObserver = NULL;
}

/**
 * @function            utc_Dali_ConnectionTracker_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_ConnectionTracker_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_ConnectionTracker_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_ConnectionTracker_cleanup(void)
{

}

void ConnectionTrackerConstructorP();
void ConnectionTrackerInterfaceConstructorP();
void ConnectionTrackerDisconnectAllP();
void ConnectionTrackerDisconnectAllN();
void ConnectionTrackerGetConnectionCountP();
void ConnectionTrackerSignalConnectedP();
void ConnectionTrackerSignalDisconnectP();

namespace
{
  enum TEST_CASES_LIST_CONNECTION_TRACKER
  {
    CONNECTION_TRACKER_CONSTRUCTOR_P,
    CONNECTION_TRACKER_INTERFACE_CONSTRUCTOR_P,
    CONNECTION_TRACKER_DISCONNECT_ALL_P,
    CONNECTION_TRACKER_DISCONNECT_ALL_N,
    CONNECTION_TRACKER_GET_CONNECTION_COUNT_P,
    CONNECTION_TRACKER_SIGNAL_CONNECTED_P,
    CONNECTION_TRACKER_SIGNAL_DISCONNECTED_P
  };

  struct ConnectionTracker_TestApp : public ConnectionTracker
  {
    ConnectionTracker_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ConnectionTracker_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &ConnectionTracker_TestApp::Tick );
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
        case CONNECTION_TRACKER_CONSTRUCTOR_P:
          ConnectionTrackerConstructorP();
          break;
        case CONNECTION_TRACKER_INTERFACE_CONSTRUCTOR_P:
          ConnectionTrackerInterfaceConstructorP();
          break;
        case CONNECTION_TRACKER_DISCONNECT_ALL_P:
          ConnectionTrackerDisconnectAllP();
          break;
        case CONNECTION_TRACKER_DISCONNECT_ALL_N:
          ConnectionTrackerDisconnectAllN();
          break;
        case CONNECTION_TRACKER_GET_CONNECTION_COUNT_P:
          ConnectionTrackerGetConnectionCountP();
          break;
        case CONNECTION_TRACKER_SIGNAL_CONNECTED_P:
          ConnectionTrackerSignalConnectedP();
          break;
        case CONNECTION_TRACKER_SIGNAL_DISCONNECTED_P:
          ConnectionTrackerSignalDisconnectP();
          break;
      }
    }

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

void ConnectionTrackerConstructorP()
{
  ConnectionTracker tracker;
  DALI_CHECK_FAIL( tracker.GetConnectionCount() != NoConnection , " ConnectionTracker constructor is failed");

  DaliLog::PrintPass();
}

void ConnectionTrackerInterfaceConstructorP()
{
  TestConnectionTrackerInterface connect;
  DALI_CHECK_FAIL( connect.GetConnectionCount() != NoConnection , " ConnectionTrackerInterface constructor is failed");

  DaliLog::PrintPass();
}

void ConnectionTrackerDisconnectAllP()
{
  const int SIGNAL_COUNT_CONNECTED = 3;
  gConnectionTrackerSlotObserver = NULL;
  gConnectionTrackerCallBack = NULL;

  gConnectionTrackerSlotObserver = new ConnectionTrackerSlotObserver();
  DALI_CHECK_FAIL( !gConnectionTrackerSlotObserver , "Failed to create ConnectionTrackerSlotObserver handler.");

  gConnectionTrackerCallBack = new CallbackFunction( TestCallBackFunction::CallBack );
  DALI_CHECK_FAIL_CB( !gConnectionTrackerCallBack, "Failed to create CallbackFunction handler.", CbConnectionTrackerResetSlotObserver, NULL);

  ConnectionTracker connect;
  for( int nCountSignal = 0; nCountSignal < SIGNAL_COUNT_CONNECTED; nCountSignal++ )
  {
    connect.SignalConnected(  gConnectionTrackerSlotObserver,  gConnectionTrackerCallBack );
  }
  size_t size = connect.GetConnectionCount();
  DALI_CHECK_FAIL_CB(size == NoConnection, "SignalConnected api failed and GetConnectionCount api returns zero.", CbConnectionTrackerReset, NULL);

  connect.DisconnectAll();

  size = connect.GetConnectionCount();
  DALI_CHECK_FAIL_CB(size != NoConnection, "DisconnectAll api failed to disconnect all signals.", CbConnectionTrackerReset, NULL);
  ConnectionTrackerReset();

  DaliLog::PrintPass();
}

void ConnectionTrackerDisconnectAllN()
{
  ConnectionTracker connect;

  size_t size = connect.GetConnectionCount();
  DALI_CHECK_FAIL_CB(size != NoConnection, "DisconnectAll api failed to disconnect all signals.", CbConnectionTrackerReset, NULL);

  connect.DisconnectAll();

  size = connect.GetConnectionCount();
  DALI_CHECK_FAIL_CB(size != NoConnection, "DisconnectAll api failed to disconnect all signals.", CbConnectionTrackerReset, NULL);
  ConnectionTrackerReset();

  DaliLog::PrintPass();
}

void ConnectionTrackerGetConnectionCountP()
{
  const int SIGNAL_COUNT_CONNECTED = 3;
  gConnectionTrackerSlotObserver = NULL;
  gConnectionTrackerCallBack = NULL;

  gConnectionTrackerSlotObserver = new ConnectionTrackerSlotObserver();
  DALI_CHECK_FAIL( !gConnectionTrackerSlotObserver , "Failed to create ConnectionTrackerSlotObserver handler.");

  gConnectionTrackerCallBack = new CallbackFunction( TestCallBackFunction::CallBack );
  DALI_CHECK_FAIL_CB( !gConnectionTrackerCallBack, "Failed to create CallbackFunction handler.", CbConnectionTrackerResetSlotObserver, NULL);

  ConnectionTracker connect;
  for( int nCountSignal = 0; nCountSignal < SIGNAL_COUNT_CONNECTED; nCountSignal++ )
  {
    connect.SignalConnected(  gConnectionTrackerSlotObserver,  gConnectionTrackerCallBack );
  }
  size_t size = connect.GetConnectionCount();
  DALI_CHECK_FAIL_CB(size == NoConnection, "GetConnectionCount api failed", CbConnectionTrackerReset, NULL);

  connect.DisconnectAll();
  ConnectionTrackerReset();

  DaliLog::PrintPass();
}

void ConnectionTrackerSignalConnectedP()
{
  const int SIGNAL_COUNT_CONNECTED = 3;
  gConnectionTrackerSlotObserver = NULL;
  gConnectionTrackerCallBack = NULL;

  gConnectionTrackerSlotObserver = new ConnectionTrackerSlotObserver();
  DALI_CHECK_FAIL( !gConnectionTrackerSlotObserver , "Failed to create ConnectionTrackerSlotObserver handler.");

  gConnectionTrackerCallBack = new CallbackFunction( TestCallBackFunction::CallBack );
  DALI_CHECK_FAIL_CB( !gConnectionTrackerCallBack, "Failed to create CallbackFunction handler.", CbConnectionTrackerResetSlotObserver, NULL);

  ConnectionTracker connect;
  for( int nCountSignal = 0; nCountSignal < SIGNAL_COUNT_CONNECTED; nCountSignal++ )
  {
    connect.SignalConnected(  gConnectionTrackerSlotObserver,  gConnectionTrackerCallBack );
  }
  size_t size = connect.GetConnectionCount();
  DALI_CHECK_FAIL_CB(size == NoConnection, "SignalConnected api failed", CbConnectionTrackerReset, NULL);
  connect.DisconnectAll();
  ConnectionTrackerReset();

  DaliLog::PrintPass();
}

void ConnectionTrackerSignalDisconnectP()
{
  const int SIGNAL_COUNT_CONNECTED = 3;
  gConnectionTrackerSlotObserver = NULL;
  gConnectionTrackerCallBack = NULL;

  gConnectionTrackerSlotObserver = new ConnectionTrackerSlotObserver();
  DALI_CHECK_FAIL( !gConnectionTrackerSlotObserver , "Failed to create ConnectionTrackerSlotObserver handler.");

  gConnectionTrackerCallBack = new CallbackFunction( TestCallBackFunction::CallBack );
  DALI_CHECK_FAIL_CB( !gConnectionTrackerCallBack, "Failed to create CallbackFunction handler.", CbConnectionTrackerResetSlotObserver, NULL);

  ConnectionTracker connect;
  for( int nCountSignal = 0; nCountSignal < SIGNAL_COUNT_CONNECTED; nCountSignal++ )
  {
    connect.SignalConnected(  gConnectionTrackerSlotObserver,  gConnectionTrackerCallBack );
  }
  size_t size = connect.GetConnectionCount();
  DALI_CHECK_FAIL(size == NoConnection, "SignalConnected api failed and GetConnectionCount api returns zero.");

  try
  {
    connect.SignalDisconnected( gConnectionTrackerSlotObserver, gConnectionTrackerCallBack );
  }
  catch(DaliException& de)
  {
    LOG_E("SignalDisconnected with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  connect.DisconnectAll();
  ConnectionTrackerReset();

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliConnectionTrackerConstructorP
 * @since_tizen         2.4
 * @description         checks if default constructor works or not.
 */

int UtcDaliConnectionTrackerConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConnectionTracker_TestApp testApp(application, CONNECTION_TRACKER_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliConnectionTrackerInterfaceConstructorP
 * @since_tizen         2.4
 * @description         checks if default constructor works or not for ConnectionTrackerInterface.
 */

int UtcDaliConnectionTrackerInterfaceConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConnectionTracker_TestApp testApp(application, CONNECTION_TRACKER_INTERFACE_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliConnectionTrackerDisconnectAllP
 * @since_tizen         2.4
 * @description         Disconnect all the connection signal information.
 */

int UtcDaliConnectionTrackerDisconnectAllP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConnectionTracker_TestApp testApp(application, CONNECTION_TRACKER_DISCONNECT_ALL_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliConnectionTrackerDisconnectAllN
 * @since_tizen         2.4
 * @description         Negative Test for Disconnecting all the connection signal information.
 */

int UtcDaliConnectionTrackerDisconnectAllN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConnectionTracker_TestApp testApp(application, CONNECTION_TRACKER_DISCONNECT_ALL_N );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliConnectionTrackerGetConnectionCountP
 * @since_tizen         2.4
 * @description
 */

int UtcDaliConnectionTrackerGetConnectionCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConnectionTracker_TestApp testApp(application, CONNECTION_TRACKER_GET_CONNECTION_COUNT_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliConnectionTrackerSignalConnectedP
 * @since_tizen         2.4
 * @description
 */

int UtcDaliConnectionTrackerSignalConnectedP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConnectionTracker_TestApp testApp(application, CONNECTION_TRACKER_SIGNAL_CONNECTED_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliConnectionTrackerSignalDisconnectP
 * @since_tizen         2.4
 * @description
 */

int UtcDaliConnectionTrackerSignalDisconnectP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConnectionTracker_TestApp testApp(application, CONNECTION_TRACKER_SIGNAL_DISCONNECTED_P );
  application.MainLoop();
  return test_return_value;
}
