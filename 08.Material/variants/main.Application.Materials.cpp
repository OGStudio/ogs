FEATURE ogs.h/Setup
this->setupMaterials();

FEATURE ogs.h/TearDown
this->tearMaterialsDown();

FEATURE ogs.h/Impl
public:
    Materials *materials;
private:
    void setupMaterials()
    {
        this->materials = new Materials;
    }
    void tearMaterialsDown()
    {
        delete this->materials;
    }
