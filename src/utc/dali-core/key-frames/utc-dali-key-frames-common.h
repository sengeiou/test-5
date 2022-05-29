#ifndef _UTC_DALI_KEYFRAMES_COMMON_H_
#define _UTC_DALI_KEYFRAMES_COMMON_H_

#include "dali-common.h"

using namespace std;
using namespace Dali;

#define SUITE_NAME  "KEY_FRAMES_UTC"

//common function for Add Api with Different template Type
bool KeyFramesWithDiffPropValue (KeyFrames& keyFrames ,Property::Value& value,float fVal);

#endif  //_UTC_DALI_KEYFRAMES_COMMON_H_
