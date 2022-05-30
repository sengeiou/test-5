/*
 * Copyright (c) 2014 - 2015 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __UTC_CONTACTS_SERVICE_RECORD_EXTENSION_H__
#define __UTC_CONTACTS_SERVICE_RECORD_EXTENSION_H__

#include <contacts.h>
int ctsvc_tc_record_get_property_extension(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count);
int ctsvc_tc_record_compare_extension(contacts_record_h record, ctsvc_property_type_e type);
int ctsvc_tc_filter_set_extension(contacts_filter_h filter, ctsvc_property_type_e type);
int ctsvc_tc_record_update_extension(contacts_record_h record, ctsvc_property_type_e type);
int ctsvc_tc_record_create_extension(int contact_id, ctsvc_property_type_e type, contacts_record_h *p_record);
#endif // __UTC_CONTACTS_SERVICE_RECORD_EXTENSION_H__

