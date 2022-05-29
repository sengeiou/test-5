#include "utc-dali-toolkit-common.h"

/**
 * @functioncleanup             ToolkitVector3Compare
 * @description                 Compare two Vector3 value
 */

bool ToolkitVector3Compare(Vector3 vec3ValueOne, Vector3 vec3ValueTwo)
{
  return fabsf(vec3ValueOne.x - vec3ValueTwo.x)<GetRangedEpsilon(vec3ValueOne.x, vec3ValueTwo.x) &&
         fabsf(vec3ValueOne.y - vec3ValueTwo.y)<GetRangedEpsilon(vec3ValueOne.y, vec3ValueTwo.y) &&
         fabsf(vec3ValueOne.z - vec3ValueTwo.z)<GetRangedEpsilon(vec3ValueOne.z, vec3ValueTwo.z);
}
