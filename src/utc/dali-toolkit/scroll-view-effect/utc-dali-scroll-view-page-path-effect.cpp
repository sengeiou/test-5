#include "utc-dali-scroll-view-effect-common.h"

//& set: ScrollViewPagePath

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;
int gRenderCountScrollView1;
ScrollView gScrollView1;                                        /** ScrollView instance **/
static std::vector< Actor > gVecPagesActor;                     /** Vector of actor pages **/
Actor gActorA1;                                                 /** Actor binded/ added to scrollview */
typedef std::vector< Actor >::iterator ActorIter;               /** Iterator for actor pages **/
const int SCROLL_DESTINATION = 2;                               /** Destination page number **/

/**
 * @function                     ScrollViewCreateRuler1
 * @description                  Creates a Ruler that snaps to a specified grid size.
 * @return                       The ruler is returned.
 */
RulerPtr ScrollViewCreateRuler1(float fGridSize = 0.0f)
{
  if(fGridSize <= Math::MACHINE_EPSILON_0)
  {
    return new DefaultRuler();
  }
  return new FixedRuler(fGridSize);
}

/**
 * @function                     ScrollViewSetupTest
 * @description                  Sets up a scrollview
 * @return                       ScrollView
 */
ScrollView ScrollViewSetupTest1(int nRows, int nColumns, Vector2 vec2Size)
{
  Constraint constraint;

  ScrollView scrollView = ScrollView::New();
  scrollView.SetSize(vec2Size);
  scrollView.SetAnchorPoint(AnchorPoint::CENTER);
  scrollView.SetParentOrigin(ParentOrigin::CENTER);

  constraint = Constraint::New<Dali::Vector3>( scrollView, Dali::Actor::Property::SIZE, Dali::EqualToConstraint() );
  constraint.AddSource( Dali::ParentSource( Dali::Actor::Property::SIZE ) );
  constraint.Apply();

  scrollView.SetWrapMode(false);
  Stage::GetCurrent().Add( scrollView );
  RulerPtr rulerX = ScrollViewCreateRuler1(vec2Size.width);
  RulerPtr rulerY = ScrollViewCreateRuler1(vec2Size.height);
  if(nColumns > 1)
  {
    rulerX->SetDomain(RulerDomain(0.0f, vec2Size.width * nColumns));
  }
  else
  {
    rulerX->Disable();
  }
  if(nRows > 1)
  {
    rulerY->SetDomain(RulerDomain(0.0f, vec2Size.width * nRows));
  }
  else
  {
    rulerY->Disable();
  }

  scrollView.SetRulerX( rulerX );
  scrollView.SetRulerY( rulerY );
  Stage::GetCurrent().Add( scrollView );

  Actor container = Actor::New();
  container.SetParentOrigin(ParentOrigin::CENTER);
  container.SetAnchorPoint(AnchorPoint::CENTER);
  container.SetSize( vec2Size );
  scrollView.Add( container );

  constraint = Constraint::New<Vector3>( container, Actor::Property::SIZE, EqualToConstraint() );
  constraint.AddSource( Dali::ParentSource( Dali::Actor::Property::SIZE ) );
  constraint.Apply();

  gVecPagesActor.clear();
  for(int row = 0;row<nRows;row++)
  {
    for(int column = 0;column<nColumns;column++)
    {
      Actor page = Actor::New();

      constraint = Constraint::New<Vector3>( page, Actor::Property::SIZE, EqualToConstraint() );
      constraint.AddSource( Dali::ParentSource( Dali::Actor::Property::SIZE ) );
      constraint.Apply();
      page.SetParentOrigin( ParentOrigin::CENTER );
      page.SetAnchorPoint( AnchorPoint::CENTER );
      page.SetPosition( column * vec2Size.x, row * vec2Size.y );
      container.Add(page);

      gVecPagesActor.push_back(page);
    }
  }

  return scrollView;
}

