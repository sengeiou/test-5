%define MODULE_NAME thumbnail-util
%define MODULE_LIBNAME capi-media-thumbnail-util
Name:       native-%{MODULE_NAME}-itc
Summary:    Native API Integration TC (%{name})
Version:    0.1
Release:    0
Group:      Development/Tools
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:	pkgconfig(%{MODULE_LIBNAME})
BuildRequires:	pkgconfig(capi-appfw-application)
BuildRequires:	pkgconfig(elementary)
BuildRequires:	pkgconfig(dlog)
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	cmake
BuildRequires:	pkgconfig(bundle)
BuildRequires:	pkgconfig(capi-system-info)

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

mkdir -p %{buildroot}/usr/share/packages/
cp packaging/itc/%{name}.xml %{buildroot}/usr/share/packages/
mkdir -p %{buildroot}%{APP_PATH}%{name}/bin
#cp templates/external_wrapper.sh %{buildroot}%{APP_PATH}%{name}/bin

mkdir -p %{buildroot}%{APP_PATH}%{name}/data/

%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
cp src/itc/thumbnail-util/res/mobile/Sample_01.jpg %{buildroot}%{APP_PATH}%{name}/data/Sample_01.jpg
cp src/itc/thumbnail-util/res/mobile/Sample_02.jpg %{buildroot}%{APP_PATH}%{name}/data/Sample_02.jpg
%endif

%if %{?DEVICE_BUILD_TYPE_WEARABLE:1}0
cp src/itc/thumbnail-util/res/wearable/Sample_01.jpg %{buildroot}%{APP_PATH}%{name}/data/Sample_01.jpg
cp src/itc/thumbnail-util/res/wearable/Sample_02.jpg %{buildroot}%{APP_PATH}%{name}/data/Sample_02.jpg
%endif

%if %{?DEVICE_BUILD_TYPE_TV:1}0
cp src/itc/thumbnail-util/res/tv/Sample_01.jpg %{buildroot}%{APP_PATH}%{name}/data/Sample_01.jpg
cp src/itc/thumbnail-util/res/tv/Sample_02.jpg %{buildroot}%{APP_PATH}%{name}/data/Sample_02.jpg
%endif

%if %{?DEVICE_BUILD_TYPE_TIZENIOT:1}0
cp src/itc/thumbnail-util/res/tizeniot/Sample_01.jpg %{buildroot}%{APP_PATH}%{name}/data/Sample_01.jpg
cp src/itc/thumbnail-util/res/tizeniot/Sample_02.jpg %{buildroot}%{APP_PATH}%{name}/data/Sample_02.jpg
%endif

%post
%if %{?DEVICE_BUILD_TYPE_TV:1}0
chown -R 5000:5000 %{APP_PATH}%{name}/data
chsmack -a %{name} %{APP_PATH}%{name}/data
%endif

%postun


%files
%{APP_PATH}%{name}/*
/usr/share/packages/%{name}.xml
/usr/share/license/%{name}
