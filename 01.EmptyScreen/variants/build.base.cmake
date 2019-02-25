FEATURE CMakeLists.txt/Begin
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(OGS)
# Path to `ogs` distribution directory.
SET(OGS_DIR ${CMAKE_SOURCE_DIR}/../../../ogs)

FEATURE CMakeLists.txt/Lib
SET(BINARY_NAME "ogs-${STAGE_ID}")
# Create and link executable.
ADD_EXECUTABLE(${BINARY_NAME} ogs.cpp)
# Use C++14.
TARGET_COMPILE_OPTIONS(${BINARY_NAME} PUBLIC "-std=c++14")

FEATURE CMakeLists.txt/Link
TARGET_LINK_LIBRARIES(
    ${BINARY_NAME}

FEATURE CMakeLists.txt/End
)
