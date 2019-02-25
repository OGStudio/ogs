FEATURE CMakeLists.txt/Impl
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
