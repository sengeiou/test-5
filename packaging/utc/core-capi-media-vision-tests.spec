%define MODULE_NAME capi-media-vision
%define MODULE_LIBNAME capi-media-vision
Name:       core-%{MODULE_NAME}-tests
Summary:    Core API unit TC (%{name})
Version:    0.1
Release:    0
Group:      Development/Tools
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:	pkgconfig(%{MODULE_LIBNAME})
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	cmake
BuildRequires:	pkgconfig(capi-appfw-application)
BuildRequires:	pkgconfig(elementary)
BuildRequires:  pkgconfig(bundle)
BuildRequires:  pkgconfig(storage)
BuildRequires:  pkgconfig(json-glib-1.0)
BuildRequires:  pkgconfig(capi-media-tool)
BuildRequires:  pkgconfig(libtbm)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(capi-media-image-util)
BuildRequires:  zint
BuildRequires:  zint-devel
BuildRequires:  zbar
BuildRequires:  pkgconfig(capi-system-info)

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

mkdir -p %{buildroot}%{APP_PATH}%{name}/bin

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/
mkdir -p %{buildroot}%{APP_PATH}%{name}/data/data
mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res
mkdir -p %{buildroot}%{APP_PATH}%{name}/data/model
cp src/utc/capi-media-vision/res/rec/test_rec_model %{buildroot}%{APP_PATH}%{name}/data/model
cp src/utc/capi-media-vision/res/track/test_trk_model %{buildroot}%{APP_PATH}%{name}/data/model

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/img
cp src/utc/capi-media-vision/res/media-vision-barcodes.json %{buildroot}%{APP_PATH}%{name}/data/res/
cp src/utc/capi-media-vision/res/img/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/img/
cp src/utc/capi-media-vision/res/img/*.raw %{buildroot}%{APP_PATH}%{name}/data/res/img/

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/rec/P1
mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/rec/P2
cp src/utc/capi-media-vision/res/rec/P1/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/rec/P1
cp src/utc/capi-media-vision/res/rec/P2/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/rec/P2

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/eye
cp src/utc/capi-media-vision/res/eye/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/eye/

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/expr
cp src/utc/capi-media-vision/res/expr/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/expr/

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/track/sequence
cp src/utc/capi-media-vision/res/track/sequence/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/track/sequence/

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/facedetect
cp src/utc/capi-media-vision/res/facedetect/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/facedetect/

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/image
cp src/utc/capi-media-vision/res/image/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/image/

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/image/tracking
cp src/utc/capi-media-vision/res/image/tracking/*.jpg %{buildroot}%{APP_PATH}%{name}/data/res/image/tracking/

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/surv
cp src/utc/capi-media-vision/res/surv/* %{buildroot}%{APP_PATH}%{name}/data/res/surv/

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/inference/models
mkdir -p %{buildroot}%{APP_PATH}%{name}/data/res/inference/images
cp src/utc/capi-media-vision/res/inference/models/* %{buildroot}%{APP_PATH}%{name}/data/res/inference/models/
cp src/utc/capi-media-vision/res/inference/images/* %{buildroot}%{APP_PATH}%{name}/data/res/inference/images/
%post

%postun


%files
%{APP_PATH}%{name}/*
/usr/share/packages/%{name}.xml
/usr/share/license/%{name}
