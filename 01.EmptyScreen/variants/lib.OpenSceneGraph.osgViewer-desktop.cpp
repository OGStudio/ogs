FEATURE OpenSceneGraph-04.cpp/Src
// macOS.
#ifdef __APPLE__
    #define USE_DARWIN_COCOA_IMPLEMENTATION
    #include "src/osgViewer/DarwinUtils.mm"
    #include "src/osgViewer/GraphicsWindowCocoa.mm"
    #include "src/osgViewer/PixelBufferCocoa.mm"
// Linux.
#else
    #include "src/osgViewer/GraphicsWindowX11.cpp"
    #include "src/osgViewer/PixelBufferX11.cpp"
#endif

FEATURE OpenSceneGraph-04.mm/Src
#include "OpenSceneGraph-04.cpp"
