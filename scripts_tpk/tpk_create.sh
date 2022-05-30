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

# Initializing log text properties
red=`tput setaf 1`
green=`tput setaf 2`
yellow=`tput setaf 3`
reset=`tput sgr0`
bold=`tput bold`

checkModuleName()
{
	if [ "$MODULE_NAME" == "media-vision" ]; then
		TIZENIOTMODULENAME="capi-media-vision"
	elif [ "$MODULE_NAME" == "capi-mediamuxer" ]; then
		TIZENIOTMODULENAME="mediamuxer"
	elif [ "$MODULE_NAME" == "capi-mediademuxer" ]; then
		TIZENIOTMODULENAME="mediademuxer"
	elif [ "$MODULE_NAME" == "capi-media-tool" ]; then
		TIZENIOTMODULENAME="mediatool"
	elif [ "$MODULE_NAME" == "mediastreamrecorder" ]; then
		TIZENIOTMODULENAME="streamrecorder"
	elif [ "$MODULE_NAME" == "ttrace" ]; then
		TIZENIOTMODULENAME="trace"
	elif [ "$MODULE_NAME" == "vpn-service" ]; then
		TIZENIOTMODULENAME="vpn"
	fi
}

SRCFILES=""
SRCFILES="${SRCFILES} src"
SRCFILES="${SRCFILES} inc"

changeUItoServiceApp()
{
	# updating ui-app >>serviceapp in case of tizeniot and for 'S' type modules
	grep $TIZENIOTMODULENAME $SCRIPT_DIR/tizeniot_service_modules.txt > /dev/null
	if [ $? == "0" ]; then
		for files in ${SRCFILES};
		do
			for srcFile in `ls $WORKSPACE_PATH/$PROJECT_NAME/$files/`
			do
				file_path=$WORKSPACE_PATH/$PROJECT_NAME/$files/$srcFile
				header_flag=0

				while read line
				do
					if [[ $line == "#include <service_app.h>" ]]; then
						header_flag=1
					fi

					if [[ ($line =~ "#include <app.h>")  && ($header_flag == 0) ]]; then
						header_flag=1
						sed -i 's/#include <app.h>/#include <service_app.h>/g' $file_path
					fi
				done < $file_path

				while read line
				do
					if [[ $line =~ "ui_app" ]]; then
						sed -i 's/ui_app/service_app/g' $file_path
					fi
				done < $file_path
			done
		done
	fi
}

RunCommand () {
        echo $green''$2' Started'$reset
        if eval $1; then
                echo $green''$2' SUCCESSFUL'$reset
        else
                echo $red'[ERROR]'$2' FAILED'
                echo ""
                echo " ============================================"
                echo "||                "$bold"BUILD FAILED$reset$red              ||"
                echo " ============================================"
                echo ""$reset
                exit 1
fi
}

