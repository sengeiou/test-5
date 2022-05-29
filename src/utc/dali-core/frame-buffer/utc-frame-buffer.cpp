#include "utc-frame-buffer-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: FrameBuffer

void utc_frame_buffer_startup(void)
{
  test_return_value = 0;
}

void utc_frame_buffer_cleanup(void)
{

}

void FrameBufferConstructorAndNew();
void FrameBufferDownCastP();
void FrameBufferDownCastN();
void FrameBufferAssignmentOperator();
void FrameBufferAttachAndGetColorTexture01();
void FrameBufferAttachAndGetColorTexture02();
void FrameBufferNewWithColor01();
void FrameBufferNewWithColor02();
void FrameBufferNewWithColor03();
void FrameBufferNewWithColor04();
void FrameBufferNewWithColor05();


namespace
{
  enum TEST_CASES_LIST_FRAMEBUFFER
  {
    FRAMEBUFFER_CONSTRUCTOR_AND_NEW,
    FRAMEBUFFER_DOWN_CAST_POSITIVE,
    FRAMEBUFFER_DOWN_CAST_NEGATIVE,
    FRAMEBUFFER_ASSIGNMENT_OPERATOR,
    FRAMEBUFFER_ATTACH_AND_GET_COLOR_TEXTURE_01,
    FRAMEBUFFER_ATTACH_AND_GET_COLOR_TEXTURE_02,
    FRAMEBUFFER_NEW_WITH_COLOR_01,
    FRAMEBUFFER_NEW_WITH_COLOR_02,
    FRAMEBUFFER_NEW_WITH_COLOR_03,
    FRAMEBUFFER_NEW_WITH_COLOR_04,
    FRAMEBUFFER_NEW_WITH_COLOR_05,
  };

