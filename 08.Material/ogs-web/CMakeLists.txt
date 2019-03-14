CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(OGS)
# Path to `ogs` distribution directory.
SET(OGS_DIR ${CMAKE_SOURCE_DIR}/../../../ogs)

SET(STAGE_ID "08")
SET(STAGE ${STAGE_ID}.Material)

SET(BINARY_NAME "ogs-${STAGE_ID}")
# Create and link executable.
ADD_EXECUTABLE(${BINARY_NAME} ogs.cpp)
# Use C++14.
TARGET_COMPILE_OPTIONS(${BINARY_NAME} PUBLIC "-std=c++14")

# Include cross-platform headers.
INCLUDE_DIRECTORIES(${OGS_DIR}/../OpenSceneGraph)
INCLUDE_DIRECTORIES(${OGS_DIR}/../OpenSceneGraph/include)

# Include Lua headers.
INCLUDE_DIRECTORIES(${OGS_DIR}/../lua/src)
# Include Sol2 headers.
INCLUDE_DIRECTORIES(${OGS_DIR}/../sol2)

# Include web specific headers.
INCLUDE_DIRECTORIES(${OGS_DIR}/OpenSceneGraph/include/web)
ADD_LIBRARY(
    OpenSceneGraph
    STATIC
    OpenSceneGraph-01.cpp
    OpenSceneGraph-02.cpp
    OpenSceneGraph-03.cpp
    OpenSceneGraph-04.cpp
)
TARGET_LINK_LIBRARIES(
    OpenSceneGraph
    # for OpenThreads:
    pthread 
    # for osgViewer:
    EGL
)
ADD_LIBRARY(lua STATIC lua.c)


TARGET_LINK_LIBRARIES(
    ${BINARY_NAME}

    OpenSceneGraph
    lua
)

# Make Emscripten generate ready-to-open HTML page.
SET(CMAKE_EXECUTABLE_SUFFIX ".html")

# Construct build flags for web.
SET(BUILD_FLAGS "")
# Make compact binary.
LIST(APPEND BUILD_FLAGS "-O3")
# Use SDL2 as OpenGL provider.
LIST(APPEND BUILD_FLAGS "-s USE_SDL=2")
# Disable web assembly because it's too new.
LIST(APPEND BUILD_FLAGS "-s WASM=0")

# Enable exceptions for Sol.
LIST(APPEND BUILD_FLAGS "-s DISABLE_EXCEPTION_CATCHING=0")
# Convert build flags into a string.
STRING(REPLACE ";" " " BUILD_FLAGS "${BUILD_FLAGS}")
# Use build flags for complation and linking.
ADD_DEFINITIONS(${BUILD_FLAGS})
SET_TARGET_PROPERTIES(${BINARY_NAME} PROPERTIES LINK_FLAGS ${BUILD_FLAGS})
