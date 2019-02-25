FEATURE ogs.h/Setup
this->setupMouse();

FEATURE ogs.h/TearDown
this->tearMouseDown();

FEATURE ogs.h/Impl
public:
    osg::ref_ptr<input::Mouse> mouse;
private:
    void setupMouse()
    {
        // Create mouse events' handler.
        this->mouse = new input::Mouse;
        // Register it.
        this->viewer->addEventHandler(this->mouse);
    }
    void tearMouseDown()
    {
        // This also removes `mouse` instance.
        this->viewer->removeEventHandler(this->mouse);
    }
