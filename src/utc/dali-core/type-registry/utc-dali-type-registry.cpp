#include "utc-dali-type-registry-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

namespace
{
  //
  // Create function as Init function called
  //
  static bool CreateCustomInitCalled = false;
  BaseHandle CreateCustomInit(void)
  {
    CreateCustomInitCalled = true;
    return BaseHandle();
  }

  static bool CreateCustomNamedInitCalled = false;
  BaseHandle CreateCustomNamedInit(void)
  {
    CreateCustomNamedInitCalled = true;
    return BaseHandle();
  }

  const std::string scriptedName("PopupStyle");
  static TypeRegistration scriptedType( scriptedName, typeid(Dali::CustomActor), CreateCustomNamedInit );

  // Property Registration
  bool setPropertyCalled = false;
  bool getPropertyCalled = false;
  void SetProperty( BaseObject* object, Property::Index propertyIndex, const Property::Value& value)
  {
    setPropertyCalled = true;
  }
  Property::Value GetProperty( BaseObject* object, Property::Index propertyIndex )
  {
    getPropertyCalled = true;
    return Property::Value( true );
  }

  /*******************************************************************************
   *
   * Custom Actor
   *
   ******************************************************************************/
  namespace Impl
  {
    struct MyTypeRegistryTestCustomActor : public CustomActorImpl
    {
      typedef Signal< void ()> SignalType;
      typedef Signal< void (float)> SignalTypeFloat;

      MyTypeRegistryTestCustomActor() : CustomActorImpl( ActorFlags( REQUIRES_TOUCH_EVENTS ) )
      { }

      virtual ~MyTypeRegistryTestCustomActor()
      { }

      void ResetCallStack()
      {
      }

      // From CustomActorImpl
      virtual void OnStageConnection( int depth )
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

  class MyTypeRegistryTestCustomActor : public CustomActor
  {
    public:

      typedef Signal< void ()> SignalType;
      typedef Signal< void (float)> SignalTypeFloat;

      MyTypeRegistryTestCustomActor()
      {
      }

      static MyTypeRegistryTestCustomActor New()
      {
        Impl::MyTypeRegistryTestCustomActor* p = new Impl::MyTypeRegistryTestCustomActor;
        return MyTypeRegistryTestCustomActor( *p ); // takes ownership
      }

      virtual ~MyTypeRegistryTestCustomActor()
      {
      }

      static MyTypeRegistryTestCustomActor DownCast( BaseHandle handle )
      {
        MyTypeRegistryTestCustomActor result;

        CustomActor custom = Dali::CustomActor::DownCast( handle );
        if ( custom )
        {
          CustomActorImpl& customImpl = custom.GetImplementation();

          Impl::MyTypeRegistryTestCustomActor* impl = dynamic_cast<Impl::MyTypeRegistryTestCustomActor*>(&customImpl);

          if (impl)
          {
            result = MyTypeRegistryTestCustomActor(customImpl.GetOwner());
          }
        }

        return result;
      }

      SignalType& GetCustomSignal()
      {
        Dali::RefObject& obj = GetImplementation();
        return static_cast<Impl::MyTypeRegistryTestCustomActor&>( obj ).mSignal;
      }

    private:

      MyTypeRegistryTestCustomActor(Internal::CustomActor* internal)
        : CustomActor(internal)
      {
      }

      MyTypeRegistryTestCustomActor( Impl::MyTypeRegistryTestCustomActor& impl )
        : CustomActor( impl )
      {
      }
  };


  class MyTypeRegistryTestCustomActor2 : public CustomActor
  {
    public:

      MyTypeRegistryTestCustomActor2()
      {
      }

      static MyTypeRegistryTestCustomActor2 New()
      {
        return MyTypeRegistryTestCustomActor2(); // takes ownership
      }

      virtual ~MyTypeRegistryTestCustomActor2()
      {
      }

      static MyTypeRegistryTestCustomActor2 DownCast( BaseHandle handle )
      {
        MyTypeRegistryTestCustomActor2 result;

        CustomActor custom = Dali::CustomActor::DownCast( handle );
        if ( custom )
        {
          CustomActorImpl& customImpl = custom.GetImplementation();

          Impl::MyTypeRegistryTestCustomActor* impl = dynamic_cast<Impl::MyTypeRegistryTestCustomActor*>(&customImpl);

          if (impl)
          {
            result = MyTypeRegistryTestCustomActor2(customImpl.GetOwner());
          }
        }

        return result;
      }

    private:

      MyTypeRegistryTestCustomActor2(Internal::CustomActor* internal)
        : CustomActor(internal)
      {
      }

      MyTypeRegistryTestCustomActor2( Impl::MyTypeRegistryTestCustomActor& impl )
        : CustomActor( impl )
      {
      }
  };

  static TypeRegistration customTypeInit( typeid(MyTypeRegistryTestCustomActor2), typeid(Dali::CustomActor), CreateCustomInit, true );


  BaseHandle CreateCustom1(void)
  {
    return MyTypeRegistryTestCustomActor::New();
  }

  static std::string lastSignalConnectionCustom;

  bool DoConnectSignalCustom1( BaseObject* object, ConnectionTrackerInterface* tracker, const std::string& signalName, FunctorDelegate* functor )
  {
    lastSignalConnectionCustom = signalName;

    bool connected( true );

    Dali::BaseHandle handle(object);
    MyTypeRegistryTestCustomActor customActor = MyTypeRegistryTestCustomActor::DownCast(handle);

    if( "sig1" == signalName )
    {
      customActor.GetCustomSignal().Connect( tracker, functor );
    }
    else
    {
      // signalName does not match any signal
      connected = false;
    }

    return connected;
  }

  bool DoConnectSignalCustomFailure1( BaseObject* object, ConnectionTrackerInterface* tracker, const std::string& signalName, FunctorDelegate* functor )
  {
    lastSignalConnectionCustom = "failed";

    return false; // This is supposed to fail
  }

  struct CustomTestFunctor
  {
    CustomTestFunctor()
    {
      ++mTotalInstanceCount;
      ++mCurrentInstanceCount;
    }

    CustomTestFunctor( const CustomTestFunctor& copyMe )
    {
      ++mTotalInstanceCount;
      ++mCurrentInstanceCount;
    }

    ~CustomTestFunctor()
    {
      --mCurrentInstanceCount;
    }

    void operator()()
    {
      ++mCallbackCount;
    }

    static int mTotalInstanceCount;
    static int mCurrentInstanceCount;
    static int mCallbackCount;
  };

  int CustomTestFunctor::mTotalInstanceCount = 0;
  int CustomTestFunctor::mCurrentInstanceCount = 0;
  int CustomTestFunctor::mCallbackCount = 0;

  static void ResetFunctorCounts()
  {
    CustomTestFunctor::mTotalInstanceCount   = 0;
    CustomTestFunctor::mCurrentInstanceCount = 0;
    CustomTestFunctor::mCallbackCount        = 0;
  }

  static std::string lastActionCustom;
  bool DoActionCustom(BaseObject* object, const std::string& actionName, const Property::Map& /*attributes*/)
  {
    lastActionCustom = actionName;
    return true;
  }

  // Custom type registration
  static TypeRegistration customType1( typeid(MyTypeRegistryTestCustomActor), typeid(Dali::CustomActor), CreateCustom1 );

