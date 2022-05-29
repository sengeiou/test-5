#include "utc-dali-object-registry-common.h"

//& set: Objectregistry
extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_ObjectRegistry_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_ObjectRegistry_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_ObjectRegistry_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_ObjectRegistry_cleanup(void)
{

}

void ObjectRegistryConstructorP();
void ObjectRegistryObjectCreatedSignalP();
void ObjectRegistryObjectDestroyedSignalP();
void ObjectRegistryOperatorAssignmentP();
void ObjectRegistryCopyConstructorP();

namespace
{
  enum TEST_CASES_LIST_OBJECT_REGISTRY
  {
    OBJECT_REGISTRY_CONSTRUCTOR_P,
    OBJECT_REGISTRY_OBJECT_CREATED_SIGNAL_P,
    OBJECT_REGISTRY_OBJECT_DESTROYED_SIGNAL_P,
    OBJECT_REGISTRY_OPERATOR_ASSIGNMENT_P,
    OBJECT_REGISTRY_COPY_CONSTRUCTOR_P
  };

  struct ObjectRegistry_TestApp : public ConnectionTracker
  {
    ObjectRegistry_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ObjectRegistry_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &ObjectRegistry_TestApp::Tick );
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
        case OBJECT_REGISTRY_OBJECT_CREATED_SIGNAL_P:
          ObjectRegistryObjectCreatedSignalP();
          break;

        case OBJECT_REGISTRY_OBJECT_DESTROYED_SIGNAL_P:
          ObjectRegistryObjectDestroyedSignalP();
          break;

        case OBJECT_REGISTRY_OPERATOR_ASSIGNMENT_P:
          ObjectRegistryOperatorAssignmentP();
          break;

        case OBJECT_REGISTRY_CONSTRUCTOR_P:
          ObjectRegistryConstructorP();
          break;

