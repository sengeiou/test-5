#include "utc-dali-key-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function      utc_Dali_Key_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */

void utc_Dali_Key_startup(void)
{
  test_return_value=0;
}

/**
 * @function      utc__Dali_Key_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */

void utc_Dali_Key_cleanup(void)
{
}


void IsKeyP();


namespace
{
  enum TEST_CASES_LIST_ISKEY
  {
    ISKEY_P,
  };

  struct IsKey_TestApp : public ConnectionTracker
  {
    IsKey_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &IsKey_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &IsKey_TestApp::Tick );
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
        case ISKEY_P:
          IsKeyP();
          break;
      }
    }

    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

} // unnamed namespace


struct KeyLookup
{
  const char* keyName;          ///< XF86 key name
  const Dali::KEY daliKeyCode;  ///< Dali key code
  const bool  deviceButton;     ///< Whether the key is from a button on the device
};

// Common keys for all platforms
KeyLookup KeyLookupTable[]=
{
  { "Escape",                DALI_KEY_ESCAPE,          false },  // item not defined in utilX
  { "Menu",                  DALI_KEY_MENU,            false },  // item not defined in utilX

  // Now the key names are used as literal string not defined symbols,
  // since these definition in utilX.h is deprecated and we're guided not to use them
  { "XF86Camera",            DALI_KEY_CAMERA,          false },
  { "XF86Camera_Full",       DALI_KEY_CONFIG,          false },
  { "XF86PowerOff",          DALI_KEY_POWER,           true  },
  { "XF86Standby",           DALI_KEY_PAUSE,           false },
  { "Cancel",                DALI_KEY_CANCEL,          false },
  { "XF86AudioPlay",         DALI_KEY_PLAY_CD,         false },
  { "XF86AudioStop",         DALI_KEY_STOP_CD,         false },
  { "XF86AudioPause",        DALI_KEY_PAUSE_CD,        false },
  { "XF86AudioNext",         DALI_KEY_NEXT_SONG,       false },
  { "XF86AudioPrev",         DALI_KEY_PREVIOUS_SONG,   false },
  { "XF86AudioRewind",       DALI_KEY_REWIND,          false },
  { "XF86AudioForward",      DALI_KEY_FASTFORWARD,     false },
  { "XF86AudioMedia",        DALI_KEY_MEDIA,           false },
  { "XF86AudioPlayPause",    DALI_KEY_PLAY_PAUSE,      false },
  { "XF86AudioMute",         DALI_KEY_MUTE,            false },
  { "XF86Menu",              DALI_KEY_MENU,            true  },
  { "XF86Home",              DALI_KEY_HOME,            true  },
  { "XF86Back",              DALI_KEY_BACK,            true  },
  { "XF86HomePage",          DALI_KEY_HOMEPAGE,        false },
  { "XF86WWW",               DALI_KEY_WEBPAGE,         false },
  { "XF86Mail",              DALI_KEY_MAIL,            false },
  { "XF86ScreenSaver",       DALI_KEY_SCREENSAVER,     false },
  { "XF86MonBrightnessUp",   DALI_KEY_BRIGHTNESS_UP,   false },
  { "XF86MonBrightnessDown", DALI_KEY_BRIGHTNESS_DOWN, false },
  { "XF86SoftKBD",           DALI_KEY_SOFT_KBD,        false },
  { "XF86QuickPanel",        DALI_KEY_QUICK_PANEL,     false },
  { "XF86TaskPane",          DALI_KEY_TASK_SWITCH,     false },
  { "XF86Apps",              DALI_KEY_APPS,            false },
  { "XF86Search",            DALI_KEY_SEARCH,          false },
  { "XF86Voice",             DALI_KEY_VOICE,           false },
  { "Hangul",                DALI_KEY_LANGUAGE,        false },
  { "XF86AudioRaiseVolume",  DALI_KEY_VOLUME_UP,       true  },
  { "XF86AudioLowerVolume",  DALI_KEY_VOLUME_DOWN,     true  },
};

const std::size_t KEY_LOOKUP_COUNT = (sizeof( KeyLookupTable))/ (sizeof(KeyLookup));


// Generate a KeyPressEvent to send to Core
Dali::KeyEvent GenerateKeyPress( const std::string& keyName )
{
  KeyEvent keyPress;
  keyPress.keyPressedName = keyName;
  return keyPress;
}


void IsKeyP()
{
  for ( std::size_t i = 0; i < KEY_LOOKUP_COUNT; ++i )
  {
    KeyEvent kp =    GenerateKeyPress( KeyLookupTable[i].keyName );
    DALI_CHECK_FAIL(IsKey(kp,KeyLookupTable[i].daliKeyCode ) == false, "IsKey lookup is failing");
  }

  DaliLog::PrintPass();
}


/**
 * @testcase        UtcDaliIsKeyP
 * @since_tizen     2.4
 * @description     Positive test case for IsKey
 */

int UtcDaliIsKeyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  IsKey_TestApp testApp( application, ISKEY_P);
  application.MainLoop();
  return test_return_value;
}
