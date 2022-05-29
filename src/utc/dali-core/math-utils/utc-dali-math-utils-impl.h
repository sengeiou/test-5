#include "utc-dali-math-utils-common.h"

Vector3 gVec3GetSize;
Vector3 gVec3SetSize;
int gRenderCountMathUtils;
Actor gActorMU;
float gFXValue = 15.18f;
float gFYValue = 12.45f;
float gFZValue = 23.5f;


void MathUtilsNextPowerOfTwoP()
{
  unsigned int unCheckPower = 120u, unTestCheckPower = 128u, unGetNextPowerOfTwo = 0u;

  unGetNextPowerOfTwo = NextPowerOfTwo( unCheckPower );
  DALI_CHECK_FAIL( unGetNextPowerOfTwo != unTestCheckPower , "NextPowerOfTwo api is failed to return next power of two.");

  DaliLog::PrintPass();
}
void MathUtilsIsPowerOfTwoP()
{
  unsigned int unCheckPower = 120u, unTestCheckPower = 128u, unGetNextPowerOfTwo = 0u;
  bool bTestPowerOfTwo = false;

  unGetNextPowerOfTwo = NextPowerOfTwo( unCheckPower );
  DALI_CHECK_FAIL( unGetNextPowerOfTwo != unTestCheckPower , "NextPowerOfTwo api is failed to return next power of two.");
  bTestPowerOfTwo = IsPowerOfTwo( unGetNextPowerOfTwo );
  DALI_CHECK_FAIL( !bTestPowerOfTwo , "IsPowerOfTwo api is failed to check that the number is a power of two.");

  DaliLog::PrintPass();
}
void MathUtilsEqualsZeroP()
{
  float fZeroVal = 0.0f, fNonZeroVal = 1.0f;
  bool bGetStatusOfZeroVal = false;
  bool bGetStatusOfNonZeroVal = false;

  bGetStatusOfZeroVal = EqualsZero( fZeroVal );
  DALI_CHECK_FAIL( !bGetStatusOfZeroVal , "EqualsZero api is failed to return correct result(true) for a zero value" );
  bGetStatusOfNonZeroVal = EqualsZero( fNonZeroVal );
  DALI_CHECK_FAIL( bGetStatusOfNonZeroVal , "EqualsZero api is failed to return correct result(false) for a non-zero value" );

  DaliLog::PrintPass();
}
void MathUtilsShortestDistanceInDomainP()
{
  float fWrapX = 1.2f, fWrapY = 4.5f, fStart = 0.0f, fEnd = 9.0f;
  float fDistance = 0.0f;
  float fSize = fEnd - fStart;
  float fVect = fWrapY - fWrapX;
  float faRight = fWrapX + fSize;

  if( faRight - fWrapY < fVect )
  {
    fVect = fWrapY-faRight;
  }

  fDistance = ShortestDistanceInDomain( fWrapX, fWrapY, fStart, fEnd );
  DALI_CHECK_FAIL( fDistance != fVect ,  "ShortestDistanceInDomain api is failed to return shortest distance." );

  DaliLog::PrintPass();
}
void MathUtilsClampfloatP()
{
  float fValue = 5.0f;
  float fMin = 2.0f;
  float fMax = 11.0f;
  bool bClampFloat = false;

  bClampFloat = MathUtilsCommonClamp( fValue, fMin, fMax );
  DALI_CHECK_FAIL( !bClampFloat ,  "Clamp api is failed to clamp the float value between minimum and maximum float values." );

  DaliLog::PrintPass();
}
void MathUtilsClampintP()
{
  int nValue = 5;
  int nMin = 2;
  int nMax = 11;
  bool bClampInt = false;

  bClampInt = MathUtilsCommonClamp( nValue, nMin, nMax );
  DALI_CHECK_FAIL( !bClampInt,  "Clamp api is failed to clamp the integer value between minimum and maximum integer values." );

  DaliLog::PrintPass();
}
void MathUtilsClampInPlacefloatP()
{
  float fValue = 4.0f;
  float fMin = 6.0f;
  float fMax = 8.0f;
  bool bClampInPlacefloat = false;

  bClampInPlacefloat = MathUtilsCommonClampInPlace( fValue, fMin, fMax );
  DALI_CHECK_FAIL( !bClampInPlacefloat ,  "ClampInPlace api is failed to clamp the float value directly between minimum and maximum float values." );

  DaliLog::PrintPass();
}
void MathUtilsClampInPlaceintP()
{
  int nValue = 4;
  int nMin = 6;
  int nMax = 8;
  bool bClampInPlaceInt = false;

  bClampInPlaceInt = MathUtilsCommonClampInPlace( nValue, nMin, nMax );
  DALI_CHECK_FAIL( !bClampInPlaceInt ,  "ClampInPlace api is failed to clamp the integer value directly between minimum and maximum integer values." );

  DaliLog::PrintPass();
}
void MathUtilsRoundP()
{
  float fValue = 4.5f, fTemp = 0.0f, fRoundedVal = -1.0f;
  int nPos = 0;

  // Calculation to round the value of specific position
  fTemp = fValue * powf(  10, nPos  );
  fTemp = floorf(  fTemp + 0.5  );
  fTemp *= powf(  10, -nPos  );
  fRoundedVal = Round( fValue, nPos );
  DALI_CHECK_FAIL( fRoundedVal != fTemp ,  "Round api is failed to round the value in given position." );

  DaliLog::PrintPass();
}
void MathUtilsLerpForFloatP()
{
  float fOffset = 2.5f, fLow = 3.0f, fHigh = 7.8f, fLerpedVal = -1.0f, fCalLerpVal = 0.0f;

  fCalLerpVal = fLow + ( ( fHigh - fLow ) * Clamp( fOffset, 0.0f, 1.0f ) );  //  fOffset must be in between 0.0f and 1.0f range
  fLerpedVal = Lerp( fOffset, fLow, fHigh );
  DALI_CHECK_FAIL( fLerpedVal != fCalLerpVal ,  "Lerp api is failed to interpolate between two float values linearly." );

  DaliLog::PrintPass();
}
void MathUtilsLerpForIntP()
{
  int nLow = 3, nHigh = 7, nLerpedVal = -1, nCalLerpVal = 0;
  float fOffset = 2.0f;

  nCalLerpVal = nLow + ( ( nHigh - nLow ) * Clamp( fOffset, 0.0f, 1.0f ) );  //  fOffset must be in between 0.0f and 1.0f range
  nLerpedVal = Lerp( fOffset, nLow, nHigh );
  DALI_CHECK_FAIL( nLerpedVal != nCalLerpVal ,  "Lerp api is failed to interpolate between two integer values linearly." );

  DaliLog::PrintPass();
}
void MathUtilsEqualsWithAndWithoutEpsilonP()
{
  gVec3SetSize = Vector3( gFXValue, gFYValue, gFZValue );

  gActorMU = Actor::New();
  DALI_CHECK_INSTANCE( gActorMU, "Actor::New() is failed." );

  Stage::GetCurrent().Add( gActorMU );
  gActorMU.SetSize( gVec3SetSize );
}
void VTMathUtilsEqualsWithAndWithoutEpsilon001()
{
  gVec3GetSize = gActorMU.GetCurrentSize();

  //Direct result by comparison
  bool bResultbyCompare = (gVec3GetSize == gVec3SetSize);
  DALI_CHECK_FAIL( !bResultbyCompare, "Set/Get values of actor's size mismatches." );

  //Result by Equals without epsilon
  bool bResultbyEquals = Equals( gVec3GetSize.x, gFXValue );
  bResultbyEquals &= Equals( gVec3GetSize.y, gFYValue );
  bResultbyEquals &= Equals( gVec3GetSize.z, gFZValue );

  DALI_CHECK_FAIL( !bResultbyEquals || (bResultbyEquals != bResultbyCompare) , "Equals(float, float) is failed to match the actor's size with set value." );
  float fRandomMisMatch = 1e-8f;
  gFXValue += fRandomMisMatch;
  gFYValue += fRandomMisMatch;
  gFZValue += fRandomMisMatch;

  gActorMU.SetSize( gFXValue, gFYValue, gFZValue );
}
void VTMathUtilsEqualsWithAndWithoutEpsilon002()
{
  bool bResultbyCompare = false, bResultbyEquals = false;
  gVec3GetSize = gActorMU.GetCurrentSize();

  //Result by comparison considering slight mismatches
  bResultbyCompare = fabsf(gVec3GetSize.x - gVec3SetSize.x) <= GetRangedEpsilon(gVec3GetSize.x,  gVec3SetSize.x);
  bResultbyCompare &= fabsf(gVec3GetSize.y - gVec3SetSize.y) <= GetRangedEpsilon(gVec3GetSize.y,  gVec3SetSize.y);
  bResultbyCompare &= fabsf(gVec3GetSize.z - gVec3SetSize.z) <= GetRangedEpsilon(gVec3GetSize.z,  gVec3SetSize.z);

  DALI_CHECK_FAIL( !bResultbyCompare, "Failed to consider slight mismatch of actor's size using GetRangedEpsilon api." );

  //Result by Equals with epsilon
  bResultbyEquals = Equals( gVec3GetSize.x, gVec3SetSize.x, GetRangedEpsilon(gVec3GetSize.x,  gVec3SetSize.x) );
  bResultbyEquals &= Equals( gVec3GetSize.y, gVec3SetSize.y, GetRangedEpsilon(gVec3GetSize.y,  gVec3SetSize.y) );
  bResultbyEquals &= Equals( gVec3GetSize.z, gVec3SetSize.z, GetRangedEpsilon(gVec3GetSize.z,  gVec3SetSize.z) );

  DALI_CHECK_FAIL( !bResultbyEquals || (bResultbyEquals != bResultbyCompare) , "Equals(float, float, float) is failed to match the actor's size with set value considering slight mismatch" );

  Stage::GetCurrent().Remove(gActorMU);
  DaliLog::PrintPass();
}
void MathUtilsSignP()
{
  int test1 = 10, test2 = -10, test3 = 0;
  DALI_CHECK_FAIL( Sign(test1) != 1 , "Sign is failed for positive case." );
  DALI_CHECK_FAIL( Sign(test2) != -1 , "Sign is failed for negative case." );
  DALI_CHECK_FAIL( Sign(test3) != 0 , "Sign is failed for zero case." );

  DaliLog::PrintPass();
}
void MathUtilsWarpInDomainP()
{
  float fWrapX = 0.0f, fStart = 0.0f, fEnd = 0.0f;
  float fDistance = 0.0f, fExpected = 0.0f;

  fDistance = WrapInDomain( fWrapX, fStart, fEnd );
  DALI_CHECK_FAIL( fDistance != fExpected ,  "WrapInDomain api is failed to return wrap distance." );

  fWrapX = -1.1f;
  fStart = -2.0f;
  fEnd = -1.0f;
  fExpected = -1.1f;

  fDistance = WrapInDomain( fWrapX, fStart, fEnd );
  DALI_CHECK_FAIL( fDistance != fExpected ,  "WrapInDomain api is failed to return wrap distance." );

  fWrapX = 5.0f;
  fStart = 0.0f;
  fEnd = 10.0f;
  fExpected = 5.0f;

  fDistance = WrapInDomain( fWrapX, fStart, fEnd );
  DALI_CHECK_FAIL( fDistance != fExpected ,  "WrapInDomain api is failed to return wrap distance." );

  DaliLog::PrintPass();
}
