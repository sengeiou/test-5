#include "utc-dali-vector2-common.h"

/**
 * @function     Vector2CreateParentAndChildActor
 * @description  Create parent and child actor set their size and add to stage.
 * @param[out]   actorParent[Parent Actor]
 * @param[out]   actorChild[Child Actor]
 * @return       true if successfully creates parent and child actor.
 */
bool Vector2CreateParentAndChildActor(Actor &actorParent, Actor &actorChild)
{
  Vector2 vec2StartParentSize( 10, 10 );
  Vector2 vec2StartChildSize( 15, 15 );

  actorParent =  Actor::New();
  DALI_CHECK_FALSE(!actorParent, "Parent Actor failed to initialized.");

  actorParent.SetSize( vec2StartParentSize );
  Stage::GetCurrent().Add( actorParent );

  actorChild =  Actor::New();
  DALI_CHECK_FALSE(!actorChild, "Child Actor failed to initialized.");

  actorChild.SetSize( vec2StartChildSize );
  actorParent.Add( actorChild );

  return true;
}

