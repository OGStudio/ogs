FEATURE ogs.h/Impl
public:
    osg::MatrixTransform *node(const std::string &name)
    {
        auto it = this->nodes.find(name);

        // Return valid node.
        if (it != this->nodes.end())
        {
            return it->second.get();
        }

        // Found noting.
        return 0;
    }
