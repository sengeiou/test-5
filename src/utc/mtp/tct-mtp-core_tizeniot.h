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
#ifndef __TCT_MTP-NATIVE_H__
#define __TCT_MTP-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_mtp_manager_startup(void);
extern void utc_mtp_manager_cleanup(void);
extern void utc_mtp_deviceinfo_startup(void);
extern void utc_mtp_deviceinfo_cleanup(void);
extern void utc_mtp_storageinfo_startup(void);
extern void utc_mtp_storageinfo_cleanup(void);
extern void utc_mtp_objectinfo_startup(void);
extern void utc_mtp_objectinfo_cleanup(void);

extern int utc_mtp_mtp_initialize_p(void);
extern int utc_mtp_mtp_get_devices_n(void);
extern int utc_mtp_mtp_get_storages_n(void);
extern int utc_mtp_mtp_get_object_handles_n(void);
extern int utc_mtp_mtp_get_object_n(void);
extern int utc_mtp_mtp_get_thumbnail_n(void);
extern int utc_mtp_mtp_add_mtp_event_cb_p(void);
extern int utc_mtp_mtp_add_mtp_event_cb_n(void);
extern int utc_mtp_mtp_remove_mtp_event_cb_p(void);
extern int utc_mtp_mtp_remove_mtp_event_cb_n(void);
extern int utc_mtp_mtp_deinitialize_p(void);
extern int utc_mtp_mtp_deviceinfo_get_manufacturer_name_n(void);
extern int utc_mtp_mtp_deviceinfo_get_model_name_n(void);
extern int utc_mtp_mtp_deviceinfo_get_serial_number_n(void);
extern int utc_mtp_mtp_deviceinfo_get_device_version_n(void);
extern int utc_mtp_mtp_storageinfo_get_description_n(void);
extern int utc_mtp_mtp_storageinfo_get_free_space_n(void);
extern int utc_mtp_mtp_storageinfo_get_max_capacity_n(void);
extern int utc_mtp_mtp_storageinfo_get_storage_type_n(void);
extern int utc_mtp_mtp_storageinfo_get_volume_identifier_n(void);
extern int utc_mtp_mtp_objectinfo_get_file_name_n(void);
extern int utc_mtp_mtp_objectinfo_get_keywords_n(void);
extern int utc_mtp_mtp_objectinfo_get_association_desc_n(void);
extern int utc_mtp_mtp_objectinfo_get_association_type_n(void);
extern int utc_mtp_mtp_objectinfo_get_size_n(void);
extern int utc_mtp_mtp_objectinfo_get_parent_object_handle_n(void);
extern int utc_mtp_mtp_objectinfo_get_storage_n(void);
extern int utc_mtp_mtp_objectinfo_get_date_created_n(void);
extern int utc_mtp_mtp_objectinfo_get_date_modified_n(void);
extern int utc_mtp_mtp_objectinfo_get_file_type_n(void);
extern int utc_mtp_mtp_objectinfo_get_image_bit_depth_n(void);
extern int utc_mtp_mtp_objectinfo_get_image_pix_width_n(void);
extern int utc_mtp_mtp_objectinfo_get_image_pix_height_n(void);
extern int utc_mtp_mtp_objectinfo_get_thumbnail_size_n(void);
extern int utc_mtp_mtp_objectinfo_get_thumbnail_file_type_n(void);
extern int utc_mtp_mtp_objectinfo_get_thumbnail_pix_height_n(void);
extern int utc_mtp_mtp_objectinfo_get_thumbnail_pix_width_n(void);

