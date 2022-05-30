SET(PKG_NAME "webkit2")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "chromium-efl gobject-2.0")
IF( DEFINED MOBILE )
SET(TC_SOURCES
	ITs-webkit2-common.c
	ITs-webkit2-back_forward_list.c
	ITs-webkit2-autofill-profile.c
	ITs-webkit2-context.c
	ITs-webkit2-context-form.c
	ITs-webkit2-context-web.c
	ITs-webkit2-cookies.c
	ITs-webkit2-error.c
	ITs-webkit2-policy-decision.c
	ITs-webkit2-settings.c
	ITs-webkit2-view.c
	ITs-webkit2-intercept-request.c
	ITs-webkit2-view-add-incognito-mode.c
	ITs-webkit2-ewk-view-original-url.c
)
ENDIF()
IF( DEFINED TIZENIOT )
SET(TC_SOURCES
	ITs-webkit2-common.c
	ITs-webkit2-back_forward_list.c
	ITs-webkit2-autofill-profile.c
	ITs-webkit2-context.c
	ITs-webkit2-context-form.c
	ITs-webkit2-context-web.c
	ITs-webkit2-cookies.c
	ITs-webkit2-error.c
	ITs-webkit2-policy-decision.c
	ITs-webkit2-settings.c
	ITs-webkit2-view.c
	ITs-webkit2-intercept-request.c
	ITs-webkit2-view-add-incognito-mode.c
	ITs-webkit2-ewk-view-original-url.c
)
ENDIF()
IF( DEFINED WEARABLE )
SET(TC_SOURCES
	ITs-webkit2-common.c
	ITs-webkit2-back_forward_list.c
	ITs-webkit2-context.c
	ITs-webkit2-cookies.c
	ITs-webkit2-policy-decision.c
	ITs-webkit2-settings.c
	ITs-webkit2-view.c
	ITs-webkit2-intercept-request.c
	ITs-webkit2-view-add-incognito-mode.c
	ITs-webkit2-ewk-view-original-url.c
)
ENDIF()
IF( DEFINED TV )
SET(TC_SOURCES
    ITs-webkit2-context.c
    ITs-webkit2-autofill-profile.c
    ITs-webkit2-context-form.c
    ITs-webkit2-context-web.c
    ITs-webkit2-common.c
    ITs-webkit2-back_forward_list.c
    ITs-webkit2-cookies.c
    ITs-webkit2-error.c
    ITs-webkit2-policy-decision.c
    ITs-webkit2-settings.c
    ITs-webkit2-view.c
    ITs-webkit2-intercept-request.c
    ITs-webkit2-view-add-incognito-mode.c
    ITs-webkit2-ewk-view-original-url.c
)
ENDIF()
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
    bundle
    ecore-evas
    ecore
    edje
    eina
    glib-2.0
    gobject-2.0
    wayland-client
	capi-system-info
	dlog 
	storage
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
