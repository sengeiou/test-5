SET(PKG_NAME "platform-permission")

SET(EXEC_NAME "tct-${PKG_NAME}-ctc")
SET(RPM_NAME "native-${PKG_NAME}-ctc")

SET(CAPI_LIB "capi-media-camera")

IF( DEFINED MOBILE )
SET(CAPI_LIB "iotcon")
ENDIF()

IF( DEFINED MOBILE )
SET(TC_SOURCES
	CTs-platform-permission-common.c 
	CTs-platform-permission-ime.c 
	CTs-platform-permission-sync-manager.c  
	CTs-platform-permission-context.c  
	CTs-platform-permission-notification.c
	CTs-platform-permission-datacontrol.c 
	CTs-platform-permission-device.c 
	CTs-platform-permission-email.c
	CTs-platform-permission-location-manager.c 
	CTs-platform-permission-messages.c 
	CTs-platform-permission-package-manager.c 
	CTs-platform-permission-recorder.c
	CTs-platform-permission-runtime-info.c
	CTs-platform-permission-sensor.c
	CTs-platform-permission-sound-manager.c
	CTs-platform-permission-smartcard.c
	CTs-platform-permission-stt.c 
	CTs-platform-permission-badge.c 
	CTs-platform-permission-shortcut.c 
	CTs-platform-permission-sppc.c  
	CTs-platform-permission-bluetooth.c
	CTs-platform-permission-audio-io.c 
	CTs-platform-permission-camera.c 
	CTs-platform-permission-inputmethod-manager.c 
	CTs-platform-permission-connection.c 
	CTs-platform-permission-thumbnail-util.c 
	CTs-platform-permission-url-download.c 
	CTs-platform-permission-wifi-direct.c 
	CTs-platform-permission-app-manager.c   
	CTs-platform-permission-libfeedback.c 
	CTs-platform-permission-telephony.c 
	CTs-platform-permission-nfc.c  
	CTs-platform-permission-media-controller.c
	CTs-platform-permission-media-content.c
	CTs-platform-permission-voice-control.c 
	CTs-platform-permission-voice-control-elm.c 
	CTs-platform-permission-widget-service.c 
	CTs-platform-permission-widget-viewer.c 
	CTs-platform-permission-application.c 
	CTs-platform-permission-maps-service.c  
	CTs-platform-permission-attach-panel.c
	CTs-platform-permission-accountsvc.c 
	CTs-platform-permission-contacts-service.c 
	CTs-platform-permission-calendar-service.c
	CTs-platform-permission-oauth2-manager.c
	CTs-platform-permission-vpn-service.c
	CTs-platform-permission-efl-util.c
	CTs-platform-permission-iotcon.c
	CTs-platform-permission-phonenumber-utils.c
	CTs-platform-permission-media-streamer.c
	CTs-platform-permission-http.c
	CTs-platform-permission-wifi-manager.c
)
ENDIF()

IF( DEFINED WEARABLE )
SET(TC_SOURCES
    CTs-platform-permission-common.c
	CTs-platform-permission-app-manager.c
	CTs-platform-permission-application.c
	CTs-platform-permission-audio-io.c
	CTs-platform-permission-badge.c
	CTs-platform-permission-bluetooth.c
	CTs-platform-permission-camera.c
	CTs-platform-permission-connection.c
	CTs-platform-permission-datacontrol.c
	CTs-platform-permission-device.c
	CTs-platform-permission-location-manager.c
	CTs-platform-permission-media-content.c
	CTs-platform-permission-messages.c
	CTs-platform-permission-nfc.c
	CTs-platform-permission-notification.c
	CTs-platform-permission-package-manager.c
	CTs-platform-permission-recorder.c
	CTs-platform-permission-sensor.c
	CTs-platform-permission-smartcard.c
	CTs-platform-permission-sound-manager.c
	CTs-platform-permission-sppc.c
	CTs-platform-permission-stt.c
	CTs-platform-permission-telephony.c
	CTs-platform-permission-widget-service.c
	CTs-platform-permission-widget-viewer.c
	CTs-platform-permission-http.c
	CTs-platform-permission-media-streamer.c
	CTs-platform-permission-wifi-manager.c
)
ENDIF()

