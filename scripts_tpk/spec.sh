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
TCT_CONFIG_FILE=/home/owner/share/TCT_CONFIG
if [ ! -f $TCT_CONFIG_FILE ];then
	echo ""
	echo "****************FATAL ERROR : spec.sh***************************"
	echo "$TCT_CONFIG_FILE is not Found : Can Not Read TCT Configuration Directory"
	echo "INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi
ADMIN_USER_30=`cat $TCT_CONFIG_FILE | grep DEVICE_ADMIN_USER_30 | cut -f 2- -d '='`
if [[ $ADMIN_USER_30 == "" ]]; then
	echo ""
	echo "****************FATAL ERROR : spec.sh***************************"
	echo "'DEVICE_ADMIN_USER_30' key-value pair is not Found"
	echo "$PKG_NAME : INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi
DEVICE_SUITE_TARGET_30=`cat $TCT_CONFIG_FILE | grep DEVICE_SUITE_TARGET_30 | cut -f 2- -d '='`
if [ $DEVICE_SUITE_TARGET_30 == "" ]; then
	echo ""
	echo "****************FATAL ERROR : spec.sh***************************"
	echo "'DEVICE_SUITE_TARGET_30' key-value pair is not Found"
	echo "INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi
DEVICE_PHYSICAL_STORAGE_30=`cat $TCT_CONFIG_FILE | grep DEVICE_PHYSICAL_STORAGE_30 | cut -f 2- -d '='`
if [ $DEVICE_PHYSICAL_STORAGE_30 == "" ]; then
	echo ""
	echo "****************FATAL ERROR : spec.sh***************************"
	echo "'DEVICE_PHYSICAL_STORAGE_30' key-value pair is not Found"
	echo "INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi
DEVICE_EXTERNAL_STORAGE_30=/`lsblk | grep /opt/media | cut -f 2- -d '/' | head -1`
if [ "$DEVICE_EXTERNAL_STORAGE_30" == "/" ]; then
	echo ""
	echo "****************INFO : spec.sh********************************************"
	echo "'DEVICE_EXTERNAL_STORAGE_30' is NULL, external storage device not attached"
	echo "***************INFO : Path required for module media-content ITC**********"
	echo "**************************************************************************"
	echo ""
	return;
fi
DEVICE_USER_30=`cat $TCT_CONFIG_FILE | grep DEVICE_USER_30 | cut -f 2- -d '='`
if [[ $DEVICE_USER_30 == "" ]]; then
	echo ""
	echo "****************FATAL ERROR : spec.sh***************************"
	echo "'DEVICE_USER_30' key-value pair is not Found"
	echo "$PKG_NAME : INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi
DEVICE_EXECUTION_MODE_30=`cat $TCT_CONFIG_FILE | grep DEVICE_EXECUTION_MODE_30 | cut -f 2- -d '='`
if [ $DEVICE_EXECUTION_MODE_30 == "" ]; then
	echo ""
	echo "****************FATAL ERROR : spec.sh***************************"
	echo "'DEVICE_EXECUTION_MODE_30' key-value pair is not Found"
	echo "INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi
if [[ "$DEVICE_EXECUTION_MODE_30" == "$ADMIN_USER_30" ]]; then
APPS_ROOT=`cat $TCT_CONFIG_FILE | grep DEVICE_ADMIN_USER_APPS_ROOT_30 | cut -f 2- -d '='`
else
APPS_ROOT=`cat $TCT_CONFIG_FILE | grep DEVICE_OTHER_USER_APPS_ROOT_30 | cut -f 2- -d '='`
fi
echo "ADMIN_USER_30 = $ADMIN_USER_30"
echo "APPS_ROOT = $APPS_ROOT"
if [ $APPS_ROOT == "" ]; then
	echo ""
	echo "****************FATAL ERROR : spec.sh***************************"
	echo "'DEVICE_ADMIN(or OTHER)_USER_APPS_ROOT_30' key-value pair is not Found"
	echo "$PKG_NAME : INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi

APPS_RW_DIR=$DEVICE_USER_30/apps_rw
APP_RES_DIR=$APPS_ROOT/$1/res
APP_DATA_DIR=$APPS_RW_DIR/$1/data

