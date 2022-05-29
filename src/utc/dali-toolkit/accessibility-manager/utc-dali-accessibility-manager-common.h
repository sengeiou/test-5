#ifndef _UTC_DALI_ACCESSIBILITY_MANAGER_COMMON_H_
#define _UTC_DALI_ACCESSIBILITY_MANAGER_COMMON_H_

#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME             "ACCESSIBILITY_MANAGER_UTC"

bool AccessibilityManagerHasAncestor(Actor actorChild, Actor actorAncestor);
bool AccessibilityManagerStageAncestor(Actor actorChild, Stage stageAncestor);
bool AccessibilityManagerAccessibilityAttribute( AccessibilityManager accessibilityManager, Actor actor, AccessibilityManager::AccessibilityAttribute nAttribute);

#endif //_UTC_DALI_ACCESSIBILITY_MANAGER_COMMON_H_
