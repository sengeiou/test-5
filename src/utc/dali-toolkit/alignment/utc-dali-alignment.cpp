#include "utc-dali-alignment-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Alignment_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Alignment_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_Alignment_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Alignment_cleanup(void)
{

}

void AlignmentConstructorP();
void AlignmentNewP();
void AlignmentCopyConstructorP();
void AlignmentOperatorAssignmentP();
void AlignmentDownCastP();
void AlignmentDownCastN();
void AlignmentSetGetAlignmentTypeP();
void AlignmentSetGetScalingP();
void AlignmentSetGetPaddingP();

namespace
{
  enum TEST_CASES_LIST_ALIGNMENT
  {
    ALIGNMENT_CONSTRUCTOR_P,
    ALIGNMENT_NEW_P,
    ALIGNMENT_COPY_CONSTRUCTOR_P,
    ALIGNMENT_ASSIGNMENT_OPERATOR_P,
    ALIGNMENT_DOWNCAST_P,
    ALIGNMENT_DOWNCAST_N,
    ALIGNMENT_SET_GET_ALIGNMENT_TYPE_P,
    ALIGNMENT_SET_GET_SCALING_P,
    ALIGNMENT_SET_GET_PADDING_P
  };

  struct Alignment_TestApp : public ConnectionTracker
  {
    Alignment_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Alignment_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Alignment_TestApp::Tick );
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
        case ALIGNMENT_NEW_P:
            AlignmentNewP();
            break;
        case ALIGNMENT_CONSTRUCTOR_P:
            AlignmentConstructorP();
            break;
        case ALIGNMENT_COPY_CONSTRUCTOR_P:
            AlignmentCopyConstructorP();
            break;
        case ALIGNMENT_ASSIGNMENT_OPERATOR_P:
            AlignmentOperatorAssignmentP();
            break;
        case ALIGNMENT_DOWNCAST_P:
            AlignmentDownCastP();
            break;
        case ALIGNMENT_DOWNCAST_N:
            AlignmentDownCastN();
            break;
        case ALIGNMENT_SET_GET_ALIGNMENT_TYPE_P:
            AlignmentSetGetAlignmentTypeP();
            break;
        case ALIGNMENT_SET_GET_SCALING_P:
            AlignmentSetGetScalingP();
            break;
        case ALIGNMENT_SET_GET_PADDING_P:
            AlignmentSetGetPaddingP();
            break;
      }
    }

    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} //unnamed namespace

void AlignmentConstructorP()
{
  Alignment alignment;
  DALI_CHECK_FAIL( alignment, "Alignment Default Contructor is failed." );

  DaliLog::PrintPass();
}

void AlignmentNewP()
{
  Alignment alignment;
  DALI_CHECK_FAIL( alignment, "Failed to create a null aligment handle" );

  alignment = Alignment::New(Toolkit::Alignment::HorizontalLeft, Toolkit::Alignment::VerticalCenter);
  DALI_CHECK_FAIL( !alignment, "Dali::Alignment::New() is failed to initialize the alignment handle." );

  DaliLog::PrintPass();
}

void AlignmentCopyConstructorP()
{
  Alignment alignment = Alignment::New(Toolkit::Alignment::HorizontalLeft, Toolkit::Alignment::VerticalCenter);
  DALI_CHECK_FAIL(!alignment, "Dali::Alignment::New is failed to create an handle." );

  Alignment* copyAlignment(&alignment);
  DALI_CHECK_FAIL( !copyAlignment, "Alignment copy constructor is failed." );

  DALI_CHECK_FAIL( *copyAlignment != alignment, "Alignment copy constructor is not same with default Alignment." );

  DaliLog::PrintPass();
}

void AlignmentOperatorAssignmentP()
{
  Alignment alignment = Alignment::New(Toolkit::Alignment::HorizontalLeft, Toolkit::Alignment::VerticalCenter);
  DALI_CHECK_FAIL(!alignment, "Dali::Alignment::New is failed to create a handle." );

  Alignment* copyAlignment = &alignment;
  DALI_CHECK_FAIL(copyAlignment == NULL,  "Copy Alignment assign has returned null." );
  DALI_CHECK_FAIL( *copyAlignment != alignment, "Alignment copy is not same with default Alignment." );

  DaliLog::PrintPass();
}

void AlignmentDownCastP()
{
  Alignment alignment = Alignment::New(Toolkit::Alignment::HorizontalLeft, Toolkit::Alignment::VerticalCenter);
  DALI_CHECK_FAIL(!alignment, "Dali::Alignment::New is failed to create a handle." );

  Handle handleAlignment;
  handleAlignment = alignment;
  Alignment downCastAlignment = Alignment::DownCast( handleAlignment );
  DALI_CHECK_FAIL(!downCastAlignment, "downCastAlignment has returned null." );
  DALI_CHECK_FAIL( downCastAlignment != alignment, "Alignment Downcasted is not same with default Alignment." );

  DaliLog::PrintPass();
}

