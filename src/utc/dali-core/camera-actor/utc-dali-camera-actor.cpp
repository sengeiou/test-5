#include "utc-dali-camera-actor-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: CameraActor

/**
 * @function            utc_Dali_CameraActor_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_CameraActor_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_Path_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_CameraActor_cleanup(void)
{

}

void CameraActorSetNearClippingPlaneP();
void CameraActorGetNearClippingPlaneP();
void CameraActorSetAspectRatioP();
void CameraActorGetAspectRatioP();
void CameraActorSetFieldOfViewP();
void CameraActorGetFieldOfViewP();
void CameraActorSetFarClippingPlaneP();
void CameraActorGetFarClippingPlaneP();
void CameraActorSetTargetPositionP();
void CameraActorGetTargetPositionP();
void CameraActorSetInvertYAxisP();
void CameraActorGetInvertYAxisP();
void CameraActorOperatorAssignmentP();
void CameraActorDownCastP();
void CameraActorDownCastN();
void CameraActorSetTypeP();
void CameraActorGetTypeP();
void CameraActorSetProjectionModeP();
void CameraActorGetProjectionModeP();
void CameraActorSetPerspectiveProjectionP();
void CameraActorSetOrthographicProjectionP();
void CameraActorSetOrthographicProjectionP2();
void CameraActorCopyConstructorP();
void CameraActorConstructorP();
void CameraActorNewP();
void CameraActorNewP2();

namespace
{
  enum TEST_CASES_LIST
  {
    CAMERA_ACTOR_SET_NEAR_CLIPPING_PLANE_P,
    CAMERA_ACTOR_GET_NEAR_CLIPPING_PLANE_P,
    CAMERA_ACTOR_SET_ASPECT_RATIO_P,
    CAMERA_ACTOR_GET_ASPECT_RATIO_P,
    CAMERA_ACTOR_SET_FIELD_OF_VIEW_P,
    CAMERA_ACTOR_GET_FIELD_OF_VIEW_P,
    CAMERA_ACTOR_SET_FAR_CLIPPING_PLANE_P,
    CAMERA_ACTOR_GET_FAR_CLIPPING_PLANE_P,
    CAMERA_ACTOR_SET_TARGET_POSITION_P,
    CAMERA_ACTOR_GET_TARGET_POSITION_P,
    CAMERA_ACTOR_SET_INVERT_YAXIS_P,
    CAMERA_ACTOR_GET_INVERT_YAXIS_P,
    CAMERA_ACTOR_OPERATOR_ASSIGNMENT_P,
    CAMERA_ACTOR_DOWNCAST_P,
    CAMERA_ACTOR_DOWNCAST_N,
    CAMERA_ACTOR_SET_TYPE_P,
    CAMERA_ACTOR_GET_TYPE_P,
    CAMERA_ACTOR_SET_PROJECTION_MODE_P,
    CAMERA_ACTOR_GET_PROJECTION_MODE_P,
    CAMERA_ACTOR_SET_PERSPECTIVE_PROJECTION_P,
    CAMERA_ACTOR_SET_ORTHOGRAPHIC_PROJECTION_P,
    CAMERA_ACTOR_SET_ORTHOGRAPHIC_PROJECTION_P2,
    CAMERA_ACTOR_COPY_CONSTRUCTOR_P,
    CAMERA_ACTOR_CONSTRUCTOR_P,
    CAMERA_ACTOR_NEW_P,
    CAMERA_ACTOR_NEW_P2
  };

  struct TestApp : public ConnectionTracker
  {
    TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &TestApp::Tick );
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
        case CAMERA_ACTOR_SET_NEAR_CLIPPING_PLANE_P:
          CameraActorSetNearClippingPlaneP();
          break;

        case CAMERA_ACTOR_GET_NEAR_CLIPPING_PLANE_P:
          CameraActorGetNearClippingPlaneP();
          break;

        case CAMERA_ACTOR_SET_ASPECT_RATIO_P:
          CameraActorSetAspectRatioP();
          break;

        case CAMERA_ACTOR_GET_ASPECT_RATIO_P:
          CameraActorGetAspectRatioP();
          break;

        case CAMERA_ACTOR_SET_FIELD_OF_VIEW_P:
          CameraActorSetFieldOfViewP();
          break;

        case CAMERA_ACTOR_GET_FIELD_OF_VIEW_P:
          CameraActorGetFieldOfViewP();
          break;

        case CAMERA_ACTOR_SET_FAR_CLIPPING_PLANE_P:
          CameraActorSetFarClippingPlaneP();
          break;

        case CAMERA_ACTOR_GET_FAR_CLIPPING_PLANE_P:
          CameraActorGetFarClippingPlaneP();
          break;

        case CAMERA_ACTOR_SET_TARGET_POSITION_P:
          CameraActorSetTargetPositionP();
          break;

        case CAMERA_ACTOR_GET_TARGET_POSITION_P:
          CameraActorGetTargetPositionP();
          break;

        case CAMERA_ACTOR_SET_INVERT_YAXIS_P:
          CameraActorSetInvertYAxisP();
          break;

        case CAMERA_ACTOR_GET_INVERT_YAXIS_P:
          CameraActorGetInvertYAxisP();
          break;

        case CAMERA_ACTOR_OPERATOR_ASSIGNMENT_P:
          CameraActorOperatorAssignmentP();
          break;

        case CAMERA_ACTOR_DOWNCAST_P:
          CameraActorDownCastP();
          break;

        case CAMERA_ACTOR_DOWNCAST_N:
          CameraActorDownCastN();
          break;

        case CAMERA_ACTOR_SET_TYPE_P:
          CameraActorSetTypeP();
          break;

        case CAMERA_ACTOR_GET_TYPE_P:
          CameraActorGetTypeP();
          break;

        case CAMERA_ACTOR_SET_PROJECTION_MODE_P:
          CameraActorSetProjectionModeP();
          break;

        case CAMERA_ACTOR_GET_PROJECTION_MODE_P:
          CameraActorGetProjectionModeP();
          break;

        case CAMERA_ACTOR_SET_PERSPECTIVE_PROJECTION_P:
          CameraActorSetPerspectiveProjectionP();
          break;

        case CAMERA_ACTOR_SET_ORTHOGRAPHIC_PROJECTION_P:
          CameraActorSetOrthographicProjectionP();
          break;

        case CAMERA_ACTOR_SET_ORTHOGRAPHIC_PROJECTION_P2:
          CameraActorSetOrthographicProjectionP2();
          break;

        case CAMERA_ACTOR_COPY_CONSTRUCTOR_P:
          CameraActorCopyConstructorP();
          break;

        case CAMERA_ACTOR_CONSTRUCTOR_P:
          CameraActorConstructorP();
          break;

        case CAMERA_ACTOR_NEW_P:
          CameraActorNewP();
          break;

        case CAMERA_ACTOR_NEW_P2:
          CameraActorNewP2();
          break;
      }
    }

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace



/**
 * @testcase           UtcDaliCameraActorSetNearClippingPlaneP
 * @since_tizen        2.4
 * @description        check if SetNearClippingPlace apis works or not.
 */

