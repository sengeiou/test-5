SET(PKG_NAME "minicontrol")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "minicontrol bundle	glib-2.0	capi-system-info	minicontrol-viewer	minicontrol-provider	minicontrol-monitor    dbus-1    dbus-glib-1    	capi-appfw-application")
SET(TC_SOURCES
    ITs-minicontrol-common.c
	ITs-minicontrol.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
#    ${CAPI_LIB}
    bundle
	glib-2.0
	capi-system-info
	minicontrol-viewer
	minicontrol-provider
	minicontrol-monitor
    dbus-1
    dbus-glib-1
	capi-appfw-application
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
