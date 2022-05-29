ST(PKG_NAME "dali-adaptor")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "glib-2.0 capi-appfw-application capi-system-info dali-core dali-adaptor dali-toolkit storage bundle capi-system-system-settings")
SET(TC_SOURCES
    timer/utc-dali-timer-common.cpp
    timer/utc-dali-timer.cpp
    window/utc-dali-window.cpp
    window/utc-dali-window-common.cpp
    native-image-source/utc-dali-native-image-source.cpp
    native-image-source/utc-dali-native-image-source-common.cpp
    key/utc-dali-key.cpp
    key/utc-dali-key-common.cpp
    ttsplayer/utc-dali-ttsplayer.cpp
    ttsplayer/utc-dali-ttsplayer-common.cpp
    application/utc-dali-application.cpp
    application/utc-dali-application-common.cpp
    capture/utc-dali-capture.cpp
    capture/utc-dali-capture-common.cpp
)

IF(DEFINED WEARABLE)
SET(TC_SOURCES ${TC_SOURCES}
    application/utc-dali-watch.cpp
    application/utc-dali-watch-time.cpp
)
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
    glib-2.0
    capi-appfw-application
    capi-system-info
    dali-core
    dali-adaptor
    dali-toolkit
    storage
    bundle
    dlog
    
    capi-appfw-watch-application
    appcore-watch
)
ELSE()
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
    glib-2.0
    capi-appfw-application
    capi-system-info
    dali-core
    dali-adaptor
    dali-toolkit
    storage
    bundle
    dlog
    
)
ENDIF()

LIST(APPEND TC_SOURCES
  ../../common/dali-common.cpp
)

INCLUDE_DIRECTORIES(
    ${${CAPI_LIB}_INCLUDE_DIRS}
    ./
    ../../common
)

ADD_EXECUTABLE(${EXEC_NAME} ${EXEC_NAME}.cpp ${TC_SOURCES})
TARGET_LINK_LIBRARIES(${EXEC_NAME}
    ${${CAPI_LIB}_LIBRARIES}
    pthread
)

INSTALL(PROGRAMS ${EXEC_NAME}
    DESTINATION ${BIN_DIR}/${RPM_NAME}/bin
)

IF( DEFINED ASAN )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -pie -g -fsanitize=address -fsanitize-recover=address -U_FORTIFY_SOURCE -fno-omit-frame-pointer")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=/usr/lib -Wl,-fsanitize=address")
SET(EXE_DALI_CORE_CTS_LINKER_FLAGS "-L${${CAPI_LIB}_LIBRARY_DIRS} -ldali-core -ldali-adaptor ")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXE_DALI_CORE_CTS_LINKER_FLAGS}")
ELSE()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fPIE -Wall")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=/usr/lib -pie")
SET(EXE_DALI_CORE_CTS_LINKER_FLAGS "-L${${CAPI_LIB}_LIBRARY_DIRS} -ldali-core -ldali-adaptor ")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXE_DALI_CORE_CTS_LINKER_FLAGS}")
ENDIF()
