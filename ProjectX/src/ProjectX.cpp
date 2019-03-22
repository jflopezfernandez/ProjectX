
#include "ProjectX.hpp"

class ProjectConfiguration
{
    std::string m_name;
    std::string m_lang;
    std::string m_comp;

public:
    ProjectConfiguration()
        : m_name{ "Untitled" }, m_lang{ "C++" }, m_comp{ "g++" }
    {
        //
    }
    
    void setName(const std::string& str)
    {
        std::cout << "Old Name: " << m_name << std::cout.widen('\n');
        m_name = str;
        std::cout << "New Name: " << m_name << std::cout.widen('\n');
    }

    void setProgrammingLanguage(const std::string& str)
    {
        m_lang = str;
    }

    void setCompiler(const std::string& str)
    {
        m_comp = str;
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
};

// enum class ProgrammingLanguage {
//     C++,
//     C,
//     Perl
// };

//

namespace X
{
    class File {
        std::string Name;
    public:
        //
    };
} // namespace X

// struct FileSystemNode {
//     std::variant<File, std::vector<struct FileSystemNode>> Contents;
// };

int main(int argc, char *argv[])
{
    ProjectConfiguration project;

    Options::options_description optionsDescription("Program Options");
    optionsDescription.add_options()
        ("help", "Show this help message")
        ("version", "Print program version information")
        ("project-name", Options::value<std::string>(), "The name of the project being generated")
        ("programming-language", Options::value<std::string>(), "The new project's primary programming language")
        ("compiler", Options::value<std::string>(), "Project default compiler")
    ;

    Options::variables_map inputArgs;
    Options::store(Options::parse_command_line(argc, argv, optionsDescription), inputArgs);
    Options::notify(inputArgs);

    if (inputArgs.count("help")) {
        std::cout << optionsDescription << std::cout.widen('\n');

        return EXIT_SUCCESS;
    } else if (inputArgs.count("version")) {
        std::cout << "<Program Version>" << std::cout.widen('\n');

        return EXIT_SUCCESS;
    }

    if (inputArgs.count("project-name")) {
        project.setName(inputArgs["project-name"].as<std::string>());
    } else if (inputArgs.count("programming-language")) {
        project.setProgrammingLanguage(inputArgs["programming-language"].as<std::string>());
    } else if (inputArgs.count("compiler")) {
        project.setCompiler(inputArgs["compiler"].as<std::string>());
    }

    FileSystem::path projectDir;
    projectDir /= project.name();
    projectDir /= project.name();
    FileSystem::create_directories(projectDir);

    FileSystem::path srcDir = projectDir;
    srcDir /= "src";
    FileSystem::path includeDir = projectDir;
    includeDir /= "include";

    FileSystem::create_directory(srcDir);
    FileSystem::create_directory(includeDir);

    /** Makefile */
    std::string makefileDir = projectDir.string() + "/Makefile";
    std::ofstream makefile;
    makefile.open(makefileDir, std::ios::out);

    //makefile << "testing..." << std::endl;

    makefile << "" << std::endl;
    makefile << "#==============================================================" << std::endl;
    makefile << "#" << std::endl;
    makefile << "#                            PROJECT X" << std::endl;
    makefile << "#" << std::endl;
    makefile << "# =============================================================" << std::endl;
    makefile << "" << std::endl;
    makefile << "vpath %.cpp src" << std::endl;
    makefile << "vpath %.hpp include" << std::endl;
    makefile << "" << std::endl;
    makefile << ".SUFFIXES:" << std::endl;
    makefile << ".SUFFIXES: .cpp .hpp" << std::endl;
    makefile << "" << std::endl;
    makefile << "SHELL         = /bin/sh" << std::endl;
    makefile << "" << std::endl;
    makefile << "COMPILERWARN  = -Wall -Wextra -Wpedantic" << std::endl;
    makefile << "OPTIMIZATIONS = -Ofast -mtune=intel -march=skylake -mavx2" << std::endl;
    makefile << "BUILDFLAGS    =    $(COMPILERWARN) $(OPTIMIZATIONS)" << std::endl;
    makefile << "" << std::endl;
    makefile << "ASM           =  nasm" << std::endl;
    makefile << "CC            =  gcc" << std::endl;
    makefile << "CXX           =  g++" << std::endl;
    makefile << "CFLAGS        = -std=c11   $(BUILDFLAGS)" << std::endl;
    makefile << "CXXFLAGS      = -std=c++17 $(BUILDFLAGS)" << std::endl;
    makefile << "" << std::endl;
    makefile << "SOURCES_DIR   = src" << std::endl;
    makefile << "INCLUDES_DIR  = include" << std::endl;
    makefile << "" << std::endl;
    makefile << "MKLHEADERS    = -I $(INTELMKLINCLUDEDIR) " << std::endl;
    makefile << "INTELINCLUDES =    $(MKLHEADERS)" << std::endl;
    makefile << "SRC_HEADERS   = -I $(INCLUDES_DIR)" << std::endl;
    makefile << "INCLUDEDIRS   =    $(SRC_HEADERS)" << std::endl;
    makefile << "" << std::endl;
    makefile << "MATHLIB       = -lm" << std::endl;
    makefile << "CPPFILESYSTEM = -lstdc++fs" << std::endl;
    makefile << "LIBGMP        = -lgmp" << std::endl;
    makefile << "INTEL_MKL     = -L $(INTELMKLLIBDIR) -lmkl" << std::endl;
    makefile << "INTEL_LIBS    =    $(IPPLIB) $(IPPCPLIB)" << std::endl;
    makefile << "BOOSTOPTS     = -lboost_program_options" << std::endl;
    makefile << "BOOSTLIBS     =    $(BOOSTOPTS)" << std::endl;
    makefile << "REQLIBS       =    $(MATHLIB) $(CPPFILESYSTEM) $(LIBGMP) $(BOOSTLIBS)" << std::endl;
    makefile << "" << std::endl;
    makefile << "SRCS          = ProjectX.cpp" << std::endl;
    makefile << "HDRS          = $(patsubst %.cpp, %.hpp, $(SRCS))" << std::endl;
    makefile << "OBJS          = $(patsubst %.cpp, %.o, $(SRCS))" << std::endl;
    makefile << "PROGRAM       = x" << std::endl;
    makefile << "" << std::endl;
    makefile << "OUTPUT_OPTION = -o $@" << std::endl;
    makefile << "TARGET_ARCH   = " << std::endl;
    makefile << "" << std::endl;
    makefile << "COMPILE.c     = $(CC)  $(CFLAGS)   $(CPPFLAGS) $(INCLUDEDIRS) $(TARGET_ARCH) -c" << std::endl;
    makefile << "LINK.c        = $(CC)  $(CFLAGS)   $(CPPFLAGS) $(INCLUDEDIRS) $(TARGET_ARCH) $(LDFLAGS)" << std::endl;
    makefile << "COMPILE.cpp   = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDEDIRS) $(TARGET_ARCH) -c" << std::endl;
    makefile << "LINK.o        = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDEDIRS) $(TARGET_ARCH) $(LDFLAGS)" << std::endl;
    makefile << "" << std::endl;
    makefile << "all: $(PROGRAM)" << std::endl;
    makefile << "" << std::endl;
    makefile << "$(PROGRAM): $(OBJS)" << std::endl;
    makefile << "	$(LINK.o) $(OUTPUT_OPTION) $^ $(REQLIBS)" << std::endl;
    makefile << "" << std::endl;
    makefile << "%.o: %.cpp" << std::endl;
    makefile << "	$(COMPILE.cpp) $(OUTPUT_OPTION) $^ " << std::endl;
    makefile << "" << std::endl;
    makefile << ".PHONY: clean" << std::endl;
    makefile << "clean:" << std::endl;
    makefile << "	$(RM) $(OBJS) $(PROGRAM)" << std::endl;



    makefile.close();

    /** Source File */
    std::string srcFile = projectDir.string() + "/src/" + project.name() + ".cpp";
    std::ofstream file;
    file.open(srcFile, std::ios::out);

    file << std::endl;
    file << "#include \"" << project.name() + ".cpp" << "\"" << std::endl;
    file << std::endl;
    file << std::endl;
    file << "int main()" << std::endl;
    file << "{" << std::endl;
    file << "    std::cout << \"testing...\" << std::endl;" << std::endl;
    file << std::endl;
    file << "    return EXIT_SUCCESS;" << std::endl;
    file << "}" << std::endl;

    file.close();

    /** Source File */
    std::string includeFile = projectDir.string() + "/include/" + project.name() + ".hpp";
    std::ofstream headerFile;
    headerFile.open(includeFile, std::ios::out);

    headerFile << "#ifndef " << project.name() << "_INCLUDES_" << project.name() << "_HPP_" << std::endl;
    headerFile << "#define " << project.name() << "_INCLUDES_" << project.name() << "_HPP_" << std::endl;
    headerFile << std::endl;
    headerFile << "#include <cstdio>" << std::endl;
    headerFile << "#include <cstdlib>" << std::endl;
    headerFile << "#include <cstring>" << std::endl;
    headerFile << "#include <cmath>" << std::endl;
    headerFile << "#include <ctime>" << std::endl;
    headerFile << std::endl;
    headerFile << "#include <any>" << std::endl;
    headerFile << "#include <filesystem>" << std::endl;
    headerFile << "#include <fstream>" << std::endl;
    headerFile << "#include <iostream>" << std::endl;
    headerFile << "#include <iterator>" << std::endl;
    headerFile << "#include <memory>" << std::endl;
    headerFile << "#include <optional>" << std::endl;
    headerFile << "#include <string>" << std::endl;
    headerFile << "#include <utility>" << std::endl;
    headerFile << "#include <variant>" << std::endl;
    headerFile << "#include <vector>" << std::endl;
    headerFile << std::endl;
    headerFile << "#include <boost/lexical_cast.hpp>" << std::endl;
    headerFile << "#include <boost/program_options.hpp>" << std::endl;
    headerFile << std::endl;
    headerFile << "#endif // " << project.name() << "_INCLUDES_" << project.name() << "_HPP_" << std::endl;
    headerFile.close();

    return EXIT_SUCCESS;
}
