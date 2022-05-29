SET(PKG_NAME "wifi-direct")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "capi-network-wifi-direct")

ADD_DEFINITIONS("-DTIZEN_FEATURE_WIFI_DISPLAY -DTIZEN_FEATURE_SERVICE_DISCOVERY")

SET(TC_SOURCES
    utc-wifi-direct-connection-negative.c
    utc-wifi-direct-connection-positive.c
    utc-wifi-direct-device-negative.c
    utc-wifi-direct-device-positive.c
    utc-wifi-direct-discovery-negative.c
    utc-wifi-direct-discovery-positive.c
    utc-wifi-direct-group-negative.c
    utc-wifi-direct-group-positive.c
    utc-wifi-direct-registration-negative.c
    utc-wifi-direct-registration-positive.c
    utc-wifi-direct-service-discovery-negative.c
    utc-wifi-direct-service-discovery-positive.c
)

IF( DEFINED MOBILE)
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	capi-system-info
	glib-2.0
	dlog 
    )
ENDIF()

IF( DEFINED TIZENIOT)
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	capi-system-info
	glib-2.0
	dlog 
    )
ENDIF()

IF( DEFINED TV)
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	capi-system-info
	glib-2.0
	dlog 
    )
ENDIF()

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
