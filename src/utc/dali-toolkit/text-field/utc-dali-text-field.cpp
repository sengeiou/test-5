#include "utc-dali-text-field-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_TextField_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_TextField_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_TextField_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_TextField_cleanup(void)
{
}

bool gTextChangedCallback = false;

void TextFieldTextChangedCallback( TextField textField )
{
  LOG_I("\n TextFieldTextChangedCallback is called. \n");
  gTextChangedCallback = ( textField.GetProperty< string >( TextField::Property::TEXT ) == TEXT_FIELD_STRING );
}

void TextFieldNewP();
void TextFieldConstructorP();
void TextFieldCopyConstructorP();
void TextFieldOperatorAssignmentP();
void TextFieldDownCastP();
void TextFieldDownCastN();
void TextFieldTextChangedSignalP();
void TextFieldPropertyInputColorP();
void TextFieldPropertyEnableMarkupP();
void TextFieldPropertyUnderlineP();
void TextFieldPropertyInputUnderlineP();
void TextFieldPropertyShadowP();
void TextFieldPropertyInputShadowP();
void TextFieldPropertyEmbossP();
void TextFieldPropertyInputEmbossP();
void TextFieldPropertyOutlineP();
void TextFieldPropertyInputOutlineP();
void TextFieldPropertyInputMethodSettingsP();

namespace
{

  const char* const PROPERTY_NAME_INPUT_COLOR = "inputColor";
  const char* const PROPERTY_NAME_ENABLE_MARKUP = "enableMarkup";

  enum TEST_CASES_LIST_TEXT_FIELD
  {
    TEXT_FIELD_NEW_P,
    TEXT_FIELD_CONSTRUCTOR_P,
    TEXT_FIELD_COPY_CONSTRUCTOR_P,
    TEXT_FIELD_OPERATOR_ASSIGNMENT_P,
    TEXT_FIELD_DOWNCAST_P,
    TEXT_FIELD_DOWNCAST_N,
    TEXT_FIELD_TEXT_CHANGED_SIGNAL_P,
    TEXT_FIELD_PROPERTY_INPUT_COLOR_P,
    TEXT_FIELD_PROPERTY_ENABLE_MARKUP_P,
    TEXT_FIELD_PROPERTY_UNDERLINE_P,
    TEXT_FIELD_PROPERTY_INPUT_UNDERLINE_P,
    TEXT_FIELD_PROPERTY_SHADOW_P,
    TEXT_FIELD_PROPERTY_INPUT_SHADOW_P,
    TEXT_FIELD_PROPERTY_EMBOSS_P,
    TEXT_FIELD_PROPERTY_INPUT_EMBOSS_P,
    TEXT_FIELD_PROPERTY_OUTLINE_P,
    TEXT_FIELD_PROPERTY_INPUT_OUTLINE_P,
    TEXT_FIELD_PROPERTY_INPUT_METHOD_SETTINGS_P
  };

  struct TextField_TestApp : public ConnectionTracker
  {
    TextField_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &TextField_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &TextField_TestApp::Tick );
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
        case TEXT_FIELD_NEW_P:
          TextFieldNewP();
          break;
        case TEXT_FIELD_CONSTRUCTOR_P:
          TextFieldConstructorP();
          break;
        case TEXT_FIELD_DOWNCAST_P:
          TextFieldDownCastP();
          break;
        case TEXT_FIELD_DOWNCAST_N:
          TextFieldDownCastN();
          break;
        case TEXT_FIELD_OPERATOR_ASSIGNMENT_P:
          TextFieldOperatorAssignmentP();
          break;
        case TEXT_FIELD_COPY_CONSTRUCTOR_P:
          TextFieldCopyConstructorP();
          break;
        case TEXT_FIELD_TEXT_CHANGED_SIGNAL_P:
          TextFieldTextChangedSignalP();
          break;
        case TEXT_FIELD_PROPERTY_INPUT_COLOR_P:
          TextFieldPropertyInputColorP();
          break;
        case TEXT_FIELD_PROPERTY_ENABLE_MARKUP_P:
          TextFieldPropertyEnableMarkupP();
          break;
        case TEXT_FIELD_PROPERTY_UNDERLINE_P:
          TextFieldPropertyUnderlineP();
          break;
        case TEXT_FIELD_PROPERTY_INPUT_UNDERLINE_P:
          TextFieldPropertyInputUnderlineP();
          break;
        case TEXT_FIELD_PROPERTY_SHADOW_P:
          TextFieldPropertyShadowP();
          break;
        case TEXT_FIELD_PROPERTY_INPUT_SHADOW_P:
          TextFieldPropertyInputShadowP();
          break;
        case TEXT_FIELD_PROPERTY_EMBOSS_P:
          TextFieldPropertyEmbossP();
          break;
        case TEXT_FIELD_PROPERTY_INPUT_EMBOSS_P:
          TextFieldPropertyInputEmbossP();
          break;
        case TEXT_FIELD_PROPERTY_OUTLINE_P:
          TextFieldPropertyOutlineP();
          break;
        case TEXT_FIELD_PROPERTY_INPUT_OUTLINE_P:
          TextFieldPropertyInputOutlineP();
          break;
        case TEXT_FIELD_PROPERTY_INPUT_METHOD_SETTINGS_P:
          TextFieldPropertyInputMethodSettingsP();
          break;
      }
    }

    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} //unnamed namespace


