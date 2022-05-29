#include "utc-dali-rect-common.h"

bool RectBottomLeftRightTop(enum ERectDirection eRectDirection)
{
  float fXvalue=10.0f, fYvalue=30.0f, fWidth=10.0f, fHeight=200.0f, fRes=0.0f, fChk = 0.0f;
  const int INCREAMENTAL_FACTOR = 1.0f;


  fChk = 0.0f;
  Rect<float> rect(fXvalue, fYvalue, fWidth, fHeight);


  if(eRectDirection == RECT_BOTTOM)
  {
    fRes=fYvalue + fHeight;
    fChk = rect.Bottom();
  }
  else if(eRectDirection == RECT_TOP)
  {
    fRes=fYvalue;
    fChk = rect.Top();
  }
  else if(eRectDirection == RECT_LEFT)
  {
    fRes=fXvalue;
    fChk = rect.Left();
  }
  else
  {
    fRes=fXvalue + fWidth;
    fChk = rect.Right();
  }

  if(fRes != fChk)
  {
    if(eRectDirection == RECT_BOTTOM)
    {
      LOG_I("Didnt get direction of Bottom" );
      return false;
    }
    else if(eRectDirection == RECT_TOP)
    {
      LOG_I("Didnt get direction of Top" );
      return false;
    }
    else if(eRectDirection == RECT_LEFT)
    {
      LOG_I("Didnt get direction of Left" );
      return false;
    }
    else
    {
      LOG_I("Didnt get direction of Right" );
      return false;
    }
  }
  fXvalue += INCREAMENTAL_FACTOR, fYvalue += INCREAMENTAL_FACTOR, fWidth += INCREAMENTAL_FACTOR, fHeight += INCREAMENTAL_FACTOR;

  return true;

}
