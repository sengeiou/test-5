#ifndef _UTC_DALI_FIXEDRULER_COMMON_H_
#define _UTC_DALI_FIXEDRULER_COMMON_H_

#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME            "FIXED_RULER_UTC"

#define PAGE_VOLUME           99999
#define PAGE_SIZE             99999

// HELPER FUNCTIONS

/** Fixed Ruler Initialization **/
bool FixedRulerInit(RulerPtr &rulerX, float fSetRuler, float fMinVal, float fMaxVal);

#endif  //_UTC_DALI_FIXEDRULER_COMMON_H_
