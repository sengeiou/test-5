%define MODULE_NAME platform-permission
%define MODULE_LIBNAME capi-media-camera
Name:       native-%{MODULE_NAME}-ctc
Summary:    Native API Compatibility Test (%{name})
Version:    0.1
Release:    0
Group:      Development/Tools
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:	pkgconfig(%{MODULE_LIBNAME})
BuildRequires:	pkgconfig(capi-appfw-application)
BuildRequires:	pkgconfig(elementary)
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	pkgconfig(dlog)
BuildRequires:	pkgconfig(sqlite3)
BuildRequires:	pkgconfig(db-util)
BuildRequires:	pkgconfig(deviced)
BuildRequires:	pkgconfig(appcore-common)
BuildRequires:	pkgconfig(appcore-efl)
BuildRequires:	pkgconfig(pkgmgr-info)
BuildRequires:	pkgconfig(appsvc)
BuildRequires:	pkgconfig(alarm-service)
BuildRequires:	pkgconfig(capi-base-common)
BuildRequires:	pkgconfig(libsmack)
BuildRequires:	pkgconfig(capi-network-connection)
BuildRequires:	pkgconfig(capi-content-media-content)
BuildRequires:	pkgconfig(capi-system-info)
BuildRequires:	pkgconfig(capi-system-runtime-info)
BuildRequires:	pkgconfig(capi-location-manager)
BuildRequires:	pkgconfig(capi-network-bluetooth)
BuildRequires:	pkgconfig(tapi)
BuildRequires:	pkgconfig(capi-web-url-download)
BuildRequires:	pkgconfig(capi-system-device)
BuildRequires:	pkgconfig(capi-telephony)
BuildRequires:	pkgconfig(capi-media-recorder)
BuildRequires:	pkgconfig(capi-appfw-package-manager)
BuildRequires:	pkgconfig(capi-appfw-app-manager)
BuildRequires:	pkgconfig(capi-system-system-settings)
BuildRequires:	pkgconfig(capi-media-sound-manager)
BuildRequires:	pkgconfig(push)
BuildRequires:	pkgconfig(ecore)
BuildRequires:	pkgconfig(ecore-evas)
BuildRequires:	pkgconfig(notification)
BuildRequires:	pkgconfig(capi-media-player)
BuildRequires:	pkgconfig(capi-system-sensor)
BuildRequires:	pkgconfig(accounts-svc)
BuildRequires:	pkgconfig(capi-media-wav-player)
BuildRequires:	pkgconfig(capi-network-wifi-direct)
BuildRequires:	pkgconfig(bundle)
BuildRequires:	pkgconfig(appcore-efl)
BuildRequires:	pkgconfig(evas)
BuildRequires:	pkgconfig(capi-data-control)
BuildRequires:	pkgconfig(capi-message-port)
BuildRequires:	pkgconfig(capi-media-audio-io)
BuildRequires:	pkgconfig(capi-appfw-app-control)
BuildRequires:	pkgconfig(capi-network-nfc)
BuildRequires:	pkgconfig(badge)
BuildRequires:	pkgconfig(storage)
BuildRequires:	pkgconfig(capi-network-smartcard)
BuildRequires:	pkgconfig(capi-maps-service)
BuildRequires:	pkgconfig(capi-media-controller)
BuildRequires:	pkgconfig(elementary)
BuildRequires:	pkgconfig(widget_viewer_evas)
BuildRequires:	pkgconfig(widget_service)
BuildRequires:	pkgconfig(dbus-glib-1)
BuildRequires:	pkgconfig(capi-base-common)
BuildRequires:	pkgconfig(capi-system-runtime-info)
BuildRequires:	pkgconfig(capi-ui-inputmethod-manager)
BuildRequires:	pkgconfig(capi-ui-inputmethod)
BuildRequires:	pkgconfig(capi-ui-efl-util)
BuildRequires:	pkgconfig(stt)
BuildRequires:	cmake
BuildRequires:	pkgconfig(capi-network-http)
BuildRequires: pkgconfig(capi-media-streamer)
BuildRequires:  pkgconfig(capi-network-wifi-manager)
BuildRequires:  pkgconfig(capi-appfw-alarm)


%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
BuildRequires: 	pkgconfig(capi-messaging-email)
BuildRequires:  pkgconfig(contacts-service2)
BuildRequires:  pkgconfig(calendar-service2)
BuildRequires:	pkgconfig(capi-messaging-messages)
BuildRequires:	pkgconfig(context)
BuildRequires:	pkgconfig(minicontrol-viewer)
BuildRequires:	pkgconfig(minicontrol-provider)
BuildRequires:	pkgconfig(minicontrol-monitor)
BuildRequires:	pkgconfig(shortcut)
BuildRequires:	pkgconfig(core-sync-client)
BuildRequires:	pkgconfig(efl-extension)
BuildRequires:	pkgconfig(capi-geofence-manager)
BuildRequires:	pkgconfig(feedback)
BuildRequires:	pkgconfig(capi-media-thumbnail-util)
BuildRequires:	pkgconfig(voice-control)
BuildRequires:	pkgconfig(key-manager)
BuildRequires:	pkgconfig(voice-control-elm)
BuildRequires:	pkgconfig(attach-panel)
BuildRequires:	pkgconfig(oauth2)
BuildRequires:	pkgconfig(libcurl)
BuildRequires:	pkgconfig(capi-vpnsvc)
BuildRequires:	pkgconfig(iotcon)
BuildRequires: pkgconfig(phonenumber-utils)
BuildRequires: pkgconfig(capi-network-http)
%endif

