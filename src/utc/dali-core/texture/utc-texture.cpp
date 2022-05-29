#include "utc-texture-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;


void utc_texture_startup(void)
{
  test_return_value = 0;
}

void utc_texture_cleanup(void)
{

}

void TextureConstructorAndNew();
void TextureNewNativeImage();
void TextureDownCastP();
void TextureDownCastN();
void TextureAssignmentOperator();
void TextureGetWidthHeight();

namespace
{
  enum TEST_CASES_LIST_TEXTURE
  {
    TEXTURE_CONSTRUCTOR_AND_NEW,
    TEXTURE_NEW_NATIVE_IMAGE,
    TEXTURE_DOWN_CAST_POSITIVE,
    TEXTURE_DOWN_CAST_NEGATIVE,
    TEXTURE_ASSIGNMENT_OPERATOR,
    TEXTURE_GET_WIDTH_HEIGHT,
  };

  struct Texture_TestApp : public ConnectionTracker
  {
    Texture_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Texture_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Texture_TestApp::Tick );
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
        case TEXTURE_CONSTRUCTOR_AND_NEW:
        TextureConstructorAndNew();
        break;
        case TEXTURE_NEW_NATIVE_IMAGE:
        TextureNewNativeImage();
        break;
        case TEXTURE_DOWN_CAST_POSITIVE:
        TextureDownCastP();
        break;
        case TEXTURE_DOWN_CAST_NEGATIVE:
        TextureDownCastN();
        break;
        case TEXTURE_ASSIGNMENT_OPERATOR:
        TextureAssignmentOperator();
        break;
        case TEXTURE_GET_WIDTH_HEIGHT:
        TextureGetWidthHeight();
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

void TextureConstructorAndNew()
{
  Texture texture;
  DALI_CHECK_FAIL( texture, "Texture constructor failed" );

  texture = Texture::New( TextureType::TEXTURE_2D, Pixel::RGBA8888, 64, 64 );
  DALI_CHECK_FAIL( !texture, "Texture::New failed" );

  DaliLog::PrintPass();
}

void TextureNewNativeImage()
{
  Texture texture;
  DALI_CHECK_FAIL( texture, "Texture constructor failed" );

  NativeImageInterfaceImplPointer nativeImageImplemented = NativeImageInterfaceImpl::New( 64, 64 );
  texture = Texture::New( *nativeImageImplemented );
  DALI_CHECK_FAIL( !texture, "Texture::New failed" );

  DaliLog::PrintPass();
}

void TextureDownCastP()
{
  Texture texture = Texture::New( TextureType::TEXTURE_2D, Pixel::RGBA8888, 64, 64 );

  BaseHandle handle( texture );
  Texture texture2 = Texture::DownCast( handle );
  DALI_CHECK_FAIL( !texture2, "Texture::DownCast failed" );

  DaliLog::PrintPass();
}

void TextureDownCastN()
{
  Handle handle = Handle::New();
  Texture texture = Texture::DownCast( handle );

  DALI_CHECK_FAIL( texture, "Texture::DownCast Negative test failed" );

  DaliLog::PrintPass();
}

void TextureAssignmentOperator()
{
  Texture texture1 = Texture::New( TextureType::TEXTURE_2D, Pixel::RGBA8888, 64, 64 );
  Texture texture2 = Texture::New( TextureType::TEXTURE_2D, Pixel::RGBA8888, 64, 64 );
  DALI_CHECK_FAIL( ! ( texture1 != texture2 ), "Texture::operator= test failed" );

  texture2 = texture1;
  DALI_CHECK_FAIL( ! ( texture1 == texture2 ), "Texture::operator= test failed" );

  DaliLog::PrintPass();
}

void TextureGetWidthHeight()
{
  Texture texture = Texture::New( TextureType::TEXTURE_2D, Pixel::RGBA8888, 64, 64 );
  DALI_CHECK_FAIL( ! ( texture.GetWidth() == 64 ), "Texture::GetWidth test failed" );
  DALI_CHECK_FAIL( ! ( texture.GetHeight() == 64 ), "Texture::GetHeight test failed" );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase          UtcTextureConstructorAndNew
 * @since_tizen       3.0
 * @description       Check whether the default constructor and New method works
 */
int UtcTextureConstructorAndNew(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Texture_TestApp testApp( application, TEXTURE_CONSTRUCTOR_AND_NEW);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcTextureNewNativeImage
 * @since_tizen       3.0
 * @description       Check whether the New method which takes a NativeImageInterface works
 */
int UtcTextureNewNativeImage(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Texture_TestApp testApp( application, TEXTURE_NEW_NATIVE_IMAGE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcTextureDownCastP
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcTextureDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Texture_TestApp testApp( application, TEXTURE_DOWN_CAST_POSITIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcTextureAssignmentOperator
 * @since_tizen       3.0
 * @description       Check assignment operator
 */
int UtcTextureAssignmentOperator(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Texture_TestApp testApp( application, TEXTURE_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcTextureDownCastN
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcTextureDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Texture_TestApp testApp( application, TEXTURE_DOWN_CAST_NEGATIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcTextureGetWidthHeight
 * @since_tizen       3.0
 * @description       Check the width and height getters
 */
int UtcTextureGetWidthHeight(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Texture_TestApp testApp( application, TEXTURE_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

