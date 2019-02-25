FEATURE ogs.h/Impl
//! Decode base64 string representation into a string (of bytes)

//! \return an empty string if decoding failed
std::string base64Decode(const std::string &input)
{
    std::string output;
    lib::Base64::Decode(input, &output);
    return output;
}
