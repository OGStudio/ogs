FEATURE ogs.h/Impl
//! Split a string into a list of strings using single character.

//! \param `text` contains the string to split
//! \param `delimiter` contains single character used to split `text` string
//! \param `maxSplit` larger than `0` restricts the number of splits
std::vector<std::string> splitString(
    const std::string &text,
    const char *delimiter,
    size_t maxSplit = 0 
) {
    size_t splitCount = 0;
    size_t pos = 0;
    bool proceed = true;
    bool hasChar = false;
    std::vector<std::string> result;

    while (proceed)
    {
        // 1. Is this split allowed?
        bool isAllowed = true;
        if (
            maxSplit &&
            (splitCount >= maxSplit)
        ) {
            isAllowed = false;
        }
        // 2. The remaining string contains the delimiter?
        auto id = text.find(delimiter, pos);
        bool hasDelimiter = (id != std::string::npos);

        if (isAllowed && hasDelimiter)
        {
            auto segment = text.substr(pos, id - pos);
            result.push_back(segment);
            pos = id + 1;
            hasChar = true;
            ++splitCount;
        }
        else
        {
            auto segment = text.substr(pos, text.length());
            result.push_back(segment);
            proceed = false;
            // If delimiting char has not been found,
            // the result should only contain original string.
        }
    }
    return result;
}
