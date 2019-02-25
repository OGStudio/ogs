FEATURE ogs.h/Include
#include <sol.hpp>

FEATURE ogs.h/Setup
this->setupLua();

FEATURE ogs.h/TearDown
this->tearLuaDown();

FEATURE ogs.h/Impl
private:
    sol::state *lua;
    void setupLua()
    {
        this->lua = new sol::state;
        this->lua->open_libraries();
    }
    void tearLuaDown()
    {
        delete this->lua;
    }
public:
    void executeLuaScript(
        const std::string &name,
        const std::string &contents
    ) {
        try {
            this->lua->script(contents);
            MAIN_EXAMPLE_LOG(
                "Executed Lua script '%s'(%u)",
                name.c_str(),
                contents.size()
            );
        }
        catch (const std::exception &e)
        {
            MAIN_EXAMPLE_LOG(
                "ERROR Could not execute Lua script '%s'(%u): '%s'",
                name.c_str(),
                contents.size(),
                e.what()
            );
        }
    }
