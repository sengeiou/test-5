#include "utc-dali-constraint-impl.h"

//& set: Constraint

/**
 * @function            utc_Dali_Constraints_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Constraint_startup(void)
{
  test_return_value=0;
  gRenderCountConstraint=0;
}

/**
 * @function            utc_Dali_Constraint_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Constraint_cleanup(void)
{

}


namespace
{
  enum TEST_CASES_LIST_CONSTRAINT
  {
    CONSTRAINT_NEW_ON_STAGE_BOOLEAN_P,
    CONSTRAINT_NEW_ON_STAGE_INTEGER_P,
    CONSTRAINT_NEW_ON_STAGE_FLOAT_P,
    CONSTRAINT_NEW_ON_STAGE_VECTOR2_P,
    CONSTRAINT_NEW_ON_STAGE_VECTOR3_P,
    CONSTRAINT_NEW_ON_STAGE_VECTOR4_P,
    CONSTRAINT_NEW_ON_STAGE_MATRIX_P,
    CONSTRAINT_NEW_ON_STAGE_MATRIX3_P,
    CONSTRAINT_NEW_ON_STAGE_QUATERNION_P,
    CONSTRAINT_NEW_ON_STAGE_BOOLEAN_ADD_SOURCE_P,
    CONSTRAINT_NEW_ON_STAGE_BOOLEAN_ADD_SOURCE_PARENT_P,
    CONSTRAINT_NEW_ON_STAGE_INTEGER_ADD_SOURCE_P,
    CONSTRAINT_NEW_ON_STAGE_INTEGER_ADD_SOURCE_PARENT_P,
    CONSTRAINT_NEW_ON_STAGE_FLOAT_ADD_SOURCE_P,
    CONSTRAINT_NEW_ON_STAGE_FLOAT_ADD_SOURCE_PARENT_P,
    CONSTRAINT_NEW_ON_STAGE_VECTOR2_ADD_SOURCE_P,
    CONSTRAINT_NEW_ON_STAGE_VECTOR2_ADD_SOURCE_PARENT_P,
    CONSTRAINT_NEW_ON_STAGE_VECTOR3_ADD_SOURCE_P,
    CONSTRAINT_NEW_ON_STAGE_VECTOR3_ADD_SOURCE_PARENT_P,
    CONSTRAINT_NEW_ON_STAGE_MATRIX_ADD_SOURCE_P,
    CONSTRAINT_NEW_ON_STAGE_MATRIX_ADD_SOURCE_PARENT_P,
    CONSTRAINT_NEW_ON_STAGE_MATRIX3_ADD_SOURCE_P,
    CONSTRAINT_NEW_ON_STAGE_MATRIX3_ADD_SOURCE_PARENT_P,
    CONSTRAINT_NEW_ON_STAGE_QUATERNION_ADD_SOURCE_P,
    CONSTRAINT_NEW_ON_STAGE_QUATERNION_ADD_SOURCE_PARENT_P,
    CONSTRAINT_NEW_ON_STAGE_VECTOR2_ADD_SOURCE_LOCAL_P,
    CONSTRAINT_CLONED_DOWNCAST_P,
    CONSTRAINT_COPYCONSTRUCTOR_P,
    CONSTRAINT_OPERATORASSIGNMENT_P,
    CONSTRAINT_GETTARGETOBJECT_P,
    CONSTRAINT_GETTARGETOBJECT_N,
    CONSTRAINT_GETTARGETPROPERTY_P,
    CONSTRAINT_GETTARGETPROPERTY_N,
    CONSTRAINT_SETGETTAG_P,
    CONSTRAINT_SETGETTAG_P2,
    CONSTRAINT_GET_REMOVE_ACTION_P
  };

  struct Constraint_TestApp : public ConnectionTracker
  {
    Constraint_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Constraint_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Constraint_TestApp::Tick );
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
        case CONSTRAINT_NEW_ON_STAGE_BOOLEAN_P:
          ConstraintNewOnStageBooleanP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_INTEGER_P:
          ConstraintNewOnStageIntegerP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_FLOAT_P:
          ConstraintNewOnStageFloatP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR2_P:
          ConstraintNewOnStageVector2P();
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR3_P:
          ConstraintNewOnStageVector3P();
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR4_P:
          ConstraintNewOnStageVector4P();
          break;

        case CONSTRAINT_NEW_ON_STAGE_MATRIX_P:
          ConstraintNewOnStageMatrixP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_MATRIX3_P:
          ConstraintNewOnStageMatrix3P();
          break;

        case CONSTRAINT_NEW_ON_STAGE_QUATERNION_P:
          ConstraintNewOnStageQuaternionP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_BOOLEAN_ADD_SOURCE_P:
          ConstraintNewOnStageBooleanAddSourceP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_BOOLEAN_ADD_SOURCE_PARENT_P:
          ConstraintNewOnStageBooleanAddSourceParentP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_INTEGER_ADD_SOURCE_P:
          ConstraintNewOnStageIntegerAddSourceP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_INTEGER_ADD_SOURCE_PARENT_P:
          ConstraintNewOnStageIntegerAddSourceParentP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_FLOAT_ADD_SOURCE_P:
          ConstraintNewOnStageFloatAddSourceP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_FLOAT_ADD_SOURCE_PARENT_P:
          ConstraintNewOnStageFloatAddSourceParentP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR2_ADD_SOURCE_P:
          ConstraintNewOnStageVector2AddSourceP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR2_ADD_SOURCE_PARENT_P:
          ConstraintNewOnStageVector2AddSourceParentP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR3_ADD_SOURCE_P:
          ConstraintNewOnStageVector3AddSourceP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR3_ADD_SOURCE_PARENT_P:
          ConstraintNewOnStageVector3AddSourceParentP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_MATRIX_ADD_SOURCE_P:
          ConstraintNewOnStageMatrixAddSourceP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_MATRIX_ADD_SOURCE_PARENT_P:
          ConstraintNewOnStageMatrixAddSourceParentP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_MATRIX3_ADD_SOURCE_P:
          ConstraintNewOnStageMatrix3AddSourceP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_MATRIX3_ADD_SOURCE_PARENT_P:
          ConstraintNewOnStageMatrix3AddSourceParentP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_QUATERNION_ADD_SOURCE_P:
          ConstraintNewOnStageQuaternionAddSourceP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_QUATERNION_ADD_SOURCE_PARENT_P:
          ConstraintNewOnStageQuaternionAddSourceParentP();
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR2_ADD_SOURCE_LOCAL_P:
          ConstraintNewOnStageVector2AddSourceLocalP();
          break;

        case CONSTRAINT_CLONED_DOWNCAST_P:
          ConstraintClonedDowncastP();
          break;

        case CONSTRAINT_COPYCONSTRUCTOR_P:
          ConstraintCopyConstructorP();
          break;

        case CONSTRAINT_OPERATORASSIGNMENT_P:
          ConstraintOperatorAssignmentP();
          break;

        case CONSTRAINT_GETTARGETOBJECT_P:
          ConstraintGetTargetObjectP();
          break;

        case CONSTRAINT_GETTARGETOBJECT_N:
          ConstraintGetTargetObjectN();
          break;

        case CONSTRAINT_GETTARGETPROPERTY_P:
          ConstraintGetTargetPropertyP();
          break;

        case CONSTRAINT_GETTARGETPROPERTY_N:
          ConstraintGetTargetPropertyN();
          break;

        case CONSTRAINT_SETGETTAG_P:
          ConstraintSetGetTagP();
          break;

        case CONSTRAINT_SETGETTAG_P2:
          ConstraintSetGetTagP2();
          break;

        case CONSTRAINT_GET_REMOVE_ACTION_P:
          ConstraintGetRemoveActionP();
          break;

      }
    }


    void VerdictTest()
    {
      switch (mTestCase)
      {
        case CONSTRAINT_NEW_ON_STAGE_BOOLEAN_P:
        case CONSTRAINT_GETTARGETPROPERTY_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<bool>(gConstraintActor, CONSTRAINT_BOOL_START, CONSTRAINT_BOOL_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<bool>(gConstraintActor, CONSTRAINT_BOOL_TARGET, CONSTRAINT_BOOL_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<bool>(CONSTRAINT_BOOL_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_BOOLEAN_ADD_SOURCE_P:
        case CONSTRAINT_NEW_ON_STAGE_BOOLEAN_ADD_SOURCE_PARENT_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<bool>(gSourceActor, CONSTRAINT_BOOL_START, CONSTRAINT_BOOL_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<bool>(gSourceActor, CONSTRAINT_BOOL_TARGET, CONSTRAINT_BOOL_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<bool>(CONSTRAINT_BOOL_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_INTEGER_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<int>(gConstraintActor, CONSTRAINT_INT_START, CONSTRAINT_INT_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<int>(gConstraintActor, CONSTRAINT_INT_TARGET, CONSTRAINT_INT_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<int>(CONSTRAINT_INT_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_INTEGER_ADD_SOURCE_P:
        case CONSTRAINT_NEW_ON_STAGE_INTEGER_ADD_SOURCE_PARENT_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<int>(gSourceActor, CONSTRAINT_INT_START, CONSTRAINT_INT_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<int>(gSourceActor, CONSTRAINT_INT_TARGET, CONSTRAINT_INT_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<int>(CONSTRAINT_INT_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_FLOAT_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<float>(gConstraintActor, CONSTRAINT_FLOAT_START, CONSTRAINT_FLOAT_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<float>(gConstraintActor, CONSTRAINT_FLOAT_TARGET, CONSTRAINT_FLOAT_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<float>(CONSTRAINT_FLOAT_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_CLONED_DOWNCAST_P:
        case CONSTRAINT_NEW_ON_STAGE_FLOAT_ADD_SOURCE_P:
        case CONSTRAINT_NEW_ON_STAGE_FLOAT_ADD_SOURCE_PARENT_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<float>(gSourceActor, CONSTRAINT_FLOAT_START, CONSTRAINT_FLOAT_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<float>(gSourceActor, CONSTRAINT_FLOAT_TARGET, CONSTRAINT_FLOAT_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<float>(CONSTRAINT_FLOAT_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR2_P:
        case CONSTRAINT_NEW_ON_STAGE_VECTOR2_ADD_SOURCE_LOCAL_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<Vector2>(gConstraintActor, CONSTRAINT_VEC2_START, CONSTRAINT_VEC2_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<Vector2>(gConstraintActor, CONSTRAINT_VEC2_TARGET, CONSTRAINT_VEC2_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<Vector2>(CONSTRAINT_VEC2_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR2_ADD_SOURCE_P:
        case CONSTRAINT_NEW_ON_STAGE_VECTOR2_ADD_SOURCE_PARENT_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<Vector2>(gSourceActor, CONSTRAINT_VEC2_START, CONSTRAINT_VEC2_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<Vector2>(gSourceActor, CONSTRAINT_VEC2_TARGET, CONSTRAINT_VEC2_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<Vector2>(CONSTRAINT_VEC2_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR3_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<Vector3>(gConstraintActor, CONSTRAINT_VEC3_START, CONSTRAINT_VEC3_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<Vector3>(gConstraintActor, CONSTRAINT_VEC3_TARGET, CONSTRAINT_VEC3_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<Vector3>(CONSTRAINT_VEC3_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR3_ADD_SOURCE_P:
        case CONSTRAINT_NEW_ON_STAGE_VECTOR3_ADD_SOURCE_PARENT_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<Vector3>(gSourceActor, CONSTRAINT_VEC3_START, CONSTRAINT_VEC3_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<Vector3>(gSourceActor, CONSTRAINT_VEC3_TARGET, CONSTRAINT_VEC3_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<Vector3>(CONSTRAINT_VEC3_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_VECTOR4_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<Vector4>(gConstraintActor, CONSTRAINT_VEC4_START, CONSTRAINT_VEC4_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<Vector4>(gConstraintActor, CONSTRAINT_VEC4_TARGET, CONSTRAINT_VEC4_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<Vector4>(CONSTRAINT_VEC4_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_MATRIX_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<Matrix>(gConstraintActor, gConstraintMatStartValue, gConstraintMatTargetValue);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<Matrix>(gConstraintActor, gConstraintMatTargetValue, gConstraintMatStartValue);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<Matrix>(gConstraintMatStartValue);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_MATRIX_ADD_SOURCE_P:
        case CONSTRAINT_NEW_ON_STAGE_MATRIX_ADD_SOURCE_PARENT_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<Matrix>(gSourceActor, gConstraintMatStartValue, gConstraintMatTargetValue);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<Matrix>(gSourceActor, gConstraintMatTargetValue, gConstraintMatStartValue);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<Matrix>(gConstraintMatStartValue);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_MATRIX3_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<Matrix3>(gConstraintActor, gConstraintMat3StartValue, gConstraintMat3TargetValue);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<Matrix3>(gConstraintActor, gConstraintMat3TargetValue, gConstraintMat3StartValue);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<Matrix3>(gConstraintMat3StartValue);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_MATRIX3_ADD_SOURCE_P:
        case CONSTRAINT_NEW_ON_STAGE_MATRIX3_ADD_SOURCE_PARENT_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<Matrix3>(gSourceActor, gConstraintMat3StartValue, gConstraintMat3TargetValue);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<Matrix3>(gSourceActor, gConstraintMat3TargetValue, gConstraintMat3StartValue);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<Matrix3>(gConstraintMat3StartValue);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_QUATERNION_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<Quaternion>(gConstraintActor, CONSTRAINT_QT_START, CONSTRAINT_QT_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<Quaternion>(gConstraintActor, CONSTRAINT_QT_TARGET, CONSTRAINT_QT_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<Quaternion>(CONSTRAINT_QT_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_NEW_ON_STAGE_QUATERNION_ADD_SOURCE_P:
        case CONSTRAINT_NEW_ON_STAGE_QUATERNION_ADD_SOURCE_PARENT_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintAppliedCheck<Quaternion>(gSourceActor, CONSTRAINT_QT_START, CONSTRAINT_QT_TARGET);
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintCheckPropertyBeforeRemove<Quaternion>(gSourceActor, CONSTRAINT_QT_TARGET, CONSTRAINT_QT_START);
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintFinalCheck<Quaternion>(CONSTRAINT_QT_START);
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case CONSTRAINT_GET_REMOVE_ACTION_P:
          switch(gRenderCountConstraint)
          {
            case 0:
              VTConstraintGetRemoveAction001();
              gRenderCountConstraint++;
              break;

            case 1:
              VTConstraintGetRemoveAction002();
              gRenderCountConstraint++;
              break;

            case 2:
              VTConstraintGetRemoveAction003();
              gRenderCountConstraint++;
              break;

            case 3:
              VTConstraintGetRemoveAction004();
              gRenderCountConstraint++;
              break;

            case 4:
              VTConstraintGetRemoveAction005();
              gRenderCountConstraint++;
              break;

            case 5:
              VTConstraintGetRemoveAction006();
              gRenderCountConstraint++;
              break;

            case 6:
              VTConstraintGetRemoveAction007();
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
 * @testcase        UtcDaliConstraintNewOnStageBooleanP
 * @since_tizen     2.4
 * @description     Construct a constraint with boolean type property index
 */
