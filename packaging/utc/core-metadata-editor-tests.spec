%define MODULE_NAME metadata-editor
%define MODULE_LIBNAME capi-media-metadata-editor
Name:       core-%{MODULE_NAME}-tests
Summary:    Core API unit TC (%{name})
Version:    0.1
Release:    0
Group:      Development/Tools
License:    Apache License, Version 2.0, Samsung Properietary
Source0:    %{name}-%{version}.tar.gz
BuildRequires:	pkgconfig(%{MODULE_LIBNAME})
BuildRequires:	cmake
BuildRequires:	pkgconfig(capi-appfw-application)
BuildRequires:	pkgconfig(dlog)
BuildRequires:	pkgconfig(elementary)
BuildRequires:	pkgconfig(capi-system-info)
BuildRequires:	pkgconfig(bundle)
BuildRequires:	pkgconfig(taglib)
BuildRequires:  pkgconfig(storage)

%description
Core API unit TC (%{name})

%prep
%setup -q

%build

%define PREFIX "%{_libdir}/%{name}"

export LDFLAGS+="-Wl,--rpath=%{PREFIX} -Wl,--as-needed"

%if %{?ASAN_BUILD:1}0
	%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="utc" -DDEVICE_BUILD_TYPE="mobile" -DASANBUILD="true" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_WEARABLE:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="utc" -DDEVICE_BUILD_TYPE="wearable" -DASANBUILD="true" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_TV:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="utc" -DDEVICE_BUILD_TYPE="tv" -DASANBUILD="true" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_TIZENIOT:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="utc" -DDEVICE_BUILD_TYPE="tizeniot" -DASANBUILD="true" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
%else
	%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="utc" -DDEVICE_BUILD_TYPE="mobile" -DASANBUILD="false" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_WEARABLE:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="utc" -DDEVICE_BUILD_TYPE="wearable" -DASANBUILD="false" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_TV:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="utc" -DDEVICE_BUILD_TYPE="tv" -DASANBUILD="false" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
	%if %{?DEVICE_BUILD_TYPE_TIZENIOT:1}0
	cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="utc" -DDEVICE_BUILD_TYPE="tizeniot" -DASANBUILD="false" -DCMAKE_INSTALL_PREFIX=%{_prefix}
	%endif
%endif

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install
mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}
mkdir -p %{buildroot}/usr/share/packages/
cp packaging/utc/%{name}.xml %{buildroot}/usr/share/packages/

mkdir -p %{buildroot}%{APP_PATH}%{name}/data

%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
cp src/utc/metadata-editor/res/mobile/sample_audio.mp3 %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/mobile/sample.jpg %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/mobile/sample_video.mp4 %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/mobile/no_tag.mp3 %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/mobile/id3tag_v1.mp3 %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/mobile/sample_m4a.m4a %{buildroot}%{APP_PATH}%{name}/data/
%endif

%if %{?DEVICE_BUILD_TYPE_WEARABLE:1}0
cp src/utc/metadata-editor/res/wearable/sample_audio.mp3 %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/wearable/sample.jpg %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/wearable/sample_video.mp4 %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/wearable/no_tag.mp3 %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/wearable/id3tag_v1.mp3 %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/wearable/sample_m4a.m4a %{buildroot}%{APP_PATH}%{name}/data/
%endif

%if %{?DEVICE_BUILD_TYPE_TV:1}0
cp src/utc/metadata-editor/res/tv/sample_audio.mp3 %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/tv/sample.jpg %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/tv/sample_video.mp4 %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/tv/no_tag.mp3 %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/tv/id3tag_v1.mp3 %{buildroot}%{APP_PATH}%{name}/data/
cp src/utc/metadata-editor/res/tv/sample_m4a.m4a %{buildroot}%{APP_PATH}%{name}/data/
%endif

%post

%postun

%files
/usr/apps/%{name}/*
/usr/share/packages/%{name}.xml
/usr/share/license/%{name}
