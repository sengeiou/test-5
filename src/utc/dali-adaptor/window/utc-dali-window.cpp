#include "utc-dali-window-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

bool gBoolSignalReceived( false );
bool gBoolSignalReceived2( false );
bool gBoolWindowVerify( false );

/**
 * @function        utc_Dali_Window_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */

void utc_Dali_Window_startup(void)
{
  test_return_value=0;
}


/**
 * @function        utc_Dali_Window_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */

void utc_Dali_Window_cleanup(void)
{
}

void WindowIndicatorVisibilityChangedSignalP(Application& mApplication);
void WindowNewP( Window& newWindow );
void WindowNewP2( Window& newWindow );
void WindowCheckConstructorP();
void WindowCheckCopyConstructorP( Window& newWindow );
void WindowCheckSetClassP(Application& mApplication);
void WindowConstructorNewAssignmentOperatorP(Application& mApplication);
void WindowSetPreferredOrientationP(Application& mApplication);
void WindowGetDefaultPreferredOrientationP(Application& mApplication);
void WindowGetNativeHandleP(Application& mApplication);
void WindowAddAvailableOrientationN(Application& mApplication);
void WindowRemoveAvailableOrientationN(Application& mApplication);
void WindowLowerP(Application& mApplication);
void WindowRaiseP(Application& mApplication);
void WindowActivateP(Application& mApplication);
void WindowSetClassSetIndicatorBgOpacityP(Application& mApplication);
void WindowShowIndicatorP(Application& mApplication);
void WindowRotateIndicatorP(Application& mApplication);
void WindowSetAcceptFocusIsFocusAcceptableP( Application& application );
void WindowShowHideIsVisibleP( Application& application );
void WindowAuxiliaryHintTestP( Application& application );
void WindowSetGetTypeP( Application& application );
void WindowSetGetNotificationLevelP( Application& application );
void WindowSetOpaqueStateIsOpaqueStateP( Application& application );
void WindowSetGetScreenOffModeP( Application& application );
void WindowSetGetBrightnessP( Application& application );
void WindowSetGetSizeResizedSignalP( Application& application );
void WindowSetGetSizeResizedSignalP2( Application& application );
void WindowSetGetPositionP( Application& application );
void WindowAddRemoveActorP( Application& application );
void WindowSetGetBackgroundColorP( Application& application );
void WindowGetRootLayerP( Application& application );
void WindowGetLayerCountP( Application& application );
void WindowGetLayerP( Application& application );

void VTWindowSetGetSizeResizedSignal001( Application& application );
void VTWindowSetGetSizeResizedSignal002( Application& application );

void WindowResizedCallback( Window::WindowSize windowSize )
{
  gBoolSignalReceived = true;
}

void WindowResizedCallback2( Window window, Window::WindowSize windowSize )
{
  gBoolSignalReceived2 = true;
  if( window )
    gBoolWindowVerify = true;
}


class WindowIndicatorSignalHandler : public Dali::ConnectionTracker
{
  public:
    WindowIndicatorSignalHandler() :
      mCalls( 0 )
  {
  }

    void Callback( bool visible )
    {
      mCalls++;
    }

    unsigned int GetCalls() const
    {
      return mCalls;
    }

  private:
    unsigned int mCalls;
};

namespace
{
  enum TEST_CASES_LIST_WINDOW
  {
    WINDOW_INDICATOR_VISIBILITY_CHANGE_P,
    WINDOW_NEW_P,
    WINDOW_NEW_P2,
    WINDOW_CONSTRUCTOR_P,
    WINDOW_COPY_CONSTRUCTOR_P,
    WINDOW_SET_CLASS_P,
    WINDOW_CONSTRUCTOR_NEW_ASSIGNMENT_OPERATOR_P,
    WINDOW_SET_PREFERRED_ORIENTATION_P,
    WINDOW_GET_PREFERRED_ORIENTATION_P,
    WINDOW_GET_DRAGAND_DROP_DETECTOR_P,
    WINDOW_GET_NATIVE_HANDLE_P,
    WINDOW_ADD_AVAILABLE_ORIENTATION_N,
    WINDOW_REMOVE_AVAILABLE_ORIENTATION_N,
    WINDOW_LOWER_P,
    WINDOW_RAISE_P,
    WINDOW_ACTIVATE_P,
    WINDOW_SET_CLASS_SET_INDICATOR_BGOPACITY_P,
    WINDOW_SHOW_INDICATOR_P,
    WINDOW_ROTATE_INDICATOR_P,
    WINDOW_SET_ACCEPT_FOCUS_P,
    WINDOW_SHOW_HIDE_IS_VISIBLE_P,
    WINDOW_AUXILIARY_HINT_TEST_P,
    WINDOW_SET_GET_TYPE_P,
    WINDOW_SET_GET_NOTIFICATION_LEVEL_P,
    WINDOW_SET_OPAQUE_STATE_IS_OPAQUE_STATE_P,
    WINDOW_SET_GET_SCREEN_OFF_MODE_P,
    WINDOW_SET_GET_BRIGHTNESS_P,
    WINDOW_SET_GET_SIZE_RESIZED_SIGNAL_P,
    WINDOW_SET_GET_SIZE_RESIZED_SIGNAL_P2,
    WINDOW_SET_GET_POSITION_P,
    WINDOW_ADD_REMOVE_ACTOR_P,
    WINDOW_SET_GET_BACKGROUND_COLOR_P,
    WINDOW_GET_ROOT_LAYER_P,
    WINDOW_GET_LAYER_COUNT_P,
    WINDOW_GET_LAYER_P
  };

