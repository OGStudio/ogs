FEATURE ogs.h/Impl
#define MAIN_APPLICATION_LOG_PREFIX "main::Application(%p) %s"
#define MAIN_APPLICATION_LOG(...) \
    log::logprintf( \
        MAIN_APPLICATION_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
