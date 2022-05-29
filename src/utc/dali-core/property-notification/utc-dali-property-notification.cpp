#include "utc-dali-property-notification-impl.h"


extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_PropertyNotification_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_PropertyNotification_startup(void)
{
  test_return_value = 0;
  gRenderCountPropertyNotification=TC_PASS;
}

/**
 * @function            utc_Dali_PropertyNotification_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_PropertyNotification_cleanup(void)
{

}


namespace
{
  enum TEST_CASES_LIST_PROPERTY_NOTIFICATION
  {
    PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_ON_CHANGED_P,
    PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_ON_TRUE_P,
    PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_ON_FALSE_P,
    PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_DISABLED_P,
    PROPERTY_NOTIFICATION_GET_CONDITION_P,
    PROPERTY_NOTIFICATION_GET_CONDITION_CONST_P,
    PROPERTY_NOTIFICATION_GET_TARGET_P,
    PROPERTY_NOTIFICATION_GET_TARGET_PROPERTY_P,
    PROPERTY_NOTIFICATION_GET_NOTIFY_RESULT_P,
    PROPERTY_NOTIFICATION_DOWNCAST_P,
    PROPERTY_NOTIFICATION_DOWNCAST_N,
    PROPERTY_NOTIFICATION_CONSTRUCTOR_P,
    PROPERTY_NOTIFICATION_COPYCONSTRUCTOR_P,
    PROPERTY_NOTIFICATION_OPERATORASSIGNMENT_P
  };

  struct Property_Notification_TestApp : public ConnectionTracker
  {
    Property_Notification_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Property_Notification_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Property_Notification_TestApp::Tick );
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
        case PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_ON_CHANGED_P:
          PropertyNotificationSetGetNotifyModeONChangedP();
          break;

        case PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_ON_TRUE_P:
          PropertyNotificationSetGetNotifyModeONTrueP();
          break;

        case PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_ON_FALSE_P:
          PropertyNotificationSetGetNotifyModeONFalseP();
          break;

        case PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_DISABLED_P:
          PropertyNotificationSetGetNotifyModeDisabledP();
          break;

        case PROPERTY_NOTIFICATION_GET_CONDITION_P:
          PropertyNotificationGetConditionP();
          break;

        case PROPERTY_NOTIFICATION_GET_CONDITION_CONST_P:
          PropertyNotificationGetConditionConstP();
          break;

        case PROPERTY_NOTIFICATION_GET_TARGET_P:
          PropertyNotificationGetTargetP();
          break;

        case PROPERTY_NOTIFICATION_GET_TARGET_PROPERTY_P:
          PropertyNotificationGetTargetPropertyP();
          break;

        case PROPERTY_NOTIFICATION_GET_NOTIFY_RESULT_P:
          PropertyNotificationGetNotifyResultP();
          break;

        case PROPERTY_NOTIFICATION_DOWNCAST_P:
          PropertyNotificationDownCastP();
          break;

        case PROPERTY_NOTIFICATION_DOWNCAST_N:
          PropertyNotificationDownCastN();
          break;

        case PROPERTY_NOTIFICATION_CONSTRUCTOR_P:
          PropertyNotificationConstructorP();
          break;

        case PROPERTY_NOTIFICATION_COPYCONSTRUCTOR_P:
          PropertyNotificationCopyConstructorP();
          break;

        case PROPERTY_NOTIFICATION_OPERATORASSIGNMENT_P:
          PropertyNotificationOperatorAssignmentP();
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_ON_CHANGED_P:
          switch (gRenderCountPropertyNotification)
          {
            case 0:
              VTPropertyNotificationSetGetNotifyModeONChanged001();
              gRenderCountPropertyNotification++;
              break;

            case 1:
              VTPropertyNotificationSetGetNotifyModeONChanged002();
              gRenderCountPropertyNotification++;
              break;

            case 2:
              VTPropertyNotificationSetGetNotifyModeONChanged003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_ON_TRUE_P:
          switch (gRenderCountPropertyNotification)
          {
            case 0:
              VTPropertyNotificationSetGetNotifyModeONTrue001();
              gRenderCountPropertyNotification++;
              break;

            case 1:
              VTPropertyNotificationSetGetNotifyModeONTrue002();
              gRenderCountPropertyNotification++;
              break;

            case 2:
              VTPropertyNotificationSetGetNotifyModeONTrue003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_ON_FALSE_P:
          switch (gRenderCountPropertyNotification)
          {
            case 0:
              VTPropertyNotificationSetGetNotifyModeONFalse001();
              gRenderCountPropertyNotification++;
              break;

            case 1:
              VTPropertyNotificationSetGetNotifyModeONFalse002();
              gRenderCountPropertyNotification++;
              break;

            case 2:
              VTPropertyNotificationSetGetNotifyModeONFalse003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_DISABLED_P:
          switch (gRenderCountPropertyNotification)
          {
            case 0:
              VTPropertyNotificationSetGetNotifyModeDisabled001();
              gRenderCountPropertyNotification++;
              break;

            case 1:
              VTPropertyNotificationSetGetNotifyModeDisabled002();
              gRenderCountPropertyNotification++;
              break;

            case 2:
              VTPropertyNotificationSetGetNotifyModeDisabled003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case PROPERTY_NOTIFICATION_GET_NOTIFY_RESULT_P:
          switch (gRenderCountPropertyNotification)
          {
            case 0:
              VTPropertyNotificationGetNotifyResult001();
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
 * @testcase            UtcDaliPropertyNotificationConstructorP
 * @since_tizen         2.4
 * @description         check for the default constructor
 */

int UtcDaliPropertyNotificationConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliPropertyNotificationCopyConstructorP
 * @since_tizen         2.4
 * @description         check for the copy constructor
 */

int UtcDaliPropertyNotificationCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_COPYCONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliPropertyNotificationOperatorAssignmentP
 * @since_tizen         2.4
 * @description         check for the assignment operator
 */

int UtcDaliPropertyNotificationOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_OPERATORASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

// Positive test case for a method
/**
 * @testcase            UtcDaliPropertyNotificationDownCastP
 * @since_tizen         2.4
 * @description         check for the DownCast
 */
int UtcDaliPropertyNotificationDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}


// Negative test case for a method
/**
 * @testcase            UtcDaliPropertyNotificationDownCastN
 * @since_tizen         2.4
 * @description         check for the DownCast
 */

int UtcDaliPropertyNotificationDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliPropertyNotificationGetConditionP
 * @since_tizen         2.4
 * @description         check for the DownCast
 */

int UtcDaliPropertyNotificationGetConditionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_GET_CONDITION_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliPropertyNotificationGetConditionConstP
 * @since_tizen         2.4
 * @description         Get the condition of this notification.
 */

int UtcDaliPropertyNotificationGetConditionConstP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_GET_CONDITION_CONST_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliPropertyNotificationGetTargetP
 * @since_tizen         2.4
 * @description         Get the target handle that this notification is observing.
 */

int UtcDaliPropertyNotificationGetTargetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_GET_TARGET_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliPropertyNotificationGetTargetPropertyP
 * @since_tizen         2.4
 * @description         Get the target handle that this notification is observing.
 */

int UtcDaliPropertyNotificationGetTargetPropertyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_GET_TARGET_PROPERTY_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliPropertyNotificationSetGetNotifyModeP
 * @since_tizen         2.4
 * @description         Sets NotifyOnChanged as Notification mode  and Get mode and also check whether signal has been notified.
 */

int UtcDaliPropertyNotificationSetGetNotifyModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_ON_CHANGED_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliPropertyNotificationSetGetNotifyModeP2
 * @since_tizen         2.4
 * @description         Sets NotifyOnTrue as Notification mode  and Get mode and also check whether signal has been notified.
 */

int UtcDaliPropertyNotificationSetGetNotifyModeP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_ON_TRUE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliPropertyNotificationSetGetNotifyModeP3
 * @since_tizen         2.4
 * @description         Sets NotifyOnFalse as Notification mode  and Get mode and also check whether signal has been notified.
 */

int UtcDaliPropertyNotificationSetGetNotifyModeP3(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_ON_FALSE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliPropertyNotificationSetGetNotifyModeP4
 * @since_tizen         2.4
 * @description         Sets Disabled as Notification mode  and Get mode and also check whether signal has been notified.
 */

int UtcDaliPropertyNotificationSetGetNotifyModeP4(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_SET_GET_NOTIFY_MODE_DISABLED_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliPropertyNotificationGetNotifyResultP
 * @since_tizen         2.4
 * @description         Gets the result of the last condition check that caused a signal emit.
 */

int UtcDaliPropertyNotificationGetNotifyResultP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Notification_TestApp testApp( application, PROPERTY_NOTIFICATION_GET_NOTIFY_RESULT_P);
  application.MainLoop();
  return test_return_value;
}
