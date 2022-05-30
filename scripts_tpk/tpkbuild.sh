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

PWD=`pwd`
PROFILE_TYPE=""
ARCH_TYPE=""
TESTCASE_TYPE=""
MODULE_NAME=""
TC_COUNT=""


function helpusage {
# usage note
    echo "Usage: `basename $0` <build|install> <build_type> <module_name> <arch_type> <device_type>"
    echo "Usage: `basename $0` <addmod|rmmod> <build_type> <module_name>"
    echo "<build_type> = itc|ctc|utc"
    echo "<arch_type> = armv7l|x86 for 32bit architecture"
    echo "<arch_type> = aarch64|x86_64 for 64bit architecture"
    echo "<device_type> = mobile|wearable|tizeniot|tv"
    echo "commands description:"
    echo "       build       		performs SDK build"
    echo "       install      		install packages for execution"
    echo "       addmod      		add a new 'c' module"
    echo "       rmmod      		remove a module"
    echo "To build|install all the packages (itc,ctc and utc), usage: `basename $0` build|install <arch_type> <device_type>"
    echo "To build|install all packages of a <build_type>, usage: `basename $0` build|install <build_type> <arch_type> <device_type>"
    echo "addmod|rmmod is specific to build_type and module_name, usage: `basename $0` <addmod|rmmod> <build_type> <module_name>"
    echo ""
    exit 1
}

INSTALL_CHILD=0

if   [ "$1" != "addmod" ] && [ "$1" != "rmmod" ]; then
	if [ "$2" = "mobile" ] || [ "$3" = "mobile" ] || [ "$4" = "mobile" ] || [ "$5" = "mobile" ]; then
		PROFILE_TYPE="mobile"
	elif [ "$2" = "wearable" ] || [ "$3" = "wearable"  ] || [ "$4" = "wearable"  ] || [ "$5" = "wearable"  ]; then
		PROFILE_TYPE="wearable"
	elif [ "$2" = "tizeniot" ] || [ "$3" = "tizeniot"  ] || [ "$4" = "tizeniot"  ] || [ "$5" = "tizeniot"  ]; then
		PROFILE_TYPE="tizeniot"
	elif [ "$2" = "tv" ] || [ "$3" = "tv"  ] || [ "$4" = "tv"  ] || [ "$5" = "tv"  ]; then
		PROFILE_TYPE="tv"
	else
		echo "Add argument 'profile type (mobile,tv,tizeniot or wearable)'"
		helpusage
	fi
fi

if   [ "$1" != "addmod" ] && [ "$1" != "rmmod" ]; then
	if   [ "$2" = "armv7l" ] || [ "$3" = "armv7l" ] || [ "$4" = "armv7l" ] || [ "$5" = "armv7l" ]; then
		ARCH_TYPE="arm"
	elif [ "$2" = "x86" ] || [ "$3" = "x86"  ] || [ "$4" = "x86"  ] || [ "$5" = "x86"  ]; then
		ARCH_TYPE="x86"
	elif [ "$2" = "aarch64" ] || [ "$3" = "aarch64"  ] || [ "$4" = "aarch64"  ] || [ "$5" = "aarch64"  ]; then
		ARCH_TYPE="aarch64"
	elif [ "$2" = "x86_64" ] || [ "$3" = "x86_64"  ] || [ "$4" = "x86_64"  ] || [ "$5" = "x86_64"  ]; then
		ARCH_TYPE="x86_64"
	else
		echo "Add argument '32 bit architecture (armv7l or x86)'"
		echo "Add argument '64 bit architecture (aarch64 or x86_64)'"
		helpusage
	fi
fi

