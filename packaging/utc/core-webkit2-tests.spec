%define MODULE_NAME webkit2
%define MODULE_LIBNAME chromium-efl
Name:       core-%{MODULE_NAME}-tests
Summary:    Core API unit TC (%{name})
Version:    0.1
Release:    0
Group:      Development/Tools
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:	pkgconfig(%{MODULE_LIBNAME})
BuildRequires:	pkgconfig(evas)
BuildRequires:	pkgconfig(ecore)
BuildRequires:	pkgconfig(ecore-evas)
BuildRequires:	pkgconfig(edje)
BuildRequires:	pkgconfig(eina)
BuildRequires:	pkgconfig(elementary)
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	pkgconfig(gobject-2.0)
BuildRequires:	cmake
BuildRequires:	pkgconfig(capi-appfw-application)
BuildRequires:	pkgconfig(dlog)
BuildRequires:	pkgconfig(capi-system-info)
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	pkgconfig(storage)

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

mkdir -p %{buildroot}/usr/apps/%{name}/data
mkdir -p %{buildroot}/usr/apps/%{name}/data/res
mkdir -p %{buildroot}/usr/apps/%{name}/data/res/common
mkdir -p %{buildroot}/usr/apps/%{name}/data/res/ewk_context
mkdir -p %{buildroot}/usr/apps/%{name}/data/res/ewk_context_menu
mkdir -p %{buildroot}/usr/apps/%{name}/data/res/ewk_view
cp src/utc/webkit2/res/common/* %{buildroot}/usr/apps/%{name}/data/res/common/
cp src/utc/webkit2/res/ewk_context/* %{buildroot}/usr/apps/%{name}/data/res/ewk_context/
cp src/utc/webkit2/res/ewk_context_menu/* %{buildroot}/usr/apps/%{name}/data/res/ewk_context_menu/
cp src/utc/webkit2/res/ewk_view/* %{buildroot}/usr/apps/%{name}/data/res/ewk_view/

mkdir -p %{buildroot}/usr/share/packages/
cp packaging/utc/%{name}.xml %{buildroot}/usr/share/packages/
mkdir -p %{buildroot}/usr/apps/%{name}/bin
#cp templates/external_wrapper.sh %{buildroot}/usr/apps/%{name}/bin

%post

%postun

%files
/usr/apps/%{name}/*
/usr/share/packages/%{name}.xml
/usr/share/license/%{name}
