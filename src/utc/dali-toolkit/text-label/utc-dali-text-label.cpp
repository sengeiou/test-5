#include "utc-dali-text-label-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_TextLabel_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_TextLabel_startup(void)
{
  test_return_value =0;
}

/**
 * @function            utc_Dali_TextLabel_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_TextLabel_cleanup(void)
{
}

void TextLabelNewP();
void TextLabelConstructorP();
void TextLabelCopyConstructorP();
void TextLabelOperatorAssignmentP();
void TextLabelDownCastP();
void TextLabelDownCastN();
void TextLabelPropertyLineSpacingP();
void TextLabelPropertyUnderlineP();
void TextLabelPropertyShadowP();
void TextLabelPropertyEmbossP();
void TextLabelPropertyOutlineP();


namespace
{
  enum TEST_CASES_LIST_TEXT_LABEL
  {
    TEXT_LABEL_NEW_P,
    TEXT_LABEL_CONSTRUCTOR_P,
    TEXT_LABEL_COPY_CONSTRUCTOR_P,
    TEXT_LABEL_OPERATOR_ASSIGNMENT_P,
    TEXT_LABEL_DOWNCAST_P,
    TEXT_LABEL_DOWNCAST_N,
    TEXT_LABEL_PROPERTY_LINE_SPACING_P,
    TEXT_LABEL_PROPERTY_UNDERLINE_P,
    TEXT_LABEL_PROPERTY_SHADOW_P,
    TEXT_LABEL_PROPERTY_EMBOSS_P,
    TEXT_LABEL_PROPERTY_OUTLINE_P
  };

  struct TextLabel_TestApp : public ConnectionTracker
  {
    TextLabel_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &TextLabel_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &TextLabel_TestApp::Tick );
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
        case TEXT_LABEL_NEW_P:
          TextLabelNewP();
          break;
        case TEXT_LABEL_CONSTRUCTOR_P:
          TextLabelConstructorP();
          break;
        case TEXT_LABEL_COPY_CONSTRUCTOR_P:
          TextLabelCopyConstructorP();
          break;
        case TEXT_LABEL_OPERATOR_ASSIGNMENT_P:
          TextLabelOperatorAssignmentP();
          break;
        case TEXT_LABEL_DOWNCAST_P:
          TextLabelDownCastP();
          break;
        case TEXT_LABEL_DOWNCAST_N:
          TextLabelDownCastN();
          break;
        case TEXT_LABEL_PROPERTY_LINE_SPACING_P:
          TextLabelPropertyLineSpacingP();
          break;
        case TEXT_LABEL_PROPERTY_UNDERLINE_P:
          TextLabelPropertyUnderlineP();
          break;
        case TEXT_LABEL_PROPERTY_SHADOW_P:
          TextLabelPropertyShadowP();
          break;
        case TEXT_LABEL_PROPERTY_EMBOSS_P:
          TextLabelPropertyEmbossP();
          break;
        case TEXT_LABEL_PROPERTY_OUTLINE_P:
          TextLabelPropertyOutlineP();
          break;
      }
    }
    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

} // unnamed namespace


void TextLabelNewP(void)
{
  TextLabel textLabel1 = TextLabel::New( );
  DALI_CHECK_FAIL(!textLabel1, "TextLabel::New() is failed.");
  TextLabel textLabel2 = TextLabel::New( "Test Text" );
  DALI_CHECK_FAIL(!textLabel2, "TextLabel::New(const std::string&) is failed.");
  DaliLog::PrintPass();
}

void TextLabelConstructorP(void)
{
  TextLabel textLabel;
  DALI_CHECK_FAIL(textLabel, "TextLabel::TextLabel() is failed.");
  DaliLog::PrintPass();
}

void TextLabelDownCastP()
{
  TextLabel textLabel1 = TextLabel::New();
  BaseHandle object( textLabel1 );

  TextLabel textLabel2 = TextLabel::DownCast( object );
  DALI_CHECK_FAIL(!textLabel2, "TextLabel handle is empty.");

  TextLabel textLabel3 = DownCast< TextLabel >( object );
  DALI_CHECK_FAIL(!textLabel3, "TextLabel handle is empty after downcast.");
  DaliLog::PrintPass();
}

void TextLabelDownCastN(void)
{
  BaseHandle uninitializedObject;
  TextLabel textLabel1 = TextLabel::DownCast( uninitializedObject );
  DALI_CHECK_FAIL(textLabel1, "TextLabel handle is not empty.");

  TextLabel textLabel2 = DownCast< TextLabel >( uninitializedObject );
  DALI_CHECK_FAIL(textLabel2, "TextLabel handle is not empty after downcast.");
  DaliLog::PrintPass();
}

void TextLabelOperatorAssignmentP()
{
  TextLabel textLabel = TextLabel::New();
  textLabel.SetProperty( TextLabel::Property::TEXT_COLOR, Color::RED );

  TextLabel copy = textLabel;
  DALI_CHECK_INSTANCE(copy, "TextLabel handle is empty after assignment.");
  DALI_CHECK_FAIL( copy.GetProperty<Vector4>( TextLabel::Property::TEXT_COLOR ) != textLabel.GetProperty<Vector4>( TextLabel::Property::TEXT_COLOR ), "TextLabel::operator= is failed.");
  DaliLog::PrintPass();
}

void TextLabelCopyConstructorP()
{
  TextLabel textLabel = TextLabel::New();
  textLabel.SetProperty( TextLabel::Property::TEXT_COLOR, Color::RED );

  TextLabel copy(textLabel);
  DALI_CHECK_INSTANCE(copy, "TextLabel handle is empty after copy.");
  DALI_CHECK_FAIL( copy.GetProperty<Vector4>( TextLabel::Property::TEXT_COLOR ) != textLabel.GetProperty<Vector4>( TextLabel::Property::TEXT_COLOR ), "TextLabel::TextLabel(const TextLabel&) is failed.");
  DaliLog::PrintPass();
}

void TextLabelPropertyLineSpacingP()
{
  TextLabel textLabel = TextLabel::New();

  DALI_CHECK_FAIL( ((textLabel.GetProperty( TextLabel::Property::LINE_SPACING ).Get<float>()) - 0.0f ) > Math::MACHINE_EPSILON_1000, "TextLabel fails to get the default value of LINE_SPACING property." );

  textLabel.SetProperty( TextLabel::Property::LINE_SPACING, 10.f );
  DALI_CHECK_FAIL( ((textLabel.GetProperty( TextLabel::Property::LINE_SPACING ).Get<float>()) - 10.0f ) > Math::MACHINE_EPSILON_1000, "TextLabel fails to get the current value of LINE_SPACING property." );

  DaliLog::PrintPass();
}

void TextLabelPropertyUnderlineP()
{
  TextLabel textLabel = TextLabel::New();

  std::string propertyValue( "{\"enable\":\"true\",\"color\":\"red\",\"height\":\"1\"}" );
  textLabel.SetProperty( TextLabel::Property::UNDERLINE, propertyValue );
  DALI_CHECK_FAIL( textLabel.GetProperty( TextLabel::Property::UNDERLINE ).Get<std::string>() != propertyValue, "TextLabel fails to get the value of UNDERLINE property."  );

  DaliLog::PrintPass();
}

void TextLabelPropertyShadowP()
{
  TextLabel textLabel = TextLabel::New();

  std::string propertyValue( "{\"color\":\"green\",\"offset\":\"2 2\",\"blurRadius\":\"0\"}" );
  textLabel.SetProperty( TextLabel::Property::SHADOW, propertyValue );
  DALI_CHECK_FAIL( textLabel.GetProperty( TextLabel::Property::SHADOW ).Get<std::string>() != propertyValue, "TextLabel fails to get the value of SHADOW property."  );

  DaliLog::PrintPass();
}

void TextLabelPropertyEmbossP()
{
  TextLabel textLabel = TextLabel::New();

  std::string propertyValue( "Emboss properties" );
  textLabel.SetProperty( TextLabel::Property::EMBOSS, propertyValue );
  DALI_CHECK_FAIL( textLabel.GetProperty( TextLabel::Property::EMBOSS ).Get<std::string>() != propertyValue, "TextLabel fails to get the value of EMBOSS property."  );

  DaliLog::PrintPass();
}

void TextLabelPropertyOutlineP()
{
  TextLabel textLabel = TextLabel::New();

  std::string propertyValue( "Outline properties" );
  textLabel.SetProperty( TextLabel::Property::OUTLINE, propertyValue );
  DALI_CHECK_FAIL( textLabel.GetProperty( TextLabel::Property::OUTLINE ).Get<std::string>() != propertyValue, "TextLabel fails to get the value of OUTLINE property."  );

  DaliLog::PrintPass();
}

/**
 * @testcase            UtcDaliTextLabelNewP
 * @since_tizen         2.4
 * @description         to check for the TextLabel::New() functionality
 */

int UtcDaliTextLabelNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextLabel_TestApp testApp( application, TEXT_LABEL_NEW_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextLabelConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliTextLabelConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextLabel_TestApp testApp( application, TEXT_LABEL_CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextLabelCopyConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of a copy of object
 */

int UtcDaliTextLabelCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextLabel_TestApp testApp( application, TEXT_LABEL_COPY_CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliTextLabelOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Checks correct assigntment of one object to other object
 */

int UtcDaliTextLabelOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextLabel_TestApp testApp( application, TEXT_LABEL_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextLabelDowncastP
 * @since_tizen         2.4
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliTextLabelDowncastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextLabel_TestApp testApp( application, TEXT_LABEL_DOWNCAST_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextLabelDowncastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliTextLabelDowncastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextLabel_TestApp testApp( application, TEXT_LABEL_DOWNCAST_N);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextLabelPropertyLineSpacing
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the LINE_SPACING property
 */

int UtcDaliTextLabelPropertyLineSpacingP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextLabel_TestApp testApp( application, TEXT_LABEL_PROPERTY_LINE_SPACING_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextLabelPropertyUnderline
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the UNDERLINE property
 */

int UtcDaliTextLabelPropertyUnderlineP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextLabel_TestApp testApp( application, TEXT_LABEL_PROPERTY_UNDERLINE_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextLabelPropertyShadow
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the SHADOW property
 */

int UtcDaliTextLabelPropertyShadowP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextLabel_TestApp testApp( application, TEXT_LABEL_PROPERTY_SHADOW_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextLabelPropertyEmboss
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the EMBOSS property
 */

int UtcDaliTextLabelPropertyEmbossP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextLabel_TestApp testApp( application, TEXT_LABEL_PROPERTY_EMBOSS_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTextLabelPropertyOutline
 * @since_tizen         3.0
 * @description         Checks test for correct setting and getting of the OUTLINE property
 */

int UtcDaliTextLabelPropertyOutlineP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TextLabel_TestApp testApp( application, TEXT_LABEL_PROPERTY_OUTLINE_P);
  application.MainLoop();

  return test_return_value;
}
