FEATURE CMakeLists.txt/Headers
# Include Lua headers.
INCLUDE_DIRECTORIES(${OGS_DIR}/../lua/src)
# Include Sol2 headers.
INCLUDE_DIRECTORIES(${OGS_DIR}/../sol2)

FEATURE CMakeLists.txt/Impl
ADD_LIBRARY(lua STATIC lua.c)

FEATURE CMakeLists.txt/Link
    lua
