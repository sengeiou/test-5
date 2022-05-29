#include "utc-dali-radio-button-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function             utc_Dali_RadioButton_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_RadioButton_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_RadioButton_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_RadioButton_cleanup(void)
{

}

void RadioButtonConstructorP();
void RadioButtonNewP();
void RadioButtonCopyConstructorP();
void RadioButtonOperatorAssignmentP();
void RadioButtonDownCastP();
void RadioButtonDownCastN();

namespace
{
  enum TEST_CASES_RADIO_BUTTON
  {
    RADIO_BUTTON_CONSTRUCTOR_P,
    RADIO_BUTTON_NEW_P,
    RADIO_BUTTON_COPY_CONSTRUCTOR_P,
    RADIO_BUTTON_OPERATOR_ASSIGNMENT_P,
    RADIO_BUTTON_DOWNCAST_P,
    RADIO_BUTTON_DOWNCAST_N
  };

  struct RadioButton_TestApp : public ConnectionTracker
  {
    RadioButton_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &RadioButton_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &RadioButton_TestApp::Tick );
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

        case RADIO_BUTTON_CONSTRUCTOR_P:
          RadioButtonConstructorP();
          break;
        case RADIO_BUTTON_NEW_P:
          RadioButtonNewP();
          break;
        case RADIO_BUTTON_COPY_CONSTRUCTOR_P:
          RadioButtonCopyConstructorP();
          break;
        case RADIO_BUTTON_OPERATOR_ASSIGNMENT_P:
          RadioButtonOperatorAssignmentP();
          break;
        case RADIO_BUTTON_DOWNCAST_P:
          RadioButtonDownCastP();
          break;
        case RADIO_BUTTON_DOWNCAST_N:
          RadioButtonDownCastN();
          break;
      }
    }
    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

} // unnamed namespace


void RadioButtonConstructorP()
{
  RadioButton button;
  DALI_CHECK_FAIL(button, "RadioButton default constructor is failed.");

  DaliLog::PrintPass();
}

void RadioButtonNewP()
{
  RadioButton button = RadioButton::New();
  DALI_CHECK_FAIL(!button, "RadioButton::New is failed without args.");

  RadioButton button1 = RadioButton::New("radio");
  DALI_CHECK_FAIL(!button1, "RadioButton::New is failed with args.");

  DaliLog::PrintPass();
}

void RadioButtonCopyConstructorP()
{
  RadioButton radioButton = RadioButton::New();
  DALI_CHECK_FAIL(!radioButton, "RadioButton::New() is failed" );

  RadioButton copyConstructorRadioButton(radioButton);
  DALI_CHECK_FAIL(radioButton != copyConstructorRadioButton,  "Copy Constructor do not work properly.");

  DaliLog::PrintPass();


}

void RadioButtonOperatorAssignmentP()
{
  RadioButton radioButton = RadioButton::New();
  DALI_CHECK_FAIL(!radioButton, "RadioButton::New() is failed" );

  RadioButton* pOperatorRadioButton = &radioButton;

  DALI_CHECK_FAIL(pOperatorRadioButton==NULL,  "RadioButton Assignment is Failed .");

  DaliLog::PrintPass();
}

void RadioButtonDownCastP()
{
  RadioButton radioButton = RadioButton::New();
  DALI_CHECK_FAIL(!radioButton, "RadioButton::New() is failed" );

  BaseHandle handleRadioButton;
  handleRadioButton = radioButton;

  RadioButton downCastRadioButton = RadioButton::DownCast(handleRadioButton);
  DALI_CHECK_FAIL(!downCastRadioButton, "RadioButton DownCast is failed" );

  DALI_CHECK_FAIL(radioButton != downCastRadioButton, "downCastRadioButton is failed to match with radioButton" );

  DaliLog::PrintPass();

}

void RadioButtonDownCastN()
{
  BaseHandle unInitializedObject;

  RadioButton radioButton1 = RadioButton::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(radioButton1, "RadioButton handle is not empty." );

  RadioButton radioButton2 = DownCast< RadioButton >( unInitializedObject );
  DALI_CHECK_FAIL(radioButton2, "RadioButton handle is not empty." );

  DaliLog::PrintPass();
}

/**
 * @testcase       UtcDaliRadioButtonConstructorP
 * @since_tizen    2.4
 * @description    Checks correct creation of an object
 */

int UtcDaliRadioButtonConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  RadioButton_TestApp testApp( application, RADIO_BUTTON_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase       UtcDaliRadioButtonNewP
 * @since_tizen    2.4
 * @description    Checks correct allocation of memory to object
 */

int UtcDaliRadioButtonNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  RadioButton_TestApp testApp( application, RADIO_BUTTON_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase       UtcDaliRadioButtonCopyConstructorP
 * @since_tizen    2.4
 * @description    Checks correct creation of a copy of object
 */

int UtcDaliRadioButtonCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  RadioButton_TestApp testApp( application, RADIO_BUTTON_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase       UtcDaliRadioButtonOperatorAssignmentP
 * @since_tizen    2.4
 * @description    Checks correct assigntment of one object to other object
 */

int UtcDaliRadioButtonOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  RadioButton_TestApp testApp( application, RADIO_BUTTON_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase       UtcDaliRadioButtonDowncastP
 * @since_tizen    2.4
 * @description    Checks for correct downcasting of Base Handle
 */

int UtcDaliRadioButtonDowncastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  RadioButton_TestApp testApp( application, RADIO_BUTTON_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase       UtcDaliRadioButtonDowncastN
 * @since_tizen    2.4
 * @description    Negative test for checking downcasting of Base Handle
 */

int UtcDaliRadioButtonDowncastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  RadioButton_TestApp testApp( application, RADIO_BUTTON_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}
