%define MODULE_NAME sync-manager
%define MODULE_LIBNAME core-sync-client
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
BuildRequires:	pkgconfig(bundle)
BuildRequires:	pkgconfig(capi-system-info)
BuildRequires:	pkgconfig(capi-system-runtime-info)
BuildRequires:	pkgconfig(capi-system-device)
BuildRequires:	pkgconfig(capi-appfw-app-manager)
BuildRequires:	pkgconfig(capi-appfw-package-manager)
BuildRequires:	pkgconfig(capi-network-connection)
BuildRequires:	pkgconfig(appcore-efl)
BuildRequires:	pkgconfig(dlog)
BuildRequires:	pkgconfig(db-util)
BuildRequires:	pkgconfig(pkgmgr)
BuildRequires:	pkgconfig(pkgmgr-info)
BuildRequires:	pkgconfig(appsvc)
BuildRequires:	pkgconfig(vconf)
BuildRequires:	pkgconfig(vconf-internal-keys)
BuildRequires:	pkgconfig(libxml-2.0)
BuildRequires:	pkgconfig(glib-2.0) >=	2.26
BuildRequires:	pkgconfig(gio-unix-2.0)
BuildRequires:	pkgconfig(accounts-svc)
BuildRequires:	pkgconfig(alarm-service)
BuildRequires:	pkgconfig(bundle)
BuildRequires:	pkgconfig(elementary)
BuildRequires:	pkgconfig(ecore)

%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
BuildRequires:	pkgconfig(calendar-service2)
BuildRequires:	pkgconfig(contacts-service2)
%endif

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
%post

%postun


%files
%{APP_PATH}%{name}/*
/usr/share/packages/%{name}.xml
/usr/share/license/%{name}
