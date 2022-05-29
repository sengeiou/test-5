#include "utc-dali-custom-actor-impl-common.h"

int gRenderCountCustomActor1;
bool gReqWheelEvent1;

namespace
{
  std::vector< std::string > masterCallStack;
}


namespace
{
  struct KeyEventSignalData
  {
    KeyEventSignalData() : m_bFunctorCalled(false)
    {

    }

    void Reset()
    {
      m_bFunctorCalled = false;

      m_KeyEvent.keyModifier = MODIFIER_INVALID;
      m_KeyEvent.keyPressedName.clear();
      m_KeyEvent.keyPressed.clear();
    }

    bool m_bFunctorCalled;
    KeyEvent m_KeyEvent;
  };

  struct KeyEventReceivedFunctor
  {
    KeyEventReceivedFunctor( KeyEventSignalData& data ) : m_signalData( data )
    {

    }

    bool operator()( const KeyEvent& keyEvent )
    {
      m_signalData.m_bFunctorCalled = true;
      m_signalData.m_KeyEvent = keyEvent;

      return true;
    }

    KeyEventSignalData& m_signalData;
  };

  struct TouchedSignalData
  {
    TouchedSignalData() : m_bFunctorCalled(false)
    {

    }

    void Reset()
    {
      m_bFunctorCalled = false;

      m_receivedTouchEvent.points.clear();
      m_receivedTouchEvent.time = 0;
    }

    bool m_bFunctorCalled;
    TouchEvent m_receivedTouchEvent;
  };

  struct TouchedFunctor
  {
    TouchedFunctor( TouchedSignalData& data ) : m_singleData( data )
    {

    }

    void operator()( const TouchEvent& touch )
    {
      m_singleData.m_bFunctorCalled = true;
      m_singleData.m_receivedTouchEvent = touch;
    }

    TouchedSignalData& m_singleData;
  };
}


namespace
{
  struct SignalData
  {
    SignalData() : m_bFunctorCalled(false)
    {

    }

    void Reset()
    {
      m_bFunctorCalled = false;

      m_receivedKeyEvent.keyModifier = MODIFIER_INVALID;
      m_receivedKeyEvent.keyPressedName.clear();
      m_receivedKeyEvent.keyPressed.clear();

      m_keyedActor.Reset();
    }

    bool m_bFunctorCalled;
    KeyEvent m_receivedKeyEvent;
    Actor m_keyedActor;
  };
}

namespace Impl
{
  struct TestCustomActor : public CustomActorImpl
  {
    /**
     * Constructor
     */
    TestCustomActor()
      :     CustomActorImpl( (ActorFlags)(REQUIRES_TOUCH_EVENTS | REQUIRES_HOVER_EVENTS | REQUIRES_WHEEL_EVENTS) ), //requires touch, hover and wheel events only
      m_property( Property::INVALID_INDEX ),
      m_vec3SizeSet( Vector3::ZERO ),
      m_targetSize( Vector3::ZERO ),
      m_nDepth(0)
    {
    }

    /**
     * Destructor
     */
    virtual ~TestCustomActor()
    {

    }

    void Initialize( const char* pchName = NULL )
    {
      m_property = Self().RegisterProperty( CUSTOMACTORIMPL_PROPERTIES[DALI], CUSTOMACTORIMPL_VALUES[DALI], Property::READ_WRITE);
      OnInitialize( pchName );
    }

    virtual void OnInitialize( const char* pchName )
    {
      ResetCallStack();
    }

    /**
     * Resets the call stack
     */
    void ResetCallStack()
    {
      m_vec3SizeSet = Vector3();
      m_targetSize = Vector3();
      m_vecMethodsCalled.clear();
    }

    void AddToCallStacks( const char* pchMethod )
    {
      m_vecMethodsCalled.push_back( pchMethod );

      // Combine Actor name with method string
      std::string strNameAndMethod( Self().GetName() );

      if (strNameAndMethod.size() == CUSTOMACTORIMPL_INVALID_LENGTH_NAME_METHOD)
      {
        strNameAndMethod = CUSTOMACTORIMPL_INVALID_NAME_METHOD;
      }
      else
      {
        strNameAndMethod += CUSTOMACTORIMPL_SEPARATOR_NAME_METHOD;
      }

      strNameAndMethod += pchMethod;

      masterCallStack.push_back( strNameAndMethod );
    }

    // From CustomActorImpl
    virtual void OnStageConnection( int nDepth )
    {
      AddToCallStacks("OnStageConnection");
      m_nDepth = nDepth;
    }

    virtual void OnStageDisconnection()
    {
      AddToCallStacks("OnStageDisconnection");
    }

    virtual void OnChildAdd(Actor& child)
    {
      AddToCallStacks("OnChildAdd");
    }

    virtual void OnChildRemove(Actor& child)
    {
      AddToCallStacks("OnChildRemove");
    }

