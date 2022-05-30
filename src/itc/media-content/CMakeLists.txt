SET(PKG_NAME "media-content")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "capi-content-media-content")

IF( DEFINED MOBILE )
SET(TC_SOURCES
    ITs-media-content-common.c
	ITs-media-content.c
	ITs-media-content-album.c
	ITs-media-content-tag.c
	ITs-media-content-folder.c
	ITs-media-content-bookmark.c
	ITs-media-content-playlist.c
	ITs-media-content-filter.c
	ITs-media-content-group.c
	ITs-media-content-info.c
	ITs-media-content-audio-meta.c
	ITs-media-content-video-meta.c
	ITs-media-content-image-meta.c
	ITs-media-content-face.c
        ITs-media-content-book.c
)
ENDIF()

IF( DEFINED TIZENIOT )
SET(TC_SOURCES
    ITs-media-content-common.c
	ITs-media-content.c
	ITs-media-content-album.c
	ITs-media-content-tag.c
	ITs-media-content-folder.c
	ITs-media-content-bookmark.c
	ITs-media-content-playlist.c
	ITs-media-content-filter.c
	ITs-media-content-group.c
	ITs-media-content-info.c
	ITs-media-content-audio-meta.c
	ITs-media-content-video-meta.c
	ITs-media-content-image-meta.c
	ITs-media-content-face.c
	ITs-media-content-storage.c
        ITs-media-content-book.c
)
ENDIF()

IF( DEFINED WEARABLE )
SET(TC_SOURCES
    ITs-media-content-common.c
	ITs-media-content.c
	ITs-media-content-album.c
	ITs-media-content-tag.c
	ITs-media-content-folder.c
	ITs-media-content-bookmark.c
	ITs-media-content-playlist.c
	ITs-media-content-filter.c
	ITs-media-content-group.c
	ITs-media-content-info.c
	ITs-media-content-audio-meta.c
	ITs-media-content-video-meta.c
	ITs-media-content-image-meta.c
	ITs-media-content-face.c
        ITs-media-content-book.c
)
ENDIF()

IF( DEFINED TV )
SET(TC_SOURCES
    ITs-media-content-common.c
	ITs-media-content.c
	ITs-media-content-album.c
	ITs-media-content-tag.c
	ITs-media-content-folder.c
	ITs-media-content-bookmark.c
	ITs-media-content-playlist.c
	ITs-media-content-filter.c
	ITs-media-content-group.c
	ITs-media-content-info.c
	ITs-media-content-audio-meta.c
	ITs-media-content-video-meta.c
	ITs-media-content-image-meta.c
	ITs-media-content-face.c
	ITs-media-content-storage.c
        ITs-media-content-book.c
)
ENDIF()


PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
    bundle
	glib-2.0
	capi-system-info
	dlog
	libmedia-service
	media-thumbnail
	libmedia-utils
	capi-base-common
	icu-i18n
	vconf
	storage
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
