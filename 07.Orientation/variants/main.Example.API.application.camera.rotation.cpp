FEATURE ogs.h/Setup
this->app->registerScriptCallback(
    "application.camera.rotation",
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

            // Apply rotation.
            osg::Vec3d rot = {
                atof(values[0].c_str()),
                atof(values[1].c_str()),
                atof(values[2].c_str()),
            };
            q = scene::degreesToQuaternion(rot);
            manipulator->setTransformation(pos, q);
        }

        // Return current position for Get and after Set.
        manipulator->getTransformation(pos, q);
        auto rot = scene::quaternionToDegrees(q);
        return std::vector<std::string>({
            format::printfString("%f", rot.x()),
            format::printfString("%f", rot.y()),
            format::printfString("%f", rot.z()),
        });
    )
);
