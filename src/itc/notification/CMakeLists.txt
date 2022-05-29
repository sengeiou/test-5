SET(PKG_NAME "notification")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "notification gobject-2.0")
SET(TC_SOURCES
	ITs-notification-common.c
	ITs-notification.c
        ITs-notification-ex-item.c
        ITs-notification-ex-reporter.c
        ITs-notification-ex-action_app_control.c
        ITs-notification-ex-button.c
        ITs-notification-ex-chat-message.c
        ITs-notification-ex-checkbox.c
        ITs-notification-ex-entry.c
        ITs-notification-ex-group.c
        ITs-notification-ex-image.c
        ITs-notification-ex-input-selector.c
        ITs-notification-ex-multi-language.c
        ITs-notification-ex-progress.c
        ITs-notification-ex-text.c
        ITs-notification-ex-time.c
        ITs-notification-ex-visibility-action.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
    bundle
	glib-2.0
	gobject-2.0
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