function check_tc_type {

	if [ "$#" -eq  "3" ]; then
		if   [ "$1" = "itc" ] || [ "$2" = "itc" ] || [ "$3" = "itc" ]; then
			TESTCASE_TYPE="itc"
		elif   [ "$1" = "utc" ] || [ "$2" = "utc" ] || [ "$3" = "utc" ]; then
			TESTCASE_TYPE="utc"
		elif   [ "$1" = "ctc" ] || [ "$2" = "ctc" ] || [ "$3" = "ctc" ]; then
			TESTCASE_TYPE="ctc"
		else
			echo "Add argument 'test case type (itc or ctc or utc)'"
			helpusage
		fi

	elif [ "$#" -eq  "4" ]; then
		if [ "$1" = "itc" ] || [ "$2" = "itc" ] || [ "$3" = "itc" ] || [ "$4" = "itc" ]; then
			TESTCASE_TYPE="itc"
		elif [ "$1" = "utc" ] || [ "$2" = "utc" ] || [ "$3" = "utc" ] || [ "$4" = "utc" ]; then
			TESTCASE_TYPE="utc"
		elif [ "$1" = "ctc" ] || [ "$2" = "ctc" ] || [ "$3" = "ctc" ] || [ "$4" = "ctc" ]; then
			TESTCASE_TYPE="ctc"
		else
			echo "Add argument 'test case type (itc or ctc or utc)'"
			helpusage
		fi
	fi
}

function build {

	if [ "$#" -eq  "2" ]; then
		scripts_tpk/tpk_create.sh $1 $2 $ARCH_TYPE $PROFILE_TYPE | tee -a BuildLog/$1/$2.txt

	#below code remove the log file in case build is SUCCESS
	#keep the log file only for build FAILED modules
	while read LINE
	do
		if [[ $LINE =~ "CREATION  SUCCESSFUL" ]] || [[ $LINE =~ "BUILD FAILED : Module doesn't exist" ]] || [[ $LINE =~ "'SKIPPING' THIS MODULE FROM BUILD PROCESS" ]]; then
			rm BuildLog/$1/$2.txt
			break
		fi
	done <BuildLog/$1/$2.txt

	elif [ "$#" -eq  "1" ]; then
		for module in `ls -1 src/$1/ | grep -v CMakeList`
		do
			build $1 $module
		done

	else
		for test_type in `ls -1 src/ | grep -v CMakeList | grep -v common`
		do
			build $test_type
		done
	fi
}

function install {

	TC_TYPE=$1
	MOD_NAME=$2
	TC_COUNT=1
	IS_COVERAGE=0

	if [ "$ARCH_TYPE" != "arm" ] ; then
		if  [[ ("$PROFILE_TYPE" == "tv") ]] ; then
			echo "$PROFILE_TYPE profile is not buildable and installable for $ARCH_TYPE architecture"
			exit 1;
		fi
	fi

	ROOTSTRAP_FILE=$(readlink -f rootstrap.txt)
	ROOTSTRAP_NAME=`cat $ROOTSTRAP_FILE | grep "${PROFILE_TYPE}_$ARCH_TYPE:" | cut -f 2- -d ':'`
	ROOTSTRAP_ARCH=`tizen list rootstrap | grep "${ROOTSTRAP_NAME}" | cut -f4 -d' '`
	if [ "$ARCH_TYPE" == "arm" ] || [ "$ARCH_TYPE" == "aarch64" ] ; then
		ln -sf ./scripts_tpk/tpk-install.py $PWD/tpk-install
		python tpk-install $ARCH_TYPE $PROFILE_TYPE $TC_COUNT $IS_COVERAGE $TC_TYPE $MOD_NAME
	elif [ "$ARCH_TYPE" == "x86" ] || [ "$ARCH_TYPE" == "x86_64" ] ; then
		ln -sf ./scripts_tpk/tpksdk-install.py $PWD/tpksdk-install
		if [ "$ROOTSTRAP_ARCH" == "i586" ]; then
			python tpksdk-install $ROOTSTRAP_ARCH $PROFILE_TYPE $TC_COUNT $IS_COVERAGE $TC_TYPE $MOD_NAME
		else
			python tpksdk-install $ARCH_TYPE $PROFILE_TYPE $TC_COUNT $IS_COVERAGE $TC_TYPE $MOD_NAME
		fi
	fi

	if [ $INSTALL_CHILD == 1 ]; then
		echo "------ Generating child packages..."
		bash $PWD/scripts_tpk/child-package-generator.sh $TC_TYPE $MOD_NAME $PROFILE_TYPE $TC_CHILD_COUNT
		if [ $? -ne 0 ]; then
			cd $PWD
			echo "------ child-package-generator script Failed to generate child packages"
			exit 1;
		fi
		cd $PWD
	fi
}
function install_coverage {

	TC_TYPE=$1
	MOD_NAME=$2
	TC_COUNT=1
	IS_COVERAGE=1

	if [ "$ARCH_TYPE" != "arm" ] ; then
		if  [ "$PROFILE_TYPE" == "tv" ] ; then
			echo "$PROFILE_TYPE profile is not buildable and coverage installable for $ARCH_TYPE architecture"
		exit 1;
		fi
	fi

	if [ "$ARCH_TYPE" == "arm" ] || [ "$ARCH_TYPE" == "aarch64" ] ; then
		ln -sf ./scripts_tpk/tpk-install.py $PWD/tpk-install
		python tpk-install $ARCH_TYPE $PROFILE_TYPE $TC_COUNT $IS_COVERAGE $TC_TYPE $MOD_NAME
	elif [ "$ARCH_TYPE" == "x86" ] || [ "$ARCH_TYPE" == "x86_64" ] ; then
		ln -sf ./scripts_tpk/tpksdk-install.py $PWD/tpksdk-install
		python tpksdk-install $ARCH_TYPE $PROFILE_TYPE $TC_COUNT $IS_COVERAGE $TC_TYPE $MOD_NAME
	fi

	if [ $INSTALL_CHILD == 1 ]; then
		echo "------ Generating child packages..."
		bash $PWD/scripts_tpk/child-package-generator.sh $TC_TYPE $MOD_NAME $PROFILE_TYPE $TC_CHILD_COUNT
		if [ $? -ne 0 ]; then
			cd $PWD
			echo "------ child-package-generator script Failed to generate child packages"
			exit 1;
		fi
		cd $PWD
	fi
}

