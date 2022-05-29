
#include "dali-common.h"

using namespace std;
using namespace Dali;

#define SUITE_NAME "EVENTS_UTC"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

void UtcDaliKeyEventAssignment(void);
void UtcDaliKeyEventCopy(void);
void UtcDaliKeyEventGetCompose(void);


void utc_Dali_Events_startup(void)
{
  test_return_value = 0;
}

void utc_Dali_Events_cleanup(void)
{

}

namespace
{
  enum TEST_CASES_LIST_EVENTS
  {
    EVENTS_ASSIGNMENT_P,
    EVENTS_COPY_P,
    GET_COMPOSE_P
  };

  struct Events_TestApp : public ConnectionTracker
  {
    Events_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Events_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Events_TestApp::Tick );
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
        case EVENTS_ASSIGNMENT_P:
          UtcDaliKeyEventAssignment();
          break;

        case EVENTS_COPY_P:
          UtcDaliKeyEventCopy();
          break;

        case GET_COMPOSE_P:
          UtcDaliKeyEventGetCompose();
          break;
      }
    }


    void VerdictTest()
    {
      switch (mTestCase)
      {
        case EVENTS_ASSIGNMENT_P:
          break;

        case EVENTS_COPY_P:
          break;

        case GET_COMPOSE_P:
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


#include <iostream>
#include <stdlib.h>
#include <dali/public-api/dali-core.h>

// Key Event Test references
const static int SHIFT_MODIFIER  = 0x1;
const static int CTRL_MODIFIER  = 0x2;
const static int ALT_MODIFIER  = 0x4;

const static char* TEST_STRING_1 = "alpha";

void UtcDaliKeyEventAssignment(void)
{
  // Test Assignment operator
  KeyEvent event(TEST_STRING_1,"i", 99, SHIFT_MODIFIER, 0, KeyEvent::Down);  // set name to test, key string to i and modifier to shift

  DALI_CHECK_FAIL(strcmp(TEST_STRING_1, event.keyPressedName.c_str()), "keyPressedName error!"); // check key name
  DALI_CHECK_FAIL(strcmp("i", event.keyPressed.c_str()), "keyPressed error!"); // check key string
  DALI_CHECK_FAIL(99 != event.keyCode, "keyCode is different"); // check keyCode
  DALI_CHECK_FAIL(SHIFT_MODIFIER != event.keyModifier, "keyModifier error!"); // check modifier
  DALI_CHECK_FAIL(KeyEvent::Down != event.state, "event.state error!"); // check state

  KeyEvent event2(TEST_STRING_1,"j", 88, CTRL_MODIFIER, 0, KeyEvent::Up);  // set name to test, key string to i and modifier to shift

  DALI_CHECK_FAIL(strcmp(TEST_STRING_1, event2.keyPressedName.c_str()), "keyPressedName error!"); // check key name
  DALI_CHECK_FAIL(strcmp("j", event2.keyPressed.c_str()), "keyPressed error!"); // check key string
  DALI_CHECK_FAIL(88 != event2.keyCode, "keyCode is different"); // check keyCode
  DALI_CHECK_FAIL(CTRL_MODIFIER != event2.keyModifier, "keyModifier error!"); // check modifier
  DALI_CHECK_FAIL(KeyEvent::Up != event2.state, "event.state error!"); // check state

  event = event2;

  DALI_CHECK_FAIL(strcmp(TEST_STRING_1, event.keyPressedName.c_str()), "keyPressedName error!"); // check key name
  DALI_CHECK_FAIL(strcmp("j", event.keyPressed.c_str()), "keyPressed error!"); // check key string
  DALI_CHECK_FAIL(88 != event.keyCode, "keyCode is different"); // check keyCode
  DALI_CHECK_FAIL(CTRL_MODIFIER != event.keyModifier, "keyModifier error!"); // check modifier
  DALI_CHECK_FAIL(KeyEvent::Up != event.state, "event.state error!"); // check state

  DaliLog::PrintPass();
}

void UtcDaliKeyEventCopy(void)
{
  // Test Assignment operator
  KeyEvent event(TEST_STRING_1,"i", 99, SHIFT_MODIFIER, 0, KeyEvent::Down);  // set name to test, key string to i and modifier to shift

  DALI_CHECK_FAIL(strcmp(TEST_STRING_1, event.keyPressedName.c_str()), "keyPressedName error!"); // check key name
  DALI_CHECK_FAIL(strcmp("i", event.keyPressed.c_str()), "keyPressed error!"); // check key string
  DALI_CHECK_FAIL(99 != event.keyCode, "keyCode is different"); // check keyCode
  DALI_CHECK_FAIL(SHIFT_MODIFIER != event.keyModifier, "keyModifier error!"); // check modifier
  DALI_CHECK_FAIL(KeyEvent::Down != event.state, "event.state error!"); // check state

  KeyEvent event2( event );

  DALI_CHECK_FAIL(strcmp(TEST_STRING_1, event2.keyPressedName.c_str()), "keyPressedName error!"); // check key name
  DALI_CHECK_FAIL(strcmp("i", event2.keyPressed.c_str()), "keyPressed error!"); // check key string
  DALI_CHECK_FAIL(99 != event2.keyCode, "keyCode is different"); // check keyCode
  DALI_CHECK_FAIL(SHIFT_MODIFIER != event2.keyModifier, "keyModifier error!"); // check modifier
  DALI_CHECK_FAIL(KeyEvent::Down != event2.state, "event.state error!"); // check state

  DaliLog::PrintPass();
}

void UtcDaliKeyEventGetCompose(void)
{
  KeyEvent event(TEST_STRING_1,"i", 99, SHIFT_MODIFIER, 0lu, KeyEvent::Down);

  DALI_CHECK_FAIL( strcmp(event.GetCompose().c_str(), ""), "GetCompse() is failed.");

  DaliLog::PrintPass();
}

int UtcDaliKeyEventAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Events_TestApp testApp(application, EVENTS_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

int UtcDaliKeyEventCopyP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Events_TestApp testApp(application, EVENTS_COPY_P );
  application.MainLoop();

  return test_return_value;
}

int UtcDaliKeyEventGetComposeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv);
  CHECK_GL;
  Events_TestApp testApp(application, GET_COMPOSE_P );
  application.MainLoop();

  return test_return_value;
}

