#include "utc-dali-check-box-button-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_CheckBoxButton_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_CheckBoxButton_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_CheckBoxButton_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_CheckBoxButton_cleanup(void)
{

}

void CheckBoxButtonConstructorP();
void CheckBoxButtonNewP();
void CheckBoxButtonCopyConstructorP();
void CheckBoxButtonOperatorAssignmentP();
void CheckBoxButtonDownCastP();
void CheckBoxButtonDownCastN();

namespace
{
  enum TEST_CASES_LIST_CHECK_BOX_BUTTON
  {
    CHECK_BOX_BUTTON_CONSTRUCTOR_P,
    CHECK_BOX_BUTTON_NEW_P,
    CHECK_BOX_BUTTON_COPY_CONSTRUCTOR_P,
    CHECK_BOX_BUTTON_OPERATOR_ASSIGNMENT_P,
    CHECK_BOX_BUTTON_DOWNCAST_P,
    CHECK_BOX_BUTTON_DOWNCAST_N
  };

  struct CheckBoxButton_TestApp : public ConnectionTracker
  {
    CheckBoxButton_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &CheckBoxButton_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &CheckBoxButton_TestApp::Tick );
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
        case CHECK_BOX_BUTTON_CONSTRUCTOR_P:
          CheckBoxButtonConstructorP();
          break;
        case CHECK_BOX_BUTTON_NEW_P:
          CheckBoxButtonNewP();
          break;
        case CHECK_BOX_BUTTON_COPY_CONSTRUCTOR_P:
          CheckBoxButtonCopyConstructorP();
          break;
        case CHECK_BOX_BUTTON_OPERATOR_ASSIGNMENT_P:
          CheckBoxButtonOperatorAssignmentP();
          break;
        case CHECK_BOX_BUTTON_DOWNCAST_P:
          CheckBoxButtonDownCastP();
          break;
        case CHECK_BOX_BUTTON_DOWNCAST_N:
          CheckBoxButtonDownCastN();
          break;
      }
    }

    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

} // unnamed namespace


void CheckBoxButtonConstructorP()
{
  CheckBoxButton checkBoxButton;
  DALI_CHECK_FAIL(checkBoxButton, "CheckBoxButton default constructor is failed.");

  DaliLog::PrintPass();
}

void CheckBoxButtonNewP()
{
  CheckBoxButton checkBoxButton = CheckBoxButton::New( );
  DALI_CHECK_INSTANCE(checkBoxButton, "CheckBoxButton::New() is failed.");

  DaliLog::PrintPass();
}

void CheckBoxButtonCopyConstructorP()
{
  CheckBoxButton checkBox = CheckBoxButton::New();
  CheckBoxButton copy( checkBox );
  DALI_CHECK_INSTANCE(copy, "CheckBoxButton::CheckBoxButton(const CheckBoxButton&) is failed.");

  DaliLog::PrintPass();
}

void CheckBoxButtonOperatorAssignmentP()
{
  CheckBoxButton checkBox = CheckBoxButton::New();

  CheckBoxButton copy = checkBox;
  DALI_CHECK_INSTANCE(copy, "CheckBoxButton::CheckBoxButton(const CheckBoxButton&) is failed.");
  DALI_CHECK_FAIL(checkBox != copy, "CheckBoxButton::CheckBoxButton(const CheckBoxButton&) is failed.");

  DaliLog::PrintPass();
}

void CheckBoxButtonDownCastP()
{
  CheckBoxButton checkBox = CheckBoxButton::New();
  BaseHandle object(checkBox);
  CheckBoxButton checkBox2 = CheckBoxButton::DownCast( object );
  DALI_CHECK_INSTANCE(checkBox2, "CheckBoxButton::DownCast is failed." );

  CheckBoxButton checkBox3 = DownCast< CheckBoxButton >(object);
  DALI_CHECK_INSTANCE(checkBox3, "CheckBoxButton::DownCast is failed." );

  DaliLog::PrintPass();
}

void CheckBoxButtonDownCastN()
{
  BaseHandle unInitializedObject;

  CheckBoxButton checkBox1 = CheckBoxButton::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(checkBox1, "CheckBoxButton handle is not empty." );

  CheckBoxButton checkBox2 = DownCast< CheckBoxButton >( unInitializedObject );
  DALI_CHECK_FAIL(checkBox2, "CheckBoxButton handle is not empty." );

  DaliLog::PrintPass();
}

/**
 * @testcase            UtcDaliCheckboxButtonConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliCheckboxButtonConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CheckBoxButton_TestApp testApp( application, CHECK_BOX_BUTTON_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCheckboxButtonNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliCheckboxButtonNewP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CheckBoxButton_TestApp testApp( application, CHECK_BOX_BUTTON_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCheckboxButtonCopyConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of a copy of object
 */

int UtcDaliCheckboxButtonCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CheckBoxButton_TestApp testApp( application, CHECK_BOX_BUTTON_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCheckboxButtonOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Checks correct assigntment of one object to other object
 */

int UtcDaliCheckboxButtonOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CheckBoxButton_TestApp testApp( application, CHECK_BOX_BUTTON_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCheckboxButtonDowncastP
 * @since_tizen         2.4
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliCheckboxButtonDowncastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CheckBoxButton_TestApp testApp( application, CHECK_BOX_BUTTON_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCheckboxButtonDowncastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliCheckboxButtonDowncastN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CheckBoxButton_TestApp testApp( application, CHECK_BOX_BUTTON_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}
