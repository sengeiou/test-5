#include "utc-dali-path-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Path_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Path_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_Path_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Path_cleanup(void)
{
}


void PathNewP();
void PathConstructorP();
void PathCopyConstructorP();
void PathDownCastP();
void PathDownCastN();
void PathGetPointP();
void PathGetPointN();
void PathGetPointN2();
void PathGetControlPointP();
void PathGetControlPointN();
void PathGetControlPointN2();
void PathGenerateControlPointsP();
void PathGetPointsCountP();
void PathSampleP();

namespace
{
  enum TEST_CASES_LIST_PATH
  {
    PATH_NEW_P,
    PATH_CONSTRUCTOR_P,
    PATH_COPYCONSTRUCTOR_P,
    PATH_DOWNCAST_P,
    PATH_DOWNCAST_N,
    PATH_GET_POINT_P,
    PATH_GET_POINT_N,
    PATH_GET_POINT_N2,
    PATH_GET_CONTROL_POINT_P,
    PATH_GET_CONTROL_POINT_N,
    PATH_GET_CONTROL_POINT_N2,
    PATH_GENERATE_CONTROL_POINTS_P,
    PATH_GET_POINTS_COUNT_P,
    PATH_SAMPLE_P
  };

  struct Path_TestApp : public ConnectionTracker
  {
    Path_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Path_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Path_TestApp::Tick );
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
        case PATH_NEW_P:
          PathNewP();
          break;

        case PATH_CONSTRUCTOR_P:
          PathConstructorP();
          break;

        case PATH_COPYCONSTRUCTOR_P:
          PathCopyConstructorP();
          break;

        case PATH_DOWNCAST_P:
          PathDownCastP();
          break;

        case PATH_DOWNCAST_N:
          PathDownCastN();
          break;

        case PATH_GET_POINT_P:
          PathGetPointP();
          break;

        case PATH_GET_POINT_N:
          PathGetPointN();
          break;

        case PATH_GET_POINT_N2:
          PathGetPointN2();
          break;

        case PATH_GET_CONTROL_POINT_P:
          PathGetControlPointP();
          break;

        case PATH_GET_CONTROL_POINT_N:
          PathGetControlPointN();
          break;

        case PATH_GET_CONTROL_POINT_N2:
          PathGetControlPointN2();
          break;

        case PATH_GENERATE_CONTROL_POINTS_P:
          PathGenerateControlPointsP();
          break;

        case PATH_GET_POINTS_COUNT_P:
          PathGetPointsCountP();
          break;

