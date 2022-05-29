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

 NAME=$(basename $(cd $(dirname $0);pwd))

 MOD_NAME=%{MOD_NAME}

 PKG_DIR=%{PKG_DIR} # directory supplied by external script

 PKG_NAME=%{PKG_NAME} # name supplied by external script

 PKG_FULLNAME=%{PKG_FULLNAME} # name supplied by external script

 APP_DIR=/usr/apps

 #parse params
 USAGE="Usage: ./inst.sh [-i] [-u]
   -i install wgt and config environment
   -u uninstall wgt and remove source file
 [-i] option was set as default."
 # extract TCT configuration directory from TCT_CONFIG_FILE (/home/owner/share/TCT_CONFIG)
TCT_CONFIG_FILE=/home/owner/share/TCT_CONFIG
if [ ! -f $TCT_CONFIG_FILE ];then
	echo ""
	echo "****************FATAL ERROR : inst.sh***************************"
	echo "$TCT_CONFIG_FILE is not Found : Can Not Read TCT Configuration Directory"
	echo "$PKG_NAME : INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi
ADMIN_USER_30=`cat $TCT_CONFIG_FILE | grep DEVICE_ADMIN_USER_30 | cut -f 2- -d '='`
if [[ $ADMIN_USER_30 == "" ]]; then
	echo ""
	echo "****************FATAL ERROR : inst.sh***************************"
	echo "'DEVICE_ADMIN_USER_30' key-value pair is not Found"
	echo "$PKG_NAME : INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi
DEVICE_SUITE_TARGET_30=`cat $TCT_CONFIG_FILE | grep DEVICE_SUITE_TARGET_30 | cut -f 2- -d '='`
if [ $DEVICE_SUITE_TARGET_30 == "" ]; then
	echo ""
	echo "****************FATAL ERROR : inst.sh***************************"
	echo "'DEVICE_SUITE_TARGET_30' key-value pair is not Found"
	echo "$PKG_NAME : INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi
DEVICE_PHYSICAL_STORAGE_30=`cat $TCT_CONFIG_FILE | grep DEVICE_PHYSICAL_STORAGE_30 | cut -f 2- -d '='`
if [ $DEVICE_PHYSICAL_STORAGE_30 == "" ]; then
	echo ""
	echo "****************FATAL ERROR : inst.sh***************************"
	echo "'DEVICE_PHYSICAL_STORAGE_30' key-value pair is not Found"
	echo "$PKG_NAME : INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi
DEVICE_EXTERNAL_STORAGE_30=/`lsblk | grep /opt/media | cut -f 2- -d '/'  | head -1`
if [ "$DEVICE_EXTERNAL_STORAGE_30" == "/" ]; then
	echo ""
	echo "****************INFO : inst.sh********************************************"
	echo "'DEVICE_EXTERNAL_STORAGE_30' is NULL, external storage device not attached"
	echo "***************INFO : Path required for module media-content ITC**********"
	echo "**************************************************************************"
	echo ""
	return;
fi
DEVICE_USER_30=`cat $TCT_CONFIG_FILE | grep DEVICE_USER_30 | cut -f 2- -d '='`
if [[ $DEVICE_USER_30 == "" ]]; then
	echo ""
	echo "****************FATAL ERROR : inst.sh***************************"
	echo "'DEVICE_USER_30' key-value pair is not Found"
	echo "$PKG_NAME : INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi
DEVICE_EXECUTION_MODE_30=`cat $TCT_CONFIG_FILE | grep DEVICE_EXECUTION_MODE_30 | cut -f 2- -d '='`
if [ $DEVICE_EXECUTION_MODE_30 == "" ]; then
	echo ""
	echo "****************FATAL ERROR : inst.sh***************************"
	echo "'DEVICE_EXECUTION_MODE_30' key-value pair is not Found"
	echo "$PKG_NAME : INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi
if [[ "$DEVICE_EXECUTION_MODE_30" == "$ADMIN_USER_30" ]]; then
APPS_ROOT=`cat $TCT_CONFIG_FILE | grep DEVICE_ADMIN_USER_APPS_ROOT_30 | cut -f 2- -d '='`
GLOBAL_OPT="--global"
else
APPS_ROOT=`cat $TCT_CONFIG_FILE | grep DEVICE_OTHER_USER_APPS_ROOT_30 | cut -f 2- -d '='`
GLOBAL_OPT=""
fi
echo "ADMIN_USER_30 = $ADMIN_USER_30"
echo "APPS_ROOT = $APPS_ROOT"
if [ $APPS_ROOT == "" ]; then
	echo ""
	echo "****************FATAL ERROR : inst.sh***************************"
	echo "'DEVICE_ADMIN(or OTHER)_USER_APPS_ROOT_30' key-value pair is not Found"
	echo "$PKG_NAME : INSTALLATION/UNINSTALLATION Can Not Proceed"
	echo "********************************************************************"
	echo ""
	return;
fi

APPS_RW_DIR=$DEVICE_USER_30/apps_rw

TCT_DIR="opt/$NAME"

PKG_DIR=$DEVICE_SUITE_TARGET_30/tct/$TCT_DIR

echo "DEVICE_EXECUTION_MODE_30 = $DEVICE_EXECUTION_MODE_30"
if [[ $PKG_NAME == *"-itc" ]] ;then
	SUITENAME=$MOD_NAME-native
	#APP_ID=native.${PKG_NAME#native-}
	APP_ID=$PKG_NAME
elif [[ $PKG_NAME == *"-ctc" ]]; then
	SUITENAME=$MOD_NAME-ctc
	APP_ID=$PKG_NAME
else
	SUITENAME=$MOD_NAME-core
	APP_ID=$PKG_NAME
