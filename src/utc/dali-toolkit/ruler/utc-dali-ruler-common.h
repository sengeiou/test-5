#ifndef _UTC_DALI_RULER_COMMON_H_
#define _UTC_DALI_RULER_COMMON_H_

#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME         "RULER_UTC"
#define PAGE_VOLUME1       99999
#define PAGE_SIZE1         99999

// HELPER FUNCTIONS

/** Fixed Ruler Initialization **/
bool FixedRulerInit1(RulerPtr &rulerX, float fSetRuler, float fMinVal, float fMaxVal);

#endif  //_UTC_DALI_RULER_COMMON_H_
