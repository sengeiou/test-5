SET(PKG_NAME "package-manager")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "capi-appfw-package-manager")
SET(TC_SOURCES
	utc-ApplicationFW-package-manager-common.c
	utc-ApplicationFW-package-info-clone.c
	utc-ApplicationFW-package-info-create.c
	utc-ApplicationFW-package-info-destroy.c
	utc-ApplicationFW-package-info-foreach-app-from-package.c
	utc-ApplicationFW-package-info-foreach-cert-info.c
	utc-ApplicationFW-package-info-foreach-dependency-info.c
	utc-ApplicationFW-package-info-foreach-dependency-info-depends-on.c
	utc-ApplicationFW-package-info-foreach-privilege-info.c
	utc-ApplicationFW-package-info-foreach-required-privilege.c
	utc-ApplicationFW-package-info-foreach-res-allowed-package.c
	utc-ApplicationFW-package-info-get-icon.c
	utc-ApplicationFW-package-info-get-installed-storage.c
	utc-ApplicationFW-package-info-get-installed-time.c
	utc-ApplicationFW-package-info-get-label.c
	utc-ApplicationFW-package-info-get-main-app-id.c
	utc-ApplicationFW-package-info-get-package.c
	utc-ApplicationFW-package-info-get-res-type.c
	utc-ApplicationFW-package-info-get-res-version.c
	utc-ApplicationFW-package-info-get-root-path.c
	utc-ApplicationFW-package-info-get-type.c
	utc-ApplicationFW-package-info-get-version.c
	utc-ApplicationFW-package-info-is-accessible.c
	utc-ApplicationFW-package-info-is-equal.c
	utc-ApplicationFW-package-info-is-preload-package.c
	utc-ApplicationFW-package-info-is-removable-package.c
	utc-ApplicationFW-package-info-is-system-package.c
	utc-ApplicationFW-package-manager-clear-cache-dir.c
	utc-ApplicationFW-package-manager-compare-app-cert-info.c
	utc-ApplicationFW-package-manager-compare-package-cert-info.c
	utc-ApplicationFW-package-manager-create.c
	utc-ApplicationFW-package-manager-destroy.c
	utc-ApplicationFW-package-manager-foreach-package-info.c
	utc-ApplicationFW-package-manager-get-package-id-by-app-id.c
	utc-ApplicationFW-package-manager-get-package-info.c
	utc-ApplicationFW-package-manager-get-package-size-info.c
	utc-ApplicationFW-package-manager-get-permission-type.c
	utc-ApplicationFW-package-manager-get-total-package-size-info.c
	utc-ApplicationFW-package-manager-is-preload-package-by-app-id.c
	utc-ApplicationFW-package-manager-set-event-cb.c
	utc-ApplicationFW-package-manager-set-event-status.c
	utc-ApplicationFW-package-manager-unset-event-cb.c
	utc-ApplicationFW-package-manager-filter-create.c
	utc-ApplicationFW-package-manager-filter-add-bool.c
	utc-ApplicationFW-package-manager-filter-add-string.c
	utc-ApplicationFW-package-manager-filter-count.c
	utc-ApplicationFW-package-manager-filter-foreach-package-info.c
	utc-ApplicationFW-package-manager-filter-destroy.c
	utc-ApplicationFW-package-size-info_get_data_size.c
	utc-ApplicationFW-package-size-info_get_app_size.c
	utc-ApplicationFW-package-size-info_get_cache_size.c
	utc-ApplicationFW-package-size-info_get_external_data_size.c
	utc-ApplicationFW-package-size-info_get_external_app_size.c
	utc-ApplicationFW-package-size-info_get_external_cache_size.c
	utc-ApplicationFW-package-info-updateinfo-create.c
	utc-ApplicationFW-package-info-updateinfo-destroy.c
	utc-ApplicationFW-package-info-updateinfo-foreach_info.c
	utc-ApplicationFW-package-info-updateinfo-get-pkgid.c
	utc-ApplicationFW-package-info-updateinfo-get-type.c
	utc-ApplicationFW-package-info-updateinfo-get-version.c
	utc-ApplicationFW-package-archive-info-create.c
	utc-ApplicationFW-package-archive-info-destroy.c
	utc-ApplicationFW-package_archive_info_foreach_direct_dependency.c
	utc-ApplicationFW-package-archive-info-get-api-version.c
	utc-ApplicationFW-package-archive-info-get-author.c
	utc-ApplicationFW-package-archive-info-get-description.c
	utc-ApplicationFW-package-archive-info-get-icon.c
	utc-ApplicationFW-package-archive-info-get-label.c
	utc-ApplicationFW-package-archive-info-get-package.c
	utc-ApplicationFW-package-archive-info-get-type.c
	utc-ApplicationFW-package-archive-info-get-version.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	capi-system-info
	glib-2.0
	dlog
	capi-appfw-app-manager
)

INCLUDE_DIRECTORIES(
    ${${CAPI_LIB}_INCLUDE_DIRS}
)

ADD_EXECUTABLE(${EXEC_NAME} ${EXEC_NAME}.c ${TC_SOURCES} ${COMMON_FILE} ${COMMON_APP_FILE})
TARGET_LINK_LIBRARIES(${EXEC_NAME}
    ${${CAPI_LIB}_LIBRARIES}
)

INSTALL(PROGRAMS ${EXEC_NAME}
    DESTINATION ${BIN_DIR}/${RPM_NAME}/bin
)

IF( DEFINED ASAN )
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall -pie -g -fsanitize=address -fsanitize-recover=address -U_FORTIFY_SOURCE -fno-omit-frame-pointer")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=/usr/lib -Wl,-fsanitize=address")
ELSE()
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -fPIE -Wall")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=/usr/lib -pie")
ENDIF()

