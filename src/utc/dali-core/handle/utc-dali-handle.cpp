#include "utc-dali-handle-impl.h"

//& set: Handle

/**
 * @function            utc_Dali_Handle_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Handle_startup(void)
{
  test_return_value = 0;
  gRenderCountHandle = 0;
}

/**
 * @function            utc_Dali_Handle_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Handle_cleanup(void)
{

}

namespace
{
  enum TEST_CASES_LIST_TAP_HANDLE
  {
    HANDLE_CONSTRUCTOR_P,
    HANDLE_COPYCONSTRUCTOR_P,
    HANDLE_NEW_P,
    HANDLE_GET_PROPERTY_INDICES_P,
    HANDLE_IS_PROPERTY_A_CONSTRAINT_INPUT_P,
    HANDLE_ADD_REMOVE_PROPERTY_NOTIFICATION_P,
    HANDLE_GET_PROPERTY_COUNT_AND_INDEX_AND_NAME_AND_TYPE_P,
    HANDLE_IS_PROPERTY_WRITABLE_P,
    HANDLE_IS_PROPERTY_ANIMATABLE_P,
    HANDLE_SUPPORTS_P,
    HANDLE_SET_GET_PROPERTY_FLOAT_P,
    HANDLE_SET_GET_PROPERTY_STRING_P,
    HANDLE_SET_GET_PROPERTY_INT_P,
    HANDLE_SET_GET_PROPERTY_BOOLEAN_P,
    HANDLE_SET_GET_PROPERTY_VECTOR2_P,
    HANDLE_SET_GET_PROPERTY_VECTOR3_P,
    HANDLE_SET_GET_PROPERTY_VECTOR4_P,
    HANDLE_SET_GET_PROPERTY_MATRIX_P,
    HANDLE_SET_GET_PROPERTY_MATRIX3_P,
    HANDLE_SET_GET_PROPERTY_RECT_P,
    HANDLE_SET_GET_PROPERTY_QUATERNION_P,
    HANDLE_SET_GET_PROPERTY_ARRAY_P,
    HANDLE_SET_GET_PROPERTY_MAP_P,
    HANDLE_SET_GET_PROPERTY_TYPE_P,
    HANDLE_OPERATOR_ASSIGNMENT_P,
    HANDLE_REGISTER_PROPERTY_FLOAT_WITHOUT_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_FLOAT_WITH_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_BOOL_WITHOUT_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_BOOL_WITH_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_VECTOR2_WITHOUT_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_VECTOR2_WITH_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_VECTOR3_WITHOUT_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_VECTOR3_WITH_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_VECTOR4_WITHOUT_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_VECTOR4_WITH_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_MATRIX3_WITHOUT_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_MATRIX3_WITH_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_MATRIX_WITHOUT_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_MATRIX_WITH_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_STRING_WITHOUT_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_STRING_WITH_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_QUATERNION_WITHOUT_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_QUATERNION_WITH_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_RECT_WITHOUT_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_RECT_WITH_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_MAP_WITH_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_MAP_WITHOUT_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_ARRAY_WITHOUT_ACCESSMODE_P,
    HANDLE_REGISTER_PROPERTY_ARRAY_WITH_ACCESSMODE_P,
    HANDLE_REMOVE_CONSTRAINTS_WITH_AND_WITHOUT_TAG_P,
    HANDLE_NEW_WEIGHT_OBJECT_DOWNCAST_P,
    HANDLE_DOWNCAST_N,
    HANDLE_REMOVE_PROPERTY_NOTIFICATIONS_P
  };

  struct Handle_TestApp : public ConnectionTracker
  {
    Handle_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Handle_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Handle_TestApp::Tick );
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
        case HANDLE_CONSTRUCTOR_P:
          HandleConstructorP();
          break;
        case HANDLE_COPYCONSTRUCTOR_P:
          HandleCopyConstructorP();
          break;
        case HANDLE_NEW_P:
          HandleNewP();
          break;
        case HANDLE_GET_PROPERTY_INDICES_P:
          HandleGetPropertyIndicesP();
          break;
        case HANDLE_IS_PROPERTY_A_CONSTRAINT_INPUT_P:
          HandleIsPropertyAConstraintInputP();
          break;
        case HANDLE_ADD_REMOVE_PROPERTY_NOTIFICATION_P:
          HandleAddRemovePropertyNotificationP();
          break;
        case HANDLE_GET_PROPERTY_COUNT_AND_INDEX_AND_NAME_AND_TYPE_P:
          HandleGetPropertyCountAndIndexAndNameAndTypeP();
          break;
        case HANDLE_IS_PROPERTY_WRITABLE_P:
          HandleIsPropertyWritableP();
          break;
        case HANDLE_IS_PROPERTY_ANIMATABLE_P:
          HandleIsPropertyAnimatableP();
          break;
        case HANDLE_SUPPORTS_P:
          HandleSupportsP();
          break;
        case HANDLE_SET_GET_PROPERTY_FLOAT_P:
          HandleSetGetPropertyFloatP();
          break;
        case HANDLE_SET_GET_PROPERTY_STRING_P:
          HandleSetGetPropertyStringP();
          break;
        case HANDLE_SET_GET_PROPERTY_INT_P:
          HandleSetGetPropertyIntP();
          break;
        case HANDLE_SET_GET_PROPERTY_BOOLEAN_P:
          HandleSetGetPropertyBooleanP();
          break;
        case HANDLE_SET_GET_PROPERTY_VECTOR2_P:
          HandleSetGetPropertyVector2P();
          break;
        case HANDLE_SET_GET_PROPERTY_VECTOR3_P:
          HandleSetGetPropertyVector3P();
          break;
        case HANDLE_SET_GET_PROPERTY_VECTOR4_P:
          HandleSetGetPropertyVector4P();
          break;
        case HANDLE_SET_GET_PROPERTY_MATRIX_P:
          HandleSetGetPropertyMatrixP();
          break;
        case HANDLE_SET_GET_PROPERTY_MATRIX3_P:
          HandleSetGetPropertyMatrix3P();
          break;
        case HANDLE_SET_GET_PROPERTY_RECT_P:
          HandleSetGetPropertyRectP();
          break;
        case HANDLE_SET_GET_PROPERTY_QUATERNION_P:
          HandleSetGetPropertyQuaternionP();
          break;
        case HANDLE_SET_GET_PROPERTY_ARRAY_P:
          HandleSetGetPropertyArrayP();
          break;
        case HANDLE_SET_GET_PROPERTY_MAP_P:
          HandleSetGetPropertyMapP();
          break;
        case HANDLE_SET_GET_PROPERTY_TYPE_P:
          HandleSetGetPropertyTypeP();
          break;
        case HANDLE_OPERATOR_ASSIGNMENT_P:
          HandleOperatorAssignmentP();
          break;
        case HANDLE_REGISTER_PROPERTY_FLOAT_WITHOUT_ACCESSMODE_P:
          HandleRegisterPropertyFloatWithoutAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_FLOAT_WITH_ACCESSMODE_P:
          HandleRegisterPropertyFloatWithAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_BOOL_WITHOUT_ACCESSMODE_P:
          HandleRegisterPropertyboolWithOutAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_BOOL_WITH_ACCESSMODE_P:
          HandleRegisterPropertyboolWithAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_VECTOR2_WITHOUT_ACCESSMODE_P:
          HandleRegisterPropertyVector2WithoutAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_VECTOR2_WITH_ACCESSMODE_P:
          HandleRegisterPropertyVector2WithAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_VECTOR3_WITHOUT_ACCESSMODE_P:
          HandleRegisterPropertyVector3WithOutAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_VECTOR3_WITH_ACCESSMODE_P:
          HandleRegisterPropertyVector3WithAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_VECTOR4_WITHOUT_ACCESSMODE_P:
          HandleRegisterPropertyVector4WithOutAccessmodeP();
          break;
        case HANDLE_REGISTER_PROPERTY_VECTOR4_WITH_ACCESSMODE_P:
          HandleRegisterPropertyVector4WithAccessmodeP();
          break;
        case HANDLE_REGISTER_PROPERTY_MATRIX3_WITHOUT_ACCESSMODE_P:
          HandleRegisterPropertyMatrix3WithoutAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_MATRIX3_WITH_ACCESSMODE_P:
          HandleRegisterPropertyMatrix3WithAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_MATRIX_WITHOUT_ACCESSMODE_P:
          HandleRegisterPropertyMatrixWithoutAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_MATRIX_WITH_ACCESSMODE_P:
          HandleRegisterPropertyMatrixWithAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_STRING_WITHOUT_ACCESSMODE_P:
          HandleRegisterPropertyStringWithoutAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_STRING_WITH_ACCESSMODE_P:
          HandleRegisterPropertyStringWithAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_QUATERNION_WITHOUT_ACCESSMODE_P:
          HandleRegisterPropertyQuaternionWithoutAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_QUATERNION_WITH_ACCESSMODE_P:
          HandleRegisterPropertyQuaternionWithAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_RECT_WITHOUT_ACCESSMODE_P:
          HandleRegisterPropertyRectWithoutAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_RECT_WITH_ACCESSMODE_P:
          HandleRegisterPropertyRectWithAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_MAP_WITH_ACCESSMODE_P:
          HandleRegisterPropertyMapWithAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_MAP_WITHOUT_ACCESSMODE_P:
          HandleRegisterPropertyMapWithoutAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_ARRAY_WITHOUT_ACCESSMODE_P:
          HandleRegisterPropertyArrayWithoutAccessModeP();
          break;
        case HANDLE_REGISTER_PROPERTY_ARRAY_WITH_ACCESSMODE_P:
          HandleRegisterPropertyArrayWithAccessModeP();
          break;
        case HANDLE_REMOVE_CONSTRAINTS_WITH_AND_WITHOUT_TAG_P:
          HandleRemoveConstraintsWithAndWithoutTagP();
          break;
        case HANDLE_NEW_WEIGHT_OBJECT_DOWNCAST_P:
          HandleNewWeightObjectDownCastP();
          break;
        case HANDLE_DOWNCAST_N:
          HandleDownCastN();
          break;
        case HANDLE_REMOVE_PROPERTY_NOTIFICATIONS_P:
          HandleRemovePropertyNotificationsP();
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case HANDLE_ADD_REMOVE_PROPERTY_NOTIFICATION_P:
          switch(gRenderCountHandle)
          {
            case 0:
              VTHandleAddRemovePropertyNotification001();
              gRenderCountHandle++;
              break;

            case 1:
              VTHandleAddRemovePropertyNotification002();
              gRenderCountHandle++;
              break;

            case 2:
              VTHandleAddRemovePropertyNotification003();
              gRenderCountHandle++;
              break;

            case 3:
              VTHandleAddRemovePropertyNotification004();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case HANDLE_REMOVE_CONSTRAINTS_WITH_AND_WITHOUT_TAG_P:
          switch(gRenderCountHandle)
          {
            case 0:
              VTHandleRemoveConstraintsWithAndWithoutTag001();
              gRenderCountHandle++;
              break;

            case 1:
              VTHandleRemoveConstraintsWithAndWithoutTag002();
              gRenderCountHandle++;
              break;

            case 2:
              VTHandleRemoveConstraintsWithAndWithoutTag003();
              gRenderCountHandle++;
              break;

            case 3:
              VTHandleRemoveConstraintsWithAndWithoutTag004();
              gRenderCountHandle++;
              break;

            case 4:
              VTHandleRemoveConstraintsWithAndWithoutTag005();
              gRenderCountHandle++;
              break;

            case 5:
              VTHandleRemoveConstraintsWithAndWithoutTag006();
              gRenderCountHandle++;
              break;

            case 6:
              VTHandleRemoveConstraintsWithAndWithoutTag007();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case HANDLE_REMOVE_PROPERTY_NOTIFICATIONS_P:
          switch(gRenderCountHandle)
          {
            case 0:
              VTHandleRemovePropertyNotifications001();
              gRenderCountHandle++;
              break;

            case 1:
              VTHandleRemovePropertyNotifications002();
              gRenderCountHandle++;
              break;

            case 2:
              VTHandleRemovePropertyNotifications003();
              gRenderCountHandle++;
              break;

            case 3:
              VTHandleRemovePropertyNotifications004();
              gRenderCountHandle++;
              break;

            case 4:
              VTHandleRemovePropertyNotifications005();
              gRenderCountHandle++;
              break;

            case 5:
              VTHandleRemovePropertyNotifications006();
              gRenderCountHandle++;
              break;

            case 6:
              VTHandleRemovePropertyNotifications007();
              gRenderCountHandle++;
              break;

            case 7:
              VTHandleRemovePropertyNotifications008();
              gRenderCountHandle++;
              break;

            case 8:
              VTHandleRemovePropertyNotifications009();
              gRenderCountHandle++;
              break;

            case 9:
              VTHandleRemovePropertyNotifications010();
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
 * @testcase        UtcDaliHandleConstuctorP
 * @since_tizen     2.4
 * @description     Checking if Handle's default constructor works property or not.
 */
int UtcDaliHandleConstuctorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleCopyConstuctorP
 * @since_tizen     2.4
 * @description     Checking if Handle's Copy constructor works property or not.
 */
int UtcDaliHandleCopyConstuctorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_COPYCONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleNewP
 * @since_tizen     2.4
 * @description     Checking if Handle's New() method works property or not.
 */
int UtcDaliHandleNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_NEW_P);
  application.MainLoop();
  return test_return_value;
}
/**
 * @testcase        UtcDaliHandleGetPropertyIndicesP
 * @since_tizen     2.4
 * @description     Checking the container that retrieves all the property indices for this object (including custom properties) is valid or not.
 */
int UtcDaliHandleGetPropertyIndicesP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_GET_PROPERTY_INDICES_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleIsPropertyAConstraintInputP
 * @since_tizen     2.4
 * @description     Checking the query whether a property can be used as in input to a constraint or not.
 */
int UtcDaliHandleIsPropertyAConstraintInputP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_IS_PROPERTY_A_CONSTRAINT_INPUT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleAddRemovePropertyNotificationP
 * @since_tizen     2.4
 * @description     Add and Remove a property notification to this object.
 */
int UtcDaliHandleAddRemovePropertyNotificationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_ADD_REMOVE_PROPERTY_NOTIFICATION_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleGetPropertyCountAndIndexAndNameAndTypeP
 * @since_tizen     2.4
 * @description     Query the index , count of a property and Query the strname of a property.
 */
