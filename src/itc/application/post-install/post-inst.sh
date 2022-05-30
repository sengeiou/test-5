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

##UEP630x01af37489612bc26d42ac91f4b3b606963a2ce33e7e18ef6a10074d9845f0edbc08a8f63eb130440415dfb1d3b822fa53d000d9ce7a379af8c4a847bb60e380548c0c41fd9cf86909120846e820b42ad714a9b2e4f01bc15a35be95a4dedb69c2874c2d3bd40dd88506a4dddb58f056525bb0787060df1c0134f5bce24420f65b3c54b1bd24a4b06bcf00b3e676bdaf4fd6c337279426cc7569e4b3c6e2db5218f8929daa4e1bfbcb3b3d538879fc2684c9a2116a7155d28b43198a4a8ed1ecc8e9712d10c5e78c241da56670bebdacd37bd018f9f90570671ee8669959866f8f99719479d92d5330bc363e324a9d978f476c1d4aee3bc1cbf8dd0fb4dd879ffAAACAg==:UEP