function install_custom {

	TC_TYPE=$2
	MOD_NAME=$3
	TC_COUNT=$1
	IS_COVERAGE=0

	if [ "$ARCH_TYPE" == "arm" ] || [ "$ARCH_TYPE" == "aarch64" ]; then
		ln -sf ./scripts_tpk/tpk-install.py $PWD/tpk-install
		python tpk-install $ARCH_TYPE $PROFILE_TYPE $TC_COUNT $IS_COVERAGE $TC_TYPE $MOD_NAME
	elif [ "$ARCH_TYPE" == "x86" ] || [ "$ARCH_TYPE" == "x86_64" ] ; then
		ln -sf ./scripts_tpk/tpksdk-install.py $PWD/tpksdk-install
		python tpksdk-install $ARCH_TYPE $PROFILE_TYPE $TC_COUNT $IS_COVERAGE $TC_TYPE $MOD_NAME
	fi

	if [ $INSTALL_CHILD == 1 ]; then
		echo "------ Generating child packages..."
		bash $PWD/scripts_tpk/child-package-generator.sh $TC_TYPE $MOD_NAME $PROFILE_TYPE $TC_CHILD_COUNT
		if [ $? -ne 0 ]; then
			cd $PWD
			echo "------ child-package-generator script Failed to generate child packages"
			exit 1;
		fi
		cd $PWD
	fi

}

# d_showVar VARNAME -- print bash variable name
function d_showVar { if [ "$ARG" == "-d" -a -n "$1" ]; then echo "d >> ${1} = ${!1}"; fi }
# keyprompt "introductory message" -- wait until any key pressed
function keyprompt { echo -ne "\n\e[1;31m$1 -- " && read -n 1 && echo -e "\n\e[0m"; }
# d_bp -- breakpoint at which user need to press any key to proceed
function d_bp { if [[ "$ARG" == "-d" ]]; then keyprompt "d >> Press any key"; fi }

PROJECT_DIR="$(cd "$(dirname $0)" && pwd)"
d_showVar PROJECT_DIR