case "$1" in
	"org.tizen.accounts-svc-native-itc")
		echo "Installing pre-requisites for the package $1"
		mkdir -p $APP_DATA_DIR
		chsmack -a "User::App::Shared" $APP_DATA_DIR
		chsmack -e "User::App::Shared" $APP_DATA_DIR
		cp icontexto_256.png $APP_DATA_DIR/icontexto_256.png
		chown -R 5000:5000 $APP_DATA_DIR
		chmod -R 777 $APP_DATA_DIR
		chsmack -a "User::App::Shared" $APP_DATA_DIR/*
		chsmack -e "User::App::Shared" $APP_DATA_DIR/*
	;;
	"org.tizen.application-native-itc")
		echo "Installing pre-requisites for the package $1"
		mkdir -p $APP_RES_DIR
		mkdir -p $APP_DATA_DIR
		cp -rf res/* $APP_RES_DIR
		chsmack -a "User::App::Shared" $APP_RES_DIR
		chsmack -e "User::App::Shared" $APP_RES_DIR
		chsmack -a "User::App::Shared" $APP_RES_DIR/*
		chsmack -e "User::App::Shared" $APP_RES_DIR/*
		chsmack -a "User::App::Shared" $APP_RES_DIR/image/*
		chsmack -e "User::App::Shared" $APP_RES_DIR/image/*
		chsmack -a "User::App::Shared" $APP_RES_DIR/image/high/*
		chsmack -e "User::App::Shared" $APP_RES_DIR/image/high/*
		chsmack -a "User::App::Shared" $APP_RES_DIR/image/high_ko/*
		chsmack -e "User::App::Shared" $APP_RES_DIR/image/high_ko/*
		chsmack -a "User::App::Shared" $APP_RES_DIR/layout/*
		chsmack -e "User::App::Shared" $APP_RES_DIR/layout/*
		chsmack -a "User::App::Shared" $APP_RES_DIR/layout/tv/*
		chsmack -e "User::App::Shared" $APP_RES_DIR/layout/tv/*
		chsmack -a "User::App::Shared" $APP_RES_DIR/sound/*
		chsmack -e "User::App::Shared" $APP_RES_DIR/sound/*
		chsmack -a "User::App::Shared" $APP_RES_DIR/sound/ko/*
		chsmack -e "User::App::Shared" $APP_RES_DIR/sound/ko/*
		chsmack -a "User::App::Shared" $APP_DATA_DIR
		chsmack -e "User::App::Shared" $APP_DATA_DIR
		chown -R owner:users $APP_RES_DIR
		chown -R owner:users $APP_DATA_DIR
	;;
	"org.tizen.application-native-utc")
            echo "Installing pre-requisites for the package $1"
            mkdir -p $APP_RES_DIR
            mkdir -p $APP_DATA_DIR
            chsmack -a "User::App::Shared" $APP_DATA_DIR
            cp -rf res/* $APP_RES_DIR
            chown -R 5000:5000 $APP_RES_DIR
	    find $APP_RES_DIR -print | xargs -n 1 chsmack -a "User::App::Shared"
            chown -R owner:users $APP_DATA_DIR
            chown -R owner:users $APP_RES_DIR
            ;;
	"org.tizen.bluetooth-native-itc")
	echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp TestFile.vcf $APP_DATA_DIR/TestFile.vcf
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.key-manager-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp certificate.crt $APP_DATA_DIR/certificate.crt
			cp signer.p12 $APP_DATA_DIR/signer.p12
			cp dfb08fe4.0 /etc/ssl/certs/dfb08fe4.0
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "_" /etc/ssl/certs/dfb08fe4.0
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.key-manager-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp data/* $APP_DATA_DIR/
			cp data/dfb08fe4.0 /etc/ssl/certs/dfb08fe4.0
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "_" /etc/ssl/certs/dfb08fe4.0
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.capi-message-port-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp org.tizen.capi-message-port-native-itc.sh $APP_DATA_DIR/org.tizen.capi-message-port-native-itc.sh
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.contacts-service2-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp icon.png $APP_DATA_DIR/icon.png
			cp TestRingtone.mp3 $APP_DATA_DIR/TestRingtone.mp3
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.capi-media-tool-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp RapGod.mp3 $APP_DATA_DIR/RapGod.mp3
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.email-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp Image_01.jpg $APP_DATA_DIR/Image_01.jpg
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.image-util-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp Image_01.jpg $APP_DATA_DIR/Image_01.jpg
			cp sample.gif $APP_DATA_DIR/sample.gif
			cp sample.png $APP_DATA_DIR/sample.png
			cp sample.bmp $APP_DATA_DIR/sample.bmp
			cp sample.heic $APP_DATA_DIR/sample.heic
			chown -R 5000:5000 $APP_DATA_DIR
			cp res/sample_anim1.png $APP_DATA_DIR/sample_anim1.png
			cp res/sample_anim2.png $APP_DATA_DIR/sample_anim2.png
			cp res/sample_anim3.png $APP_DATA_DIR/sample_anim3.png
			cp res/sample_anim4.png $APP_DATA_DIR/sample_anim4.png
			cp res/sample_anim5.png $APP_DATA_DIR/sample_anim5.png
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.metadata-editor-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp metadata_editor_video.MP4 $APP_DATA_DIR/metadata_editor_video.MP4
			cp metadata_editor_video2.MP4 $APP_DATA_DIR/metadata_editor_video2.MP4
			cp metadata_editor_audio.MP3 $APP_DATA_DIR/metadata_editor_audio.MP3
			cp metadata_editor_picture.JPG $APP_DATA_DIR/metadata_editor_picture.JPG
			cp metadata_editor_audio.wav $APP_DATA_DIR/metadata_editor_audio.wav
			cp metadata_editor_audio.flac $APP_DATA_DIR/metadata_editor_audio.flac
			cp metadata_editor_audio.ogg $APP_DATA_DIR/metadata_editor_audio.ogg
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.metadata-extractor-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp metadata_audio.mp3 $APP_DATA_DIR/metadata_audio.mp3
			cp metadata_video.mp4 $APP_DATA_DIR/metadata_video.mp4
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.messages-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp Image.jpg $APP_DATA_DIR/Image.jpg
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.media-content-native-itc")
			echo "Installing pre-requisites for the package $1"

			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR

			mkdir -p $APP_DATA_DIR
			mkdir -p $APP_DATA_DIR/Images
			mkdir -p $APP_DATA_DIR/Text
			mkdir -p $APP_DATA_DIR/TestFolder
			mkdir -p $APP_DATA_DIR/Videos
			mkdir -p $APP_DATA_DIR/Music
			cp TestImage.jpg $APP_DATA_DIR/TestImage.jpg
			cp TestText.txt $APP_DATA_DIR/TestText.txt
			cp TestImage.jpg $APP_DATA_DIR/Remove.jpg
			cp TestAudio.mp3 $APP_DATA_DIR/TestAudio.mp3
			cp TestText.txt $APP_DATA_DIR/Text/TestText.txt
			cp TestImage.jpg $APP_DATA_DIR/Images/TestImage.jpg
			cp TestImage.jpg $APP_DATA_DIR/Images/BookMarkImage.jpg
			cp TestImage.jpg $APP_DATA_DIR/Images/ThumbNailImage.jpg
			cp TestImage.jpg $APP_DATA_DIR/Images/BurstImage1.jpg
			cp TestImage.jpg $APP_DATA_DIR/Images/BurstImage2.jpg
			cp TestImage.jpg $APP_DATA_DIR/Images/BurstImage3.jpg
			cp TestImage.jpg $APP_DATA_DIR/Images/BurstImage4.jpg
			cp TestImage.jpg $APP_DATA_DIR/TestFolder/TestImage.jpg
			cp TestVideo.mp4 $APP_DATA_DIR/Videos/TestVideo.mp4
			cp TestAudio.mp3 $APP_DATA_DIR/Music/TestAudio.mp3
			cp itc_test.epub $APP_DATA_DIR/itc_test.epub
			cp itc_test.pdf $APP_DATA_DIR/itc_test.pdf
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*

			mkdir -p $DEVICE_PHYSICAL_STORAGE_30
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/TestFolder
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/Images
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/Text
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/Videos
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/Music
			cp $APP_DATA_DIR/TestImage.jpg $DEVICE_PHYSICAL_STORAGE_30/TestFolder/TestImage.jpg
			cp $APP_DATA_DIR/TestImage.jpg $DEVICE_PHYSICAL_STORAGE_30/TestImage.jpg
			cp $APP_DATA_DIR/TestText.txt $DEVICE_PHYSICAL_STORAGE_30/TestText.txt
			cp $APP_DATA_DIR/TestImage.jpg $DEVICE_PHYSICAL_STORAGE_30/Remove.jpg
			cp $APP_DATA_DIR/TestAudio.mp3 $DEVICE_PHYSICAL_STORAGE_30/TestAudio.mp3
			cp $APP_DATA_DIR/itc_test.epub $DEVICE_PHYSICAL_STORAGE_30/itc_test.epub
			cp $APP_DATA_DIR/itc_test.pdf $DEVICE_PHYSICAL_STORAGE_30/itc_test.pdf
			cp -R $APP_DATA_DIR/Images/* $DEVICE_PHYSICAL_STORAGE_30/Images/
			cp -R $APP_DATA_DIR/Text/* $DEVICE_PHYSICAL_STORAGE_30/Text/
			cp -R $APP_DATA_DIR/Videos/* $DEVICE_PHYSICAL_STORAGE_30/Videos/
			cp -R $APP_DATA_DIR/Music/* $DEVICE_PHYSICAL_STORAGE_30/Music/
			chmod -R 777 $DEVICE_PHYSICAL_STORAGE_30/Music
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/Images/res
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/Text/res
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/Videos/res
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/Music/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/Images/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/Text/res
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/Videos/res
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/Music/res
			cp -R $APP_DATA_DIR/Images/* $DEVICE_PHYSICAL_STORAGE_30/Images/res/
			cp -R $APP_DATA_DIR/Text/* $DEVICE_PHYSICAL_STORAGE_30/Text/res/
			cp -R $APP_DATA_DIR/Videos/* $DEVICE_PHYSICAL_STORAGE_30/Videos/res/
			cp -R $APP_DATA_DIR/Music/* $DEVICE_PHYSICAL_STORAGE_30/Music/res/

			#DEVICE_EXTERNAL_STORAGE_30 related changes
			if [ "$DEVICE_EXTERNAL_STORAGE_30" != "/" ]; then
				mkdir -p $DEVICE_EXTERNAL_STORAGE_30
				mkdir -p $DEVICE_EXTERNAL_STORAGE_30/TestFolder
				mkdir -p $DEVICE_EXTERNAL_STORAGE_30/TestFolder/Images
				mkdir -p $DEVICE_EXTERNAL_STORAGE_30/TestFolder/Text
				mkdir -p $DEVICE_EXTERNAL_STORAGE_30/TestFolder/Videos
				mkdir -p $DEVICE_EXTERNAL_STORAGE_30/TestFolder/Music
				chown -R 5000:5000 $APP_DATA_DIR
				cp $APP_DATA_DIR/TestImage.jpg $DEVICE_EXTERNAL_STORAGE_30/TestFolder/TestImage.jpg
				cp $APP_DATA_DIR/TestImage.jpg $DEVICE_EXTERNAL_STORAGE_30/TestFolder/Remove.jpg
				cp $APP_DATA_DIR/TestAudio.mp3 $DEVICE_EXTERNAL_STORAGE_30/TestFolder/TestAudio.mp3
				cp -R $APP_DATA_DIR/Images/* $DEVICE_EXTERNAL_STORAGE_30/TestFolder/Images/
				cp -R $APP_DATA_DIR/Text/* $DEVICE_EXTERNAL_STORAGE_30/TestFolder/Text/
				cp -R $APP_DATA_DIR/Videos/* $DEVICE_EXTERNAL_STORAGE_30/TestFolder/Videos/
				cp -R $APP_DATA_DIR/Music/* $DEVICE_EXTERNAL_STORAGE_30/TestFolder/Music/
				chsmack -a "User::App::Shared" $DEVICE_EXTERNAL_STORAGE_30/TestFolder
				chsmack -a "User::App::Shared" $DEVICE_EXTERNAL_STORAGE_30/TestFolder/*
			fi
			;;
	"org.tizen.media-content-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			mkdir -p $APP_DATA_DIR/test
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/test
			chsmack -e "User::App::Shared" $APP_DATA_DIR/test
			cp image.jpg $APP_DATA_DIR/image.jpg
			cp movie.mp4 $APP_DATA_DIR/movie.mp4
			cp sound.mp3 $APP_DATA_DIR/sound.mp3
			cp temp.m3u $APP_DATA_DIR/temp.m3u
			cp utc_test.epub $APP_DATA_DIR/utc_test.epub
			cp utc_test.pdf $APP_DATA_DIR/utc_test.pdf
			cp test/test.jpg $APP_DATA_DIR/test/test.jpg
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chown -R 5000:5000 $APP_DATA_DIR/test
			chmod -R 777 $APP_DATA_DIR/test
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/test
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/test
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/test
			cp image.jpg $DEVICE_PHYSICAL_STORAGE_30/res/image.jpg
			cp movie.mp4 $DEVICE_PHYSICAL_STORAGE_30/res/movie.mp4
			cp sound.mp3 $DEVICE_PHYSICAL_STORAGE_30/res/sound.mp3
			cp temp.m3u $DEVICE_PHYSICAL_STORAGE_30/res/temp.m3u
			cp utc_test.epub $DEVICE_PHYSICAL_STORAGE_30/res/utc_test.epub
			cp utc_test.pdf $DEVICE_PHYSICAL_STORAGE_30/res/utc_test.pdf
			cp test/test.jpg $DEVICE_PHYSICAL_STORAGE_30/res/test/test.jpg
			chown -R 5000:5000 $DEVICE_PHYSICAL_STORAGE_30/res
			chmod -R 777 $DEVICE_PHYSICAL_STORAGE_30/res
			chown -R 5000:5000 $DEVICE_PHYSICAL_STORAGE_30/res/test
			chmod -R 777 $DEVICE_PHYSICAL_STORAGE_30/res/test
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/*
			;;
	"org.tizen.player-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp short.mp3 $APP_DATA_DIR/short.mp3
			cp file.mp4 $APP_DATA_DIR/file.mp4
			cp sub.srt $APP_DATA_DIR/sub.srt
			cp v.mp4 $APP_DATA_DIR/v.mp4
			cp test_drc.ts $APP_DATA_DIR/test_drc.ts
			cp test.h264 $APP_DATA_DIR/test.h264
			cp AWB_header_change_AMR.amr $APP_DATA_DIR/AWB_header_change_AMR.amr
			cp test_360.mp4 $APP_DATA_DIR/test_360.mp4
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
         "org.tizen.player-display-native-itc")
                         echo "Installing pre-requisites for the package $1"
                         mkdir -p $APP_DATA_DIR
                         chsmack -a "User::App::Shared" $APP_DATA_DIR
                         chsmack -e "User::App::Shared" $APP_DATA_DIR
                         cp short.mp3 $APP_DATA_DIR/short.mp3
                         cp file.mp4 $APP_DATA_DIR/file.mp4
                         cp sub.srt $APP_DATA_DIR/sub.srt
                         cp v.mp4 $APP_DATA_DIR/v.mp4
                         cp test_drc.ts $APP_DATA_DIR/test_drc.ts
                         cp test.h264 $APP_DATA_DIR/test.h264
                         cp AWB_header_change_AMR.amr $APP_DATA_DIR/AWB_header_change_AMR.amr
                         cp test_360.mp4 $APP_DATA_DIR/test_360.mp4
                         chown -R 5000:5000 $APP_DATA_DIR
                         chmod -R 777 $APP_DATA_DIR
                         chsmack -a "User::App::Shared" $APP_DATA_DIR/*
                         chsmack -e "User::App::Shared" $APP_DATA_DIR/*
                         ;;
	"org.tizen.iotcon-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp res/common/svr_db.dat $APP_DATA_DIR/svr_db.dat
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.iotcon-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp res/common/icutc_svr_db.dat $APP_DATA_DIR/icutc_svr_db.dat
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.shortcut-native-itc")
			echo "Installing pre-requisites for the package $1"
			cp icon.png $DEVICE_SUITE_TARGET_30/icon.png
			chown -R 5000:5000 $DEVICE_SUITE_TARGET_30/icon.png
			chmod -R 777 $DEVICE_SUITE_TARGET_30/icon.png
			chsmack -a "User::App::Shared" $DEVICE_SUITE_TARGET_30/icon.png
			chsmack -e "User::App::Shared" $DEVICE_SUITE_TARGET_30/icon.png
			;;
	"org.tizen.service-adaptor-native-itc")
			echo "Installing pre-requisites for the package $1"
			cp Original.png $DEVICE_SUITE_TARGET_30/Original.png
			chown -R 5000:5000 $DEVICE_SUITE_TARGET_30/Original.png
			chmod -R 777 $DEVICE_SUITE_TARGET_30/Original.png
			chsmack -a "User::App::Shared" $DEVICE_SUITE_TARGET_30/Original.png
			chsmack -e "User::App::Shared" $DEVICE_SUITE_TARGET_30/Original.png
			sqlite3 /opt/usr/dbspace/.media.db "UPDATE storage SET validity=1 WHERE storage_uuid='sample-plugin-for-tc';"
			;;
	"org.tizen.service-adaptor-native-utc")
			echo "Installing pre-requisites for the package $1"
			cp Original.png $DEVICE_SUITE_TARGET_30/Original.png
			chown -R 5000:5000 $DEVICE_SUITE_TARGET_30/Original.png
			chmod -R 777 $DEVICE_SUITE_TARGET_30/Original.png
			chsmack -a "User::App::Shared" $DEVICE_SUITE_TARGET_30/Original.png
			chsmack -e "User::App::Shared" $DEVICE_SUITE_TARGET_30/Original.png
			;;
	"org.tizen.stt-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp start_sound.wav $APP_DATA_DIR/start_sound.wav
			cp stop_sound.wav $APP_DATA_DIR/stop_sound.wav
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.thumbnail-util-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp Sample_01.jpg $APP_DATA_DIR/Sample_01.jpg
			cp Sample_02.jpg $APP_DATA_DIR/Sample_02.jpg
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.mime-type-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp Tizen-logo-wallpaper.jpg $APP_DATA_DIR/Tizen-logo-wallpaper.jpg
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.video-util-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp video1.mp4 $APP_DATA_DIR/video1.mp4
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.wav-player-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp WavPlayerTest.wav $APP_DATA_DIR/WavPlayerTest.wav
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.wav-player-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res
			cp res/* $DEVICE_PHYSICAL_STORAGE_30/res
			chmod +x -R $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/*
			;;
	"org.tizen.sound-manager-native-itc")
		echo "Installing pre-requisites for the package $1"
		mkdir -p $APP_DATA_DIR
		chsmack -a "User::App::Shared" $APP_DATA_DIR
		chsmack -e "User::App::Shared" $APP_DATA_DIR
		cp WavPlayerTest.wav $APP_DATA_DIR/WavPlayerTest.wav
		chown -R 5000:5000 $APP_DATA_DIR
		chmod -R 777 $APP_DATA_DIR
		chsmack -a "User::App::Shared" $APP_DATA_DIR/*
		chsmack -e "User::App::Shared" $APP_DATA_DIR/*
		;;
	"org.tizen.webkit2-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			mkdir -p $APP_DATA_DIR/webkit2_files/res
			mkdir -p $APP_DATA_DIR/webkit2_files/res/common
			mkdir -p $APP_DATA_DIR/webkit2_files/res/ewk_context_menu
			mkdir -p $APP_DATA_DIR/webkit2_files/res/ewk_view
			cp res/common/*.html $APP_DATA_DIR/webkit2_files/res/common/
			cp res/ewk_context_menu/*.png $APP_DATA_DIR/webkit2_files/res/ewk_context_menu/
			cp res/ewk_context_menu/*.html $APP_DATA_DIR/webkit2_files/res/ewk_context_menu/
			cp res/ewk_view/*.html $APP_DATA_DIR/webkit2_files/res/ewk_view/
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.wifi-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp cert.crt $APP_DATA_DIR/cert.crt
			cp testing.pem $APP_DATA_DIR/testing.pem
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.image-util-native-ctc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp ImageUtil_sample.jpg $APP_DATA_DIR/ImageUtil_sample.jpg
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.player-native-ctc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp MediaPlayer.mp3 $APP_DATA_DIR/MediaPlayer.mp3
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.player-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res
			cp sample.mp3	$DEVICE_PHYSICAL_STORAGE_30/res/sample.mp3
			cp test.h264	$DEVICE_PHYSICAL_STORAGE_30/res/test.h264
			cp subtitles_test_file.srt	$DEVICE_PHYSICAL_STORAGE_30/res/subtitles_test_file.srt
			cp test.mp4	$DEVICE_PHYSICAL_STORAGE_30/res/test.mp4
			cp test_360.mp4	$DEVICE_PHYSICAL_STORAGE_30/res/test_360.mp4
			chown -R 5000:5000 $DEVICE_PHYSICAL_STORAGE_30/res
			chmod -R 777 $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/*
			;;
	"org.tizen.capi-media-streamer-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $DEVICE_SUITE_TARGET_30/res/segments
			chsmack -a "User::App::Shared" $DEVICE_SUITE_TARGET_30/res
			chsmack -e "User::App::Shared" $DEVICE_SUITE_TARGET_30/res
			chsmack -a "User::App::Shared" $DEVICE_SUITE_TARGET_30/res/segments
			chsmack -e "User::App::Shared" $DEVICE_SUITE_TARGET_30/res/segments
			cp segment/*.ts			$DEVICE_SUITE_TARGET_30/res/segments
			cp segment/prog_index.m3u8	$DEVICE_SUITE_TARGET_30/res/segments
			chmod -R 777 $DEVICE_SUITE_TARGET_30/res
			chsmack -a "User::App::Shared" $DEVICE_SUITE_TARGET_30/res/*
			chsmack -e "User::App::Shared" $DEVICE_SUITE_TARGET_30/res/*
			chsmack -a "User::App::Shared" $DEVICE_SUITE_TARGET_30/res/segments/*
			chsmack -e "User::App::Shared" $DEVICE_SUITE_TARGET_30/res/segments/*
			chmod -R 777 $DEVICE_SUITE_TARGET_30/res/segment
			;;
	"org.tizen.platform-permission-native-ctc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp native-platform-permission-ctc-0.1-0.armv7l.rpm $APP_DATA_DIR/native-platform-permission-ctc-0.1-0.armv7l.rpm
			cp native-platform-permission-ctc-0.1-0.aarch64.rpm $APP_DATA_DIR/native-platform-permission-ctc-0.1-0.aarch64.rpm
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			cp -R PlatformPermission_test.jpg $DEVICE_SUITE_TARGET_30/Images/PlatformPermission_test.jpg
			chmod -R 777 $DEVICE_SUITE_TARGET_30/Images
			;;
	"org.tizen.video-util-native-ctc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp video_color.mp4 $APP_DATA_DIR/video_color.mp4
			chown -R 5000:5000 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.media-vision-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			mkdir -p $APP_DATA_DIR/tmp
			mkdir -p $APP_DATA_DIR/P1
			cp 09.jpg  $APP_DATA_DIR/P1
			cp test_rec_model $APP_DATA_DIR/test_rec_model
			cp test_trk_model $APP_DATA_DIR/test_trk_model
			cp 00.jpg $APP_DATA_DIR/tmp/00.jpg
			cp 09.jpg $APP_DATA_DIR/tmp/09.jpg
			cp 04.jpg $APP_DATA_DIR/tmp/04.jpg
			cp 01.jpg $APP_DATA_DIR/tmp/01.jpg
			cp 05.jpg $APP_DATA_DIR/tmp/05.jpg
			cp scene.jpg $APP_DATA_DIR/tmp/scene.jpg
			cp target.jpg $APP_DATA_DIR/tmp/target.jpg
			cp neutral.jpg $APP_DATA_DIR/tmp/neutral.jpg

			mkdir -p $DEVICE_PHYSICAL_STORAGE_30
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/P1
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/track/sequence
			cp $APP_DATA_DIR/tmp/09.jpg $DEVICE_PHYSICAL_STORAGE_30/P1
			cp track/sequence/*.* $DEVICE_PHYSICAL_STORAGE_30/res/track/sequence/

			chmod -R 777 $APP_DATA_DIR
			chmod -R 777 $DEVICE_PHYSICAL_STORAGE_30/res
			chown -R 5000:5000 $APP_DATA_DIR
			chown -R 5001:100 $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			chsmack -a "User::App::Shared" $APP_DATA_DIR/tmp/*
			chsmack -a "User::App::Shared" $APP_DATA_DIR/tmp/*
			;;
	"org.tizen.mediastreamrecorder-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/
			chsmack -e "User::App::Shared" $APP_DATA_DIR/
			cp short.mp3 $APP_DATA_DIR/short.mp3
			cp I420_352x288.yuv $APP_DATA_DIR/I420_352x288.yuv
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.streamrecorder-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res
			cp res/* $DEVICE_PHYSICAL_STORAGE_30/res
			chmod -R 777 $DEVICE_PHYSICAL_STORAGE_30/res
			chown -R 5001:100 $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/*
			;;
	"org.tizen.capi-media-vision-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $DEVICE_SUITE_TARGET_30/data
			chsmack -a "User::App::Shared" $DEVICE_SUITE_TARGET_30/data
			chsmack -e "User::App::Shared" $DEVICE_SUITE_TARGET_30/data
			chmod -R 777 $DEVICE_SUITE_TARGET_30/data
			chown -R 5000:5000 $DEVICE_SUITE_TARGET_30/data

			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/model
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/model
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/model
			cp res/rec/test_rec_model $DEVICE_PHYSICAL_STORAGE_30/res/model/test_rec_model
			cp res/track/test_trk_model $DEVICE_PHYSICAL_STORAGE_30/res/model/test_trk_model
			chmod -R 777 $DEVICE_PHYSICAL_STORAGE_30/res/model
			chown -R 5000:5000 $DEVICE_PHYSICAL_STORAGE_30/res/model
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/*
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/model/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/model/*

			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/img
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/img
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/img
			cp res/media-vision-barcodes.json $DEVICE_PHYSICAL_STORAGE_30/res/media-vision-barcodes.json
			cp res/img/*.jpg $DEVICE_PHYSICAL_STORAGE_30/res/img/
			cp res/img/*.raw $DEVICE_PHYSICAL_STORAGE_30/res/img/
			chmod -R 777 $DEVICE_PHYSICAL_STORAGE_30/res
			chown -R 5000:5000 $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/img/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/img/*

			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/rec/P1
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/rec/P2
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/rec
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/rec
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/rec/P1
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/rec/P1
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/rec/P2
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/rec/P2
			cp res/rec/P1/*.jpg $DEVICE_PHYSICAL_STORAGE_30/res/rec/P1/
			cp res/rec/P2/*.jpg $DEVICE_PHYSICAL_STORAGE_30/res/rec/P2/
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/rec/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/rec/*
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/rec/P1/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/rec/P1/*
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/rec/P2/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/rec/P2/*

			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/eye
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/eye
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/eye
			cp res/eye/*.jpg $DEVICE_PHYSICAL_STORAGE_30/res/eye/
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/eye/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/eye/*

			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/expr
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/expr
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/expr
			cp res/expr/*.jpg  $DEVICE_PHYSICAL_STORAGE_30/res/expr/
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/expr/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/expr/*

			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/track/sequence
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/track/sequence
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/track/sequence
			cp res/track/sequence/*.jpg $DEVICE_PHYSICAL_STORAGE_30/res/track/sequence/
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/track/sequence/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/track/sequence/*

			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/facedetect
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/facedetect
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/facedetect
			cp res/facedetect/*.jpg $DEVICE_PHYSICAL_STORAGE_30/res/facedetect/
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/facedetect/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/facedetect/*

			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/image
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/image
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/image
			cp res/image/*.jpg $DEVICE_PHYSICAL_STORAGE_30/res/image/
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/image/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/image/*

			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/image/tracking
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/image/tracking
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/image/tracking
			cp res/image/tracking/*.jpg $DEVICE_PHYSICAL_STORAGE_30/res/image/tracking/
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/image/tracking/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/image/tracking/*

			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/surv
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/surv
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/surv
			cp res/surv/* $DEVICE_PHYSICAL_STORAGE_30/res/surv/
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/surv/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/surv/*



			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/inference/models
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/inference/images
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/inference
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/inference
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/inference/models
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/inference/models
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/inference/images
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/inference/images
			cp res/inference/models/* $DEVICE_PHYSICAL_STORAGE_30/res/inference/models/
			cp res/inference/images/* $DEVICE_PHYSICAL_STORAGE_30/res/inference/images/
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/inference/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/inference/*
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/inference/models/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/inference/models/*
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/inference/images/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/inference/images/*
			;;
	"org.tizen.capi-message-port-native-utc")
			echo "Installing pre-requisites for the package $1"
			install -m 755 core-capi-message-port-tests.sh $APPS_ROOT/org.tizen.capi-message-port-native-utc/bin
			;;
	"org.tizen.metadata-editor-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp -rf * $APP_DATA_DIR/
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.stt-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp res/ringtone.wav $APP_DATA_DIR/ringtone.wav
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.dali-core-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp res/* $APP_DATA_DIR
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.dali-toolkit-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			cp res/* $APP_DATA_DIR
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/*
			;;
	"org.tizen.mediamuxer-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $DEVICE_SUITE_TARGET_30/res
			chsmack -a "User::App::Shared" $DEVICE_SUITE_TARGET_30/res
			chsmack -e "User::App::Shared" $DEVICE_SUITE_TARGET_30/res
			chmod -R 777 $DEVICE_SUITE_TARGET_30/res
			chmod -R 777 $DEVICE_SUITE_TARGET_30/res/*
			chsmack -a "User::App::Shared" $DEVICE_SUITE_TARGET_30/res/*
			chsmack -e "User::App::Shared" $DEVICE_SUITE_TARGET_30/res/*
			;;
	"org.tizen.capi-mediamuxer-native-itc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $DEVICE_SUITE_TARGET_30/res
			chsmack -a "User::App::Shared" $DEVICE_SUITE_TARGET_30/res
			chsmack -e "User::App::Shared" $DEVICE_SUITE_TARGET_30/res
			chmod -R 777 $DEVICE_SUITE_TARGET_30/res
			chmod -R 777 $DEVICE_SUITE_TARGET_30/res/*
			chsmack -a "User::App::Shared" $DEVICE_SUITE_TARGET_30/res/*
			chsmack -e "User::App::Shared" $DEVICE_SUITE_TARGET_30/res/*
			;;
	"org.tizen.webkit2-native-utc")
			echo "Installing pre-requisites for the package $1"
			mkdir -p $APP_DATA_DIR
			mkdir -p $APP_DATA_DIR/res
			mkdir -p $APP_DATA_DIR/res/common
			mkdir -p $APP_DATA_DIR/res/ewk_context_menu
			mkdir -p $APP_DATA_DIR/res/ewk_context
			mkdir -p $APP_DATA_DIR/res/ewk_view
			chsmack -a "User::App::Shared" $APP_DATA_DIR
			chsmack -e "User::App::Shared" $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/res
			chsmack -e "User::App::Shared" $APP_DATA_DIR/res
			chsmack -a "User::App::Shared" $APP_DATA_DIR/res/common
			chsmack -e "User::App::Shared" $APP_DATA_DIR/res/common
			chsmack -a "User::App::Shared" $APP_DATA_DIR/res/ewk_context
			chsmack -e "User::App::Shared" $APP_DATA_DIR/res/ewk_context
			chsmack -a "User::App::Shared" $APP_DATA_DIR/res/ewk_context_menu
			chsmack -e "User::App::Shared" $APP_DATA_DIR/res/ewk_context_menu
			chsmack -a "User::App::Shared" $APP_DATA_DIR/res/ewk_view
			chsmack -e "User::App::Shared" $APP_DATA_DIR/res/ewk_view
			cp res/common/*.html $APP_DATA_DIR/res/common/
			cp res/ewk_view/*.html $APP_DATA_DIR/res/ewk_view/
			cp res/ewk_context_menu/*.png $APP_DATA_DIR/res/ewk_context_menu/
			cp res/ewk_context_menu/*.html $APP_DATA_DIR/res/ewk_context_menu/
			cp res/ewk_context/*.bmp $APP_DATA_DIR/res/ewk_context/
			cp res/ewk_context/*.html $APP_DATA_DIR/res/ewk_context/
			chown -R 5000:5000 $APP_DATA_DIR
			chmod -R 777 $APP_DATA_DIR
			chsmack -a "User::App::Shared" $APP_DATA_DIR/res/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/res/*
			chsmack -a "User::App::Shared" $APP_DATA_DIR/res/common/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/res/common/*
			chsmack -a "User::App::Shared" $APP_DATA_DIR/res/ewk_context/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/res/ewk_context/*
			chsmack -a "User::App::Shared" $APP_DATA_DIR/res/ewk_context_menu/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/res/ewk_context_menu/*
			chsmack -a "User::App::Shared" $APP_DATA_DIR/res/ewk_view/*
			chsmack -e "User::App::Shared" $APP_DATA_DIR/res/ewk_view/*
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/common
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context_menu
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context
			mkdir -p $DEVICE_PHYSICAL_STORAGE_30/res/ewk_view
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/common
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/common
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context_menu
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context_menu
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/ewk_view
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/ewk_view
			cp res/common/*.html $DEVICE_PHYSICAL_STORAGE_30/res/common/
			cp res/ewk_view/*.html $DEVICE_PHYSICAL_STORAGE_30/res/ewk_view/
			cp res/ewk_context_menu/*.png $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context_menu/
			cp res/ewk_context_menu/*.html $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context_menu/
			cp res/ewk_context/*.bmp $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context/
			cp res/ewk_context/*.html $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context/
			chown -R 5000:5000 $DEVICE_PHYSICAL_STORAGE_30/res
			chmod -R 777 $DEVICE_PHYSICAL_STORAGE_30/res
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/*
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/common/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/common/*
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context/*
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context_menu/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/ewk_context_menu/*
			chsmack -a "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/ewk_view/*
			chsmack -e "User::App::Shared" $DEVICE_PHYSICAL_STORAGE_30/res/ewk_view/*
			;;
	"org.tizen.privilege-info-native-utc")
			echo "Installing pre-requisites for the package $1"
			cyad -s -k MANIFESTS_GLOBAL -c User::Pkg::org.tizen.privilege-info-native-utc -u '*' -p http://tizen.org/privilege/contact.read -t DENY
			;;
	"org.tizen.trace-native-utc")
			echo "Installing pre-requisites for the package $1"
			chsmack -e "User" /usr/bin/atrace-1.1
			;;
	"org.tizen.ttrace-native-itc")
			echo "Installing pre-requisites for the package $1"
			chsmack -e "User" /usr/bin/atrace-1.1
			;;
esac

##UEP630x36d2205b5a37f64ccfd9d5852a47c792cf7b1be9dc10a72c0a339b740a6c19d34dca8fdbff1c45e56fb78c5460dc55fa7ced98b3e2c76ddff29f75f6cbff037844b84e75aff67faf7063ffb12ba75b175dd96ecdd626c1d6dead49c926fa94e0e45c175e2460663a7ed78e45e5b20c0658965a5d3bd0783594376d0b37e5ddd210a7b9b4b286fc1f5cc0203f93a68b650c9ca2bf959cd9c512e4f47e48c96f5b32e704fccb042ccfa0281dc9202a3c9bffb2d045bd11e4a120c8349f81172975e96b09a14304523716e8a870533acadd262030d0a0e4346fe5d1b44c576f39e046d74f8d6506151db9aac97561208a4798954246ef51e8b234ceba009f63e4eaAAACAg==:UEP