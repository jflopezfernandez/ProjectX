
#ifndef PROJECTX_INCLUDES_PROJECTX_HPP_
#define PROJECTX_INCLUDES_PROJECTX_HPP_

#if defined(__unix__)
#include <sys/types.h>
#include <unistd.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>

#include <algorithm>
#include <any>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <optional>
#include <ratio>
#include <set>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace FileSystem = std::filesystem;

#include <Eigen/Core>
#include <Eigen/Dense>

#include <boost/compute.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

namespace Options = boost::program_options;

#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/math/distributions.hpp>
#include <boost/math/special_functions.hpp>
#include <boost/math/tr1.hpp>

#include <gmp.h>

#include "Version.hpp"
#include "IO.hpp"
#include "String.hpp"
#include "File.hpp"
#include "Person.hpp"
#include "ProgrammingLanguages.hpp"
#include "Compilers.hpp"
#include "License.hpp"
#include "Configuration.hpp"

using VariableName       = std::string;
using VariableDefinition = std::string;

namespace Makefile
{
    void PrintSpaces(OutputFile& filename, size_t n)
    {
        for (auto i = 0u; i < n; ++i) {
            filename << ' ';
        }
    }

    void DefineVariable(OutputFile& filename, VariableName variable, VariableDefinition value)
    {
        const size_t l = 15 - variable.length();

        filename << variable << " ";

        for (auto i = 0u; i < l; ++i) {
            filename << " ";
        }

        filename << "= " << value << " " << IO::endl;
    }

    void PrintNewLines(OutputFile& filename, size_t n)
    {
        for (auto i = 0u; i <= n; ++i) {
            filename << IO::endl;
        }
    }

    void PrintNewLine(OutputFile& filename)
    {
        PrintNewLines(filename, 0);
    }

    const std::string_view& headingLiner = "#===============================================================================";

    void PrintHeadingLine(OutputFile& filename, const std::string_view& liner)
    {
        filename << liner << IO::endl;
    }

    using MakefileHeading = std::string;

    void PrintHeadingBorder(OutputFile& filename)
    {
        filename << "#";
    }

    void PrintHeadingBorderLine(OutputFile& filename)
    {
        PrintHeadingBorder(filename);
        PrintNewLine(filename);
    }

    void PrintHeadingTitle(OutputFile& filename, MakefileHeading heading)
    {
        const size_t m = 30 - 1;

        PrintHeadingBorder(filename);
        PrintSpaces(filename, m);
        filename << heading << IO::endl;
    }

    void PrintHeading(OutputFile& filename, MakefileHeading heading, size_t n = 2)
    {
        Makefile::PrintNewLine(filename);
        PrintHeadingLine(filename, headingLiner);
        for (auto i = 0u; i < n; ++i) {
            PrintHeadingBorderLine(filename);
        }
        PrintHeadingTitle(filename, heading);
        for (auto i = 0u; i < n; ++i) {
            PrintHeadingBorderLine(filename);
        }
        PrintHeadingLine(filename, headingLiner);
    }

    std::string Dereference(VariableName variable)
    {
        return "$(" + variable + ") ";
    }

    void VPathExtensionDeclaration(OutputFile& filename, std::string extension, std::string path)
    {
        filename << "vpath " << extension << " " << path << IO::endl;
    }

    void DefineRecipe(OutputFile& filename, std::string goal, std::string dependencies, std::string recipe)
    {
        filename << goal << ": " << dependencies << IO::endl;
        filename << '\t' << recipe << IO::endl;
    }

    void Declare(OutputFile& filename, std::string declaration)
    {
        filename << declaration << IO::endl;
    }

    using DoxygenTagName       = std::string;
    using DoxygenDocumentation = std::string;

    void PrintDoxygenDocTag(OutputFile& filename, DoxygenTagName tag, DoxygenDocumentation doc)
    {
        PrintHeadingBorder(filename);
        filename << " " << tag << " " << doc << IO::endl;
    }
} // namespace Makefile

namespace Source
{
    void PrintNewLines(OutputFile& filename, size_t n)
    {
        for (auto i = 0u; i < n; ++i) {
            filename << IO::endl;
        }
    }

    void PrintNewLine(OutputFile& filename)
    {
        PrintNewLines(filename, 1);
    }

    void PrintHeaderFileGuardStart(OutputFile& filename, std::string projectName, std::string headerFileName, std::string extension)
    {
        const auto headerGuardExtension = (extension == ".h") ? "_H_" : "_HPP_";

        filename << "#ifndef " << projectName << "_INCLUDES_" << headerFileName << headerGuardExtension << IO::endl;
        filename << "#define " << projectName << "_INCLUDES_" << headerFileName << headerGuardExtension << IO::endl;
    }

    void PrintHeaderFileGuardEnd(OutputFile& filename, std::string projectName, std::string headerFileName, std::string extension)
    {
        const auto headerGuardExtension = (extension == ".h") ? "_H_" : "_HPP_";

        filename << "#endif // " << projectName << "_INCLUDES_" << headerFileName << headerGuardExtension << IO::endl;
    }

    void IncludeHeader(OutputFile& filename, std::string headerFile)
    {
        filename << "#include <" << headerFile << ">" << IO::endl;
    }
} // namespace Source

#endif // PROJECTX_INCLUDES_PROJECTX_HPP_
