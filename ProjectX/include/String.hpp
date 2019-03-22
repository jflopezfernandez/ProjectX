
#ifndef PROJECTX_INCLUDES_STRING_HPP_
#define PROJECTX_INCLUDES_STRING_HPP_

namespace X
{
    namespace String
    {
        void Capitalize(std::string& s)
        {
            std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::toupper(c); });
        }

        void Lowercase(std::string& s)
        {
            std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
        }
    } // namespace String
} // namespace X

#endif // PROJECTX_INCLUDES_STRING_HPP_
