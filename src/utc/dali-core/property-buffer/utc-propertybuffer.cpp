#include "utc-propertybuffer-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: PropertyBuffer

void utc_propertybuffer_startup(void)
{
  test_return_value = 0;
}

void utc_propertybuffer_cleanup(void)
{

}

void PropertyBufferConstructorAndNew();
void PropertyBufferDownCastP();
void PropertyBufferDownCastN();
void PropertyBufferAssignmentOperator();
void PropertyBufferSetDataGetSize();


namespace
{
  enum TEST_CASES_LIST_PROPERTYBUFFER
  {
    PROPERTYBUFFER_CONSTRUCTOR_AND_NEW,
    PROPERTYBUFFER_DOWN_CAST_POSITIVE,
    PROPERTYBUFFER_DOWN_CAST_NEGATIVE,
    PROPERTYBUFFER_ASSIGNMENT_OPERATOR,
    PROPERTYBUFFER_SET_DATA_GET_SIZE,
  };

  struct PropertyBuffer_TestApp : public ConnectionTracker
  {
    PropertyBuffer_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &PropertyBuffer_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &PropertyBuffer_TestApp::Tick );
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
        case PROPERTYBUFFER_CONSTRUCTOR_AND_NEW:
        PropertyBufferConstructorAndNew();
        break;
        case PROPERTYBUFFER_DOWN_CAST_POSITIVE:
        PropertyBufferDownCastP();
        break;
        case PROPERTYBUFFER_DOWN_CAST_NEGATIVE:
        PropertyBufferDownCastN();
        break;
        case PROPERTYBUFFER_ASSIGNMENT_OPERATOR:
        PropertyBufferAssignmentOperator();
        break;
        case PROPERTYBUFFER_SET_DATA_GET_SIZE:
        PropertyBufferSetDataGetSize();
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

void PropertyBufferConstructorAndNew()
{
  PropertyBuffer propertybuffer;
  DALI_CHECK_FAIL( propertybuffer, "PropertyBuffer constructor failed" );

  propertybuffer = CreateVertexBuffer("aPosition1", "aTexCoord1" );
  DALI_CHECK_FAIL( !propertybuffer, "PropertyBuffer::New failed" );

  DaliLog::PrintPass();
}

void PropertyBufferDownCastP()
{
  PropertyBuffer propertybuffer = CreateVertexBuffer("aPosition1", "aTexCoord1" );

  BaseHandle handle( propertybuffer );
  PropertyBuffer propertybuffer2 = PropertyBuffer::DownCast( handle );
  DALI_CHECK_FAIL( !propertybuffer2, "PropertyBuffer::DownCast failed" );

  DaliLog::PrintPass();
}

void PropertyBufferDownCastN()
{
  Handle handle = Handle::New();
  PropertyBuffer propertybuffer = PropertyBuffer::DownCast( handle );

  DALI_CHECK_FAIL( propertybuffer, "PropertyBuffer::DownCast Negative test failed" );

  DaliLog::PrintPass();
}

void PropertyBufferAssignmentOperator()
{
  PropertyBuffer propertybuffer1 = CreateVertexBuffer("aPosition1", "aTexCoord1" );
  PropertyBuffer propertybuffer2 = CreateVertexBuffer("aPosition1", "aTexCoord1" );
  DALI_CHECK_FAIL( ! ( propertybuffer1 != propertybuffer2 ), "PropertyBuffer::operator= test failed" );

  propertybuffer2 = propertybuffer1;
  DALI_CHECK_FAIL( ! ( propertybuffer1 == propertybuffer2 ), "PropertyBuffer::operator= test failed" );

  DaliLog::PrintPass();
}

void PropertyBufferSetDataGetSize()
{
  const float halfQuadSize = .5f;
  TexturedQuadVertex texturedQuadVertexData[4] = {
    { Vector2(-halfQuadSize, -halfQuadSize), Vector2(0.f, 0.f) },
    { Vector2( halfQuadSize, -halfQuadSize), Vector2(1.f, 0.f) },
    { Vector2(-halfQuadSize,  halfQuadSize), Vector2(0.f, 1.f) },
    { Vector2( halfQuadSize,  halfQuadSize), Vector2(1.f, 1.f) } };

  Property::Map vertexFormat;
  vertexFormat["aPosition1"] = Property::VECTOR2;
  vertexFormat["aTexCoord1"] = Property::VECTOR2;

  PropertyBuffer propertybuffer = PropertyBuffer::New( vertexFormat );
  DALI_CHECK_FAIL( ! ( propertybuffer.GetSize() == 0 ), "PropertyBuffer::GetSize() test failed" );

  propertybuffer.SetData( texturedQuadVertexData, 4 );
  DALI_CHECK_FAIL( ! ( propertybuffer.GetSize() == 4 ), "PropertyBuffer::SetData() test failed" );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase          UtcPropertyBufferConstructorAndNew
 * @since_tizen       3.0
 * @description       Check whether the default constructor and New method works
 */
int UtcPropertyBufferConstructorAndNew(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  PropertyBuffer_TestApp testApp( application, PROPERTYBUFFER_CONSTRUCTOR_AND_NEW);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcPropertyBufferDownCastP
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcPropertyBufferDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  PropertyBuffer_TestApp testApp( application, PROPERTYBUFFER_DOWN_CAST_POSITIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcPropertyBufferDownCastN
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcPropertyBufferDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  PropertyBuffer_TestApp testApp( application, PROPERTYBUFFER_DOWN_CAST_NEGATIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcPropertyBufferAssignmentOperator
 * @since_tizen       3.0
 * @description       Check assignment operator
 */
int UtcPropertyBufferAssignmentOperator(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  PropertyBuffer_TestApp testApp( application, PROPERTYBUFFER_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcPropertyBufferSetDataGetSize
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcPropertyBufferSetDataGetSize(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  PropertyBuffer_TestApp testApp( application, PROPERTYBUFFER_SET_DATA_GET_SIZE);
  application.MainLoop();
  return test_return_value;
}

