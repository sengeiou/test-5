#ifndef _UTC_CUSTOMACTOR_COMMON_H_
#define _UTC_CUSTOMACTOR_COMMON_H_

//Add test package related includes here
#include "dali-common.h"
#include <exception>
#include <dali/public-api/events/key-event.h>
#include <dali/dali.h>
#include <dali-toolkit/dali-toolkit.h>

using namespace std;
using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME  "CUSTOM_ACTOR_UTC"
#define GET_METHOD(method) #method
#define CHILD_FIRST  0

namespace
{
  enum EProperties
  {
    DALI = 0,
  };
  enum EAliasActor
  {
    FOUND = 0,
    NOT_FOUND,
  };
  // Key Event Enhanced Test references
  enum EKeyModifierEnhanced
  {
    MODIFIER_INVALID = 0x0,
    MODIFIER_SHIFT = 0x1,
    MODIFIER_CTRL  = 0x2,
    MODIFIER_ALT   = 0x4,
    MODIFIER_SHIFT_AND_CTRL  = (MODIFIER_SHIFT | MODIFIER_CTRL),
    MODIFIER_SHIFT_AND_ALT  = (MODIFIER_SHIFT | MODIFIER_ALT),
    MODIFIER_CTRL_AND_ALT  = (MODIFIER_CTRL | MODIFIER_ALT)
  };
  enum EWheelDirection
  {
    WHEEL_DIRECTION_VERTICAL = 0,    //Default
    WHEEL_DIRECTION_HORIZONTAL
  };
  enum EWheelRollingOffset
  {
    WHEEL_ROLLING_OFFSET_ROLLDOWN = 1,        // A positive value means roll down
    WHEEL_ROLLING_OFFSET_ROLLUP = -1        // A negative value means roll up
  };
  enum EActors { A = 0, B, C };
  enum EMethodsCall { FIRST = 0, SECOND };
  const string CUSTOMACTORIMPL_ACTORS[] = { "ActorA", "ActorB", "ActorC" };
  static const string CUSTOMACTORIMPL_PROPERTIES[] = { "DALi" };
  static const string CUSTOMACTORIMPL_VALUES[] = { "no" };
  static const string CUSTOMACTORIMPL_ALIAS_ACTOR[] = { "found", "not-found" };
  static const string CUSTOMACTORIMPL_INVALID_NAME_METHOD = "Unknown: ";
  static const string CUSTOMACTORIMPL_SEPARATOR_NAME_METHOD = ": ";
  static const size_t CUSTOMACTORIMPL_INVALID_LENGTH_NAME_METHOD = 0;
};

// A helper for checking a method contains or not
bool CustomActorImplHasMethod(const char* pchMethodName, std::vector<std::string> vecMethods);

#endif  //_UTC_CUSTOMACTOR_COMMON_H_