        case PATH_SAMPLE_P:
          PathSampleP();
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


void PathNewP()
{
  Dali::Path path = Dali::Path::New();
  DALI_CHECK_FAIL(!path , "Dali::Path::Path() is failed. Not Initialized object.");

  DaliLog::PrintPass();
}

void PathConstructorP()
{
  Dali::Path path;
  DALI_CHECK_FAIL(path , "Dali::Path::Path() is failed. Not Uninitialized object.");

  DaliLog::PrintPass();
}

void PathCopyConstructorP()
{
  Dali::Path path = Dali::Path::New();
  DALI_CHECK_FAIL(!path , "Dali::Path::Path() is failed. Not Uninitialized object.");

  Dali::Path path2 = path;
  DALI_CHECK_FAIL(!path2 , "Dali::Path::Path() is failed. Not Uninitialized object.");

  DALI_CHECK_FAIL( (path2 != path), "Path instance is not created.");

  DaliLog::PrintPass();
}


void PathDownCastP()
{    size_t nCount = 0;
  Vector3 vec3InitPoint( 5.0f,  5.0f, 0.0f);
  Vector3 vec3PointsAdded[PATH_POINT_COUNT];

  Dali::Path path;
  DALI_CHECK_FAIL(path , "Dali::Path::Path() is failed. Not Uninitialized object.");
  path = Dali::Path::New();
  DALI_CHECK_FAIL(!path , "Dali::Path::Path() is failed. Not Initialized object.");
  while(nCount++ < PATH_POINT_COUNT)
  {
    path.AddPoint(vec3InitPoint);
    DALI_CHECK_FAIL(vec3InitPoint != path.GetPoint(nCount - 1) , "Dali::Path::AddPoint() is failed. Interpolation point did not add.");
    vec3PointsAdded[nCount - 1] = vec3InitPoint;
    vec3InitPoint.x += PATH_X_OFFSET;
    vec3InitPoint.y = F_X2(vec3InitPoint.x);    //y = f(x) = x^2
  }
  Dali::Path newPath(path);
  DALI_CHECK_FAIL(!newPath , "Dali::Path::Path(const Path &) is failed. Not Initialized object by another object");

  nCount = newPath.GetPointCount();
  DALI_CHECK_FAIL(nCount == 0 || nCount != PATH_POINT_COUNT , "Dali::Path::GetPointCount() is failed. Invalid count of interpolation points.");

  Handle baseHandle(newPath);
  path = Path::DownCast(baseHandle);
  DALI_CHECK_FAIL(!path , "Dali::Path::DownCast() is failed. Invalid casting.");
  try
  {
    while(nCount--)
    {
      DALI_CHECK_FAIL(newPath.GetPoint(nCount) != vec3PointsAdded[nCount],
          "Dali::Path::GetPoint() is failed. Wrong point accessing from interpolation points.");
    }
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    test_return_value=1;
    return;
  }
  catch(...)
  {
    LOG_E("Unknown error.");
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}


void PathDownCastN()
{
  Dali::Path newPath;
  DALI_CHECK_FAIL(newPath , "Dali::Path::Path() is failed. Not Initialized object");

  BaseHandle baseHandle = newPath;
  DALI_CHECK_FAIL(baseHandle, "BaseHandle is empty");


  Dali::Path path2 = Path::DownCast(baseHandle);
  DALI_CHECK_FAIL(path2 , "Dali::Path::DownCast() is failed. Invalid casting.");

  DaliLog::PrintPass();
}


void PathGetPointP()
{
  const int nCount = 6;
  Dali::Path path = Dali::Path::New();

  Vector3 vectors[nCount] = {
    Vector3( 50.0,  50.0, 0.0),
    Vector3(120.0,  70.0, 0.0),
    Vector3(190.0, 250.0, 0.0),
    Vector3(260.0, 260.0, 0.0),
    Vector3(330.0, 220.0, 0.0),
    Vector3(400.0,  50.0, 0.0)
  };
  for(int i=0;  i < nCount; i++)
  {
    path.AddPoint(vectors[i]);
  }

  for(int i=0; i< nCount; i++)
  {
    DALI_CHECK_FAIL( (path.GetPoint(i) != vectors[i]), "Path GetPoint is failing.");
  }

  DaliLog::PrintPass();
}


void PathGetPointN(void)
{

  Dali::Path path = Dali::Path::New();
  path.AddPoint(Vector3( 50.0,  50.0, 0.0f));

  try
  {
    path.GetPoint(1);

  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "index < mPoint.Size()");
  }

  DaliLog::PrintPass();

}

void PathGetPointN2(void)
{

  Dali::Path path = Dali::Path::New();

  try
  {
    path.GetPoint(0);

  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "index < mPoint.Size()");
  }

  DaliLog::PrintPass();

}

void PathGetControlPointP()
{

  const int nCount = 2;
  Dali::Path path = Dali::Path::New();

  Vector3 vectors[nCount] = {
    Vector3(0.0f, 0.0f, 0.0),
    Vector3(108.0f, 57.0f, 0.0)
  };
  for(int i=0;  i < nCount; i++)
  {
    path.AddControlPoint(vectors[i]);
  }

  for(int i=0; i< nCount; i++)
  {
    DALI_CHECK_FAIL( (path.GetControlPoint(i) != vectors[i]), "Path GetPoint is failing.");
  }

  DaliLog::PrintPass();
}