copy_native_core()
{
	if [ "$3" == "utc" ]; then
		if [[ ( $2 =~ "dali-" ) || ( $2 =~ "_dali" ) ]];	then
			cp $2/*core.cpp $1/src/.
		else
			cp $2/*core.c $1/src/.
		fi
	else
		if [[ ( $2 =~ "dali-" ) || ( $2 =~ "_dali" ) ]];	then
			cp $2/*native.cpp $1/src/.
		else
			cp $2/*native.c $1/src/.
		fi

	fi
}

deploySourceFile() {
	rm -rf $1/src/*.c
	rm -rf $1/inc/*.h

	echo $green"Copying Source files "

	#copying common source and header files
	cp $2/../../common/*.c $1/src/.
	cp $2/../../common/*.h $1/inc/.
	if [[ ( $2 =~ "dali-" ) || ( $2 =~ "_dali" ) ]];	then
		cp $2/../../common/*.cpp $1/src/.
	fi

	#copying module specific header files
	find $2 -name "*.h" | xargs cp -t $1/inc/

	#copying module source files having device specific macros in CMakeLists.txt

	if [ "$3" == "mobile" ]; then
		macro="MOBILE"
	elif [ "$3" == "wearable" ]; then
		macro="WEARABLE"
	elif [ "$3" == "tizeniot" ]; then
		macro="TIZENIOT"
	elif [ "$3" == "tv" ]; then
		macro="TV"
	fi


	#Copy c/cpp files as per entry in CMakeFile for common files

	while read line
	do
		if ! [[ $lastline =~ "MOBILE" ]] && ! [[ $lastline =~ "WEARABLE" ]]  && ! [[ $lastline =~ "TV" ]] && ! [[ $lastline =~ "TIZENIOT" ]]; then
			if [[ $line =~ "SET(TC_SOURCES" || $line =~ "GLOB TC_SOURCES" ]]; then
				while true
				do
					read srcFile
					substring=$(echo $srcFile | tail -c 3)
					 if [ "$substring" == ".c" ]; then
						 cp $2/$srcFile $1/src/.
					 fi
					 substring=$(echo $srcFile | tail -c 5)
					 if [ "$substring" == ".cpp" ]; then
						 cp $2/$srcFile $1/src/.
					 fi

					 substring=$(echo $srcFile | tail -c 2)
					 if [ "$substring" == ")" ]; then
						 chCount=${#srcFile}
						 chCount=$((chCount-1))
						 substring=$(echo $srcFile | head -c $chCount)
						 cp $2/$substring $1/src/.
						 copy_native_core $1 $2 $5
						 break
					 elif [[ $srcFile == ")" ]]; then
						 copy_native_core $1 $2 $5
						 break
					 fi
				done

			fi
		fi
		lastline=$line
	done < $2/CMakeLists.txt

	#Copy profile specific (mobile/wearable/tizeniot/tv) c/cpp files as per entry in CMakeFile
	while read line
	do
		if [[ $line =~ $macro ]]
		then

			while true
			do
				read srcFile
				substring=$(echo $srcFile | tail -c 3)
				if [ "$substring" == ".c" ]; then
					cp $2/$srcFile $1/src/.
				fi

				substring=$(echo $srcFile | tail -c 5)
				if [ "$substring" == ".cpp" ]; then
					cp $2/$srcFile $1/src/.
				fi

				if [[ $srcFile == *"ENDIF"* ]]; then
					if [ "$5" == "utc" ]; then
						cp $2/*core.c $1/src/.
					else
						cp $2/*native.c $1/src/.
					fi
				break
				fi
			done
		fi
	done < $2/CMakeLists.txt

	# copying data and shared data
	WORKDIR=`pwd`
	cd $2
	if [ "$3" == "tv" ]; then
		fileCount="$(git status -s | grep -c  "post-install/post-inst.sh" )"
		if [ $fileCount -gt 0 ] ; then
			#post-inst.sh file signed by kuep certificate if there is any new change in file for tv profile
			echo -e $green"Signing of post-inst.sh started"$reset
			sed -i '/##UEP*/d' post-install/post-inst.sh
			./../../../scripts_tpk/kuep_net_signer.sh -s -tizen_major_ver 6 post-install/post-inst.sh
			echo -e $green"Signing of post-inst.sh done"$reset
		fi
	fi
	find . -type f ! -iname "*.c" ! -iname "*.cpp" ! -iname "*.h" ! -iname "CMakeLists.txt" -exec cp -p --parents {} $1/shared/res/. ";"
	cd $WORKDIR

	if [ -d $2/res ];then
		cp -rf $2/res/* $1/res/.
	fi

	if [ -d $2/res/$3 ];then
		cp -rf $2/res/$3/. $1/shared/res/.
		# As Profile specific resources has been copied from shared/res/res/<profile> to shared/res location
		# So removing all profile specific folders from shared/res/res/
		WORKDIR=`pwd`
		cd $1/shared/res/res
		dirs=(*/)
		for dir in "${dirs[@]}"
		do
			if [[ $dir =~ "mobile" ]] || [[ $dir =~ "wearable" ]] || [[ $dir =~ "tizeniot" ]] || [[ $dir =~ "tv" ]]; then
				# So removing all profile specific folders from shared/res/res/
				rm -rf $dir
			fi
		done

		#if 'res' (/shared/res/res) folder is empty, then remove 'res' folder too.
		cd ..
		VALUE=`ls -l res | wc -l`
		if [ $VALUE == 1 ]; then
			rm -rf res
		fi
		cd $WORKDIR
	fi
	if [ "$3" == "tv" ]; then
		fileCount="$(git status -s | grep -c  "scripts_tpk/spec.sh" )"
		if [ $fileCount -gt 0 ] ; then
			#spec.sh file signed by kuep certificate if there is any new change in file for tv profile
			echo -e "${reset}Signing of spec.sh started"
			sed -i '/##UEP*/d' scripts_tpk/spec.sh
			./scripts_tpk/kuep_net_signer.sh -s -tizen_major_ver 6 scripts_tpk/spec.sh
			echo -e "${reset}Signing of spec.sh done"
		fi
	fi

	cp scripts_tpk/spec.sh $1/shared/res/.

	sed -i -f scripts_tpk/$3.sed $1/inc/tct_common.h

	# include tct_common.h in utc source files
	if [[ ( $2 =~ "dali-" ) || ( $2 =~ "_dali" ) ]];	then
		for srcFile in `ls $1/src/`
		do
			sed -i '1i\#include <tct_common.h>' $1/src/$srcFile
		done
	elif [ "$5" == "utc" ]; then
		for srcFile in `ls $1/src/ | grep -v core | grep -v common`
		do
			sed -i '1i\#include <tct_common.h>' $1/src/$srcFile
		done
	fi


	cd $1

	if [[ ( $2 =~ "dali-" ) || ( $2 =~ "_dali" ) ]];	then
		find ./src -iname *.cpp -print0 | tr '\0' ' ' > test.files
		find ./src -iname *.c -print0 | tr '\0' ' ' >> test.files
	else
		find ./src -iname *.c -print0 | tr '\0' ' ' > test.files
	fi

	sed -i 's/\.\///g' test.files

	#replace="src/$4.c"
	output=`cat test.files`
	sed -i "/USER_SRCS/d" project_def.prop
	echo "USER_SRCS =$output" >> project_def.prop

	if [[ $2 =~ "vulkan" ]]; then
		echo "USER_LIBS = vulkan SDL2 SDL2main" >> project_def.prop
	fi

	if [[ $2 =~ "sdl2" ]]; then
		echo "USER_LIBS = SDL2 SDL2main" >> project_def.prop
	fi

	rm -rf test.files

	# updating privileges in xml file
	if [ "$5" == "utc" ]; then
		xmlfilepath=$2/../../../packaging/$5/core-$6-tests.xml
	else
		xmlfilepath=$2/../../../packaging/$5/native-$6-$5.xml
	fi
	flag=0

	while read line
	do
		# When profile type is <tizeniot>, set flag for service-app specific changes to be done
		if [ $PROFILE_TYPE == "tizeniot" ]; then
			grep $TIZENIOTMODULENAME $SCRIPT_DIR/tizeniot_service_modules.txt > /dev/null
			if [ $? == "0" ]; then
				flag=1
			fi
		fi

		if [[ $line =~ "<service-application" ]]; then
			sed -i 's/ui-application/service-application/g' tizen-manifest.xml
			flag=1
		fi

		if [[ $line =~ "<widget-application" ]]; then
			sed -i 's/ui-application/widget-application/g' tizen-manifest.xml
			flag=2
		fi

		# add datacontrol attribute for data-control module
		if echo "$line" | grep -q "<datacontrol"; then
			if [ $PROFILE_TYPE == "tizeniot" ]; then
				sed -i '/<\/manifest>/d' tizen-manifest.xml
				sed -i '/<\/service-application>/d' tizen-manifest.xml
				echo $line >> tizen-manifest.xml
				echo '</service-application>' >> tizen-manifest.xml
				echo '</manifest>' >> tizen-manifest.xml
			else
				sed -i '/<\/manifest>/d' tizen-manifest.xml
				sed -i '/<\/ui-application>/d' tizen-manifest.xml
				echo $line >> tizen-manifest.xml
				echo '</ui-application>' >> tizen-manifest.xml
				echo '</manifest>' >> tizen-manifest.xml
			fi
		fi

		# add app-control attribute for application-utc
		if echo "$line" | grep -q "<app-control"; then
			echo $line >> tizen-manifest.xml
			sed -i '/<\/ui-application>/d' tizen-manifest.xml
			while true
			do
				read nextLine
				if echo $nextLine | grep -q "</app-control"; then
					echo $nextLine >> tizen-manifest.xml
					break
				fi
				echo $nextLine >> tizen-manifest.xml
			done
			echo '</ui-application>' >> tizen-manifest.xml
		fi

		# keep complication information
		if echo "$line" | grep -q "<complication"; then
			echo $line >> tizen-manifest.xml
			sed -i '/<\/manifest>/d' tizen-manifest.xml
			sed -i '/<\/service-application>/d' tizen-manifest.xml
			while true
			do
				read nextLine
				if echo $nextLine | grep -q "</complication"; then
					echo $nextLine >> tizen-manifest.xml
					break
				fi
				echo $nextLine >> tizen-manifest.xml
			done
			echo '</service-application>' >> tizen-manifest.xml
			echo '</manifest>' >> tizen-manifest.xml
		fi

		# keep metadata information
		if echo "$line" | grep -q "<metadata"; then
			echo $line >> tizen-manifest.xml
			sed -i '/<\/manifest>/d' tizen-manifest.xml

			if [ $flag == 1 ]; then
				sed -i '/<\/service-application>/d' tizen-manifest.xml
				echo '</service-application>' >> tizen-manifest.xml
			elif [ $flag == 2 ]; then
				sed -i '/<\/widget-application>/d' tizen-manifest.xml
				echo '</widget-application>' >> tizen-manifest.xml
			else
				sed -i '/<\/ui-application>/d' tizen-manifest.xml
				echo '</ui-application>' >> tizen-manifest.xml
			fi
			echo '</manifest>' >> tizen-manifest.xml
		fi

		if [[ $line =~ "</ui-application>" ]] || [[ $line =~ "</service-application>" ]] || [[ $line =~ "</widget-application>" ]]
		then
			sed -i '/<\/manifest>/d' tizen-manifest.xml
			while true
			do
				read nextLine
				if [[ $nextLine =~ "</manifest>" ]]
				then
					echo $nextLine >> tizen-manifest.xml
					break
				fi
				echo $nextLine >> tizen-manifest.xml
			done
		fi
	done < $xmlfilepath
	sed -i 's/example/tizen/g' tizen-manifest.xml

	BACKGROUND_DATA="<background-category value=\"background-network\"\/>\n \
	<background-category value=\"download\"\/>\n \
	<background-category value=\"iot-communication\"\/>\n \
	<background-category value=\"location\"\/>\n \
	<background-category value=\"media\"\/>\n \
	<background-category value=\"sensor\"\/>\n"

	if [ $flag == 1 ]; then
		BACKGROUND_DATA+="<\/service-application>"
		sed -i "s/<\/service-application>/${BACKGROUND_DATA}/" tizen-manifest.xml
	elif [ $flag == 2 ]; then
		BACKGROUND_DATA+="<\/widget-application>"
		sed -i "s/<\/widget-application>/${BACKGROUND_DATA}/" tizen-manifest.xml
	else
		BACKGROUND_DATA+="<\/ui-application>"
		sed -i "s/<\/ui-application>/${BACKGROUND_DATA}/" tizen-manifest.xml
	fi

	###set multipule true/false
	while read line
	do
		if [[ $line =~ "multiple=\"true\"" ]]; then
			sed -i 's/multiple=\"false\"/multiple=\"true\"/g' tizen-manifest.xml
			break
		fi
	done < $xmlfilepath

	# updating the xml files for 'S' type modules
	if [ $PROFILE_TYPE == "tizeniot" ]; then
		changeUItoServiceApp
	fi

	echo $green"Source files copied and xml modified successfully"

	## Module specific changes start
	#  Change of appid as per TPK approach.
	#  If there are other modules than 'badge' also then code to change their appid must be written here for specific modules.
	if [ $MODULE_NAME == "application" ]; then
		if [ "$5" == "utc" ]; then
			sed -i -e 's/core.application-tests/org.tizen.application-native-utc/g' $1/src/utc_app_event.c
			sed -i -e 's/core.application-tests/org.tizen.application-native-utc/g' $1/src/utc_alarm.c
			sed -i -e 's/core.application-tests/org.tizen.application-native-utc/g' $1/inc/assert_common.h
		elif [ "$5" == "itc" ]; then
			sed -i -e 's/native.application-itc/org.tizen.application-native-itc/g' $1/src/ITs-application-event.c
			sed -i -e 's/native.application-itc/org.tizen.application-native-itc/g' $1/src/ITs-application-alarm.c
		fi
	fi
	if [ $MODULE_NAME == "badge" ]; then
		if [ "$5" == "utc" ]; then
			sed -i -e 's/core.badge-tests/org.tizen.badge-native-utc/g' $1/src/utc-badge.c
		elif [ "$5" == "itc" ]; then
			sed -i -e 's/native.badge-itc/org.tizen.badge-native-itc/g' $1/inc/ITs-badge-common.h
		fi
	fi

	if [ $MODULE_NAME == "context" ]; then
		if [ "$5" == "utc" ]; then
			sed -i -e 's/core-context-tests/org.tizen.context-native-utc/g' $1/inc/utc-context-trigger-custom.h
		elif [ "$5" == "itc" ]; then
			sed -i -e 's/native-context-itc/org.tizen.context-native-itc/g' $1/inc/ITs-context-common.h
		fi
	fi

	if [ $MODULE_NAME == "accounts-svc" ]; then
		if [ "$5" == "utc" ]; then
			sed -i -e 's/core.accounts-svc-tests/org.tizen.accounts-svc-native-utc/g' $1/src/utc-accounts-svc.c
		elif [ "$5" == "itc" ]; then
			sed -i -e 's/native.accounts-svc-itc/org.tizen.accounts-svc-native-itc/g' $1/inc/ITs-accounts-svc-common.h
		fi
	fi

	if [ $MODULE_NAME == "iotcon" ]; then
		if [ "$5" == "utc" ]; then
			sed -i -e 's/core-iotcon-tests/org.tizen.iotcon-native-utc/g' $1/src/utc-iotcon-common.c
		elif [ "$5" == "itc" ]; then
			sed -i -e 's/native-iotcon-itc/org.tizen.iotcon-native-itc/g' $1/src/ITs-iotcon-common.c
		fi
	fi

	if [ $MODULE_NAME == "metadata-editor" ]; then
		if [ "$5" == "utc" ]; then
			sed -i -e 's/core-metadata-editor-tests/org.tizen.metadata-editor-native-utc/g' $1/src/utc-metadata-editor.c
		fi
	fi

	if [ $MODULE_NAME == "sync-manager" ]; then
		if [ "$5" == "utc" ]; then
			sed -i -e 's/core.sync-manager-tests/org.tizen.sync-manager-native-utc/g' $1/src/utc-sync-manager.c
		elif [ "$5" == "itc" ]; then
			sed -i -e 's/native-sync-manager-itc/org.tizen.sync-manager-native-itc/g' $1/inc/ITs-sync-manager-common.h
		fi
	fi


	#Change in xml file for specific modules
	if [ $MODULE_NAME == "accounts-svc" ]; then
		if [ "$5" == "utc" ]; then
			sed -i -e 's/core.accounts-svc-tests/org.tizen.accounts-svc-native-utc/g' tizen-manifest.xml
		elif [ "$5" == "itc" ]; then
			sed -i -e 's/native.accounts-svc-itc/org.tizen.accounts-svc-native-itc/g' tizen-manifest.xml
		fi
	fi
	if [ $MODULE_NAME == "contacts-service2" ]; then
		if [ "$5" == "utc" ]; then
			sed -i -e 's/core.contacts-service2-tests/org.tizen.contacts-service2-native-utc/g' tizen-manifest.xml
		elif [ "$5" == "itc" ]; then
			sed -i -e 's/native.contacts-service2-itc/org.tizen.contacts-service2-native-itc/g' tizen-manifest.xml
		fi
	fi
	if [ $MODULE_NAME == "sync-manager" ]; then
		if [ "$5" == "utc" ]; then
			sed -i -e 's/core.sync-manager-tests/org.tizen.sync-manager-native-utc/g' tizen-manifest.xml
			if [[ $macro =~ "WEARABLE" ]]; then
				sed -i '/calendar.read/d' tizen-manifest.xml
			fi
		elif [ "$5" == "itc" ]; then
			sed -i -e 's/native.sync-manager-itc/org.tizen.sync-manager-native-itc/g' tizen-manifest.xml
			if [[ $macro =~ "WEARABLE" ]]; then
				sed -i '/calendar.read/d' tizen-manifest.xml
			fi
		fi
	fi
	## Module specific changes end

	cd $2/../../../scripts_tpk
}

