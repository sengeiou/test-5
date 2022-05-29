SET(PKG_NAME "yaca")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "yaca")
SET(TC_SOURCES
    ITs-yaca-common.c
	ITs-yaca.c
	ITs-yaca-digest.c
	ITs-yaca-encrypt.c
	ITs-yaca-key.c
	ITs-yaca-seal.c
	ITs-yaca-sign.c
	ITs-yaca-simple.c
	ITs-yaca-rsa.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	glib-2.0
    bundle
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
