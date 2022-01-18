Name:       capi-base-common
Summary:    Common header files of Tizen Native API
Version:    0.4.66
Release:    1
Group:      Base
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz

BuildRequires: cmake
%if 0%{?gcov:1}
BuildRequires: lcov
%endif

Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
Common header files of Tizen Native API

%package devel
License:  Apache-2.0
Summary:  Common header files of Tizen Native API (Development)
Group:    Base
Requires: %{name} = %{version}-%{release}

%description devel
Common header files of Tizen Native API

%if 0%{?gcov:1}
%package gcov
Summary:    Common header files of Tizen Native API (gcov)
Group:      Base
%description gcov
Common header files of Tizen Native API gcov objects
%endif

%prep
%setup -q

%build
%if 0%{?gcov:1}
export CFLAGS+=" -fprofile-arcs -ftest-coverage"
export CXXFLAGS+=" -fprofile-arcs -ftest-coverage"
export FFLAGS+=" -fprofile-arcs -ftest-coverage"
export LDFLAGS+=" -lgcov"
%endif

MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`

cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix} -DLIB_INSTALL_DIR:PATH=%{_libdir} -DINCLUDE_INSTALL_DIR:PATH=%{_includedir} \
-DFULLVER=%{version} -DMAJORVER=${MAJORVER}

make %{?jobs:-j%jobs}

%if 0%{?gcov:1}
mkdir -p gcov-obj
find . -name '*.gcno' -exec cp '{}' gcov-obj ';'
%endif

%install
rm -rf %{buildroot}
%make_install

%if 0%{?gcov:1}
mkdir -p %{buildroot}%{_datadir}/gcov/obj
install -m 0644 gcov-obj/* %{buildroot}%{_datadir}/gcov/obj
%endif

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest %{name}.manifest
%{_libdir}/libcapi-base-common.so.*
%license LICENSE

%files devel
%{_includedir}/*.h
%{_libdir}/pkgconfig/capi-base-common.pc
%{_libdir}/libcapi-base-common.so

%if 0%{?gcov:1}
%files gcov
%{_datadir}/gcov/obj/*
%endif
