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

#include "utc-download-common.h"

static int bIsDownloadFeatureSupported = -1;
static int bIsTelephonyFeatureSupported = -1;
static int bIsWiFiFeatureSupported = -1;
static int bIsWiFiDirectFeatureSupported = -1;

bool download_check_feature(download_supported_features_e feature)
{
	bool val = false;

	if (feature == DOWNLOAD_SUPPORTED_FEATURE_DOWNLOAD) {
		if (bIsDownloadFeatureSupported == -1) {
			if(system_info_get_platform_bool(DOWNLOAD_FEATURE, &val) < 0 )
				return false;
			bIsDownloadFeatureSupported = val;
		}
		return bIsDownloadFeatureSupported;
	} else if (feature == DOWNLOAD_SUPPORTED_FEATURE_TELEPHONY) {
		if (bIsTelephonyFeatureSupported == -1) {
			if(system_info_get_platform_bool(TELEPHONY_FEATURE, &val) < 0 )
				return false;
			bIsTelephonyFeatureSupported = val;
		}
		return bIsTelephonyFeatureSupported;
	} else if (feature == DOWNLOAD_SUPPORTED_FEATURE_WIFI) {
		if (bIsWiFiFeatureSupported == -1) {
			if(system_info_get_platform_bool(WIFI_FEATURE, &val) < 0 )
				return false;
			bIsWiFiFeatureSupported = val;
		}
		return bIsWiFiFeatureSupported;
	} else if (feature == DOWNLOAD_SUPPORTED_FEATURE_WIFI_DIRECT) {
		if (bIsWiFiDirectFeatureSupported == -1) {
			if(system_info_get_platform_bool(WIFI_DIRECT_FEATURE, &val) < 0 )
				return false;
			bIsWiFiDirectFeatureSupported = val;
		}
		return bIsWiFiDirectFeatureSupported;
	}

	return false;
}