int UtcDaliCameraActorSetNearClippingPlaneP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_SET_NEAR_CLIPPING_PLANE_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorSetNearClippingPlaneP()
{
  const float SET_VALUE_NEAR_CLIPPING_PANE = 0.23f;
  float fGetNearClippingPlane = 0.0f;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , "New Camera Actor initialization is failed.");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created.");

  stage.Add(cameraActor);
  cameraActor.SetNearClippingPlane(SET_VALUE_NEAR_CLIPPING_PANE);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  fGetNearClippingPlane = cameraActor.GetNearClippingPlane();
  DALI_CHECK_FAIL(SET_VALUE_NEAR_CLIPPING_PANE != fGetNearClippingPlane , "Set and Get the near clipping plane distance is mismatched.");

  stage.Remove(cameraActor);
  DaliLog::PrintPass();
}


/**
 * @testcase           UtcDaliCameraActorGetNearClippingPlaneP
 * @since_tizen        2.4
 * @description        check if GetNearClippingPlace apis works or not.
 */

int UtcDaliCameraActorGetNearClippingPlaneP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_GET_NEAR_CLIPPING_PLANE_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorGetNearClippingPlaneP()
{
  const float SET_VALUE_NEAR_CLIPPING_PANE = 0.23f;
  float fGetNearClippingPlane = 0.0f;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , "New Camera Actor initialization is failed.");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created.");

  stage.Add(cameraActor);
  cameraActor.SetNearClippingPlane(SET_VALUE_NEAR_CLIPPING_PANE);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  fGetNearClippingPlane = cameraActor.GetNearClippingPlane();
  DALI_CHECK_FAIL(SET_VALUE_NEAR_CLIPPING_PANE != fGetNearClippingPlane , "Set and Get the near clipping plane distance is mismatched.");

  stage.Remove(cameraActor);
  DaliLog::PrintPass();
}


