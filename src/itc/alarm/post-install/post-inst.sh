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
	chown -R owner:users $APP_DIR/$PKG_NAME/data
	chown -R owner:users $APP_DIR/$PKG_NAME/res
	echo "Installing the pre-requisites for the package $PKG_NAME ======> Completed"
else
	echo "Un-installing the pre-requisites for the package $PKG_NAME"
	echo "Un-installing the pre-requisites for the package $PKG_NAME ======> Completed"
fi



##UEP630x1662164e85f4ce5c46266d3f7b2dac8baab9cf6d487f4c0ddbcb992e4d9e292d044867f742fbb0905906c431351e9021b3003078f36d7d4129a3986765684af88e2d9d422a7d551b6131e4e03ceb46058fc6e434e53ebf5198fcc97865f22067b19e4d919dcb138db8535557edc6f4c97fac9c95cd80c5d2fdfb8c7e47d5a8f9bc9b4fe1807d96a2c18276eb5174026e8c3d77b145fae5284568c77ca803c72967121a401a716ff52347161c3ca95eb1de3163ae4152c9947ee1ade676fc00e88d1c25319f05547cc1b73217e97bcdab1d3ceb82f994597cdbe69bdd980accc6b27c8189e177e70ffc23e540e79e99c36387f798a34890b90a86530d231cb030AAACAg==:UEP
