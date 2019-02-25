FEATURE CMakeLists.txt/Impl
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