function add_module {
	# argument check
	if [ -z "$2" ]; then echo "Usage: `basename $0` addmod <build_type> <module_name>"; exit 1; fi
	if [ $1 != "itc" ] && [ $1 != "ctc" ] && [ $1 != "utc" ]; then echo "Usage: `basename $0` addmod <build_type> <module_name> ; <build_type> = itc or ctc or utc"; exit 1; fi

	BUILD_TYPE=$1
	MODULE_NAME=$2

	MODE="c"
	LANG_NAME="c"
	LANG_COMPILER_NAME="C"

	d_showVar MODULE_NAME
	MODULE_NAME_C=$(echo $MODULE_NAME | sed -e 's/-\([a-z]\)/\U\1/' -e 's/^\([a-z]\)/\U\1/')
	d_showVar MODULE_NAME_C
	MODULE_NAME_U=$(echo $MODULE_NAME | sed -e 's/-/_/g')
	d_showVar MODULE_NAME_U
	MODULE_LIBNAME=$2
	d_showVar MODULE_LIBNAME
	TAG_SPEC=$BUILD_TYPE
	PREFIX="native"
	if [ $1 == "utc" ]; then
		TAG_SPEC="tests"
		PREFIX="core"
	fi

	HEADER_TOP=$(echo $2 | tr '[:lower:]' '[:upper:]' | sed -e 's/-/_/g' -e 's/\./_/')
	echo "Adding $BUILD_TYPE:->$MODULE_NAME module to project..."
	d_bp
	cd $PROJECT_DIR
# prepare .xml file
	echo "-- Generating packaging/$BUILD_TYPE/$PREFIX-$MODULE_NAME-$TAG_SPEC.xml manifest file"
	LABEL=${MODULE_NAME^}
	LABEL=`echo $LABEL | sed -e 's/-\(\w\)/\U\1/g'`
	sed -e "s:MODULE:$MODULE_NAME:g" -e "s:LABEL:$LABEL:g" \
	templates/src-directory/$BUILD_TYPE/$PREFIX-\[module_name\]-$TAG_SPEC.xml > packaging/$BUILD_TYPE/$PREFIX-$MODULE_NAME-$TAG_SPEC.xml
	# prepare src directory
	mkdir src/$BUILD_TYPE/$MODULE_NAME
	echo "-- Generating src/$BUILD_TYPE/$MODULE_NAME/CMakeLists.txt file"
	if [ $LANG_COMPILER_NAME == "CXX" ]; then
		sed -e "s:%{MODULE_NAME}:$MODULE_NAME:g" -e "s:%{MODULE_LIBNAME}:$MODULE_LIBNAME:g" -e "s:%{LANG_NAME}:$LANG_NAME:g" -e "s:%{LANG_COMPILER_NAME}:$LANG_COMPILER_NAME:g" \
        templates/src-directory/$BUILD_TYPE/CMakeLists.txt > src/$BUILD_TYPE/$MODULE_NAME/CMakeLists.txt
	else
		sed -e "s:%{MODULE_NAME}:$MODULE_NAME:g" -e "s:%{MODULE_LIBNAME}:$MODULE_LIBNAME:g" -e "s:%{LANG_NAME}:$LANG_NAME:g" -e "/LANG_COMPILER_NAME/d" \
	templates/src-directory/$BUILD_TYPE/CMakeLists.txt > src/$BUILD_TYPE/$MODULE_NAME/CMakeLists.txt
	fi
	echo "-- Generating src/$BUILD_TYPE/$MODULE_NAME/tct-$MODULE_NAME-$PREFIX.$MODE file"
	sed -e "s:%{MODULE_NAME}:$MODULE_NAME:g" \
	templates/src-directory/$BUILD_TYPE/tct-\[module_name\]-$PREFIX.c > src/$BUILD_TYPE/$MODULE_NAME/tct-$MODULE_NAME-$PREFIX.$MODE
	echo "-- Generating src/$BUILD_TYPE/$MODULE_NAME/tct-$MODULE_NAME-$PREFIX header files for mobile, wearable,tizeniot and tv"
	sed -e "s:%{MODULE_NAME_U}:$MODULE_NAME_U:g" -e "s:%{HEADER_TOP}:$HEADER_TOP:g" \
	templates/src-directory/$BUILD_TYPE/tct-\[module_name\]-$PREFIX\_mobile.h > src/$BUILD_TYPE/$MODULE_NAME/tct-$MODULE_NAME-$PREFIX\_mobile.h
	sed -e "s:%{MODULE_NAME_U}:$MODULE_NAME_U:g" -e "s:%{HEADER_TOP}:$HEADER_TOP:g" \
	templates/src-directory/$BUILD_TYPE/tct-\[module_name\]-$PREFIX\_wearable.h > src/$BUILD_TYPE/$MODULE_NAME/tct-$MODULE_NAME-$PREFIX\_wearable.h
	sed -e "s:%{MODULE_NAME_U}:$MODULE_NAME_U:g" -e "s:%{HEADER_TOP}:$HEADER_TOP:g" \
	templates/src-directory/$BUILD_TYPE/tct-\[module_name\]-$PREFIX\_tv.h > src/$BUILD_TYPE/$MODULE_NAME/tct-$MODULE_NAME-$PREFIX\_tv.h
	sed -e "s:%{MODULE_NAME_U}:$MODULE_NAME_U:g" -e "s:%{HEADER_TOP}:$HEADER_TOP:g" \
        templates/src-directory/$BUILD_TYPE/tct-\[module_name\]-$PREFIX\_tizeniot.h > src/$BUILD_TYPE/$MODULE_NAME/tct-$MODULE_NAME-$PREFIX\_tizeniot.h


	if [ $BUILD_TYPE == "itc" ]; then
		# generate ITs file
		echo "-- Generating src/$BUILD_TYPE/$MODULE_NAME/ITs-$MODULE_NAME.$MODE file"
		sed -e "s:%{MODULE_NAME}:$MODULE_NAME:g" -e "s:%{MODULE_NAME_U}:$MODULE_NAME_U:g" -e "s:%{MODULE_NAME_C}:$MODULE_NAME_C:g" \
		templates/src-directory/$BUILD_TYPE/ITs-\[module_name\].c > src/$BUILD_TYPE/$MODULE_NAME/ITs-$MODULE_NAME.$MODE

		# generate Common C file
		echo "-- Generating src/$BUILD_TYPE/$MODULE_NAME/ITs-$MODULE_NAME-common.$MODE file"
		sed -e "s:%{MODULE_NAME}:$MODULE_NAME:g" \
		templates/src-directory/$BUILD_TYPE/ITs-\[module_name\]-common.c > src/$BUILD_TYPE/$MODULE_NAME/ITs-$MODULE_NAME-common.$MODE

		# generate Common header file
		echo "-- Generating src/$BUILD_TYPE/$MODULE_NAME/ITs-$MODULE_NAME-common.h file"
		sed -e "s:%{MODULE_NAME_U}:$MODULE_NAME_U:g" -e "s:%{MODULE_NAME_C}:$MODULE_NAME_C:g" -e "s:%{HEADER_TOP}:$HEADER_TOP:g" \
		templates/src-directory/$BUILD_TYPE/ITs-\[module_name\]-common.h > src/$BUILD_TYPE/$MODULE_NAME/ITs-$MODULE_NAME-common.h
	else
		if [ $BUILD_TYPE == "ctc" ]; then
			# generate ctc file
			echo "-- Generating src/$BUILD_TYPE/$MODULE_NAME/CTs-$MODULE_NAME.$MODE file"
			sed -e "s:%{MODULE_NAME}:$MODULE_NAME:g" -e "s:%{MODULE_NAME_U}:$MODULE_NAME_U:g" -e "s:%{MODULE_NAME_C}:$MODULE_NAME_C:g" \
			templates/src-directory/$BUILD_TYPE/CTs-\[module_name\].c > src/$BUILD_TYPE/$MODULE_NAME/CTs-$MODULE_NAME.$MODE

			# generate Common C file
			echo "-- Generating src/$BUILD_TYPE/$MODULE_NAME/CTs-$MODULE_NAME-common.$MODE file"
			sed -e "s:%{MODULE_NAME}:$MODULE_NAME:g" \
			templates/src-directory/$BUILD_TYPE/CTs-\[module_name\]-common.c > src/$BUILD_TYPE/$MODULE_NAME/CTs-$MODULE_NAME-common.$MODE

			# generate Common header file
			echo "-- Generating src/$BUILD_TYPE/$MODULE_NAME/CTs-$MODULE_NAME-common.h file"
			sed -e "s:%{MODULE_NAME_U}:$MODULE_NAME_U:g" -e "s:%{MODULE_NAME_C}:$MODULE_NAME_C:g" -e "s:%{HEADER_TOP}:$HEADER_TOP:g" \
			templates/src-directory/$BUILD_TYPE/CTs-\[module_name\]-common.h > src/$BUILD_TYPE/$MODULE_NAME/CTs-$MODULE_NAME-common.h
		else
			# generate utc file
			echo "-- Generating src/$BUILD_TYPE/$MODULE_NAME/utc-$MODULE_NAME.$MODE file"
			sed -e "s:%{MODULE_NAME}:$MODULE_NAME:g" -e "s:%{MODULE_NAME_U}:$MODULE_NAME_U:g" -e "s:%{MODULE_NAME_C}:$MODULE_NAME_C:g" \
			templates/src-directory/$BUILD_TYPE/utc-\[module_name\].c > src/$BUILD_TYPE/$MODULE_NAME/utc-$MODULE_NAME.$MODE
		fi
	fi
	echo "Task finished successfully"
}

