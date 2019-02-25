FEATURE ogs.h/Include
#include <functional>

FEATURE ogs.h/Impl
//! Interface to scriptable entity represented in Lua.
class EnvironmentClient
{
    public:
        EnvironmentClient() : call(nullptr) { }
        ~EnvironmentClient() { }

        // 'call' method/callback:
        // * accepts key and a list of values
        // * returns a list of values
        typedef
            std::function<
                std::vector<std::string> (
                    const std::string &,
                    const std::vector<std::string> &
                )
            > CallbackCall;
        CallbackCall call;
};
