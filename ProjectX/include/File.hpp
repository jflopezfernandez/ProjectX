
#ifndef PROJECTX_INCLUDES_FILE_HPP_
#define PROJECTX_INCLUDES_FILE_HPP_

using FileExtension = std::string;
using FileName      = std::string;

using InputFile     = std::ifstream;
using OutputFile    = std::ofstream;

namespace File
{
    template <typename T1, typename T2, size_t N>
    void AddHeader(T1& outputStream, T2 (&filename)[N])
    {
        outputStream << "#include <" << filename << ">" << IO::endl;
    }

    template <typename T1, typename T2>
    void AddHeader(T1& outputStream, T2& filename)
    {
        outputStream << "#include <" << filename << ">" << IO::endl;
    }
}

void PrintCurrentPath()
{
    std::cout << "Current Path: " << FileSystem::current_path() << IO::endl;
}

namespace EXPERIMENTAL
{
    // struct File
    // {
    //     std::string Name;
    //     std::string Extension;
    // };

    // struct SourceFile : public File
    // {
    //     ProgrammingLanguage Language;

    //     SourceFile(const std::string& filename, const ProgrammingLanguage lang)
    //         : Name{ filename }, Language{ lang }
    //     {
    //         // TODO: Set file extension
    //     }
    // };
} // namespace X

#endif // PROJECTX_INCLUDES_FILE_HPP_
