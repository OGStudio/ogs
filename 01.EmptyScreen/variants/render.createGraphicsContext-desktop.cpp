FEATURE ogs.h/Impl
//! Create graphics context for desktop: linux, macos, windows.
osg::GraphicsContext *createGraphicsContext(
    const std::string &title,
    int x,
    int y,
    int width,
    int height
) {
    // Traits combine configuration parameters.
    osg::GraphicsContext::Traits *traits =
        new osg::GraphicsContext::Traits;
    // Geometry.
    traits->x = x;
    traits->y = y;
    traits->width = width;
    traits->height = height;
    // Title.
    traits->windowName = title;
    // Window borders.
    traits->windowDecoration = true;
    // Double buffer (simply put, it's a flicker fix).
    traits->doubleBuffer = true;

    return osg::GraphicsContext::createGraphicsContext(traits);
}