function rm_module {
	# argument check
	if [ -z "$2" ]; then echo "Usage: `basename $0` rmmod <build_type> <module_name>"; exit 1; fi
	if [ $1 != "itc" ] && [ $1 != "ctc" ] && [ $1 != "utc" ]; then echo "Usage: `basename $0` rmmod <build_type> <module_name> ; <build_type> = itc or ctc or utc"; exit 1; fi

	BUILD_TYPE=$1
	MODULE_NAME=$2
	d_showVar BUILD_TYPE
	d_showVar MODULE_NAME
	TAG_SPEC=$BUILD_TYPE
	PREFIX="native"
	if [ $1 == "utc" ]; then
		TAG_SPEC="tests"
		PREFIX="core"
	fi

	TIZEN____="tizen_native_6.5"

	echo "Removing $BUILD_TYPE:->$MODULE_NAME module from project..."
	TO_PKG_DIR="/opt/tct/$TIZEN____/packages"
	echo "---- Updating $TO_PKG_DIR/pkg_infos/mobile_pkg_info.xml"
	python scripts_tpk/tcpackageslistsgen.py $BUILD_TYPE $MODULE_NAME mobile $TO_PKG_DIR/pkg_infos/mobile_pkg_info.xml 1 0 1
	if [ $? -ne 0 ]; then echo "Aborting..."; exit 1; fi
	echo "---- Updating $TO_PKG_DIR/pkg_infos/wearable_pkg_info.xml"
	python scripts_tpk/tcpackageslistsgen.py $BUILD_TYPE $MODULE_NAME wearable $TO_PKG_DIR/pkg_infos/wearable_pkg_info.xml 1 0 1
	if [ $? -ne 0 ]; then echo "Aborting..."; exit 1; fi
	echo "---- Updating $TO_PKG_DIR/pkg_infos/tv_pkg_info.xml"
	python scripts_tpk/tcpackageslistsgen.py $BUILD_TYPE $MODULE_NAME tv $TO_PKG_DIR/pkg_infos/tv_pkg_info.xml 1 0 1
	if [ $? -ne 0 ]; then echo "Aborting..."; exit 1; fi
	echo "---- Updating $TO_PKG_DIR/pkg_infos/tizeniot_pkg_info.xml"
        python scripts_tpk/tcpackageslistsgen.py $BUILD_TYPE $MODULE_NAME tizeniot $TO_PKG_DIR/pkg_infos/tizeniot_pkg_info.xml 1 0 1
	if [ $? -ne 0 ]; then echo "Aborting..."; exit 1; fi

	cd $PROJECT_DIR
	echo "-- Removing packaging/$BUILD_TYPE/$PREFIX-$MODULE_NAME-$TAG_SPEC.xml file"
	rm packaging/$BUILD_TYPE/$PREFIX-$MODULE_NAME-$TAG_SPEC.xml
	echo "-- Removing src/$BUILD_TYPE/$MODULE_NAME directory"
	rm -r src/$BUILD_TYPE/$MODULE_NAME
	echo "Task finished successfully"
}

