#include "utc-dali-camera-actor-common.h"

bool  CameraActorHasAncestor (Actor actorChild, Actor actorAncestor)
{
  while(actorChild && actorChild != actorAncestor)
  {
    actorChild = actorChild.GetParent();
  }
  return (actorChild == actorAncestor);
}