  // Custom signals
  static SignalConnectorType customSignalConnector1( customType1, "sig1", DoConnectSignalCustom1 );
  static SignalConnectorType customSignalConnector2( customType1, "sig2", DoConnectSignalCustomFailure1 );
  static const int TEST_SIGNAL_COUNT = 2;

  // Custom actions
  static TypeAction customAction1( customType1, "act1", DoActionCustom);
  static const int TEST_ACTION_COUNT = 1;

  class TestConnectionTracker : public ConnectionTracker
  {
    public:

      TestConnectionTracker()
      {
      }
  };

  BaseHandle CreateNamedActorType()
  {
    Actor actor = Actor::New();
    actor.SetName( "NamedActor" );
    return actor;
  }

  TypeRegistration namedActorType( "MyNamedActor", typeid(Dali::Actor), CreateNamedActorType );
  PropertyRegistration namedActorPropertyOne( namedActorType, "propName",  PROPERTY_REGISTRATION_START_INDEX, Property::BOOLEAN, &SetProperty, &GetProperty );

} // Anonymous namespace

/**
 * @function            utc_Dali_TypeRegistry_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_TypeRegistry_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_TypeRegistry_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_TypeRegistry_cleanup(void)
{

}

void TypeRegistryGetTypeP();
void TypeRegistryConstructorP();
void TypeRegistryCopyConstructorP();
void TypeRegistryCopyConstructorP2();
void TypeRegistryOperatorAssignmentP();
void TypeRegistryGetTypeInfoP();
void TypeRegistryGetTypeInfoP2();
void TypeRegistryGetTypeNameCountP();
void TypeRegistryGetTypeNamesP();
void TypeRegistryPropertyRegistrationP();
void TypeRegistryRegisteredNameP();
void TypeRegistrySignalConnectorTypeP();
void TypeRegistrySignalConnectorTypeN();
void TypeRegistryTypeActionP();
void TypeRegistryTypeActionN();
void TypeRegistryTypeRegistrationNotCallingCreateOnInitP();
void TypeRegistryTypeRegistrationCallingCreateOnInitP();
void TypeRegistryTypeRegistrationForNamedTypeP();
void TypeRegistryChildPropertyRegistrationP();
void TypeRegistryChildPropertyRegistrationN();
void TypeRegisterChildProperties();

namespace
{
  enum TEST_CASES_LIST_TYPE_REGISTRY
  {
    TYPE_REGISTRY_GET_TYPE_P,
    TYPE_REGISTRY_CONSTRUCTOR_P,
    TYPE_REGISTRY_COPY_CONSTRUCTOR_P,
    TYPE_REGISTRY_COPY_CONSTRUCTOR_P2,
    TYPE_REGISTRY_ASSIGNMENT_OPERATOR_P,
    TYPE_REGISTRY_GET_TYPE_INFO_P,
    TYPE_REGISTRY_GET_TYPE_INFO_P2,
    TYPE_REGISTRY_GET_TYPE_P_NAME_COUNT_P,
    TYPE_REGISTRY_GET_TYPE_P_NAMES_P,
    TYPE_REGISTRY_ANIMATABLE_PROPERTY_REGISTRATION_P,
    TYPE_REGISTRY_ANIMATABLE_PROPERTY_COMPONENT_REGISTRATION_P,
    TYPE_REGISTRY_PROPERTY_REGISTRATION_P,
    TYPE_REGISTRY_REGISTERED_NAME_P,
    TYPE_REGISTRY_SIGNAL_CONNECTOR_TYPE_P,
    TYPE_REGISTRY_SIGNAL_CONNECTOR_TYPE_N,
    TYPE_REGISTRY_TYPE_ACTION_P,
    TYPE_REGISTRY_TYPE_ACTION_N,
    TYPE_REGISTRY_TYPE_REGISTRATION_NOT_CALLING_CREATE_ON_INIT_P,
    TYPE_REGISTRY_TYPE_REGISTRATION_CALLING_CREATE_ON_INIT_P,
    TYPE_REGISTRY_TYPE_REGISTRATION_FOR_NAMED_TYPE_P,
    TYPE_REGISTRY_CHILD_PROPERTY_REGISTRATION_P,
    TYPE_REGISTRY_CHILD_PROPERTY_REGISTRATION_N,
    TYPE_REGISTRY_CHILD_PROPERTIES
  };

  struct Type_Registry_TestApp : public ConnectionTracker
  {
    Type_Registry_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Type_Registry_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Type_Registry_TestApp::Tick );
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
        case TYPE_REGISTRY_GET_TYPE_P:
          TypeRegistryGetTypeP();
          break;

        case TYPE_REGISTRY_CONSTRUCTOR_P:
          TypeRegistryConstructorP();
          break;

        case TYPE_REGISTRY_COPY_CONSTRUCTOR_P:
          TypeRegistryCopyConstructorP();
          break;

        case TYPE_REGISTRY_COPY_CONSTRUCTOR_P2:
          TypeRegistryCopyConstructorP2();
          break;
        case TYPE_REGISTRY_ASSIGNMENT_OPERATOR_P:
          TypeRegistryOperatorAssignmentP();
          break;

        case TYPE_REGISTRY_GET_TYPE_INFO_P:
          TypeRegistryGetTypeInfoP();
          break;

        case TYPE_REGISTRY_GET_TYPE_INFO_P2:
          TypeRegistryGetTypeInfoP2();
          break;

        case TYPE_REGISTRY_GET_TYPE_P_NAME_COUNT_P:
          TypeRegistryGetTypeNameCountP();
          break;

        case TYPE_REGISTRY_GET_TYPE_P_NAMES_P:
          TypeRegistryGetTypeNamesP();
          break;

        case TYPE_REGISTRY_PROPERTY_REGISTRATION_P:
          TypeRegistryPropertyRegistrationP();
          break;

        case TYPE_REGISTRY_REGISTERED_NAME_P:
          TypeRegistryRegisteredNameP();
          break;

        case TYPE_REGISTRY_SIGNAL_CONNECTOR_TYPE_P:
          TypeRegistrySignalConnectorTypeP();
          break;

        case TYPE_REGISTRY_SIGNAL_CONNECTOR_TYPE_N:
          TypeRegistrySignalConnectorTypeN();
          break;

        case TYPE_REGISTRY_TYPE_ACTION_P:
          TypeRegistryTypeActionP();
          break;

        case TYPE_REGISTRY_TYPE_ACTION_N:
          TypeRegistryTypeActionN();
          break;

        case TYPE_REGISTRY_TYPE_REGISTRATION_NOT_CALLING_CREATE_ON_INIT_P:
          TypeRegistryTypeRegistrationNotCallingCreateOnInitP();
          break;

        case TYPE_REGISTRY_TYPE_REGISTRATION_CALLING_CREATE_ON_INIT_P:
          TypeRegistryTypeRegistrationCallingCreateOnInitP();
          break;

        case TYPE_REGISTRY_TYPE_REGISTRATION_FOR_NAMED_TYPE_P:
          TypeRegistryTypeRegistrationForNamedTypeP();
          break;

        case TYPE_REGISTRY_CHILD_PROPERTY_REGISTRATION_P:
          TypeRegistryChildPropertyRegistrationP();
          break;

        case TYPE_REGISTRY_CHILD_PROPERTY_REGISTRATION_N:
          TypeRegistryChildPropertyRegistrationN();
          break;
        case TYPE_REGISTRY_CHILD_PROPERTIES:
          TypeRegisterChildProperties();
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

void TypeRegistryGetTypeP()
{
  TypeRegistry typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");

  DaliLog::PrintPass();
}

void TypeRegistryConstructorP()
{
  TypeRegistry typeRegistry;
  DALI_CHECK_FAIL(typeRegistry,  "TypeRegistry::Constructor() is failed.");

  DaliLog::PrintPass();
}

void TypeRegistryCopyConstructorP()
{
  TypeRegistry typeRegistry;
  const string STR_TYPE_NAME = "Actor";

  typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");

  TypeRegistry typeRegistryCopy( typeRegistry );

  DALI_CHECK_FAIL(!typeRegistryCopy || (typeRegistryCopy != typeRegistry), "TypeRegistry::TypeRegistry(Dali::TypeRegistry const&) is failed.");
  DALI_CHECK_FAIL( typeRegistryCopy.GetTypeInfo( STR_TYPE_NAME ).GetName() != typeRegistry.GetTypeInfo( STR_TYPE_NAME ).GetName(), "Copied type registry handle does not have the selected type name." );

  DaliLog::PrintPass();
}

void TypeRegistryCopyConstructorP2()
{
  TypeRegistry typeRegistry;
  const string STR_TYPE_NAME = "Actor";

  typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");

  TypeRegistry typeRegistryCopy( typeRegistry );

  DALI_CHECK_FAIL(!typeRegistryCopy || (typeRegistryCopy != typeRegistry), "TypeRegistry::TypeRegistry(Dali::TypeRegistry const&) is failed.");

  DALI_CHECK_FAIL( typeRegistryCopy.GetTypeInfo( STR_TYPE_NAME ).GetName() != typeRegistry.GetTypeInfo( STR_TYPE_NAME ).GetName(), "Copied type registry handle does not have the selected type name." );

  DaliLog::PrintPass();
}

void TypeRegistryOperatorAssignmentP()
{
  TypeRegistry typeRegistry;
  const string STR_TYPE_NAME = "Actor";

  typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");

  TypeRegistry typeRegistryCopy( typeRegistry );

  DALI_CHECK_FAIL(!typeRegistryCopy || (typeRegistryCopy != typeRegistry), "TypeRegistry::TypeRegistry(Dali::TypeRegistry const&) is failed.");

  DALI_CHECK_FAIL( typeRegistryCopy.GetTypeInfo( STR_TYPE_NAME ).GetName() != typeRegistry.GetTypeInfo( STR_TYPE_NAME ).GetName(), "Copied type registry handle does not have the selected type name." );

  TypeRegistry typeRegistryAssigned = typeRegistry;

  DALI_CHECK_FAIL(!typeRegistryAssigned || (typeRegistryAssigned != typeRegistry),  "TypeRegistry::operator=(Dali::TypeRegistry const&) is failed.");
  DALI_CHECK_FAIL( typeRegistryAssigned.GetTypeInfo( STR_TYPE_NAME ).GetName() != typeRegistry.GetTypeInfo( STR_TYPE_NAME ).GetName(), "Assigned type registry handle does not have the selected type name." );

  DaliLog::PrintPass();
}

void TypeRegistryGetTypeInfoP()
{
  TypeInfo typeInfo;

  TypeRegistry typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");

  typeInfo = typeRegistry.GetTypeInfo( "Actor" );
  DALI_CHECK_FAIL(!typeInfo, "TypeRegistry::typeInfo() is failed.");

  typeInfo = typeRegistry.GetTypeInfo( "CameraActor" );
  DALI_CHECK_FAIL(!typeInfo, "TypeRegistry::typeInfo() is failed.");

  typeInfo = typeRegistry.GetTypeInfo( "Animation" );
  DALI_CHECK_FAIL(!typeInfo, "TypeRegistry::typeInfo() is failed.");

  DaliLog::PrintPass();
}

void TypeRegistryGetTypeInfoP2()
{
  TypeInfo typeInfoFromName;
  TypeInfo typeInfoFromType;

  TypeRegistry typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");

  typeInfoFromName = typeRegistry.GetTypeInfo( "Actor" );
  DALI_CHECK_FAIL(!typeInfoFromName, "TypeRegistry::typeInfo() is failed.");

  typeInfoFromType = typeRegistry.GetTypeInfo( typeid(Dali::Actor) );
  DALI_CHECK_FAIL(!typeInfoFromType, "TypeRegistry::typeInfo() is failed.");

  DALI_CHECK_FAIL(typeInfoFromName != typeInfoFromType , "TypeRegistry::typeInfo() is failed.");

  DaliLog::PrintPass();
}

void TypeRegistryGetTypeNameCountP()
{

  TypeInfo typeInfo;

  TypeRegistry typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");
  size_t nameCount = typeRegistry.GetTypeNameCount();
  for(unsigned int i = 0; i < nameCount; i++)
  {
    std::string typeName = typeRegistry.GetTypeName(i);
    typeInfo = TypeRegistry::Get().GetTypeInfo( typeName );
    DALI_CHECK_FAIL(!typeInfo, "TypeRegistry::Get() is failed.");
  }
  DaliLog::PrintPass();
}

void TypeRegistryGetTypeNamesP()
{
  TypeInfo typeInfo;

  TypeRegistry typeRegistry = TypeRegistry::Get();
  DALI_CHECK_FAIL(!typeRegistry,  "TypeRegistry::Get() is failed.");
  size_t nameCount = typeRegistry.GetTypeNameCount();
  for(unsigned int i = 0; i < nameCount; i++)
  {
    std::string typeName = typeRegistry.GetTypeName(i);
    typeInfo = TypeRegistry::Get().GetTypeInfo( typeName );
    DALI_CHECK_FAIL(!typeInfo, "TypeRegistry::Get() is failed.");
  }
  DaliLog::PrintPass();
}

void TypeRegistryPropertyRegistrationP()
{
  TypeRegistry typeRegistry = TypeRegistry::Get();

  // Check property count before property registration
  TypeInfo typeInfo = typeRegistry.GetTypeInfo( typeid(MyTypeRegistryTestCustomActor) );
  DALI_CHECK_FAIL( !typeInfo, "TypeInfo is failed" );
  BaseHandle handle = typeInfo.CreateInstance();
  DALI_CHECK_FAIL( !handle, "CreateInstance is failed" );
  Actor customActor = Actor::DownCast( handle );
  DALI_CHECK_FAIL( !customActor, "Actor downcast is failed" );
  unsigned int initialPropertyCount( customActor.GetPropertyCount() );

  std::string propertyName( "prop1" );
  int propertyIndex( PROPERTY_REGISTRATION_START_INDEX );
  Property::Type propertyType( Property::BOOLEAN );
  PropertyRegistration property1( customType1, propertyName, propertyIndex, propertyType, &SetProperty, &GetProperty );

  // Check property count after registration
  unsigned int postRegistrationPropertyCount( customActor.GetPropertyCount() );
  DALI_CHECK_FAIL( initialPropertyCount + 1u != postRegistrationPropertyCount, "postRegistrationPropertyCount is failed" );

  // Add custom property and check property count
  customActor.RegisterProperty( "customProp1",   true );
  unsigned int customPropertyCount( customActor.GetPropertyCount() );
  DALI_CHECK_FAIL( postRegistrationPropertyCount + 1u != customPropertyCount, "customPropertyCount is failed" );

  // Set the property, ensure SetProperty called
  DALI_CHECK_FAIL( setPropertyCalled, "SetProperty exists" );
  customActor.SetProperty( propertyIndex, false );
  DALI_CHECK_FAIL( !setPropertyCalled, "SetProperty is failed" );

  // Get the property, ensure GetProperty called
  DALI_CHECK_FAIL( getPropertyCalled, "GetProperty exists" );
  (void)customActor.GetProperty< bool >( propertyIndex );
  DALI_CHECK_FAIL( !getPropertyCalled, "GetProperty is failed");

  // Check the property name
  DALI_CHECK_FAIL( customActor.GetPropertyName( propertyIndex ) != propertyName, "GetPropertyName is failed" );
  DALI_CHECK_FAIL( typeInfo.GetPropertyName( propertyIndex ) != propertyName, "GetPropertyName is failed" );

  // Check the property index
  DALI_CHECK_FAIL( customActor.GetPropertyIndex( propertyName ) != propertyIndex, "GetPropertyIndex is failed" );

  // Check the property type
  DALI_CHECK_FAIL( customActor.GetPropertyType( propertyIndex ) != propertyType, "GetPropertyType is failed" );

  // Check property count of type-info is 1
  Property::IndexContainer indices;
  typeInfo.GetPropertyIndices( indices );
  DALI_CHECK_FAIL( indices.Size() != typeInfo.GetPropertyCount(), "GetPropertyIndices is failed" );

  // Ensure indices returned from actor and customActor differ by two
  Actor actor = Actor::New();
  actor.GetPropertyIndices( indices );
  unsigned int actorIndices = indices.Size();
  customActor.GetPropertyIndices( indices );
  unsigned int customActorIndices = indices.Size();
  DALI_CHECK_FAIL( actorIndices + 2u != customActorIndices, "customActorIndices is failed" ); // Custom property + registered property

  DaliLog::PrintPass();
}

void TypeRegistryRegisteredNameP()
{
  DALI_CHECK_FAIL( scriptedName != scriptedType.RegisteredName(), "Script name is different" );

  TypeInfo baseType = TypeRegistry::Get().GetTypeInfo( scriptedName );
  DALI_CHECK_FAIL( !baseType, "GetTypeInfo is failed" );

  BaseHandle handle = baseType.CreateInstance();
  DALI_CHECK_FAIL( !CreateCustomNamedInitCalled, "CreateInstance is failed" );

  TypeInfo type = TypeRegistry::Get().GetTypeInfo( scriptedName );
  DALI_CHECK_FAIL( !type, "GetTypeInfo is failed" );

  DaliLog::PrintPass();
}

void TypeRegistrySignalConnectorTypeP()
{
  ResetFunctorCounts();

  TypeInfo type = TypeRegistry::Get().GetTypeInfo( "MyTypeRegistryTestCustomActor" );
  DALI_CHECK_FAIL( !type, "GetTypeInfo is failed" );

  BaseHandle handle = type.CreateInstance();
  DALI_CHECK_FAIL( !handle, "CreateInstance is failed" );

  MyTypeRegistryTestCustomActor customHandle = MyTypeRegistryTestCustomActor::DownCast( handle );
  DALI_CHECK_FAIL( !customHandle, "DownCast is failed" );

  {
    TestConnectionTracker tracker;

    bool connected = handle.ConnectSignal( &tracker, "sig1", CustomTestFunctor() );
    DALI_CHECK_FAIL( connected != true, "ConnectSignal is failed" );
    DALI_CHECK_FAIL( lastSignalConnectionCustom != "sig1", "ConnectSignal is failed" );
    DALI_CHECK_FAIL( CustomTestFunctor::mTotalInstanceCount != 2/*temporary copy + FunctorDelegate copy*/, "ConnectSignal is failed" );
    DALI_CHECK_FAIL( CustomTestFunctor::mCurrentInstanceCount != 1, "ConnectSignal is failed" );

