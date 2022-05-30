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

#include "res-util.h"

#include "tct_common.h"
#include <app.h>
#include <stdlib.h>

void append_to_app_data_path(const char *filename, char *outbuf, size_t size)
{
    if (!filename || !outbuf || size == 0)
        return;

    char *app_data_path = app_get_data_path();
    if (!app_data_path)
        return;

    size_t app_data_path_len = strlen(app_data_path);
    if (size < app_data_path_len + strlen(filename) + 1)
        goto out;

    memset(outbuf, 0x00, size);
    memcpy(outbuf, app_data_path, app_data_path_len);
    memcpy(outbuf + app_data_path_len, filename, strlen(filename));

out:
    free(app_data_path);
    return;
}
