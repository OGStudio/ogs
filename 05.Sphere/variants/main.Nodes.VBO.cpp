FEATURE ogs.h/Impl
private:
    render::VBOSetupVisitor vbo;

FEATURE ogs.h/Apply
node->accept(this->vbo);
