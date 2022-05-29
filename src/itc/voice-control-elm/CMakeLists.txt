SET(PKG_NAME "voice-control-elm")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "voice-control-elm capi-appfw-application    bundle	capi-system-info	bundle	appcore-efl	capi-base-common	evas	eina	ecore		voice-control-widget	dlog	edje	libxml-2.0	aul	capi-base-common	capi-media-audio-io	capi-media-sound-manager	capi-network-bluetooth	dbus-1	dlog	ecore	glib-2.0	libxml-2.0	vconf")
SET(TC_SOURCES
	ITs-voice-control-elm-common.c
	ITs-voice-control-elm.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
	${CAPI_LIB}
	capi-appfw-application
	bundle
	capi-system-info
	bundle
	appcore-efl
	capi-base-common
	evas
	eina
	ecore
	voice-control-widget
	dlog
	edje
	libxml-2.0
	aul
	capi-base-common
	capi-media-audio-io
	capi-media-sound-manager
	capi-network-bluetooth
	dbus-1
	dlog
	ecore
	glib-2.0
	libxml-2.0
	vconf
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
