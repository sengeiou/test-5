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
#ifndef __TCT_FILESYSTEM-PERMISSION-NATIVE_H__
#define __TCT_FILESYSTEM-PERMISSION-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void CTs_filesystem_permission_startup(void);
extern void CTs_filesystem_permission_cleanup(void);

extern int CTc_CreateFileToImages_p(void);
extern int CTc_CreateFileToSounds_p(void);
extern int CTc_CreateFileToVideos_p(void);
extern int CTc_CreateFileToCamera_p(void);
extern int CTc_CreateFileToDownloads_p(void);
extern int CTc_CreateFileToMusic_p(void);
extern int CTc_CreateFileToDocuments_p(void);
extern int CTc_CreateFileToOthers_p(void);
extern int CTc_CreateFileToExternalImages_p(void);
extern int CTc_CreateFileToExternalSounds_p(void);
extern int CTc_CreateFileToExternalVideos_p(void);
extern int CTc_CreateFileToExternalCamera_p(void);
extern int CTc_CreateFileToExternalDownloads_p(void);
extern int CTc_CreateFileToExternalMusic_p(void);
extern int CTc_CreateFileToExternalDocuments_p(void);
extern int CTc_CreateFileToExternalOthers_p(void);
extern int CTc_CreateFolderToImages_p(void);
extern int CTc_CreateFolderToSounds_p(void);
extern int CTc_CreateFolderToVideos_p(void);
extern int CTc_CreateFolderToCamera_p(void);
extern int CTc_CreateFolderToDownloads_p(void);
extern int CTc_CreateFolderToMusic_p(void);
extern int CTc_CreateFolderToDocuments_p(void);
extern int CTc_CreateFolderToOthers_p(void);
extern int CTc_CreateFolderToExternalImages_p(void);
extern int CTc_CreateFolderToExternalSounds_p(void);
extern int CTc_CreateFolderToExternalVideos_p(void);
extern int CTc_CreateFolderToExternalCamera_p(void);
extern int CTc_CreateFolderToExternalDownloads_p(void);
extern int CTc_CreateFolderToExternalMusic_p(void);
extern int CTc_CreateFolderToExternalDocuments_p(void);
extern int CTc_CreateFolderToExternalOthers_p(void);

testcase tc_array[] = {
	{"CTc_CreateFileToImages_p",CTc_CreateFileToImages_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToSounds_p",CTc_CreateFileToSounds_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToVideos_p",CTc_CreateFileToVideos_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToCamera_p",CTc_CreateFileToCamera_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToDownloads_p",CTc_CreateFileToDownloads_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToMusic_p",CTc_CreateFileToMusic_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToDocuments_p",CTc_CreateFileToDocuments_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToOthers_p",CTc_CreateFileToOthers_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToExternalImages_p",CTc_CreateFileToExternalImages_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToExternalSounds_p",CTc_CreateFileToExternalSounds_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToExternalVideos_p",CTc_CreateFileToExternalVideos_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToExternalCamera_p",CTc_CreateFileToExternalCamera_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToExternalDownloads_p",CTc_CreateFileToExternalDownloads_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToExternalMusic_p",CTc_CreateFileToExternalMusic_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToExternalDocuments_p",CTc_CreateFileToExternalDocuments_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFileToExternalOthers_p",CTc_CreateFileToExternalOthers_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToImages_p",CTc_CreateFolderToImages_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToSounds_p",CTc_CreateFolderToSounds_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToVideos_p",CTc_CreateFolderToVideos_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToCamera_p",CTc_CreateFolderToCamera_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToDownloads_p",CTc_CreateFolderToDownloads_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToMusic_p",CTc_CreateFolderToMusic_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToDocuments_p",CTc_CreateFolderToDocuments_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToOthers_p",CTc_CreateFolderToOthers_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToExternalImages_p",CTc_CreateFolderToExternalImages_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToExternalSounds_p",CTc_CreateFolderToExternalSounds_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToExternalVideos_p",CTc_CreateFolderToExternalVideos_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToExternalCamera_p",CTc_CreateFolderToExternalCamera_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToExternalDownloads_p",CTc_CreateFolderToExternalDownloads_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToExternalMusic_p",CTc_CreateFolderToExternalMusic_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToExternalDocuments_p",CTc_CreateFolderToExternalDocuments_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{"CTc_CreateFolderToExternalOthers_p",CTc_CreateFolderToExternalOthers_p,CTs_filesystem_permission_startup,CTs_filesystem_permission_cleanup},
	{NULL, NULL}
};

#endif // __TCT_FILESYSTEM-PERMISSION-NATIVE_H__
