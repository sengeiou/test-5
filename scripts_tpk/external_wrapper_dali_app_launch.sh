

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

TIME_FACTOR=10
RESULT_PATH=/tmp/tcresult
ERRLOG_PATH=/tmp/tclog
UTC_LOG_CORE=/tmp/utclog_core

#Read timeout value from /tmp/TCT_Timeout.txt file
if [ -f $FILE ];
then
	for next in `cat $FILE`
	do
	    TIMEOUT_VALUE=$next
	done
fi

function KillPackage {
	pkgcmd --kill -n $1
	sleep 2
}


function Execute {
	rm -f $RESULT_PATH
	rm -f $ERRLOG_PATH
	rm -f $UTC_LOG_CORE

	RET=`su -c "app_launcher -s $1 testcase_name $2" $DEVICE_EXECUTION_MODE_30`
	if [[ $RET != *"successfully launched"* ]];then
		su -c "app_launcher -k $1 > /dev/null" $DEVICE_EXECUTION_MODE_30
		exit 1
	fi

	COUNTER=0
	i=0
	TIME_OUT=0
	while [ ! -e $RESULT_PATH ];
	do
		if [ $COUNTER -eq $TIMEOUT_VALUE ];
		then
			TIME_OUT=1
			break
		fi
		for i in {1..20}
		do
			sleep 0.1
			RE=`su -c "app_launcher -r $1 " $DEVICE_EXECUTION_MODE_30`
			if [[ $RE == *"result: running"* ]];then
				continue
			else
				break
			fi
		done
		COUNTER=$(($COUNTER + 2))
	done

	su -c "app_launcher -k $1 > /dev/null" $DEVICE_EXECUTION_MODE_30
	for i in {1..100}
	do
		sleep 0.1
		RE=`su -c "app_launcher -r $1 " $DEVICE_EXECUTION_MODE_30`
		if [[ $RE == *"result: running"* ]];then
			continue
		else
			break
		fi
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
	if [[ $TIME_OUT == "1" ]];
	then
		exit 1
	fi

	exit `cat $RESULT_PATH`
}


Execute $1 $2
