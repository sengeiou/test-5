SET(PKG_NAME "player")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "capi-media-player")

SET(TC_SOURCES
	ITs-player-common.c
	ITs-player.c
	ITs-player-audio-effect.c
	ITs-player-stream-info.c
	ITs-player-subtitle.c
	ITs-player.c
	ITs-player-360.c
)

IF(DEFINED TIZENIOT)
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	capi-system-info
	capi-network-connection
	dlog
	glib-2.0
	gobject-2.0
	gthread-2.0
	storage
	libcurl
)
ENDIF()
IF( DEFINED MOBILE )
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
	${CAPI_LIB}
	appcore-efl
	bundle
	capi-appfw-application
	capi-system-info
	capi-network-connection
	dlog
	ecore
	elementary
	evas
	glib-2.0
	libcurl
)
ENDIF()
IF( DEFINED WEARABLE )
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
	${CAPI_LIB}
	appcore-efl
	bundle
	capi-appfw-application
	capi-system-info
	capi-network-connection
	dlog
	ecore
	elementary
	evas
	glib-2.0
	libcurl
)
ENDIF()

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

