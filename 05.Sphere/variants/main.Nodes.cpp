FEATURE ogs.h/Include
#include <osg/MatrixTransform>

FEATURE ogs.h/Setup
class Nodes
{
    public:
        Nodes()
        {

FEATURE ogs.h/TearDown
        }
        ~Nodes()
        {

FEATURE ogs.h/Impl
        }

    private:
        std::map<std::string, osg::ref_ptr<osg::MatrixTransform> > nodes;

FEATURE ogs.h/End
};
