#include "utc-dali-pixel-common.h"

//& set: Pixel

/**
 * @function            utc_Dali_Pixel_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Pixel_startup(void)
{
}

/**
 * @function            utc_Dali_Pixel_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Pixel_cleanup(void)
{
}

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

void PixelHasAlphaP();
void PixelGetBytesPerPixelP();
void PixelGetAlphaOffsetAndMaskP();

namespace
{
  enum TEST_CASES_LIST_PIXEL
  {
    PIXEL_HAS_ALPHA_P,
    PIXEL_GET_BYTES_PER_PIXEL_P,
    PIXEL_GET_ALPHA_OFF_SET_AND_MASK_P
  };

  struct Pixel_TestApp : public ConnectionTracker
  {
    Pixel_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Pixel_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Pixel_TestApp::Tick );
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
        case PIXEL_HAS_ALPHA_P:
          PixelHasAlphaP();
          break;

        case PIXEL_GET_BYTES_PER_PIXEL_P:
          PixelGetBytesPerPixelP();
          break;

        case PIXEL_GET_ALPHA_OFF_SET_AND_MASK_P:
          PixelGetAlphaOffsetAndMaskP();
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
void PixelHasAlphaP()
{
  bool bHasAlpha = false;
  Pixel::Format pixelFormatGet;
  string strPixelVal = "";

  for ( int nIndex = 0; nIndex < gPixelEnumSize; nIndex++ )
  {
    if ( !PixelSetGetforImageAttributes(gPixelFormatA[ nIndex ], pixelFormatGet) )
    {
      test_return_value=1;
      return;
    }

    bHasAlpha = Pixel::HasAlpha( pixelFormatGet );

    if( nIndex <= gPixelEnumSize/2 && bHasAlpha )
    {
      strPixelVal = gPixelEnumList[ pixelFormatGet - 1 ].c_str() ;
      LOG_E("Pixel::HasAlpha is failed to return false for Pixel");
      test_return_value=1;
      return;
    }

    if( nIndex > gPixelEnumSize/2 && !bHasAlpha )
    {
      strPixelVal = gPixelEnumList[ pixelFormatGet - 1 ].c_str() ;
      LOG_E("Pixel::HasAlpha is failed to return true for Pixel");
      test_return_value=1;
      return;
    }

    bHasAlpha = false;
  }

  DaliLog::PrintPass();
}
void PixelGetBytesPerPixelP()
{
  unsigned int uGetPixelByte = 0u;
  Pixel::Format pixelFormatGet;
  string strPixelVal = "";

  for ( int nIndex = 0; nIndex < gPixelEnumSize; nIndex++ )
  {
    if ( !PixelSetGetforImageAttributes(gPixelFormatA[ nIndex ], pixelFormatGet) )
    {
      test_return_value=1;
      return;
    }

    uGetPixelByte = Pixel::GetBytesPerPixel( pixelFormatGet );
    if( uGetPixelByte != gPixelBytePerPxl[ nIndex ] )
    {
      strPixelVal = gPixelEnumList[ pixelFormatGet-1 ].c_str() ;
      LOG_E("Pixel::GetBytesPerPixel is failed to get bytes per pixel for Pixel");
      test_return_value=1;
      return;
    }

    strPixelVal = "";
    uGetPixelByte = 0u;
  }

  DaliLog::PrintPass();
}
void PixelGetAlphaOffsetAndMaskP()
{
  int nbyteOffset = 0;
  int nbitMask = 0;
  Pixel::Format pixelFormatGet;
  string strPixelVal = "";

  for ( int nIndex = 0; nIndex < gPixelEnumSize; nIndex++ )
  {
    if ( !PixelSetGetforImageAttributes(gPixelFormatA[ nIndex ], pixelFormatGet) )
    {
      test_return_value=1;
      return;
    }

    Pixel::GetAlphaOffsetAndMask( pixelFormatGet, nbyteOffset, nbitMask );
    if( nbyteOffset != gPixelByteOffset[ nIndex ] )
    {
      strPixelVal = gPixelEnumList[ pixelFormatGet - 1 ].c_str();
      LOG_E("Pixel::GetAlphaOffsetAndMask is failed to returns the offset of alpha mask containing byte for Pixel");
      test_return_value=1;
      return;
    }

    if( nbitMask != gPixelBitMask[ nIndex ] )
    {
      strPixelVal = gPixelEnumList[ pixelFormatGet - 1 ].c_str();
      LOG_E("Pixel::GetAlphaOffsetAndMask is failed to return the bitmask of alpha mask containing byte to get the alpha value for Pixel");
      test_return_value=1;
      return;
    }

    strPixelVal = "";
    nbyteOffset = 0;
    nbitMask = 0;
  }

  DaliLog::PrintPass();
}



/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliPixelHasAlphaP
 * @since_tizen         2.4
 * @description         check if HasAlpha api works or not.
 */

int UtcDaliPixelHasAlphaP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Pixel_TestApp testApp( application, PIXEL_HAS_ALPHA_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliPixelGetBytesPerPixelP
 * @since_tizen         2.4
 * @description         check if GetBytesPerPixel api works or not.
 */

int UtcDaliPixelGetBytesPerPixelP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Pixel_TestApp testApp( application, PIXEL_GET_BYTES_PER_PIXEL_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliPixelGetAlphaOffsetAndMaskP
 * @since_tizen         2.4
 * @description         check if GetAlphaOffsetAndMask api works or not.
 */

int UtcDaliPixelGetAlphaOffsetAndMaskP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Pixel_TestApp testApp( application, PIXEL_GET_ALPHA_OFF_SET_AND_MASK_P);
  application.MainLoop();
  return test_return_value;
}
