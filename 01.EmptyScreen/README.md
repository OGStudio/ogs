
This is the base of `ogs` to let it run on supported platforms and display an
empty screen, nothing more.

The base consists of:

* [OpenSceneGraph/](#osg)
    * custom configuration to build `OpenSceneGraph` for supported platforms
* [features/](#features)
    * source code variants of OGS
* [platforms/](#platforms)
    * platform specific build and configuration files

<a name="osg"/>

# OpenSceneGraph/

[OpenSceneGraph][OpenSceneGraph] is a versatile C++ library to render 3D with
OpenGL. 

`OpenSceneGraph` directory contains:

* `CMakeLists.txt`
    * Is a configuration file for [CMake][CMake]
    * Builds `OpenSceneGraph` components (`osgViewer`, `osgUtil`, etc.) as static libraries
    * Builds `OpenSceneGraph` for `linux`, `macos`, and `web`
        * `android` and `windows` are coming later
        * `ios` is supported by `Xcode` project, not `CMake` one
* `include/`
    * Contains platform specific headers for `OpenThreads` and `OpenSceneGraph`
        * The headers were generated by original `OpenSceneGraph`'s `CMake` configuration process for each supported platform
        * They are kept in the repository to support custom `OpenSceneGraph` configuration
* `include-gen/`
    * Contains simplistic `OpenSceneGraph` applications to generate platform specific headers for `ios` and `web`
* `src/`
    * Contains custom sources to build `OpenSceneGraph` fast
    * Speedup is achieved by combining several sources into one

**Notes**:

* Place original `OpenSceneGraph` distribution directory alongside `ogs`
directory because custom sources reference original `OpenSceneGraph`
distribution sources
        
<a name="features"/>

# features/

Features represent source code variants that may be easily switched on or off.

TODO Update [feature-tool][feature-tool] to better describe its purpose and
usage.

        
<a name="platforms"/>

# platforms/

`platforms` directory contains:

* `CMakeLists.txt`
    * configuration common to all platforms
* `desktop/`
    * build and configuration files for `linux`, `macos`, and `windows`

[OpenSceneGraph]: http://www.openscenegraph.com/
[CMake]: https://cmake.org/
[feature-tool]: http://bitbucket.org/ogstudio/feature-tool

