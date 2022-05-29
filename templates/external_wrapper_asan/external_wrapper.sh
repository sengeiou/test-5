

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

############ address sanitizer ######################
ASAN_DIR=/tmp/asan_test
mkdir -p $ASAN_DIR
chmod 777 $ASAN_DIR -R
chsmack -a "*" $ASAN_DIR
rm -f $ASAN_DIR/asan.log.*
######################################################


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
	echo "'DEVICE_EXECUTION_MODE_30' key-value pair is not Found in $TCT_CONFIG_FILE"
	exit 1;
fi

UTC_LOG_CORE=/tmp/utclog_core

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
	
	RET=`su -c "app_launcher -e native.$1-$3 testcase_name $2" $DEVICE_EXECUTION_MODE_30`
	if [[ $RET == *"successfully launched"* ]];then
		echo "Successfully Launched"
	else
		echo "Launch Failed"
		su -c "app_launcher -t native.$1-$3 > /dev/null" $DEVICE_EXECUTION_MODE_30
		exit 1
	fi

	COUNTER=0
	while [ ! -e $RESULT_PATH ];
	do
		if [ $COUNTER -eq $TIMEOUT_VALUE ];
		then
			# terminate launched application
			su -c "app_launcher -t native.$1-$3 > /dev/null" $DEVICE_EXECUTION_MODE_30
			echo "Timeout! [ Execution exceeded $TIMEOUT_VALUE seconds ]"
			if [ -e $ERRLOG_PATH ];
			then
				echo `cat $ERRLOG_PATH`
				rm -f $ERRLOG_PATH
			fi
			############################## address sanitizer ############################
			echo "\n\n=========================== Address Sanitizer Info ==========================="
			ASAN_RESULT=`ls /tmp/asan_test`
			if [[ $ASAN_RESULT == "" ]];then
				echo "ASAN Did Not Find Any Memory Corruption Issue During Execution"
			else
				echo "--ASAN Found Following Memory Corruption Issue During Execution--"
				cat $ASAN_DIR/$ASAN_RESULT
			fi
			echo "================================================================================"
			#############################################################################
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
	############################## address sanitizer ############################
	echo "\n\n======================= Address Sanitizer Info ======================="
	ASAN_RESULT=`ls /tmp/asan_test`
	if [[ $ASAN_RESULT == "" ]];then
		echo "ASAN Did Not Find Any Memory Corruption Issue During Execution"
	else
		echo "--ASAN Found Following Memory Corruption Issue During Execution--"
		cat $ASAN_DIR/$ASAN_RESULT
	fi
	echo "================================================================"
	#############################################################################
	exit `cat $RESULT_PATH`
}

function ExecuteUTC {
	RESULT_PATH=/tmp/tcresult
	ERRLOG_PATH=/tmp/utclog
	rm -f $RESULT_PATH
	rm -f $ERRLOG_PATH
	rm -f $UTC_LOG_CORE
	RET=`su -c "app_launcher -e core.$1-tests testcase_name $2" $DEVICE_EXECUTION_MODE_30`
	if [[ $RET == *"successfully launched"* ]];then
		echo "Successfully Launched"
	else
		echo "Launch Failed"
		su -c "app_launcher -t core.$1-tests > /dev/null" $DEVICE_EXECUTION_MODE_30
		exit 1
	fi
	COUNTER=0
	while [ ! -e $RESULT_PATH ];
	do
		if [ $COUNTER -eq $TIMEOUT_VALUE ];
		then
			# terminate launched application
			su -c "app_launcher -t core.$1-tests > /dev/null" $DEVICE_EXECUTION_MODE_30
			echo "Timeout! [ Execution exceeded $TIMEOUT_VALUE seconds ]"

			############################## address sanitizer ############################
			echo "\n\n======================= Address Sanitizer Info ======================="
			ASAN_RESULT=`ls /tmp/asan_test`
			if [[ $ASAN_RESULT == "" ]];then
				echo "ASAN Did Not Find Any Memory Corruption Issue During Execution"
			else
				echo "--ASAN Found Following Memory Corruption Issue During Execution--"
				cat $ASAN_DIR/$ASAN_RESULT
			fi
			echo "================================================================"
			#############################################################################
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
	############################## address sanitizer ############################
	echo "\n\n======================= Address Sanitizer Info ======================="
	ASAN_RESULT=`ls /tmp/asan_test`
	if [[ $ASAN_RESULT == "" ]];then
		echo "ASAN Did Not Find Any Memory Corruption Issue During Execution"
	else
		echo "--ASAN Found Following Memory Corruption Issue During Execution--"
		cat $ASAN_DIR/$ASAN_RESULT
	fi
	echo "================================================================"
	#############################################################################
	exit `cat $RESULT_PATH`
}

if [[ $3 == "itc" ]] || [[ $3 == "ctc" ]] ;then
	Execute $1 $2 $3
else
	ExecuteUTC $1 $2
fi