    DALI_CHECK_FAIL( CustomTestFunctor::mCallbackCount != 0, "ConnectSignal is failed" );
    customHandle.GetCustomSignal().Emit();
    DALI_CHECK_FAIL( CustomTestFunctor::mCallbackCount != 1, "GetCustomSignal is failed" );
    DALI_CHECK_FAIL( CustomTestFunctor::mTotalInstanceCount != 2/*temporary copy + FunctorDelegate copy*/, "GetCustomSignal is failed" );
    DALI_CHECK_FAIL( CustomTestFunctor::mCurrentInstanceCount != 1, "GetCustomSignal is failed" );
  }
  //tracker should automatically disconnect here
  DALI_CHECK_FAIL( CustomTestFunctor::mTotalInstanceCount != 2/*temporary copy + FunctorDelegate copy*/, "ConnectSignal is failed" );
  DALI_CHECK_FAIL( CustomTestFunctor::mCurrentInstanceCount != 0, "ConnectSignal is failed" );

  //Test that functor is disconnected
  DALI_CHECK_FAIL( CustomTestFunctor::mCallbackCount != 1, "ConnectSignal is failed" );
  customHandle.GetCustomSignal().Emit();
  DALI_CHECK_FAIL( CustomTestFunctor::mCallbackCount != 1/*not incremented*/, "GetCustomSignal is failed" );
  DALI_CHECK_FAIL( CustomTestFunctor::mTotalInstanceCount != 2/*temporary copy + FunctorDelegate copy*/, "GetCustomSignal is failed" );
  DALI_CHECK_FAIL( CustomTestFunctor::mCurrentInstanceCount != 0, "GetCustomSignal is failed" );

  DaliLog::PrintPass();
}
void TypeRegistrySignalConnectorTypeN()
{
  // Test what happens when signal connnector (DoConnectSignalFailure method) returns false

  ResetFunctorCounts();

  TypeInfo type = TypeRegistry::Get().GetTypeInfo( "MyTypeRegistryTestCustomActor" );
  DALI_CHECK_FAIL( !type, "GetTypeInfo is failed" );

  TypeInfo baseType = TypeRegistry::Get().GetTypeInfo( "CustomActor" );
  DALI_CHECK_FAIL( !baseType, "GetTypeInfo is failed" );

  BaseHandle handle = type.CreateInstance();
  DALI_CHECK_FAIL( !handle, "CreateInstance is failed" );

  MyTypeRegistryTestCustomActor customHandle = MyTypeRegistryTestCustomActor::DownCast( handle );
  DALI_CHECK_FAIL( !customHandle, "DownCast is failed" );

  DALI_CHECK_FAIL( type.GetActionCount() != TEST_ACTION_COUNT + baseType.GetActionCount(), "GetActionCount is failed" );

  DALI_CHECK_FAIL( type.GetSignalCount() != TEST_SIGNAL_COUNT + baseType.GetSignalCount(), "GetSignalCount is failed" );

  {
    TestConnectionTracker tracker;

    bool connected = handle.ConnectSignal( &tracker, "sig2", CustomTestFunctor() );
    DALI_CHECK_FAIL( connected != false/*This is supposed to fail*/, "ConnectSignal is failed" );
    DALI_CHECK_FAIL( lastSignalConnectionCustom != "failed", "ConnectSignal is failed" );
    DALI_CHECK_FAIL( CustomTestFunctor::mTotalInstanceCount != 2/*temporary copy + FunctorDelegate copy*/, "ConnectSignal is failed" );
    DALI_CHECK_FAIL( CustomTestFunctor::mCurrentInstanceCount != 0/*deleted along with FunctorDelegate*/, "ConnectSignal is failed" );

    // Should be a NOOP
    DALI_CHECK_FAIL( CustomTestFunctor::mCallbackCount != 0, "ConnectSignal is failed" );
    customHandle.GetCustomSignal().Emit();
    DALI_CHECK_FAIL( CustomTestFunctor::mCallbackCount != 0/*never called*/, "GetCustomSignal is failed" );
  }
  //tracker should have nothing to disconnect here

  // Should be a NOOP
  DALI_CHECK_FAIL( CustomTestFunctor::mCallbackCount != 0, "ConnectSignal is failed" );
  customHandle.GetCustomSignal().Emit();
  DALI_CHECK_FAIL( CustomTestFunctor::mCallbackCount != 0/*never called*/, "GetCustomSignal is failed" );

  DaliLog::PrintPass();
}

