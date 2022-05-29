#include "utc-dali-keyboard-focus-manager-common.h"

namespace
{

  /**Functions to test whether PreFocusChange signal is emitted when the keyboard focus is about to change**/
  class KeyboardPreFocusChangeCallback : public Dali::ConnectionTracker
  {
    public:
      KeyboardPreFocusChangeCallback(bool& bsignalReceived)
        : m_bSignalVerified(bsignalReceived),
        m_CurrentFocusedActor(),
        m_ProposedActorToFocus(),
        m_Direction(Control::KeyboardFocus::LEFT)
    {
    }

      Actor Callback(Actor currentFocusedActor, Actor proposedActorToFocus, Control::KeyboardFocus::Direction direction)
      {
        m_bSignalVerified = true;

        m_CurrentFocusedActor = currentFocusedActor;
        m_ProposedActorToFocus = proposedActorToFocus;
        m_Direction = direction;

        return m_ProposedActorToFocus;
      }

      void Reset()
      {
        m_bSignalVerified = false;
        m_CurrentFocusedActor = Actor();
        m_ProposedActorToFocus = Actor();
        m_Direction = Control::KeyboardFocus::LEFT;
      }

      bool& m_bSignalVerified;
      Actor m_CurrentFocusedActor;
      Actor m_ProposedActorToFocus;
      Control::KeyboardFocus::Direction m_Direction;
  };

  /** Functions to test whether focus changed signal is emitted when the keyboard focus is changed **/
  class KeyboardFocusChangedCallback : public Dali::ConnectionTracker
  {
    public:
      KeyboardFocusChangedCallback(bool& bsignalReceived)
        : m_bSignalVerified(bsignalReceived),
        m_OriginalFocusedActor(),
        m_CurrentFocusedActor()
    {
    }

      void Callback(Actor originalFocusedActor, Actor currentFocusedActor)
      {
        if(originalFocusedActor == m_CurrentFocusedActor)
        {
          m_bSignalVerified = true;
        }

        m_OriginalFocusedActor = originalFocusedActor;
        m_CurrentFocusedActor = currentFocusedActor;
      }

      void Reset()
      {
        m_bSignalVerified = false;
      }

      bool& m_bSignalVerified;
      Actor m_OriginalFocusedActor;
      Actor m_CurrentFocusedActor;
  };
} // namespace

/**
 * @function                  KeyboardFocusManagerMoveFocus
 * @description               Helper function for foving focus in different direction
 * @param                     focusDirection[Direction of focus]
 * @return                    true if all condition pass properly or false otherwise
 */
bool KeyboardFocusManagerMoveFocus( Dali::Toolkit::Control::KeyboardFocus::Direction focusDirection)
{
  bool bRet = false;

  KeyboardFocusManager focusManager = KeyboardFocusManager::Get();
  DALI_CHECK_FALSE(!focusManager, "Keyboard Focus Manager Initialization Failed");

  bool bpreFocusChangeSignalVerified = false;
  KeyboardPreFocusChangeCallback preFocusChangeCallback(bpreFocusChangeSignalVerified);
  focusManager.PreFocusChangeSignal().Connect( &preFocusChangeCallback, &KeyboardPreFocusChangeCallback::Callback );

  bool bfocusChangedSignalVerified = false;
  KeyboardFocusChangedCallback focusChangedCallback(bfocusChangedSignalVerified);

  focusManager.FocusChangedSignal().Connect( &focusChangedCallback, &KeyboardFocusChangedCallback::Callback );

  // Create the first actor and add it to the stage
  Actor firstActor = Actor::New();
  firstActor.SetKeyboardFocusable(true);
  Stage::GetCurrent().Add(firstActor);

  // Create the second actor and add it to the stage
  Actor secondActor = Actor::New();
  secondActor.SetKeyboardFocusable(true);
  Stage::GetCurrent().Add(secondActor);

  bRet = focusManager.MoveFocus(focusDirection);

  DALI_CHECK_FALSE(bRet, "Move the focus to right without emitting FocusChangedSignal");
  // no layout control is in the stage and no actor is focused, it should emit the PreFocusChange signal
  DALI_CHECK_FALSE(!preFocusChangeCallback.m_bSignalVerified && !(preFocusChangeCallback.m_CurrentFocusedActor == Actor()) && !(preFocusChangeCallback.m_ProposedActorToFocus == Actor()) && !(preFocusChangeCallback.m_Direction == Control::KeyboardFocus::RIGHT), "API failed api to Connect pre focus changed callback.");
  preFocusChangeCallback.Reset();
  // no layout control is in the stage and no actor is focused, it should emit the PreFocusChange signal
  DALI_CHECK_FALSE(!focusManager.SetCurrentFocusActor(firstActor) && !(focusManager.GetCurrentFocusActor() == firstActor) && !(focusChangedCallback.m_bSignalVerified) && !(focusChangedCallback.m_OriginalFocusedActor == Actor())&& !(focusChangedCallback.m_CurrentFocusedActor == firstActor), "FocusChangeSignal Failed to call focus changed callback.");
  Stage::GetCurrent().Remove(secondActor);
  Stage::GetCurrent().Remove(firstActor);
  return true;
}