int UtcDaliHandleGetPropertyCountAndIndexAndNameAndTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_GET_PROPERTY_COUNT_AND_INDEX_AND_NAME_AND_TYPE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleIsPropertyWritableP
 * @since_tizen     2.4
 * @description     Query whether a writable property can be the target of an animation or constraint.
 */
int UtcDaliHandleIsPropertyWritableP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_IS_PROPERTY_WRITABLE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleIsPropertyAnimatableP
 * @since_tizen     2.4
 * @description     Query whether a Animatable property can be the target of an animation or constraint.
 */
int UtcDaliHandleIsPropertyAnimatableP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_IS_PROPERTY_ANIMATABLE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleSupportsP
 * @since_tizen     2.4
 * @description     Query whether an handle supports a given capability.
 */
int UtcDaliHandleSupportsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SUPPORTS_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleSetGetPropertyFloatP
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type float
 */
int UtcDaliHandleSetGetPropertyFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleSetGetPropertyStringP
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type String.
 */
int UtcDaliHandleSetGetPropertyStringP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_STRING_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleSetGetPropertyIntP
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type  Int.
 */
int UtcDaliHandleSetGetPropertyIntP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_INT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleSetGetPropertyBooleanP
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type  Boolean.
 */
int UtcDaliHandleSetGetPropertyBooleanP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_BOOLEAN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleSetGetPropertyVector2P
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type vector2.
 */
