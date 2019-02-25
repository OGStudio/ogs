FEATURE ogs.h/Impl
//! Encode a string (of bytes) into base64 string representation

//! \return an empty string if encoding failed
std::string base64Encode(const std::string &input)
{
    std::string output;
    lib::Base64::Encode(input, &output);
    return output;
}