  struct Window_TestApp : public ConnectionTracker
  {
    Window_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case ),
      mNewWindow()
    {
      mApplication.InitSignal().Connect( this, &Window_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Window_TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      if( test_return_value == TC_FAIL )
      {
        mTimer.Stop();
        mApplication.Quit();
        return true;
      }

      VerdictTest();

      if( test_return_value == TC_FAIL )
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
        case WINDOW_INDICATOR_VISIBILITY_CHANGE_P:
          WindowIndicatorVisibilityChangedSignalP(mApplication);
          break;

        case WINDOW_NEW_P:
          WindowNewP( mNewWindow );
          break;

        case WINDOW_NEW_P2:
          WindowNewP2( mNewWindow );
          break;

        case WINDOW_CONSTRUCTOR_P:
          WindowCheckConstructorP();
          break;

        case WINDOW_COPY_CONSTRUCTOR_P:
          WindowCheckCopyConstructorP( mNewWindow );
          break;

        case WINDOW_SET_CLASS_P:
          WindowCheckSetClassP(mApplication);
          break;

        case WINDOW_CONSTRUCTOR_NEW_ASSIGNMENT_OPERATOR_P:
          WindowConstructorNewAssignmentOperatorP(mApplication);
          break;

        case WINDOW_SET_PREFERRED_ORIENTATION_P:
          WindowSetPreferredOrientationP(mApplication);
          break;

        case WINDOW_GET_PREFERRED_ORIENTATION_P:
          WindowGetDefaultPreferredOrientationP(mApplication);
          break;

        case WINDOW_GET_NATIVE_HANDLE_P:
          WindowGetNativeHandleP(mApplication);
          break;

        case WINDOW_ADD_AVAILABLE_ORIENTATION_N:
          WindowAddAvailableOrientationN(mApplication);
          break;

        case WINDOW_REMOVE_AVAILABLE_ORIENTATION_N:
          WindowRemoveAvailableOrientationN(mApplication);
          break;

        case WINDOW_LOWER_P:
          WindowLowerP(mApplication);
          break;

        case WINDOW_RAISE_P:
          WindowRaiseP(mApplication);
          break;

        case WINDOW_ACTIVATE_P:
          WindowActivateP(mApplication);
          break;

        case WINDOW_SET_CLASS_SET_INDICATOR_BGOPACITY_P:
          WindowSetClassSetIndicatorBgOpacityP(mApplication);
          break;

        case WINDOW_SHOW_INDICATOR_P:
          WindowShowIndicatorP(mApplication);
          break;

        case WINDOW_ROTATE_INDICATOR_P:
          WindowRotateIndicatorP(mApplication);
          break;

        case WINDOW_SET_ACCEPT_FOCUS_P:
          WindowSetAcceptFocusIsFocusAcceptableP( mApplication );
          break;

        case WINDOW_SHOW_HIDE_IS_VISIBLE_P:
          WindowShowHideIsVisibleP( mApplication );
          break;

        case WINDOW_AUXILIARY_HINT_TEST_P:
          WindowAuxiliaryHintTestP( mApplication );
          break;

        case WINDOW_SET_GET_TYPE_P:
          WindowSetGetTypeP( mApplication );
          break;

        case WINDOW_SET_GET_NOTIFICATION_LEVEL_P:
          WindowSetGetNotificationLevelP( mApplication );
          break;

        case WINDOW_SET_OPAQUE_STATE_IS_OPAQUE_STATE_P:
          WindowSetOpaqueStateIsOpaqueStateP( mApplication );
          break;

        case WINDOW_SET_GET_SCREEN_OFF_MODE_P:
          WindowSetGetScreenOffModeP( mApplication );
          break;

        case WINDOW_SET_GET_BRIGHTNESS_P:
          WindowSetGetBrightnessP( mApplication );
          break;

        case WINDOW_SET_GET_SIZE_RESIZED_SIGNAL_P:
          WindowSetGetSizeResizedSignalP( mApplication );
          break;

        case WINDOW_SET_GET_SIZE_RESIZED_SIGNAL_P2:
          WindowSetGetSizeResizedSignalP2( mApplication );
          break;

        case WINDOW_SET_GET_POSITION_P:
          WindowSetGetPositionP( mApplication );
          break;

        case WINDOW_ADD_REMOVE_ACTOR_P:
          WindowAddRemoveActorP( mApplication );
          break;

        case WINDOW_SET_GET_BACKGROUND_COLOR_P:
          WindowSetGetBackgroundColorP( mApplication );
          break;

        case WINDOW_GET_ROOT_LAYER_P:
          WindowGetRootLayerP( mApplication );
          break;

        case WINDOW_GET_LAYER_COUNT_P:
          WindowGetLayerCountP( mApplication );
          break;

        case WINDOW_GET_LAYER_P:
          WindowGetLayerP( mApplication );
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case WINDOW_SET_GET_SIZE_RESIZED_SIGNAL_P:
          VTWindowSetGetSizeResizedSignal001( mApplication );
          mTimer.Stop();
          mApplication.Quit();
          break;

        case WINDOW_SET_GET_SIZE_RESIZED_SIGNAL_P2:
          VTWindowSetGetSizeResizedSignal002( mApplication );
          mTimer.Stop();
          mApplication.Quit();
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
    Window mNewWindow;
  };

} // unnamed namespace

void WindowCheckConstructorP()
{
  Window window;
  DALI_CHECK_FAIL(window,"Window::New constructor is failed to create initialized window object");

  DaliLog::PrintPass();

}

void WindowCheckCopyConstructorP( Window& newWindow )
{

  try
  {
    PositionSize windowPosition( 0, 0, 1, 1 );
    newWindow = Dali::Window::New( windowPosition, "test-window", true );
    DALI_CHECK_FAIL( !newWindow, "Window::New is failed to create initialized window object" );

    Dali::Window copy( newWindow );
    DALI_CHECK_FAIL( copy != newWindow, "Window::CheckCopyConstructor is failed" );
  }
  catch ( DaliException& e )
  {
    DALI_CHECK_FAIL( true, "Window::New is failed to create initialized window object" );
  }

  DaliLog::PrintPass();
}

void WindowCheckSetClassP(Application& mApplication)
{
  std::string sname;
  std::string skclass;

  try
  {

    sname = "test";
    skclass = "testc";

    Window window = mApplication.GetWindow();
    DALI_CHECK_FAIL(!window,"Window::New constructor is failed to create initialized window object");

    window.SetClass( sname, skclass );
  }
  catch( ... )
  {
    DALI_CHECK_FAIL( true, "Window::CheckSetClass() is failed." );
  }

  DaliLog::PrintPass();
}

void WindowConstructorNewAssignmentOperatorP(Application& mApplication)
{
  Window window = mApplication.GetWindow();
  DALI_CHECK_FAIL(!window,"Window::New constructor is failed to create initialized window object");

  Window copy;
  DALI_CHECK_FAIL( !(copy != window) , "Copy is same as Window" );

  copy = window;
  DALI_CHECK_FAIL( !(copy == window)," Window::ConstructorNewAssignmentOperator is failed");


  DaliLog::PrintPass();
}

void WindowNewP( Window& newWindow )
{
  try
  {
    PositionSize windowPosition( 0, 0, 1, 1 );
    newWindow = Dali::Window::New( windowPosition, "test-window", true );
    DALI_CHECK_FAIL( !newWindow, "Window::New is failed to create initialized window object" );
  }
  catch ( DaliException& e )
  {
    DALI_CHECK_FAIL( true,"Window::New is failed to create initialized window object" );
  }

  DaliLog::PrintPass();
}

void WindowNewP2( Window& newWindow )
{
  try
  {
    PositionSize windowPosition( 0, 0, 1, 1 );
    newWindow = Dali::Window::New( windowPosition, "test-window", "test-window-class", true );
    DALI_CHECK_FAIL( !newWindow, "Window::New is failed to create initialized window object" );
  }
  catch ( DaliException& e )
  {
    DALI_CHECK_FAIL( true, "Window::New is failed to create initialized window object" );
  }

  DaliLog::PrintPass();
}

void WindowSetPreferredOrientationP(Application& mApplication)
{
  Window window = mApplication.GetWindow();
  DALI_CHECK_FAIL(!window,"Window::New constructor is failed to create initialized window object");

  window.AddAvailableOrientation( Dali::Window::PORTRAIT );
  window.AddAvailableOrientation( Dali::Window::LANDSCAPE );
  window.AddAvailableOrientation( Dali::Window::PORTRAIT_INVERSE );
  window.AddAvailableOrientation( Dali::Window::LANDSCAPE_INVERSE );

  window.SetPreferredOrientation( Dali::Window::LANDSCAPE );
  DALI_CHECK_FAIL( !(window.GetPreferredOrientation() == Dali::Window::LANDSCAPE), "Window::SetPreferredOrientationP is failed");

  DaliLog::PrintPass();
}

void WindowGetDefaultPreferredOrientationP(Application& mApplication)
{
  Window window = mApplication.GetWindow();
  DALI_CHECK_FAIL(!window,"Window::New constructor is failed to create initialized window object");

  DALI_CHECK_FAIL( !(window.GetPreferredOrientation() == -1),"Window::GetPreferredOrientation is failed");

  DaliLog::PrintPass();
}

void WindowGetNativeHandleP(Application& mApplication)
{
  Window window = mApplication.GetWindow();
  DALI_CHECK_FAIL(!window,"Window::New constructor is failed to create initialized window object");

  Any any = window.GetNativeHandle();
  DALI_CHECK_FAIL( any.Empty()," window.GetNativeHandle() failed");

  DaliLog::PrintPass();
}


void WindowAddAvailableOrientationN(Application& mApplication)
{
  Window window = mApplication.GetWindow();
  DALI_CHECK_FAIL(!window,"Window::New constructor is failed to create initialized window object");


  try
  {
    window.AddAvailableOrientation( Dali::Window::PORTRAIT );
    window.AddAvailableOrientation( Dali::Window::LANDSCAPE );
    window.AddAvailableOrientation( Dali::Window::PORTRAIT_INVERSE );
    window.AddAvailableOrientation( Dali::Window::LANDSCAPE_INVERSE );
    window.AddAvailableOrientation( static_cast<Dali::Window::WindowOrientation>( 100 ) );
    window.AddAvailableOrientation( static_cast<Dali::Window::WindowOrientation>( 200 ) );
    window.AddAvailableOrientation( static_cast<Dali::Window::WindowOrientation>( 300 ) );
  }
  catch( DaliException& e )
  {
    DALI_CHECK_FAIL( false, "Window::AddAvailableOrientation() is failed." );
  }

  DaliLog::PrintPass();
}

void WindowRemoveAvailableOrientationN(Application& mApplication)
{
  Window window = mApplication.GetWindow();
  DALI_CHECK_FAIL(!window,"Window::New constructor is failed to create initialized window object");


  try
  {
    window.AddAvailableOrientation( Dali::Window::PORTRAIT );
    window.AddAvailableOrientation( Dali::Window::LANDSCAPE );
    window.AddAvailableOrientation( Dali::Window::PORTRAIT_INVERSE );
    window.AddAvailableOrientation( Dali::Window::LANDSCAPE_INVERSE );
    window.RemoveAvailableOrientation( Dali::Window::LANDSCAPE );
    window.RemoveAvailableOrientation( Dali::Window::LANDSCAPE );
    window.RemoveAvailableOrientation( Dali::Window::LANDSCAPE );
    window.AddAvailableOrientation( static_cast<Dali::Window::WindowOrientation>( 100 ) );
    window.RemoveAvailableOrientation( Dali::Window::LANDSCAPE );
    window.AddAvailableOrientation( static_cast<Dali::Window::WindowOrientation>( 200 ) );
    window.AddAvailableOrientation( static_cast<Dali::Window::WindowOrientation>( 300 ) );
  }
  catch( DaliException& e )
  {
    DALI_CHECK_FAIL( false, "Window::RemoveAvailableOrientation() is failed." );
  }
  DaliLog::PrintPass();
}

void WindowLowerP(Application& mApplication)
{
  Window window =  mApplication.GetWindow();
  DALI_CHECK_FAIL(!window,"Window::New constructor is failed to create initialized window object");

  try
  {
    window.Lower();
  }
  catch( ... )
  {
    DALI_CHECK_FAIL( true, "Window::Lower() is failed." );
  }

  DaliLog::PrintPass();
}


void WindowRaiseP(Application& mApplication)
{
  Window window =  mApplication.GetWindow();
  DALI_CHECK_FAIL(!window,"Window::New constructor is failed to create initialized window object");

  try
  {
    window.Raise();
  }
  catch( ... )
  {
    DALI_CHECK_FAIL( true, "Window::Raise() is failed." );
  }

  DaliLog::PrintPass();
}


void WindowActivateP(Application& mApplication)
{
  Window window =  mApplication.GetWindow();
  DALI_CHECK_FAIL(!window,"Window::New constructor is failed to create initialized window object");

  try
  {
    window.Activate();
  }
  catch( ... )
  {
    DALI_CHECK_FAIL( true, "Window::Activate() is failed." );
  }

  DaliLog::PrintPass();
}

void WindowSetClassSetIndicatorBgOpacityP(Application& mApplication)
{
  Window window =  mApplication.GetWindow();
  DALI_CHECK_FAIL( !window ,"Window creation failed" );

  try
  {
    window.ShowIndicator( Dali::Window::VISIBLE );
    window.SetIndicatorBgOpacity( Dali::Window::TRANSLUCENT );
    window.ShowIndicator( Dali::Window::VISIBLE );
  }
  catch( ... )
  {
    DALI_CHECK_FAIL( true, "Window::SetClassSetIndicatorBgOpacity is failed." );
  }

  DaliLog::PrintPass();
}

void WindowShowIndicatorP(Application& mApplication)
{
  Window window =  mApplication.GetWindow();
  DALI_CHECK_FAIL( !window ,"Window creation failed" );

  try
  {
    window.ShowIndicator( Dali::Window::VISIBLE );
  }
  catch( ... )
  {
    DALI_CHECK_FAIL( true, "Window::ShowIndicator is failed." );
  }

  DaliLog::PrintPass();
}


void WindowIndicatorVisibilityChangedSignalP(Application& mApplication)
{
  Window window =  mApplication.GetWindow();
  DALI_CHECK_FAIL( !window ,"Window creation failed" );
  WindowIndicatorSignalHandler callback;
  window.IndicatorVisibilityChangedSignal().Connect(&callback, &WindowIndicatorSignalHandler::Callback);
  try
  {
    window.ShowIndicator( Dali::Window::VISIBLE );
    //DALI_CHECK_FAIL(callback.GetCalls() == 1, "Window::IndicatorVisibilityChangedSignal is failed." );
  }
  catch( ... )
  {
    DALI_CHECK_FAIL( true, "Window::ShowIndicator is failed." );
  }

  DaliLog::PrintPass();
}


void WindowRotateIndicatorP(Application& mApplication)
{
  Window window =  mApplication.GetWindow();
  window.ShowIndicator( Dali::Window::VISIBLE );
  DALI_CHECK_FAIL( !window ,"Window creation failed" );

  try
  {
    window.ShowIndicator( Dali::Window::VISIBLE );
    window.RotateIndicator( Dali::Window::LANDSCAPE_INVERSE );
  }
  catch( ... )
  {
    DALI_CHECK_FAIL( true, "Window::RotateIndicator is failed." );
  }

  DaliLog::PrintPass();
}

void WindowSetAcceptFocusIsFocusAcceptableP( Application& application )
{
  Window window = application.GetWindow();

  window.SetAcceptFocus( true );
  DALI_CHECK_FAIL( window.IsFocusAcceptable() != true, "SetAcceptFocus is failed" );

  window.SetAcceptFocus( false );
  DALI_CHECK_FAIL( window.IsFocusAcceptable() != false, "SetAcceptFocus is failed" );

  DaliLog::PrintPass();
}

void WindowShowHideIsVisibleP( Application& application )
{
  Window window = application.GetWindow();

  window.Show();
  DALI_CHECK_FAIL( window.IsVisible() != true, "Window::Show is failed" );

  window.Hide();
  DALI_CHECK_FAIL( window.IsVisible() != false, "Window::Hide is failed" );

  DaliLog::PrintPass();
}

void WindowAuxiliaryHintTestP( Application& application )
{
  Window window = application.GetWindow();

  int count = window.GetSupportedAuxiliaryHintCount();

  if( count > 0 )
  {
    std::string hint = window.GetSupportedAuxiliaryHint( 0 );
    DALI_CHECK_FAIL( hint.empty(), "Window::GetSupportedAuxiliaryHint is failed" );

    std::string value( "hint value" );

    unsigned int id = window.AddAuxiliaryHint( hint, value );
    std::string returnValue = window.GetAuxiliaryHintValue( id );

    DALI_CHECK_FAIL( returnValue.compare( value ) != 0, "Window::AddAuxiliaryHint and Window::GetAuxiliaryHintValue is failed" );

    std::string newValue( "hint new value" );

    DALI_CHECK_FAIL( !window.SetAuxiliaryHintValue( id, newValue ), "Window::SetAuxiliaryHintValue is failed" );

    returnValue = window.GetAuxiliaryHintValue( id );

    DALI_CHECK_FAIL( returnValue.compare( newValue ) != 0, "Window::SetAuxiliaryHintValue and Window::GetAuxiliaryHintValue is failed" );

    DALI_CHECK_FAIL( window.GetAuxiliaryHintId( hint ) != id, "Window::GetAuxiliaryHintId is failed" );

    DALI_CHECK_FAIL( !window.RemoveAuxiliaryHint( id ), "Window::RemoveAuxiliaryHint is failed" );
  }

  DaliLog::PrintPass();
}

void WindowSetGetTypeP( Application& application )
{
  Window window = application.GetWindow();

  Window::Type type = window.GetType();
  DALI_CHECK_FAIL( type != Window::NORMAL, "Window default type error" );

  window.SetType( Window::UTILITY );

  type = window.GetType();
  DALI_CHECK_FAIL( type != Window::UTILITY, "Window::SetType and Window::GetType is failed" );

  window.SetType( Window::DIALOG );

  type = window.GetType();
  DALI_CHECK_FAIL( type != Window::DIALOG, "Window::SetType and Window::GetType is failed" );

  DaliLog::PrintPass();
}

void WindowSetGetNotificationLevelP( Application& application )
{
  Window window = application.GetWindow();

  DALI_CHECK_FAIL( window.SetNotificationLevel( Window::NotificationLevel::MEDIUM ), "Normal window should be failed" );

  window.SetType( Window::NOTIFICATION );

  DALI_CHECK_FAIL( window.GetNotificationLevel() != Window::NotificationLevel::NONE, "Default notification level should be NONE" );

  DALI_CHECK_FAIL( !window.SetNotificationLevel( Window::NotificationLevel::HIGH ), "Window::SetNotificationLevel is failed" );

  DALI_CHECK_FAIL( window.GetNotificationLevel() != Window::NotificationLevel::HIGH, "Window::GetNotificationLevel is failed" );

  DaliLog::PrintPass();
}

void WindowSetOpaqueStateIsOpaqueStateP( Application& application )
{
  Window window = application.GetWindow();

  window.SetOpaqueState( true );

  DALI_CHECK_FAIL( window.IsOpaqueState() != true, "Window::SetOpaqueState( true ) is failed" );

  window.SetOpaqueState( false );

  DALI_CHECK_FAIL( window.IsOpaqueState() != false, "Window::SetOpaqueState( false ) is failed" );

  DaliLog::PrintPass();
}

void WindowSetGetScreenOffModeP( Application& application )
{
  Window window = application.GetWindow();

  window.SetScreenOffMode( Window::ScreenOffMode::TIMEOUT );

  DALI_CHECK_FAIL( window.GetScreenOffMode() != Window::ScreenOffMode::TIMEOUT, "Window::SetScreenOffMode( TIMEOUT ) is failed" );

  window.SetScreenOffMode( Window::ScreenOffMode::NEVER );

  DALI_CHECK_FAIL( window.GetScreenOffMode() != Window::ScreenOffMode::NEVER, "Window::SetScreenOffMode( NEVER ) is failed" );

  DaliLog::PrintPass();
}

void WindowSetGetBrightnessP( Application& application )
{
  Window window = application.GetWindow();

  DALI_CHECK_FAIL( window.SetBrightness( 200 ) != false, "The brightness should be 0 to 100." );

  DALI_CHECK_FAIL( window.SetBrightness( 50 ) != true, "Window::SetBrightness is failed" );

  DALI_CHECK_FAIL( window.GetBrightness() != 50, "Window::GetBrightness is failed" );

  DaliLog::PrintPass();
}

void WindowSetGetSizeResizedSignalP( Application& application )
{
  gBoolSignalReceived = false;

  Window window = application.GetWindow();

  window.ResizedSignal().Connect( &WindowResizedCallback );

  window.SetSize( Window::WindowSize( 200, 200 ) );
}

void WindowSetGetSizeResizedSignalP2( Application& application )
{
  gBoolSignalReceived2 = false;
  gBoolWindowVerify = false;

  Window window = application.GetWindow();

  window.ResizeSignal().Connect( &WindowResizedCallback2 );

  window.SetSize( Window::WindowSize( 200, 200 ) );
}

void VTWindowSetGetSizeResizedSignal001( Application& application )
{
  Window window = application.GetWindow();

  DALI_CHECK_FAIL( gBoolSignalReceived == false, "Window resize is failed" );

  Window::WindowSize size = window.GetSize();

  DALI_CHECK_FAIL( size != Window::WindowSize( 200, 200 ), "Window::GetSize is failed" );

  DaliLog::PrintPass();
}

void VTWindowSetGetSizeResizedSignal002( Application& application )
{
  Window window = application.GetWindow();

  DALI_CHECK_FAIL( gBoolSignalReceived2 == false, "Window resize is failed" );

  Window::WindowSize size = window.GetSize();

  DALI_CHECK_FAIL( size != Window::WindowSize( 200, 200 ), "Window::GetSize is failed" );

  DALI_CHECK_FAIL( gBoolWindowVerify == false , " Failure to call the appropriate window" );

  DaliLog::PrintPass();
}

void WindowSetGetPositionP( Application& application )
{
  Window window = application.GetWindow();

  window.SetPosition( Window::WindowPosition( 100, 100 ) );

  DALI_CHECK_FAIL( window.GetPosition() != Window::WindowPosition( 100, 100 ), "Window::SetPosition and Window::GetPosition are failed" );

  DaliLog::PrintPass();
}

void WindowAddRemoveActorP( Application& application )
{
  Window window = application.GetWindow();

  Actor actor = Actor::New();
  DALI_CHECK_FAIL( !actor,  "Actor::New() is Failed" );

  bool bIsOnStage = actor.OnStage();
  DALI_CHECK_FAIL( bIsOnStage,  " OnStage is Failed to get default value" );

  window.Add( actor );
  bIsOnStage = actor.OnStage();
  DALI_CHECK_FAIL( !bIsOnStage,  "OnStage is Failed to get the expected value" );

  window.Remove( actor );
  bIsOnStage = actor.OnStage();
  DALI_CHECK_FAIL( bIsOnStage,  "OnStage is Failed to get the expected value" );

  DaliLog::PrintPass();
}

void WindowSetGetBackgroundColorP( Application& application )
{
  Window window = application.GetWindow();

  window.SetBackgroundColor( Color::RED );
  DALI_CHECK_FAIL( Color::RED != window.GetBackgroundColor(), "Window::SetBackgroundColor and Window::GetBackgroundColor are failed" );

  DaliLog::PrintPass();
}

void WindowGetRootLayerP( Application& application )
{
  Window window = application.GetWindow();

  Layer rootLayer = window.GetLayer( 0u );
  DALI_CHECK_FAIL( window.GetRootLayer() != rootLayer,  "GetRootLayer is failed to get expected value" );

  Layer layer = Layer::New();
  window.Add( layer );
  layer.LowerToBottom();
  DALI_CHECK_FAIL( window.GetRootLayer() != rootLayer,  "GetRootLayer is failed to get expected value" );

  DaliLog::PrintPass();
}

void WindowGetLayerCountP( Application& application )
{
  Window window = application.GetWindow();

  // Initially we have a default layer
  DALI_CHECK_FAIL( window.GetLayer( 0u ) != window.GetRootLayer(),  "GetLayer is failed to get expected value" );
  DALI_CHECK_FAIL( window.GetLayerCount() != 1u, "GetLayerCount is failed to get expected value" );

  // Add a new layer to the window
  Layer newLayer = Layer::New();
  window.Add( newLayer );
  DALI_CHECK_FAIL( window.GetLayerCount() != 2u, "GetLayerCount is failed to get expected value" );

  // Retrieves the new layer from the window
  DALI_CHECK_FAIL( window.GetLayer( 1u ) != newLayer, "GetLayer is failed to get expected value" );

  DaliLog::PrintPass();
}

void WindowGetLayerP( Application& application )
{
  Window window = application.GetWindow();

  // Initially we have a default layer
  DALI_CHECK_FAIL( window.GetLayerCount() != 1u, "GetLayerCount is failed to get expected value" );

  // Add a new layer to the window
  Layer layer = Layer::New();
  window.Add( layer );
  DALI_CHECK_FAIL( window.GetLayerCount() != 2u, "GetLayerCount is failed to get expected value" );

  // Remove the new layer from the window
  window.Remove( layer );
  DALI_CHECK_FAIL( window.GetLayerCount() != 1u, "GetLayerCount is failed to get expected value" );

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliWindowNewP
 * @since_tizen     2.4
 * @description     checks for Window::WindowNewP() functionality
 */

int UtcDaliWindowNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_NEW_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowNewP2
 * @since_tizen     2.4
 * @description     checks for Window::WindowNewP2() functionality
 */

int UtcDaliWindowNewP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_NEW_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowIndicatorVisibilityChangeP
 * @since_tizen     2.4
 * @description     checks for Window::IndicatorVisibilityChangeP() functionality
 */

int UtcDaliWindowIndicatorVisibilityChangeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_INDICATOR_VISIBILITY_CHANGE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowConstructorP
 * @since_tizen     2.4
 * @description     checks for Window::ConstructorP() functionality
 */

int UtcDaliWindowConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowCopyConstructorP
 * @since_tizen     2.4
 * @description     checks for Window::CopyConstructorP() functionality
 */

int UtcDaliWindowCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowSetClassP
 * @since_tizen     2.4
 * @description     checks for Window::SetClassP() functionality
 */

int UtcDaliWindowSetClassP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_CLASS_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowConstructorNewAssignmentOperatorP
 * @since_tizen     2.4
 * @description     checks for Window::ConstructorNewAssignmentOperatorP() functionality
 */

int UtcDaliWindowConstructorNewAssignmentOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_CONSTRUCTOR_NEW_ASSIGNMENT_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowSetPreferredOrientationP
 * @since_tizen     2.4
 * @description     checks for Window::SetPreferredOrientationP() functionality
 */

int UtcDaliWindowSetPreferredOrientationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_PREFERRED_ORIENTATION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowGetPreferredOrientationP
 * @since_tizen     2.4
 * @description     checks for Window::GetPreferredOrientationP() functionality
 */

int UtcDaliWindowGetPreferredOrientationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_GET_PREFERRED_ORIENTATION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowGetNativeHandleP
 * @since_tizen     2.4
 * @description     checks for Window::GetNativeHandleP() functionality
 */

int UtcDaliWindowGetNativeHandleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_GET_NATIVE_HANDLE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowAddAvailableOrientationN
 * @since_tizen     2.4
 * @description     checks for Window::AddAvailableOrientationN() functionality
 */

int UtcDaliWindowAddAvailableOrientationN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_ADD_AVAILABLE_ORIENTATION_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowRemoveAvailableOrientationN
 * @since_tizen     2.4
 * @description     checks for Window::RemoveAvailableOrientationN() functionality
 */

int UtcDaliWindowRemoveAvailableOrientationN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_REMOVE_AVAILABLE_ORIENTATION_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowLowerP
 * @since_tizen     2.4
 * @description     checks for Window::LowerP() functionality
 */

int UtcDaliWindowLowerP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_LOWER_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowRaiseP
 * @since_tizen     2.4
 * @description     checks for Window::RaiseP() functionality
 */

int UtcDaliWindowRaiseP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_RAISE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowActivateP
 * @since_tizen     2.4
 * @description     checks for Window::ActivateP() functionality
 */

int UtcDaliWindowActivateP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_ACTIVATE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowSetClassSetIndicatorBgOpacityP
 * @since_tizen     2.4
 * @description     checks for Window::SetClassSetIndicatorBgOpacityP() functionality
 */

int UtcDaliWindowSetClassSetIndicatorBgOpacityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_CLASS_SET_INDICATOR_BGOPACITY_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowShowIndicatorP
 * @since_tizen     2.4
 * @description     checks for Window::ShowIndicatorP() functionality
 */

int UtcDaliWindowShowIndicatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SHOW_INDICATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowRotateIndicatorP
 * @since_tizen     2.4
 * @description     checks for Window::RotateIndicatorP() functionality
 */

int UtcDaliWindowRotateIndicatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_ROTATE_INDICATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowIndicatorVisibilityChangedSignalP
 * @since_tizen     2.4
 * @description     checks for Window::IndicatorVisibilityChangedSignalP() functionality
 */

int UtcDaliWindowIndicatorVisibilityChangedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_INDICATOR_VISIBILITY_CHANGE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowSetAcceptFocusIsFocusAcceptableP
 * @since_tizen     4.0
 * @description     checks for Window::SetAcceptFocus() and Window::IsFocusAcceptable() functionality
 */

int UtcDaliWindowSetAcceptFocusIsFocusAcceptableP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_ACCEPT_FOCUS_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowShowHideIsVisibleP
 * @since_tizen     4.0
 * @description     checks for Window::Show(), Window::Hide() and Window::IsVisible() functionality
 */

int UtcDaliWindowShowHideIsVisibleP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SHOW_HIDE_IS_VISIBLE_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowAuxiliaryHintTestP
 * @since_tizen     4.0
 * @description     checks for Window::GetSupportedAuxiliaryHintCount(), Window::GetSupportedAuxiliaryHint(), Window::AddAuxiliaryHint(),
 *                  Window::RemoveAuxiliaryHint(), Window::SetAuxiliaryHintValue(), Window::GetAuxiliaryHintValue() and Window::GetAuxiliaryHintId() functionality
 */

int UtcDaliWindowAuxiliaryHintTestP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_AUXILIARY_HINT_TEST_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowSetGetTypeP
 * @since_tizen     4.0
 * @description     checks for Window::SetType() and Window::GetType() functionality
 */

int UtcDaliWindowSetGetTypeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_GET_TYPE_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowSetGetNotificationLevelP
 * @since_tizen     4.0
 * @description     checks for Window::SetNotificationLevel() and Window::GetNotificationLevel() functionality
 */

int UtcDaliWindowSetGetNotificationLevelP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_GET_NOTIFICATION_LEVEL_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowSetOpaqueStateIsOpaqueStateP
 * @since_tizen     4.0
 * @description     checks for Window::SetOpaqueState() and Window::IsOpaqueState() functionality
 */

int UtcDaliWindowSetOpaqueStateIsOpaqueStateP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_OPAQUE_STATE_IS_OPAQUE_STATE_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowSetGetScreenOffModeP
 * @since_tizen     4.0
 * @description     checks for Window::SetScreenOffMode() and Window::GetScreenOffMode() functionality
 */

int UtcDaliWindowSetGetScreenOffModeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_GET_SCREEN_OFF_MODE_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowSetGetBrightnessP
 * @since_tizen     4.0
 * @description     checks for Window::SetBrightness() and Window::GetBrightness() functionality
 */

int UtcDaliWindowSetGetBrightnessP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_GET_BRIGHTNESS_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowSetGetSizeResizedSignalP
 * @since_tizen     4.0
 * @description     checks for Window::SetSize(), Window::GetSize() and Window::ResizedSignal() functionality
 */

int UtcDaliWindowSetGetSizeResizedSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_GET_SIZE_RESIZED_SIGNAL_P );
  application.MainLoop();
  return test_return_value;
}

