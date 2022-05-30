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

#include <stdio.h>
#include <stdlib.h>
#include "tct-autofill-profile.h"

Ewk_Autofill_Profile* getTestEwkAutofillProfile()
{
    Ewk_Autofill_Profile* profile = ewk_autofill_profile_new();
    if (!profile)
        return NULL;

    char id[10];
    snprintf(id, sizeof(id)/sizeof(id[0]), "%d", TEST_AUTOFILL_PROFILE_ID);
    ewk_autofill_profile_data_set(profile, EWK_PROFILE_ID, id);
    ewk_autofill_profile_data_set(profile, EWK_PROFILE_NAME, TEST_AUTOFILL_PROFILE_NAME);
    ewk_autofill_profile_data_set(profile, EWK_PROFILE_COMPANY, TEST_AUTOFILL_PROFILE_COMPANY);
    ewk_autofill_profile_data_set(profile, EWK_PROFILE_ADDRESS1, TEST_AUTOFILL_PROFILE_ADDRESS1);
    ewk_autofill_profile_data_set(profile, EWK_PROFILE_ADDRESS2, TEST_AUTOFILL_PROFILE_ADDRESS2);
    ewk_autofill_profile_data_set(profile, EWK_PROFILE_CITY_TOWN, TEST_AUTOFILL_PROFILE_CITY_TOWN);
    ewk_autofill_profile_data_set(profile, EWK_PROFILE_STATE_PROVINCE_REGION, TEST_AUTOFILL_PROFILE_STATE_PROVINCE_REGION);
    ewk_autofill_profile_data_set(profile, EWK_PROFILE_ZIPCODE, TEST_AUTOFILL_PROFILE_ZIPCODE);
    ewk_autofill_profile_data_set(profile, EWK_PROFILE_COUNTRY, TEST_AUTOFILL_PROFILE_COUNTRY);
    ewk_autofill_profile_data_set(profile, EWK_PROFILE_PHONE, TEST_AUTOFILL_PROFILE_PHONE);
    ewk_autofill_profile_data_set(profile, EWK_PROFILE_EMAIL, TEST_AUTOFILL_PROFILE_EMAIL);

    return profile;
}
