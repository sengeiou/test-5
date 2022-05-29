#ifndef _UTC_DALI_CONTROL_IMPL_COMMON_H_
#define _UTC_DALI_CONTROL_IMPL_COMMON_H_

#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME                 "CONTROL_IMPL_UTC"
#define CONTROL_IMAGE_NAME         "dali_imagemodule_image.png"

// HELPER FUNCTIONS

namespace Dali
{

  namespace Toolkit
  {

    class DummyControlImpl;

    /**
     * Control does not have a New method so use this dummy class for the handle.
     */
    class DummyControl : public Control
    {
      public:

        DummyControl();
        DummyControl(const DummyControl& control);
        ~DummyControl();

        static DummyControl New( bool override = false );

        static DummyControl DownCast( BaseHandle handle );


        DummyControl& operator=(const DummyControl& control);

      public: // Not intended for application developers

        DummyControl( DummyControlImpl& implementation );
        DummyControl( Dali::Internal::CustomActor* internal );
    };

    /**
     * Cannot create an instance of Internal::Control, so use this dummy class for the implementation.
     * This class does not override any of Internal::Control's behaviour.
     */
    class DummyControlImpl : public Internal::Control
    {
      public:

        static DummyControl New();

      public:
        inline void EnableGestureDetection(Gesture::Type type) { Internal::Control::EnableGestureDetection(type); }
        inline void DisableGestureDetection(Gesture::Type type) { Internal::Control::DisableGestureDetection(type); }
        inline PinchGestureDetector GetPinchGestureDetector() const { return Internal::Control::GetPinchGestureDetector(); }
        inline PanGestureDetector GetPanGestureDetector() const { return Internal::Control::GetPanGestureDetector(); }
        inline TapGestureDetector GetTapGestureDetector() const { return Internal::Control::GetTapGestureDetector(); }
        inline LongPressGestureDetector GetLongPressGestureDetector() const { return Internal::Control::GetLongPressGestureDetector(); }
        inline float CalculateChildSize( const Dali::Actor& child, Dimension::Type dimension ) { return Internal::Control::CalculateChildSize(child,dimension); }
        inline bool RelayoutDependentOnChildren( Dimension::Type dimension ) { return Internal::Control::RelayoutDependentOnChildren( dimension ); }

        // Used to test signal connections
        void CustomSlot1( Actor actor );

        bool mCustomSlot1Called;

      protected:

        DummyControlImpl();

        virtual ~DummyControlImpl();
    };

    /**
     * Cannot create an instance of Internal::Control, so use this dummy class for the implementation.
     * This class DOES override Internal::Control's behaviour.
     */
    class DummyControlImplOverride : public DummyControlImpl
    {
      public:

        static DummyControl New();

      private:

        DummyControlImplOverride();

        virtual ~DummyControlImplOverride();

      private: // From Internal::Control

        virtual void OnInitialize();
        virtual bool OnAccessibilityActivated();
        virtual void OnStyleChange( Toolkit::StyleManager styleManager, StyleChange::Type change );
        virtual void OnPinch(const PinchGesture& pinch);
        virtual void OnPan(const PanGesture& pan);
        virtual void OnTap(const TapGesture& tap);
        virtual void OnLongPress(const LongPressGesture& longPress);

      private: // From CustomActorImpl

        virtual void OnStageConnection( int depth );
        virtual void OnStageDisconnection();
        virtual void OnChildAdd(Actor& child);
        virtual void OnChildRemove(Actor& child);
        virtual bool OnTouchEvent(const TouchEvent& event);
        virtual bool OnHoverEvent(const HoverEvent& event);
        virtual bool OnWheelEvent(const WheelEvent& event);
        virtual bool OnKeyEvent(const KeyEvent& event);
        virtual void OnKeyInputFocusGained();
        virtual void OnKeyInputFocusLost();

      public:

        virtual void OnSizeSet(const Vector3& targetSize);
        virtual void OnSizeAnimation(Animation& animation, const Vector3& targetSize);
        virtual void OnSetResizePolicy( ResizePolicy::Type policy, Dimension::Type dimension );
        bool initializeCalled;
        bool activatedCalled;
        bool themeChangeCalled;
        bool fontChangeCalled;
        bool pinchCalled;
        bool panCalled;
        bool tapCalled;
        bool longPressCalled;
        bool stageConnectionCalled;
        bool stageDisconnectionCalled;
        bool childAddCalled;
        bool childRemoveCalled;
        bool sizeSetCalled;
        bool sizeAnimationCalled;
        bool touchEventCalled;
        bool hoverEventCalled;
        bool wheelEventCalled;
        bool keyEventCalled;
        bool keyInputFocusGained;
        bool keyInputFocusLost;
    };

  } // namespace Toolkit

} // namespace Dali

#endif //_UTC_DALI_CONTROL_IMPL_COMMON_H_