int UtcDaliConstraintNewOnStageBooleanP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_BOOLEAN_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageIntegerP
 * @since_tizen     2.4
 * @description     Construct a constraint with integer type property index
 */
int UtcDaliConstraintNewOnStageIntegerP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_INTEGER_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageFloatP
 * @since_tizen     2.4
 * @description      Construct a constraint with float type property index
 */
int UtcDaliConstraintNewOnStageFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintNewOnStageVector2P
 * @since_tizen     2.4
 * @description     Construct a constraint with vector2 type property index
 */
int UtcDaliConstraintNewOnStageVector2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_VECTOR2_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintNewOnStageVector3P
 * @since_tizen     2.4
 * @description     Construct a constraint with vector3 type property index
 */
int UtcDaliConstraintNewOnStageVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_VECTOR3_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageVector3P
 * @since_tizen     2.4
 * @description     Construct a constraint with vector4 type property index
 */
int UtcDaliConstraintNewOnStageVector4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_VECTOR4_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageMatrixP
 * @since_tizen     2.4
 * @description     Construct a constraint with matrix type property index
 */
int UtcDaliConstraintNewOnStageMatrixP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_MATRIX_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintNewOnStageMatrix3P
 * @since_tizen     2.4
 * @description     Construct a constraint with matrix3 type property index
 */