IF( DEFINED MOBILE )
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
    iotcon
    sqlite3
    shortcut
    phonenumber-utils
    capi-media-streamer
	dlog 
    db-util
    glib-2.0
	ecore
	ecore-evas
	deviced
    pkgmgr-info
    libsmack
    appcore-common
    appcore-efl
    capi-base-common
	core-sync-client
	efl-extension
	stt
	attach-panel
	libcurl
	oauth2
	capi-geofence-manager
	voice-control
	key-manager
	voice-control-elm
    alarm-service
    capi-network-bluetooth
    capi-system-info
	capi-system-runtime-info
	capi-location-manager
	capi-network-connection
	feedback
	capi-media-thumbnail-util
	capi-messaging-email
	capi-web-url-download
	capi-system-device
	tapi
	capi-telephony
	capi-appfw-package-manager
	capi-media-recorder
	capi-messaging-messages
    msg-service
    push
    capi-system-system-settings
    capi-media-sound-manager
    contacts-service2
    calendar-service2
	notification
	capi-appfw-app-manager
	capi-content-media-content
	capi-media-player
	capi-system-sensor
	capi-media-wav-player
	accounts-svc
	capi-appfw-application
	capi-appfw-alarm
	capi-appfw-app-control
    capi-data-control
    capi-media-audio-io
    capi-message-port
    capi-network-wifi-direct
    capi-network-nfc
    capi-network-http
	context
	minicontrol-viewer
	minicontrol-provider
	minicontrol-monitor
	capi-network-smartcard
	capi-maps-service
	capi-media-controller
	
	evas
	capi-system-info
	widget_viewer_evas
	widget_service
	capi-base-common
	capi-system-runtime-info
    capi-vpnsvc
    bundle
	capi-ui-inputmethod-manager
	capi-ui-inputmethod
	capi-ui-efl-util
    badge
    storage
	capi-network-wifi-manager

)
ENDIF()

IF( DEFINED WEARABLE )
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
    sqlite3
	dlog 
    db-util
    glib-2.0
	ecore
	ecore-evas
	deviced
    pkgmgr-info
    libsmack
    appcore-common
    appcore-efl
    capi-base-common
    alarm-service
    capi-network-bluetooth
    capi-system-info
    capi-media-streamer
	capi-system-runtime-info
	capi-location-manager
	capi-network-connection
	capi-web-url-download
	capi-system-device
	tapi
	capi-telephony
	capi-appfw-package-manager
	capi-media-recorder
	capi-messaging-messages
    msg-service
    push
    capi-system-system-settings
    capi-media-sound-manager
    notification
	capi-appfw-app-manager
	capi-content-media-content
	capi-media-player
	capi-system-sensor
	capi-media-wav-player
	accounts-svc
	capi-appfw-application
	capi-appfw-alarm
	capi-appfw-app-control
    capi-data-control
    capi-media-audio-io
    capi-message-port
    capi-network-wifi-direct
    capi-network-nfc
    capi-network-http
	capi-network-smartcard
	capi-maps-service
	capi-media-controller
	evas
	capi-system-info
	widget_viewer_evas
	widget_service
	capi-base-common
	capi-system-runtime-info
    bundle
	capi-ui-inputmethod-manager
	capi-ui-inputmethod
	capi-ui-efl-util
    badge
    storage
	stt
	capi-network-wifi-manager
)
ENDIF()

INCLUDE_DIRECTORIES(
    ${${CAPI_LIB}_INCLUDE_DIRS}
)

ADD_EXECUTABLE(${EXEC_NAME} tct-${PKG_NAME}-native.c ${TC_SOURCES} ${COMMON_FILE} ${COMMON_APP_FILE})
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

