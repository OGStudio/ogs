FEATURE ogs.h/Setup
this->app->registerScriptCallback(
    "application.camera.position",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        auto manipulator = this->app->cameraManipulator();
        osg::Vec3d pos;
        osg::Quat q;
        manipulator->getTransformation(pos, q);

        // Set.
        if (!values.empty())
        {
            // Make sure there are three components.
            if (values.size() != 3)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 3"
                );
                return std::vector<std::string>();
            }

            // Apply position.
            pos = {
                atof(values[0].c_str()),
                atof(values[1].c_str()),
                atof(values[2].c_str()),
            };
            manipulator->setTransformation(pos, q);
        }

        // Return current position for Get and after Set.
        manipulator->getTransformation(pos, q);
        return std::vector<std::string>({
            format::printfString("%f", pos.x()),
            format::printfString("%f", pos.y()),
            format::printfString("%f", pos.z()),
        });
    )
);
