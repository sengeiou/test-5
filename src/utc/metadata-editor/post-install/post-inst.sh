#!/bin/bash
#
# Copyright (c) 2016 Samsung Electronics Co., Ltd.
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

# extract TCT configuration directory from TCT_CONFIG_FILE (/home/owner/share/TCT_CONFIG)
APP_DIR=/usr/apps
TCT_CONFIG_FILE=/home/owner/share/TCT_CONFIG
PKG_NAME=$1
MODE=$2

if [ $PKG_NAME == "" ] || [ $MODE == "" ]; then
	echo ""
	echo "****************FATAL ERROR : post-inst.sh***************************"
	echo "PackageName/Mode is not supplied with post-inst.sh"
	echo "Necessary Resource Files if any can not be processed"
	echo "********************************************************************"
	echo ""
	return;
fi

if [ ! -f $TCT_CONFIG_FILE ];then
	echo ""
	echo "****************FATAL ERROR : $PKG_NAME/post-inst.sh***************************"
	echo "$TCT_CONFIG_FILE is not Found : Can Not Read TCT Configuration Directory"
	echo "$PKG_NAME : Necessary Resource Files if any can not be processed"
	echo "********************************************************************"
	echo ""
	return;
fi
DEVICE_SUITE_TARGET_30=`cat $TCT_CONFIG_FILE | grep DEVICE_SUITE_TARGET_30 | cut -f 2- -d '='`
if [ $DEVICE_SUITE_TARGET_30 == "" ]; then
	echo ""
	echo "****************FATAL ERROR : $PKG_NAME/post-inst.sh***************************"
	echo "'DEVICE_SUITE_TARGET_30' key-value pair is not Found"
	echo "$PKG_NAME : Necessary Resource Files if any can not be processed"
	echo "********************************************************************"
	echo ""
	return;
fi
DEVICE_USER_30=`cat $TCT_CONFIG_FILE | grep DEVICE_USER_30 | cut -f 2- -d '='`
if [ $DEVICE_USER_30 == "" ]; then
	echo ""
	echo "****************FATAL ERROR : $PKG_NAME/post-inst.sh***************************"
	echo "'DEVICE_USER_30' key-value pair is not Found"
	echo "$PKG_NAME : Necessary Resource Files if any can not be processed"
	echo "********************************************************************"
	echo ""
	return;
fi
DEVICE_PHYSICAL_STORAGE_30=`cat $TCT_CONFIG_FILE | grep DEVICE_PHYSICAL_STORAGE_30 | cut -f 2- -d '='`
if [ $DEVICE_PHYSICAL_STORAGE_30 == "" ]; then
	echo ""
	echo "****************FATAL ERROR : $PKG_NAME/post-inst.sh***************************"
	echo "'DEVICE_PHYSICAL_STORAGE_30' key-value pair is not Found"
	echo "$PKG_NAME : Necessary Resource Files if any can not be processed"
	echo "********************************************************************"
	echo ""
	return;
fi


if [ $MODE == "inst" ]; then
	echo "Installing pre-requisites for the package $PKG_NAME"
	mkdir -p $DEVICE_USER_30/apps_rw/core-metadata-editor-tests/data/
	cp $APP_DIR/$PKG_NAME/data/* $DEVICE_USER_30/apps_rw/core-metadata-editor-tests/data/
	chown -R 5001:100 $DEVICE_USER_30/apps_rw/core-metadata-editor-tests/data/
	echo "Installing the pre-requisites for the package $PKG_NAME ======> Completed"
else
	echo "Un-installing the pre-requisites for the package $PKG_NAME"
	echo "Un-installing the pre-requisites for the package $PKG_NAME ======> Completed"
fi
