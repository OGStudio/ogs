FEATURE ogs.h/Setup
this->runBase64Script(parameters);

FEATURE ogs.h/Impl
private:
    void runBase64Script(const Parameters &parameters)
    {
        // Get base64 string from `base64script` command line argument.
        auto it = parameters.find("base64script");
        if (it == parameters.end())
        {
            return;
        }
        auto base64Script = it->second;

        auto script = format::base64Decode(base64Script);
        this->app->executeLuaScript("Base64", script);
    }
