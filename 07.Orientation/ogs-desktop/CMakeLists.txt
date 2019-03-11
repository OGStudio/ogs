CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(OGS)
# Path to `ogs` distribution directory.
SET(OGS_DIR ${CMAKE_SOURCE_DIR}/../../../ogs)

SET(STAGE_ID "07")
SET(STAGE ${STAGE_ID}.Orientation)

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

# Build OpenSceneGraph for macOS.
IF (APPLE)
    # Include macOS specific headers.
    INCLUDE_DIRECTORIES(${OGS_DIR}/OpenSceneGraph/include/macos)
    ADD_LIBRARY(
        OpenSceneGraph
        STATIC
        OpenSceneGraph-01.cpp
        OpenSceneGraph-02.cpp
        OpenSceneGraph-03.cpp
        OpenSceneGraph-04.mm
    )
    TARGET_LINK_LIBRARIES(
        OpenSceneGraph
        # for OpenThreads:
        pthread 
        # for osgViewer:
        "-framework Accelerate"
        "-framework Foundation"
        "-framework Cocoa"
        "-framework ImageIO"
        "-framework OpenGL"
    )
# Build OpenSceneGraph for Linux.
ELSE()
    # Include Linux specific headers.
    INCLUDE_DIRECTORIES(${OGS_DIR}/OpenSceneGraph/include/linux)
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
        # For osgDB:
        dl
        # For OpenThreads:
        pthread
        # For osgViewer:
        GL
        X11
    )
ENDIF ()
ADD_LIBRARY(lua STATIC lua.c)


TARGET_LINK_LIBRARIES(
    ${BINARY_NAME}

    OpenSceneGraph
    lua
)

