FEATURE ogs.h/Impl
//! Combine several strings into one
std::string stringsToString(
    const std::vector<std::string> &strings,
    const std::string &separator = ", "
) {
    std::string result;
    for (auto item : strings)
    {
        // The first item.
        if (result.empty())
        {
            result = item;
        }
        // The rest ones.
        else
        {
            result += separator + item;
        }
    }

    return result;
}
