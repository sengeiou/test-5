

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

TIMEOUT_VALUE=60 #default timeout value
FILE="/tmp/TC_Timeout.txt"
UTC_LOG_CORE=/tmp/utclog_core
SCRIPT_DIR="/home/owner/share"

# extract TCT configuration directory from TCT_CONFIG_FILE (/home/owner/share/TCT_CONFIG)
TCT_CONFIG_FILE=/home/owner/share/TCT_CONFIG
if [ ! -f $TCT_CONFIG_FILE ];then
	echo "$TCT_CONFIG_FILE is not Found : Can Not Read TCT Configuration File to get Execution Mode"
	exit 1;
fi
DEVICE_EXECUTION_MODE_30=`cat $TCT_CONFIG_FILE | grep DEVICE_EXECUTION_MODE_30 | cut -f 2- -d '='`
if [ $DEVICE_EXECUTION_MODE_30 == "" ]; then
	echo "'DEVICE_EXECUTION_MODE_30' key-value pair is not Found in $TCT_CONFIG_FILE. Unable to get Execution Mode"
	exit 1;
fi

if [[ "$1" == "" || "$2" == "" || "$3" == "" ]];
then
    echo "module name, TC name and build type type needed"
    exit 1
fi

#Read timeout value from /tmp/TCT_Timeout.txt file

if [ -f $FILE ];
then
	for next in `cat $FILE`
	do
	    TIMEOUT_VALUE=$next
	done
fi


function Execute {
	RESULT_PATH=/tmp/tcresult
	ERRLOG_PATH=/tmp/tclog
	rm -f $RESULT_PATH
	rm -f $ERRLOG_PATH
	rm -f $UTC_LOG_CORE
	
	## pre-launch script
	if [ -f $SCRIPT_DIR/pre_launch.sh ];
	then
		bash $SCRIPT_DIR/pre_launch.sh $1 $3 $2
	fi

	#execute directly via tct binary
	EXE_DIR=/usr/apps/native-$1-$3/bin
	if [ ! -e $EXE_DIR/tct-$1-native ];
	then
		echo "TCT Binary does not exist at '$EXE_DIR'. Please check if package is installed properly"
	fi

	#test case execution
	cd $EXE_DIR
	./tct-$1-native $2

	## post-launch script
	if [ -f $SCRIPT_DIR/post_launch.sh ];
	then
		bash $SCRIPT_DIR/post_launch.sh $1 $3 $2 
	fi

	COUNTER=0
	while [ ! -e $RESULT_PATH ];
	do
		if [ $COUNTER -eq $TIMEOUT_VALUE ];
		then
			# terminate launched application
			echo "Timeout! [ Execution exceeded $TIMEOUT_VALUE seconds ]"
			PROCESS_ID=`ps -ef | grep "tct-" | grep "tct-$1-native" | awk 'NR==1{printf "%s", $2}'`
			kill -9 $PROCESS_ID
			exit 1
		fi
		sleep 1
		COUNTER=$(($COUNTER + 1))
	done
	if [ -e $ERRLOG_PATH ];
	then
		echo `cat $ERRLOG_PATH`
		rm -f $ERRLOG_PATH
	fi
	if [ -e $UTC_LOG_CORE ];
	then
		echo `cat $UTC_LOG_CORE`
		rm -f $UTC_LOG_CORE
	fi
	exit `cat $RESULT_PATH`
}

function ExecuteUTC {
	RESULT_PATH=/tmp/tcresult
	ERRLOG_PATH=/tmp/utclog
	rm -f $RESULT_PATH
	rm -f $ERRLOG_PATH
	rm -f $UTC_LOG_CORE

	## pre-launch script
	if [ -f $SCRIPT_DIR/pre_launch.sh ];
	then
		bash $SCRIPT_DIR/pre_launch.sh $1 "utc" $2
	fi

	#execute directly via tct binary
	EXE_DIR=/usr/apps/core-$1-tests/bin
	if [ ! -e $EXE_DIR/tct-$1-core ];
	then
		echo "TCT Binary does not exist at '$EXE_DIR'. Please check if package is installed properly"
	fi

	#test case execution
	cd $EXE_DIR
	./tct-$1-core $2

	## post-launch script
	if [ -f $SCRIPT_DIR/post_launch.sh ];
	then
		bash $SCRIPT_DIR/post_launch.sh $1 "utc" $2 
	fi

	COUNTER=0
	while [ ! -e $RESULT_PATH ];
	do
		if [ $COUNTER -eq $TIMEOUT_VALUE ];
		then
			# terminate launched application
			echo "Timeout! [ Execution exceeded $TIMEOUT_VALUE seconds ]"
			PROCESS_ID=`ps -ef | grep "tct-" | grep "tct-$1-core" | awk 'NR==1{printf "%s", $2}'`
			kill -9 $PROCESS_ID
			exit 1
		fi
		sleep 1
		COUNTER=$(($COUNTER + 1))
	done
	if [ -e $ERRLOG_PATH ];
	then
		echo `cat $ERRLOG_PATH`
		rm -f $ERRLOG_PATH
	fi
	if [ -e $UTC_LOG_CORE ];
	then
		echo `cat $UTC_LOG_CORE`
		rm -f $UTC_LOG_CORE
	fi
	exit `cat $RESULT_PATH`
}

if [[ $3 == "itc" ]] || [[ $3 == "ctc" ]] ;then
	Execute $1 $2 $3
else
	ExecuteUTC $1 $2
fi






