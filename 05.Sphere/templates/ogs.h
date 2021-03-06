
/*
This file is part of OGS: https://github.com/ogstudio/ogs

Copyright (C) 2019 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OGS_H
#define OGS_H

// FEATURE core.Reporter/Include
// FEATURE format.commandLineArgumentsToParameters/Include
// FEATURE format.printfString/Include
// FEATURE format.urlToParameters/Include
// FEATURE input.Mouse/Include
// FEATURE log.log-default/Include
// FEATURE log.logprintf/Include
// FEATURE main.Application.Lua/Include
// FEATURE main.Application.Rendering/Include
// FEATURE main.Application.Scripting/Include
// FEATURE main.Application+frame/Include
// FEATURE main.Application+setupWindow-web/Include
// FEATURE main.Example.EmbeddedAPIScript/Include
// FEATURE main.Nodes/Include
// FEATURE render.VBOSetupVisitor/Include
// FEATURE render.createGraphicsContext-desktop/Include
// FEATURE render.createShaderProgram/Include
// FEATURE render.setupCamera/Include
// FEATURE scene.createShape/Include
// FEATURE script.EnvironmentClient/Include

// FEATURE SCRIPT_ENVIRONMENT_CLIENT_CALL/Impl
// FEATURE SCRIPT_ENVIRONMENT_LOG/Impl
// FEATURE MAIN_APPLICATION_LOG/Impl
// FEATURE MAIN_EXAMPLE_LOG/Impl

namespace lib
{

// FEATURE lib.base64/Impl

}

namespace ogs
{

namespace core
{

// FEATURE core.Reporter/Impl

}

namespace format
{

// FEATURE format.base64Encode/Impl
// FEATURE format.base64Decode/Impl
// FEATURE format.splitString/Impl
// FEATURE format.stringStartsWith/Impl
// FEATURE format.stringsToString/Impl
// FEATURE format.commandLineArgumentsToParameters/Impl
// FEATURE format.printfString/Impl
// FEATURE format.urlToParameters/Impl

}

namespace log
{

// FEATURE log.log-default/Impl
// FEATURE log.logprintf/Impl

}

namespace input
{

// FEATURE input.MouseButtons/Impl
// FEATURE input.Mouse/Impl

}

namespace render
{

// FEATURE render.VBOSetupVisitor/Impl

// FEATURE render.createGraphicsContext-desktop/Impl
// FEATURE render.createShaderProgram/Impl
// FEATURE render.setupCamera/Impl

}

namespace resource
{

// FEATURE resource.Resource/Impl

}

namespace scene
{

// FEATURE scene.createShape/Impl
// FEATURE scene.createSphere/Impl

}

namespace script
{

// FEATURE script.EnvironmentClient/Impl
// FEATURE script.Environment/Begin
            // FEATURE script.Environment/Call
// FEATURE script.Environment/End

}

namespace main
{

// FEATURE main.Nodes/Setup
    // FEATURE main.Nodes.Root/Setup
// FEATURE main.Nodes/TearDown
// FEATURE main.Nodes/Impl
    // FEATURE main.Nodes.VBO/Impl
 
    // FEATURE main.Nodes+createSphere/Begin
            // FEATURE main.Nodes.VBO/Apply
    // FEATURE main.Nodes+createSphere/End
    // FEATURE main.Nodes+node/Impl
 
    // FEATURE main.Nodes.Root/Impl
// FEATURE main.Nodes/End

// FEATURE main.Application/Setup
            // FEATURE main.Application.Rendering/Setup
            // FEATURE main.Application.Mouse/Setup
            // FEATURE main.Application.Nodes/Setup
            // FEATURE main.Application.Lua/Setup
            // FEATURE main.Application.Scripting/Setup
// FEATURE main.Application/TearDown
            // FEATURE main.Application.Scripting/TearDown
            // FEATURE main.Application.Lua/TearDown
            // FEATURE main.Application.Nodes/TearDown
            // FEATURE main.Application.Mouse/TearDown
            // FEATURE main.Application.Rendering/TearDown
// FEATURE main.Application/Impl
    // FEATURE main.Application+camera/Impl
    // FEATURE main.Application+frame/Impl
    // FEATURE main.Application+handleEvent-web/Impl
    // FEATURE main.Application+run/Impl
    // FEATURE main.Application+setupWindow-desktop/Impl
    // FEATURE main.Application+setupWindow-embedded/Impl
    // FEATURE main.Application+setupWindow-web/Impl

    // FEATURE main.Application.Lua/Impl
    // FEATURE main.Application.Mouse/Impl
    // FEATURE main.Application.Nodes/Impl
    // FEATURE main.Application.Rendering/Impl
    // FEATURE main.Application.Scripting/Impl
// FEATURE main.Application/End

// FEATURE main.Example.05.Sphere/Title

// FEATURE main.Example/Setup
        // FEATURE main.Example.LogTitle/Impl
        // FEATURE main.Example.WhiteNodes/Setup
        // FEATURE main.Example.API.application.camera.clearColor/Setup
        // FEATURE main.Example.API.application.mouse/Setup
        // FEATURE main.Example.API.application.nodes.createSphere/Setup
        // FEATURE main.Example.API.application.nodes.node.addChild/Setup
        // FEATURE main.Example.API.application.nodes.node.exists/Setup
        // FEATURE main.Example.EmbeddedAPIScript/Setup
        // FEATURE main.Example.Base64Script/Setup
// FEATURE main.Example/TearDown
        // FEATURE main.Example.API.application.mouse/TearDown
// FEATURE main.Example/Impl
    // FEATURE main.Example.API.application.mouse/Impl
    // FEATURE main.Example.Base64Script/Impl
    // FEATURE main.Example.EmbeddedAPIScript/Impl
    // FEATURE main.Example.WhiteNodes/Impl
// FEATURE main.Example/End

}

} // namespace ogs

#endif // OGS_H