void TextFieldNewP()
{
  TextField textField = TextField::New();
  DALI_CHECK_INSTANCE(textField, "TextField::New() is failed.");

  DaliLog::PrintPass();
}

void TextFieldConstructorP()
{
  TextField textField;
  DALI_CHECK_FAIL(textField, "TextField::TextField() is failed.");

  DaliLog::PrintPass();
}

void TextFieldCopyConstructorP()
{
  TextField textField = TextField::New();
  textField.SetProperty( TextField::Property::TEXT, "Test" );

  TextField copy( textField );
  DALI_CHECK_INSTANCE(copy, "TextField handle is empty after copy.");
  DALI_CHECK_FAIL( copy.GetProperty<std::string>( TextField::Property::TEXT ) != textField.GetProperty<std::string>( TextField::Property::TEXT ), "TextField::TextField(const TextField&) is failed." );

  DaliLog::PrintPass();
}

void TextFieldOperatorAssignmentP()
{
  TextField textFieldAssign;

  TextField textField = TextField::New();
  DALI_CHECK_INSTANCE( textField, "TextField::New() is failed." );

  textField.SetProperty( TextField::Property::TEXT, "Test" );

  textFieldAssign = textField;
  DALI_CHECK_INSTANCE( textFieldAssign, "TextField handle is empty after assignment." );

  DALI_CHECK_FAIL( textFieldAssign.GetProperty<std::string>( TextField::Property::TEXT ) != textField.GetProperty<std::string>( TextField::Property::TEXT ), "TextField::operator= is failed along with set properties." );

  DaliLog::PrintPass();
}

void TextFieldDownCastP()
{
  TextField textField1 = TextField::New();
  BaseHandle object( textField1 );

  TextField textField2 = TextField::DownCast( object );
  DALI_CHECK_INSTANCE( textField2, "TextField handle is empty." );

  TextField textField3 = DownCast< TextField >( object );
  DALI_CHECK_INSTANCE( textField3, "TextField handle is empty after downcast." );

  DaliLog::PrintPass();
}

void TextFieldDownCastN()
{
  BaseHandle uninitializedObject;
  TextField textField1 = TextField::DownCast( uninitializedObject );
  DALI_CHECK_INSTANCE( !textField1, "TextField handle is not empty." );

  TextField textField2 = DownCast< TextField >( uninitializedObject );
  DALI_CHECK_INSTANCE( !textField2, "TextField handle is not empty after downcast." );

  DaliLog::PrintPass();
}

void TextFieldTextChangedSignalP()
{
  TextField textField = TextField::New();
  DALI_CHECK_INSTANCE( textField, "TextField::New() is failed." );

  Stage::GetCurrent().Add( textField );

  gTextChangedCallback = false;
  textField.TextChangedSignal().Connect( &TextFieldTextChangedCallback );

  Property::Index indexText = TextField::Property::TEXT;
  textField.SetProperty( indexText, TEXT_FIELD_STRING );

  DALI_CHECK_FAIL( !gTextChangedCallback, "TextField::TextChangedSignal() is failed when text changes by setting text property." );

  Stage::GetCurrent().Remove( textField );
  DaliLog::PrintPass();
}

void TextFieldPropertyInputColorP()
{
  TextField field = TextField::New();
  DALI_CHECK_FAIL( field.GetPropertyIndex( PROPERTY_NAME_INPUT_COLOR ) != TextField::Property::INPUT_COLOR, "TextField property check failed." );

  DaliLog::PrintPass();
}

void TextFieldPropertyEnableMarkupP()
{
  TextField field = TextField::New();
  DALI_CHECK_FAIL( field.GetPropertyIndex( PROPERTY_NAME_ENABLE_MARKUP ) != TextField::Property::ENABLE_MARKUP, "TextField property check failed." );

  DaliLog::PrintPass();
}