void TypeRegistryTypeActionP()
{
  ResetFunctorCounts();

  TypeInfo type = TypeRegistry::Get().GetTypeInfo( "MyTypeRegistryTestCustomActor" );
  DALI_CHECK_FAIL( !type, "GetTypeInfo is failed" );

  BaseHandle handle = type.CreateInstance();
  DALI_CHECK_FAIL( !handle, "CreateInstance is failed" );

  Property::Map attributes;
  DALI_CHECK_FAIL( !handle.DoAction("act1", attributes), "DoAction is failed" );
  DALI_CHECK_FAIL( lastActionCustom != "act1", "DoAction is failed" );

  DaliLog::PrintPass();
}

void TypeRegistryTypeActionN()
{
  ResetFunctorCounts();

  TypeInfo type = TypeRegistry::Get().GetTypeInfo( "MyTypeRegistryTestCustomActor" );
  DALI_CHECK_FAIL( !type, "GetTypeInfo is failed" );

  BaseHandle handle = type.CreateInstance();
  DALI_CHECK_FAIL( !handle, "CreateInstance is failed" );

  Property::Map attributes;
  DALI_CHECK_FAIL( handle.DoAction( "unknownAction",  attributes ), "DoAction is failed" );

  DaliLog::PrintPass();
}

void TypeRegistryTypeRegistrationNotCallingCreateOnInitP()
{
  ResetFunctorCounts();

  TypeInfo type = TypeRegistry::Get().GetTypeInfo( "MyTypeRegistryTestCustomActor" );
  DALI_CHECK_FAIL( !type, "GetTypeInfo is failed" );

  TypeInfo baseType = TypeRegistry::Get().GetTypeInfo( "CustomActor" );
  DALI_CHECK_FAIL( !baseType, "GetTypeInfo is failed" );

  BaseHandle handle = type.CreateInstance();
  DALI_CHECK_FAIL( !handle, "CreateInstance is failed" );

  MyTypeRegistryTestCustomActor customHandle = MyTypeRegistryTestCustomActor::DownCast( handle );
  DALI_CHECK_FAIL( !customHandle, "DownCast is failed" );

  DALI_CHECK_FAIL( type.GetActionCount() != TEST_ACTION_COUNT + baseType.GetActionCount(), "GetActionCount is failed" );

  DALI_CHECK_FAIL( type.GetSignalCount() != TEST_SIGNAL_COUNT + baseType.GetSignalCount(), "GetSignalCount is failed" );

  {
    TestConnectionTracker tracker;

    bool connected = handle.ConnectSignal( &tracker, "sig1", CustomTestFunctor() );
    DALI_CHECK_FAIL( connected != true, "ConnectSignal is failed" );
    DALI_CHECK_FAIL( lastSignalConnectionCustom != "sig1", "ConnectSignal is failed" );
    DALI_CHECK_FAIL( CustomTestFunctor::mTotalInstanceCount != 2/*temporary copy + FunctorDelegate copy*/, "ConnectSignal is failed" );
    DALI_CHECK_FAIL( CustomTestFunctor::mCurrentInstanceCount != 1, "ConnectSignal is failed" );

    DALI_CHECK_FAIL( CustomTestFunctor::mCallbackCount != 0, "ConnectSignal is failed" );
    customHandle.GetCustomSignal().Emit();
    DALI_CHECK_FAIL( CustomTestFunctor::mCallbackCount != 1, "ConnectSignal is failed" );
    DALI_CHECK_FAIL( CustomTestFunctor::mTotalInstanceCount != 2/*temporary copy + FunctorDelegate copy*/, "GetCustomSignal is failed" );
    DALI_CHECK_FAIL( CustomTestFunctor::mCurrentInstanceCount != 1, "ConnectSignal is failed" );
  }
  // tracker should automatically disconnect here
  DALI_CHECK_FAIL( CustomTestFunctor::mTotalInstanceCount != 2/*temporary copy + FunctorDelegate copy*/, "ConnectSignal is failed" );
  DALI_CHECK_FAIL( CustomTestFunctor::mCurrentInstanceCount != 0, "ConnectSignal is failed" );

  // Test that functor is disconnected
  DALI_CHECK_FAIL( CustomTestFunctor::mCallbackCount != 1, "ConnectSignal is failed" );
  customHandle.GetCustomSignal().Emit();
  DALI_CHECK_FAIL( CustomTestFunctor::mCallbackCount != 1/*not incremented*/, "GetCustomSignal is failed" );
  DALI_CHECK_FAIL( CustomTestFunctor::mTotalInstanceCount != 2/*temporary copy + FunctorDelegate copy*/, "ConnectSignal is failed" );
  DALI_CHECK_FAIL( CustomTestFunctor::mCurrentInstanceCount != 0, "ConnectSignal is failed" );

  Property::Map attributes;
  handle.DoAction("act1", attributes);
  DALI_CHECK_FAIL( lastActionCustom != "act1", "DoAction is failed" );

  DaliLog::PrintPass();
}

