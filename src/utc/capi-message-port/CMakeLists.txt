SET(PKG_NAME "capi-message-port")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "capi-message-port")
SET(TC_SOURCES
	utc-capi-message-port.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
	${CAPI_LIB}
	bundle
	capi-appfw-application
	capi-system-info
	capi-appfw-app-manager
	gobject-2.0
	glib-2.0
	dlog 
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