/**
* @testcase       UtcDaliWindowSetGetSizeResizedSignalP2
* @since_tizen    5.5
* @description      checks for Window::SetSize(), Window::GetSize() and Window::ResizeSignal() functionality
*/
int UtcDaliWindowSetGetSizeResizedSignalP2(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_GET_SIZE_RESIZED_SIGNAL_P2 );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWindowSetGetPositionP
 * @since_tizen     4.0
 * @description     checks for Window::SetPosition() and Window::GetPosition() functionality
 */

int UtcDaliWindowSetGetPositionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_GET_POSITION_P );
  application.MainLoop();
  return test_return_value;
}

/**
* @testcase       UtcWindowAddRemoveActorP
* @since_tizen    5.5
* @description    checks for Window::Add() and Window::Remove() functionality
*/
int UtcWindowAddRemoveActorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_ADD_REMOVE_ACTOR_P );
  application.MainLoop();
  return test_return_value;
}

/**
* @testcase       UtcWindowSetGetBackgroundColorP
* @since_tizen    5.5
* @description    checks for Window::SetBackgroundColor() and Window::GetBackgroundColor() functionality
*/
int UtcWindowSetGetBackgroundColorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_SET_GET_BACKGROUND_COLOR_P );
  application.MainLoop();
  return test_return_value;
}

/**
* @testcase       UtcWindowGetRootLayerP
* @since_tizen    5.5
* @description    checks for Window::GetRootLayer functionality
*/
int UtcWindowGetRootLayerP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_GET_ROOT_LAYER_P );
  application.MainLoop();
  return test_return_value;
}

/**
* @testcase       UtcWindowGetLayerCountP
* @since_tizen    5.5
* @description    checks for Window::GetLayerCount functionality
*/
int UtcWindowGetLayerCountP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_GET_LAYER_COUNT_P );
  application.MainLoop();
  return test_return_value;
}

/**
* @testcase       UtcWindowGetLayerP
* @since_tizen    5.5
* @description      checks for Window::GetLayer functionality
*/
int UtcWindowGetLayerP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Window_TestApp testApp( application, WINDOW_GET_LAYER_P );
  application.MainLoop();
  return test_return_value;
}
