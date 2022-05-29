#include "utc-dali-push-button-common.h"

//& set: PushButton
extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_PushButton_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_PushButton_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_PushButton_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_PushButton_cleanup(void)
{

}

void PushButtonConstructorP();
void PushButtonCopyConstructorP();
void PushButtonNewP();
void PushButtonOperatorAssignmentP();
void PushButtonDowncastP();
void PushButtonDowncastN();
void PushButtonSetGetInitialAutoRepeatingDelayP();
void PushButtonSetIsAutoRepeatingP();
void PushButtonSetGetNextAutoRepeatingDelayP();




namespace
{
  enum TEST_CASES_LIST_PUSH_BUTTON
  {
    PUSH_BUTTON_CONSTRUCTOR_P,
    PUSH_BUTTON_COPY_CONSTRUCTOR_P,
    PUSH_BUTTON_NEW_P,
    PUSH_BUTTON_OPERATOR_ASSIGNMENT_P,
    PUSH_BUTTON_DOWNCAST_P,
    PUSH_BUTTON_DOWNCAST_N,
    PUSH_BUTTON_SET_GET_INITIAL_AUTO_REPEATING_DELAY_P,
    PUSH_BUTTON_SET_IS_AUTO_REPEATING_P,
    PUSH_BUTTON_SET_GET_NEXT_AUTO_REPEATING_DELAY_P
  };

  struct PushButton_TestApp : public ConnectionTracker
  {
    PushButton_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &PushButton_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &PushButton_TestApp::Tick );
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
        case PUSH_BUTTON_CONSTRUCTOR_P:
          PushButtonConstructorP();
          break;

        case PUSH_BUTTON_COPY_CONSTRUCTOR_P:
          PushButtonCopyConstructorP();
          break;

        case PUSH_BUTTON_NEW_P:
          PushButtonNewP();
          break;

        case PUSH_BUTTON_OPERATOR_ASSIGNMENT_P:
          PushButtonOperatorAssignmentP();
          break;

        case PUSH_BUTTON_DOWNCAST_N:
          PushButtonDowncastN();
          break;

        case PUSH_BUTTON_DOWNCAST_P:
          PushButtonDowncastP();
          break;

        case PUSH_BUTTON_SET_GET_INITIAL_AUTO_REPEATING_DELAY_P:
          PushButtonSetGetInitialAutoRepeatingDelayP();
          break;

        case PUSH_BUTTON_SET_IS_AUTO_REPEATING_P:
          PushButtonSetIsAutoRepeatingP();
          break;

