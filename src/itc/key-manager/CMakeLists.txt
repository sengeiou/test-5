SET(PKG_NAME "key-manager")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "key-manager")
SET(TC_SOURCES
	ITs-key-manager-common.c
	ITs-key-manager.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
	${CAPI_LIB}
	capi-appfw-application
	bundle
	capi-system-info
	glib-2.0
	dlog
)

INCLUDE_DIRECTORIES(
	${${CAPI_LIB}_INCLUDE_DIRS}
)

IF(NOT DEFINED COMMON_FILE)
	MESSAGE(FATAL_ERROR "COMMON_FILE variable not defined")
ENDIF(NOT DEFINED COMMON_FILE)

ADD_EXECUTABLE(${EXEC_NAME} ${EXEC_NAME}.c ${TC_SOURCES} ${COMMON_FILE})
TARGET_LINK_LIBRARIES(${EXEC_NAME}
	${${CAPI_LIB}_LIBRARIES}
	resolv
	pthread
)

INSTALL(PROGRAMS ${EXEC_NAME}
	DESTINATION ${BIN_DIR}/${RPM_NAME}/bin
)

INSTALL(FILES dfb08fe4.0 DESTINATION /etc/ssl/certs/)

IF( DEFINED ASAN )
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall -pie -g -fsanitize=address -fsanitize-recover=address -U_FORTIFY_SOURCE -fno-omit-frame-pointer")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=/usr/lib -Wl,-fsanitize=address")
ELSE()
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -fPIE -Wall")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=/usr/lib -pie")
ENDIF()
