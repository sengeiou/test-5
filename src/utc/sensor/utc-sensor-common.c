//
// Copyright (c) 2020 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "utc-sensor-common.h"

#define ADD_CASE_TO_STR(c) \
    case c:                \
        ret = #c;          \
        break;

char *sensor_type_e_to_str(sensor_type_e type)
{
    char *ret = "Unknown type";

    switch (type)
    {
    SENSOR_TYPES(ADD_CASE_TO_STR);
    default:
        break;
    }

    return ret;
}

char *sensor_error_to_str(int error)
{
    char *ret = "Unknown error";

    switch (error)
    {
    SENSOR_ERRORS(ADD_CASE_TO_STR);
    default:
        break;
    }

    return ret;
}

#undef ADD_CASE_TO_STR
