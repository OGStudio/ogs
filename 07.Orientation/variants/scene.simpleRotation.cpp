FEATURE ogs.h/Include
#include <osg/MatrixTransform>

FEATURE ogs.h/Impl
//! Get node rotation.
osg::Vec3f simpleRotation(osg::MatrixTransform *node)
{
    auto quat = node->getMatrix().getRotate();
    return quaternionToDegrees(quat);
}

//! Set node rotation.
void setSimpleRotation(osg::MatrixTransform *node, const osg::Vec3f &rotation)
{
    osg::Quat quat = degreesToQuaternion(rotation);
    node->setMatrix(
        osg::Matrix::scale(node->getMatrix().getScale()) *
        osg::Matrix::rotate(quat) *
        osg::Matrix::translate(node->getMatrix().getTrans())
    );
}
