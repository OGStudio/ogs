FEATURE ogs.h/Setup
this->app->registerScriptCallback(
    "application.nodes.node.setMask",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        // Make sure there are two components.
        if (values.size() != 2)
        {
            MAIN_EXAMPLE_LOG(
                "ERROR Could not set value for key '%s' "
                "because values' count is not 2"
            );
            return std::vector<std::string>();
        }

        auto name = values[0];
        auto node = this->app->nodes->node(name);

        // Make sure node exists.
        if (!node)
        {
            MAIN_EXAMPLE_LOG(
                "ERROR Could not set mask for node named '%s' because "
                "it does not exist",
                name.c_str()
            );
            return std::vector<std::string>();
        }

        // Set mask.
        int mask = atoi(values[1].c_str());
        node->setNodeMask(node->getNodeMask() & ~mask);

        return std::vector<std::string>();
    )
);
