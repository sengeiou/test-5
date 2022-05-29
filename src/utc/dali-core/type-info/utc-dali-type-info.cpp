#include "utc-dali-type-info-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_TypeInfo_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_TypeInfo_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_TypeInfo_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_TypeInfo_cleanup(void)
{

}


static string strSignalOne = "sig1";
static string strSignalTwo = "sig2";
static string strActionOne = "act1";
static const int TEST_ACTION_COUNT = 1;
static const int TEST_SIGNAL_COUNT = 2;
bool bGetCreatorCreateCustomNamedInitCalled = false ;
static string strLastSignalConnectionCustom = "";
static string strLastActionCustom = "";
bool bSetPropertyCalled = false;
bool bGetPropertyCalled = false;
/*******************************************************************************
 *
 * Custom Actor
 *
 ******************************************************************************/
namespace ImplMine
{
  struct MyTestCustomActor : public CustomActorImpl
  {
    typedef Signal< void ()> SignalType;
    typedef Signal< void (float)> SignalTypeFloat;

    MyTestCustomActor() : CustomActorImpl( ActorFlags( REQUIRES_TOUCH_EVENTS ) )
    { }

    virtual ~MyTestCustomActor()
    { }

    void ResetCallStack()
    {
    }

    // From CustomActorImpl
    virtual void OnStageConnection( int nDepth )
    {
    }
    virtual void OnStageDisconnection()
    {
    }
    virtual void OnChildAdd(Actor& child)
    {
    }
    virtual void OnChildRemove(Actor& child)
    {
    }
    virtual void OnSizeSet(const Vector3& targetSize)
    {
    }
    virtual void OnSizeAnimation(Animation& animation, const Vector3& targetSize)
    {
    }
    virtual bool OnTouchEvent(const TouchEvent& event)
    {
      return true;
    }
    virtual bool OnHoverEvent(const HoverEvent& event)
    {
      return true;
    }
    virtual bool OnWheelEvent(const WheelEvent& event)
    {
      return true;
    }
    virtual bool OnKeyEvent(const KeyEvent& event)
    {
      return true;
    }
    virtual void OnKeyInputFocusGained()
    {
    }
    virtual void OnKeyInputFocusLost()
    {
    }
    virtual Vector3 GetNaturalSize()
    {
      return Vector3( 0.0f, 0.0f, 0.0f );
    }

    virtual float GetHeightForWidth( float width )
    {
      return 0.0f;
    }

    virtual float GetWidthForHeight( float height )
    {
      return 0.0f;
    }

    virtual void OnRelayout( const Vector2& size, RelayoutContainer& container )
    {
    }

    virtual void OnSetResizePolicy( ResizePolicy::Type policy, Dimension::Type dimension )
    {
    }

    virtual void OnCalculateRelayoutSize( Dimension::Type dimension )
    {
    }

    virtual float CalculateChildSize( const Dali::Actor& child, Dimension::Type dimension )
    {
      return 0.0f;
    }

    virtual void OnLayoutNegotiated( float size, Dimension::Type dimension )
    {
    }

    virtual bool RelayoutDependentOnChildren( Dimension::Type dimension = Dimension::ALL_DIMENSIONS )
    {
      return false;
    }

    public:

    SignalType mSignal;
  };

}; // namespace Impl

class MyTestCustomActor : public CustomActor
{
  public:

    typedef Signal< void ()> SignalType;
    typedef Signal< void (float)> SignalTypeFloat;

    MyTestCustomActor()
    {
    }

    static MyTestCustomActor New()
    {
      ImplMine::MyTestCustomActor* p = new ImplMine::MyTestCustomActor;
      return MyTestCustomActor( *p ); // takes ownership
    }

    virtual ~MyTestCustomActor()
    {
    }

    static MyTestCustomActor DownCast( BaseHandle handle )
    {
      MyTestCustomActor result;

      CustomActor custom = Dali::CustomActor::DownCast( handle );
      if ( custom )
      {
        CustomActorImpl& customImpl = custom.GetImplementation();

        ImplMine::MyTestCustomActor* impl = dynamic_cast<ImplMine::MyTestCustomActor*>(&customImpl);

        if (impl)
        {
          result = MyTestCustomActor(customImpl.GetOwner());
        }
      }

      return result;
    }

