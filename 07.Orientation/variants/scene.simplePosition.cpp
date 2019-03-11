FEATURE ogs.h/Include
#include <osg/MatrixTransform>

FEATURE ogs.h/Impl
//! Get node position.
//! NOTE Only works for non-rotated/scaled nodes.
osg::Vec3f simplePosition(osg::MatrixTransform *node)
{
    return node->getMatrix().getTrans();
}

//! Set node position.
//! NOTE Only works for non-rotated/scaled nodes.
void setSimplePosition(osg::MatrixTransform *node, const osg::Vec3f &position)
{
    auto matrix = node->getMatrix();
    node->setMatrix(
        osg::Matrix::scale(matrix.getScale()) *
        osg::Matrix::rotate(matrix.getRotate()) *
        osg::Matrix::translate(position)
    );
}
