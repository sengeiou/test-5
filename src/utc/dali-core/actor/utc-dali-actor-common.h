#ifndef _UTC_DALI_ACTOR_COMMON_H_
#define _UTC_DALI_ACTOR_COMMON_H_

#include "dali-common.h"

using namespace Dali;

#define SUITE_NAME   "ACTOR_UTC"
#define ACTOR_ID     99999
#define DEFAULT_XYZ  100.0f

const float   ACTOR_SET_WIDTH  =  27.0f;                                             /**Actor's height**/
const float   ACTOR_SET_HEIGHT =  28.0f;                                           /**Actor's weight**/
const float   ACTOR_DEGREE_ANGLE = 90.0f;                                          /**Actor's orientation angle in float**/
const Radian  ACTOR_SET_ANGLE( M_PI * 0.25f );                                       /**Actor's orientation angle in Radian**/
const Vector4 ACTOR_SET_COLOR(1.0f, 0.5f, 0.0f, 0.8f);                               /** Vector4 instance for Actor's color **/
const Vector4 ACTOR_CHILD_SET_COLOR(0.5f, 0.6f, 0.5f, 1.0f);                      /** Vector4 instance for Actor's color **/
const Vector3 ACTOR_SET_POSITION(DEFAULT_XYZ, DEFAULT_XYZ, DEFAULT_XYZ);          /** Position in Vector3 **/
const Vector3 ACTOR_CHILD_SET_POSITION( 6.0f, 6.0f, 6.0f );                          /** Position in Vector3 **/
const Vector3 ACTOR_CHILD_SET_OFFSET( -1.0f, 1.0f, 0.0f );                          /** Vector3 instance for child offset **/
const Vector3 ACTOR_SET_SIZE(DEFAULT_XYZ, DEFAULT_XYZ, DEFAULT_XYZ);              /** Size in Vector3 **/
const Vector3 ACTOR_SET_TRANSLATE(1.0f, 2.0f, 3.0f);                              /** Translation of actor **/
const Vector3 ACTOR_AXIS_VEC3(1.0f, 1.0f, 0.0f);                                  /** Actor's orientation axis **/
const Vector3 ACTOR_SET_SCALE(0.5f, 2.0f, 3.0f);                                  /** Actor's Scale **/
const Vector3 ACTOR_SCALE_BY(2.0f, 2.0f, 2.0f);                                      /** Scale by factor**/
const string  ACTOR_SET_NAME = "actor";                                              /** Actor's name **/
/** Actor's orientation **/
const Quaternion ACTOR_SET_ORIENTATION(Radian(Degree(ACTOR_DEGREE_ANGLE)), Vector3::YAXIS);

enum ActorScaleInputParam
{
  ACTORSCALE_SINGLE_INPUT_PARAM,
  ACTORSCALE_MULTI_INPUT_PARAM,
  ACTORSCALE_VECTOR_INPUT_PARAM
};

enum ActorPositionInputParam
{
  ACTORPOSITION_DOUBLE_INPUT_PARAM,
  ACTORPOSITION_MULTI_INPUT_PARAM,
  ACTORPOSITION_VECTOR_INPUT_PARAM
};

enum ActorSizeInputParam
{
  ACTORSIZE_DOUBLE_INPUT_PARAM,
  ACTORSIZE_MULTI_INPUT_PARAM,
  ACTORSIZE_VECTOR2_INPUT_PARAM,
  ACTORSIZE_VECTOR3_INPUT_PARAM
};

enum ActorOrientationInputParam
{
  ACTORROTATION_DEGREE,
  ACTORROTATION_RADIAN,
  ACTORROTATION_QUATERNION
};

/**Varrying the input parameter for actor's position**/
bool ActorGetCurrentPosition(Actor &actor,Vector3 vec3SetPosition,enum ActorPositionInputParam PositionOption);

/**Varrying the input parameter for actor's rotation**/
bool ActorGetCurrentOrientation(Actor &actor,float fSetAngle,Vector3 vec3SetAxis,enum ActorOrientationInputParam OrientationOption);

/**Varrying the input parameter for actor's Scale**/
bool ActorGetCurrentScale(Actor &actor,Vector3 vec3SetScale,enum ActorScaleInputParam ScaleOption);

/**Varrying the input parameter for actor's Size**/
bool ActorGetCurrentSize(Actor &actor,Vector3 vec3SetSize, enum ActorSizeInputParam SizeOption);

#endif  //_UTC_DALI_ACTOR_COMMON_H_
