SET(PKG_NAME "media-content")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "capi-content-media-content")
SET(TC_SOURCES
utc-media-audio.c
utc-media-book.c
utc-media-bookmark-delete.c
utc-media-bookmark-insert.c
utc-media-bookmark.c
utc-media-content.c
utc-media-face.c
utc-media-filter-create.c
utc-media-filter-destroy.c
utc-media-filter.c
utc-media-folder.c
utc-media-group.c
utc-media-image.c
utc-media-info.c
utc-media-playlist.c
utc-media-storage.c
utc-media-tag.c
utc-media-video.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	capi-system-info
    glib-2.0
    storage
     dlog elementary
)

ADD_DEFINITIONS( -DCOMMERCIAL_FEATURE )

INCLUDE_DIRECTORIES(
	${${CAPI_LIB}_INCLUDE_DIRS}
)

ADD_EXECUTABLE(${EXEC_NAME} ${EXEC_NAME}.c ${TC_SOURCES} ${COMMON_FILE})
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

