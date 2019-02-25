FEATURE OpenSceneGraph-03.cpp/Src
// NOTE This is a fake osg::Billboard implementation
// NOTE to be able to build OpenSceneGraph without additional patching.

#include <osg/Billboard>

namespace osg
{

Billboard::Billboard()
{
    OSG_WARN << "osg::Billboard is not implemented\n";
}
Billboard::Billboard(const Billboard &, const CopyOp &)
{
    OSG_WARN << "osg::Billboard is not implemented\n";
}
Billboard::~Billboard() { } 
void Billboard::setAxis(const Vec3 &) { }
void Billboard::setNormal(const Vec3 &) { }
void Billboard::setMode(Mode mode) {}
bool Billboard::addDrawable(Drawable *)
{
    return false;
}
bool Billboard::addDrawable(Drawable *, const Vec3 &)
{
    return false;
}
bool Billboard::removeDrawable(Drawable *)
{
    return false;
}
BoundingSphere Billboard::computeBound() const
{
    BoundingSphere bsphere;
    return bsphere;
}
bool Billboard::computeMatrix(Matrix &, const Vec3 &, const Vec3 &) const
{
    return false;
}

} // namespace osg
