CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(tct_coreapi_itc)

INCLUDE(FindPkgConfig)
SET(BIN_DIR "/usr/apps/")

INCLUDE_DIRECTORIES(
	src/common
)

ADD_DEFINITIONS("-DRES_PATH=\"${RES_PATH}\"")

ADD_SUBDIRECTORY(src)
