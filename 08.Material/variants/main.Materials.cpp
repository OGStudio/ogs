FEATURE ogs.h/Setup
class Materials
{
    public:
        Materials()
        {

FEATURE ogs.h/TearDown
        }
        ~Materials()
        {

FEATURE ogs.h/Impl
        }

    private:
        std::map<std::string, osg::ref_ptr<osg::StateSet> > materials;

FEATURE ogs.h/End
};
