SET(PKG_NAME "vulkan")

SET(EXEC_NAME "tct-${PKG_NAME}-ctc")
SET(RPM_NAME "native-${PKG_NAME}-ctc")

SET(CAPI_LIB "vulkan")
SET(TC_SOURCES
    CTs-vulkan-common.c
	CTs-vulkan-instance.c
	CTs-vulkan-draw.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    capi-appfw-application
	glib-2.0
    bundle
	capi-system-info
	dlog
	sdl2
	glesv2
)

INCLUDE_DIRECTORIES(
    ${${CAPI_LIB}_INCLUDE_DIRS}
)

ADD_EXECUTABLE(${EXEC_NAME} tct-${PKG_NAME}-native.c ${TC_SOURCES} ${COMMON_FILE})
TARGET_LINK_LIBRARIES(${EXEC_NAME}
    ${${CAPI_LIB}_LIBRARIES}
    bundle
	vulkan
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
