SET(PKG_NAME "bluetooth")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "capi-network-bluetooth")

IF( DEFINED MOBILE )
SET(TC_SOURCES
    ITs-bluetooth-common.c
	ITs-bluetooth-audio.c
	ITs-bluetooth-device.c
	ITs-bluetooth-le-adapter.c
	ITs-bluetooth-adapter.c
	ITs-bluetooth-OPP.c
	ITs-bluetooth-socket.c
)
ENDIF()

IF( DEFINED TIZENIOT )
SET(TC_SOURCES
    ITs-bluetooth-common.c
	ITs-bluetooth-audio.c
	ITs-bluetooth-device.c
	ITs-bluetooth-le-adapter.c
	ITs-bluetooth-adapter.c
	ITs-bluetooth-OPP.c
	ITs-bluetooth-socket.c
)
ENDIF()

IF( DEFINED WEARABLE )
SET(TC_SOURCES
    ITs-bluetooth-common.c
	ITs-bluetooth-audio.c
	ITs-bluetooth-device.c
	ITs-bluetooth-le-adapter.c
	ITs-bluetooth-adapter.c
	ITs-bluetooth-OPP.c
	ITs-bluetooth-socket.c
)
ENDIF()

IF( DEFINED TV )
SET(TC_SOURCES
    ITs-bluetooth-common.c
	ITs-bluetooth-audio.c
	ITs-bluetooth-device.c
	ITs-bluetooth-adapter.c
	ITs-bluetooth-le-adapter.c
	ITs-bluetooth-socket.c
	ITs-bluetooth-OPP.c
)
ENDIF()

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	glib-2.0
    bundle
	capi-system-info
	storage
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
