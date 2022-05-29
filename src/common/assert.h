//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
#ifndef _ASSERT_H_
#define _ASSERT_H_
#include <stdio.h>
#include <stdlib.h>

#define assert(exp) \
    do { \
        if (!(exp)) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert Fail; Following expression is not true: %s\\n", \
                __FILE__, __LINE__, #exp); \
            return 1; \
        } \
    } while (0)

#define assert_eq(var, ref) \
    do { \
        if (var != ref) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert fail; Values (%s == 0x%x) and (%s == 0x%x) are not equal\\n", \
                __FILE__, __LINE__, #var, (int)var, #ref, (int)ref); \
            return 1; \
        } \
    } while (0)

#define assert_eq_no_return(var, ref) \
    do { \
        if (var != ref) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert fail; Values (%s == 0x%x) and (%s == 0x%x) are not equal\\n", \
                __FILE__, __LINE__, #var, (int)var, #ref, (int)ref); \
            return ; \
        } \
    } while (0)

#define assert_neq_no_return(var, ref) \
    do { \
        if (var == ref) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert fail; Values (%s == 0x%x) and (%s == 0x%x) are equal\\n", \
                __FILE__, __LINE__,  #var, (int)var, #ref, (int)ref); \
            return ; \
        } \
    } while (0)

#define assert_neq(var, ref) \
    do { \
        if (var == ref) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert fail; Values (%s == 0x%x) and (%s == 0x%x) are equal\\n", \
                __FILE__, __LINE__,  #var, (int)var, #ref, (int)ref); \
            return 1; \
        } \
    } while (0)

#define assert_gt(var, ref) \
    do { \
        if (var <= ref) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert fail; Values (%s == 0x%x) is not greater than (%s == 0x%x)\\n", \
            __FILE__, __LINE__,  #var, (int)var, #ref, (int)ref); \
            return 1; \
        } \
    } while (0)

#define assert_geq(var, ref) \
    do { \
        if (var < ref) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert fail; Values (%s == 0x%x) is not greater than or equal to (%s == 0x%x)\\n", \
                __FILE__, __LINE__,  #var, (int)var, #ref, (int)ref); \
            return 1; \
        } \
    } while (0)

#define assert_lt(var, ref) \
    do { \
        if (var >= ref) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert fail; Values (%s == 0x%x) is not lower than (%s == 0x%x)\\n", \
                __FILE__, __LINE__,  #var, (int)var, #ref, (int)ref); \
            return 1; \
        } \
    } while (0)

#define assert_leq(var, ref) \
    do { \
        if (var > ref) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert fail; Values (%s == 0x%x) is not lower than or equal to (%s == 0x%x)\\n", \
            __FILE__, __LINE__,  #var, (int)var, #ref, (int)ref); \
            return 1; \
        } \
    } while (0)


#endif //  _ASSERT_H_
