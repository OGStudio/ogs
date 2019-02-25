FEATURE ogs.h/Include
#include <map>

FEATURE ogs.h/Impl
typedef std::map<std::string, std::string> Parameters;
//! Convert query parameters starting after `?` that are in the form of `key=value` to parameters.
Parameters urlToParameters(int argc, char *argv[])
{
    Parameters parameters;

    // No URL has been provided. Nothing to parse.
    if (argc < 3)
    {
        return parameters;
    }

    std::string query = argv[2];
    auto options = format::splitString(query, "&");

    for (auto option : options)
    {
        // Only split once.
        auto keyAndValue = format::splitString(option, "=", 1);
        if (keyAndValue.size() == 2)
        {
            auto key = keyAndValue[0];
            auto value = keyAndValue[1];
            parameters[key] = value;
        }
    }

    // Create "base" parameter to contain
    // everything before `? and the search string` plus `/..`
    std::string url(argv[1]);
    parameters["base"] = url + "/..";
    // Use substring if there's `?` sign.
    if (query.length())
    {
        auto pos = url.find("?");
        parameters["base"] = url.substr(0, pos) + "/..";
    }

    return parameters;
}