void TypeRegistryTypeRegistrationCallingCreateOnInitP()
{
  DALI_CHECK_FAIL( "MyTypeRegistryTestCustomActor2" != customTypeInit.RegisteredName(), "RegisteredName is failed" );

  DALI_CHECK_FAIL( true != CreateCustomInitCalled, "RegisteredName is failed" );
  TypeInfo type = TypeRegistry::Get().GetTypeInfo( "MyTypeRegistryTestCustomActor2" );
  DALI_CHECK_FAIL( !type, "GetTypeInfo is failed" );

  DaliLog::PrintPass();
}

void TypeRegistryTypeRegistrationForNamedTypeP()
{
  // Create Named Actor Type
  TypeInfo type = TypeRegistry::Get().GetTypeInfo( "MyNamedActor" );
  DALI_CHECK_FAIL( !type, "GetTypeInfo is failed" );

  BaseHandle namedHandle = type.CreateInstance();
  DALI_CHECK_FAIL( !namedHandle, "CreateInstance is failed" );
  Actor namedActor( Actor::DownCast( namedHandle ) );
  DALI_CHECK_FAIL( !namedActor, "DownCast is failed" );

  DALI_CHECK_FAIL( namedActor.GetName() != "NamedActor", "GetName is failed" );
  DALI_CHECK_FAIL( type.GetName() != "MyNamedActor", "GetName is failed" );
  DALI_CHECK_FAIL( type.GetBaseName() != "Actor", "GetBaseName is failed" );

  DaliLog::PrintPass();
}

