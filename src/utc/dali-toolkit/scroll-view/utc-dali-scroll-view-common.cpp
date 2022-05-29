#include "utc-dali-scroll-view-common.h"

/**
 * @function                    ScrollViewSetGetFilckAplhaFunction
 * @description                 Sets and gets the flick alpha function and checks if the values match
 * @return                      bool    the verdict for set get value mismatch
 */
bool  ScrollViewSetGetFilckAplhaFunction(ScrollView& scrollView,AlphaFunction setAlphaFunction,ScrollviewAlphaFunction scrollviewAlphaFunction)
{
  AlphaFunction getDefaultFunc;
  scrollView.SetScrollFlickAlphaFunction(setAlphaFunction);

  getDefaultFunc = scrollView.GetScrollFlickAlphaFunction();

  switch(scrollviewAlphaFunction)
  {
    case ALPHAFUNCTION_LINEAR:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::LINEAR,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_DEFAULT:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::DEFAULT,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_REVERSE:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::REVERSE,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_EASE_IN:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_IN,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_EASE_OUT:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_OUT,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_EASE_IN_OUT:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_IN_OUT,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_EASE_IN_SINE:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_IN_SINE,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_EASE_OUT_SINE:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_OUT_SINE,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_EASE_IN_OUT_SINE:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_IN_OUT_SINE,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_SIN:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::SIN,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
  }

  return true;
}

/**
 * @function                    ScrollViewSetGetSnapAplhaFunction
 * @description                 Sets and gets the snap alpha function and checks if the values match
 * @return                      bool    the verdict for set get value mismatch
 */
bool  ScrollViewSetGetSnapAplhaFunction(ScrollView& scrollView,AlphaFunction setAlphaFunction,ScrollviewAlphaFunction scrollviewAlphaFunction)
{
  AlphaFunction getDefaultFunc;
  scrollView.SetScrollSnapAlphaFunction(setAlphaFunction);

  getDefaultFunc = scrollView.GetScrollSnapAlphaFunction();
  switch(scrollviewAlphaFunction)
  {
    case ALPHAFUNCTION_LINEAR:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::LINEAR,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_DEFAULT:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::DEFAULT,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_REVERSE:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::REVERSE,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_EASE_IN:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_IN,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_EASE_OUT:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_OUT,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_EASE_IN_OUT:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_IN_OUT,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_EASE_IN_SINE:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_IN_SINE,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_EASE_OUT_SINE:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_OUT_SINE,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_EASE_IN_OUT_SINE:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::EASE_IN_OUT_SINE,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
    case ALPHAFUNCTION_SIN:
      DALI_CHECK_FALSE(getDefaultFunc.GetBuiltinFunction() != AlphaFunction::SIN,"GetDefaultAlphaFunctionis mismatched with SetDefaultAlphaFunction .");
      break;
  }

  return true;
}


/**
 * @function                    ScrollViewSetRulerScaleParameters
 * @description                 Set Ruler position
 * @return                      bool    the verdict for set ruler values
 */

bool ScrollViewSetRulerScaleParameters(ScrollView& scrlview , RulerPtr& rulerX , RulerPtr& rulerY ,float fMin, float fMax,float fRulerSize,bool bDomainEnabled,bool bIsDefaultRuler)
{
  if(bIsDefaultRuler)
  {
    rulerX = new DefaultRuler();
    rulerY = new DefaultRuler();
  }
  else
  {
    rulerX = new FixedRuler( fRulerSize );
    rulerY = new FixedRuler( fRulerSize );
  }

  DALI_CHECK_FALSE(!rulerX, " FixedRuler creation is failed.");
  rulerX->SetDomain( RulerDomain(fMin, fMax, bDomainEnabled) );

  DALI_CHECK_FALSE(!rulerY, " FixedRuler creation is failed.");
  rulerY->SetDomain( RulerDomain(fMin, fMax, bDomainEnabled) );

  scrlview.SetRulerX( rulerX );
  scrlview.SetRulerY( rulerY );

  return true;
}

/**
 * @function                    ScrollViewSetDefaultRuler
 * @description                 Set Ruler position
 * @return                      bool    the verdict for set ruler values
 */

bool ScrollViewSetDefaultRuler(Stage &stage,ScrollView& scrollView , RulerPtr& rulerX , RulerPtr& rulerY,bool bDomainEnabled)
{
  Vector2 vec2StageSize = Stage::GetCurrent().GetSize();

  rulerX = new DefaultRuler();
  DALI_CHECK_FALSE(!rulerX, " FixedRuler creation is failed.");
  rulerX->SetDomain( RulerDomain(0.0f, vec2StageSize.width + SCROLL_VIEW_CLAMP_EXCESS_WIDTH, bDomainEnabled) );

  rulerY = new DefaultRuler();
  DALI_CHECK_FALSE(!rulerY, " FixedRuler creation is failed.");
  rulerY->SetDomain( RulerDomain(0.0f, vec2StageSize.height + SCROLL_VIEW_CLAMP_EXCESS_HEIGHT, bDomainEnabled) );

  scrollView.SetRulerX( rulerX );
  scrollView.SetRulerY( rulerY );
  scrollView.SetSize(vec2StageSize);
  scrollView.SetParentOrigin(ParentOrigin::TOP_LEFT);
  scrollView.SetAnchorPoint(AnchorPoint::TOP_LEFT);

  return true;
}
