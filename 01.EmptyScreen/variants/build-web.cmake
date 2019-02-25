FEATURE CMakeLists.txt/Flag
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

FEATURE CMakeLists.txt/End
# Convert build flags into a string.
STRING(REPLACE ";" " " BUILD_FLAGS "${BUILD_FLAGS}")
# Use build flags for complation and linking.
ADD_DEFINITIONS(${BUILD_FLAGS})
SET_TARGET_PROPERTIES(${BINARY_NAME} PROPERTIES LINK_FLAGS ${BUILD_FLAGS})