    virtual void OnPropertySet( Property::Index index, Property::Value propertyValue )
    {
      AddToCallStacks("OnPropertySet");
    }

    virtual void OnSizeSet(const Vector3& targetSize)
    {
      m_vec3SizeSet = targetSize;
      AddToCallStacks("OnSizeSet");
    }

    virtual void OnSizeAnimation(Animation& animation, const Vector3& targetSize)
    {
      m_targetSize = targetSize;
      AddToCallStacks("OnSizeAnimation");
    }

    virtual bool OnTouchEvent(const TouchEvent& event)
    {
      AddToCallStacks("OnTouchEvent");
      return true;
    }

    virtual bool OnWheelEvent(const WheelEvent& event)
    {
      AddToCallStacks(__FUNCTION__);
      return true;
    }

    virtual bool OnKeyEvent(const KeyEvent& event)
    {
      AddToCallStacks("OnKeyEvent");
      return true;
    }

    virtual void OnKeyInputFocusGained()
    {
      AddToCallStacks("OnKeyInputFocusGained");
    }

    virtual void OnKeyInputFocusLost()
    {
      AddToCallStacks("OnKeyInputFocusLost");
    }

    virtual bool OnHoverEvent(const HoverEvent& event)
    {
      AddToCallStacks("OnHoverEvent");
      return true;
    }

    virtual Dali::Vector3 GetNaturalSize()
    {
      AddToCallStacks("GetNaturalSize");
      return Vector3::ONE;
    }

    virtual void OnRelayout( const Vector2& size, RelayoutContainer& container )
    {
      AddToCallStacks("OnRelayout");
    }

    virtual void OnSetResizePolicy( ResizePolicy::Type policy, Dimension::Type dimension )
    {
      AddToCallStacks("OnSetResizePolicy");
    }

    virtual float CalculateChildSize( const Dali::Actor& child, Dimension::Type dimension )
    {
      AddToCallStacks("CalculateChildSize");
      return child.GetCurrentSize().Length();
    }

    virtual float GetHeightForWidth( float width )
    {
      AddToCallStacks("GetHeightForWidth");
      return width;
    }

    virtual float GetWidthForHeight( float height )
    {
      AddToCallStacks("GetWidthForHeight");
      return height;
    }

    void TestRelayoutRequest()
    {
      RelayoutRequest();
      AddToCallStacks("RelayoutRequest");
      return;
    }

    virtual bool RelayoutDependentOnChildren( Dimension::Type dimension = Dimension::ALL_DIMENSIONS )
    {
      AddToCallStacks("RelayoutDependentOnChildren");
      return true;
    }

    virtual void OnCalculateRelayoutSize( Dimension::Type dimension )
    {
      AddToCallStacks("OnCalculateRelayoutSize");
      return;
    }

    virtual void OnLayoutNegotiated( float size, Dimension::Type dimension )
    {
      AddToCallStacks("OnLayoutNegotiated");
    }

    float TestGetHeightForWidthBase( float width )
    {
      return GetHeightForWidthBase( width );
    }

    float TestGetWidthForHeightBase( float height )
    {
      return GetWidthForHeightBase( height );
    }

    float TestCalculateChildSizeBase( const Dali::Actor& child, Dimension::Type dimension )
    {
      return CalculateChildSizeBase( child, dimension );
    }

    bool TestRelayoutDependentOnChildrenBase( Dimension::Type dimension )
    {
      return RelayoutDependentOnChildrenBase( dimension );
    }

    void SetDaliProperty(std::string strProperty)
    {
      Self().SetProperty(m_property, strProperty) ;
    }

    Property::Index m_property;
    std::vector< std::string > m_vecMethodsCalled;
    Vector3 m_vec3SizeSet;
    Vector3 m_targetSize;
    int m_nDepth;
  }; // class TestCustomActor

};// namespace Impl


namespace
{
  /**
   * Test custom actor handle
   */
  class TestCustomActor : public CustomActor
  {
    public:
      TestCustomActor(){}

      static TestCustomActor New()
      {
        Impl::TestCustomActor* impl = new Impl::TestCustomActor();
        if(!impl)
        {
          LOG_I("Invalid instance of Impl::TestCustomActor");
        }
        TestCustomActor custom( *impl ); // takes ownership

        impl->Initialize();
        return custom;
      }

      virtual ~TestCustomActor()
      {

      }

      Impl::TestCustomActor& GetImpl()
      {
        return static_cast<Impl::TestCustomActor&>(GetImplementation());
      }

      std::vector< std::string >& GetMethodsCalled()
      {
        return GetImpl().m_vecMethodsCalled;
      }

      void ResetCallStack()
      {
        GetImpl().ResetCallStack();
      }

      void SetDaliProperty(std::string s)
      {
        GetImpl().SetDaliProperty(s);
      }

      Vector3 GetSize()
      {
        return GetImpl().m_vec3SizeSet;
      }