checkRootstrap() {
	ROOTSTRAP_TYPE=$1
	PROFILE_TYPE=$2
	DEVICE_TYPE=$3
	CURRENT_VERSION=$4
	if [ -z "$ROOTSTRAP_TYPE" ]; then
		echo $yellow"rootstrap.txt file is empty."$reset
		EXISTING_ROOTSTRAP=`tizen list rootstrap | grep "${PROFILE_TYPE}" | grep "${DEVICE_TYPE}" | grep "${CURRENT_VERSION}" | cut -f1 -d' ' |grep -v "public"`
		if [ -z "$EXISTING_ROOTSTRAP" ]; then
			echo $red"Default rootstrap is not installed for ${CURRENT_VERSION} version"$reset
			OPTIONAL_ROOTSTRAP=`tizen list rootstrap | grep "${PROFILE_TYPE}" | grep "${DEVICE_TYPE}" | grep "${CURRENT_VERSION}" | cut -f1 -d' ' |grep -i "public"`
			if [ -z "$OPTIONAL_ROOTSTRAP" ]; then
				echo $red"Please install the rootstrap."$reset
				exit
			else
				echo $red"****Please run tizen list rootstrap command to check available rootstrap and update rootstrap.txt file ${BUILD_PROFILE}_$ARCH tag"$reset
				exit
			fi
		else
			echo $green$EXISTING_ROOTSTRAP" rootstrap is present and used."$reset
		fi
	else
		EXISTING_ROOTSTRAP=`tizen list rootstrap | grep "${ROOTSTRAP_TYPE}" | grep "${DEVICE_TYPE}" | grep "${CURRENT_VERSION}" |cut -f1 -d' '`
		if echo "$ROOTSTRAP_TYPE" | grep -q "$CURRENT_VERSION";then
			echo $green"Version of branch and rootstrap is same."$reset
		else
			ROOTSTRAP_VERSION=$(echo "$ROOTSTRAP_TYPE" | cut -f2 -d'-')
			echo $red"Version mismatch. Code branch version: "${CURRENT_VERSION}" and rootstrap.txt file contain rootstrap version: ${ROOTSTRAP_VERSION}"$reset
			exit
		fi
		if [ -z "$EXISTING_ROOTSTRAP" ]; then
			echo $red$ROOTSTRAP_TYPE" rootstrap mentioned in rootstrap.txt is not installed.Please install the rootstrap."$reset
			exit
		else
			echo $green$EXISTING_ROOTSTRAP" rootstrap is present and used."$reset
		fi
	fi
}

