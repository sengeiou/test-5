#include "utc-dali-fixed-ruler-common.h"

/**
 * @function            FixedRulerInit
 * @description         FixedRuler Initialization
 * @return              bool
 */

bool FixedRulerInit(RulerPtr &rulerX, float fSetRuler, float fMinVal, float fMaxVal)
{
  rulerX = new FixedRuler( fSetRuler );
  DALI_CHECK_FALSE( !rulerX, "FixedRuler() is not created." );

  rulerX->SetDomain( RulerDomain(fMinVal, fMaxVal, true) );

  return true;
}
