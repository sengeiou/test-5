SET(PKG_NAME "iotcon")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(TC_SOURCES
    utc-iotcon.c
    utc-iotcon-common.c
    utc-iotcon-struct.c
    utc-iotcon-representation.c
    utc-iotcon-device.c
    utc-iotcon-presence.c
    utc-iotcon-presence-response.c
    utc-iotcon-encap.c
    utc-iotcon-service.c
    utc-iotcon-remote-resource.c
    utc-iotcon-resource.c
)

IF( DEFINED ASAN )
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall -pie -g -fsanitize=address -fsanitize-recover=address -U_FORTIFY_SOURCE -fno-omit-frame-pointer")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=/usr/lib -Wl,-fsanitize=address")
ELSE()
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -fPIE -Wall")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=/usr/lib -pie")
ENDIF()

PKG_CHECK_MODULES(pkgs REQUIRED
   iotcon
	capi-appfw-application
	glib-2.0
	capi-system-info
	dlog
	
	capi-network-wifi-manager
)
INCLUDE_DIRECTORIES(${pkgs_INCLUDE_DIRS})
LINK_DIRECTORIES(${pkgs_LIBRARY_DIRS})

ADD_EXECUTABLE(${EXEC_NAME} ${EXEC_NAME}.c ${TC_SOURCES} ${COMMON_FILE})
TARGET_LINK_LIBRARIES(${EXEC_NAME} ${pkgs_LIBRARIES})
INSTALL(PROGRAMS ${EXEC_NAME} DESTINATION ${BIN_DIR}/${RPM_NAME}/bin)
