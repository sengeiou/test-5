#include "utc-renderer-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;


void utc_renderer_startup(void)
{
  test_return_value = 0;
}

void utc_renderer_cleanup(void)
{

}

void RendererConstructorAndNew();
void RendererDownCastP();
void RendererDownCastN();
void RendererAssignmentOperator();
void RendererSetGetGeometry();
void RendererSetGetTextures();
void RendererSetGetShader();
void RendererSetIndexRange();

namespace
{

  /*
   * Vertex shader
   */
  const char* VERTEX_SHADER = DALI_COMPOSE_SHADER(
  attribute mediump vec2 aPosition;\n
  uniform   mediump mat4 uMvpMatrix;\n
  \n
  void main()\n
  {\n
    mediump vec4 vertexPosition = vec4(aPosition, 0.0, 1.0);\n
    gl_Position = uMvpMatrix * vertexPosition;\n
  }\n
  );

  /*
   * Fragment shader
   */
  const char* FRAGMENT_SHADER = DALI_COMPOSE_SHADER(
  uniform mediump vec4 uColor;\n
  \n
  void main()\n
  {\n
    gl_FragColor = uColor;\n
  }\n
  );

  enum TEST_CASES_LIST_RENDERER
  {
    RENDERER_CONSTRUCTOR_AND_NEW,
    RENDERER_DOWN_CAST_POSITIVE,
    RENDERER_DOWN_CAST_NEGATIVE,
    RENDERER_ASSIGNMENT_OPERATOR,
    RENDERER_SET_GET_GEOMETRY,
    RENDERER_SET_GET_TEXTURES,
    RENDERER_SET_GET_SHADER,
    RENDERER_SET_INDEX_RANGE,
  };

