
#include "ProjectX.hpp"

void PrintCurrentPath()
{
    std::cout << "Current Path: " << FileSystem::current_path() << IO::endl;
}


int main(int argc, char *argv[])
{
    LanguageExtensionMap     extensions;
    LanguageExtensionMapIter exIterator;

    extensions[ProgrammingLanguage::C]          = ".c";
    extensions[ProgrammingLanguage::Cpp]        = ".cpp";
    extensions[ProgrammingLanguage::Perl]       = ".pl";
    extensions[ProgrammingLanguage::Python]     = ".py";
    extensions[ProgrammingLanguage::CommonLisp] = ".lisp";
    extensions[ProgrammingLanguage::Haskell]    = ".hs";

    LanguageExtensionMap     includesExt;
    LanguageExtensionMapIter includesIter;

    includesExt[ProgrammingLanguage::C]         = ".h";
    includesExt[ProgrammingLanguage::Cpp]       = ".hpp";

    ProjectConfiguration project;

    Options::options_description optionsDescription("Program Options");
    optionsDescription.add_options()
        ("help", "Show this help message")
        ("version", "Print program version information")
        ("project-name", Options::value<std::string>()->default_value("Untitled"), "The name of the project being generated")
        ("programming-language", Options::value<std::string>()->default_value("C++"), "The new project's primary programming language")
        ("author", Options::value<std::string>()->default_value("Unknown author"), "The name of the project's author.")
        ("compiler", Options::value<std::string>()->default_value("GCC"), "Project default compiler")
        ("license", "Specify the license this project will be released under.")
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
    } 
    
    if (inputArgs.count("programming-language")) {
        const auto userLanguageSelection = inputArgs["programming-language"].as<std::string>();
        
        ProgrammingLanguage configuredLanguage = None;

        if (userLanguageSelection == "C++" || userLanguageSelection == "c++") {
            configuredLanguage = ProgrammingLanguage::Cpp;
        } else if (userLanguageSelection == "C" || userLanguageSelection == "c") {
            configuredLanguage = ProgrammingLanguage::C;
        } else if (userLanguageSelection == "Perl" || userLanguageSelection == "perl") {
            configuredLanguage = ProgrammingLanguage::Perl;
        } else if (userLanguageSelection == "Python" || userLanguageSelection == "python") {
            configuredLanguage = ProgrammingLanguage::Python;
        } else if (userLanguageSelection == "CommonLisp" || userLanguageSelection == "commonlisp") {
            configuredLanguage = ProgrammingLanguage::CommonLisp;
        }

        project.setProgrammingLanguage(configuredLanguage);
    } 
    
    if (inputArgs.count("compiler")) {
        project.setCompiler(inputArgs["compiler"].as<std::string>());
    }

    FileSystem::path projectDir = FileSystem::current_path();
    /*std::cout << "Project Dir: " << projectDir << IO::endl;*/

    /** 1. Create directory
     *  2. Change directory
     *  3. Repeat.
     */
    {
        const auto relativePath     = FileSystem::relative(project.name());
        const auto directoryCreated = FileSystem::create_directory(relativePath);

        if (!directoryCreated) {
            std::cerr << "Directory not created." << IO::endl;
        }

        FileSystem::current_path(relativePath);

    } // End of first directory traversal.

    {
        const auto relativePath     = FileSystem::relative(project.name());
        const auto directoryCreated = FileSystem::create_directory(relativePath);

        if (!directoryCreated) {
            std::cerr << "Directory not created." << IO::endl;
        }

        FileSystem::current_path(relativePath);
        
    } // End of second directory traversal.
    
    //std::cout << "Relative Path: " << relativePath << IO::endl;
    /*
    FileSystem::create_directory(project.name());
    FileSystem::current_path()

/*
    projectDir /= project.name();
    FileSystem::current_path(projectDir);
    PrintCurrentPath();
    
    projectDir /= project.name();
    FileSystem::current_path(projectDir);
    PrintCurrentPath();

    // FileSystem::create_directories(projectDir);
    // FileSystem::current_path(projectDir);

    FileSystem::path srcDir = projectDir;
    srcDir /= "src";
    FileSystem::path includeDir = projectDir;
    includeDir /= "include";



    FileSystem::create_directory(srcDir);
    FileSystem::create_directory(includeDir);

    

    const auto FileExtension = extensions[project.programmingLanguage()];
    const auto IncludesExtension = (project.programmingLanguage() == ProgrammingLanguage::C || project.programmingLanguage() == ProgrammingLanguage::Cpp) ? includesExt[project.programmingLanguage()] : "";

    std::cout << "Programming Language: " << project.programmingLanguage() << IO::endl;
    std::cout << "File extension: " << FileExtension << IO::endl;
    std::cout << "Includes Extension: " << IncludesExtension << IO::endl;
    

    FileName makefileDir = projectDir.string() + "/Makefile";
    OutputFile makefile;
    makefile.open(makefileDir, std::ios::out);

    Makefile::PrintHeading(makefile, project.name());
    Makefile::PrintHeadingBorderLine(makefile);
    
    Makefile::PrintDoxygenDocTag(makefile, "@date", "24-Mar-2019");
    Makefile::PrintDoxygenDocTag(makefile, "@author", "Jose Fernando Lopez Fernandez");
    Makefile::PrintDoxygenDocTag(makefile, "@version", "0.2.0");
    Makefile::PrintHeadingBorderLine(makefile);
    
    Makefile::PrintDoxygenDocTag(makefile, "@brief", "");
    Makefile::PrintDoxygenDocTag(makefile, "This is the master makefile for the project.", "");
    Makefile::PrintHeadingBorderLine(makefile);
    Makefile::PrintHeadingLine(makefile, Makefile::headingLiner);
    Makefile::PrintNewLine(makefile);

    Makefile::VPathExtensionDeclaration(makefile, "%" + extensions[project.programmingLanguage()], "src");
    Makefile::VPathExtensionDeclaration(makefile, "%.hpp", "include");
    Makefile::PrintNewLine(makefile);
    
    Makefile::DefineVariable(makefile, "SHELL", "/bin/sh");
    Makefile::PrintNewLine(makefile);

    Makefile::DefineVariable(makefile, "CSTD", " c11 ");
    Makefile::DefineVariable(makefile, "CXXSTD", " c++17 ");

    Makefile::DefineVariable(makefile, "WARNINGS", "-Wall -Wextra -Wpedantic ");
    Makefile::DefineVariable(makefile, "OPTIMIZATIONS", "-Ofast -mtune=intel -march=skylake -mavx2 ");
    Makefile::DefineVariable(makefile, "BUILDFLAGS", "   " + Makefile::Dereference("WARNINGS") + Makefile::Dereference("OPTIMIZATIONS"));
    Makefile::PrintNewLine(makefile);

    Makefile::DefineVariable(makefile, "ASM", " nasm");
    Makefile::DefineVariable(makefile, "CC", " gcc");
    Makefile::DefineVariable(makefile, "CXX", " g++");
    Makefile::DefineVariable(makefile, "CFLAGS", "-std=" + Makefile::Dereference("CSTD") + Makefile::Dereference("BUILDFLAGS"));
    Makefile::DefineVariable(makefile, "CXXFLAGS", "-std=" + Makefile::Dereference("CXXSTD") + Makefile::Dereference("BUILDFLAGS"));
    Makefile::PrintNewLine(makefile);
    
    Makefile::DefineVariable(makefile, "SOURCES_DIR", " src");
    Makefile::DefineVariable(makefile, "INCLUDES_DIR", " include");
    Makefile::PrintNewLine(makefile);
    
    Makefile::DefineVariable(makefile, "SRC_HEADERS", "-I " + Makefile::Dereference("INCLUDES_DIR"));
    Makefile::DefineVariable(makefile, "INCLUDEDIRS", "   " + Makefile::Dereference("SRC_HEADERS"));
    Makefile::PrintNewLine(makefile);

    Makefile::DefineVariable(makefile, "MATHLIB", "-lm");
    Makefile::DefineVariable(makefile, "CPPFILESYSTEM", "-lstdc++fs");
    Makefile::DefineVariable(makefile, "INTEL_MKL", "-L " + Makefile::Dereference("INTELMKLLIBDIR") + " -lmkl");
    Makefile::DefineVariable(makefile, "INTEL_LIBS", "   " + Makefile::Dereference("IPPLIB") + Makefile::Dereference("IPPCPLIB"));
    Makefile::DefineVariable(makefile, "BOOST_OPTS", "-lboost_program_options");
    Makefile::DefineVariable(makefile, "BOOSTLIBS", "   " + Makefile::Dereference("BOOSTOPTS"));
    Makefile::DefineVariable(makefile, "REQLIBS", "   " + Makefile::Dereference("MATHLIB") + Makefile::Dereference("CPPFILESYSTEM") + Makefile::Dereference("BOOSTLIBS"));
    Makefile::PrintNewLine(makefile);

    Makefile::DefineVariable(makefile, "SRCS", project.name() + extensions[project.programmingLanguage()]);
    Makefile::DefineVariable(makefile, "OBJS", Makefile::Dereference("patsubst %.cpp, %.o, " + Makefile::Dereference("SRCS")));
    Makefile::DefineVariable(makefile, "PROGRAM", project.name());
    Makefile::PrintNewLine(makefile);
    
    Makefile::DefineVariable(makefile, "OUTPUT_OPTION", "-o $@");
    Makefile::DefineVariable(makefile, "TARGET_ARCH", "");
    Makefile::PrintNewLine(makefile);
    
    Makefile::DefineVariable(makefile, "COMPILE.c ", Makefile::Dereference("CC") + " " + Makefile::Dereference("CFLAGS") + "  " + Makefile::Dereference("CPPFLAGS") + Makefile::Dereference("INCLUDEDIRS") + Makefile::Dereference("TARGET_ARCH") + "-c ");
    Makefile::DefineVariable(makefile, "LINK.c ", Makefile::Dereference("CC") + " " + Makefile::Dereference("CFLAGS") + "  " + Makefile::Dereference("CPPFLAGS") + Makefile::Dereference("INCLUDEDIRS") + Makefile::Dereference("TARGET_ARCH") + Makefile::Dereference("LDFLAGS"));
    Makefile::DefineVariable(makefile, "COMPILE.cpp ", Makefile::Dereference("CXX") + Makefile::Dereference("CXXFLAGS") + Makefile::Dereference("CPPFLAGS") + Makefile::Dereference("INCLUDEDIRS") + Makefile::Dereference("TARGET_ARCH") + "-c ");
    Makefile::DefineVariable(makefile, "LINK.o ", "$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDEDIRS) $(TARGET_ARCH) $(LDFLAGS)");
    Makefile::PrintNewLine(makefile);
    
    Makefile::Declare(makefile, "all:" + Makefile::Dereference("PROGRAM"));
    Makefile::PrintNewLine(makefile);
    
    Makefile::DefineRecipe(makefile, Makefile::Dereference("PROGRAM"), Makefile::Dereference("OBJS"), Makefile::Dereference("LINK.o") + Makefile::Dereference("OUTPUT_OPTION") + " $^ " + Makefile::Dereference("REQLIBS"));
    Makefile::PrintNewLine(makefile);
    
    Makefile::DefineRecipe(makefile, "%.o", "%" + extensions[project.programmingLanguage()], Makefile::Dereference("COMPILE.cpp") + Makefile::Dereference("OUTPUT_OPTION") + " $^");
    Makefile::PrintNewLine(makefile);
    
    Makefile::Declare(makefile, ".PHONY: clean");
    Makefile::DefineRecipe(makefile, "clean", "", Makefile::Dereference("RM") + Makefile::Dereference("OBJS") + Makefile::Dereference("PROGRAM"));
    Makefile::PrintNewLine(makefile);

    makefile.close();

    std::string srcFile = projectDir.string() + "/src/" + project.name() + FileExtension;
    std::ofstream file;
    file.open(srcFile, std::ios::out);

    file << IO::endl;
    file << "#include \"" << project.name() + IncludesExtension << "\"" << IO::endl;
    file << IO::endl;
    file << IO::endl;
    file << "int main()" << IO::endl;
    file << "{" << IO::endl;
    file << "    std::cout << \"testing...\" << std::endl;" << IO::endl;
    file << IO::endl;
    file << "    return EXIT_SUCCESS;" << IO::endl;
    file << "}" << IO::endl;

    file.close();

    std::string CStandardIO;
    std::string CStandardLib;
    std::string CString;
    std::string CMath;
    std::string CTime;

    if (project.programmingLanguage() == ProgrammingLanguage::Cpp) {
        CStandardIO  = "cstdio";
        CStandardLib = "cstdlib";
        CString      = "cstring";
        CMath        = "cmath";
        CTime        = "ctime";
    } else if (project.programmingLanguage() == ProgrammingLanguage::C) {
        CStandardIO  = "stdio.h";
        CStandardLib = "stdlib.h";
        CString      = "string.h";
        CMath        = "math.h";
        CTime        = "time.h";
    }

    std::string includeFile = projectDir.string() + "/include/" + project.name() + IncludesExtension;
    std::ofstream headerFile;
    headerFile.open(includeFile, std::ios::out);

    Source::PrintNewLine(headerFile);
    Source::PrintHeaderFileGuardStart(headerFile, project.name(), project.name(), IncludesExtension);
    Source::PrintNewLine(headerFile);

    Source::IncludeHeader(headerFile, CStandardIO);
    Source::IncludeHeader(headerFile, CStandardLib);
    Source::IncludeHeader(headerFile, CString);
    Source::IncludeHeader(headerFile, CMath);
    Source::IncludeHeader(headerFile, CTime);
    Source::PrintNewLine(headerFile);
    
    if (project.programmingLanguage() == ProgrammingLanguage::Cpp) {
        Source::IncludeHeader(headerFile, "any");
        Source::IncludeHeader(headerFile, "filesystem");
        Source::IncludeHeader(headerFile, "fstream");
        Source::IncludeHeader(headerFile, "iostream");
        Source::IncludeHeader(headerFile, "iterator");
        Source::IncludeHeader(headerFile, "memory");
        Source::IncludeHeader(headerFile, "optional");
        Source::IncludeHeader(headerFile, "string");
        Source::IncludeHeader(headerFile, "utility");
        Source::IncludeHeader(headerFile, "variant");
        Source::IncludeHeader(headerFile, "vector");
        Source::PrintNewLine(headerFile);

        Source::IncludeHeader(headerFile, "boost/lexical_cast.hpp");
        Source::IncludeHeader(headerFile, "boost/program_options.hpp");
        Source::PrintNewLine(headerFile);     
    }

    Source::PrintHeaderFileGuardEnd(headerFile, project.name(), project.name(), IncludesExtension);
    Source::PrintNewLine(headerFile);

    headerFile.close();

    */

    return EXIT_SUCCESS;
}