testcase tc_array[] = {
	{"utc_mtp_mtp_initialize_p",utc_mtp_mtp_initialize_p,utc_mtp_manager_startup,utc_mtp_manager_cleanup},
	{"utc_mtp_mtp_get_devices_n",utc_mtp_mtp_get_devices_n,utc_mtp_manager_startup,utc_mtp_manager_cleanup},
	{"utc_mtp_mtp_get_storages_n",utc_mtp_mtp_get_storages_n,utc_mtp_manager_startup,utc_mtp_manager_cleanup},
	{"utc_mtp_mtp_get_object_handles_n",utc_mtp_mtp_get_object_handles_n,utc_mtp_manager_startup,utc_mtp_manager_cleanup},
	{"utc_mtp_mtp_get_object_n",utc_mtp_mtp_get_object_n,utc_mtp_manager_startup,utc_mtp_manager_cleanup},
	{"utc_mtp_mtp_get_thumbnail_n",utc_mtp_mtp_get_thumbnail_n,utc_mtp_manager_startup,utc_mtp_manager_cleanup},
	{"utc_mtp_mtp_add_mtp_event_cb_p",utc_mtp_mtp_add_mtp_event_cb_p,utc_mtp_manager_startup,utc_mtp_manager_cleanup},
	{"utc_mtp_mtp_add_mtp_event_cb_n",utc_mtp_mtp_add_mtp_event_cb_n,utc_mtp_manager_startup,utc_mtp_manager_cleanup},
	{"utc_mtp_mtp_remove_mtp_event_cb_p",utc_mtp_mtp_remove_mtp_event_cb_p,utc_mtp_manager_startup,utc_mtp_manager_cleanup},
	{"utc_mtp_mtp_remove_mtp_event_cb_n",utc_mtp_mtp_remove_mtp_event_cb_n,utc_mtp_manager_startup,utc_mtp_manager_cleanup},
	{"utc_mtp_mtp_deinitialize_p",utc_mtp_mtp_deinitialize_p,utc_mtp_manager_startup,utc_mtp_manager_cleanup},
	{"utc_mtp_mtp_deviceinfo_get_manufacturer_name_n",utc_mtp_mtp_deviceinfo_get_manufacturer_name_n,utc_mtp_deviceinfo_startup,utc_mtp_deviceinfo_cleanup},
	{"utc_mtp_mtp_deviceinfo_get_model_name_n",utc_mtp_mtp_deviceinfo_get_model_name_n,utc_mtp_deviceinfo_startup,utc_mtp_deviceinfo_cleanup},
	{"utc_mtp_mtp_deviceinfo_get_serial_number_n",utc_mtp_mtp_deviceinfo_get_serial_number_n,utc_mtp_deviceinfo_startup,utc_mtp_deviceinfo_cleanup},
	{"utc_mtp_mtp_deviceinfo_get_device_version_n",utc_mtp_mtp_deviceinfo_get_device_version_n,utc_mtp_deviceinfo_startup,utc_mtp_deviceinfo_cleanup},
	{"utc_mtp_mtp_storageinfo_get_description_n",utc_mtp_mtp_storageinfo_get_description_n,utc_mtp_storageinfo_startup,utc_mtp_storageinfo_cleanup},
	{"utc_mtp_mtp_storageinfo_get_free_space_n",utc_mtp_mtp_storageinfo_get_free_space_n,utc_mtp_storageinfo_startup,utc_mtp_storageinfo_cleanup},
	{"utc_mtp_mtp_storageinfo_get_max_capacity_n",utc_mtp_mtp_storageinfo_get_max_capacity_n,utc_mtp_storageinfo_startup,utc_mtp_storageinfo_cleanup},
	{"utc_mtp_mtp_storageinfo_get_storage_type_n",utc_mtp_mtp_storageinfo_get_storage_type_n,utc_mtp_storageinfo_startup,utc_mtp_storageinfo_cleanup},
	{"utc_mtp_mtp_storageinfo_get_volume_identifier_n",utc_mtp_mtp_storageinfo_get_volume_identifier_n,utc_mtp_storageinfo_startup,utc_mtp_storageinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_file_name_n",utc_mtp_mtp_objectinfo_get_file_name_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_keywords_n",utc_mtp_mtp_objectinfo_get_keywords_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_association_desc_n",utc_mtp_mtp_objectinfo_get_association_desc_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_association_type_n",utc_mtp_mtp_objectinfo_get_association_type_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_size_n",utc_mtp_mtp_objectinfo_get_size_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_parent_object_handle_n",utc_mtp_mtp_objectinfo_get_parent_object_handle_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_storage_n",utc_mtp_mtp_objectinfo_get_storage_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_date_created_n",utc_mtp_mtp_objectinfo_get_date_created_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_date_modified_n",utc_mtp_mtp_objectinfo_get_date_modified_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_file_type_n",utc_mtp_mtp_objectinfo_get_file_type_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_image_bit_depth_n",utc_mtp_mtp_objectinfo_get_image_bit_depth_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_image_pix_width_n",utc_mtp_mtp_objectinfo_get_image_pix_width_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_image_pix_height_n",utc_mtp_mtp_objectinfo_get_image_pix_height_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_thumbnail_size_n",utc_mtp_mtp_objectinfo_get_thumbnail_size_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_thumbnail_file_type_n",utc_mtp_mtp_objectinfo_get_thumbnail_file_type_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_thumbnail_pix_height_n",utc_mtp_mtp_objectinfo_get_thumbnail_pix_height_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{"utc_mtp_mtp_objectinfo_get_thumbnail_pix_width_n",utc_mtp_mtp_objectinfo_get_thumbnail_pix_width_n,utc_mtp_objectinfo_startup,utc_mtp_objectinfo_cleanup},
	{NULL, NULL}
};

#endif // __TCT_MTP-NATIVE_H__
