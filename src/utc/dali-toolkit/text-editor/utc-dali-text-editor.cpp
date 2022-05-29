#include "utc-dali-text-editor.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_TextEditor_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_TextEditor_startup(void)
{
  test_return_value =0;
}

/**
 * @function            utc_Dali_TextEditor_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_TextEditor_cleanup(void)
{
}

bool FloatCompare(float value1, float value2, float epsilon)
{
	return fabsf(value1 - value2)<epsilon;
}

class ScrollStateChangeCallback : public Dali::ConnectionTracker
{
public:
  ScrollStateChangeCallback()
  : mStartedCalled( false ),
    mFinishedCalled( false )
  {
  }

  void Callback( TextEditor editor, TextEditor::Scroll::Type type )
  {
    if( type == TextEditor::Scroll::STARTED )
    {
      mStartedCalled = true;
    }
    else if( type == TextEditor::Scroll::FINISHED )
    {
      mFinishedCalled = true;
    }
  }

  bool mStartedCalled;
  bool mFinishedCalled;
};

void TextEditorNewP();
void TextEditorConstructorP();
void TextEditorCopyConstructorP();
void TextEditorOperatorAssignmentP();
void TextEditorDownCastP();
void TextEditorDownCastN();
void TextEditorHorizontalAlignmentP();
void TextEditorScrollThresholdP();
void TextEditorScrollSpeedP();
void TextEditorPrimaryCursorColorP();
void TextEditorSecondaryCursorColorP();
void TextEditorBlinkInterval();
void TextEditorBlinkDuration();
void TextEditorCursorWidth();
void TextEditorPropertyLineSpacingP();
void TextEditorPropertyUnderlineP();
void TextEditorPropertyShadowP();
void TextEditorPropertyEmbossP();
void TextEditorPropertyOutlineP();
void TextEditorScrollStateChangedSignal( ScrollStateChangeCallback& callback );
void VTTextEditorScrollStateChangedSignal( ScrollStateChangeCallback& callback );


namespace
{
  enum TEST_CASES_LIST_TEXT_EDITOR
  {
    TEXT_EDITOR_NEW_P,
    TEXT_EDITOR_CONSTRUCTOR_P,
    TEXT_EDITOR_COPY_CONSTRUCTOR_P,
    TEXT_EDITOR_OPERATOR_ASSIGNMENT_P,
    TEXT_EDITOR_DOWNCAST_P,
    TEXT_EDITOR_DOWNCAST_N,
    TEXT_EDITOR_HORIZONTAL_ALIGNMENT,
    TEXT_EDITOR_SCROLL_THRESHOLD,
    TEXT_EDITOR_SCROLL_SPEED,
    TEXT_EDITOR_PRIMARY_CURSOR_COLOR,
    TEXT_EDITOR_SECONDARY_CURSOR_COLOR,
    TEXT_EDITOR_CURSOR_BLINK_INTERVAL,
    TEXT_EDITOR_CURSOR_BLINK_DURATION,
    TEXT_EDITOR_CURSOR_WIDTH,
    TEXT_EDITOR_PROPERTY_LINE_SPACING_P,
    TEXT_EDITOR_PROPERTY_UNDERLINE_P,
    TEXT_EDITOR_PROPERTY_SHADOW_P,
    TEXT_EDITOR_PROPERTY_EMBOSS_P,
    TEXT_EDITOR_PROPERTY_OUTLINE_P,
    TEXT_EDITOR_SCROLL_STATE_CHANGED_SIGNAL
  };

  struct TextEditor_TestApp : public ConnectionTracker
  {
    TextEditor_TestApp( Application& app, int test_case )
      : mApplication( app ),
        mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &TextEditor_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &TextEditor_TestApp::Tick );
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
        case TEXT_EDITOR_NEW_P:
          TextEditorNewP();
          break;
        case TEXT_EDITOR_CONSTRUCTOR_P:
          TextEditorConstructorP();
          break;
        case TEXT_EDITOR_COPY_CONSTRUCTOR_P:
          TextEditorCopyConstructorP();
          break;
        case TEXT_EDITOR_OPERATOR_ASSIGNMENT_P:
          TextEditorOperatorAssignmentP();
          break;
        case TEXT_EDITOR_DOWNCAST_P:
          TextEditorDownCastP();
          break;
        case TEXT_EDITOR_DOWNCAST_N:
          TextEditorDownCastN();
          break;
        case TEXT_EDITOR_HORIZONTAL_ALIGNMENT:
          TextEditorHorizontalAlignmentP();
          break;
        case TEXT_EDITOR_SCROLL_THRESHOLD:
          TextEditorScrollThresholdP();
          break;
        case TEXT_EDITOR_SCROLL_SPEED:
          TextEditorScrollSpeedP();
          break;
        case TEXT_EDITOR_PRIMARY_CURSOR_COLOR:
          TextEditorPrimaryCursorColorP();
          break;
        case TEXT_EDITOR_SECONDARY_CURSOR_COLOR:
          TextEditorSecondaryCursorColorP();
          break;
        case TEXT_EDITOR_CURSOR_BLINK_INTERVAL:
          TextEditorBlinkInterval();
          break;
        case TEXT_EDITOR_CURSOR_BLINK_DURATION:
          TextEditorBlinkDuration();
          break;
        case TEXT_EDITOR_CURSOR_WIDTH:
          TextEditorCursorWidth();
          break;
        case TEXT_EDITOR_PROPERTY_LINE_SPACING_P:
          TextEditorPropertyLineSpacingP();
          break;
        case TEXT_EDITOR_PROPERTY_UNDERLINE_P:
          TextEditorPropertyUnderlineP();
          break;
        case TEXT_EDITOR_PROPERTY_SHADOW_P:
          TextEditorPropertyShadowP();
          break;
        case TEXT_EDITOR_PROPERTY_EMBOSS_P:
          TextEditorPropertyEmbossP();
          break;
        case TEXT_EDITOR_PROPERTY_OUTLINE_P:
          TextEditorPropertyOutlineP();
          break;
        case TEXT_EDITOR_SCROLL_STATE_CHANGED_SIGNAL:
          TextEditorScrollStateChangedSignal( mCallback );
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case TEXT_EDITOR_SCROLL_STATE_CHANGED_SIGNAL:
          VTTextEditorScrollStateChangedSignal( mCallback );
          break;
      }
    }

    // Data
    Application& mApplication;
    int mTestCase;
    ScrollStateChangeCallback mCallback;
    Timer mTimer;
  };

} // unnamed namespace


void TextEditorNewP(void)
{
  TextEditor textEditor1 = TextEditor::New( );
  DALI_CHECK_FAIL(!textEditor1, "TextEditor::New() is failed.");
  DaliLog::PrintPass();
}

void TextEditorConstructorP(void)
{
  TextEditor textEditor;
  DALI_CHECK_FAIL(textEditor, "TextEditor::TextEditor() is failed.");
  DaliLog::PrintPass();
}

void TextEditorDownCastP()
{
  TextEditor textEditor1 = TextEditor::New();
  BaseHandle object( textEditor1 );

  TextEditor textEditor2 = TextEditor::DownCast( object );
  DALI_CHECK_FAIL(!textEditor2, "TextEditor handle is empty.");

  TextEditor textEditor3 = DownCast< TextEditor >( object );
  DALI_CHECK_FAIL(!textEditor3, "TextEditor handle is empty after downcast.");
  DaliLog::PrintPass();
}

void TextEditorDownCastN(void)
{
  BaseHandle uninitializedObject;
  TextEditor textEditor1 = TextEditor::DownCast( uninitializedObject );
  DALI_CHECK_FAIL(textEditor1, "TextEditor handle is not empty.");

  TextEditor textEditor2 = DownCast< TextEditor >( uninitializedObject );
  DALI_CHECK_FAIL(textEditor2, "TextEditor handle is not empty after downcast.");
  DaliLog::PrintPass();
}

void TextEditorOperatorAssignmentP()
{
  TextEditor textEditor = TextEditor::New();
  textEditor.SetProperty( TextEditor::Property::TEXT_COLOR, Color::RED );

  TextEditor copy = textEditor;
  DALI_CHECK_INSTANCE(copy, "TextEditor handle is empty after assignment.");
  DALI_CHECK_FAIL( copy.GetProperty<Vector4>( TextEditor::Property::TEXT_COLOR ) != textEditor.GetProperty<Vector4>( TextEditor::Property::TEXT_COLOR ), "TextEditor::operator= is failed.");
  DaliLog::PrintPass();
}

void TextEditorCopyConstructorP()
{
  TextEditor textEditor = TextEditor::New();
  textEditor.SetProperty( TextEditor::Property::TEXT_COLOR, Color::RED );

  TextEditor copy(textEditor);
  DALI_CHECK_INSTANCE(copy, "TextEditor handle is empty after copy.");
  DALI_CHECK_FAIL( copy.GetProperty<Vector4>( TextEditor::Property::TEXT_COLOR ) != textEditor.GetProperty<Vector4>( TextEditor::Property::TEXT_COLOR ), "TextEditor::TextEditor(const TextEditor&) is failed.");
  DaliLog::PrintPass();
}

void TextEditorHorizontalAlignmentP()
{
  TextEditor textEditor = TextEditor::New();

  textEditor.SetProperty( TextEditor::Property::HORIZONTAL_ALIGNMENT, "END" );
  DALI_CHECK_FAIL( textEditor.GetProperty<std::string>( TextEditor::Property::HORIZONTAL_ALIGNMENT ) != "END", "TextEditorHorizontalAlignmentP is failed." );
  DaliLog::PrintPass();
}

void TextEditorScrollThresholdP()
{
  TextEditor textEditor = TextEditor::New();

  textEditor.SetProperty( TextEditor::Property::SCROLL_THRESHOLD, 1.f );
  DALI_CHECK_FAIL( !FloatCompare(textEditor.GetProperty<float>( TextEditor::Property::SCROLL_THRESHOLD ), 1.f, Math::MACHINE_EPSILON_1000), "TextEditorScrollThresholdP is failed." );
  DaliLog::PrintPass();
}

void TextEditorScrollSpeedP()
{
  TextEditor textEditor = TextEditor::New();

  textEditor.SetProperty( TextEditor::Property::SCROLL_SPEED, 100.f );
  DALI_CHECK_FAIL( !FloatCompare(textEditor.GetProperty<float>( TextEditor::Property::SCROLL_SPEED ), 100.f, Math::MACHINE_EPSILON_1000), "TextEditorScrollSpeedP is failed." );
  DaliLog::PrintPass();
}

void TextEditorPrimaryCursorColorP()
{
  TextEditor textEditor = TextEditor::New();

  textEditor.SetProperty( TextEditor::Property::PRIMARY_CURSOR_COLOR, Color::RED );
  DALI_CHECK_FAIL( textEditor.GetProperty<Vector4>( TextEditor::Property::PRIMARY_CURSOR_COLOR ) != Color::RED, "TextEditorScrollSpeedP is failed." );
  DaliLog::PrintPass();
}

void TextEditorSecondaryCursorColorP()
{
  TextEditor textEditor = TextEditor::New();

  textEditor.SetProperty( TextEditor::Property::SECONDARY_CURSOR_COLOR, Color::BLUE );
  DALI_CHECK_FAIL( textEditor.GetProperty<Vector4>( TextEditor::Property::SECONDARY_CURSOR_COLOR ) != Color::BLUE, "TextEditorSecondaryCursorColorP is failed." );
  DaliLog::PrintPass();
}

void TextEditorBlinkInterval()
{
  TextEditor textEditor = TextEditor::New();

  textEditor.SetProperty( TextEditor::Property::CURSOR_BLINK_INTERVAL, 1.f );
  DALI_CHECK_FAIL( !FloatCompare(textEditor.GetProperty<float>( TextEditor::Property::CURSOR_BLINK_INTERVAL ), 1.f, Math::MACHINE_EPSILON_1000), "TextEditorBlinkInterval is failed." );
  DaliLog::PrintPass();
}

void TextEditorBlinkDuration()
{
  TextEditor textEditor = TextEditor::New();

  textEditor.SetProperty( TextEditor::Property::CURSOR_BLINK_DURATION, 10.f );
  DALI_CHECK_FAIL( !FloatCompare(textEditor.GetProperty<float>( TextEditor::Property::CURSOR_BLINK_DURATION ), 10.f, Math::MACHINE_EPSILON_1000), "TextEditorBlinkDuration is failed." );
  DaliLog::PrintPass();
}

void TextEditorCursorWidth()
{
  TextEditor textEditor = TextEditor::New();

  textEditor.SetProperty( TextEditor::Property::CURSOR_WIDTH, 1 );
  DALI_CHECK_FAIL( textEditor.GetProperty<int>( TextEditor::Property::CURSOR_WIDTH) != 1, "TextEditorCursorWidth is failed." );
  DaliLog::PrintPass();
}

void TextEditorPropertyLineSpacingP()
{
  TextEditor textEditor = TextEditor::New();

  DALI_CHECK_FAIL( ((textEditor.GetProperty( TextEditor::Property::LINE_SPACING ).Get<float>()) - 0.0f ) > Math::MACHINE_EPSILON_1000, "TextEditor fails to get the default value of LINE_SPACING property." );

  textEditor.SetProperty( TextEditor::Property::LINE_SPACING, 10.f );
  DALI_CHECK_FAIL( ((textEditor.GetProperty( TextEditor::Property::LINE_SPACING ).Get<float>()) - 10.0f ) > Math::MACHINE_EPSILON_1000, "TextEditor fails to get the current value of LINE_SPACING property." );

  DaliLog::PrintPass();
}

void TextEditorPropertyUnderlineP()
{
  TextEditor textEditor = TextEditor::New();

  std::string propertyValue( "{\"enable\":\"true\",\"color\":\"red\",\"height\":\"1\"}" );
  textEditor.SetProperty( TextEditor::Property::UNDERLINE, propertyValue );
  DALI_CHECK_FAIL( textEditor.GetProperty( TextEditor::Property::UNDERLINE ).Get<std::string>() != propertyValue, "TextEditor fails to get the value of UNDERLINE property."  );

  DaliLog::PrintPass();
}

void TextEditorPropertyShadowP()
{
  TextEditor textEditor = TextEditor::New();

  std::string propertyValue( "{\"color\":\"green\",\"offset\":\"2 2\",\"blurRadius\":\"0\"}" );
  textEditor.SetProperty( TextEditor::Property::SHADOW, propertyValue );
  DALI_CHECK_FAIL( textEditor.GetProperty( TextEditor::Property::SHADOW ).Get<std::string>() != propertyValue, "TextEditor fails to get the value of SHADOW property."  );

  DaliLog::PrintPass();
}

void TextEditorPropertyEmbossP()
{
  TextEditor textEditor = TextEditor::New();

  std::string propertyValue( "Emboss properties" );
  textEditor.SetProperty( TextEditor::Property::EMBOSS, propertyValue );
  DALI_CHECK_FAIL( textEditor.GetProperty( TextEditor::Property::EMBOSS ).Get<std::string>() != propertyValue, "TextEditor fails to get the value of EMBOSS property."  );

  DaliLog::PrintPass();
}

void TextEditorPropertyOutlineP()
{
  TextEditor textEditor = TextEditor::New();

  std::string propertyValue( "Outline properties" );
  textEditor.SetProperty( TextEditor::Property::OUTLINE, propertyValue );
  DALI_CHECK_FAIL( textEditor.GetProperty( TextEditor::Property::OUTLINE ).Get<std::string>() != propertyValue, "TextEditor fails to get the value of OUTLINE property."  );

  DaliLog::PrintPass();
}

void TextEditorScrollStateChangedSignal( ScrollStateChangeCallback& callback )
{
  TextEditor editor = TextEditor::New();
  Stage::GetCurrent().Add( editor );

  editor.SetProperty( TextEditor::Property::PIXEL_SIZE, 10.f );
  editor.SetSize( 50.f, 50.f );
  editor.SetParentOrigin( ParentOrigin::TOP_LEFT );
  editor.SetAnchorPoint( AnchorPoint::TOP_LEFT );
  editor.SetProperty( TextEditor::Property::ENABLE_SCROLL_BAR, true );
  editor.SetProperty( TextEditor::Property::SCROLL_BAR_SHOW_DURATION, 0.05f );
  editor.SetProperty( TextEditor::Property::SCROLL_BAR_FADE_DURATION, 0.05f );
  editor.SetKeyboardFocusable(true);

  editor.ScrollStateChangedSignal().Connect( &callback, &ScrollStateChangeCallback::Callback );

  KeyboardFocusManager::Get().SetCurrentFocusActor( editor );
  editor.SetProperty( TextEditor::Property::TEXT, "Long enough message for TextEditor!");

}

void VTTextEditorScrollStateChangedSignal( ScrollStateChangeCallback& callback)
{
  DALI_CHECK_FAIL( !callback.mStartedCalled,  "ScrollStateChanged start is failed to connect the callback." );
  DALI_CHECK_FAIL( !callback.mFinishedCalled, "ScrollStateChanged finish failed to connect the callback." );

  DaliLog::PrintPass();
}

int UtcDaliTextEditorTest(int testMode)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextEditor_TestApp testApp( application, testMode);
  application.MainLoop();
  return test_return_value;
}


int UtcDaliTextEditorNewP(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_NEW_P);
}

int UtcDaliTextEditorConstructorP(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_CONSTRUCTOR_P);
}

int UtcDaliTextEditorCopyConstructorP(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_COPY_CONSTRUCTOR_P);
}

int UtcDaliTextEditorOperatorAssignmentP(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_OPERATOR_ASSIGNMENT_P);
}

int UtcDaliTextEditorDowncastP(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_DOWNCAST_P);
}

int UtcDaliTextEditorDowncastN(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_DOWNCAST_N);
}

int UtcDaliTextEditorHorizontalAlignment(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_HORIZONTAL_ALIGNMENT);
}

int UtcDaliTextEditorScrollThreshold(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_SCROLL_THRESHOLD);
}

int UtcDaliTextEditorScrollSpeed(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_SCROLL_SPEED);
}

int UtcDaliTextEditorPrimaryCursorColor(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_PRIMARY_CURSOR_COLOR);
}

int UtcDaliTextEditorSecondaryCursorColor(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_SECONDARY_CURSOR_COLOR);
}

int UtcDaliTextEditorCursorBlinkInterval(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_CURSOR_BLINK_INTERVAL);
}

int UtcDaliTextEditorCursorBlinkDuration(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_CURSOR_BLINK_DURATION);
}

int UtcDaliTextEditorCursorWidth(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_CURSOR_WIDTH);
}

int UtcDaliTextEditorPropertyLineSpacingP(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_PROPERTY_LINE_SPACING_P);
}

int UtcDaliTextEditorPropertyUnderlineP(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_PROPERTY_UNDERLINE_P);
}

int UtcDaliTextEditorPropertyShadowP(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_PROPERTY_SHADOW_P);
}

int UtcDaliTextEditorPropertyEmbossP(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_PROPERTY_EMBOSS_P);
}

int UtcDaliTextEditorPropertyOutlineP(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_PROPERTY_OUTLINE_P);
}
int UtcDaliTextEditorScrollStateChangedSignal(void)
{
  return UtcDaliTextEditorTest(TEXT_EDITOR_SCROLL_STATE_CHANGED_SIGNAL);
}