fi

 function installpkg(){
    if [ `date +%Y` -lt 2015 ]
    then
        date -s "1 JUL 2015 00:00:00"
    fi

    if [ ! -d $DEVICE_SUITE_TARGET_30/res/ ]; then
        mkdir $DEVICE_SUITE_TARGET_30/res
    fi
    #cp -rf $PKG_DIR/res $DEVICE_SUITE_TARGET_30/
    #find $DEVICE_SUITE_TARGET_30/res/ -exec chsmack -a "User::App::Shared" {} \;
    su -c "pkgcmd $GLOBAL_OPT -i -q -t tpk -p /$PKG_DIR/$PKG_FULLNAME" $DEVICE_EXECUTION_MODE_30

	for i in `grep -r "0xA" /var/cynara/db/_ | grep $PKG_NAME`
	do
		CLIENT=`echo $i | cut -d ";" -f1`
		USER=`echo $i | cut -d ";" -f2`
		PRIVILEGE=`echo $i | cut -d ";" -f3`

		#echo "cyad --erase=\"\" -r=no -c $CLIENT -u $USER -p $PRIVILEGE"
		cyad --erase="" -r=no -c $CLIENT -u $USER -p $PRIVILEGE
	done

	if [ -e $APPS_ROOT/$PKG_NAME/shared/res/spec.sh ];then
		cp -rf $APPS_ROOT/$PKG_NAME/shared/res $DEVICE_SUITE_TARGET_30/
		find $DEVICE_SUITE_TARGET_30/res/ -exec chsmack -a "User::App::Shared" {} \;
		WORKDIR=`pwd`
		cd $APPS_ROOT/$PKG_NAME/shared/res
		chmod -R 777 ./spec.sh
		sh ./spec.sh $PKG_NAME
		cd $WORKDIR
	fi

    if [ -e $PKG_DIR/post-inst.sh ];then
	WORKDIR=`pwd`
	cd $PKG_DIR
	chmod -R 777 ./post-inst.sh
	sh ./post-inst.sh $PKG_NAME inst
	cd $WORKDIR
    fi

    mkdir -p $APPS_RW_DIR/$PKG_NAME/data
    if [ -d $APP_DIR/$PKG_NAME/data ]; then
        cp -a $APP_DIR/$PKG_NAME/data/* $APPS_RW_DIR/$PKG_NAME/data/
    fi
    chown -R $DEVICE_EXECUTION_MODE_30:users $APPS_RW_DIR/$PKG_NAME/

    cp $PKG_DIR/external_wrapper.sh $DEVICE_SUITE_TARGET_30/

    if [ "$(echo $HOSTTYPE)" == "armv7l" ]; then
	    applist=`ls $DEVICE_SUITE_TARGET_30/res | grep -e tpk -e rpk | grep arm`
    elif [ "$(echo $HOSTTYPE)" == "aarch64" ]; then
	    applist=`ls $DEVICE_SUITE_TARGET_30/res | grep -e tpk -e rpk | grep aarch64`
    elif [ "$(echo $HOSTTYPE)" == "x86" ]; then
	    applist=`ls $DEVICE_SUITE_TARGET_30/res | grep -e tpk -e rpk | grep x86 | grep -v x86_64`
    elif [ "$(echo $HOSTTYPE)" == "x86_64" ]; then
	    applist=`ls $DEVICE_SUITE_TARGET_30/res | grep -e tpk -e rpk | grep x86_64`
    else
	    applist=`ls $DEVICE_SUITE_TARGET_30/res | grep -e tpk -e rpk | grep x86 | grep -v x86_64`
	    applist2=`ls $DEVICE_SUITE_TARGET_30/res | grep -e tpk -e rpk | grep -e i386 -e i586`
	    applist="$applist $applist2"
    fi

    for app in $applist
    do
	   if [[ "$app" == "org.tizen.globalapp"* ]]; then
		   cp $DEVICE_SUITE_TARGET_30/res/$app /tmp/
		   su -c "pkgcmd --global -iqt tpk -p /tmp/$app > /dev/null" $ADMIN_USER_30
	   else
		   su -c "pkgcmd $GLOBAL_OPT -iqt tpk -p $DEVICE_SUITE_TARGET_30/res/$app > /dev/null" $DEVICE_EXECUTION_MODE_30
	   fi
    done

    if [[ $PKG_NAME == *"application"* || $PKG_NAME == *"message-port"* ]]; then
	    ( echo 3 ; sleep 1 ; echo MIIClTCCAX2gAwIBAgIGAU1wuKP1MA0GCSqGSIb3DQEBBQUAMFYxGjAYBgNVBAoMEVRpemVuIEFzc29jaWF0aW9uMRowGAYDVQQLDBFUaXplbiBBc3NvY2lhdGlvbjEcMBoGA1UEAwwTVGl6ZW4gRGV2ZWxvcGVycyBDQTAeFw0xMjExMDEwMDAwMDBaFw0xOTAxMDEwMDAwMDBaMBExDzANBgNVBAMMBmF1dGhvcjCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAkzTMc+oxDLzYKi7TWoN8vMeMwLTdjxECyrdrv/8SJmqzvV4fYVUKx7kdRHCHazb1BGDxtgt4Ntilc+Qt5a42BNi19HTDpoWuga1fL7U3B/UNRmWjarHQQOLKcQ+2QD4vMjVpf4UOe8zE9ssCTKDNEw5ELV6XVwWoP9GYIXMug2UCAwEAAaMyMDAwDAYDVR0TAQH/BAIwADALBgNVHQ8EBAMCB4AwEwYDVR0lBAwwCgYIKwYBBQUHAwMwDQYJKoZIhvcNAQEFBQADggEBAMj0yAvusFduH+ABua+EijUBRzfhy68WaXOB7i4KfBYeQtJx5zeu0M5tttpaAibLF7MVrazaV2B6Q8IlI8WA13USwhPOeIlcOUX0zmw7TYCJtfuDf3ybKaxIMgWLFUt2Gcb2r/MT6kT49LdLOhKkfkonxSZflmcLEJNIb/K8/n6ERimFsO2L0tI2Eqh6YNUpyNxLsJEkZm6DDeOvW0yZXqDNoymAwmG9bg7x2gA6i/E7e3UjODvWxmLfS6qvNkDs21OSTLjspvzjWPFkTdJx2DJu88xGHO7IUYUk6e8UPtzvVR/0J2JY1d9znMmYVdax/HBG0E7875UFMTlwZ/Yhxc0= ; sleep 1 ; echo 0 ) | pkginfo --setcert $PKG_NAME
    fi

    if [ -d $APPS_ROOT/org.tizen.messageportapp ]; then
	    ( echo 3 ; sleep 1 ; echo MIIClTCCAX2gAwIBAgIGAU1wuKP1MA0GCSqGSIb3DQEBBQUAMFYxGjAYBgNVBAoMEVRpemVuIEFzc29jaWF0aW9uMRowGAYDVQQLDBFUaXplbiBBc3NvY2lhdGlvbjEcMBoGA1UEAwwTVGl6ZW4gRGV2ZWxvcGVycyBDQTAeFw0xMjExMDEwMDAwMDBaFw0xOTAxMDEwMDAwMDBaMBExDzANBgNVBAMMBmF1dGhvcjCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAkzTMc+oxDLzYKi7TWoN8vMeMwLTdjxECyrdrv/8SJmqzvV4fYVUKx7kdRHCHazb1BGDxtgt4Ntilc+Qt5a42BNi19HTDpoWuga1fL7U3B/UNRmWjarHQQOLKcQ+2QD4vMjVpf4UOe8zE9ssCTKDNEw5ELV6XVwWoP9GYIXMug2UCAwEAAaMyMDAwDAYDVR0TAQH/BAIwADALBgNVHQ8EBAMCB4AwEwYDVR0lBAwwCgYIKwYBBQUHAwMwDQYJKoZIhvcNAQEFBQADggEBAMj0yAvusFduH+ABua+EijUBRzfhy68WaXOB7i4KfBYeQtJx5zeu0M5tttpaAibLF7MVrazaV2B6Q8IlI8WA13USwhPOeIlcOUX0zmw7TYCJtfuDf3ybKaxIMgWLFUt2Gcb2r/MT6kT49LdLOhKkfkonxSZflmcLEJNIb/K8/n6ERimFsO2L0tI2Eqh6YNUpyNxLsJEkZm6DDeOvW0yZXqDNoymAwmG9bg7x2gA6i/E7e3UjODvWxmLfS6qvNkDs21OSTLjspvzjWPFkTdJx2DJu88xGHO7IUYUk6e8UPtzvVR/0J2JY1d9znMmYVdax/HBG0E7875UFMTlwZ/Yhxc0= ; sleep 1 ; echo 0 ) | pkginfo --setcert org.tizen.messageportapp
    fi

    if [[ $PKG_NAME == *"application"* || $PKG_NAME == *"badge"* ]]; then
	    ( echo 3 ; sleep 1 ; echo MIIClTCCAX2gAwIBAgIGAU1wuKP1MA0GCSqGSIb3DQEBBQUAMFYxGjAYBgNVBAoMEVRpemVuIEFzc29jaWF0aW9uMRowGAYDVQQLDBFUaXplbiBBc3NvY2lhdGlvbjEcMBoGA1UEAwwTVGl6ZW4gRGV2ZWxvcGVycyBDQTAeFw0xMjExMDEwMDAwMDBaFw0xOTAxMDEwMDAwMDBaMBExDzANBgNVBAMMBmF1dGhvcjCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAkzTMc+oxDLzYKi7TWoN8vMeMwLTdjxECyrdrv/8SJmqzvV4fYVUKx7kdRHCHazb1BGDxtgt4Ntilc+Qt5a42BNi19HTDpoWuga1fL7U3B/UNRmWjarHQQOLKcQ+2QD4vMjVpf4UOe8zE9ssCTKDNEw5ELV6XVwWoP9GYIXMug2UCAwEAAaMyMDAwDAYDVR0TAQH/BAIwADALBgNVHQ8EBAMCB4AwEwYDVR0lBAwwCgYIKwYBBQUHAwMwDQYJKoZIhvcNAQEFBQADggEBAMj0yAvusFduH+ABua+EijUBRzfhy68WaXOB7i4KfBYeQtJx5zeu0M5tttpaAibLF7MVrazaV2B6Q8IlI8WA13USwhPOeIlcOUX0zmw7TYCJtfuDf3ybKaxIMgWLFUt2Gcb2r/MT6kT49LdLOhKkfkonxSZflmcLEJNIb/K8/n6ERimFsO2L0tI2Eqh6YNUpyNxLsJEkZm6DDeOvW0yZXqDNoymAwmG9bg7x2gA6i/E7e3UjODvWxmLfS6qvNkDs21OSTLjspvzjWPFkTdJx2DJu88xGHO7IUYUk6e8UPtzvVR/0J2JY1d9znMmYVdax/HBG0E7875UFMTlwZ/Yhxc0= ; sleep 1 ; echo 0 ) | pkginfo --setcert $PKG_NAME
    fi

    if [ -d $APPS_ROOT/org.tizen.badge_utc_app ]; then
	    ( echo 3 ; sleep 1 ; echo MIIClTCCAX2gAwIBAgIGAU1wuKP1MA0GCSqGSIb3DQEBBQUAMFYxGjAYBgNVBAoMEVRpemVuIEFzc29jaWF0aW9uMRowGAYDVQQLDBFUaXplbiBBc3NvY2lhdGlvbjEcMBoGA1UEAwwTVGl6ZW4gRGV2ZWxvcGVycyBDQTAeFw0xMjExMDEwMDAwMDBaFw0xOTAxMDEwMDAwMDBaMBExDzANBgNVBAMMBmF1dGhvcjCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAkzTMc+oxDLzYKi7TWoN8vMeMwLTdjxECyrdrv/8SJmqzvV4fYVUKx7kdRHCHazb1BGDxtgt4Ntilc+Qt5a42BNi19HTDpoWuga1fL7U3B/UNRmWjarHQQOLKcQ+2QD4vMjVpf4UOe8zE9ssCTKDNEw5ELV6XVwWoP9GYIXMug2UCAwEAAaMyMDAwDAYDVR0TAQH/BAIwADALBgNVHQ8EBAMCB4AwEwYDVR0lBAwwCgYIKwYBBQUHAwMwDQYJKoZIhvcNAQEFBQADggEBAMj0yAvusFduH+ABua+EijUBRzfhy68WaXOB7i4KfBYeQtJx5zeu0M5tttpaAibLF7MVrazaV2B6Q8IlI8WA13USwhPOeIlcOUX0zmw7TYCJtfuDf3ybKaxIMgWLFUt2Gcb2r/MT6kT49LdLOhKkfkonxSZflmcLEJNIb/K8/n6ERimFsO2L0tI2Eqh6YNUpyNxLsJEkZm6DDeOvW0yZXqDNoymAwmG9bg7x2gA6i/E7e3UjODvWxmLfS6qvNkDs21OSTLjspvzjWPFkTdJx2DJu88xGHO7IUYUk6e8UPtzvVR/0J2JY1d9znMmYVdax/HBG0E7875UFMTlwZ/Yhxc0= ; sleep 1 ; echo 0 ) | su -c "pkginfo --setcert org.tizen.badge_utc_app"
    fi

    if [ -d $APPS_ROOT/org.tizen.event_receiver ]; then
	    ( echo 3 ; sleep 1 ; echo MIIClTCCAX2gAwIBAgIGAU1wuKP1MA0GCSqGSIb3DQEBBQUAMFYxGjAYBgNVBAoMEVRpemVuIEFzc29jaWF0aW9uMRowGAYDVQQLDBFUaXplbiBBc3NvY2lhdGlvbjEcMBoGA1UEAwwTVGl6ZW4gRGV2ZWxvcGVycyBDQTAeFw0xMjExMDEwMDAwMDBaFw0xOTAxMDEwMDAwMDBaMBExDzANBgNVBAMMBmF1dGhvcjCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAkzTMc+oxDLzYKi7TWoN8vMeMwLTdjxECyrdrv/8SJmqzvV4fYVUKx7kdRHCHazb1BGDxtgt4Ntilc+Qt5a42BNi19HTDpoWuga1fL7U3B/UNRmWjarHQQOLKcQ+2QD4vMjVpf4UOe8zE9ssCTKDNEw5ELV6XVwWoP9GYIXMug2UCAwEAAaMyMDAwDAYDVR0TAQH/BAIwADALBgNVHQ8EBAMCB4AwEwYDVR0lBAwwCgYIKwYBBQUHAwMwDQYJKoZIhvcNAQEFBQADggEBAMj0yAvusFduH+ABua+EijUBRzfhy68WaXOB7i4KfBYeQtJx5zeu0M5tttpaAibLF7MVrazaV2B6Q8IlI8WA13USwhPOeIlcOUX0zmw7TYCJtfuDf3ybKaxIMgWLFUt2Gcb2r/MT6kT49LdLOhKkfkonxSZflmcLEJNIb/K8/n6ERimFsO2L0tI2Eqh6YNUpyNxLsJEkZm6DDeOvW0yZXqDNoymAwmG9bg7x2gA6i/E7e3UjODvWxmLfS6qvNkDs21OSTLjspvzjWPFkTdJx2DJu88xGHO7IUYUk6e8UPtzvVR/0J2JY1d9znMmYVdax/HBG0E7875UFMTlwZ/Yhxc0= ; sleep 1 ; echo 0 ) | su -c "pkginfo --setcert org.tizen.event_receiver"
    fi

    if [ -d $APPS_ROOT/org.example.invalidcertstub ]; then
	    ( echo 3 ; sleep 1 ; echo MIIClTCCAX2gAwIBAgIGAU1wuKP1MA0GCSqGSIb3DQEBBQUAMFYxGjAYBgNVBAoMEVRpemVuIEFzc29jaWF0aW9uMRowGAYDVQQLDBFUaXplbiBBc3NvY2lhdGlvbjEcMBoGA1UEAwwTVGl6ZW4gRGV2ZWxvcGVycyBDQTAeFw0xMjExMDEwMDAwMDBaFw0xOTAxMDEwMDAwMDBaMBExDzANBgNVBAMMBmF1dGhvcjCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAkzTMc+oxDLzYKi7TWoN8vMeMwLTdjxECyrdrv/8SJmqzvV4fYVUKx7kdRHCHazb1BGDxtgt4Ntilc+Qt5a42BNi19HTDpoWuga1fL7U3B/UNRmWjarHQQOLKcQ+2QD4vMjVpf4UOe8zE9ssCTKDNEw5ELV6XVwWoP9GYIXMug2UCAwEAAaMyMDAwDAYDVR0TAQH/BAIwADALBgNVHQ8EBAMCB4AwEwYDVR0lBAwwCgYIKwYBBQUHAwMwDQYJKoZIhvcNAQEFBQADggEBAMj0yAvusFduH+ABua+EijUBRzfhy68WaXOB7i4KfBYeQtJx5zeu0M5tttpaAibLF7MVrazaV2B6Q8IlI8WA13USwhPOeIlcOUX0zmw7TYCJtfuDf3ybKaxIMgWLFUt2Gcb2r/MT6kT49LdLOhKkfkonxSZflmcLEJNIb/K8/n6ERimFsO2L0tI2Eqh6YNUpyNxLsJEkZm6DDeOvW0yZXqDNoymAwmG9bg7x2gA6i/E7e3UjODvWxmLfS6qvNkDs21OSTLjspvzjWPFkTdJx2DJu88xGHO7IUYUk6e8UPtzvVR/0J2JY1d9znMmYVdax/HBG0E7875UFMTlwZ/Yhxc0= ; sleep 1 ; echo 0 ) | pkginfo --setcert org.example.invalidcertstub
    fi

}

function uninstallpkg(){
### remove source file ###

# terminate launched application
su -c "app_launcher -t $APP_ID > /dev/null" $DEVICE_EXECUTION_MODE_30

applist=`ls $DEVICE_SUITE_TARGET_30/res | grep -e tpk -e rpk | cut -d '-' -f1`
    echo "applist: ${applist}"
    for app in $applist
    do
	echo "- App: $app"
	if [ "$app" == "org.tizen.globalapp" ]; then
	    su -c "pkgcmd --global -u -n $app > /dev/null" $ADMIN_USER_30
	else
	    su -c "pkgcmd $GLOBAL_OPT -u -n $app > /dev/null" $DEVICE_EXECUTION_MODE_30
	fi
    done
    rm -rf $DEVICE_SUITE_TARGET_30/res

    if [ -d $DEVICE_PHYSICAL_STORAGE_30/TestFolder ]; then
	    rm -rf $DEVICE_PHYSICAL_STORAGE_30/TestFolder
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/TestImage.jpg ]; then
	    rm $DEVICE_PHYSICAL_STORAGE_30/TestImage.jpg
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/Remove.jpg ]; then
	    rm $DEVICE_PHYSICAL_STORAGE_30/Remove.jpg
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/Images/TestImage.jpg ]; then
	    rm $DEVICE_PHYSICAL_STORAGE_30/Images/TestImage.jpg
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/TestAudio.mp3 ]; then
	    rm $DEVICE_PHYSICAL_STORAGE_30/TestAudio.mp3
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/Images/BookMarkImage.jpg ]; then
	    rm $DEVICE_PHYSICAL_STORAGE_30/Images/BookMarkImage.jpg
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/Images/ThumbNailImage.jpg ]; then
	    rm $DEVICE_PHYSICAL_STORAGE_30/Images/ThumbNailImage.jpg
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/Images/BurstImage1.jpg ]; then
	    rm $DEVICE_PHYSICAL_STORAGE_30/Images/BurstImage1.jpg
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/Images/BurstImage2.jpg ]; then
	    rm $DEVICE_PHYSICAL_STORAGE_30/Images/BurstImage2.jpg
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/Images/BurstImage3.jpg ]; then
	    rm $DEVICE_PHYSICAL_STORAGE_30/Images/BurstImage3.jpg
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/Images/BurstImage4.jpg ]; then
	    rm $DEVICE_PHYSICAL_STORAGE_30/Images/BurstImage4.jpg
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/Videos/TestVideo.mp4 ]; then
	    rm $DEVICE_PHYSICAL_STORAGE_30/Videos/TestVideo.mp4
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/Music/TestAudio.mp3 ]; then
	    rm $DEVICE_PHYSICAL_STORAGE_30/Music/TestAudio.mp3
    fi
    if [ -d $DEVICE_PHYSICAL_STORAGE_30/Music/res ]; then
            rm -rf $DEVICE_PHYSICAL_STORAGE_30/Music/res
    fi
    if [ -d $DEVICE_PHYSICAL_STORAGE_30/Videos/res ]; then
            rm -rf $DEVICE_PHYSICAL_STORAGE_30/Videos/res
    fi
    if [ -d $DEVICE_PHYSICAL_STORAGE_30/Images/res ]; then
            rm -rf $DEVICE_PHYSICAL_STORAGE_30/Images/res
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/TestText.txt ]; then
            rm -f $DEVICE_PHYSICAL_STORAGE_30/TestText.txt
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/itc_test.pdf ]; then
            rm -f $DEVICE_PHYSICAL_STORAGE_30/itc_test.pdf
    fi
    if [ -f $DEVICE_PHYSICAL_STORAGE_30/itc_test.epub ]; then
            rm -f $DEVICE_PHYSICAL_STORAGE_30/itc_test.epub
    fi
    if [ -d $DEVICE_PHYSICAL_STORAGE_30/Text ]; then
            rm -rf $DEVICE_PHYSICAL_STORAGE_30/Text
    fi
    if [ -d $DEVICE_PHYSICAL_STORAGE_30/res ]; then
	    rm -rf $DEVICE_PHYSICAL_STORAGE_30/res
    fi
    if [ -d $DEVICE_PHYSICAL_STORAGE_30/P1 ]; then
	    rm -rf $DEVICE_PHYSICAL_STORAGE_30/P1
    fi
    if [ -d $DEVICE_PHYSICAL_STORAGE_30/data ]; then
	    rm -rf $DEVICE_PHYSICAL_STORAGE_30/data
    fi
    if [ -d $DEVICE_PHYSICAL_STORAGE_30/model ]; then
	    rm -rf $DEVICE_PHYSICAL_STORAGE_30/model
    fi
    ############### DEVICE_EXTERNAL_STORAGE related CHANGES ##########################
    if [ -d $DEVICE_EXTERNAL_STORAGE_30/TestFolder ]; then
	    rm -rf $DEVICE_EXTERNAL_STORAGE_30/TestFolder
    fi

    if [ -d $DEVICE_SUITE_TARGET_30/tct/opt/$NAME ];then
	    rm -rf $DEVICE_SUITE_TARGET_30/tct/opt/$NAME
	    su -c "pkgcmd $GLOBAL_OPT -u -n $PKG_NAME" $DEVICE_EXECUTION_MODE_30

	    if [ -d $APPS_ROOT/$PKG_NAME ];then
		    rm -rf $APPS_ROOT/$PKG_NAME
	    fi

	    if [ -d $DEVICE_SUITE_TARGET_30/Images/test ];then
		    rm -rf $DEVICE_SUITE_TARGET_30/Images/test*
	    fi
    else
	    echo "Remove source file fail, please check if the source file exist: $DEVICE_SUITE_TARGET_30/tct/opt/$NAME ..."
    fi
}

 case "$1" in
     -h|--help) echo "$USAGE"
                exit ;;
     ""|-i) installpkg $2;;
     -u) uninstallpkg;;
     *) echo "Unknown option: $1"
        echo "$USAGE"
        exit ;;
 esac