/**
 * @function            utc_Dali_ScrollViewPagePathEffect_cleanup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ScrollViewPagePathEffect_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_ScrollViewPagePathEffect_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ScrollViewPagePathEffect_cleanup(void)
{

}

void ScrollViewPagePathEffectConstructorP();
void ScrollViewPagePathEffectNewP();
void ScrollViewPagePathEffectDowncastP();
void ScrollViewPagePathEffectDowncastN();
void ScrollViewPagePathEffectApplyToPageP();
void VTScrollViewPagePathEffectDownCastApplyToPage001();
void VTScrollViewPagePathEffectDownCastApplyToPage002();

namespace
{
  enum TEST_CASES_LIST_PAGE_TURN_VIEW
  {
    SCROLL_VIEW_PAGE_PATH_EFFECT_CONSTRUCTOR_P,
    SCROLL_VIEW_PAGE_PATH_EFFECT_NEW_P,
    SCROLL_VIEW_PAGE_PATH_EFFECT_DOWNCAST_P,
    SCROLL_VIEW_PAGE_PATH_EFFECT_DOWNCAST_N,
    SCROLL_VIEW_PAGE_PATH_EFFECT_APPLY_TO_PAGE_P,
  };

  struct ScrollViewPagePathEffect_TestApp : public ConnectionTracker
  {
    ScrollViewPagePathEffect_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ScrollViewPagePathEffect_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &ScrollViewPagePathEffect_TestApp::Tick );
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
        case SCROLL_VIEW_PAGE_PATH_EFFECT_CONSTRUCTOR_P:
          ScrollViewPagePathEffectConstructorP();
          break;

        case SCROLL_VIEW_PAGE_PATH_EFFECT_NEW_P:
          ScrollViewPagePathEffectNewP();
          break;

        case SCROLL_VIEW_PAGE_PATH_EFFECT_DOWNCAST_P:
          ScrollViewPagePathEffectDowncastP();
          break;

        case SCROLL_VIEW_PAGE_PATH_EFFECT_DOWNCAST_N:
          ScrollViewPagePathEffectDowncastN();
          break;

        case SCROLL_VIEW_PAGE_PATH_EFFECT_APPLY_TO_PAGE_P:
          ScrollViewPagePathEffectApplyToPageP();
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {

        case SCROLL_VIEW_PAGE_PATH_EFFECT_APPLY_TO_PAGE_P:
          switch(gRenderCountScrollView1)
          {
            case 0:
              VTScrollViewPagePathEffectDownCastApplyToPage001();
              gRenderCountScrollView1++;
              break;

            case 1:
              VTScrollViewPagePathEffectDownCastApplyToPage002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
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
  };

} // unnamed namespace

/**
 * ##############################
 * TC Logic Implementation Area.
 * ##############################
 **/

void ScrollViewPagePathEffectConstructorP()
{
  ScrollViewPagePathEffect patheEffect;
  DALI_CHECK_FAIL( patheEffect, "ScrollViewPagePathEffect constructor is failed." );

  DaliLog::PrintPass();
}

