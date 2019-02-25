FEATURE ogs.h/Setup
struct Example
{
    Application *app;

    typedef std::map<std::string, std::string> Parameters;

    Example(const Parameters &parameters)
    {
        this->app = new Application(EXAMPLE_TITLE);

FEATURE ogs.h/TearDown
    }
    ~Example()
    {

FEATURE ogs.h/Impl
        delete this->app;
    }

FEATURE ogs.h/End
};