int UtcDaliConstraintNewOnStageMatrix3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_MATRIX3_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageQuaternionP
 * @since_tizen     2.4
 * @description     Construct a constraint with quaternion type property index
 */
int UtcDaliConstraintNewOnStageQuaternionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_QUATERNION_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageBooleanAddSourceP
 * @since_tizen     2.4
 * @description     Construct a constraint with boolean type property index and source constraint
 */
int UtcDaliConstraintNewOnStageBooleanAddSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_BOOLEAN_ADD_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageBooleanAddSourceParentP
 * @since_tizen     2.4
 * @description     Construct a Constraint with boolean type property index and parent source constraint
 */
int UtcDaliConstraintNewOnStageBooleanAddSourceParentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_BOOLEAN_ADD_SOURCE_PARENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageIntegerAddSourceP
 * @since_tizen     2.4
 * @description     Construct a constraint with integer type property index and source constraint
 */
int UtcDaliConstraintNewOnStageIntegerAddSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_INTEGER_ADD_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageIntegerAddSourceParentP
 * @since_tizen     2.4
 * @description     Construct a Constraint with integer type property index and parent source constraint
 */
int UtcDaliConstraintNewOnStageIntegerAddSourceParentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_INTEGER_ADD_SOURCE_PARENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintNewOnStageFloatAddSourceP
 * @since_tizen     2.4
 * @description     Construct a constraint with float type property index and source constraint
 */
