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

//#ifndef _UTC_DOWNLOAD_COMMON_H_
//#define _UTC_DONWLOAD_COMMON_H_

#include <dlog.h>
#include <system_info.h>

#define API_NAMESPACE       "URL_DOWNLOAD_UTC"
#define DOWNLOAD_TIMEOUT    25000

#define DOWNLOAD_FEATURE    "tizen.org/feature/download"
#define TELEPHONY_FEATURE   "tizen.org/feature/network.telephony"
#define WIFI_FEATURE        "tizen.org/feature/network.wifi"
#define WIFI_DIRECT_FEATURE "tizen.org/feature/network.wifi.direct"
#define API_NAMESPACE       "URL_DOWNLOAD_UTC"

#define TEST_URL "http://download.tizen.org/tct/2.2.1/Manual/Native_TBT_2.2.1_User_Guide_v1.0.pdf"
#define TEST_URL_SMALL "http://download.tizen.org/tct/tct-download-tizen-tests-image-lq.png"

typedef enum {
	DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD = 0,
	DOWNLOAD_SUPPORTED_FEATURE_TELEPHONY,
	DOWNLOAD_SUPPORTED_FEATURE_WIFI,
	DOWNLOAD_SUPPORTED_FEATURE_WIFI_DIRECT
} download_supported_features_e;

bool g_bIsDownloadFeatureSupported;
bool g_bIsTelephonyFeatureSupported;
bool g_bIsWifiFeatureSupported;
bool g_bIsWifiDirectFeatureSupported;

bool download_check_feature(download_supported_features_e feature);

//#endif  /* _UTC_DOWNLOAD_COMMON_H_ */