int UtcDaliHandleSetGetPropertyVector2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_VECTOR2_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleSetGetPropertyVector3P
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type vector3.
 */
int UtcDaliHandleSetGetPropertyVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_VECTOR3_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleSetGetPropertyVector4P
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type vector4.
 */
int UtcDaliHandleSetGetPropertyVector4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_VECTOR4_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleSetGetPropertyMatrixP
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type Matrix.
 */
int UtcDaliHandleSetGetPropertyMatrixP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_MATRIX_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleSetGetPropertyMatrix3P
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type Matrix3.
 */
int UtcDaliHandleSetGetPropertyMatrix3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_MATRIX3_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleSetGetPropertyRectP
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type Rect.
 */
int UtcDaliHandleSetGetPropertyRectP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_RECT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleSetGetPropertyQuaternionP
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type Quaternion.
 */
int UtcDaliHandleSetGetPropertyQuaternionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_QUATERNION_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleSetGetPropertyArrayP
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type Array.
 */
int UtcDaliHandleSetGetPropertyArrayP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_ARRAY_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleSetGetPropertyMapP
 * @since_tizen     2.4
 * @description     Set and Retrieve  property value of type Map.
 */
int UtcDaliHandleSetGetPropertyMapP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_MAP_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleSetGetPropertyTypeP
 * @since_tizen     2.4
 * @description     Convenience function for obtaining a property of a known type.
 */
int UtcDaliHandleSetGetPropertyTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_SET_GET_PROPERTY_TYPE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleOperatorAssignmentP
 * @since_tizen     2.4
 * @description     Assign a Handle object to another handle object.
 */
int UtcDaliHandleOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyFloatWithoutAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Float Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyFloatWithoutAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_FLOAT_WITHOUT_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyFloatWithAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Float Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyFloatWithAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_FLOAT_WITH_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyboolWithoutAccessModeP
 * @since_tizen     2.4
 * @description     Register a new bool Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyboolWithoutAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_BOOL_WITHOUT_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyboolWithAccessModeP
 * @since_tizen     2.4
 * @description     Register a new bool Value property with access mode.
 */