void PathGetControlPointN(void)
{

  Dali::Path path = Dali::Path::New();
  path.AddControlPoint(Vector3( 50.0,  50.0, 0.0f));

  try
  {
    path.GetControlPoint(1);

  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "index < mControlPoint.Size()");
  }

  DaliLog::PrintPass();

}

void PathGetControlPointN2(void)
{

  Dali::Path path = Dali::Path::New();

  try
  {
    path.GetControlPoint(0);

  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "index < mControlPoint.Size()");
  }

  DaliLog::PrintPass();
}


void PathGenerateControlPointsP()
{
  size_t nCount = 0;
  Vector3 vec3InitPoint( 5.0f,  5.0f, 0.0f), vec3InitControlPoint;
  Vector3 vec3PointsAdded[PATH_POINT_COUNT];
  vec3InitControlPoint.x = (PATH_POINT_COUNT/ 2.0f);
  vec3InitControlPoint.y = (PATH_POINT_COUNT/ 2.0f);
  vec3InitControlPoint.z = 0.0f;

  Dali::Path path;
  DALI_CHECK_FAIL(path , "Dali::Path::Path() is failed. Not Uninitialized object.");
  path = Dali::Path::New();
  DALI_CHECK_FAIL(!path , "Dali::Path::Path() is failed. Not Initialized object.");
  while(nCount++ < PATH_POINT_COUNT)
  {
    path.AddPoint(vec3InitPoint);
    DALI_CHECK_FAIL(vec3InitPoint != path.GetPoint(nCount - 1) , "Dali::Path::AddPoint() is failed. Interpolation point did not add.");
    vec3PointsAdded[nCount - 1] = vec3InitPoint;
    vec3InitPoint.x += PATH_X_OFFSET;
    vec3InitPoint.y = F_X2(vec3InitPoint.x);    //y = f(x) = x^2
  }

  path.GenerateControlPoints(PATH_POINT_CURVATURE);

  Dali::Path newPath(path);
  DALI_CHECK_FAIL(!newPath , "Dali::Path::Path(const Path &) is failed. Not Initialized object by another object");

  nCount = newPath.GetPointCount();
  DALI_CHECK_FAIL(nCount == 0 || nCount != PATH_POINT_COUNT , "Dali::Path::GetPointCount() is failed. Invalid count of interpolation points.");

  Handle baseHandle(newPath);
  path = Path::DownCast(baseHandle);
  DALI_CHECK_FAIL(!path , "Dali::Path::DownCast() is failed. Invalid casting.");
  try
  {
    while(nCount--)
    {
      DALI_CHECK_FAIL(newPath.GetPoint(nCount) != vec3PointsAdded[nCount],
          "Dali::Path::GetPoint() is failed. Wrong point accessing from interpolation points.");
    }
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    test_return_value=1;
    return;
  }
  catch(...)
  {
    LOG_E("Unknown error.");
    test_return_value=1;
    return;
  }
  PathAnimatePlay(path);

  DaliLog::PrintPass();
}


void PathSampleP()
{
  size_t nCount = 0;
  float fProgress = 0.0f;
  Vector3 vec3InitPoint( 5.0f,  5.0f, 0.0f);
  Vector3 vec3Position, vec3Tangent;
  const size_t kPathPointCount = PATH_POINT_COUNT + 2;

  Dali::Path path = Dali::Path::New();
  DALI_CHECK_FAIL(!path , "Dali::Path::Path() is failed. Not Initialized object.");
  while(nCount++ < kPathPointCount)
  {
    path.AddPoint(vec3InitPoint);
    DALI_CHECK_FAIL(vec3InitPoint != path.GetPoint(nCount - 1) , "Dali::Path::GetPoint() is failed. Interpolation point did not add.");
    vec3InitPoint.x += PATH_X_OFFSET;
    vec3InitPoint.y = F_X2(vec3InitPoint.x);    //y = f(x) = x^2
  }
  path.GenerateControlPoints(PATH_POINT_CURVATURE);

  while(fProgress <= 1.0f)
  {
    path.Sample(fProgress, vec3Position, vec3Tangent);
    DALI_CHECK_FAIL(vec3Position.x < path.GetPoint(0).x || vec3Position.y < path.GetPoint(0).y,
        "Dali::Path::Sample() is failed. Invalid progress sample.");
    fProgress += 0.25f;
  }

  PathAnimatePlay(path);

  DaliLog::PrintPass();
}


