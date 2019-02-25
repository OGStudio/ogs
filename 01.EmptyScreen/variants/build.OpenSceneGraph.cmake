FEATURE CMakeLists.txt/Headers
# Include cross-platform headers.
INCLUDE_DIRECTORIES(${OGS_DIR}/../OpenSceneGraph)
INCLUDE_DIRECTORIES(${OGS_DIR}/../OpenSceneGraph/include)

FEATURE CMakeLists.txt/Link
    OpenSceneGraph