  struct FrameBuffer_TestApp : public ConnectionTracker
  {
    FrameBuffer_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &FrameBuffer_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &FrameBuffer_TestApp::Tick );
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
        case FRAMEBUFFER_CONSTRUCTOR_AND_NEW:
        FrameBufferConstructorAndNew();
        break;
        case FRAMEBUFFER_DOWN_CAST_POSITIVE:
        FrameBufferDownCastP();
        break;
        case FRAMEBUFFER_DOWN_CAST_NEGATIVE:
        FrameBufferDownCastN();
        break;
        case FRAMEBUFFER_ASSIGNMENT_OPERATOR:
        FrameBufferAssignmentOperator();
        break;
        case FRAMEBUFFER_ATTACH_AND_GET_COLOR_TEXTURE_01:
        FrameBufferAttachAndGetColorTexture01();
        break;
        case FRAMEBUFFER_ATTACH_AND_GET_COLOR_TEXTURE_02:
        FrameBufferAttachAndGetColorTexture02();
        break;
        case FRAMEBUFFER_NEW_WITH_COLOR_01:
        FrameBufferNewWithColor01();
        break;
        case FRAMEBUFFER_NEW_WITH_COLOR_02:
        FrameBufferNewWithColor02();
        break;
        case FRAMEBUFFER_NEW_WITH_COLOR_03:
        FrameBufferNewWithColor03();
        break;
        case FRAMEBUFFER_NEW_WITH_COLOR_04:
        FrameBufferNewWithColor04();
        break;
        case FRAMEBUFFER_NEW_WITH_COLOR_05:
        FrameBufferNewWithColor05();
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

void FrameBufferConstructorAndNew()
{
  FrameBuffer frameBuffer;
  DALI_CHECK_FAIL( frameBuffer, "FrameBuffer constructor failed" );

  frameBuffer = FrameBuffer::New( 64, 64, FrameBuffer::Attachment::NONE );
  DALI_CHECK_FAIL( !frameBuffer, "FrameBuffer::New failed" );

  DaliLog::PrintPass();
}

void FrameBufferDownCastP()
{
  FrameBuffer frameBuffer = FrameBuffer::New( 64, 64, FrameBuffer::Attachment::NONE );

  BaseHandle handle( frameBuffer );
  FrameBuffer frameBuffer2 = FrameBuffer::DownCast( handle );
  DALI_CHECK_FAIL( !frameBuffer2, "FrameBuffer::DownCast failed" );

  DaliLog::PrintPass();
}

void FrameBufferDownCastN()
{
  Handle handle = Handle::New();
  FrameBuffer frameBuffer = FrameBuffer::DownCast( handle );

  DALI_CHECK_FAIL( frameBuffer, "FrameBuffer::DownCast Negative test failed" );

  DaliLog::PrintPass();
}

void FrameBufferAssignmentOperator()
{
  FrameBuffer frameBuffer1 = FrameBuffer::New( 64, 64, FrameBuffer::Attachment::NONE );
  FrameBuffer frameBuffer2 = FrameBuffer::New( 64, 64, FrameBuffer::Attachment::NONE );
  DALI_CHECK_FAIL( ! ( frameBuffer1 != frameBuffer2 ), "FrameBuffer::operator= test failed" );

  frameBuffer2 = frameBuffer1;
  DALI_CHECK_FAIL( ! ( frameBuffer1 == frameBuffer2 ), "FrameBuffer::operator= test failed" );

  DaliLog::PrintPass();
}

void FrameBufferAttachAndGetColorTexture01()
{
  FrameBuffer frameBuffer = FrameBuffer::New( 64, 64, FrameBuffer::Attachment::NONE );
  Texture texture = Texture::New( TextureType::TEXTURE_2D, Pixel::RGBA8888, 64, 64 );
  frameBuffer.AttachColorTexture( texture );

  DALI_CHECK_FAIL( !( frameBuffer.GetColorTexture() == texture ), "FrameBuffer::AttachColorTexture failed" );

  DaliLog::PrintPass();
}

void FrameBufferAttachAndGetColorTexture02()
{
  FrameBuffer frameBuffer = FrameBuffer::New( 64, 64, FrameBuffer::Attachment::NONE );
  Texture texture = Texture::New( TextureType::TEXTURE_2D, Pixel::RGBA8888, 64, 64 );
  frameBuffer.AttachColorTexture( texture, 0u, 1u );

  DALI_CHECK_FAIL( !( frameBuffer.GetColorTexture() == texture ), "FrameBuffer::AttachColorTexture Test 2 failed" );

  DaliLog::PrintPass();
}

void FrameBufferNewWithColor01()
{
  uint32_t width = 64;
  uint32_t height = 64;
  FrameBuffer frameBuffer = FrameBuffer::New( width, height );

  DALI_CHECK_FAIL( !frameBuffer, "FrameBuffer::New failed" );

  DaliLog::PrintPass();
}

void FrameBufferNewWithColor02()
{
  uint32_t width = 64;
  uint32_t height = 64;
  FrameBuffer frameBuffer = FrameBuffer::New( width, height, FrameBuffer::Attachment::COLOR );

  DALI_CHECK_FAIL( !frameBuffer, "FrameBuffer::New failed" );

  DaliLog::PrintPass();
}

void FrameBufferNewWithColor03()
{
  uint32_t width = 64;
  uint32_t height = 64;
  FrameBuffer frameBuffer = FrameBuffer::New( width, height, FrameBuffer::Attachment::COLOR_DEPTH );

  DALI_CHECK_FAIL( !frameBuffer, "FrameBuffer::New failed" );

  DaliLog::PrintPass();
}

void FrameBufferNewWithColor04()
{
  uint32_t width = 64;
  uint32_t height = 64;
  FrameBuffer frameBuffer = FrameBuffer::New( width, height, FrameBuffer::Attachment::COLOR_STENCIL );

  DALI_CHECK_FAIL( !frameBuffer, "FrameBuffer::New failed" );

  DaliLog::PrintPass();
}

void FrameBufferNewWithColor05()
{
  uint32_t width = 64;
  uint32_t height = 64;
  FrameBuffer frameBuffer = FrameBuffer::New( width, height, FrameBuffer::Attachment::COLOR_DEPTH_STENCIL );

  DALI_CHECK_FAIL( !frameBuffer, "FrameBuffer::New failed" );

  DaliLog::PrintPass();
}


/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase          UtcFrameBufferConstructorAndNew
 * @since_tizen      3.0
 * @description      Check whether the default constructor and New mothod works
 */
int UtcFrameBufferConstructorAndNew(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  FrameBuffer_TestApp testApp( application, FRAMEBUFFER_CONSTRUCTOR_AND_NEW);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcFrameBufferDownCastP
 * @since_tizen     3.0
 * @description     Check DownCast
 */
int UtcFrameBufferDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  FrameBuffer_TestApp testApp( application, FRAMEBUFFER_DOWN_CAST_POSITIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcFrameBufferDownCastN
 * @since_tizen      3.0
 * @description      Check DownCast
 */
int UtcFrameBufferDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  FrameBuffer_TestApp testApp( application, FRAMEBUFFER_DOWN_CAST_NEGATIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcFrameBufferAssignmentOperator
 * @since_tizen      3.0
 * @description      Check assignment operator
 */
int UtcFrameBufferAssignmentOperator(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  FrameBuffer_TestApp testApp( application, FRAMEBUFFER_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcFrameBufferAttachAndGetColorTexture01
 * @since_tizen      3.0
 * @description      Attach a texture and ensure the same one can be retrieved
 */
int UtcFrameBufferAttachAndGetColorTexture01(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  FrameBuffer_TestApp testApp( application, FRAMEBUFFER_ATTACH_AND_GET_COLOR_TEXTURE_01);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcFrameBufferAttachAndGetColorTexture02
 * @since_tizen      3.0
 * @description      Attach a texture and ensure the same one can be retrieved
 */
int UtcFrameBufferAttachAndGetColorTexture02(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  FrameBuffer_TestApp testApp( application, FRAMEBUFFER_ATTACH_AND_GET_COLOR_TEXTURE_02);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcFrameBufferNewWithColor01
 * @since_tizen      5.5
 * @description      Check New method with FrameBuffer::Attachment parameter
 */
int UtcFrameBufferNewWithColor01(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  FrameBuffer_TestApp testApp( application, FRAMEBUFFER_NEW_WITH_COLOR_01 );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcFrameBufferNewWithColor02
 * @since_tizen      5.5
 * @description      Check New method with FrameBuffer::Attachment parameter
 */
int UtcFrameBufferNewWithColor02(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  FrameBuffer_TestApp testApp( application, FRAMEBUFFER_NEW_WITH_COLOR_02 );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcFrameBufferNewWithColor03
 * @since_tizen      5.5
 * @description      Check New method with FrameBuffer::Attachment parameter
 */
int UtcFrameBufferNewWithColor03(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  FrameBuffer_TestApp testApp( application, FRAMEBUFFER_NEW_WITH_COLOR_03 );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcFrameBufferNewWithColor04
 * @since_tizen      5.5
 * @description      Check New method with FrameBuffer::Attachment parameter
 */
int UtcFrameBufferNewWithColor04(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  FrameBuffer_TestApp testApp( application, FRAMEBUFFER_NEW_WITH_COLOR_04 );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcFrameBufferNewWithColor02
 * @since_tizen      5.5
 * @description      Check New method with FrameBuffer::Attachment parameter
 */
int UtcFrameBufferNewWithColor05(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  FrameBuffer_TestApp testApp( application, FRAMEBUFFER_NEW_WITH_COLOR_05 );
  application.MainLoop();
  return test_return_value;
}
