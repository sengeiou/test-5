#ifndef _UTC_DALI_PROPERTYTYPES_COMMON_H_
#define _UTC_DALI_PROPERTYTYPES_COMMON_H_

#include "dali-common.h"

using namespace std;
using namespace Dali;

#define SUITE_NAME  "PROPERTY_TYPES_UTC"

/**
 * @function          ShaderEffectsMethodNew
 * @description       Test for overloded constructor New
 * @param[int]        typeValue[Value of different Type]
 * @param[int]        pszExpectedTypeName[Expected name of given type]
 * @return            NA
 */
template <class TemType> bool PropertyTypesGetTypeName(TemType typeValue, char* pszExpectedTypeName)
{
  Property::Value value(typeValue);

  const char* pszTypeName = PropertyTypes::GetName(value.GetType());

  if( strcmp(pszTypeName, pszExpectedTypeName) )
  {
    DaliLog::Print( LOG_ERROR, SUITE_NAME, "Get Type Name is not correct", __LINE__ );
    return false;
  }

  pszTypeName = NULL;
  return true;
}

#endif  //_UTC_DALI_PROPERTYTYPES_COMMON_H_
