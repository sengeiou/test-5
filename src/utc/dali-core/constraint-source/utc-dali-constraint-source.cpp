#include "utc-dali-constraint-source-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Constraintsource

/**
 * @function            utc_Dali_ConstraintSource_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_ConstraintSource_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_ConstraintSource_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_ConstraintSource_cleanup(void)
{

}

void ConstraintSourceSourceP();
void ConstraintSourceLocalSourceP();
void ConstraintSourceParentSourceP();
void SourceP();
void LocalSourceP();
void ParentSourceP();

namespace
{
  enum TEST_CASES_LIST_CONSTRAINT_SOURCE
  {
    SOURCE_P,
    LOCAL_SOURCE_P,
    PARENT_SOURCE_P,
    CONSTRAINT_SOURCE_SOURCE_P,
    CONSTRAINT_SOURCE_LOCAL_SOURCE_P,
    CONSTRAINT_SOURCE_PARENT_SOURCE_P
  };

  struct Constraint_Source_TestApp : public ConnectionTracker
  {
    Constraint_Source_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Constraint_Source_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Constraint_Source_TestApp::Tick );
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
        case SOURCE_P:
          SourceP();
          break;

        case LOCAL_SOURCE_P:
          LocalSourceP();
          break;

        case PARENT_SOURCE_P:
          ParentSourceP();
          break;

        case CONSTRAINT_SOURCE_SOURCE_P:
          ConstraintSourceSourceP();
          break;

        case CONSTRAINT_SOURCE_LOCAL_SOURCE_P:
          ConstraintSourceLocalSourceP();
          break;

        case CONSTRAINT_SOURCE_PARENT_SOURCE_P:
          ConstraintSourceParentSourceP();
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

void SourceP()
{
  bool bStartValue(true);
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed.");
  Stage::GetCurrent().Add(actor);

  Property::Index propertyIndex = actor.RegisterProperty("boolean-property", bStartValue);
  if(actor.GetProperty<bool>(propertyIndex) != bStartValue)
  {
    Stage::GetCurrent().Remove(actor);
    LOG_E("Actor::RegisterProperty() for propertyIndex is failed.");
    test_return_value=1;
    return;
  }

  Source source( actor, propertyIndex);
  DALI_CHECK_FAIL(source.object != actor, "Source object is failed.");
  DALI_CHECK_FAIL(source.propertyIndex != propertyIndex, "The index of the source property is failed.");

  Stage::GetCurrent().Remove(actor);
  DaliLog::PrintPass();
}


void LocalSourceP()
{

  bool bStartValue(true);
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed.");
  Stage::GetCurrent().Add(actor);

  Property::Index propertyIndex = actor.RegisterProperty("boolean-property", bStartValue);
  if(actor.GetProperty<bool>(propertyIndex) != bStartValue)
  {
    Stage::GetCurrent().Remove(actor);
    LOG_E("Actor::RegisterProperty() for propertyIndex is failed.");
    test_return_value=1;
    return;
  }
  Constraint constraint = Constraint::New<bool>(actor, propertyIndex, STConstraintSourceTypeValue(bStartValue));
  constraint.Apply();
  LocalSource localsource(propertyIndex);

  DALI_CHECK_FAIL(localsource.propertyIndex != propertyIndex, "The index of the local source property is failed.");

  Stage::GetCurrent().Remove(actor);
  DaliLog::PrintPass();

}

void ParentSourceP()
{

  bool bStartValue(true);
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed.");
  Stage::GetCurrent().Add(actor);
  Actor parentSourceActor = Actor::New();

  if(!parentSourceActor)
  {
    Stage::GetCurrent().Remove(actor);
    LOG_E("Actor::New() for parentSourceActor is failed.");
    test_return_value=1;
    return;
  }
  parentSourceActor.Add(actor);
  Property::Index parentSourcePropertyIndex = parentSourceActor.RegisterProperty("parent-boolean-property", bStartValue);
  if(parentSourceActor.GetProperty<bool>(parentSourcePropertyIndex) != bStartValue)
  {
    Stage::GetCurrent().Remove(actor);
    LOG_E("Actor::RegisterProperty() for parentSourcePropertyIndex is failed.");
    test_return_value=1;
    return;
  }
  Constraint constraint = Constraint::New<bool>(parentSourceActor, parentSourcePropertyIndex, STConstraintSourceTypeValue(bStartValue));
  constraint.Apply();
  ParentSource parentsource(parentSourcePropertyIndex);
  DALI_CHECK_FAIL(parentsource.propertyIndex != parentSourcePropertyIndex, "The index of the parent source property is failed.");

  Stage::GetCurrent().Remove(actor);
  DaliLog::PrintPass();

}


void ConstraintSourceSourceP()
{
  bool bStartValue(true);
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed.");
  Stage::GetCurrent().Add(actor);

  Property::Index propertyIndex = actor.RegisterProperty("boolean-property", bStartValue);
  if(actor.GetProperty<bool>(propertyIndex) != bStartValue)
  {
    Stage::GetCurrent().Remove(actor);
    LOG_E("Actor::RegisterProperty() for propertyIndex is failed.");
    test_return_value=1;
    return;
  }

  ConstraintSource constraintSource(Source(actor, propertyIndex));
  DALI_CHECK_FAIL(constraintSource.sourceType != OBJECT_PROPERTY, "The source type is invalid.");
  DALI_CHECK_FAIL(constraintSource.object != actor, "The target object is failed.");
  DALI_CHECK_FAIL(constraintSource.propertyIndex != propertyIndex, "The index of the source property is failed.");

  Stage::GetCurrent().Remove(actor);
  DaliLog::PrintPass();
}

void ConstraintSourceLocalSourceP()
{
  bool bStartValue(true);
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed.");
  Stage::GetCurrent().Add(actor);

  Property::Index propertyIndex = actor.RegisterProperty("boolean-property", bStartValue);
  if(actor.GetProperty<bool>(propertyIndex) != bStartValue)
  {
    Stage::GetCurrent().Remove(actor);
    LOG_E("Actor::RegisterProperty() for propertyIndex is failed.");
    test_return_value=1;
    return;
  }
  Constraint constraint = Constraint::New<bool>(actor, propertyIndex, STConstraintSourceTypeValue(bStartValue));
  constraint.Apply();
  ConstraintSource constraintSource = LocalSource(propertyIndex);

  DALI_CHECK_FAIL(constraintSource.sourceType != LOCAL_PROPERTY, "The source type is invalid.");
  DALI_CHECK_FAIL(constraintSource.propertyIndex != propertyIndex, "The index of the local source property is failed.");

  Stage::GetCurrent().Remove(actor);
  DaliLog::PrintPass();
}
void ConstraintSourceParentSourceP()
{
  bool bStartValue(true);
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed.");
  Stage::GetCurrent().Add(actor);
  Actor parentSourceActor = Actor::New();

  if(!parentSourceActor)
  {
    Stage::GetCurrent().Remove(actor);
    LOG_E("Actor::New() for parentSourceActor is failed.");
    test_return_value=1;
    return;
  }
  parentSourceActor.Add(actor);
  Property::Index parentSourcePropertyIndex = parentSourceActor.RegisterProperty("parent-boolean-property", bStartValue);
  if(parentSourceActor.GetProperty<bool>(parentSourcePropertyIndex) != bStartValue)
  {
    Stage::GetCurrent().Remove(actor);
    LOG_E("Actor::RegisterProperty() for parentSourcePropertyIndex is failed.");
    test_return_value=1;
    return;
  }
  Constraint constraint = Constraint::New<bool>(parentSourceActor, parentSourcePropertyIndex, STConstraintSourceTypeValue(bStartValue));
  constraint.Apply();
  ConstraintSource constraintSource = ParentSource(parentSourcePropertyIndex);
  DALI_CHECK_FAIL(constraintSource.sourceType != PARENT_PROPERTY, "The source type is invalid.");
  DALI_CHECK_FAIL(constraintSource.propertyIndex != parentSourcePropertyIndex, "The index of the parent source property is failed.");

  Stage::GetCurrent().Remove(actor);
  DaliLog::PrintPass();
}
/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase        UtcDaliSourceP
 * @since_tizen     2.4
 * @description     Construct a source instance
 */
