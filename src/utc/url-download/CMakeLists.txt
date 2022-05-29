SET(PKG_NAME "url-download")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "capi-web-url-download")
SET(TC_SOURCES
	utc-download-common.c
    utc-download-add-http-header-field.c
    utc-download-create.c
    utc-download-destroy.c
    utc-download-get-auto-download.c
    utc-download-get-content-name.c
    utc-download-get-content-size.c
    utc-download-get-destination.c
    utc-download-get-downloaded-file-path.c
    utc-download-get-error.c
    utc-download-get-etag.c
    utc-download-get-file-name.c
    utc-download-get-http-header-field.c
    utc-download-get-http-header-field-list.c
    utc-download-get-http-status.c
    utc-download-get-mime-type.c
    utc-download-get-network-type.c
    utc-download-get-notification-app-control.c
    utc-download-get-notification-description.c
    utc-download-get-notification-title.c
    utc-download-get-notification-type.c
    utc-download-get-state.c
    utc-download-get-temp-path.c
    utc-download-get-url.c
    utc-download-pause.c
    utc-download-cancel.c
    utc-download-remove-http-header-field.c
    utc-download-set-auto-download.c
    utc-download-set-destination.c
    utc-download-set-file-name.c
    utc-download-set-network-type.c
    utc-download-set-notification-app-control.c
    utc-download-set-notification-description.c
    utc-download-set-notification-title.c
    utc-download-set-notification-type.c
    utc-download-set-progress-cb.c
    utc-download-set-state-changed-cb.c
    utc-download-set-temp-file-path.c
    utc-download-set-url.c
    utc-download-start.c
    utc-download-unset-progress-cb.c
    utc-download-unset-state-changed-cb.c
)


PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	capi-system-info
    glib-2.0
    gobject-2.0
	dlog 
)

INCLUDE_DIRECTORIES(
    ${${CAPI_LIB}_INCLUDE_DIRS}
)

ADD_EXECUTABLE(${EXEC_NAME} ${EXEC_NAME}.c ${TC_SOURCES} ${COMMON_FILE})
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

