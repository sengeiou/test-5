/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __UTC_CALENDAR_SERVICE_H__
#define __UTC_CALENDAR_SERVICE_H__

int utc_calendar_connect_p(void);
int utc_calendar_disconnect_p(void);
int utc_calendar_connect_on_thread_p(void);
int utc_calendar_disconnect_on_thread_p(void);
int utc_calendar_connect_with_flags_p(void);

#endif /* __UTC_CALENDAR_SERVICE_H__ */
