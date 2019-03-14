FEATURE ogs.h/Setup
this->app->registerScriptCallback(
    "application.materials.createMaterial",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        // Set.
        if (!values.empty())
        {
            // Make sure there is one component.
            if (values.size() != 1)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 1"
                );
                return std::vector<std::string>();
            }

            // Create material.
            auto name = values[0];
            this->app->materials->createMaterial(name);
        }

        return std::vector<std::string>();
    )
);