int UtcDaliSourceP(void)
{

  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_Source_TestApp testApp( application, SOURCE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliLocalSourceP
 * @since_tizen     2.4
 * @description     Construct a local source instance
 */
int UtcDaliLocalSourceP(void)
{

  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_Source_TestApp testApp( application, LOCAL_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliParentSourceP
 * @since_tizen     2.4
 * @description     Construct a parent source instance
 */
int UtcDaliParentSourceP(void)
{

  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_Source_TestApp testApp( application, PARENT_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintSourceSourceP
 * @since_tizen     2.4
 * @description     Construct a constraintsource instance for boolean type property index and source
 */
int UtcDaliConstraintSourceSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_Source_TestApp testApp( application, CONSTRAINT_SOURCE_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}

///////////////////////////////////////////////////////////////////////////////
/**
 * @testcase        UtcDaliConstraintSourceLocalSourceP
 * @since_tizen     2.4
 * @description     Construct a constraintsource instance for boolean type property index and local source
 */

int UtcDaliConstraintSourceLocalSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_Source_TestApp testApp( application, CONSTRAINT_SOURCE_LOCAL_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}

///////////////////////////////////////////////////////////////////////////////
/**
 * @testcase        UtcDaliConstraintSourceParentSourceP
 * @since_tizen     2.4
 * @description     Construct a constraintsource instance for boolean type property index and parent source
 */
int UtcDaliConstraintSourceParentSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_Source_TestApp testApp( application, CONSTRAINT_SOURCE_PARENT_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}

