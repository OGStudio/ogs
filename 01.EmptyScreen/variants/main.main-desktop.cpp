FEATURE ogs.cpp/Setup
main::Example::Parameters parameters;

FEATURE ogs.cpp/End
auto example = new main::Example(parameters);
example->app->setupWindow(main::EXAMPLE_TITLE, 100, 100, 800, 600);

FEATURE ogs.cpp/Run
example->app->run();
delete example;