        case PUSH_BUTTON_SET_GET_NEXT_AUTO_REPEATING_DELAY_P:
          PushButtonSetGetNextAutoRepeatingDelayP();
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


void PushButtonConstructorP()
{
  PushButton pushButton;
  DALI_CHECK_FAIL(pushButton,  "pushButton Default Contructor is failed.");

  DaliLog::PrintPass();
}

void PushButtonNewP()
{
  PushButton pushButton = PushButton::New();
  DALI_CHECK_FAIL(!pushButton,  "PushButton::New() is failed .");

  DaliLog::PrintPass();
}

void PushButtonCopyConstructorP()
{
  bool bBorder = false;
  const unsigned int unBorderSize = 1u;
  Image imgset;
  DALI_CHECK_FAIL(!PushButtonCreateImage(imgset),  "PushButtonCreateImage is failed .");

  Actor imageActor = ImageView::New(imgset);
  DALI_CHECK_FAIL(!imageActor,  "ImageView::New() is failed .");

  PushButton pushButton = PushButton::New();

  DALI_CHECK_FAIL(!pushButton,  "PushButton::New() is failed .");

  PushButton copyconstPushButton(pushButton);
  DALI_CHECK_FAIL(pushButton != copyconstPushButton,  "Copy Constructor do not work properly.");

  DaliLog::PrintPass();
}

void PushButtonOperatorAssignmentP()
{
  PushButton pushButton = PushButton::New();

  DALI_CHECK_FAIL(!pushButton,  "PushButton::New() is failed .");

  PushButton* pOperatorPushButton =&pushButton;

  DALI_CHECK_FAIL(pOperatorPushButton==NULL,  "PushButton Assignment is Failed .");

  DaliLog::PrintPass();
}


void PushButtonDowncastP()
{
  PushButton pushButton = PushButton::New();

  DALI_CHECK_FAIL(!pushButton,  "PushButton::New() is failed .");

  BaseHandle handlePushButton;
  handlePushButton = pushButton;

  PushButton downCastPushButton = PushButton::DownCast( handlePushButton );

  DALI_CHECK_FAIL(!downCastPushButton,  "downCastPushButton is not valid object  .");
  DALI_CHECK_FAIL(pushButton != downCastPushButton,  "downCastPushButton is failed to match with pushButton  .");

  DaliLog::PrintPass();
}

void PushButtonDowncastN()
{
  BaseHandle unInitializedObject;

  PushButton downCastPushButton = PushButton::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(downCastPushButton, "PushButton handle is not empty." );

  PushButton downCastPushButton2 = DownCast< PushButton >( unInitializedObject );
  DALI_CHECK_FAIL(downCastPushButton2, "PushButton handle is not empty." );

  DaliLog::PrintPass();
}

void PushButtonSetGetInitialAutoRepeatingDelayP()
{
  float fSetAutoRepeat = 1.15f;
  float fGetInitRepeatTime = 0.0f ;
  bool bIsRepeating = true   ;

  PushButton pushButton = PushButton::New();

  DALI_CHECK_FAIL(!pushButton,  "PushButton::New() is failed .");

  pushButton.SetProperty( Button::Property::AUTO_REPEATING, bIsRepeating );

	pushButton.SetProperty( Button::Property::INITIAL_AUTO_REPEATING_DELAY, fSetAutoRepeat );
	
	fGetInitRepeatTime = pushButton.GetProperty<float>( Button::Property::INITIAL_AUTO_REPEATING_DELAY );
	
  DALI_CHECK_FAIL( fGetInitRepeatTime != fSetAutoRepeat, "Button::Property::INITIAL_AUTO_REPEATING_DELAY is not match properly .");

  DaliLog::PrintPass();
}

void PushButtonSetIsAutoRepeatingP()
{
  bool bAutoRepeatCheck = false ;
  bool bIsAutoRepeat = true;

  PushButton pushButton = PushButton::New();

  DALI_CHECK_FAIL(!pushButton,  "PushButton::New() is failed .");

  pushButton.SetProperty( Button::Property::AUTO_REPEATING, bIsAutoRepeat );

  bAutoRepeatCheck = pushButton.GetProperty<bool>( Button::Property::AUTO_REPEATING );

  DALI_CHECK_FAIL( !bAutoRepeatCheck,  "Button::Property::AUTO_REPEATING is not working properly" );

  DaliLog::PrintPass();
}


void PushButtonSetGetNextAutoRepeatingDelayP()
{
  float fSetNextAutoRepeat = 1.15f;
  float fGetNextRepeatTime = 0.0f;
  bool bIsRepeating = true   ;

  PushButton pushButton = PushButton::New();

  DALI_CHECK_FAIL(!pushButton,  "PushButton::New() is failed .");

  pushButton.SetProperty( Button::Property::AUTO_REPEATING, bIsRepeating );

	DALI_CHECK_FAIL( !pushButton.GetProperty<bool>( Button::Property::AUTO_REPEATING ), "Button::Property::AUTO_REPEATING is failed." );

	pushButton.SetProperty( Button::Property::NEXT_AUTO_REPEATING_DELAY, fSetNextAutoRepeat );

	fGetNextRepeatTime = pushButton.GetProperty<float>( Button::Property::NEXT_AUTO_REPEATING_DELAY );

  DALI_CHECK_FAIL( fGetNextRepeatTime != fSetNextAutoRepeat, "Button::Property::NEXT_AUTO_REPEATING_DELAY is not match properly.");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliPushButtonConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */


int UtcDaliPushButtonConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  PushButton_TestApp testApp( application, PUSH_BUTTON_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliPushButtonCopyConstructorP
 * @since_tizen         2.4
 * @description         Copy constructor to PushButton.
 */


int UtcDaliPushButtonCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  PushButton_TestApp testApp( application, PUSH_BUTTON_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliPushButtonNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliPushButtonNewP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  PushButton_TestApp testApp( application, PUSH_BUTTON_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliPushButtonOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Assignment operator.Changes this handle to point to another real object.
 */

int UtcDaliPushButtonOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  PushButton_TestApp testApp( application, PUSH_BUTTON_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliPushButtonDowncastP
 * @since_tizen         2.4
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliPushButtonDowncastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  PushButton_TestApp testApp( application, PUSH_BUTTON_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliPushButtonDowncastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliPushButtonDowncastN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  PushButton_TestApp testApp( application, PUSH_BUTTON_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliPushButtonSetGetInitialAutoRepeatingDelayP
 * @since_tizen         2.4
 * @description         Sets the initial autorepeating delay..
 */

int UtcDaliPushButtonSetGetInitialAutoRepeatingDelayP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  PushButton_TestApp testApp( application, PUSH_BUTTON_SET_GET_INITIAL_AUTO_REPEATING_DELAY_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliPushButtonSetIsAutoRepeatingP
 * @since_tizen         2.4
 * @description         Sets the autorepeating property. .
 */

int UtcDaliPushButtonSetIsAutoRepeatingP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  PushButton_TestApp testApp( application, PUSH_BUTTON_SET_IS_AUTO_REPEATING_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliPushButtonSetGetNextAutoRepeatingDelayP
 * @since_tizen         2.4
 * @description         Sets and Gets the Next autorepeating delay.
 */

int UtcDaliPushButtonSetGetNextAutoRepeatingDelayP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  PushButton_TestApp testApp( application, PUSH_BUTTON_SET_GET_NEXT_AUTO_REPEATING_DELAY_P );
  application.MainLoop();

  return test_return_value;
}

