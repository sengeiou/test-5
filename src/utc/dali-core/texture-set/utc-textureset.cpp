#include "utc-textureset-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;


void utc_textureset_startup(void)
{
  test_return_value = 0;
}

void utc_textureset_cleanup(void)
{

}

void TextureSetConstructorAndNew();
void TextureSetDownCastP();
void TextureSetDownCastN();
void TextureSetAssignmentOperator();
void TextureSetSetGetTexture();
void TextureSetSetGetSampler();

namespace
{
  enum TEST_CASES_LIST_TEXTURESET
  {
    TEXTURESET_CONSTRUCTOR_AND_NEW,
    TEXTURESET_DOWN_CAST_POSITIVE,
    TEXTURESET_DOWN_CAST_NEGATIVE,
    TEXTURESET_ASSIGNMENT_OPERATOR,
    TEXTURESET_SET_GET_TEXTURE,
    TEXTURESET_SET_GET_SAMPLER,
  };

  struct TextureSet_TestApp : public ConnectionTracker
  {
    TextureSet_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &TextureSet_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &TextureSet_TestApp::Tick );
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
        case TEXTURESET_CONSTRUCTOR_AND_NEW:
        TextureSetConstructorAndNew();
        break;
        case TEXTURESET_DOWN_CAST_POSITIVE:
        TextureSetDownCastP();
        break;
        case TEXTURESET_DOWN_CAST_NEGATIVE:
        TextureSetDownCastN();
        break;
        case TEXTURESET_ASSIGNMENT_OPERATOR:
        TextureSetAssignmentOperator();
        break;
        case TEXTURESET_SET_GET_TEXTURE:
        TextureSetSetGetTexture();
        break;
        case TEXTURESET_SET_GET_SAMPLER:
        TextureSetSetGetSampler();
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

void TextureSetConstructorAndNew()
{
  TextureSet textureset;
  DALI_CHECK_FAIL( textureset, "TextureSet constructor failed" );

  textureset = TextureSet::New();
  DALI_CHECK_FAIL( !textureset, "TextureSet::New failed" );

  DaliLog::PrintPass();
}

void TextureSetDownCastP()
{
  TextureSet textureset = TextureSet::New();

  BaseHandle handle( textureset );
  TextureSet textureset2 = TextureSet::DownCast( handle );
  DALI_CHECK_FAIL( !textureset2, "TextureSet::DownCast failed" );

  DaliLog::PrintPass();
}

void TextureSetDownCastN()
{
  Handle handle = Handle::New();
  TextureSet textureset = TextureSet::DownCast( handle );

  DALI_CHECK_FAIL( textureset, "TextureSet::DownCast Negative test failed" );

  DaliLog::PrintPass();
}

void TextureSetAssignmentOperator()
{
  TextureSet textureset1 = TextureSet::New();
  TextureSet textureset2 = TextureSet::New();
  DALI_CHECK_FAIL( ! ( textureset1 != textureset2 ), "TextureSet::operator= test failed" );

  textureset2 = textureset1;
  DALI_CHECK_FAIL( ! ( textureset1 == textureset2 ), "TextureSet::operator= test failed" );

  DaliLog::PrintPass();
}

void TextureSetSetGetTexture()
{
  Texture texture = Texture::New( TextureType::TEXTURE_2D, Pixel::RGBA8888, 64, 64 );

  TextureSet textureset = TextureSet::New();
  DALI_CHECK_FAIL( ! ( textureset.GetTextureCount() == 0 ), "TextureSet::SetTexture test failed" );
  textureset.SetTexture( 0, texture );

  Texture returnedTexture = textureset.GetTexture(0);
  DALI_CHECK_FAIL( ! ( returnedTexture.GetWidth() == 64 ), "TextureSet::GetTexture test failed" );
  DALI_CHECK_FAIL( ! ( returnedTexture.GetHeight() == 64 ), "TextureSet::GetTexture test failed" );

  DaliLog::PrintPass();
}

void TextureSetSetGetSampler()
{
  Sampler sampler = Sampler::New();
  sampler.SetFilterMode( FilterMode::NEAREST, FilterMode::NEAREST );

  TextureSet textureset = TextureSet::New();
  textureset.SetSampler( 0, sampler );

  DALI_CHECK_FAIL( ! ( textureset.GetSampler(0) == sampler ), "TextureSet::GetSampler test failed" );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase          UtcTextureSetConstructorAndNew
 * @since_tizen       3.0
 * @description       Check whether the default constructor and New method works
 */
int UtcTextureSetConstructorAndNew(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  TextureSet_TestApp testApp( application, TEXTURESET_CONSTRUCTOR_AND_NEW);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcTextureSetDownCastP
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcTextureSetDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  TextureSet_TestApp testApp( application, TEXTURESET_DOWN_CAST_POSITIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcTextureSetAssignmentOperator
 * @since_tizen       3.0
 * @description       Check assignment operator
 */
int UtcTextureSetAssignmentOperator(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  TextureSet_TestApp testApp( application, TEXTURESET_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcTextureSetDownCastN
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcTextureSetDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  TextureSet_TestApp testApp( application, TEXTURESET_DOWN_CAST_NEGATIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcTextureSetSetGetTexture
 * @since_tizen       3.0
 * @description       Check setting and then retrieving of a texture
 */
int UtcTextureSetSetGetTexture(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  TextureSet_TestApp testApp( application, TEXTURESET_SET_GET_TEXTURE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcTextureSetSetGetSampler
 * @since_tizen       3.0
 * @description       Check setting and then retrieving of a sampler
 */
int UtcTextureSetSetGetSampler(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  TextureSet_TestApp testApp( application, TEXTURESET_SET_GET_SAMPLER);
  application.MainLoop();
  return test_return_value;
}