void TypeRegistryChildPropertyRegistrationP()
{
  TypeRegistry typeRegistry = TypeRegistry::Get();

  // Check property count before property registration
  TypeInfo typeInfo = typeRegistry.GetTypeInfo( typeid(MyTypeRegistryTestCustomActor) );
  DALI_CHECK_FAIL( !typeInfo, "GetTypeInfo is failed" );

  BaseHandle handle = typeInfo.CreateInstance();
  DALI_CHECK_FAIL( !handle, "handle creation is failed" );

  Actor customActor = Actor::DownCast( handle );
  DALI_CHECK_FAIL( !customActor, "customActor creation is failed" );

  unsigned int initialPropertyCount( customActor.GetPropertyCount() );

  // Register child properties to the parent
  std::string propertyName( "childProp1" );
  int propertyIndex( CHILD_PROPERTY_REGISTRATION_START_INDEX );
  Property::Type propertyType( Property::BOOLEAN );
  ChildPropertyRegistration childProperty1( customType1, propertyName, propertyIndex, propertyType );

  std::string propertyName2( "childProp2" );
  int propertyIndex2( CHILD_PROPERTY_REGISTRATION_START_INDEX + 1 );
  Property::Type propertyType2( Property::INTEGER );
  ChildPropertyRegistration childProperty2( customType1, propertyName2, propertyIndex2, propertyType2 );

  std::string propertyName3( "childProp3" );
  int propertyIndex3( CHILD_PROPERTY_REGISTRATION_START_INDEX + 2 );
  Property::Type propertyType3( Property::FLOAT );
  ChildPropertyRegistration childProperty3( customType1, propertyName3, propertyIndex3, propertyType3 );

  std::string propertyName4( "childProp4" );
  int propertyIndex4( CHILD_PROPERTY_REGISTRATION_START_INDEX + 3 );
  Property::Type propertyType4( Property::INTEGER );
  ChildPropertyRegistration childProperty4( customType1, propertyName4, propertyIndex4, propertyType4 );

  // Check property count are not changed because the child properties will not be created for the parent
  DALI_CHECK_FAIL( initialPropertyCount != customActor.GetPropertyCount(), "GetProperty count is not same as initial count." );

  // Create a child actor
  Actor childActor = Actor::New();
  DALI_CHECK_FAIL( !childActor, "GetProperty count is not same as initial count." );
  unsigned int initialChildActorPropertyCount( childActor.GetPropertyCount() );

  // The type of child properties should be Property::None as the child hasn't registered any child property yet.
  DALI_CHECK_FAIL( childActor.GetPropertyType( propertyIndex ) != Property::NONE, "propertyIndex should be equals to Property::None" );
  DALI_CHECK_FAIL( childActor.GetPropertyType( propertyIndex2 ) != Property::NONE, "propertyIndex should be equals to Property::None" );
  DALI_CHECK_FAIL( childActor.GetPropertyType( propertyIndex3 ) != Property::NONE, "propertyIndex should be equals to Property::None" );
  DALI_CHECK_FAIL( childActor.GetPropertyType( propertyIndex4 ) != Property::NONE, "propertyIndex should be equals to Property::None" );

  //Set the value for the first child property when the child actor doesn't have a parent yet
  childActor.SetProperty(propertyIndex, true);

  //Check that the first child property is dynamically created
  DALI_CHECK_FAIL( initialChildActorPropertyCount + 1u != childActor.GetPropertyCount(), "GetProperty is failed" );

  //Check the first child property value
  DALI_CHECK_FAIL( childActor.GetProperty< bool >( propertyIndex ) != true, "GetProperty is failed" );

  //Check the first child property type
  DALI_CHECK_FAIL( childActor.GetPropertyType( propertyIndex ) != propertyType, "GetProperty is failed" );

  //Check that the first child property have no name, as it doesn't have a parent yet.
  DALI_CHECK_FAIL( childActor.GetPropertyName( propertyIndex ) != "", "GetProperty is failed" );

  //Check that the first property can't be accessed through its name, as it doesn't have a parent yet.
  DALI_CHECK_FAIL( childActor.GetPropertyIndex( propertyName ) != Property::INVALID_INDEX, "GetProperty is failed" );

  //Create a custom property for the child with the same name as the second child property registered to the parent
  Property::Index customPropertyIndex = childActor.RegisterProperty(propertyName2, 100, Property::READ_WRITE);

  //Check that the custom property is created
  DALI_CHECK_FAIL( initialChildActorPropertyCount + 2u != childActor.GetPropertyCount(), "GetProperty is failed" );

  //Check the property value
  DALI_CHECK_FAIL( childActor.GetProperty< int >( customPropertyIndex ) != 100, "GetProperty is failed" );

  //Check the property index
  DALI_CHECK_FAIL( childActor.GetPropertyIndex( propertyName2 ) != customPropertyIndex, "GetProperty is failed" );

  //Check the property type
  DALI_CHECK_FAIL( childActor.GetPropertyType( customPropertyIndex ) != propertyType2, "GetProperty is failed" );

  //Check the property name
  DALI_CHECK_FAIL( childActor.GetPropertyName( customPropertyIndex ) != propertyName2, "GetProperty is failed" );

  //Now add the child actor to the parent
  customActor.Add( childActor );

  //Check that the first child property now has the correct name as previously registered to the parent
  DALI_CHECK_FAIL( childActor.GetPropertyName( propertyIndex ) != propertyName, "GetProperty is failed" );

  //Check that the child property index for the first child property can now be retrieved through its child property name
  DALI_CHECK_FAIL( childActor.GetPropertyIndex( propertyName ) != propertyIndex, "GetProperty is failed" );

  //Check that the second child property now has the correct index as previously registered to the parent
  DALI_CHECK_FAIL( childActor.GetPropertyName( propertyIndex2 ) != propertyName2, "GetProperty is failed" );

  //Check that the second child property can be accessed through both its custom property index and its child property index
  DALI_CHECK_FAIL( childActor.GetProperty< int >( customPropertyIndex ) != 100, "GetProperty is failed" );

  DALI_CHECK_FAIL( childActor.GetProperty< int >( propertyIndex2 ) != 100, "GetProperty is failed." );
  DALI_CHECK_FAIL( childActor.GetPropertyType( customPropertyIndex ) != propertyType2, "GetProperty is failed." );
  DALI_CHECK_FAIL( childActor.GetPropertyType( propertyIndex2 ) != propertyType2, "GetProperty is failed." );


  // Check that the child property index for the second child property can now be retrieved through its child property name
  DALI_CHECK_FAIL( childActor.GetPropertyIndex( propertyName2 ) != propertyIndex2, "GetProperty is failed." );
  // Set the value for the third child property when the child actor is already added to the parent
  childActor.SetProperty(propertyIndex3, 0.15f);
  // Check that the third child property is dynamically created
  DALI_CHECK_FAIL( initialChildActorPropertyCount + 3u != childActor.GetPropertyCount(), "GetProperty is failed." );

  // Check the third child property value
  DALI_CHECK_FAIL( childActor.GetProperty< float >( propertyIndex3 ) !=  0.15f, "GetProperty is failed." );

  // Check the third child property type
  DALI_CHECK_FAIL( childActor.GetPropertyType( propertyIndex3 ) != propertyType3, "GetProperty is failed." );

  // Check the third child property name
  DALI_CHECK_FAIL( childActor.GetPropertyName( propertyIndex3 ) != propertyName3, "GetProperty is failed." );

  // Check the third child property index.
  DALI_CHECK_FAIL( childActor.GetPropertyIndex( propertyName3 ) != propertyIndex3, "GetProperty is failed." );

  //Create a custom property for the child with the same name as the fourth child property registered to the parent
  Property::Index customPropertyIndex2 = childActor.RegisterProperty(propertyName4, 20, Property::READ_WRITE);

  //Check that the custom property is created
  DALI_CHECK_FAIL( initialChildActorPropertyCount + 4u != childActor.GetPropertyCount(), "GetProperty is failed" );

  //Check the fourth child property value
  DALI_CHECK_FAIL( childActor.GetProperty< int >( propertyIndex4 ) != 20, "GetProperty is failed" );
  DALI_CHECK_FAIL( childActor.GetProperty< int >( customPropertyIndex2 ) != 20, "GetProperty is failed" );

  //Check the fourth child property type
  DALI_CHECK_FAIL( childActor.GetPropertyType( propertyIndex4 ) != propertyType4, "GetProperty is failed" );
  DALI_CHECK_FAIL( childActor.GetPropertyType( customPropertyIndex2 ) != propertyType4, "GetProperty is failed" );

  //Check the fourth child property name
  DALI_CHECK_FAIL( childActor.GetPropertyName( propertyIndex4 ) != propertyName4, "GetProperty is failed" );
  DALI_CHECK_FAIL( childActor.GetPropertyName( customPropertyIndex2 ) != propertyName4, "GetProperty is failed" );

  //Check the fourth child property index.
  DALI_CHECK_FAIL( childActor.GetPropertyIndex( propertyName4 ) != propertyIndex4, "GetProperty is failed" );

  //Now create another parent actor with different child properties registered
  TypeInfo typeInfo2 = typeRegistry.GetTypeInfo( "MyNamedActor" );
  DALI_CHECK_FAIL( !typeInfo2, "typeInfo2 initialization failed" );
  BaseHandle handle2 = typeInfo2.CreateInstance();
  DALI_CHECK_FAIL( !handle2, "handle2 initialization failed");
  Actor customActor2 = Actor::DownCast( handle2 );
  DALI_CHECK_FAIL( !customActor2, "customActor2 initialization failed" );

  //Register child properties to the new parent
  std::string newPropertyName( "newChildProp" );
  int newPropertyIndex( CHILD_PROPERTY_REGISTRATION_START_INDEX );
  //The same index as the first child property "childProp1" in the old parent
  Property::Type newPropertyType( Property::VECTOR2 );
  ChildPropertyRegistration newChildProperty( namedActorType, newPropertyName, newPropertyIndex, newPropertyType );

  std::string newPropertyName2( "childProp3" );
  //The same name as the third child property in the old parent
  int newPropertyIndex2( CHILD_PROPERTY_REGISTRATION_START_INDEX + 1 );
  //The same index as the second child property "childProp2" in the old parent
  Property::Type newPropertyType2( Property::FLOAT );
  //The same type as the third child property in the old parent
  ChildPropertyRegistration newChildProperty2( namedActorType, newPropertyName2, newPropertyIndex2, newPropertyType2 );

  //Now move the child actor to the new parent
  customActor2.Add( childActor );

  //"childProp1" is not a valid child property supported by the new parent, so nothing changed
  DALI_CHECK_FAIL( childActor.GetPropertyType( propertyIndex ) != propertyType, "GetProperty is failed" );
  DALI_CHECK_FAIL( childActor.GetPropertyName( propertyIndex ) != propertyName, "GetProperty is failed" );
  DALI_CHECK_FAIL( childActor.GetPropertyIndex( propertyName ) != propertyIndex, "GetProperty is failed" );

  //"childProp3" is a valid child property supported by the new parent. So it should get its new child property index and should just work

  DALI_CHECK_FAIL( childActor.GetPropertyType( newPropertyIndex2 ) != newPropertyType2, "GetProperty is failed." );
  DALI_CHECK_FAIL( childActor.GetPropertyName( newPropertyIndex2 ) != newPropertyName2, "GetProperty is failed." );
  DALI_CHECK_FAIL( childActor.GetPropertyIndex( newPropertyName2 ) != newPropertyIndex2, "GetProperty is failed." );
  DALI_CHECK_FAIL( childActor.GetProperty< float >( newPropertyIndex2 ) != 0.15f, "GetProperty is failed." );

  // Now register a custom property called "newChildProp"
  Property::Index customPropertyIndex3 = childActor.RegisterProperty("newChildProp", Vector2( 10.0f, 10.0f ), Property::READ_WRITE);

  // Check that the custom property is created
  DALI_CHECK_FAIL( initialChildActorPropertyCount + 5u != childActor.GetPropertyCount(), "GetProperty is failed" );

  //This is a valid child property registered to the new parent So should be able to access it through both its custom property index and its registered child property index
  DALI_CHECK_FAIL( childActor.GetPropertyType( newPropertyIndex ) != newPropertyType, "GetProperty is failed" );
  DALI_CHECK_FAIL( childActor.GetPropertyType( customPropertyIndex3 ) != newPropertyType, "GetProperty is failed" );
  DALI_CHECK_FAIL( childActor.GetPropertyName( newPropertyIndex ) != newPropertyName, "GetProperty is failed" );
  //This should return the new name, although the child property index remains the same
  DALI_CHECK_FAIL( childActor.GetPropertyName( customPropertyIndex3 ) != newPropertyName, "GetProperty is failed");
  DALI_CHECK_FAIL( childActor.GetProperty< Vector2 >( newPropertyIndex ) != Vector2( 10.0f, 10.0f ), "GetProperty is failed" );
  DALI_CHECK_FAIL( childActor.GetProperty< Vector2 >( customPropertyIndex3 ) != Vector2( 10.0f, 10.0f ), "GetProperty is failed" );

  //Should return the child property index by given its name
  DALI_CHECK_FAIL( childActor.GetPropertyIndex( newPropertyName ) != newPropertyIndex, "GetProperty is failed" );

  DaliLog::PrintPass();
}

