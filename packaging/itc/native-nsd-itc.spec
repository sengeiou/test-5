%define MODULE_NAME nsd
%define MODULE_LIBNAME_SSDP nsd-ssdp
%define MODULE_LIBNAME_DNS_SD nsd-dns-sd

Name:       native-%{MODULE_NAME}-itc
Summary:    Native API Integration TC (%{name})
Version:    0.1
Release:    0
Group:      Development/Tools
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz

BuildRequires:	pkgconfig(%{MODULE_LIBNAME_DNS_SD})
BuildRequires:	pkgconfig(%{MODULE_LIBNAME_SSDP})
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	cmake
BuildRequires:	pkgconfig(capi-appfw-application)
BuildRequires:	pkgconfig(elementary)
BuildRequires:	pkgconfig(dlog)
BuildRequires:	pkgconfig(capi-system-info)
BuildRequires:	pkgconfig(bundle)

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
cp packaging/itc/native-%{MODULE_NAME}-itc.xml %{buildroot}/usr/share/packages/
mkdir -p %{buildroot}%{APP_PATH}%{name}/bin
#cp templates/external_wrapper.sh %{buildroot}%{APP_PATH}%{name}/bin
%post

%postun


%files
%{APP_PATH}%{name}/*
/usr/share/packages/native-%{MODULE_NAME}-itc.xml
/usr/share/license/%{name}