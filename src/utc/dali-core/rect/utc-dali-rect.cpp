#include "utc-dali-rect-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Rect
/**
 * @function      utc_Dali_Rect_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_Rect_startup(void)
{
  test_return_value=0;
}

/**
 * @function      utc_Dali_Rect_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_Rect_cleanup(void)
{
}

void RectSetP();
void RectIsEmptyP();
void RectAreaRectP();
void RectBottomP();
void RectTopP();
void RectLeftP();
void RectRightP();
void RectContainsP();
void RectIntersectsP();
void RectOperatorEqualsOStreamP();
void RectCopyConsP();
void RectConsWithoutParamP();
void RectConsWithParamP();

namespace
{
  enum TEST_CASES_LIST_RECT
  {
    RECT_SET_P,
    RECT_IS_EMPTY_P,
    RECT_AREA_P,
    RECT_BOTTOM2_P,
    RECT_TOP2_P,
    RECT_LEFT2_P,
    RECT_RIGHT2_P,
    RECT_CONTAINS_P,
    RECT_INTERSECTS_P,
    RECT_OPERATOR_EQUALS_OSTREAM_P,
    RECT_COPY_CONS_P,
    RECT_CONS_WITH_OUT_PARAM_P,
    RECT_CONS_WITH_PARAM_P
  };

  struct Rect_TestApp : public ConnectionTracker
  {
    Rect_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Rect_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Rect_TestApp::Tick );
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
        case RECT_SET_P:
          RectSetP();
          break;

        case RECT_IS_EMPTY_P:
          RectIsEmptyP();
          break;

        case RECT_AREA_P:
          RectAreaRectP();
          break;

        case RECT_BOTTOM2_P:
          RectBottomP();
          break;

        case RECT_TOP2_P:
          RectTopP();
          break;

        case RECT_LEFT2_P:
          RectLeftP();
          break;

        case RECT_RIGHT2_P:
          RectRightP();
          break;

        case RECT_CONTAINS_P:
          RectContainsP();
          break;

        case RECT_INTERSECTS_P:
          RectIntersectsP();
          break;

        case RECT_OPERATOR_EQUALS_OSTREAM_P:
          RectOperatorEqualsOStreamP();
          break;

        case RECT_COPY_CONS_P:
          RectCopyConsP();
          break;

        case RECT_CONS_WITH_OUT_PARAM_P:
          RectConsWithoutParamP();
          break;

        case RECT_CONS_WITH_PARAM_P:
          RectConsWithParamP();
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
void RectSetP()
{
  float fXvalue=10.0f, fYvalue=20.0f, fWidth=400.0f, fHeight=200.0f;
  Rect<float> rect(fXvalue, fYvalue, fWidth, fHeight);


  rect.Set(fXvalue, fYvalue, fWidth, fHeight);

  DALI_CHECK_FAIL(rect.x != fXvalue || rect.y != fYvalue || rect.width != fWidth || rect.height != fHeight,  "Dali::Set is Failed.");
  DaliLog::PrintPass();
}
void RectIsEmptyP()
{
  Rect<float> rect(10.0f, 20.0f, 0.0f, 200.0f);
  bool bResult = false;


  bResult = false;
  bResult = rect.IsEmpty();
  DALI_CHECK_FAIL(!bResult, "Dali::IsEmpty is Failed: Showing not empty even though the width is ZERO" );

  DaliLog::PrintPass();
}
void RectAreaRectP()
{
  float fXvalue=10.0f, fYvalue=20.0f, fWidth=10.0f, fHeight=200.0f;
  float fAreaRes=0.0f, fAreaChk = 0.0f;


  Rect<float> rect(fXvalue, fYvalue, fWidth, fHeight);
  fAreaRes = fWidth * fHeight;
  fAreaChk = 0.0f;

  fAreaChk = rect.Area();
  DALI_CHECK_FAIL(fAreaRes != fAreaChk, "Dali::Area is Failed" );

  DaliLog::PrintPass();
}
void RectBottomP()
{
  bool bRet = true;

  bRet = RectBottomLeftRightTop(RECT_BOTTOM);

  DALI_CHECK_FAIL(!bRet, "RectBottomLeftRightTop returns false" );
  DaliLog::PrintPass();
}
void RectTopP()
{
  bool bRet = true;

  bRet = RectBottomLeftRightTop(RECT_TOP);

  DALI_CHECK_FAIL(!bRet, "RectBottomLeftRightTop returns false" );
  DaliLog::PrintPass();
}
void RectLeftP()
{
  bool bRet = true;

  bRet = RectBottomLeftRightTop(RECT_LEFT);

  DALI_CHECK_FAIL(!bRet, "RectBottomLeftRightTop returns false" );
  DaliLog::PrintPass();
}
void RectRightP()
{
  bool bRet = true;

  bRet = RectBottomLeftRightTop(RECT_RIGHT);

  DALI_CHECK_FAIL(!bRet, "RectBottomLeftRightTop returns false" );
  DaliLog::PrintPass();
}
void RectContainsP()
{
  float fXvalue1=10.0f, fYvalue1=20.0f, fWidth1=200.0f, fHeight1=200.0f;
  float fXvalue2=50.0f, fYvalue2=70.0f, fWidth2=50.0f, fHeight2=50.0f;
  bool bChk = false;

  Rect<float> rect1(fXvalue1, fYvalue1, fWidth1, fHeight1);
  Rect<float> rect2(fXvalue2, fYvalue2, fWidth2, fHeight2);
  bChk = false;

  bChk = rect1.Contains(rect2);
  DALI_CHECK_FAIL(!bChk, "Dali::Contains is Failed" );

  DaliLog::PrintPass();
}
void RectIntersectsP()
{
  float fXvalue1=10.0f, fYvalue1=20.0f, fWidth1=200.0f, fHeight1=200.0f;
  float fXvalue2=110.0f, fYvalue2=20.0f, fWidth2=200.0f, fHeight2=200.0f;

  bool bChk = false;

  Rect<float> rect1(fXvalue1, fYvalue1, fWidth1, fHeight1);
  Rect<float> rect2(fXvalue2, fYvalue2, fWidth2, fHeight2);
  bChk = false;
  bChk = rect1.Intersects(rect2);
  DALI_CHECK_FAIL(!bChk, "Dali::Intersects is Failed" );

  DaliLog::PrintPass();
}
void RectOperatorEqualsOStreamP()
{
  float fXvalue1=10.0f, fYvalue1=20.0f, fWidth1=200.0f, fHeight1=200.0f;
  float fXvalue2=10.0f, fYvalue2=20.0f, fWidth2=200.0f, fHeight2=200.0f;
  ostringstream ossRectOne, ossRectTwo ;

  bool bChk = false;

  Rect<float> rect1(fXvalue1, fYvalue1, fWidth1, fHeight1);
  Rect<float> rect2(fXvalue2, fYvalue2, fWidth2, fHeight2);
  bChk = false;

  if(rect1 == rect2)
  {
    bChk = true;
  }
  DALI_CHECK_FAIL(!bChk, "Dali::Rect equality operator is Failed" );
  ossRectOne << rect1;
  ossRectTwo << rect2;
  DALI_CHECK_FAIL( ossRectOne.str() != ossRectTwo.str(), "operator<< for Rect is failed." );

  DaliLog::PrintPass();
}
void RectCopyConsP()
{
  float fXvalue=10.0f, fYvalue=20.0f, fWidth=200.0f, fHeight=200.0f;

  Rect<float> rect1(fXvalue, fYvalue, fWidth, fHeight);
  Rect<float> rect2(rect1);
  DALI_CHECK_FAIL(rect2.x != fXvalue || rect2.y != fYvalue || rect2.width != fWidth || rect2.height != fHeight, "Dali::Rect::Rect(const Rect<float>&) is Failed" );

  DaliLog::PrintPass();
}
void RectConsWithoutParamP()
{
  const float X_VALUE = 0.0f, Y_VALUE = 0.0f, WIDTH = 0.0f, HEIGHT = 0.0f;

  Rect<float> rect2;
  DALI_CHECK_FAIL(X_VALUE != rect2.x  || Y_VALUE != rect2.y || WIDTH != rect2.width || HEIGHT != rect2.height, "Dali::Rect::Rect<float>() is Failed" );

  DaliLog::PrintPass();
}
void RectConsWithParamP()
{
  float fXvalue=10.0f, fYvalue=20.0f, fWidth=30.0f, fHeight=40.0f;

  Rect<float> rect2(fXvalue, fYvalue, fWidth, fHeight);
  DALI_CHECK_FAIL(fXvalue != rect2.x  || fYvalue != rect2.y || fWidth != rect2.width || fHeight != rect2.height, "Dali::Rect::Rect<float>(x, y, width, height) is Failed" );

  DaliLog::PrintPass();
}
/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase      UtcDaliRectSetP
 * @since_tizen   2.4
 * @description   check if Set api works or not.
 */
int UtcDaliRectSetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_SET_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliRectIsEmptyP
 * @since_tizen   2.4
 * @description   check if IsEmpty api works or not.
 */
int UtcDaliRectIsEmptyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_IS_EMPTY_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliRectAreaP
 * @since_tizen   2.4
 * @description   check if Area api works or not.
 */
int UtcDaliRectAreaP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_AREA_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliRectBottomP
 * @since_tizen   2.4
 * @description   check if Bottom api works or not.
 */
int UtcDaliRectBottomP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_BOTTOM2_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliRectTopP
 * @since_tizen   2.4
 * @description   check if Top api works or not.
 */
int UtcDaliRectTopP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_TOP2_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliRectLeftP
 * @since_tizen   2.4
 * @description   check if Left api works or not.
 */
int UtcDaliRectLeftP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_LEFT2_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliRectRightP
 * @since_tizen   2.4
 * @description   check if Right api works or not.
 */
int UtcDaliRectRightP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_RIGHT2_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliRectContainsP
 * @since_tizen   2.4
 * @description   check if Contains api works or not.
 */
int UtcDaliRectContainsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_CONTAINS_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliRectIntersectsP
 * @since_tizen   2.4
 * @description   check if Intersects api works or not.
 */
int UtcDaliRectIntersectsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_INTERSECTS_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliRectOperatorEqualsOStreamP
 * @since_tizen   2.4
 * @description   check if OperatorEqualsOStream api works or not.
 */
int UtcDaliRectOperatorEqualsOStreamP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_OPERATOR_EQUALS_OSTREAM_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliRectCopyConsP
 * @since_tizen   2.4
 * @description   check if CopyCons api works or not.
 */
int UtcDaliRectCopyConsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_COPY_CONS_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliRectConsWithoutParamP
 * @since_tizen   2.4
 * @description   check if ConsWithoutParam api works or not.
 */
int UtcDaliRectConsWithoutParamP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_CONS_WITH_OUT_PARAM_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliRectConsWithParamP
 * @since_tizen   2.4
 * @description   check if ConsWithParam api works or not.
 */
int UtcDaliRectConsWithParamP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Rect_TestApp testApp( application, RECT_CONS_WITH_PARAM_P);
  application.MainLoop();
  return test_return_value;
}
