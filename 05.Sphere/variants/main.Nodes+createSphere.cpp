FEATURE ogs.h/Begin
public:
    osg::MatrixTransform *createSphere(
        const std::string &name,
        float radius
    ) {
        auto node = scene::createSphere(radius);
        node->setName(name);
        this->nodes[name] = node;

FEATURE ogs.h/End
        return node;
    }
