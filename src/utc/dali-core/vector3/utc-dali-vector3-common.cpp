#include "utc-dali-vector3-common.h"

/**
 * @function     vector3IsApplicable
 * @description  Check that a vector3 can successfully apply to an actor object.
 * @param[IN]    vec3TestValue[A Vector3 object to Test its applicability]
 * @return       bool
 */
bool vector3IsApplicable(Vector3 &vec3TestValue)
{
  Actor actor = Actor::New();
  Vector3 vec3TempValue(1.0f, 1.0f, 1.0f);

  DALI_CHECK_FALSE(!actor, "Failed to initiate an actor.");

  actor.SetAnchorPoint(vec3TempValue);

  DALI_CHECK_FALSE(vec3TempValue != actor.GetCurrentAnchorPoint(), "Failed to get current anchor point.");

  Stage::GetCurrent().Add( actor );

  actor.SetAnchorPoint(vec3TestValue);

  DALI_CHECK_FALSE(vec3TestValue != actor.GetCurrentAnchorPoint(), "Failed to get current anchor point.");

  Stage::GetCurrent().Remove( actor );
  return true;
}

/**
 * @function     vector3CreateParentAndChildActor
 * @description  Create parent and child actor set their size and add to stage.
 * @param[IN]    actorParent[Parent Actor]
 *       [IN]    actorChild[Child Actor]
 * @return       true if successfully creates parent and child actor.
 */
bool vector3CreateParentAndChildActor(Actor &actorParent, Actor &actorChild)
{
  Vector3 vec3StartParentSize( 10, 10, 10 );
  Vector3 vec3StartChildSize( 5, 5, 5 );

  actorParent =  Actor::New();
  DALI_CHECK_FALSE(!actorParent, "Parent Actor failed to initialized.");

  actorParent.SetSize( vec3StartParentSize );
  Stage::GetCurrent().Add( actorParent );

  actorChild =  Actor::New();
  DALI_CHECK_FALSE(!actorChild, "Child Actor failed to initialized.");

  actorChild.SetSize( vec3StartChildSize );
  actorParent.Add( actorChild );

  return true;
}
