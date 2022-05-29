#include "utc-dali-native-image-impl.h"

//& set: NativeImage

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_NativeImage_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_NativeImage_startup(void)
{
  test_return_value=TC_PASS;
  gRenderCountNativeImage=TC_PASS;
}

/**
 * @function            utc_Dali_NativeImage_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_NativeImage_cleanup(void)
{
}

namespace
{
  enum TEST_CASES_LIST_NATIVE_IMAGE
  {
    NATIVE_IMAGE_CONSTRUCTOR_P,
    NATIVE_IMAGE_NEW_P,
    NATIVE_IMAGE_DOWNCAST_P,
    NATIVE_IMAGE_DOWNCAST_N,
    NATIVE_IMAGE_COPY_CONSTRUCTOR_P,
    NATIVE_IMAGE_OPERATOR_ASSIGNMENT_P,
    NATIVE_IMAGE_CREATE_GL_TEXTURE_P,
    NATIVE_IMAGE_CUSTOM_FRAGMENT_PREFIX_P,
    NATIVE_IMAGE_CUSTOM_SAMPLER_TYPENAME_P
  };

  struct NativeImage_TestApp : public ConnectionTracker
  {
    NativeImage_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &NativeImage_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &NativeImage_TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      if(test_return_value==TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
        return true;
      }

      VerdictTest();

      if(test_return_value==TC_FAIL)
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

        case NATIVE_IMAGE_CONSTRUCTOR_P:
          NativeImageConstructorP();
          break;

        case NATIVE_IMAGE_NEW_P:
          NativeImageNewP();
          break;

        case NATIVE_IMAGE_DOWNCAST_P:
          NativeImageDownCastP();
          break;

        case NATIVE_IMAGE_DOWNCAST_N:
          NativeImageDownCastN();
          break;

        case NATIVE_IMAGE_COPY_CONSTRUCTOR_P:
          NativeImageCopyConstructorP();
          break;

        case NATIVE_IMAGE_OPERATOR_ASSIGNMENT_P:
          NativeImageOperatorAssignmentP();
          break;

        case NATIVE_IMAGE_CREATE_GL_TEXTURE_P:
          NativeImageCreateGlTextureP();
          break;

        case NATIVE_IMAGE_CUSTOM_FRAGMENT_PREFIX_P:
          NativeImageCustomFragmentPrefixP();
          break;

        case NATIVE_IMAGE_CUSTOM_SAMPLER_TYPENAME_P:
          NativeImageCustomSamplerTypenameP();
          break;
      }
    }
    void VerdictTest()
    {
      switch (mTestCase)
      {
        case NATIVE_IMAGE_CREATE_GL_TEXTURE_P:
          switch (gRenderCountNativeImage)
          {
            case 0:
              VTNativeImageCreateGlTexture001();
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
 * @testcase           UtcDaliNativeImageConstructorP
 * @since_tizen        2.4
 * @description        check if default constructor works or not.
 */

int UtcDaliNativeImageConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImage_TestApp testApp( application, NATIVE_IMAGE_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliNativeImageNewP
 * @since_tizen         2.4
 * @description         check if New api works or not.
 */

int UtcDaliNativeImageNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImage_TestApp testApp( application, NATIVE_IMAGE_NEW_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliNativeImageDownCastP
 * @since_tizen         2.4
 * @description         check if Downcast api works or not.
 */

int UtcDaliNativeImageDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImage_TestApp testApp( application, NATIVE_IMAGE_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}



/**
 * @testcase            UtcDaliNativeImageDownCastN
 * @since_tizen         2.4
 * @description         check if Downcast api works or not.
 */

int UtcDaliNativeImageDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImage_TestApp testApp( application, NATIVE_IMAGE_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}



/**
 * @testcase            UtcDaliNativeImageCopyConstructorP
 * @since_tizen         2.4
 * @description         check if copy constructor works or not.
 */

int UtcDaliNativeImageCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImage_TestApp testApp( application, NATIVE_IMAGE_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}



/**
 * @testcase            UtcDaliNativeImageOperatorAssignmentP
 * @since_tizen         2.4
 * @description         check if operator=() works or not.
 */

int UtcDaliNativeImageOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImage_TestApp testApp( application, NATIVE_IMAGE_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliNativeImageCreateGlTextureP
 * @since_tizen         2.4
 * @description         check if CreateGlTexture api works or not.
 */

int UtcDaliNativeImageCreateGlTextureP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImage_TestApp testApp( application, NATIVE_IMAGE_CREATE_GL_TEXTURE_P );
  application.MainLoop();

  return test_return_value;
}
/**
 * @testcase            UtcDaliNativeImageCustomFragmentPrefixP
 * @since_tizen         3.0
 * @description         check if CustomFragmentPrefix api works or not.
 */

int UtcDaliNativeImageCustomFragmentPrefixP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImage_TestApp testApp( application, NATIVE_IMAGE_CUSTOM_FRAGMENT_PREFIX_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliNativeImageCustomSamplerTypenameP
 * @since_tizen         3.0
 * @description         check if CustomSamplerTypename api works or not.
 */

int UtcDaliNativeImageCustomSamplerTypenameP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImage_TestApp testApp( application, NATIVE_IMAGE_CUSTOM_SAMPLER_TYPENAME_P );
  application.MainLoop();

  return test_return_value;
}