int UtcDaliHandleRegisterPropertyboolWithAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_BOOL_WITH_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyVector2WithoutAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Vector2 Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyVector2WithoutAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_VECTOR2_WITHOUT_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleRegisterPropertyVector2WithAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Vector2 Value property with access mode.
 */
int UtcDaliHandleRegisterPropertyVector2WithAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_VECTOR2_WITH_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleRegisterPropertyVector3WithoutAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Vector3 Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyVector3WithoutAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_VECTOR3_WITHOUT_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyVector3WithAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Vector3 Value property with access mode.
 */
int UtcDaliHandleRegisterPropertyVector3WithAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_VECTOR3_WITH_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyVector4WithoutAccessmodeP
 * @since_tizen     2.4
 * @description     Register a new Vector4 Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyVector4WithoutAccessmodeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_VECTOR4_WITHOUT_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyVector4WithAccessmodeP
 * @since_tizen     2.4
 * @description     Register a new Vector4 Value property with access mode.
 */
int UtcDaliHandleRegisterPropertyVector4WithAccessmodeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_VECTOR4_WITH_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyMatrix3WithoutAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Matrix3 Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyMatrix3WithoutAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_MATRIX3_WITHOUT_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleRegisterPropertyMatrix3WithAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Matrix3 Value property with access mode.
 */
int UtcDaliHandleRegisterPropertyMatrix3WithAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_MATRIX3_WITH_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleRegisterPropertyMatrixWithoutAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Matrix Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyMatrixWithoutAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_MATRIX_WITHOUT_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyMatrixWithAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Matrix Value property with access mode.
 */
int UtcDaliHandleRegisterPropertyMatrixWithAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_MATRIX_WITH_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyStringWithoutAccessModeP
 * @since_tizen     2.4
 * @description     Register a new String Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyStringWithoutAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_STRING_WITHOUT_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyStringWithAccessModeP
 * @since_tizen     2.4
 * @description     Register a new String Value property with access mode.
 */
int UtcDaliHandleRegisterPropertyStringWithAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_STRING_WITH_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleRegisterPropertyQuaternionWithoutAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Quartion Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyQuaternionWithoutAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_QUATERNION_WITHOUT_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyQuaternionWithAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Quartion Value property with access mode.
 */
int UtcDaliHandleRegisterPropertyQuaternionWithAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_QUATERNION_WITH_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyRectWithoutAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Rect Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyRectWithoutAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_RECT_WITHOUT_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyRectWithAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Rect Value property with access mode.
 */
int UtcDaliHandleRegisterPropertyRectWithAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_RECT_WITH_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyMapWithAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Map Value property with access mode.
 */
int UtcDaliHandleRegisterPropertyMapWithAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_MAP_WITH_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleRegisterPropertyMapWithoutAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Map Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyMapWithoutAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_MAP_WITHOUT_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyArrayWithoutAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Array Value property without access mode.
 */
int UtcDaliHandleRegisterPropertyArrayWithoutAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_ARRAY_WITHOUT_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliHandleRegisterPropertyArrayWithAccessModeP
 * @since_tizen     2.4
 * @description     Register a new Array Value property with access mode.
 */
int UtcDaliHandleRegisterPropertyArrayWithAccessModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REGISTER_PROPERTY_ARRAY_WITH_ACCESSMODE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleRemoveConstraintsWithAndWithoutTagP
 * @since_tizen     2.4
 * @description     Check if RemoveConstraints can remove all constraints from an object properly with matching tags and without any tag.
 */
int UtcDaliHandleRemoveConstraintsWithAndWithoutTagP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REMOVE_CONSTRAINTS_WITH_AND_WITHOUT_TAG_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleNewWeightObjectDownCastP
 * @since_tizen     2.4
 * @description     Construct a handle object and a WeightObject having a custom weight property and DownCast WeightObject to Handle
 */
int UtcDaliHandleNewWeightObjectDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_NEW_WEIGHT_OBJECT_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleDownCastN
 * @since_tizen     2.4
 * @description     Construct a handle object and a WeightObject having a custom weight property and DownCast WeightObject to Handle
 */
int UtcDaliHandleDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliHandleRemovePropertyNotificationsP
 * @since_tizen     2.4
 * @description     Remove all added property notifications from handle.
 */
int UtcDaliHandleRemovePropertyNotificationsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Handle_TestApp testApp( application, HANDLE_REMOVE_PROPERTY_NOTIFICATIONS_P);
  application.MainLoop();
  return test_return_value;
}


