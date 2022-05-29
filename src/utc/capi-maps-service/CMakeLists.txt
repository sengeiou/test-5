SET(PKG_NAME "capi-maps-service")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "capi-maps-service")
SET(TC_SOURCES
    utc_maps_utils.c
    utc_maps_address_common.c
    utc_maps_area_common.c
    utc_maps_coordinates_common.c
    utc_maps_place_common.c
    utc_maps_place_attribute_common.c
    utc_maps_place_category_common.c
    utc_maps_place_contact_common.c
    utc_maps_place_editorial_common.c
    utc_maps_place_filter_common.c
    utc_maps_place_image_common.c
    utc_maps_place_link_object_common.c
    utc_maps_place_media_common.c
    utc_maps_place_rating_common.c
    utc_maps_place_review_common.c
    utc_maps_place_url_common.c
    utc_maps_preference_common.c
    utc_maps_route_common.c
    utc_maps_route_maneuver_common.c
    utc_maps_route_segment_common.c
    utc_maps_view_object_common.c
    utc_maps_view_event_data_common.c

    utc_maps_service_here.c
    utc_maps_view_here.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
    capi-appfw-application
    capi-system-info
    bundle
    glib-2.0
    dlog
    elementary
)

INCLUDE_DIRECTORIES(
    ${${CAPI_LIB}_INCLUDE_DIRS}
)

ADD_DEFINITIONS("-DLIBDIR=\"${LIBDIR}\"")
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
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=${LIBDIR} -Wl,-fsanitize=address")
ELSE()
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -fPIE -Wall")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=${LIBDIR} -pie")
ENDIF()