  struct Renderer_TestApp : public ConnectionTracker
  {
    Renderer_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Renderer_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Renderer_TestApp::Tick );
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
        case RENDERER_CONSTRUCTOR_AND_NEW:
        RendererConstructorAndNew();
        break;
        case RENDERER_DOWN_CAST_POSITIVE:
        RendererDownCastP();
        break;
        case RENDERER_DOWN_CAST_NEGATIVE:
        RendererDownCastN();
        break;
        case RENDERER_ASSIGNMENT_OPERATOR:
        RendererAssignmentOperator();
        break;
        case RENDERER_SET_GET_GEOMETRY:
        RendererSetGetGeometry();
        break;
        case RENDERER_SET_GET_TEXTURES:
        RendererSetGetTextures();
        break;
        case RENDERER_SET_GET_SHADER:
        RendererSetGetShader();
        break;
        case RENDERER_SET_INDEX_RANGE:
        RendererSetIndexRange();
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

static Shader CreateShader()
{
  return Shader::New( VERTEX_SHADER, FRAGMENT_SHADER, Shader::Hint::NONE );
}

void RendererConstructorAndNew()
{
  Renderer renderer;
  DALI_CHECK_FAIL( renderer, "Renderer constructor failed" );

  Geometry geometry = Geometry::New();
  Shader shader = CreateShader();
  renderer = Renderer::New( geometry, shader );
  DALI_CHECK_FAIL( !renderer, "Renderer::New failed" );

  DaliLog::PrintPass();
}

void RendererDownCastP()
{
  Geometry geometry = Geometry::New();
  Shader shader = CreateShader();
  Renderer renderer = Renderer::New( geometry, shader );

  BaseHandle handle( renderer );
  Renderer renderer2 = Renderer::DownCast( handle );
  DALI_CHECK_FAIL( !renderer2, "Renderer::DownCast failed" );

  DaliLog::PrintPass();
}

void RendererDownCastN()
{
  Handle handle = Handle::New();
  Renderer renderer = Renderer::DownCast( handle );

  DALI_CHECK_FAIL( renderer, "Renderer::DownCast Negative test failed" );

  DaliLog::PrintPass();
}

void RendererAssignmentOperator()
{
  Geometry geometry = Geometry::New();
  Shader shader = CreateShader();

  Renderer renderer1 = Renderer::New( geometry, shader );
  Renderer renderer2 = Renderer::New( geometry, shader );
  DALI_CHECK_FAIL( ! ( renderer1 != renderer2 ), "Renderer::operator= test failed" );

  renderer2 = renderer1;
  DALI_CHECK_FAIL( ! ( renderer1 == renderer2 ), "Renderer::operator= test failed" );

  DaliLog::PrintPass();
}

void RendererSetGetGeometry()
{
  Geometry geometry = Geometry::New();
  Shader shader = CreateShader();

  Renderer renderer = Renderer::New( geometry, shader );
  Geometry geometry2 = Geometry::New();
  DALI_CHECK_FAIL( ! ( renderer.GetGeometry() != geometry2 ), "Renderer::GetGeometry() test failed" );

  renderer.SetGeometry( geometry2 );
  DALI_CHECK_FAIL( ! ( renderer.GetGeometry() == geometry2 ), "Renderer::SetGeometry() test failed" );

  DaliLog::PrintPass();
}

void RendererSetGetTextures()
{
  Geometry geometry = Geometry::New();
  Shader shader = CreateShader();

  Renderer renderer = Renderer::New( geometry, shader );
  TextureSet textureSet = TextureSet::New();
  DALI_CHECK_FAIL( ! ( renderer.GetTextures() != textureSet ), "Renderer::GetTextures() test failed" );

  renderer.SetTextures( textureSet );
  DALI_CHECK_FAIL( ! ( renderer.GetTextures() == textureSet ), "Renderer::SetTextures() test failed" );

  DaliLog::PrintPass();
}

void RendererSetGetShader()
{
  Geometry geometry = Geometry::New();
  Shader shader = CreateShader();

  Renderer renderer = Renderer::New( geometry, shader );
  Shader shader2 = CreateShader();
  DALI_CHECK_FAIL( ! ( renderer.GetShader() != shader2 ), "Renderer::GetShader() test failed" );

  renderer.SetShader( shader2 );
  DALI_CHECK_FAIL( ! ( renderer.GetShader() == shader2 ), "Renderer::SetShader() test failed" );

  DaliLog::PrintPass();
}

void RendererSetIndexRange()
{
  Geometry geometry = Geometry::New();
  Shader shader = CreateShader();

  Renderer renderer = Renderer::New( geometry, shader );
  renderer.SetIndexRange( 10, 20 );

  DALI_CHECK_FAIL( ! ( renderer.GetProperty( Renderer::Property::INDEX_RANGE_FIRST ).Get<int>() == 10), "Renderer::SetIndexRange() test failed" );
  DALI_CHECK_FAIL( ! ( renderer.GetProperty( Renderer::Property::INDEX_RANGE_COUNT ).Get<int>() == 20), "Renderer::SetIndexRange() test failed" );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase          UtcRendererConstructorAndNew
 * @since_tizen       3.0
 * @description       Check whether the default constructor and New method works
 */
int UtcRendererConstructorAndNew(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Renderer_TestApp testApp( application, RENDERER_CONSTRUCTOR_AND_NEW);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcRendererDownCastP
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcRendererDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Renderer_TestApp testApp( application, RENDERER_DOWN_CAST_POSITIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcRendererAssignmentOperator
 * @since_tizen       3.0
 * @description       Check assignment operator
 */
int UtcRendererAssignmentOperator(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Renderer_TestApp testApp( application, RENDERER_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcRendererDownCastN
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcRendererDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Renderer_TestApp testApp( application, RENDERER_DOWN_CAST_NEGATIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcRendererSetGetGeometry
 * @since_tizen       3.0
 * @description       Check setting and getting the geometry
 */
int UtcRendererSetGetGeometry(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Renderer_TestApp testApp( application, RENDERER_SET_GET_GEOMETRY);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcRendererSetGetTextures
 * @type              Positive
 * @since_tizen      3.0
 * @description      Check assignment operator
 * @scenario          Create an instance of renderer, set the textures and check what was set.
 * @apicovered        Renderer::SetTextures(), Renderer::GetTextures()
 * @passcase          Should match the textures that we set.
 * @failcase          Anything other than pass case
 * @precondition      NA
 * @postcondition    NA
 */
int UtcRendererSetGetTextures(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Renderer_TestApp testApp( application, RENDERER_SET_GET_TEXTURES);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcRendererSetGetShader
 * @since_tizen       3.0
 * @description       Create an instance of renderer, set the shader and check what was set.
 */
int UtcRendererSetGetShader(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Renderer_TestApp testApp( application, RENDERER_SET_GET_SHADER);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcRendererSetIndexRange
 * @since_tizen       3.0
 * @description       Check the SetIndexRange inline method
 */
int UtcRendererSetIndexRange(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Renderer_TestApp testApp( application, RENDERER_SET_INDEX_RANGE);
  application.MainLoop();
  return test_return_value;
}