if [ "$1" = "install_child"  ]; then
	if [[ $4 == ?(-)+([0-9]) ]]; then
		TC_CHILD_COUNT=$4
	elif [[ $5 == ?(-)+([0-9]) ]]; then
		TC_CHILD_COUNT=$5
	elif [[ $6 == ?(-)+([0-9]) ]]; then
		TC_CHILD_COUNT=$6
	fi
fi

if [ -z "$1" ]; then
	helpusage
elif [ "addmod" == "$1" ]; then
# add new module
	if [ "$#" -gt  "3" ]; then echo "Usage: `basename $0` addmod <build_type> <module_name>"; exit 1; fi
	add_module $2 $3
elif [ "rmmod" == "$1" ]; then
# remove module
	if [ "$#" -gt  "3" ]; then echo "Usage: `basename $0` addmod <build_type> <module_name>"; exit 1; fi
	rm_module $2 $3
elif [ "build" == "$1" ]; then

	if [ -d BuildLog ];then
		rm -rf BuildLog
	fi
	mkdir -p BuildLog/itc
	mkdir -p BuildLog/ctc
	mkdir -p BuildLog/utc

	if [ "$#" -eq  "3" ]; then
		build

	elif  [ "$#" -eq  "4" ]; then
		check_tc_type $2 $3 $4
		build $TESTCASE_TYPE

	elif  [ "$#" -eq  "5" ]; then
		check_tc_type $2 $3 $4 $5
		MODULE_NAME=$3
		build $TESTCASE_TYPE $MODULE_NAME

	else
		echo "Entered wrong number of arguments"
		helpusage
	fi

