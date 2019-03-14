FEATURE ogs.h/Impl
public:
    osg::StateSet *material(const std::string &name)
    {
        auto it = this->materials.find(name);
        if (it != this->materials.end())
        {
            return it->second.get();
        }

        return 0;
    }
