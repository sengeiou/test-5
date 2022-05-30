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
	mkdir -p $DEVICE_PHYSICAL_STORAGE_30
	mkdir -p $DEVICE_PHYSICAL_STORAGE_30/P1
	mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/track/sequence
	cp $APP_DIR/$PKG_NAME/data/P1/09.jpg $DEVICE_PHYSICAL_STORAGE_30/P1
	cp $APP_DIR/$PKG_NAME/data/res/track/sequence/*.jpg $DEVICE_PHYSICAL_STORAGE_30/res/track/sequence/

	chmod -R 777 $APP_DIR/$PKG_NAME/data
	chmod -R 777 $DEVICE_PHYSICAL_STORAGE_30/res
	chown -R 5000:5000 $APP_DIR/$PKG_NAME/data
	chown -R 5001:100 $DEVICE_PHYSICAL_STORAGE_30/res
	chsmack -a $PKG_NAME $APP_DIR/$PKG_NAME/data
	echo "Installing the pre-requisites for the package $PKG_NAME ======> Completed"
else
	echo "Un-installing the pre-requisites for the package $PKG_NAME"
	rm -rf $DEVICE_PHYSICAL_STORAGE_30/P1
	rm -rf $DEVICE_PHYSICAL_STORAGE_30/res
	echo "Un-installing the pre-requisites for the package $PKG_NAME ======> Completed"
fi

##UEP630x6581c89df89192cd393bdd9b2ec4801ee2e8e3bc3c4e9c8ca07ae9f9c8aa60aaecd9cf837cdb175388eda0f47dff2c26ea6fe4a19338d5504d6049860257ef765aa68c994d3fff37d5e740496e5f2346fc907ca3ceb307c97dd60bc152e25837aa84e96190b8ebdd107b60f1a146d984b09de23fa51b61b080e9629fb5d9f9290d51a3ab56312c658a04a9a4fa9f46f561091629a48fb9b9fca5cf25e3af1fc66fae436d87b39cc41834f777a236768351e5a9d3043fdf7c853eb7a857f5174e4c4a8207f834e3adfc05603285ad1a7951a5aeaf3295b4f9a18b894142ad85e0032112b547539795b37e2d0a9401631b954d1046da16a3ad2a5a380909f3e35dAAACAg==:UEP