TESTCASE_TYPE="$1"
MODULE_NAME="$2"
TIZENIOTMODULENAME="$2"
ARCH_TYPE="$3"
APPLLICATION_PROFILE="basic-ui"
PROFILE_TYPE="$4"
WORKSPACE_PATH="$HOME/workspace_$PROFILE_TYPE"
CURRENT_VERSION="7.0"

#####Check for architecture in case of TV  profile##########
if [ "$ARCH_TYPE" != "arm" ];  then
	if [ "$PROFILE_TYPE" == "tv" ] ; then
		echo $yellow"$PROFILE_TYPE profile build is supported only for arm architecture"$reset
		exit
	fi
fi

#####Check for already existing profile directory##########
if [ ! -d $WORKSPACE_PATH ];then
	mkdir $WORKSPACE_PATH
fi

# build command properties
#COMPILER_TYPE="llvm"
COMPILER_TYPE="gcc-9.2"
BUILD_TYPE="Debug"
UNSUPPORTED_FILE="tct_unsupported.txt"

#######skipping build for unsupported modules#######
if [ "$ARCH_TYPE" == "arm" ]; then
	ARCH="armv7l"
elif [ "$ARCH_TYPE" == "x86" ]; then
	ARCH="x86"
elif [ "$ARCH_TYPE" == "aarch64" ]; then
	ARCH="aarch64"
