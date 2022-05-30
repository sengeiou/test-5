#!/bin/bash
#
# Copyright (c) 2014 Samsung Electronics Co., Ltd.
#
# Licensed under the Apache License, Version 2.0 (the License);
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http:#www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

PROJECT_DIR="$(cd "$(dirname $0)" && cd .. && pwd)"
sudo ln -sf $HOME/tizen-studio/tools/ide/bin/tizen.sh /usr/bin/tizen

tizen cli-config default.profiles.path=$HOME/tizen-studio-data/profile/profiles.xml

sudo ln -sf ./scripts_tpk/tpkbuild.sh $PROJECT_DIR/tpkbuild
sudo ln -sf ./scripts_tpk/tc_info.sh $PROJECT_DIR/tc_info