void TextFieldPropertyUnderlineP()
{
  TextField field = TextField::New();

  std::string propertyValue( "{\"enable\":\"true\",\"color\":\"red\",\"height\":\"1\"}" );
  field.SetProperty( TextField::Property::UNDERLINE, propertyValue );
  DALI_CHECK_FAIL( field.GetProperty( TextField::Property::UNDERLINE ).Get<std::string>() != propertyValue, "TextField fails to get the value of UNDERLINE property."  );

   DaliLog::PrintPass();

}

void TextFieldPropertyInputUnderlineP()
{
  TextField field = TextField::New();

  std::string propertyValue( "{\"enable\":\"true\",\"color\":\"red\",\"height\":\"1\"}" );
  field.SetProperty( TextField::Property::INPUT_UNDERLINE, propertyValue );
  DALI_CHECK_FAIL( field.GetProperty( TextField::Property::INPUT_UNDERLINE ).Get<std::string>() != propertyValue, "TextField fails to get the value of INPUT_UNDERLINE property."  );

  DaliLog::PrintPass();
}

void TextFieldPropertyShadowP()
{
  TextField field = TextField::New();

  std::string propertyValue( "{\"color\":\"green\",\"offset\":\"2 2\",\"blurRadius\":\"0\"}" );
  field.SetProperty( TextField::Property::SHADOW, propertyValue );
  DALI_CHECK_FAIL( field.GetProperty( TextField::Property::SHADOW ).Get<std::string>() != propertyValue, "TextField fails to get the value of SHADOW property."  );

  DaliLog::PrintPass();
}

void TextFieldPropertyInputShadowP()
{
  TextField field = TextField::New();

  std::string propertyValue( "{\"color\":\"green\",\"offset\":\"2 2\"}" );
  field.SetProperty( TextField::Property::INPUT_SHADOW, propertyValue );
  DALI_CHECK_FAIL( field.GetProperty( TextField::Property::INPUT_SHADOW ).Get<std::string>() != propertyValue, "TextField fails to get the value of INPUT_SHADOW property."  );

  DaliLog::PrintPass();
}

void TextFieldPropertyEmbossP()
{
  TextField field = TextField::New();

  std::string propertyValue( "Emboss properties" );
  field.SetProperty( TextField::Property::EMBOSS, propertyValue );
  DALI_CHECK_FAIL( field.GetProperty( TextField::Property::EMBOSS ).Get<std::string>() != propertyValue, "TextField fails to get the value of EMBOSS EMBOSS."  );

  DaliLog::PrintPass();
}

void TextFieldPropertyInputEmbossP()
{
  TextField field = TextField::New();

  std::string propertyValue( "Emboss input properties" );
  field.SetProperty( TextField::Property::INPUT_EMBOSS, propertyValue );
  DALI_CHECK_FAIL( field.GetProperty( TextField::Property::INPUT_EMBOSS ).Get<std::string>() != propertyValue, "TextField fails to get the value of INPUT_EMBOSS property."  );

  DaliLog::PrintPass();
}

void TextFieldPropertyOutlineP()
{
  TextField field = TextField::New();

  std::string propertyValue( "Outline properties" );
  field.SetProperty( TextField::Property::OUTLINE, propertyValue );
  DALI_CHECK_FAIL( field.GetProperty( TextField::Property::OUTLINE ).Get<std::string>() != propertyValue, "TextField fails to get the value of OUTLINE property."  );

  DaliLog::PrintPass();
}

void TextFieldPropertyInputOutlineP()
{
  TextField field = TextField::New();

  std::string propertyValue( "Outline input properties" );
  field.SetProperty( TextField::Property::INPUT_OUTLINE, propertyValue );
  DALI_CHECK_FAIL( field.GetProperty( TextField::Property::INPUT_OUTLINE ).Get<std::string>() != propertyValue, "TextField fails to get the value of INPUT_OUTLINE property."  );

  DaliLog::PrintPass();
}