/**
 * @testcase           UtcDaliCameraActorSetAspectRatioP
 * @since_tizen        2.4
 * @description        check if SetAspectRation apis works or not.
 */

int UtcDaliCameraActorSetAspectRatioP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_SET_ASPECT_RATIO_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorSetAspectRatioP()
{
  float fGetAspectRatio = 0.0f ;
  const float fSetAspectRatio = 0.123f ;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  cameraActor.SetAspectRatio(fSetAspectRatio);

  fGetAspectRatio = cameraActor.GetAspectRatio();
  DALI_CHECK_FAIL(fSetAspectRatio != fGetAspectRatio , "Set Aspect  and Get Aspect Ratio is mismatched");

  stage.Remove(cameraActor);
  DaliLog::PrintPass();
}


/**
 * @testcase           UtcDaliCameraActorGetAspectRatioP
 * @since_tizen        2.4
 * @description        check if GetAspectRatio apis works or not.
 */

int UtcDaliCameraActorGetAspectRatioP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_GET_ASPECT_RATIO_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorGetAspectRatioP()
{
  float fGetAspectRatio = 0.0f ;
  const float fSetAspectRatio = 0.123f ;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  cameraActor.SetAspectRatio(fSetAspectRatio);

  fGetAspectRatio = cameraActor.GetAspectRatio();
  DALI_CHECK_FAIL(fSetAspectRatio != fGetAspectRatio , "Set Aspect  and Get Aspect Ratio is mismatched");

  stage.Remove(cameraActor);
  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorSetFieldOfViewP
 * @since_tizen        2.4
 * @description        check if SetFieldOfView api works or not.
 */

int UtcDaliCameraActorSetFieldOfViewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_SET_FIELD_OF_VIEW_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorSetFieldOfViewP()
{
  float fGetFieldOfView = 0.0f ;
  const float fSetFieldOfView = Radian(Degree(40.0f));

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  cameraActor.SetFieldOfView(fSetFieldOfView);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  fGetFieldOfView = cameraActor.GetFieldOfView();
  DALI_CHECK_FAIL(fSetFieldOfView != fGetFieldOfView , "Set  and Get the field of view is mismatched");

  stage.Remove(cameraActor);
  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorGetFieldOfViewP
 * @since_tizen        2.4
 * @description        check if GetFieldOfView api works or not.
 */

int UtcDaliCameraActorGetFieldOfViewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_GET_FIELD_OF_VIEW_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorGetFieldOfViewP()
{
  float fGetFieldOfView = 0.0f ;
  const float fSetFieldOfView = Radian(Degree(40.0f));

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  cameraActor.SetFieldOfView(fSetFieldOfView);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  fGetFieldOfView = cameraActor.GetFieldOfView();
  DALI_CHECK_FAIL(fSetFieldOfView != fGetFieldOfView , "Set  and Get the field of view is mismatched");

  stage.Remove(cameraActor);
  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorSetFarClippingPlaneP
 * @since_tizen        2.4
 * @description        check if SetFarClippingPlane api works or not.
 */

int UtcDaliCameraActorSetFarClippingPlaneP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_SET_FAR_CLIPPING_PLANE_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorSetFarClippingPlaneP()
{
  float fGetFarClippingPlane = 0.0f ;
  const float fSetFarClippingPlane = 0.23f;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  cameraActor.SetFarClippingPlane(fSetFarClippingPlane);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  fGetFarClippingPlane = cameraActor.GetFarClippingPlane();
  DALI_CHECK_FAIL(fSetFarClippingPlane != fGetFarClippingPlane , "Set  and Get the far clipping plane distance is mismatched");

  stage.Remove(cameraActor);

  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorGetFarClippingPlaneP
 * @since_tizen        2.4
 * @description        check if GetFarClippingPlane api works or not.
 */

int UtcDaliCameraActorGetFarClippingPlaneP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_GET_FAR_CLIPPING_PLANE_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorGetFarClippingPlaneP()
{
  float fGetFarClippingPlane = 0.0f ;
  const float fSetFarClippingPlane = 0.23f;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  cameraActor.SetFarClippingPlane(fSetFarClippingPlane);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  fGetFarClippingPlane = cameraActor.GetFarClippingPlane();
  DALI_CHECK_FAIL(fSetFarClippingPlane != fGetFarClippingPlane , "Set  and Get the far clipping plane distance is mismatched");

  stage.Remove(cameraActor);

  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorSetTargetPositionP
 * @since_tizen        2.4
 * @description        check if SetTargetPosition api works or not.
 */

int UtcDaliCameraActorSetTargetPositionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_SET_TARGET_POSITION_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorSetTargetPositionP()
{
  const float fX = 10.0f , fY = 20.0f , fZ = 30.f;
  Vector3 vec3GetTargetPosition(0.0f,0.0f,0.0f) ;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  Vector3 vec3SetTargetPosition(fX , fY , fZ);
  cameraActor.SetTargetPosition(vec3SetTargetPosition);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  vec3GetTargetPosition = cameraActor.GetTargetPosition();
  DALI_CHECK_FAIL(vec3SetTargetPosition.x != vec3GetTargetPosition.x , "Set  and Get the target X positition is mismatched");
  DALI_CHECK_FAIL(vec3SetTargetPosition.y != vec3GetTargetPosition.y , "Set  and Get the target Y positition is mismatched");
  DALI_CHECK_FAIL(vec3SetTargetPosition.z != vec3GetTargetPosition.z , "Set  and Get the target Z positition is mismatched");

  stage.Remove(cameraActor);

  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorGetTargetPositionP
 * @since_tizen        2.4
 * @description        check if GetTargetPosition api works or not.
 */

int UtcDaliCameraActorGetTargetPositionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_GET_TARGET_POSITION_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorGetTargetPositionP()
{
  const float fX = 10.0f , fY = 20.0f , fZ = 30.f;
  Vector3 vec3GetTargetPosition(0.0f,0.0f,0.0f) ;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  Vector3 vec3SetTargetPosition(fX , fY , fZ);
  cameraActor.SetTargetPosition(vec3SetTargetPosition);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  vec3GetTargetPosition = cameraActor.GetTargetPosition();
  DALI_CHECK_FAIL(vec3SetTargetPosition.x != vec3GetTargetPosition.x , "Set  and Get the target X positition is mismatched");
  DALI_CHECK_FAIL(vec3SetTargetPosition.y != vec3GetTargetPosition.y , "Set  and Get the target Y positition is mismatched");
  DALI_CHECK_FAIL(vec3SetTargetPosition.z != vec3GetTargetPosition.z , "Set  and Get the target Z positition is mismatched");

  stage.Remove(cameraActor);

  DaliLog::PrintPass();
}




/**
 * @testcase           UtcDaliCameraActorSetInvertYAxisP
 * @since_tizen        2.4
 * @description        check if SetInvertYAxis api works or not.
 */

int UtcDaliCameraActorSetInvertYAxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_SET_INVERT_YAXIS_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorSetInvertYAxisP()
{
  bool bSetInvertYAxis = false ;
  bool bGetInvertYAxis = false ;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  cameraActor.SetInvertYAxis(bSetInvertYAxis);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  bGetInvertYAxis = cameraActor.GetInvertYAxis();
  DALI_CHECK_FAIL(bSetInvertYAxis != bGetInvertYAxis , "Set  and Get whether the Y axis is inverted is mismatched");

  stage.Remove(cameraActor);

  DaliLog::PrintPass();
}




/**
 * @testcase           UtcDaliCameraActorGetInvertYAxisP
 * @since_tizen        2.4
 * @description        check if GetInvertYAxis api works or not.
 */

int UtcDaliCameraActorGetInvertYAxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_GET_INVERT_YAXIS_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorGetInvertYAxisP()
{
  bool bSetInvertYAxis = false ;
  bool bGetInvertYAxis = false ;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  cameraActor.SetInvertYAxis(bSetInvertYAxis);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  bGetInvertYAxis = cameraActor.GetInvertYAxis();
  DALI_CHECK_FAIL(bSetInvertYAxis != bGetInvertYAxis , "Set  and Get whether the Y axis is inverted is mismatched");

  stage.Remove(cameraActor);

  DaliLog::PrintPass();
}




/**
 * @testcase           UtcDaliCameraActorOperatorAssignmentP
 * @since_tizen        2.4
 * @description        check if operator=() works or not.
 */

int UtcDaliCameraActorOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorOperatorAssignmentP()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  stage.Add(cameraActor);

  CameraActor* OperatorCameraActor =&cameraActor;
  DALI_CHECK_FAIL(OperatorCameraActor == NULL, " CameraActor Assignment is Failed ");

  stage.Remove(cameraActor);

  DaliLog::PrintPass();
}




/**
 * @testcase           UtcDaliCameraActorDownCastP
 * @since_tizen        2.4
 * @description        check if Downcast api works or not.
 */

int UtcDaliCameraActorDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorDownCastP()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  stage.Add(cameraActor);

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, " Actor::New() is failed ");

  actor.Add(cameraActor);
  DALI_CHECK_FAIL(!CameraActorHasAncestor(cameraActor , actor), " Actor::New() is failed ");

  Actor childActor = actor.GetChildAt(0);
  DALI_CHECK_FAIL(!childActor, " actor.GetChildAt() is failed ");

  CameraActor downCastCameraActor = CameraActor::DownCast( childActor );
  DALI_CHECK_FAIL(!downCastCameraActor, "Failed to Downcast an Object handle to CameraActor");

  UnparentAndReset(downCastCameraActor);

  DaliLog::PrintPass();
}




/**
 * @testcase           UtcDaliCameraActorDownCastN
 * @since_tizen        2.4
 * @description        check if Downcast api works or not.
 */

int UtcDaliCameraActorDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}

void CameraActorDownCastN()
{

  Actor childActor;
  CameraActor downCastCameraActor = CameraActor::DownCast( childActor );
  DALI_CHECK_FAIL( downCastCameraActor, "Failed to Downcast an Object handle to CameraActor");

  DaliLog::PrintPass();
}


/**
 * @testcase           UtcDaliCameraActorSetTypeP
 * @since_tizen        2.4
 * @description        check if SetType api works or not.
 */

int UtcDaliCameraActorSetTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_SET_TYPE_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorSetTypeP()
{
  Dali::Camera::Type typeGet ;
  Dali::Camera::Type typeSet = Camera::LOOK_AT_TARGET;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  cameraActor.SetType(typeSet);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  typeGet = cameraActor.GetType();
  DALI_CHECK_FAIL(typeSet != typeGet , "Set  and Get Camera type is mismatched");

  stage.Remove(cameraActor);

  DaliLog::PrintPass();
}




/**
 * @testcase           UtcDaliCameraActorGetTypeP
 * @since_tizen        2.4
 * @description        check if GetType api works or not.
 */

int UtcDaliCameraActorGetTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_GET_TYPE_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorGetTypeP()
{
  Dali::Camera::Type typeGet ;
  Dali::Camera::Type typeSet = Camera::LOOK_AT_TARGET;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  cameraActor.SetType(typeSet);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  typeGet = cameraActor.GetType();
  DALI_CHECK_FAIL(typeSet != typeGet , "Set  and Get Camera type is mismatched");

  stage.Remove(cameraActor);

  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorSetProjectionModeP
 * @since_tizen        2.4
 * @description        check if SetProjectionMode api works or not.
 */

int UtcDaliCameraActorSetProjectionModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_SET_PROJECTION_MODE_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorSetProjectionModeP()
{
  const float fDegreeOfView =  40.0f , fAspectRatio = 3.14f , fNearClippingPlaneDistance =  0.23f , fFarClippingPlaneDistance = 6.98f;

  Dali::Camera::ProjectionMode projectionModeSet = Camera::PERSPECTIVE_PROJECTION;
  Dali::Camera::ProjectionMode projectionModeGet;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );

  cameraActor.SetType(Camera::FREE_LOOK);
  DALI_CHECK_FAIL(Camera::FREE_LOOK !=  cameraActor.GetType(), " cameraActor.GetType()/SetType() is failed ");

  cameraActor.SetFieldOfView(Radian(Degree(fDegreeOfView)) ) ;
  DALI_CHECK_FAIL( cameraActor.GetFieldOfView() != Radian(Degree(fDegreeOfView)) , " cameraActor.SetFieldOfView()/SetFieldOfView() is failed ");

  cameraActor.SetAspectRatio(fAspectRatio);
  DALI_CHECK_FAIL( cameraActor.GetAspectRatio() != fAspectRatio, " cameraActor.SetAspectRatio()/GetAspectRatio() is failed ");

  cameraActor.SetNearClippingPlane(fNearClippingPlaneDistance);
  cameraActor.SetFarClippingPlane(fFarClippingPlaneDistance);

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");
  stage.Add(cameraActor);

  cameraActor.SetProjectionMode(projectionModeSet);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  projectionModeGet = cameraActor.GetProjectionMode();
  DALI_CHECK_FAIL(projectionModeSet != projectionModeGet , "Set  and Get projection mode is mismatched");

  stage.Remove(cameraActor);

  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorGetProjectionModeP
 * @since_tizen        2.4
 * @description        check if GetProjectionMode api works or not.
 */

int UtcDaliCameraActorGetProjectionModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_GET_PROJECTION_MODE_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorGetProjectionModeP()
{
  const float fDegreeOfView =  40.0f , fAspectRatio = 3.14f , fNearClippingPlaneDistance =  0.23f , fFarClippingPlaneDistance = 6.98f;

  Dali::Camera::ProjectionMode projectionModeSet = Camera::PERSPECTIVE_PROJECTION;
  Dali::Camera::ProjectionMode projectionModeGet;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );

  cameraActor.SetType(Camera::FREE_LOOK);
  DALI_CHECK_FAIL(Camera::FREE_LOOK !=  cameraActor.GetType(), " cameraActor.GetType()/SetType() is failed ");

  cameraActor.SetFieldOfView(Radian(Degree(fDegreeOfView)) ) ;
  DALI_CHECK_FAIL( cameraActor.GetFieldOfView() != Radian(Degree(fDegreeOfView)) , " cameraActor.SetFieldOfView()/SetFieldOfView() is failed ");

  cameraActor.SetAspectRatio(fAspectRatio);
  DALI_CHECK_FAIL( cameraActor.GetAspectRatio() != fAspectRatio, " cameraActor.SetAspectRatio()/GetAspectRatio() is failed ");

  cameraActor.SetNearClippingPlane(fNearClippingPlaneDistance);
  cameraActor.SetFarClippingPlane(fFarClippingPlaneDistance);

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");
  stage.Add(cameraActor);

  cameraActor.SetProjectionMode(projectionModeSet);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  projectionModeGet = cameraActor.GetProjectionMode();
  DALI_CHECK_FAIL(projectionModeSet != projectionModeGet , "Set  and Get projection mode is mismatched");

  stage.Remove(cameraActor);

  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorSetPerspectiveProjectionP
 * @since_tizen        2.4
 * @description        check if SetPerspectiveProjection api works or not.
 */

int UtcDaliCameraActorSetPerspectiveProjectionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_SET_PERSPECTIVE_PROJECTION_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorSetPerspectiveProjectionP()
{
  const Size size  = Size( 100.f, 150.f);
  const float fPerspetiveProjectionRatio = 0.666666f, fFieldofViewRatio = 0.489957f, fNearClippingPlane = 150.0f, fFarClippingPlane = 4245.0f;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  cameraActor.SetParentOrigin( ParentOrigin::CENTER );
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  stage.Add(cameraActor);
  RenderTaskList renderTaskList = stage.GetRenderTaskList();
  renderTaskList.GetTask(TASK_NUMBER).SetCameraActor( cameraActor );

  try
  {
    cameraActor.SetPerspectiveProjection(size);
  }
  catch ( DaliException& e )
  {
    LOG_E(" SetPerspectiveProjection() is Failed ");
    test_return_value = TC_FAIL;
    return;
  }

  DALI_CHECK_FAIL( fabs(cameraActor.GetAspectRatio() - fPerspetiveProjectionRatio) > CAMERAACTOR_EPSYLON , "  Seting Aspect ratio value is Failed ");
  DALI_CHECK_FAIL( fabs(cameraActor.GetFieldOfView()- fFieldofViewRatio) > CAMERAACTOR_EPSYLON , "   Setting  exact field of view is failed   ");
  DALI_CHECK_FAIL( fabs(cameraActor.GetNearClippingPlane() - fNearClippingPlane) > CAMERAACTOR_EPSYLON , "   Setting  near clipping plane is failed   ");
  DALI_CHECK_FAIL( fabs(cameraActor.GetFarClippingPlane() - fFarClippingPlane) > CAMERAACTOR_EPSYLON , "   Setting  far clipping plane is failed   ");

  stage.Remove(cameraActor);
  DaliLog::PrintPass();
}




/**
 * @testcase           UtcDaliCameraActorSetOrthographicProjectionP
 * @since_tizen        2.4
 * @description        check if SetOrthographicProjection api works or not.
 */

int UtcDaliCameraActorSetOrthographicProjectionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_SET_ORTHOGRAPHIC_PROJECTION_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorSetOrthographicProjectionP()
{
  float fLeftPlaneDistance = 0.0f , fRightPlaneDistance = 0.0f ,fTopPlaneDistance = 0.0f , fBottomPlaneDistance = 0.0f ;
  const float fXPlane = IMAGE_WIDTH , fYPlane = IMAGE_HEIGHT , fImageHeight = IMAGE_HEIGHT, fImageWidth = IMAGE_WIDTH  ;

  CameraActor cameraActor = CameraActor::New( Size(fImageWidth, fImageHeight) );
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");


  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");
  stage.Add(cameraActor);

  try
  {
    cameraActor.SetOrthographicProjection( Size( fXPlane, fYPlane ) );
  }
  catch ( DaliException& e )
  {
    LOG_E(" SetPerspectiveProjection() is Failed ");
    test_return_value = TC_FAIL;
    return;
  }

  cameraActor.GetProperty(CameraActor::Property::LEFT_PLANE_DISTANCE).Get(fLeftPlaneDistance);
  DALI_CHECK_FAIL( fabs(fLeftPlaneDistance - (-fXPlane/2)) > CAMERAACTOR_EPSYLON , "  Setting  left clipping plane is failed  ");

  cameraActor.GetProperty(CameraActor::Property::RIGHT_PLANE_DISTANCE).Get(fRightPlaneDistance);
  DALI_CHECK_FAIL( fabs(fRightPlaneDistance - fXPlane/2 ) > CAMERAACTOR_EPSYLON , "   Setting  right clipping plane is failed    ");

  cameraActor.GetProperty(CameraActor::Property::TOP_PLANE_DISTANCE).Get(fTopPlaneDistance);
  DALI_CHECK_FAIL( fabs(fTopPlaneDistance - fYPlane/2) > CAMERAACTOR_EPSYLON , "   Setting  near clipping plane is failed   ");

  cameraActor.GetProperty(CameraActor::Property::BOTTOM_PLANE_DISTANCE).Get(fBottomPlaneDistance);
  DALI_CHECK_FAIL( fabs(fBottomPlaneDistance - (-fYPlane/2)) > CAMERAACTOR_EPSYLON , "   Setting  far clipping plane is failed   ");

  stage.Remove(cameraActor);
  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorSetOrthographicProjectionP2
 * @since_tizen        2.4
 * @description        check if SetOrthographicProjection api works or not.
 */

int UtcDaliCameraActorSetOrthographicProjectionP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_SET_ORTHOGRAPHIC_PROJECTION_P2);
  application.MainLoop();
  return test_return_value;
}

void CameraActorSetOrthographicProjectionP2()
{
  const float fSetLeftPlaneDistance = -100.0f , fSetRightPlaneDistance = 200.0f ,fSetTopPlaneDistance = -300.0f , fSetBottomPlaneDistance = 500.0f , fSetNearPlaneDistance = 400.0f , fSetFarPlaneDistance = 4000.0f ;
  float fGetLeftPlaneDistance = 0.0f, fGetRightPlaneDistance = 0.0f ,fGetTopPlaneDistance = 0.0f, fGetBottomPlaneDistance = 0.0f, fGetNearPlaneDistance = 0.0f , fGetFarPlaneDistance = 0.0f;
  const float  fImageHeight = IMAGE_HEIGHT, fImageWidth = IMAGE_WIDTH  ;

  CameraActor cameraActor = CameraActor::New( Size(fImageWidth, fImageHeight) );
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");
  stage.Add(cameraActor);

  try
  {
    cameraActor.SetOrthographicProjection( fSetLeftPlaneDistance ,fSetRightPlaneDistance,fSetTopPlaneDistance, fSetBottomPlaneDistance, fSetNearPlaneDistance, fSetFarPlaneDistance );
  }
  catch ( DaliException& e )
  {
    LOG_E(" SetOrthographicProjection() is Failed ");
    test_return_value = TC_FAIL;
    return;
  }

  cameraActor.GetProperty(CameraActor::Property::LEFT_PLANE_DISTANCE).Get(fGetLeftPlaneDistance);
  DALI_CHECK_FAIL( fabs(fGetLeftPlaneDistance - (fSetLeftPlaneDistance)) > CAMERAACTOR_EPSYLON , "  Seting left clipping plane is failed ");

  cameraActor.GetProperty(CameraActor::Property::RIGHT_PLANE_DISTANCE).Get(fGetRightPlaneDistance);
  DALI_CHECK_FAIL( fabs(fGetRightPlaneDistance - fSetRightPlaneDistance ) > CAMERAACTOR_EPSYLON , "   Setting  right clipping plane is failed   ");

  cameraActor.GetProperty(CameraActor::Property::TOP_PLANE_DISTANCE).Get(fGetTopPlaneDistance);
  DALI_CHECK_FAIL( fabs(fGetTopPlaneDistance - (fSetTopPlaneDistance)) > CAMERAACTOR_EPSYLON , "   Setting  top clipping plane is failed   ");

  cameraActor.GetProperty(CameraActor::Property::BOTTOM_PLANE_DISTANCE).Get(fGetBottomPlaneDistance);
  DALI_CHECK_FAIL( fabs(fGetBottomPlaneDistance - fSetBottomPlaneDistance) > CAMERAACTOR_EPSYLON , "   Setting  bottom clipping plane is failed   ");

  cameraActor.GetProperty(CameraActor::Property::NEAR_PLANE_DISTANCE).Get(fGetNearPlaneDistance);
  DALI_CHECK_FAIL( fabs(fGetNearPlaneDistance - fSetNearPlaneDistance ) > CAMERAACTOR_EPSYLON , "   Setting  Near clipping plane is failed   ");

  cameraActor.GetProperty(CameraActor::Property::FAR_PLANE_DISTANCE).Get(fGetFarPlaneDistance);
  DALI_CHECK_FAIL( fabs(fGetFarPlaneDistance - fSetFarPlaneDistance ) > CAMERAACTOR_EPSYLON , "   Setting  far clipping plane is failed   ");

  stage.Remove(cameraActor);
  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorCopyConstructorP
 * @since_tizen        2.4
 * @description        check if copy constructor works or not.
 */

int UtcDaliCameraActorCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorCopyConstructorP()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  CameraActor cameraActor;
  DALI_CHECK_FAIL(cameraActor , "CameraActor() failed to create un initialized object.");

  Size size = Size(480.0f, 320.0f);
  CameraActor cameraActorMain = CameraActor::New(size);
  DALI_CHECK_FAIL( !cameraActorMain , " New Camera Actor initialization is failed ");

  cameraActorMain.SetParentOrigin( ParentOrigin::CENTER );
  stage.Add(cameraActorMain);

  cameraActor = CameraActor(cameraActorMain);

  DALI_CHECK_FAIL(cameraActor != cameraActorMain, "CameraActor Copy constructor failed.");

  stage.Remove(cameraActor);

  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorConstructorP
 * @since_tizen        2.4
 * @description        check if default constructor works or not.
 */

int UtcDaliCameraActorConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorConstructorP()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  CameraActor cameraActor;
  DALI_CHECK_FAIL(cameraActor , "CameraActor() failed to create un initialized object.");

  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorNewP
 * @since_tizen        2.4
 * @description        check if New api works or not.
 */

int UtcDaliCameraActorNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_NEW_P);
  application.MainLoop();
  return test_return_value;
}

void CameraActorNewP()
{
  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL( !cameraActor , " New Camera Actor initialization is failed ");

  DaliLog::PrintPass();
}



/**
 * @testcase           UtcDaliCameraActorNewP2
 * @since_tizen        2.4
 * @description        check if New api works or not.
 */

int UtcDaliCameraActorNewP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CAMERA_ACTOR_NEW_P2);
  application.MainLoop();
  return test_return_value;
}

void CameraActorNewP2()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created ");

  CameraActor cameraActor;
  DALI_CHECK_FAIL(cameraActor , "CameraActor() failed to create un initialized object.");

  Size size = Size(480.0f, 320.0f);
  CameraActor cameraActorMain = CameraActor::New(size);
  DALI_CHECK_FAIL( !cameraActorMain , " New Camera Actor initialization is failed ");

  DaliLog::PrintPass();
}