elif [ "$ARCH_TYPE" == "x86_64" ]; then
	ARCH="x86_64"
fi

SUPPORTED=`cat ./$UNSUPPORTED_FILE | grep "$PROFILE_TYPE:$ARCH:$TESTCASE_TYPE:$MODULE_NAME;"`
if [[ $SUPPORTED != "" ]]
then
	echo ""
	echo "****************SKIPPED BUILDING $TESTCASE_TYPE:native-$MODULE_NAME***************************"
	echo "'$TESTCASE_TYPE:$MODULE_NAME' is Unsupported for (profile type='$PROFILE_TYPE',architecture='$ARCH_TYPE')"
	echo "'SKIPPING' THIS MODULE FROM BUILD PROCESS"
	echo "***********************************************************************************"
	echo ""
	sleep 1
	exit
fi

if [ "$1" == "itc" ]; then
	PROJECT_NAME="$MODULE_NAME-native-itc"
elif [ "$1" == "ctc" ]; then
	PROJECT_NAME="$MODULE_NAME-native-ctc"
elif [ "$1" == "utc" ]; then
	PROJECT_NAME="$MODULE_NAME-native-utc"
fi

PWD=$(pwd)
SRC_DIRCTORY=$PWD/src
# packaging properties details

echo "TESTCASE TYPE : $TESTCASE_TYPE"
echo "PROFILE TYPE : $PROFILE_TYPE"
echo "MODULE NAME : $MODULE_NAME"
echo "WORKSPACE PATH : $WORKSPACE_PATH"

