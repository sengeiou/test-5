%define MODULE_NAME key-manager
%define MODULE_LIBNAME key-manager
Name:       core-%{MODULE_NAME}-tests
Summary:    Core API unit TC (%{name})
Version:    0.1
Release:    0
Group:      Development/Tools
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:	pkgconfig(%{MODULE_LIBNAME})
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	pkgconfig(storage)
BuildRequires:	cmake
BuildRequires:	pkgconfig(capi-appfw-application)
BuildRequires:	pkgconfig(dlog)
BuildRequires:	pkgconfig(elementary)
BuildRequires:	pkgconfig(capi-system-info)

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
cp src/utc/key-manager/data/* %{buildroot}%{APP_PATH}%{name}/data/
mkdir -p %{buildroot}/etc/ssl/certs
cp src/utc/key-manager/data/dfb08fe4.0 %{buildroot}/etc/ssl/certs/

%post
chsmack -a "_" /etc/ssl/certs/dfb08fe4.0
chsmack -a "_" %{APP_PATH}%{name}/data

%files
%{APP_PATH}%{name}/*
/usr/share/packages/%{name}.xml
/usr/share/license/%{name}
/etc/ssl/certs/dfb08fe4.0