void PathGetPointsCountP()
{

  Dali::Path path = Dali::Path::New();
  DALI_CHECK_FAIL(!path , "Dali::Path::Path() is failed. Not Initialized object.");

  DALI_CHECK_FAIL(path.GetPointCount() != 0u , "Dali::Path::GetPointCount() has failed.");

  path.AddPoint(Vector3( 50.0,  50.0, 0.0));
  path.AddPoint(Vector3(120.0,  70.0, 0.0));
  path.AddPoint(Vector3(190.0, 250.0, 0.0));
  path.AddPoint(Vector3(260.0, 260.0, 0.0));

  DALI_CHECK_FAIL(path.GetPointCount() != 4u, "Dali::Path::GetPointCount() has failed.");

  path.AddPoint(Vector3(330.0, 220.0, 0.0));
  path.AddPoint(Vector3(400.0,  50.0, 0.0));

  DALI_CHECK_FAIL(path.GetPointCount() != 6u, "Dali::Path::GetPointCount() has failed.");
  DaliLog::PrintPass();
}

/**
 * @testcase                 UtcDaliPathNewP
 * @since_tizen              2.4
 * @description              Check for the creation of Path instance thro' static method New
 */
int UtcDaliPathNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_NEW_P );
  application.MainLoop();

  return test_return_value;
}



/**
 * @testcase                 UtcDaliPathConstructorP
 * @since_tizen              2.4
 * @description              Check for the creation of Path instance
 */
int UtcDaliPathConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliPathCopyConstructorP
 * @since_tizen              2.4
 * @description              Check for the creation of Path instance thro' copy constructor
 */
int UtcDaliPathCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_COPYCONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase                 UtcDaliPathDownCastP
 * @since_tizen              2.4
 * @description              Check for the dowcast of Path instance
 */
int UtcDaliPathDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliPathDownCastN
 * @since_tizen              2.4
 * @description              Check for the dowcast of Path instance
 */
int UtcDaliPathDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliPathGetPointP
 * @since_tizen              2.4
 * @description              Check for the getpoint of Path instance
 */
int UtcDaliPathGetPointP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_GET_POINT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliPathGetPointN
 * @since_tizen              2.4
 * @description              Check for the point in Path instance
 */
int UtcDaliPathGetPointN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_GET_POINT_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliPathGetPointN2
 * @since_tizen              2.4
 * @description              Check for the point in Path instance
 */
int UtcDaliPathGetPointN2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_GET_POINT_N2 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliPathGetControlPointP
 * @since_tizen              2.4
 * @description              Check for the getcontrolpoint of Path instance
 */
int UtcDaliPathGetControlPointP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_GET_CONTROL_POINT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliPathGetControlPointN
 * @since_tizen              2.4
 * @description              Check for the controlpoint in Path instance
 */
int UtcDaliPathGetControlPointN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_GET_CONTROL_POINT_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliPathGetControlPointN2
 * @since_tizen              2.4
 * @description              Check for the controlpoint in Path instance
 */
int UtcDaliPathGetControlPointN2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_GET_CONTROL_POINT_N2 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliPathGenerateControlPointsP
 * @since_tizen              2.4
 * @description              Check for the generatecontrolpoints of Path instance
 */
int UtcDaliPathGenerateControlPointsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_GENERATE_CONTROL_POINTS_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliPathSampleP
 * @since_tizen              2.4
 * @description              Checks sample path position and tangent from a set path
 */

int UtcDaliPathSampleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_SAMPLE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliPathGetPointcountP
 * @since_tizen              2.4
 * @description              Check for the controlpointcount in Path instance
 */
int UtcDaliPathGetPointCountP(void)
{

  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Path_TestApp testApp( application, PATH_GET_POINTS_COUNT_P );
  application.MainLoop();

  return test_return_value;
}
