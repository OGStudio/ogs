FEATURE ogs.h/Setup
this->app->registerScriptCallback(
    "application.nodes.node.setMaterial",
    SCRIPT_ENVIRONMENT_CLIENT_CALL(
        // Set.
        if (!values.empty())
        {
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

            // Nil material is allowed.
            std::string materialName = "(nil)";
            osg::StateSet *material = 0;
            if (values.size() == 2)
            {
                materialName = values[1];
                material = this->app->materials->material(materialName);
            }

            // Make sure node exists.
            if (!node)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set material '%s' for node '%s' "
                    "because node does not exist",
                    materialName.c_str(),
                    nodeName.c_str()
                );
                return std::vector<std::string>();
            }

            // Apply.
            node->setStateSet(material);
        }

        return std::vector<std::string>();
    )
);
