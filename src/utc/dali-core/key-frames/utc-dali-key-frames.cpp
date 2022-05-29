#include "utc-dali-key-frames-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Keyframes

/**
 * @function            utc_Dali_KeyFrames_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_KeyFrames_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_KeyFrames_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_KeyFrames_cleanup(void)
{
}


void KeyFramesNewP();
void KeyFramesDowncastP();
void KeyFramesDowncastN();
void KeyFramesConstructorP();
void KeyFramesCopyConstructorP();
void KeyFramesAssignmentOperatorP();
void KeyFramesAddWithAlphaFunctionP();
void KeyFramesAddGetTypeWithBoolP();
void KeyFramesAddGetTypeWithFloatP();
void KeyFramesAddGetTypeWithVector2P();
void KeyFramesAddGetTypeWithVector3P();
void KeyFramesAddGetTypeWithVector4P();
void KeyFramesAddGetTypeWithAngleAxisP();

namespace
{
  enum TEST_CASES_LIST_KEY_FRAMES
  {
    KEY_FRAMES_NEW_P,
    KEY_FRAMES_DOWNCAST_P,
    KEY_FRAMES_DOWNCAST_N,
    KEY_FRAMES_CONSTRUCTOR_P,
    KEY_FRAMES_COPY_CONSTRUCTOR_P,
    KEY_FRAMES_ASSIGNMENT_OPERATOR_P,
    KEY_FRAMES_ADD_WITH_ALPHA_FUNCTION_P,
    KEY_FRAMES_ADD_GET_TYPE_WITH_BOOL_P,
    KEY_FRAMES_ADD_GET_TYPE_WITH_FLOAT_P,
    KEY_FRAMES_ADD_GET_TYPE_WITH_VECTOR2_P,
    KEY_FRAMES_ADD_GET_TYPE_WITH_VECTOR3_P,
    KEY_FRAMES_ADD_GET_TYPE_WITH_VECTOR4_P,
    KEY_FRAMES_ADD_GET_TYPE_WITH_ANGLE_AXIS_P,
    KEY_FRAMES_ADD_GET_TYPE_WITH_RECT_P
  };

  struct Key_Frames_TestApp : public ConnectionTracker
  {
    Key_Frames_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Key_Frames_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Key_Frames_TestApp::Tick );
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

        case KEY_FRAMES_ADD_WITH_ALPHA_FUNCTION_P:
          KeyFramesAddWithAlphaFunctionP();
          break;

        case KEY_FRAMES_NEW_P:
          KeyFramesDowncastP();
          break;

        case KEY_FRAMES_DOWNCAST_P:
          KeyFramesDowncastP();
          break;

        case KEY_FRAMES_DOWNCAST_N:
          KeyFramesDowncastN();
          break;

        case KEY_FRAMES_CONSTRUCTOR_P:
          KeyFramesCopyConstructorP();
          break;

        case KEY_FRAMES_COPY_CONSTRUCTOR_P:
          KeyFramesCopyConstructorP();
          break;

        case KEY_FRAMES_ADD_GET_TYPE_WITH_BOOL_P:
          KeyFramesAddGetTypeWithBoolP();
          break;

        case KEY_FRAMES_ADD_GET_TYPE_WITH_FLOAT_P:
          KeyFramesAddGetTypeWithFloatP();
          break;

        case KEY_FRAMES_ADD_GET_TYPE_WITH_VECTOR2_P:
          KeyFramesAddGetTypeWithVector2P();
          break;

        case KEY_FRAMES_ADD_GET_TYPE_WITH_VECTOR3_P:
          KeyFramesAddGetTypeWithVector3P();
          break;

        case KEY_FRAMES_ADD_GET_TYPE_WITH_VECTOR4_P:
          KeyFramesAddGetTypeWithVector4P();
          break;

        case KEY_FRAMES_ADD_GET_TYPE_WITH_ANGLE_AXIS_P:
          KeyFramesAddGetTypeWithAngleAxisP();
          break;

        case KEY_FRAMES_ASSIGNMENT_OPERATOR_P:
          KeyFramesAssignmentOperatorP();
          break;
      }
    }

    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

} // unnamed namespace


void KeyFramesNewP()
{
  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "keyFrames::New() is failed" );

  DaliLog::PrintPass();
}


void KeyFramesDowncastP()
{
  float fVal =0.0f,fValY=0.1f;
  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "keyFrames::New() is failed" );
  keyFrames.Add(fVal, fValY);
  BaseHandle baseHandle(keyFrames);

  KeyFrames keyFramesDownCast = KeyFrames::DownCast(baseHandle);
  DALI_CHECK_FAIL(!keyFramesDownCast, "keyFrames() DownCast is failed" );

  DALI_CHECK_FAIL(keyFramesDownCast.GetType()!=Property::FLOAT, "keyFrames() DownCast is failed to retrive Get Value " );

  DaliLog::PrintPass();
}

void KeyFramesDowncastN()
{
  KeyFrames keyFrames2;
  BaseHandle baseHandle = keyFrames2;
  DALI_CHECK_FAIL(baseHandle, "BaseHandle is empty");

  KeyFrames keyFramesDownCast = KeyFrames::DownCast(baseHandle);
  DALI_CHECK_FAIL(keyFramesDownCast, "keyFrames() DownCast is failed");

  DaliLog::PrintPass();
}

void KeyFramesConstructorP()
{
  KeyFrames keyFrames;
  DALI_CHECK_FAIL(keyFrames, "KeyFrames::KeyFrames() is failed ." );

  DaliLog::PrintPass();
}


void KeyFramesCopyConstructorP()
{
  float fVal =0.0f,fValY=0.1f;

  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "keyFrames::New() is failed ." );
  keyFrames.Add(fVal, fValY);

  KeyFrames keyFramesCopyConst(keyFrames);
  DALI_CHECK_FAIL(!keyFramesCopyConst, "keyFrames() copyconstructor  is failed " );

  DALI_CHECK_FAIL(keyFramesCopyConst.GetType()!=Property::FLOAT, "keyFrames() copyconstructor is failed to retrive Get Value " );

  DaliLog::PrintPass();
}

void KeyFramesAddWithAlphaFunctionP()
{
  bool bPropTypeSet= true;

  float fVal =0.0f;
  Property::Type setType = Property::BOOLEAN;
  Property::Type getType;
  Property::Value value(bPropTypeSet);
  AlphaFunction setAlphaFunction = AlphaFunction::DEFAULT ;

  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "keyFrames::New() is failed" );

  keyFrames.Add(fVal,value,setAlphaFunction);
  getType= keyFrames.GetType();
  DALI_CHECK_FAIL(getType!=setType, "property is Not Matched With Target Type" );

  DaliLog::PrintPass();
}


void KeyFramesAddGetTypeWithBoolP()
{
  float fVal =0.0f;
  bool bPropTypeSet= true;

  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "keyFrames::New() is failed" );

  Property::Value value(bPropTypeSet);

  if(!KeyFramesWithDiffPropValue(keyFrames,value,fVal))
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void KeyFramesAddGetTypeWithFloatP()
{
  float fVal =0.0f;
  float fSetFloat= 0.5f;

  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "keyFrames::New() is failed" );

  Property::Value value(fSetFloat);

  if(!KeyFramesWithDiffPropValue(keyFrames,value,fVal))
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void KeyFramesAddGetTypeWithVector2P()
{
  float fVal =0.0f,fXx=0.4,fYy=0.5f;

  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "keyFrames::New() is failed ." );

  Vector2 vec2Set(fXx,fYy);
  Property::Value value(vec2Set);

  if(!KeyFramesWithDiffPropValue(keyFrames,value,fVal))
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void KeyFramesAddGetTypeWithVector3P()
{
  float fVal =0.0f,fXx=0.4,fYy=0.5f,fZz=0.6f;

  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "keyFrames::New() is failed " );

  Vector3 vec3Set(fXx,fYy,fZz);
  Property::Value value(vec3Set);
  if(!KeyFramesWithDiffPropValue(keyFrames,value,fVal))
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void KeyFramesAddGetTypeWithVector4P()
{
  float fVal =0.0f,fXx=0.4,fYy=0.5f,fZz=0.6f,fWw=0.3f;

  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "keyFrames::New() is failed" );

  Vector4 vec4Set(fXx,fYy,fWw,fZz);
  Property::Value value(vec4Set);
  if(!KeyFramesWithDiffPropValue(keyFrames,value,fVal))
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}


void KeyFramesAddGetTypeWithAngleAxisP()
{
  float fVal =0.0f;
  Degree deg(75.0f);
  Vector3 vec3Value(5.0f, 5.0f, 5.0f);

  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "keyFrames::New() is failed" );

  AngleAxis angleSetValue(deg, vec3Value);
  Property::Value value(angleSetValue);
  if(!KeyFramesWithDiffPropValue(keyFrames,value,fVal))
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void KeyFramesAssignmentOperatorP()
{
  float fVal =0.0f,fValY=0.1f;

  KeyFrames keyFrames = KeyFrames::New();
  DALI_CHECK_FAIL(!keyFrames, "keyFrames::New() is failed " );
  keyFrames.Add(fVal, fValY);

  KeyFrames* keyFramesAssign = &keyFrames ;
  DALI_CHECK_FAIL(!keyFramesAssign, "keyFrames() Assignmentoperator  is failed" );

  DaliLog::PrintPass();
}


/**
 * @testcase                 UtcDaliKeyFramesNewP
 * @since_tizen              2.4
 * @description              Create a KeyFrames handle using New static method.
 */
int UtcDaliKeyFramesNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_NEW_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                 UtcDaliKeyFramesDownCastP
 * @since_tizen              2.4
 * @description              To Check keyFrames DownCast  Api is working properly or not.
 */
int UtcDaliKeyFramesDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase                 UtcDaliKeyFramesDownCastN
 * @since_tizen              2.4
 * @description              To Check keyFrames DownCast  Api is working properly or not.
 */
int UtcDaliKeyFramesDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                 UtcDaliKeyFramesConstructorP
 * @since_tizen              2.4
 * @description              To Check keyFrames CopyConstructor  Api is working properly or not.
 */
int UtcDaliKeyFramesConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                 UtcDaliKeyFramesCopyConstructorP
 * @since_tizen              2.4
 * @description              To Check keyFrames CopyConstructor  Api is working properly or not.
 */
int UtcDaliKeyFramesCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                 UtcDaliKeyFramesAddwithalphafunctionP
 * @since_tizen              2.4
 * @description              To Check keyFrames Add and getType  Api is working properly for alpha function EaseIn.
 */
int UtcDaliKeyFramesAddwithalphafunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_ADD_WITH_ALPHA_FUNCTION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                 UtcDaliKeyFramesAddGetTypewithboolP
 * @since_tizen              2.4
 * @description              To Check keyFrames Add and getType  Api is working properly for BOOL.
 */
