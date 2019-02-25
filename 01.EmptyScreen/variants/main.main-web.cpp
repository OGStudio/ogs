FEATURE ogs.cpp/LoopBegin
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

FEATURE ogs.cpp/LoopEnd
        }
        example->app->frame();
    }
}

FEATURE ogs.cpp/Setup
// Make sure SDL is working.
if (SDL_Init(SDL_INIT_VIDEO) < 0)
{
    printf("ERROR Could not initialize SDL: '%s'\n", SDL_GetError());
    return 1;
}
// Clean SDL up at exit.
atexit(SDL_Quit);

main::Example::Parameters parameters;

FEATURE ogs.cpp/End
example = new main::Example(parameters);
// Create rendering window of initial size.
if (!example->app->setupWindow(main::EXAMPLE_TITLE, 800, 600))
{
    return 1;
}

FEATURE ogs.cpp/Run
// Render asynchronously.
emscripten_set_main_loop(loop, -1, 0);
