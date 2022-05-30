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
BUILD_TYPE=%{BUILD_TYPE} # directory supplied by external script
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
DEVICE_USER_30=`cat $TCT_CONFIG_FILE | grep DEVICE_USER_30 | cut -f 2- -d '='`
if [ $DEVICE_USER_30 == "" ]; then
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

TCT_DIR="opt/tct-$MOD_NAME-native-$BUILD_TYPE"
PKG_DIR=$DEVICE_SUITE_TARGET_30/tct/$TCT_DIR

echo "DEVICE_EXECUTION_MODE_30 = $DEVICE_EXECUTION_MODE_30"

if [[ $PKG_NAME == *"-itc" ]] ;then
	SUITENAME=$MOD_NAME-native
	APP_ID=native.${PKG_NAME#native-}
elif [[ $PKG_NAME == *"-ctc" ]]; then
	SUITENAME=$MOD_NAME-ctc
	APP_ID=native.${PKG_NAME#native-}
else
	SUITENAME=$MOD_NAME-core
	APP_ID=core.${PKG_NAME#core-}
fi

function installpkg(){
    if [ `date +%Y` -lt 2015 ]
    then
        date -s "1 JUL 2015 00:00:00"
    fi

    if [ ! -d $DEVICE_SUITE_TARGET_30/res/ ]; then
        mkdir $DEVICE_SUITE_TARGET_30/res
    fi
    cp -rf $PKG_DIR/res $DEVICE_SUITE_TARGET_30/
    find $DEVICE_SUITE_TARGET_30/res/ -exec chsmack -a "User::App::Shared" {} \;
    rpm -e `rpm -qa | grep $PKG_NAME`
    rpm -ih $PKG_DIR/$PKG_FULLNAME

   # pkginfo --imd /usr/share/packages/$PKG_NAME\.xml
   # pkg_privilege -i /usr/share/packages/$PKG_NAME\.xml
    tpk-backend --preload -y $PKG_NAME

	for i in `grep -r "0xA" /var/cynara/db/_ | grep $PKG_NAME`
	do
		CLIENT=`echo $i | cut -d ";" -f1`
		USER=`echo $i | cut -d ";" -f2`
		PRIVILEGE=`echo $i | cut -d ";" -f3`

		#echo "cyad --erase=\"\" -r=no -c $CLIENT -u $USER -p $PRIVILEGE"
		cyad --erase="" -r=no -c $CLIENT -u $USER -p $PRIVILEGE
	done

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
	    applist=`ls $DEVICE_SUITE_TARGET_30/res | grep tpk | grep arm`
    elif [ "$(echo $HOSTTYPE)" == "aarch64" ]; then
	    applist=`ls $DEVICE_SUITE_TARGET_30/res | grep tpk | grep aarch64`
	elif [ "$(echo $HOSTTYPE)" == "x86_64" ]; then
	    applist=`ls $DEVICE_SUITE_TARGET_30/res | grep tpk | grep x86_64`
    else
	    applist=`ls $DEVICE_SUITE_TARGET_30/res | grep tpk | grep -e i386 -e i586`
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
	    ( echo 3 ; sleep 1 ; echo MIIClTCCAX2gAwIBAgIGAU1wuKP1MA0GCSqGSIb3DQEBBQUAMFYxGjAYBgNVBAoMEVRpemVuIEFzc29jaWF0aW9uMRowGAYDVQQLDBFUaXplbiBBc3NvY2lhdGlvbjEcMBoGA1UEAwwTVGl6ZW4gRGV2ZWxvcGVycyBDQTAeFw0xMjExMDEwMDAwMDBaFw0xOTAxMDEwMDAwMDBaMBExDzANBgNVBAMMBmF1dGhvcjCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAkzTMc+oxDLzYKi7TWoN8vMeMwLTdjxECyrdrv/8SJmqzvV4fYVUKx7kdRHCHazb1BGDxtgt4Ntilc+Qt5a42BNi19HTDpoWuga1fL7U3B/UNRmWjarHQQOLKcQ+2QD4vMjVpf4UOe8zE9ssCTKDNEw5ELV6XVwWoP9GYIXMug2UCAwEAAaMyMDAwDAYDVR0TAQH/BAIwADALBgNVHQ8EBAMCB4AwEwYDVR0lBAwwCgYIKwYBBQUHAwMwDQYJKoZIhvcNAQEFBQADggEBAMj0yAvusFduH+ABua+EijUBRzfhy68WaXOB7i4KfBYeQtJx5zeu0M5tttpaAibLF7MVrazaV2B6Q8IlI8WA13USwhPOeIlcOUX0zmw7TYCJtfuDf3ybKaxIMgWLFUt2Gcb2r/MT6kT49LdLOhKkfkonxSZflmcLEJNIb/K8/n6ERimFsO2L0tI2Eqh6YNUpyNxLsJEkZm6DDeOvW0yZXqDNoymAwmG9bg7x2gA6i/E7e3UjODvWxmLfS6qvNkDs21OSTLjspvzjWPFkTdJx2DJu88xGHO7IUYUk6e8UPtzvVR/0J2JY1d9znMmYVdax/HBG0E7875UFMTlwZ/Yhxc0= ; sleep 1 ; echo 0 ) | su -c "pkginfo --setcert org.tizen.messageportapp"
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

}

function uninstallpkg(){
### remove source file ###

# terminate launched application
su -c "app_launcher -t $APP_ID > /dev/null" $DEVICE_EXECUTION_MODE_30

# remove files if any
if [ -e $PKG_DIR/post-inst.sh ];then
	WORKDIR=`pwd`
	cd $PKG_DIR
	sh ./post-inst.sh $PKG_NAME uninst
	cd $WORKDIR
fi

if [ -d $DEVICE_SUITE_TARGET_30/tct/opt/$NAME ];then
    rm -rf $DEVICE_SUITE_TARGET_30/tct/opt/$NAME
     tpk-backend -d $PKG_NAME --preload --force-remove
     rpm -e `rpm -qa | grep $PKG_NAME`
    if [ -d $DEVICE_SUITE_TARGET_30/Images/test ];then
        rm -rf $DEVICE_SUITE_TARGET_30/Images/test*
    fi
else
    echo "Remove source file fail, please check if the source file exist: $DEVICE_SUITE_TARGET_30/tct/opt/$NAME ..."
fi
    applist=`ls $DEVICE_SUITE_TARGET_30/res | grep tpk | awk -F'-' '{print $1}'`
    for app in $applist
    do
	if [ "$app" == "org.tizen.globalapp" ]; then
	    su -c "pkgcmd --global -u -n $app > /dev/null" $ADMIN_USER_30
	else
	    su -c "pkgcmd $GLOBAL_OPT -u -n $app > /dev/null" $DEVICE_EXECUTION_MODE_30
	fi
    done
    rm -rf $DEVICE_SUITE_TARGET_30/res
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
