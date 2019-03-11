FEATURE ogs.h/Include
#include <osgGA/TrackballManipulator>

FEATURE ogs.h/Setup
this->setupCameraManipulator();

FEATURE ogs.h/Impl
private:
    osg::ref_ptr<osgGA::TrackballManipulator> cameraManip;
    void setupCameraManipulator()
    {
        // Create manipulator: CRITICAL for mobile and web.
        this->cameraManip = new osgGA::TrackballManipulator;
        this->viewer->setCameraManipulator(this->cameraManip);

        // Reset camera rotation.
        osg::Vec3d pos;
        osg::Quat q;
        this->cameraManip->getTransformation(pos, q);
        osg::Vec3d rot(0, 0, 0);
        q = scene::degreesToQuaternion(rot);
        this->cameraManip->setTransformation(pos, q);
    }
public:
    osgGA::TrackballManipulator *cameraManipulator()
    {
        return this->cameraManip;
    }
