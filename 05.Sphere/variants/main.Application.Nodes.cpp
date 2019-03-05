FEATURE ogs.h/Setup
this->setupNodes();

FEATURE ogs.h/TearDown
this->tearNodesDown();

FEATURE ogs.h/Impl
public:
    Nodes *nodes;
private:
    void setupNodes()
    {
        this->nodes = new Nodes;

        // Set pool's root node to viewer.
        auto root = this->nodes->node("root");
        this->viewer->setSceneData(root);
    }
    void tearNodesDown()
    {
        this->viewer->setSceneData(0);
        delete this->nodes;
    }
