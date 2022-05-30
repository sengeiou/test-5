SET(PKG_NAME "base-utils")

SET(EXEC_NAME "tct-${PKG_NAME}-native")
SET(RPM_NAME "native-${PKG_NAME}-itc")

SET(CAPI_LIB "capi-base-utils-i18n")
SET(TC_SOURCES
    ITs-base-utils-common.c
	ITs-base-utils-ubrk.c
	ITs-base-utils-ucalendar.c
	ITs-base-utils-udate.c
	ITs-base-utils-udatepg.c
	ITs-base-utils-uenumeration.c
	ITs-base-utils-uset.c
	ITs-base-utils-unumber.c
	ITs-base-utils-ulocale.c
	ITs-base-utils-timezone.c
	ITs-base-utils-date-interval.c
	ITs-base-utils-date-interval-format.c
	ITs-base-utils-uchar.c
	ITs-base-utils-ucollator.c
	ITs-base-utils-unormalization.c
	ITs-base-utils-usearch.c
	ITs-base-utils-ustring.c
	ITs-base-utils-field-position.c
	ITs-base-utils-format.c
	ITs-base-utils-measure.c
	ITs-base-utils-measure-format.c
	ITs-base-utils-measure-unit.c
	ITs-base-utils-parse-position.c
	ITs-base-utils-alpha-idx.c
	ITs-base-utils-formattable.c
	ITs-base-utils-utmscale.c
	ITs-base-utils-ubidi.c
	ITs-base-utils-uchar-iter.c
	ITs-base-utils-uversion.c
	ITs-base-utils-plural-rules.c
	ITs-base-utils-immutable-idx.c
	ITs-base-utils-plural-format.c
	ITs-base-utils-simple-date-format.c
	ITs-base-utils-loc-disp-names.c
        ITs-base-utils-utext.c
        ITs-base-utils-uscript.c
        ITs-base-utils-unumsys.c
        ITs-base-utils-uidna.c
        ITs-base-utils-ucsdet.c
        ITs-base-utils-ucnvsel.c
        ITs-base-utils-ucnv.c
        ITs-base-utils-ures.c
)

PKG_CHECK_MODULES(${CAPI_LIB} REQUIRED
    ${CAPI_LIB}
	capi-appfw-application
	capi-appfw-common
    bundle
	glib-2.0
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
