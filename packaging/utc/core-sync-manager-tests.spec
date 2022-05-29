%define MODULE_NAME sync-manager
%define MODULE_LIBNAME core-sync-client
Name:       core-%{MODULE_NAME}-tests
Summary:    Core API unit TC (%{name})
Version:    0.1
Release:    0
Group:      Development/Tools
License:    Apache License, Version 2.0, Samsung Properietary
Source0:    %{name}-%{version}.tar.gz
BuildRequires:	cmake
BuildRequires:	pkgconfig(capi-appfw-application)
BuildRequires:	pkgconfig(dlog)
BuildRequires:	pkgconfig(elementary)
BuildRequires:	pkgconfig(capi-system-info)
BuildRequires:	pkgconfig(%{MODULE_LIBNAME})
BuildRequires:	pkgconfig(accounts-svc)
BuildRequires:	pkgconfig(bundle)
BuildRequires:	pkgconfig(capi-appfw-package-manager)
BuildRequires:	pkgconfig(capi-base-common)
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	pkgconfig(json-glib-1.0)

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
mkdir -p %{buildroot}/tmp/
mkdir -p %{buildroot}/usr/share/packages/
cp packaging/utc/%{name}.xml %{buildroot}/usr/share/packages/
mkdir -p %{buildroot}/usr/apps/%{name}/bin
#cp templates/external_wrapper.sh %{buildroot}/usr/apps/%{name}/bin
mkdir -p %{buildroot}/usr/apps/%{name}/shared
mkdir -p %{buildroot}/usr/apps/%{name}/shared/res
cp src/utc/sync-manager/sync.png %{buildroot}/usr/apps/%{name}/shared/res
cp src/utc/sync-manager/sync_small.png %{buildroot}/usr/apps/%{name}/shared/res
%post

%postun


%files
/usr/apps/%{name}/*
/usr/share/packages/%{name}.xml
/usr/share/license/%{name}
