SET(PKG_NAME "capi-maps-service")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "capi-maps-service")
SET(TC_SOURCES
	ITs-capi-maps-service-here.c
	ITs-capi-maps-service-address.c
	ITs-capi-maps-service-area.c
	ITs-capi-maps-service-common.c
	ITs-capi-maps-service-coordinates.c
	ITs-capi-maps-service-place-filter.c
	ITs-capi-maps-service-preference.c
	ITs-capi-maps-place-category.c
	ITs-capi-maps-view-object.c
	ITs-capi-maps-view-here.c
	ITs-capi-maps-place-here.c
	ITs-capi-maps-place-contact-here.c
	ITs-capi-maps-place-image-link-object-here.c
	ITs-capi-maps-place-review-here.c
	ITs-capi-maps-route.c
	ITs-capi-maps-route-maneuver.c
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
