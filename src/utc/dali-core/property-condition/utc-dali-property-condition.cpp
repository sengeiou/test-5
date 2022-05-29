#include "utc-dali-property-condition-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;
int gRenderCountPC;

/**
 * @function            utc_Dali_PropertyCondition_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_PropertyCondition_startup(void)
{
  test_return_value=0;
  gRenderCountPC=0;
}

/**
 * @function            utc_Dali_PropertyCondition_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_PropertyCondition_cleanup(void)
{

}

Actor gActorPC;        /**Actor instance*/
float gStep = 0.0f;    /** Common float step/variable step value*/
bool gPropertyConditionNotifyCallback = false;    /**Status for notification signal callback*/

void CbPropertyConditionNotifySignalCallback(PropertyNotification& source)
{
  LOG_I("Notification callback is called.");
  gPropertyConditionNotifyCallback = true;
}



void PropertyConditionGreaterThanCondition();
void PropertyConditionInsideCondition();
void PropertyConditionOperatorAssignment();
void PropertyConditionConstructor();
void PropertyConditionCopyConstructor();
void PropertyConditionLessThanCondition();
void PropertyConditionGetArguments();
void PropertyConditionGetArgumentsCount();

void PropertyConditionStepCondition();
void VTPropertyConditionStepCondition001();
void VTPropertyConditionStepCondition002();
void VTPropertyConditionStepCondition003();

void PropertyConditionVariableStepCondition();
void VTPropertyConditionVariableStepCondition001();

void PropertyConditionOutsideCondition();
void VTPropertyConditionOutsideCondition001();
void VTPropertyConditionOutsideCondition002();
void VTPropertyConditionOutsideCondition003();

namespace
{
  enum TEST_CASES_LIST_PROPERTY_CONDITION
  {
    PROPERTY_CONDITION_GREATER_THAN_CONDITION,
    PROPERTY_CONDITION_INSIDE_CONDITION,
    PROPERTY_CONDITION_ASSIGNMENT_OPERATOR,
    PROPERTY_CONDITION_CONSTRUCTOR,
    PROPERTY_CONDITION_COPYCONSTRUCTOR,
    PROPERTY_CONDITION_LESS_THAN_CONDITION,
    PROPERTY_CONDITION_GET_ARGUMENTS,
    PROPERTY_CONDITION_GET_ARGUMENTS_COUNT,
    PROPERTY_CONDITION_STEP_CONDITION,
    PROPERTY_CONDITION_VARIABLE_STEP_CONDITION,
    PROPERTY_CONDITION_OUTSIDE_CONDITION
  };

  struct Property_Condition_TestApp : public ConnectionTracker
  {
    Property_Condition_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Property_Condition_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Property_Condition_TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      if(test_return_value == TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
        return true;
      }

      VerdictTest();

      if(test_return_value == TC_FAIL)
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
        case PROPERTY_CONDITION_GREATER_THAN_CONDITION:
          PropertyConditionGreaterThanCondition();
          break;

        case PROPERTY_CONDITION_INSIDE_CONDITION:
          PropertyConditionInsideCondition();
          break;

        case PROPERTY_CONDITION_ASSIGNMENT_OPERATOR:
          PropertyConditionOperatorAssignment();
          break;

        case PROPERTY_CONDITION_CONSTRUCTOR:
          PropertyConditionConstructor();
          break;

        case PROPERTY_CONDITION_COPYCONSTRUCTOR:
          PropertyConditionCopyConstructor();
          break;

        case PROPERTY_CONDITION_LESS_THAN_CONDITION:
          PropertyConditionLessThanCondition();
          break;

        case PROPERTY_CONDITION_GET_ARGUMENTS:
          PropertyConditionGetArguments();
          break;

        case PROPERTY_CONDITION_GET_ARGUMENTS_COUNT:
          PropertyConditionGetArgumentsCount();
          break;

        case PROPERTY_CONDITION_STEP_CONDITION:
          PropertyConditionStepCondition();
          break;

        case PROPERTY_CONDITION_VARIABLE_STEP_CONDITION:
          PropertyConditionVariableStepCondition();
          break;

        case PROPERTY_CONDITION_OUTSIDE_CONDITION:
          PropertyConditionOutsideCondition();
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case PROPERTY_CONDITION_STEP_CONDITION:
          switch(gRenderCountPC)
          {
            case 0:
              VTPropertyConditionStepCondition001();
              gRenderCountPC++;
              break;

            case 1:
              VTPropertyConditionStepCondition002();
              gRenderCountPC++;
              break;

            case 2:
              VTPropertyConditionStepCondition003();
              mTimer.Stop();
              mApplication.Quit();
              break;

          }
          break;

