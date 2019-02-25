FEATURE ogs.h/Include
#include "api.lua.h"

FEATURE ogs.h/Setup
this->runEmbeddedAPIScript();

FEATURE ogs.h/Impl
private:
    void runEmbeddedAPIScript()
    {
        resource::Resource api("scripts", "api.lua", api_lua, api_lua_len);
        this->app->executeLuaScript("Embedded API", api.contents);
    }