%if %{?DEVICE_BUILD_TYPE_WEARABLE:1}0
BuildRequires:	pkgconfig(capi-messaging-messages)
%endif

%description
Core API Compatibility Test (%{name})

%prep
%setup -q

%build

%define PREFIX "%{_libdir}/%{name}"

export LDFLAGS+="-Wl,--rpath=%{PREFIX} -Wl,--as-needed"

%if %{?ASAN_BUILD:1}0
	%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="ctc" -DDEVICE_BUILD_TYPE="mobile" -DASANBUILD="true" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_WEARABLE:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="ctc" -DDEVICE_BUILD_TYPE="wearable" -DASANBUILD="true" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_TV:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="ctc" -DDEVICE_BUILD_TYPE="tv" -DASANBUILD="true" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_TIZENIOT:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="ctc" -DDEVICE_BUILD_TYPE="tizeniot" -DASANBUILD="true" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
%else
	%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="ctc" -DDEVICE_BUILD_TYPE="mobile" -DASANBUILD="false" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_WEARABLE:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="ctc" -DDEVICE_BUILD_TYPE="wearable" -DASANBUILD="false" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_TV:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="ctc" -DDEVICE_BUILD_TYPE="tv" -DASANBUILD="false" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_TIZENIOT:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="ctc" -DDEVICE_BUILD_TYPE="tizeniot" -DASANBUILD="false" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
%endif

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install
mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}
mkdir -p %{buildroot}/tmp/

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/
cp %{_builddir}/%{name}-%{version}/src/ctc/%{MODULE_NAME}/native-platform-permission-ctc-0.1-0.armv7l.rpm %{buildroot}%{APP_PATH}%{name}/data/native-platform-permission-ctc-0.1-0.armv7l.rpm
cp %{_builddir}/%{name}-%{version}/src/ctc/%{MODULE_NAME}/native-platform-permission-ctc-0.1-0.aarch64.rpm %{buildroot}%{APP_PATH}%{name}/data/native-platform-permission-ctc-0.1-0.aarch64.rpm

mkdir -p %{buildroot}/usr/share/packages/
cp packaging/ctc/native-%{MODULE_NAME}-ctc.xml %{buildroot}/usr/share/packages/
mkdir -p %{buildroot}%{APP_PATH}/%{name}/bin

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/Videos
mkdir -p %{buildroot}%{APP_PATH}%{name}/data/Music
mkdir -p %{buildroot}%{APP_PATH}%{name}/data/Images

mkdir -p %{buildroot}%{APP_PATH}%{name}/res
cp -r src/ctc/platform-permission/res/* %{buildroot}%{APP_PATH}%{name}/res

%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
cp src/ctc/%{MODULE_NAME}/PlatformPermission_test.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/PlatformPermission_test.jpg
cp src/ctc/%{MODULE_NAME}/res/mobile/TestImage.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/TestImage.jpg
cp src/ctc/%{MODULE_NAME}/res/mobile/BurstImage1.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/BurstImage1.jpg
cp src/ctc/%{MODULE_NAME}/res/mobile/BurstImage2.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/BurstImage2.jpg
cp src/ctc/%{MODULE_NAME}/res/mobile/BurstImage3.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/BurstImage3.jpg
cp src/ctc/%{MODULE_NAME}/res/mobile/BurstImage4.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/BurstImage4.jpg
cp src/ctc/%{MODULE_NAME}/res/mobile/BookMarkImage.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/BookMarkImage.jpg
cp src/ctc/%{MODULE_NAME}/res/mobile/TestVideo.mp4 %{buildroot}%{APP_PATH}%{name}/data/Videos/TestVideo.mp4
cp src/ctc/%{MODULE_NAME}/res/mobile/TestAudio.mp3 %{buildroot}%{APP_PATH}%{name}/data/Music/TestAudio.mp3
%endif

%if %{?DEVICE_BUILD_TYPE_WEARABLE:1}0
cp src/ctc/%{MODULE_NAME}/PlatformPermission_test.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/PlatformPermission_test.jpg
cp src/ctc/%{MODULE_NAME}/res/wearable/TestImage.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/TestImage.jpg
cp src/ctc/%{MODULE_NAME}/res/wearable/BookMarkImage.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/BookMarkImage.jpg
cp src/ctc/%{MODULE_NAME}/res/wearable/BurstImage1.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/BurstImage1.jpg
cp src/ctc/%{MODULE_NAME}/res/wearable/BurstImage2.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/BurstImage2.jpg
cp src/ctc/%{MODULE_NAME}/res/wearable/BurstImage3.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/BurstImage3.jpg
cp src/ctc/%{MODULE_NAME}/res/wearable/BurstImage4.jpg %{buildroot}%{APP_PATH}%{name}/data/Images/BurstImage4.jpg
cp src/ctc/%{MODULE_NAME}/res/wearable/TestVideo.mp4 %{buildroot}%{APP_PATH}%{name}/data/Videos/TestVideo.mp4
cp src/ctc/%{MODULE_NAME}/res/wearable/TestAudio.mp3 %{buildroot}%{APP_PATH}%{name}/data/Music/TestAudio.mp3
%endif

%pre

%post

%postun

%files
%{APP_PATH}%{name}/*
/usr/share/packages/native-%{MODULE_NAME}-ctc.xml
/usr/share/license/%{name}
