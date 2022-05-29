%define MODULE_NAME metadata-editor
%define MODULE_LIBNAME capi-media-metadata-editor
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
BuildRequires:	pkgconfig(glib-2.0)
BuildRequires:	cmake
BuildRequires:	pkgconfig(dlog)
BuildRequires:	pkgconfig(capi-base-common)
BuildRequires:	pkgconfig(taglib)
BuildRequires:	pkgconfig(aul)
BuildRequires:	pkgconfig(capi-system-info)
BuildRequires:	pkgconfig(libcurl)

%description
Native API Integration TC (%{name})

p%prep
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
cp src/itc/metadata-editor/metadata_editor_video.MP4 %{buildroot}%{APP_PATH}%{name}/data/metadata_editor_video.MP4
cp src/itc/metadata-editor/metadata_editor_video2.MP4 %{buildroot}%{APP_PATH}%{name}/data/metadata_editor_video2.MP4
cp src/itc/metadata-editor/metadata_editor_audio.MP3 %{buildroot}%{APP_PATH}%{name}/data/metadata_editor_audio.MP3
cp src/itc/metadata-editor/metadata_editor_picture.JPG %{buildroot}%{APP_PATH}%{name}/data/metadata_editor_picture.JPG


mkdir -p %{buildroot}/usr/share/packages/
cp packaging/itc/native-%{MODULE_NAME}-itc.xml %{buildroot}/usr/share/packages/	
mkdir -p %{buildroot}%{APP_PATH}%{name}/bin
#cp templates/external_wrapper.sh %{buildroot}%{APP_PATH}%{name}/bin
%post
chown -R 5000:5000 %{APP_PATH}%{name}/data
chsmack -a %{name} %{APP_PATH}%{name}/data
chmod -R 777 %{APP_PATH}%{name}/data/
%postun


%files
%{APP_PATH}%{name}/*
/usr/share/packages/%{name}.xml
/usr/share/license/%{name}
