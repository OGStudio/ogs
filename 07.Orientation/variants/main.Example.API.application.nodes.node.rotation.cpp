FEATURE ogs.h/Setup
this->app->registerScriptCallback(
    "application.nodes.node.rotation",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        // Make sure there is at least one component.
        if (values.size() < 1)
        {
            MAIN_EXAMPLE_LOG(
                "ERROR Could not set value for key '%s' "
                "because values' count is less than 1",
                key.c_str()
            );
            return std::vector<std::string>();
        }

        auto nodeName = values[0];
        auto node = this->app->nodes->node(nodeName);

        // Make sure node exists.
        if (!node)
        {
            MAIN_EXAMPLE_LOG(
                "ERROR Could not get or set rotation for node '%s' "
                "because it does not exist",
                nodeName.c_str()
            );
            return std::vector<std::string>();
        }

        // Set.
        if (values.size() == 4)
        {
            osg::Vec3 rotation(
                atof(values[1].c_str()),
                atof(values[2].c_str()),
                atof(values[3].c_str())
            );
            scene::setSimpleRotation(node, rotation);
        }

        // Get.
        auto rotation = scene::simpleRotation(node);
        return std::vector<std::string>({
            format::printfString("%f", rotation.x()),
            format::printfString("%f", rotation.y()),
            format::printfString("%f", rotation.z()),
        });
    )
);
