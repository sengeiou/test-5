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

#include "tct_app_common.h"

/**
 * @function            utc_package_manager_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_package_manager_startup(void)
{
        TCT_UTCCheckInstalledApp(3, "org.tizen.helloworld", "org.tizen.helloworld2",
				"org.tizen.helloworld3");
}
