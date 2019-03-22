
#ifndef PROJECTX_INCLUDES_UTILITY_HPP_
#define PROJECTX_INCLUDES_UTILITY_HPP_

namespace X
{
    namespace Utils
    {
        DateString DateToString(std::chrono::system_clock::time_point date, const char* formatSpecifier = "%d-%b-%Y")
        {
            std::time_t fromSystemClock = std::chrono::system_clock::to_time_t(date);

            std::ostringstream dateStringStream;
            dateStringStream << std::put_time(std::localtime(&fromSystemClock), formatSpecifier);

            return dateStringStream.str();
        }

        /** @todo Allow for customizations to the date string via passed-in function parameters.
         *
         */
        DateString CurrentDateString()
        {
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            return X::Utils::DateToString(now);
        }
    } // namespace Utils
} // namespace X

#endif // PROJECTX_INCLUDES_UTILITY_HPP_
