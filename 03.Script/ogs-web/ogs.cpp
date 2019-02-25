
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

#include "ogs.h"

using namespace ogs;

// Global instance to be used in free functions.
main::Example *example = 0;

// Free function to be used by Emscripten to run the app.
void loop()
{
    if (example)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {

        }
        example->app->frame();
    }
}


int main(int argc, char *argv[])
{

    // Make sure SDL is working.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("ERROR Could not initialize SDL: '%s'\n", SDL_GetError());
        return 1;
    }
    // Clean SDL up at exit.
    atexit(SDL_Quit);
    
    main::Example::Parameters parameters;
    
    parameters = format::urlToParameters(argc, argv);
    example = new main::Example(parameters);
    // Create rendering window of initial size.
    if (!example->app->setupWindow(main::EXAMPLE_TITLE, 800, 600))
    {
        return 1;
    }
    
    // Render asynchronously.
    emscripten_set_main_loop(loop, -1, 0);

    return 0;
}