int UtcDaliConstraintNewOnStageFloatAddSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_FLOAT_ADD_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageFloatAddSourceParentP
 * @since_tizen     2.4
 * @description     Construct a Constraint with float type property index and parent source constraint
 */
int UtcDaliConstraintNewOnStageFloatAddSourceParentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_FLOAT_ADD_SOURCE_PARENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintNewOnStageVector2AddSourceP
 * @since_tizen     2.4
 * @description     Construct a constraint with vector2 type property index and source constraint
 */
int UtcDaliConstraintNewOnStageVector2AddSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_VECTOR2_ADD_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintNewOnStageVector2AddSourceParentP
 * @since_tizen     2.4
 * @description     Construct a Constraint with vector2 type property index and parent source constraint
 */
int UtcDaliConstraintNewOnStageVector2AddSourceParentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_VECTOR2_ADD_SOURCE_PARENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageVector3AddSourceP
 * @since_tizen     2.4
 * @description     Construct a constraint with vector3 type property index and source constraint
 */
int UtcDaliConstraintNewOnStageVector3AddSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_VECTOR3_ADD_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintNewOnStageVector3AddSourceParentP
 * @since_tizen     2.4
 * @description     Construct a Constraint with vector3 type property index and parent source constraint
 */
int UtcDaliConstraintNewOnStageVector3AddSourceParentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_VECTOR3_ADD_SOURCE_PARENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageMatrixAddSourceP
 * @since_tizen     2.4
 * @description     Construct a constraint with matrix type property index and source constraint
 */
