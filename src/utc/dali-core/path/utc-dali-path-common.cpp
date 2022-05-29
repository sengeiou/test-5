#include "utc-dali-path-common.h"

/**
 * @function         PathAnimatePlay
 * @description      A helper for animating of a path
 * @param[in]        path, Dali::Path
 * @return           if error occurs returns false else true
 */
bool PathAnimatePlay(Dali::Path path)
{
  const Vector3 vec3Forward(90.0f,  10.0f, 0.0f);
  Animation anim = Animation::New(PATH_ANIM_DUR_SEC);
  DALI_CHECK_FALSE(!anim , "Dali::Animation::New() is failed. Not Initialized object.");
  anim.Animate(Actor::New(), path, vec3Forward);
  anim.Play();
  anim.Stop();
  anim.Clear();
  return true;
}