    SignalType& GetCustomSignal()
    {
      Dali::RefObject& obj = GetImplementation();
      return static_cast<ImplMine::MyTestCustomActor&>( obj ).mSignal;
    }

  private:

    MyTestCustomActor(Internal::CustomActor* internal)
      : CustomActor(internal)
    {
    }

    MyTestCustomActor( ImplMine::MyTestCustomActor& impl )
      : CustomActor( impl )
    {
    }
};


class MyTestCustomActor2 : public CustomActor
{
  public:

    MyTestCustomActor2()
    {
    }

    static MyTestCustomActor2 New()
    {
      return MyTestCustomActor2(); // takes ownership
    }

    virtual ~MyTestCustomActor2()
    {
    }

    static MyTestCustomActor2 DownCast( BaseHandle handle )
    {
      MyTestCustomActor2 result;

      CustomActor custom = Dali::CustomActor::DownCast( handle );
      if ( custom )
      {
        CustomActorImpl& customImpl = custom.GetImplementation();

        ImplMine::MyTestCustomActor* impl = dynamic_cast<ImplMine::MyTestCustomActor*>(&customImpl);

        if (impl)
        {
          result = MyTestCustomActor2(customImpl.GetOwner());
        }
      }

      return result;
    }

  private:

    MyTestCustomActor2(Internal::CustomActor* internal)
      : CustomActor(internal)
    {
    }

    MyTestCustomActor2( ImplMine::MyTestCustomActor& impl )
      : CustomActor( impl )
    {
    }
};



BaseHandle GetCreatorCreateFunction(void)
{
  bGetCreatorCreateCustomNamedInitCalled = true;
  LOG_I("GetCreatorCreateFunction is called.");
  return BaseHandle();
}


BaseHandle CreateCustom(void)
{
  LOG_I("CreateCustom is called.");
  return MyTestCustomActor::New();
}


bool DoActionCustom(BaseObject* object, const std::string& actionName, const Property::Map& attributes)
{
  LOG_I("DoActionCustom is called.");
  strLastActionCustom = actionName;
  return true;
}
bool DoConnectSignalCustomFailure( BaseObject* object, ConnectionTrackerInterface* tracker, const std::string& signalName, FunctorDelegate* functor )
{
  LOG_I("DoConnectSignalCustomFailure is called.");
  strLastSignalConnectionCustom = "failed";
  return false;
}
// Custom type registration
static TypeRegistration customType( typeid(MyTestCustomActor), typeid(Dali::CustomActor), CreateCustom, false );
bool DoConnectSignalCustom( BaseObject* object, ConnectionTrackerInterface* tracker, const std::string& signalName, FunctorDelegate* functor )
{
  LOG_I("DoConnectSignalCustom is called.");
  strLastSignalConnectionCustom = signalName;
  bool bConnected( true );
  Dali::BaseHandle handle(object);
  MyTestCustomActor customActor = MyTestCustomActor::DownCast(handle);

  if( strSignalOne == signalName )
  {
    customActor.GetCustomSignal().Connect( tracker, functor );
  }
  else
  {
    // signalName does not match any signal
    bConnected = false;
  }
  return bConnected;
}
// Custom signals
static SignalConnectorType customSignalConnector1( customType, strSignalOne, DoConnectSignalCustom );
static SignalConnectorType customSignalConnector2( customType, strSignalTwo, DoConnectSignalCustomFailure );

// Property Registration
void TypeSetProperty( BaseObject* object, Property::Index propertyIndex, const Property::Value& value )
{
  LOG_I("TypeSetProperty is called.");
  bSetPropertyCalled = true;
}
Property::Value TypeGetPropertyTypeInfo( BaseObject* object, Property::Index propertyIndex )
{
  LOG_I("GetProperty is called.");
  bGetPropertyCalled = true;
  return Property::Value( true );
}


