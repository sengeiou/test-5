SET(PKG_NAME "base-utils")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "capi-base-utils-i18n")
SET(TC_SOURCES
    utc-capi-base-utils-ucalendar.c
    utc-capi-base-utils-udate.c
    utc-capi-base-utils-udatepg.c
    utc-capi-base-utils-uenumeration.c
    utc-capi-base-utils-ulocale.c
    utc-capi-base-utils-unumber.c
    utc-capi-base-utils-uset.c
    utc-capi-base-utils-timezone.c
    utc-capi-base-utils-ubrk.c
    utc-capi-base-utils-uchar.c
    utc-capi-base-utils-ucollator.c
    utc-capi-base-utils-unormalization.c
    utc-capi-base-utils-usearch.c
    utc-capi-base-utils-ustring.c
    utc-capi-base-utils-formattable.c
    utc-capi-base-utils-measure-unit.c
    utc-capi-base-utils-measure.c
    utc-capi-base-utils-measure-format.c
    utc-capi-base-utils-format.c
    utc-capi-base-utils-parse-position.c
    utc-capi-base-utils-field-position.c
    utc-capi-base-utils-alpha-idx.c
    utc-capi-base-utils-ushape.c
    utc-capi-base-utils-utmscale.c
    utc-capi-base-utils-ubidi.c
    utc-capi-base-utils-uversion.c
    utc-capi-base-utils-uchar_iter.c
    utc-capi-base-utils-plural-rules.c
    utc-capi-base-utils-plural-format.c
    utc-capi-base-utils-immutable-idx.c
    utc-capi-base-utils-date-interval.c
    utc-capi-base-utils-date-interval-format.c
    utc-capi-base-utils-simple-date-format.c
    utc-capi-base-utils-loc-disp-names.c
    utc-capi-base-utils-utext.c
    utc-capi-base-utils-uscript.c
    utc-capi-base-utils-unumsys.c
    utc-capi-base-utils-uidna.c
    utc-capi-base-utils-ucsdet.c
    utc-capi-base-utils-ucnvsel.c
    utc-capi-base-utils-ucnv.c
    utc-capi-base-utils-ures.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	capi-appfw-app-common
	capi-system-info
    glib-2.0
    bundle
    dlog
)

INCLUDE_DIRECTORIES(
    ${${CAPI_LIB}_INCLUDE_DIRS}
)

ADD_EXECUTABLE(${EXEC_NAME} ${EXEC_NAME}.c ${TC_SOURCES} ${COMMON_FILE})
TARGET_LINK_LIBRARIES(${EXEC_NAME}
    ${${CAPI_LIB}_LIBRARIES}
)

MESSAGE("EXEC ${EXEC_NAME}")
MESSAGE("BIN_DIR ${BIN_DIR}")

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