if [ -d $WORKSPACE_PATH/$PROJECT_NAME ];then
	rm -rf $WORKSPACE_PATH/$PROJECT_NAME
fi

if [ ! -d $SRC_DIRCTORY/$TESTCASE_TYPE/$MODULE_NAME ];then
	echo $red"[ERROR] BUILD FAILED : Module doesn't exist "
	echo ""$reset
	exit
fi


BUILD_PROFILE="wearable"
if [[ $PROFILE_TYPE == "mobile" ]]; then
	BUILD_PROFILE="mobile"
elif [ $PROFILE_TYPE == "tizeniot" ]; then
	BUILD_PROFILE="tizeniot"
elif [ $PROFILE_TYPE == "tv" ]; then
	BUILD_PROFILE="tv"
fi

ROOTSTRAP_FILE=$(readlink -f rootstrap.txt)
if [ $ARCH_TYPE == "arm" ]; then
	ROOTSTRAP_MOBILE=`cat $ROOTSTRAP_FILE | grep "${BUILD_PROFILE}_$ARCH:" | cut -f 2- -d ':'`
	ROOTSTRAP_TV=`cat $ROOTSTRAP_FILE | grep "${BUILD_PROFILE}_$ARCH:" | cut -f 2- -d ':'`
	ROOTSTRAP_WEARABLE=`cat $ROOTSTRAP_FILE | grep "${BUILD_PROFILE}_$ARCH:" | cut -f 2- -d ':'`
	ROOTSTRAP_TIZENIOT=`cat $ROOTSTRAP_FILE | grep "${BUILD_PROFILE}_$ARCH:" | cut -f 2- -d ':'`
