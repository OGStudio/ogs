FEATURE ogs.h/Setup
this->app->registerScriptCallback(
    "application.camera.nodeAtPosition",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        // Make sure there are three components.
        if (values.size() != 3)
        {
            MAIN_EXAMPLE_LOG(
                "ERROR Could not set value for key '%s' "
                "because values' count is not 3"
            );
            return std::vector<std::string>();
        }

        osg::Vec2d position = {
            atof(values[0].c_str()),
            atof(values[1].c_str()),
        };
        int selectionMask = atoi(values[2].c_str());

        // Locate a node.
        auto node =
            scene::nodeAtPosition(
                position,
                this->app->camera(),
                selectionMask
            );

        // Return the name of the node if it exists.
        if (node)
        {
            return std::vector<std::string>({
                node->getName()
            });
        }

        // Return nothing otherwise.
        return std::vector<std::string>();
    )
);
