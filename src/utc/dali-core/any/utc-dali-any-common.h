#ifndef _UTC_DALI_ANY_COMMON_H_
#define _UTC_DALI_ANY_COMMON_H_

#include <exception>

#include "dali-common.h"

using namespace Dali;

#define SUITE_NAME  "ANY_UTC"

namespace
{
  struct MyStruct
  {
    MyStruct()
      : mFloatValue( 0.f ),
      mIntValue( 0 )
    {}

    MyStruct( float fValue, int iValue )
      : mFloatValue( fValue ),
      mIntValue( iValue )
    {}

    MyStruct( const MyStruct& myStruct )
      : mFloatValue( myStruct.mFloatValue ),
      mIntValue( myStruct.mIntValue )
    {}

    MyStruct& operator=( const MyStruct& myStruct )
    {
      mFloatValue = myStruct.mFloatValue;
      mIntValue = myStruct.mIntValue;

      return *this;
    }

    float mFloatValue;
    int mIntValue;
  };
}

#endif  //_UTC_DALI_ANY_COMMON_H_
