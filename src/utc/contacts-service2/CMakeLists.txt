SET(PKG_NAME "contacts-service2")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "contacts-service2")
SET(TC_SOURCES
	utc-contacts-service-tc-utils.c
	utc-contacts-service-db-phone-log.c
	utc-contacts-service-db-url.c
	utc-contacts-service-db-contact.c
	utc-contacts-service-db-grouprel-updated-info.c
	utc-contacts-service-db-nickname.c
	utc-contacts-service-db-company.c
	utc-contacts-service-db-group.c
	utc-contacts-service-db-phone-log-stat.c
	utc-contacts-service-db-sdn.c
	utc-contacts-service-db-person-usage.c
	utc-contacts-service-db-address-book.c
	utc-contacts-service-db-profile.c
	utc-contacts-service-db-my-profile-updated-info.c
	utc-contacts-service-db-number.c
	utc-contacts-service-db-email.c
	utc-contacts-service-db-name.c
	utc-contacts-service-db-extension.c
	utc-contacts-service-db-speeddial.c
	utc-contacts-service-db-event.c
	utc-contacts-service-db-person.c
	utc-contacts-service-db-my-profile.c
	utc-contacts-service-db-group-updated-info.c
	utc-contacts-service-db-image.c
	utc-contacts-service-db-messenger.c
	utc-contacts-service-db-group-member-updated-info.c
	utc-contacts-service-db-contact-updated-info.c
	utc-contacts-service-db-activity-photo.c
	utc-contacts-service-db-relationship.c
	utc-contacts-service-db-note.c
	utc-contacts-service-db-group-relation.c
	utc-contacts-service-db-simple-contact.c
	utc-contacts-service-db-address.c
	utc-contacts-service-db-activity.c
	utc-contacts-service-db-sip.c
	utc-contacts-service-record-url.c
	utc-contacts-service-record-relationship.c
	utc-contacts-service-record-person.c
	utc-contacts-service-record-number.c
	utc-contacts-service-record-my-profile.c
	utc-contacts-service-record-speeddial.c
	utc-contacts-service-record-image.c
	utc-contacts-service-record-activity-photo.c
	utc-contacts-service-record-company.c
	utc-contacts-service-record-name.c
	utc-contacts-service-record-email.c
	utc-contacts-service-record-group.c
	utc-contacts-service-record-extension.c
	utc-contacts-service-record-profile.c
	utc-contacts-service-record-address-book.c
	utc-contacts-service-record-nickname.c
	utc-contacts-service-record-activity.c
	utc-contacts-service-record-contact.c
	utc-contacts-service-record-sdn.c
	utc-contacts-service-record-event.c
	utc-contacts-service-record-group-relation.c
	utc-contacts-service-record-address.c
	utc-contacts-service-record-note.c
	utc-contacts-service-record-phone-log.c
	utc-contacts-service-record-messenger.c
	utc-contacts-service-record-contact-updated-info.c
	utc-contacts-service-record-my-profile-updated-info.c
	utc-contacts-service-record-group-updated-info.c
	utc-contacts-service-record-group-member-updated-info.c
	utc-contacts-service-record-grouprel-updated-info.c
	utc-contacts-service-record-phone-log-stat.c
	utc-contacts-service-record-sip.c
	utc-contacts-service-sevice.c
	utc-contacts-service-filter.c
	utc-contacts-service-person.c
	utc-contacts-service-group.c
	utc-contacts-service-sim.c
	utc-contacts-service-setting.c
	utc-contacts-service-vcard.c
	utc-contacts-service-sdn.c
	utc-contacts-service-list.c
	utc-contacts-service-db.c
	utc-contacts-service-db-status.c
	utc-contacts-service-query.c
	utc-contacts-service-record.c
	utc-contacts-service-activity.c
	utc-contacts-service-phone-log.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	capi-system-info
	accounts-svc
	storage
	glib-2.0
	dlog elementary
	capi-telephony
	)

INCLUDE_DIRECTORIES(
    ${${CAPI_LIB}_INCLUDE_DIRS}
)

ADD_EXECUTABLE(${EXEC_NAME} ${EXEC_NAME}.c ${TC_SOURCES} ${COMMON_FILE})
TARGET_LINK_LIBRARIES(${EXEC_NAME}
    ${${CAPI_LIB}_LIBRARIES}
    pthread
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

