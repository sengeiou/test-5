#include "utc-dali-control-impl-common.h"

//Add helper function definitions here

namespace Dali
{

  namespace Toolkit
  {

    DummyControl::DummyControl()
    {
    }

    DummyControl::DummyControl(const DummyControl& control)
      : Control( control )
    {
    }

    DummyControl::~DummyControl()
    {
    }

    DummyControl DummyControl::DownCast( BaseHandle handle )
    {
      return Control::DownCast<DummyControl, DummyControlImpl>(handle);
    }

    DummyControl& DummyControl::operator=(const DummyControl& control)
    {
      Control::operator=( control );
      return *this;
    }

    // Used to test signal connections
    void DummyControlImpl::CustomSlot1( Actor actor )
    {
      mCustomSlot1Called = true;
    }

    DummyControl DummyControlImpl::New()
    {
      IntrusivePtr< DummyControlImpl > impl = new DummyControlImpl;
      DummyControl control( *impl );
      impl->Initialize();
      return control;
    }

    DummyControlImpl::DummyControlImpl()
      : Control( ControlBehaviour( REQUIRES_TOUCH_EVENTS | REQUIRES_HOVER_EVENTS | REQUIRES_STYLE_CHANGE_SIGNALS ) ),
      mCustomSlot1Called(false)
    {
    }


    DummyControlImpl::~DummyControlImpl()
    {
    }

    DummyControl DummyControlImplOverride::New()
    {
      IntrusivePtr< DummyControlImplOverride > impl = new DummyControlImplOverride;
      DummyControl control( *impl );
      impl->Initialize();
      return control;
    }


    DummyControlImplOverride::DummyControlImplOverride()
      : DummyControlImpl(),
      initializeCalled(false),
      activatedCalled(false),
      themeChangeCalled( false ),
      fontChangeCalled( false ),
      pinchCalled(false),
      panCalled(false),
      tapCalled(false),
      longPressCalled(false),
      stageConnectionCalled(false),
      stageDisconnectionCalled(false),
      childAddCalled(false),
      childRemoveCalled(false),
      sizeSetCalled(false),
      sizeAnimationCalled(false),
      touchEventCalled(false),
      hoverEventCalled(false),
      wheelEventCalled(false),
      keyEventCalled(false),
      keyInputFocusGained(false),
      keyInputFocusLost(false)
    {
    }

    DummyControlImplOverride::~DummyControlImplOverride() { }


    void DummyControlImplOverride::OnInitialize() { initializeCalled = true; }
    bool DummyControlImplOverride::OnAccessibilityActivated() { activatedCalled = true; return true; }
    void DummyControlImplOverride::OnStyleChange( Toolkit::StyleManager styleManager, StyleChange::Type change )
    {
      themeChangeCalled = change == StyleChange::THEME_CHANGE;
      fontChangeCalled = change == StyleChange::DEFAULT_FONT_SIZE_CHANGE;
    }
    void DummyControlImplOverride::OnPinch(const PinchGesture& pinch) { pinchCalled = true; }
    void DummyControlImplOverride::OnPan(const PanGesture& pan) { panCalled = true; }
    void DummyControlImplOverride::OnTap(const TapGesture& tap) { tapCalled = true; }
    void DummyControlImplOverride::OnLongPress(const LongPressGesture& longPress) { longPressCalled = true; }
    void DummyControlImplOverride::OnStageConnection( int depth ) { Control::OnStageConnection( depth ); stageConnectionCalled = true; }
    void DummyControlImplOverride::OnStageDisconnection() { stageDisconnectionCalled = true; Control::OnStageDisconnection(); }
    void DummyControlImplOverride::OnChildAdd(Actor& child) { childAddCalled = true; }
    void DummyControlImplOverride::OnChildRemove(Actor& child) { childRemoveCalled = true; }
    void DummyControlImplOverride::OnSizeSet(const Vector3& targetSize) { Control::OnSizeSet( targetSize ); sizeSetCalled = true; }
    void DummyControlImplOverride::OnSizeAnimation(Animation& animation, const Vector3& targetSize) { Control::OnSizeAnimation( animation, targetSize ); sizeAnimationCalled = true; }
    bool DummyControlImplOverride::OnTouchEvent(const TouchEvent& event) { touchEventCalled = true; return false; }
    bool DummyControlImplOverride::OnHoverEvent(const HoverEvent& event) { hoverEventCalled = true; return false; }
    bool DummyControlImplOverride::OnWheelEvent(const WheelEvent& event) { wheelEventCalled = true; return false; }
    bool DummyControlImplOverride::OnKeyEvent(const KeyEvent& event) { keyEventCalled = true; return false;}
    void DummyControlImplOverride::OnKeyInputFocusGained() { keyInputFocusGained = true; }
    void DummyControlImplOverride::OnKeyInputFocusLost() { keyInputFocusLost = true; }
    void DummyControlImplOverride::OnSetResizePolicy( ResizePolicy::Type policy, Dimension::Type dimension ) { Control::OnSetResizePolicy( policy, dimension ); }

    DummyControl DummyControl::New( bool override )
    {
      DummyControl control;

      if (override)
      {
        control = DummyControlImplOverride::New();
      }
      else
      {
        control = DummyControlImpl::New();
      }

      return control;
    }

    DummyControl::DummyControl( DummyControlImpl& implementation )
      : Control( implementation )
    {
    }

    DummyControl::DummyControl( Dali::Internal::CustomActor* internal )
      : Control( internal )
    {
      VerifyCustomActorPointer<DummyControlImpl>(internal);
    }

  } // namespace Toolkit

} // namespace Dali
