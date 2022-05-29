#include "utc-dali-flex-container-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;


/**
 * @function            utc_Dali_FlexContainer_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_FlexContainer_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_FlexContainer_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_FlexContainer_cleanup(void)
{

}

void FlexContainerConstructor();
void FlexContainerCopyConstructor();
void FlexContainerAlignment();
void FlexContainerChildProperty();
void FlexContainerContentDirection();
void FlexContainerDownCastP();
void FlexContainerDownCastN();
void FlexContainerFlexDirection();
void FlexContainerJustification();
void FlexContainerNew();
void FlexContainerOperatorAssignment();
void FlexContainerProperty();
void FlexContainerWrapType();

namespace
{
  const char* const PROPERTY_NAME_CONTENT_DIRECTION = "contentDirection";
  const char* const PROPERTY_NAME_FLEX_DIRECTION = "flexDirection";
  const char* const PROPERTY_NAME_FLEX_WRAP = "flexWrap";
  const char* const PROPERTY_NAME_JUSTIFY_CONTENT = "justifyContent";
  const char* const PROPERTY_NAME_ALIGN_ITEMS = "alignItems";
  const char* const PROPERTY_NAME_ALIGN_CONTENT =  "alignContent";
  const char* const CHILD_PROPERTY_NAME_FLEX = "flex";
  const char* const CHILD_PROPERTY_NAME_ALIGN_SELF = "alignSelf";
  const char* const CHILD_PROPERTY_NAME_FLEX_MARGIN =  "flexMargin";

  enum TEST_CASES_LIST_STYLE_MANAGER
  {
    FLEX_CONTAINER_CONSTRUCTOR_P,
    FLEX_CONTAINER_COPY_CONSTRUCTOR_P,
    FLEX_CONTAINER_ALIGNMENT_P,
    FLEX_CONTAINER_CHILD_PROPERTY_P,
    FLEX_CONTAINER_CONTENT_DIRECTION_P,
    FLEX_CONTAINER_DOWNCAST_P,
    FLEX_CONTAINER_DOWNCAST_N,
    FLEX_CONTAINER_FLEX_DIRECTION_P,
    FLEX_CONTAINER_JUSTIFICATION_P,
    FLEX_CONTAINER_NEW_P,
    FLEX_CONTAINER_OPERATOR_ASSIGNMENT_P,
    FLEX_CONTAINER_PROPERTY_P,
    FLEX_CONTAINER_WRAP_TYPE_P
  };

  struct FlexContainer_TestApp : public ConnectionTracker
  {
    FlexContainer_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &FlexContainer_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &FlexContainer_TestApp::Tick );
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

        case FLEX_CONTAINER_CONSTRUCTOR_P:
          FlexContainerConstructor();
          break;

        case FLEX_CONTAINER_COPY_CONSTRUCTOR_P:
          FlexContainerCopyConstructor();
          break;

        case FLEX_CONTAINER_ALIGNMENT_P:
          FlexContainerAlignment();
          break;

        case FLEX_CONTAINER_CHILD_PROPERTY_P:
          FlexContainerChildProperty();
          break;

        case FLEX_CONTAINER_CONTENT_DIRECTION_P:
          FlexContainerContentDirection();
          break;

        case FLEX_CONTAINER_DOWNCAST_P:
          FlexContainerDownCastP();
          break;

        case FLEX_CONTAINER_DOWNCAST_N:
          FlexContainerDownCastN();
          break;

        case FLEX_CONTAINER_JUSTIFICATION_P:
          FlexContainerJustification();
          break;

        case FLEX_CONTAINER_FLEX_DIRECTION_P:
          FlexContainerFlexDirection();
          break;

        case FLEX_CONTAINER_NEW_P:
          FlexContainerNew();
          break;

        case FLEX_CONTAINER_OPERATOR_ASSIGNMENT_P:
          FlexContainerOperatorAssignment();
          break;

        case FLEX_CONTAINER_PROPERTY_P:
          FlexContainerProperty();
          break;

        case FLEX_CONTAINER_WRAP_TYPE_P:
          FlexContainerWrapType();
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

void FlexContainerConstructor()
{
  FlexContainer flexContainer;
  DALI_CHECK_FAIL( flexContainer, "Flex Container Constructor failed" );

  DaliLog::PrintPass();
}

void FlexContainerCopyConstructor()
{
  FlexContainer flexContainer = FlexContainer::New();
  flexContainer.SetProperty( FlexContainer::Property::FLEX_DIRECTION, FlexContainer::ROW_REVERSE );

  FlexContainer copy( flexContainer );
  DALI_CHECK_FAIL( !copy, "Flex Container Constructor failed"  );
  DALI_CHECK_FAIL( copy.GetProperty<int>( FlexContainer::Property::FLEX_DIRECTION ) != flexContainer.GetProperty<int>( FlexContainer::Property::FLEX_DIRECTION ), "Flex Container Copy Constructor Property failed"  );

  DaliLog::PrintPass();
}

void FlexContainerAlignment()
{
  FlexContainer flexContainer = FlexContainer::New();
  DALI_CHECK_FAIL( !flexContainer, "Flex Container New failed"  );
  // Add flex container to the stage
  Stage::GetCurrent().Add( flexContainer );

  // Create two actors and add them to the container
  Actor actor1 = Actor::New();
  Actor actor2 = Actor::New();
  DALI_CHECK_FAIL( !actor1, "Actor initialization failed" );
  DALI_CHECK_FAIL( !actor2, "Actor initialization failed" );

  flexContainer.Add(actor1);
  flexContainer.Add(actor2);

  // Check align items property.
  flexContainer.SetProperty( FlexContainer::Property::ALIGN_ITEMS, FlexContainer::ALIGN_FLEX_START );
  DALI_CHECK_FAIL( (FlexContainer::Alignment)flexContainer.GetProperty<int>( FlexContainer::Property::ALIGN_ITEMS ) !=  FlexContainer::ALIGN_FLEX_START, "Alignment Property failed" );

  // Check align content property.
  flexContainer.SetProperty( FlexContainer::Property::ALIGN_CONTENT, FlexContainer::ALIGN_STRETCH );
  DALI_CHECK_FAIL( (FlexContainer::Alignment)flexContainer.GetProperty<int>( FlexContainer::Property::ALIGN_CONTENT ) != FlexContainer::ALIGN_STRETCH, "Alignment Property failed" );

  DaliLog::PrintPass();
}

void FlexContainerChildProperty()
{
  FlexContainer flexContainer = FlexContainer::New();
  DALI_CHECK_FAIL( !flexContainer, "Flex Container New failed" );

  // Add flex container to the stage
  Stage::GetCurrent().Add( flexContainer );

  // Create an actor and add it to the container
  Actor actor = Actor::New();
  DALI_CHECK_FAIL( !actor, "Actor failed" );

  flexContainer.Add(actor);

  // Check flex child property.
  actor.SetProperty( FlexContainer::ChildProperty::FLEX, 2.0f );
  DALI_CHECK_FAIL( (actor.GetProperty<float>( FlexContainer::ChildProperty::FLEX )) != 2.0f, "Flex Container GetProperty failed" );
  DALI_CHECK_FAIL( actor.GetPropertyIndex( CHILD_PROPERTY_NAME_FLEX ) != FlexContainer::ChildProperty::FLEX, "Flex Container GetPropertyIndex failed" );

  // Check align self child property.
  actor.SetProperty( FlexContainer::ChildProperty::ALIGN_SELF, FlexContainer::ALIGN_FLEX_END );
  DALI_CHECK_FAIL( (FlexContainer::Alignment)actor.GetProperty<int>( FlexContainer::ChildProperty::ALIGN_SELF ) != FlexContainer::ALIGN_FLEX_END, "Flex Container GetProperty failed" );
  DALI_CHECK_FAIL( actor.GetPropertyIndex( CHILD_PROPERTY_NAME_ALIGN_SELF ) != FlexContainer::ChildProperty::ALIGN_SELF, "Flex Container GetPropertyIndex failed" );

  // Check flex margin child property.
  actor.SetProperty( FlexContainer::ChildProperty::FLEX_MARGIN, Vector4( 10.0f, 10.0f, 10.0f, 10.0f ) );
  DALI_CHECK_FAIL( actor.GetProperty<Vector4>( FlexContainer::ChildProperty::FLEX_MARGIN ) != Vector4( 10.0f, 10.0f, 10.0f, 10.0f ), "Flex Container GetProperty failed" );
  DALI_CHECK_FAIL( actor.GetPropertyIndex( CHILD_PROPERTY_NAME_FLEX_MARGIN ) != FlexContainer::ChildProperty::FLEX_MARGIN, "Flex Container GetPropertyIndex failed" );

  DaliLog::PrintPass();
}

void FlexContainerContentDirection()
{
  FlexContainer flexContainer = FlexContainer::New();
  DALI_CHECK_FAIL( !flexContainer, "Flex Container New failed"  );
  // Add flex container to the stage
  Stage::GetCurrent().Add( flexContainer );

  // Create two actors and add them to the container
  Actor actor1 = Actor::New();
  Actor actor2 = Actor::New();
  DALI_CHECK_FAIL( !actor1, "Actor initialization failed" );
  DALI_CHECK_FAIL( !actor2, "Actor initialization failed" );

  flexContainer.Add(actor1);
  flexContainer.Add(actor2);

  // Check content direction property
  flexContainer.SetProperty( FlexContainer::Property::CONTENT_DIRECTION, FlexContainer::RTL );
  DALI_CHECK_FAIL( (FlexContainer::ContentDirection)flexContainer.GetProperty<int>( FlexContainer::Property::CONTENT_DIRECTION ) != FlexContainer::RTL, "ContentDirection Property failed" );

  DaliLog::PrintPass();
}

void FlexContainerDownCastP()
{
  FlexContainer flexContainer1 = FlexContainer::New();
  BaseHandle object( flexContainer1 );

  FlexContainer flexContainer2 = FlexContainer::DownCast( object );
  DALI_CHECK_FAIL( !flexContainer2, "Flex Container failed"  );

  FlexContainer flexContainer3 = DownCast< FlexContainer >( object );
  DALI_CHECK_FAIL( !flexContainer3, "Flex Container failed" );

  DaliLog::PrintPass();
}

void FlexContainerDownCastN()
{
  BaseHandle uninitializedObject;
  FlexContainer flexContainer1 = FlexContainer::DownCast( uninitializedObject );
  DALI_CHECK_FAIL( flexContainer1, "Flex Container failed" );

  FlexContainer flexContainer2 = DownCast< FlexContainer >( uninitializedObject );
  DALI_CHECK_FAIL( flexContainer2, "Flex Container failed" );

  DaliLog::PrintPass();
}

void FlexContainerFlexDirection()
{
  FlexContainer flexContainer = FlexContainer::New();
  DALI_CHECK_FAIL( !flexContainer, "Flex Container New failed"  );
  // Add flex container to the stage
  Stage::GetCurrent().Add( flexContainer );

  // Create two actors and add them to the container
  Actor actor1 = Actor::New();
  Actor actor2 = Actor::New();
  DALI_CHECK_FAIL( !actor1, "Actor initialization failed" );
  DALI_CHECK_FAIL( !actor2, "Actor initialization failed" );

  flexContainer.Add(actor1);
  flexContainer.Add(actor2);

  // Check flex direction property.
  flexContainer.SetProperty( FlexContainer::Property::FLEX_DIRECTION, FlexContainer::COLUMN_REVERSE );
  DALI_CHECK_FAIL( (FlexContainer::FlexDirection)flexContainer.GetProperty<int>( FlexContainer::Property::FLEX_DIRECTION ) !=  FlexContainer::COLUMN_REVERSE, "FlexDirection Property failed" );

  DaliLog::PrintPass();
}

void FlexContainerJustification()
{
  FlexContainer flexContainer = FlexContainer::New();
  DALI_CHECK_FAIL( !flexContainer, "Flex Container New failed"  );
  // Add flex container to the stage
  Stage::GetCurrent().Add( flexContainer );

  // Create two actors and add them to the container
  Actor actor1 = Actor::New();
  Actor actor2 = Actor::New();
  DALI_CHECK_FAIL( !actor1, "Actor initialization failed" );
  DALI_CHECK_FAIL( !actor2, "Actor initialization failed" );

  flexContainer.Add(actor1);
  flexContainer.Add(actor2);

  // Check justify content property.
  flexContainer.SetProperty( FlexContainer::Property::JUSTIFY_CONTENT, FlexContainer::JUSTIFY_SPACE_BETWEEN );
  DALI_CHECK_FAIL( (FlexContainer::Justification)flexContainer.GetProperty<int>( FlexContainer::Property::JUSTIFY_CONTENT ) !=  FlexContainer::JUSTIFY_SPACE_BETWEEN, "Actor Justification Property failed" );

  DaliLog::PrintPass();
}

void FlexContainerNew()
{
  FlexContainer flexContainer = FlexContainer::New();
  DALI_CHECK_FAIL( !flexContainer, "Flex Container New failed" );

  DaliLog::PrintPass();
}

void FlexContainerOperatorAssignment()
{
  FlexContainer flexContainer = FlexContainer::New();
  flexContainer.SetProperty( FlexContainer::Property::FLEX_DIRECTION, FlexContainer::ROW_REVERSE );

  FlexContainer copy = flexContainer;
  DALI_CHECK_FAIL( !copy, "Flex Container Copy Constructor failed" );
  DALI_CHECK_FAIL( copy.GetProperty<int>( FlexContainer::Property::FLEX_DIRECTION ) != flexContainer.GetProperty<int>( FlexContainer::Property::FLEX_DIRECTION ), "Flex Container Copy Constructor failed"  );

  DaliLog::PrintPass();
}

void FlexContainerProperty()
{
  FlexContainer flexContainer = FlexContainer::New();
  DALI_CHECK_FAIL( !flexContainer, "Flex Container New failed"  );

  // Check Property Indices are correct
  DALI_CHECK_FAIL( flexContainer.GetPropertyIndex( PROPERTY_NAME_CONTENT_DIRECTION ) != FlexContainer::Property::CONTENT_DIRECTION, "FlexContainer Get Property Failed" );
  DALI_CHECK_FAIL( flexContainer.GetPropertyIndex( PROPERTY_NAME_FLEX_DIRECTION ) != FlexContainer::Property::FLEX_DIRECTION, "FlexContainer Get Property Failed" );
  DALI_CHECK_FAIL( flexContainer.GetPropertyIndex( PROPERTY_NAME_FLEX_WRAP ) != FlexContainer::Property::FLEX_WRAP, "FlexContainer Get Property Failed" );
  DALI_CHECK_FAIL( flexContainer.GetPropertyIndex( PROPERTY_NAME_JUSTIFY_CONTENT ) != FlexContainer::Property::JUSTIFY_CONTENT, "FlexContainer Get Property Failed");
  DALI_CHECK_FAIL( flexContainer.GetPropertyIndex( PROPERTY_NAME_ALIGN_ITEMS ) != FlexContainer::Property::ALIGN_ITEMS, "FlexContainer Get Property Failed" );
  DALI_CHECK_FAIL( flexContainer.GetPropertyIndex( PROPERTY_NAME_ALIGN_CONTENT ) != FlexContainer::Property::ALIGN_CONTENT, "FlexContainer Get Property Failed" );

  DaliLog::PrintPass();
}

void FlexContainerWrapType()
{
  FlexContainer flexContainer = FlexContainer::New();
  DALI_CHECK_FAIL( !flexContainer, "Flex Container New failed"  );
  // Add flex container to the stage
  Stage::GetCurrent().Add( flexContainer );

  // Create two actors and add them to the container
  Actor actor1 = Actor::New();
  Actor actor2 = Actor::New();
  DALI_CHECK_FAIL( !actor1, "Actor initialization failed" );
  DALI_CHECK_FAIL( !actor2, "Actor initialization failed" );

  flexContainer.Add(actor1);
  flexContainer.Add(actor2);

  // Check flex wrap property.
  flexContainer.SetProperty( FlexContainer::Property::FLEX_WRAP, FlexContainer::WRAP );
  DALI_CHECK_FAIL( (FlexContainer::WrapType)flexContainer.GetProperty<int>( FlexContainer::Property::FLEX_WRAP ) != FlexContainer::WRAP, "Set Property failed" );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase                 UtcDaliFlexContainerConstructorP
 * @since_tizen              2.4
 * @description              Constructor to FlexContainer
 */
int UtcDaliFlexContainerConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliFlexContainerCopyConstructorP
 * @since_tizen              2.4
 * @description              Copy constructor to FlexContainer
 */

int UtcDaliFlexContainerCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_COPY_CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliFlexContainerAlignmentP
 * @since_tizen              2.4
 * @description              Tests Flex Container GetAlignment
 */

int UtcDaliFlexContainerAlignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_ALIGNMENT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliFlexContainerChildPropertyP
 * @since_tizen              2.4
 * @description              Tests Flex Container ChildProperty
 */

int UtcDaliFlexContainerChildPropertyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_CHILD_PROPERTY_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliFlexContainerContentDirectionP
 * @since_tizen              2.4
 * @description              Test Flex Container ContentDirection
 */

int UtcDaliFlexContainerContentDirectionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_CONTENT_DIRECTION_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliFlexContainerDownCastP
 * @since_tizen              2.4
 * @description              Test FlexContainer DownCast Positive.
 */

int UtcDaliFlexContainerDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_DOWNCAST_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliFlexContainerDownCastN
 * @since_tizen              2.4
 * @description              Test FlexContainer DownCast Negative.
 */

int UtcDaliFlexContainerDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_DOWNCAST_N);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliFlexContainerFlexDirectionP
 * @since_tizen              2.4
 * @description              Test FlexContainer FlexDirection.
 */

int UtcDaliFlexContainerFlexDirectionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_FLEX_DIRECTION_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliFlexContainerJustificationP
 * @since_tizen              2.4
 * @description              Test FlexContainer Justification.
 */

int UtcDaliFlexContainerJustificationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_JUSTIFICATION_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliFlexContainerNewP
 * @since_tizen              2.4
 * @description              Test FlexContainer New.
 */

int UtcDaliFlexContainerNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_NEW_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliFlexContainerOperatorAssignmentP
 * @since_tizen              2.4
 * @description              Test FlexContainer OperatorAssignment.
 */

int UtcDaliFlexContainerOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliFlexContainerPropertyP
 * @since_tizen              2.4
 * @description              Test FlexContainer Property.
 */

int UtcDaliFlexContainerPropertyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_PROPERTY_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliFlexContainerWrapTypeP
 * @since_tizen              2.4
 * @description              Test FlexContainer WrapType.
 */

int UtcDaliFlexContainerWrapTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FlexContainer_TestApp testApp( application, FLEX_CONTAINER_WRAP_TYPE_P);
  application.MainLoop();

  return test_return_value;
}
