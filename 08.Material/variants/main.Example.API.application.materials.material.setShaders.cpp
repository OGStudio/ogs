FEATURE ogs.h/Setup
this->app->registerScriptCallback(
    "application.materials.material.setShaders",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        // Set.
        if (!values.empty())
        {
            // Make sure there are 3 components.
            if (values.size() != 3)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 3",
                    key.c_str()
                );
                return std::vector<std::string>();
            }

            auto materialName = values[0];
            auto vertexShader = values[1];
            auto fragmentShader = values[2];

            auto material = this->app->materials->material(materialName);

            // Make sure material exist.
            if (!material)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set vertex shader(%lld) and fragment "
                    "shader(%lld)' for material '%s' "
                    "because material does not exist",
                    vertexShader.length(),
                    fragmentShader.length(),
                    materialName.c_str()
                );
                return std::vector<std::string>();
            }

            // Apply.
            auto prog =
                render::createShaderProgram(vertexShader, fragmentShader);
            material->setAttribute(prog);
        }

        return std::vector<std::string>();
    )
);
