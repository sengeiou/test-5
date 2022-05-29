#ifndef _UTC_DALI_SCROLL_VIEW_COMMON_H_
#define _UTC_DALI_SCROLL_VIEW_COMMON_H_

#include <dali-common.h>
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME                                    "SCROLL_VIEW_UTC"

#define SCROLL_VIEW_CLAMP_EXCESS_HEIGHT                                    200.0f                                    /** Amount of height that can be panned outside scrollview **/
#define SCROLL_VIEW_CLAMP_EXCESS_WIDTH                                     200.0f                                    /** Amount of width that can be panned outside scrollview **/
#define SCROLL_DURATION                                                    0.0f                                      /** ScrollTo duration **/
#define N_PAGE                                                             0                                         /** Initial Page number **/

enum ScrollviewAlphaFunction
{
  ALPHAFUNCTION_LINEAR,
  ALPHAFUNCTION_DEFAULT,
  ALPHAFUNCTION_REVERSE,
  ALPHAFUNCTION_EASE_IN,
  ALPHAFUNCTION_EASE_OUT,
  ALPHAFUNCTION_EASE_IN_OUT,
  ALPHAFUNCTION_EASE_IN_SINE,
  ALPHAFUNCTION_EASE_OUT_SINE,
  ALPHAFUNCTION_EASE_IN_OUT_SINE,
  ALPHAFUNCTION_SIN
};


/**Sets and gets the scroll view flick alpha function status**/
bool  ScrollViewSetGetFilckAplhaFunction(ScrollView& sView , AlphaFunction setAlphaFunction,ScrollviewAlphaFunction);

/**Sets and gets the scroll view snap alpha function status**/
bool  ScrollViewSetGetSnapAplhaFunction(ScrollView& scrollView, AlphaFunction setAlphaFunction,ScrollviewAlphaFunction);

/**sets the ruler and scale parameters of scroll view**/
bool ScrollViewSetRulerScaleParameters(ScrollView& scrlview , RulerPtr& rulerX , RulerPtr& rulerY ,float fMin, float fMax,float fRulerSize,bool bDomainEnabled,bool bIsDefaultRuler);

/**sets the ruler and scale parameters for default ruler**/
bool ScrollViewSetDefaultRuler(Stage &stage,ScrollView& scrollView , RulerPtr& rulerX , RulerPtr& rulerY,bool bDomainEnabled);

#endif //_UTC_DALI_SCROLL_VIEW_COMMON_H_
