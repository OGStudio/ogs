// osgDB-02.
#include "src/osgDB/FileUtils.cpp"
// osgViewer.
#include "src/osgViewer/CompositeViewer.cpp"
#include "src/osgViewer/GraphicsWindow.cpp"
#include "src/osgViewer/Keystone.cpp"
#include "src/osgViewer/Renderer.cpp"
#include "src/osgViewer/Scene.cpp"
#include "src/osgViewer/View.cpp"
#include "src/osgViewer/ViewerBase.cpp"
#include "src/osgViewer/Viewer.cpp"
#include "src/osgViewer/config/AcrossAllScreens.cpp"
#include "src/osgViewer/config/SingleScreen.cpp"
#include "src/osgViewer/config/SingleWindow.cpp"
#include "src/osgViewer/config/SphericalDisplay.cpp"
#include "src/osgViewer/config/PanoramicSphericalDisplay.cpp"
#include "src/osgViewer/config/WoWVxDisplay.cpp"
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