else
	ROOTSTRAP_MOBILE=`cat $ROOTSTRAP_FILE | grep "${BUILD_PROFILE}_$ARCH_TYPE:" | cut -f 2- -d ':'`
	ROOTSTRAP_WEARABLE=`cat $ROOTSTRAP_FILE | grep "${BUILD_PROFILE}_$ARCH_TYPE:" | cut -f 2- -d ':'`
	ROOTSTRAP_TIZENIOT=`cat $ROOTSTRAP_FILE | grep "${BUILD_PROFILE}_$ARCH_TYPE:" | cut -f 2- -d ':'`
fi

DEVICE_TYPE="device"
if [ $ARCH_TYPE == "arm" ]; then
	DEVICE_TYPE="device"
elif [ $ARCH_TYPE == "x86" ]; then
	DEVICE_TYPE="emulator"
elif [ $ARCH_TYPE == "aarch64" ]; then
	DEVICE_TYPE="device64"
elif [ $ARCH_TYPE == "x86_64" ]; then
	DEVICE_TYPE="emulator64"
fi

if [ $PROFILE_TYPE == "tizeniot" ]; then
	SCRIPT_DIR=$PWD/scripts_tpk

	# Below function is called to match the module name with tizeniot_service_modules.txt file.
	if [ "$TESTCASE_TYPE" == "itc" ]; then
		checkModuleName
	fi

	grep $TIZENIOTMODULENAME $SCRIPT_DIR/tizeniot_service_modules.txt > /dev/null
	if [ $? == "0" ]; then
		APPLLICATION_PROFILE="ServiceApp"
	fi

fi

echo "[APPLLICATION_PROFILE] : $APPLLICATION_PROFILE"
RunCommand "tizen create native-project -p $BUILD_PROFILE-6.0 -t $APPLLICATION_PROFILE -n $PROJECT_NAME -- $WORKSPACE_PATH" "Project creation $PROJECT_NAME"
deploySourceFile "$WORKSPACE_PATH/$PROJECT_NAME" "$SRC_DIRCTORY/$TESTCASE_TYPE/$MODULE_NAME" "$PROFILE_TYPE" "$PROJECT_NAME" "$TESTCASE_TYPE" "$MODULE_NAME"

