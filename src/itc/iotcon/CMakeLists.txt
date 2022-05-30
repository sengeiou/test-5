SET(PKG_NAME "iotcon")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "iotcon")
SET(TC_SOURCES
	ITs-iotcon-lite-resource.c
	ITs-iotcon-representation.c
	ITs-iotcon.c
	ITs-iotcon-device.c
	ITs-iotcon-observers.c
	ITs-iotcon-query.c
	ITs-iotcon-state.c
	ITs-iotcon-common.c
	ITs-iotcon-list.c
	ITs-iotcon-options.c
	ITs-iotcon-remote-resource.c
	ITs-iotcon-response.c
	ITs-iotcon-request.c
	ITs-iotcon-resource.c
	ITs-iotcon-presence.c
	ITs-iotcon-presence-response.c
	ITs-iotcon-serive.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	iotcon
	capi-appfw-application
    bundle
	glib-2.0
	capi-system-info
	dlog
)

INCLUDE_DIRECTORIES(
    ${${CAPI_LIB}_INCLUDE_DIRS}
)

ADD_EXECUTABLE(${EXEC_NAME} ${EXEC_NAME}.c ${TC_SOURCES} ${COMMON_FILE})
TARGET_LINK_LIBRARIES(${EXEC_NAME}
    ${${CAPI_LIB}_LIBRARIES}
    bundle
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
