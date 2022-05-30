SET(PKG_NAME "sync-manager")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "core-sync-client")
SET(TC_SOURCES
    ITs-sync-manager-common.c
	ITs-sync-manager.c
)
IF( DEFINED TV )
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	bundle
	capi-system-info
	capi-system-runtime-info
	capi-system-device
	capi-appfw-app-manager
	capi-appfw-package-manager
	capi-network-connection
	appcore-efl
	dlog
	db-util
	pkgmgr
	pkgmgr-info
	appsvc
	vconf
	vconf-internal-keys
	libxml-2.0
	glib-2.0
	gio-unix-2.0
	accounts-svc
	alarm-service
	calendar-service2
	contacts-service2
	ecore
	dlog
)
ENDIF()
IF( DEFINED MOBILE )
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	bundle
	capi-system-info
	capi-system-runtime-info
	capi-system-device
	capi-appfw-app-manager
	capi-appfw-package-manager
	capi-network-connection
	appcore-efl
	dlog
	db-util
	pkgmgr
	pkgmgr-info
	appsvc
	vconf
	vconf-internal-keys
	libxml-2.0
	glib-2.0
	gio-unix-2.0
	accounts-svc
	alarm-service
	calendar-service2
	contacts-service2
	ecore
	dlog
)
ENDIF()

IF( DEFINED WEARABLE )
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	bundle
	capi-system-info
	capi-system-runtime-info
	capi-system-device
	capi-appfw-app-manager
	capi-appfw-package-manager
	capi-network-connection
	appcore-efl
	dlog
	db-util
	pkgmgr
	pkgmgr-info
	appsvc
	vconf
	vconf-internal-keys
	libxml-2.0
	glib-2.0
	gio-unix-2.0
	accounts-svc
	alarm-service
	ecore
	dlog
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