#Checking rootstrap
if [ $PROFILE_TYPE == "mobile" ]; then
	checkRootstrap "$ROOTSTRAP_MOBILE" $PROFILE_TYPE $DEVICE_TYPE $CURRENT_VERSION
elif [ $PROFILE_TYPE == "wearable" ]; then
	checkRootstrap "$ROOTSTRAP_WEARABLE" $PROFILE_TYPE $DEVICE_TYPE $CURRENT_VERSION
elif [ $PROFILE_TYPE == "tizeniot" ]; then
	checkRootstrap "$ROOTSTRAP_TIZENIOT" $PROFILE_TYPE $DEVICE_TYPE $CURRENT_VERSION
elif [ $PROFILE_TYPE == "tv" ]; then
	checkRootstrap "$ROOTSTRAP_TV" $PROFILE_TYPE $DEVICE_TYPE $CURRENT_VERSION
fi

if [ $BUILD_PROFILE == "wearable" ]; then
	if [ -z "$ROOTSTRAP_WEARABLE" ]; then
		RunCommand "tizen build-native -a $ARCH_TYPE -c $COMPILER_TYPE -C $BUILD_TYPE -- $WORKSPACE_PATH/$PROJECT_NAME" "Building tpk $PROJECT_NAME"
	else
		RunCommand "tizen build-native -r $ROOTSTRAP_WEARABLE -a $ARCH_TYPE -c $COMPILER_TYPE -C $BUILD_TYPE -- $WORKSPACE_PATH/$PROJECT_NAME" "Building tpk $PROJECT_NAME"
	fi
elif [ $BUILD_PROFILE == "tizeniot" ]; then
	if [ -z "$ROOTSTRAP_TIZENIOT" ]; then
		RunCommand "tizen build-native -a $ARCH_TYPE -c $COMPILER_TYPE -C $BUILD_TYPE -- $WORKSPACE_PATH/$PROJECT_NAME" "Building tpk $PROJECT_NAME"
	else
		RunCommand "tizen build-native -r $ROOTSTRAP_TIZENIOT -a $ARCH_TYPE -c $COMPILER_TYPE -C $BUILD_TYPE -- $WORKSPACE_PATH/$PROJECT_NAME" "Building tpk $PROJECT_NAME"
	fi
elif [ $BUILD_PROFILE == "tv" ]; then
	if [ -z "$ROOTSTRAP_TV" ]; then
		RunCommand "tizen build-native -a $ARCH_TYPE -c $COMPILER_TYPE -C $BUILD_TYPE -- $WORKSPACE_PATH/$PROJECT_NAME" "Building tpk $PROJECT_NAME"
	else
		RunCommand "tizen build-native -r $ROOTSTRAP_TV -a $ARCH_TYPE -c $COMPILER_TYPE -C $BUILD_TYPE -- $WORKSPACE_PATH/$PROJECT_NAME" "Building tpk $PROJECT_NAME"
	fi
else
	if [ -z "$ROOTSTRAP_MOBILE" ]; then
		RunCommand "tizen build-native -a $ARCH_TYPE -c $COMPILER_TYPE -C $BUILD_TYPE -- $WORKSPACE_PATH/$PROJECT_NAME" "Building tpk $PROJECT_NAME"
	else
		RunCommand "tizen build-native -r $ROOTSTRAP_MOBILE -a $ARCH_TYPE -c $COMPILER_TYPE -C $BUILD_TYPE -- $WORKSPACE_PATH/$PROJECT_NAME" "Building tpk $PROJECT_NAME"
	fi
fi

if [ $PROFILE_TYPE == "tv" ]; then
	#If profile is tv then kuep signing for tpk is required
	echo $green"kuep signing of tpk has been started"$reset
	RunCommand "./kuep_net_signer.sh -s -tizen_major_ver 6 $WORKSPACE_PATH/$PROJECT_NAME/$BUILD_TYPE/$PROJECT_NAME"
	echo $green"kuep signing of tpk has been completed successfully"$reset
fi

RunCommand "tizen package --type tpk --sign test -- $WORKSPACE_PATH/$PROJECT_NAME/$BUILD_TYPE" "packaging of $PROJECT_NAME"

echo $green""
echo " ============================================"
echo "||              "$bold"CREATION  SUCCESSFUL$reset$green        ||"
echo " ============================================"
echo ""$reset
