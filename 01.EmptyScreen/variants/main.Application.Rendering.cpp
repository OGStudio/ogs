FEATURE ogs.h/Include
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

FEATURE ogs.h/Setup
this->setupRendering();

FEATURE ogs.h/TearDown
this->tearRenderingDown();

FEATURE ogs.h/Impl
private:
    osgViewer::Viewer *viewer;
    void setupRendering()
    {
        // Create OpenSceneGraph viewer.
        this->viewer = new osgViewer::Viewer;
        // Use single thread: CRITICAL for mobile and web because
        // there were are issues with multiple threads for OpenSceneGraph there.
        this->viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
        // Create manipulator: CRITICAL for mobile and web to focus on the
        // nodes in the scene.
        this->viewer->setCameraManipulator(new osgGA::TrackballManipulator);
    }
    void tearRenderingDown()
    {
        delete this->viewer;
    }