void ScrollViewPagePathEffectNewP()
{
  Vector2 size = Stage::GetCurrent().GetSize();
  ScrollViewPagePathEffect patheEffect;

  //Create path
  float xHalfSize( size.x * 0.5f);

  Dali::Path path = Dali::Path::New();
  Dali::Property::Array points;
  points.Resize(3);
  points[0] = Vector3( xHalfSize, 0.0f,  -xHalfSize);
  points[1] = Vector3( 0.0f, 0.0f, 0.0f );
  points[2] = Vector3( -xHalfSize, 0.0f,  -xHalfSize);
  path.SetProperty( Path::Property::POINTS, points );

  Dali::Property::Array controlPoints;
  controlPoints.Resize(4);
  controlPoints[0] = Vector3( xHalfSize, 0.0f, 0.0f );
  controlPoints[1] = Vector3( xHalfSize, 0.0f, 0.0f );
  controlPoints[2] = Vector3(-xHalfSize, 0.0f, 0.0f );
  controlPoints[3] = Vector3(-xHalfSize, 0.0f, 0.0f );
  path.SetProperty( Path::Property::CONTROL_POINTS, controlPoints );

  patheEffect = ScrollViewPagePathEffect::New(path, Vector3::ZERO, Toolkit::ScrollView::Property::SCROLL_FINAL_X, Vector3(size.x,size.y,0.0f), 3);
  DALI_CHECK_FAIL( !patheEffect, "ScrollViewPagePathEffect::New() is failed." );

  DaliLog::PrintPass();

}
void ScrollViewPagePathEffectDowncastP()
{
  Vector2 size = Stage::GetCurrent().GetSize();
  ScrollViewPagePathEffect patheEffect;

  //Create path
  float xHalfSize( size.x * 0.5f);

  Dali::Path path = Dali::Path::New();
  Dali::Property::Array points;
  points.Resize(3);
  points[0] = Vector3( xHalfSize, 0.0f,  -xHalfSize);
  points[1] = Vector3( 0.0f, 0.0f, 0.0f );
  points[2] = Vector3( -xHalfSize, 0.0f,  -xHalfSize);
  path.SetProperty( Path::Property::POINTS, points );

  Dali::Property::Array controlPoints;
  controlPoints.Resize(4);
  controlPoints[0] = Vector3( xHalfSize, 0.0f, 0.0f );
  controlPoints[1] = Vector3( xHalfSize, 0.0f, 0.0f );
  controlPoints[2] = Vector3(-xHalfSize, 0.0f, 0.0f );
  controlPoints[3] = Vector3(-xHalfSize, 0.0f, 0.0f );
  path.SetProperty( Path::Property::CONTROL_POINTS, controlPoints );

  patheEffect = ScrollViewPagePathEffect::New(path, Vector3::ZERO, Toolkit::ScrollView::Property::SCROLL_FINAL_X, Vector3(size.x,size.y,0.0f), 3);
  DALI_CHECK_FAIL( !patheEffect, "ScrollViewPagePathEffect::New() is failed." );

  ScrollViewPagePathEffect effect = ScrollViewPagePathEffect::DownCast(patheEffect);
  DALI_CHECK_FAIL( !effect, "ScrollViewPagePathEffect::DownCast() is failed." );

  DaliLog::PrintPass();
}

void ScrollViewPagePathEffectDowncastN()
{
  BaseHandle uninitializedObject;
  ScrollViewPagePathEffect scrollViewPagePathEffect1 = ScrollViewPagePathEffect::DownCast( uninitializedObject );
  DALI_CHECK_INSTANCE( !scrollViewPagePathEffect1, "ScrollViewPagePathEffect handle is not empty." );

  ScrollViewPagePathEffect scrollViewPagePathEffect2 = DownCast< ScrollViewPagePathEffect >( uninitializedObject );
  DALI_CHECK_INSTANCE( !scrollViewPagePathEffect2, "ScrollViewPagePathEffect handle is not empty after downcast." );

  DaliLog::PrintPass();
}