void TextFieldPropertyInputMethodSettingsP()
{
  TextField field = TextField::New();

  // Check the input method setting
  Property::Map propertyMap;
  InputMethod::PanelLayout::Type panelLayout = InputMethod::PanelLayout::NUMBER;
  InputMethod::AutoCapital::Type autoCapital = InputMethod::AutoCapital::WORD;
  InputMethod::ButtonAction::Type buttonAction = InputMethod::ButtonAction::GO;
  int inputVariation = 1;
  propertyMap["PANEL_LAYOUT"] = panelLayout;
  propertyMap["AUTO_CAPITALIZE"] = autoCapital;
  propertyMap["BUTTON_ACTION"] = buttonAction;
  propertyMap["VARIATION"] = inputVariation;
  field.SetProperty( TextField::Property::INPUT_METHOD_SETTINGS, propertyMap );

  Property::Value value = field.GetProperty( TextField::Property::INPUT_METHOD_SETTINGS );
  Property::Map map;
  value.Get( map );

  int layout = 0;
  map[ "PANEL_LAYOUT" ].Get( layout );
  DALI_CHECK_FAIL( static_cast<int>(panelLayout) != layout, "TextField fails to get the value of PANEL_LAYOUT in INPUT_METHOD_SETTINGS." );

  int capital = 0;
  map[ "AUTO_CAPITALIZE" ].Get( capital );
  DALI_CHECK_FAIL( static_cast<int>(autoCapital) != capital, "TextField fails to get the value of AUTO_CAPITALIZE in INPUT_METHOD_SETTINGS." );

  int action = 0;
  map[ "BUTTON_ACTION" ].Get( action );
  DALI_CHECK_FAIL( static_cast<int>(buttonAction) != action, "TextField fails to get the value of BUTTON_ACTION in INPUT_METHOD_SETTINGS." );

  int variation = 0;
  map[ "VARIATION" ].Get( variation );
  DALI_CHECK_FAIL( inputVariation != variation, "TextField fails to get the value of VARIATION in INPUT_METHOD_SETTINGS." );

  DaliLog::PrintPass();
}



/**
 * @testcase            UtcDaliTextFieldNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliTextFieldNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliTextFieldConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldCopyConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of a copy of object
 */

int UtcDaliTextFieldCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Checks correct assigntment of one object to other object
 */

int UtcDaliTextFieldOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliTextFieldDownCastP
 * @since_tizen         2.4
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliTextFieldDowncastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldDownCastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliTextFieldDowncastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldTextChangedSignalP
 * @since_tizen         2.4
 * @description         Checks the functionality of TextChangedSignal API
 */

int UtcDaliTextFieldTextChangedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_TEXT_CHANGED_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldPropertyInputColorP
 * @since_tizen         2.4
 * @description         Checks the property InputColor
 */

int UtcDaliTextFieldPropertyInputColorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_PROPERTY_INPUT_COLOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldPropertyEnableMarkupP
 * @since_tizen         2.4
 * @description         Checks the property EnableMarkup
 */

int UtcDaliTextFieldPropertyEnableMarkupP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_PROPERTY_ENABLE_MARKUP_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldPropertyUnderlineP
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the UNDERLINE property
 */

int UtcDaliTextFieldPropertyUnderlineP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_PROPERTY_UNDERLINE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldPropertyInputUnderlineP
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the INPUT_UNDERLINE property
 */

int UtcDaliTextFieldPropertyInputUnderlineP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_PROPERTY_INPUT_UNDERLINE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldPropertyShadowP
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the SHADOW property
 */

int UtcDaliTextFieldPropertyShadowP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_PROPERTY_SHADOW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldPropertyInputShadowP
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the INPUT_SHADOW property
 */

int UtcDaliTextFieldPropertyInputShadowP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_PROPERTY_INPUT_SHADOW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldPropertyEmbossP
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the EMBOSS property
 */

int UtcDaliTextFieldPropertyEmbossP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_PROPERTY_EMBOSS_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldPropertyInputEmbossP
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the INPUT_EMBOSS property
 */

int UtcDaliTextFieldPropertyInputEmbossP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_PROPERTY_INPUT_EMBOSS_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldPropertyOutlineP
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the OUTLINE property
 */

int UtcDaliTextFieldPropertyOutlineP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_PROPERTY_OUTLINE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldPropertyInputOutlineP
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the INPUT_OUTLINE property
 */

int UtcDaliTextFieldPropertyInputOutlineP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_PROPERTY_INPUT_OUTLINE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextFieldPropertyInputMethodSettingsP
 * @since_tizen         5.0
 * @description         Checks test for correct setting and getting of the INPUT_METHOD_SETTINGS property
 */

int UtcDaliTextFieldPropertyInputMethodSettingsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextField_TestApp testApp( application, TEXT_FIELD_PROPERTY_INPUT_METHOD_SETTINGS_P );
  application.MainLoop();

  return test_return_value;
}
