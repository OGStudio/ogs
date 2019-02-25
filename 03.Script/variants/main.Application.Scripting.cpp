FEATURE ogs.h/Setup
this->setupScripting();

FEATURE ogs.h/TearDown
this->tearScriptingDown();

FEATURE ogs.h/Impl
private:
    script::Environment *environment;
    std::vector<script::EnvironmentClient *> clients;

    void setupScripting()
    {
        this->environment = new script::Environment;

        // Register Environment instance.
        (*this->lua)["ENV"] = this->environment;

        // Register Environment class.
        this->lua->new_usertype<script::Environment>(
            "Environment",
            // 'setVerbose' method.
            "setVerbose",
            [](script::Environment &env, bool state)
            {
                env.setVerbose(state);
            },
            // 'addClient' method.
            "addClient",
            [](script::Environment &env, script::EnvironmentClient *client, sol::nested<std::vector<std::string> > keys)
            {
                env.addClient(client, keys);
            },
            // 'call' method.
            "call",
            [](script::Environment &env, const std::string &key, sol::nested<std::vector<std::string> > values)
            {
                return env.call(key, values);
            }
        );

        // Register EnvironmentClient class.
        this->lua->new_usertype<script::EnvironmentClient>(
            "EnvironmentClient",
            // 'call' method.
            "call",
            sol::property(
                [](script::EnvironmentClient &ec, sol::function luaCallback)
                {
                    ec.call =
                        SCRIPT_ENVIRONMENT_CLIENT_CALL(
                            sol::nested<std::vector<std::string> > result =
                                luaCallback(key, sol::as_table(values));
                            return std::move(result.source);
                        );
                }
            )
        );
    }
    void tearScriptingDown()
    {
        delete this->environment;
    }
public:
    void registerScriptCallback(
        const std::string &key,
        script::EnvironmentClient::CallbackCall callback
    ) {
        auto client = new script::EnvironmentClient;
        client->call = callback;
        this->clients.push_back(client);
        this->environment->addClient(client, {key});
    }
