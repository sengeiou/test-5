#include "utc-dali-custom-actor-common.h"


int gRenderCountCustomActor;
bool gReqWheelEvent;


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

TestCustomActor gTestCustomActor, gTestCustomActorImpl, gTestCustomActorA, gTestCustomActorB, gTestCustomActorC;

//~ TestCustomActor g_testCustomActor;
CustomActor gCustomActor;
Actor gParentActor;

size_t CustomActorImplGetMasterStackSize(std::string strName)
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


void CustomActorDownCastP()
{
  float fWidth = 100.0f, fHeight = 200.0f;
  gTestCustomActor= TestCustomActor::New();
  DALI_CHECK_FAIL(!gTestCustomActor, "TestCustomActor::New() is failed.");

  CustomActor aCustomActor = gTestCustomActor;
  aCustomActor.SetSize(fWidth, fHeight);
  gParentActor = Actor::New();
  DALI_CHECK_FAIL(!gParentActor, "Actor::New() is failed.");
  Stage::GetCurrent().Add(gParentActor);
  gParentActor.Add( gTestCustomActor );
  Actor child = gParentActor.GetChildAt(CHILD_FIRST);
  DALI_CHECK_FAIL(!child, "Actor::GetChildAt() is failed.");
  gCustomActor = CustomActor::DownCast( child );
  DALI_CHECK_FAIL(!gCustomActor , "CustomActor::DownCast() is failed: invalid actor instance.");

  DaliLog::PrintPass();
}
void VTCustomActorDownCast001()
{
  float fWidth = 100.0f, fHeight = 200.0f;
  DALI_CHECK_FAIL(gCustomActor.GetCurrentSize().x != fWidth || gCustomActor.GetCurrentSize().y != fHeight, "CustomActor::DownCast() is failed: actor's size set mismatches.");

  gParentActor.Remove(gTestCustomActor);
  Stage::GetCurrent().Remove(gParentActor);

  DaliLog::PrintPass();
}

void CustomActorDownCastN()
{
  Actor child;

  CustomActor Custom_Actor = CustomActor::DownCast( child );
  DALI_CHECK_FAIL(Custom_Actor , "CustomActor::DownCast() is failed: invalid actor instance.");

  DaliLog::PrintPass();
}

void CustomActorGetImplementationP()
{
  TestCustomActor testCustomActor = TestCustomActor::New();

  DALI_CHECK_FAIL(!testCustomActor, "CustomActor()::New() is failed.");
  CustomActorImpl& customActorGetImplementation = testCustomActor.GetImplementation();
  DALI_CHECK_FAIL(!customActorGetImplementation.GetOwner(), "CustomActor::GetImplementation() is failed: invalid owner.");
  DALI_CHECK_FAIL(!customActorGetImplementation.RequiresWheelEvents(), "CustomActor::GetImplementation() is failed:  wheel event set failed.");
  DaliLog::PrintPass();
}

void CustomActorConstructorP2()
{
  CustomActor customActor(*(new Impl::TestCustomActor()));
  DALI_CHECK_FAIL(!customActor , "CustomActor::CustomActor() is failed: invalid custom actor instance.");
  DALI_CHECK_FAIL(!customActor.GetImplementation().RequiresTouchEvents(), "CustomActor::CustomActor() is failed: Touch events set failed.");

  DaliLog::PrintPass();
}

void CustomActorConstructorP()
{
  CustomActor customActor;
  DALI_CHECK_FAIL(customActor , "CustomActor::CustomActor() is failed: invalid custom actor instance.");

  DaliLog::PrintPass();
}

void CustomActorCopyConstructorP()
{
  float fWidth = 100.0f, fHeight = 200.0f;
  CustomActor customActor= TestCustomActor::New();
  DALI_CHECK_FAIL(!customActor, "TestCustomActor::New() is failed.");

  customActor.SetSize(fWidth, fHeight);

  CustomActor CustomActor_copy( customActor );
  DALI_CHECK_FAIL(!CustomActor_copy, "Copy constructor is failed.");

  DaliLog::PrintPass();
}

void CustomActorOperatorAssignmentP()
{
  float fWidth = 100.0f, fHeight = 200.0f;
  CustomActor customActor= TestCustomActor::New();
  DALI_CHECK_FAIL(!customActor, "TestCustomActor::New() is failed.");

  customActor.SetSize(fWidth, fHeight);

  CustomActor CustomActor_copy = customActor;
  DALI_CHECK_FAIL(!CustomActor_copy, "Copy constructor is failed.");

  DaliLog::PrintPass();
}
