%define MODULE_NAME player
%define MODULE_LIBNAME capi-media-player
Name:       native-%{MODULE_NAME}-itc
Summary:    Native API Integration TC (%{name})
Version:    0.1
Release:    0
Group:      Development/Tools
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:	pkgconfig(%{MODULE_LIBNAME})
BuildRequires:	pkgconfig(capi-appfw-application)
BuildRequires:	cmake
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	pkgconfig(gobject-2.0)
BuildRequires:	pkgconfig(bundle)
BuildRequires:	pkgconfig(appcore-efl)
BuildRequires:	pkgconfig(capi-system-info)
BuildRequires:	pkgconfig(dlog)
BuildRequires:	pkgconfig(capi-network-connection)
BuildRequires:	pkgconfig(libcurl)

%description
Native API Integration TC (%{name})

%prep
%setup -q

%build

%define PREFIX "%{_libdir}/%{name}"

export LDFLAGS+="-Wl,--rpath=%{PREFIX} -Wl,--as-needed"

%if %{?ASAN_BUILD:1}0
	%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="itc" -DDEVICE_BUILD_TYPE="mobile" -DASANBUILD="true" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_WEARABLE:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="itc" -DDEVICE_BUILD_TYPE="wearable" -DASANBUILD="true" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_TV:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="itc" -DDEVICE_BUILD_TYPE="tv" -DASANBUILD="true" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_TIZENIOT:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="itc" -DDEVICE_BUILD_TYPE="tizeniot" -DASANBUILD="true" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
%else
	%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="itc" -DDEVICE_BUILD_TYPE="mobile" -DASANBUILD="false" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_WEARABLE:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="itc" -DDEVICE_BUILD_TYPE="wearable" -DASANBUILD="false" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_TV:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="itc" -DDEVICE_BUILD_TYPE="tv" -DASANBUILD="false" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_TIZENIOT:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="itc" -DDEVICE_BUILD_TYPE="tizeniot" -DASANBUILD="false" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
%endif

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install
mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}
mkdir -p %{buildroot}%{APP_PATH}%{name}/data/
cp src/itc/player/short.mp3 %{buildroot}%{APP_PATH}%{name}/data/short.mp3
cp src/itc/player/file.mp4 %{buildroot}%{APP_PATH}%{name}/data/file.mp4
cp src/itc/player/sub.srt %{buildroot}%{APP_PATH}%{name}/data/sub.srt
cp src/itc/player/v.mp4 %{buildroot}%{APP_PATH}%{name}/data/v.mp4
cp src/itc/player/test.h264 %{buildroot}%{APP_PATH}%{name}/data/test.h264
cp src/itc/player/AWB_header_change_AMR.amr %{buildroot}%{APP_PATH}%{name}/data/AWB_header_change_AMR.amr

mkdir -p %{buildroot}/usr/share/packages/
cp packaging/itc/native-%{MODULE_NAME}-itc.xml %{buildroot}/usr/share/packages/
mkdir -p %{buildroot}%{APP_PATH}%{name}/bin
#cp templates/external_wrapper.sh %{buildroot}%{APP_PATH}%{name}/bin

%post
chown -R 5000:5000 %{APP_PATH}%{name}/data
chsmack -a %{name} %{APP_PATH}%{name}/data
%postun


%files
%{APP_PATH}%{name}/*
/usr/share/packages/native-%{MODULE_NAME}-itc.xml
/usr/share/license/%{name}
