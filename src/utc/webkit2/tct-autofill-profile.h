/* Copyright (c) 2014 Samsung Electronics Co., Ltd.

   Licensed under the Apache License, Version 2.0 (the License);
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "utc_webkit2_ewk.h"

#ifndef TCT_AUTOFILL_PROFILE_H
#define TCT_AUTOFILL_PROFILE_H

static const unsigned     TEST_AUTOFILL_PROFILE_ID                    =   12345;
static const char* const  TEST_AUTOFILL_PROFILE_NAME                  =   "Mr. Smith";
static const char* const  TEST_AUTOFILL_PROFILE_NAME_2                =   "Mrs. Smith";
static const char* const  TEST_AUTOFILL_PROFILE_COMPANY               =   "Samsung";
static const char* const  TEST_AUTOFILL_PROFILE_ADDRESS1              =   "Existing Street 15";
static const char* const  TEST_AUTOFILL_PROFILE_ADDRESS2              =   "NonExisting Street -15";
static const char* const  TEST_AUTOFILL_PROFILE_CITY_TOWN             =   "Capitol";
static const char* const  TEST_AUTOFILL_PROFILE_STATE_PROVINCE_REGION =   "Beautiful Province";
static const char* const  TEST_AUTOFILL_PROFILE_ZIPCODE               =   "12-345";
static const char* const  TEST_AUTOFILL_PROFILE_COUNTRY               =   "Neverland";
static const char* const  TEST_AUTOFILL_PROFILE_PHONE                 =   "123456789";
static const char* const  TEST_AUTOFILL_PROFILE_EMAIL                 =   "someEmail@someServer.com";

Ewk_Autofill_Profile* getTestEwkAutofillProfile();

#endif