void TypeInfoConstructor();
void TypeInfoCopyConstructor();
void TypeInfoOperatorAssignment();
void TypeInfoGetName();
void TypeInfoGetBaseName();
void TypeInfoCreateInstance();
void TypeInfoGetCreator();
void TypeInfoGetActionCount();
void TypeInfoGetActionName();
void TypeInfoGetSignalCount();
void TypeInfoGetSignalName();
void TypeInfoGetPropertyCount();
void TypeInfoGetPropertyIndices();
void TypeInfoGetPropertyName();
void TypeInfoGetChildProperties01();
void TypeInfoGetChildProperties02();

namespace
{
  enum TEST_CASES_LIST_TYPE_INFO
  {
    TYPE_INFO_CONSTRUCTOR,
    TYPE_INFO_COPY_CONSTRUCTOR,
    TYPE_INFO_OPERATOR_ASSIGNMENT,
    TYPE_INFO_GET_NAME,
    TYPE_INFO_GET_BASE_NAME,
    TYPE_INFO_CREATE_INSTANCE,
    TYPE_INFO_GET_CREATOR,
    TYPE_INFO_GET_ACTION_COUNT,
    TYPE_INFO_GET_ACTION_NAME,
    TYPE_INFO_GET_SIGNAL_COUNT,
    TYPE_INFO_GET_SIGNAL_NAME,
    TYPE_INFO_GET_PROPERTY_COUNT,
    TYPE_INFO_GET_PROPERTY_INDICES,
    TYPE_INFO_GET_PROPERTY_NAME,
    TYPE_INFO_GET_CHILD_PROPERTIES_01,
    TYPE_INFO_GET_CHILD_PROPERTIES_02
  };

  struct Type_Info_TestApp : public ConnectionTracker
  {
    Type_Info_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Type_Info_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Type_Info_TestApp::Tick );
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

        case TYPE_INFO_CONSTRUCTOR:
          TypeInfoConstructor();
          break;

        case TYPE_INFO_COPY_CONSTRUCTOR:
          TypeInfoCopyConstructor();
          break;

        case TYPE_INFO_OPERATOR_ASSIGNMENT:
          TypeInfoOperatorAssignment();
          break;

        case TYPE_INFO_GET_NAME:
          TypeInfoGetName();
          break;

        case TYPE_INFO_GET_BASE_NAME:
          TypeInfoGetBaseName();
          break;

        case TYPE_INFO_CREATE_INSTANCE:
          TypeInfoCreateInstance();
          break;

        case TYPE_INFO_GET_CREATOR:
          TypeInfoGetCreator();
          break;

        case TYPE_INFO_GET_ACTION_COUNT:
          TypeInfoGetActionCount();
          break;

        case TYPE_INFO_GET_ACTION_NAME:
          TypeInfoGetActionName();
          break;

        case TYPE_INFO_GET_SIGNAL_COUNT:
          TypeInfoGetSignalCount();
          break;

        case TYPE_INFO_GET_SIGNAL_NAME:
          TypeInfoGetSignalName();
          break;

        case TYPE_INFO_GET_PROPERTY_COUNT:
          TypeInfoGetPropertyCount();
          break;

        case TYPE_INFO_GET_PROPERTY_INDICES:
          TypeInfoGetPropertyIndices();
          break;