int UtcDaliConstraintNewOnStageMatrixAddSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_MATRIX_ADD_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageMatrixAddSourceParentP
 * @since_tizen     2.4
 * @description     Construct a Constraint with matrix type property index and parent source constraint
 */
int UtcDaliConstraintNewOnStageMatrixAddSourceParentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_MATRIX_ADD_SOURCE_PARENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageMatrixAddSourceParentP
 * @since_tizen     2.4
 * @description     Construct a constraint with matrix3 type property index and source constraint
 */
int UtcDaliConstraintNewOnStageMatrix3AddSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_MATRIX3_ADD_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintNewOnStageMatrix3AddSourceParentP
 * @since_tizen     2.4
 * @description     Construct a Constraint with matrix3 type property index and parent source constraint
 */
int UtcDaliConstraintNewOnStageMatrix3AddSourceParentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_MATRIX3_ADD_SOURCE_PARENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintNewOnStageQuaternionAddSourceP
 * @since_tizen     2.4
 * @description     Construct a constraint with quaternion type property index and source constraint
 */
int UtcDaliConstraintNewOnStageQuaternionAddSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_QUATERNION_ADD_SOURCE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintNewOnStageQuaternionAddSourceParentP
 * @since_tizen     2.4
 * @description     Construct a Constraint with quaternion type property index and parent source constraint
 */
