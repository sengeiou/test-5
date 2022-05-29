SET(PKG_NAME "dali-core")

SET(EXEC_NAME "tct-${PKG_NAME}-core")
SET(RPM_NAME "core-${PKG_NAME}-tests")

SET(CAPI_LIB "glib-2.0 capi-appfw-application capi-system-info dali-core dali-adaptor dali-toolkit storage bundle")
SET(TC_SOURCES
property-notification/utc-dali-property-notification.cpp
property-notification/utc-dali-property-notification-common.cpp
path/utc-dali-path.cpp
path/utc-dali-path-common.cpp
linear-constrainer/utc-dali-linear-constrainer.cpp
linear-constrainer/utc-dali-linear-constrainer-common.cpp
key-frames/utc-dali-key-frames.cpp
key-frames/utc-dali-key-frames-common.cpp
constraint-source/utc-dali-constraint-source.cpp
constraint-source/utc-dali-constraint-source-common.cpp
constraints/utc-dali-constraints.cpp
constraints/utc-dali-constraints-common.cpp
constraint/utc-dali-constraint.cpp
constraint/utc-dali-constraint-common.cpp
animation/utc-dali-animation.cpp
animation/utc-dali-animation-common.cpp
render-task-list/utc-dali-render-task-list.cpp
render-task-list/utc-dali-render-task-list-common.cpp
render-task/utc-dali-render-task.cpp
render-task/utc-dali-render-task-common.cpp
handle/utc-dali-handle.cpp
handle/utc-dali-handle-common.cpp
property-value/utc-dali-property-value.cpp
property-value/utc-dali-property-value-common.cpp
property-notification/utc-dali-property-notification.cpp
property-notification/utc-dali-property-notification-common.cpp
property-condition/utc-dali-property-condition.cpp
property-condition/utc-dali-property-condition-common.cpp
property-map/utc-dali-property-map.cpp
property-map/utc-dali-property-map-common.cpp
property-array/utc-dali-property-array.cpp
property-array/utc-dali-property-array-common.cpp
property-types/utc-dali-property-types.cpp
property-types/utc-dali-property-types-common.cpp
base-handle/utc-dali-base-handle.cpp
base-handle/utc-dali-base-handle-common.cpp
ref-object/utc-dali-refobject.cpp
ref-object/utc-dali-refobject-common.cpp
type-registry/utc-dali-type-registry.cpp
type-registry/utc-dali-type-registry-common.cpp
property/utc-dali-property.cpp
property/utc-dali-property-common.cpp
type-info/utc-dali-type-info.cpp
type-info/utc-dali-type-info-common.cpp
time-period/utc-dali-time-period.cpp
time-period/utc-dali-time-period-common.cpp
callback/utc-dali-callback.cpp
callback/utc-dali-callback-common.cpp
stage/utc-dali-stage.cpp
stage/utc-dali-stage-common.cpp
alpha-function/utc-dali-alpha-function.cpp
alpha-function/utc-dali-alpha-function-common.cpp
encoded-buffer-image/utc-dali-encoded-buffer-image.cpp
encoded-buffer-image/utc-dali-encoded-buffer-image-common.cpp
buffer-image/utc-dali-buffer-image.cpp
buffer-image/utc-dali-buffer-image-common.cpp
frame-buffer-image/utc-dali-frame-buffer-image.cpp
frame-buffer-image/utc-dali-frame-buffer-image-common.cpp
image/utc-dali-image.cpp
image/utc-dali-image-common.cpp
resource-image/utc-dali-resource-image.cpp
resource-image/utc-dali-resource-image-common.cpp
native-image/utc-dali-native-image.cpp
native-image/utc-dali-native-image-common.cpp
intrusive-ptr/utc-dali-intrusive-ptr.cpp
intrusive-ptr/utc-dali-intrusive-ptr-common.cpp
pixel/utc-dali-pixel.cpp
pixel/utc-dali-pixel-common.cpp
any/utc-dali-any.cpp
any/utc-dali-any-common.cpp
camera-actor/utc-dali-camera-actor.cpp
camera-actor/utc-dali-camera-actor-common.cpp
custom-actor/utc-dali-custom-actor.cpp
custom-actor/utc-dali-custom-actor-common.cpp
object-registry/utc-dali-object-registry.cpp
object-registry/utc-dali-object-registry-common.cpp
base-object/utc-dali-base-object.cpp
base-object/utc-dali-base-object-common.cpp
custom-actor-impl/utc-dali-custom-actor-impl.cpp
custom-actor-impl/utc-dali-custom-actor-impl-common.cpp
actor/utc-dali-actor.cpp
actor/utc-dali-actor-common.cpp
layer/utc-dali-layer.cpp
layer/utc-dali-layer-common.cpp
vector2/utc-dali-vector2.cpp
vector2/utc-dali-vector2-common.cpp
vector3/utc-dali-vector3.cpp
vector3/utc-dali-vector3-common.cpp
vector4/utc-dali-vector4.cpp
vector4/utc-dali-vector4-common.cpp
angle-axis/utc-dali-angle-axis.cpp
angle-axis/utc-dali-angle-axis-common.cpp
degree/utc-dali-degree.cpp
degree/utc-dali-degree-common.cpp
math-utils/utc-dali-math-utils.cpp
math-utils/utc-dali-math-utils-common.cpp
uint16-pair/utc-dali-uint16-pair.cpp
uint16-pair/utc-dali-uint16-pair-common.cpp
rect/utc-dali-rect.cpp
rect/utc-dali-rect-common.cpp
random/utc-dali-random.cpp
random/utc-dali-random-common.cpp
matrix/utc-dali-matrix.cpp
matrix/utc-dali-matrix-common.cpp
matrix3/utc-dali-matrix3.cpp
matrix3/utc-dali-matrix3-common.cpp
quaternion/utc-dali-quaternion.cpp
quaternion/utc-dali-quaternion-common.cpp
radian/utc-dali-radian.cpp
radian/utc-dali-radian-common.cpp
sampling/utc-dali-sampling-common.cpp
sampling/utc-dali-sampling.cpp
vector/utc-dali-vector.cpp
vector/utc-dali-vector-common.cpp
constraint-function/utc-dali-constraint-function.cpp
vector-base/utc-dali-vector-base.cpp
vector-base/utc-dali-vector-base-common.cpp
exception/utc-dali-exception.cpp
exception/utc-dali-exception-common.cpp
connection-tracker/utc-dali-connection-tracker.cpp
connection-tracker/utc-dali-connection-tracker-common.cpp
frame-buffer/utc-frame-buffer-common.cpp
frame-buffer/utc-frame-buffer.cpp
geometry/utc-geometry-common.cpp
geometry/utc-geometry.cpp
pixel-data/utc-pixeldata-common.cpp
pixel-data/utc-pixeldata.cpp
property-buffer/utc-propertybuffer-common.cpp
property-buffer/utc-propertybuffer.cpp
renderer/utc-renderer-common.cpp
renderer/utc-renderer.cpp
sampler/utc-sampler-common.cpp
sampler/utc-sampler.cpp
shader/utc-shader-common.cpp
shader/utc-shader.cpp
texture-set/utc-textureset-common.cpp
texture-set/utc-textureset.cpp
texture/utc-texture-common.cpp
texture/utc-texture.cpp
events/utc-dali-key-event.cpp
weakhandle-base/utc-dali-weakhandle-base.cpp
extents/utc-dali-extents.cpp
extents/utc-dali-extents-common.cpp
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
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fPIE -Wall")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=/usr/lib -pie")
SET(EXE_DALI_CORE_CTS_LINKER_FLAGS "-L${${CAPI_LIB}_LIBRARY_DIRS} -ldali-core -ldali-adaptor ")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXE_DALI_CORE_CTS_LINKER_FLAGS}")
ENDIF()


