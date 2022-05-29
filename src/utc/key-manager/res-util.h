//
// Copyright (c) 2017 Samsung Electronics Co., Ltd.
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
#ifndef _UTC_KEY_MANAGER_RES_UTIL_H__
#define _UTC_KEY_MANAGER_RES_UTIL_H__

#define PATH_LEN 1024

#include <stddef.h>

void append_to_app_data_path(const char *filename, char *outbuf, size_t size);

#endif
