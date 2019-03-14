FEATURE ogs.h/Setup
this->app->registerScriptCallback(
    "application.materials.material.setUniform",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        // Set.
        if (!values.empty())
        {
            // Make sure there are at least three components.
            if (values.size() < 3)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is less than 3",
                    key.c_str()
                );
                return std::vector<std::string>();
            }

            auto materialName = values[0];
            auto uniformName = values[1];

            // We only support vec3 values.
            // TODO Support other values, too.
            if (values.size() != 5)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Cannot set value for uniform '%s' of material '%s' "
                    "because we only support vec3 values for now",
                    uniformName.c_str(),
                    materialName.c_str()
                );
                return std::vector<std::string>();
            }

            auto material = this->app->materials->material(materialName);

            // Make sure material exists.
            if (!material)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not uniform '%s' for material '%s' "
                    "because material does not exist",
                    uniformName.c_str(),
                    materialName.c_str()
                );
                return std::vector<std::string>();
            }

            osg::Uniform *uniform =
                material->getOrCreateUniform(
                    uniformName,
                    osg::Uniform::FLOAT_VEC3
                );
            osg::Vec3 vector(
                atof(values[2].c_str()),
                atof(values[3].c_str()),
                atof(values[4].c_str())
            );
            uniform->set(vector);
        }

        return std::vector<std::string>();
    )
);
