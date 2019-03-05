FEATURE ogs.h/Setup
this->setupRoot();

FEATURE ogs.h/Impl
private:
    void setupRoot()
    {
        auto root = new osg::MatrixTransform;
        this->nodes["root"] = root;
    }
