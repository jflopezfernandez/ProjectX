
#ifndef PROJECTX_INCLUDES_IO_HPP_
#define PROJECTX_INCLUDES_IO_HPP_

namespace IO
{
    template <typename T, typename CharT = std::char_traits<T>>
    std::basic_ostream<T, CharT>&
    endl(std::basic_ostream<T, CharT>& outputStream)
    {
        return outputStream << outputStream.widen('\n');
    }
} // namespace IO

#endif // PROJECTX_INCLUDES_IO_HPP_
