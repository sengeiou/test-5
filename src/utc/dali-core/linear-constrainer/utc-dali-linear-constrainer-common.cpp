#include "utc-dali-linear-constrainer-common.h"

/**
 * @function     LinearConstrainerSetupUniformProgress
 * @description  Set path point for LinearConstrainer
 * @param[in]    path [Dali path]
 * @return       NA
 */
void LinearConstrainerSetupUniformProgress( Dali::LinearConstrainer& linearConstrainer)
{
  Dali::Property::Array points;
  points.Resize(3);
  points[0] = 0.0f;
  points[1] = 1.0f;
  points[2] = 0.0f;
  linearConstrainer.SetProperty( Dali::LinearConstrainer::Property::VALUE, points );
}

/**
 * @function     LinearConstrainerSetupNonUniformProgress
 * @description  Set path point for segment
 * @param[in]    pathConstrainer [Dali  LinearConstrainer]
 * @return       NA
 */
void LinearConstrainerSetupNonUniformProgress( Dali::LinearConstrainer& linearConstrainer)
{
  Dali::Property::Array points;
  points.Resize(3);
  points[0] = 0.0f;
  points[1] = 1.0f;
  points[2] = 0.0f;
  linearConstrainer.SetProperty( Dali::LinearConstrainer::Property::VALUE, points );

  points[0] = 0.0f;
  points[1] = 0.25f;
  points[2] = 1.0f;
  linearConstrainer.SetProperty( Dali::LinearConstrainer::Property::PROGRESS, points );
}

/**
 * @function     LinearConstrainerCompareType
 * @description  Compare Set and Get Position with MathEpsilon
 * @param[in]    actorPosition [Acotors position]
 * @param[in]    getPosition [Get Position by applying LinearConstrainer]
 * @param[in]    epsilon [Dali  LinearConstrainer]
 * @return       bool
 */
bool LinearConstrainerCompareType(Vector3 actorPosition, float getPosition, float epsilon)
{
  return fabsf(actorPosition.x - getPosition)<epsilon;
}
