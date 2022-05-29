#include "utc-geometry-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Geometry

void utc_geometry_startup(void)
{
  test_return_value = 0;
}

void utc_geometry_cleanup(void)
{

}

void GeometryConstructorAndNew();
void GeometryDownCastP();
void GeometryDownCastN();
void GeometryAssignmentOperator();
void GeometryAddGetRemoveVertexBuffer();
void GeometrySetGetType();


namespace
{
  enum TEST_CASES_LIST_GEOMETRY
  {
    GEOMETRY_CONSTRUCTOR_AND_NEW,
    GEOMETRY_DOWN_CAST_POSITIVE,
    GEOMETRY_DOWN_CAST_NEGATIVE,
    GEOMETRY_ASSIGNMENT_OPERATOR,
    GEOMETRY_ADD_GET_REMOVE_VERTEX_BUFFER,
    GEOMETRY_SET_GET_TYPE,
  };

  struct Geometry_TestApp : public ConnectionTracker
  {
    Geometry_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Geometry_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Geometry_TestApp::Tick );
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
        case GEOMETRY_CONSTRUCTOR_AND_NEW:
        GeometryConstructorAndNew();
        break;
        case GEOMETRY_DOWN_CAST_POSITIVE:
        GeometryDownCastP();
        break;
        case GEOMETRY_DOWN_CAST_NEGATIVE:
        GeometryDownCastN();
        break;
        case GEOMETRY_ASSIGNMENT_OPERATOR:
        GeometryAssignmentOperator();
        break;
        case GEOMETRY_ADD_GET_REMOVE_VERTEX_BUFFER:
        GeometryAddGetRemoveVertexBuffer();
        break;
        case GEOMETRY_SET_GET_TYPE:
        GeometrySetGetType();
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

struct TexturedQuadVertex { Vector2 position; Vector2 textureCoordinates; };

static PropertyBuffer CreateVertexBuffer( const std::string& aPosition, const std::string& aTexCoord )
{
  const float halfQuadSize = .5f;
  TexturedQuadVertex texturedQuadVertexData[4] = {
    { Vector2(-halfQuadSize, -halfQuadSize), Vector2(0.f, 0.f) },
    { Vector2( halfQuadSize, -halfQuadSize), Vector2(1.f, 0.f) },
    { Vector2(-halfQuadSize,  halfQuadSize), Vector2(0.f, 1.f) },
    { Vector2( halfQuadSize,  halfQuadSize), Vector2(1.f, 1.f) } };

  Property::Map vertexFormat;
  vertexFormat[aPosition] = Property::VECTOR2;
  vertexFormat[aTexCoord] = Property::VECTOR2;

  PropertyBuffer vertexData = PropertyBuffer::New( vertexFormat );
  vertexData.SetData( texturedQuadVertexData, 4 );

  return vertexData;
}

void GeometryConstructorAndNew()
{
  Geometry geometry;
  DALI_CHECK_FAIL( geometry, "Geometry constructor failed" );

  geometry = Geometry::New();
  DALI_CHECK_FAIL( !geometry, "Geometry::New failed" );

  DaliLog::PrintPass();
}

void GeometryDownCastP()
{
  Geometry geometry = Geometry::New();

  BaseHandle handle( geometry );
  Geometry geometry2 = Geometry::DownCast( handle );
  DALI_CHECK_FAIL( !geometry2, "Geometry::DownCast failed" );

  DaliLog::PrintPass();
}

void GeometryDownCastN()
{
  Handle handle = Handle::New();
  Geometry geometry = Geometry::DownCast( handle );

  DALI_CHECK_FAIL( geometry, "Geometry::DownCast Negative test failed" );

  DaliLog::PrintPass();
}

void GeometryAssignmentOperator()
{
  Geometry geometry1 = Geometry::New();
  Geometry geometry2 = Geometry::New();
  DALI_CHECK_FAIL( ! ( geometry1 != geometry2 ), "Geometry::operator= test failed" );

  geometry2 = geometry1;
  DALI_CHECK_FAIL( ! ( geometry1 == geometry2 ), "Geometry::operator= test failed" );

  DaliLog::PrintPass();
}

void GeometryAddGetRemoveVertexBuffer()
{
  Geometry geometry = Geometry::New();
  PropertyBuffer vertexBuffer1 = CreateVertexBuffer("aPosition1", "aTexCoord1" );

  DALI_CHECK_FAIL( geometry.GetNumberOfVertexBuffers() != 0, "Geometry::GetNumberOfVertexBuffers test failed" );
  geometry.AddVertexBuffer( vertexBuffer1 );
  DALI_CHECK_FAIL( geometry.GetNumberOfVertexBuffers() == 0, "Geometry::GeometryAddVertexBuffer test failed" );
  geometry.RemoveVertexBuffer( 0 );
  DALI_CHECK_FAIL( geometry.GetNumberOfVertexBuffers() != 0, "Geometry::RemoveVertexBuffer test failed" );

  DaliLog::PrintPass();
}

void GeometrySetGetType()
{
  Geometry geometry = Geometry::New();
  geometry.SetType( Geometry::TRIANGLE_FAN );
  DALI_CHECK_FAIL( geometry.GetType() != Geometry::TRIANGLE_FAN, "Geometry::SetType test failed" );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase          UtcGeometryConstructorAndNew
 * @since_tizen       3.0
 * @description       Check whether the default constructor and New method works
 */
int UtcGeometryConstructorAndNew(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Geometry_TestApp testApp( application, GEOMETRY_CONSTRUCTOR_AND_NEW);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcGeometryDownCastP
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcGeometryDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Geometry_TestApp testApp( application, GEOMETRY_DOWN_CAST_POSITIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcGeometryDownCastN
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcGeometryDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Geometry_TestApp testApp( application, GEOMETRY_DOWN_CAST_NEGATIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcGeometryAssignmentOperator
 * @since_tizen       3.0
 * @description       Check assignment operator
 */
int UtcGeometryAssignmentOperator(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Geometry_TestApp testApp( application, GEOMETRY_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcGeometryAddGetRemoveVertexBuffer
 * @since_tizen       3.0
 * @description       Check VertexBuffer methods
 */
int UtcGeometryAddGetRemoveVertexBuffer(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Geometry_TestApp testApp( application, GEOMETRY_ADD_GET_REMOVE_VERTEX_BUFFER);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcGeometrySetGetType
 * @since_tizen       3.0
 * @description       Check Set/Get Type methods
 */
int UtcGeometrySetGetType(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Geometry_TestApp testApp( application, GEOMETRY_SET_GET_TYPE);
  application.MainLoop();
  return test_return_value;
}

