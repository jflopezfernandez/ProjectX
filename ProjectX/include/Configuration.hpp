
/** 
 *  @author Jose Fernando Lopez Fernandez
 *  @version 0.2.1
 *  @date 22 March, 2019
 *  @copyright GNU Public License.
 *
 */

#ifndef PROJECTX_INCLUDES_CONFIGURATION_HPP_
#define PROJECTX_INCLUDES_CONFIGURATION_HPP_

using ProjectName = std::string;

class ProjectConfiguration
{
    ProjectName         m_name;
    ProgrammingLanguage m_lang;
    CompilerName        m_comp;
    Person              m_author;
    License             m_license;
    Version             m_version;
    std::chrono::system_clock::time_point m_created;
    bool                m_verbose;

public:
    ProjectConfiguration()
        : m_name{ "Untitled" }, m_lang{ None }, m_comp{ "g++" }
    {
        //
    }
    
    void setName(const std::string& str)
    {
        m_name = str;
    }

    void setProgrammingLanguage(ProgrammingLanguage lang)
    {
        m_lang = lang;
    }

    void setCompiler(const std::string& str)
    {
        m_comp = str;
    }

    void setVerbosity(bool requested)
    {
        m_verbose = requested;
    }

    auto name() const noexcept
    {
        return m_name;
    }

    auto programmingLanguage() const noexcept
    {
        return m_lang;
    }

    auto compiler() const noexcept
    {
        return m_comp;
    }

    auto verbose() const noexcept
    {
        return m_verbose;
    }
};

#endif // PROJECTX_INCLUDES_CONFIGURATION_HPP_