int UtcDaliKeyFramesAddGetTypewithboolP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_ADD_GET_TYPE_WITH_BOOL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                 UtcDaliKeyFramesAddGetTypewithfloatP
 * @since_tizen              2.4
 * @description              To Check keyFrames Add and getType  Api is working properly for float.
 */
int UtcDaliKeyFramesAddGetTypewithfloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_ADD_GET_TYPE_WITH_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                 UtcDaliKeyFramesAddGetTypewithvector2P
 * @since_tizen              2.4
 * @description              To Check keyFrames Add and getType  Api is working properly for vector2.
 */
int UtcDaliKeyFramesAddGetTypewithvector2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_ADD_GET_TYPE_WITH_VECTOR2_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                 UtcDaliKeyFramesAddGetTypewithvector3P
 * @since_tizen              2.4
 * @description              To Check keyFrames Add and getType  Api is working properly for vector3.
 */
int UtcDaliKeyFramesAddGetTypewithvector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_ADD_GET_TYPE_WITH_VECTOR3_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                 UtcDaliKeyFramesAddGetTypewithvector4P
 * @since_tizen              2.4
 * @description              To Check keyFrames Add and getType  Api is working properly for vector4.
 */
int UtcDaliKeyFramesAddGetTypewithvector4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_ADD_GET_TYPE_WITH_VECTOR4_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                 UtcDaliKeyFramesAddGetTypewithangleaxisP
 * @since_tizen              2.4
 * @description              To Check keyFrames Add and getType  Api is working properly for AngleAxis.
 */
int UtcDaliKeyFramesAddGetTypewithangleaxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_ADD_GET_TYPE_WITH_ANGLE_AXIS_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase                 UtcDaliKeyFramesOperatorAssignmentP
 * @since_tizen              2.4
 * @description              To Check keyFrames Assignmentoperator  Api is working properly or not.
 */

int UtcDaliKeyFramesOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Key_Frames_TestApp testApp( application, KEY_FRAMES_ASSIGNMENT_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}