        case PROPERTY_CONDITION_VARIABLE_STEP_CONDITION:
          VTPropertyConditionVariableStepCondition001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case PROPERTY_CONDITION_OUTSIDE_CONDITION:
          switch(gRenderCountPC)
          {
            case 0:
              VTPropertyConditionOutsideCondition001();
              gRenderCountPC++;
              break;

            case 1:
              VTPropertyConditionOutsideCondition002();
              gRenderCountPC++;
              break;

            case 2:
              VTPropertyConditionOutsideCondition003();
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
 * ##############################
 * TC Logic Implementation Area.
 * ##############################
 **/
void PropertyConditionGreaterThanCondition()
{
  Actor actor;
  float fCondition = 100.0f ;

  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created " );
  Stage::GetCurrent().Add(actor);

  PropertyCondition condition = GreaterThanCondition(fCondition);
  PropertyNotification notification = actor.AddPropertyNotification(Actor::Property::POSITION_X, condition);
  DALI_CHECK_FAIL( condition != notification.GetCondition() , "GreaterThanCondition() is failed to set condition value " );

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}
void PropertyConditionInsideCondition()
{
  Actor actor;
  float fConditionArgumentOne = 125.0f , fConditionArgumentTwo = 250.0f;

  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created " );

  Stage::GetCurrent().Add(actor);

  PropertyCondition condition = InsideCondition( fConditionArgumentOne , fConditionArgumentTwo );
  DALI_CHECK_FAIL( !condition, "InsideCondition() is failed create a PropertyCondition instance." );

  PropertyNotification notification = actor.AddPropertyNotification(Actor::Property::POSITION_X, condition);
  PropertyCondition conditionGet = notification.GetCondition();

  DALI_CHECK_FAIL( conditionGet.GetArgument( ARGUMENT_INDEX_ZERO ) != fConditionArgumentOne , "InsideCondition() is failed to set first argument of condition value " );
  DALI_CHECK_FAIL( conditionGet.GetArgument( ARGUMENT_INDEX_ONE ) != fConditionArgumentTwo , "InsideCondition() is failed to set second argument of condition value " );

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}
void PropertyConditionOperatorAssignment()
{
  Actor actor;
  float fCondition = 100.0f ;

  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created " );
  Stage::GetCurrent().Add(actor);

  PropertyCondition condition = GreaterThanCondition(fCondition);
  PropertyCondition OperatorPropertyCondition = condition;
  PropertyNotification notification = actor.AddPropertyNotification(Actor::Property::POSITION_X, OperatorPropertyCondition);
  DALI_CHECK_FAIL( OperatorPropertyCondition != notification.GetCondition() , "PropertyCondition Assignment is Failed" );

  OperatorPropertyCondition.Reset() ;
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}
void PropertyConditionConstructor()
{
  Actor actor;
  float fCondition = 100.0f ;

  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created " );

  Stage::GetCurrent().Add(actor);

  PropertyCondition condition = GreaterThanCondition(fCondition);
  PropertyCondition constructor(condition);
  PropertyNotification notification = actor.AddPropertyNotification(Actor::Property::POSITION_X, constructor);
  DALI_CHECK_FAIL( constructor != notification.GetCondition() , "PropertyCondition constructor is Failed" );

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}
void PropertyConditionCopyConstructor()
{
  Actor actor;
  float fCondition = 100.0f ;

  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created " );

  Stage::GetCurrent().Add(actor);

  PropertyCondition condition = GreaterThanCondition(fCondition);
  PropertyCondition constructor(condition);
  PropertyNotification notification = actor.AddPropertyNotification(Actor::Property::POSITION_X, constructor);
  DALI_CHECK_FAIL( constructor != notification.GetCondition() , "PropertyCondition constructor is Failed" );

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}
void PropertyConditionLessThanCondition()
{
  Actor actor;
  float fCondition = 100.0f ;
  actor = Actor::New();

  DALI_CHECK_FAIL(!actor, "actor is not created " );

  Stage::GetCurrent().Add(actor);

  PropertyCondition condition = LessThanCondition(fCondition);
  PropertyNotification notification = actor.AddPropertyNotification(Actor::Property::POSITION_X, condition);
  DALI_CHECK_FAIL( condition != notification.GetCondition() , "LessThanCondition is Failed to set condition value " );

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}
void PropertyConditionGetArguments(void)
{
  Actor actor;
  float fConditionArgumentOne = 125.0f , fConditionArgumentTwo = 250.0f;
  float fArgumentGetOne = 0.0f, fArgumentGetTwo = 0.0f;

  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created " );

  Stage::GetCurrent().Add(actor);

  PropertyCondition condition = InsideCondition( fConditionArgumentOne , fConditionArgumentTwo );
  DALI_CHECK_FAIL(!condition, "PropertyCondition instance is empty" );

  PropertyNotification notification = actor.AddPropertyNotification(Actor::Property::POSITION_X, condition);
  PropertyCondition conditionGet = notification.GetCondition();

  fArgumentGetOne = conditionGet.GetArgument( ARGUMENT_INDEX_ZERO );
  fArgumentGetTwo = conditionGet.GetArgument( ARGUMENT_INDEX_ONE );

  DALI_CHECK_FAIL( fArgumentGetOne != fConditionArgumentOne , "GetArgument() is Failed to get first argument" );
  DALI_CHECK_FAIL( fArgumentGetTwo != fArgumentGetTwo , "GetArgument() is Failed to get second argument" );

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void PropertyConditionGetArgumentsCount(void)
{
  Actor actor;
  float fConditionArgumentOne = 125.0f , fConditionArgumentTwo = 250.0f;
  size_t argumentSize = 2, argumentSizeGet = 0;

  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "actor is not created " );

  Stage::GetCurrent().Add(actor);

  PropertyCondition condition = InsideCondition( fConditionArgumentOne , fConditionArgumentTwo );
  DALI_CHECK_FAIL(!condition, "PropertyCondition instance is empty" );

  PropertyNotification notification = actor.AddPropertyNotification(Actor::Property::POSITION_X, condition);
  PropertyCondition conditionGet = notification.GetCondition();

  argumentSizeGet = conditionGet.GetArgumentCount();
  DALI_CHECK_FAIL( argumentSizeGet != argumentSize, "GetArgumentCount() is failed" );

  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void PropertyConditionStepCondition()
{
  gActorPC = Actor::New();
  DALI_CHECK_FAIL(!gActorPC,  "Actor::New() is failed" );
  Stage::GetCurrent().Add(gActorPC);

  //Set fStep condition
  gStep = 100.0f;
  PropertyNotification step_notification = gActorPC.AddPropertyNotification( Actor::Property::POSITION, 0, StepCondition(gStep, 50.0f) );
  step_notification.NotifySignal().Connect( &CbPropertyConditionNotifySignalCallback );

  // set initial position
  gActorPC.SetPosition(Vector3::ZERO);
}
void VTPropertyConditionStepCondition001()
{
  // test both directions: Move x to positive position
  gPropertyConditionNotifyCallback = false;
  gActorPC.SetPosition(Vector3(gStep, 0.0f, 0.0f));
}
void VTPropertyConditionStepCondition002()
{
  DALI_CHECK_FAIL(!gPropertyConditionNotifyCallback,
      "StepCondition is failed; could not trigger notification signal for positive position." );
  // Move x to negative position
  gPropertyConditionNotifyCallback = false;
  gActorPC.SetPosition(Vector3(-gStep, 0.0f, 0.0f));
}
void VTPropertyConditionStepCondition003()
{
  DALI_CHECK_FAIL(!gPropertyConditionNotifyCallback,
      "StepCondition is failed; could not trigger notification signal for negative position." );
  Stage::GetCurrent().Remove(gActorPC);
  DaliLog::PrintPass();
}


void PropertyConditionVariableStepCondition()
{
  gActorPC = Actor::New();
  DALI_CHECK_FAIL(!gActorPC,  "Actor::New() is failed" );
  Stage::GetCurrent().Add(gActorPC);

  //Set variable fStep condition
  gStep = 100.0f;
  Dali::Vector<float> vecValues;
  for( int i = 1 ; i < 10 ; i++ )
  {
    vecValues.PushBack(i * gStep + (i % 2 == 0 ? -(gStep * 0.2f) : (gStep * 0.2f)));
  }

  PropertyNotification variable_step_notification = gActorPC.AddPropertyNotification( Actor::Property::POSITION, 0, VariableStepCondition(vecValues) );
  variable_step_notification.NotifySignal().Connect( &CbPropertyConditionNotifySignalCallback );

  // set initial position lower than first position in list
  gPropertyConditionNotifyCallback = false;
  gActorPC.SetPosition(Vector3(vecValues[0] - gStep, 0.0f, 0.0f));
}

void VTPropertyConditionVariableStepCondition001()
{
  DALI_CHECK_FAIL(!gPropertyConditionNotifyCallback, "VariableStepCondition is failed; could not trigger notification signal.");
  Stage::GetCurrent().Remove(gActorPC);
  DaliLog::PrintPass();

}

void PropertyConditionOutsideCondition()
{
  const float F_MIN = 100.0f, F_MAX = 200.0f;

  gActorPC = Actor::New();
  DALI_CHECK_FAIL(!gActorPC,  "Actor::New() is failed" );
  Stage::GetCurrent().Add(gActorPC);

  PropertyNotification notification = gActorPC.AddPropertyNotification( Actor::Property::POSITION_X, OutsideCondition(F_MIN, F_MAX) );
  notification.NotifySignal().Connect( &CbPropertyConditionNotifySignalCallback );

  // Move outside (left) to satisfy condition
  gPropertyConditionNotifyCallback = false;
  gActorPC.SetPosition(Vector3::ZERO);
}
void VTPropertyConditionOutsideCondition001()
{
  DALI_CHECK_FAIL(!gPropertyConditionNotifyCallback,
      "OutsideCondition is failed; could not trigger notification signal at a lower value than the range." );

  // Move inside to un-satisfy condition
  const float F_INSIDE = 150.0f;
  gPropertyConditionNotifyCallback = false;
  gActorPC.SetPosition(Vector3(F_INSIDE, 0.0f, 0.0f));
}
void VTPropertyConditionOutsideCondition002()
{
  DALI_CHECK_FAIL( gPropertyConditionNotifyCallback,
      "OutsideCondition is failed; notification signal is triggered inside the range." );
  // Move outside (right) to satisfy condition again.
  const float F_OUTSIDE = 300.0f;
  gPropertyConditionNotifyCallback = false;
  gActorPC.SetPosition(Vector3(F_OUTSIDE, 0.0f, 0.0f));
}
void VTPropertyConditionOutsideCondition003()
{
  DALI_CHECK_FAIL(!gPropertyConditionNotifyCallback,
      "OutsideCondition is failed; could not trigger notification signal at a higher value than the range." );

  Stage::GetCurrent().Remove(gActorPC);
  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase         UtcDaliPropertyConditionConstructorP
 * @since_tizen      2.4
 * @description      Property Condition instance Constructor
 */
int UtcDaliPropertyConditionConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Condition_TestApp testApp( application, PROPERTY_CONDITION_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase            UtcDaliPropertyConditionCopyConstructorP
 * @since_tizen         2.4
 *  @description      Property Condition instance Copy Constructor
 */
int UtcDaliPropertyConditionCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Condition_TestApp testApp( application, PROPERTY_CONDITION_COPYCONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyConditionOperatorAssignmentP
 * @since_tizen      2.4
 * @description      Assignment operator.Changes this handle to point to another real object.
 */
int UtcDaliPropertyConditionOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Condition_TestApp testApp( application, PROPERTY_CONDITION_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyConditionGetArgumentP
 * @since_tizen      2.4
 * @description      To Retrieve the arguments that this condition uses.
 */
int UtcDaliPropertyConditionGetArgumentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Condition_TestApp testApp( application, PROPERTY_CONDITION_GET_ARGUMENTS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyConditionGetArgumentCountP
 * @since_tizen      2.4
 * @description      To Retrieve the arguments that this condition uses.
 */
int UtcDaliPropertyConditionGetArgumentCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Condition_TestApp testApp( application, PROPERTY_CONDITION_GET_ARGUMENTS_COUNT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyConditionLessThanConditionP
 * @since_tizen      2.4
 * @description      To compare whether property is less than arg.
 */
int UtcDaliPropertyConditionLessThanConditionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Condition_TestApp testApp( application, PROPERTY_CONDITION_LESS_THAN_CONDITION);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyConditionGreaterThanConditionP
 * @since_tizen      2.4
 * @description      To compare whether property is greater than arg.
 */
int UtcDaliPropertyConditionGreaterThanConditionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Condition_TestApp testApp( application, PROPERTY_CONDITION_GREATER_THAN_CONDITION);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliPropertyConditionInsideConditionP
 * @since_tizen      2.4
 * @description      To compare whether property is greater than arg0 and less than arg1.
 */
int UtcDaliPropertyConditionInsideConditionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Condition_TestApp testApp( application, PROPERTY_CONDITION_INSIDE_CONDITION);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase         UtcDaliPropertyConditionOutsideConditionP
 * @since_tizen      2.4
 * @description      Set property OutsideCondition of an actor
 */
int UtcDaliPropertyConditionOutsideConditionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Condition_TestApp testApp( application, PROPERTY_CONDITION_OUTSIDE_CONDITION );
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase         UtcDaliPropertyConditionStepConditionP
 * @since_tizen      2.4
 * @description      Set property StepCondition of an actor
 */
int UtcDaliPropertyConditionStepConditionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Condition_TestApp testApp( application, PROPERTY_CONDITION_STEP_CONDITION);
  application.MainLoop();
  return test_return_value;
}



/**
 * @testcase         UtcDaliPropertyConditionVariableStepConditionP
 * @since_tizen      2.4
 * @description      Set property VariableStepCondition of an actor
 */
int UtcDaliPropertyConditionVariableStepConditionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Condition_TestApp testApp( application, PROPERTY_CONDITION_VARIABLE_STEP_CONDITION);
  application.MainLoop();
  return test_return_value;
}