void TypeRegistryChildPropertyRegistrationN()
{
  // Attempt to register a child property type out-of-bounds index (less than)
  try
  {
    ChildPropertyRegistration property1( customType1, "propName", CHILD_PROPERTY_REGISTRATION_START_INDEX - 1, Property::BOOLEAN);
  }
  catch ( DaliException& e )
  {
    DALI_CHECK_FAIL( false, "ChildPropertyRegistration test case is failed" );
  }

  // Attempt to register a child property type out-of-bounds index (greater than)
  try
  {
    ChildPropertyRegistration property1( customType1, "propName", CHILD_PROPERTY_REGISTRATION_MAX_INDEX + 1, Property::BOOLEAN );
  }
  catch ( DaliException& e )
  {
    DALI_CHECK_FAIL( false, "ChildPropertyRegistration test case is failed" );
  }

  DaliLog::PrintPass();
}

void TypeRegisterChildProperties()
{
  TypeRegistry typeRegistry = TypeRegistry::Get();

  // Register child properties on a type via name
  auto customActorTypeInfo = typeRegistry.GetTypeInfo( typeid(CustomActor) );
  auto myCustomTypeInfo = typeRegistry.GetTypeInfo( typeid(MyTypeRegistryTestCustomActor) );
  DALI_CHECK_FAIL( !customActorTypeInfo, "GetTypeInfo is failed" );
  DALI_CHECK_FAIL( !myCustomTypeInfo, "GetTypeInfo is failed" );

  const Property::Index WIDTH_SPECIFICATION( CHILD_PROPERTY_REGISTRATION_START_INDEX );
  const Property::Index HEIGHT_SPECIFICATION( CHILD_PROPERTY_REGISTRATION_START_INDEX + 1);

  ChildPropertyRegistration property1( customActorTypeInfo.GetName(), "widthSpecification", WIDTH_SPECIFICATION, Property::INTEGER );
  ChildPropertyRegistration property2( customActorTypeInfo.GetName(), "heightSpecification", HEIGHT_SPECIFICATION, Property::INTEGER );

  auto customActor = MyTypeRegistryTestCustomActor::New();
  Stage::GetCurrent().Add( customActor );
  auto child = Actor::New();
  customActor.Add( child );

  child.SetProperty( WIDTH_SPECIFICATION, 33 );
  DALI_CHECK_FAIL( child.GetProperty< int >( WIDTH_SPECIFICATION ) != 33, "ChildPropertyRegistration is failed." );

  child.SetProperty( HEIGHT_SPECIFICATION, 44 );
  DALI_CHECK_FAIL( child.GetProperty< int >( HEIGHT_SPECIFICATION ) != 44, "ChildPropertyRegistration is failed." );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase                UtcDaliTypeRegistryGetTypeP
 * @since_Tizen             2.4
 * @description             To check the typeregistry retrieve the getType Properly
 */
int UtcDaliTypeRegistryGetTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_GET_TYPE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryConstructorP
 * @since_Tizen             2.4
 * @description             To check the typeregistry constructor Properly
 */
int UtcDaliTypeRegistryConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryCopyConstructorP
 * @since_Tizen             2.4
 * @description             To check the typeregistry copy constructor Properly
 */
int UtcDaliTypeRegistryCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryCopyConstructorP2
 * @since_Tizen             2.4
 * @description             Copy and assign a typeregistry
 */
int UtcDaliTypeRegistryCopyConstructorP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_COPY_CONSTRUCTOR_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryOperatorAssignmentP
 * @since_Tizen             2.4
 * @description             To check the typeregistry assignment operator Properly
 */
int UtcDaliTypeRegistryOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_ASSIGNMENT_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryGetTypeInfoP
 * @since_Tizen             2.4
 * @description             To check the typeregistry retrieve the getTypeInfo Properly
 */
int UtcDaliTypeRegistryGetTypeInfoP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_GET_TYPE_INFO_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryGetTypeInfoP2
 * @since_Tizen             2.4
 * @description             To check the typeregistry retrieve the getTypeInfo Properly
 */
int UtcDaliTypeRegistryGetTypeInfoP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_GET_TYPE_INFO_P2);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase                UtcDaliTypeRegistryGetTypeNameCountP
 * @since_Tizen             2.4
 * @description             To check the typeregistry retrieve the getTypeNameCount Properly
 */
int UtcDaliTypeRegistryGetTypeNameCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_GET_TYPE_P_NAME_COUNT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryGetTypeNamesP
 * @since_Tizen             2.4
 * @description             To check the typeregistry retrieve the getTypeNames Properly
 */
int UtcDaliTypeRegistryGetTypeNamesP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_GET_TYPE_P_NAMES_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryPropertyRegistrationP
 * @since_Tizen             2.4
 * @description             constructor registers the property with the registered type.
 */
int UtcDaliTypeRegistryPropertyRegistrationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_PROPERTY_REGISTRATION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryRegisteredNameP
 * @since_Tizen             2.4
 * @description             Constructor registers the type creation function For registered NamedType.
 */
int UtcDaliTypeRegistryRegisteredNameP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_REGISTERED_NAME_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistrySignalConnectorTypeP
 * @since_Tizen             2.4
 * @description             Register a signal connector function to a registered type.
 */
int UtcDaliTypeRegistrySignalConnectorTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_SIGNAL_CONNECTOR_TYPE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistrySignalConnectorTypeN
 * @since_Tizen             2.4
 * @description             Negative test for signal connector function.
 */
int UtcDaliTypeRegistrySignalConnectorTypeN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_SIGNAL_CONNECTOR_TYPE_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryTypeActionP
 * @since_Tizen             2.4
 * @description             checks the registeration an action function.
 */
int UtcDaliTypeRegistryTypeActionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_TYPE_ACTION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryTypeActionN
 * @since_Tizen             2.4
 * @description             Negative check for registeration of an action function.
 */
int UtcDaliTypeRegistryTypeActionN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_TYPE_ACTION_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryTypeRegistrationNotCallingCreateOnInitP
 * @since_Tizen             2.4
 * @description             Constructor registers the type creation function without CallingCreateOnInit
 */
int UtcDaliTypeRegistryTypeRegistrationNotCallingCreateOnInitP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_TYPE_REGISTRATION_NOT_CALLING_CREATE_ON_INIT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryTypeRegistrationCallingCreateOnInitP
 * @since_Tizen             2.4
 * @description             Constructor registers the type creation function wiht CallingCreateOnInit
 */
int UtcDaliTypeRegistryTypeRegistrationCallingCreateOnInitP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_TYPE_REGISTRATION_CALLING_CREATE_ON_INIT_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryTypeRegistrationForNamedTypeP
 * @since_Tizen             2.4
 * @description             Constructor registers the type creation function ForNamedType.
 */
int UtcDaliTypeRegistryTypeRegistrationForNamedTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_TYPE_REGISTRATION_FOR_NAMED_TYPE_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryChildPropertyRegistrationP
 * @since_Tizen             2.4
 * @description             Function that tests ChildPropertyRegistration API.
 */
int UtcDaliTypeRegistryChildPropertyRegistrationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_CHILD_PROPERTY_REGISTRATION_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegistryChildPropertyRegistrationN
 * @since_Tizen             2.4
 * @description             Function that tests ChildPropertyRegistration API.
 */
int UtcDaliTypeRegistryChildPropertyRegistrationN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_CHILD_PROPERTY_REGISTRATION_N );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliTypeRegisterChildProperties
 * @since_Tizen             5.0
 * @description             Function that tests Dali::ChildPropertyRegistration.
 */
int UtcDaliTypeRegisterChildProperties(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Type_Registry_TestApp testApp( application, TYPE_REGISTRY_CHILD_PROPERTIES );
  application.MainLoop();
  return test_return_value;
}
