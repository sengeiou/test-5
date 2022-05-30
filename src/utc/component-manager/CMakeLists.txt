SET(PKG_NAME "component-manager")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "capi-appfw-component-manager")

SET(TC_SOURCES
	utc_common.c
	tct-component-manager-core.c
	utc_component_context_clone.c
	utc_component_context_destroy.c
	utc_component_context_get_app_id.c
	utc_component_context_get_component_id.c
	utc_component_context_get_component_state.c
	utc_component_context_get_instance_id.c
	utc_component_context_is_subcomponent.c
	utc_component_context_is_terminated.c
	utc_component_info_clone.c
	utc_component_info_create.c
	utc_component_info_destroy.c
	utc_component_info_get_app_id.c
	utc_component_info_get_component_id.c
	utc_component_info_get_component_type.c
	utc_component_info_get_icon.c
	utc_component_info_get_label.c
	utc_component_info_get_localized_label.c
	utc_component_info_is_icon_display.c
	utc_component_info_is_managed_by_task_manager.c
	utc_component_manager_foreach_component_context.c
	utc_component_manager_foreach_component_info.c
	utc_component_manager_get_component_context.c
	utc_component_manager_get_component_info.c
	utc_component_manager_is_running.c
	utc_component_manager_resume_component.c
	utc_component_manager_terminate_bg_component.c
	)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
	${CAPI_LIB}
	capi-appfw-application
	capi-system-info
	glib-2.0
	bundle
	dlog
	elementary
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
