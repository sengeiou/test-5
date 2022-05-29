SET(PKG_NAME "dali-toolkit")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "glib-2.0 capi-appfw-application capi-system-info dali-core dali-adaptor dali-toolkit storage bundle")
SET(TC_SOURCES
    model-3d-view/utc-dali-model-3d-view.cpp
    model-3d-view/utc-dali-model-3d-view-common.cpp
    alignment/utc-dali-alignment.cpp
    alignment/utc-dali-alignment-common.cpp
    push-button/utc-dali-push-button.cpp
    push-button/utc-dali-push-button-common.cpp
    keyboard-focus-manager/utc-dali-keyboard-focus-manager.cpp
    keyboard-focus-manager/utc-dali-keyboard-focus-manager-common.cpp
    control/utc-dali-control.cpp
    control/utc-dali-control-common.cpp
    button/utc-dali-button.cpp
    button/utc-dali-button-common.cpp
    item-factory/utc-dali-item-factory.cpp
    item-factory/utc-dali-item-factory-common.cpp
    check-box-button/utc-dali-check-box-button.cpp
    check-box-button/utc-dali-check-box-button-common.cpp
    radio-button/utc-dali-radio-button.cpp
    radio-button/utc-dali-radio-button-common.cpp
    text-editor/utc-dali-text-editor.cpp
    text-label/utc-dali-text-label.cpp
    text-label/utc-dali-text-label-common.cpp
    text-field/utc-dali-text-field.cpp
    text-field/utc-dali-text-field-common.cpp
    scrollable/utc-dali-scrollable.cpp
    scrollable/utc-dali-scrollable-common.cpp
    image/utc-dali-image.cpp
    image/utc-dali-image-common.cpp
    image-view/utc-dali-image-view.cpp
    image-view/utc-dali-image-view-common.cpp
    accessibility-manager/utc-dali-accessibility-manager.cpp
    accessibility-manager/utc-dali-accessibility-manager-common.cpp
    scroll-bar/utc-dali-scroll-bar.cpp
    scroll-bar/utc-dali-scroll-bar-common.cpp
    item-layout/utc-dali-item-layout.cpp
    item-layout/utc-dali-item-layout-common.cpp
    scroll-view-effect/utc-dali-scroll-view-effect.cpp
    scroll-view-effect/utc-dali-scroll-view-effect-common.cpp
    scroll-view-effect/utc-dali-scroll-view-page-path-effect.cpp
    table-view/utc-dali-table-view.cpp
    table-view/utc-dali-table-view-common.cpp
    item-view/utc-dali-item-view.cpp
    item-view/utc-dali-item-view-common.cpp
    scroll-view/utc-dali-scroll-view.cpp
    scroll-view/utc-dali-scroll-view-common.cpp
    toolkit/utc-dali-toolkit.cpp
    toolkit/utc-dali-toolkit-common.cpp
    default-ruler/utc-dali-default-ruler.cpp
    default-ruler/utc-dali-default-ruler-common.cpp
    ruler-domain/utc-dali-ruler-domain.cpp
    ruler-domain/utc-dali-ruler-domain-common.cpp
    fixed-ruler/utc-dali-fixed-ruler.cpp
    fixed-ruler/utc-dali-fixed-ruler-common.cpp
    ruler/utc-dali-ruler.cpp
    ruler/utc-dali-ruler-common.cpp
    control-impl/utc-dali-control-impl.cpp
    control-impl/utc-dali-control-impl-common.cpp
    style-manager/utc-dali-style-manager-common.cpp
    style-manager/utc-dali-style-manager.cpp
    flex-container/utc-dali-flex-container-common.cpp
    flex-container/utc-dali-flex-container.cpp
    item-range/utc-dali-item-range-common.cpp
    item-range/utc-dali-item-range.cpp
    default-item-layout/utc-dali-default-item-layout.cpp
    default-item-layout/utc-dali-default-item-layout-common.cpp
    slider/utc-dali-slider.cpp
    slider/utc-dali-slider-common.cpp
    video-view/utc-dali-video-view.cpp
    video-view/utc-dali-video-view-common.cpp
    async-image-loader/utc-dali-async-image-loader.cpp
    async-image-loader/utc-dali-async-image-loader-common.cpp
    sync-image-loader/utc-dali-sync-image-loader.cpp
    sync-image-loader/utc-dali-sync-image-loader-common.cpp
    progress-bar/utc-dali-progress-bar.cpp
    progress-bar/utc-dali-progress-bar-common.cpp
)

LIST(APPEND TC_SOURCES
  ../../common/dali-common.cpp
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
SET(CMAKE_CXX_FLAGS " -fPIE -Wall")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=/usr/lib -pie")
SET(EXE_DALI_CORE_CTS_LINKER_FLAGS "-L${${CAPI_LIB}_LIBRARY_DIRS} -ldali-core -ldali-adaptor ")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXE_DALI_CORE_CTS_LINKER_FLAGS}")
ENDIF()


