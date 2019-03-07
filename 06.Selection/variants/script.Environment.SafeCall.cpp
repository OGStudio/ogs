FEATURE ogs.h/Impl
// Perform safe call.
try {
    return client->call(key, values);
}
catch (const std::exception &e)
{
    SCRIPT_ENVIRONMENT_LOG(
        "ERROR Client execution for key '%s' failed: '%s'",
        key.c_str(),
        e.what()
    );
    return { };
}