int UtcDaliConstraintNewOnStageQuaternionAddSourceParentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_QUATERNION_ADD_SOURCE_PARENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintNewOnStageVector2AddSourceLocalP
 * @since_tizen     2.4
 * @description     Construct a constraint with Vector2 type property index and local source constraint
 */
int UtcDaliConstraintNewOnStageVector2AddSourceLocalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_NEW_ON_STAGE_VECTOR2_ADD_SOURCE_LOCAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintGetRemoveActionP
 * @since_tizen     2.4
 * @description     Check that whether the constraint has remove action when fully-applied or discarded.
 */
int UtcDaliConstraintGetRemoveActionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_GET_REMOVE_ACTION_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintClonedDownCastP
 * @since_tizen     2.4
 * @description     Check that this case creates a clones of a constraint for another object and downcast an Object handle to Constraint handle.
 */
int UtcDaliConstraintClonedDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_CLONED_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintCopyConstuctorP
 * @since_tizen     2.4
 * @description     Check for copy constructor.
 */
int UtcDaliConstraintCopyConstuctorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_COPYCONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintOperatorAssignmentP
 * @since_tizen     2.4
 * @description     Check for operator=.
 */
int UtcDaliConstraintOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_OPERATORASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintGetTargetObjectP
 * @since_tizen     2.4
 * @description     Check for GetTargetObject
 */
int UtcDaliConstraintGetTargetObjectP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_GETTARGETOBJECT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintGetTargetObjectN
 * @since_tizen     2.4
 * @description     Check for GetTargetObject
 */
int UtcDaliConstraintGetTargetObjectN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_GETTARGETOBJECT_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintGetTargetPropertyP
 * @since_tizen     2.4
 * @description     Check for GetTargetProperty
 */
int UtcDaliConstraintGetTargetPropertyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_GETTARGETPROPERTY_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintGetTargetPropertyN
 * @since_tizen     2.4
 * @description     Check for GetTargetProperty
 */
int UtcDaliConstraintGetTargetPropertyN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_GETTARGETPROPERTY_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintSetGetTagP
 * @since_tizen     2.4
 * @description     check for SetTag and GetTag
 */
int UtcDaliConstraintSetGetTagP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_SETGETTAG_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintSetGetTagP2
 * @since_tizen     2.4
 * @description     check for SetTag and GetTag
 */
int UtcDaliConstraintSetGetTagP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraint_TestApp testapp( application, CONSTRAINT_SETGETTAG_P2);
  application.MainLoop();
  return test_return_value;
}