void ScrollViewPagePathEffectApplyToPageP()
{
  int nRow = 1, nColumn = 3;
  int nPageCount = 2;
  Vector2 size = Stage::GetCurrent().GetSize();
  ScrollViewPagePathEffect patheEffect;

  gScrollView1 = ScrollViewSetupTest1(nRow, nColumn, size);
  Actor testPage = gVecPagesActor[nPageCount];

  //Create path
  float xHalfSize( size.x * 0.5f);

  Dali::Path path = Dali::Path::New();
  Dali::Property::Array points;
  points.Resize(3);
  points[0] = Vector3( xHalfSize, 0.0f,  -xHalfSize);
  points[1] = Vector3( 0.0f, 0.0f, 0.0f );
  points[2] = Vector3( -xHalfSize, 0.0f,  -xHalfSize);
  path.SetProperty( Path::Property::POINTS, points );

  Dali::Property::Array controlPoints;
  controlPoints.Resize(4);
  controlPoints[0] = Vector3( xHalfSize, 0.0f, 0.0f );
  controlPoints[1] = Vector3( xHalfSize, 0.0f, 0.0f );
  controlPoints[2] = Vector3(-xHalfSize, 0.0f, 0.0f );
  controlPoints[3] = Vector3(-xHalfSize, 0.0f, 0.0f );
  path.SetProperty( Path::Property::CONTROL_POINTS, controlPoints );

  patheEffect = ScrollViewPagePathEffect::New(path, Vector3::ZERO, Toolkit::ScrollView::Property::SCROLL_FINAL_X, Vector3(size.x,size.y,0.0f), 3);

  DALI_CHECK_FAIL( !patheEffect, "ScrollViewPagePathEffect::New() is failed." );

  ScrollViewPagePathEffect effect = ScrollViewPagePathEffect::DownCast(patheEffect);
  DALI_CHECK_FAIL( !effect, "ScrollViewPagePathEffect::DownCast() is failed." );

  gScrollView1.ApplyEffect(effect);

  unsigned int pageCounter(0);
  for(ActorIter pageIter = gVecPagesActor.begin(); pageIter != gVecPagesActor.end(); ++pageIter)
  {
    Actor page = *pageIter;
    page.RemoveConstraints();
    Constraint constraint = Constraint::New<Vector3>( page, Actor::Property::SIZE, EqualToConstraint() );
    constraint.AddSource( ParentSource( Actor::Property::SIZE ) );
    constraint.Apply();
    try
    {
      effect.ApplyToPage(page, pageCounter++);
    }
    catch ( DaliException& de )
    {
      LOG_E( "ScrollViewPagePathEffect::ApplyToPage is failed.");
      DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception# location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
      Stage::GetCurrent().Remove( gScrollView1 );
      test_return_value = TC_FAIL;
      return;
    }
    catch(exception &e)
    {
      LOG_E( "ScrollViewPagePathEffect::ApplyToPage is failed.");
      DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Exception: %s, at [LINE: %d]", e.what(), __LINE__);
      Stage::GetCurrent().Remove(gScrollView1);
      test_return_value = TC_FAIL;
      return;
    }
  }
  gActorA1 = testPage;
}

// * ############################## Verdict test for ScrollViewPagePathEffectApplyToPage

void VTScrollViewPagePathEffectDownCastApplyToPage001()
{
  // Just, trying to scroll to page after rendering after applying effect is successfull
  gScrollView1.ScrollTo(SCROLL_DESTINATION);
}
void VTScrollViewPagePathEffectDownCastApplyToPage002()
{
  DALI_CHECK_FAIL( static_cast<int>(gScrollView1.GetCurrentPage()) != SCROLL_DESTINATION, "Failed to get desitnation page after applying path effect to page.");
  gVecPagesActor.clear();
  Stage::GetCurrent().Remove(gScrollView1);

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliScrollViewPagePathEffectConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliScrollViewPagePathEffectConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollViewPagePathEffect_TestApp testApp( application, SCROLL_VIEW_PAGE_PATH_EFFECT_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewPagePathEffectNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliScrollViewPagePathEffectNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollViewPagePathEffect_TestApp testApp( application, SCROLL_VIEW_PAGE_PATH_EFFECT_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewPagePathEffectDowncastP
 * @since_tizen         2.4
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliScrollViewPagePathEffectDowncastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollViewPagePathEffect_TestApp testApp( application, SCROLL_VIEW_PAGE_PATH_EFFECT_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewPagePathEffectDowncastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliScrollViewPagePathEffectDowncastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollViewPagePathEffect_TestApp testApp( application, SCROLL_VIEW_PAGE_PATH_EFFECT_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewPagePathEffectApplyToPageP
 * @since_tizen         2.4
 * @description         Apply the effect to page
 */

int UtcDaliScrollViewPagePathEffectApplyToPageP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollViewPagePathEffect_TestApp testApp( application, SCROLL_VIEW_PAGE_PATH_EFFECT_APPLY_TO_PAGE_P );
  application.MainLoop();

  return test_return_value;
}

