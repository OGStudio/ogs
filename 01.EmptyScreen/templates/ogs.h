
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

// FEATURE format.printfString/Include
// FEATURE log.log-default/Include
// FEATURE log.logprintf/Include
// FEATURE main.Application.Rendering/Include
// FEATURE main.Application+frame/Include
// FEATURE main.Application+setupWindow-web/Include
// FEATURE render.createGraphicsContext-desktop/Include
// FEATURE render.setupCamera/Include

// FEATURE MAIN_APPLICATION_LOG/Impl

namespace ogs
{

namespace format
{

// FEATURE format.printfString/Impl

}

namespace log
{

// FEATURE log.log-default/Impl
// FEATURE log.logprintf/Impl

}

namespace render
{

// FEATURE render.createGraphicsContext-desktop/Impl
// FEATURE render.setupCamera/Impl

}

namespace main
{

// FEATURE main.Application/Setup
            // FEATURE main.Application.Rendering/Setup
// FEATURE main.Application/TearDown
            // FEATURE main.Application.Rendering/TearDown
// FEATURE main.Application/Impl
    // FEATURE main.Application+frame/Impl
    // FEATURE main.Application+run/Impl
    // FEATURE main.Application+setupWindow-desktop/Impl
    // FEATURE main.Application+setupWindow-embedded/Impl
    // FEATURE main.Application+setupWindow-web/Impl

    // FEATURE main.Application.Rendering/Impl
// FEATURE main.Application/End

// FEATURE main.Example.01.EmptyScreen/Title

// FEATURE main.Example/Setup
// FEATURE main.Example/TearDown
// FEATURE main.Example/Impl
// FEATURE main.Example/End

}

} // namespace ogs

#endif // OGS_H

