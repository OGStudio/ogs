FEATURE ogs.h/Impl
#define SCRIPT_ENVIRONMENT_LOG_PREFIX "script::Environment(%p) %s"
#define SCRIPT_ENVIRONMENT_LOG(...) \
    log::logprintf( \
        SCRIPT_ENVIRONMENT_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
