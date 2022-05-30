SET(PKG_NAME "bundle")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "bundle")
SET(TC_SOURCES
    utc-ApplicationFW-bundle-create-func.c
    utc-ApplicationFW-bundle-decode-func.c
    utc-ApplicationFW-bundle-del-func.c
    utc-ApplicationFW-bundle-dup-func.c
    utc-ApplicationFW-bundle-encode-func.c
    utc-ApplicationFW-bundle-free-func.c
    utc-ApplicationFW-bundle-get-count-func.c
    utc-ApplicationFW-bundle-foreach-func.c
    utc-ApplicationFW-bundle-get-type-func.c
    utc-ApplicationFW-bundle-add-str-func.c
    utc-ApplicationFW-bundle-get-str-func.c
    utc-ApplicationFW-bundle-add-byte-func.c
    utc-ApplicationFW-bundle-get-byte-func.c
    utc-ApplicationFW-bundle-add-str-array-func.c
    utc-ApplicationFW-bundle-get-str-array-func.c
    utc-ApplicationFW-bundle-keyval.c
    utc-ApplicationFW-bundle-keyval-get-basic-val-func.c
    utc-ApplicationFW-bundle-keyval-get-array-val-func.c
    utc-ApplicationFW-bundle-add-byte-array-func.c
    utc-ApplicationFW-bundle-set-byte-array-element-func.c
    utc-ApplicationFW-bundle-get-byte-array-func.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	capi-system-info
    capi-base-common
    glib-2.0
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