      Vector3 GetTargetSize()
      {
        return GetImpl().m_targetSize;
      }

    private:

      TestCustomActor( Impl::TestCustomActor& impl ) : CustomActor( impl )
    {

    }
  };
}

TestCustomActor gCustomActor, gCustomActorImpl, gCustomActorA, gCustomActorB, gCustomActorC;

//~ TestCustomActor gTestCustomActor;
CustomActor gCustomActor1;
Actor gParentActor1;

size_t CustomActorImplGetMasterStackSize1(std::string strName)
{
  std::vector< std::string > vecNames;
  for (std::vector<std::string>::iterator it = masterCallStack.begin() ; it != masterCallStack.end(); ++it)
  {
    if(static_cast<std::string>(*it).find(strName) != string::npos)
    {
      vecNames.push_back(static_cast<std::string>(*it));
    }
  }

  return vecNames.size();
}

void CustomActorImplRequiresHoverEventsP()
{
  bool bReqiresHoverEvent = false;
  const unsigned long ulTime = 1000ul;
  try
  {
    HoverEvent hoverEvent(ulTime);
    TestCustomActor testCustomActor = TestCustomActor::New();
    DALI_CHECK_FAIL(!testCustomActor, "TestCustomActor::New() is failed.");
    CustomActorImpl& customActorGetImplementation = testCustomActor.GetImplementation();
    DALI_CHECK_FAIL(!(&customActorGetImplementation), "CustomActor::GetImplementation is failed.");
    bReqiresHoverEvent = customActorGetImplementation.RequiresHoverEvents();
    DALI_CHECK_FAIL(!bReqiresHoverEvent, "CustomActorImpl::RequiresHoverEvents does not set.");
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();
}

void CustomActorImplGetNaturalSizeP()
{
  gCustomActorImpl =TestCustomActor::New() ;
  DALI_CHECK_FAIL(!gCustomActorImpl, "TestCustomActor::New is failed.");
  gCustomActorImpl.SetName("actor");
  gCustomActorImpl.Add(Actor::New());
  Stage::GetCurrent().Add(gCustomActorImpl);
}

void VTCustomActorImplGetNaturalSize001()
{
  //Vector3 vec3NaturalSize = gCustomActorImpl.GetImplementation().GetNaturalSize();
  DALI_CHECK_FAIL( !(int)(gCustomActorImpl.GetMethodsCalled().size()) , "Invalid number of methods called by the custom actor object.");

  Stage::GetCurrent().Remove(gCustomActorImpl);
  DaliLog::PrintPass();
}

void CustomActorImplOnChildAddP()
{
  TestCustomActor custom = TestCustomActor::New();

  Actor aChild = Actor::New();
  custom.Add( aChild );

  DALI_CHECK_FAIL( 2 != (int)(custom.GetMethodsCalled().size()), "On removing child failed" );
  DaliLog::PrintPass();
}

void VTCustomActorImplOnChildAdd001()
{
  if(CustomActorImplGetMasterStackSize1(gCustomActorA.GetName()) != (gCustomActorA.GetMethodsCalled().size()))
  {
    LOG_E("custom actor called invalid number of methods call");
    Stage::GetCurrent().Remove(gCustomActorA);
    Stage::GetCurrent().Remove(gCustomActorC);
    test_return_value=1;
    return;
  }

  if(!CustomActorImplHasMethod1(GET_METHOD(OnChildAdd), gCustomActorA.GetMethodsCalled()))
  {
    LOG_E("CustomActorImpl::OnChildAdd does not added to master stack");
    Stage::GetCurrent().Remove(gCustomActorA);
    Stage::GetCurrent().Remove(gCustomActorC);
    test_return_value=1;
    return;
  }

  if(!CustomActorImplHasMethod1(GET_METHOD(RelayoutDependentOnChildren), gCustomActorA.GetMethodsCalled()))
  {
    LOG_E("CustomActorImpl::RelayoutDependentOnChildren does not added to master stack");
    Stage::GetCurrent().Remove(gCustomActorA);
    Stage::GetCurrent().Remove(gCustomActorC);
    test_return_value=1;
    return;
  }

  if(!CustomActorImplHasMethod1(GET_METHOD(OnStageConnection), gCustomActorA.GetMethodsCalled()))
  {
    LOG_E("CustomActorImpl::OnStageConnection does not added to master stack");
    Stage::GetCurrent().Remove(gCustomActorA);
    Stage::GetCurrent().Remove(gCustomActorC);
    test_return_value=1;
    return;
  }

  Stage::GetCurrent().Remove(gCustomActorA);
  DaliLog::PrintPass();
}

void CustomActorImplOnChildRemoveP()
{
  TestCustomActor custom = TestCustomActor::New();
  Actor aChild = Actor::New();
  custom.Add( aChild );

  custom.Remove( aChild );

  DALI_CHECK_FAIL( !(int)(custom.GetMethodsCalled().size()) , "On removing child failed" );

  DaliLog::PrintPass();
}

void VTCustomActorImplOnChildRemove001()
{
  gCustomActorA.Remove(gCustomActorB);
}

void VTCustomActorImplOnChildRemove002()
{
  if(CustomActorImplGetMasterStackSize1(gCustomActorA.GetName()) != (gCustomActorA.GetMethodsCalled().size()))
  {
    LOG_E("Invalid number of methods called by the custom actor");
    test_return_value=1;
    return;
  }

  DALI_CHECK_FAIL( !CustomActorImplHasMethod1(GET_METHOD(OnChildAdd), gCustomActorA.GetMethodsCalled()), "CustomActorImpl::OnChildAdd does not added to the master stack");

  DALI_CHECK_FAIL( !CustomActorImplHasMethod1(GET_METHOD(OnChildRemove), gCustomActorA.GetMethodsCalled()), "CustomActorImpl::OnChildRemove does not added to the master stack");

  DaliLog::PrintPass();
}

void CustomActorImplOnKeyEventP()
{
  const char* KEY_NAME = "at the rate of"; //"alpha";
  const char* KEY_STRING = "@"; //"i";
  const int nKeyCode = 99;
  const unsigned long ulTimeStamp = 0;

  KeyEvent event(KEY_NAME, KEY_STRING, nKeyCode, MODIFIER_SHIFT, ulTimeStamp, KeyEvent::Down);
  try
  {
    TestCustomActor customActor = TestCustomActor::New();
    DALI_CHECK_FAIL(!customActor, "CustomActor()::New() is failed");

    Impl::TestCustomActor &testCustomActor = customActor.GetImpl();

    DALI_CHECK_FAIL(!(&testCustomActor), "CustomActor()::GetImplementation() is failed");
    bool bOnKeyEvent = testCustomActor.OnKeyEvent(event);

    DALI_CHECK_FAIL(!bOnKeyEvent, "CustomActorImpl::OnKeyEvent returns false");

    DALI_CHECK_FAIL(customActor.GetMethodsCalled()[FIRST] != GET_METHOD(OnKeyEvent), "SimpleTestCustomActor::OnKeyEvent does not added to the master stack.");
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();
}

void CustomActorImplOnKeyInputFocusGainedP()
{
  try
  {
    TestCustomActor customActor = TestCustomActor::New();
    DALI_CHECK_FAIL(!customActor, "CustomActor()::New() is failed");

    Impl::TestCustomActor &testCustomActor = customActor.GetImpl();
    DALI_CHECK_FAIL(!(&testCustomActor), "CustomActor::GetImplementation is failed");

    testCustomActor.OnKeyInputFocusGained();
    DALI_CHECK_FAIL(customActor.GetMethodsCalled()[FIRST] != GET_METHOD(OnKeyInputFocusGained), "CustomActorImpl::OnKeyInputFocusGained is not added to the master stack.");
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();
}

void CustomActorImplOnKeyInputFocusLostP()
{
  try
  {
    TestCustomActor customActor = TestCustomActor::New();
    DALI_CHECK_FAIL(!customActor, "CustomActor()::New() is failed");

    Impl::TestCustomActor &testCustomActor = customActor.GetImpl();
    DALI_CHECK_FAIL(!(&testCustomActor), "CustomActor::GetImplementation is failed");

    testCustomActor.OnKeyInputFocusLost();
    DALI_CHECK_FAIL(customActor.GetMethodsCalled()[FIRST] != GET_METHOD(OnKeyInputFocusLost), "CustomActorImpl::OnKeyInputFocusLost does not set to the master stack");
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}

void CustomActorImplOnWheelEventP()
{
  float fX = 0.0f, fY = 0.0f;
  const float X_OFFSET = 0.12f, Y_OFFSET = 0.15f;
  unsigned int ulTimeStamp = 1000u;

  fY += Y_OFFSET;
  fX += X_OFFSET;
  Vector2 screenCoordinates( fX, fY );
  WheelEvent event(WheelEvent::MOUSE_WHEEL, WHEEL_DIRECTION_VERTICAL, MODIFIER_SHIFT, screenCoordinates, WHEEL_ROLLING_OFFSET_ROLLDOWN, ulTimeStamp);
  gCustomActor = TestCustomActor::New();
  DALI_CHECK_FAIL(!gCustomActor, "TestCustomActor::New is failed");

  gCustomActor.SetName("actor");
  Impl::TestCustomActor &testCustomActor = gCustomActor.GetImpl();
  DALI_CHECK_FAIL(!(&testCustomActor), "CustomActor::GetImplementation is failed");
  testCustomActor.OnWheelEvent(event);
}

void VTCustomActorImplOnWheelEvent001()
{
  DALI_CHECK_FAIL(gCustomActor.GetMethodsCalled()[ FIRST ] != GET_METHOD(OnWheelEvent), "CustomActorImpl::OnWheelEvent is not set to the master stack");

  DaliLog::PrintPass();
}

void CustomActorImplOnSizeSetP()
{
  TestCustomActor custom = TestCustomActor::New();

  custom.SetSize( Vector2( 9.0f, 10.0f ) );
  DALI_CHECK_FAIL( (int)(custom.GetMethodsCalled().size()) != 2 , "Set Size not added to stack" );

  DaliLog::PrintPass();
}

void VTCustomActorImplOnSizeSet001()
{
  if(CustomActorImplGetMasterStackSize1(gCustomActorA.GetName()) != (gCustomActorA.GetMethodsCalled().size()))
  {
    LOG_E("Invalid number of methods called by custom actor implementation object");
    Stage::GetCurrent().Remove( gCustomActorA );
    test_return_value=1;
    return;
  }

  if( !CustomActorImplHasMethod1(GET_METHOD(OnSetResizePolicy), gCustomActorA.GetMethodsCalled()))
  {
    LOG_E("CustomActorImpl::OnSizeSet does not added to the master stack");
    Stage::GetCurrent().Remove( gCustomActorA );
    test_return_value=1;
    return;
  }
  Stage::GetCurrent().Remove( gCustomActorA );

  DaliLog::PrintPass();
}

void CustomActorImplOnStageConnectionP()
{
  TestCustomActor custom = TestCustomActor::New();

  // add the custom actor to stage
  Stage::GetCurrent().Add( custom );

  DALI_CHECK_FAIL( (int)(custom.GetMethodsCalled().size()) != 1 , "Mismatch" );
  Stage::GetCurrent().Remove( custom );

  DALI_CHECK_FAIL( (int)(custom.GetMethodsCalled().size()) != 2, "Mismatch" );
  DaliLog::PrintPass();
}

void VTCustomActorImplOnStageConnection001()
{
  if(CustomActorImplGetMasterStackSize1(gCustomActorA.GetName()) != (gCustomActorA.GetMethodsCalled().size()))
  {
    LOG_E("Invalid number of methods called");
    Stage::GetCurrent().Remove( gCustomActorA );
    test_return_value=1;
    return;
  }
  if( GET_METHOD(OnStageConnection) != gCustomActorA.GetMethodsCalled()[ FIRST ] )
  {
    LOG_E("CustomActorImpl::OnStageConnection does not added to the master stack");
    Stage::GetCurrent().Remove( gCustomActorA );
    test_return_value=1;
    return;
  }
  Stage::GetCurrent().Remove( gCustomActorA );

  DaliLog::PrintPass();
}

void CustomActorImplOnStageDisconnectionP()
{
  TestCustomActor custom = TestCustomActor::New();

  // add the custom actor to stage
  Stage::GetCurrent().Add( custom );

  DALI_CHECK_FAIL( (int)(custom.GetMethodsCalled().size()) != 1 , "Mismatch" );
  Stage::GetCurrent().Remove( custom );

  DALI_CHECK_FAIL( (int)(custom.GetMethodsCalled().size()) != 2, "Mismatch" );
  DaliLog::PrintPass();
}

void VTCustomActorImplOnStageDisconnection001()
{
  Stage::GetCurrent().Remove( gCustomActorA );
}

void VTCustomActorImplOnStageDisconnection002()
{
  DALI_CHECK_FAIL(CustomActorImplGetMasterStackSize1(gCustomActorA.GetName()) != (gCustomActorA.GetMethodsCalled().size()),
      "invalid numbers of method called by the custom actor object");
  DALI_CHECK_FAIL(!CustomActorImplHasMethod1(GET_METHOD(OnStageDisconnection), gCustomActorA.GetMethodsCalled()) ,
      "CustomActorImpl::OnStageDisconnection does not added to the master stack");

  DaliLog::PrintPass();
}

void CustomActorImplOnTouchEventP()
{
  float fX = 0.0f, fY = 0.0f;
  const float Y_OFFSET = 0.15f, X_OFFSET = 0.12f;
  int nTouchDeviceId = 0;
  bool bOnTouchEvent = false;

  try
  {
    fX += X_OFFSET;
    fY += Y_OFFSET;
    TouchEvent touchEvent;
    touchEvent.points.push_back( TouchPoint( nTouchDeviceId, TouchPoint::Down, fX, fY ) );
    TestCustomActor customActor = TestCustomActor::New();
    DALI_CHECK_FAIL(!customActor, "TestCustomActor::New is failed");
    Impl::TestCustomActor &testCustomActor = customActor.GetImpl();
    DALI_CHECK_FAIL(!(&testCustomActor), "CustomActor::GetImplementation is failed");
    bOnTouchEvent = testCustomActor.OnTouchEvent(touchEvent);
    DALI_CHECK_FAIL(!bOnTouchEvent, "CustomActorImpl::OnTouchEvent returns false");
    DALI_CHECK_FAIL(customActor.GetMethodsCalled()[FIRST] != GET_METHOD(OnTouchEvent), "TestCustomActor::OnTouchEvent does not set to the master stack");
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();
}

void CustomActorImplRequiresWheelEventsP(void)
{
  float fX = 0.0f, fY = 0.0f;
  const float Y_OFFSET = 0.15f, X_OFFSET = 0.12f;
  unsigned int ulTimeStamp = 1000u;
  fY += Y_OFFSET;
  fX += X_OFFSET;
  Vector2 screenCoordinates( fX, fY );
  WheelEvent event(WheelEvent::MOUSE_WHEEL, WHEEL_DIRECTION_VERTICAL, MODIFIER_SHIFT, screenCoordinates, WHEEL_ROLLING_OFFSET_ROLLDOWN, ulTimeStamp);
  gCustomActor = TestCustomActor::New();
  DALI_CHECK_FAIL(!gCustomActor, "CustomActor::New is failed");
  gCustomActor.SetName("actor");
  Impl::TestCustomActor &testCustomActor = gCustomActor.GetImpl();
  DALI_CHECK_FAIL(!(&testCustomActor), "CustomActor::GetImplementation is failed.");
  gReqWheelEvent1 = testCustomActor.RequiresWheelEvents();
  DALI_CHECK_FAIL(!testCustomActor.OnWheelEvent(event), "CustomActorImpl::OnWheelEvent is failed: event did not consume.");
}

void VTCustomActorImplRequiresWheelEvents001()
{
  DALI_CHECK_FAIL(gCustomActor.GetMethodsCalled()[ FIRST ] != GET_METHOD(OnWheelEvent), "CustomActorImpl::OnWheelEvent is not set on event");
  DALI_CHECK_FAIL(!gReqWheelEvent1, "CustomActorImpl::RequiresWheelEvents is failed");

  DaliLog::PrintPass();
}

void CustomActorImplRequiresTouchEventsP()
{
  try
  {
    TestCustomActor testCustomActor = TestCustomActor::New();
    DALI_CHECK_FAIL(!testCustomActor, "CustomActor::New is failed");
    CustomActorImpl& customActorGetImplementation = testCustomActor.GetImplementation();
    DALI_CHECK_FAIL(!(&customActorGetImplementation), "CustomActor::GetImplementation is failed");
    DALI_CHECK_FAIL(!customActorGetImplementation.RequiresTouchEvents(), "CustomActorImpl::RequiresTouchEvents returns false");
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();
}

void CustomActorImplSelfP()
{
  float fX = 0.0f, fY = 0.0f;
  const float Y_OFFSET = 0.15f, X_OFFSET = 0.12f;
  unsigned int ulTimeStamp = 1000u;

  try
  {
    Vector2 screenCoordinates( fX, fY );
    WheelEvent event(WheelEvent::MOUSE_WHEEL, WHEEL_DIRECTION_VERTICAL, MODIFIER_SHIFT, screenCoordinates, WHEEL_ROLLING_OFFSET_ROLLDOWN, ulTimeStamp);
    fY += Y_OFFSET; fX += X_OFFSET;
    TestCustomActor customActor = TestCustomActor::New();
    DALI_CHECK_FAIL(!customActor, "CustomActor::New is failed");
    Impl::TestCustomActor &testCustomActor = customActor.GetImpl();
    DALI_CHECK_FAIL(!(&testCustomActor), "CustomActor::GetImplementation is failed");
    CustomActor customActorSelf = testCustomActor.Self();
    DALI_CHECK_FAIL(!customActorSelf, "CustomActorImpl::Self is failed: invalid instance.");
    CustomActor customActorTestObject = CustomActor::DownCast(customActor);
    DALI_CHECK_FAIL(!customActorTestObject, "CustomActor::DownCast is failed: casting failure.");
    DALI_CHECK_FAIL(customActorTestObject != customActorSelf, "CustomActorImpl::Self returns invalid CustomActor object");
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();
}

void CustomActorImplSetRequiresWheelEventsP()
{
  try
  {
    TestCustomActor testCustomActor = TestCustomActor::New();
    DALI_CHECK_FAIL(!testCustomActor, "CustomActor::New is failed");
    CustomActorImpl& customActorGetImplementation = testCustomActor.GetImplementation();
    DALI_CHECK_FAIL(!(&customActorGetImplementation), "CustomActor::GetImplementation is failed");
    DALI_CHECK_FAIL(!customActorGetImplementation.RequiresWheelEvents(), "CustomActorImpl::SetRequiresWheelEvents does not set.");
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();
}

void CustomActorImplCustomActorImplWithBoolParamP()
{
  try
  {
    TestCustomActor testCustomActor = TestCustomActor::New();
    DALI_CHECK_FAIL(!testCustomActor, "TestCustomActor::New is failed.");
    Impl::TestCustomActor& customActorGetImplementation = testCustomActor.GetImpl();
    DALI_CHECK_FAIL(!(&customActorGetImplementation), "CustomActor::GetImplementation is failed: invalid instance.");
    bool bReqWheelEvent = customActorGetImplementation.RequiresTouchEvents();
    DALI_CHECK_FAIL(!bReqWheelEvent, "CustomActorImpl::RequiresTouchEvents returns false: CustomActorImpl::CustomActorImpl(bool) is failed to set touch events requirement.");
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();
}

void CustomActorImplRelayoutRequestP()
{
  const Vector2 kVec2ActorSize(10.6f, 5.3f);
  gCustomActorA = TestCustomActor::New();
  DALI_CHECK_FAIL(!gCustomActorA, "TestCustomActor::New is failed.");
  gCustomActorA.SetSize( kVec2ActorSize );
  gCustomActorA.SetName( CUSTOMACTORIMPL_ACTORS[A]    );
  gCustomActorB = TestCustomActor::New();
  DALI_CHECK_FAIL(!gCustomActorB, "TestCustomActor::New is failed.");
  gCustomActorB.SetSize( kVec2ActorSize );
  gCustomActorB.SetName( CUSTOMACTORIMPL_ACTORS[B] );
  gCustomActorA.Add( gCustomActorB );
  Stage::GetCurrent().Add( gCustomActorA );
  gCustomActorA.GetImpl().TestRelayoutRequest();
}

void VTCustomActorImplRelayoutRequest001()
{
  if(!CustomActorImplHasMethod1(GET_METHOD(OnRelayout), gCustomActorA.GetMethodsCalled()))
  {
    LOG_E("CustomActorImpl::RelayoutRequest is failed. OnRelayout method did not call.");
    Stage::GetCurrent().Remove( gCustomActorA );
    test_return_value=1;
    return;
  }

  Stage::GetCurrent().Remove( gCustomActorA );
  DaliLog::PrintPass();
}

void CustomActorImplGetExtensionP()
{
  const Vector2 kVec2ActorSize(10.6f, 5.3f);
  TestCustomActor testCustomActorA = TestCustomActor::New();
  DALI_CHECK_FAIL(!testCustomActorA, "TestCustomActor::New is failed.");

  try
  {
    testCustomActorA.SetSize( kVec2ActorSize );
    testCustomActorA.SetName( CUSTOMACTORIMPL_ACTORS[A]    );
    TestCustomActor testCustomActorB = TestCustomActor::New();
    DALI_CHECK_FAIL(!testCustomActorB, "TestCustomActor::New is failed.");
    testCustomActorB.SetSize( kVec2ActorSize );
    testCustomActorB.SetName( CUSTOMACTORIMPL_ACTORS[B] );
    testCustomActorA.Add( testCustomActorB );
    Stage::GetCurrent().Add( testCustomActorA );
    DALI_CHECK_FAIL(testCustomActorA.GetImplementation().GetExtension(), "CustomActorImpl::GetExtension() is failed.");
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    Stage::GetCurrent().Remove( testCustomActorA );
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    Stage::GetCurrent().Remove( testCustomActorA );
    test_return_value=1;
    return;
  }
  Stage::GetCurrent().Remove( testCustomActorA );
  DaliLog::PrintPass();
}

void CustomActorImplOnPropertySetP()
{
  TestCustomActor custom = TestCustomActor::New();
  DALI_CHECK_FAIL( 0 != (int)(custom.GetMethodsCalled().size()), "Wrong Size while creating" );

  custom.SetDaliProperty("yes");

  DALI_CHECK_FAIL( 1 != (int)(custom.GetMethodsCalled().size()), "OnPropertySet() is failed " );
  DALI_CHECK_FAIL(custom.GetMethodsCalled()[ FIRST ] != GET_METHOD(OnPropertySet), "CustomActorImpl::OnPropertySet is not set to the master stack");

  DaliLog::PrintPass();
}

void CustomActorOnSizeAnimationP(void)
{
  gCustomActorImpl = TestCustomActor::New();
  DALI_CHECK_FAIL(!gCustomActorImpl, "TestCustomActor::New is failed.");

  Animation anim = Animation::New( 0.1f );
  anim.AnimateTo( Property( gCustomActorImpl, Actor::Property::SIZE ), Vector3( 8.0f, 9.0f, 10.0f ) );
  anim.Play();
}

void VTCustomActorOnSizeAnimation001()
{
  DALI_CHECK_FAIL( 1 != (int)(gCustomActorImpl.GetMethodsCalled().size()), "Property Not Added");
  DALI_CHECK_FAIL(gCustomActorImpl.GetMethodsCalled()[ FIRST ] != GET_METHOD(OnSizeAnimation), "CustomActorImpl::OnSizeAnimation is not set to the master stack");
  DALI_CHECK_FAIL( 8.0f != gCustomActorImpl.GetTargetSize().width, "Width does not match" );
  DALI_CHECK_FAIL( 9.0f != gCustomActorImpl.GetTargetSize().height, "Height does not match" );
  DALI_CHECK_FAIL( 10.0f != gCustomActorImpl.GetTargetSize().depth, "Depth does not match" );

  Stage::GetCurrent().Remove(gCustomActorImpl);
  DaliLog::PrintPass();
}

void CustomActorOnHoverEventP(void)
{
  float fX = 0.0f, fY = 0.0f;
  const float Y_OFFSET = 0.15f, X_OFFSET = 0.12f;
  int nHoverDeviceId = 0;
  bool bOnHoverEvent = false;

  try
  {
    fX += X_OFFSET;
    fY += Y_OFFSET;
    HoverEvent hoverEvent;
    hoverEvent.points.push_back( TouchPoint( nHoverDeviceId, TouchPoint::Motion, fX, fY ) );
    TestCustomActor customActor = TestCustomActor::New();
    DALI_CHECK_FAIL(!customActor, "TestCustomActor::New is failed");
    Impl::TestCustomActor &testCustomActor = customActor.GetImpl();
    DALI_CHECK_FAIL(!(&testCustomActor), "CustomActor::GetImplementation is failed");
    bOnHoverEvent = testCustomActor.OnHoverEvent(hoverEvent);
    DALI_CHECK_FAIL(!bOnHoverEvent, "CustomActorImpl::OnHoverEvent returns false");
    DALI_CHECK_FAIL(customActor.GetMethodsCalled()[FIRST] != GET_METHOD(OnHoverEvent), "TestCustomActor::OnHoverEvent does not set to the master stack");
  }
  catch(DaliException& de)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();
}

void CustomActorImplGetHeightForWidthBaseP(void)
{
  TestCustomActor customActor = TestCustomActor::New();
  DALI_CHECK_FAIL(!customActor, "CustomActor()::New() is failed");

  Impl::TestCustomActor &testCustomActor = customActor.GetImpl();
  DALI_CHECK_FAIL(!(&testCustomActor), "CustomActor::GetImplementation is failed");
  float width = 300.0f;
  float v = 0.0f;

  v = customActor.GetHeightForWidth( width );
  DALI_CHECK_FAIL( v != width , "GetHeightForWidthBase is failed." );

  v = testCustomActor.TestGetHeightForWidthBase( width );
  DALI_CHECK_FAIL( v != width, "GetWidthForHeightBase is failed." );

  DaliLog::PrintPass();
}


void CustomActorImplGetWidthForHeightBaseP(void)
{
  TestCustomActor customActor = TestCustomActor::New();
  DALI_CHECK_FAIL(!customActor, "CustomActor()::New() is failed");

  Impl::TestCustomActor &testCustomActor = customActor.GetImpl();
  DALI_CHECK_FAIL(!(&testCustomActor), "CustomActor::GetImplementation is failed");
  float height = 300.0f;
  float v = 0.0f;

  v = customActor.GetWidthForHeight( height );
  DALI_CHECK_FAIL( v != height, "GetWidthForHeightBase is failed." );

  v = testCustomActor.TestGetWidthForHeightBase( height );
  DALI_CHECK_FAIL( v != height, "GetWidthForHeightBase is failed." );

  DaliLog::PrintPass();
}

void  CustomActorImplCalculateChildSizeBaseP(void)
{
  TestCustomActor customActor = TestCustomActor::New();
  DALI_CHECK_FAIL(!customActor, "CustomActor()::New() is failed");

  Impl::TestCustomActor &testCustomActor = customActor.GetImpl();
  DALI_CHECK_FAIL(!(&testCustomActor), "CustomActor::GetImplementation is failed");

  Actor child = Actor::New();
  child.SetResizePolicy(Dali::ResizePolicy::FIXED, Dali::Dimension::ALL_DIMENSIONS);
  child.SetSize(150, 150);

  float v = 9.99f;
  v = testCustomActor.TestCalculateChildSizeBase( child, Dali::Dimension::ALL_DIMENSIONS );
  DALI_CHECK_FAIL( v != 0.0f, "CalculateChildSizeBase is failed" );

  DaliLog::PrintPass();
}

void CustomActorImplRelayoutDependentOnChildrenBaseP(void)
{
  TestCustomActor customActor = TestCustomActor::New();
  DALI_CHECK_FAIL(!customActor, "CustomActor()::New() is failed");

  Impl::TestCustomActor &testCustomActor = customActor.GetImpl();
  DALI_CHECK_FAIL(!(&testCustomActor), "CustomActor::GetImplementation is failed");

  customActor.SetResizePolicy(Dali::ResizePolicy::FIT_TO_CHILDREN, Dali::Dimension::ALL_DIMENSIONS);

  bool v = false;

  v = testCustomActor.TestRelayoutDependentOnChildrenBase( Dali::Dimension::ALL_DIMENSIONS );
  DALI_CHECK_FAIL( v != true, "RelayoutDependentOnChildrenBas is failed " );

  DaliLog::PrintPass();
}
