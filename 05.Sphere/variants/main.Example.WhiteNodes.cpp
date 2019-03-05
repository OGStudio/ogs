FEATURE ogs.h/Setup
this->setupWhiteNodes();

FEATURE ogs.h/Impl
private:
    void setupWhiteNodes()
    {
        // Create material that paints every scene node in white.
        const std::string vertexShader = R"(
			void main()
			{
				// Pass vertex to fragment shader.
				// Convert from Model/Object space to Screen one.
				gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
			}
        )";
        const std::string fragmentShader = R"(
            void main()
            {
                // Paint scene nodes in white.
                gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
            }
        )";

        auto prog = render::createShaderProgram(vertexShader, fragmentShader);
        osg::ref_ptr<osg::StateSet> material = new osg::StateSet;
        material->setAttribute(prog);

        // Apply material to the whole scene.
        auto root = this->app->nodes->node("root");
        root->setStateSet(material);
    }
