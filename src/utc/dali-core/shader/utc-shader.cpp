#include "utc-shader-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;


void utc_shader_startup(void)
{
  test_return_value = 0;
}

void utc_shader_cleanup(void)
{

}

void ShaderConstructorAndNew();
void ShaderDownCastP();
void ShaderDownCastN();
void ShaderAssignmentOperator();

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

  enum TEST_CASES_LIST_SHADER
  {
    SHADER_CONSTRUCTOR_AND_NEW,
    SHADER_DOWN_CAST_POSITIVE,
    SHADER_DOWN_CAST_NEGATIVE,
    SHADER_ASSIGNMENT_OPERATOR,
  };

  struct Shader_TestApp : public ConnectionTracker
  {
    Shader_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Shader_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Shader_TestApp::Tick );
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
        case SHADER_CONSTRUCTOR_AND_NEW:
        ShaderConstructorAndNew();
        break;
        case SHADER_DOWN_CAST_POSITIVE:
        ShaderDownCastP();
        break;
        case SHADER_DOWN_CAST_NEGATIVE:
        ShaderDownCastN();
        break;
        case SHADER_ASSIGNMENT_OPERATOR:
        ShaderAssignmentOperator();
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

void ShaderConstructorAndNew()
{
  Shader shader;
  DALI_CHECK_FAIL( shader, "Shader constructor failed" );

  shader = Shader::New( VERTEX_SHADER, FRAGMENT_SHADER,Shader::Hint::NONE );
  DALI_CHECK_FAIL( !shader, "Shader::New failed" );

  DaliLog::PrintPass();
}

void ShaderDownCastP()
{
  Shader shader = Shader::New( VERTEX_SHADER, FRAGMENT_SHADER );
  BaseHandle handle( shader );
  Shader shader2 = Shader::DownCast( handle );
  DALI_CHECK_FAIL( !shader2, "Shader::DownCast failed" );

  DaliLog::PrintPass();
}

void ShaderDownCastN()
{
  Handle handle = Handle::New();
  Shader shader = Shader::DownCast( handle );

  DALI_CHECK_FAIL( shader, "Shader::DownCast Negative test failed" );

  DaliLog::PrintPass();
}

void ShaderAssignmentOperator()
{
  Shader shader1 = Shader::New( VERTEX_SHADER, FRAGMENT_SHADER,Shader::Hint::NONE );
  Shader shader2 = Shader::New( VERTEX_SHADER, FRAGMENT_SHADER,Shader::Hint::NONE );
  DALI_CHECK_FAIL( ! ( shader1 != shader2 ), "Shader::operator= test failed" );

  shader2 = shader1;
  DALI_CHECK_FAIL( ! ( shader1 == shader2 ), "Shader::operator= test failed" );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase          UtcShaderConstructorAndNew
 * @since_tizen       3.0
 * @description       Check whether the default constructor and New method works
 */
int UtcShaderConstructorAndNew(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Shader_TestApp testApp( application, SHADER_CONSTRUCTOR_AND_NEW);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcShaderDownCastP
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcShaderDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Shader_TestApp testApp( application, SHADER_DOWN_CAST_POSITIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcShaderAssignmentOperator
 * @since_tizen       3.0
 * @description       Check assignment operator
 */
int UtcShaderAssignmentOperator(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Shader_TestApp testApp( application, SHADER_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcShaderDownCastN
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcShaderDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Shader_TestApp testApp( application, SHADER_DOWN_CAST_NEGATIVE);
  application.MainLoop();
  return test_return_value;
}

