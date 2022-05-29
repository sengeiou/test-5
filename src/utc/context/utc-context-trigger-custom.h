//
// Copyright (c) 2016 Samsung Electronics Co., Ltd.
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
#ifndef __UTC_CONTEXT_TRIGGER_CUSTOM_H__
#define __UTC_CONTEXT_TRIGGER_CUSTOM_H__


#define CONTEXT_TEST_PACKAGE_ID "core-context-tests"
#define CUSTOM_ITEM_WEATHER "weather"

#define CUSTOM_WEATHER_TEMPLATE "{ \"temperature\": { \"type\": \"integer\", \"minimum\": -50, \"maximum\": 50}, \"status\": { \"enum\": [ \"sunny\", \"snowy\", \"cloudy\", \"rainy\"]} }"
#define CUSTOM_WEATHER_TEMPLATE2 "{ \"humidity\": { \"type\": \"integer\", \"minimum\": 0, \"maximum\": 100}, \"status\": { \"enum\": [ \"cold\", \"cool\", \"warm\", \"hot\"]} }"
#define CUSTOM_WEATHER_TEMPLATE_INVALID_JSON "{ \"temperature\": { \"type\": \"integer\", \"minimum\": -50, \"maximum\": 50}, \"status\": { \"enum\": [ \"sunny\", \"snowy\", \"cloudy\", \"rainy\"} }"
#define CUSTOM_WEATHER_TEMPLATE_INVALID1 "{ \"temperature\": { \"type\": \"string\", \"minimum\": -50, \"maximum\": 50}, \"status\": { \"enum\": [ \"sunny\", \"snowy\", \"cloudy\", \"rainy\"]} }"
#define CUSTOM_WEATHER_TEMPLATE_INVALID2 "{ \"temperature\": { \"type\": \"integer\", \"minimum\": -50, \"maximum\": 50}, \"status\": { \"type\": \"string\", \"maximum\": 15, \"enum\": [ \"sunny\", \"snowy\", \"cloudy\", \"rainy\"]} }"
#define CUSTOM_WEATHER_TEMPLATE_INVALID3 "{ \"temperature\": { \"type\": \"integer\", \"minimum\": -50, \"maximum\": 50}, \"status\": { \"enum\": [ 5, 6, 7]} }"
#define CUSTOM_WEATHER_TEMPLATE_INVALID4 "{ \"temperature\": { \"type\": \"integer\", \"minimum\": -50, \"maximum\": 50}, \"status\": { \"maximum\": 15, \"enum\": [ \"sunny\", \"snowy\", \"cloudy\", \"rainy\"]} }"

// Valid
#define CUSTOM_WEATHER_DATA1 "{\"temperature\": 30, \"status\":\"sunny\"}"
#define CUSTOM_WEATHER_DATA2 "{\"temperature\": -1, \"status\":\"snowy\"}"
// Invalid KEY
#define CUSTOM_WEATHER_DATA_INVALID_KEY "{\"humidity\": 20, \"status\":\"cloudy\"}"
// Invalid value
#define CUSTOM_WEATHER_DATA_INVALID_VAL_INT "{\"temperature\": -100, \"status\":\"cloudy\"}"
#define CUSTOM_WEATHER_DATA_INVALID_VAL_STR "{\"temperature\": 30, \"status\":\"windy\"}"
// Invalid type
#define CUSTOM_WEATHER_DATA_INVALID_TYPE "{\"temperature\": 20, \"status\": 50}"
// Invalid json
#define CUSTOM_WEATHER_DATA_INVALID_JSON "{\"temperature\": 30 \"status\":\"sunny\"}"


#endif // __UTC_CONTEXT_TRIGGER_CUSTOM_H__
