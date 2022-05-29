%define MODULE_NAME usb-host
%define MODULE_LIBNAME capi-system-usbhost
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
BuildRequires:	pkgconfig(capi-system-info)
BuildRequires:	pkgconfig(dlog)

%description
Core API unit TC (%{name})

%prep
%setup -q

%build

%define PREFIX "%{_libdir}/%{name}"

export LDFLAGS+="-Wl,--rpath=%{PREFIX} -Wl,--as-needed"

%if %{?DEVICE_BUILD_TYPE_MOBILE:1}0
cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="utc" -DDEVICE_BUILD_TYPE="mobile" -DCMAKE_INSTALL_PREFIX=%{_prefix}
%endif

%if %{?DEVICE_BUILD_TYPE_WEARABLE:1}0
cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="utc" -DDEVICE_BUILD_TYPE="wearable" -DCMAKE_INSTALL_PREFIX=%{_prefix}
%endif

%if %{?DEVICE_BUILD_TYPE_TV:1}0
cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="utc" -DDEVICE_BUILD_TYPE="tv" -DCMAKE_INSTALL_PREFIX=%{_prefix}
%endif

%if %{?DEVICE_BUILD_TYPE_TIZENIOT:1}0
cmake . -DMODULE="%{MODULE_NAME}" -DBUILDTCTYPE="utc" -DDEVICE_BUILD_TYPE="tizeniot" -DCMAKE_INSTALL_PREFIX=%{_prefix}
%endif

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install
mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}
mkdir -p %{buildroot}/usr/share/packages/
cp packaging/utc/%{name}.xml %{buildroot}/usr/share/packages/
mkdir -p %{buildroot}/usr/apps/%{name}/bin
%post

%postun


%files
/usr/apps/%{name}/*
/usr/share/packages/%{name}.xml
/usr/share/license/%{name}
