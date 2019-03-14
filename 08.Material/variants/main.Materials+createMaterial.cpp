FEATURE ogs.h/Impl
public:
    osg::StateSet *createMaterial(const std::string &name)
    {
        auto material = new osg::StateSet;
        this->materials[name] = material;
        return material;
    }
