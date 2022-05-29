SET(PKG_NAME "bluetooth")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "capi-network-bluetooth")

IF( DEFINED WEARABLE )
SET(TC_SOURCES
utc_bluetooth_adapter_negative.c
utc_bluetooth_adapter_positive.c
utc_bluetooth_audio_negative.c
utc_bluetooth_audio_positive.c
utc_bluetooth_common_positive.c
utc_bluetooth_device_discovery_negative.c
utc_bluetooth_device_discovery_positive.c
utc_bluetooth_device_negative.c
utc_bluetooth_device_positive.c
utc_bluetooth_gatt_negative.c
utc_bluetooth_gatt_positive.c
utc_bluetooth_hdp_negative.c
utc_bluetooth_hdp_positive.c
utc_bluetooth_hid_negative.c
utc_bluetooth_hid_positive.c
utc_bluetooth_opp_client_negative.c
utc_bluetooth_opp_client_positive.c
utc_bluetooth_opp_server_negative.c
utc_bluetooth_opp_server_positive.c
utc_bluetooth_service_search_negative.c
utc_bluetooth_service_search_positive.c
utc_bluetooth_socket_negative.c
utc_bluetooth_socket_positive.c
utc_bluetooth_pbap_negative.c
utc_bluetooth_pbap_positive.c
utc_bluetooth_avrcp_control_positive.c
utc_bluetooth_avrcp_control_negative.c
)
ENDIF()

IF( DEFINED MOBILE )
SET(TC_SOURCES
utc_bluetooth_adapter_negative.c
utc_bluetooth_adapter_positive.c
utc_bluetooth_audio_negative.c
utc_bluetooth_audio_positive.c
utc_bluetooth_common_positive.c
utc_bluetooth_device_discovery_negative.c
utc_bluetooth_device_discovery_positive.c
utc_bluetooth_device_negative.c
utc_bluetooth_device_positive.c
utc_bluetooth_gatt_negative.c
utc_bluetooth_gatt_positive.c
utc_bluetooth_hdp_negative.c
utc_bluetooth_hdp_positive.c
utc_bluetooth_hid_negative.c
utc_bluetooth_hid_positive.c
utc_bluetooth_opp_client_negative.c
utc_bluetooth_opp_client_positive.c
utc_bluetooth_opp_server_negative.c
utc_bluetooth_opp_server_positive.c
utc_bluetooth_service_search_negative.c
utc_bluetooth_service_search_positive.c
utc_bluetooth_socket_negative.c
utc_bluetooth_socket_positive.c
utc_bluetooth_avrcp_control_positive.c
utc_bluetooth_avrcp_control_negative.c
)
ENDIF()

IF( DEFINED TIZENIOT )
SET(TC_SOURCES
utc_bluetooth_adapter_negative.c
utc_bluetooth_adapter_positive.c
utc_bluetooth_audio_negative.c
utc_bluetooth_audio_positive.c
utc_bluetooth_common_positive.c
utc_bluetooth_device_discovery_negative.c
utc_bluetooth_device_discovery_positive.c
utc_bluetooth_device_negative.c
utc_bluetooth_device_positive.c
utc_bluetooth_gatt_negative.c
utc_bluetooth_gatt_positive.c
utc_bluetooth_hdp_negative.c
utc_bluetooth_hdp_positive.c
utc_bluetooth_hid_negative.c
utc_bluetooth_hid_positive.c
utc_bluetooth_opp_client_negative.c
utc_bluetooth_opp_client_positive.c
utc_bluetooth_opp_server_negative.c
utc_bluetooth_opp_server_positive.c
utc_bluetooth_service_search_negative.c
utc_bluetooth_service_search_positive.c
utc_bluetooth_socket_negative.c
utc_bluetooth_socket_positive.c
utc_bluetooth_avrcp_control_positive.c
utc_bluetooth_avrcp_control_negative.c
)
ENDIF()

IF( DEFINED TV )
SET(TC_SOURCES
utc_bluetooth_adapter_negative.c
utc_bluetooth_adapter_positive.c
utc_bluetooth_audio_negative.c
utc_bluetooth_audio_positive.c
utc_bluetooth_common_positive.c
utc_bluetooth_device_discovery_negative.c
utc_bluetooth_device_discovery_positive.c
utc_bluetooth_device_negative.c
utc_bluetooth_device_positive.c
utc_bluetooth_gatt_negative.c
utc_bluetooth_gatt_positive.c
utc_bluetooth_hdp_negative.c
utc_bluetooth_hdp_positive.c
utc_bluetooth_hid_negative.c
utc_bluetooth_hid_positive.c
utc_bluetooth_opp_client_negative.c
utc_bluetooth_opp_client_positive.c
utc_bluetooth_opp_server_negative.c
utc_bluetooth_opp_server_positive.c
utc_bluetooth_service_search_negative.c
utc_bluetooth_service_search_positive.c
utc_bluetooth_socket_negative.c
utc_bluetooth_socket_positive.c
utc_bluetooth_avrcp_control_positive.c
utc_bluetooth_avrcp_control_negative.c
)
ENDIF()

IF( DEFINED MOBILE )
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
		${CAPI_LIB}
	capi-appfw-application
	glib-2.0
	capi-system-info
	elementary
	dlog
)
ENDIF()

IF( DEFINED TIZENIOT )
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
		${CAPI_LIB}
	capi-appfw-application
	glib-2.0
	capi-system-info
	elementary
	dlog
)
ENDIF()

IF( DEFINED TV )
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
		${CAPI_LIB}
	capi-appfw-application
	glib-2.0
	capi-system-info
	elementary
	dlog
)
ENDIF()

IF( DEFINED WEARABLE )
PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
	${CAPI_LIB}
	capi-appfw-application
	glib-2.0
	capi-system-info
	elementary
	dlog
)
ENDIF()

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

