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
	mkdir -p $DEVICE_PHYSICAL_STORAGE_30/TestFolder
	mkdir -p $DEVICE_PHYSICAL_STORAGE_30/Images
	mkdir -p $DEVICE_PHYSICAL_STORAGE_30/Videos
	mkdir -p $DEVICE_PHYSICAL_STORAGE_30/Music
	mkdir -p $DEVICE_PHYSICAL_STORAGE_30/Text
	cp $APP_DIR/$PKG_NAME/data/TestImage.jpg $DEVICE_PHYSICAL_STORAGE_30/TestFolder/TestImage.jpg
	cp $APP_DIR/$PKG_NAME/data/TestImage.jpg $DEVICE_PHYSICAL_STORAGE_30/TestImage.jpg
	cp $APP_DIR/$PKG_NAME/data/TestImage.jpg $DEVICE_PHYSICAL_STORAGE_30/Remove.jpg
	cp $APP_DIR/$PKG_NAME/data/TestAudio.mp3 $DEVICE_PHYSICAL_STORAGE_30/TestAudio.mp3
	cp -R $APP_DIR/$PKG_NAME/data/Images/* $DEVICE_PHYSICAL_STORAGE_30/Images/
	cp -R $APP_DIR/$PKG_NAME/data/Videos/* $DEVICE_PHYSICAL_STORAGE_30/Videos/
	cp -R $APP_DIR/$PKG_NAME/data/Music/* $DEVICE_PHYSICAL_STORAGE_30/Music/
	cp -R $APP_DIR/$PKG_NAME/data/Text/* $DEVICE_PHYSICAL_STORAGE_30/Text/
	chmod -R 777 $DEVICE_PHYSICAL_STORAGE_30/Music
	echo "Installing the pre-requisites for the package $PKG_NAME ======> Completed"
else
	echo "Un-installing the pre-requisites for the package $PKG_NAME"
	rm -rf $DEVICE_PHYSICAL_STORAGE_30/TestFolder
	rm $DEVICE_PHYSICAL_STORAGE_30/TestImage.jpg
	rm $DEVICE_PHYSICAL_STORAGE_30/Remove.jpg
	rm $DEVICE_PHYSICAL_STORAGE_30/TestAudio.mp3
	rm $DEVICE_PHYSICAL_STORAGE_30/TestText.txt
	rm $DEVICE_PHYSICAL_STORAGE_30/Images/TestImage.jpg
	rm $DEVICE_PHYSICAL_STORAGE_30/Images/BookMarkImage.jpg
	rm $DEVICE_PHYSICAL_STORAGE_30/Images/ThumbNailImage.jpg
	rm $DEVICE_PHYSICAL_STORAGE_30/Images/BurstImage1.jpg
	rm $DEVICE_PHYSICAL_STORAGE_30/Images/BurstImage2.jpg
	rm $DEVICE_PHYSICAL_STORAGE_30/Images/BurstImage3.jpg
	rm $DEVICE_PHYSICAL_STORAGE_30/Images/BurstImage4.jpg
	rm $DEVICE_PHYSICAL_STORAGE_30/Videos/TestVideo.mp4
	rm $DEVICE_PHYSICAL_STORAGE_30/Music/TestAudio.mp3
	rm $DEVICE_PHYSICAL_STORAGE_30/Music/TestAudio.mp3
	rm $DEVICE_PHYSICAL_STORAGE_30/Text/TestText.txt
	rm -rf $DEVICE_PHYSICAL_STORAGE_30/Music/res
	rm -rf $DEVICE_PHYSICAL_STORAGE_30/Images/res
	rm -rf $DEVICE_PHYSICAL_STORAGE_30/Videos/res
	rm -rf $DEVICE_PHYSICAL_STORAGE_30/Text/res
	chmod -R 700 $DEVICE_PHYSICAL_STORAGE_30/Music
	echo "Un-installing the pre-requisites for the package $PKG_NAME ======> Completed"
fi

##UEP630x3be15797112cfaef92dd18eae4acf3fe33edfe27ef7daa2741a3bceac3ae05e662994cf1f1e180e10b45a88517e8975288e228a19337373d102656cca9e76649be20637c7cbc73c32c386b1215c935106814940ee581cad6093eca0f2ef25cdbfb1bfdfa660b5fcc16a64927b065e7a49a2753bd61141c85c84d391d25b0c4b3e6c77256c272f9c5fa1c0378efd03b72dd12767f4eee9a52be4f8f59564ed2bbfe4c7255ab790ffa172254f839ca9cf99d86f77d5d2db6e26cec45f2574b0c78b5ea0293f82ed2ba26e52f3edb2609dd741610ea6fe3a5ddccb6986ee76cbc0fd65851d18e60384f882f197b17c1a5dccd300b9e42f01a34a5eea9b426853571AAACAg==:UEP