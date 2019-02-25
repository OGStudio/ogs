FEATURE ogs.h/Setup
this->app->registerScriptCallback(
    "application.camera.clearColor",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        auto camera = this->app->camera();
        // Set.
        if (!values.empty())
        {
            // Report error if values' count is insufficient.
            if (values.size() != 3)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 3"
                );
            }
            // Apply color otherwise.
            else
            {
                auto color = camera->getClearColor();
                color.r() = atof(values[0].c_str());
                color.g() = atof(values[1].c_str());
                color.b() = atof(values[2].c_str());
                camera->setClearColor(color);
            }
        }

        // Return current color for Get and after Set.
        auto color = camera->getClearColor();
        return std::vector<std::string>({
            format::printfString("%f", color.r()),
            format::printfString("%f", color.g()),
            format::printfString("%f", color.b()),
        });
    )
);