elif [ "install" == "$1" ]; then

	if [ "$#" -eq  "3" ]; then
		install

	elif  [ "$#" -eq  "4" ]; then
		check_tc_type $2 $3 $4
		install $TESTCASE_TYPE

	elif  [ "$#" -eq  "5" ]; then
		check_tc_type $2 $3 $4 $5
		MODULE_NAME=$3
		install $TESTCASE_TYPE $MODULE_NAME

	else
		echo "Entered wrong number of arguments"
		helpusage
	fi

elif [ "install_coverage" == "$1" ]; then

	if [ "$#" -eq  "3" ]; then
		install_coverage

	elif  [ "$#" -eq  "4" ]; then
		check_tc_type $2 $3 $4
		install_coverage $TESTCASE_TYPE

	elif  [ "$#" -eq  "5" ]; then
		check_tc_type $2 $3 $4 $5
		MODULE_NAME=$3
		install_coverage $TESTCASE_TYPE $MODULE_NAME

	else
		echo "Entered wrong number of arguments"
		helpusage
	fi

elif [ "install_child" == "$1" ]; then

	INSTALL_CHILD=1
	if [ "$#" -eq  "4" ]; then
		install

	elif  [ "$#" -eq  "5" ]; then
		check_tc_type $2 $3 $4
		install $TESTCASE_TYPE

	elif  [ "$#" -eq  "6" ]; then
		check_tc_type $2 $3 $4 $5
		MODULE_NAME=$3
		install $TESTCASE_TYPE $MODULE_NAME

	else
		echo "Entered wrong number of arguments"
		helpusage
	fi
elif [ "install_custom" == "$1" ]; then

	if [ "$#" -eq  "4" ]; then
		TC_COUNT=$4
		MODULE_NAME=""
		install_custom $TC_COUNT $MODULE_NAME

	elif  [ "$#" -eq  "5" ]; then
		check_tc_type $2 $3 $4 $5
		MODULE_NAME=""
		TC_COUNT=$5
		install_custom $TC_COUNT $TESTCASE_TYPE $MODULE_NAME

	elif  [ "$#" -eq  "6" ]; then
		check_tc_type $2 $3 $4 $5 $6
		TESTCASE_TYPE=$2
		MODULE_NAME=$3
		TC_COUNT=$6
		install_custom $TC_COUNT $TESTCASE_TYPE $MODULE_NAME
	else
		echo "Entered wrong number of arguments"
		helpusage
	fi

else
	echo "Entered invalid arguments"
	helpusage
fi
