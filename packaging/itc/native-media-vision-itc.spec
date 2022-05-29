%define MODULE_NAME media-vision
%define MODULE_LIBNAME capi-media-vision
Name:       native-%{MODULE_NAME}-itc
Summary:    Native API Integration TC (%{name})
Version:    0.1
Release:    0
Group:      Development/Tools
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:	pkgconfig(%{MODULE_LIBNAME})
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	cmake
BuildRequires:	pkgconfig(capi-appfw-application)
BuildRequires:	pkgconfig(elementary)
BuildRequires:  pkgconfig(bundle)
BuildRequires:  pkgconfig(storage)
BuildRequires:  pkgconfig(capi-media-tool)
BuildRequires:  pkgconfig(libtbm)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  zint
BuildRequires:  zint-devel
BuildRequires:  zbar
BuildRequires:  pkgconfig(capi-system-info)
BuildRequires:  pkgconfig(capi-media-image-util)

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
mkdir -p %{buildroot}%{APP_PATH}%{name}/data
mkdir -p %{buildroot}%{APP_PATH}%{name}/data/tmp
mkdir -p %{buildroot}%{APP_PATH}%{name}/data/P1

cp src/itc/media-vision/P1/09.jpg %{buildroot}%{APP_PATH}%{name}/data/P1

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/track/sequence
%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
cp src/itc/media-vision/res/mobile/track/sequence/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/track/sequence/
%endif

%if %{?DEVICE_BUILD_TYPE_WEARABLE:1}0
cp src/itc/media-vision/res/wearable/track/sequence/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/track/sequence/
%endif

%if %{?DEVICE_BUILD_TYPE_TV:1}0
cp src/itc/media-vision/res/tv/track/sequence/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/track/sequence/
%endif

%if %{?DEVICE_BUILD_TYPE_TIZENIOT:1}0
cp src/itc/media-vision/res/tizeniot/track/sequence/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/track/sequence/
%endif

cp src/itc/media-vision/test_rec_model %{buildroot}%{APP_PATH}%{name}/data/test_rec_model
cp src/itc/media-vision/test_trk_model %{buildroot}%{APP_PATH}%{name}/data/test_trk_model
cp src/itc/media-vision/00.jpg %{buildroot}%{APP_PATH}%{name}/data/tmp/00.jpg
cp src/itc/media-vision/09.jpg %{buildroot}%{APP_PATH}%{name}/data/tmp/09.jpg
cp src/itc/media-vision/09.jpg %{buildroot}%{APP_PATH}%{name}/data/tmp/04.jpg
cp src/itc/media-vision/01.jpg %{buildroot}%{APP_PATH}%{name}/data/tmp/01.jpg
cp src/itc/media-vision/01.jpg %{buildroot}%{APP_PATH}%{name}/data/tmp/05.jpg
cp src/itc/media-vision/01.jpg %{buildroot}%{APP_PATH}%{name}/data/tmp/scene.jpg
cp src/itc/media-vision/01.jpg %{buildroot}%{APP_PATH}%{name}/data/tmp/target.jpg
cp src/itc/media-vision/01.jpg %{buildroot}%{APP_PATH}%{name}/data/tmp/neutral.jpg

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/inference/models
mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/inference/images
cp src/itc/media-vision/res/inference/models/* %{buildroot}%{APP_PATH}%{name}/data/res/inference/models/
cp src/itc/media-vision/res/inference/images/* %{buildroot}%{APP_PATH}%{name}/data/res/inference/images/

mkdir -p %{buildroot}/usr/share/packages/
cp packaging/itc/native-%{MODULE_NAME}-itc.xml %{buildroot}/usr/share/packages/
mkdir -p %{buildroot}%{APP_PATH}%{name}/bin

%post

%postun


%files
%{APP_PATH}%{name}/*
/usr/share/packages/native-%{MODULE_NAME}-itc.xml
/usr/share/license/%{name}
