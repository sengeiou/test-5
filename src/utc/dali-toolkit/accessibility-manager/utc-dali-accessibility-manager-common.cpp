#include "utc-dali-accessibility-manager-common.h"

bool  AccessibilityManagerStageAncestor (Actor actorChild, Stage stageAncestor)
{
  while(actorChild && actorChild != stageAncestor)
  {
    actorChild = actorChild.GetParent();
  }
  return (actorChild == stageAncestor);
}

bool  AccessibilityManagerHasAncestor (Actor actorChild, Actor actorAncestor)
{
  while(actorChild && actorChild != actorAncestor)
  {
    actorChild = actorChild.GetParent();
  }
  return (actorChild == actorAncestor);
}

bool AccessibilityManagerAccessibilityAttribute( AccessibilityManager accessibilityManager, Actor actor, AccessibilityManager::AccessibilityAttribute nAttribute)
{
  const string STR_ACCESSIBILITY_ATTR_NAME = "Description";
  string strGetString ;

  accessibilityManager.SetAccessibilityAttribute(actor, nAttribute, STR_ACCESSIBILITY_ATTR_NAME);
  strGetString = accessibilityManager.GetAccessibilityAttribute(actor, nAttribute);

  DALI_CHECK_FALSE( STR_ACCESSIBILITY_ATTR_NAME != strGetString, "Set String and Get String is mismatched." );

  return true;
}