        case OBJECT_REGISTRY_COPY_CONSTRUCTOR_P:
          ObjectRegistryCopyConstructorP();
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

void ObjectRegistryObjectCreatedSignalP()
{
  bool bResult = false;

  bResult = ObjectRegistryNewHelper< Actor > ();
  DALI_CHECK_FAIL( !bResult ,  "Object creation and destroy is failed for Actor.\n" );

  bResult = false;
  bResult = ObjectRegistryNewHelper< CameraActor > ();
  DALI_CHECK_FAIL( !bResult ,  "Object creation and destroy is failed for CameraActor.\n" );

  bResult = false;
  bResult = ObjectRegistryNewHelper< ImageView > ();
  DALI_CHECK_FAIL( !bResult ,  "Object creation and destroy is failed for ImageView.\n" );

  bResult = false;
  bResult = ObjectRegistryNewHelper< Layer > ();
  DALI_CHECK_FAIL( !bResult ,  "Object creation and destroy is failed for Layer.\n" );

  DaliLog::PrintPass();
}

void ObjectRegistryObjectDestroyedSignalP()
{
  bool bResult = false;

  bResult = ObjectRegistryNewHelper< Actor > ();
  DALI_CHECK_FAIL( !bResult ,  "Object creation and destroy is failed for Actor.\n" );

  bResult = false;
  bResult = ObjectRegistryNewHelper< CameraActor > ();
  DALI_CHECK_FAIL( !bResult ,  "Object creation and destroy is failed for CameraActor.\n" );

  bResult = false;
  bResult = ObjectRegistryNewHelper< ImageView > ();
  DALI_CHECK_FAIL( !bResult ,  "Object creation and destroy is failed for ImageView.\n" );

  bResult = false;
  bResult = ObjectRegistryNewHelper< Layer > ();
  DALI_CHECK_FAIL( !bResult ,  "Object creation and destroy is failed for Layer.\n" );

  DaliLog::PrintPass();
}


void ObjectRegistryOperatorAssignmentP()
{
  unsigned int uX = 10u, uY = 10u;
  gDestroyedSignalVerified = false;
  gCreatedSignalVerified = false;

  ObjectRegistry objectRegistry;
  DALI_CHECK_FAIL( objectRegistry,  "Default ObjectRegistry is not null" );

  objectRegistry = Stage::GetCurrent().GetObjectRegistry();
  DALI_CHECK_FAIL( !objectRegistry ,  "ObjectRegistry instance is not created successfully." );

  objectRegistry.ObjectCreatedSignal().Connect( &CbObjectRegistryCreated<BufferImage> );

  ObjectRegistry objectRegistryAssigned = objectRegistry;
  DALI_CHECK_FAIL( objectRegistryAssigned != objectRegistry ,  "ObjectRegistry::operator= is failed to assign objectRegistry" );

  objectRegistryAssigned.ObjectDestroyedSignal().Connect( &CbObjectRegistryDestroyed );

  //BufferImage will be created inside the scope
  {
    BufferImage bufferImage = BufferImage::New( uX, uY );
    DALI_CHECK_FAIL( !bufferImage ,  "BufferImage::New is failed" );

    DALI_CHECK_FAIL( !gCreatedSignalVerified, "ObjectRegistry::ObjectCreatedSignal() is failed." );
  }
  //BufferImage will be destroyed outside the scope
  DALI_CHECK_FAIL( !gDestroyedSignalVerified ,  "ObjectRegistry::ObjectDestroyedSignal() is failed" );

  DaliLog::PrintPass();
}

void ObjectRegistryCopyConstructorP()
{
  gDestroyedSignalVerified = false;
  gCreatedSignalVerified = false;
  float fAnimTime = 1.0f;

  ObjectRegistry objectRegistry = Stage::GetCurrent().GetObjectRegistry();
  DALI_CHECK_FAIL( !objectRegistry ,  "ObjectRegistry instance is not created successfully." );

  objectRegistry.ObjectCreatedSignal().Connect( &CbObjectRegistryCreated<Animation> );

  ObjectRegistry objectRegistryCopy( objectRegistry );
  DALI_CHECK_FAIL( objectRegistryCopy != objectRegistry ,  "ObjectRegistry Copy Constructor is failed to copy objectRegistry" );

  objectRegistryCopy.ObjectDestroyedSignal().Connect( &CbObjectRegistryDestroyed );

  //Animation object will be created inside the scope
  {
    Animation animation = Animation::New( fAnimTime );
    DALI_CHECK_FAIL( !animation ,  "Animation::New is failed" );

    DALI_CHECK_FAIL( !gCreatedSignalVerified, "ObjectRegistry::ObjectCreatedSignal() is failed." );
  }
  //Animation object will be destroyed outside the scope
  DALI_CHECK_FAIL( !gDestroyedSignalVerified ,  "ObjectRegistry::ObjectDestroyedSignal() is failed" );

  DaliLog::PrintPass();
}

void ObjectRegistryConstructorP()
{
  ObjectRegistry objectRegistry;
  DALI_CHECK_FAIL( objectRegistry ,  "ObjectRegistry instance is not created successfully." );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase           UtcDaliObjectRegistryObjectCreatedSignalP
 * @since_tizen        2.4
 * @description        check if ObjectCreatedSignal api works or not.
 */

int UtcDaliObjectRegistryObjectCreatedSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ObjectRegistry_TestApp testApp( application, OBJECT_REGISTRY_OBJECT_CREATED_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}



/**
 * @testcase           UtcDaliObjectRegistryObjectDestroyedSignalP
 * @since_tizen        2.4
 * @description        check if ObjectDestroyedSignal api works or not.
 */

int UtcDaliObjectRegistryObjectDestroyedSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ObjectRegistry_TestApp testApp( application, OBJECT_REGISTRY_OBJECT_DESTROYED_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase           UtcDaliObjectRegistryOperatorAssignmentP
 * @since_tizen        2.4
 * @description        check if operator=() works or not.
 */

int UtcDaliObjectRegistryOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ObjectRegistry_TestApp testApp( application, OBJECT_REGISTRY_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase           UtcDaliObjectRegistryCopyConstructorP
 * @since_tizen        2.4
 * @description        check if copy constructor works or not.
 */

int UtcDaliObjectRegistryCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ObjectRegistry_TestApp testApp( application, OBJECT_REGISTRY_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase           UtcDaliObjectRegistryConstructorP
 * @since_tizen        2.4
 * @description        check if constructor works or not.
 */

int UtcDaliObjectRegistryConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ObjectRegistry_TestApp testApp( application, OBJECT_REGISTRY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}