void AlignmentDownCastN()
{
  BaseHandle unInitializedObject;

  Alignment alignment = Alignment::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(alignment, "Model3dview handle is not empty." );

  Alignment alignment2 = DownCast< Alignment >( unInitializedObject );
  DALI_CHECK_FAIL(alignment2, "Model3dview handle is not empty." );

  DaliLog::PrintPass();
}

void AlignmentSetGetAlignmentTypeP()
{
  Alignment::Type alignmentType;

  Alignment alignment = Alignment::New();
  DALI_CHECK_FAIL(!alignment, "Dali::Alignment::New is failed to create a handle." );

  alignmentType = Toolkit::Alignment::HorizontalCenter;
  alignment.SetAlignmentType(Toolkit::Alignment::HorizontalLeft);
  alignmentType = alignment.GetAlignmentType();

  DALI_CHECK_FAIL(!(alignmentType & Toolkit::Alignment::HorizontalLeft), "Get Alignment Type & Set Alignment Type is mismatched." );

  DaliLog::PrintPass();
}


void AlignmentSetGetScalingP()
{
  Alignment::Scaling alignmentScaling;

  Alignment alignment = Alignment::New();
  DALI_CHECK_FAIL(!alignment, "Dali::Alignment::New() is failed to create a handle." );

  alignmentScaling = Toolkit::Alignment::ScaleNone;
  alignment.SetScaling(Toolkit::Alignment::ScaleToFill);
  alignmentScaling = alignment.GetScaling();

  DALI_CHECK_FAIL(!(alignmentScaling & Toolkit::Alignment::ScaleToFill), "SetScaling of Alignment & GetScaling of Alignment is mismatched." );

  DaliLog::PrintPass();
}

void AlignmentSetGetPaddingP()
{
  float fLeft = 1.0f, fRight = 1.5f, fTop = 2.0f, fBottom = 0.5f;
  Alignment::Padding paddingSet, paddingGet;

  Alignment alignment = Alignment::New();
  DALI_CHECK_FAIL(!alignment,  "Dali::Alignment::New is Failed to create a handle." );

  // Matching with zero value as no padding is set
  DALI_CHECK_FAIL(alignment.GetPadding().left != 0.0f || alignment.GetPadding().right != 0.0f || alignment.GetPadding().top != 0.0f || alignment.GetPadding().bottom != 0.0f,  "GetPadding is not zero." );

  alignment.SetPadding(paddingSet); //default padding is set
  paddingGet = alignment.GetPadding();

  // Matching with zero value as parameter is not set (default padding is set)
  DALI_CHECK_FAIL(paddingGet.left != 0.0f || paddingGet.right != 0.0f || paddingGet.top != 0.0f || paddingGet.bottom != 0.0f,  "SetPadding & GetPadding mismatched." );

  paddingSet = Alignment::Padding(fLeft, fRight, fTop, fBottom);
  //Check the set padding values
  DALI_CHECK_FAIL(paddingSet.left != fLeft || paddingSet.right != fRight || paddingSet.top != fTop || paddingSet.bottom != fBottom,  "Alignment::Padding instance is not created properly with parameters." );

  alignment.SetPadding(paddingSet);
  paddingGet = alignment.GetPadding();
  //Matching get values with set padding values
  DALI_CHECK_FAIL( paddingGet.left != fLeft || paddingGet.right != fRight || paddingGet.top != fTop || paddingGet.bottom != fBottom,  "SetPadding & GetPadding mismatched." );

  DaliLog::PrintPass();
}

/**
 * @testcase            UtcDaliAlignmentConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliAlignmentConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Alignment_TestApp testApp( application, ALIGNMENT_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAlignmentNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliAlignmentNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Alignment_TestApp testApp( application, ALIGNMENT_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAlignmentCopyConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of a copy of object
 */

int UtcDaliAlignmentCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Alignment_TestApp testApp( application, ALIGNMENT_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAlignmentOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Checks correct assigntment of one object to other object
 */

int UtcDaliAlignmentOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Alignment_TestApp testApp( application, ALIGNMENT_ASSIGNMENT_OPERATOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAlignmentDownCastP
 * @since_tizen         2.4
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliAlignmentDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Alignment_TestApp testApp( application, ALIGNMENT_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAlignmentDownCastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliAlignmentDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Alignment_TestApp testApp( application, ALIGNMENT_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAlignmentSetGetAlignmentTypeP
 * @since_tizen         2.4
 * @description         Checks for correct setting of Aligment Type
 */

int UtcDaliAlignmentSetGetAlignmentTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Alignment_TestApp testApp( application, ALIGNMENT_SET_GET_ALIGNMENT_TYPE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAlignmentSetGetScalingP
 * @since_tizen         2.4
 * @description         Checks for correct setting of Scale
 */

int UtcDaliAlignmentSetGetScalingP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Alignment_TestApp testApp( application, ALIGNMENT_SET_GET_SCALING_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAlignmentSetGetPaddingP
 * @since_tizen         2.4
 * @description         Checks for correct setting of Padding
 */

int UtcDaliAlignmentSetGetPaddingP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Alignment_TestApp testApp( application, ALIGNMENT_SET_GET_PADDING_P );
  application.MainLoop();

  return test_return_value;
}
