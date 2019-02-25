FEATURE ogs.h/Impl
public:
    void run()
    {
        while (!this->viewer->done())
        {
            this->frame();
        }
    }