        case TYPE_INFO_GET_PROPERTY_NAME:
          TypeInfoGetPropertyName();
          break;
        case TYPE_INFO_GET_CHILD_PROPERTIES_01:
          TypeInfoGetChildProperties01();
          break;
        case TYPE_INFO_GET_CHILD_PROPERTIES_02:
          TypeInfoGetChildProperties02();
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

void TypeInfoConstructor()
{
  const string STRTYPE    = "Actor";

  TypeRegistry typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");

  TypeInfo typeInfo = typeRegistry.GetTypeInfo(STRTYPE);
  DALI_CHECK_FAIL(!typeInfo,  "GetTypeInfo is failed to retrive the value.");

  DaliLog::PrintPass();
}

void TypeInfoCopyConstructor()
{
  const string STRTYPE    = "Actor";

  TypeRegistry typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");

  TypeInfo typeInfo = typeRegistry.GetTypeInfo(STRTYPE);
  DALI_CHECK_FAIL(!typeInfo,  "GetTypeInfo is failed to retrive the value.");

  TypeRegistry typeRegistryCopy(typeRegistry);
  DALI_CHECK_FAIL(!typeRegistryCopy,  "TypeRegistry::Consturctor is failed.");

  TypeInfo typeInfoCopy = typeRegistryCopy.GetTypeInfo(STRTYPE);
  DALI_CHECK_FAIL(!typeInfoCopy,  "GetTypeInfo is failed to retrive the value.");

  DALI_CHECK_FAIL(typeInfo != typeInfoCopy,  "GetTypeInfo is not same as expected.");

  DaliLog::PrintPass();
}

void TypeInfoOperatorAssignment()
{
  const string STRTYPE    = "Actor";

  TypeRegistry typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");

  TypeInfo typeInfo = typeRegistry.GetTypeInfo(STRTYPE);
  DALI_CHECK_FAIL(!typeInfo,  "GetTypeInfo is failed to retrive the value.");

  TypeInfo typeInfoAssigned = typeInfo;
  DALI_CHECK_FAIL(!typeInfoAssigned || (typeInfoAssigned != typeInfo),  "TypeInfo::operator=(Dali::TypeInfo const&) is failed.");

  DaliLog::PrintPass();
}

void TypeInfoGetName()
{
  const string STRTYPE    = "Actor";
  string strTypeGet = "" , strTypeCheck ;

  TypeInfo typeinfo_Type_Get = TypeRegistry::Get().GetTypeInfo( typeid(Dali::Actor) );
  strTypeCheck = typeinfo_Type_Get.GetName();

  TypeRegistry typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");
  TypeInfo typeInfo = typeRegistry.GetTypeInfo(STRTYPE);
  DALI_CHECK_FAIL(!typeInfo,  "GetTypeInfo is failed to retrive the value.");
  strTypeGet = typeInfo.GetName();

  DALI_CHECK_FAIL(strTypeGet != strTypeCheck,  "GetName is failed to match with the expected value.");

  DaliLog::PrintPass();
}

void TypeInfoGetBaseName()
{
  const string STRTYPE    = "Actor";
  string strTypeGet = "" , strTypeCheck ;

  TypeInfo typeinfo_Type_Get = TypeRegistry::Get().GetTypeInfo( typeid(Dali::Actor) );
  strTypeCheck = typeinfo_Type_Get.GetBaseName();

  TypeRegistry typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");
  TypeInfo typeInfo = typeRegistry.GetTypeInfo(STRTYPE);
  DALI_CHECK_FAIL(!typeInfo,  "GetTypeInfo is failed to retrive the value.");
  strTypeGet = typeInfo.GetBaseName();

  DALI_CHECK_FAIL(strTypeGet != strTypeCheck,  "GetBaseName is failed to match with the expected value.");

  DaliLog::PrintPass();
}

void TypeInfoCreateInstance()
{
  TypeInfo typeInfo = TypeRegistry::Get().GetTypeInfo( typeid(Dali::Actor) );
  DALI_CHECK_FAIL(!typeInfo,  "TypeRegistry::Get() is failed.");
  DALI_CHECK_FAIL(!typeInfo.GetCreator(),  "GetCreator is failed to create valid CreateFunction.");
  BaseHandle handle = typeInfo.CreateInstance();
  DALI_CHECK_FAIL(!handle,  "CreateInstance is failed to create valid handle.");
  Actor actor = Actor::DownCast(handle);
  DALI_CHECK_FAIL(!actor,  "Actor Downcast is failed to get valid handle from the handle get by CreateInstance().");

  Stage::GetCurrent().Add( actor );

  DaliLog::PrintPass();
}

void TypeInfoGetCreator()
{
  TypeInfo typeInfo = TypeRegistry::Get().GetTypeInfo( typeid(Dali::Actor) );
  DALI_CHECK_FAIL(!typeInfo,  "TypeRegistry::Get() is failed.");
  DALI_CHECK_FAIL(!typeInfo.GetCreator(),  "GetCreator is failed to create valid CreateFunction.");
  BaseHandle handle = typeInfo.CreateInstance();
  DALI_CHECK_FAIL(!handle,  "CreateInstance is failed to create valid handle.");
  Actor actor = Actor::DownCast(handle);
  DALI_CHECK_FAIL(!actor,  "Actor Downcast is failed to get valid handle from the handle get by CreateInstance().");

  Stage::GetCurrent().Add( actor );

  DaliLog::PrintPass();
}

void TypeInfoGetActionCount()
{
  const string UNIQUETYPENAME = "MyTestCustomActor" ;
  const string UNIQUETYPENAMECUSTOM = "CustomActor" ;

  TypeInfo type = TypeRegistry::Get().GetTypeInfo( UNIQUETYPENAME  );
  DALI_CHECK_FAIL(!type,  "TypeRegistry failed to get the typeInfo name .");

  TypeInfo baseType = TypeRegistry::Get().GetTypeInfo( UNIQUETYPENAMECUSTOM );
  DALI_CHECK_FAIL(!baseType,  "TypeRegistry failed to get the typeInfo name .");

  BaseHandle handle = type.CreateInstance();
  DALI_CHECK_FAIL(!handle,  "CreateInstance failed to return the  basehandle .");

  TypeAction customAction( customType, strActionOne, DoActionCustom);
  MyTestCustomActor customHandle = MyTestCustomActor::DownCast( handle );
  DALI_CHECK_FAIL(!customHandle,  "MyTestCustomActor failed to return the  valid handle with downcast .");

  size_t actionCount = type.GetActionCount();
  size_t baseActionCount = baseType.GetActionCount();
  DALI_CHECK_FAIL(actionCount != TEST_ACTION_COUNT + baseActionCount, "GetActionCount of basetype is not match with child type GetActionCount value .");

  DaliLog::PrintPass();
}

void TypeInfoGetActionName()
{
  const string UNIQUETYPENAME = "MyTestCustomActor" ;
  const string UNIQUETYPENAMECUSTOM = "CustomActor" ;
  const unsigned int FIRST_INDEX = 0u;

  TypeInfo type = TypeRegistry::Get().GetTypeInfo( UNIQUETYPENAME  );
  DALI_CHECK_FAIL(!type,  "TypeRegistry failed to get the typeInfo name .");

  TypeAction customAction( customType, strActionOne, DoActionCustom);

  DALI_CHECK_FAIL( type.GetActionName(FIRST_INDEX) != strActionOne, "TypeInfo::GetActionName is failed." );

  DaliLog::PrintPass();
}

void TypeInfoGetSignalCount()
{
  const string UNIQUETYPENAME = "MyTestCustomActor" ;
  const string UNIQUETYPENAMECUSTOM = "CustomActor" ;

  TypeInfo type = TypeRegistry::Get().GetTypeInfo( UNIQUETYPENAME  );
  DALI_CHECK_FAIL(!type,  "TypeRegistry failed to get the typeInfo name .");

  TypeInfo baseType = TypeRegistry::Get().GetTypeInfo( UNIQUETYPENAMECUSTOM );
  DALI_CHECK_FAIL(!baseType,  "TypeRegistry failed to get the typeInfo name .");

  BaseHandle handle = type.CreateInstance();
  DALI_CHECK_FAIL(!handle,  "CreateInstance failed to return the  basehandle .");

  //size_t signalCount = type.GetSignalCount();
  //size_t baseSignalCount = baseType.GetSignalCount();
  //DALI_CHECK_FAIL(signalCount != TEST_SIGNAL_COUNT + baseSignalCount, "GetSignalCount of basetype is not match with child type GetSignalCount value .");

  DaliLog::PrintPass();
}

void TypeInfoGetSignalName()
{
  const string UNIQUETYPENAME = "MyTestCustomActor" ;
  const string UNIQUETYPENAMECUSTOM = "CustomActor" ;
  //const unsigned int FIRST_INDEX = 0u;

  TypeInfo type = TypeRegistry::Get().GetTypeInfo( UNIQUETYPENAME  );
  DALI_CHECK_FAIL(!type,  "TypeRegistry failed to get the typeInfo name .");

  TypeInfo baseType = TypeRegistry::Get().GetTypeInfo( UNIQUETYPENAMECUSTOM );
  DALI_CHECK_FAIL(!baseType,  "TypeRegistry failed to get the typeInfo name .");

  BaseHandle handle = type.CreateInstance();
  DALI_CHECK_FAIL(!handle,  "CreateInstance failed to return the  basehandle .");
  //DALI_CHECK_FAIL( type.GetSignalName(FIRST_INDEX) != strSignalOne, "TypeInfo::GetSignalName is failed." );

  DaliLog::PrintPass();
}

void TypeInfoGetPropertyCount()
{
  string propertyName( "prop-1" );
  int propertyIndex( PROPERTY_REGISTRATION_START_INDEX );

  TypeInfo typeInfo = TypeRegistry::Get().GetTypeInfo( typeid(MyTestCustomActor) );
  DALI_CHECK_FAIL(!typeInfo,  "TypeRegistry failed to get the typeInfo name .");
  BaseHandle handle = typeInfo.CreateInstance();
  DALI_CHECK_FAIL(!handle,  "CreateInstance failed to create the handle  .");
  Actor customActor = Actor::DownCast( handle );
  DALI_CHECK_FAIL(!customActor,  "Actor Downcast failed to return valid handle  .");

  Property::Type propertyType( Property::BOOLEAN );
  PropertyRegistration property1( customType, propertyName, propertyIndex, propertyType, &TypeSetProperty, &TypeGetPropertyTypeInfo );

  Property::IndexContainer indices;
  typeInfo.GetPropertyIndices( indices );
  DALI_CHECK_FAIL(indices.Size() != customActor.GetPropertyCount(),  "GetPropertyIndices failed to retrive the size .");
  DaliLog::PrintPass();
}

void TypeInfoGetPropertyIndices()
{
  string propertyName( "prop-1" );
  int propertyIndex( PROPERTY_REGISTRATION_START_INDEX );

  TypeInfo typeInfo = TypeRegistry::Get().GetTypeInfo( typeid(MyTestCustomActor) );
  DALI_CHECK_FAIL(!typeInfo,  "TypeRegistry failed to get the typeInfo name .");
  BaseHandle handle = typeInfo.CreateInstance();
  DALI_CHECK_FAIL(!handle,  "CreateInstance failed to create the handle  .");
  Actor customActor = Actor::DownCast( handle );
  DALI_CHECK_FAIL(!customActor,  "Actor Downcast failed to return valid handle  .");

  Property::Type propertyType( Property::BOOLEAN );
  PropertyRegistration property1( customType, propertyName, propertyIndex, propertyType, &TypeSetProperty, &TypeGetPropertyTypeInfo );

  Property::IndexContainer indices;
  typeInfo.GetPropertyIndices( indices );
  DALI_CHECK_FAIL(indices.Size() != customActor.GetPropertyCount(),  "GetPropertyIndices failed to retrive the size .");
  DaliLog::PrintPass();
}

void TypeInfoGetPropertyName()
{
  string propertyName( "prop-1" );
  int propertyIndex( PROPERTY_REGISTRATION_START_INDEX );

  TypeInfo typeInfo = TypeRegistry::Get().GetTypeInfo( typeid(MyTestCustomActor) );
  DALI_CHECK_FAIL(!typeInfo,  "TypeRegistry failed to get the typeInfo name .");
  BaseHandle handle = typeInfo.CreateInstance();
  DALI_CHECK_FAIL(!handle,  "CreateInstance failed to create the handle  .");
  Actor customActor = Actor::DownCast( handle );
  DALI_CHECK_FAIL(!customActor,  "Actor Downcast failed to return valid handle  .");

  Property::Type propertyType( Property::BOOLEAN );
  PropertyRegistration property1( customType, propertyName, propertyIndex, propertyType, &TypeSetProperty, &TypeGetPropertyTypeInfo );

  Property::IndexContainer indices;
  typeInfo.GetPropertyIndices( indices );
  DALI_CHECK_FAIL(indices.Size() != customActor.GetPropertyCount(),  "GetPropertyIndices failed to retrive the size .");
  DaliLog::PrintPass();
}

void TypeInfoGetChildProperties01()
{
  TypeRegistry typeRegistry = TypeRegistry::Get();

  // Register child properties on a type via name
  auto customActorTypeInfo = typeRegistry.GetTypeInfo( typeid(CustomActor) );
  auto myCustomTypeInfo = typeRegistry.GetTypeInfo( typeid(MyTestCustomActor) );
  DALI_CHECK_FAIL( !customActorTypeInfo, "GetTypeInfo is failed" );
  DALI_CHECK_FAIL( !myCustomTypeInfo, "GetTypeInfo is failed" );

  const Property::Index WIDTH_SPECIFICATION( CHILD_PROPERTY_REGISTRATION_START_INDEX );
  const Property::Index HEIGHT_SPECIFICATION( CHILD_PROPERTY_REGISTRATION_START_INDEX + 1);

  ChildPropertyRegistration childProperty1( customActorTypeInfo.GetName(), "widthSpecification", WIDTH_SPECIFICATION, Property::INTEGER );
  ChildPropertyRegistration childProperty2( customActorTypeInfo.GetName(), "heightSpecification", HEIGHT_SPECIFICATION, Property::INTEGER );

  auto index = customActorTypeInfo.GetChildPropertyIndex( "widthSpecification" );
  DALI_CHECK_FAIL( index != WIDTH_SPECIFICATION, "GetChildPropertyIndex is failed." );

  index = customActorTypeInfo.GetChildPropertyIndex( "heightSpecification" );
  DALI_CHECK_FAIL( index != HEIGHT_SPECIFICATION, "GetChildPropertyIndex is failed." );

  auto name = customActorTypeInfo.GetChildPropertyName( WIDTH_SPECIFICATION );
  DALI_CHECK_FAIL( name != "widthSpecification", "GetChildPropertyName is failed." );

  name = customActorTypeInfo.GetChildPropertyName( HEIGHT_SPECIFICATION );
  DALI_CHECK_FAIL( name != "heightSpecification", "GetChildPropertyName is failed." );

  auto type = customActorTypeInfo.GetChildPropertyType( WIDTH_SPECIFICATION );
  DALI_CHECK_FAIL( type != Property::INTEGER, "GetChildPropertyType is failed." );

  type = customActorTypeInfo.GetChildPropertyType( HEIGHT_SPECIFICATION );
  DALI_CHECK_FAIL( type != Property::INTEGER, "GetChildPropertyType is failed." );

  DaliLog::PrintPass();
}

void TypeInfoGetChildProperties02()
{
  TypeRegistry typeRegistry = TypeRegistry::Get();

  // Check registered child properties can be retrieved
  auto customActorTypeInfo = typeRegistry.GetTypeInfo( typeid(CustomActor) );
  auto myCustomTypeInfo = typeRegistry.GetTypeInfo( typeid(MyTestCustomActor) );
  DALI_CHECK_FAIL( !customActorTypeInfo, "GetTypeInfo is failed" );
  DALI_CHECK_FAIL( !myCustomTypeInfo, "GetTypeInfo is failed" );

  const Property::Index WIDTH_SPECIFICATION( CHILD_PROPERTY_REGISTRATION_START_INDEX );
  const Property::Index HEIGHT_SPECIFICATION( CHILD_PROPERTY_REGISTRATION_START_INDEX + 1);

  ChildPropertyRegistration childProperty1( customActorTypeInfo.GetName(), "widthSpecification", WIDTH_SPECIFICATION, Property::INTEGER );
  ChildPropertyRegistration childProperty2( customActorTypeInfo.GetName(), "heightSpecification", HEIGHT_SPECIFICATION, Property::INTEGER );

  Property::IndexContainer indices;
  myCustomTypeInfo.GetChildPropertyIndices( indices );

  auto result = std::find( indices.Begin(), indices.End(), WIDTH_SPECIFICATION );
  DALI_CHECK_FAIL( result == indices.End(), "GetChildPropertyIndices is failed." );

  result = std::find( indices.Begin(), indices.End(), HEIGHT_SPECIFICATION );
  DALI_CHECK_FAIL( result == indices.End(), "GetChildPropertyIndices is failed." );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase                UtcDaliTypeInfoConstructorP
 * @since_Tizen             2.4
 * @description             Returns the constructor for this type
 */
int UtcDaliTypeInfoConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoCopyConstructorP
 * @since_Tizen             2.4
 * @description             Retrieve the copy constructor of this type
 */
int UtcDaliTypeInfoCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_COPY_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoOperatorAssignmentP
 * @since_Tizen             2.4
 * @description             Retrieve the base type name for this type
 */
int UtcDaliTypeInfoOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_OPERATOR_ASSIGNMENT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoGetNameP
 * @since_Tizen             2.4
 * @description             Retrieve the base type name for this type
 */
int UtcDaliTypeInfoGetNameP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_GET_NAME);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoGetBaseNameP
 * @since_Tizen             2.4
 * @description             Retrieve the base type name for this type
 */
int UtcDaliTypeInfoGetBaseNameP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_GET_BASE_NAME);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoCreateInstanceP
 * @since_Tizen             2.4
 * @description             Retrieve the base type name for this type
 */
int UtcDaliTypeInfoCreateInstanceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_CREATE_INSTANCE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoGetCreatorP
 * @since_Tizen             2.4
 * @description             Retrieve the base type name for this type
 */
int UtcDaliTypeInfoGetCreatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_GET_CREATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoGetActionCountP
 * @since_Tizen             2.4
 * @description             Retrieve the base type name for this type
 */
int UtcDaliTypeInfoGetActionCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_GET_ACTION_COUNT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoGetActionNameP
 * @since_Tizen             2.4
 * @description             Retrieve the base type name for this type
 */
int UtcDaliTypeInfoGetActionNameP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_GET_ACTION_NAME);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoGetSignalCountP
 * @since_Tizen             2.4
 * @description             To Retrieve the signals and actions for the specified type
 */
int UtcDaliTypeInfoGetSignalCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_GET_SIGNAL_COUNT);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase                UtcDaliTypeInfoGetSignalNameP
 * @since_Tizen             2.4
 * @description             To Create an object from specified type and to Retrieve the creator function for this type.
 */
int UtcDaliTypeInfoGetSignalNameP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_GET_SIGNAL_NAME);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoGetPropertyCountP
 * @since_Tizen             2.4
 * @description             To Retrieve all the property indices for this type.
 */
int UtcDaliTypeInfoGetPropertyCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_GET_PROPERTY_COUNT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoGetPropertyIndicesP
 * @since_Tizen             2.4
 * @description             To Retrieve all the property indices for this type.
 */
int UtcDaliTypeInfoGetPropertyIndicesP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_GET_PROPERTY_INDICES);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoGetPropertyNameP
 * @since_Tizen             2.4
 * @description             To Retrieve all the property indices for this type.
 */
int UtcDaliTypeInfoGetPropertyNameP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_GET_PROPERTY_NAME);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoGetChildProperties01
 * @since_Tizen             5.0
 * @description             To Retrieve all child property indices for this type.
 */
int UtcDaliTypeInfoGetChildProperties01(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_GET_CHILD_PROPERTIES_01);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeInfoGetChildProperties02
 * @since_Tizen             5.0
 * @description             To Retrieve all child property indices for this type.
 */
int UtcDaliTypeInfoGetChildProperties02(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Info_TestApp testApp( application, TYPE_INFO_GET_CHILD_PROPERTIES_02);
  application.MainLoop();
  return test_return_value;
}
